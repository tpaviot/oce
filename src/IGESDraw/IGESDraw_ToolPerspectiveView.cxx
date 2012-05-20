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

#include <IGESDraw_ToolPerspectiveView.ixx>
#include <IGESData_ParamCursor.hxx>
#include <IGESData_TransfEntity.hxx>
#include <gp_XY.hxx>
#include <gp_XYZ.hxx>
#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <IGESData_Dump.hxx>
#include <Interface_Macros.hxx>


IGESDraw_ToolPerspectiveView::IGESDraw_ToolPerspectiveView ()    {  }


void IGESDraw_ToolPerspectiveView::ReadOwnParams
  (const Handle(IGESDraw_PerspectiveView)& ent,
   const Handle(IGESData_IGESReaderData)& /*IR*/, IGESData_ParamReader& PR) const
{
  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed

  gp_XY tempTopLeft, tempBottomRight;
  Standard_Real tempLeft, tempRight, tempTop, tempBottom;
  gp_XYZ tempCenterOfProjection, tempViewUpVector;
  gp_XYZ tempViewNormalVector, tempViewReferencePoint;
  Standard_Integer tempViewNumber, tempDepthClip;
  Standard_Real tempScaleFactor, tempViewPlaneDistance;
  Standard_Real tempBackPlaneDistance, tempFrontPlaneDistance;

  //szv#4:S4163:12Mar99 `st=` not needed
  PR.ReadInteger(PR.Current(), "View Number", tempViewNumber);
  PR.ReadReal(PR.Current(), "Scale Number", tempScaleFactor);
  PR.ReadXYZ(PR.CurrentList(1, 3), "View Plane Normal Vector", tempViewNormalVector);
  PR.ReadXYZ(PR.CurrentList(1, 3), "View Reference Point", tempViewReferencePoint);
  PR.ReadXYZ(PR.CurrentList(1, 3), "Center Of Projection", tempCenterOfProjection);
  PR.ReadXYZ(PR.CurrentList(1, 3), "View Up Vector", tempViewUpVector);
  PR.ReadReal(PR.Current(), "View Plane Distance", tempViewPlaneDistance);

  //st = PR.ReadReal(PR.Current(), "Left Side Of Clipping Window", tempLeft); //szv#4:S4163:12Mar99 moved in if
  if (PR.ReadReal(PR.Current(), "Left Side Of Clipping Window", tempLeft))
    tempTopLeft.SetX(tempLeft);

  //st = PR.ReadReal(PR.Current(), "Right Side Of Clipping Window", tempRight); //szv#4:S4163:12Mar99 moved in if
  if (PR.ReadReal(PR.Current(), "Right Side Of Clipping Window", tempRight))
    tempBottomRight.SetX(tempRight);

  //st = PR.ReadReal(PR.Current(), "Bottom Of Clipping Window", tempBottom); //szv#4:S4163:12Mar99 moved in if
  if (PR.ReadReal(PR.Current(), "Bottom Of Clipping Window", tempBottom))
    tempBottomRight.SetY(tempBottom);

  //st = PR.ReadReal(PR.Current(), "Top Of Clipping Window", tempTop); //szv#4:S4163:12Mar99 moved in if
  if (PR.ReadReal(PR.Current(), "Top Of Clipping Window", tempTop))
    tempTopLeft.SetY(tempTop);

  //szv#4:S4163:12Mar99 `st=` not needed
  PR.ReadInteger(PR.Current(), "Depth Clipping Indicator", tempDepthClip);
  PR.ReadReal(PR.Current(), "Back Plane Distance", tempBackPlaneDistance);
  PR.ReadReal(PR.Current(), "Front Plane Distance", tempFrontPlaneDistance);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init
    (tempViewNumber, tempScaleFactor, tempViewNormalVector,
     tempViewReferencePoint, tempCenterOfProjection, tempViewUpVector,
     tempViewPlaneDistance, tempTopLeft, tempBottomRight, tempDepthClip,
     tempBackPlaneDistance, tempFrontPlaneDistance);
}

void IGESDraw_ToolPerspectiveView::WriteOwnParams
  (const Handle(IGESDraw_PerspectiveView)& ent, IGESData_IGESWriter& IW)  const
{
  IW.Send(ent->ViewNumber());
  IW.Send(ent->ScaleFactor());
  IW.Send(ent->ViewNormalVector().X());
  IW.Send(ent->ViewNormalVector().Y());
  IW.Send(ent->ViewNormalVector().Z());
  IW.Send(ent->ViewReferencePoint().X());
  IW.Send(ent->ViewReferencePoint().Y());
  IW.Send(ent->ViewReferencePoint().Z());
  IW.Send(ent->CenterOfProjection().X());
  IW.Send(ent->CenterOfProjection().Y());
  IW.Send(ent->CenterOfProjection().Z());
  IW.Send(ent->ViewUpVector().X());
  IW.Send(ent->ViewUpVector().Y());
  IW.Send(ent->ViewUpVector().Z());
  IW.Send(ent->ViewPlaneDistance());
  IW.Send(ent->TopLeft().X());
  IW.Send(ent->BottomRight().X());
  IW.Send(ent->BottomRight().Y());
  IW.Send(ent->TopLeft().Y());
  IW.Send(ent->DepthClip());
  IW.Send(ent->BackPlaneDistance());
  IW.Send(ent->FrontPlaneDistance());
}

void  IGESDraw_ToolPerspectiveView::OwnShared
  (const Handle(IGESDraw_PerspectiveView)& /*ent*/, Interface_EntityIterator& /*iter*/) const
{
}

void IGESDraw_ToolPerspectiveView::OwnCopy
  (const Handle(IGESDraw_PerspectiveView)& another,
   const Handle(IGESDraw_PerspectiveView)& ent, Interface_CopyTool& /*TC*/) const
{
  ent->Init
    (another->ViewNumber(), another->ScaleFactor(),
     another->ViewNormalVector().XYZ(),   another->ViewReferencePoint().XYZ(),
     another->CenterOfProjection().XYZ(), another->ViewUpVector().XYZ(),
     another->ViewPlaneDistance(),
     another->TopLeft().XY(),another->BottomRight().XY(), another->DepthClip(),
     another->BackPlaneDistance(), another->FrontPlaneDistance());
}


IGESData_DirChecker IGESDraw_ToolPerspectiveView::DirChecker
  (const Handle(IGESDraw_PerspectiveView)& /*ent*/)  const
{
  IGESData_DirChecker DC(410, 1);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.UseFlagRequired(1);
  DC.HierarchyStatusIgnored();

  return DC;
}

void IGESDraw_ToolPerspectiveView::OwnCheck
  (const Handle(IGESDraw_PerspectiveView)& ent,
   const Interface_ShareTool& , Handle(Interface_Check)& ach)  const
{
  if ((ent->DepthClip() < 0) || (ent->DepthClip() > 3))
    ach->AddFail("DepthClip has invalid value");
  if (ent->HasTransf()) {
    if (ent->Transf()->FormNumber() != 0)
      ach->AddFail("Associated Matrix has not Form Number 0");
  }
}

void IGESDraw_ToolPerspectiveView::OwnDump
  (const Handle(IGESDraw_PerspectiveView)& ent, const IGESData_IGESDumper& /*dumper*/,
   const Handle(Message_Messenger)& S, const Standard_Integer level)  const
{
  S << "IGESDraw_PerspectiveView" << endl;

  S << "View Number  : " << ent->ViewNumber()  << "  ";
  S << "Scale Factor : " << ent->ScaleFactor() << endl;
  S         << "View Plane Normal Vector : ";
  IGESData_DumpXYZL(S,level, ent->ViewNormalVector(), ent->Location());
  S << endl << "View Reference Point     : ";
  IGESData_DumpXYZL(S,level, ent->ViewReferencePoint() , ent->Location());
  S << endl << "Center Of Projection     : ";
  IGESData_DumpXYZL(S,level, ent->CenterOfProjection() , ent->Location());
  S << endl << "View Up Vector           : ";
  IGESData_DumpXYZL(S,level, ent->ViewUpVector() , ent->Location());
  S << endl << "View Plane Distance      : " << ent->ViewPlaneDistance()<<endl;
  S << "Left   Side Of Clipping Window : " << ent->TopLeft().X()     << endl;
  S << "Right  Side Of Clipping Window : " << ent->BottomRight().X() << endl;
  S << "Bottom Side Of Clipping Window : " << ent->BottomRight().Y() << endl;
  S << "Top    Side Of Clipping Window : " << ent->TopLeft().Y()     << endl;
  S << "Depth Clipping : " << ent->DepthClip();
  switch (ent->DepthClip()) {
    case 0 :  S << " (No Depth Clipping)" << endl;                    break;
    case 1 :  S << " (Back Clipping Plane ON)" << endl;               break;
    case 2 :  S << " (Front Clipping Plane ON)" << endl;              break;
    case 3 :  S << " (Front and Back Clipping Planes ON)" << endl;    break;
    default : S << " (Invalid Value)" << endl;                        break;
  }
  S << "Back Plane Distance  : " << ent->BackPlaneDistance()  << "  ";
  S << "Front Plane Distance : " << ent->FrontPlaneDistance() << endl;
  S << endl;
}
