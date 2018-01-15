// Created on: 2014-03-12
// Created by: Kirill GAVRILOV
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

#ifndef _Prs3d_PresentationShadow_HeaderFile
#define _Prs3d_PresentationShadow_HeaderFile

#include <Prs3d_Presentation.hxx>

//! Defines a "shadow" of existing presentation object with custom aspects.
class Prs3d_PresentationShadow : public Prs3d_Presentation
{

public:

  //! Constructs a shadow of existing presentation object.
  Standard_EXPORT Prs3d_PresentationShadow (const Handle(Graphic3d_StructureManager)& theViewer,
                                            const Handle(Prs3d_Presentation)&         thePrs);

private: 

  DEFINE_STANDARD_RTTI(Prs3d_PresentationShadow)

};

DEFINE_STANDARD_HANDLE(Prs3d_PresentationShadow, Prs3d_Presentation)

#endif // _Prs3d_PresentationShadow_HeaderFile
