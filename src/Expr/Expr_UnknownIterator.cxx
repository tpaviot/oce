// Created on: 1991-09-18
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


#include <Expr_UnknownIterator.ixx>
#include <Standard_NoMoreObject.hxx>
#include <Standard_NoSuchObject.hxx>
#include <Expr.hxx>

Expr_UnknownIterator::Expr_UnknownIterator (const Handle(Expr_GeneralExpression)& exp)
{
  Perform(exp);
  myCurrent = 1;
}

void Expr_UnknownIterator::Perform(const Handle(Expr_GeneralExpression)& exp)
{
  if (exp->IsKind(STANDARD_TYPE(Expr_NamedUnknown))) {
    Handle(Expr_NamedUnknown) varexp = Handle(Expr_NamedUnknown)::DownCast(exp);
    if (!myMap.Contains(varexp)) {
      myMap.Add(varexp);
    }
  }
  Standard_Integer nbsub = exp->NbSubExpressions();
  for (Standard_Integer i = 1; i <= nbsub ; i++) {
    Perform(exp->SubExpression(i));
  }
}

Standard_Boolean Expr_UnknownIterator::More() const
{
  return (myCurrent <= myMap.Extent());
}

void Expr_UnknownIterator::Next ()
{
  if (!More()) {
    Standard_NoMoreObject::Raise();
  }
  myCurrent++;
}

Handle(Expr_NamedUnknown) Expr_UnknownIterator::Value () const
{
  return myMap(myCurrent);
}

