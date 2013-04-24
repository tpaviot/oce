project(TKCDF)

if (WIN32)
  list( APPEND TKCDF_PRECOMPILED_DEFS "-D__CDM_DLL" )
  list( APPEND TKCDF_PRECOMPILED_DEFS "-D__PCDM_DLL" )
  list( APPEND TKCDF_PRECOMPILED_DEFS "-D__CDF_DLL" )
  list( APPEND TKCDF_PRECOMPILED_DEFS "-D__UTL_DLL" )
  list( APPEND TKCDF_PRECOMPILED_DEFS "-D__LDOM_DLL" )
  string( REGEX REPLACE ";" " " TKCDF_PRECOMPILED_DEFS "${TKCDF_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKCDF_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKCDF_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKCDF_COMPILER_DIRECTORIES "../../../drv/CDM" )
  list( APPEND TKCDF_COMPILER_DIRECTORIES "../../../src/CDM" )
  list( APPEND TKCDF_COMPILER_DIRECTORIES "../../../drv/PCDM" )
  list( APPEND TKCDF_COMPILER_DIRECTORIES "../../../src/PCDM" )
  list( APPEND TKCDF_COMPILER_DIRECTORIES "../../../drv/CDF" )
  list( APPEND TKCDF_COMPILER_DIRECTORIES "../../../src/CDF" )
  list( APPEND TKCDF_COMPILER_DIRECTORIES "../../../drv/UTL" )
  list( APPEND TKCDF_COMPILER_DIRECTORIES "../../../src/UTL" )
  list( APPEND TKCDF_COMPILER_DIRECTORIES "../../../drv/LDOM" )
  list( APPEND TKCDF_COMPILER_DIRECTORIES "../../../src/LDOM" )

if (WIN32)
else()
endif()

  list( APPEND TKCDF_USED_LIBS TKernel )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_DataMapIteratorOfMetaDataLookUpTable_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_DataMapIteratorOfMetaDataLookUpTable_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_DataMapIteratorOfPresentationDirectory_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_DataMapIteratorOfPresentationDirectory_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_DataMapNodeOfMetaDataLookUpTable_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_DataMapNodeOfMetaDataLookUpTable_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_DataMapNodeOfPresentationDirectory_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_DataMapNodeOfPresentationDirectory_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_DocumentHasher_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_DocumentHasher_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_ListIteratorOfListOfDocument_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_ListIteratorOfListOfDocument_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_ListIteratorOfListOfReferences_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_ListIteratorOfListOfReferences_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_ListNodeOfListOfDocument_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_ListNodeOfListOfDocument_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_ListNodeOfListOfReferences_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_ListNodeOfListOfReferences_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_ListOfDocument_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_ListOfDocument_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_ListOfReferences_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_ListOfReferences_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_MapIteratorOfMapOfDocument_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_MapIteratorOfMapOfDocument_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_MapOfDocument_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_MapOfDocument_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_MetaDataLookUpTable_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_MetaDataLookUpTable_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_PresentationDirectory_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_PresentationDirectory_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_StackIteratorOfStackOfDocument_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_StackIteratorOfStackOfDocument_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_StackNodeOfStackOfDocument_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_StackNodeOfStackOfDocument_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_StackOfDocument_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_StackOfDocument_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDM/CDM_StdMapNodeOfMapOfDocument_0.cxx" )
  SOURCE_GROUP (CDM FILES "../../../drv/CDM/CDM_StdMapNodeOfMapOfDocument_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/CDM/CDM_Application.cxx" )
  SOURCE_GROUP (CDM FILES "../../../src/CDM/CDM_Application.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/CDM/CDM_COutMessageDriver.cxx" )
  SOURCE_GROUP (CDM FILES "../../../src/CDM/CDM_COutMessageDriver.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/CDM/CDM_Document.cxx" )
  SOURCE_GROUP (CDM FILES "../../../src/CDM/CDM_Document.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/CDM/CDM_MessageDriver.cxx" )
  SOURCE_GROUP (CDM FILES "../../../src/CDM/CDM_MessageDriver.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/CDM/CDM_MetaData.cxx" )
  SOURCE_GROUP (CDM FILES "../../../src/CDM/CDM_MetaData.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/CDM/CDM_NullMessageDriver.cxx" )
  SOURCE_GROUP (CDM FILES "../../../src/CDM/CDM_NullMessageDriver.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/CDM/CDM_Reference.cxx" )
  SOURCE_GROUP (CDM FILES "../../../src/CDM/CDM_Reference.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/CDM/CDM_ReferenceIterator.cxx" )
  SOURCE_GROUP (CDM FILES "../../../src/CDM/CDM_ReferenceIterator.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/PCDM/PCDM_DriverError_0.cxx" )
  SOURCE_GROUP (PCDM FILES "../../../drv/PCDM/PCDM_DriverError_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/PCDM/PCDM_SequenceNodeOfSequenceOfDocument_0.cxx" )
  SOURCE_GROUP (PCDM FILES "../../../drv/PCDM/PCDM_SequenceNodeOfSequenceOfDocument_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/PCDM/PCDM_SequenceNodeOfSequenceOfReference_0.cxx" )
  SOURCE_GROUP (PCDM FILES "../../../drv/PCDM/PCDM_SequenceNodeOfSequenceOfReference_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/PCDM/PCDM_SequenceOfDocument_0.cxx" )
  SOURCE_GROUP (PCDM FILES "../../../drv/PCDM/PCDM_SequenceOfDocument_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/PCDM/PCDM_SequenceOfReference_0.cxx" )
  SOURCE_GROUP (PCDM FILES "../../../drv/PCDM/PCDM_SequenceOfReference_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/PCDM/PCDM.cxx" )
  SOURCE_GROUP (PCDM FILES "../../../src/PCDM/PCDM.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/PCDM/PCDM_DOMHeaderParser.cxx" )
  SOURCE_GROUP (PCDM FILES "../../../src/PCDM/PCDM_DOMHeaderParser.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/PCDM/PCDM_Document.cxx" )
  SOURCE_GROUP (PCDM FILES "../../../src/PCDM/PCDM_Document.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/PCDM/PCDM_ReadWriter.cxx" )
  SOURCE_GROUP (PCDM FILES "../../../src/PCDM/PCDM_ReadWriter.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/PCDM/PCDM_ReadWriter_1.cxx" )
  SOURCE_GROUP (PCDM FILES "../../../src/PCDM/PCDM_ReadWriter_1.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/PCDM/PCDM_Reader.cxx" )
  SOURCE_GROUP (PCDM FILES "../../../src/PCDM/PCDM_Reader.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/PCDM/PCDM_Reference.cxx" )
  SOURCE_GROUP (PCDM FILES "../../../src/PCDM/PCDM_Reference.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/PCDM/PCDM_ReferenceIterator.cxx" )
  SOURCE_GROUP (PCDM FILES "../../../src/PCDM/PCDM_ReferenceIterator.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/PCDM/PCDM_RetrievalDriver.cxx" )
  SOURCE_GROUP (PCDM FILES "../../../src/PCDM/PCDM_RetrievalDriver.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/PCDM/PCDM_StorageDriver.cxx" )
  SOURCE_GROUP (PCDM FILES "../../../src/PCDM/PCDM_StorageDriver.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/PCDM/PCDM_Writer.cxx" )
  SOURCE_GROUP (PCDM FILES "../../../src/PCDM/PCDM_Writer.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../drv/CDF/CDF_MetaDataDriverError_0.cxx" )
  SOURCE_GROUP (CDF FILES "../../../drv/CDF/CDF_MetaDataDriverError_0.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/CDF/CDF.cxx" )
  SOURCE_GROUP (CDF FILES "../../../src/CDF/CDF.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/CDF/CDF_Application.cxx" )
  SOURCE_GROUP (CDF FILES "../../../src/CDF/CDF_Application.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/CDF/CDF_Directory.cxx" )
  SOURCE_GROUP (CDF FILES "../../../src/CDF/CDF_Directory.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/CDF/CDF_DirectoryIterator.cxx" )
  SOURCE_GROUP (CDF FILES "../../../src/CDF/CDF_DirectoryIterator.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/CDF/CDF_MetaDataDriver.cxx" )
  SOURCE_GROUP (CDF FILES "../../../src/CDF/CDF_MetaDataDriver.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/CDF/CDF_MetaDataDriverFactory.cxx" )
  SOURCE_GROUP (CDF FILES "../../../src/CDF/CDF_MetaDataDriverFactory.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/CDF/CDF_Session.cxx" )
  SOURCE_GROUP (CDF FILES "../../../src/CDF/CDF_Session.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/CDF/CDF_Store.cxx" )
  SOURCE_GROUP (CDF FILES "../../../src/CDF/CDF_Store.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/CDF/CDF_StoreList.cxx" )
  SOURCE_GROUP (CDF FILES "../../../src/CDF/CDF_StoreList.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/CDF/CDF_Timer.cxx" )
  SOURCE_GROUP (CDF FILES "../../../src/CDF/CDF_Timer.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/UTL/UTL.cxx" )
  SOURCE_GROUP (UTL FILES "../../../src/UTL/UTL.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOMBasicString.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOMBasicString.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOMParser.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOMParser.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOMString.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOMString.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOM_Attr.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOM_Attr.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOM_BasicAttribute.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOM_BasicAttribute.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOM_BasicElement.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOM_BasicElement.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOM_BasicNode.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOM_BasicNode.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOM_BasicText.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOM_BasicText.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOM_CharReference.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOM_CharReference.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOM_CharacterData.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOM_CharacterData.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOM_Document.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOM_Document.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOM_Element.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOM_Element.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOM_LDOMImplementation.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOM_LDOMImplementation.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOM_MemManager.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOM_MemManager.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOM_Node.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOM_Node.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOM_NodeList.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOM_NodeList.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOM_OSStream.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOM_OSStream.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOM_XmlReader.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOM_XmlReader.cxx")

  list( APPEND TKCDF_USED_SRCFILES "../../../src/LDOM/LDOM_XmlWriter.cxx" )
  SOURCE_GROUP (LDOM FILES "../../../src/LDOM/LDOM_XmlWriter.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKCDF)
 add_library( TKCDF SHARED ${TKCDF_USED_SRCFILES} )

 set_property(TARGET TKCDF PROPERTY FOLDER ApplicationFramework)

 install( TARGETS TKCDF
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKCDF.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKCDF PROPERTIES COMPILE_FLAGS "${TKCDF_PRECOMPILED_DEFS}" )
 include_directories( ${TKCDF_COMPILER_DIRECTORIES} )
 target_link_libraries( TKCDF ${TKCDF_USED_LIBS} )
endif()
