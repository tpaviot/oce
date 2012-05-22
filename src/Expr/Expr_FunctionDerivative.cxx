// Created on: 1991-06-27
// Created by: Arnaud BOUZY
// Copyright (c) 1991-1999 Matra Datavision
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


#include <Expr_FunctionDerivative.ixx>
#include <Expr_NumericValue.hxx>
#include <Expr_NamedFunction.hxx>
#include <Standard_OutOfRange.hxx>
#include <Standard_NotImplemented.hxx>

Expr_FunctionDerivative::Expr_FunctionDerivative (const Handle(Expr_GeneralFunction)& func, const Handle(Expr_NamedUnknown)& withX, const Standard_Integer deg)
{
  myFunction = func;
  myDerivate = withX;
  if (deg <= 0) {
    Standard_OutOfRange::Raise();
  }
  myDegree = deg;
  UpdateExpression();
}

Standard_Integer Expr_FunctionDerivative::NbOfVariables () const
{
  return myFunction->NbOfVariables();
}

Handle(Expr_NamedUnknown) Expr_FunctionDerivative::Variable (const Standard_Integer index) const
{
  return myFunction->Variable(index);
}

Standard_Real Expr_FunctionDerivative::Evaluate (const Expr_Array1OfNamedUnknown& vars, const TColStd_Array1OfReal& values) const
{
  if (vars.Length() != values.Length()) {
    Standard_OutOfRange::Raise();
  }
  return myExp->Evaluate(vars,values);
}

Handle(Expr_GeneralFunction) Expr_FunctionDerivative::Copy () const
{
  return new Expr_FunctionDerivative(myFunction->Copy(),myDerivate,myDegree);
}

Handle(Expr_GeneralFunction) Expr_FunctionDerivative::Derivative(const Handle(Expr_NamedUnknown)& var) const
{
  return Derivative(var,1);
}

Handle(Expr_GeneralFunction) Expr_FunctionDerivative::Derivative(const Handle(Expr_NamedUnknown)& var, const Standard_Integer deg) const
{
  if (var == myDerivate) {
    return new Expr_FunctionDerivative(myFunction,var,myDegree+deg);
  }
  Handle(Expr_FunctionDerivative) me = this;
  return new Expr_FunctionDerivative(me,var,deg);
}

Standard_Boolean Expr_FunctionDerivative::IsIdentical (const Handle(Expr_GeneralFunction)& func) const
{
  if (!func->IsKind(STANDARD_TYPE(Expr_FunctionDerivative))) {
    return Standard_False;
  }
  Handle(Expr_FunctionDerivative) dfunc = Handle(Expr_FunctionDerivative)::DownCast(func);
  if (myDegree != dfunc->Degree()) {
    return Standard_False;
  }
  if (!myDerivate->IsIdentical(dfunc->DerivVariable())) {
    return Standard_False;
  }
  if (!myFunction->IsIdentical(dfunc->Function())) {
    return Standard_False;
  }
  return Standard_True;
}

Standard_Boolean Expr_FunctionDerivative::IsLinearOnVariable(const Standard_Integer) const
{
  // should be improved
  return myExp->IsLinear();
}

Handle(Expr_GeneralFunction) Expr_FunctionDerivative::Function () const
{
  return myFunction;
}

Standard_Integer Expr_FunctionDerivative::Degree () const
{
  return myDegree;
}

Handle(Expr_NamedUnknown) Expr_FunctionDerivative::DerivVariable () const
{
  return myDerivate;
}


TCollection_AsciiString Expr_FunctionDerivative::GetStringName() const
{
  TCollection_AsciiString res;
  if (NbOfVariables() ==1) {
    res = myFunction->GetStringName();
    char c = 39;
    TCollection_AsciiString diff(myDegree,c);
    res += diff;
    return res;
  }
  TCollection_AsciiString diff("@");
  if (myDegree > 1) {
    TCollection_AsciiString deg(myDegree);
    diff += deg;
  }
  res = diff;
  res += myFunction->GetStringName();
  res += "/";
  Standard_Integer index=0;
  for (Standard_Integer i=1; (i<= NbOfVariables()) && (index ==0) ; i++) {
    if (Variable(i) == myDerivate) {
      index =i;
    }
  }
  res += diff;
  res += "X";
  TCollection_AsciiString rank(index);
  res += rank;
  return res;
}    


Handle(Expr_GeneralExpression) Expr_FunctionDerivative::Expression() const
{
  return myExp;
}

void Expr_FunctionDerivative::UpdateExpression()
{
  if (myFunction->IsKind(STANDARD_TYPE(Expr_FunctionDerivative))) {
    Handle(Expr_FunctionDerivative) defunc = Handle(Expr_FunctionDerivative)::DownCast(myFunction);
    defunc->UpdateExpression();
    myExp = defunc->Expression()->NDerivative(myDerivate,myDegree);
  }
  else {
    Handle(Expr_NamedFunction) nafunc = Handle(Expr_NamedFunction)::DownCast(myFunction);
    myExp = nafunc->Expression()->NDerivative(myDerivate,myDegree);
  }
}
