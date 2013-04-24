project(TKOffset)

if (WIN32)
  list( APPEND TKOffset_PRECOMPILED_DEFS "-D__BRepOffsetAPI_DLL" )
  list( APPEND TKOffset_PRECOMPILED_DEFS "-D__Draft_DLL" )
  list( APPEND TKOffset_PRECOMPILED_DEFS "-D__BRepOffset_DLL" )
  list( APPEND TKOffset_PRECOMPILED_DEFS "-D__BiTgte_DLL" )
  string( REGEX REPLACE ";" " " TKOffset_PRECOMPILED_DEFS "${TKOffset_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKOffset_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKOffset_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKOffset_COMPILER_DIRECTORIES "../../../drv/BRepOffsetAPI" )
  list( APPEND TKOffset_COMPILER_DIRECTORIES "../../../src/BRepOffsetAPI" )
  list( APPEND TKOffset_COMPILER_DIRECTORIES "../../../drv/Draft" )
  list( APPEND TKOffset_COMPILER_DIRECTORIES "../../../src/Draft" )
  list( APPEND TKOffset_COMPILER_DIRECTORIES "../../../drv/BRepOffset" )
  list( APPEND TKOffset_COMPILER_DIRECTORIES "../../../src/BRepOffset" )
  list( APPEND TKOffset_COMPILER_DIRECTORIES "../../../drv/BiTgte" )
  list( APPEND TKOffset_COMPILER_DIRECTORIES "../../../src/BiTgte" )

if (WIN32)
else()
endif()

  list( APPEND TKOffset_USED_LIBS TKFillet )
  list( APPEND TKOffset_USED_LIBS TKBRep )
  list( APPEND TKOffset_USED_LIBS TKTopAlgo )
  list( APPEND TKOffset_USED_LIBS TKMath )
  list( APPEND TKOffset_USED_LIBS TKernel )
  list( APPEND TKOffset_USED_LIBS TKGeomBase )
  list( APPEND TKOffset_USED_LIBS TKG2d )
  list( APPEND TKOffset_USED_LIBS TKG3d )
  list( APPEND TKOffset_USED_LIBS TKGeomAlgo )
  list( APPEND TKOffset_USED_LIBS TKShHealing )
  list( APPEND TKOffset_USED_LIBS TKBO )
  list( APPEND TKOffset_USED_LIBS TKPrim )
  list( APPEND TKOffset_USED_LIBS TKBool )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BRepOffsetAPI/BRepOffsetAPI_SequenceNodeOfSequenceOfSequenceOfReal_0.cxx" )
  SOURCE_GROUP (BRepOffsetAPI FILES "../../../drv/BRepOffsetAPI/BRepOffsetAPI_SequenceNodeOfSequenceOfSequenceOfReal_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BRepOffsetAPI/BRepOffsetAPI_SequenceNodeOfSequenceOfSequenceOfShape_0.cxx" )
  SOURCE_GROUP (BRepOffsetAPI FILES "../../../drv/BRepOffsetAPI/BRepOffsetAPI_SequenceNodeOfSequenceOfSequenceOfShape_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BRepOffsetAPI/BRepOffsetAPI_SequenceOfSequenceOfReal_0.cxx" )
  SOURCE_GROUP (BRepOffsetAPI FILES "../../../drv/BRepOffsetAPI/BRepOffsetAPI_SequenceOfSequenceOfReal_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BRepOffsetAPI/BRepOffsetAPI_SequenceOfSequenceOfShape_0.cxx" )
  SOURCE_GROUP (BRepOffsetAPI FILES "../../../drv/BRepOffsetAPI/BRepOffsetAPI_SequenceOfSequenceOfShape_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_DraftAngle.cxx" )
  SOURCE_GROUP (BRepOffsetAPI FILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_DraftAngle.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_FindContigousEdges.cxx" )
  SOURCE_GROUP (BRepOffsetAPI FILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_FindContigousEdges.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_MakeDraft.cxx" )
  SOURCE_GROUP (BRepOffsetAPI FILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_MakeDraft.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_MakeEvolved.cxx" )
  SOURCE_GROUP (BRepOffsetAPI FILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_MakeEvolved.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_MakeFilling.cxx" )
  SOURCE_GROUP (BRepOffsetAPI FILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_MakeFilling.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_MakeOffset.cxx" )
  SOURCE_GROUP (BRepOffsetAPI FILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_MakeOffset.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_MakeOffsetShape.cxx" )
  SOURCE_GROUP (BRepOffsetAPI FILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_MakeOffsetShape.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_MakePipe.cxx" )
  SOURCE_GROUP (BRepOffsetAPI FILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_MakePipe.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_MakePipeShell.cxx" )
  SOURCE_GROUP (BRepOffsetAPI FILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_MakePipeShell.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_MakeThickSolid.cxx" )
  SOURCE_GROUP (BRepOffsetAPI FILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_MakeThickSolid.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_MiddlePath.cxx" )
  SOURCE_GROUP (BRepOffsetAPI FILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_MiddlePath.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_NormalProjection.cxx" )
  SOURCE_GROUP (BRepOffsetAPI FILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_NormalProjection.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_ThruSections.cxx" )
  SOURCE_GROUP (BRepOffsetAPI FILES "../../../src/BRepOffsetAPI/BRepOffsetAPI_ThruSections.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/Draft/Draft_DataMapIteratorOfDataMapOfEdgeEdgeInfo_0.cxx" )
  SOURCE_GROUP (Draft FILES "../../../drv/Draft/Draft_DataMapIteratorOfDataMapOfEdgeEdgeInfo_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/Draft/Draft_DataMapIteratorOfDataMapOfFaceFaceInfo_0.cxx" )
  SOURCE_GROUP (Draft FILES "../../../drv/Draft/Draft_DataMapIteratorOfDataMapOfFaceFaceInfo_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/Draft/Draft_DataMapIteratorOfDataMapOfVertexVertexInfo_0.cxx" )
  SOURCE_GROUP (Draft FILES "../../../drv/Draft/Draft_DataMapIteratorOfDataMapOfVertexVertexInfo_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/Draft/Draft_DataMapNodeOfDataMapOfEdgeEdgeInfo_0.cxx" )
  SOURCE_GROUP (Draft FILES "../../../drv/Draft/Draft_DataMapNodeOfDataMapOfEdgeEdgeInfo_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/Draft/Draft_DataMapNodeOfDataMapOfFaceFaceInfo_0.cxx" )
  SOURCE_GROUP (Draft FILES "../../../drv/Draft/Draft_DataMapNodeOfDataMapOfFaceFaceInfo_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/Draft/Draft_DataMapNodeOfDataMapOfVertexVertexInfo_0.cxx" )
  SOURCE_GROUP (Draft FILES "../../../drv/Draft/Draft_DataMapNodeOfDataMapOfVertexVertexInfo_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/Draft/Draft_DataMapOfEdgeEdgeInfo_0.cxx" )
  SOURCE_GROUP (Draft FILES "../../../drv/Draft/Draft_DataMapOfEdgeEdgeInfo_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/Draft/Draft_DataMapOfFaceFaceInfo_0.cxx" )
  SOURCE_GROUP (Draft FILES "../../../drv/Draft/Draft_DataMapOfFaceFaceInfo_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/Draft/Draft_DataMapOfVertexVertexInfo_0.cxx" )
  SOURCE_GROUP (Draft FILES "../../../drv/Draft/Draft_DataMapOfVertexVertexInfo_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/Draft/Draft.cxx" )
  SOURCE_GROUP (Draft FILES "../../../src/Draft/Draft.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/Draft/Draft_EdgeInfo.cxx" )
  SOURCE_GROUP (Draft FILES "../../../src/Draft/Draft_EdgeInfo.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/Draft/Draft_FaceInfo.cxx" )
  SOURCE_GROUP (Draft FILES "../../../src/Draft/Draft_FaceInfo.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/Draft/Draft_Modification.cxx" )
  SOURCE_GROUP (Draft FILES "../../../src/Draft/Draft_Modification.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/Draft/Draft_Modification_1.cxx" )
  SOURCE_GROUP (Draft FILES "../../../src/Draft/Draft_Modification_1.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/Draft/Draft_VertexInfo.cxx" )
  SOURCE_GROUP (Draft FILES "../../../src/Draft/Draft_VertexInfo.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BRepOffset/BRepOffset_DataMapIteratorOfDataMapOfShapeListOfInterval_0.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../drv/BRepOffset/BRepOffset_DataMapIteratorOfDataMapOfShapeListOfInterval_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BRepOffset/BRepOffset_DataMapIteratorOfDataMapOfShapeMapOfShape_0.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../drv/BRepOffset/BRepOffset_DataMapIteratorOfDataMapOfShapeMapOfShape_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BRepOffset/BRepOffset_DataMapIteratorOfDataMapOfShapeOffset_0.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../drv/BRepOffset/BRepOffset_DataMapIteratorOfDataMapOfShapeOffset_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BRepOffset/BRepOffset_DataMapNodeOfDataMapOfShapeListOfInterval_0.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../drv/BRepOffset/BRepOffset_DataMapNodeOfDataMapOfShapeListOfInterval_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BRepOffset/BRepOffset_DataMapNodeOfDataMapOfShapeMapOfShape_0.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../drv/BRepOffset/BRepOffset_DataMapNodeOfDataMapOfShapeMapOfShape_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BRepOffset/BRepOffset_DataMapNodeOfDataMapOfShapeOffset_0.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../drv/BRepOffset/BRepOffset_DataMapNodeOfDataMapOfShapeOffset_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BRepOffset/BRepOffset_DataMapOfShapeListOfInterval_0.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../drv/BRepOffset/BRepOffset_DataMapOfShapeListOfInterval_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BRepOffset/BRepOffset_DataMapOfShapeMapOfShape_0.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../drv/BRepOffset/BRepOffset_DataMapOfShapeMapOfShape_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BRepOffset/BRepOffset_DataMapOfShapeOffset_0.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../drv/BRepOffset/BRepOffset_DataMapOfShapeOffset_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BRepOffset/BRepOffset_ListIteratorOfListOfInterval_0.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../drv/BRepOffset/BRepOffset_ListIteratorOfListOfInterval_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BRepOffset/BRepOffset_ListNodeOfListOfInterval_0.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../drv/BRepOffset/BRepOffset_ListNodeOfListOfInterval_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BRepOffset/BRepOffset_ListOfInterval_0.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../drv/BRepOffset/BRepOffset_ListOfInterval_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffset/BRepOffset.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../src/BRepOffset/BRepOffset.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffset/BRepOffset_Analyse.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../src/BRepOffset/BRepOffset_Analyse.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffset/BRepOffset_Inter2d.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../src/BRepOffset/BRepOffset_Inter2d.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffset/BRepOffset_Inter3d.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../src/BRepOffset/BRepOffset_Inter3d.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffset/BRepOffset_Interval.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../src/BRepOffset/BRepOffset_Interval.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffset/BRepOffset_MakeLoops.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../src/BRepOffset/BRepOffset_MakeLoops.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffset/BRepOffset_MakeOffset.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../src/BRepOffset/BRepOffset_MakeOffset.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffset/BRepOffset_Offset.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../src/BRepOffset/BRepOffset_Offset.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BRepOffset/BRepOffset_Tool.cxx" )
  SOURCE_GROUP (BRepOffset FILES "../../../src/BRepOffset/BRepOffset_Tool.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BiTgte/BiTgte_DataMapIteratorOfDataMapOfShapeBox_0.cxx" )
  SOURCE_GROUP (BiTgte FILES "../../../drv/BiTgte/BiTgte_DataMapIteratorOfDataMapOfShapeBox_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BiTgte/BiTgte_DataMapNodeOfDataMapOfShapeBox_0.cxx" )
  SOURCE_GROUP (BiTgte FILES "../../../drv/BiTgte/BiTgte_DataMapNodeOfDataMapOfShapeBox_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BiTgte/BiTgte_DataMapOfShapeBox_0.cxx" )
  SOURCE_GROUP (BiTgte FILES "../../../drv/BiTgte/BiTgte_DataMapOfShapeBox_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BiTgte/BiTgte_HCurveOnEdge_0.cxx" )
  SOURCE_GROUP (BiTgte FILES "../../../drv/BiTgte/BiTgte_HCurveOnEdge_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../drv/BiTgte/BiTgte_HCurveOnVertex_0.cxx" )
  SOURCE_GROUP (BiTgte FILES "../../../drv/BiTgte/BiTgte_HCurveOnVertex_0.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BiTgte/BiTgte_Blend.cxx" )
  SOURCE_GROUP (BiTgte FILES "../../../src/BiTgte/BiTgte_Blend.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BiTgte/BiTgte_CurveOnEdge.cxx" )
  SOURCE_GROUP (BiTgte FILES "../../../src/BiTgte/BiTgte_CurveOnEdge.cxx")

  list( APPEND TKOffset_USED_SRCFILES "../../../src/BiTgte/BiTgte_CurveOnVertex.cxx" )
  SOURCE_GROUP (BiTgte FILES "../../../src/BiTgte/BiTgte_CurveOnVertex.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKOffset)
 add_library( TKOffset SHARED ${TKOffset_USED_SRCFILES} )

 set_property(TARGET TKOffset PROPERTY FOLDER ModelingAlgorithms)

 install( TARGETS TKOffset
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKOffset.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKOffset PROPERTIES COMPILE_FLAGS "${TKOffset_PRECOMPILED_DEFS}" )
 include_directories( ${TKOffset_COMPILER_DIRECTORIES} )
 target_link_libraries( TKOffset ${TKOffset_USED_LIBS} )
endif()
