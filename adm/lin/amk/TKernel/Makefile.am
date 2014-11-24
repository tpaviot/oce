# Makefile.am for Open Cascade toolkit TKernel
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/FSD : @top_srcdir@/src/FSD: \
@top_srcdir@/drv/MMgt : @top_srcdir@/src/MMgt: \
@top_srcdir@/drv/OSD : @top_srcdir@/src/OSD: \
@top_srcdir@/drv/Plugin : @top_srcdir@/src/Plugin: \
@top_srcdir@/drv/Quantity : @top_srcdir@/src/Quantity: \
@top_srcdir@/drv/Resource : @top_srcdir@/src/Resource: \
@top_srcdir@/drv/SortTools : @top_srcdir@/src/SortTools: \
@top_srcdir@/drv/Standard : @top_srcdir@/src/Standard: \
@top_srcdir@/drv/StdFail : @top_srcdir@/src/StdFail: \
@top_srcdir@/drv/Storage : @top_srcdir@/src/Storage: \
@top_srcdir@/drv/TColStd : @top_srcdir@/src/TColStd: \
@top_srcdir@/drv/TCollection : @top_srcdir@/src/TCollection: \
@top_srcdir@/drv/TShort : @top_srcdir@/src/TShort: \
@top_srcdir@/drv/Units : @top_srcdir@/src/Units: \
@top_srcdir@/drv/UnitsAPI : @top_srcdir@/src/UnitsAPI: \
@top_srcdir@/drv/Dico : @top_srcdir@/src/Dico: \
@top_srcdir@/drv/NCollection : @top_srcdir@/src/NCollection: \
@top_srcdir@/drv/Message : @top_srcdir@/src/Message


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES) $(CSF_SOCKETLibs_INCLUDES) $(CSF_FPELibs_INCLUDES) $(CSF_ThreadLibs_INCLUDES) $(CSF_advapi32_INCLUDES) $(CSF_gdi32_INCLUDES) $(CSF_user32_INCLUDES) $(CSF_kernel32_INCLUDES) $(CSF_TBB_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/FSD -I@top_srcdir@/src/FSD \
-I@top_srcdir@/drv/MMgt -I@top_srcdir@/src/MMgt \
-I@top_srcdir@/drv/OSD -I@top_srcdir@/src/OSD \
-I@top_srcdir@/drv/Plugin -I@top_srcdir@/src/Plugin \
-I@top_srcdir@/drv/Quantity -I@top_srcdir@/src/Quantity \
-I@top_srcdir@/drv/Resource -I@top_srcdir@/src/Resource \
-I@top_srcdir@/drv/SortTools -I@top_srcdir@/src/SortTools \
-I@top_srcdir@/drv/Standard -I@top_srcdir@/src/Standard \
-I@top_srcdir@/drv/StdFail -I@top_srcdir@/src/StdFail \
-I@top_srcdir@/drv/Storage -I@top_srcdir@/src/Storage \
-I@top_srcdir@/drv/TColStd -I@top_srcdir@/src/TColStd \
-I@top_srcdir@/drv/TCollection -I@top_srcdir@/src/TCollection \
-I@top_srcdir@/drv/TShort -I@top_srcdir@/src/TShort \
-I@top_srcdir@/drv/Units -I@top_srcdir@/src/Units \
-I@top_srcdir@/drv/UnitsAPI -I@top_srcdir@/src/UnitsAPI \
-I@top_srcdir@/drv/Dico -I@top_srcdir@/src/Dico \
-I@top_srcdir@/drv/NCollection -I@top_srcdir@/src/NCollection \
-I@top_srcdir@/drv/Message -I@top_srcdir@/src/Message


lib_LTLIBRARIES=libTKernel.la

libTKernel_la_LIBADD = $(CSF_OPT_LIBS) \
 \
$(STLPort_LIB) $(CSF_SOCKETLibs_LIB) $(CSF_FPELibs_LIB) $(CSF_ThreadLibs_LIB) $(CSF_advapi32_LIB) $(CSF_gdi32_LIB) $(CSF_user32_LIB) $(CSF_kernel32_LIB) $(CSF_TBB_LIB) 

libTKernel_la_SOURCES = \
@top_srcdir@/drv/Dico/Dico_DictionaryOfInteger_0.cxx \
@top_srcdir@/drv/Dico/Dico_DictionaryOfTransient_0.cxx \
@top_srcdir@/drv/Dico/Dico_IteratorOfDictionaryOfInteger_0.cxx \
@top_srcdir@/drv/Dico/Dico_IteratorOfDictionaryOfTransient_0.cxx \
@top_srcdir@/drv/Dico/Dico_StackItemOfDictionaryOfInteger_0.cxx \
@top_srcdir@/drv/Dico/Dico_StackItemOfDictionaryOfTransient_0.cxx \
@top_srcdir@/drv/Message/Message_ListIteratorOfListOfMsg_0.cxx \
@top_srcdir@/drv/Message/Message_ListNodeOfListOfMsg_0.cxx \
@top_srcdir@/drv/Message/Message_ListOfMsg_0.cxx \
@top_srcdir@/drv/Message/Message_SequenceNodeOfSequenceOfPrinters_0.cxx \
@top_srcdir@/drv/Message/Message_SequenceNodeOfSequenceOfProgressScale_0.cxx \
@top_srcdir@/drv/Message/Message_SequenceOfPrinters_0.cxx \
@top_srcdir@/drv/Message/Message_SequenceOfProgressScale_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_ACCESS_VIOLATION_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_ARRAY_BOUNDS_EXCEEDED_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_CTRL_BREAK_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_FLT_DENORMAL_OPERAND_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_FLT_DIVIDE_BY_ZERO_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_FLT_INEXACT_RESULT_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_FLT_INVALID_OPERATION_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_FLT_OVERFLOW_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_FLT_STACK_CHECK_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_FLT_UNDERFLOW_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_ILLEGAL_INSTRUCTION_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_INT_DIVIDE_BY_ZERO_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_INT_OVERFLOW_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_INVALID_DISPOSITION_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_IN_PAGE_ERROR_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_NONCONTINUABLE_EXCEPTION_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_PRIV_INSTRUCTION_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_STACK_OVERFLOW_0.cxx \
@top_srcdir@/drv/OSD/OSD_Exception_STATUS_NO_MEMORY_0.cxx \
@top_srcdir@/drv/OSD/OSD_OSDError_0.cxx \
@top_srcdir@/drv/OSD/OSD_SIGBUS_0.cxx \
@top_srcdir@/drv/OSD/OSD_SIGHUP_0.cxx \
@top_srcdir@/drv/OSD/OSD_SIGILL_0.cxx \
@top_srcdir@/drv/OSD/OSD_SIGINT_0.cxx \
@top_srcdir@/drv/OSD/OSD_SIGKILL_0.cxx \
@top_srcdir@/drv/OSD/OSD_SIGQUIT_0.cxx \
@top_srcdir@/drv/OSD/OSD_SIGSEGV_0.cxx \
@top_srcdir@/drv/OSD/OSD_SIGSYS_0.cxx \
@top_srcdir@/drv/OSD/OSD_Signal_0.cxx \
@top_srcdir@/drv/Plugin/Plugin_DataMapIteratorOfMapOfFunctions_0.cxx \
@top_srcdir@/drv/Plugin/Plugin_DataMapNodeOfMapOfFunctions_0.cxx \
@top_srcdir@/drv/Plugin/Plugin_Failure_0.cxx \
@top_srcdir@/drv/Plugin/Plugin_MapOfFunctions_0.cxx \
@top_srcdir@/drv/Quantity/Quantity_Array1OfCoefficient_0.cxx \
@top_srcdir@/drv/Quantity/Quantity_Array1OfColor_0.cxx \
@top_srcdir@/drv/Quantity/Quantity_Array2OfColor_0.cxx \
@top_srcdir@/drv/Quantity/Quantity_ColorDefinitionError_0.cxx \
@top_srcdir@/drv/Quantity/Quantity_DateDefinitionError_0.cxx \
@top_srcdir@/drv/Quantity/Quantity_HArray1OfColor_0.cxx \
@top_srcdir@/drv/Quantity/Quantity_PeriodDefinitionError_0.cxx \
@top_srcdir@/drv/Resource/Resource_DataMapIteratorOfDataMapOfAsciiStringAsciiString_0.cxx \
@top_srcdir@/drv/Resource/Resource_DataMapIteratorOfDataMapOfAsciiStringExtendedString_0.cxx \
@top_srcdir@/drv/Resource/Resource_DataMapNodeOfDataMapOfAsciiStringAsciiString_0.cxx \
@top_srcdir@/drv/Resource/Resource_DataMapNodeOfDataMapOfAsciiStringExtendedString_0.cxx \
@top_srcdir@/drv/Resource/Resource_DataMapOfAsciiStringAsciiString_0.cxx \
@top_srcdir@/drv/Resource/Resource_DataMapOfAsciiStringExtendedString_0.cxx \
@top_srcdir@/drv/Resource/Resource_NoSuchResource_0.cxx \
@top_srcdir@/drv/Resource/Resource_QuickSortOfArray1_0.cxx \
@top_srcdir@/drv/SortTools/SortTools_HeapSortOfInteger_0.cxx \
@top_srcdir@/drv/SortTools/SortTools_HeapSortOfReal_0.cxx \
@top_srcdir@/drv/SortTools/SortTools_QuickSortOfInteger_0.cxx \
@top_srcdir@/drv/SortTools/SortTools_QuickSortOfReal_0.cxx \
@top_srcdir@/drv/SortTools/SortTools_ShellSortOfInteger_0.cxx \
@top_srcdir@/drv/SortTools/SortTools_ShellSortOfReal_0.cxx \
@top_srcdir@/drv/SortTools/SortTools_StraightInsertionSortOfInteger_0.cxx \
@top_srcdir@/drv/SortTools/SortTools_StraightInsertionSortOfReal_0.cxx \
@top_srcdir@/drv/Standard/Standard_AbortiveTransaction_0.cxx \
@top_srcdir@/drv/Standard/Standard_ConstructionError_0.cxx \
@top_srcdir@/drv/Standard/Standard_DimensionError_0.cxx \
@top_srcdir@/drv/Standard/Standard_DimensionMismatch_0.cxx \
@top_srcdir@/drv/Standard/Standard_DivideByZero_0.cxx \
@top_srcdir@/drv/Standard/Standard_DomainError_0.cxx \
@top_srcdir@/drv/Standard/Standard_ImmutableObject_0.cxx \
@top_srcdir@/drv/Standard/Standard_LicenseError_0.cxx \
@top_srcdir@/drv/Standard/Standard_LicenseNotFound_0.cxx \
@top_srcdir@/drv/Standard/Standard_MultiplyDefined_0.cxx \
@top_srcdir@/drv/Standard/Standard_NegativeValue_0.cxx \
@top_srcdir@/drv/Standard/Standard_NoMoreObject_0.cxx \
@top_srcdir@/drv/Standard/Standard_NoSuchObject_0.cxx \
@top_srcdir@/drv/Standard/Standard_NotImplemented_0.cxx \
@top_srcdir@/drv/Standard/Standard_NullObject_0.cxx \
@top_srcdir@/drv/Standard/Standard_NullValue_0.cxx \
@top_srcdir@/drv/Standard/Standard_NumericError_0.cxx \
@top_srcdir@/drv/Standard/Standard_OutOfMemory_0.cxx \
@top_srcdir@/drv/Standard/Standard_OutOfRange_0.cxx \
@top_srcdir@/drv/Standard/Standard_Overflow_0.cxx \
@top_srcdir@/drv/Standard/Standard_ProgramError_0.cxx \
@top_srcdir@/drv/Standard/Standard_RangeError_0.cxx \
@top_srcdir@/drv/Standard/Standard_TooManyUsers_0.cxx \
@top_srcdir@/drv/Standard/Standard_TypeMismatch_0.cxx \
@top_srcdir@/drv/Standard/Standard_Underflow_0.cxx \
@top_srcdir@/drv/StdFail/StdFail_InfiniteSolutions_0.cxx \
@top_srcdir@/drv/StdFail/StdFail_NotDone_0.cxx \
@top_srcdir@/drv/StdFail/StdFail_UndefinedDerivative_0.cxx \
@top_srcdir@/drv/StdFail/StdFail_UndefinedValue_0.cxx \
@top_srcdir@/drv/StdFail/StdFail_Undefined_0.cxx \
@top_srcdir@/drv/Storage/Storage_ArrayOfCallBack_0.cxx \
@top_srcdir@/drv/Storage/Storage_ArrayOfSchema_0.cxx \
@top_srcdir@/drv/Storage/Storage_DataMapIteratorOfMapOfCallBack_0.cxx \
@top_srcdir@/drv/Storage/Storage_DataMapIteratorOfMapOfPers_0.cxx \
@top_srcdir@/drv/Storage/Storage_DataMapNodeOfMapOfCallBack_0.cxx \
@top_srcdir@/drv/Storage/Storage_DataMapNodeOfMapOfPers_0.cxx \
@top_srcdir@/drv/Storage/Storage_HArrayOfCallBack_0.cxx \
@top_srcdir@/drv/Storage/Storage_HArrayOfSchema_0.cxx \
@top_srcdir@/drv/Storage/Storage_HPArray_0.cxx \
@top_srcdir@/drv/Storage/Storage_HSeqOfRoot_0.cxx \
@top_srcdir@/drv/Storage/Storage_IndexedDataMapNodeOfPType_0.cxx \
@top_srcdir@/drv/Storage/Storage_MapOfCallBack_0.cxx \
@top_srcdir@/drv/Storage/Storage_MapOfPers_0.cxx \
@top_srcdir@/drv/Storage/Storage_PArray_0.cxx \
@top_srcdir@/drv/Storage/Storage_PType_0.cxx \
@top_srcdir@/drv/Storage/Storage_SeqOfRoot_0.cxx \
@top_srcdir@/drv/Storage/Storage_SequenceNodeOfSeqOfRoot_0.cxx \
@top_srcdir@/drv/Storage/Storage_StreamExtCharParityError_0.cxx \
@top_srcdir@/drv/Storage/Storage_StreamFormatError_0.cxx \
@top_srcdir@/drv/Storage/Storage_StreamModeError_0.cxx \
@top_srcdir@/drv/Storage/Storage_StreamReadError_0.cxx \
@top_srcdir@/drv/Storage/Storage_StreamTypeMismatchError_0.cxx \
@top_srcdir@/drv/Storage/Storage_StreamUnknownTypeError_0.cxx \
@top_srcdir@/drv/Storage/Storage_StreamWriteError_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_Array1OfAsciiString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_Array1OfBoolean_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_Array1OfByte_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_Array1OfCharacter_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_Array1OfExtendedString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_Array1OfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_Array1OfListOfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_Array1OfReal_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_Array1OfTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_Array2OfBoolean_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_Array2OfCharacter_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_Array2OfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_Array2OfReal_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_Array2OfTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapIteratorOfDataMapOfAsciiStringInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapIteratorOfDataMapOfIntegerInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapIteratorOfDataMapOfIntegerListOfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapIteratorOfDataMapOfIntegerReal_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapIteratorOfDataMapOfIntegerTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapIteratorOfDataMapOfStringInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapIteratorOfDataMapOfTransientTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapNodeOfDataMapOfAsciiStringInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapNodeOfDataMapOfIntegerInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapNodeOfDataMapOfIntegerListOfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapNodeOfDataMapOfIntegerReal_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapNodeOfDataMapOfIntegerTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapNodeOfDataMapOfStringInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapNodeOfDataMapOfTransientTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapOfAsciiStringInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapOfIntegerInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapOfIntegerListOfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapOfIntegerReal_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapOfIntegerTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapOfStringInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_DataMapOfTransientTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HArray1OfAsciiString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HArray1OfBoolean_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HArray1OfByte_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HArray1OfCharacter_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HArray1OfExtendedString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HArray1OfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HArray1OfListOfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HArray1OfReal_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HArray1OfTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HArray2OfBoolean_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HArray2OfCharacter_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HArray2OfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HArray2OfReal_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HArray2OfTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HSequenceOfAsciiString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HSequenceOfExtendedString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HSequenceOfHAsciiString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HSequenceOfHExtendedString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HSequenceOfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HSequenceOfReal_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_HSequenceOfTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_IndexedDataMapNodeOfIndexedDataMapOfTransientTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_IndexedDataMapOfTransientTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_IndexedMapNodeOfIndexedMapOfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_IndexedMapNodeOfIndexedMapOfReal_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_IndexedMapNodeOfIndexedMapOfTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_IndexedMapOfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_IndexedMapOfReal_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_IndexedMapOfTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_ListIteratorOfListOfAsciiString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_ListIteratorOfListOfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_ListIteratorOfListOfReal_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_ListIteratorOfListOfTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_ListNodeOfListOfAsciiString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_ListNodeOfListOfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_ListNodeOfListOfReal_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_ListNodeOfListOfTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_ListOfAsciiString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_ListOfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_ListOfReal_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_ListOfTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_MapIntegerHasher_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_MapIteratorOfMapOfAsciiString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_MapIteratorOfMapOfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_MapIteratorOfMapOfReal_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_MapIteratorOfMapOfTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_MapOfAsciiString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_MapOfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_MapOfReal_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_MapOfTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_MapRealHasher_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_MapTransientHasher_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_SequenceNodeOfSequenceOfAddress_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_SequenceNodeOfSequenceOfAsciiString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_SequenceNodeOfSequenceOfBoolean_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_SequenceNodeOfSequenceOfExtendedString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_SequenceNodeOfSequenceOfHAsciiString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_SequenceNodeOfSequenceOfHExtendedString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_SequenceNodeOfSequenceOfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_SequenceNodeOfSequenceOfReal_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_SequenceNodeOfSequenceOfTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_SequenceOfAddress_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_SequenceOfAsciiString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_SequenceOfBoolean_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_SequenceOfExtendedString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_SequenceOfHAsciiString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_SequenceOfHExtendedString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_SequenceOfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_SequenceOfReal_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_SequenceOfTransient_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_StdMapNodeOfMapOfAsciiString_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_StdMapNodeOfMapOfInteger_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_StdMapNodeOfMapOfReal_0.cxx \
@top_srcdir@/drv/TColStd/TColStd_StdMapNodeOfMapOfTransient_0.cxx \
@top_srcdir@/drv/TCollection/TCollection_PrivCompareOfInteger_0.cxx \
@top_srcdir@/drv/TCollection/TCollection_PrivCompareOfReal_0.cxx \
@top_srcdir@/drv/TShort/TShort_Array1OfShortReal_0.cxx \
@top_srcdir@/drv/TShort/TShort_Array2OfShortReal_0.cxx \
@top_srcdir@/drv/TShort/TShort_HArray1OfShortReal_0.cxx \
@top_srcdir@/drv/TShort/TShort_HArray2OfShortReal_0.cxx \
@top_srcdir@/drv/TShort/TShort_HSequenceOfShortReal_0.cxx \
@top_srcdir@/drv/TShort/TShort_SequenceNodeOfSequenceOfShortReal_0.cxx \
@top_srcdir@/drv/TShort/TShort_SequenceOfShortReal_0.cxx \
@top_srcdir@/drv/Units/Units_NoSuchType_0.cxx \
@top_srcdir@/drv/Units/Units_NoSuchUnit_0.cxx \
@top_srcdir@/drv/Units/Units_QtsSequence_0.cxx \
@top_srcdir@/drv/Units/Units_QuantitiesSequence_0.cxx \
@top_srcdir@/drv/Units/Units_SequenceNodeOfQtsSequence_0.cxx \
@top_srcdir@/drv/Units/Units_SequenceNodeOfTksSequence_0.cxx \
@top_srcdir@/drv/Units/Units_SequenceNodeOfUtsSequence_0.cxx \
@top_srcdir@/drv/Units/Units_TksSequence_0.cxx \
@top_srcdir@/drv/Units/Units_TokensSequence_0.cxx \
@top_srcdir@/drv/Units/Units_UnitsSequence_0.cxx \
@top_srcdir@/drv/Units/Units_UtsSequence_0.cxx \
@top_srcdir@/src/FSD/FSD_BinaryFile.cxx \
@top_srcdir@/src/FSD/FSD_CmpFile.cxx \
@top_srcdir@/src/FSD/FSD_File.cxx \
@top_srcdir@/src/MMgt/MMgt_TShared.cxx \
@top_srcdir@/src/Message/Message.cxx \
@top_srcdir@/src/Message/Message_Algorithm.cxx \
@top_srcdir@/src/Message/Message_Messenger.cxx \
@top_srcdir@/src/Message/Message_Msg.cxx \
@top_srcdir@/src/Message/Message_MsgFile.cxx \
@top_srcdir@/src/Message/Message_Printer.cxx \
@top_srcdir@/src/Message/Message_PrinterOStream.cxx \
@top_srcdir@/src/Message/Message_ProgressIndicator.cxx \
@top_srcdir@/src/Message/Message_ProgressScale.cxx \
@top_srcdir@/src/Message/Message_ProgressSentry.cxx \
@top_srcdir@/src/NCollection/NCollection_AccAllocator.cxx \
@top_srcdir@/src/NCollection/NCollection_AlignedAllocator.cxx \
@top_srcdir@/src/NCollection/NCollection_BaseAllocator.cxx \
@top_srcdir@/src/NCollection/NCollection_BaseList.cxx \
@top_srcdir@/src/NCollection/NCollection_BaseMap.cxx \
@top_srcdir@/src/NCollection/NCollection_BaseSequence.cxx \
@top_srcdir@/src/NCollection/NCollection_BaseVector.cxx \
@top_srcdir@/src/NCollection/NCollection_Handle.cxx \
@top_srcdir@/src/NCollection/NCollection_HeapAllocator.cxx \
@top_srcdir@/src/NCollection/NCollection_IncAllocator.cxx \
@top_srcdir@/src/NCollection/NCollection_SparseArrayBase.cxx \
@top_srcdir@/src/NCollection/NCollection_WinHeapAllocator.cxx \
@top_srcdir@/src/OSD/OSD.cxx \
@top_srcdir@/src/OSD/OSD_Chronometer.cxx \
@top_srcdir@/src/OSD/OSD_Directory.cxx \
@top_srcdir@/src/OSD/OSD_DirectoryIterator.cxx \
@top_srcdir@/src/OSD/OSD_Disk.cxx \
@top_srcdir@/src/OSD/OSD_Environment.cxx \
@top_srcdir@/src/OSD/OSD_EnvironmentIterator.cxx \
@top_srcdir@/src/OSD/OSD_Error.cxx \
@top_srcdir@/src/OSD/OSD_File.cxx \
@top_srcdir@/src/OSD/OSD_FileIterator.cxx \
@top_srcdir@/src/OSD/OSD_FileNode.cxx \
@top_srcdir@/src/OSD/OSD_Host.cxx \
@top_srcdir@/src/OSD/OSD_MAllocHook.cxx \
@top_srcdir@/src/OSD/OSD_MemInfo.cxx \
@top_srcdir@/src/OSD/OSD_OpenFile.cxx \
@top_srcdir@/src/OSD/OSD_Path.cxx \
@top_srcdir@/src/OSD/OSD_PerfMeter.cxx \
@top_srcdir@/src/OSD/OSD_Printer.cxx \
@top_srcdir@/src/OSD/OSD_Process.cxx \
@top_srcdir@/src/OSD/OSD_Protection.cxx \
@top_srcdir@/src/OSD/OSD_SharedLibrary.cxx \
@top_srcdir@/src/OSD/OSD_Thread.cxx \
@top_srcdir@/src/OSD/OSD_Timer.cxx \
@top_srcdir@/src/OSD/OSD_WNT.cxx \
@top_srcdir@/src/OSD/OSD_signal.cxx \
@top_srcdir@/src/OSD/OSD_signal_WNT.cxx \
@top_srcdir@/src/Plugin/Plugin.cxx \
@top_srcdir@/src/Quantity/Quantity_Color.cxx \
@top_srcdir@/src/Quantity/Quantity_Convert.cxx \
@top_srcdir@/src/Quantity/Quantity_Date.cxx \
@top_srcdir@/src/Quantity/Quantity_Period.cxx \
@top_srcdir@/src/Resource/Resource_ConvertUnicode.c \
@top_srcdir@/src/Resource/Resource_LexicalCompare.cxx \
@top_srcdir@/src/Resource/Resource_Manager.cxx \
@top_srcdir@/src/Resource/Resource_Unicode.cxx \
@top_srcdir@/src/Standard/Handle_Standard_Persistent.cxx \
@top_srcdir@/src/Standard/Handle_Standard_Transient.cxx \
@top_srcdir@/src/Standard/Standard.cxx \
@top_srcdir@/src/Standard/Standard_AncestorIterator.cxx \
@top_srcdir@/src/Standard/Standard_CLocaleSentry.cxx \
@top_srcdir@/src/Standard/Standard_CString.cxx \
@top_srcdir@/src/Standard/Standard_ErrorHandler.cxx \
@top_srcdir@/src/Standard/Standard_ErrorHandlerCallback.cxx \
@top_srcdir@/src/Standard/Standard_ExtString.cxx \
@top_srcdir@/src/Standard/Standard_Failure.cxx \
@top_srcdir@/src/Standard/Standard_GUID.cxx \
@top_srcdir@/src/Standard/Standard_HashCode.cxx \
@top_srcdir@/src/Standard/Standard_MMgrOpt.cxx \
@top_srcdir@/src/Standard/Standard_MMgrRaw.cxx \
@top_srcdir@/src/Standard/Standard_MMgrRoot.cxx \
@top_srcdir@/src/Standard/Standard_MMgrTBBalloc.cxx \
@top_srcdir@/src/Standard/Standard_Mutex.cxx \
@top_srcdir@/src/Standard/Standard_Persistent.cxx \
@top_srcdir@/src/Standard/Standard_Real.cxx \
@top_srcdir@/src/Standard/Standard_SStream.cxx \
@top_srcdir@/src/Standard/Standard_ShortReal.cxx \
@top_srcdir@/src/Standard/Standard_Storable.cxx \
@top_srcdir@/src/Standard/Standard_Transient.cxx \
@top_srcdir@/src/Standard/Standard_Type.cxx \
@top_srcdir@/src/Standard/Standard_UUID.cxx \
@top_srcdir@/src/Standard/Standard_math.cxx \
@top_srcdir@/src/Storage/Storage.cxx \
@top_srcdir@/src/Storage/Storage_BaseDriver.cxx \
@top_srcdir@/src/Storage/Storage_CallBack.cxx \
@top_srcdir@/src/Storage/Storage_Data.cxx \
@top_srcdir@/src/Storage/Storage_DefaultCallBack.cxx \
@top_srcdir@/src/Storage/Storage_HeaderData.cxx \
@top_srcdir@/src/Storage/Storage_InternalData.cxx \
@top_srcdir@/src/Storage/Storage_Root.cxx \
@top_srcdir@/src/Storage/Storage_RootData.cxx \
@top_srcdir@/src/Storage/Storage_Schema.cxx \
@top_srcdir@/src/Storage/Storage_TypeData.cxx \
@top_srcdir@/src/Storage/Storage_TypedCallBack.cxx \
@top_srcdir@/src/Storage/Storage_stCONSTclCOM.cxx \
@top_srcdir@/src/TColStd/TColStd_HPackedMapOfInteger.cxx \
@top_srcdir@/src/TColStd/TColStd_MapIteratorOfPackedMapOfInteger.cxx \
@top_srcdir@/src/TColStd/TColStd_PackedMapOfInteger.cxx \
@top_srcdir@/src/TCollection/TCollection.cxx \
@top_srcdir@/src/TCollection/TCollection_AsciiString.cxx \
@top_srcdir@/src/TCollection/TCollection_BaseSequence.cxx \
@top_srcdir@/src/TCollection/TCollection_BasicMap.cxx \
@top_srcdir@/src/TCollection/TCollection_BasicMapIterator.cxx \
@top_srcdir@/src/TCollection/TCollection_CompareOfInteger.cxx \
@top_srcdir@/src/TCollection/TCollection_CompareOfReal.cxx \
@top_srcdir@/src/TCollection/TCollection_ExtendedString.cxx \
@top_srcdir@/src/TCollection/TCollection_HAsciiString.cxx \
@top_srcdir@/src/TCollection/TCollection_HExtendedString.cxx \
@top_srcdir@/src/TCollection/TCollection_MapNode.cxx \
@top_srcdir@/src/TCollection/TCollection_SeqNode.cxx \
@top_srcdir@/src/Units/Units.cxx \
@top_srcdir@/src/Units/Units_Dimensions.cxx \
@top_srcdir@/src/Units/Units_Explorer.cxx \
@top_srcdir@/src/Units/Units_Lexicon.cxx \
@top_srcdir@/src/Units/Units_MathSentence.cxx \
@top_srcdir@/src/Units/Units_Measurement.cxx \
@top_srcdir@/src/Units/Units_Quantity.cxx \
@top_srcdir@/src/Units/Units_Sentence.cxx \
@top_srcdir@/src/Units/Units_ShiftedToken.cxx \
@top_srcdir@/src/Units/Units_ShiftedUnit.cxx \
@top_srcdir@/src/Units/Units_Token.cxx \
@top_srcdir@/src/Units/Units_Unit.cxx \
@top_srcdir@/src/Units/Units_UnitSentence.cxx \
@top_srcdir@/src/Units/Units_UnitsDictionary.cxx \
@top_srcdir@/src/Units/Units_UnitsLexicon.cxx \
@top_srcdir@/src/Units/Units_UnitsSystem.cxx \
@top_srcdir@/src/UnitsAPI/UnitsAPI.cxx

