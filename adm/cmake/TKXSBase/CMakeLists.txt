project(TKXSBase)

if (WIN32)
  list( APPEND TKXSBase_PRECOMPILED_DEFS "-D__Interface_DLL" )
  list( APPEND TKXSBase_PRECOMPILED_DEFS "-D__Transfer_DLL" )
  list( APPEND TKXSBase_PRECOMPILED_DEFS "-D__IFGraph_DLL" )
  list( APPEND TKXSBase_PRECOMPILED_DEFS "-D__IFSelect_DLL" )
  list( APPEND TKXSBase_PRECOMPILED_DEFS "-D__TransferBRep_DLL" )
  list( APPEND TKXSBase_PRECOMPILED_DEFS "-D__XSControl_DLL" )
  list( APPEND TKXSBase_PRECOMPILED_DEFS "-D__StepData_DLL" )
  list( APPEND TKXSBase_PRECOMPILED_DEFS "-D__StepFile_DLL" )
  list( APPEND TKXSBase_PRECOMPILED_DEFS "-D__HeaderSection_DLL" )
  list( APPEND TKXSBase_PRECOMPILED_DEFS "-D__RWHeaderSection_DLL" )
  list( APPEND TKXSBase_PRECOMPILED_DEFS "-D__APIHeaderSection_DLL" )
  list( APPEND TKXSBase_PRECOMPILED_DEFS "-D__StepSelect_DLL" )
  list( APPEND TKXSBase_PRECOMPILED_DEFS "-D__UnitsMethods_DLL" )
  list( APPEND TKXSBase_PRECOMPILED_DEFS "-D__XSAlgo_DLL" )
  list( APPEND TKXSBase_PRECOMPILED_DEFS "-D__LibCtl_DLL" )
  list( APPEND TKXSBase_PRECOMPILED_DEFS "-D__MoniTool_DLL" )
  string( REGEX REPLACE ";" " " TKXSBase_PRECOMPILED_DEFS "${TKXSBase_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKXSBase_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../drv/Interface" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../src/Interface" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../drv/Transfer" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../src/Transfer" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../drv/IFGraph" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../src/IFGraph" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../drv/IFSelect" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../src/IFSelect" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../drv/TransferBRep" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../src/TransferBRep" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../drv/XSControl" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../src/XSControl" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../drv/StepData" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../src/StepData" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../drv/StepFile" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../src/StepFile" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../drv/HeaderSection" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../src/HeaderSection" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../drv/RWHeaderSection" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../src/RWHeaderSection" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../drv/APIHeaderSection" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../src/APIHeaderSection" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../drv/StepSelect" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../src/StepSelect" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../drv/UnitsMethods" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../src/UnitsMethods" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../drv/XSAlgo" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../src/XSAlgo" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../drv/LibCtl" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../src/LibCtl" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../drv/MoniTool" )
  list( APPEND TKXSBase_COMPILER_DIRECTORIES "../../../src/MoniTool" )

if (WIN32)
else()
endif()

  list( APPEND TKXSBase_USED_LIBS TKBRep )
  list( APPEND TKXSBase_USED_LIBS TKernel )
  list( APPEND TKXSBase_USED_LIBS TKMath )
  list( APPEND TKXSBase_USED_LIBS TKG2d )
  list( APPEND TKXSBase_USED_LIBS TKG3d )
  list( APPEND TKXSBase_USED_LIBS TKTopAlgo )
  list( APPEND TKXSBase_USED_LIBS TKGeomBase )
  list( APPEND TKXSBase_USED_LIBS TKShHealing )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_Array1OfFileParameter_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_Array1OfFileParameter_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_Array1OfHAsciiString_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_Array1OfHAsciiString_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_CheckFailure_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_CheckFailure_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_DataMapIteratorOfDataMapOfTransientInteger_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_DataMapIteratorOfDataMapOfTransientInteger_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_DataMapNodeOfDataMapOfTransientInteger_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_DataMapNodeOfDataMapOfTransientInteger_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_DataMapOfTransientInteger_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_DataMapOfTransientInteger_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_GeneralLib_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_GeneralLib_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_GlobalNodeOfGeneralLib_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_GlobalNodeOfGeneralLib_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_GlobalNodeOfReaderLib_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_GlobalNodeOfReaderLib_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_HArray1OfHAsciiString_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_HArray1OfHAsciiString_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_HSequenceOfCheck_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_HSequenceOfCheck_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_IndexedMapNodeOfIndexedMapOfAsciiString_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_IndexedMapNodeOfIndexedMapOfAsciiString_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_IndexedMapOfAsciiString_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_IndexedMapOfAsciiString_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_InterfaceError_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_InterfaceError_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_InterfaceMismatch_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_InterfaceMismatch_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_NodeOfGeneralLib_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_NodeOfGeneralLib_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_NodeOfReaderLib_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_NodeOfReaderLib_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_ReaderLib_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_ReaderLib_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_SequenceNodeOfSequenceOfCheck_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_SequenceNodeOfSequenceOfCheck_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Interface/Interface_SequenceOfCheck_0.cxx" )
  SOURCE_GROUP (Interface FILES "../../../drv/Interface/Interface_SequenceOfCheck_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_BitMap.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_BitMap.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_Category.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_Category.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_Check.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_Check.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_CheckIterator.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_CheckIterator.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_CheckTool.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_CheckTool.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_CopyControl.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_CopyControl.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_CopyMap.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_CopyMap.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_CopyTool.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_CopyTool.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_EntityCluster.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_EntityCluster.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_EntityIterator.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_EntityIterator.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_EntityList.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_EntityList.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_FileParameter.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_FileParameter.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_FileReaderData.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_FileReaderData.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_FileReaderTool.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_FileReaderTool.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_FloatWriter.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_FloatWriter.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_GTool.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_GTool.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_GeneralModule.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_GeneralModule.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_Graph.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_Graph.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_GraphContent.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_GraphContent.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_HGraph.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_HGraph.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_IntList.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_IntList.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_IntVal.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_IntVal.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_InterfaceModel.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_InterfaceModel.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_LineBuffer.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_LineBuffer.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_MSG.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_MSG.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_MapAsciiStringHasher.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_MapAsciiStringHasher.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_ParamList.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_ParamList.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_ParamSet.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_ParamSet.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_Protocol.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_Protocol.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_ReaderModule.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_ReaderModule.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_ReportEntity.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_ReportEntity.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_STAT.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_STAT.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_ShareFlags.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_ShareFlags.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_ShareTool.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_ShareTool.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_SignLabel.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_SignLabel.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_SignType.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_SignType.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_Static.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_Static.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_StaticStandards.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_StaticStandards.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_TypedValue.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_TypedValue.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Interface/Interface_UndefinedContent.cxx" )
  SOURCE_GROUP (Interface FILES "../../../src/Interface/Interface_UndefinedContent.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_ActorOfProcessForFinder_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_ActorOfProcessForFinder_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_ActorOfProcessForTransient_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_ActorOfProcessForTransient_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_HSequenceOfBinder_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_HSequenceOfBinder_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_HSequenceOfFinder_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_HSequenceOfFinder_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_IndexedDataMapNodeOfTransferMapOfProcessForFinder_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_IndexedDataMapNodeOfTransferMapOfProcessForFinder_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_IndexedDataMapNodeOfTransferMapOfProcessForTransient_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_IndexedDataMapNodeOfTransferMapOfProcessForTransient_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_IteratorOfProcessForFinder_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_IteratorOfProcessForFinder_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_IteratorOfProcessForTransient_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_IteratorOfProcessForTransient_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_ProcessForFinder_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_ProcessForFinder_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_ProcessForTransient_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_ProcessForTransient_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_SequenceNodeOfSequenceOfBinder_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_SequenceNodeOfSequenceOfBinder_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_SequenceNodeOfSequenceOfFinder_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_SequenceNodeOfSequenceOfFinder_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_SequenceOfBinder_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_SequenceOfBinder_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_SequenceOfFinder_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_SequenceOfFinder_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_TransferDeadLoop_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_TransferDeadLoop_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_TransferFailure_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_TransferFailure_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_TransferMapOfProcessForFinder_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_TransferMapOfProcessForFinder_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_TransferMapOfProcessForTransient_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_TransferMapOfProcessForTransient_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/Transfer/Transfer_TransientMapper_0.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../drv/Transfer/Transfer_TransientMapper_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_ActorDispatch.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_ActorDispatch.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_ActorOfFinderProcess.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_ActorOfFinderProcess.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_ActorOfTransientProcess.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_ActorOfTransientProcess.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_Binder.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_Binder.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_BinderOfTransientInteger.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_BinderOfTransientInteger.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_DataInfo.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_DataInfo.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_DispatchControl.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_DispatchControl.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_FindHasher.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_FindHasher.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_Finder.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_Finder.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_FinderProcess.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_FinderProcess.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_MapContainer.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_MapContainer.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_MultipleBinder.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_MultipleBinder.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_ResultFromModel.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_ResultFromModel.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_ResultFromTransient.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_ResultFromTransient.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_SimpleBinderOfTransient.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_SimpleBinderOfTransient.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_TransferDispatch.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_TransferDispatch.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_TransferInput.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_TransferInput.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_TransferIterator.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_TransferIterator.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_TransferOutput.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_TransferOutput.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_TransientListBinder.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_TransientListBinder.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_TransientProcess.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_TransientProcess.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/Transfer/Transfer_VoidBinder.cxx" )
  SOURCE_GROUP (Transfer FILES "../../../src/Transfer/Transfer_VoidBinder.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFGraph/IFGraph_AllConnected.cxx" )
  SOURCE_GROUP (IFGraph FILES "../../../src/IFGraph/IFGraph_AllConnected.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFGraph/IFGraph_AllShared.cxx" )
  SOURCE_GROUP (IFGraph FILES "../../../src/IFGraph/IFGraph_AllShared.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFGraph/IFGraph_Articulations.cxx" )
  SOURCE_GROUP (IFGraph FILES "../../../src/IFGraph/IFGraph_Articulations.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFGraph/IFGraph_Compare.cxx" )
  SOURCE_GROUP (IFGraph FILES "../../../src/IFGraph/IFGraph_Compare.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFGraph/IFGraph_ConnectedComponants.cxx" )
  SOURCE_GROUP (IFGraph FILES "../../../src/IFGraph/IFGraph_ConnectedComponants.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFGraph/IFGraph_Cumulate.cxx" )
  SOURCE_GROUP (IFGraph FILES "../../../src/IFGraph/IFGraph_Cumulate.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFGraph/IFGraph_Cycles.cxx" )
  SOURCE_GROUP (IFGraph FILES "../../../src/IFGraph/IFGraph_Cycles.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFGraph/IFGraph_ExternalSources.cxx" )
  SOURCE_GROUP (IFGraph FILES "../../../src/IFGraph/IFGraph_ExternalSources.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFGraph/IFGraph_SCRoots.cxx" )
  SOURCE_GROUP (IFGraph FILES "../../../src/IFGraph/IFGraph_SCRoots.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFGraph/IFGraph_StrongComponants.cxx" )
  SOURCE_GROUP (IFGraph FILES "../../../src/IFGraph/IFGraph_StrongComponants.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFGraph/IFGraph_SubPartsIterator.cxx" )
  SOURCE_GROUP (IFGraph FILES "../../../src/IFGraph/IFGraph_SubPartsIterator.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/IFSelect/IFSelect_HSeqOfSelection_0.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../drv/IFSelect/IFSelect_HSeqOfSelection_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/IFSelect/IFSelect_SequenceNodeOfSequenceOfAppliedModifiers_0.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../drv/IFSelect/IFSelect_SequenceNodeOfSequenceOfAppliedModifiers_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/IFSelect/IFSelect_SequenceNodeOfSequenceOfGeneralModifier_0.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../drv/IFSelect/IFSelect_SequenceNodeOfSequenceOfGeneralModifier_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/IFSelect/IFSelect_SequenceNodeOfSequenceOfInterfaceModel_0.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../drv/IFSelect/IFSelect_SequenceNodeOfSequenceOfInterfaceModel_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/IFSelect/IFSelect_SequenceNodeOfTSeqOfDispatch_0.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../drv/IFSelect/IFSelect_SequenceNodeOfTSeqOfDispatch_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/IFSelect/IFSelect_SequenceNodeOfTSeqOfSelection_0.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../drv/IFSelect/IFSelect_SequenceNodeOfTSeqOfSelection_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/IFSelect/IFSelect_SequenceOfAppliedModifiers_0.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../drv/IFSelect/IFSelect_SequenceOfAppliedModifiers_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/IFSelect/IFSelect_SequenceOfGeneralModifier_0.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../drv/IFSelect/IFSelect_SequenceOfGeneralModifier_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/IFSelect/IFSelect_SequenceOfInterfaceModel_0.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../drv/IFSelect/IFSelect_SequenceOfInterfaceModel_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/IFSelect/IFSelect_TSeqOfDispatch_0.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../drv/IFSelect/IFSelect_TSeqOfDispatch_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/IFSelect/IFSelect_TSeqOfSelection_0.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../drv/IFSelect/IFSelect_TSeqOfSelection_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_Act.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_Act.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_ActFunc.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_ActFunc.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_Activator.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_Activator.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_AppliedModifiers.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_AppliedModifiers.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_BasicDumper.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_BasicDumper.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_CheckCounter.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_CheckCounter.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_ContextModif.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_ContextModif.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_ContextWrite.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_ContextWrite.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_DispGlobal.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_DispGlobal.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_DispPerCount.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_DispPerCount.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_DispPerFiles.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_DispPerFiles.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_DispPerOne.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_DispPerOne.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_DispPerSignature.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_DispPerSignature.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_Dispatch.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_Dispatch.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_EditForm.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_EditForm.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_Editor.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_Editor.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_Functions.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_Functions.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_GeneralModifier.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_GeneralModifier.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_GraphCounter.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_GraphCounter.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_IntParam.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_IntParam.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_ListEditor.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_ListEditor.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_ModelCopier.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_ModelCopier.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_ModifEditForm.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_ModifEditForm.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_ModifReorder.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_ModifReorder.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_Modifier.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_Modifier.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_PacketList.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_PacketList.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_ParamEditor.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_ParamEditor.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectAnyList.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectAnyList.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectAnyType.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectAnyType.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectBase.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectBase.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectCombine.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectCombine.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectControl.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectControl.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectDeduct.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectDeduct.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectDiff.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectDiff.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectEntityNumber.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectEntityNumber.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectErrorEntities.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectErrorEntities.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectExplore.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectExplore.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectExtract.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectExtract.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectFlag.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectFlag.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectInList.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectInList.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectIncorrectEntities.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectIncorrectEntities.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectIntersection.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectIntersection.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectModelEntities.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectModelEntities.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectModelRoots.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectModelRoots.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectPointed.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectPointed.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectRange.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectRange.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectRootComps.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectRootComps.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectRoots.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectRoots.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectSent.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectSent.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectShared.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectShared.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectSharing.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectSharing.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectSignature.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectSignature.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectSignedShared.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectSignedShared.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectSignedSharing.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectSignedSharing.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectSuite.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectSuite.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectType.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectType.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectUnion.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectUnion.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectUnknownEntities.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectUnknownEntities.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_Selection.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_Selection.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SelectionIterator.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SelectionIterator.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SessionDumper.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SessionDumper.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SessionFile.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SessionFile.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SessionPilot.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SessionPilot.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_ShareOut.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_ShareOut.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_ShareOutResult.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_ShareOutResult.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SignAncestor.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SignAncestor.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SignCategory.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SignCategory.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SignCounter.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SignCounter.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SignMultiple.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SignMultiple.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SignType.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SignType.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SignValidity.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SignValidity.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_Signature.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_Signature.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_SignatureList.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_SignatureList.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_TransformStandard.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_TransformStandard.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_Transformer.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_Transformer.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_WorkLibrary.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_WorkLibrary.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/IFSelect/IFSelect_WorkSession.cxx" )
  SOURCE_GROUP (IFSelect FILES "../../../src/IFSelect/IFSelect_WorkSession.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/TransferBRep/TransferBRep_BinderOfShape_0.cxx" )
  SOURCE_GROUP (TransferBRep FILES "../../../drv/TransferBRep/TransferBRep_BinderOfShape_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/TransferBRep/TransferBRep_HSequenceOfTransferResultInfo_0.cxx" )
  SOURCE_GROUP (TransferBRep FILES "../../../drv/TransferBRep/TransferBRep_HSequenceOfTransferResultInfo_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/TransferBRep/TransferBRep_OrientedShapeMapper_0.cxx" )
  SOURCE_GROUP (TransferBRep FILES "../../../drv/TransferBRep/TransferBRep_OrientedShapeMapper_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/TransferBRep/TransferBRep_SequenceNodeOfSequenceOfTransferResultInfo_0.cxx" )
  SOURCE_GROUP (TransferBRep FILES "../../../drv/TransferBRep/TransferBRep_SequenceNodeOfSequenceOfTransferResultInfo_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/TransferBRep/TransferBRep_SequenceOfTransferResultInfo_0.cxx" )
  SOURCE_GROUP (TransferBRep FILES "../../../drv/TransferBRep/TransferBRep_SequenceOfTransferResultInfo_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/TransferBRep/TransferBRep_ShapeMapper_0.cxx" )
  SOURCE_GROUP (TransferBRep FILES "../../../drv/TransferBRep/TransferBRep_ShapeMapper_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/TransferBRep/TransferBRep.cxx" )
  SOURCE_GROUP (TransferBRep FILES "../../../src/TransferBRep/TransferBRep.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/TransferBRep/TransferBRep_Reader.cxx" )
  SOURCE_GROUP (TransferBRep FILES "../../../src/TransferBRep/TransferBRep_Reader.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/TransferBRep/TransferBRep_ShapeBinder.cxx" )
  SOURCE_GROUP (TransferBRep FILES "../../../src/TransferBRep/TransferBRep_ShapeBinder.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/TransferBRep/TransferBRep_ShapeInfo.cxx" )
  SOURCE_GROUP (TransferBRep FILES "../../../src/TransferBRep/TransferBRep_ShapeInfo.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/TransferBRep/TransferBRep_ShapeListBinder.cxx" )
  SOURCE_GROUP (TransferBRep FILES "../../../src/TransferBRep/TransferBRep_ShapeListBinder.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/TransferBRep/TransferBRep_TransferResultInfo.cxx" )
  SOURCE_GROUP (TransferBRep FILES "../../../src/TransferBRep/TransferBRep_TransferResultInfo.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/XSControl/XSControl.cxx" )
  SOURCE_GROUP (XSControl FILES "../../../src/XSControl/XSControl.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/XSControl/XSControl_ConnectedShapes.cxx" )
  SOURCE_GROUP (XSControl FILES "../../../src/XSControl/XSControl_ConnectedShapes.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/XSControl/XSControl_Controller.cxx" )
  SOURCE_GROUP (XSControl FILES "../../../src/XSControl/XSControl_Controller.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/XSControl/XSControl_FuncShape.cxx" )
  SOURCE_GROUP (XSControl FILES "../../../src/XSControl/XSControl_FuncShape.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/XSControl/XSControl_Functions.cxx" )
  SOURCE_GROUP (XSControl FILES "../../../src/XSControl/XSControl_Functions.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/XSControl/XSControl_Reader.cxx" )
  SOURCE_GROUP (XSControl FILES "../../../src/XSControl/XSControl_Reader.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/XSControl/XSControl_SelectForTransfer.cxx" )
  SOURCE_GROUP (XSControl FILES "../../../src/XSControl/XSControl_SelectForTransfer.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/XSControl/XSControl_SignTransferStatus.cxx" )
  SOURCE_GROUP (XSControl FILES "../../../src/XSControl/XSControl_SignTransferStatus.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/XSControl/XSControl_TransferReader.cxx" )
  SOURCE_GROUP (XSControl FILES "../../../src/XSControl/XSControl_TransferReader.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/XSControl/XSControl_TransferWriter.cxx" )
  SOURCE_GROUP (XSControl FILES "../../../src/XSControl/XSControl_TransferWriter.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/XSControl/XSControl_Utils.cxx" )
  SOURCE_GROUP (XSControl FILES "../../../src/XSControl/XSControl_Utils.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/XSControl/XSControl_Vars.cxx" )
  SOURCE_GROUP (XSControl FILES "../../../src/XSControl/XSControl_Vars.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/XSControl/XSControl_WorkSession.cxx" )
  SOURCE_GROUP (XSControl FILES "../../../src/XSControl/XSControl_WorkSession.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/XSControl/XSControl_Writer.cxx" )
  SOURCE_GROUP (XSControl FILES "../../../src/XSControl/XSControl_Writer.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/StepData/StepData_Array1OfField_0.cxx" )
  SOURCE_GROUP (StepData FILES "../../../drv/StepData/StepData_Array1OfField_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/StepData/StepData_FileRecognizer_0.cxx" )
  SOURCE_GROUP (StepData FILES "../../../drv/StepData/StepData_FileRecognizer_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/StepData/StepData_GlobalNodeOfWriterLib_0.cxx" )
  SOURCE_GROUP (StepData FILES "../../../drv/StepData/StepData_GlobalNodeOfWriterLib_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/StepData/StepData_HArray1OfField_0.cxx" )
  SOURCE_GROUP (StepData FILES "../../../drv/StepData/StepData_HArray1OfField_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/StepData/StepData_NodeOfWriterLib_0.cxx" )
  SOURCE_GROUP (StepData FILES "../../../drv/StepData/StepData_NodeOfWriterLib_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/StepData/StepData_WriterLib_0.cxx" )
  SOURCE_GROUP (StepData FILES "../../../drv/StepData/StepData_WriterLib_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_DefaultGeneral.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_DefaultGeneral.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_DescrGeneral.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_DescrGeneral.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_DescrProtocol.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_DescrProtocol.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_DescrReadWrite.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_DescrReadWrite.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_Described.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_Described.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_ECDescr.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_ECDescr.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_EDescr.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_EDescr.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_ESDescr.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_ESDescr.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_EnumTool.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_EnumTool.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_Field.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_Field.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_FieldList.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_FieldList.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_FieldList1.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_FieldList1.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_FieldListD.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_FieldListD.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_FieldListN.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_FieldListN.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_FileProtocol.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_FileProtocol.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_FreeFormEntity.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_FreeFormEntity.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_GeneralModule.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_GeneralModule.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_HeaderTool.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_HeaderTool.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_PDescr.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_PDescr.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_Plex.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_Plex.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_Protocol.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_Protocol.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_ReadWriteModule.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_ReadWriteModule.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_SelectArrReal.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_SelectArrReal.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_SelectInt.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_SelectInt.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_SelectMember.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_SelectMember.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_SelectNamed.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_SelectNamed.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_SelectReal.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_SelectReal.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_SelectType.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_SelectType.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_Simple.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_Simple.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_StepDumper.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_StepDumper.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_StepModel.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_StepModel.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_StepReaderData.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_StepReaderData.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_StepReaderTool.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_StepReaderTool.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_StepWriter.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_StepWriter.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepData/StepData_UndefinedEntity.cxx" )
  SOURCE_GROUP (StepData FILES "../../../src/StepData/StepData_UndefinedEntity.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/StepFile/lex.step.c" )
  SOURCE_GROUP (StepFile FILES "../../../drv/StepFile/lex.step.c")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/StepFile/step.tab.c" )
  SOURCE_GROUP (StepFile FILES "../../../drv/StepFile/step.tab.c")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepFile/StepFile_CallFailure.cxx" )
  SOURCE_GROUP (StepFile FILES "../../../src/StepFile/StepFile_CallFailure.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepFile/StepFile_Read.cxx" )
  SOURCE_GROUP (StepFile FILES "../../../src/StepFile/StepFile_Read.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepFile/stepread.c" )
  SOURCE_GROUP (StepFile FILES "../../../src/StepFile/stepread.c")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/HeaderSection/HeaderSection.cxx" )
  SOURCE_GROUP (HeaderSection FILES "../../../src/HeaderSection/HeaderSection.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/HeaderSection/HeaderSection_FileDescription.cxx" )
  SOURCE_GROUP (HeaderSection FILES "../../../src/HeaderSection/HeaderSection_FileDescription.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/HeaderSection/HeaderSection_FileName.cxx" )
  SOURCE_GROUP (HeaderSection FILES "../../../src/HeaderSection/HeaderSection_FileName.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/HeaderSection/HeaderSection_FileSchema.cxx" )
  SOURCE_GROUP (HeaderSection FILES "../../../src/HeaderSection/HeaderSection_FileSchema.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/HeaderSection/HeaderSection_HeaderRecognizer.cxx" )
  SOURCE_GROUP (HeaderSection FILES "../../../src/HeaderSection/HeaderSection_HeaderRecognizer.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/HeaderSection/HeaderSection_Protocol.cxx" )
  SOURCE_GROUP (HeaderSection FILES "../../../src/HeaderSection/HeaderSection_Protocol.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/RWHeaderSection/RWHeaderSection.cxx" )
  SOURCE_GROUP (RWHeaderSection FILES "../../../src/RWHeaderSection/RWHeaderSection.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/RWHeaderSection/RWHeaderSection_GeneralModule.cxx" )
  SOURCE_GROUP (RWHeaderSection FILES "../../../src/RWHeaderSection/RWHeaderSection_GeneralModule.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/RWHeaderSection/RWHeaderSection_RWFileDescription.cxx" )
  SOURCE_GROUP (RWHeaderSection FILES "../../../src/RWHeaderSection/RWHeaderSection_RWFileDescription.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/RWHeaderSection/RWHeaderSection_RWFileName.cxx" )
  SOURCE_GROUP (RWHeaderSection FILES "../../../src/RWHeaderSection/RWHeaderSection_RWFileName.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/RWHeaderSection/RWHeaderSection_RWFileSchema.cxx" )
  SOURCE_GROUP (RWHeaderSection FILES "../../../src/RWHeaderSection/RWHeaderSection_RWFileSchema.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/RWHeaderSection/RWHeaderSection_ReadWriteModule.cxx" )
  SOURCE_GROUP (RWHeaderSection FILES "../../../src/RWHeaderSection/RWHeaderSection_ReadWriteModule.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/APIHeaderSection/APIHeaderSection_EditHeader.cxx" )
  SOURCE_GROUP (APIHeaderSection FILES "../../../src/APIHeaderSection/APIHeaderSection_EditHeader.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/APIHeaderSection/APIHeaderSection_MakeHeader.cxx" )
  SOURCE_GROUP (APIHeaderSection FILES "../../../src/APIHeaderSection/APIHeaderSection_MakeHeader.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/StepSelect/StepSelect_FileModifier_0.cxx" )
  SOURCE_GROUP (StepSelect FILES "../../../drv/StepSelect/StepSelect_FileModifier_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/StepSelect/StepSelect_ModelModifier_0.cxx" )
  SOURCE_GROUP (StepSelect FILES "../../../drv/StepSelect/StepSelect_ModelModifier_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepSelect/StepSelect_Activator.cxx" )
  SOURCE_GROUP (StepSelect FILES "../../../src/StepSelect/StepSelect_Activator.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepSelect/StepSelect_FloatFormat.cxx" )
  SOURCE_GROUP (StepSelect FILES "../../../src/StepSelect/StepSelect_FloatFormat.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepSelect/StepSelect_StepType.cxx" )
  SOURCE_GROUP (StepSelect FILES "../../../src/StepSelect/StepSelect_StepType.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/StepSelect/StepSelect_WorkLibrary.cxx" )
  SOURCE_GROUP (StepSelect FILES "../../../src/StepSelect/StepSelect_WorkLibrary.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/UnitsMethods/UnitsMethods.cxx" )
  SOURCE_GROUP (UnitsMethods FILES "../../../src/UnitsMethods/UnitsMethods.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/XSAlgo/XSAlgo.cxx" )
  SOURCE_GROUP (XSAlgo FILES "../../../src/XSAlgo/XSAlgo.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/XSAlgo/XSAlgo_AlgoContainer.cxx" )
  SOURCE_GROUP (XSAlgo FILES "../../../src/XSAlgo/XSAlgo_AlgoContainer.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/XSAlgo/XSAlgo_ToolContainer.cxx" )
  SOURCE_GROUP (XSAlgo FILES "../../../src/XSAlgo/XSAlgo_ToolContainer.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/MoniTool/MoniTool_DataMapIteratorOfDataMapOfShapeTransient_0.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../drv/MoniTool/MoniTool_DataMapIteratorOfDataMapOfShapeTransient_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/MoniTool/MoniTool_DataMapIteratorOfDataMapOfTimer_0.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../drv/MoniTool/MoniTool_DataMapIteratorOfDataMapOfTimer_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/MoniTool/MoniTool_DataMapNodeOfDataMapOfShapeTransient_0.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../drv/MoniTool/MoniTool_DataMapNodeOfDataMapOfShapeTransient_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/MoniTool/MoniTool_DataMapNodeOfDataMapOfTimer_0.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../drv/MoniTool/MoniTool_DataMapNodeOfDataMapOfTimer_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/MoniTool/MoniTool_DataMapOfShapeTransient_0.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../drv/MoniTool/MoniTool_DataMapOfShapeTransient_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/MoniTool/MoniTool_DataMapOfTimer_0.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../drv/MoniTool/MoniTool_DataMapOfTimer_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/MoniTool/MoniTool_HSequenceOfElement_0.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../drv/MoniTool/MoniTool_HSequenceOfElement_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/MoniTool/MoniTool_IndexedDataMapNodeOfIndexedDataMapOfShapeTransient_0.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../drv/MoniTool/MoniTool_IndexedDataMapNodeOfIndexedDataMapOfShapeTransient_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/MoniTool/MoniTool_IndexedDataMapOfShapeTransient_0.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../drv/MoniTool/MoniTool_IndexedDataMapOfShapeTransient_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/MoniTool/MoniTool_SequenceNodeOfSequenceOfElement_0.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../drv/MoniTool/MoniTool_SequenceNodeOfSequenceOfElement_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/MoniTool/MoniTool_SequenceOfElement_0.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../drv/MoniTool/MoniTool_SequenceOfElement_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../drv/MoniTool/MoniTool_TransientElem_0.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../drv/MoniTool/MoniTool_TransientElem_0.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_AttrList.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_AttrList.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_CaseData.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_CaseData.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_DataInfo.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_DataInfo.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_ElemHasher.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_ElemHasher.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_Element.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_Element.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_IntVal.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_IntVal.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_MTHasher.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_MTHasher.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_OptValue.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_OptValue.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_Option.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_Option.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_Profile.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_Profile.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_RealVal.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_RealVal.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_SignShape.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_SignShape.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_SignText.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_SignText.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_Stat.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_Stat.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_Timer.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_Timer.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_TimerSentry.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_TimerSentry.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_TypedValue.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_TypedValue.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_ValueInterpret.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_ValueInterpret.cxx")

  list( APPEND TKXSBase_USED_SRCFILES "../../../src/MoniTool/MoniTool_ValueSatisfies.cxx" )
  SOURCE_GROUP (MoniTool FILES "../../../src/MoniTool/MoniTool_ValueSatisfies.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKXSBase)
 add_library( TKXSBase SHARED ${TKXSBase_USED_SRCFILES} )

 set_property(TARGET TKXSBase PROPERTY FOLDER DataExchange)

 install( TARGETS TKXSBase
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKXSBase.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKXSBase PROPERTIES COMPILE_FLAGS "${TKXSBase_PRECOMPILED_DEFS}" )
 include_directories( ${TKXSBase_COMPILER_DIRECTORIES} )
 target_link_libraries( TKXSBase ${TKXSBase_USED_LIBS} )
endif()
