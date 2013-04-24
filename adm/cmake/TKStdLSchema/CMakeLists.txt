project(TKStdLSchema)

if (WIN32)
  list( APPEND TKStdLSchema_PRECOMPILED_DEFS "-D__StdLSchema_DLL" )
  list( APPEND TKStdLSchema_PRECOMPILED_DEFS "-D__StdLDrivers_DLL" )
  string( REGEX REPLACE ";" " " TKStdLSchema_PRECOMPILED_DEFS "${TKStdLSchema_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKStdLSchema_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKStdLSchema_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKStdLSchema_COMPILER_DIRECTORIES "../../../drv/StdLSchema" )
  list( APPEND TKStdLSchema_COMPILER_DIRECTORIES "../../../src/StdLSchema" )
  list( APPEND TKStdLSchema_COMPILER_DIRECTORIES "../../../drv/StdLDrivers" )
  list( APPEND TKStdLSchema_COMPILER_DIRECTORIES "../../../src/StdLDrivers" )

if (WIN32)
else()
endif()

  list( APPEND TKStdLSchema_USED_LIBS TKCDF )
  list( APPEND TKStdLSchema_USED_LIBS PTKernel )
  list( APPEND TKStdLSchema_USED_LIBS TKernel )
  list( APPEND TKStdLSchema_USED_LIBS TKShapeSchema )
  list( APPEND TKStdLSchema_USED_LIBS TKLCAF )
  list( APPEND TKStdLSchema_USED_LIBS TKPLCAF )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_DBC_VArrayOfCharacter.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_DBC_VArrayOfCharacter.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_DBC_VArrayOfExtCharacter.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_DBC_VArrayOfExtCharacter.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PCDM_Document.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PCDM_Document.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PColStd_FieldOfHArray1OfExtendedString.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PColStd_FieldOfHArray1OfExtendedString.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PColStd_FieldOfHArray1OfInteger.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PColStd_FieldOfHArray1OfInteger.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PColStd_FieldOfHArray1OfReal.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PColStd_FieldOfHArray1OfReal.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PColStd_FieldOfHArray2OfInteger.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PColStd_FieldOfHArray2OfInteger.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PColStd_HArray1OfExtendedString.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PColStd_HArray1OfExtendedString.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PColStd_HArray1OfInteger.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PColStd_HArray1OfInteger.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PColStd_HArray1OfReal.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PColStd_HArray1OfReal.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PColStd_HArray2OfInteger.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PColStd_HArray2OfInteger.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PCollection_HAsciiString.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PCollection_HAsciiString.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PCollection_HExtendedString.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PCollection_HExtendedString.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDF_Attribute.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDF_Attribute.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDF_Data.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDF_Data.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDF_FieldOfHAttributeArray1.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDF_FieldOfHAttributeArray1.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDF_HAttributeArray1.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDF_HAttributeArray1.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDF_Reference.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDF_Reference.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDF_TagSource.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDF_TagSource.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_AsciiString.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_AsciiString.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_BooleanArray.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_BooleanArray.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_BooleanList.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_BooleanList.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_ByteArray.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_ByteArray.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_ByteArray_1.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_ByteArray_1.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_Comment.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_Comment.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_Directory.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_Directory.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_Expression.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_Expression.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_ExtStringArray.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_ExtStringArray.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_ExtStringArray_1.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_ExtStringArray_1.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_ExtStringList.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_ExtStringList.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_FieldOfHArray1OfByte.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_FieldOfHArray1OfByte.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_FieldOfHArray1OfHArray1OfInteger.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_FieldOfHArray1OfHArray1OfInteger.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_FieldOfHArray1OfHArray1OfReal.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_FieldOfHArray1OfHArray1OfReal.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_FieldOfHArray1OfHAsciiString.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_FieldOfHArray1OfHAsciiString.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_HArray1OfByte.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_HArray1OfByte.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_HArray1OfHArray1OfInteger.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_HArray1OfHArray1OfInteger.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_HArray1OfHArray1OfReal.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_HArray1OfHArray1OfReal.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_HArray1OfHAsciiString.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_HArray1OfHAsciiString.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_IntPackedMap.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_IntPackedMap.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_IntPackedMap_1.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_IntPackedMap_1.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_Integer.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_Integer.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_IntegerArray.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_IntegerArray.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_IntegerArray_1.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_IntegerArray_1.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_IntegerList.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_IntegerList.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_Name.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_Name.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_NamedData.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_NamedData.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_NoteBook.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_NoteBook.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_Real.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_Real.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_RealArray.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_RealArray.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_RealArray_1.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_RealArray_1.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_RealList.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_RealList.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_ReferenceArray.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_ReferenceArray.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_ReferenceList.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_ReferenceList.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_Relation.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_Relation.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_Tick.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_Tick.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_TreeNode.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_TreeNode.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_UAttribute.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_UAttribute.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDataStd_Variable.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDataStd_Variable.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDocStd_Document.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDocStd_Document.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PDocStd_XLink.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PDocStd_XLink.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_PFunction_Function.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_PFunction_Function.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_Standard_GUID.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_Standard_GUID.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_Standard_Persistent.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_Standard_Persistent.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../drv/StdLSchema/StdLSchema_Standard_Storable.cxx" )
  SOURCE_GROUP (StdLSchema FILES "../../../drv/StdLSchema/StdLSchema_Standard_Storable.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../src/StdLDrivers/StdLDrivers.cxx" )
  SOURCE_GROUP (StdLDrivers FILES "../../../src/StdLDrivers/StdLDrivers.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../src/StdLDrivers/StdLDrivers_DocumentRetrievalDriver.cxx" )
  SOURCE_GROUP (StdLDrivers FILES "../../../src/StdLDrivers/StdLDrivers_DocumentRetrievalDriver.cxx")

  list( APPEND TKStdLSchema_USED_SRCFILES "../../../src/StdLDrivers/StdLDrivers_DocumentStorageDriver.cxx" )
  SOURCE_GROUP (StdLDrivers FILES "../../../src/StdLDrivers/StdLDrivers_DocumentStorageDriver.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKStdLSchema)
 add_library( TKStdLSchema SHARED ${TKStdLSchema_USED_SRCFILES} )

 set_property(TARGET TKStdLSchema PROPERTY FOLDER ApplicationFramework)

 install( TARGETS TKStdLSchema
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKStdLSchema.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKStdLSchema PROPERTIES COMPILE_FLAGS "${TKStdLSchema_PRECOMPILED_DEFS}" )
 include_directories( ${TKStdLSchema_COMPILER_DIRECTORIES} )
 target_link_libraries( TKStdLSchema ${TKStdLSchema_USED_LIBS} )
endif()
