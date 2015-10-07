# Makefile.am for Open Cascade toolkit TKV3d
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/V3d : @top_srcdir@/src/V3d: \
@top_srcdir@/drv/Graphic3d : @top_srcdir@/src/Graphic3d: \
@top_srcdir@/drv/Visual3d : @top_srcdir@/src/Visual3d: \
@top_srcdir@/drv/Select3D : @top_srcdir@/src/Select3D: \
@top_srcdir@/drv/Prs3d : @top_srcdir@/src/Prs3d: \
@top_srcdir@/drv/StdPrs : @top_srcdir@/src/StdPrs: \
@top_srcdir@/drv/SelectMgr : @top_srcdir@/src/SelectMgr: \
@top_srcdir@/drv/PrsMgr : @top_srcdir@/src/PrsMgr: \
@top_srcdir@/drv/AIS : @top_srcdir@/src/AIS: \
@top_srcdir@/drv/DsgPrs : @top_srcdir@/src/DsgPrs: \
@top_srcdir@/drv/StdSelect : @top_srcdir@/src/StdSelect


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES) $(CSF_user32_INCLUDES) $(CSF_gdi32_INCLUDES) $(CSF_OpenGlLibs_INCLUDES) $(CSF_FREETYPE_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/V3d -I@top_srcdir@/src/V3d \
-I@top_srcdir@/drv/Graphic3d -I@top_srcdir@/src/Graphic3d \
-I@top_srcdir@/drv/Visual3d -I@top_srcdir@/src/Visual3d \
-I@top_srcdir@/drv/Select3D -I@top_srcdir@/src/Select3D \
-I@top_srcdir@/drv/Prs3d -I@top_srcdir@/src/Prs3d \
-I@top_srcdir@/drv/StdPrs -I@top_srcdir@/src/StdPrs \
-I@top_srcdir@/drv/SelectMgr -I@top_srcdir@/src/SelectMgr \
-I@top_srcdir@/drv/PrsMgr -I@top_srcdir@/src/PrsMgr \
-I@top_srcdir@/drv/AIS -I@top_srcdir@/src/AIS \
-I@top_srcdir@/drv/DsgPrs -I@top_srcdir@/src/DsgPrs \
-I@top_srcdir@/drv/StdSelect -I@top_srcdir@/src/StdSelect


lib_LTLIBRARIES=libTKV3d.la

libTKV3d_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKBRep/libTKBRep.la \
../TKMath/libTKMath.la \
../TKernel/libTKernel.la \
../TKService/libTKService.la \
../TKShHealing/libTKShHealing.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../TKGeomBase/libTKGeomBase.la \
../TKMesh/libTKMesh.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKHLR/libTKHLR.la \
$(STLPort_LIB) $(CSF_user32_LIB) $(CSF_gdi32_LIB) $(CSF_OpenGlLibs_LIB) $(CSF_FREETYPE_LIB) 

libTKV3d_la_SOURCES = \
@top_srcdir@/drv/AIS/AIS_DataMapIteratorOfDataMapOfILC_0.cxx \
@top_srcdir@/drv/AIS/AIS_DataMapIteratorOfDataMapOfIOStatus_0.cxx \
@top_srcdir@/drv/AIS/AIS_DataMapIteratorOfDataMapOfSelStat_0.cxx \
@top_srcdir@/drv/AIS/AIS_DataMapIteratorOfDataMapofIntegerListOfinteractive_0.cxx \
@top_srcdir@/drv/AIS/AIS_DataMapNodeOfDataMapOfILC_0.cxx \
@top_srcdir@/drv/AIS/AIS_DataMapNodeOfDataMapOfIOStatus_0.cxx \
@top_srcdir@/drv/AIS/AIS_DataMapNodeOfDataMapOfSelStat_0.cxx \
@top_srcdir@/drv/AIS/AIS_DataMapNodeOfDataMapofIntegerListOfinteractive_0.cxx \
@top_srcdir@/drv/AIS/AIS_DataMapOfILC_0.cxx \
@top_srcdir@/drv/AIS/AIS_DataMapOfIOStatus_0.cxx \
@top_srcdir@/drv/AIS/AIS_DataMapOfSelStat_0.cxx \
@top_srcdir@/drv/AIS/AIS_DataMapofIntegerListOfinteractive_0.cxx \
@top_srcdir@/drv/AIS/AIS_IndexedDataMapNodeOfIndexedDataMapOfOwnerPrs_0.cxx \
@top_srcdir@/drv/AIS/AIS_IndexedDataMapOfOwnerPrs_0.cxx \
@top_srcdir@/drv/AIS/AIS_ListIteratorOfListOfInteractive_0.cxx \
@top_srcdir@/drv/AIS/AIS_ListNodeOfListOfInteractive_0.cxx \
@top_srcdir@/drv/AIS/AIS_ListOfInteractive_0.cxx \
@top_srcdir@/drv/AIS/AIS_MapIteratorOfMapOfInteractive_0.cxx \
@top_srcdir@/drv/AIS/AIS_MapOfInteractive_0.cxx \
@top_srcdir@/drv/AIS/AIS_SequenceNodeOfSequenceOfDimension_0.cxx \
@top_srcdir@/drv/AIS/AIS_SequenceNodeOfSequenceOfInteractive_0.cxx \
@top_srcdir@/drv/AIS/AIS_SequenceOfDimension_0.cxx \
@top_srcdir@/drv/AIS/AIS_SequenceOfInteractive_0.cxx \
@top_srcdir@/drv/AIS/AIS_StdMapNodeOfMapOfInteractive_0.cxx \
@top_srcdir@/drv/Graphic3d/Graphic3d_Array1OfVector_0.cxx \
@top_srcdir@/drv/Graphic3d/Graphic3d_Array1OfVertex_0.cxx \
@top_srcdir@/drv/Graphic3d/Graphic3d_Array2OfVertex_0.cxx \
@top_srcdir@/drv/Graphic3d/Graphic3d_AspectTextDefinitionError_0.cxx \
@top_srcdir@/drv/Graphic3d/Graphic3d_CycleError_0.cxx \
@top_srcdir@/drv/Graphic3d/Graphic3d_GroupDefinitionError_0.cxx \
@top_srcdir@/drv/Graphic3d/Graphic3d_HSequenceOfStructure_0.cxx \
@top_srcdir@/drv/Graphic3d/Graphic3d_InitialisationError_0.cxx \
@top_srcdir@/drv/Graphic3d/Graphic3d_ListIteratorOfListOfShortReal_0.cxx \
@top_srcdir@/drv/Graphic3d/Graphic3d_ListNodeOfListOfShortReal_0.cxx \
@top_srcdir@/drv/Graphic3d/Graphic3d_ListOfShortReal_0.cxx \
@top_srcdir@/drv/Graphic3d/Graphic3d_MaterialDefinitionError_0.cxx \
@top_srcdir@/drv/Graphic3d/Graphic3d_PriorityDefinitionError_0.cxx \
@top_srcdir@/drv/Graphic3d/Graphic3d_SequenceNodeOfSequenceOfStructure_0.cxx \
@top_srcdir@/drv/Graphic3d/Graphic3d_SequenceOfStructure_0.cxx \
@top_srcdir@/drv/Graphic3d/Graphic3d_StructureDefinitionError_0.cxx \
@top_srcdir@/drv/Graphic3d/Graphic3d_TransformError_0.cxx \
@top_srcdir@/drv/Graphic3d/Graphic3d_VectorError_0.cxx \
@top_srcdir@/drv/Prs3d/Prs3d_InvalidAngle_0.cxx \
@top_srcdir@/drv/PrsMgr/PrsMgr_Presentations_0.cxx \
@top_srcdir@/drv/PrsMgr/PrsMgr_SequenceNodeOfPresentations_0.cxx \
@top_srcdir@/drv/SelectMgr/SelectMgr_DataMapIteratorOfDataMapOfObjectSelectors_0.cxx \
@top_srcdir@/drv/SelectMgr/SelectMgr_DataMapNodeOfDataMapOfObjectSelectors_0.cxx \
@top_srcdir@/drv/SelectMgr/SelectMgr_DataMapOfObjectSelectors_0.cxx \
@top_srcdir@/drv/SelectMgr/SelectMgr_IndexedDataMapNodeOfIndexedDataMapOfOwnerCriterion_0.cxx \
@top_srcdir@/drv/SelectMgr/SelectMgr_IndexedDataMapOfOwnerCriterion_0.cxx \
@top_srcdir@/drv/SelectMgr/SelectMgr_ListIteratorOfListOfFilter_0.cxx \
@top_srcdir@/drv/SelectMgr/SelectMgr_ListNodeOfListOfFilter_0.cxx \
@top_srcdir@/drv/SelectMgr/SelectMgr_ListOfFilter_0.cxx \
@top_srcdir@/drv/SelectMgr/SelectMgr_SequenceNodeOfSequenceOfFilter_0.cxx \
@top_srcdir@/drv/SelectMgr/SelectMgr_SequenceNodeOfSequenceOfOwner_0.cxx \
@top_srcdir@/drv/SelectMgr/SelectMgr_SequenceNodeOfSequenceOfSelector_0.cxx \
@top_srcdir@/drv/SelectMgr/SelectMgr_SequenceOfFilter_0.cxx \
@top_srcdir@/drv/SelectMgr/SelectMgr_SequenceOfOwner_0.cxx \
@top_srcdir@/drv/SelectMgr/SelectMgr_SequenceOfSelector_0.cxx \
@top_srcdir@/drv/StdSelect/StdSelect_IndexedDataMapNodeOfIndexedDataMapOfOwnerPrs_0.cxx \
@top_srcdir@/drv/StdSelect/StdSelect_IndexedDataMapOfOwnerPrs_0.cxx \
@top_srcdir@/drv/V3d/V3d_BadValue_0.cxx \
@top_srcdir@/drv/V3d/V3d_UnMapped_0.cxx \
@top_srcdir@/drv/Visual3d/Visual3d_ClipDefinitionError_0.cxx \
@top_srcdir@/drv/Visual3d/Visual3d_ContextPickDefinitionError_0.cxx \
@top_srcdir@/drv/Visual3d/Visual3d_DepthCueingDefinitionError_0.cxx \
@top_srcdir@/drv/Visual3d/Visual3d_HSequenceOfLight_0.cxx \
@top_srcdir@/drv/Visual3d/Visual3d_HSequenceOfView_0.cxx \
@top_srcdir@/drv/Visual3d/Visual3d_LayerDefinitionError_0.cxx \
@top_srcdir@/drv/Visual3d/Visual3d_LightDefinitionError_0.cxx \
@top_srcdir@/drv/Visual3d/Visual3d_PickError_0.cxx \
@top_srcdir@/drv/Visual3d/Visual3d_SequenceNodeOfSequenceOfLight_0.cxx \
@top_srcdir@/drv/Visual3d/Visual3d_SequenceNodeOfSequenceOfView_0.cxx \
@top_srcdir@/drv/Visual3d/Visual3d_SequenceOfLight_0.cxx \
@top_srcdir@/drv/Visual3d/Visual3d_SequenceOfView_0.cxx \
@top_srcdir@/drv/Visual3d/Visual3d_TransformError_0.cxx \
@top_srcdir@/drv/Visual3d/Visual3d_ViewDefinitionError_0.cxx \
@top_srcdir@/drv/Visual3d/Visual3d_ViewManagerDefinitionError_0.cxx \
@top_srcdir@/drv/Visual3d/Visual3d_ViewMappingDefinitionError_0.cxx \
@top_srcdir@/drv/Visual3d/Visual3d_ViewOrientationDefinitionError_0.cxx \
@top_srcdir@/drv/Visual3d/Visual3d_ZClippingDefinitionError_0.cxx \
@top_srcdir@/src/AIS/AIS.cxx \
@top_srcdir@/src/AIS/AIS_AngleDimension.cxx \
@top_srcdir@/src/AIS/AIS_AttributeFilter.cxx \
@top_srcdir@/src/AIS/AIS_Axis.cxx \
@top_srcdir@/src/AIS/AIS_BadEdgeFilter.cxx \
@top_srcdir@/src/AIS/AIS_C0RegularityFilter.cxx \
@top_srcdir@/src/AIS/AIS_Chamf2dDimension.cxx \
@top_srcdir@/src/AIS/AIS_Chamf3dDimension.cxx \
@top_srcdir@/src/AIS/AIS_Circle.cxx \
@top_srcdir@/src/AIS/AIS_ColoredShape.cxx \
@top_srcdir@/src/AIS/AIS_ConcentricRelation.cxx \
@top_srcdir@/src/AIS/AIS_ConnectedInteractive.cxx \
@top_srcdir@/src/AIS/AIS_DiameterDimension.cxx \
@top_srcdir@/src/AIS/AIS_Dimension.cxx \
@top_srcdir@/src/AIS/AIS_DimensionOwner.cxx \
@top_srcdir@/src/AIS/AIS_EllipseRadiusDimension.cxx \
@top_srcdir@/src/AIS/AIS_EqualDistanceRelation.cxx \
@top_srcdir@/src/AIS/AIS_EqualRadiusRelation.cxx \
@top_srcdir@/src/AIS/AIS_ExclusionFilter.cxx \
@top_srcdir@/src/AIS/AIS_FixRelation.cxx \
@top_srcdir@/src/AIS/AIS_GlobalStatus.cxx \
@top_srcdir@/src/AIS/AIS_GraphicTool.cxx \
@top_srcdir@/src/AIS/AIS_IdenticRelation.cxx \
@top_srcdir@/src/AIS/AIS_InteractiveContext.cxx \
@top_srcdir@/src/AIS/AIS_InteractiveContext_1.cxx \
@top_srcdir@/src/AIS/AIS_InteractiveContext_2.cxx \
@top_srcdir@/src/AIS/AIS_InteractiveContext_3.cxx \
@top_srcdir@/src/AIS/AIS_InteractiveObject.cxx \
@top_srcdir@/src/AIS/AIS_LengthDimension.cxx \
@top_srcdir@/src/AIS/AIS_Line.cxx \
@top_srcdir@/src/AIS/AIS_LocalContext.cxx \
@top_srcdir@/src/AIS/AIS_LocalContext_1.cxx \
@top_srcdir@/src/AIS/AIS_LocalStatus.cxx \
@top_srcdir@/src/AIS/AIS_MaxRadiusDimension.cxx \
@top_srcdir@/src/AIS/AIS_MidPointRelation.cxx \
@top_srcdir@/src/AIS/AIS_MinRadiusDimension.cxx \
@top_srcdir@/src/AIS/AIS_MultipleConnectedInteractive.cxx \
@top_srcdir@/src/AIS/AIS_OffsetDimension.cxx \
@top_srcdir@/src/AIS/AIS_ParallelRelation.cxx \
@top_srcdir@/src/AIS/AIS_PerpendicularRelation.cxx \
@top_srcdir@/src/AIS/AIS_Plane.cxx \
@top_srcdir@/src/AIS/AIS_PlaneTrihedron.cxx \
@top_srcdir@/src/AIS/AIS_Point.cxx \
@top_srcdir@/src/AIS/AIS_PointCloud.cxx \
@top_srcdir@/src/AIS/AIS_RadiusDimension.cxx \
@top_srcdir@/src/AIS/AIS_Relation.cxx \
@top_srcdir@/src/AIS/AIS_Selection.cxx \
@top_srcdir@/src/AIS/AIS_Shape.cxx \
@top_srcdir@/src/AIS/AIS_SignatureFilter.cxx \
@top_srcdir@/src/AIS/AIS_SymmetricRelation.cxx \
@top_srcdir@/src/AIS/AIS_TangentRelation.cxx \
@top_srcdir@/src/AIS/AIS_TextLabel.cxx \
@top_srcdir@/src/AIS/AIS_TexturedShape.cxx \
@top_srcdir@/src/AIS/AIS_Triangulation.cxx \
@top_srcdir@/src/AIS/AIS_Trihedron.cxx \
@top_srcdir@/src/AIS/AIS_TypeFilter.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_AnglePresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_Chamf2dPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_ConcentricPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_DatumPrs.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_DiameterPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_EllipseRadiusPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_EqualDistancePresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_EqualRadiusPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_FilletRadiusPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_FixPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_IdenticPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_LengthPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_MidPointPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_OffsetPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_ParalPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_PerpenPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_RadiusPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_ShadedPlanePresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_ShapeDirPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_SymbPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_SymmetricPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_TangentPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_XYZAxisPresentation.cxx \
@top_srcdir@/src/DsgPrs/DsgPrs_XYZPlanePresentation.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_ArrayOfPoints.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_ArrayOfPolygons.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_ArrayOfPolylines.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_ArrayOfPrimitives.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_ArrayOfQuadrangleStrips.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_ArrayOfQuadrangles.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_ArrayOfSegments.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_ArrayOfTriangleFans.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_ArrayOfTriangleStrips.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_ArrayOfTriangles.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_AspectFillArea3d.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_AspectLine3d.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_AspectMarker3d.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_AspectText3d.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_CStructure.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_Camera.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_ClipPlane.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_DataStructureManager.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_GraphicDriver.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_Group.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_MarkerImage.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_MaterialAspect.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_ShaderObject.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_ShaderProgram.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_ShaderVariable.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_Structure.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_StructureManager.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_Texture1D.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_Texture1Dmanual.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_Texture1Dsegment.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_Texture2D.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_Texture2Dmanual.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_Texture2Dplane.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_TextureEnv.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_TextureMap.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_TextureParams.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_TextureRoot.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_Vector.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_Vertex.cxx \
@top_srcdir@/src/Graphic3d/Graphic3d_ViewAffinity.cxx \
@top_srcdir@/src/Prs3d/Prs3d.cxx \
@top_srcdir@/src/Prs3d/Prs3d_Arrow.cxx \
@top_srcdir@/src/Prs3d/Prs3d_ArrowAspect.cxx \
@top_srcdir@/src/Prs3d/Prs3d_BasicAspect.cxx \
@top_srcdir@/src/Prs3d/Prs3d_DatumAspect.cxx \
@top_srcdir@/src/Prs3d/Prs3d_DimensionAspect.cxx \
@top_srcdir@/src/Prs3d/Prs3d_DimensionUnits.cxx \
@top_srcdir@/src/Prs3d/Prs3d_Drawer.cxx \
@top_srcdir@/src/Prs3d/Prs3d_IsoAspect.cxx \
@top_srcdir@/src/Prs3d/Prs3d_LineAspect.cxx \
@top_srcdir@/src/Prs3d/Prs3d_PlaneAspect.cxx \
@top_srcdir@/src/Prs3d/Prs3d_PlaneSet.cxx \
@top_srcdir@/src/Prs3d/Prs3d_PointAspect.cxx \
@top_srcdir@/src/Prs3d/Prs3d_Presentation.cxx \
@top_srcdir@/src/Prs3d/Prs3d_PresentationShadow.cxx \
@top_srcdir@/src/Prs3d/Prs3d_Projector.cxx \
@top_srcdir@/src/Prs3d/Prs3d_Root.cxx \
@top_srcdir@/src/Prs3d/Prs3d_ShadingAspect.cxx \
@top_srcdir@/src/Prs3d/Prs3d_ShapeTool.cxx \
@top_srcdir@/src/Prs3d/Prs3d_Text.cxx \
@top_srcdir@/src/Prs3d/Prs3d_TextAspect.cxx \
@top_srcdir@/src/Prs3d/Prs3d_WFShape.cxx \
@top_srcdir@/src/PrsMgr/PrsMgr_ModedPresentation.cxx \
@top_srcdir@/src/PrsMgr/PrsMgr_PresentableObject.cxx \
@top_srcdir@/src/PrsMgr/PrsMgr_Presentation.cxx \
@top_srcdir@/src/PrsMgr/PrsMgr_PresentationManager.cxx \
@top_srcdir@/src/PrsMgr/PrsMgr_Prs.cxx \
@top_srcdir@/src/Select3D/Select3D_BVHPrimitiveContent.cxx \
@top_srcdir@/src/Select3D/Select3D_InteriorSensitivePointSet.cxx \
@top_srcdir@/src/Select3D/Select3D_SensitiveBox.cxx \
@top_srcdir@/src/Select3D/Select3D_SensitiveCircle.cxx \
@top_srcdir@/src/Select3D/Select3D_SensitiveCurve.cxx \
@top_srcdir@/src/Select3D/Select3D_SensitiveEntity.cxx \
@top_srcdir@/src/Select3D/Select3D_SensitiveFace.cxx \
@top_srcdir@/src/Select3D/Select3D_SensitiveGroup.cxx \
@top_srcdir@/src/Select3D/Select3D_SensitivePoint.cxx \
@top_srcdir@/src/Select3D/Select3D_SensitivePoly.cxx \
@top_srcdir@/src/Select3D/Select3D_SensitiveSegment.cxx \
@top_srcdir@/src/Select3D/Select3D_SensitiveSet.cxx \
@top_srcdir@/src/Select3D/Select3D_SensitiveTriangle.cxx \
@top_srcdir@/src/Select3D/Select3D_SensitiveTriangulation.cxx \
@top_srcdir@/src/Select3D/Select3D_SensitiveWire.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_AndFilter.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_BaseFrustum.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_CompositionFilter.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_EntityOwner.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_Filter.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_FrustumBuilder.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_OrFilter.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_RectangularFrustum.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_SelectableObject.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_SelectableObjectSet.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_SelectingVolumeManager.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_Selection.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_SelectionManager.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_SensitiveEntity.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_SensitiveEntitySet.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_SortCriterion.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_TriangularFrustum.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_TriangularFrustumSet.cxx \
@top_srcdir@/src/SelectMgr/SelectMgr_ViewerSelector.cxx \
@top_srcdir@/src/StdPrs/StdPrs_Curve.cxx \
@top_srcdir@/src/StdPrs/StdPrs_DeflectionCurve.cxx \
@top_srcdir@/src/StdPrs/StdPrs_HLRPolyShape.cxx \
@top_srcdir@/src/StdPrs/StdPrs_HLRShape.cxx \
@top_srcdir@/src/StdPrs/StdPrs_HLRToolShape.cxx \
@top_srcdir@/src/StdPrs/StdPrs_Plane.cxx \
@top_srcdir@/src/StdPrs/StdPrs_PoleCurve.cxx \
@top_srcdir@/src/StdPrs/StdPrs_ShadedShape.cxx \
@top_srcdir@/src/StdPrs/StdPrs_ShadedSurface.cxx \
@top_srcdir@/src/StdPrs/StdPrs_ToolPoint.cxx \
@top_srcdir@/src/StdPrs/StdPrs_ToolRFace.cxx \
@top_srcdir@/src/StdPrs/StdPrs_ToolShadedShape.cxx \
@top_srcdir@/src/StdPrs/StdPrs_ToolVertex.cxx \
@top_srcdir@/src/StdPrs/StdPrs_WFDeflectionRestrictedFace.cxx \
@top_srcdir@/src/StdPrs/StdPrs_WFDeflectionSurface.cxx \
@top_srcdir@/src/StdPrs/StdPrs_WFPoleSurface.cxx \
@top_srcdir@/src/StdPrs/StdPrs_WFRestrictedFace.cxx \
@top_srcdir@/src/StdPrs/StdPrs_WFSurface.cxx \
@top_srcdir@/src/StdSelect/StdSelect.cxx \
@top_srcdir@/src/StdSelect/StdSelect_BRepOwner.cxx \
@top_srcdir@/src/StdSelect/StdSelect_BRepSelectionTool.cxx \
@top_srcdir@/src/StdSelect/StdSelect_EdgeFilter.cxx \
@top_srcdir@/src/StdSelect/StdSelect_FaceFilter.cxx \
@top_srcdir@/src/StdSelect/StdSelect_Prs.cxx \
@top_srcdir@/src/StdSelect/StdSelect_Shape.cxx \
@top_srcdir@/src/StdSelect/StdSelect_ShapeTypeFilter.cxx \
@top_srcdir@/src/StdSelect/StdSelect_ViewerSelector3d.cxx \
@top_srcdir@/src/V3d/V3d.cxx \
@top_srcdir@/src/V3d/V3d_AmbientLight.cxx \
@top_srcdir@/src/V3d/V3d_CircularGrid.cxx \
@top_srcdir@/src/V3d/V3d_ColorScale.cxx \
@top_srcdir@/src/V3d/V3d_ColorScaleLayerItem.cxx \
@top_srcdir@/src/V3d/V3d_DirectionalLight.cxx \
@top_srcdir@/src/V3d/V3d_LayerMgr.cxx \
@top_srcdir@/src/V3d/V3d_Light.cxx \
@top_srcdir@/src/V3d/V3d_Plane.cxx \
@top_srcdir@/src/V3d/V3d_PositionLight.cxx \
@top_srcdir@/src/V3d/V3d_PositionalLight.cxx \
@top_srcdir@/src/V3d/V3d_RectangularGrid.cxx \
@top_srcdir@/src/V3d/V3d_SpotLight.cxx \
@top_srcdir@/src/V3d/V3d_View.cxx \
@top_srcdir@/src/V3d/V3d_View_1.cxx \
@top_srcdir@/src/V3d/V3d_View_2.cxx \
@top_srcdir@/src/V3d/V3d_View_3.cxx \
@top_srcdir@/src/V3d/V3d_View_4.cxx \
@top_srcdir@/src/V3d/V3d_View_5.cxx \
@top_srcdir@/src/V3d/V3d_View_Print.cxx \
@top_srcdir@/src/V3d/V3d_Viewer.cxx \
@top_srcdir@/src/V3d/V3d_Viewer_1.cxx \
@top_srcdir@/src/V3d/V3d_Viewer_2.cxx \
@top_srcdir@/src/V3d/V3d_Viewer_3.cxx \
@top_srcdir@/src/V3d/V3d_Viewer_4.cxx \
@top_srcdir@/src/Visual3d/Visual3d_ContextPick.cxx \
@top_srcdir@/src/Visual3d/Visual3d_ContextView.cxx \
@top_srcdir@/src/Visual3d/Visual3d_Layer.cxx \
@top_srcdir@/src/Visual3d/Visual3d_LayerItem.cxx \
@top_srcdir@/src/Visual3d/Visual3d_Light.cxx \
@top_srcdir@/src/Visual3d/Visual3d_View.cxx \
@top_srcdir@/src/Visual3d/Visual3d_ViewManager.cxx

