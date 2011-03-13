# Makefile.am for Open Cascade toolkit TKXMesh
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/XBRepMesh : @top_srcdir@/src/XBRepMesh


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/XBRepMesh -I@top_srcdir@/src/XBRepMesh


lib_LTLIBRARIES=libTKXMesh.la

libTKXMesh_la_LIBADD = \
../TKMesh/libTKMesh.la \
../TKG2d/libTKG2d.la \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
../TKBRep/libTKBRep.la \
$(STLPort_LIB) 

libTKXMesh_la_SOURCES = \
@top_srcdir@/src/XBRepMesh/XBRepMesh.cxx

