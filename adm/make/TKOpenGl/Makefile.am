# Makefile.am for Open Cascade toolkit TKOpenGl
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/OpenGl : @top_srcdir@/src/OpenGl


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(CSF_OpenGlLibs_INCLUDES) $(CSF_FREETYPE_INCLUDES) $(CSF_FTGL_INCLUDES) $(CSF_GL2PS_INCLUDES) $(CSF_user32_INCLUDES) $(CSF_gdi32_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/OpenGl -I@top_srcdir@/src/OpenGl


lib_LTLIBRARIES=libTKOpenGl.la

libTKOpenGl_la_LIBADD = $(CSF_OPT_LIBS) \
../TKernel/libTKernel.la \
../TKService/libTKService.la \
../TKV3d/libTKV3d.la \
$(CSF_OpenGlLibs_LIB) $(CSF_FREETYPE_LIB) $(CSF_FTGL_LIB) $(CSF_GL2PS_LIB) $(CSF_user32_LIB) $(CSF_gdi32_LIB) 

libTKOpenGl_la_SOURCES = \
@top_srcdir@/src/OpenGl/OpenGl_AVIWriter.cxx \
@top_srcdir@/src/OpenGl/OpenGl_AspectFace.cxx \
@top_srcdir@/src/OpenGl/OpenGl_AspectLine.cxx \
@top_srcdir@/src/OpenGl/OpenGl_AspectMarker.cxx \
@top_srcdir@/src/OpenGl/OpenGl_AspectText.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Context.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Display.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Display_1.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Display_2.cxx \
@top_srcdir@/src/OpenGl/OpenGl_FontMgr.cxx \
@top_srcdir@/src/OpenGl/OpenGl_FrameBuffer.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraduatedTrihedron.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_1.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_2.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_3.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_4.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_7.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_703.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_705.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_710.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_713.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_8.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_9.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_Export.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_Layer.cxx \
@top_srcdir@/src/OpenGl/OpenGl_GraphicDriver_print.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Group.cxx \
@top_srcdir@/src/OpenGl/OpenGl_ImageBox.cxx \
@top_srcdir@/src/OpenGl/OpenGl_LayerList.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Marker.cxx \
@top_srcdir@/src/OpenGl/OpenGl_MarkerSet.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Matrix.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Polygon.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Polyline.cxx \
@top_srcdir@/src/OpenGl/OpenGl_PrimitiveArray.cxx \
@top_srcdir@/src/OpenGl/OpenGl_PrinterContext.cxx \
@top_srcdir@/src/OpenGl/OpenGl_PriorityList.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Resource.cxx \
@top_srcdir@/src/OpenGl/OpenGl_ResourceCleaner.cxx \
@top_srcdir@/src/OpenGl/OpenGl_ResourceTexture.cxx \
@top_srcdir@/src/OpenGl/OpenGl_ResourceVBO.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Structure.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Text.cxx \
@top_srcdir@/src/OpenGl/OpenGl_TextureBox.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Trihedron.cxx \
@top_srcdir@/src/OpenGl/OpenGl_View.cxx \
@top_srcdir@/src/OpenGl/OpenGl_View_1.cxx \
@top_srcdir@/src/OpenGl/OpenGl_View_2.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Window.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Workspace.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Workspace_1.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Workspace_2.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Workspace_3.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Workspace_4.cxx \
@top_srcdir@/src/OpenGl/OpenGl_Workspace_5.cxx \
@top_srcdir@/src/OpenGl/OpenGl_telem_util.cxx \
@top_srcdir@/src/OpenGl/OpenGl_telem_view.cxx

