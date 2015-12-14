// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

//:k1 abv 16.12.98 K4L PRO10107, PRO10108, PRO10109
//:j8 abv 10.12.98 TR10 r0501_db.stp #9423
//:S4030 abv, pdn: new methods - interface to standard ProjLib_CompProjectedCurve
//%12 pdn 15.02.99 PRO9234 optimizing
//%12 pdn 15.02.99 PRO9234 using improved ProjectDegenerated method
//    rln 03.03.99 S4135: bm2_sd_t4-A.stp treatment of Geom_SphericalSurface together with V-closed surfaces
//:p9 abv 11.03.99 PRO7226 #489490: make IsAnIsoparametric to find nearest case
//:q1 abv 15.03.99 (pdn) PRO7226 #525030: limit NextValueOfUV() by tolerance
//:q5 abv 19.03.99 code improvement
//:q9 abv 23.03.99 PRO7226.stp #489490: cashe for projecting end points
//#78 rln 12.03.99 S4135: checking spatial closure with myPreci
//    pdn 12.03.99 S4135: creating pcurve with minimal length in the case of densed points
//    abv 29.03.99 IsAnIsoparametric with Precision::Confusion
//    pdn 09.04.99 IsAnisoparametric uses already computed parameters (S4030, fix PRO14323)
//szv#4 S4163
//:s5 abv 22.04.99  Adding debug printouts in catch {} blocks
//#1  svv 11.01.00  Porting on DEC
#include <ShapeConstruct_ProjectCurveOnSurface.ixx>

#include <Standard_ErrorHandler.hxx>
#include <Standard_Failure.hxx>

#include <algorithm>

#include <Precision.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <NCollection_Sequence.hxx>

#include <GeomAPI_PointsToBSpline.hxx>
#include <Geom2dAPI_Interpolate.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <Geom2dAdaptor.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2d_Hyperbola.hxx>
#include <Geom2d_Parabola.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom_SurfaceOfLinearExtrusion.hxx>
#include <Geom_SphericalSurface.hxx>
#include <Geom_OffsetSurface.hxx>
#include <Geom_Plane.hxx>
#include <GeomProjLib.hxx>
#include <GeomAdaptor_HSurface.hxx>
#include <GeomAdaptor_HCurve.hxx>

#include <ShapeAnalysis_Curve.hxx>
#include <ShapeAnalysis_Surface.hxx>
#include <ShapeExtend.hxx>

#include <ProjLib_ProjectedCurve.hxx>
#include <ProjLib_CompProjectedCurve.hxx>
#include <ProjLib_HCompProjectedCurve.hxx>
#include <Approx_CurveOnSurface.hxx>

#define NCONTROL 23

//=======================================================================
//function : ShapeConstruct_ProjectCurveOnSurface
//purpose  : 
//=======================================================================

ShapeConstruct_ProjectCurveOnSurface::ShapeConstruct_ProjectCurveOnSurface()
{
  myPreci = Precision::Confusion();
  myBuild = Standard_False;
  myAdjustOverDegen = 1; //:c0 //szv#4:S4163:12Mar99 was boolean
  myNbCashe = 0; //:q9
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

 void ShapeConstruct_ProjectCurveOnSurface::Init(const Handle(Geom_Surface)& surf,const Standard_Real preci) 
{
  Init (new ShapeAnalysis_Surface (surf), preci);
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

 void ShapeConstruct_ProjectCurveOnSurface::Init(const Handle(ShapeAnalysis_Surface)& surf,const Standard_Real preci) 
{
  SetSurface (surf);
  SetPrecision (preci);
}

//=======================================================================
//function : SetSurface
//purpose  : 
//=======================================================================

 void ShapeConstruct_ProjectCurveOnSurface::SetSurface(const Handle(Geom_Surface)& surf) 
{
  SetSurface (new ShapeAnalysis_Surface (surf));
}

//=======================================================================
//function : SetSurface
//purpose  : 
//=======================================================================

 void ShapeConstruct_ProjectCurveOnSurface::SetSurface(const Handle(ShapeAnalysis_Surface)& surf) 
{
  if ( mySurf == surf ) return;
  mySurf = surf;
  myNbCashe = 0; //:q9
}

//=======================================================================
//function : SetPrecision
//purpose  : 
//=======================================================================

 void ShapeConstruct_ProjectCurveOnSurface::SetPrecision(const Standard_Real preci) 
{
  myPreci = preci;
}

//=======================================================================
//function : BuildCurveMode
//purpose  : 
//=======================================================================

 Standard_Boolean& ShapeConstruct_ProjectCurveOnSurface::BuildCurveMode()
{
  return myBuild;
}

//=======================================================================
//function : AdjustOverDegenMode
//purpose  : 
//=======================================================================
//:c0

//szv#4:S4163:12Mar99 was Boolean
 Standard_Integer& ShapeConstruct_ProjectCurveOnSurface::AdjustOverDegenMode()
 {
   return myAdjustOverDegen;
 }


//=======================================================================
//function : NbSurfIntervals
//purpose  : work-around of bug in standard method 
//           GeomAdaptor_Surface->NbIntervals() (PRO16346)
//=======================================================================

static Standard_Integer NbSurfIntervals(const Handle(GeomAdaptor_HSurface)& GAS, const GeomAbs_Shape cont)
{
  Standard_Integer NbU = 0;
  if (GAS->GetType() == GeomAbs_SurfaceOfExtrusion) {
    // extract the surface
    Handle(Geom_SurfaceOfLinearExtrusion) surf = Handle(Geom_SurfaceOfLinearExtrusion)::DownCast(GAS->ChangeSurface().Surface());
    // build a 3d adaptor curve
    GeomAdaptor_Curve Adaptor3dCurve(surf->BasisCurve(), GAS->FirstUParameter(), GAS->LastUParameter());
    if (Adaptor3dCurve.GetType() == GeomAbs_BSplineCurve)
      NbU = Adaptor3dCurve.NbIntervals(cont);
  }
  if (NbU == 0)
    NbU = GAS->NbUIntervals(cont);
  return NbU * (GAS->NbVIntervals(cont));
}

//=======================================================================
//function : Status
//purpose  : 
//=======================================================================

 Standard_Boolean ShapeConstruct_ProjectCurveOnSurface::Status (const ShapeExtend_Status Status) const
{
  return ShapeExtend::DecodeStatus (myStatus, Status);
}

//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================
Standard_Boolean ShapeConstruct_ProjectCurveOnSurface::Perform (Handle(Geom_Curve)& c3d,
                                                                const Standard_Real First,
                                                                const Standard_Real Last,
                                                                Handle(Geom2d_Curve)& c2d,
                                                                const GeomAbs_Shape,
                                                                const Standard_Integer,
                                                                const Standard_Integer)
{
  myStatus = ShapeExtend::EncodeStatus (ShapeExtend_OK);
  //Standard_Boolean OK = Standard_True; //szv#4:S4163:12Mar99 not needed
  
  if (mySurf.IsNull()) {
    c2d.Nullify();
    myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_FAIL1);
    return Standard_False;
  }
//  Projection Analytique
  Handle(Geom_Curve) crv3dtrim = c3d;
  if ( ! c3d->IsKind(STANDARD_TYPE(Geom_BoundedCurve)) )
    crv3dtrim = new Geom_TrimmedCurve ( c3d, First, Last );
  c2d = ProjectAnalytic ( crv3dtrim );
  if (!c2d.IsNull()) {
    myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_DONE1);
    return Standard_True;
  }

//  Projection par approximation

  // discretize the 3d curve

  Standard_Integer nbrPnt;
  
//   $$$$    :92 abv 28 Jan 98   see PRO10107, big BSplineCurve C0
  Standard_Integer nbPini = NCONTROL;  // as in BRepCheck_Edge (RLN/Nijni)
 // 20; // number of points for interpolation, should be "parametric dependent"

  //:92 abv 28 Jan 98: if curve is BSpline with many intervals,
  // increase number of points to provide at least Degree()+1 points per interval
  Handle(Geom_BSplineCurve) bspl;
  if ( c3d->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)) ) {
    Handle(Geom_TrimmedCurve) ctrim = Handle(Geom_TrimmedCurve)::DownCast(c3d);
    bspl = Handle(Geom_BSplineCurve)::DownCast ( ctrim->BasisCurve() );
  }
  else bspl = Handle(Geom_BSplineCurve)::DownCast ( c3d );
  if ( ! bspl.IsNull() ) {
    Standard_Integer nint = 0;
    for ( Standard_Integer i=1; i < bspl->NbKnots(); i++ )
      if ( bspl->Knot(i+1) > First && bspl->Knot(i) < Last ) nint++;
    Standard_Integer minPnt = nint * ( bspl->Degree() + 1 );
    while ( nbPini < minPnt ) nbPini += NCONTROL - 1;
#ifdef OCCT_DEBUG
    if ( nbPini > NCONTROL ) 
      cout << "Warning: number of points for projecting is " << nbPini << endl;
#endif
  }

//    $$$$    end :92 (big BSplineCurve C0)
  
  // this number should be "parametric dependent"
  TColgp_Array1OfPnt points(1, nbPini);
  TColStd_Array1OfReal params(1, nbPini);
  NCollection_Sequence<Standard_Real> aKnotCoeffs;
  gp_Pnt p3d;
  Standard_Integer iPnt;

  // In case of bspline compute parametrization speed on each 
  // knot interval inside [aFirstParam, aLastParam].
  // If quotient = (MaxSpeed / MinSpeed) >= aMaxQuotientCoeff then
  // use PerformByProjLib algorithm.
  if(!bspl.IsNull())
  {
    Standard_Integer aNbIntPnts = NCONTROL;
    Standard_Real aFirstParam = First; // First parameter of current interval.
    Standard_Real aLastParam = Last; // Last parameter of current interval.

    // First index computation.
    Standard_Integer anIdx = 1;
    for(; anIdx <= bspl->NbKnots() && aFirstParam < Last; anIdx++)
    {
      if(bspl->Knot(anIdx) > First)
      {
        break;
      }
    }

    for(; anIdx <= bspl->NbKnots() && aFirstParam < Last; anIdx++)
    {
      // Fill current knot interval.
      aLastParam = Min(Last, bspl->Knot(anIdx));
      Standard_Real aStep = (aLastParam - aFirstParam) / (aNbIntPnts - 1);
      Standard_Integer anIntIdx;
      gp_Pnt p3d1, p3d2;
      Standard_Real aLength3d = 0.0;
      for(anIntIdx = 0; anIntIdx < aNbIntPnts - 1; anIntIdx++)
      {
        // Start filling from first point.
        Standard_Real aParam1 = aFirstParam + aStep * anIntIdx;
        Standard_Real aParam2 = aFirstParam + aStep * (anIntIdx + 1);
        c3d->D0 (aParam1, p3d1);
        c3d->D0 (aParam2, p3d2);
        aLength3d += p3d2.Distance(p3d1);
      }
      aKnotCoeffs.Append(aLength3d / (aLastParam - aFirstParam));
      aFirstParam = aLastParam;
    }

    Standard_Real anEvenlyCoeff = 0;
    if (aKnotCoeffs.Size() > 0)
    {
      anEvenlyCoeff = *std::max_element(aKnotCoeffs.begin(), aKnotCoeffs.end()) / 
                      *std::min_element(aKnotCoeffs.begin(), aKnotCoeffs.end());
    }

    const Standard_Real aMaxQuotientCoeff = 1500.0;
    if (anEvenlyCoeff > aMaxQuotientCoeff)
    {
      PerformByProjLib(c3d, First, Last, c2d);
      // PerformByProjLib fail detection:
      if (!c2d.IsNull())
      {
        return Status (ShapeExtend_DONE);
      }
    }
  }

  Standard_Real deltaT, t;
  deltaT = (Last - First) / (nbPini-1);
  nbrPnt = nbPini;
  for (iPnt = 1; iPnt <= nbPini; iPnt ++)
  {
    if      (iPnt == 1)      t = First;
    else if (iPnt == nbPini) t = Last;
    else                     t = First + (iPnt - 1) * deltaT;

    c3d->D0 (t, p3d);
    points(iPnt) = p3d;
    params(iPnt) = t;
  }

  //  CALCUL par approximation
  TColgp_Array1OfPnt2d pnt2d(1, nbrPnt);
  ApproxPCurve (nbrPnt,points,params,pnt2d,c2d); //szv#4:S4163:12Mar99 OK not needed
  if (!c2d.IsNull()) {
    myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_DONE2);
    return Standard_True;
  }// cas particulier d iso

//  INTERPOLATION du resultat

  if ( myBuild ) {
    Handle(TColgp_HArray1OfPnt) thePnts = new TColgp_HArray1OfPnt  (1, nbPini);
    Handle(TColStd_HArray1OfReal) theParams = new TColStd_HArray1OfReal(1, nbPini);
    for (iPnt = 1; iPnt <= nbPini ; iPnt ++) {
      thePnts->SetValue(iPnt, points(iPnt));
      theParams->SetValue(iPnt, params(iPnt));
    }

    Handle(Geom_Curve) newc3d = InterpolateCurve3d (nbPini,thePnts,theParams, c3d);
    if ( newc3d.IsNull() ) myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_FAIL2);
    else {
      myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_DONE3);
      c3d = newc3d;
    }
  }

  Handle(TColgp_HArray1OfPnt2d) thePnts2d = new TColgp_HArray1OfPnt2d(1, nbPini);
  Handle(TColStd_HArray1OfReal) theParams2d = new TColStd_HArray1OfReal(1, nbPini);
  for (iPnt = 1; iPnt <= nbPini ; iPnt ++) {
    theParams2d->SetValue(iPnt, params(iPnt));
    thePnts2d->SetValue(iPnt, pnt2d(iPnt));
  }

  c2d = InterpolatePCurve (nbPini, thePnts2d, theParams2d, c3d);
//  c2d = ApproximatePCurve (nbPini, thePnts2d, theParams2d, c3d);
//  Faut-il aussi reprendre la C3D ?
  myStatus |= ShapeExtend::EncodeStatus (c2d.IsNull() ? ShapeExtend_FAIL1 : ShapeExtend_DONE2);
  return Status (ShapeExtend_DONE);
}

//=======================================================================
//function : PerformByProjLib
//purpose  : 
//=======================================================================

Standard_Boolean ShapeConstruct_ProjectCurveOnSurface::PerformByProjLib(Handle(Geom_Curve)& c3d,
									const Standard_Real First,
									const Standard_Real Last,
									Handle(Geom2d_Curve)& c2d,
									const GeomAbs_Shape /*continuity*/,
									const Standard_Integer /*maxdeg */,
									const Standard_Integer /*nbinterval */)
{
  //Standard_Boolean OK = Standard_True; //szv#4:S4163:12Mar99 unused
  c2d.Nullify();
  if (mySurf.IsNull()) {
    myStatus = ShapeExtend::EncodeStatus (ShapeExtend_FAIL1);
    return Standard_False;
  }
   
  try
  {
    OCC_CATCH_SIGNALS
    Handle(GeomAdaptor_HSurface) GAS = mySurf->Adaptor3d();
    Handle(GeomAdaptor_HCurve) GAC = new GeomAdaptor_HCurve (c3d,First,Last);
    ProjLib_ProjectedCurve Projector(GAS, GAC);

    switch (Projector.GetType())
    {
    case GeomAbs_Line : 
      c2d = new Geom2d_Line(Projector.Line()); 
      break;
    case GeomAbs_Circle : 
      c2d = new Geom2d_Circle(Projector.Circle());
      break;
    case GeomAbs_Ellipse :
      c2d = new Geom2d_Ellipse(Projector.Ellipse());
      break;
    case GeomAbs_Parabola : 
      c2d = new Geom2d_Parabola(Projector.Parabola()); 
      break;
    case GeomAbs_Hyperbola : 
      c2d = new Geom2d_Hyperbola(Projector.Hyperbola()); 
      break;
    case GeomAbs_BSplineCurve :
      c2d = Projector.BSpline();
      break;
    case GeomAbs_BezierCurve :
    case GeomAbs_OtherCurve :
      // Not possible, handling added to avoid gcc warning.
      break;
    }

    if(c2d.IsNull())
    {
      myStatus = ShapeExtend::EncodeStatus (ShapeExtend_FAIL2);
      return Standard_False;
    }
    else 
    {
      myStatus = ShapeExtend::EncodeStatus (ShapeExtend_DONE1);
      return Standard_True;
    }
    
  }
  catch(Standard_Failure)
  {
#ifdef OCCT_DEBUG
    cout << "Warning: ShapeConstruct_ProjectCurveOnSurface::PerformByProjLib(): Exception: ";
    Standard_Failure::Caught()->Print(cout); cout << endl;
#endif
    myStatus = ShapeExtend::EncodeStatus (ShapeExtend_FAIL3);
    c2d.Nullify();
  }
  return Standard_False;
}

//=======================================================================
//function : PerformAdvanced
//purpose  : 
//=======================================================================

Standard_Boolean ShapeConstruct_ProjectCurveOnSurface::PerformAdvanced (Handle(Geom_Curve)& c3d,
									const Standard_Real First,
									const Standard_Real Last,
									Handle(Geom2d_Curve)& c2d)
{
  Standard_Boolean hasResult = Standard_False;
  Standard_Integer nbintervals;
  
  Standard_Boolean isStandard = (mySurf->Adaptor3d()->GetType() != GeomAbs_Cylinder);
// &&   (mySurf->Adaptor3d()->GetType() != GeomAbs_SurfaceOfRevolution);

  if (isStandard) isStandard = !mySurf->HasSingularities(myPreci);
  if (isStandard) {
    Handle(GeomAdaptor_HSurface) GAS = mySurf->Adaptor3d();
    Handle(GeomAdaptor_HCurve) GAC = new GeomAdaptor_HCurve (c3d,First,Last);
    nbintervals = NbSurfIntervals(GAS, GeomAbs_C1);//+GAC->NbIntervals(GeomAbs_C3);
    isStandard = (nbintervals < 2);
  }
  if (isStandard) {
    hasResult = PerformByProjLib(c3d, First, Last, c2d);
  }
  if (!hasResult) hasResult = Perform (c3d, First, Last, c2d);
  return hasResult;
}

//=======================================================================
//function : ProjectAnalytic
//purpose  : 
//=======================================================================

 Handle(Geom2d_Curve) ShapeConstruct_ProjectCurveOnSurface::ProjectAnalytic(const Handle(Geom_Curve)& c3d) const
{
  Handle(Geom2d_Curve) result;

  //:k1 abv 16 Dec 98: limit analytic cases by Plane surfaces only
  // This is necessary for K4L since it fails on other surfaces
  // when general method GeomProjLib::Curve2d() is used
  // Projection is done as in BRep_Tool and BRepCheck_Edge
  Handle(Geom_Surface) surf = mySurf->Surface();
  Handle(Geom_Plane) Plane = Handle(Geom_Plane)::DownCast ( surf );
  if ( Plane.IsNull() ) {
    Handle(Geom_RectangularTrimmedSurface) RTS = 
      Handle(Geom_RectangularTrimmedSurface)::DownCast ( surf );
    if ( ! RTS.IsNull() ) Plane = Handle(Geom_Plane)::DownCast ( RTS->BasisSurface() );
    else {
      Handle(Geom_OffsetSurface) OS = 
	Handle(Geom_OffsetSurface)::DownCast ( surf );
      if ( ! OS.IsNull() ) 
	Plane = Handle(Geom_Plane)::DownCast ( OS->BasisSurface() );
    }
  }
  if ( ! Plane.IsNull() ) {
    Handle(Geom_Curve) ProjOnPlane = 
      GeomProjLib::ProjectOnPlane (c3d, Plane, 
				   Plane->Position().Direction(), Standard_True);
    Handle(GeomAdaptor_HCurve) HC = new GeomAdaptor_HCurve ( ProjOnPlane );
    ProjLib_ProjectedCurve Proj ( mySurf->Adaptor3d(), HC );

    result = Geom2dAdaptor::MakeCurve(Proj);
    if ( result.IsNull() ) return result;
    if ( result->IsKind(STANDARD_TYPE(Geom2d_TrimmedCurve)) ) {
      Handle(Geom2d_TrimmedCurve) TC = Handle(Geom2d_TrimmedCurve)::DownCast ( result );
      result = TC->BasisCurve();
    }

    return result;
  }
  
  return result;
}

 //! Fix possible period jump and handle walking period parameter.
 static Standard_Boolean fixPeriodictyTroubles(gp_Pnt2d *thePnt, // pointer to gp_Pnt2d[4] beginning
                                               Standard_Integer theIdx, // Index of objective coord: 1 ~ X, 2 ~ Y
                                               Standard_Real thePeriod) // Period on objective coord
 {
   Standard_Integer i;

   Standard_Boolean isNeedToFix = Standard_True;
   for (i = 0; i < 3; i++)
   {
     Standard_Real aDiff = Abs (thePnt[i].Coord(theIdx) - thePnt[i + 1].Coord(theIdx));
     if ( aDiff > Precision::PConfusion() && 
          aDiff < thePeriod - Precision::PConfusion())
     {
       // Walk over period coord -> not walking on another isoline in parameter space.
       isNeedToFix = Standard_False; 
     }
   }

   if (isNeedToFix)
   {
     // Walking on isoline on another parameter. Fix period paramter to obtained minimum.
     Standard_Real aFixParam = Min (thePnt[0].Coord(theIdx), thePnt[3].Coord(theIdx));
     for(i = 0; i < 4; i++)
       thePnt[i].SetCoord(theIdx, aFixParam);
   }

   // Fix possible period jump on first point.
   if ( Abs(thePnt[0].Coord(theIdx) - thePnt[1].Coord(theIdx) ) >  thePeriod / 2.01)
   {
     Standard_Real aMult = thePnt[0].Coord(theIdx) < thePnt[1].Coord(theIdx) ? 1.0 : -1.0;
     Standard_Real aNewParam = thePnt[0].Coord(theIdx) + aMult * thePeriod;
     thePnt[0].SetCoord(theIdx, aNewParam);
     return Standard_False;
   }

   // Fix possible period jump on last point.
   if ( Abs(thePnt[2].Coord(theIdx) - thePnt[3].Coord(theIdx) ) >  thePeriod / 2.01)
   {
     Standard_Real aMult = thePnt[3].Coord(theIdx) < thePnt[2].Coord(theIdx) ? 1.0 : -1.0;
     Standard_Real aNewParam = thePnt[3].Coord(theIdx) + aMult * thePeriod;
     thePnt[3].SetCoord(theIdx, aNewParam);
     return Standard_False;
   }

   return Standard_True;
 }

//=======================================================================
//function : getLine
//purpose  : 
//=======================================================================

 Handle(Geom2d_Curve) ShapeConstruct_ProjectCurveOnSurface::getLine(
   const TColgp_Array1OfPnt& thepoints,
   const TColStd_Array1OfReal& theparams,
   TColgp_Array1OfPnt2d& thePnt2ds,
   Standard_Real theTol,
   Standard_Boolean &isRecompute) const 
 {
   Standard_Integer nb =  thepoints.Length();
   gp_Pnt aP[4];
   aP[0] = thepoints(1);
   aP[1] = thepoints(2);
   aP[2] = thepoints(nb - 1);
   aP[3] = thepoints(nb);
   gp_Pnt2d aP2d[4];
   Standard_Integer i = 0;

   Standard_Real aTol2 = theTol * theTol;
   Standard_Boolean isPeriodicU = mySurf->Surface()->IsUPeriodic();
   Standard_Boolean isPeriodicV = mySurf->Surface()->IsVPeriodic();

   // Workaround:
   // Protection against bad "tolerance" shapes.
   if (aTol2 > 1.0)
   {
     theTol = Precision::Confusion();
     aTol2 = theTol * theTol;
   }
   Standard_Real anOldTol2 = aTol2;

   // project first and last points
   for( ; i < 4; i +=3)
   {
     Standard_Integer j;
     for ( j=0; j < myNbCashe; j++ ) 
       if ( myCashe3d[j].SquareDistance (aP[i] ) < aTol2)
       {
         aP2d[i] = mySurf->NextValueOfUV (myCashe2d[j], aP[i], theTol, 
           theTol);
         break;
       }
       if ( j >= myNbCashe )
         aP2d[i] = mySurf->ValueOfUV(aP[i], theTol);

       Standard_Real aDist = mySurf->Gap();
       Standard_Real aCurDist = aDist * aDist;
       if( aTol2 < aDist * aDist)
         aTol2 = aCurDist;
   }

   if ( isPeriodicU || isPeriodicV )
   {
     // Compute second and last but one c2d points.
     for(i = 1; i < 3; i++)
     {
       Standard_Integer j;
       for ( j=0; j < myNbCashe; j++ ) 
         if ( myCashe3d[j].SquareDistance (aP[i] ) < aTol2)
         {
           aP2d[i] = mySurf->NextValueOfUV (myCashe2d[j], aP[i], theTol, theTol);
           break;
         }
         if ( j >= myNbCashe )
           aP2d[i] = mySurf->ValueOfUV(aP[i], theTol);

         Standard_Real aDist = mySurf->Gap();
         Standard_Real aCurDist = aDist * aDist;
         if( aTol2 < aDist * aDist)
           aTol2 = aCurDist;
     }

     if (isPeriodicU)
     {
       isRecompute = fixPeriodictyTroubles(&aP2d[0], 1 /* X Coord */, mySurf->Surface()->UPeriod());
     }

     if (isPeriodicV)
     {
       isRecompute = fixPeriodictyTroubles(&aP2d[0], 2 /* Y Coord */, mySurf->Surface()->VPeriod());
     }
   }

   thePnt2ds.SetValue(1, aP2d[0]);
   thePnt2ds.SetValue(nb, aP2d[3]);

   // Restore old tolerance in 2d space to avoid big gap cases.
   aTol2 = anOldTol2;
   // Check that straight line in 2d with parameterisation as in 3d will fit 
   // fit 3d curve at all points.
   Standard_Real dPar = theparams(nb) - theparams(1);
   if ( Abs(dPar) < Precision::PConfusion() )
     return 0;
   gp_Vec2d aVec0 (aP2d[0], aP2d[3]);
   gp_Vec2d aVec = aVec0 / dPar;
   Standard_Real aFirstPointDist = mySurf->Surface()->Value(aP2d[0].X(), aP2d[0].Y()). 
                                   SquareDistance(thepoints(1));
   for(i = 2; i <  nb; i++)
   {
     gp_XY aCurPoint = aP2d[0].XY() + aVec.XY() * (theparams(i) - theparams(1));
     gp_Pnt aCurP;
     mySurf->Surface()->D0(aCurPoint.X(), aCurPoint.Y(), aCurP);
     Standard_Real aDist1 = aCurP.SquareDistance(thepoints(i));

     if(Abs (aFirstPointDist - aDist1) > aTol2)
       return 0;
   }

   // check if pcurve can be represented by Geom2d_Line (parameterised by length)
   Standard_Real aLLength = aVec0.Magnitude();
   if ( Abs (aLLength - dPar) <= Precision::PConfusion() )
   {
     gp_XY aDirL = aVec0.XY() / aLLength;
     gp_Pnt2d aPL (aP2d[0].XY() - theparams(1) * aDirL);
     return new Geom2d_Line (aPL, gp_Dir2d(aDirL));
   }

   // create straight bspline
   TColgp_Array1OfPnt2d aPoles(1, 2);
   aPoles(1) = aP2d[0];
   aPoles(2) = aP2d[3];

   TColStd_Array1OfReal aKnots(1,2);
   aKnots(1) = theparams(1);
   aKnots(2) = theparams(theparams.Length());

   TColStd_Array1OfInteger aMults(1,2);
   aMults(1) = 2;
   aMults(2) = 2;
   Standard_Integer aDegree = 1;
   Handle(Geom2d_BSplineCurve) abspl2d =
     new Geom2d_BSplineCurve (aPoles, aKnots, aMults, aDegree);
   return abspl2d;
 }

//=======================================================================
//function : ApproxPCurve
//purpose  : 
//=======================================================================

  Standard_Boolean ShapeConstruct_ProjectCurveOnSurface::ApproxPCurve(const Standard_Integer nbrPnt,
								     const TColgp_Array1OfPnt& points,
								     const TColStd_Array1OfReal& params,
								     TColgp_Array1OfPnt2d& pnt2d,
								     Handle(Geom2d_Curve)& c2d) 
{
  // for performance, first try to handle typical case when pcurve is straight
  Standard_Boolean isRecompute = Standard_False;
  c2d = getLine(points, params, pnt2d, myPreci, isRecompute);
  if(!c2d.IsNull())
  {
    return Standard_True;
  }
    Standard_Boolean isDone = Standard_True;
  // test if the curve 3d is a boundary of the surface 
  // (only for Bezier or BSpline surface)
  
  Standard_Boolean isoParam, isoPar2d3d, isoTypeU, p1OnIso, p2OnIso, isoclosed;
  gp_Pnt2d valueP1, valueP2;
  Handle(Geom_Curve) cIso;
  Standard_Real t1, t2;
  
  Handle(Standard_Type) sType = mySurf->Surface()->DynamicType();
  Standard_Boolean isAnalytic = Standard_True;
  if (sType == STANDARD_TYPE(Geom_BezierSurface) || sType == STANDARD_TYPE(Geom_BSplineSurface)) isAnalytic = Standard_False; 
  Standard_Real uf, ul, vf, vl;
  mySurf->Surface()->Bounds(uf, ul, vf, vl);
  isoclosed = Standard_False;
  TColStd_Array1OfReal pout(1, nbrPnt);
  
  isoParam = IsAnIsoparametric(nbrPnt, points, params, 
			       isoTypeU, p1OnIso, valueP1, p2OnIso, valueP2,
			       isoPar2d3d, cIso, t1, t2, pout);
  
  // projection of the points on surfaces
  
  gp_Pnt p3d;
  gp_Pnt2d p2d;
  Standard_Integer i;
  Standard_Real isoValue=0., isoPar1=0., isoPar2=0., tPar=0., tdeb,tfin;
  Standard_Real Cf, Cl, parf, parl; //szv#4:S4163:12Mar99 dist not needed
  
  //  Le calcul part-il dans le bon sens, c-a-d deb et fin dans le bon ordre ?
  //  Si uclosed et iso en V, attention isoPar1 ET/OU 2 peut toucher la fermeture
  if(isoParam){
    if(isoTypeU){
      isoValue = valueP1.X();
      isoPar1 = valueP1.Y();
      isoPar2 = valueP2.Y();
      isoclosed = mySurf->IsVClosed(myPreci);//#78 rln 12.03.99 S4135
      parf = vf;  parl = vl;
    }
    else { 
      isoValue = valueP1.Y();
      isoPar1 = valueP1.X();
      isoPar2 = valueP2.X();
      isoclosed = mySurf->IsUClosed(myPreci);//#78 rln 12.03.99 S4135
      parf = uf;  parl = ul;
    }
    if (!isoPar2d3d && !isAnalytic) {
      Cf = cIso->FirstParameter();
      Cl = cIso->LastParameter();
      if (Precision::IsInfinite(Cf))	Cf = -1000;
      if (Precision::IsInfinite(Cl))	Cl = +1000;
      //pdn S4030 optimizing and fix isopar case on PRO41323
      tdeb = pout(2);
      //    dist = ShapeAnalysis_Curve().Project (cIso,points(2),myPreci,pt,tdeb,Cf,Cl);
      //  Chacun des par1 ou par2 est-il sur un bord. Attention first/last : recaler
      if (isoclosed && (isoPar1 == parf || isoPar1 == parl)) {
	if (Abs(tdeb-parf) < Abs(tdeb-parl)) isoPar1 = parf;
	else isoPar1 = parl;
	if (isoTypeU) valueP1.SetY (isoPar1);
	else          valueP1.SetX (isoPar1);
      }
      if (isoclosed && (isoPar2 == parf || isoPar2 == parl)) {
	//pdn S4030 optimizing and fix isopar case on PRO41323
	tfin = pout(nbrPnt-1);
	//dist =  ShapeAnalysis_Curve().Project (cIso,points(nbrPnt-1),myPreci,pt,tfin,Cf,Cl);
	if (Abs(tfin-parf) < Abs(tfin-parl)) isoPar2 = parf;
	else isoPar2 = parl;
	if (isoTypeU) valueP2.SetY (isoPar2);
	else          valueP2.SetX (isoPar2);
      }
      
      //  Interversion Par1/Par2 (ne veut que si les 2 sont sur les bords ...)
      //  Est-ce encore necessaire apres ce qui vient d etre fait ?
      
      // PTV 05.02.02 fix for translation face from 12_hp_mouse (PARASOLID) face 24008
      // if curve is periodic do not change the points
      // skl change "if" for pout(nbrPnt-1) 19.11.2003
      if (!isoclosed) {
        if( (Abs(tdeb-isoPar1)>Abs(tdeb-isoPar2)) &&
            (Abs(pout(nbrPnt-1)-isoPar2)>Abs(pout(nbrPnt-1)-isoPar1)) ) {
          gp_Pnt2d valueTmp = valueP1;
          valueP1 = valueP2;  valueP2 = valueTmp;
          if (isoTypeU) {
            isoValue = valueP1.X();
            isoPar1 = valueP1.Y();
            isoPar2 = valueP2.Y();
          }
          else { 
            isoValue = valueP1.Y();
            isoPar1 = valueP1.X();
            isoPar2 = valueP2.X();
          }
          //  Fin calcul sens de courbe iso
        }
      } // end of fix check 05.02.02
    }
  }
  
  //  Si pas isoParam, on a quand meme du p1OnIso/p2OnIso possible ... !!!
  //  (utile pour detromper bug de projection). Mais detromper aussi circularite
  //else {
    //if (p1OnIso) valueP1 =
    //BestExtremum (valueP1,points(1),points(2));
    //if (p2OnIso) valueP2 =
    //BestExtremum (valueP2,points(nbrPnt),points(nbrPnt-1));
    //}
  
  Standard_Real gap = myPreci; //:q1
  Standard_Boolean ChangeCycle = Standard_False; //skl for OCC3430
  if( myNbCashe>0 && myCashe3d[0].Distance(points(1))>myCashe3d[0].Distance(points(nbrPnt)) )
    //if(myCashe3d[0].Distance(points(nbrPnt))<myPreci)
    if(myCashe3d[0].Distance(points(nbrPnt))<Precision::Confusion())
      ChangeCycle = Standard_True;
  //for( i = 1; i <= nbrPnt; i ++) {
  for(Standard_Integer ii=1; ii<=nbrPnt; ii++) {
    if(ChangeCycle) //skl for OCC3430
      i=nbrPnt-ii+1;
    else
      i=ii;
    p3d = points(i);
    if (isoParam) {
      
      if (isoPar2d3d) {
	if (isoPar2 > isoPar1) tPar = params(i);
	else                   tPar = t1 + t2 - params(i);
      } else if (!isAnalytic) {
	// projection to iso
	if      (i==1)      tPar = isoPar1;
	else if (i==nbrPnt) tPar = isoPar2;
	else {
	  tPar = pout(i);
	  //:S4030  ShapeAnalysis_Curve().Project (cIso,p3d,myPreci,pt,tPar,Cf,Cl); //szv#4:S4163:12Mar99 `dist=` not needed
	}
      }
      
      if (!isoPar2d3d && isAnalytic) {
	if      (i == 1)      p2d = valueP1;
	else if (i == nbrPnt) p2d = valueP2;
        else {
	  p2d = mySurf->NextValueOfUV(p2d,p3d, myPreci, //%12 pdn 15.02.99 optimizing
				      Precision::Confusion()+1000*gap); //:q1
	  gap = mySurf->Gap();
	}
      } else {
	if(isoTypeU)  {  p2d.SetX(isoValue);  p2d.SetY(tPar);     }
	else          {  p2d.SetX(tPar);      p2d.SetY(isoValue); }
      }
    }
    
    else {
      if     ( (i == 1)      && p1OnIso)  p2d = valueP1;
      else if( (i == nbrPnt) && p2OnIso)  p2d = valueP2;
      else  {// general case (not an iso)  mais attention aux singularites !
        // first and last points are already computed by getLine()
        if ( (i == 1 || i == nbrPnt))
        {
          if (!isRecompute)
          {
            p2d = pnt2d(i);
            gap = mySurf->Gap();
            continue;
          }
          else
          {
            //:q9 abv 23 Mar 99: use cashe as 1st approach
            Standard_Integer j; // svv #1
            for ( j=0; j < myNbCashe; j++ ) 
              if ( myCashe3d[j].SquareDistance ( p3d ) < myPreci*myPreci )
              {
                p2d = mySurf->NextValueOfUV (myCashe2d[j], p3d, myPreci, 
                  Precision::Confusion()+gap);
                break;
              }
              if ( j >= myNbCashe ) p2d = mySurf->ValueOfUV(p3d, myPreci);
          }
        }
        else {
          p2d = mySurf->NextValueOfUV (p2d, p3d, myPreci, //:S4030: optimizing
                                       Precision::Confusion()+1000*gap); //:q1
        }
	gap = mySurf->Gap();
      }
    }
    pnt2d (i) = p2d;
    if ( ii > 1 ) {
      if(ChangeCycle)
        p2d.SetXY ( 2. * p2d.XY() - pnt2d(i+1).XY() );
      else
        p2d.SetXY ( 2. * p2d.XY() - pnt2d(i-1).XY() );
    }
  }

  //pdn %12 11.02.99 PRO9234 entity 15402
  if (!isoPar2d3d) {
    mySurf->ProjectDegenerated(nbrPnt,points,pnt2d,myPreci,Standard_True);
    mySurf->ProjectDegenerated(nbrPnt,points,pnt2d,myPreci,Standard_False);
  }
  
  //  attention aux singularites ... (hors cas iso qui les traite deja)
  //  if (!isoParam) {
    //    p2d = pnt2d (1);
    //    if (mySurf->ProjectDegenerated (points(1),myPreci,pnt2d (2),p2d))
    //      pnt2d (1) = p2d;
    //    p2d = pnt2d (nbrPnt);
    //    if (mySurf->ProjectDegenerated (points(nbrPnt),myPreci,pnt2d (nbrPnt-1),p2d))
    //      pnt2d (nbrPnt) = p2d;
    //  }
  
  // Si la surface est UCLosed et VClosed, on recadre les points
  // algo un peu complique, on retarde l implementation
  Standard_Real Up = ul - uf;
  Standard_Real Vp = vl - vf;
  Standard_Real dist2d;
#ifdef OCCT_DEBUG
  if (mySurf->IsUClosed(myPreci) && mySurf->IsVClosed(myPreci)) {//#78 rln 12.03.99 S4135
    cout << "WARNING : Recadrage incertain sur U & VClosed" << endl;
  }
#endif
  // Si la surface est UCLosed, on recadre les points
  if (mySurf->IsUClosed(myPreci)) {//#78 rln 12.03.99 S4135
    // Premier point dans le domain [uf, ul]
    Standard_Real prevX, firstX = pnt2d (1).X();
    while (firstX < uf)  {  firstX += Up;   pnt2d (1).SetX(firstX);  }
    while (firstX > ul)  {  firstX -= Up;   pnt2d (1).SetX(firstX);  }
    prevX = firstX;
    
    //:97 abv 1 Feb 98: treat case when curve is whole out of surface bounds
    Standard_Real minX = firstX, maxX = firstX;
    
    // On decalle toujours le suivant
    for (i = 2; i <= nbrPnt; i++) {
      //      dist2d = pnt2d (i-1).Distance(pnt2d (i));
      Standard_Real CurX = pnt2d (i).X();
      dist2d = Abs (CurX - prevX);
      if (dist2d > ( Up / 2) ) {
	if        (CurX > prevX + Up/2) {
	  while (CurX > prevX + Up/2) {  CurX -= Up;  pnt2d (i).SetX (CurX);  }
	} else if (CurX < prevX - Up/2) {
	  while (CurX < prevX - Up/2) {  CurX += Up;  pnt2d (i).SetX (CurX);  }
	}
	
      }
      prevX = CurX;
      if ( minX > CurX ) minX = CurX;      //:97
      else if ( maxX < CurX ) maxX = CurX; //:97
    }
    
    //:97
    Standard_Real midX = 0.5 * ( minX + maxX );
    Standard_Real shiftX=0.;
    if ( midX > ul ) shiftX = -Up;
    else if ( midX < uf ) shiftX = Up;
    if ( shiftX != 0. ) 
      for ( i=1; i <= nbrPnt; i++ ) pnt2d(i).SetX ( pnt2d(i).X() + shiftX );
  }
  // Si la surface est VCLosed, on recadre les points
  // Same code as UClosed : optimisation souhaitable !!
  // CKY : d abord un code IDENTIQUE A UClosed; PUIS le special Seam ...
  // Si la surface est UCLosed, on recadre les points
  //
  //#69 rln 01.03.99 S4135 bm2_sd_t4-A.stp entity 30
  //#78 rln 12.03.99 S4135
  if (mySurf->IsVClosed(myPreci) || mySurf->Surface()->IsKind (STANDARD_TYPE (Geom_SphericalSurface))) {
    // Premier point dans le domain [vf, vl]
    Standard_Real prevY, firstY = pnt2d (1).Y();
    while (firstY < vf)  {  firstY += Vp;  pnt2d (1).SetY(firstY);  }
    while (firstY > vl)  {  firstY -= Vp;  pnt2d (1).SetY(firstY);  }
    prevY = firstY;
    
    //:97 abv 1 Feb 98: treat case when curve is whole out of surface bounds
    Standard_Real minY = firstY, maxY = firstY;
    
    // On decalle toujours le suivant
    for (i = 2; i <= nbrPnt; i ++) {
      //      dist2d = pnt2d (i-1).Distance(pnt2d (i));
      Standard_Real CurY = pnt2d (i).Y();
      dist2d = Abs (CurY - prevY);
      if (dist2d > ( Vp / 2) ) {
	if        (CurY > prevY + Vp/2) {
	  while (CurY > prevY + Vp/2) {  CurY -= Vp;  pnt2d (i).SetY (CurY);  }
	} else if (CurY < prevY - Vp/2) {
	  while (CurY < prevY - Vp/2) {  CurY += Vp;  pnt2d (i).SetY (CurY);  }
	}
      }
      prevY = CurY;
      if ( minY > CurY ) minY = CurY;      //:97
      else if ( maxY < CurY ) maxY = CurY; //:97
    }
    
    //:97
    Standard_Real midY = 0.5 * ( minY + maxY );
    Standard_Real shiftY=0.;
    if ( midY > vl ) shiftY = -Vp;
    else if ( midY < vf ) shiftY = Vp;
    if ( shiftY != 0. ) 
      for ( i=1; i <= nbrPnt; i++ ) pnt2d(i).SetY ( pnt2d(i).Y() + shiftY );
  }
  
  //#69 rln 01.03.99 S4135 bm2_sd_t4-A.stp entity 30
  //#78 rln 12.03.99 S4135
  if (mySurf->IsVClosed(myPreci) || mySurf->Surface()->IsKind (STANDARD_TYPE (Geom_SphericalSurface))) {
    for (i = 2; i <= nbrPnt; i++) {
      //#1 rln 11/02/98 ca_exhaust.stp entity #9869 dist2d = pnt2d (i-1).Distance(pnt2d (i));
      dist2d = Abs (pnt2d(i).Y() - pnt2d(i - 1).Y());
      if (dist2d > ( Vp / 2) ) {
	// ATTENTION : il faut regarder ou le decalage se fait.
	// si plusieurs points sont decalles, il faut plusieurs passes
	// pour obtenir un resultat correct.
	// NOT YET IMPLEMENTED
	
	// one of those point is incorrectly placed
	// i.e on the wrong side of the "seam"
	// on prend le point le plus pres des bords vf ou vl
	Standard_Boolean prevOnFirst = Standard_False;
	Standard_Boolean prevOnLast  = Standard_False;
	Standard_Boolean currOnFirst = Standard_False;
	Standard_Boolean currOnLast  = Standard_False;
	
	//  .X ?  plutot .Y ,  non ?
	Standard_Real distPrevVF = Abs(pnt2d (i-1).Y() - vf);
	Standard_Real distPrevVL = Abs(pnt2d (i-1).Y() - vl);
	Standard_Real distCurrVF = Abs(pnt2d (i).Y() - vf);
	Standard_Real distCurrVL = Abs(pnt2d (i).Y() - vl);
	
	Standard_Real theMin = distPrevVF;
	prevOnFirst = Standard_True;
	if (distPrevVL < theMin) {
	  theMin = distPrevVL;
	  prevOnFirst = Standard_False;
	  prevOnLast  = Standard_True;
	}
	if (distCurrVF < theMin) {
	  theMin = distCurrVF;
	  prevOnFirst = Standard_False;
	  prevOnLast  = Standard_False;
	  currOnFirst = Standard_True;
	}
	if (distCurrVL < theMin) {
	  theMin = distCurrVL;
	  prevOnFirst = Standard_False;
	  prevOnLast  = Standard_False;
	  currOnFirst = Standard_False;
	  currOnLast  = Standard_True;
	}
	//  Modifs RLN/Nijni  3-DEC-1997
	if (prevOnFirst) {
	  // on decalle le point (i-1) en V Last
	  gp_Pnt2d newPrev(pnt2d (i-1).X(), vf); // instead of  vl RLN/Nijni
	  pnt2d (i-1) = newPrev;
	}
	else if (prevOnLast) {
	  // on decalle le point (i-1) en V first
	  gp_Pnt2d newPrev(pnt2d (i-1).X(), vl); // instead of  vf RLN/Nijni
	  pnt2d (i-1) = newPrev;
	}
	else if (currOnFirst) {
	  // on decalle le point (i) en V Last
	  gp_Pnt2d newCurr(pnt2d (i).X(),vf);  // instead of vl  RLN/Nijni
	  pnt2d (i) = newCurr;
	}
	else if (currOnLast) {
	  // on decalle le point (i) en V First
	  gp_Pnt2d newCurr(pnt2d (i).X(), vl); // instead of vf  RLN/Nijni
	  pnt2d (i) = newCurr;
	}
	// on verifie
#ifdef OCCT_DEBUG
	dist2d = pnt2d (i-1).Distance(pnt2d (i));
	if (dist2d > ( Vp / 2) ) {
	  cout << "Echec dans le recadrage" << endl;
	}
#endif
      }
    }
  }
  
  //:c0 abv 20 Feb 98: treat very special case when 3d curve
  // go over the pole of, e.g., sphere, and partly lies along seam.
  // 2d representation of such a curve should consist of 3 parts - one on
  // regular part of surface (interior), one part along degenerated boundary
  // and one along seam.
  // Since it cannot be adjusted later by arranging pcurves (curve is single),
  // to fix it it is nesessary to have a possibility of adjusting seam
  // part of such curve either to left or right boundary of surface.
  // Test is performed only if flag AdjustOverDegen is not -1.
  // If AdjustOverDegen is True, seam part of curve is adjusted to
  // the left, and if False - to the right parametric boundary 
  // If treated case is detected, flag DONE4 is set to status
  // NOTE: currently, precision is Precision::PConfusion() since it 
  // is enough on encountered example
  // (ug_turbine-A.stp from ProSTEP Benchmark #3, entities ##2470 & 5680)
  // (r1001_ac.stp from Test Rally #10, face #35027 and others)
  if ( myAdjustOverDegen != -1 ) {
    if ( mySurf->IsUClosed(myPreci) ) {//#78 rln 12.03.99 S4135
      mySurf->IsDegenerated ( gp_Pnt(0,0,0), myPreci );  // pour calculer les dgnr
      if ( mySurf->NbSingularities(myPreci) > 0 ) { //rln S4135
	// 1st, find gap point (degenerated pole)
	Standard_Real PrevX=0.;
	Standard_Integer OnBound=0, PrevOnBound=0;
	Standard_Integer ind; // svv #1
	Standard_Boolean start = Standard_True;
	for ( ind=1; ind <= nbrPnt; ind++ ) {
	  Standard_Real CurX = pnt2d(ind).X();
	  // abv 16 Mar 00: trj3_s1-ug.stp #697: ignore points in singularity
	  if ( mySurf->IsDegenerated ( points(ind), Precision::Confusion() ) )
	    continue;
	  OnBound = ( Abs ( Abs ( CurX - 0.5 * ( ul + uf ) ) - Up/2 ) <=
		     Precision::PConfusion() );
	  if ( ! start &&  Abs ( Abs ( CurX - PrevX ) - Up/2 ) <= 0.01*Up ) 
	    break;
	  start = Standard_False;
	  PrevX = CurX;
	  PrevOnBound = OnBound;
	}
        // if found, adjust seam part
        if ( ind <= nbrPnt ) {
	  PrevX = ( myAdjustOverDegen ? uf : ul );
	  Standard_Real dU = Up/2 + Precision::PConfusion();
	  if ( PrevOnBound ) {
	    pnt2d(ind-1).SetX ( PrevX );
	    for ( Standard_Integer j=ind-2; j >0; j-- ) {
	      Standard_Real CurX = pnt2d(j).X();
	      while ( CurX < PrevX - dU ) pnt2d(j).SetX ( CurX += Up );
	      while ( CurX > PrevX + dU ) pnt2d(j).SetX ( CurX -= Up );
	    }
	  }
	  else if ( OnBound ) {
	    pnt2d(ind).SetX ( PrevX );
	    for ( Standard_Integer j=ind+1; j <= nbrPnt; j++ ) {
	      Standard_Real CurX = pnt2d(j).X();
	      while ( CurX < PrevX - dU ) pnt2d(j).SetX ( CurX += Up );
	      while ( CurX > PrevX + dU ) pnt2d(j).SetX ( CurX -= Up );
	    }
	  }
	  myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_DONE4);
	}
      }
    }
    else if ( mySurf->IsVClosed(myPreci) ) {//#78 rln 12.03.99 S4135
      mySurf->IsDegenerated ( gp_Pnt(0,0,0), myPreci );  // pour calculer les dgnr
      if ( mySurf->NbSingularities(myPreci) > 0 ) { //rln S4135
	// 1st, find gap point (degenerated pole)
	Standard_Real PrevY=0.;
	Standard_Integer OnBound=0, PrevOnBound=0;
	Standard_Integer ind; // svv #1
	Standard_Boolean start = Standard_True;
	for ( ind=1; ind <= nbrPnt; ind++ ) {
	  Standard_Real CurY = pnt2d(ind).Y();
	  // abv 16 Mar 00: trj3_s1-ug.stp #697: ignore points in singularity
	  if ( mySurf->IsDegenerated ( points(ind), Precision::Confusion() ) )
	    continue;
	  OnBound = ( Abs ( Abs ( CurY - 0.5 * ( vl + vf ) ) - Vp/2 ) <=
		     Precision::PConfusion() );
	  if ( ! start &&  Abs ( Abs ( CurY - PrevY ) - Vp/2 ) <= 0.01*Vp ) 
	    break;
	  start = Standard_False;
	  PrevY = CurY;
	  PrevOnBound = OnBound;
	}
        // if found, adjust seam part
        if ( ind <= nbrPnt ) {
	  PrevY = ( myAdjustOverDegen ? vf : vl );
	  Standard_Real dV = Vp/2 + Precision::PConfusion();
	  if ( PrevOnBound ) {
	    pnt2d(ind-1).SetY ( PrevY );
	    for ( Standard_Integer j=ind-2; j >0; j-- ) {
	      Standard_Real CurY = pnt2d(j).Y();
	      while ( CurY < PrevY - dV ) pnt2d(j).SetY ( CurY += Vp );
	      while ( CurY > PrevY + dV ) pnt2d(j).SetY ( CurY -= Vp );
	    }
	  }
	  else if ( OnBound ) {
	    pnt2d(ind).SetY ( PrevY );
	    for ( Standard_Integer j=ind+1; j <= nbrPnt; j++ ) {
	      Standard_Real CurY = pnt2d(j).Y();
	      while ( CurY < PrevY - dV ) pnt2d(j).SetY ( CurY += Vp );
	      while ( CurY > PrevY + dV ) pnt2d(j).SetY ( CurY -= Vp );
	    }
	  }
	  myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_DONE4);
	}
      }
    }
  }

  //:q9: fill cashe
  myNbCashe = 2;
  if(ChangeCycle) {  // msv 10.08.04: avoid using of uninitialised field
  //if(myCashe3d[0].Distance(points(1))>Precision::Confusion() &&
  //   myCashe3d[1].Distance(points(1))>Precision::Confusion()) {
    myCashe3d[0] = points(1);
    myCashe3d[1] = points(nbrPnt);
    myCashe2d[0] = pnt2d(1);
    myCashe2d[1] = pnt2d(nbrPnt);
  }
  else {
    myCashe3d[1] = points(1);
    myCashe3d[0] = points(nbrPnt);
    myCashe2d[1] = pnt2d(1);
    myCashe2d[0] = pnt2d(nbrPnt);
  }
  return isDone;
}

//=======================================================================
//function : ApproximatePCurve
//purpose  : 
//=======================================================================

Handle(Geom2d_Curve) ShapeConstruct_ProjectCurveOnSurface::ApproximatePCurve(const Standard_Integer /*nbrPnt*/,
									     Handle(TColgp_HArray1OfPnt2d)& points2d, 
									     Handle(TColStd_HArray1OfReal)& params,
									     const Handle(Geom_Curve)& /*orig*/) const
{
//  Standard_Real resol = Min(mySurf->Adaptor3d()->VResolution(myPreci), mySurf->Adaptor3d()->UResolution(myPreci));
  Standard_Real theTolerance2d = myPreci; // (100*nbrPnt);//resol;
  Handle(Geom2d_Curve) C2d;
  try {
    OCC_CATCH_SIGNALS
    CheckPoints2d (points2d, params, theTolerance2d);
    Standard_Integer numberPnt = points2d->Length();
    
    TColgp_Array1OfPnt points3d(1,numberPnt);
    gp_Pnt2d pnt2d;
    gp_Pnt pnt;
    Standard_Integer i; // svv #1 
    for( i = 1; i <= numberPnt; i++) {
      pnt2d = points2d->Value(i);
      pnt.SetCoord(pnt2d.X(),pnt2d.Y(),0);
      points3d(i) = pnt;
    }
    
    GeomAPI_PointsToBSpline appr(points3d, params->Array1(), 1, 10, GeomAbs_C1, theTolerance2d);
    Handle(Geom_BSplineCurve) crv3d = appr.Curve();
    Standard_Integer NbPoles = crv3d->NbPoles();
    TColgp_Array1OfPnt poles3d (1, NbPoles);
    TColgp_Array1OfPnt2d poles2d (1, NbPoles);
    crv3d->Poles(poles3d);
    for( i = 1; i <= NbPoles; i++) {
      pnt2d.SetCoord(poles3d(i).X(),poles3d(i).Y());
      poles2d(i) = pnt2d;
    }
    TColStd_Array1OfReal weights (1,NbPoles);
    TColStd_Array1OfInteger multiplicities (1,crv3d->NbKnots());
    TColStd_Array1OfReal knots(1,crv3d->NbKnots());
    crv3d->Knots(knots);
    crv3d->Weights(weights);
    crv3d->Multiplicities(multiplicities);
    C2d = new Geom2d_BSplineCurve  ( poles2d, weights, knots, multiplicities, crv3d->Degree(), crv3d->IsPeriodic());
    return C2d;
  }
  catch(Standard_Failure) {
#ifdef OCCT_DEBUG //:s5
    //    debug ...
    Standard_Integer nbp = params->Length();
    Standard_Integer nb2 = points2d->Length();
    cout << "Warning: ShapeConstruct_ProjectCurveOnSurface::ApproximatePCurve(): Exception: ";
    Standard_Failure::Caught()->Print(cout); 
    cout<<"Pb Geom2dAPI_Approximate, tol2d="<<theTolerance2d<<" NbParams="<<nbp<<" NbPnts="<<nb2<<endl;
//     if (nb2 > nbp) nb2 = nbp;
//     Standard_Real rbp,rb2; rbp = nbp; rb2 = nb2;
//     //    dbl.AddString ("NbP2d/NbParams puis  X Y Param -> mini");
//     dbl.AddReals (rb2,rbp);
//     for (Standard_Integer i = 1; i <= nb2; i ++) {
//       gp_XYZ quoi (points2d->Value(i).X(),points2d->Value(i).Y(),params->Value(i) );
//       dbl.AddXYZ (quoi);
//     }
#endif
     C2d.Nullify();
  }
  return C2d;
}  

//=======================================================================
//function : InterpolatePCurve
//purpose  : 
//=======================================================================

 Handle(Geom2d_Curve) ShapeConstruct_ProjectCurveOnSurface::InterpolatePCurve(const Standard_Integer nbrPnt,
									      Handle(TColgp_HArray1OfPnt2d)& points2d, 
									      Handle(TColStd_HArray1OfReal)& params,
									      const Handle(Geom_Curve)& /*orig*/) const
{
  Handle(Geom2d_Curve) C2d;    // NULL si echec
  Standard_Real theTolerance2d = myPreci / (100 * nbrPnt);
  try {
    OCC_CATCH_SIGNALS
    // on verifie d abord s il n y a pas de points confondus
    // si besoin on retouche les valeurs ...
    CheckPoints2d (points2d, params, theTolerance2d);
    Geom2dAPI_Interpolate myInterPol2d (points2d, params, 
					Standard_False, theTolerance2d);
    myInterPol2d.Perform();
    if (myInterPol2d.IsDone()) C2d = myInterPol2d.Curve();
  }
  catch(Standard_Failure) {
#ifdef OCCT_DEBUG //:s5
// //    debug ...
    Standard_Integer nbp = params->Length();
    Standard_Integer nb2 = points2d->Length();
    cout << "Warning: ShapeConstruct_ProjectCurveOnSurface::InterpolatePCurve(): Exception: ";
    Standard_Failure::Caught()->Print(cout); 
    cout<<"Pb Geom2dAPI_Interpolate, tol2d="<<theTolerance2d<<" NbParams="<<nbp<<" NbPnts="<<nb2<<endl;
//     if (nb2 > nbp) nb2 = nbp;
//     Standard_Real rbp,rb2; rbp = nbp; rb2 = nb2;
// //    dbl.AddString ("NbP2d/NbParams puis  X Y Param -> mini");
//     dbl.AddReals (rb2,rbp);
//     for (Standard_Integer i = 1; i <= nb2; i ++) {
//       gp_XYZ quoi (points2d->Value(i).X(),points2d->Value(i).Y(),params->Value(i) );
//       dbl.AddXYZ (quoi);
//     }
#endif
    C2d.Nullify();
  }
  return C2d;
}

//=======================================================================
//function : InterpolateCurve3d
//purpose  : 
//=======================================================================

Handle(Geom_Curve) ShapeConstruct_ProjectCurveOnSurface::InterpolateCurve3d(const Standard_Integer,
									    Handle(TColgp_HArray1OfPnt)& points, 
									    Handle(TColStd_HArray1OfReal)& params,
									    const Handle(Geom_Curve)& /*orig*/) const
{
  Handle(Geom_Curve) C3d;    // NULL si echec
  try {
    OCC_CATCH_SIGNALS
    Standard_Real Tol = myPreci;
    CheckPoints(points, params, Tol);
    GeomAPI_Interpolate myInterPol(points, params, Standard_False, Tol);
    myInterPol.Perform();
    if (myInterPol.IsDone()) C3d = myInterPol.Curve();
  }
  catch(Standard_Failure) {
    C3d.Nullify();
#ifdef OCCT_DEBUG //:s5
    cout << "Warning: ShapeConstruct_ProjectCurveOnSurface::InterpolateCurve3d(): Exception: ";
    Standard_Failure::Caught()->Print(cout); cout << endl;
#endif
  }
  return C3d;
}

//=======================================================================
//function : CheckPoints
//purpose  : 
//=======================================================================

 void ShapeConstruct_ProjectCurveOnSurface::CheckPoints(Handle(TColgp_HArray1OfPnt)& points,Handle(TColStd_HArray1OfReal)& params,Standard_Real& preci) const
{
  Standard_Integer firstElem = points->Lower();
  Standard_Integer lastElem  = points->Upper();
  Standard_Integer i;
  Standard_Integer nbPntDropped = 0;
  Standard_Integer lastValid = firstElem; // indice of last undropped point

  // will store 0 when the point is to be removed, 1 otherwise
  TColStd_Array1OfInteger tmpParam(firstElem, lastElem);
  for (i = firstElem; i<=lastElem ; i++) tmpParam.SetValue(i,1);
  Standard_Real DistMin2 = RealLast();
  gp_Pnt Prev = points->Value (lastValid);
  gp_Pnt Curr;
  for (i = firstElem + 1; i <= lastElem ; i ++) {
    Curr = points->Value(i);
    Standard_Real CurDist2 = Prev.SquareDistance(Curr);
    if (CurDist2 < gp::Resolution()) {  // test 0
      nbPntDropped ++;
      if ( i == lastElem ) tmpParam.SetValue(lastValid, 0); // last point kept
      else tmpParam.SetValue(i, 0);    // current dropped, lastValid unchanged
    } else {
      if (CurDist2 < DistMin2) 
        DistMin2 = CurDist2;
      // lastValid becomes the current (i.e. i)
      lastValid = i;
      Prev = Curr;
    }
  }
  if (DistMin2 < RealLast())
    preci = 0.9 * Sqrt (DistMin2); // preci est la distance min entre les points on la reduit un peu
  if (nbPntDropped == 0)
    return;

#ifdef OCCT_DEBUG
  cout << "Warning : removing 3d points for interpolation" << endl;
#endif
  // Build new HArrays
  Standard_Integer newLast = lastElem - nbPntDropped;
  if ((newLast - firstElem + 1)  < 2) {
#ifdef OCCT_DEBUG
    cout << "Too many degenerated points for 3D interpolation" << endl;
#endif
    return;
  }
  Handle(TColgp_HArray1OfPnt) newPnts = 
    new TColgp_HArray1OfPnt(firstElem, newLast);
  Handle(TColStd_HArray1OfReal) newParams =
    new TColStd_HArray1OfReal(firstElem, newLast);
  Standard_Integer newCurr = 1;
  for (i = firstElem; i<= lastElem ; i++) {
    if (tmpParam.Value(i) == 1) { 
      newPnts->SetValue(newCurr, points->Value(i));
      newParams->SetValue(newCurr, params->Value(i));
      newCurr ++;
    }
  }
  points = newPnts;
  params = newParams;
  // on la reduit un peu
}

//=======================================================================
//function : CheckPoints2d
//purpose  : 
//=======================================================================

 void ShapeConstruct_ProjectCurveOnSurface::CheckPoints2d(Handle(TColgp_HArray1OfPnt2d)& points,
							  Handle(TColStd_HArray1OfReal)& params,
							  Standard_Real& preci) const
{
  Standard_Integer firstElem = points->Lower();
  Standard_Integer lastElem  = points->Upper();
  Standard_Integer i;
  Standard_Integer nbPntDropped = 0;
  Standard_Integer lastValid = firstElem; // indice of last undropped point

  // will store 0 when the point is to be removed, 1 otherwise
  TColStd_Array1OfInteger tmpParam(firstElem, lastElem);
  for (i = firstElem; i<=lastElem ; i++) {
    tmpParam.SetValue(i,1);
  }
  Standard_Real DistMin2 = RealLast();
  gp_Pnt2d Prev = points->Value(lastValid);
  gp_Pnt2d Curr;
  for (i = firstElem + 1; i<=lastElem ; i++) {
    Curr = points->Value(i);
    Standard_Real CurDist2 = Prev.SquareDistance(Curr);
    if (CurDist2 < gp::Resolution()) {  // test 0
      nbPntDropped ++;
      if ( i == lastElem ) tmpParam.SetValue(lastValid, 0); // last point kept
      else tmpParam.SetValue(i, 0);    // current dropped, lastValid unchanged
    } else {
      if (CurDist2 < DistMin2) 
        DistMin2 = CurDist2;
      // lastValid becomes the current (i.e. i)
      lastValid = i;
      Prev = Curr;
    }
  }
  if (DistMin2 < RealLast())
    preci = 0.9 * Sqrt (DistMin2);
  if (nbPntDropped == 0)
    return;

#ifdef OCCT_DEBUG
  cout << "Warning : removing 2d points for interpolation" << endl;
#endif
  // Build new HArrays
  Standard_Integer newLast = lastElem - nbPntDropped;
  if ((newLast - firstElem + 1)  < 2) {
#ifdef OCCT_DEBUG
    cout << "Too many degenerated points for 2D interpolation" << endl;
#endif
    //pdn 12.02.99 S4135 Creating pcurve with minimal length.
    tmpParam.SetValue(firstElem,1);
    tmpParam.SetValue(lastElem,1);
    gp_XY  lastPnt = points->Value(lastElem).XY();
    lastPnt.Add(gp_XY(preci,preci));
    points->SetValue(lastElem,lastPnt);
    newLast = firstElem+1;
    //return;
  }
  Handle(TColgp_HArray1OfPnt2d) newPnts = 
    new TColgp_HArray1OfPnt2d(firstElem, newLast);
  Handle(TColStd_HArray1OfReal) newParams =
    new TColStd_HArray1OfReal(firstElem, newLast);
  Standard_Integer newCurr = 1;
  for (i = firstElem; i <= lastElem ; i++) {
    if (tmpParam.Value(i) == 1) { 
#ifdef OCCT_DEBUG
      cout << "Point " << i << " : " << points->Value(i).X() << " " << points->Value(i).Y() << " at param " <<  params->Value(i) << endl;
#endif
      newPnts->SetValue(newCurr, points->Value(i));
      newParams->SetValue(newCurr, params->Value(i));
      newCurr ++;
    }
    else {
#ifdef OCCT_DEBUG
      cout << "Removed " << i << " : " << points->Value(i).X() << " " << points->Value(i).Y() << " at param " <<  params->Value(i) << endl;
#endif
    }
  }
  points = newPnts;
  params = newParams;
}

//=======================================================================
//function : IsAnIsoparametric
//purpose  : 
//=======================================================================
//:S4030: modified for optimization
//:p9 abv 11 Mar 99: PRO7226 #489490: find nearest boundary instead of first one

 Standard_Boolean ShapeConstruct_ProjectCurveOnSurface::IsAnIsoparametric(const Standard_Integer nbrPnt,
									  const TColgp_Array1OfPnt& points,
									  const TColStd_Array1OfReal& params,
									  Standard_Boolean& isoTypeU,
									  Standard_Boolean& p1OnIso,
									  gp_Pnt2d& valueP1,
									  Standard_Boolean& p2OnIso,
									  gp_Pnt2d& valueP2,
									  Standard_Boolean& isoPar2d3d,
									  Handle(Geom_Curve)& cIso,
									  Standard_Real& t1,
									  Standard_Real& t2,
									  TColStd_Array1OfReal& pout) const
{
  try {    // RAJOUT
    OCC_CATCH_SIGNALS
    
  Standard_Real prec = Precision::Confusion();//myPreci;
    
  Standard_Boolean isoParam = Standard_False;
  isoPar2d3d = Standard_False;
  
  Standard_Real U1, U2, V1, V2;
  mySurf->Bounds(U1, U2, V1, V2);
  
  if ( mySurf->Surface()->IsKind(STANDARD_TYPE(Geom_RectangularTrimmedSurface))) {
    Handle(Geom_RectangularTrimmedSurface) sTrim =
      Handle(Geom_RectangularTrimmedSurface)::DownCast(mySurf->Surface());
    sTrim->Bounds(U1, U2, V1, V2);
  }
  
  gp_Pnt pt;
  Standard_Integer mpt[2]; mpt[0] = mpt[1] = 0;
  Standard_Real t, tpar[2] = { 0.0, 0.0 }, isoValue=0.;
  Standard_Real mindist2;
  Standard_Real mind2[2];
  mindist2 = mind2[0] = mind2[1] = 4*prec*prec;
  
  p1OnIso = Standard_False;
  p2OnIso = Standard_False;
  const Bnd_Box* aBox = 0;
  
  for (Standard_Integer j=1; (j<=4) /*&& !isoParam*/; j++) {
    Standard_Real isoVal=0.;
    Standard_Boolean isoU=Standard_False; //szv#4:S4163:12Mar99 `isoU` must be Standard_Boolean
    Handle(Geom_Curve) cI;
    Standard_Real tt1, tt2;
    
    if      (j == 1 ) {
      if (Precision::IsInfinite(U1)) continue;
      cI = mySurf->UIso(U1);
      isoU = Standard_True;
      isoVal = U1;
      aBox = & mySurf->GetBoxUF();
    }
    else if (j == 2) {
      if (Precision::IsInfinite(U2)) continue;
      cI = mySurf->UIso(U2);
      isoU = Standard_True;
      isoVal = U2;
      aBox = & mySurf->GetBoxUL();
    }
    else if (j == 3) {
      if (Precision::IsInfinite(V1)) continue;
      cI = mySurf->VIso(V1);
      isoU = Standard_False;
      isoVal = V1;
      aBox = & mySurf->GetBoxVF();
    }
    else if (j == 4) {
      if (Precision::IsInfinite(V2)) continue;
      cI = mySurf->VIso(V2);
      isoU = Standard_False;
      isoVal = V2;
      aBox = & mySurf->GetBoxVL();
    }
    if(cI.IsNull())
      continue;
    
    if (isoU)  {  tt1 = V1;  tt2 = V2;  }
    else       {  tt1 = U1;  tt2 = U2;  }

    gp_Pnt ext1, ext2;
    cI->D0(tt1, ext1);
    cI->D0(tt2, ext2);

// PATCH CKY 9-JUL-1998 : protection contre singularite
    gp_Pnt extmi;
    cI->D0( (tt1+tt2)/2,extmi);
    if (ext1.IsEqual(ext2,prec) && ext1.IsEqual(extmi,prec)) continue;

    Standard_Boolean PtEQext1 = Standard_False;
    Standard_Boolean PtEQext2 = Standard_False;

    Standard_Real currd2[2], tp[2] = {0, 0};
    Standard_Integer mp[2];
    
    for (Standard_Integer i=0; i<2; i++) {
      mp[i] = 0;
      Standard_Integer k = (i == 0 ? 1 : nbrPnt);

      // si ext1 == ext2 => valueP1 == valueP2 => vect null plus tard
      currd2[i] = points(k).SquareDistance ( ext1 );
      if ( currd2[i] <= prec*prec && !PtEQext1) {
        mp[i] = 1;
        tp[i] = tt1;
	PtEQext1 = Standard_True;
	continue;
      } 
      
      currd2[i] = points(k).SquareDistance ( ext2 );
      if ( currd2[i] <= prec*prec && !PtEQext2) {
        mp[i] = 2;
        tp[i] = tt2;
	PtEQext2 = Standard_True;
	continue;
      }  
      
      // On evite de projecter sur un iso degenere
      // on doit egalement le faire pour l apex du cone
      if (mySurf->Surface()->IsKind(STANDARD_TYPE(Geom_SphericalSurface)) && !isoU) {
	continue;
      }
      
      if(aBox->IsOut(points(k))) continue;
      
      Standard_Real Cf = cI->FirstParameter();
      Standard_Real Cl = cI->LastParameter();
      if (Precision::IsInfinite(Cf))  Cf = -1000;
      if (Precision::IsInfinite(Cl))  Cl = +1000;

      ShapeAnalysis_Curve sac;
      Standard_Real dist = sac.Project (cI,points(k),prec,pt,t,Cf,Cl);
      currd2[i] = dist * dist;
      if ((dist <= prec) && (t>= Cf) && (t<=Cl)) {
	mp[i]  = 3;
	tp[i] = t;
      }
    }

    //:e7 abv 21 Apr 98: ProSTEP TR8, r0501_pe #56679:
    // avoid possible null-length curves
    if ( mp[0] >0 && mp[1] >0 &&
	 Abs ( tp[0] - tp[1] ) < Precision::PConfusion() ) continue;
    
    
    if (mp[0] > 0 && 
	( ! p1OnIso || currd2[0] < mind2[0] ) ) {
      p1OnIso = Standard_True;
      mind2[0] = currd2[0]; // LP2.stp #105899: FLT_INVALID_OPERATION on Windows 7 VC 9 Release mode on the whole file 
      if (isoU) valueP1.SetCoord(isoVal, tp[0]);
      else      valueP1.SetCoord(tp[0], isoVal);
    }

    if (mp[1] > 0 &&
	( ! p2OnIso || currd2[1] < mind2[1] ) ) {
      p2OnIso = Standard_True;
      mind2[1] = currd2[1];
      if (isoU) valueP2.SetCoord(isoVal, tp[1]);
      else      valueP2.SetCoord(tp[1], isoVal);
    }

    if ( mp[0] <=0 || mp[1] <=0 ) continue;

    Standard_Real md2 = currd2[0] + currd2[1];
    if ( mindist2 <= md2 ) continue;
    
    mindist2 = md2;
    mpt[0] = mp[0];
    mpt[1] = mp[1];
    tpar[0] = tp[0];
    tpar[1] = tp[1];
    isoTypeU = isoU;
    isoValue = isoVal;
    cIso = cI;
    t1 = tt1;
    t2 = tt2;
  }
    
  // probablely it concerns an isoparametrics
  if ( mpt[0] >0 && mpt[1] >0 ) {

    p1OnIso = p2OnIso = Standard_True;
    if (isoTypeU) {
      valueP1.SetCoord(isoValue, tpar[0]);
      valueP2.SetCoord(isoValue, tpar[1]);
    }
    else {
      valueP1.SetCoord(tpar[0], isoValue);
      valueP2.SetCoord(tpar[1], isoValue);
    }

    if ( mpt[0] != 3 && mpt[1] != 3 ) {
      isoPar2d3d = Standard_True;
      for (Standard_Integer i=2; i < nbrPnt && isoPar2d3d; i++){
	if (tpar[1] > tpar[0])  t = params(i);
	else                    t = t1+t2-params(i);
	cIso->D0(t, pt);
	if (!points(i).IsEqual(pt, prec)) isoPar2d3d = Standard_False;
      }
    }

    if (isoPar2d3d) isoParam = Standard_True;
    else {
      Standard_Real prevParam = tpar[0];
      Standard_Real Cf, Cl;
      Standard_Boolean isoByDistance = Standard_True;
      Cf = cIso->FirstParameter();
      Cl = cIso->LastParameter();
      if (Precision::IsInfinite(Cf))  Cf = -1000;
      if (Precision::IsInfinite(Cl))  Cl = +1000;
	
      ShapeAnalysis_Curve sac;
      for (Standard_Integer i=2; i < nbrPnt && isoByDistance; i++) {
	Standard_Real dist = sac.NextProject (prevParam,cIso,points(i),
					      prec,pt,t,Cf,Cl,
					      Standard_False); //:j8 abv 10.12.98: TR10 r0501_db.stp #9423: avoid adjusting to ends
	prevParam = t;
	pout(i)=t;
	if( (dist > prec) || (t < Cf) || (t > Cl) ) 
	  isoByDistance = Standard_False;
      }
      if (isoByDistance) isoParam = Standard_True;
    }
  }
/*  if (!isoParam) {    CKY 29-mai-1997 : garder tout ce qu on peut ?
    p1OnIso = Standard_False;
    p2OnIso = Standard_False;
  }  */
  return isoParam;
  }  // RAJOUT
  catch(Standard_Failure) {
//  pb : on affiche ce qu on peut
#ifdef OCCT_DEBUG
    for (Standard_Integer numpnt = 1; numpnt <= nbrPnt; numpnt ++) {
      cout<<"["<<numpnt<<"]param="<<params(numpnt)<<" point=("<<
	points(numpnt).X()<<"  "<<points(numpnt).Y()<<"  "<<points(numpnt).Z()<<")"<<endl;
    }
#endif
#ifdef OCCT_DEBUG //:s5
    cout << "Warning: ShapeConstruct_ProjectCurveOnSurface::IsAnIsoparametric(): Exception: ";
    Standard_Failure::Caught()->Print(cout); cout << endl;
#endif
    return Standard_False;
  }
}

/* S4135 : BestExtremum is commented after IsAnIsoparametric works with Precision::Confusion()
//=======================================================================
//function : BestExtremum
//purpose  : auxiliaire prenant le meilleur extremum si ISO car doute possible
//=======================================================================

 gp_Pnt2d ShapeConstruct_ProjectCurveOnSurface::BestExtremum(const gp_Pnt2d& P2iso,const gp_Pnt& P3ext,const gp_Pnt& P3next) const
{
//  P2iso a ete calcule depuis P3ext sur une iso externe de la surface
//  En principe bon mais circularite possible ... et IsU/VClosed faillible
//    (si baillement 1e-4 ou 1e-5, on est dedans !). DONC
//  1/ on privilegie l iso mais a tout hasard on verifie si Surf meilleur
//  2/ si iso, attention a la circularite (cas limite)

//  NB : si isoParam, on suppose que P2iso est bon (car il y en a 2). A voir...

//  D abord, calcul p2ext depuis la surface. choix surface/iso
  return P2iso;
  Standard_Real prec = Precision::Confusion();//myPreci;
  gp_Pnt2d P2cal = mySurf->ValueOfUV(P3ext, prec);
  gp_Pnt   P3cal = mySurf->Value (P2cal);
  Standard_Real dcal = P3ext.Distance (P3cal);
  Standard_Real dnxt = P3ext.Distance (P3next);
  if (dcal > dnxt) return P2iso;    // en fait protection sur BUG (PRO8468)

//  On choisit entre P2iso et P2cal, le plus proche de P2next ... !!!
  gp_Pnt2d P2next = mySurf->ValueOfUV(P3next, prec);
  if (P2next.Distance(P2cal) < P2next.Distance(P2iso)) return P2cal;
  return P2iso;
}
*/
