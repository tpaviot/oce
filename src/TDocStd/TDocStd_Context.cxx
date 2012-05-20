// Created on: 1998-06-08
// Created by: Isabelle GRIGNON
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



#include <TDocStd_Context.ixx>

//=======================================================================
//function : TDocStd_Context
//purpose  : 
//=======================================================================

TDocStd_Context::TDocStd_Context():modifiedRef(Standard_False){}

//=======================================================================
//function : SetModifiedReferences
//purpose  : 
//=======================================================================

void TDocStd_Context::SetModifiedReferences(const Standard_Boolean Mod) {
  modifiedRef = Mod;
}

Standard_Boolean  TDocStd_Context::ModifiedReferences() const {
  return modifiedRef;
}
