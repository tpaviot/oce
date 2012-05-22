// Created on: 2002-12-12
// Created by: data exchange team
// Copyright (c) 2002-2012 OPEN CASCADE SAS
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

// Generator:	ExpToCas (EXPRESS -> CASCADE/XSTEP Translator) V1.2

#include <RWStepFEA_RWVolume3dElementRepresentation.ixx>
#include <StepRepr_HArray1OfRepresentationItem.hxx>
#include <StepRepr_RepresentationItem.hxx>
#include <StepFEA_HArray1OfNodeRepresentation.hxx>
#include <StepFEA_NodeRepresentation.hxx>

//=======================================================================
//function : RWStepFEA_RWVolume3dElementRepresentation
//purpose  : 
//=======================================================================

RWStepFEA_RWVolume3dElementRepresentation::RWStepFEA_RWVolume3dElementRepresentation ()
{
}

//=======================================================================
//function : ReadStep
//purpose  : 
//=======================================================================

void RWStepFEA_RWVolume3dElementRepresentation::ReadStep (const Handle(StepData_StepReaderData)& data,
                                                          const Standard_Integer num,
                                                          Handle(Interface_Check)& ach,
                                                          const Handle(StepFEA_Volume3dElementRepresentation) &ent) const
{
  // Check number of parameters
  if ( ! data->CheckNbParams(num,7,ach,"volume3d_element_representation") ) return;

  // Inherited fields of Representation

  Handle(TCollection_HAsciiString) aRepresentation_Name;
  data->ReadString (num, 1, "representation.name", ach, aRepresentation_Name);

  Handle(StepRepr_HArray1OfRepresentationItem) aRepresentation_Items;
  Standard_Integer sub2 = 0;
  if ( data->ReadSubList (num, 2, "representation.items", ach, sub2) ) {
    Standard_Integer nb0 = data->NbParams(sub2);
    aRepresentation_Items = new StepRepr_HArray1OfRepresentationItem (1, nb0);
    Standard_Integer num2 = sub2;
    for ( Standard_Integer i0=1; i0 <= nb0; i0++ ) {
      Handle(StepRepr_RepresentationItem) anIt0;
      data->ReadEntity (num2, i0, "representation_item", ach, STANDARD_TYPE(StepRepr_RepresentationItem), anIt0);
      aRepresentation_Items->SetValue(i0, anIt0);
    }
  }

  Handle(StepRepr_RepresentationContext) aRepresentation_ContextOfItems;
  data->ReadEntity (num, 3, "representation.context_of_items", ach, STANDARD_TYPE(StepRepr_RepresentationContext), aRepresentation_ContextOfItems);

  // Inherited fields of ElementRepresentation

  Handle(StepFEA_HArray1OfNodeRepresentation) aElementRepresentation_NodeList;
  Standard_Integer sub4 = 0;
  if ( data->ReadSubList (num, 4, "element_representation.node_list", ach, sub4) ) {
    Standard_Integer nb0 = data->NbParams(sub4);
    aElementRepresentation_NodeList = new StepFEA_HArray1OfNodeRepresentation (1, nb0);
    Standard_Integer num2 = sub4;
    for ( Standard_Integer i0=1; i0 <= nb0; i0++ ) {
      Handle(StepFEA_NodeRepresentation) anIt0;
      data->ReadEntity (num2, i0, "node_representation", ach, STANDARD_TYPE(StepFEA_NodeRepresentation), anIt0);
      aElementRepresentation_NodeList->SetValue(i0, anIt0);
    }
  }

  // Own fields of Volume3dElementRepresentation

  Handle(StepFEA_FeaModel3d) aModelRef;
  data->ReadEntity (num, 5, "model_ref", ach, STANDARD_TYPE(StepFEA_FeaModel3d), aModelRef);

  Handle(StepElement_Volume3dElementDescriptor) aElementDescriptor;
  data->ReadEntity (num, 6, "element_descriptor", ach, STANDARD_TYPE(StepElement_Volume3dElementDescriptor), aElementDescriptor);

  Handle(StepElement_ElementMaterial) aMaterial;
  data->ReadEntity (num, 7, "material", ach, STANDARD_TYPE(StepElement_ElementMaterial), aMaterial);

  // Initialize entity
  ent->Init(aRepresentation_Name,
            aRepresentation_Items,
            aRepresentation_ContextOfItems,
            aElementRepresentation_NodeList,
            aModelRef,
            aElementDescriptor,
            aMaterial);
}

//=======================================================================
//function : WriteStep
//purpose  : 
//=======================================================================

void RWStepFEA_RWVolume3dElementRepresentation::WriteStep (StepData_StepWriter& SW,
                                                           const Handle(StepFEA_Volume3dElementRepresentation) &ent) const
{

  // Inherited fields of Representation

  SW.Send (ent->StepRepr_Representation::Name());

  SW.OpenSub();
  for (Standard_Integer i1=1; i1 <= ent->StepRepr_Representation::Items()->Length(); i1++ ) {
    Handle(StepRepr_RepresentationItem) Var0 = ent->StepRepr_Representation::Items()->Value(i1);
    SW.Send (Var0);
  }
  SW.CloseSub();

  SW.Send (ent->StepRepr_Representation::ContextOfItems());

  // Inherited fields of ElementRepresentation

  SW.OpenSub();
  for (Standard_Integer i3=1; i3 <= ent->StepFEA_ElementRepresentation::NodeList()->Length(); i3++ ) {
    Handle(StepFEA_NodeRepresentation) Var0 = ent->StepFEA_ElementRepresentation::NodeList()->Value(i3);
    SW.Send (Var0);
  }
  SW.CloseSub();

  // Own fields of Volume3dElementRepresentation

  SW.Send (ent->ModelRef());

  SW.Send (ent->ElementDescriptor());

  SW.Send (ent->Material());
}

//=======================================================================
//function : Share
//purpose  : 
//=======================================================================

void RWStepFEA_RWVolume3dElementRepresentation::Share (const Handle(StepFEA_Volume3dElementRepresentation) &ent,
                                                       Interface_EntityIterator& iter) const
{

  // Inherited fields of Representation

  for (Standard_Integer i1=1; i1 <= ent->StepRepr_Representation::Items()->Length(); i1++ ) {
    Handle(StepRepr_RepresentationItem) Var0 = ent->StepRepr_Representation::Items()->Value(i1);
    iter.AddItem (Var0);
  }

  iter.AddItem (ent->StepRepr_Representation::ContextOfItems());

  // Inherited fields of ElementRepresentation

  for (Standard_Integer i3=1; i3 <= ent->StepFEA_ElementRepresentation::NodeList()->Length(); i3++ ) {
    Handle(StepFEA_NodeRepresentation) Var0 = ent->StepFEA_ElementRepresentation::NodeList()->Value(i3);
    iter.AddItem (Var0);
  }

  // Own fields of Volume3dElementRepresentation

  iter.AddItem (ent->ModelRef());

  iter.AddItem (ent->ElementDescriptor());

  iter.AddItem (ent->Material());
}
