// Created on: 1993-03-25
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


// Passage en classe persistante - 23/01/91
// Modif suite a la deuxieme revue de projet toolkit Geometry -23/01/91
// Infos :
// Actuellement pour les champs de la courbe le tableau des poles est 
// declare de 1 a NbPoles et le tableau des poids est declare de 1 a NbPoles


// Revised RLE  Aug 19 1993
// Suppressed Swaps, added Init, removed typedefs

#define No_Standard_OutOfRange
#define No_Standard_DimensionError

#include <Geom2d_BezierCurve.ixx>
#include <PLib.hxx>
#include <BSplCLib.hxx>
#include <gp.hxx>
#include <gp_XY.hxx>
#include <Standard_ConstructionError.hxx>
#include <Standard_DimensionError.hxx>
#include <Standard_OutOfRange.hxx>
#include <Standard_RangeError.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>

//=======================================================================
//function : Rational
//purpose  : check rationality of an array of weights
//=======================================================================

static Standard_Boolean Rational(const TColStd_Array1OfReal& W)
{
  Standard_Integer i, n = W.Length();
  Standard_Boolean rat = Standard_False;
  for (i = 1; i < n; i++) {
    rat =  Abs(W(i) - W(i+1)) > gp::Resolution();
    if (rat) break;
  }
  return rat;
}


//=======================================================================
//function : Geom2d_BezierCurve
//purpose  : 
//=======================================================================

Geom2d_BezierCurve::Geom2d_BezierCurve
 (const TColgp_Array1OfPnt2d& Poles):
 validcache(0), parametercache(0.), spanlenghtcache(1.)
{
  //  copy the poles
  
  Handle(TColgp_HArray1OfPnt2d) npoles =
    new TColgp_HArray1OfPnt2d(1,Poles.Length());
  
  npoles->ChangeArray1() = Poles;
  
  // Init non rational
  Init(npoles,
       Handle(TColStd_HArray1OfReal)());
}


//=======================================================================
//function : Geom2d_BezierCurve
//purpose  : 
//=======================================================================

Geom2d_BezierCurve::Geom2d_BezierCurve
(const TColgp_Array1OfPnt2d&  Poles, 
 const TColStd_Array1OfReal& Weights):
 validcache(0), parametercache(0.), spanlenghtcache(1.)

{
  // copy the poles
  
  Handle(TColgp_HArray1OfPnt2d) npoles =
    new TColgp_HArray1OfPnt2d(1,Poles.Length());
  
  npoles->ChangeArray1()   = Poles;
  
  
  // check  the weights
  
  Standard_Integer nbpoles = Poles.Length();
  
  if (Weights.Length() != nbpoles)
    Standard_ConstructionError::Raise();
  
  Standard_Integer i;
  for (i = 1; i <= nbpoles; i++) {
    if (Weights(i) <= gp::Resolution()) {
      Standard_ConstructionError::Raise();
    }
  }
  
  // check really rational
  Standard_Boolean rat = Rational(Weights);
  
  // copy the weights
  Handle(TColStd_HArray1OfReal) nweights;
  if (rat) {
    nweights = new TColStd_HArray1OfReal(1,nbpoles);
    nweights->ChangeArray1() = Weights;
  }
  
  // Init
  Init(npoles,nweights);
}


//=======================================================================
//function : Increase
//purpose  : increase degree
//=======================================================================

void Geom2d_BezierCurve::Increase (const Standard_Integer Deg)
{
  if (Deg == Degree()) return;
  
  Standard_ConstructionError_Raise_if
    (Deg < Degree() ||
     Deg > Geom2d_BezierCurve::MaxDegree(), "Geom2d_BezierCurve::Increase");
  
  Handle(TColgp_HArray1OfPnt2d) npoles =
    new TColgp_HArray1OfPnt2d(1,Deg+1);
  
  Handle(TColStd_HArray1OfReal) nweights;
  
  TColStd_Array1OfReal bidknots(1,2); bidknots(1) = 0.; bidknots(2) = 1.;
  TColStd_Array1OfInteger bidmults(1,2); bidmults.Init(Degree() + 1);
  
  if (IsRational()) {
    nweights = new TColStd_HArray1OfReal(1,Deg+1);
    BSplCLib::IncreaseDegree(Degree(), Deg, 0,
			     poles->Array1(),weights->Array1(),
			     bidknots, bidmults,
			     npoles->ChangeArray1(),nweights->ChangeArray1(),
			     bidknots, bidmults);
  }
  else {
    BSplCLib::IncreaseDegree(Degree(), Deg, 0,
			     poles->Array1(),
			     *((TColStd_Array1OfReal*) NULL),
			     bidknots, bidmults,
			     npoles->ChangeArray1(),
			     *((TColStd_Array1OfReal*) NULL),
			     bidknots, bidmults);
  }
  
  Init(npoles,nweights);
}


//=======================================================================
//function : MaxDegree
//purpose  : 
//=======================================================================

Standard_Integer Geom2d_BezierCurve::MaxDegree () 
{ 
  return BSplCLib::MaxDegree(); 
}


//=======================================================================
//function : InsertPoleAfter
//purpose  : 
//=======================================================================

void Geom2d_BezierCurve::InsertPoleAfter
(const Standard_Integer Index,
 const gp_Pnt2d& P,
 const Standard_Real Weight)
{
  Standard_Integer nbpoles = NbPoles();
  
  Standard_ConstructionError_Raise_if
    (nbpoles >= Geom2d_BezierCurve::MaxDegree() ||
     Weight <= gp::Resolution(), 
     "Geom2d_BezierCurve::InsertPoleAfter" );
  
  Standard_OutOfRange_Raise_if
    (Index < 0 || Index > nbpoles,
     "Geom2d_BezierCurve::InsertPoleAfter");
  
  Standard_Integer i;
  
  // Insert the pole
  Handle(TColgp_HArray1OfPnt2d) npoles =
    new TColgp_HArray1OfPnt2d(1,nbpoles+1);
  
  TColgp_Array1OfPnt2d&        newpoles = npoles->ChangeArray1();
  const TColgp_Array1OfPnt2d& oldpoles  = poles->Array1();
  
  for (i = 1; i <= Index; i++)
    newpoles(i) = oldpoles(i);
  
  newpoles(Index+1) = P;
  
  for (i = Index+1; i <= nbpoles; i++)
    newpoles(i+1) = oldpoles(i);
  
  
  // Insert the weight
  Handle(TColStd_HArray1OfReal) nweights;
  Standard_Boolean rat = IsRational() || Abs(Weight-1.) > gp::Resolution();
  
  if (rat) {
    nweights = new TColStd_HArray1OfReal(1,nbpoles+1);
    TColStd_Array1OfReal& newweights = nweights->ChangeArray1();
    
    for (i = 1; i <= Index; i++)
      if (IsRational())
	newweights(i) = weights->Value(i);
      else
	newweights(i) = 1.;
    
    newweights(Index+1) = Weight;
    
    for (i = Index+1; i <= nbpoles; i++)
      if (IsRational())
	newweights(i+1) = weights->Value(i);
      else
	newweights(i+1) = 1.;
  }
  
  
  Init(npoles,nweights);
}


//=======================================================================
//function : InsertPoleBefore
//purpose  : 
//=======================================================================

void Geom2d_BezierCurve::InsertPoleBefore
(const Standard_Integer Index,
 const gp_Pnt2d& P,
 const Standard_Real Weight)
{
  InsertPoleAfter(Index-1,P,Weight);
}


//=======================================================================
//function : RemovePole
//purpose  : 
//=======================================================================

void Geom2d_BezierCurve::RemovePole
(const Standard_Integer Index)
{
  Standard_Integer nbpoles = NbPoles();
  
  Standard_ConstructionError_Raise_if
    (nbpoles <= 2 , "Geom2d_BezierCurve::RemovePole" );
  
  Standard_OutOfRange_Raise_if
    (Index < 1 || Index > nbpoles,
     "Geom2d_BezierCurve::RemovePole");
  
  Standard_Integer i;
  
  // Remove the pole
  Handle(TColgp_HArray1OfPnt2d) npoles =
    new TColgp_HArray1OfPnt2d(1,nbpoles-1);
  
  TColgp_Array1OfPnt2d&        newpoles = npoles->ChangeArray1();
  const TColgp_Array1OfPnt2d& oldpoles  = poles->Array1();
  
  for (i = 1; i < Index; i++)
    newpoles(i) = oldpoles(i);
  
  for (i = Index+1; i <= nbpoles; i++)
    newpoles(i-1) = oldpoles(i);
  
  
  // Remove the weight
  Handle(TColStd_HArray1OfReal) nweights;
  
  if (IsRational()) {
    nweights = new TColStd_HArray1OfReal(1,nbpoles-1);
    TColStd_Array1OfReal&       newweights = nweights->ChangeArray1();
    const TColStd_Array1OfReal& oldweights = weights->Array1();
    
    for (i = 1; i < Index; i++)
      newweights(i) = oldweights(i);
    
    for (i = Index+1; i <= nbpoles; i++)
      newweights(i-1) = oldweights(i);
  }
  
  Init(npoles,nweights);
}


//=======================================================================
//function : Reverse
//purpose  : 
//=======================================================================

void Geom2d_BezierCurve::Reverse ()
{
  gp_Pnt2d P;
  Standard_Integer i, nbpoles = NbPoles();
  TColgp_Array1OfPnt2d & cpoles = poles->ChangeArray1();
  
  // reverse poles
  for (i = 1; i <= nbpoles / 2; i++) {
    P = cpoles(i);
    cpoles(i) = cpoles(nbpoles-i+1);
    cpoles(nbpoles-i+1) = P;
  }
  
  // reverse weights
  if (IsRational()) {
    TColStd_Array1OfReal & cweights = weights->ChangeArray1();
    Standard_Real w;
    for (i = 1; i <= nbpoles / 2; i++) {
      w = cweights(i);
      cweights(i) = cweights(nbpoles-i+1);
      cweights(nbpoles-i+1) = w;
    }
  }
  
  UpdateCoefficients();
}


//=======================================================================
//function : ReversedParameter
//purpose  : 
//=======================================================================

Standard_Real Geom2d_BezierCurve::ReversedParameter
( const Standard_Real U) const 
{
  return ( 1. - U);
}


//=======================================================================
//function : Segment
//purpose  : 
//=======================================================================

void Geom2d_BezierCurve::Segment
(const Standard_Real U1, const Standard_Real U2)
{
  closed =  (Abs(Value(U1).Distance (Value(U2))) <= gp::Resolution());
//
//   WARNING : when calling trimming be carefull that the cache
//   is computed regarding 0.0e0 and not 1.0e0 
//

  if (IsRational()) {
    PLib::Trimming(U1,U2,coeffs->ChangeArray1(),wcoeffs->ChangeArray1());
    PLib::CoefficientsPoles(coeffs->Array1(),wcoeffs->Array1(),
			    poles->ChangeArray1(),weights->ChangeArray1());
  }
  else {
    PLib::Trimming(U1,U2,coeffs->ChangeArray1(),
		   *((TColStd_Array1OfReal*) NULL));
    PLib::CoefficientsPoles(coeffs->Array1(),
			    *((TColStd_Array1OfReal*) NULL),
			    poles->ChangeArray1(),
			    *((TColStd_Array1OfReal*) NULL));
  }
  UpdateCoefficients();
}


//=======================================================================
//function : SetPole
//purpose  : 
//=======================================================================

void Geom2d_BezierCurve::SetPole
(const Standard_Integer Index,
 const gp_Pnt2d& P)
{
  Standard_OutOfRange_Raise_if (Index < 1 || Index > NbPoles(),
				"Geom2d_BezierCurve::SetPole");
  
  TColgp_Array1OfPnt2d& cpoles = poles->ChangeArray1();
  cpoles(Index) = P;
  
  if (Index == 1 || Index == cpoles.Length()) {
    closed = (cpoles(1).Distance(cpoles(NbPoles())) <= gp::Resolution());
  }
  
  UpdateCoefficients();
}


//=======================================================================
//function : SetPole
//purpose  : 
//=======================================================================

void Geom2d_BezierCurve::SetPole
(const Standard_Integer Index,
 const gp_Pnt2d& P,
 const Standard_Real Weight)
{
  SetPole(Index,P);
  SetWeight(Index,Weight);
}


//=======================================================================
//function : SetWeight
//purpose  : 
//=======================================================================

void Geom2d_BezierCurve::SetWeight
(const Standard_Integer Index,
 const Standard_Real Weight)
{
  Standard_Integer nbpoles = NbPoles();
  
  Standard_OutOfRange_Raise_if
    (Index < 1 || Index > nbpoles,
     "Geom2d_BezierCurve::SetWeight");
  Standard_ConstructionError_Raise_if
    (Weight <= gp::Resolution (),
     "Geom2d_BezierCurve::SetWeight");
  
  
  // compute new rationality
  Standard_Boolean wasrat = IsRational();
  if (!wasrat) {
    // a weight of 1. does not turn to rational
    if (Abs(Weight - 1.) <= gp::Resolution()) return;
    
    // set weights of 1.
    weights = new TColStd_HArray1OfReal(1,nbpoles);
    wcoeffs = new TColStd_HArray1OfReal(1,nbpoles);
    weights->Init(1.);
  }
  
  TColStd_Array1OfReal & cweights = weights->ChangeArray1();
  cweights(Index) = Weight;
  
  // is it turning into non rational
  if (wasrat) {
    if (!Rational(cweights)) {
      weights.Nullify();
      wcoeffs.Nullify();
    }
  }
  
  UpdateCoefficients();
}


//=======================================================================
//function : IsClosed
//purpose  : 
//=======================================================================

Standard_Boolean Geom2d_BezierCurve::IsClosed () const 
{
  return closed; 
}


//=======================================================================
//function : IsCN
//purpose  : 
//=======================================================================

Standard_Boolean Geom2d_BezierCurve::IsCN (const Standard_Integer ) const 
{
  return Standard_True; 
}


//=======================================================================
//function : IsPeriodic
//purpose  : 
//=======================================================================

Standard_Boolean Geom2d_BezierCurve::IsPeriodic () const 
{
  return Standard_False; 
}


//=======================================================================
//function : IsRational
//purpose  : 
//=======================================================================

Standard_Boolean Geom2d_BezierCurve::IsRational () const 
{  
  return !weights.IsNull(); 
}


//=======================================================================
//function : Continuity
//purpose  : 
//=======================================================================

GeomAbs_Shape Geom2d_BezierCurve::Continuity () const 
{ 
  return GeomAbs_CN; 
}


//=======================================================================
//function : Degree
//purpose  : 
//=======================================================================

Standard_Integer Geom2d_BezierCurve::Degree () const 
{
  return poles->Length()-1;
}


//=======================================================================
//function : D0
//purpose  : 
//=======================================================================

void Geom2d_BezierCurve::D0 (const Standard_Real U, gp_Pnt2d& P ) const
{
//  Idee lumineuse sacrifiee sur l autel des performances.
//
//  if(!CoefficientsOK(U)) 
//    ((Geom2d_BezierCurve*)(void*)this)->UpdateCoefficients(U);
  if (IsRational())
    BSplCLib::CacheD0(U,Degree(),parametercache,spanlenghtcache,
		      coeffs->Array1(),wcoeffs->Array1(),P);
  else 
    BSplCLib::CacheD0(U,Degree(),parametercache,spanlenghtcache,
		      coeffs->Array1(),
		      *((TColStd_Array1OfReal*) NULL),
		      P);
}

//=======================================================================
//function : D1
//purpose  : 
//=======================================================================

void Geom2d_BezierCurve::D1(const Standard_Real U, 
			    gp_Pnt2d& P, 
			    gp_Vec2d& V1) const
{
//  Idee lumineuse sacrifiee sur l autel des performances.
//
//  if(!CoefficientsOK(U)) 
//    ((Geom2d_BezierCurve*)(void*)this)->UpdateCoefficients(U);
  if (IsRational())
    BSplCLib::CacheD1(U,Degree(),parametercache,spanlenghtcache,
		      coeffs->Array1(),wcoeffs->Array1(),P,V1);
  else 
    BSplCLib::CacheD1(U,Degree(),parametercache,spanlenghtcache,
		      coeffs->Array1(),
		      *((TColStd_Array1OfReal*) NULL),
		      P,V1);
}

//=======================================================================
//function : D2
//purpose  : 
//=======================================================================

void Geom2d_BezierCurve::D2 (const Standard_Real U,
			     gp_Pnt2d& P,
			     gp_Vec2d& V1,
			     gp_Vec2d& V2) const
{
//  Idee lumineuse sacrifiee sur l autel des performances.
//
//  if(!CoefficientsOK(U)) 
//    ((Geom2d_BezierCurve*)(void*)this)->UpdateCoefficients(U);
  if (IsRational())
    BSplCLib::CacheD2(U,Degree(),parametercache,spanlenghtcache,
		      coeffs->Array1(),wcoeffs->Array1(),P,V1,V2);
  else 
    BSplCLib::CacheD2(U,Degree(),parametercache,spanlenghtcache,
		      coeffs->Array1(),
		      *((TColStd_Array1OfReal*) NULL),
		      P,V1,V2);
}

//=======================================================================
//function : D3
//purpose  : 
//=======================================================================

void Geom2d_BezierCurve::D3 (const Standard_Real U,
			     gp_Pnt2d& P,
			     gp_Vec2d& V1,
			     gp_Vec2d& V2,
			     gp_Vec2d& V3) const
{
//  Idee lumineuse sacrifiee sur l autel des performances.
//
//  if(!CoefficientsOK(U)) 
//    ((Geom2d_BezierCurve*)(void*)this)->UpdateCoefficients(U);
  if (IsRational())
    BSplCLib::CacheD3(U,Degree(),parametercache,spanlenghtcache,
		      coeffs->Array1(),wcoeffs->Array1(),P,V1,V2,V3);
  else 
    BSplCLib::CacheD3(U,Degree(),parametercache,spanlenghtcache,
		      coeffs->Array1(),
		      *((TColStd_Array1OfReal*) NULL),
		      P,V1,V2,V3);
}

//=======================================================================
//function : DN
//purpose  : 
//=======================================================================

gp_Vec2d Geom2d_BezierCurve::DN (const Standard_Real U,
				 const Standard_Integer N) const
{
  Standard_RangeError_Raise_if (N < 1, "Geom2d_BezierCurve::DN");
  gp_Vec2d V;
  
  TColStd_Array1OfReal bidknots(1,2); bidknots(1) = 0.; bidknots(2) = 1.;
  TColStd_Array1OfInteger bidmults(1,2); bidmults.Init(Degree() + 1);
  
  if (IsRational())
    BSplCLib::DN(U,N,0,Degree(),Standard_False,
		 poles->Array1(),weights->Array1(),
		 bidknots,bidmults,V);
  else 
    BSplCLib::DN(U,N,0,Degree(),Standard_False,
		 poles->Array1(),
		 *((TColStd_Array1OfReal*) NULL),
		 bidknots,bidmults,V);
  return V;
}

//=======================================================================
//function : EndPoint
//purpose  : 
//=======================================================================

gp_Pnt2d Geom2d_BezierCurve::EndPoint () const
{
  return poles->Value (poles->Upper());
}


//=======================================================================
//function : FirstParameter
//purpose  : 
//=======================================================================

Standard_Real Geom2d_BezierCurve::FirstParameter () const 
{
  return 0.0; 
}


//=======================================================================
//function : LastParameter
//purpose  : 
//=======================================================================

Standard_Real Geom2d_BezierCurve::LastParameter () const 
{
  return 1.0; 
}


//=======================================================================
//function : NbPoles
//purpose  : 
//=======================================================================

Standard_Integer Geom2d_BezierCurve::NbPoles () const 
{
  return poles->Length(); 
}


//=======================================================================
//function : Pole
//purpose  : 
//=======================================================================

gp_Pnt2d Geom2d_BezierCurve::Pole (const Standard_Integer Index) const
{
  Standard_OutOfRange_Raise_if (Index < 1 || Index > poles->Length(),
				"Geom2d_BezierCurve::Pole");
  return poles->Value(Index);
}


//=======================================================================
//function : Poles
//purpose  : 
//=======================================================================

void Geom2d_BezierCurve::Poles (TColgp_Array1OfPnt2d& P) const
{
  Standard_DimensionError_Raise_if (P.Length() != poles->Length(),
				    "Geom2d_BezierCurve::Poles");
  P = poles->Array1();
}


//=======================================================================
//function : StartPoint
//purpose  : 
//=======================================================================

gp_Pnt2d Geom2d_BezierCurve::StartPoint () const
{
  return poles->Value(1);
}


//=======================================================================
//function : Weight
//purpose  : 
//=======================================================================

Standard_Real Geom2d_BezierCurve::Weight
(const Standard_Integer Index) const
{
  Standard_OutOfRange_Raise_if (Index < 1 || Index > weights->Length(),
				"Geom2d_BezierCurve::Weight");
  if (IsRational())
    return weights->Value(Index);
  else
    return 1.;
}


//=======================================================================
//function : Weights
//purpose  : 
//=======================================================================

void Geom2d_BezierCurve::Weights
(TColStd_Array1OfReal& W) const
{
  
  Standard_Integer nbpoles = NbPoles();
  Standard_DimensionError_Raise_if (W.Length() != nbpoles,
				    "Geom2d_BezierCurve::Weights");
  if (IsRational())
    W = weights->Array1();
  else {
    Standard_Integer i;
    for (i = 1; i <= nbpoles; i++)
      W(i) = 1.;
  }
}


//=======================================================================
//function : Transform
//purpose  : 
//=======================================================================

void Geom2d_BezierCurve::Transform (const gp_Trsf2d& T)
{
  Standard_Integer nbpoles = NbPoles();
  TColgp_Array1OfPnt2d & cpoles = poles->ChangeArray1();
  
  for (Standard_Integer i = 1; i <= nbpoles; i++) 
    cpoles (i).Transform(T);
  
  UpdateCoefficients();
}


//=======================================================================
//function : Resolution
//purpose  : 
//=======================================================================

void Geom2d_BezierCurve::Resolution(const Standard_Real ToleranceUV,
				    Standard_Real &     UTolerance)
{
  if(!maxderivinvok){
    TColStd_Array1OfReal bidflatknots(1, 2*(Degree()+1));
    for(Standard_Integer i = 1; i <= Degree()+1; i++){
      bidflatknots(i) = 0.;
      bidflatknots(i + Degree() +1) = 1.;
    }
    
    if (IsRational()) {  
      BSplCLib::Resolution(poles->Array1(),
			   weights->Array1(),
			   poles->Length(),
			   bidflatknots,
			   Degree(),
			   1.,
			   maxderivinv) ;
    }
    else {
      BSplCLib::Resolution(poles->Array1(),
			   *((TColStd_Array1OfReal*) NULL),
			   poles->Length(),
			   bidflatknots,
			   Degree(),
			   1.,
			   maxderivinv) ;
    }
    maxderivinvok = 1;
  }
  UTolerance = ToleranceUV * maxderivinv;
}


//=======================================================================
//function : Copy
//purpose  : 
//=======================================================================

Handle(Geom2d_Geometry) Geom2d_BezierCurve::Copy() const {
  
  Handle(Geom2d_BezierCurve) C;
  if (IsRational())
    C = new Geom2d_BezierCurve (poles->Array1(),weights->Array1());
  else
    C = new Geom2d_BezierCurve (poles->Array1());
  return C;
}


//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void Geom2d_BezierCurve::Init
(const Handle(TColgp_HArray1OfPnt2d)&   Poles, 
 const Handle(TColStd_HArray1OfReal)& Weights)
{
  Standard_Integer nbpoles = Poles->Length();
  // closed ?
  const TColgp_Array1OfPnt2d&   cpoles   = Poles->Array1();
  closed = cpoles(1).Distance(cpoles(nbpoles)) <= gp::Resolution(); 
  
  // rational
  rational = !Weights.IsNull();
  
  // set fields
  poles   = Poles;
  coeffs  = new TColgp_HArray1OfPnt2d  (1,nbpoles);
  
  if (rational) {
    weights = Weights;
    wcoeffs = new TColStd_HArray1OfReal (1, nbpoles, 0.0);
  }
  else {
    weights.Nullify();
    wcoeffs.Nullify();
  }
  
  UpdateCoefficients();
}


//=======================================================================
//function : CoefficientsOK
//purpose  : 
//=======================================================================

//Standard_Boolean Geom2d_BezierCurve::CoefficientsOK(const Standard_Real U)const
Standard_Boolean Geom2d_BezierCurve::CoefficientsOK(const Standard_Real )const
{
  return (validcache) ;
			
}


//=======================================================================
//function : UpdateCoefficients
//purpose  : 
//=======================================================================

//void Geom2d_BezierCurve::UpdateCoefficients(const Standard_Real U)
void Geom2d_BezierCurve::UpdateCoefficients(const Standard_Real )
{
  maxderivinvok = 0;
  parametercache = 0.;
//  
//  Idee lumineuse sacrifiee sur l autel des performances.
//  if (U >= 1.) parametercache = 1.;
  TColStd_Array1OfReal bidflatknots(BSplCLib::FlatBezierKnots(Degree()),
				    1, 2*(Degree()+1));
  if (IsRational())
    BSplCLib::BuildCache(parametercache,spanlenghtcache,0,Degree(),
			 bidflatknots,poles->Array1(),weights->Array1(),
			 coeffs->ChangeArray1(),wcoeffs->ChangeArray1());
  else
    BSplCLib::BuildCache(parametercache,spanlenghtcache,0,Degree(),
			 bidflatknots,poles->Array1(),
			 *((TColStd_Array1OfReal*) NULL),
			 coeffs->ChangeArray1(),
			 *((TColStd_Array1OfReal*) NULL));
  validcache = 1;
}

