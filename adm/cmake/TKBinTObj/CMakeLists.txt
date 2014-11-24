project(TKBinTObj)

if (WIN32)
  list( APPEND TKBinTObj_PRECOMPILED_DEFS "-D__BinTObjDrivers_DLL" )
  string( REGEX REPLACE ";" " " TKBinTObj_PRECOMPILED_DEFS "${TKBinTObj_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKBinTObj_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}/inc")
    list( APPEND TKBinTObj_COMPILER_DIRECTORIES "${BUILD_PATCH_DIR}/inc" )
  ENDIF()
  IF(EXISTS "${CMAKE_SOURCE_DIR}/inc")
    list( APPEND TKBinTObj_COMPILER_DIRECTORIES "${CMAKE_SOURCE_DIR}/inc" )
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "")
    IF(EXISTS "${BUILD_PATCH_DIR}/drv/BinTObjDrivers")
      list( APPEND TKBinTObj_COMPILER_DIRECTORIES "${BUILD_PATCH_DIR}/drv/BinTObjDrivers" )
    ENDIF()
    IF(EXISTS "${BUILD_PATCH_DIR}/src/BinTObjDrivers")
      list( APPEND TKBinTObj_COMPILER_DIRECTORIES "${BUILD_PATCH_DIR}/src/BinTObjDrivers" )
    ENDIF()

  ENDIF()

  IF(EXISTS "${CMAKE_SOURCE_DIR}/drv/BinTObjDrivers")
    list( APPEND TKBinTObj_COMPILER_DIRECTORIES "${CMAKE_SOURCE_DIR}/drv/BinTObjDrivers" )
  ENDIF()
  IF(EXISTS "${CMAKE_SOURCE_DIR}/src/BinTObjDrivers")
    list( APPEND TKBinTObj_COMPILER_DIRECTORIES "${CMAKE_SOURCE_DIR}/src/BinTObjDrivers" )
  ENDIF()

IF (WIN32)
  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "")
  ENDIF()

ELSE()
  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "")
  ENDIF()

ENDIF()

  list( APPEND TKBinTObj_USED_LIBS TKCDF )
  list( APPEND TKBinTObj_USED_LIBS TKernel )
  list( APPEND TKBinTObj_USED_LIBS TKTObj )
  list( APPEND TKBinTObj_USED_LIBS TKMath )
  list( APPEND TKBinTObj_USED_LIBS TKLCAF )
  list( APPEND TKBinTObj_USED_LIBS TKBinL )

if (WIN32)
elseif(APPLE)
elseif(ANDROID)
else()
endif()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers.cxx")
    list( APPEND TKBinTObj_USED_SRCFILES "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers.cxx" )
    SOURCE_GROUP (BinTObjDrivers FILES "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers.cxx")
      list( APPEND TKBinTObj_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers.cxx" )
      SOURCE_GROUP (BinTObjDrivers FILES "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers.cxx")
    ENDIF()
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_DocumentRetrievalDriver.cxx")
    list( APPEND TKBinTObj_USED_SRCFILES "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_DocumentRetrievalDriver.cxx" )
    SOURCE_GROUP (BinTObjDrivers FILES "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_DocumentRetrievalDriver.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_DocumentRetrievalDriver.cxx")
      list( APPEND TKBinTObj_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_DocumentRetrievalDriver.cxx" )
      SOURCE_GROUP (BinTObjDrivers FILES "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_DocumentRetrievalDriver.cxx")
    ENDIF()
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_DocumentStorageDriver.cxx")
    list( APPEND TKBinTObj_USED_SRCFILES "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_DocumentStorageDriver.cxx" )
    SOURCE_GROUP (BinTObjDrivers FILES "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_DocumentStorageDriver.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_DocumentStorageDriver.cxx")
      list( APPEND TKBinTObj_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_DocumentStorageDriver.cxx" )
      SOURCE_GROUP (BinTObjDrivers FILES "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_DocumentStorageDriver.cxx")
    ENDIF()
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_IntSparseArrayDriver.cxx")
    list( APPEND TKBinTObj_USED_SRCFILES "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_IntSparseArrayDriver.cxx" )
    SOURCE_GROUP (BinTObjDrivers FILES "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_IntSparseArrayDriver.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_IntSparseArrayDriver.cxx")
      list( APPEND TKBinTObj_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_IntSparseArrayDriver.cxx" )
      SOURCE_GROUP (BinTObjDrivers FILES "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_IntSparseArrayDriver.cxx")
    ENDIF()
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_ModelDriver.cxx")
    list( APPEND TKBinTObj_USED_SRCFILES "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_ModelDriver.cxx" )
    SOURCE_GROUP (BinTObjDrivers FILES "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_ModelDriver.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_ModelDriver.cxx")
      list( APPEND TKBinTObj_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_ModelDriver.cxx" )
      SOURCE_GROUP (BinTObjDrivers FILES "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_ModelDriver.cxx")
    ENDIF()
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_ObjectDriver.cxx")
    list( APPEND TKBinTObj_USED_SRCFILES "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_ObjectDriver.cxx" )
    SOURCE_GROUP (BinTObjDrivers FILES "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_ObjectDriver.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_ObjectDriver.cxx")
      list( APPEND TKBinTObj_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_ObjectDriver.cxx" )
      SOURCE_GROUP (BinTObjDrivers FILES "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_ObjectDriver.cxx")
    ENDIF()
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_ReferenceDriver.cxx")
    list( APPEND TKBinTObj_USED_SRCFILES "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_ReferenceDriver.cxx" )
    SOURCE_GROUP (BinTObjDrivers FILES "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_ReferenceDriver.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_ReferenceDriver.cxx")
      list( APPEND TKBinTObj_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_ReferenceDriver.cxx" )
      SOURCE_GROUP (BinTObjDrivers FILES "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_ReferenceDriver.cxx")
    ENDIF()
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_XYZDriver.cxx")
    list( APPEND TKBinTObj_USED_SRCFILES "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_XYZDriver.cxx" )
    SOURCE_GROUP (BinTObjDrivers FILES "${BUILD_PATCH_DIR}//src/BinTObjDrivers/BinTObjDrivers_XYZDriver.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_XYZDriver.cxx")
      list( APPEND TKBinTObj_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_XYZDriver.cxx" )
      SOURCE_GROUP (BinTObjDrivers FILES "${CMAKE_SOURCE_DIR}//src/BinTObjDrivers/BinTObjDrivers_XYZDriver.cxx")
    ENDIF()
  ENDIF()


IF (WIN32)
ELSE()

  IF (APPLE)

  ENDIF()

ENDIF()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKBinTObj)
 add_library( TKBinTObj SHARED ${TKBinTObj_USED_SRCFILES} )

 set_property(TARGET TKBinTObj PROPERTY FOLDER ApplicationFramework)

 install( TARGETS TKBinTObj
                                 RUNTIME DESTINATION "${INSTALL_DIR}/${OS_WITH_BIT}/${COMPILER}/bin${BUILD_POSTFIX}"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/${OS_WITH_BIT}/${COMPILER}/lib${BUILD_POSTFIX}"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/${OS_WITH_BIT}/${COMPILER}/lib${BUILD_POSTFIX}")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bind/Debug/TKBinTObj.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/${OS_WITH_BIT}/${COMPILER}/bin${BUILD_POSTFIX}")
 endif()


 set_target_properties( TKBinTObj PROPERTIES COMPILE_FLAGS "${TKBinTObj_PRECOMPILED_DEFS}" )
 include_directories( ${TKBinTObj_COMPILER_DIRECTORIES} )
 target_link_libraries( TKBinTObj ${TKBinTObj_USED_LIBS} )
endif()
