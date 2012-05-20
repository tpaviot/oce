// Created on: 1993-03-24
// Created by: JCV
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



#include <Geom2d_TrimmedCurve.ixx>
#include <gp.hxx>
#include <Geom2d_Geometry.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_BezierCurve.hxx>
#include <Geom2d_OffsetCurve.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2d_Hyperbola.hxx>
#include <Geom2d_Parabola.hxx>
#include <Standard_ConstructionError.hxx>
#include <Standard_RangeError.hxx>
#include <ElCLib.hxx>
#include <Precision.hxx>


typedef Handle(Geom2d_TrimmedCurve) Handle(TrimmedCurve);
typedef Geom2d_TrimmedCurve         TrimmedCurve;
typedef Handle(Geom2d_Curve)        Handle(Curve);
typedef Handle(Geom2d_Geometry)     Handle(Geometry);
typedef gp_Ax2d   Ax2d;
typedef gp_Pnt2d  Pnt2d;
typedef gp_Trsf2d Trsf2d;
typedef gp_Vec2d  Vec2d;





//=======================================================================
//function : Copy
//purpose  : 
//=======================================================================

Handle(Geom2d_Geometry) Geom2d_TrimmedCurve::Copy () const 
{
  Handle(TrimmedCurve) Tc;
  Tc = new TrimmedCurve (basisCurve, uTrim1, uTrim2);
  return Tc;
}

//=======================================================================
//function : Geom2d_TrimmedCurve
//purpose  : 
//=======================================================================

Geom2d_TrimmedCurve::Geom2d_TrimmedCurve (const Handle(Geom2d_Curve)& C, 
					  const Standard_Real U1, 
					  const Standard_Real U2,
					  const Standard_Boolean Sense) :
     uTrim1 (U1),
     uTrim2 (U2)
{
  if(C.IsNull()) Standard_ConstructionError::Raise("Geom2d_TrimmedCurve:: C is null");
  // kill trimmed basis curves
  Handle(Geom2d_TrimmedCurve) T = Handle(Geom2d_TrimmedCurve)::DownCast(C);
  if (!T.IsNull())
    basisCurve = Handle(Curve)::DownCast(T->BasisCurve()->Copy());
  else
    basisCurve = Handle(Curve)::DownCast(C->Copy());

  SetTrim(U1,U2,Sense);
}

//=======================================================================
//function : Reverse
//purpose  : 
//=======================================================================

void Geom2d_TrimmedCurve::Reverse () 
{
  Standard_Real U1 = basisCurve->ReversedParameter(uTrim2);
  Standard_Real U2 = basisCurve->ReversedParameter(uTrim1);
  basisCurve->Reverse();
  SetTrim(U1,U2);
}

//=======================================================================
//function : ReversedParamater
//purpose  : 
//=======================================================================

Standard_Real Geom2d_TrimmedCurve::ReversedParameter( const Standard_Real U) const
{
  return basisCurve->ReversedParameter(U);
}

//=======================================================================
//function : SetTrim
//purpose  : 
//=======================================================================

void Geom2d_TrimmedCurve::SetTrim (const Standard_Real U1, 
				   const Standard_Real U2, 
				   const Standard_Boolean Sense) 
{
  Standard_Boolean sameSense = Standard_True;
  if (U1 == U2)
    Standard_ConstructionError::Raise("Geom2d_TrimmedCurve::U1 == U2");

  Standard_Real Udeb = basisCurve->FirstParameter();
  Standard_Real Ufin = basisCurve->LastParameter();
  
  if (basisCurve->IsPeriodic())  {
     sameSense = Sense;
      
     // set uTrim1 in the range Udeb , Ufin
     // set uTrim2 in the range uTrim1 , uTrim1 + Period()
     uTrim1 = U1;
     uTrim2 = U2;     
     ElCLib::AdjustPeriodic(Udeb, Ufin, 
			    Min(Abs(uTrim2-uTrim1)/2,Precision::PConfusion()), 
			    uTrim1, uTrim2);
  }
  else { 
    if (U1 < U2) {
      sameSense = Sense;
      uTrim1 = U1;
      uTrim2 = U2;
    }
    else {
      sameSense = !Sense;
      uTrim1 = U2;
      uTrim2 = U1;
    }

    if ((Udeb - uTrim1 > Precision::PConfusion()) ||
	(uTrim2 - Ufin > Precision::PConfusion()))   {
      Standard_ConstructionError::Raise
	("Geom_TrimmedCurve::parameters out of range");
    }
  }    

  if (!sameSense)
    Reverse();
}

//=======================================================================
//function : BasisCurve
//purpose  : 
//=======================================================================

Handle(Curve) Geom2d_TrimmedCurve::BasisCurve () const 
{ 
  return basisCurve;
}

//=======================================================================
//function : Continuity
//purpose  : 
//=======================================================================

GeomAbs_Shape Geom2d_TrimmedCurve::Continuity () const
{ 
  return basisCurve->Continuity(); 
}

//=======================================================================
//function : IsCN
//purpose  : 
//=======================================================================

Standard_Boolean Geom2d_TrimmedCurve::IsCN (const Standard_Integer N) const 
{
  Standard_RangeError_Raise_if (N < 0, " ");
  return basisCurve->IsCN (N);
}

//=======================================================================
//function : EndPoint
//purpose  : 
//=======================================================================

Pnt2d Geom2d_TrimmedCurve::EndPoint () const 
{ 
  return  basisCurve->Value(uTrim2);
}

//=======================================================================
//function : FirstParameter
//purpose  : 
//=======================================================================

Standard_Real Geom2d_TrimmedCurve::FirstParameter () const       { return uTrim1; }

//=======================================================================
//function : IsClosed
//purpose  : 
//=======================================================================

Standard_Boolean Geom2d_TrimmedCurve::IsClosed () const          
{
  Standard_Real Dist = 
    Value(FirstParameter()).Distance(Value(LastParameter()));
  return ( Dist <= gp::Resolution());
}

//=======================================================================
//function : IsPeriodic
//purpose  : 
//=======================================================================

Standard_Boolean Geom2d_TrimmedCurve::IsPeriodic () const        
{
  //return basisCurve->IsPeriodic();
  return Standard_False;
}

//=======================================================================
//function : Period
//purpose  : 
//=======================================================================

Standard_Real Geom2d_TrimmedCurve::Period () const
{
  return basisCurve->Period();
}

//=======================================================================
//function : LastParameter
//purpose  : 
//=======================================================================

Standard_Real Geom2d_TrimmedCurve::LastParameter () const        { return uTrim2; }

//=======================================================================
//function : StartPoint
//purpose  : 
//=======================================================================

Pnt2d Geom2d_TrimmedCurve::StartPoint () const 
{
  gp_Pnt2d P;
    P = basisCurve->Value(uTrim1);
  return P;
}

//=======================================================================
//function : D0
//purpose  : 
//=======================================================================

void Geom2d_TrimmedCurve::D0 (const Standard_Real   U,
			            Pnt2d& P ) const {
  basisCurve->D0(U, P);
}

//=======================================================================
//function : D1
//purpose  : 
//=======================================================================

void Geom2d_TrimmedCurve::D1 (const Standard_Real U, Pnt2d& P, Vec2d& V1) const 
{
   basisCurve->D1 (U, P, V1);
}

//=======================================================================
//function : D2
//purpose  : 
//=======================================================================

void Geom2d_TrimmedCurve::D2 (const Standard_Real U, 
			            Pnt2d& P, 
			            Vec2d& V1, Vec2d& V2) const 
{
   basisCurve->D2 (U, P, V1, V2);
}

//=======================================================================
//function : D3
//purpose  : 
//=======================================================================

void Geom2d_TrimmedCurve::D3 (const Standard_Real U, 
			            Pnt2d& P, 
			            Vec2d& V1, Vec2d& V2, Vec2d& V3) const 
{
   basisCurve->D3 (U, P, V1, V2, V3);
}

//=======================================================================
//function : DN
//purpose  : 
//=======================================================================

Vec2d Geom2d_TrimmedCurve::DN (const Standard_Real U, const Standard_Integer N) const 
{
  return  basisCurve->DN(U, N);
}

//=======================================================================
//function : Transform
//purpose  : 
//=======================================================================

void Geom2d_TrimmedCurve::Transform (const Trsf2d& T) 
{
  basisCurve->Transform (T);
  Standard_Real U1 = basisCurve->TransformedParameter(uTrim1,T);
  Standard_Real U2 = basisCurve->TransformedParameter(uTrim2,T);
  SetTrim(U1,U2);
}

//=======================================================================
//function : TransformedParameter
//purpose  : 
//=======================================================================

Standard_Real Geom2d_TrimmedCurve::TransformedParameter(const Standard_Real U,
							const gp_Trsf2d& T) const
{
  return basisCurve->TransformedParameter(U,T);
}

//=======================================================================
//function : ParametricTransformation
//purpose  : 
//=======================================================================

Standard_Real Geom2d_TrimmedCurve::ParametricTransformation(const gp_Trsf2d& T) const
{
  return basisCurve->ParametricTransformation(T);
}

