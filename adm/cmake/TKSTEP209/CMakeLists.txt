project(TKSTEP209)

if (WIN32)
  list( APPEND TKSTEP209_PRECOMPILED_DEFS "-D__StepElement_DLL" )
  list( APPEND TKSTEP209_PRECOMPILED_DEFS "-D__StepFEA_DLL" )
  list( APPEND TKSTEP209_PRECOMPILED_DEFS "-D__RWStepElement_DLL" )
  list( APPEND TKSTEP209_PRECOMPILED_DEFS "-D__RWStepFEA_DLL" )
  string( REGEX REPLACE ";" " " TKSTEP209_PRECOMPILED_DEFS "${TKSTEP209_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKSTEP209_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKSTEP209_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKSTEP209_COMPILER_DIRECTORIES "../../../drv/StepElement" )
  list( APPEND TKSTEP209_COMPILER_DIRECTORIES "../../../src/StepElement" )
  list( APPEND TKSTEP209_COMPILER_DIRECTORIES "../../../drv/StepFEA" )
  list( APPEND TKSTEP209_COMPILER_DIRECTORIES "../../../src/StepFEA" )
  list( APPEND TKSTEP209_COMPILER_DIRECTORIES "../../../drv/RWStepElement" )
  list( APPEND TKSTEP209_COMPILER_DIRECTORIES "../../../src/RWStepElement" )
  list( APPEND TKSTEP209_COMPILER_DIRECTORIES "../../../drv/RWStepFEA" )
  list( APPEND TKSTEP209_COMPILER_DIRECTORIES "../../../src/RWStepFEA" )

if (WIN32)
else()
endif()

  list( APPEND TKSTEP209_USED_LIBS TKernel )
  list( APPEND TKSTEP209_USED_LIBS TKXSBase )
  list( APPEND TKSTEP209_USED_LIBS TKSTEPBase )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_Array1OfCurveElementEndReleasePacket_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_Array1OfCurveElementEndReleasePacket_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_Array1OfCurveElementSectionDefinition_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_Array1OfCurveElementSectionDefinition_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_Array1OfHSequenceOfCurveElementPurposeMember_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_Array1OfHSequenceOfCurveElementPurposeMember_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_Array1OfHSequenceOfSurfaceElementPurposeMember_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_Array1OfHSequenceOfSurfaceElementPurposeMember_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_Array1OfMeasureOrUnspecifiedValue_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_Array1OfMeasureOrUnspecifiedValue_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_Array1OfSurfaceSection_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_Array1OfSurfaceSection_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_Array1OfVolumeElementPurposeMember_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_Array1OfVolumeElementPurposeMember_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_Array1OfVolumeElementPurpose_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_Array1OfVolumeElementPurpose_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_Array2OfCurveElementPurposeMember_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_Array2OfCurveElementPurposeMember_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_Array2OfSurfaceElementPurposeMember_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_Array2OfSurfaceElementPurposeMember_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_Array2OfSurfaceElementPurpose_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_Array2OfSurfaceElementPurpose_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_HArray1OfCurveElementEndReleasePacket_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_HArray1OfCurveElementEndReleasePacket_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_HArray1OfCurveElementSectionDefinition_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_HArray1OfCurveElementSectionDefinition_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_HArray1OfHSequenceOfCurveElementPurposeMember_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_HArray1OfHSequenceOfCurveElementPurposeMember_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_HArray1OfHSequenceOfSurfaceElementPurposeMember_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_HArray1OfHSequenceOfSurfaceElementPurposeMember_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_HArray1OfMeasureOrUnspecifiedValue_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_HArray1OfMeasureOrUnspecifiedValue_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_HArray1OfSurfaceSection_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_HArray1OfSurfaceSection_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_HArray1OfVolumeElementPurposeMember_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_HArray1OfVolumeElementPurposeMember_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_HArray1OfVolumeElementPurpose_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_HArray1OfVolumeElementPurpose_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_HArray2OfCurveElementPurposeMember_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_HArray2OfCurveElementPurposeMember_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_HArray2OfSurfaceElementPurposeMember_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_HArray2OfSurfaceElementPurposeMember_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_HArray2OfSurfaceElementPurpose_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_HArray2OfSurfaceElementPurpose_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_HSequenceOfCurveElementPurposeMember_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_HSequenceOfCurveElementPurposeMember_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_HSequenceOfCurveElementSectionDefinition_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_HSequenceOfCurveElementSectionDefinition_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_HSequenceOfElementMaterial_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_HSequenceOfElementMaterial_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_HSequenceOfSurfaceElementPurposeMember_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_HSequenceOfSurfaceElementPurposeMember_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_SequenceNodeOfSequenceOfCurveElementPurposeMember_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_SequenceNodeOfSequenceOfCurveElementPurposeMember_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_SequenceNodeOfSequenceOfCurveElementSectionDefinition_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_SequenceNodeOfSequenceOfCurveElementSectionDefinition_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_SequenceNodeOfSequenceOfElementMaterial_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_SequenceNodeOfSequenceOfElementMaterial_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_SequenceNodeOfSequenceOfSurfaceElementPurposeMember_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_SequenceNodeOfSequenceOfSurfaceElementPurposeMember_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_SequenceOfCurveElementPurposeMember_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_SequenceOfCurveElementPurposeMember_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_SequenceOfCurveElementSectionDefinition_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_SequenceOfCurveElementSectionDefinition_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_SequenceOfElementMaterial_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_SequenceOfElementMaterial_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepElement/StepElement_SequenceOfSurfaceElementPurposeMember_0.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../drv/StepElement/StepElement_SequenceOfSurfaceElementPurposeMember_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_AnalysisItemWithinRepresentation.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_AnalysisItemWithinRepresentation.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_Curve3dElementDescriptor.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_Curve3dElementDescriptor.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_CurveElementEndReleasePacket.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_CurveElementEndReleasePacket.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_CurveElementFreedom.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_CurveElementFreedom.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_CurveElementFreedomMember.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_CurveElementFreedomMember.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_CurveElementPurpose.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_CurveElementPurpose.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_CurveElementPurposeMember.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_CurveElementPurposeMember.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_CurveElementSectionDefinition.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_CurveElementSectionDefinition.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_CurveElementSectionDerivedDefinitions.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_CurveElementSectionDerivedDefinitions.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_ElementAspect.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_ElementAspect.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_ElementAspectMember.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_ElementAspectMember.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_ElementDescriptor.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_ElementDescriptor.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_ElementMaterial.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_ElementMaterial.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_MeasureOrUnspecifiedValue.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_MeasureOrUnspecifiedValue.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_MeasureOrUnspecifiedValueMember.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_MeasureOrUnspecifiedValueMember.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_Surface3dElementDescriptor.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_Surface3dElementDescriptor.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_SurfaceElementProperty.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_SurfaceElementProperty.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_SurfaceElementPurpose.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_SurfaceElementPurpose.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_SurfaceElementPurposeMember.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_SurfaceElementPurposeMember.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_SurfaceSection.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_SurfaceSection.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_SurfaceSectionField.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_SurfaceSectionField.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_SurfaceSectionFieldConstant.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_SurfaceSectionFieldConstant.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_SurfaceSectionFieldVarying.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_SurfaceSectionFieldVarying.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_UniformSurfaceSection.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_UniformSurfaceSection.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_Volume3dElementDescriptor.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_Volume3dElementDescriptor.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_VolumeElementPurpose.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_VolumeElementPurpose.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepElement/StepElement_VolumeElementPurposeMember.cxx" )
  SOURCE_GROUP (StepElement FILES "../../../src/StepElement/StepElement_VolumeElementPurposeMember.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_Array1OfCurveElementEndOffset_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_Array1OfCurveElementEndOffset_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_Array1OfCurveElementEndRelease_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_Array1OfCurveElementEndRelease_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_Array1OfCurveElementInterval_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_Array1OfCurveElementInterval_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_Array1OfDegreeOfFreedom_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_Array1OfDegreeOfFreedom_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_Array1OfElementRepresentation_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_Array1OfElementRepresentation_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_Array1OfNodeRepresentation_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_Array1OfNodeRepresentation_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_HArray1OfCurveElementEndOffset_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_HArray1OfCurveElementEndOffset_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_HArray1OfCurveElementEndRelease_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_HArray1OfCurveElementEndRelease_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_HArray1OfCurveElementInterval_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_HArray1OfCurveElementInterval_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_HArray1OfDegreeOfFreedom_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_HArray1OfDegreeOfFreedom_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_HArray1OfElementRepresentation_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_HArray1OfElementRepresentation_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_HArray1OfNodeRepresentation_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_HArray1OfNodeRepresentation_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_HSequenceOfCurve3dElementProperty_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_HSequenceOfCurve3dElementProperty_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_HSequenceOfElementGeometricRelationship_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_HSequenceOfElementGeometricRelationship_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_HSequenceOfElementRepresentation_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_HSequenceOfElementRepresentation_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_HSequenceOfNodeRepresentation_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_HSequenceOfNodeRepresentation_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_SequenceNodeOfSequenceOfCurve3dElementProperty_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_SequenceNodeOfSequenceOfCurve3dElementProperty_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_SequenceNodeOfSequenceOfElementGeometricRelationship_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_SequenceNodeOfSequenceOfElementGeometricRelationship_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_SequenceNodeOfSequenceOfElementRepresentation_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_SequenceNodeOfSequenceOfElementRepresentation_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_SequenceNodeOfSequenceOfNodeRepresentation_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_SequenceNodeOfSequenceOfNodeRepresentation_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_SequenceOfCurve3dElementProperty_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_SequenceOfCurve3dElementProperty_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_SequenceOfElementGeometricRelationship_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_SequenceOfElementGeometricRelationship_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_SequenceOfElementRepresentation_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_SequenceOfElementRepresentation_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../drv/StepFEA/StepFEA_SequenceOfNodeRepresentation_0.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../drv/StepFEA/StepFEA_SequenceOfNodeRepresentation_0.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_AlignedCurve3dElementCoordinateSystem.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_AlignedCurve3dElementCoordinateSystem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_AlignedSurface3dElementCoordinateSystem.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_AlignedSurface3dElementCoordinateSystem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_ArbitraryVolume3dElementCoordinateSystem.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_ArbitraryVolume3dElementCoordinateSystem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_ConstantSurface3dElementCoordinateSystem.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_ConstantSurface3dElementCoordinateSystem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_Curve3dElementProperty.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_Curve3dElementProperty.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_Curve3dElementRepresentation.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_Curve3dElementRepresentation.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_CurveElementEndCoordinateSystem.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_CurveElementEndCoordinateSystem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_CurveElementEndOffset.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_CurveElementEndOffset.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_CurveElementEndRelease.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_CurveElementEndRelease.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_CurveElementInterval.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_CurveElementInterval.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_CurveElementIntervalConstant.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_CurveElementIntervalConstant.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_CurveElementIntervalLinearlyVarying.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_CurveElementIntervalLinearlyVarying.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_CurveElementLocation.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_CurveElementLocation.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_DegreeOfFreedom.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_DegreeOfFreedom.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_DegreeOfFreedomMember.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_DegreeOfFreedomMember.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_DummyNode.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_DummyNode.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_ElementGeometricRelationship.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_ElementGeometricRelationship.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_ElementGroup.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_ElementGroup.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_ElementOrElementGroup.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_ElementOrElementGroup.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_ElementRepresentation.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_ElementRepresentation.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaAreaDensity.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaAreaDensity.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaAxis2Placement3d.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaAxis2Placement3d.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaCurveSectionGeometricRelationship.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaCurveSectionGeometricRelationship.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaGroup.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaGroup.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaLinearElasticity.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaLinearElasticity.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaMassDensity.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaMassDensity.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaMaterialPropertyRepresentation.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaMaterialPropertyRepresentation.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaMaterialPropertyRepresentationItem.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaMaterialPropertyRepresentationItem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaModel.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaModel.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaModel3d.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaModel3d.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaModelDefinition.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaModelDefinition.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaMoistureAbsorption.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaMoistureAbsorption.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaParametricPoint.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaParametricPoint.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaRepresentationItem.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaRepresentationItem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaSecantCoefficientOfLinearThermalExpansion.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaSecantCoefficientOfLinearThermalExpansion.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaShellBendingStiffness.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaShellBendingStiffness.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaShellMembraneBendingCouplingStiffness.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaShellMembraneBendingCouplingStiffness.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaShellMembraneStiffness.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaShellMembraneStiffness.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaShellShearStiffness.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaShellShearStiffness.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaSurfaceSectionGeometricRelationship.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaSurfaceSectionGeometricRelationship.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FreedomAndCoefficient.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FreedomAndCoefficient.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_FreedomsList.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_FreedomsList.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_GeometricNode.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_GeometricNode.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_Node.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_Node.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_NodeDefinition.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_NodeDefinition.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_NodeGroup.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_NodeGroup.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_NodeRepresentation.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_NodeRepresentation.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_NodeSet.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_NodeSet.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_NodeWithSolutionCoordinateSystem.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_NodeWithSolutionCoordinateSystem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_NodeWithVector.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_NodeWithVector.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_ParametricCurve3dElementCoordinateDirection.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_ParametricCurve3dElementCoordinateDirection.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_ParametricCurve3dElementCoordinateSystem.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_ParametricCurve3dElementCoordinateSystem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_ParametricSurface3dElementCoordinateSystem.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_ParametricSurface3dElementCoordinateSystem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_Surface3dElementRepresentation.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_Surface3dElementRepresentation.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_SymmetricTensor22d.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_SymmetricTensor22d.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_SymmetricTensor23d.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_SymmetricTensor23d.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_SymmetricTensor23dMember.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_SymmetricTensor23dMember.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_SymmetricTensor42d.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_SymmetricTensor42d.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_SymmetricTensor43d.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_SymmetricTensor43d.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_SymmetricTensor43dMember.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_SymmetricTensor43dMember.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/StepFEA/StepFEA_Volume3dElementRepresentation.cxx" )
  SOURCE_GROUP (StepFEA FILES "../../../src/StepFEA/StepFEA_Volume3dElementRepresentation.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepElement/RWStepElement_RWAnalysisItemWithinRepresentation.cxx" )
  SOURCE_GROUP (RWStepElement FILES "../../../src/RWStepElement/RWStepElement_RWAnalysisItemWithinRepresentation.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepElement/RWStepElement_RWCurve3dElementDescriptor.cxx" )
  SOURCE_GROUP (RWStepElement FILES "../../../src/RWStepElement/RWStepElement_RWCurve3dElementDescriptor.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepElement/RWStepElement_RWCurveElementEndReleasePacket.cxx" )
  SOURCE_GROUP (RWStepElement FILES "../../../src/RWStepElement/RWStepElement_RWCurveElementEndReleasePacket.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepElement/RWStepElement_RWCurveElementSectionDefinition.cxx" )
  SOURCE_GROUP (RWStepElement FILES "../../../src/RWStepElement/RWStepElement_RWCurveElementSectionDefinition.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepElement/RWStepElement_RWCurveElementSectionDerivedDefinitions.cxx" )
  SOURCE_GROUP (RWStepElement FILES "../../../src/RWStepElement/RWStepElement_RWCurveElementSectionDerivedDefinitions.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepElement/RWStepElement_RWElementDescriptor.cxx" )
  SOURCE_GROUP (RWStepElement FILES "../../../src/RWStepElement/RWStepElement_RWElementDescriptor.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepElement/RWStepElement_RWElementMaterial.cxx" )
  SOURCE_GROUP (RWStepElement FILES "../../../src/RWStepElement/RWStepElement_RWElementMaterial.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepElement/RWStepElement_RWSurface3dElementDescriptor.cxx" )
  SOURCE_GROUP (RWStepElement FILES "../../../src/RWStepElement/RWStepElement_RWSurface3dElementDescriptor.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepElement/RWStepElement_RWSurfaceElementProperty.cxx" )
  SOURCE_GROUP (RWStepElement FILES "../../../src/RWStepElement/RWStepElement_RWSurfaceElementProperty.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepElement/RWStepElement_RWSurfaceSection.cxx" )
  SOURCE_GROUP (RWStepElement FILES "../../../src/RWStepElement/RWStepElement_RWSurfaceSection.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepElement/RWStepElement_RWSurfaceSectionField.cxx" )
  SOURCE_GROUP (RWStepElement FILES "../../../src/RWStepElement/RWStepElement_RWSurfaceSectionField.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepElement/RWStepElement_RWSurfaceSectionFieldConstant.cxx" )
  SOURCE_GROUP (RWStepElement FILES "../../../src/RWStepElement/RWStepElement_RWSurfaceSectionFieldConstant.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepElement/RWStepElement_RWSurfaceSectionFieldVarying.cxx" )
  SOURCE_GROUP (RWStepElement FILES "../../../src/RWStepElement/RWStepElement_RWSurfaceSectionFieldVarying.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepElement/RWStepElement_RWUniformSurfaceSection.cxx" )
  SOURCE_GROUP (RWStepElement FILES "../../../src/RWStepElement/RWStepElement_RWUniformSurfaceSection.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepElement/RWStepElement_RWVolume3dElementDescriptor.cxx" )
  SOURCE_GROUP (RWStepElement FILES "../../../src/RWStepElement/RWStepElement_RWVolume3dElementDescriptor.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWAlignedCurve3dElementCoordinateSystem.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWAlignedCurve3dElementCoordinateSystem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWAlignedSurface3dElementCoordinateSystem.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWAlignedSurface3dElementCoordinateSystem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWArbitraryVolume3dElementCoordinateSystem.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWArbitraryVolume3dElementCoordinateSystem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWConstantSurface3dElementCoordinateSystem.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWConstantSurface3dElementCoordinateSystem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWCurve3dElementProperty.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWCurve3dElementProperty.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWCurve3dElementRepresentation.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWCurve3dElementRepresentation.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWCurveElementEndOffset.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWCurveElementEndOffset.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWCurveElementEndRelease.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWCurveElementEndRelease.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWCurveElementInterval.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWCurveElementInterval.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWCurveElementIntervalConstant.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWCurveElementIntervalConstant.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWCurveElementIntervalLinearlyVarying.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWCurveElementIntervalLinearlyVarying.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWCurveElementLocation.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWCurveElementLocation.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWDummyNode.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWDummyNode.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWElementGeometricRelationship.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWElementGeometricRelationship.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWElementGroup.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWElementGroup.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWElementRepresentation.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWElementRepresentation.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaAreaDensity.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaAreaDensity.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaAxis2Placement3d.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaAxis2Placement3d.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaCurveSectionGeometricRelationship.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaCurveSectionGeometricRelationship.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaGroup.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaGroup.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaLinearElasticity.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaLinearElasticity.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaMassDensity.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaMassDensity.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaMaterialPropertyRepresentation.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaMaterialPropertyRepresentation.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaMaterialPropertyRepresentationItem.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaMaterialPropertyRepresentationItem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaModel.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaModel.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaModel3d.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaModel3d.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaModelDefinition.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaModelDefinition.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaMoistureAbsorption.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaMoistureAbsorption.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaParametricPoint.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaParametricPoint.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaRepresentationItem.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaRepresentationItem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaSecantCoefficientOfLinearThermalExpansion.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaSecantCoefficientOfLinearThermalExpansion.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaShellBendingStiffness.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaShellBendingStiffness.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaShellMembraneBendingCouplingStiffness.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaShellMembraneBendingCouplingStiffness.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaShellMembraneStiffness.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaShellMembraneStiffness.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaShellShearStiffness.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaShellShearStiffness.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaSurfaceSectionGeometricRelationship.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaSurfaceSectionGeometricRelationship.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFeaTangentialCoefficientOfLinearThermalExpansion.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFeaTangentialCoefficientOfLinearThermalExpansion.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFreedomAndCoefficient.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFreedomAndCoefficient.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWFreedomsList.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWFreedomsList.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWGeometricNode.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWGeometricNode.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWNode.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWNode.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWNodeDefinition.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWNodeDefinition.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWNodeGroup.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWNodeGroup.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWNodeRepresentation.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWNodeRepresentation.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWNodeSet.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWNodeSet.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWNodeWithSolutionCoordinateSystem.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWNodeWithSolutionCoordinateSystem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWNodeWithVector.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWNodeWithVector.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWParametricCurve3dElementCoordinateDirection.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWParametricCurve3dElementCoordinateDirection.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWParametricCurve3dElementCoordinateSystem.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWParametricCurve3dElementCoordinateSystem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWParametricSurface3dElementCoordinateSystem.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWParametricSurface3dElementCoordinateSystem.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWSurface3dElementRepresentation.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWSurface3dElementRepresentation.cxx")

  list( APPEND TKSTEP209_USED_SRCFILES "../../../src/RWStepFEA/RWStepFEA_RWVolume3dElementRepresentation.cxx" )
  SOURCE_GROUP (RWStepFEA FILES "../../../src/RWStepFEA/RWStepFEA_RWVolume3dElementRepresentation.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKSTEP209)
 add_library( TKSTEP209 SHARED ${TKSTEP209_USED_SRCFILES} )

 set_property(TARGET TKSTEP209 PROPERTY FOLDER DataExchange)

 install( TARGETS TKSTEP209
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKSTEP209.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKSTEP209 PROPERTIES COMPILE_FLAGS "${TKSTEP209_PRECOMPILED_DEFS}" )
 include_directories( ${TKSTEP209_COMPILER_DIRECTORIES} )
 target_link_libraries( TKSTEP209 ${TKSTEP209_USED_LIBS} )
endif()
