# Makefile.am for Open Cascade toolkit TKXSBase
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/Interface : @top_srcdir@/src/Interface: \
@top_srcdir@/drv/Transfer : @top_srcdir@/src/Transfer: \
@top_srcdir@/drv/IFGraph : @top_srcdir@/src/IFGraph: \
@top_srcdir@/drv/IFSelect : @top_srcdir@/src/IFSelect: \
@top_srcdir@/drv/TransferBRep : @top_srcdir@/src/TransferBRep: \
@top_srcdir@/drv/XSControl : @top_srcdir@/src/XSControl: \
@top_srcdir@/drv/StepData : @top_srcdir@/src/StepData: \
@top_srcdir@/drv/StepFile : @top_srcdir@/src/StepFile: \
@top_srcdir@/drv/HeaderSection : @top_srcdir@/src/HeaderSection: \
@top_srcdir@/drv/RWHeaderSection : @top_srcdir@/src/RWHeaderSection: \
@top_srcdir@/drv/APIHeaderSection : @top_srcdir@/src/APIHeaderSection: \
@top_srcdir@/drv/StepSelect : @top_srcdir@/src/StepSelect: \
@top_srcdir@/drv/UnitsMethods : @top_srcdir@/src/UnitsMethods: \
@top_srcdir@/drv/XSAlgo : @top_srcdir@/src/XSAlgo: \
@top_srcdir@/drv/LibCtl : @top_srcdir@/src/LibCtl: \
@top_srcdir@/drv/MoniTool : @top_srcdir@/src/MoniTool


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/Interface -I@top_srcdir@/src/Interface \
-I@top_srcdir@/drv/Transfer -I@top_srcdir@/src/Transfer \
-I@top_srcdir@/drv/IFGraph -I@top_srcdir@/src/IFGraph \
-I@top_srcdir@/drv/IFSelect -I@top_srcdir@/src/IFSelect \
-I@top_srcdir@/drv/TransferBRep -I@top_srcdir@/src/TransferBRep \
-I@top_srcdir@/drv/XSControl -I@top_srcdir@/src/XSControl \
-I@top_srcdir@/drv/StepData -I@top_srcdir@/src/StepData \
-I@top_srcdir@/drv/StepFile -I@top_srcdir@/src/StepFile \
-I@top_srcdir@/drv/HeaderSection -I@top_srcdir@/src/HeaderSection \
-I@top_srcdir@/drv/RWHeaderSection -I@top_srcdir@/src/RWHeaderSection \
-I@top_srcdir@/drv/APIHeaderSection -I@top_srcdir@/src/APIHeaderSection \
-I@top_srcdir@/drv/StepSelect -I@top_srcdir@/src/StepSelect \
-I@top_srcdir@/drv/UnitsMethods -I@top_srcdir@/src/UnitsMethods \
-I@top_srcdir@/drv/XSAlgo -I@top_srcdir@/src/XSAlgo \
-I@top_srcdir@/drv/LibCtl -I@top_srcdir@/src/LibCtl \
-I@top_srcdir@/drv/MoniTool -I@top_srcdir@/src/MoniTool


lib_LTLIBRARIES=libTKXSBase.la

libTKXSBase_la_LIBADD = \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../TKShHealing/libTKShHealing.la \
../TKBRep/libTKBRep.la \
../TKGeomBase/libTKGeomBase.la \
../TKTopAlgo/libTKTopAlgo.la \
$(STLPort_LIB) 

libTKXSBase_la_SOURCES = \
@top_srcdir@/drv/IFSelect/IFSelect_HSeqOfSelection_0.cxx \
@top_srcdir@/drv/IFSelect/IFSelect_SequenceNodeOfSequenceOfAppliedModifiers_0.cxx \
@top_srcdir@/drv/IFSelect/IFSelect_SequenceNodeOfSequenceOfGeneralModifier_0.cxx \
@top_srcdir@/drv/IFSelect/IFSelect_SequenceNodeOfSequenceOfInterfaceModel_0.cxx \
@top_srcdir@/drv/IFSelect/IFSelect_SequenceNodeOfTSeqOfDispatch_0.cxx \
@top_srcdir@/drv/IFSelect/IFSelect_SequenceNodeOfTSeqOfSelection_0.cxx \
@top_srcdir@/drv/IFSelect/IFSelect_SequenceOfAppliedModifiers_0.cxx \
@top_srcdir@/drv/IFSelect/IFSelect_SequenceOfGeneralModifier_0.cxx \
@top_srcdir@/drv/IFSelect/IFSelect_SequenceOfInterfaceModel_0.cxx \
@top_srcdir@/drv/IFSelect/IFSelect_TSeqOfDispatch_0.cxx \
@top_srcdir@/drv/IFSelect/IFSelect_TSeqOfSelection_0.cxx \
@top_srcdir@/drv/Interface/Interface_Array1OfFileParameter_0.cxx \
@top_srcdir@/drv/Interface/Interface_Array1OfHAsciiString_0.cxx \
@top_srcdir@/drv/Interface/Interface_CheckFailure_0.cxx \
@top_srcdir@/drv/Interface/Interface_DataMapIteratorOfDataMapOfTransientInteger_0.cxx \
@top_srcdir@/drv/Interface/Interface_DataMapNodeOfDataMapOfTransientInteger_0.cxx \
@top_srcdir@/drv/Interface/Interface_DataMapOfTransientInteger_0.cxx \
@top_srcdir@/drv/Interface/Interface_GeneralLib_0.cxx \
@top_srcdir@/drv/Interface/Interface_GlobalNodeOfGeneralLib_0.cxx \
@top_srcdir@/drv/Interface/Interface_GlobalNodeOfReaderLib_0.cxx \
@top_srcdir@/drv/Interface/Interface_HArray1OfHAsciiString_0.cxx \
@top_srcdir@/drv/Interface/Interface_HSequenceOfCheck_0.cxx \
@top_srcdir@/drv/Interface/Interface_IndexedMapNodeOfIndexedMapOfAsciiString_0.cxx \
@top_srcdir@/drv/Interface/Interface_IndexedMapOfAsciiString_0.cxx \
@top_srcdir@/drv/Interface/Interface_InterfaceError_0.cxx \
@top_srcdir@/drv/Interface/Interface_InterfaceMismatch_0.cxx \
@top_srcdir@/drv/Interface/Interface_NodeOfGeneralLib_0.cxx \
@top_srcdir@/drv/Interface/Interface_NodeOfReaderLib_0.cxx \
@top_srcdir@/drv/Interface/Interface_ReaderLib_0.cxx \
@top_srcdir@/drv/Interface/Interface_SequenceNodeOfSequenceOfCheck_0.cxx \
@top_srcdir@/drv/Interface/Interface_SequenceOfCheck_0.cxx \
@top_srcdir@/drv/MoniTool/MoniTool_DataMapIteratorOfDataMapOfShapeTransient_0.cxx \
@top_srcdir@/drv/MoniTool/MoniTool_DataMapIteratorOfDataMapOfTimer_0.cxx \
@top_srcdir@/drv/MoniTool/MoniTool_DataMapNodeOfDataMapOfShapeTransient_0.cxx \
@top_srcdir@/drv/MoniTool/MoniTool_DataMapNodeOfDataMapOfTimer_0.cxx \
@top_srcdir@/drv/MoniTool/MoniTool_DataMapOfShapeTransient_0.cxx \
@top_srcdir@/drv/MoniTool/MoniTool_DataMapOfTimer_0.cxx \
@top_srcdir@/drv/MoniTool/MoniTool_HSequenceOfElement_0.cxx \
@top_srcdir@/drv/MoniTool/MoniTool_IndexedDataMapNodeOfIndexedDataMapOfShapeTransient_0.cxx \
@top_srcdir@/drv/MoniTool/MoniTool_IndexedDataMapOfShapeTransient_0.cxx \
@top_srcdir@/drv/MoniTool/MoniTool_SequenceNodeOfSequenceOfElement_0.cxx \
@top_srcdir@/drv/MoniTool/MoniTool_SequenceOfElement_0.cxx \
@top_srcdir@/drv/MoniTool/MoniTool_TransientElem_0.cxx \
@top_srcdir@/drv/StepData/StepData_Array1OfField_0.cxx \
@top_srcdir@/drv/StepData/StepData_FileRecognizer_0.cxx \
@top_srcdir@/drv/StepData/StepData_GlobalNodeOfWriterLib_0.cxx \
@top_srcdir@/drv/StepData/StepData_HArray1OfField_0.cxx \
@top_srcdir@/drv/StepData/StepData_NodeOfWriterLib_0.cxx \
@top_srcdir@/drv/StepData/StepData_WriterLib_0.cxx \
@top_srcdir@/drv/StepFile/lex.step.c \
@top_srcdir@/drv/StepFile/step.tab.c \
@top_srcdir@/drv/StepSelect/StepSelect_FileModifier_0.cxx \
@top_srcdir@/drv/StepSelect/StepSelect_ModelModifier_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_ActorOfProcessForFinder_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_ActorOfProcessForTransient_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_HSequenceOfBinder_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_HSequenceOfFinder_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_IndexedDataMapNodeOfTransferMapOfProcessForFinder_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_IndexedDataMapNodeOfTransferMapOfProcessForTransient_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_IteratorOfProcessForFinder_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_IteratorOfProcessForTransient_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_ProcessForFinder_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_ProcessForTransient_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_SequenceNodeOfSequenceOfBinder_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_SequenceNodeOfSequenceOfFinder_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_SequenceOfBinder_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_SequenceOfFinder_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_TransferDeadLoop_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_TransferFailure_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_TransferMapOfProcessForFinder_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_TransferMapOfProcessForTransient_0.cxx \
@top_srcdir@/drv/Transfer/Transfer_TransientMapper_0.cxx \
@top_srcdir@/drv/TransferBRep/TransferBRep_BinderOfShape_0.cxx \
@top_srcdir@/drv/TransferBRep/TransferBRep_HSequenceOfTransferResultInfo_0.cxx \
@top_srcdir@/drv/TransferBRep/TransferBRep_OrientedShapeMapper_0.cxx \
@top_srcdir@/drv/TransferBRep/TransferBRep_SequenceNodeOfSequenceOfTransferResultInfo_0.cxx \
@top_srcdir@/drv/TransferBRep/TransferBRep_SequenceOfTransferResultInfo_0.cxx \
@top_srcdir@/drv/TransferBRep/TransferBRep_ShapeMapper_0.cxx \
@top_srcdir@/src/APIHeaderSection/APIHeaderSection_EditHeader.cxx \
@top_srcdir@/src/APIHeaderSection/APIHeaderSection_MakeHeader.cxx \
@top_srcdir@/src/HeaderSection/HeaderSection.cxx \
@top_srcdir@/src/HeaderSection/HeaderSection_FileDescription.cxx \
@top_srcdir@/src/HeaderSection/HeaderSection_FileName.cxx \
@top_srcdir@/src/HeaderSection/HeaderSection_FileSchema.cxx \
@top_srcdir@/src/HeaderSection/HeaderSection_HeaderRecognizer.cxx \
@top_srcdir@/src/HeaderSection/HeaderSection_Protocol.cxx \
@top_srcdir@/src/IFGraph/IFGraph_AllConnected.cxx \
@top_srcdir@/src/IFGraph/IFGraph_AllShared.cxx \
@top_srcdir@/src/IFGraph/IFGraph_Articulations.cxx \
@top_srcdir@/src/IFGraph/IFGraph_Compare.cxx \
@top_srcdir@/src/IFGraph/IFGraph_ConnectedComponants.cxx \
@top_srcdir@/src/IFGraph/IFGraph_Cumulate.cxx \
@top_srcdir@/src/IFGraph/IFGraph_Cycles.cxx \
@top_srcdir@/src/IFGraph/IFGraph_ExternalSources.cxx \
@top_srcdir@/src/IFGraph/IFGraph_SCRoots.cxx \
@top_srcdir@/src/IFGraph/IFGraph_StrongComponants.cxx \
@top_srcdir@/src/IFGraph/IFGraph_SubPartsIterator.cxx \
@top_srcdir@/src/IFSelect/IFSelect.cxx \
@top_srcdir@/src/IFSelect/IFSelect_Act.cxx \
@top_srcdir@/src/IFSelect/IFSelect_ActFunc.cxx \
@top_srcdir@/src/IFSelect/IFSelect_Activator.cxx \
@top_srcdir@/src/IFSelect/IFSelect_AppliedModifiers.cxx \
@top_srcdir@/src/IFSelect/IFSelect_BasicDumper.cxx \
@top_srcdir@/src/IFSelect/IFSelect_CheckCounter.cxx \
@top_srcdir@/src/IFSelect/IFSelect_ContextModif.cxx \
@top_srcdir@/src/IFSelect/IFSelect_ContextWrite.cxx \
@top_srcdir@/src/IFSelect/IFSelect_DispGlobal.cxx \
@top_srcdir@/src/IFSelect/IFSelect_DispPerCount.cxx \
@top_srcdir@/src/IFSelect/IFSelect_DispPerFiles.cxx \
@top_srcdir@/src/IFSelect/IFSelect_DispPerOne.cxx \
@top_srcdir@/src/IFSelect/IFSelect_DispPerSignature.cxx \
@top_srcdir@/src/IFSelect/IFSelect_Dispatch.cxx \
@top_srcdir@/src/IFSelect/IFSelect_EditForm.cxx \
@top_srcdir@/src/IFSelect/IFSelect_Editor.cxx \
@top_srcdir@/src/IFSelect/IFSelect_Functions.cxx \
@top_srcdir@/src/IFSelect/IFSelect_GeneralModifier.cxx \
@top_srcdir@/src/IFSelect/IFSelect_GraphCounter.cxx \
@top_srcdir@/src/IFSelect/IFSelect_IntParam.cxx \
@top_srcdir@/src/IFSelect/IFSelect_ListEditor.cxx \
@top_srcdir@/src/IFSelect/IFSelect_ModelCopier.cxx \
@top_srcdir@/src/IFSelect/IFSelect_ModifEditForm.cxx \
@top_srcdir@/src/IFSelect/IFSelect_ModifReorder.cxx \
@top_srcdir@/src/IFSelect/IFSelect_Modifier.cxx \
@top_srcdir@/src/IFSelect/IFSelect_PacketList.cxx \
@top_srcdir@/src/IFSelect/IFSelect_ParamEditor.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectAnyList.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectAnyType.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectBase.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectCombine.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectControl.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectDeduct.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectDiff.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectEntityNumber.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectErrorEntities.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectExplore.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectExtract.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectFlag.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectInList.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectIncorrectEntities.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectIntersection.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectModelEntities.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectModelRoots.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectPointed.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectRange.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectRootComps.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectRoots.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectSent.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectShared.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectSharing.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectSignature.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectSignedShared.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectSignedSharing.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectSuite.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectType.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectUnion.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectUnknownEntities.cxx \
@top_srcdir@/src/IFSelect/IFSelect_Selection.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SelectionIterator.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SessionDumper.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SessionFile.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SessionPilot.cxx \
@top_srcdir@/src/IFSelect/IFSelect_ShareOut.cxx \
@top_srcdir@/src/IFSelect/IFSelect_ShareOutResult.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SignAncestor.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SignCategory.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SignCounter.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SignMultiple.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SignType.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SignValidity.cxx \
@top_srcdir@/src/IFSelect/IFSelect_Signature.cxx \
@top_srcdir@/src/IFSelect/IFSelect_SignatureList.cxx \
@top_srcdir@/src/IFSelect/IFSelect_TransformStandard.cxx \
@top_srcdir@/src/IFSelect/IFSelect_Transformer.cxx \
@top_srcdir@/src/IFSelect/IFSelect_WorkLibrary.cxx \
@top_srcdir@/src/IFSelect/IFSelect_WorkSession.cxx \
@top_srcdir@/src/Interface/Interface_BitMap.cxx \
@top_srcdir@/src/Interface/Interface_Category.cxx \
@top_srcdir@/src/Interface/Interface_Check.cxx \
@top_srcdir@/src/Interface/Interface_CheckIterator.cxx \
@top_srcdir@/src/Interface/Interface_CheckTool.cxx \
@top_srcdir@/src/Interface/Interface_CopyControl.cxx \
@top_srcdir@/src/Interface/Interface_CopyMap.cxx \
@top_srcdir@/src/Interface/Interface_CopyTool.cxx \
@top_srcdir@/src/Interface/Interface_EntityCluster.cxx \
@top_srcdir@/src/Interface/Interface_EntityIterator.cxx \
@top_srcdir@/src/Interface/Interface_EntityList.cxx \
@top_srcdir@/src/Interface/Interface_FileParameter.cxx \
@top_srcdir@/src/Interface/Interface_FileReaderData.cxx \
@top_srcdir@/src/Interface/Interface_FileReaderTool.cxx \
@top_srcdir@/src/Interface/Interface_FloatWriter.cxx \
@top_srcdir@/src/Interface/Interface_GTool.cxx \
@top_srcdir@/src/Interface/Interface_GeneralModule.cxx \
@top_srcdir@/src/Interface/Interface_Graph.cxx \
@top_srcdir@/src/Interface/Interface_GraphContent.cxx \
@top_srcdir@/src/Interface/Interface_HGraph.cxx \
@top_srcdir@/src/Interface/Interface_IntList.cxx \
@top_srcdir@/src/Interface/Interface_IntVal.cxx \
@top_srcdir@/src/Interface/Interface_InterfaceModel.cxx \
@top_srcdir@/src/Interface/Interface_LineBuffer.cxx \
@top_srcdir@/src/Interface/Interface_MSG.cxx \
@top_srcdir@/src/Interface/Interface_MapAsciiStringHasher.cxx \
@top_srcdir@/src/Interface/Interface_ParamList.cxx \
@top_srcdir@/src/Interface/Interface_ParamSet.cxx \
@top_srcdir@/src/Interface/Interface_Protocol.cxx \
@top_srcdir@/src/Interface/Interface_ReaderModule.cxx \
@top_srcdir@/src/Interface/Interface_ReportEntity.cxx \
@top_srcdir@/src/Interface/Interface_STAT.cxx \
@top_srcdir@/src/Interface/Interface_ShareFlags.cxx \
@top_srcdir@/src/Interface/Interface_ShareTool.cxx \
@top_srcdir@/src/Interface/Interface_SignLabel.cxx \
@top_srcdir@/src/Interface/Interface_SignType.cxx \
@top_srcdir@/src/Interface/Interface_Static.cxx \
@top_srcdir@/src/Interface/Interface_StaticStandards.cxx \
@top_srcdir@/src/Interface/Interface_TypedValue.cxx \
@top_srcdir@/src/Interface/Interface_UndefinedContent.cxx \
@top_srcdir@/src/MoniTool/MoniTool_AttrList.cxx \
@top_srcdir@/src/MoniTool/MoniTool_CaseData.cxx \
@top_srcdir@/src/MoniTool/MoniTool_DataInfo.cxx \
@top_srcdir@/src/MoniTool/MoniTool_ElemHasher.cxx \
@top_srcdir@/src/MoniTool/MoniTool_Element.cxx \
@top_srcdir@/src/MoniTool/MoniTool_IntVal.cxx \
@top_srcdir@/src/MoniTool/MoniTool_MTHasher.cxx \
@top_srcdir@/src/MoniTool/MoniTool_OptValue.cxx \
@top_srcdir@/src/MoniTool/MoniTool_Option.cxx \
@top_srcdir@/src/MoniTool/MoniTool_Profile.cxx \
@top_srcdir@/src/MoniTool/MoniTool_RealVal.cxx \
@top_srcdir@/src/MoniTool/MoniTool_SignShape.cxx \
@top_srcdir@/src/MoniTool/MoniTool_SignText.cxx \
@top_srcdir@/src/MoniTool/MoniTool_Stat.cxx \
@top_srcdir@/src/MoniTool/MoniTool_Timer.cxx \
@top_srcdir@/src/MoniTool/MoniTool_TimerSentry.cxx \
@top_srcdir@/src/MoniTool/MoniTool_TypedValue.cxx \
@top_srcdir@/src/MoniTool/MoniTool_ValueInterpret.cxx \
@top_srcdir@/src/MoniTool/MoniTool_ValueSatisfies.cxx \
@top_srcdir@/src/RWHeaderSection/RWHeaderSection.cxx \
@top_srcdir@/src/RWHeaderSection/RWHeaderSection_GeneralModule.cxx \
@top_srcdir@/src/RWHeaderSection/RWHeaderSection_RWFileDescription.cxx \
@top_srcdir@/src/RWHeaderSection/RWHeaderSection_RWFileName.cxx \
@top_srcdir@/src/RWHeaderSection/RWHeaderSection_RWFileSchema.cxx \
@top_srcdir@/src/RWHeaderSection/RWHeaderSection_ReadWriteModule.cxx \
@top_srcdir@/src/StepData/StepData.cxx \
@top_srcdir@/src/StepData/StepData_DefaultGeneral.cxx \
@top_srcdir@/src/StepData/StepData_DescrGeneral.cxx \
@top_srcdir@/src/StepData/StepData_DescrProtocol.cxx \
@top_srcdir@/src/StepData/StepData_DescrReadWrite.cxx \
@top_srcdir@/src/StepData/StepData_Described.cxx \
@top_srcdir@/src/StepData/StepData_ECDescr.cxx \
@top_srcdir@/src/StepData/StepData_EDescr.cxx \
@top_srcdir@/src/StepData/StepData_ESDescr.cxx \
@top_srcdir@/src/StepData/StepData_EnumTool.cxx \
@top_srcdir@/src/StepData/StepData_Field.cxx \
@top_srcdir@/src/StepData/StepData_FieldList.cxx \
@top_srcdir@/src/StepData/StepData_FieldList1.cxx \
@top_srcdir@/src/StepData/StepData_FieldListD.cxx \
@top_srcdir@/src/StepData/StepData_FieldListN.cxx \
@top_srcdir@/src/StepData/StepData_FileProtocol.cxx \
@top_srcdir@/src/StepData/StepData_FreeFormEntity.cxx \
@top_srcdir@/src/StepData/StepData_GeneralModule.cxx \
@top_srcdir@/src/StepData/StepData_HeaderTool.cxx \
@top_srcdir@/src/StepData/StepData_PDescr.cxx \
@top_srcdir@/src/StepData/StepData_Plex.cxx \
@top_srcdir@/src/StepData/StepData_Protocol.cxx \
@top_srcdir@/src/StepData/StepData_ReadWriteModule.cxx \
@top_srcdir@/src/StepData/StepData_SelectArrReal.cxx \
@top_srcdir@/src/StepData/StepData_SelectInt.cxx \
@top_srcdir@/src/StepData/StepData_SelectMember.cxx \
@top_srcdir@/src/StepData/StepData_SelectNamed.cxx \
@top_srcdir@/src/StepData/StepData_SelectReal.cxx \
@top_srcdir@/src/StepData/StepData_SelectType.cxx \
@top_srcdir@/src/StepData/StepData_Simple.cxx \
@top_srcdir@/src/StepData/StepData_StepDumper.cxx \
@top_srcdir@/src/StepData/StepData_StepModel.cxx \
@top_srcdir@/src/StepData/StepData_StepReaderData.cxx \
@top_srcdir@/src/StepData/StepData_StepReaderTool.cxx \
@top_srcdir@/src/StepData/StepData_StepWriter.cxx \
@top_srcdir@/src/StepData/StepData_UndefinedEntity.cxx \
@top_srcdir@/src/StepFile/StepFile_CallFailure.cxx \
@top_srcdir@/src/StepFile/StepFile_Read.cxx \
@top_srcdir@/src/StepFile/stepread.c \
@top_srcdir@/src/StepSelect/StepSelect_Activator.cxx \
@top_srcdir@/src/StepSelect/StepSelect_FloatFormat.cxx \
@top_srcdir@/src/StepSelect/StepSelect_StepType.cxx \
@top_srcdir@/src/StepSelect/StepSelect_WorkLibrary.cxx \
@top_srcdir@/src/Transfer/Transfer_ActorDispatch.cxx \
@top_srcdir@/src/Transfer/Transfer_ActorOfFinderProcess.cxx \
@top_srcdir@/src/Transfer/Transfer_ActorOfTransientProcess.cxx \
@top_srcdir@/src/Transfer/Transfer_Binder.cxx \
@top_srcdir@/src/Transfer/Transfer_BinderOfTransientInteger.cxx \
@top_srcdir@/src/Transfer/Transfer_DataInfo.cxx \
@top_srcdir@/src/Transfer/Transfer_DispatchControl.cxx \
@top_srcdir@/src/Transfer/Transfer_FindHasher.cxx \
@top_srcdir@/src/Transfer/Transfer_Finder.cxx \
@top_srcdir@/src/Transfer/Transfer_FinderProcess.cxx \
@top_srcdir@/src/Transfer/Transfer_MapContainer.cxx \
@top_srcdir@/src/Transfer/Transfer_MultipleBinder.cxx \
@top_srcdir@/src/Transfer/Transfer_ResultFromModel.cxx \
@top_srcdir@/src/Transfer/Transfer_ResultFromTransient.cxx \
@top_srcdir@/src/Transfer/Transfer_SimpleBinderOfTransient.cxx \
@top_srcdir@/src/Transfer/Transfer_TransferDispatch.cxx \
@top_srcdir@/src/Transfer/Transfer_TransferInput.cxx \
@top_srcdir@/src/Transfer/Transfer_TransferIterator.cxx \
@top_srcdir@/src/Transfer/Transfer_TransferOutput.cxx \
@top_srcdir@/src/Transfer/Transfer_TransientListBinder.cxx \
@top_srcdir@/src/Transfer/Transfer_TransientProcess.cxx \
@top_srcdir@/src/Transfer/Transfer_VoidBinder.cxx \
@top_srcdir@/src/TransferBRep/TransferBRep.cxx \
@top_srcdir@/src/TransferBRep/TransferBRep_Reader.cxx \
@top_srcdir@/src/TransferBRep/TransferBRep_ShapeBinder.cxx \
@top_srcdir@/src/TransferBRep/TransferBRep_ShapeInfo.cxx \
@top_srcdir@/src/TransferBRep/TransferBRep_ShapeListBinder.cxx \
@top_srcdir@/src/TransferBRep/TransferBRep_TransferResultInfo.cxx \
@top_srcdir@/src/UnitsMethods/UnitsMethods.cxx \
@top_srcdir@/src/XSAlgo/XSAlgo.cxx \
@top_srcdir@/src/XSAlgo/XSAlgo_AlgoContainer.cxx \
@top_srcdir@/src/XSAlgo/XSAlgo_ToolContainer.cxx \
@top_srcdir@/src/XSControl/XSControl.cxx \
@top_srcdir@/src/XSControl/XSControl_ConnectedShapes.cxx \
@top_srcdir@/src/XSControl/XSControl_Controller.cxx \
@top_srcdir@/src/XSControl/XSControl_FuncShape.cxx \
@top_srcdir@/src/XSControl/XSControl_Functions.cxx \
@top_srcdir@/src/XSControl/XSControl_Reader.cxx \
@top_srcdir@/src/XSControl/XSControl_SelectForTransfer.cxx \
@top_srcdir@/src/XSControl/XSControl_SignTransferStatus.cxx \
@top_srcdir@/src/XSControl/XSControl_TransferReader.cxx \
@top_srcdir@/src/XSControl/XSControl_TransferWriter.cxx \
@top_srcdir@/src/XSControl/XSControl_Utils.cxx \
@top_srcdir@/src/XSControl/XSControl_Vars.cxx \
@top_srcdir@/src/XSControl/XSControl_WorkSession.cxx \
@top_srcdir@/src/XSControl/XSControl_Writer.cxx

