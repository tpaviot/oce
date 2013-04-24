project(TKG3d)

if (WIN32)
  list( APPEND TKG3d_PRECOMPILED_DEFS "-D__Geom_DLL" )
  list( APPEND TKG3d_PRECOMPILED_DEFS "-D__TColGeom_DLL" )
  list( APPEND TKG3d_PRECOMPILED_DEFS "-D__GeomAdaptor_DLL" )
  list( APPEND TKG3d_PRECOMPILED_DEFS "-D__AdvApprox_DLL" )
  list( APPEND TKG3d_PRECOMPILED_DEFS "-D__GeomLProp_DLL" )
  list( APPEND TKG3d_PRECOMPILED_DEFS "-D__Adaptor3d_DLL" )
  list( APPEND TKG3d_PRECOMPILED_DEFS "-D__LProp3d_DLL" )
  list( APPEND TKG3d_PRECOMPILED_DEFS "-D__TopAbs_DLL" )
  string( REGEX REPLACE ";" " " TKG3d_PRECOMPILED_DEFS "${TKG3d_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKG3d_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKG3d_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKG3d_COMPILER_DIRECTORIES "../../../drv/Geom" )
  list( APPEND TKG3d_COMPILER_DIRECTORIES "../../../src/Geom" )
  list( APPEND TKG3d_COMPILER_DIRECTORIES "../../../drv/TColGeom" )
  list( APPEND TKG3d_COMPILER_DIRECTORIES "../../../src/TColGeom" )
  list( APPEND TKG3d_COMPILER_DIRECTORIES "../../../drv/GeomAdaptor" )
  list( APPEND TKG3d_COMPILER_DIRECTORIES "../../../src/GeomAdaptor" )
  list( APPEND TKG3d_COMPILER_DIRECTORIES "../../../drv/AdvApprox" )
  list( APPEND TKG3d_COMPILER_DIRECTORIES "../../../src/AdvApprox" )
  list( APPEND TKG3d_COMPILER_DIRECTORIES "../../../drv/GeomLProp" )
  list( APPEND TKG3d_COMPILER_DIRECTORIES "../../../src/GeomLProp" )
  list( APPEND TKG3d_COMPILER_DIRECTORIES "../../../drv/Adaptor3d" )
  list( APPEND TKG3d_COMPILER_DIRECTORIES "../../../src/Adaptor3d" )
  list( APPEND TKG3d_COMPILER_DIRECTORIES "../../../drv/LProp3d" )
  list( APPEND TKG3d_COMPILER_DIRECTORIES "../../../src/LProp3d" )
  list( APPEND TKG3d_COMPILER_DIRECTORIES "../../../drv/TopAbs" )
  list( APPEND TKG3d_COMPILER_DIRECTORIES "../../../src/TopAbs" )

if (WIN32)
else()
endif()

  list( APPEND TKG3d_USED_LIBS TKMath )
  list( APPEND TKG3d_USED_LIBS TKernel )
  list( APPEND TKG3d_USED_LIBS TKG2d )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/Geom/Geom_HSequenceOfBSplineSurface_0.cxx" )
  SOURCE_GROUP (Geom FILES "../../../drv/Geom/Geom_HSequenceOfBSplineSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/Geom/Geom_HSequenceOfSurface_0.cxx" )
  SOURCE_GROUP (Geom FILES "../../../drv/Geom/Geom_HSequenceOfSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/Geom/Geom_SequenceNodeOfSequenceOfBSplineSurface_0.cxx" )
  SOURCE_GROUP (Geom FILES "../../../drv/Geom/Geom_SequenceNodeOfSequenceOfBSplineSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/Geom/Geom_SequenceNodeOfSequenceOfSurface_0.cxx" )
  SOURCE_GROUP (Geom FILES "../../../drv/Geom/Geom_SequenceNodeOfSequenceOfSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/Geom/Geom_SequenceOfBSplineSurface_0.cxx" )
  SOURCE_GROUP (Geom FILES "../../../drv/Geom/Geom_SequenceOfBSplineSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/Geom/Geom_SequenceOfSurface_0.cxx" )
  SOURCE_GROUP (Geom FILES "../../../drv/Geom/Geom_SequenceOfSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/Geom/Geom_UndefinedDerivative_0.cxx" )
  SOURCE_GROUP (Geom FILES "../../../drv/Geom/Geom_UndefinedDerivative_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/Geom/Geom_UndefinedValue_0.cxx" )
  SOURCE_GROUP (Geom FILES "../../../drv/Geom/Geom_UndefinedValue_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_Axis1Placement.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_Axis1Placement.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_Axis2Placement.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_Axis2Placement.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_AxisPlacement.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_AxisPlacement.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_BSplineCurve.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_BSplineCurve.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_BSplineCurve_1.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_BSplineCurve_1.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_BSplineSurface.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_BSplineSurface.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_BSplineSurface_1.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_BSplineSurface_1.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_BezierCurve.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_BezierCurve.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_BezierSurface.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_BezierSurface.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_BoundedCurve.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_BoundedCurve.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_BoundedSurface.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_BoundedSurface.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_CartesianPoint.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_CartesianPoint.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_Circle.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_Circle.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_Conic.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_Conic.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_ConicalSurface.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_ConicalSurface.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_Curve.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_Curve.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_CylindricalSurface.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_CylindricalSurface.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_Direction.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_Direction.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_ElementarySurface.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_ElementarySurface.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_Ellipse.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_Ellipse.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_Geometry.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_Geometry.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_Hyperbola.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_Hyperbola.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_Line.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_Line.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_OffsetCurve.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_OffsetCurve.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_OffsetSurface.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_OffsetSurface.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_OsculatingSurface.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_OsculatingSurface.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_Parabola.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_Parabola.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_Plane.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_Plane.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_Point.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_Point.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_RectangularTrimmedSurface.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_RectangularTrimmedSurface.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_SphericalSurface.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_SphericalSurface.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_Surface.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_Surface.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_SurfaceOfLinearExtrusion.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_SurfaceOfLinearExtrusion.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_SurfaceOfRevolution.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_SurfaceOfRevolution.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_SweptSurface.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_SweptSurface.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_ToroidalSurface.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_ToroidalSurface.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_Transformation.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_Transformation.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_TrimmedCurve.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_TrimmedCurve.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_Vector.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_Vector.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Geom/Geom_VectorWithMagnitude.cxx" )
  SOURCE_GROUP (Geom FILES "../../../src/Geom/Geom_VectorWithMagnitude.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_Array1OfBSplineCurve_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_Array1OfBSplineCurve_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_Array1OfBezierCurve_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_Array1OfBezierCurve_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_Array1OfBoundedCurve_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_Array1OfBoundedCurve_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_Array1OfBoundedSurface_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_Array1OfBoundedSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_Array1OfCurve_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_Array1OfCurve_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_Array1OfSurface_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_Array1OfSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_Array2OfBSplineSurface_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_Array2OfBSplineSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_Array2OfBezierSurface_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_Array2OfBezierSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_Array2OfBoundedSurface_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_Array2OfBoundedSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_Array2OfSurface_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_Array2OfSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_HArray1OfBSplineCurve_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_HArray1OfBSplineCurve_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_HArray1OfBezierCurve_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_HArray1OfBezierCurve_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_HArray1OfBoundedCurve_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_HArray1OfBoundedCurve_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_HArray1OfBoundedSurface_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_HArray1OfBoundedSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_HArray1OfCurve_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_HArray1OfCurve_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_HArray1OfSurface_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_HArray1OfSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_HArray2OfBSplineSurface_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_HArray2OfBSplineSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_HArray2OfBezierSurface_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_HArray2OfBezierSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_HArray2OfBoundedSurface_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_HArray2OfBoundedSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_HArray2OfSurface_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_HArray2OfSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_HSequenceOfBoundedCurve_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_HSequenceOfBoundedCurve_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_HSequenceOfBoundedSurface_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_HSequenceOfBoundedSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_HSequenceOfCurve_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_HSequenceOfCurve_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_HSequenceOfSurface_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_HSequenceOfSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_SequenceNodeOfSequenceOfBoundedCurve_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_SequenceNodeOfSequenceOfBoundedCurve_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_SequenceNodeOfSequenceOfBoundedSurface_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_SequenceNodeOfSequenceOfBoundedSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_SequenceNodeOfSequenceOfCurve_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_SequenceNodeOfSequenceOfCurve_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_SequenceNodeOfSequenceOfSurface_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_SequenceNodeOfSequenceOfSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_SequenceOfBoundedCurve_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_SequenceOfBoundedCurve_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_SequenceOfBoundedSurface_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_SequenceOfBoundedSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_SequenceOfCurve_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_SequenceOfCurve_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/TColGeom/TColGeom_SequenceOfSurface_0.cxx" )
  SOURCE_GROUP (TColGeom FILES "../../../drv/TColGeom/TColGeom_SequenceOfSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/GeomAdaptor/GeomAdaptor_GHCurve_0.cxx" )
  SOURCE_GROUP (GeomAdaptor FILES "../../../drv/GeomAdaptor/GeomAdaptor_GHCurve_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/GeomAdaptor/GeomAdaptor_GHSurface_0.cxx" )
  SOURCE_GROUP (GeomAdaptor FILES "../../../drv/GeomAdaptor/GeomAdaptor_GHSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/GeomAdaptor/GeomAdaptor.cxx" )
  SOURCE_GROUP (GeomAdaptor FILES "../../../src/GeomAdaptor/GeomAdaptor.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/GeomAdaptor/GeomAdaptor_Curve.cxx" )
  SOURCE_GROUP (GeomAdaptor FILES "../../../src/GeomAdaptor/GeomAdaptor_Curve.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/GeomAdaptor/GeomAdaptor_HCurve.cxx" )
  SOURCE_GROUP (GeomAdaptor FILES "../../../src/GeomAdaptor/GeomAdaptor_HCurve.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/GeomAdaptor/GeomAdaptor_HSurface.cxx" )
  SOURCE_GROUP (GeomAdaptor FILES "../../../src/GeomAdaptor/GeomAdaptor_HSurface.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/GeomAdaptor/GeomAdaptor_Surface.cxx" )
  SOURCE_GROUP (GeomAdaptor FILES "../../../src/GeomAdaptor/GeomAdaptor_Surface.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/AdvApprox/AdvApprox_ApproxAFunction.cxx" )
  SOURCE_GROUP (AdvApprox FILES "../../../src/AdvApprox/AdvApprox_ApproxAFunction.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/AdvApprox/AdvApprox_Cutting.cxx" )
  SOURCE_GROUP (AdvApprox FILES "../../../src/AdvApprox/AdvApprox_Cutting.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/AdvApprox/AdvApprox_DichoCutting.cxx" )
  SOURCE_GROUP (AdvApprox FILES "../../../src/AdvApprox/AdvApprox_DichoCutting.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/AdvApprox/AdvApprox_PrefAndRec.cxx" )
  SOURCE_GROUP (AdvApprox FILES "../../../src/AdvApprox/AdvApprox_PrefAndRec.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/AdvApprox/AdvApprox_PrefCutting.cxx" )
  SOURCE_GROUP (AdvApprox FILES "../../../src/AdvApprox/AdvApprox_PrefCutting.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/AdvApprox/AdvApprox_SimpleApprox.cxx" )
  SOURCE_GROUP (AdvApprox FILES "../../../src/AdvApprox/AdvApprox_SimpleApprox.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/GeomLProp/GeomLProp_CLProps_0.cxx" )
  SOURCE_GROUP (GeomLProp FILES "../../../drv/GeomLProp/GeomLProp_CLProps_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/GeomLProp/GeomLProp_SLProps_0.cxx" )
  SOURCE_GROUP (GeomLProp FILES "../../../drv/GeomLProp/GeomLProp_SLProps_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/GeomLProp/GeomLProp.cxx" )
  SOURCE_GROUP (GeomLProp FILES "../../../src/GeomLProp/GeomLProp.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/GeomLProp/GeomLProp_CurveTool.cxx" )
  SOURCE_GROUP (GeomLProp FILES "../../../src/GeomLProp/GeomLProp_CurveTool.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/GeomLProp/GeomLProp_SurfaceTool.cxx" )
  SOURCE_GROUP (GeomLProp FILES "../../../src/GeomLProp/GeomLProp_SurfaceTool.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/Adaptor3d/Adaptor3d_HCurveOnSurface_0.cxx" )
  SOURCE_GROUP (Adaptor3d FILES "../../../drv/Adaptor3d/Adaptor3d_HCurveOnSurface_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/Adaptor3d/Adaptor3d_HIsoCurve_0.cxx" )
  SOURCE_GROUP (Adaptor3d FILES "../../../drv/Adaptor3d/Adaptor3d_HIsoCurve_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/Adaptor3d/Adaptor3d_HOffsetCurve_0.cxx" )
  SOURCE_GROUP (Adaptor3d FILES "../../../drv/Adaptor3d/Adaptor3d_HOffsetCurve_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/Adaptor3d/Adaptor3d_HSurfaceOfLinearExtrusion_0.cxx" )
  SOURCE_GROUP (Adaptor3d FILES "../../../drv/Adaptor3d/Adaptor3d_HSurfaceOfLinearExtrusion_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/Adaptor3d/Adaptor3d_HSurfaceOfRevolution_0.cxx" )
  SOURCE_GROUP (Adaptor3d FILES "../../../drv/Adaptor3d/Adaptor3d_HSurfaceOfRevolution_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Adaptor3d/Adaptor3d_Curve.cxx" )
  SOURCE_GROUP (Adaptor3d FILES "../../../src/Adaptor3d/Adaptor3d_Curve.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Adaptor3d/Adaptor3d_CurveOnSurface.cxx" )
  SOURCE_GROUP (Adaptor3d FILES "../../../src/Adaptor3d/Adaptor3d_CurveOnSurface.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Adaptor3d/Adaptor3d_HCurve.cxx" )
  SOURCE_GROUP (Adaptor3d FILES "../../../src/Adaptor3d/Adaptor3d_HCurve.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Adaptor3d/Adaptor3d_HSurface.cxx" )
  SOURCE_GROUP (Adaptor3d FILES "../../../src/Adaptor3d/Adaptor3d_HSurface.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Adaptor3d/Adaptor3d_HSurfaceTool.cxx" )
  SOURCE_GROUP (Adaptor3d FILES "../../../src/Adaptor3d/Adaptor3d_HSurfaceTool.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Adaptor3d/Adaptor3d_HVertex.cxx" )
  SOURCE_GROUP (Adaptor3d FILES "../../../src/Adaptor3d/Adaptor3d_HVertex.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Adaptor3d/Adaptor3d_InterFunc.cxx" )
  SOURCE_GROUP (Adaptor3d FILES "../../../src/Adaptor3d/Adaptor3d_InterFunc.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Adaptor3d/Adaptor3d_IsoCurve.cxx" )
  SOURCE_GROUP (Adaptor3d FILES "../../../src/Adaptor3d/Adaptor3d_IsoCurve.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Adaptor3d/Adaptor3d_OffsetCurve.cxx" )
  SOURCE_GROUP (Adaptor3d FILES "../../../src/Adaptor3d/Adaptor3d_OffsetCurve.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Adaptor3d/Adaptor3d_Surface.cxx" )
  SOURCE_GROUP (Adaptor3d FILES "../../../src/Adaptor3d/Adaptor3d_Surface.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Adaptor3d/Adaptor3d_SurfaceOfLinearExtrusion.cxx" )
  SOURCE_GROUP (Adaptor3d FILES "../../../src/Adaptor3d/Adaptor3d_SurfaceOfLinearExtrusion.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Adaptor3d/Adaptor3d_SurfaceOfRevolution.cxx" )
  SOURCE_GROUP (Adaptor3d FILES "../../../src/Adaptor3d/Adaptor3d_SurfaceOfRevolution.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/Adaptor3d/Adaptor3d_TopolTool.cxx" )
  SOURCE_GROUP (Adaptor3d FILES "../../../src/Adaptor3d/Adaptor3d_TopolTool.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/LProp3d/LProp3d_CLProps_0.cxx" )
  SOURCE_GROUP (LProp3d FILES "../../../drv/LProp3d/LProp3d_CLProps_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../drv/LProp3d/LProp3d_SLProps_0.cxx" )
  SOURCE_GROUP (LProp3d FILES "../../../drv/LProp3d/LProp3d_SLProps_0.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/LProp3d/LProp3d_CurveTool.cxx" )
  SOURCE_GROUP (LProp3d FILES "../../../src/LProp3d/LProp3d_CurveTool.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/LProp3d/LProp3d_SurfaceTool.cxx" )
  SOURCE_GROUP (LProp3d FILES "../../../src/LProp3d/LProp3d_SurfaceTool.cxx")

  list( APPEND TKG3d_USED_SRCFILES "../../../src/TopAbs/TopAbs.cxx" )
  SOURCE_GROUP (TopAbs FILES "../../../src/TopAbs/TopAbs.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKG3d)
 add_library( TKG3d SHARED ${TKG3d_USED_SRCFILES} )

 set_property(TARGET TKG3d PROPERTY FOLDER ModelingData)

 install( TARGETS TKG3d
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKG3d.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKG3d PROPERTIES COMPILE_FLAGS "${TKG3d_PRECOMPILED_DEFS}" )
 include_directories( ${TKG3d_COMPILER_DIRECTORIES} )
 target_link_libraries( TKG3d ${TKG3d_USED_LIBS} )
endif()
