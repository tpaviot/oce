// Created on: 2000-05-10
// Created by: Andrey BETENEV
// Copyright (c) 2000-2012 OPEN CASCADE SAS
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

// Generator:	ExpToCas (EXPRESS -> CASCADE/XSTEP Translator) V1.1

#include <StepBasic_RoleSelect.ixx>

//=======================================================================
//function : StepBasic_RoleSelect
//purpose  : 
//=======================================================================

StepBasic_RoleSelect::StepBasic_RoleSelect ()
{
}

//=======================================================================
//function : CaseNum
//purpose  : 
//=======================================================================

Standard_Integer StepBasic_RoleSelect::CaseNum (const Handle(Standard_Transient)& ent) const
{
  if (ent.IsNull()) return 0;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ActionAssignment))) return 1;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ActionRequestAssignment))) return 2;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ApprovalAssignment))) return 3;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ApprovalDateTime))) return 4;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_CertificationAssignment))) return 5;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ContractAssignment))) return 6;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_DocumentReference))) return 7;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_EffectivityAssignment))) return 8;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_GroupAssignment))) return 9;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_NameAssignment))) return 10;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_SecurityClassificationAssignment))) return 11;
  return 0;
}

//=======================================================================
//function : ActionAssignment
//purpose  : 
//=======================================================================

Handle(StepBasic_ActionAssignment) StepBasic_RoleSelect::ActionAssignment () const
{
  return Handle(StepBasic_ActionAssignment)::DownCast(Value());
}

//=======================================================================
//function : ActionRequestAssignment
//purpose  : 
//=======================================================================

Handle(StepBasic_ActionRequestAssignment) StepBasic_RoleSelect::ActionRequestAssignment () const
{
  return Handle(StepBasic_ActionRequestAssignment)::DownCast(Value());
}

//=======================================================================
//function : ApprovalAssignment
//purpose  : 
//=======================================================================

Handle(StepBasic_ApprovalAssignment) StepBasic_RoleSelect::ApprovalAssignment () const
{
  return Handle(StepBasic_ApprovalAssignment)::DownCast(Value());
}

//=======================================================================
//function : ApprovalDateTime
//purpose  : 
//=======================================================================

Handle(StepBasic_ApprovalDateTime) StepBasic_RoleSelect::ApprovalDateTime () const
{
  return Handle(StepBasic_ApprovalDateTime)::DownCast(Value());
}

//=======================================================================
//function : CertificationAssignment
//purpose  : 
//=======================================================================

Handle(StepBasic_CertificationAssignment) StepBasic_RoleSelect::CertificationAssignment () const
{
  return Handle(StepBasic_CertificationAssignment)::DownCast(Value());
}

//=======================================================================
//function : ContractAssignment
//purpose  : 
//=======================================================================

Handle(StepBasic_ContractAssignment) StepBasic_RoleSelect::ContractAssignment () const
{
  return Handle(StepBasic_ContractAssignment)::DownCast(Value());
}

//=======================================================================
//function : DocumentReference
//purpose  : 
//=======================================================================

Handle(StepBasic_DocumentReference) StepBasic_RoleSelect::DocumentReference () const
{
  return Handle(StepBasic_DocumentReference)::DownCast(Value());
}

//=======================================================================
//function : EffectivityAssignment
//purpose  : 
//=======================================================================

Handle(StepBasic_EffectivityAssignment) StepBasic_RoleSelect::EffectivityAssignment () const
{
  return Handle(StepBasic_EffectivityAssignment)::DownCast(Value());
}

//=======================================================================
//function : GroupAssignment
//purpose  : 
//=======================================================================

Handle(StepBasic_GroupAssignment) StepBasic_RoleSelect::GroupAssignment () const
{
  return Handle(StepBasic_GroupAssignment)::DownCast(Value());
}

//=======================================================================
//function : NameAssignment
//purpose  : 
//=======================================================================

Handle(StepBasic_NameAssignment) StepBasic_RoleSelect::NameAssignment () const
{
  return Handle(StepBasic_NameAssignment)::DownCast(Value());
}

//=======================================================================
//function : SecurityClassificationAssignment
//purpose  : 
//=======================================================================

Handle(StepBasic_SecurityClassificationAssignment) StepBasic_RoleSelect::SecurityClassificationAssignment () const
{
  return Handle(StepBasic_SecurityClassificationAssignment)::DownCast(Value());
}
