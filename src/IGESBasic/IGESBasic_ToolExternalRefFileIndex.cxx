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

#include <IGESBasic_ToolExternalRefFileIndex.ixx>
#include <IGESData_ParamCursor.hxx>
#include <IGESData_IGESEntity.hxx>
#include <TCollection_HAsciiString.hxx>
#include <IGESData_HArray1OfIGESEntity.hxx>
#include <Interface_HArray1OfHAsciiString.hxx>
#include <IGESData_Dump.hxx>
#include <Interface_Macros.hxx>


IGESBasic_ToolExternalRefFileIndex::IGESBasic_ToolExternalRefFileIndex ()  {  }


void  IGESBasic_ToolExternalRefFileIndex::ReadOwnParams
  (const Handle(IGESBasic_ExternalRefFileIndex)& ent,
   const Handle(IGESData_IGESReaderData)& IR, IGESData_ParamReader& PR) const
{
  //Standard_Boolean st; //szv#4:S4163:12Mar99 moved down
  Standard_Integer num, i;
  Handle(Interface_HArray1OfHAsciiString) tempNames;
  Handle(IGESData_HArray1OfIGESEntity) tempEntities;
  Standard_Boolean st = PR.ReadInteger(PR.Current(), "Number of index entries", num);
  if (st && num > 0)
    {
      tempNames = new Interface_HArray1OfHAsciiString(1, num);
      tempEntities = new IGESData_HArray1OfIGESEntity(1, num);
    }
  else  PR.AddFail("Number of index entries: Not Positive");
  if (!tempNames.IsNull() && !tempEntities.IsNull())
    for ( i = 1; i <= num; i++ )
      {
	Handle(TCollection_HAsciiString) tempNam;
	if (PR.ReadText(PR.Current(), "External Reference Entity", tempNam)) //szv#4:S4163:12Mar99 `st=` not needed
	  tempNames->SetValue(i, tempNam);
	Handle(IGESData_IGESEntity) tempEnt;
	if (PR.ReadEntity(IR, PR.Current(), "Internal Entity", tempEnt)) //szv#4:S4163:12Mar99 `st=` not needed
	  tempEntities->SetValue(i, tempEnt);
      }
  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init(tempNames, tempEntities);
}

void  IGESBasic_ToolExternalRefFileIndex::WriteOwnParams
  (const Handle(IGESBasic_ExternalRefFileIndex)& ent, IGESData_IGESWriter& IW) const
{
  Standard_Integer i, num;
  IW.Send(ent->NbEntries());
  for ( num = ent->NbEntries(), i = 1; i <= num; i++ )
    {
      IW.Send(ent->Name(i));
      IW.Send(ent->Entity(i));
    }
}

void  IGESBasic_ToolExternalRefFileIndex::OwnShared
  (const Handle(IGESBasic_ExternalRefFileIndex)& ent, Interface_EntityIterator& iter) const
{
  Standard_Integer i, num;
  for ( num = ent->NbEntries(), i = 1; i <= num; i++ )
    iter.GetOneItem(ent->Entity(i));
}

void  IGESBasic_ToolExternalRefFileIndex::OwnCopy
  (const Handle(IGESBasic_ExternalRefFileIndex)& another,
   const Handle(IGESBasic_ExternalRefFileIndex)& ent, Interface_CopyTool& TC) const
{
  Standard_Integer num = another->NbEntries();
  Handle(Interface_HArray1OfHAsciiString) tempNames =
    new Interface_HArray1OfHAsciiString(1, num);
  Handle(IGESData_HArray1OfIGESEntity) tempEntities =
    new IGESData_HArray1OfIGESEntity(1, num);
  for ( Standard_Integer i = 1; i <= num; i++ )
    {
      tempNames->SetValue(i, new TCollection_HAsciiString
			  (another->Name(i)));
      DeclareAndCast(IGESData_IGESEntity, new_item,
		     TC.Transferred(another->Entity(i)));
      tempEntities->SetValue(i, new_item);
    }
  ent->Init(tempNames, tempEntities);
}

IGESData_DirChecker  IGESBasic_ToolExternalRefFileIndex::DirChecker
  (const Handle(IGESBasic_ExternalRefFileIndex)& /* ent */ ) const
{
  IGESData_DirChecker DC(402, 12);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void  IGESBasic_ToolExternalRefFileIndex::OwnCheck
  (const Handle(IGESBasic_ExternalRefFileIndex)& /* ent */,
   const Interface_ShareTool& , Handle(Interface_Check)& /* ach */) const
{
}

void  IGESBasic_ToolExternalRefFileIndex::OwnDump
  (const Handle(IGESBasic_ExternalRefFileIndex)& ent, const IGESData_IGESDumper& dumper,
   const Handle(Message_Messenger)& S, const Standard_Integer level) const
{
  Standard_Integer i, num;
  S << "IGESBasic_ExternalRefFileIndex" << endl;
  S << "External Reference Names : " << endl;
  S << "Internal Entities : ";
  IGESData_DumpEntities(S,dumper,-level,1, ent->NbEntries(),ent->Entity);
  S << endl;
  if (level > 4)
    for ( num = ent->NbEntries(), i = 1; i <= num; i++ )
      {
	S << "[" << i << "]: ";
	S << "External Reference Name : ";
	IGESData_DumpString(S,ent->Name(i));
	S << "  Internal Entity : ";
	dumper.Dump (ent->Entity(i),S, 1);
	S << endl;
      }
  S << endl;
}
