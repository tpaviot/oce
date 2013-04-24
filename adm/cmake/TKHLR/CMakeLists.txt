project(TKHLR)

if (WIN32)
  list( APPEND TKHLR_PRECOMPILED_DEFS "-D__HLRTopoBRep_DLL" )
  list( APPEND TKHLR_PRECOMPILED_DEFS "-D__HLRBRep_DLL" )
  list( APPEND TKHLR_PRECOMPILED_DEFS "-D__HLRAlgo_DLL" )
  list( APPEND TKHLR_PRECOMPILED_DEFS "-D__Intrv_DLL" )
  list( APPEND TKHLR_PRECOMPILED_DEFS "-D__TopBas_DLL" )
  list( APPEND TKHLR_PRECOMPILED_DEFS "-D__TopCnx_DLL" )
  list( APPEND TKHLR_PRECOMPILED_DEFS "-D__Contap_DLL" )
  string( REGEX REPLACE ";" " " TKHLR_PRECOMPILED_DEFS "${TKHLR_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKHLR_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKHLR_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKHLR_COMPILER_DIRECTORIES "../../../drv/HLRTopoBRep" )
  list( APPEND TKHLR_COMPILER_DIRECTORIES "../../../src/HLRTopoBRep" )
  list( APPEND TKHLR_COMPILER_DIRECTORIES "../../../drv/HLRBRep" )
  list( APPEND TKHLR_COMPILER_DIRECTORIES "../../../src/HLRBRep" )
  list( APPEND TKHLR_COMPILER_DIRECTORIES "../../../drv/HLRAlgo" )
  list( APPEND TKHLR_COMPILER_DIRECTORIES "../../../src/HLRAlgo" )
  list( APPEND TKHLR_COMPILER_DIRECTORIES "../../../drv/Intrv" )
  list( APPEND TKHLR_COMPILER_DIRECTORIES "../../../src/Intrv" )
  list( APPEND TKHLR_COMPILER_DIRECTORIES "../../../drv/TopBas" )
  list( APPEND TKHLR_COMPILER_DIRECTORIES "../../../src/TopBas" )
  list( APPEND TKHLR_COMPILER_DIRECTORIES "../../../drv/TopCnx" )
  list( APPEND TKHLR_COMPILER_DIRECTORIES "../../../src/TopCnx" )
  list( APPEND TKHLR_COMPILER_DIRECTORIES "../../../drv/Contap" )
  list( APPEND TKHLR_COMPILER_DIRECTORIES "../../../src/Contap" )

if (WIN32)
else()
endif()

  list( APPEND TKHLR_USED_LIBS TKBRep )
  list( APPEND TKHLR_USED_LIBS TKernel )
  list( APPEND TKHLR_USED_LIBS TKMath )
  list( APPEND TKHLR_USED_LIBS TKGeomBase )
  list( APPEND TKHLR_USED_LIBS TKG2d )
  list( APPEND TKHLR_USED_LIBS TKG3d )
  list( APPEND TKHLR_USED_LIBS TKGeomAlgo )
  list( APPEND TKHLR_USED_LIBS TKTopAlgo )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRTopoBRep/HLRTopoBRep_DataMapIteratorOfDataMapOfShapeFaceData_0.cxx" )
  SOURCE_GROUP (HLRTopoBRep FILES "../../../drv/HLRTopoBRep/HLRTopoBRep_DataMapIteratorOfDataMapOfShapeFaceData_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRTopoBRep/HLRTopoBRep_DataMapIteratorOfMapOfShapeListOfVData_0.cxx" )
  SOURCE_GROUP (HLRTopoBRep FILES "../../../drv/HLRTopoBRep/HLRTopoBRep_DataMapIteratorOfMapOfShapeListOfVData_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRTopoBRep/HLRTopoBRep_DataMapNodeOfDataMapOfShapeFaceData_0.cxx" )
  SOURCE_GROUP (HLRTopoBRep FILES "../../../drv/HLRTopoBRep/HLRTopoBRep_DataMapNodeOfDataMapOfShapeFaceData_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRTopoBRep/HLRTopoBRep_DataMapNodeOfMapOfShapeListOfVData_0.cxx" )
  SOURCE_GROUP (HLRTopoBRep FILES "../../../drv/HLRTopoBRep/HLRTopoBRep_DataMapNodeOfMapOfShapeListOfVData_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRTopoBRep/HLRTopoBRep_DataMapOfShapeFaceData_0.cxx" )
  SOURCE_GROUP (HLRTopoBRep FILES "../../../drv/HLRTopoBRep/HLRTopoBRep_DataMapOfShapeFaceData_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRTopoBRep/HLRTopoBRep_ListIteratorOfListOfVData_0.cxx" )
  SOURCE_GROUP (HLRTopoBRep FILES "../../../drv/HLRTopoBRep/HLRTopoBRep_ListIteratorOfListOfVData_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRTopoBRep/HLRTopoBRep_ListNodeOfListOfVData_0.cxx" )
  SOURCE_GROUP (HLRTopoBRep FILES "../../../drv/HLRTopoBRep/HLRTopoBRep_ListNodeOfListOfVData_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRTopoBRep/HLRTopoBRep_ListOfVData_0.cxx" )
  SOURCE_GROUP (HLRTopoBRep FILES "../../../drv/HLRTopoBRep/HLRTopoBRep_ListOfVData_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRTopoBRep/HLRTopoBRep_MapOfShapeListOfVData_0.cxx" )
  SOURCE_GROUP (HLRTopoBRep FILES "../../../drv/HLRTopoBRep/HLRTopoBRep_MapOfShapeListOfVData_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRTopoBRep/HLRTopoBRep_DSFiller.cxx" )
  SOURCE_GROUP (HLRTopoBRep FILES "../../../src/HLRTopoBRep/HLRTopoBRep_DSFiller.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRTopoBRep/HLRTopoBRep_Data.cxx" )
  SOURCE_GROUP (HLRTopoBRep FILES "../../../src/HLRTopoBRep/HLRTopoBRep_Data.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRTopoBRep/HLRTopoBRep_FaceData.cxx" )
  SOURCE_GROUP (HLRTopoBRep FILES "../../../src/HLRTopoBRep/HLRTopoBRep_FaceData.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRTopoBRep/HLRTopoBRep_FaceIsoLiner.cxx" )
  SOURCE_GROUP (HLRTopoBRep FILES "../../../src/HLRTopoBRep/HLRTopoBRep_FaceIsoLiner.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRTopoBRep/HLRTopoBRep_OutLiner.cxx" )
  SOURCE_GROUP (HLRTopoBRep FILES "../../../src/HLRTopoBRep/HLRTopoBRep_OutLiner.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRTopoBRep/HLRTopoBRep_VData.cxx" )
  SOURCE_GROUP (HLRTopoBRep FILES "../../../src/HLRTopoBRep/HLRTopoBRep_VData.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_Array1OfEData_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_Array1OfEData_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_Array1OfFData_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_Array1OfFData_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_CInter_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_CInter_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_CLProps_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_CLProps_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_ExactIntersectionPointOfTheIntPCurvePCurveOfCInter_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_ExactIntersectionPointOfTheIntPCurvePCurveOfCInter_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_IntConicCurveOfCInter_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_IntConicCurveOfCInter_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_InterCSurf_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_InterCSurf_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_ListIteratorOfListOfBPnt2D_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_ListIteratorOfListOfBPnt2D_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_ListIteratorOfListOfBPoint_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_ListIteratorOfListOfBPoint_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_ListNodeOfListOfBPnt2D_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_ListNodeOfListOfBPnt2D_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_ListNodeOfListOfBPoint_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_ListNodeOfListOfBPoint_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_ListOfBPnt2D_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_ListOfBPnt2D_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_ListOfBPoint_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_ListOfBPoint_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfCInter_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_PCLocFOfTheLocateExtPCOfTheProjPCurOfCInter_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_PCLocFOfTheLocateExtPCOfTheProjPCurOfCInter_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_SLProps_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_SLProps_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_SeqOfShapeBounds_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_SeqOfShapeBounds_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_SeqPCOfPCLocFOfTheLocateExtPCOfTheProjPCurOfCInter_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_SeqPCOfPCLocFOfTheLocateExtPCOfTheProjPCurOfCInter_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_SequenceNodeOfSeqOfShapeBounds_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_SequenceNodeOfSeqOfShapeBounds_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_SequenceNodeOfSeqPCOfPCLocFOfTheLocateExtPCOfTheProjPCurOfCInter_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_SequenceNodeOfSeqPCOfPCLocFOfTheLocateExtPCOfTheProjPCurOfCInter_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_TheCSFunctionOfInterCSurf_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_TheCSFunctionOfInterCSurf_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_TheCurveLocatorOfTheProjPCurOfCInter_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_TheCurveLocatorOfTheProjPCurOfCInter_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfCInter_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfCInter_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_TheExactInterCSurf_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_TheExactInterCSurf_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_TheIntConicCurveOfCInter_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_TheIntConicCurveOfCInter_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_TheIntPCurvePCurveOfCInter_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_TheIntPCurvePCurveOfCInter_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_TheInterferenceOfInterCSurf_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_TheInterferenceOfInterCSurf_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_TheIntersectorOfTheIntConicCurveOfCInter_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_TheLocateExtPCOfTheProjPCurOfCInter_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_TheLocateExtPCOfTheProjPCurOfCInter_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_ThePolygonOfInterCSurf_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_ThePolygonOfInterCSurf_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_ThePolygonToolOfInterCSurf_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_ThePolygonToolOfInterCSurf_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_ThePolyhedronOfInterCSurf_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_ThePolyhedronOfInterCSurf_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_ThePolyhedronToolOfInterCSurf_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_ThePolyhedronToolOfInterCSurf_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_TheProjPCurOfCInter_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_TheProjPCurOfCInter_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_TheQuadCurvExactInterCSurf_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_TheQuadCurvExactInterCSurf_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRBRep/HLRBRep_TheQuadCurvFuncOfTheQuadCurvExactInterCSurf_0.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../drv/HLRBRep/HLRBRep_TheQuadCurvFuncOfTheQuadCurvExactInterCSurf_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_Algo.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_Algo.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_AreaLimit.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_AreaLimit.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_BCurveTool.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_BCurveTool.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_BSurfaceTool.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_BSurfaceTool.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_BiPnt2D.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_BiPnt2D.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_BiPoint.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_BiPoint.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_CLPropsATool.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_CLPropsATool.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_Curve.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_Curve.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_CurveTool.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_CurveTool.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_Data.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_Data.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_EdgeBuilder.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_EdgeBuilder.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_EdgeData.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_EdgeData.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_EdgeFaceTool.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_EdgeFaceTool.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_EdgeIList.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_EdgeIList.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_EdgeInterferenceTool.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_EdgeInterferenceTool.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_FaceData.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_FaceData.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_FaceIterator.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_FaceIterator.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_HLRToShape.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_HLRToShape.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_Hider.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_Hider.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_InternalAlgo.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_InternalAlgo.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_Intersector.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_Intersector.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_LineTool.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_LineTool.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_PolyAlgo.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_PolyAlgo.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_PolyHLRToShape.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_PolyHLRToShape.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_SLPropsATool.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_SLPropsATool.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_ShapeBounds.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_ShapeBounds.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_ShapeToHLR.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_ShapeToHLR.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_Surface.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_Surface.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_SurfaceTool.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_SurfaceTool.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRBRep/HLRBRep_VertexList.cxx" )
  SOURCE_GROUP (HLRBRep FILES "../../../src/HLRBRep/HLRBRep_VertexList.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRAlgo/HLRAlgo_Array1OfPHDat_0.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../drv/HLRAlgo/HLRAlgo_Array1OfPHDat_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRAlgo/HLRAlgo_Array1OfPINod_0.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../drv/HLRAlgo/HLRAlgo_Array1OfPINod_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRAlgo/HLRAlgo_Array1OfPISeg_0.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../drv/HLRAlgo/HLRAlgo_Array1OfPISeg_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRAlgo/HLRAlgo_Array1OfTData_0.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../drv/HLRAlgo/HLRAlgo_Array1OfTData_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRAlgo/HLRAlgo_HArray1OfPHDat_0.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../drv/HLRAlgo/HLRAlgo_HArray1OfPHDat_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRAlgo/HLRAlgo_HArray1OfPINod_0.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../drv/HLRAlgo/HLRAlgo_HArray1OfPINod_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRAlgo/HLRAlgo_HArray1OfPISeg_0.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../drv/HLRAlgo/HLRAlgo_HArray1OfPISeg_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRAlgo/HLRAlgo_HArray1OfTData_0.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../drv/HLRAlgo/HLRAlgo_HArray1OfTData_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRAlgo/HLRAlgo_InterferenceList_0.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../drv/HLRAlgo/HLRAlgo_InterferenceList_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRAlgo/HLRAlgo_Interference_0.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../drv/HLRAlgo/HLRAlgo_Interference_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRAlgo/HLRAlgo_ListIteratorOfInterferenceList_0.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../drv/HLRAlgo/HLRAlgo_ListIteratorOfInterferenceList_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRAlgo/HLRAlgo_ListIteratorOfListOfBPoint_0.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../drv/HLRAlgo/HLRAlgo_ListIteratorOfListOfBPoint_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRAlgo/HLRAlgo_ListNodeOfInterferenceList_0.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../drv/HLRAlgo/HLRAlgo_ListNodeOfInterferenceList_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRAlgo/HLRAlgo_ListNodeOfListOfBPoint_0.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../drv/HLRAlgo/HLRAlgo_ListNodeOfListOfBPoint_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/HLRAlgo/HLRAlgo_ListOfBPoint_0.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../drv/HLRAlgo/HLRAlgo_ListOfBPoint_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRAlgo/HLRAlgo.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../src/HLRAlgo/HLRAlgo.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRAlgo/HLRAlgo_BiPoint.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../src/HLRAlgo/HLRAlgo_BiPoint.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRAlgo/HLRAlgo_Coincidence.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../src/HLRAlgo/HLRAlgo_Coincidence.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRAlgo/HLRAlgo_EdgeIterator.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../src/HLRAlgo/HLRAlgo_EdgeIterator.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRAlgo/HLRAlgo_EdgeStatus.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../src/HLRAlgo/HLRAlgo_EdgeStatus.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRAlgo/HLRAlgo_EdgesBlock.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../src/HLRAlgo/HLRAlgo_EdgesBlock.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRAlgo/HLRAlgo_Intersection.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../src/HLRAlgo/HLRAlgo_Intersection.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRAlgo/HLRAlgo_PolyAlgo.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../src/HLRAlgo/HLRAlgo_PolyAlgo.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRAlgo/HLRAlgo_PolyData.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../src/HLRAlgo/HLRAlgo_PolyData.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRAlgo/HLRAlgo_PolyHidingData.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../src/HLRAlgo/HLRAlgo_PolyHidingData.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRAlgo/HLRAlgo_PolyInternalData.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../src/HLRAlgo/HLRAlgo_PolyInternalData.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRAlgo/HLRAlgo_PolyInternalNode.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../src/HLRAlgo/HLRAlgo_PolyInternalNode.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRAlgo/HLRAlgo_PolyInternalSegment.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../src/HLRAlgo/HLRAlgo_PolyInternalSegment.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRAlgo/HLRAlgo_PolyShellData.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../src/HLRAlgo/HLRAlgo_PolyShellData.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRAlgo/HLRAlgo_Projector.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../src/HLRAlgo/HLRAlgo_Projector.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRAlgo/HLRAlgo_TriangleData.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../src/HLRAlgo/HLRAlgo_TriangleData.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/HLRAlgo/HLRAlgo_WiresBlock.cxx" )
  SOURCE_GROUP (HLRAlgo FILES "../../../src/HLRAlgo/HLRAlgo_WiresBlock.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Intrv/Intrv_SequenceNodeOfSequenceOfInterval_0.cxx" )
  SOURCE_GROUP (Intrv FILES "../../../drv/Intrv/Intrv_SequenceNodeOfSequenceOfInterval_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Intrv/Intrv_SequenceOfInterval_0.cxx" )
  SOURCE_GROUP (Intrv FILES "../../../drv/Intrv/Intrv_SequenceOfInterval_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/Intrv/Intrv_Interval.cxx" )
  SOURCE_GROUP (Intrv FILES "../../../src/Intrv/Intrv_Interval.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/Intrv/Intrv_Intervals.cxx" )
  SOURCE_GROUP (Intrv FILES "../../../src/Intrv/Intrv_Intervals.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/TopBas/TopBas_ListIteratorOfListOfTestInterference_0.cxx" )
  SOURCE_GROUP (TopBas FILES "../../../drv/TopBas/TopBas_ListIteratorOfListOfTestInterference_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/TopBas/TopBas_ListNodeOfListOfTestInterference_0.cxx" )
  SOURCE_GROUP (TopBas FILES "../../../drv/TopBas/TopBas_ListNodeOfListOfTestInterference_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/TopBas/TopBas_ListOfTestInterference_0.cxx" )
  SOURCE_GROUP (TopBas FILES "../../../drv/TopBas/TopBas_ListOfTestInterference_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/TopBas/TopBas_TestInterference_0.cxx" )
  SOURCE_GROUP (TopBas FILES "../../../drv/TopBas/TopBas_TestInterference_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/TopCnx/TopCnx_EdgeFaceTransition.cxx" )
  SOURCE_GROUP (TopCnx FILES "../../../src/TopCnx/TopCnx_EdgeFaceTransition.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_Contour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_Contour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_HContTool_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_HContTool_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_HCurve2dTool_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_HCurve2dTool_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_SequenceNodeOfSequenceOfIWLineOfTheIWalkingOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_SequenceNodeOfSequenceOfIWLineOfTheIWalkingOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_SequenceNodeOfSequenceOfPathPointOfTheSearchOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_SequenceNodeOfSequenceOfPathPointOfTheSearchOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_SequenceNodeOfSequenceOfSegmentOfTheSearchOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_SequenceNodeOfSequenceOfSegmentOfTheSearchOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_SequenceNodeOfTheSequenceOfLineOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_SequenceNodeOfTheSequenceOfLineOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_SequenceNodeOfTheSequenceOfPointOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_SequenceNodeOfTheSequenceOfPointOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_SequenceOfIWLineOfTheIWalkingOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_SequenceOfIWLineOfTheIWalkingOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_SequenceOfPathPointOfTheSearchOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_SequenceOfPathPointOfTheSearchOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_SequenceOfSegmentOfTheSearchOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_SequenceOfSegmentOfTheSearchOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_TheArcFunctionOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_TheArcFunctionOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_TheHSequenceOfPointOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_TheHSequenceOfPointOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_TheIWLineOfTheIWalkingOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_TheIWLineOfTheIWalkingOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_TheIWalkingOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_TheIWalkingOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_TheLineOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_TheLineOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_ThePathPointOfTheSearchOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_ThePathPointOfTheSearchOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_ThePointOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_ThePointOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_TheSearchInsideOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_TheSearchInsideOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_TheSearchOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_TheSearchOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_TheSegmentOfTheSearchOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_TheSegmentOfTheSearchOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_TheSequenceOfLineOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_TheSequenceOfLineOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_TheSequenceOfPointOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_TheSequenceOfPointOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_TheSurfFunctionOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_TheSurfFunctionOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../drv/Contap/Contap_TheSurfPropsOfContour_0.cxx" )
  SOURCE_GROUP (Contap FILES "../../../drv/Contap/Contap_TheSurfPropsOfContour_0.cxx")

  list( APPEND TKHLR_USED_SRCFILES "../../../src/Contap/Contap_ContAna.cxx" )
  SOURCE_GROUP (Contap FILES "../../../src/Contap/Contap_ContAna.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKHLR)
 add_library( TKHLR SHARED ${TKHLR_USED_SRCFILES} )

 set_property(TARGET TKHLR PROPERTY FOLDER ModelingAlgorithms)

 install( TARGETS TKHLR
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKHLR.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKHLR PROPERTIES COMPILE_FLAGS "${TKHLR_PRECOMPILED_DEFS}" )
 include_directories( ${TKHLR_COMPILER_DIRECTORIES} )
 target_link_libraries( TKHLR ${TKHLR_USED_LIBS} )
endif()
