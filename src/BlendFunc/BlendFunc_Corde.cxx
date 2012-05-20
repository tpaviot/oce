// Created on: 1996-06-04
// Created by: Stagiaire Xuan Trang PHAMPHU
// Copyright (c) 1996-1999 Matra Datavision
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


#include <BlendFunc_Corde.ixx>

#include <math_Gauss.hxx>

#include <ElCLib.hxx>
#include <gp.hxx>
#include <BlendFunc.hxx>
#include <Standard_DomainError.hxx>
#include <Standard_NotImplemented.hxx>


//=======================================================================
//function : BlendFunc_Corde
//purpose  : 
//=======================================================================

BlendFunc_Corde::BlendFunc_Corde(const Handle(Adaptor3d_HSurface)&   S,
                                 const Handle(Adaptor3d_HCurve)&     CG) :
    surf(S),guide(CG)
{
}

//=======================================================================
//function : SetDist
//purpose  : 
//=======================================================================

void BlendFunc_Corde::SetDist(const Standard_Real Dist)
{
  dis = Dist;
}

//=======================================================================
//function : SetParam
//purpose  : 
//=======================================================================

void BlendFunc_Corde::SetParam(const Standard_Real Param)
{
  guide->D2(Param,ptgui,d1gui,d2gui);
  normtg = d1gui.Magnitude();
  nplan  = d1gui.Normalized();
  theD = - (nplan.XYZ().Dot(ptgui.XYZ()));
}

//=======================================================================
//function : Value
//purpose  : returns F(U,V)
//=======================================================================

Standard_Boolean BlendFunc_Corde::Value(const math_Vector& X, math_Vector& F)
{
  gp_Vec d1u,d1v;
  surf->D1(X(1),X(2),pts,d1u,d1v);

  F(1) = nplan.XYZ().Dot(pts.XYZ()) + theD;
  const gp_Vec vref(ptgui,pts);
  F(2) = vref.SquareMagnitude() - dis*dis; 

  return Standard_True;
}

//=======================================================================
//function : Derivatives
//purpose  : D = grad F(U,V)
//=======================================================================

Standard_Boolean BlendFunc_Corde::Derivatives(const math_Vector& X, math_Matrix& D)
{
  gp_Vec d1u,d1v;
  surf->D1(X(1),X(2),pts,d1u,d1v);  

  D(1,1) = nplan.Dot(d1u);
  D(1,2) = nplan.Dot(d1v); 
  D(2,1) = 2.*gp_Vec(ptgui,pts).Dot(d1u);
  D(2,2) = 2.*gp_Vec(ptgui,pts).Dot(d1v);

  return Standard_True;
}

//=======================================================================
//function : PointOnS
//purpose  : 
//=======================================================================

const gp_Pnt& BlendFunc_Corde::PointOnS () const
{
  return pts;
}


//=======================================================================
//function : PointOnGuide
//purpose  : 
//=======================================================================

const gp_Pnt& BlendFunc_Corde::PointOnGuide () const
{
  return ptgui;
}


//=======================================================================
//function : Nplan
//purpose  : 
//=======================================================================

const gp_Vec& BlendFunc_Corde::NPlan () const
{
  return nplan;
}


//=======================================================================
//function : IsTangencyPoint
//purpose  : 
//=======================================================================

Standard_Boolean BlendFunc_Corde::IsTangencyPoint () const
{
  return istangent;
}


//=======================================================================
//function : TangentOnS
//purpose  : 
//=======================================================================

const gp_Vec& BlendFunc_Corde::TangentOnS () const
{
  if (istangent)
    Standard_DomainError::Raise("BlendFunc_Corde::TangentOnS");
  return tgs;
}


//=======================================================================
//function : Tangent2dOnS
//purpose  : 
//=======================================================================

const gp_Vec2d& BlendFunc_Corde::Tangent2dOnS () const
{
  if (istangent) 
    Standard_DomainError::Raise("BlendFunc_Corde::Tangent2dOnS");
  return tg2d;
}


//=======================================================================
//function : DerFguide
//purpose  : dF/dw
//=======================================================================

void BlendFunc_Corde::DerFguide (const math_Vector& Sol, gp_Vec2d& DerF)
{
  gp_Vec d1u,d1v;
  surf->D1(Sol(1),Sol(2),pts,d1u,d1v);

  gp_Vec dnplan;
  dnplan.SetLinearForm(1./normtg,d2gui,-1./normtg*(nplan.Dot(d2gui)),nplan);

  const gp_Vec temp(pts.XYZ()-ptgui.XYZ());

  DerF.SetX( dnplan.Dot(temp)-nplan.Dot(d1gui) );
  DerF.SetY( -2.*d1gui.Dot(temp) );
}

//=======================================================================
//function : IsSolution
//purpose  :
//=======================================================================

Standard_Boolean BlendFunc_Corde::IsSolution(const math_Vector& Sol, const Standard_Real Tol)
{
  math_Vector secmember(1,2),valsol(1,2);
  math_Matrix gradsol(1,2,1,2);

  gp_Vec dnplan,temp,d1u,d1v;

  Value(Sol,valsol);
  Derivatives(Sol,gradsol);
  if (Abs(valsol(1)) <= Tol &&
      Abs(valsol(2)) <= Tol*Tol) {

    surf->D1(Sol(1),Sol(2),pts,d1u,d1v);
    dnplan.SetLinearForm(1./normtg,d2gui,
			 -1./normtg*(nplan.Dot(d2gui)),nplan); 

    temp.SetXYZ(pts.XYZ()-ptgui.XYZ());

    secmember(1) = nplan.Dot(d1gui) - dnplan.Dot(temp);
    secmember(2) = 2.*d1gui.Dot(temp);

//  gradsol*der = secmember
//  with  der(1) = dU/dW, der(2) = dU/dW, W is the guide parameter

    math_Gauss Resol(gradsol);
    if (Resol.IsDone()) {
      Resol.Solve(secmember);
      tgs.SetLinearForm(secmember(1),d1u,secmember(2),d1v);
      tg2d.SetCoord(secmember(1),secmember(2));
      istangent = Standard_False;
    }
    else {
      istangent = Standard_True;
    }
    return Standard_True;
  }

  return Standard_False;
}
