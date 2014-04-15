// Created on: 2014-03-06
// Created by: Kirill GAVRILOV
// Copyright (c) -1999 Matra Datavision
// Copyright (c) 2014-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and / or modify it
// under the terms of the GNU Lesser General Public version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _OpenGl_GlCore12_H__
#define _OpenGl_GlCore12_H__

#include <oce-config.h>

#include <OpenGl_GlCore11.hxx>

// We can safely #undef GL_VERSION_x_y since redeclaration of typedef names can
// be done for same type: http://msdn.microsoft.com/en-us/library/87txds41.aspx
// It is required to fix build against Mesa >= 10:
// http://cgit.freedesktop.org/mesa/mesa/commit/?id=a36f7e6
#undef GL_VERSION_1_2
#undef GL_VERSION_1_3
#undef GL_VERSION_1_4
#undef GL_VERSION_1_5
#undef GL_VERSION_2_0

#include <OpenGl_glext.h>

//! Function list for GL1.2 core functionality.
struct OpenGl_GlCore12
{

  PFNGLBLENDCOLORPROC        glBlendColor;
  PFNGLBLENDEQUATIONPROC     glBlendEquation;
  PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements;
  PFNGLTEXIMAGE3DPROC        glTexImage3D;
  PFNGLTEXSUBIMAGE3DPROC     glTexSubImage3D;
  PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D;

};

#endif // _OpenGl_GlCore12_H__
