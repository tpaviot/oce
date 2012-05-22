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

#include <Adaptor2d_Line2d.ixx>

#include <Precision.hxx>
#include <ElCLib.hxx>
#include <Standard_OutOfRange.hxx>
#include <Standard_NoSuchObject.hxx>
#include <Adaptor2d_HLine2d.hxx>

//=======================================================================
//function : Adaptor2d_Line2d
//purpose  : 
//=======================================================================

Adaptor2d_Line2d::Adaptor2d_Line2d()
{
}

//=======================================================================
//function : Adaptor_Line2d
//purpose  : 
//=======================================================================

 Adaptor2d_Line2d::Adaptor2d_Line2d(const gp_Pnt2d& P, const gp_Dir2d& D, 
				const Standard_Real UFirst, 
				const Standard_Real ULast):
       myUfirst(UFirst),myUlast(ULast),myAx2d(P,D)
{
}

//=======================================================================
//function : Load
//purpose  : 
//=======================================================================

void Adaptor2d_Line2d::Load(const gp_Lin2d& L)
{
  myAx2d   =  L.Position();
  myUfirst = -Precision::Infinite();
  myUlast  =  Precision::Infinite();
}

//=======================================================================
//function : Load
//purpose  : 
//=======================================================================

void Adaptor2d_Line2d::Load(const gp_Lin2d& L, const Standard_Real Fi, const Standard_Real La)
{
  myAx2d   =  L.Position();
  myUfirst =  Fi;
  myUlast  =  La;
}

//=======================================================================
//function : FirstParameter
//purpose  : 
//=======================================================================

Standard_Real Adaptor2d_Line2d::FirstParameter() const 
{
  return myUfirst;
}

//=======================================================================
//function : LastParameter
//purpose  : 
//=======================================================================

Standard_Real Adaptor2d_Line2d::LastParameter() const 
{
  return myUlast;
}

//=======================================================================
//function : Continuity
//purpose  : 
//=======================================================================

GeomAbs_Shape Adaptor2d_Line2d::Continuity() const 
{
  return GeomAbs_CN;
}

//=======================================================================
//function : NbIntervals
//purpose  : 
//=======================================================================

//Standard_Integer Adaptor2d_Line2d::NbIntervals(const GeomAbs_Shape S) const 
Standard_Integer Adaptor2d_Line2d::NbIntervals(const GeomAbs_Shape ) const 
{
  return 1;
}

//=======================================================================
//function : Interval
//purpose  : 
//=======================================================================

void Adaptor2d_Line2d::Intervals(TColStd_Array1OfReal& T,
//			       const GeomAbs_Shape S) const 
			       const GeomAbs_Shape ) const 
{
  T(T.Lower())   = myUfirst;
  T(T.Lower()+1) = myUlast;
}

//=======================================================================
//function : Trim
//purpose  : 
//=======================================================================

Handle(Adaptor2d_HCurve2d) Adaptor2d_Line2d::Trim
(const Standard_Real First,
 const Standard_Real Last,
 const Standard_Real) const 
{
  Handle(Adaptor2d_HLine2d) HL = new Adaptor2d_HLine2d();
  HL->ChangeCurve2d().Load(gp_Lin2d(myAx2d),First,Last);
  return HL;
}

//=======================================================================
//function : IsClosed
//purpose  : 
//=======================================================================

Standard_Boolean Adaptor2d_Line2d::IsClosed() const 
{
  return Standard_False;
}

//=======================================================================
//function : IsPeriodic
//purpose  : 
//=======================================================================

Standard_Boolean Adaptor2d_Line2d::IsPeriodic() const 
{
  return Standard_False;
}

//=======================================================================
//function : Period
//purpose  : 
//=======================================================================

Standard_Real Adaptor2d_Line2d::Period() const 
{
  Standard_NoSuchObject::Raise();
  return 0;
}

//=======================================================================
//function : Value
//purpose  : 
//=======================================================================

gp_Pnt2d Adaptor2d_Line2d::Value(const Standard_Real X) const 
{
  return ElCLib::LineValue(X,myAx2d);
}

//=======================================================================
//function : D0
//purpose  : 
//=======================================================================

void Adaptor2d_Line2d::D0(const Standard_Real X, gp_Pnt2d& P) const 
{
  P = ElCLib::LineValue(X,myAx2d);
}

//=======================================================================
//function : D1
//purpose  : 
//=======================================================================

void Adaptor2d_Line2d::D1(const Standard_Real X, gp_Pnt2d& P, gp_Vec2d& V) const 
{
  ElCLib::LineD1(X,myAx2d,P,V);
}

//=======================================================================
//function : D2
//purpose  : 
//=======================================================================

void Adaptor2d_Line2d::D2(const Standard_Real X, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2) const 
{
  ElCLib::LineD1(X,myAx2d,P,V1);
  V2.SetCoord(0.,0.);
}

//=======================================================================
//function : D3
//purpose  : 
//=======================================================================

void Adaptor2d_Line2d::D3(const Standard_Real X, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2, gp_Vec2d& V3) const 
{
  ElCLib::LineD1(X,myAx2d,P,V1);
  V2.SetCoord(0.,0.);
  V3.SetCoord(0.,0.);
}

//=======================================================================
//function : DN
//purpose  : 
//=======================================================================

//gp_Vec2d Adaptor2d_Line2d::DN(const Standard_Real U, const Standard_Integer N) const 
gp_Vec2d Adaptor2d_Line2d::DN(const Standard_Real , const Standard_Integer N) const 
{
  if (N<=0) {Standard_OutOfRange::Raise();}
  if (N==1) {
    return myAx2d.Direction();
  }
  return gp_Vec2d(0.,0.);
}

//=======================================================================
//function : Resolution
//purpose  : 
//=======================================================================

Standard_Real Adaptor2d_Line2d::Resolution(const Standard_Real R3d) const 
{
  return R3d; // nul !!!!
}

//=======================================================================
//function : GetType
//purpose  : 
//=======================================================================

GeomAbs_CurveType Adaptor2d_Line2d::GetType() const 
{
  return GeomAbs_Line;
}

//=======================================================================
//function : Line
//purpose  : 
//=======================================================================

gp_Lin2d Adaptor2d_Line2d::Line() const 
{
  return gp_Lin2d(myAx2d);
}

//=======================================================================
//function : Circle
//purpose  : 
//=======================================================================

gp_Circ2d Adaptor2d_Line2d::Circle() const 
{
  Standard_NoSuchObject::Raise();
  return gp_Circ2d();
}

//=======================================================================
//function : Ellipse
//purpose  : 
//=======================================================================

gp_Elips2d Adaptor2d_Line2d::Ellipse() const 
{
  Standard_NoSuchObject::Raise();
  return gp_Elips2d();
}

//=======================================================================
//function : Hyperbola
//purpose  : 
//=======================================================================

gp_Hypr2d Adaptor2d_Line2d::Hyperbola() const 
{
  Standard_NoSuchObject::Raise();
  return gp_Hypr2d();
}

//=======================================================================
//function : Parabola
//purpose  : 
//=======================================================================

gp_Parab2d Adaptor2d_Line2d::Parabola() const 
{
  Standard_NoSuchObject::Raise();
  return gp_Parab2d();
}

//=======================================================================
//function : Degree
//purpose  : 
//=======================================================================

Standard_Integer Adaptor2d_Line2d::Degree()  const 
 {
  Standard_NoSuchObject::Raise();
  return 0 ;
}
//=======================================================================
//function : IsRational
//purpose  : 
//=======================================================================

Standard_Boolean Adaptor2d_Line2d::IsRational()  const 
 {
  Standard_NoSuchObject::Raise();
  return 0 ;
}
//=======================================================================
//function : NbPoles
//purpose  : 
//=======================================================================

Standard_Integer Adaptor2d_Line2d::NbPoles()  const 
 {
  Standard_NoSuchObject::Raise();
  return 0 ;
}
//=======================================================================
//function : NbKnots
//purpose  : 
//=======================================================================

Standard_Integer Adaptor2d_Line2d::NbKnots()  const 
 {
  Standard_NoSuchObject::Raise();
  return 0 ;
}
//=======================================================================
//function : Bezier
//purpose  : 
//=======================================================================

Handle(Geom2d_BezierCurve) Adaptor2d_Line2d::Bezier() const 
{
  Standard_NoSuchObject::Raise();
  Handle(Geom2d_BezierCurve) nul;
  return nul;
}

//=======================================================================
//function : BSpline
//purpose  : 
//=======================================================================

Handle(Geom2d_BSplineCurve) Adaptor2d_Line2d::BSpline() const 
{
  Standard_NoSuchObject::Raise();
  Handle(Geom2d_BSplineCurve) nul;
  return nul;
}

