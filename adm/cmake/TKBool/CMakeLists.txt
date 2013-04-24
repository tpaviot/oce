project(TKBool)

if (WIN32)
  list( APPEND TKBool_PRECOMPILED_DEFS "-D__TopOpeBRep_DLL" )
  list( APPEND TKBool_PRECOMPILED_DEFS "-D__TopOpeBRepDS_DLL" )
  list( APPEND TKBool_PRECOMPILED_DEFS "-D__TopOpeBRepBuild_DLL" )
  list( APPEND TKBool_PRECOMPILED_DEFS "-D__TopOpeBRepTool_DLL" )
  list( APPEND TKBool_PRECOMPILED_DEFS "-D__BRepAlgo_DLL" )
  list( APPEND TKBool_PRECOMPILED_DEFS "-D__BRepFill_DLL" )
  list( APPEND TKBool_PRECOMPILED_DEFS "-D__BRepProj_DLL" )
  string( REGEX REPLACE ";" " " TKBool_PRECOMPILED_DEFS "${TKBool_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKBool_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKBool_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKBool_COMPILER_DIRECTORIES "../../../drv/TopOpeBRep" )
  list( APPEND TKBool_COMPILER_DIRECTORIES "../../../src/TopOpeBRep" )
  list( APPEND TKBool_COMPILER_DIRECTORIES "../../../drv/TopOpeBRepDS" )
  list( APPEND TKBool_COMPILER_DIRECTORIES "../../../src/TopOpeBRepDS" )
  list( APPEND TKBool_COMPILER_DIRECTORIES "../../../drv/TopOpeBRepBuild" )
  list( APPEND TKBool_COMPILER_DIRECTORIES "../../../src/TopOpeBRepBuild" )
  list( APPEND TKBool_COMPILER_DIRECTORIES "../../../drv/TopOpeBRepTool" )
  list( APPEND TKBool_COMPILER_DIRECTORIES "../../../src/TopOpeBRepTool" )
  list( APPEND TKBool_COMPILER_DIRECTORIES "../../../drv/BRepAlgo" )
  list( APPEND TKBool_COMPILER_DIRECTORIES "../../../src/BRepAlgo" )
  list( APPEND TKBool_COMPILER_DIRECTORIES "../../../drv/BRepFill" )
  list( APPEND TKBool_COMPILER_DIRECTORIES "../../../src/BRepFill" )
  list( APPEND TKBool_COMPILER_DIRECTORIES "../../../drv/BRepProj" )
  list( APPEND TKBool_COMPILER_DIRECTORIES "../../../src/BRepProj" )

if (WIN32)
else()
endif()

  list( APPEND TKBool_USED_LIBS TKBRep )
  list( APPEND TKBool_USED_LIBS TKTopAlgo )
  list( APPEND TKBool_USED_LIBS TKMath )
  list( APPEND TKBool_USED_LIBS TKernel )
  list( APPEND TKBool_USED_LIBS TKPrim )
  list( APPEND TKBool_USED_LIBS TKG2d )
  list( APPEND TKBool_USED_LIBS TKG3d )
  list( APPEND TKBool_USED_LIBS TKShHealing )
  list( APPEND TKBool_USED_LIBS TKGeomBase )
  list( APPEND TKBool_USED_LIBS TKGeomAlgo )
  list( APPEND TKBool_USED_LIBS TKBO )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRep/TopOpeBRep_Array1OfLineInter_0.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../drv/TopOpeBRep/TopOpeBRep_Array1OfLineInter_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRep/TopOpeBRep_Array1OfVPointInter_0.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../drv/TopOpeBRep/TopOpeBRep_Array1OfVPointInter_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRep/TopOpeBRep_DataMapIteratorOfDataMapOfTopolTool_0.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../drv/TopOpeBRep/TopOpeBRep_DataMapIteratorOfDataMapOfTopolTool_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRep/TopOpeBRep_DataMapNodeOfDataMapOfTopolTool_0.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../drv/TopOpeBRep/TopOpeBRep_DataMapNodeOfDataMapOfTopolTool_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRep/TopOpeBRep_DataMapOfTopolTool_0.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../drv/TopOpeBRep/TopOpeBRep_DataMapOfTopolTool_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRep/TopOpeBRep_HArray1OfLineInter_0.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../drv/TopOpeBRep/TopOpeBRep_HArray1OfLineInter_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRep/TopOpeBRep_HArray1OfVPointInter_0.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../drv/TopOpeBRep/TopOpeBRep_HArray1OfVPointInter_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRep/TopOpeBRep_ListIteratorOfListOfBipoint_0.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../drv/TopOpeBRep/TopOpeBRep_ListIteratorOfListOfBipoint_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRep/TopOpeBRep_ListNodeOfListOfBipoint_0.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../drv/TopOpeBRep/TopOpeBRep_ListNodeOfListOfBipoint_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRep/TopOpeBRep_ListOfBipoint_0.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../drv/TopOpeBRep/TopOpeBRep_ListOfBipoint_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRep/TopOpeBRep_SequenceNodeOfSequenceOfPoint2d_0.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../drv/TopOpeBRep/TopOpeBRep_SequenceNodeOfSequenceOfPoint2d_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRep/TopOpeBRep_SequenceOfPoint2d_0.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../drv/TopOpeBRep/TopOpeBRep_SequenceOfPoint2d_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_Bipoint.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_Bipoint.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_DRAW.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_DRAW.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_DSFiller.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_DSFiller.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_EdgesFiller.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_EdgesFiller.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_EdgesIntersector.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_EdgesIntersector.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_EdgesIntersector_1.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_EdgesIntersector_1.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_FFDumper.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_FFDumper.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_FFTransitionTool.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_FFTransitionTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_FaceEdgeFiller.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_FaceEdgeFiller.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_FaceEdgeFiller_DEB.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_FaceEdgeFiller_DEB.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_FaceEdgeIntersector.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_FaceEdgeIntersector.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_FacesFiller.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_FacesFiller.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_FacesFiller_1.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_FacesFiller_1.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_FacesFiller_VPonR.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_FacesFiller_VPonR.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_FacesIntersector.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_FacesIntersector.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_GeomTool.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_GeomTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_Hctxee2d.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_Hctxee2d.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_Hctxff2d.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_Hctxff2d.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_LineInter.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_LineInter.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_Point2d.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_Point2d.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_PointClassifier.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_PointClassifier.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_PointGeomTool.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_PointGeomTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_ProcessGR.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_ProcessGR.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_ProcessSectionEdges.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_ProcessSectionEdges.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_ShapeIntersector.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_ShapeIntersector.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_ShapeIntersector2d.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_ShapeIntersector2d.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_ShapeScanner.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_ShapeScanner.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_VPointInter.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_VPointInter.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_VPointInterClassifier.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_VPointInterClassifier.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_VPointInterIterator.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_VPointInterIterator.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_WPointInter.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_WPointInter.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_WPointInterIterator.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_WPointInterIterator.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_kpart.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_kpart.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_mergePDS.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_mergePDS.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_sort.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_sort.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_trace.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_trace.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_traceALWL.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_traceALWL.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_traceBOOPNINT.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_traceBOOPNINT.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_traceSIFF.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_traceSIFF.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_vpr.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_vpr.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_vprclo.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_vprclo.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRep/TopOpeBRep_vprdeg.cxx" )
  SOURCE_GROUP (TopOpeBRep FILES "../../../src/TopOpeBRep/TopOpeBRep_vprdeg.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_Array1OfDataMapOfIntegerListOfInterference_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_Array1OfDataMapOfIntegerListOfInterference_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfDataMapOfCheckStatus_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfDataMapOfCheckStatus_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfDataMapOfIntegerListOfInterference_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfDataMapOfIntegerListOfInterference_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfDataMapOfInterferenceListOfInterference_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfDataMapOfInterferenceListOfInterference_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfDataMapOfInterferenceShape_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfDataMapOfInterferenceShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfDataMapOfShapeListOfShapeOn1State_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfDataMapOfShapeListOfShapeOn1State_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfDataMapOfShapeState_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfDataMapOfShapeState_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfMapOfCurve_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfMapOfCurve_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfMapOfIntegerShapeData_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfMapOfIntegerShapeData_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfMapOfPoint_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfMapOfPoint_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfMapOfSurface_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfMapOfSurface_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfShapeSurface_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapIteratorOfShapeSurface_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfDataMapOfCheckStatus_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfDataMapOfCheckStatus_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfDataMapOfIntegerListOfInterference_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfDataMapOfIntegerListOfInterference_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfDataMapOfInterferenceListOfInterference_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfDataMapOfInterferenceListOfInterference_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfDataMapOfInterferenceShape_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfDataMapOfInterferenceShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfDataMapOfShapeListOfShapeOn1State_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfDataMapOfShapeListOfShapeOn1State_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfDataMapOfShapeState_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfDataMapOfShapeState_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfMapOfCurve_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfMapOfCurve_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfMapOfIntegerShapeData_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfMapOfIntegerShapeData_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfMapOfPoint_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfMapOfPoint_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfMapOfSurface_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfMapOfSurface_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfShapeSurface_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapNodeOfShapeSurface_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapOfCheckStatus_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapOfCheckStatus_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapOfIntegerListOfInterference_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapOfIntegerListOfInterference_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapOfInterferenceListOfInterference_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapOfInterferenceListOfInterference_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapOfInterferenceShape_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapOfInterferenceShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapOfShapeListOfShapeOn1State_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapOfShapeListOfShapeOn1State_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapOfShapeState_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DataMapOfShapeState_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DoubleMapIteratorOfDoubleMapOfIntegerShape_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DoubleMapIteratorOfDoubleMapOfIntegerShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DoubleMapNodeOfDoubleMapOfIntegerShape_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DoubleMapNodeOfDoubleMapOfIntegerShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DoubleMapOfIntegerShape_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_DoubleMapOfIntegerShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_HArray1OfDataMapOfIntegerListOfInterference_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_HArray1OfDataMapOfIntegerListOfInterference_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_IndexedDataMapNodeOfIndexedDataMapOfShapeWithState_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_IndexedDataMapNodeOfIndexedDataMapOfShapeWithState_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_IndexedDataMapNodeOfIndexedDataMapOfVertexPoint_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_IndexedDataMapNodeOfIndexedDataMapOfVertexPoint_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_IndexedDataMapNodeOfMapOfShapeData_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_IndexedDataMapNodeOfMapOfShapeData_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_IndexedDataMapOfShapeWithState_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_IndexedDataMapOfShapeWithState_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_IndexedDataMapOfVertexPoint_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_IndexedDataMapOfVertexPoint_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_ListIteratorOfListOfInterference_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_ListIteratorOfListOfInterference_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_ListNodeOfListOfInterference_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_ListNodeOfListOfInterference_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_ListOfInterference_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_ListOfInterference_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_MapOfCurve_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_MapOfCurve_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_MapOfIntegerShapeData_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_MapOfIntegerShapeData_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_MapOfPoint_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_MapOfPoint_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_MapOfShapeData_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_MapOfShapeData_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_MapOfSurface_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_MapOfSurface_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_ShapeSurface_0.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../drv/TopOpeBRepDS/TopOpeBRepDS_ShapeSurface_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Association.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Association.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_BuildTool.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_BuildTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Check.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Check.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Curve.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Curve.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_CurveData.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_CurveData.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_CurveExplorer.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_CurveExplorer.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_CurveIterator.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_CurveIterator.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_CurvePointInterference.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_CurvePointInterference.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_DRAW.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_DRAW.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_DSS.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_DSS.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_DataStructure.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_DataStructure.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Dumper.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Dumper.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_EIR.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_EIR.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_EXPORT.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_EXPORT.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Edge3dInterferenceTool.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Edge3dInterferenceTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_EdgeInterferenceTool.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_EdgeInterferenceTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_EdgeVertexInterference.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_EdgeVertexInterference.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Explorer.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Explorer.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_FIR.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_FIR.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_FaceEdgeInterference.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_FaceEdgeInterference.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_FaceInterferenceTool.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_FaceInterferenceTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Filter.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Filter.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_FilterCurveInterferences.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_FilterCurveInterferences.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_FilterEdgeInterferences.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_FilterEdgeInterferences.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_FilterFaceInterferences.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_FilterFaceInterferences.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_GapFiller.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_GapFiller.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_GapTool.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_GapTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_GeometryData.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_GeometryData.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_HDataStructure.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_HDataStructure.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Interference.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Interference.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_InterferenceIterator.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_InterferenceIterator.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_InterferenceTool.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_InterferenceTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_ListOfShapeOn1State.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_ListOfShapeOn1State.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Marker.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Marker.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Point.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Point.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_PointData.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_PointData.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_PointExplorer.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_PointExplorer.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_PointIterator.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_PointIterator.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_ProcessEdgeInterferences.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_ProcessEdgeInterferences.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_ProcessFaceInterferences.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_ProcessFaceInterferences.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_ProcessInterferencesTool.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_ProcessInterferencesTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Reducer.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Reducer.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_ShapeData.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_ShapeData.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_ShapeShapeInterference.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_ShapeShapeInterference.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_ShapeWithState.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_ShapeWithState.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_SolidSurfaceInterference.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_SolidSurfaceInterference.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Surface.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Surface.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_SurfaceCurveInterference.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_SurfaceCurveInterference.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_SurfaceData.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_SurfaceData.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_SurfaceExplorer.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_SurfaceExplorer.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_SurfaceIterator.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_SurfaceIterator.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_TKI.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_TKI.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_TOOL.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_TOOL.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Transition.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_Transition.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_connex.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_connex.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_funk.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_funk.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_reDEB.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_reDEB.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_redu.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_redu.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_repvg.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_repvg.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_samdom.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_samdom.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_trace.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_trace.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_traceDSX.cxx" )
  SOURCE_GROUP (TopOpeBRepDS FILES "../../../src/TopOpeBRepDS/TopOpeBRepDS_traceDSX.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_DataMapIteratorOfDataMapOfShapeListOfShapeListOfShape_0.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_DataMapIteratorOfDataMapOfShapeListOfShapeListOfShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_DataMapNodeOfDataMapOfShapeListOfShapeListOfShape_0.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_DataMapNodeOfDataMapOfShapeListOfShapeListOfShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_DataMapOfShapeListOfShapeListOfShape_0.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_DataMapOfShapeListOfShapeListOfShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_IndexedDataMapNodeOfIndexedDataMapOfShapeVertexInfo_0.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_IndexedDataMapNodeOfIndexedDataMapOfShapeVertexInfo_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_IndexedDataMapOfShapeVertexInfo_0.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_IndexedDataMapOfShapeVertexInfo_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListIteratorOfListOfListOfLoop_0.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListIteratorOfListOfListOfLoop_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListIteratorOfListOfLoop_0.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListIteratorOfListOfLoop_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListIteratorOfListOfPave_0.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListIteratorOfListOfPave_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListIteratorOfListOfShapeListOfShape_0.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListIteratorOfListOfShapeListOfShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListNodeOfListOfListOfLoop_0.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListNodeOfListOfListOfLoop_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListNodeOfListOfLoop_0.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListNodeOfListOfLoop_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListNodeOfListOfPave_0.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListNodeOfListOfPave_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListNodeOfListOfShapeListOfShape_0.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListNodeOfListOfShapeListOfShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListOfListOfLoop_0.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListOfListOfLoop_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListOfLoop_0.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListOfLoop_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListOfPave_0.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListOfPave_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListOfShapeListOfShape_0.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../drv/TopOpeBRepBuild/TopOpeBRepBuild_ListOfShapeListOfShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Area1dBuilder.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Area1dBuilder.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Area2dBuilder.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Area2dBuilder.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Area3dBuilder.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Area3dBuilder.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_AreaBuilder.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_AreaBuilder.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_BlockBuilder.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_BlockBuilder.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_BlockIterator.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_BlockIterator.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_BuildEdges.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_BuildEdges.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_BuildFaces.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_BuildFaces.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_BuildVertices.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_BuildVertices.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Builder.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Builder.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Builder1.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Builder1.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Builder1_1.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Builder1_1.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Builder1_2.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Builder1_2.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_BuilderON.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_BuilderON.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_BuilderON2d.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_BuilderON2d.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_CompositeClassifier.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_CompositeClassifier.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_CorrectFace2d.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_CorrectFace2d.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_EdgeBuilder.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_EdgeBuilder.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_End.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_End.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_FREGU.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_FREGU.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_FaceAreaBuilder.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_FaceAreaBuilder.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_FaceBuilder.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_FaceBuilder.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_FuseFace.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_FuseFace.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_GIter.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_GIter.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_GTool.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_GTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_GTopo.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_GTopo.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Grid.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Grid.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_GridEE.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_GridEE.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_GridFF.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_GridFF.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_GridSS.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_GridSS.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Griddump.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Griddump.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_HBuilder.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_HBuilder.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_KPart.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_KPart.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Loop.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Loop.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_LoopClassifier.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_LoopClassifier.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_LoopSet.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_LoopSet.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Merge.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Merge.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Pave.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Pave.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_PaveClassifier.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_PaveClassifier.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_PaveSet.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_PaveSet.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_SREGU.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_SREGU.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Section.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Section.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_ShapeListOfShape.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_ShapeListOfShape.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_ShapeSet.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_ShapeSet.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_ShellFaceClassifier.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_ShellFaceClassifier.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_ShellFaceSet.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_ShellFaceSet.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_ShellToSolid.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_ShellToSolid.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_SolidAreaBuilder.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_SolidAreaBuilder.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_SolidBuilder.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_SolidBuilder.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Tools.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Tools.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Tools2d.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Tools2d.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Tools_1.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_Tools_1.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_VertexInfo.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_VertexInfo.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_WireEdgeClassifier.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_WireEdgeClassifier.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_WireEdgeSet.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_WireEdgeSet.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_WireToFace.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_WireToFace.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_fctwes.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_fctwes.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_ffsfs.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_ffsfs.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_ffwesk.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_ffwesk.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_keep.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_keep.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_kpkole.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_kpkole.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_makeedges.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_makeedges.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_makefaces.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_makefaces.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_makesolids.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_makesolids.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_on.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_on.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_trace.cxx" )
  SOURCE_GROUP (TopOpeBRepBuild FILES "../../../src/TopOpeBRepBuild/TopOpeBRepBuild_trace.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_DataMapIteratorOfDataMapOfOrientedShapeC2DF_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_DataMapIteratorOfDataMapOfOrientedShapeC2DF_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_DataMapIteratorOfDataMapOfShapeListOfC2DF_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_DataMapIteratorOfDataMapOfShapeListOfC2DF_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_DataMapIteratorOfDataMapOfShapeface_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_DataMapIteratorOfDataMapOfShapeface_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_DataMapNodeOfDataMapOfOrientedShapeC2DF_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_DataMapNodeOfDataMapOfOrientedShapeC2DF_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_DataMapNodeOfDataMapOfShapeListOfC2DF_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_DataMapNodeOfDataMapOfShapeListOfC2DF_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_DataMapNodeOfDataMapOfShapeface_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_DataMapNodeOfDataMapOfShapeface_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_DataMapOfOrientedShapeC2DF_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_DataMapOfOrientedShapeC2DF_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_DataMapOfShapeListOfC2DF_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_DataMapOfShapeListOfC2DF_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_DataMapOfShapeface_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_DataMapOfShapeface_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_IndexedDataMapNodeOfIndexedDataMapOfShapeBox2d_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_IndexedDataMapNodeOfIndexedDataMapOfShapeBox2d_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_IndexedDataMapNodeOfIndexedDataMapOfShapeBox_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_IndexedDataMapNodeOfIndexedDataMapOfShapeBox_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_IndexedDataMapNodeOfIndexedDataMapOfShapeconnexity_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_IndexedDataMapNodeOfIndexedDataMapOfShapeconnexity_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_IndexedDataMapNodeOfIndexedDataMapOfSolidClassifier_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_IndexedDataMapNodeOfIndexedDataMapOfSolidClassifier_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_IndexedDataMapOfShapeBox2d_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_IndexedDataMapOfShapeBox2d_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_IndexedDataMapOfShapeBox_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_IndexedDataMapOfShapeBox_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_IndexedDataMapOfShapeconnexity_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_IndexedDataMapOfShapeconnexity_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_IndexedDataMapOfSolidClassifier_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_IndexedDataMapOfSolidClassifier_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_ListIteratorOfListOfC2DF_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_ListIteratorOfListOfC2DF_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_ListNodeOfListOfC2DF_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_ListNodeOfListOfC2DF_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_ListOfC2DF_0.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../drv/TopOpeBRepTool/TopOpeBRepTool_ListOfC2DF_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_2d.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_2d.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_AncestorsTool.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_AncestorsTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_BoxSort.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_BoxSort.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_C2DF.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_C2DF.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_CLASSI.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_CLASSI.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_CORRISO.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_CORRISO.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_CurveTool.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_CurveTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_DRAW.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_DRAW.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_FuseEdges.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_FuseEdges.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_GEOMETRY.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_GEOMETRY.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_GeomTool.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_GeomTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_HBoxTool.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_HBoxTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_PROJECT.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_PROJECT.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_PURGE.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_PURGE.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_PurgeInternalEdges.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_PurgeInternalEdges.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_REGUS.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_REGUS.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_REGUW.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_REGUW.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_RegularizeS.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_RegularizeS.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_RegularizeW.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_RegularizeW.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_SC.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_SC.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_STATE.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_STATE.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_ShapeClassifier.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_ShapeClassifier.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_ShapeExplorer.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_ShapeExplorer.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_ShapeTool.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_ShapeTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_SolidClassifier.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_SolidClassifier.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_TOOL.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_TOOL.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_TOPOLOGY.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_TOPOLOGY.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_box.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_box.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_closing.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_closing.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_connexity.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_connexity.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_face.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_face.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_faulty.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_faulty.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_makeTransition.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_makeTransition.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_matter.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_matter.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_mkTondgE.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_mkTondgE.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_tol.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_tol.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_trace.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_trace.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_traceSTATE.cxx" )
  SOURCE_GROUP (TopOpeBRepTool FILES "../../../src/TopOpeBRepTool/TopOpeBRepTool_traceSTATE.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepAlgo/BRepAlgo_DataMapIteratorOfDataMapOfShapeBoolean_0.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../drv/BRepAlgo/BRepAlgo_DataMapIteratorOfDataMapOfShapeBoolean_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepAlgo/BRepAlgo_DataMapIteratorOfDataMapOfShapeInterference_0.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../drv/BRepAlgo/BRepAlgo_DataMapIteratorOfDataMapOfShapeInterference_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepAlgo/BRepAlgo_DataMapNodeOfDataMapOfShapeBoolean_0.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../drv/BRepAlgo/BRepAlgo_DataMapNodeOfDataMapOfShapeBoolean_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepAlgo/BRepAlgo_DataMapNodeOfDataMapOfShapeInterference_0.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../drv/BRepAlgo/BRepAlgo_DataMapNodeOfDataMapOfShapeInterference_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepAlgo/BRepAlgo_DataMapOfShapeBoolean_0.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../drv/BRepAlgo/BRepAlgo_DataMapOfShapeBoolean_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepAlgo/BRepAlgo_DataMapOfShapeInterference_0.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../drv/BRepAlgo/BRepAlgo_DataMapOfShapeInterference_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepAlgo/BRepAlgo_SequenceNodeOfSequenceOfSequenceOfInteger_0.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../drv/BRepAlgo/BRepAlgo_SequenceNodeOfSequenceOfSequenceOfInteger_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepAlgo/BRepAlgo_SequenceOfSequenceOfInteger_0.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../drv/BRepAlgo/BRepAlgo_SequenceOfSequenceOfInteger_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepAlgo/BRepAlgo.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../src/BRepAlgo/BRepAlgo.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepAlgo/BRepAlgo_1.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../src/BRepAlgo/BRepAlgo_1.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepAlgo/BRepAlgo_AsDes.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../src/BRepAlgo/BRepAlgo_AsDes.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepAlgo/BRepAlgo_BooleanOperation.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../src/BRepAlgo/BRepAlgo_BooleanOperation.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepAlgo/BRepAlgo_BooleanOperations.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../src/BRepAlgo/BRepAlgo_BooleanOperations.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepAlgo/BRepAlgo_Common.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../src/BRepAlgo/BRepAlgo_Common.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepAlgo/BRepAlgo_Cut.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../src/BRepAlgo/BRepAlgo_Cut.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepAlgo/BRepAlgo_DSAccess.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../src/BRepAlgo/BRepAlgo_DSAccess.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepAlgo/BRepAlgo_EdgeConnector.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../src/BRepAlgo/BRepAlgo_EdgeConnector.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepAlgo/BRepAlgo_FaceRestrictor.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../src/BRepAlgo/BRepAlgo_FaceRestrictor.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepAlgo/BRepAlgo_Fuse.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../src/BRepAlgo/BRepAlgo_Fuse.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepAlgo/BRepAlgo_Image.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../src/BRepAlgo/BRepAlgo_Image.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepAlgo/BRepAlgo_Loop.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../src/BRepAlgo/BRepAlgo_Loop.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepAlgo/BRepAlgo_NormalProjection.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../src/BRepAlgo/BRepAlgo_NormalProjection.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepAlgo/BRepAlgo_Section.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../src/BRepAlgo/BRepAlgo_Section.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepAlgo/BRepAlgo_Tool.cxx" )
  SOURCE_GROUP (BRepAlgo FILES "../../../src/BRepAlgo/BRepAlgo_Tool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_ComputeCLine_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_ComputeCLine_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_DataMapIteratorOfDataMapOfNodeDataMapOfShapeShape_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_DataMapIteratorOfDataMapOfNodeDataMapOfShapeShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_DataMapIteratorOfDataMapOfNodeShape_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_DataMapIteratorOfDataMapOfNodeShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_DataMapIteratorOfDataMapOfOrientedShapeListOfShape_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_DataMapIteratorOfDataMapOfOrientedShapeListOfShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_DataMapIteratorOfDataMapOfShapeDataMapOfShapeListOfShape_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_DataMapIteratorOfDataMapOfShapeDataMapOfShapeListOfShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_DataMapIteratorOfDataMapOfShapeSequenceOfPnt_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_DataMapIteratorOfDataMapOfShapeSequenceOfPnt_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_DataMapIteratorOfDataMapOfShapeSequenceOfReal_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_DataMapIteratorOfDataMapOfShapeSequenceOfReal_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_DataMapNodeOfDataMapOfNodeDataMapOfShapeShape_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_DataMapNodeOfDataMapOfNodeDataMapOfShapeShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_DataMapNodeOfDataMapOfNodeShape_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_DataMapNodeOfDataMapOfNodeShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_DataMapNodeOfDataMapOfOrientedShapeListOfShape_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_DataMapNodeOfDataMapOfOrientedShapeListOfShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_DataMapNodeOfDataMapOfShapeDataMapOfShapeListOfShape_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_DataMapNodeOfDataMapOfShapeDataMapOfShapeListOfShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_DataMapNodeOfDataMapOfShapeSequenceOfPnt_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_DataMapNodeOfDataMapOfShapeSequenceOfPnt_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_DataMapNodeOfDataMapOfShapeSequenceOfReal_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_DataMapNodeOfDataMapOfShapeSequenceOfReal_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_DataMapOfNodeDataMapOfShapeShape_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_DataMapOfNodeDataMapOfShapeShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_DataMapOfNodeShape_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_DataMapOfNodeShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_DataMapOfOrientedShapeListOfShape_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_DataMapOfOrientedShapeListOfShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_DataMapOfShapeDataMapOfShapeListOfShape_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_DataMapOfShapeDataMapOfShapeListOfShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_DataMapOfShapeSequenceOfPnt_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_DataMapOfShapeSequenceOfPnt_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_DataMapOfShapeSequenceOfReal_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_DataMapOfShapeSequenceOfReal_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_IndexedDataMapNodeOfIndexedDataMapOfOrientedShapeListOfShape_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_IndexedDataMapNodeOfIndexedDataMapOfOrientedShapeListOfShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_IndexedDataMapOfOrientedShapeListOfShape_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_IndexedDataMapOfOrientedShapeListOfShape_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_ListIteratorOfListOfOffsetWire_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_ListIteratorOfListOfOffsetWire_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_ListNodeOfListOfOffsetWire_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_ListNodeOfListOfOffsetWire_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_ListOfOffsetWire_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_ListOfOffsetWire_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_MyLeastSquareOfComputeCLine_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_MyLeastSquareOfComputeCLine_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_SequenceNodeOfSequenceOfEdgeFaceAndOrder_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_SequenceNodeOfSequenceOfEdgeFaceAndOrder_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_SequenceNodeOfSequenceOfFaceAndOrder_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_SequenceNodeOfSequenceOfFaceAndOrder_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_SequenceNodeOfSequenceOfSection_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_SequenceNodeOfSequenceOfSection_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_SequenceOfEdgeFaceAndOrder_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_SequenceOfEdgeFaceAndOrder_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_SequenceOfFaceAndOrder_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_SequenceOfFaceAndOrder_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../drv/BRepFill/BRepFill_SequenceOfSection_0.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../drv/BRepFill/BRepFill_SequenceOfSection_0.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_ACRLaw.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_ACRLaw.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_ApproxSeewing.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_ApproxSeewing.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_CompatibleWires.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_CompatibleWires.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_CurveConstraint.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_CurveConstraint.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_Draft.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_Draft.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_DraftLaw.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_DraftLaw.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_Edge3DLaw.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_Edge3DLaw.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_EdgeFaceAndOrder.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_EdgeFaceAndOrder.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_EdgeOnSurfLaw.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_EdgeOnSurfLaw.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_Evolved.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_Evolved.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_FaceAndOrder.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_FaceAndOrder.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_Filling.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_Filling.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_Generator.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_Generator.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_LocationLaw.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_LocationLaw.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_MultiLine.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_MultiLine.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_MultiLineTool.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_MultiLineTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_NSections.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_NSections.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_OffsetAncestors.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_OffsetAncestors.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_OffsetWire.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_OffsetWire.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_Pipe.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_Pipe.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_PipeShell.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_PipeShell.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_Section.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_Section.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_SectionLaw.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_SectionLaw.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_SectionPlacement.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_SectionPlacement.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_ShapeLaw.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_ShapeLaw.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_Sweep.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_Sweep.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_TrimEdgeTool.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_TrimEdgeTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_TrimShellCorner.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_TrimShellCorner.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepFill/BRepFill_TrimSurfaceTool.cxx" )
  SOURCE_GROUP (BRepFill FILES "../../../src/BRepFill/BRepFill_TrimSurfaceTool.cxx")

  list( APPEND TKBool_USED_SRCFILES "../../../src/BRepProj/BRepProj_Projection.cxx" )
  SOURCE_GROUP (BRepProj FILES "../../../src/BRepProj/BRepProj_Projection.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKBool)
 add_library( TKBool SHARED ${TKBool_USED_SRCFILES} )

 set_property(TARGET TKBool PROPERTY FOLDER ModelingAlgorithms)

 install( TARGETS TKBool
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKBool.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKBool PROPERTIES COMPILE_FLAGS "${TKBool_PRECOMPILED_DEFS}" )
 include_directories( ${TKBool_COMPILER_DIRECTORIES} )
 target_link_libraries( TKBool ${TKBool_USED_LIBS} )
endif()
