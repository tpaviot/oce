project(TKXMesh)

if (WIN32)
  list( APPEND TKXMesh_PRECOMPILED_DEFS "-D__XBRepMesh_DLL" )
  string( REGEX REPLACE ";" " " TKXMesh_PRECOMPILED_DEFS "${TKXMesh_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKXMesh_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}/inc")
    list( APPEND TKXMesh_COMPILER_DIRECTORIES "${BUILD_PATCH_DIR}/inc" )
  ENDIF()
  IF(EXISTS "${CMAKE_SOURCE_DIR}/inc")
    list( APPEND TKXMesh_COMPILER_DIRECTORIES "${CMAKE_SOURCE_DIR}/inc" )
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "")
    IF(EXISTS "${BUILD_PATCH_DIR}/drv/XBRepMesh")
      list( APPEND TKXMesh_COMPILER_DIRECTORIES "${BUILD_PATCH_DIR}/drv/XBRepMesh" )
    ENDIF()
    IF(EXISTS "${BUILD_PATCH_DIR}/src/XBRepMesh")
      list( APPEND TKXMesh_COMPILER_DIRECTORIES "${BUILD_PATCH_DIR}/src/XBRepMesh" )
    ENDIF()

  ENDIF()

  IF(EXISTS "${CMAKE_SOURCE_DIR}/drv/XBRepMesh")
    list( APPEND TKXMesh_COMPILER_DIRECTORIES "${CMAKE_SOURCE_DIR}/drv/XBRepMesh" )
  ENDIF()
  IF(EXISTS "${CMAKE_SOURCE_DIR}/src/XBRepMesh")
    list( APPEND TKXMesh_COMPILER_DIRECTORIES "${CMAKE_SOURCE_DIR}/src/XBRepMesh" )
  ENDIF()

IF (WIN32)
  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "")
  ENDIF()

ELSE()
  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "")
  ENDIF()

ENDIF()

  list( APPEND TKXMesh_USED_LIBS TKBRep )
  list( APPEND TKXMesh_USED_LIBS TKMath )
  list( APPEND TKXMesh_USED_LIBS TKernel )
  list( APPEND TKXMesh_USED_LIBS TKG2d )
  list( APPEND TKXMesh_USED_LIBS TKMesh )

if (WIN32)
elseif(APPLE)
elseif(ANDROID)
else()
endif()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/XBRepMesh/XBRepMesh.cxx")
    list( APPEND TKXMesh_USED_SRCFILES "${BUILD_PATCH_DIR}//src/XBRepMesh/XBRepMesh.cxx" )
    SOURCE_GROUP (XBRepMesh FILES "${BUILD_PATCH_DIR}//src/XBRepMesh/XBRepMesh.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/XBRepMesh/XBRepMesh.cxx")
      list( APPEND TKXMesh_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/XBRepMesh/XBRepMesh.cxx" )
      SOURCE_GROUP (XBRepMesh FILES "${CMAKE_SOURCE_DIR}//src/XBRepMesh/XBRepMesh.cxx")
    ENDIF()
  ENDIF()


IF (WIN32)
ELSE()

  IF (APPLE)

  ENDIF()

ENDIF()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKXMesh)
 add_library( TKXMesh SHARED ${TKXMesh_USED_SRCFILES} )

 set_property(TARGET TKXMesh PROPERTY FOLDER ModelingAlgorithms)

 install( TARGETS TKXMesh
                                 RUNTIME DESTINATION "${INSTALL_DIR}/${OS_WITH_BIT}/${COMPILER}/bin${BUILD_POSTFIX}"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/${OS_WITH_BIT}/${COMPILER}/lib${BUILD_POSTFIX}"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/${OS_WITH_BIT}/${COMPILER}/lib${BUILD_POSTFIX}")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bind/Debug/TKXMesh.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/${OS_WITH_BIT}/${COMPILER}/bin${BUILD_POSTFIX}")
 endif()


 set_target_properties( TKXMesh PROPERTIES COMPILE_FLAGS "${TKXMesh_PRECOMPILED_DEFS}" )
 include_directories( ${TKXMesh_COMPILER_DIRECTORIES} )
 target_link_libraries( TKXMesh ${TKXMesh_USED_LIBS} )
endif()
