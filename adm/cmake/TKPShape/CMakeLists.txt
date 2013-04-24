project(TKPShape)

if (WIN32)
  list( APPEND TKPShape_PRECOMPILED_DEFS "-D__PBRep_DLL" )
  list( APPEND TKPShape_PRECOMPILED_DEFS "-D__PTopoDS_DLL" )
  list( APPEND TKPShape_PRECOMPILED_DEFS "-D__PGeom_DLL" )
  list( APPEND TKPShape_PRECOMPILED_DEFS "-D__PGeom2d_DLL" )
  list( APPEND TKPShape_PRECOMPILED_DEFS "-D__PPoly_DLL" )
  list( APPEND TKPShape_PRECOMPILED_DEFS "-D__PColgp_DLL" )
  list( APPEND TKPShape_PRECOMPILED_DEFS "-D__PTopLoc_DLL" )
  list( APPEND TKPShape_PRECOMPILED_DEFS "-D__PColPGeom_DLL" )
  list( APPEND TKPShape_PRECOMPILED_DEFS "-D__PColPGeom2d_DLL" )
  list( APPEND TKPShape_PRECOMPILED_DEFS "-D__MgtBRep_DLL" )
  list( APPEND TKPShape_PRECOMPILED_DEFS "-D__MgtGeom_DLL" )
  list( APPEND TKPShape_PRECOMPILED_DEFS "-D__MgtGeom2d_DLL" )
  list( APPEND TKPShape_PRECOMPILED_DEFS "-D__MgtPoly_DLL" )
  list( APPEND TKPShape_PRECOMPILED_DEFS "-D__MgtTopLoc_DLL" )
  list( APPEND TKPShape_PRECOMPILED_DEFS "-D__MgtTopoDS_DLL" )
  string( REGEX REPLACE ";" " " TKPShape_PRECOMPILED_DEFS "${TKPShape_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKPShape_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../drv/PBRep" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../src/PBRep" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../drv/PTopoDS" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../src/PTopoDS" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../drv/PGeom" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../src/PGeom" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../drv/PGeom2d" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../src/PGeom2d" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../drv/PPoly" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../src/PPoly" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../drv/PColgp" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../src/PColgp" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../drv/PTopLoc" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../src/PTopLoc" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../drv/PColPGeom" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../src/PColPGeom" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../drv/PColPGeom2d" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../src/PColPGeom2d" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../drv/MgtBRep" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../src/MgtBRep" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../drv/MgtGeom" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../src/MgtGeom" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../drv/MgtGeom2d" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../src/MgtGeom2d" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../drv/MgtPoly" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../src/MgtPoly" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../drv/MgtTopLoc" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../src/MgtTopLoc" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../drv/MgtTopoDS" )
  list( APPEND TKPShape_COMPILER_DIRECTORIES "../../../src/MgtTopoDS" )

if (WIN32)
else()
endif()

  list( APPEND TKPShape_USED_LIBS TKMath )
  list( APPEND TKPShape_USED_LIBS TKernel )
  list( APPEND TKPShape_USED_LIBS TKG2d )
  list( APPEND TKPShape_USED_LIBS TKG3d )
  list( APPEND TKPShape_USED_LIBS PTKernel )
  list( APPEND TKPShape_USED_LIBS TKBRep )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_Curve3D.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_Curve3D.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_CurveOn2Surfaces.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_CurveOn2Surfaces.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_CurveOnClosedSurface.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_CurveOnClosedSurface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_CurveOnSurface.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_CurveOnSurface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_CurveRepresentation.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_CurveRepresentation.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_GCurve.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_GCurve.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_PointOnCurve.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_PointOnCurve.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_PointOnCurveOnSurface.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_PointOnCurveOnSurface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_PointOnSurface.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_PointOnSurface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_PointRepresentation.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_PointRepresentation.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_PointsOnSurface.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_PointsOnSurface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_Polygon3D.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_Polygon3D.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_PolygonOnClosedSurface.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_PolygonOnClosedSurface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_PolygonOnClosedTriangulation.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_PolygonOnClosedTriangulation.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_PolygonOnSurface.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_PolygonOnSurface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_PolygonOnTriangulation.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_PolygonOnTriangulation.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_TEdge.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_TEdge.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_TEdge1.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_TEdge1.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_TFace.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_TFace.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_TFace1.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_TFace1.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_TVertex.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_TVertex.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PBRep/PBRep_TVertex1.cxx" )
  SOURCE_GROUP (PBRep FILES "../../../src/PBRep/PBRep_TVertex1.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PTopoDS/PTopoDS_FieldOfHArray1OfHShape_0.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../drv/PTopoDS/PTopoDS_FieldOfHArray1OfHShape_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PTopoDS/PTopoDS_FieldOfHArray1OfShape1_0.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../drv/PTopoDS/PTopoDS_FieldOfHArray1OfShape1_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PTopoDS/PTopoDS_HArray1OfHShape_0.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../drv/PTopoDS/PTopoDS_HArray1OfHShape_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PTopoDS/PTopoDS_HArray1OfShape1_0.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../drv/PTopoDS/PTopoDS_HArray1OfShape1_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PTopoDS/PTopoDS_VArrayNodeOfFieldOfHArray1OfHShape_0.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../drv/PTopoDS/PTopoDS_VArrayNodeOfFieldOfHArray1OfHShape_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PTopoDS/PTopoDS_VArrayNodeOfFieldOfHArray1OfShape1_0.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../drv/PTopoDS/PTopoDS_VArrayNodeOfFieldOfHArray1OfShape1_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PTopoDS/PTopoDS_VArrayTNodeOfFieldOfHArray1OfHShape_0.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../drv/PTopoDS/PTopoDS_VArrayTNodeOfFieldOfHArray1OfHShape_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PTopoDS/PTopoDS_VArrayTNodeOfFieldOfHArray1OfShape1_0.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../drv/PTopoDS/PTopoDS_VArrayTNodeOfFieldOfHArray1OfShape1_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_CompSolid.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_CompSolid.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_Compound.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_Compound.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_Edge.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_Edge.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_Face.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_Face.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_HShape.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_HShape.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_Shape1.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_Shape1.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_Shell.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_Shell.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_Solid.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_Solid.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_TCompSolid.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_TCompSolid.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_TCompSolid1.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_TCompSolid1.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_TCompound.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_TCompound.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_TCompound1.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_TCompound1.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_TEdge.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_TEdge.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_TEdge1.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_TEdge1.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_TFace.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_TFace.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_TFace1.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_TFace1.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_TShape.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_TShape.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_TShape1.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_TShape1.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_TShell.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_TShell.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_TShell1.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_TShell1.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_TSolid.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_TSolid.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_TSolid1.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_TSolid1.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_TVertex.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_TVertex.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_TVertex1.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_TVertex1.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_TWire.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_TWire.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_TWire1.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_TWire1.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_Vertex.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_Vertex.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopoDS/PTopoDS_Wire.cxx" )
  SOURCE_GROUP (PTopoDS FILES "../../../src/PTopoDS/PTopoDS_Wire.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_Axis1Placement.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_Axis1Placement.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_Axis2Placement.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_Axis2Placement.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_AxisPlacement.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_AxisPlacement.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_BSplineCurve.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_BSplineCurve.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_BSplineSurface.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_BSplineSurface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_BezierCurve.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_BezierCurve.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_BezierSurface.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_BezierSurface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_BoundedCurve.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_BoundedCurve.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_BoundedSurface.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_BoundedSurface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_CartesianPoint.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_CartesianPoint.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_Circle.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_Circle.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_Conic.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_Conic.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_ConicalSurface.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_ConicalSurface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_Curve.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_Curve.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_CylindricalSurface.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_CylindricalSurface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_Direction.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_Direction.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_ElementarySurface.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_ElementarySurface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_Ellipse.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_Ellipse.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_Geometry.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_Geometry.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_Hyperbola.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_Hyperbola.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_Line.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_Line.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_OffsetCurve.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_OffsetCurve.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_OffsetSurface.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_OffsetSurface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_Parabola.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_Parabola.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_Plane.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_Plane.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_Point.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_Point.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_RectangularTrimmedSurface.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_RectangularTrimmedSurface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_SphericalSurface.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_SphericalSurface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_Surface.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_Surface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_SurfaceOfLinearExtrusion.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_SurfaceOfLinearExtrusion.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_SurfaceOfRevolution.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_SurfaceOfRevolution.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_SweptSurface.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_SweptSurface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_ToroidalSurface.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_ToroidalSurface.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_Transformation.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_Transformation.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_TrimmedCurve.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_TrimmedCurve.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_Vector.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_Vector.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom/PGeom_VectorWithMagnitude.cxx" )
  SOURCE_GROUP (PGeom FILES "../../../src/PGeom/PGeom_VectorWithMagnitude.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_AxisPlacement.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_AxisPlacement.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_BSplineCurve.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_BSplineCurve.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_BezierCurve.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_BezierCurve.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_BoundedCurve.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_BoundedCurve.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_CartesianPoint.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_CartesianPoint.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_Circle.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_Circle.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_Conic.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_Conic.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_Curve.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_Curve.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_Direction.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_Direction.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_Ellipse.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_Ellipse.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_Geometry.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_Geometry.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_Hyperbola.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_Hyperbola.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_Line.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_Line.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_OffsetCurve.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_OffsetCurve.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_Parabola.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_Parabola.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_Point.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_Point.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_Transformation.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_Transformation.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_TrimmedCurve.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_TrimmedCurve.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_Vector.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_Vector.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PGeom2d/PGeom2d_VectorWithMagnitude.cxx" )
  SOURCE_GROUP (PGeom2d FILES "../../../src/PGeom2d/PGeom2d_VectorWithMagnitude.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PPoly/PPoly_FieldOfHArray1OfTriangle_0.cxx" )
  SOURCE_GROUP (PPoly FILES "../../../drv/PPoly/PPoly_FieldOfHArray1OfTriangle_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PPoly/PPoly_HArray1OfTriangle_0.cxx" )
  SOURCE_GROUP (PPoly FILES "../../../drv/PPoly/PPoly_HArray1OfTriangle_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PPoly/PPoly_VArrayNodeOfFieldOfHArray1OfTriangle_0.cxx" )
  SOURCE_GROUP (PPoly FILES "../../../drv/PPoly/PPoly_VArrayNodeOfFieldOfHArray1OfTriangle_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PPoly/PPoly_VArrayTNodeOfFieldOfHArray1OfTriangle_0.cxx" )
  SOURCE_GROUP (PPoly FILES "../../../drv/PPoly/PPoly_VArrayTNodeOfFieldOfHArray1OfTriangle_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PPoly/PPoly_Polygon2D.cxx" )
  SOURCE_GROUP (PPoly FILES "../../../src/PPoly/PPoly_Polygon2D.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PPoly/PPoly_Polygon3D.cxx" )
  SOURCE_GROUP (PPoly FILES "../../../src/PPoly/PPoly_Polygon3D.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PPoly/PPoly_PolygonOnTriangulation.cxx" )
  SOURCE_GROUP (PPoly FILES "../../../src/PPoly/PPoly_PolygonOnTriangulation.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PPoly/PPoly_Triangle.cxx" )
  SOURCE_GROUP (PPoly FILES "../../../src/PPoly/PPoly_Triangle.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PPoly/PPoly_Triangulation.cxx" )
  SOURCE_GROUP (PPoly FILES "../../../src/PPoly/PPoly_Triangulation.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfCirc2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfCirc2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfDir2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfDir2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfDir_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfDir_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfLin2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfLin2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfPnt2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfPnt2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfPnt_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfPnt_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfVec2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfVec2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfVec_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfVec_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfXYZ_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfXYZ_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfXY_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray1OfXY_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfCirc2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfCirc2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfDir2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfDir2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfDir_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfDir_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfLin2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfLin2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfPnt2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfPnt2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfPnt_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfPnt_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfVec2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfVec2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfVec_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfVec_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfXYZ_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfXYZ_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfXY_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_FieldOfHArray2OfXY_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray1OfCirc2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray1OfCirc2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray1OfDir2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray1OfDir2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray1OfDir_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray1OfDir_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray1OfLin2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray1OfLin2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray1OfPnt2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray1OfPnt2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray1OfPnt_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray1OfPnt_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray1OfVec2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray1OfVec2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray1OfVec_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray1OfVec_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray1OfXYZ_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray1OfXYZ_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray1OfXY_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray1OfXY_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray2OfCirc2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray2OfCirc2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray2OfDir2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray2OfDir2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray2OfDir_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray2OfDir_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray2OfLin2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray2OfLin2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray2OfPnt2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray2OfPnt2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray2OfPnt_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray2OfPnt_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray2OfVec2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray2OfVec2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray2OfVec_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray2OfVec_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray2OfXYZ_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray2OfXYZ_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HArray2OfXY_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HArray2OfXY_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HSequenceOfDir_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HSequenceOfDir_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HSequenceOfPnt_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HSequenceOfPnt_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HSequenceOfVec_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HSequenceOfVec_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_HSequenceOfXYZ_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_HSequenceOfXYZ_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_SeqExplorerOfHSequenceOfDir_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_SeqExplorerOfHSequenceOfDir_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_SeqExplorerOfHSequenceOfPnt_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_SeqExplorerOfHSequenceOfPnt_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_SeqExplorerOfHSequenceOfVec_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_SeqExplorerOfHSequenceOfVec_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_SeqExplorerOfHSequenceOfXYZ_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_SeqExplorerOfHSequenceOfXYZ_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_SeqNodeOfHSequenceOfDir_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_SeqNodeOfHSequenceOfDir_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_SeqNodeOfHSequenceOfPnt_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_SeqNodeOfHSequenceOfPnt_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_SeqNodeOfHSequenceOfVec_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_SeqNodeOfHSequenceOfVec_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_SeqNodeOfHSequenceOfXYZ_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_SeqNodeOfHSequenceOfXYZ_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfCirc2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfCirc2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfDir2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfDir2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfDir_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfDir_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfLin2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfLin2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfPnt2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfPnt2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfPnt_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfPnt_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfVec2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfVec2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfVec_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfVec_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfXYZ_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfXYZ_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfXY_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfXY_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfCirc2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfCirc2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfDir2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfDir2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfDir_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfDir_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfLin2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfLin2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfPnt2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfPnt2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfPnt_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfPnt_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfVec2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfVec2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfVec_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfVec_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfXYZ_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfXYZ_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfXY_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfXY_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfCirc2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfCirc2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfDir2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfDir2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfDir_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfDir_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfLin2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfLin2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfPnt2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfPnt2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfPnt_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfPnt_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfVec2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfVec2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfVec_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfVec_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfXYZ_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfXYZ_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfXY_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfXY_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfCirc2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfCirc2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfDir2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfDir2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfDir_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfDir_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfLin2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfLin2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfPnt2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfPnt2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfPnt_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfPnt_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfVec2d_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfVec2d_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfVec_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfVec_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfXYZ_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfXYZ_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfXY_0.cxx" )
  SOURCE_GROUP (PColgp FILES "../../../drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfXY_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopLoc/PTopLoc_Datum3D.cxx" )
  SOURCE_GROUP (PTopLoc FILES "../../../src/PTopLoc/PTopLoc_Datum3D.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopLoc/PTopLoc_ItemLocation.cxx" )
  SOURCE_GROUP (PTopLoc FILES "../../../src/PTopLoc/PTopLoc_ItemLocation.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/PTopLoc/PTopLoc_Location.cxx" )
  SOURCE_GROUP (PTopLoc FILES "../../../src/PTopLoc/PTopLoc_Location.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray1OfBSplineCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray1OfBSplineCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray1OfBezierCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray1OfBezierCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray1OfBoundedCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray1OfBoundedCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray1OfBoundedSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray1OfBoundedSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray1OfCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray1OfCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray1OfSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray1OfSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray2OfBSplineSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray2OfBSplineSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray2OfBezierSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray2OfBezierSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray2OfBoundedSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray2OfBoundedSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray2OfSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_FieldOfHArray2OfSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_HArray1OfBSplineCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_HArray1OfBSplineCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_HArray1OfBezierCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_HArray1OfBezierCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_HArray1OfBoundedCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_HArray1OfBoundedCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_HArray1OfBoundedSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_HArray1OfBoundedSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_HArray1OfCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_HArray1OfCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_HArray1OfSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_HArray1OfSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_HArray2OfBSplineSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_HArray2OfBSplineSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_HArray2OfBezierSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_HArray2OfBezierSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_HArray2OfBoundedSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_HArray2OfBoundedSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_HArray2OfSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_HArray2OfSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray1OfBSplineCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray1OfBSplineCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray1OfBezierCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray1OfBezierCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray1OfBoundedCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray1OfBoundedCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray1OfBoundedSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray1OfBoundedSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray1OfCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray1OfCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray1OfSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray1OfSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray2OfBSplineSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray2OfBSplineSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray2OfBezierSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray2OfBezierSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray2OfBoundedSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray2OfBoundedSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray2OfSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray2OfSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray1OfBSplineCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray1OfBSplineCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray1OfBezierCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray1OfBezierCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray1OfBoundedCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray1OfBoundedCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray1OfBoundedSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray1OfBoundedSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray1OfCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray1OfCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray1OfSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray1OfSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray2OfBSplineSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray2OfBSplineSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray2OfBezierSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray2OfBezierSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray2OfBoundedSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray2OfBoundedSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray2OfSurface_0.cxx" )
  SOURCE_GROUP (PColPGeom FILES "../../../drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray2OfSurface_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom2d/PColPGeom2d_FieldOfHArray1OfBSplineCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom2d FILES "../../../drv/PColPGeom2d/PColPGeom2d_FieldOfHArray1OfBSplineCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom2d/PColPGeom2d_FieldOfHArray1OfBezierCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom2d FILES "../../../drv/PColPGeom2d/PColPGeom2d_FieldOfHArray1OfBezierCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom2d/PColPGeom2d_FieldOfHArray1OfBoundedCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom2d FILES "../../../drv/PColPGeom2d/PColPGeom2d_FieldOfHArray1OfBoundedCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom2d/PColPGeom2d_FieldOfHArray1OfCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom2d FILES "../../../drv/PColPGeom2d/PColPGeom2d_FieldOfHArray1OfCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom2d/PColPGeom2d_HArray1OfBSplineCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom2d FILES "../../../drv/PColPGeom2d/PColPGeom2d_HArray1OfBSplineCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom2d/PColPGeom2d_HArray1OfBezierCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom2d FILES "../../../drv/PColPGeom2d/PColPGeom2d_HArray1OfBezierCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom2d/PColPGeom2d_HArray1OfBoundedCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom2d FILES "../../../drv/PColPGeom2d/PColPGeom2d_HArray1OfBoundedCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom2d/PColPGeom2d_HArray1OfCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom2d FILES "../../../drv/PColPGeom2d/PColPGeom2d_HArray1OfCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom2d/PColPGeom2d_VArrayNodeOfFieldOfHArray1OfBSplineCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom2d FILES "../../../drv/PColPGeom2d/PColPGeom2d_VArrayNodeOfFieldOfHArray1OfBSplineCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom2d/PColPGeom2d_VArrayNodeOfFieldOfHArray1OfBezierCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom2d FILES "../../../drv/PColPGeom2d/PColPGeom2d_VArrayNodeOfFieldOfHArray1OfBezierCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom2d/PColPGeom2d_VArrayNodeOfFieldOfHArray1OfBoundedCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom2d FILES "../../../drv/PColPGeom2d/PColPGeom2d_VArrayNodeOfFieldOfHArray1OfBoundedCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom2d/PColPGeom2d_VArrayNodeOfFieldOfHArray1OfCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom2d FILES "../../../drv/PColPGeom2d/PColPGeom2d_VArrayNodeOfFieldOfHArray1OfCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom2d/PColPGeom2d_VArrayTNodeOfFieldOfHArray1OfBSplineCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom2d FILES "../../../drv/PColPGeom2d/PColPGeom2d_VArrayTNodeOfFieldOfHArray1OfBSplineCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom2d/PColPGeom2d_VArrayTNodeOfFieldOfHArray1OfBezierCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom2d FILES "../../../drv/PColPGeom2d/PColPGeom2d_VArrayTNodeOfFieldOfHArray1OfBezierCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom2d/PColPGeom2d_VArrayTNodeOfFieldOfHArray1OfBoundedCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom2d FILES "../../../drv/PColPGeom2d/PColPGeom2d_VArrayTNodeOfFieldOfHArray1OfBoundedCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../drv/PColPGeom2d/PColPGeom2d_VArrayTNodeOfFieldOfHArray1OfCurve_0.cxx" )
  SOURCE_GROUP (PColPGeom2d FILES "../../../drv/PColPGeom2d/PColPGeom2d_VArrayTNodeOfFieldOfHArray1OfCurve_0.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/MgtBRep/MgtBRep.cxx" )
  SOURCE_GROUP (MgtBRep FILES "../../../src/MgtBRep/MgtBRep.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/MgtBRep/MgtBRep_TranslateTool.cxx" )
  SOURCE_GROUP (MgtBRep FILES "../../../src/MgtBRep/MgtBRep_TranslateTool.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/MgtBRep/MgtBRep_TranslateTool1.cxx" )
  SOURCE_GROUP (MgtBRep FILES "../../../src/MgtBRep/MgtBRep_TranslateTool1.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/MgtGeom/MgtGeom.cxx" )
  SOURCE_GROUP (MgtGeom FILES "../../../src/MgtGeom/MgtGeom.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/MgtGeom2d/MgtGeom2d.cxx" )
  SOURCE_GROUP (MgtGeom2d FILES "../../../src/MgtGeom2d/MgtGeom2d.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/MgtPoly/MgtPoly.cxx" )
  SOURCE_GROUP (MgtPoly FILES "../../../src/MgtPoly/MgtPoly.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/MgtTopLoc/MgtTopLoc.cxx" )
  SOURCE_GROUP (MgtTopLoc FILES "../../../src/MgtTopLoc/MgtTopLoc.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/MgtTopoDS/MgtTopoDS.cxx" )
  SOURCE_GROUP (MgtTopoDS FILES "../../../src/MgtTopoDS/MgtTopoDS.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/MgtTopoDS/MgtTopoDS_TranslateTool.cxx" )
  SOURCE_GROUP (MgtTopoDS FILES "../../../src/MgtTopoDS/MgtTopoDS_TranslateTool.cxx")

  list( APPEND TKPShape_USED_SRCFILES "../../../src/MgtTopoDS/MgtTopoDS_TranslateTool1.cxx" )
  SOURCE_GROUP (MgtTopoDS FILES "../../../src/MgtTopoDS/MgtTopoDS_TranslateTool1.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKPShape)
 add_library( TKPShape SHARED ${TKPShape_USED_SRCFILES} )

 set_property(TARGET TKPShape PROPERTY FOLDER ApplicationFramework)

 install( TARGETS TKPShape
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKPShape.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKPShape PROPERTIES COMPILE_FLAGS "${TKPShape_PRECOMPILED_DEFS}" )
 include_directories( ${TKPShape_COMPILER_DIRECTORIES} )
 target_link_libraries( TKPShape ${TKPShape_USED_LIBS} )
endif()
