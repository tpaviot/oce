// Created on: 1997-11-21
// Created by: Philippe MANGIN
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


#ifndef DEB
#define No_Standard_RangeError
#define No_Standard_OutOfRange
#define No_Standard_DimensionError
#endif


#include <GeomFill_SweepFunction.ixx>

#include <TColStd_SequenceOfReal.hxx>
#include <GeomLib.hxx>
#include <Precision.hxx>


//=======================================================================
//function : GeomFill_SweepFunction
//purpose  : 
//=======================================================================
GeomFill_SweepFunction::
GeomFill_SweepFunction(const Handle(GeomFill_SectionLaw)& Section,
		       const Handle(GeomFill_LocationLaw)& Location,
		       const Standard_Real  FirstParameter,
		       const Standard_Real  FirstParameterOnS,
		       const Standard_Real  RatioParameterOnS)
{
  myLoc = Location;
  mySec = Section;
  myf = FirstParameter;
  myfOnS = FirstParameterOnS;
  myRatio =  RatioParameterOnS;
}

//=======================================================================
//function : D0
//purpose  : 
//=======================================================================
Standard_Boolean GeomFill_SweepFunction::D0(const Standard_Real Param,
					    const Standard_Real,
					    const Standard_Real,
					    TColgp_Array1OfPnt& Poles,
					    TColgp_Array1OfPnt2d& Poles2d,
					    TColStd_Array1OfReal& Weigths) 
{
  Standard_Integer ii, L;
  Standard_Boolean Ok;
  Standard_Real T =  myfOnS + (Param - myf) * myRatio;
  L = Poles.Length();

  Ok = myLoc->D0(Param, M, V, Poles2d);
  if (!Ok) return Ok;
  Ok = mySec->D0(T, Poles, Weigths);
  if (!Ok) return Ok;

  for (ii=1; ii<=L; ii++) {
    gp_XYZ& aux = Poles(ii).ChangeCoord();
    aux *= M;
    aux += V.XYZ();
  }
  return Standard_True;
}

//=======================================================================
//function : D1
//purpose  : 
//=======================================================================
 Standard_Boolean GeomFill_SweepFunction::D1(const Standard_Real Param,
					     const Standard_Real,
					     const Standard_Real,
					     TColgp_Array1OfPnt& Poles,
					     TColgp_Array1OfVec& DPoles,
					     TColgp_Array1OfPnt2d& Poles2d,
					     TColgp_Array1OfVec2d& DPoles2d,
					     TColStd_Array1OfReal& Weigths,
					     TColStd_Array1OfReal& DWeigths) 
{
  Standard_Integer ii, L;
  Standard_Boolean Ok;
  Standard_Real T =  myfOnS + (Param - myf) * myRatio;
  gp_XYZ PPrim;
  L = Poles.Length();

  Ok = myLoc->D1(Param, M,  V, DM, DV, Poles2d, DPoles2d);
  if (!Ok) return Ok;
  Ok = mySec->D1(T, Poles, DPoles, Weigths, DWeigths);
  if (!Ok) return Ok;

  for (ii=1; ii<=L; ii++) {
    PPrim = DPoles(ii).XYZ();
    gp_XYZ& P = Poles(ii).ChangeCoord();
    PPrim *= myRatio;
    DWeigths(ii) *= myRatio;
    PPrim *= M;
    PPrim += DM*P;
    PPrim += DV.XYZ();
    DPoles(ii).SetXYZ(PPrim);
   
    P *= M;
    P += V.XYZ();
  }  
  return Standard_True;
}

//=======================================================================
//function : D2
//purpose  : 
//=======================================================================
 Standard_Boolean GeomFill_SweepFunction::D2(const Standard_Real Param,
					     const Standard_Real,
					     const Standard_Real ,
					     TColgp_Array1OfPnt& Poles,
					     TColgp_Array1OfVec& DPoles,
					     TColgp_Array1OfVec& D2Poles,
					     TColgp_Array1OfPnt2d& Poles2d,
					     TColgp_Array1OfVec2d& DPoles2d,
					     TColgp_Array1OfVec2d& D2Poles2d,
					     TColStd_Array1OfReal& Weigths,
					     TColStd_Array1OfReal& DWeigths,
					     TColStd_Array1OfReal& D2Weigths) 
{
  Standard_Integer ii, L;
  Standard_Boolean Ok;
  Standard_Real T =  myfOnS + (Param - myf) * myRatio;
  Standard_Real squareratio = myRatio*myRatio;
  L = Poles.Length();

  Ok = myLoc->D2(Param, M,  V, DM, DV, D2M, D2V, 
		 Poles2d, DPoles2d, D2Poles2d);
  if (!Ok) return Ok;
  Ok = mySec->D2(T, Poles, DPoles, D2Poles, 
		 Weigths, DWeigths, D2Weigths);
  if (!Ok) return Ok;

  for (ii=1; ii<=L; ii++) {
    gp_XYZ PSecn = D2Poles(ii).XYZ();
    gp_XYZ PPrim = DPoles(ii).XYZ();
    PPrim *= myRatio;
    DWeigths(ii) *= myRatio;
    PSecn *= squareratio;
    D2Weigths(ii) *= squareratio;
    gp_XYZ& P = Poles(ii).ChangeCoord();

    PSecn *= M;
    PSecn += 2*(DM*PPrim);
    PSecn += D2M*P;
    PSecn += D2V.XYZ();
    D2Poles(ii).SetXYZ(PSecn);

    PPrim *= M;
    PPrim += DM*P;
    PPrim += DV.XYZ();
    DPoles(ii).SetXYZ(PPrim);

    P *= M;
    P += V.XYZ();
  } 
   return Standard_True;
}

//=======================================================================
//function : Nb2dCurves
//purpose  : 
//=======================================================================
 Standard_Integer GeomFill_SweepFunction::Nb2dCurves() const
{
  return myLoc->Nb2dCurves();
}

//=======================================================================
//function : SectionShape
//purpose  : 
//=======================================================================
 void GeomFill_SweepFunction::SectionShape(Standard_Integer& NbPoles,
					   Standard_Integer& NbKnots,
					   Standard_Integer& Degree) const
{
  mySec->SectionShape(NbPoles, NbKnots, Degree); 
}

//=======================================================================
//function : Knots
//purpose  : 
//=======================================================================
 void GeomFill_SweepFunction::Knots(TColStd_Array1OfReal& TKnots) const
{
  mySec->Knots(TKnots);
}

//=======================================================================
//function : Mults
//purpose  : 
//=======================================================================
 void GeomFill_SweepFunction::Mults(TColStd_Array1OfInteger& TMults) const
{
 mySec->Mults(TMults);
}

//=======================================================================
//function : IsRational
//purpose  : 
//=======================================================================
 Standard_Boolean GeomFill_SweepFunction::IsRational() const
{
 return mySec->IsRational();
}

//=======================================================================
//function : NbIntervals
//purpose  : 
//=======================================================================
 Standard_Integer GeomFill_SweepFunction::NbIntervals(const GeomAbs_Shape S) const
{
  Standard_Integer Nb_Sec, Nb_Loc;
  Nb_Sec  =  mySec->NbIntervals(S);
  Nb_Loc  =  myLoc->NbIntervals(S);

  if  (Nb_Sec==1) {
    return Nb_Loc;
  }
  else if (Nb_Loc==1) {
    return Nb_Sec;
  }

  TColStd_Array1OfReal IntS(1, Nb_Sec+1);
  TColStd_Array1OfReal IntL(1, Nb_Loc+1);
  TColStd_SequenceOfReal    Inter;
  Standard_Real T;
  Standard_Integer ii;
  mySec->Intervals(IntS, S);
  for (ii=1; ii<=Nb_Sec+1; ii++) {
    T = (IntS(ii) - myfOnS) / myRatio +  myf;
    IntS(ii) = T;
  }
  myLoc->Intervals(IntL, S);

  GeomLib::FuseIntervals( IntS, IntL, Inter, Precision::PConfusion()*0.99);
  return Inter.Length()-1; 
}

//=======================================================================
//function : Intervals
//purpose  : 
//=======================================================================
 void GeomFill_SweepFunction::Intervals(TColStd_Array1OfReal& T,const GeomAbs_Shape S) const
{
  Standard_Integer Nb_Sec, Nb_Loc, ii;
  Nb_Sec  =  mySec->NbIntervals(S);
  Nb_Loc  =  myLoc->NbIntervals(S);

  if  (Nb_Sec==1) {
    myLoc->Intervals(T, S);
    return;
  }
  else if (Nb_Loc==1) {
    Standard_Real t;
    mySec->Intervals(T, S);
    for (ii=1; ii<=Nb_Sec+1; ii++) {
      t = (T(ii) - myfOnS) / myRatio +  myf;
      T(ii) = t;
    }
    return;
  }

  TColStd_Array1OfReal IntS(1, Nb_Sec+1);
  TColStd_Array1OfReal IntL(1, Nb_Loc+1);
  TColStd_SequenceOfReal    Inter;
  Standard_Real t;

  mySec->Intervals(IntS, S);
  for (ii=1; ii<=Nb_Sec+1; ii++) {
    t = (IntS(ii) - myfOnS) / myRatio +  myf;
    IntS(ii) = t;
  }
  myLoc->Intervals(IntL, S);

  GeomLib::FuseIntervals(IntS, IntL, Inter, Precision::PConfusion()*0.99);
  for (ii=1; ii<=Inter.Length(); ii++)
    T(ii) = Inter(ii);
}

//=======================================================================
//function : SetInterval
//purpose  : 
//=======================================================================
 void GeomFill_SweepFunction::SetInterval(const Standard_Real First,
					  const Standard_Real Last) 
{
  Standard_Real uf, ul;
  myLoc->SetInterval(First, Last);
  uf = myf + (First - myf) * myRatio;
  ul = myf + (Last  - myf) * myRatio;
  mySec->SetInterval(uf, ul);
}

//=======================================================================
//function :
//purpose  : 
//=======================================================================
 void GeomFill_SweepFunction::GetTolerance(const Standard_Real BoundTol,
					   const Standard_Real SurfTol,
					   const Standard_Real AngleTol,
					   TColStd_Array1OfReal& Tol3d) const
{
  mySec->GetTolerance( BoundTol, SurfTol, AngleTol, Tol3d);
}


//=======================================================================
//function : Resolution
//purpose  : 
//=======================================================================
void GeomFill_SweepFunction::Resolution(const Standard_Integer Index,
					const Standard_Real Tol,
					Standard_Real& TolU,
					Standard_Real& TolV)const
{
 myLoc->Resolution(Index, Tol, TolU, TolV);
}

//=======================================================================
//function :
//purpose  : 
//=======================================================================
 void GeomFill_SweepFunction::SetTolerance(const Standard_Real Tol3d,
					   const Standard_Real Tol2d) 
{
  mySec->SetTolerance(Tol3d, Tol2d);
  myLoc->SetTolerance(Tol3d, Tol2d);
}

//=======================================================================
//function :
//purpose  : 
//=======================================================================
 gp_Pnt GeomFill_SweepFunction::BarycentreOfSurf() const
{
  gp_Pnt Bary;
  gp_Vec Translate;
  gp_Mat M;

  Bary =  mySec->BarycentreOfSurf();
  myLoc->GetAverageLaw(M, Translate);
  Bary.ChangeCoord() *= M;
  Bary.ChangeCoord() += Translate.XYZ();

  return Bary;
}

//=======================================================================
//function :
//purpose  : 
//=======================================================================
 Standard_Real GeomFill_SweepFunction::MaximalSection() const
{
  Standard_Real L =  mySec->MaximalSection();
  L *= myLoc->GetMaximalNorm();
  return L;
}

//=======================================================================
//function :
//purpose  : 
//=======================================================================
 void GeomFill_SweepFunction::GetMinimalWeight(TColStd_Array1OfReal& Weigths) const
{
  mySec->GetMinimalWeight(Weigths);
}













