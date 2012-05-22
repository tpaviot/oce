// Created on: 1995-09-22
// Created by: Bruno DUMORTIER
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



#include <BRepFill_ApproxSeewing.ixx>

#include <AppParCurves_MultiCurve.hxx>
#include <AppDef_Compute.hxx>
#include <AppDef_MultiLine.hxx>
#include <AppDef_MultiPointConstraint.hxx>
#include <BSplCLib.hxx>
#include <PLib.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>


//=======================================================================
//function : BRepFill_ApproxSeewing
//purpose  : 
//=======================================================================

BRepFill_ApproxSeewing::BRepFill_ApproxSeewing() 
:myIsDone(Standard_False)
{
}


//=======================================================================
//function : BRepFill_ApproxSeewing
//purpose  : 
//=======================================================================

BRepFill_ApproxSeewing::BRepFill_ApproxSeewing(const BRepFill_MultiLine& ML) 
:myIsDone(Standard_False)
{
  Perform(ML);
}


//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================

void BRepFill_ApproxSeewing::Perform(const BRepFill_MultiLine& ML)
{
  myML = ML;

  // evaluate the approximative length of the 3dCurve
  Standard_Integer i;
  Standard_Real Length = 0.;
  Standard_Real U1 = myML.FirstParameter();
  Standard_Real U2 = myML.LastParameter();
  Standard_Integer NbPoints = 50;
  Standard_Real Dist, dU = (U2 - U1) / ( 2*NbPoints - 1);

  TColgp_Array1OfPnt2d LP(1,2*NbPoints); // tableau Longueur <-> Param 
  gp_Pnt P1, P2;
  P1 = myML.Value(U1);

  for ( i = 0; i < 2*NbPoints ; i++) {
    P2      = myML.Value(U1 + i*dU);
    Dist    = P1.Distance(P2);
    Length += Dist;
    LP(i+1) = gp_Pnt2d( Length, U1 + (i*dU));
    P1      = P2;
  }

  // On cherche a mettre NbPoints dans la curve.
  // on met les points environ a Length/NbPoints.
  
  AppDef_MultiLine            MLS ( NbPoints);
  AppDef_MultiPointConstraint MP  ( 1, 2);
  gp_Pnt                      P3d;
  gp_Pnt2d                    PF1,PF2;

  ML.Value3dOnF1OnF2(U1,P3d,PF1,PF2);
  MP.SetPoint  (1, P3d);
  MP.SetPoint2d(2, PF1);
  MP.SetPoint2d(3, PF2);
  MLS.SetValue (1, MP);
  
  Standard_Real DCorde = Length / ( NbPoints - 1); 
  Standard_Real Corde  = DCorde;
  Standard_Integer Index = 1;
  Standard_Real U, Alpha;
  for ( i = 2; i < NbPoints; i++) {
    while ( LP(Index).X() < Corde) Index ++;
    Alpha = (Corde - LP(Index-1).X()) / (LP(Index).X() - LP(Index-1).X());
    U = LP(Index-1).Y() + Alpha * ( LP(Index).Y() - LP(Index-1).Y());
    AppDef_MultiPointConstraint MPC( 1, 2);
    ML.Value3dOnF1OnF2(U,P3d,PF1,PF2);
    MPC.SetPoint  (1, P3d);
    MPC.SetPoint2d(2, PF1);
    MPC.SetPoint2d(3, PF2);
    MLS.SetValue  (i, MPC);
    Corde = i*DCorde;
  }
  AppDef_MultiPointConstraint MPE( 1, 2);
  ML.Value3dOnF1OnF2(U2,P3d,PF1,PF2);
  MPE.SetPoint  (1, P3d);
  MPE.SetPoint2d(2, PF1);
  MPE.SetPoint2d(3, PF2);
  MLS.SetValue (NbPoints, MPE);
  
  AppDef_Compute Fit(MLS);

  Standard_Integer NbCurves = Fit.NbMultiCurves();
//  Standard_Integer MaxDeg = 0;
  
  if ( NbCurves == 0) {
#ifdef DEBUG_EVOLVED
    cout << " TrimSurfaceTool : Approx echoue, on met les polygones" << endl;
#endif

    TColStd_Array1OfReal    Knots(1,NbPoints);
    TColStd_Array1OfInteger Mults(1,NbPoints);
    Mults.Init(1);
    Mults(1) = Mults(NbPoints) =  2;
    TColgp_Array1OfPnt   P (1,NbPoints);
    TColgp_Array1OfPnt2d P1(1,NbPoints);
    TColgp_Array1OfPnt2d P2(1,NbPoints);
    
    Standard_Real Uf = ML.FirstParameter();
    Standard_Real Ul = ML.LastParameter();
    Standard_Real dU = (Ul-Uf)/(NbPoints-1);
    AppDef_MultiPointConstraint MPC;
    for ( i = 1; i<= NbPoints-1; i++) {
      MPC = MLS.Value(i);
      U = Uf + (i-1) * dU;
      P (i) = MPC.Point(1);
      P1(i) = MPC.Point2d(2);
      P2(i) = MPC.Point2d(3);
      Knots(i) = U;
    }
    // eval the last point on Ul
    MPC = MLS.Value(NbPoints);
    P (NbPoints)    = MPC.Point(1);
    P1(NbPoints)    = MPC.Point2d(2);
    P2(NbPoints)    = MPC.Point2d(3);
    Knots(NbPoints) = Ul;
    
    myCurve   = new Geom_BSplineCurve  ( P , Knots, Mults, 1);
    myPCurve1 = new Geom2d_BSplineCurve( P1, Knots, Mults, 1);
    myPCurve2 = new Geom2d_BSplineCurve( P2, Knots, Mults, 1);
    
    myIsDone  = Standard_True;
    
    return;
  }
  
  // Les approx sont a priori OK.
  
  const AppParCurves_MultiBSpCurve& MBSp = 
    Fit.SplineValue();
  Standard_Integer NbPoles = MBSp.NbPoles();
  TColgp_Array1OfPnt   Poles   (1 , NbPoles);
  TColgp_Array1OfPnt2d Poles2d1(1 , NbPoles);
  TColgp_Array1OfPnt2d Poles2d2(1 , NbPoles);
  
  MBSp.Curve(1, Poles);
  MBSp.Curve(2, Poles2d1);
  MBSp.Curve(3, Poles2d2);
  
  const TColStd_Array1OfReal&    Knots  = MBSp.Knots();
  const TColStd_Array1OfInteger& Mults  = MBSp.Multiplicities();
  Standard_Integer               Degree = MBSp.Degree();

  myCurve   = new Geom_BSplineCurve  (Poles,   Knots,Mults,Degree);
  myPCurve1 = new Geom2d_BSplineCurve(Poles2d1,Knots,Mults,Degree);
  myPCurve2 = new Geom2d_BSplineCurve(Poles2d2,Knots,Mults,Degree);
  
  myIsDone = Standard_True;
}


//=======================================================================
//function : IsDone
//purpose  : 
//=======================================================================

Standard_Boolean BRepFill_ApproxSeewing::IsDone() const 
{
  return myIsDone;
}


//=======================================================================
//function : Handle_Geom_Curve&
//purpose  : 
//=======================================================================

const Handle(Geom_Curve)& BRepFill_ApproxSeewing::Curve() const 
{
  StdFail_NotDone_Raise_if( !myIsDone,
			    "BRepFill_ApproxSeewing::Curve");
  return myCurve;
}


//=======================================================================
//function : Handle_Geom2d_Curve&
//purpose  : 
//=======================================================================

const Handle(Geom2d_Curve)& BRepFill_ApproxSeewing::CurveOnF1() const 
{
  StdFail_NotDone_Raise_if( !myIsDone,
			    "BRepFill_ApproxSeewing::CurveOnF1");
  return myPCurve1;
}


//=======================================================================
//function : Handle_Geom2d_Curve&
//purpose  : 
//=======================================================================

const Handle(Geom2d_Curve)& BRepFill_ApproxSeewing::CurveOnF2() const 
{
  StdFail_NotDone_Raise_if( !myIsDone,
			    "BRepFill_ApproxSeewing::CurveOnF2");
  return myPCurve2;
}


