# Makefile.am for Open Cascade toolkit TKStdSchema
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/StdSchema : @top_srcdir@/src/StdSchema: \
@top_srcdir@/drv/StdDrivers : @top_srcdir@/src/StdDrivers


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/StdSchema -I@top_srcdir@/src/StdSchema \
-I@top_srcdir@/drv/StdDrivers -I@top_srcdir@/src/StdDrivers


lib_LTLIBRARIES=libTKStdSchema.la

libTKStdSchema_la_LIBADD = \
../TKMath/libTKMath.la \
../TKPCAF/libTKPCAF.la \
../TKernel/libTKernel.la \
../TKLCAF/libTKLCAF.la \
../TKCAF/libTKCAF.la \
../TKPLCAF/libTKPLCAF.la \
../TKPShape/libTKPShape.la \
../PTKernel/libPTKernel.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../TKCDF/libTKCDF.la \
../TKShapeSchema/libTKShapeSchema.la \
../TKStdLSchema/libTKStdLSchema.la \
$(STLPort_LIB) 

libTKStdSchema_la_SOURCES = \
@top_srcdir@/drv/StdSchema/StdSchema.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_DBC_VArrayOfCharacter.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_DBC_VArrayOfExtCharacter.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PColStd_FieldOfHArray1OfInteger.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PColStd_HArray1OfInteger.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PCollection_HAsciiString.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PCollection_HExtendedString.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PDF_Attribute.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PDF_FieldOfHAttributeArray1.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PDF_HAttributeArray1.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PDataStd_Integer.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PDataStd_Real.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PDataXtd_Axis.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PDataXtd_Constraint.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PDataXtd_Geometry.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PDataXtd_PatternStd.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PDataXtd_Placement.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PDataXtd_Plane.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PDataXtd_Point.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PDataXtd_Position.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PDataXtd_Shape.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PNaming_FieldOfHArray1OfNamedShape.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PNaming_HArray1OfNamedShape.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PNaming_Name.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PNaming_Name_1.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PNaming_NamedShape.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PNaming_Naming.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PNaming_Naming_1.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PPrsStd_AISPresentation.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PPrsStd_AISPresentation_1.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PTopLoc_Datum3D.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PTopLoc_ItemLocation.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PTopLoc_Location.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PTopoDS_FieldOfHArray1OfShape1.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PTopoDS_HArray1OfShape1.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PTopoDS_Shape1.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_PTopoDS_TShape1.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_Standard_Persistent.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_Standard_Storable.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_gp_Ax1.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_gp_Ax2.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_gp_Ax2d.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_gp_Ax3.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_gp_Dir.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_gp_Dir2d.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_gp_Mat.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_gp_Mat2d.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_gp_Pnt.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_gp_Pnt2d.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_gp_Trsf.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_gp_Trsf2d.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_gp_Vec.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_gp_Vec2d.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_gp_XY.cxx \
@top_srcdir@/drv/StdSchema/StdSchema_gp_XYZ.cxx \
@top_srcdir@/src/StdDrivers/StdDrivers.cxx \
@top_srcdir@/src/StdDrivers/StdDrivers_DocumentRetrievalDriver.cxx \
@top_srcdir@/src/StdDrivers/StdDrivers_DocumentStorageDriver.cxx

