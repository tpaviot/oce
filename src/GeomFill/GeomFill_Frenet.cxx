// Created on: 1998-01-22
// Created by: Philippe MANGIN/Roman BORISOV
// Copyright (c) 1998-1999 Matra Datavision
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


#include <GeomFill_Frenet.ixx>
#include <GeomAbs_CurveType.hxx>
#include <Adaptor3d_HCurve.hxx>
#include <Precision.hxx>
#include <GeomLib.hxx>
#include <GeomFill_SnglrFunc.hxx>
#include <Extrema_ExtPC.hxx>
#include <TColStd_HArray1OfBoolean.hxx>
#include <SortTools_QuickSortOfReal.hxx>
#include <TCollection_CompareOfReal.hxx>
#include <TColgp_SequenceOfPnt2d.hxx>

#define NullTol 1.e-10
#define MaxSingular 1.e-5

//=======================================================================
//function : FDeriv
//purpose  : computes (F/|F|)'
//=======================================================================
static gp_Vec FDeriv(const gp_Vec& F, const gp_Vec& DF)
{
  Standard_Real Norma = F.Magnitude();
  gp_Vec Result = (DF - F*(F*DF)/(Norma*Norma))/Norma;
  return Result;
}


//=======================================================================
//function : DDeriv
//purpose  : computes (F/|F|)''
//=======================================================================
static gp_Vec DDeriv(const gp_Vec& F, const gp_Vec& DF, const gp_Vec& D2F)
{
  Standard_Real Norma = F.Magnitude();
  gp_Vec Result = (D2F - 2*DF*(F*DF)/(Norma*Norma))/Norma - 
     F*((DF.SquareMagnitude() + F*D2F 
        - 3*(F*DF)*(F*DF)/(Norma*Norma))/(Norma*Norma*Norma));
  return Result;
}

//=======================================================================
//function : GeomFill_Frenet
//purpose  : 
//=======================================================================

GeomFill_Frenet::GeomFill_Frenet()
{
}


//=======================================================================
//function : Copy
//purpose  : 
//=======================================================================

Handle(GeomFill_TrihedronLaw) GeomFill_Frenet::Copy() const
{
  Handle(GeomFill_Frenet) copy = new (GeomFill_Frenet)();
  if (!myCurve.IsNull()) copy->SetCurve(myCurve);
  return copy;
}

//=======================================================================
//function : SetCurve
//purpose  : 
//=======================================================================

 void GeomFill_Frenet::SetCurve(const Handle(Adaptor3d_HCurve)& C) 
{
  GeomFill_TrihedronLaw::SetCurve(C);
  if (! C.IsNull()) {
    GeomAbs_CurveType type;
    type = C->GetType();
    switch  (type) {
    case GeomAbs_Circle:
    case GeomAbs_Ellipse:
    case GeomAbs_Hyperbola:
    case GeomAbs_Parabola:
    case GeomAbs_Line:
      {
	// No probleme
	isSngl = Standard_False;
      }
     default :
       { 
	 // We have to search singulaties
	 Init(); 
       }
    }
  }
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

 void GeomFill_Frenet::Init()
{
  Standard_Integer i, j;
  GeomFill_SnglrFunc Func(myCurve);
  Standard_Real TolF = 1.0e-10, Tol = 10*TolF, Tol2 = Tol * Tol,
                PTol = Precision::PConfusion();

// We want to determine if the curve has linear segments
  Standard_Integer NbIntC2 = myCurve->NbIntervals(GeomAbs_C2);
  Handle(TColStd_HArray1OfReal) myC2Disc = 
    new TColStd_HArray1OfReal(1, NbIntC2 + 1);
  Handle(TColStd_HArray1OfBoolean) IsLin = 
    new TColStd_HArray1OfBoolean(1, NbIntC2);
  Handle(TColStd_HArray1OfBoolean) IsConst = 
    new TColStd_HArray1OfBoolean(1, NbIntC2);
  TColStd_Array1OfReal AveFunc(1,  NbIntC2);
  myCurve->Intervals(myC2Disc->ChangeArray1(), GeomAbs_C2);
  Standard_Integer NbControl = 10;
  Standard_Real Step, Average = 0, modulus;
  gp_Pnt C, C1;
  for(i = 1; i <= NbIntC2; i++) {
    Step = (myC2Disc->Value(i+1) - myC2Disc->Value(i))/NbControl;
    IsLin->ChangeValue(i) = Standard_True;
    IsConst->ChangeValue(i) = Standard_True;
    for(j = 1; j <= NbControl; j++) {
      Func.D0(myC2Disc->Value(i) + (j-1)*Step, C);
      if(j == 1) C1 = C;
      modulus = C.XYZ().Modulus();
      if(modulus > Tol) {
	IsLin->ChangeValue(i) = Standard_False;
      }
      Average += modulus;

      if(IsConst->Value(i)) {
	if(Abs(C.X() - C1.X()) > Tol ||
	   Abs(C.Y() - C1.Y()) > Tol ||
	   Abs(C.Z() - C1.Z()) > Tol) {
	  IsConst->ChangeValue(i) = Standard_False;
	}
      }
	  
    }
    AveFunc(i) = Average/NbControl;
  }
  
// Here we are looking for singularities
  TColStd_SequenceOfReal * SeqArray = new TColStd_SequenceOfReal[ NbIntC2 ];
  TColStd_SequenceOfReal SnglSeq;
//  Standard_Real Value2, preValue=1.e200, t;
  Standard_Real Value2, t;
  Extrema_ExtPC Ext;
  gp_Pnt Origin(0, 0, 0);

  for(i = 1; i <= NbIntC2; i++) {
    if (!IsLin->Value(i) && !IsConst->Value(i))
      {
	Func.SetRatio(1./AveFunc(i)); // Normalization
	Ext.Initialize(Func, myC2Disc->Value(i), myC2Disc->Value(i+1), TolF);
	Ext.Perform(Origin);
	if(Ext.IsDone() && Ext.NbExt() != 0)
	  {
	    for(j = 1; j <= Ext.NbExt(); j++)
	      {
		Value2 = Ext.SquareDistance(j);
		if(Value2 < Tol2)
		  {
		    t = Ext.Point(j).Parameter();
		    SeqArray[i-1].Append(t);
		  }
	      }
	  }
	// sorting
	if(SeqArray[i-1].Length() != 0) {
	  TColStd_Array1OfReal anArray( 1, SeqArray[i-1].Length() );
	  for (j = 1; j <= anArray.Length(); j++)
	    anArray(j) = SeqArray[i-1](j);
	  TCollection_CompareOfReal Compar;
	  SortTools_QuickSortOfReal::Sort( anArray, Compar);
	  for (j = 1; j <= anArray.Length(); j++)
	    SeqArray[i-1](j) = anArray(j);
	}
      }
  }
  //Filling SnglSeq by first sets of roots
  for(i = 0; i < NbIntC2; i++)
    for (j = 1; j <= SeqArray[i].Length(); j++)
      SnglSeq.Append( SeqArray[i](j) );

  //Extrema works bad, need to pass second time
  for(i = 0; i < NbIntC2; i++)
    if (! SeqArray[i].IsEmpty())
      {
	SeqArray[i].Prepend( myC2Disc->Value(i+1) );
	SeqArray[i].Append( myC2Disc->Value(i+2) );
	Func.SetRatio(1./AveFunc(i+1)); // Normalization
	for (j = 1; j < SeqArray[i].Length(); j++)
	  if (SeqArray[i](j+1) - SeqArray[i](j) > PTol)
	    {
	      Ext.Initialize(Func, SeqArray[i](j), SeqArray[i](j+1), TolF);
	      Ext.Perform(Origin);
	      if(Ext.IsDone())
		{
		  for(Standard_Integer k = 1; k <= Ext.NbExt(); k++)
		    {
		      Value2 = Ext.SquareDistance(k);
		      if(Value2 < Tol2)
			{
			  t = Ext.Point(k).Parameter();
			  if (t-SeqArray[i](j) > PTol && SeqArray[i](j+1)-t > PTol)
			    SnglSeq.Append(t);
			}
		    }
		}
	    }
      }

  delete [] SeqArray;

  if(SnglSeq.Length() > 0) {
    // sorting
    TColStd_Array1OfReal anArray( 1, SnglSeq.Length() );
    for (i = 1; i <= SnglSeq.Length(); i++)
      anArray(i) = SnglSeq(i);
    TCollection_CompareOfReal Compar;
    SortTools_QuickSortOfReal::Sort( anArray, Compar );
    for (i = 1; i <= SnglSeq.Length(); i++)
      SnglSeq(i) = anArray(i);
    
    // discard repeating elements
    Standard_Boolean found = Standard_True;
    j = 1;
    while (found)
      {
	found = Standard_False;
	for (i = j; i < SnglSeq.Length(); i++)
	  if (SnglSeq(i+1) - SnglSeq(i) <= PTol)
	    {
	      SnglSeq.Remove(i+1);
	      j = i;
	      found = Standard_True;
	      break;
	    }
      }
    
    mySngl = new TColStd_HArray1OfReal(1, SnglSeq.Length());
    for(i = 1; i <= mySngl->Length(); i++)
      mySngl->ChangeValue(i) = SnglSeq(i);

// computation of length of singular interval
    mySnglLen = new TColStd_HArray1OfReal(1, mySngl->Length());
    gp_Vec SnglDer, SnglDer2;
    Standard_Real norm;
    for(i = 1; i <= mySngl->Length(); i++) {
      Func.D2(mySngl->Value(i), C, SnglDer, SnglDer2);
      if ((norm = SnglDer.Magnitude()) > gp::Resolution())
        mySnglLen->ChangeValue(i) = Min(NullTol/norm, MaxSingular);
      else if ((norm = SnglDer2.Magnitude()) > gp::Resolution())
        mySnglLen->ChangeValue(i) = Min(Sqrt(2*NullTol/norm), MaxSingular);
      else mySnglLen->ChangeValue(i) = MaxSingular;
    }
#if DEB
    for(i = 1; i <= mySngl->Length(); i++) {
      cout<<"Sngl("<<i<<") = "<<mySngl->Value(i)<<" Length = "<<mySnglLen->Value(i)<<endl;
    }
#endif
    if(mySngl->Length() > 1) {
// we have to merge singular points that have common parts of singular intervals
    TColgp_SequenceOfPnt2d tmpSeq;
    tmpSeq.Append(gp_Pnt2d(mySngl->Value(1), mySnglLen->Value(1)));
    Standard_Real U11, U12, U21, U22;
    for(i = 2; i<= mySngl->Length(); i++) {
      U12 = tmpSeq.Last().X() + tmpSeq.Last().Y();
      U21 = mySngl->Value(i) - mySnglLen->Value(i);
      if(U12 >= U21) {
        U11 = tmpSeq.Last().X() - tmpSeq.Last().Y();
        U22 = mySngl->Value(i) + mySnglLen->Value(i);
        tmpSeq.ChangeValue(tmpSeq.Length()) = gp_Pnt2d((U11 + U22)/2, (U22 - U11)/2);
      }
      else tmpSeq.Append(gp_Pnt2d(mySngl->Value(i), mySnglLen->Value(i)));
    }
    mySngl = new TColStd_HArray1OfReal(1, tmpSeq.Length());
    mySnglLen = new TColStd_HArray1OfReal(1, tmpSeq.Length());
    for(i = 1; i <= mySngl->Length(); i++) {
      mySngl->ChangeValue(i) = tmpSeq(i).X();
      mySnglLen->ChangeValue(i) = tmpSeq(i).Y();
    }
  }    
#if DEB
    cout<<"After merging"<<endl;
    for(i = 1; i <= mySngl->Length(); i++) {
      cout<<"Sngl("<<i<<") = "<<mySngl->Value(i)<<" Length = "<<mySnglLen->Value(i)<<endl;
    }
#endif
    isSngl = Standard_True;
  }
  else isSngl = Standard_False;
}

//=======================================================================
//function : D0
//purpose  : 
//=======================================================================

 Standard_Boolean GeomFill_Frenet::D0(const Standard_Real Param,
                                      gp_Vec& Tangent,
                                      gp_Vec& Normal,
                                      gp_Vec& BiNormal)
{
  Standard_Real norm;
  Standard_Integer Index;
  Standard_Real Delta = 0.;
  if(IsSingular(Param, Index)) 
    if (SingularD0(Param, Index, Tangent, Normal, BiNormal, Delta))
      return Standard_True;

  Standard_Real theParam = Param + Delta;
  myTrimmed->D2(theParam, P, Tangent, BiNormal);
  Tangent.Normalize();
  BiNormal = Tangent.Crossed(BiNormal);
  norm = BiNormal.Magnitude();
  if (norm <= gp::Resolution()) {
    gp_Ax2 Axe (gp_Pnt(0,0,0), Tangent);
    BiNormal.SetXYZ(Axe.YDirection().XYZ());    
  }
  else BiNormal.Normalize();

  Normal = BiNormal;
  Normal.Cross(Tangent);

  return Standard_True;
}

//=======================================================================
//function : D1
//purpose  : 
//=======================================================================

 Standard_Boolean GeomFill_Frenet::D1(const Standard_Real Param,
                                      gp_Vec& Tangent,
                                      gp_Vec& DTangent,
                                      gp_Vec& Normal,
                                      gp_Vec& DNormal,
                                      gp_Vec& BiNormal,
                                      gp_Vec& DBiNormal) 
{
  Standard_Integer Index;
  Standard_Real Delta = 0.;
  if(IsSingular(Param, Index)) 
    if (SingularD1(Param, Index, Tangent, DTangent, Normal, DNormal, BiNormal, DBiNormal, Delta))
      return Standard_True;

//  Standard_Real Norma;
  Standard_Real theParam = Param + Delta;
  gp_Vec DC1, DC2, DC3;
  myTrimmed->D3(theParam, P, DC1, DC2, DC3);
  Tangent = DC1.Normalized();

  //if (DC2.Magnitude() <= NullTol || Tangent.Crossed(DC2).Magnitude() <= NullTol) {
  if (Tangent.Crossed(DC2).Magnitude() <= gp::Resolution()) {
    gp_Ax2 Axe (gp_Pnt(0,0,0), Tangent);
    Normal.SetXYZ(Axe.XDirection().XYZ());
    BiNormal.SetXYZ(Axe.YDirection().XYZ());
    DTangent.SetCoord(0,0,0);
    DNormal.SetCoord(0,0,0);
    DBiNormal.SetCoord(0,0,0);
    return Standard_True;
  }
  else
    BiNormal = Tangent.Crossed(DC2).Normalized();

  Normal = BiNormal.Crossed(Tangent);

  DTangent = FDeriv(DC1, DC2);

  gp_Vec instead_DC1, instead_DC2;
  instead_DC1 = Tangent.Crossed(DC2);
  instead_DC2 = DTangent.Crossed(DC2) + Tangent.Crossed(DC3);
  DBiNormal = FDeriv(instead_DC1, instead_DC2);

  DNormal = DBiNormal.Crossed(Tangent) + BiNormal.Crossed(DTangent);
  return Standard_True;
}

//=======================================================================
//function : D2
//purpose  : 
//=======================================================================

 Standard_Boolean GeomFill_Frenet::D2(const Standard_Real Param,
                                      gp_Vec& Tangent,
                                      gp_Vec& DTangent,
                                      gp_Vec& D2Tangent,
                                      gp_Vec& Normal,
                                      gp_Vec& DNormal,
                                      gp_Vec& D2Normal,
                                      gp_Vec& BiNormal,
                                      gp_Vec& DBiNormal,
                                      gp_Vec& D2BiNormal) 
{
  Standard_Integer Index;
  Standard_Real Delta = 0.;
  if(IsSingular(Param, Index)) 
    if(SingularD2(Param, Index, Tangent, DTangent, D2Tangent, 
                  Normal, DNormal, D2Normal, 
                  BiNormal, DBiNormal, D2BiNormal,
                  Delta))
      return Standard_True;

//  Standard_Real Norma;
  Standard_Real theParam = Param + Delta;
  gp_Vec DC1, DC2, DC3, DC4;
  myTrimmed->D3(theParam, P, DC1, DC2, DC3);
  DC4 = myTrimmed->DN(theParam, 4);

  Tangent = DC1.Normalized();

  //if (DC2.Magnitude() <= NullTol || Tangent.Crossed(DC2).Magnitude() <= NullTol) {
  if (Tangent.Crossed(DC2).Magnitude() <= gp::Resolution()) {
    gp_Ax2 Axe (gp_Pnt(0,0,0), Tangent);
    Normal.SetXYZ(Axe.XDirection().XYZ());
    BiNormal.SetXYZ(Axe.YDirection().XYZ());
    DTangent.SetCoord(0,0,0);
    DNormal.SetCoord(0,0,0);
    DBiNormal.SetCoord(0,0,0);
    D2Tangent.SetCoord(0,0,0);
    D2Normal.SetCoord(0,0,0);
    D2BiNormal.SetCoord(0,0,0);
    return Standard_True;
  }
  else
    BiNormal = Tangent.Crossed(DC2).Normalized();

  Normal = BiNormal.Crossed(Tangent);

  DTangent = FDeriv(DC1, DC2);
  D2Tangent = DDeriv(DC1, DC2, DC3);
  
  gp_Vec instead_DC1, instead_DC2, instead_DC3;
  instead_DC1 = Tangent.Crossed(DC2);
  instead_DC2 = DTangent.Crossed(DC2) + Tangent.Crossed(DC3);
  instead_DC3 = D2Tangent.Crossed(DC2) + 2*DTangent.Crossed(DC3) + Tangent.Crossed(DC4);
  DBiNormal = FDeriv(instead_DC1, instead_DC2);
  D2BiNormal = DDeriv(instead_DC1, instead_DC2, instead_DC3);

  DNormal = DBiNormal.Crossed(Tangent) + BiNormal.Crossed(DTangent);

  D2Normal = D2BiNormal.Crossed(Tangent) + 2*DBiNormal.Crossed(DTangent) + BiNormal.Crossed(D2Tangent);

  return Standard_True;
}

//=======================================================================
//function : NbIntervals
//purpose  : 
//=======================================================================

 Standard_Integer GeomFill_Frenet::NbIntervals(const GeomAbs_Shape S) const
{
  GeomAbs_Shape tmpS = GeomAbs_C0;
  Standard_Integer NbTrimmed;
  switch (S) {
  case GeomAbs_C0: tmpS = GeomAbs_C2; break;
  case GeomAbs_C1: tmpS = GeomAbs_C3; break;
  case GeomAbs_C2:
  case GeomAbs_C3:
  case GeomAbs_CN: tmpS = GeomAbs_CN; break;
  default: Standard_OutOfRange::Raise();
  }
  
  NbTrimmed = myCurve->NbIntervals(tmpS);

  if (!isSngl) return NbTrimmed;

  TColStd_Array1OfReal TrimInt(1, NbTrimmed + 1);
  myCurve->Intervals(TrimInt, tmpS);

  TColStd_SequenceOfReal Fusion;
  GeomLib::FuseIntervals(TrimInt, mySngl->Array1(), Fusion);

  return Fusion.Length() - 1;
}

//=======================================================================
//function : Intervals
//purpose  : 
//=======================================================================

 void GeomFill_Frenet::Intervals(TColStd_Array1OfReal& T,
                                 const GeomAbs_Shape S) const
{
  GeomAbs_Shape tmpS = GeomAbs_C0;
  Standard_Integer NbTrimmed;
  switch (S) {
  case GeomAbs_C0: tmpS = GeomAbs_C2; break;
  case GeomAbs_C1: tmpS = GeomAbs_C3; break;
  case GeomAbs_C2:
  case GeomAbs_C3:
  case GeomAbs_CN: tmpS = GeomAbs_CN; break;
  default: Standard_OutOfRange::Raise();
  }

  if (!isSngl) {
    myCurve->Intervals(T, tmpS);
    return;
  }

  NbTrimmed = myCurve->NbIntervals(tmpS);
  TColStd_Array1OfReal TrimInt(1, NbTrimmed + 1);
  myCurve->Intervals(TrimInt, tmpS);

  TColStd_SequenceOfReal Fusion;
  GeomLib::FuseIntervals(TrimInt, mySngl->Array1(), Fusion);

  for (Standard_Integer i = 1; i <= Fusion.Length(); i++)
    T.ChangeValue(i) = Fusion.Value(i);
}

 void GeomFill_Frenet::GetAverageLaw(gp_Vec& ATangent,
                                     gp_Vec& ANormal,
                                     gp_Vec& ABiNormal) 
{
  Standard_Integer Num = 20; //order of digitalization
  gp_Vec T, N, BN;
  ATangent = gp_Vec(0, 0, 0);
  ANormal = gp_Vec(0, 0, 0);
  ABiNormal = gp_Vec(0, 0, 0);
  Standard_Real Step = (myTrimmed->LastParameter() - 
                        myTrimmed->FirstParameter()) / Num;
  Standard_Real Param;
  for (Standard_Integer i = 0; i <= Num; i++) {
    Param = myTrimmed->FirstParameter() + i*Step;
    if (Param > myTrimmed->LastParameter()) Param = myTrimmed->LastParameter();
    D0(Param, T, N, BN);
    ATangent += T;
    ANormal += N;
    ABiNormal += BN;
  }
  ATangent /= Num + 1;
  ANormal /= Num + 1;

  ATangent.Normalize();
  ABiNormal = ATangent.Crossed(ANormal).Normalized();
  ANormal = ABiNormal.Crossed(ATangent);
}

//=======================================================================
//function : IsConstant
//purpose  : 
//=======================================================================

 Standard_Boolean GeomFill_Frenet::IsConstant() const
{
  return (myCurve->GetType() == GeomAbs_Line);
}

//=======================================================================
//function : IsOnlyBy3dCurve
//purpose  : 
//=======================================================================

 Standard_Boolean GeomFill_Frenet::IsOnlyBy3dCurve() const
{
  return Standard_True;
}

//=======================================================================
//function : IsSingular
//purpose  : 
//=======================================================================

Standard_Boolean GeomFill_Frenet::IsSingular(const Standard_Real U, Standard_Integer& Index) const
{
  Standard_Integer i;
  if(!isSngl) return Standard_False;
  for(i = 1; i <= mySngl->Length(); i++) {
    if (Abs(U - mySngl->Value(i)) < mySnglLen->Value(i)) {
      Index = i;
      return Standard_True;    
    }
  }
  return Standard_False;
}

//=======================================================================
//function : DoSingular
//purpose  : 
//=======================================================================

Standard_Boolean GeomFill_Frenet::DoSingular(const Standard_Real U,
                                             const Standard_Integer Index,
                                             gp_Vec& Tangent,
                                             gp_Vec& BiNormal, 
                                             Standard_Integer& n, 
                                             Standard_Integer& k, 
                                             Standard_Integer& TFlag,
                                             Standard_Integer& BNFlag,
                                             Standard_Real& Delta)
{
  Standard_Integer i, MaxN = 20;
  Delta = 0.;
  Standard_Real h;
  h = 2*mySnglLen->Value(Index);

  Standard_Real A, B;
  gp_Vec T, N, BN;
  TFlag = 1;
  BNFlag = 1;
  GetInterval(A, B);
  if (U >= (A + B)/2)
    h = -h;
  for(i = 1; i <= MaxN; i++) {
    Tangent = myTrimmed->DN(U, i);
    if(Tangent.Magnitude() > Precision::Confusion()) break;
  }
  if (i > MaxN) return Standard_False;
  Tangent.Normalize();
  n = i;

  i++;
  for(; i <= MaxN; i++) {
    BiNormal = Tangent.Crossed(myTrimmed->DN(U, i));
    Standard_Real magn = BiNormal.Magnitude();
    if (magn > Precision::Confusion())
      {
	//modified by jgv, 12.08.03 for OCC605 ////
	gp_Vec NextBiNormal = Tangent.Crossed(myTrimmed->DN(U, i+1));
	if (NextBiNormal.Magnitude() > magn)
	  {
	    i++;
	    BiNormal = NextBiNormal;
	  }
	///////////////////////////////////////////
	break;
      }
  }
  if (i > MaxN)
  {
    Delta = h;
    return Standard_False;
  }
  
  BiNormal.Normalize();
  k = i;

  D0(U + h, T, N, BN);

  if(Tangent.Angle(T) > M_PI/2) TFlag = -1;
  if(BiNormal.Angle(BN) > M_PI/2) BNFlag = -1;  

  return Standard_True;
}

 Standard_Boolean GeomFill_Frenet::SingularD0(const Standard_Real Param,
                                              const Standard_Integer Index,
                                              gp_Vec& Tangent,
                                              gp_Vec& Normal,
                                              gp_Vec& BiNormal,
                                              Standard_Real& Delta)
{
  Standard_Integer n, k, TFlag, BNFlag;
  if(!DoSingular(Param, Index, Tangent, BiNormal, 
                 n, k, TFlag, BNFlag, Delta))
    return Standard_False;
  
  Tangent *= TFlag;
  BiNormal *= BNFlag;
  Normal = BiNormal;
  Normal.Cross(Tangent);

  return Standard_True;
}

 Standard_Boolean GeomFill_Frenet::SingularD1(const Standard_Real Param,
                                              const Standard_Integer Index,
                                              gp_Vec& Tangent,gp_Vec& DTangent,
                                              gp_Vec& Normal,gp_Vec& DNormal,
                                              gp_Vec& BiNormal,gp_Vec& DBiNormal,
                                              Standard_Real& Delta) 
{
  Standard_Integer n, k, TFlag, BNFlag;
  if(!DoSingular(Param, Index, Tangent, BiNormal, n, k, TFlag, BNFlag, Delta))
    return Standard_False;

  gp_Vec F, DF, Dtmp;
  F = myTrimmed->DN(Param, n);
  DF = myTrimmed->DN(Param, n+1);
  DTangent = FDeriv(F, DF);

  Dtmp = myTrimmed->DN(Param, k);
  F = Tangent.Crossed(Dtmp);
  DF = DTangent.Crossed(Dtmp) + Tangent.Crossed(myTrimmed->DN(Param, k+1));
  DBiNormal = FDeriv(F, DF);

  if(TFlag < 0) {
    Tangent = -Tangent;
    DTangent = -DTangent;
  }

  if(BNFlag < 0) {
    BiNormal = -BiNormal;
    DBiNormal = -DBiNormal;
  }

  Normal = BiNormal.Crossed(Tangent);  
  DNormal = DBiNormal.Crossed(Tangent) + BiNormal.Crossed(DTangent);

  return Standard_True;
}

 Standard_Boolean GeomFill_Frenet::SingularD2(const Standard_Real Param,
                                              const Standard_Integer Index,
                                              gp_Vec& Tangent,
                                              gp_Vec& DTangent,
                                              gp_Vec& D2Tangent,
                                              gp_Vec& Normal,
                                              gp_Vec& DNormal,
                                              gp_Vec& D2Normal,
                                              gp_Vec& BiNormal,
                                              gp_Vec& DBiNormal,
                                              gp_Vec& D2BiNormal,
                                              Standard_Real& Delta)
{
  Standard_Integer n, k, TFlag, BNFlag;
  if(!DoSingular(Param, Index, Tangent, BiNormal, n, k, TFlag, BNFlag, Delta)) 
    return Standard_False;

  gp_Vec F, DF, D2F, Dtmp1, Dtmp2;
  F = myTrimmed->DN(Param, n);
  DF = myTrimmed->DN(Param, n+1);
  D2F = myTrimmed->DN(Param, n+2);
  DTangent = FDeriv(F, DF);
  D2Tangent = DDeriv(F, DF, D2F);

  Dtmp1 = myTrimmed->DN(Param, k);
  Dtmp2 = myTrimmed->DN(Param, k+1);
  F = Tangent.Crossed(Dtmp1);
  DF = DTangent.Crossed(Dtmp1) + Tangent.Crossed(Dtmp2);
  D2F = D2Tangent.Crossed(Dtmp1) + 2*DTangent.Crossed(Dtmp2) + 
    Tangent.Crossed(myTrimmed->DN(Param, k+2));
  DBiNormal = FDeriv(F, DF);
  D2BiNormal = DDeriv(F, DF, D2F);

  if(TFlag < 0) {
    Tangent = -Tangent;
    DTangent = -DTangent;
    D2Tangent = -D2Tangent;
  }

  if(BNFlag < 0) {
    BiNormal = -BiNormal;
    DBiNormal = -DBiNormal;
    D2BiNormal = -D2BiNormal;
  }

  Normal = BiNormal.Crossed(Tangent);
  DNormal = DBiNormal.Crossed(Tangent) + BiNormal.Crossed(DTangent);
  D2Normal = D2BiNormal.Crossed(Tangent) + 2*DBiNormal.Crossed(DTangent) + BiNormal.Crossed(D2Tangent); 

  return Standard_True;
}
