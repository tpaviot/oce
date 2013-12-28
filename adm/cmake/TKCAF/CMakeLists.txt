project(TKCAF)

if (WIN32)
  list( APPEND TKCAF_PRECOMPILED_DEFS "-D__TDataXtd_DLL" )
  list( APPEND TKCAF_PRECOMPILED_DEFS "-D__TNaming_DLL" )
  list( APPEND TKCAF_PRECOMPILED_DEFS "-D__TPrsStd_DLL" )
  list( APPEND TKCAF_PRECOMPILED_DEFS "-D__AppStd_DLL" )
  string( REGEX REPLACE ";" " " TKCAF_PRECOMPILED_DEFS "${TKCAF_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKCAF_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKCAF_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKCAF_COMPILER_DIRECTORIES "../../../drv/TDataXtd" )
  list( APPEND TKCAF_COMPILER_DIRECTORIES "../../../src/TDataXtd" )
  list( APPEND TKCAF_COMPILER_DIRECTORIES "../../../drv/TNaming" )
  list( APPEND TKCAF_COMPILER_DIRECTORIES "../../../src/TNaming" )
  list( APPEND TKCAF_COMPILER_DIRECTORIES "../../../drv/TPrsStd" )
  list( APPEND TKCAF_COMPILER_DIRECTORIES "../../../src/TPrsStd" )
  list( APPEND TKCAF_COMPILER_DIRECTORIES "../../../drv/AppStd" )
  list( APPEND TKCAF_COMPILER_DIRECTORIES "../../../src/AppStd" )

if (WIN32)
else()
endif()

  list( APPEND TKCAF_USED_LIBS TKernel )
  list( APPEND TKCAF_USED_LIBS TKGeomBase )
  list( APPEND TKCAF_USED_LIBS TKBRep )
  list( APPEND TKCAF_USED_LIBS TKTopAlgo )
  list( APPEND TKCAF_USED_LIBS TKMath )
  list( APPEND TKCAF_USED_LIBS TKService )
  list( APPEND TKCAF_USED_LIBS TKG2d )
  list( APPEND TKCAF_USED_LIBS TKG3d )
  list( APPEND TKCAF_USED_LIBS TKCDF )
  list( APPEND TKCAF_USED_LIBS TKLCAF )
  list( APPEND TKCAF_USED_LIBS TKV3d )
  list( APPEND TKCAF_USED_LIBS TKBO )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TDataXtd/TDataXtd_Array1OfTrsf_0.cxx" )
  SOURCE_GROUP (TDataXtd FILES "../../../drv/TDataXtd/TDataXtd_Array1OfTrsf_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TDataXtd/TDataXtd_HArray1OfTrsf_0.cxx" )
  SOURCE_GROUP (TDataXtd FILES "../../../drv/TDataXtd/TDataXtd_HArray1OfTrsf_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TDataXtd/TDataXtd.cxx" )
  SOURCE_GROUP (TDataXtd FILES "../../../src/TDataXtd/TDataXtd.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TDataXtd/TDataXtd_Axis.cxx" )
  SOURCE_GROUP (TDataXtd FILES "../../../src/TDataXtd/TDataXtd_Axis.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TDataXtd/TDataXtd_Constraint.cxx" )
  SOURCE_GROUP (TDataXtd FILES "../../../src/TDataXtd/TDataXtd_Constraint.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TDataXtd/TDataXtd_Geometry.cxx" )
  SOURCE_GROUP (TDataXtd FILES "../../../src/TDataXtd/TDataXtd_Geometry.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TDataXtd/TDataXtd_Pattern.cxx" )
  SOURCE_GROUP (TDataXtd FILES "../../../src/TDataXtd/TDataXtd_Pattern.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TDataXtd/TDataXtd_PatternStd.cxx" )
  SOURCE_GROUP (TDataXtd FILES "../../../src/TDataXtd/TDataXtd_PatternStd.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TDataXtd/TDataXtd_Placement.cxx" )
  SOURCE_GROUP (TDataXtd FILES "../../../src/TDataXtd/TDataXtd_Placement.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TDataXtd/TDataXtd_Plane.cxx" )
  SOURCE_GROUP (TDataXtd FILES "../../../src/TDataXtd/TDataXtd_Plane.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TDataXtd/TDataXtd_Point.cxx" )
  SOURCE_GROUP (TDataXtd FILES "../../../src/TDataXtd/TDataXtd_Point.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TDataXtd/TDataXtd_Position.cxx" )
  SOURCE_GROUP (TDataXtd FILES "../../../src/TDataXtd/TDataXtd_Position.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TDataXtd/TDataXtd_Shape.cxx" )
  SOURCE_GROUP (TDataXtd FILES "../../../src/TDataXtd/TDataXtd_Shape.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_DataMapIteratorOfDataMapOfShapePtrRefShape_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_DataMapIteratorOfDataMapOfShapePtrRefShape_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_DataMapIteratorOfDataMapOfShapeShapesSet_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_DataMapIteratorOfDataMapOfShapeShapesSet_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_DataMapNodeOfDataMapOfShapePtrRefShape_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_DataMapNodeOfDataMapOfShapePtrRefShape_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_DataMapNodeOfDataMapOfShapeShapesSet_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_DataMapNodeOfDataMapOfShapeShapesSet_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_DataMapOfShapePtrRefShape_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_DataMapOfShapePtrRefShape_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_DataMapOfShapeShapesSet_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_DataMapOfShapeShapesSet_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_ListIteratorOfListOfIndexedDataMapOfShapeListOfShape_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_ListIteratorOfListOfIndexedDataMapOfShapeListOfShape_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_ListIteratorOfListOfMapOfShape_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_ListIteratorOfListOfMapOfShape_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_ListIteratorOfListOfNamedShape_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_ListIteratorOfListOfNamedShape_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_ListNodeOfListOfIndexedDataMapOfShapeListOfShape_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_ListNodeOfListOfIndexedDataMapOfShapeListOfShape_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_ListNodeOfListOfMapOfShape_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_ListNodeOfListOfMapOfShape_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_ListNodeOfListOfNamedShape_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_ListNodeOfListOfNamedShape_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_ListOfIndexedDataMapOfShapeListOfShape_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_ListOfIndexedDataMapOfShapeListOfShape_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_ListOfMapOfShape_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_ListOfMapOfShape_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_ListOfNamedShape_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_ListOfNamedShape_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_MapIteratorOfMapOfNamedShape_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_MapIteratorOfMapOfNamedShape_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_MapOfNamedShape_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_MapOfNamedShape_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_NamedShapeHasher_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_NamedShapeHasher_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TNaming/TNaming_StdMapNodeOfMapOfNamedShape_0.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../drv/TNaming/TNaming_StdMapNodeOfMapOfNamedShape_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_Builder.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_Builder.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_CopyShape.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_CopyShape.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_DeltaOnModification.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_DeltaOnModification.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_DeltaOnRemoval.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_DeltaOnRemoval.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_Identifier.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_Identifier.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_Iterator.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_Iterator.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_IteratorOnShapesSet.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_IteratorOnShapesSet.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_Localizer.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_Localizer.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_Name.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_Name.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_NamedShape.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_NamedShape.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_Naming.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_Naming.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_NamingTool.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_NamingTool.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_NewShapeIterator.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_NewShapeIterator.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_OldShapeIterator.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_OldShapeIterator.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_RefShape.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_RefShape.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_SameShapeIterator.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_SameShapeIterator.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_Scope.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_Scope.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_Selector.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_Selector.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_ShapesSet.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_ShapesSet.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_Tool.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_Tool.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_TranslateTool.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_TranslateTool.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_Translator.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_Translator.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TNaming/TNaming_UsedShapes.cxx" )
  SOURCE_GROUP (TNaming FILES "../../../src/TNaming/TNaming_UsedShapes.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TPrsStd/TPrsStd_DataMapIteratorOfDataMapOfGUIDDriver_0.cxx" )
  SOURCE_GROUP (TPrsStd FILES "../../../drv/TPrsStd/TPrsStd_DataMapIteratorOfDataMapOfGUIDDriver_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TPrsStd/TPrsStd_DataMapNodeOfDataMapOfGUIDDriver_0.cxx" )
  SOURCE_GROUP (TPrsStd FILES "../../../drv/TPrsStd/TPrsStd_DataMapNodeOfDataMapOfGUIDDriver_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../drv/TPrsStd/TPrsStd_DataMapOfGUIDDriver_0.cxx" )
  SOURCE_GROUP (TPrsStd FILES "../../../drv/TPrsStd/TPrsStd_DataMapOfGUIDDriver_0.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TPrsStd/TPrsStd_AISPresentation.cxx" )
  SOURCE_GROUP (TPrsStd FILES "../../../src/TPrsStd/TPrsStd_AISPresentation.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TPrsStd/TPrsStd_AISViewer.cxx" )
  SOURCE_GROUP (TPrsStd FILES "../../../src/TPrsStd/TPrsStd_AISViewer.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TPrsStd/TPrsStd_AxisDriver.cxx" )
  SOURCE_GROUP (TPrsStd FILES "../../../src/TPrsStd/TPrsStd_AxisDriver.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TPrsStd/TPrsStd_ConstraintDriver.cxx" )
  SOURCE_GROUP (TPrsStd FILES "../../../src/TPrsStd/TPrsStd_ConstraintDriver.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TPrsStd/TPrsStd_ConstraintTools.cxx" )
  SOURCE_GROUP (TPrsStd FILES "../../../src/TPrsStd/TPrsStd_ConstraintTools.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TPrsStd/TPrsStd_Driver.cxx" )
  SOURCE_GROUP (TPrsStd FILES "../../../src/TPrsStd/TPrsStd_Driver.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TPrsStd/TPrsStd_DriverTable.cxx" )
  SOURCE_GROUP (TPrsStd FILES "../../../src/TPrsStd/TPrsStd_DriverTable.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TPrsStd/TPrsStd_GeometryDriver.cxx" )
  SOURCE_GROUP (TPrsStd FILES "../../../src/TPrsStd/TPrsStd_GeometryDriver.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TPrsStd/TPrsStd_NamedShapeDriver.cxx" )
  SOURCE_GROUP (TPrsStd FILES "../../../src/TPrsStd/TPrsStd_NamedShapeDriver.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TPrsStd/TPrsStd_PlaneDriver.cxx" )
  SOURCE_GROUP (TPrsStd FILES "../../../src/TPrsStd/TPrsStd_PlaneDriver.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/TPrsStd/TPrsStd_PointDriver.cxx" )
  SOURCE_GROUP (TPrsStd FILES "../../../src/TPrsStd/TPrsStd_PointDriver.cxx")

  list( APPEND TKCAF_USED_SRCFILES "../../../src/AppStd/AppStd_Application.cxx" )
  SOURCE_GROUP (AppStd FILES "../../../src/AppStd/AppStd_Application.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKCAF)
 add_library( TKCAF SHARED ${TKCAF_USED_SRCFILES} )

 set_property(TARGET TKCAF PROPERTY FOLDER ApplicationFramework)

 install( TARGETS TKCAF
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKCAF.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKCAF PROPERTIES COMPILE_FLAGS "${TKCAF_PRECOMPILED_DEFS}" )
 include_directories( ${TKCAF_COMPILER_DIRECTORIES} )
 target_link_libraries( TKCAF ${TKCAF_USED_LIBS} )
endif()
