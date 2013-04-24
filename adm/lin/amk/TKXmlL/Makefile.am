# Makefile.am for Open Cascade toolkit TKXmlL
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/XmlLDrivers : @top_srcdir@/src/XmlLDrivers: \
@top_srcdir@/drv/XmlMDF : @top_srcdir@/src/XmlMDF: \
@top_srcdir@/drv/XmlMDataStd : @top_srcdir@/src/XmlMDataStd: \
@top_srcdir@/drv/XmlMDocStd : @top_srcdir@/src/XmlMDocStd: \
@top_srcdir@/drv/XmlMFunction : @top_srcdir@/src/XmlMFunction: \
@top_srcdir@/drv/XmlObjMgt : @top_srcdir@/src/XmlObjMgt


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/XmlLDrivers -I@top_srcdir@/src/XmlLDrivers \
-I@top_srcdir@/drv/XmlMDF -I@top_srcdir@/src/XmlMDF \
-I@top_srcdir@/drv/XmlMDataStd -I@top_srcdir@/src/XmlMDataStd \
-I@top_srcdir@/drv/XmlMDocStd -I@top_srcdir@/src/XmlMDocStd \
-I@top_srcdir@/drv/XmlMFunction -I@top_srcdir@/src/XmlMFunction \
-I@top_srcdir@/drv/XmlObjMgt -I@top_srcdir@/src/XmlObjMgt


lib_LTLIBRARIES=libTKXmlL.la

libTKXmlL_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKCDF/libTKCDF.la \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
../TKLCAF/libTKLCAF.la \
$(STLPort_LIB) 

libTKXmlL_la_SOURCES = \
@top_srcdir@/drv/XmlLDrivers/XmlLDrivers_SequenceNodeOfSequenceOfNamespaceDef_0.cxx \
@top_srcdir@/drv/XmlLDrivers/XmlLDrivers_SequenceOfNamespaceDef_0.cxx \
@top_srcdir@/drv/XmlMDF/XmlMDF_DataMapIteratorOfMapOfDriver_0.cxx \
@top_srcdir@/drv/XmlMDF/XmlMDF_DataMapIteratorOfTypeADriverMap_0.cxx \
@top_srcdir@/drv/XmlMDF/XmlMDF_DataMapNodeOfMapOfDriver_0.cxx \
@top_srcdir@/drv/XmlMDF/XmlMDF_DataMapNodeOfTypeADriverMap_0.cxx \
@top_srcdir@/drv/XmlMDF/XmlMDF_MapOfDriver_0.cxx \
@top_srcdir@/drv/XmlMDF/XmlMDF_TypeADriverMap_0.cxx \
@top_srcdir@/src/XmlLDrivers/XmlLDrivers.cxx \
@top_srcdir@/src/XmlLDrivers/XmlLDrivers_DocumentRetrievalDriver.cxx \
@top_srcdir@/src/XmlLDrivers/XmlLDrivers_DocumentStorageDriver.cxx \
@top_srcdir@/src/XmlLDrivers/XmlLDrivers_NamespaceDef.cxx \
@top_srcdir@/src/XmlMDF/XmlMDF.cxx \
@top_srcdir@/src/XmlMDF/XmlMDF_ADriver.cxx \
@top_srcdir@/src/XmlMDF/XmlMDF_ADriverTable.cxx \
@top_srcdir@/src/XmlMDF/XmlMDF_ReferenceDriver.cxx \
@top_srcdir@/src/XmlMDF/XmlMDF_TagSourceDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_AsciiStringDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_BooleanArrayDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_BooleanListDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_ByteArrayDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_CommentDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_DirectoryDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_ExpressionDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_ExtStringArrayDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_ExtStringListDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_IntPackedMapDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_IntegerArrayDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_IntegerDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_IntegerListDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_NameDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_NamedDataDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_NoteBookDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_RealArrayDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_RealDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_RealListDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_ReferenceArrayDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_ReferenceListDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_RelationDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_TickDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_TreeNodeDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_UAttributeDriver.cxx \
@top_srcdir@/src/XmlMDataStd/XmlMDataStd_VariableDriver.cxx \
@top_srcdir@/src/XmlMDocStd/XmlMDocStd.cxx \
@top_srcdir@/src/XmlMDocStd/XmlMDocStd_XLinkDriver.cxx \
@top_srcdir@/src/XmlMFunction/XmlMFunction.cxx \
@top_srcdir@/src/XmlMFunction/XmlMFunction_FunctionDriver.cxx \
@top_srcdir@/src/XmlMFunction/XmlMFunction_GraphNodeDriver.cxx \
@top_srcdir@/src/XmlMFunction/XmlMFunction_ScopeDriver.cxx \
@top_srcdir@/src/XmlObjMgt/XmlObjMgt.cxx \
@top_srcdir@/src/XmlObjMgt/XmlObjMgt_GP.cxx \
@top_srcdir@/src/XmlObjMgt/XmlObjMgt_Persistent.cxx

