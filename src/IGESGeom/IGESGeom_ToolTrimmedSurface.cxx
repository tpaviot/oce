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

#include <IGESGeom_ToolTrimmedSurface.ixx>
#include <IGESData_ParamCursor.hxx>
#include <IGESData_IGESEntity.hxx>
#include <IGESGeom_CurveOnSurface.hxx>
#include <IGESGeom_HArray1OfCurveOnSurface.hxx>
#include <IGESData_Dump.hxx>
#include <Interface_Macros.hxx>

// MGE 31/07/98
#include <Message_Msg.hxx>
#include <IGESData_Status.hxx>

//=======================================================================
//function : IGESGeom_ToolTrimmedSurface
//purpose  : 
//=======================================================================

IGESGeom_ToolTrimmedSurface::IGESGeom_ToolTrimmedSurface ()
{
}


//=======================================================================
//function : ReadOwnParams
//purpose  : 
//=======================================================================

void IGESGeom_ToolTrimmedSurface::ReadOwnParams
  (const Handle(IGESGeom_TrimmedSurface)& ent,
   const Handle(IGESData_IGESReaderData)& IR, IGESData_ParamReader& PR) const
{
  // MGE 31/07/98
  // Building of messages
  //========================================
  //========================================

  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed
  Standard_Integer aFlag;
  Standard_Integer count;
  Handle(IGESData_IGESEntity) aSurface;
  Handle(IGESGeom_CurveOnSurface) anOuter;
  Handle(IGESGeom_HArray1OfCurveOnSurface) anInner;
  IGESData_Status aStatus;

  //szv#4:S4163:12Mar99 `st=` not needed
  if (!PR.ReadEntity(IR, PR.Current(), aStatus, aSurface)){
    Message_Msg Msg169("XSTEP_169");
    switch(aStatus) {
    case IGESData_ReferenceError: {  
      Message_Msg Msg216 ("IGES_216");
      Msg169.Arg(Msg216.Value());
      PR.SendFail(Msg169);
      break; }
    case IGESData_EntityError: {
      Message_Msg Msg217 ("IGES_217");
      Msg169.Arg(Msg217.Value());
      PR.SendFail(Msg169);
      break; }
    default:{
    }
    }
  }
  if (!PR.ReadInteger(PR.Current(), aFlag)){
    Message_Msg Msg170("XSTEP_170");
    PR.SendFail(Msg170);
  }
  //st = PR.ReadInteger(PR.Current(), Msg171, count); //szv#4:S4163:12Mar99 moved in if

/*
  st = PR.ReadEntity(IR, PR.Current(), "Surface to be trimmed", aSurface);
  st = PR.ReadInteger(PR.Current(), "Outer boundary type", aFlag);
  st = PR.ReadInteger(PR.Current(), "Number of inner boundary closed curves", count);
*/
  if (PR.ReadInteger(PR.Current(), count)) {
    if (count < 0){
      Message_Msg Msg171("XSTEP_171");
      PR.SendFail (Msg171);
    }
    else  if (count > 0) anInner =
      new IGESGeom_HArray1OfCurveOnSurface(1, count);
  }
  else {
    Message_Msg Msg171("XSTEP_171");
    PR.SendFail(Msg171);
  }

  if (!PR.ReadEntity(IR, PR.Current(), aStatus,
		STANDARD_TYPE(IGESGeom_CurveOnSurface), anOuter,Standard_True)){
    Message_Msg Msg172("XSTEP_172");
    switch(aStatus) {
    case IGESData_ReferenceError: {  
      Message_Msg Msg216 ("IGES_216");
      Msg172.Arg(Msg216.Value());
      PR.SendFail(Msg172);
      break; }
    case IGESData_EntityError: {
      Message_Msg Msg217 ("IGES_217");
      Msg172.Arg(Msg217.Value());
      PR.SendFail(Msg172);
      break; }
    case IGESData_TypeError: {
      Message_Msg Msg218 ("IGES_218");
      Msg172.Arg(Msg218.Value());
      PR.SendFail(Msg172);
      break; }
    default:{
    }
    }
  } //szv#4:S4163:12Mar99 `st=` not needed
/*  st = PR.ReadEntity(IR, PR.Current(), "Outer boundary curve",
		     STANDARD_TYPE(IGESGeom_CurveOnSurface), anOuter,Standard_True);
*/
  if (! anInner.IsNull()) {
    Standard_Integer I;
    for (I = 1; I <= count; I++ ) {
      Handle(IGESGeom_CurveOnSurface) tempEnt;
      //st = PR.ReadEntity(IR, PR.Current(), Msg173,
			   //STANDARD_TYPE(IGESGeom_CurveOnSurface), tempEnt); //szv#4:S4163:12Mar99 moved in if
/*      st = PR.ReadEntity(IR, PR.Current(), "Inner boundary curves",
			 STANDARD_TYPE(IGESGeom_CurveOnSurface), tempEnt);
*/
      if (PR.ReadEntity(IR, PR.Current(), aStatus, STANDARD_TYPE(IGESGeom_CurveOnSurface), tempEnt))
	anInner->SetValue(I, tempEnt);
      else{
	Message_Msg Msg173("XSTEP_173");
	switch(aStatus) {
	case IGESData_ReferenceError: {  
	  Message_Msg Msg216 ("IGES_216");
	  Msg173.Arg(Msg216.Value());
	  PR.SendFail(Msg173);
	  break; }
	case IGESData_EntityError: {
	  Message_Msg Msg217 ("IGES_217");
	  Msg173.Arg(Msg217.Value());
	  PR.SendFail(Msg173);
	  break; }
	case IGESData_TypeError: {
	  Message_Msg Msg218 ("IGES_218");
	  Msg173.Arg(Msg218.Value());
	  PR.SendFail(Msg173);
	  break; }
	default:{
	}
	}
      }
    }
  }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init(aSurface, aFlag, anOuter, anInner);
}


//=======================================================================
//function : WriteOwnParams
//purpose  : 
//=======================================================================

void IGESGeom_ToolTrimmedSurface::WriteOwnParams
  (const Handle(IGESGeom_TrimmedSurface)& ent, IGESData_IGESWriter& IW)  const
{
  Standard_Integer up  = ent->NbInnerContours();
  IW.Send(ent->Surface());
  IW.Send(ent->OuterBoundaryType());
  IW.Send(up);

  IW.Send(ent->OuterContour());
  Standard_Integer I;
  for (I = 1; I <= up; I ++)
    IW.Send(ent->InnerContour(I));
}


//=======================================================================
//function : OwnShared
//purpose  : 
//=======================================================================

void IGESGeom_ToolTrimmedSurface::OwnShared(const Handle(IGESGeom_TrimmedSurface)& ent,
                                            Interface_EntityIterator& iter) const
{
  Standard_Integer up  = ent->NbInnerContours();
  iter.GetOneItem(ent->Surface());
  iter.GetOneItem(ent->OuterContour());
  Standard_Integer I;
  for (I = 1; I <= up; I ++)  iter.GetOneItem(ent->InnerContour(I));
}


//=======================================================================
//function : OwnCopy
//purpose  : 
//=======================================================================

void IGESGeom_ToolTrimmedSurface::OwnCopy(const Handle(IGESGeom_TrimmedSurface)& another,
                                          const Handle(IGESGeom_TrimmedSurface)& ent,
                                          Interface_CopyTool& TC) const
{
  Handle(IGESGeom_HArray1OfCurveOnSurface) anInner;

  DeclareAndCast(IGESData_IGESEntity, aSurface,
                 TC.Transferred(another->Surface()));
  Standard_Integer aFlag = another->OuterBoundaryType();
  DeclareAndCast(IGESGeom_CurveOnSurface, anOuter,
                 TC.Transferred(another->OuterContour()));
  Standard_Integer count = another->NbInnerContours();

  if (count > 0) {
    anInner = new IGESGeom_HArray1OfCurveOnSurface(1, count);
    Standard_Integer I;
    for (I = 1; I <= count; I++) {
      DeclareAndCast(IGESGeom_CurveOnSurface, temp,
		     TC.Transferred(another->InnerContour(I)));
      anInner->SetValue(I, temp);
    }
  }

  ent->Init(aSurface, aFlag, anOuter, anInner);
}


//=======================================================================
//function : DirChecker
//purpose  : 
//=======================================================================

IGESData_DirChecker IGESGeom_ToolTrimmedSurface::DirChecker
  (const Handle(IGESGeom_TrimmedSurface)& /* ent */ )   const
{
  IGESData_DirChecker DC(144, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
//  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);
  DC.UseFlagRequired (0);
  DC.HierarchyStatusIgnored();

  return DC;
}


//=======================================================================
//function : OwnCheck
//purpose  : 
//=======================================================================

void IGESGeom_ToolTrimmedSurface::OwnCheck(const Handle(IGESGeom_TrimmedSurface)& ent,
                                           const Interface_ShareTool&,
                                           Handle(Interface_Check)& ach)  const
{
  // MGE 31/07/98
  // Building of messages
  //========================================
  //Message_Msg Msg172("XSTEP_172");
  //========================================

  if (ent->OuterBoundaryType() != 0 &&   ent->OuterBoundaryType() != 1) {
    Message_Msg Msg172("XSTEP_172");
    ach->SendFail(Msg172);
  }
}


//=======================================================================
//function : OwnDump
//purpose  : 
//=======================================================================

void IGESGeom_ToolTrimmedSurface::OwnDump(const Handle(IGESGeom_TrimmedSurface)& ent,
                                          const IGESData_IGESDumper& dumper,
                                          const Handle(Message_Messenger)& S,
                                          const Standard_Integer level)  const
{
  Standard_Integer tempSubLevel = (level <= 4) ? 0 : 1;

  S << "IGESGeom_TrimmedSurface" << endl;

  S << "Surface to be trimmed : ";
  dumper.Dump(ent->Surface(),S, tempSubLevel);
  S << endl;
  S << "Boundary type    : " << ent->OuterBoundaryType() << endl;
  S << "Outer Boundary   : ";
  dumper.Dump(ent->OuterContour(),S, tempSubLevel);
  S << endl;
  S << "Inner Boundaries : ";
  IGESData_DumpEntities(S,dumper ,level,1, ent->NbInnerContours(),ent->InnerContour);
  S << endl;
}
