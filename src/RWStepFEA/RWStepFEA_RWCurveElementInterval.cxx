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

#include <RWStepFEA_RWCurveElementInterval.ixx>

//=======================================================================
//function : RWStepFEA_RWCurveElementInterval
//purpose  : 
//=======================================================================

RWStepFEA_RWCurveElementInterval::RWStepFEA_RWCurveElementInterval ()
{
}

//=======================================================================
//function : ReadStep
//purpose  : 
//=======================================================================

void RWStepFEA_RWCurveElementInterval::ReadStep (const Handle(StepData_StepReaderData)& data,
                                                 const Standard_Integer num,
                                                 Handle(Interface_Check)& ach,
                                                 const Handle(StepFEA_CurveElementInterval) &ent) const
{
  // Check number of parameters
  if ( ! data->CheckNbParams(num,2,ach,"curve_element_interval") ) return;

  // Own fields of CurveElementInterval

  Handle(StepFEA_CurveElementLocation) aFinishPosition;
  data->ReadEntity (num, 1, "finish_position", ach, STANDARD_TYPE(StepFEA_CurveElementLocation), aFinishPosition);

  Handle(StepBasic_EulerAngles) aEuAngles;
  data->ReadEntity (num, 2, "eu_angles", ach, STANDARD_TYPE(StepBasic_EulerAngles), aEuAngles);

  // Initialize entity
  ent->Init(aFinishPosition,
            aEuAngles);
}

//=======================================================================
//function : WriteStep
//purpose  : 
//=======================================================================

void RWStepFEA_RWCurveElementInterval::WriteStep (StepData_StepWriter& SW,
                                                  const Handle(StepFEA_CurveElementInterval) &ent) const
{

  // Own fields of CurveElementInterval

  SW.Send (ent->FinishPosition());

  SW.Send (ent->EuAngles());
}

//=======================================================================
//function : Share
//purpose  : 
//=======================================================================

void RWStepFEA_RWCurveElementInterval::Share (const Handle(StepFEA_CurveElementInterval) &ent,
                                              Interface_EntityIterator& iter) const
{

  // Own fields of CurveElementInterval

  iter.AddItem (ent->FinishPosition());

  iter.AddItem (ent->EuAngles());
}
