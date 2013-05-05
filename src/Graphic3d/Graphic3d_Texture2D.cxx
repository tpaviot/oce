// Created on: 1997-07-28
// Created by: Pierre CHALAMET
// Copyright (c) 1997-1999 Matra Datavision
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

#include <Graphic3d_Texture2D.ixx>
#include <TCollection_AsciiString.hxx>

static const char *NameOfTexture_to_FileName[] =
{
  "2d_MatraDatavision.rgb",
  "2d_alienskin.rgb",
  "2d_blue_rock.rgb",
  "2d_bluewhite_paper.rgb",
  "2d_brushed.rgb",
  "2d_bubbles.rgb",
  "2d_bumps.rgb",
  "2d_cast.rgb",
  "2d_chipbd.rgb",
  "2d_clouds.rgb",
  "2d_flesh.rgb",
  "2d_floor.rgb",
  "2d_galvnisd.rgb",
  "2d_grass.rgb",
  "2d_aluminum.rgb",
  "2d_rock.rgb",
  "2d_knurl.rgb",
  "2d_maple.rgb",
  "2d_marble.rgb",
  "2d_mottled.rgb",
  "2d_rain.rgb"
};

// =======================================================================
// function : Graphic3d_Texture2D
// purpose  :
// =======================================================================
Graphic3d_Texture2D::Graphic3d_Texture2D (const TCollection_AsciiString& theFileName,
                                          const Graphic3d_TypeOfTexture  theType)
: Graphic3d_TextureMap (theFileName, theType),
  myName (Graphic3d_NOT_2D_UNKNOWN)
{
}

// =======================================================================
// function : Graphic3d_Texture2D
// purpose  :
// =======================================================================
Graphic3d_Texture2D::Graphic3d_Texture2D (const Graphic3d_NameOfTexture2D theNOT,
                                          const Graphic3d_TypeOfTexture   theType)
: Graphic3d_TextureMap (NameOfTexture_to_FileName[theNOT], theType),
  myName (theNOT)
{
  myPath.SetTrek (Graphic3d_TextureRoot::TexturesFolder());
  myTexId = TCollection_AsciiString ("Graphic3d_Texture2D_")
          + NameOfTexture_to_FileName[theNOT];
}

// =======================================================================
// function : NumberOfTextures
// purpose  :
// =======================================================================
Standard_Integer Graphic3d_Texture2D::NumberOfTextures()
{
  return sizeof(NameOfTexture_to_FileName)/sizeof(char*);
}

// =======================================================================
// function : Name
// purpose  :
// =======================================================================
Graphic3d_NameOfTexture2D Graphic3d_Texture2D::Name() const
{
  return myName;
}

// =======================================================================
// function : TextureName
// purpose  :
// =======================================================================
TCollection_AsciiString Graphic3d_Texture2D::TextureName (const Standard_Integer theRank)
{
  if (theRank < 1 || theRank > NumberOfTextures())
  {
    Standard_OutOfRange::Raise ("BAD index of texture");
  }

  TCollection_AsciiString aFileName (NameOfTexture_to_FileName[theRank - 1]);
  Standard_Integer i = aFileName.SearchFromEnd (".");
  return aFileName.SubString (4, i - 1);
}
