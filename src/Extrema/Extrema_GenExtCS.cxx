// Created on: 1995-07-18
// Created by: Modelistation
// Copyright (c) 1995-1999 Matra Datavision
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

#include <Extrema_GenExtCS.ixx>

#include <Adaptor3d_HCurve.hxx>
#include <Extrema_ExtCC.hxx>
#include <Extrema_ExtPS.hxx>
#include <Extrema_GlobOptFuncCS.hxx>
#include <Extrema_POnCurv.hxx>
#include <Geom_Line.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <math_FunctionSetRoot.hxx>
#include <math_PSO.hxx>
#include <math_PSOParticlesPool.hxx>
#include <math_Vector.hxx>
#include <Precision.hxx>
#include <TColgp_HArray1OfPnt.hxx>

const Standard_Real aMaxParamVal = 1.0e+10;
const Standard_Real aBorderDivisor = 1.0e+4;

//=======================================================================
//function : Extrema_GenExtCS
//purpose  : 
//=======================================================================
Extrema_GenExtCS::Extrema_GenExtCS()
{
  myDone = Standard_False;
  myInit = Standard_False;
}

//=======================================================================
//function : Extrema_GenExtCS
//purpose  : 
//=======================================================================
Extrema_GenExtCS::Extrema_GenExtCS(const Adaptor3d_Curve& C,
                                   const Adaptor3d_Surface& S,
                                   const Standard_Integer NbT,
                                   const Standard_Integer NbU,
                                   const Standard_Integer NbV,
                                   const Standard_Real Tol1,
                                   const Standard_Real Tol2)
{
  Initialize(S, NbU, NbV, Tol2);
  Perform(C, NbT, Tol1);
}

//=======================================================================
//function : Extrema_GenExtCS
//purpose  : 
//=======================================================================

Extrema_GenExtCS::Extrema_GenExtCS (const Adaptor3d_Curve& C,
                                    const Adaptor3d_Surface& S,
                                    const Standard_Integer NbT,
                                    const Standard_Integer NbU,
                                    const Standard_Integer NbV,
                                    const Standard_Real tmin,
                                    const Standard_Real tsup,
                                    const Standard_Real Umin,
                                    const Standard_Real Usup,
                                    const Standard_Real Vmin,
                                    const Standard_Real Vsup,
                                    const Standard_Real Tol1,
                                    const Standard_Real Tol2)
{
  Initialize(S, NbU, NbV, Umin,Usup,Vmin,Vsup,Tol2);
  Perform(C, NbT, tmin, tsup, Tol1);
}

//=======================================================================
//function : Initialize
//purpose  : 
//=======================================================================
void Extrema_GenExtCS::Initialize (const Adaptor3d_Surface& S,
                                   const Standard_Integer NbU,
                                   const Standard_Integer NbV,
                                   const Standard_Real Tol2)
{
  myumin = S.FirstUParameter();
  myusup = S.LastUParameter();
  myvmin = S.FirstVParameter();
  myvsup = S.LastVParameter();
  Initialize(S,NbU,NbV,myumin,myusup,myvmin,myvsup,Tol2);
}

//=======================================================================
//function : Initialize
//purpose  : 
//=======================================================================
void Extrema_GenExtCS::Initialize (const Adaptor3d_Surface& S,
                                   const Standard_Integer NbU,
                                   const Standard_Integer NbV,
                                   const Standard_Real Umin,
                                   const Standard_Real Usup,
                                   const Standard_Real Vmin,
                                   const Standard_Real Vsup,
                                   const Standard_Real Tol2)
{
  myS = (Adaptor3d_SurfacePtr)&S;
  myusample = NbU;
  myvsample = NbV;
  myumin = Umin;
  myusup = Usup;
  myvmin = Vmin;
  myvsup = Vsup;
  mytol2 = Tol2;

  const Standard_Real aTrimMaxU = Precision::IsInfinite (myusup) ?  aMaxParamVal : myusup;
  const Standard_Real aTrimMinU = Precision::IsInfinite (myumin) ? -aMaxParamVal : myumin;
  const Standard_Real aTrimMaxV = Precision::IsInfinite (myvsup) ?  aMaxParamVal : myvsup;
  const Standard_Real aTrimMinV = Precision::IsInfinite (myvmin) ? -aMaxParamVal : myvmin;

  const Standard_Real aMinU = aTrimMinU + (aTrimMaxU - aTrimMinU) / aBorderDivisor;
  const Standard_Real aMinV = aTrimMinV + (aTrimMaxV - aTrimMinV) / aBorderDivisor;
  const Standard_Real aMaxU = aTrimMaxU - (aTrimMaxU - aTrimMinU) / aBorderDivisor;
  const Standard_Real aMaxV = aTrimMaxV - (aTrimMaxV - aTrimMinV) / aBorderDivisor;
  
  const Standard_Real aStepSU = (aMaxU - aMinU) / myusample;
  const Standard_Real aStepSV = (aMaxV - aMinV) / myvsample;

  mySurfPnts = new TColgp_HArray2OfPnt (0, myusample, 0, myvsample);

  Standard_Real aSU = aMinU;
  for (Standard_Integer aSUI = 0; aSUI <= myusample; aSUI++, aSU += aStepSU)
  {
    Standard_Real aSV = aMinV;
    for (Standard_Integer aSVI = 0; aSVI <= myvsample; aSVI++, aSV += aStepSV)
    {
      mySurfPnts->ChangeValue (aSUI, aSVI) = myS->Value (aSU, aSV);
    }
  }
}

//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================
void Extrema_GenExtCS::Perform(const Adaptor3d_Curve& C, 
  const Standard_Integer NbT,
  const Standard_Real Tol1)
{
  mytmin = C.FirstParameter();
  mytsup = C.LastParameter();
  Perform(C, NbT, mytmin, mytsup,Tol1);
}

//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================
void Extrema_GenExtCS::Perform (const Adaptor3d_Curve& C,
                                const Standard_Integer NbT,
                                const Standard_Real tmin,
                                const Standard_Real tsup,
                                const Standard_Real Tol1)
{
  myDone = Standard_False;
  myF.Initialize(C,*myS);
  mytmin = tmin;
  mytsup = tsup;
  mytol1 = Tol1;
  mytsample = NbT;
  // Modif de lvt pour trimer la surface non pas aux infinis mais  a +/- 10000

  Standard_Real trimusup = myusup, trimumin = myumin,trimvsup = myvsup,trimvmin = myvmin;
  if (Precision::IsInfinite(trimusup)){
    trimusup = aMaxParamVal;
  }
  if (Precision::IsInfinite(trimvsup)){
    trimvsup = aMaxParamVal;
  }
  if (Precision::IsInfinite(trimumin)){
    trimumin = -aMaxParamVal;
  }
  if (Precision::IsInfinite(trimvmin)){
    trimvmin = -aMaxParamVal;
  }
  //
  math_Vector Tol(1, 3);
  Tol(1) = mytol1;
  Tol(2) = mytol2;
  Tol(3) = mytol2;
  math_Vector TUV(1,3), TUVinf(1,3), TUVsup(1,3);
  TUVinf(1) = mytmin;
  TUVinf(2) = trimumin;
  TUVinf(3) = trimvmin;

  TUVsup(1) = mytsup;
  TUVsup(2) = trimusup;
  TUVsup(3) = trimvsup;

  // Number of particles used in PSO algorithm (particle swarm optimization).
  const Standard_Integer aNbParticles = 32;

  math_PSOParticlesPool aParticles(aNbParticles, 3);

  math_Vector aMinTUV(1,3);
  aMinTUV = TUVinf + (TUVsup - TUVinf) / aBorderDivisor;

  math_Vector aMaxTUV(1,3); 
  aMaxTUV = TUVsup - (TUVsup - TUVinf) / aBorderDivisor;

  Standard_Real aStepCU = (aMaxTUV(1) - aMinTUV(1)) / mytsample;
  Standard_Real aStepSU = (aMaxTUV(2) - aMinTUV(2)) / myusample;
  Standard_Real aStepSV = (aMaxTUV(3) - aMinTUV(3)) / myvsample;

  // Correct number of curve samples in case of low resolution
  Standard_Real aScaleFactor = 5.0;
  Standard_Real aResolutionCU = aStepCU / C.Resolution (1.0);

  Standard_Real aMinResolution = aScaleFactor * Min (aResolutionCU,
    Min (aStepSU / myS->UResolution (1.0), aStepSV / myS->VResolution (1.0)));

  if (aMinResolution > Epsilon (1.0))
  {
    if (aResolutionCU > aMinResolution)
    {
      const Standard_Integer aMaxNbNodes = 50;

      mytsample = Min(aMaxNbNodes,
        RealToInt(mytsample * aResolutionCU / aMinResolution));

      aStepCU = (aMaxTUV(1) - aMinTUV(1)) / mytsample;
    }
  }

  // Pre-compute curve sample points.
  TColgp_HArray1OfPnt aCurvPnts (0, mytsample);

  Standard_Real aCU = aMinTUV(1);
  for (Standard_Integer aCUI = 0; aCUI <= mytsample; aCUI++, aCU += aStepCU)
    aCurvPnts.SetValue (aCUI, C.Value (aCU));

  PSO_Particle* aParticle = aParticles.GetWorstParticle();
  // Select specified number of particles from pre-computed set of samples
  Standard_Real aSU = aMinTUV(2);
  for (Standard_Integer aSUI = 0; aSUI <= myusample; aSUI++, aSU += aStepSU)
  {
    Standard_Real aSV = aMinTUV(3);
    for (Standard_Integer aSVI = 0; aSVI <= myvsample; aSVI++, aSV += aStepSV)
    {
      Standard_Real aCU = aMinTUV(1);
      for (Standard_Integer aCUI = 0; aCUI <= mytsample; aCUI++, aCU += aStepCU)
      {
        Standard_Real aSqDist = mySurfPnts->Value(aSUI, aSVI).SquareDistance(aCurvPnts.Value(aCUI)); 

        if (aSqDist < aParticle->Distance)
        {
          aParticle->Position[0] = aCU;
          aParticle->Position[1] = aSU;
          aParticle->Position[2] = aSV;

          aParticle->BestPosition[0] = aCU;
          aParticle->BestPosition[1] = aSU;
          aParticle->BestPosition[2] = aSV;

          aParticle->Distance     = aSqDist;
          aParticle->BestDistance = aSqDist;

          aParticle = aParticles.GetWorstParticle();
        }
      }
    }
  }

  math_Vector aStep(1,3);
  aStep(1) = aStepCU;
  aStep(2) = aStepSU;
  aStep(3) = aStepSV;

  // Find min approximation
  Standard_Real aValue;
  Extrema_GlobOptFuncCS aFunc(&C, myS);
  math_PSO aPSO(&aFunc, TUVinf, TUVsup, aStep);
  aPSO.Perform(aParticles, aNbParticles, aValue, TUV);

  math_FunctionSetRoot anA(myF, Tol);
  anA.Perform(myF, TUV, TUVinf, TUVsup);

  myDone = Standard_True;
}

//=======================================================================
//function : IsDone
//purpose  : 
//=======================================================================
Standard_Boolean Extrema_GenExtCS::IsDone() const 
{
  return myDone;
}

//=======================================================================
//function : NbExt
//purpose  : 
//=======================================================================
Standard_Integer Extrema_GenExtCS::NbExt() const 
{
  if (!IsDone()) { StdFail_NotDone::Raise(); }
  return myF.NbExt();
}

//=======================================================================
//function : Value
//purpose  : 
//=======================================================================
Standard_Real Extrema_GenExtCS::SquareDistance(const Standard_Integer N) const 
{
  if (!IsDone()) { StdFail_NotDone::Raise(); }
  return myF.SquareDistance(N);
}

//=======================================================================
//function : PointOnCurve
//purpose  : 
//=======================================================================
const Extrema_POnCurv& Extrema_GenExtCS::PointOnCurve(const Standard_Integer N) const 
{
  if (!IsDone()) { StdFail_NotDone::Raise(); }
  return myF.PointOnCurve(N);
}

//=======================================================================
//function : PointOnSurface
//purpose  : 
//=======================================================================
const Extrema_POnSurf& Extrema_GenExtCS::PointOnSurface(const Standard_Integer N) const 
{
  if (!IsDone()) { StdFail_NotDone::Raise(); }
  return myF.PointOnSurface(N);
}

//=======================================================================
//function : BidonSurface
//purpose  : 
//=======================================================================
Adaptor3d_SurfacePtr Extrema_GenExtCS::BidonSurface() const 
{
  return (Adaptor3d_SurfacePtr)0L;
}

//=======================================================================
//function : BidonCurve
//purpose  : 
//=======================================================================
Adaptor3d_CurvePtr Extrema_GenExtCS::BidonCurve() const 
{
  return (Adaptor3d_CurvePtr)0L;
}

