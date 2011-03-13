# Makefile.am for Open Cascade toolkit TKG2d
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/Geom2d : @top_srcdir@/src/Geom2d: \
@top_srcdir@/drv/LProp : @top_srcdir@/src/LProp: \
@top_srcdir@/drv/TColGeom2d : @top_srcdir@/src/TColGeom2d: \
@top_srcdir@/drv/Adaptor2d : @top_srcdir@/src/Adaptor2d: \
@top_srcdir@/drv/Geom2dLProp : @top_srcdir@/src/Geom2dLProp: \
@top_srcdir@/drv/Geom2dAdaptor : @top_srcdir@/src/Geom2dAdaptor: \
@top_srcdir@/drv/TopAbs : @top_srcdir@/src/TopAbs: \
@top_srcdir@/drv/GProp : @top_srcdir@/src/GProp


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/Geom2d -I@top_srcdir@/src/Geom2d \
-I@top_srcdir@/drv/LProp -I@top_srcdir@/src/LProp \
-I@top_srcdir@/drv/TColGeom2d -I@top_srcdir@/src/TColGeom2d \
-I@top_srcdir@/drv/Adaptor2d -I@top_srcdir@/src/Adaptor2d \
-I@top_srcdir@/drv/Geom2dLProp -I@top_srcdir@/src/Geom2dLProp \
-I@top_srcdir@/drv/Geom2dAdaptor -I@top_srcdir@/src/Geom2dAdaptor \
-I@top_srcdir@/drv/TopAbs -I@top_srcdir@/src/TopAbs \
-I@top_srcdir@/drv/GProp -I@top_srcdir@/src/GProp


lib_LTLIBRARIES=libTKG2d.la

libTKG2d_la_LIBADD = \
../TKMath/libTKMath.la \
../TKernel/libTKernel.la \
$(STLPort_LIB) 

libTKG2d_la_SOURCES = \
@top_srcdir@/drv/Adaptor2d/Adaptor2d_HLine2d_0.cxx \
@top_srcdir@/drv/GProp/GProp_UndefinedAxis_0.cxx \
@top_srcdir@/drv/Geom2d/Geom2d_UndefinedDerivative_0.cxx \
@top_srcdir@/drv/Geom2d/Geom2d_UndefinedValue_0.cxx \
@top_srcdir@/drv/Geom2dAdaptor/Geom2dAdaptor_GHCurve_0.cxx \
@top_srcdir@/drv/Geom2dLProp/Geom2dLProp_CLProps2d_0.cxx \
@top_srcdir@/drv/Geom2dLProp/Geom2dLProp_FCurExtOfNumericCurInf2d_0.cxx \
@top_srcdir@/drv/Geom2dLProp/Geom2dLProp_FCurNulOfNumericCurInf2d_0.cxx \
@top_srcdir@/drv/Geom2dLProp/Geom2dLProp_NumericCurInf2d_0.cxx \
@top_srcdir@/drv/LProp/LProp_BadContinuity_0.cxx \
@top_srcdir@/drv/LProp/LProp_NotDefined_0.cxx \
@top_srcdir@/drv/LProp/LProp_SequenceNodeOfSequenceOfCIType_0.cxx \
@top_srcdir@/drv/LProp/LProp_SequenceOfCIType_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_Array1OfBSplineCurve_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_Array1OfBezierCurve_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_Array1OfBoundedCurve_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_Array1OfCurve_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_Array1OfGeometry_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_HArray1OfBSplineCurve_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_HArray1OfBezierCurve_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_HArray1OfBoundedCurve_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_HArray1OfCurve_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_HArray1OfGeometry_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_HSequenceOfBoundedCurve_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_HSequenceOfCurve_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_HSequenceOfGeometry_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_SequenceNodeOfSequenceOfBoundedCurve_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_SequenceNodeOfSequenceOfCurve_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_SequenceNodeOfSequenceOfGeometry_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_SequenceOfBoundedCurve_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_SequenceOfCurve_0.cxx \
@top_srcdir@/drv/TColGeom2d/TColGeom2d_SequenceOfGeometry_0.cxx \
@top_srcdir@/src/Adaptor2d/Adaptor2d_Curve2d.cxx \
@top_srcdir@/src/Adaptor2d/Adaptor2d_HCurve2d.cxx \
@top_srcdir@/src/Adaptor2d/Adaptor2d_Line2d.cxx \
@top_srcdir@/src/GProp/GProp.cxx \
@top_srcdir@/src/GProp/GProp_CelGProps.cxx \
@top_srcdir@/src/GProp/GProp_GProps.cxx \
@top_srcdir@/src/GProp/GProp_PEquation.cxx \
@top_srcdir@/src/GProp/GProp_PGProps.cxx \
@top_srcdir@/src/GProp/GProp_PrincipalProps.cxx \
@top_srcdir@/src/GProp/GProp_SelGProps.cxx \
@top_srcdir@/src/GProp/GProp_VelGProps.cxx \
@top_srcdir@/src/Geom2d/Geom2d_AxisPlacement.cxx \
@top_srcdir@/src/Geom2d/Geom2d_BSplineCurve.cxx \
@top_srcdir@/src/Geom2d/Geom2d_BSplineCurve_1.cxx \
@top_srcdir@/src/Geom2d/Geom2d_BezierCurve.cxx \
@top_srcdir@/src/Geom2d/Geom2d_BoundedCurve.cxx \
@top_srcdir@/src/Geom2d/Geom2d_CartesianPoint.cxx \
@top_srcdir@/src/Geom2d/Geom2d_Circle.cxx \
@top_srcdir@/src/Geom2d/Geom2d_Conic.cxx \
@top_srcdir@/src/Geom2d/Geom2d_Curve.cxx \
@top_srcdir@/src/Geom2d/Geom2d_Direction.cxx \
@top_srcdir@/src/Geom2d/Geom2d_Ellipse.cxx \
@top_srcdir@/src/Geom2d/Geom2d_Geometry.cxx \
@top_srcdir@/src/Geom2d/Geom2d_Hyperbola.cxx \
@top_srcdir@/src/Geom2d/Geom2d_Line.cxx \
@top_srcdir@/src/Geom2d/Geom2d_OffsetCurve.cxx \
@top_srcdir@/src/Geom2d/Geom2d_Parabola.cxx \
@top_srcdir@/src/Geom2d/Geom2d_Point.cxx \
@top_srcdir@/src/Geom2d/Geom2d_Transformation.cxx \
@top_srcdir@/src/Geom2d/Geom2d_TrimmedCurve.cxx \
@top_srcdir@/src/Geom2d/Geom2d_Vector.cxx \
@top_srcdir@/src/Geom2d/Geom2d_VectorWithMagnitude.cxx \
@top_srcdir@/src/Geom2dAdaptor/Geom2dAdaptor.cxx \
@top_srcdir@/src/Geom2dAdaptor/Geom2dAdaptor_Curve.cxx \
@top_srcdir@/src/Geom2dAdaptor/Geom2dAdaptor_HCurve.cxx \
@top_srcdir@/src/Geom2dLProp/Geom2dLProp_CurAndInf2d.cxx \
@top_srcdir@/src/Geom2dLProp/Geom2dLProp_Curve2dTool.cxx \
@top_srcdir@/src/LProp/LProp_AnalyticCurInf.cxx \
@top_srcdir@/src/LProp/LProp_CurAndInf.cxx \
@top_srcdir@/src/TopAbs/TopAbs.cxx

