// Created on: 1995-10-09
// Created by: Arnaud BOUZY/Odile Olivier
// Copyright (c) 1995-1999 Matra Datavision
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


//GER61351		//GG_171199     Enable to set an object RGB color instead a restricted object NameOfColor.

#define IMP120100	// GG Add SetTextColor() and SetArrowColor() methods

#include <AIS_Trihedron.ixx>
#include <DsgPrs_DatumPrs.hxx>
#include <SelectBasics_EntityOwner.hxx>
#include <SelectMgr_EntityOwner.hxx>
#include <Select3D_SensitiveSegment.hxx>
#include <Select3D_SensitiveFace.hxx>
#include <Select3D_SensitivePoint.hxx>
#include <Geom_Axis2Placement.hxx>
#include <Geom_Line.hxx>
#include <Geom_Point.hxx>
#include <Geom_Plane.hxx>
#include <Geom_CartesianPoint.hxx>
#include <gp_Dir.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <Prs3d_Drawer.hxx>
#include <Prs3d_LineAspect.hxx>
#include <Prs3d_TextAspect.hxx>
#include <Prs3d_ArrowAspect.hxx>
#include <Prs3d_DatumAspect.hxx>
#include <Graphic3d_AspectLine3d.hxx>
#include <Graphic3d_Structure.hxx>
#include <Graphic3d_MaterialAspect.hxx>
#include <Graphic3d_AspectFillArea3d.hxx>
#include <Aspect_TypeOfLine.hxx>
#include <AIS_Drawer.hxx>
#include <AIS_Plane.hxx>
#include <AIS_Axis.hxx>
#include <AIS_Point.hxx>
#include <UnitsAPI.hxx>

#include <Select3D_SensitiveBox.hxx>
#include <Select3D_SensitiveTriangle.hxx>
#include <TColgp_Array1OfPnt.hxx>



//=======================================================================
//function : AIS_Trihedron
//purpose  : 
//=======================================================================
AIS_Trihedron::AIS_Trihedron(const Handle(Geom_Axis2Placement)& aComponent):
myComponent(aComponent),
myHasOwnSize(Standard_False)
#ifdef IMP120100
,myHasOwnTextColor(Standard_False)
,myHasOwnArrowColor(Standard_False)
#endif

{  LoadSubObjects();}



//=======================================================================
//function : SetComponent
//purpose  : 
//=======================================================================

void AIS_Trihedron::SetComponent(const Handle(Geom_Axis2Placement)& aComponent)
{
  myComponent = aComponent;

  // Remove from current context and nullify objects to update
  Handle(AIS_InteractiveContext) anAISContext = GetContext();
  Standard_Boolean hasContext = (anAISContext.IsNull() == Standard_False);
  Standard_Integer anIdx;
  for (anIdx = 0; anIdx < 7; anIdx++)
  {
    // Deselect object
    if (hasContext)
    {
      if (anAISContext->IsSelected (myShapes[anIdx]))
        anAISContext->AddOrRemoveSelected (myShapes[anIdx], Standard_False);

      anAISContext->Remove (myShapes[anIdx], Standard_False);
    }
    myShapes[anIdx].Nullify();
  }

  LoadSubObjects();
}

//=======================================================================
//function : SetLocation
//purpose  : 
//=======================================================================

void AIS_Trihedron::SetLocation(const TopLoc_Location& aLoc)
{
  // Update location to the subshapes
  Standard_Integer anIdx;
  for (anIdx = 0; anIdx < 7; anIdx++)
    myShapes[anIdx]->SetLocation (aLoc);

  AIS_InteractiveObject::SetLocation (aLoc);
}

//=======================================================================
//function : SetSize
//purpose  : 
//=======================================================================
void AIS_Trihedron::SetSize(const Standard_Real aValue)
{
  myHasOwnSize = Standard_True;
  if(!myDrawer->HasDatumAspect()){
    Handle (Prs3d_DatumAspect) DA = new Prs3d_DatumAspect();
    myDrawer->SetDatumAspect(DA);
  }
  
  myDrawer->DatumAspect()->SetAxisLength(aValue,aValue,aValue);
  
  for(Standard_Integer i=4;i<=6;i++) 
    (*((Handle(AIS_Plane)*)&myShapes[i]))->SetSize(aValue);

  Update();
  UpdateSelection();
}



//=======================================================================
//function : UnsetSize
//purpose  : if the object has 1 color, the default size of the 
//           drawer is reproduced, otherwise DatumAspect becomes null
//=======================================================================

void AIS_Trihedron::UnsetSize()
{
  if(!myHasOwnSize) return;
  
  myHasOwnSize = Standard_False;
  if(hasOwnColor){
    const Handle(Prs3d_DatumAspect)& DA = myDrawer->Link()->DatumAspect();
    myDrawer->DatumAspect()->SetAxisLength(DA->FirstAxisLength(),
					   DA->SecondAxisLength(),
					   DA->ThirdAxisLength());
  }
  else
    myDrawer->DatumAspect().Nullify();
  Update();
  UpdateSelection();

}

//=======================================================================
//function : Size
//purpose  : 
//=======================================================================

Standard_Real AIS_Trihedron::Size() const 
{
  if(myDrawer->HasDatumAspect()){
    myDrawer->Link()->DatumAspect(); // ? to ensure that myDrawer->myLink is not null for next call ?
    return myDrawer->DatumAspect()->FirstAxisLength();
  }
  else
    //return the Defaut value
    return 100. ;
    

}

//=======================================================================
//function : XAxis
//purpose  : 
//=======================================================================
Handle(AIS_Axis) AIS_Trihedron::XAxis() const 
{
  Handle(AIS_Axis) anAxis = Handle(AIS_Axis)::DownCast(myShapes[1]);
  if (anAxis.IsNull()) anAxis = new AIS_Axis (myComponent,AIS_TOAX_XAxis);
  return anAxis;
}

//=======================================================================
//function : YAxis
//purpose  : 
//=======================================================================
Handle(AIS_Axis) AIS_Trihedron::YAxis() const 
{
  Handle(AIS_Axis) anAxis = Handle(AIS_Axis)::DownCast(myShapes[2]);
  if (anAxis.IsNull()) anAxis = new AIS_Axis (myComponent,AIS_TOAX_YAxis);
  return anAxis;
}

//=======================================================================
//function : Axis
//purpose  : 
//=======================================================================
Handle(AIS_Axis) AIS_Trihedron::Axis() const 
{
  Handle(AIS_Axis) anAxis = Handle(AIS_Axis)::DownCast(myShapes[3]);
  if (anAxis.IsNull()) anAxis = new AIS_Axis (myComponent,AIS_TOAX_ZAxis);
  return anAxis;
}

//=======================================================================
//function : Position
//purpose  : 
//=======================================================================
Handle(AIS_Point) AIS_Trihedron::Position() const 
{
  Handle(AIS_Point) aPt = Handle(AIS_Point)::DownCast(myShapes[0]);
  if (aPt.IsNull()) {
    gp_Pnt aPnt = myComponent->Ax2().Location();
    Handle(Geom_Point) aPoint = new Geom_CartesianPoint(aPnt);
    aPt = new AIS_Point (aPoint);
  }
  return aPt;
}

//=======================================================================
//function : XYPlane
//purpose  : 
//=======================================================================
Handle(AIS_Plane) AIS_Trihedron::XYPlane() const 
{
  Handle(AIS_Plane) aPl = Handle(AIS_Plane)::DownCast(myShapes[4]);
  if (aPl.IsNull()) aPl = new AIS_Plane (myComponent,AIS_TOPL_XYPlane);
  return aPl;
}

//=======================================================================
//function : XZPlane
//purpose  : 
//=======================================================================
Handle(AIS_Plane) AIS_Trihedron::XZPlane() const 
{
  Handle(AIS_Plane) aPl = Handle(AIS_Plane)::DownCast(myShapes[5]);
  if (aPl.IsNull()) aPl = new AIS_Plane (myComponent,AIS_TOPL_XZPlane);
  return aPl;
}

//=======================================================================
//function : YZPlane
//purpose  : 
//=======================================================================
Handle(AIS_Plane) AIS_Trihedron::YZPlane() const 
{
  Handle(AIS_Plane) aPl = Handle(AIS_Plane)::DownCast(myShapes[6]);
  if (aPl.IsNull()) aPl = new AIS_Plane (myComponent,AIS_TOPL_YZPlane);
  return aPl;
}

//=======================================================================
//function : Compute
//purpose  : 
//=======================================================================
void AIS_Trihedron::Compute(
 const Handle(PrsMgr_PresentationManager3d)& /*aPresentationManager*/,
 const Handle(Prs3d_Presentation)& aPresentation, 
 const Standard_Integer aMode)
{
  aPresentation->Clear();

  aPresentation->SetInfiniteState (Standard_True);
  switch(aMode){
  case 0: 
    DsgPrs_DatumPrs::Add(aPresentation,myComponent->Ax2(),myDrawer);
    break;
  case 1:
    break;
  case 2:
    break;
  }
}

//=======================================================================
//function : Compute
//purpose  : 
//=======================================================================

void AIS_Trihedron::Compute(const Handle_Prs3d_Projector& aProjector,
                            const Handle_Geom_Transformation& aTransformation,
                            const Handle_Prs3d_Presentation& aPresentation)
{
// Standard_NotImplemented::Raise("AIS_Trihedron::Compute(const Handle_Prs3d_Projector&, const Handle_Geom_Transformation&, const Handle_Prs3d_Presentation&)");
 PrsMgr_PresentableObject::Compute( aProjector , aTransformation , aPresentation) ;
}

//=======================================================================
//function : ComputeSelection
//purpose  : 
//=======================================================================

void AIS_Trihedron::ComputeSelection(const Handle(SelectMgr_Selection)& aSelection,
                                     const Standard_Integer aMode)
{
  // retrieve the tops of the trihedron.
  Standard_Integer Prior, anIdx;
  Handle(SelectMgr_EntityOwner) eown;
  TColgp_Array1OfPnt PP(1,4),PO(1,4);
  ExtremityPoints(PP);

  // remove shapes from active selections
  Handle(AIS_InteractiveContext) anAISContext = GetContext();
  if (!anAISContext.IsNull())
    for (anIdx = 0; anIdx < 7; anIdx++)
    {
      // Deselect object
      if (anAISContext->IsSelected (myShapes[anIdx]))
        anAISContext->AddOrRemoveSelected (myShapes[anIdx], Standard_False);

      anAISContext->Remove (myShapes[anIdx], Standard_False);
    }
  
  switch (aMode) {
  case 0:
    {   // complete triedron only 1 owner : this... priority 5 (same as faces)
      Prior = 5;
      eown = new SelectMgr_EntityOwner(this,Prior);
      for (Standard_Integer i=1; i<=3;i++)
	aSelection->Add(new Select3D_SensitiveSegment(eown,PP(1),PP(i+1)));
      break;
    }
  case 1:
    {  //origin : 
      Prior = 8;
      eown= new SelectMgr_EntityOwner(myShapes[0],Prior);
      
      aSelection->Add(new Select3D_SensitivePoint (eown,myComponent->Location()));
      // If the trihedron's shapes display and selection modes are the same
      // the shapes are still displayed after selection, so we need to
      // use different presentation and hide it by nullifying
      if (!anAISContext.IsNull())
      {
        anAISContext->Display (myShapes[0], 1, 0, Standard_False);
        anAISContext->ClearPrs (myShapes[0], 1, Standard_False);
      }
      
      break;
    }
  case 2:
    {  //axes ... priority 7
      Prior = 7;
      for (Standard_Integer i=1; i<=3;i++){
	eown= new SelectMgr_EntityOwner(myShapes[i],Prior);
	aSelection->Add(new Select3D_SensitiveSegment(eown,PP(1),PP(i+1)));

      }

      // If the trihedron's shapes display and selection modes are the same
      // the shapes are still displayed after selection, so we need to
      // use different presentation and hide it by nullifying
      AIS_TypeOfAxis anAxisType;
      if (!anAISContext.IsNull())
        for (anIdx = 1; anIdx <= 3; anIdx++)
        {
          // update AIS_Axis for selection
          Handle(AIS_Axis) anAxis = Handle(AIS_Axis)::DownCast(myShapes[anIdx]);
          Handle(AIS_Drawer) aDrawer = anAxis->Attributes();
          Handle(Prs3d_DatumAspect) aDatum = myDrawer->DatumAspect();
          aDrawer->DatumAspect()->SetAxisLength (aDatum->FirstAxisLength(),
                                                 aDatum->SecondAxisLength(),
                                                 aDatum->ThirdAxisLength());
          anAxisType = anAxis->TypeOfAxis();
          anAxis->SetAxis2Placement (myComponent, anAxisType);

          // display
          anAISContext->Display (myShapes[anIdx], 1, 0, Standard_False);
          anAISContext->ClearPrs (myShapes[anIdx], 1, Standard_False);
        }
      
      break;
    }
    
  case 3:
    {  // main planes priority 6
//      PO(1) = PP(1);
//      PO(4) = PP(1);
      Prior =5;
      
      
      eown= new SelectMgr_EntityOwner(myShapes[4],Prior);
//      PO(2) = PP(2);PO(3) = PP(3);
      aSelection->Add(new Select3D_SensitiveTriangle(eown,PP(1),PP(2),PP(3)));

      eown= new SelectMgr_EntityOwner(myShapes[5],Prior);
//      PO(2) = PP(3);PO(3) = PP(4);
      aSelection->Add(new Select3D_SensitiveTriangle(eown,PP(1),PP(2),PP(4)));

      eown= new SelectMgr_EntityOwner(myShapes[6],Prior);
//      PO(2) = PP(4);PO(3) = PP(2);
      aSelection->Add(new Select3D_SensitiveTriangle(eown,PP(1),PP(3),PP(4)));
      
      // If the trihedron's shapes display and selection modes are the same
      // the shapes are still displayed after selection, so we need to
      // use different presentation and hide it by nullifying
      if (!anAISContext.IsNull())
        for (anIdx = 4; anIdx < 7; anIdx++)
	{
          anAISContext->Display (myShapes[anIdx], 1, 0, Standard_False);
          anAISContext->ClearPrs (myShapes[anIdx], 1, Standard_False);
        }
    }
  }
  
}

//=======================================================================
//function : SetColor
//purpose  : 
//=======================================================================

void AIS_Trihedron::SetColor(const Quantity_NameOfColor aCol)
{
  SetColor(Quantity_Color(aCol));
}

void AIS_Trihedron::SetColor(const Quantity_Color &aCol)
{
  hasOwnColor=Standard_True;
  myOwnColor = aCol;
  
  if(!myDrawer->HasDatumAspect()){
    Handle (Prs3d_DatumAspect) DA = new Prs3d_DatumAspect();
    
    DA->SetAxisLength(myDrawer->DatumAspect()->FirstAxisLength(),
		      myDrawer->DatumAspect()->SecondAxisLength(),
		      myDrawer->DatumAspect()->ThirdAxisLength());
    myDrawer->SetDatumAspect(DA);
  }
  myDrawer->DatumAspect()->FirstAxisAspect()->SetColor(aCol);
  myDrawer->DatumAspect()->SecondAxisAspect()->SetColor(aCol);
  myDrawer->DatumAspect()->ThirdAxisAspect()->SetColor(aCol);

}

//=======================================================================
//function : SetTextColor
//purpose  : 
//=======================================================================

#ifdef IMP120100
void AIS_Trihedron::SetTextColor(const Quantity_NameOfColor aCol)
{
  myHasOwnTextColor = Standard_True;
  myOwnTextColor = aCol;
  
  if(!myDrawer->HasDatumAspect()){
    Handle (Prs3d_DatumAspect) DA = new Prs3d_DatumAspect();
    
    DA->SetAxisLength(myDrawer->DatumAspect()->FirstAxisLength(),
		      myDrawer->DatumAspect()->SecondAxisLength(),
		      myDrawer->DatumAspect()->ThirdAxisLength());
    myDrawer->SetDatumAspect(DA);
  }
  Handle(Prs3d_TextAspect) aspect = myDrawer->TextAspect();
  aspect->SetColor(aCol);
  myDrawer->SetTextAspect(aspect);
}

void AIS_Trihedron::SetArrowColor(const Quantity_NameOfColor aCol)
{
  myHasOwnArrowColor = Standard_True;
  myOwnArrowColor = aCol;
  
  if(!myDrawer->HasDatumAspect()){
    Handle (Prs3d_DatumAspect) DA = new Prs3d_DatumAspect();
    
    DA->SetAxisLength(myDrawer->DatumAspect()->FirstAxisLength(),
		      myDrawer->DatumAspect()->SecondAxisLength(),
		      myDrawer->DatumAspect()->ThirdAxisLength());
    myDrawer->SetDatumAspect(DA);
  }
  Handle(Prs3d_ArrowAspect) aspect = myDrawer->ArrowAspect();
  aspect->SetColor(aCol);
  myDrawer->SetArrowAspect(aspect);
}

//=======================================================================
Standard_Boolean AIS_Trihedron::HasTextColor() const {

  return myHasOwnTextColor;
}

//=======================================================================
Quantity_NameOfColor AIS_Trihedron::TextColor() const {

  return myOwnTextColor;
}

//=======================================================================
Standard_Boolean AIS_Trihedron::HasArrowColor() const {

  return myHasOwnArrowColor;
}

//=======================================================================
Quantity_NameOfColor AIS_Trihedron::ArrowColor() const {

  return myOwnArrowColor;
}
#endif


//=======================================================================
//function : Compute
//purpose  : to avoid warning
//=======================================================================
void AIS_Trihedron::Compute(const Handle(Prs3d_Projector)&, 
			       const Handle(Prs3d_Presentation)&)
{
}
//=======================================================================
//function : Type
//purpose  : 
//=======================================================================

AIS_KindOfInteractive AIS_Trihedron::Type() const 
{return AIS_KOI_Datum;}


//=======================================================================
//function : Signature
//purpose  : 
//=======================================================================

 Standard_Integer AIS_Trihedron::Signature() const 
{return 3;}

//=======================================================================
//function : ExtremityPoints
//purpose  : to avoid warning
//=======================================================================
void  AIS_Trihedron::ExtremityPoints(TColgp_Array1OfPnt& PP) const 
{
  gp_Ax2 theax(myComponent->Ax2());
  PP(1) = theax.Location();

  Standard_Real len = myDrawer->DatumAspect()->FirstAxisLength();
  gp_Vec vec = theax.XDirection();
  vec *= len;
  PP(2) = PP(1).Translated(vec);
  
  len = myDrawer->DatumAspect()->SecondAxisLength();
  vec = theax.YDirection();
  vec *= len;
  PP(3) = PP(1).Translated(vec);

  len = myDrawer->DatumAspect()->ThirdAxisLength();
  vec = theax.Direction();
  vec *= len;
  PP(4) = PP(1).Translated(vec);
}

//=======================================================================
//function : AcceptDisplayMode
//purpose  : 
//=======================================================================

 Standard_Boolean  AIS_Trihedron::
AcceptDisplayMode(const Standard_Integer aMode) const
{return aMode == 0;}



//=======================================================================
//function : UnsetColor
//purpose  : 
//=======================================================================

void AIS_Trihedron::UnsetColor()
{
  hasOwnColor=Standard_False;
  myOwnColor = Quantity_NOC_LIGHTSTEELBLUE4;
  myDrawer->DatumAspect()->FirstAxisAspect()->SetColor(myOwnColor);
  myDrawer->DatumAspect()->SecondAxisAspect()->SetColor(myOwnColor);
  myDrawer->DatumAspect()->ThirdAxisAspect()->SetColor(myOwnColor);
#ifdef IMP120100
  if( HasTextColor() ) {
    SetTextColor(myOwnColor.Name());
    myHasOwnTextColor = Standard_False;
  }
  if( HasArrowColor() ) {
    SetArrowColor(myOwnColor.Name());
    myHasOwnArrowColor = Standard_False;
  }
#endif
  
}

//=======================================================================
//function : UnsetWitdth
//purpose  : 
//=======================================================================

void AIS_Trihedron::UnsetWidth()
{
  myOwnWidth =0.0;
  myDrawer->DatumAspect()->FirstAxisAspect()->SetWidth(1.);
  myDrawer->DatumAspect()->SecondAxisAspect()->SetWidth(1.);
  myDrawer->DatumAspect()->ThirdAxisAspect()->SetWidth(1.);

}
void AIS_Trihedron::LoadSubObjects()
{
  myShapes[0] = Position();
  myShapes[1] = XAxis();
  myShapes[2] = YAxis();
  myShapes[3] = Axis();
  myShapes[4] = XYPlane();
  myShapes[5] = XZPlane();
  myShapes[6] = YZPlane();
}

//=======================================================================
//function : SetContext
//purpose  : 
//=======================================================================

void AIS_Trihedron::SetContext(const Handle(AIS_InteractiveContext)& Ctx)
{
//  Standard_Boolean same_DA = myDrawer->Link() == Ctx->DefaultDrawer();

  // Remove subobjects from current context
  Handle(AIS_InteractiveContext) anAISContext = GetContext();
  Standard_Boolean hasContext = (anAISContext.IsNull() == Standard_False);
  Standard_Integer anIdx;
  for (anIdx = 0; anIdx < 7; anIdx++)
    {
      // Deselect object
      if (hasContext)
	{
	  if (anAISContext->IsSelected (myShapes[anIdx]))
	    anAISContext->AddOrRemoveSelected (myShapes[anIdx]);
	  
	  anAISContext->Remove (myShapes[anIdx], Standard_False);
	}
      myShapes[anIdx].Nullify();
    }

  AIS_InteractiveObject::SetContext (Ctx);
  
  LoadSubObjects();
  for(Standard_Integer i= 0;i<=6;i++)
    myShapes[i]->SetContext (Ctx);
}
