project(TKSTL)

if (WIN32)
  list( APPEND TKSTL_PRECOMPILED_DEFS "-D__StlMesh_DLL" )
  list( APPEND TKSTL_PRECOMPILED_DEFS "-D__StlAPI_DLL" )
  list( APPEND TKSTL_PRECOMPILED_DEFS "-D__StlTransfer_DLL" )
  list( APPEND TKSTL_PRECOMPILED_DEFS "-D__RWStl_DLL" )
  string( REGEX REPLACE ";" " " TKSTL_PRECOMPILED_DEFS "${TKSTL_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKSTL_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKSTL_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKSTL_COMPILER_DIRECTORIES "../../../drv/StlMesh" )
  list( APPEND TKSTL_COMPILER_DIRECTORIES "../../../src/StlMesh" )
  list( APPEND TKSTL_COMPILER_DIRECTORIES "../../../drv/StlAPI" )
  list( APPEND TKSTL_COMPILER_DIRECTORIES "../../../src/StlAPI" )
  list( APPEND TKSTL_COMPILER_DIRECTORIES "../../../drv/StlTransfer" )
  list( APPEND TKSTL_COMPILER_DIRECTORIES "../../../src/StlTransfer" )
  list( APPEND TKSTL_COMPILER_DIRECTORIES "../../../drv/RWStl" )
  list( APPEND TKSTL_COMPILER_DIRECTORIES "../../../src/RWStl" )

if (WIN32)
else()
endif()

  list( APPEND TKSTL_USED_LIBS TKernel )
  list( APPEND TKSTL_USED_LIBS TKMath )
  list( APPEND TKSTL_USED_LIBS TKBRep )
  list( APPEND TKSTL_USED_LIBS TKG2d )
  list( APPEND TKSTL_USED_LIBS TKG3d )
  list( APPEND TKSTL_USED_LIBS TKMesh )
  list( APPEND TKSTL_USED_LIBS TKTopAlgo )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKSTL_USED_SRCFILES "../../../drv/StlMesh/StlMesh_SequenceNodeOfSequenceOfMeshDomain_0.cxx" )
  SOURCE_GROUP (StlMesh FILES "../../../drv/StlMesh/StlMesh_SequenceNodeOfSequenceOfMeshDomain_0.cxx")

  list( APPEND TKSTL_USED_SRCFILES "../../../drv/StlMesh/StlMesh_SequenceNodeOfSequenceOfMeshTriangle_0.cxx" )
  SOURCE_GROUP (StlMesh FILES "../../../drv/StlMesh/StlMesh_SequenceNodeOfSequenceOfMeshTriangle_0.cxx")

  list( APPEND TKSTL_USED_SRCFILES "../../../drv/StlMesh/StlMesh_SequenceNodeOfSequenceOfMesh_0.cxx" )
  SOURCE_GROUP (StlMesh FILES "../../../drv/StlMesh/StlMesh_SequenceNodeOfSequenceOfMesh_0.cxx")

  list( APPEND TKSTL_USED_SRCFILES "../../../drv/StlMesh/StlMesh_SequenceOfMeshDomain_0.cxx" )
  SOURCE_GROUP (StlMesh FILES "../../../drv/StlMesh/StlMesh_SequenceOfMeshDomain_0.cxx")

  list( APPEND TKSTL_USED_SRCFILES "../../../drv/StlMesh/StlMesh_SequenceOfMeshTriangle_0.cxx" )
  SOURCE_GROUP (StlMesh FILES "../../../drv/StlMesh/StlMesh_SequenceOfMeshTriangle_0.cxx")

  list( APPEND TKSTL_USED_SRCFILES "../../../drv/StlMesh/StlMesh_SequenceOfMesh_0.cxx" )
  SOURCE_GROUP (StlMesh FILES "../../../drv/StlMesh/StlMesh_SequenceOfMesh_0.cxx")

  list( APPEND TKSTL_USED_SRCFILES "../../../src/StlMesh/StlMesh.cxx" )
  SOURCE_GROUP (StlMesh FILES "../../../src/StlMesh/StlMesh.cxx")

  list( APPEND TKSTL_USED_SRCFILES "../../../src/StlMesh/StlMesh_Mesh.cxx" )
  SOURCE_GROUP (StlMesh FILES "../../../src/StlMesh/StlMesh_Mesh.cxx")

  list( APPEND TKSTL_USED_SRCFILES "../../../src/StlMesh/StlMesh_MeshDomain.cxx" )
  SOURCE_GROUP (StlMesh FILES "../../../src/StlMesh/StlMesh_MeshDomain.cxx")

  list( APPEND TKSTL_USED_SRCFILES "../../../src/StlMesh/StlMesh_MeshExplorer.cxx" )
  SOURCE_GROUP (StlMesh FILES "../../../src/StlMesh/StlMesh_MeshExplorer.cxx")

  list( APPEND TKSTL_USED_SRCFILES "../../../src/StlMesh/StlMesh_MeshTriangle.cxx" )
  SOURCE_GROUP (StlMesh FILES "../../../src/StlMesh/StlMesh_MeshTriangle.cxx")

  list( APPEND TKSTL_USED_SRCFILES "../../../src/StlAPI/StlAPI.cxx" )
  SOURCE_GROUP (StlAPI FILES "../../../src/StlAPI/StlAPI.cxx")

  list( APPEND TKSTL_USED_SRCFILES "../../../src/StlAPI/StlAPI_Reader.cxx" )
  SOURCE_GROUP (StlAPI FILES "../../../src/StlAPI/StlAPI_Reader.cxx")

  list( APPEND TKSTL_USED_SRCFILES "../../../src/StlAPI/StlAPI_Writer.cxx" )
  SOURCE_GROUP (StlAPI FILES "../../../src/StlAPI/StlAPI_Writer.cxx")

  list( APPEND TKSTL_USED_SRCFILES "../../../src/StlTransfer/StlTransfer.cxx" )
  SOURCE_GROUP (StlTransfer FILES "../../../src/StlTransfer/StlTransfer.cxx")

  list( APPEND TKSTL_USED_SRCFILES "../../../src/RWStl/RWStl.cxx" )
  SOURCE_GROUP (RWStl FILES "../../../src/RWStl/RWStl.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKSTL)
 add_library( TKSTL SHARED ${TKSTL_USED_SRCFILES} )

 set_property(TARGET TKSTL PROPERTY FOLDER DataExchange)

 install( TARGETS TKSTL
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKSTL.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKSTL PROPERTIES COMPILE_FLAGS "${TKSTL_PRECOMPILED_DEFS}" )
 include_directories( ${TKSTL_COMPILER_DIRECTORIES} )
 target_link_libraries( TKSTL ${TKSTL_USED_LIBS} )
endif()
