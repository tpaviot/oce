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

#include <IGESAppli_ToolReferenceDesignator.ixx>
#include <IGESData_ParamCursor.hxx>
#include <TCollection_HAsciiString.hxx>
#include <IGESData_LevelListEntity.hxx>
#include <Interface_Macros.hxx>
#include <IGESData_Dump.hxx>


IGESAppli_ToolReferenceDesignator::IGESAppli_ToolReferenceDesignator ()    {  }


void  IGESAppli_ToolReferenceDesignator::ReadOwnParams
  (const Handle(IGESAppli_ReferenceDesignator)& ent,
   const Handle(IGESData_IGESReaderData)& /* IR */, IGESData_ParamReader& PR) const
{
  Standard_Integer tempNbPropertyValues;
  Handle(TCollection_HAsciiString) tempReferenceDesignator;
  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed

  //szv#4:S4163:12Mar99 `st=` not needed
  PR.ReadInteger(PR.Current(),"Number of property values",tempNbPropertyValues);
  PR.ReadText(PR.Current(),"ReferenceDesignator",tempReferenceDesignator);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init(tempNbPropertyValues,tempReferenceDesignator);
}

void  IGESAppli_ToolReferenceDesignator::WriteOwnParams
  (const Handle(IGESAppli_ReferenceDesignator)& ent, IGESData_IGESWriter& IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->RefDesignatorText());
}

void  IGESAppli_ToolReferenceDesignator::OwnShared
  (const Handle(IGESAppli_ReferenceDesignator)& /* ent */, Interface_EntityIterator& /* iter */) const
{
}

void  IGESAppli_ToolReferenceDesignator::OwnCopy
  (const Handle(IGESAppli_ReferenceDesignator)& another,
   const Handle(IGESAppli_ReferenceDesignator)& ent, Interface_CopyTool& /* TC */) const
{
  Standard_Integer aNbPropertyValues;
  Handle(TCollection_HAsciiString) aReferenceDesignator =
    new TCollection_HAsciiString(another->RefDesignatorText());
  aNbPropertyValues = another->NbPropertyValues();
  ent->Init(aNbPropertyValues,aReferenceDesignator);
}

Standard_Boolean  IGESAppli_ToolReferenceDesignator::OwnCorrect
  (const Handle(IGESAppli_ReferenceDesignator)& ent) const
{
  Standard_Boolean res = (ent->NbPropertyValues() != 1);
  if (res) ent->Init(1,ent->RefDesignatorText());
//         nbpropertyvalues=1
  if (ent->SubordinateStatus() != 0) {
    Handle(IGESData_LevelListEntity) nulevel;
    ent->InitLevel(nulevel,0);
    res = Standard_True;
  }
  return res;    // + RAZ level selon subordibate
}

IGESData_DirChecker  IGESAppli_ToolReferenceDesignator::DirChecker
  (const Handle(IGESAppli_ReferenceDesignator)& /* ent */ ) const
{
  //UNFINISHED
  IGESData_DirChecker DC(406,7);  //Form no = 7 & Type = 406
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void  IGESAppli_ToolReferenceDesignator::OwnCheck
  (const Handle(IGESAppli_ReferenceDesignator)& ent,
   const Interface_ShareTool& , Handle(Interface_Check)& ach) const
{
  if (ent->SubordinateStatus() != 0)
    //the level is ignored if this property is subordinate
    if (ent->DefLevel() != IGESData_DefOne &&
	ent->DefLevel() != IGESData_DefSeveral)
      ach->AddFail("Level type: Not value/reference");
  if (ent->NbPropertyValues() != 1)
    ach->AddFail("Number of Property Values != 1");
  //UNFINISHED
  //the level is ignored if this property is subordinate -- queried
}

void  IGESAppli_ToolReferenceDesignator::OwnDump
  (const Handle(IGESAppli_ReferenceDesignator)& ent, const IGESData_IGESDumper& /* dumper */,
   const Handle(Message_Messenger)& S, const Standard_Integer /* level */) const
{
  S << "IGESAppli_ReferenceDesignator" << endl;
  S << "Number of Property Values : " << ent->NbPropertyValues() << endl;
  S << "ReferenceDesignator : ";
  IGESData_DumpString(S,ent->RefDesignatorText());
  S << endl;
}
