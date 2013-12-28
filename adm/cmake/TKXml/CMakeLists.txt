project(TKXml)

if (WIN32)
  list( APPEND TKXml_PRECOMPILED_DEFS "-D__XmlDrivers_DLL" )
  list( APPEND TKXml_PRECOMPILED_DEFS "-D__XmlMDataXtd_DLL" )
  list( APPEND TKXml_PRECOMPILED_DEFS "-D__XmlMNaming_DLL" )
  list( APPEND TKXml_PRECOMPILED_DEFS "-D__XmlMPrsStd_DLL" )
  string( REGEX REPLACE ";" " " TKXml_PRECOMPILED_DEFS "${TKXml_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKXml_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKXml_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKXml_COMPILER_DIRECTORIES "../../../drv/XmlDrivers" )
  list( APPEND TKXml_COMPILER_DIRECTORIES "../../../src/XmlDrivers" )
  list( APPEND TKXml_COMPILER_DIRECTORIES "../../../drv/XmlMDataXtd" )
  list( APPEND TKXml_COMPILER_DIRECTORIES "../../../src/XmlMDataXtd" )
  list( APPEND TKXml_COMPILER_DIRECTORIES "../../../drv/XmlMNaming" )
  list( APPEND TKXml_COMPILER_DIRECTORIES "../../../src/XmlMNaming" )
  list( APPEND TKXml_COMPILER_DIRECTORIES "../../../drv/XmlMPrsStd" )
  list( APPEND TKXml_COMPILER_DIRECTORIES "../../../src/XmlMPrsStd" )

if (WIN32)
else()
endif()

  list( APPEND TKXml_USED_LIBS TKCDF )
  list( APPEND TKXml_USED_LIBS TKernel )
  list( APPEND TKXml_USED_LIBS TKV3d )
  list( APPEND TKXml_USED_LIBS TKMath )
  list( APPEND TKXml_USED_LIBS TKBRep )
  list( APPEND TKXml_USED_LIBS TKG2d )
  list( APPEND TKXml_USED_LIBS TKGeomBase )
  list( APPEND TKXml_USED_LIBS TKG3d )
  list( APPEND TKXml_USED_LIBS TKLCAF )
  list( APPEND TKXml_USED_LIBS TKCAF )
  list( APPEND TKXml_USED_LIBS TKXmlL )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlDrivers/XmlDrivers.cxx" )
  SOURCE_GROUP (XmlDrivers FILES "../../../src/XmlDrivers/XmlDrivers.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlDrivers/XmlDrivers_DocumentRetrievalDriver.cxx" )
  SOURCE_GROUP (XmlDrivers FILES "../../../src/XmlDrivers/XmlDrivers_DocumentRetrievalDriver.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlDrivers/XmlDrivers_DocumentStorageDriver.cxx" )
  SOURCE_GROUP (XmlDrivers FILES "../../../src/XmlDrivers/XmlDrivers_DocumentStorageDriver.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlMDataXtd/XmlMDataXtd.cxx" )
  SOURCE_GROUP (XmlMDataXtd FILES "../../../src/XmlMDataXtd/XmlMDataXtd.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlMDataXtd/XmlMDataXtd_AxisDriver.cxx" )
  SOURCE_GROUP (XmlMDataXtd FILES "../../../src/XmlMDataXtd/XmlMDataXtd_AxisDriver.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlMDataXtd/XmlMDataXtd_ConstraintDriver.cxx" )
  SOURCE_GROUP (XmlMDataXtd FILES "../../../src/XmlMDataXtd/XmlMDataXtd_ConstraintDriver.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlMDataXtd/XmlMDataXtd_GeometryDriver.cxx" )
  SOURCE_GROUP (XmlMDataXtd FILES "../../../src/XmlMDataXtd/XmlMDataXtd_GeometryDriver.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlMDataXtd/XmlMDataXtd_PatternStdDriver.cxx" )
  SOURCE_GROUP (XmlMDataXtd FILES "../../../src/XmlMDataXtd/XmlMDataXtd_PatternStdDriver.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlMDataXtd/XmlMDataXtd_PlacementDriver.cxx" )
  SOURCE_GROUP (XmlMDataXtd FILES "../../../src/XmlMDataXtd/XmlMDataXtd_PlacementDriver.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlMDataXtd/XmlMDataXtd_PlaneDriver.cxx" )
  SOURCE_GROUP (XmlMDataXtd FILES "../../../src/XmlMDataXtd/XmlMDataXtd_PlaneDriver.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlMDataXtd/XmlMDataXtd_PointDriver.cxx" )
  SOURCE_GROUP (XmlMDataXtd FILES "../../../src/XmlMDataXtd/XmlMDataXtd_PointDriver.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlMDataXtd/XmlMDataXtd_ShapeDriver.cxx" )
  SOURCE_GROUP (XmlMDataXtd FILES "../../../src/XmlMDataXtd/XmlMDataXtd_ShapeDriver.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../drv/XmlMNaming/XmlMNaming_Array1OfShape1_0.cxx" )
  SOURCE_GROUP (XmlMNaming FILES "../../../drv/XmlMNaming/XmlMNaming_Array1OfShape1_0.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlMNaming/XmlMNaming.cxx" )
  SOURCE_GROUP (XmlMNaming FILES "../../../src/XmlMNaming/XmlMNaming.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlMNaming/XmlMNaming_NamedShapeDriver.cxx" )
  SOURCE_GROUP (XmlMNaming FILES "../../../src/XmlMNaming/XmlMNaming_NamedShapeDriver.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlMNaming/XmlMNaming_NamingDriver.cxx" )
  SOURCE_GROUP (XmlMNaming FILES "../../../src/XmlMNaming/XmlMNaming_NamingDriver.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlMNaming/XmlMNaming_Shape1.cxx" )
  SOURCE_GROUP (XmlMNaming FILES "../../../src/XmlMNaming/XmlMNaming_Shape1.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlMPrsStd/XmlMPrsStd.cxx" )
  SOURCE_GROUP (XmlMPrsStd FILES "../../../src/XmlMPrsStd/XmlMPrsStd.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlMPrsStd/XmlMPrsStd_AISPresentationDriver.cxx" )
  SOURCE_GROUP (XmlMPrsStd FILES "../../../src/XmlMPrsStd/XmlMPrsStd_AISPresentationDriver.cxx")

  list( APPEND TKXml_USED_SRCFILES "../../../src/XmlMPrsStd/XmlMPrsStd_PositionDriver.cxx" )
  SOURCE_GROUP (XmlMPrsStd FILES "../../../src/XmlMPrsStd/XmlMPrsStd_PositionDriver.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKXml)
 add_library( TKXml SHARED ${TKXml_USED_SRCFILES} )

 set_property(TARGET TKXml PROPERTY FOLDER ApplicationFramework)

 install( TARGETS TKXml
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKXml.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKXml PROPERTIES COMPILE_FLAGS "${TKXml_PRECOMPILED_DEFS}" )
 include_directories( ${TKXml_COMPILER_DIRECTORIES} )
 target_link_libraries( TKXml ${TKXml_USED_LIBS} )
endif()
