#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_BaseDriver_HeaderFile
#include <Storage_BaseDriver.hxx>
#endif
#ifndef _Storage_CallBack_HeaderFile
#include <Storage_CallBack.hxx>
#endif
#ifndef _Storage_Macros_HeaderFile
#include <Storage_Macros.hxx>
#endif
class Handle(ObjMgt_ExternShareable);
class Handle(ObjMgt_ExternRef);
class Handle(ObjMgt_PSeqOfExtRef);
class Handle(ObjMgt_SeqNodeOfPSeqOfExtRef);
class Handle(PTopLoc_Datum3D);
class Handle(PTopLoc_ItemLocation);
class PTopLoc_Location;
class Handle(PColgp_HArray1OfCirc2d);
class PColgp_FieldOfHArray1OfCirc2d;
class Handle(PColgp_HArray1OfDir2d);
class PColgp_FieldOfHArray1OfDir2d;
class Handle(PColgp_HArray1OfLin2d);
class PColgp_FieldOfHArray1OfLin2d;
class Handle(PColgp_HArray1OfPnt2d);
class PColgp_FieldOfHArray1OfPnt2d;
class Handle(PColgp_HArray1OfVec2d);
class PColgp_FieldOfHArray1OfVec2d;
class Handle(PColgp_HArray1OfXY);
class PColgp_FieldOfHArray1OfXY;
class Handle(PColgp_HArray1OfDir);
class PColgp_FieldOfHArray1OfDir;
class Handle(PColgp_HArray1OfPnt);
class PColgp_FieldOfHArray1OfPnt;
class Handle(PColgp_HArray1OfVec);
class PColgp_FieldOfHArray1OfVec;
class Handle(PColgp_HArray1OfXYZ);
class PColgp_FieldOfHArray1OfXYZ;
class Handle(PColgp_HArray2OfCirc2d);
class PColgp_FieldOfHArray2OfCirc2d;
class Handle(PColgp_HArray2OfDir2d);
class PColgp_FieldOfHArray2OfDir2d;
class Handle(PColgp_HArray2OfLin2d);
class PColgp_FieldOfHArray2OfLin2d;
class Handle(PColgp_HArray2OfPnt2d);
class PColgp_FieldOfHArray2OfPnt2d;
class Handle(PColgp_HArray2OfVec2d);
class PColgp_FieldOfHArray2OfVec2d;
class Handle(PColgp_HArray2OfXY);
class PColgp_FieldOfHArray2OfXY;
class Handle(PColgp_HArray2OfDir);
class PColgp_FieldOfHArray2OfDir;
class Handle(PColgp_HArray2OfPnt);
class PColgp_FieldOfHArray2OfPnt;
class Handle(PColgp_HArray2OfVec);
class PColgp_FieldOfHArray2OfVec;
class Handle(PColgp_HArray2OfXYZ);
class PColgp_FieldOfHArray2OfXYZ;
class Handle(PColgp_HSequenceOfDir);
class Handle(PColgp_SeqNodeOfHSequenceOfDir);
class Handle(PColgp_HSequenceOfPnt);
class Handle(PColgp_SeqNodeOfHSequenceOfPnt);
class Handle(PColgp_HSequenceOfVec);
class Handle(PColgp_SeqNodeOfHSequenceOfVec);
class Handle(PColgp_HSequenceOfXYZ);
class Handle(PColgp_SeqNodeOfHSequenceOfXYZ);
class Handle(PGeom2d_Transformation);
class Handle(PGeom2d_Geometry);
class Handle(PGeom2d_Point);
class Handle(PGeom2d_CartesianPoint);
class Handle(PGeom2d_Vector);
class Handle(PGeom2d_Direction);
class Handle(PGeom2d_VectorWithMagnitude);
class Handle(PGeom2d_AxisPlacement);
class Handle(PGeom2d_Curve);
class Handle(PGeom2d_Line);
class Handle(PGeom2d_Conic);
class Handle(PGeom2d_Circle);
class Handle(PGeom2d_Ellipse);
class Handle(PGeom2d_Hyperbola);
class Handle(PGeom2d_Parabola);
class Handle(PGeom2d_BoundedCurve);
class Handle(PGeom2d_BezierCurve);
class Handle(PGeom2d_BSplineCurve);
class Handle(PGeom2d_TrimmedCurve);
class Handle(PGeom2d_OffsetCurve);
class Handle(PGeom_Transformation);
class Handle(PGeom_Geometry);
class Handle(PGeom_Point);
class Handle(PGeom_CartesianPoint);
class Handle(PGeom_Vector);
class Handle(PGeom_Direction);
class Handle(PGeom_VectorWithMagnitude);
class Handle(PGeom_AxisPlacement);
class Handle(PGeom_Axis1Placement);
class Handle(PGeom_Axis2Placement);
class Handle(PGeom_Curve);
class Handle(PGeom_Line);
class Handle(PGeom_Conic);
class Handle(PGeom_Circle);
class Handle(PGeom_Ellipse);
class Handle(PGeom_Hyperbola);
class Handle(PGeom_Parabola);
class Handle(PGeom_BoundedCurve);
class Handle(PGeom_BezierCurve);
class Handle(PGeom_BSplineCurve);
class Handle(PGeom_TrimmedCurve);
class Handle(PGeom_OffsetCurve);
class Handle(PGeom_Surface);
class Handle(PGeom_ElementarySurface);
class Handle(PGeom_Plane);
class Handle(PGeom_ConicalSurface);
class Handle(PGeom_CylindricalSurface);
class Handle(PGeom_SphericalSurface);
class Handle(PGeom_ToroidalSurface);
class Handle(PGeom_SweptSurface);
class Handle(PGeom_SurfaceOfLinearExtrusion);
class Handle(PGeom_SurfaceOfRevolution);
class Handle(PGeom_BoundedSurface);
class Handle(PGeom_BezierSurface);
class Handle(PGeom_BSplineSurface);
class Handle(PGeom_RectangularTrimmedSurface);
class Handle(PGeom_OffsetSurface);
class PPoly_Triangle;
class Handle(PPoly_Triangulation);
class Handle(PPoly_Polygon3D);
class Handle(PPoly_Polygon2D);
class Handle(PPoly_PolygonOnTriangulation);
class Handle(PPoly_HArray1OfTriangle);
class PPoly_FieldOfHArray1OfTriangle;
class Handle(PTopoDS_HShape);
class Handle(PTopoDS_TShape);
class Handle(PTopoDS_TVertex);
class Handle(PTopoDS_Vertex);
class Handle(PTopoDS_TEdge);
class Handle(PTopoDS_Edge);
class Handle(PTopoDS_TWire);
class Handle(PTopoDS_Wire);
class Handle(PTopoDS_TFace);
class Handle(PTopoDS_Face);
class Handle(PTopoDS_TShell);
class Handle(PTopoDS_Shell);
class Handle(PTopoDS_TSolid);
class Handle(PTopoDS_Solid);
class Handle(PTopoDS_TCompSolid);
class Handle(PTopoDS_CompSolid);
class Handle(PTopoDS_TCompound);
class Handle(PTopoDS_Compound);
class Handle(PTopoDS_HArray1OfHShape);
class PTopoDS_FieldOfHArray1OfHShape;
class PTopoDS_Shape1;
class Handle(PTopoDS_TShape1);
class Handle(PTopoDS_TVertex1);
class Handle(PTopoDS_TEdge1);
class Handle(PTopoDS_TWire1);
class Handle(PTopoDS_TFace1);
class Handle(PTopoDS_TShell1);
class Handle(PTopoDS_TSolid1);
class Handle(PTopoDS_TCompSolid1);
class Handle(PTopoDS_TCompound1);
class Handle(PTopoDS_HArray1OfShape1);
class PTopoDS_FieldOfHArray1OfShape1;
class Handle(PBRep_CurveRepresentation);
class Handle(PBRep_GCurve);
class Handle(PBRep_Curve3D);
class Handle(PBRep_CurveOnSurface);
class Handle(PBRep_CurveOnClosedSurface);
class Handle(PBRep_Polygon3D);
class Handle(PBRep_PolygonOnTriangulation);
class Handle(PBRep_PolygonOnClosedTriangulation);
class Handle(PBRep_PolygonOnSurface);
class Handle(PBRep_PolygonOnClosedSurface);
class Handle(PBRep_CurveOn2Surfaces);
class Handle(PBRep_PointRepresentation);
class Handle(PBRep_PointOnCurve);
class Handle(PBRep_PointsOnSurface);
class Handle(PBRep_PointOnCurveOnSurface);
class Handle(PBRep_PointOnSurface);
class Handle(PBRep_TFace);
class Handle(PBRep_TEdge);
class Handle(PBRep_TVertex);
class Handle(PBRep_TFace1);
class Handle(PBRep_TEdge1);
class Handle(PBRep_TVertex1);
class Handle(PCDMShape_Document);
class Handle(Standard_Persistent);
class Standard_Storable;
class Handle(PCollection_HAsciiString);
class Handle(PMMgt_PManaged);
class gp_Trsf;
class gp_Circ2d;
class gp_Dir2d;
class gp_Lin2d;
class gp_Pnt2d;
class gp_Vec2d;
class gp_XY;
class gp_Dir;
class gp_Pnt;
class gp_Vec;
class gp_XYZ;
class gp_Trsf2d;
class gp_Ax2d;
class gp_Ax22d;
class Handle(PColStd_HArray1OfReal);
class Handle(PColStd_HArray1OfInteger);
class gp_Ax1;
class gp_Ax2;
class gp_Ax3;
class Handle(PColStd_HArray2OfReal);
class Handle(PCDM_Document);
class DBC_VArrayOfCharacter;
class Handle(PCollection_HExtendedString);
class gp_Mat;
class gp_Mat2d;
class PColStd_FieldOfHArray1OfReal;
class PColStd_FieldOfHArray1OfInteger;
class PColStd_FieldOfHArray2OfReal;
class DBC_VArrayOfExtCharacter;
// This file is generated by WOK (CSFDBSchema).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _ShapeSchema_HeaderFile
#define _ShapeSchema_HeaderFile

#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif
#ifndef _Storage_Macros_HeaderFile
#include <Storage_Macros.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_CallBack_HeaderFile
#include <Storage_CallBack.hxx>
#endif
#ifndef _Storage_BaseDriver_HeaderFile
#include <Storage_BaseDriver.hxx>
#endif

DEFINE_STANDARD_HANDLE(ShapeSchema,Storage_Schema)


class ShapeSchema : public Storage_Schema {
public:

  Storage_DECLARE_SCHEMA_METHODS(ShapeSchema)

  DEFINE_STANDARD_RTTI(ShapeSchema)
};

#endif
