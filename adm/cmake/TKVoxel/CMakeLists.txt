project(TKVoxel)

if (WIN32)
  list( APPEND TKVoxel_PRECOMPILED_DEFS "-D__Voxel_DLL" )
  string( REGEX REPLACE ";" " " TKVoxel_PRECOMPILED_DEFS "${TKVoxel_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKVoxel_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKVoxel_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKVoxel_COMPILER_DIRECTORIES "../../../drv/Voxel" )
  list( APPEND TKVoxel_COMPILER_DIRECTORIES "../../../src/Voxel" )

if (WIN32)
else()
endif()

  list( APPEND TKVoxel_USED_LIBS TKBRep )
  list( APPEND TKVoxel_USED_LIBS TKernel )
  list( APPEND TKVoxel_USED_LIBS TKV3d )
  list( APPEND TKVoxel_USED_LIBS TKMath )
  list( APPEND TKVoxel_USED_LIBS TKService )
  list( APPEND TKVoxel_USED_LIBS TKGeomBase )
  list( APPEND TKVoxel_USED_LIBS TKG2d )
  list( APPEND TKVoxel_USED_LIBS TKTopAlgo )
  list( APPEND TKVoxel_USED_LIBS TKG3d )
  list( APPEND TKVoxel_USED_LIBS TKMesh )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKVoxel_USED_SRCFILES "../../../src/Voxel/Voxel_BoolDS.cxx" )
  SOURCE_GROUP (Voxel FILES "../../../src/Voxel/Voxel_BoolDS.cxx")

  list( APPEND TKVoxel_USED_SRCFILES "../../../src/Voxel/Voxel_BooleanOperation.cxx" )
  SOURCE_GROUP (Voxel FILES "../../../src/Voxel/Voxel_BooleanOperation.cxx")

  list( APPEND TKVoxel_USED_SRCFILES "../../../src/Voxel/Voxel_CollisionDetection.cxx" )
  SOURCE_GROUP (Voxel FILES "../../../src/Voxel/Voxel_CollisionDetection.cxx")

  list( APPEND TKVoxel_USED_SRCFILES "../../../src/Voxel/Voxel_ColorDS.cxx" )
  SOURCE_GROUP (Voxel FILES "../../../src/Voxel/Voxel_ColorDS.cxx")

  list( APPEND TKVoxel_USED_SRCFILES "../../../src/Voxel/Voxel_DS.cxx" )
  SOURCE_GROUP (Voxel FILES "../../../src/Voxel/Voxel_DS.cxx")

  list( APPEND TKVoxel_USED_SRCFILES "../../../src/Voxel/Voxel_FastConverter.cxx" )
  SOURCE_GROUP (Voxel FILES "../../../src/Voxel/Voxel_FastConverter.cxx")

  list( APPEND TKVoxel_USED_SRCFILES "../../../src/Voxel/Voxel_FloatDS.cxx" )
  SOURCE_GROUP (Voxel FILES "../../../src/Voxel/Voxel_FloatDS.cxx")

  list( APPEND TKVoxel_USED_SRCFILES "../../../src/Voxel/Voxel_OctBoolDS.cxx" )
  SOURCE_GROUP (Voxel FILES "../../../src/Voxel/Voxel_OctBoolDS.cxx")

  list( APPEND TKVoxel_USED_SRCFILES "../../../src/Voxel/Voxel_Prs.cxx" )
  SOURCE_GROUP (Voxel FILES "../../../src/Voxel/Voxel_Prs.cxx")

  list( APPEND TKVoxel_USED_SRCFILES "../../../src/Voxel/Voxel_ROctBoolDS.cxx" )
  SOURCE_GROUP (Voxel FILES "../../../src/Voxel/Voxel_ROctBoolDS.cxx")

  list( APPEND TKVoxel_USED_SRCFILES "../../../src/Voxel/Voxel_Reader.cxx" )
  SOURCE_GROUP (Voxel FILES "../../../src/Voxel/Voxel_Reader.cxx")

  list( APPEND TKVoxel_USED_SRCFILES "../../../src/Voxel/Voxel_Selector.cxx" )
  SOURCE_GROUP (Voxel FILES "../../../src/Voxel/Voxel_Selector.cxx")

  list( APPEND TKVoxel_USED_SRCFILES "../../../src/Voxel/Voxel_SplitData.cxx" )
  SOURCE_GROUP (Voxel FILES "../../../src/Voxel/Voxel_SplitData.cxx")

  list( APPEND TKVoxel_USED_SRCFILES "../../../src/Voxel/Voxel_Writer.cxx" )
  SOURCE_GROUP (Voxel FILES "../../../src/Voxel/Voxel_Writer.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKVoxel)
 add_library( TKVoxel SHARED ${TKVoxel_USED_SRCFILES} )

 set_property(TARGET TKVoxel PROPERTY FOLDER Visualization)

 install( TARGETS TKVoxel
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKVoxel.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKVoxel PROPERTIES COMPILE_FLAGS "${TKVoxel_PRECOMPILED_DEFS}" )
 include_directories( ${TKVoxel_COMPILER_DIRECTORIES} )
 target_link_libraries( TKVoxel ${TKVoxel_USED_LIBS} )
endif()
