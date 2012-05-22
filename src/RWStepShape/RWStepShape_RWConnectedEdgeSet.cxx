// Created on: 2001-12-28
// Created by: Andrey BETENEV
// Copyright (c) 2001-2012 OPEN CASCADE SAS
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

#include <RWStepShape_RWConnectedEdgeSet.ixx>
#include <StepShape_HArray1OfEdge.hxx>
#include <StepShape_Edge.hxx>

//=======================================================================
//function : RWStepShape_RWConnectedEdgeSet
//purpose  : 
//=======================================================================

RWStepShape_RWConnectedEdgeSet::RWStepShape_RWConnectedEdgeSet ()
{
}

//=======================================================================
//function : ReadStep
//purpose  : 
//=======================================================================

void RWStepShape_RWConnectedEdgeSet::ReadStep (const Handle(StepData_StepReaderData)& data,
                                               const Standard_Integer num,
                                               Handle(Interface_Check)& ach,
                                               const Handle(StepShape_ConnectedEdgeSet) &ent) const
{
  // Check number of parameters
  if ( ! data->CheckNbParams(num,2,ach,"connected_edge_set") ) return;

  // Inherited fields of RepresentationItem

  Handle(TCollection_HAsciiString) aRepresentationItem_Name;
  data->ReadString (num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  // Own fields of ConnectedEdgeSet

  Handle(StepShape_HArray1OfEdge) aCesEdges;
  Standard_Integer sub2 = 0;
  if ( data->ReadSubList (num, 2, "ces_edges", ach, sub2) ) {
    Standard_Integer num2 = sub2;
    Standard_Integer nb0 = data->NbParams(num2);
    aCesEdges = new StepShape_HArray1OfEdge (1, nb0);
    for ( Standard_Integer i0=1; i0 <= nb0; i0++ ) {
      Handle(StepShape_Edge) anIt0;
      data->ReadEntity (num2, i0, "ces_edges", ach, STANDARD_TYPE(StepShape_Edge), anIt0);
      aCesEdges->SetValue(i0, anIt0);
    }
  }

  // Initialize entity
  ent->Init(aRepresentationItem_Name,
            aCesEdges);
}

//=======================================================================
//function : WriteStep
//purpose  : 
//=======================================================================

void RWStepShape_RWConnectedEdgeSet::WriteStep (StepData_StepWriter& SW,
                                                const Handle(StepShape_ConnectedEdgeSet) &ent) const
{

  // Inherited fields of RepresentationItem

  SW.Send (ent->StepRepr_RepresentationItem::Name());

  // Own fields of ConnectedEdgeSet

  SW.OpenSub();
  for (Standard_Integer i1=1; i1 <= ent->CesEdges()->Length(); i1++ ) {
    Handle(StepShape_Edge) Var0 = ent->CesEdges()->Value(i1);
    SW.Send (Var0);
  }
  SW.CloseSub();
}

//=======================================================================
//function : Share
//purpose  : 
//=======================================================================

void RWStepShape_RWConnectedEdgeSet::Share (const Handle(StepShape_ConnectedEdgeSet) &ent,
                                            Interface_EntityIterator& iter) const
{

  // Inherited fields of RepresentationItem

  // Own fields of ConnectedEdgeSet

  for (Standard_Integer i1=1; i1 <= ent->CesEdges()->Length(); i1++ ) {
    Handle(StepShape_Edge) Var0 = ent->CesEdges()->Value(i1);
    iter.AddItem (Var0);
  }
}
