project(TKFeat)

if (WIN32)
  list( APPEND TKFeat_PRECOMPILED_DEFS "-D__LocOpe_DLL" )
  list( APPEND TKFeat_PRECOMPILED_DEFS "-D__BRepFeat_DLL" )
  string( REGEX REPLACE ";" " " TKFeat_PRECOMPILED_DEFS "${TKFeat_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKFeat_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKFeat_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKFeat_COMPILER_DIRECTORIES "../../../drv/LocOpe" )
  list( APPEND TKFeat_COMPILER_DIRECTORIES "../../../src/LocOpe" )
  list( APPEND TKFeat_COMPILER_DIRECTORIES "../../../drv/BRepFeat" )
  list( APPEND TKFeat_COMPILER_DIRECTORIES "../../../src/BRepFeat" )

if (WIN32)
else()
endif()

  list( APPEND TKFeat_USED_LIBS TKBRep )
  list( APPEND TKFeat_USED_LIBS TKTopAlgo )
  list( APPEND TKFeat_USED_LIBS TKGeomAlgo )
  list( APPEND TKFeat_USED_LIBS TKMath )
  list( APPEND TKFeat_USED_LIBS TKernel )
  list( APPEND TKFeat_USED_LIBS TKGeomBase )
  list( APPEND TKFeat_USED_LIBS TKPrim )
  list( APPEND TKFeat_USED_LIBS TKG2d )
  list( APPEND TKFeat_USED_LIBS TKBO )
  list( APPEND TKFeat_USED_LIBS TKG3d )
  list( APPEND TKFeat_USED_LIBS TKBool )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKFeat_USED_SRCFILES "../../../drv/LocOpe/LocOpe_DataMapIteratorOfDataMapOfShapePnt_0.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../drv/LocOpe/LocOpe_DataMapIteratorOfDataMapOfShapePnt_0.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../drv/LocOpe/LocOpe_DataMapNodeOfDataMapOfShapePnt_0.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../drv/LocOpe/LocOpe_DataMapNodeOfDataMapOfShapePnt_0.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../drv/LocOpe/LocOpe_DataMapOfShapePnt_0.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../drv/LocOpe/LocOpe_DataMapOfShapePnt_0.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../drv/LocOpe/LocOpe_SequenceNodeOfSequenceOfCirc_0.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../drv/LocOpe/LocOpe_SequenceNodeOfSequenceOfCirc_0.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../drv/LocOpe/LocOpe_SequenceNodeOfSequenceOfLin_0.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../drv/LocOpe/LocOpe_SequenceNodeOfSequenceOfLin_0.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../drv/LocOpe/LocOpe_SequenceNodeOfSequenceOfPntFace_0.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../drv/LocOpe/LocOpe_SequenceNodeOfSequenceOfPntFace_0.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../drv/LocOpe/LocOpe_SequenceOfCirc_0.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../drv/LocOpe/LocOpe_SequenceOfCirc_0.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../drv/LocOpe/LocOpe_SequenceOfLin_0.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../drv/LocOpe/LocOpe_SequenceOfLin_0.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../drv/LocOpe/LocOpe_SequenceOfPntFace_0.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../drv/LocOpe/LocOpe_SequenceOfPntFace_0.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_BuildShape.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_BuildShape.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_BuildWires.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_BuildWires.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_CSIntersector.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_CSIntersector.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_CurveShapeIntersector.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_CurveShapeIntersector.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_DPrism.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_DPrism.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_FindEdges.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_FindEdges.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_FindEdgesInFace.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_FindEdgesInFace.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_GeneratedShape.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_GeneratedShape.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_Generator.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_Generator.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_GluedShape.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_GluedShape.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_Gluer.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_Gluer.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_HBuilder.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_HBuilder.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_LinearForm.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_LinearForm.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_Pipe.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_Pipe.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_PntFace.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_PntFace.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_Prism.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_Prism.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_ProjectedWires.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_ProjectedWires.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_Revol.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_Revol.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_RevolutionForm.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_RevolutionForm.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_SplitDrafts.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_SplitDrafts.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_SplitShape.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_SplitShape.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_Spliter.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_Spliter.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/LocOpe/LocOpe_WiresOnShape.cxx" )
  SOURCE_GROUP (LocOpe FILES "../../../src/LocOpe/LocOpe_WiresOnShape.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/BRepFeat/BRepFeat.cxx" )
  SOURCE_GROUP (BRepFeat FILES "../../../src/BRepFeat/BRepFeat.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/BRepFeat/BRepFeat_Builder.cxx" )
  SOURCE_GROUP (BRepFeat FILES "../../../src/BRepFeat/BRepFeat_Builder.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/BRepFeat/BRepFeat_Form.cxx" )
  SOURCE_GROUP (BRepFeat FILES "../../../src/BRepFeat/BRepFeat_Form.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/BRepFeat/BRepFeat_Gluer.cxx" )
  SOURCE_GROUP (BRepFeat FILES "../../../src/BRepFeat/BRepFeat_Gluer.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/BRepFeat/BRepFeat_MakeCylindricalHole.cxx" )
  SOURCE_GROUP (BRepFeat FILES "../../../src/BRepFeat/BRepFeat_MakeCylindricalHole.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/BRepFeat/BRepFeat_MakeDPrism.cxx" )
  SOURCE_GROUP (BRepFeat FILES "../../../src/BRepFeat/BRepFeat_MakeDPrism.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/BRepFeat/BRepFeat_MakeLinearForm.cxx" )
  SOURCE_GROUP (BRepFeat FILES "../../../src/BRepFeat/BRepFeat_MakeLinearForm.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/BRepFeat/BRepFeat_MakePipe.cxx" )
  SOURCE_GROUP (BRepFeat FILES "../../../src/BRepFeat/BRepFeat_MakePipe.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/BRepFeat/BRepFeat_MakePrism.cxx" )
  SOURCE_GROUP (BRepFeat FILES "../../../src/BRepFeat/BRepFeat_MakePrism.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/BRepFeat/BRepFeat_MakeRevol.cxx" )
  SOURCE_GROUP (BRepFeat FILES "../../../src/BRepFeat/BRepFeat_MakeRevol.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/BRepFeat/BRepFeat_MakeRevolutionForm.cxx" )
  SOURCE_GROUP (BRepFeat FILES "../../../src/BRepFeat/BRepFeat_MakeRevolutionForm.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/BRepFeat/BRepFeat_RibSlot.cxx" )
  SOURCE_GROUP (BRepFeat FILES "../../../src/BRepFeat/BRepFeat_RibSlot.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/BRepFeat/BRepFeat_SplitShape.cxx" )
  SOURCE_GROUP (BRepFeat FILES "../../../src/BRepFeat/BRepFeat_SplitShape.cxx")

  list( APPEND TKFeat_USED_SRCFILES "../../../src/BRepFeat/BRepFeat_trace.cxx" )
  SOURCE_GROUP (BRepFeat FILES "../../../src/BRepFeat/BRepFeat_trace.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKFeat)
 add_library( TKFeat SHARED ${TKFeat_USED_SRCFILES} )

 set_property(TARGET TKFeat PROPERTY FOLDER ModelingAlgorithms)

 install( TARGETS TKFeat
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKFeat.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKFeat PROPERTIES COMPILE_FLAGS "${TKFeat_PRECOMPILED_DEFS}" )
 include_directories( ${TKFeat_COMPILER_DIRECTORIES} )
 target_link_libraries( TKFeat ${TKFeat_USED_LIBS} )
endif()
