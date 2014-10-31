# Makefile.am for Open Cascade toolkit TKViewerTest
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/ViewerTest : @top_srcdir@/src/ViewerTest


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES) $(CSF_TclLibs_INCLUDES) $(CSF_TclTkLibs_INCLUDES) $(CSF_user32_INCLUDES) $(CSF_gdi32_INCLUDES) $(CSF_OpenGlLibs_INCLUDES) $(CSF_objc_INCLUDES) $(CSF_Appkit_INCLUDES) $(CSF_IOKit_INCLUDES) $(CSF_FREETYPE_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/ViewerTest -I@top_srcdir@/src/ViewerTest


lib_LTLIBRARIES=libTKViewerTest.la

libTKViewerTest_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKGeomBase/libTKGeomBase.la \
../TKFillet/libTKFillet.la \
../TKBRep/libTKBRep.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKHLR/libTKHLR.la \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
../TKNIS/libTKNIS.la \
../TKService/libTKService.la \
../TKShHealing/libTKShHealing.la \
../TKBool/libTKBool.la \
../TKPrim/libTKPrim.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKG2d/libTKG2d.la \
../TKTopTest/libTKTopTest.la \
../TKG3d/libTKG3d.la \
../TKOffset/libTKOffset.la \
../TKVoxel/libTKVoxel.la \
../TKMesh/libTKMesh.la \
../TKV3d/libTKV3d.la \
../TKDraw/libTKDraw.la \
../TKOpenGl/libTKOpenGl.la \
$(STLPort_LIB) $(CSF_TclLibs_LIB) $(CSF_TclTkLibs_LIB) $(CSF_user32_LIB) $(CSF_gdi32_LIB) $(CSF_OpenGlLibs_LIB) $(CSF_objc_LIB) $(CSF_Appkit_LIB) $(CSF_IOKit_LIB) $(CSF_FREETYPE_LIB) 

libTKViewerTest_la_SOURCES = \
@top_srcdir@/drv/ViewerTest/ViewerTest_DoubleMapIteratorOfDoubleMapOfInteractiveAndName_0.cxx \
@top_srcdir@/drv/ViewerTest/ViewerTest_DoubleMapNodeOfDoubleMapOfInteractiveAndName_0.cxx \
@top_srcdir@/drv/ViewerTest/ViewerTest_DoubleMapOfInteractiveAndName_0.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_AutoUpdater.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_AviCommands.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_EventManager.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_FilletCommands.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_ObjectCommands.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_OpenGlCommands.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_RelationCommands.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_ViewerCommands.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_VoxelCommands.cxx

