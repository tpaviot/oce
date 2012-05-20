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


#include <StepAP214_AutoDesignDatedItem.ixx>
#include <Interface_Macros.hxx>

StepAP214_AutoDesignDatedItem::StepAP214_AutoDesignDatedItem () {  }

Standard_Integer StepAP214_AutoDesignDatedItem::CaseNum(const Handle(Standard_Transient)& ent) const
{
	if (ent.IsNull()) return 0;
	if (ent->IsKind(STANDARD_TYPE(StepBasic_ApprovalPersonOrganization))) return 1;
	if (ent->IsKind(STANDARD_TYPE(StepAP214_AutoDesignDateAndPersonAssignment))) return 2;
	if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionEffectivity))) return 3;
	return 0;
}

Handle(StepBasic_ApprovalPersonOrganization) StepAP214_AutoDesignDatedItem::ApprovalPersonOrganization () const
{
	return GetCasted(StepBasic_ApprovalPersonOrganization,Value());
}

Handle(StepAP214_AutoDesignDateAndPersonAssignment) StepAP214_AutoDesignDatedItem::AutoDesignDateAndPersonAssignment () const
{
	return GetCasted(StepAP214_AutoDesignDateAndPersonAssignment,Value());
}

Handle(StepBasic_ProductDefinitionEffectivity)  StepAP214_AutoDesignDatedItem::ProductDefinitionEffectivity () const
{
  return GetCasted(StepBasic_ProductDefinitionEffectivity,Value());
}
