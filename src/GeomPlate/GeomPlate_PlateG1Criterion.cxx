// Created on: 1997-03-05
// Created by: Joelle CHAUVET
// Copyright (c) 1997-1999 Matra Datavision
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



#include <GeomPlate_PlateG1Criterion.ixx>
#include <AdvApp2Var_Criterion.hxx>
#include <TColgp_SequenceOfXY.hxx>
#include <TColgp_SequenceOfXYZ.hxx>
#include <gp_Vec.hxx>
#include <gp_XY.hxx>
#include <gp_Pnt.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <PLib.hxx>


//  static Standard_Boolean  first = Standard_True;


//============================================================================
//function : GeomPlate_PlateG1Criterion 
//purpose  :
//============================================================================


GeomPlate_PlateG1Criterion::
GeomPlate_PlateG1Criterion(const TColgp_SequenceOfXY& Data,
			   const TColgp_SequenceOfXYZ& G1Data,
			   const Standard_Real Maximum,
			   const AdvApp2Var_CriterionType Type,
			   const AdvApp2Var_CriterionRepartition Repart)
{
  myData=Data;
  myXYZ=G1Data;
  myMaxValue = Maximum;
  myType = Type;
  myRepartition = Repart;
}


//============================================================================
//function : Value
//purpose  :
//============================================================================

void GeomPlate_PlateG1Criterion::Value(AdvApp2Var_Patch& P,
				       const AdvApp2Var_Context& C) const
{
  Standard_Real UInt[2],VInt[2];
  Standard_Integer MaxNbCoeff[2], NbCoeff[2];
  Standard_Real * adrCoeff = NULL ;
  adrCoeff = (Standard_Real *) &P.Coefficients(1,C) ->ChangeArray1()(P.Coefficients(1,C)->Lower());

  MaxNbCoeff[0] = C.ULimit();
  MaxNbCoeff[1] = C.VLimit();
  NbCoeff[0] = P.NbCoeffInU();
  NbCoeff[1] = P.NbCoeffInV();
  UInt[0] = P.U0();
  UInt[1] = P.U1();
  VInt[0] = P.V0();
  VInt[1] = P.V1();

  Standard_Real up,vp, ang = 0.;
  
  Standard_Integer dimension = 3 * NbCoeff[1];
  TColStd_Array1OfReal Patch(1, NbCoeff[0] * dimension);
  TColStd_Array1OfReal Curve(1, 2*dimension);
  TColStd_Array1OfReal Point(1, 3); 
  Standard_Real * Coeffs =  (Standard_Real *) &Patch.ChangeValue(1);
  Standard_Real * Digit  =  (Standard_Real *) &Point.ChangeValue(1);
  
  Standard_Integer k1, k2, pos, ll=1;
  for (k1 = 1; k1 <= NbCoeff[0]; k1++) {
// JAG 99.04.29    pos = 3*(MaxNbCoeff[0])*(k1-1);
    pos = 3*(MaxNbCoeff[1])*(k1-1);
    for (k2 = 1; k2 <= NbCoeff[1]; k2++, pos+=3 ) {
      Patch(ll)   =  adrCoeff[pos];
      Patch(ll+1) =  adrCoeff[pos+1];
      Patch(ll+2) =  adrCoeff[pos+2];
      ll += 3;
    }
  }

  Standard_Integer i, NbCtr = myData.Length();
  for(i=1; i<=NbCtr; i++) {
    gp_Vec v1s,v2s,v3s;
    gp_Vec v3h(myXYZ.Value(i).X(),myXYZ.Value(i).Y(),myXYZ.Value(i).Z());
    gp_XY P2d = myData.Value(i);
      if ( UInt[0]<P2d.X() && P2d.X()<UInt[1]
	  && VInt[0]<P2d.Y() && P2d.Y()<VInt[1] ) {
//   u,v recadres sur (-1,1)
	up = (2*P2d.X()-UInt[0]-UInt[1])
              / (UInt[1]-UInt[0]) ;
	vp = (2*P2d.Y()-VInt[0]-VInt[1])
	      / (VInt[1]-VInt[0]) ;
	PLib::EvalPoly2Var(up,vp,
			   1,0,
			   NbCoeff[0]-1,NbCoeff[1]-1,3,
			   Coeffs[0],
			   Digit[0]);

	v1s.SetCoord(1,Digit[0]);
	v1s.SetCoord(2,Digit[1]);
	v1s.SetCoord(3,Digit[2]);

	PLib::EvalPoly2Var(up,vp,
			   0,1,
			   NbCoeff[0]-1,NbCoeff[1]-1,3,
			   Coeffs[0],
			   Digit[0]);
      
	v2s.SetCoord(1,Digit[0]);
	v2s.SetCoord(2,Digit[1]);
	v2s.SetCoord(3,Digit[2]);

	v3s=v1s^v2s;
	if( v3s.Angle(v3h)>(M_PI/2)) {
	  if ((M_PI-v3s.Angle(v3h))>ang) {
            ang=(M_PI-v3s.Angle(v3h));
          }
	}
	else {
	  if(v3s.Angle(v3h)>ang) {
            ang=v3s.Angle(v3h);
          }
	}
      }
  }
  P.SetCritValue(ang);
}


//============================================================================
//function : IsSatisfied
//purpose  :
//============================================================================

Standard_Boolean GeomPlate_PlateG1Criterion::IsSatisfied(const AdvApp2Var_Patch& P) const
{
  return (P.CritValue() < myMaxValue);
}

