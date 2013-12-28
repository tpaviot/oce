project(TKXCAFSchema)

if (WIN32)
  list( APPEND TKXCAFSchema_PRECOMPILED_DEFS "-D__MXCAFDoc_DLL" )
  list( APPEND TKXCAFSchema_PRECOMPILED_DEFS "-D__PXCAFDoc_DLL" )
  list( APPEND TKXCAFSchema_PRECOMPILED_DEFS "-D__XCAFDrivers_DLL" )
  list( APPEND TKXCAFSchema_PRECOMPILED_DEFS "-D__XCAFSchema_DLL" )
  string( REGEX REPLACE ";" " " TKXCAFSchema_PRECOMPILED_DEFS "${TKXCAFSchema_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKXCAFSchema_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKXCAFSchema_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKXCAFSchema_COMPILER_DIRECTORIES "../../../drv/MXCAFDoc" )
  list( APPEND TKXCAFSchema_COMPILER_DIRECTORIES "../../../src/MXCAFDoc" )
  list( APPEND TKXCAFSchema_COMPILER_DIRECTORIES "../../../drv/PXCAFDoc" )
  list( APPEND TKXCAFSchema_COMPILER_DIRECTORIES "../../../src/PXCAFDoc" )
  list( APPEND TKXCAFSchema_COMPILER_DIRECTORIES "../../../drv/XCAFDrivers" )
  list( APPEND TKXCAFSchema_COMPILER_DIRECTORIES "../../../src/XCAFDrivers" )
  list( APPEND TKXCAFSchema_COMPILER_DIRECTORIES "../../../drv/XCAFSchema" )
  list( APPEND TKXCAFSchema_COMPILER_DIRECTORIES "../../../src/XCAFSchema" )

if (WIN32)
else()
endif()

  list( APPEND TKXCAFSchema_USED_LIBS TKPLCAF )
  list( APPEND TKXCAFSchema_USED_LIBS TKernel )
  list( APPEND TKXCAFSchema_USED_LIBS PTKernel )
  list( APPEND TKXCAFSchema_USED_LIBS TKMath )
  list( APPEND TKXCAFSchema_USED_LIBS TKPShape )
  list( APPEND TKXCAFSchema_USED_LIBS TKCDF )
  list( APPEND TKXCAFSchema_USED_LIBS TKShapeSchema )
  list( APPEND TKXCAFSchema_USED_LIBS TKLCAF )
  list( APPEND TKXCAFSchema_USED_LIBS TKPCAF )
  list( APPEND TKXCAFSchema_USED_LIBS TKXCAF )
  list( APPEND TKXCAFSchema_USED_LIBS TKStdLSchema )
  list( APPEND TKXCAFSchema_USED_LIBS TKStdSchema )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_AreaRetrievalDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_AreaRetrievalDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_AreaStorageDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_AreaStorageDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_CentroidRetrievalDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_CentroidRetrievalDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_CentroidStorageDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_CentroidStorageDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_ColorRetrievalDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_ColorRetrievalDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_ColorStorageDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_ColorStorageDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_ColorToolRetrievalDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_ColorToolRetrievalDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_ColorToolStorageDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_ColorToolStorageDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_DatumRetrievalDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_DatumRetrievalDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_DatumStorageDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_DatumStorageDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_DimTolRetrievalDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_DimTolRetrievalDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_DimTolStorageDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_DimTolStorageDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_DimTolToolRetrievalDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_DimTolToolRetrievalDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_DimTolToolStorageDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_DimTolToolStorageDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_DocumentToolRetrievalDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_DocumentToolRetrievalDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_DocumentToolStorageDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_DocumentToolStorageDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_GraphNodeRetrievalDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_GraphNodeRetrievalDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_GraphNodeStorageDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_GraphNodeStorageDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_LayerToolRetrievalDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_LayerToolRetrievalDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_LayerToolStorageDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_LayerToolStorageDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_LocationRetrievalDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_LocationRetrievalDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_LocationStorageDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_LocationStorageDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_MaterialRetrievalDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_MaterialRetrievalDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_MaterialStorageDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_MaterialStorageDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_MaterialToolRetrievalDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_MaterialToolRetrievalDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_MaterialToolStorageDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_MaterialToolStorageDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_ShapeToolRetrievalDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_ShapeToolRetrievalDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_ShapeToolStorageDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_ShapeToolStorageDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_VolumeRetrievalDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_VolumeRetrievalDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/MXCAFDoc/MXCAFDoc_VolumeStorageDriver.cxx" )
  SOURCE_GROUP (MXCAFDoc FILES "../../../src/MXCAFDoc/MXCAFDoc_VolumeStorageDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/PXCAFDoc/PXCAFDoc_GraphNodeSequence_0.cxx" )
  SOURCE_GROUP (PXCAFDoc FILES "../../../drv/PXCAFDoc/PXCAFDoc_GraphNodeSequence_0.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/PXCAFDoc/PXCAFDoc_SeqExplorerOfGraphNodeSequence_0.cxx" )
  SOURCE_GROUP (PXCAFDoc FILES "../../../drv/PXCAFDoc/PXCAFDoc_SeqExplorerOfGraphNodeSequence_0.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/PXCAFDoc/PXCAFDoc_SeqNodeOfGraphNodeSequence_0.cxx" )
  SOURCE_GROUP (PXCAFDoc FILES "../../../drv/PXCAFDoc/PXCAFDoc_SeqNodeOfGraphNodeSequence_0.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/PXCAFDoc/PXCAFDoc_Area.cxx" )
  SOURCE_GROUP (PXCAFDoc FILES "../../../src/PXCAFDoc/PXCAFDoc_Area.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/PXCAFDoc/PXCAFDoc_Centroid.cxx" )
  SOURCE_GROUP (PXCAFDoc FILES "../../../src/PXCAFDoc/PXCAFDoc_Centroid.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/PXCAFDoc/PXCAFDoc_Color.cxx" )
  SOURCE_GROUP (PXCAFDoc FILES "../../../src/PXCAFDoc/PXCAFDoc_Color.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/PXCAFDoc/PXCAFDoc_ColorTool.cxx" )
  SOURCE_GROUP (PXCAFDoc FILES "../../../src/PXCAFDoc/PXCAFDoc_ColorTool.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/PXCAFDoc/PXCAFDoc_Datum.cxx" )
  SOURCE_GROUP (PXCAFDoc FILES "../../../src/PXCAFDoc/PXCAFDoc_Datum.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/PXCAFDoc/PXCAFDoc_DimTol.cxx" )
  SOURCE_GROUP (PXCAFDoc FILES "../../../src/PXCAFDoc/PXCAFDoc_DimTol.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/PXCAFDoc/PXCAFDoc_DimTolTool.cxx" )
  SOURCE_GROUP (PXCAFDoc FILES "../../../src/PXCAFDoc/PXCAFDoc_DimTolTool.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/PXCAFDoc/PXCAFDoc_DocumentTool.cxx" )
  SOURCE_GROUP (PXCAFDoc FILES "../../../src/PXCAFDoc/PXCAFDoc_DocumentTool.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/PXCAFDoc/PXCAFDoc_GraphNode.cxx" )
  SOURCE_GROUP (PXCAFDoc FILES "../../../src/PXCAFDoc/PXCAFDoc_GraphNode.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/PXCAFDoc/PXCAFDoc_LayerTool.cxx" )
  SOURCE_GROUP (PXCAFDoc FILES "../../../src/PXCAFDoc/PXCAFDoc_LayerTool.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/PXCAFDoc/PXCAFDoc_Location.cxx" )
  SOURCE_GROUP (PXCAFDoc FILES "../../../src/PXCAFDoc/PXCAFDoc_Location.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/PXCAFDoc/PXCAFDoc_Material.cxx" )
  SOURCE_GROUP (PXCAFDoc FILES "../../../src/PXCAFDoc/PXCAFDoc_Material.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/PXCAFDoc/PXCAFDoc_MaterialTool.cxx" )
  SOURCE_GROUP (PXCAFDoc FILES "../../../src/PXCAFDoc/PXCAFDoc_MaterialTool.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/PXCAFDoc/PXCAFDoc_ShapeTool.cxx" )
  SOURCE_GROUP (PXCAFDoc FILES "../../../src/PXCAFDoc/PXCAFDoc_ShapeTool.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/PXCAFDoc/PXCAFDoc_Volume.cxx" )
  SOURCE_GROUP (PXCAFDoc FILES "../../../src/PXCAFDoc/PXCAFDoc_Volume.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/XCAFDrivers/XCAFDrivers.cxx" )
  SOURCE_GROUP (XCAFDrivers FILES "../../../src/XCAFDrivers/XCAFDrivers.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/XCAFDrivers/XCAFDrivers_DocumentRetrievalDriver.cxx" )
  SOURCE_GROUP (XCAFDrivers FILES "../../../src/XCAFDrivers/XCAFDrivers_DocumentRetrievalDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../src/XCAFDrivers/XCAFDrivers_DocumentStorageDriver.cxx" )
  SOURCE_GROUP (XCAFDrivers FILES "../../../src/XCAFDrivers/XCAFDrivers_DocumentStorageDriver.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_DBC_VArrayOfCharacter.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_DBC_VArrayOfCharacter.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_DBC_VArrayOfExtCharacter.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_DBC_VArrayOfExtCharacter.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PColStd_FieldOfHArray1OfReal.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PColStd_FieldOfHArray1OfReal.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PColStd_HArray1OfReal.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PColStd_HArray1OfReal.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PCollection_HAsciiString.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PCollection_HAsciiString.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PCollection_HExtendedString.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PCollection_HExtendedString.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PDF_Attribute.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PDF_Attribute.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PMMgt_PManaged.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PMMgt_PManaged.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PTopLoc_Datum3D.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PTopLoc_Datum3D.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PTopLoc_ItemLocation.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PTopLoc_ItemLocation.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PTopLoc_Location.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PTopLoc_Location.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_Area.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_Area.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_Centroid.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_Centroid.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_Color.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_Color.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_ColorTool.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_ColorTool.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_Datum.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_Datum.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_DimTol.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_DimTol.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_DimTolTool.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_DimTolTool.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_DocumentTool.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_DocumentTool.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_GraphNode.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_GraphNode.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_GraphNodeSequence.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_GraphNodeSequence.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_LayerTool.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_LayerTool.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_Location.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_Location.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_Material.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_Material.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_MaterialTool.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_MaterialTool.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_SeqNodeOfGraphNodeSequence.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_SeqNodeOfGraphNodeSequence.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_ShapeTool.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_ShapeTool.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_Volume.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_PXCAFDoc_Volume.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_Quantity_Color.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_Quantity_Color.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_Standard_GUID.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_Standard_GUID.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_Standard_Persistent.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_Standard_Persistent.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_Standard_Storable.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_Standard_Storable.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_gp_Ax1.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_gp_Ax1.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_gp_Ax2.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_gp_Ax2.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_gp_Ax2d.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_gp_Ax2d.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_gp_Ax3.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_gp_Ax3.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_gp_Dir.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_gp_Dir.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_gp_Dir2d.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_gp_Dir2d.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_gp_Mat.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_gp_Mat.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_gp_Mat2d.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_gp_Mat2d.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_gp_Pnt.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_gp_Pnt.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_gp_Pnt2d.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_gp_Pnt2d.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_gp_Trsf.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_gp_Trsf.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_gp_Trsf2d.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_gp_Trsf2d.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_gp_Vec.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_gp_Vec.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_gp_Vec2d.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_gp_Vec2d.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_gp_XY.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_gp_XY.cxx")

  list( APPEND TKXCAFSchema_USED_SRCFILES "../../../drv/XCAFSchema/XCAFSchema_gp_XYZ.cxx" )
  SOURCE_GROUP (XCAFSchema FILES "../../../drv/XCAFSchema/XCAFSchema_gp_XYZ.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKXCAFSchema)
 add_library( TKXCAFSchema SHARED ${TKXCAFSchema_USED_SRCFILES} )

 set_property(TARGET TKXCAFSchema PROPERTY FOLDER DataExchange)

 install( TARGETS TKXCAFSchema
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKXCAFSchema.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKXCAFSchema PROPERTIES COMPILE_FLAGS "${TKXCAFSchema_PRECOMPILED_DEFS}" )
 include_directories( ${TKXCAFSchema_COMPILER_DIRECTORIES} )
 target_link_libraries( TKXCAFSchema ${TKXCAFSchema_USED_LIBS} )
endif()
