// Created on: 1999-09-16
// Created by: Edward AGAPOV
// Copyright (c) 1999 Matra Datavision
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


#include <Standard_NotImplemented.hxx>
#include <Standard_OutOfRange.hxx>
#include <StdFail_NotDone.hxx>
#include <Adaptor3d_HCurve.hxx>
#include <ElCLib.hxx>
#include <Extrema_ExtPElC.hxx>
#include <Extrema_ExtPExtS.hxx>
#include <Extrema_POnCurv.hxx>
#include <Extrema_POnSurf.hxx>
#include <Precision.hxx>
#include <gp.hxx>
#include <gp_Ax2.hxx>
#include <gp_Dir.hxx>
#include <gp_Lin.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <math_FunctionSetRoot.hxx>
#include <math_Vector.hxx>
#include <Adaptor3d_SurfaceOfLinearExtrusion.hxx>

static gp_Ax2 GetPosition (const Handle(Adaptor3d_HCurve)& C);
     
static void PerformExtPElC (Extrema_ExtPElC& E,
			    const gp_Pnt& P,
			    const Handle(Adaptor3d_HCurve)& C,
			    const Standard_Real Tol);
     
static Standard_Boolean
  IsCaseAnalyticallyComputable (const GeomAbs_CurveType& theType,
				const gp_Ax2& theCurvePos,
				const gp_Dir& theSurfaceDirection) ;

static gp_Pnt GetValue(const Standard_Real U,
		       const Handle(Adaptor3d_HCurve)& C);
//=======================================================================
//function : Project
//purpose  : Returns the projection of a point <Point> on a plane 
//           <ThePlane>  along a direction <TheDir>.
//=======================================================================
static gp_Pnt ProjectPnt(const gp_Ax2& ThePlane,
			 const gp_Dir& TheDir,
			 const gp_Pnt& Point) 
{
  gp_Vec PO(Point,ThePlane.Location());
  Standard_Real Alpha = PO * gp_Vec(ThePlane.Direction());
  Alpha /= TheDir * ThePlane.Direction();
  gp_Pnt P;
  P.SetXYZ(Point.XYZ() + Alpha * TheDir.XYZ());
  return P;
}

//=======================================================================
//function : IsOriginalPnt
//purpose  : 
//=======================================================================

static Standard_Boolean IsOriginalPnt (const gp_Pnt& P,
				       const Extrema_POnSurf* Points,
				       const Standard_Integer NbPoints)
{
  for (Standard_Integer i=1; i<=NbPoints; i++) {
    if (Points[i-1].Value().IsEqual(P, Precision::Confusion())) {
      return Standard_False;
    }
  }
  return Standard_True;
}

//=======================================================================
//function : MakePreciser
//purpose  : 
//=======================================================================

void Extrema_ExtPExtS::MakePreciser (Standard_Real& U,
				     const gp_Pnt& P,
				     const Standard_Boolean isMin,
				     const gp_Ax2& OrtogSection) const
{
  if (U>myusup) {
    U = myusup;
  } else if (U<myuinf) {
    U = myuinf;
  } else {
    
    Standard_Real step = (myusup - myuinf) / 30, D2e, D2next ,D2prev;
    gp_Pnt
      Pe = ProjectPnt (OrtogSection, myDirection, GetValue(U,myC)),
      Pprev = ProjectPnt (OrtogSection, myDirection, GetValue(U-step, myC)),
      Pnext = ProjectPnt (OrtogSection, myDirection, GetValue(U+step, myC));
    D2e = P.SquareDistance(Pe),
    D2next = P.SquareDistance(Pnext),
    D2prev = P.SquareDistance(Pprev);
    Standard_Boolean notFound;
    if (isMin) 
      notFound =  (D2e > D2prev || D2e > D2next);
    else 
      notFound = (D2e < D2prev || D2e < D2next);
    
    if (notFound && (D2e < D2next && isMin)) {
      step = -step;
      D2next = D2prev;
      Pnext = Pprev;
    }
    while (notFound) {
      U = U + step;
      if (U > myusup) {
	U = myusup;
	break;
      }
      if (U < myuinf) {
	U = myuinf;
	break;
      }
      D2e = D2next;
      Pe = Pnext;
      Pnext = ProjectPnt (OrtogSection, myDirection, GetValue(U+step, myC));
      D2next = P.SquareDistance(Pnext);
      if (isMin) 
	notFound = D2e > D2next;
      else 
	notFound = D2e < D2next;
    }
  }
}
//=============================================================================

Extrema_ExtPExtS::Extrema_ExtPExtS ()
{
  myDone = Standard_False;
}

//=============================================================================

Extrema_ExtPExtS::Extrema_ExtPExtS (const gp_Pnt&       P, 
				    const Adaptor3d_SurfaceOfLinearExtrusion&  S,
				    const Standard_Real    Umin,
				    const Standard_Real    Usup,
				    const Standard_Real    Vmin,
				    const Standard_Real    Vsup,
				    const Standard_Real    TolU, 
				    const Standard_Real    TolV) 
{
  Initialize (S,
	      Umin, Usup, Vmin, Vsup,
	      TolU, TolV);
  Perform(P);
}
//=============================================================================

Extrema_ExtPExtS::Extrema_ExtPExtS (const gp_Pnt&       P, 
				    const Adaptor3d_SurfaceOfLinearExtrusion&  S,
				    const Standard_Real    TolU, 
				    const Standard_Real    TolV)
{
  Initialize (S,
	      S.FirstUParameter(), S.LastUParameter(),
	      S.FirstVParameter(), S.LastVParameter(),
	      TolU, TolV);
  Perform(P);
}
//=======================================================================
//function : Initialize
//purpose  : 
//=======================================================================

void Extrema_ExtPExtS::Initialize(const Adaptor3d_SurfaceOfLinearExtrusion& S,
				  const Standard_Real Uinf,
				  const Standard_Real Usup,
				  const Standard_Real Vinf,
				  const Standard_Real Vsup,
				  const Standard_Real TolU,
				  const Standard_Real TolV)
{
  myuinf=Uinf;
  myusup=Usup;
  mytolu=TolU;
  
  myvinf=Vinf;
  myvsup=Vsup;
  mytolv=TolV;
  
  Handle(Adaptor3d_HCurve) anACurve = S.BasisCurve();

  myF.Initialize(S);
  myC = anACurve;
  myPosition = GetPosition(myC);
  myDirection = S.Direction();
  myIsAnalyticallyComputable = //Standard_False;
    IsCaseAnalyticallyComputable (myC->GetType(),myPosition,myDirection);
  
  if (!myIsAnalyticallyComputable)
    
    myExtPS.Initialize(S, 32, 32,
		       Uinf, Usup, Vinf, Vsup,
		       TolU, TolV);
}


//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================

void Extrema_ExtPExtS::Perform (const gp_Pnt& P)
{
  myDone = Standard_False;
  myNbExt = 0;
  
  if (!myIsAnalyticallyComputable) {
    myExtPS.Perform(P);
    myDone = myExtPS.IsDone();
//  modified by NIZHNY-EAP Wed Nov 17 12:59:08 1999 ___BEGIN___
    myNbExt = myExtPS.NbExt();
//  modified by NIZHNY-EAP Wed Nov 17 12:59:09 1999 ___END___
    return;
  }
  
  gp_Pnt Pe, Pp = ProjectPnt(myPosition,myDirection,P);
  Extrema_ExtPElC anExt;
  PerformExtPElC(anExt, Pp, myC, mytolu);
  if (!anExt.IsDone()) return;
  
  gp_Ax2 anOrtogSection (P, myDirection);
  Standard_Real U,V;
  Standard_Boolean
    isMin,
    isSimpleCase =
      myDirection.IsParallel(myPosition.Direction(),Precision::Angular());
  Standard_Integer i, aNbExt = anExt.NbExt();
  math_Vector UV(1,2), Tol(1,2), UVinf(1,2), UVsup(1,2);
  Tol(1) = mytolu;   Tol(2) = mytolv;
  UVinf(1) = myuinf; UVinf(2) = myvinf;
  UVsup(1) = myusup; UVsup(2) = myvsup;
  
  
  for (i=1; i<=aNbExt; i++) {
    Extrema_POnCurv POC=anExt.Point(i);
    U = POC.Parameter();
    //// modified by jgv, 23.12.2008 for OCC17194 ////
    if (myC->IsPeriodic())
      {
	Standard_Real U2 = U;
	ElCLib::AdjustPeriodic(myuinf, myuinf + 2.*M_PI, Precision::PConfusion(), U, U2);
      }
    //////////////////////////////////////////////////
    gp_Pnt E = POC.Value();
    Pe = ProjectPnt(anOrtogSection, myDirection, E);
    
    if (isSimpleCase) {
      V = gp_Vec(E,Pe) * gp_Vec(myDirection);
      // modified by NIZHNY-MKK  Thu Sep 18 14:46:14 2003.BEGIN
      //       myPoint[++myNbExt] = Extrema_POnSurf(U, V, Pe);
      //       myValue[myNbExt] = anExt.Value(i);
      myPoint[myNbExt] = Extrema_POnSurf(U, V, Pe);
      mySqDist[myNbExt] = anExt.SquareDistance(i);
      myNbExt++;
      // modified by NIZHNY-MKK  Thu Sep 18 14:46:18 2003.END
    }
    else {
      myF.SetPoint(P);
      isMin = anExt.IsMin(i);//( Pp.Distance(GetValue(U+10,myC)) > anExt.Value(i) );
      
      MakePreciser(U, P, isMin, anOrtogSection);
      E = GetValue(U, myC);
      Pe = ProjectPnt (anOrtogSection, myDirection, E),
      V = gp_Vec(E,Pe) * gp_Vec(myDirection);
      UV(1) = U;         UV(2) = V;
      math_FunctionSetRoot aFSR (myF,UV,Tol,UVinf,UVsup);
//      for (Standard_Integer k=1 ; k <= myF.NbExt(); 
      Standard_Integer k;
      for ( k=1 ; k <= myF.NbExt(); k++) {
	if (IsOriginalPnt(myF.Point(k).Value(), myPoint, myNbExt)) {
	  // modified by NIZHNY-MKK  Thu Sep 18 14:46:41 2003.BEGIN
	  // 	  myPoint[++myNbExt] = myF.Point(k);
	  // 	  myValue[myNbExt] = myF.Value(k);
	  myPoint[myNbExt] = myF.Point(k);
	  mySqDist[myNbExt] = myF.SquareDistance(k);
	  myNbExt++;
	  // modified by NIZHNY-MKK  Thu Sep 18 14:46:43 2003.END
	}
      }
      // try symmetric point
      U *= -1;
      MakePreciser(U, P, isMin, anOrtogSection);
      E = GetValue(U, myC);
      Pe = ProjectPnt (anOrtogSection, myDirection, E),
      V = gp_Vec(E,Pe) * gp_Vec(myDirection); 
      UV(1) = U; UV(2) = V;
      
      aFSR.Perform (myF,UV,UVinf,UVsup);
      
      for (k=1 ; k <= myF.NbExt(); k++) {
	if (IsOriginalPnt(myF.Point(k).Value(), myPoint, myNbExt)) {
	  // modified by NIZHNY-MKK  Thu Sep 18 14:46:59 2003.BEGIN
	  // 	  myPoint[++myNbExt] = myF.Point(k);
	  // 	  myValue[myNbExt] = myF.Value(k);
	  myPoint[myNbExt] = myF.Point(k);
	  mySqDist[myNbExt] = myF.SquareDistance(k);
	  myNbExt++;
	  // modified by NIZHNY-MKK  Thu Sep 18 14:47:04 2003.END
	}
      }
    }
  }
  myDone = Standard_True;
  return;
}

//=============================================================================

Standard_Boolean Extrema_ExtPExtS::IsDone () const { return myDone; }
//=============================================================================

Standard_Integer Extrema_ExtPExtS::NbExt () const
{
  if (!IsDone()) { StdFail_NotDone::Raise(); }
  if (myIsAnalyticallyComputable)
    return myNbExt;
  else
    return myExtPS.NbExt();
}
//=============================================================================

Standard_Real Extrema_ExtPExtS::SquareDistance (const Standard_Integer N) const
{
  if (!IsDone()) { StdFail_NotDone::Raise(); }
  if ((N < 1) || (N > myNbExt)) { Standard_OutOfRange::Raise(); }
  if (myIsAnalyticallyComputable)
    // modified by NIZHNY-MKK  Thu Sep 18 14:48:39 2003.BEGIN
    //     return myValue[N];
    return mySqDist[N-1];
  // modified by NIZHNY-MKK  Thu Sep 18 14:48:42 2003.END
  else
    return myExtPS.SquareDistance(N);
}
//=============================================================================

Extrema_POnSurf Extrema_ExtPExtS::Point (const Standard_Integer N) const
{
  if (!IsDone()) { StdFail_NotDone::Raise(); }
  if ((N < 1) || (N > myNbExt)) { Standard_OutOfRange::Raise(); }
  if (myIsAnalyticallyComputable) {
    // modified by NIZHNY-MKK  Thu Sep 18 14:47:40 2003.BEGIN
    //     return myPoint[N];
    return myPoint[N-1];
  }
  // modified by NIZHNY-MKK  Thu Sep 18 14:47:43 2003.END
  else
    return myExtPS.Point(N);
}
//=============================================================================


static gp_Ax2 GetPosition (const Handle(Adaptor3d_HCurve)& C)
{
  switch (C->GetType()) {
  case GeomAbs_Line: {
    gp_Lin L = C->Line();
    gp_Pln Pln = gp_Pln(L.Location(), L.Direction());
    //:abv 30.05.02: OCC  - use constructor instead of Set...s() to avoid exception
    gp_Ax2 Pos ( Pln.Location(), Pln.Position().Direction(), Pln.Position().XDirection() );
//     Pos.SetAxis(Pln.XAxis());
//     Pos.SetXDirection(Pln.YAxis().Direction());
//     Pos.SetYDirection(Pln.Position().Direction());
    return Pos;
  }
  case GeomAbs_Circle:
    return  C->Circle().Position();
  case GeomAbs_Ellipse:
    return  C->Ellipse().Position();
  case GeomAbs_Hyperbola:
    return  C->Hyperbola().Position();
  case GeomAbs_Parabola:
    return  C->Parabola().Position();
  default: 
    return gp_Ax2 ();
  }
}
//=============================================================================

static void PerformExtPElC (Extrema_ExtPElC& E,
			    const gp_Pnt& P,
			    const Handle(Adaptor3d_HCurve)& C,
			    const Standard_Real Tol)
{
  switch (C->GetType()) {
  case GeomAbs_Hyperbola:
    E.Perform(P, C->Hyperbola(), Tol, -Precision::Infinite(),Precision::Infinite());
    return;
  case GeomAbs_Line:
    E.Perform(P, C->Line(), Tol, -Precision::Infinite(),Precision::Infinite());
    return;
  case GeomAbs_Circle:
    E.Perform(P, C->Circle(), Tol, 0.0, 2.0 * M_PI);
    return;
  case GeomAbs_Ellipse:
    E.Perform(P, C->Ellipse(), Tol, 0.0, 2.0 * M_PI);
    return;
  case GeomAbs_Parabola:
    E.Perform(P, C->Parabola(), Tol, -Precision::Infinite(),Precision::Infinite());
    return;
  default:
    return;
  }
}

//=======================================================================
//function : IsCaseAnalyticallyComputable
//purpose  : 
//=======================================================================

static Standard_Boolean IsCaseAnalyticallyComputable
  (const GeomAbs_CurveType& theType,
   const gp_Ax2& theCurvePos,
   const gp_Dir& theSurfaceDirection) 
{
  // check type
  switch (theType) {
  case GeomAbs_Line:
  case GeomAbs_Circle:
  case GeomAbs_Ellipse:
  case GeomAbs_Hyperbola:
  case GeomAbs_Parabola:
    break;
  default:
    return  Standard_False;
  }
  // check if it is a plane
  if (Abs(theCurvePos.Direction() * theSurfaceDirection) <= gp::Resolution())
    return Standard_False;
  else
    return Standard_True;
}
//=======================================================================
//function : GetValue
//purpose  : 
//=======================================================================

static gp_Pnt GetValue(const Standard_Real U,
		       const Handle(Adaptor3d_HCurve)& C)
{
  switch (C->GetType()) {
  case GeomAbs_Line:
    return ElCLib::Value(U, C->Line());
  case GeomAbs_Circle:
    return ElCLib::Value(U, C->Circle());
  case GeomAbs_Ellipse:
    return ElCLib::Value(U, C->Ellipse());
  case GeomAbs_Hyperbola:
    return ElCLib::Value(U, C->Hyperbola());
  case GeomAbs_Parabola:
    return ElCLib::Value(U, C->Parabola());
  default:
    return gp_Pnt();
  }
}
//=======================================================================
//function : GetU
//purpose  : 
//=======================================================================
//#ifdef DEB
//static Standard_Real GetU(const gp_Vec& vec,
//			  const gp_Pnt& P,
//			  const Handle(Adaptor3d_HCurve)& C)
//{
//  switch (C->GetType()) {
//  case GeomAbs_Line:
//    return ElCLib::Parameter(C->Line().Translated(vec), P);
//  case GeomAbs_Circle:
//    return ElCLib::Parameter(C->Circle().Translated(vec), P);
//  case GeomAbs_Ellipse:
//    return ElCLib::Parameter(C->Ellipse().Translated(vec), P);
//  case GeomAbs_Hyperbola:
//    return ElCLib::Parameter(C->Hyperbola().Translated(vec), P);
//  case GeomAbs_Parabola:
//    return ElCLib::Parameter(C->Parabola().Translated(vec), P);
//  default:
//    return 0;
//  }
//}
//#endif
