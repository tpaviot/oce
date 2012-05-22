// Created on: 1995-07-18
// Created by: Modelistation
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


#include <Extrema_GenExtSS.ixx>
#include <math_Vector.hxx>
#include <math_FunctionSetRoot.hxx>

//=======================================================================
//function : Extrema_GenExtSS
//purpose  : 
//=======================================================================

Extrema_GenExtSS::Extrema_GenExtSS()
{
  myDone = Standard_False;
  myInit = Standard_False;
}

//=======================================================================
//function : Extrema_GenExtSS
//purpose  : 
//=======================================================================

Extrema_GenExtSS::Extrema_GenExtSS(const Adaptor3d_Surface& S1, 
				   const Adaptor3d_Surface& S2, 
				   const Standard_Integer NbU, 
				   const Standard_Integer NbV, 
				   const Standard_Real    Tol1, 
				   const Standard_Real    Tol2) : myF(S1,S2)
{
  Initialize(S2, NbU, NbV, Tol2);
  Perform(S1, Tol1);
}

//=======================================================================
//function : Extrema_GenExtSS
//purpose  : 
//=======================================================================

Extrema_GenExtSS::Extrema_GenExtSS(const Adaptor3d_Surface& S1, 
				   const Adaptor3d_Surface& S2, 
				   const Standard_Integer NbU, 
				   const Standard_Integer NbV, 
				   const Standard_Real U1min, 
				   const Standard_Real U1sup, 
				   const Standard_Real V1min, 
				   const Standard_Real V1sup, 
				   const Standard_Real U2min, 
				   const Standard_Real U2sup, 
				   const Standard_Real V2min, 
				   const Standard_Real V2sup, 
				   const Standard_Real Tol1, 
				   const Standard_Real Tol2): myF(S1, S2)
{
  Initialize(S2, NbU, NbV, U2min,U2sup,V2min,V2sup,Tol2);
  Perform(S1, U1min,U1sup,V1min,V1sup,Tol1);
}

//=======================================================================
//function : Initialize
//purpose  : 
//=======================================================================

void Extrema_GenExtSS::Initialize(const Adaptor3d_Surface& S2, 
				  const Standard_Integer NbU, 
				  const Standard_Integer NbV, 
				  const Standard_Real Tol2)
{
  myu2min = S2.FirstUParameter();
  myu2sup = S2.LastUParameter();
  myv2min = S2.FirstVParameter();
  myv2sup = S2.LastVParameter();
  Initialize(S2,NbU,NbV,myu2min,myu2sup,myv2min,myv2sup,Tol2);
}

//=======================================================================
//function : Initialize
//purpose  : 
//=======================================================================

void Extrema_GenExtSS::Initialize(const Adaptor3d_Surface& S2, 
				  const Standard_Integer NbU, 
				  const Standard_Integer NbV, 
				  const Standard_Real U2min, 
				  const Standard_Real U2sup, 
				  const Standard_Real V2min, 
				  const Standard_Real V2sup, 
				  const Standard_Real Tol2)
{
  myS2 = (Adaptor3d_SurfacePtr)&S2;
  mypoints1 = new TColgp_HArray2OfPnt(0,NbU+1,0,NbV+1);
  mypoints2 = new TColgp_HArray2OfPnt(0,NbU+1,0,NbV+1);
  myusample = NbU;
  myvsample = NbV;
  myu2min = U2min;
  myu2sup = U2sup;
  myv2min = V2min;
  myv2sup = V2sup;
  mytol2 = Tol2;

// Parametrage de l echantillon sur S2

  Standard_Real PasU = myu2sup - myu2min;
  Standard_Real PasV = myv2sup - myv2min;
  Standard_Real U0 = PasU / myusample / 100.;
  Standard_Real V0 = PasV / myvsample / 100.;
  gp_Pnt P1;
  PasU = (PasU - U0) / (myusample - 1);
  PasV = (PasV - V0) / (myvsample - 1);
  U0 = myu2min + U0/2.;
  V0 = myv2min + V0/2.;

// Calcul des distances

  Standard_Integer NoU, NoV;
  Standard_Real U, V;
  for ( NoU = 1, U = U0; NoU <= myusample; NoU++, U += PasU) {
    for ( NoV = 1, V = V0; NoV <= myvsample; NoV++, V += PasV) {
      P1 = myS2->Value(U, V);
      mypoints2->SetValue(NoU,NoV,P1);
    }
  }
}

//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================

void Extrema_GenExtSS::Perform(const Adaptor3d_Surface& S1,
			       const Standard_Real    Tol1)
{
  myu1min = S1.FirstUParameter();
  myu1sup = S1.LastUParameter();
  myv1min = S1.FirstVParameter();
  myv1sup = S1.LastVParameter();
  Perform(S1, myu1min, myu1sup,myv1min,myv1sup,Tol1);
}

//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================

void Extrema_GenExtSS::Perform(const Adaptor3d_Surface& S1,
			       const Standard_Real U1min, 
			       const Standard_Real U1sup, 
			       const Standard_Real V1min, 
			       const Standard_Real V1sup, 
			       const Standard_Real Tol1)
{
  myF.Initialize(S1,*myS2);
  myu1min = U1min;
  myu1sup = U1sup;
  myv1min = V1min;
  myv1sup = V1sup;
  mytol1 = Tol1;

  Standard_Real U1, V1, U2, V2;
  Standard_Integer NoU1, NoV1, NoU2, NoV2;
  gp_Pnt P1, P2;

// Parametrage de l echantillon sur S1

  Standard_Real PasU1 = myu1sup - myu1min;
  Standard_Real PasV1 = myv1sup - myv1min;
  Standard_Real U10 = PasU1 / myusample / 100.;
  Standard_Real V10 = PasV1 / myvsample / 100.;
  PasU1 = (PasU1 - U10) / (myusample - 1);
  PasV1 = (PasV1 - V10) / (myvsample - 1);
  U10 = myu1min + U10/2.;
  V10 = myv1min + V10/2.;

  Standard_Real PasU2 = myu2sup - myu2min;
  Standard_Real PasV2 = myv2sup - myv2min;
  Standard_Real U20 = PasU2 / myusample / 100.;
  Standard_Real V20 = PasV2 / myvsample / 100.;
  PasU2 = (PasU2 - U20) / (myusample - 1);
  PasV2 = (PasV2 - V20) / (myvsample - 1);
  U20 = myu2min + U20/2.;
  V20 = myv2min + V20/2.;

// Calcul des distances

  for ( NoU1 = 1, U1 = U10; NoU1 <= myusample; NoU1++, U1 += PasU1) {
    for ( NoV1 = 1, V1 = V10; NoV1 <= myvsample; NoV1++, V1 += PasV1) {
      P1 = S1.Value(U1, V1);
      mypoints1->SetValue(NoU1,NoV1,P1);
    }
  }
  
/*
b- Calcul des minima:
   -----------------
   b.a) Initialisations:
*/

  math_Vector Tol(1, 4);
  Tol(1) = mytol1;
  Tol(2) = mytol1;
  Tol(3) = mytol2;
  Tol(4) = mytol2;
  math_Vector UV(1,4), UVinf(1,4), UVsup(1,4);
  UVinf(1) = myu1min;
  UVinf(2) = myv1min;
  UVinf(3) = myu2min;
  UVinf(4) = myv2min;
  UVsup(1) = myu1sup;
  UVsup(2) = myv1sup;
  UVsup(3) = myu2sup;
  UVsup(4) = myv2sup;
  

  Standard_Real distmin = RealLast(), distmax = 0.0, TheDist;

  Standard_Integer N1Umin=0,N1Vmin=0,N2Umin=0,N2Vmin=0;
  gp_Pnt PP1min, PP2min;
  Standard_Integer N1Umax=0,N1Vmax=0,N2Umax=0,N2Vmax=0;
  gp_Pnt PP1max, PP2max;

  for ( NoU1 = 1, U1 = U10; NoU1 <= myusample; NoU1++, U1 += PasU1) {
    for ( NoV1 = 1, V1 = V10; NoV1 <= myvsample; NoV1++, V1 += PasV1) {
      P1 = mypoints1->Value(NoU1, NoV1);
      for ( NoU2 = 1, U2 = U20; NoU2 <= myusample; NoU2++, U2 += PasU2) {
	for ( NoV2 = 1, V2 = V20; NoV2 <= myvsample; NoV2++, V2 += PasV2) {
	  P2 = mypoints2->Value(NoU2, NoV2);
	  TheDist = P1.SquareDistance(P2);
	  if (TheDist < distmin) {
	    distmin = TheDist;
	    N1Umin = NoU1;
	    N1Vmin = NoV1;
	    N2Umin = NoU2;
	    N2Vmin = NoV2;
	    PP1min = P1;
	    PP2min = P2;
	  }
	  if (TheDist > distmax) {
	    distmax = TheDist;
	    N1Umax = NoU1;
	    N1Vmax = NoV1;
	    N2Umax = NoU2;
	    N2Vmax = NoV2;
	    PP1max = P1;
	    PP2max = P2;
	  }
	}
      }
    }
  }
  
  UV(1) = U10 + (N1Umin - 1) * PasU1;
  UV(2) = V10 + (N1Vmin - 1) * PasV1;
  UV(3) = U20 + (N2Umin - 1) * PasU2;
  UV(4) = V20 + (N2Vmin - 1) * PasV2;

  math_FunctionSetRoot SR1 (myF,UV,Tol,UVinf,UVsup);

  UV(1) = U10 + (N1Umax - 1) * PasU1;
  UV(2) = V10 + (N1Vmax - 1) * PasV1;
  UV(3) = U20 + (N2Umax - 1) * PasU2;
  UV(4) = V20 + (N2Vmax - 1) * PasV2;

  math_FunctionSetRoot SR2 (myF,UV,Tol,UVinf,UVsup);

  myDone = Standard_True;
}

//=======================================================================
//function : IsDone
//purpose  : 
//=======================================================================

Standard_Boolean Extrema_GenExtSS::IsDone() const 
{
  return myDone;
}

//=======================================================================
//function : NbExt
//purpose  : 
//=======================================================================

Standard_Integer Extrema_GenExtSS::NbExt() const 
{
  if (!IsDone()) { StdFail_NotDone::Raise(); }
  return myF.NbExt();

}

//=======================================================================
//function : Value
//purpose  : 
//=======================================================================

Standard_Real Extrema_GenExtSS::SquareDistance(const Standard_Integer N) const 
{  
  if (!IsDone()) { StdFail_NotDone::Raise(); }
  return myF.SquareDistance(N);
}

//=======================================================================
//function : PointOnS1
//purpose  : 
//=======================================================================

Extrema_POnSurf Extrema_GenExtSS::PointOnS1(const Standard_Integer N) const 
{
  if (!IsDone()) { StdFail_NotDone::Raise(); }
  return myF.PointOnS1(N);
}

//=======================================================================
//function : PointOnS2
//purpose  : 
//=======================================================================

Extrema_POnSurf Extrema_GenExtSS::PointOnS2(const Standard_Integer N) const 
{
  if (!IsDone()) { StdFail_NotDone::Raise(); }
  return myF.PointOnS2(N);
}

//=======================================================================
//function : Bidon
//purpose  : 
//=======================================================================

Adaptor3d_SurfacePtr Extrema_GenExtSS::Bidon() const 
{
  return (Adaptor3d_SurfacePtr)0L;
}

