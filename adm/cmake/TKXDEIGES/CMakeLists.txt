project(TKXDEIGES)

if (WIN32)
  list( APPEND TKXDEIGES_PRECOMPILED_DEFS "-D__IGESCAFControl_DLL" )
  string( REGEX REPLACE ";" " " TKXDEIGES_PRECOMPILED_DEFS "${TKXDEIGES_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKXDEIGES_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKXDEIGES_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKXDEIGES_COMPILER_DIRECTORIES "../../../drv/IGESCAFControl" )
  list( APPEND TKXDEIGES_COMPILER_DIRECTORIES "../../../src/IGESCAFControl" )

if (WIN32)
else()
endif()

  list( APPEND TKXDEIGES_USED_LIBS TKBRep )
  list( APPEND TKXDEIGES_USED_LIBS TKernel )
  list( APPEND TKXDEIGES_USED_LIBS TKMath )
  list( APPEND TKXDEIGES_USED_LIBS TKXSBase )
  list( APPEND TKXDEIGES_USED_LIBS TKCDF )
  list( APPEND TKXDEIGES_USED_LIBS TKLCAF )
  list( APPEND TKXDEIGES_USED_LIBS TKG2d )
  list( APPEND TKXDEIGES_USED_LIBS TKXCAF )
  list( APPEND TKXDEIGES_USED_LIBS TKIGES )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKXDEIGES_USED_SRCFILES "../../../src/IGESCAFControl/IGESCAFControl.cxx" )
  SOURCE_GROUP (IGESCAFControl FILES "../../../src/IGESCAFControl/IGESCAFControl.cxx")

  list( APPEND TKXDEIGES_USED_SRCFILES "../../../src/IGESCAFControl/IGESCAFControl_Reader.cxx" )
  SOURCE_GROUP (IGESCAFControl FILES "../../../src/IGESCAFControl/IGESCAFControl_Reader.cxx")

  list( APPEND TKXDEIGES_USED_SRCFILES "../../../src/IGESCAFControl/IGESCAFControl_Writer.cxx" )
  SOURCE_GROUP (IGESCAFControl FILES "../../../src/IGESCAFControl/IGESCAFControl_Writer.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKXDEIGES)
 add_library( TKXDEIGES SHARED ${TKXDEIGES_USED_SRCFILES} )

 set_property(TARGET TKXDEIGES PROPERTY FOLDER DataExchange)

 install( TARGETS TKXDEIGES
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKXDEIGES.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKXDEIGES PROPERTIES COMPILE_FLAGS "${TKXDEIGES_PRECOMPILED_DEFS}" )
 include_directories( ${TKXDEIGES_COMPILER_DIRECTORIES} )
 target_link_libraries( TKXDEIGES ${TKXDEIGES_USED_LIBS} )
endif()
