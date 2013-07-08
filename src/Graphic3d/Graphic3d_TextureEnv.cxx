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

#include <Graphic3d_TextureEnv.ixx>
#include <Graphic3d_TypeOfTexture.hxx>
#include <Graphic3d_TypeOfTextureMode.hxx>
#include <Graphic3d_TextureParams.hxx>
#include <TCollection_AsciiString.hxx>

static const char *NameOfTexture_to_FileName[] =
{
  "env_clouds.rgb",
  "env_cv.rgb",
  "env_medit.rgb",
  "env_pearl.rgb",
  "env_sky1.rgb",
  "env_sky2.rgb",
  "env_lines.rgb",
  "env_road.rgb"
};

// =======================================================================
// function : Graphic3d_TextureEnv
// purpose  :
// =======================================================================
Graphic3d_TextureEnv::Graphic3d_TextureEnv (const TCollection_AsciiString& theFileName)
: Graphic3d_TextureRoot (theFileName, Graphic3d_TOT_2D_MIPMAP),
  myName (Graphic3d_NOT_ENV_UNKNOWN)
{
  myParams->SetFilter  (Graphic3d_TOTF_TRILINEAR);
  myParams->SetGenMode (Graphic3d_TOTM_SPHERE,
                        Graphic3d_Vec4 (1.0f, 0.0f, 0.0f, 0.0f),
                        Graphic3d_Vec4 (0.0f, 1.0f, 0.0f, 0.0f));
}

// =======================================================================
// function : Graphic3d_TextureEnv
// purpose  :
// =======================================================================
Graphic3d_TextureEnv::Graphic3d_TextureEnv (const Graphic3d_NameOfTextureEnv theNOT)
: Graphic3d_TextureRoot (NameOfTexture_to_FileName[theNOT], Graphic3d_TOT_2D_MIPMAP),
  myName (theNOT)
{
  myPath.SetTrek (Graphic3d_TextureRoot::TexturesFolder());
  myTexId = TCollection_AsciiString ("Graphic3d_TextureEnv_")
          + NameOfTexture_to_FileName[theNOT];

  myParams->SetFilter  (Graphic3d_TOTF_TRILINEAR);
  myParams->SetGenMode (Graphic3d_TOTM_SPHERE,
                        Graphic3d_Vec4 (1.0f, 0.0f, 0.0f, 0.0f),
                        Graphic3d_Vec4 (0.0f, 1.0f, 0.0f, 0.0f));
}

// =======================================================================
// function : Name
// purpose  :
// =======================================================================
Graphic3d_NameOfTextureEnv Graphic3d_TextureEnv::Name() const
{
  return myName;
}

// =======================================================================
// function : NumberOfTextures
// purpose  :
// =======================================================================
Standard_Integer Graphic3d_TextureEnv::NumberOfTextures()
{
  return sizeof(NameOfTexture_to_FileName)/sizeof(char*);
}

// =======================================================================
// function : TextureName
// purpose  :
// =======================================================================
TCollection_AsciiString Graphic3d_TextureEnv::TextureName (const Standard_Integer theRank)
{
  if(theRank < 1 || theRank > NumberOfTextures())
  {
	Standard_OutOfRange::Raise ("BAD index of texture");
  }

  TCollection_AsciiString aFileName (NameOfTexture_to_FileName[theRank - 1]);
  Standard_Integer i = aFileName.SearchFromEnd(".");
  return aFileName.SubString (5, i - 1);
}
