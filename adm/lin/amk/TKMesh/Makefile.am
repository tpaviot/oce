# Makefile.am for Open Cascade toolkit TKMesh
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/BRepMesh : @top_srcdir@/src/BRepMesh


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES) $(CSF_TBB_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/BRepMesh -I@top_srcdir@/src/BRepMesh


lib_LTLIBRARIES=libTKMesh.la

libTKMesh_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKBRep/libTKBRep.la \
../TKMath/libTKMath.la \
../TKernel/libTKernel.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../TKGeomBase/libTKGeomBase.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKGeomAlgo/libTKGeomAlgo.la \
$(STLPort_LIB) $(CSF_TBB_LIB) 

libTKMesh_la_SOURCES = \
@top_srcdir@/src/BRepMesh/BRepMesh_CircleTool.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_Classifier.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_DataStructureOfDelaun.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_Delaun.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_DiscretFactory.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_DiscretRoot.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_EdgeParameterProvider.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_EdgeTessellationExtractor.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_EdgeTessellator.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_FaceAttribute.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_FastDiscret.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_FastDiscretFace.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_GeomTool.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_IEdgeTool.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_IncrementalMesh.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_SelectorOfDataStructureOfDelaun.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_ShapeTool.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_VertexTool.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_WireChecker.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_WireInterferenceChecker.cxx

