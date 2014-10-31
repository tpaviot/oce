# Makefile.am for Open Cascade toolkit TKLCAF
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/TDF : @top_srcdir@/src/TDF: \
@top_srcdir@/drv/TDataStd : @top_srcdir@/src/TDataStd: \
@top_srcdir@/drv/TFunction : @top_srcdir@/src/TFunction: \
@top_srcdir@/drv/TDocStd : @top_srcdir@/src/TDocStd: \
@top_srcdir@/drv/AppStdL : @top_srcdir@/src/AppStdL


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/TDF -I@top_srcdir@/src/TDF \
-I@top_srcdir@/drv/TDataStd -I@top_srcdir@/src/TDataStd \
-I@top_srcdir@/drv/TFunction -I@top_srcdir@/src/TFunction \
-I@top_srcdir@/drv/TDocStd -I@top_srcdir@/src/TDocStd \
-I@top_srcdir@/drv/AppStdL -I@top_srcdir@/src/AppStdL


lib_LTLIBRARIES=libTKLCAF.la

libTKLCAF_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKCDF/libTKCDF.la \
../TKernel/libTKernel.la \
$(STLPort_LIB) 

libTKLCAF_la_SOURCES = \
@top_srcdir@/drv/TDF/TDF_AttributeArray1_0.cxx \
@top_srcdir@/drv/TDF/TDF_AttributeDataMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_AttributeDeltaList_0.cxx \
@top_srcdir@/drv/TDF/TDF_AttributeDoubleMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_AttributeIndexedMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_AttributeList_0.cxx \
@top_srcdir@/drv/TDF/TDF_AttributeMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_AttributeSequence_0.cxx \
@top_srcdir@/drv/TDF/TDF_DataMapIteratorOfAttributeDataMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_DataMapIteratorOfLabelDataMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_DataMapIteratorOfLabelIntegerMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_DataMapNodeOfAttributeDataMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_DataMapNodeOfLabelDataMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_DataMapNodeOfLabelIntegerMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_DeltaList_0.cxx \
@top_srcdir@/drv/TDF/TDF_DoubleMapIteratorOfAttributeDoubleMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_DoubleMapIteratorOfGUIDProgIDMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_DoubleMapIteratorOfLabelDoubleMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_DoubleMapNodeOfAttributeDoubleMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_DoubleMapNodeOfGUIDProgIDMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_DoubleMapNodeOfLabelDoubleMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_GUIDProgIDMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_HAttributeArray1_0.cxx \
@top_srcdir@/drv/TDF/TDF_IDList_0.cxx \
@top_srcdir@/drv/TDF/TDF_IDMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_IndexedMapNodeOfAttributeIndexedMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_IndexedMapNodeOfLabelIndexedMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_LabelDataMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_LabelDoubleMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_LabelIndexedMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_LabelIntegerMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_LabelList_0.cxx \
@top_srcdir@/drv/TDF/TDF_LabelMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_LabelSequence_0.cxx \
@top_srcdir@/drv/TDF/TDF_ListIteratorOfAttributeDeltaList_0.cxx \
@top_srcdir@/drv/TDF/TDF_ListIteratorOfAttributeList_0.cxx \
@top_srcdir@/drv/TDF/TDF_ListIteratorOfDeltaList_0.cxx \
@top_srcdir@/drv/TDF/TDF_ListIteratorOfIDList_0.cxx \
@top_srcdir@/drv/TDF/TDF_ListIteratorOfLabelList_0.cxx \
@top_srcdir@/drv/TDF/TDF_ListNodeOfAttributeDeltaList_0.cxx \
@top_srcdir@/drv/TDF/TDF_ListNodeOfAttributeList_0.cxx \
@top_srcdir@/drv/TDF/TDF_ListNodeOfDeltaList_0.cxx \
@top_srcdir@/drv/TDF/TDF_ListNodeOfIDList_0.cxx \
@top_srcdir@/drv/TDF/TDF_ListNodeOfLabelList_0.cxx \
@top_srcdir@/drv/TDF/TDF_MapIteratorOfAttributeMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_MapIteratorOfIDMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_MapIteratorOfLabelMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_SequenceNodeOfAttributeSequence_0.cxx \
@top_srcdir@/drv/TDF/TDF_SequenceNodeOfLabelSequence_0.cxx \
@top_srcdir@/drv/TDF/TDF_StdMapNodeOfAttributeMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_StdMapNodeOfIDMap_0.cxx \
@top_srcdir@/drv/TDF/TDF_StdMapNodeOfLabelMap_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_DataMapIteratorOfDataMapOfStringByte_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_DataMapIteratorOfDataMapOfStringHArray1OfInteger_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_DataMapIteratorOfDataMapOfStringHArray1OfReal_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_DataMapIteratorOfDataMapOfStringReal_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_DataMapIteratorOfDataMapOfStringString_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_DataMapNodeOfDataMapOfStringByte_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_DataMapNodeOfDataMapOfStringHArray1OfInteger_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_DataMapNodeOfDataMapOfStringHArray1OfReal_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_DataMapNodeOfDataMapOfStringReal_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_DataMapNodeOfDataMapOfStringString_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_DataMapOfStringByte_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_DataMapOfStringHArray1OfInteger_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_DataMapOfStringHArray1OfReal_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_DataMapOfStringReal_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_DataMapOfStringString_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_HLabelArray1_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_LabelArray1_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_ListIteratorOfListOfByte_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_ListIteratorOfListOfExtendedString_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_ListNodeOfListOfByte_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_ListNodeOfListOfExtendedString_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_ListOfByte_0.cxx \
@top_srcdir@/drv/TDataStd/TDataStd_ListOfExtendedString_0.cxx \
@top_srcdir@/drv/TDocStd/TDocStd_DataMapIteratorOfLabelIDMapDataMap_0.cxx \
@top_srcdir@/drv/TDocStd/TDocStd_DataMapNodeOfLabelIDMapDataMap_0.cxx \
@top_srcdir@/drv/TDocStd/TDocStd_LabelIDMapDataMap_0.cxx \
@top_srcdir@/drv/TDocStd/TDocStd_SequenceNodeOfSequenceOfApplicationDelta_0.cxx \
@top_srcdir@/drv/TDocStd/TDocStd_SequenceNodeOfSequenceOfDocument_0.cxx \
@top_srcdir@/drv/TDocStd/TDocStd_SequenceOfApplicationDelta_0.cxx \
@top_srcdir@/drv/TDocStd/TDocStd_SequenceOfDocument_0.cxx \
@top_srcdir@/drv/TFunction/TFunction_Array1OfDataMapOfGUIDDriver_0.cxx \
@top_srcdir@/drv/TFunction/TFunction_DataMapIteratorOfDataMapOfGUIDDriver_0.cxx \
@top_srcdir@/drv/TFunction/TFunction_DataMapIteratorOfDataMapOfLabelListOfLabel_0.cxx \
@top_srcdir@/drv/TFunction/TFunction_DataMapNodeOfDataMapOfGUIDDriver_0.cxx \
@top_srcdir@/drv/TFunction/TFunction_DataMapNodeOfDataMapOfLabelListOfLabel_0.cxx \
@top_srcdir@/drv/TFunction/TFunction_DataMapOfGUIDDriver_0.cxx \
@top_srcdir@/drv/TFunction/TFunction_DataMapOfLabelListOfLabel_0.cxx \
@top_srcdir@/drv/TFunction/TFunction_DoubleMapIteratorOfDoubleMapOfIntegerLabel_0.cxx \
@top_srcdir@/drv/TFunction/TFunction_DoubleMapNodeOfDoubleMapOfIntegerLabel_0.cxx \
@top_srcdir@/drv/TFunction/TFunction_DoubleMapOfIntegerLabel_0.cxx \
@top_srcdir@/drv/TFunction/TFunction_HArray1OfDataMapOfGUIDDriver_0.cxx \
@top_srcdir@/src/AppStdL/AppStdL_Application.cxx \
@top_srcdir@/src/TDF/TDF.cxx \
@top_srcdir@/src/TDF/TDF_Attribute.cxx \
@top_srcdir@/src/TDF/TDF_AttributeDelta.cxx \
@top_srcdir@/src/TDF/TDF_AttributeIterator.cxx \
@top_srcdir@/src/TDF/TDF_ChildIDIterator.cxx \
@top_srcdir@/src/TDF/TDF_ChildIterator.cxx \
@top_srcdir@/src/TDF/TDF_ClosureMode.cxx \
@top_srcdir@/src/TDF/TDF_ClosureTool.cxx \
@top_srcdir@/src/TDF/TDF_ComparisonTool.cxx \
@top_srcdir@/src/TDF/TDF_CopyLabel.cxx \
@top_srcdir@/src/TDF/TDF_CopyTool.cxx \
@top_srcdir@/src/TDF/TDF_Data.cxx \
@top_srcdir@/src/TDF/TDF_DataSet.cxx \
@top_srcdir@/src/TDF/TDF_DefaultDeltaOnModification.cxx \
@top_srcdir@/src/TDF/TDF_DefaultDeltaOnRemoval.cxx \
@top_srcdir@/src/TDF/TDF_Delta.cxx \
@top_srcdir@/src/TDF/TDF_DeltaOnAddition.cxx \
@top_srcdir@/src/TDF/TDF_DeltaOnForget.cxx \
@top_srcdir@/src/TDF/TDF_DeltaOnModification.cxx \
@top_srcdir@/src/TDF/TDF_DeltaOnRemoval.cxx \
@top_srcdir@/src/TDF/TDF_DeltaOnResume.cxx \
@top_srcdir@/src/TDF/TDF_IDFilter.cxx \
@top_srcdir@/src/TDF/TDF_Label.cxx \
@top_srcdir@/src/TDF/TDF_LabelMapHasher.cxx \
@top_srcdir@/src/TDF/TDF_LabelNode.cxx \
@top_srcdir@/src/TDF/TDF_Reference.cxx \
@top_srcdir@/src/TDF/TDF_RelocationTable.cxx \
@top_srcdir@/src/TDF/TDF_TagSource.cxx \
@top_srcdir@/src/TDF/TDF_Tool.cxx \
@top_srcdir@/src/TDF/TDF_Transaction.cxx \
@top_srcdir@/src/TDataStd/TDataStd.cxx \
@top_srcdir@/src/TDataStd/TDataStd_AsciiString.cxx \
@top_srcdir@/src/TDataStd/TDataStd_BooleanArray.cxx \
@top_srcdir@/src/TDataStd/TDataStd_BooleanList.cxx \
@top_srcdir@/src/TDataStd/TDataStd_ByteArray.cxx \
@top_srcdir@/src/TDataStd/TDataStd_ChildNodeIterator.cxx \
@top_srcdir@/src/TDataStd/TDataStd_Comment.cxx \
@top_srcdir@/src/TDataStd/TDataStd_Current.cxx \
@top_srcdir@/src/TDataStd/TDataStd_DeltaOnModificationOfByteArray.cxx \
@top_srcdir@/src/TDataStd/TDataStd_DeltaOnModificationOfExtStringArray.cxx \
@top_srcdir@/src/TDataStd/TDataStd_DeltaOnModificationOfIntArray.cxx \
@top_srcdir@/src/TDataStd/TDataStd_DeltaOnModificationOfIntPackedMap.cxx \
@top_srcdir@/src/TDataStd/TDataStd_DeltaOnModificationOfRealArray.cxx \
@top_srcdir@/src/TDataStd/TDataStd_Directory.cxx \
@top_srcdir@/src/TDataStd/TDataStd_Expression.cxx \
@top_srcdir@/src/TDataStd/TDataStd_ExtStringArray.cxx \
@top_srcdir@/src/TDataStd/TDataStd_ExtStringList.cxx \
@top_srcdir@/src/TDataStd/TDataStd_HDataMapOfStringByte.cxx \
@top_srcdir@/src/TDataStd/TDataStd_HDataMapOfStringHArray1OfInteger.cxx \
@top_srcdir@/src/TDataStd/TDataStd_HDataMapOfStringHArray1OfReal.cxx \
@top_srcdir@/src/TDataStd/TDataStd_HDataMapOfStringInteger.cxx \
@top_srcdir@/src/TDataStd/TDataStd_HDataMapOfStringReal.cxx \
@top_srcdir@/src/TDataStd/TDataStd_HDataMapOfStringString.cxx \
@top_srcdir@/src/TDataStd/TDataStd_IntPackedMap.cxx \
@top_srcdir@/src/TDataStd/TDataStd_Integer.cxx \
@top_srcdir@/src/TDataStd/TDataStd_IntegerArray.cxx \
@top_srcdir@/src/TDataStd/TDataStd_IntegerList.cxx \
@top_srcdir@/src/TDataStd/TDataStd_Name.cxx \
@top_srcdir@/src/TDataStd/TDataStd_NamedData.cxx \
@top_srcdir@/src/TDataStd/TDataStd_NoteBook.cxx \
@top_srcdir@/src/TDataStd/TDataStd_Real.cxx \
@top_srcdir@/src/TDataStd/TDataStd_RealArray.cxx \
@top_srcdir@/src/TDataStd/TDataStd_RealList.cxx \
@top_srcdir@/src/TDataStd/TDataStd_ReferenceArray.cxx \
@top_srcdir@/src/TDataStd/TDataStd_ReferenceList.cxx \
@top_srcdir@/src/TDataStd/TDataStd_Relation.cxx \
@top_srcdir@/src/TDataStd/TDataStd_Tick.cxx \
@top_srcdir@/src/TDataStd/TDataStd_TreeNode.cxx \
@top_srcdir@/src/TDataStd/TDataStd_UAttribute.cxx \
@top_srcdir@/src/TDataStd/TDataStd_Variable.cxx \
@top_srcdir@/src/TDocStd/TDocStd.cxx \
@top_srcdir@/src/TDocStd/TDocStd_Application.cxx \
@top_srcdir@/src/TDocStd/TDocStd_ApplicationDelta.cxx \
@top_srcdir@/src/TDocStd/TDocStd_CompoundDelta.cxx \
@top_srcdir@/src/TDocStd/TDocStd_Context.cxx \
@top_srcdir@/src/TDocStd/TDocStd_Document.cxx \
@top_srcdir@/src/TDocStd/TDocStd_Modified.cxx \
@top_srcdir@/src/TDocStd/TDocStd_MultiTransactionManager.cxx \
@top_srcdir@/src/TDocStd/TDocStd_Owner.cxx \
@top_srcdir@/src/TDocStd/TDocStd_PathParser.cxx \
@top_srcdir@/src/TDocStd/TDocStd_XLink.cxx \
@top_srcdir@/src/TDocStd/TDocStd_XLinkIterator.cxx \
@top_srcdir@/src/TDocStd/TDocStd_XLinkRoot.cxx \
@top_srcdir@/src/TDocStd/TDocStd_XLinkTool.cxx \
@top_srcdir@/src/TFunction/TFunction_Driver.cxx \
@top_srcdir@/src/TFunction/TFunction_DriverTable.cxx \
@top_srcdir@/src/TFunction/TFunction_Function.cxx \
@top_srcdir@/src/TFunction/TFunction_GraphNode.cxx \
@top_srcdir@/src/TFunction/TFunction_IFunction.cxx \
@top_srcdir@/src/TFunction/TFunction_Iterator.cxx \
@top_srcdir@/src/TFunction/TFunction_Logbook.cxx \
@top_srcdir@/src/TFunction/TFunction_Scope.cxx

