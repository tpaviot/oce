project(TKSTEPAttr)

if (WIN32)
  list( APPEND TKSTEPAttr_PRECOMPILED_DEFS "-D__StepVisual_DLL" )
  list( APPEND TKSTEPAttr_PRECOMPILED_DEFS "-D__RWStepVisual_DLL" )
  list( APPEND TKSTEPAttr_PRECOMPILED_DEFS "-D__StepDimTol_DLL" )
  list( APPEND TKSTEPAttr_PRECOMPILED_DEFS "-D__RWStepDimTol_DLL" )
  string( REGEX REPLACE ";" " " TKSTEPAttr_PRECOMPILED_DEFS "${TKSTEPAttr_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKSTEPAttr_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKSTEPAttr_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKSTEPAttr_COMPILER_DIRECTORIES "../../../drv/StepVisual" )
  list( APPEND TKSTEPAttr_COMPILER_DIRECTORIES "../../../src/StepVisual" )
  list( APPEND TKSTEPAttr_COMPILER_DIRECTORIES "../../../drv/RWStepVisual" )
  list( APPEND TKSTEPAttr_COMPILER_DIRECTORIES "../../../src/RWStepVisual" )
  list( APPEND TKSTEPAttr_COMPILER_DIRECTORIES "../../../drv/StepDimTol" )
  list( APPEND TKSTEPAttr_COMPILER_DIRECTORIES "../../../src/StepDimTol" )
  list( APPEND TKSTEPAttr_COMPILER_DIRECTORIES "../../../drv/RWStepDimTol" )
  list( APPEND TKSTEPAttr_COMPILER_DIRECTORIES "../../../src/RWStepDimTol" )

if (WIN32)
else()
endif()

  list( APPEND TKSTEPAttr_USED_LIBS TKernel )
  list( APPEND TKSTEPAttr_USED_LIBS TKXSBase )
  list( APPEND TKSTEPAttr_USED_LIBS TKSTEPBase )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_Array1OfBoxCharacteristicSelect_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_Array1OfBoxCharacteristicSelect_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_Array1OfCurveStyleFontPattern_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_Array1OfCurveStyleFontPattern_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_Array1OfDirectionCountSelect_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_Array1OfDirectionCountSelect_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_Array1OfFillStyleSelect_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_Array1OfFillStyleSelect_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_Array1OfInvisibleItem_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_Array1OfInvisibleItem_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_Array1OfLayeredItem_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_Array1OfLayeredItem_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_Array1OfPresentationStyleAssignment_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_Array1OfPresentationStyleAssignment_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_Array1OfPresentationStyleSelect_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_Array1OfPresentationStyleSelect_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_Array1OfStyleContextSelect_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_Array1OfStyleContextSelect_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_Array1OfSurfaceStyleElementSelect_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_Array1OfSurfaceStyleElementSelect_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_Array1OfTextOrCharacter_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_Array1OfTextOrCharacter_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_HArray1OfBoxCharacteristicSelect_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_HArray1OfBoxCharacteristicSelect_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_HArray1OfCurveStyleFontPattern_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_HArray1OfCurveStyleFontPattern_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_HArray1OfDirectionCountSelect_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_HArray1OfDirectionCountSelect_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_HArray1OfFillStyleSelect_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_HArray1OfFillStyleSelect_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_HArray1OfInvisibleItem_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_HArray1OfInvisibleItem_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_HArray1OfLayeredItem_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_HArray1OfLayeredItem_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_HArray1OfPresentationStyleAssignment_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_HArray1OfPresentationStyleAssignment_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_HArray1OfPresentationStyleSelect_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_HArray1OfPresentationStyleSelect_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_HArray1OfStyleContextSelect_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_HArray1OfStyleContextSelect_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_HArray1OfSurfaceStyleElementSelect_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_HArray1OfSurfaceStyleElementSelect_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepVisual/StepVisual_HArray1OfTextOrCharacter_0.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../drv/StepVisual/StepVisual_HArray1OfTextOrCharacter_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_AnnotationOccurrence.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_AnnotationOccurrence.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_AnnotationText.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_AnnotationText.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_AnnotationTextOccurrence.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_AnnotationTextOccurrence.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_AreaInSet.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_AreaInSet.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_AreaOrView.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_AreaOrView.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_BackgroundColour.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_BackgroundColour.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_BoxCharacteristicSelect.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_BoxCharacteristicSelect.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_CameraImage.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_CameraImage.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_CameraImage2dWithScale.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_CameraImage2dWithScale.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_CameraImage3dWithScale.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_CameraImage3dWithScale.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_CameraModel.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_CameraModel.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_CameraModelD2.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_CameraModelD2.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_CameraModelD3.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_CameraModelD3.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_CameraUsage.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_CameraUsage.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_Colour.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_Colour.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_ColourRgb.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_ColourRgb.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_ColourSpecification.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_ColourSpecification.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_CompositeText.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_CompositeText.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_CompositeTextWithExtent.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_CompositeTextWithExtent.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_ContextDependentInvisibility.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_ContextDependentInvisibility.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_ContextDependentOverRidingStyledItem.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_ContextDependentOverRidingStyledItem.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_CurveStyle.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_CurveStyle.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_CurveStyleFont.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_CurveStyleFont.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_CurveStyleFontPattern.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_CurveStyleFontPattern.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_CurveStyleFontSelect.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_CurveStyleFontSelect.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_DirectionCountSelect.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_DirectionCountSelect.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_DraughtingAnnotationOccurrence.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_DraughtingAnnotationOccurrence.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_DraughtingModel.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_DraughtingModel.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_DraughtingPreDefinedColour.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_DraughtingPreDefinedColour.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_DraughtingPreDefinedCurveFont.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_DraughtingPreDefinedCurveFont.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_ExternallyDefinedCurveFont.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_ExternallyDefinedCurveFont.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_ExternallyDefinedTextFont.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_ExternallyDefinedTextFont.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_FillAreaStyle.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_FillAreaStyle.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_FillAreaStyleColour.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_FillAreaStyleColour.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_FillStyleSelect.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_FillStyleSelect.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_FontSelect.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_FontSelect.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_Invisibility.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_Invisibility.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_InvisibilityContext.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_InvisibilityContext.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_InvisibleItem.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_InvisibleItem.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_LayeredItem.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_LayeredItem.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_MarkerMember.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_MarkerMember.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_MarkerSelect.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_MarkerSelect.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_MechanicalDesignGeometricPresentationArea.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_MechanicalDesignGeometricPresentationArea.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_MechanicalDesignGeometricPresentationRepresentation.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_MechanicalDesignGeometricPresentationRepresentation.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_OverRidingStyledItem.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_OverRidingStyledItem.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PlanarBox.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PlanarBox.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PlanarExtent.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PlanarExtent.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PointStyle.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PointStyle.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PreDefinedColour.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PreDefinedColour.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PreDefinedCurveFont.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PreDefinedCurveFont.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PreDefinedItem.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PreDefinedItem.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PreDefinedTextFont.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PreDefinedTextFont.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PresentationArea.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PresentationArea.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PresentationLayerAssignment.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PresentationLayerAssignment.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PresentationLayerUsage.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PresentationLayerUsage.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PresentationRepresentation.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PresentationRepresentation.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PresentationRepresentationSelect.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PresentationRepresentationSelect.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PresentationSet.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PresentationSet.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PresentationSize.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PresentationSize.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PresentationSizeAssignmentSelect.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PresentationSizeAssignmentSelect.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PresentationStyleAssignment.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PresentationStyleAssignment.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PresentationStyleByContext.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PresentationStyleByContext.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PresentationStyleSelect.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PresentationStyleSelect.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PresentationView.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PresentationView.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PresentedItem.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PresentedItem.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_PresentedItemRepresentation.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_PresentedItemRepresentation.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_StyleContextSelect.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_StyleContextSelect.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_StyledItem.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_StyledItem.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_SurfaceSideStyle.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_SurfaceSideStyle.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_SurfaceStyleBoundary.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_SurfaceStyleBoundary.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_SurfaceStyleControlGrid.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_SurfaceStyleControlGrid.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_SurfaceStyleElementSelect.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_SurfaceStyleElementSelect.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_SurfaceStyleFillArea.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_SurfaceStyleFillArea.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_SurfaceStyleParameterLine.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_SurfaceStyleParameterLine.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_SurfaceStyleSegmentationCurve.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_SurfaceStyleSegmentationCurve.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_SurfaceStyleSilhouette.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_SurfaceStyleSilhouette.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_SurfaceStyleUsage.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_SurfaceStyleUsage.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_Template.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_Template.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_TemplateInstance.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_TemplateInstance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_TextLiteral.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_TextLiteral.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_TextOrCharacter.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_TextOrCharacter.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_TextStyle.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_TextStyle.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_TextStyleForDefinedFont.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_TextStyleForDefinedFont.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_TextStyleWithBoxCharacteristics.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_TextStyleWithBoxCharacteristics.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepVisual/StepVisual_ViewVolume.cxx" )
  SOURCE_GROUP (StepVisual FILES "../../../src/StepVisual/StepVisual_ViewVolume.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWAreaInSet.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWAreaInSet.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWBackgroundColour.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWBackgroundColour.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWCameraImage.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWCameraImage.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWCameraModel.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWCameraModel.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWCameraModelD2.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWCameraModelD2.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWCameraModelD3.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWCameraModelD3.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWCameraUsage.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWCameraUsage.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWColour.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWColour.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWColourRgb.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWColourRgb.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWColourSpecification.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWColourSpecification.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWCompositeText.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWCompositeText.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWCompositeTextWithExtent.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWCompositeTextWithExtent.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWContextDependentInvisibility.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWContextDependentInvisibility.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWContextDependentOverRidingStyledItem.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWContextDependentOverRidingStyledItem.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWCurveStyle.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWCurveStyle.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWCurveStyleFont.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWCurveStyleFont.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWCurveStyleFontPattern.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWCurveStyleFontPattern.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWDraughtingModel.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWDraughtingModel.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWDraughtingPreDefinedColour.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWDraughtingPreDefinedColour.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWDraughtingPreDefinedCurveFont.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWDraughtingPreDefinedCurveFont.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWExternallyDefinedCurveFont.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWExternallyDefinedCurveFont.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWFillAreaStyle.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWFillAreaStyle.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWFillAreaStyleColour.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWFillAreaStyleColour.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWInvisibility.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWInvisibility.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWMechanicalDesignGeometricPresentationArea.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWMechanicalDesignGeometricPresentationArea.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWMechanicalDesignGeometricPresentationRepresentation.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWMechanicalDesignGeometricPresentationRepresentation.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWOverRidingStyledItem.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWOverRidingStyledItem.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWPlanarBox.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWPlanarBox.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWPlanarExtent.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWPlanarExtent.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWPointStyle.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWPointStyle.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWPreDefinedColour.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWPreDefinedColour.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWPreDefinedCurveFont.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWPreDefinedCurveFont.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWPreDefinedItem.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWPreDefinedItem.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWPresentationArea.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWPresentationArea.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWPresentationLayerAssignment.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWPresentationLayerAssignment.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWPresentationLayerUsage.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWPresentationLayerUsage.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWPresentationRepresentation.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWPresentationRepresentation.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWPresentationSet.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWPresentationSet.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWPresentationSize.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWPresentationSize.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWPresentationStyleAssignment.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWPresentationStyleAssignment.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWPresentationStyleByContext.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWPresentationStyleByContext.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWPresentationView.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWPresentationView.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWPresentedItemRepresentation.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWPresentedItemRepresentation.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWStyledItem.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWStyledItem.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWSurfaceSideStyle.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWSurfaceSideStyle.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWSurfaceStyleBoundary.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWSurfaceStyleBoundary.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWSurfaceStyleControlGrid.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWSurfaceStyleControlGrid.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWSurfaceStyleFillArea.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWSurfaceStyleFillArea.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWSurfaceStyleParameterLine.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWSurfaceStyleParameterLine.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWSurfaceStyleSegmentationCurve.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWSurfaceStyleSegmentationCurve.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWSurfaceStyleSilhouette.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWSurfaceStyleSilhouette.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWSurfaceStyleUsage.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWSurfaceStyleUsage.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWTemplate.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWTemplate.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWTemplateInstance.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWTemplateInstance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWTextLiteral.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWTextLiteral.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWTextStyle.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWTextStyle.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWTextStyleForDefinedFont.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWTextStyleForDefinedFont.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWTextStyleWithBoxCharacteristics.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWTextStyleWithBoxCharacteristics.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepVisual/RWStepVisual_RWViewVolume.cxx" )
  SOURCE_GROUP (RWStepVisual FILES "../../../src/RWStepVisual/RWStepVisual_RWViewVolume.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepDimTol/StepDimTol_Array1OfDatumReference_0.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../drv/StepDimTol/StepDimTol_Array1OfDatumReference_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../drv/StepDimTol/StepDimTol_HArray1OfDatumReference_0.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../drv/StepDimTol/StepDimTol_HArray1OfDatumReference_0.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_AngularityTolerance.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_AngularityTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_CircularRunoutTolerance.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_CircularRunoutTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_CoaxialityTolerance.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_CoaxialityTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_CommonDatum.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_CommonDatum.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_ConcentricityTolerance.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_ConcentricityTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_CylindricityTolerance.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_CylindricityTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_Datum.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_Datum.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_DatumFeature.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_DatumFeature.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_DatumReference.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_DatumReference.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_DatumTarget.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_DatumTarget.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_FlatnessTolerance.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_FlatnessTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_GeometricTolerance.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_GeometricTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_GeometricToleranceRelationship.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_GeometricToleranceRelationship.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_GeometricToleranceWithDatumReference.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_GeometricToleranceWithDatumReference.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_LineProfileTolerance.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_LineProfileTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_ModifiedGeometricTolerance.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_ModifiedGeometricTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_ParallelismTolerance.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_ParallelismTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_PerpendicularityTolerance.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_PerpendicularityTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_PlacedDatumTargetFeature.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_PlacedDatumTargetFeature.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_PositionTolerance.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_PositionTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_RoundnessTolerance.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_RoundnessTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_ShapeToleranceSelect.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_ShapeToleranceSelect.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_StraightnessTolerance.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_StraightnessTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_SurfaceProfileTolerance.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_SurfaceProfileTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_SymmetryTolerance.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_SymmetryTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/StepDimTol/StepDimTol_TotalRunoutTolerance.cxx" )
  SOURCE_GROUP (StepDimTol FILES "../../../src/StepDimTol/StepDimTol_TotalRunoutTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWAngularityTolerance.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWAngularityTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWCircularRunoutTolerance.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWCircularRunoutTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWCoaxialityTolerance.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWCoaxialityTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWCommonDatum.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWCommonDatum.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWConcentricityTolerance.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWConcentricityTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWCylindricityTolerance.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWCylindricityTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWDatum.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWDatum.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWDatumFeature.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWDatumFeature.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWDatumReference.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWDatumReference.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWDatumTarget.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWDatumTarget.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWFlatnessTolerance.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWFlatnessTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWGeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWGeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWGeometricTolerance.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWGeometricTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWGeometricToleranceRelationship.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWGeometricToleranceRelationship.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWGeometricToleranceWithDatumReference.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWGeometricToleranceWithDatumReference.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWLineProfileTolerance.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWLineProfileTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWModifiedGeometricTolerance.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWModifiedGeometricTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWParallelismTolerance.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWParallelismTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWPerpendicularityTolerance.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWPerpendicularityTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWPlacedDatumTargetFeature.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWPlacedDatumTargetFeature.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWPositionTolerance.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWPositionTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWRoundnessTolerance.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWRoundnessTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWStraightnessTolerance.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWStraightnessTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWSurfaceProfileTolerance.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWSurfaceProfileTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWSymmetryTolerance.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWSymmetryTolerance.cxx")

  list( APPEND TKSTEPAttr_USED_SRCFILES "../../../src/RWStepDimTol/RWStepDimTol_RWTotalRunoutTolerance.cxx" )
  SOURCE_GROUP (RWStepDimTol FILES "../../../src/RWStepDimTol/RWStepDimTol_RWTotalRunoutTolerance.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKSTEPAttr)
 add_library( TKSTEPAttr SHARED ${TKSTEPAttr_USED_SRCFILES} )

 set_property(TARGET TKSTEPAttr PROPERTY FOLDER DataExchange)

 install( TARGETS TKSTEPAttr
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKSTEPAttr.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKSTEPAttr PROPERTIES COMPILE_FLAGS "${TKSTEPAttr_PRECOMPILED_DEFS}" )
 include_directories( ${TKSTEPAttr_COMPILER_DIRECTORIES} )
 target_link_libraries( TKSTEPAttr ${TKSTEPAttr_USED_LIBS} )
endif()
