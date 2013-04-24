# Makefile.am for Open Cascade toolkit TKStdLSchema
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/StdLSchema : @top_srcdir@/src/StdLSchema: \
@top_srcdir@/drv/StdLDrivers : @top_srcdir@/src/StdLDrivers


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/StdLSchema -I@top_srcdir@/src/StdLSchema \
-I@top_srcdir@/drv/StdLDrivers -I@top_srcdir@/src/StdLDrivers


lib_LTLIBRARIES=libTKStdLSchema.la

libTKStdLSchema_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKCDF/libTKCDF.la \
../PTKernel/libPTKernel.la \
../TKernel/libTKernel.la \
../TKShapeSchema/libTKShapeSchema.la \
../TKLCAF/libTKLCAF.la \
../TKPLCAF/libTKPLCAF.la \
$(STLPort_LIB) 

libTKStdLSchema_la_SOURCES = \
@top_srcdir@/drv/StdLSchema/StdLSchema.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_DBC_VArrayOfCharacter.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_DBC_VArrayOfExtCharacter.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PCDM_Document.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PColStd_FieldOfHArray1OfExtendedString.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PColStd_FieldOfHArray1OfInteger.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PColStd_FieldOfHArray1OfReal.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PColStd_FieldOfHArray2OfInteger.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PColStd_HArray1OfExtendedString.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PColStd_HArray1OfInteger.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PColStd_HArray1OfReal.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PColStd_HArray2OfInteger.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PCollection_HAsciiString.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PCollection_HExtendedString.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDF_Attribute.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDF_Data.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDF_FieldOfHAttributeArray1.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDF_HAttributeArray1.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDF_Reference.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDF_TagSource.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_AsciiString.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_BooleanArray.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_BooleanList.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_ByteArray.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_ByteArray_1.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_Comment.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_Directory.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_Expression.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_ExtStringArray.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_ExtStringArray_1.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_ExtStringList.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_FieldOfHArray1OfByte.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_FieldOfHArray1OfHArray1OfInteger.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_FieldOfHArray1OfHArray1OfReal.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_FieldOfHArray1OfHAsciiString.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_HArray1OfByte.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_HArray1OfHArray1OfInteger.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_HArray1OfHArray1OfReal.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_HArray1OfHAsciiString.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_IntPackedMap.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_IntPackedMap_1.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_Integer.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_IntegerArray.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_IntegerArray_1.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_IntegerList.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_Name.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_NamedData.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_NoteBook.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_Real.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_RealArray.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_RealArray_1.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_RealList.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_ReferenceArray.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_ReferenceList.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_Relation.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_Tick.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_TreeNode.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_UAttribute.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDataStd_Variable.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDocStd_Document.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PDocStd_XLink.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_PFunction_Function.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_Standard_GUID.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_Standard_Persistent.cxx \
@top_srcdir@/drv/StdLSchema/StdLSchema_Standard_Storable.cxx \
@top_srcdir@/src/StdLDrivers/StdLDrivers.cxx \
@top_srcdir@/src/StdLDrivers/StdLDrivers_DocumentRetrievalDriver.cxx \
@top_srcdir@/src/StdLDrivers/StdLDrivers_DocumentStorageDriver.cxx

