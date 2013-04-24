# Makefile.am for Open Cascade toolkit TKXMesh
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/XBRepMesh : @top_srcdir@/src/XBRepMesh


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/XBRepMesh -I@top_srcdir@/src/XBRepMesh


lib_LTLIBRARIES=libTKXMesh.la

libTKXMesh_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKBRep/libTKBRep.la \
../TKMath/libTKMath.la \
../TKernel/libTKernel.la \
../TKG2d/libTKG2d.la \
../TKMesh/libTKMesh.la \
$(STLPort_LIB) 

libTKXMesh_la_SOURCES = \
@top_srcdir@/src/XBRepMesh/XBRepMesh.cxx

