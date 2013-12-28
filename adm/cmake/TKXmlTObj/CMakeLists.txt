project(TKXmlTObj)

if (WIN32)
  list( APPEND TKXmlTObj_PRECOMPILED_DEFS "-D__XmlTObjDrivers_DLL" )
  string( REGEX REPLACE ";" " " TKXmlTObj_PRECOMPILED_DEFS "${TKXmlTObj_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKXmlTObj_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKXmlTObj_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKXmlTObj_COMPILER_DIRECTORIES "../../../drv/XmlTObjDrivers" )
  list( APPEND TKXmlTObj_COMPILER_DIRECTORIES "../../../src/XmlTObjDrivers" )

if (WIN32)
else()
endif()

  list( APPEND TKXmlTObj_USED_LIBS TKCDF )
  list( APPEND TKXmlTObj_USED_LIBS TKernel )
  list( APPEND TKXmlTObj_USED_LIBS TKTObj )
  list( APPEND TKXmlTObj_USED_LIBS TKMath )
  list( APPEND TKXmlTObj_USED_LIBS TKLCAF )
  list( APPEND TKXmlTObj_USED_LIBS TKXmlL )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKXmlTObj_USED_SRCFILES "../../../src/XmlTObjDrivers/XmlTObjDrivers.cxx" )
  SOURCE_GROUP (XmlTObjDrivers FILES "../../../src/XmlTObjDrivers/XmlTObjDrivers.cxx")

  list( APPEND TKXmlTObj_USED_SRCFILES "../../../src/XmlTObjDrivers/XmlTObjDrivers_DocumentRetrievalDriver.cxx" )
  SOURCE_GROUP (XmlTObjDrivers FILES "../../../src/XmlTObjDrivers/XmlTObjDrivers_DocumentRetrievalDriver.cxx")

  list( APPEND TKXmlTObj_USED_SRCFILES "../../../src/XmlTObjDrivers/XmlTObjDrivers_DocumentStorageDriver.cxx" )
  SOURCE_GROUP (XmlTObjDrivers FILES "../../../src/XmlTObjDrivers/XmlTObjDrivers_DocumentStorageDriver.cxx")

  list( APPEND TKXmlTObj_USED_SRCFILES "../../../src/XmlTObjDrivers/XmlTObjDrivers_IntSparseArrayDriver.cxx" )
  SOURCE_GROUP (XmlTObjDrivers FILES "../../../src/XmlTObjDrivers/XmlTObjDrivers_IntSparseArrayDriver.cxx")

  list( APPEND TKXmlTObj_USED_SRCFILES "../../../src/XmlTObjDrivers/XmlTObjDrivers_ModelDriver.cxx" )
  SOURCE_GROUP (XmlTObjDrivers FILES "../../../src/XmlTObjDrivers/XmlTObjDrivers_ModelDriver.cxx")

  list( APPEND TKXmlTObj_USED_SRCFILES "../../../src/XmlTObjDrivers/XmlTObjDrivers_ObjectDriver.cxx" )
  SOURCE_GROUP (XmlTObjDrivers FILES "../../../src/XmlTObjDrivers/XmlTObjDrivers_ObjectDriver.cxx")

  list( APPEND TKXmlTObj_USED_SRCFILES "../../../src/XmlTObjDrivers/XmlTObjDrivers_ReferenceDriver.cxx" )
  SOURCE_GROUP (XmlTObjDrivers FILES "../../../src/XmlTObjDrivers/XmlTObjDrivers_ReferenceDriver.cxx")

  list( APPEND TKXmlTObj_USED_SRCFILES "../../../src/XmlTObjDrivers/XmlTObjDrivers_XYZDriver.cxx" )
  SOURCE_GROUP (XmlTObjDrivers FILES "../../../src/XmlTObjDrivers/XmlTObjDrivers_XYZDriver.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKXmlTObj)
 add_library( TKXmlTObj SHARED ${TKXmlTObj_USED_SRCFILES} )

 set_property(TARGET TKXmlTObj PROPERTY FOLDER ApplicationFramework)

 install( TARGETS TKXmlTObj
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKXmlTObj.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKXmlTObj PROPERTIES COMPILE_FLAGS "${TKXmlTObj_PRECOMPILED_DEFS}" )
 include_directories( ${TKXmlTObj_COMPILER_DIRECTORIES} )
 target_link_libraries( TKXmlTObj ${TKXmlTObj_USED_LIBS} )
endif()
