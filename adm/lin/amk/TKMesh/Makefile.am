# Makefile.am for Open Cascade toolkit TKMesh
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/BRepMesh : @top_srcdir@/src/BRepMesh: \
@top_srcdir@/drv/IntPoly : @top_srcdir@/src/IntPoly


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES) $(CSF_TBB_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/BRepMesh -I@top_srcdir@/src/BRepMesh \
-I@top_srcdir@/drv/IntPoly -I@top_srcdir@/src/IntPoly


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
@top_srcdir@/drv/BRepMesh/BRepMesh_Array1OfBiPoint_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_Array1OfVertexOfDelaun_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfFaceAttribute_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfIntegerListOfInteger_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfIntegerListOfXY_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfIntegerPnt_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfShapePairOfPolygon_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfShapeReal_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfVertexInteger_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfFaceAttribute_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfIntegerListOfInteger_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfIntegerListOfXY_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfIntegerPnt_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfShapePairOfPolygon_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfShapeReal_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfVertexInteger_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapOfFaceAttribute_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapOfIntegerListOfInteger_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapOfIntegerListOfXY_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapOfIntegerPnt_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapOfShapePairOfPolygon_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapOfShapeReal_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_DataMapOfVertexInteger_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_ElemHasherOfDataStructureOfDelaun_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_HArray1OfVertexOfDelaun_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_HeapSortIndexedVertexOfDelaun_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_HeapSortVertexOfDelaun_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_IDMapOfLinkOfDataStructureOfDelaun_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_IDMapOfNodeOfDataStructureOfDelaun_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_IMapOfElementOfDataStructureOfDelaun_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_IndexedDataMapNodeOfIDMapOfLinkOfDataStructureOfDelaun_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_IndexedDataMapNodeOfIDMapOfNodeOfDataStructureOfDelaun_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_IndexedMapNodeOfIMapOfElementOfDataStructureOfDelaun_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_IndexedMapNodeOfIndexedMapOfVertex_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_IndexedMapOfVertex_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_LinkHasherOfDataStructureOfDelaun_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_ListIteratorOfListOfVertex_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_ListIteratorOfListOfXY_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_ListNodeOfListOfVertex_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_ListNodeOfListOfXY_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_ListOfVertex_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_ListOfXY_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_NodeHasherOfDataStructureOfDelaun_0.cxx \
@top_srcdir@/drv/BRepMesh/BRepMesh_VertexHasher_0.cxx \
@top_srcdir@/drv/IntPoly/IntPoly_IndexedMapNodeOfIndexedMapOfPnt2d_0.cxx \
@top_srcdir@/drv/IntPoly/IntPoly_IndexedMapNodeOfIndexedMapOfPnt_0.cxx \
@top_srcdir@/drv/IntPoly/IntPoly_IndexedMapOfPnt2d_0.cxx \
@top_srcdir@/drv/IntPoly/IntPoly_IndexedMapOfPnt_0.cxx \
@top_srcdir@/drv/IntPoly/IntPoly_SequenceNodeOfSequenceOfSequenceOfPnt2d_0.cxx \
@top_srcdir@/drv/IntPoly/IntPoly_SequenceNodeOfSequenceOfSequenceOfPnt_0.cxx \
@top_srcdir@/drv/IntPoly/IntPoly_SequenceOfSequenceOfPnt2d_0.cxx \
@top_srcdir@/drv/IntPoly/IntPoly_SequenceOfSequenceOfPnt_0.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_BiPoint.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_Circ.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_CircleTool.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_Classifier.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_ComparatorOfIndexedVertexOfDelaun.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_ComparatorOfVertexOfDelaun.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_DataStructureOfDelaun.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_Delaun.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_DiscretFactory.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_DiscretRoot.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_Edge.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_FaceAttribute.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_FastDiscret.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_FastDiscretFace.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_GeomTool.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_IncrementalMesh.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_PairOfPolygon.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_SelectorOfDataStructureOfDelaun.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_ShapeTool.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_Triangle.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_Vertex.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_VertexInspector.cxx \
@top_srcdir@/src/BRepMesh/BRepMesh_VertexTool.cxx \
@top_srcdir@/src/IntPoly/IntPoly_PlaneSection.cxx \
@top_srcdir@/src/IntPoly/IntPoly_Pnt2dHasher.cxx \
@top_srcdir@/src/IntPoly/IntPoly_PntHasher.cxx \
@top_srcdir@/src/IntPoly/IntPoly_ShapeSection.cxx

