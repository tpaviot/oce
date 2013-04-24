project(TKTObj)

if (WIN32)
  list( APPEND TKTObj_PRECOMPILED_DEFS "-D__TObj_DLL" )
  string( REGEX REPLACE ";" " " TKTObj_PRECOMPILED_DEFS "${TKTObj_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKTObj_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKTObj_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKTObj_COMPILER_DIRECTORIES "../../../drv/TObj" )
  list( APPEND TKTObj_COMPILER_DIRECTORIES "../../../src/TObj" )

if (WIN32)
else()
endif()

  list( APPEND TKTObj_USED_LIBS TKCDF )
  list( APPEND TKTObj_USED_LIBS TKernel )
  list( APPEND TKTObj_USED_LIBS TKMath )
  list( APPEND TKTObj_USED_LIBS TKLCAF )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_Application.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_Application.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_Assistant.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_Assistant.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_CheckModel.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_CheckModel.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_HiddenPartition.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_HiddenPartition.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_LabelIterator.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_LabelIterator.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_Model.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_Model.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_ModelIterator.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_ModelIterator.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_Object.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_Object.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_ObjectIterator.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_ObjectIterator.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_OcafObjectIterator.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_OcafObjectIterator.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_Partition.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_Partition.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_Persistence.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_Persistence.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_ReferenceIterator.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_ReferenceIterator.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_SequenceIterator.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_SequenceIterator.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_SequenceOfObject.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_SequenceOfObject.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_TIntSparseArray.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_TIntSparseArray.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_TModel.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_TModel.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_TNameContainer.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_TNameContainer.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_TObject.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_TObject.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_TReference.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_TReference.cxx")

  list( APPEND TKTObj_USED_SRCFILES "../../../src/TObj/TObj_TXYZ.cxx" )
  SOURCE_GROUP (TObj FILES "../../../src/TObj/TObj_TXYZ.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKTObj)
 add_library( TKTObj SHARED ${TKTObj_USED_SRCFILES} )

 set_property(TARGET TKTObj PROPERTY FOLDER ApplicationFramework)

 install( TARGETS TKTObj
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKTObj.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKTObj PROPERTIES COMPILE_FLAGS "${TKTObj_PRECOMPILED_DEFS}" )
 include_directories( ${TKTObj_COMPILER_DIRECTORIES} )
 target_link_libraries( TKTObj ${TKTObj_USED_LIBS} )
endif()
