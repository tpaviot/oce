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

#include <IGESControl_ActorWrite.ixx>
#include <TransferBRep_ShapeMapper.hxx>
#include <Interface_Macros.hxx>
#include <IGESData_IGESModel.hxx>

#include <BRepToIGES_BREntity.hxx>
#include <BRepToIGESBRep_Entity.hxx>

#include <Transfer_TransientMapper.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Surface.hxx>
#include <GeomToIGES_GeomCurve.hxx>
#include <GeomToIGES_GeomSurface.hxx>
#include <XSAlgo.hxx>
#include <XSAlgo_AlgoContainer.hxx>
#include <Interface_Static.hxx>

IGESControl_ActorWrite::IGESControl_ActorWrite ()  {  ModeTrans() = 0;  }

Standard_Boolean  IGESControl_ActorWrite::Recognize
  (const Handle(Transfer_Finder)& start)
{
  DeclareAndCast(TransferBRep_ShapeMapper,shmap,start);
  if (!shmap.IsNull()) return Standard_True;
  DeclareAndCast(Transfer_TransientMapper,gemap,start);
  if (!gemap.IsNull()) {
    Handle(Standard_Transient) geom = gemap->Value();
    DeclareAndCast(Geom_Curve,Curve,geom);
    DeclareAndCast(Geom_Surface,Surf,geom);
    if (!Curve.IsNull() || !Surf.IsNull()) return Standard_True;
  }
  return Standard_False;
}

Handle(Transfer_Binder)  IGESControl_ActorWrite::Transfer
  (const Handle(Transfer_Finder)& start,
   const Handle(Transfer_FinderProcess)& FP)
{
  XSAlgo::AlgoContainer()->PrepareForTransfer();
    
  DeclareAndCast(IGESData_IGESModel,modl,FP->Model());
  if (modl.IsNull()) return NullResult();
  if (themodetrans < 0 || themodetrans > 1) return NullResult();
  Handle(Standard_Transient) ent;

  DeclareAndCast(TransferBRep_ShapeMapper,shmap,start);
  if (!shmap.IsNull()) {
    TopoDS_Shape shape = shmap->Value();
    if (shape.IsNull()) return NullResult();
//  modified by NIZHNY-EAP Tue Aug 29 11:16:54 2000 ___BEGIN___
    Handle(Standard_Transient) info;
    Standard_Real Tol = Interface_Static::RVal("write.precision.val");
    Standard_Real maxTol = Interface_Static::RVal("read.maxprecision.val");
    shape = XSAlgo::AlgoContainer()->ProcessShape( shape, Tol, maxTol, 
                                                   "write.iges.resource.name", 
                                                   "write.iges.sequence", info,
                                                   FP->GetProgress() );
//  modified by NIZHNY-EAP Tue Aug 29 11:17:01 2000 ___END___

    BRepToIGES_BREntity   BR0; BR0.SetModel(modl);  BR0.SetTransferProcess(FP);
    BRepToIGESBRep_Entity BR1; BR1.SetModel(modl);  BR1.SetTransferProcess(FP);

    if (themodetrans == 0) ent = BR0.TransferShape(shape);
    if (themodetrans == 1) ent = BR1.TransferShape(shape);
//  modified by NIZHNY-EAP Tue Aug 29 11:37:18 2000 ___BEGIN___
    XSAlgo::AlgoContainer()->MergeTransferInfo(FP, info);
//  modified by NIZHNY-EAP Tue Aug 29 11:37:25 2000 ___END___
    if (!ent.IsNull()) return TransientResult(ent);
  }
  DeclareAndCast(Transfer_TransientMapper,gemap,start);
  if (!gemap.IsNull()) {
    Handle(Standard_Transient) geom = gemap->Value();
    DeclareAndCast(Geom_Curve,Curve,geom);
    DeclareAndCast(Geom_Surface,Surf,geom);
 
//  On reconnait : Curve et Surface de Geom
//   quid de Point; Geom2d ?
 
//  GeomToIGES_GeomPoint GP;
    GeomToIGES_GeomCurve GC;    GC.SetModel(modl);
    GeomToIGES_GeomSurface GS;  GS.SetModel(modl);
    if (!Curve.IsNull())
      ent = GC.TransferCurve(Curve,Curve->FirstParameter(),Curve->LastParameter())
;
    else if (!Surf.IsNull()) {
      Standard_Real U1,U2,V1,V2;
      Surf->Bounds(U1,U2,V1,V2);
      ent = GS.TransferSurface(Surf,U1,U2,V1,V2);
    }
    if (!ent.IsNull()) return TransientResult(ent);
  }

  return NullResult();
}
