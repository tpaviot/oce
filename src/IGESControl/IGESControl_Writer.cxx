// Copyright (c) 1999-2012 OPEN CASCADE SAS
//
// The content of this file is subject to the Open CASCADE Technology Public
// License Version 6.5 (the "License"). You may not use the content of this file
// except in compliance with the License. Please obtain a copy of the License
// at http://www.opencascade.org and read it completely before using this file.
//
// The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
// main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.
//
// The Original Code and all software distributed under the License is
// distributed on an "AS IS" basis, without warranty of any kind, and the
// Initial Developer hereby disclaims all such warranties, including without
// limitation, any warranties of merchantability, fitness for a particular
// purpose or non-infringement. Please see the License for the specific terms
// and conditions governing the rights and limitations under the License.

//cky 16.01.99 Remove couts.
//rln 28.12.98 CCI60005

#include <Standard_Stream.hxx>

#include <IGESControl_Writer.ixx>
#include <IGESControl_Controller.hxx>
#include <IGESSelect_WorkLibrary.hxx>
#include <BRepToIGES_BREntity.hxx>
#include <BRepToIGESBRep_Entity.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Surface.hxx>
#include <GeomToIGES_GeomCurve.hxx>
#include <GeomToIGES_GeomSurface.hxx>
#include <IGESData_IGESWriter.hxx>
#include <XSControl_TransferWriter.hxx>

#include <Interface_Macros.hxx>
#include <Interface_Static.hxx>
#include <ShapeAnalysis_ShapeTolerance.hxx>

#include <gp_XYZ.hxx>
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <GeomAdaptor_Surface.hxx>
#include <BndLib_Add3dCurve.hxx>
#include <BndLib_AddSurface.hxx>
#include <XSAlgo.hxx>
#include <XSAlgo_AlgoContainer.hxx>
#include <TopExp_Explorer.hxx>
#include <Message_ProgressIndicator.hxx>
#include <errno.h>

IGESControl_Writer::IGESControl_Writer ()
    :  theTP (new Transfer_FinderProcess(10000)) ,
       thedit (IGESSelect_WorkLibrary::DefineProtocol()) ,
       thest (Standard_False)
{
//  faudrait aussi (?) prendre les parametres par defaut ... ?
  IGESControl_Controller::Init();
  thedit.SetUnitName(Interface_Static::CVal ("write.iges.unit"));
  thedit.ApplyUnit(); 
  thecr = Interface_Static::IVal ("write.iges.brep.mode");
  themod = thedit.Model();
}

IGESControl_Writer::IGESControl_Writer
  (const Standard_CString unit, const Standard_Integer modecr)
    :  theTP (new Transfer_FinderProcess(10000)) ,
       thedit (IGESSelect_WorkLibrary::DefineProtocol()) ,
       thecr (modecr) , thest (Standard_False)
{
//  faudrait aussi (?) prendre les parametres par defaut ... ?
  IGESControl_Controller::Init();
  thedit.SetUnitName(unit);
  thedit.ApplyUnit();
  themod = thedit.Model();
}

IGESControl_Writer::IGESControl_Writer
  (const Handle(IGESData_IGESModel)& model, const Standard_Integer modecr)
    :  theTP (new Transfer_FinderProcess(10000)) ,
       themod (model) , 
       thedit (model,IGESSelect_WorkLibrary::DefineProtocol()) ,
       thecr (modecr) , thest (Standard_False)     {  }

Handle(IGESData_IGESModel) IGESControl_Writer::Model () const
{
  return themod;
}

Handle(Transfer_FinderProcess) IGESControl_Writer::TransferProcess () const
{
  return theTP;
}

void IGESControl_Writer::SetTransferProcess
  (const Handle(Transfer_FinderProcess)& TP)
{
  theTP = TP;
}

Standard_Boolean IGESControl_Writer::AddShape (const TopoDS_Shape& theShape)
{
  if (theShape.IsNull()) return Standard_False;
  
  // for progress indication
  Handle(Message_ProgressIndicator) progress = theTP->GetProgress();
  if ( ! progress.IsNull() ) { 
    Standard_Integer nbfaces=0;
    for( TopExp_Explorer exp(theShape,TopAbs_FACE); exp.More(); exp.Next() )
      nbfaces++;
    progress->SetScale ( "Faces", 0, nbfaces, 1 );
  }
  
  XSAlgo::AlgoContainer()->PrepareForTransfer();
  
  //  modified by NIZHNY-EAP Tue Aug 29 11:16:54 2000 ___BEGIN___
  Handle(Standard_Transient) info;
  Standard_Real Tol = Interface_Static::RVal("write.precision.val");
  Standard_Real maxTol = Interface_Static::RVal("read.maxprecision.val");
  TopoDS_Shape Shape = XSAlgo::AlgoContainer()->ProcessShape( theShape, Tol, maxTol, 
                                                              "write.iges.resource.name", 
                                                              "write.iges.sequence", info,
                                                              progress );
  //  modified by NIZHNY-EAP Tue Aug 29 11:17:01 2000 ___END___
  Handle(IGESData_IGESEntity) ent; 
  BRepToIGES_BREntity   B0;  B0.SetTransferProcess(theTP); B0.SetModel(themod);
  BRepToIGESBRep_Entity B1;  B1.SetTransferProcess(theTP); B1.SetModel(themod);
  if (thecr) ent = B1.TransferShape(Shape);
  else       ent = B0.TransferShape(Shape);

  if(ent.IsNull())
    return Standard_False;
//  modified by NIZHNY-EAP Tue Aug 29 11:37:18 2000 ___BEGIN___
  XSAlgo::AlgoContainer()->MergeTransferInfo(theTP, info);
//  modified by NIZHNY-EAP Tue Aug 29 11:37:25 2000 ___END___
  
  //22.10.98 gka BUC60080

  Standard_Integer oldnb = themod->NbEntities();
  Standard_Boolean aent = AddEntity (ent);
  Standard_Integer newnb = themod->NbEntities();

  Standard_Real oldtol = themod->GlobalSection().Resolution(), newtol;
  
  Standard_Integer tolmod = Interface_Static::IVal("write.precision.mode");
  if (tolmod == 2)
    newtol = Interface_Static::RVal("write.precision.val");
  else {
    ShapeAnalysis_ShapeTolerance stu; 
    Standard_Real Tolv = stu.Tolerance (Shape, tolmod, TopAbs_VERTEX);
    Standard_Real Tole = stu.Tolerance (Shape, tolmod, TopAbs_EDGE); 

    if (tolmod == 0 ) {   //Average
      Standard_Real Tol1 = (Tolv + Tole) / 2;
      newtol = (oldtol * oldnb + Tol1 * (newnb - oldnb)) / newnb;
    }
    else if (tolmod < 0) {//Least
      newtol = Min (Tolv, Tole);
      if (oldnb > 0) newtol = Min (oldtol, newtol);
    }
    else {                //Greatest
      newtol = Max (Tolv, Tole);
      if (oldnb > 0) newtol = Max (oldtol, newtol);
    }
  }
  
  IGESData_GlobalSection gs = themod->GlobalSection();
  gs.SetResolution (newtol / gs.UnitValue());//rln 28.12.98 CCI60005

  //#34 22.10.98 rln BUC60081
  Bnd_Box box;
  BRepBndLib::Add (Shape, box);
  if (!(box.IsVoid() || box.IsOpenXmax() || box.IsOpenYmax() || box.IsOpenZmax() || box.IsOpenXmin() || box.IsOpenYmin() || box.IsOpenZmin())){
    Standard_Real aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
    box.Get (aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);
    gs.MaxMaxCoords (gp_XYZ (aXmax / gs.UnitValue(),
	     		     aYmax / gs.UnitValue(),
	  		     aZmax / gs.UnitValue()));
    gs.MaxMaxCoords (gp_XYZ (aXmin / gs.UnitValue(),
 			     aYmin / gs.UnitValue(),
			     aZmin / gs.UnitValue()));
  }

  themod->SetGlobalSection(gs);

  return aent;
}

Standard_Boolean IGESControl_Writer::AddGeom (const Handle(Standard_Transient)& geom)
{
  if (geom.IsNull() || !geom->IsKind (STANDARD_TYPE (Geom_Geometry)))
    return Standard_False;
  DeclareAndCast(Geom_Curve,Curve,geom);
  DeclareAndCast(Geom_Surface,Surf,geom);
  Handle(IGESData_IGESEntity) ent; 

//  On reconnait : Curve et Surface de Geom
//   quid de Point; Geom2d ?

//  GeomToIGES_GeomPoint GP;
  GeomToIGES_GeomCurve GC;    GC.SetModel(themod);
  GeomToIGES_GeomSurface GS;  GS.SetModel(themod);

  //#34 22.10.98 rln BUC60081
  IGESData_GlobalSection gs = themod->GlobalSection();
  Bnd_Box box;

  if (!Curve.IsNull()) {
    ent = GC.TransferCurve(Curve,Curve->FirstParameter(),Curve->LastParameter());
    BndLib_Add3dCurve::Add (GeomAdaptor_Curve (Curve), 0, box); }
  else if (!Surf.IsNull()) {
    Standard_Real U1,U2,V1,V2;
    Surf->Bounds(U1,U2,V1,V2);
    ent = GS.TransferSurface(Surf,U1,U2,V1,V2);
    BndLib_AddSurface::Add (GeomAdaptor_Surface (Surf), 0, box);
  }

  Standard_Real aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
  box.Get (aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);
  gs.MaxMaxCoords (gp_XYZ (aXmax / gs.UnitValue(),
			   aYmax / gs.UnitValue(),
			   aZmax / gs.UnitValue()));
  gs.MaxMaxCoords (gp_XYZ (aXmin / gs.UnitValue(),
			   aYmin / gs.UnitValue(),
			   aZmin / gs.UnitValue()));
  themod->SetGlobalSection(gs);
  return AddEntity (ent);
}

Standard_Boolean IGESControl_Writer::AddEntity (const Handle(IGESData_IGESEntity)& ent)
{
  if (ent.IsNull()) return Standard_False;
  themod->AddWithRefs(ent,IGESSelect_WorkLibrary::DefineProtocol());
  thest = Standard_False;
  return Standard_True;
}

void IGESControl_Writer::ComputeModel ()
{
  if (thest) return;
  thedit.ComputeStatus();
  thedit.AutoCorrectModel();
  thest = Standard_True;
}

Standard_Boolean IGESControl_Writer::Write
  (Standard_OStream& S, const Standard_Boolean fnes)
{
  if (!S) return Standard_False;
  ComputeModel();
  Standard_Integer nbEnt = themod->NbEntities();
#ifdef DEBUG
  cout<<" IGES Write : "<<nbEnt<<" ent.s"<< flush;
#endif
  if(!nbEnt)
    return Standard_False;
  IGESData_IGESWriter IW (themod);
//  ne pas oublier le mode fnes ... a transmettre a IW
  IW.SendModel (IGESSelect_WorkLibrary::DefineProtocol());
#ifdef DEBUG
  cout<<" ...  ecriture  ..."<<flush;
#endif
  if (fnes) IW.WriteMode() = 10;
  Standard_Boolean status = IW.Print(S);
#ifdef DEBUG
  cout<<" ...  fichier ecrit  ..."<<endl;
#endif
  return status;
}

Standard_Boolean IGESControl_Writer::Write
  (const Standard_CString file, const Standard_Boolean fnes)
{
  ofstream fout(file,ios::out);
  if (!fout) return Standard_False;
#ifdef DEBUG
  cout<<" Ecriture fichier ("<< (fnes ? "fnes" : "IGES") <<"): "<<file<<endl;
#endif
  Standard_Boolean res = Write (fout,fnes);

  errno = 0;
  fout.close();
  res = fout.good() && res && !errno;

  return res;
}

void IGESControl_Writer::PrintStatsTransfer
  (const Standard_Integer what, const Standard_Integer mode) const
{
  XSControl_TransferWriter::PrintStatsProcess (theTP,what,mode);
}
