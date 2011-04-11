# Makefile.am for Open Cascade toolkit TKVoxel
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/Voxel : @top_srcdir@/src/Voxel


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/Voxel -I@top_srcdir@/src/Voxel


lib_LTLIBRARIES=libTKVoxel.la

libTKVoxel_la_LIBADD = \
../TKMath/libTKMath.la \
../TKernel/libTKernel.la \
../TKService/libTKService.la \
../TKMesh/libTKMesh.la \
../TKV3d/libTKV3d.la \
../TKG2d/libTKG2d.la \
../TKV2d/libTKV2d.la \
../TKBRep/libTKBRep.la \
../TKGeomBase/libTKGeomBase.la \
../TKG3d/libTKG3d.la \
../TKTopAlgo/libTKTopAlgo.la \
$(STLPort_LIB) 

libTKVoxel_la_SOURCES = \
@top_srcdir@/src/Voxel/Voxel_BoolDS.cxx \
@top_srcdir@/src/Voxel/Voxel_BooleanOperation.cxx \
@top_srcdir@/src/Voxel/Voxel_CollisionDetection.cxx \
@top_srcdir@/src/Voxel/Voxel_ColorDS.cxx \
@top_srcdir@/src/Voxel/Voxel_DS.cxx \
@top_srcdir@/src/Voxel/Voxel_FastConverter.cxx \
@top_srcdir@/src/Voxel/Voxel_FloatDS.cxx \
@top_srcdir@/src/Voxel/Voxel_OctBoolDS.cxx \
@top_srcdir@/src/Voxel/Voxel_Prs.cxx \
@top_srcdir@/src/Voxel/Voxel_ROctBoolDS.cxx \
@top_srcdir@/src/Voxel/Voxel_Reader.cxx \
@top_srcdir@/src/Voxel/Voxel_Selector.cxx \
@top_srcdir@/src/Voxel/Voxel_SplitData.cxx \
@top_srcdir@/src/Voxel/Voxel_Writer.cxx

libTKVoxel_laLDFLAGS = -version-info @oce_version_info@

