# Makefile.am for Open Cascade toolkit TKPrim
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/BRepPrim : @top_srcdir@/src/BRepPrim: \
@top_srcdir@/drv/Primitives : @top_srcdir@/src/Primitives: \
@top_srcdir@/drv/BRepSweep : @top_srcdir@/src/BRepSweep: \
@top_srcdir@/drv/Sweep : @top_srcdir@/src/Sweep: \
@top_srcdir@/drv/BRepPrimAPI : @top_srcdir@/src/BRepPrimAPI


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/BRepPrim -I@top_srcdir@/src/BRepPrim \
-I@top_srcdir@/drv/Primitives -I@top_srcdir@/src/Primitives \
-I@top_srcdir@/drv/BRepSweep -I@top_srcdir@/src/BRepSweep \
-I@top_srcdir@/drv/Sweep -I@top_srcdir@/src/Sweep \
-I@top_srcdir@/drv/BRepPrimAPI -I@top_srcdir@/src/BRepPrimAPI


lib_LTLIBRARIES=libTKPrim.la

libTKPrim_la_LIBADD = \
../TKMath/libTKMath.la \
../TKernel/libTKernel.la \
../TKG2d/libTKG2d.la \
../TKBRep/libTKBRep.la \
../TKGeomBase/libTKGeomBase.la \
../TKG3d/libTKG3d.la \
../TKTopAlgo/libTKTopAlgo.la \
$(STLPort_LIB) 

libTKPrim_la_SOURCES = \
@top_srcdir@/drv/BRepPrim/BRepPrim_GWedge_0.cxx \
@top_srcdir@/drv/BRepPrim/BRepPrim_OneAxis_0.cxx \
@top_srcdir@/drv/BRepSweep/BRepSweep_Array2OfShapesOfNumLinearRegularSweep_0.cxx \
@top_srcdir@/drv/BRepSweep/BRepSweep_NumLinearRegularSweep_0.cxx \
@top_srcdir@/drv/BRepSweep/BRepSweep_SequenceNodeOfSequenceOfShapesOfNumLinearRegularSweep_0.cxx \
@top_srcdir@/drv/BRepSweep/BRepSweep_SequenceOfShapesOfNumLinearRegularSweep_0.cxx \
@top_srcdir@/src/BRepPrim/BRepPrim_Builder.cxx \
@top_srcdir@/src/BRepPrim/BRepPrim_Cone.cxx \
@top_srcdir@/src/BRepPrim/BRepPrim_Cylinder.cxx \
@top_srcdir@/src/BRepPrim/BRepPrim_FaceBuilder.cxx \
@top_srcdir@/src/BRepPrim/BRepPrim_Revolution.cxx \
@top_srcdir@/src/BRepPrim/BRepPrim_Sphere.cxx \
@top_srcdir@/src/BRepPrim/BRepPrim_Torus.cxx \
@top_srcdir@/src/BRepPrim/BRepPrim_Wedge.cxx \
@top_srcdir@/src/BRepPrimAPI/BRepPrimAPI_MakeBox.cxx \
@top_srcdir@/src/BRepPrimAPI/BRepPrimAPI_MakeCone.cxx \
@top_srcdir@/src/BRepPrimAPI/BRepPrimAPI_MakeCylinder.cxx \
@top_srcdir@/src/BRepPrimAPI/BRepPrimAPI_MakeHalfSpace.cxx \
@top_srcdir@/src/BRepPrimAPI/BRepPrimAPI_MakeOneAxis.cxx \
@top_srcdir@/src/BRepPrimAPI/BRepPrimAPI_MakePrism.cxx \
@top_srcdir@/src/BRepPrimAPI/BRepPrimAPI_MakeRevol.cxx \
@top_srcdir@/src/BRepPrimAPI/BRepPrimAPI_MakeRevolution.cxx \
@top_srcdir@/src/BRepPrimAPI/BRepPrimAPI_MakeSphere.cxx \
@top_srcdir@/src/BRepPrimAPI/BRepPrimAPI_MakeSweep.cxx \
@top_srcdir@/src/BRepPrimAPI/BRepPrimAPI_MakeTorus.cxx \
@top_srcdir@/src/BRepPrimAPI/BRepPrimAPI_MakeWedge.cxx \
@top_srcdir@/src/BRepSweep/BRepSweep_Builder.cxx \
@top_srcdir@/src/BRepSweep/BRepSweep_Iterator.cxx \
@top_srcdir@/src/BRepSweep/BRepSweep_Prism.cxx \
@top_srcdir@/src/BRepSweep/BRepSweep_Revol.cxx \
@top_srcdir@/src/BRepSweep/BRepSweep_Rotation.cxx \
@top_srcdir@/src/BRepSweep/BRepSweep_Tool.cxx \
@top_srcdir@/src/BRepSweep/BRepSweep_Translation.cxx \
@top_srcdir@/src/BRepSweep/BRepSweep_Trsf.cxx \
@top_srcdir@/src/Sweep/Sweep_NumShape.cxx \
@top_srcdir@/src/Sweep/Sweep_NumShapeIterator.cxx \
@top_srcdir@/src/Sweep/Sweep_NumShapeTool.cxx

