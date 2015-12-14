// Created on: 2014-11-10
// Copyright (c) 2014 OPEN CASCADE SAS
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

#include <AIS_TextLabel.hxx>

#include <Graphic3d_AspectText3d.hxx>

#include <Prs3d_Text.hxx>
#include <Prs3d_TextAspect.hxx>

#include <Select3D_SensitivePoint.hxx>
#include <SelectMgr_Selection.hxx>
#include <SelectMgr_EntityOwner.hxx>

IMPLEMENT_STANDARD_HANDLE (AIS_TextLabel, AIS_InteractiveObject)
IMPLEMENT_STANDARD_RTTIEXT(AIS_TextLabel, AIS_InteractiveObject)

//=======================================================================
//function : AIS_TextLabel
//purpose  :
//=======================================================================
AIS_TextLabel::AIS_TextLabel()
: myText       ("?"),
  myPosition   (0.0, 0.0, 0.0),
  myFont       ("Courier"),
  myFontAspect (Font_FA_Regular)
{
  myDrawer->SetTextAspect (new Prs3d_TextAspect());

  SetDisplayMode (0);
}

//=======================================================================
//function : SetColor
//purpose  :
//=======================================================================
void AIS_TextLabel::SetColor (const Quantity_Color& theColor)
{
  hasOwnColor = Standard_True;
  myOwnColor  = theColor;
  myDrawer->TextAspect()->SetColor (theColor);
}

//=======================================================================
//function : SetColor
//purpose  :
//=======================================================================
void AIS_TextLabel::SetColor (const Quantity_NameOfColor theColor)
{
  SetColor (Quantity_Color (theColor));
}

//=======================================================================
//function : SetText
//purpose  :
//=======================================================================
void AIS_TextLabel::SetText (const TCollection_ExtendedString& theText)
{
  myText = theText;
}

//=======================================================================
//function : SetPosition
//purpose  :
//=======================================================================
void AIS_TextLabel::SetPosition (const gp_Pnt& thePosition)
{
  myPosition = thePosition;
}

//=======================================================================
//function : SetHJustification
//purpose  :
//=======================================================================
void AIS_TextLabel::SetHJustification (const Graphic3d_HorizontalTextAlignment theHJust)
{
  myDrawer->TextAspect()->SetHorizontalJustification (theHJust);
}

//=======================================================================
//function : SetVJustification
//purpose  : Setup vertical justification.
//=======================================================================
void AIS_TextLabel::SetVJustification (const Graphic3d_VerticalTextAlignment theVJust)
{
  myDrawer->TextAspect()->SetVerticalJustification (theVJust);
}

//=======================================================================
//function : SetAngle
//purpose  :
//=======================================================================
void AIS_TextLabel::SetAngle (const Standard_Real theAngle)
{
  myDrawer->TextAspect()->Aspect()->SetTextAngle (theAngle * 180.0 / M_PI);
}

//=======================================================================
//function : SetZoom
//purpose  :
//=======================================================================
void AIS_TextLabel::SetZoomable (const Standard_Boolean theIsZoomable)
{
  myDrawer->TextAspect()->Aspect()->SetTextZoomable (theIsZoomable);
}

//=======================================================================
//function : SetHeight
//purpose  :
//=======================================================================
void AIS_TextLabel::SetHeight (const Standard_Real theHeight)
{
  myDrawer->TextAspect()->SetHeight (theHeight);
}

//=======================================================================
//function : SetAngle
//purpose  :
//=======================================================================
void AIS_TextLabel::SetFontAspect (const Font_FontAspect theFontAspect)
{
  myDrawer->TextAspect()->Aspect()->SetTextFontAspect (theFontAspect);
}

//=======================================================================
//function : SetFont
//purpose  :
//=======================================================================
void AIS_TextLabel::SetFont (Standard_CString theFont)
{
  myFont = theFont;
  myDrawer->TextAspect()->SetFont (myFont.ToCString());
}

//=======================================================================
//function : Compute
//purpose  :
//=======================================================================
void AIS_TextLabel::Compute (const Handle(PrsMgr_PresentationManager3d)& /*thePrsMgr*/,
                             const Handle(Prs3d_Presentation)&             thePrs,
                             const Standard_Integer                        theMode)
{
  switch (theMode)
  {
    case 0:
    {
      Handle(Prs3d_TextAspect) anAsp = myDrawer->TextAspect();
      Prs3d_Text::Draw (thePrs, anAsp, myText, myPosition);
      break;
    }
  }
}

//=======================================================================
//function : ComputeSelection
//purpose  :
//=======================================================================
void AIS_TextLabel::ComputeSelection (const Handle(SelectMgr_Selection)& theSelection,
                                      const Standard_Integer             theMode)
{
  switch (theMode)
  {
    case 0:
    {
      Handle(SelectMgr_EntityOwner)   anEntityOwner   = new SelectMgr_EntityOwner (this, 10);
      Handle(Select3D_SensitivePoint) aSensitivePoint = new Select3D_SensitivePoint (anEntityOwner, myPosition);
      theSelection->Add (aSensitivePoint);
      break;
    }
  }
}
