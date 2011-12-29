
#include <RWStepAP214_RWAppliedOrganizationAssignment.ixx>
#include <StepAP214_HArray1OfOrganizationItem.hxx>
#include <StepAP214_OrganizationItem.hxx>
#include <StepBasic_Organization.hxx>
#include <StepBasic_OrganizationRole.hxx>


#include <Interface_EntityIterator.hxx>


#include <StepAP214_AppliedOrganizationAssignment.hxx>


RWStepAP214_RWAppliedOrganizationAssignment::RWStepAP214_RWAppliedOrganizationAssignment () {}

void RWStepAP214_RWAppliedOrganizationAssignment::ReadStep
	(const Handle(StepData_StepReaderData)& data,
	 const Standard_Integer num,
	 Handle(Interface_Check)& ach,
	 const Handle(StepAP214_AppliedOrganizationAssignment)& ent) const
{


  // --- Number of Parameter Control ---

  if (!data->CheckNbParams(num,3,ach,"applied_organization_assignment")) return;

  // --- inherited field : assignedOrganization ---
  
  Handle(StepBasic_Organization) aAssignedOrganization;
  data->ReadEntity(num, 1,"assigned_organization", ach, STANDARD_TYPE(StepBasic_Organization), aAssignedOrganization);
  
  // --- inherited field : role ---

  Handle(StepBasic_OrganizationRole) aRole;
  data->ReadEntity(num, 2,"role", ach, STANDARD_TYPE(StepBasic_OrganizationRole), aRole);
  
  // --- own field : items ---

  Handle(StepAP214_HArray1OfOrganizationItem) aItems;
  StepAP214_OrganizationItem aItemsItem;
  Standard_Integer nsub3;
  if (data->ReadSubList (num,3,"items",ach,nsub3)) {
    Standard_Integer nb3 = data->NbParams(nsub3);
    aItems = new StepAP214_HArray1OfOrganizationItem (1, nb3);
    for (Standard_Integer i3 = 1; i3 <= nb3; i3 ++) {
      Standard_Boolean stat3 = data->ReadEntity
	(nsub3,i3,"items",ach,aItemsItem);
      if (stat3) aItems->SetValue(i3,aItemsItem);
    }
  }

  //--- Initialisation of the read entity ---


  ent->Init(aAssignedOrganization, aRole, aItems);
}


void RWStepAP214_RWAppliedOrganizationAssignment::WriteStep
	(StepData_StepWriter& SW,
	 const Handle(StepAP214_AppliedOrganizationAssignment)& ent) const
{

  // --- inherited field assignedOrganization ---

  SW.Send(ent->AssignedOrganization());
	
  // --- inherited field role ---

  SW.Send(ent->Role());

  // --- own field : items ---

  SW.OpenSub();
  for (Standard_Integer i3 = 1;  i3 <= ent->NbItems();  i3 ++) {
    SW.Send(ent->ItemsValue(i3).Value());
  }
  SW.CloseSub();
}


void RWStepAP214_RWAppliedOrganizationAssignment::Share(const Handle(StepAP214_AppliedOrganizationAssignment)& ent, Interface_EntityIterator& iter) const
{

  iter.GetOneItem(ent->AssignedOrganization());
  iter.GetOneItem(ent->Role());
  Standard_Integer nbElem3 = ent->NbItems();
  for (Standard_Integer is3=1; is3<=nbElem3; is3 ++) {
    iter.GetOneItem(ent->ItemsValue(is3).Value());
  }

}

