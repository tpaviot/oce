project(TKXDESTEP)

if (WIN32)
  list( APPEND TKXDESTEP_PRECOMPILED_DEFS "-D__STEPCAFControl_DLL" )
  string( REGEX REPLACE ";" " " TKXDESTEP_PRECOMPILED_DEFS "${TKXDESTEP_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKXDESTEP_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKXDESTEP_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKXDESTEP_COMPILER_DIRECTORIES "../../../drv/STEPCAFControl" )
  list( APPEND TKXDESTEP_COMPILER_DIRECTORIES "../../../src/STEPCAFControl" )

if (WIN32)
else()
endif()

  list( APPEND TKXDESTEP_USED_LIBS TKBRep )
  list( APPEND TKXDESTEP_USED_LIBS TKSTEPAttr )
  list( APPEND TKXDESTEP_USED_LIBS TKernel )
  list( APPEND TKXDESTEP_USED_LIBS TKMath )
  list( APPEND TKXDESTEP_USED_LIBS TKXSBase )
  list( APPEND TKXDESTEP_USED_LIBS TKG2d )
  list( APPEND TKXDESTEP_USED_LIBS TKCAF )
  list( APPEND TKXDESTEP_USED_LIBS TKSTEPBase )
  list( APPEND TKXDESTEP_USED_LIBS TKCDF )
  list( APPEND TKXDESTEP_USED_LIBS TKLCAF )
  list( APPEND TKXDESTEP_USED_LIBS TKG3d )
  list( APPEND TKXDESTEP_USED_LIBS TKXCAF )
  list( APPEND TKXDESTEP_USED_LIBS TKSTEP )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapIteratorOfDataMapOfLabelExternFile_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapIteratorOfDataMapOfLabelExternFile_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapIteratorOfDataMapOfLabelShape_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapIteratorOfDataMapOfLabelShape_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapIteratorOfDataMapOfPDExternFile_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapIteratorOfDataMapOfPDExternFile_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapIteratorOfDataMapOfSDRExternFile_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapIteratorOfDataMapOfSDRExternFile_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapIteratorOfDataMapOfShapePD_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapIteratorOfDataMapOfShapePD_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapIteratorOfDataMapOfShapeSDR_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapIteratorOfDataMapOfShapeSDR_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapNodeOfDataMapOfLabelExternFile_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapNodeOfDataMapOfLabelExternFile_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapNodeOfDataMapOfLabelShape_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapNodeOfDataMapOfLabelShape_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapNodeOfDataMapOfPDExternFile_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapNodeOfDataMapOfPDExternFile_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapNodeOfDataMapOfSDRExternFile_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapNodeOfDataMapOfSDRExternFile_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapNodeOfDataMapOfShapePD_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapNodeOfDataMapOfShapePD_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapNodeOfDataMapOfShapeSDR_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapNodeOfDataMapOfShapeSDR_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapOfLabelExternFile_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapOfLabelExternFile_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapOfLabelShape_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapOfLabelShape_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapOfPDExternFile_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapOfPDExternFile_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapOfSDRExternFile_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapOfSDRExternFile_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapOfShapePD_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapOfShapePD_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapOfShapeSDR_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DataMapOfShapeSDR_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_DictionaryOfExternFile_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_DictionaryOfExternFile_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_IteratorOfDictionaryOfExternFile_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_IteratorOfDictionaryOfExternFile_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../drv/STEPCAFControl/STEPCAFControl_StackItemOfDictionaryOfExternFile_0.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../drv/STEPCAFControl/STEPCAFControl_StackItemOfDictionaryOfExternFile_0.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../src/STEPCAFControl/STEPCAFControl_ActorWrite.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../src/STEPCAFControl/STEPCAFControl_ActorWrite.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../src/STEPCAFControl/STEPCAFControl_Controller.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../src/STEPCAFControl/STEPCAFControl_Controller.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../src/STEPCAFControl/STEPCAFControl_ExternFile.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../src/STEPCAFControl/STEPCAFControl_ExternFile.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../src/STEPCAFControl/STEPCAFControl_Reader.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../src/STEPCAFControl/STEPCAFControl_Reader.cxx")

  list( APPEND TKXDESTEP_USED_SRCFILES "../../../src/STEPCAFControl/STEPCAFControl_Writer.cxx" )
  SOURCE_GROUP (STEPCAFControl FILES "../../../src/STEPCAFControl/STEPCAFControl_Writer.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKXDESTEP)
 add_library( TKXDESTEP SHARED ${TKXDESTEP_USED_SRCFILES} )

 set_property(TARGET TKXDESTEP PROPERTY FOLDER DataExchange)

 install( TARGETS TKXDESTEP
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKXDESTEP.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKXDESTEP PROPERTIES COMPILE_FLAGS "${TKXDESTEP_PRECOMPILED_DEFS}" )
 include_directories( ${TKXDESTEP_COMPILER_DIRECTORIES} )
 target_link_libraries( TKXDESTEP ${TKXDESTEP_USED_LIBS} )
endif()
