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


#include <RWStepVisual_RWContextDependentOverRidingStyledItem.ixx>
#include <StepVisual_HArray1OfStyleContextSelect.hxx>
#include <StepVisual_StyleContextSelect.hxx>
#include <StepVisual_HArray1OfPresentationStyleAssignment.hxx>
#include <StepVisual_PresentationStyleAssignment.hxx>
#include <StepRepr_RepresentationItem.hxx>
#include <StepVisual_StyledItem.hxx>


#include <Interface_EntityIterator.hxx>


#include <StepVisual_ContextDependentOverRidingStyledItem.hxx>


RWStepVisual_RWContextDependentOverRidingStyledItem::RWStepVisual_RWContextDependentOverRidingStyledItem () {}

void RWStepVisual_RWContextDependentOverRidingStyledItem::ReadStep
	(const Handle(StepData_StepReaderData)& data,
	 const Standard_Integer num,
	 Handle(Interface_Check)& ach,
	 const Handle(StepVisual_ContextDependentOverRidingStyledItem)& ent) const
{


	// --- Number of Parameter Control ---

	if (!data->CheckNbParams(num,5,ach,"context_dependent_over_riding_styled_item")) return;

	// --- inherited field : name ---

	Handle(TCollection_HAsciiString) aName;
	//szv#4:S4163:12Mar99 `Standard_Boolean stat1 =` not needed
	data->ReadString (num,1,"name",ach,aName);

	// --- inherited field : styles ---

	Handle(StepVisual_HArray1OfPresentationStyleAssignment) aStyles;
	Handle(StepVisual_PresentationStyleAssignment) anent2;
	Standard_Integer nsub2;
	if (data->ReadSubList (num,2,"styles",ach,nsub2)) {
	  Standard_Integer nb2 = data->NbParams(nsub2);
	  aStyles = new StepVisual_HArray1OfPresentationStyleAssignment (1, nb2);
	  for (Standard_Integer i2 = 1; i2 <= nb2; i2 ++) {
	    //szv#4:S4163:12Mar99 `Standard_Boolean stat2 =` not needed
	    if (data->ReadEntity (nsub2, i2,"presentation_style_assignment", ach,
				  STANDARD_TYPE(StepVisual_PresentationStyleAssignment), anent2))
	      aStyles->SetValue(i2, anent2);
	  }
	}

	// --- inherited field : item ---

	Handle(StepRepr_RepresentationItem) aItem;
	//szv#4:S4163:12Mar99 `Standard_Boolean stat3 =` not needed
	data->ReadEntity(num, 3,"item", ach, STANDARD_TYPE(StepRepr_RepresentationItem), aItem);

	// --- inherited field : overRiddenStyle ---

	Handle(StepVisual_StyledItem) aOverRiddenStyle;
	//szv#4:S4163:12Mar99 `Standard_Boolean stat4 =` not needed
	data->ReadEntity(num, 4,"over_ridden_style", ach, STANDARD_TYPE(StepVisual_StyledItem), aOverRiddenStyle);

	// --- own field : styleContext ---

	Handle(StepVisual_HArray1OfStyleContextSelect) aStyleContext;
	StepVisual_StyleContextSelect aStyleContextItem;
	Standard_Integer nsub5;
	if (data->ReadSubList (num,5,"style_context",ach,nsub5)) {
	  Standard_Integer nb5 = data->NbParams(nsub5);
	  aStyleContext = new StepVisual_HArray1OfStyleContextSelect (1, nb5);
	  for (Standard_Integer i5 = 1; i5 <= nb5; i5 ++) {
	    //szv#4:S4163:12Mar99 `Standard_Boolean stat5 =` not needed
	    if (data->ReadEntity (nsub5,i5,"style_context",ach,aStyleContextItem))
	      aStyleContext->SetValue(i5,aStyleContextItem);
	  }
	}

	//--- Initialisation of the read entity ---


	ent->Init(aName, aStyles, aItem, aOverRiddenStyle, aStyleContext);
}


void RWStepVisual_RWContextDependentOverRidingStyledItem::WriteStep
	(StepData_StepWriter& SW,
	 const Handle(StepVisual_ContextDependentOverRidingStyledItem)& ent) const
{

	// --- inherited field name ---

	SW.Send(ent->Name());

	// --- inherited field styles ---

	SW.OpenSub();
	for (Standard_Integer i2 = 1;  i2 <= ent->NbStyles();  i2 ++) {
	  SW.Send(ent->StylesValue(i2));
	}
	SW.CloseSub();

	// --- inherited field item ---

	SW.Send(ent->Item());

	// --- inherited field overRiddenStyle ---

	SW.Send(ent->OverRiddenStyle());

	// --- own field : styleContext ---

	SW.OpenSub();
	for (Standard_Integer i5 = 1;  i5 <= ent->NbStyleContext();  i5 ++) {
	  SW.Send(ent->StyleContextValue(i5).Value());
	}
	SW.CloseSub();
}


void RWStepVisual_RWContextDependentOverRidingStyledItem::Share(const Handle(StepVisual_ContextDependentOverRidingStyledItem)& ent, Interface_EntityIterator& iter) const
{

	Standard_Integer nbElem1 = ent->NbStyles();
	for (Standard_Integer is1=1; is1<=nbElem1; is1 ++) {
	  iter.GetOneItem(ent->StylesValue(is1));
	}



	iter.GetOneItem(ent->Item());


	iter.GetOneItem(ent->OverRiddenStyle());


	Standard_Integer nbElem4 = ent->NbStyleContext();
	for (Standard_Integer is4=1; is4<=nbElem4; is4 ++) {
	  iter.GetOneItem(ent->StyleContextValue(is4).Value());
	}

}

