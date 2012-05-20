// Created on: 2003-01-22
// Created by: data exchange team
// Copyright (c) 2003-2012 OPEN CASCADE SAS
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

#include <RWStepFEA_RWFeaCurveSectionGeometricRelationship.ixx>

//=======================================================================
//function : RWStepFEA_RWFeaCurveSectionGeometricRelationship
//purpose  : 
//=======================================================================

RWStepFEA_RWFeaCurveSectionGeometricRelationship::RWStepFEA_RWFeaCurveSectionGeometricRelationship ()
{
}

//=======================================================================
//function : ReadStep
//purpose  : 
//=======================================================================

void RWStepFEA_RWFeaCurveSectionGeometricRelationship::ReadStep (const Handle(StepData_StepReaderData)& data,
                                                                 const Standard_Integer num,
                                                                 Handle(Interface_Check)& ach,
                                                                 const Handle(StepFEA_FeaCurveSectionGeometricRelationship) &ent) const
{
  // Check number of parameters
  if ( ! data->CheckNbParams(num,2,ach,"fea_curve_section_geometric_relationship") ) return;

  // Own fields of FeaCurveSectionGeometricRelationship

  Handle(StepElement_CurveElementSectionDefinition) aSectionRef;
  data->ReadEntity (num, 1, "section_ref", ach, STANDARD_TYPE(StepElement_CurveElementSectionDefinition), aSectionRef);

  Handle(StepElement_AnalysisItemWithinRepresentation) aItem;
  data->ReadEntity (num, 2, "item", ach, STANDARD_TYPE(StepElement_AnalysisItemWithinRepresentation), aItem);

  // Initialize entity
  ent->Init(aSectionRef,
            aItem);
}

//=======================================================================
//function : WriteStep
//purpose  : 
//=======================================================================

void RWStepFEA_RWFeaCurveSectionGeometricRelationship::WriteStep (StepData_StepWriter& SW,
                                                                  const Handle(StepFEA_FeaCurveSectionGeometricRelationship) &ent) const
{

  // Own fields of FeaCurveSectionGeometricRelationship

  SW.Send (ent->SectionRef());

  SW.Send (ent->Item());
}

//=======================================================================
//function : Share
//purpose  : 
//=======================================================================

void RWStepFEA_RWFeaCurveSectionGeometricRelationship::Share (const Handle(StepFEA_FeaCurveSectionGeometricRelationship) &ent,
                                                              Interface_EntityIterator& iter) const
{

  // Own fields of FeaCurveSectionGeometricRelationship

  iter.AddItem (ent->SectionRef());

  iter.AddItem (ent->Item());
}
