project(TKQADraw)

if (WIN32)
  list( APPEND TKQADraw_PRECOMPILED_DEFS "-D__QABugs_DLL" )
  list( APPEND TKQADraw_PRECOMPILED_DEFS "-D__QADNaming_DLL" )
  list( APPEND TKQADraw_PRECOMPILED_DEFS "-D__QADraw_DLL" )
  list( APPEND TKQADraw_PRECOMPILED_DEFS "-D__QANCollection_DLL" )
  list( APPEND TKQADraw_PRECOMPILED_DEFS "-D__QANewBRepNaming_DLL" )
  list( APPEND TKQADraw_PRECOMPILED_DEFS "-D__QANewDBRepNaming_DLL" )
  list( APPEND TKQADraw_PRECOMPILED_DEFS "-D__QANewModTopOpe_DLL" )
  string( REGEX REPLACE ";" " " TKQADraw_PRECOMPILED_DEFS "${TKQADraw_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKQADraw_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKQADraw_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKQADraw_COMPILER_DIRECTORIES "../../../drv/QABugs" )
  list( APPEND TKQADraw_COMPILER_DIRECTORIES "../../../src/QABugs" )
  list( APPEND TKQADraw_COMPILER_DIRECTORIES "../../../drv/QADNaming" )
  list( APPEND TKQADraw_COMPILER_DIRECTORIES "../../../src/QADNaming" )
  list( APPEND TKQADraw_COMPILER_DIRECTORIES "../../../drv/QADraw" )
  list( APPEND TKQADraw_COMPILER_DIRECTORIES "../../../src/QADraw" )
  list( APPEND TKQADraw_COMPILER_DIRECTORIES "../../../drv/QANCollection" )
  list( APPEND TKQADraw_COMPILER_DIRECTORIES "../../../src/QANCollection" )
  list( APPEND TKQADraw_COMPILER_DIRECTORIES "../../../drv/QANewBRepNaming" )
  list( APPEND TKQADraw_COMPILER_DIRECTORIES "../../../src/QANewBRepNaming" )
  list( APPEND TKQADraw_COMPILER_DIRECTORIES "../../../drv/QANewDBRepNaming" )
  list( APPEND TKQADraw_COMPILER_DIRECTORIES "../../../src/QANewDBRepNaming" )
  list( APPEND TKQADraw_COMPILER_DIRECTORIES "../../../drv/QANewModTopOpe" )
  list( APPEND TKQADraw_COMPILER_DIRECTORIES "../../../src/QANewModTopOpe" )

if (WIN32)
else()
endif()

  list( APPEND TKQADraw_USED_LIBS TKBRep )
  list( APPEND TKQADraw_USED_LIBS TKNIS )
  list( APPEND TKQADraw_USED_LIBS TKMath )
  list( APPEND TKQADraw_USED_LIBS TKernel )
  list( APPEND TKQADraw_USED_LIBS TKService )
  list( APPEND TKQADraw_USED_LIBS TKG2d )
  list( APPEND TKQADraw_USED_LIBS TKDraw )
  list( APPEND TKQADraw_USED_LIBS PTKernel )
  list( APPEND TKQADraw_USED_LIBS TKV3d )
  list( APPEND TKQADraw_USED_LIBS TKGeomBase )
  list( APPEND TKQADraw_USED_LIBS TKG3d )
  list( APPEND TKQADraw_USED_LIBS TKViewerTest )
  list( APPEND TKQADraw_USED_LIBS TKCDF )
  list( APPEND TKQADraw_USED_LIBS TKDCAF )
  list( APPEND TKQADraw_USED_LIBS TKLCAF )
  list( APPEND TKQADraw_USED_LIBS TKFillet )
  list( APPEND TKQADraw_USED_LIBS TKTopAlgo )
  list( APPEND TKQADraw_USED_LIBS TKHLR )
  list( APPEND TKQADraw_USED_LIBS TKBool )
  list( APPEND TKQADraw_USED_LIBS TKGeomAlgo )
  list( APPEND TKQADraw_USED_LIBS TKPrim )
  list( APPEND TKQADraw_USED_LIBS TKBO )
  list( APPEND TKQADraw_USED_LIBS TKShHealing )
  list( APPEND TKQADraw_USED_LIBS TKOffset )
  list( APPEND TKQADraw_USED_LIBS TKFeat )
  list( APPEND TKQADraw_USED_LIBS TKCAF )
  list( APPEND TKQADraw_USED_LIBS TKIGES )
  list( APPEND TKQADraw_USED_LIBS TKXSBase )
  list( APPEND TKQADraw_USED_LIBS TKMesh )
  list( APPEND TKQADraw_USED_LIBS TKXCAF )
  list( APPEND TKQADraw_USED_LIBS TKSTEP )
  list( APPEND TKQADraw_USED_LIBS TKXDESTEP )
  list( APPEND TKQADraw_USED_LIBS TKXSDRAW )
  list( APPEND TKQADraw_USED_LIBS TKSTL )
  list( APPEND TKQADraw_USED_LIBS TKAdvTools )
  list( APPEND TKQADraw_USED_LIBS TKVoxel )

if (WIN32)
  list( APPEND TKQADraw_USED_LIBS gdi32.lib )
  list( APPEND TKQADraw_USED_LIBS advapi32.lib )
  list( APPEND TKQADraw_USED_LIBS user32.lib )
elseif(APPLE)
  if(USE_TBB)
    list( APPEND TKQADraw_USED_LIBS tbb )
  endif()
  if(USE_TBB)
    list( APPEND TKQADraw_USED_LIBS tbbmalloc )
  endif()
else()
  if(USE_TBB)
    list( APPEND TKQADraw_USED_LIBS tbb )
  endif()
  if(USE_TBB)
    list( APPEND TKQADraw_USED_LIBS tbbmalloc )
  endif()
endif()

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_1.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_1.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_10.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_10.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_11.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_11.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_12.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_12.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_13.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_13.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_14.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_14.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_15.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_15.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_16.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_16.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_17.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_17.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_18.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_18.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_19.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_19.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_2.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_2.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_3.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_3.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_4.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_4.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_5.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_5.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_6.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_6.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_7.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_7.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_8.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_8.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_9.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_9.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_MyText.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_MyText.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QABugs/QABugs_PresentableObject.cxx" )
  SOURCE_GROUP (QABugs FILES "../../../src/QABugs/QABugs_PresentableObject.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QADNaming/QADNaming_DataMapIteratorOfDataMapOfShapeOfName_0.cxx" )
  SOURCE_GROUP (QADNaming FILES "../../../drv/QADNaming/QADNaming_DataMapIteratorOfDataMapOfShapeOfName_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QADNaming/QADNaming_DataMapNodeOfDataMapOfShapeOfName_0.cxx" )
  SOURCE_GROUP (QADNaming FILES "../../../drv/QADNaming/QADNaming_DataMapNodeOfDataMapOfShapeOfName_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QADNaming/QADNaming_DataMapOfShapeOfName_0.cxx" )
  SOURCE_GROUP (QADNaming FILES "../../../drv/QADNaming/QADNaming_DataMapOfShapeOfName_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QADNaming/QADNaming.cxx" )
  SOURCE_GROUP (QADNaming FILES "../../../src/QADNaming/QADNaming.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QADNaming/QADNaming_BasicCommands.cxx" )
  SOURCE_GROUP (QADNaming FILES "../../../src/QADNaming/QADNaming_BasicCommands.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QADNaming/QADNaming_BuilderCommands.cxx" )
  SOURCE_GROUP (QADNaming FILES "../../../src/QADNaming/QADNaming_BuilderCommands.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QADNaming/QADNaming_IteratorsCommands.cxx" )
  SOURCE_GROUP (QADNaming FILES "../../../src/QADNaming/QADNaming_IteratorsCommands.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QADNaming/QADNaming_SelectionCommands.cxx" )
  SOURCE_GROUP (QADNaming FILES "../../../src/QADNaming/QADNaming_SelectionCommands.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QADNaming/QADNaming_ToolsCommands.cxx" )
  SOURCE_GROUP (QADNaming FILES "../../../src/QADNaming/QADNaming_ToolsCommands.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QADraw/QADraw.cxx" )
  SOURCE_GROUP (QADraw FILES "../../../src/QADraw/QADraw.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QADraw/QADraw_Additional.cxx" )
  SOURCE_GROUP (QADraw FILES "../../../src/QADraw/QADraw_Additional.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QANCollection/QANCollection_DataMapIteratorOfDataMapOfRealPnt_0.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../drv/QANCollection/QANCollection_DataMapIteratorOfDataMapOfRealPnt_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QANCollection/QANCollection_DataMapNodeOfDataMapOfRealPnt_0.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../drv/QANCollection/QANCollection_DataMapNodeOfDataMapOfRealPnt_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QANCollection/QANCollection_DataMapOfRealPnt_0.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../drv/QANCollection/QANCollection_DataMapOfRealPnt_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QANCollection/QANCollection_DoubleMapIteratorOfDoubleMapOfRealInteger_0.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../drv/QANCollection/QANCollection_DoubleMapIteratorOfDoubleMapOfRealInteger_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QANCollection/QANCollection_DoubleMapNodeOfDoubleMapOfRealInteger_0.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../drv/QANCollection/QANCollection_DoubleMapNodeOfDoubleMapOfRealInteger_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QANCollection/QANCollection_DoubleMapOfRealInteger_0.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../drv/QANCollection/QANCollection_DoubleMapOfRealInteger_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QANCollection/QANCollection_IndexedDataMapNodeOfIndexedDataMapOfRealPnt_0.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../drv/QANCollection/QANCollection_IndexedDataMapNodeOfIndexedDataMapOfRealPnt_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QANCollection/QANCollection_IndexedDataMapOfRealPnt_0.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../drv/QANCollection/QANCollection_IndexedDataMapOfRealPnt_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QANCollection/QANCollection_ListIteratorOfListOfPnt_0.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../drv/QANCollection/QANCollection_ListIteratorOfListOfPnt_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QANCollection/QANCollection_ListNodeOfListOfPnt_0.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../drv/QANCollection/QANCollection_ListNodeOfListOfPnt_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QANCollection/QANCollection_ListOfPnt_0.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../drv/QANCollection/QANCollection_ListOfPnt_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QANCollection/QANCollection_QueueNodeOfQueueOfPnt_0.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../drv/QANCollection/QANCollection_QueueNodeOfQueueOfPnt_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QANCollection/QANCollection_QueueOfPnt_0.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../drv/QANCollection/QANCollection_QueueOfPnt_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QANCollection/QANCollection_SListNodeOfSListOfPnt_0.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../drv/QANCollection/QANCollection_SListNodeOfSListOfPnt_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QANCollection/QANCollection_SListOfPnt_0.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../drv/QANCollection/QANCollection_SListOfPnt_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QANCollection/QANCollection_StackIteratorOfStackOfPnt_0.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../drv/QANCollection/QANCollection_StackIteratorOfStackOfPnt_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QANCollection/QANCollection_StackNodeOfStackOfPnt_0.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../drv/QANCollection/QANCollection_StackNodeOfStackOfPnt_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../drv/QANCollection/QANCollection_StackOfPnt_0.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../drv/QANCollection/QANCollection_StackOfPnt_0.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANCollection/QANCollection.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../src/QANCollection/QANCollection.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANCollection/QANCollection1.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../src/QANCollection/QANCollection1.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANCollection/QANCollection2.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../src/QANCollection/QANCollection2.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANCollection/QANCollection3.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../src/QANCollection/QANCollection3.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANCollection/QANCollection4.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../src/QANCollection/QANCollection4.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANCollection/QANCollectionTest.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../src/QANCollection/QANCollectionTest.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANCollection/QANCollection_Common.cxx" )
  SOURCE_GROUP (QANCollection FILES "../../../src/QANCollection/QANCollection_Common.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_BooleanOperation.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_BooleanOperation.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_BooleanOperationFeat.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_BooleanOperationFeat.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_Box.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_Box.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_Chamfer.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_Chamfer.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_Common.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_Common.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_Cut.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_Cut.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_Cylinder.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_Cylinder.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_Fillet.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_Fillet.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_Fuse.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_Fuse.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_Gluing.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_Gluing.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_ImportShape.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_ImportShape.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_Intersection.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_Intersection.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_Limitation.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_Limitation.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_Loader.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_Loader.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_LoaderParent.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_LoaderParent.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_Prism.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_Prism.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_Revol.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_Revol.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_Sphere.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_Sphere.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewBRepNaming/QANewBRepNaming_TopNaming.cxx" )
  SOURCE_GROUP (QANewBRepNaming FILES "../../../src/QANewBRepNaming/QANewBRepNaming_TopNaming.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewDBRepNaming/QANewDBRepNaming.cxx" )
  SOURCE_GROUP (QANewDBRepNaming FILES "../../../src/QANewDBRepNaming/QANewDBRepNaming.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewDBRepNaming/QANewDBRepNaming_FeatureCommands.cxx" )
  SOURCE_GROUP (QANewDBRepNaming FILES "../../../src/QANewDBRepNaming/QANewDBRepNaming_FeatureCommands.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewDBRepNaming/QANewDBRepNaming_PrimitiveCommands.cxx" )
  SOURCE_GROUP (QANewDBRepNaming FILES "../../../src/QANewDBRepNaming/QANewDBRepNaming_PrimitiveCommands.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewModTopOpe/QANewModTopOpe.cxx" )
  SOURCE_GROUP (QANewModTopOpe FILES "../../../src/QANewModTopOpe/QANewModTopOpe.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewModTopOpe/QANewModTopOpe_Glue.cxx" )
  SOURCE_GROUP (QANewModTopOpe FILES "../../../src/QANewModTopOpe/QANewModTopOpe_Glue.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewModTopOpe/QANewModTopOpe_Glue_SDFaces.cxx" )
  SOURCE_GROUP (QANewModTopOpe FILES "../../../src/QANewModTopOpe/QANewModTopOpe_Glue_SDFaces.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewModTopOpe/QANewModTopOpe_Glue_shell.cxx" )
  SOURCE_GROUP (QANewModTopOpe FILES "../../../src/QANewModTopOpe/QANewModTopOpe_Glue_shell.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewModTopOpe/QANewModTopOpe_Glue_util.cxx" )
  SOURCE_GROUP (QANewModTopOpe FILES "../../../src/QANewModTopOpe/QANewModTopOpe_Glue_util.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewModTopOpe/QANewModTopOpe_Glue_vertex.cxx" )
  SOURCE_GROUP (QANewModTopOpe FILES "../../../src/QANewModTopOpe/QANewModTopOpe_Glue_vertex.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewModTopOpe/QANewModTopOpe_Glue_wire.cxx" )
  SOURCE_GROUP (QANewModTopOpe FILES "../../../src/QANewModTopOpe/QANewModTopOpe_Glue_wire.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewModTopOpe/QANewModTopOpe_Intersection.cxx" )
  SOURCE_GROUP (QANewModTopOpe FILES "../../../src/QANewModTopOpe/QANewModTopOpe_Intersection.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewModTopOpe/QANewModTopOpe_Limitation.cxx" )
  SOURCE_GROUP (QANewModTopOpe FILES "../../../src/QANewModTopOpe/QANewModTopOpe_Limitation.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewModTopOpe/QANewModTopOpe_ReShaper.cxx" )
  SOURCE_GROUP (QANewModTopOpe FILES "../../../src/QANewModTopOpe/QANewModTopOpe_ReShaper.cxx")

  list( APPEND TKQADraw_USED_SRCFILES "../../../src/QANewModTopOpe/QANewModTopOpe_Tools.cxx" )
  SOURCE_GROUP (QANewModTopOpe FILES "../../../src/QANewModTopOpe/QANewModTopOpe_Tools.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKQADraw)
 add_library( TKQADraw SHARED ${TKQADraw_USED_SRCFILES} )

 set_property(TARGET TKQADraw PROPERTY FOLDER Draw)

 install( TARGETS TKQADraw
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKQADraw.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKQADraw PROPERTIES COMPILE_FLAGS "${TKQADraw_PRECOMPILED_DEFS}" )
 include_directories( ${TKQADraw_COMPILER_DIRECTORIES} )
 target_link_libraries( TKQADraw ${TKQADraw_USED_LIBS} )
endif()
