# Makefile.am for Open Cascade toolkit TKShapeSchema
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/ShapeSchema : @top_srcdir@/src/ShapeSchema: \
@top_srcdir@/drv/PCDMShape : @top_srcdir@/src/PCDMShape


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/ShapeSchema -I@top_srcdir@/src/ShapeSchema \
-I@top_srcdir@/drv/PCDMShape -I@top_srcdir@/src/PCDMShape


lib_LTLIBRARIES=libTKShapeSchema.la

libTKShapeSchema_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKernel/libTKernel.la \
../TKG2d/libTKG2d.la \
../PTKernel/libPTKernel.la \
../TKMath/libTKMath.la \
../TKCDF/libTKCDF.la \
../TKPShape/libTKPShape.la \
$(STLPort_LIB) 

libTKShapeSchema_la_SOURCES = \
@top_srcdir@/drv/ShapeSchema/ShapeSchema.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_DBC_VArrayOfCharacter.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_DBC_VArrayOfExtCharacter.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_ObjMgt_ExternRef.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_ObjMgt_ExternShareable.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_ObjMgt_PSeqOfExtRef.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_ObjMgt_SeqNodeOfPSeqOfExtRef.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_Curve3D.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_CurveOn2Surfaces.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_CurveOnClosedSurface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_CurveOnSurface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_CurveRepresentation.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_GCurve.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_PointOnCurve.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_PointOnCurveOnSurface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_PointOnSurface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_PointRepresentation.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_PointsOnSurface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_Polygon3D.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_PolygonOnClosedSurface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_PolygonOnClosedTriangulation.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_PolygonOnSurface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_PolygonOnTriangulation.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_TEdge.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_TEdge1.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_TFace.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_TFace1.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_TVertex.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PBRep_TVertex1.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PCDMShape_Document.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PCDM_Document.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColStd_FieldOfHArray1OfInteger.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColStd_FieldOfHArray1OfReal.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColStd_FieldOfHArray2OfReal.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColStd_HArray1OfInteger.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColStd_HArray1OfReal.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColStd_HArray2OfReal.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfCirc2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfDir.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfDir2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfLin2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfPnt.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfPnt2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfVec.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfVec2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfXY.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfXYZ.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfCirc2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfDir.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfDir2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfLin2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfPnt.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfPnt2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfVec.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfVec2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfXY.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfXYZ.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfCirc2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfDir.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfDir2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfLin2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfPnt.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfPnt2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfVec.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfVec2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfXY.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfXYZ.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfCirc2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfDir.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfDir2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfLin2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfPnt.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfPnt2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfVec.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfVec2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfXY.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfXYZ.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HSequenceOfDir.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HSequenceOfPnt.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HSequenceOfVec.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_HSequenceOfXYZ.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_SeqNodeOfHSequenceOfDir.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_SeqNodeOfHSequenceOfPnt.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_SeqNodeOfHSequenceOfVec.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PColgp_SeqNodeOfHSequenceOfXYZ.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PCollection_HAsciiString.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PCollection_HExtendedString.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_AxisPlacement.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_BSplineCurve.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_BezierCurve.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_BoundedCurve.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_CartesianPoint.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_Circle.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_Conic.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_Curve.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_Direction.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_Ellipse.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_Geometry.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_Hyperbola.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_Line.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_OffsetCurve.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_Parabola.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_Point.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_Transformation.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_TrimmedCurve.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_Vector.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom2d_VectorWithMagnitude.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_Axis1Placement.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_Axis2Placement.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_AxisPlacement.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_BSplineCurve.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_BSplineSurface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_BezierCurve.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_BezierSurface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_BoundedCurve.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_BoundedSurface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_CartesianPoint.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_Circle.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_Conic.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_ConicalSurface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_Curve.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_CylindricalSurface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_Direction.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_ElementarySurface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_Ellipse.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_Geometry.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_Hyperbola.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_Line.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_OffsetCurve.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_OffsetSurface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_Parabola.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_Plane.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_Point.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_RectangularTrimmedSurface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_SphericalSurface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_Surface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_SurfaceOfLinearExtrusion.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_SurfaceOfRevolution.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_SweptSurface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_ToroidalSurface.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_Transformation.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_TrimmedCurve.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_Vector.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PGeom_VectorWithMagnitude.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PMMgt_PManaged.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PPoly_FieldOfHArray1OfTriangle.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PPoly_HArray1OfTriangle.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PPoly_Polygon2D.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PPoly_Polygon3D.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PPoly_PolygonOnTriangulation.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PPoly_Triangle.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PPoly_Triangulation.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopLoc_Datum3D.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopLoc_ItemLocation.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopLoc_Location.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_CompSolid.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_Compound.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_Edge.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_Face.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_FieldOfHArray1OfHShape.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_FieldOfHArray1OfShape1.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_HArray1OfHShape.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_HArray1OfShape1.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_HShape.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_Shape1.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_Shell.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_Solid.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_TCompSolid.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_TCompSolid1.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_TCompound.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_TCompound1.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_TEdge.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_TEdge1.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_TFace.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_TFace1.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_TShape.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_TShape1.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_TShell.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_TShell1.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_TSolid.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_TSolid1.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_TVertex.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_TVertex1.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_TWire.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_TWire1.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_Vertex.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_PTopoDS_Wire.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_Standard_Persistent.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_Standard_Storable.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_Ax1.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_Ax2.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_Ax22d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_Ax2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_Ax3.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_Circ2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_Dir.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_Dir2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_Lin2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_Mat.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_Mat2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_Pnt.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_Pnt2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_Trsf.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_Trsf2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_Vec.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_Vec2d.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_XY.cxx \
@top_srcdir@/drv/ShapeSchema/ShapeSchema_gp_XYZ.cxx \
@top_srcdir@/src/PCDMShape/PCDMShape_Document.cxx

