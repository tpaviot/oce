// Created on: 2011-08-05
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

#include <OpenGl_GlCore11.hxx>

#include <OpenGl_Workspace.hxx>

#include <OpenGl_AspectLine.hxx>
#include <OpenGl_AspectFace.hxx>
#include <OpenGl_AspectMarker.hxx>
#include <OpenGl_AspectText.hxx>
#include <OpenGl_Context.hxx>
#include <OpenGl_ShaderManager.hxx>
#include <OpenGl_telem_util.hxx>

/* OCC22218 NOTE: project dependency on gl2ps is specified by macro */
#ifdef HAVE_GL2PS
  #include <gl2ps.h>
#endif

#include <Aspect_PolygonOffsetMode.hxx>
#include <OpenGl_View.hxx>

/*----------------------------------------------------------------------*/

static void TelUpdatePolygonOffsets (const TEL_POFFSET_PARAM& theOffsetData)
{
  if ((theOffsetData.mode & Aspect_POM_Fill) == Aspect_POM_Fill)
  {
    glEnable (GL_POLYGON_OFFSET_FILL);
  }
  else
  {
    glDisable (GL_POLYGON_OFFSET_FILL);
  }

#if !defined(GL_ES_VERSION_2_0)
  if ((theOffsetData.mode & Aspect_POM_Line) == Aspect_POM_Line)
  {
    glEnable (GL_POLYGON_OFFSET_LINE);
  }
  else
  {
    glDisable (GL_POLYGON_OFFSET_LINE);
  }

  if ((theOffsetData.mode & Aspect_POM_Point) == Aspect_POM_Point)
  {
    glEnable (GL_POLYGON_OFFSET_POINT);
  }
  else
  {
    glDisable (GL_POLYGON_OFFSET_POINT);
  }
#endif

  glPolygonOffset (theOffsetData.factor, theOffsetData.units);
}

/*----------------------------------------------------------------------*/

void OpenGl_Workspace::updateMaterial (const int theFlag)
{
  // Case of hidden line
  if (AspectFace_set->InteriorStyle() == Aspect_IS_HIDDENLINE)
  {
    myAspectFaceHl = *AspectFace_set; // copy all values including line edge aspect
    myAspectFaceHl.ChangeIntFront().matcol     = BackgroundColor();
    myAspectFaceHl.ChangeIntFront().color_mask = 0;
    myAspectFaceHl.ChangeIntFront().color_mask = 0;

    AspectFace_set = &myAspectFaceHl;
    return;
  }

  const OPENGL_SURF_PROP* aProps = &AspectFace_set->IntFront();
  GLenum aFace = GL_FRONT_AND_BACK;
  if (theFlag == TEL_BACK_MATERIAL)
  {
    aFace  = GL_BACK;
    aProps = &AspectFace_set->IntBack();
  }
  else if (AspectFace_set->DistinguishingMode() == TOn
        && !(NamedStatus & OPENGL_NS_RESMAT))
  {
    aFace = GL_FRONT;
  }

  myMatTmp.Init (*aProps);

  // handling transparency
  if (NamedStatus & OPENGL_NS_2NDPASSDO)
  {
    // second pass
    myMatTmp.Diffuse.a() = aProps->env_reflexion;
  }
  else
  {
    if (aProps->env_reflexion != 0.0f)
    {
      // if the material reflects the environment scene, the second pass is needed
      NamedStatus |= OPENGL_NS_2NDPASSNEED;
    }

    if (aProps->trans != 1.0f)
    {
      // render transparent
      myMatTmp.Diffuse.a() = aProps->trans;
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable    (GL_BLEND);
      glDepthMask (GL_FALSE);
    }
    else
    {
      // render opaque
      if ((NamedStatus & OPENGL_NS_ANTIALIASING) == 0)
      {
        glBlendFunc (GL_ONE, GL_ZERO);
        glDisable   (GL_BLEND);
      }
      glDepthMask (GL_TRUE);
    }
  }

  // do not update material properties in case of zero reflection mode,
  // because GL lighting will be disabled by OpenGl_PrimitiveArray::DrawArray() anyway.
  if (aProps->color_mask == 0)
  {
    return;
  }

  // reset material
  if (NamedStatus & OPENGL_NS_RESMAT)
  {
  #if !defined(GL_ES_VERSION_2_0)
    if (myGlContext->core11 != NULL)
    {
      myGlContext->core11->glMaterialfv (aFace, GL_AMBIENT,   myMatTmp.Ambient.GetData());
      myGlContext->core11->glMaterialfv (aFace, GL_DIFFUSE,   myMatTmp.Diffuse.GetData());
      myGlContext->core11->glMaterialfv (aFace, GL_SPECULAR,  myMatTmp.Specular.GetData());
      myGlContext->core11->glMaterialfv (aFace, GL_EMISSION,  myMatTmp.Emission.GetData());
      myGlContext->core11->glMaterialf  (aFace, GL_SHININESS, myMatTmp.Shine());
    }
  #endif

    if (theFlag == TEL_FRONT_MATERIAL)
    {
      myMatFront = myMatTmp;
      myMatBack  = myMatTmp;
    }
    else
    {
      myMatBack = myMatTmp;
    }

    NamedStatus &= ~OPENGL_NS_RESMAT;
    return;
  }

  // reduce updates
  OpenGl_Material& anOld = (theFlag == TEL_FRONT_MATERIAL)
                         ? myMatFront
                         : myMatBack;
#if !defined(GL_ES_VERSION_2_0)
  if (myGlContext->core11 != NULL)
  {
    if (myMatTmp.Ambient.r() != anOld.Ambient.r()
     || myMatTmp.Ambient.g() != anOld.Ambient.g()
     || myMatTmp.Ambient.b() != anOld.Ambient.b())
    {
      myGlContext->core11->glMaterialfv (aFace, GL_AMBIENT, myMatTmp.Ambient.GetData());
    }
    if (myMatTmp.Diffuse.r() != anOld.Diffuse.r()
     || myMatTmp.Diffuse.g() != anOld.Diffuse.g()
     || myMatTmp.Diffuse.b() != anOld.Diffuse.b()
     || fabs (myMatTmp.Diffuse.a() - anOld.Diffuse.a()) > 0.01f)
    {
      myGlContext->core11->glMaterialfv (aFace, GL_DIFFUSE, myMatTmp.Diffuse.GetData());
    }
    if (myMatTmp.Specular.r() != anOld.Specular.r()
     || myMatTmp.Specular.g() != anOld.Specular.g()
     || myMatTmp.Specular.b() != anOld.Specular.b())
    {
      myGlContext->core11->glMaterialfv (aFace, GL_SPECULAR, myMatTmp.Specular.GetData());
    }
    if (myMatTmp.Emission.r() != anOld.Emission.r()
     || myMatTmp.Emission.g() != anOld.Emission.g()
     || myMatTmp.Emission.b() != anOld.Emission.b())
    {
      myGlContext->core11->glMaterialfv (aFace, GL_EMISSION, myMatTmp.Emission.GetData());
    }
    if (myMatTmp.Shine() != anOld.Shine())
    {
      myGlContext->core11->glMaterialf (aFace, GL_SHININESS, myMatTmp.Shine());
    }
  }
#endif
  anOld = myMatTmp;
  if (aFace == GL_FRONT_AND_BACK)
  {
    myMatBack = myMatTmp;
  }
}

/*----------------------------------------------------------------------*/

const OpenGl_AspectLine * OpenGl_Workspace::SetAspectLine(const OpenGl_AspectLine *AnAspect)
{
  const OpenGl_AspectLine *AspectLine_old = AspectLine_set;
  AspectLine_set = AnAspect;
  return AspectLine_old;
}

/*----------------------------------------------------------------------*/

const OpenGl_AspectFace * OpenGl_Workspace::SetAspectFace(const OpenGl_AspectFace *AnAspect)
{
  const OpenGl_AspectFace *AspectFace_old = AspectFace_set;
  AspectFace_set = AnAspect;
  return AspectFace_old;
}

/*----------------------------------------------------------------------*/

const OpenGl_AspectMarker * OpenGl_Workspace::SetAspectMarker(const OpenGl_AspectMarker *AnAspect)
{
  const OpenGl_AspectMarker *AspectMarker_old = AspectMarker_set;
  AspectMarker_set = AnAspect;
  return AspectMarker_old;
}

/*----------------------------------------------------------------------*/

const OpenGl_AspectText * OpenGl_Workspace::SetAspectText(const OpenGl_AspectText *AnAspect)
{
  const OpenGl_AspectText *AspectText_old = AspectText_set;
  AspectText_set = AnAspect;
  return AspectText_old;
}

/*----------------------------------------------------------------------*/

const OpenGl_AspectLine * OpenGl_Workspace::AspectLine(const Standard_Boolean WithApply)
{
  if ( WithApply && (AspectLine_set != AspectLine_applied) )
  {
    myGlContext->SetColor4fv (*(const OpenGl_Vec4* )AspectLine_set->Color().rgb);
    if ( !AspectLine_applied || (AspectLine_set->Type() != AspectLine_applied->Type() ) )
    {
      myLineAttribs->SetTypeOfLine (AspectLine_set->Type());
    }

    if ( !AspectLine_applied || ( AspectLine_set->Width() != AspectLine_applied->Width() ) )
    {
      glLineWidth( (GLfloat)AspectLine_set->Width() );
#ifdef HAVE_GL2PS
      gl2psLineWidth( (GLfloat)AspectLine_set->Width() );
#endif
    }

    AspectLine_applied = AspectLine_set;
  }
  return AspectLine_set;
}

/*----------------------------------------------------------------------*/

const OpenGl_AspectFace* OpenGl_Workspace::AspectFace (const Standard_Boolean theToApply)
{
  if (!theToApply)
  {
    return AspectFace_set;
  }

  if (!ActiveView()->Backfacing())
  {
    // manage back face culling mode, disable culling when clipping is enabled
    TelCullMode aCullingMode = (myGlContext->Clipping().IsClippingOrCappingOn()
                             || AspectFace_set->InteriorStyle() == Aspect_IS_HATCH)
                             ? TelCullNone
                             : (TelCullMode )AspectFace_set->CullingMode();
    if (aCullingMode != TelCullNone
     && !(NamedStatus & OPENGL_NS_2NDPASSDO))
    {
      // disable culling in case of translucent shading aspect
      if (AspectFace_set->IntFront().trans != 1.0f)
      {
        aCullingMode = TelCullNone;
      }
    }
    if (myCullingMode != aCullingMode)
    {
      myCullingMode = aCullingMode;
      switch (myCullingMode)
      {
        case TelCullNone:
        case TelCullUndefined:
        {
          glDisable (GL_CULL_FACE);
          break;
        }
        case TelCullFront:
        {
          glCullFace (GL_FRONT);
          glEnable (GL_CULL_FACE);
          break;
        }
        case TelCullBack:
        {
          glCullFace (GL_BACK);
          glEnable (GL_CULL_FACE);
          break;
        }
      }
    }
  }

  if (AspectFace_set == AspectFace_applied)
  {
    return AspectFace_set;
  }

#if !defined(GL_ES_VERSION_2_0)
  const Aspect_InteriorStyle anIntstyle = AspectFace_set->InteriorStyle();
  if (AspectFace_applied == NULL || AspectFace_applied->InteriorStyle() != anIntstyle)
  {
    switch (anIntstyle)
    {
      case Aspect_IS_EMPTY:
      case Aspect_IS_HOLLOW:
      {
        glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
        break;
      }
      case Aspect_IS_HATCH:
      {
        glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
        myLineAttribs->SetTypeOfHatch (AspectFace_applied != NULL ? AspectFace_applied->Hatch() : TEL_HS_SOLID);
        break;
      }
      case Aspect_IS_SOLID:
      case Aspect_IS_HIDDENLINE:
      {
        glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
        if (myGlContext->core11 != NULL)
        {
          glDisable (GL_POLYGON_STIPPLE);
        }
        break;
      }
      case Aspect_IS_POINT:
      {
        glPolygonMode (GL_FRONT_AND_BACK, GL_POINT);
        break;
      }
    }
  }

  if (anIntstyle == Aspect_IS_HATCH)
  {
    const Tint hatchstyle = AspectFace_set->Hatch();
    if (AspectFace_applied == NULL || AspectFace_applied->Hatch() != hatchstyle)
    {
      myLineAttribs->SetTypeOfHatch (hatchstyle);
    }
  }
#endif

  // Aspect_POM_None means: do not change current settings
  if ((AspectFace_set->PolygonOffset().mode & Aspect_POM_None) != Aspect_POM_None)
  {
    if (PolygonOffset_applied.mode   != AspectFace_set->PolygonOffset().mode
     || PolygonOffset_applied.factor != AspectFace_set->PolygonOffset().factor
     || PolygonOffset_applied.units  != AspectFace_set->PolygonOffset().units)
    {
      SetPolygonOffset (AspectFace_set->PolygonOffset().mode,
                        AspectFace_set->PolygonOffset().factor,
                        AspectFace_set->PolygonOffset().units);
    }
  }

  updateMaterial (TEL_FRONT_MATERIAL);
  if (AspectFace_set->DistinguishingMode() == TOn)
  {
    updateMaterial (TEL_BACK_MATERIAL);
  }

  if ((NamedStatus & OPENGL_NS_FORBIDSETTEX) == 0)
  {
    if (AspectFace_set->DoTextureMap())
    {
      EnableTexture (AspectFace_set->TextureRes (myGlContext),
                     AspectFace_set->TextureParams());
    }
    else
    {
      DisableTexture();
    }
  }

  AspectFace_applied = AspectFace_set;
  return AspectFace_set;
}

//=======================================================================
//function : SetPolygonOffset
//purpose  :
//=======================================================================
void OpenGl_Workspace::SetPolygonOffset (int theMode,
                                         Standard_ShortReal theFactor,
                                         Standard_ShortReal theUnits)
{
  PolygonOffset_applied.mode   = theMode;
  PolygonOffset_applied.factor = theFactor;
  PolygonOffset_applied.units  = theUnits;

  TelUpdatePolygonOffsets (PolygonOffset_applied);
}

/*----------------------------------------------------------------------*/

const OpenGl_AspectMarker* OpenGl_Workspace::AspectMarker (const Standard_Boolean theToApply)
{
  if (theToApply && (AspectMarker_set != AspectMarker_applied))
  {
    if (!AspectMarker_applied || (AspectMarker_set->Scale() != AspectMarker_applied->Scale()))
    {
    #if !defined(GL_ES_VERSION_2_0)
      glPointSize (AspectMarker_set->Scale());
    #ifdef HAVE_GL2PS
      gl2psPointSize (AspectMarker_set->Scale());
    #endif
    #endif
    }
    AspectMarker_applied = AspectMarker_set;
  }
  return AspectMarker_set;
}

/*----------------------------------------------------------------------*/

const OpenGl_AspectText* OpenGl_Workspace::AspectText (const Standard_Boolean theWithApply)
{
  if (theWithApply)
  {
    AspectText_applied = AspectText_set;
    TextParam_applied  = TextParam_set;
  }

  return AspectText_set;
}
