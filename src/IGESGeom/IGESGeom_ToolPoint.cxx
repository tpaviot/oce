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

#include <IGESGeom_ToolPoint.ixx>
#include <IGESData_ParamCursor.hxx>
#include <IGESBasic_SubfigureDef.hxx>
#include <gp_XYZ.hxx>
#include <gp_Pnt.hxx>
#include <IGESData_Dump.hxx>
#include <Interface_Macros.hxx>

// MGE 28/07/98
#include <Message_Msg.hxx>
#include <IGESData_Status.hxx>

IGESGeom_ToolPoint::IGESGeom_ToolPoint ()    {  }


void IGESGeom_ToolPoint::ReadOwnParams
  (const Handle(IGESGeom_Point)& ent,
   const Handle(IGESData_IGESReaderData)& IR, IGESData_ParamReader& PR) const
{
  // MGE 28/07/98
  // Building of messages
  //==================================
  Message_Msg Msg73("XSTEP_73");
  //==================================

  gp_XYZ aPoint;
  Handle(IGESBasic_SubfigureDef) aSymbol;
  IGESData_Status aStatus;
  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed

  PR.ReadXYZ(PR.CurrentList(1, 3), Msg73, aPoint); //szv#4:S4163:12Mar99 `st=` not needed
  //st = PR.ReadXYZ(PR.CurrentList(1, 3), "Point", aPoint);

  if (PR.DefinedElseSkip()){
    if (!PR.ReadEntity(IR, PR.Current(), aStatus,
		  STANDARD_TYPE(IGESBasic_SubfigureDef), aSymbol, Standard_True)){
      Message_Msg Msg74("XSTEP_74");
      switch(aStatus) {
      case IGESData_ReferenceError: {  
	Message_Msg Msg216 ("IGES_216");
	Msg74.Arg(Msg216.Value());
	PR.SendFail(Msg74);
	break; }
      case IGESData_EntityError: {
	Message_Msg Msg217 ("IGES_217");
	Msg74.Arg(Msg217.Value());
	PR.SendFail(Msg74);
	break; }
      case IGESData_TypeError: {
	Message_Msg Msg218 ("IGES_218");
	Msg74.Arg(Msg218.Value());
	PR.SendFail(Msg74);
	break; }
      default:{
      }
      }
    }
 //szv#4:S4163:12Mar99 `st=` not needed
  }
   // st = PR.ReadEntity(IR, PR.Current(), "Display Symbol",
//		       STANDARD_TYPE(IGESBasic_SubfigureDef), aSymbol, Standard_True);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init(aPoint, aSymbol);
}

void IGESGeom_ToolPoint::WriteOwnParams
  (const Handle(IGESGeom_Point)& ent, IGESData_IGESWriter& IW)  const
{
  IW.Send(ent->Value().X());
  IW.Send(ent->Value().Y());
  IW.Send(ent->Value().Z());
  IW.Send(ent->DisplaySymbol());
}

void  IGESGeom_ToolPoint::OwnShared
  (const Handle(IGESGeom_Point)& ent, Interface_EntityIterator& iter) const
{
  iter.GetOneItem(ent->DisplaySymbol());
}

void IGESGeom_ToolPoint::OwnCopy
  (const Handle(IGESGeom_Point)& another,
   const Handle(IGESGeom_Point)& ent, Interface_CopyTool& TC) const
{
  gp_XYZ aPoint = (another->Value()).XYZ();

  DeclareAndCast(IGESBasic_SubfigureDef, aSymbol, 
                 TC.Transferred(another->DisplaySymbol()));
  ent->Init(aPoint, aSymbol);
}


IGESData_DirChecker IGESGeom_ToolPoint::DirChecker
  (const Handle(IGESGeom_Point)& ent )   const
{
  IGESData_DirChecker DC(116,0);
  DC.Structure(IGESData_DefVoid);
  if (ent->HasDisplaySymbol())
    {
      DC.LineFont(IGESData_DefAny);
      DC.LineWeight(IGESData_DefValue);
    }
  DC.Color(IGESData_DefAny);
  return DC;
}

void IGESGeom_ToolPoint::OwnCheck
  (const Handle(IGESGeom_Point)& /* ent */,
   const Interface_ShareTool& , Handle(Interface_Check)& /* ach */)  const
{
}

void IGESGeom_ToolPoint::OwnDump
  (const Handle(IGESGeom_Point)& ent, const IGESData_IGESDumper& dumper,
   const Handle(Message_Messenger)& S, const Standard_Integer level)  const
{
  S << "IGESGeom_Point" << endl;

  S << " Value         : ";
  IGESData_DumpXYZL(S,level, ent->Value(), ent->Location());
  S << endl;
  S << " Display Symbol : ";
  dumper.Dump(ent->DisplaySymbol(),S, (level <= 4) ? 0 : 1);
  S << endl;
}
