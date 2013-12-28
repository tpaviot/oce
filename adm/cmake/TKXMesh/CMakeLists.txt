project(TKXMesh)

if (WIN32)
  list( APPEND TKXMesh_PRECOMPILED_DEFS "-D__XBRepMesh_DLL" )
  string( REGEX REPLACE ";" " " TKXMesh_PRECOMPILED_DEFS "${TKXMesh_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKXMesh_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKXMesh_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKXMesh_COMPILER_DIRECTORIES "../../../drv/XBRepMesh" )
  list( APPEND TKXMesh_COMPILER_DIRECTORIES "../../../src/XBRepMesh" )

if (WIN32)
else()
endif()

  list( APPEND TKXMesh_USED_LIBS TKBRep )
  list( APPEND TKXMesh_USED_LIBS TKMath )
  list( APPEND TKXMesh_USED_LIBS TKernel )
  list( APPEND TKXMesh_USED_LIBS TKG2d )
  list( APPEND TKXMesh_USED_LIBS TKMesh )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKXMesh_USED_SRCFILES "../../../src/XBRepMesh/XBRepMesh.cxx" )
  SOURCE_GROUP (XBRepMesh FILES "../../../src/XBRepMesh/XBRepMesh.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKXMesh)
 add_library( TKXMesh SHARED ${TKXMesh_USED_SRCFILES} )

 set_property(TARGET TKXMesh PROPERTY FOLDER ModelingAlgorithms)

 install( TARGETS TKXMesh
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKXMesh.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKXMesh PROPERTIES COMPILE_FLAGS "${TKXMesh_PRECOMPILED_DEFS}" )
 include_directories( ${TKXMesh_COMPILER_DIRECTORIES} )
 target_link_libraries( TKXMesh ${TKXMesh_USED_LIBS} )
endif()
