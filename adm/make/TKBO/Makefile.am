# Makefile.am for Open Cascade toolkit TKBO
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/BOPTColStd : @top_srcdir@/src/BOPTColStd: \
@top_srcdir@/drv/BOPTools : @top_srcdir@/src/BOPTools: \
@top_srcdir@/drv/BOP : @top_srcdir@/src/BOP: \
@top_srcdir@/drv/BooleanOperations : @top_srcdir@/src/BooleanOperations: \
@top_srcdir@/drv/IntTools : @top_srcdir@/src/IntTools: \
@top_srcdir@/drv/BRepAlgoAPI : @top_srcdir@/src/BRepAlgoAPI


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/BOPTColStd -I@top_srcdir@/src/BOPTColStd \
-I@top_srcdir@/drv/BOPTools -I@top_srcdir@/src/BOPTools \
-I@top_srcdir@/drv/BOP -I@top_srcdir@/src/BOP \
-I@top_srcdir@/drv/BooleanOperations -I@top_srcdir@/src/BooleanOperations \
-I@top_srcdir@/drv/IntTools -I@top_srcdir@/src/IntTools \
-I@top_srcdir@/drv/BRepAlgoAPI -I@top_srcdir@/src/BRepAlgoAPI


lib_LTLIBRARIES=libTKBO.la

libTKBO_la_LIBADD = $(CSF_OPT_LIBS) \
../TKBRep/libTKBRep.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKMath/libTKMath.la \
../TKernel/libTKernel.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKGeomBase/libTKGeomBase.la


libTKBO_la_SOURCES = \
@top_srcdir@/drv/BOP/BOP_IndexedDataMapNodeOfIndexedDataMapOfEdgeListFaceInfo_0.cxx \
@top_srcdir@/drv/BOP/BOP_IndexedDataMapNodeOfIndexedDataMapOfSolidClassifier_0.cxx \
@top_srcdir@/drv/BOP/BOP_IndexedDataMapNodeOfIndexedDataMapOfVertexListEdgeInfo_0.cxx \
@top_srcdir@/drv/BOP/BOP_IndexedDataMapOfEdgeListFaceInfo_0.cxx \
@top_srcdir@/drv/BOP/BOP_IndexedDataMapOfSolidClassifier_0.cxx \
@top_srcdir@/drv/BOP/BOP_IndexedDataMapOfVertexListEdgeInfo_0.cxx \
@top_srcdir@/drv/BOP/BOP_ListIteratorOfListOfCheckResult_0.cxx \
@top_srcdir@/drv/BOP/BOP_ListIteratorOfListOfConnexityBlock_0.cxx \
@top_srcdir@/drv/BOP/BOP_ListIteratorOfListOfEdgeInfo_0.cxx \
@top_srcdir@/drv/BOP/BOP_ListIteratorOfListOfFaceInfo_0.cxx \
@top_srcdir@/drv/BOP/BOP_ListIteratorOfListOfListOfLoop_0.cxx \
@top_srcdir@/drv/BOP/BOP_ListIteratorOfListOfLoop_0.cxx \
@top_srcdir@/drv/BOP/BOP_ListNodeOfListOfCheckResult_0.cxx \
@top_srcdir@/drv/BOP/BOP_ListNodeOfListOfConnexityBlock_0.cxx \
@top_srcdir@/drv/BOP/BOP_ListNodeOfListOfEdgeInfo_0.cxx \
@top_srcdir@/drv/BOP/BOP_ListNodeOfListOfFaceInfo_0.cxx \
@top_srcdir@/drv/BOP/BOP_ListNodeOfListOfListOfLoop_0.cxx \
@top_srcdir@/drv/BOP/BOP_ListNodeOfListOfLoop_0.cxx \
@top_srcdir@/drv/BOP/BOP_ListOfCheckResult_0.cxx \
@top_srcdir@/drv/BOP/BOP_ListOfConnexityBlock_0.cxx \
@top_srcdir@/drv/BOP/BOP_ListOfEdgeInfo_0.cxx \
@top_srcdir@/drv/BOP/BOP_ListOfFaceInfo_0.cxx \
@top_srcdir@/drv/BOP/BOP_ListOfListOfLoop_0.cxx \
@top_srcdir@/drv/BOP/BOP_ListOfLoop_0.cxx \
@top_srcdir@/drv/BOP/BOP_SeqOfSeqOfShape_0.cxx \
@top_srcdir@/drv/BOP/BOP_SequenceNodeOfSeqOfSeqOfShape_0.cxx \
@top_srcdir@/drv/BOPTColStd/BOPTColStd_CArray1OfInteger_0.cxx \
@top_srcdir@/drv/BOPTColStd/BOPTColStd_CArray1OfPnt2d_0.cxx \
@top_srcdir@/drv/BOPTColStd/BOPTColStd_CArray1OfShape_0.cxx \
@top_srcdir@/drv/BOPTColStd/BOPTColStd_IndexedDataMapNodeOfIndexedDataMapOfIntegerIndexedMapOfInteger_0.cxx \
@top_srcdir@/drv/BOPTColStd/BOPTColStd_IndexedDataMapNodeOfIndexedDataMapOfIntegerInteger_0.cxx \
@top_srcdir@/drv/BOPTColStd/BOPTColStd_IndexedDataMapNodeOfIndexedDataMapOfSWRInteger_0.cxx \
@top_srcdir@/drv/BOPTColStd/BOPTColStd_IndexedDataMapOfIntegerIndexedMapOfInteger_0.cxx \
@top_srcdir@/drv/BOPTColStd/BOPTColStd_IndexedDataMapOfIntegerInteger_0.cxx \
@top_srcdir@/drv/BOPTColStd/BOPTColStd_IndexedDataMapOfSWRInteger_0.cxx \
@top_srcdir@/drv/BOPTColStd/BOPTColStd_ListIteratorOfListOfListOfShape_0.cxx \
@top_srcdir@/drv/BOPTColStd/BOPTColStd_ListNodeOfListOfListOfShape_0.cxx \
@top_srcdir@/drv/BOPTColStd/BOPTColStd_ListOfListOfShape_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_Array1OfPave_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_Array2OfIntersectionStatus_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_CArray1OfEEInterference_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_CArray1OfESInterference_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_CArray1OfInterferenceLine_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_CArray1OfPave_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_CArray1OfSSInterference_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_CArray1OfVEInterference_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_CArray1OfVSInterference_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_CArray1OfVVInterference_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_CommonBlockPool_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_HArray2OfIntersectionStatus_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_IDMapOfPaveBlockIMapOfInteger_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_IDMapOfPaveBlockIMapOfPaveBlock_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_IMapOfPaveBlock_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_IndexedDataMapNodeOfIDMapOfPaveBlockIMapOfInteger_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_IndexedDataMapNodeOfIDMapOfPaveBlockIMapOfPaveBlock_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_IndexedDataMapNodeOfIndexedDataMapOfIntegerDEInfo_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_IndexedDataMapNodeOfIndexedDataMapOfIntegerPaveSet_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_IndexedDataMapNodeOfIndexedDataMapOfIntegerState_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_IndexedDataMapNodeOfIndexedDataMapOfShapeWithState_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_IndexedDataMapOfIntegerDEInfo_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_IndexedDataMapOfIntegerPaveSet_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_IndexedDataMapOfIntegerState_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_IndexedDataMapOfShapeWithState_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_IndexedMapNodeOfIMapOfPaveBlock_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_IndexedMapNodeOfIndexedMapOfCoupleOfInteger_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_IndexedMapOfCoupleOfInteger_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListIteratorOfListOfCheckResults_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListIteratorOfListOfCommonBlock_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListIteratorOfListOfCoupleOfInteger_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListIteratorOfListOfInterference_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListIteratorOfListOfPaveBlock_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListIteratorOfListOfPave_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListIteratorOfListOfShapeEnum_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListNodeOfListOfCheckResults_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListNodeOfListOfCommonBlock_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListNodeOfListOfCoupleOfInteger_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListNodeOfListOfInterference_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListNodeOfListOfPaveBlock_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListNodeOfListOfPave_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListNodeOfListOfShapeEnum_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListOfCheckResults_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListOfCommonBlock_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListOfCoupleOfInteger_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListOfInterference_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListOfPaveBlock_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListOfPave_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_ListOfShapeEnum_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_PavePool_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_QuickSortPave_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_SequenceNodeOfSequenceOfCurves_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_SequenceNodeOfSequenceOfPaveBlock_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_SequenceOfCurves_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_SequenceOfPaveBlock_0.cxx \
@top_srcdir@/drv/BOPTools/BOPTools_SplitShapesPool_0.cxx \
@top_srcdir@/drv/BooleanOperations/BooleanOperations_IndexedDataMapNodeOfIndexedDataMapOfShapeAncestorsSuccessors_0.cxx \
@top_srcdir@/drv/BooleanOperations/BooleanOperations_IndexedDataMapNodeOfIndexedDataMapOfShapeInteger_0.cxx \
@top_srcdir@/drv/BooleanOperations/BooleanOperations_IndexedDataMapOfShapeAncestorsSuccessors_0.cxx \
@top_srcdir@/drv/BooleanOperations/BooleanOperations_IndexedDataMapOfShapeInteger_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_Array1OfRange_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_Array1OfRoots_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_CArray1OfInteger_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_CArray1OfReal_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_DataMapIteratorOfDataMapOfCurveSampleBox_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_DataMapIteratorOfDataMapOfSurfaceSampleBox_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_DataMapNodeOfDataMapOfCurveSampleBox_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_DataMapNodeOfDataMapOfSurfaceSampleBox_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_DataMapOfCurveSampleBox_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_DataMapOfSurfaceSampleBox_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_IndexedDataMapNodeOfIndexedDataMapOfTransientAddress_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_IndexedDataMapOfTransientAddress_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_ListIteratorOfListOfBox_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_ListIteratorOfListOfCurveRangeSample_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_ListIteratorOfListOfSurfaceRangeSample_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_ListNodeOfListOfBox_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_ListNodeOfListOfCurveRangeSample_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_ListNodeOfListOfSurfaceRangeSample_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_ListOfBox_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_ListOfCurveRangeSample_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_ListOfSurfaceRangeSample_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_MapIteratorOfMapOfCurveSample_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_MapIteratorOfMapOfSurfaceSample_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_MapOfCurveSample_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_MapOfSurfaceSample_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_QuickSortRange_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_QuickSort_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_SequenceNodeOfSequenceOfCommonPrts_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_SequenceNodeOfSequenceOfCurves_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_SequenceNodeOfSequenceOfPntOn2Faces_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_SequenceNodeOfSequenceOfRanges_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_SequenceNodeOfSequenceOfRoots_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_SequenceOfCommonPrts_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_SequenceOfCurves_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_SequenceOfPntOn2Faces_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_SequenceOfRanges_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_SequenceOfRoots_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_StdMapNodeOfMapOfCurveSample_0.cxx \
@top_srcdir@/drv/IntTools/IntTools_StdMapNodeOfMapOfSurfaceSample_0.cxx \
@top_srcdir@/src/BOP/BOP_Area2dBuilder.cxx \
@top_srcdir@/src/BOP/BOP_Area3dBuilder.cxx \
@top_srcdir@/src/BOP/BOP_AreaBuilder.cxx \
@top_srcdir@/src/BOP/BOP_ArgumentAnalyzer.cxx \
@top_srcdir@/src/BOP/BOP_BlockBuilder.cxx \
@top_srcdir@/src/BOP/BOP_BlockIterator.cxx \
@top_srcdir@/src/BOP/BOP_Builder.cxx \
@top_srcdir@/src/BOP/BOP_BuilderTools.cxx \
@top_srcdir@/src/BOP/BOP_CheckResult.cxx \
@top_srcdir@/src/BOP/BOP_CompositeClassifier.cxx \
@top_srcdir@/src/BOP/BOP_ConnexityBlock.cxx \
@top_srcdir@/src/BOP/BOP_CorrectTolerances.cxx \
@top_srcdir@/src/BOP/BOP_Draw.cxx \
@top_srcdir@/src/BOP/BOP_EdgeInfo.cxx \
@top_srcdir@/src/BOP/BOP_EmptyBuilder.cxx \
@top_srcdir@/src/BOP/BOP_FaceAreaBuilder.cxx \
@top_srcdir@/src/BOP/BOP_FaceBuilder.cxx \
@top_srcdir@/src/BOP/BOP_FaceInfo.cxx \
@top_srcdir@/src/BOP/BOP_HistoryCollector.cxx \
@top_srcdir@/src/BOP/BOP_Loop.cxx \
@top_srcdir@/src/BOP/BOP_LoopClassifier.cxx \
@top_srcdir@/src/BOP/BOP_LoopSet.cxx \
@top_srcdir@/src/BOP/BOP_Refiner.cxx \
@top_srcdir@/src/BOP/BOP_SDFWESFiller.cxx \
@top_srcdir@/src/BOP/BOP_SFSCorrector.cxx \
@top_srcdir@/src/BOP/BOP_Section.cxx \
@top_srcdir@/src/BOP/BOP_SectionHistoryCollector.cxx \
@top_srcdir@/src/BOP/BOP_ShapeSet.cxx \
@top_srcdir@/src/BOP/BOP_ShellFaceClassifier.cxx \
@top_srcdir@/src/BOP/BOP_ShellFaceSet.cxx \
@top_srcdir@/src/BOP/BOP_ShellShell.cxx \
@top_srcdir@/src/BOP/BOP_ShellSolid.cxx \
@top_srcdir@/src/BOP/BOP_ShellSolidHistoryCollector.cxx \
@top_srcdir@/src/BOP/BOP_ShellSolid_1.cxx \
@top_srcdir@/src/BOP/BOP_ShellSolid_2.cxx \
@top_srcdir@/src/BOP/BOP_ShellSolid_3.cxx \
@top_srcdir@/src/BOP/BOP_ShellSplitter.cxx \
@top_srcdir@/src/BOP/BOP_SolidAreaBuilder.cxx \
@top_srcdir@/src/BOP/BOP_SolidBuilder.cxx \
@top_srcdir@/src/BOP/BOP_SolidClassifier.cxx \
@top_srcdir@/src/BOP/BOP_SolidSolid.cxx \
@top_srcdir@/src/BOP/BOP_SolidSolidHistoryCollector.cxx \
@top_srcdir@/src/BOP/BOP_SolidSolid_1.cxx \
@top_srcdir@/src/BOP/BOP_WESCorrector.cxx \
@top_srcdir@/src/BOP/BOP_WireEdgeClassifier.cxx \
@top_srcdir@/src/BOP/BOP_WireEdgeSet.cxx \
@top_srcdir@/src/BOP/BOP_WireShape.cxx \
@top_srcdir@/src/BOP/BOP_WireShell.cxx \
@top_srcdir@/src/BOP/BOP_WireSolid.cxx \
@top_srcdir@/src/BOP/BOP_WireSolidHistoryCollector.cxx \
@top_srcdir@/src/BOP/BOP_WireSplitter.cxx \
@top_srcdir@/src/BOP/BOP_WireWire.cxx \
@top_srcdir@/src/BOPTColStd/BOPTColStd_Dump.cxx \
@top_srcdir@/src/BOPTColStd/BOPTColStd_Failure.cxx \
@top_srcdir@/src/BOPTColStd/BOPTColStd_ShapeWithRank.cxx \
@top_srcdir@/src/BOPTColStd/BOPTColStd_ShapeWithRankHasher.cxx \
@top_srcdir@/src/BOPTools/BOPTools_CheckResult.cxx \
@top_srcdir@/src/BOPTools/BOPTools_Checker.cxx \
@top_srcdir@/src/BOPTools/BOPTools_CommonBlock.cxx \
@top_srcdir@/src/BOPTools/BOPTools_CommonBlockAPI.cxx \
@top_srcdir@/src/BOPTools/BOPTools_ComparePave.cxx \
@top_srcdir@/src/BOPTools/BOPTools_CoupleOfInteger.cxx \
@top_srcdir@/src/BOPTools/BOPTools_CoupleOfIntegerMapHasher.cxx \
@top_srcdir@/src/BOPTools/BOPTools_Curve.cxx \
@top_srcdir@/src/BOPTools/BOPTools_DEInfo.cxx \
@top_srcdir@/src/BOPTools/BOPTools_DEProcessor.cxx \
@top_srcdir@/src/BOPTools/BOPTools_DSFiller.cxx \
@top_srcdir@/src/BOPTools/BOPTools_EEInterference.cxx \
@top_srcdir@/src/BOPTools/BOPTools_ESInterference.cxx \
@top_srcdir@/src/BOPTools/BOPTools_Interference.cxx \
@top_srcdir@/src/BOPTools/BOPTools_InterferenceLine.cxx \
@top_srcdir@/src/BOPTools/BOPTools_InterferencePool.cxx \
@top_srcdir@/src/BOPTools/BOPTools_IteratorOfCoupleOfShape.cxx \
@top_srcdir@/src/BOPTools/BOPTools_PCurveMaker.cxx \
@top_srcdir@/src/BOPTools/BOPTools_Pave.cxx \
@top_srcdir@/src/BOPTools/BOPTools_PaveBlock.cxx \
@top_srcdir@/src/BOPTools/BOPTools_PaveBlockIterator.cxx \
@top_srcdir@/src/BOPTools/BOPTools_PaveBlockMapHasher.cxx \
@top_srcdir@/src/BOPTools/BOPTools_PaveFiller.cxx \
@top_srcdir@/src/BOPTools/BOPTools_PaveFiller_1.cxx \
@top_srcdir@/src/BOPTools/BOPTools_PaveFiller_2.cxx \
@top_srcdir@/src/BOPTools/BOPTools_PaveFiller_3.cxx \
@top_srcdir@/src/BOPTools/BOPTools_PaveFiller_4.cxx \
@top_srcdir@/src/BOPTools/BOPTools_PaveSet.cxx \
@top_srcdir@/src/BOPTools/BOPTools_PointBetween.cxx \
@top_srcdir@/src/BOPTools/BOPTools_RoughShapeIntersector.cxx \
@top_srcdir@/src/BOPTools/BOPTools_SSInterference.cxx \
@top_srcdir@/src/BOPTools/BOPTools_SSIntersectionAttribute.cxx \
@top_srcdir@/src/BOPTools/BOPTools_ShapeShapeInterference.cxx \
@top_srcdir@/src/BOPTools/BOPTools_SolidStateFiller.cxx \
@top_srcdir@/src/BOPTools/BOPTools_StateFiller.cxx \
@top_srcdir@/src/BOPTools/BOPTools_Tools.cxx \
@top_srcdir@/src/BOPTools/BOPTools_Tools2D.cxx \
@top_srcdir@/src/BOPTools/BOPTools_Tools3D.cxx \
@top_srcdir@/src/BOPTools/BOPTools_Tools3D_1.cxx \
@top_srcdir@/src/BOPTools/BOPTools_Tools3D_2.cxx \
@top_srcdir@/src/BOPTools/BOPTools_VEInterference.cxx \
@top_srcdir@/src/BOPTools/BOPTools_VSInterference.cxx \
@top_srcdir@/src/BOPTools/BOPTools_VVInterference.cxx \
@top_srcdir@/src/BOPTools/BOPTools_WireStateFiller.cxx \
@top_srcdir@/src/BRepAlgoAPI/BRepAlgoAPI_BooleanOperation.cxx \
@top_srcdir@/src/BRepAlgoAPI/BRepAlgoAPI_Common.cxx \
@top_srcdir@/src/BRepAlgoAPI/BRepAlgoAPI_Cut.cxx \
@top_srcdir@/src/BRepAlgoAPI/BRepAlgoAPI_Fuse.cxx \
@top_srcdir@/src/BRepAlgoAPI/BRepAlgoAPI_Section.cxx \
@top_srcdir@/src/BooleanOperations/BooleanOperations_AncestorsAndSuccessors.cxx \
@top_srcdir@/src/BooleanOperations/BooleanOperations_AncestorsSeqAndSuccessorsSeq.cxx \
@top_srcdir@/src/BooleanOperations/BooleanOperations_Explorer.cxx \
@top_srcdir@/src/BooleanOperations/BooleanOperations_OnceExplorer.cxx \
@top_srcdir@/src/BooleanOperations/BooleanOperations_ShapeAndInterferences.cxx \
@top_srcdir@/src/BooleanOperations/BooleanOperations_ShapesDataStructure.cxx \
@top_srcdir@/src/IntTools/IntTools.cxx \
@top_srcdir@/src/IntTools/IntTools_BaseRangeSample.cxx \
@top_srcdir@/src/IntTools/IntTools_BeanBeanIntersector.cxx \
@top_srcdir@/src/IntTools/IntTools_BeanFaceIntersector.cxx \
@top_srcdir@/src/IntTools/IntTools_CommonPrt.cxx \
@top_srcdir@/src/IntTools/IntTools_Compare.cxx \
@top_srcdir@/src/IntTools/IntTools_CompareRange.cxx \
@top_srcdir@/src/IntTools/IntTools_Context.cxx \
@top_srcdir@/src/IntTools/IntTools_Curve.cxx \
@top_srcdir@/src/IntTools/IntTools_CurveRangeLocalizeData.cxx \
@top_srcdir@/src/IntTools/IntTools_CurveRangeSample.cxx \
@top_srcdir@/src/IntTools/IntTools_CurveRangeSampleMapHasher.cxx \
@top_srcdir@/src/IntTools/IntTools_EdgeEdge.cxx \
@top_srcdir@/src/IntTools/IntTools_EdgeEdge_1.cxx \
@top_srcdir@/src/IntTools/IntTools_EdgeFace.cxx \
@top_srcdir@/src/IntTools/IntTools_FClass2d.cxx \
@top_srcdir@/src/IntTools/IntTools_FaceFace.cxx \
@top_srcdir@/src/IntTools/IntTools_LineConstructor.cxx \
@top_srcdir@/src/IntTools/IntTools_MarkedRangeSet.cxx \
@top_srcdir@/src/IntTools/IntTools_PntOn2Faces.cxx \
@top_srcdir@/src/IntTools/IntTools_PntOnFace.cxx \
@top_srcdir@/src/IntTools/IntTools_Range.cxx \
@top_srcdir@/src/IntTools/IntTools_Root.cxx \
@top_srcdir@/src/IntTools/IntTools_ShrunkRange.cxx \
@top_srcdir@/src/IntTools/IntTools_SurfaceRangeLocalizeData.cxx \
@top_srcdir@/src/IntTools/IntTools_SurfaceRangeSample.cxx \
@top_srcdir@/src/IntTools/IntTools_SurfaceRangeSampleMapHasher.cxx \
@top_srcdir@/src/IntTools/IntTools_Tools.cxx \
@top_srcdir@/src/IntTools/IntTools_TopolTool.cxx

