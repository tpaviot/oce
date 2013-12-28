project(FWOSPlugin)

if (WIN32)
  list( APPEND FWOSPlugin_PRECOMPILED_DEFS "-D__FWOSDriver_DLL" )
  string( REGEX REPLACE ";" " " FWOSPlugin_PRECOMPILED_DEFS "${FWOSPlugin_PRECOMPILED_DEFS}")
endif()

  list( APPEND FWOSPlugin_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND FWOSPlugin_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND FWOSPlugin_COMPILER_DIRECTORIES "../../../drv/FWOSDriver" )
  list( APPEND FWOSPlugin_COMPILER_DIRECTORIES "../../../src/FWOSDriver" )

if (WIN32)
else()
endif()

  list( APPEND FWOSPlugin_USED_LIBS TKernel )
  list( APPEND FWOSPlugin_USED_LIBS TKCDF )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND FWOSPlugin_USED_SRCFILES "../../../src/FWOSDriver/FWOSDriver.cxx" )
  SOURCE_GROUP (FWOSDriver FILES "../../../src/FWOSDriver/FWOSDriver.cxx")

  list( APPEND FWOSPlugin_USED_SRCFILES "../../../src/FWOSDriver/FWOSDriver_Driver.cxx" )
  SOURCE_GROUP (FWOSDriver FILES "../../../src/FWOSDriver/FWOSDriver_Driver.cxx")

  list( APPEND FWOSPlugin_USED_SRCFILES "../../../src/FWOSDriver/FWOSDriver_DriverFactory.cxx" )
  SOURCE_GROUP (FWOSDriver FILES "../../../src/FWOSDriver/FWOSDriver_DriverFactory.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheFWOSPlugin)
 add_library( FWOSPlugin SHARED ${FWOSPlugin_USED_SRCFILES} )

 set_property(TARGET FWOSPlugin PROPERTY FOLDER ApplicationFramework)

 install( TARGETS FWOSPlugin
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/FWOSPlugin.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( FWOSPlugin PROPERTIES COMPILE_FLAGS "${FWOSPlugin_PRECOMPILED_DEFS}" )
 include_directories( ${FWOSPlugin_COMPILER_DIRECTORIES} )
 target_link_libraries( FWOSPlugin ${FWOSPlugin_USED_LIBS} )
endif()
