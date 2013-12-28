project(TKMeshVS)

if (WIN32)
  list( APPEND TKMeshVS_PRECOMPILED_DEFS "-D__MeshVS_DLL" )
  string( REGEX REPLACE ";" " " TKMeshVS_PRECOMPILED_DEFS "${TKMeshVS_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKMeshVS_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKMeshVS_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKMeshVS_COMPILER_DIRECTORIES "../../../drv/MeshVS" )
  list( APPEND TKMeshVS_COMPILER_DIRECTORIES "../../../src/MeshVS" )

if (WIN32)
else()
endif()

  list( APPEND TKMeshVS_USED_LIBS TKV3d )
  list( APPEND TKMeshVS_USED_LIBS TKMath )
  list( APPEND TKMeshVS_USED_LIBS TKService )
  list( APPEND TKMeshVS_USED_LIBS TKernel )
  list( APPEND TKMeshVS_USED_LIBS TKG3d )
  list( APPEND TKMeshVS_USED_LIBS TKG2d )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_Array1OfSequenceOfInteger_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_Array1OfSequenceOfInteger_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfColorMapOfInteger_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfColorMapOfInteger_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfHArray1OfSequenceOfInteger_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfHArray1OfSequenceOfInteger_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfIntegerAsciiString_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfIntegerAsciiString_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfIntegerBoolean_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfIntegerBoolean_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfIntegerColor_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfIntegerColor_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfIntegerMaterial_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfIntegerMaterial_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfIntegerMeshEntityOwner_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfIntegerMeshEntityOwner_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfIntegerOwner_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfIntegerOwner_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfIntegerTwoColors_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfIntegerTwoColors_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfIntegerVector_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfIntegerVector_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfTwoColorsMapOfInteger_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapIteratorOfDataMapOfTwoColorsMapOfInteger_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfColorMapOfInteger_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfColorMapOfInteger_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfHArray1OfSequenceOfInteger_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfHArray1OfSequenceOfInteger_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfIntegerAsciiString_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfIntegerAsciiString_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfIntegerBoolean_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfIntegerBoolean_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfIntegerColor_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfIntegerColor_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfIntegerMaterial_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfIntegerMaterial_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfIntegerMeshEntityOwner_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfIntegerMeshEntityOwner_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfIntegerOwner_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfIntegerOwner_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfIntegerTwoColors_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfIntegerTwoColors_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfIntegerVector_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfIntegerVector_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfTwoColorsMapOfInteger_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapNodeOfDataMapOfTwoColorsMapOfInteger_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapOfColorMapOfInteger_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapOfColorMapOfInteger_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapOfHArray1OfSequenceOfInteger_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapOfHArray1OfSequenceOfInteger_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapOfIntegerAsciiString_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapOfIntegerAsciiString_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapOfIntegerBoolean_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapOfIntegerBoolean_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapOfIntegerColor_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapOfIntegerColor_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapOfIntegerMaterial_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapOfIntegerMaterial_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapOfIntegerMeshEntityOwner_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapOfIntegerMeshEntityOwner_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapOfIntegerOwner_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapOfIntegerOwner_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapOfIntegerTwoColors_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapOfIntegerTwoColors_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapOfIntegerVector_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapOfIntegerVector_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_DataMapOfTwoColorsMapOfInteger_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_DataMapOfTwoColorsMapOfInteger_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_HArray1OfSequenceOfInteger_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_HArray1OfSequenceOfInteger_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_MapIteratorOfMapOfTwoNodes_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_MapIteratorOfMapOfTwoNodes_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_MapOfTwoNodes_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_MapOfTwoNodes_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_SequenceNodeOfSequenceOfPrsBuilder_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_SequenceNodeOfSequenceOfPrsBuilder_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_SequenceOfPrsBuilder_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_SequenceOfPrsBuilder_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_StdMapNodeOfMapOfTwoNodes_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_StdMapNodeOfMapOfTwoNodes_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_TwoColorsHasher_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_TwoColorsHasher_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../drv/MeshVS/MeshVS_TwoNodesHasher_0.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../drv/MeshVS/MeshVS_TwoNodesHasher_0.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_ColorHasher.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_ColorHasher.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_DataSource.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_DataSource.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_DataSource3D.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_DataSource3D.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_DeformedDataSource.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_DeformedDataSource.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_Drawer.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_Drawer.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_DummySensitiveEntity.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_DummySensitiveEntity.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_ElementalColorPrsBuilder.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_ElementalColorPrsBuilder.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_Mesh.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_Mesh.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_MeshEntityOwner.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_MeshEntityOwner.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_MeshOwner.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_MeshOwner.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_MeshPrsBuilder.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_MeshPrsBuilder.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_NodalColorPrsBuilder.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_NodalColorPrsBuilder.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_PrsBuilder.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_PrsBuilder.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_SensitiveFace.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_SensitiveFace.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_SensitiveMesh.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_SensitiveMesh.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_SensitivePolyhedron.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_SensitivePolyhedron.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_SensitiveSegment.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_SensitiveSegment.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_TextPrsBuilder.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_TextPrsBuilder.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_Tool.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_Tool.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_TwoColors.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_TwoColors.cxx")

  list( APPEND TKMeshVS_USED_SRCFILES "../../../src/MeshVS/MeshVS_VectorPrsBuilder.cxx" )
  SOURCE_GROUP (MeshVS FILES "../../../src/MeshVS/MeshVS_VectorPrsBuilder.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKMeshVS)
 add_library( TKMeshVS SHARED ${TKMeshVS_USED_SRCFILES} )

 set_property(TARGET TKMeshVS PROPERTY FOLDER Visualization)

 install( TARGETS TKMeshVS
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKMeshVS.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKMeshVS PROPERTIES COMPILE_FLAGS "${TKMeshVS_PRECOMPILED_DEFS}" )
 include_directories( ${TKMeshVS_COMPILER_DIRECTORIES} )
 target_link_libraries( TKMeshVS ${TKMeshVS_USED_LIBS} )
endif()
