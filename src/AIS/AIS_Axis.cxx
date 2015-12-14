// Created on: 1995-08-09
// Created by: Arnaud BOUZY/Odile Olivier
// Copyright (c) 1995-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <AIS_Axis.ixx>
#include <Aspect_TypeOfLine.hxx>
#include <Prs3d_Drawer.hxx>
#include <Prs3d_LineAspect.hxx>
#include <Prs3d_DatumAspect.hxx>
#include <Graphic3d_AspectLine3d.hxx>
#include <Graphic3d_Structure.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <SelectMgr_EntityOwner.hxx>
#include <SelectMgr_Selection.hxx>
#include <SelectBasics_EntityOwner.hxx>
#include <Select3D_SensitiveSegment.hxx>
#include <StdPrs_Curve.hxx>
#include <TopoDS.hxx>
#include <Geom_Axis1Placement.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <Geom_Line.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <DsgPrs_XYZAxisPresentation.hxx>
#include <UnitsAPI.hxx>

//=======================================================================
//function : AIS_Axis
//purpose  :
//=======================================================================
AIS_Axis::AIS_Axis(const Handle(Geom_Line)& aComponent):
myComponent(aComponent),
myTypeOfAxis(AIS_TOAX_Unknown),
myIsXYZAxis(Standard_False)
{
  myDrawer->SetLineAspect(new Prs3d_LineAspect
     (Quantity_NOC_RED,Aspect_TOL_DOTDASH,1.));
  SetInfiniteState();

  gp_Dir thedir = myComponent->Position().Direction();
  gp_Pnt loc = myComponent->Position().Location();
//POP  Standard_Real aLength = UnitsAPI::CurrentToLS (250000. ,"LENGTH");
  Standard_Real aLength = UnitsAPI::AnyToLS(250000., "mm");
  myPfirst = loc.XYZ() + aLength*thedir.XYZ();
  myPlast = loc.XYZ() - aLength*thedir.XYZ();
}

//=======================================================================
//function : AIS_Axis
//purpose  :  Xaxis, YAxis, ZAxis
//=======================================================================
AIS_Axis::AIS_Axis(const Handle(Geom_Axis2Placement)& aComponent,
		   const AIS_TypeOfAxis anAxisType):
myAx2(aComponent),
myTypeOfAxis(anAxisType),
myIsXYZAxis(Standard_True)
{
  Handle (Prs3d_DatumAspect) DA = new Prs3d_DatumAspect();
//POP  Standard_Real aLength = UnitsAPI::CurrentToLS (100. ,"LENGTH"); 
  Standard_Real aLength;
  try {
    aLength = UnitsAPI::AnyToLS(100. ,"mm");
  } catch (Standard_Failure) {
    aLength = 0.1;
  }
  DA->SetAxisLength(aLength,aLength,aLength);
  Quantity_NameOfColor col = Quantity_NOC_TURQUOISE;
  DA->FirstAxisAspect()->SetColor(col);
  DA->SecondAxisAspect()->SetColor(col);
  DA->ThirdAxisAspect()->SetColor(col);
  myDrawer->SetDatumAspect(DA); 
  
  ComputeFields();
}

//=======================================================================
//function : AIS_Axis
//purpose  : 
//=======================================================================
AIS_Axis::AIS_Axis(const Handle(Geom_Axis1Placement)& anAxis)
:myComponent(new Geom_Line(anAxis->Ax1())),
 myTypeOfAxis(AIS_TOAX_Unknown),
 myIsXYZAxis(Standard_False)
{
  myDrawer->SetLineAspect(new Prs3d_LineAspect(Quantity_NOC_RED,Aspect_TOL_DOTDASH,1.));
  SetInfiniteState();

  gp_Dir thedir = myComponent->Position().Direction();
  gp_Pnt loc = myComponent->Position().Location();
//POP  Standard_Real aLength = UnitsAPI::CurrentToLS (250000. ,"LENGTH");
  Standard_Real aLength = UnitsAPI::AnyToLS(250000. ,"mm"); 
  myPfirst = loc.XYZ() + aLength*thedir.XYZ();
  myPlast = loc.XYZ() - aLength*thedir.XYZ();
}


//=======================================================================
//function : SetComponent
//purpose  : 
//=======================================================================

void AIS_Axis::SetComponent(const Handle(Geom_Line)& aComponent)
{
  myComponent = aComponent;
  myTypeOfAxis = AIS_TOAX_Unknown;
  myIsXYZAxis = Standard_False;
  SetInfiniteState();

  gp_Dir thedir = myComponent->Position().Direction();
  gp_Pnt loc = myComponent->Position().Location();
//POP  Standard_Real aLength = UnitsAPI::CurrentToLS (250000. ,"LENGTH");
  Standard_Real aLength = UnitsAPI::AnyToLS(250000. ,"mm");
  myPfirst = loc.XYZ() + aLength*thedir.XYZ();
  myPlast = loc.XYZ() - aLength*thedir.XYZ();
}



//=======================================================================
//function : SetAxis2Placement
//purpose  : 
//=======================================================================

void AIS_Axis::SetAxis2Placement(const Handle(Geom_Axis2Placement)& aComponent,
				 const AIS_TypeOfAxis anAxisType)
{
  myAx2 = aComponent;
  myTypeOfAxis = anAxisType;
  myIsXYZAxis = Standard_True;
  ComputeFields();
}

//=======================================================================
//function : SetAxis1Placement
//purpose  : 
//=======================================================================

void AIS_Axis::SetAxis1Placement(const Handle(Geom_Axis1Placement)& anAxis)
{
  SetComponent(new Geom_Line(anAxis->Ax1()));
}

//=======================================================================
//function : Compute
//purpose  : 
//=======================================================================
void AIS_Axis::Compute(const Handle(PrsMgr_PresentationManager3d)&,
		       const Handle(Prs3d_Presentation)& aPresentation, 
		       const Standard_Integer)
{
  aPresentation->Clear();

  //Pro.... : pas de prise en compte des axes lors du FITALL (jmi)
  aPresentation->SetInfiniteState (myInfiniteState);

  aPresentation->SetDisplayPriority(5);
  if (!myIsXYZAxis ){
    GeomAdaptor_Curve curv(myComponent);
    StdPrs_Curve::Add(aPresentation,curv,myDrawer);
  }
  else {
    DsgPrs_XYZAxisPresentation::Add(aPresentation,myLineAspect,myDir,myVal,myText,myPfirst,myPlast);
  }

}

void AIS_Axis::Compute(const Handle(Prs3d_Projector)& aProjector, const Handle(Geom_Transformation)& aTransformation, const Handle(Prs3d_Presentation)& aPresentation)
{
// Standard_NotImplemented::Raise("AIS_Axis::Compute(const Handle(Prs3d_Projector)&, const Handle(Geom_Transformation)&, const Handle(Prs3d_Presentation)&)");
  PrsMgr_PresentableObject::Compute( aProjector , aTransformation , aPresentation ) ;
}

//=======================================================================
//function : ComputeSelection
//purpose  : 
//=======================================================================

void AIS_Axis::ComputeSelection(const Handle(SelectMgr_Selection)& aSelection,
				const Standard_Integer)
{
  Handle(SelectMgr_EntityOwner) eown = new SelectMgr_EntityOwner(this);
  eown -> SelectBasics_EntityOwner::Set(3);
  Handle(Select3D_SensitiveSegment) seg = new Select3D_SensitiveSegment(eown,
									myPfirst,
									myPlast);
  aSelection->Add(seg);
}

//=======================================================================
//function : SetColor
//purpose  : 
//=======================================================================


void AIS_Axis::SetColor(const Quantity_NameOfColor aCol)
{
  SetColor(Quantity_Color(aCol));
}

void AIS_Axis::SetColor(const Quantity_Color &aCol)
{
  hasOwnColor=Standard_True;
  myOwnColor=aCol;
  myDrawer->LineAspect()->SetColor(aCol);
  
  const Handle(Prs3d_DatumAspect)& DA = myDrawer->DatumAspect();
  DA->FirstAxisAspect()->SetColor(aCol);
  DA->SecondAxisAspect()->SetColor(aCol);
  DA->ThirdAxisAspect()->SetColor(aCol);
  
}

//=======================================================================
//function : SetWidth 
//purpose  : 
//=======================================================================
void AIS_Axis::SetWidth(const Standard_Real aValue)
{
  
  if(aValue<0.0) return;
  if(aValue==0) UnsetWidth();
  
  myDrawer->LineAspect()->SetWidth(aValue);
  
  const Handle(Prs3d_DatumAspect)& DA = myDrawer->DatumAspect();
  DA->FirstAxisAspect()->SetWidth(aValue);
  DA->SecondAxisAspect()->SetWidth(aValue);
  DA->ThirdAxisAspect()->SetWidth(aValue);
}


//=======================================================================
//function : Compute
//purpose  : to avoid warning
//=======================================================================
void AIS_Axis::Compute(const Handle(Prs3d_Projector)&, 
		       const Handle(Prs3d_Presentation)&)
{
}

//=======================================================================
//function : ComputeFields
//purpose  : 
//=======================================================================
void AIS_Axis::ComputeFields()
{
  if (myIsXYZAxis){
    // calcul de myPFirst,myPlast
    Handle(Prs3d_DatumAspect) DA = myDrawer->DatumAspect();
    gp_Ax2 anAxis = myAx2->Ax2();
    const gp_Pnt& Orig = anAxis.Location();
    const gp_Dir& oX   = anAxis.XDirection();
    const gp_Dir& oY   = anAxis.YDirection();
    const gp_Dir& oZ   = anAxis.Direction();
    Quantity_Length xo,yo,zo,x = 0.,y = 0.,z = 0.;
    Orig.Coord(xo,yo,zo);
    myPfirst.SetCoord(xo,yo,zo);
    
    switch (myTypeOfAxis) {
    case AIS_TOAX_XAxis:
      {
	oX.Coord(x,y,z);
	myVal = DA->FirstAxisLength();
	myDir = oX;
	myLineAspect = DA->FirstAxisAspect();
	myText = Standard_CString ("X");
	break;
      }
    case AIS_TOAX_YAxis:
      {
	oY.Coord(x,y,z);
	myVal = DA->SecondAxisLength();
	myDir = oY;
	myLineAspect = DA->SecondAxisAspect();
	myText = Standard_CString ("Y");
	break;
      }
    case AIS_TOAX_ZAxis:
      {
	oZ.Coord(x,y,z); 
	myVal = DA->ThirdAxisLength();
	myDir = oZ;
	myLineAspect = DA->ThirdAxisAspect();
	myText = Standard_CString ("Z");
	break;
      }
     default:
      break;
    }
    
    myComponent = new Geom_Line(Orig,myDir);
    x = xo + x*myVal;   y = yo + y*myVal;  z = zo + z*myVal;
    myPlast.SetCoord(x,y,z);
    SetInfiniteState();
  }
}

//=======================================================================
//function : AcceptDisplayMode
//purpose  : 
//=======================================================================

 Standard_Boolean  AIS_Axis::
AcceptDisplayMode(const Standard_Integer aMode) const
{return aMode == 0;}

//=======================================================================
//function : UnsetColor
//purpose  : 
//=======================================================================
void AIS_Axis::UnsetColor()
{
  
  myDrawer->LineAspect()->SetColor(Quantity_NOC_RED);

  hasOwnColor=Standard_False;

  myDrawer->DatumAspect()->FirstAxisAspect()->SetColor(Quantity_NOC_TURQUOISE);
  myDrawer->DatumAspect()->SecondAxisAspect()->SetColor(Quantity_NOC_TURQUOISE);
  myDrawer->DatumAspect()->ThirdAxisAspect()->SetColor(Quantity_NOC_TURQUOISE);
}
//=======================================================================
//function : UnsetWidth
//purpose  : 
//=======================================================================

void AIS_Axis::UnsetWidth()
{
  myOwnWidth = 0.0;
  myDrawer->LineAspect()->SetWidth(1.);
  myDrawer->DatumAspect()->FirstAxisAspect()->SetWidth(1.);
  myDrawer->DatumAspect()->SecondAxisAspect()->SetWidth(1.);
  myDrawer->DatumAspect()->ThirdAxisAspect()->SetWidth(1.);
}

