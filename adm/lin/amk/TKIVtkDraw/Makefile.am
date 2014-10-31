# Makefile.am for Open Cascade toolkit TKIVtkDraw
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/IVtkDraw : @top_srcdir@/src/IVtkDraw


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES) $(CSF_VTK_INCLUDES) $(CSF_TclLibs_INCLUDES) $(CSF_TclTkLibs_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/IVtkDraw -I@top_srcdir@/src/IVtkDraw


lib_LTLIBRARIES=libTKIVtkDraw.la

libTKIVtkDraw_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKernel/libTKernel.la \
../TKBRep/libTKBRep.la \
../TKDraw/libTKDraw.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKGeomBase/libTKGeomBase.la \
../TKMath/libTKMath.la \
../TKMesh/libTKMesh.la \
../TKService/libTKService.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKV3d/libTKV3d.la \
../TKOpenGl/libTKOpenGl.la \
../TKIVtk/libTKIVtk.la \
$(STLPort_LIB) $(CSF_VTK_LIB) $(CSF_TclLibs_LIB) $(CSF_TclTkLibs_LIB) 

libTKIVtkDraw_la_SOURCES = \
@top_srcdir@/src/IVtkDraw/IVtkDraw.cxx \
@top_srcdir@/src/IVtkDraw/IVtkDraw_HighlightAndSelectionPipeline.cxx \
@top_srcdir@/src/IVtkDraw/IVtkDraw_Interactor.cxx

