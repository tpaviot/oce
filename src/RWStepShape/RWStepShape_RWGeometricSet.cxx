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


#include <RWStepShape_RWGeometricSet.ixx>
#include <StepShape_HArray1OfGeometricSetSelect.hxx>
#include <StepShape_GeometricSetSelect.hxx>


#include <Interface_EntityIterator.hxx>


#include <StepShape_GeometricSet.hxx>


RWStepShape_RWGeometricSet::RWStepShape_RWGeometricSet () {}

void RWStepShape_RWGeometricSet::ReadStep
	(const Handle(StepData_StepReaderData)& data,
	 const Standard_Integer num,
	 Handle(Interface_Check)& ach,
	 const Handle(StepShape_GeometricSet)& ent) const
{


	// --- Number of Parameter Control ---

	if (!data->CheckNbParams(num,2,ach,"geometric_set")) return;

	// --- inherited field : name ---

	Handle(TCollection_HAsciiString) aName;
	//szv#4:S4163:12Mar99 `Standard_Boolean stat1 =` not needed
	data->ReadString (num,1,"name",ach,aName);

	// --- own field : elements ---

	Handle(StepShape_HArray1OfGeometricSetSelect) aElements;
	StepShape_GeometricSetSelect aElementsItem;
	Standard_Integer nsub2;
	if (data->ReadSubList (num,2,"elements",ach,nsub2)) {
	  Standard_Integer nb2 = data->NbParams(nsub2);
	  aElements = new StepShape_HArray1OfGeometricSetSelect (1, nb2);
	  for (Standard_Integer i2 = 1; i2 <= nb2; i2 ++) {
	    //szv#4:S4163:12Mar99 `Standard_Boolean stat2 =` not needed
	    if (data->ReadEntity (nsub2,i2,"elements",ach,aElementsItem))
	      aElements->SetValue(i2,aElementsItem);
	  }
	}

	//--- Initialisation of the read entity ---


	ent->Init(aName, aElements);
}


void RWStepShape_RWGeometricSet::WriteStep
	(StepData_StepWriter& SW,
	 const Handle(StepShape_GeometricSet)& ent) const
{

	// --- inherited field name ---

	SW.Send(ent->Name());

	// --- own field : elements ---

	SW.OpenSub();
	for (Standard_Integer i2 = 1;  i2 <= ent->NbElements();  i2 ++) {
	  SW.Send(ent->ElementsValue(i2).Value());
	}
	SW.CloseSub();
}


void RWStepShape_RWGeometricSet::Share(const Handle(StepShape_GeometricSet)& ent, Interface_EntityIterator& iter) const
{

	Standard_Integer nbElem1 = ent->NbElements();
	for (Standard_Integer is1=1; is1<=nbElem1; is1 ++) {
	  iter.GetOneItem(ent->ElementsValue(is1).Value());
	}

}

