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


#include <StepAP214_ApprovalItem.ixx>
#include <Interface_Macros.hxx>

StepAP214_ApprovalItem::StepAP214_ApprovalItem () {  }

Standard_Integer StepAP214_ApprovalItem::CaseNum(const Handle(Standard_Transient)& ent) const
{
	
  if (ent.IsNull()) return 0;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_AssemblyComponentUsageSubstitute))) return 1;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_DocumentFile))) return 2;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_MaterialDesignation))) return 3;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_MechanicalDesignGeometricPresentationRepresentation))) return 4;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_PresentationArea))) return 5;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_Product))) return 6;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinition))) return 7;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionFormation))) return 8;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_ProductDefinitionRelationship))) return 9;
  if (ent->IsKind(STANDARD_TYPE(StepRepr_PropertyDefinition))) return 10;
  if (ent->IsKind(STANDARD_TYPE(StepShape_ShapeRepresentation))) return 11;
  if (ent->IsKind(STANDARD_TYPE(StepBasic_SecurityClassification))) return 12;
	
	return 0;
}


Handle(StepRepr_AssemblyComponentUsageSubstitute)  StepAP214_ApprovalItem::AssemblyComponentUsageSubstitute() const
{  return GetCasted(StepRepr_AssemblyComponentUsageSubstitute,Value());  }

Handle(StepBasic_DocumentFile) StepAP214_ApprovalItem::DocumentFile() const
{  return GetCasted(StepBasic_DocumentFile,Value());  }


Handle(StepRepr_MaterialDesignation) StepAP214_ApprovalItem::MaterialDesignation() const
{  return GetCasted(StepRepr_MaterialDesignation,Value());  }

Handle(StepVisual_MechanicalDesignGeometricPresentationRepresentation) StepAP214_ApprovalItem::MechanicalDesignGeometricPresentationRepresentation() const
{  return GetCasted(StepVisual_MechanicalDesignGeometricPresentationRepresentation,Value());  }

Handle(StepVisual_PresentationArea) StepAP214_ApprovalItem::PresentationArea() const
{  return GetCasted(StepVisual_PresentationArea,Value());  }

Handle(StepBasic_Product) StepAP214_ApprovalItem::Product() const
{  return GetCasted(StepBasic_Product,Value());  }

Handle(StepBasic_ProductDefinition) StepAP214_ApprovalItem::ProductDefinition () const
{  return GetCasted(StepBasic_ProductDefinition,Value());  }

Handle(StepBasic_ProductDefinitionFormation) StepAP214_ApprovalItem::ProductDefinitionFormation() const
{  return GetCasted(StepBasic_ProductDefinitionFormation,Value());  }

Handle(StepBasic_ProductDefinitionRelationship) StepAP214_ApprovalItem::ProductDefinitionRelationship() const
{  return GetCasted(StepBasic_ProductDefinitionRelationship,Value());  }

Handle(StepRepr_PropertyDefinition) StepAP214_ApprovalItem::PropertyDefinition() const
{  return GetCasted(StepRepr_PropertyDefinition,Value());  }

Handle(StepShape_ShapeRepresentation) StepAP214_ApprovalItem::ShapeRepresentation() const
{  return GetCasted(StepShape_ShapeRepresentation,Value());  }

Handle(StepBasic_SecurityClassification) StepAP214_ApprovalItem::SecurityClassification() const
{  return GetCasted(StepBasic_SecurityClassification,Value());  }
