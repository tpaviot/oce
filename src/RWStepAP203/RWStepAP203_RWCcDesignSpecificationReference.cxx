// Created on: 1999-11-26
// Created by: Andrey BETENEV
// Copyright (c) 1999 Matra Datavision
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

// Generator:	ExpToCas (EXPRESS -> CASCADE/XSTEP Translator) V1.0

#include <RWStepAP203_RWCcDesignSpecificationReference.ixx>
#include <StepAP203_HArray1OfSpecifiedItem.hxx>
#include <StepAP203_SpecifiedItem.hxx>

//=======================================================================
//function : RWStepAP203_RWCcDesignSpecificationReference
//purpose  : 
//=======================================================================

RWStepAP203_RWCcDesignSpecificationReference::RWStepAP203_RWCcDesignSpecificationReference ()
{
}

//=======================================================================
//function : ReadStep
//purpose  : 
//=======================================================================

void RWStepAP203_RWCcDesignSpecificationReference::ReadStep (const Handle(StepData_StepReaderData)& data,
                                                             const Standard_Integer num,
                                                             Handle(Interface_Check)& ach,
                                                             const Handle(StepAP203_CcDesignSpecificationReference) &ent) const
{
  // Check number of parameters
  if ( ! data->CheckNbParams(num,3,ach,"cc_design_specification_reference") ) return;

  // Inherited fields of DocumentReference

  Handle(StepBasic_Document) aDocumentReference_AssignedDocument;
  data->ReadEntity (num, 1, "document_reference.assigned_document", ach, STANDARD_TYPE(StepBasic_Document), aDocumentReference_AssignedDocument);

  Handle(TCollection_HAsciiString) aDocumentReference_Source;
  data->ReadString (num, 2, "document_reference.source", ach, aDocumentReference_Source);

  // Own fields of CcDesignSpecificationReference

  Handle(StepAP203_HArray1OfSpecifiedItem) aItems;
  Standard_Integer sub3 = 0;
  if ( data->ReadSubList (num, 3, "items", ach, sub3) ) {
    Standard_Integer num2 = sub3;
    Standard_Integer nb0 = data->NbParams(num2);
    aItems = new StepAP203_HArray1OfSpecifiedItem (1, nb0);
    for ( Standard_Integer i0=1; i0 <= nb0; i0++ ) {
      StepAP203_SpecifiedItem anIt0;
      data->ReadEntity (num2, i0, "items", ach, anIt0);
      aItems->SetValue(i0, anIt0);
    }
  }

  // Initialize entity
  ent->Init(aDocumentReference_AssignedDocument,
            aDocumentReference_Source,
            aItems);
}

//=======================================================================
//function : WriteStep
//purpose  : 
//=======================================================================

void RWStepAP203_RWCcDesignSpecificationReference::WriteStep (StepData_StepWriter& SW,
                                                              const Handle(StepAP203_CcDesignSpecificationReference) &ent) const
{

  // Inherited fields of DocumentReference

  SW.Send (ent->StepBasic_DocumentReference::AssignedDocument());

  SW.Send (ent->StepBasic_DocumentReference::Source());

  // Own fields of CcDesignSpecificationReference

  SW.OpenSub();
  for (Standard_Integer i2=1; i2 <= ent->Items()->Length(); i2++ ) {
    StepAP203_SpecifiedItem Var0 = ent->Items()->Value(i2);
    SW.Send (Var0.Value());
  }
  SW.CloseSub();
}

//=======================================================================
//function : Share
//purpose  : 
//=======================================================================

void RWStepAP203_RWCcDesignSpecificationReference::Share (const Handle(StepAP203_CcDesignSpecificationReference) &ent,
                                                          Interface_EntityIterator& iter) const
{

  // Inherited fields of DocumentReference

  iter.AddItem (ent->StepBasic_DocumentReference::AssignedDocument());

  // Own fields of CcDesignSpecificationReference

  for (Standard_Integer i2=1; i2 <= ent->Items()->Length(); i2++ ) {
    StepAP203_SpecifiedItem Var0 = ent->Items()->Value(i2);
    iter.AddItem (Var0.Value());
  }
}
