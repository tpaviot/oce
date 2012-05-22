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


#include <RWStepShape_RWFacetedBrepAndBrepWithVoids.ixx>
#include <StepShape_FacetedBrep.hxx>
#include <StepShape_BrepWithVoids.hxx>
#include <StepShape_ClosedShell.hxx>
#include <StepShape_HArray1OfOrientedClosedShell.hxx>
#include <StepShape_OrientedClosedShell.hxx>


#include <Interface_EntityIterator.hxx>


#include <StepShape_FacetedBrepAndBrepWithVoids.hxx>


RWStepShape_RWFacetedBrepAndBrepWithVoids::RWStepShape_RWFacetedBrepAndBrepWithVoids () {}

void RWStepShape_RWFacetedBrepAndBrepWithVoids::ReadStep
	(const Handle(StepData_StepReaderData)& data,
	 const Standard_Integer num0,
	 Handle(Interface_Check)& ach,
	 const Handle(StepShape_FacetedBrepAndBrepWithVoids)& ent) const
{

	Standard_Integer num = num0;


	// --- Instance of plex componant BrepWithVoids ---

	if (!data->CheckNbParams(num,1,ach,"brep_with_voids")) return;

	// --- field : voids ---

	Handle(StepShape_HArray1OfOrientedClosedShell) aVoids;
	Handle(StepShape_OrientedClosedShell) anent;
	Standard_Integer nsub1;
	if (data->ReadSubList (num,1,"voids",ach,nsub1)) {
	  Standard_Integer nb1 = data->NbParams(nsub1);
	  aVoids = new StepShape_HArray1OfOrientedClosedShell (1, nb1);
	  for (Standard_Integer i1 = 1; i1 <= nb1; i1 ++) {
	    //szv#4:S4163:12Mar99 `Standard_Boolean stat1 =` not needed
	    if (data->ReadEntity (nsub1, i1,"oriented_closed_shell", ach,
				  STANDARD_TYPE(StepShape_OrientedClosedShell), anent))
	      aVoids->SetValue(i1, anent);
	  }
	}

	num = data->NextForComplex(num);

	// --- Instance of plex componant FacetedBrep ---

	if (!data->CheckNbParams(num,0,ach,"faceted_brep")) return;

	num = data->NextForComplex(num);

	// --- Instance of plex componant GeometricRepresentationItem ---

	if (!data->CheckNbParams(num,0,ach,"geometric_representation_item")) return;

	num = data->NextForComplex(num);

	// --- Instance of common supertype ManifoldSolidBrep ---

	if (!data->CheckNbParams(num,1,ach,"manifold_solid_brep")) return;
	// --- field : outer ---


	Handle(StepShape_ClosedShell) aOuter;
	//szv#4:S4163:12Mar99 `Standard_Boolean stat2 =` not needed
	data->ReadEntity(num, 1,"outer", ach, STANDARD_TYPE(StepShape_ClosedShell), aOuter);

	num = data->NextForComplex(num);

	// --- Instance of plex componant RepresentationItem ---

	if (!data->CheckNbParams(num,1,ach,"representation_item")) return;


	// --- field : name ---

	Handle(TCollection_HAsciiString) aName;
	//szv#4:S4163:12Mar99 `Standard_Boolean stat10 =` not needed
	data->ReadString (num,1,"name",ach,aName);
	
	num = data->NextForComplex(num);

	// --- Instance of plex componant SolidModel ---

	if (!data->CheckNbParams(num,0,ach,"solid_model")) return;

	//--- Initialisation of the red entity ---

	ent->Init(aName, aOuter,aVoids);
}


void RWStepShape_RWFacetedBrepAndBrepWithVoids::WriteStep
	(StepData_StepWriter& SW,
	 const Handle(StepShape_FacetedBrepAndBrepWithVoids)& ent) const
{

	// --- Instance of plex componant BrepWithVoids ---

	SW.StartEntity("BREP_WITH_VOIDS");
	// --- field : voids ---

	SW.OpenSub();
	for (Standard_Integer i1 = 1;  i1 <= ent->NbVoids();  i1 ++) {
	  SW.Send(ent->VoidsValue(i1));
	}
	SW.CloseSub();

	// --- Instance of plex componant FacetedBrep ---

	SW.StartEntity("FACETED_BREP");

	// --- Instance of plex componant GeometricRepresentationItem ---

	SW.StartEntity("GEOMETRIC_REPRESENTATION_ITEM");

	// --- Instance of common supertype ManifoldSolidBrep ---

	SW.StartEntity("MANIFOLD_SOLID_BREP");
	// --- field : outer ---

	SW.Send(ent->Outer());

	// --- Instance of plex componant RepresentationItem ---

	SW.StartEntity("REPRESENTATION_ITEM");
	// --- field : name ---

	SW.Send(ent->Name());

	// --- Instance of plex componant SolidModel ---

	SW.StartEntity("SOLID_MODEL");
}


void RWStepShape_RWFacetedBrepAndBrepWithVoids::Share(const Handle(StepShape_FacetedBrepAndBrepWithVoids)& ent, Interface_EntityIterator& iter) const
{

	iter.GetOneItem(ent->Outer());
	
	Standard_Integer nbElem2 = ent->NbVoids();
	for (Standard_Integer is2=1; is2<=nbElem2; is2 ++) {
	  iter.GetOneItem(ent->VoidsValue(is2));
	}

}

