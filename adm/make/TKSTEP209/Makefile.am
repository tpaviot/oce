# Makefile.am for Open Cascade toolkit TKSTEP209
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/StepElement : @top_srcdir@/src/StepElement: \
@top_srcdir@/drv/StepFEA : @top_srcdir@/src/StepFEA: \
@top_srcdir@/drv/RWStepElement : @top_srcdir@/src/RWStepElement: \
@top_srcdir@/drv/RWStepFEA : @top_srcdir@/src/RWStepFEA


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/StepElement -I@top_srcdir@/src/StepElement \
-I@top_srcdir@/drv/StepFEA -I@top_srcdir@/src/StepFEA \
-I@top_srcdir@/drv/RWStepElement -I@top_srcdir@/src/RWStepElement \
-I@top_srcdir@/drv/RWStepFEA -I@top_srcdir@/src/RWStepFEA


lib_LTLIBRARIES=libTKSTEP209.la

libTKSTEP209_la_LIBADD = \
../TKSTEPBase/libTKSTEPBase.la \
../TKernel/libTKernel.la \
../TKXSBase/libTKXSBase.la \
$(STLPort_LIB) 

libTKSTEP209_la_SOURCES = \
@top_srcdir@/drv/StepElement/StepElement_Array1OfCurveElementEndReleasePacket_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_Array1OfCurveElementSectionDefinition_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_Array1OfHSequenceOfCurveElementPurposeMember_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_Array1OfHSequenceOfSurfaceElementPurposeMember_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_Array1OfMeasureOrUnspecifiedValue_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_Array1OfSurfaceSection_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_Array1OfVolumeElementPurposeMember_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_Array1OfVolumeElementPurpose_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_Array2OfCurveElementPurposeMember_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_Array2OfSurfaceElementPurposeMember_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_Array2OfSurfaceElementPurpose_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_HArray1OfCurveElementEndReleasePacket_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_HArray1OfCurveElementSectionDefinition_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_HArray1OfHSequenceOfCurveElementPurposeMember_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_HArray1OfHSequenceOfSurfaceElementPurposeMember_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_HArray1OfMeasureOrUnspecifiedValue_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_HArray1OfSurfaceSection_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_HArray1OfVolumeElementPurposeMember_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_HArray1OfVolumeElementPurpose_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_HArray2OfCurveElementPurposeMember_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_HArray2OfSurfaceElementPurposeMember_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_HArray2OfSurfaceElementPurpose_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_HSequenceOfCurveElementPurposeMember_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_HSequenceOfCurveElementSectionDefinition_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_HSequenceOfElementMaterial_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_HSequenceOfSurfaceElementPurposeMember_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_SequenceNodeOfSequenceOfCurveElementPurposeMember_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_SequenceNodeOfSequenceOfCurveElementSectionDefinition_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_SequenceNodeOfSequenceOfElementMaterial_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_SequenceNodeOfSequenceOfSurfaceElementPurposeMember_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_SequenceOfCurveElementPurposeMember_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_SequenceOfCurveElementSectionDefinition_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_SequenceOfElementMaterial_0.cxx \
@top_srcdir@/drv/StepElement/StepElement_SequenceOfSurfaceElementPurposeMember_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_Array1OfCurveElementEndOffset_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_Array1OfCurveElementEndRelease_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_Array1OfCurveElementInterval_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_Array1OfDegreeOfFreedom_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_Array1OfElementRepresentation_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_Array1OfNodeRepresentation_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_HArray1OfCurveElementEndOffset_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_HArray1OfCurveElementEndRelease_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_HArray1OfCurveElementInterval_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_HArray1OfDegreeOfFreedom_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_HArray1OfElementRepresentation_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_HArray1OfNodeRepresentation_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_HSequenceOfCurve3dElementProperty_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_HSequenceOfElementGeometricRelationship_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_HSequenceOfElementRepresentation_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_HSequenceOfNodeRepresentation_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_SequenceNodeOfSequenceOfCurve3dElementProperty_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_SequenceNodeOfSequenceOfElementGeometricRelationship_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_SequenceNodeOfSequenceOfElementRepresentation_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_SequenceNodeOfSequenceOfNodeRepresentation_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_SequenceOfCurve3dElementProperty_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_SequenceOfElementGeometricRelationship_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_SequenceOfElementRepresentation_0.cxx \
@top_srcdir@/drv/StepFEA/StepFEA_SequenceOfNodeRepresentation_0.cxx \
@top_srcdir@/src/RWStepElement/RWStepElement_RWAnalysisItemWithinRepresentation.cxx \
@top_srcdir@/src/RWStepElement/RWStepElement_RWCurve3dElementDescriptor.cxx \
@top_srcdir@/src/RWStepElement/RWStepElement_RWCurveElementEndReleasePacket.cxx \
@top_srcdir@/src/RWStepElement/RWStepElement_RWCurveElementSectionDefinition.cxx \
@top_srcdir@/src/RWStepElement/RWStepElement_RWCurveElementSectionDerivedDefinitions.cxx \
@top_srcdir@/src/RWStepElement/RWStepElement_RWElementDescriptor.cxx \
@top_srcdir@/src/RWStepElement/RWStepElement_RWElementMaterial.cxx \
@top_srcdir@/src/RWStepElement/RWStepElement_RWSurface3dElementDescriptor.cxx \
@top_srcdir@/src/RWStepElement/RWStepElement_RWSurfaceElementProperty.cxx \
@top_srcdir@/src/RWStepElement/RWStepElement_RWSurfaceSection.cxx \
@top_srcdir@/src/RWStepElement/RWStepElement_RWSurfaceSectionField.cxx \
@top_srcdir@/src/RWStepElement/RWStepElement_RWSurfaceSectionFieldConstant.cxx \
@top_srcdir@/src/RWStepElement/RWStepElement_RWSurfaceSectionFieldVarying.cxx \
@top_srcdir@/src/RWStepElement/RWStepElement_RWUniformSurfaceSection.cxx \
@top_srcdir@/src/RWStepElement/RWStepElement_RWVolume3dElementDescriptor.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWAlignedCurve3dElementCoordinateSystem.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWAlignedSurface3dElementCoordinateSystem.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWArbitraryVolume3dElementCoordinateSystem.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWConstantSurface3dElementCoordinateSystem.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWCurve3dElementProperty.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWCurve3dElementRepresentation.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWCurveElementEndOffset.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWCurveElementEndRelease.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWCurveElementInterval.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWCurveElementIntervalConstant.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWCurveElementIntervalLinearlyVarying.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWCurveElementLocation.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWDummyNode.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWElementGeometricRelationship.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWElementGroup.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWElementRepresentation.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaAreaDensity.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaAxis2Placement3d.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaCurveSectionGeometricRelationship.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaGroup.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaLinearElasticity.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaMassDensity.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaMaterialPropertyRepresentation.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaMaterialPropertyRepresentationItem.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaModel.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaModel3d.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaModelDefinition.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaMoistureAbsorption.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaParametricPoint.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaRepresentationItem.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaSecantCoefficientOfLinearThermalExpansion.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaShellBendingStiffness.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaShellMembraneBendingCouplingStiffness.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaShellMembraneStiffness.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaShellShearStiffness.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaSurfaceSectionGeometricRelationship.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFeaTangentialCoefficientOfLinearThermalExpansion.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFreedomAndCoefficient.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWFreedomsList.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWGeometricNode.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWNode.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWNodeDefinition.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWNodeGroup.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWNodeRepresentation.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWNodeSet.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWNodeWithSolutionCoordinateSystem.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWNodeWithVector.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWParametricCurve3dElementCoordinateDirection.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWParametricCurve3dElementCoordinateSystem.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWParametricSurface3dElementCoordinateSystem.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWSurface3dElementRepresentation.cxx \
@top_srcdir@/src/RWStepFEA/RWStepFEA_RWVolume3dElementRepresentation.cxx \
@top_srcdir@/src/StepElement/StepElement_AnalysisItemWithinRepresentation.cxx \
@top_srcdir@/src/StepElement/StepElement_Curve3dElementDescriptor.cxx \
@top_srcdir@/src/StepElement/StepElement_CurveElementEndReleasePacket.cxx \
@top_srcdir@/src/StepElement/StepElement_CurveElementFreedom.cxx \
@top_srcdir@/src/StepElement/StepElement_CurveElementFreedomMember.cxx \
@top_srcdir@/src/StepElement/StepElement_CurveElementPurpose.cxx \
@top_srcdir@/src/StepElement/StepElement_CurveElementPurposeMember.cxx \
@top_srcdir@/src/StepElement/StepElement_CurveElementSectionDefinition.cxx \
@top_srcdir@/src/StepElement/StepElement_CurveElementSectionDerivedDefinitions.cxx \
@top_srcdir@/src/StepElement/StepElement_ElementAspect.cxx \
@top_srcdir@/src/StepElement/StepElement_ElementAspectMember.cxx \
@top_srcdir@/src/StepElement/StepElement_ElementDescriptor.cxx \
@top_srcdir@/src/StepElement/StepElement_ElementMaterial.cxx \
@top_srcdir@/src/StepElement/StepElement_MeasureOrUnspecifiedValue.cxx \
@top_srcdir@/src/StepElement/StepElement_MeasureOrUnspecifiedValueMember.cxx \
@top_srcdir@/src/StepElement/StepElement_Surface3dElementDescriptor.cxx \
@top_srcdir@/src/StepElement/StepElement_SurfaceElementProperty.cxx \
@top_srcdir@/src/StepElement/StepElement_SurfaceElementPurpose.cxx \
@top_srcdir@/src/StepElement/StepElement_SurfaceElementPurposeMember.cxx \
@top_srcdir@/src/StepElement/StepElement_SurfaceSection.cxx \
@top_srcdir@/src/StepElement/StepElement_SurfaceSectionField.cxx \
@top_srcdir@/src/StepElement/StepElement_SurfaceSectionFieldConstant.cxx \
@top_srcdir@/src/StepElement/StepElement_SurfaceSectionFieldVarying.cxx \
@top_srcdir@/src/StepElement/StepElement_UniformSurfaceSection.cxx \
@top_srcdir@/src/StepElement/StepElement_Volume3dElementDescriptor.cxx \
@top_srcdir@/src/StepElement/StepElement_VolumeElementPurpose.cxx \
@top_srcdir@/src/StepElement/StepElement_VolumeElementPurposeMember.cxx \
@top_srcdir@/src/StepFEA/StepFEA_AlignedCurve3dElementCoordinateSystem.cxx \
@top_srcdir@/src/StepFEA/StepFEA_AlignedSurface3dElementCoordinateSystem.cxx \
@top_srcdir@/src/StepFEA/StepFEA_ArbitraryVolume3dElementCoordinateSystem.cxx \
@top_srcdir@/src/StepFEA/StepFEA_ConstantSurface3dElementCoordinateSystem.cxx \
@top_srcdir@/src/StepFEA/StepFEA_Curve3dElementProperty.cxx \
@top_srcdir@/src/StepFEA/StepFEA_Curve3dElementRepresentation.cxx \
@top_srcdir@/src/StepFEA/StepFEA_CurveElementEndCoordinateSystem.cxx \
@top_srcdir@/src/StepFEA/StepFEA_CurveElementEndOffset.cxx \
@top_srcdir@/src/StepFEA/StepFEA_CurveElementEndRelease.cxx \
@top_srcdir@/src/StepFEA/StepFEA_CurveElementInterval.cxx \
@top_srcdir@/src/StepFEA/StepFEA_CurveElementIntervalConstant.cxx \
@top_srcdir@/src/StepFEA/StepFEA_CurveElementIntervalLinearlyVarying.cxx \
@top_srcdir@/src/StepFEA/StepFEA_CurveElementLocation.cxx \
@top_srcdir@/src/StepFEA/StepFEA_DegreeOfFreedom.cxx \
@top_srcdir@/src/StepFEA/StepFEA_DegreeOfFreedomMember.cxx \
@top_srcdir@/src/StepFEA/StepFEA_DummyNode.cxx \
@top_srcdir@/src/StepFEA/StepFEA_ElementGeometricRelationship.cxx \
@top_srcdir@/src/StepFEA/StepFEA_ElementGroup.cxx \
@top_srcdir@/src/StepFEA/StepFEA_ElementOrElementGroup.cxx \
@top_srcdir@/src/StepFEA/StepFEA_ElementRepresentation.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaAreaDensity.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaAxis2Placement3d.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaCurveSectionGeometricRelationship.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaGroup.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaLinearElasticity.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaMassDensity.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaMaterialPropertyRepresentation.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaMaterialPropertyRepresentationItem.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaModel.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaModel3d.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaModelDefinition.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaMoistureAbsorption.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaParametricPoint.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaRepresentationItem.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaSecantCoefficientOfLinearThermalExpansion.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaShellBendingStiffness.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaShellMembraneBendingCouplingStiffness.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaShellMembraneStiffness.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaShellShearStiffness.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaSurfaceSectionGeometricRelationship.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FeaTangentialCoefficientOfLinearThermalExpansion.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FreedomAndCoefficient.cxx \
@top_srcdir@/src/StepFEA/StepFEA_FreedomsList.cxx \
@top_srcdir@/src/StepFEA/StepFEA_GeometricNode.cxx \
@top_srcdir@/src/StepFEA/StepFEA_Node.cxx \
@top_srcdir@/src/StepFEA/StepFEA_NodeDefinition.cxx \
@top_srcdir@/src/StepFEA/StepFEA_NodeGroup.cxx \
@top_srcdir@/src/StepFEA/StepFEA_NodeRepresentation.cxx \
@top_srcdir@/src/StepFEA/StepFEA_NodeSet.cxx \
@top_srcdir@/src/StepFEA/StepFEA_NodeWithSolutionCoordinateSystem.cxx \
@top_srcdir@/src/StepFEA/StepFEA_NodeWithVector.cxx \
@top_srcdir@/src/StepFEA/StepFEA_ParametricCurve3dElementCoordinateDirection.cxx \
@top_srcdir@/src/StepFEA/StepFEA_ParametricCurve3dElementCoordinateSystem.cxx \
@top_srcdir@/src/StepFEA/StepFEA_ParametricSurface3dElementCoordinateSystem.cxx \
@top_srcdir@/src/StepFEA/StepFEA_Surface3dElementRepresentation.cxx \
@top_srcdir@/src/StepFEA/StepFEA_SymmetricTensor22d.cxx \
@top_srcdir@/src/StepFEA/StepFEA_SymmetricTensor23d.cxx \
@top_srcdir@/src/StepFEA/StepFEA_SymmetricTensor23dMember.cxx \
@top_srcdir@/src/StepFEA/StepFEA_SymmetricTensor42d.cxx \
@top_srcdir@/src/StepFEA/StepFEA_SymmetricTensor43d.cxx \
@top_srcdir@/src/StepFEA/StepFEA_SymmetricTensor43dMember.cxx \
@top_srcdir@/src/StepFEA/StepFEA_Volume3dElementRepresentation.cxx

libTKSTEP209_laLDFLAGS = -version-info @oce_version_info@

