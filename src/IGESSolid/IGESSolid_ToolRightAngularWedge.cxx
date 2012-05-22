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

#include <IGESSolid_ToolRightAngularWedge.ixx>
#include <IGESData_ParamCursor.hxx>
#include <gp_XYZ.hxx>
#include <gp_Pnt.hxx>
#include <gp_Dir.hxx>
#include <IGESData_Dump.hxx>


IGESSolid_ToolRightAngularWedge::IGESSolid_ToolRightAngularWedge ()    {  }


void  IGESSolid_ToolRightAngularWedge::ReadOwnParams
  (const Handle(IGESSolid_RightAngularWedge)& ent,
   const Handle(IGESData_IGESReaderData)& /* IR */, IGESData_ParamReader& PR) const
{
  gp_XYZ tempSize, tempCorner, tempXAxis, tempZAxis;
  Standard_Real lowX;
  Standard_Real tempreal;
  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed

  PR.ReadXYZ(PR.CurrentList(1, 3), "Size of RightAngularWedge", tempSize); //szv#4:S4163:12Mar99 `st=` not needed

  PR.ReadReal(PR.Current(), "Small X length", lowX); //szv#4:S4163:12Mar99 `st=` not needed

  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(), "Corner Point (X)", tempreal); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadReal(PR.Current(), "Corner Point (X)", tempreal))
	tempCorner.SetX(tempreal);
    }
  else  tempCorner.SetX(0.0);

  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(), "Corner Point (Y)", tempreal); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadReal(PR.Current(), "Corner Point (Y)", tempreal))
	tempCorner.SetY(tempreal);
    }
  else  tempCorner.SetY(0.0);

  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(), "Corner Point (Z)", tempreal); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadReal(PR.Current(), "Corner Point (Z)", tempreal))
	tempCorner.SetZ(tempreal);
    }
  else  tempCorner.SetZ(0.0);

  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(), "Local X axis (I)", tempreal); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadReal(PR.Current(), "Local X axis (I)", tempreal))
	tempXAxis.SetX(tempreal);
    }
  else  tempXAxis.SetX(1.0);

  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(), "Local X axis (J)", tempreal); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadReal(PR.Current(), "Local X axis (J)", tempreal))
	tempXAxis.SetY(tempreal);
    }
  else  tempXAxis.SetY(0.0);

  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(), "Local X axis (K)", tempreal); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadReal(PR.Current(), "Local X axis (K)", tempreal))
	tempXAxis.SetZ(tempreal);
    }
  else  tempXAxis.SetZ(0.0);

  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(), "Local Z axis (I)", tempreal); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadReal(PR.Current(), "Local Z axis (I)", tempreal))
	tempZAxis.SetX(tempreal);
    }
  else  tempZAxis.SetX(0.0);

  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(), "Local Z axis (J)", tempreal); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadReal(PR.Current(), "Local Z axis (J)", tempreal))
	tempZAxis.SetY(tempreal);
    }
  else  tempZAxis.SetY(0.0);

  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(), "Local Z axis (K)", tempreal); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadReal(PR.Current(), "Local Z axis (K)", tempreal))
	tempZAxis.SetZ(tempreal);
    }
  else  tempZAxis.SetZ(1.0);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init (tempSize, lowX, tempCorner, tempXAxis, tempZAxis);
  Standard_Real eps = 1.E-05;
  if (!tempXAxis.IsEqual(ent->XAxis().XYZ(),eps)) PR.AddWarning
    ("XAxis poorly unitary, normalized");
  if (!tempZAxis.IsEqual(ent->ZAxis().XYZ(),eps)) PR.AddWarning
    ("ZAxis poorly unitary, normalized");
}

void  IGESSolid_ToolRightAngularWedge::WriteOwnParams
  (const Handle(IGESSolid_RightAngularWedge)& ent, IGESData_IGESWriter& IW) const
{
  IW.Send(ent->Size().X());
  IW.Send(ent->Size().Y());
  IW.Send(ent->Size().Z());
  IW.Send(ent->XSmallLength());
  IW.Send(ent->Corner().X());
  IW.Send(ent->Corner().Y());
  IW.Send(ent->Corner().Z());
  IW.Send(ent->XAxis().X());
  IW.Send(ent->XAxis().Y());
  IW.Send(ent->XAxis().Z());
  IW.Send(ent->ZAxis().X());
  IW.Send(ent->ZAxis().Y());
  IW.Send(ent->ZAxis().Z());
}

void  IGESSolid_ToolRightAngularWedge::OwnShared
  (const Handle(IGESSolid_RightAngularWedge)& /* ent */, Interface_EntityIterator& /* iter */) const
{
}

void  IGESSolid_ToolRightAngularWedge::OwnCopy
  (const Handle(IGESSolid_RightAngularWedge)& another,
   const Handle(IGESSolid_RightAngularWedge)& ent, Interface_CopyTool& /* TC */) const
{
  ent->Init(another->Size(), another->XSmallLength(), another->Corner().XYZ(),
	    another->XAxis().XYZ(), another->ZAxis().XYZ());
}

IGESData_DirChecker  IGESSolid_ToolRightAngularWedge::DirChecker
  (const Handle(IGESSolid_RightAngularWedge)& /* ent */ ) const
{
  IGESData_DirChecker DC(152, 0);
  DC.Structure  (IGESData_DefVoid);
  DC.LineFont   (IGESData_DefAny);
  DC.Color      (IGESData_DefAny);

  DC.UseFlagRequired (0);
  DC.HierarchyStatusIgnored ();
  return DC;
}

void  IGESSolid_ToolRightAngularWedge::OwnCheck
  (const Handle(IGESSolid_RightAngularWedge)& ent,
   const Interface_ShareTool& , Handle(Interface_Check)& ach) const
{
  Standard_Real eps = 1.E-04;
  Standard_Real prosca = ent->XAxis() * ent->ZAxis();
  if (prosca < -eps || prosca > eps)
    ach->AddFail("Local Z axis : Not orthogonal to X axis");
  if (ent->Size().X() <= 0. || ent->Size().Y() <= 0. || ent->Size().Z() <= 0.)
    ach->AddFail("Size : Values are not positive");
  if (ent->XSmallLength() <= 0.0)
    ach->AddFail("Small X Length : Not Positive");
  if (ent->XSmallLength() >= ent->Size().X())
    ach->AddFail("Small X Length : Value not < LX");
}

void  IGESSolid_ToolRightAngularWedge::OwnDump
  (const Handle(IGESSolid_RightAngularWedge)& ent, const IGESData_IGESDumper& /* dumper */,
   const Handle(Message_Messenger)& S, const Standard_Integer level) const
{
  S << "IGESSolid_RightAngularWedge" << endl;

  S << "Size   : ";
  IGESData_DumpXYZ(S, ent->Size());  S << "  ";
  S << "XSmall : " << ent->XSmallLength() << endl;
  S << "Corner : ";
  IGESData_DumpXYZL(S,level, ent->Corner(), ent->Location());
  S << endl << "XAxis : ";
  IGESData_DumpXYZL(S,level, ent->XAxis(), ent->VectorLocation());
  S << endl << "ZAxis : ";
  IGESData_DumpXYZL(S,level, ent->ZAxis(), ent->VectorLocation());
  S << endl;
}
