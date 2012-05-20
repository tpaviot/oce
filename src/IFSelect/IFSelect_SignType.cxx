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

#include <IFSelect_SignType.ixx>
#include <Standard_Type.hxx>
#include <Interface_Macros.hxx>

static Standard_CString nulsign = "";


    IFSelect_SignType::IFSelect_SignType (const Standard_Boolean nopk)
    : IFSelect_Signature ((Standard_CString ) (nopk ? "Class Type" : "Dynamic Type") ) ,
      thenopk (nopk)
{}

    Standard_CString IFSelect_SignType::Value
  (const Handle(Standard_Transient)& ent,
   const Handle(Interface_InterfaceModel)& model) const
{
  if (ent.IsNull()) return nulsign;
  DeclareAndCast(Standard_Type,atype,ent);
  if (atype.IsNull()) atype = ent->DynamicType();
  Standard_CString tn = atype->Name();
  if (!thenopk) return tn;
  for (int i = 0; tn[i] != '\0'; i ++) {
    if (tn[i] == '_') return &tn[i+1];
  }
  return tn;
}
