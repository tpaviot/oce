// Created on: 2011-08-01
// Created by: Sergey ZERCHANINOV
// Copyright (c) 2011-2014 OPEN CASCADE SAS
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

#include <OpenGl_Group.hxx>

#include <OpenGl_GraphicDriver.hxx>
#include <OpenGl_Flipper.hxx>
#include <OpenGl_PrimitiveArray.hxx>
#include <OpenGl_StencilTest.hxx>
#include <OpenGl_Structure.hxx>
#include <OpenGl_Text.hxx>
#include <OpenGl_Workspace.hxx>

#include <Graphic3d_ArrayOfPrimitives.hxx>
#include <Graphic3d_CUserDraw.hxx>
#include <Graphic3d_GroupDefinitionError.hxx>

IMPLEMENT_STANDARD_HANDLE (OpenGl_Group, Graphic3d_Group)
IMPLEMENT_STANDARD_RTTIEXT(OpenGl_Group, Graphic3d_Group)

// =======================================================================
// function : OpenGl_Group
// purpose  :
// =======================================================================
OpenGl_Group::OpenGl_Group (const Handle(Graphic3d_Structure)& theStruct)
: Graphic3d_Group (theStruct),
  myAspectLine(NULL),
  myAspectFace(NULL),
  myAspectMarker(NULL),
  myAspectText(NULL),
  myFirst(NULL),
  myLast(NULL),
  myIsRaytracable (Standard_False)
{
  Handle(OpenGl_Structure) aStruct = Handle(OpenGl_Structure)::DownCast (myStructure->CStructure());
  if (aStruct == NULL)
  {
    Graphic3d_GroupDefinitionError::Raise ("OpenGl_Group should be created by OpenGl_Structure!");
  }
}

// =======================================================================
// function : ~OpenGl_Group
// purpose  :
// =======================================================================
OpenGl_Group::~OpenGl_Group()
{
  Release (Handle(OpenGl_Context)());
}

// =======================================================================
// function : UpdateAspectLine
// purpose  :
// =======================================================================
void OpenGl_Group::UpdateAspectLine (const Standard_Boolean theIsGlobal)
{
  if (!ContextLine.IsDef)
  {
    return;
  }

  if (theIsGlobal || myFirst == NULL)
  {
    if (myAspectLine == NULL)
    {
      myAspectLine = new OpenGl_AspectLine();
    }
    myAspectLine->SetAspect (ContextLine);
  }
  else
  {
    OpenGl_AspectLine* anAspectLine = new OpenGl_AspectLine();
    anAspectLine->SetAspect (ContextLine);
    AddElement (anAspectLine);
  }
}

// =======================================================================
// function : UpdateAspectFace
// purpose  :
// =======================================================================
void OpenGl_Group::UpdateAspectFace (const Standard_Boolean theIsGlobal)
{
  if (!ContextFillArea.IsDef)
  {
    return;
  }

  if (theIsGlobal || myFirst == NULL)
  {
    if (myAspectFace == NULL)
    {
      myAspectFace = new OpenGl_AspectFace();
    }
    myAspectFace->SetAspect (ContextFillArea);
  }
  else
  {
    OpenGl_AspectFace* anAspectFace = new OpenGl_AspectFace();
    anAspectFace->SetAspect (ContextFillArea);
    AddElement (anAspectFace);
  }

  if (myIsRaytracable)
  {
    OpenGl_Structure* aStruct = GlStruct();
    if (aStruct != NULL)
    {
      aStruct->UpdateStateIfRaytracable (Standard_False);
    }
  }
}

// =======================================================================
// function : UpdateAspectMarker
// purpose  :
// =======================================================================
void OpenGl_Group::UpdateAspectMarker (const Standard_Boolean theIsGlobal)
{
  if (!ContextMarker.IsDef)
  {
    return;
  }

  if (theIsGlobal || myFirst == NULL)
  {
    if (myAspectMarker == NULL)
    {
      myAspectMarker = new OpenGl_AspectMarker();
    }
    myAspectMarker->SetAspect (ContextMarker);
  }
  else
  {
    OpenGl_AspectMarker* anAspectMarker = new OpenGl_AspectMarker();
    anAspectMarker->SetAspect (ContextMarker);
    AddElement (anAspectMarker);
  }
}

// =======================================================================
// function : UpdateAspectText
// purpose  :
// =======================================================================
void OpenGl_Group::UpdateAspectText (const Standard_Boolean theIsGlobal)
{
  if (!ContextText.IsDef)
  {
    return;
  }

  if (theIsGlobal || myFirst == NULL)
  {
    if (myAspectText == NULL)
    {
      myAspectText = new OpenGl_AspectText();
    }
    myAspectText->SetAspect (ContextText);
  }
  else
  {
    OpenGl_AspectText* anAspectText = new OpenGl_AspectText();
    anAspectText->SetAspect (ContextText);
    AddElement (anAspectText);
  }
}

// =======================================================================
// function : AddPrimitiveArray
// purpose  :
// =======================================================================
void OpenGl_Group::AddPrimitiveArray (const Graphic3d_TypeOfPrimitiveArray theType,
                                      const Handle(Graphic3d_IndexBuffer)& theIndices,
                                      const Handle(Graphic3d_Buffer)&      theAttribs,
                                      const Handle(Graphic3d_BoundBuffer)& theBounds,
                                      const Standard_Boolean               theToEvalMinMax)
{
  if (IsDeleted()
   || theAttribs.IsNull())
  {
    return;
  }

  OpenGl_Structure* aStruct = GlStruct();
  const OpenGl_GraphicDriver* aDriver = aStruct->GlDriver();

  OpenGl_PrimitiveArray* anArray = new OpenGl_PrimitiveArray (aDriver, theType, theIndices, theAttribs, theBounds);
  AddElement (anArray);

  Graphic3d_Group::AddPrimitiveArray (theType, theIndices, theAttribs, theBounds, theToEvalMinMax);
}

// =======================================================================
// function : Text
// purpose  :
// =======================================================================
void OpenGl_Group::Text (const Standard_CString                  theTextUtf,
                         const Graphic3d_Vertex&                 thePoint,
                         const Standard_Real                     theHeight,
                         const Quantity_PlaneAngle               theAngle,
                         const Graphic3d_TextPath                theTp,
                         const Graphic3d_HorizontalTextAlignment theHta,
                         const Graphic3d_VerticalTextAlignment   theVta,
                         const Standard_Boolean                  theToEvalMinMax)
{
  if (IsDeleted())
  {
    return;
  }

  OpenGl_TextParam  aParams;
  OpenGl_Structure* aStruct = GlStruct();
  aParams.Height = int ((theHeight < 2.0) ? aStruct->GlDriver()->DefaultTextHeight() : theHeight);
  aParams.HAlign = theHta;
  aParams.VAlign = theVta;
  const OpenGl_Vec3 aPoint (thePoint.X(), thePoint.Y(), thePoint.Z());
  OpenGl_Text* aText = new OpenGl_Text (theTextUtf, aPoint, aParams);
  AddElement (aText);
  Graphic3d_Group::Text (theTextUtf, thePoint, theHeight, theAngle,
                         theTp, theHta, theVta, theToEvalMinMax);
}

// =======================================================================
// function : UserDraw
// purpose  :
// =======================================================================
void OpenGl_Group::UserDraw (const Standard_Address theObject,
                             const Standard_Boolean theToEvalMinMax,
                             const Standard_Boolean theContainsFacet)
{
  if (IsDeleted())
  {
    return;
  }

  OpenGl_Structure* aStruct = GlStruct();
  if (aStruct->GlDriver()->UserDrawCallback() == NULL)
  {
    return;
  }

  Graphic3d_CUserDraw aUserDraw;
  aUserDraw.Data   = theObject;
  aUserDraw.Bounds = theToEvalMinMax ? &myBounds : NULL;
  OpenGl_Element* aUserDrawElem = aStruct->GlDriver()->UserDrawCallback()(&aUserDraw);
  if (aUserDrawElem != NULL)
  {
    AddElement (aUserDrawElem);
  }
  Graphic3d_Group::UserDraw (theObject, theToEvalMinMax, theContainsFacet);
}

// =======================================================================
// function : SetFlippingOptions
// purpose  :
// =======================================================================
void OpenGl_Group::SetFlippingOptions (const Standard_Boolean theIsEnabled,
                                       const gp_Ax2&          theRefPlane)
{
  OpenGl_Flipper* aFlipper = new OpenGl_Flipper (theRefPlane);
  aFlipper->SetOptions (theIsEnabled);
  AddElement (aFlipper);
}

// =======================================================================
// function : SetStencilTestOptions
// purpose  :
// =======================================================================
void OpenGl_Group::SetStencilTestOptions (const Standard_Boolean theIsEnabled)
{
  OpenGl_StencilTest* aStencilTest = new OpenGl_StencilTest();
  aStencilTest->SetOptions (theIsEnabled);
  AddElement (aStencilTest);
}

// =======================================================================
// function : AddElement
// purpose  :
// =======================================================================
void OpenGl_Group::AddElement (OpenGl_Element* theElem)
{
  OpenGl_ElementNode *aNode = new OpenGl_ElementNode();

  aNode->elem = theElem;
  aNode->next = NULL;
  (myLast? myLast->next : myFirst) = aNode;
  myLast = aNode;

  if (OpenGl_Raytrace::IsRaytracedElement (aNode))
  {
    myIsRaytracable = Standard_True;

    OpenGl_Structure* aStruct = GlStruct();
    if (aStruct != NULL)
    {
      aStruct->UpdateStateIfRaytracable (Standard_False);
    }
  }
}

// =======================================================================
// function : Render
// purpose  :
// =======================================================================
void OpenGl_Group::Render (const Handle(OpenGl_Workspace)& theWorkspace) const
{
  // Is rendering in ADD or IMMEDIATE mode?
  const Handle(OpenGl_RenderFilter)& aFilter = theWorkspace->GetRenderFilter();

  // Setup aspects
  const OpenGl_AspectLine*   aBackAspectLine   = theWorkspace->AspectLine   (Standard_False);
  const OpenGl_AspectFace*   aBackAspectFace   = theWorkspace->AspectFace   (Standard_False);
  const OpenGl_AspectMarker* aBackAspectMarker = theWorkspace->AspectMarker (Standard_False);
  const OpenGl_AspectText*   aBackAspectText   = theWorkspace->AspectText   (Standard_False);
  Standard_Boolean isLineSet   = myAspectLine   && myAspectLine->RenderFiltered (theWorkspace, aFilter);
  Standard_Boolean isFaceSet   = myAspectFace   && myAspectFace->RenderFiltered (theWorkspace, aFilter);
  Standard_Boolean isMarkerSet = myAspectMarker && myAspectMarker->RenderFiltered (theWorkspace, aFilter);
  Standard_Boolean isTextSet   = myAspectText   && myAspectText->RenderFiltered (theWorkspace, aFilter);

  // Render group elements
  for (OpenGl_ElementNode* aNodeIter = myFirst; aNodeIter != NULL; aNodeIter = aNodeIter->next)
  {
    aNodeIter->elem->RenderFiltered (theWorkspace, aFilter);
  }

  // Restore aspects
  if (isLineSet)
    theWorkspace->SetAspectLine (aBackAspectLine);
  if (isFaceSet)
    theWorkspace->SetAspectFace (aBackAspectFace);
  if (isMarkerSet)
    theWorkspace->SetAspectMarker (aBackAspectMarker);
  if (isTextSet)
    theWorkspace->SetAspectText (aBackAspectText);
}

// =======================================================================
// function : Clear
// purpose  :
// =======================================================================
void OpenGl_Group::Clear (const Standard_Boolean theToUpdateStructureMgr)
{
  if (IsDeleted())
  {
    return;
  }

  OpenGl_Structure* aStruct = GlStruct();
  const Handle(OpenGl_Context)& aCtx = aStruct->GlDriver()->GetSharedContext();

  Release (aCtx);
  Graphic3d_Group::Clear (theToUpdateStructureMgr);

  myIsRaytracable = Standard_False;
}

// =======================================================================
// function : Release
// purpose  :
// =======================================================================
void OpenGl_Group::Release (const Handle(OpenGl_Context)& theGlCtx)
{
  // Delete elements
  while (myFirst != NULL)
  {
    OpenGl_ElementNode* aNext = myFirst->next;
    OpenGl_Element::Destroy (theGlCtx.operator->(), myFirst->elem);
    delete myFirst;
    myFirst = aNext;
  }
  myLast = NULL;

  OpenGl_Element::Destroy (theGlCtx.operator->(), myAspectLine);
  OpenGl_Element::Destroy (theGlCtx.operator->(), myAspectFace);
  OpenGl_Element::Destroy (theGlCtx.operator->(), myAspectMarker);
  OpenGl_Element::Destroy (theGlCtx.operator->(), myAspectText);
}
