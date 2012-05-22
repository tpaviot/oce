// Created on: 1997-03-06
// Created by: Robert COUBLANC
// Copyright (c) 1997-1999 Matra Datavision
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



#include <AIS_TypeFilter.ixx>
#include <AIS_InteractiveObject.hxx>

AIS_TypeFilter::AIS_TypeFilter(const AIS_KindOfInteractive TheKind):
myKind(TheKind){}

Standard_Boolean AIS_TypeFilter::IsOk(const Handle(SelectMgr_EntityOwner)& anObj) const 
{
  if(Handle(AIS_InteractiveObject)::DownCast(anObj->Selectable()).IsNull()) 
    return Standard_False;
  
//#ifndef DEB
  Handle_SelectMgr_SelectableObject aSelectableObject = anObj->Selectable() ;
  return ((Handle(AIS_InteractiveObject)&) aSelectableObject)->Type()== myKind;
//#else
//  return ((Handle(AIS_InteractiveObject)&)anObj->Selectable())->Type()== myKind;
//#endif
}
