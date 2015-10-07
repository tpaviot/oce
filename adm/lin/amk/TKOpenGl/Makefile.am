# Makefile.am for Open Cascade toolkit TKOpenGl
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/OpenGl : @top_srcdir@/src/OpenGl


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES) $(CSF_OpenGlLibs_INCLUDES) $(CSF_objc_INCLUDES) $(CSF_Appkit_INCLUDES) $(CSF_IOKit_INCLUDES) $(CSF_FREETYPE_INCLUDES) $(CSF_GL2PS_INCLUDES) $(CSF_user32_INCLUDES) $(CSF_gdi32_INCLUDES) $(CSF_AviLibs_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/OpenGl -I@top_srcdir@/src/OpenGl


lib_LTLIBRARIES=libTKOpenGl.la

libTKOpenGl_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKernel/libTKernel.la \
../TKService/libTKService.la \
../TKMath/libTKMath.la \
../TKV3d/libTKV3d.la \
$(STLPort_LIB) $(CSF_OpenGlLibs_LIB) $(CSF_objc_LIB) $(CSF_Appkit_LIB) $(CSF_IOKit_LIB) $(CSF_FREETYPE_LIB) $(CSF_GL2PS_LIB) $(CSF_user32_LIB) $(CSF_gdi32_LIB) $(CSF_AviLibs_LIB) 

libTKOpenGl_la_SOURCES = \
@top_srcdir@/src/OpenGl/OpenGl_AVIWriter.cxx \
@top_srcdir@/src/OpenGl/OpenGl_AspectFace.cxx \
@top_srcdir@/src/OpenGl/OpenGl_AspectLine.cxx \
@top_srcdir@/src/OpenGl/OpenGl_AspectMarker.cxx \
@top_srcdir@/src/OpenGl/OpenGl_AspectText.cxx \
@top_srcdir@/src/OpenGl/OpenGl_BVHClipPrimitiveSet.cxx \
@top_srcdir@/src/OpenGl/OpenGl_BVHTreeSelector.cxx \
@top_srcdir@/src/OpenGl/OpenGl_BackgroundArray.cxx \
@top_srcdir@/src/OpenGl/OpenGl_CappingAlgo.cxx \
@top_srcdir@/src/OpenGl/OpenGl_CappingPlaneResource.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Caps.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Clipping.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Context.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Cylinder.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Disk.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Element.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Flipper.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Font.cxx \
@top_srcdir@/src/OpenGl/OpenGl_FrameBuffer.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraduatedTrihedron.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_4.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_7.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_713.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_Export.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_Layer.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Group.cxx \
@top_srcdir@/src/OpenGl/OpenGl_IndexBuffer.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Layer.cxx \
@top_srcdir@/src/OpenGl/OpenGl_LayerList.cxx \
@top_srcdir@/src/OpenGl/OpenGl_LineAttributes.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Matrix.cxx \
@top_srcdir@/src/OpenGl/OpenGl_PointSprite.cxx \
@top_srcdir@/src/OpenGl/OpenGl_PrimitiveArray.cxx \
@top_srcdir@/src/OpenGl/OpenGl_PrinterContext.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Quadric.cxx \
@top_srcdir@/src/OpenGl/OpenGl_RenderFilter.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Resource.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Sampler.cxx \
@top_srcdir@/src/OpenGl/OpenGl_SceneGeometry.cxx \
@top_srcdir@/src/OpenGl/OpenGl_ShaderManager.cxx \
@top_srcdir@/src/OpenGl/OpenGl_ShaderObject.cxx \
@top_srcdir@/src/OpenGl/OpenGl_ShaderProgram.cxx \
@top_srcdir@/src/OpenGl/OpenGl_ShaderStates.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Sphere.cxx \
@top_srcdir@/src/OpenGl/OpenGl_StencilTest.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Structure.cxx \
@top_srcdir@/src/OpenGl/OpenGl_StructureShadow.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Text.cxx \
@top_srcdir@/src/OpenGl/OpenGl_TextFormatter.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Texture.cxx \
@top_srcdir@/src/OpenGl/OpenGl_TextureBufferArb.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Trihedron.cxx \
@top_srcdir@/src/OpenGl/OpenGl_VertexBuffer.cxx \
@top_srcdir@/src/OpenGl/OpenGl_VertexBufferCompat.cxx \
@top_srcdir@/src/OpenGl/OpenGl_View.cxx \
@top_srcdir@/src/OpenGl/OpenGl_View_2.cxx \
@top_srcdir@/src/OpenGl/OpenGl_View_Raytrace.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Window.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Workspace.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Workspace_2.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Workspace_5.cxx \
@top_srcdir@/src/OpenGl/OpenGl_telem_util.cxx

