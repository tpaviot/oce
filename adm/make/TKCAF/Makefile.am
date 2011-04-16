# Makefile.am for Open Cascade toolkit TKCAF
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/TDataXtd : @top_srcdir@/src/TDataXtd: \
@top_srcdir@/drv/TNaming : @top_srcdir@/src/TNaming: \
@top_srcdir@/drv/TPrsStd : @top_srcdir@/src/TPrsStd: \
@top_srcdir@/drv/AppStd : @top_srcdir@/src/AppStd


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/TDataXtd -I@top_srcdir@/src/TDataXtd \
-I@top_srcdir@/drv/TNaming -I@top_srcdir@/src/TNaming \
-I@top_srcdir@/drv/TPrsStd -I@top_srcdir@/src/TPrsStd \
-I@top_srcdir@/drv/AppStd -I@top_srcdir@/src/AppStd


lib_LTLIBRARIES=libTKCAF.la

libTKCAF_la_LIBADD = \
../TKernel/libTKernel.la \
../TKLCAF/libTKLCAF.la \
../TKG3d/libTKG3d.la \
../TKGeomBase/libTKGeomBase.la \
../TKV3d/libTKV3d.la \
../TKService/libTKService.la \
../TKMath/libTKMath.la \
../TKCDF/libTKCDF.la \
../TKBRep/libTKBRep.la \
../TKG2d/libTKG2d.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKV2d/libTKV2d.la \
$(STLPort_LIB) 

libTKCAF_la_SOURCES = \
@top_srcdir@/drv/TDataXtd/TDataXtd_Array1OfTrsf_0.cxx \
@top_srcdir@/drv/TDataXtd/TDataXtd_HArray1OfTrsf_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_DataMapIteratorOfDataMapOfShapePtrRefShape_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_DataMapIteratorOfDataMapOfShapeShapesSet_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_DataMapNodeOfDataMapOfShapePtrRefShape_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_DataMapNodeOfDataMapOfShapeShapesSet_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_DataMapOfShapePtrRefShape_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_DataMapOfShapeShapesSet_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_ListIteratorOfListOfIndexedDataMapOfShapeListOfShape_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_ListIteratorOfListOfMapOfShape_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_ListIteratorOfListOfNamedShape_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_ListNodeOfListOfIndexedDataMapOfShapeListOfShape_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_ListNodeOfListOfMapOfShape_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_ListNodeOfListOfNamedShape_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_ListOfIndexedDataMapOfShapeListOfShape_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_ListOfMapOfShape_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_ListOfNamedShape_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_MapIteratorOfMapOfNamedShape_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_MapOfNamedShape_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_NamedShapeHasher_0.cxx \
@top_srcdir@/drv/TNaming/TNaming_StdMapNodeOfMapOfNamedShape_0.cxx \
@top_srcdir@/drv/TPrsStd/TPrsStd_DataMapIteratorOfDataMapOfGUIDDriver_0.cxx \
@top_srcdir@/drv/TPrsStd/TPrsStd_DataMapNodeOfDataMapOfGUIDDriver_0.cxx \
@top_srcdir@/drv/TPrsStd/TPrsStd_DataMapOfGUIDDriver_0.cxx \
@top_srcdir@/src/AppStd/AppStd_Application.cxx \
@top_srcdir@/src/TDataXtd/TDataXtd.cxx \
@top_srcdir@/src/TDataXtd/TDataXtd_Axis.cxx \
@top_srcdir@/src/TDataXtd/TDataXtd_Constraint.cxx \
@top_srcdir@/src/TDataXtd/TDataXtd_Geometry.cxx \
@top_srcdir@/src/TDataXtd/TDataXtd_Pattern.cxx \
@top_srcdir@/src/TDataXtd/TDataXtd_PatternStd.cxx \
@top_srcdir@/src/TDataXtd/TDataXtd_Placement.cxx \
@top_srcdir@/src/TDataXtd/TDataXtd_Plane.cxx \
@top_srcdir@/src/TDataXtd/TDataXtd_Point.cxx \
@top_srcdir@/src/TDataXtd/TDataXtd_Position.cxx \
@top_srcdir@/src/TDataXtd/TDataXtd_Shape.cxx \
@top_srcdir@/src/TNaming/TNaming.cxx \
@top_srcdir@/src/TNaming/TNaming_Builder.cxx \
@top_srcdir@/src/TNaming/TNaming_CopyShape.cxx \
@top_srcdir@/src/TNaming/TNaming_DeltaOnModification.cxx \
@top_srcdir@/src/TNaming/TNaming_DeltaOnRemoval.cxx \
@top_srcdir@/src/TNaming/TNaming_Identifier.cxx \
@top_srcdir@/src/TNaming/TNaming_Iterator.cxx \
@top_srcdir@/src/TNaming/TNaming_IteratorOnShapesSet.cxx \
@top_srcdir@/src/TNaming/TNaming_Localizer.cxx \
@top_srcdir@/src/TNaming/TNaming_Name.cxx \
@top_srcdir@/src/TNaming/TNaming_NamedShape.cxx \
@top_srcdir@/src/TNaming/TNaming_Naming.cxx \
@top_srcdir@/src/TNaming/TNaming_NamingTool.cxx \
@top_srcdir@/src/TNaming/TNaming_NewShapeIterator.cxx \
@top_srcdir@/src/TNaming/TNaming_OldShapeIterator.cxx \
@top_srcdir@/src/TNaming/TNaming_RefShape.cxx \
@top_srcdir@/src/TNaming/TNaming_SameShapeIterator.cxx \
@top_srcdir@/src/TNaming/TNaming_Scope.cxx \
@top_srcdir@/src/TNaming/TNaming_Selector.cxx \
@top_srcdir@/src/TNaming/TNaming_ShapesSet.cxx \
@top_srcdir@/src/TNaming/TNaming_Tool.cxx \
@top_srcdir@/src/TNaming/TNaming_TranslateTool.cxx \
@top_srcdir@/src/TNaming/TNaming_Translator.cxx \
@top_srcdir@/src/TNaming/TNaming_UsedShapes.cxx \
@top_srcdir@/src/TPrsStd/TPrsStd_AISPresentation.cxx \
@top_srcdir@/src/TPrsStd/TPrsStd_AISViewer.cxx \
@top_srcdir@/src/TPrsStd/TPrsStd_AxisDriver.cxx \
@top_srcdir@/src/TPrsStd/TPrsStd_ConstraintDriver.cxx \
@top_srcdir@/src/TPrsStd/TPrsStd_ConstraintTools.cxx \
@top_srcdir@/src/TPrsStd/TPrsStd_Driver.cxx \
@top_srcdir@/src/TPrsStd/TPrsStd_DriverTable.cxx \
@top_srcdir@/src/TPrsStd/TPrsStd_GeometryDriver.cxx \
@top_srcdir@/src/TPrsStd/TPrsStd_NamedShapeDriver.cxx \
@top_srcdir@/src/TPrsStd/TPrsStd_PlaneDriver.cxx \
@top_srcdir@/src/TPrsStd/TPrsStd_PointDriver.cxx

libTKCAF_laLDFLAGS = -version-info @oce_version_info@

