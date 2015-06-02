# Makefile.am for Open Cascade toolkit TKXSDRAW
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/XSDRAW : @top_srcdir@/src/XSDRAW: \
@top_srcdir@/drv/XSDRAWIGES : @top_srcdir@/src/XSDRAWIGES: \
@top_srcdir@/drv/XSDRAWSTEP : @top_srcdir@/src/XSDRAWSTEP: \
@top_srcdir@/drv/XSDRAWSTLVRML : @top_srcdir@/src/XSDRAWSTLVRML


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/XSDRAW -I@top_srcdir@/src/XSDRAW \
-I@top_srcdir@/drv/XSDRAWIGES -I@top_srcdir@/src/XSDRAWIGES \
-I@top_srcdir@/drv/XSDRAWSTEP -I@top_srcdir@/src/XSDRAWSTEP \
-I@top_srcdir@/drv/XSDRAWSTLVRML -I@top_srcdir@/src/XSDRAWSTLVRML


lib_LTLIBRARIES=libTKXSDRAW.la

libTKXSDRAW_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKBRep/libTKBRep.la \
../TKV3d/libTKV3d.la \
../TKMath/libTKMath.la \
../TKNIS/libTKNIS.la \
../TKernel/libTKernel.la \
../TKService/libTKService.la \
../TKXSBase/libTKXSBase.la \
../TKMeshVS/libTKMeshVS.la \
../TKG3d/libTKG3d.la \
../TKViewerTest/libTKViewerTest.la \
../TKG2d/libTKG2d.la \
../TKSTEPBase/libTKSTEPBase.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKGeomBase/libTKGeomBase.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKMesh/libTKMesh.la \
../TKDraw/libTKDraw.la \
../TKSTEP/libTKSTEP.la \
../TKIGES/libTKIGES.la \
../TKSTL/libTKSTL.la \
../TKVRML/libTKVRML.la \
$(STLPort_LIB) 

libTKXSDRAW_la_SOURCES = \
@top_srcdir@/drv/XSDRAWSTLVRML/XSDRAWSTLVRML_CoordsMap_0.cxx \
@top_srcdir@/drv/XSDRAWSTLVRML/XSDRAWSTLVRML_DataMapIteratorOfCoordsMap_0.cxx \
@top_srcdir@/drv/XSDRAWSTLVRML/XSDRAWSTLVRML_DataMapIteratorOfElemNodesMap_0.cxx \
@top_srcdir@/drv/XSDRAWSTLVRML/XSDRAWSTLVRML_DataMapNodeOfCoordsMap_0.cxx \
@top_srcdir@/drv/XSDRAWSTLVRML/XSDRAWSTLVRML_DataMapNodeOfElemNodesMap_0.cxx \
@top_srcdir@/drv/XSDRAWSTLVRML/XSDRAWSTLVRML_ElemNodesMap_0.cxx \
@top_srcdir@/src/XSDRAW/XSDRAW.cxx \
@top_srcdir@/src/XSDRAW/XSDRAW_Functions.cxx \
@top_srcdir@/src/XSDRAW/XSDRAW_Vars.cxx \
@top_srcdir@/src/XSDRAWIGES/XSDRAWIGES.cxx \
@top_srcdir@/src/XSDRAWSTEP/XSDRAWSTEP.cxx \
@top_srcdir@/src/XSDRAWSTLVRML/XSDRAWSTLVRML.cxx \
@top_srcdir@/src/XSDRAWSTLVRML/XSDRAWSTLVRML_DataSource.cxx \
@top_srcdir@/src/XSDRAWSTLVRML/XSDRAWSTLVRML_DataSource3D.cxx \
@top_srcdir@/src/XSDRAWSTLVRML/XSDRAWSTLVRML_DrawableMesh.cxx

