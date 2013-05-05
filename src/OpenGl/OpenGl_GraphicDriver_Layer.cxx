// Created on: 2011-10-20
// Created by: Sergey ZERCHANINOV
// Copyright (c) 2011-2012 OPEN CASCADE SAS
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

#include <OpenGl_GlCore11.hxx>

#include <OpenGl_GraphicDriver.hxx>

#include <Font_FontAspect.hxx>

#include <OpenGl_Display.hxx>
#include <OpenGl_AspectText.hxx>
#include <OpenGl_Text.hxx>
#include <OpenGl_TextParam.hxx>

/*----------------------------------------------------------------------*/

struct OpenGl_LAYER_PROP
{
  int        ListId;

  TEL_COLOUR Color;
  int        NbPoints;
  int        LineType;
  float      LineWidth;

  OpenGl_AspectText AspectText;
  OpenGl_TextParam TextParam;
};

/*----------------------------------------------------------------------*/

static const TEL_COLOUR myDefaultColor = {{ 1.F, 1.F, 1.F, 1.F }};
static const CALL_DEF_CONTEXTTEXT myDefaultContextText =
{
  1, //IsDef
  1, //IsSet
  "Courier", //Font
  0.3F, //Space
  1.F, //Expan
  { 1.F, 1.F, 1.F }, //Color
  (int)Aspect_TOST_NORMAL, //Style
  (int)Aspect_TODT_NORMAL, //DisplayType
  { 1.F, 1.F, 1.F }, //ColorSubTitle
  0, //TextZoomable
  0.F, //TextAngle
  (int)Font_FA_Regular //TextFontAspect
};

static Standard_Boolean TheLayerIsOpen = Standard_False;
static OpenGl_LAYER_PROP TheLayerProp;

/*----------------------------------------------------------------------*/

void InitLayerProp (const int AListId)
{
  TheLayerProp.ListId = AListId;

  if (AListId)
  {
    TheLayerProp.Color = myDefaultColor;
    TheLayerProp.NbPoints = 0;
    TheLayerProp.LineType = -1;
    TheLayerProp.LineWidth = -1.F;

    TheLayerProp.AspectText.SetContext(myDefaultContextText);

    TheLayerProp.TextParam.HAlign = Graphic3d_HTA_LEFT;
    TheLayerProp.TextParam.VAlign = Graphic3d_VTA_BOTTOM;
  }
}

/*----------------------------------------------------------------------*/

void OpenGl_GraphicDriver::Layer (Aspect_CLayer2d& ACLayer)
{
  ACLayer.ptrLayer = new CALL_DEF_PTRLAYER();
  ACLayer.ptrLayer->listIndex = glGenLists(1);
}

/*----------------------------------------------------------------------*/

void OpenGl_GraphicDriver::RemoveLayer (const Aspect_CLayer2d& ACLayer)
{
  if (!ACLayer.ptrLayer) return;
  if (!ACLayer.ptrLayer->listIndex) return;
  if (TheLayerProp.ListId == ACLayer.ptrLayer->listIndex)
    EndLayer();
  glDeleteLists (ACLayer.ptrLayer->listIndex, 1);
  ACLayer.ptrLayer->listIndex = 0;
  //szvgl: memory leak here?
  //free ( ACLayer.ptrLayer );
  //ACLayer.ptrLayer = NULL;
}

/*----------------------------------------------------------------------*/

void OpenGl_GraphicDriver::BeginLayer (const Aspect_CLayer2d& ACLayer)
{
  call_def_ptrLayer ptrLayer = (call_def_ptrLayer) ACLayer.ptrLayer;
  if (!ptrLayer) return;

  InitLayerProp(ptrLayer->listIndex);
  if (!TheLayerProp.ListId) return;

  glNewList (TheLayerProp.ListId, GL_COMPILE);
  TheLayerIsOpen = Standard_True;
}

void OpenGl_GraphicDriver::BeginPolygon2d ()
{
  if (!TheLayerProp.ListId) return;
  TheLayerProp.NbPoints = 0;
  glBegin (GL_POLYGON);
}

void OpenGl_GraphicDriver::BeginPolyline2d ()
{
  if (!TheLayerProp.ListId) return;
  TheLayerProp.NbPoints = 0;
  glBegin (GL_LINE_STRIP);
}

void OpenGl_GraphicDriver::ClearLayer (const Aspect_CLayer2d& ACLayer)
{
  if (!ACLayer.ptrLayer) return;

  InitLayerProp(ACLayer.ptrLayer->listIndex);
  if (!TheLayerProp.ListId) return;

  glNewList (TheLayerProp.ListId, GL_COMPILE);
  glEndList ();
}

void OpenGl_GraphicDriver::Draw (const Standard_ShortReal X, const Standard_ShortReal Y)
{
  if (!TheLayerProp.ListId) return;
  TheLayerProp.NbPoints++;
  glVertex3f (X, Y, 0.F);
}

void OpenGl_GraphicDriver::Edge (const Standard_ShortReal X, const Standard_ShortReal Y)
{
  if (!TheLayerProp.ListId) return;
  TheLayerProp.NbPoints++;
  glVertex3f (X, Y, 0.F);
}

void OpenGl_GraphicDriver::EndLayer ()
{
  if (!TheLayerProp.ListId) return;
  if (TheLayerIsOpen)
  {
    glEndList();
    TheLayerIsOpen = Standard_False;
  }
  TheLayerProp.ListId = 0;
}

void OpenGl_GraphicDriver::EndPolygon2d ()
{
  if (!TheLayerProp.ListId) return;
  glEnd ();
}

void OpenGl_GraphicDriver::EndPolyline2d ()
{
  if (!TheLayerProp.ListId) return;
  glEnd ();
}

void OpenGl_GraphicDriver::Move (const Standard_ShortReal X, const Standard_ShortReal Y)
{
  if (!TheLayerProp.ListId) return;
  if (TheLayerProp.NbPoints)
  {
    glEnd ();
    TheLayerProp.NbPoints = 0;
    glBegin (GL_LINE_STRIP);
  }
  TheLayerProp.NbPoints++;
  glVertex3f (X, Y, 0.F);
}

void OpenGl_GraphicDriver::Rectangle (const Standard_ShortReal X, const Standard_ShortReal Y, const Standard_ShortReal Width, const Standard_ShortReal Height)
{
  if (!TheLayerProp.ListId) return;
  glRectf (X, Y, X + Width, Y + Height);
}

void OpenGl_GraphicDriver::SetColor (const Standard_ShortReal R, const Standard_ShortReal G, const Standard_ShortReal B)
{
  if (!TheLayerProp.ListId) return;
  TheLayerProp.Color.rgb[0] = R;
  TheLayerProp.Color.rgb[1] = G;
  TheLayerProp.Color.rgb[2] = B;
  glColor3fv (TheLayerProp.Color.rgb);
}

void OpenGl_GraphicDriver::SetTransparency (const Standard_ShortReal ATransparency)
{
  if (!TheLayerProp.ListId) return;
  TheLayerProp.Color.rgb[3] = ATransparency;
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4fv (TheLayerProp.Color.rgb);
}

void OpenGl_GraphicDriver::UnsetTransparency ()
{
  if (!TheLayerProp.ListId) return;
  TheLayerProp.Color.rgb[3] = 1.F;
  glDisable (GL_BLEND);
}

void OpenGl_GraphicDriver::SetLineAttributes (const Standard_Integer Type, const Standard_ShortReal Width)
{
  if (!TheLayerProp.ListId || openglDisplay.IsNull()) return;

  if (TheLayerProp.LineType != Type)
  {
    TheLayerProp.LineType = Type;
    openglDisplay->SetTypeOfLine((Aspect_TypeOfLine) Type);
  }
  if (TheLayerProp.LineWidth != Width)
  {
    TheLayerProp.LineWidth = Width;
    glLineWidth ((GLfloat) Width);
  }
}

void OpenGl_GraphicDriver::SetTextAttributes (const Standard_CString   theFont,
                                              const Standard_Integer   theType,
                                              const Standard_ShortReal theR,
                                              const Standard_ShortReal theG,
                                              const Standard_ShortReal theB)
{
  if (!TheLayerProp.ListId)
  {
    return;
  }

  TheLayerProp.AspectText.ChangeFontName() = theFont;
  TheLayerProp.AspectText.SetDisplayType ((Aspect_TypeOfDisplayText )theType);
  TEL_COLOUR& aSubColor = TheLayerProp.AspectText.ChangeSubtitleColor();
  aSubColor.rgb[0] = (float )theR;
  aSubColor.rgb[1] = (float )theG;
  aSubColor.rgb[2] = (float )theB;
}

void OpenGl_GraphicDriver::Text (const Standard_CString   theText,
                                 const Standard_ShortReal theX,
                                 const Standard_ShortReal theY,
                                 const Standard_ShortReal theHeight)
{
  const Handle(OpenGl_Context)& aCtx = GetSharedContext();
  if (!TheLayerProp.ListId || aCtx.IsNull())
  {
    return;
  }

  const Standard_ShortReal aHeight = (theHeight < 2.0f) ? DefaultTextHeight() : theHeight;
  TheLayerProp.TextParam.Height = (int )aHeight;
  TheLayerProp.AspectText.ChangeColor() = TheLayerProp.Color;

  myTempText->Init (aCtx, TCollection_ExtendedString (theText), OpenGl_Vec2 (theX, theY), TheLayerProp.TextParam);
  myTempText->Render (myPrintContext, aCtx, TheLayerProp.AspectText);
  //myTempText->Release (aCtx);
}

void OpenGl_GraphicDriver::TextSize (const Standard_CString   theText,
                                     const Standard_ShortReal theHeight,
                                     Standard_ShortReal&      theWidth,
                                     Standard_ShortReal&      theAscent,
                                     Standard_ShortReal&      theDescent) const
{
  const Handle(OpenGl_Context)& aCtx = GetSharedContext();
  if (!TheLayerProp.ListId || aCtx.IsNull())
  {
    return;
  }

  const Standard_ShortReal aHeight = (theHeight < 2.0f) ? DefaultTextHeight() : theHeight;
  TheLayerProp.TextParam.Height = (int )aHeight;

  TCollection_ExtendedString anExtText = theText;
  NCollection_String aText = (Standard_Utf16Char* )anExtText.ToExtString();
  OpenGl_Text::StringSize (aCtx, aText, TheLayerProp.AspectText, TheLayerProp.TextParam, theWidth, theAscent, theDescent);
}
