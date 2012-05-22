// Created on: 1998-03-03
// Created by: Roman BORISOV
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



#include <GeomFill_ConstantBiNormal.ixx>

#include <gp_Ax1.hxx>
#include <gp_Lin.hxx>

#include <Precision.hxx>

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

GeomFill_ConstantBiNormal::GeomFill_ConstantBiNormal(const gp_Dir& BiNormal) : BN(BiNormal)
{
  frenet = new GeomFill_Frenet();
}

 Handle(GeomFill_TrihedronLaw) GeomFill_ConstantBiNormal::Copy() const
{
  Handle(GeomFill_TrihedronLaw) copy = new GeomFill_ConstantBiNormal(gp_Dir(BN));
  if (!myCurve.IsNull()) copy->SetCurve(myCurve);
  return copy;
}

 void GeomFill_ConstantBiNormal::SetCurve(const Handle(Adaptor3d_HCurve)& C) 
{
  GeomFill_TrihedronLaw::SetCurve(C);
    if (! C.IsNull()) { 
    frenet->SetCurve(C);
  }
}

 Standard_Boolean GeomFill_ConstantBiNormal::D0(const Standard_Real Param,gp_Vec& Tangent,gp_Vec& Normal,gp_Vec& BiNormal) 
{
// if BN^T != 0 then N = (BN^T).Normalized ; T = N^BN  
// else T = (N^BN).Normalized ; N = BN^T

  frenet->D0(Param, Tangent, Normal, BiNormal);
  BiNormal = BN;
  if(BiNormal.Crossed(Tangent).Magnitude() > Precision::Confusion()) {
    Normal = BiNormal.Crossed(Tangent).Normalized();    
    Tangent = Normal.Crossed(BiNormal);
  }
  else {
    Tangent = Normal.Crossed(BiNormal).Normalized(); 
    Normal = BiNormal.Crossed(Tangent);
  }
/*for Test
  gp_Vec DTangent, D2Tangent, DNormal, D2Normal, DBiNormal, D2BiNormal;
  D2(Param, Tangent, DTangent, D2Tangent, 
     Normal, DNormal, D2Normal, BiNormal, DBiNormal, D2BiNormal);
*/
  return Standard_True;
}

 Standard_Boolean GeomFill_ConstantBiNormal::D1(const Standard_Real Param,gp_Vec& Tangent,gp_Vec& DTangent,gp_Vec& Normal,gp_Vec& DNormal,gp_Vec& BiNormal,gp_Vec& DBiNormal) 
{
  gp_Vec F, DF;
  frenet->D1(Param, Tangent, DTangent, Normal, DNormal, BiNormal, DBiNormal);
  BiNormal = BN;
  DBiNormal = gp_Vec(0, 0, 0);
  if(BiNormal.Crossed(Tangent).Magnitude() > Precision::Confusion()) {
    F = BiNormal.Crossed(Tangent);
    DF = BiNormal.Crossed(DTangent);
    Normal = F.Normalized();    
    DNormal = FDeriv(F, DF);
    
    Tangent = Normal.Crossed(BiNormal);
    DTangent = DNormal.Crossed(BiNormal);
  }
  else {
    F = Normal.Crossed(BiNormal);
    DF = DNormal.Crossed(BiNormal);
    Tangent = F.Normalized();
    DTangent = FDeriv(F, DF);

    Normal = BiNormal.Crossed(Tangent);
    DNormal = BiNormal.Crossed(DTangent);
  }
/*test
  Standard_Real h = 1.e-10;
  gp_Vec cTangent, cNormal, cBiNormal, Tangent_, Normal_, BiNormal_;
  D0(Param, cTangent, cNormal, cBiNormal);
  D0(Param + h, Tangent_, Normal_, BiNormal_);
  cTangent = (Tangent_ - cTangent)/h;
  cNormal = (Normal_ - cNormal)/h;
  cBiNormal = (BiNormal_ - cBiNormal)/h;
  cout<<"DTangent = ("<<DTangent.X()<<", "<<DTangent.Y()<<", "<<DTangent.Z()<<")"<<endl;
  cout<<"CTangent = ("<<cTangent.X()<<", "<<cTangent.Y()<<", "<<cTangent.Z()<<")"<<endl;
  cout<<"DNormal = ("<<DNormal.X()<<", "<<DNormal.Y()<<", "<<DNormal.Z()<<")"<<endl;
  cout<<"CNormal = ("<<cNormal.X()<<", "<<cNormal.Y()<<", "<<cNormal.Z()<<")"<<endl;
  cout<<"DBiNormal = ("<<DBiNormal.X()<<", "<<DBiNormal.Y()<<", "<<DBiNormal.Z()<<")"<<endl;
  cout<<"CBiNormal = ("<<cBiNormal.X()<<", "<<cBiNormal.Y()<<", "<<cBiNormal.Z()<<")"<<endl;
*/
  return Standard_True;
}

 Standard_Boolean GeomFill_ConstantBiNormal::D2(const Standard_Real Param,
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
  gp_Vec F, DF, D2F;
  frenet->D2(Param, Tangent, DTangent, D2Tangent,
	     Normal, DNormal, D2Normal, 
	     BiNormal, DBiNormal, D2BiNormal);
  BiNormal = BN;
  DBiNormal = gp_Vec(0, 0, 0);
  D2BiNormal = gp_Vec(0, 0, 0);
  if(BiNormal.Crossed(Tangent).Magnitude() > Precision::Confusion()) {
    F = BiNormal.Crossed(Tangent);
    DF = BiNormal.Crossed(DTangent);
    D2F = BiNormal.Crossed(D2Tangent);
    Normal = F.Normalized();    
    DNormal = FDeriv(F, DF);
    D2Normal = DDeriv(F, DF, D2F);

    Tangent = Normal.Crossed(BiNormal);
    DTangent = DNormal.Crossed(BiNormal);
    D2Tangent = D2Normal.Crossed(BiNormal);
  }
  else {
    F = Normal.Crossed(BiNormal);
    DF = DNormal.Crossed(BiNormal);
    D2F = D2Normal.Crossed(BiNormal);
    Tangent = F.Normalized();
    DTangent = FDeriv(F, DF);
    D2Tangent = DDeriv(F, DF, D2F);

    Normal = BiNormal.Crossed(Tangent);
    DNormal = BiNormal.Crossed(DTangent);
    D2Normal = BiNormal.Crossed(D2Tangent);
  }
/*  cout<<"Param = "<<Param<<endl;
  cout<<"Tangent = ("<<Tangent.X()<<", "<<Tangent.Y()<<", "<<Tangent.Z()<<")"<<endl;
  cout<<"DTangent = ("<<DTangent.X()<<", "<<DTangent.Y()<<", "<<DTangent.Z()<<")"<<endl;
  cout<<"D2Tangent = ("<<D2Tangent.X()<<", "<<D2Tangent.Y()<<", "<<D2Tangent.Z()<<")"<<endl;

  cout<<"BiNormal = ("<<BiNormal.X()<<", "<<BiNormal.Y()<<", "<<BiNormal.Z()<<")"<<endl;
  cout<<"DBiNormal = ("<<DBiNormal.X()<<", "<<DBiNormal.Y()<<", "<<DBiNormal.Z()<<")"<<endl;
  cout<<"D2BiNormal = ("<<D2BiNormal.X()<<", "<<D2BiNormal.Y()<<", "<<D2BiNormal.Z()<<")"<<endl;
*/  
  return Standard_True;
}

 Standard_Integer GeomFill_ConstantBiNormal::NbIntervals(const GeomAbs_Shape S) const
{
  return frenet->NbIntervals(S);
}

 void GeomFill_ConstantBiNormal::Intervals(TColStd_Array1OfReal& T,const GeomAbs_Shape S) const
{
  frenet->Intervals(T, S);
}

 void GeomFill_ConstantBiNormal::GetAverageLaw(gp_Vec& ATangent,gp_Vec& ANormal,gp_Vec& ABiNormal) 
{
  frenet->GetAverageLaw(ATangent, ANormal, ABiNormal);
  ABiNormal = BN;
  if(ABiNormal.Crossed(ATangent).Magnitude() > Precision::Confusion()) {
    ANormal = ABiNormal.Crossed(ATangent).Normalized();    
    ATangent = ANormal.Crossed(ABiNormal);
  }
  else {
    ATangent = ANormal.Crossed(ABiNormal).Normalized(); 
    ANormal = ABiNormal.Crossed(ATangent);
  }
}

 Standard_Boolean GeomFill_ConstantBiNormal::IsConstant() const
{
  return frenet->IsConstant();
}

 Standard_Boolean GeomFill_ConstantBiNormal::IsOnlyBy3dCurve() const
{
  GeomAbs_CurveType TheType = myCurve->GetType();
  gp_Ax1 TheAxe;

  switch  (TheType) {
  case GeomAbs_Circle:
    {
      TheAxe =  myCurve->Circle().Axis();
      break;
    }
  case GeomAbs_Ellipse:
    {
      TheAxe =  myCurve->Ellipse().Axis();
      break;
    }
  case GeomAbs_Hyperbola:
    {
      TheAxe =  myCurve->Hyperbola().Axis();
      break;
    }
  case GeomAbs_Parabola:
    {
      TheAxe =  myCurve->Parabola().Axis();
      break;
    }
  case GeomAbs_Line:
    { //La normale du plan de la courbe est il perpendiculaire a la BiNormale ?
     gp_Vec V;
     V.SetXYZ(myCurve->Line().Direction().XYZ());
     return V.IsNormal(BN, Precision::Angular());
    }
  default:
    return Standard_False; // pas de risques
  }

  // La normale du plan de la courbe est il // a la BiNormale ?
  gp_Vec V;
  V.SetXYZ(TheAxe.Direction().XYZ());
  return V.IsParallel(BN, Precision::Angular());
}
