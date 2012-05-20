// Created on: 2009-04-06
// Copyright (c) 2009-2012 OPEN CASCADE SAS
//
// The content of this file is subject to the Open CASCADE Technology Public
// License Version 6.5 (the "License"). You may not use the content of this file
// except in compliance with the License. Please obtain a copy of the License
// at http://www.opencascade.org and read it completely before using this file.
//
// The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
// main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.
//
// The Original Code and all software distributed under the License is
// distributed on an "AS IS" basis, without warranty of any kind, and the
// Initial Developer hereby disclaims all such warranties, including without
// limitation, any warranties of merchantability, fitness for a particular
// purpose or non-infringement. Please see the License for the specific terms
// and conditions governing the rights and limitations under the License.




#include <TDataXtd_Geometry.ixx>
#include <TDataStd.hxx>
#include <TDataXtd.hxx>
#include <TNaming_NamedShape.hxx>
#include <TNaming_Tool.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopAbs.hxx>
#include <BRep_Tool.hxx>

#include <Geom_CartesianPoint.hxx>

#include <Geom_TrimmedCurve.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Line.hxx>
#include <Geom_Ellipse.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Curve.hxx>

#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom_Plane.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Standard_Failure.hxx>


//=======================================================================
//function : GetID
//purpose  : 
//=======================================================================

const Standard_GUID& TDataXtd_Geometry::GetID () 
{
  static Standard_GUID TDataXtd_GeometryID ("2a96b604-ec8b-11d0-bee7-080009dc3333");
  return TDataXtd_GeometryID;
}



//=======================================================================
//function : Set
//purpose  : 
//=======================================================================

Handle(TDataXtd_Geometry) TDataXtd_Geometry::Set (const TDF_Label& L)
{ 
  Handle(TDataXtd_Geometry) A;  
  if (!L.FindAttribute(TDataXtd_Geometry::GetID(),A)) {
    A = new TDataXtd_Geometry (); 
//    A->SetType(TDataXtd_ANY_GEOM);
    L.AddAttribute(A);
  }  
  return A;
}


//=======================================================================
//function : Point
//purpose  : 
//=======================================================================

Standard_Boolean TDataXtd_Geometry::Point(const TDF_Label& L,gp_Pnt& G) 
{
  Handle(TNaming_NamedShape) NS;
  if (L.FindAttribute(TNaming_NamedShape::GetID(),NS)) { 
    return Point(NS,G);
  }
  return Standard_False;
}

//=======================================================================
//function : Point
//purpose  : 
//=======================================================================

Standard_Boolean TDataXtd_Geometry::Point(const Handle(TNaming_NamedShape)& NS, gp_Pnt& G) 
{
  const TopoDS_Shape& shape = TNaming_Tool::GetShape(NS);
  if (shape.IsNull()) return Standard_False;
  if (shape.ShapeType() == TopAbs_VERTEX) {
    const TopoDS_Vertex& vertex = TopoDS::Vertex(shape);
    G = BRep_Tool::Pnt (TopoDS::Vertex (vertex));
    return Standard_True;
  }
  return Standard_False;
}

//=======================================================================
//function : Axis
//purpose  : 
//=======================================================================

Standard_Boolean TDataXtd_Geometry::Axis(const TDF_Label& L,gp_Ax1& G) 
{    
  Handle(TNaming_NamedShape) NS;
  if (L.FindAttribute(TNaming_NamedShape::GetID(),NS)) { 
    return Axis(NS,G);
  }
  return Standard_False;
}

//=======================================================================
//function : Axis
//purpose  : 
//=======================================================================

Standard_Boolean TDataXtd_Geometry::Axis(const Handle(TNaming_NamedShape)& NS, gp_Ax1& G) 
{
  gp_Lin lin;
  if (Line(NS, lin)) {
    G = lin.Position();
    return Standard_True;
  }
  return Standard_False;
}


//=======================================================================
//function : Line
//purpose  : 
//=======================================================================

Standard_Boolean TDataXtd_Geometry::Line(const TDF_Label& L,gp_Lin& G) 
{
  Handle(TNaming_NamedShape) NS;
  if (L.FindAttribute(TNaming_NamedShape::GetID(),NS)) { 
    return Line(NS,G);
  }
  return Standard_False;
}

//=======================================================================
//function : Line
//purpose  : 
//=======================================================================

Standard_Boolean TDataXtd_Geometry::Line(const Handle(TNaming_NamedShape)& NS,gp_Lin& G) 
{
  const TopoDS_Shape& shape = TNaming_Tool::GetShape(NS);
  if (shape.IsNull()) return Standard_False;
  if (shape.ShapeType() == TopAbs_EDGE) {
    const TopoDS_Edge& edge = TopoDS::Edge(shape);
    Standard_Real first,last;
    // TopLoc_Location loc;
    Handle(Geom_Curve) curve = BRep_Tool::Curve (edge,first,last);
    if (!curve.IsNull()) {
      if (curve->IsInstance (STANDARD_TYPE (Geom_TrimmedCurve)))
	curve =  (Handle(Geom_TrimmedCurve)::DownCast (curve))->BasisCurve ();
      Handle(Geom_Line) C  = Handle(Geom_Line)::DownCast(curve);
      if (!C.IsNull()) {
	G = C->Lin();
	return Standard_True;
      }
    }
  }
  return Standard_False;
}

//=======================================================================
//function : Circle
//purpose  : 
//=======================================================================

Standard_Boolean TDataXtd_Geometry::Circle(const TDF_Label& L,gp_Circ& G) 
{  
  Handle(TNaming_NamedShape) NS;
  if (L.FindAttribute(TNaming_NamedShape::GetID(),NS)) { 
    return Circle(NS,G);
  }
  return Standard_False; 
}

//=======================================================================
//function : Circle
//purpose  : 
//=======================================================================

Standard_Boolean TDataXtd_Geometry::Circle(const Handle(TNaming_NamedShape)& NS,gp_Circ& G) 
{  
  const TopoDS_Shape& shape = TNaming_Tool::GetShape(NS);
  if (shape.IsNull()) return Standard_False;
  if (shape.ShapeType() == TopAbs_EDGE) {
    const TopoDS_Edge& edge = TopoDS::Edge(shape);
    Standard_Real first,last;
    // TopLoc_Location loc;
    Handle(Geom_Curve) curve = BRep_Tool::Curve (edge,first,last);
    if (!curve.IsNull()) {
      if (curve->IsInstance (STANDARD_TYPE (Geom_TrimmedCurve)))
	curve =  (Handle(Geom_TrimmedCurve)::DownCast (curve))->BasisCurve ();
      Handle(Geom_Circle) C = Handle(Geom_Circle)::DownCast(curve);
      if (!C.IsNull()) {
	G = C->Circ();
	return Standard_True;
      }
    }
  }
  return Standard_False;
}


//=======================================================================
//function : Ellipse
//purpose  : 
//=======================================================================

Standard_Boolean TDataXtd_Geometry::Ellipse(const TDF_Label& L,gp_Elips& G) 
{
  Handle(TNaming_NamedShape) NS;
  if (L.FindAttribute(TNaming_NamedShape::GetID(),NS)) { 
    return Ellipse(NS,G);
  }
  return Standard_False;
}


//=======================================================================
//function : Ellipse
//purpose  : 
//=======================================================================

Standard_Boolean TDataXtd_Geometry::Ellipse(const Handle(TNaming_NamedShape)& NS, gp_Elips& G) 
{  
  const TopoDS_Shape& shape = TNaming_Tool::GetShape(NS);
  if (shape.IsNull()) return Standard_False;
  if (shape.ShapeType() == TopAbs_EDGE) {
    const TopoDS_Edge& edge = TopoDS::Edge(shape);
    Standard_Real first,last;
    Handle(Geom_Curve) curve = BRep_Tool::Curve (edge,first,last);
    if (!curve.IsNull()) {
      if (curve->IsInstance (STANDARD_TYPE (Geom_TrimmedCurve)))
	curve =  (Handle(Geom_TrimmedCurve)::DownCast (curve))->BasisCurve ();
      Handle(Geom_Ellipse) C = Handle(Geom_Ellipse)::DownCast(curve);
      if (!C.IsNull()) {
	G = C->Elips();
	return Standard_True;
      }
    }
  }
  return Standard_False;
}


//=======================================================================
//function : Plane
//purpose  : 
//=======================================================================

Standard_Boolean TDataXtd_Geometry::Plane(const TDF_Label& L, gp_Pln& G) 
{  
  Handle(TNaming_NamedShape) NS;
  if (L.FindAttribute(TNaming_NamedShape::GetID(),NS)) { 
    return Plane(NS,G);
  }
  return Standard_False;
}


//=======================================================================
//function : Plane
//purpose  : 
//=======================================================================

Standard_Boolean TDataXtd_Geometry::Plane(const Handle(TNaming_NamedShape)& NS, gp_Pln& G) 
{
  const TopoDS_Shape& shape = TNaming_Tool::GetShape(NS);
  if (shape.IsNull()) return Standard_False;
  if (shape.ShapeType() == TopAbs_FACE) {
    const TopoDS_Face& face = TopoDS::Face(shape);
    Handle(Geom_Surface) surface = BRep_Tool::Surface (face);
    if (!surface.IsNull())  {
       if (surface->IsInstance(STANDARD_TYPE(Geom_RectangularTrimmedSurface))) 
	 surface = ((Handle(Geom_RectangularTrimmedSurface)&) surface)->BasisSurface();
       Handle(Geom_Plane) S = Handle(Geom_Plane)::DownCast(surface);  
       if (!S.IsNull()) {
	 G = S->Pln();
	 return Standard_True;
       }
     } 
  }
  return Standard_False;
}


//=======================================================================
//function : Cylinder
//purpose  : 
//=======================================================================

Standard_Boolean TDataXtd_Geometry::Cylinder(const TDF_Label& L, gp_Cylinder& G) 
{ 
  Handle(TNaming_NamedShape) NS;
  if (L.FindAttribute(TNaming_NamedShape::GetID(),NS)) { 
    return Cylinder (NS,G);
  }
  return Standard_False;
}


//=======================================================================
//function : Cylinder
//purpose  : 
//=======================================================================

Standard_Boolean TDataXtd_Geometry::Cylinder(const Handle(TNaming_NamedShape)& NS, gp_Cylinder& G) 
{  
  const TopoDS_Shape& shape = TNaming_Tool::GetShape(NS);
  if (shape.IsNull()) return Standard_False;
  if (shape.ShapeType() == TopAbs_FACE) {
    const TopoDS_Face& face = TopoDS::Face(shape);
    Handle(Geom_Surface) surface = BRep_Tool::Surface (face);
    if (!surface.IsNull())  {
      if (surface->IsInstance(STANDARD_TYPE(Geom_RectangularTrimmedSurface))) 
	surface = ((Handle(Geom_RectangularTrimmedSurface)&) surface)->BasisSurface();
      Handle(Geom_CylindricalSurface) S = Handle(Geom_CylindricalSurface)::DownCast(surface);
      if (!S.IsNull()) {
	G = S->Cylinder();
	return Standard_True;
      }
      
    } 
  }
  return Standard_False;
}


//=======================================================================
//function : Type
//purpose  : 
//=======================================================================

TDataXtd_GeometryEnum  TDataXtd_Geometry::Type (const TDF_Label& L)
{  
  Handle(TNaming_NamedShape) NS;
  if (L.FindAttribute(TNaming_NamedShape::GetID(),NS)) { 
    return Type (NS);
  }
  return TDataXtd_ANY_GEOM;
}

//=======================================================================
//function : Type
//purpose  : 
//=======================================================================

TDataXtd_GeometryEnum  TDataXtd_Geometry::Type (const Handle(TNaming_NamedShape)& NS)
{
  TDataXtd_GeometryEnum type (TDataXtd_ANY_GEOM);
  const TopoDS_Shape& shape = TNaming_Tool::GetShape(NS);
  switch (shape.ShapeType()) {
  case TopAbs_VERTEX : 
    { 
      type = TDataXtd_POINT;
      break;
    }
  case TopAbs_EDGE : 
    {    
      const TopoDS_Edge& edge = TopoDS::Edge(shape);    
      Standard_Real first,last;
      // TopLoc_Location loc;
      Handle(Geom_Curve) curve = BRep_Tool::Curve (edge,first,last);
      if (!curve.IsNull()) {
	if (curve->IsInstance (STANDARD_TYPE (Geom_TrimmedCurve))) {
	  curve =  (Handle(Geom_TrimmedCurve)::DownCast (curve))->BasisCurve ();
	}
	if (curve->IsInstance(STANDARD_TYPE(Geom_Line))) {
	  type = TDataXtd_LINE;
	}
	else if (curve->IsInstance(STANDARD_TYPE(Geom_Circle))) {
	  type = TDataXtd_CIRCLE;
	}
	else if (curve->IsInstance(STANDARD_TYPE(Geom_Ellipse))) {
	  type = TDataXtd_ELLIPSE;
	}
	break;
      }
#ifdef DEB      
      else {
	Standard_Failure::Raise("curve Null dans TDataXtd_Geometry");
      }
#endif
    }
  case TopAbs_FACE : 
    {
      const TopoDS_Face& face = TopoDS::Face(shape);
      Handle(Geom_Surface) surface = BRep_Tool::Surface (face);
      if (!surface.IsNull()) {
	if (surface->IsInstance(STANDARD_TYPE(Geom_RectangularTrimmedSurface))) { 
	  surface = ((Handle(Geom_RectangularTrimmedSurface)&) surface)->BasisSurface();
	}
	if (surface->IsInstance(STANDARD_TYPE(Geom_CylindricalSurface))) {
	  type = TDataXtd_CYLINDER;
	}
	else if (surface->IsInstance(STANDARD_TYPE(Geom_Plane))) {
	  type = TDataXtd_PLANE;
	}
      } 
#ifdef DEB      
      else {
	Standard_Failure::Raise("surface Null dans TDataXtd_Geometry");
      }
#endif
      break;
    }
    default :
      {
	break;
      }
  }
  return type;
}

//=======================================================================
//function : TDataXtd_Geometry
//purpose  : 
//=======================================================================

TDataXtd_Geometry::TDataXtd_Geometry ()
     : myType (TDataXtd_ANY_GEOM)
 { }


//=======================================================================
//function : GetType
//purpose  : 
//=======================================================================

TDataXtd_GeometryEnum  TDataXtd_Geometry::GetType () const
{
  return myType;
}


//=======================================================================
//function : SetType
//purpose  : 
//=======================================================================

void TDataXtd_Geometry::SetType (const TDataXtd_GeometryEnum G)
{
  // OCC2932 correction
  if(myType == G) return;

  Backup();
  myType = G;
}


//=======================================================================
//function : ID
//purpose  : 
//=======================================================================

const Standard_GUID& TDataXtd_Geometry::ID() const {  return GetID(); }


//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================

Handle(TDF_Attribute) TDataXtd_Geometry::NewEmpty () const
{  
  return new TDataXtd_Geometry(); 
}

//=======================================================================
//function : Restore
//purpose  : 
//=======================================================================

void TDataXtd_Geometry::Restore (const Handle(TDF_Attribute)& With) 
{
  myType =  Handle(TDataXtd_Geometry)::DownCast(With)->GetType();
}

//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================

void TDataXtd_Geometry::Paste (const Handle(TDF_Attribute)& Into, const Handle(TDF_RelocationTable)& RT) const { 
  Handle(TDataXtd_Geometry)::DownCast(Into)->SetType(myType);
}


//=======================================================================
//function : Dump
//purpose  : 
//=======================================================================

Standard_OStream& TDataXtd_Geometry::Dump (Standard_OStream& anOS) const
{  
  anOS << "Geometry ";  
  TDataXtd::Print(GetType(),anOS);
  return anOS;
}
