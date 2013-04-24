project(TKSTEPBase)

if (WIN32)
  list( APPEND TKSTEPBase_PRECOMPILED_DEFS "-D__StepBasic_DLL" )
  list( APPEND TKSTEPBase_PRECOMPILED_DEFS "-D__RWStepBasic_DLL" )
  list( APPEND TKSTEPBase_PRECOMPILED_DEFS "-D__StepRepr_DLL" )
  list( APPEND TKSTEPBase_PRECOMPILED_DEFS "-D__RWStepRepr_DLL" )
  list( APPEND TKSTEPBase_PRECOMPILED_DEFS "-D__StepGeom_DLL" )
  list( APPEND TKSTEPBase_PRECOMPILED_DEFS "-D__RWStepGeom_DLL" )
  list( APPEND TKSTEPBase_PRECOMPILED_DEFS "-D__StepShape_DLL" )
  list( APPEND TKSTEPBase_PRECOMPILED_DEFS "-D__RWStepShape_DLL" )
  string( REGEX REPLACE ";" " " TKSTEPBase_PRECOMPILED_DEFS "${TKSTEPBase_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKSTEPBase_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKSTEPBase_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKSTEPBase_COMPILER_DIRECTORIES "../../../drv/StepBasic" )
  list( APPEND TKSTEPBase_COMPILER_DIRECTORIES "../../../src/StepBasic" )
  list( APPEND TKSTEPBase_COMPILER_DIRECTORIES "../../../drv/RWStepBasic" )
  list( APPEND TKSTEPBase_COMPILER_DIRECTORIES "../../../src/RWStepBasic" )
  list( APPEND TKSTEPBase_COMPILER_DIRECTORIES "../../../drv/StepRepr" )
  list( APPEND TKSTEPBase_COMPILER_DIRECTORIES "../../../src/StepRepr" )
  list( APPEND TKSTEPBase_COMPILER_DIRECTORIES "../../../drv/RWStepRepr" )
  list( APPEND TKSTEPBase_COMPILER_DIRECTORIES "../../../src/RWStepRepr" )
  list( APPEND TKSTEPBase_COMPILER_DIRECTORIES "../../../drv/StepGeom" )
  list( APPEND TKSTEPBase_COMPILER_DIRECTORIES "../../../src/StepGeom" )
  list( APPEND TKSTEPBase_COMPILER_DIRECTORIES "../../../drv/RWStepGeom" )
  list( APPEND TKSTEPBase_COMPILER_DIRECTORIES "../../../src/RWStepGeom" )
  list( APPEND TKSTEPBase_COMPILER_DIRECTORIES "../../../drv/StepShape" )
  list( APPEND TKSTEPBase_COMPILER_DIRECTORIES "../../../src/StepShape" )
  list( APPEND TKSTEPBase_COMPILER_DIRECTORIES "../../../drv/RWStepShape" )
  list( APPEND TKSTEPBase_COMPILER_DIRECTORIES "../../../src/RWStepShape" )

if (WIN32)
else()
endif()

  list( APPEND TKSTEPBase_USED_LIBS TKernel )
  list( APPEND TKSTEPBase_USED_LIBS TKXSBase )
  list( APPEND TKSTEPBase_USED_LIBS TKMath )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_Array1OfApproval_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_Array1OfApproval_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_Array1OfDerivedUnitElement_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_Array1OfDerivedUnitElement_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_Array1OfDocument_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_Array1OfDocument_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_Array1OfNamedUnit_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_Array1OfNamedUnit_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_Array1OfOrganization_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_Array1OfOrganization_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_Array1OfPerson_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_Array1OfPerson_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_Array1OfProductContext_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_Array1OfProductContext_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_Array1OfProductDefinition_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_Array1OfProductDefinition_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_Array1OfProduct_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_Array1OfProduct_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_Array1OfUncertaintyMeasureWithUnit_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_Array1OfUncertaintyMeasureWithUnit_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_HArray1OfApproval_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_HArray1OfApproval_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_HArray1OfDerivedUnitElement_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_HArray1OfDerivedUnitElement_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_HArray1OfDocument_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_HArray1OfDocument_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_HArray1OfNamedUnit_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_HArray1OfNamedUnit_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_HArray1OfOrganization_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_HArray1OfOrganization_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_HArray1OfPerson_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_HArray1OfPerson_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_HArray1OfProductContext_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_HArray1OfProductContext_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_HArray1OfProductDefinition_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_HArray1OfProductDefinition_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_HArray1OfProduct_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_HArray1OfProduct_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepBasic/StepBasic_HArray1OfUncertaintyMeasureWithUnit_0.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../drv/StepBasic/StepBasic_HArray1OfUncertaintyMeasureWithUnit_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_Action.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_Action.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ActionAssignment.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ActionAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ActionMethod.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ActionMethod.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ActionRequestAssignment.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ActionRequestAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ActionRequestSolution.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ActionRequestSolution.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_Address.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_Address.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ApplicationContext.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ApplicationContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ApplicationContextElement.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ApplicationContextElement.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ApplicationProtocolDefinition.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ApplicationProtocolDefinition.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_Approval.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_Approval.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ApprovalAssignment.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ApprovalAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ApprovalDateTime.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ApprovalDateTime.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ApprovalPersonOrganization.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ApprovalPersonOrganization.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ApprovalRelationship.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ApprovalRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ApprovalRole.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ApprovalRole.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ApprovalStatus.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ApprovalStatus.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_AreaUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_AreaUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_CalendarDate.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_CalendarDate.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_Certification.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_Certification.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_CertificationAssignment.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_CertificationAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_CertificationType.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_CertificationType.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_CharacterizedObject.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_CharacterizedObject.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_Contract.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_Contract.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ContractAssignment.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ContractAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ContractType.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ContractType.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ConversionBasedUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ConversionBasedUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ConversionBasedUnitAndAreaUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ConversionBasedUnitAndAreaUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ConversionBasedUnitAndLengthUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ConversionBasedUnitAndLengthUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ConversionBasedUnitAndMassUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ConversionBasedUnitAndMassUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ConversionBasedUnitAndPlaneAngleUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ConversionBasedUnitAndPlaneAngleUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ConversionBasedUnitAndRatioUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ConversionBasedUnitAndRatioUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ConversionBasedUnitAndSolidAngleUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ConversionBasedUnitAndSolidAngleUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ConversionBasedUnitAndTimeUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ConversionBasedUnitAndTimeUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ConversionBasedUnitAndVolumeUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ConversionBasedUnitAndVolumeUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_CoordinatedUniversalTimeOffset.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_CoordinatedUniversalTimeOffset.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_Date.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_Date.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DateAndTime.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DateAndTime.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DateAndTimeAssignment.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DateAndTimeAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DateAssignment.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DateAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DateRole.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DateRole.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DateTimeRole.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DateTimeRole.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DateTimeSelect.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DateTimeSelect.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DerivedUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DerivedUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DerivedUnitElement.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DerivedUnitElement.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DesignContext.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DesignContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DigitalDocument.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DigitalDocument.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DimensionalExponents.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DimensionalExponents.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_Document.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_Document.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DocumentFile.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DocumentFile.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DocumentProductAssociation.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DocumentProductAssociation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DocumentProductEquivalence.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DocumentProductEquivalence.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DocumentReference.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DocumentReference.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DocumentRelationship.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DocumentRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DocumentRepresentationType.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DocumentRepresentationType.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DocumentType.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DocumentType.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_DocumentUsageConstraint.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_DocumentUsageConstraint.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_Effectivity.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_Effectivity.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_EffectivityAssignment.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_EffectivityAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_EulerAngles.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_EulerAngles.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ExternalIdentificationAssignment.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ExternalIdentificationAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ExternalSource.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ExternalSource.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ExternallyDefinedItem.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ExternallyDefinedItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_GeneralProperty.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_GeneralProperty.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_Group.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_Group.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_GroupAssignment.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_GroupAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_GroupRelationship.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_GroupRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_IdentificationAssignment.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_IdentificationAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_IdentificationRole.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_IdentificationRole.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_LengthMeasureWithUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_LengthMeasureWithUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_LengthUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_LengthUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_LocalTime.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_LocalTime.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_MassMeasureWithUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_MassMeasureWithUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_MassUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_MassUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_MeasureValueMember.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_MeasureValueMember.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_MeasureWithUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_MeasureWithUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_MechanicalContext.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_MechanicalContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_NameAssignment.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_NameAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_NamedUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_NamedUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ObjectRole.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ObjectRole.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_OrdinalDate.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_OrdinalDate.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_Organization.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_Organization.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_OrganizationAssignment.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_OrganizationAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_OrganizationRole.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_OrganizationRole.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_OrganizationalAddress.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_OrganizationalAddress.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_Person.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_Person.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_PersonAndOrganization.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_PersonAndOrganization.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_PersonAndOrganizationAssignment.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_PersonAndOrganizationAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_PersonAndOrganizationRole.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_PersonAndOrganizationRole.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_PersonOrganizationSelect.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_PersonOrganizationSelect.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_PersonalAddress.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_PersonalAddress.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_PhysicallyModeledProductDefinition.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_PhysicallyModeledProductDefinition.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_PlaneAngleMeasureWithUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_PlaneAngleMeasureWithUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_PlaneAngleUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_PlaneAngleUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_Product.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_Product.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ProductCategory.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ProductCategory.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ProductCategoryRelationship.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ProductCategoryRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ProductConceptContext.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ProductConceptContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ProductContext.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ProductContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ProductDefinition.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ProductDefinition.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ProductDefinitionContext.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ProductDefinitionContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ProductDefinitionEffectivity.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ProductDefinitionEffectivity.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ProductDefinitionFormation.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ProductDefinitionFormation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ProductDefinitionFormationRelationship.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ProductDefinitionFormationRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ProductDefinitionFormationWithSpecifiedSource.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ProductDefinitionFormationWithSpecifiedSource.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ProductDefinitionRelationship.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ProductDefinitionRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ProductDefinitionWithAssociatedDocuments.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ProductDefinitionWithAssociatedDocuments.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ProductOrFormationOrDefinition.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ProductOrFormationOrDefinition.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ProductRelatedProductCategory.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ProductRelatedProductCategory.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ProductType.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ProductType.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_RatioMeasureWithUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_RatioMeasureWithUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_RatioUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_RatioUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_RoleAssociation.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_RoleAssociation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_RoleSelect.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_RoleSelect.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_SecurityClassification.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_SecurityClassification.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_SecurityClassificationAssignment.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_SecurityClassificationAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_SecurityClassificationLevel.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_SecurityClassificationLevel.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_SiUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_SiUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_SiUnitAndAreaUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_SiUnitAndAreaUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_SiUnitAndLengthUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_SiUnitAndLengthUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_SiUnitAndMassUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_SiUnitAndMassUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_SiUnitAndPlaneAngleUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_SiUnitAndPlaneAngleUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_SiUnitAndRatioUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_SiUnitAndRatioUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_SiUnitAndSolidAngleUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_SiUnitAndSolidAngleUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_SiUnitAndThermodynamicTemperatureUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_SiUnitAndThermodynamicTemperatureUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_SiUnitAndTimeUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_SiUnitAndTimeUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_SiUnitAndVolumeUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_SiUnitAndVolumeUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_SizeMember.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_SizeMember.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_SizeSelect.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_SizeSelect.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_SolidAngleMeasureWithUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_SolidAngleMeasureWithUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_SolidAngleUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_SolidAngleUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_SourceItem.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_SourceItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_ThermodynamicTemperatureUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_ThermodynamicTemperatureUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_TimeMeasureWithUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_TimeMeasureWithUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_TimeUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_TimeUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_UncertaintyMeasureWithUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_UncertaintyMeasureWithUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_Unit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_Unit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_VersionedActionRequest.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_VersionedActionRequest.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_VolumeUnit.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_VolumeUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepBasic/StepBasic_WeekOfYearAndDayDate.cxx" )
  SOURCE_GROUP (StepBasic FILES "../../../src/StepBasic/StepBasic_WeekOfYearAndDayDate.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWAction.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWAction.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWActionAssignment.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWActionAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWActionMethod.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWActionMethod.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWActionRequestAssignment.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWActionRequestAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWActionRequestSolution.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWActionRequestSolution.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWAddress.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWAddress.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWApplicationContext.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWApplicationContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWApplicationContextElement.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWApplicationContextElement.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWApplicationProtocolDefinition.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWApplicationProtocolDefinition.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWApproval.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWApproval.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWApprovalDateTime.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWApprovalDateTime.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWApprovalPersonOrganization.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWApprovalPersonOrganization.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWApprovalRelationship.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWApprovalRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWApprovalRole.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWApprovalRole.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWApprovalStatus.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWApprovalStatus.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWCalendarDate.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWCalendarDate.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWCertification.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWCertification.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWCertificationAssignment.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWCertificationAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWCertificationType.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWCertificationType.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWCharacterizedObject.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWCharacterizedObject.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWContract.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWContract.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWContractAssignment.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWContractAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWContractType.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWContractType.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWConversionBasedUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWConversionBasedUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWConversionBasedUnitAndAreaUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWConversionBasedUnitAndAreaUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWConversionBasedUnitAndLengthUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWConversionBasedUnitAndLengthUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWConversionBasedUnitAndMassUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWConversionBasedUnitAndMassUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWConversionBasedUnitAndPlaneAngleUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWConversionBasedUnitAndPlaneAngleUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWConversionBasedUnitAndRatioUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWConversionBasedUnitAndRatioUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWConversionBasedUnitAndSolidAngleUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWConversionBasedUnitAndSolidAngleUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWConversionBasedUnitAndTimeUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWConversionBasedUnitAndTimeUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWConversionBasedUnitAndVolumeUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWConversionBasedUnitAndVolumeUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWCoordinatedUniversalTimeOffset.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWCoordinatedUniversalTimeOffset.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWDate.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWDate.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWDateAndTime.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWDateAndTime.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWDateRole.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWDateRole.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWDateTimeRole.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWDateTimeRole.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWDerivedUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWDerivedUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWDerivedUnitElement.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWDerivedUnitElement.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWDimensionalExponents.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWDimensionalExponents.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWDocument.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWDocument.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWDocumentFile.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWDocumentFile.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWDocumentProductAssociation.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWDocumentProductAssociation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWDocumentProductEquivalence.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWDocumentProductEquivalence.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWDocumentRelationship.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWDocumentRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWDocumentRepresentationType.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWDocumentRepresentationType.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWDocumentType.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWDocumentType.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWDocumentUsageConstraint.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWDocumentUsageConstraint.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWEffectivity.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWEffectivity.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWEffectivityAssignment.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWEffectivityAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWEulerAngles.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWEulerAngles.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWExternalIdentificationAssignment.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWExternalIdentificationAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWExternalSource.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWExternalSource.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWExternallyDefinedItem.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWExternallyDefinedItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWGeneralProperty.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWGeneralProperty.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWGroup.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWGroup.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWGroupAssignment.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWGroupAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWGroupRelationship.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWGroupRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWIdentificationAssignment.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWIdentificationAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWIdentificationRole.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWIdentificationRole.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWLengthMeasureWithUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWLengthMeasureWithUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWLengthUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWLengthUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWLocalTime.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWLocalTime.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWMassMeasureWithUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWMassMeasureWithUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWMassUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWMassUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWMeasureWithUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWMeasureWithUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWMechanicalContext.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWMechanicalContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWNameAssignment.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWNameAssignment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWNamedUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWNamedUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWObjectRole.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWObjectRole.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWOrdinalDate.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWOrdinalDate.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWOrganization.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWOrganization.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWOrganizationRole.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWOrganizationRole.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWOrganizationalAddress.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWOrganizationalAddress.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWPerson.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWPerson.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWPersonAndOrganization.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWPersonAndOrganization.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWPersonAndOrganizationRole.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWPersonAndOrganizationRole.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWPersonalAddress.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWPersonalAddress.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWPlaneAngleMeasureWithUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWPlaneAngleMeasureWithUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWPlaneAngleUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWPlaneAngleUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWProduct.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWProduct.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWProductCategory.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWProductCategory.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWProductCategoryRelationship.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWProductCategoryRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWProductConceptContext.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWProductConceptContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWProductContext.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWProductContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWProductDefinition.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWProductDefinition.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWProductDefinitionContext.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWProductDefinitionContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWProductDefinitionEffectivity.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWProductDefinitionEffectivity.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWProductDefinitionFormation.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWProductDefinitionFormation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWProductDefinitionFormationRelationship.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWProductDefinitionFormationRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWProductDefinitionFormationWithSpecifiedSource.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWProductDefinitionFormationWithSpecifiedSource.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWProductDefinitionRelationship.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWProductDefinitionRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWProductDefinitionWithAssociatedDocuments.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWProductDefinitionWithAssociatedDocuments.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWProductRelatedProductCategory.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWProductRelatedProductCategory.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWProductType.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWProductType.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWRatioMeasureWithUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWRatioMeasureWithUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWRoleAssociation.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWRoleAssociation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWSecurityClassification.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWSecurityClassification.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWSecurityClassificationLevel.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWSecurityClassificationLevel.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnitAndAreaUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnitAndAreaUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnitAndLengthUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnitAndLengthUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnitAndMassUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnitAndMassUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnitAndPlaneAngleUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnitAndPlaneAngleUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnitAndRatioUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnitAndRatioUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnitAndSolidAngleUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnitAndSolidAngleUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnitAndThermodynamicTemperatureUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnitAndThermodynamicTemperatureUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnitAndTimeUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnitAndTimeUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnitAndVolumeUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWSiUnitAndVolumeUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWSolidAngleMeasureWithUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWSolidAngleMeasureWithUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWSolidAngleUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWSolidAngleUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWThermodynamicTemperatureUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWThermodynamicTemperatureUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWUncertaintyMeasureWithUnit.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWUncertaintyMeasureWithUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWVersionedActionRequest.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWVersionedActionRequest.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepBasic/RWStepBasic_RWWeekOfYearAndDayDate.cxx" )
  SOURCE_GROUP (RWStepBasic FILES "../../../src/RWStepBasic/RWStepBasic_RWWeekOfYearAndDayDate.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepRepr/StepRepr_Array1OfMaterialPropertyRepresentation_0.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../drv/StepRepr/StepRepr_Array1OfMaterialPropertyRepresentation_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepRepr/StepRepr_Array1OfPropertyDefinitionRepresentation_0.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../drv/StepRepr/StepRepr_Array1OfPropertyDefinitionRepresentation_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepRepr/StepRepr_Array1OfRepresentationItem_0.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../drv/StepRepr/StepRepr_Array1OfRepresentationItem_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepRepr/StepRepr_HArray1OfMaterialPropertyRepresentation_0.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../drv/StepRepr/StepRepr_HArray1OfMaterialPropertyRepresentation_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepRepr/StepRepr_HArray1OfPropertyDefinitionRepresentation_0.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../drv/StepRepr/StepRepr_HArray1OfPropertyDefinitionRepresentation_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepRepr/StepRepr_HArray1OfRepresentationItem_0.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../drv/StepRepr/StepRepr_HArray1OfRepresentationItem_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepRepr/StepRepr_HSequenceOfMaterialPropertyRepresentation_0.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../drv/StepRepr/StepRepr_HSequenceOfMaterialPropertyRepresentation_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepRepr/StepRepr_HSequenceOfRepresentationItem_0.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../drv/StepRepr/StepRepr_HSequenceOfRepresentationItem_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepRepr/StepRepr_SequenceNodeOfSequenceOfMaterialPropertyRepresentation_0.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../drv/StepRepr/StepRepr_SequenceNodeOfSequenceOfMaterialPropertyRepresentation_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepRepr/StepRepr_SequenceNodeOfSequenceOfRepresentationItem_0.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../drv/StepRepr/StepRepr_SequenceNodeOfSequenceOfRepresentationItem_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepRepr/StepRepr_SequenceOfMaterialPropertyRepresentation_0.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../drv/StepRepr/StepRepr_SequenceOfMaterialPropertyRepresentation_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepRepr/StepRepr_SequenceOfRepresentationItem_0.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../drv/StepRepr/StepRepr_SequenceOfRepresentationItem_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_AssemblyComponentUsage.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_AssemblyComponentUsage.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_AssemblyComponentUsageSubstitute.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_AssemblyComponentUsageSubstitute.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_CharacterizedDefinition.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_CharacterizedDefinition.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_CompositeShapeAspect.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_CompositeShapeAspect.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_CompoundRepresentationItem.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_CompoundRepresentationItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ConfigurationDesign.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ConfigurationDesign.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ConfigurationDesignItem.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ConfigurationDesignItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ConfigurationEffectivity.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ConfigurationEffectivity.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ConfigurationItem.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ConfigurationItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_DataEnvironment.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_DataEnvironment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_DefinitionalRepresentation.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_DefinitionalRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_DerivedShapeAspect.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_DerivedShapeAspect.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_DescriptiveRepresentationItem.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_DescriptiveRepresentationItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_Extension.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_Extension.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ExternallyDefinedRepresentation.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ExternallyDefinedRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_FunctionallyDefinedTransformation.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_FunctionallyDefinedTransformation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_GlobalUncertaintyAssignedContext.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_GlobalUncertaintyAssignedContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_GlobalUnitAssignedContext.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_GlobalUnitAssignedContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ItemDefinedTransformation.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ItemDefinedTransformation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_MakeFromUsageOption.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_MakeFromUsageOption.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_MappedItem.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_MappedItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_MaterialDesignation.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_MaterialDesignation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_MaterialProperty.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_MaterialProperty.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_MaterialPropertyRepresentation.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_MaterialPropertyRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_MeasureRepresentationItem.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_MeasureRepresentationItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_NextAssemblyUsageOccurrence.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_NextAssemblyUsageOccurrence.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ParametricRepresentationContext.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ParametricRepresentationContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ProductConcept.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ProductConcept.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ProductDefinitionShape.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ProductDefinitionShape.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ProductDefinitionUsage.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ProductDefinitionUsage.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_PromissoryUsageOccurrence.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_PromissoryUsageOccurrence.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_PropertyDefinition.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_PropertyDefinition.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_PropertyDefinitionRelationship.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_PropertyDefinitionRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_PropertyDefinitionRepresentation.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_PropertyDefinitionRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_QuantifiedAssemblyComponentUsage.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_QuantifiedAssemblyComponentUsage.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ReprItemAndLengthMeasureWithUnit.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ReprItemAndLengthMeasureWithUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_Representation.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_Representation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_RepresentationContext.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_RepresentationContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_RepresentationItem.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_RepresentationItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_RepresentationMap.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_RepresentationMap.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_RepresentationRelationship.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_RepresentationRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_RepresentationRelationshipWithTransformation.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_RepresentationRelationshipWithTransformation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_RepresentedDefinition.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_RepresentedDefinition.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ShapeAspect.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ShapeAspect.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ShapeAspectDerivingRelationship.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ShapeAspectDerivingRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ShapeAspectRelationship.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ShapeAspectRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ShapeAspectTransition.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ShapeAspectTransition.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ShapeDefinition.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ShapeDefinition.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ShapeRepresentationRelationship.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ShapeRepresentationRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ShapeRepresentationRelationshipWithTransformation.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ShapeRepresentationRelationshipWithTransformation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_SpecifiedHigherUsageOccurrence.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_SpecifiedHigherUsageOccurrence.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_StructuralResponseProperty.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_StructuralResponseProperty.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_StructuralResponsePropertyDefinitionRepresentation.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_StructuralResponsePropertyDefinitionRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_SuppliedPartRelationship.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_SuppliedPartRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_Transformation.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_Transformation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepRepr/StepRepr_ValueRange.cxx" )
  SOURCE_GROUP (StepRepr FILES "../../../src/StepRepr/StepRepr_ValueRange.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWAssemblyComponentUsage.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWAssemblyComponentUsage.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWAssemblyComponentUsageSubstitute.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWAssemblyComponentUsageSubstitute.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWCompositeShapeAspect.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWCompositeShapeAspect.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWCompoundRepresentationItem.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWCompoundRepresentationItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWConfigurationDesign.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWConfigurationDesign.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWConfigurationEffectivity.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWConfigurationEffectivity.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWConfigurationItem.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWConfigurationItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWDataEnvironment.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWDataEnvironment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWDefinitionalRepresentation.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWDefinitionalRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWDerivedShapeAspect.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWDerivedShapeAspect.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWDescriptiveRepresentationItem.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWDescriptiveRepresentationItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWExtension.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWExtension.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWFunctionallyDefinedTransformation.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWFunctionallyDefinedTransformation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWGlobalUncertaintyAssignedContext.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWGlobalUncertaintyAssignedContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWGlobalUnitAssignedContext.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWGlobalUnitAssignedContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWItemDefinedTransformation.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWItemDefinedTransformation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWMakeFromUsageOption.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWMakeFromUsageOption.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWMappedItem.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWMappedItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWMaterialDesignation.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWMaterialDesignation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWMaterialProperty.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWMaterialProperty.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWMaterialPropertyRepresentation.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWMaterialPropertyRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWMeasureRepresentationItem.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWMeasureRepresentationItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWParametricRepresentationContext.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWParametricRepresentationContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWProductConcept.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWProductConcept.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWProductDefinitionShape.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWProductDefinitionShape.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWPropertyDefinition.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWPropertyDefinition.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWPropertyDefinitionRelationship.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWPropertyDefinitionRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWPropertyDefinitionRepresentation.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWPropertyDefinitionRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWQuantifiedAssemblyComponentUsage.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWQuantifiedAssemblyComponentUsage.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWReprItemAndLengthMeasureWithUnit.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWReprItemAndLengthMeasureWithUnit.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWRepresentation.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWRepresentationContext.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWRepresentationContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWRepresentationItem.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWRepresentationItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWRepresentationMap.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWRepresentationMap.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWRepresentationRelationship.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWRepresentationRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWRepresentationRelationshipWithTransformation.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWRepresentationRelationshipWithTransformation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWShapeAspect.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWShapeAspect.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWShapeAspectDerivingRelationship.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWShapeAspectDerivingRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWShapeAspectRelationship.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWShapeAspectRelationship.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWShapeAspectTransition.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWShapeAspectTransition.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWShapeRepresentationRelationshipWithTransformation.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWShapeRepresentationRelationshipWithTransformation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWSpecifiedHigherUsageOccurrence.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWSpecifiedHigherUsageOccurrence.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWStructuralResponseProperty.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWStructuralResponseProperty.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepRepr/RWStepRepr_RWStructuralResponsePropertyDefinitionRepresentation.cxx" )
  SOURCE_GROUP (RWStepRepr FILES "../../../src/RWStepRepr/RWStepRepr_RWStructuralResponsePropertyDefinitionRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepGeom/StepGeom_Array1OfBoundaryCurve_0.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../drv/StepGeom/StepGeom_Array1OfBoundaryCurve_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepGeom/StepGeom_Array1OfCartesianPoint_0.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../drv/StepGeom/StepGeom_Array1OfCartesianPoint_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepGeom/StepGeom_Array1OfCompositeCurveSegment_0.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../drv/StepGeom/StepGeom_Array1OfCompositeCurveSegment_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepGeom/StepGeom_Array1OfCurve_0.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../drv/StepGeom/StepGeom_Array1OfCurve_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepGeom/StepGeom_Array1OfPcurveOrSurface_0.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../drv/StepGeom/StepGeom_Array1OfPcurveOrSurface_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepGeom/StepGeom_Array1OfSurfaceBoundary_0.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../drv/StepGeom/StepGeom_Array1OfSurfaceBoundary_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepGeom/StepGeom_Array1OfTrimmingSelect_0.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../drv/StepGeom/StepGeom_Array1OfTrimmingSelect_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepGeom/StepGeom_Array2OfCartesianPoint_0.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../drv/StepGeom/StepGeom_Array2OfCartesianPoint_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepGeom/StepGeom_Array2OfSurfacePatch_0.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../drv/StepGeom/StepGeom_Array2OfSurfacePatch_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepGeom/StepGeom_HArray1OfBoundaryCurve_0.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../drv/StepGeom/StepGeom_HArray1OfBoundaryCurve_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepGeom/StepGeom_HArray1OfCartesianPoint_0.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../drv/StepGeom/StepGeom_HArray1OfCartesianPoint_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepGeom/StepGeom_HArray1OfCompositeCurveSegment_0.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../drv/StepGeom/StepGeom_HArray1OfCompositeCurveSegment_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepGeom/StepGeom_HArray1OfCurve_0.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../drv/StepGeom/StepGeom_HArray1OfCurve_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepGeom/StepGeom_HArray1OfPcurveOrSurface_0.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../drv/StepGeom/StepGeom_HArray1OfPcurveOrSurface_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepGeom/StepGeom_HArray1OfSurfaceBoundary_0.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../drv/StepGeom/StepGeom_HArray1OfSurfaceBoundary_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepGeom/StepGeom_HArray1OfTrimmingSelect_0.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../drv/StepGeom/StepGeom_HArray1OfTrimmingSelect_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepGeom/StepGeom_HArray2OfCartesianPoint_0.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../drv/StepGeom/StepGeom_HArray2OfCartesianPoint_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepGeom/StepGeom_HArray2OfSurfacePatch_0.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../drv/StepGeom/StepGeom_HArray2OfSurfacePatch_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Axis1Placement.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Axis1Placement.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Axis2Placement.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Axis2Placement.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Axis2Placement2d.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Axis2Placement2d.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Axis2Placement3d.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Axis2Placement3d.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_BSplineCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_BSplineCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_BSplineCurveWithKnots.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_BSplineCurveWithKnots.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_BSplineSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_BSplineSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_BSplineSurfaceWithKnots.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_BSplineSurfaceWithKnots.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_BezierCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_BezierCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_BezierCurveAndRationalBSplineCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_BezierCurveAndRationalBSplineCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_BezierSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_BezierSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_BezierSurfaceAndRationalBSplineSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_BezierSurfaceAndRationalBSplineSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_BoundaryCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_BoundaryCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_BoundedCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_BoundedCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_BoundedSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_BoundedSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_CartesianPoint.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_CartesianPoint.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_CartesianTransformationOperator.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_CartesianTransformationOperator.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_CartesianTransformationOperator2d.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_CartesianTransformationOperator2d.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_CartesianTransformationOperator3d.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_CartesianTransformationOperator3d.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Circle.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Circle.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_CompositeCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_CompositeCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_CompositeCurveOnSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_CompositeCurveOnSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_CompositeCurveSegment.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_CompositeCurveSegment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Conic.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Conic.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_ConicalSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_ConicalSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Curve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Curve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_CurveBoundedSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_CurveBoundedSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_CurveOnSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_CurveOnSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_CurveReplica.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_CurveReplica.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_CylindricalSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_CylindricalSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_DegeneratePcurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_DegeneratePcurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_DegenerateToroidalSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_DegenerateToroidalSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Direction.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Direction.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_ElementarySurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_ElementarySurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Ellipse.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Ellipse.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_EvaluatedDegeneratePcurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_EvaluatedDegeneratePcurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_GeometricRepresentationContext.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_GeometricRepresentationContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_GeometricRepresentationContextAndParametricRepresentationContext.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_GeometricRepresentationContextAndParametricRepresentationContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_GeometricRepresentationItem.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_GeometricRepresentationItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Hyperbola.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Hyperbola.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_IntersectionCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_IntersectionCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Line.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Line.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_OffsetCurve3d.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_OffsetCurve3d.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_OffsetSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_OffsetSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_OrientedSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_OrientedSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_OuterBoundaryCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_OuterBoundaryCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Parabola.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Parabola.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Pcurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Pcurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_PcurveOrSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_PcurveOrSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Placement.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Placement.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Plane.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Plane.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Point.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Point.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_PointOnCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_PointOnCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_PointOnSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_PointOnSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_PointReplica.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_PointReplica.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Polyline.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Polyline.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_QuasiUniformCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_QuasiUniformCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_QuasiUniformCurveAndRationalBSplineCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_QuasiUniformCurveAndRationalBSplineCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_QuasiUniformSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_QuasiUniformSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_QuasiUniformSurfaceAndRationalBSplineSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_RationalBSplineCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_RationalBSplineCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_RationalBSplineSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_RationalBSplineSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_RectangularCompositeSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_RectangularCompositeSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_RectangularTrimmedSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_RectangularTrimmedSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_ReparametrisedCompositeCurveSegment.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_ReparametrisedCompositeCurveSegment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_SeamCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_SeamCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_SphericalSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_SphericalSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Surface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Surface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_SurfaceBoundary.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_SurfaceBoundary.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_SurfaceCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_SurfaceCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_SurfaceCurveAndBoundedCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_SurfaceCurveAndBoundedCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_SurfaceOfLinearExtrusion.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_SurfaceOfLinearExtrusion.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_SurfaceOfRevolution.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_SurfaceOfRevolution.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_SurfacePatch.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_SurfacePatch.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_SurfaceReplica.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_SurfaceReplica.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_SweptSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_SweptSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_ToroidalSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_ToroidalSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_TrimmedCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_TrimmedCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_TrimmingMember.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_TrimmingMember.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_TrimmingSelect.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_TrimmingSelect.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_UniformCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_UniformCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_UniformCurveAndRationalBSplineCurve.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_UniformCurveAndRationalBSplineCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_UniformSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_UniformSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_UniformSurfaceAndRationalBSplineSurface.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_UniformSurfaceAndRationalBSplineSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_Vector.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_Vector.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepGeom/StepGeom_VectorOrDirection.cxx" )
  SOURCE_GROUP (StepGeom FILES "../../../src/StepGeom/StepGeom_VectorOrDirection.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWAxis1Placement.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWAxis1Placement.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWAxis2Placement2d.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWAxis2Placement2d.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWAxis2Placement3d.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWAxis2Placement3d.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWBSplineCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWBSplineCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWBSplineCurveWithKnots.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWBSplineCurveWithKnots.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWBSplineCurveWithKnotsAndRationalBSplineCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWBSplineSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWBSplineSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWBSplineSurfaceWithKnots.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWBSplineSurfaceWithKnots.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWBSplineSurfaceWithKnotsAndRationalBSplineSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWBezierCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWBezierCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWBezierCurveAndRationalBSplineCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWBezierCurveAndRationalBSplineCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWBezierSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWBezierSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWBezierSurfaceAndRationalBSplineSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWBoundaryCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWBoundaryCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWBoundedCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWBoundedCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWBoundedSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWBoundedSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWCartesianPoint.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWCartesianPoint.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWCartesianTransformationOperator.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWCartesianTransformationOperator.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWCartesianTransformationOperator3d.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWCartesianTransformationOperator3d.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWCircle.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWCircle.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWCompositeCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWCompositeCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWCompositeCurveOnSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWCompositeCurveOnSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWCompositeCurveSegment.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWCompositeCurveSegment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWConic.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWConic.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWConicalSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWConicalSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWCurveBoundedSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWCurveBoundedSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWCurveReplica.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWCurveReplica.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWCylindricalSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWCylindricalSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWDegeneratePcurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWDegeneratePcurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWDegenerateToroidalSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWDegenerateToroidalSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWDirection.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWDirection.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWElementarySurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWElementarySurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWEllipse.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWEllipse.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWEvaluatedDegeneratePcurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWEvaluatedDegeneratePcurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWGeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWGeometricRepresentationContext.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWGeometricRepresentationContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWGeometricRepresentationContextAndGlobalUnitAssignedContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWGeometricRepresentationContextAndParametricRepresentationContext.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWGeometricRepresentationItem.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWGeometricRepresentationItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWHyperbola.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWHyperbola.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWIntersectionCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWIntersectionCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWLine.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWLine.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWOffsetCurve3d.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWOffsetCurve3d.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWOffsetSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWOffsetSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWOrientedSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWOrientedSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWOuterBoundaryCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWOuterBoundaryCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWParabola.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWParabola.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWPcurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWPcurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWPlacement.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWPlacement.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWPlane.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWPlane.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWPoint.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWPoint.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWPointOnCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWPointOnCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWPointOnSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWPointOnSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWPointReplica.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWPointReplica.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWPolyline.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWPolyline.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWQuasiUniformCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWQuasiUniformCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWQuasiUniformCurveAndRationalBSplineCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWQuasiUniformSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWQuasiUniformSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWQuasiUniformSurfaceAndRationalBSplineSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWRationalBSplineCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWRationalBSplineCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWRationalBSplineSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWRationalBSplineSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWRectangularCompositeSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWRectangularCompositeSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWRectangularTrimmedSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWRectangularTrimmedSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWReparametrisedCompositeCurveSegment.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWReparametrisedCompositeCurveSegment.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWSeamCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWSeamCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWSphericalSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWSphericalSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWSurfaceCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWSurfaceCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWSurfaceCurveAndBoundedCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWSurfaceCurveAndBoundedCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWSurfaceOfLinearExtrusion.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWSurfaceOfLinearExtrusion.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWSurfaceOfRevolution.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWSurfaceOfRevolution.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWSurfacePatch.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWSurfacePatch.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWSurfaceReplica.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWSurfaceReplica.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWSweptSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWSweptSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWToroidalSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWToroidalSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWTrimmedCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWTrimmedCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWUniformCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWUniformCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWUniformCurveAndRationalBSplineCurve.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWUniformCurveAndRationalBSplineCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWUniformSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWUniformSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWUniformSurfaceAndRationalBSplineSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepGeom/RWStepGeom_RWVector.cxx" )
  SOURCE_GROUP (RWStepGeom FILES "../../../src/RWStepGeom/RWStepGeom_RWVector.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_Array1OfConnectedEdgeSet_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_Array1OfConnectedEdgeSet_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_Array1OfConnectedFaceSet_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_Array1OfConnectedFaceSet_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_Array1OfEdge_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_Array1OfEdge_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_Array1OfFaceBound_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_Array1OfFaceBound_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_Array1OfFace_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_Array1OfFace_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_Array1OfGeometricSetSelect_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_Array1OfGeometricSetSelect_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_Array1OfOrientedClosedShell_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_Array1OfOrientedClosedShell_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_Array1OfOrientedEdge_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_Array1OfOrientedEdge_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_Array1OfShell_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_Array1OfShell_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_Array1OfValueQualifier_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_Array1OfValueQualifier_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_HArray1OfConnectedEdgeSet_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_HArray1OfConnectedEdgeSet_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_HArray1OfConnectedFaceSet_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_HArray1OfConnectedFaceSet_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_HArray1OfEdge_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_HArray1OfEdge_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_HArray1OfFaceBound_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_HArray1OfFaceBound_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_HArray1OfFace_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_HArray1OfFace_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_HArray1OfGeometricSetSelect_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_HArray1OfGeometricSetSelect_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_HArray1OfOrientedClosedShell_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_HArray1OfOrientedClosedShell_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_HArray1OfOrientedEdge_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_HArray1OfOrientedEdge_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_HArray1OfShell_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_HArray1OfShell_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../drv/StepShape/StepShape_HArray1OfValueQualifier_0.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../drv/StepShape/StepShape_HArray1OfValueQualifier_0.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_AdvancedBrepShapeRepresentation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_AdvancedBrepShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_AdvancedFace.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_AdvancedFace.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_AngularLocation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_AngularLocation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_AngularSize.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_AngularSize.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_Block.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_Block.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_BooleanOperand.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_BooleanOperand.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_BooleanResult.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_BooleanResult.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_BoxDomain.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_BoxDomain.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_BoxedHalfSpace.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_BoxedHalfSpace.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_BrepWithVoids.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_BrepWithVoids.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ClosedShell.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ClosedShell.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_CompoundShapeRepresentation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_CompoundShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ConnectedEdgeSet.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ConnectedEdgeSet.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ConnectedFaceSet.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ConnectedFaceSet.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ConnectedFaceShapeRepresentation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ConnectedFaceShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ConnectedFaceSubSet.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ConnectedFaceSubSet.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ContextDependentShapeRepresentation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ContextDependentShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_CsgPrimitive.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_CsgPrimitive.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_CsgSelect.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_CsgSelect.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_CsgShapeRepresentation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_CsgShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_CsgSolid.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_CsgSolid.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_DefinitionalRepresentationAndShapeRepresentation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_DefinitionalRepresentationAndShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_DimensionalCharacteristic.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_DimensionalCharacteristic.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_DimensionalCharacteristicRepresentation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_DimensionalCharacteristicRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_DimensionalLocation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_DimensionalLocation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_DimensionalLocationWithPath.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_DimensionalLocationWithPath.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_DimensionalSize.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_DimensionalSize.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_DimensionalSizeWithPath.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_DimensionalSizeWithPath.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_DirectedDimensionalLocation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_DirectedDimensionalLocation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_Edge.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_Edge.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_EdgeBasedWireframeModel.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_EdgeBasedWireframeModel.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_EdgeBasedWireframeShapeRepresentation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_EdgeBasedWireframeShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_EdgeCurve.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_EdgeCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_EdgeLoop.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_EdgeLoop.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ExtrudedAreaSolid.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ExtrudedAreaSolid.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ExtrudedFaceSolid.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ExtrudedFaceSolid.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_Face.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_Face.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_FaceBasedSurfaceModel.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_FaceBasedSurfaceModel.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_FaceBound.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_FaceBound.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_FaceOuterBound.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_FaceOuterBound.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_FaceSurface.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_FaceSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_FacetedBrep.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_FacetedBrep.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_FacetedBrepAndBrepWithVoids.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_FacetedBrepAndBrepWithVoids.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_FacetedBrepShapeRepresentation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_FacetedBrepShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_GeometricCurveSet.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_GeometricCurveSet.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_GeometricSet.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_GeometricSet.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_GeometricSetSelect.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_GeometricSetSelect.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_GeometricallyBoundedSurfaceShapeRepresentation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_GeometricallyBoundedSurfaceShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_GeometricallyBoundedWireframeShapeRepresentation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_GeometricallyBoundedWireframeShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_HalfSpaceSolid.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_HalfSpaceSolid.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_LimitsAndFits.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_LimitsAndFits.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_Loop.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_Loop.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_LoopAndPath.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_LoopAndPath.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ManifoldSolidBrep.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ManifoldSolidBrep.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ManifoldSurfaceShapeRepresentation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ManifoldSurfaceShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_MeasureQualification.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_MeasureQualification.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_MeasureRepresentationItemAndQualifiedRepresentationItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_NonManifoldSurfaceShapeRepresentation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_NonManifoldSurfaceShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_OpenShell.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_OpenShell.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_OrientedClosedShell.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_OrientedClosedShell.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_OrientedEdge.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_OrientedEdge.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_OrientedFace.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_OrientedFace.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_OrientedOpenShell.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_OrientedOpenShell.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_OrientedPath.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_OrientedPath.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_Path.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_Path.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_PlusMinusTolerance.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_PlusMinusTolerance.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_PointRepresentation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_PointRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_PolyLoop.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_PolyLoop.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_PrecisionQualifier.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_PrecisionQualifier.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_QualifiedRepresentationItem.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_QualifiedRepresentationItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ReversibleTopologyItem.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ReversibleTopologyItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_RevolvedAreaSolid.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_RevolvedAreaSolid.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_RevolvedFaceSolid.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_RevolvedFaceSolid.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_RightAngularWedge.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_RightAngularWedge.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_RightCircularCone.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_RightCircularCone.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_RightCircularCylinder.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_RightCircularCylinder.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_SeamEdge.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_SeamEdge.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ShapeDefinitionRepresentation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ShapeDefinitionRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ShapeDimensionRepresentation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ShapeDimensionRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ShapeRepresentation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ShapeRepresentationWithParameters.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ShapeRepresentationWithParameters.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_Shell.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_Shell.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ShellBasedSurfaceModel.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ShellBasedSurfaceModel.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_SolidModel.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_SolidModel.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_SolidReplica.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_SolidReplica.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_Sphere.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_Sphere.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_Subedge.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_Subedge.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_Subface.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_Subface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_SurfaceModel.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_SurfaceModel.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_SweptAreaSolid.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_SweptAreaSolid.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_SweptFaceSolid.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_SweptFaceSolid.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ToleranceMethodDefinition.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ToleranceMethodDefinition.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ToleranceValue.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ToleranceValue.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_TopologicalRepresentationItem.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_TopologicalRepresentationItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_Torus.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_Torus.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_TransitionalShapeRepresentation.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_TransitionalShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_TypeQualifier.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_TypeQualifier.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_ValueQualifier.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_ValueQualifier.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_Vertex.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_Vertex.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_VertexLoop.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_VertexLoop.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/StepShape/StepShape_VertexPoint.cxx" )
  SOURCE_GROUP (StepShape FILES "../../../src/StepShape/StepShape_VertexPoint.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWAdvancedBrepShapeRepresentation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWAdvancedBrepShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWAdvancedFace.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWAdvancedFace.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWAngularLocation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWAngularLocation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWAngularSize.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWAngularSize.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWBlock.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWBlock.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWBooleanResult.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWBooleanResult.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWBoxDomain.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWBoxDomain.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWBoxedHalfSpace.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWBoxedHalfSpace.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWBrepWithVoids.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWBrepWithVoids.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWClosedShell.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWClosedShell.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWCompoundShapeRepresentation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWCompoundShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWConnectedEdgeSet.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWConnectedEdgeSet.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWConnectedFaceSet.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWConnectedFaceSet.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWConnectedFaceShapeRepresentation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWConnectedFaceShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWConnectedFaceSubSet.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWConnectedFaceSubSet.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWContextDependentShapeRepresentation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWContextDependentShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWCsgShapeRepresentation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWCsgShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWCsgSolid.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWCsgSolid.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWDefinitionalRepresentationAndShapeRepresentation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWDefinitionalRepresentationAndShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWDimensionalCharacteristicRepresentation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWDimensionalCharacteristicRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWDimensionalLocation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWDimensionalLocation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWDimensionalLocationWithPath.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWDimensionalLocationWithPath.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWDimensionalSize.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWDimensionalSize.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWDimensionalSizeWithPath.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWDimensionalSizeWithPath.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWEdge.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWEdge.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWEdgeBasedWireframeModel.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWEdgeBasedWireframeModel.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWEdgeBasedWireframeShapeRepresentation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWEdgeBasedWireframeShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWEdgeCurve.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWEdgeCurve.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWEdgeLoop.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWEdgeLoop.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWExtrudedAreaSolid.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWExtrudedAreaSolid.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWExtrudedFaceSolid.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWExtrudedFaceSolid.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWFace.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWFace.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWFaceBasedSurfaceModel.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWFaceBasedSurfaceModel.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWFaceBound.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWFaceBound.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWFaceOuterBound.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWFaceOuterBound.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWFaceSurface.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWFaceSurface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWFacetedBrep.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWFacetedBrep.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWFacetedBrepAndBrepWithVoids.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWFacetedBrepAndBrepWithVoids.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWFacetedBrepShapeRepresentation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWFacetedBrepShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWGeometricCurveSet.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWGeometricCurveSet.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWGeometricSet.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWGeometricSet.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWGeometricallyBoundedSurfaceShapeRepresentation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWGeometricallyBoundedSurfaceShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWGeometricallyBoundedWireframeShapeRepresentation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWGeometricallyBoundedWireframeShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWHalfSpaceSolid.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWHalfSpaceSolid.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWLimitsAndFits.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWLimitsAndFits.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWLoop.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWLoop.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWLoopAndPath.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWLoopAndPath.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWManifoldSolidBrep.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWManifoldSolidBrep.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWManifoldSurfaceShapeRepresentation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWManifoldSurfaceShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWMeasureQualification.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWMeasureQualification.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWMeasureRepresentationItemAndQualifiedRepresentationItem.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWMeasureRepresentationItemAndQualifiedRepresentationItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWNonManifoldSurfaceShapeRepresentation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWNonManifoldSurfaceShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWOpenShell.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWOpenShell.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWOrientedClosedShell.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWOrientedClosedShell.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWOrientedEdge.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWOrientedEdge.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWOrientedFace.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWOrientedFace.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWOrientedOpenShell.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWOrientedOpenShell.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWOrientedPath.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWOrientedPath.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWPath.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWPath.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWPlusMinusTolerance.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWPlusMinusTolerance.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWPointRepresentation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWPointRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWPolyLoop.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWPolyLoop.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWPrecisionQualifier.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWPrecisionQualifier.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWQualifiedRepresentationItem.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWQualifiedRepresentationItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWRevolvedAreaSolid.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWRevolvedAreaSolid.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWRevolvedFaceSolid.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWRevolvedFaceSolid.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWRightAngularWedge.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWRightAngularWedge.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWRightCircularCone.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWRightCircularCone.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWRightCircularCylinder.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWRightCircularCylinder.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWSeamEdge.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWSeamEdge.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWShapeDefinitionRepresentation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWShapeDefinitionRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWShapeDefinitionRepresentation_1.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWShapeDefinitionRepresentation_1.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWShapeDimensionRepresentation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWShapeDimensionRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWShapeRepresentation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWShapeRepresentationWithParameters.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWShapeRepresentationWithParameters.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWShellBasedSurfaceModel.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWShellBasedSurfaceModel.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWSolidModel.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWSolidModel.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWSolidReplica.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWSolidReplica.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWSphere.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWSphere.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWSubedge.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWSubedge.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWSubface.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWSubface.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWSweptAreaSolid.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWSweptAreaSolid.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWSweptFaceSolid.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWSweptFaceSolid.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWToleranceValue.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWToleranceValue.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWTopologicalRepresentationItem.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWTopologicalRepresentationItem.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWTorus.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWTorus.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWTransitionalShapeRepresentation.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWTransitionalShapeRepresentation.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWTypeQualifier.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWTypeQualifier.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWVertex.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWVertex.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWVertexLoop.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWVertexLoop.cxx")

  list( APPEND TKSTEPBase_USED_SRCFILES "../../../src/RWStepShape/RWStepShape_RWVertexPoint.cxx" )
  SOURCE_GROUP (RWStepShape FILES "../../../src/RWStepShape/RWStepShape_RWVertexPoint.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKSTEPBase)
 add_library( TKSTEPBase SHARED ${TKSTEPBase_USED_SRCFILES} )

 set_property(TARGET TKSTEPBase PROPERTY FOLDER DataExchange)

 install( TARGETS TKSTEPBase
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKSTEPBase.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKSTEPBase PROPERTIES COMPILE_FLAGS "${TKSTEPBase_PRECOMPILED_DEFS}" )
 include_directories( ${TKSTEPBase_COMPILER_DIRECTORIES} )
 target_link_libraries( TKSTEPBase ${TKSTEPBase_USED_LIBS} )
endif()
