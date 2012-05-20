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

#include <IGESAppli_ToolDrilledHole.ixx>
#include <IGESData_ParamCursor.hxx>
#include <IGESData_LevelListEntity.hxx>


IGESAppli_ToolDrilledHole::IGESAppli_ToolDrilledHole ()    {  }


void  IGESAppli_ToolDrilledHole::ReadOwnParams
  (const Handle(IGESAppli_DrilledHole)& ent,
   const Handle(IGESData_IGESReaderData)& /*IR*/, IGESData_ParamReader& PR) const
{
  Standard_Integer tempNbPropertyValues;
  Standard_Real    tempDrillDiaSize;
  Standard_Real    tempFinishDiaSize;
  Standard_Integer tempPlatingFlag;
  Standard_Integer tempNbLowerLayer;
  Standard_Integer tempNbHigherLayer;
  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed

  //szv#4:S4163:12Mar99 `st=` not needed
  PR.ReadInteger(PR.Current(),"No. of Property values",tempNbPropertyValues);
  PR.ReadReal(PR.Current(),"Drill diameter size",tempDrillDiaSize);
  PR.ReadReal(PR.Current(),"Finish diameter size",tempFinishDiaSize);
  PR.ReadInteger(PR.Current(),"Plating Flag",tempPlatingFlag);
  PR.ReadInteger(PR.Current(),"Lower numbered layer", tempNbLowerLayer);
  PR.ReadInteger(PR.Current(),"Higher numbered layer", tempNbHigherLayer);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init(tempNbPropertyValues,tempDrillDiaSize,tempFinishDiaSize,
	    tempPlatingFlag, tempNbLowerLayer,tempNbHigherLayer);
}

void  IGESAppli_ToolDrilledHole::WriteOwnParams
  (const Handle(IGESAppli_DrilledHole)& ent, IGESData_IGESWriter& IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->DrillDiaSize());
  IW.Send(ent->FinishDiaSize());
  IW.SendBoolean(ent->IsPlating());
  IW.Send(ent->NbLowerLayer());
  IW.Send(ent->NbHigherLayer());
}

void  IGESAppli_ToolDrilledHole::OwnShared
  (const Handle(IGESAppli_DrilledHole)& /*ent*/, Interface_EntityIterator& /*iter*/) const
{
}

void  IGESAppli_ToolDrilledHole::OwnCopy
  (const Handle(IGESAppli_DrilledHole)& another,
   const Handle(IGESAppli_DrilledHole)& ent, Interface_CopyTool& /*TC*/) const
{
  ent->Init
    (5,another->DrillDiaSize(),another->FinishDiaSize(),
     (another->IsPlating() ? 1 : 0),
     another->NbLowerLayer(),another->NbHigherLayer());
}


Standard_Boolean  IGESAppli_ToolDrilledHole::OwnCorrect
  (const Handle(IGESAppli_DrilledHole)& ent) const
{
  Standard_Boolean res = (ent->NbPropertyValues() != 5);
  if (res) ent->Init
    (5,ent->DrillDiaSize(),ent->FinishDiaSize(),(ent->IsPlating() ? 1 : 0),
     ent->NbLowerLayer(),ent->NbHigherLayer());
  if (ent->SubordinateStatus() != 0) {
    Handle(IGESData_LevelListEntity) nulevel;
    ent->InitLevel(nulevel,0);
    res = Standard_True;
  }   // NbPropertyvalues = 5 + RAZ level selon subordinate
  return res;
}

IGESData_DirChecker  IGESAppli_ToolDrilledHole::DirChecker
  (const Handle(IGESAppli_DrilledHole)& /*ent*/) const
{
  IGESData_DirChecker DC(406,6);  //Form no = 6 & Type = 406
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void  IGESAppli_ToolDrilledHole::OwnCheck
  (const Handle(IGESAppli_DrilledHole)& ent,
   const Interface_ShareTool& , Handle(Interface_Check)& ach) const
{
  if (ent->SubordinateStatus() != 0)
    if (ent->DefLevel() != IGESData_DefOne &&
	ent->DefLevel() != IGESData_DefSeveral)
      ach->AddFail("Level type : Not value/reference");
  if (ent->NbPropertyValues() != 5)
    ach->AddFail("Number of Property Values != 5");
}

void  IGESAppli_ToolDrilledHole::OwnDump
  (const Handle(IGESAppli_DrilledHole)& ent, const IGESData_IGESDumper& /*dumper*/,
   const Handle(Message_Messenger)& S, const Standard_Integer /*level*/) const
{
  S << "IGESAppli_DrilledHole" << endl;

  S << "Number of property values : " << ent->NbPropertyValues() << endl;
  S << "Drill  diameter size :" << ent->DrillDiaSize() << "  ";
  S << "Finish diameter size : "  << ent->FinishDiaSize() << endl;
  S << "Plating indication flag : ";
  if (!ent->IsPlating())   S << "NO"  << "  -  ";
  else                     S << "YES" << "  -  ";
  S << "Lower Numbered Layer  : " << ent->NbLowerLayer() << "  ";
  S << "Higher Numbered Layer : " << ent->NbHigherLayer() << endl;
}
