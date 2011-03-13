# Makefile.am for Open Cascade toolkit TKXSDRAW
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/SWDRAW : @top_srcdir@/src/SWDRAW: \
@top_srcdir@/drv/XSDRAW : @top_srcdir@/src/XSDRAW: \
@top_srcdir@/drv/XSDRAWIGES : @top_srcdir@/src/XSDRAWIGES: \
@top_srcdir@/drv/XSDRAWSTEP : @top_srcdir@/src/XSDRAWSTEP: \
@top_srcdir@/drv/XSDRAWSTLVRML : @top_srcdir@/src/XSDRAWSTLVRML


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/SWDRAW -I@top_srcdir@/src/SWDRAW \
-I@top_srcdir@/drv/XSDRAW -I@top_srcdir@/src/XSDRAW \
-I@top_srcdir@/drv/XSDRAWIGES -I@top_srcdir@/src/XSDRAWIGES \
-I@top_srcdir@/drv/XSDRAWSTEP -I@top_srcdir@/src/XSDRAWSTEP \
-I@top_srcdir@/drv/XSDRAWSTLVRML -I@top_srcdir@/src/XSDRAWSTLVRML


lib_LTLIBRARIES=libTKXSDRAW.la

libTKXSDRAW_la_LIBADD = \
../TKernel/libTKernel.la \
../TKXSBase/libTKXSBase.la \
../TKIGES/libTKIGES.la \
../TKVRML/libTKVRML.la \
../TKViewerTest/libTKViewerTest.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKShHealing/libTKShHealing.la \
../TKService/libTKService.la \
../TKSTL/libTKSTL.la \
../TKV3d/libTKV3d.la \
../TKMesh/libTKMesh.la \
../TKMath/libTKMath.la \
../TKBRep/libTKBRep.la \
../TKGeomBase/libTKGeomBase.la \
../TKDraw/libTKDraw.la \
../TKSTEPBase/libTKSTEPBase.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKSTEP/libTKSTEP.la \
../TKMeshVS/libTKMeshVS.la \
../TKNIS/libTKNIS.la \
../TKV2d/libTKV2d.la \
$(STLPort_LIB) 

libTKXSDRAW_la_SOURCES = \
@top_srcdir@/drv/XSDRAWSTLVRML/XSDRAWSTLVRML_CoordsMap_0.cxx \
@top_srcdir@/drv/XSDRAWSTLVRML/XSDRAWSTLVRML_DataMapIteratorOfCoordsMap_0.cxx \
@top_srcdir@/drv/XSDRAWSTLVRML/XSDRAWSTLVRML_DataMapIteratorOfElemNodesMap_0.cxx \
@top_srcdir@/drv/XSDRAWSTLVRML/XSDRAWSTLVRML_DataMapNodeOfCoordsMap_0.cxx \
@top_srcdir@/drv/XSDRAWSTLVRML/XSDRAWSTLVRML_DataMapNodeOfElemNodesMap_0.cxx \
@top_srcdir@/drv/XSDRAWSTLVRML/XSDRAWSTLVRML_ElemNodesMap_0.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ShapeAnalysis.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ShapeBuild.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ShapeConstruct.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ShapeCustom.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ShapeExtend.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ShapeFix.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ShapeProcess.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ShapeProcessAPI.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ShapeTool.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ShapeUpgrade.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ToVRML.cxx \
@top_srcdir@/src/XSDRAW/XSDRAW.cxx \
@top_srcdir@/src/XSDRAW/XSDRAW_Functions.cxx \
@top_srcdir@/src/XSDRAW/XSDRAW_Shape.cxx \
@top_srcdir@/src/XSDRAW/XSDRAW_Vars.cxx \
@top_srcdir@/src/XSDRAWIGES/XSDRAWIGES.cxx \
@top_srcdir@/src/XSDRAWSTEP/XSDRAWSTEP.cxx \
@top_srcdir@/src/XSDRAWSTLVRML/XSDRAWSTLVRML.cxx \
@top_srcdir@/src/XSDRAWSTLVRML/XSDRAWSTLVRML_DataSource.cxx \
@top_srcdir@/src/XSDRAWSTLVRML/XSDRAWSTLVRML_DrawableMesh.cxx

