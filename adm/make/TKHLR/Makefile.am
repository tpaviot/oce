# Makefile.am for Open Cascade toolkit TKHLR
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/HLRTopoBRep : @top_srcdir@/src/HLRTopoBRep: \
@top_srcdir@/drv/HLRBRep : @top_srcdir@/src/HLRBRep: \
@top_srcdir@/drv/HLRAlgo : @top_srcdir@/src/HLRAlgo: \
@top_srcdir@/drv/Intrv : @top_srcdir@/src/Intrv: \
@top_srcdir@/drv/TopBas : @top_srcdir@/src/TopBas: \
@top_srcdir@/drv/TopCnx : @top_srcdir@/src/TopCnx: \
@top_srcdir@/drv/Contap : @top_srcdir@/src/Contap


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/HLRTopoBRep -I@top_srcdir@/src/HLRTopoBRep \
-I@top_srcdir@/drv/HLRBRep -I@top_srcdir@/src/HLRBRep \
-I@top_srcdir@/drv/HLRAlgo -I@top_srcdir@/src/HLRAlgo \
-I@top_srcdir@/drv/Intrv -I@top_srcdir@/src/Intrv \
-I@top_srcdir@/drv/TopBas -I@top_srcdir@/src/TopBas \
-I@top_srcdir@/drv/TopCnx -I@top_srcdir@/src/TopCnx \
-I@top_srcdir@/drv/Contap -I@top_srcdir@/src/Contap


lib_LTLIBRARIES=libTKHLR.la

libTKHLR_la_LIBADD = $(CSF_OPT_LIBS) \
../TKBRep/libTKBRep.la \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
../TKGeomBase/libTKGeomBase.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKTopAlgo/libTKTopAlgo.la


libTKHLR_la_SOURCES = \
@top_srcdir@/drv/Contap/Contap_Contour_0.cxx \
@top_srcdir@/drv/Contap/Contap_HContTool_0.cxx \
@top_srcdir@/drv/Contap/Contap_HCurve2dTool_0.cxx \
@top_srcdir@/drv/Contap/Contap_SequenceNodeOfSequenceOfIWLineOfTheIWalkingOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_SequenceNodeOfSequenceOfPathPointOfTheSearchOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_SequenceNodeOfSequenceOfSegmentOfTheSearchOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_SequenceNodeOfTheSequenceOfLineOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_SequenceNodeOfTheSequenceOfPointOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_SequenceOfIWLineOfTheIWalkingOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_SequenceOfPathPointOfTheSearchOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_SequenceOfSegmentOfTheSearchOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_TheArcFunctionOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_TheHSequenceOfPointOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_TheIWLineOfTheIWalkingOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_TheIWalkingOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_TheLineOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_ThePathPointOfTheSearchOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_ThePointOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_TheSearchInsideOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_TheSearchOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_TheSegmentOfTheSearchOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_TheSequenceOfLineOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_TheSequenceOfPointOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_TheSurfFunctionOfContour_0.cxx \
@top_srcdir@/drv/Contap/Contap_TheSurfPropsOfContour_0.cxx \
@top_srcdir@/drv/HLRAlgo/HLRAlgo_Array1OfPHDat_0.cxx \
@top_srcdir@/drv/HLRAlgo/HLRAlgo_Array1OfPINod_0.cxx \
@top_srcdir@/drv/HLRAlgo/HLRAlgo_Array1OfPISeg_0.cxx \
@top_srcdir@/drv/HLRAlgo/HLRAlgo_Array1OfTData_0.cxx \
@top_srcdir@/drv/HLRAlgo/HLRAlgo_HArray1OfPHDat_0.cxx \
@top_srcdir@/drv/HLRAlgo/HLRAlgo_HArray1OfPINod_0.cxx \
@top_srcdir@/drv/HLRAlgo/HLRAlgo_HArray1OfPISeg_0.cxx \
@top_srcdir@/drv/HLRAlgo/HLRAlgo_HArray1OfTData_0.cxx \
@top_srcdir@/drv/HLRAlgo/HLRAlgo_InterferenceList_0.cxx \
@top_srcdir@/drv/HLRAlgo/HLRAlgo_Interference_0.cxx \
@top_srcdir@/drv/HLRAlgo/HLRAlgo_ListIteratorOfInterferenceList_0.cxx \
@top_srcdir@/drv/HLRAlgo/HLRAlgo_ListIteratorOfListOfBPoint_0.cxx \
@top_srcdir@/drv/HLRAlgo/HLRAlgo_ListNodeOfInterferenceList_0.cxx \
@top_srcdir@/drv/HLRAlgo/HLRAlgo_ListNodeOfListOfBPoint_0.cxx \
@top_srcdir@/drv/HLRAlgo/HLRAlgo_ListOfBPoint_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_Array1OfEData_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_Array1OfFData_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_CInter_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_CLProps_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_ExactIntersectionPointOfTheIntPCurvePCurveOfCInter_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_IntConicCurveOfCInter_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_InterCSurf_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_ListIteratorOfListOfBPnt2D_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_ListIteratorOfListOfBPoint_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_ListNodeOfListOfBPnt2D_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_ListNodeOfListOfBPoint_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_ListOfBPnt2D_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_ListOfBPoint_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_PCLocFOfTheLocateExtPCOfTheProjPCurOfCInter_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_SLProps_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_SeqOfShapeBounds_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_SeqPCOfPCLocFOfTheLocateExtPCOfTheProjPCurOfCInter_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_SequenceNodeOfSeqOfShapeBounds_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_SequenceNodeOfSeqPCOfPCLocFOfTheLocateExtPCOfTheProjPCurOfCInter_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_TheCSFunctionOfInterCSurf_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_TheCurveLocatorOfTheProjPCurOfCInter_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfCInter_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_TheExactInterCSurf_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_TheIntConicCurveOfCInter_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_TheIntPCurvePCurveOfCInter_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_TheInterferenceOfInterCSurf_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_TheLocateExtPCOfTheProjPCurOfCInter_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_ThePolygonOfInterCSurf_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_ThePolygonToolOfInterCSurf_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_ThePolyhedronOfInterCSurf_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_ThePolyhedronToolOfInterCSurf_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_TheProjPCurOfCInter_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_TheQuadCurvExactInterCSurf_0.cxx \
@top_srcdir@/drv/HLRBRep/HLRBRep_TheQuadCurvFuncOfTheQuadCurvExactInterCSurf_0.cxx \
@top_srcdir@/drv/HLRTopoBRep/HLRTopoBRep_DataMapIteratorOfDataMapOfShapeFaceData_0.cxx \
@top_srcdir@/drv/HLRTopoBRep/HLRTopoBRep_DataMapIteratorOfMapOfShapeListOfVData_0.cxx \
@top_srcdir@/drv/HLRTopoBRep/HLRTopoBRep_DataMapNodeOfDataMapOfShapeFaceData_0.cxx \
@top_srcdir@/drv/HLRTopoBRep/HLRTopoBRep_DataMapNodeOfMapOfShapeListOfVData_0.cxx \
@top_srcdir@/drv/HLRTopoBRep/HLRTopoBRep_DataMapOfShapeFaceData_0.cxx \
@top_srcdir@/drv/HLRTopoBRep/HLRTopoBRep_ListIteratorOfListOfVData_0.cxx \
@top_srcdir@/drv/HLRTopoBRep/HLRTopoBRep_ListNodeOfListOfVData_0.cxx \
@top_srcdir@/drv/HLRTopoBRep/HLRTopoBRep_ListOfVData_0.cxx \
@top_srcdir@/drv/HLRTopoBRep/HLRTopoBRep_MapOfShapeListOfVData_0.cxx \
@top_srcdir@/drv/Intrv/Intrv_SequenceNodeOfSequenceOfInterval_0.cxx \
@top_srcdir@/drv/Intrv/Intrv_SequenceOfInterval_0.cxx \
@top_srcdir@/drv/TopBas/TopBas_ListIteratorOfListOfTestInterference_0.cxx \
@top_srcdir@/drv/TopBas/TopBas_ListNodeOfListOfTestInterference_0.cxx \
@top_srcdir@/drv/TopBas/TopBas_ListOfTestInterference_0.cxx \
@top_srcdir@/drv/TopBas/TopBas_TestInterference_0.cxx \
@top_srcdir@/src/Contap/Contap_ContAna.cxx \
@top_srcdir@/src/HLRAlgo/HLRAlgo.cxx \
@top_srcdir@/src/HLRAlgo/HLRAlgo_BiPoint.cxx \
@top_srcdir@/src/HLRAlgo/HLRAlgo_Coincidence.cxx \
@top_srcdir@/src/HLRAlgo/HLRAlgo_EdgeIterator.cxx \
@top_srcdir@/src/HLRAlgo/HLRAlgo_EdgeStatus.cxx \
@top_srcdir@/src/HLRAlgo/HLRAlgo_EdgesBlock.cxx \
@top_srcdir@/src/HLRAlgo/HLRAlgo_Intersection.cxx \
@top_srcdir@/src/HLRAlgo/HLRAlgo_PolyAlgo.cxx \
@top_srcdir@/src/HLRAlgo/HLRAlgo_PolyData.cxx \
@top_srcdir@/src/HLRAlgo/HLRAlgo_PolyHidingData.cxx \
@top_srcdir@/src/HLRAlgo/HLRAlgo_PolyInternalData.cxx \
@top_srcdir@/src/HLRAlgo/HLRAlgo_PolyInternalNode.cxx \
@top_srcdir@/src/HLRAlgo/HLRAlgo_PolyInternalSegment.cxx \
@top_srcdir@/src/HLRAlgo/HLRAlgo_PolyShellData.cxx \
@top_srcdir@/src/HLRAlgo/HLRAlgo_Projector.cxx \
@top_srcdir@/src/HLRAlgo/HLRAlgo_TriangleData.cxx \
@top_srcdir@/src/HLRAlgo/HLRAlgo_WiresBlock.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_Algo.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_AreaLimit.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_BCurveTool.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_BSurfaceTool.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_BiPnt2D.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_BiPoint.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_CLPropsATool.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_Curve.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_CurveTool.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_Data.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_EdgeBuilder.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_EdgeData.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_EdgeFaceTool.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_EdgeIList.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_EdgeInterferenceTool.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_FaceData.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_FaceIterator.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_HLRToShape.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_Hider.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_InternalAlgo.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_Intersector.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_LineTool.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_PolyAlgo.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_PolyHLRToShape.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_SLPropsATool.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_ShapeBounds.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_ShapeToHLR.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_Surface.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_SurfaceTool.cxx \
@top_srcdir@/src/HLRBRep/HLRBRep_VertexList.cxx \
@top_srcdir@/src/HLRTopoBRep/HLRTopoBRep_DSFiller.cxx \
@top_srcdir@/src/HLRTopoBRep/HLRTopoBRep_Data.cxx \
@top_srcdir@/src/HLRTopoBRep/HLRTopoBRep_FaceData.cxx \
@top_srcdir@/src/HLRTopoBRep/HLRTopoBRep_FaceIsoLiner.cxx \
@top_srcdir@/src/HLRTopoBRep/HLRTopoBRep_OutLiner.cxx \
@top_srcdir@/src/HLRTopoBRep/HLRTopoBRep_VData.cxx \
@top_srcdir@/src/Intrv/Intrv_Interval.cxx \
@top_srcdir@/src/Intrv/Intrv_Intervals.cxx \
@top_srcdir@/src/TopCnx/TopCnx_EdgeFaceTransition.cxx

