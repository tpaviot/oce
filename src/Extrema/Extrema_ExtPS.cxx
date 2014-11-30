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

//-----------------------------------------------------------------

#include <Extrema_ExtPS.ixx>
#include <Extrema_GenExtPS.hxx>
#include <StdFail_NotDone.hxx>
#include <Standard_NotImplemented.hxx>
#include <Precision.hxx>
#include <GeomAbs_CurveType.hxx>
#include <Adaptor3d_SurfaceOfLinearExtrusion.hxx>
#include <Adaptor3d_SurfaceOfRevolution.hxx>
#include <ElCLib.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pln.hxx>
#include <gp_Cylinder.hxx>
#include <gp_Cone.hxx>
#include <gp_Sphere.hxx>
#include <gp_Torus.hxx>
#include <Extrema_ExtPExtS.hxx>
#include <Extrema_ExtPRevS.hxx>
#include <Extrema_POnSurf.hxx>
#include <GeomAbs_IsoType.hxx>

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
      if( !Precision::IsInfinite(U1) &&  !Precision::IsInfinite(U2) )
      {
        Step = (U2 - U1)/10;
        if(Step < Precision::PConfusion()) {
          return Standard_False;
        }
        D1NormMax=0.;

        for (T=U1;T<=U2;T=T+Step) 
        {
          S.D1(T,Param,P,D1U,D1V);
          D1NormMax=Max(D1NormMax,D1U.Magnitude());
        }

        if (D1NormMax >TolMax || D1NormMax < TolMin ) 
          Along = Standard_False;
      }
    }
    else 
    {
      if( !Precision::IsInfinite(V1) &&  !Precision::IsInfinite(V2) )
      {
        Step = (V2 - V1)/10;
        if(Step < Precision::PConfusion()) {
          return Standard_False;
        }
        D1NormMax=0.;
        for (T=V1;T<=V2;T=T+Step) 
        {
          S.D1(Param,T,P,D1U,D1V);
          D1NormMax=Max(D1NormMax,D1V.Magnitude());
        }

        if (D1NormMax >TolMax || D1NormMax < TolMin ) 
          Along = Standard_False;
      }



    }
    return Along;
}

//=======================================================================
//function : TreatSolution
//purpose  : 
//=======================================================================

void Extrema_ExtPS::TreatSolution (const Extrema_POnSurf& PS,
				   const Standard_Real Val)
{
  Standard_Real U, V;
  PS.Parameter(U, V);
  if (myS->IsUPeriodic()) {
    Standard_Real Uupper = myuinf+myS->UPeriod();
    if(U>(myuinf-mytolu) && U < myuinf) U = myuinf;
    else if(U < (Uupper+mytolu) && U > Uupper) U = Uupper;
    else
      U = ElCLib::InPeriod(U, myuinf, myuinf+myS->UPeriod());
  }
  if (myS->IsVPeriodic()) {
    Standard_Real Vupper = myvinf+myS->VPeriod();
    if(V>(myvinf-mytolv) && V < myvinf) V = myvinf;
    else if(V < (Vupper+mytolv) && V > Vupper) V = Vupper;
    else
      V = ElCLib::InPeriod(V, myvinf, myvinf+myS->VPeriod());
  }
  if ((myuinf-U) <= mytolu && (U-myusup) <= mytolu &&
      (myvinf-V) <= mytolv && (V-myvsup) <= mytolv) {
    myPoints.Append(Extrema_POnSurf (U, V, PS.Value()));
    mySqDist.Append(Val);
  }
}


//=======================================================================
//function : Extrema_ExtPS
//purpose  : 
//=======================================================================

Extrema_ExtPS::Extrema_ExtPS() 
{
  myDone = Standard_False;
}


//=======================================================================
//function : Extrema_ExtPS
//purpose  : 
//=======================================================================

Extrema_ExtPS::Extrema_ExtPS(const gp_Pnt&          P,
			     const Adaptor3d_Surface& S,
			     const Standard_Real    TolU,
			     const Standard_Real    TolV,
           const Extrema_ExtFlag F,
           const Extrema_ExtAlgo A)

{
  myExtPS.SetFlag(F);
  myExtPS.SetAlgo(A);
  Initialize(S, S.FirstUParameter(), S.LastUParameter(), 
	        S.FirstVParameter(), S.LastVParameter(), 
	        TolU, TolV);
  Perform(P);
}

//=======================================================================
//function : Extrema_ExtPS
//purpose  : 
//=======================================================================

Extrema_ExtPS::Extrema_ExtPS(const gp_Pnt&          P,
			     const Adaptor3d_Surface& S,
			     const Standard_Real    Uinf,	
			     const Standard_Real    Usup,
			     const Standard_Real    Vinf,	
			     const Standard_Real    Vsup,
			     const Standard_Real    TolU,
			     const Standard_Real    TolV,
           const Extrema_ExtFlag F,
           const Extrema_ExtAlgo A)

{
  myExtPS.SetFlag(F);
  myExtPS.SetAlgo(A);
  Initialize(S, Uinf, Usup, Vinf, Vsup, TolU, TolV);
  Perform(P);
}


//=======================================================================
//function : Initialize
//purpose  : 
//=======================================================================

void Extrema_ExtPS::Initialize(const Adaptor3d_Surface& S,
			       const Standard_Real    Uinf,	
			       const Standard_Real    Usup,
			       const Standard_Real    Vinf,	
			       const Standard_Real    Vsup,
			       const Standard_Real    TolU,
			       const Standard_Real    TolV)
{
  myS = (Adaptor3d_SurfacePtr)&S;
  myuinf = Uinf;
  myusup = Usup;
  myvinf = Vinf;
  myvsup = Vsup;

  if (Precision::IsNegativeInfinite(myuinf)) myuinf = -1e10;
  if (Precision::IsPositiveInfinite(myusup)) myusup = 1e10;
  if (Precision::IsNegativeInfinite(myvinf)) myvinf = -1e10;
  if (Precision::IsPositiveInfinite(myvsup)) myvsup = 1e10;

  mytolu = TolU;
  mytolv = TolV;
  mytype = myS->GetType();

  Standard_Boolean isB = ( myS->GetType() == GeomAbs_BSplineSurface ||
			   myS->GetType() == GeomAbs_BezierSurface );

  Standard_Integer nbU = (isB) ? 44 : 32;
  Standard_Integer nbV = (isB) ? 44 : 32;

  Standard_Boolean bUIsoIsDeg = Standard_False, bVIsoIsDeg = Standard_False;

  if(myS->GetType() != GeomAbs_Plane) {
    bUIsoIsDeg = IsoIsDeg(S, myuinf, GeomAbs_IsoU, 0., 1.e-9) ||
                 IsoIsDeg(S, myusup, GeomAbs_IsoU, 0., 1.e-9);
    bVIsoIsDeg = IsoIsDeg(S, myvinf, GeomAbs_IsoV, 0., 1.e-9) ||
                 IsoIsDeg(S, myvsup, GeomAbs_IsoV, 0., 1.e-9);
  }

  if(bUIsoIsDeg) nbU = 300;
  if(bVIsoIsDeg) nbV = 300;

  myExtPS.Initialize(*myS, nbU, nbV, myuinf, myusup, myvinf, myvsup, mytolu, mytolv);
}

//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================

void Extrema_ExtPS::Perform(const gp_Pnt& P)
{
  myPoints.Clear();
  mySqDist.Clear();
  Standard_Integer i;
  
  
  switch(mytype) {
    
  case GeomAbs_Cylinder:
    myExtPElS.Perform(P, myS->Cylinder(), Precision::Confusion());
    break;
  case GeomAbs_Plane:
    myExtPElS.Perform(P, myS->Plane(), Precision::Confusion());
    break;
  case GeomAbs_Cone:
    myExtPElS.Perform(P, myS->Cone(), Precision::Confusion());
    break;
  case GeomAbs_Sphere:
    myExtPElS.Perform(P, myS->Sphere(), Precision::Confusion());
    break;
  case GeomAbs_Torus:
    myExtPElS.Perform(P, myS->Torus(), Precision::Confusion());
    break;

    
  case GeomAbs_SurfaceOfExtrusion: {
    Extrema_ExtPExtS anExtPExtS(P,
				Adaptor3d_SurfaceOfLinearExtrusion(myS->BasisCurve(),
								   myS->Direction()),
				myuinf,myusup, myvinf,myvsup, mytolu,mytolv);
    myDone = anExtPExtS.IsDone();
    if (myDone) 
      for (i = 1; i <= anExtPExtS.NbExt(); i++) {
	TreatSolution (anExtPExtS.Point(i), anExtPExtS.SquareDistance(i));
      }
    return;
  }

    
  case GeomAbs_SurfaceOfRevolution: {
    Extrema_ExtPRevS anExtPRevS(P,
				Adaptor3d_SurfaceOfRevolution(myS->BasisCurve(),
							      myS->AxeOfRevolution()),
				myuinf, myusup,myvinf, myvsup,mytolu, mytolv);
    myDone = anExtPRevS.IsDone();
    if (myDone) 
      for (i = 1; i <= anExtPRevS.NbExt(); i++) {
	TreatSolution (anExtPRevS.Point(i), anExtPRevS.SquareDistance(i));
      }
    return;
  }

    
  default: 
    myExtPS.Perform(P);
    myDone = myExtPS.IsDone();
    if (myDone) 
      for (i = 1; i <= myExtPS.NbExt(); i++) 
	TreatSolution (myExtPS.Point(i), myExtPS.SquareDistance(i));
    return;
  }

  
  myDone = myExtPElS.IsDone();
  if (myDone) 
    for (i = 1; i <= myExtPElS.NbExt(); i++) 
      TreatSolution (myExtPElS.Point(i), myExtPElS.SquareDistance(i));
  return;
}



Standard_Boolean Extrema_ExtPS::IsDone() const
{
  return myDone;
}


Standard_Real Extrema_ExtPS::SquareDistance(const Standard_Integer N) const
{
  if(!myDone) StdFail_NotDone::Raise();
  if ((N < 1) || (N > mySqDist.Length())) Standard_OutOfRange::Raise();
  return mySqDist.Value(N);
}


Standard_Integer Extrema_ExtPS::NbExt() const
{
  if(!myDone) StdFail_NotDone::Raise();
  return mySqDist.Length();
}



const Extrema_POnSurf& Extrema_ExtPS::Point(const Standard_Integer N) const
{
  if(!myDone) StdFail_NotDone::Raise();
  return myPoints.Value(N);
}


void Extrema_ExtPS::TrimmedSquareDistances(Standard_Real& dUfVf,
				      Standard_Real& dUfVl,
				      Standard_Real& dUlVf,
				      Standard_Real& dUlVl,
				      gp_Pnt&        PUfVf,
				      gp_Pnt&        PUfVl,
				      gp_Pnt&        PUlVf,
				      gp_Pnt&        PUlVl) const
{
  dUfVf = d11;
  dUfVl = d12;
  dUlVf = d21;
  dUlVl = d22;
  PUfVf = P11;
  PUfVl = P12;
  PUlVf = P21;
  PUlVl = P22;
}

void Extrema_ExtPS::SetFlag(const Extrema_ExtFlag F)
{
  myExtPS.SetFlag(F);
}

void Extrema_ExtPS::SetAlgo(const Extrema_ExtAlgo A)
{
  myExtPS.SetAlgo(A);
}
