project(TKMesh)

if (WIN32)
  list( APPEND TKMesh_PRECOMPILED_DEFS "-D__BRepMesh_DLL" )
  list( APPEND TKMesh_PRECOMPILED_DEFS "-D__IntPoly_DLL" )
  string( REGEX REPLACE ";" " " TKMesh_PRECOMPILED_DEFS "${TKMesh_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKMesh_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKMesh_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKMesh_COMPILER_DIRECTORIES "../../../drv/BRepMesh" )
  list( APPEND TKMesh_COMPILER_DIRECTORIES "../../../src/BRepMesh" )
  list( APPEND TKMesh_COMPILER_DIRECTORIES "../../../drv/IntPoly" )
  list( APPEND TKMesh_COMPILER_DIRECTORIES "../../../src/IntPoly" )

if (WIN32)
else()
endif()

  list( APPEND TKMesh_USED_LIBS TKBRep )
  list( APPEND TKMesh_USED_LIBS TKMath )
  list( APPEND TKMesh_USED_LIBS TKernel )
  list( APPEND TKMesh_USED_LIBS TKG2d )
  list( APPEND TKMesh_USED_LIBS TKG3d )
  list( APPEND TKMesh_USED_LIBS TKGeomBase )
  list( APPEND TKMesh_USED_LIBS TKTopAlgo )
  list( APPEND TKMesh_USED_LIBS TKGeomAlgo )

if (WIN32)
elseif(APPLE)
  if(3RDPARTY_USE_TBB)
    list( APPEND TKMesh_USED_LIBS tbb )
  endif()
  if(3RDPARTY_USE_TBB)
    list( APPEND TKMesh_USED_LIBS tbbmalloc )
  endif()
else()
  if(3RDPARTY_USE_TBB)
    list( APPEND TKMesh_USED_LIBS tbb )
  endif()
  if(3RDPARTY_USE_TBB)
    list( APPEND TKMesh_USED_LIBS tbbmalloc )
  endif()
endif()

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_Array1OfBiPoint_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_Array1OfBiPoint_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_Array1OfVertexOfDelaun_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_Array1OfVertexOfDelaun_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfFaceAttribute_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfFaceAttribute_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfIntegerListOfInteger_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfIntegerListOfInteger_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfIntegerListOfXY_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfIntegerListOfXY_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfIntegerPnt_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfIntegerPnt_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfShapePairOfPolygon_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfShapePairOfPolygon_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfShapeReal_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfShapeReal_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfVertexInteger_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapIteratorOfDataMapOfVertexInteger_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfFaceAttribute_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfFaceAttribute_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfIntegerListOfInteger_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfIntegerListOfInteger_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfIntegerListOfXY_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfIntegerListOfXY_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfIntegerPnt_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfIntegerPnt_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfShapePairOfPolygon_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfShapePairOfPolygon_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfShapeReal_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfShapeReal_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfVertexInteger_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapNodeOfDataMapOfVertexInteger_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapOfFaceAttribute_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapOfFaceAttribute_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapOfIntegerListOfInteger_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapOfIntegerListOfInteger_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapOfIntegerListOfXY_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapOfIntegerListOfXY_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapOfIntegerPnt_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapOfIntegerPnt_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapOfShapePairOfPolygon_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapOfShapePairOfPolygon_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapOfShapeReal_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapOfShapeReal_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_DataMapOfVertexInteger_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_DataMapOfVertexInteger_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_ElemHasherOfDataStructureOfDelaun_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_ElemHasherOfDataStructureOfDelaun_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_HArray1OfVertexOfDelaun_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_HArray1OfVertexOfDelaun_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_HeapSortIndexedVertexOfDelaun_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_HeapSortIndexedVertexOfDelaun_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_HeapSortVertexOfDelaun_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_HeapSortVertexOfDelaun_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_IDMapOfLinkOfDataStructureOfDelaun_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_IDMapOfLinkOfDataStructureOfDelaun_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_IDMapOfNodeOfDataStructureOfDelaun_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_IDMapOfNodeOfDataStructureOfDelaun_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_IMapOfElementOfDataStructureOfDelaun_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_IMapOfElementOfDataStructureOfDelaun_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_IndexedDataMapNodeOfIDMapOfLinkOfDataStructureOfDelaun_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_IndexedDataMapNodeOfIDMapOfLinkOfDataStructureOfDelaun_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_IndexedDataMapNodeOfIDMapOfNodeOfDataStructureOfDelaun_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_IndexedDataMapNodeOfIDMapOfNodeOfDataStructureOfDelaun_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_IndexedMapNodeOfIMapOfElementOfDataStructureOfDelaun_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_IndexedMapNodeOfIMapOfElementOfDataStructureOfDelaun_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_IndexedMapNodeOfIndexedMapOfVertex_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_IndexedMapNodeOfIndexedMapOfVertex_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_IndexedMapOfVertex_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_IndexedMapOfVertex_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_LinkHasherOfDataStructureOfDelaun_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_LinkHasherOfDataStructureOfDelaun_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_ListIteratorOfListOfVertex_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_ListIteratorOfListOfVertex_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_ListIteratorOfListOfXY_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_ListIteratorOfListOfXY_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_ListNodeOfListOfVertex_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_ListNodeOfListOfVertex_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_ListNodeOfListOfXY_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_ListNodeOfListOfXY_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_ListOfVertex_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_ListOfVertex_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_ListOfXY_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_ListOfXY_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_NodeHasherOfDataStructureOfDelaun_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_NodeHasherOfDataStructureOfDelaun_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/BRepMesh/BRepMesh_VertexHasher_0.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../drv/BRepMesh/BRepMesh_VertexHasher_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_BiPoint.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_BiPoint.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_Circ.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_Circ.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_CircleTool.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_CircleTool.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_Classifier.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_Classifier.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_ComparatorOfIndexedVertexOfDelaun.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_ComparatorOfIndexedVertexOfDelaun.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_ComparatorOfVertexOfDelaun.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_ComparatorOfVertexOfDelaun.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_DataStructureOfDelaun.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_DataStructureOfDelaun.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_Delaun.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_Delaun.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_DiscretFactory.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_DiscretFactory.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_DiscretRoot.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_DiscretRoot.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_Edge.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_Edge.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_FaceAttribute.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_FaceAttribute.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_FastDiscret.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_FastDiscret.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_FastDiscretFace.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_FastDiscretFace.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_GeomTool.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_GeomTool.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_IncrementalMesh.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_IncrementalMesh.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_PairOfPolygon.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_PairOfPolygon.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_SelectorOfDataStructureOfDelaun.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_SelectorOfDataStructureOfDelaun.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_ShapeTool.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_ShapeTool.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_Triangle.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_Triangle.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_Vertex.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_Vertex.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_VertexInspector.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_VertexInspector.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/BRepMesh/BRepMesh_VertexTool.cxx" )
  SOURCE_GROUP (BRepMesh FILES "../../../src/BRepMesh/BRepMesh_VertexTool.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/IntPoly/IntPoly_IndexedMapNodeOfIndexedMapOfPnt2d_0.cxx" )
  SOURCE_GROUP (IntPoly FILES "../../../drv/IntPoly/IntPoly_IndexedMapNodeOfIndexedMapOfPnt2d_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/IntPoly/IntPoly_IndexedMapNodeOfIndexedMapOfPnt_0.cxx" )
  SOURCE_GROUP (IntPoly FILES "../../../drv/IntPoly/IntPoly_IndexedMapNodeOfIndexedMapOfPnt_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/IntPoly/IntPoly_IndexedMapOfPnt2d_0.cxx" )
  SOURCE_GROUP (IntPoly FILES "../../../drv/IntPoly/IntPoly_IndexedMapOfPnt2d_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/IntPoly/IntPoly_IndexedMapOfPnt_0.cxx" )
  SOURCE_GROUP (IntPoly FILES "../../../drv/IntPoly/IntPoly_IndexedMapOfPnt_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/IntPoly/IntPoly_SequenceNodeOfSequenceOfSequenceOfPnt2d_0.cxx" )
  SOURCE_GROUP (IntPoly FILES "../../../drv/IntPoly/IntPoly_SequenceNodeOfSequenceOfSequenceOfPnt2d_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/IntPoly/IntPoly_SequenceNodeOfSequenceOfSequenceOfPnt_0.cxx" )
  SOURCE_GROUP (IntPoly FILES "../../../drv/IntPoly/IntPoly_SequenceNodeOfSequenceOfSequenceOfPnt_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/IntPoly/IntPoly_SequenceOfSequenceOfPnt2d_0.cxx" )
  SOURCE_GROUP (IntPoly FILES "../../../drv/IntPoly/IntPoly_SequenceOfSequenceOfPnt2d_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../drv/IntPoly/IntPoly_SequenceOfSequenceOfPnt_0.cxx" )
  SOURCE_GROUP (IntPoly FILES "../../../drv/IntPoly/IntPoly_SequenceOfSequenceOfPnt_0.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/IntPoly/IntPoly_PlaneSection.cxx" )
  SOURCE_GROUP (IntPoly FILES "../../../src/IntPoly/IntPoly_PlaneSection.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/IntPoly/IntPoly_Pnt2dHasher.cxx" )
  SOURCE_GROUP (IntPoly FILES "../../../src/IntPoly/IntPoly_Pnt2dHasher.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/IntPoly/IntPoly_PntHasher.cxx" )
  SOURCE_GROUP (IntPoly FILES "../../../src/IntPoly/IntPoly_PntHasher.cxx")

  list( APPEND TKMesh_USED_SRCFILES "../../../src/IntPoly/IntPoly_ShapeSection.cxx" )
  SOURCE_GROUP (IntPoly FILES "../../../src/IntPoly/IntPoly_ShapeSection.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKMesh)
 add_library( TKMesh SHARED ${TKMesh_USED_SRCFILES} )

 set_property(TARGET TKMesh PROPERTY FOLDER ModelingAlgorithms)

 install( TARGETS TKMesh
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKMesh.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKMesh PROPERTIES COMPILE_FLAGS "${TKMesh_PRECOMPILED_DEFS}" )
 include_directories( ${TKMesh_COMPILER_DIRECTORIES} )
 target_link_libraries( TKMesh ${TKMesh_USED_LIBS} )
endif()
