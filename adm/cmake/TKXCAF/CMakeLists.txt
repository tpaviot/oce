project(TKXCAF)

if (WIN32)
  list( APPEND TKXCAF_PRECOMPILED_DEFS "-D__XCAFApp_DLL" )
  list( APPEND TKXCAF_PRECOMPILED_DEFS "-D__XCAFDoc_DLL" )
  list( APPEND TKXCAF_PRECOMPILED_DEFS "-D__XCAFPrs_DLL" )
  string( REGEX REPLACE ";" " " TKXCAF_PRECOMPILED_DEFS "${TKXCAF_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKXCAF_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKXCAF_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKXCAF_COMPILER_DIRECTORIES "../../../drv/XCAFApp" )
  list( APPEND TKXCAF_COMPILER_DIRECTORIES "../../../src/XCAFApp" )
  list( APPEND TKXCAF_COMPILER_DIRECTORIES "../../../drv/XCAFDoc" )
  list( APPEND TKXCAF_COMPILER_DIRECTORIES "../../../src/XCAFDoc" )
  list( APPEND TKXCAF_COMPILER_DIRECTORIES "../../../drv/XCAFPrs" )
  list( APPEND TKXCAF_COMPILER_DIRECTORIES "../../../src/XCAFPrs" )

if (WIN32)
else()
endif()

  list( APPEND TKXCAF_USED_LIBS TKBRep )
  list( APPEND TKXCAF_USED_LIBS TKernel )
  list( APPEND TKXCAF_USED_LIBS TKMath )
  list( APPEND TKXCAF_USED_LIBS TKService )
  list( APPEND TKXCAF_USED_LIBS TKG2d )
  list( APPEND TKXCAF_USED_LIBS TKTopAlgo )
  list( APPEND TKXCAF_USED_LIBS TKV3d )
  list( APPEND TKXCAF_USED_LIBS TKCDF )
  list( APPEND TKXCAF_USED_LIBS TKLCAF )
  list( APPEND TKXCAF_USED_LIBS TKG3d )
  list( APPEND TKXCAF_USED_LIBS TKCAF )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFApp/XCAFApp_Application.cxx" )
  SOURCE_GROUP (XCAFApp FILES "../../../src/XCAFApp/XCAFApp_Application.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../drv/XCAFDoc/XCAFDoc_DataMapIteratorOfDataMapOfShapeLabel_0.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../drv/XCAFDoc/XCAFDoc_DataMapIteratorOfDataMapOfShapeLabel_0.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../drv/XCAFDoc/XCAFDoc_DataMapNodeOfDataMapOfShapeLabel_0.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../drv/XCAFDoc/XCAFDoc_DataMapNodeOfDataMapOfShapeLabel_0.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../drv/XCAFDoc/XCAFDoc_DataMapOfShapeLabel_0.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../drv/XCAFDoc/XCAFDoc_DataMapOfShapeLabel_0.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../drv/XCAFDoc/XCAFDoc_GraphNodeSequence_0.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../drv/XCAFDoc/XCAFDoc_GraphNodeSequence_0.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../drv/XCAFDoc/XCAFDoc_SequenceNodeOfGraphNodeSequence_0.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../drv/XCAFDoc/XCAFDoc_SequenceNodeOfGraphNodeSequence_0.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFDoc/XCAFDoc.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../src/XCAFDoc/XCAFDoc.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFDoc/XCAFDoc_Area.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../src/XCAFDoc/XCAFDoc_Area.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFDoc/XCAFDoc_Centroid.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../src/XCAFDoc/XCAFDoc_Centroid.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFDoc/XCAFDoc_Color.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../src/XCAFDoc/XCAFDoc_Color.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFDoc/XCAFDoc_ColorTool.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../src/XCAFDoc/XCAFDoc_ColorTool.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFDoc/XCAFDoc_Datum.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../src/XCAFDoc/XCAFDoc_Datum.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFDoc/XCAFDoc_DimTol.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../src/XCAFDoc/XCAFDoc_DimTol.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFDoc/XCAFDoc_DimTolTool.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../src/XCAFDoc/XCAFDoc_DimTolTool.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFDoc/XCAFDoc_DocumentTool.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../src/XCAFDoc/XCAFDoc_DocumentTool.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFDoc/XCAFDoc_GraphNode.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../src/XCAFDoc/XCAFDoc_GraphNode.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFDoc/XCAFDoc_LayerTool.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../src/XCAFDoc/XCAFDoc_LayerTool.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFDoc/XCAFDoc_Location.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../src/XCAFDoc/XCAFDoc_Location.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFDoc/XCAFDoc_Material.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../src/XCAFDoc/XCAFDoc_Material.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFDoc/XCAFDoc_MaterialTool.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../src/XCAFDoc/XCAFDoc_MaterialTool.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFDoc/XCAFDoc_ShapeMapTool.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../src/XCAFDoc/XCAFDoc_ShapeMapTool.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFDoc/XCAFDoc_ShapeTool.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../src/XCAFDoc/XCAFDoc_ShapeTool.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFDoc/XCAFDoc_Volume.cxx" )
  SOURCE_GROUP (XCAFDoc FILES "../../../src/XCAFDoc/XCAFDoc_Volume.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../drv/XCAFPrs/XCAFPrs_DataMapIteratorOfDataMapOfShapeStyle_0.cxx" )
  SOURCE_GROUP (XCAFPrs FILES "../../../drv/XCAFPrs/XCAFPrs_DataMapIteratorOfDataMapOfShapeStyle_0.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../drv/XCAFPrs/XCAFPrs_DataMapIteratorOfDataMapOfStyleShape_0.cxx" )
  SOURCE_GROUP (XCAFPrs FILES "../../../drv/XCAFPrs/XCAFPrs_DataMapIteratorOfDataMapOfStyleShape_0.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../drv/XCAFPrs/XCAFPrs_DataMapIteratorOfDataMapOfStyleTransient_0.cxx" )
  SOURCE_GROUP (XCAFPrs FILES "../../../drv/XCAFPrs/XCAFPrs_DataMapIteratorOfDataMapOfStyleTransient_0.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../drv/XCAFPrs/XCAFPrs_DataMapNodeOfDataMapOfShapeStyle_0.cxx" )
  SOURCE_GROUP (XCAFPrs FILES "../../../drv/XCAFPrs/XCAFPrs_DataMapNodeOfDataMapOfShapeStyle_0.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../drv/XCAFPrs/XCAFPrs_DataMapNodeOfDataMapOfStyleShape_0.cxx" )
  SOURCE_GROUP (XCAFPrs FILES "../../../drv/XCAFPrs/XCAFPrs_DataMapNodeOfDataMapOfStyleShape_0.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../drv/XCAFPrs/XCAFPrs_DataMapNodeOfDataMapOfStyleTransient_0.cxx" )
  SOURCE_GROUP (XCAFPrs FILES "../../../drv/XCAFPrs/XCAFPrs_DataMapNodeOfDataMapOfStyleTransient_0.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../drv/XCAFPrs/XCAFPrs_DataMapOfShapeStyle_0.cxx" )
  SOURCE_GROUP (XCAFPrs FILES "../../../drv/XCAFPrs/XCAFPrs_DataMapOfShapeStyle_0.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../drv/XCAFPrs/XCAFPrs_DataMapOfStyleShape_0.cxx" )
  SOURCE_GROUP (XCAFPrs FILES "../../../drv/XCAFPrs/XCAFPrs_DataMapOfStyleShape_0.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../drv/XCAFPrs/XCAFPrs_DataMapOfStyleTransient_0.cxx" )
  SOURCE_GROUP (XCAFPrs FILES "../../../drv/XCAFPrs/XCAFPrs_DataMapOfStyleTransient_0.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFPrs/XCAFPrs.cxx" )
  SOURCE_GROUP (XCAFPrs FILES "../../../src/XCAFPrs/XCAFPrs.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFPrs/XCAFPrs_AISObject.cxx" )
  SOURCE_GROUP (XCAFPrs FILES "../../../src/XCAFPrs/XCAFPrs_AISObject.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFPrs/XCAFPrs_Driver.cxx" )
  SOURCE_GROUP (XCAFPrs FILES "../../../src/XCAFPrs/XCAFPrs_Driver.cxx")

  list( APPEND TKXCAF_USED_SRCFILES "../../../src/XCAFPrs/XCAFPrs_Style.cxx" )
  SOURCE_GROUP (XCAFPrs FILES "../../../src/XCAFPrs/XCAFPrs_Style.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKXCAF)
 add_library( TKXCAF SHARED ${TKXCAF_USED_SRCFILES} )

 set_property(TARGET TKXCAF PROPERTY FOLDER DataExchange)

 install( TARGETS TKXCAF
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKXCAF.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKXCAF PROPERTIES COMPILE_FLAGS "${TKXCAF_PRECOMPILED_DEFS}" )
 include_directories( ${TKXCAF_COMPILER_DIRECTORIES} )
 target_link_libraries( TKXCAF ${TKXCAF_USED_LIBS} )
endif()
