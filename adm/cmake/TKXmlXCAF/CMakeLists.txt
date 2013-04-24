project(TKXmlXCAF)

if (WIN32)
  list( APPEND TKXmlXCAF_PRECOMPILED_DEFS "-D__XmlXCAFDrivers_DLL" )
  list( APPEND TKXmlXCAF_PRECOMPILED_DEFS "-D__XmlMXCAFDoc_DLL" )
  string( REGEX REPLACE ";" " " TKXmlXCAF_PRECOMPILED_DEFS "${TKXmlXCAF_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKXmlXCAF_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKXmlXCAF_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKXmlXCAF_COMPILER_DIRECTORIES "../../../drv/XmlXCAFDrivers" )
  list( APPEND TKXmlXCAF_COMPILER_DIRECTORIES "../../../src/XmlXCAFDrivers" )
  list( APPEND TKXmlXCAF_COMPILER_DIRECTORIES "../../../drv/XmlMXCAFDoc" )
  list( APPEND TKXmlXCAF_COMPILER_DIRECTORIES "../../../src/XmlMXCAFDoc" )

if (WIN32)
else()
endif()

  list( APPEND TKXmlXCAF_USED_LIBS TKXmlL )
  list( APPEND TKXmlXCAF_USED_LIBS TKBRep )
  list( APPEND TKXmlXCAF_USED_LIBS TKCDF )
  list( APPEND TKXmlXCAF_USED_LIBS TKMath )
  list( APPEND TKXmlXCAF_USED_LIBS TKernel )
  list( APPEND TKXmlXCAF_USED_LIBS TKG2d )
  list( APPEND TKXmlXCAF_USED_LIBS TKGeomBase )
  list( APPEND TKXmlXCAF_USED_LIBS TKCAF )
  list( APPEND TKXmlXCAF_USED_LIBS TKG3d )
  list( APPEND TKXmlXCAF_USED_LIBS TKLCAF )
  list( APPEND TKXmlXCAF_USED_LIBS TKXCAF )
  list( APPEND TKXmlXCAF_USED_LIBS TKXml )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlXCAFDrivers/XmlXCAFDrivers.cxx" )
  SOURCE_GROUP (XmlXCAFDrivers FILES "../../../src/XmlXCAFDrivers/XmlXCAFDrivers.cxx")

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlXCAFDrivers/XmlXCAFDrivers_DocumentRetrievalDriver.cxx" )
  SOURCE_GROUP (XmlXCAFDrivers FILES "../../../src/XmlXCAFDrivers/XmlXCAFDrivers_DocumentRetrievalDriver.cxx")

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlXCAFDrivers/XmlXCAFDrivers_DocumentStorageDriver.cxx" )
  SOURCE_GROUP (XmlXCAFDrivers FILES "../../../src/XmlXCAFDrivers/XmlXCAFDrivers_DocumentStorageDriver.cxx")

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc.cxx" )
  SOURCE_GROUP (XmlMXCAFDoc FILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc.cxx")

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_AreaDriver.cxx" )
  SOURCE_GROUP (XmlMXCAFDoc FILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_AreaDriver.cxx")

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_CentroidDriver.cxx" )
  SOURCE_GROUP (XmlMXCAFDoc FILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_CentroidDriver.cxx")

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_ColorDriver.cxx" )
  SOURCE_GROUP (XmlMXCAFDoc FILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_ColorDriver.cxx")

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_ColorToolDriver.cxx" )
  SOURCE_GROUP (XmlMXCAFDoc FILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_ColorToolDriver.cxx")

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_DatumDriver.cxx" )
  SOURCE_GROUP (XmlMXCAFDoc FILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_DatumDriver.cxx")

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_DimTolDriver.cxx" )
  SOURCE_GROUP (XmlMXCAFDoc FILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_DimTolDriver.cxx")

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_DimTolToolDriver.cxx" )
  SOURCE_GROUP (XmlMXCAFDoc FILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_DimTolToolDriver.cxx")

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_DocumentToolDriver.cxx" )
  SOURCE_GROUP (XmlMXCAFDoc FILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_DocumentToolDriver.cxx")

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_GraphNodeDriver.cxx" )
  SOURCE_GROUP (XmlMXCAFDoc FILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_GraphNodeDriver.cxx")

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_LayerToolDriver.cxx" )
  SOURCE_GROUP (XmlMXCAFDoc FILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_LayerToolDriver.cxx")

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_LocationDriver.cxx" )
  SOURCE_GROUP (XmlMXCAFDoc FILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_LocationDriver.cxx")

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_MaterialDriver.cxx" )
  SOURCE_GROUP (XmlMXCAFDoc FILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_MaterialDriver.cxx")

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_MaterialToolDriver.cxx" )
  SOURCE_GROUP (XmlMXCAFDoc FILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_MaterialToolDriver.cxx")

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_ShapeToolDriver.cxx" )
  SOURCE_GROUP (XmlMXCAFDoc FILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_ShapeToolDriver.cxx")

  list( APPEND TKXmlXCAF_USED_SRCFILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_VolumeDriver.cxx" )
  SOURCE_GROUP (XmlMXCAFDoc FILES "../../../src/XmlMXCAFDoc/XmlMXCAFDoc_VolumeDriver.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKXmlXCAF)
 add_library( TKXmlXCAF SHARED ${TKXmlXCAF_USED_SRCFILES} )

 set_property(TARGET TKXmlXCAF PROPERTY FOLDER DataExchange)

 install( TARGETS TKXmlXCAF
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKXmlXCAF.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKXmlXCAF PROPERTIES COMPILE_FLAGS "${TKXmlXCAF_PRECOMPILED_DEFS}" )
 include_directories( ${TKXmlXCAF_COMPILER_DIRECTORIES} )
 target_link_libraries( TKXmlXCAF ${TKXmlXCAF_USED_LIBS} )
endif()
