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

//gka 05.03.99 S4134 upgrade from CD to DIS
#include <RWStepRepr_RWRepresentationRelationship.ixx>
#include <StepRepr_Representation.hxx>


#include <Interface_EntityIterator.hxx>


#include <StepRepr_RepresentationRelationship.hxx>


RWStepRepr_RWRepresentationRelationship::RWStepRepr_RWRepresentationRelationship () {}

void RWStepRepr_RWRepresentationRelationship::ReadStep
	(const Handle(StepData_StepReaderData)& data,
	 const Standard_Integer num,
	 Handle(Interface_Check)& ach,
	 const Handle(StepRepr_RepresentationRelationship)& ent) const
{


	// --- Number of Parameter Control ---

	if (!data->CheckNbParams(num,4,ach,"representation_relationship")) return;

	// --- own field : name ---

	Handle(TCollection_HAsciiString) aName;
	//szv#4:S4163:12Mar99 `Standard_Boolean stat1 =` not needed
	data->ReadString (num,1,"name",ach,aName);

	// --- own field : description ---

	Handle(TCollection_HAsciiString) aDescription;
	if (data->IsParamDefined (num,2)) { //gka 05.03.99 S4134 upgrade from CD to DIS
	  //szv#4:S4163:12Mar99 `Standard_Boolean stat2 =` not needed
	  data->ReadString (num,2,"description",ach,aDescription);
	}
	// --- own field : rep1 ---

	Handle(StepRepr_Representation) aRep1;
	//szv#4:S4163:12Mar99 `Standard_Boolean stat3 =` not needed
	data->ReadEntity(num, 3,"rep_1", ach, STANDARD_TYPE(StepRepr_Representation), aRep1);

	// --- own field : rep2 ---

	Handle(StepRepr_Representation) aRep2;
	//szv#4:S4163:12Mar99 `Standard_Boolean stat4 =` not needed
	data->ReadEntity(num, 4,"rep_2", ach, STANDARD_TYPE(StepRepr_Representation), aRep2);

	//--- Initialisation of the read entity ---


	ent->Init(aName, aDescription, aRep1, aRep2);
}


void RWStepRepr_RWRepresentationRelationship::WriteStep
	(StepData_StepWriter& SW,
	 const Handle(StepRepr_RepresentationRelationship)& ent) const
{

	// --- own field : name ---

	SW.Send(ent->Name());

	// --- own field : description ---

	SW.Send(ent->Description());

	// --- own field : rep1 ---

	SW.Send(ent->Rep1());

	// --- own field : rep2 ---

	SW.Send(ent->Rep2());
}


void RWStepRepr_RWRepresentationRelationship::Share(const Handle(StepRepr_RepresentationRelationship)& ent, Interface_EntityIterator& iter) const
{

	iter.GetOneItem(ent->Rep1());


	iter.GetOneItem(ent->Rep2());
}

