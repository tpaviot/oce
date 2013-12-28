project(TKDCAF)

if (WIN32)
  list( APPEND TKDCAF_PRECOMPILED_DEFS "-D__DDF_DLL" )
  list( APPEND TKDCAF_PRECOMPILED_DEFS "-D__DDocStd_DLL" )
  list( APPEND TKDCAF_PRECOMPILED_DEFS "-D__DNaming_DLL" )
  list( APPEND TKDCAF_PRECOMPILED_DEFS "-D__DDataStd_DLL" )
  list( APPEND TKDCAF_PRECOMPILED_DEFS "-D__DPrsStd_DLL" )
  list( APPEND TKDCAF_PRECOMPILED_DEFS "-D__DrawDim_DLL" )
  string( REGEX REPLACE ";" " " TKDCAF_PRECOMPILED_DEFS "${TKDCAF_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKDCAF_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKDCAF_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKDCAF_COMPILER_DIRECTORIES "../../../drv/DDF" )
  list( APPEND TKDCAF_COMPILER_DIRECTORIES "../../../src/DDF" )
  list( APPEND TKDCAF_COMPILER_DIRECTORIES "../../../drv/DDocStd" )
  list( APPEND TKDCAF_COMPILER_DIRECTORIES "../../../src/DDocStd" )
  list( APPEND TKDCAF_COMPILER_DIRECTORIES "../../../drv/DNaming" )
  list( APPEND TKDCAF_COMPILER_DIRECTORIES "../../../src/DNaming" )
  list( APPEND TKDCAF_COMPILER_DIRECTORIES "../../../drv/DDataStd" )
  list( APPEND TKDCAF_COMPILER_DIRECTORIES "../../../src/DDataStd" )
  list( APPEND TKDCAF_COMPILER_DIRECTORIES "../../../drv/DPrsStd" )
  list( APPEND TKDCAF_COMPILER_DIRECTORIES "../../../src/DPrsStd" )
  list( APPEND TKDCAF_COMPILER_DIRECTORIES "../../../drv/DrawDim" )
  list( APPEND TKDCAF_COMPILER_DIRECTORIES "../../../src/DrawDim" )

if (WIN32)
else()
endif()

  list( APPEND TKDCAF_USED_LIBS TKGeomBase )
  list( APPEND TKDCAF_USED_LIBS TKBRep )
  list( APPEND TKDCAF_USED_LIBS TKGeomAlgo )
  list( APPEND TKDCAF_USED_LIBS TKernel )
  list( APPEND TKDCAF_USED_LIBS TKMath )
  list( APPEND TKDCAF_USED_LIBS TKG2d )
  list( APPEND TKDCAF_USED_LIBS TKG3d )
  list( APPEND TKDCAF_USED_LIBS TKDraw )
  list( APPEND TKDCAF_USED_LIBS TKCDF )
  list( APPEND TKDCAF_USED_LIBS TKV3d )
  list( APPEND TKDCAF_USED_LIBS TKNIS )
  list( APPEND TKDCAF_USED_LIBS TKService )
  list( APPEND TKDCAF_USED_LIBS TKLCAF )
  list( APPEND TKDCAF_USED_LIBS TKFillet )
  list( APPEND TKDCAF_USED_LIBS TKTopAlgo )
  list( APPEND TKDCAF_USED_LIBS TKPrim )
  list( APPEND TKDCAF_USED_LIBS TKBool )
  list( APPEND TKDCAF_USED_LIBS TKBO )
  list( APPEND TKDCAF_USED_LIBS TKCAF )
  list( APPEND TKDCAF_USED_LIBS TKViewerTest )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKDCAF_USED_SRCFILES "../../../drv/DDF/DDF_StackIteratorOfTransactionStack_0.cxx" )
  SOURCE_GROUP (DDF FILES "../../../drv/DDF/DDF_StackIteratorOfTransactionStack_0.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../drv/DDF/DDF_StackNodeOfTransactionStack_0.cxx" )
  SOURCE_GROUP (DDF FILES "../../../drv/DDF/DDF_StackNodeOfTransactionStack_0.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../drv/DDF/DDF_TransactionStack_0.cxx" )
  SOURCE_GROUP (DDF FILES "../../../drv/DDF/DDF_TransactionStack_0.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDF/DDF.cxx" )
  SOURCE_GROUP (DDF FILES "../../../src/DDF/DDF.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDF/DDF_AttributeBrowser.cxx" )
  SOURCE_GROUP (DDF FILES "../../../src/DDF/DDF_AttributeBrowser.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDF/DDF_BasicCommands.cxx" )
  SOURCE_GROUP (DDF FILES "../../../src/DDF/DDF_BasicCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDF/DDF_Browser.cxx" )
  SOURCE_GROUP (DDF FILES "../../../src/DDF/DDF_Browser.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDF/DDF_BrowserCommands.cxx" )
  SOURCE_GROUP (DDF FILES "../../../src/DDF/DDF_BrowserCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDF/DDF_Data.cxx" )
  SOURCE_GROUP (DDF FILES "../../../src/DDF/DDF_Data.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDF/DDF_DataCommands.cxx" )
  SOURCE_GROUP (DDF FILES "../../../src/DDF/DDF_DataCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDF/DDF_IOStream.cxx" )
  SOURCE_GROUP (DDF FILES "../../../src/DDF/DDF_IOStream.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDF/DDF_Transaction.cxx" )
  SOURCE_GROUP (DDF FILES "../../../src/DDF/DDF_Transaction.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDF/DDF_TransactionCommands.cxx" )
  SOURCE_GROUP (DDF FILES "../../../src/DDF/DDF_TransactionCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDocStd/DDocStd.cxx" )
  SOURCE_GROUP (DDocStd FILES "../../../src/DDocStd/DDocStd.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDocStd/DDocStd_ApplicationCommands.cxx" )
  SOURCE_GROUP (DDocStd FILES "../../../src/DDocStd/DDocStd_ApplicationCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDocStd/DDocStd_DocumentCommands.cxx" )
  SOURCE_GROUP (DDocStd FILES "../../../src/DDocStd/DDocStd_DocumentCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDocStd/DDocStd_DrawDocument.cxx" )
  SOURCE_GROUP (DDocStd FILES "../../../src/DDocStd/DDocStd_DrawDocument.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDocStd/DDocStd_MTMCommands.cxx" )
  SOURCE_GROUP (DDocStd FILES "../../../src/DDocStd/DDocStd_MTMCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDocStd/DDocStd_ToolsCommands.cxx" )
  SOURCE_GROUP (DDocStd FILES "../../../src/DDocStd/DDocStd_ToolsCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../drv/DNaming/DNaming_DataMapIteratorOfDataMapOfShapeOfName_0.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../drv/DNaming/DNaming_DataMapIteratorOfDataMapOfShapeOfName_0.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../drv/DNaming/DNaming_DataMapNodeOfDataMapOfShapeOfName_0.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../drv/DNaming/DNaming_DataMapNodeOfDataMapOfShapeOfName_0.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../drv/DNaming/DNaming_DataMapOfShapeOfName_0.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../drv/DNaming/DNaming_DataMapOfShapeOfName_0.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DNaming/DNaming.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../src/DNaming/DNaming.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DNaming/DNaming_BasicCommands.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../src/DNaming/DNaming_BasicCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DNaming/DNaming_BooleanOperationDriver.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../src/DNaming/DNaming_BooleanOperationDriver.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DNaming/DNaming_BoxDriver.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../src/DNaming/DNaming_BoxDriver.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DNaming/DNaming_CylinderDriver.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../src/DNaming/DNaming_CylinderDriver.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DNaming/DNaming_FilletDriver.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../src/DNaming/DNaming_FilletDriver.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DNaming/DNaming_Line3DDriver.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../src/DNaming/DNaming_Line3DDriver.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DNaming/DNaming_ModelingCommands.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../src/DNaming/DNaming_ModelingCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DNaming/DNaming_PointDriver.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../src/DNaming/DNaming_PointDriver.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DNaming/DNaming_PrismDriver.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../src/DNaming/DNaming_PrismDriver.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DNaming/DNaming_RevolutionDriver.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../src/DNaming/DNaming_RevolutionDriver.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DNaming/DNaming_SelectionCommands.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../src/DNaming/DNaming_SelectionCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DNaming/DNaming_SelectionDriver.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../src/DNaming/DNaming_SelectionDriver.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DNaming/DNaming_SphereDriver.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../src/DNaming/DNaming_SphereDriver.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DNaming/DNaming_ToolsCommands.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../src/DNaming/DNaming_ToolsCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DNaming/DNaming_TransformationDriver.cxx" )
  SOURCE_GROUP (DNaming FILES "../../../src/DNaming/DNaming_TransformationDriver.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDataStd/DDataStd.cxx" )
  SOURCE_GROUP (DDataStd FILES "../../../src/DDataStd/DDataStd.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDataStd/DDataStd_BasicCommands.cxx" )
  SOURCE_GROUP (DDataStd FILES "../../../src/DDataStd/DDataStd_BasicCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDataStd/DDataStd_ConstraintCommands.cxx" )
  SOURCE_GROUP (DDataStd FILES "../../../src/DDataStd/DDataStd_ConstraintCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDataStd/DDataStd_DatumCommands.cxx" )
  SOURCE_GROUP (DDataStd FILES "../../../src/DDataStd/DDataStd_DatumCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDataStd/DDataStd_DrawDisplayCommands.cxx" )
  SOURCE_GROUP (DDataStd FILES "../../../src/DDataStd/DDataStd_DrawDisplayCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDataStd/DDataStd_DrawDriver.cxx" )
  SOURCE_GROUP (DDataStd FILES "../../../src/DDataStd/DDataStd_DrawDriver.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDataStd/DDataStd_DrawPresentation.cxx" )
  SOURCE_GROUP (DDataStd FILES "../../../src/DDataStd/DDataStd_DrawPresentation.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDataStd/DDataStd_NameCommands.cxx" )
  SOURCE_GROUP (DDataStd FILES "../../../src/DDataStd/DDataStd_NameCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDataStd/DDataStd_NamedShapeCommands.cxx" )
  SOURCE_GROUP (DDataStd FILES "../../../src/DDataStd/DDataStd_NamedShapeCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDataStd/DDataStd_ObjectCommands.cxx" )
  SOURCE_GROUP (DDataStd FILES "../../../src/DDataStd/DDataStd_ObjectCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDataStd/DDataStd_TreeBrowser.cxx" )
  SOURCE_GROUP (DDataStd FILES "../../../src/DDataStd/DDataStd_TreeBrowser.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DDataStd/DDataStd_TreeCommands.cxx" )
  SOURCE_GROUP (DDataStd FILES "../../../src/DDataStd/DDataStd_TreeCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DPrsStd/DPrsStd.cxx" )
  SOURCE_GROUP (DPrsStd FILES "../../../src/DPrsStd/DPrsStd.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DPrsStd/DPrsStd_AISPresentationCommands.cxx" )
  SOURCE_GROUP (DPrsStd FILES "../../../src/DPrsStd/DPrsStd_AISPresentationCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DPrsStd/DPrsStd_AISViewerCommands.cxx" )
  SOURCE_GROUP (DPrsStd FILES "../../../src/DPrsStd/DPrsStd_AISViewerCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DrawDim/DrawDim.cxx" )
  SOURCE_GROUP (DrawDim FILES "../../../src/DrawDim/DrawDim.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DrawDim/DrawDim_Angle.cxx" )
  SOURCE_GROUP (DrawDim FILES "../../../src/DrawDim/DrawDim_Angle.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DrawDim/DrawDim_Dimension.cxx" )
  SOURCE_GROUP (DrawDim FILES "../../../src/DrawDim/DrawDim_Dimension.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DrawDim/DrawDim_Distance.cxx" )
  SOURCE_GROUP (DrawDim FILES "../../../src/DrawDim/DrawDim_Distance.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DrawDim/DrawDim_PlanarAngle.cxx" )
  SOURCE_GROUP (DrawDim FILES "../../../src/DrawDim/DrawDim_PlanarAngle.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DrawDim/DrawDim_PlanarDiameter.cxx" )
  SOURCE_GROUP (DrawDim FILES "../../../src/DrawDim/DrawDim_PlanarDiameter.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DrawDim/DrawDim_PlanarDimension.cxx" )
  SOURCE_GROUP (DrawDim FILES "../../../src/DrawDim/DrawDim_PlanarDimension.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DrawDim/DrawDim_PlanarDimensionCommands.cxx" )
  SOURCE_GROUP (DrawDim FILES "../../../src/DrawDim/DrawDim_PlanarDimensionCommands.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DrawDim/DrawDim_PlanarDistance.cxx" )
  SOURCE_GROUP (DrawDim FILES "../../../src/DrawDim/DrawDim_PlanarDistance.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DrawDim/DrawDim_PlanarRadius.cxx" )
  SOURCE_GROUP (DrawDim FILES "../../../src/DrawDim/DrawDim_PlanarRadius.cxx")

  list( APPEND TKDCAF_USED_SRCFILES "../../../src/DrawDim/DrawDim_Radius.cxx" )
  SOURCE_GROUP (DrawDim FILES "../../../src/DrawDim/DrawDim_Radius.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKDCAF)
 add_library( TKDCAF SHARED ${TKDCAF_USED_SRCFILES} )

 set_property(TARGET TKDCAF PROPERTY FOLDER Draw)

 install( TARGETS TKDCAF
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKDCAF.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKDCAF PROPERTIES COMPILE_FLAGS "${TKDCAF_PRECOMPILED_DEFS}" )
 include_directories( ${TKDCAF_COMPILER_DIRECTORIES} )
 target_link_libraries( TKDCAF ${TKDCAF_USED_LIBS} )
endif()
