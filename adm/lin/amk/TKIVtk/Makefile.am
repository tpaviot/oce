# Makefile.am for Open Cascade toolkit TKIVtk
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/IVtk : @top_srcdir@/src/IVtk: \
@top_srcdir@/drv/IVtkOCC : @top_srcdir@/src/IVtkOCC: \
@top_srcdir@/drv/IVtkVTK : @top_srcdir@/src/IVtkVTK: \
@top_srcdir@/drv/IVtkTools : @top_srcdir@/src/IVtkTools


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES) $(CSF_VTK_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/IVtk -I@top_srcdir@/src/IVtk \
-I@top_srcdir@/drv/IVtkOCC -I@top_srcdir@/src/IVtkOCC \
-I@top_srcdir@/drv/IVtkVTK -I@top_srcdir@/src/IVtkVTK \
-I@top_srcdir@/drv/IVtkTools -I@top_srcdir@/src/IVtkTools


lib_LTLIBRARIES=libTKIVtk.la

libTKIVtk_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKernel/libTKernel.la \
../TKBRep/libTKBRep.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKGeomBase/libTKGeomBase.la \
../TKMath/libTKMath.la \
../TKMesh/libTKMesh.la \
../TKService/libTKService.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKV3d/libTKV3d.la \
$(STLPort_LIB) $(CSF_VTK_LIB) 

libTKIVtk_la_SOURCES = \
@top_srcdir@/src/IVtk/IVtk_IShape.cxx \
@top_srcdir@/src/IVtk/IVtk_IShapeData.cxx \
@top_srcdir@/src/IVtk/IVtk_IShapeMesher.cxx \
@top_srcdir@/src/IVtk/IVtk_IShapePickerAlgo.cxx \
@top_srcdir@/src/IVtk/IVtk_IView.cxx \
@top_srcdir@/src/IVtk/IVtk_Interface.cxx \
@top_srcdir@/src/IVtkOCC/IVtkOCC_SelectableObject.cxx \
@top_srcdir@/src/IVtkOCC/IVtkOCC_Shape.cxx \
@top_srcdir@/src/IVtkOCC/IVtkOCC_ShapeMesher.cxx \
@top_srcdir@/src/IVtkOCC/IVtkOCC_ShapePickerAlgo.cxx \
@top_srcdir@/src/IVtkOCC/IVtkOCC_ViewerSelector.cxx \
@top_srcdir@/src/IVtkTools/IVtkTools.cxx \
@top_srcdir@/src/IVtkTools/IVtkTools_DisplayModeFilter.cxx \
@top_srcdir@/src/IVtkTools/IVtkTools_ShapeDataSource.cxx \
@top_srcdir@/src/IVtkTools/IVtkTools_ShapeObject.cxx \
@top_srcdir@/src/IVtkTools/IVtkTools_ShapePicker.cxx \
@top_srcdir@/src/IVtkTools/IVtkTools_SubPolyDataFilter.cxx \
@top_srcdir@/src/IVtkVTK/IVtkVTK_ShapeData.cxx \
@top_srcdir@/src/IVtkVTK/IVtkVTK_View.cxx

