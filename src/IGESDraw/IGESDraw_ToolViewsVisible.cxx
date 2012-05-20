// Created by: CKY / Contract Toubro-Larsen
// Copyright (c) 1993-1999 Matra Datavision
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

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <IGESDraw_ToolViewsVisible.ixx>
#include <IGESData_ParamCursor.hxx>
#include <IGESData_ViewKindEntity.hxx>
#include <IGESData_IGESEntity.hxx>
#include <IGESDraw_HArray1OfViewKindEntity.hxx>
#include <IGESData_HArray1OfIGESEntity.hxx>
#include <IGESData_Dump.hxx>
#include <Interface_Macros.hxx>
#include <stdio.h>


IGESDraw_ToolViewsVisible::IGESDraw_ToolViewsVisible ()    {  }


void IGESDraw_ToolViewsVisible::ReadOwnParams
  (const Handle(IGESDraw_ViewsVisible)& ent,
   const Handle(IGESData_IGESReaderData)& IR, IGESData_ParamReader& PR) const
{
  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed

  Standard_Integer tempNbViewsVisible, tempNbDisplayedEntities;
  Handle(IGESDraw_HArray1OfViewKindEntity) tempViewEntities;
  Handle(IGESData_HArray1OfIGESEntity) tempDisplayEntity;

  //st = PR.ReadInteger(PR.Current(), "Number Of Views Visible",
			//tempNbViewsVisible); //szv#4:S4163:12Mar99 moved in if
  if (PR.ReadInteger(PR.Current(), "Number Of Views Visible", tempNbViewsVisible)) {
    // Initialise HArray1 only if there is no error reading its Length
    if (tempNbViewsVisible <= 0)
      PR.AddFail("Number Of Views Visible : Not Positive");
    else  tempViewEntities = new IGESDraw_HArray1OfViewKindEntity (1, tempNbViewsVisible);
  }

  if (PR.DefinedElseSkip())
    PR.ReadInteger(PR.Current(), "Number of Entities Displayed",
		   tempNbDisplayedEntities); //szv#4:S4163:12Mar99 `st=` not needed
  else {
    tempNbDisplayedEntities = 0;
    PR.AddWarning("Number of Entities Displayed : undefined, set to Zero");
  }
  // Initialise HArray1 only if there is no error reading its Length
  if      (tempNbDisplayedEntities < 0)
    PR.AddFail ("Number Of Entities Displayed : Less than Zero");
//  else if (tempNbDisplayedEntities > 0) {

  if (! tempViewEntities.IsNull()) {
  // Read the HArray1 only if its Length was read without any Error
    Standard_Integer I;
    for (I = 1; I <= tempNbViewsVisible; I++) {
      Handle(IGESData_ViewKindEntity) tempViewEntity1;
      //st = PR.ReadEntity(IR, PR.Current(), "View Entity",
			   //STANDARD_TYPE(IGESData_ViewKindEntity), tempViewEntity1); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadEntity(IR, PR.Current(), "View Entity",
			STANDARD_TYPE(IGESData_ViewKindEntity), tempViewEntity1))
	tempViewEntities->SetValue(I, tempViewEntity1);
    }
  }

  // Read the HArray1 only if its Length was read without any Error
  if      (tempNbDisplayedEntities > 0) {
    PR.ReadEnts (IR,PR.CurrentList(tempNbDisplayedEntities),
		 "Displayed Entities",tempDisplayEntity); //szv#4:S4163:12Mar99 `st=` not needed
/*
    tempDisplayEntity =
      new IGESData_HArray1OfIGESEntity (1, tempNbDisplayedEntities);

    Handle(IGESData_IGESEntity) tempEntity2;
    Standard_Integer I;
    for (I = 1; I <= tempNbDisplayedEntities; I++) {
      st = PR.ReadEntity(IR, PR.Current(), "Displayed Entity",
			 tempEntity2);
      if (st) tempDisplayEntity->SetValue(I, tempEntity2);
    }
*/
  }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init(tempViewEntities, tempDisplayEntity);
}

void IGESDraw_ToolViewsVisible::WriteOwnParams
  (const Handle(IGESDraw_ViewsVisible)& ent, IGESData_IGESWriter& IW)  const
{
  IW.Send(ent->NbViews());
  IW.Send(ent->NbDisplayedEntities());

  Standard_Integer I;
  Standard_Integer up  = ent->NbViews();
  for (I = 1; I <= up; I++)
    IW.Send(ent->ViewItem(I));
  up  = ent->NbDisplayedEntities();
  for (I = 1; I <= up; I++)
    IW.Send(ent->DisplayedEntity(I));
}

void  IGESDraw_ToolViewsVisible::OwnShared
  (const Handle(IGESDraw_ViewsVisible)& ent, Interface_EntityIterator& iter) const
{
  Standard_Integer I,up;
  up  = ent->NbViews();
  for (I = 1; I <= up; I++)
    iter.GetOneItem(ent->ViewItem(I));
//  Displayed -> Implied
}

void  IGESDraw_ToolViewsVisible::OwnImplied
  (const Handle(IGESDraw_ViewsVisible)& ent, Interface_EntityIterator& iter) const
{
  Standard_Integer I,up;
  up  = ent->NbDisplayedEntities();
  for (I = 1; I <= up; I++)
    iter.GetOneItem(ent->DisplayedEntity(I));
}


void IGESDraw_ToolViewsVisible::OwnCopy
  (const Handle(IGESDraw_ViewsVisible)& another,
   const Handle(IGESDraw_ViewsVisible)& ent, Interface_CopyTool& TC) const
{
  Handle(IGESDraw_HArray1OfViewKindEntity) tempViewEntities =
    new IGESDraw_HArray1OfViewKindEntity(1, another->NbViews());
  Standard_Integer I, up;
  up  = another->NbViews();
  for (I = 1; I <= up; I++) {
    DeclareAndCast(IGESData_ViewKindEntity, tempView,
		   TC.Transferred(another->ViewItem(I)));
    tempViewEntities->SetValue(I, tempView);
  }
//  Displayed -> Implied : mettre une liste vide par defaut
  Handle(IGESData_HArray1OfIGESEntity) tempDisplayEntities;
  ent->Init(tempViewEntities, tempDisplayEntities);
}

void IGESDraw_ToolViewsVisible::OwnRenew
  (const Handle(IGESDraw_ViewsVisible)& another,
   const Handle(IGESDraw_ViewsVisible)& ent, const Interface_CopyTool& TC) const
{
  Interface_EntityIterator newdisp;
  Standard_Integer I, up;
  up  = another->NbDisplayedEntities();
  if (up == 0) return;
  Handle(IGESData_HArray1OfIGESEntity) tempDisplayEntities;
  Handle(IGESData_IGESEntity) anew;
  for (I = 1; I <= up; I++) {
    if (TC.Search (another->DisplayedEntity(I),anew)) newdisp.GetOneItem(anew);
  }

  up = newdisp.NbEntities();  I = 0;
  if (up > 0) tempDisplayEntities = new IGESData_HArray1OfIGESEntity(1,up);
  for (newdisp.Start(); newdisp.More(); newdisp.Next()) {
    I ++;
    DeclareAndCast(IGESData_IGESEntity, tempEntity,newdisp.Value());
    tempDisplayEntities->SetValue(I, tempEntity);
  }
  ent->InitImplied (tempDisplayEntities);
}


IGESData_DirChecker IGESDraw_ToolViewsVisible::DirChecker
  (const Handle(IGESDraw_ViewsVisible)& /*ent*/)  const
{
  IGESData_DirChecker DC(402, 3);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.SubordinateStatusRequired(0);
  DC.UseFlagRequired(1);
  DC.HierarchyStatusIgnored();

  return DC;
}

void IGESDraw_ToolViewsVisible::OwnCheck
  (const Handle(IGESDraw_ViewsVisible)& ent,
   const Interface_ShareTool& , Handle(Interface_Check)& ach)  const
{
  Standard_Integer res = 0;
  Standard_Integer nb = ent->NbDisplayedEntities();
  Handle(IGESData_ViewKindEntity) entcomp = ent;
  for (Standard_Integer i = 1; i <= nb; i ++) {
    Handle(IGESData_IGESEntity) displayed = ent->DisplayedEntity(i);
    if (entcomp != displayed->View()) res ++;
  }
  if (!res) return;
  char mess[80];
  sprintf(mess,"Mismatch for %d Entities displayed",res);
  ach->AddFail(mess,"Mismatch for %d Entities displayed");
}

void  IGESDraw_ToolViewsVisible::OwnWhenDelete
  (const Handle(IGESDraw_ViewsVisible)& ent) const
{
  Handle(IGESData_HArray1OfIGESEntity) tempDisplayEntities;
  ent->InitImplied (tempDisplayEntities);
}

void IGESDraw_ToolViewsVisible::OwnDump
  (const Handle(IGESDraw_ViewsVisible)& ent, const IGESData_IGESDumper& dumper,
  const Handle(Message_Messenger)& S, const Standard_Integer level)  const
{
  S << "IGESDraw_ViewsVisible" << endl;

  S << "Views Visible : ";
  IGESData_DumpEntities(S,dumper ,level,1, ent->NbViews(),ent->ViewItem);
  S << endl;
  S << "Entities Displayed : ";
  IGESData_DumpEntities
    (S,dumper ,level,1, ent->NbDisplayedEntities(),ent->DisplayedEntity);
  S << endl;
}

Standard_Boolean  IGESDraw_ToolViewsVisible::OwnCorrect
  (const Handle(IGESDraw_ViewsVisible)& ent) const
{
//  Les entites affichees doivent referencer <ent>. Elles ont priorite.
  Standard_Boolean res = Standard_False;
  Standard_Integer nb = ent->NbDisplayedEntities();
  Handle(IGESData_ViewKindEntity) entcomp = ent;
  for (Standard_Integer i = 1; i <= nb; i ++) {
    Handle(IGESData_IGESEntity) displayed = ent->DisplayedEntity(i);
    if (entcomp != displayed->View()) res = Standard_True;
  }
  if (!res) return res;
  Handle(IGESData_HArray1OfIGESEntity) nulDisplayEntities;
  ent->InitImplied (nulDisplayEntities);
  return res;
}
