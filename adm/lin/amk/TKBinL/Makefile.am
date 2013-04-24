# Makefile.am for Open Cascade toolkit TKBinL
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/BinMDF : @top_srcdir@/src/BinMDF: \
@top_srcdir@/drv/BinMDataStd : @top_srcdir@/src/BinMDataStd: \
@top_srcdir@/drv/BinMFunction : @top_srcdir@/src/BinMFunction: \
@top_srcdir@/drv/BinMDocStd : @top_srcdir@/src/BinMDocStd: \
@top_srcdir@/drv/BinObjMgt : @top_srcdir@/src/BinObjMgt: \
@top_srcdir@/drv/BinLDrivers : @top_srcdir@/src/BinLDrivers


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/BinMDF -I@top_srcdir@/src/BinMDF \
-I@top_srcdir@/drv/BinMDataStd -I@top_srcdir@/src/BinMDataStd \
-I@top_srcdir@/drv/BinMFunction -I@top_srcdir@/src/BinMFunction \
-I@top_srcdir@/drv/BinMDocStd -I@top_srcdir@/src/BinMDocStd \
-I@top_srcdir@/drv/BinObjMgt -I@top_srcdir@/src/BinObjMgt \
-I@top_srcdir@/drv/BinLDrivers -I@top_srcdir@/src/BinLDrivers


lib_LTLIBRARIES=libTKBinL.la

libTKBinL_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKCDF/libTKCDF.la \
../TKernel/libTKernel.la \
../TKLCAF/libTKLCAF.la \
$(STLPort_LIB) 

libTKBinL_la_SOURCES = \
@top_srcdir@/drv/BinMDF/BinMDF_DataMapIteratorOfTypeADriverMap_0.cxx \
@top_srcdir@/drv/BinMDF/BinMDF_DataMapNodeOfTypeADriverMap_0.cxx \
@top_srcdir@/drv/BinMDF/BinMDF_DoubleMapIteratorOfTypeIdMap_0.cxx \
@top_srcdir@/drv/BinMDF/BinMDF_DoubleMapNodeOfTypeIdMap_0.cxx \
@top_srcdir@/drv/BinMDF/BinMDF_TypeADriverMap_0.cxx \
@top_srcdir@/drv/BinMDF/BinMDF_TypeIdMap_0.cxx \
@top_srcdir@/src/BinLDrivers/BinLDrivers.cxx \
@top_srcdir@/src/BinLDrivers/BinLDrivers_DocumentRetrievalDriver.cxx \
@top_srcdir@/src/BinLDrivers/BinLDrivers_DocumentSection.cxx \
@top_srcdir@/src/BinLDrivers/BinLDrivers_DocumentStorageDriver.cxx \
@top_srcdir@/src/BinMDF/BinMDF.cxx \
@top_srcdir@/src/BinMDF/BinMDF_ADriver.cxx \
@top_srcdir@/src/BinMDF/BinMDF_ADriverTable.cxx \
@top_srcdir@/src/BinMDF/BinMDF_ReferenceDriver.cxx \
@top_srcdir@/src/BinMDF/BinMDF_TagSourceDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_AsciiStringDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_BooleanArrayDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_BooleanListDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_ByteArrayDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_CommentDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_DirectoryDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_ExpressionDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_ExtStringArrayDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_ExtStringListDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_IntPackedMapDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_IntegerArrayDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_IntegerDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_IntegerListDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_NameDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_NamedDataDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_NoteBookDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_RealArrayDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_RealDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_RealListDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_ReferenceArrayDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_ReferenceListDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_RelationDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_TickDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_TreeNodeDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_UAttributeDriver.cxx \
@top_srcdir@/src/BinMDataStd/BinMDataStd_VariableDriver.cxx \
@top_srcdir@/src/BinMDocStd/BinMDocStd.cxx \
@top_srcdir@/src/BinMDocStd/BinMDocStd_XLinkDriver.cxx \
@top_srcdir@/src/BinMFunction/BinMFunction.cxx \
@top_srcdir@/src/BinMFunction/BinMFunction_FunctionDriver.cxx \
@top_srcdir@/src/BinMFunction/BinMFunction_GraphNodeDriver.cxx \
@top_srcdir@/src/BinMFunction/BinMFunction_ScopeDriver.cxx \
@top_srcdir@/src/BinObjMgt/BinObjMgt_Persistent.cxx

