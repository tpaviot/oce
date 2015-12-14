// Created on: 2011-07-13
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

#include <Graphic3d_ShaderProgram.hxx>

#include <OpenGl_AspectLine.hxx>
#include <OpenGl_Context.hxx>
#include <OpenGl_ShaderManager.hxx>
#include <OpenGl_ShaderProgram.hxx>
#include <OpenGl_Workspace.hxx>

namespace
{
  static const TEL_COLOUR myDefaultColor = {{ 1.0F, 1.0F, 1.0F, 1.0F }};
  static const TCollection_AsciiString THE_EMPTY_KEY;
}

// =======================================================================
// function : OpenGl_AspectLine
// purpose  :
// =======================================================================
OpenGl_AspectLine::OpenGl_AspectLine ()
 : myColor(myDefaultColor),
   myType(Aspect_TOL_SOLID),
   myWidth(1.0F)
{}

// =======================================================================
// function : OpenGl_AspectLine
// purpose  :
// =======================================================================
OpenGl_AspectLine::OpenGl_AspectLine (const OpenGl_AspectLine &AnOther)
 : myColor(AnOther.myColor),
   myType(AnOther.myType),
   myWidth(AnOther.myWidth)
{}

// =======================================================================
// function : SetAspect
// purpose  :
// =======================================================================
void OpenGl_AspectLine::SetAspect (const CALL_DEF_CONTEXTLINE &theAspect)
{
  myColor.rgb[0] = (float) theAspect.Color.r;
  myColor.rgb[1] = (float) theAspect.Color.g;
  myColor.rgb[2] = (float) theAspect.Color.b;
  myColor.rgb[3] = 1.0f;
  myType = (Aspect_TypeOfLine) theAspect.LineType;
  myWidth = (float) theAspect.Width;

  // update resource bindings
  myShaderProgram = theAspect.ShaderProgram;

  const TCollection_AsciiString& aShaderKey = myShaderProgram.IsNull() ? THE_EMPTY_KEY : myShaderProgram->GetId();
  if (aShaderKey.IsEmpty() || myResources.ShaderProgramId != aShaderKey)
  {
    myResources.ResetShaderReadiness();
  }
}

// =======================================================================
// function : Render
// purpose  :
// =======================================================================
void OpenGl_AspectLine::Render (const Handle(OpenGl_Workspace) &theWorkspace) const
{
  theWorkspace->SetAspectLine (this);
}

// =======================================================================
// function : Release
// purpose  :
// =======================================================================
void OpenGl_AspectLine::Release (OpenGl_Context* theContext)
{
  if (!myResources.ShaderProgram.IsNull()
   && theContext)
  {
    theContext->ShaderManager()->Unregister (myResources.ShaderProgramId,
                                             myResources.ShaderProgram);
  }
  myResources.ShaderProgramId.Clear();
  myResources.ResetShaderReadiness();
}

// =======================================================================
// function : BuildShader
// purpose  :
// =======================================================================
void OpenGl_AspectLine::Resources::BuildShader (const Handle(OpenGl_Context)&          theCtx,
                                                const Handle(Graphic3d_ShaderProgram)& theShader)
{
  if (theCtx->core20fwd == NULL)
  {
    return;
  }

  // release old shader program resources
  if (!ShaderProgram.IsNull())
  {
    theCtx->ShaderManager()->Unregister (ShaderProgramId, ShaderProgram);
    ShaderProgramId.Clear();
    ShaderProgram.Nullify();
  }
  if (theShader.IsNull())
  {
    return;
  }

  theCtx->ShaderManager()->Create (theShader, ShaderProgramId, ShaderProgram);
}
