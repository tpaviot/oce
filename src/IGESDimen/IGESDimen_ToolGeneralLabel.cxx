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

#include <IGESDimen_ToolGeneralLabel.ixx>
#include <IGESData_ParamCursor.hxx>
#include <IGESDimen_LeaderArrow.hxx>
#include <IGESDimen_GeneralNote.hxx>
#include <IGESDimen_HArray1OfLeaderArrow.hxx>
#include <IGESData_Dump.hxx>
#include <Interface_Macros.hxx>


IGESDimen_ToolGeneralLabel::IGESDimen_ToolGeneralLabel ()    {  }


void  IGESDimen_ToolGeneralLabel::ReadOwnParams
  (const Handle(IGESDimen_GeneralLabel)& ent,
   const Handle(IGESData_IGESReaderData)& IR, IGESData_ParamReader& PR) const
{ 
  //Standard_Boolean st; //szv#4:S4163:12Mar99 moved down

  Handle(IGESDimen_GeneralNote) note;
  Standard_Integer nbval;
  Handle(IGESDimen_HArray1OfLeaderArrow) leaders;

  PR.ReadEntity(IR, PR.Current(), "General Note Entity",
		STANDARD_TYPE(IGESDimen_GeneralNote),note); //szv#4:S4163:12Mar99 `st=` not needed

  Standard_Boolean st = PR.ReadInteger(PR.Current(), "Number of Leaders", nbval);
  if (st && nbval > 0)
    leaders = new IGESDimen_HArray1OfLeaderArrow(1, nbval);
  else  PR.AddFail("Number of Leaders: Not Positive");

  if (! leaders.IsNull())
    for (Standard_Integer i = 1; i <= nbval; i++)
      {
	Handle(IGESDimen_LeaderArrow) anentity;
	//st = PR.ReadEntity(IR, PR.Current(), "Leaders",
			     //STANDARD_TYPE(IGESDimen_LeaderArrow), anentity); //szv#4:S4163:12Mar99 moved in if
	if (PR.ReadEntity(IR, PR.Current(), "Leaders", STANDARD_TYPE(IGESDimen_LeaderArrow), anentity))
	  leaders->SetValue(i, anentity);
      }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init(note, leaders);
}

void  IGESDimen_ToolGeneralLabel::WriteOwnParams
  (const Handle(IGESDimen_GeneralLabel)& ent, IGESData_IGESWriter& IW) const 
{ 
  Standard_Integer upper = ent->NbLeaders();
  IW.Send(ent->Note());
  IW.Send(upper);
  for (Standard_Integer i = 1; i <= upper; i++)
    IW.Send(ent->Leader(i));
}

void  IGESDimen_ToolGeneralLabel::OwnShared
  (const Handle(IGESDimen_GeneralLabel)& ent, Interface_EntityIterator& iter) const
{
  Standard_Integer upper = ent->NbLeaders();
  iter.GetOneItem(ent->Note());
  for (Standard_Integer i = 1; i <= upper; i++)
    iter.GetOneItem(ent->Leader(i));
}

void  IGESDimen_ToolGeneralLabel::OwnCopy
  (const Handle(IGESDimen_GeneralLabel)& another,
   const Handle(IGESDimen_GeneralLabel)& ent, Interface_CopyTool& TC) const
{
  DeclareAndCast(IGESDimen_GeneralNote, note,
		 TC.Transferred(another->Note()));
  Standard_Integer nbval = another->NbLeaders();

  Handle(IGESDimen_HArray1OfLeaderArrow) leaders = 
    new IGESDimen_HArray1OfLeaderArrow(1, nbval);
  for (Standard_Integer i = 1; i <= nbval; i++)
    {
      DeclareAndCast(IGESDimen_LeaderArrow, new_ent, 
		     TC.Transferred(another->Leader(i)));
      leaders->SetValue(i, new_ent);
    }
  ent->Init(note, leaders);
}

IGESData_DirChecker  IGESDimen_ToolGeneralLabel::DirChecker
  (const Handle(IGESDimen_GeneralLabel)& /* ent */ ) const 
{ 
  IGESData_DirChecker DC (210, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);
  DC.UseFlagRequired(1);
  return DC;
}

void  IGESDimen_ToolGeneralLabel::OwnCheck
  (const Handle(IGESDimen_GeneralLabel)& /* ent */,
   const Interface_ShareTool& , Handle(Interface_Check)& /* ach */) const 
{
}

void  IGESDimen_ToolGeneralLabel::OwnDump
  (const Handle(IGESDimen_GeneralLabel)& ent, const IGESData_IGESDumper& dumper,
   const Handle(Message_Messenger)& S, const Standard_Integer level) const 
{ 
  Standard_Integer sublevel = (level > 4) ? 1 : 0;

  S << "IGESDimen_GeneralLabel" << endl;
  S << "General Note Entity : ";
  dumper.Dump(ent->Note(),S, sublevel);
  S << endl;
  S << "Number of Leaders : " << ent->NbLeaders() << endl;
  S << "Leaders : "; 
  IGESData_DumpEntities(S,dumper ,level,1, ent->NbLeaders(),ent->Leader);
  S << endl;
}

