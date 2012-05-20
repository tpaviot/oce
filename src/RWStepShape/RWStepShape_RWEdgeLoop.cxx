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


#include <RWStepShape_RWEdgeLoop.ixx>

#include <StepShape_HArray1OfOrientedEdge.hxx>
#include <StepShape_OrientedEdge.hxx>

RWStepShape_RWEdgeLoop::RWStepShape_RWEdgeLoop () {}

void RWStepShape_RWEdgeLoop::ReadStep
(const Handle(StepData_StepReaderData)& data,
 const Standard_Integer num,
 Handle(Interface_Check)& ach,
 const Handle(StepShape_EdgeLoop)& ent) const
{
  
  
  // --- Number of Parameter Control ---
  
  if (!data->CheckNbParams(num,2,ach,"edge_loop")) return;
  
  // --- inherited field : name ---
  
  Handle(TCollection_HAsciiString) aName;
  //szv#4:S4163:12Mar99 `Standard_Boolean stat0 =` not needed
  data->ReadString (num,1,"name",ach,aName);
  
  // --- own field : edgeList ---
  
  Handle(StepShape_HArray1OfOrientedEdge) aEdgeList;
  Handle(StepShape_OrientedEdge) anent;
  Standard_Integer nsub1;
  if (data->ReadSubList (num,2,"edge_list",ach,nsub1)) {
    Standard_Integer nb1 = data->NbParams(nsub1);
    aEdgeList = new StepShape_HArray1OfOrientedEdge (1, nb1);
    for (Standard_Integer i1 = 1; i1 <= nb1; i1 ++) {
      //szv#4:S4163:12Mar99 `Standard_Boolean stat1 =` not needed
      if (data->ReadEntity (nsub1, i1,"oriented_edge", ach, STANDARD_TYPE(StepShape_OrientedEdge), anent))
	aEdgeList->SetValue(i1, anent);
    }
  }
  
  //--- Initialisation of the read entity ---
  
  ent->Init(aName, aEdgeList);
}


void RWStepShape_RWEdgeLoop::WriteStep
	(StepData_StepWriter& SW,
	 const Handle(StepShape_EdgeLoop)& ent) const
{
  
  // --- inherited field name ---
  
  SW.Send(ent->Name());
  
  // --- own field : edgeList ---
  
  SW.OpenSub();
  for (Standard_Integer i1 = 1;  i1 <= ent->NbEdgeList();  i1 ++) {
    SW.Send(ent->EdgeListValue(i1));
  }
  SW.CloseSub();
}

// ============================================================================
// Method : Share
// ============================================================================

void RWStepShape_RWEdgeLoop::Share(const Handle(StepShape_EdgeLoop)& ent, Interface_EntityIterator& iter) const
{

	Standard_Integer nbElem1 = ent->NbEdgeList();
	for (Standard_Integer is1=1; is1<=nbElem1; is1 ++) {
	  iter.GetOneItem(ent->EdgeListValue(is1));
	}

}



void RWStepShape_RWEdgeLoop::Check
  (const Handle(StepShape_EdgeLoop)& ent,
   const Interface_ShareTool& ,
   Handle(Interface_Check)& ach) const
{
//  cout << "------ calling CheckEdgeLoop ------" << endl;
  Standard_Boolean headToTail = Standard_True;
  //Standard_Boolean noIdentVtx = Standard_True; //szv#4:S4163:12Mar99 unused
  Standard_Integer nbEdg = ent->NbEdgeList();
  Handle(StepShape_OrientedEdge) theOE = ent->EdgeListValue(1);
  Handle(StepShape_Vertex) theVxFrst = theOE->EdgeStart();
  Handle(StepShape_Vertex) theVxLst  = theOE->EdgeEnd();
  if((nbEdg == 1) && (theVxFrst != theVxLst)){
    ach->AddFail("Edge loop composed of single Edge : Start and End Vertex of edge are not identical");
  }
  for(Standard_Integer i = 2; i <= nbEdg; i++)
    {
      theOE     = ent->EdgeListValue(i);
      Handle(StepShape_Vertex) theVxStrt = theOE->EdgeStart();
      if(theVxStrt != theVxLst){
	headToTail = Standard_False;
      }
      theVxLst = theOE->EdgeEnd();
      if(theVxStrt == theVxLst){
	ach->AddWarning("One edge_curve contains identical vertices");
      }
    }
  if(theVxFrst != theVxLst){
    headToTail = Standard_False;
  }
  if(!headToTail) {
    ach->AddFail("Error : Path does not head to tail");
  }
}
