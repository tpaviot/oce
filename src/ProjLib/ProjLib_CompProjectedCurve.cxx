// Created on: 1997-09-23
// Created by: Roman BORISOV
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



#include <ProjLib_CompProjectedCurve.ixx>
#include <ProjLib_HCompProjectedCurve.hxx>
#include <gp_XY.hxx>
#include <gp_Mat2d.hxx>
#include <Extrema_ExtPS.hxx>
#include <Precision.hxx>
#include <Extrema_ExtCS.hxx>
#include <TColgp_HSequenceOfPnt.hxx>
#include <Extrema_GenLocateExtPS.hxx>
#include <Extrema_POnSurf.hxx>
#include <Extrema_POnCurv.hxx>
#include <ProjLib_PrjResolve.hxx>
#include <GeomAbs_CurveType.hxx>
#include <GeomLib.hxx>

#define FuncTol 1.e-10

#ifdef __OCC_DEBUG_CHRONO
#include <OSD_Timer.hxx>

static OSD_Chronometer chr_init_point, chr_dicho_bound;

Standard_EXPORT Standard_Real t_init_point, t_dicho_bound;
Standard_EXPORT Standard_Integer init_point_count, dicho_bound_count;

static void InitChron(OSD_Chronometer& ch)
{ 
    ch.Reset();
    ch.Start();
}

static void ResultChron( OSD_Chronometer & ch, Standard_Real & time) 
{
    Standard_Real tch ;
    ch.Stop();
    ch.Show(tch);
    time=time +tch;
}
#endif


//=======================================================================
//function : d1
//purpose  : computes first derivative of the projected curve
//=======================================================================

static void d1(const Standard_Real t,
               const Standard_Real u,
               const Standard_Real v,
               gp_Vec2d& V, 
               const Handle(Adaptor3d_HCurve)& Curve, 
               const Handle(Adaptor3d_HSurface)& Surface)
{
  gp_Pnt S, C;
  gp_Vec DS1_u, DS1_v, DS2_u, DS2_uv, DS2_v, DC1_t;
  Surface->D2(u, v, S, DS1_u, DS1_v, DS2_u, DS2_v, DS2_uv);
  Curve->D1(t, C, DC1_t);
  gp_Vec Ort(C, S);// Ort = S - C

  gp_Vec2d dE_dt(-DC1_t*DS1_u, -DC1_t*DS1_v);
  gp_XY dE_du(DS1_u*DS1_u + Ort*DS2_u, 
	      DS1_u*DS1_v + Ort*DS2_uv);
  gp_XY dE_dv(DS1_v*DS1_u + Ort*DS2_uv, 
	      DS1_v*DS1_v + Ort*DS2_v);

  Standard_Real det = dE_du.X()*dE_dv.Y() - dE_du.Y()*dE_dv.X();
  if (fabs(det) < gp::Resolution()) Standard_ConstructionError::Raise();
 
  gp_Mat2d M(gp_XY(dE_dv.Y()/det, -dE_du.Y()/det), 
	     gp_XY(-dE_dv.X()/det, dE_du.X()/det));

  V = - gp_Vec2d(gp_Vec2d(M.Row(1))*dE_dt, gp_Vec2d(M.Row(2))*dE_dt);
}

//=======================================================================
//function : d2
//purpose  : computes second derivative of the projected curve
//=======================================================================

 static void d2(const Standard_Real t,
                const Standard_Real u,
                const Standard_Real v,
                gp_Vec2d& V1, gp_Vec2d& V2,
                const Handle(Adaptor3d_HCurve)& Curve, 
                const Handle(Adaptor3d_HSurface)& Surface)
{
  gp_Pnt S, C;
  gp_Vec DS1_u, DS1_v, DS2_u, DS2_uv, DS2_v, 
         DS3_u, DS3_v, DS3_uuv, DS3_uvv, 
         DC1_t, DC2_t;
  Surface->D3(u, v, S, DS1_u, DS1_v, DS2_u, DS2_v, DS2_uv, 
		DS3_u, DS3_v, DS3_uuv, DS3_uvv);
  Curve->D2(t, C, DC1_t, DC2_t);
  gp_Vec Ort(C, S);

  gp_Vec2d dE_dt(-DC1_t*DS1_u, -DC1_t*DS1_v);
  gp_XY dE_du(DS1_u*DS1_u + Ort*DS2_u, 
	      DS1_u*DS1_v + Ort*DS2_uv);
  gp_XY dE_dv(DS1_v*DS1_u + Ort*DS2_uv, 
	      DS1_v*DS1_v + Ort*DS2_v);

  Standard_Real det = dE_du.X()*dE_dv.Y() - dE_du.Y()*dE_dv.X();
  if (fabs(det) < gp::Resolution()) Standard_ConstructionError::Raise();

  gp_Mat2d M(gp_XY(dE_dv.Y()/det, -dE_du.Y()/det), 
	     gp_XY(-dE_dv.X()/det, dE_du.X()/det));

  // First derivative
  V1 = - gp_Vec2d(gp_Vec2d(M.Row(1))*dE_dt, gp_Vec2d(M.Row(2))*dE_dt);

  /* Second derivative */

  // Computation of d2E_dt2 = S1
  gp_Vec2d d2E_dt(-DC2_t*DS1_u, -DC2_t*DS1_v);

  // Computation of 2*(d2E/dtdX)(dX/dt) = S2
  gp_Vec2d d2E1_dtdX(-DC1_t*DS2_u,
		     -DC1_t*DS2_uv);
  gp_Vec2d d2E2_dtdX(-DC1_t*DS2_uv,
		     -DC1_t*DS2_v);
  gp_Vec2d S2 = 2*gp_Vec2d(d2E1_dtdX*V1, d2E2_dtdX*V1);

  // Computation of (d2E/dX2)*(dX/dt)2 = S3

  // Row11 = (d2E1/du2, d2E1/dudv)
  Standard_Real tmp;
  gp_Vec2d Row11(3*DS1_u*DS2_u + Ort*DS3_u,
	     tmp = 2*DS1_u*DS2_uv + 
	     DS1_v*DS2_u + Ort*DS3_uuv);  

  // Row12 = (d2E1/dudv, d2E1/dv2)
  gp_Vec2d Row12(tmp, DS2_v*DS1_u + 2*DS1_v*DS2_uv + 
	     Ort*DS3_uvv);

  // Row21 = (d2E2/du2, d2E2/dudv)
  gp_Vec2d Row21(DS2_u*DS1_v + 2*DS1_u*DS2_uv + Ort*DS3_uuv, 
	      tmp = 2*DS2_uv*DS1_v + DS1_u*DS2_v + Ort*DS3_uvv);

  // Row22 = (d2E2/duv, d2E2/dvdv)
  gp_Vec2d Row22(tmp, 3*DS1_v*DS2_v + Ort*DS3_v);

  gp_Vec2d S3(V1*gp_Vec2d(Row11*V1, Row12*V1),
	      V1*gp_Vec2d(Row21*V1, Row22*V1));

  gp_Vec2d Sum = d2E_dt + S2 + S3;

  V2 = - gp_Vec2d(gp_Vec2d(M.Row(1))*Sum, gp_Vec2d(M.Row(2))*Sum);
}
//=======================================================================
//function : d1CurveOnSurf
//purpose  : computes first derivative of the 3d projected curve
//=======================================================================

#if 0
static void d1CurvOnSurf(const Standard_Real t,
                         const Standard_Real u,
                         const Standard_Real v,
                         gp_Vec& V, 
                         const Handle(Adaptor3d_HCurve)& Curve, 
                         const Handle(Adaptor3d_HSurface)& Surface)
{
  gp_Pnt S, C;
  gp_Vec2d V2d;
  gp_Vec DS1_u, DS1_v, DS2_u, DS2_uv, DS2_v, DC1_t;
  Surface->D2(u, v, S, DS1_u, DS1_v, DS2_u, DS2_v, DS2_uv);
  Curve->D1(t, C, DC1_t);
  gp_Vec Ort(C, S);// Ort = S - C

  gp_Vec2d dE_dt(-DC1_t*DS1_u, -DC1_t*DS1_v);
  gp_XY dE_du(DS1_u*DS1_u + Ort*DS2_u, 
	      DS1_u*DS1_v + Ort*DS2_uv);
  gp_XY dE_dv(DS1_v*DS1_u + Ort*DS2_uv, 
	      DS1_v*DS1_v + Ort*DS2_v);

  Standard_Real det = dE_du.X()*dE_dv.Y() - dE_du.Y()*dE_dv.X();
  if (fabs(det) < gp::Resolution()) Standard_ConstructionError::Raise();
 
  gp_Mat2d M(gp_XY(dE_dv.Y()/det, -dE_du.Y()/det), 
	     gp_XY(-dE_dv.X()/det, dE_du.X()/det));

  V2d = - gp_Vec2d(gp_Vec2d(M.Row(1))*dE_dt, gp_Vec2d(M.Row(2))*dE_dt);

  V = DS1_u * V2d.X() + DS1_v * V2d.Y();

}
#endif

//=======================================================================
//function : d2CurveOnSurf
//purpose  : computes second derivative of the 3D projected curve
//=======================================================================

 static void d2CurvOnSurf(const Standard_Real t,
                           const Standard_Real u,
                           const Standard_Real v,
                           gp_Vec& V1 , gp_Vec& V2 ,
                           const Handle(Adaptor3d_HCurve)& Curve, 
                           const Handle(Adaptor3d_HSurface)& Surface)
{
  gp_Pnt S, C;
  gp_Vec2d V12d,V22d;
  gp_Vec DS1_u, DS1_v, DS2_u, DS2_uv, DS2_v, 
         DS3_u, DS3_v, DS3_uuv, DS3_uvv, 
         DC1_t, DC2_t;
  Surface->D3(u, v, S, DS1_u, DS1_v, DS2_u, DS2_v, DS2_uv, 
		DS3_u, DS3_v, DS3_uuv, DS3_uvv);
  Curve->D2(t, C, DC1_t, DC2_t);
  gp_Vec Ort(C, S);

  gp_Vec2d dE_dt(-DC1_t*DS1_u, -DC1_t*DS1_v);
  gp_XY dE_du(DS1_u*DS1_u + Ort*DS2_u, 
	      DS1_u*DS1_v + Ort*DS2_uv);
  gp_XY dE_dv(DS1_v*DS1_u + Ort*DS2_uv, 
	      DS1_v*DS1_v + Ort*DS2_v);

  Standard_Real det = dE_du.X()*dE_dv.Y() - dE_du.Y()*dE_dv.X();
  if (fabs(det) < gp::Resolution()) Standard_ConstructionError::Raise();

  gp_Mat2d M(gp_XY(dE_dv.Y()/det, -dE_du.Y()/det), 
	     gp_XY(-dE_dv.X()/det, dE_du.X()/det));

  // First derivative
  V12d = - gp_Vec2d(gp_Vec2d(M.Row(1))*dE_dt, gp_Vec2d(M.Row(2))*dE_dt);

  /* Second derivative */

  // Computation of d2E_dt2 = S1
  gp_Vec2d d2E_dt(-DC2_t*DS1_u, -DC2_t*DS1_v);

  // Computation of 2*(d2E/dtdX)(dX/dt) = S2
  gp_Vec2d d2E1_dtdX(-DC1_t*DS2_u,
		     -DC1_t*DS2_uv);
  gp_Vec2d d2E2_dtdX(-DC1_t*DS2_uv,
		     -DC1_t*DS2_v);
  gp_Vec2d S2 = 2*gp_Vec2d(d2E1_dtdX*V12d, d2E2_dtdX*V12d);

  // Computation of (d2E/dX2)*(dX/dt)2 = S3

  // Row11 = (d2E1/du2, d2E1/dudv)
  Standard_Real tmp;
  gp_Vec2d Row11(3*DS1_u*DS2_u + Ort*DS3_u,
	     tmp = 2*DS1_u*DS2_uv + 
	     DS1_v*DS2_u + Ort*DS3_uuv);  

  // Row12 = (d2E1/dudv, d2E1/dv2)
  gp_Vec2d Row12(tmp, DS2_v*DS1_u + 2*DS1_v*DS2_uv + 
	     Ort*DS3_uvv);

  // Row21 = (d2E2/du2, d2E2/dudv)
  gp_Vec2d Row21(DS2_u*DS1_v + 2*DS1_u*DS2_uv + Ort*DS3_uuv, 
	      tmp = 2*DS2_uv*DS1_v + DS1_u*DS2_v + Ort*DS3_uvv);

  // Row22 = (d2E2/duv, d2E2/dvdv)
  gp_Vec2d Row22(tmp, 3*DS1_v*DS2_v + Ort*DS3_v);

  gp_Vec2d S3(V12d*gp_Vec2d(Row11*V12d, Row12*V12d),
	      V12d*gp_Vec2d(Row21*V12d, Row22*V12d));

  gp_Vec2d Sum = d2E_dt + S2 + S3;

  V22d = - gp_Vec2d(gp_Vec2d(M.Row(1))*Sum, gp_Vec2d(M.Row(2))*Sum);

  V1 = DS1_u * V12d.X() + DS1_v * V12d.Y();
  V2 =     DS2_u * V12d.X() *V12d.X()  
     +     DS1_u * V22d.X() 
     + 2 * DS2_uv * V12d.X() *V12d.Y()
     +     DS2_v * V12d.Y() * V12d.Y()
     +     DS1_v * V22d.Y();
}

//=======================================================================
//function : ExactBound
//purpose  : computes exact boundary point
//=======================================================================

static Standard_Boolean ExactBound(gp_Pnt& Sol, 
                                   const Standard_Real NotSol, 
                                   const Standard_Real Tol, 
                                   const Standard_Real TolU, 
                                   const Standard_Real TolV,  
                                   const Handle(Adaptor3d_HCurve)& Curve, 
                                   const Handle(Adaptor3d_HSurface)& Surface)
{
  Standard_Real U0, V0, t, t1, t2, FirstU, LastU, FirstV, LastV;
  gp_Pnt2d POnS;
  U0 = Sol.Y();
  V0 = Sol.Z();
  FirstU = Surface->FirstUParameter();
  LastU = Surface->LastUParameter();
  FirstV = Surface->FirstVParameter();
  LastV = Surface->LastVParameter();
  // Here we have to compute the boundary that projection is going to intersect
  gp_Vec2d D2d;
  //these variables are to estimate which boundary has more apportunity 
  //to be intersected
  Standard_Real RU1, RU2, RV1, RV2; 
  d1(Sol.X(), U0, V0, D2d, Curve, Surface);
  // Here we assume that D2d != (0, 0)
  if(Abs(D2d.X()) < gp::Resolution()) 
  {
    RU1 = Precision::Infinite();
    RU2 = Precision::Infinite();
    RV1 = V0 - FirstV;
    RV2 = LastV - V0;
  }
  else if(Abs(D2d.Y()) < gp::Resolution()) 
  {
    RU1 = U0 - FirstU;
    RU2 = LastU - U0;
    RV1 = Precision::Infinite();
    RV2 = Precision::Infinite();    
  }
  else 
  {
    RU1 = gp_Pnt2d(U0, V0).
          Distance(gp_Pnt2d(FirstU, V0 + (FirstU - U0)*D2d.Y()/D2d.X()));
    RU2 = gp_Pnt2d(U0, V0).
          Distance(gp_Pnt2d(LastU, V0 + (LastU - U0)*D2d.Y()/D2d.X()));
    RV1 = gp_Pnt2d(U0, V0).
          Distance(gp_Pnt2d(U0 + (FirstV - V0)*D2d.X()/D2d.Y(), FirstV));
    RV2 = gp_Pnt2d(U0, V0).
          Distance(gp_Pnt2d(U0 + (LastV - V0)*D2d.X()/D2d.Y(), LastV));
  }
  TColgp_SequenceOfPnt Seq;
  Seq.Append(gp_Pnt(FirstU, RU1, 2));
  Seq.Append(gp_Pnt(LastU, RU2, 2));
  Seq.Append(gp_Pnt(FirstV, RV1, 3));
  Seq.Append(gp_Pnt(LastV, RV2, 3));
  Standard_Integer i, j;
  for(i = 1; i <= 3; i++)
    for(j = 1; j <= 4-i; j++)
      if(Seq(j).Y() < Seq(j+1).Y()) 
      {
	gp_Pnt swp;
	swp = Seq.Value(j+1);
	Seq.ChangeValue(j+1) = Seq.Value(j);
	Seq.ChangeValue(j) = swp;
      }

  t = Sol.X();
  t1 = Min(Sol.X(), NotSol);
  t2 = Max(Sol.X(), NotSol);

  Standard_Boolean isDone = Standard_False;
  while (!Seq.IsEmpty()) 
  {
    gp_Pnt P;
    P = Seq.Last();
    Seq.Remove(Seq.Length());
    ProjLib_PrjResolve aPrjPS(Curve->Curve(), 
                              Surface->Surface(), 
                              Standard_Integer(P.Z()));
    if(Standard_Integer(P.Z()) == 2) 
    {
      aPrjPS.Perform(t, P.X(), V0, gp_Pnt2d(Tol, TolV), 
                     gp_Pnt2d(t1, Surface->FirstVParameter()), 
                     gp_Pnt2d(t2, Surface->LastVParameter()), FuncTol);
      if(!aPrjPS.IsDone()) continue;
      POnS = aPrjPS.Solution();
      Sol = gp_Pnt(POnS.X(), P.X(), POnS.Y());
      isDone = Standard_True;
      break;
    }
    else 
    {
      aPrjPS.Perform(t, U0, P.X(), gp_Pnt2d(Tol, TolU), 
                     gp_Pnt2d(t1, Surface->FirstUParameter()), 
                     gp_Pnt2d(t2, Surface->LastUParameter()), FuncTol);
      if(!aPrjPS.IsDone()) continue;
      POnS = aPrjPS.Solution();
      Sol = gp_Pnt(POnS.X(), POnS.Y(), P.X());
      isDone = Standard_True;
      break;
    }
  }

  return isDone;
}

//=======================================================================
//function : DichExactBound
//purpose  : computes exact boundary point
//=======================================================================

static void DichExactBound(gp_Pnt& Sol, 
                           const Standard_Real NotSol, 
                           const Standard_Real Tol, 
                           const Standard_Real TolU, 
                           const Standard_Real TolV,  
                           const Handle(Adaptor3d_HCurve)& Curve, 
                           const Handle(Adaptor3d_HSurface)& Surface)
{
#ifdef __OCC_DEBUG_CHRONO
  InitChron(chr_dicho_bound);
#endif

  Standard_Real U0, V0, t;
  gp_Pnt2d POnS;
  U0 = Sol.Y();
  V0 = Sol.Z();
  ProjLib_PrjResolve aPrjPS(Curve->Curve(), Surface->Surface(), 1);

  Standard_Real aNotSol = NotSol;
  while (fabs(Sol.X() - aNotSol) > Tol) 
  {
    t = (Sol.X() + aNotSol)/2;
    aPrjPS.Perform(t, U0, V0, gp_Pnt2d(TolU, TolV), 
              gp_Pnt2d(Surface->FirstUParameter(),Surface->FirstVParameter()), 
              gp_Pnt2d(Surface->LastUParameter(),Surface->LastVParameter()), 
              FuncTol, Standard_True);

    if (aPrjPS.IsDone()) 
    {
      POnS = aPrjPS.Solution();
      Sol = gp_Pnt(t, POnS.X(), POnS.Y());
      U0=Sol.Y();
      V0=Sol.Z();
    }
    else aNotSol = t; 
  }
#ifdef __OCC_DEBUG_CHRONO
      ResultChron(chr_dicho_bound,t_dicho_bound);
      dicho_bound_count++;
#endif
}

//=======================================================================
//function : InitialPoint
//purpose  : 
//=======================================================================

static Standard_Boolean InitialPoint(const gp_Pnt& Point, 
                                     const Standard_Real t,
                                     const Handle(Adaptor3d_HCurve)& C,
                                     const Handle(Adaptor3d_HSurface)& S, 
                                     const Standard_Real TolU, 
                                     const Standard_Real TolV, 
                                     Standard_Real& U, 
                                     Standard_Real& V)
{

    ProjLib_PrjResolve aPrjPS(C->Curve(), S->Surface(), 1);
    Standard_Real ParU,ParV;
    Extrema_ExtPS aExtPS;
    aExtPS.Initialize(S->Surface(), S->FirstUParameter(), 
		      S->LastUParameter(), S->FirstVParameter(), 
		      S->LastVParameter(), TolU, TolV);

    aExtPS.Perform(Point);
    Standard_Integer argmin = 0;
    if (aExtPS.IsDone() && aExtPS.NbExt()) 
    {
      Standard_Integer i, Nend;
      // Search for the nearest solution which is also a normal projection
      Nend = aExtPS.NbExt();
      for(i = 1; i <= Nend; i++)
      {
         Extrema_POnSurf POnS = aExtPS.Point(i);
         POnS.Parameter(ParU, ParV);
	 aPrjPS.Perform(t, ParU, ParV, gp_Pnt2d(TolU, TolV), 
                        gp_Pnt2d(S->FirstUParameter(), S->FirstVParameter()), 
                        gp_Pnt2d(S->LastUParameter(), S->LastVParameter()), 
                        FuncTol, Standard_True);
         if(aPrjPS.IsDone() )
           if  (argmin == 0 || aExtPS.SquareDistance(i) < aExtPS.SquareDistance(argmin)) argmin = i;  
      }
    }
    if( argmin == 0 ) return Standard_False;
    else
    {  
         Extrema_POnSurf POnS = aExtPS.Point(argmin);
         POnS.Parameter(U, V);
         return Standard_True;
    }
}

//=======================================================================
//function : ProjLib_CompProjectedCurve
//purpose  : 
//=======================================================================

 ProjLib_CompProjectedCurve::ProjLib_CompProjectedCurve()
{
}

//=======================================================================
//function : ProjLib_CompProjectedCurve
//purpose  : 
//=======================================================================

 ProjLib_CompProjectedCurve::ProjLib_CompProjectedCurve(
                             const Handle(Adaptor3d_HSurface)& S,
                             const Handle(Adaptor3d_HCurve)& C, 
                             const Standard_Real TolU, 
                             const Standard_Real TolV) 
 : mySurface(S), myCurve(C), myNbCurves(0), myTolU(TolU), myTolV(TolV), 
   myMaxDist(-1)
{
  mySequence = new ProjLib_HSequenceOfHSequenceOfPnt();
  Init();
}

//=======================================================================
//function : ProjLib_CompProjectedCurve
//purpose  : 
//=======================================================================

 ProjLib_CompProjectedCurve::ProjLib_CompProjectedCurve(
                             const Handle(Adaptor3d_HSurface)& S,
                             const Handle(Adaptor3d_HCurve)& C, 
                             const Standard_Real TolU, 
                             const Standard_Real TolV, 
                             const Standard_Real MaxDist) 
 : mySurface(S), myCurve(C), myNbCurves(0), myTolU(TolU), myTolV(TolV), 
   myMaxDist(MaxDist)
{
  mySequence = new ProjLib_HSequenceOfHSequenceOfPnt();
  Init();
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

 void ProjLib_CompProjectedCurve::Init() 
{
  myTabInt.Nullify();

  Standard_Real Tol;// Tolerance for ExactBound
  Standard_Integer i, Nend = 0;
  Standard_Boolean FromLastU=Standard_False;

  //new part (to discard far solutions)
  //Method Extrema_ExtCS gives wrong result(ex. sphere and segment orthogonal to it)
  Standard_Real TolC = Precision::Confusion(), TolS = Precision::Confusion();
  Extrema_ExtCS CExt(myCurve->Curve(),
		     mySurface->Surface(),
		     TolC,
		     TolS);
  if (CExt.IsDone() && CExt.NbExt()) 
  {
      // Search for the minimum solution
      Nend = CExt.NbExt();
      if(myMaxDist > 0) 
      {
         Standard_Real min_val2;
         min_val2 = CExt.SquareDistance(1);
         for(i = 2; i <= Nend; i++)
	     if (CExt.SquareDistance(i) < min_val2) min_val2 = CExt.SquareDistance(i);  
         if(min_val2 > myMaxDist * myMaxDist) return;
      }
   }
   // end of new part

  Standard_Real FirstU, LastU, Step, DecStep, SearchStep, WalkStep, t;
  
  FirstU = myCurve->FirstParameter();
  LastU  = myCurve->LastParameter();
  const Standard_Real MinStep = 0.01*(LastU - FirstU), 
                      MaxStep = 0.1*(LastU - FirstU);
  SearchStep = 10*MinStep;
  Step = SearchStep;
  
  //Initialization of aPrjPS
  Standard_Real Uinf = mySurface->FirstUParameter();
  Standard_Real Usup = mySurface->LastUParameter();
  Standard_Real Vinf = mySurface->FirstVParameter();
  Standard_Real Vsup = mySurface->LastVParameter();

  ProjLib_PrjResolve aPrjPS(myCurve->Curve(), mySurface->Surface(), 1);

  t = FirstU;
  Standard_Boolean new_part; 
  Standard_Real prevDeb=0.;
  Standard_Boolean SameDeb=Standard_False;
 
                 
  gp_Pnt Triple, prevTriple;

  //Basic loop  
  while(t <= LastU) 
  {
    //Search for the begining a new continuous part
    //To avoid infinite computation in some difficult cases
    new_part = Standard_False;
    if(t > FirstU && Abs(t-prevDeb) <= Precision::PConfusion()) SameDeb=Standard_True;
    while(t <= LastU && !new_part && !FromLastU && !SameDeb)
    {
      prevDeb=t;
      if (t == LastU) FromLastU=Standard_True;
      Standard_Boolean initpoint=Standard_False;
      Standard_Real U=0, V=0;
      gp_Pnt CPoint;
      Standard_Real ParT,ParU,ParV; 

      // Search an initpoint in the list of Extrema Curve-Surface
      if(Nend != 0 && !CExt.IsParallel()) 
      {
         for (i=1;i<=Nend;i++)
         {
              Extrema_POnCurv P1;
              Extrema_POnSurf P2;
              CExt.Points(i,P1,P2);
              ParT=P1.Parameter();
              P2.Parameter(ParU, ParV);

              aPrjPS.Perform(ParT, ParU, ParV, gp_Pnt2d(myTolU, myTolV), 
                             gp_Pnt2d(mySurface->FirstUParameter(),mySurface->FirstVParameter()), 
                             gp_Pnt2d(mySurface->LastUParameter(), mySurface->LastVParameter()), 
                             FuncTol, Standard_True);           
              if ( aPrjPS.IsDone() && P1.Parameter() > Max(FirstU,t-Step+Precision::PConfusion()) 
                  && P1.Parameter() <= t) 
	      {
                  t=ParT;
                  U=ParU;
                  V=ParV;
                  CPoint=P1.Value();
                  initpoint = Standard_True;
                  break;
              }
	 }
      }
      if (!initpoint) 
      {        
         myCurve->D0(t,CPoint);
#ifdef __OCC_DEBUG_CHRONO
         InitChron(chr_init_point);
#endif
         initpoint=InitialPoint(CPoint, t,myCurve,mySurface, myTolU, myTolV, U, V);
#ifdef __OCC_DEBUG_CHRONO
         ResultChron(chr_init_point,t_init_point);
         init_point_count++;
#endif
       }
      if(initpoint) 
      {
        // When U or V lie on surface joint in some cases we cannot use them 
        // as initial point for aPrjPS, so we switch them
	gp_Vec2d D;
	
	if((Abs(U - Uinf) < mySurface->UResolution(Precision::PConfusion())) &&
                                                        mySurface->IsUPeriodic())
        { 
	  d1(t, U, V, D, myCurve, mySurface);
	  if (D.X() < 0) U = Usup;
	}
	else if((Abs(U - Usup) < mySurface->UResolution(Precision::PConfusion())) &&
                                                        mySurface->IsUPeriodic())
    {
	  d1(t, U, V, D, myCurve, mySurface);
	  if (D.X() > 0) U = Uinf;
	}

	if((Abs(V - Vinf) < mySurface->VResolution(Precision::PConfusion())) && 
                                                        mySurface->IsVPeriodic()) 
        {
	  d1(t, U, V, D, myCurve, mySurface);
	  if (D.Y() < 0) V = Vsup;
	}
	else if((Abs(V - Vsup) <= mySurface->VResolution(Precision::PConfusion())) &&
                                                        mySurface->IsVPeriodic())
        {
	  d1(t, U, V, D, myCurve, mySurface);
	  if (D.Y() > 0) V = Vinf;
	}


	if (myMaxDist > 0) 
        {
          // Here we are going to stop if the distance between projection and 
          // corresponding curve point is greater than myMaxDist
	  gp_Pnt POnS;
	  Standard_Real d;
	  mySurface->D0(U, V, POnS);
	  d = CPoint.Distance(POnS);
	  if (d > myMaxDist) 
          {
	    mySequence->Clear();
	    myNbCurves = 0;
	    return;
	  }
        }
	Triple = gp_Pnt(t, U, V);
	if (t != FirstU) 
        {
	  //Search for exact boundary point
	  Tol = Min(myTolU, myTolV);
	  gp_Vec2d D;
	  d1(Triple.X(), Triple.Y(), Triple.Z(), D, myCurve, mySurface);
	  Tol /= Max(Abs(D.X()), Abs(D.Y()));

	  if(!ExactBound(Triple, t - Step, Tol, 
                         myTolU, myTolV, myCurve, mySurface)) 
          {
#if DEB
	    cout<<"There is a problem with ExactBound computation"<<endl;
#endif
	    DichExactBound(Triple, t - Step, Tol, myTolU, myTolV, 
                           myCurve, mySurface);
	  }
	}
	new_part = Standard_True;
      }
      else 
      {
        if(t == LastU) break;
        t += Step;
          if(t>LastU) 
          { 
             Step =Step+LastU-t;
             t=LastU;
          }  
      }
    }
    if (!new_part) break;


    //We have found a new continuous part
    Handle(TColgp_HSequenceOfPnt) hSeq = new TColgp_HSequenceOfPnt();    
    mySequence->Append(hSeq);
    myNbCurves++;
    mySequence->Value(myNbCurves)->Append(Triple);
    prevTriple = Triple;

    if (Triple.X() == LastU) break;//return;

    //Computation of WalkStep
    gp_Vec D1, D2;
    Standard_Real MagnD1, MagnD2;
    d2CurvOnSurf(Triple.X(), Triple.Y(), Triple.Z(), D1, D2, myCurve, mySurface);
    MagnD1 = D1.Magnitude();
    MagnD2 = D2.Magnitude();
    if(MagnD2 < Precision::Confusion()) WalkStep = MaxStep;
    else WalkStep = Min(MaxStep, Max(MinStep, 0.1*MagnD1/MagnD2));
    
    Step = WalkStep;
    DecStep = Step;;

    t = Triple.X() + Step;
    if (t > LastU) t = LastU;

    //Here we are trying to prolong continuous part
    while (t <= LastU && new_part) 
    {
      Standard_Real U0, V0;

      U0 = Triple.Y();
      V0 = Triple.Z();

      aPrjPS.Perform(t, U0, V0, gp_Pnt2d(myTolU, myTolV), 
         gp_Pnt2d(mySurface->FirstUParameter(),mySurface->FirstVParameter()), 
         gp_Pnt2d(mySurface->LastUParameter(), mySurface->LastVParameter()), 
         FuncTol, Standard_True);
      if(!aPrjPS.IsDone()) 
      {

        if (DecStep <= MinStep) 
        {
              //Search for exact boundary point
              Tol = Min(myTolU, myTolV);
	      gp_Vec2d D;
	      d1(Triple.X(), Triple.Y(), Triple.Z(), D, myCurve, mySurface);
	      Tol /= Max(Abs(D.X()), Abs(D.Y()));

	      if(!ExactBound(Triple, t, Tol, myTolU, myTolV, 
                             myCurve, mySurface)) 
              {
#if DEB
	          cout<<"There is a problem with ExactBound computation"<<endl;
#endif
	          DichExactBound(Triple, t, Tol, myTolU, myTolV, 
                                 myCurve, mySurface);
	      }

	      if((Triple.X() - mySequence->Value(myNbCurves)->Value(mySequence->Value(myNbCurves)->Length()).X()) > 1.e-10)
	          mySequence->Value(myNbCurves)->Append(Triple);
	      if((LastU - Triple.X()) < Tol) {t = LastU + 1; break;}//return;

	      Step = SearchStep;
	      t = Triple.X() + Step;
	      if (t > (LastU-MinStep/2) ) 
	      { 
	         Step =Step+LastU-t;
	         t = LastU;
	      }
              DecStep=Step;
	      new_part = Standard_False;
           }
        else 
        {
            // decrease step
            DecStep=DecStep / 2.;
            Step = Max (MinStep , DecStep);
            t = Triple .X() + Step;
	    if (t > (LastU-MinStep/4) ) 
            { 
	         Step =Step+LastU-t;
	         t = LastU;
	    }
        }
      }
      // Go further
      else 
      {
	  prevTriple = Triple; 
	  Triple = gp_Pnt(t, aPrjPS.Solution().X(), aPrjPS.Solution().Y());
	
	  if((Triple.X() - mySequence->Value(myNbCurves)->Value(mySequence->Value(myNbCurves)->Length()).X()) > 1.e-10)
	     mySequence->Value(myNbCurves)->Append(Triple);
	  if (t == LastU) {t = LastU + 1; break;}//return;

          //Computation of WalkStep
	  d2CurvOnSurf(Triple.X(), Triple.Y(), Triple.Z(), D1, D2, myCurve, mySurface);
	  MagnD1 = D1.Magnitude();
	  MagnD2 = D2.Magnitude();
	  if(MagnD2 < Precision::Confusion() ) WalkStep = MaxStep;
	  else WalkStep = Min(MaxStep, Max(MinStep, 0.1*MagnD1/MagnD2));
	
	  Step = WalkStep;
	  t += Step;
	  if (t > (LastU-MinStep/2) ) 
	  { 
	    Step =Step+LastU-t;
	    t = LastU;
	  }	
          DecStep=Step;
      }
    }
  }
  // Sequence postproceeding
  Standard_Integer j;

// 1. Removing poor parts
  Standard_Integer NbPart=myNbCurves;
  Standard_Integer ipart=1;
  for(i = 1; i <= NbPart; i++) {
//    Standard_Integer NbPoints = mySequence->Value(i)->Length();
    if(mySequence->Value(ipart)->Length() < 2) {
      mySequence->Remove(ipart);
      myNbCurves--;
    }
    else ipart++;
  }

  if(myNbCurves == 0) return;

// 2. Removing common parts of bounds
  for(i = 1; i < myNbCurves; i++) 
  {
    if(mySequence->Value(i)->Value(mySequence->Value(i)->Length()).X() >= 
       mySequence->Value(i+1)->Value(1).X())
      mySequence->ChangeValue(i+1)->ChangeValue(1).SetX(mySequence->Value(i)->Value(mySequence->Value(i)->Length()).X() + 1.e-12);
  }

// 3. Computation of the maximum distance from each part of curve to surface

  myMaxDistance = new TColStd_HArray1OfReal(1, myNbCurves);
  myMaxDistance->Init(0);
  for(i = 1; i <= myNbCurves; i++)
    for(j = 1; j <= mySequence->Value(i)->Length(); j++) 
    {
      gp_Pnt POnC, POnS, Triple;
      Standard_Real Distance;
      Triple = mySequence->Value(i)->Value(j);
      myCurve->D0(Triple.X(), POnC);
      mySurface->D0(Triple.Y(), Triple.Z(), POnS);
      Distance = POnC.Distance(POnS);
      if (myMaxDistance->Value(i) < Distance)
	myMaxDistance->ChangeValue(i) = Distance;
    } 


// 4. Check the projection to be a single point

  gp_Pnt2d Pmoy, Pcurr, P;
  Standard_Real AveU, AveV;
  mySnglPnts = new TColStd_HArray1OfBoolean(1, myNbCurves);
  for(i = 1; i <= myNbCurves; i++) mySnglPnts->SetValue(i, Standard_True);

  for(i = 1; i <= myNbCurves; i++)
  {    
    //compute an average U and V

    for(j = 1, AveU = 0., AveV = 0.; j <= mySequence->Value(i)->Length(); j++)
    {
      AveU += mySequence->Value(i)->Value(j).Y();
      AveV += mySequence->Value(i)->Value(j).Z();
    }
    AveU /= mySequence->Value(i)->Length();
    AveV /= mySequence->Value(i)->Length();

    Pmoy.SetCoord(AveU,AveV);
    for(j = 1; j <= mySequence->Value(i)->Length(); j++)
    {
	Pcurr = 
        gp_Pnt2d(mySequence->Value(i)->Value(j).Y(), mySequence->Value(i)->Value(j).Z());
	if (Pcurr.Distance(Pmoy) > ((myTolU < myTolV) ? myTolV : myTolU))
        {
	  mySnglPnts->SetValue(i, Standard_False);
	  break;
	}
    }
  }
  
// 5. Check the projection to be an isoparametric curve of the surface

  myUIso = new TColStd_HArray1OfBoolean(1, myNbCurves);
  for(i = 1; i <= myNbCurves; i++) myUIso->SetValue(i, Standard_True);

  myVIso = new TColStd_HArray1OfBoolean(1, myNbCurves);
  for(i = 1; i <= myNbCurves; i++) myVIso->SetValue(i, Standard_True);

  for(i = 1; i <= myNbCurves; i++) {
    if (IsSinglePnt(i, P)|| mySequence->Value(i)->Length() <=2) {
      myUIso->SetValue(i, Standard_False);
      myVIso->SetValue(i, Standard_False);
      continue;
    }

// new test for isoparametrics

   if ( mySequence->Value(i)->Length() > 2) {
    //compute an average U and V

    for(j = 1, AveU = 0., AveV = 0.; j <= mySequence->Value(i)->Length(); j++) {
      AveU += mySequence->Value(i)->Value(j).Y();
      AveV += mySequence->Value(i)->Value(j).Z();
    }
    AveU /= mySequence->Value(i)->Length();
    AveV /= mySequence->Value(i)->Length();

    // is i-part U-isoparametric ?
    for(j = 1; j <= mySequence->Value(i)->Length(); j++) 
    {
      if(Abs(mySequence->Value(i)->Value(j).Y() - AveU) > myTolU) 
      {
	myUIso->SetValue(i, Standard_False);
	break;
      }
    }

    // is i-part V-isoparametric ?
    for(j = 1; j <= mySequence->Value(i)->Length(); j++) 
    {
      if(Abs(mySequence->Value(i)->Value(j).Z() - AveV) > myTolV) 
      {
	myVIso->SetValue(i, Standard_False);
	break;
      }
    }
//
  }
  }
}
//=======================================================================
//function : Load
//purpose  : 
//=======================================================================

void ProjLib_CompProjectedCurve::Load(const Handle(Adaptor3d_HSurface)& S) 
{
  mySurface = S;
}

//=======================================================================
//function : Load
//purpose  : 
//=======================================================================

void ProjLib_CompProjectedCurve::Load(const Handle(Adaptor3d_HCurve)& C) 
{
  myCurve = C;
}

//=======================================================================
//function : GetSurface
//purpose  : 
//=======================================================================

 const Handle(Adaptor3d_HSurface)& ProjLib_CompProjectedCurve::GetSurface() const
{
  return mySurface;
}


//=======================================================================
//function : GetCurve
//purpose  : 
//=======================================================================

 const Handle(Adaptor3d_HCurve)& ProjLib_CompProjectedCurve::GetCurve() const
{
  return myCurve;
}

//=======================================================================
//function : GetTolerance
//purpose  : 
//=======================================================================

 void ProjLib_CompProjectedCurve::GetTolerance(Standard_Real& TolU,
                                               Standard_Real& TolV) const
{
  TolU = myTolU;
  TolV = myTolV;
}

//=======================================================================
//function : NbCurves
//purpose  : 
//=======================================================================

 Standard_Integer ProjLib_CompProjectedCurve::NbCurves() const
{
  return myNbCurves;
}
//=======================================================================
//function : Bounds
//purpose  : 
//=======================================================================

 void ProjLib_CompProjectedCurve::Bounds(const Standard_Integer Index,
                                         Standard_Real& Udeb,
                                         Standard_Real& Ufin) const
{
  if(Index < 1 || Index > myNbCurves) Standard_NoSuchObject::Raise();
  Udeb = mySequence->Value(Index)->Value(1).X();
  Ufin = mySequence->Value(Index)->Value(mySequence->Value(Index)->Length()).X();
}
//=======================================================================
//function : IsSinglePnt
//purpose  : 
//=======================================================================

 Standard_Boolean ProjLib_CompProjectedCurve::IsSinglePnt(const Standard_Integer Index, gp_Pnt2d& P) const
{
  if(Index < 1 || Index > myNbCurves) Standard_NoSuchObject::Raise();
  P = gp_Pnt2d(mySequence->Value(Index)->Value(1).Y(), mySequence->Value(Index)->Value(1).Z());
  return mySnglPnts->Value(Index);
}

//=======================================================================
//function : IsUIso
//purpose  : 
//=======================================================================

 Standard_Boolean ProjLib_CompProjectedCurve::IsUIso(const Standard_Integer Index, Standard_Real& U) const
{
  if(Index < 1 || Index > myNbCurves) Standard_NoSuchObject::Raise();
  U = mySequence->Value(Index)->Value(1).Y();
  return myUIso->Value(Index);
}
//=======================================================================
//function : IsVIso
//purpose  : 
//=======================================================================

 Standard_Boolean ProjLib_CompProjectedCurve::IsVIso(const Standard_Integer Index, Standard_Real& V) const
{
  if(Index < 1 || Index > myNbCurves) Standard_NoSuchObject::Raise();
  V = mySequence->Value(Index)->Value(1).Z();
  return myVIso->Value(Index);
}
//=======================================================================
//function : Value
//purpose  : 
//=======================================================================

 gp_Pnt2d ProjLib_CompProjectedCurve::Value(const Standard_Real t) const
{
  gp_Pnt2d P;
  D0(t, P);
  return P;
}
//=======================================================================
//function : D0
//purpose  : 
//=======================================================================

 void ProjLib_CompProjectedCurve::D0(const Standard_Real U,gp_Pnt2d& P) const
{
  Standard_Integer i, j;
  Standard_Real Udeb, Ufin;
  Standard_Boolean found = Standard_False;

  for(i = 1; i <= myNbCurves; i++) 
  {
    Bounds(i, Udeb, Ufin);
    if (U >= Udeb && U <= Ufin) 
    {
      found = Standard_True;
      break;
    }
  }
  if (!found) Standard_DomainError::Raise("ProjLib_CompProjectedCurve::D0");

  Standard_Real U0, V0;

  Standard_Integer End = mySequence->Value(i)->Length();
  for(j = 1; j < End; j++)
    if ((U >= mySequence->Value(i)->Value(j).X()) && (U <= mySequence->Value(i)->Value(j + 1).X())) break;

//  U0 = mySequence->Value(i)->Value(j).Y();
//  V0 = mySequence->Value(i)->Value(j).Z();

//  Cubic Interpolation
  if(mySequence->Value(i)->Length() < 4 || 
    (Abs(U-mySequence->Value(i)->Value(j).X()) <= Precision::PConfusion()) ) 
  {
    U0 = mySequence->Value(i)->Value(j).Y();
    V0 = mySequence->Value(i)->Value(j).Z();
  }
  else if (Abs(U-mySequence->Value(i)->Value(j+1).X()) 
        <= Precision::PConfusion())
  {
    U0 = mySequence->Value(i)->Value(j+1).Y();
    V0 = mySequence->Value(i)->Value(j+1).Z();
  }
  else 
  {
    if (j == 1) j = 2;
    if (j > mySequence->Value(i)->Length() - 2) 
        j = mySequence->Value(i)->Length() - 2;
    
    gp_Vec2d I1, I2, I3, I21, I22, I31, Y1, Y2, Y3, Y4, Res;
    Standard_Real X1, X2, X3, X4;
    
    X1 = mySequence->Value(i)->Value(j - 1).X();
    X2 = mySequence->Value(i)->Value(j).X();
    X3 = mySequence->Value(i)->Value(j + 1).X();
    X4 = mySequence->Value(i)->Value(j + 2).X();
    
    Y1 = gp_Vec2d(mySequence->Value(i)->Value(j - 1).Y(), 
                  mySequence->Value(i)->Value(j - 1).Z());
    Y2 = gp_Vec2d(mySequence->Value(i)->Value(j).Y(), 
                  mySequence->Value(i)->Value(j).Z());
    Y3 = gp_Vec2d(mySequence->Value(i)->Value(j + 1).Y(), 
                  mySequence->Value(i)->Value(j + 1).Z());
    Y4 = gp_Vec2d(mySequence->Value(i)->Value(j + 2).Y(), 
                  mySequence->Value(i)->Value(j + 2).Z());
    
    I1 = (Y1 - Y2)/(X1 - X2);
    I2 = (Y2 - Y3)/(X2 - X3);
    I3 = (Y3 - Y4)/(X3 - X4);
    
    I21 = (I1 - I2)/(X1 - X3);
    I22 = (I2 - I3)/(X2 - X4);
    
    I31 = (I21 - I22)/(X1 - X4);
    
    Res = Y1 + (U - X1)*(I1 + (U - X2)*(I21 + (U - X3)*I31));
      
    U0 = Res.X();
    V0 = Res.Y();

    if(U0 < mySurface->FirstUParameter()) U0 = mySurface->FirstUParameter();
    else if(U0 > mySurface->LastUParameter()) U0 = mySurface->LastUParameter();

    if(V0 < mySurface->FirstVParameter()) V0 = mySurface->FirstVParameter();
    else if(V0 > mySurface->LastVParameter()) V0 = mySurface->LastVParameter();
  }
  //End of cubic interpolation

  ProjLib_PrjResolve aPrjPS(myCurve->Curve(), mySurface->Surface(), 1);
  aPrjPS.Perform(U, U0, V0, gp_Pnt2d(myTolU, myTolV), 
         gp_Pnt2d(mySurface->FirstUParameter(), mySurface->FirstVParameter()), 
         gp_Pnt2d(mySurface->LastUParameter(), mySurface->LastVParameter()));
  P = aPrjPS.Solution();

}
//=======================================================================
//function : D1
//purpose  : 
//=======================================================================

 void ProjLib_CompProjectedCurve::D1(const Standard_Real t,
                                     gp_Pnt2d& P,
                                     gp_Vec2d& V) const
{
  Standard_Real u, v;
  D0(t, P);
  u = P.X();
  v = P.Y();
  d1(t, u, v, V, myCurve, mySurface);
}
//=======================================================================
//function : D2
//purpose  : 
//=======================================================================

 void ProjLib_CompProjectedCurve::D2(const Standard_Real t,
                                     gp_Pnt2d& P,
                                     gp_Vec2d& V1,
                                     gp_Vec2d& V2) const
{
  Standard_Real u, v;
  D0(t, P);
  u = P.X();
  v = P.Y();
  d2(t, u, v, V1, V2, myCurve, mySurface);
}
//=======================================================================
//function : DN
//purpose  : 
//=======================================================================

gp_Vec2d ProjLib_CompProjectedCurve::DN(const Standard_Real t, 
			                const Standard_Integer N) const 
{
  if (N < 1 ) Standard_OutOfRange::Raise("ProjLib_CompProjectedCurve : N must be greater than 0");
  else if (N ==1) 
  {
     gp_Pnt2d P;
     gp_Vec2d V;
     D1(t,P,V);
     return V;
   }
  else if ( N==2)
  {
     gp_Pnt2d P;
     gp_Vec2d V1,V2;
     D2(t,P,V1,V2);
     return V2;
  }
  else if (N > 2 ) 
     Standard_NotImplemented::Raise("ProjLib_CompProjectedCurve::DN");
  return gp_Vec2d();
}

//=======================================================================
//function : GetSequence
//purpose  : 
//=======================================================================

 const Handle(ProjLib_HSequenceOfHSequenceOfPnt)& ProjLib_CompProjectedCurve::GetSequence() const
{
  return mySequence;
}
//=======================================================================
//function : FirstParameter
//purpose  : 
//=======================================================================

 Standard_Real ProjLib_CompProjectedCurve::FirstParameter() const
{
  return myCurve->FirstParameter();
}

//=======================================================================
//function : LastParameter
//purpose  : 
//=======================================================================

 Standard_Real ProjLib_CompProjectedCurve::LastParameter() const
{
  return myCurve->LastParameter();
}

//=======================================================================
//function : MaxDistance
//purpose  : 
//=======================================================================

 Standard_Real ProjLib_CompProjectedCurve::MaxDistance(const Standard_Integer Index) const
{
  if(Index < 1 || Index > myNbCurves) Standard_NoSuchObject::Raise();
  return myMaxDistance->Value(Index);
}

//=======================================================================
//function : NbIntervals
//purpose  : 
//=======================================================================

 Standard_Integer ProjLib_CompProjectedCurve::NbIntervals(const GeomAbs_Shape S) const
{
  const_cast<ProjLib_CompProjectedCurve*>(this)->myTabInt.Nullify();
  BuildIntervals(S);
  return myTabInt->Length() - 1;
}

//=======================================================================
//function : Intervals
//purpose  : 
//=======================================================================

 void ProjLib_CompProjectedCurve::Intervals(TColStd_Array1OfReal& T,const GeomAbs_Shape S) const
{
  if (myTabInt.IsNull()) BuildIntervals (S);
  T = myTabInt->Array1();
}

//=======================================================================
//function : BuildIntervals
//purpose  : 
//=======================================================================

 void ProjLib_CompProjectedCurve::BuildIntervals(const GeomAbs_Shape S) const
{
  GeomAbs_Shape SforS = GeomAbs_CN;
  switch(S) {
  case GeomAbs_C0: 
    SforS = GeomAbs_C1; 
    break;    
  case GeomAbs_C1: 
    SforS = GeomAbs_C2; 
    break;
  case GeomAbs_C2: 
    SforS = GeomAbs_C3; 
    break;
  case GeomAbs_C3:
    SforS = GeomAbs_CN; 
    break;
  case GeomAbs_CN: 
    SforS = GeomAbs_CN; 
    break;
  default: 
    Standard_OutOfRange::Raise();
  }
  Standard_Integer i, j, k;
  Standard_Integer NbIntCur = myCurve->NbIntervals(S);
  Standard_Integer NbIntSurU = mySurface->NbUIntervals(SforS);
  Standard_Integer NbIntSurV = mySurface->NbVIntervals(SforS);

  TColStd_Array1OfReal CutPntsT(1, NbIntCur+1);
  TColStd_Array1OfReal CutPntsU(1, NbIntSurU+1);
  TColStd_Array1OfReal CutPntsV(1, NbIntSurV+1);

  myCurve->Intervals(CutPntsT, S);
  mySurface->UIntervals(CutPntsU, SforS);
  mySurface->VIntervals(CutPntsV, SforS);

  Standard_Real Tl, Tr, Ul, Ur, Vl, Vr, Tol;

  Handle(TColStd_HArray1OfReal) BArr = NULL, 
                                CArr = NULL, 
                                UArr = NULL, 
                                VArr = NULL;

  // proccessing projection bounds
  BArr = new TColStd_HArray1OfReal(1, 2*myNbCurves);
  for(i = 1; i <= myNbCurves; i++)
    Bounds(i, BArr->ChangeValue(2*i - 1), BArr->ChangeValue(2*i));

  // proccessing curve discontinuities
  if(NbIntCur > 1) {
    CArr = new TColStd_HArray1OfReal(1, NbIntCur - 1);
    for(i = 1; i <= CArr->Length(); i++)
      CArr->ChangeValue(i) = CutPntsT(i + 1);
  }

  // proccessing U-surface discontinuities  
  TColStd_SequenceOfReal TUdisc;

  for(k = 2; k <= NbIntSurU; k++) {
//    cout<<"CutPntsU("<<k<<") = "<<CutPntsU(k)<<endl;
    for(i = 1; i <= myNbCurves; i++)
      for(j = 1; j < mySequence->Value(i)->Length(); j++) {
	Ul = mySequence->Value(i)->Value(j).Y();
	Ur = mySequence->Value(i)->Value(j + 1).Y();

	if(Abs(Ul - CutPntsU(k)) <= myTolU) 
           TUdisc.Append(mySequence->Value(i)->Value(j).X());
	else if(Abs(Ur - CutPntsU(k)) <= myTolU) 
           TUdisc.Append(mySequence->Value(i)->Value(j + 1).X());
	else if((Ul < CutPntsU(k) && CutPntsU(k) < Ur) ||
		(Ur < CutPntsU(k) && CutPntsU(k) < Ul))
        {
	  Standard_Real V;
	  V = (mySequence->Value(i)->Value(j).Z() 
            + mySequence->Value(i)->Value(j +1).Z())/2;
	  ProjLib_PrjResolve Solver(myCurve->Curve(), mySurface->Surface(), 2);
	  
	  gp_Vec2d D;
	  gp_Pnt Triple;
	  Triple = mySequence->Value(i)->Value(j);
	  d1(Triple.X(), Triple.Y(), Triple.Z(), D, myCurve, mySurface);
	  if (Abs(D.X()) < Precision::Confusion()) 
	    Tol = myTolU;
	  else 
	    Tol = Min(myTolU, myTolU / Abs(D.X()));

	  Tl = mySequence->Value(i)->Value(j).X();
	  Tr = mySequence->Value(i)->Value(j + 1).X();
	  
	  Solver.Perform((Tl + Tr)/2, CutPntsU(k), V, 
                          gp_Pnt2d(Tol, myTolV), 
                          gp_Pnt2d(Tl, mySurface->FirstVParameter()), 
                          gp_Pnt2d(Tr, mySurface->LastVParameter()));
	  TUdisc.Append(Solver.Solution().X());
	}
      }
  }
  for(i = 2; i <= TUdisc.Length(); i++)
    if(TUdisc(i) - TUdisc(i-1) < Precision::PConfusion())
      TUdisc.Remove(i--);

  if(TUdisc.Length()) 
  {
    UArr = new TColStd_HArray1OfReal(1, TUdisc.Length());
    for(i = 1; i <= UArr->Length(); i++)
      UArr->ChangeValue(i) = TUdisc(i);
  }
  // proccessing V-surface discontinuities
  TColStd_SequenceOfReal TVdisc;

  for(k = 2; k <= NbIntSurV; k++)
    for(i = 1; i <= myNbCurves; i++) 
    {
//      cout<<"CutPntsV("<<k<<") = "<<CutPntsV(k)<<endl;
      for(j = 1; j < mySequence->Value(i)->Length(); j++) {

	Vl = mySequence->Value(i)->Value(j).Z();
	Vr = mySequence->Value(i)->Value(j + 1).Z();

	if(Abs(Vl - CutPntsV(k)) <= myTolV) 
           TVdisc.Append(mySequence->Value(i)->Value(j).X());
	else if (Abs(Vr - CutPntsV(k)) <= myTolV) 
           TVdisc.Append(mySequence->Value(i)->Value(j + 1).X());
	else if((Vl < CutPntsV(k) && CutPntsV(k) < Vr) ||
		(Vr < CutPntsV(k) && CutPntsV(k) < Vl))
        {
	  Standard_Real U;
	  U = (mySequence->Value(i)->Value(j).Y() 
             + mySequence->Value(i)->Value(j +1).Y())/2;
	  ProjLib_PrjResolve Solver(myCurve->Curve(), mySurface->Surface(), 3);
	  
	  gp_Vec2d D;
	  gp_Pnt Triple;
	  Triple = mySequence->Value(i)->Value(j);
	  d1(Triple.X(), Triple.Y(), Triple.Z(), D, myCurve, mySurface);
	  if (Abs(D.Y()) < Precision::Confusion()) 
	    Tol = myTolV;
	  else 
	    Tol = Min(myTolV, myTolV / Abs(D.Y()));
	  
	  Tl = mySequence->Value(i)->Value(j).X();
	  Tr = mySequence->Value(i)->Value(j + 1).X();

	  Solver.Perform((Tl + Tr)/2, U, CutPntsV(k), 
                         gp_Pnt2d(Tol, myTolV), 
                         gp_Pnt2d(Tl, mySurface->FirstUParameter()), 
                         gp_Pnt2d(Tr, mySurface->LastUParameter()));
	                 TVdisc.Append(Solver.Solution().X());
	}
      }
  }
  for(i = 2; i <= TVdisc.Length(); i++)
    if(TVdisc(i) - TVdisc(i-1) < Precision::PConfusion())
      TVdisc.Remove(i--);

  if(TVdisc.Length()) 
  {
    VArr = new TColStd_HArray1OfReal(1, TVdisc.Length());
    for(i = 1; i <= VArr->Length(); i++)
      VArr->ChangeValue(i) = TVdisc(i);
  }

  // fusion
  TColStd_SequenceOfReal Fusion;
  if(!CArr.IsNull()) 
  {
    GeomLib::FuseIntervals(BArr->ChangeArray1(), 
                           CArr->ChangeArray1(), 
                           Fusion, Precision::PConfusion());
    BArr = new TColStd_HArray1OfReal(1, Fusion.Length());
    for(i = 1; i <= BArr->Length(); i++)
      BArr->ChangeValue(i) = Fusion(i);
    Fusion.Clear();
  }

  if(!UArr.IsNull()) 
  {
    GeomLib::FuseIntervals(BArr->ChangeArray1(), 
                           UArr->ChangeArray1(), 
                           Fusion, Precision::PConfusion());
    BArr = new TColStd_HArray1OfReal(1, Fusion.Length());
    for(i = 1; i <= BArr->Length(); i++)
      BArr->ChangeValue(i) = Fusion(i);
    Fusion.Clear();
  }

  if(!VArr.IsNull()) 
  {
    GeomLib::FuseIntervals(BArr->ChangeArray1(), 
                           VArr->ChangeArray1(), 
                           Fusion, Precision::PConfusion());
    BArr = new TColStd_HArray1OfReal(1, Fusion.Length());
    for(i = 1; i <= BArr->Length(); i++)
      BArr->ChangeValue(i) = Fusion(i);
  }

  const_cast<ProjLib_CompProjectedCurve*>(this)->myTabInt = new TColStd_HArray1OfReal(1, BArr->Length());
  for(i = 1; i <= BArr->Length(); i++)
    myTabInt->ChangeValue(i) = BArr->Value(i);

}

//=======================================================================
//function : Trim
//purpose  : 
//=======================================================================

Handle(Adaptor2d_HCurve2d) ProjLib_CompProjectedCurve::Trim
(const Standard_Real First,
 const Standard_Real Last,
 const Standard_Real Tol) const 
{
  Handle(ProjLib_HCompProjectedCurve) HCS = 
        new ProjLib_HCompProjectedCurve(*this);
  HCS->ChangeCurve2d().Load(mySurface);
  HCS->ChangeCurve2d().Load(myCurve->Trim(First,Last,Tol));
  return HCS;
}

//=======================================================================
//function : GetType
//purpose  : 
//=======================================================================

GeomAbs_CurveType ProjLib_CompProjectedCurve::GetType() const 
{
  return GeomAbs_OtherCurve;
}
