// Created on: 1993-09-29
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


#include <GeomFill_Coons.ixx>

#include <BSplCLib.hxx>
#include <PLib.hxx>
#include <TColgp_HArray2OfPnt.hxx>
#include <TColStd_HArray2OfReal.hxx>

//=======================================================================
//function : GeomFill_Coons
//purpose  : 
//=======================================================================

GeomFill_Coons::GeomFill_Coons()
{
}


//=======================================================================
//function : GeomFill_Coons
//purpose  : 
//=======================================================================

GeomFill_Coons::GeomFill_Coons(const TColgp_Array1OfPnt& P1, 
			 const TColgp_Array1OfPnt& P2, 
			 const TColgp_Array1OfPnt& P3, 
			 const TColgp_Array1OfPnt& P4)
{
  Init( P1, P2, P3, P4);
}


//=======================================================================
//function : GeomFill_Coons
//purpose  : 
//=======================================================================

GeomFill_Coons::GeomFill_Coons(const TColgp_Array1OfPnt&   P1, 
			 const TColgp_Array1OfPnt&   P2, 
			 const TColgp_Array1OfPnt&   P3, 
			 const TColgp_Array1OfPnt&   P4, 
			 const TColStd_Array1OfReal& W1, 
			 const TColStd_Array1OfReal& W2, 
			 const TColStd_Array1OfReal& W3, 
			 const TColStd_Array1OfReal& W4)
{
  Init( P1, P2, P3, P4, W1, W2, W3, W4);
}


//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void  GeomFill_Coons::Init(const TColgp_Array1OfPnt& P1, 
			const TColgp_Array1OfPnt& P2, 
			const TColgp_Array1OfPnt& P3, 
			const TColgp_Array1OfPnt& P4)
{
  Standard_DomainError_Raise_if
    ( P1.Length() != P3.Length() || P2.Length() != P4.Length()," ");

  Standard_Integer NPolU = P1.Length();
  Standard_Integer NPolV = P2.Length();

  IsRational = Standard_False;

  myPoles = new TColgp_HArray2OfPnt( 1, NPolU, 1, NPolV);

  // The boundaries are not modified
  Standard_Integer i,j,k;

  for (i=1; i<=NPolU; i++) {
    myPoles->SetValue( i, 1    , P1(i));
    myPoles->SetValue( i, NPolV, P3(i));
  }
  for (i=1; i<=NPolV; i++) {
    myPoles->SetValue( 1    , i, P2(i));
    myPoles->SetValue( NPolU, i, P4(i));
  }

  // Calcul des coefficients multiplicateurs
  TColgp_Array1OfPnt Coef ( 1, 4);
  TColgp_Array1OfPnt Pole ( 1, 4);
  TColgp_Array1OfPnt CoefU( 1, NPolU);
  TColgp_Array1OfPnt CoefV( 1, NPolV);
  Coef( 4) = gp_Pnt(  2., -2., 0.);
  Coef( 3) = gp_Pnt( -3.,  3., 0.);
  Coef( 2) = gp_Pnt(  0.,  0., 0.);
  Coef( 1) = gp_Pnt(  1.,  0., 0.);
  PLib::CoefficientsPoles(Coef, PLib::NoWeights(),
			  Pole, PLib::NoWeights());
  if (NPolU > 4) {
    BSplCLib::IncreaseDegree(NPolU-1, Pole, PLib::NoWeights(), 
			     CoefU, PLib::NoWeights());
  }
  else {
     CoefU = Pole;
  }
  if (NPolV > 4) {
    BSplCLib::IncreaseDegree(NPolV-1, Pole, PLib::NoWeights(), 
			     CoefV, PLib::NoWeights());
  }
  else {
      CoefV = Pole;
  }
  TColStd_Array1OfReal FU(2,NPolU-1);
  TColStd_Array1OfReal GU(2,NPolU-1);
  TColStd_Array1OfReal FV(2,NPolV-1);
  TColStd_Array1OfReal GV(2,NPolV-1);
  Standard_Real Dummy;
  for ( i= 2; i< NPolU; i++) {
    CoefU(i).Coord(FU(i), GU(i), Dummy);
  }
  for ( i= 2; i< NPolV; i++) {
    CoefV(i).Coord(FV(i), GV(i), Dummy);
  }
  
  // Clacul des poles interieurs
  gp_Pnt P;
  for ( j=2; j<NPolV; j++) {
    for ( i=2; i<NPolU; i++) {
      for ( k=1; k<=3      ; k++) {
	P.SetCoord( k,
		             FV(j) * (myPoles->Value(i    ,1    )).Coord(k)
		   +         GV(j) * (myPoles->Value(i    ,NPolV)).Coord(k)
		   +         FU(i) * (myPoles->Value(1    ,j    )).Coord(k)
		   +         GU(i) * (myPoles->Value(NPolU,j    )).Coord(k)
		   - FU(i) * FV(j) * (myPoles->Value(1    ,1    )).Coord(k)
		   - FU(i) * GV(j) * (myPoles->Value(1    ,NPolV)).Coord(k)
		   - GU(i) * FV(j) * (myPoles->Value(NPolU,1    )).Coord(k)
		   - GU(i) * GV(j) * (myPoles->Value(NPolU,NPolV)).Coord(k));
      }
      myPoles->SetValue(i,j,P);
    }
  }
}


//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void  GeomFill_Coons::Init(const TColgp_Array1OfPnt&   P1, 
			   const TColgp_Array1OfPnt&   P2, 
			   const TColgp_Array1OfPnt&   P3, 
			   const TColgp_Array1OfPnt&   P4, 
			   const TColStd_Array1OfReal& W1, 
			   const TColStd_Array1OfReal& W2, 
			   const TColStd_Array1OfReal& W3,
			   const TColStd_Array1OfReal& W4
                          )
{

  Standard_DomainError_Raise_if
    ( W1.Length() != W3.Length() || W2.Length() != W4.Length()," ");
  Standard_DomainError_Raise_if
    ( W1.Length() != P1.Length() || 
      W2.Length() != P2.Length() || 
      W3.Length() != P3.Length() || 
      W4.Length() != P4.Length()   , " ");
  Init(P1,P2,P3,P4);
  IsRational = Standard_True;

  Standard_Integer NPolU = W1.Length();
  Standard_Integer NPolV = W2.Length();

//#ifdef DEB
  Standard_Real NU = NPolU - 1;
  Standard_Real NV = NPolV - 1;
//#endif
  myWeights = new TColStd_HArray2OfReal( 1, NPolU, 1, NPolV);
   // The boundaries are not modified
  Standard_Integer i,j;
  for ( i=1; i<=NPolU; i++) {
    myWeights->SetValue( i, 1    , W1(i));
    myWeights->SetValue( i, NPolV, W3(i));
  }
  Standard_Real PU,PU1,PV,PV1;
  
  for ( j=2; j<=NPolV-1; j++) {
    PV  = (j-1)/NV;
    PV1 = 1 - PV;
    myWeights->SetValue( 1    , j, W4(j));
    myWeights->SetValue( NPolU, j, W2(j));

    for ( i=2; i<=NPolU-1; i++) {
      PU  = (i-1)/NU;
      PU1 = 1 - PU;

//      Standard_Real W = 0.5 * ( PV1 * W1(i) + PV  * W3(i) +
//			        PU  * W2(j) + PU1 * W4(j)  );
      Standard_Real W = PV1 * W1(i) + PV  * W3(i) +
	                PU  * W2(j) + PU1 * W4(j) -
	              ( PU1 * PV1 * W1(1)     +
	                PU  * PV1 * W2(1)     +
	                PU  * PV  * W3(NPolU) +
	                PU1 * PV  * W4(NPolV)   );

      myWeights->SetValue(i,j,W);
    }
  }
 
}



