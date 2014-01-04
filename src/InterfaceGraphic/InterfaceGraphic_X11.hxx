// Copyright (c) 1991-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
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

#ifndef _WIN32
#ifndef InterfaceGraphic_X11Header
#define InterfaceGraphic_X11Header

#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <GL/glx.h>

// workaround name conflicts with OCCT methods (in class TopoDS_Shape for example)
#ifdef Convex
  #undef Convex
#endif
#ifdef Status
  #undef Status
#endif

#define WINDOW     Window
#define DISPLAY    Display
#define GLCONTEXT  GLXContext
#define GLDRAWABLE GLXDrawable

#define GET_GL_CONTEXT()       glXGetCurrentContext()
#define GET_GLDEV_CONTEXT()    glXGetCurrentDrawable()
#define GL_MAKE_CURRENT(a,b,c) glXMakeCurrent(a,b,c)

#ifndef EXPORT
  #define EXPORT
#endif  // EXPORT

#endif // InterfaceGraphic_X11Header
#endif // _WIN32
