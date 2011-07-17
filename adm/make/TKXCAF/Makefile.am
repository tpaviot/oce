# Makefile.am for Open Cascade toolkit TKXCAF
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/XCAFApp : @top_srcdir@/src/XCAFApp: \
@top_srcdir@/drv/XCAFDoc : @top_srcdir@/src/XCAFDoc: \
@top_srcdir@/drv/XCAFPrs : @top_srcdir@/src/XCAFPrs


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/XCAFApp -I@top_srcdir@/src/XCAFApp \
-I@top_srcdir@/drv/XCAFDoc -I@top_srcdir@/src/XCAFDoc \
-I@top_srcdir@/drv/XCAFPrs -I@top_srcdir@/src/XCAFPrs


lib_LTLIBRARIES=libTKXCAF.la

libTKXCAF_la_LIBADD = \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
../TKService/libTKService.la \
../TKV3d/libTKV3d.la \
../TKLCAF/libTKLCAF.la \
../TKG2d/libTKG2d.la \
../TKCDF/libTKCDF.la \
../TKCAF/libTKCAF.la \
../TKBRep/libTKBRep.la \
../TKV2d/libTKV2d.la \
../TKG3d/libTKG3d.la \
../TKTopAlgo/libTKTopAlgo.la \
$(STLPort_LIB) 

libTKXCAF_la_SOURCES = \
@top_srcdir@/drv/XCAFDoc/XCAFDoc_DataMapIteratorOfDataMapOfShapeLabel_0.cxx \
@top_srcdir@/drv/XCAFDoc/XCAFDoc_DataMapNodeOfDataMapOfShapeLabel_0.cxx \
@top_srcdir@/drv/XCAFDoc/XCAFDoc_DataMapOfShapeLabel_0.cxx \
@top_srcdir@/drv/XCAFDoc/XCAFDoc_GraphNodeSequence_0.cxx \
@top_srcdir@/drv/XCAFDoc/XCAFDoc_SequenceNodeOfGraphNodeSequence_0.cxx \
@top_srcdir@/drv/XCAFPrs/XCAFPrs_DataMapIteratorOfDataMapOfShapeStyle_0.cxx \
@top_srcdir@/drv/XCAFPrs/XCAFPrs_DataMapIteratorOfDataMapOfStyleShape_0.cxx \
@top_srcdir@/drv/XCAFPrs/XCAFPrs_DataMapIteratorOfDataMapOfStyleTransient_0.cxx \
@top_srcdir@/drv/XCAFPrs/XCAFPrs_DataMapNodeOfDataMapOfShapeStyle_0.cxx \
@top_srcdir@/drv/XCAFPrs/XCAFPrs_DataMapNodeOfDataMapOfStyleShape_0.cxx \
@top_srcdir@/drv/XCAFPrs/XCAFPrs_DataMapNodeOfDataMapOfStyleTransient_0.cxx \
@top_srcdir@/drv/XCAFPrs/XCAFPrs_DataMapOfShapeStyle_0.cxx \
@top_srcdir@/drv/XCAFPrs/XCAFPrs_DataMapOfStyleShape_0.cxx \
@top_srcdir@/drv/XCAFPrs/XCAFPrs_DataMapOfStyleTransient_0.cxx \
@top_srcdir@/src/XCAFApp/XCAFApp_Application.cxx \
@top_srcdir@/src/XCAFDoc/XCAFDoc.cxx \
@top_srcdir@/src/XCAFDoc/XCAFDoc_Area.cxx \
@top_srcdir@/src/XCAFDoc/XCAFDoc_Centroid.cxx \
@top_srcdir@/src/XCAFDoc/XCAFDoc_Color.cxx \
@top_srcdir@/src/XCAFDoc/XCAFDoc_ColorTool.cxx \
@top_srcdir@/src/XCAFDoc/XCAFDoc_Datum.cxx \
@top_srcdir@/src/XCAFDoc/XCAFDoc_DimTol.cxx \
@top_srcdir@/src/XCAFDoc/XCAFDoc_DimTolTool.cxx \
@top_srcdir@/src/XCAFDoc/XCAFDoc_DocumentTool.cxx \
@top_srcdir@/src/XCAFDoc/XCAFDoc_GraphNode.cxx \
@top_srcdir@/src/XCAFDoc/XCAFDoc_LayerTool.cxx \
@top_srcdir@/src/XCAFDoc/XCAFDoc_Location.cxx \
@top_srcdir@/src/XCAFDoc/XCAFDoc_Material.cxx \
@top_srcdir@/src/XCAFDoc/XCAFDoc_MaterialTool.cxx \
@top_srcdir@/src/XCAFDoc/XCAFDoc_ShapeMapTool.cxx \
@top_srcdir@/src/XCAFDoc/XCAFDoc_ShapeTool.cxx \
@top_srcdir@/src/XCAFDoc/XCAFDoc_Volume.cxx \
@top_srcdir@/src/XCAFPrs/XCAFPrs.cxx \
@top_srcdir@/src/XCAFPrs/XCAFPrs_AISObject.cxx \
@top_srcdir@/src/XCAFPrs/XCAFPrs_Driver.cxx \
@top_srcdir@/src/XCAFPrs/XCAFPrs_Style.cxx

