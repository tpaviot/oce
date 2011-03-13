# Makefile.am for Open Cascade toolkit TKSTEPAttr
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/StepVisual : @top_srcdir@/src/StepVisual: \
@top_srcdir@/drv/RWStepVisual : @top_srcdir@/src/RWStepVisual: \
@top_srcdir@/drv/StepDimTol : @top_srcdir@/src/StepDimTol: \
@top_srcdir@/drv/RWStepDimTol : @top_srcdir@/src/RWStepDimTol


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/StepVisual -I@top_srcdir@/src/StepVisual \
-I@top_srcdir@/drv/RWStepVisual -I@top_srcdir@/src/RWStepVisual \
-I@top_srcdir@/drv/StepDimTol -I@top_srcdir@/src/StepDimTol \
-I@top_srcdir@/drv/RWStepDimTol -I@top_srcdir@/src/RWStepDimTol


lib_LTLIBRARIES=libTKSTEPAttr.la

libTKSTEPAttr_la_LIBADD = \
../TKSTEPBase/libTKSTEPBase.la \
../TKernel/libTKernel.la \
../TKXSBase/libTKXSBase.la \
$(STLPort_LIB) 

libTKSTEPAttr_la_SOURCES = \
@top_srcdir@/drv/StepDimTol/StepDimTol_Array1OfDatumReference_0.cxx \
@top_srcdir@/drv/StepDimTol/StepDimTol_HArray1OfDatumReference_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_Array1OfBoxCharacteristicSelect_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_Array1OfCurveStyleFontPattern_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_Array1OfDirectionCountSelect_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_Array1OfFillStyleSelect_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_Array1OfInvisibleItem_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_Array1OfLayeredItem_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_Array1OfPresentationStyleAssignment_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_Array1OfPresentationStyleSelect_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_Array1OfStyleContextSelect_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_Array1OfSurfaceStyleElementSelect_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_Array1OfTextOrCharacter_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_HArray1OfBoxCharacteristicSelect_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_HArray1OfCurveStyleFontPattern_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_HArray1OfDirectionCountSelect_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_HArray1OfFillStyleSelect_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_HArray1OfInvisibleItem_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_HArray1OfLayeredItem_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_HArray1OfPresentationStyleAssignment_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_HArray1OfPresentationStyleSelect_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_HArray1OfStyleContextSelect_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_HArray1OfSurfaceStyleElementSelect_0.cxx \
@top_srcdir@/drv/StepVisual/StepVisual_HArray1OfTextOrCharacter_0.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWAngularityTolerance.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWCircularRunoutTolerance.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWCoaxialityTolerance.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWCommonDatum.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWConcentricityTolerance.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWCylindricityTolerance.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWDatum.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWDatumFeature.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWDatumReference.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWDatumTarget.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWFlatnessTolerance.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWGeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWGeometricTolerance.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWGeometricToleranceRelationship.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWGeometricToleranceWithDatumReference.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWLineProfileTolerance.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWModifiedGeometricTolerance.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWParallelismTolerance.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWPerpendicularityTolerance.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWPlacedDatumTargetFeature.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWPositionTolerance.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWRoundnessTolerance.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWStraightnessTolerance.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWSurfaceProfileTolerance.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWSymmetryTolerance.cxx \
@top_srcdir@/src/RWStepDimTol/RWStepDimTol_RWTotalRunoutTolerance.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWAreaInSet.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWBackgroundColour.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWCameraImage.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWCameraModel.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWCameraModelD2.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWCameraModelD3.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWCameraUsage.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWColour.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWColourRgb.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWColourSpecification.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWCompositeText.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWCompositeTextWithExtent.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWContextDependentInvisibility.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWContextDependentOverRidingStyledItem.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWCurveStyle.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWCurveStyleFont.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWCurveStyleFontPattern.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWDraughtingModel.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWDraughtingPreDefinedColour.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWDraughtingPreDefinedCurveFont.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWExternallyDefinedCurveFont.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWFillAreaStyle.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWFillAreaStyleColour.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWInvisibility.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWMechanicalDesignGeometricPresentationArea.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWMechanicalDesignGeometricPresentationRepresentation.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWOverRidingStyledItem.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWPlanarBox.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWPlanarExtent.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWPointStyle.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWPreDefinedColour.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWPreDefinedCurveFont.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWPreDefinedItem.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWPresentationArea.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWPresentationLayerAssignment.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWPresentationLayerUsage.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWPresentationRepresentation.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWPresentationSet.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWPresentationSize.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWPresentationStyleAssignment.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWPresentationStyleByContext.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWPresentationView.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWPresentedItemRepresentation.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWStyledItem.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWSurfaceSideStyle.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWSurfaceStyleBoundary.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWSurfaceStyleControlGrid.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWSurfaceStyleFillArea.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWSurfaceStyleParameterLine.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWSurfaceStyleSegmentationCurve.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWSurfaceStyleSilhouette.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWSurfaceStyleUsage.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWTemplate.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWTemplateInstance.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWTextLiteral.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWTextStyle.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWTextStyleForDefinedFont.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWTextStyleWithBoxCharacteristics.cxx \
@top_srcdir@/src/RWStepVisual/RWStepVisual_RWViewVolume.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_AngularityTolerance.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_CircularRunoutTolerance.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_CoaxialityTolerance.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_CommonDatum.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_ConcentricityTolerance.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_CylindricityTolerance.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_Datum.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_DatumFeature.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_DatumReference.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_DatumTarget.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_FlatnessTolerance.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_GeometricTolerance.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_GeometricToleranceRelationship.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_GeometricToleranceWithDatumReference.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_LineProfileTolerance.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_ModifiedGeometricTolerance.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_ParallelismTolerance.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_PerpendicularityTolerance.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_PlacedDatumTargetFeature.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_PositionTolerance.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_RoundnessTolerance.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_ShapeToleranceSelect.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_StraightnessTolerance.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_SurfaceProfileTolerance.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_SymmetryTolerance.cxx \
@top_srcdir@/src/StepDimTol/StepDimTol_TotalRunoutTolerance.cxx \
@top_srcdir@/src/StepVisual/StepVisual_AnnotationOccurrence.cxx \
@top_srcdir@/src/StepVisual/StepVisual_AnnotationText.cxx \
@top_srcdir@/src/StepVisual/StepVisual_AnnotationTextOccurrence.cxx \
@top_srcdir@/src/StepVisual/StepVisual_AreaInSet.cxx \
@top_srcdir@/src/StepVisual/StepVisual_AreaOrView.cxx \
@top_srcdir@/src/StepVisual/StepVisual_BackgroundColour.cxx \
@top_srcdir@/src/StepVisual/StepVisual_BoxCharacteristicSelect.cxx \
@top_srcdir@/src/StepVisual/StepVisual_CameraImage.cxx \
@top_srcdir@/src/StepVisual/StepVisual_CameraImage2dWithScale.cxx \
@top_srcdir@/src/StepVisual/StepVisual_CameraImage3dWithScale.cxx \
@top_srcdir@/src/StepVisual/StepVisual_CameraModel.cxx \
@top_srcdir@/src/StepVisual/StepVisual_CameraModelD2.cxx \
@top_srcdir@/src/StepVisual/StepVisual_CameraModelD3.cxx \
@top_srcdir@/src/StepVisual/StepVisual_CameraUsage.cxx \
@top_srcdir@/src/StepVisual/StepVisual_Colour.cxx \
@top_srcdir@/src/StepVisual/StepVisual_ColourRgb.cxx \
@top_srcdir@/src/StepVisual/StepVisual_ColourSpecification.cxx \
@top_srcdir@/src/StepVisual/StepVisual_CompositeText.cxx \
@top_srcdir@/src/StepVisual/StepVisual_CompositeTextWithExtent.cxx \
@top_srcdir@/src/StepVisual/StepVisual_ContextDependentInvisibility.cxx \
@top_srcdir@/src/StepVisual/StepVisual_ContextDependentOverRidingStyledItem.cxx \
@top_srcdir@/src/StepVisual/StepVisual_CurveStyle.cxx \
@top_srcdir@/src/StepVisual/StepVisual_CurveStyleFont.cxx \
@top_srcdir@/src/StepVisual/StepVisual_CurveStyleFontPattern.cxx \
@top_srcdir@/src/StepVisual/StepVisual_CurveStyleFontSelect.cxx \
@top_srcdir@/src/StepVisual/StepVisual_DirectionCountSelect.cxx \
@top_srcdir@/src/StepVisual/StepVisual_DraughtingAnnotationOccurrence.cxx \
@top_srcdir@/src/StepVisual/StepVisual_DraughtingModel.cxx \
@top_srcdir@/src/StepVisual/StepVisual_DraughtingPreDefinedColour.cxx \
@top_srcdir@/src/StepVisual/StepVisual_DraughtingPreDefinedCurveFont.cxx \
@top_srcdir@/src/StepVisual/StepVisual_ExternallyDefinedCurveFont.cxx \
@top_srcdir@/src/StepVisual/StepVisual_ExternallyDefinedTextFont.cxx \
@top_srcdir@/src/StepVisual/StepVisual_FillAreaStyle.cxx \
@top_srcdir@/src/StepVisual/StepVisual_FillAreaStyleColour.cxx \
@top_srcdir@/src/StepVisual/StepVisual_FillStyleSelect.cxx \
@top_srcdir@/src/StepVisual/StepVisual_FontSelect.cxx \
@top_srcdir@/src/StepVisual/StepVisual_Invisibility.cxx \
@top_srcdir@/src/StepVisual/StepVisual_InvisibilityContext.cxx \
@top_srcdir@/src/StepVisual/StepVisual_InvisibleItem.cxx \
@top_srcdir@/src/StepVisual/StepVisual_LayeredItem.cxx \
@top_srcdir@/src/StepVisual/StepVisual_MarkerMember.cxx \
@top_srcdir@/src/StepVisual/StepVisual_MarkerSelect.cxx \
@top_srcdir@/src/StepVisual/StepVisual_MechanicalDesignGeometricPresentationArea.cxx \
@top_srcdir@/src/StepVisual/StepVisual_MechanicalDesignGeometricPresentationRepresentation.cxx \
@top_srcdir@/src/StepVisual/StepVisual_OverRidingStyledItem.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PlanarBox.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PlanarExtent.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PointStyle.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PreDefinedColour.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PreDefinedCurveFont.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PreDefinedItem.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PreDefinedTextFont.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PresentationArea.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PresentationLayerAssignment.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PresentationLayerUsage.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PresentationRepresentation.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PresentationRepresentationSelect.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PresentationSet.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PresentationSize.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PresentationSizeAssignmentSelect.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PresentationStyleAssignment.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PresentationStyleByContext.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PresentationStyleSelect.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PresentationView.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PresentedItem.cxx \
@top_srcdir@/src/StepVisual/StepVisual_PresentedItemRepresentation.cxx \
@top_srcdir@/src/StepVisual/StepVisual_StyleContextSelect.cxx \
@top_srcdir@/src/StepVisual/StepVisual_StyledItem.cxx \
@top_srcdir@/src/StepVisual/StepVisual_SurfaceSideStyle.cxx \
@top_srcdir@/src/StepVisual/StepVisual_SurfaceStyleBoundary.cxx \
@top_srcdir@/src/StepVisual/StepVisual_SurfaceStyleControlGrid.cxx \
@top_srcdir@/src/StepVisual/StepVisual_SurfaceStyleElementSelect.cxx \
@top_srcdir@/src/StepVisual/StepVisual_SurfaceStyleFillArea.cxx \
@top_srcdir@/src/StepVisual/StepVisual_SurfaceStyleParameterLine.cxx \
@top_srcdir@/src/StepVisual/StepVisual_SurfaceStyleSegmentationCurve.cxx \
@top_srcdir@/src/StepVisual/StepVisual_SurfaceStyleSilhouette.cxx \
@top_srcdir@/src/StepVisual/StepVisual_SurfaceStyleUsage.cxx \
@top_srcdir@/src/StepVisual/StepVisual_Template.cxx \
@top_srcdir@/src/StepVisual/StepVisual_TemplateInstance.cxx \
@top_srcdir@/src/StepVisual/StepVisual_TextLiteral.cxx \
@top_srcdir@/src/StepVisual/StepVisual_TextOrCharacter.cxx \
@top_srcdir@/src/StepVisual/StepVisual_TextStyle.cxx \
@top_srcdir@/src/StepVisual/StepVisual_TextStyleForDefinedFont.cxx \
@top_srcdir@/src/StepVisual/StepVisual_TextStyleWithBoxCharacteristics.cxx \
@top_srcdir@/src/StepVisual/StepVisual_ViewVolume.cxx

