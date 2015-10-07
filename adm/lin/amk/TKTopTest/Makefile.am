# Makefile.am for Open Cascade toolkit TKTopTest
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/TestTopOpeDraw : @top_srcdir@/src/TestTopOpeDraw: \
@top_srcdir@/drv/TestTopOpeTools : @top_srcdir@/src/TestTopOpeTools: \
@top_srcdir@/drv/TestTopOpe : @top_srcdir@/src/TestTopOpe: \
@top_srcdir@/drv/BRepTest : @top_srcdir@/src/BRepTest: \
@top_srcdir@/drv/GeometryTest : @top_srcdir@/src/GeometryTest: \
@top_srcdir@/drv/HLRTest : @top_srcdir@/src/HLRTest: \
@top_srcdir@/drv/MeshTest : @top_srcdir@/src/MeshTest: \
@top_srcdir@/drv/GeomliteTest : @top_srcdir@/src/GeomliteTest: \
@top_srcdir@/drv/DrawFairCurve : @top_srcdir@/src/DrawFairCurve: \
@top_srcdir@/drv/BOPTest : @top_srcdir@/src/BOPTest: \
@top_srcdir@/drv/SWDRAW : @top_srcdir@/src/SWDRAW


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/TestTopOpeDraw -I@top_srcdir@/src/TestTopOpeDraw \
-I@top_srcdir@/drv/TestTopOpeTools -I@top_srcdir@/src/TestTopOpeTools \
-I@top_srcdir@/drv/TestTopOpe -I@top_srcdir@/src/TestTopOpe \
-I@top_srcdir@/drv/BRepTest -I@top_srcdir@/src/BRepTest \
-I@top_srcdir@/drv/GeometryTest -I@top_srcdir@/src/GeometryTest \
-I@top_srcdir@/drv/HLRTest -I@top_srcdir@/src/HLRTest \
-I@top_srcdir@/drv/MeshTest -I@top_srcdir@/src/MeshTest \
-I@top_srcdir@/drv/GeomliteTest -I@top_srcdir@/src/GeomliteTest \
-I@top_srcdir@/drv/DrawFairCurve -I@top_srcdir@/src/DrawFairCurve \
-I@top_srcdir@/drv/BOPTest -I@top_srcdir@/src/BOPTest \
-I@top_srcdir@/drv/SWDRAW -I@top_srcdir@/src/SWDRAW


lib_LTLIBRARIES=libTKTopTest.la

libTKTopTest_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKBRep/libTKBRep.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
../TKBO/libTKBO.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../TKDraw/libTKDraw.la \
../TKHLR/libTKHLR.la \
../TKGeomBase/libTKGeomBase.la \
../TKMesh/libTKMesh.la \
../TKService/libTKService.la \
../TKV3d/libTKV3d.la \
../TKFillet/libTKFillet.la \
../TKPrim/libTKPrim.la \
../TKBool/libTKBool.la \
../TKOffset/libTKOffset.la \
../TKFeat/libTKFeat.la \
../TKShHealing/libTKShHealing.la \
$(STLPort_LIB) 

libTKTopTest_la_SOURCES = \
@top_srcdir@/drv/TestTopOpeDraw/TestTopOpeDraw_Array1OfDrawableMesure_0.cxx \
@top_srcdir@/drv/TestTopOpeDraw/TestTopOpeDraw_Array1OfDrawableP3D_0.cxx \
@top_srcdir@/drv/TestTopOpeDraw/TestTopOpeDraw_HArray1OfDrawableMesure_0.cxx \
@top_srcdir@/drv/TestTopOpeDraw/TestTopOpeDraw_HArray1OfDrawableP3D_0.cxx \
@top_srcdir@/drv/TestTopOpeDraw/TestTopOpeDraw_ListIteratorOfListOfPnt2d_0.cxx \
@top_srcdir@/drv/TestTopOpeDraw/TestTopOpeDraw_ListNodeOfListOfPnt2d_0.cxx \
@top_srcdir@/drv/TestTopOpeDraw/TestTopOpeDraw_ListOfPnt2d_0.cxx \
@top_srcdir@/drv/TestTopOpeTools/TestTopOpeTools_Array1OfMesure_0.cxx \
@top_srcdir@/drv/TestTopOpeTools/TestTopOpeTools_HArray1OfMesure_0.cxx \
@top_srcdir@/src/BOPTest/BOPTest.cxx \
@top_srcdir@/src/BOPTest/BOPTest_APICommands.cxx \
@top_srcdir@/src/BOPTest/BOPTest_BOPCommands.cxx \
@top_srcdir@/src/BOPTest/BOPTest_CheckCommands.cxx \
@top_srcdir@/src/BOPTest/BOPTest_DrawableShape.cxx \
@top_srcdir@/src/BOPTest/BOPTest_HistoryCommands.cxx \
@top_srcdir@/src/BOPTest/BOPTest_LowCommands.cxx \
@top_srcdir@/src/BOPTest/BOPTest_ObjCommands.cxx \
@top_srcdir@/src/BOPTest/BOPTest_Objects.cxx \
@top_srcdir@/src/BOPTest/BOPTest_OptionCommands.cxx \
@top_srcdir@/src/BOPTest/BOPTest_PartitionCommands.cxx \
@top_srcdir@/src/BOPTest/BOPTest_TolerCommands.cxx \
@top_srcdir@/src/BRepTest/BRepTest.cxx \
@top_srcdir@/src/BRepTest/BRepTest_BasicCommands.cxx \
@top_srcdir@/src/BRepTest/BRepTest_ChamferCommands.cxx \
@top_srcdir@/src/BRepTest/BRepTest_CheckCommands.cxx \
@top_srcdir@/src/BRepTest/BRepTest_CurveCommands.cxx \
@top_srcdir@/src/BRepTest/BRepTest_DraftAngleCommands.cxx \
@top_srcdir@/src/BRepTest/BRepTest_ExtremaCommands.cxx \
@top_srcdir@/src/BRepTest/BRepTest_FeatureCommands.cxx \
@top_srcdir@/src/BRepTest/BRepTest_Fillet2DCommands.cxx \
@top_srcdir@/src/BRepTest/BRepTest_FilletCommands.cxx \
@top_srcdir@/src/BRepTest/BRepTest_FillingCommands.cxx \
@top_srcdir@/src/BRepTest/BRepTest_GPropCommands.cxx \
@top_srcdir@/src/BRepTest/BRepTest_MatCommands.cxx \
@top_srcdir@/src/BRepTest/BRepTest_OtherCommands.cxx \
@top_srcdir@/src/BRepTest/BRepTest_PrimitiveCommands.cxx \
@top_srcdir@/src/BRepTest/BRepTest_ProjectionCommands.cxx \
@top_srcdir@/src/BRepTest/BRepTest_SurfaceCommands.cxx \
@top_srcdir@/src/BRepTest/BRepTest_SweepCommands.cxx \
@top_srcdir@/src/BRepTest/BRepTest_TopologyCommands.cxx \
@top_srcdir@/src/DrawFairCurve/DrawFairCurve_Batten.cxx \
@top_srcdir@/src/DrawFairCurve/DrawFairCurve_MinimalVariation.cxx \
@top_srcdir@/src/GeometryTest/GeometryTest.cxx \
@top_srcdir@/src/GeometryTest/GeometryTest_API2dCommands.cxx \
@top_srcdir@/src/GeometryTest/GeometryTest_APICommands.cxx \
@top_srcdir@/src/GeometryTest/GeometryTest_ConstraintCommands.cxx \
@top_srcdir@/src/GeometryTest/GeometryTest_ContinuityCommands.cxx \
@top_srcdir@/src/GeometryTest/GeometryTest_CurveCommands.cxx \
@top_srcdir@/src/GeometryTest/GeometryTest_FairCurveCommands.cxx \
@top_srcdir@/src/GeometryTest/GeometryTest_PolyCommands.cxx \
@top_srcdir@/src/GeometryTest/GeometryTest_SurfaceCommands.cxx \
@top_srcdir@/src/GeometryTest/GeometryTest_TestProjCommands.cxx \
@top_srcdir@/src/GeomliteTest/GeomliteTest.cxx \
@top_srcdir@/src/GeomliteTest/GeomliteTest_API2dCommands.cxx \
@top_srcdir@/src/GeomliteTest/GeomliteTest_ApproxCommands.cxx \
@top_srcdir@/src/GeomliteTest/GeomliteTest_CurveCommands.cxx \
@top_srcdir@/src/GeomliteTest/GeomliteTest_ModificationCommands.cxx \
@top_srcdir@/src/GeomliteTest/GeomliteTest_SurfaceCommands.cxx \
@top_srcdir@/src/HLRTest/HLRTest.cxx \
@top_srcdir@/src/HLRTest/HLRTest_DrawableEdgeTool.cxx \
@top_srcdir@/src/HLRTest/HLRTest_DrawablePolyEdgeTool.cxx \
@top_srcdir@/src/HLRTest/HLRTest_OutLiner.cxx \
@top_srcdir@/src/HLRTest/HLRTest_Projector.cxx \
@top_srcdir@/src/HLRTest/HLRTest_ShapeData.cxx \
@top_srcdir@/src/MeshTest/MeshTest.cxx \
@top_srcdir@/src/MeshTest/MeshTest_CheckTopology.cxx \
@top_srcdir@/src/MeshTest/MeshTest_DrawableMesh.cxx \
@top_srcdir@/src/MeshTest/MeshTest_PluginCommands.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ShapeAnalysis.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ShapeCustom.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ShapeExtend.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ShapeFix.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ShapeProcess.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ShapeProcessAPI.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ShapeTool.cxx \
@top_srcdir@/src/SWDRAW/SWDRAW_ShapeUpgrade.cxx \
@top_srcdir@/src/TestTopOpe/TestTopOpe.cxx \
@top_srcdir@/src/TestTopOpe/TestTopOpe_BOOP.cxx \
@top_srcdir@/src/TestTopOpe/TestTopOpe_BOOPCommands.cxx \
@top_srcdir@/src/TestTopOpe/TestTopOpe_CORCommands.cxx \
@top_srcdir@/src/TestTopOpe/TestTopOpe_DSF.cxx \
@top_srcdir@/src/TestTopOpe/TestTopOpe_EditBOOP.cxx \
@top_srcdir@/src/TestTopOpe/TestTopOpe_HDSCommands.cxx \
@top_srcdir@/src/TestTopOpe/TestTopOpe_HDSDisplayer.cxx \
@top_srcdir@/src/TestTopOpe/TestTopOpe_KroBOOP.cxx \
@top_srcdir@/src/TestTopOpe/TestTopOpe_MesureCommands.cxx \
@top_srcdir@/src/TestTopOpe/TestTopOpe_MiscBOOP.cxx \
@top_srcdir@/src/TestTopOpe/TestTopOpe_OtherCommands.cxx \
@top_srcdir@/src/TestTopOpe/TestTopOpe_VarsTopo.cxx \
@top_srcdir@/src/TestTopOpeDraw/TestTopOpeDraw.cxx \
@top_srcdir@/src/TestTopOpeDraw/TestTopOpeDraw_Displayer.cxx \
@top_srcdir@/src/TestTopOpeDraw/TestTopOpeDraw_DrawableC2D.cxx \
@top_srcdir@/src/TestTopOpeDraw/TestTopOpeDraw_DrawableC3D.cxx \
@top_srcdir@/src/TestTopOpeDraw/TestTopOpeDraw_DrawableMesure.cxx \
@top_srcdir@/src/TestTopOpeDraw/TestTopOpeDraw_DrawableP2D.cxx \
@top_srcdir@/src/TestTopOpeDraw/TestTopOpeDraw_DrawableP3D.cxx \
@top_srcdir@/src/TestTopOpeDraw/TestTopOpeDraw_DrawableSHA.cxx \
@top_srcdir@/src/TestTopOpeDraw/TestTopOpeDraw_DrawableSUR.cxx \
@top_srcdir@/src/TestTopOpeDraw/TestTopOpeDraw_OtherCommands.cxx \
@top_srcdir@/src/TestTopOpeDraw/TestTopOpeDraw_SaveRestore.cxx \
@top_srcdir@/src/TestTopOpeDraw/TestTopOpeDraw_TTOT.cxx \
@top_srcdir@/src/TestTopOpeTools/TestTopOpeTools.cxx \
@top_srcdir@/src/TestTopOpeTools/TestTopOpeTools_Mesure.cxx \
@top_srcdir@/src/TestTopOpeTools/TestTopOpeTools_OtherCommands.cxx \
@top_srcdir@/src/TestTopOpeTools/TestTopOpeTools_Trace.cxx \
@top_srcdir@/src/TestTopOpeTools/TestTopOpeTools_TraceCommands.cxx

