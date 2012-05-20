// Created on: 1995-05-30
// Created by: Xavier BENVENISTE
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


// 19-06-96 : JPI : NbPoles doit utiliser  ColLength() au lieu de RowLength()
// 16-09-96 : PMN : On ne doit pas se soucier de la continuite lorsqu'il n'y
//                  qu'un seul segment(PRO5474).
// 11-12-96 : PMN : Respect de l'indicage des tableaux passer en arguments 
//                  TrueIntervals et PolynomialIntervals (BUC40077)
// 15-04-97 : PMN : Constructeurs avec un seul segement ou differentes 
//                  continuitees. 

#define No_Standard_OutOfRange

#include <Convert_CompPolynomialToPoles.ixx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <PLib.hxx>
#include <BSplCLib.hxx>
#include <Standard_ConstructionError.hxx>

//=======================================================================
//function : Constructor
//purpose  : 
//=======================================================================

Convert_CompPolynomialToPoles::Convert_CompPolynomialToPoles(
    const Standard_Integer                 NumCurves,
    const Standard_Integer                 Continuity, 
    const Standard_Integer                 Dimension, 
    const Standard_Integer                 MaxDegree, 
    const Handle_TColStd_HArray1OfInteger& NumCoeffPerCurve, 
    const Handle_TColStd_HArray1OfReal&    Coefficients,    
    const Handle_TColStd_HArray2OfReal&    PolynomialIntervals, 
    const Handle_TColStd_HArray1OfReal&    TrueIntervals)
     : myDone(Standard_False) 
{
 Standard_Integer ii, delta;
 if (NumCurves <= 0               ||
     NumCoeffPerCurve.IsNull()    ||
     Coefficients.IsNull()        ||
     PolynomialIntervals.IsNull() ||
     TrueIntervals.IsNull()       || 
     Continuity < 0               ||
     MaxDegree  <= 0              ||
     Dimension  <= 0              ||
     PolynomialIntervals->RowLength() != 2) {
   Standard_ConstructionError::
   Raise("Convert_CompPolynomialToPoles:bad arguments");
 } 
 myDegree = 0 ;

 delta = NumCurves - 1 ;
 for (ii =  NumCoeffPerCurve->Lower(); 
      ii <= NumCoeffPerCurve->Lower() + delta ;
      ii++) {
   myDegree = Max(NumCoeffPerCurve->Value(ii)-1,myDegree) ;
 }
 if ((Continuity > myDegree)&& (NumCurves>1)) {
   Standard_ConstructionError::
   Raise("Convert_CompPolynomialToPoles:Continuity is too great");
 } 
//
//  prepare output
//
 Standard_Integer Tindex, multiplicities ;

 myKnots = 
 new TColStd_HArray1OfReal(1, NumCurves + 1) ;
 for (ii = 1, Tindex = TrueIntervals->Lower() ; 
      ii <=  NumCurves + 1 ; ii++,Tindex++ ) {
    myKnots->ChangeArray1().SetValue(ii,TrueIntervals->Value(Tindex)) ;
  }

 multiplicities = myDegree - Continuity ;
 myMults =
 new TColStd_HArray1OfInteger(1, NumCurves + 1) ;
 for (ii = 2 ; ii < NumCurves + 1 ; ii++) {
   myMults -> SetValue(ii,multiplicities);
 }
 myMults -> SetValue(1, myDegree + 1) ;
 myMults -> SetValue(NumCurves + 1, myDegree + 1) ;

 Perform(NumCurves, MaxDegree, Dimension,
	 NumCoeffPerCurve->Array1(), Coefficients->Array1(),
	 PolynomialIntervals->Array2(), TrueIntervals->Array1());
}

Convert_CompPolynomialToPoles::
Convert_CompPolynomialToPoles(const Standard_Integer NumCurves,
			      const Standard_Integer Dimension,
			      const Standard_Integer MaxDegree,
			      const TColStd_Array1OfInteger& Continuity,
			      const TColStd_Array1OfInteger& NumCoeffPerCurve,
			      const TColStd_Array1OfReal& Coefficients,
			      const TColStd_Array2OfReal& PolynomialIntervals,
			      const TColStd_Array1OfReal& TrueIntervals)
                              : myDone(Standard_False) 
{
 Standard_Integer ii, delta;
 if (NumCurves <= 0               ||
     MaxDegree  <= 0              ||
     Dimension  <= 0              ||
     PolynomialIntervals.RowLength() != 2) {
   Standard_ConstructionError::
   Raise("Convert_CompPolynomialToPoles:bad arguments");
 } 
 myDegree = 0 ;

 delta = NumCurves - 1 ;
 for (ii =  NumCoeffPerCurve.Lower(); 
      ii <= NumCoeffPerCurve.Lower() + delta ;
      ii++) {
   myDegree = Max(NumCoeffPerCurve.Value(ii)-1,myDegree) ;
 }
//
//  prepare output
//
 Standard_Integer Tindex ;

 myKnots = 
 new TColStd_HArray1OfReal(1, NumCurves + 1) ;
 for (ii = 1, Tindex = TrueIntervals.Lower() ; 
      ii <=  NumCurves + 1 ; ii++,Tindex++ ) {
    myKnots->ChangeArray1().SetValue(ii,TrueIntervals.Value(Tindex)) ;
  }

 myMults =
 new TColStd_HArray1OfInteger(1, NumCurves + 1) ;
 for (ii = 2 ; ii < NumCurves + 1 ; ii++) {
   if ((Continuity(ii) > myDegree)&& (NumCurves>1)) {
     Standard_ConstructionError::
     Raise("Convert_CompPolynomialToPoles:Continuity is too great");
   }

   myMults -> SetValue(ii, myDegree-Continuity(ii) );
 }
 myMults -> SetValue(1, myDegree + 1) ;
 myMults -> SetValue(NumCurves + 1, myDegree + 1) ;

// Calculs
 Perform(NumCurves, MaxDegree, Dimension,
	 NumCoeffPerCurve, Coefficients,
	 PolynomialIntervals, TrueIntervals);  
}

Convert_CompPolynomialToPoles::
Convert_CompPolynomialToPoles(const Standard_Integer Dimension,
			      const Standard_Integer MaxDegree,
			      const Standard_Integer Degree,
			      const TColStd_Array1OfReal& Coefficients,
			      const TColStd_Array1OfReal& PolynomialIntervals,
			      const TColStd_Array1OfReal& TrueIntervals) :
                              myDegree(Degree) ,
                              myDone(Standard_False)
  
{
 if (MaxDegree  <= 0              ||
     Dimension  <= 0              ||
     PolynomialIntervals.Length() != 2) 
   {
     Standard_ConstructionError::
     Raise("Convert_CompPolynomialToPoles:bad arguments");
   }

 TColStd_Array2OfReal ThePolynomialIntervals(1,1,1,2);
 ThePolynomialIntervals.SetValue(1,1,PolynomialIntervals(PolynomialIntervals.Lower()));
 ThePolynomialIntervals.SetValue(1,2,PolynomialIntervals(PolynomialIntervals.Upper()));
 
 TColStd_Array1OfInteger NumCoeffPerCurve(1,1);
 NumCoeffPerCurve(1) = Degree+1;

 myKnots = 
 new TColStd_HArray1OfReal(1, 2) ;
 myKnots->ChangeArray1().SetValue(1, TrueIntervals.Value(TrueIntervals.Lower()));
 myKnots->ChangeArray1().SetValue(2, TrueIntervals.Value(TrueIntervals.Lower()+1));

 myMults =
 new TColStd_HArray1OfInteger(1, 2) ;
 myMults->Init( myDegree + 1);


// Calculs
 Perform(1, MaxDegree, Dimension,
	 NumCoeffPerCurve, Coefficients,
	 ThePolynomialIntervals, TrueIntervals);  
}

void Convert_CompPolynomialToPoles::
Perform(const Standard_Integer NumCurves,
	const Standard_Integer MaxDegree,
	const Standard_Integer Dimension,
	const TColStd_Array1OfInteger& NumCoeffPerCurve,
	const TColStd_Array1OfReal& Coefficients, 
	const TColStd_Array2OfReal& PolynomialIntervals,
	const TColStd_Array1OfReal& TrueIntervals)
{
 Standard_Integer ii, 
 num_flat_knots,
 index, Tindex, Pindex,
 coeff_index,
 inversion_problem,
 poles_index,
 num_poles ;
 Standard_Real normalized_value,
 *coefficient_array,
 *poles_array ;
 
 num_flat_knots = 2 * myDegree + 2 ;
 for (ii=2; ii<myMults->Length(); ii++) {
   num_flat_knots += myMults->Value(ii);
 }
 num_poles = num_flat_knots - myDegree - 1 ;

 myFlatKnots = new TColStd_HArray1OfReal(1,num_flat_knots) ;
 BSplCLib::KnotSequence (myKnots->Array1(), 
			 myMults->Array1(),
			 myDegree,
			 Standard_False,
			 myFlatKnots->ChangeArray1());

 TColStd_Array1OfReal parameters(1,num_poles) ;
 BSplCLib::BuildSchoenbergPoints(myDegree,
				 myFlatKnots->Array1(),
				 parameters) ;
 myPoles = new TColStd_HArray2OfReal(1, num_poles,
				     1, Dimension) ;
 index = 2;
 Tindex = TrueIntervals.Lower()+1;
 Pindex = PolynomialIntervals.LowerRow();
 poles_array =
 (Standard_Real *) &(myPoles->ChangeArray2()).Value(1,1) ;

 TColStd_Array1OfInteger contact_array(1,num_poles) ;

 poles_index = 0 ;
 for (ii = 1 ; ii <= num_poles ; ii++, poles_index += Dimension) {
   contact_array.SetValue(ii,0) ;
   while (parameters.Value(ii) >= TrueIntervals(Tindex) &&
	  index <= NumCurves) {
     index++; Tindex++; Pindex++;
   }
// 
// normalized value so that it fits the original intervals for
// the polynomial definition of the curves
//
   normalized_value =  parameters.Value(ii) - TrueIntervals(Tindex-1) ;
   normalized_value /=  TrueIntervals(Tindex) 
                     -  TrueIntervals(Tindex-1)  ;
   normalized_value = (1.0e0 -normalized_value) * 
     PolynomialIntervals(Pindex, PolynomialIntervals.LowerCol()) 
                    + normalized_value * 
     PolynomialIntervals(Pindex, PolynomialIntervals.UpperCol()) ;
   coeff_index = ((index-2) * Dimension * (Max(MaxDegree, myDegree) + 1))  
               + Coefficients.Lower();
   
   coefficient_array =
     (Standard_Real *) &(Coefficients(coeff_index)) ;
   Standard_Integer Deg = NumCoeffPerCurve(NumCoeffPerCurve.Lower()+index-2) - 1;

   PLib::NoDerivativeEvalPolynomial
     (normalized_value,
      Deg,
      Dimension,
      Deg * Dimension,
      coefficient_array[0],
      poles_array[poles_index]) ; 
 }
//
// interpolation at schoenberg points should yield the desired
// result
//
 BSplCLib::Interpolate(myDegree,
		       myFlatKnots->Array1(),
		       parameters,
		       contact_array,
		       Dimension,
		       poles_array[0],
		       inversion_problem) ;
 if (inversion_problem != 0) {
  Standard_ConstructionError::
  Raise("Convert_CompPolynomialToPoles:inversion_problem");
 } 
 myDone = Standard_True ;
}


 
//=======================================================================
//function : NbPoles
//purpose  : 
//=======================================================================

Standard_Integer Convert_CompPolynomialToPoles::NbPoles()  const 
{
  if (myDone) {
    return myPoles->ColLength() ;
  }
  else 
    return 0 ;
}
//=======================================================================
//function : Poles
//purpose  : 
//=======================================================================

void Convert_CompPolynomialToPoles::Poles(
			Handle_TColStd_HArray2OfReal& P) const 
 { if (myDone) {
   P = myPoles ; } 
 }
//=======================================================================
//function : NbKnots
//purpose  : 
//=======================================================================

Standard_Integer Convert_CompPolynomialToPoles::NbKnots()  const 
{
  if (myDone) {
    return myKnots->Length() ;
  }
  else 
    return 0 ;
}
//=======================================================================
//function : Knots
//purpose  : 
//=======================================================================

void Convert_CompPolynomialToPoles::Knots(
			 Handle_TColStd_HArray1OfReal& K) const 
 { if (myDone) {
   K = myKnots ; } 
 }
   
//=======================================================================
//function : Knots
//purpose  : 
//=======================================================================

void Convert_CompPolynomialToPoles::Multiplicities(
                      Handle_TColStd_HArray1OfInteger& M) const 
 { if (myDone) {
   M = myMults ; }
 }
//=======================================================================
//function : IsDone
//purpose  : 
//=======================================================================

Standard_Boolean  Convert_CompPolynomialToPoles::IsDone() const 
{ return myDone ; }
//=======================================================================
//function : IsDone
//purpose  : 
//=======================================================================

Standard_Integer Convert_CompPolynomialToPoles::Degree() const 
{ 
  if (myDone) {
    return myDegree ; 
  }
  return 0 ;
}
