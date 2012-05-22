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

#include <IGESDimen_ToolPointDimension.ixx>
#include <IGESData_ParamCursor.hxx>
#include <IGESData_IGESEntity.hxx>
#include <IGESDimen_GeneralNote.hxx>
#include <IGESDimen_LeaderArrow.hxx>
#include <Interface_Macros.hxx>


IGESDimen_ToolPointDimension::IGESDimen_ToolPointDimension ()    {  }


void IGESDimen_ToolPointDimension::ReadOwnParams
  (const Handle(IGESDimen_PointDimension)& ent,
   const Handle(IGESData_IGESReaderData)& IR, IGESData_ParamReader& PR) const
{
  Handle(IGESDimen_GeneralNote) tempNote;
  Handle(IGESDimen_LeaderArrow) leadArr;
  Handle(IGESData_IGESEntity) tempGeom;
  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed

  PR.ReadEntity(IR, PR.Current(), "General Note",
		STANDARD_TYPE(IGESDimen_GeneralNote), tempNote); //szv#4:S4163:12Mar99 `st=` not needed

  PR.ReadEntity(IR, PR.Current(), "Leader",
		STANDARD_TYPE(IGESDimen_LeaderArrow), leadArr); //szv#4:S4163:12Mar99 `st=` not needed

  if (PR.IsParamEntity(PR.CurrentNumber()))
    PR.ReadEntity(IR, PR.Current(), "Enclosing entity", tempGeom); //szv#4:S4163:12Mar99 `st=` not needed

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init(tempNote, leadArr, tempGeom);
}

void IGESDimen_ToolPointDimension::WriteOwnParams
  (const Handle(IGESDimen_PointDimension)& ent, IGESData_IGESWriter& IW) const
{
  IW.Send(ent->Note());
  IW.Send(ent->LeaderArrow());
  IW.Send(ent->Geom());
}

void  IGESDimen_ToolPointDimension::OwnShared
  (const Handle(IGESDimen_PointDimension)& ent, Interface_EntityIterator& iter) const
{
  iter.GetOneItem(ent->Note());
  iter.GetOneItem(ent->LeaderArrow());
  iter.GetOneItem(ent->Geom());
}

void IGESDimen_ToolPointDimension::OwnCopy
  (const Handle(IGESDimen_PointDimension)& another,
   const Handle(IGESDimen_PointDimension)& ent, Interface_CopyTool& TC) const
{
  DeclareAndCast(IGESDimen_GeneralNote, tempNote,
		 TC.Transferred(another->Note()));
  DeclareAndCast(IGESDimen_LeaderArrow, tempArrow,
		 TC.Transferred(another->LeaderArrow()));
  DeclareAndCast(IGESData_IGESEntity, tempGeom,
		 TC.Transferred(another->Geom()));
  ent->Init(tempNote, tempArrow, tempGeom);
}

IGESData_DirChecker IGESDimen_ToolPointDimension::DirChecker
  (const Handle(IGESDimen_PointDimension)& /*ent*/) const
{
  IGESData_DirChecker DC(220, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);

  DC.UseFlagRequired (1);

  return DC;
}

void IGESDimen_ToolPointDimension::OwnCheck
  (const Handle(IGESDimen_PointDimension)& /*ent*/,
   const Interface_ShareTool& , Handle(Interface_Check)& /*ach*/) const
{
}

void IGESDimen_ToolPointDimension::OwnDump
  (const Handle(IGESDimen_PointDimension)& ent, const IGESData_IGESDumper& dumper,
   const Handle(Message_Messenger)& S, const Standard_Integer level) const
{
  S << "IGESDimen_PointDimension" << endl;
  Standard_Integer sublevel = (level <= 4) ? 0 : 1;

  S << "General Note : ";
  dumper.Dump(ent->Note(),S , sublevel);
  S << endl;
  S << "Leader Arrow : ";
  dumper.Dump(ent->LeaderArrow(),S , sublevel);
  S << endl;
  if (!ent->Geom().IsNull())
    {
      S << "Enclosing Entity : ";
      dumper.Dump(ent->Geom(),S , sublevel);
      S << endl;
    }
}
