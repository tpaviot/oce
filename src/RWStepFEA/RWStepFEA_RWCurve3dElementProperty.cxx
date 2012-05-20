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

#include <RWStepFEA_RWCurve3dElementProperty.ixx>
#include <StepFEA_HArray1OfCurveElementInterval.hxx>
#include <StepFEA_CurveElementInterval.hxx>
#include <StepFEA_HArray1OfCurveElementEndOffset.hxx>
#include <StepFEA_CurveElementEndOffset.hxx>
#include <StepFEA_HArray1OfCurveElementEndRelease.hxx>
#include <StepFEA_CurveElementEndRelease.hxx>

//=======================================================================
//function : RWStepFEA_RWCurve3dElementProperty
//purpose  : 
//=======================================================================

RWStepFEA_RWCurve3dElementProperty::RWStepFEA_RWCurve3dElementProperty ()
{
}

//=======================================================================
//function : ReadStep
//purpose  : 
//=======================================================================

void RWStepFEA_RWCurve3dElementProperty::ReadStep (const Handle(StepData_StepReaderData)& data,
                                                   const Standard_Integer num,
                                                   Handle(Interface_Check)& ach,
                                                   const Handle(StepFEA_Curve3dElementProperty) &ent) const
{
  // Check number of parameters
  if ( ! data->CheckNbParams(num,5,ach,"curve3d_element_property") ) return;

  // Own fields of Curve3dElementProperty

  Handle(TCollection_HAsciiString) aPropertyId;
  data->ReadString (num, 1, "property_id", ach, aPropertyId);

  Handle(TCollection_HAsciiString) aDescription;
  data->ReadString (num, 2, "description", ach, aDescription);

  Handle(StepFEA_HArray1OfCurveElementInterval) aIntervalDefinitions;
  Standard_Integer sub3 = 0;
  if ( data->ReadSubList (num, 3, "interval_definitions", ach, sub3) ) {
    Standard_Integer nb0 = data->NbParams(sub3);
    aIntervalDefinitions = new StepFEA_HArray1OfCurveElementInterval (1, nb0);
    Standard_Integer num2 = sub3;
    for ( Standard_Integer i0=1; i0 <= nb0; i0++ ) {
      Handle(StepFEA_CurveElementInterval) anIt0;
      data->ReadEntity (num2, i0, "curve_element_interval", ach, STANDARD_TYPE(StepFEA_CurveElementInterval), anIt0);
      aIntervalDefinitions->SetValue(i0, anIt0);
    }
  }

  Handle(StepFEA_HArray1OfCurveElementEndOffset) aEndOffsets;
  Standard_Integer sub4 = 0;
  if ( data->ReadSubList (num, 4, "end_offsets", ach, sub4) ) {
    Standard_Integer nb0 = data->NbParams(sub4);
    aEndOffsets = new StepFEA_HArray1OfCurveElementEndOffset (1, nb0);
    Standard_Integer num2 = sub4;
    for ( Standard_Integer i0=1; i0 <= nb0; i0++ ) {
      Handle(StepFEA_CurveElementEndOffset) anIt0;
      data->ReadEntity (num2, i0, "curve_element_end_offset", ach, STANDARD_TYPE(StepFEA_CurveElementEndOffset), anIt0);
      aEndOffsets->SetValue(i0, anIt0);
    }
  }

  Handle(StepFEA_HArray1OfCurveElementEndRelease) aEndReleases;
  Standard_Integer sub5 = 0;
  if ( data->ReadSubList (num, 5, "end_releases", ach, sub5) ) {
    Standard_Integer nb0 = data->NbParams(sub5);
    aEndReleases = new StepFEA_HArray1OfCurveElementEndRelease (1, nb0);
    Standard_Integer num2 = sub5;
    for ( Standard_Integer i0=1; i0 <= nb0; i0++ ) {
      Handle(StepFEA_CurveElementEndRelease) anIt0;
      data->ReadEntity (num2, i0, "curve_element_end_release", ach, STANDARD_TYPE(StepFEA_CurveElementEndRelease), anIt0);
      aEndReleases->SetValue(i0, anIt0);
    }
  }

  // Initialize entity
  ent->Init(aPropertyId,
            aDescription,
            aIntervalDefinitions,
            aEndOffsets,
            aEndReleases);
}

//=======================================================================
//function : WriteStep
//purpose  : 
//=======================================================================

void RWStepFEA_RWCurve3dElementProperty::WriteStep (StepData_StepWriter& SW,
                                                    const Handle(StepFEA_Curve3dElementProperty) &ent) const
{

  // Own fields of Curve3dElementProperty

  SW.Send (ent->PropertyId());

  SW.Send (ent->Description());

  SW.OpenSub();
  for (Standard_Integer i2=1; i2 <= ent->IntervalDefinitions()->Length(); i2++ ) {
    Handle(StepFEA_CurveElementInterval) Var0 = ent->IntervalDefinitions()->Value(i2);
    SW.Send (Var0);
  }
  SW.CloseSub();

  SW.OpenSub();
  for (Standard_Integer i3=1; i3 <= ent->EndOffsets()->Length(); i3++ ) {
    Handle(StepFEA_CurveElementEndOffset) Var0 = ent->EndOffsets()->Value(i3);
    SW.Send (Var0);
  }
  SW.CloseSub();

  SW.OpenSub();
  for (Standard_Integer i4=1; i4 <= ent->EndReleases()->Length(); i4++ ) {
    Handle(StepFEA_CurveElementEndRelease) Var0 = ent->EndReleases()->Value(i4);
    SW.Send (Var0);
  }
  SW.CloseSub();
}

//=======================================================================
//function : Share
//purpose  : 
//=======================================================================

void RWStepFEA_RWCurve3dElementProperty::Share (const Handle(StepFEA_Curve3dElementProperty) &ent,
                                                Interface_EntityIterator& iter) const
{

  // Own fields of Curve3dElementProperty

  for (Standard_Integer i1=1; i1 <= ent->IntervalDefinitions()->Length(); i1++ ) {
    Handle(StepFEA_CurveElementInterval) Var0 = ent->IntervalDefinitions()->Value(i1);
    iter.AddItem (Var0);
  }

  for (Standard_Integer i2=1; i2 <= ent->EndOffsets()->Length(); i2++ ) {
    Handle(StepFEA_CurveElementEndOffset) Var0 = ent->EndOffsets()->Value(i2);
    iter.AddItem (Var0);
  }

  for (Standard_Integer i3=1; i3 <= ent->EndReleases()->Length(); i3++ ) {
    Handle(StepFEA_CurveElementEndRelease) Var0 = ent->EndReleases()->Value(i3);
    iter.AddItem (Var0);
  }
}
