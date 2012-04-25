# Makefile.am for Open Cascade toolkit TKV2d
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/V2d : @top_srcdir@/src/V2d: \
@top_srcdir@/drv/Graphic2d : @top_srcdir@/src/Graphic2d: \
@top_srcdir@/drv/Select2D : @top_srcdir@/src/Select2D: \
@top_srcdir@/drv/Prs2d : @top_srcdir@/src/Prs2d: \
@top_srcdir@/drv/AIS2D : @top_srcdir@/src/AIS2D: \
@top_srcdir@/drv/GGraphic2d : @top_srcdir@/src/GGraphic2d


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/V2d -I@top_srcdir@/src/V2d \
-I@top_srcdir@/drv/Graphic2d -I@top_srcdir@/src/Graphic2d \
-I@top_srcdir@/drv/Select2D -I@top_srcdir@/src/Select2D \
-I@top_srcdir@/drv/Prs2d -I@top_srcdir@/src/Prs2d \
-I@top_srcdir@/drv/AIS2D -I@top_srcdir@/src/AIS2D \
-I@top_srcdir@/drv/GGraphic2d -I@top_srcdir@/src/GGraphic2d


lib_LTLIBRARIES=libTKV2d.la

libTKV2d_la_LIBADD = $(CSF_OPT_LIBS) \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
../TKGeomBase/libTKGeomBase.la \
../TKG2d/libTKG2d.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKBRep/libTKBRep.la \
../TKHLR/libTKHLR.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKG3d/libTKG3d.la \
../TKService/libTKService.la


libTKV2d_la_SOURCES = \
@top_srcdir@/drv/AIS2D/AIS2D_DataMapIteratorOfDataMapOfIOStatus_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_DataMapIteratorOfDataMapOfLC_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_DataMapIteratorOfDataMapOfLocStat_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_DataMapIteratorOfDataMapOfPrimAspects_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_DataMapNodeOfDataMapOfIOStatus_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_DataMapNodeOfDataMapOfLC_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_DataMapNodeOfDataMapOfLocStat_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_DataMapNodeOfDataMapOfPrimAspects_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_DataMapOfIOStatus_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_DataMapOfLC_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_DataMapOfLocStat_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_DataMapOfPrimAspects_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_HSequenceOfIO_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_HSequenceOfPrimArchit_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_ListIteratorOfListOfIO_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_ListNodeOfListOfIO_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_ListOfIO_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_SequenceNodeOfSequenceOfIO_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_SequenceNodeOfSequenceOfPrimArchit_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_SequenceOfIO_0.cxx \
@top_srcdir@/drv/AIS2D/AIS2D_SequenceOfPrimArchit_0.cxx \
@top_srcdir@/drv/GGraphic2d/GGraphic2d_CurveDefinitionError_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_Array1OfVertex_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_BufferList_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_CircleDefinitionError_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_DetectionColorError_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_DisplayList_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_DrawerDefinitionError_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_EllipsDefinitionError_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_HArray1OfVertex_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_HSequenceOfPrimitives_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_HSequenceOfVertex_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_ImageDefinitionError_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_InfiniteLineDefinitionError_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_MarkerDefinitionError_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_OverrideColorError_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_PolylineDefinitionError_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_SegmentDefinitionError_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_SequenceNodeOfSequenceOfBuffer_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_SequenceNodeOfSequenceOfGraphicObject_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_SequenceNodeOfSequenceOfPolyline_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_SequenceNodeOfSequenceOfPrimitives_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_SequenceNodeOfSequenceOfVertex_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_SequenceOfBuffer_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_SequenceOfGraphicObject_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_SequenceOfPolyline_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_SequenceOfPrimitives_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_SequenceOfVertex_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_TextDefinitionError_0.cxx \
@top_srcdir@/drv/Graphic2d/Graphic2d_TransientDefinitionError_0.cxx \
@top_srcdir@/drv/Prs2d/Prs2d_DataMapIteratorOfDataMapOfAspectRoot_0.cxx \
@top_srcdir@/drv/Prs2d/Prs2d_DataMapNodeOfDataMapOfAspectRoot_0.cxx \
@top_srcdir@/drv/Prs2d/Prs2d_DataMapOfAspectRoot_0.cxx \
@top_srcdir@/drv/Prs2d/Prs2d_SymbolDefinitionError_0.cxx \
@top_srcdir@/src/AIS2D/AIS2D.cxx \
@top_srcdir@/src/AIS2D/AIS2D_GlobalStatus.cxx \
@top_srcdir@/src/AIS2D/AIS2D_InteractiveContext.cxx \
@top_srcdir@/src/AIS2D/AIS2D_InteractiveObject.cxx \
@top_srcdir@/src/AIS2D/AIS2D_LocalContext.cxx \
@top_srcdir@/src/AIS2D/AIS2D_LocalStatus.cxx \
@top_srcdir@/src/AIS2D/AIS2D_PrimitiveArchit.cxx \
@top_srcdir@/src/AIS2D/AIS2D_ProjShape.cxx \
@top_srcdir@/src/GGraphic2d/GGraphic2d_Curve.cxx \
@top_srcdir@/src/GGraphic2d/GGraphic2d_SetOfCurves.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_Buffer.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_CBitFields8.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_Circle.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_CircleMarker.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_Drawer.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_Ellips.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_EllipsMarker.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_FramedText.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_GraphicObject.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_HidingGraphicObject.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_HidingText.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_Image.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_ImageFile.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_InfiniteLine.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_Line.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_Marker.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_Paragraph.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_Polyline.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_PolylineMarker.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_Primitive.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_Segment.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_SetOfMarkers.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_SetOfPolylines.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_SetOfSegments.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_Text.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_TransientManager.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_VectorialMarker.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_Vertex.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_View.cxx \
@top_srcdir@/src/Graphic2d/Graphic2d_ViewMapping.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Angle.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Angularity.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Arrow.cxx \
@top_srcdir@/src/Prs2d/Prs2d_AspectFramedText.cxx \
@top_srcdir@/src/Prs2d/Prs2d_AspectHidingPoly.cxx \
@top_srcdir@/src/Prs2d/Prs2d_AspectHidingText.cxx \
@top_srcdir@/src/Prs2d/Prs2d_AspectLine.cxx \
@top_srcdir@/src/Prs2d/Prs2d_AspectRoot.cxx \
@top_srcdir@/src/Prs2d/Prs2d_AspectText.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Axis.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Circularity.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Concentric.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Cylindric.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Diameter.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Dimension.cxx \
@top_srcdir@/src/Prs2d/Prs2d_DrawSymbol.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Drawer.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Flatness.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Length.cxx \
@top_srcdir@/src/Prs2d/Prs2d_LineProfile.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Parallelism.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Perpendicular.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Point.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Position.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Radius.cxx \
@top_srcdir@/src/Prs2d/Prs2d_RadiusIndep.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Repere.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Straightness.cxx \
@top_srcdir@/src/Prs2d/Prs2d_SurfProfile.cxx \
@top_srcdir@/src/Prs2d/Prs2d_SymCircular.cxx \
@top_srcdir@/src/Prs2d/Prs2d_SymTotal.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Symmetry.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Taper.cxx \
@top_srcdir@/src/Prs2d/Prs2d_Tolerance.cxx \
@top_srcdir@/src/Prs2d/Prs2d_ToleranceFrame.cxx \
@top_srcdir@/src/Select2D/Select2D_Projector.cxx \
@top_srcdir@/src/Select2D/Select2D_SensitiveArc.cxx \
@top_srcdir@/src/Select2D/Select2D_SensitiveBox.cxx \
@top_srcdir@/src/Select2D/Select2D_SensitiveCircle.cxx \
@top_srcdir@/src/Select2D/Select2D_SensitiveEntity.cxx \
@top_srcdir@/src/Select2D/Select2D_SensitivePoint.cxx \
@top_srcdir@/src/Select2D/Select2D_SensitiveSegment.cxx \
@top_srcdir@/src/V2d/V2d.cxx \
@top_srcdir@/src/V2d/V2d_BackgroundGraphicObject.cxx \
@top_srcdir@/src/V2d/V2d_CircularGraphicGrid.cxx \
@top_srcdir@/src/V2d/V2d_CircularGrid.cxx \
@top_srcdir@/src/V2d/V2d_DefaultMap.cxx \
@top_srcdir@/src/V2d/V2d_RectangularGraphicGrid.cxx \
@top_srcdir@/src/V2d/V2d_RectangularGrid.cxx \
@top_srcdir@/src/V2d/V2d_View.cxx \
@top_srcdir@/src/V2d/V2d_Viewer.cxx

