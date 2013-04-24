# Makefile.am for Open Cascade toolkit TKSTL
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/StlMesh : @top_srcdir@/src/StlMesh: \
@top_srcdir@/drv/StlAPI : @top_srcdir@/src/StlAPI: \
@top_srcdir@/drv/StlTransfer : @top_srcdir@/src/StlTransfer: \
@top_srcdir@/drv/RWStl : @top_srcdir@/src/RWStl


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/StlMesh -I@top_srcdir@/src/StlMesh \
-I@top_srcdir@/drv/StlAPI -I@top_srcdir@/src/StlAPI \
-I@top_srcdir@/drv/StlTransfer -I@top_srcdir@/src/StlTransfer \
-I@top_srcdir@/drv/RWStl -I@top_srcdir@/src/RWStl


lib_LTLIBRARIES=libTKSTL.la

libTKSTL_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
../TKBRep/libTKBRep.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../TKMesh/libTKMesh.la \
../TKTopAlgo/libTKTopAlgo.la \
$(STLPort_LIB) 

libTKSTL_la_SOURCES = \
@top_srcdir@/drv/StlMesh/StlMesh_SequenceNodeOfSequenceOfMeshDomain_0.cxx \
@top_srcdir@/drv/StlMesh/StlMesh_SequenceNodeOfSequenceOfMeshTriangle_0.cxx \
@top_srcdir@/drv/StlMesh/StlMesh_SequenceNodeOfSequenceOfMesh_0.cxx \
@top_srcdir@/drv/StlMesh/StlMesh_SequenceOfMeshDomain_0.cxx \
@top_srcdir@/drv/StlMesh/StlMesh_SequenceOfMeshTriangle_0.cxx \
@top_srcdir@/drv/StlMesh/StlMesh_SequenceOfMesh_0.cxx \
@top_srcdir@/src/RWStl/RWStl.cxx \
@top_srcdir@/src/StlAPI/StlAPI.cxx \
@top_srcdir@/src/StlAPI/StlAPI_Reader.cxx \
@top_srcdir@/src/StlAPI/StlAPI_Writer.cxx \
@top_srcdir@/src/StlMesh/StlMesh.cxx \
@top_srcdir@/src/StlMesh/StlMesh_Mesh.cxx \
@top_srcdir@/src/StlMesh/StlMesh_MeshDomain.cxx \
@top_srcdir@/src/StlMesh/StlMesh_MeshExplorer.cxx \
@top_srcdir@/src/StlMesh/StlMesh_MeshTriangle.cxx \
@top_srcdir@/src/StlTransfer/StlTransfer.cxx

