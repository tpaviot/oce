project(TKPrim)

if (WIN32)
  list( APPEND TKPrim_PRECOMPILED_DEFS "-D__BRepPrim_DLL" )
  list( APPEND TKPrim_PRECOMPILED_DEFS "-D__Primitives_DLL" )
  list( APPEND TKPrim_PRECOMPILED_DEFS "-D__BRepSweep_DLL" )
  list( APPEND TKPrim_PRECOMPILED_DEFS "-D__Sweep_DLL" )
  list( APPEND TKPrim_PRECOMPILED_DEFS "-D__BRepPrimAPI_DLL" )
  string( REGEX REPLACE ";" " " TKPrim_PRECOMPILED_DEFS "${TKPrim_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKPrim_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKPrim_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKPrim_COMPILER_DIRECTORIES "../../../drv/BRepPrim" )
  list( APPEND TKPrim_COMPILER_DIRECTORIES "../../../src/BRepPrim" )
  list( APPEND TKPrim_COMPILER_DIRECTORIES "../../../drv/Primitives" )
  list( APPEND TKPrim_COMPILER_DIRECTORIES "../../../src/Primitives" )
  list( APPEND TKPrim_COMPILER_DIRECTORIES "../../../drv/BRepSweep" )
  list( APPEND TKPrim_COMPILER_DIRECTORIES "../../../src/BRepSweep" )
  list( APPEND TKPrim_COMPILER_DIRECTORIES "../../../drv/Sweep" )
  list( APPEND TKPrim_COMPILER_DIRECTORIES "../../../src/Sweep" )
  list( APPEND TKPrim_COMPILER_DIRECTORIES "../../../drv/BRepPrimAPI" )
  list( APPEND TKPrim_COMPILER_DIRECTORIES "../../../src/BRepPrimAPI" )

if (WIN32)
else()
endif()

  list( APPEND TKPrim_USED_LIBS TKBRep )
  list( APPEND TKPrim_USED_LIBS TKernel )
  list( APPEND TKPrim_USED_LIBS TKMath )
  list( APPEND TKPrim_USED_LIBS TKG2d )
  list( APPEND TKPrim_USED_LIBS TKGeomBase )
  list( APPEND TKPrim_USED_LIBS TKG3d )
  list( APPEND TKPrim_USED_LIBS TKTopAlgo )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKPrim_USED_SRCFILES "../../../drv/BRepPrim/BRepPrim_GWedge_0.cxx" )
  SOURCE_GROUP (BRepPrim FILES "../../../drv/BRepPrim/BRepPrim_GWedge_0.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../drv/BRepPrim/BRepPrim_OneAxis_0.cxx" )
  SOURCE_GROUP (BRepPrim FILES "../../../drv/BRepPrim/BRepPrim_OneAxis_0.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrim/BRepPrim_Builder.cxx" )
  SOURCE_GROUP (BRepPrim FILES "../../../src/BRepPrim/BRepPrim_Builder.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrim/BRepPrim_Cone.cxx" )
  SOURCE_GROUP (BRepPrim FILES "../../../src/BRepPrim/BRepPrim_Cone.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrim/BRepPrim_Cylinder.cxx" )
  SOURCE_GROUP (BRepPrim FILES "../../../src/BRepPrim/BRepPrim_Cylinder.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrim/BRepPrim_FaceBuilder.cxx" )
  SOURCE_GROUP (BRepPrim FILES "../../../src/BRepPrim/BRepPrim_FaceBuilder.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrim/BRepPrim_Revolution.cxx" )
  SOURCE_GROUP (BRepPrim FILES "../../../src/BRepPrim/BRepPrim_Revolution.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrim/BRepPrim_Sphere.cxx" )
  SOURCE_GROUP (BRepPrim FILES "../../../src/BRepPrim/BRepPrim_Sphere.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrim/BRepPrim_Torus.cxx" )
  SOURCE_GROUP (BRepPrim FILES "../../../src/BRepPrim/BRepPrim_Torus.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrim/BRepPrim_Wedge.cxx" )
  SOURCE_GROUP (BRepPrim FILES "../../../src/BRepPrim/BRepPrim_Wedge.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../drv/BRepSweep/BRepSweep_Array2OfShapesOfNumLinearRegularSweep_0.cxx" )
  SOURCE_GROUP (BRepSweep FILES "../../../drv/BRepSweep/BRepSweep_Array2OfShapesOfNumLinearRegularSweep_0.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../drv/BRepSweep/BRepSweep_NumLinearRegularSweep_0.cxx" )
  SOURCE_GROUP (BRepSweep FILES "../../../drv/BRepSweep/BRepSweep_NumLinearRegularSweep_0.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../drv/BRepSweep/BRepSweep_SequenceNodeOfSequenceOfShapesOfNumLinearRegularSweep_0.cxx" )
  SOURCE_GROUP (BRepSweep FILES "../../../drv/BRepSweep/BRepSweep_SequenceNodeOfSequenceOfShapesOfNumLinearRegularSweep_0.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../drv/BRepSweep/BRepSweep_SequenceOfShapesOfNumLinearRegularSweep_0.cxx" )
  SOURCE_GROUP (BRepSweep FILES "../../../drv/BRepSweep/BRepSweep_SequenceOfShapesOfNumLinearRegularSweep_0.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepSweep/BRepSweep_Builder.cxx" )
  SOURCE_GROUP (BRepSweep FILES "../../../src/BRepSweep/BRepSweep_Builder.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepSweep/BRepSweep_Iterator.cxx" )
  SOURCE_GROUP (BRepSweep FILES "../../../src/BRepSweep/BRepSweep_Iterator.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepSweep/BRepSweep_Prism.cxx" )
  SOURCE_GROUP (BRepSweep FILES "../../../src/BRepSweep/BRepSweep_Prism.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepSweep/BRepSweep_Revol.cxx" )
  SOURCE_GROUP (BRepSweep FILES "../../../src/BRepSweep/BRepSweep_Revol.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepSweep/BRepSweep_Rotation.cxx" )
  SOURCE_GROUP (BRepSweep FILES "../../../src/BRepSweep/BRepSweep_Rotation.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepSweep/BRepSweep_Tool.cxx" )
  SOURCE_GROUP (BRepSweep FILES "../../../src/BRepSweep/BRepSweep_Tool.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepSweep/BRepSweep_Translation.cxx" )
  SOURCE_GROUP (BRepSweep FILES "../../../src/BRepSweep/BRepSweep_Translation.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepSweep/BRepSweep_Trsf.cxx" )
  SOURCE_GROUP (BRepSweep FILES "../../../src/BRepSweep/BRepSweep_Trsf.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/Sweep/Sweep_NumShape.cxx" )
  SOURCE_GROUP (Sweep FILES "../../../src/Sweep/Sweep_NumShape.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/Sweep/Sweep_NumShapeIterator.cxx" )
  SOURCE_GROUP (Sweep FILES "../../../src/Sweep/Sweep_NumShapeIterator.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/Sweep/Sweep_NumShapeTool.cxx" )
  SOURCE_GROUP (Sweep FILES "../../../src/Sweep/Sweep_NumShapeTool.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeBox.cxx" )
  SOURCE_GROUP (BRepPrimAPI FILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeBox.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeCone.cxx" )
  SOURCE_GROUP (BRepPrimAPI FILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeCone.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeCylinder.cxx" )
  SOURCE_GROUP (BRepPrimAPI FILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeCylinder.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeHalfSpace.cxx" )
  SOURCE_GROUP (BRepPrimAPI FILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeHalfSpace.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeOneAxis.cxx" )
  SOURCE_GROUP (BRepPrimAPI FILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeOneAxis.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakePrism.cxx" )
  SOURCE_GROUP (BRepPrimAPI FILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakePrism.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeRevol.cxx" )
  SOURCE_GROUP (BRepPrimAPI FILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeRevol.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeRevolution.cxx" )
  SOURCE_GROUP (BRepPrimAPI FILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeRevolution.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeSphere.cxx" )
  SOURCE_GROUP (BRepPrimAPI FILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeSphere.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeSweep.cxx" )
  SOURCE_GROUP (BRepPrimAPI FILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeSweep.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeTorus.cxx" )
  SOURCE_GROUP (BRepPrimAPI FILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeTorus.cxx")

  list( APPEND TKPrim_USED_SRCFILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeWedge.cxx" )
  SOURCE_GROUP (BRepPrimAPI FILES "../../../src/BRepPrimAPI/BRepPrimAPI_MakeWedge.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKPrim)
 add_library( TKPrim SHARED ${TKPrim_USED_SRCFILES} )

 set_property(TARGET TKPrim PROPERTY FOLDER ModelingAlgorithms)

 install( TARGETS TKPrim
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKPrim.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKPrim PROPERTIES COMPILE_FLAGS "${TKPrim_PRECOMPILED_DEFS}" )
 include_directories( ${TKPrim_COMPILER_DIRECTORIES} )
 target_link_libraries( TKPrim ${TKPrim_USED_LIBS} )
endif()
