# Makefile.am for Open Cascade toolkit TKBO
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/IntTools : @top_srcdir@/src/IntTools: \
@top_srcdir@/drv/BRepAlgoAPI : @top_srcdir@/src/BRepAlgoAPI: \
@top_srcdir@/drv/BOPCol : @top_srcdir@/src/BOPCol: \
@top_srcdir@/drv/BOPDS : @top_srcdir@/src/BOPDS: \
@top_srcdir@/drv/BOPAlgo : @top_srcdir@/src/BOPAlgo: \
@top_srcdir@/drv/BOPTools : @top_srcdir@/src/BOPTools


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES) $(CSF_TBB_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/IntTools -I@top_srcdir@/src/IntTools \
-I@top_srcdir@/drv/BRepAlgoAPI -I@top_srcdir@/src/BRepAlgoAPI \
-I@top_srcdir@/drv/BOPCol -I@top_srcdir@/src/BOPCol \
-I@top_srcdir@/drv/BOPDS -I@top_srcdir@/src/BOPDS \
-I@top_srcdir@/drv/BOPAlgo -I@top_srcdir@/src/BOPAlgo \
-I@top_srcdir@/drv/BOPTools -I@top_srcdir@/src/BOPTools


lib_LTLIBRARIES=libTKBO.la

libTKBO_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKBRep/libTKBRep.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKMath/libTKMath.la \
../TKernel/libTKernel.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKGeomBase/libTKGeomBase.la \
../TKPrim/libTKPrim.la \
$(STLPort_LIB) $(CSF_TBB_LIB) 

libTKBO_la_SOURCES = \
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
@top_srcdir@/src/BOPAlgo/BOPAlgo_Algo.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_ArgumentAnalyzer.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_BOP.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_Builder.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_BuilderArea.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_BuilderFace.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_BuilderShape.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_BuilderSolid.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_Builder_1.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_Builder_2.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_Builder_3.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_Builder_4.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_CheckResult.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_CheckerSI.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_MakerVolume.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_PaveFiller.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_PaveFiller_1.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_PaveFiller_10.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_PaveFiller_2.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_PaveFiller_3.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_PaveFiller_4.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_PaveFiller_5.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_PaveFiller_6.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_PaveFiller_7.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_PaveFiller_8.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_PaveFiller_9.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_Section.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_SectionAttribute.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_ShellSplitter.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_Tools.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_WireEdgeSet.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_WireSplitter.cxx \
@top_srcdir@/src/BOPAlgo/BOPAlgo_WireSplitter_1.cxx \
@top_srcdir@/src/BOPCol/BOPCol_Box2DBndTree.cxx \
@top_srcdir@/src/BOPCol/BOPCol_BoxBndTree.cxx \
@top_srcdir@/src/BOPDS/BOPDS_CommonBlock.cxx \
@top_srcdir@/src/BOPDS/BOPDS_Curve.cxx \
@top_srcdir@/src/BOPDS/BOPDS_DS.cxx \
@top_srcdir@/src/BOPDS/BOPDS_FaceInfo.cxx \
@top_srcdir@/src/BOPDS/BOPDS_IndexRange.cxx \
@top_srcdir@/src/BOPDS/BOPDS_Iterator.cxx \
@top_srcdir@/src/BOPDS/BOPDS_IteratorSI.cxx \
@top_srcdir@/src/BOPDS/BOPDS_PassKey.cxx \
@top_srcdir@/src/BOPDS/BOPDS_PassKeyBoolean.cxx \
@top_srcdir@/src/BOPDS/BOPDS_PassKeyMapHasher.cxx \
@top_srcdir@/src/BOPDS/BOPDS_Pave.cxx \
@top_srcdir@/src/BOPDS/BOPDS_PaveBlock.cxx \
@top_srcdir@/src/BOPDS/BOPDS_PaveMapHasher.cxx \
@top_srcdir@/src/BOPDS/BOPDS_Point.cxx \
@top_srcdir@/src/BOPDS/BOPDS_ShapeInfo.cxx \
@top_srcdir@/src/BOPDS/BOPDS_SubIterator.cxx \
@top_srcdir@/src/BOPDS/BOPDS_Tools.cxx \
@top_srcdir@/src/BOPTools/BOPTools.cxx \
@top_srcdir@/src/BOPTools/BOPTools_AlgoTools.cxx \
@top_srcdir@/src/BOPTools/BOPTools_AlgoTools2D.cxx \
@top_srcdir@/src/BOPTools/BOPTools_AlgoTools2D_1.cxx \
@top_srcdir@/src/BOPTools/BOPTools_AlgoTools3D.cxx \
@top_srcdir@/src/BOPTools/BOPTools_AlgoTools_1.cxx \
@top_srcdir@/src/BOPTools/BOPTools_AlgoTools_2.cxx \
@top_srcdir@/src/BOPTools/BOPTools_EdgeSet.cxx \
@top_srcdir@/src/BOPTools/BOPTools_Set.cxx \
@top_srcdir@/src/BOPTools/BOPTools_SetMapHasher.cxx \
@top_srcdir@/src/BOPTools/BOPTools_ShapeSet.cxx \
@top_srcdir@/src/BRepAlgoAPI/BRepAlgoAPI_Algo.cxx \
@top_srcdir@/src/BRepAlgoAPI/BRepAlgoAPI_BooleanOperation.cxx \
@top_srcdir@/src/BRepAlgoAPI/BRepAlgoAPI_BuilderAlgo.cxx \
@top_srcdir@/src/BRepAlgoAPI/BRepAlgoAPI_Check.cxx \
@top_srcdir@/src/BRepAlgoAPI/BRepAlgoAPI_Common.cxx \
@top_srcdir@/src/BRepAlgoAPI/BRepAlgoAPI_Cut.cxx \
@top_srcdir@/src/BRepAlgoAPI/BRepAlgoAPI_Fuse.cxx \
@top_srcdir@/src/BRepAlgoAPI/BRepAlgoAPI_Section.cxx \
@top_srcdir@/src/IntTools/IntTools.cxx \
@top_srcdir@/src/IntTools/IntTools_BaseRangeSample.cxx \
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
@top_srcdir@/src/IntTools/IntTools_EdgeFace.cxx \
@top_srcdir@/src/IntTools/IntTools_FClass2d.cxx \
@top_srcdir@/src/IntTools/IntTools_FaceFace.cxx \
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

