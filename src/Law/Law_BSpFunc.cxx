// Created on: 1995-11-16
// Created by: Laurent BOURESCHE
// Copyright (c) 1995-1999 Matra Datavision
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


// pmn -> 17/01/1996 added : Continuity, (Nb)Intervals, D2, Trim

#include <Law_BSpFunc.ixx>

#include <BSplCLib.hxx>
#include <Precision.hxx>
#include <Law_BSplineKnotSplitting.hxx>
#include <TColStd_Array1OfInteger.hxx>

#define PosTol Precision::PConfusion()/2

//=======================================================================
//function : Law_BSpFunc
//purpose  : 
//=======================================================================

Law_BSpFunc::Law_BSpFunc()
{
}

//=======================================================================
//function : Law_BSpFunc
//purpose  : 
//=======================================================================
Law_BSpFunc::Law_BSpFunc(const Handle(Law_BSpline)& C,
			 const Standard_Real First,
			 const Standard_Real Last)
                         :curv(C), first(First), last(Last)
{  
}

//=======================================================================
//function : Continuity
//purpose  : 
//=======================================================================
GeomAbs_Shape Law_BSpFunc::Continuity() const 
{
  return curv->Continuity();
}
//=======================================================================
//function : NbIntervals
//purpose  : Inspirer de GeomAdaptor_Curve
//=======================================================================

Standard_Integer Law_BSpFunc::NbIntervals(const GeomAbs_Shape S) const
{
  Standard_Integer myNbIntervals = 1;
  if ( S > Continuity()) {
    Standard_Integer Cont;
    switch ( S) {
    case GeomAbs_G1:
    case GeomAbs_G2:
      Standard_DomainError::Raise("Law_BSpFunc::NbIntervals");
      break;
    case GeomAbs_C0:
      myNbIntervals = 1;
      break;
    case GeomAbs_C1:
    case GeomAbs_C2:
    case GeomAbs_C3: 
    case GeomAbs_CN: 
      {
	if      ( S == GeomAbs_C1) Cont = 1;
	else if ( S == GeomAbs_C2) Cont = 2;
	else if ( S == GeomAbs_C3) Cont = 3;
	else                       Cont = curv->Degree();
	Law_BSplineKnotSplitting Convector(curv, Cont);
	Standard_Integer NbInt = Convector.NbSplits()-1;
	TColStd_Array1OfInteger Inter(1,NbInt+1);
	Convector.Splitting( Inter);
	  
	Standard_Integer Nb = curv->NbKnots();
	Standard_Integer Index1 = 0;
	Standard_Integer Index2 = 0;
	Standard_Real newFirst, newLast;
	TColStd_Array1OfReal    TK(1,Nb);
	TColStd_Array1OfInteger TM(1,Nb);
	curv->Knots(TK);
	curv->Multiplicities(TM);
	BSplCLib::LocateParameter(curv->Degree(),TK,TM,first,
				  curv->IsPeriodic(),
				  1,Nb,Index1,newFirst);
	BSplCLib::LocateParameter(curv->Degree(),TK,TM,last,
				  curv->IsPeriodic(),
				  1,Nb,Index2,newLast);
	if ( Abs(newFirst-TK(Index1+1))<Precision::PConfusion()) 
	  Index1++;
	if ( newLast-TK(Index2)>Precision::PConfusion()) 
	  Index2++;
	  
	myNbIntervals = 1;
	for ( Standard_Integer i=1; i<=NbInt; i++)
	  if (Inter(i)>Index1 && Inter(i)<Index2) myNbIntervals++;
      }
      break;
    }
  }

  return myNbIntervals;
}

//=======================================================================
//function : Intervals
//purpose  : Inspirer de GeomAdaptor_Curve
//=======================================================================

void Law_BSpFunc::Intervals(TColStd_Array1OfReal& T,
			    const GeomAbs_Shape S   ) const 
{
  Standard_Integer myNbIntervals = 1;
  if ( S > Continuity()) {
    Standard_Integer Cont;
    switch ( S) {
    case GeomAbs_G1:
    case GeomAbs_G2:
      Standard_DomainError::Raise("Law_BSpFunc_Curve::Intervals");
      break;
    case GeomAbs_C0:
      myNbIntervals = 1;
      break;
    case GeomAbs_C1:
    case GeomAbs_C2:
    case GeomAbs_C3: 
    case GeomAbs_CN: 
      {
	if      ( S == GeomAbs_C1) Cont = 1;
	else if ( S == GeomAbs_C2) Cont = 2;
	else if ( S == GeomAbs_C3) Cont = 3;
	else                       Cont = curv->Degree();
	Law_BSplineKnotSplitting Convector(curv, Cont);
	Standard_Integer NbInt = Convector.NbSplits()-1;
	TColStd_Array1OfInteger Inter(1,NbInt+1);
	Convector.Splitting( Inter);
	  
	Standard_Integer Nb = curv->NbKnots();
	Standard_Integer Index1 = 0;
	Standard_Integer Index2 = 0;
	Standard_Real newFirst, newLast;
	TColStd_Array1OfReal    TK(1,Nb);
	TColStd_Array1OfInteger TM(1,Nb);
	curv->Knots(TK);
	curv->Multiplicities(TM);
	BSplCLib::LocateParameter(curv->Degree(),TK,TM,first,
				  curv->IsPeriodic(),
				  1,Nb,Index1,newFirst);
	BSplCLib::LocateParameter(curv->Degree(),TK,TM,last,
				  curv->IsPeriodic(),
				  1,Nb,Index2,newLast);
	if ( Abs(newFirst-TK(Index1+1))<Precision::PConfusion()) 
	  Index1++;
	if ( newLast-TK(Index2)>Precision::PConfusion()) 
	  Index2++;
	  
	Inter( 1) = Index1;
	myNbIntervals = 1;
	for ( Standard_Integer i=1; i<=NbInt; i++) {
	  if (Inter(i) > Index1 && Inter(i)<Index2 ) {
	    myNbIntervals++;
	    Inter(myNbIntervals) = Inter(i);
	  }
	}
	Inter(myNbIntervals+1) = Index2;
	  
	for (Standard_Integer I=1;I<=myNbIntervals+1;I++) {
	  T(I) = TK(Inter(I));
	}
      }
      break;
    }
  }
  T( T.Lower() ) = first;
  T( T.Lower() + myNbIntervals ) = last;
}


//=======================================================================
//function : Value
//purpose  : 
//=======================================================================

Standard_Real Law_BSpFunc::Value(const Standard_Real X)
{
  if ((X==first) || (X==last)) {
    Standard_Integer Ideb = 0, Ifin = 0;
    if (X==first) {
      curv->LocateU(first, PosTol, Ideb, Ifin);
      if (Ideb<1) Ideb=1;
      if (Ideb>=Ifin) Ifin = Ideb+1;
      }
    if (X==last) {
      curv->LocateU(last, PosTol, Ideb, Ifin);
      if (Ifin>curv->NbKnots()) Ifin = curv->NbKnots();
      if (Ideb>=Ifin) Ideb = Ifin-1;
      }
    return curv->LocalValue(X, Ideb, Ifin);
  }
  else {
    return curv->Value(X);
   }
}


//=======================================================================
//function : D1
//purpose  : 
//=======================================================================

void Law_BSpFunc::D1(const Standard_Real X, 
		     Standard_Real& F, 
		     Standard_Real& D)
{
  if ((X==first) || (X==last)) {
    Standard_Integer Ideb = 0, Ifin = 0;
    if (X==first) {
      curv->LocateU(first, PosTol, Ideb, Ifin);
      if (Ideb<1) Ideb=1;
      if (Ideb>=Ifin) Ifin = Ideb+1;
      }
    if (X==last) {
      curv->LocateU(last, PosTol, Ideb, Ifin);
      if (Ifin>curv->NbKnots()) Ifin = curv->NbKnots();
      if (Ideb>=Ifin) Ideb = Ifin-1;
      }
    curv->LocalD1(X, Ideb, Ifin, F, D);
  }
  else {
    curv->D1(X, F, D);
   }
}

//=======================================================================
//function : D2
//purpose  : 
//=======================================================================

void Law_BSpFunc::D2(const Standard_Real X, 
		     Standard_Real& F, 
		     Standard_Real& D,
		     Standard_Real& D2)
{
  if ((X==first) || (X==last)) {
    Standard_Integer Ideb = 0, Ifin = 0;
    if (X==first) {
      curv->LocateU(first, PosTol, Ideb, Ifin);
      if (Ideb<1) Ideb=1;
      if (Ideb>=Ifin) Ifin = Ideb+1;
      }
    if (X==last) {
      curv->LocateU(last, PosTol, Ideb, Ifin);
      if (Ifin>curv->NbKnots()) Ifin = curv->NbKnots();
      if (Ideb>=Ifin) Ideb = Ifin-1;
      }
    curv->LocalD2(X, Ideb, Ifin, F, D, D2);
  }
  else {
    curv->D2(X, F, D, D2);
   }

}

//=======================================================================
//function : Trim
//purpose  : 
//=======================================================================

Handle(Law_Function) Law_BSpFunc::Trim(const Standard_Real PFirst, 
				       const Standard_Real PLast, 
//				       const Standard_Real Tol) const 
				       const Standard_Real ) const 
{
  Handle(Law_BSpFunc) l = new (Law_BSpFunc)(curv, PFirst, PLast);
  return l;
}

//=======================================================================
//function : Bounds
//purpose  : 
//=======================================================================

void Law_BSpFunc::Bounds(Standard_Real& PFirst, Standard_Real& PLast)
{
  PFirst = first;
  PLast  = last;
}


//=======================================================================
//function : Curve
//purpose  : 
//=======================================================================

Handle(Law_BSpline) Law_BSpFunc::Curve() const 
{
  return curv;
}


//=======================================================================
//function : SetCurve
//purpose  : 
//=======================================================================

void Law_BSpFunc::SetCurve(const Handle(Law_BSpline)& C)
{
  curv = C;
  first = C->FirstParameter();
  last  = C->LastParameter();
}
