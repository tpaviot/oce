# Makefile.am for Open Cascade toolkit TKXCAFSchema
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/MXCAFDoc : @top_srcdir@/src/MXCAFDoc: \
@top_srcdir@/drv/PXCAFDoc : @top_srcdir@/src/PXCAFDoc: \
@top_srcdir@/drv/XCAFDrivers : @top_srcdir@/src/XCAFDrivers: \
@top_srcdir@/drv/XCAFSchema : @top_srcdir@/src/XCAFSchema


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/MXCAFDoc -I@top_srcdir@/src/MXCAFDoc \
-I@top_srcdir@/drv/PXCAFDoc -I@top_srcdir@/src/PXCAFDoc \
-I@top_srcdir@/drv/XCAFDrivers -I@top_srcdir@/src/XCAFDrivers \
-I@top_srcdir@/drv/XCAFSchema -I@top_srcdir@/src/XCAFSchema


lib_LTLIBRARIES=libTKXCAFSchema.la

libTKXCAFSchema_la_LIBADD = \
../TKMath/libTKMath.la \
../TKernel/libTKernel.la \
../TKLCAF/libTKLCAF.la \
../TKStdSchema/libTKStdSchema.la \
../TKPLCAF/libTKPLCAF.la \
../TKPShape/libTKPShape.la \
../PTKernel/libPTKernel.la \
../TKXCAF/libTKXCAF.la \
../TKCDF/libTKCDF.la \
../TKShapeSchema/libTKShapeSchema.la \
../TKStdLSchema/libTKStdLSchema.la \
$(STLPort_LIB) 

libTKXCAFSchema_la_SOURCES = \
@top_srcdir@/drv/PXCAFDoc/PXCAFDoc_GraphNodeSequence_0.cxx \
@top_srcdir@/drv/PXCAFDoc/PXCAFDoc_SeqExplorerOfGraphNodeSequence_0.cxx \
@top_srcdir@/drv/PXCAFDoc/PXCAFDoc_SeqNodeOfGraphNodeSequence_0.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_DBC_VArrayOfCharacter.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_DBC_VArrayOfExtCharacter.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PColStd_FieldOfHArray1OfReal.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PColStd_HArray1OfReal.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PCollection_HAsciiString.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PCollection_HExtendedString.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PDF_Attribute.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PMMgt_PManaged.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PTopLoc_Datum3D.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PTopLoc_ItemLocation.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PTopLoc_Location.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PXCAFDoc_Area.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PXCAFDoc_Centroid.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PXCAFDoc_Color.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PXCAFDoc_ColorTool.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PXCAFDoc_Datum.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PXCAFDoc_DimTol.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PXCAFDoc_DimTolTool.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PXCAFDoc_DocumentTool.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PXCAFDoc_GraphNode.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PXCAFDoc_GraphNodeSequence.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PXCAFDoc_LayerTool.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PXCAFDoc_Location.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PXCAFDoc_Material.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PXCAFDoc_MaterialTool.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PXCAFDoc_SeqNodeOfGraphNodeSequence.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PXCAFDoc_ShapeTool.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_PXCAFDoc_Volume.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_Quantity_Color.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_Standard_GUID.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_Standard_Persistent.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_Standard_Storable.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_gp_Ax1.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_gp_Ax2.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_gp_Ax2d.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_gp_Ax3.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_gp_Dir.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_gp_Dir2d.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_gp_Mat.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_gp_Mat2d.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_gp_Pnt.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_gp_Pnt2d.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_gp_Trsf.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_gp_Trsf2d.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_gp_Vec.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_gp_Vec2d.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_gp_XY.cxx \
@top_srcdir@/drv/XCAFSchema/XCAFSchema_gp_XYZ.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_AreaRetrievalDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_AreaStorageDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_CentroidRetrievalDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_CentroidStorageDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_ColorRetrievalDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_ColorStorageDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_ColorToolRetrievalDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_ColorToolStorageDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_DatumRetrievalDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_DatumStorageDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_DimTolRetrievalDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_DimTolStorageDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_DimTolToolRetrievalDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_DimTolToolStorageDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_DocumentToolRetrievalDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_DocumentToolStorageDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_GraphNodeRetrievalDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_GraphNodeStorageDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_LayerToolRetrievalDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_LayerToolStorageDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_LocationRetrievalDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_LocationStorageDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_MaterialRetrievalDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_MaterialStorageDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_MaterialToolRetrievalDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_MaterialToolStorageDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_ShapeToolRetrievalDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_ShapeToolStorageDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_VolumeRetrievalDriver.cxx \
@top_srcdir@/src/MXCAFDoc/MXCAFDoc_VolumeStorageDriver.cxx \
@top_srcdir@/src/PXCAFDoc/PXCAFDoc_Area.cxx \
@top_srcdir@/src/PXCAFDoc/PXCAFDoc_Centroid.cxx \
@top_srcdir@/src/PXCAFDoc/PXCAFDoc_Color.cxx \
@top_srcdir@/src/PXCAFDoc/PXCAFDoc_ColorTool.cxx \
@top_srcdir@/src/PXCAFDoc/PXCAFDoc_Datum.cxx \
@top_srcdir@/src/PXCAFDoc/PXCAFDoc_DimTol.cxx \
@top_srcdir@/src/PXCAFDoc/PXCAFDoc_DimTolTool.cxx \
@top_srcdir@/src/PXCAFDoc/PXCAFDoc_DocumentTool.cxx \
@top_srcdir@/src/PXCAFDoc/PXCAFDoc_GraphNode.cxx \
@top_srcdir@/src/PXCAFDoc/PXCAFDoc_LayerTool.cxx \
@top_srcdir@/src/PXCAFDoc/PXCAFDoc_Location.cxx \
@top_srcdir@/src/PXCAFDoc/PXCAFDoc_Material.cxx \
@top_srcdir@/src/PXCAFDoc/PXCAFDoc_MaterialTool.cxx \
@top_srcdir@/src/PXCAFDoc/PXCAFDoc_ShapeTool.cxx \
@top_srcdir@/src/PXCAFDoc/PXCAFDoc_Volume.cxx \
@top_srcdir@/src/XCAFDrivers/XCAFDrivers.cxx \
@top_srcdir@/src/XCAFDrivers/XCAFDrivers_DocumentRetrievalDriver.cxx \
@top_srcdir@/src/XCAFDrivers/XCAFDrivers_DocumentStorageDriver.cxx

libTKXCAFSchema_laLDFLAGS = -version-info @oce_version_info@

