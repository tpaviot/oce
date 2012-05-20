// Created on: 1991-04-17
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


#include <Expr_Difference.ixx>
#include <Expr_UnaryMinus.hxx>
#include <Expr_NumericValue.hxx>
#include <Expr_Sum.hxx>
#include <Expr_Operators.hxx>
#include <Expr.hxx>
#include <Standard_OutOfRange.hxx>

Expr_Difference::Expr_Difference (const Handle(Expr_GeneralExpression)& exp1, const Handle(Expr_GeneralExpression)& exp2)
{
  CreateFirstOperand(exp1);
  CreateSecondOperand(exp2);
}


Handle(Expr_GeneralExpression) Expr_Difference::ShallowSimplified() const
{
  Handle(Expr_GeneralExpression) myfirst = FirstOperand();
  Handle(Expr_GeneralExpression) mysecond = SecondOperand();

  Standard_Boolean nvfirst = myfirst->IsKind(STANDARD_TYPE(Expr_NumericValue));
  Standard_Boolean nvsecond = mysecond->IsKind(STANDARD_TYPE(Expr_NumericValue));
  if (nvfirst && nvsecond) {
    // case num1 - num2
    Handle(Expr_NumericValue) myNVfirst = Handle(Expr_NumericValue)::DownCast(myfirst);
    Handle(Expr_NumericValue) myNVsecond = Handle(Expr_NumericValue)::DownCast(mysecond);
    return new Expr_NumericValue(myNVfirst->GetValue()-myNVsecond->GetValue());
  }
  if (nvfirst && !nvsecond) {
    // case num1 - X2
    Handle(Expr_NumericValue) myNVfirst = Handle(Expr_NumericValue)::DownCast(myfirst);
    if (myNVfirst->GetValue() == 0.0) {
      // case 0 - X2
      return - mysecond;
    }
  }
  if (!nvfirst && nvsecond) {
    // case X1 - num2
    Handle(Expr_NumericValue) myNVsecond = Handle(Expr_NumericValue)::DownCast(mysecond);
    if (myNVsecond->GetValue() == 0.0) {
      // case X1 - 0
      return myfirst;
    }
  }
  // Treat UnaryMinus case
  Standard_Boolean unfirst = myfirst->IsKind(STANDARD_TYPE(Expr_UnaryMinus));
  Standard_Boolean unsecond = mysecond->IsKind(STANDARD_TYPE(Expr_UnaryMinus));
  if (unfirst && unsecond) {
    // case (-ssX1) - (-ssX2) = ssX2 - ssX1
    Handle(Expr_GeneralExpression) ssop1 = myfirst->SubExpression(1);
    Handle(Expr_GeneralExpression) ssop2 = mysecond->SubExpression(1);
    return ssop2 - ssop1;
  }
  if (unfirst && !unsecond) {
    // case (-ssX1) - X2 = -( ssX1 + X2)
    Handle(Expr_GeneralExpression) ssop1 = myfirst->SubExpression(1);
    return -(ssop1 + mysecond);
  }
  if (!unfirst && unsecond) {
    // case X1 - (-ssX2) = X1 + ssX2
    Handle(Expr_GeneralExpression) ssop2 = mysecond->SubExpression(1);
    return myfirst + ssop2;
  }
  Handle(Expr_Difference) me = this;
  return me;
}

Handle(Expr_GeneralExpression) Expr_Difference::Copy () const
{
  return Expr::CopyShare(FirstOperand()) - Expr::CopyShare(SecondOperand());
}

Standard_Boolean Expr_Difference::IsIdentical (const Handle(Expr_GeneralExpression)& Other) const
{
  Standard_Boolean ident = Standard_False;
  if (Other->IsKind(STANDARD_TYPE(Expr_Difference))) {
    Handle(Expr_GeneralExpression) myfirst = FirstOperand();
    Handle(Expr_GeneralExpression) mysecond = SecondOperand();
    Handle(Expr_Difference) DOther = Handle(Expr_Difference)::DownCast(Other);
    Handle(Expr_GeneralExpression) fother = DOther->FirstOperand();
    Handle(Expr_GeneralExpression) sother = DOther->SecondOperand();
    if ((myfirst->IsIdentical(fother)) &&
	(mysecond->IsIdentical(sother))) {
      ident = Standard_True;
    }
  }
  return ident;
}

Standard_Boolean Expr_Difference::IsLinear () const
{
  Handle(Expr_GeneralExpression) myfirst = FirstOperand();
  Handle(Expr_GeneralExpression) mysecond = SecondOperand();
  return (myfirst->IsLinear() && mysecond->IsLinear());
}

Handle(Expr_GeneralExpression) Expr_Difference::Derivative (const Handle(Expr_NamedUnknown)& X) const
{
  if (!Contains(X)) {
    return new Expr_NumericValue(0.0);
  }
  Handle(Expr_GeneralExpression) myfirst = FirstOperand();
  Handle(Expr_GeneralExpression) mysecond = SecondOperand();

  myfirst = myfirst->Derivative(X);
  mysecond = mysecond->Derivative(X);
  Handle(Expr_Difference) der = myfirst - mysecond;
  return der->ShallowSimplified();
}

Handle(Expr_GeneralExpression) Expr_Difference::NDerivative (const Handle(Expr_NamedUnknown)& X, const Standard_Integer N) const
{
  if (N <= 0) {
    Standard_OutOfRange::Raise();
  }
  if (!Contains(X)) {
    return new Expr_NumericValue(0.0);
  }
  Handle(Expr_GeneralExpression) myfirst = FirstOperand();
  Handle(Expr_GeneralExpression) mysecond = SecondOperand();

  myfirst = myfirst->NDerivative(X,N);
  mysecond = mysecond->NDerivative(X,N);
  Handle(Expr_Difference) der = myfirst - mysecond;
  return der->ShallowSimplified();
  
}


Standard_Real Expr_Difference::Evaluate(const Expr_Array1OfNamedUnknown& vars, const TColStd_Array1OfReal& vals) const
{
  Standard_Real res = FirstOperand()->Evaluate(vars,vals);
  return res - SecondOperand()->Evaluate(vars,vals);
}

TCollection_AsciiString Expr_Difference::String() const
{
  Handle(Expr_GeneralExpression) op1 = FirstOperand();
  Handle(Expr_GeneralExpression) op2 = SecondOperand();
  TCollection_AsciiString str;
  if (op1->NbSubExpressions() > 1) {
    str += "(";
    str += op1->String();
    str += ")";
  }
  else {
    str = op1->String();
  }
  str += "-";
  if (op2->NbSubExpressions() > 1) {
    str += "(";
    str += op2->String();
    str += ")";
  }
  else {
    str += op2->String();
  }
  return str;
}
