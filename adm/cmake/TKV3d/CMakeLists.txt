project(TKV3d)

if (WIN32)
  list( APPEND TKV3d_PRECOMPILED_DEFS "-D__V3d_DLL" )
  list( APPEND TKV3d_PRECOMPILED_DEFS "-D__Graphic3d_DLL" )
  list( APPEND TKV3d_PRECOMPILED_DEFS "-D__Visual3d_DLL" )
  list( APPEND TKV3d_PRECOMPILED_DEFS "-D__Select3D_DLL" )
  list( APPEND TKV3d_PRECOMPILED_DEFS "-D__Prs3d_DLL" )
  list( APPEND TKV3d_PRECOMPILED_DEFS "-D__StdPrs_DLL" )
  list( APPEND TKV3d_PRECOMPILED_DEFS "-D__SelectMgr_DLL" )
  list( APPEND TKV3d_PRECOMPILED_DEFS "-D__PrsMgr_DLL" )
  list( APPEND TKV3d_PRECOMPILED_DEFS "-D__AIS_DLL" )
  list( APPEND TKV3d_PRECOMPILED_DEFS "-D__DsgPrs_DLL" )
  list( APPEND TKV3d_PRECOMPILED_DEFS "-D__StdSelect_DLL" )
  string( REGEX REPLACE ";" " " TKV3d_PRECOMPILED_DEFS "${TKV3d_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKV3d_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../drv/V3d" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../src/V3d" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../drv/Graphic3d" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../src/Graphic3d" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../drv/Visual3d" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../src/Visual3d" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../drv/Select3D" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../src/Select3D" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../drv/Prs3d" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../src/Prs3d" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../drv/StdPrs" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../src/StdPrs" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../drv/SelectMgr" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../src/SelectMgr" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../drv/PrsMgr" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../src/PrsMgr" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../drv/AIS" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../src/AIS" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../drv/DsgPrs" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../src/DsgPrs" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../drv/StdSelect" )
  list( APPEND TKV3d_COMPILER_DIRECTORIES "../../../src/StdSelect" )

if (WIN32)
else()
endif()

  list( APPEND TKV3d_USED_LIBS TKBRep )
  list( APPEND TKV3d_USED_LIBS TKMath )
  list( APPEND TKV3d_USED_LIBS TKernel )
  list( APPEND TKV3d_USED_LIBS TKService )
  list( APPEND TKV3d_USED_LIBS TKTopAlgo )
  list( APPEND TKV3d_USED_LIBS TKG2d )
  list( APPEND TKV3d_USED_LIBS TKG3d )
  list( APPEND TKV3d_USED_LIBS TKGeomBase )
  list( APPEND TKV3d_USED_LIBS TKMesh )
  list( APPEND TKV3d_USED_LIBS TKGeomAlgo )
  list( APPEND TKV3d_USED_LIBS TKHLR )

if (WIN32)
  list( APPEND TKV3d_USED_LIBS user32.lib )
  list( APPEND TKV3d_USED_LIBS gdi32.lib )
  list( APPEND TKV3d_USED_LIBS opengl32.lib )
  list( APPEND TKV3d_USED_LIBS glu32.lib )
elseif(APPLE)
  find_library(FRAMEWORKS_OPENGL NAMES OpenGL)
  if(3RDPARTY_USE_GLX)
    list( APPEND TKV3d_USED_LIBS GL )
    list( APPEND TKV3d_USED_LIBS GLU )
  else()
    list( APPEND TKV3d_USED_LIBS ${FRAMEWORKS_OPENGL} )
  endif()
else()
  list( APPEND TKV3d_USED_LIBS GLU )
  list( APPEND TKV3d_USED_LIBS GL )
endif()

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/V3d/V3d_BadValue_0.cxx" )
  SOURCE_GROUP (V3d FILES "../../../drv/V3d/V3d_BadValue_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/V3d/V3d_UnMapped_0.cxx" )
  SOURCE_GROUP (V3d FILES "../../../drv/V3d/V3d_UnMapped_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_AmbientLight.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_AmbientLight.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_CircularGrid.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_CircularGrid.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_ColorScale.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_ColorScale.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_ColorScaleLayerItem.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_ColorScaleLayerItem.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_DirectionalLight.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_DirectionalLight.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_LayerMgr.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_LayerMgr.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_Light.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_Light.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_ListOfTransient.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_ListOfTransient.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_OrthographicView.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_OrthographicView.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_PerspectiveView.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_PerspectiveView.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_Plane.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_Plane.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_PositionLight.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_PositionLight.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_PositionalLight.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_PositionalLight.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_RectangularGrid.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_RectangularGrid.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_SpotLight.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_SpotLight.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_View.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_View.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_View_1.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_View_1.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_View_2.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_View_2.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_View_3.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_View_3.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_View_4.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_View_4.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_View_5.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_View_5.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_View_Print.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_View_Print.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_Viewer.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_Viewer.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_Viewer_1.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_Viewer_1.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_Viewer_2.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_Viewer_2.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_Viewer_3.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_Viewer_3.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/V3d/V3d_Viewer_4.cxx" )
  SOURCE_GROUP (V3d FILES "../../../src/V3d/V3d_Viewer_4.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_Array1OfVector_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_Array1OfVector_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_Array1OfVertex_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_Array1OfVertex_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_Array2OfVertex_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_Array2OfVertex_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_AspectTextDefinitionError_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_AspectTextDefinitionError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_CycleError_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_CycleError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_GroupDefinitionError_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_GroupDefinitionError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_HSequenceOfGroup_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_HSequenceOfGroup_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_HSequenceOfStructure_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_HSequenceOfStructure_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_HSetOfGroup_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_HSetOfGroup_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_InitialisationError_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_InitialisationError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_ListIteratorOfListOfPArray_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_ListIteratorOfListOfPArray_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_ListIteratorOfListOfShortReal_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_ListIteratorOfListOfShortReal_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_ListIteratorOfSetListOfSetOfGroup_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_ListIteratorOfSetListOfSetOfGroup_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_ListNodeOfListOfPArray_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_ListNodeOfListOfPArray_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_ListNodeOfListOfShortReal_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_ListNodeOfListOfShortReal_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_ListNodeOfSetListOfSetOfGroup_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_ListNodeOfSetListOfSetOfGroup_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_ListOfPArray_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_ListOfPArray_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_ListOfShortReal_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_ListOfShortReal_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_MapIteratorOfMapOfStructure_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_MapIteratorOfMapOfStructure_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_MapOfStructure_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_MapOfStructure_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_MaterialDefinitionError_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_MaterialDefinitionError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_PickIdDefinitionError_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_PickIdDefinitionError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_PlotterDefinitionError_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_PlotterDefinitionError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_PriorityDefinitionError_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_PriorityDefinitionError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_SequenceNodeOfSequenceOfAddress_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_SequenceNodeOfSequenceOfAddress_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_SequenceNodeOfSequenceOfGroup_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_SequenceNodeOfSequenceOfGroup_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_SequenceNodeOfSequenceOfStructure_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_SequenceNodeOfSequenceOfStructure_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_SequenceOfAddress_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_SequenceOfAddress_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_SequenceOfGroup_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_SequenceOfGroup_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_SequenceOfStructure_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_SequenceOfStructure_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_SetIteratorOfSetOfGroup_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_SetIteratorOfSetOfGroup_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_SetListOfSetOfGroup_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_SetListOfSetOfGroup_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_SetOfGroup_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_SetOfGroup_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_StdMapNodeOfMapOfStructure_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_StdMapNodeOfMapOfStructure_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_StructureDefinitionError_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_StructureDefinitionError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_TransformError_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_TransformError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Graphic3d/Graphic3d_VectorError_0.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../drv/Graphic3d/Graphic3d_VectorError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_ArrayOfPoints.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_ArrayOfPoints.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_ArrayOfPolygons.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_ArrayOfPolygons.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_ArrayOfPolylines.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_ArrayOfPolylines.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_ArrayOfPrimitives.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_ArrayOfPrimitives.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_ArrayOfQuadrangleStrips.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_ArrayOfQuadrangleStrips.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_ArrayOfQuadrangles.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_ArrayOfQuadrangles.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_ArrayOfSegments.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_ArrayOfSegments.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_ArrayOfTriangleFans.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_ArrayOfTriangleFans.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_ArrayOfTriangleStrips.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_ArrayOfTriangleStrips.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_ArrayOfTriangles.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_ArrayOfTriangles.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_AspectFillArea3d.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_AspectFillArea3d.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_AspectLine3d.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_AspectLine3d.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_AspectMarker3d.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_AspectMarker3d.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_AspectText3d.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_AspectText3d.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_CBitFields16.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_CBitFields16.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_CBitFields20.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_CBitFields20.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_CBitFields4.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_CBitFields4.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_CBitFields8.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_CBitFields8.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_CBounds.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_CBounds.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_CGraduatedTrihedron.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_CGraduatedTrihedron.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_CGroup.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_CGroup.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_CLight.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_CLight.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_CPick.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_CPick.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_CPlane.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_CPlane.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_CStructure.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_CStructure.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_CTexture.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_CTexture.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_CTransPersStruct.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_CTransPersStruct.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_CUserDraw.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_CUserDraw.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_CView.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_CView.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_DataStructureManager.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_DataStructureManager.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_GraphicDriver.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_GraphicDriver.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_Group.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_Group.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_Group_1.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_Group_1.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_Group_10.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_Group_10.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_Group_13.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_Group_13.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_Group_2.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_Group_2.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_Group_3.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_Group_3.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_Group_8.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_Group_8.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_MaterialAspect.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_MaterialAspect.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_Plotter.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_Plotter.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_Strips.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_Strips.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_Structure.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_Structure.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_StructureManager.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_StructureManager.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_Texture1D.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_Texture1D.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_Texture1Dmanual.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_Texture1Dmanual.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_Texture1Dsegment.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_Texture1Dsegment.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_Texture2D.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_Texture2D.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_Texture2Dmanual.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_Texture2Dmanual.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_Texture2Dplane.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_Texture2Dplane.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_TextureEnv.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_TextureEnv.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_TextureMap.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_TextureMap.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_TextureParams.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_TextureParams.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_TextureRoot.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_TextureRoot.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_Vector.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_Vector.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Graphic3d/Graphic3d_Vertex.cxx" )
  SOURCE_GROUP (Graphic3d FILES "../../../src/Graphic3d/Graphic3d_Vertex.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_ClipDefinitionError_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_ClipDefinitionError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_ContextPickDefinitionError_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_ContextPickDefinitionError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_DepthCueingDefinitionError_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_DepthCueingDefinitionError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_HSequenceOfPickPath_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_HSequenceOfPickPath_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_HSetOfClipPlane_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_HSetOfClipPlane_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_HSetOfLight_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_HSetOfLight_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_HSetOfView_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_HSetOfView_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_LayerDefinitionError_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_LayerDefinitionError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_LightDefinitionError_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_LightDefinitionError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_ListIteratorOfSetListOfSetOfClipPlane_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_ListIteratorOfSetListOfSetOfClipPlane_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_ListIteratorOfSetListOfSetOfLight_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_ListIteratorOfSetListOfSetOfLight_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_ListIteratorOfSetListOfSetOfView_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_ListIteratorOfSetListOfSetOfView_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_ListNodeOfSetListOfSetOfClipPlane_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_ListNodeOfSetListOfSetOfClipPlane_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_ListNodeOfSetListOfSetOfLight_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_ListNodeOfSetListOfSetOfLight_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_ListNodeOfSetListOfSetOfView_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_ListNodeOfSetListOfSetOfView_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_PickError_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_PickError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_SequenceNodeOfSequenceOfPickPath_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_SequenceNodeOfSequenceOfPickPath_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_SequenceOfPickPath_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_SequenceOfPickPath_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_SetIteratorOfSetOfClipPlane_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_SetIteratorOfSetOfClipPlane_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_SetIteratorOfSetOfLight_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_SetIteratorOfSetOfLight_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_SetIteratorOfSetOfView_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_SetIteratorOfSetOfView_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_SetListOfSetOfClipPlane_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_SetListOfSetOfClipPlane_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_SetListOfSetOfLight_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_SetListOfSetOfLight_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_SetListOfSetOfView_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_SetListOfSetOfView_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_SetOfClipPlane_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_SetOfClipPlane_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_SetOfLight_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_SetOfLight_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_SetOfView_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_SetOfView_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_TransformError_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_TransformError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_TransientDefinitionError_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_TransientDefinitionError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_ViewDefinitionError_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_ViewDefinitionError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_ViewManagerDefinitionError_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_ViewManagerDefinitionError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_ViewMappingDefinitionError_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_ViewMappingDefinitionError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_ViewOrientationDefinitionError_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_ViewOrientationDefinitionError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Visual3d/Visual3d_ZClippingDefinitionError_0.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../drv/Visual3d/Visual3d_ZClippingDefinitionError_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Visual3d/Visual3d_ClipPlane.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../src/Visual3d/Visual3d_ClipPlane.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Visual3d/Visual3d_ContextPick.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../src/Visual3d/Visual3d_ContextPick.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Visual3d/Visual3d_ContextView.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../src/Visual3d/Visual3d_ContextView.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Visual3d/Visual3d_Layer.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../src/Visual3d/Visual3d_Layer.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Visual3d/Visual3d_LayerItem.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../src/Visual3d/Visual3d_LayerItem.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Visual3d/Visual3d_Light.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../src/Visual3d/Visual3d_Light.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Visual3d/Visual3d_PickDescriptor.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../src/Visual3d/Visual3d_PickDescriptor.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Visual3d/Visual3d_PickPath.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../src/Visual3d/Visual3d_PickPath.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Visual3d/Visual3d_TransientManager.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../src/Visual3d/Visual3d_TransientManager.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Visual3d/Visual3d_View.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../src/Visual3d/Visual3d_View.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Visual3d/Visual3d_ViewManager.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../src/Visual3d/Visual3d_ViewManager.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Visual3d/Visual3d_ViewMapping.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../src/Visual3d/Visual3d_ViewMapping.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Visual3d/Visual3d_ViewOrientation.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../src/Visual3d/Visual3d_ViewOrientation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Visual3d/Visual3d_View_Print.cxx" )
  SOURCE_GROUP (Visual3d FILES "../../../src/Visual3d/Visual3d_View_Print.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Select3D/Select3D_ListIteratorOfListOfSensitiveTriangle_0.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../drv/Select3D/Select3D_ListIteratorOfListOfSensitiveTriangle_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Select3D/Select3D_ListIteratorOfListOfSensitive_0.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../drv/Select3D/Select3D_ListIteratorOfListOfSensitive_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Select3D/Select3D_ListNodeOfListOfSensitiveTriangle_0.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../drv/Select3D/Select3D_ListNodeOfListOfSensitiveTriangle_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Select3D/Select3D_ListNodeOfListOfSensitive_0.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../drv/Select3D/Select3D_ListNodeOfListOfSensitive_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Select3D/Select3D_ListOfSensitiveTriangle_0.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../drv/Select3D/Select3D_ListOfSensitiveTriangle_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Select3D/Select3D_ListOfSensitive_0.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../drv/Select3D/Select3D_ListOfSensitive_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Select3D/Select3D_SensitiveEntitySequence_0.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../drv/Select3D/Select3D_SensitiveEntitySequence_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Select3D/Select3D_SequenceNodeOfSensitiveEntitySequence_0.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../drv/Select3D/Select3D_SequenceNodeOfSensitiveEntitySequence_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Select3D/Select3D_Projector.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../src/Select3D/Select3D_Projector.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Select3D/Select3D_SensitiveBox.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../src/Select3D/Select3D_SensitiveBox.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Select3D/Select3D_SensitiveCircle.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../src/Select3D/Select3D_SensitiveCircle.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Select3D/Select3D_SensitiveCurve.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../src/Select3D/Select3D_SensitiveCurve.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Select3D/Select3D_SensitiveEntity.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../src/Select3D/Select3D_SensitiveEntity.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Select3D/Select3D_SensitiveFace.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../src/Select3D/Select3D_SensitiveFace.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Select3D/Select3D_SensitiveGroup.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../src/Select3D/Select3D_SensitiveGroup.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Select3D/Select3D_SensitivePoint.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../src/Select3D/Select3D_SensitivePoint.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Select3D/Select3D_SensitivePoly.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../src/Select3D/Select3D_SensitivePoly.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Select3D/Select3D_SensitiveSegment.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../src/Select3D/Select3D_SensitiveSegment.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Select3D/Select3D_SensitiveTriangle.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../src/Select3D/Select3D_SensitiveTriangle.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Select3D/Select3D_SensitiveTriangulation.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../src/Select3D/Select3D_SensitiveTriangulation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Select3D/Select3D_SensitiveWire.cxx" )
  SOURCE_GROUP (Select3D FILES "../../../src/Select3D/Select3D_SensitiveWire.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/Prs3d/Prs3d_InvalidAngle_0.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../drv/Prs3d/Prs3d_InvalidAngle_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_AngleAspect.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_AngleAspect.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_AnglePresentation.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_AnglePresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_Arrow.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_Arrow.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_ArrowAspect.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_ArrowAspect.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_BasicAspect.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_BasicAspect.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_CompositeAspect.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_CompositeAspect.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_DatumAspect.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_DatumAspect.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_Drawer.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_Drawer.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_IsoAspect.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_IsoAspect.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_LengthAspect.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_LengthAspect.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_LengthPresentation.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_LengthPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_LineAspect.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_LineAspect.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_PlaneAspect.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_PlaneAspect.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_PlaneSet.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_PlaneSet.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_PointAspect.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_PointAspect.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_Presentation.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_Presentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_Projector.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_Projector.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_RadiusAspect.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_RadiusAspect.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_Root.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_Root.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_ShadingAspect.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_ShadingAspect.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_ShapeTool.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_ShapeTool.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_Text.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_Text.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/Prs3d/Prs3d_TextAspect.cxx" )
  SOURCE_GROUP (Prs3d FILES "../../../src/Prs3d/Prs3d_TextAspect.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/StdPrs/StdPrs_HLRShape_0.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../drv/StdPrs/StdPrs_HLRShape_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/StdPrs/StdPrs_Point_0.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../drv/StdPrs/StdPrs_Point_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/StdPrs/StdPrs_Vertex_0.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../drv/StdPrs/StdPrs_Vertex_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/StdPrs/StdPrs_WFDeflectionShape_0.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../drv/StdPrs/StdPrs_WFDeflectionShape_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/StdPrs/StdPrs_WFRestrictedFace_0.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../drv/StdPrs/StdPrs_WFRestrictedFace_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/StdPrs/StdPrs_WFShape_0.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../drv/StdPrs/StdPrs_WFShape_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdPrs/StdPrs_Curve.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../src/StdPrs/StdPrs_Curve.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdPrs/StdPrs_DeflectionCurve.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../src/StdPrs/StdPrs_DeflectionCurve.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdPrs/StdPrs_HLRPolyShape.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../src/StdPrs/StdPrs_HLRPolyShape.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdPrs/StdPrs_HLRToolShape.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../src/StdPrs/StdPrs_HLRToolShape.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdPrs/StdPrs_Plane.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../src/StdPrs/StdPrs_Plane.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdPrs/StdPrs_PoleCurve.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../src/StdPrs/StdPrs_PoleCurve.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdPrs/StdPrs_ShadedShape.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../src/StdPrs/StdPrs_ShadedShape.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdPrs/StdPrs_ShadedSurface.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../src/StdPrs/StdPrs_ShadedSurface.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdPrs/StdPrs_ToolPoint.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../src/StdPrs/StdPrs_ToolPoint.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdPrs/StdPrs_ToolRFace.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../src/StdPrs/StdPrs_ToolRFace.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdPrs/StdPrs_ToolShadedShape.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../src/StdPrs/StdPrs_ToolShadedShape.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdPrs/StdPrs_ToolVertex.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../src/StdPrs/StdPrs_ToolVertex.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdPrs/StdPrs_WFDeflectionRestrictedFace.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../src/StdPrs/StdPrs_WFDeflectionRestrictedFace.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdPrs/StdPrs_WFDeflectionSurface.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../src/StdPrs/StdPrs_WFDeflectionSurface.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdPrs/StdPrs_WFPoleSurface.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../src/StdPrs/StdPrs_WFPoleSurface.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdPrs/StdPrs_WFSurface.cxx" )
  SOURCE_GROUP (StdPrs FILES "../../../src/StdPrs/StdPrs_WFSurface.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_DataMapIteratorOfDataMapOfIntegerSensitive_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_DataMapIteratorOfDataMapOfIntegerSensitive_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_DataMapIteratorOfDataMapOfObjectSelectors_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_DataMapIteratorOfDataMapOfObjectSelectors_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_DataMapIteratorOfDataMapOfSelectionActivation_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_DataMapIteratorOfDataMapOfSelectionActivation_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_DataMapNodeOfDataMapOfIntegerSensitive_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_DataMapNodeOfDataMapOfIntegerSensitive_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_DataMapNodeOfDataMapOfObjectSelectors_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_DataMapNodeOfDataMapOfObjectSelectors_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_DataMapNodeOfDataMapOfSelectionActivation_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_DataMapNodeOfDataMapOfSelectionActivation_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_DataMapOfIntegerSensitive_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_DataMapOfIntegerSensitive_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_DataMapOfObjectSelectors_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_DataMapOfObjectSelectors_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_DataMapOfSelectionActivation_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_DataMapOfSelectionActivation_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_IndexedDataMapNodeOfIndexedDataMapOfOwnerCriterion_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_IndexedDataMapNodeOfIndexedDataMapOfOwnerCriterion_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_IndexedDataMapOfOwnerCriterion_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_IndexedDataMapOfOwnerCriterion_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_IndexedMapNodeOfIndexedMapOfOwner_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_IndexedMapNodeOfIndexedMapOfOwner_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_IndexedMapOfOwner_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_IndexedMapOfOwner_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_ListIteratorOfListOfFilter_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_ListIteratorOfListOfFilter_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_ListNodeOfListOfFilter_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_ListNodeOfListOfFilter_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_ListOfFilter_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_ListOfFilter_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_SequenceNodeOfSequenceOfFilter_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_SequenceNodeOfSequenceOfFilter_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_SequenceNodeOfSequenceOfOwner_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_SequenceNodeOfSequenceOfOwner_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_SequenceNodeOfSequenceOfSelection_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_SequenceNodeOfSequenceOfSelection_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_SequenceNodeOfSequenceOfSelector_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_SequenceNodeOfSequenceOfSelector_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_SequenceOfFilter_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_SequenceOfFilter_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_SequenceOfOwner_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_SequenceOfOwner_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_SequenceOfSelection_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_SequenceOfSelection_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/SelectMgr/SelectMgr_SequenceOfSelector_0.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../drv/SelectMgr/SelectMgr_SequenceOfSelector_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/SelectMgr/SelectMgr_AndFilter.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../src/SelectMgr/SelectMgr_AndFilter.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/SelectMgr/SelectMgr_CompositionFilter.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../src/SelectMgr/SelectMgr_CompositionFilter.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/SelectMgr/SelectMgr_EntityOwner.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../src/SelectMgr/SelectMgr_EntityOwner.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/SelectMgr/SelectMgr_Filter.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../src/SelectMgr/SelectMgr_Filter.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/SelectMgr/SelectMgr_OrFilter.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../src/SelectMgr/SelectMgr_OrFilter.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/SelectMgr/SelectMgr_SelectableObject.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../src/SelectMgr/SelectMgr_SelectableObject.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/SelectMgr/SelectMgr_Selection.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../src/SelectMgr/SelectMgr_Selection.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/SelectMgr/SelectMgr_SelectionManager.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../src/SelectMgr/SelectMgr_SelectionManager.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/SelectMgr/SelectMgr_SortCriterion.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../src/SelectMgr/SelectMgr_SortCriterion.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/SelectMgr/SelectMgr_ViewerSelector.cxx" )
  SOURCE_GROUP (SelectMgr FILES "../../../src/SelectMgr/SelectMgr_ViewerSelector.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/PrsMgr/PrsMgr_Presentations_0.cxx" )
  SOURCE_GROUP (PrsMgr FILES "../../../drv/PrsMgr/PrsMgr_Presentations_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/PrsMgr/PrsMgr_SequenceNodeOfPresentations_0.cxx" )
  SOURCE_GROUP (PrsMgr FILES "../../../drv/PrsMgr/PrsMgr_SequenceNodeOfPresentations_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/PrsMgr/PrsMgr_ModedPresentation.cxx" )
  SOURCE_GROUP (PrsMgr FILES "../../../src/PrsMgr/PrsMgr_ModedPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/PrsMgr/PrsMgr_PresentableObject.cxx" )
  SOURCE_GROUP (PrsMgr FILES "../../../src/PrsMgr/PrsMgr_PresentableObject.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/PrsMgr/PrsMgr_Presentation.cxx" )
  SOURCE_GROUP (PrsMgr FILES "../../../src/PrsMgr/PrsMgr_Presentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/PrsMgr/PrsMgr_Presentation3d.cxx" )
  SOURCE_GROUP (PrsMgr FILES "../../../src/PrsMgr/PrsMgr_Presentation3d.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/PrsMgr/PrsMgr_PresentationManager.cxx" )
  SOURCE_GROUP (PrsMgr FILES "../../../src/PrsMgr/PrsMgr_PresentationManager.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/PrsMgr/PrsMgr_PresentationManager3d.cxx" )
  SOURCE_GROUP (PrsMgr FILES "../../../src/PrsMgr/PrsMgr_PresentationManager3d.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/PrsMgr/PrsMgr_Prs.cxx" )
  SOURCE_GROUP (PrsMgr FILES "../../../src/PrsMgr/PrsMgr_Prs.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_DataMapIteratorOfDataMapOfILC_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_DataMapIteratorOfDataMapOfILC_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_DataMapIteratorOfDataMapOfIOStatus_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_DataMapIteratorOfDataMapOfIOStatus_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_DataMapIteratorOfDataMapOfSelStat_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_DataMapIteratorOfDataMapOfSelStat_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_DataMapIteratorOfDataMapofIntegerListOfinteractive_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_DataMapIteratorOfDataMapofIntegerListOfinteractive_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_DataMapNodeOfDataMapOfILC_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_DataMapNodeOfDataMapOfILC_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_DataMapNodeOfDataMapOfIOStatus_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_DataMapNodeOfDataMapOfIOStatus_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_DataMapNodeOfDataMapOfSelStat_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_DataMapNodeOfDataMapOfSelStat_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_DataMapNodeOfDataMapofIntegerListOfinteractive_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_DataMapNodeOfDataMapofIntegerListOfinteractive_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_DataMapOfILC_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_DataMapOfILC_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_DataMapOfIOStatus_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_DataMapOfIOStatus_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_DataMapOfSelStat_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_DataMapOfSelStat_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_DataMapofIntegerListOfinteractive_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_DataMapofIntegerListOfinteractive_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_IndexedDataMapNodeOfIndexedDataMapOfOwnerPrs_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_IndexedDataMapNodeOfIndexedDataMapOfOwnerPrs_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_IndexedDataMapOfOwnerPrs_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_IndexedDataMapOfOwnerPrs_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_ListIteratorOfListOfInteractive_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_ListIteratorOfListOfInteractive_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_ListNodeOfListOfInteractive_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_ListNodeOfListOfInteractive_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_ListOfInteractive_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_ListOfInteractive_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_MapIteratorOfMapOfInteractive_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_MapIteratorOfMapOfInteractive_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_MapOfInteractive_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_MapOfInteractive_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_SequenceNodeOfSequenceOfDimension_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_SequenceNodeOfSequenceOfDimension_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_SequenceNodeOfSequenceOfInteractive_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_SequenceNodeOfSequenceOfInteractive_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_SequenceOfDimension_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_SequenceOfDimension_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_SequenceOfInteractive_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_SequenceOfInteractive_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/AIS/AIS_StdMapNodeOfMapOfInteractive_0.cxx" )
  SOURCE_GROUP (AIS FILES "../../../drv/AIS/AIS_StdMapNodeOfMapOfInteractive_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_AngleDimension.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_AngleDimension.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_AttributeFilter.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_AttributeFilter.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_Axis.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_Axis.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_BadEdgeFilter.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_BadEdgeFilter.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_C0RegularityFilter.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_C0RegularityFilter.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_Chamf2dDimension.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_Chamf2dDimension.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_Chamf3dDimension.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_Chamf3dDimension.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_Circle.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_Circle.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_ConcentricRelation.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_ConcentricRelation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_ConnectedInteractive.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_ConnectedInteractive.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_ConnectedShape.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_ConnectedShape.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_DiameterDimension.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_DiameterDimension.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_DimensionOwner.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_DimensionOwner.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_Drawer.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_Drawer.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_EllipseRadiusDimension.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_EllipseRadiusDimension.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_EqualDistanceRelation.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_EqualDistanceRelation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_EqualRadiusRelation.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_EqualRadiusRelation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_ExclusionFilter.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_ExclusionFilter.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_FixRelation.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_FixRelation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_GlobalStatus.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_GlobalStatus.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_GraphicTool.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_GraphicTool.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_IdenticRelation.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_IdenticRelation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_InteractiveContext.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_InteractiveContext.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_InteractiveContext_1.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_InteractiveContext_1.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_InteractiveContext_2.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_InteractiveContext_2.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_InteractiveContext_3.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_InteractiveContext_3.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_InteractiveObject.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_InteractiveObject.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_LengthDimension.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_LengthDimension.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_Line.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_Line.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_LocalContext.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_LocalContext.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_LocalContext_1.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_LocalContext_1.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_LocalStatus.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_LocalStatus.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_MaxRadiusDimension.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_MaxRadiusDimension.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_MidPointRelation.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_MidPointRelation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_MinRadiusDimension.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_MinRadiusDimension.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_MultipleConnectedInteractive.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_MultipleConnectedInteractive.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_MultipleConnectedShape.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_MultipleConnectedShape.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_OffsetDimension.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_OffsetDimension.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_ParallelRelation.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_ParallelRelation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_PerpendicularRelation.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_PerpendicularRelation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_Plane.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_Plane.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_PlaneTrihedron.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_PlaneTrihedron.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_Point.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_Point.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_RadiusDimension.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_RadiusDimension.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_Relation.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_Relation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_Selection.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_Selection.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_Shape.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_Shape.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_SignatureFilter.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_SignatureFilter.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_SymmetricRelation.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_SymmetricRelation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_TangentRelation.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_TangentRelation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_TexturedShape.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_TexturedShape.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_Triangulation.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_Triangulation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_Trihedron.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_Trihedron.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/AIS/AIS_TypeFilter.cxx" )
  SOURCE_GROUP (AIS FILES "../../../src/AIS/AIS_TypeFilter.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/DsgPrs/DsgPrs_DatumPrs_0.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../drv/DsgPrs/DsgPrs_DatumPrs_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_AnglePresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_AnglePresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_Chamf2dPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_Chamf2dPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_ConcentricPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_ConcentricPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_DatumTool.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_DatumTool.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_DiameterPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_DiameterPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_EllipseRadiusPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_EllipseRadiusPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_EqualDistancePresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_EqualDistancePresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_EqualRadiusPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_EqualRadiusPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_FilletRadiusPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_FilletRadiusPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_FixPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_FixPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_IdenticPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_IdenticPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_LengthPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_LengthPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_MidPointPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_MidPointPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_OffsetPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_OffsetPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_ParalPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_ParalPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_PerpenPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_PerpenPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_RadiusPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_RadiusPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_ShadedPlanePresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_ShadedPlanePresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_ShapeDirPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_ShapeDirPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_SymbPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_SymbPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_SymmetricPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_SymmetricPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_TangentPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_TangentPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_XYZAxisPresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_XYZAxisPresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/DsgPrs/DsgPrs_XYZPlanePresentation.cxx" )
  SOURCE_GROUP (DsgPrs FILES "../../../src/DsgPrs/DsgPrs_XYZPlanePresentation.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/StdSelect/StdSelect_IndexedDataMapNodeOfIndexedDataMapOfOwnerPrs_0.cxx" )
  SOURCE_GROUP (StdSelect FILES "../../../drv/StdSelect/StdSelect_IndexedDataMapNodeOfIndexedDataMapOfOwnerPrs_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../drv/StdSelect/StdSelect_IndexedDataMapOfOwnerPrs_0.cxx" )
  SOURCE_GROUP (StdSelect FILES "../../../drv/StdSelect/StdSelect_IndexedDataMapOfOwnerPrs_0.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdSelect/StdSelect.cxx" )
  SOURCE_GROUP (StdSelect FILES "../../../src/StdSelect/StdSelect.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdSelect/StdSelect_BRepHilighter.cxx" )
  SOURCE_GROUP (StdSelect FILES "../../../src/StdSelect/StdSelect_BRepHilighter.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdSelect/StdSelect_BRepOwner.cxx" )
  SOURCE_GROUP (StdSelect FILES "../../../src/StdSelect/StdSelect_BRepOwner.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdSelect/StdSelect_BRepSelectionTool.cxx" )
  SOURCE_GROUP (StdSelect FILES "../../../src/StdSelect/StdSelect_BRepSelectionTool.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdSelect/StdSelect_EdgeFilter.cxx" )
  SOURCE_GROUP (StdSelect FILES "../../../src/StdSelect/StdSelect_EdgeFilter.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdSelect/StdSelect_FaceFilter.cxx" )
  SOURCE_GROUP (StdSelect FILES "../../../src/StdSelect/StdSelect_FaceFilter.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdSelect/StdSelect_Prs.cxx" )
  SOURCE_GROUP (StdSelect FILES "../../../src/StdSelect/StdSelect_Prs.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdSelect/StdSelect_Shape.cxx" )
  SOURCE_GROUP (StdSelect FILES "../../../src/StdSelect/StdSelect_Shape.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdSelect/StdSelect_ShapeTypeFilter.cxx" )
  SOURCE_GROUP (StdSelect FILES "../../../src/StdSelect/StdSelect_ShapeTypeFilter.cxx")

  list( APPEND TKV3d_USED_SRCFILES "../../../src/StdSelect/StdSelect_ViewerSelector3d.cxx" )
  SOURCE_GROUP (StdSelect FILES "../../../src/StdSelect/StdSelect_ViewerSelector3d.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKV3d)
 add_library( TKV3d SHARED ${TKV3d_USED_SRCFILES} )

 set_property(TARGET TKV3d PROPERTY FOLDER Visualization)

 install( TARGETS TKV3d
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKV3d.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKV3d PROPERTIES COMPILE_FLAGS "${TKV3d_PRECOMPILED_DEFS}" )
 include_directories( ${TKV3d_COMPILER_DIRECTORIES} )
 target_link_libraries( TKV3d ${TKV3d_USED_LIBS} )
endif()
