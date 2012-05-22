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

#include <IGESDimen_ToolLeaderArrow.ixx>
#include <IGESData_ParamCursor.hxx>
#include <TColgp_HArray1OfXY.hxx>
#include <gp_XY.hxx>
#include <gp_Pnt2d.hxx>
#include <IGESData_Dump.hxx>
#include <Interface_Macros.hxx>


IGESDimen_ToolLeaderArrow::IGESDimen_ToolLeaderArrow ()    {  }


void  IGESDimen_ToolLeaderArrow::ReadOwnParams
  (const Handle(IGESDimen_LeaderArrow)& ent,
   const Handle(IGESData_IGESReaderData)& /* IR */, IGESData_ParamReader& PR) const
{ 
  //Standard_Boolean st; //szv#4:S4163:12Mar99 moved down

  Standard_Real arrowHeadHeight; 
  Standard_Real arrowHeadWidth; 
  Standard_Real zDepth; 
  gp_XY arrowHead; 
  Handle(TColgp_HArray1OfXY) segmentTails;
  Standard_Integer nbval;

  Standard_Boolean st = PR.ReadInteger( PR.Current(), "Count of Segments", nbval);
  if (st && nbval > 0)
    segmentTails = new TColgp_HArray1OfXY(1,nbval);
  else  PR.AddFail("Count of Segments: Not Positive");

  //szv#4:S4163:12Mar99 `st=` not needed
  PR.ReadReal(PR.Current(), "Arrow Head Height", arrowHeadHeight);
  PR.ReadReal(PR.Current(), "Arrow Head Width", arrowHeadWidth);
  PR.ReadReal(PR.Current(), "Z Depth", zDepth);
  PR.ReadXY(PR.CurrentList(1, 2), "Arrow Head Position", arrowHead);

  if (! segmentTails.IsNull())
    {
      for (Standard_Integer i = 1; i <= nbval; i++)
	{
          gp_XY tempXY;
          //st = PR.ReadXY(PR.CurrentList(1, 2), "Segment Co-ords.", tempXY); //szv#4:S4163:12Mar99 moved in if
	  if (PR.ReadXY(PR.CurrentList(1, 2), "Segment Co-ords.", tempXY))
	    segmentTails->SetValue(i, tempXY);
	}
      DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
      ent->Init (arrowHeadHeight, arrowHeadWidth, zDepth, arrowHead, segmentTails);
    } //segmentTails.IsNull() crash in ent->Init( ...

}

void  IGESDimen_ToolLeaderArrow::WriteOwnParams
  (const Handle(IGESDimen_LeaderArrow)& ent, IGESData_IGESWriter& IW) const 
{ 
  Standard_Integer upper = ent->NbSegments();
  IW.Send(upper);
  IW.Send(ent->ArrowHeadHeight());
  IW.Send(ent->ArrowHeadWidth());
  IW.Send(ent->ZDepth());
  IW.Send(ent->ArrowHead().X());
  IW.Send(ent->ArrowHead().Y());
  for (Standard_Integer i = 1; i <= upper; i++)
    {
      IW.Send((ent->SegmentTail(i)).X());
      IW.Send((ent->SegmentTail(i)).Y());
    }
}

void  IGESDimen_ToolLeaderArrow::OwnShared
  (const Handle(IGESDimen_LeaderArrow)& /* ent */, Interface_EntityIterator& /* iter */) const
{
}

void  IGESDimen_ToolLeaderArrow::OwnCopy
  (const Handle(IGESDimen_LeaderArrow)& another,
   const Handle(IGESDimen_LeaderArrow)& ent, Interface_CopyTool& /* TC */) const
{ 
  Standard_Integer nbval = another->NbSegments();
  Standard_Real arrowHeadHeight = another->ArrowHeadHeight();
  Standard_Real arrowHeadWidth = another->ArrowHeadWidth();
  Standard_Real zDepth = another->ZDepth();
  gp_XY arrowHead = another->ArrowHead().XY();

  Handle(TColgp_HArray1OfXY) segmentTails = new TColgp_HArray1OfXY(1, nbval);

  for (Standard_Integer i = 1; i <= nbval; i++)
    {
      segmentTails->SetValue(i, (another->SegmentTail(i)).XY());
    }

  ent->Init(arrowHeadHeight, arrowHeadWidth, zDepth, arrowHead, segmentTails);
  ent->SetFormNumber (another->FormNumber());
}

IGESData_DirChecker  IGESDimen_ToolLeaderArrow::DirChecker
  (const Handle(IGESDimen_LeaderArrow)& /* ent */ ) const 
{ 
  IGESData_DirChecker DC (214, 1, 12);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);
  DC.UseFlagRequired(1);
  DC.HierarchyStatusIgnored();
  return DC;
}

void  IGESDimen_ToolLeaderArrow::OwnCheck
  (const Handle(IGESDimen_LeaderArrow)& /* ent */,
   const Interface_ShareTool& , Handle(Interface_Check)& /* ach */) const 
{
}

void  IGESDimen_ToolLeaderArrow::OwnDump
  (const Handle(IGESDimen_LeaderArrow)& ent, const IGESData_IGESDumper& /* dumper */,
   const Handle(Message_Messenger)& S, const Standard_Integer level) const 
{ 
  S << "IGESDimen_LeaderArrow" << endl;
  S << "Number of Segments : " << ent->NbSegments() << endl;
  S << "Arrowhead Height   : " << ent->ArrowHeadHeight() << endl;
  S << "Arrowhead Width    : " << ent->ArrowHeadWidth() << endl;
  S << "Z depth            : " << ent->ZDepth() << endl;
  S << "Arrowhead co-ords  : ";
  IGESData_DumpXYLZ(S,level,ent->ArrowHead(),ent->Location(),ent->ZDepth());
  S << endl << "Segment Tails : "; 
  IGESData_DumpListXYLZ(S ,level,1, ent->NbSegments(),ent->SegmentTail,
			ent->Location(), ent->ZDepth());
  S << endl;
}
