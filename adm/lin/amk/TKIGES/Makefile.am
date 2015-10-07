# Makefile.am for Open Cascade toolkit TKIGES
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/IGESData : @top_srcdir@/src/IGESData: \
@top_srcdir@/drv/IGESFile : @top_srcdir@/src/IGESFile: \
@top_srcdir@/drv/IGESBasic : @top_srcdir@/src/IGESBasic: \
@top_srcdir@/drv/IGESGraph : @top_srcdir@/src/IGESGraph: \
@top_srcdir@/drv/IGESGeom : @top_srcdir@/src/IGESGeom: \
@top_srcdir@/drv/IGESDimen : @top_srcdir@/src/IGESDimen: \
@top_srcdir@/drv/IGESDraw : @top_srcdir@/src/IGESDraw: \
@top_srcdir@/drv/IGESSolid : @top_srcdir@/src/IGESSolid: \
@top_srcdir@/drv/IGESDefs : @top_srcdir@/src/IGESDefs: \
@top_srcdir@/drv/IGESAppli : @top_srcdir@/src/IGESAppli: \
@top_srcdir@/drv/IGESConvGeom : @top_srcdir@/src/IGESConvGeom: \
@top_srcdir@/drv/IGESSelect : @top_srcdir@/src/IGESSelect: \
@top_srcdir@/drv/IGESToBRep : @top_srcdir@/src/IGESToBRep: \
@top_srcdir@/drv/GeomToIGES : @top_srcdir@/src/GeomToIGES: \
@top_srcdir@/drv/Geom2dToIGES : @top_srcdir@/src/Geom2dToIGES: \
@top_srcdir@/drv/BRepToIGES : @top_srcdir@/src/BRepToIGES: \
@top_srcdir@/drv/BRepToIGESBRep : @top_srcdir@/src/BRepToIGESBRep: \
@top_srcdir@/drv/IGESControl : @top_srcdir@/src/IGESControl


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/IGESData -I@top_srcdir@/src/IGESData \
-I@top_srcdir@/drv/IGESFile -I@top_srcdir@/src/IGESFile \
-I@top_srcdir@/drv/IGESBasic -I@top_srcdir@/src/IGESBasic \
-I@top_srcdir@/drv/IGESGraph -I@top_srcdir@/src/IGESGraph \
-I@top_srcdir@/drv/IGESGeom -I@top_srcdir@/src/IGESGeom \
-I@top_srcdir@/drv/IGESDimen -I@top_srcdir@/src/IGESDimen \
-I@top_srcdir@/drv/IGESDraw -I@top_srcdir@/src/IGESDraw \
-I@top_srcdir@/drv/IGESSolid -I@top_srcdir@/src/IGESSolid \
-I@top_srcdir@/drv/IGESDefs -I@top_srcdir@/src/IGESDefs \
-I@top_srcdir@/drv/IGESAppli -I@top_srcdir@/src/IGESAppli \
-I@top_srcdir@/drv/IGESConvGeom -I@top_srcdir@/src/IGESConvGeom \
-I@top_srcdir@/drv/IGESSelect -I@top_srcdir@/src/IGESSelect \
-I@top_srcdir@/drv/IGESToBRep -I@top_srcdir@/src/IGESToBRep \
-I@top_srcdir@/drv/GeomToIGES -I@top_srcdir@/src/GeomToIGES \
-I@top_srcdir@/drv/Geom2dToIGES -I@top_srcdir@/src/Geom2dToIGES \
-I@top_srcdir@/drv/BRepToIGES -I@top_srcdir@/src/BRepToIGES \
-I@top_srcdir@/drv/BRepToIGESBRep -I@top_srcdir@/src/BRepToIGESBRep \
-I@top_srcdir@/drv/IGESControl -I@top_srcdir@/src/IGESControl


lib_LTLIBRARIES=libTKIGES.la

libTKIGES_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKBRep/libTKBRep.la \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKShHealing/libTKShHealing.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../TKGeomBase/libTKGeomBase.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKPrim/libTKPrim.la \
../TKBool/libTKBool.la \
../TKXSBase/libTKXSBase.la \
$(STLPort_LIB) 

libTKIGES_la_SOURCES = \
@top_srcdir@/drv/IGESAppli/IGESAppli_Array1OfFiniteElement_0.cxx \
@top_srcdir@/drv/IGESAppli/IGESAppli_Array1OfFlow_0.cxx \
@top_srcdir@/drv/IGESAppli/IGESAppli_Array1OfNode_0.cxx \
@top_srcdir@/drv/IGESAppli/IGESAppli_HArray1OfFiniteElement_0.cxx \
@top_srcdir@/drv/IGESAppli/IGESAppli_HArray1OfFlow_0.cxx \
@top_srcdir@/drv/IGESAppli/IGESAppli_HArray1OfNode_0.cxx \
@top_srcdir@/drv/IGESBasic/IGESBasic_Array1OfLineFontEntity_0.cxx \
@top_srcdir@/drv/IGESBasic/IGESBasic_Array2OfHArray1OfReal_0.cxx \
@top_srcdir@/drv/IGESBasic/IGESBasic_HArray1OfHArray1OfIGESEntity_0.cxx \
@top_srcdir@/drv/IGESBasic/IGESBasic_HArray1OfHArray1OfInteger_0.cxx \
@top_srcdir@/drv/IGESBasic/IGESBasic_HArray1OfHArray1OfReal_0.cxx \
@top_srcdir@/drv/IGESBasic/IGESBasic_HArray1OfHArray1OfXYZ_0.cxx \
@top_srcdir@/drv/IGESBasic/IGESBasic_HArray1OfHArray1OfXY_0.cxx \
@top_srcdir@/drv/IGESBasic/IGESBasic_HArray1OfLineFontEntity_0.cxx \
@top_srcdir@/drv/IGESBasic/IGESBasic_HArray2OfHArray1OfReal_0.cxx \
@top_srcdir@/drv/IGESData/IGESData_Array1OfDirPart_0.cxx \
@top_srcdir@/drv/IGESData/IGESData_Array1OfIGESEntity_0.cxx \
@top_srcdir@/drv/IGESData/IGESData_FileRecognizer_0.cxx \
@top_srcdir@/drv/IGESData/IGESData_GlobalNodeOfSpecificLib_0.cxx \
@top_srcdir@/drv/IGESData/IGESData_GlobalNodeOfWriterLib_0.cxx \
@top_srcdir@/drv/IGESData/IGESData_HArray1OfIGESEntity_0.cxx \
@top_srcdir@/drv/IGESData/IGESData_NodeOfSpecificLib_0.cxx \
@top_srcdir@/drv/IGESData/IGESData_NodeOfWriterLib_0.cxx \
@top_srcdir@/drv/IGESData/IGESData_SpecificLib_0.cxx \
@top_srcdir@/drv/IGESData/IGESData_WriterLib_0.cxx \
@top_srcdir@/drv/IGESDefs/IGESDefs_Array1OfTabularData_0.cxx \
@top_srcdir@/drv/IGESDefs/IGESDefs_HArray1OfHArray1OfTextDisplayTemplate_0.cxx \
@top_srcdir@/drv/IGESDefs/IGESDefs_HArray1OfTabularData_0.cxx \
@top_srcdir@/drv/IGESDimen/IGESDimen_Array1OfGeneralNote_0.cxx \
@top_srcdir@/drv/IGESDimen/IGESDimen_Array1OfLeaderArrow_0.cxx \
@top_srcdir@/drv/IGESDimen/IGESDimen_HArray1OfGeneralNote_0.cxx \
@top_srcdir@/drv/IGESDimen/IGESDimen_HArray1OfLeaderArrow_0.cxx \
@top_srcdir@/drv/IGESDraw/IGESDraw_Array1OfConnectPoint_0.cxx \
@top_srcdir@/drv/IGESDraw/IGESDraw_Array1OfViewKindEntity_0.cxx \
@top_srcdir@/drv/IGESDraw/IGESDraw_HArray1OfConnectPoint_0.cxx \
@top_srcdir@/drv/IGESDraw/IGESDraw_HArray1OfViewKindEntity_0.cxx \
@top_srcdir@/drv/IGESGeom/IGESGeom_Array1OfBoundary_0.cxx \
@top_srcdir@/drv/IGESGeom/IGESGeom_Array1OfCurveOnSurface_0.cxx \
@top_srcdir@/drv/IGESGeom/IGESGeom_Array1OfTransformationMatrix_0.cxx \
@top_srcdir@/drv/IGESGeom/IGESGeom_HArray1OfBoundary_0.cxx \
@top_srcdir@/drv/IGESGeom/IGESGeom_HArray1OfCurveOnSurface_0.cxx \
@top_srcdir@/drv/IGESGeom/IGESGeom_HArray1OfTransformationMatrix_0.cxx \
@top_srcdir@/drv/IGESGraph/IGESGraph_Array1OfColor_0.cxx \
@top_srcdir@/drv/IGESGraph/IGESGraph_Array1OfTextDisplayTemplate_0.cxx \
@top_srcdir@/drv/IGESGraph/IGESGraph_Array1OfTextFontDef_0.cxx \
@top_srcdir@/drv/IGESGraph/IGESGraph_HArray1OfColor_0.cxx \
@top_srcdir@/drv/IGESGraph/IGESGraph_HArray1OfTextDisplayTemplate_0.cxx \
@top_srcdir@/drv/IGESGraph/IGESGraph_HArray1OfTextFontDef_0.cxx \
@top_srcdir@/drv/IGESSelect/IGESSelect_FileModifier_0.cxx \
@top_srcdir@/drv/IGESSelect/IGESSelect_ModelModifier_0.cxx \
@top_srcdir@/drv/IGESSolid/IGESSolid_Array1OfFace_0.cxx \
@top_srcdir@/drv/IGESSolid/IGESSolid_Array1OfLoop_0.cxx \
@top_srcdir@/drv/IGESSolid/IGESSolid_Array1OfShell_0.cxx \
@top_srcdir@/drv/IGESSolid/IGESSolid_Array1OfVertexList_0.cxx \
@top_srcdir@/drv/IGESSolid/IGESSolid_HArray1OfFace_0.cxx \
@top_srcdir@/drv/IGESSolid/IGESSolid_HArray1OfLoop_0.cxx \
@top_srcdir@/drv/IGESSolid/IGESSolid_HArray1OfShell_0.cxx \
@top_srcdir@/drv/IGESSolid/IGESSolid_HArray1OfVertexList_0.cxx \
@top_srcdir@/src/BRepToIGES/BRepToIGES_BREntity.cxx \
@top_srcdir@/src/BRepToIGES/BRepToIGES_BRShell.cxx \
@top_srcdir@/src/BRepToIGES/BRepToIGES_BRSolid.cxx \
@top_srcdir@/src/BRepToIGES/BRepToIGES_BRWire.cxx \
@top_srcdir@/src/BRepToIGESBRep/BRepToIGESBRep_Entity.cxx \
@top_srcdir@/src/Geom2dToIGES/Geom2dToIGES_Geom2dCurve.cxx \
@top_srcdir@/src/Geom2dToIGES/Geom2dToIGES_Geom2dEntity.cxx \
@top_srcdir@/src/Geom2dToIGES/Geom2dToIGES_Geom2dPoint.cxx \
@top_srcdir@/src/Geom2dToIGES/Geom2dToIGES_Geom2dVector.cxx \
@top_srcdir@/src/GeomToIGES/GeomToIGES_GeomCurve.cxx \
@top_srcdir@/src/GeomToIGES/GeomToIGES_GeomEntity.cxx \
@top_srcdir@/src/GeomToIGES/GeomToIGES_GeomPoint.cxx \
@top_srcdir@/src/GeomToIGES/GeomToIGES_GeomSurface.cxx \
@top_srcdir@/src/GeomToIGES/GeomToIGES_GeomVector.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_DrilledHole.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ElementResults.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_FiniteElement.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_Flow.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_FlowLineSpec.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_GeneralModule.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_LevelFunction.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_LevelToPWBLayerMap.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_LineWidening.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_NodalConstraint.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_NodalDisplAndRot.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_NodalResults.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_Node.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_PWBArtworkStackup.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_PWBDrilledHole.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_PartNumber.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_PinNumber.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_PipingFlow.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_Protocol.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ReadWriteModule.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ReferenceDesignator.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_RegionRestriction.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_SpecificModule.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolDrilledHole.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolElementResults.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolFiniteElement.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolFlow.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolFlowLineSpec.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolLevelFunction.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolLevelToPWBLayerMap.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolLineWidening.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolNodalConstraint.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolNodalDisplAndRot.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolNodalResults.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolNode.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolPWBArtworkStackup.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolPWBDrilledHole.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolPartNumber.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolPinNumber.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolPipingFlow.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolReferenceDesignator.cxx \
@top_srcdir@/src/IGESAppli/IGESAppli_ToolRegionRestriction.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_AssocGroupType.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ExternalRefFile.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ExternalRefFileIndex.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ExternalRefFileName.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ExternalRefLibName.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ExternalRefName.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ExternalReferenceFile.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_GeneralModule.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_Group.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_GroupWithoutBackP.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_Hierarchy.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_Name.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_OrderedGroup.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_OrderedGroupWithoutBackP.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_Protocol.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ReadWriteModule.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_SingleParent.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_SingularSubfigure.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_SpecificModule.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_SubfigureDef.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ToolAssocGroupType.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ToolExternalRefFile.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ToolExternalRefFileIndex.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ToolExternalRefFileName.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ToolExternalRefLibName.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ToolExternalRefName.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ToolExternalReferenceFile.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ToolGroup.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ToolGroupWithoutBackP.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ToolHierarchy.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ToolName.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ToolOrderedGroup.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ToolOrderedGroupWithoutBackP.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ToolSingleParent.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ToolSingularSubfigure.cxx \
@top_srcdir@/src/IGESBasic/IGESBasic_ToolSubfigureDef.cxx \
@top_srcdir@/src/IGESControl/IGESControl_ActorWrite.cxx \
@top_srcdir@/src/IGESControl/IGESControl_AlgoContainer.cxx \
@top_srcdir@/src/IGESControl/IGESControl_Controller.cxx \
@top_srcdir@/src/IGESControl/IGESControl_IGESBoundary.cxx \
@top_srcdir@/src/IGESControl/IGESControl_Reader.cxx \
@top_srcdir@/src/IGESControl/IGESControl_ToolContainer.cxx \
@top_srcdir@/src/IGESControl/IGESControl_Writer.cxx \
@top_srcdir@/src/IGESConvGeom/IGESConvGeom.cxx \
@top_srcdir@/src/IGESConvGeom/IGESConvGeom_GeomBuilder.cxx \
@top_srcdir@/src/IGESData/IGESData.cxx \
@top_srcdir@/src/IGESData/IGESData_BasicEditor.cxx \
@top_srcdir@/src/IGESData/IGESData_ColorEntity.cxx \
@top_srcdir@/src/IGESData/IGESData_DefSwitch.cxx \
@top_srcdir@/src/IGESData/IGESData_DefaultGeneral.cxx \
@top_srcdir@/src/IGESData/IGESData_DefaultSpecific.cxx \
@top_srcdir@/src/IGESData/IGESData_DirChecker.cxx \
@top_srcdir@/src/IGESData/IGESData_DirPart.cxx \
@top_srcdir@/src/IGESData/IGESData_FileProtocol.cxx \
@top_srcdir@/src/IGESData/IGESData_FreeFormatEntity.cxx \
@top_srcdir@/src/IGESData/IGESData_GeneralModule.cxx \
@top_srcdir@/src/IGESData/IGESData_GlobalSection.cxx \
@top_srcdir@/src/IGESData/IGESData_IGESDumper.cxx \
@top_srcdir@/src/IGESData/IGESData_IGESEntity.cxx \
@top_srcdir@/src/IGESData/IGESData_IGESModel.cxx \
@top_srcdir@/src/IGESData/IGESData_IGESReaderData.cxx \
@top_srcdir@/src/IGESData/IGESData_IGESReaderTool.cxx \
@top_srcdir@/src/IGESData/IGESData_IGESType.cxx \
@top_srcdir@/src/IGESData/IGESData_IGESWriter.cxx \
@top_srcdir@/src/IGESData/IGESData_LabelDisplayEntity.cxx \
@top_srcdir@/src/IGESData/IGESData_LevelListEntity.cxx \
@top_srcdir@/src/IGESData/IGESData_LineFontEntity.cxx \
@top_srcdir@/src/IGESData/IGESData_NameEntity.cxx \
@top_srcdir@/src/IGESData/IGESData_ParamCursor.cxx \
@top_srcdir@/src/IGESData/IGESData_ParamReader.cxx \
@top_srcdir@/src/IGESData/IGESData_Protocol.cxx \
@top_srcdir@/src/IGESData/IGESData_ReadWriteModule.cxx \
@top_srcdir@/src/IGESData/IGESData_SingleParentEntity.cxx \
@top_srcdir@/src/IGESData/IGESData_SpecificModule.cxx \
@top_srcdir@/src/IGESData/IGESData_ToolLocation.cxx \
@top_srcdir@/src/IGESData/IGESData_TransfEntity.cxx \
@top_srcdir@/src/IGESData/IGESData_UndefinedEntity.cxx \
@top_srcdir@/src/IGESData/IGESData_ViewKindEntity.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs_AssociativityDef.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs_AttributeDef.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs_AttributeTable.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs_GeneralModule.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs_GenericData.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs_MacroDef.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs_Protocol.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs_ReadWriteModule.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs_SpecificModule.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs_TabularData.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs_ToolAssociativityDef.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs_ToolAttributeDef.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs_ToolAttributeTable.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs_ToolGenericData.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs_ToolMacroDef.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs_ToolTabularData.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs_ToolUnitsData.cxx \
@top_srcdir@/src/IGESDefs/IGESDefs_UnitsData.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_AngularDimension.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_BasicDimension.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_CenterLine.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_CurveDimension.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_DiameterDimension.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_DimensionDisplayData.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_DimensionTolerance.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_DimensionUnits.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_DimensionedGeometry.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_FlagNote.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_GeneralLabel.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_GeneralModule.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_GeneralNote.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_GeneralSymbol.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_LeaderArrow.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_LinearDimension.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_NewDimensionedGeometry.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_NewGeneralNote.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_OrdinateDimension.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_PointDimension.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_Protocol.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_RadiusDimension.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ReadWriteModule.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_Section.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_SectionedArea.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_SpecificModule.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolAngularDimension.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolBasicDimension.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolCenterLine.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolCurveDimension.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolDiameterDimension.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolDimensionDisplayData.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolDimensionTolerance.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolDimensionUnits.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolDimensionedGeometry.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolFlagNote.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolGeneralLabel.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolGeneralNote.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolGeneralSymbol.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolLeaderArrow.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolLinearDimension.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolNewDimensionedGeometry.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolNewGeneralNote.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolOrdinateDimension.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolPointDimension.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolRadiusDimension.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolSection.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolSectionedArea.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_ToolWitnessLine.cxx \
@top_srcdir@/src/IGESDimen/IGESDimen_WitnessLine.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_CircArraySubfigure.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_ConnectPoint.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_Drawing.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_DrawingWithRotation.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_GeneralModule.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_LabelDisplay.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_NetworkSubfigure.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_NetworkSubfigureDef.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_PerspectiveView.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_Planar.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_Protocol.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_ReadWriteModule.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_RectArraySubfigure.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_SegmentedViewsVisible.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_SpecificModule.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_ToolCircArraySubfigure.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_ToolConnectPoint.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_ToolDrawing.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_ToolDrawingWithRotation.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_ToolLabelDisplay.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_ToolNetworkSubfigure.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_ToolNetworkSubfigureDef.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_ToolPerspectiveView.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_ToolPlanar.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_ToolRectArraySubfigure.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_ToolSegmentedViewsVisible.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_ToolView.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_ToolViewsVisible.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_ToolViewsVisibleWithAttr.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_View.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_ViewsVisible.cxx \
@top_srcdir@/src/IGESDraw/IGESDraw_ViewsVisibleWithAttr.cxx \
@top_srcdir@/src/IGESFile/IGESFile_Read.cxx \
@top_srcdir@/src/IGESFile/analiges.c \
@top_srcdir@/src/IGESFile/igesread.c \
@top_srcdir@/src/IGESFile/liriges.c \
@top_srcdir@/src/IGESFile/structiges.c \
@top_srcdir@/src/IGESGeom/IGESGeom.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_BSplineCurve.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_BSplineSurface.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_Boundary.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_BoundedSurface.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_CircularArc.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_CompositeCurve.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ConicArc.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_CopiousData.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_CurveOnSurface.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_Direction.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_Flash.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_GeneralModule.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_Line.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_OffsetCurve.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_OffsetSurface.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_Plane.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_Point.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_Protocol.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ReadWriteModule.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_RuledSurface.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_SpecificModule.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_SplineCurve.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_SplineSurface.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_SurfaceOfRevolution.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_TabulatedCylinder.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolBSplineCurve.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolBSplineSurface.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolBoundary.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolBoundedSurface.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolCircularArc.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolCompositeCurve.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolConicArc.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolCopiousData.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolCurveOnSurface.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolDirection.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolFlash.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolLine.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolOffsetCurve.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolOffsetSurface.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolPlane.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolPoint.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolRuledSurface.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolSplineCurve.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolSplineSurface.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolSurfaceOfRevolution.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolTabulatedCylinder.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolTransformationMatrix.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_ToolTrimmedSurface.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_TransformationMatrix.cxx \
@top_srcdir@/src/IGESGeom/IGESGeom_TrimmedSurface.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_Color.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_DefinitionLevel.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_DrawingSize.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_DrawingUnits.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_GeneralModule.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_HighLight.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_IntercharacterSpacing.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_LineFontDefPattern.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_LineFontDefTemplate.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_LineFontPredefined.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_NominalSize.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_Pick.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_Protocol.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_ReadWriteModule.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_SpecificModule.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_TextDisplayTemplate.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_TextFontDef.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_ToolColor.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_ToolDefinitionLevel.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_ToolDrawingSize.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_ToolDrawingUnits.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_ToolHighLight.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_ToolIntercharacterSpacing.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_ToolLineFontDefPattern.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_ToolLineFontDefTemplate.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_ToolLineFontPredefined.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_ToolNominalSize.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_ToolPick.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_ToolTextDisplayTemplate.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_ToolTextFontDef.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_ToolUniformRectGrid.cxx \
@top_srcdir@/src/IGESGraph/IGESGraph_UniformRectGrid.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_Activator.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_AddFileComment.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_AddGroup.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_AutoCorrect.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_ChangeLevelList.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_ChangeLevelNumber.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_ComputeStatus.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_CounterOfLevelNumber.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_DispPerDrawing.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_DispPerSingleView.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_Dumper.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_EditDirPart.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_EditHeader.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_FloatFormat.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_IGESName.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_IGESTypeForm.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_RebuildDrawings.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_RebuildGroups.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_RemoveCurves.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SelectBasicGeom.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SelectBypassGroup.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SelectBypassSubfigure.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SelectDrawingFrom.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SelectFaces.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SelectFromDrawing.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SelectFromSingleView.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SelectLevelNumber.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SelectName.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SelectPCurves.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SelectSingleViewFrom.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SelectSubordinate.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SelectVisibleStatus.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SetGlobalParameter.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SetLabel.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SetVersion5.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SignColor.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SignLevelNumber.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SignStatus.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_SplineToBSpline.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_UpdateCreationDate.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_UpdateFileName.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_UpdateLastChange.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_ViewSorter.cxx \
@top_srcdir@/src/IGESSelect/IGESSelect_WorkLibrary.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_Block.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_BooleanTree.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ConeFrustum.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ConicalSurface.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_Cylinder.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_CylindricalSurface.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_EdgeList.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_Ellipsoid.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_Face.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_GeneralModule.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_Loop.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ManifoldSolid.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_PlaneSurface.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_Protocol.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ReadWriteModule.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_RightAngularWedge.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_SelectedComponent.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_Shell.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_SolidAssembly.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_SolidInstance.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_SolidOfLinearExtrusion.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_SolidOfRevolution.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_SpecificModule.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_Sphere.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_SphericalSurface.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolBlock.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolBooleanTree.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolConeFrustum.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolConicalSurface.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolCylinder.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolCylindricalSurface.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolEdgeList.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolEllipsoid.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolFace.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolLoop.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolManifoldSolid.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolPlaneSurface.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolRightAngularWedge.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolSelectedComponent.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolShell.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolSolidAssembly.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolSolidInstance.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolSolidOfLinearExtrusion.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolSolidOfRevolution.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolSphere.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolSphericalSurface.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolToroidalSurface.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolTorus.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToolVertexList.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_TopoBuilder.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_ToroidalSurface.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_Torus.cxx \
@top_srcdir@/src/IGESSolid/IGESSolid_VertexList.cxx \
@top_srcdir@/src/IGESToBRep/IGESToBRep.cxx \
@top_srcdir@/src/IGESToBRep/IGESToBRep_Actor.cxx \
@top_srcdir@/src/IGESToBRep/IGESToBRep_AlgoContainer.cxx \
@top_srcdir@/src/IGESToBRep/IGESToBRep_BRepEntity.cxx \
@top_srcdir@/src/IGESToBRep/IGESToBRep_BasicCurve.cxx \
@top_srcdir@/src/IGESToBRep/IGESToBRep_BasicSurface.cxx \
@top_srcdir@/src/IGESToBRep/IGESToBRep_CurveAndSurface.cxx \
@top_srcdir@/src/IGESToBRep/IGESToBRep_IGESBoundary.cxx \
@top_srcdir@/src/IGESToBRep/IGESToBRep_Reader.cxx \
@top_srcdir@/src/IGESToBRep/IGESToBRep_ToolContainer.cxx \
@top_srcdir@/src/IGESToBRep/IGESToBRep_TopoCurve.cxx \
@top_srcdir@/src/IGESToBRep/IGESToBRep_TopoSurface.cxx

