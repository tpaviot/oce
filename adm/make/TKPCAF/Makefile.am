# Makefile.am for Open Cascade toolkit TKPCAF
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/PDataXtd : @top_srcdir@/src/PDataXtd: \
@top_srcdir@/drv/PNaming : @top_srcdir@/src/PNaming: \
@top_srcdir@/drv/PPrsStd : @top_srcdir@/src/PPrsStd: \
@top_srcdir@/drv/MDataXtd : @top_srcdir@/src/MDataXtd: \
@top_srcdir@/drv/MPrsStd : @top_srcdir@/src/MPrsStd: \
@top_srcdir@/drv/MNaming : @top_srcdir@/src/MNaming


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/PDataXtd -I@top_srcdir@/src/PDataXtd \
-I@top_srcdir@/drv/PNaming -I@top_srcdir@/src/PNaming \
-I@top_srcdir@/drv/PPrsStd -I@top_srcdir@/src/PPrsStd \
-I@top_srcdir@/drv/MDataXtd -I@top_srcdir@/src/MDataXtd \
-I@top_srcdir@/drv/MPrsStd -I@top_srcdir@/src/MPrsStd \
-I@top_srcdir@/drv/MNaming -I@top_srcdir@/src/MNaming


lib_LTLIBRARIES=libTKPCAF.la

libTKPCAF_la_LIBADD = $(CSF_OPT_LIBS) \
../PTKernel/libPTKernel.la \
../TKBRep/libTKBRep.la \
../TKMath/libTKMath.la \
../TKernel/libTKernel.la \
../TKCDF/libTKCDF.la \
../TKG2d/libTKG2d.la \
../TKV3d/libTKV3d.la \
../TKService/libTKService.la \
../TKG3d/libTKG3d.la \
../TKV2d/libTKV2d.la \
../TKPShape/libTKPShape.la \
../TKCAF/libTKCAF.la \
../TKLCAF/libTKLCAF.la \
../TKPLCAF/libTKPLCAF.la


libTKPCAF_la_SOURCES = \
@top_srcdir@/drv/PNaming/PNaming_FieldOfHArray1OfNamedShape_0.cxx \
@top_srcdir@/drv/PNaming/PNaming_HArray1OfNamedShape_0.cxx \
@top_srcdir@/drv/PNaming/PNaming_VArrayNodeOfFieldOfHArray1OfNamedShape_0.cxx \
@top_srcdir@/drv/PNaming/PNaming_VArrayTNodeOfFieldOfHArray1OfNamedShape_0.cxx \
@top_srcdir@/src/MDataXtd/MDataXtd.cxx \
@top_srcdir@/src/MDataXtd/MDataXtd_AxisRetrievalDriver.cxx \
@top_srcdir@/src/MDataXtd/MDataXtd_AxisStorageDriver.cxx \
@top_srcdir@/src/MDataXtd/MDataXtd_ConstraintRetrievalDriver.cxx \
@top_srcdir@/src/MDataXtd/MDataXtd_ConstraintStorageDriver.cxx \
@top_srcdir@/src/MDataXtd/MDataXtd_GeometryRetrievalDriver.cxx \
@top_srcdir@/src/MDataXtd/MDataXtd_GeometryStorageDriver.cxx \
@top_srcdir@/src/MDataXtd/MDataXtd_PatternStdRetrievalDriver.cxx \
@top_srcdir@/src/MDataXtd/MDataXtd_PatternStdStorageDriver.cxx \
@top_srcdir@/src/MDataXtd/MDataXtd_PlacementRetrievalDriver.cxx \
@top_srcdir@/src/MDataXtd/MDataXtd_PlacementStorageDriver.cxx \
@top_srcdir@/src/MDataXtd/MDataXtd_PlaneRetrievalDriver.cxx \
@top_srcdir@/src/MDataXtd/MDataXtd_PlaneStorageDriver.cxx \
@top_srcdir@/src/MDataXtd/MDataXtd_PointRetrievalDriver.cxx \
@top_srcdir@/src/MDataXtd/MDataXtd_PointStorageDriver.cxx \
@top_srcdir@/src/MDataXtd/MDataXtd_ShapeRetrievalDriver.cxx \
@top_srcdir@/src/MDataXtd/MDataXtd_ShapeStorageDriver.cxx \
@top_srcdir@/src/MNaming/MNaming.cxx \
@top_srcdir@/src/MNaming/MNaming_NamedShapeRetrievalDriver.cxx \
@top_srcdir@/src/MNaming/MNaming_NamedShapeStorageDriver.cxx \
@top_srcdir@/src/MNaming/MNaming_NamingRetrievalDriver.cxx \
@top_srcdir@/src/MNaming/MNaming_NamingRetrievalDriver_1.cxx \
@top_srcdir@/src/MNaming/MNaming_NamingStorageDriver.cxx \
@top_srcdir@/src/MPrsStd/MPrsStd.cxx \
@top_srcdir@/src/MPrsStd/MPrsStd_AISPresentationRetrievalDriver.cxx \
@top_srcdir@/src/MPrsStd/MPrsStd_AISPresentationRetrievalDriver_1.cxx \
@top_srcdir@/src/MPrsStd/MPrsStd_AISPresentationStorageDriver.cxx \
@top_srcdir@/src/MPrsStd/MPrsStd_PositionRetrievalDriver.cxx \
@top_srcdir@/src/MPrsStd/MPrsStd_PositionStorageDriver.cxx \
@top_srcdir@/src/PDataXtd/PDataXtd_Axis.cxx \
@top_srcdir@/src/PDataXtd/PDataXtd_Constraint.cxx \
@top_srcdir@/src/PDataXtd/PDataXtd_Geometry.cxx \
@top_srcdir@/src/PDataXtd/PDataXtd_PatternStd.cxx \
@top_srcdir@/src/PDataXtd/PDataXtd_Placement.cxx \
@top_srcdir@/src/PDataXtd/PDataXtd_Plane.cxx \
@top_srcdir@/src/PDataXtd/PDataXtd_Point.cxx \
@top_srcdir@/src/PDataXtd/PDataXtd_Position.cxx \
@top_srcdir@/src/PDataXtd/PDataXtd_Shape.cxx \
@top_srcdir@/src/PNaming/PNaming_Name.cxx \
@top_srcdir@/src/PNaming/PNaming_Name_1.cxx \
@top_srcdir@/src/PNaming/PNaming_NamedShape.cxx \
@top_srcdir@/src/PNaming/PNaming_Naming.cxx \
@top_srcdir@/src/PNaming/PNaming_Naming_1.cxx \
@top_srcdir@/src/PPrsStd/PPrsStd_AISPresentation.cxx \
@top_srcdir@/src/PPrsStd/PPrsStd_AISPresentation_1.cxx

