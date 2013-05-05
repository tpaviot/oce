// Created on: 1996-12-05
// Created by: Flore Lantheaume/Odile Olivier
// Copyright (c) 1996-1999 Matra Datavision
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


#define BUC60915        //GG 05/06/01 Enable to compute the requested arrow size
//                      if any in all dimensions.

#include <Standard_NotImplemented.hxx>

#include <AIS_Chamf2dDimension.ixx>

#include <DsgPrs_Chamf2dPresentation.hxx>

#include <Prs3d_ArrowAspect.hxx>
#include <Prs3d_LengthAspect.hxx>
#include <Prs3d_Drawer.hxx>

#include <SelectMgr_EntityOwner.hxx>
#include <Select3D_SensitiveSegment.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Edge.hxx>

#include <TopAbs_Orientation.hxx>

#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>

#include <gp_Dir.hxx>
#include <gp_Pln.hxx>
#include <gp_Vec.hxx>

#include <Geom_Line.hxx>

#include <ElCLib.hxx>

#include <Precision.hxx>

#include <TCollection_AsciiString.hxx>
#include <TCollection_ExtendedString.hxx>

#include <BRepTools_WireExplorer.hxx>

#include <AIS.hxx>
#include <AIS_Drawer.hxx>

#include <BRepAdaptor_Surface.hxx>
#include <ProjLib.hxx>
#include <Select3D_SensitiveBox.hxx>

//=======================================================================
//function : Constructor
//purpose  : 
//=======================================================================
AIS_Chamf2dDimension::AIS_Chamf2dDimension(const TopoDS_Shape& aFShape, 
					   const Handle(Geom_Plane)& aPlane, 
					   const Standard_Real aVal, 
					   const TCollection_ExtendedString& aText)
:AIS_Relation()
{
  myFShape = aFShape;
  myPlane = aPlane;
  myVal = aVal;
  myText = aText;
  mySymbolPrs = DsgPrs_AS_LASTAR;
  myAutomaticPosition = Standard_True;

  myArrowSize = myVal / 100.;
}
//=======================================================================
//function : Constructor
//purpose  : 
//=======================================================================
AIS_Chamf2dDimension::AIS_Chamf2dDimension(const TopoDS_Shape& aFShape, 
					   const Handle(Geom_Plane)& aPlane, 
					   const Standard_Real aVal, 
					   const TCollection_ExtendedString& aText,
					   const gp_Pnt& aPosition, 
					   const DsgPrs_ArrowSide aSymbolPrs ,
					   const Standard_Real anArrowSize)
:AIS_Relation()
{
  myFShape = aFShape;
  myPlane = aPlane;
  myVal = aVal;
  myText = aText;
  myPosition = aPosition;
  mySymbolPrs = aSymbolPrs;
#ifdef BUC60915
  SetArrowSize( anArrowSize );
#else
  myArrowSize = anArrowSize;
#endif
  myAutomaticPosition = Standard_False;
}


//=======================================================================
//function : Compute
//purpose  : 
//=======================================================================

void AIS_Chamf2dDimension::Compute(const Handle(PrsMgr_PresentationManager3d)& , 
				   const Handle(Prs3d_Presentation)& aPresentation, 
				   const Standard_Integer)
{
    aPresentation->Clear();

    Handle(Geom_Line) glin;
    gp_Pnt pfirst,plast;
    const TopoDS_Edge& thechamfedge = TopoDS::Edge(myFShape);
    if (!AIS::ComputeGeometry(thechamfedge, glin,pfirst,plast) ) 
      return;


    gp_Dir dir1 (glin->Position().Direction());
    gp_Dir norm1 = myPlane->Pln().Axis().Direction();
    myDir = norm1.Crossed(dir1);
    

    //-------------------------------------------------
    // calcul d'une direction orthogonale a l'edge du
    // chanfrein et dirigee vers l'ext. du contour
    //-------------------------------------------------
    

    // recup. d'une edge adjacente a l'edge du chanfrein
    /*TopoDS_Edge nextedge = TopoDS::Edge(mySShape);

    gp_Pnt pfirstnext,plastnext;
    Handle(Geom_Line) glinnext;
    if (!AIS::ComputeGeometry(nextedge,glinnext,pfirstnext,plastnext) )
      return;
    
    gp_Vec v1(pfirst,plast);
    gp_Vec v2;
    if (pfirst.IsEqual(plastnext, Precision::Confusion()))
      v2.SetXYZ(pfirstnext.XYZ() - pfirst.XYZ());
    else
      v2.SetXYZ(plastnext.XYZ() - pfirst.XYZ());
    gp_Vec crossvec = v1.Crossed(v2);
    
    myDir = dimserv.GetDirection().Crossed(glin->Position().Direction());
    if (crossvec.Dot(dimserv.GetDirection()) > 0 )
      myDir.Reverse();*/     //       myDir   => donne a la creation
    
    //--------------------------------------------
    //Calcul du point de positionnement du texte
    //--------------------------------------------
    gp_Pnt curpos;
    if (myAutomaticPosition) {
      myPntAttach.SetXYZ((pfirst.XYZ()+plast.XYZ())/2);
      gp_Vec transVec(myDir);
      transVec*=myVal;
      curpos = myPntAttach.Translated(transVec);

      if (myIsSetBndBox)
	curpos = AIS::TranslatePointToBound( curpos, myDir, myBndBox );

      myPosition = curpos;
    }
    else {

      myPntAttach.SetXYZ((pfirst.XYZ()+plast.XYZ())/2);
      Handle(Geom_Line) dimLin = new Geom_Line(myPntAttach, myDir);
      Standard_Real parcurpos = ElCLib::Parameter(dimLin->Lin(),myPosition);
      curpos = ElCLib::Value(parcurpos,dimLin->Lin());
      //static Standard_Real minlength = 0.005;
      //taille minimale de la dimension

      if ( curpos.Distance(myPntAttach) < 5. ) {
	gp_Vec transVec(myDir);
	transVec*=5.;
	curpos = myPntAttach.Translated(transVec);
      }
      myPosition = curpos;
    }
    
    Handle(Prs3d_LengthAspect) la = myDrawer->LengthAspect();
    Handle(Prs3d_ArrowAspect) arr = la->Arrow1Aspect();
    
    //-------------------------------------------------
    //Calcul de la boite englobante du component pour
    //determiner la taille de la fleche
    //-------------------------------------------------

#ifdef BUC60915
    if( !myArrowSizeIsDefined ) {
#endif
      Standard_Real arrsize = myArrowSize;
      if ( (myVal/4) < arrsize)
        arrsize = myVal/4;
      if (arrsize > 30.) 
        arrsize = 30.;
      else if (arrsize < 8.)
        arrsize = 8.;
#ifdef BUC60915
      myArrowSize = arrsize;
    }
    arr->SetLength(myArrowSize);
#else
    arr->SetLength(arrsize);
#endif
    
    //Calcul de la presentation
    DsgPrs_Chamf2dPresentation::Add(aPresentation,
				    myDrawer,
				    myPntAttach,
				    curpos,
				    myText,
				    mySymbolPrs);
  
  }

//=======================================================================
//function : Compute
//purpose  : to avoid warning
//=======================================================================

void AIS_Chamf2dDimension::Compute(const Handle(Prs3d_Projector)& aProjector,
				   const Handle(Prs3d_Presentation)& aPresentation)
{
// Standard_NotImplemented::Raise("AIS_Chamf2dDimension::Compute(const Handle(Prs3d_Projector)&,const Handle(Prs3d_Presentation)&)");
 PrsMgr_PresentableObject::Compute( aProjector , aPresentation ) ;
}

void AIS_Chamf2dDimension::Compute(const Handle_Prs3d_Projector& aProjector, const Handle_Geom_Transformation& aTransformation, const Handle_Prs3d_Presentation& aPresentation)
{
// Standard_NotImplemented::Raise("AIS_Chamf2dDimension::Compute(const Handle_Prs3d_Projector&, const Handle_Geom_Transformation&, const Handle_Prs3d_Presentation&)");
  PrsMgr_PresentableObject::Compute( aProjector , aTransformation , aPresentation ) ;
}

//=======================================================================
//function : ComputeSelection
//purpose  : 
//=======================================================================

void AIS_Chamf2dDimension::ComputeSelection(const Handle(SelectMgr_Selection)& aSelection, 
					    const Standard_Integer)
{
  Handle(SelectMgr_EntityOwner) own = new SelectMgr_EntityOwner(this,7);
  Handle(Select3D_SensitiveSegment) seg = new Select3D_SensitiveSegment(own,myPntAttach,myPosition);
  aSelection->Add(seg);

  // Text
  Standard_Real size(Min(myVal/100.+1.e-6,myArrowSize+1.e-6));
  Handle( Select3D_SensitiveBox ) box = new Select3D_SensitiveBox( own,
								   myPosition.X(),
								   myPosition.Y(),
								   myPosition.Z(),
								   myPosition.X() + size,
								   myPosition.Y() + size,
								   myPosition.Z() + size);    
  aSelection->Add(box);
}

