project(TKBin)

if (WIN32)
  list( APPEND TKBin_PRECOMPILED_DEFS "-D__BinDrivers_DLL" )
  list( APPEND TKBin_PRECOMPILED_DEFS "-D__BinMDataXtd_DLL" )
  list( APPEND TKBin_PRECOMPILED_DEFS "-D__BinMPrsStd_DLL" )
  list( APPEND TKBin_PRECOMPILED_DEFS "-D__BinMNaming_DLL" )
  list( APPEND TKBin_PRECOMPILED_DEFS "-D__BinTools_DLL" )
  string( REGEX REPLACE ";" " " TKBin_PRECOMPILED_DEFS "${TKBin_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKBin_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKBin_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKBin_COMPILER_DIRECTORIES "../../../drv/BinDrivers" )
  list( APPEND TKBin_COMPILER_DIRECTORIES "../../../src/BinDrivers" )
  list( APPEND TKBin_COMPILER_DIRECTORIES "../../../drv/BinMDataXtd" )
  list( APPEND TKBin_COMPILER_DIRECTORIES "../../../src/BinMDataXtd" )
  list( APPEND TKBin_COMPILER_DIRECTORIES "../../../drv/BinMPrsStd" )
  list( APPEND TKBin_COMPILER_DIRECTORIES "../../../src/BinMPrsStd" )
  list( APPEND TKBin_COMPILER_DIRECTORIES "../../../drv/BinMNaming" )
  list( APPEND TKBin_COMPILER_DIRECTORIES "../../../src/BinMNaming" )
  list( APPEND TKBin_COMPILER_DIRECTORIES "../../../drv/BinTools" )
  list( APPEND TKBin_COMPILER_DIRECTORIES "../../../src/BinTools" )

if (WIN32)
else()
endif()

  list( APPEND TKBin_USED_LIBS TKBRep )
  list( APPEND TKBin_USED_LIBS TKMath )
  list( APPEND TKBin_USED_LIBS TKernel )
  list( APPEND TKBin_USED_LIBS TKG2d )
  list( APPEND TKBin_USED_LIBS TKG3d )
  list( APPEND TKBin_USED_LIBS TKCAF )
  list( APPEND TKBin_USED_LIBS TKCDF )
  list( APPEND TKBin_USED_LIBS TKLCAF )
  list( APPEND TKBin_USED_LIBS TKV3d )
  list( APPEND TKBin_USED_LIBS TKBinL )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinDrivers/BinDrivers.cxx" )
  SOURCE_GROUP (BinDrivers FILES "../../../src/BinDrivers/BinDrivers.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinDrivers/BinDrivers_DocumentRetrievalDriver.cxx" )
  SOURCE_GROUP (BinDrivers FILES "../../../src/BinDrivers/BinDrivers_DocumentRetrievalDriver.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinDrivers/BinDrivers_DocumentStorageDriver.cxx" )
  SOURCE_GROUP (BinDrivers FILES "../../../src/BinDrivers/BinDrivers_DocumentStorageDriver.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinMDataXtd/BinMDataXtd.cxx" )
  SOURCE_GROUP (BinMDataXtd FILES "../../../src/BinMDataXtd/BinMDataXtd.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinMDataXtd/BinMDataXtd_AxisDriver.cxx" )
  SOURCE_GROUP (BinMDataXtd FILES "../../../src/BinMDataXtd/BinMDataXtd_AxisDriver.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinMDataXtd/BinMDataXtd_ConstraintDriver.cxx" )
  SOURCE_GROUP (BinMDataXtd FILES "../../../src/BinMDataXtd/BinMDataXtd_ConstraintDriver.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinMDataXtd/BinMDataXtd_GeometryDriver.cxx" )
  SOURCE_GROUP (BinMDataXtd FILES "../../../src/BinMDataXtd/BinMDataXtd_GeometryDriver.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinMDataXtd/BinMDataXtd_PatternStdDriver.cxx" )
  SOURCE_GROUP (BinMDataXtd FILES "../../../src/BinMDataXtd/BinMDataXtd_PatternStdDriver.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinMDataXtd/BinMDataXtd_PlacementDriver.cxx" )
  SOURCE_GROUP (BinMDataXtd FILES "../../../src/BinMDataXtd/BinMDataXtd_PlacementDriver.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinMDataXtd/BinMDataXtd_PlaneDriver.cxx" )
  SOURCE_GROUP (BinMDataXtd FILES "../../../src/BinMDataXtd/BinMDataXtd_PlaneDriver.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinMDataXtd/BinMDataXtd_PointDriver.cxx" )
  SOURCE_GROUP (BinMDataXtd FILES "../../../src/BinMDataXtd/BinMDataXtd_PointDriver.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinMDataXtd/BinMDataXtd_ShapeDriver.cxx" )
  SOURCE_GROUP (BinMDataXtd FILES "../../../src/BinMDataXtd/BinMDataXtd_ShapeDriver.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinMPrsStd/BinMPrsStd.cxx" )
  SOURCE_GROUP (BinMPrsStd FILES "../../../src/BinMPrsStd/BinMPrsStd.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinMPrsStd/BinMPrsStd_AISPresentationDriver.cxx" )
  SOURCE_GROUP (BinMPrsStd FILES "../../../src/BinMPrsStd/BinMPrsStd_AISPresentationDriver.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinMPrsStd/BinMPrsStd_PositionDriver.cxx" )
  SOURCE_GROUP (BinMPrsStd FILES "../../../src/BinMPrsStd/BinMPrsStd_PositionDriver.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinMNaming/BinMNaming.cxx" )
  SOURCE_GROUP (BinMNaming FILES "../../../src/BinMNaming/BinMNaming.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinMNaming/BinMNaming_NamedShapeDriver.cxx" )
  SOURCE_GROUP (BinMNaming FILES "../../../src/BinMNaming/BinMNaming_NamedShapeDriver.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinMNaming/BinMNaming_NamingDriver.cxx" )
  SOURCE_GROUP (BinMNaming FILES "../../../src/BinMNaming/BinMNaming_NamingDriver.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinTools/BinTools.cxx" )
  SOURCE_GROUP (BinTools FILES "../../../src/BinTools/BinTools.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinTools/BinTools_Curve2dSet.cxx" )
  SOURCE_GROUP (BinTools FILES "../../../src/BinTools/BinTools_Curve2dSet.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinTools/BinTools_CurveSet.cxx" )
  SOURCE_GROUP (BinTools FILES "../../../src/BinTools/BinTools_CurveSet.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinTools/BinTools_LocationSet.cxx" )
  SOURCE_GROUP (BinTools FILES "../../../src/BinTools/BinTools_LocationSet.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinTools/BinTools_ShapeSet.cxx" )
  SOURCE_GROUP (BinTools FILES "../../../src/BinTools/BinTools_ShapeSet.cxx")

  list( APPEND TKBin_USED_SRCFILES "../../../src/BinTools/BinTools_SurfaceSet.cxx" )
  SOURCE_GROUP (BinTools FILES "../../../src/BinTools/BinTools_SurfaceSet.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKBin)
 add_library( TKBin SHARED ${TKBin_USED_SRCFILES} )

 set_property(TARGET TKBin PROPERTY FOLDER ApplicationFramework)

 install( TARGETS TKBin
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKBin.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKBin PROPERTIES COMPILE_FLAGS "${TKBin_PRECOMPILED_DEFS}" )
 include_directories( ${TKBin_COMPILER_DIRECTORIES} )
 target_link_libraries( TKBin ${TKBin_USED_LIBS} )
endif()
