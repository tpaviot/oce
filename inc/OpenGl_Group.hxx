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

#ifndef _OpenGl_Group_Header
#define _OpenGl_Group_Header

#include <InterfaceGraphic_Graphic3d.hxx>
#include <Graphic3d_Group.hxx>
#include <Graphic3d_Structure.hxx>

#include <NCollection_List.hxx>
#include <OpenGl_AspectLine.hxx>
#include <OpenGl_AspectFace.hxx>
#include <OpenGl_AspectMarker.hxx>
#include <OpenGl_AspectText.hxx>
#include <OpenGl_Element.hxx>

class OpenGl_Group;
class OpenGl_Structure;

struct OpenGl_ElementNode
{
  OpenGl_Element*     elem;
  OpenGl_ElementNode* next;
  DEFINE_STANDARD_ALLOC
};

//! Implementation of low-level graphic group.
class OpenGl_Group : public Graphic3d_Group
{
public:

  //! Create empty group.
  //! Will throw exception if not created by OpenGl_Structure.
  Standard_EXPORT OpenGl_Group (const Handle(Graphic3d_Structure)& theStruct);

  Standard_EXPORT virtual void Clear (const Standard_Boolean theToUpdateStructureMgr);

  //! Update line aspect
  Standard_EXPORT virtual void UpdateAspectLine   (const Standard_Boolean theIsGlobal);

  //! Update fill aspect
  Standard_EXPORT virtual void UpdateAspectFace   (const Standard_Boolean theIsGlobal);

  //! Update marker aspect
  Standard_EXPORT virtual void UpdateAspectMarker (const Standard_Boolean theIsGlobal);

  //! Update text aspect
  Standard_EXPORT virtual void UpdateAspectText   (const Standard_Boolean theIsGlobal);

  //! Add primitive array element
  Standard_EXPORT virtual void AddPrimitiveArray (const Graphic3d_TypeOfPrimitiveArray theType,
                                                  const Handle(Graphic3d_IndexBuffer)& theIndices,
                                                  const Handle(Graphic3d_Buffer)&      theAttribs,
                                                  const Handle(Graphic3d_BoundBuffer)& theBounds,
                                                  const Standard_Boolean               theToEvalMinMax);

  //! Add text element
  Standard_EXPORT virtual void Text (const Standard_CString                  theTextUtf,
                                     const Graphic3d_Vertex&                 thePoint,
                                     const Standard_Real                     theHeight,
                                     const Quantity_PlaneAngle               theAngle,
                                     const Graphic3d_TextPath                theTp,
                                     const Graphic3d_HorizontalTextAlignment theHta,
                                     const Graphic3d_VerticalTextAlignment   theVta,
                                     const Standard_Boolean                  theToEvalMinMax);

  //! Add UserDraw element using obsolete API
  Standard_EXPORT virtual void UserDraw (const Standard_Address theObject,
                                         const Standard_Boolean theToEvalMinMax,
                                         const Standard_Boolean theContainsFacet);

  //! Add flipping element
  Standard_EXPORT virtual void SetFlippingOptions (const Standard_Boolean theIsEnabled,
                                                   const gp_Ax2&          theRefPlane);

  //! Add stencil test element
  Standard_EXPORT virtual void SetStencilTestOptions (const Standard_Boolean theIsEnabled);

public:

  OpenGl_Structure* GlStruct() const { return (OpenGl_Structure* )(myStructure->CStructure().operator->()); }

  Standard_EXPORT void AddElement (OpenGl_Element* theElem);

  Standard_EXPORT virtual void Render  (const Handle(OpenGl_Workspace)& theWorkspace) const;
  Standard_EXPORT virtual void Release (const Handle(OpenGl_Context)&   theGlCtx);

  //! Returns first OpenGL element node of the group.
  const OpenGl_ElementNode* FirstNode() const { return myFirst; }

  //! Returns OpenGL face aspect.
  const OpenGl_AspectFace* AspectFace() const { return myAspectFace; }

  //! Is the group ray-tracable (contains ray-tracable elements)?
  Standard_Boolean IsRaytracable() const { return myIsRaytracable; }

  //! Accessor to line aspect (to be removed)
  CALL_DEF_CONTEXTLINE& ChangeContextLine() { return ContextLine; }

protected:

  Standard_EXPORT virtual ~OpenGl_Group();

protected:

  OpenGl_AspectLine*     myAspectLine;
  OpenGl_AspectFace*     myAspectFace;
  OpenGl_AspectMarker*   myAspectMarker;
  OpenGl_AspectText*     myAspectText;

  OpenGl_ElementNode*    myFirst;
  OpenGl_ElementNode*    myLast;

  Standard_Boolean       myIsRaytracable;

public:

  DEFINE_STANDARD_RTTI(OpenGl_Group) // Type definition

};

DEFINE_STANDARD_HANDLE(OpenGl_Group, Graphic3d_Group)

#endif // _OpenGl_Group_Header
