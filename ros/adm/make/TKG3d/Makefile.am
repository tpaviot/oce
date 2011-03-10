# Makefile.am for Open Cascade toolkit TKG3d
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/Geom : @top_srcdir@/src/Geom: \
@top_srcdir@/drv/TColGeom : @top_srcdir@/src/TColGeom: \
@top_srcdir@/drv/GeomAdaptor : @top_srcdir@/src/GeomAdaptor: \
@top_srcdir@/drv/AdvApprox : @top_srcdir@/src/AdvApprox: \
@top_srcdir@/drv/GeomLProp : @top_srcdir@/src/GeomLProp: \
@top_srcdir@/drv/Adaptor3d : @top_srcdir@/src/Adaptor3d: \
@top_srcdir@/drv/LProp3d : @top_srcdir@/src/LProp3d


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/Geom -I@top_srcdir@/src/Geom \
-I@top_srcdir@/drv/TColGeom -I@top_srcdir@/src/TColGeom \
-I@top_srcdir@/drv/GeomAdaptor -I@top_srcdir@/src/GeomAdaptor \
-I@top_srcdir@/drv/AdvApprox -I@top_srcdir@/src/AdvApprox \
-I@top_srcdir@/drv/GeomLProp -I@top_srcdir@/src/GeomLProp \
-I@top_srcdir@/drv/Adaptor3d -I@top_srcdir@/src/Adaptor3d \
-I@top_srcdir@/drv/LProp3d -I@top_srcdir@/src/LProp3d


lib_LTLIBRARIES=libTKG3d.la

libTKG3d_la_LIBADD = \
../TKMath/libTKMath.la \
../TKernel/libTKernel.la \
../TKG2d/libTKG2d.la \
$(STLPort_LIB) 

libTKG3d_la_SOURCES = \
@top_srcdir@/drv/Adaptor3d/Adaptor3d_HCurveOnSurface_0.cxx \
@top_srcdir@/drv/Adaptor3d/Adaptor3d_HIsoCurve_0.cxx \
@top_srcdir@/drv/Adaptor3d/Adaptor3d_HOffsetCurve_0.cxx \
@top_srcdir@/drv/Adaptor3d/Adaptor3d_HSurfaceOfLinearExtrusion_0.cxx \
@top_srcdir@/drv/Adaptor3d/Adaptor3d_HSurfaceOfRevolution_0.cxx \
@top_srcdir@/drv/Geom/Geom_HSequenceOfBSplineSurface_0.cxx \
@top_srcdir@/drv/Geom/Geom_HSequenceOfSurface_0.cxx \
@top_srcdir@/drv/Geom/Geom_SequenceNodeOfSequenceOfBSplineSurface_0.cxx \
@top_srcdir@/drv/Geom/Geom_SequenceNodeOfSequenceOfSurface_0.cxx \
@top_srcdir@/drv/Geom/Geom_SequenceOfBSplineSurface_0.cxx \
@top_srcdir@/drv/Geom/Geom_SequenceOfSurface_0.cxx \
@top_srcdir@/drv/Geom/Geom_UndefinedDerivative_0.cxx \
@top_srcdir@/drv/Geom/Geom_UndefinedValue_0.cxx \
@top_srcdir@/drv/GeomAdaptor/GeomAdaptor_GHCurve_0.cxx \
@top_srcdir@/drv/GeomAdaptor/GeomAdaptor_GHSurface_0.cxx \
@top_srcdir@/drv/GeomLProp/GeomLProp_CLProps_0.cxx \
@top_srcdir@/drv/GeomLProp/GeomLProp_SLProps_0.cxx \
@top_srcdir@/drv/LProp3d/LProp3d_CLProps_0.cxx \
@top_srcdir@/drv/LProp3d/LProp3d_SLProps_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_Array1OfBSplineCurve_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_Array1OfBezierCurve_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_Array1OfBoundedCurve_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_Array1OfBoundedSurface_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_Array1OfCurve_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_Array1OfSurface_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_Array2OfBSplineSurface_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_Array2OfBezierSurface_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_Array2OfBoundedSurface_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_Array2OfSurface_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_HArray1OfBSplineCurve_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_HArray1OfBezierCurve_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_HArray1OfBoundedCurve_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_HArray1OfBoundedSurface_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_HArray1OfCurve_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_HArray1OfSurface_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_HArray2OfBSplineSurface_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_HArray2OfBezierSurface_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_HArray2OfBoundedSurface_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_HArray2OfSurface_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_HSequenceOfBoundedCurve_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_HSequenceOfBoundedSurface_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_HSequenceOfCurve_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_HSequenceOfSurface_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_SequenceNodeOfSequenceOfBoundedCurve_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_SequenceNodeOfSequenceOfBoundedSurface_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_SequenceNodeOfSequenceOfCurve_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_SequenceNodeOfSequenceOfSurface_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_SequenceOfBoundedCurve_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_SequenceOfBoundedSurface_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_SequenceOfCurve_0.cxx \
@top_srcdir@/drv/TColGeom/TColGeom_SequenceOfSurface_0.cxx \
@top_srcdir@/src/Adaptor3d/Adaptor3d_Curve.cxx \
@top_srcdir@/src/Adaptor3d/Adaptor3d_CurveOnSurface.cxx \
@top_srcdir@/src/Adaptor3d/Adaptor3d_HCurve.cxx \
@top_srcdir@/src/Adaptor3d/Adaptor3d_HSurface.cxx \
@top_srcdir@/src/Adaptor3d/Adaptor3d_HSurfaceTool.cxx \
@top_srcdir@/src/Adaptor3d/Adaptor3d_HVertex.cxx \
@top_srcdir@/src/Adaptor3d/Adaptor3d_InterFunc.cxx \
@top_srcdir@/src/Adaptor3d/Adaptor3d_IsoCurve.cxx \
@top_srcdir@/src/Adaptor3d/Adaptor3d_OffsetCurve.cxx \
@top_srcdir@/src/Adaptor3d/Adaptor3d_Surface.cxx \
@top_srcdir@/src/Adaptor3d/Adaptor3d_SurfaceOfLinearExtrusion.cxx \
@top_srcdir@/src/Adaptor3d/Adaptor3d_SurfaceOfRevolution.cxx \
@top_srcdir@/src/Adaptor3d/Adaptor3d_TopolTool.cxx \
@top_srcdir@/src/AdvApprox/AdvApprox_ApproxAFunction.cxx \
@top_srcdir@/src/AdvApprox/AdvApprox_Cutting.cxx \
@top_srcdir@/src/AdvApprox/AdvApprox_DichoCutting.cxx \
@top_srcdir@/src/AdvApprox/AdvApprox_PrefAndRec.cxx \
@top_srcdir@/src/AdvApprox/AdvApprox_PrefCutting.cxx \
@top_srcdir@/src/AdvApprox/AdvApprox_SimpleApprox.cxx \
@top_srcdir@/src/Geom/Geom_Axis1Placement.cxx \
@top_srcdir@/src/Geom/Geom_Axis2Placement.cxx \
@top_srcdir@/src/Geom/Geom_AxisPlacement.cxx \
@top_srcdir@/src/Geom/Geom_BSplineCurve.cxx \
@top_srcdir@/src/Geom/Geom_BSplineCurve_1.cxx \
@top_srcdir@/src/Geom/Geom_BSplineSurface.cxx \
@top_srcdir@/src/Geom/Geom_BSplineSurface_1.cxx \
@top_srcdir@/src/Geom/Geom_BezierCurve.cxx \
@top_srcdir@/src/Geom/Geom_BezierSurface.cxx \
@top_srcdir@/src/Geom/Geom_BoundedCurve.cxx \
@top_srcdir@/src/Geom/Geom_BoundedSurface.cxx \
@top_srcdir@/src/Geom/Geom_CartesianPoint.cxx \
@top_srcdir@/src/Geom/Geom_Circle.cxx \
@top_srcdir@/src/Geom/Geom_Conic.cxx \
@top_srcdir@/src/Geom/Geom_ConicalSurface.cxx \
@top_srcdir@/src/Geom/Geom_Curve.cxx \
@top_srcdir@/src/Geom/Geom_CylindricalSurface.cxx \
@top_srcdir@/src/Geom/Geom_Direction.cxx \
@top_srcdir@/src/Geom/Geom_ElementarySurface.cxx \
@top_srcdir@/src/Geom/Geom_Ellipse.cxx \
@top_srcdir@/src/Geom/Geom_Geometry.cxx \
@top_srcdir@/src/Geom/Geom_Hyperbola.cxx \
@top_srcdir@/src/Geom/Geom_Line.cxx \
@top_srcdir@/src/Geom/Geom_OffsetCurve.cxx \
@top_srcdir@/src/Geom/Geom_OffsetSurface.cxx \
@top_srcdir@/src/Geom/Geom_OsculatingSurface.cxx \
@top_srcdir@/src/Geom/Geom_Parabola.cxx \
@top_srcdir@/src/Geom/Geom_Plane.cxx \
@top_srcdir@/src/Geom/Geom_Point.cxx \
@top_srcdir@/src/Geom/Geom_RectangularTrimmedSurface.cxx \
@top_srcdir@/src/Geom/Geom_SphericalSurface.cxx \
@top_srcdir@/src/Geom/Geom_Surface.cxx \
@top_srcdir@/src/Geom/Geom_SurfaceOfLinearExtrusion.cxx \
@top_srcdir@/src/Geom/Geom_SurfaceOfRevolution.cxx \
@top_srcdir@/src/Geom/Geom_SweptSurface.cxx \
@top_srcdir@/src/Geom/Geom_ToroidalSurface.cxx \
@top_srcdir@/src/Geom/Geom_Transformation.cxx \
@top_srcdir@/src/Geom/Geom_TrimmedCurve.cxx \
@top_srcdir@/src/Geom/Geom_Vector.cxx \
@top_srcdir@/src/Geom/Geom_VectorWithMagnitude.cxx \
@top_srcdir@/src/GeomAdaptor/GeomAdaptor.cxx \
@top_srcdir@/src/GeomAdaptor/GeomAdaptor_Curve.cxx \
@top_srcdir@/src/GeomAdaptor/GeomAdaptor_HCurve.cxx \
@top_srcdir@/src/GeomAdaptor/GeomAdaptor_HSurface.cxx \
@top_srcdir@/src/GeomAdaptor/GeomAdaptor_Surface.cxx \
@top_srcdir@/src/GeomLProp/GeomLProp.cxx \
@top_srcdir@/src/GeomLProp/GeomLProp_CurveTool.cxx \
@top_srcdir@/src/GeomLProp/GeomLProp_SurfaceTool.cxx \
@top_srcdir@/src/LProp3d/LProp3d_CurveTool.cxx \
@top_srcdir@/src/LProp3d/LProp3d_SurfaceTool.cxx

