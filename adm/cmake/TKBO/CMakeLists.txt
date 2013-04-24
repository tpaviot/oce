project(TKBO)

if (WIN32)
  list( APPEND TKBO_PRECOMPILED_DEFS "-D__IntTools_DLL" )
  list( APPEND TKBO_PRECOMPILED_DEFS "-D__BRepAlgoAPI_DLL" )
  list( APPEND TKBO_PRECOMPILED_DEFS "-D__BOPCol_DLL" )
  list( APPEND TKBO_PRECOMPILED_DEFS "-D__BOPInt_DLL" )
  list( APPEND TKBO_PRECOMPILED_DEFS "-D__BOPDS_DLL" )
  list( APPEND TKBO_PRECOMPILED_DEFS "-D__BOPAlgo_DLL" )
  list( APPEND TKBO_PRECOMPILED_DEFS "-D__BOPTools_DLL" )
  string( REGEX REPLACE ";" " " TKBO_PRECOMPILED_DEFS "${TKBO_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKBO_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKBO_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKBO_COMPILER_DIRECTORIES "../../../drv/IntTools" )
  list( APPEND TKBO_COMPILER_DIRECTORIES "../../../src/IntTools" )
  list( APPEND TKBO_COMPILER_DIRECTORIES "../../../drv/BRepAlgoAPI" )
  list( APPEND TKBO_COMPILER_DIRECTORIES "../../../src/BRepAlgoAPI" )
  list( APPEND TKBO_COMPILER_DIRECTORIES "../../../drv/BOPCol" )
  list( APPEND TKBO_COMPILER_DIRECTORIES "../../../src/BOPCol" )
  list( APPEND TKBO_COMPILER_DIRECTORIES "../../../drv/BOPInt" )
  list( APPEND TKBO_COMPILER_DIRECTORIES "../../../src/BOPInt" )
  list( APPEND TKBO_COMPILER_DIRECTORIES "../../../drv/BOPDS" )
  list( APPEND TKBO_COMPILER_DIRECTORIES "../../../src/BOPDS" )
  list( APPEND TKBO_COMPILER_DIRECTORIES "../../../drv/BOPAlgo" )
  list( APPEND TKBO_COMPILER_DIRECTORIES "../../../src/BOPAlgo" )
  list( APPEND TKBO_COMPILER_DIRECTORIES "../../../drv/BOPTools" )
  list( APPEND TKBO_COMPILER_DIRECTORIES "../../../src/BOPTools" )

if (WIN32)
else()
endif()

  list( APPEND TKBO_USED_LIBS TKBRep )
  list( APPEND TKBO_USED_LIBS TKTopAlgo )
  list( APPEND TKBO_USED_LIBS TKMath )
  list( APPEND TKBO_USED_LIBS TKernel )
  list( APPEND TKBO_USED_LIBS TKG2d )
  list( APPEND TKBO_USED_LIBS TKG3d )
  list( APPEND TKBO_USED_LIBS TKGeomAlgo )
  list( APPEND TKBO_USED_LIBS TKGeomBase )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_Array1OfRange_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_Array1OfRange_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_Array1OfRoots_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_Array1OfRoots_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_CArray1OfInteger_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_CArray1OfInteger_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_CArray1OfReal_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_CArray1OfReal_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_DataMapIteratorOfDataMapOfCurveSampleBox_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_DataMapIteratorOfDataMapOfCurveSampleBox_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_DataMapIteratorOfDataMapOfSurfaceSampleBox_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_DataMapIteratorOfDataMapOfSurfaceSampleBox_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_DataMapNodeOfDataMapOfCurveSampleBox_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_DataMapNodeOfDataMapOfCurveSampleBox_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_DataMapNodeOfDataMapOfSurfaceSampleBox_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_DataMapNodeOfDataMapOfSurfaceSampleBox_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_DataMapOfCurveSampleBox_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_DataMapOfCurveSampleBox_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_DataMapOfSurfaceSampleBox_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_DataMapOfSurfaceSampleBox_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_IndexedDataMapNodeOfIndexedDataMapOfTransientAddress_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_IndexedDataMapNodeOfIndexedDataMapOfTransientAddress_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_IndexedDataMapOfTransientAddress_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_IndexedDataMapOfTransientAddress_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_ListIteratorOfListOfBox_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_ListIteratorOfListOfBox_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_ListIteratorOfListOfCurveRangeSample_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_ListIteratorOfListOfCurveRangeSample_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_ListIteratorOfListOfSurfaceRangeSample_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_ListIteratorOfListOfSurfaceRangeSample_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_ListNodeOfListOfBox_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_ListNodeOfListOfBox_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_ListNodeOfListOfCurveRangeSample_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_ListNodeOfListOfCurveRangeSample_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_ListNodeOfListOfSurfaceRangeSample_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_ListNodeOfListOfSurfaceRangeSample_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_ListOfBox_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_ListOfBox_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_ListOfCurveRangeSample_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_ListOfCurveRangeSample_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_ListOfSurfaceRangeSample_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_ListOfSurfaceRangeSample_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_MapIteratorOfMapOfCurveSample_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_MapIteratorOfMapOfCurveSample_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_MapIteratorOfMapOfSurfaceSample_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_MapIteratorOfMapOfSurfaceSample_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_MapOfCurveSample_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_MapOfCurveSample_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_MapOfSurfaceSample_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_MapOfSurfaceSample_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_QuickSortRange_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_QuickSortRange_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_QuickSort_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_QuickSort_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_SequenceNodeOfSequenceOfCommonPrts_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_SequenceNodeOfSequenceOfCommonPrts_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_SequenceNodeOfSequenceOfCurves_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_SequenceNodeOfSequenceOfCurves_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_SequenceNodeOfSequenceOfPntOn2Faces_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_SequenceNodeOfSequenceOfPntOn2Faces_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_SequenceNodeOfSequenceOfRanges_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_SequenceNodeOfSequenceOfRanges_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_SequenceNodeOfSequenceOfRoots_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_SequenceNodeOfSequenceOfRoots_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_SequenceOfCommonPrts_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_SequenceOfCommonPrts_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_SequenceOfCurves_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_SequenceOfCurves_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_SequenceOfPntOn2Faces_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_SequenceOfPntOn2Faces_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_SequenceOfRanges_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_SequenceOfRanges_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_SequenceOfRoots_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_SequenceOfRoots_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_StdMapNodeOfMapOfCurveSample_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_StdMapNodeOfMapOfCurveSample_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../drv/IntTools/IntTools_StdMapNodeOfMapOfSurfaceSample_0.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../drv/IntTools/IntTools_StdMapNodeOfMapOfSurfaceSample_0.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_BaseRangeSample.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_BaseRangeSample.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_BeanBeanIntersector.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_BeanBeanIntersector.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_BeanFaceIntersector.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_BeanFaceIntersector.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_CommonPrt.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_CommonPrt.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_Compare.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_Compare.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_CompareRange.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_CompareRange.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_Curve.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_Curve.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_CurveRangeLocalizeData.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_CurveRangeLocalizeData.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_CurveRangeSample.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_CurveRangeSample.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_CurveRangeSampleMapHasher.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_CurveRangeSampleMapHasher.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_EdgeEdge.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_EdgeEdge.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_EdgeEdge_1.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_EdgeEdge_1.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_EdgeFace.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_EdgeFace.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_FClass2d.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_FClass2d.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_FaceFace.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_FaceFace.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_LineConstructor.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_LineConstructor.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_MarkedRangeSet.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_MarkedRangeSet.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_PntOn2Faces.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_PntOn2Faces.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_PntOnFace.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_PntOnFace.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_Range.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_Range.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_Root.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_Root.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_SurfaceRangeLocalizeData.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_SurfaceRangeLocalizeData.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_SurfaceRangeSample.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_SurfaceRangeSample.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_SurfaceRangeSampleMapHasher.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_SurfaceRangeSampleMapHasher.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_Tools.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_Tools.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/IntTools/IntTools_TopolTool.cxx" )
  SOURCE_GROUP (IntTools FILES "../../../src/IntTools/IntTools_TopolTool.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BRepAlgoAPI/BRepAlgoAPI.cxx" )
  SOURCE_GROUP (BRepAlgoAPI FILES "../../../src/BRepAlgoAPI/BRepAlgoAPI.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BRepAlgoAPI/BRepAlgoAPI_BooleanOperation.cxx" )
  SOURCE_GROUP (BRepAlgoAPI FILES "../../../src/BRepAlgoAPI/BRepAlgoAPI_BooleanOperation.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BRepAlgoAPI/BRepAlgoAPI_Check.cxx" )
  SOURCE_GROUP (BRepAlgoAPI FILES "../../../src/BRepAlgoAPI/BRepAlgoAPI_Check.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BRepAlgoAPI/BRepAlgoAPI_Common.cxx" )
  SOURCE_GROUP (BRepAlgoAPI FILES "../../../src/BRepAlgoAPI/BRepAlgoAPI_Common.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BRepAlgoAPI/BRepAlgoAPI_Cut.cxx" )
  SOURCE_GROUP (BRepAlgoAPI FILES "../../../src/BRepAlgoAPI/BRepAlgoAPI_Cut.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BRepAlgoAPI/BRepAlgoAPI_Fuse.cxx" )
  SOURCE_GROUP (BRepAlgoAPI FILES "../../../src/BRepAlgoAPI/BRepAlgoAPI_Fuse.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BRepAlgoAPI/BRepAlgoAPI_Section.cxx" )
  SOURCE_GROUP (BRepAlgoAPI FILES "../../../src/BRepAlgoAPI/BRepAlgoAPI_Section.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPInt/BOPInt_Context.cxx" )
  SOURCE_GROUP (BOPInt FILES "../../../src/BOPInt/BOPInt_Context.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPInt/BOPInt_ShrunkRange.cxx" )
  SOURCE_GROUP (BOPInt FILES "../../../src/BOPInt/BOPInt_ShrunkRange.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPInt/BOPInt_Tools.cxx" )
  SOURCE_GROUP (BOPInt FILES "../../../src/BOPInt/BOPInt_Tools.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPDS/BOPDS_BoxBndTree.cxx" )
  SOURCE_GROUP (BOPDS FILES "../../../src/BOPDS/BOPDS_BoxBndTree.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPDS/BOPDS_CommonBlock.cxx" )
  SOURCE_GROUP (BOPDS FILES "../../../src/BOPDS/BOPDS_CommonBlock.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPDS/BOPDS_Curve.cxx" )
  SOURCE_GROUP (BOPDS FILES "../../../src/BOPDS/BOPDS_Curve.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPDS/BOPDS_DS.cxx" )
  SOURCE_GROUP (BOPDS FILES "../../../src/BOPDS/BOPDS_DS.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPDS/BOPDS_FaceInfo.cxx" )
  SOURCE_GROUP (BOPDS FILES "../../../src/BOPDS/BOPDS_FaceInfo.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPDS/BOPDS_IndexRange.cxx" )
  SOURCE_GROUP (BOPDS FILES "../../../src/BOPDS/BOPDS_IndexRange.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPDS/BOPDS_Iterator.cxx" )
  SOURCE_GROUP (BOPDS FILES "../../../src/BOPDS/BOPDS_Iterator.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPDS/BOPDS_IteratorSI.cxx" )
  SOURCE_GROUP (BOPDS FILES "../../../src/BOPDS/BOPDS_IteratorSI.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPDS/BOPDS_PassKey.cxx" )
  SOURCE_GROUP (BOPDS FILES "../../../src/BOPDS/BOPDS_PassKey.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPDS/BOPDS_PassKeyBoolean.cxx" )
  SOURCE_GROUP (BOPDS FILES "../../../src/BOPDS/BOPDS_PassKeyBoolean.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPDS/BOPDS_PassKeyMapHasher.cxx" )
  SOURCE_GROUP (BOPDS FILES "../../../src/BOPDS/BOPDS_PassKeyMapHasher.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPDS/BOPDS_Pave.cxx" )
  SOURCE_GROUP (BOPDS FILES "../../../src/BOPDS/BOPDS_Pave.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPDS/BOPDS_PaveBlock.cxx" )
  SOURCE_GROUP (BOPDS FILES "../../../src/BOPDS/BOPDS_PaveBlock.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPDS/BOPDS_PaveMapHasher.cxx" )
  SOURCE_GROUP (BOPDS FILES "../../../src/BOPDS/BOPDS_PaveMapHasher.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPDS/BOPDS_Point.cxx" )
  SOURCE_GROUP (BOPDS FILES "../../../src/BOPDS/BOPDS_Point.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPDS/BOPDS_ShapeInfo.cxx" )
  SOURCE_GROUP (BOPDS FILES "../../../src/BOPDS/BOPDS_ShapeInfo.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPDS/BOPDS_SubIterator.cxx" )
  SOURCE_GROUP (BOPDS FILES "../../../src/BOPDS/BOPDS_SubIterator.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPDS/BOPDS_Tools.cxx" )
  SOURCE_GROUP (BOPDS FILES "../../../src/BOPDS/BOPDS_Tools.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_Algo.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_Algo.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_ArgumentAnalyzer.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_ArgumentAnalyzer.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_BOP.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_BOP.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_BOP_1.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_BOP_1.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_Builder.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_Builder.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_BuilderArea.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_BuilderArea.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_BuilderFace.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_BuilderFace.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_BuilderShape.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_BuilderShape.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_BuilderSolid.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_BuilderSolid.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_Builder_1.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_Builder_1.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_Builder_2.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_Builder_2.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_Builder_3.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_Builder_3.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_Builder_4.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_Builder_4.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_CheckResult.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_CheckResult.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_CheckerSI.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_CheckerSI.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_PaveFiller.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_PaveFiller.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_PaveFiller_1.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_PaveFiller_1.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_PaveFiller_2.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_PaveFiller_2.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_PaveFiller_3.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_PaveFiller_3.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_PaveFiller_4.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_PaveFiller_4.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_PaveFiller_5.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_PaveFiller_5.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_PaveFiller_6.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_PaveFiller_6.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_PaveFiller_7.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_PaveFiller_7.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_PaveFiller_8.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_PaveFiller_8.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_SectionAttribute.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_SectionAttribute.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_Tools.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_Tools.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_WireEdgeSet.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_WireEdgeSet.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_WireSplitter.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_WireSplitter.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPAlgo/BOPAlgo_WireSplitter_1.cxx" )
  SOURCE_GROUP (BOPAlgo FILES "../../../src/BOPAlgo/BOPAlgo_WireSplitter_1.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPTools/BOPTools.cxx" )
  SOURCE_GROUP (BOPTools FILES "../../../src/BOPTools/BOPTools.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPTools/BOPTools_AlgoTools.cxx" )
  SOURCE_GROUP (BOPTools FILES "../../../src/BOPTools/BOPTools_AlgoTools.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPTools/BOPTools_AlgoTools2D.cxx" )
  SOURCE_GROUP (BOPTools FILES "../../../src/BOPTools/BOPTools_AlgoTools2D.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPTools/BOPTools_AlgoTools3D.cxx" )
  SOURCE_GROUP (BOPTools FILES "../../../src/BOPTools/BOPTools_AlgoTools3D.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPTools/BOPTools_AlgoTools_1.cxx" )
  SOURCE_GROUP (BOPTools FILES "../../../src/BOPTools/BOPTools_AlgoTools_1.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPTools/BOPTools_AlgoTools_2.cxx" )
  SOURCE_GROUP (BOPTools FILES "../../../src/BOPTools/BOPTools_AlgoTools_2.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPTools/BOPTools_EdgeSet.cxx" )
  SOURCE_GROUP (BOPTools FILES "../../../src/BOPTools/BOPTools_EdgeSet.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPTools/BOPTools_Set.cxx" )
  SOURCE_GROUP (BOPTools FILES "../../../src/BOPTools/BOPTools_Set.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPTools/BOPTools_SetMapHasher.cxx" )
  SOURCE_GROUP (BOPTools FILES "../../../src/BOPTools/BOPTools_SetMapHasher.cxx")

  list( APPEND TKBO_USED_SRCFILES "../../../src/BOPTools/BOPTools_ShapeSet.cxx" )
  SOURCE_GROUP (BOPTools FILES "../../../src/BOPTools/BOPTools_ShapeSet.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKBO)
 add_library( TKBO SHARED ${TKBO_USED_SRCFILES} )

 set_property(TARGET TKBO PROPERTY FOLDER ModelingAlgorithms)

 install( TARGETS TKBO
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKBO.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKBO PROPERTIES COMPILE_FLAGS "${TKBO_PRECOMPILED_DEFS}" )
 include_directories( ${TKBO_COMPILER_DIRECTORIES} )
 target_link_libraries( TKBO ${TKBO_USED_LIBS} )
endif()
