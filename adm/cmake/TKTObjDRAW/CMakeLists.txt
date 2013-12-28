project(TKTObjDRAW)

if (WIN32)
  list( APPEND TKTObjDRAW_PRECOMPILED_DEFS "-D__TObjDRAW_DLL" )
  string( REGEX REPLACE ";" " " TKTObjDRAW_PRECOMPILED_DEFS "${TKTObjDRAW_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKTObjDRAW_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKTObjDRAW_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKTObjDRAW_COMPILER_DIRECTORIES "../../../drv/TObjDRAW" )
  list( APPEND TKTObjDRAW_COMPILER_DIRECTORIES "../../../src/TObjDRAW" )

if (WIN32)
else()
endif()

  list( APPEND TKTObjDRAW_USED_LIBS TKernel )
  list( APPEND TKTObjDRAW_USED_LIBS TKCDF )
  list( APPEND TKTObjDRAW_USED_LIBS TKLCAF )
  list( APPEND TKTObjDRAW_USED_LIBS TKTObj )
  list( APPEND TKTObjDRAW_USED_LIBS TKMath )
  list( APPEND TKTObjDRAW_USED_LIBS TKDraw )
  list( APPEND TKTObjDRAW_USED_LIBS TKDCAF )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKTObjDRAW_USED_SRCFILES "../../../src/TObjDRAW/TObjDRAW.cxx" )
  SOURCE_GROUP (TObjDRAW FILES "../../../src/TObjDRAW/TObjDRAW.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKTObjDRAW)
 add_library( TKTObjDRAW SHARED ${TKTObjDRAW_USED_SRCFILES} )

 set_property(TARGET TKTObjDRAW PROPERTY FOLDER Draw)

 install( TARGETS TKTObjDRAW
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKTObjDRAW.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKTObjDRAW PROPERTIES COMPILE_FLAGS "${TKTObjDRAW_PRECOMPILED_DEFS}" )
 include_directories( ${TKTObjDRAW_COMPILER_DIRECTORIES} )
 target_link_libraries( TKTObjDRAW ${TKTObjDRAW_USED_LIBS} )
endif()
