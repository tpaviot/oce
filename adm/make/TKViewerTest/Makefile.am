# Makefile.am for Open Cascade toolkit TKViewerTest
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/Viewer2dTest : @top_srcdir@/src/Viewer2dTest: \
@top_srcdir@/drv/ViewerTest : @top_srcdir@/src/ViewerTest


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES) $(CSF_TclLibs_INCLUDES) $(CSF_TclTkLibs_INCLUDES) $(CSF_user32_INCLUDES) $(CSF_gdi32_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/Viewer2dTest -I@top_srcdir@/src/Viewer2dTest \
-I@top_srcdir@/drv/ViewerTest -I@top_srcdir@/src/ViewerTest


lib_LTLIBRARIES=libTKViewerTest.la

libTKViewerTest_la_LIBADD = \
../TKernel/libTKernel.la \
../TKBool/libTKBool.la \
../TKV2d/libTKV2d.la \
../TKG2d/libTKG2d.la \
../TKOffset/libTKOffset.la \
../TKG3d/libTKG3d.la \
../TKGeomBase/libTKGeomBase.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKV3d/libTKV3d.la \
../TKService/libTKService.la \
../TKMath/libTKMath.la \
../TKBRep/libTKBRep.la \
../TKMesh/libTKMesh.la \
../TKOpenGl/libTKOpenGl.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKFillet/libTKFillet.la \
../TKTopTest/libTKTopTest.la \
../TKHLR/libTKHLR.la \
../TKDraw/libTKDraw.la \
../TKVoxel/libTKVoxel.la \
../TKNIS/libTKNIS.la \
../TKPrim/libTKPrim.la \
$(STLPort_LIB) $(CSF_TclLibs_LIB) $(CSF_TclTkLibs_LIB) $(CSF_user32_LIB) $(CSF_gdi32_LIB) 

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
@top_srcdir@/src/ViewerTest/ViewerTest_RelationCommands.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_Tool.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_ViewerCommands.cxx \
@top_srcdir@/src/ViewerTest/ViewerTest_VoxelCommands.cxx

