# Makefile.am for Open Cascade toolkit TKDCAF
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/DDF : @top_srcdir@/src/DDF: \
@top_srcdir@/drv/DDocStd : @top_srcdir@/src/DDocStd: \
@top_srcdir@/drv/DNaming : @top_srcdir@/src/DNaming: \
@top_srcdir@/drv/DDataStd : @top_srcdir@/src/DDataStd: \
@top_srcdir@/drv/DPrsStd : @top_srcdir@/src/DPrsStd: \
@top_srcdir@/drv/DrawDim : @top_srcdir@/src/DrawDim


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/DDF -I@top_srcdir@/src/DDF \
-I@top_srcdir@/drv/DDocStd -I@top_srcdir@/src/DDocStd \
-I@top_srcdir@/drv/DNaming -I@top_srcdir@/src/DNaming \
-I@top_srcdir@/drv/DDataStd -I@top_srcdir@/src/DDataStd \
-I@top_srcdir@/drv/DPrsStd -I@top_srcdir@/src/DPrsStd \
-I@top_srcdir@/drv/DrawDim -I@top_srcdir@/src/DrawDim


lib_LTLIBRARIES=libTKDCAF.la

libTKDCAF_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKGeomBase/libTKGeomBase.la \
../TKBRep/libTKBRep.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../TKDraw/libTKDraw.la \
../TKCDF/libTKCDF.la \
../TKV3d/libTKV3d.la \
../TKNIS/libTKNIS.la \
../TKService/libTKService.la \
../TKLCAF/libTKLCAF.la \
../TKFillet/libTKFillet.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKPrim/libTKPrim.la \
../TKBool/libTKBool.la \
../TKBO/libTKBO.la \
../TKCAF/libTKCAF.la \
../TKViewerTest/libTKViewerTest.la \
$(STLPort_LIB) 

libTKDCAF_la_SOURCES = \
@top_srcdir@/drv/DDF/DDF_StackIteratorOfTransactionStack_0.cxx \
@top_srcdir@/drv/DDF/DDF_StackNodeOfTransactionStack_0.cxx \
@top_srcdir@/drv/DDF/DDF_TransactionStack_0.cxx \
@top_srcdir@/drv/DNaming/DNaming_DataMapIteratorOfDataMapOfShapeOfName_0.cxx \
@top_srcdir@/drv/DNaming/DNaming_DataMapNodeOfDataMapOfShapeOfName_0.cxx \
@top_srcdir@/drv/DNaming/DNaming_DataMapOfShapeOfName_0.cxx \
@top_srcdir@/src/DDF/DDF.cxx \
@top_srcdir@/src/DDF/DDF_AttributeBrowser.cxx \
@top_srcdir@/src/DDF/DDF_BasicCommands.cxx \
@top_srcdir@/src/DDF/DDF_Browser.cxx \
@top_srcdir@/src/DDF/DDF_BrowserCommands.cxx \
@top_srcdir@/src/DDF/DDF_Data.cxx \
@top_srcdir@/src/DDF/DDF_DataCommands.cxx \
@top_srcdir@/src/DDF/DDF_IOStream.cxx \
@top_srcdir@/src/DDF/DDF_Transaction.cxx \
@top_srcdir@/src/DDF/DDF_TransactionCommands.cxx \
@top_srcdir@/src/DDataStd/DDataStd.cxx \
@top_srcdir@/src/DDataStd/DDataStd_BasicCommands.cxx \
@top_srcdir@/src/DDataStd/DDataStd_ConstraintCommands.cxx \
@top_srcdir@/src/DDataStd/DDataStd_DatumCommands.cxx \
@top_srcdir@/src/DDataStd/DDataStd_DrawDisplayCommands.cxx \
@top_srcdir@/src/DDataStd/DDataStd_DrawDriver.cxx \
@top_srcdir@/src/DDataStd/DDataStd_DrawPresentation.cxx \
@top_srcdir@/src/DDataStd/DDataStd_NameCommands.cxx \
@top_srcdir@/src/DDataStd/DDataStd_NamedShapeCommands.cxx \
@top_srcdir@/src/DDataStd/DDataStd_ObjectCommands.cxx \
@top_srcdir@/src/DDataStd/DDataStd_TreeBrowser.cxx \
@top_srcdir@/src/DDataStd/DDataStd_TreeCommands.cxx \
@top_srcdir@/src/DDocStd/DDocStd.cxx \
@top_srcdir@/src/DDocStd/DDocStd_ApplicationCommands.cxx \
@top_srcdir@/src/DDocStd/DDocStd_DocumentCommands.cxx \
@top_srcdir@/src/DDocStd/DDocStd_DrawDocument.cxx \
@top_srcdir@/src/DDocStd/DDocStd_MTMCommands.cxx \
@top_srcdir@/src/DDocStd/DDocStd_ToolsCommands.cxx \
@top_srcdir@/src/DNaming/DNaming.cxx \
@top_srcdir@/src/DNaming/DNaming_BasicCommands.cxx \
@top_srcdir@/src/DNaming/DNaming_BooleanOperationDriver.cxx \
@top_srcdir@/src/DNaming/DNaming_BoxDriver.cxx \
@top_srcdir@/src/DNaming/DNaming_CylinderDriver.cxx \
@top_srcdir@/src/DNaming/DNaming_FilletDriver.cxx \
@top_srcdir@/src/DNaming/DNaming_Line3DDriver.cxx \
@top_srcdir@/src/DNaming/DNaming_ModelingCommands.cxx \
@top_srcdir@/src/DNaming/DNaming_PointDriver.cxx \
@top_srcdir@/src/DNaming/DNaming_PrismDriver.cxx \
@top_srcdir@/src/DNaming/DNaming_RevolutionDriver.cxx \
@top_srcdir@/src/DNaming/DNaming_SelectionCommands.cxx \
@top_srcdir@/src/DNaming/DNaming_SelectionDriver.cxx \
@top_srcdir@/src/DNaming/DNaming_SphereDriver.cxx \
@top_srcdir@/src/DNaming/DNaming_ToolsCommands.cxx \
@top_srcdir@/src/DNaming/DNaming_TransformationDriver.cxx \
@top_srcdir@/src/DPrsStd/DPrsStd.cxx \
@top_srcdir@/src/DPrsStd/DPrsStd_AISPresentationCommands.cxx \
@top_srcdir@/src/DPrsStd/DPrsStd_AISViewerCommands.cxx \
@top_srcdir@/src/DrawDim/DrawDim.cxx \
@top_srcdir@/src/DrawDim/DrawDim_Angle.cxx \
@top_srcdir@/src/DrawDim/DrawDim_Dimension.cxx \
@top_srcdir@/src/DrawDim/DrawDim_Distance.cxx \
@top_srcdir@/src/DrawDim/DrawDim_PlanarAngle.cxx \
@top_srcdir@/src/DrawDim/DrawDim_PlanarDiameter.cxx \
@top_srcdir@/src/DrawDim/DrawDim_PlanarDimension.cxx \
@top_srcdir@/src/DrawDim/DrawDim_PlanarDimensionCommands.cxx \
@top_srcdir@/src/DrawDim/DrawDim_PlanarDistance.cxx \
@top_srcdir@/src/DrawDim/DrawDim_PlanarRadius.cxx \
@top_srcdir@/src/DrawDim/DrawDim_Radius.cxx

