project(TKXmlL)

if (WIN32)
  list( APPEND TKXmlL_PRECOMPILED_DEFS "-D__XmlLDrivers_DLL" )
  list( APPEND TKXmlL_PRECOMPILED_DEFS "-D__XmlMDF_DLL" )
  list( APPEND TKXmlL_PRECOMPILED_DEFS "-D__XmlMDataStd_DLL" )
  list( APPEND TKXmlL_PRECOMPILED_DEFS "-D__XmlMDocStd_DLL" )
  list( APPEND TKXmlL_PRECOMPILED_DEFS "-D__XmlMFunction_DLL" )
  list( APPEND TKXmlL_PRECOMPILED_DEFS "-D__XmlObjMgt_DLL" )
  string( REGEX REPLACE ";" " " TKXmlL_PRECOMPILED_DEFS "${TKXmlL_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKXmlL_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKXmlL_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKXmlL_COMPILER_DIRECTORIES "../../../drv/XmlLDrivers" )
  list( APPEND TKXmlL_COMPILER_DIRECTORIES "../../../src/XmlLDrivers" )
  list( APPEND TKXmlL_COMPILER_DIRECTORIES "../../../drv/XmlMDF" )
  list( APPEND TKXmlL_COMPILER_DIRECTORIES "../../../src/XmlMDF" )
  list( APPEND TKXmlL_COMPILER_DIRECTORIES "../../../drv/XmlMDataStd" )
  list( APPEND TKXmlL_COMPILER_DIRECTORIES "../../../src/XmlMDataStd" )
  list( APPEND TKXmlL_COMPILER_DIRECTORIES "../../../drv/XmlMDocStd" )
  list( APPEND TKXmlL_COMPILER_DIRECTORIES "../../../src/XmlMDocStd" )
  list( APPEND TKXmlL_COMPILER_DIRECTORIES "../../../drv/XmlMFunction" )
  list( APPEND TKXmlL_COMPILER_DIRECTORIES "../../../src/XmlMFunction" )
  list( APPEND TKXmlL_COMPILER_DIRECTORIES "../../../drv/XmlObjMgt" )
  list( APPEND TKXmlL_COMPILER_DIRECTORIES "../../../src/XmlObjMgt" )

if (WIN32)
else()
endif()

  list( APPEND TKXmlL_USED_LIBS TKCDF )
  list( APPEND TKXmlL_USED_LIBS TKernel )
  list( APPEND TKXmlL_USED_LIBS TKMath )
  list( APPEND TKXmlL_USED_LIBS TKLCAF )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKXmlL_USED_SRCFILES "../../../drv/XmlLDrivers/XmlLDrivers_SequenceNodeOfSequenceOfNamespaceDef_0.cxx" )
  SOURCE_GROUP (XmlLDrivers FILES "../../../drv/XmlLDrivers/XmlLDrivers_SequenceNodeOfSequenceOfNamespaceDef_0.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../drv/XmlLDrivers/XmlLDrivers_SequenceOfNamespaceDef_0.cxx" )
  SOURCE_GROUP (XmlLDrivers FILES "../../../drv/XmlLDrivers/XmlLDrivers_SequenceOfNamespaceDef_0.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlLDrivers/XmlLDrivers.cxx" )
  SOURCE_GROUP (XmlLDrivers FILES "../../../src/XmlLDrivers/XmlLDrivers.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlLDrivers/XmlLDrivers_DocumentRetrievalDriver.cxx" )
  SOURCE_GROUP (XmlLDrivers FILES "../../../src/XmlLDrivers/XmlLDrivers_DocumentRetrievalDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlLDrivers/XmlLDrivers_DocumentStorageDriver.cxx" )
  SOURCE_GROUP (XmlLDrivers FILES "../../../src/XmlLDrivers/XmlLDrivers_DocumentStorageDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlLDrivers/XmlLDrivers_NamespaceDef.cxx" )
  SOURCE_GROUP (XmlLDrivers FILES "../../../src/XmlLDrivers/XmlLDrivers_NamespaceDef.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../drv/XmlMDF/XmlMDF_DataMapIteratorOfMapOfDriver_0.cxx" )
  SOURCE_GROUP (XmlMDF FILES "../../../drv/XmlMDF/XmlMDF_DataMapIteratorOfMapOfDriver_0.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../drv/XmlMDF/XmlMDF_DataMapIteratorOfTypeADriverMap_0.cxx" )
  SOURCE_GROUP (XmlMDF FILES "../../../drv/XmlMDF/XmlMDF_DataMapIteratorOfTypeADriverMap_0.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../drv/XmlMDF/XmlMDF_DataMapNodeOfMapOfDriver_0.cxx" )
  SOURCE_GROUP (XmlMDF FILES "../../../drv/XmlMDF/XmlMDF_DataMapNodeOfMapOfDriver_0.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../drv/XmlMDF/XmlMDF_DataMapNodeOfTypeADriverMap_0.cxx" )
  SOURCE_GROUP (XmlMDF FILES "../../../drv/XmlMDF/XmlMDF_DataMapNodeOfTypeADriverMap_0.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../drv/XmlMDF/XmlMDF_MapOfDriver_0.cxx" )
  SOURCE_GROUP (XmlMDF FILES "../../../drv/XmlMDF/XmlMDF_MapOfDriver_0.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../drv/XmlMDF/XmlMDF_TypeADriverMap_0.cxx" )
  SOURCE_GROUP (XmlMDF FILES "../../../drv/XmlMDF/XmlMDF_TypeADriverMap_0.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDF/XmlMDF.cxx" )
  SOURCE_GROUP (XmlMDF FILES "../../../src/XmlMDF/XmlMDF.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDF/XmlMDF_ADriver.cxx" )
  SOURCE_GROUP (XmlMDF FILES "../../../src/XmlMDF/XmlMDF_ADriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDF/XmlMDF_ADriverTable.cxx" )
  SOURCE_GROUP (XmlMDF FILES "../../../src/XmlMDF/XmlMDF_ADriverTable.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDF/XmlMDF_ReferenceDriver.cxx" )
  SOURCE_GROUP (XmlMDF FILES "../../../src/XmlMDF/XmlMDF_ReferenceDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDF/XmlMDF_TagSourceDriver.cxx" )
  SOURCE_GROUP (XmlMDF FILES "../../../src/XmlMDF/XmlMDF_TagSourceDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_AsciiStringDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_AsciiStringDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_BooleanArrayDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_BooleanArrayDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_BooleanListDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_BooleanListDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_ByteArrayDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_ByteArrayDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_CommentDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_CommentDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_DirectoryDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_DirectoryDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_ExpressionDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_ExpressionDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_ExtStringArrayDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_ExtStringArrayDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_ExtStringListDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_ExtStringListDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_IntPackedMapDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_IntPackedMapDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_IntegerArrayDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_IntegerArrayDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_IntegerDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_IntegerDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_IntegerListDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_IntegerListDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_NameDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_NameDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_NamedDataDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_NamedDataDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_NoteBookDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_NoteBookDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_RealArrayDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_RealArrayDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_RealDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_RealDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_RealListDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_RealListDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_ReferenceArrayDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_ReferenceArrayDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_ReferenceListDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_ReferenceListDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_RelationDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_RelationDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_TickDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_TickDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_TreeNodeDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_TreeNodeDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_UAttributeDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_UAttributeDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDataStd/XmlMDataStd_VariableDriver.cxx" )
  SOURCE_GROUP (XmlMDataStd FILES "../../../src/XmlMDataStd/XmlMDataStd_VariableDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDocStd/XmlMDocStd.cxx" )
  SOURCE_GROUP (XmlMDocStd FILES "../../../src/XmlMDocStd/XmlMDocStd.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMDocStd/XmlMDocStd_XLinkDriver.cxx" )
  SOURCE_GROUP (XmlMDocStd FILES "../../../src/XmlMDocStd/XmlMDocStd_XLinkDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMFunction/XmlMFunction.cxx" )
  SOURCE_GROUP (XmlMFunction FILES "../../../src/XmlMFunction/XmlMFunction.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMFunction/XmlMFunction_FunctionDriver.cxx" )
  SOURCE_GROUP (XmlMFunction FILES "../../../src/XmlMFunction/XmlMFunction_FunctionDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMFunction/XmlMFunction_GraphNodeDriver.cxx" )
  SOURCE_GROUP (XmlMFunction FILES "../../../src/XmlMFunction/XmlMFunction_GraphNodeDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlMFunction/XmlMFunction_ScopeDriver.cxx" )
  SOURCE_GROUP (XmlMFunction FILES "../../../src/XmlMFunction/XmlMFunction_ScopeDriver.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlObjMgt/XmlObjMgt.cxx" )
  SOURCE_GROUP (XmlObjMgt FILES "../../../src/XmlObjMgt/XmlObjMgt.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlObjMgt/XmlObjMgt_GP.cxx" )
  SOURCE_GROUP (XmlObjMgt FILES "../../../src/XmlObjMgt/XmlObjMgt_GP.cxx")

  list( APPEND TKXmlL_USED_SRCFILES "../../../src/XmlObjMgt/XmlObjMgt_Persistent.cxx" )
  SOURCE_GROUP (XmlObjMgt FILES "../../../src/XmlObjMgt/XmlObjMgt_Persistent.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKXmlL)
 add_library( TKXmlL SHARED ${TKXmlL_USED_SRCFILES} )

 set_property(TARGET TKXmlL PROPERTY FOLDER ApplicationFramework)

 install( TARGETS TKXmlL
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKXmlL.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKXmlL PROPERTIES COMPILE_FLAGS "${TKXmlL_PRECOMPILED_DEFS}" )
 include_directories( ${TKXmlL_COMPILER_DIRECTORIES} )
 target_link_libraries( TKXmlL ${TKXmlL_USED_LIBS} )
endif()
