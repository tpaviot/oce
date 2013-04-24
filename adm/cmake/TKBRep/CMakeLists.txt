project(TKBRep)

if (WIN32)
  list( APPEND TKBRep_PRECOMPILED_DEFS "-D__TopoDS_DLL" )
  list( APPEND TKBRep_PRECOMPILED_DEFS "-D__TopExp_DLL" )
  list( APPEND TKBRep_PRECOMPILED_DEFS "-D__TopTools_DLL" )
  list( APPEND TKBRep_PRECOMPILED_DEFS "-D__BRep_DLL" )
  list( APPEND TKBRep_PRECOMPILED_DEFS "-D__BRepLProp_DLL" )
  list( APPEND TKBRep_PRECOMPILED_DEFS "-D__BRepAdaptor_DLL" )
  list( APPEND TKBRep_PRECOMPILED_DEFS "-D__BRepTools_DLL" )
  string( REGEX REPLACE ";" " " TKBRep_PRECOMPILED_DEFS "${TKBRep_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKBRep_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKBRep_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKBRep_COMPILER_DIRECTORIES "../../../drv/TopoDS" )
  list( APPEND TKBRep_COMPILER_DIRECTORIES "../../../src/TopoDS" )
  list( APPEND TKBRep_COMPILER_DIRECTORIES "../../../drv/TopExp" )
  list( APPEND TKBRep_COMPILER_DIRECTORIES "../../../src/TopExp" )
  list( APPEND TKBRep_COMPILER_DIRECTORIES "../../../drv/TopTools" )
  list( APPEND TKBRep_COMPILER_DIRECTORIES "../../../src/TopTools" )
  list( APPEND TKBRep_COMPILER_DIRECTORIES "../../../drv/BRep" )
  list( APPEND TKBRep_COMPILER_DIRECTORIES "../../../src/BRep" )
  list( APPEND TKBRep_COMPILER_DIRECTORIES "../../../drv/BRepLProp" )
  list( APPEND TKBRep_COMPILER_DIRECTORIES "../../../src/BRepLProp" )
  list( APPEND TKBRep_COMPILER_DIRECTORIES "../../../drv/BRepAdaptor" )
  list( APPEND TKBRep_COMPILER_DIRECTORIES "../../../src/BRepAdaptor" )
  list( APPEND TKBRep_COMPILER_DIRECTORIES "../../../drv/BRepTools" )
  list( APPEND TKBRep_COMPILER_DIRECTORIES "../../../src/BRepTools" )

if (WIN32)
else()
endif()

  list( APPEND TKBRep_USED_LIBS TKMath )
  list( APPEND TKBRep_USED_LIBS TKernel )
  list( APPEND TKBRep_USED_LIBS TKG2d )
  list( APPEND TKBRep_USED_LIBS TKG3d )
  list( APPEND TKBRep_USED_LIBS TKGeomBase )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopoDS/TopoDS_FrozenShape_0.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../drv/TopoDS/TopoDS_FrozenShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopoDS/TopoDS_ListIteratorOfListOfShape_0.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../drv/TopoDS/TopoDS_ListIteratorOfListOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopoDS/TopoDS_ListNodeOfListOfShape_0.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../drv/TopoDS/TopoDS_ListNodeOfListOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopoDS/TopoDS_ListOfShape_0.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../drv/TopoDS/TopoDS_ListOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopoDS/TopoDS_UnCompatibleShapes_0.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../drv/TopoDS/TopoDS_UnCompatibleShapes_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_Builder.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_Builder.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_CompSolid.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_CompSolid.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_Compound.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_Compound.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_Edge.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_Edge.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_Face.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_Face.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_HShape.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_HShape.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_Iterator.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_Iterator.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_Shape.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_Shape.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_Shell.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_Shell.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_Solid.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_Solid.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_TCompSolid.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_TCompSolid.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_TCompound.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_TCompound.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_TEdge.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_TEdge.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_TFace.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_TFace.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_TShape.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_TShape.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_TShell.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_TShell.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_TSolid.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_TSolid.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_TVertex.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_TVertex.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_TWire.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_TWire.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_Vertex.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_Vertex.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopoDS/TopoDS_Wire.cxx" )
  SOURCE_GROUP (TopoDS FILES "../../../src/TopoDS/TopoDS_Wire.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopExp/TopExp_StackIteratorOfStackOfIterator_0.cxx" )
  SOURCE_GROUP (TopExp FILES "../../../drv/TopExp/TopExp_StackIteratorOfStackOfIterator_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopExp/TopExp_StackNodeOfStackOfIterator_0.cxx" )
  SOURCE_GROUP (TopExp FILES "../../../drv/TopExp/TopExp_StackNodeOfStackOfIterator_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopExp/TopExp_StackOfIterator_0.cxx" )
  SOURCE_GROUP (TopExp FILES "../../../drv/TopExp/TopExp_StackOfIterator_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopExp/TopExp.cxx" )
  SOURCE_GROUP (TopExp FILES "../../../src/TopExp/TopExp.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopExp/TopExp_Explorer.cxx" )
  SOURCE_GROUP (TopExp FILES "../../../src/TopExp/TopExp_Explorer.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_Array1OfListOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_Array1OfListOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_Array1OfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_Array1OfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_Array2OfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_Array2OfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfIntegerListOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfIntegerListOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfIntegerShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfIntegerShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfOrientedShapeInteger_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfOrientedShapeInteger_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfOrientedShapeShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfOrientedShapeShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfShapeInteger_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfShapeInteger_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfShapeListOfInteger_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfShapeListOfInteger_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfShapeListOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfShapeListOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfShapeReal_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfShapeReal_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfShapeSequenceOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfShapeSequenceOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfShapeShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapIteratorOfDataMapOfShapeShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfIntegerListOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfIntegerListOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfIntegerShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfIntegerShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfOrientedShapeInteger_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfOrientedShapeInteger_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfOrientedShapeShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfOrientedShapeShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfShapeInteger_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfShapeInteger_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfShapeListOfInteger_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfShapeListOfInteger_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfShapeListOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfShapeListOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfShapeReal_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfShapeReal_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfShapeSequenceOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfShapeSequenceOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfShapeShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapNodeOfDataMapOfShapeShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapOfIntegerListOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapOfIntegerListOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapOfIntegerShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapOfIntegerShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapOfOrientedShapeInteger_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapOfOrientedShapeInteger_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapOfOrientedShapeShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapOfOrientedShapeShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapOfShapeInteger_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapOfShapeInteger_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapOfShapeListOfInteger_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapOfShapeListOfInteger_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapOfShapeListOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapOfShapeListOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapOfShapeReal_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapOfShapeReal_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapOfShapeSequenceOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapOfShapeSequenceOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_DataMapOfShapeShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_DataMapOfShapeShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_HArray1OfListOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_HArray1OfListOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_HArray1OfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_HArray1OfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_HArray2OfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_HArray2OfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_HSequenceOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_HSequenceOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_IndexedDataMapNodeOfIndexedDataMapOfShapeAddress_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_IndexedDataMapNodeOfIndexedDataMapOfShapeAddress_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_IndexedDataMapNodeOfIndexedDataMapOfShapeListOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_IndexedDataMapNodeOfIndexedDataMapOfShapeListOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_IndexedDataMapNodeOfIndexedDataMapOfShapeShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_IndexedDataMapNodeOfIndexedDataMapOfShapeShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_IndexedDataMapOfShapeAddress_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_IndexedDataMapOfShapeAddress_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_IndexedDataMapOfShapeListOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_IndexedDataMapOfShapeListOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_IndexedDataMapOfShapeShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_IndexedDataMapOfShapeShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_IndexedMapNodeOfIndexedMapOfOrientedShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_IndexedMapNodeOfIndexedMapOfOrientedShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_IndexedMapNodeOfIndexedMapOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_IndexedMapNodeOfIndexedMapOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_IndexedMapOfOrientedShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_IndexedMapOfOrientedShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_IndexedMapOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_IndexedMapOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_ListIteratorOfListOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_ListIteratorOfListOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_ListNodeOfListOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_ListNodeOfListOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_ListOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_ListOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_MapIteratorOfMapOfOrientedShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_MapIteratorOfMapOfOrientedShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_MapIteratorOfMapOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_MapIteratorOfMapOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_MapOfOrientedShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_MapOfOrientedShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_MapOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_MapOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_SequenceNodeOfSequenceOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_SequenceNodeOfSequenceOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_SequenceOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_SequenceOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_StdMapNodeOfMapOfOrientedShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_StdMapNodeOfMapOfOrientedShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/TopTools/TopTools_StdMapNodeOfMapOfShape_0.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../drv/TopTools/TopTools_StdMapNodeOfMapOfShape_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopTools/TopTools.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../src/TopTools/TopTools.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopTools/TopTools_LocationSet.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../src/TopTools/TopTools_LocationSet.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopTools/TopTools_MutexForShapeProvider.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../src/TopTools/TopTools_MutexForShapeProvider.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopTools/TopTools_OrientedShapeMapHasher.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../src/TopTools/TopTools_OrientedShapeMapHasher.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopTools/TopTools_ShapeMapHasher.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../src/TopTools/TopTools_ShapeMapHasher.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/TopTools/TopTools_ShapeSet.cxx" )
  SOURCE_GROUP (TopTools FILES "../../../src/TopTools/TopTools_ShapeSet.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/BRep/BRep_ListIteratorOfListOfCurveRepresentation_0.cxx" )
  SOURCE_GROUP (BRep FILES "../../../drv/BRep/BRep_ListIteratorOfListOfCurveRepresentation_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/BRep/BRep_ListIteratorOfListOfPointRepresentation_0.cxx" )
  SOURCE_GROUP (BRep FILES "../../../drv/BRep/BRep_ListIteratorOfListOfPointRepresentation_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/BRep/BRep_ListNodeOfListOfCurveRepresentation_0.cxx" )
  SOURCE_GROUP (BRep FILES "../../../drv/BRep/BRep_ListNodeOfListOfCurveRepresentation_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/BRep/BRep_ListNodeOfListOfPointRepresentation_0.cxx" )
  SOURCE_GROUP (BRep FILES "../../../drv/BRep/BRep_ListNodeOfListOfPointRepresentation_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/BRep/BRep_ListOfCurveRepresentation_0.cxx" )
  SOURCE_GROUP (BRep FILES "../../../drv/BRep/BRep_ListOfCurveRepresentation_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/BRep/BRep_ListOfPointRepresentation_0.cxx" )
  SOURCE_GROUP (BRep FILES "../../../drv/BRep/BRep_ListOfPointRepresentation_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_Builder.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_Builder.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_Curve3D.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_Curve3D.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_CurveOn2Surfaces.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_CurveOn2Surfaces.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_CurveOnClosedSurface.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_CurveOnClosedSurface.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_CurveOnSurface.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_CurveOnSurface.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_CurveRepresentation.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_CurveRepresentation.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_GCurve.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_GCurve.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_PointOnCurve.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_PointOnCurve.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_PointOnCurveOnSurface.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_PointOnCurveOnSurface.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_PointOnSurface.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_PointOnSurface.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_PointRepresentation.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_PointRepresentation.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_PointsOnSurface.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_PointsOnSurface.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_Polygon3D.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_Polygon3D.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_PolygonOnClosedSurface.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_PolygonOnClosedSurface.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_PolygonOnClosedTriangulation.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_PolygonOnClosedTriangulation.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_PolygonOnSurface.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_PolygonOnSurface.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_PolygonOnTriangulation.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_PolygonOnTriangulation.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_TEdge.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_TEdge.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_TFace.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_TFace.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_TVertex.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_TVertex.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRep/BRep_Tool.cxx" )
  SOURCE_GROUP (BRep FILES "../../../src/BRep/BRep_Tool.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/BRepLProp/BRepLProp_CLProps_0.cxx" )
  SOURCE_GROUP (BRepLProp FILES "../../../drv/BRepLProp/BRepLProp_CLProps_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/BRepLProp/BRepLProp_SLProps_0.cxx" )
  SOURCE_GROUP (BRepLProp FILES "../../../drv/BRepLProp/BRepLProp_SLProps_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRepLProp/BRepLProp.cxx" )
  SOURCE_GROUP (BRepLProp FILES "../../../src/BRepLProp/BRepLProp.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRepLProp/BRepLProp_CurveTool.cxx" )
  SOURCE_GROUP (BRepLProp FILES "../../../src/BRepLProp/BRepLProp_CurveTool.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRepLProp/BRepLProp_SurfaceTool.cxx" )
  SOURCE_GROUP (BRepLProp FILES "../../../src/BRepLProp/BRepLProp_SurfaceTool.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/BRepAdaptor/BRepAdaptor_Array1OfCurve_0.cxx" )
  SOURCE_GROUP (BRepAdaptor FILES "../../../drv/BRepAdaptor/BRepAdaptor_Array1OfCurve_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/BRepAdaptor/BRepAdaptor_HArray1OfCurve_0.cxx" )
  SOURCE_GROUP (BRepAdaptor FILES "../../../drv/BRepAdaptor/BRepAdaptor_HArray1OfCurve_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/BRepAdaptor/BRepAdaptor_HCompCurve_0.cxx" )
  SOURCE_GROUP (BRepAdaptor FILES "../../../drv/BRepAdaptor/BRepAdaptor_HCompCurve_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/BRepAdaptor/BRepAdaptor_HCurve2d_0.cxx" )
  SOURCE_GROUP (BRepAdaptor FILES "../../../drv/BRepAdaptor/BRepAdaptor_HCurve2d_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/BRepAdaptor/BRepAdaptor_HCurve_0.cxx" )
  SOURCE_GROUP (BRepAdaptor FILES "../../../drv/BRepAdaptor/BRepAdaptor_HCurve_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/BRepAdaptor/BRepAdaptor_HSurface_0.cxx" )
  SOURCE_GROUP (BRepAdaptor FILES "../../../drv/BRepAdaptor/BRepAdaptor_HSurface_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRepAdaptor/BRepAdaptor_CompCurve.cxx" )
  SOURCE_GROUP (BRepAdaptor FILES "../../../src/BRepAdaptor/BRepAdaptor_CompCurve.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRepAdaptor/BRepAdaptor_Curve.cxx" )
  SOURCE_GROUP (BRepAdaptor FILES "../../../src/BRepAdaptor/BRepAdaptor_Curve.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRepAdaptor/BRepAdaptor_Curve2d.cxx" )
  SOURCE_GROUP (BRepAdaptor FILES "../../../src/BRepAdaptor/BRepAdaptor_Curve2d.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRepAdaptor/BRepAdaptor_Surface.cxx" )
  SOURCE_GROUP (BRepAdaptor FILES "../../../src/BRepAdaptor/BRepAdaptor_Surface.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/BRepTools/BRepTools_DataMapIteratorOfMapOfVertexPnt2d_0.cxx" )
  SOURCE_GROUP (BRepTools FILES "../../../drv/BRepTools/BRepTools_DataMapIteratorOfMapOfVertexPnt2d_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/BRepTools/BRepTools_DataMapNodeOfMapOfVertexPnt2d_0.cxx" )
  SOURCE_GROUP (BRepTools FILES "../../../drv/BRepTools/BRepTools_DataMapNodeOfMapOfVertexPnt2d_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../drv/BRepTools/BRepTools_MapOfVertexPnt2d_0.cxx" )
  SOURCE_GROUP (BRepTools FILES "../../../drv/BRepTools/BRepTools_MapOfVertexPnt2d_0.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRepTools/BRepTools.cxx" )
  SOURCE_GROUP (BRepTools FILES "../../../src/BRepTools/BRepTools.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRepTools/BRepTools_GTrsfModification.cxx" )
  SOURCE_GROUP (BRepTools FILES "../../../src/BRepTools/BRepTools_GTrsfModification.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRepTools/BRepTools_Modification.cxx" )
  SOURCE_GROUP (BRepTools FILES "../../../src/BRepTools/BRepTools_Modification.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRepTools/BRepTools_Modifier.cxx" )
  SOURCE_GROUP (BRepTools FILES "../../../src/BRepTools/BRepTools_Modifier.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRepTools/BRepTools_NurbsConvertModification.cxx" )
  SOURCE_GROUP (BRepTools FILES "../../../src/BRepTools/BRepTools_NurbsConvertModification.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRepTools/BRepTools_Quilt.cxx" )
  SOURCE_GROUP (BRepTools FILES "../../../src/BRepTools/BRepTools_Quilt.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRepTools/BRepTools_ReShape.cxx" )
  SOURCE_GROUP (BRepTools FILES "../../../src/BRepTools/BRepTools_ReShape.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRepTools/BRepTools_ShapeSet.cxx" )
  SOURCE_GROUP (BRepTools FILES "../../../src/BRepTools/BRepTools_ShapeSet.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRepTools/BRepTools_Substitution.cxx" )
  SOURCE_GROUP (BRepTools FILES "../../../src/BRepTools/BRepTools_Substitution.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRepTools/BRepTools_TrsfModification.cxx" )
  SOURCE_GROUP (BRepTools FILES "../../../src/BRepTools/BRepTools_TrsfModification.cxx")

  list( APPEND TKBRep_USED_SRCFILES "../../../src/BRepTools/BRepTools_WireExplorer.cxx" )
  SOURCE_GROUP (BRepTools FILES "../../../src/BRepTools/BRepTools_WireExplorer.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKBRep)
 add_library( TKBRep SHARED ${TKBRep_USED_SRCFILES} )

 set_property(TARGET TKBRep PROPERTY FOLDER ModelingData)

 install( TARGETS TKBRep
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKBRep.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKBRep PROPERTIES COMPILE_FLAGS "${TKBRep_PRECOMPILED_DEFS}" )
 include_directories( ${TKBRep_COMPILER_DIRECTORIES} )
 target_link_libraries( TKBRep ${TKBRep_USED_LIBS} )
endif()
