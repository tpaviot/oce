
#include <RWStepAP214_RWAutoDesignPersonAndOrganizationAssignment.ixx>
#include <StepAP214_HArray1OfAutoDesignGeneralOrgItem.hxx>
#include <StepAP214_AutoDesignGeneralOrgItem.hxx>
#include <StepBasic_PersonAndOrganization.hxx>
#include <StepBasic_PersonAndOrganizationRole.hxx>


#include <Interface_EntityIterator.hxx>


#include <StepAP214_AutoDesignPersonAndOrganizationAssignment.hxx>


RWStepAP214_RWAutoDesignPersonAndOrganizationAssignment::RWStepAP214_RWAutoDesignPersonAndOrganizationAssignment () {}

void RWStepAP214_RWAutoDesignPersonAndOrganizationAssignment::ReadStep
	(const Handle(StepData_StepReaderData)& data,
	 const Standard_Integer num,
	 Handle(Interface_Check)& ach,
	 const Handle(StepAP214_AutoDesignPersonAndOrganizationAssignment)& ent) const
{


	// --- Number of Parameter Control ---

	if (!data->CheckNbParams(num,3,ach,"auto_design_person_and_organization_assignment")) return;

	// --- inherited field : assignedPersonAndOrganization ---

	Handle(StepBasic_PersonAndOrganization) aAssignedPersonAndOrganization;
	data->ReadEntity(num, 1,"assigned_person_and_organization", ach, STANDARD_TYPE(StepBasic_PersonAndOrganization), aAssignedPersonAndOrganization);

	// --- inherited field : role ---

	Handle(StepBasic_PersonAndOrganizationRole) aRole;
	data->ReadEntity(num, 2,"role", ach, STANDARD_TYPE(StepBasic_PersonAndOrganizationRole), aRole);

	// --- own field : items ---

	Handle(StepAP214_HArray1OfAutoDesignGeneralOrgItem) aItems;
	StepAP214_AutoDesignGeneralOrgItem aItemsItem;
	Standard_Integer nsub3;
	if (data->ReadSubList (num,3,"items",ach,nsub3)) {
	  Standard_Integer nb3 = data->NbParams(nsub3);
	  aItems = new StepAP214_HArray1OfAutoDesignGeneralOrgItem (1, nb3);
	  for (Standard_Integer i3 = 1; i3 <= nb3; i3 ++) {
	    Standard_Boolean stat3 = data->ReadEntity
	         (nsub3,i3,"items",ach,aItemsItem);
	    if (stat3) aItems->SetValue(i3,aItemsItem);
	  }
	}

	//--- Initialisation of the read entity ---


	ent->Init(aAssignedPersonAndOrganization, aRole, aItems);
}


void RWStepAP214_RWAutoDesignPersonAndOrganizationAssignment::WriteStep
	(StepData_StepWriter& SW,
	 const Handle(StepAP214_AutoDesignPersonAndOrganizationAssignment)& ent) const
{

	// --- inherited field assignedPersonAndOrganization ---

	SW.Send(ent->AssignedPersonAndOrganization());

	// --- inherited field role ---

	SW.Send(ent->Role());

	// --- own field : items ---

	SW.OpenSub();
	for (Standard_Integer i3 = 1;  i3 <= ent->NbItems();  i3 ++) {
	  SW.Send(ent->ItemsValue(i3).Value());
	}
	SW.CloseSub();
}


void RWStepAP214_RWAutoDesignPersonAndOrganizationAssignment::Share(const Handle(StepAP214_AutoDesignPersonAndOrganizationAssignment)& ent, Interface_EntityIterator& iter) const
{

	iter.GetOneItem(ent->AssignedPersonAndOrganization());


	iter.GetOneItem(ent->Role());


	Standard_Integer nbElem3 = ent->NbItems();
	for (Standard_Integer is3=1; is3<=nbElem3; is3 ++) {
	  iter.GetOneItem(ent->ItemsValue(is3).Value());
	}

}

