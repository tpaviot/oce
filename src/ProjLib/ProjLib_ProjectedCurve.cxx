// Created on: 1993-08-25
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



//  Modified by skv - Wed Aug 11 15:45:58 2004 OCC6272

#include <GeomAbs_SurfaceType.hxx>
#include <Standard_NoSuchObject.hxx>
#include <Standard_NotImplemented.hxx>
#include <ProjLib_ProjectedCurve.hxx>
#include <ProjLib_CompProjectedCurve.hxx>
#include <ProjLib_HCompProjectedCurve.hxx>
#include <ProjLib_ComputeApproxOnPolarSurface.hxx>
#include <ProjLib_ComputeApprox.hxx>
#include <ProjLib_Projector.hxx>
#include <Handle_Adaptor3d_HCurve.hxx>
#include <Handle_Adaptor3d_HSurface.hxx>
#include <Adaptor3d_HCurve.hxx>
#include <Adaptor3d_HSurface.hxx>
#include <Approx_CurveOnSurface.hxx>
#include <ProjLib_Plane.hxx>
#include <ProjLib_Cylinder.hxx>
#include <ProjLib_Cone.hxx>
#include <ProjLib_Sphere.hxx>
#include <ProjLib_Torus.hxx>
#include <Precision.hxx>
#include <Handle_Geom_BSplineCurve.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Handle_Geom2d_BSplineCurve.hxx>
#include <Geom2d_BezierCurve.hxx>
#include <Handle_Geom2d_BezierCurve.hxx>
#include <Handle_Adaptor2d_HCurve2d.hxx>
#include <gp_Vec2d.hxx>
#include <StdFail_NotDone.hxx>
#include <gp_XY.hxx>
#include <TColgp_HArray1OfPnt2d.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <Geom2dConvert_CompCurveToBSplineCurve.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TColgp_HArray1OfVec2d.hxx>
#include <TColStd_HArray1OfBoolean.hxx>
#include <BSplCLib.hxx>
#include <GeomAbs_IsoType.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <ElCLib.hxx>
#include <GeomLib.hxx>

//=======================================================================
//function : IsoIsDeg
//purpose  : 
//=======================================================================

static Standard_Boolean IsoIsDeg  (const Adaptor3d_Surface& S,
				   const Standard_Real      Param,
				   const GeomAbs_IsoType    IT,
				   const Standard_Real      TolMin,
				   const Standard_Real      TolMax) 
{
    Standard_Real U1=0.,U2=0.,V1=0.,V2=0.,T;
    Standard_Boolean Along = Standard_True;
    U1 = S.FirstUParameter();
    U2 = S.LastUParameter();
    V1 = S.FirstVParameter();
    V2 = S.LastVParameter();
    gp_Vec D1U,D1V;
    gp_Pnt P;
    Standard_Real Step,D1NormMax;
    if (IT == GeomAbs_IsoV) 
    {
      Step = (U2 - U1)/10;
      D1NormMax=0.;
      for (T=U1;T<=U2;T=T+Step) 
      {
        S.D1(T,Param,P,D1U,D1V);
        D1NormMax=Max(D1NormMax,D1U.Magnitude());
      }

      if (D1NormMax >TolMax || D1NormMax < TolMin ) 
           Along = Standard_False;
    }
    else 
    {
      Step = (V2 - V1)/10;
      D1NormMax=0.;
      for (T=V1;T<=V2;T=T+Step) 
      {
	S.D1(Param,T,P,D1U,D1V);
        D1NormMax=Max(D1NormMax,D1V.Magnitude());
      }

      if (D1NormMax >TolMax || D1NormMax < TolMin ) 
           Along = Standard_False;


    }
    return Along;
}

//=======================================================================
//function : TrimC3d
//purpose  : 
//=======================================================================

static void TrimC3d(Handle(Adaptor3d_HCurve)& myCurve,
		    Standard_Boolean* IsTrimmed,
		    const Standard_Real dt,
		    const gp_Pnt& Pole,
                    Standard_Integer* SingularCase,
                    const Standard_Integer NumberOfSingularCase)
{
  Standard_Real f = myCurve->FirstParameter();
  Standard_Real l = myCurve->LastParameter();

  gp_Pnt P = myCurve->Value(f);

  if(P.Distance(Pole) < Precision::Confusion()) {
    IsTrimmed[0] = Standard_True;
    f = f+dt;
    myCurve = myCurve->Trim(f, l, Precision::Confusion());
    SingularCase[0] = NumberOfSingularCase;
  }
  
  P = myCurve->Value(l);
  if(P.Distance(Pole) < Precision::Confusion()) {
    IsTrimmed[1] = Standard_True;
    l = l-dt;
    myCurve = myCurve->Trim(f, l, Precision::Confusion());
    SingularCase[1] = NumberOfSingularCase;
  }
}

//=======================================================================
//function : ExtendC2d
//purpose  : 
//=======================================================================

static void ExtendC2d(Handle(Geom2d_BSplineCurve)& aRes,
		      const Standard_Real t,
		      const Standard_Real dt,
		      const Standard_Real u1,
		      const Standard_Real u2,
		      const Standard_Real v1,
		      const Standard_Real v2,
                      const Standard_Integer FirstOrLast,
                      const Standard_Integer NumberOfSingularCase)
{
  Standard_Real theParam = (FirstOrLast == 0)? aRes->FirstParameter()
    : aRes->LastParameter();

  gp_Pnt2d                              aPBnd;
  gp_Vec2d                              aVBnd;
  gp_Dir2d                              aDBnd;
  Handle(Geom2d_TrimmedCurve)           aSegment;
  Geom2dConvert_CompCurveToBSplineCurve aCompCurve(aRes, Convert_RationalC1);
  Standard_Real                         aTol = Precision::Confusion();

  aRes->D1(theParam, aPBnd, aVBnd);
  aDBnd.SetXY(aVBnd.XY());
  gp_Lin2d aLin(aPBnd, aDBnd); //line in direction of derivative

  gp_Pnt2d thePole;
  gp_Dir2d theBoundDir;
  switch (NumberOfSingularCase)
  {
  case 1:
    {
      thePole.SetCoord(u1, v1);
      theBoundDir.SetCoord(0., 1.);
      break;
    }
  case 2:
    {
      thePole.SetCoord(u2, v1);
      theBoundDir.SetCoord(0., 1.);
      break;
    }
  case 3:
    {
      thePole.SetCoord(u1, v1);
      theBoundDir.SetCoord(1., 0.);
      break;
    }
  case 4:
    {
      thePole.SetCoord(u1, v2);
      theBoundDir.SetCoord(1., 0.);
      break;
    }
  }
  gp_Lin2d BoundLin(thePole, theBoundDir); //one of the bounds of rectangle

  Standard_Real U1x = BoundLin.Direction().X();
  Standard_Real U1y = BoundLin.Direction().Y();
  Standard_Real U2x = aLin.Direction().X();
  Standard_Real U2y = aLin.Direction().Y();
  Standard_Real Uo21x = aLin.Location().X() - BoundLin.Location().X();
  Standard_Real Uo21y = aLin.Location().Y() - BoundLin.Location().Y();
  
  Standard_Real D = U1y*U2x-U1x*U2y;
  
  Standard_Real ParOnLin = (Uo21y * U1x - Uo21x * U1y)/D; //parameter of intersection point
  
  Handle(Geom2d_Line) aSegLine = new Geom2d_Line(aLin);
  aSegment = (FirstOrLast == 0)?
    new Geom2d_TrimmedCurve(aSegLine, ParOnLin, 0.) :
    new Geom2d_TrimmedCurve(aSegLine, 0., ParOnLin);

  aCompCurve.Add(aSegment, aTol);
  aRes = aCompCurve.BSplineCurve();
  
  /*  
  gp_Pnt2d P0;
  gp_Vec2d V01, V02;
  aRes->D2(t, P0, V01, V02);
  
  gp_XY XYP1 = P0.XY() + V01.XY()*dt + .5*V02.XY()*dt*dt;
  
  gp_Vec2d V11 = V01 + V02*dt;
  
  if(XYP1.X() < u1) XYP1.SetX(u1);
  if(XYP1.X() > u2) XYP1.SetX(u2);
  if(XYP1.Y() < v1) XYP1.SetY(v1);
  if(XYP1.Y() > v2) XYP1.SetY(v2);
  
  Handle(TColgp_HArray1OfPnt2d) aPnts = new TColgp_HArray1OfPnt2d(1, 2);
  Handle(TColStd_HArray1OfReal) aPars = new TColStd_HArray1OfReal(1, 2);
  
  if(dt < 0.) {
    aPnts->SetValue(1, gp_Pnt2d(XYP1));
    aPnts->SetValue(2, P0);
    aPars->SetValue(1, t + dt);
    aPars->SetValue(2, t);
  }
  else {
    aPnts->SetValue(2, gp_Pnt2d(XYP1));
    aPnts->SetValue(1, P0);
    aPars->SetValue(2, t + dt);
    aPars->SetValue(1, t);
  }
  
  Handle(Geom2d_BSplineCurve) aC;  
  
  if(dt < 0.) {
    aC = Interpolate(aPnts, aPars, V11, V01); 
  }
  else {
    aC = Interpolate(aPnts, aPars, V01, V11); 
  }
  
  
  Geom2dConvert_CompCurveToBSplineCurve aConcat(aRes);
  aConcat.Add(aC, Precision::PConfusion());
  
  aRes = aConcat.BSplineCurve();
  */
}  

//=======================================================================
//function : Project
//purpose  : 
//=======================================================================

static void Project(ProjLib_Projector& P, Handle(Adaptor3d_HCurve)& C)
{
  GeomAbs_CurveType CType = C->GetType();
  switch (CType) {
    case GeomAbs_Line:
      P.Project(C->Line());
      break;
    case GeomAbs_Circle:
      P.Project(C->Circle());
      break;
    case GeomAbs_Ellipse:
      P.Project(C->Ellipse());
      break;
    case GeomAbs_Hyperbola:
      P.Project(C->Hyperbola());
      break;
    case GeomAbs_Parabola:
      P.Project(C->Parabola());
      break;
    case GeomAbs_BSplineCurve:
    case GeomAbs_BezierCurve:
    case GeomAbs_OtherCurve:    // try the approximation
      break;
    default:
      Standard_NoSuchObject::Raise(" ");
  }
}

//=======================================================================
//function : ProjLib_ProjectedCurve
//purpose  : 
//=======================================================================

ProjLib_ProjectedCurve::ProjLib_ProjectedCurve()

{
  myTolerance = Precision::Confusion();
}


//=======================================================================
//function : ProjLib_ProjectedCurve
//purpose  : 
//=======================================================================

ProjLib_ProjectedCurve::ProjLib_ProjectedCurve
(const Handle(Adaptor3d_HSurface)& S)
{
  myTolerance = Precision::Confusion();
  Load(S);
}


//=======================================================================
//function : ProjLib_ProjectedCurve
//purpose  : 
//=======================================================================

ProjLib_ProjectedCurve::ProjLib_ProjectedCurve
(const Handle(Adaptor3d_HSurface)& S,
 const Handle(Adaptor3d_HCurve)& C)
{
  myTolerance = Precision::Confusion();
  Load(S);
  Load(C);
}


//=======================================================================
//function : ProjLib_ProjectedCurve
//purpose  : 
//=======================================================================

ProjLib_ProjectedCurve::ProjLib_ProjectedCurve
(const Handle(Adaptor3d_HSurface)& S,
 const Handle(Adaptor3d_HCurve)&   C,
 const Standard_Real             Tol)
{
  myTolerance = Max(Tol, Precision::Confusion());
  Load(S);
  Load(C);
}


//=======================================================================
//function : Load
//purpose  : 
//=======================================================================

void ProjLib_ProjectedCurve::Load(const Handle(Adaptor3d_HSurface)& S)
{
  mySurface = S ;
}


//=======================================================================
//function : Load
//purpose  : 
//=======================================================================

void ProjLib_ProjectedCurve::Load(const Handle(Adaptor3d_HCurve)& C)
{
  myTolerance = Max(myTolerance, Precision::Confusion());
  myCurve = C;
  Standard_Real FirstPar = C->FirstParameter();
  Standard_Real LastPar  = C->LastParameter();
  GeomAbs_SurfaceType SType = mySurface->GetType();    
  GeomAbs_CurveType   CType = myCurve->GetType();

  switch (SType) {

    case GeomAbs_Plane:
      {
	ProjLib_Plane P(mySurface->Plane());
	Project(P,myCurve);
	myResult = P;
      }
      break;

    case GeomAbs_Cylinder:
      {
	ProjLib_Cylinder P(mySurface->Cylinder());
	Project(P,myCurve);
	myResult = P;
      }
      break;

    case GeomAbs_Cone:
      {
	ProjLib_Cone P(mySurface->Cone());
	Project(P,myCurve);
	myResult = P;
      }
      break;

    case GeomAbs_Sphere:
      {
	ProjLib_Sphere P(mySurface->Sphere());
	Project(P,myCurve);
	if ( P.IsDone()) { 
	  // on met dans la pseudo-periode ( car Sphere n'est pas
	  // periodique en V !)
	  P.SetInBounds(myCurve->FirstParameter());
	}
	myResult = P;
      }
      break;

    case GeomAbs_Torus:
      {
	ProjLib_Torus P(mySurface->Torus());
	Project(P,myCurve);
	myResult = P;
      }
      break;

    case GeomAbs_BezierSurface:
    case GeomAbs_BSplineSurface:
      {
	
	Standard_Boolean IsTrimmed[2] = {Standard_False, Standard_False};
        Standard_Integer SingularCase[2];
	Standard_Real f, l, dt;
	const Standard_Real eps = 0.01;
	f = myCurve->FirstParameter();
	l = myCurve->LastParameter();
	dt = (l-f)*eps;

	Standard_Real U1=0.,U2=0.,V1=0.,V2=0;
	const Adaptor3d_Surface& S = mySurface->Surface();
	U1 = S.FirstUParameter();
	U2 = S.LastUParameter();
	V1 = S.FirstVParameter();
	V2 = S.LastVParameter();

	if(IsoIsDeg(S, U1, GeomAbs_IsoU, 0., myTolerance) ) {
	  //Surface has pole at U = Umin
	  gp_Pnt Pole = mySurface->Value(U1, V1);
	  TrimC3d(myCurve, IsTrimmed, dt, Pole, SingularCase, 1);
	}

	if(IsoIsDeg(S, U2, GeomAbs_IsoU, 0., myTolerance) ) {
	  //Surface has pole at U = Umax
	  gp_Pnt Pole = mySurface->Value(U2, V1);
	  TrimC3d(myCurve, IsTrimmed, dt, Pole, SingularCase, 2);
	}
	  
	if(IsoIsDeg(S, V1, GeomAbs_IsoV, 0., myTolerance) ) {
	  //Surface has pole at V = Vmin
	  gp_Pnt Pole = mySurface->Value(U1, V1);
	  TrimC3d(myCurve, IsTrimmed, dt, Pole, SingularCase, 3);
	}

	if(IsoIsDeg(S, V2, GeomAbs_IsoV, 0., myTolerance) ) {
	  //Surface has pole at V = Vmax
	  gp_Pnt Pole = mySurface->Value(U1, V2);
	  TrimC3d(myCurve, IsTrimmed, dt, Pole, SingularCase, 4);
	}

	ProjLib_ComputeApproxOnPolarSurface polar(myCurve, 
						  mySurface,
						  myTolerance);

	Handle(Geom2d_BSplineCurve) aRes = polar.BSpline();

	if(IsTrimmed[0] || IsTrimmed[1]) {
	  if(IsTrimmed[0]) {
	    //Add segment before start of curve
	    f = myCurve->FirstParameter();
	    ExtendC2d(aRes, f, -dt, U1, U2, V1, V2, 0, SingularCase[0]);
	  }
	  if(IsTrimmed[1]) {
	    //Add segment after end of curve
	    l = myCurve->LastParameter();
	    ExtendC2d(aRes, l, dt, U1, U2, V1, V2, 1, SingularCase[1]);
	  }
          Handle(Geom2d_Curve) NewCurve2d;
          GeomLib::SameRange(Precision::PConfusion(), aRes,
                             aRes->FirstParameter(), aRes->LastParameter(),
                             FirstPar, LastPar,
                             NewCurve2d);
          aRes = Handle(Geom2d_BSplineCurve)::DownCast(NewCurve2d);
        }
	myResult.SetBSpline(aRes);
	myResult.Done();
	myResult.SetType(GeomAbs_BSplineCurve);
      }
      break;

    default:
      {
	Standard_Boolean IsTrimmed[2] = {Standard_False, Standard_False};
        Standard_Real Vsingular[2]; //for surfaces of revolution
	Standard_Real f, l, dt;
	const Standard_Real eps = 0.01;
	
	if(mySurface->GetType() == GeomAbs_SurfaceOfRevolution) {
	  //Check possible singularity

	  gp_Pnt P = mySurface->AxeOfRevolution().Location();
	  gp_Dir N = mySurface->AxeOfRevolution().Direction();

	  gp_Lin L(P, N);

	  f = myCurve->FirstParameter();
	  l = myCurve->LastParameter();
	  dt = (l-f)*eps;

	  P = myCurve->Value(f);
	  if(L.Distance(P) < Precision::Confusion()) {
	    IsTrimmed[0] = Standard_True;
	    f = f+dt;
	    myCurve = myCurve->Trim(f, l, Precision::Confusion());
            Vsingular[0] = ElCLib::Parameter(L, P);
            //SingularCase[0] = 3;
	  }

	  P = myCurve->Value(l);
	  if(L.Distance(P) < Precision::Confusion()) {
	    IsTrimmed[1] = Standard_True;
	    l = l-dt;
	    myCurve = myCurve->Trim(f, l, Precision::Confusion());
            Vsingular[1] = ElCLib::Parameter(L, P);
            //SingularCase[1] = 3;
	  }
	}

     	ProjLib_CompProjectedCurve Projector(mySurface,myCurve,
					     myTolerance,myTolerance);
	Handle(ProjLib_HCompProjectedCurve) HProjector = 
	  new ProjLib_HCompProjectedCurve();
	HProjector->Set(Projector);

	// Normalement, dans le cadre de ProjLib, le resultat 
	// doit etre une et une seule courbe !!!
	// De plus, cette courbe ne doit pas etre Single point
	Standard_Integer NbCurves = Projector.NbCurves();
	Standard_Real Udeb = 0.0,Ufin = 0.0;
	if (NbCurves > 0) {
	  Projector.Bounds(1,Udeb,Ufin);
	}
	else {
	  StdFail_NotDone::Raise("ProjLib CompProjectedCurve Not Done");
	}
	// Approximons cette courbe algorithmique.
	Standard_Boolean Only3d = Standard_False;
	Standard_Boolean Only2d = Standard_True;
	GeomAbs_Shape Continuity = GeomAbs_C1;
	Standard_Integer MaxDegree = 14;
	Standard_Integer MaxSeg    = 16;

	Approx_CurveOnSurface appr(HProjector, mySurface, Udeb, Ufin, 
				   myTolerance, 
				   Continuity, MaxDegree, MaxSeg, 
				   Only3d, Only2d);

	Handle(Geom2d_BSplineCurve) aRes = appr.Curve2d();

	if(IsTrimmed[0] || IsTrimmed[1]) {
	  // Treatment only for surface of revolution
	  Standard_Real u1, u2, v2;
	  u1 = mySurface->FirstUParameter();
	  u2 = mySurface->LastUParameter();
	  v2 = mySurface->LastVParameter();
	  
	  if(IsTrimmed[0]) {
	    //Add segment before start of curve
	    ExtendC2d(aRes, f, -dt, u1, u2, Vsingular[0], v2, 0, 3);
	  }
	  if(IsTrimmed[1]) {
	    //Add segment after end of curve
	    ExtendC2d(aRes, l, dt, u1, u2, Vsingular[1], v2, 1, 3);
	  }
          Handle(Geom2d_Curve) NewCurve2d;
          GeomLib::SameRange(Precision::PConfusion(), aRes,
                             aRes->FirstParameter(), aRes->LastParameter(),
                             FirstPar, LastPar,
                             NewCurve2d);
          aRes = Handle(Geom2d_BSplineCurve)::DownCast(NewCurve2d);
	}
	  
	myResult.SetBSpline(aRes);
	myResult.Done();
	myResult.SetType(GeomAbs_BSplineCurve);
      }
  }
  if ( !myResult.IsDone()) {
    ProjLib_ComputeApprox Comp( myCurve, mySurface, myTolerance);
    myResult.Done();
    
    // set the type
    if ( SType == GeomAbs_Plane  &&  CType == GeomAbs_BezierCurve) {
      myResult.SetType(GeomAbs_BezierCurve);
      myResult.SetBezier(Comp.Bezier()) ;
    }
    else {
      myResult.SetType(GeomAbs_BSplineCurve);
      myResult.SetBSpline(Comp.BSpline()) ;
    }
    // set the periodicity flag
    if ( SType == GeomAbs_Plane               && 
	 CType == GeomAbs_BSplineCurve        &&
	 myCurve->IsPeriodic()   ) {
      myResult.SetPeriodic();
    }
    myTolerance = Comp.Tolerance();
  }

  else {
    // On remet arbitrairement la tol atteinte a une valeur
    // petite en attendant mieux. dub lbo 11/03/97
    myTolerance = Min(myTolerance,Precision::Confusion());
    
    // Translate the projected curve to keep the first point
    // In the canonical boundaries of periodic surfaces.
    if (mySurface->IsUPeriodic()) {
      // xf
      Standard_Real aT1, aT2, aU1, aU2, aUPeriod, aUr, aUm, aUmid, dUm, dUr;
      GeomAbs_CurveType aTypeR;
      ProjLib_Projector aResult;
      //
      aT1=myCurve->FirstParameter();
      aT2=myCurve->LastParameter();
      aU1=mySurface->FirstUParameter();
      aU2=mySurface->LastUParameter();
      aUPeriod=mySurface->UPeriod();
      //
      aTypeR=myResult.GetType();
      if ((aU2-aU1)<(aUPeriod-myTolerance) && aTypeR == GeomAbs_Line) {
	aResult=myResult;
	aResult.UFrame(aT1, aT2, aU1, aUPeriod);
	//
	gp_Lin2d &aLr = (gp_Lin2d &) aResult.Line();
	aUr=aLr.Location().X();
	gp_Lin2d &aLm = (gp_Lin2d &) myResult.Line();
	aUm=aLm.Location().X();
	//
	aUmid=0.5*(aU2+aU1);
	dUm=fabs(aUm-aUmid);
	dUr=fabs(aUr-aUmid);
	if (dUr<dUm) {
	  myResult=aResult;
	}
      }
      else {
	myResult.UFrame(aT1, aT2, aU1, aUPeriod);
      }
      //
      /*
      myResult.UFrame(myCurve->FirstParameter(),
		      myCurve->LastParameter(),
		      mySurface->FirstUParameter(),
		      mySurface->UPeriod());
      */
      //xt
      //  Modified by skv - Wed Aug 11 15:45:58 2004 OCC6272 Begin
      //  Correct the U isoline in periodical surface
      // to be inside restriction boundaries.
      if (myResult.GetType() == GeomAbs_Line) {
	gp_Lin2d &aLine = (gp_Lin2d &) myResult.Line();

	Standard_Real aPeriod = mySurface->UPeriod();
	Standard_Real aFUPar  = mySurface->FirstUParameter();
	Standard_Real aLUPar  = mySurface->LastUParameter();

	// Check if the parametric range is lower then the period.
	if (aLUPar - aFUPar < aPeriod - myTolerance) {
	  Standard_Real aU = aLine.Location().X();

	  if (Abs(aU + aPeriod - aFUPar) < myTolerance ||
	      Abs(aU - aPeriod - aFUPar) < myTolerance) {
	    gp_Pnt2d aNewLoc(aFUPar, aLine.Location().Y());

	    aLine.SetLocation(aNewLoc);
	  } else if (Abs(aU + aPeriod - aLUPar) < myTolerance ||
		     Abs(aU - aPeriod - aLUPar) < myTolerance) {
	    gp_Pnt2d aNewLoc(aLUPar, aLine.Location().Y());

	    aLine.SetLocation(aNewLoc);
	  }
	}
      }
    }
//  Modified by skv - Wed Aug 11 15:45:58 2004 OCC6272 End

    if (mySurface->IsVPeriodic()) {
      myResult.VFrame(myCurve->FirstParameter(),
			 myCurve->LastParameter(),
			 mySurface->FirstVParameter(),
			 mySurface->VPeriod());
//  Modified by skv - Wed Aug 11 15:45:58 2004 OCC6272 Begin
//  Correct the V isoline in a periodical surface
// to be inside restriction boundaries.
      if (myResult.GetType() == GeomAbs_Line) {
	gp_Lin2d &aLine = (gp_Lin2d &) myResult.Line();

	Standard_Real aPeriod = mySurface->VPeriod();
	Standard_Real aFVPar  = mySurface->FirstVParameter();
	Standard_Real aLVPar  = mySurface->LastVParameter();

	// Check if the parametric range is lower then the period.
	if (aLVPar - aFVPar < aPeriod - myTolerance) {
	  Standard_Real aV = aLine.Location().Y();

	  if (Abs(aV + aPeriod - aFVPar) < myTolerance ||
	      Abs(aV - aPeriod - aFVPar) < myTolerance) {
	    gp_Pnt2d aNewLoc(aLine.Location().X(), aFVPar);

	    aLine.SetLocation(aNewLoc);
	  } else if (Abs(aV + aPeriod - aLVPar) < myTolerance ||
		     Abs(aV - aPeriod - aLVPar) < myTolerance) {
	    gp_Pnt2d aNewLoc(aLine.Location().X(), aLVPar);

	    aLine.SetLocation(aNewLoc);
	  }
	}
      }
    }
//  Modified by skv - Wed Aug 11 15:45:58 2004 OCC6272 End
  } 
}


//=======================================================================
//function : GetSurface
//purpose  : 
//=======================================================================

const Handle(Adaptor3d_HSurface)& ProjLib_ProjectedCurve::GetSurface() const
{
  return mySurface;
}


//=======================================================================
//function : GetCurve
//purpose  : 
//=======================================================================

const Handle(Adaptor3d_HCurve)& ProjLib_ProjectedCurve::GetCurve() const
{
  return myCurve;
}


//=======================================================================
//function : GetTolerance
//purpose  : 
//=======================================================================

Standard_Real ProjLib_ProjectedCurve::GetTolerance() const 
{
  return myTolerance;
}


//=======================================================================
//function : FirstParameter
//purpose  : 
//=======================================================================

Standard_Real ProjLib_ProjectedCurve::FirstParameter() const 
{
  return myCurve->FirstParameter();
}


//=======================================================================
//function : LastParameter
//purpose  : 
//=======================================================================

Standard_Real ProjLib_ProjectedCurve::LastParameter() const 
{
  return myCurve->LastParameter();
}


//=======================================================================
//function : Continuity
//purpose  : 
//=======================================================================

GeomAbs_Shape ProjLib_ProjectedCurve::Continuity() const
{
  Standard_NotImplemented::Raise("");
  return GeomAbs_C0;
}


//=======================================================================
//function : NbIntervals
//purpose  : 
//=======================================================================

Standard_Integer ProjLib_ProjectedCurve::NbIntervals(const GeomAbs_Shape ) const 
{
  Standard_NotImplemented::Raise("");
  return 0;
}


//=======================================================================
//function : Intervals
//purpose  : 
//=======================================================================

//void ProjLib_ProjectedCurve::Intervals(TColStd_Array1OfReal&  T,
void ProjLib_ProjectedCurve::Intervals(TColStd_Array1OfReal&  ,
				       const GeomAbs_Shape ) const 
{
  Standard_NotImplemented::Raise("");
}


//=======================================================================
//function : IsClosed
//purpose  : 
//=======================================================================

Standard_Boolean ProjLib_ProjectedCurve::IsClosed() const
{
  Standard_NotImplemented::Raise("");
  return Standard_True;
}


//=======================================================================
//function : IsPeriodic
//purpose  : 
//=======================================================================

Standard_Boolean ProjLib_ProjectedCurve::IsPeriodic() const
{
  return myResult.IsPeriodic();
}


//=======================================================================
//function : Period
//purpose  : 
//=======================================================================

Standard_Real ProjLib_ProjectedCurve::Period() const
{
  Standard_NotImplemented::Raise("");
  return 0.;
}


//=======================================================================
//function : Value
//purpose  : 
//=======================================================================

gp_Pnt2d ProjLib_ProjectedCurve::Value(const Standard_Real ) const 
{
  Standard_NotImplemented::Raise("");
  return gp_Pnt2d(0.,0.);
}


//=======================================================================
//function : D0
//purpose  : 
//=======================================================================

void ProjLib_ProjectedCurve::D0(const Standard_Real , gp_Pnt2d& ) const
{
  Standard_NotImplemented::Raise("");
}


//=======================================================================
//function : D1
//purpose  : 
//=======================================================================

void ProjLib_ProjectedCurve::D1(const Standard_Real ,
			              gp_Pnt2d&     , 
                                      gp_Vec2d&     ) const 
{
  Standard_NotImplemented::Raise("");
}


//=======================================================================
//function : D2
//purpose  : 
//=======================================================================

void ProjLib_ProjectedCurve::D2(const Standard_Real , 
			              gp_Pnt2d&     , 
                                      gp_Vec2d&     , 
                                      gp_Vec2d&     ) const 
{
  Standard_NotImplemented::Raise("");
}


//=======================================================================
//function : D3
//purpose  : 
//=======================================================================

void ProjLib_ProjectedCurve::D3(const Standard_Real, 
				      gp_Pnt2d&, 
			              gp_Vec2d&, 
				      gp_Vec2d&, 
			              gp_Vec2d&) const 
{
  Standard_NotImplemented::Raise("");
}


//=======================================================================
//function : DN
//purpose  : 
//=======================================================================

gp_Vec2d ProjLib_ProjectedCurve::DN(const Standard_Real, 
				    const Standard_Integer) const 
{
  Standard_NotImplemented::Raise("");
  return gp_Vec2d(0.,0.);
}


//=======================================================================
//function : Resolution
//purpose  : 
//=======================================================================

Standard_Real ProjLib_ProjectedCurve::Resolution(const Standard_Real) const 
{
  Standard_NotImplemented::Raise("");
  return 0.;
}
    

//=======================================================================
//function : GetType
//purpose  : 
//=======================================================================

GeomAbs_CurveType ProjLib_ProjectedCurve::GetType() const
{
  return myResult.GetType();
}


//=======================================================================
//function : Line
//purpose  : 
//=======================================================================

gp_Lin2d ProjLib_ProjectedCurve::Line() const
{
  return myResult.Line();
}


//=======================================================================
//function : Circle
//purpose  : 
//=======================================================================

gp_Circ2d ProjLib_ProjectedCurve::Circle() const
{
  return myResult.Circle();
}


//=======================================================================
//function : Ellipse
//purpose  : 
//=======================================================================

gp_Elips2d ProjLib_ProjectedCurve::Ellipse() const
{
  return myResult.Ellipse();
}


//=======================================================================
//function : Hyperbola
//purpose  : 
//=======================================================================

gp_Hypr2d ProjLib_ProjectedCurve::Hyperbola() const
{
  return myResult.Hyperbola();
}


//=======================================================================
//function : Parabola
//purpose  : 
//=======================================================================

gp_Parab2d ProjLib_ProjectedCurve::Parabola() const
{
  return myResult.Parabola();
}



//=======================================================================
//function : Degree
//purpose  : 
//=======================================================================

Standard_Integer ProjLib_ProjectedCurve::Degree() const
{
  Standard_NoSuchObject_Raise_if 
    ( (GetType() != GeomAbs_BSplineCurve) &&
      (GetType() != GeomAbs_BezierCurve),
     "ProjLib_ProjectedCurve:Degree");
  if (GetType() == GeomAbs_BSplineCurve) {
    return myResult.BSpline()->Degree();
  }
  else if (GetType() == GeomAbs_BezierCurve) {
    return myResult.Bezier()->Degree();
  }

  // portage WNT
  return 0;
}

//=======================================================================
//function : IsRational
//purpose  : 
//=======================================================================

Standard_Boolean ProjLib_ProjectedCurve::IsRational() const 
{
  Standard_NoSuchObject_Raise_if 
    ( (GetType() != GeomAbs_BSplineCurve) &&
      (GetType() != GeomAbs_BezierCurve),
     "ProjLib_ProjectedCurve:IsRational");
  if (GetType() == GeomAbs_BSplineCurve) {
    return myResult.BSpline()->IsRational();
  }
  else if (GetType() == GeomAbs_BezierCurve) {
    return myResult.Bezier()->IsRational();
  }
  // portage WNT
  return Standard_False;
}

//=======================================================================
//function : NbPoles
//purpose  : 
//=======================================================================

Standard_Integer ProjLib_ProjectedCurve::NbPoles() const
{
  Standard_NoSuchObject_Raise_if 
    ( (GetType() != GeomAbs_BSplineCurve) &&
      (GetType() != GeomAbs_BezierCurve)   
     ,"ProjLib_ProjectedCurve:NbPoles"  );
  if (GetType() == GeomAbs_BSplineCurve) {
    return myResult.BSpline()->NbPoles();
  }
  else if (GetType() == GeomAbs_BezierCurve) {
    return myResult.Bezier()->NbPoles();
  }

  // portage WNT
  return 0;
}

//=======================================================================
//function : NbKnots
//purpose  : 
//=======================================================================

Standard_Integer ProjLib_ProjectedCurve::NbKnots() const 
{
  Standard_NoSuchObject_Raise_if ( GetType() != GeomAbs_BSplineCurve, 
				  "ProjLib_ProjectedCurve:NbKnots");
  return myResult.BSpline()->NbKnots();
}

//=======================================================================
//function : Bezier
//purpose  : 
//=======================================================================

Handle(Geom2d_BezierCurve) ProjLib_ProjectedCurve::Bezier() const 
{
 return myResult.Bezier() ;
}

//=======================================================================
//function : BSpline
//purpose  : 
//=======================================================================

Handle(Geom2d_BSplineCurve) ProjLib_ProjectedCurve::BSpline() const 
{
 return myResult.BSpline() ;
}
//=======================================================================
//function : Trim
//purpose  : 
//=======================================================================

Handle(Adaptor2d_HCurve2d) ProjLib_ProjectedCurve::Trim 
//(const Standard_Real First,
// const Standard_Real Last,
// const Standard_Real Tolerance) const 
(const Standard_Real ,
 const Standard_Real ,
 const Standard_Real ) const 
{
  Standard_NotImplemented::Raise("");
  return NULL ;
}

