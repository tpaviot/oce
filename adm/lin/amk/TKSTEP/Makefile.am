# Makefile.am for Open Cascade toolkit TKSTEP
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/StepAP214 : @top_srcdir@/src/StepAP214: \
@top_srcdir@/drv/RWStepAP214 : @top_srcdir@/src/RWStepAP214: \
@top_srcdir@/drv/StepAP203 : @top_srcdir@/src/StepAP203: \
@top_srcdir@/drv/RWStepAP203 : @top_srcdir@/src/RWStepAP203: \
@top_srcdir@/drv/STEPConstruct : @top_srcdir@/src/STEPConstruct: \
@top_srcdir@/drv/STEPEdit : @top_srcdir@/src/STEPEdit: \
@top_srcdir@/drv/GeomToStep : @top_srcdir@/src/GeomToStep: \
@top_srcdir@/drv/StepToGeom : @top_srcdir@/src/StepToGeom: \
@top_srcdir@/drv/StepToTopoDS : @top_srcdir@/src/StepToTopoDS: \
@top_srcdir@/drv/TopoDSToStep : @top_srcdir@/src/TopoDSToStep: \
@top_srcdir@/drv/STEPControl : @top_srcdir@/src/STEPControl: \
@top_srcdir@/drv/STEPSelections : @top_srcdir@/src/STEPSelections: \
@top_srcdir@/drv/StepAP209 : @top_srcdir@/src/StepAP209


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES) $(CSF_wsock32_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/StepAP214 -I@top_srcdir@/src/StepAP214 \
-I@top_srcdir@/drv/RWStepAP214 -I@top_srcdir@/src/RWStepAP214 \
-I@top_srcdir@/drv/StepAP203 -I@top_srcdir@/src/StepAP203 \
-I@top_srcdir@/drv/RWStepAP203 -I@top_srcdir@/src/RWStepAP203 \
-I@top_srcdir@/drv/STEPConstruct -I@top_srcdir@/src/STEPConstruct \
-I@top_srcdir@/drv/STEPEdit -I@top_srcdir@/src/STEPEdit \
-I@top_srcdir@/drv/GeomToStep -I@top_srcdir@/src/GeomToStep \
-I@top_srcdir@/drv/StepToGeom -I@top_srcdir@/src/StepToGeom \
-I@top_srcdir@/drv/StepToTopoDS -I@top_srcdir@/src/StepToTopoDS \
-I@top_srcdir@/drv/TopoDSToStep -I@top_srcdir@/src/TopoDSToStep \
-I@top_srcdir@/drv/STEPControl -I@top_srcdir@/src/STEPControl \
-I@top_srcdir@/drv/STEPSelections -I@top_srcdir@/src/STEPSelections \
-I@top_srcdir@/drv/StepAP209 -I@top_srcdir@/src/StepAP209


lib_LTLIBRARIES=libTKSTEP.la

libTKSTEP_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKernel/libTKernel.la \
../TKSTEPAttr/libTKSTEPAttr.la \
../TKSTEP209/libTKSTEP209.la \
../TKSTEPBase/libTKSTEPBase.la \
../TKBRep/libTKBRep.la \
../TKMath/libTKMath.la \
../TKG2d/libTKG2d.la \
../TKShHealing/libTKShHealing.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKG3d/libTKG3d.la \
../TKGeomBase/libTKGeomBase.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKXSBase/libTKXSBase.la \
$(STLPort_LIB) $(CSF_wsock32_LIB) 

libTKSTEP_la_SOURCES = \
@top_srcdir@/drv/STEPConstruct/STEPConstruct_DataMapIteratorOfDataMapOfAsciiStringTransient_0.cxx \
@top_srcdir@/drv/STEPConstruct/STEPConstruct_DataMapIteratorOfDataMapOfPointTransient_0.cxx \
@top_srcdir@/drv/STEPConstruct/STEPConstruct_DataMapNodeOfDataMapOfAsciiStringTransient_0.cxx \
@top_srcdir@/drv/STEPConstruct/STEPConstruct_DataMapNodeOfDataMapOfPointTransient_0.cxx \
@top_srcdir@/drv/STEPConstruct/STEPConstruct_DataMapOfAsciiStringTransient_0.cxx \
@top_srcdir@/drv/STEPConstruct/STEPConstruct_DataMapOfPointTransient_0.cxx \
@top_srcdir@/drv/STEPSelections/STEPSelections_HSequenceOfAssemblyLink_0.cxx \
@top_srcdir@/drv/STEPSelections/STEPSelections_SequenceNodeOfSequenceOfAssemblyComponent_0.cxx \
@top_srcdir@/drv/STEPSelections/STEPSelections_SequenceNodeOfSequenceOfAssemblyLink_0.cxx \
@top_srcdir@/drv/STEPSelections/STEPSelections_SequenceOfAssemblyComponent_0.cxx \
@top_srcdir@/drv/STEPSelections/STEPSelections_SequenceOfAssemblyLink_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_Array1OfApprovedItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_Array1OfCertifiedItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_Array1OfChangeRequestItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_Array1OfClassifiedItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_Array1OfContractedItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_Array1OfDateTimeItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_Array1OfPersonOrganizationItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_Array1OfSpecifiedItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_Array1OfStartRequestItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_Array1OfWorkItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_HArray1OfApprovedItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_HArray1OfCertifiedItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_HArray1OfChangeRequestItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_HArray1OfClassifiedItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_HArray1OfContractedItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_HArray1OfDateTimeItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_HArray1OfPersonOrganizationItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_HArray1OfSpecifiedItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_HArray1OfStartRequestItem_0.cxx \
@top_srcdir@/drv/StepAP203/StepAP203_HArray1OfWorkItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_Array1OfApprovalItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_Array1OfAutoDesignDateAndPersonItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_Array1OfAutoDesignDateAndTimeItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_Array1OfAutoDesignDatedItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_Array1OfAutoDesignGeneralOrgItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_Array1OfAutoDesignGroupedItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_Array1OfAutoDesignPresentedItemSelect_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_Array1OfAutoDesignReferencingItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_Array1OfDateAndTimeItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_Array1OfDateItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_Array1OfDocumentReferenceItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_Array1OfExternalIdentificationItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_Array1OfGroupItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_Array1OfOrganizationItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_Array1OfPersonAndOrganizationItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_Array1OfPresentedItemSelect_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_Array1OfSecurityClassificationItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_HArray1OfApprovalItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_HArray1OfAutoDesignDateAndPersonItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_HArray1OfAutoDesignDateAndTimeItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_HArray1OfAutoDesignDatedItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_HArray1OfAutoDesignGeneralOrgItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_HArray1OfAutoDesignGroupedItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_HArray1OfAutoDesignPresentedItemSelect_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_HArray1OfAutoDesignReferencingItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_HArray1OfDateAndTimeItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_HArray1OfDateItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_HArray1OfDocumentReferenceItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_HArray1OfExternalIdentificationItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_HArray1OfGroupItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_HArray1OfOrganizationItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_HArray1OfPersonAndOrganizationItem_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_HArray1OfPresentedItemSelect_0.cxx \
@top_srcdir@/drv/StepAP214/StepAP214_HArray1OfSecurityClassificationItem_0.cxx \
@top_srcdir@/drv/StepToTopoDS/StepToTopoDS_DataMapIteratorOfDataMapOfRINames_0.cxx \
@top_srcdir@/drv/StepToTopoDS/StepToTopoDS_DataMapIteratorOfDataMapOfRI_0.cxx \
@top_srcdir@/drv/StepToTopoDS/StepToTopoDS_DataMapIteratorOfDataMapOfTRI_0.cxx \
@top_srcdir@/drv/StepToTopoDS/StepToTopoDS_DataMapIteratorOfPointEdgeMap_0.cxx \
@top_srcdir@/drv/StepToTopoDS/StepToTopoDS_DataMapIteratorOfPointVertexMap_0.cxx \
@top_srcdir@/drv/StepToTopoDS/StepToTopoDS_DataMapNodeOfDataMapOfRINames_0.cxx \
@top_srcdir@/drv/StepToTopoDS/StepToTopoDS_DataMapNodeOfDataMapOfRI_0.cxx \
@top_srcdir@/drv/StepToTopoDS/StepToTopoDS_DataMapNodeOfDataMapOfTRI_0.cxx \
@top_srcdir@/drv/StepToTopoDS/StepToTopoDS_DataMapNodeOfPointEdgeMap_0.cxx \
@top_srcdir@/drv/StepToTopoDS/StepToTopoDS_DataMapNodeOfPointVertexMap_0.cxx \
@top_srcdir@/drv/StepToTopoDS/StepToTopoDS_DataMapOfRINames_0.cxx \
@top_srcdir@/drv/StepToTopoDS/StepToTopoDS_DataMapOfRI_0.cxx \
@top_srcdir@/drv/StepToTopoDS/StepToTopoDS_DataMapOfTRI_0.cxx \
@top_srcdir@/drv/StepToTopoDS/StepToTopoDS_PointEdgeMap_0.cxx \
@top_srcdir@/drv/StepToTopoDS/StepToTopoDS_PointVertexMap_0.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeAxis1Placement.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeAxis2Placement2d.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeAxis2Placement3d.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeBSplineCurveWithKnots.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeBSplineSurfaceWithKnots.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeBSplineSurfaceWithKnotsAndRationalBSplineSurface.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeBoundedCurve.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeBoundedSurface.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeCartesianPoint.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeCircle.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeConic.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeConicalSurface.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeCurve.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeCylindricalSurface.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeDirection.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeElementarySurface.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeEllipse.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeHyperbola.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeLine.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeParabola.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakePlane.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakePolyline.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeRectangularTrimmedSurface.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeSphericalSurface.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeSurface.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeSurfaceOfLinearExtrusion.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeSurfaceOfRevolution.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeSweptSurface.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeToroidalSurface.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_MakeVector.cxx \
@top_srcdir@/src/GeomToStep/GeomToStep_Root.cxx \
@top_srcdir@/src/RWStepAP203/RWStepAP203_RWCcDesignApproval.cxx \
@top_srcdir@/src/RWStepAP203/RWStepAP203_RWCcDesignCertification.cxx \
@top_srcdir@/src/RWStepAP203/RWStepAP203_RWCcDesignContract.cxx \
@top_srcdir@/src/RWStepAP203/RWStepAP203_RWCcDesignDateAndTimeAssignment.cxx \
@top_srcdir@/src/RWStepAP203/RWStepAP203_RWCcDesignPersonAndOrganizationAssignment.cxx \
@top_srcdir@/src/RWStepAP203/RWStepAP203_RWCcDesignSecurityClassification.cxx \
@top_srcdir@/src/RWStepAP203/RWStepAP203_RWCcDesignSpecificationReference.cxx \
@top_srcdir@/src/RWStepAP203/RWStepAP203_RWChange.cxx \
@top_srcdir@/src/RWStepAP203/RWStepAP203_RWChangeRequest.cxx \
@top_srcdir@/src/RWStepAP203/RWStepAP203_RWStartRequest.cxx \
@top_srcdir@/src/RWStepAP203/RWStepAP203_RWStartWork.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_GeneralModule.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAppliedApprovalAssignment.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAppliedDateAndTimeAssignment.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAppliedDateAssignment.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAppliedDocumentReference.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAppliedExternalIdentificationAssignment.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAppliedGroupAssignment.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAppliedOrganizationAssignment.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAppliedPersonAndOrganizationAssignment.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAppliedPresentedItem.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAppliedSecurityClassificationAssignment.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAutoDesignActualDateAndTimeAssignment.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAutoDesignActualDateAssignment.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAutoDesignApprovalAssignment.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAutoDesignDateAndPersonAssignment.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAutoDesignDocumentReference.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAutoDesignGroupAssignment.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAutoDesignNominalDateAndTimeAssignment.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAutoDesignNominalDateAssignment.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAutoDesignOrganizationAssignment.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAutoDesignPersonAndOrganizationAssignment.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAutoDesignPresentedItem.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWAutoDesignSecurityClassificationAssignment.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWClass.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWExternallyDefinedClass.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWExternallyDefinedGeneralProperty.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_RWRepItemGroup.cxx \
@top_srcdir@/src/RWStepAP214/RWStepAP214_ReadWriteModule.cxx \
@top_srcdir@/src/STEPConstruct/STEPConstruct.cxx \
@top_srcdir@/src/STEPConstruct/STEPConstruct_AP203Context.cxx \
@top_srcdir@/src/STEPConstruct/STEPConstruct_Assembly.cxx \
@top_srcdir@/src/STEPConstruct/STEPConstruct_ContextTool.cxx \
@top_srcdir@/src/STEPConstruct/STEPConstruct_ExternRefs.cxx \
@top_srcdir@/src/STEPConstruct/STEPConstruct_Part.cxx \
@top_srcdir@/src/STEPConstruct/STEPConstruct_PointHasher.cxx \
@top_srcdir@/src/STEPConstruct/STEPConstruct_Styles.cxx \
@top_srcdir@/src/STEPConstruct/STEPConstruct_Tool.cxx \
@top_srcdir@/src/STEPConstruct/STEPConstruct_UnitContext.cxx \
@top_srcdir@/src/STEPConstruct/STEPConstruct_ValidationProps.cxx \
@top_srcdir@/src/STEPControl/STEPControl_ActorRead.cxx \
@top_srcdir@/src/STEPControl/STEPControl_ActorWrite.cxx \
@top_srcdir@/src/STEPControl/STEPControl_Controller.cxx \
@top_srcdir@/src/STEPControl/STEPControl_Reader.cxx \
@top_srcdir@/src/STEPControl/STEPControl_Writer.cxx \
@top_srcdir@/src/STEPEdit/STEPEdit.cxx \
@top_srcdir@/src/STEPEdit/STEPEdit_EditContext.cxx \
@top_srcdir@/src/STEPEdit/STEPEdit_EditSDR.cxx \
@top_srcdir@/src/STEPSelections/STEPSelections_AssemblyComponent.cxx \
@top_srcdir@/src/STEPSelections/STEPSelections_AssemblyExplorer.cxx \
@top_srcdir@/src/STEPSelections/STEPSelections_AssemblyLink.cxx \
@top_srcdir@/src/STEPSelections/STEPSelections_Counter.cxx \
@top_srcdir@/src/STEPSelections/STEPSelections_SelectAssembly.cxx \
@top_srcdir@/src/STEPSelections/STEPSelections_SelectDerived.cxx \
@top_srcdir@/src/STEPSelections/STEPSelections_SelectFaces.cxx \
@top_srcdir@/src/STEPSelections/STEPSelections_SelectForTransfer.cxx \
@top_srcdir@/src/STEPSelections/STEPSelections_SelectGSCurves.cxx \
@top_srcdir@/src/STEPSelections/STEPSelections_SelectInstances.cxx \
@top_srcdir@/src/StepAP203/StepAP203_ApprovedItem.cxx \
@top_srcdir@/src/StepAP203/StepAP203_CcDesignApproval.cxx \
@top_srcdir@/src/StepAP203/StepAP203_CcDesignCertification.cxx \
@top_srcdir@/src/StepAP203/StepAP203_CcDesignContract.cxx \
@top_srcdir@/src/StepAP203/StepAP203_CcDesignDateAndTimeAssignment.cxx \
@top_srcdir@/src/StepAP203/StepAP203_CcDesignPersonAndOrganizationAssignment.cxx \
@top_srcdir@/src/StepAP203/StepAP203_CcDesignSecurityClassification.cxx \
@top_srcdir@/src/StepAP203/StepAP203_CcDesignSpecificationReference.cxx \
@top_srcdir@/src/StepAP203/StepAP203_CertifiedItem.cxx \
@top_srcdir@/src/StepAP203/StepAP203_Change.cxx \
@top_srcdir@/src/StepAP203/StepAP203_ChangeRequest.cxx \
@top_srcdir@/src/StepAP203/StepAP203_ChangeRequestItem.cxx \
@top_srcdir@/src/StepAP203/StepAP203_ClassifiedItem.cxx \
@top_srcdir@/src/StepAP203/StepAP203_ContractedItem.cxx \
@top_srcdir@/src/StepAP203/StepAP203_DateTimeItem.cxx \
@top_srcdir@/src/StepAP203/StepAP203_PersonOrganizationItem.cxx \
@top_srcdir@/src/StepAP203/StepAP203_SpecifiedItem.cxx \
@top_srcdir@/src/StepAP203/StepAP203_StartRequest.cxx \
@top_srcdir@/src/StepAP203/StepAP203_StartRequestItem.cxx \
@top_srcdir@/src/StepAP203/StepAP203_StartWork.cxx \
@top_srcdir@/src/StepAP203/StepAP203_WorkItem.cxx \
@top_srcdir@/src/StepAP209/StepAP209_Construct.cxx \
@top_srcdir@/src/StepAP214/StepAP214.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AppliedApprovalAssignment.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AppliedDateAndTimeAssignment.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AppliedDateAssignment.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AppliedDocumentReference.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AppliedExternalIdentificationAssignment.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AppliedGroupAssignment.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AppliedOrganizationAssignment.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AppliedPersonAndOrganizationAssignment.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AppliedPresentedItem.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AppliedSecurityClassificationAssignment.cxx \
@top_srcdir@/src/StepAP214/StepAP214_ApprovalItem.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignActualDateAndTimeAssignment.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignActualDateAssignment.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignApprovalAssignment.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignDateAndPersonAssignment.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignDateAndPersonItem.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignDateAndTimeItem.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignDatedItem.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignDocumentReference.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignGeneralOrgItem.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignGroupAssignment.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignGroupedItem.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignNominalDateAndTimeAssignment.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignNominalDateAssignment.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignOrganizationAssignment.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignOrganizationItem.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignPersonAndOrganizationAssignment.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignPresentedItem.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignPresentedItemSelect.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignReferencingItem.cxx \
@top_srcdir@/src/StepAP214/StepAP214_AutoDesignSecurityClassificationAssignment.cxx \
@top_srcdir@/src/StepAP214/StepAP214_Class.cxx \
@top_srcdir@/src/StepAP214/StepAP214_DateAndTimeItem.cxx \
@top_srcdir@/src/StepAP214/StepAP214_DateItem.cxx \
@top_srcdir@/src/StepAP214/StepAP214_DocumentReferenceItem.cxx \
@top_srcdir@/src/StepAP214/StepAP214_ExternalIdentificationItem.cxx \
@top_srcdir@/src/StepAP214/StepAP214_ExternallyDefinedClass.cxx \
@top_srcdir@/src/StepAP214/StepAP214_ExternallyDefinedGeneralProperty.cxx \
@top_srcdir@/src/StepAP214/StepAP214_GroupItem.cxx \
@top_srcdir@/src/StepAP214/StepAP214_OrganizationItem.cxx \
@top_srcdir@/src/StepAP214/StepAP214_PersonAndOrganizationItem.cxx \
@top_srcdir@/src/StepAP214/StepAP214_PresentedItemSelect.cxx \
@top_srcdir@/src/StepAP214/StepAP214_Protocol.cxx \
@top_srcdir@/src/StepAP214/StepAP214_RepItemGroup.cxx \
@top_srcdir@/src/StepAP214/StepAP214_SecurityClassificationItem.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeAxis1Placement.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeAxis2Placement.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeAxisPlacement.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeBSplineCurve.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeBSplineCurve2d.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeBSplineSurface.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeBoundedCurve.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeBoundedCurve2d.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeBoundedSurface.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeCartesianPoint.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeCartesianPoint2d.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeCircle.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeCircle2d.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeConic.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeConic2d.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeConicalSurface.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeCurve.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeCurve2d.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeCylindricalSurface.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeDirection.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeDirection2d.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeElementarySurface.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeEllipse.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeEllipse2d.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeHyperbola.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeHyperbola2d.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeLine.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeLine2d.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeParabola.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeParabola2d.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakePlane.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakePolyline.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakePolyline2d.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeRectangularTrimmedSurface.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeSphericalSurface.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeSurface.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeSurfaceOfLinearExtrusion.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeSurfaceOfRevolution.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeSweptSurface.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeToroidalSurface.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeTransformation2d.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeTransformation3d.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeTrimmedCurve.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeTrimmedCurve2d.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeVectorWithMagnitude.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_MakeVectorWithMagnitude2d.cxx \
@top_srcdir@/src/StepToGeom/StepToGeom_Root.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS_Builder.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS_CartesianPointHasher.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS_GeometricTool.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS_MakeTransformed.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS_NMTool.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS_PointPair.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS_PointPairHasher.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS_Root.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS_Tool.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS_TranslateCompositeCurve.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS_TranslateCurveBoundedSurface.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS_TranslateEdge.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS_TranslateEdgeLoop.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS_TranslateFace.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS_TranslatePolyLoop.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS_TranslateShell.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS_TranslateVertex.cxx \
@top_srcdir@/src/StepToTopoDS/StepToTopoDS_TranslateVertexLoop.cxx \
@top_srcdir@/src/TopoDSToStep/TopoDSToStep.cxx \
@top_srcdir@/src/TopoDSToStep/TopoDSToStep_Builder.cxx \
@top_srcdir@/src/TopoDSToStep/TopoDSToStep_FacetedTool.cxx \
@top_srcdir@/src/TopoDSToStep/TopoDSToStep_MakeBrepWithVoids.cxx \
@top_srcdir@/src/TopoDSToStep/TopoDSToStep_MakeFacetedBrep.cxx \
@top_srcdir@/src/TopoDSToStep/TopoDSToStep_MakeFacetedBrepAndBrepWithVoids.cxx \
@top_srcdir@/src/TopoDSToStep/TopoDSToStep_MakeGeometricCurveSet.cxx \
@top_srcdir@/src/TopoDSToStep/TopoDSToStep_MakeManifoldSolidBrep.cxx \
@top_srcdir@/src/TopoDSToStep/TopoDSToStep_MakeShellBasedSurfaceModel.cxx \
@top_srcdir@/src/TopoDSToStep/TopoDSToStep_MakeStepEdge.cxx \
@top_srcdir@/src/TopoDSToStep/TopoDSToStep_MakeStepFace.cxx \
@top_srcdir@/src/TopoDSToStep/TopoDSToStep_MakeStepVertex.cxx \
@top_srcdir@/src/TopoDSToStep/TopoDSToStep_MakeStepWire.cxx \
@top_srcdir@/src/TopoDSToStep/TopoDSToStep_Root.cxx \
@top_srcdir@/src/TopoDSToStep/TopoDSToStep_Tool.cxx \
@top_srcdir@/src/TopoDSToStep/TopoDSToStep_WireframeBuilder.cxx

