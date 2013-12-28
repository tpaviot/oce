project(TKBinTObj)

if (WIN32)
  list( APPEND TKBinTObj_PRECOMPILED_DEFS "-D__BinTObjDrivers_DLL" )
  string( REGEX REPLACE ";" " " TKBinTObj_PRECOMPILED_DEFS "${TKBinTObj_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKBinTObj_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKBinTObj_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKBinTObj_COMPILER_DIRECTORIES "../../../drv/BinTObjDrivers" )
  list( APPEND TKBinTObj_COMPILER_DIRECTORIES "../../../src/BinTObjDrivers" )

if (WIN32)
else()
endif()

  list( APPEND TKBinTObj_USED_LIBS TKCDF )
  list( APPEND TKBinTObj_USED_LIBS TKernel )
  list( APPEND TKBinTObj_USED_LIBS TKTObj )
  list( APPEND TKBinTObj_USED_LIBS TKMath )
  list( APPEND TKBinTObj_USED_LIBS TKLCAF )
  list( APPEND TKBinTObj_USED_LIBS TKBinL )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKBinTObj_USED_SRCFILES "../../../src/BinTObjDrivers/BinTObjDrivers.cxx" )
  SOURCE_GROUP (BinTObjDrivers FILES "../../../src/BinTObjDrivers/BinTObjDrivers.cxx")

  list( APPEND TKBinTObj_USED_SRCFILES "../../../src/BinTObjDrivers/BinTObjDrivers_DocumentRetrievalDriver.cxx" )
  SOURCE_GROUP (BinTObjDrivers FILES "../../../src/BinTObjDrivers/BinTObjDrivers_DocumentRetrievalDriver.cxx")

  list( APPEND TKBinTObj_USED_SRCFILES "../../../src/BinTObjDrivers/BinTObjDrivers_DocumentStorageDriver.cxx" )
  SOURCE_GROUP (BinTObjDrivers FILES "../../../src/BinTObjDrivers/BinTObjDrivers_DocumentStorageDriver.cxx")

  list( APPEND TKBinTObj_USED_SRCFILES "../../../src/BinTObjDrivers/BinTObjDrivers_IntSparseArrayDriver.cxx" )
  SOURCE_GROUP (BinTObjDrivers FILES "../../../src/BinTObjDrivers/BinTObjDrivers_IntSparseArrayDriver.cxx")

  list( APPEND TKBinTObj_USED_SRCFILES "../../../src/BinTObjDrivers/BinTObjDrivers_ModelDriver.cxx" )
  SOURCE_GROUP (BinTObjDrivers FILES "../../../src/BinTObjDrivers/BinTObjDrivers_ModelDriver.cxx")

  list( APPEND TKBinTObj_USED_SRCFILES "../../../src/BinTObjDrivers/BinTObjDrivers_ObjectDriver.cxx" )
  SOURCE_GROUP (BinTObjDrivers FILES "../../../src/BinTObjDrivers/BinTObjDrivers_ObjectDriver.cxx")

  list( APPEND TKBinTObj_USED_SRCFILES "../../../src/BinTObjDrivers/BinTObjDrivers_ReferenceDriver.cxx" )
  SOURCE_GROUP (BinTObjDrivers FILES "../../../src/BinTObjDrivers/BinTObjDrivers_ReferenceDriver.cxx")

  list( APPEND TKBinTObj_USED_SRCFILES "../../../src/BinTObjDrivers/BinTObjDrivers_XYZDriver.cxx" )
  SOURCE_GROUP (BinTObjDrivers FILES "../../../src/BinTObjDrivers/BinTObjDrivers_XYZDriver.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKBinTObj)
 add_library( TKBinTObj SHARED ${TKBinTObj_USED_SRCFILES} )

 set_property(TARGET TKBinTObj PROPERTY FOLDER ApplicationFramework)

 install( TARGETS TKBinTObj
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKBinTObj.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKBinTObj PROPERTIES COMPILE_FLAGS "${TKBinTObj_PRECOMPILED_DEFS}" )
 include_directories( ${TKBinTObj_COMPILER_DIRECTORIES} )
 target_link_libraries( TKBinTObj ${TKBinTObj_USED_LIBS} )
endif()
