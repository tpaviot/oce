project(TKBinL)

if (WIN32)
  list( APPEND TKBinL_PRECOMPILED_DEFS "-D__BinMDF_DLL" )
  list( APPEND TKBinL_PRECOMPILED_DEFS "-D__BinMDataStd_DLL" )
  list( APPEND TKBinL_PRECOMPILED_DEFS "-D__BinMFunction_DLL" )
  list( APPEND TKBinL_PRECOMPILED_DEFS "-D__BinMDocStd_DLL" )
  list( APPEND TKBinL_PRECOMPILED_DEFS "-D__BinObjMgt_DLL" )
  list( APPEND TKBinL_PRECOMPILED_DEFS "-D__BinLDrivers_DLL" )
  string( REGEX REPLACE ";" " " TKBinL_PRECOMPILED_DEFS "${TKBinL_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKBinL_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKBinL_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKBinL_COMPILER_DIRECTORIES "../../../drv/BinMDF" )
  list( APPEND TKBinL_COMPILER_DIRECTORIES "../../../src/BinMDF" )
  list( APPEND TKBinL_COMPILER_DIRECTORIES "../../../drv/BinMDataStd" )
  list( APPEND TKBinL_COMPILER_DIRECTORIES "../../../src/BinMDataStd" )
  list( APPEND TKBinL_COMPILER_DIRECTORIES "../../../drv/BinMFunction" )
  list( APPEND TKBinL_COMPILER_DIRECTORIES "../../../src/BinMFunction" )
  list( APPEND TKBinL_COMPILER_DIRECTORIES "../../../drv/BinMDocStd" )
  list( APPEND TKBinL_COMPILER_DIRECTORIES "../../../src/BinMDocStd" )
  list( APPEND TKBinL_COMPILER_DIRECTORIES "../../../drv/BinObjMgt" )
  list( APPEND TKBinL_COMPILER_DIRECTORIES "../../../src/BinObjMgt" )
  list( APPEND TKBinL_COMPILER_DIRECTORIES "../../../drv/BinLDrivers" )
  list( APPEND TKBinL_COMPILER_DIRECTORIES "../../../src/BinLDrivers" )

if (WIN32)
else()
endif()

  list( APPEND TKBinL_USED_LIBS TKCDF )
  list( APPEND TKBinL_USED_LIBS TKernel )
  list( APPEND TKBinL_USED_LIBS TKLCAF )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKBinL_USED_SRCFILES "../../../drv/BinMDF/BinMDF_DataMapIteratorOfTypeADriverMap_0.cxx" )
  SOURCE_GROUP (BinMDF FILES "../../../drv/BinMDF/BinMDF_DataMapIteratorOfTypeADriverMap_0.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../drv/BinMDF/BinMDF_DataMapNodeOfTypeADriverMap_0.cxx" )
  SOURCE_GROUP (BinMDF FILES "../../../drv/BinMDF/BinMDF_DataMapNodeOfTypeADriverMap_0.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../drv/BinMDF/BinMDF_DoubleMapIteratorOfTypeIdMap_0.cxx" )
  SOURCE_GROUP (BinMDF FILES "../../../drv/BinMDF/BinMDF_DoubleMapIteratorOfTypeIdMap_0.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../drv/BinMDF/BinMDF_DoubleMapNodeOfTypeIdMap_0.cxx" )
  SOURCE_GROUP (BinMDF FILES "../../../drv/BinMDF/BinMDF_DoubleMapNodeOfTypeIdMap_0.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../drv/BinMDF/BinMDF_TypeADriverMap_0.cxx" )
  SOURCE_GROUP (BinMDF FILES "../../../drv/BinMDF/BinMDF_TypeADriverMap_0.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../drv/BinMDF/BinMDF_TypeIdMap_0.cxx" )
  SOURCE_GROUP (BinMDF FILES "../../../drv/BinMDF/BinMDF_TypeIdMap_0.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDF/BinMDF.cxx" )
  SOURCE_GROUP (BinMDF FILES "../../../src/BinMDF/BinMDF.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDF/BinMDF_ADriver.cxx" )
  SOURCE_GROUP (BinMDF FILES "../../../src/BinMDF/BinMDF_ADriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDF/BinMDF_ADriverTable.cxx" )
  SOURCE_GROUP (BinMDF FILES "../../../src/BinMDF/BinMDF_ADriverTable.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDF/BinMDF_ReferenceDriver.cxx" )
  SOURCE_GROUP (BinMDF FILES "../../../src/BinMDF/BinMDF_ReferenceDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDF/BinMDF_TagSourceDriver.cxx" )
  SOURCE_GROUP (BinMDF FILES "../../../src/BinMDF/BinMDF_TagSourceDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_AsciiStringDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_AsciiStringDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_BooleanArrayDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_BooleanArrayDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_BooleanListDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_BooleanListDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_ByteArrayDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_ByteArrayDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_CommentDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_CommentDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_DirectoryDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_DirectoryDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_ExpressionDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_ExpressionDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_ExtStringArrayDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_ExtStringArrayDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_ExtStringListDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_ExtStringListDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_IntPackedMapDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_IntPackedMapDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_IntegerArrayDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_IntegerArrayDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_IntegerDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_IntegerDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_IntegerListDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_IntegerListDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_NameDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_NameDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_NamedDataDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_NamedDataDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_NoteBookDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_NoteBookDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_RealArrayDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_RealArrayDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_RealDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_RealDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_RealListDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_RealListDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_ReferenceArrayDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_ReferenceArrayDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_ReferenceListDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_ReferenceListDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_RelationDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_RelationDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_TickDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_TickDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_TreeNodeDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_TreeNodeDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_UAttributeDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_UAttributeDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDataStd/BinMDataStd_VariableDriver.cxx" )
  SOURCE_GROUP (BinMDataStd FILES "../../../src/BinMDataStd/BinMDataStd_VariableDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMFunction/BinMFunction.cxx" )
  SOURCE_GROUP (BinMFunction FILES "../../../src/BinMFunction/BinMFunction.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMFunction/BinMFunction_FunctionDriver.cxx" )
  SOURCE_GROUP (BinMFunction FILES "../../../src/BinMFunction/BinMFunction_FunctionDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMFunction/BinMFunction_GraphNodeDriver.cxx" )
  SOURCE_GROUP (BinMFunction FILES "../../../src/BinMFunction/BinMFunction_GraphNodeDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMFunction/BinMFunction_ScopeDriver.cxx" )
  SOURCE_GROUP (BinMFunction FILES "../../../src/BinMFunction/BinMFunction_ScopeDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDocStd/BinMDocStd.cxx" )
  SOURCE_GROUP (BinMDocStd FILES "../../../src/BinMDocStd/BinMDocStd.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinMDocStd/BinMDocStd_XLinkDriver.cxx" )
  SOURCE_GROUP (BinMDocStd FILES "../../../src/BinMDocStd/BinMDocStd_XLinkDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinObjMgt/BinObjMgt_Persistent.cxx" )
  SOURCE_GROUP (BinObjMgt FILES "../../../src/BinObjMgt/BinObjMgt_Persistent.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinLDrivers/BinLDrivers.cxx" )
  SOURCE_GROUP (BinLDrivers FILES "../../../src/BinLDrivers/BinLDrivers.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinLDrivers/BinLDrivers_DocumentRetrievalDriver.cxx" )
  SOURCE_GROUP (BinLDrivers FILES "../../../src/BinLDrivers/BinLDrivers_DocumentRetrievalDriver.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinLDrivers/BinLDrivers_DocumentSection.cxx" )
  SOURCE_GROUP (BinLDrivers FILES "../../../src/BinLDrivers/BinLDrivers_DocumentSection.cxx")

  list( APPEND TKBinL_USED_SRCFILES "../../../src/BinLDrivers/BinLDrivers_DocumentStorageDriver.cxx" )
  SOURCE_GROUP (BinLDrivers FILES "../../../src/BinLDrivers/BinLDrivers_DocumentStorageDriver.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKBinL)
 add_library( TKBinL SHARED ${TKBinL_USED_SRCFILES} )

 set_property(TARGET TKBinL PROPERTY FOLDER ApplicationFramework)

 install( TARGETS TKBinL
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKBinL.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKBinL PROPERTIES COMPILE_FLAGS "${TKBinL_PRECOMPILED_DEFS}" )
 include_directories( ${TKBinL_COMPILER_DIRECTORIES} )
 target_link_libraries( TKBinL ${TKBinL_USED_LIBS} )
endif()
