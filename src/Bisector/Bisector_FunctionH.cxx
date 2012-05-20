// Created on: 1994-04-05
// Created by: Yves FRICAUD
// Copyright (c) 1994-1999 Matra Datavision
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



#include <Bisector_FunctionH.ixx>
#include <Geom2d_Curve.hxx>

//=============================================================================
//function :
// purpose :
//=============================================================================
Bisector_FunctionH::Bisector_FunctionH (const Handle(Geom2d_Curve)& C2,
					const gp_Pnt2d&             P1,
					const gp_Vec2d&             T1)
     :p1(P1),t1(T1)
{
  t1.Normalize();
  curve2 = C2;
}

//=============================================================================
//function : Value
// purpose :
//                F = P1P2.(||T2||T1 + T2)
//=============================================================================
Standard_Boolean Bisector_FunctionH::Value (const Standard_Real  X,
					          Standard_Real& F)
{
  gp_Pnt2d P2  ;      // point sur C2. 
  gp_Vec2d T2  ;      // tangente a C2 en V.
  curve2->D1(X,P2,T2);  

  Standard_Real NormT2 = T2.Magnitude();
  Standard_Real Ax     = NormT2*t1.X() - T2.X();
  Standard_Real Ay     = NormT2*t1.Y() - T2.Y();

  F = (p1.X() - P2.X())*Ax + (p1.Y() - P2.Y())*Ay;

  return Standard_True;
}

//=============================================================================
//function : Derivative
// purpose :
//=============================================================================
Standard_Boolean Bisector_FunctionH::Derivative(const Standard_Real  X,
						      Standard_Real& D)
{
  Standard_Real F;
  return Values (X,F,D);
}

//=============================================================================
//function : Values
// purpose :
//=============================================================================
Standard_Boolean Bisector_FunctionH::Values (const Standard_Real  X,
					           Standard_Real& F,
					           Standard_Real& D)
{
  gp_Pnt2d P2  ;      // point sur C2. 
  gp_Vec2d T2  ;      // tangente a C2 en V.
  gp_Vec2d T2v ;      // derivee seconde a C2 en V.

  curve2->D2(X,P2,T2,T2v); 
 
  Standard_Real NormT2 = T2.Magnitude();
  Standard_Real Ax     = NormT2*t1.X() - T2.X();
  Standard_Real Ay     = NormT2*t1.Y() - T2.Y();

  F = (p1.X() - P2.X())*Ax + (p1.Y() - P2.Y())*Ay;

  Standard_Real Scal = T2.Dot(T2v)/NormT2;
  Standard_Real dAx  = Scal*t1.X() - T2v.X();
  Standard_Real dAy  = Scal*t1.Y() - T2v.Y();
  
  D = - T2.X()*Ax - T2.Y()*Ay + (p1.X() - P2.X())*dAx + (p1.Y() - P2.Y())*dAy;
  

  return Standard_True;

}

