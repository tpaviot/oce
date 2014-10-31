project(FWOSPlugin)

if (WIN32)
  list( APPEND FWOSPlugin_PRECOMPILED_DEFS "-D__FWOSDriver_DLL" )
  string( REGEX REPLACE ";" " " FWOSPlugin_PRECOMPILED_DEFS "${FWOSPlugin_PRECOMPILED_DEFS}")
endif()

  list( APPEND FWOSPlugin_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}/inc")
    list( APPEND FWOSPlugin_COMPILER_DIRECTORIES "${BUILD_PATCH_DIR}/inc" )
  ENDIF()
  IF(EXISTS "${CMAKE_SOURCE_DIR}/inc")
    list( APPEND FWOSPlugin_COMPILER_DIRECTORIES "${CMAKE_SOURCE_DIR}/inc" )
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "")
    IF(EXISTS "${BUILD_PATCH_DIR}/drv/FWOSDriver")
      list( APPEND FWOSPlugin_COMPILER_DIRECTORIES "${BUILD_PATCH_DIR}/drv/FWOSDriver" )
    ENDIF()
    IF(EXISTS "${BUILD_PATCH_DIR}/src/FWOSDriver")
      list( APPEND FWOSPlugin_COMPILER_DIRECTORIES "${BUILD_PATCH_DIR}/src/FWOSDriver" )
    ENDIF()

  ENDIF()

  IF(EXISTS "${CMAKE_SOURCE_DIR}/drv/FWOSDriver")
    list( APPEND FWOSPlugin_COMPILER_DIRECTORIES "${CMAKE_SOURCE_DIR}/drv/FWOSDriver" )
  ENDIF()
  IF(EXISTS "${CMAKE_SOURCE_DIR}/src/FWOSDriver")
    list( APPEND FWOSPlugin_COMPILER_DIRECTORIES "${CMAKE_SOURCE_DIR}/src/FWOSDriver" )
  ENDIF()

IF (WIN32)
  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "")
  ENDIF()

ELSE()
  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "")
  ENDIF()

ENDIF()

  list( APPEND FWOSPlugin_USED_LIBS TKernel )
  list( APPEND FWOSPlugin_USED_LIBS TKCDF )

if (WIN32)
elseif(APPLE)
else()
endif()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/FWOSDriver/FWOSDriver.cxx")
    list( APPEND FWOSPlugin_USED_SRCFILES "${BUILD_PATCH_DIR}//src/FWOSDriver/FWOSDriver.cxx" )
    SOURCE_GROUP (FWOSDriver FILES "${BUILD_PATCH_DIR}//src/FWOSDriver/FWOSDriver.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/FWOSDriver/FWOSDriver.cxx")
      list( APPEND FWOSPlugin_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/FWOSDriver/FWOSDriver.cxx" )
      SOURCE_GROUP (FWOSDriver FILES "${CMAKE_SOURCE_DIR}//src/FWOSDriver/FWOSDriver.cxx")
    ENDIF()
  ENDIF()

  IF(NOT "${BUILD_PATCH_DIR}" STREQUAL "" AND EXISTS "${BUILD_PATCH_DIR}//src/FWOSDriver/FWOSDriver_DriverFactory.cxx")
    list( APPEND FWOSPlugin_USED_SRCFILES "${BUILD_PATCH_DIR}//src/FWOSDriver/FWOSDriver_DriverFactory.cxx" )
    SOURCE_GROUP (FWOSDriver FILES "${BUILD_PATCH_DIR}//src/FWOSDriver/FWOSDriver_DriverFactory.cxx")
  ELSE()
    IF(EXISTS "${CMAKE_SOURCE_DIR}//src/FWOSDriver/FWOSDriver_DriverFactory.cxx")
      list( APPEND FWOSPlugin_USED_SRCFILES "${CMAKE_SOURCE_DIR}//src/FWOSDriver/FWOSDriver_DriverFactory.cxx" )
      SOURCE_GROUP (FWOSDriver FILES "${CMAKE_SOURCE_DIR}//src/FWOSDriver/FWOSDriver_DriverFactory.cxx")
    ENDIF()
  ENDIF()


IF (WIN32)
ELSE()

  IF (APPLE)

  ENDIF()

ENDIF()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheFWOSPlugin)
 add_library( FWOSPlugin SHARED ${FWOSPlugin_USED_SRCFILES} )

 set_property(TARGET FWOSPlugin PROPERTY FOLDER ApplicationFramework)

 install( TARGETS FWOSPlugin
                                 RUNTIME DESTINATION "${INSTALL_DIR}/${OS_WITH_BIT}/${COMPILER}/bin${BUILD_SUFFIX}"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/${OS_WITH_BIT}/${COMPILER}/lib${BUILD_SUFFIX}"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/${OS_WITH_BIT}/${COMPILER}/lib${BUILD_SUFFIX}")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/FWOSPlugin.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/${OS_WITH_BIT}/${COMPILER}/bin${BUILD_SUFFIX}")
 endif()


 set_target_properties( FWOSPlugin PROPERTIES COMPILE_FLAGS "${FWOSPlugin_PRECOMPILED_DEFS}" )
 include_directories( ${FWOSPlugin_COMPILER_DIRECTORIES} )
 target_link_libraries( FWOSPlugin ${FWOSPlugin_USED_LIBS} )
endif()
