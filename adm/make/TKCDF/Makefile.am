# Makefile.am for Open Cascade toolkit TKCDF
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/CDM : @top_srcdir@/src/CDM: \
@top_srcdir@/drv/PCDM : @top_srcdir@/src/PCDM: \
@top_srcdir@/drv/CDF : @top_srcdir@/src/CDF: \
@top_srcdir@/drv/UTL : @top_srcdir@/src/UTL: \
@top_srcdir@/drv/LDOM : @top_srcdir@/src/LDOM


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/CDM -I@top_srcdir@/src/CDM \
-I@top_srcdir@/drv/PCDM -I@top_srcdir@/src/PCDM \
-I@top_srcdir@/drv/CDF -I@top_srcdir@/src/CDF \
-I@top_srcdir@/drv/UTL -I@top_srcdir@/src/UTL \
-I@top_srcdir@/drv/LDOM -I@top_srcdir@/src/LDOM


lib_LTLIBRARIES=libTKCDF.la

libTKCDF_la_LIBADD = $(CSF_OPT_LIBS) \
../TKernel/libTKernel.la


libTKCDF_la_SOURCES = \
@top_srcdir@/drv/CDF/CDF_MetaDataDriverError_0.cxx \
@top_srcdir@/drv/CDM/CDM_DataMapIteratorOfMetaDataLookUpTable_0.cxx \
@top_srcdir@/drv/CDM/CDM_DataMapIteratorOfPresentationDirectory_0.cxx \
@top_srcdir@/drv/CDM/CDM_DataMapNodeOfMetaDataLookUpTable_0.cxx \
@top_srcdir@/drv/CDM/CDM_DataMapNodeOfPresentationDirectory_0.cxx \
@top_srcdir@/drv/CDM/CDM_DocumentHasher_0.cxx \
@top_srcdir@/drv/CDM/CDM_ListIteratorOfListOfDocument_0.cxx \
@top_srcdir@/drv/CDM/CDM_ListIteratorOfListOfReferences_0.cxx \
@top_srcdir@/drv/CDM/CDM_ListNodeOfListOfDocument_0.cxx \
@top_srcdir@/drv/CDM/CDM_ListNodeOfListOfReferences_0.cxx \
@top_srcdir@/drv/CDM/CDM_ListOfDocument_0.cxx \
@top_srcdir@/drv/CDM/CDM_ListOfReferences_0.cxx \
@top_srcdir@/drv/CDM/CDM_MapIteratorOfMapOfDocument_0.cxx \
@top_srcdir@/drv/CDM/CDM_MapOfDocument_0.cxx \
@top_srcdir@/drv/CDM/CDM_MetaDataLookUpTable_0.cxx \
@top_srcdir@/drv/CDM/CDM_PresentationDirectory_0.cxx \
@top_srcdir@/drv/CDM/CDM_StackIteratorOfStackOfDocument_0.cxx \
@top_srcdir@/drv/CDM/CDM_StackNodeOfStackOfDocument_0.cxx \
@top_srcdir@/drv/CDM/CDM_StackOfDocument_0.cxx \
@top_srcdir@/drv/CDM/CDM_StdMapNodeOfMapOfDocument_0.cxx \
@top_srcdir@/drv/PCDM/PCDM_DriverError_0.cxx \
@top_srcdir@/drv/PCDM/PCDM_SequenceNodeOfSequenceOfDocument_0.cxx \
@top_srcdir@/drv/PCDM/PCDM_SequenceNodeOfSequenceOfReference_0.cxx \
@top_srcdir@/drv/PCDM/PCDM_SequenceOfDocument_0.cxx \
@top_srcdir@/drv/PCDM/PCDM_SequenceOfReference_0.cxx \
@top_srcdir@/src/CDF/CDF.cxx \
@top_srcdir@/src/CDF/CDF_Application.cxx \
@top_srcdir@/src/CDF/CDF_Directory.cxx \
@top_srcdir@/src/CDF/CDF_DirectoryIterator.cxx \
@top_srcdir@/src/CDF/CDF_MetaDataDriver.cxx \
@top_srcdir@/src/CDF/CDF_MetaDataDriverFactory.cxx \
@top_srcdir@/src/CDF/CDF_Session.cxx \
@top_srcdir@/src/CDF/CDF_Store.cxx \
@top_srcdir@/src/CDF/CDF_StoreList.cxx \
@top_srcdir@/src/CDF/CDF_Timer.cxx \
@top_srcdir@/src/CDM/CDM_Application.cxx \
@top_srcdir@/src/CDM/CDM_COutMessageDriver.cxx \
@top_srcdir@/src/CDM/CDM_Document.cxx \
@top_srcdir@/src/CDM/CDM_MessageDriver.cxx \
@top_srcdir@/src/CDM/CDM_MetaData.cxx \
@top_srcdir@/src/CDM/CDM_NullMessageDriver.cxx \
@top_srcdir@/src/CDM/CDM_Reference.cxx \
@top_srcdir@/src/CDM/CDM_ReferenceIterator.cxx \
@top_srcdir@/src/LDOM/LDOMBasicString.cxx \
@top_srcdir@/src/LDOM/LDOMParser.cxx \
@top_srcdir@/src/LDOM/LDOMString.cxx \
@top_srcdir@/src/LDOM/LDOM_Attr.cxx \
@top_srcdir@/src/LDOM/LDOM_BasicAttribute.cxx \
@top_srcdir@/src/LDOM/LDOM_BasicElement.cxx \
@top_srcdir@/src/LDOM/LDOM_BasicNode.cxx \
@top_srcdir@/src/LDOM/LDOM_BasicText.cxx \
@top_srcdir@/src/LDOM/LDOM_CharReference.cxx \
@top_srcdir@/src/LDOM/LDOM_CharacterData.cxx \
@top_srcdir@/src/LDOM/LDOM_Document.cxx \
@top_srcdir@/src/LDOM/LDOM_Element.cxx \
@top_srcdir@/src/LDOM/LDOM_LDOMImplementation.cxx \
@top_srcdir@/src/LDOM/LDOM_MemManager.cxx \
@top_srcdir@/src/LDOM/LDOM_Node.cxx \
@top_srcdir@/src/LDOM/LDOM_NodeList.cxx \
@top_srcdir@/src/LDOM/LDOM_OSStream.cxx \
@top_srcdir@/src/LDOM/LDOM_XmlReader.cxx \
@top_srcdir@/src/LDOM/LDOM_XmlWriter.cxx \
@top_srcdir@/src/PCDM/PCDM.cxx \
@top_srcdir@/src/PCDM/PCDM_DOMHeaderParser.cxx \
@top_srcdir@/src/PCDM/PCDM_Document.cxx \
@top_srcdir@/src/PCDM/PCDM_ReadWriter.cxx \
@top_srcdir@/src/PCDM/PCDM_ReadWriter_1.cxx \
@top_srcdir@/src/PCDM/PCDM_Reader.cxx \
@top_srcdir@/src/PCDM/PCDM_Reference.cxx \
@top_srcdir@/src/PCDM/PCDM_ReferenceIterator.cxx \
@top_srcdir@/src/PCDM/PCDM_RetrievalDriver.cxx \
@top_srcdir@/src/PCDM/PCDM_StorageDriver.cxx \
@top_srcdir@/src/PCDM/PCDM_Writer.cxx \
@top_srcdir@/src/UTL/UTL.cxx

