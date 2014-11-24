project(TKXmlTObj)

if (WIN32)
  list( APPEND TKXmlTObj_PRECOMPILED_DEFS "-D__XmlTObjDrivers_DLL" )
  string( REGEX REPLACE ";" " " TKXmlTObj_PRECOMPILED_DEFS "${TKXmlTObj_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKXmlTObj_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}/inc")
    list( APPEND TKXmlTObj_COMPILER_DIRECTORIES "${BUILD_PATCH_DIR}/inc" )
  ENDIF()
  IF(EXISTS "${CMAKE_SOURCE_DIR}/inc")
    list( APPEND TKXmlTObj_COMPILER_DIRECTORIES "${CMAKE_SOURCE_DIR}/inc" )
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "")
    IF(EXISTS "${BUILD_PATCH_DIR}/drv/XmlTObjDrivers")
      list( APPEND TKXmlTObj_COMPILER_DIRECTORIES "${BUILD_PATCH_DIR}/drv/XmlTObjDrivers" )
    ENDIF()
    IF(EXISTS "${BUILD_PATCH_DIR}/src/XmlTObjDrivers")
      list( APPEND TKXmlTObj_COMPILER_DIRECTORIES "${BUILD_PATCH_DIR}/src/XmlTObjDrivers" )
    ENDIF()

  ENDIF()

  IF(EXISTS "${CMAKE_SOURCE_DIR}/drv/XmlTObjDrivers")
    list( APPEND TKXmlTObj_COMPILER_DIRECTORIES "${CMAKE_SOURCE_DIR}/drv/XmlTObjDrivers" )
  ENDIF()
  IF(EXISTS "${CMAKE_SOURCE_DIR}/src/XmlTObjDrivers")
    list( APPEND TKXmlTObj_COMPILER_DIRECTORIES "${CMAKE_SOURCE_DIR}/src/XmlTObjDrivers" )
  ENDIF()

IF (WIN32)
  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "")
  ENDIF()

ELSE()
  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "")
  ENDIF()

ENDIF()

  list( APPEND TKXmlTObj_USED_LIBS TKCDF )
  list( APPEND TKXmlTObj_USED_LIBS TKernel )
  list( APPEND TKXmlTObj_USED_LIBS TKTObj )
  list( APPEND TKXmlTObj_USED_LIBS TKMath )
  list( APPEND TKXmlTObj_USED_LIBS TKLCAF )
  list( APPEND TKXmlTObj_USED_LIBS TKXmlL )

if (WIN32)
elseif(APPLE)
elseif(ANDROID)
else()
endif()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers.cxx")
    list( APPEND TKXmlTObj_USED_SRCFILES "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers.cxx" )
    SOURCE_GROUP (XmlTObjDrivers FILES "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers.cxx")
      list( APPEND TKXmlTObj_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers.cxx" )
      SOURCE_GROUP (XmlTObjDrivers FILES "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers.cxx")
    ENDIF()
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_DocumentRetrievalDriver.cxx")
    list( APPEND TKXmlTObj_USED_SRCFILES "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_DocumentRetrievalDriver.cxx" )
    SOURCE_GROUP (XmlTObjDrivers FILES "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_DocumentRetrievalDriver.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_DocumentRetrievalDriver.cxx")
      list( APPEND TKXmlTObj_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_DocumentRetrievalDriver.cxx" )
      SOURCE_GROUP (XmlTObjDrivers FILES "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_DocumentRetrievalDriver.cxx")
    ENDIF()
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_DocumentStorageDriver.cxx")
    list( APPEND TKXmlTObj_USED_SRCFILES "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_DocumentStorageDriver.cxx" )
    SOURCE_GROUP (XmlTObjDrivers FILES "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_DocumentStorageDriver.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_DocumentStorageDriver.cxx")
      list( APPEND TKXmlTObj_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_DocumentStorageDriver.cxx" )
      SOURCE_GROUP (XmlTObjDrivers FILES "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_DocumentStorageDriver.cxx")
    ENDIF()
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_IntSparseArrayDriver.cxx")
    list( APPEND TKXmlTObj_USED_SRCFILES "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_IntSparseArrayDriver.cxx" )
    SOURCE_GROUP (XmlTObjDrivers FILES "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_IntSparseArrayDriver.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_IntSparseArrayDriver.cxx")
      list( APPEND TKXmlTObj_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_IntSparseArrayDriver.cxx" )
      SOURCE_GROUP (XmlTObjDrivers FILES "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_IntSparseArrayDriver.cxx")
    ENDIF()
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_ModelDriver.cxx")
    list( APPEND TKXmlTObj_USED_SRCFILES "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_ModelDriver.cxx" )
    SOURCE_GROUP (XmlTObjDrivers FILES "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_ModelDriver.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_ModelDriver.cxx")
      list( APPEND TKXmlTObj_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_ModelDriver.cxx" )
      SOURCE_GROUP (XmlTObjDrivers FILES "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_ModelDriver.cxx")
    ENDIF()
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_ObjectDriver.cxx")
    list( APPEND TKXmlTObj_USED_SRCFILES "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_ObjectDriver.cxx" )
    SOURCE_GROUP (XmlTObjDrivers FILES "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_ObjectDriver.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_ObjectDriver.cxx")
      list( APPEND TKXmlTObj_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_ObjectDriver.cxx" )
      SOURCE_GROUP (XmlTObjDrivers FILES "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_ObjectDriver.cxx")
    ENDIF()
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_ReferenceDriver.cxx")
    list( APPEND TKXmlTObj_USED_SRCFILES "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_ReferenceDriver.cxx" )
    SOURCE_GROUP (XmlTObjDrivers FILES "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_ReferenceDriver.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_ReferenceDriver.cxx")
      list( APPEND TKXmlTObj_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_ReferenceDriver.cxx" )
      SOURCE_GROUP (XmlTObjDrivers FILES "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_ReferenceDriver.cxx")
    ENDIF()
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_XYZDriver.cxx")
    list( APPEND TKXmlTObj_USED_SRCFILES "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_XYZDriver.cxx" )
    SOURCE_GROUP (XmlTObjDrivers FILES "${BUILD_PATCH_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_XYZDriver.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_XYZDriver.cxx")
      list( APPEND TKXmlTObj_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_XYZDriver.cxx" )
      SOURCE_GROUP (XmlTObjDrivers FILES "${CMAKE_SOURCE_DIR}//src/XmlTObjDrivers/XmlTObjDrivers_XYZDriver.cxx")
    ENDIF()
  ENDIF()


IF (WIN32)
ELSE()

  IF (APPLE)

  ENDIF()

ENDIF()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKXmlTObj)
 add_library( TKXmlTObj SHARED ${TKXmlTObj_USED_SRCFILES} )

 set_property(TARGET TKXmlTObj PROPERTY FOLDER ApplicationFramework)

 install( TARGETS TKXmlTObj
                                 RUNTIME DESTINATION "${INSTALL_DIR}/${OS_WITH_BIT}/${COMPILER}/bin${BUILD_POSTFIX}"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/${OS_WITH_BIT}/${COMPILER}/lib${BUILD_POSTFIX}"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/${OS_WITH_BIT}/${COMPILER}/lib${BUILD_POSTFIX}")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bind/Debug/TKXmlTObj.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/${OS_WITH_BIT}/${COMPILER}/bin${BUILD_POSTFIX}")
 endif()


 set_target_properties( TKXmlTObj PROPERTIES COMPILE_FLAGS "${TKXmlTObj_PRECOMPILED_DEFS}" )
 include_directories( ${TKXmlTObj_COMPILER_DIRECTORIES} )
 target_link_libraries( TKXmlTObj ${TKXmlTObj_USED_LIBS} )
endif()
