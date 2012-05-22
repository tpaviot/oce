// Created on: 1993-07-01
// Created by: Bruno DUMORTIER
// Copyright (c) 1993-1999 Matra Datavision
// Copyright (c) 1999-2012 OPEN CASCADE SAS
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


#include <Adaptor2d_Curve2d.ixx>
#include <Standard_NotImplemented.hxx>

void Adaptor2d_Curve2d::Delete()
{}

//=======================================================================
//function : FirstParameter
//purpose  : 
//=======================================================================

Standard_Real Adaptor2d_Curve2d::FirstParameter() const 
{  
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::FirstParameter");
  return 0.;
}


//=======================================================================
//function : LastParameter
//purpose  : 
//=======================================================================

Standard_Real Adaptor2d_Curve2d::LastParameter() const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::LastParameter");
  return 0.;
}


//=======================================================================
//function : Continuity
//purpose  : 
//=======================================================================

GeomAbs_Shape Adaptor2d_Curve2d::Continuity() const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::Continuity");
  return GeomAbs_C0;
}


//=======================================================================
//function : NbIntervals
//purpose  : 
//=======================================================================

//Standard_Integer Adaptor2d_Curve2d::NbIntervals(const GeomAbs_Shape S) const 
Standard_Integer Adaptor2d_Curve2d::NbIntervals(const GeomAbs_Shape ) const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::NbIntervals");
  return 0;
}


//=======================================================================
//function : Intervals
//purpose  : 
//=======================================================================

//void Adaptor2d_Curve2d::Intervals(TColStd_Array1OfReal& T, 
//				const GeomAbs_Shape S) const 
void Adaptor2d_Curve2d::Intervals(TColStd_Array1OfReal& , 
				const GeomAbs_Shape ) const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::Intervals");
}


//=======================================================================
//function : Trim
//purpose  : 
//=======================================================================

//Handle(Adaptor2d_HCurve2d) Adaptor2d_Curve2d::Trim(const Standard_Real First,
//					       const Standard_Real Last ,
//					       const Standard_Real Tol) const 
Handle(Adaptor2d_HCurve2d) Adaptor2d_Curve2d::Trim(const Standard_Real ,
					       const Standard_Real ,
					       const Standard_Real ) const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::Trim");
  return Handle(Adaptor2d_HCurve2d)();
}

//=======================================================================
//function : IsClosed
//purpose  : 
//=======================================================================

Standard_Boolean Adaptor2d_Curve2d::IsClosed() const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::IsClosed");
  return 0;
}


//=======================================================================
//function : IsPeriodic
//purpose  : 
//=======================================================================

Standard_Boolean Adaptor2d_Curve2d::IsPeriodic() const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::IsPeriodic");
  return 0;
}


//=======================================================================
//function : Period
//purpose  : 
//=======================================================================

Standard_Real Adaptor2d_Curve2d::Period() const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::Period");
  return 0.;
}


//=======================================================================
//function : Value
//purpose  : 
//=======================================================================

//gp_Pnt2d Adaptor2d_Curve2d::Value(const Standard_Real U) const 
gp_Pnt2d Adaptor2d_Curve2d::Value(const Standard_Real ) const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::Value");
  return gp_Pnt2d();
}


//=======================================================================
//function : D0
//purpose  : 
//=======================================================================

//void Adaptor2d_Curve2d::D0(const Standard_Real U, gp_Pnt2d& P) const 
void Adaptor2d_Curve2d::D0(const Standard_Real , gp_Pnt2d& ) const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::D0");
}


//=======================================================================
//function : D1
//purpose  : 
//=======================================================================

//void Adaptor2d_Curve2d::D1(const Standard_Real U, 
//			 gp_Pnt2d& P, gp_Vec2d& V) const 
void Adaptor2d_Curve2d::D1(const Standard_Real , 
			 gp_Pnt2d& , gp_Vec2d& ) const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::D1");
}


//=======================================================================
//function : D2
//purpose  : 
//=======================================================================

//void Adaptor2d_Curve2d::D2(const Standard_Real U, 
//			 gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2) const 
void Adaptor2d_Curve2d::D2(const Standard_Real , 
			 gp_Pnt2d& , gp_Vec2d& , gp_Vec2d& ) const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::D2");
}


//=======================================================================
//function : D3
//purpose  : 
//=======================================================================

//void Adaptor2d_Curve2d::D3(const Standard_Real U, 
//			 gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2, gp_Vec2d& V3)
void Adaptor2d_Curve2d::D3(const Standard_Real , 
			 gp_Pnt2d& , gp_Vec2d& , gp_Vec2d& , gp_Vec2d& ) const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::D3");
}


//=======================================================================
//function : DN
//purpose  : 
//=======================================================================

//gp_Vec2d Adaptor2d_Curve2d::DN(const Standard_Real U, 
//			     const Standard_Integer N) const 
gp_Vec2d Adaptor2d_Curve2d::DN(const Standard_Real , 
			     const Standard_Integer ) const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::DN");
  return gp_Vec2d();
}


//=======================================================================
//function : Resolution
//purpose  : 
//=======================================================================

//Standard_Real Adaptor2d_Curve2d::Resolution(const Standard_Real R3d) const 
Standard_Real Adaptor2d_Curve2d::Resolution(const Standard_Real ) const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::Resolution");
  return 0.;
}


//=======================================================================
//function : GetType
//purpose  : 
//=======================================================================

GeomAbs_CurveType Adaptor2d_Curve2d::GetType() const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::GetType");
  return GeomAbs_OtherCurve;
}


//=======================================================================
//function : Line
//purpose  : 
//=======================================================================

gp_Lin2d Adaptor2d_Curve2d::Line() const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::Line");
  return gp_Lin2d();
}


//=======================================================================
//function : Circle
//purpose  : 
//=======================================================================

gp_Circ2d Adaptor2d_Curve2d::Circle() const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::Circle");
  return gp_Circ2d();
}


//=======================================================================
//function : Ellipse
//purpose  : 
//=======================================================================

gp_Elips2d Adaptor2d_Curve2d::Ellipse() const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::Ellipse");
  return gp_Elips2d();
}


//=======================================================================
//function : Hyperbola
//purpose  : 
//=======================================================================

gp_Hypr2d Adaptor2d_Curve2d::Hyperbola() const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::Hyperbola");
  return gp_Hypr2d();
}


//=======================================================================
//function : Parabola
//purpose  : 
//=======================================================================

gp_Parab2d Adaptor2d_Curve2d::Parabola() const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::Parabola");
  return gp_Parab2d();
}


//=======================================================================
//function : Degree
//purpose  : 
//=======================================================================

Standard_Integer Adaptor2d_Curve2d::Degree() const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::Degree");
  return 0;
}


//=======================================================================
//function : IsRational
//purpose  : 
//=======================================================================

Standard_Boolean Adaptor2d_Curve2d::IsRational() const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::IsRational");
  return 0;
}


//=======================================================================
//function : NbPoles
//purpose  : 
//=======================================================================

Standard_Integer Adaptor2d_Curve2d::NbPoles() const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::NbPole");
  return 0;
}


//=======================================================================
//function : NbKnots
//purpose  : 
//=======================================================================

Standard_Integer Adaptor2d_Curve2d::NbKnots() const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::NbKnots");
  return 0;
}


//=======================================================================
//function : Bezier
//purpose  : 
//=======================================================================

Handle(Geom2d_BezierCurve) Adaptor2d_Curve2d::Bezier() const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::Bezier");
  return Handle(Geom2d_BezierCurve)();
}


//=======================================================================
//function : BSpline
//purpose  : 
//=======================================================================

Handle(Geom2d_BSplineCurve) Adaptor2d_Curve2d::BSpline() const 
{
  Standard_NotImplemented::Raise("Adaptor2d_Curve2d::BSpline");
  return Handle(Geom2d_BSplineCurve)();
}



