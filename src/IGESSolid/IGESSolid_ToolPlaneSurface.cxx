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

#include <IGESSolid_ToolPlaneSurface.ixx>
#include <IGESData_ParamCursor.hxx>
#include <IGESGeom_Point.hxx>
#include <IGESGeom_Direction.hxx>
#include <Interface_Macros.hxx>


// MGE 31/07/98
#include <Message_Msg.hxx>
#include <IGESData_Status.hxx>

//=======================================================================
//function : IGESSolid_ToolPlaneSurface
//purpose  : 
//=======================================================================

IGESSolid_ToolPlaneSurface::IGESSolid_ToolPlaneSurface ()
{
}


//=======================================================================
//function : ReadOwnParams
//purpose  : 
//=======================================================================

void IGESSolid_ToolPlaneSurface::ReadOwnParams(const Handle(IGESSolid_PlaneSurface)& ent,
                                               const Handle(IGESData_IGESReaderData)& IR,
                                               IGESData_ParamReader& PR) const
{
  Handle(IGESGeom_Point) tempLocation;
  Handle(IGESGeom_Direction) tempNormal;
  Handle(IGESGeom_Direction) tempRefdir;          // default Unparametrised
  IGESData_Status aStatus;
  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed

  if (!PR.ReadEntity(IR, PR.Current(),aStatus,STANDARD_TYPE(IGESGeom_Point), tempLocation)){ //szv#4:S4163:12Mar99 `st=` not needed
    Message_Msg Msg174("XSTEP_174");
    switch(aStatus) {
    case IGESData_ReferenceError: {  
      Message_Msg Msg216 ("IGES_216");
      Msg174.Arg(Msg216.Value());
      PR.SendFail(Msg174);
      break; }
    case IGESData_EntityError: {
      Message_Msg Msg217 ("IGES_217");
      Msg174.Arg(Msg217.Value());
      PR.SendFail(Msg174);
      break; }
    case IGESData_TypeError: {
      Message_Msg Msg218 ("IGES_218");
      Msg174.Arg(Msg218.Value());
      PR.SendFail(Msg174);
      break; }
    default:{
    }
    }
  }
/*
  st = PR.ReadEntity(IR, PR.Current(), "Point on axis",
		     STANDARD_TYPE(IGESGeom_Point), tempLocation);
*/
  if (!PR.ReadEntity(IR, PR.Current(),aStatus,STANDARD_TYPE(IGESGeom_Direction), tempNormal)){ //szv#4:S4163:12Mar99 `st=` not needed
    Message_Msg Msg175("XSTEP_175");
    switch(aStatus) {
    case IGESData_ReferenceError: {  
      Message_Msg Msg216 ("IGES_216");
      Msg175.Arg(Msg216.Value());
      PR.SendFail(Msg175);
      break; }
    case IGESData_EntityError: {
      Message_Msg Msg217 ("IGES_217");
      Msg175.Arg(Msg217.Value());
      PR.SendFail(Msg175);
      break; }
    case IGESData_TypeError: {
      Message_Msg Msg218 ("IGES_218");
      Msg175.Arg(Msg218.Value());
      PR.SendFail(Msg175);
      break; }
    default:{
    }
    }
}
/*
  st = PR.ReadEntity(IR, PR.Current(), "Normal direction",
		     STANDARD_TYPE(IGESGeom_Direction), tempNormal);
*/
  if (ent->FormNumber() == 1){
      // Parametrised surface
    if (!PR.ReadEntity(IR, PR.Current(), aStatus, STANDARD_TYPE(IGESGeom_Direction), tempRefdir)){ //szv#4:S4163:12Mar99 `st=` not needed
      Message_Msg Msg176("XSTEP_176");
      switch(aStatus) {
      case IGESData_ReferenceError: {  
	Message_Msg Msg216 ("IGES_216");
	Msg176.Arg(Msg216.Value());
	PR.SendFail(Msg176);
	break; }
      case IGESData_EntityError: {
	Message_Msg Msg217 ("IGES_217");
	Msg176.Arg(Msg217.Value());
	PR.SendFail(Msg176);
	break; }
      case IGESData_TypeError: {
	Message_Msg Msg218 ("IGES_218");
	Msg176.Arg(Msg218.Value());
	PR.SendFail(Msg176);
	break; }
      default:{
      }
      }
    }
  }
/*
    st = PR.ReadEntity(IR, PR.Current(), "Reference direction",
		       STANDARD_TYPE(IGESGeom_Direction), tempRefdir);
*/
  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init (tempLocation, tempNormal, tempRefdir);
}


//=======================================================================
//function : WriteOwnParams
//purpose  : 
//=======================================================================

void IGESSolid_ToolPlaneSurface::WriteOwnParams
  (const Handle(IGESSolid_PlaneSurface)& ent, IGESData_IGESWriter& IW) const
{
  IW.Send(ent->LocationPoint());
  IW.Send(ent->Normal());
  if (ent->IsParametrised())    IW.Send(ent->ReferenceDir());
}


//=======================================================================
//function : OwnShared
//purpose  : 
//=======================================================================

void IGESSolid_ToolPlaneSurface::OwnShared(const Handle(IGESSolid_PlaneSurface)& ent,
                                           Interface_EntityIterator& iter) const
{
  iter.GetOneItem(ent->LocationPoint());
  iter.GetOneItem(ent->Normal());
  iter.GetOneItem(ent->ReferenceDir());
}


//=======================================================================
//function : OwnCopy
//purpose  : 
//=======================================================================

void IGESSolid_ToolPlaneSurface::OwnCopy
  (const Handle(IGESSolid_PlaneSurface)& another,
   const Handle(IGESSolid_PlaneSurface)& ent, Interface_CopyTool& TC) const
{
  DeclareAndCast(IGESGeom_Point, tempLocation,
		 TC.Transferred(another->LocationPoint()));
  DeclareAndCast(IGESGeom_Direction, tempNormal,
		 TC.Transferred(another->Normal()));
  if (another->IsParametrised())
    {
      DeclareAndCast(IGESGeom_Direction, tempRefdir,
		     TC.Transferred(another->ReferenceDir()));
      ent->Init (tempLocation, tempNormal, tempRefdir);
    }
  else
    {
      Handle(IGESGeom_Direction) tempRefdir;
      ent->Init (tempLocation, tempNormal, tempRefdir);
    }
}


//=======================================================================
//function : DirChecker
//purpose  : 
//=======================================================================

IGESData_DirChecker IGESSolid_ToolPlaneSurface::DirChecker
  (const Handle(IGESSolid_PlaneSurface)& /*ent*/) const
{
  IGESData_DirChecker DC(190, 0, 1);

  DC.Structure  (IGESData_DefVoid);
  DC.LineFont   (IGESData_DefAny);
  DC.Color      (IGESData_DefAny);

  DC.BlankStatusIgnored ();
  DC.HierarchyStatusIgnored ();
  return DC;
}


//=======================================================================
//function : OwnCheck
//purpose  : 
//=======================================================================

void IGESSolid_ToolPlaneSurface::OwnCheck(const Handle(IGESSolid_PlaneSurface)& ent,
                                          const Interface_ShareTool&,
                                          Handle(Interface_Check)& ach) const
{

  // MGE 31/07/98
  // Building of messages
  //========================================
  //Message_Msg Msg177("XSTEP_177");
  //========================================

  Standard_Integer fn = 0;
  if (ent->IsParametrised()) fn = 1;
  if (fn != ent->FormNumber()) {
    Message_Msg Msg177("XSTEP_177");
    ach->SendFail (Msg177);
  }
}


//=======================================================================
//function : OwnDump
//purpose  : 
//=======================================================================

void IGESSolid_ToolPlaneSurface::OwnDump(const Handle(IGESSolid_PlaneSurface)& ent,
                                         const IGESData_IGESDumper& dumper,
                                         const Handle(Message_Messenger)& S,
                                         const Standard_Integer level) const
{
  S << "IGESSolid_PlaneSurface" << endl;

  Standard_Integer sublevel = (level <= 4) ? 0 : 1;
  S << "Point on axis    : ";
  dumper.Dump(ent->LocationPoint(),S, sublevel);
  S << endl;
  S << "Normal direction : ";
  dumper.Dump(ent->Normal(),S, sublevel);
  S << endl;
  if (ent->IsParametrised())
    {
      S << "Surface is Parametrised  -  Reference direction : ";
      dumper.Dump(ent->ReferenceDir(),S, sublevel);
      S << endl;
    }
  else S << "Surface is UnParametrised" << endl;
}
