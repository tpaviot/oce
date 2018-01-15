// Created on: 2014-03-17
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

#ifndef _OpenGl_GlCore43_Header
#define _OpenGl_GlCore43_Header

#include <OpenGl_GlCore42.hxx>

//! OpenGL 4.3 definition.
template<typename theBaseClass_t>
struct OpenGl_TmplCore43 : public theBaseClass_t
{

public: //! @name OpenGL 4.3 additives to 4.2

#if !defined(GL_ES_VERSION_2_0)

  using theBaseClass_t::glClearBufferData;
  using theBaseClass_t::glClearBufferSubData;
  using theBaseClass_t::glDispatchCompute;
  using theBaseClass_t::glDispatchComputeIndirect;
  using theBaseClass_t::glCopyImageSubData;
  using theBaseClass_t::glFramebufferParameteri;
  using theBaseClass_t::glGetFramebufferParameteriv;
  using theBaseClass_t::glGetInternalformati64v;
  using theBaseClass_t::glInvalidateTexSubImage;
  using theBaseClass_t::glInvalidateTexImage;
  using theBaseClass_t::glInvalidateBufferSubData;
  using theBaseClass_t::glInvalidateBufferData;
  using theBaseClass_t::glInvalidateFramebuffer;
  using theBaseClass_t::glInvalidateSubFramebuffer;
  using theBaseClass_t::glMultiDrawArraysIndirect;
  using theBaseClass_t::glMultiDrawElementsIndirect;
  using theBaseClass_t::glGetProgramInterfaceiv;
  using theBaseClass_t::glGetProgramResourceIndex;
  using theBaseClass_t::glGetProgramResourceName;
  using theBaseClass_t::glGetProgramResourceiv;
  using theBaseClass_t::glGetProgramResourceLocation;
  using theBaseClass_t::glGetProgramResourceLocationIndex;
  using theBaseClass_t::glShaderStorageBlockBinding;
  using theBaseClass_t::glTexBufferRange;
  using theBaseClass_t::glTexStorage2DMultisample;
  using theBaseClass_t::glTexStorage3DMultisample;
  using theBaseClass_t::glTextureView;
  using theBaseClass_t::glBindVertexBuffer;
  using theBaseClass_t::glVertexAttribFormat;
  using theBaseClass_t::glVertexAttribIFormat;
  using theBaseClass_t::glVertexAttribLFormat;
  using theBaseClass_t::glVertexAttribBinding;
  using theBaseClass_t::glVertexBindingDivisor;
  using theBaseClass_t::glDebugMessageControl;
  using theBaseClass_t::glDebugMessageInsert;
  using theBaseClass_t::glDebugMessageCallback;
  using theBaseClass_t::glGetDebugMessageLog;
  using theBaseClass_t::glPushDebugGroup;
  using theBaseClass_t::glPopDebugGroup;
  using theBaseClass_t::glObjectLabel;
  using theBaseClass_t::glGetObjectLabel;
  using theBaseClass_t::glObjectPtrLabel;
  using theBaseClass_t::glGetObjectPtrLabel;

#endif

};

//! OpenGL 4.3 compatibility profile.
typedef OpenGl_TmplCore43<OpenGl_GlCore42Back> OpenGl_GlCore43Back;

//! OpenGL 4.3 core profile.
typedef OpenGl_TmplCore43<OpenGl_GlCore42>     OpenGl_GlCore43;

#endif // _OpenGl_GlCore43_Header
