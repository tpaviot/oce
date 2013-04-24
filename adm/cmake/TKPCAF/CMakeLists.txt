project(TKPCAF)

if (WIN32)
  list( APPEND TKPCAF_PRECOMPILED_DEFS "-D__PDataXtd_DLL" )
  list( APPEND TKPCAF_PRECOMPILED_DEFS "-D__PNaming_DLL" )
  list( APPEND TKPCAF_PRECOMPILED_DEFS "-D__PPrsStd_DLL" )
  list( APPEND TKPCAF_PRECOMPILED_DEFS "-D__MDataXtd_DLL" )
  list( APPEND TKPCAF_PRECOMPILED_DEFS "-D__MPrsStd_DLL" )
  list( APPEND TKPCAF_PRECOMPILED_DEFS "-D__MNaming_DLL" )
  string( REGEX REPLACE ";" " " TKPCAF_PRECOMPILED_DEFS "${TKPCAF_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKPCAF_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKPCAF_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKPCAF_COMPILER_DIRECTORIES "../../../drv/PDataXtd" )
  list( APPEND TKPCAF_COMPILER_DIRECTORIES "../../../src/PDataXtd" )
  list( APPEND TKPCAF_COMPILER_DIRECTORIES "../../../drv/PNaming" )
  list( APPEND TKPCAF_COMPILER_DIRECTORIES "../../../src/PNaming" )
  list( APPEND TKPCAF_COMPILER_DIRECTORIES "../../../drv/PPrsStd" )
  list( APPEND TKPCAF_COMPILER_DIRECTORIES "../../../src/PPrsStd" )
  list( APPEND TKPCAF_COMPILER_DIRECTORIES "../../../drv/MDataXtd" )
  list( APPEND TKPCAF_COMPILER_DIRECTORIES "../../../src/MDataXtd" )
  list( APPEND TKPCAF_COMPILER_DIRECTORIES "../../../drv/MPrsStd" )
  list( APPEND TKPCAF_COMPILER_DIRECTORIES "../../../src/MPrsStd" )
  list( APPEND TKPCAF_COMPILER_DIRECTORIES "../../../drv/MNaming" )
  list( APPEND TKPCAF_COMPILER_DIRECTORIES "../../../src/MNaming" )

if (WIN32)
else()
endif()

  list( APPEND TKPCAF_USED_LIBS PTKernel )
  list( APPEND TKPCAF_USED_LIBS TKBRep )
  list( APPEND TKPCAF_USED_LIBS TKMath )
  list( APPEND TKPCAF_USED_LIBS TKernel )
  list( APPEND TKPCAF_USED_LIBS TKCDF )
  list( APPEND TKPCAF_USED_LIBS TKG2d )
  list( APPEND TKPCAF_USED_LIBS TKV3d )
  list( APPEND TKPCAF_USED_LIBS TKService )
  list( APPEND TKPCAF_USED_LIBS TKG3d )
  list( APPEND TKPCAF_USED_LIBS TKPShape )
  list( APPEND TKPCAF_USED_LIBS TKCAF )
  list( APPEND TKPCAF_USED_LIBS TKLCAF )
  list( APPEND TKPCAF_USED_LIBS TKPLCAF )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/PDataXtd/PDataXtd_Axis.cxx" )
  SOURCE_GROUP (PDataXtd FILES "../../../src/PDataXtd/PDataXtd_Axis.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/PDataXtd/PDataXtd_Constraint.cxx" )
  SOURCE_GROUP (PDataXtd FILES "../../../src/PDataXtd/PDataXtd_Constraint.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/PDataXtd/PDataXtd_Geometry.cxx" )
  SOURCE_GROUP (PDataXtd FILES "../../../src/PDataXtd/PDataXtd_Geometry.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/PDataXtd/PDataXtd_PatternStd.cxx" )
  SOURCE_GROUP (PDataXtd FILES "../../../src/PDataXtd/PDataXtd_PatternStd.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/PDataXtd/PDataXtd_Placement.cxx" )
  SOURCE_GROUP (PDataXtd FILES "../../../src/PDataXtd/PDataXtd_Placement.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/PDataXtd/PDataXtd_Plane.cxx" )
  SOURCE_GROUP (PDataXtd FILES "../../../src/PDataXtd/PDataXtd_Plane.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/PDataXtd/PDataXtd_Point.cxx" )
  SOURCE_GROUP (PDataXtd FILES "../../../src/PDataXtd/PDataXtd_Point.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/PDataXtd/PDataXtd_Position.cxx" )
  SOURCE_GROUP (PDataXtd FILES "../../../src/PDataXtd/PDataXtd_Position.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/PDataXtd/PDataXtd_Shape.cxx" )
  SOURCE_GROUP (PDataXtd FILES "../../../src/PDataXtd/PDataXtd_Shape.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../drv/PNaming/PNaming_FieldOfHArray1OfNamedShape_0.cxx" )
  SOURCE_GROUP (PNaming FILES "../../../drv/PNaming/PNaming_FieldOfHArray1OfNamedShape_0.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../drv/PNaming/PNaming_HArray1OfNamedShape_0.cxx" )
  SOURCE_GROUP (PNaming FILES "../../../drv/PNaming/PNaming_HArray1OfNamedShape_0.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../drv/PNaming/PNaming_VArrayNodeOfFieldOfHArray1OfNamedShape_0.cxx" )
  SOURCE_GROUP (PNaming FILES "../../../drv/PNaming/PNaming_VArrayNodeOfFieldOfHArray1OfNamedShape_0.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../drv/PNaming/PNaming_VArrayTNodeOfFieldOfHArray1OfNamedShape_0.cxx" )
  SOURCE_GROUP (PNaming FILES "../../../drv/PNaming/PNaming_VArrayTNodeOfFieldOfHArray1OfNamedShape_0.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/PNaming/PNaming_Name.cxx" )
  SOURCE_GROUP (PNaming FILES "../../../src/PNaming/PNaming_Name.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/PNaming/PNaming_Name_1.cxx" )
  SOURCE_GROUP (PNaming FILES "../../../src/PNaming/PNaming_Name_1.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/PNaming/PNaming_NamedShape.cxx" )
  SOURCE_GROUP (PNaming FILES "../../../src/PNaming/PNaming_NamedShape.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/PNaming/PNaming_Naming.cxx" )
  SOURCE_GROUP (PNaming FILES "../../../src/PNaming/PNaming_Naming.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/PNaming/PNaming_Naming_1.cxx" )
  SOURCE_GROUP (PNaming FILES "../../../src/PNaming/PNaming_Naming_1.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/PPrsStd/PPrsStd_AISPresentation.cxx" )
  SOURCE_GROUP (PPrsStd FILES "../../../src/PPrsStd/PPrsStd_AISPresentation.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/PPrsStd/PPrsStd_AISPresentation_1.cxx" )
  SOURCE_GROUP (PPrsStd FILES "../../../src/PPrsStd/PPrsStd_AISPresentation_1.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MDataXtd/MDataXtd.cxx" )
  SOURCE_GROUP (MDataXtd FILES "../../../src/MDataXtd/MDataXtd.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MDataXtd/MDataXtd_AxisRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataXtd FILES "../../../src/MDataXtd/MDataXtd_AxisRetrievalDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MDataXtd/MDataXtd_AxisStorageDriver.cxx" )
  SOURCE_GROUP (MDataXtd FILES "../../../src/MDataXtd/MDataXtd_AxisStorageDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MDataXtd/MDataXtd_ConstraintRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataXtd FILES "../../../src/MDataXtd/MDataXtd_ConstraintRetrievalDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MDataXtd/MDataXtd_ConstraintStorageDriver.cxx" )
  SOURCE_GROUP (MDataXtd FILES "../../../src/MDataXtd/MDataXtd_ConstraintStorageDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MDataXtd/MDataXtd_GeometryRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataXtd FILES "../../../src/MDataXtd/MDataXtd_GeometryRetrievalDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MDataXtd/MDataXtd_GeometryStorageDriver.cxx" )
  SOURCE_GROUP (MDataXtd FILES "../../../src/MDataXtd/MDataXtd_GeometryStorageDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MDataXtd/MDataXtd_PatternStdRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataXtd FILES "../../../src/MDataXtd/MDataXtd_PatternStdRetrievalDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MDataXtd/MDataXtd_PatternStdStorageDriver.cxx" )
  SOURCE_GROUP (MDataXtd FILES "../../../src/MDataXtd/MDataXtd_PatternStdStorageDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MDataXtd/MDataXtd_PlacementRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataXtd FILES "../../../src/MDataXtd/MDataXtd_PlacementRetrievalDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MDataXtd/MDataXtd_PlacementStorageDriver.cxx" )
  SOURCE_GROUP (MDataXtd FILES "../../../src/MDataXtd/MDataXtd_PlacementStorageDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MDataXtd/MDataXtd_PlaneRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataXtd FILES "../../../src/MDataXtd/MDataXtd_PlaneRetrievalDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MDataXtd/MDataXtd_PlaneStorageDriver.cxx" )
  SOURCE_GROUP (MDataXtd FILES "../../../src/MDataXtd/MDataXtd_PlaneStorageDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MDataXtd/MDataXtd_PointRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataXtd FILES "../../../src/MDataXtd/MDataXtd_PointRetrievalDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MDataXtd/MDataXtd_PointStorageDriver.cxx" )
  SOURCE_GROUP (MDataXtd FILES "../../../src/MDataXtd/MDataXtd_PointStorageDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MDataXtd/MDataXtd_ShapeRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataXtd FILES "../../../src/MDataXtd/MDataXtd_ShapeRetrievalDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MDataXtd/MDataXtd_ShapeStorageDriver.cxx" )
  SOURCE_GROUP (MDataXtd FILES "../../../src/MDataXtd/MDataXtd_ShapeStorageDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MPrsStd/MPrsStd.cxx" )
  SOURCE_GROUP (MPrsStd FILES "../../../src/MPrsStd/MPrsStd.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MPrsStd/MPrsStd_AISPresentationRetrievalDriver.cxx" )
  SOURCE_GROUP (MPrsStd FILES "../../../src/MPrsStd/MPrsStd_AISPresentationRetrievalDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MPrsStd/MPrsStd_AISPresentationRetrievalDriver_1.cxx" )
  SOURCE_GROUP (MPrsStd FILES "../../../src/MPrsStd/MPrsStd_AISPresentationRetrievalDriver_1.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MPrsStd/MPrsStd_AISPresentationStorageDriver.cxx" )
  SOURCE_GROUP (MPrsStd FILES "../../../src/MPrsStd/MPrsStd_AISPresentationStorageDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MPrsStd/MPrsStd_PositionRetrievalDriver.cxx" )
  SOURCE_GROUP (MPrsStd FILES "../../../src/MPrsStd/MPrsStd_PositionRetrievalDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MPrsStd/MPrsStd_PositionStorageDriver.cxx" )
  SOURCE_GROUP (MPrsStd FILES "../../../src/MPrsStd/MPrsStd_PositionStorageDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MNaming/MNaming.cxx" )
  SOURCE_GROUP (MNaming FILES "../../../src/MNaming/MNaming.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MNaming/MNaming_NamedShapeRetrievalDriver.cxx" )
  SOURCE_GROUP (MNaming FILES "../../../src/MNaming/MNaming_NamedShapeRetrievalDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MNaming/MNaming_NamedShapeStorageDriver.cxx" )
  SOURCE_GROUP (MNaming FILES "../../../src/MNaming/MNaming_NamedShapeStorageDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MNaming/MNaming_NamingRetrievalDriver.cxx" )
  SOURCE_GROUP (MNaming FILES "../../../src/MNaming/MNaming_NamingRetrievalDriver.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MNaming/MNaming_NamingRetrievalDriver_1.cxx" )
  SOURCE_GROUP (MNaming FILES "../../../src/MNaming/MNaming_NamingRetrievalDriver_1.cxx")

  list( APPEND TKPCAF_USED_SRCFILES "../../../src/MNaming/MNaming_NamingStorageDriver.cxx" )
  SOURCE_GROUP (MNaming FILES "../../../src/MNaming/MNaming_NamingStorageDriver.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKPCAF)
 add_library( TKPCAF SHARED ${TKPCAF_USED_SRCFILES} )

 set_property(TARGET TKPCAF PROPERTY FOLDER ApplicationFramework)

 install( TARGETS TKPCAF
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKPCAF.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKPCAF PROPERTIES COMPILE_FLAGS "${TKPCAF_PRECOMPILED_DEFS}" )
 include_directories( ${TKPCAF_COMPILER_DIRECTORIES} )
 target_link_libraries( TKPCAF ${TKPCAF_USED_LIBS} )
endif()
