// Created on: 1993-03-10
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



#include <Geom_Hyperbola.ixx>

#include <Precision.hxx>
#include <gp_XYZ.hxx>
#include <ElCLib.hxx>
#include <Standard_RangeError.hxx>
#include <Standard_ConstructionError.hxx>


typedef Geom_Hyperbola         Hyperbola;
typedef Handle(Geom_Hyperbola) Handle(Hyperbola);
typedef gp_Ax1  Ax1;
typedef gp_Ax2  Ax2;
typedef gp_Pnt  Pnt;
typedef gp_Vec  Vec;
typedef gp_Trsf Trsf;
typedef gp_XYZ  XYZ;





//=======================================================================
//function : Copy
//purpose  : 
//=======================================================================

Handle(Geom_Geometry) Geom_Hyperbola::Copy() const {

  Handle(Hyperbola) H;
  H = new Hyperbola (pos, majorRadius, minorRadius);
  return H;
}




//=======================================================================
//function : Geom_Hyperbola
//purpose  : 
//=======================================================================

Geom_Hyperbola::Geom_Hyperbola (const gp_Hypr& H) 
: majorRadius (H.MajorRadius()), minorRadius (H.MinorRadius()) {

  pos = H.Position();
}


//=======================================================================
//function : Geom_Hyperbola
//purpose  : 
//=======================================================================

Geom_Hyperbola::Geom_Hyperbola ( const Ax2& A, 
                                 const Standard_Real MajorRadius, 
                                 const Standard_Real MinorRadius) 
 : majorRadius (MajorRadius), minorRadius (MinorRadius) {

  if (MajorRadius < 0.0 || MinorRadius < 0.0) {
    Standard_ConstructionError::Raise();
  }
  pos = A;
}

//=======================================================================
//function : IsClosed
//purpose  : 
//=======================================================================

Standard_Boolean Geom_Hyperbola::IsClosed () const      { return Standard_False; }

//=======================================================================
//function : IsPeriodic
//purpose  : 
//=======================================================================

Standard_Boolean Geom_Hyperbola::IsPeriodic () const    { return Standard_False; } 

//=======================================================================
//function : FirstParameter
//purpose  : 
//=======================================================================

Standard_Real Geom_Hyperbola::FirstParameter () const   
{ return -Precision::Infinite(); }

//=======================================================================
//function : LastParameter
//purpose  : 
//=======================================================================

Standard_Real Geom_Hyperbola::LastParameter () const    
{ return Precision::Infinite(); }

//=======================================================================
//function : MajorRadius
//purpose  : 
//=======================================================================

Standard_Real Geom_Hyperbola::MajorRadius () const      { return majorRadius; }

//=======================================================================
//function : MinorRadius
//purpose  : 
//=======================================================================

Standard_Real Geom_Hyperbola::MinorRadius () const      { return minorRadius; }

//=======================================================================
//function : SetHypr
//purpose  : 
//=======================================================================

void Geom_Hyperbola::SetHypr (const gp_Hypr& H) {

   majorRadius = H.MajorRadius();
   minorRadius = H.MinorRadius();
   pos = H.Position();
}


//=======================================================================
//function : SetMajorRadius
//purpose  : 
//=======================================================================

void Geom_Hyperbola::SetMajorRadius (const Standard_Real MajorRadius) {

  if (MajorRadius < 0.0) Standard_ConstructionError::Raise();
  else                   majorRadius = MajorRadius;
}


//=======================================================================
//function : SetMinorRadius
//purpose  : 
//=======================================================================

void Geom_Hyperbola::SetMinorRadius (const Standard_Real MinorRadius) {

  if (MinorRadius < 0.0)  Standard_ConstructionError::Raise();
  else                    minorRadius = MinorRadius;
}


//=======================================================================
//function : Hypr
//purpose  : 
//=======================================================================

gp_Hypr Geom_Hyperbola::Hypr () const 
{
  return gp_Hypr (pos, majorRadius, minorRadius);
}

//=======================================================================
//function : ReversedParameter
//purpose  : 
//=======================================================================

Standard_Real Geom_Hyperbola::ReversedParameter( const Standard_Real U) const 
{
  return ( -U);
}

//=======================================================================
//function : Asymptote1
//purpose  : 
//=======================================================================

Ax1 Geom_Hyperbola::Asymptote1 () const {

  gp_Hypr Hv (pos, majorRadius, minorRadius);
  return Hv.Asymptote1();
}


//=======================================================================
//function : Asymptote2
//purpose  : 
//=======================================================================

Ax1 Geom_Hyperbola::Asymptote2 () const {

  gp_Hypr Hv (pos, majorRadius, minorRadius);
  return Hv.Asymptote2();
}


//=======================================================================
//function : ConjugateBranch1
//purpose  : 
//=======================================================================

gp_Hypr Geom_Hyperbola::ConjugateBranch1 () const {

  gp_Hypr Hv (pos, majorRadius, minorRadius);
  return Hv.ConjugateBranch1();
}

//=======================================================================
//function : ConjugateBranch2
//purpose  : 
//=======================================================================

gp_Hypr Geom_Hyperbola::ConjugateBranch2 () const {

  gp_Hypr Hv (pos, majorRadius, minorRadius);
  return Hv.ConjugateBranch2();
}


//=======================================================================
//function : Directrix1
//purpose  : 
//=======================================================================

Ax1 Geom_Hyperbola::Directrix1 () const {

  gp_Hypr Hv (pos, majorRadius, minorRadius);
  return Hv.Directrix1();
}

//=======================================================================
//function : Directrix2
//purpose  : 
//=======================================================================

Ax1 Geom_Hyperbola::Directrix2 () const {

  gp_Hypr Hv (pos, majorRadius, minorRadius);
  return Hv.Directrix2();
}

//=======================================================================
//function : D0
//purpose  : 
//=======================================================================

void Geom_Hyperbola::D0 (const Standard_Real U, Pnt& P) const {

  P = ElCLib::HyperbolaValue (U, pos, majorRadius, minorRadius);
}

//=======================================================================
//function : D1
//purpose  : 
//=======================================================================

void Geom_Hyperbola::D1 (const Standard_Real U, Pnt& P, Vec& V1) const {

  ElCLib::HyperbolaD1 (U, pos, majorRadius, minorRadius, P, V1);
}

//=======================================================================
//function : D2
//purpose  : 
//=======================================================================

void Geom_Hyperbola::D2 (const Standard_Real U, Pnt& P, Vec& V1, Vec& V2) const {

  ElCLib::HyperbolaD2 (U, pos, majorRadius, minorRadius, P, V1, V2);
}

//=======================================================================
//function : D3
//purpose  : 
//=======================================================================

void Geom_Hyperbola::D3 (
const Standard_Real U, Pnt& P, Vec& V1, Vec& V2, Vec& V3) const {

  ElCLib::HyperbolaD3 (U, pos, majorRadius, minorRadius, P, V1, V2, V3);
}

//=======================================================================
//function : DN
//purpose  : 
//=======================================================================

Vec Geom_Hyperbola::DN (const Standard_Real U, const Standard_Integer N) const {

  Standard_RangeError_Raise_if (N < 1, " ");  
  return ElCLib::HyperbolaDN (U, pos, majorRadius, minorRadius, N);
}

//=======================================================================
//function : Eccentricity
//purpose  : 
//=======================================================================

Standard_Real Geom_Hyperbola::Eccentricity () const {

  Standard_ConstructionError_Raise_if (majorRadius == 0.0, " ")  
  return (Sqrt(majorRadius*majorRadius + minorRadius*minorRadius))/majorRadius;
}

//=======================================================================
//function : Focal
//purpose  : 
//=======================================================================

Standard_Real Geom_Hyperbola::Focal () const {

  return 2.0 * Sqrt(majorRadius * majorRadius + minorRadius * minorRadius);
}

//=======================================================================
//function : Focus1
//purpose  : 
//=======================================================================

Pnt Geom_Hyperbola::Focus1 () const {

  Standard_Real C = Sqrt(majorRadius * majorRadius + minorRadius * minorRadius);
  Standard_Real Xp, Yp, Zp, Xd, Yd, Zd;
  pos.Location().Coord (Xp, Yp, Zp);
  pos.XDirection().Coord (Xd, Yd, Zd);
  return Pnt (Xp + C * Xd,  Yp + C * Yd, Zp + C * Zd);
}

//=======================================================================
//function : Focus2
//purpose  : 
//=======================================================================

Pnt Geom_Hyperbola::Focus2 () const {

  Standard_Real C = Sqrt(majorRadius * majorRadius + minorRadius * minorRadius);
  Standard_Real Xp, Yp, Zp, Xd, Yd, Zd;
  pos.Location().Coord (Xp, Yp, Zp);
  pos.XDirection().Coord (Xd, Yd, Zd);
  return Pnt (Xp - C * Xd,  Yp - C * Yd, Zp - C * Zd);
}

//=======================================================================
//function : OtherBranch
//purpose  : 
//=======================================================================

gp_Hypr Geom_Hyperbola::OtherBranch () const {

   gp_Hypr Hv (pos, majorRadius, minorRadius);
   return Hv.OtherBranch ();
}

//=======================================================================
//function : Parameter
//purpose  : 
//=======================================================================

Standard_Real Geom_Hyperbola::Parameter () const {

   Standard_ConstructionError_Raise_if (majorRadius == 0.0, " ");  
   return (minorRadius * minorRadius)/majorRadius;
}

//=======================================================================
//function : Transform
//purpose  : 
//=======================================================================

void Geom_Hyperbola::Transform (const Trsf& T) {

  majorRadius = majorRadius * Abs(T.ScaleFactor());
  minorRadius = minorRadius * Abs(T.ScaleFactor());
  pos.Transform(T);
}
