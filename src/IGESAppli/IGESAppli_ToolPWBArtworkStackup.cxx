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

#include <IGESAppli_ToolPWBArtworkStackup.ixx>
#include <IGESData_ParamCursor.hxx>
#include <TCollection_HAsciiString.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <IGESData_Dump.hxx>
#include <Interface_Macros.hxx>


IGESAppli_ToolPWBArtworkStackup::IGESAppli_ToolPWBArtworkStackup ()    {  }


void  IGESAppli_ToolPWBArtworkStackup::ReadOwnParams
  (const Handle(IGESAppli_PWBArtworkStackup)& ent,
   const Handle(IGESData_IGESReaderData)& /* IR */, IGESData_ParamReader& PR) const
{
  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed
  Standard_Integer num;
  Standard_Integer tempNbPropertyValues;
  Handle(TCollection_HAsciiString) tempArtworkStackupIdent;
  Handle(TColStd_HArray1OfInteger) tempLevelNumbers;
  //szv#4:S4163:12Mar99 `st=` not needed
  PR.ReadInteger(PR.Current(), "Number of property values", tempNbPropertyValues);
  PR.ReadText(PR.Current(), "Artwork Stackup Identification", tempArtworkStackupIdent);
  if (!PR.ReadInteger(PR.Current(), "Number of level numbers", num)) num = 0;
  if (num > 0) tempLevelNumbers = new TColStd_HArray1OfInteger(1, num);
  else  PR.AddFail("Number of level numbers: Not Positive");
  if (!tempLevelNumbers.IsNull())
    PR.ReadInts(PR.CurrentList(num), "Level Numbers", tempLevelNumbers);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init (tempNbPropertyValues, tempArtworkStackupIdent, tempLevelNumbers);
}

void  IGESAppli_ToolPWBArtworkStackup::WriteOwnParams
  (const Handle(IGESAppli_PWBArtworkStackup)& ent, IGESData_IGESWriter& IW) const
{
  Standard_Integer i, num;
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->Identification());
  IW.Send(ent->NbLevelNumbers());
  for ( num = ent->NbLevelNumbers(), i = 1; i <= num; i++ )
    IW.Send(ent->LevelNumber(i));
}

void  IGESAppli_ToolPWBArtworkStackup::OwnShared
  (const Handle(IGESAppli_PWBArtworkStackup)& /* ent */, Interface_EntityIterator& /* iter */) const
{
}

void  IGESAppli_ToolPWBArtworkStackup::OwnCopy
  (const Handle(IGESAppli_PWBArtworkStackup)& another,
   const Handle(IGESAppli_PWBArtworkStackup)& ent, Interface_CopyTool& /* TC */) const
{
  Standard_Integer num = another->NbLevelNumbers();
  Standard_Integer tempNbPropertyValues = another->NbPropertyValues();
  Handle(TCollection_HAsciiString) tempArtworkStackupIdent =
    new TCollection_HAsciiString(another->Identification());
  Handle(TColStd_HArray1OfInteger) tempLevelNumbers =
    new TColStd_HArray1OfInteger(1, num);
  for ( Standard_Integer i = 1; i <= num; i++ )
    tempLevelNumbers->SetValue(i, another->LevelNumber(i));
  ent->Init(tempNbPropertyValues, tempArtworkStackupIdent, tempLevelNumbers);
}

IGESData_DirChecker  IGESAppli_ToolPWBArtworkStackup::DirChecker
  (const Handle(IGESAppli_PWBArtworkStackup)& /* ent */ ) const
{
  IGESData_DirChecker DC(406, 25);
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

void  IGESAppli_ToolPWBArtworkStackup::OwnCheck
  (const Handle(IGESAppli_PWBArtworkStackup)& /* ent */,
   const Interface_ShareTool& , Handle(Interface_Check)& /* ach */) const
{
}

void  IGESAppli_ToolPWBArtworkStackup::OwnDump
  (const Handle(IGESAppli_PWBArtworkStackup)& ent, const IGESData_IGESDumper& /* dumper */,
   const Handle(Message_Messenger)& S, const Standard_Integer level) const
{
  S << "IGESAppli_PWBArtworkStackup" << endl;
  S << "Number of property values : " << ent->NbPropertyValues() << endl;
  S << "Artwork Stackup Identification : ";
  IGESData_DumpString(S,ent->Identification());
  S << endl;
  S << "Level Numbers : ";
  IGESData_DumpVals(S ,level,1, ent->NbLevelNumbers(),ent->LevelNumber);
  S << endl;
}
