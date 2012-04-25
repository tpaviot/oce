# Makefile.am for Open Cascade toolkit TKViewerTest
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/Viewer2dTest : @top_srcdir@/src/Viewer2dTest: \
@top_srcdir@/drv/ViewerTest : @top_srcdir@/src/ViewerTest


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(CSF_TclLibs_INCLUDES) $(CSF_TclTkLibs_INCLUDES) $(CSF_user32_INCLUDES) $(CSF_gdi32_INCLUDES) $(CSF_OpenGlLibs_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/Viewer2dTest -I@top_srcdir@/src/Viewer2dTest \
-I@top_srcdir@/drv/ViewerTest -I@top_srcdir@/src/ViewerTest


lib_LTLIBRARIES=libTKViewerTest.la

libTKViewerTest_la_LIBADD = $(CSF_OPT_LIBS) \
../TKGeomBase/libTKGeomBase.la \
../TKFillet/libTKFillet.la \
../TKBRep/libTKBRep.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKHLR/libTKHLR.la \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
../TKNIS/libTKNIS.la \
../TKService/libTKService.la \
../TKBool/libTKBool.la \
../TKPrim/libTKPrim.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKG2d/libTKG2d.la \
../TKTopTest/libTKTopTest.la \
../TKG3d/libTKG3d.la \
../TKOffset/libTKOffset.la \
../TKVoxel/libTKVoxel.la \
../TKMesh/libTKMesh.la \
../TKV2d/libTKV2d.la \
../TKV3d/libTKV3d.la \
../TKDraw/libTKDraw.la \
../TKOpenGl/libTKOpenGl.la \
$(CSF_TclLibs_LIB) $(CSF_TclTkLibs_LIB) $(CSF_user32_LIB) $(CSF_gdi32_LIB) $(CSF_OpenGlLibs_LIB) 

libTKViewerTest_la_SOURCES = \
@top_srcdir@/drv/Viewer2dTest/Viewer2dTest_DataMapIteratorOfDataMapOfText_0.cxx \
@top_srcdir@/drv/Viewer2dTest/Viewer2dTest_DataMapNodeOfDataMapOfText_0.cxx \
@top_srcdir@/drv/Viewer2dTest/Viewer2dTest_DataMapOfText_0.cxx \
@top_srcdir@/drv/Viewer2dTest/Viewer2dTest_DoubleMapIteratorOfDoubleMapOfInteractiveAndName_0.cxx \
@top_srcdir@/drv/Viewer2dTest/Viewer2dTest_DoubleMapNodeOfDoubleMapOfInteractiveAndName_0.cxx \
@top_srcdir@/drv/Viewer2dTest/Viewer2dTest_DoubleMapOfInteractiveAndName_0.cxx \
@top_srcdir@/drv/ViewerTest/ViewerTest_DoubleMapIteratorOfDoubleMapOfInteractiveAndName_0.cxx \
@top_srcdir@/drv/ViewerTest/ViewerTest_DoubleMapNodeOfDoubleMapOfInteractiveAndName_0.cxx \
@top_srcdir@/drv/ViewerTest/ViewerTest_DoubleMapOfInteractiveAndName_0.cxx \
@top_srcdir@/src/Viewer2dTest/Viewer2dTest.cxx \
@top_srcdir@/src/Viewer2dTest/Viewer2dTest_DisplayCommands.cxx \
@top_srcdir@/src/Viewer2dTest/Viewer2dTest_EventManager.cxx \
@top_srcdir@/src/Viewer2dTest/Viewer2dTest_GeneralCommands.cxx \
@top_srcdir@/src/Viewer2dTest/Viewer2dTest_ObjectCommands.cxx \
@top_srcdir@/src/Viewer2dTest/Viewer2dTest_ViewerCommands.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_AviCommands.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_EventManager.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_FilletCommands.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_ObjectCommands.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_OpenGlCommands.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_RelationCommands.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_Tool.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_ViewerCommands.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_VoxelCommands.cxx

