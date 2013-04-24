# Makefile.am for Open Cascade toolkit TKPLCAF
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/PDF : @top_srcdir@/src/PDF: \
@top_srcdir@/drv/PDataStd : @top_srcdir@/src/PDataStd: \
@top_srcdir@/drv/PFunction : @top_srcdir@/src/PFunction: \
@top_srcdir@/drv/PDocStd : @top_srcdir@/src/PDocStd: \
@top_srcdir@/drv/MDF : @top_srcdir@/src/MDF: \
@top_srcdir@/drv/MDataStd : @top_srcdir@/src/MDataStd: \
@top_srcdir@/drv/MFunction : @top_srcdir@/src/MFunction: \
@top_srcdir@/drv/MDocStd : @top_srcdir@/src/MDocStd


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/PDF -I@top_srcdir@/src/PDF \
-I@top_srcdir@/drv/PDataStd -I@top_srcdir@/src/PDataStd \
-I@top_srcdir@/drv/PFunction -I@top_srcdir@/src/PFunction \
-I@top_srcdir@/drv/PDocStd -I@top_srcdir@/src/PDocStd \
-I@top_srcdir@/drv/MDF -I@top_srcdir@/src/MDF \
-I@top_srcdir@/drv/MDataStd -I@top_srcdir@/src/MDataStd \
-I@top_srcdir@/drv/MFunction -I@top_srcdir@/src/MFunction \
-I@top_srcdir@/drv/MDocStd -I@top_srcdir@/src/MDocStd


lib_LTLIBRARIES=libTKPLCAF.la

libTKPLCAF_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKCDF/libTKCDF.la \
../PTKernel/libPTKernel.la \
../TKernel/libTKernel.la \
../TKLCAF/libTKLCAF.la \
$(STLPort_LIB) 

libTKPLCAF_la_SOURCES = \
@top_srcdir@/drv/MDF/MDF_ARDriverHSequence_0.cxx \
@top_srcdir@/drv/MDF/MDF_ARDriverSequence_0.cxx \
@top_srcdir@/drv/MDF/MDF_ARDriverTable_0.cxx \
@top_srcdir@/drv/MDF/MDF_ASDriverHSequence_0.cxx \
@top_srcdir@/drv/MDF/MDF_ASDriverSequence_0.cxx \
@top_srcdir@/drv/MDF/MDF_ASDriverTable_0.cxx \
@top_srcdir@/drv/MDF/MDF_DataMapIteratorOfTypeARDriverMap_0.cxx \
@top_srcdir@/drv/MDF/MDF_DataMapIteratorOfTypeASDriverMap_0.cxx \
@top_srcdir@/drv/MDF/MDF_DataMapIteratorOfTypeDriverListMapOfARDriverTable_0.cxx \
@top_srcdir@/drv/MDF/MDF_DataMapIteratorOfTypeDriverListMapOfASDriverTable_0.cxx \
@top_srcdir@/drv/MDF/MDF_DataMapNodeOfTypeARDriverMap_0.cxx \
@top_srcdir@/drv/MDF/MDF_DataMapNodeOfTypeASDriverMap_0.cxx \
@top_srcdir@/drv/MDF/MDF_DataMapNodeOfTypeDriverListMapOfARDriverTable_0.cxx \
@top_srcdir@/drv/MDF/MDF_DataMapNodeOfTypeDriverListMapOfASDriverTable_0.cxx \
@top_srcdir@/drv/MDF/MDF_DriverListOfARDriverTable_0.cxx \
@top_srcdir@/drv/MDF/MDF_DriverListOfASDriverTable_0.cxx \
@top_srcdir@/drv/MDF/MDF_ListIteratorOfDriverListOfARDriverTable_0.cxx \
@top_srcdir@/drv/MDF/MDF_ListIteratorOfDriverListOfASDriverTable_0.cxx \
@top_srcdir@/drv/MDF/MDF_ListNodeOfDriverListOfARDriverTable_0.cxx \
@top_srcdir@/drv/MDF/MDF_ListNodeOfDriverListOfASDriverTable_0.cxx \
@top_srcdir@/drv/MDF/MDF_RRelocationTable_0.cxx \
@top_srcdir@/drv/MDF/MDF_SRelocationTable_0.cxx \
@top_srcdir@/drv/MDF/MDF_SequenceNodeOfARDriverSequence_0.cxx \
@top_srcdir@/drv/MDF/MDF_SequenceNodeOfASDriverSequence_0.cxx \
@top_srcdir@/drv/MDF/MDF_TypeARDriverMap_0.cxx \
@top_srcdir@/drv/MDF/MDF_TypeASDriverMap_0.cxx \
@top_srcdir@/drv/MDF/MDF_TypeDriverListMapOfARDriverTable_0.cxx \
@top_srcdir@/drv/MDF/MDF_TypeDriverListMapOfASDriverTable_0.cxx \
@top_srcdir@/drv/PDF/PDF_FieldOfHAttributeArray1_0.cxx \
@top_srcdir@/drv/PDF/PDF_HAttributeArray1_0.cxx \
@top_srcdir@/drv/PDF/PDF_VArrayNodeOfFieldOfHAttributeArray1_0.cxx \
@top_srcdir@/drv/PDF/PDF_VArrayTNodeOfFieldOfHAttributeArray1_0.cxx \
@top_srcdir@/drv/PDataStd/PDataStd_FieldOfHArray1OfByte_0.cxx \
@top_srcdir@/drv/PDataStd/PDataStd_FieldOfHArray1OfHArray1OfInteger_0.cxx \
@top_srcdir@/drv/PDataStd/PDataStd_FieldOfHArray1OfHArray1OfReal_0.cxx \
@top_srcdir@/drv/PDataStd/PDataStd_FieldOfHArray1OfHAsciiString_0.cxx \
@top_srcdir@/drv/PDataStd/PDataStd_HArray1OfByte_0.cxx \
@top_srcdir@/drv/PDataStd/PDataStd_HArray1OfHArray1OfInteger_0.cxx \
@top_srcdir@/drv/PDataStd/PDataStd_HArray1OfHArray1OfReal_0.cxx \
@top_srcdir@/drv/PDataStd/PDataStd_HArray1OfHAsciiString_0.cxx \
@top_srcdir@/drv/PDataStd/PDataStd_VArrayNodeOfFieldOfHArray1OfByte_0.cxx \
@top_srcdir@/drv/PDataStd/PDataStd_VArrayNodeOfFieldOfHArray1OfHArray1OfInteger_0.cxx \
@top_srcdir@/drv/PDataStd/PDataStd_VArrayNodeOfFieldOfHArray1OfHArray1OfReal_0.cxx \
@top_srcdir@/drv/PDataStd/PDataStd_VArrayNodeOfFieldOfHArray1OfHAsciiString_0.cxx \
@top_srcdir@/drv/PDataStd/PDataStd_VArrayTNodeOfFieldOfHArray1OfByte_0.cxx \
@top_srcdir@/drv/PDataStd/PDataStd_VArrayTNodeOfFieldOfHArray1OfHArray1OfInteger_0.cxx \
@top_srcdir@/drv/PDataStd/PDataStd_VArrayTNodeOfFieldOfHArray1OfHArray1OfReal_0.cxx \
@top_srcdir@/drv/PDataStd/PDataStd_VArrayTNodeOfFieldOfHArray1OfHAsciiString_0.cxx \
@top_srcdir@/src/MDF/MDF.cxx \
@top_srcdir@/src/MDF/MDF_ARDriver.cxx \
@top_srcdir@/src/MDF/MDF_ASDriver.cxx \
@top_srcdir@/src/MDF/MDF_ReferenceRetrievalDriver.cxx \
@top_srcdir@/src/MDF/MDF_ReferenceStorageDriver.cxx \
@top_srcdir@/src/MDF/MDF_TagSourceRetrievalDriver.cxx \
@top_srcdir@/src/MDF/MDF_TagSourceStorageDriver.cxx \
@top_srcdir@/src/MDF/MDF_Tool.cxx \
@top_srcdir@/src/MDataStd/MDataStd.cxx \
@top_srcdir@/src/MDataStd/MDataStd_AsciiStringRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_AsciiStringStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_BooleanArrayRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_BooleanArrayStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_BooleanListRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_BooleanListStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_ByteArrayRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_ByteArrayRetrievalDriver_1.cxx \
@top_srcdir@/src/MDataStd/MDataStd_ByteArrayStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_CommentRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_CommentStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_DirectoryRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_DirectoryStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_ExpressionRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_ExpressionStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_ExtStringArrayRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_ExtStringArrayRetrievalDriver_1.cxx \
@top_srcdir@/src/MDataStd/MDataStd_ExtStringArrayStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_ExtStringListRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_ExtStringListStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_IntPackedMapRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_IntPackedMapRetrievalDriver_1.cxx \
@top_srcdir@/src/MDataStd/MDataStd_IntPackedMapStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_IntegerArrayRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_IntegerArrayRetrievalDriver_1.cxx \
@top_srcdir@/src/MDataStd/MDataStd_IntegerArrayStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_IntegerListRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_IntegerListStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_IntegerRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_IntegerStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_NameRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_NameStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_NamedDataRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_NamedDataStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_NoteBookRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_NoteBookStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_RealArrayRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_RealArrayRetrievalDriver_1.cxx \
@top_srcdir@/src/MDataStd/MDataStd_RealArrayStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_RealListRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_RealListStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_RealRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_RealStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_ReferenceArrayRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_ReferenceArrayStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_ReferenceListRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_ReferenceListStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_RelationRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_RelationStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_TickRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_TickStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_TreeNodeRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_TreeNodeStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_UAttributeRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_UAttributeStorageDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_VariableRetrievalDriver.cxx \
@top_srcdir@/src/MDataStd/MDataStd_VariableStorageDriver.cxx \
@top_srcdir@/src/MDocStd/MDocStd.cxx \
@top_srcdir@/src/MDocStd/MDocStd_DocumentRetrievalDriver.cxx \
@top_srcdir@/src/MDocStd/MDocStd_DocumentStorageDriver.cxx \
@top_srcdir@/src/MDocStd/MDocStd_XLinkRetrievalDriver.cxx \
@top_srcdir@/src/MDocStd/MDocStd_XLinkStorageDriver.cxx \
@top_srcdir@/src/MFunction/MFunction.cxx \
@top_srcdir@/src/MFunction/MFunction_FunctionRetrievalDriver.cxx \
@top_srcdir@/src/MFunction/MFunction_FunctionStorageDriver.cxx \
@top_srcdir@/src/PDF/PDF_Attribute.cxx \
@top_srcdir@/src/PDF/PDF_Data.cxx \
@top_srcdir@/src/PDF/PDF_Reference.cxx \
@top_srcdir@/src/PDF/PDF_TagSource.cxx \
@top_srcdir@/src/PDataStd/PDataStd_AsciiString.cxx \
@top_srcdir@/src/PDataStd/PDataStd_BooleanArray.cxx \
@top_srcdir@/src/PDataStd/PDataStd_BooleanList.cxx \
@top_srcdir@/src/PDataStd/PDataStd_ByteArray.cxx \
@top_srcdir@/src/PDataStd/PDataStd_ByteArray_1.cxx \
@top_srcdir@/src/PDataStd/PDataStd_Comment.cxx \
@top_srcdir@/src/PDataStd/PDataStd_Directory.cxx \
@top_srcdir@/src/PDataStd/PDataStd_Expression.cxx \
@top_srcdir@/src/PDataStd/PDataStd_ExtStringArray.cxx \
@top_srcdir@/src/PDataStd/PDataStd_ExtStringArray_1.cxx \
@top_srcdir@/src/PDataStd/PDataStd_ExtStringList.cxx \
@top_srcdir@/src/PDataStd/PDataStd_IntPackedMap.cxx \
@top_srcdir@/src/PDataStd/PDataStd_IntPackedMap_1.cxx \
@top_srcdir@/src/PDataStd/PDataStd_Integer.cxx \
@top_srcdir@/src/PDataStd/PDataStd_IntegerArray.cxx \
@top_srcdir@/src/PDataStd/PDataStd_IntegerArray_1.cxx \
@top_srcdir@/src/PDataStd/PDataStd_IntegerList.cxx \
@top_srcdir@/src/PDataStd/PDataStd_Name.cxx \
@top_srcdir@/src/PDataStd/PDataStd_NamedData.cxx \
@top_srcdir@/src/PDataStd/PDataStd_NoteBook.cxx \
@top_srcdir@/src/PDataStd/PDataStd_Real.cxx \
@top_srcdir@/src/PDataStd/PDataStd_RealArray.cxx \
@top_srcdir@/src/PDataStd/PDataStd_RealArray_1.cxx \
@top_srcdir@/src/PDataStd/PDataStd_RealList.cxx \
@top_srcdir@/src/PDataStd/PDataStd_ReferenceArray.cxx \
@top_srcdir@/src/PDataStd/PDataStd_ReferenceList.cxx \
@top_srcdir@/src/PDataStd/PDataStd_Relation.cxx \
@top_srcdir@/src/PDataStd/PDataStd_Tick.cxx \
@top_srcdir@/src/PDataStd/PDataStd_TreeNode.cxx \
@top_srcdir@/src/PDataStd/PDataStd_UAttribute.cxx \
@top_srcdir@/src/PDataStd/PDataStd_Variable.cxx \
@top_srcdir@/src/PDocStd/PDocStd_Document.cxx \
@top_srcdir@/src/PDocStd/PDocStd_XLink.cxx \
@top_srcdir@/src/PFunction/PFunction_Function.cxx

