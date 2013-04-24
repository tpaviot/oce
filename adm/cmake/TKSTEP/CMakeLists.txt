project(TKSTEP)

if (WIN32)
  list( APPEND TKSTEP_PRECOMPILED_DEFS "-D__StepAP214_DLL" )
  list( APPEND TKSTEP_PRECOMPILED_DEFS "-D__RWStepAP214_DLL" )
  list( APPEND TKSTEP_PRECOMPILED_DEFS "-D__StepAP203_DLL" )
  list( APPEND TKSTEP_PRECOMPILED_DEFS "-D__RWStepAP203_DLL" )
  list( APPEND TKSTEP_PRECOMPILED_DEFS "-D__STEPConstruct_DLL" )
  list( APPEND TKSTEP_PRECOMPILED_DEFS "-D__STEPEdit_DLL" )
  list( APPEND TKSTEP_PRECOMPILED_DEFS "-D__GeomToStep_DLL" )
  list( APPEND TKSTEP_PRECOMPILED_DEFS "-D__StepToGeom_DLL" )
  list( APPEND TKSTEP_PRECOMPILED_DEFS "-D__StepToTopoDS_DLL" )
  list( APPEND TKSTEP_PRECOMPILED_DEFS "-D__TopoDSToStep_DLL" )
  list( APPEND TKSTEP_PRECOMPILED_DEFS "-D__STEPControl_DLL" )
  list( APPEND TKSTEP_PRECOMPILED_DEFS "-D__STEPSelections_DLL" )
  list( APPEND TKSTEP_PRECOMPILED_DEFS "-D__StepAP209_DLL" )
  string( REGEX REPLACE ";" " " TKSTEP_PRECOMPILED_DEFS "${TKSTEP_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKSTEP_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../drv/StepAP214" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../src/StepAP214" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../drv/RWStepAP214" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../src/RWStepAP214" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../drv/StepAP203" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../src/StepAP203" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../drv/RWStepAP203" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../src/RWStepAP203" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../drv/STEPConstruct" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../src/STEPConstruct" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../drv/STEPEdit" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../src/STEPEdit" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../drv/GeomToStep" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../src/GeomToStep" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../drv/StepToGeom" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../src/StepToGeom" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../drv/StepToTopoDS" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../src/StepToTopoDS" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../drv/TopoDSToStep" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../src/TopoDSToStep" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../drv/STEPControl" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../src/STEPControl" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../drv/STEPSelections" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../src/STEPSelections" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../drv/StepAP209" )
  list( APPEND TKSTEP_COMPILER_DIRECTORIES "../../../src/StepAP209" )

if (WIN32)
else()
endif()

  list( APPEND TKSTEP_USED_LIBS TKernel )
  list( APPEND TKSTEP_USED_LIBS TKSTEPAttr )
  list( APPEND TKSTEP_USED_LIBS TKSTEP209 )
  list( APPEND TKSTEP_USED_LIBS TKSTEPBase )
  list( APPEND TKSTEP_USED_LIBS TKBRep )
  list( APPEND TKSTEP_USED_LIBS TKMath )
  list( APPEND TKSTEP_USED_LIBS TKG2d )
  list( APPEND TKSTEP_USED_LIBS TKShHealing )
  list( APPEND TKSTEP_USED_LIBS TKTopAlgo )
  list( APPEND TKSTEP_USED_LIBS TKG3d )
  list( APPEND TKSTEP_USED_LIBS TKGeomBase )
  list( APPEND TKSTEP_USED_LIBS TKGeomAlgo )
  list( APPEND TKSTEP_USED_LIBS TKXSBase )

if (WIN32)
  list( APPEND TKSTEP_USED_LIBS wsock32.lib )
elseif(APPLE)
else()
endif()

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_Array1OfApprovalItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_Array1OfApprovalItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_Array1OfAutoDesignDateAndPersonItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_Array1OfAutoDesignDateAndPersonItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_Array1OfAutoDesignDateAndTimeItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_Array1OfAutoDesignDateAndTimeItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_Array1OfAutoDesignDatedItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_Array1OfAutoDesignDatedItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_Array1OfAutoDesignGeneralOrgItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_Array1OfAutoDesignGeneralOrgItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_Array1OfAutoDesignGroupedItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_Array1OfAutoDesignGroupedItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_Array1OfAutoDesignPresentedItemSelect_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_Array1OfAutoDesignPresentedItemSelect_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_Array1OfAutoDesignReferencingItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_Array1OfAutoDesignReferencingItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_Array1OfDateAndTimeItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_Array1OfDateAndTimeItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_Array1OfDateItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_Array1OfDateItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_Array1OfDocumentReferenceItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_Array1OfDocumentReferenceItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_Array1OfExternalIdentificationItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_Array1OfExternalIdentificationItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_Array1OfGroupItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_Array1OfGroupItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_Array1OfOrganizationItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_Array1OfOrganizationItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_Array1OfPersonAndOrganizationItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_Array1OfPersonAndOrganizationItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_Array1OfPresentedItemSelect_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_Array1OfPresentedItemSelect_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_Array1OfSecurityClassificationItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_Array1OfSecurityClassificationItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_HArray1OfApprovalItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_HArray1OfApprovalItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_HArray1OfAutoDesignDateAndPersonItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_HArray1OfAutoDesignDateAndPersonItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_HArray1OfAutoDesignDateAndTimeItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_HArray1OfAutoDesignDateAndTimeItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_HArray1OfAutoDesignDatedItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_HArray1OfAutoDesignDatedItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_HArray1OfAutoDesignGeneralOrgItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_HArray1OfAutoDesignGeneralOrgItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_HArray1OfAutoDesignGroupedItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_HArray1OfAutoDesignGroupedItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_HArray1OfAutoDesignPresentedItemSelect_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_HArray1OfAutoDesignPresentedItemSelect_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_HArray1OfAutoDesignReferencingItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_HArray1OfAutoDesignReferencingItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_HArray1OfDateAndTimeItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_HArray1OfDateAndTimeItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_HArray1OfDateItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_HArray1OfDateItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_HArray1OfDocumentReferenceItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_HArray1OfDocumentReferenceItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_HArray1OfExternalIdentificationItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_HArray1OfExternalIdentificationItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_HArray1OfGroupItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_HArray1OfGroupItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_HArray1OfOrganizationItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_HArray1OfOrganizationItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_HArray1OfPersonAndOrganizationItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_HArray1OfPersonAndOrganizationItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_HArray1OfPresentedItemSelect_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_HArray1OfPresentedItemSelect_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP214/StepAP214_HArray1OfSecurityClassificationItem_0.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../drv/StepAP214/StepAP214_HArray1OfSecurityClassificationItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AppliedApprovalAssignment.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AppliedApprovalAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AppliedDateAndTimeAssignment.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AppliedDateAndTimeAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AppliedDateAssignment.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AppliedDateAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AppliedDocumentReference.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AppliedDocumentReference.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AppliedExternalIdentificationAssignment.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AppliedExternalIdentificationAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AppliedGroupAssignment.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AppliedGroupAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AppliedOrganizationAssignment.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AppliedOrganizationAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AppliedPersonAndOrganizationAssignment.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AppliedPersonAndOrganizationAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AppliedPresentedItem.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AppliedPresentedItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AppliedSecurityClassificationAssignment.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AppliedSecurityClassificationAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_ApprovalItem.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_ApprovalItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignActualDateAndTimeAssignment.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignActualDateAndTimeAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignActualDateAssignment.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignActualDateAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignApprovalAssignment.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignApprovalAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignDateAndPersonAssignment.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignDateAndPersonAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignDateAndPersonItem.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignDateAndPersonItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignDateAndTimeItem.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignDateAndTimeItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignDatedItem.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignDatedItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignDocumentReference.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignDocumentReference.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignGeneralOrgItem.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignGeneralOrgItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignGroupAssignment.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignGroupAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignGroupedItem.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignGroupedItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignNominalDateAndTimeAssignment.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignNominalDateAndTimeAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignNominalDateAssignment.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignNominalDateAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignOrganizationAssignment.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignOrganizationAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignOrganizationItem.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignOrganizationItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignPersonAndOrganizationAssignment.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignPersonAndOrganizationAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignPresentedItem.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignPresentedItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignPresentedItemSelect.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignPresentedItemSelect.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignReferencingItem.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignReferencingItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_AutoDesignSecurityClassificationAssignment.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_AutoDesignSecurityClassificationAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_Class.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_Class.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_DateAndTimeItem.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_DateAndTimeItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_DateItem.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_DateItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_DocumentReferenceItem.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_DocumentReferenceItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_ExternalIdentificationItem.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_ExternalIdentificationItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_ExternallyDefinedClass.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_ExternallyDefinedClass.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_ExternallyDefinedGeneralProperty.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_ExternallyDefinedGeneralProperty.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_GroupItem.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_GroupItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_OrganizationItem.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_OrganizationItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_PersonAndOrganizationItem.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_PersonAndOrganizationItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_PresentedItemSelect.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_PresentedItemSelect.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_Protocol.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_Protocol.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_RepItemGroup.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_RepItemGroup.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP214/StepAP214_SecurityClassificationItem.cxx" )
  SOURCE_GROUP (StepAP214 FILES "../../../src/StepAP214/StepAP214_SecurityClassificationItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_GeneralModule.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_GeneralModule.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedApprovalAssignment.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedApprovalAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedDateAndTimeAssignment.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedDateAndTimeAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedDateAssignment.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedDateAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedDocumentReference.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedDocumentReference.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedExternalIdentificationAssignment.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedExternalIdentificationAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedGroupAssignment.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedGroupAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedOrganizationAssignment.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedOrganizationAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedPersonAndOrganizationAssignment.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedPersonAndOrganizationAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedPresentedItem.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedPresentedItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedSecurityClassificationAssignment.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAppliedSecurityClassificationAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignActualDateAndTimeAssignment.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignActualDateAndTimeAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignActualDateAssignment.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignActualDateAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignApprovalAssignment.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignApprovalAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignDateAndPersonAssignment.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignDateAndPersonAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignDocumentReference.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignDocumentReference.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignGroupAssignment.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignGroupAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignNominalDateAndTimeAssignment.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignNominalDateAndTimeAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignNominalDateAssignment.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignNominalDateAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignOrganizationAssignment.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignOrganizationAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignPersonAndOrganizationAssignment.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignPersonAndOrganizationAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignPresentedItem.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignPresentedItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignSecurityClassificationAssignment.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWAutoDesignSecurityClassificationAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWClass.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWClass.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWExternallyDefinedClass.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWExternallyDefinedClass.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWExternallyDefinedGeneralProperty.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWExternallyDefinedGeneralProperty.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_RWRepItemGroup.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_RWRepItemGroup.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP214/RWStepAP214_ReadWriteModule.cxx" )
  SOURCE_GROUP (RWStepAP214 FILES "../../../src/RWStepAP214/RWStepAP214_ReadWriteModule.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_Array1OfApprovedItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_Array1OfApprovedItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_Array1OfCertifiedItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_Array1OfCertifiedItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_Array1OfChangeRequestItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_Array1OfChangeRequestItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_Array1OfClassifiedItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_Array1OfClassifiedItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_Array1OfContractedItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_Array1OfContractedItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_Array1OfDateTimeItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_Array1OfDateTimeItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_Array1OfPersonOrganizationItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_Array1OfPersonOrganizationItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_Array1OfSpecifiedItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_Array1OfSpecifiedItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_Array1OfStartRequestItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_Array1OfStartRequestItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_Array1OfWorkItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_Array1OfWorkItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_HArray1OfApprovedItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_HArray1OfApprovedItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_HArray1OfCertifiedItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_HArray1OfCertifiedItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_HArray1OfChangeRequestItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_HArray1OfChangeRequestItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_HArray1OfClassifiedItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_HArray1OfClassifiedItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_HArray1OfContractedItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_HArray1OfContractedItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_HArray1OfDateTimeItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_HArray1OfDateTimeItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_HArray1OfPersonOrganizationItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_HArray1OfPersonOrganizationItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_HArray1OfSpecifiedItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_HArray1OfSpecifiedItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_HArray1OfStartRequestItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_HArray1OfStartRequestItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepAP203/StepAP203_HArray1OfWorkItem_0.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../drv/StepAP203/StepAP203_HArray1OfWorkItem_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_ApprovedItem.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_ApprovedItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_CcDesignApproval.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_CcDesignApproval.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_CcDesignCertification.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_CcDesignCertification.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_CcDesignContract.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_CcDesignContract.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_CcDesignDateAndTimeAssignment.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_CcDesignDateAndTimeAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_CcDesignPersonAndOrganizationAssignment.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_CcDesignPersonAndOrganizationAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_CcDesignSecurityClassification.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_CcDesignSecurityClassification.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_CcDesignSpecificationReference.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_CcDesignSpecificationReference.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_CertifiedItem.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_CertifiedItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_Change.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_Change.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_ChangeRequest.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_ChangeRequest.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_ChangeRequestItem.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_ChangeRequestItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_ClassifiedItem.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_ClassifiedItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_ContractedItem.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_ContractedItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_DateTimeItem.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_DateTimeItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_PersonOrganizationItem.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_PersonOrganizationItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_SpecifiedItem.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_SpecifiedItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_StartRequest.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_StartRequest.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_StartRequestItem.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_StartRequestItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_StartWork.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_StartWork.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP203/StepAP203_WorkItem.cxx" )
  SOURCE_GROUP (StepAP203 FILES "../../../src/StepAP203/StepAP203_WorkItem.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP203/RWStepAP203_RWCcDesignApproval.cxx" )
  SOURCE_GROUP (RWStepAP203 FILES "../../../src/RWStepAP203/RWStepAP203_RWCcDesignApproval.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP203/RWStepAP203_RWCcDesignCertification.cxx" )
  SOURCE_GROUP (RWStepAP203 FILES "../../../src/RWStepAP203/RWStepAP203_RWCcDesignCertification.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP203/RWStepAP203_RWCcDesignContract.cxx" )
  SOURCE_GROUP (RWStepAP203 FILES "../../../src/RWStepAP203/RWStepAP203_RWCcDesignContract.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP203/RWStepAP203_RWCcDesignDateAndTimeAssignment.cxx" )
  SOURCE_GROUP (RWStepAP203 FILES "../../../src/RWStepAP203/RWStepAP203_RWCcDesignDateAndTimeAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP203/RWStepAP203_RWCcDesignPersonAndOrganizationAssignment.cxx" )
  SOURCE_GROUP (RWStepAP203 FILES "../../../src/RWStepAP203/RWStepAP203_RWCcDesignPersonAndOrganizationAssignment.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP203/RWStepAP203_RWCcDesignSecurityClassification.cxx" )
  SOURCE_GROUP (RWStepAP203 FILES "../../../src/RWStepAP203/RWStepAP203_RWCcDesignSecurityClassification.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP203/RWStepAP203_RWCcDesignSpecificationReference.cxx" )
  SOURCE_GROUP (RWStepAP203 FILES "../../../src/RWStepAP203/RWStepAP203_RWCcDesignSpecificationReference.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP203/RWStepAP203_RWChange.cxx" )
  SOURCE_GROUP (RWStepAP203 FILES "../../../src/RWStepAP203/RWStepAP203_RWChange.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP203/RWStepAP203_RWChangeRequest.cxx" )
  SOURCE_GROUP (RWStepAP203 FILES "../../../src/RWStepAP203/RWStepAP203_RWChangeRequest.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP203/RWStepAP203_RWStartRequest.cxx" )
  SOURCE_GROUP (RWStepAP203 FILES "../../../src/RWStepAP203/RWStepAP203_RWStartRequest.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/RWStepAP203/RWStepAP203_RWStartWork.cxx" )
  SOURCE_GROUP (RWStepAP203 FILES "../../../src/RWStepAP203/RWStepAP203_RWStartWork.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/STEPConstruct/STEPConstruct_DataMapIteratorOfDataMapOfAsciiStringTransient_0.cxx" )
  SOURCE_GROUP (STEPConstruct FILES "../../../drv/STEPConstruct/STEPConstruct_DataMapIteratorOfDataMapOfAsciiStringTransient_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/STEPConstruct/STEPConstruct_DataMapIteratorOfDataMapOfPointTransient_0.cxx" )
  SOURCE_GROUP (STEPConstruct FILES "../../../drv/STEPConstruct/STEPConstruct_DataMapIteratorOfDataMapOfPointTransient_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/STEPConstruct/STEPConstruct_DataMapNodeOfDataMapOfAsciiStringTransient_0.cxx" )
  SOURCE_GROUP (STEPConstruct FILES "../../../drv/STEPConstruct/STEPConstruct_DataMapNodeOfDataMapOfAsciiStringTransient_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/STEPConstruct/STEPConstruct_DataMapNodeOfDataMapOfPointTransient_0.cxx" )
  SOURCE_GROUP (STEPConstruct FILES "../../../drv/STEPConstruct/STEPConstruct_DataMapNodeOfDataMapOfPointTransient_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/STEPConstruct/STEPConstruct_DataMapOfAsciiStringTransient_0.cxx" )
  SOURCE_GROUP (STEPConstruct FILES "../../../drv/STEPConstruct/STEPConstruct_DataMapOfAsciiStringTransient_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/STEPConstruct/STEPConstruct_DataMapOfPointTransient_0.cxx" )
  SOURCE_GROUP (STEPConstruct FILES "../../../drv/STEPConstruct/STEPConstruct_DataMapOfPointTransient_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPConstruct/STEPConstruct.cxx" )
  SOURCE_GROUP (STEPConstruct FILES "../../../src/STEPConstruct/STEPConstruct.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPConstruct/STEPConstruct_AP203Context.cxx" )
  SOURCE_GROUP (STEPConstruct FILES "../../../src/STEPConstruct/STEPConstruct_AP203Context.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPConstruct/STEPConstruct_Assembly.cxx" )
  SOURCE_GROUP (STEPConstruct FILES "../../../src/STEPConstruct/STEPConstruct_Assembly.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPConstruct/STEPConstruct_ContextTool.cxx" )
  SOURCE_GROUP (STEPConstruct FILES "../../../src/STEPConstruct/STEPConstruct_ContextTool.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPConstruct/STEPConstruct_ExternRefs.cxx" )
  SOURCE_GROUP (STEPConstruct FILES "../../../src/STEPConstruct/STEPConstruct_ExternRefs.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPConstruct/STEPConstruct_Part.cxx" )
  SOURCE_GROUP (STEPConstruct FILES "../../../src/STEPConstruct/STEPConstruct_Part.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPConstruct/STEPConstruct_PointHasher.cxx" )
  SOURCE_GROUP (STEPConstruct FILES "../../../src/STEPConstruct/STEPConstruct_PointHasher.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPConstruct/STEPConstruct_Styles.cxx" )
  SOURCE_GROUP (STEPConstruct FILES "../../../src/STEPConstruct/STEPConstruct_Styles.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPConstruct/STEPConstruct_Tool.cxx" )
  SOURCE_GROUP (STEPConstruct FILES "../../../src/STEPConstruct/STEPConstruct_Tool.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPConstruct/STEPConstruct_UnitContext.cxx" )
  SOURCE_GROUP (STEPConstruct FILES "../../../src/STEPConstruct/STEPConstruct_UnitContext.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPConstruct/STEPConstruct_ValidationProps.cxx" )
  SOURCE_GROUP (STEPConstruct FILES "../../../src/STEPConstruct/STEPConstruct_ValidationProps.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPEdit/STEPEdit.cxx" )
  SOURCE_GROUP (STEPEdit FILES "../../../src/STEPEdit/STEPEdit.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPEdit/STEPEdit_EditContext.cxx" )
  SOURCE_GROUP (STEPEdit FILES "../../../src/STEPEdit/STEPEdit_EditContext.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPEdit/STEPEdit_EditSDR.cxx" )
  SOURCE_GROUP (STEPEdit FILES "../../../src/STEPEdit/STEPEdit_EditSDR.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeAxis1Placement.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeAxis1Placement.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeAxis2Placement2d.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeAxis2Placement2d.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeAxis2Placement3d.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeAxis2Placement3d.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeBSplineCurveWithKnots.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeBSplineCurveWithKnots.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeBSplineSurfaceWithKnots.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeBSplineSurfaceWithKnots.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeBoundedCurve.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeBoundedCurve.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeBoundedSurface.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeBoundedSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeCartesianPoint.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeCartesianPoint.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeCircle.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeCircle.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeConic.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeConic.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeConicalSurface.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeConicalSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeCurve.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeCurve.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeCylindricalSurface.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeCylindricalSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeDirection.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeDirection.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeElementarySurface.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeElementarySurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeEllipse.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeEllipse.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeHyperbola.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeHyperbola.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeLine.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeLine.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeParabola.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeParabola.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakePlane.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakePlane.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakePolyline.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakePolyline.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeRectangularTrimmedSurface.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeRectangularTrimmedSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeSphericalSurface.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeSphericalSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeSurface.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeSurfaceOfLinearExtrusion.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeSurfaceOfLinearExtrusion.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeSurfaceOfRevolution.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeSurfaceOfRevolution.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeSweptSurface.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeSweptSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeToroidalSurface.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeToroidalSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_MakeVector.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_MakeVector.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/GeomToStep/GeomToStep_Root.cxx" )
  SOURCE_GROUP (GeomToStep FILES "../../../src/GeomToStep/GeomToStep_Root.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeAxis1Placement.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeAxis1Placement.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeAxis2Placement.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeAxis2Placement.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeAxisPlacement.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeAxisPlacement.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeBSplineCurve.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeBSplineCurve.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeBSplineCurve2d.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeBSplineCurve2d.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeBSplineSurface.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeBSplineSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeBoundedCurve.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeBoundedCurve.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeBoundedCurve2d.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeBoundedCurve2d.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeBoundedSurface.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeBoundedSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeCartesianPoint.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeCartesianPoint.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeCartesianPoint2d.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeCartesianPoint2d.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeCircle.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeCircle.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeCircle2d.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeCircle2d.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeConic.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeConic.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeConic2d.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeConic2d.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeConicalSurface.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeConicalSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeCurve.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeCurve.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeCurve2d.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeCurve2d.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeCylindricalSurface.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeCylindricalSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeDirection.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeDirection.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeDirection2d.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeDirection2d.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeElementarySurface.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeElementarySurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeEllipse.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeEllipse.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeEllipse2d.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeEllipse2d.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeHyperbola.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeHyperbola.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeHyperbola2d.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeHyperbola2d.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeLine.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeLine.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeLine2d.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeLine2d.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeParabola.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeParabola.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeParabola2d.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeParabola2d.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakePlane.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakePlane.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakePolyline.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakePolyline.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakePolyline2d.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakePolyline2d.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeRectangularTrimmedSurface.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeRectangularTrimmedSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeSphericalSurface.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeSphericalSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeSurface.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeSurfaceOfLinearExtrusion.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeSurfaceOfLinearExtrusion.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeSurfaceOfRevolution.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeSurfaceOfRevolution.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeSweptSurface.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeSweptSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeToroidalSurface.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeToroidalSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeTransformation2d.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeTransformation2d.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeTransformation3d.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeTransformation3d.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeTrimmedCurve.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeTrimmedCurve.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeTrimmedCurve2d.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeTrimmedCurve2d.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeVectorWithMagnitude.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeVectorWithMagnitude.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_MakeVectorWithMagnitude2d.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_MakeVectorWithMagnitude2d.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToGeom/StepToGeom_Root.cxx" )
  SOURCE_GROUP (StepToGeom FILES "../../../src/StepToGeom/StepToGeom_Root.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapIteratorOfDataMapOfRINames_0.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapIteratorOfDataMapOfRINames_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapIteratorOfDataMapOfRI_0.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapIteratorOfDataMapOfRI_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapIteratorOfDataMapOfTRI_0.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapIteratorOfDataMapOfTRI_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapIteratorOfPointEdgeMap_0.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapIteratorOfPointEdgeMap_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapIteratorOfPointVertexMap_0.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapIteratorOfPointVertexMap_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapNodeOfDataMapOfRINames_0.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapNodeOfDataMapOfRINames_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapNodeOfDataMapOfRI_0.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapNodeOfDataMapOfRI_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapNodeOfDataMapOfTRI_0.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapNodeOfDataMapOfTRI_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapNodeOfPointEdgeMap_0.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapNodeOfPointEdgeMap_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapNodeOfPointVertexMap_0.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapNodeOfPointVertexMap_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapOfRINames_0.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapOfRINames_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapOfRI_0.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapOfRI_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapOfTRI_0.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../drv/StepToTopoDS/StepToTopoDS_DataMapOfTRI_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepToTopoDS/StepToTopoDS_PointEdgeMap_0.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../drv/StepToTopoDS/StepToTopoDS_PointEdgeMap_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/StepToTopoDS/StepToTopoDS_PointVertexMap_0.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../drv/StepToTopoDS/StepToTopoDS_PointVertexMap_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS_Builder.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS_Builder.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS_CartesianPointHasher.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS_CartesianPointHasher.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS_GeometricTool.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS_GeometricTool.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS_MakeTransformed.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS_MakeTransformed.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS_NMTool.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS_NMTool.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS_PointPair.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS_PointPair.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS_PointPairHasher.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS_PointPairHasher.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS_Root.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS_Root.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS_Tool.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS_Tool.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS_TranslateCompositeCurve.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS_TranslateCompositeCurve.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS_TranslateCurveBoundedSurface.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS_TranslateCurveBoundedSurface.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS_TranslateEdge.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS_TranslateEdge.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS_TranslateEdgeLoop.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS_TranslateEdgeLoop.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS_TranslateFace.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS_TranslateFace.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS_TranslatePolyLoop.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS_TranslatePolyLoop.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS_TranslateShell.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS_TranslateShell.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS_TranslateVertex.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS_TranslateVertex.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepToTopoDS/StepToTopoDS_TranslateVertexLoop.cxx" )
  SOURCE_GROUP (StepToTopoDS FILES "../../../src/StepToTopoDS/StepToTopoDS_TranslateVertexLoop.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/TopoDSToStep/TopoDSToStep.cxx" )
  SOURCE_GROUP (TopoDSToStep FILES "../../../src/TopoDSToStep/TopoDSToStep.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/TopoDSToStep/TopoDSToStep_Builder.cxx" )
  SOURCE_GROUP (TopoDSToStep FILES "../../../src/TopoDSToStep/TopoDSToStep_Builder.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/TopoDSToStep/TopoDSToStep_FacetedTool.cxx" )
  SOURCE_GROUP (TopoDSToStep FILES "../../../src/TopoDSToStep/TopoDSToStep_FacetedTool.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/TopoDSToStep/TopoDSToStep_MakeBrepWithVoids.cxx" )
  SOURCE_GROUP (TopoDSToStep FILES "../../../src/TopoDSToStep/TopoDSToStep_MakeBrepWithVoids.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/TopoDSToStep/TopoDSToStep_MakeFacetedBrep.cxx" )
  SOURCE_GROUP (TopoDSToStep FILES "../../../src/TopoDSToStep/TopoDSToStep_MakeFacetedBrep.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/TopoDSToStep/TopoDSToStep_MakeFacetedBrepAndBrepWithVoids.cxx" )
  SOURCE_GROUP (TopoDSToStep FILES "../../../src/TopoDSToStep/TopoDSToStep_MakeFacetedBrepAndBrepWithVoids.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/TopoDSToStep/TopoDSToStep_MakeGeometricCurveSet.cxx" )
  SOURCE_GROUP (TopoDSToStep FILES "../../../src/TopoDSToStep/TopoDSToStep_MakeGeometricCurveSet.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/TopoDSToStep/TopoDSToStep_MakeManifoldSolidBrep.cxx" )
  SOURCE_GROUP (TopoDSToStep FILES "../../../src/TopoDSToStep/TopoDSToStep_MakeManifoldSolidBrep.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/TopoDSToStep/TopoDSToStep_MakeShellBasedSurfaceModel.cxx" )
  SOURCE_GROUP (TopoDSToStep FILES "../../../src/TopoDSToStep/TopoDSToStep_MakeShellBasedSurfaceModel.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/TopoDSToStep/TopoDSToStep_MakeStepEdge.cxx" )
  SOURCE_GROUP (TopoDSToStep FILES "../../../src/TopoDSToStep/TopoDSToStep_MakeStepEdge.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/TopoDSToStep/TopoDSToStep_MakeStepFace.cxx" )
  SOURCE_GROUP (TopoDSToStep FILES "../../../src/TopoDSToStep/TopoDSToStep_MakeStepFace.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/TopoDSToStep/TopoDSToStep_MakeStepVertex.cxx" )
  SOURCE_GROUP (TopoDSToStep FILES "../../../src/TopoDSToStep/TopoDSToStep_MakeStepVertex.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/TopoDSToStep/TopoDSToStep_MakeStepWire.cxx" )
  SOURCE_GROUP (TopoDSToStep FILES "../../../src/TopoDSToStep/TopoDSToStep_MakeStepWire.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/TopoDSToStep/TopoDSToStep_Root.cxx" )
  SOURCE_GROUP (TopoDSToStep FILES "../../../src/TopoDSToStep/TopoDSToStep_Root.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/TopoDSToStep/TopoDSToStep_Tool.cxx" )
  SOURCE_GROUP (TopoDSToStep FILES "../../../src/TopoDSToStep/TopoDSToStep_Tool.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/TopoDSToStep/TopoDSToStep_WireframeBuilder.cxx" )
  SOURCE_GROUP (TopoDSToStep FILES "../../../src/TopoDSToStep/TopoDSToStep_WireframeBuilder.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPControl/STEPControl_ActorRead.cxx" )
  SOURCE_GROUP (STEPControl FILES "../../../src/STEPControl/STEPControl_ActorRead.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPControl/STEPControl_ActorWrite.cxx" )
  SOURCE_GROUP (STEPControl FILES "../../../src/STEPControl/STEPControl_ActorWrite.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPControl/STEPControl_Controller.cxx" )
  SOURCE_GROUP (STEPControl FILES "../../../src/STEPControl/STEPControl_Controller.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPControl/STEPControl_Reader.cxx" )
  SOURCE_GROUP (STEPControl FILES "../../../src/STEPControl/STEPControl_Reader.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPControl/STEPControl_Writer.cxx" )
  SOURCE_GROUP (STEPControl FILES "../../../src/STEPControl/STEPControl_Writer.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/STEPSelections/STEPSelections_HSequenceOfAssemblyLink_0.cxx" )
  SOURCE_GROUP (STEPSelections FILES "../../../drv/STEPSelections/STEPSelections_HSequenceOfAssemblyLink_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/STEPSelections/STEPSelections_SequenceNodeOfSequenceOfAssemblyComponent_0.cxx" )
  SOURCE_GROUP (STEPSelections FILES "../../../drv/STEPSelections/STEPSelections_SequenceNodeOfSequenceOfAssemblyComponent_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/STEPSelections/STEPSelections_SequenceNodeOfSequenceOfAssemblyLink_0.cxx" )
  SOURCE_GROUP (STEPSelections FILES "../../../drv/STEPSelections/STEPSelections_SequenceNodeOfSequenceOfAssemblyLink_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/STEPSelections/STEPSelections_SequenceOfAssemblyComponent_0.cxx" )
  SOURCE_GROUP (STEPSelections FILES "../../../drv/STEPSelections/STEPSelections_SequenceOfAssemblyComponent_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../drv/STEPSelections/STEPSelections_SequenceOfAssemblyLink_0.cxx" )
  SOURCE_GROUP (STEPSelections FILES "../../../drv/STEPSelections/STEPSelections_SequenceOfAssemblyLink_0.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPSelections/STEPSelections_AssemblyComponent.cxx" )
  SOURCE_GROUP (STEPSelections FILES "../../../src/STEPSelections/STEPSelections_AssemblyComponent.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPSelections/STEPSelections_AssemblyExplorer.cxx" )
  SOURCE_GROUP (STEPSelections FILES "../../../src/STEPSelections/STEPSelections_AssemblyExplorer.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPSelections/STEPSelections_AssemblyLink.cxx" )
  SOURCE_GROUP (STEPSelections FILES "../../../src/STEPSelections/STEPSelections_AssemblyLink.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPSelections/STEPSelections_Counter.cxx" )
  SOURCE_GROUP (STEPSelections FILES "../../../src/STEPSelections/STEPSelections_Counter.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPSelections/STEPSelections_SelectAssembly.cxx" )
  SOURCE_GROUP (STEPSelections FILES "../../../src/STEPSelections/STEPSelections_SelectAssembly.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPSelections/STEPSelections_SelectDerived.cxx" )
  SOURCE_GROUP (STEPSelections FILES "../../../src/STEPSelections/STEPSelections_SelectDerived.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPSelections/STEPSelections_SelectFaces.cxx" )
  SOURCE_GROUP (STEPSelections FILES "../../../src/STEPSelections/STEPSelections_SelectFaces.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPSelections/STEPSelections_SelectForTransfer.cxx" )
  SOURCE_GROUP (STEPSelections FILES "../../../src/STEPSelections/STEPSelections_SelectForTransfer.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPSelections/STEPSelections_SelectGSCurves.cxx" )
  SOURCE_GROUP (STEPSelections FILES "../../../src/STEPSelections/STEPSelections_SelectGSCurves.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/STEPSelections/STEPSelections_SelectInstances.cxx" )
  SOURCE_GROUP (STEPSelections FILES "../../../src/STEPSelections/STEPSelections_SelectInstances.cxx")

  list( APPEND TKSTEP_USED_SRCFILES "../../../src/StepAP209/StepAP209_Construct.cxx" )
  SOURCE_GROUP (StepAP209 FILES "../../../src/StepAP209/StepAP209_Construct.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKSTEP)
 add_library( TKSTEP SHARED ${TKSTEP_USED_SRCFILES} )

 set_property(TARGET TKSTEP PROPERTY FOLDER DataExchange)

 install( TARGETS TKSTEP
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKSTEP.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKSTEP PROPERTIES COMPILE_FLAGS "${TKSTEP_PRECOMPILED_DEFS}" )
 include_directories( ${TKSTEP_COMPILER_DIRECTORIES} )
 target_link_libraries( TKSTEP ${TKSTEP_USED_LIBS} )
endif()
