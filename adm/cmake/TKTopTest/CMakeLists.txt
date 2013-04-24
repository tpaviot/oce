project(TKTopTest)

if (WIN32)
  list( APPEND TKTopTest_PRECOMPILED_DEFS "-D__TestTopOpeDraw_DLL" )
  list( APPEND TKTopTest_PRECOMPILED_DEFS "-D__TestTopOpeTools_DLL" )
  list( APPEND TKTopTest_PRECOMPILED_DEFS "-D__TestTopOpe_DLL" )
  list( APPEND TKTopTest_PRECOMPILED_DEFS "-D__BRepTest_DLL" )
  list( APPEND TKTopTest_PRECOMPILED_DEFS "-D__GeometryTest_DLL" )
  list( APPEND TKTopTest_PRECOMPILED_DEFS "-D__HLRTest_DLL" )
  list( APPEND TKTopTest_PRECOMPILED_DEFS "-D__MeshTest_DLL" )
  list( APPEND TKTopTest_PRECOMPILED_DEFS "-D__GeomliteTest_DLL" )
  list( APPEND TKTopTest_PRECOMPILED_DEFS "-D__DrawFairCurve_DLL" )
  list( APPEND TKTopTest_PRECOMPILED_DEFS "-D__BOPTest_DLL" )
  string( REGEX REPLACE ";" " " TKTopTest_PRECOMPILED_DEFS "${TKTopTest_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKTopTest_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../drv/TestTopOpeDraw" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../src/TestTopOpeDraw" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../drv/TestTopOpeTools" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../src/TestTopOpeTools" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../drv/TestTopOpe" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../src/TestTopOpe" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../drv/BRepTest" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../src/BRepTest" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../drv/GeometryTest" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../src/GeometryTest" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../drv/HLRTest" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../src/HLRTest" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../drv/MeshTest" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../src/MeshTest" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../drv/GeomliteTest" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../src/GeomliteTest" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../drv/DrawFairCurve" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../src/DrawFairCurve" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../drv/BOPTest" )
  list( APPEND TKTopTest_COMPILER_DIRECTORIES "../../../src/BOPTest" )

if (WIN32)
else()
endif()

  list( APPEND TKTopTest_USED_LIBS TKBRep )
  list( APPEND TKTopTest_USED_LIBS TKGeomAlgo )
  list( APPEND TKTopTest_USED_LIBS TKTopAlgo )
  list( APPEND TKTopTest_USED_LIBS TKernel )
  list( APPEND TKTopTest_USED_LIBS TKMath )
  list( APPEND TKTopTest_USED_LIBS TKBO )
  list( APPEND TKTopTest_USED_LIBS TKG2d )
  list( APPEND TKTopTest_USED_LIBS TKG3d )
  list( APPEND TKTopTest_USED_LIBS TKDraw )
  list( APPEND TKTopTest_USED_LIBS TKHLR )
  list( APPEND TKTopTest_USED_LIBS TKGeomBase )
  list( APPEND TKTopTest_USED_LIBS TKMesh )
  list( APPEND TKTopTest_USED_LIBS TKService )
  list( APPEND TKTopTest_USED_LIBS TKV3d )
  list( APPEND TKTopTest_USED_LIBS TKFillet )
  list( APPEND TKTopTest_USED_LIBS TKPrim )
  list( APPEND TKTopTest_USED_LIBS TKBool )
  list( APPEND TKTopTest_USED_LIBS TKOffset )
  list( APPEND TKTopTest_USED_LIBS TKFeat )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKTopTest_USED_SRCFILES "../../../drv/TestTopOpeDraw/TestTopOpeDraw_Array1OfDrawableMesure_0.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../drv/TestTopOpeDraw/TestTopOpeDraw_Array1OfDrawableMesure_0.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../drv/TestTopOpeDraw/TestTopOpeDraw_Array1OfDrawableP3D_0.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../drv/TestTopOpeDraw/TestTopOpeDraw_Array1OfDrawableP3D_0.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../drv/TestTopOpeDraw/TestTopOpeDraw_HArray1OfDrawableMesure_0.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../drv/TestTopOpeDraw/TestTopOpeDraw_HArray1OfDrawableMesure_0.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../drv/TestTopOpeDraw/TestTopOpeDraw_HArray1OfDrawableP3D_0.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../drv/TestTopOpeDraw/TestTopOpeDraw_HArray1OfDrawableP3D_0.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../drv/TestTopOpeDraw/TestTopOpeDraw_ListIteratorOfListOfPnt2d_0.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../drv/TestTopOpeDraw/TestTopOpeDraw_ListIteratorOfListOfPnt2d_0.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../drv/TestTopOpeDraw/TestTopOpeDraw_ListNodeOfListOfPnt2d_0.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../drv/TestTopOpeDraw/TestTopOpeDraw_ListNodeOfListOfPnt2d_0.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../drv/TestTopOpeDraw/TestTopOpeDraw_ListOfPnt2d_0.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../drv/TestTopOpeDraw/TestTopOpeDraw_ListOfPnt2d_0.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpeDraw/TestTopOpeDraw.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../src/TestTopOpeDraw/TestTopOpeDraw.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_Displayer.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_Displayer.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_DrawableC2D.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_DrawableC2D.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_DrawableC3D.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_DrawableC3D.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_DrawableMesure.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_DrawableMesure.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_DrawableP2D.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_DrawableP2D.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_DrawableP3D.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_DrawableP3D.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_DrawableSHA.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_DrawableSHA.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_DrawableSUR.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_DrawableSUR.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_OtherCommands.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_OtherCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_SaveRestore.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_SaveRestore.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_TTOT.cxx" )
  SOURCE_GROUP (TestTopOpeDraw FILES "../../../src/TestTopOpeDraw/TestTopOpeDraw_TTOT.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../drv/TestTopOpeTools/TestTopOpeTools_Array1OfMesure_0.cxx" )
  SOURCE_GROUP (TestTopOpeTools FILES "../../../drv/TestTopOpeTools/TestTopOpeTools_Array1OfMesure_0.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../drv/TestTopOpeTools/TestTopOpeTools_HArray1OfMesure_0.cxx" )
  SOURCE_GROUP (TestTopOpeTools FILES "../../../drv/TestTopOpeTools/TestTopOpeTools_HArray1OfMesure_0.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpeTools/TestTopOpeTools.cxx" )
  SOURCE_GROUP (TestTopOpeTools FILES "../../../src/TestTopOpeTools/TestTopOpeTools.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpeTools/TestTopOpeTools_Mesure.cxx" )
  SOURCE_GROUP (TestTopOpeTools FILES "../../../src/TestTopOpeTools/TestTopOpeTools_Mesure.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpeTools/TestTopOpeTools_OtherCommands.cxx" )
  SOURCE_GROUP (TestTopOpeTools FILES "../../../src/TestTopOpeTools/TestTopOpeTools_OtherCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpeTools/TestTopOpeTools_Trace.cxx" )
  SOURCE_GROUP (TestTopOpeTools FILES "../../../src/TestTopOpeTools/TestTopOpeTools_Trace.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpeTools/TestTopOpeTools_TraceCommands.cxx" )
  SOURCE_GROUP (TestTopOpeTools FILES "../../../src/TestTopOpeTools/TestTopOpeTools_TraceCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpe/TestTopOpe.cxx" )
  SOURCE_GROUP (TestTopOpe FILES "../../../src/TestTopOpe/TestTopOpe.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpe/TestTopOpe_BOOP.cxx" )
  SOURCE_GROUP (TestTopOpe FILES "../../../src/TestTopOpe/TestTopOpe_BOOP.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpe/TestTopOpe_BOOPCommands.cxx" )
  SOURCE_GROUP (TestTopOpe FILES "../../../src/TestTopOpe/TestTopOpe_BOOPCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpe/TestTopOpe_CORCommands.cxx" )
  SOURCE_GROUP (TestTopOpe FILES "../../../src/TestTopOpe/TestTopOpe_CORCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpe/TestTopOpe_DSACommands.cxx" )
  SOURCE_GROUP (TestTopOpe FILES "../../../src/TestTopOpe/TestTopOpe_DSACommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpe/TestTopOpe_DSF.cxx" )
  SOURCE_GROUP (TestTopOpe FILES "../../../src/TestTopOpe/TestTopOpe_DSF.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpe/TestTopOpe_EditBOOP.cxx" )
  SOURCE_GROUP (TestTopOpe FILES "../../../src/TestTopOpe/TestTopOpe_EditBOOP.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpe/TestTopOpe_HDSCommands.cxx" )
  SOURCE_GROUP (TestTopOpe FILES "../../../src/TestTopOpe/TestTopOpe_HDSCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpe/TestTopOpe_HDSDisplayer.cxx" )
  SOURCE_GROUP (TestTopOpe FILES "../../../src/TestTopOpe/TestTopOpe_HDSDisplayer.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpe/TestTopOpe_KroBOOP.cxx" )
  SOURCE_GROUP (TestTopOpe FILES "../../../src/TestTopOpe/TestTopOpe_KroBOOP.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpe/TestTopOpe_MesureCommands.cxx" )
  SOURCE_GROUP (TestTopOpe FILES "../../../src/TestTopOpe/TestTopOpe_MesureCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpe/TestTopOpe_MiscBOOP.cxx" )
  SOURCE_GROUP (TestTopOpe FILES "../../../src/TestTopOpe/TestTopOpe_MiscBOOP.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpe/TestTopOpe_OtherCommands.cxx" )
  SOURCE_GROUP (TestTopOpe FILES "../../../src/TestTopOpe/TestTopOpe_OtherCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/TestTopOpe/TestTopOpe_VarsTopo.cxx" )
  SOURCE_GROUP (TestTopOpe FILES "../../../src/TestTopOpe/TestTopOpe_VarsTopo.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest_BasicCommands.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest_BasicCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest_ChamferCommands.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest_ChamferCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest_CheckCommands.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest_CheckCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest_CurveCommands.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest_CurveCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest_DraftAngleCommands.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest_DraftAngleCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest_ExtremaCommands.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest_ExtremaCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest_FeatureCommands.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest_FeatureCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest_Fillet2DCommands.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest_Fillet2DCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest_FilletCommands.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest_FilletCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest_FillingCommands.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest_FillingCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest_GPropCommands.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest_GPropCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest_MatCommands.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest_MatCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest_OtherCommands.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest_OtherCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest_PrimitiveCommands.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest_PrimitiveCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest_ProjectionCommands.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest_ProjectionCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest_SurfaceCommands.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest_SurfaceCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest_SweepCommands.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest_SweepCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BRepTest/BRepTest_TopologyCommands.cxx" )
  SOURCE_GROUP (BRepTest FILES "../../../src/BRepTest/BRepTest_TopologyCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/GeometryTest/GeometryTest.cxx" )
  SOURCE_GROUP (GeometryTest FILES "../../../src/GeometryTest/GeometryTest.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/GeometryTest/GeometryTest_API2dCommands.cxx" )
  SOURCE_GROUP (GeometryTest FILES "../../../src/GeometryTest/GeometryTest_API2dCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/GeometryTest/GeometryTest_APICommands.cxx" )
  SOURCE_GROUP (GeometryTest FILES "../../../src/GeometryTest/GeometryTest_APICommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/GeometryTest/GeometryTest_ConstraintCommands.cxx" )
  SOURCE_GROUP (GeometryTest FILES "../../../src/GeometryTest/GeometryTest_ConstraintCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/GeometryTest/GeometryTest_ContinuityCommands.cxx" )
  SOURCE_GROUP (GeometryTest FILES "../../../src/GeometryTest/GeometryTest_ContinuityCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/GeometryTest/GeometryTest_CurveCommands.cxx" )
  SOURCE_GROUP (GeometryTest FILES "../../../src/GeometryTest/GeometryTest_CurveCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/GeometryTest/GeometryTest_FairCurveCommands.cxx" )
  SOURCE_GROUP (GeometryTest FILES "../../../src/GeometryTest/GeometryTest_FairCurveCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/GeometryTest/GeometryTest_PolyCommands.cxx" )
  SOURCE_GROUP (GeometryTest FILES "../../../src/GeometryTest/GeometryTest_PolyCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/GeometryTest/GeometryTest_SurfaceCommands.cxx" )
  SOURCE_GROUP (GeometryTest FILES "../../../src/GeometryTest/GeometryTest_SurfaceCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/GeometryTest/GeometryTest_TestProjCommands.cxx" )
  SOURCE_GROUP (GeometryTest FILES "../../../src/GeometryTest/GeometryTest_TestProjCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/HLRTest/HLRTest.cxx" )
  SOURCE_GROUP (HLRTest FILES "../../../src/HLRTest/HLRTest.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/HLRTest/HLRTest_DrawableEdgeTool.cxx" )
  SOURCE_GROUP (HLRTest FILES "../../../src/HLRTest/HLRTest_DrawableEdgeTool.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/HLRTest/HLRTest_DrawablePolyEdgeTool.cxx" )
  SOURCE_GROUP (HLRTest FILES "../../../src/HLRTest/HLRTest_DrawablePolyEdgeTool.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/HLRTest/HLRTest_OutLiner.cxx" )
  SOURCE_GROUP (HLRTest FILES "../../../src/HLRTest/HLRTest_OutLiner.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/HLRTest/HLRTest_Projector.cxx" )
  SOURCE_GROUP (HLRTest FILES "../../../src/HLRTest/HLRTest_Projector.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/HLRTest/HLRTest_ShapeData.cxx" )
  SOURCE_GROUP (HLRTest FILES "../../../src/HLRTest/HLRTest_ShapeData.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/MeshTest/MeshTest.cxx" )
  SOURCE_GROUP (MeshTest FILES "../../../src/MeshTest/MeshTest.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/MeshTest/MeshTest_CheckTopology.cxx" )
  SOURCE_GROUP (MeshTest FILES "../../../src/MeshTest/MeshTest_CheckTopology.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/MeshTest/MeshTest_DrawableMesh.cxx" )
  SOURCE_GROUP (MeshTest FILES "../../../src/MeshTest/MeshTest_DrawableMesh.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/MeshTest/MeshTest_PluginCommands.cxx" )
  SOURCE_GROUP (MeshTest FILES "../../../src/MeshTest/MeshTest_PluginCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/GeomliteTest/GeomliteTest.cxx" )
  SOURCE_GROUP (GeomliteTest FILES "../../../src/GeomliteTest/GeomliteTest.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/GeomliteTest/GeomliteTest_API2dCommands.cxx" )
  SOURCE_GROUP (GeomliteTest FILES "../../../src/GeomliteTest/GeomliteTest_API2dCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/GeomliteTest/GeomliteTest_ApproxCommands.cxx" )
  SOURCE_GROUP (GeomliteTest FILES "../../../src/GeomliteTest/GeomliteTest_ApproxCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/GeomliteTest/GeomliteTest_CurveCommands.cxx" )
  SOURCE_GROUP (GeomliteTest FILES "../../../src/GeomliteTest/GeomliteTest_CurveCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/GeomliteTest/GeomliteTest_ModificationCommands.cxx" )
  SOURCE_GROUP (GeomliteTest FILES "../../../src/GeomliteTest/GeomliteTest_ModificationCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/GeomliteTest/GeomliteTest_SurfaceCommands.cxx" )
  SOURCE_GROUP (GeomliteTest FILES "../../../src/GeomliteTest/GeomliteTest_SurfaceCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/DrawFairCurve/DrawFairCurve_Batten.cxx" )
  SOURCE_GROUP (DrawFairCurve FILES "../../../src/DrawFairCurve/DrawFairCurve_Batten.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/DrawFairCurve/DrawFairCurve_MinimalVariation.cxx" )
  SOURCE_GROUP (DrawFairCurve FILES "../../../src/DrawFairCurve/DrawFairCurve_MinimalVariation.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BOPTest/BOPTest.cxx" )
  SOURCE_GROUP (BOPTest FILES "../../../src/BOPTest/BOPTest.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BOPTest/BOPTest_BOPCommands.cxx" )
  SOURCE_GROUP (BOPTest FILES "../../../src/BOPTest/BOPTest_BOPCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BOPTest/BOPTest_CheckCommands.cxx" )
  SOURCE_GROUP (BOPTest FILES "../../../src/BOPTest/BOPTest_CheckCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BOPTest/BOPTest_DrawableShape.cxx" )
  SOURCE_GROUP (BOPTest FILES "../../../src/BOPTest/BOPTest_DrawableShape.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BOPTest/BOPTest_LowCommands.cxx" )
  SOURCE_GROUP (BOPTest FILES "../../../src/BOPTest/BOPTest_LowCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BOPTest/BOPTest_ObjCommands.cxx" )
  SOURCE_GROUP (BOPTest FILES "../../../src/BOPTest/BOPTest_ObjCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BOPTest/BOPTest_Objects.cxx" )
  SOURCE_GROUP (BOPTest FILES "../../../src/BOPTest/BOPTest_Objects.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BOPTest/BOPTest_PartitionCommands.cxx" )
  SOURCE_GROUP (BOPTest FILES "../../../src/BOPTest/BOPTest_PartitionCommands.cxx")

  list( APPEND TKTopTest_USED_SRCFILES "../../../src/BOPTest/BOPTest_TolerCommands.cxx" )
  SOURCE_GROUP (BOPTest FILES "../../../src/BOPTest/BOPTest_TolerCommands.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKTopTest)
 add_library( TKTopTest SHARED ${TKTopTest_USED_SRCFILES} )

 set_property(TARGET TKTopTest PROPERTY FOLDER Draw)

 install( TARGETS TKTopTest
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKTopTest.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKTopTest PROPERTIES COMPILE_FLAGS "${TKTopTest_PRECOMPILED_DEFS}" )
 include_directories( ${TKTopTest_COMPILER_DIRECTORIES} )
 target_link_libraries( TKTopTest ${TKTopTest_USED_LIBS} )
endif()
