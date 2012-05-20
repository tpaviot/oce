// Created on: 1994-02-17
// Created by: Bruno DUMORTIER
// Copyright (c) 1994-1999 Matra Datavision
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


#include <GeomFill_Profiler.ixx>
#include <GeomConvert.hxx>
#include <BSplCLib.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_Conic.hxx>
#include <GeomConvert_ApproxCurve.hxx>


//=======================================================================
//function : GeomFill_Profiler
//purpose  : 
//=======================================================================

GeomFill_Profiler::GeomFill_Profiler()
{
  myIsDone = Standard_False;
  myIsPeriodic = Standard_True;
}


//=======================================================================

void GeomFill_Profiler::Delete()
{}


//=======================================================================
//function : AddCurve
//purpose  : 
//=======================================================================

void GeomFill_Profiler::AddCurve(const Handle(Geom_Curve)& Curve)
{
  Handle(Geom_Curve) C;
  //// modified by jgv, 19.01.05 for OCC7354 ////
  Handle(Geom_Curve) theCurve = Curve;
  if (theCurve->IsInstance(STANDARD_TYPE(Geom_TrimmedCurve)))
    theCurve = (*((Handle(Geom_TrimmedCurve)*)&theCurve))->BasisCurve();
  if (theCurve->IsKind(STANDARD_TYPE(Geom_Conic)))
    {
      GeomConvert_ApproxCurve appr(Curve, Precision::Confusion(), GeomAbs_C1, 16, 14);
      if (appr.HasResult())
	C = appr.Curve();
    }
  if (C.IsNull())
    C = GeomConvert::CurveToBSplineCurve(Curve);
  /*
  if ( Curve->IsKind(STANDARD_TYPE(Geom_BSplineCurve))) {
    C = Handle(Geom_Curve)::DownCast(Curve->Copy());
  }
  else {
    C = GeomConvert::CurveToBSplineCurve(Curve,Convert_QuasiAngular);
  }
  */
  ///////////////////////////////////////////////

  mySequence.Append( C);

  if ( myIsPeriodic && !C->IsPeriodic())
    myIsPeriodic = Standard_False;
}


//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================

void GeomFill_Profiler::Perform(const Standard_Real PTol)
{
  Standard_Integer i;
//  Standard_Integer myDegree = 0, myNbPoles = 0;
  Standard_Integer myDegree = 0;
  Handle(Geom_BSplineCurve) C;
  Standard_Real U1, U2, UFirst=0, ULast=0;
  Standard_Real EcartMax = 0.;

  for ( i = 1; i <= mySequence.Length(); i++) {
    C = Handle(Geom_BSplineCurve)::DownCast(mySequence(i));

    // si non periodique, il faut deperiodiser toutes les courbes
    // on les segmente ensuite pour assurer K(1) et K(n) de multiplicite
    // degre + 1

    U2 = C->Knot(C->LastUKnotIndex());
    U1 = C->Knot(C->FirstUKnotIndex());

    if ( !myIsPeriodic && C->IsPeriodic()) {
      C->SetNotPeriodic();
      C->Segment( U1, U2);
    }

    // evaluate the max degree
    myDegree = Max( myDegree, C->Degree());
    
    // Calcul de Max ( Ufin - Udeb) sur l ensemble des courbes.
    if ( ( U2 - U1) > EcartMax) {
      EcartMax = U2 - U1;
      UFirst = U1;
      ULast  = U2;
    }
  }
  
  // increase the degree of the curves to my degree
  // reparametrize them in the range U1, U2.
  for ( i = 1; i <= mySequence.Length(); i++) {
    C = Handle(Geom_BSplineCurve)::DownCast(mySequence(i));

    C->IncreaseDegree( myDegree);

    TColStd_Array1OfReal Knots(1,C->NbKnots());
    C->Knots(Knots);
    BSplCLib::Reparametrize(UFirst,ULast,Knots);
    C->SetKnots(Knots);
  }
  
  // inserting in the first curve the knot-vector of all the others.
  C = Handle(Geom_BSplineCurve)::DownCast(mySequence(1));

  for ( i = 2; i <= mySequence.Length(); i++) {
    Handle(Geom_BSplineCurve) Ci = 
      Handle(Geom_BSplineCurve)::DownCast(mySequence(i));
    TColStd_Array1OfReal Ki(1,Ci->NbKnots());
    Ci->Knots(Ki);
    TColStd_Array1OfInteger Mi(1,Ci->NbKnots());
    Ci->Multiplicities(Mi);

    C->InsertKnots( Ki, Mi, PTol, Standard_False);
  }

  TColStd_Array1OfReal NewKnots(1,C->NbKnots());
  C->Knots(NewKnots);
  TColStd_Array1OfInteger NewMults(1,C->NbKnots());
  C->Multiplicities(NewMults);
  for ( i = 2; i <= mySequence.Length(); i++) {
    Handle(Geom_BSplineCurve) Ci = 
      Handle(Geom_BSplineCurve)::DownCast(mySequence(i));
    Ci->InsertKnots(NewKnots, NewMults, PTol, Standard_False);
  }

  // essai : tentative mise des poids sur chaque section a une moyenne 1
  for ( i = 1; i <= mySequence.Length(); i++) {
    Handle(Geom_BSplineCurve) Ci = 
      Handle(Geom_BSplineCurve)::DownCast(mySequence(i));
    if ( Ci->IsRational() ) {
      Standard_Integer np = Ci->NbPoles();
      Standard_Real sigma = 0.;
      Standard_Integer j;
      for ( j = 1; j <= np; j++) {
	sigma += Ci->Weight(j);
      }
      sigma /= np;
      for ( j= 1; j<= np; j++) {
	Ci->SetWeight(j,Ci->Weight(j) / sigma);
      }
    }
  }
  // fin de l essai

  myIsDone = Standard_True;
}


//=======================================================================
//function : Degree
//purpose  : 
//=======================================================================

Standard_Integer GeomFill_Profiler::Degree() const 
{
  if ( !myIsDone)
    StdFail_NotDone::Raise("GeomFill_Profiler::Degree");

  Handle(Geom_BSplineCurve) C = 
    Handle(Geom_BSplineCurve)::DownCast(mySequence(1));
  return C->Degree();
}


//=======================================================================
//function : NbPoles
//purpose  : 
//=======================================================================

Standard_Integer GeomFill_Profiler::NbPoles() const 
{
  if ( !myIsDone)
    StdFail_NotDone::Raise("GeomFill_Profiler::Degree");

  Handle(Geom_BSplineCurve) C = 
    Handle(Geom_BSplineCurve)::DownCast(mySequence(1));
  return C->NbPoles();
}


//=======================================================================
//function : Poles
//purpose  : 
//=======================================================================

void GeomFill_Profiler::Poles(const Standard_Integer Index, 
			            TColgp_Array1OfPnt& Poles) const 
{
  if ( !myIsDone)
    StdFail_NotDone::Raise("GeomFill_Profiler::Degree");

  Standard_DomainError_Raise_if( Poles.Length() != NbPoles(),
				"GeomFill_Profiler::Poles");
  Standard_DomainError_Raise_if( Index < 1 || Index > mySequence.Length(),
				"GeomFill_Profiler::Poles");

  Handle(Geom_BSplineCurve) C = 
    Handle(Geom_BSplineCurve)::DownCast(mySequence(Index));

  C->Poles(Poles);
}


//=======================================================================
//function : Weights
//purpose  : 
//=======================================================================

void GeomFill_Profiler::Weights(const Standard_Integer      Index, 
				      TColStd_Array1OfReal& Weights) const 
{
  if ( !myIsDone)
    StdFail_NotDone::Raise("GeomFill_Profiler::Degree");

  Standard_DomainError_Raise_if( Weights.Length() != NbPoles(),
				"GeomFill_Profiler::Weights");
  Standard_DomainError_Raise_if( Index < 1 || Index > mySequence.Length(),
				"GeomFill_Profiler::Weights");

  Handle(Geom_BSplineCurve) C = 
    Handle(Geom_BSplineCurve)::DownCast(mySequence(Index));

  C->Weights(Weights);
}


//=======================================================================
//function : NbKnots
//purpose  : 
//=======================================================================

Standard_Integer GeomFill_Profiler::NbKnots() const 
{
  if ( !myIsDone)
    StdFail_NotDone::Raise("GeomFill_Profiler::Degree");

  Handle(Geom_BSplineCurve) C = 
    Handle(Geom_BSplineCurve)::DownCast(mySequence(1));

  return C->NbKnots();
}


//=======================================================================
//function : KnotsAndMults
//purpose  : 
//=======================================================================

void GeomFill_Profiler::KnotsAndMults(TColStd_Array1OfReal&    Knots, 
				      TColStd_Array1OfInteger& Mults ) const 
{
  if ( !myIsDone)
    StdFail_NotDone::Raise("GeomFill_Profiler::Degree");

#ifndef No_Exception
  Standard_Integer n = NbKnots();
#endif
  Standard_DomainError_Raise_if( Knots.Length() != n  || Mults.Length() != n,
				"GeomFill_Profiler::KnotsAndMults");

  Handle(Geom_BSplineCurve) C = 
    Handle(Geom_BSplineCurve)::DownCast(mySequence(1));

  C->Knots(Knots);
  C->Multiplicities(Mults);
}


