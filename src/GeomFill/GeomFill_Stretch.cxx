// Created on: 1993-09-28
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


#include <GeomFill_Stretch.ixx>

#include <gp_Pnt.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColgp_HArray2OfPnt.hxx>
#include <TColStd_HArray2OfReal.hxx>


//=======================================================================
//function : GeomFill_Stretch
//purpose  : 
//=======================================================================

GeomFill_Stretch::GeomFill_Stretch()
{
}


//=======================================================================
//function : GeomFill_Stretch
//purpose  : 
//=======================================================================

GeomFill_Stretch::GeomFill_Stretch(const TColgp_Array1OfPnt& P1, 
			     const TColgp_Array1OfPnt& P2, 
			     const TColgp_Array1OfPnt& P3, 
			     const TColgp_Array1OfPnt& P4)
{
  Init(P1, P2, P3, P4);
}


//=======================================================================
//function : GeomFill_Stretch
//purpose  : 
//=======================================================================

GeomFill_Stretch::GeomFill_Stretch(const TColgp_Array1OfPnt&   P1, 
			     const TColgp_Array1OfPnt&   P2, 
			     const TColgp_Array1OfPnt&   P3, 
			     const TColgp_Array1OfPnt&   P4,
			     const TColStd_Array1OfReal& W1,
			     const TColStd_Array1OfReal& W2,
			     const TColStd_Array1OfReal& W3,
			     const TColStd_Array1OfReal& W4)
{
  Init(P1, P2, P3, P4, W1, W2, W3, W4);
}


//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void  GeomFill_Stretch::Init(const TColgp_Array1OfPnt& P1, 
			  const TColgp_Array1OfPnt& P2, 
			  const TColgp_Array1OfPnt& P3, 
			  const TColgp_Array1OfPnt& P4)
{
  Standard_DomainError_Raise_if
    ( P1.Length() != P3.Length() || P2.Length() != P4.Length()," ");

  Standard_Integer NPolU = P1.Length();
  Standard_Integer NPolV = P2.Length();

  IsRational = Standard_False;

  Standard_Real NU = NPolU - 1;
  Standard_Real NV = NPolV - 1;
  myPoles = new TColgp_HArray2OfPnt( 1, NPolU, 1, NPolV);
  
  // The boundaries are not modified
  Standard_Integer i,j,k;
  for ( i=1; i<=NPolU; i++) {
    myPoles->SetValue( i, 1    , P1(i));
    myPoles->SetValue( i, NPolV, P3(i));
  }
  Standard_Real PU,PU1,PV,PV1;
  
  for ( j=2; j<=NPolV-1; j++) {
    PV  = (j-1)/NV;
    PV1 = 1 - PV;
    myPoles->SetValue( 1    , j, P4(j));
    myPoles->SetValue( NPolU, j, P2(j));

    for ( i=2; i<=NPolU-1; i++) {
      PU  = (i-1)/NU;
      PU1 = 1 - PU;
      
      gp_Pnt P;
      for (k=1; k<=3; k++) {
	P.SetCoord(k, 
		   PV1 * P1(i).Coord(k) + PV  * P3(i).Coord(k) +
		   PU  * P2(j).Coord(k) + PU1 * P4(j).Coord(k) -
		   ( PU1 * PV1 * P1(1).Coord(k)     +
		     PU  * PV1 * P2(1).Coord(k)     +
		     PU  * PV  * P3(NPolU).Coord(k) +
		     PU1 * PV  * P4(NPolV).Coord(k)   )          );
      }
      myPoles->SetValue(i,j,P);
    }
  }
}


//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void  GeomFill_Stretch::Init(const TColgp_Array1OfPnt&   P1, 
			  const TColgp_Array1OfPnt&   P2, 
			  const TColgp_Array1OfPnt&   P3, 
			  const TColgp_Array1OfPnt&   P4,
			  const TColStd_Array1OfReal& W1,
			  const TColStd_Array1OfReal& W2,
			  const TColStd_Array1OfReal& W3,
			  const TColStd_Array1OfReal& W4)
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

  Standard_Real NU = NPolU - 1;
  Standard_Real NV = NPolV - 1;
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

      Standard_Real W = 0.5 * ( PV1 * W1(i) + PV  * W3(i) +
			        PU  * W2(j) + PU1 * W4(j)  );

//      Standard_Real W = PV1 * W1(i) + PV  * W3(i) +
//	                PU  * W2(j) + PU1 * W4(j) -
//	              ( PU1 * PV1 * W1(1)     +
//	                PU  * PV1 * W2(1)     +
//	                PU  * PV  * W3(NPolU) +
//	                PU1 * PV  * W4(NPolV)   );
      myWeights->SetValue(i,j,W);
    }
  }
}


