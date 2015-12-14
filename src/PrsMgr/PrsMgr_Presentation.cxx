// Copyright (c) 1998-1999 Matra Datavision
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

#include <PrsMgr_Presentation.ixx>
#include <PrsMgr_PresentationManager.hxx>
#include <PrsMgr_Prs.hxx>
#include <PrsMgr_ModedPresentation.hxx>

#include <Graphic3d_Structure.hxx>
#include <Visual3d_View.hxx>
#include <Precision.hxx>

namespace
{
  enum BeforeHighlightState
  {
    State_Empty,
    State_Hidden,
    State_Visible
  };

  static BeforeHighlightState StructureState(const Handle(PrsMgr_Prs)& theStructure)
  {
    return !theStructure->IsDisplayed() ?
      State_Empty : !theStructure->IsVisible() ?
        State_Hidden : State_Visible;
  }
}

//=======================================================================
//function : PrsMgr_Presentation
//purpose  :
//=======================================================================
PrsMgr_Presentation::PrsMgr_Presentation (const Handle(PrsMgr_PresentationManager3d)& thePrsMgr,
                                          const Handle(PrsMgr_PresentableObject)&     thePrsObject)
: myPresentationManager  (thePrsMgr),
  myPresentableObject    (thePrsObject.operator->()),
  myMustBeUpdated        (Standard_False),
  myBeforeHighlightState (State_Empty)
{
  myStructure = new PrsMgr_Prs (thePrsMgr->StructureManager(),
                                this, thePrsObject->TypeOfPresentation3d());
  myStructure->SetOwner (myPresentableObject);
  myStructure->SetMutable (myPresentableObject->IsMutable());
}

//=======================================================================
//function : Display
//purpose  :
//=======================================================================
void PrsMgr_Presentation::Display()
{
  display (Standard_False);
  myBeforeHighlightState = State_Visible;
}

//=======================================================================
//function : display
//purpose  :
//=======================================================================
void PrsMgr_Presentation::display (const Standard_Boolean theIsHighlight)
{
  if (!myStructure->IsDisplayed())
  {
    myStructure->SetIsForHighlight (theIsHighlight);
    myStructure->Display();
  }
  else if (!myStructure->IsVisible())
  {
    SetVisible (Standard_True);
    myStructure->SetIsForHighlight (theIsHighlight);
  }
}

//=======================================================================
//function : Erase
//purpose  :
//=======================================================================
void PrsMgr_Presentation::Erase()
{
  if (myStructure.IsNull())
  {
    return;
  }

  // Erase structure from structure manager
  myStructure->Erase();
  myStructure->Clear();
  // Disconnect other structures
  myStructure->DisconnectAll (Graphic3d_TOC_DESCENDANT);
  // Clear groups and remove graphic structure
  myStructure.Nullify();
}

//=======================================================================
//function : SetVisible
//purpose  :
//=======================================================================
void PrsMgr_Presentation::SetVisible (const Standard_Boolean theValue)
{
  myStructure->SetVisible (theValue);
}

//=======================================================================
//function : Highlight
//purpose  :
//=======================================================================
void PrsMgr_Presentation::Highlight (const Aspect_TypeOfHighlightMethod theMethod,
                                     const Quantity_Color&              theColor)
{
  if (!IsHighlighted())
  {
    myBeforeHighlightState = StructureState (myStructure);
  }

  display (Standard_True);
  myStructure->Highlight (theMethod, theColor);
}

//=======================================================================
//function : Unhighlight
//purpose  :
//=======================================================================
void PrsMgr_Presentation::Unhighlight() const
{
  myStructure->UnHighlight();
  switch (myBeforeHighlightState)
  {
 case State_Visible:
    return;
 case State_Hidden:
    myStructure->SetVisible (Standard_False);
    break;
 case State_Empty:
    myStructure->Erase();
    break;
  }
}

//=======================================================================
//function : Clear
//purpose  :
//=======================================================================
void PrsMgr_Presentation::Clear()
{
  // This modification remove the contain of the structure:
  // Consequence:
  //    1. The memory zone of the group is reused
  //    2. The speed for animation is constant
  //myPresentableObject = NULL;
  SetUpdateStatus (Standard_True);
  if (myStructure.IsNull())
  {
    return;
  }

  myStructure->Clear (Standard_True);
  //  myStructure->Clear(Standard_False);
  myStructure->RemoveAll();
}

//=======================================================================
//function : IsDisplayed
//purpose  :
//=======================================================================
Standard_Boolean PrsMgr_Presentation::IsDisplayed() const
{
  return  myStructure->IsDisplayed()
      &&  myStructure->IsVisible();
}

//=======================================================================
//function : IsHighlighted
//purpose  :
//=======================================================================
Standard_Boolean PrsMgr_Presentation::IsHighlighted() const
{
  return myStructure->IsHighlighted();
}

//=======================================================================
//function : DisplayPriority
//purpose  :
//=======================================================================
Standard_Integer PrsMgr_Presentation::DisplayPriority() const
{
  return myStructure->DisplayPriority();
}

//=======================================================================
//function : SetDisplayPriority
//purpose  :
//=======================================================================
void PrsMgr_Presentation::SetDisplayPriority (const Standard_Integer theNewPrior)
{
  myStructure->SetDisplayPriority (theNewPrior);
}

//=======================================================================
//function : Connect
//purpose  :
//=======================================================================
void PrsMgr_Presentation::Connect (const Handle(PrsMgr_Presentation)& theOther) const
{
  myStructure->Connect (theOther->Presentation());
}

//=======================================================================
//function : Transform
//purpose  :
//=======================================================================
void PrsMgr_Presentation::Transform (const Handle(Geom_Transformation)& theTrsf) const
{
  myStructure->Transform (theTrsf);
}

//=======================================================================
//function : Place
//purpose  :
//=======================================================================
void PrsMgr_Presentation::Place (const Quantity_Length theX,
                                 const Quantity_Length theY,
                                 const Quantity_Length theZ) const
{
  myStructure->Place (theX, theY, theZ);
}

//=======================================================================
//function : Multiply
//purpose  :
//=======================================================================
void PrsMgr_Presentation::Multiply (const Handle(Geom_Transformation)& theTrsf) const
{
  myStructure->Multiply (theTrsf);
}

//=======================================================================
//function : Move
//purpose  :
//=======================================================================
void PrsMgr_Presentation::Move (const Quantity_Length theX,
                                const Quantity_Length theY,
                                const Quantity_Length theZ) const
{
  myStructure->Move (theX, theY, theZ);
}

//=======================================================================
//function : SetShadingAspect
//purpose  :
//=======================================================================
void PrsMgr_Presentation::SetShadingAspect (const Handle(Prs3d_ShadingAspect)& theShadingAspect) const
{
  myStructure->SetShadingAspect (theShadingAspect);
}

//=======================================================================
//function : Compute
//purpose  : Methods for hidden parts...
//=======================================================================
Handle(Graphic3d_Structure) PrsMgr_Presentation::Compute (const Handle(Graphic3d_DataStructureManager)& theProjector)
{
  Handle(Prs3d_Presentation) aPrs = new Prs3d_Presentation (myPresentationManager->StructureManager());
  myPresentableObject->Compute (Projector (theProjector), aPrs);
  return aPrs;
}

//=======================================================================
//function : Compute
//purpose  :
//=======================================================================
void PrsMgr_Presentation::Compute (const Handle(Graphic3d_Structure)& theStructure)
{
  Standard_Integer aDispMode = 0;
  Standard_Integer aPresentationsNumber = myPresentableObject->myPresentations.Length();
  for (Standard_Integer anIter = 1; anIter <= aPresentationsNumber; ++anIter)
  {
    const PrsMgr_ModedPresentation& aModedPresentation = myPresentableObject->myPresentations.Value (anIter);
    if (aModedPresentation.Presentation().operator->() == this)
    {
      aDispMode = aModedPresentation.Mode();
      break;
    }
  }

  Handle(Prs3d_Presentation) aPrs3d = Handle(Prs3d_Presentation)::DownCast (theStructure);
  myPresentableObject->Compute (myPresentationManager, aPrs3d, aDispMode);
}

//=======================================================================
//function : Compute
//purpose  :
//=======================================================================
void PrsMgr_Presentation::Compute (const Handle(Graphic3d_DataStructureManager)& theProjector,
                                   const Handle(Graphic3d_Structure)&            theStructToFill)
{
  theStructToFill->Clear();
  const Handle(Prs3d_Presentation)& aPrs = *((Handle(Prs3d_Presentation)* )&theStructToFill);
  myPresentableObject->Compute (Projector (theProjector), aPrs);
}

//=======================================================================
//function : Compute
//purpose  :
//=======================================================================
Handle(Graphic3d_Structure) PrsMgr_Presentation::Compute (const Handle(Graphic3d_DataStructureManager)& theProjector,
                                                          const Handle(Geom_Transformation)&            theTrsf)
{
  Handle(Prs3d_Presentation) aPrs3d = new Prs3d_Presentation (myPresentationManager->StructureManager());
  if (theTrsf->Form() == gp_Translation)
  {
    myPresentableObject->Compute (Projector (theProjector), aPrs3d);
    aPrs3d->Transform (theTrsf);
    return aPrs3d;
  }

  // waiting that something is done in gp_Trsf...rob
  for (Standard_Integer i = 1; i <= 3; ++i)
  {
    for (Standard_Integer j = 1; j <= 3; ++j)
    {
      if (i != j)
      {
        if (Abs (theTrsf->Value (i, j)) > Precision::Confusion())
        {
          myPresentableObject->Compute (Projector (theProjector), theTrsf, aPrs3d);
          return aPrs3d;
        }
      }
    }
  }

  myPresentableObject->Compute (Projector (theProjector), aPrs3d);
  aPrs3d->Transform (theTrsf);
  return aPrs3d;
}

//=======================================================================
//function : Compute
//purpose  :
//=======================================================================
void PrsMgr_Presentation::Compute (const Handle(Graphic3d_DataStructureManager)& theProjector,
                                   const Handle(Geom_Transformation)&            theTrsf,
                                   const Handle(Graphic3d_Structure)&            theStructToFill)
{
  // recompute HLR after transformation in all the case
  Handle(Prs3d_Presentation) aPrs = *((Handle(Prs3d_Presentation)*)&theStructToFill);
  theStructToFill->Clear();
  myPresentableObject->Compute (Projector (theProjector), theTrsf, aPrs);
}

//=======================================================================
//function : Projector
//purpose  :
//=======================================================================
Handle(Prs3d_Projector) PrsMgr_Presentation::Projector (const Handle(Graphic3d_DataStructureManager)& theProjector)
{
  const Handle(Graphic3d_Camera)& aCamera = Handle(Visual3d_View)::DownCast (theProjector)->Camera();
  const gp_Dir aDir = aCamera->Direction().Reversed();
  const gp_Pnt anAt = aCamera->Center();
  const gp_Dir anUp = aCamera->Up();
  Handle(Prs3d_Projector) aProj = new Prs3d_Projector (!aCamera->IsOrthographic(),
                                                       aCamera->Scale(),
                                                       aDir.X(), aDir.Y(), aDir.Z(),
                                                       anAt.X(), anAt.Y(), anAt.Z(),
                                                       anUp.X(), anUp.Y(), anUp.Z());
  return aProj;
}

//=======================================================================
//function : Destroy
//purpose  :
//=======================================================================
void PrsMgr_Presentation::Destroy()
{
  Erase();
}

//=======================================================================
//function : SetZLayer
//purpose  :
//=======================================================================
void PrsMgr_Presentation::SetZLayer (Standard_Integer theLayerId)
{
  myStructure->SetZLayer (theLayerId);
}

//=======================================================================
//function : GetZLayer
//purpose  :
//=======================================================================
Standard_Integer PrsMgr_Presentation::GetZLayer() const
{
  return myStructure->GetZLayer();
}
