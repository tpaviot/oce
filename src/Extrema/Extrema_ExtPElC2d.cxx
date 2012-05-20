// Created on: 1993-12-13
// Created by: Christophe MARION
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


#include <Precision.hxx>
#include <Extrema_ExtPElC2d.ixx>
#include <StdFail_NotDone.hxx>
#include <math_DirectPolynomialRoots.hxx>
#include <math_TrigonometricFunctionRoots.hxx>
#include <ElCLib.hxx>
#include <Standard_OutOfRange.hxx>
#include <Standard_NotImplemented.hxx>
//=============================================================================

Extrema_ExtPElC2d::Extrema_ExtPElC2d () { myDone = Standard_False; }
//=============================================================================

Extrema_ExtPElC2d::Extrema_ExtPElC2d 
  (const gp_Pnt2d&     P, 
   const gp_Lin2d&     L,
   const Standard_Real Tol,
   const Standard_Real Uinf, 
   const Standard_Real Usup)
{
  Perform(P, L, Tol, Uinf, Usup);
}

void Extrema_ExtPElC2d::Perform(const gp_Pnt2d&     P, 
				const gp_Lin2d&     L,
				const Standard_Real Tol,
				const Standard_Real Uinf, 
				const Standard_Real Usup)
{
  myDone = Standard_True;
  gp_Pnt2d OR, MyP;
  myNbExt = 0;

  gp_Vec2d V1 = gp_Vec2d(L.Direction());
  OR = L.Location();
  gp_Vec2d V(OR, P);
  Standard_Real Mydist = V1.Dot(V);
  if ((Mydist >= Uinf -Tol) && 
      (Mydist <= Usup+ Tol)){ 
    myNbExt = 1;
    MyP = OR.Translated(Mydist*V1);
    Extrema_POnCurv2d MyPOnCurve(Mydist, MyP);
    mySqDist[0] = P.SquareDistance(MyP);
    myPoint[0] = MyPOnCurve;
    myIsMin[0] = Standard_True;
  }
}

//=============================================================================

Extrema_ExtPElC2d::Extrema_ExtPElC2d 
  (const gp_Pnt2d&     P, 
   const gp_Circ2d&    C,
   const Standard_Real Tol,
   const Standard_Real Uinf, 
   const Standard_Real Usup)
{
  Perform(P, C, Tol, Uinf, Usup);
}

void Extrema_ExtPElC2d::Perform(const gp_Pnt2d&     P, 
				const gp_Circ2d&    C,
				const Standard_Real Tol,
				const Standard_Real Uinf, 
				const Standard_Real Usup)
{
  Standard_Real radius, U1, U2;
//  gp_Pnt2d OC, P1, P2, OL;
  gp_Pnt2d OC, P1, P2;
  OC      = C.Location();
  myNbExt = 0;
  
  if (OC.IsEqual(P, Precision::Confusion())) {
    myDone = Standard_False;
  }
  else {
    myDone = Standard_True;
    gp_Dir2d V(gp_Vec2d(P, OC));
    radius = C.Radius();
    P1 = OC.Translated(radius*V);
    U1 = ElCLib::Parameter(C, P1);
    U2 = U1 + M_PI;
    P2 = OC.Translated(-radius*V);
    Standard_Real myuinf = Uinf;
    ElCLib::AdjustPeriodic(Uinf, Uinf+2*M_PI, Precision::PConfusion(), myuinf, U1);
    ElCLib::AdjustPeriodic(Uinf, Uinf+2*M_PI, Precision::PConfusion(), myuinf, U2);
    if (((U1-2*M_PI-Uinf) < Tol) && ((U1-2*M_PI-Uinf) > -Tol)) U1 = Uinf;
    if (((U2-2*M_PI-Uinf) < Tol) && ((U2-2*M_PI-Uinf) > -Tol)) U2 = Uinf;

    if (((Uinf-U1) < Tol) && ((U1-Usup) < Tol)) {
      Extrema_POnCurv2d MyPOnCurve(U1, P1);
      mySqDist[0] = P.SquareDistance(P1);
      myPoint[0] = MyPOnCurve;
      myIsMin[0] = Standard_True;
      myNbExt++;
    }
    
    if (((Uinf-U2) < Tol) && ((U2-Usup) < Tol)) {
      Extrema_POnCurv2d MyPOnCurve(U2, P2);
      mySqDist[myNbExt] = P.SquareDistance(P2);
      myPoint[myNbExt] = MyPOnCurve;
      myIsMin[myNbExt] = Standard_True;
      myNbExt++;
    }
  }
}

//=============================================================================


Extrema_ExtPElC2d::Extrema_ExtPElC2d (const gp_Pnt2d&     P, 
				      const gp_Elips2d&   E,
				      const Standard_Real Tol,
				      const Standard_Real Uinf, 
				      const Standard_Real Usup)
{
  Perform(P, E, Tol, Uinf, Usup);
}



void Extrema_ExtPElC2d::Perform (const gp_Pnt2d&     P, 
				 const gp_Elips2d&   E,
				 const Standard_Real Tol,
				 const Standard_Real Uinf, 
				 const Standard_Real Usup)
{
//  gp_Pnt2d OR, P1, P2;
  gp_Pnt2d OR;
  OR = E.Location();
  
  Standard_Integer NoSol, NbSol;
  Standard_Real A = E.MajorRadius();
  Standard_Real B = E.MinorRadius();
  gp_Vec2d V(OR,P);

  if (OR.IsEqual(P, Precision::Confusion()) &&
      (Abs(A-B) <= Tol)) {
    myDone = Standard_False;
  }
  else {
    Standard_Real X = V.Dot(gp_Vec2d(E.XAxis().Direction()));
    Standard_Real Y = V.Dot(gp_Vec2d(E.YAxis().Direction()));

    math_TrigonometricFunctionRoots Sol(0.,(B*B-A*A)/2.,-B*Y,A*X,0.,Uinf,Usup);

    if (!Sol.IsDone()) { return; }
    gp_Pnt2d Cu;
    Standard_Real Us;
    NbSol = Sol.NbSolutions();
    myNbExt = 0;
    for (NoSol = 1; NoSol <= NbSol; NoSol++) {
      Us = Sol.Value(NoSol);
      Cu = ElCLib::Value(Us, E);
      mySqDist[myNbExt] = Cu.SquareDistance(P);
      myIsMin[myNbExt] = (NoSol == 0);
      myPoint[myNbExt] = Extrema_POnCurv2d(Us,Cu);
      myNbExt++;
    }
    myDone = Standard_True;
  }
}
//=============================================================================

Extrema_ExtPElC2d::Extrema_ExtPElC2d (const gp_Pnt2d&     P, 
				      const gp_Hypr2d&    C,
				      const Standard_Real Tol,
				      const Standard_Real Uinf, 
				      const Standard_Real Usup)
{
  Perform(P, C, Tol, Uinf, Usup);
}


void Extrema_ExtPElC2d::Perform(const gp_Pnt2d&     P, 
				const gp_Hypr2d&    H,
				const Standard_Real Tol,
				const Standard_Real Uinf,
				const Standard_Real Usup)
{
  gp_Pnt2d O = H.Location();
  myDone = Standard_False;
  myNbExt = 0;

  Standard_Real R = H.MajorRadius();
  Standard_Real r = H.MinorRadius();
  gp_Vec2d OPp(O,P);
  Standard_Real Tol2 = Tol * Tol;
  Standard_Real X = OPp.Dot(gp_Vec2d(H.XAxis().Direction()));
  Standard_Real Y = OPp.Dot(gp_Vec2d(H.YAxis().Direction()));
  Standard_Real C1 = (R*R+r*r)/4.;
  math_DirectPolynomialRoots Sol(C1,-(X*R+Y*r)/2.,0.,(X*R-Y*r)/2.,-C1);
  if (!Sol.IsDone()) { return; }
  gp_Pnt2d Cu;
  Standard_Real Us, Vs;
  Standard_Integer NbSol = Sol.NbSolutions();
  Standard_Boolean DejaEnr;
  Standard_Integer NoExt;
  gp_Pnt2d TbExt[4];
  for (Standard_Integer NoSol = 1; NoSol <= NbSol; NoSol++) {
    Vs = Sol.Value(NoSol);
    if (Vs > 0.) {
      Us = Log(Vs);
      if ((Us >= Uinf) && (Us <= Usup)) {
	Cu = ElCLib::Value(Us,H);
	DejaEnr = Standard_False;
	for (NoExt = 0; NoExt < myNbExt; NoExt++) {
	  if (TbExt[NoExt].SquareDistance(Cu) < Tol2) {
	    DejaEnr = Standard_True;
	    break;
	  }
	}
	if (!DejaEnr) {
	  TbExt[myNbExt] = Cu;
	  mySqDist[myNbExt] = Cu.SquareDistance(P);
	  myIsMin[myNbExt] = (NoSol == 0);
	  myPoint[myNbExt] = Extrema_POnCurv2d(Us,Cu);
	  myNbExt++;
	}
      } // if ((Us >= Uinf) && (Us <= Usup))
    } // if (Vs > 0.)
  } // for (Standard_Integer NoSol = 1; ...
  myDone = Standard_True;
}

//=============================================================================

Extrema_ExtPElC2d::Extrema_ExtPElC2d (const gp_Pnt2d&     P, 
				      const gp_Parab2d&   C,
				      const Standard_Real Tol,
				      const Standard_Real Uinf, 
				      const Standard_Real Usup)
{
  Perform(P, C, Tol, Uinf, Usup);
}


void Extrema_ExtPElC2d::Perform(const gp_Pnt2d&     P,
				const gp_Parab2d&   C,
				const Standard_Real Tol,
				const Standard_Real Uinf, 
				const Standard_Real Usup)
{
  myDone = Standard_False;
  myNbExt = 0;
  gp_Pnt2d O = C.Location();

  Standard_Real Tol2 = Tol * Tol;
  Standard_Real F = C.Focal();
  gp_Vec2d OPp (O,P);
  Standard_Real X = OPp.Dot(gp_Vec2d(C.MirrorAxis().Direction()));
  Standard_Real Y = OPp.Dot(gp_Vec2d(C.Axis().YAxis().Direction()));

  math_DirectPolynomialRoots Sol(1./(4.*F),0.,2.*F-X,-2.*F*Y);
  if (!Sol.IsDone()) { return; }
  gp_Pnt2d Cu;
  Standard_Real Us;
  Standard_Integer NbSol = Sol.NbSolutions();
  Standard_Boolean DejaEnr;
  Standard_Integer NoExt;
  gp_Pnt2d TbExt[3];
  for (Standard_Integer NoSol = 1; NoSol <= NbSol; NoSol++) {
    Us = Sol.Value(NoSol);
    if ((Us >= Uinf) && (Us <= Usup)) {
      Cu = ElCLib::Value(Us,C);
      DejaEnr = Standard_False;
      for (NoExt = 0; NoExt < myNbExt; NoExt++) {
	if (TbExt[NoExt].SquareDistance(Cu) < Tol2) {
	  DejaEnr = Standard_True;
	  break;
	}
      }
      if (!DejaEnr) {
	TbExt[myNbExt] = Cu;
	mySqDist[myNbExt] = Cu.SquareDistance(P);
	myIsMin[myNbExt] = (NoSol == 0);
	myPoint[myNbExt] = Extrema_POnCurv2d(Us,Cu);
	myNbExt++;
      }
    } // if ((Us >= Uinf) && (Us <= Usup))
  } // for (Standard_Integer NoSol = 1; ...
  myDone = Standard_True;
}
//=============================================================================

Standard_Boolean Extrema_ExtPElC2d::IsDone () const { return myDone; }
//=============================================================================

Standard_Integer Extrema_ExtPElC2d::NbExt () const
{
  if (!IsDone()) { StdFail_NotDone::Raise(); }
  return myNbExt;
}
//=============================================================================

Standard_Real Extrema_ExtPElC2d::SquareDistance (const Standard_Integer N) const
{
  if ((N < 1) || (N > NbExt())) { Standard_OutOfRange::Raise(); }
  return mySqDist[N-1];
}
//=============================================================================

Standard_Boolean Extrema_ExtPElC2d::IsMin (const Standard_Integer N) const
{
  if ((N < 1) || (N > NbExt())) { Standard_OutOfRange::Raise(); }
  return myIsMin[N-1];
}
//=============================================================================

Extrema_POnCurv2d Extrema_ExtPElC2d::Point (const Standard_Integer N) const
{
  if ((N < 1) || (N > NbExt())) { Standard_OutOfRange::Raise(); }
  return myPoint[N-1];
}
//=============================================================================
