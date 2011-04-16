# Makefile.am for Open Cascade toolkit TKDraw
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/Draw : @top_srcdir@/src/Draw: \
@top_srcdir@/drv/DBRep : @top_srcdir@/src/DBRep: \
@top_srcdir@/drv/DrawTrSurf : @top_srcdir@/src/DrawTrSurf


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES) $(CSF_TclLibs_INCLUDES) $(CSF_TclTkLibs_INCLUDES) $(CSF_gdi32_INCLUDES) $(CSF_advapi32_INCLUDES) $(CSF_user32_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/Draw -I@top_srcdir@/src/Draw \
-I@top_srcdir@/drv/DBRep -I@top_srcdir@/src/DBRep \
-I@top_srcdir@/drv/DrawTrSurf -I@top_srcdir@/src/DrawTrSurf


lib_LTLIBRARIES=libTKDraw.la

libTKDraw_la_LIBADD = \
../TKernel/libTKernel.la \
../TKG3d/libTKG3d.la \
../TKMath/libTKMath.la \
../TKBRep/libTKBRep.la \
../TKMesh/libTKMesh.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKG2d/libTKG2d.la \
../TKHLR/libTKHLR.la \
../TKGeomBase/libTKGeomBase.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKService/libTKService.la \
$(STLPort_LIB) $(CSF_TclLibs_LIB) $(CSF_TclTkLibs_LIB) $(CSF_gdi32_LIB) $(CSF_advapi32_LIB) $(CSF_user32_LIB) 

libTKDraw_la_SOURCES = \
@top_srcdir@/drv/DBRep/DBRep_ListIteratorOfListOfEdge_0.cxx \
@top_srcdir@/drv/DBRep/DBRep_ListIteratorOfListOfFace_0.cxx \
@top_srcdir@/drv/DBRep/DBRep_ListIteratorOfListOfHideData_0.cxx \
@top_srcdir@/drv/DBRep/DBRep_ListNodeOfListOfEdge_0.cxx \
@top_srcdir@/drv/DBRep/DBRep_ListNodeOfListOfFace_0.cxx \
@top_srcdir@/drv/DBRep/DBRep_ListNodeOfListOfHideData_0.cxx \
@top_srcdir@/drv/DBRep/DBRep_ListOfEdge_0.cxx \
@top_srcdir@/drv/DBRep/DBRep_ListOfFace_0.cxx \
@top_srcdir@/drv/DBRep/DBRep_ListOfHideData_0.cxx \
@top_srcdir@/drv/Draw/Draw_DataMapIteratorOfMapOfFunctions_0.cxx \
@top_srcdir@/drv/Draw/Draw_DataMapIteratorOfVMap_0.cxx \
@top_srcdir@/drv/Draw/Draw_DataMapNodeOfMapOfFunctions_0.cxx \
@top_srcdir@/drv/Draw/Draw_DataMapNodeOfVMap_0.cxx \
@top_srcdir@/drv/Draw/Draw_Failure_0.cxx \
@top_srcdir@/drv/Draw/Draw_IndexedMapNodeOfMapOfAsciiString_0.cxx \
@top_srcdir@/drv/Draw/Draw_MapOfAsciiString_0.cxx \
@top_srcdir@/drv/Draw/Draw_MapOfFunctions_0.cxx \
@top_srcdir@/drv/Draw/Draw_SequenceNodeOfSequenceOfDrawable3D_0.cxx \
@top_srcdir@/drv/Draw/Draw_SequenceOfDrawable3D_0.cxx \
@top_srcdir@/drv/Draw/Draw_VMap_0.cxx \
@top_srcdir@/src/DBRep/DBRep.cxx \
@top_srcdir@/src/DBRep/DBRep_Debug.cxx \
@top_srcdir@/src/DBRep/DBRep_DrawableShape.cxx \
@top_srcdir@/src/DBRep/DBRep_Edge.cxx \
@top_srcdir@/src/DBRep/DBRep_Face.cxx \
@top_srcdir@/src/DBRep/DBRep_HideData.cxx \
@top_srcdir@/src/DBRep/DBRep_IsoBuilder.cxx \
@top_srcdir@/src/Draw/CommandWindow.cxx \
@top_srcdir@/src/Draw/Draw.cxx \
@top_srcdir@/src/Draw/Draw_Axis2D.cxx \
@top_srcdir@/src/Draw/Draw_Axis3D.cxx \
@top_srcdir@/src/Draw/Draw_BasicCommands.cxx \
@top_srcdir@/src/Draw/Draw_Box.cxx \
@top_srcdir@/src/Draw/Draw_Chronometer.cxx \
@top_srcdir@/src/Draw/Draw_Circle2D.cxx \
@top_srcdir@/src/Draw/Draw_Circle3D.cxx \
@top_srcdir@/src/Draw/Draw_Color.cxx \
@top_srcdir@/src/Draw/Draw_Commands.cxx \
@top_srcdir@/src/Draw/Draw_Display.cxx \
@top_srcdir@/src/Draw/Draw_Drawable2D.cxx \
@top_srcdir@/src/Draw/Draw_Drawable3D.cxx \
@top_srcdir@/src/Draw/Draw_GraphicCommands.cxx \
@top_srcdir@/src/Draw/Draw_Grid.cxx \
@top_srcdir@/src/Draw/Draw_Interpretor.cxx \
@top_srcdir@/src/Draw/Draw_Main.cxx \
@top_srcdir@/src/Draw/Draw_Marker2D.cxx \
@top_srcdir@/src/Draw/Draw_Marker3D.cxx \
@top_srcdir@/src/Draw/Draw_Number.cxx \
@top_srcdir@/src/Draw/Draw_PloadCommands.cxx \
@top_srcdir@/src/Draw/Draw_Printer.cxx \
@top_srcdir@/src/Draw/Draw_ProgressIndicator.cxx \
@top_srcdir@/src/Draw/Draw_Segment2D.cxx \
@top_srcdir@/src/Draw/Draw_Segment3D.cxx \
@top_srcdir@/src/Draw/Draw_Text2D.cxx \
@top_srcdir@/src/Draw/Draw_Text3D.cxx \
@top_srcdir@/src/Draw/Draw_UnitCommands.cxx \
@top_srcdir@/src/Draw/Draw_VariableCommands.cxx \
@top_srcdir@/src/Draw/Draw_Viewer.cxx \
@top_srcdir@/src/Draw/Draw_Window.cxx \
@top_srcdir@/src/Draw/MainWindow.cxx \
@top_srcdir@/src/Draw/init.cxx \
@top_srcdir@/src/DrawTrSurf/DrawTrSurf.cxx \
@top_srcdir@/src/DrawTrSurf/DrawTrSurf_BSplineCurve.cxx \
@top_srcdir@/src/DrawTrSurf/DrawTrSurf_BSplineCurve2d.cxx \
@top_srcdir@/src/DrawTrSurf/DrawTrSurf_BSplineSurface.cxx \
@top_srcdir@/src/DrawTrSurf/DrawTrSurf_BezierCurve.cxx \
@top_srcdir@/src/DrawTrSurf/DrawTrSurf_BezierCurve2d.cxx \
@top_srcdir@/src/DrawTrSurf/DrawTrSurf_BezierSurface.cxx \
@top_srcdir@/src/DrawTrSurf/DrawTrSurf_Curve.cxx \
@top_srcdir@/src/DrawTrSurf/DrawTrSurf_Curve2d.cxx \
@top_srcdir@/src/DrawTrSurf/DrawTrSurf_Debug.cxx \
@top_srcdir@/src/DrawTrSurf/DrawTrSurf_Drawable.cxx \
@top_srcdir@/src/DrawTrSurf/DrawTrSurf_Point.cxx \
@top_srcdir@/src/DrawTrSurf/DrawTrSurf_Polygon2D.cxx \
@top_srcdir@/src/DrawTrSurf/DrawTrSurf_Polygon3D.cxx \
@top_srcdir@/src/DrawTrSurf/DrawTrSurf_Surface.cxx \
@top_srcdir@/src/DrawTrSurf/DrawTrSurf_Triangulation.cxx \
@top_srcdir@/src/DrawTrSurf/DrawTrSurf_Triangulation2D.cxx

libTKDraw_laLDFLAGS = -version-info @oce_version_info@

