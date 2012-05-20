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

#include <IGESGraph_ToolDrawingSize.ixx>
#include <IGESData_ParamCursor.hxx>


IGESGraph_ToolDrawingSize::IGESGraph_ToolDrawingSize ()    {  }


void IGESGraph_ToolDrawingSize::ReadOwnParams
  (const Handle(IGESGraph_DrawingSize)& ent,
   const Handle(IGESData_IGESReaderData)& /*IR*/, IGESData_ParamReader& PR) const
{ 
  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed

  Standard_Integer nbPropertyValues;
  Standard_Real    xSize;
  Standard_Real    ySize; 

  // Reading nbPropertyValues(Integer)
  PR.ReadInteger(PR.Current(), "No. of property values", nbPropertyValues); //szv#4:S4163:12Mar99 `st=` not needed
  if (nbPropertyValues != 2)
    PR.AddFail("No. of Property values : Value is not 2");

  // Reading xSize(Real)
  PR.ReadReal (PR.Current(), "Drawing extent along +ve XD axis", xSize); //szv#4:S4163:12Mar99 `st=` not needed

  // Reading ySize(Real)
  PR.ReadReal (PR.Current(), "Drawing extent along +ve YD axis", ySize); //szv#4:S4163:12Mar99 `st=` not needed

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init(nbPropertyValues, xSize, ySize);
}

void IGESGraph_ToolDrawingSize::WriteOwnParams
  (const Handle(IGESGraph_DrawingSize)& ent, IGESData_IGESWriter& IW)  const
{ 
  IW.Send( ent->NbPropertyValues() );
  IW.Send( ent->XSize() );
  IW.Send( ent->YSize() );
}

void  IGESGraph_ToolDrawingSize::OwnShared
  (const Handle(IGESGraph_DrawingSize)& /*ent*/, Interface_EntityIterator& /*iter*/) const
{
}

void IGESGraph_ToolDrawingSize::OwnCopy
  (const Handle(IGESGraph_DrawingSize)& another,
   const Handle(IGESGraph_DrawingSize)& ent, Interface_CopyTool& /*TC*/) const
{
  ent->Init(2,another->XSize(),another->YSize());
}

Standard_Boolean  IGESGraph_ToolDrawingSize::OwnCorrect
  (const Handle(IGESGraph_DrawingSize)& ent) const
{
  Standard_Boolean res = (ent->NbPropertyValues() != 2);
  if (res) ent->Init(2,ent->XSize(),ent->YSize());    // nbpropertyvalues=2
  return res;
}

IGESData_DirChecker IGESGraph_ToolDrawingSize::DirChecker
  (const Handle(IGESGraph_DrawingSize)& /*ent*/)  const
{ 
  IGESData_DirChecker DC (406, 16);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void IGESGraph_ToolDrawingSize::OwnCheck
  (const Handle(IGESGraph_DrawingSize)& ent,
   const Interface_ShareTool& , Handle(Interface_Check)& ach)  const
{
  if (ent->NbPropertyValues() != 2)
    ach->AddFail("No. of Property values : Value != 2");
}

void IGESGraph_ToolDrawingSize::OwnDump
  (const Handle(IGESGraph_DrawingSize)& ent, const IGESData_IGESDumper& /*dumper*/,
   const Handle(Message_Messenger)& S, const Standard_Integer /*level*/)  const
{
  S << "IGESGraph_DrawingSize" << endl;

  S << "No. of property values : " << ent->NbPropertyValues() << endl;
  S << "Drawing extent along positive X-axis : " << ent->XSize() << endl;
  S << "Drawing extent along positive Y-axis : " << ent->YSize() << endl;
  S << endl;
}
