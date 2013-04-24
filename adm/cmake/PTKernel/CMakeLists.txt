project(PTKernel)

if (WIN32)
  list( APPEND PTKernel_PRECOMPILED_DEFS "-D__DBC_DLL" )
  list( APPEND PTKernel_PRECOMPILED_DEFS "-D__PCollection_DLL" )
  list( APPEND PTKernel_PRECOMPILED_DEFS "-D__PColStd_DLL" )
  list( APPEND PTKernel_PRECOMPILED_DEFS "-D__PMMgt_DLL" )
  list( APPEND PTKernel_PRECOMPILED_DEFS "-D__PShort_DLL" )
  list( APPEND PTKernel_PRECOMPILED_DEFS "-D__PStandard_DLL" )
  list( APPEND PTKernel_PRECOMPILED_DEFS "-D__PTColStd_DLL" )
  list( APPEND PTKernel_PRECOMPILED_DEFS "-D__ObjMgt_DLL" )
  string( REGEX REPLACE ";" " " PTKernel_PRECOMPILED_DEFS "${PTKernel_PRECOMPILED_DEFS}")
endif()

  list( APPEND PTKernel_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND PTKernel_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND PTKernel_COMPILER_DIRECTORIES "../../../drv/DBC" )
  list( APPEND PTKernel_COMPILER_DIRECTORIES "../../../src/DBC" )
  list( APPEND PTKernel_COMPILER_DIRECTORIES "../../../drv/PCollection" )
  list( APPEND PTKernel_COMPILER_DIRECTORIES "../../../src/PCollection" )
  list( APPEND PTKernel_COMPILER_DIRECTORIES "../../../drv/PColStd" )
  list( APPEND PTKernel_COMPILER_DIRECTORIES "../../../src/PColStd" )
  list( APPEND PTKernel_COMPILER_DIRECTORIES "../../../drv/PMMgt" )
  list( APPEND PTKernel_COMPILER_DIRECTORIES "../../../src/PMMgt" )
  list( APPEND PTKernel_COMPILER_DIRECTORIES "../../../drv/PShort" )
  list( APPEND PTKernel_COMPILER_DIRECTORIES "../../../src/PShort" )
  list( APPEND PTKernel_COMPILER_DIRECTORIES "../../../drv/PStandard" )
  list( APPEND PTKernel_COMPILER_DIRECTORIES "../../../src/PStandard" )
  list( APPEND PTKernel_COMPILER_DIRECTORIES "../../../drv/PTColStd" )
  list( APPEND PTKernel_COMPILER_DIRECTORIES "../../../src/PTColStd" )
  list( APPEND PTKernel_COMPILER_DIRECTORIES "../../../drv/ObjMgt" )
  list( APPEND PTKernel_COMPILER_DIRECTORIES "../../../src/ObjMgt" )

if (WIN32)
else()
endif()

  list( APPEND PTKernel_USED_LIBS TKernel )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/DBC/DBC_VArrayNodeOfVArrayOfCharacter_0.cxx" )
  SOURCE_GROUP (DBC FILES "../../../drv/DBC/DBC_VArrayNodeOfVArrayOfCharacter_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/DBC/DBC_VArrayNodeOfVArrayOfExtCharacter_0.cxx" )
  SOURCE_GROUP (DBC FILES "../../../drv/DBC/DBC_VArrayNodeOfVArrayOfExtCharacter_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/DBC/DBC_VArrayNodeOfVArrayOfInteger_0.cxx" )
  SOURCE_GROUP (DBC FILES "../../../drv/DBC/DBC_VArrayNodeOfVArrayOfInteger_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/DBC/DBC_VArrayNodeOfVArrayOfReal_0.cxx" )
  SOURCE_GROUP (DBC FILES "../../../drv/DBC/DBC_VArrayNodeOfVArrayOfReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/DBC/DBC_VArrayOfCharacter_0.cxx" )
  SOURCE_GROUP (DBC FILES "../../../drv/DBC/DBC_VArrayOfCharacter_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/DBC/DBC_VArrayOfExtCharacter_0.cxx" )
  SOURCE_GROUP (DBC FILES "../../../drv/DBC/DBC_VArrayOfExtCharacter_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/DBC/DBC_VArrayOfInteger_0.cxx" )
  SOURCE_GROUP (DBC FILES "../../../drv/DBC/DBC_VArrayOfInteger_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/DBC/DBC_VArrayOfReal_0.cxx" )
  SOURCE_GROUP (DBC FILES "../../../drv/DBC/DBC_VArrayOfReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/DBC/DBC_VArrayTNodeOfVArrayOfCharacter_0.cxx" )
  SOURCE_GROUP (DBC FILES "../../../drv/DBC/DBC_VArrayTNodeOfVArrayOfCharacter_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/DBC/DBC_VArrayTNodeOfVArrayOfExtCharacter_0.cxx" )
  SOURCE_GROUP (DBC FILES "../../../drv/DBC/DBC_VArrayTNodeOfVArrayOfExtCharacter_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/DBC/DBC_VArrayTNodeOfVArrayOfInteger_0.cxx" )
  SOURCE_GROUP (DBC FILES "../../../drv/DBC/DBC_VArrayTNodeOfVArrayOfInteger_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/DBC/DBC_VArrayTNodeOfVArrayOfReal_0.cxx" )
  SOURCE_GROUP (DBC FILES "../../../drv/DBC/DBC_VArrayTNodeOfVArrayOfReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../src/DBC/DBC_BaseArray.cxx" )
  SOURCE_GROUP (DBC FILES "../../../src/DBC/DBC_BaseArray.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../src/DBC/DBC_DBVArray.cxx" )
  SOURCE_GROUP (DBC FILES "../../../src/DBC/DBC_DBVArray.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PCollection/PCollection_IsContained_0.cxx" )
  SOURCE_GROUP (PCollection FILES "../../../drv/PCollection/PCollection_IsContained_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PCollection/PCollection_IsNotRoot_0.cxx" )
  SOURCE_GROUP (PCollection FILES "../../../drv/PCollection/PCollection_IsNotRoot_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PCollection/PCollection_IsNullTree_0.cxx" )
  SOURCE_GROUP (PCollection FILES "../../../drv/PCollection/PCollection_IsNullTree_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PCollection/PCollection_PrivCompareOfInteger_0.cxx" )
  SOURCE_GROUP (PCollection FILES "../../../drv/PCollection/PCollection_PrivCompareOfInteger_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PCollection/PCollection_PrivCompareOfReal_0.cxx" )
  SOURCE_GROUP (PCollection FILES "../../../drv/PCollection/PCollection_PrivCompareOfReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../src/PCollection/PCollection_CompareOfInteger.cxx" )
  SOURCE_GROUP (PCollection FILES "../../../src/PCollection/PCollection_CompareOfInteger.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../src/PCollection/PCollection_CompareOfReal.cxx" )
  SOURCE_GROUP (PCollection FILES "../../../src/PCollection/PCollection_CompareOfReal.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../src/PCollection/PCollection_HAsciiString.cxx" )
  SOURCE_GROUP (PCollection FILES "../../../src/PCollection/PCollection_HAsciiString.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../src/PCollection/PCollection_HExtendedString.cxx" )
  SOURCE_GROUP (PCollection FILES "../../../src/PCollection/PCollection_HExtendedString.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_FieldOfHArray1OfExtendedString_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_FieldOfHArray1OfExtendedString_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_FieldOfHArray1OfInteger_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_FieldOfHArray1OfInteger_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_FieldOfHArray1OfPersistent_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_FieldOfHArray1OfPersistent_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_FieldOfHArray1OfReal_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_FieldOfHArray1OfReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_FieldOfHArray2OfInteger_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_FieldOfHArray2OfInteger_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_FieldOfHArray2OfPersistent_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_FieldOfHArray2OfPersistent_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_FieldOfHArray2OfReal_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_FieldOfHArray2OfReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HArray1OfExtendedString_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HArray1OfExtendedString_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HArray1OfInteger_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HArray1OfInteger_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HArray1OfPersistent_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HArray1OfPersistent_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HArray1OfReal_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HArray1OfReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HArray2OfInteger_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HArray2OfInteger_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HArray2OfPersistent_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HArray2OfPersistent_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HArray2OfReal_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HArray2OfReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HDoubleListOfInteger_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HDoubleListOfInteger_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HDoubleListOfPersistent_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HDoubleListOfPersistent_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HDoubleListOfReal_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HDoubleListOfReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HOfAsciiString_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HOfAsciiString_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HOfExtendedString_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HOfExtendedString_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HOfInteger_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HOfInteger_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HOfReal_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HOfReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HSequenceOfHAsciiString_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HSequenceOfHAsciiString_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HSequenceOfHExtendedString_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HSequenceOfHExtendedString_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HSequenceOfInteger_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HSequenceOfInteger_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HSequenceOfPersistent_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HSequenceOfPersistent_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HSequenceOfReal_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HSequenceOfReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HSingleListOfInteger_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HSingleListOfInteger_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HSingleListOfPersistent_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HSingleListOfPersistent_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_HSingleListOfReal_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_HSingleListOfReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_SeqExplorerOfHSequenceOfHAsciiString_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_SeqExplorerOfHSequenceOfHAsciiString_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_SeqExplorerOfHSequenceOfHExtendedString_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_SeqExplorerOfHSequenceOfHExtendedString_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_SeqExplorerOfHSequenceOfInteger_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_SeqExplorerOfHSequenceOfInteger_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_SeqExplorerOfHSequenceOfPersistent_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_SeqExplorerOfHSequenceOfPersistent_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_SeqExplorerOfHSequenceOfReal_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_SeqExplorerOfHSequenceOfReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_SeqNodeOfHSequenceOfHAsciiString_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_SeqNodeOfHSequenceOfHAsciiString_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_SeqNodeOfHSequenceOfHExtendedString_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_SeqNodeOfHSequenceOfHExtendedString_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_SeqNodeOfHSequenceOfInteger_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_SeqNodeOfHSequenceOfInteger_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_SeqNodeOfHSequenceOfPersistent_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_SeqNodeOfHSequenceOfPersistent_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_SeqNodeOfHSequenceOfReal_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_SeqNodeOfHSequenceOfReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_VArrayNodeOfFieldOfHArray1OfExtendedString_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_VArrayNodeOfFieldOfHArray1OfExtendedString_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_VArrayNodeOfFieldOfHArray1OfInteger_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_VArrayNodeOfFieldOfHArray1OfInteger_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_VArrayNodeOfFieldOfHArray1OfPersistent_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_VArrayNodeOfFieldOfHArray1OfPersistent_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_VArrayNodeOfFieldOfHArray1OfReal_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_VArrayNodeOfFieldOfHArray1OfReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_VArrayNodeOfFieldOfHArray2OfInteger_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_VArrayNodeOfFieldOfHArray2OfInteger_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_VArrayNodeOfFieldOfHArray2OfPersistent_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_VArrayNodeOfFieldOfHArray2OfPersistent_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_VArrayNodeOfFieldOfHArray2OfReal_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_VArrayNodeOfFieldOfHArray2OfReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_VArrayTNodeOfFieldOfHArray1OfExtendedString_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_VArrayTNodeOfFieldOfHArray1OfExtendedString_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_VArrayTNodeOfFieldOfHArray1OfInteger_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_VArrayTNodeOfFieldOfHArray1OfInteger_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_VArrayTNodeOfFieldOfHArray1OfPersistent_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_VArrayTNodeOfFieldOfHArray1OfPersistent_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_VArrayTNodeOfFieldOfHArray1OfReal_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_VArrayTNodeOfFieldOfHArray1OfReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_VArrayTNodeOfFieldOfHArray2OfInteger_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_VArrayTNodeOfFieldOfHArray2OfInteger_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_VArrayTNodeOfFieldOfHArray2OfPersistent_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_VArrayTNodeOfFieldOfHArray2OfPersistent_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PColStd/PColStd_VArrayTNodeOfFieldOfHArray2OfReal_0.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../drv/PColStd/PColStd_VArrayTNodeOfFieldOfHArray2OfReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../src/PColStd/PColStd_HashAsciiString.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../src/PColStd/PColStd_HashAsciiString.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../src/PColStd/PColStd_HashExtendedString.cxx" )
  SOURCE_GROUP (PColStd FILES "../../../src/PColStd/PColStd_HashExtendedString.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../src/PMMgt/PMMgt_PManaged.cxx" )
  SOURCE_GROUP (PMMgt FILES "../../../src/PMMgt/PMMgt_PManaged.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PShort/PShort_FieldOfHArray1OfShortReal_0.cxx" )
  SOURCE_GROUP (PShort FILES "../../../drv/PShort/PShort_FieldOfHArray1OfShortReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PShort/PShort_FieldOfHArray2OfShortReal_0.cxx" )
  SOURCE_GROUP (PShort FILES "../../../drv/PShort/PShort_FieldOfHArray2OfShortReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PShort/PShort_HArray1OfShortReal_0.cxx" )
  SOURCE_GROUP (PShort FILES "../../../drv/PShort/PShort_HArray1OfShortReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PShort/PShort_HArray2OfShortReal_0.cxx" )
  SOURCE_GROUP (PShort FILES "../../../drv/PShort/PShort_HArray2OfShortReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PShort/PShort_HSequenceOfShortReal_0.cxx" )
  SOURCE_GROUP (PShort FILES "../../../drv/PShort/PShort_HSequenceOfShortReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PShort/PShort_SeqExplorerOfHSequenceOfShortReal_0.cxx" )
  SOURCE_GROUP (PShort FILES "../../../drv/PShort/PShort_SeqExplorerOfHSequenceOfShortReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PShort/PShort_SeqNodeOfHSequenceOfShortReal_0.cxx" )
  SOURCE_GROUP (PShort FILES "../../../drv/PShort/PShort_SeqNodeOfHSequenceOfShortReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PShort/PShort_VArrayNodeOfFieldOfHArray1OfShortReal_0.cxx" )
  SOURCE_GROUP (PShort FILES "../../../drv/PShort/PShort_VArrayNodeOfFieldOfHArray1OfShortReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PShort/PShort_VArrayNodeOfFieldOfHArray2OfShortReal_0.cxx" )
  SOURCE_GROUP (PShort FILES "../../../drv/PShort/PShort_VArrayNodeOfFieldOfHArray2OfShortReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PShort/PShort_VArrayTNodeOfFieldOfHArray1OfShortReal_0.cxx" )
  SOURCE_GROUP (PShort FILES "../../../drv/PShort/PShort_VArrayTNodeOfFieldOfHArray1OfShortReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PShort/PShort_VArrayTNodeOfFieldOfHArray2OfShortReal_0.cxx" )
  SOURCE_GROUP (PShort FILES "../../../drv/PShort/PShort_VArrayTNodeOfFieldOfHArray2OfShortReal_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../src/PStandard/PStandard_ArrayNode.cxx" )
  SOURCE_GROUP (PStandard FILES "../../../src/PStandard/PStandard_ArrayNode.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PTColStd/PTColStd_DataMapIteratorOfPersistentTransientMap_0.cxx" )
  SOURCE_GROUP (PTColStd FILES "../../../drv/PTColStd/PTColStd_DataMapIteratorOfPersistentTransientMap_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PTColStd/PTColStd_DataMapIteratorOfTransientPersistentMap_0.cxx" )
  SOURCE_GROUP (PTColStd FILES "../../../drv/PTColStd/PTColStd_DataMapIteratorOfTransientPersistentMap_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PTColStd/PTColStd_DataMapNodeOfPersistentTransientMap_0.cxx" )
  SOURCE_GROUP (PTColStd FILES "../../../drv/PTColStd/PTColStd_DataMapNodeOfPersistentTransientMap_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PTColStd/PTColStd_DataMapNodeOfTransientPersistentMap_0.cxx" )
  SOURCE_GROUP (PTColStd FILES "../../../drv/PTColStd/PTColStd_DataMapNodeOfTransientPersistentMap_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PTColStd/PTColStd_DoubleMapIteratorOfDoubleMapOfTransientPersistent_0.cxx" )
  SOURCE_GROUP (PTColStd FILES "../../../drv/PTColStd/PTColStd_DoubleMapIteratorOfDoubleMapOfTransientPersistent_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PTColStd/PTColStd_DoubleMapNodeOfDoubleMapOfTransientPersistent_0.cxx" )
  SOURCE_GROUP (PTColStd FILES "../../../drv/PTColStd/PTColStd_DoubleMapNodeOfDoubleMapOfTransientPersistent_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PTColStd/PTColStd_DoubleMapOfTransientPersistent_0.cxx" )
  SOURCE_GROUP (PTColStd FILES "../../../drv/PTColStd/PTColStd_DoubleMapOfTransientPersistent_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PTColStd/PTColStd_MapPersistentHasher_0.cxx" )
  SOURCE_GROUP (PTColStd FILES "../../../drv/PTColStd/PTColStd_MapPersistentHasher_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PTColStd/PTColStd_PersistentTransientMap_0.cxx" )
  SOURCE_GROUP (PTColStd FILES "../../../drv/PTColStd/PTColStd_PersistentTransientMap_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/PTColStd/PTColStd_TransientPersistentMap_0.cxx" )
  SOURCE_GROUP (PTColStd FILES "../../../drv/PTColStd/PTColStd_TransientPersistentMap_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/ObjMgt/ObjMgt_PSeqOfExtRef_0.cxx" )
  SOURCE_GROUP (ObjMgt FILES "../../../drv/ObjMgt/ObjMgt_PSeqOfExtRef_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/ObjMgt/ObjMgt_SeqExplorerOfPSeqOfExtRef_0.cxx" )
  SOURCE_GROUP (ObjMgt FILES "../../../drv/ObjMgt/ObjMgt_SeqExplorerOfPSeqOfExtRef_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../drv/ObjMgt/ObjMgt_SeqNodeOfPSeqOfExtRef_0.cxx" )
  SOURCE_GROUP (ObjMgt FILES "../../../drv/ObjMgt/ObjMgt_SeqNodeOfPSeqOfExtRef_0.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../src/ObjMgt/ObjMgt_ExternRef.cxx" )
  SOURCE_GROUP (ObjMgt FILES "../../../src/ObjMgt/ObjMgt_ExternRef.cxx")

  list( APPEND PTKernel_USED_SRCFILES "../../../src/ObjMgt/ObjMgt_ExternShareable.cxx" )
  SOURCE_GROUP (ObjMgt FILES "../../../src/ObjMgt/ObjMgt_ExternShareable.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONthePTKernel)
 add_library( PTKernel SHARED ${PTKernel_USED_SRCFILES} )

 set_property(TARGET PTKernel PROPERTY FOLDER ApplicationFramework)

 install( TARGETS PTKernel
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/PTKernel.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( PTKernel PROPERTIES COMPILE_FLAGS "${PTKernel_PRECOMPILED_DEFS}" )
 include_directories( ${PTKernel_COMPILER_DIRECTORIES} )
 target_link_libraries( PTKernel ${PTKernel_USED_LIBS} )
endif()
