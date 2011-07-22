// File:	GeomFill_BoundWithSurf.cxx
// Created:	Thu Oct 19 14:52:52 1995
// Author:	Laurent BOURESCHE
//		<lbo@phylox>


#include <GeomFill_BoundWithSurf.ixx>
#include <Law.hxx>
#include <Law_BSpFunc.hxx>
#include <Adaptor3d_HSurface.hxx>
#include <Adaptor2d_HCurve2d.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Vec2d.hxx>
//=======================================================================
//function : GeomFill_BoundWithSurf
//purpose  : 
//=======================================================================

GeomFill_BoundWithSurf::GeomFill_BoundWithSurf
(const Adaptor3d_CurveOnSurface& CurveOnSurf,
 const Standard_Real           Tol3d,
 const Standard_Real           Tolang) :
 GeomFill_Boundary(Tol3d,Tolang), myConS(CurveOnSurf)
{
}


//=======================================================================
//function : Value
//purpose  : 
//=======================================================================

gp_Pnt GeomFill_BoundWithSurf::Value(const Standard_Real U) const 
{
  Standard_Real x = U;
  if(!myPar.IsNull()) x = myPar->Value(U);
  return myConS.Value(x);
}


//=======================================================================
//function : D1
//purpose  : 
//=======================================================================

void GeomFill_BoundWithSurf::D1(const Standard_Real U, 
				gp_Pnt& P, 
				gp_Vec& V) const 
{
  Standard_Real x = U, dx = 1.;
  if(!myPar.IsNull()) myPar->D1(U,x,dx);
  myConS.D1(x, P, V);
  V.Multiply(dx);
}


//=======================================================================
//function : HasNormals
//purpose  : 
//=======================================================================

Standard_Boolean GeomFill_BoundWithSurf::HasNormals() const 
{
  return Standard_True;
}


//=======================================================================
//function : Norm
//purpose  : 
//=======================================================================

gp_Vec GeomFill_BoundWithSurf::Norm(const Standard_Real U) const 
{
  // voir s il ne faudrait pas utiliser LProp ou autre.
  if (!HasNormals()) 
    Standard_Failure::Raise("BoundWithSurf Norm : pas de contrainte");

//  Handle(Adaptor3d_HSurface)& S = myConS.GetSurface();
//  Handle(Adaptor2d_HCurve2d)& C2d = myConS.GetCurve();
  Standard_Real x,y;
  Standard_Real w = U;
  if(!myPar.IsNull()) w = myPar->Value(U);
  myConS.GetCurve()->Value(w).Coord(x,y);
  gp_Pnt P;
  gp_Vec Su, Sv;
  myConS.GetSurface()->D1(x,y,P,Su,Sv);
  Su.Cross(Sv);
  Su.Normalize();
  return Su;
}


//=======================================================================
//function : D1Norm
//purpose  : 
//=======================================================================

void GeomFill_BoundWithSurf::D1Norm(const Standard_Real U,
				    gp_Vec&             N,
				    gp_Vec&             DN) const 
{
  if (!HasNormals()) 
    Standard_Failure::Raise("BoundWithSurf Norm : pas de contrainte");
//  Handle(Adaptor3d_HSurface)& S = myConS.GetSurface();
//  Handle(Adaptor2d_HCurve2d)& C2d = myConS.GetCurve();
  gp_Pnt2d P2d;
  gp_Vec2d V2d;
  Standard_Real x,y,dx,dy;
  Standard_Real w = U, dw = 1.;
  if(!myPar.IsNull()) myPar->D1(U,w,dw);
  myConS.GetCurve()->D1(w,P2d,V2d);
  P2d.Coord(x,y);
  V2d.Multiply(dw);
  V2d.Coord(dx,dy);
  gp_Pnt P;
  gp_Vec Su, Sv, Suu, Suv, Svv;
  myConS.GetSurface()->D2(x,y,P,Su,Sv, Suu, Svv, Suv);
  N = Su.Crossed(Sv);
  N.Normalize();
  Standard_Real nsuu = N.Dot(Suu), nsuv = N.Dot(Suv), nsvv = N.Dot(Svv);
  Standard_Real susu = Su.Dot(Su), susv = Su.Dot(Sv), svsv = Sv.Dot(Sv);
  Standard_Real deno = (susu*svsv) - (susv*susv);
  if(Abs(deno) < 1.e-16) {
    // on embraye sur un calcul approche, c est mieux que rien!?!
    gp_Vec temp = Norm(U + 1.e-12);
    DN = N.Multiplied(-1.);
    DN.Add(temp);
    DN.Multiply(1.e-12);
  }
  else{
    Standard_Real a = (-nsuu*svsv + nsuv*susv)/deno;
    Standard_Real b = ( nsuu*susv - nsuv*susu)/deno;
    Standard_Real c = (-nsuv*svsv + nsvv*susv)/deno;
    Standard_Real d = ( nsuv*susv - nsvv*susu)/deno;

    gp_Vec temp1 = Su.Multiplied(a);
    gp_Vec temp2 = Sv.Multiplied(b);
    temp1.Add(temp2);
    temp2        = Su.Multiplied(c);
    gp_Vec temp3 = Sv.Multiplied(d);
    temp2.Add(temp3);
    temp1.Multiply(dx);
    temp2.Multiply(dy);
    DN = temp1.Added(temp2);
  }
}


//=======================================================================
//function : Reparametrize
//purpose  : 
//=======================================================================

void GeomFill_BoundWithSurf::Reparametrize(const Standard_Real First, 
					   const Standard_Real Last,
					   const Standard_Boolean HasDF, 
					   const Standard_Boolean HasDL, 
					   const Standard_Real DF, 
					   const Standard_Real DL,
					   const Standard_Boolean Rev)
{
  Handle(Law_BSpline) curve = Law::Reparametrize(myConS,
						 First,Last,
						 HasDF,HasDL,DF,DL,
						 Rev,30);
  myPar = new Law_BSpFunc();
  (*((Handle_Law_BSpFunc*) &myPar))->SetCurve(curve);
}

//=======================================================================
//function : Bounds
//purpose  : 
//=======================================================================

void GeomFill_BoundWithSurf::Bounds(Standard_Real& First, 
				    Standard_Real& Last) const 
{
  if(!myPar.IsNull()) myPar->Bounds(First,Last);
  else{
    First = myConS.FirstParameter();
    Last  = myConS.LastParameter();
  }
}


//=======================================================================
//function : IsDegenerated
//purpose  : 
//=======================================================================

Standard_Boolean GeomFill_BoundWithSurf::IsDegenerated() const 
{
  return Standard_False;
}
