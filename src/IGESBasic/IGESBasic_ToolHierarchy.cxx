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

#include <IGESBasic_ToolHierarchy.ixx>
#include <IGESData_ParamCursor.hxx>


IGESBasic_ToolHierarchy::IGESBasic_ToolHierarchy ()    {  }


void  IGESBasic_ToolHierarchy::ReadOwnParams
  (const Handle(IGESBasic_Hierarchy)& ent,
   const Handle(IGESData_IGESReaderData)& /*IR*/, IGESData_ParamReader& PR) const
{
  Standard_Integer tempNbPropertyValues;
  Standard_Integer tempLineFont;
  Standard_Integer tempView;
  Standard_Integer tempEntityLevel;
  Standard_Integer tempBlankStatus;
  Standard_Integer tempLineWeight;
  Standard_Integer tempColorNum;
  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed

  //szv#4:S4163:12Mar99 `st=` not needed
  PR.ReadInteger(PR.Current(),"No. of Property values",tempNbPropertyValues);
  PR.ReadInteger(PR.Current(),"LineFont",tempLineFont);
  PR.ReadInteger(PR.Current(),"View",tempView);
  PR.ReadInteger(PR.Current(),"Entity level",tempEntityLevel);
  PR.ReadInteger(PR.Current(),"Blank status",tempBlankStatus);
  PR.ReadInteger(PR.Current(),"Line weight",tempLineWeight);
  PR.ReadInteger(PR.Current(),"Color number",tempColorNum);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init(tempNbPropertyValues,tempLineFont,tempView,tempEntityLevel,
	    tempBlankStatus,tempLineWeight,tempColorNum);
}

void  IGESBasic_ToolHierarchy::WriteOwnParams
  (const Handle(IGESBasic_Hierarchy)& ent, IGESData_IGESWriter& IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->NewLineFont());
  IW.Send(ent->NewView());
  IW.Send(ent->NewEntityLevel());
  IW.Send(ent->NewBlankStatus());
  IW.Send(ent->NewLineWeight());
  IW.Send(ent->NewColorNum());
}

void  IGESBasic_ToolHierarchy::OwnShared
  (const Handle(IGESBasic_Hierarchy)& /*ent*/, Interface_EntityIterator& /*iter*/) const
{
}

void  IGESBasic_ToolHierarchy::OwnCopy
  (const Handle(IGESBasic_Hierarchy)& another,
   const Handle(IGESBasic_Hierarchy)& ent, Interface_CopyTool& /*TC*/) const
{
  ent->Init(6,another->NewLineFont(), another->NewView(),
	    another->NewEntityLevel(),another->NewBlankStatus(),
	    another->NewLineWeight(), another->NewColorNum());
}

Standard_Boolean  IGESBasic_ToolHierarchy::OwnCorrect
  (const Handle(IGESBasic_Hierarchy)& ent) const
{
  Standard_Boolean res = (ent->NbPropertyValues() != 6);
  if (res) ent->Init
    (6,ent->NewLineFont(),ent->NewView(),ent->NewEntityLevel(),
     ent->NewBlankStatus(),ent->NewLineWeight(),ent->NewColorNum());
  return res;    // nbpropertyvalues=6
}

IGESData_DirChecker  IGESBasic_ToolHierarchy::DirChecker
  (const Handle(IGESBasic_Hierarchy)& /*ent*/) const
{
  IGESData_DirChecker DC(406,10);  //Form no = 10 & Type = 406
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void  IGESBasic_ToolHierarchy::OwnCheck
  (const Handle(IGESBasic_Hierarchy)& ent,
   const Interface_ShareTool& , Handle(Interface_Check)& ach) const
{
  if (ent->NbPropertyValues() != 6)
    ach->AddFail("Number of Property Values != 6");
  if (ent->NewLineFont() != 0 && ent->NewLineFont() != 1)
    ach->AddFail("InCorrect LineFont");
  if (ent->NewView() != 0 && ent->NewView() != 1)
    ach->AddFail("InCorrect View");
  if (ent->NewEntityLevel() != 0 && ent->NewEntityLevel() != 1)
    ach->AddFail("InCorrect EntityLevel");
  if (ent->NewBlankStatus() != 0 && ent->NewBlankStatus() != 1)
    if (ent->NewLineWeight() != 0 && ent->NewLineWeight() != 1)
      ach->AddFail("InCorrect LineWeight");
  if (ent->NewColorNum() != 0 && ent->NewColorNum() != 1)
    ach->AddFail("InCorrect ColorNum");
}

void  IGESBasic_ToolHierarchy::OwnDump
  (const Handle(IGESBasic_Hierarchy)& ent, const IGESData_IGESDumper& /*dumper*/,
   const Handle(Message_Messenger)& S, const Standard_Integer /*level*/) const
{
  S << "IGESBasic_Hierarchy" << endl;

  S << "Number of property values : " << ent->NbPropertyValues() << endl;
  S << "Line Font    : " << ent->NewLineFont() << endl;
  S << "View Number  : " << ent->NewView() << endl;
  S << "Entity level : " << ent->NewEntityLevel() << endl;
  S << "Blank status : " << ent->NewBlankStatus() << endl;
  S << "Line weight  : " << ent->NewLineWeight() << endl;
  S << "Color number : " << ent->NewColorNum() << endl;
}
