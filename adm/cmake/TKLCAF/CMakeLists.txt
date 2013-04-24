project(TKLCAF)

if (WIN32)
  list( APPEND TKLCAF_PRECOMPILED_DEFS "-D__TDF_DLL" )
  list( APPEND TKLCAF_PRECOMPILED_DEFS "-D__TDataStd_DLL" )
  list( APPEND TKLCAF_PRECOMPILED_DEFS "-D__TFunction_DLL" )
  list( APPEND TKLCAF_PRECOMPILED_DEFS "-D__TDocStd_DLL" )
  list( APPEND TKLCAF_PRECOMPILED_DEFS "-D__AppStdL_DLL" )
  string( REGEX REPLACE ";" " " TKLCAF_PRECOMPILED_DEFS "${TKLCAF_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKLCAF_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKLCAF_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKLCAF_COMPILER_DIRECTORIES "../../../drv/TDF" )
  list( APPEND TKLCAF_COMPILER_DIRECTORIES "../../../src/TDF" )
  list( APPEND TKLCAF_COMPILER_DIRECTORIES "../../../drv/TDataStd" )
  list( APPEND TKLCAF_COMPILER_DIRECTORIES "../../../src/TDataStd" )
  list( APPEND TKLCAF_COMPILER_DIRECTORIES "../../../drv/TFunction" )
  list( APPEND TKLCAF_COMPILER_DIRECTORIES "../../../src/TFunction" )
  list( APPEND TKLCAF_COMPILER_DIRECTORIES "../../../drv/TDocStd" )
  list( APPEND TKLCAF_COMPILER_DIRECTORIES "../../../src/TDocStd" )
  list( APPEND TKLCAF_COMPILER_DIRECTORIES "../../../drv/AppStdL" )
  list( APPEND TKLCAF_COMPILER_DIRECTORIES "../../../src/AppStdL" )

if (WIN32)
else()
endif()

  list( APPEND TKLCAF_USED_LIBS TKCDF )
  list( APPEND TKLCAF_USED_LIBS TKernel )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_AttributeArray1_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_AttributeArray1_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_AttributeDataMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_AttributeDataMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_AttributeDeltaList_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_AttributeDeltaList_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_AttributeDoubleMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_AttributeDoubleMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_AttributeIndexedMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_AttributeIndexedMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_AttributeList_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_AttributeList_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_AttributeMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_AttributeMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_AttributeSequence_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_AttributeSequence_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_DataMapIteratorOfAttributeDataMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_DataMapIteratorOfAttributeDataMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_DataMapIteratorOfLabelDataMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_DataMapIteratorOfLabelDataMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_DataMapIteratorOfLabelIntegerMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_DataMapIteratorOfLabelIntegerMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_DataMapIteratorOfLabelLabelMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_DataMapIteratorOfLabelLabelMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_DataMapNodeOfAttributeDataMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_DataMapNodeOfAttributeDataMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_DataMapNodeOfLabelDataMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_DataMapNodeOfLabelDataMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_DataMapNodeOfLabelIntegerMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_DataMapNodeOfLabelIntegerMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_DataMapNodeOfLabelLabelMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_DataMapNodeOfLabelLabelMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_DeltaList_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_DeltaList_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_DoubleMapIteratorOfAttributeDoubleMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_DoubleMapIteratorOfAttributeDoubleMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_DoubleMapIteratorOfGUIDProgIDMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_DoubleMapIteratorOfGUIDProgIDMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_DoubleMapIteratorOfLabelDoubleMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_DoubleMapIteratorOfLabelDoubleMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_DoubleMapNodeOfAttributeDoubleMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_DoubleMapNodeOfAttributeDoubleMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_DoubleMapNodeOfGUIDProgIDMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_DoubleMapNodeOfGUIDProgIDMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_DoubleMapNodeOfLabelDoubleMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_DoubleMapNodeOfLabelDoubleMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_GUIDProgIDMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_GUIDProgIDMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_HAttributeArray1_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_HAttributeArray1_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_IDList_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_IDList_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_IDMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_IDMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_IndexedMapNodeOfAttributeIndexedMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_IndexedMapNodeOfAttributeIndexedMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_IndexedMapNodeOfLabelIndexedMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_IndexedMapNodeOfLabelIndexedMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_LabelDataMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_LabelDataMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_LabelDoubleMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_LabelDoubleMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_LabelIndexedMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_LabelIndexedMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_LabelIntegerMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_LabelIntegerMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_LabelLabelMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_LabelLabelMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_LabelList_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_LabelList_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_LabelMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_LabelMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_LabelSequence_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_LabelSequence_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_ListIteratorOfAttributeDeltaList_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_ListIteratorOfAttributeDeltaList_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_ListIteratorOfAttributeList_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_ListIteratorOfAttributeList_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_ListIteratorOfDeltaList_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_ListIteratorOfDeltaList_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_ListIteratorOfIDList_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_ListIteratorOfIDList_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_ListIteratorOfLabelList_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_ListIteratorOfLabelList_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_ListNodeOfAttributeDeltaList_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_ListNodeOfAttributeDeltaList_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_ListNodeOfAttributeList_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_ListNodeOfAttributeList_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_ListNodeOfDeltaList_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_ListNodeOfDeltaList_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_ListNodeOfIDList_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_ListNodeOfIDList_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_ListNodeOfLabelList_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_ListNodeOfLabelList_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_MapIteratorOfAttributeMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_MapIteratorOfAttributeMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_MapIteratorOfIDMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_MapIteratorOfIDMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_MapIteratorOfLabelMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_MapIteratorOfLabelMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_SequenceNodeOfAttributeSequence_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_SequenceNodeOfAttributeSequence_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_SequenceNodeOfLabelSequence_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_SequenceNodeOfLabelSequence_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_StdMapNodeOfAttributeMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_StdMapNodeOfAttributeMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_StdMapNodeOfIDMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_StdMapNodeOfIDMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDF/TDF_StdMapNodeOfLabelMap_0.cxx" )
  SOURCE_GROUP (TDF FILES "../../../drv/TDF/TDF_StdMapNodeOfLabelMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_Attribute.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_Attribute.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_AttributeDelta.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_AttributeDelta.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_AttributeIterator.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_AttributeIterator.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_ChildIDIterator.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_ChildIDIterator.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_ChildIterator.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_ChildIterator.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_ClosureMode.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_ClosureMode.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_ClosureTool.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_ClosureTool.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_ComparisonTool.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_ComparisonTool.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_CopyLabel.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_CopyLabel.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_CopyTool.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_CopyTool.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_Data.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_Data.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_DataSet.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_DataSet.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_DefaultDeltaOnModification.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_DefaultDeltaOnModification.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_DefaultDeltaOnRemoval.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_DefaultDeltaOnRemoval.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_Delta.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_Delta.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_DeltaOnAddition.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_DeltaOnAddition.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_DeltaOnForget.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_DeltaOnForget.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_DeltaOnModification.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_DeltaOnModification.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_DeltaOnRemoval.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_DeltaOnRemoval.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_DeltaOnResume.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_DeltaOnResume.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_IDFilter.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_IDFilter.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_Label.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_Label.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_LabelMapHasher.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_LabelMapHasher.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_LabelNode.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_LabelNode.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_Reference.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_Reference.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_RelocationTable.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_RelocationTable.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_TagSource.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_TagSource.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_Tool.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_Tool.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDF/TDF_Transaction.cxx" )
  SOURCE_GROUP (TDF FILES "../../../src/TDF/TDF_Transaction.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_DataMapIteratorOfDataMapOfStringByte_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_DataMapIteratorOfDataMapOfStringByte_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_DataMapIteratorOfDataMapOfStringHArray1OfInteger_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_DataMapIteratorOfDataMapOfStringHArray1OfInteger_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_DataMapIteratorOfDataMapOfStringHArray1OfReal_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_DataMapIteratorOfDataMapOfStringHArray1OfReal_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_DataMapIteratorOfDataMapOfStringReal_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_DataMapIteratorOfDataMapOfStringReal_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_DataMapIteratorOfDataMapOfStringString_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_DataMapIteratorOfDataMapOfStringString_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_DataMapNodeOfDataMapOfStringByte_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_DataMapNodeOfDataMapOfStringByte_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_DataMapNodeOfDataMapOfStringHArray1OfInteger_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_DataMapNodeOfDataMapOfStringHArray1OfInteger_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_DataMapNodeOfDataMapOfStringHArray1OfReal_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_DataMapNodeOfDataMapOfStringHArray1OfReal_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_DataMapNodeOfDataMapOfStringReal_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_DataMapNodeOfDataMapOfStringReal_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_DataMapNodeOfDataMapOfStringString_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_DataMapNodeOfDataMapOfStringString_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_DataMapOfStringByte_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_DataMapOfStringByte_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_DataMapOfStringHArray1OfInteger_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_DataMapOfStringHArray1OfInteger_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_DataMapOfStringHArray1OfReal_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_DataMapOfStringHArray1OfReal_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_DataMapOfStringReal_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_DataMapOfStringReal_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_DataMapOfStringString_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_DataMapOfStringString_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_HLabelArray1_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_HLabelArray1_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_LabelArray1_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_LabelArray1_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_ListIteratorOfListOfByte_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_ListIteratorOfListOfByte_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_ListIteratorOfListOfExtendedString_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_ListIteratorOfListOfExtendedString_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_ListNodeOfListOfByte_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_ListNodeOfListOfByte_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_ListNodeOfListOfExtendedString_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_ListNodeOfListOfExtendedString_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_ListOfByte_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_ListOfByte_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDataStd/TDataStd_ListOfExtendedString_0.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../drv/TDataStd/TDataStd_ListOfExtendedString_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_AsciiString.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_AsciiString.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_BooleanArray.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_BooleanArray.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_BooleanList.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_BooleanList.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_ByteArray.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_ByteArray.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_ChildNodeIterator.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_ChildNodeIterator.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_Comment.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_Comment.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_Current.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_Current.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_DeltaOnModificationOfByteArray.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_DeltaOnModificationOfByteArray.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_DeltaOnModificationOfExtStringArray.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_DeltaOnModificationOfExtStringArray.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_DeltaOnModificationOfIntArray.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_DeltaOnModificationOfIntArray.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_DeltaOnModificationOfIntPackedMap.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_DeltaOnModificationOfIntPackedMap.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_DeltaOnModificationOfRealArray.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_DeltaOnModificationOfRealArray.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_Directory.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_Directory.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_Expression.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_Expression.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_ExtStringArray.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_ExtStringArray.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_ExtStringList.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_ExtStringList.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_HDataMapOfStringByte.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_HDataMapOfStringByte.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_HDataMapOfStringHArray1OfInteger.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_HDataMapOfStringHArray1OfInteger.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_HDataMapOfStringHArray1OfReal.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_HDataMapOfStringHArray1OfReal.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_HDataMapOfStringInteger.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_HDataMapOfStringInteger.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_HDataMapOfStringReal.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_HDataMapOfStringReal.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_HDataMapOfStringString.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_HDataMapOfStringString.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_IntPackedMap.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_IntPackedMap.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_Integer.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_Integer.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_IntegerArray.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_IntegerArray.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_IntegerList.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_IntegerList.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_Name.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_Name.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_NamedData.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_NamedData.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_NoteBook.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_NoteBook.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_Real.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_Real.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_RealArray.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_RealArray.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_RealList.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_RealList.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_ReferenceArray.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_ReferenceArray.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_ReferenceList.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_ReferenceList.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_Relation.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_Relation.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_Tick.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_Tick.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_TreeNode.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_TreeNode.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_UAttribute.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_UAttribute.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDataStd/TDataStd_Variable.cxx" )
  SOURCE_GROUP (TDataStd FILES "../../../src/TDataStd/TDataStd_Variable.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TFunction/TFunction_Array1OfDataMapOfGUIDDriver_0.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../drv/TFunction/TFunction_Array1OfDataMapOfGUIDDriver_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TFunction/TFunction_DataMapIteratorOfDataMapOfGUIDDriver_0.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../drv/TFunction/TFunction_DataMapIteratorOfDataMapOfGUIDDriver_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TFunction/TFunction_DataMapIteratorOfDataMapOfLabelListOfLabel_0.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../drv/TFunction/TFunction_DataMapIteratorOfDataMapOfLabelListOfLabel_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TFunction/TFunction_DataMapNodeOfDataMapOfGUIDDriver_0.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../drv/TFunction/TFunction_DataMapNodeOfDataMapOfGUIDDriver_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TFunction/TFunction_DataMapNodeOfDataMapOfLabelListOfLabel_0.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../drv/TFunction/TFunction_DataMapNodeOfDataMapOfLabelListOfLabel_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TFunction/TFunction_DataMapOfGUIDDriver_0.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../drv/TFunction/TFunction_DataMapOfGUIDDriver_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TFunction/TFunction_DataMapOfLabelListOfLabel_0.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../drv/TFunction/TFunction_DataMapOfLabelListOfLabel_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TFunction/TFunction_DoubleMapIteratorOfDoubleMapOfIntegerLabel_0.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../drv/TFunction/TFunction_DoubleMapIteratorOfDoubleMapOfIntegerLabel_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TFunction/TFunction_DoubleMapNodeOfDoubleMapOfIntegerLabel_0.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../drv/TFunction/TFunction_DoubleMapNodeOfDoubleMapOfIntegerLabel_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TFunction/TFunction_DoubleMapOfIntegerLabel_0.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../drv/TFunction/TFunction_DoubleMapOfIntegerLabel_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TFunction/TFunction_HArray1OfDataMapOfGUIDDriver_0.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../drv/TFunction/TFunction_HArray1OfDataMapOfGUIDDriver_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TFunction/TFunction_Driver.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../src/TFunction/TFunction_Driver.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TFunction/TFunction_DriverTable.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../src/TFunction/TFunction_DriverTable.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TFunction/TFunction_Function.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../src/TFunction/TFunction_Function.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TFunction/TFunction_GraphNode.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../src/TFunction/TFunction_GraphNode.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TFunction/TFunction_IFunction.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../src/TFunction/TFunction_IFunction.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TFunction/TFunction_Iterator.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../src/TFunction/TFunction_Iterator.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TFunction/TFunction_Logbook.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../src/TFunction/TFunction_Logbook.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TFunction/TFunction_Scope.cxx" )
  SOURCE_GROUP (TFunction FILES "../../../src/TFunction/TFunction_Scope.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDocStd/TDocStd_DataMapIteratorOfLabelIDMapDataMap_0.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../drv/TDocStd/TDocStd_DataMapIteratorOfLabelIDMapDataMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDocStd/TDocStd_DataMapNodeOfLabelIDMapDataMap_0.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../drv/TDocStd/TDocStd_DataMapNodeOfLabelIDMapDataMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDocStd/TDocStd_LabelIDMapDataMap_0.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../drv/TDocStd/TDocStd_LabelIDMapDataMap_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDocStd/TDocStd_SequenceNodeOfSequenceOfApplicationDelta_0.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../drv/TDocStd/TDocStd_SequenceNodeOfSequenceOfApplicationDelta_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDocStd/TDocStd_SequenceNodeOfSequenceOfDocument_0.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../drv/TDocStd/TDocStd_SequenceNodeOfSequenceOfDocument_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDocStd/TDocStd_SequenceOfApplicationDelta_0.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../drv/TDocStd/TDocStd_SequenceOfApplicationDelta_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../drv/TDocStd/TDocStd_SequenceOfDocument_0.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../drv/TDocStd/TDocStd_SequenceOfDocument_0.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDocStd/TDocStd.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../src/TDocStd/TDocStd.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDocStd/TDocStd_Application.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../src/TDocStd/TDocStd_Application.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDocStd/TDocStd_ApplicationDelta.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../src/TDocStd/TDocStd_ApplicationDelta.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDocStd/TDocStd_CompoundDelta.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../src/TDocStd/TDocStd_CompoundDelta.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDocStd/TDocStd_Context.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../src/TDocStd/TDocStd_Context.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDocStd/TDocStd_Document.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../src/TDocStd/TDocStd_Document.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDocStd/TDocStd_Modified.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../src/TDocStd/TDocStd_Modified.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDocStd/TDocStd_MultiTransactionManager.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../src/TDocStd/TDocStd_MultiTransactionManager.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDocStd/TDocStd_Owner.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../src/TDocStd/TDocStd_Owner.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDocStd/TDocStd_PathParser.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../src/TDocStd/TDocStd_PathParser.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDocStd/TDocStd_XLink.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../src/TDocStd/TDocStd_XLink.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDocStd/TDocStd_XLinkIterator.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../src/TDocStd/TDocStd_XLinkIterator.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDocStd/TDocStd_XLinkRoot.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../src/TDocStd/TDocStd_XLinkRoot.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/TDocStd/TDocStd_XLinkTool.cxx" )
  SOURCE_GROUP (TDocStd FILES "../../../src/TDocStd/TDocStd_XLinkTool.cxx")

  list( APPEND TKLCAF_USED_SRCFILES "../../../src/AppStdL/AppStdL_Application.cxx" )
  SOURCE_GROUP (AppStdL FILES "../../../src/AppStdL/AppStdL_Application.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKLCAF)
 add_library( TKLCAF SHARED ${TKLCAF_USED_SRCFILES} )

 set_property(TARGET TKLCAF PROPERTY FOLDER ApplicationFramework)

 install( TARGETS TKLCAF
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKLCAF.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKLCAF PROPERTIES COMPILE_FLAGS "${TKLCAF_PRECOMPILED_DEFS}" )
 include_directories( ${TKLCAF_COMPILER_DIRECTORIES} )
 target_link_libraries( TKLCAF ${TKLCAF_USED_LIBS} )
endif()
