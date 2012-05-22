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

#include <IGESBasic_ToolSingularSubfigure.ixx>
#include <IGESData_ParamCursor.hxx>
#include <gp_XYZ.hxx>
#include <IGESBasic_SubfigureDef.hxx>
#include <IGESData_Dump.hxx>
#include <gp_GTrsf.hxx>
#include <Interface_Macros.hxx>

// MGE 03/08/98
#include <Message_Msg.hxx>
#include <IGESData_Status.hxx>


IGESBasic_ToolSingularSubfigure::IGESBasic_ToolSingularSubfigure ()    {  }


void  IGESBasic_ToolSingularSubfigure::ReadOwnParams
  (const Handle(IGESBasic_SingularSubfigure)& ent,
   const Handle(IGESData_IGESReaderData)& IR, IGESData_ParamReader& PR) const
{
  // MGE 03/08/98
  // Building of messages
  //========================================
  Message_Msg Msg213("XSTEP_213");
  //========================================

  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed
  Standard_Boolean temphasscale;
  Standard_Real tempScaleFactor;
  Handle(IGESBasic_SubfigureDef) tempSubfigureDef;
  gp_XYZ tempTranslation;
  IGESData_Status aStatus;

  if(!PR.ReadEntity(IR,PR.Current(),aStatus,STANDARD_TYPE(IGESBasic_SubfigureDef),tempSubfigureDef)){ //szv#4:S4163:12Mar99 `st=` not needed;
    Message_Msg Msg212("XSTEP_212");
    switch(aStatus) {
    case IGESData_ReferenceError: {  
      Message_Msg Msg216 ("IGES_216");
      Msg212.Arg(Msg216.Value());
      PR.SendFail(Msg212);
      break; }
    case IGESData_EntityError: {
      Message_Msg Msg217 ("IGES_217");
      Msg212.Arg(Msg217.Value());
      PR.SendFail(Msg212);
      break; }
    case IGESData_TypeError: {
      Message_Msg Msg218 ("IGES_218");
      Msg212.Arg(Msg218.Value());
      PR.SendFail(Msg212);
      break; }
    default:{
    }
    }
  }
  PR.ReadXYZ (PR.CurrentList(1, 3),Msg213,tempTranslation); //szv#4:S4163:12Mar99 `st=` not needed
//st = PR.ReadEntity(IR,PR.Current(),"Subfigure definition entity",
//                   STANDARD_TYPE(IGESBasic_SubfigureDef), tempSubfigureDef);
//st = PR.ReadXYZ
//  (PR.CurrentList(1, 3),"Translation data",tempTranslation);
  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(),Msg214,tempScaleFactor); //szv#4:S4163:12Mar99 moved down
      //st = PR.ReadReal(PR.Current(),"Scale Factor",tempScaleFactor); 
      temphasscale = PR.ReadReal(PR.Current(),tempScaleFactor);
      if (!temphasscale){
	Message_Msg Msg214("XSTEP_214");
	PR.SendFail(Msg214);
      }
    }
  else
    {
      tempScaleFactor = 1.0;
      temphasscale = Standard_False;
    }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init
    (tempSubfigureDef,tempTranslation,temphasscale,tempScaleFactor);
}

void  IGESBasic_ToolSingularSubfigure::WriteOwnParams
  (const Handle(IGESBasic_SingularSubfigure)& ent, IGESData_IGESWriter& IW) const
{
  IW.Send(ent->Subfigure());
  IW.Send(ent->Translation().X());
  IW.Send(ent->Translation().Y());
  IW.Send(ent->Translation().Z());
  if (ent->HasScaleFactor()) IW.Send(ent->ScaleFactor());
  else IW.SendVoid();
}

void  IGESBasic_ToolSingularSubfigure::OwnShared
  (const Handle(IGESBasic_SingularSubfigure)& ent, Interface_EntityIterator& iter) const
{
  iter.GetOneItem(ent->Subfigure());
}

void  IGESBasic_ToolSingularSubfigure::OwnCopy
  (const Handle(IGESBasic_SingularSubfigure)& another,
   const Handle(IGESBasic_SingularSubfigure)& ent, Interface_CopyTool& TC) const
{
  gp_XYZ aTranslation;
  Standard_Boolean ahasScale;
  Standard_Real aScale;

  DeclareAndCast
    (IGESBasic_SubfigureDef,aSubfigureDef,TC.Transferred(another->Subfigure()));
  aTranslation  = another->Translation();
  ahasScale     = another->HasScaleFactor();
  aScale        = another->ScaleFactor();

  ent->Init(aSubfigureDef,aTranslation,ahasScale,aScale);
}

IGESData_DirChecker  IGESBasic_ToolSingularSubfigure::DirChecker
  (const Handle(IGESBasic_SingularSubfigure)& ent ) const
{
  IGESData_DirChecker DC(408,0);  //TypeNo. 408, Form no. 0
  DC.Structure(IGESData_DefVoid);
  if (ent->HierarchyStatus() == 1)
    DC.GraphicsIgnored(01);   // GraphicsIgnored if Hierarchy = 01
  return DC;
}

void  IGESBasic_ToolSingularSubfigure::OwnCheck
  (const Handle(IGESBasic_SingularSubfigure)& /* ent */,
   const Interface_ShareTool& , Handle(Interface_Check)& /* ach */) const
{
}

void  IGESBasic_ToolSingularSubfigure::OwnDump
  (const Handle(IGESBasic_SingularSubfigure)& ent, const IGESData_IGESDumper& dumper,
   const Handle(Message_Messenger)& S, const Standard_Integer level) const
{
  S << "IGESBasic_SingularSubfigure" << endl;

  S << "Subfigure Definition Entity : " ;
  dumper.Dump(ent->Subfigure(),S,(level <= 4) ? 0 : 1);
  S << endl;
  S << " Translation Data : ";
  IGESData_DumpXYZL(S,level, ent->Translation(), ent->Location());
  S << "  Scale Factors : " << ent->ScaleFactor() << endl;
  S << endl;
}
