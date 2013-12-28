project(TKPLCAF)

if (WIN32)
  list( APPEND TKPLCAF_PRECOMPILED_DEFS "-D__PDF_DLL" )
  list( APPEND TKPLCAF_PRECOMPILED_DEFS "-D__PDataStd_DLL" )
  list( APPEND TKPLCAF_PRECOMPILED_DEFS "-D__PFunction_DLL" )
  list( APPEND TKPLCAF_PRECOMPILED_DEFS "-D__PDocStd_DLL" )
  list( APPEND TKPLCAF_PRECOMPILED_DEFS "-D__MDF_DLL" )
  list( APPEND TKPLCAF_PRECOMPILED_DEFS "-D__MDataStd_DLL" )
  list( APPEND TKPLCAF_PRECOMPILED_DEFS "-D__MFunction_DLL" )
  list( APPEND TKPLCAF_PRECOMPILED_DEFS "-D__MDocStd_DLL" )
  string( REGEX REPLACE ";" " " TKPLCAF_PRECOMPILED_DEFS "${TKPLCAF_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKPLCAF_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKPLCAF_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKPLCAF_COMPILER_DIRECTORIES "../../../drv/PDF" )
  list( APPEND TKPLCAF_COMPILER_DIRECTORIES "../../../src/PDF" )
  list( APPEND TKPLCAF_COMPILER_DIRECTORIES "../../../drv/PDataStd" )
  list( APPEND TKPLCAF_COMPILER_DIRECTORIES "../../../src/PDataStd" )
  list( APPEND TKPLCAF_COMPILER_DIRECTORIES "../../../drv/PFunction" )
  list( APPEND TKPLCAF_COMPILER_DIRECTORIES "../../../src/PFunction" )
  list( APPEND TKPLCAF_COMPILER_DIRECTORIES "../../../drv/PDocStd" )
  list( APPEND TKPLCAF_COMPILER_DIRECTORIES "../../../src/PDocStd" )
  list( APPEND TKPLCAF_COMPILER_DIRECTORIES "../../../drv/MDF" )
  list( APPEND TKPLCAF_COMPILER_DIRECTORIES "../../../src/MDF" )
  list( APPEND TKPLCAF_COMPILER_DIRECTORIES "../../../drv/MDataStd" )
  list( APPEND TKPLCAF_COMPILER_DIRECTORIES "../../../src/MDataStd" )
  list( APPEND TKPLCAF_COMPILER_DIRECTORIES "../../../drv/MFunction" )
  list( APPEND TKPLCAF_COMPILER_DIRECTORIES "../../../src/MFunction" )
  list( APPEND TKPLCAF_COMPILER_DIRECTORIES "../../../drv/MDocStd" )
  list( APPEND TKPLCAF_COMPILER_DIRECTORIES "../../../src/MDocStd" )

if (WIN32)
else()
endif()

  list( APPEND TKPLCAF_USED_LIBS TKCDF )
  list( APPEND TKPLCAF_USED_LIBS PTKernel )
  list( APPEND TKPLCAF_USED_LIBS TKernel )
  list( APPEND TKPLCAF_USED_LIBS TKLCAF )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDF/PDF_FieldOfHAttributeArray1_0.cxx" )
  SOURCE_GROUP (PDF FILES "../../../drv/PDF/PDF_FieldOfHAttributeArray1_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDF/PDF_HAttributeArray1_0.cxx" )
  SOURCE_GROUP (PDF FILES "../../../drv/PDF/PDF_HAttributeArray1_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDF/PDF_VArrayNodeOfFieldOfHAttributeArray1_0.cxx" )
  SOURCE_GROUP (PDF FILES "../../../drv/PDF/PDF_VArrayNodeOfFieldOfHAttributeArray1_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDF/PDF_VArrayTNodeOfFieldOfHAttributeArray1_0.cxx" )
  SOURCE_GROUP (PDF FILES "../../../drv/PDF/PDF_VArrayTNodeOfFieldOfHAttributeArray1_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDF/PDF_Attribute.cxx" )
  SOURCE_GROUP (PDF FILES "../../../src/PDF/PDF_Attribute.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDF/PDF_Data.cxx" )
  SOURCE_GROUP (PDF FILES "../../../src/PDF/PDF_Data.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDF/PDF_Reference.cxx" )
  SOURCE_GROUP (PDF FILES "../../../src/PDF/PDF_Reference.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDF/PDF_TagSource.cxx" )
  SOURCE_GROUP (PDF FILES "../../../src/PDF/PDF_TagSource.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDataStd/PDataStd_FieldOfHArray1OfByte_0.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../drv/PDataStd/PDataStd_FieldOfHArray1OfByte_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDataStd/PDataStd_FieldOfHArray1OfHArray1OfInteger_0.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../drv/PDataStd/PDataStd_FieldOfHArray1OfHArray1OfInteger_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDataStd/PDataStd_FieldOfHArray1OfHArray1OfReal_0.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../drv/PDataStd/PDataStd_FieldOfHArray1OfHArray1OfReal_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDataStd/PDataStd_FieldOfHArray1OfHAsciiString_0.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../drv/PDataStd/PDataStd_FieldOfHArray1OfHAsciiString_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDataStd/PDataStd_HArray1OfByte_0.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../drv/PDataStd/PDataStd_HArray1OfByte_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDataStd/PDataStd_HArray1OfHArray1OfInteger_0.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../drv/PDataStd/PDataStd_HArray1OfHArray1OfInteger_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDataStd/PDataStd_HArray1OfHArray1OfReal_0.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../drv/PDataStd/PDataStd_HArray1OfHArray1OfReal_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDataStd/PDataStd_HArray1OfHAsciiString_0.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../drv/PDataStd/PDataStd_HArray1OfHAsciiString_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDataStd/PDataStd_VArrayNodeOfFieldOfHArray1OfByte_0.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../drv/PDataStd/PDataStd_VArrayNodeOfFieldOfHArray1OfByte_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDataStd/PDataStd_VArrayNodeOfFieldOfHArray1OfHArray1OfInteger_0.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../drv/PDataStd/PDataStd_VArrayNodeOfFieldOfHArray1OfHArray1OfInteger_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDataStd/PDataStd_VArrayNodeOfFieldOfHArray1OfHArray1OfReal_0.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../drv/PDataStd/PDataStd_VArrayNodeOfFieldOfHArray1OfHArray1OfReal_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDataStd/PDataStd_VArrayNodeOfFieldOfHArray1OfHAsciiString_0.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../drv/PDataStd/PDataStd_VArrayNodeOfFieldOfHArray1OfHAsciiString_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDataStd/PDataStd_VArrayTNodeOfFieldOfHArray1OfByte_0.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../drv/PDataStd/PDataStd_VArrayTNodeOfFieldOfHArray1OfByte_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDataStd/PDataStd_VArrayTNodeOfFieldOfHArray1OfHArray1OfInteger_0.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../drv/PDataStd/PDataStd_VArrayTNodeOfFieldOfHArray1OfHArray1OfInteger_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDataStd/PDataStd_VArrayTNodeOfFieldOfHArray1OfHArray1OfReal_0.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../drv/PDataStd/PDataStd_VArrayTNodeOfFieldOfHArray1OfHArray1OfReal_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/PDataStd/PDataStd_VArrayTNodeOfFieldOfHArray1OfHAsciiString_0.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../drv/PDataStd/PDataStd_VArrayTNodeOfFieldOfHArray1OfHAsciiString_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_AsciiString.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_AsciiString.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_BooleanArray.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_BooleanArray.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_BooleanList.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_BooleanList.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_ByteArray.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_ByteArray.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_ByteArray_1.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_ByteArray_1.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_Comment.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_Comment.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_Directory.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_Directory.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_Expression.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_Expression.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_ExtStringArray.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_ExtStringArray.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_ExtStringArray_1.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_ExtStringArray_1.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_ExtStringList.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_ExtStringList.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_IntPackedMap.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_IntPackedMap.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_IntPackedMap_1.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_IntPackedMap_1.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_Integer.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_Integer.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_IntegerArray.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_IntegerArray.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_IntegerArray_1.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_IntegerArray_1.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_IntegerList.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_IntegerList.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_Name.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_Name.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_NamedData.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_NamedData.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_NoteBook.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_NoteBook.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_Real.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_Real.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_RealArray.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_RealArray.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_RealArray_1.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_RealArray_1.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_RealList.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_RealList.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_ReferenceArray.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_ReferenceArray.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_ReferenceList.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_ReferenceList.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_Relation.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_Relation.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_Tick.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_Tick.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_TreeNode.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_TreeNode.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_UAttribute.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_UAttribute.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDataStd/PDataStd_Variable.cxx" )
  SOURCE_GROUP (PDataStd FILES "../../../src/PDataStd/PDataStd_Variable.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PFunction/PFunction_Function.cxx" )
  SOURCE_GROUP (PFunction FILES "../../../src/PFunction/PFunction_Function.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDocStd/PDocStd_Document.cxx" )
  SOURCE_GROUP (PDocStd FILES "../../../src/PDocStd/PDocStd_Document.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/PDocStd/PDocStd_XLink.cxx" )
  SOURCE_GROUP (PDocStd FILES "../../../src/PDocStd/PDocStd_XLink.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_ARDriverHSequence_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_ARDriverHSequence_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_ARDriverSequence_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_ARDriverSequence_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_ARDriverTable_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_ARDriverTable_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_ASDriverHSequence_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_ASDriverHSequence_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_ASDriverSequence_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_ASDriverSequence_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_ASDriverTable_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_ASDriverTable_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_DataMapIteratorOfTypeARDriverMap_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_DataMapIteratorOfTypeARDriverMap_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_DataMapIteratorOfTypeASDriverMap_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_DataMapIteratorOfTypeASDriverMap_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_DataMapIteratorOfTypeDriverListMapOfARDriverTable_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_DataMapIteratorOfTypeDriverListMapOfARDriverTable_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_DataMapIteratorOfTypeDriverListMapOfASDriverTable_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_DataMapIteratorOfTypeDriverListMapOfASDriverTable_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_DataMapNodeOfTypeARDriverMap_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_DataMapNodeOfTypeARDriverMap_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_DataMapNodeOfTypeASDriverMap_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_DataMapNodeOfTypeASDriverMap_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_DataMapNodeOfTypeDriverListMapOfARDriverTable_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_DataMapNodeOfTypeDriverListMapOfARDriverTable_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_DataMapNodeOfTypeDriverListMapOfASDriverTable_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_DataMapNodeOfTypeDriverListMapOfASDriverTable_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_DriverListOfARDriverTable_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_DriverListOfARDriverTable_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_DriverListOfASDriverTable_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_DriverListOfASDriverTable_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_ListIteratorOfDriverListOfARDriverTable_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_ListIteratorOfDriverListOfARDriverTable_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_ListIteratorOfDriverListOfASDriverTable_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_ListIteratorOfDriverListOfASDriverTable_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_ListNodeOfDriverListOfARDriverTable_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_ListNodeOfDriverListOfARDriverTable_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_ListNodeOfDriverListOfASDriverTable_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_ListNodeOfDriverListOfASDriverTable_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_RRelocationTable_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_RRelocationTable_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_SRelocationTable_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_SRelocationTable_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_SequenceNodeOfARDriverSequence_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_SequenceNodeOfARDriverSequence_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_SequenceNodeOfASDriverSequence_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_SequenceNodeOfASDriverSequence_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_TypeARDriverMap_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_TypeARDriverMap_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_TypeASDriverMap_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_TypeASDriverMap_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_TypeDriverListMapOfARDriverTable_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_TypeDriverListMapOfARDriverTable_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../drv/MDF/MDF_TypeDriverListMapOfASDriverTable_0.cxx" )
  SOURCE_GROUP (MDF FILES "../../../drv/MDF/MDF_TypeDriverListMapOfASDriverTable_0.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDF/MDF.cxx" )
  SOURCE_GROUP (MDF FILES "../../../src/MDF/MDF.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDF/MDF_ARDriver.cxx" )
  SOURCE_GROUP (MDF FILES "../../../src/MDF/MDF_ARDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDF/MDF_ASDriver.cxx" )
  SOURCE_GROUP (MDF FILES "../../../src/MDF/MDF_ASDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDF/MDF_ReferenceRetrievalDriver.cxx" )
  SOURCE_GROUP (MDF FILES "../../../src/MDF/MDF_ReferenceRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDF/MDF_ReferenceStorageDriver.cxx" )
  SOURCE_GROUP (MDF FILES "../../../src/MDF/MDF_ReferenceStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDF/MDF_TagSourceRetrievalDriver.cxx" )
  SOURCE_GROUP (MDF FILES "../../../src/MDF/MDF_TagSourceRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDF/MDF_TagSourceStorageDriver.cxx" )
  SOURCE_GROUP (MDF FILES "../../../src/MDF/MDF_TagSourceStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDF/MDF_Tool.cxx" )
  SOURCE_GROUP (MDF FILES "../../../src/MDF/MDF_Tool.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_AsciiStringRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_AsciiStringRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_AsciiStringStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_AsciiStringStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_BooleanArrayRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_BooleanArrayRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_BooleanArrayStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_BooleanArrayStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_BooleanListRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_BooleanListRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_BooleanListStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_BooleanListStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_ByteArrayRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_ByteArrayRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_ByteArrayRetrievalDriver_1.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_ByteArrayRetrievalDriver_1.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_ByteArrayStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_ByteArrayStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_CommentRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_CommentRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_CommentStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_CommentStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_DirectoryRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_DirectoryRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_DirectoryStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_DirectoryStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_ExpressionRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_ExpressionRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_ExpressionStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_ExpressionStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_ExtStringArrayRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_ExtStringArrayRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_ExtStringArrayRetrievalDriver_1.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_ExtStringArrayRetrievalDriver_1.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_ExtStringArrayStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_ExtStringArrayStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_ExtStringListRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_ExtStringListRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_ExtStringListStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_ExtStringListStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_IntPackedMapRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_IntPackedMapRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_IntPackedMapRetrievalDriver_1.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_IntPackedMapRetrievalDriver_1.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_IntPackedMapStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_IntPackedMapStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_IntegerArrayRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_IntegerArrayRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_IntegerArrayRetrievalDriver_1.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_IntegerArrayRetrievalDriver_1.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_IntegerArrayStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_IntegerArrayStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_IntegerListRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_IntegerListRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_IntegerListStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_IntegerListStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_IntegerRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_IntegerRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_IntegerStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_IntegerStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_NameRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_NameRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_NameStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_NameStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_NamedDataRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_NamedDataRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_NamedDataStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_NamedDataStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_NoteBookRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_NoteBookRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_NoteBookStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_NoteBookStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_RealArrayRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_RealArrayRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_RealArrayRetrievalDriver_1.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_RealArrayRetrievalDriver_1.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_RealArrayStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_RealArrayStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_RealListRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_RealListRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_RealListStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_RealListStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_RealRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_RealRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_RealStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_RealStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_ReferenceArrayRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_ReferenceArrayRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_ReferenceArrayStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_ReferenceArrayStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_ReferenceListRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_ReferenceListRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_ReferenceListStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_ReferenceListStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_RelationRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_RelationRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_RelationStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_RelationStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_TickRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_TickRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_TickStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_TickStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_TreeNodeRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_TreeNodeRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_TreeNodeStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_TreeNodeStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_UAttributeRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_UAttributeRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_UAttributeStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_UAttributeStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_VariableRetrievalDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_VariableRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDataStd/MDataStd_VariableStorageDriver.cxx" )
  SOURCE_GROUP (MDataStd FILES "../../../src/MDataStd/MDataStd_VariableStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MFunction/MFunction.cxx" )
  SOURCE_GROUP (MFunction FILES "../../../src/MFunction/MFunction.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MFunction/MFunction_FunctionRetrievalDriver.cxx" )
  SOURCE_GROUP (MFunction FILES "../../../src/MFunction/MFunction_FunctionRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MFunction/MFunction_FunctionStorageDriver.cxx" )
  SOURCE_GROUP (MFunction FILES "../../../src/MFunction/MFunction_FunctionStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDocStd/MDocStd.cxx" )
  SOURCE_GROUP (MDocStd FILES "../../../src/MDocStd/MDocStd.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDocStd/MDocStd_DocumentRetrievalDriver.cxx" )
  SOURCE_GROUP (MDocStd FILES "../../../src/MDocStd/MDocStd_DocumentRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDocStd/MDocStd_DocumentStorageDriver.cxx" )
  SOURCE_GROUP (MDocStd FILES "../../../src/MDocStd/MDocStd_DocumentStorageDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDocStd/MDocStd_XLinkRetrievalDriver.cxx" )
  SOURCE_GROUP (MDocStd FILES "../../../src/MDocStd/MDocStd_XLinkRetrievalDriver.cxx")

  list( APPEND TKPLCAF_USED_SRCFILES "../../../src/MDocStd/MDocStd_XLinkStorageDriver.cxx" )
  SOURCE_GROUP (MDocStd FILES "../../../src/MDocStd/MDocStd_XLinkStorageDriver.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKPLCAF)
 add_library( TKPLCAF SHARED ${TKPLCAF_USED_SRCFILES} )

 set_property(TARGET TKPLCAF PROPERTY FOLDER ApplicationFramework)

 install( TARGETS TKPLCAF
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKPLCAF.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKPLCAF PROPERTIES COMPILE_FLAGS "${TKPLCAF_PRECOMPILED_DEFS}" )
 include_directories( ${TKPLCAF_COMPILER_DIRECTORIES} )
 target_link_libraries( TKPLCAF ${TKPLCAF_USED_LIBS} )
endif()
