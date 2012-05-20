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

#include <IGESSolid_ToolCylinder.ixx>
#include <IGESData_ParamCursor.hxx>
#include <gp_XYZ.hxx>
#include <gp_Pnt.hxx>
#include <IGESData_Dump.hxx>


IGESSolid_ToolCylinder::IGESSolid_ToolCylinder ()    {  }


void  IGESSolid_ToolCylinder::ReadOwnParams
  (const Handle(IGESSolid_Cylinder)& ent,
   const Handle(IGESData_IGESReaderData)& /* IR */, IGESData_ParamReader& PR) const
{
  Standard_Real tempHeight, tempRadius, tempreal;
  gp_XYZ tempCenter, tempAxis;
  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed

  PR.ReadReal(PR.Current(), "Height", tempHeight); //szv#4:S4163:12Mar99 `st=` not needed

  PR.ReadReal(PR.Current(), "Radius", tempRadius); //szv#4:S4163:12Mar99 `st=` not needed

  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(), "Face center (X)", tempreal); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadReal(PR.Current(), "Face center (X)", tempreal))
	tempCenter.SetX(tempreal);
    }
  else  tempCenter.SetX(0.0);

  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(), "Face center (Y)", tempreal); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadReal(PR.Current(), "Face center (Y)", tempreal))
	tempCenter.SetY(tempreal);
    }
  else  tempCenter.SetY(0.0);

  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(), "Face center (Z)", tempreal); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadReal(PR.Current(), "Face center (Z)", tempreal))
	tempCenter.SetZ(tempreal);
    }
  else  tempCenter.SetZ(0.0);

  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(), "Axis direction (I)", tempreal); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadReal(PR.Current(), "Axis direction (I)", tempreal))
	tempAxis.SetX(tempreal);
    }
  else  tempAxis.SetX(0.0);

  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(), "Axis direction (J)", tempreal); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadReal(PR.Current(), "Axis direction (J)", tempreal))
	tempAxis.SetY(tempreal);
    }
  else  tempAxis.SetY(0.0);

  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(), "Axis direction (K)", tempreal); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadReal(PR.Current(), "Axis direction (K)", tempreal))
	tempAxis.SetZ(tempreal);
    }
  else  tempAxis.SetZ(1.0);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init
    (tempHeight, tempRadius, tempCenter, tempAxis);
  Standard_Real eps = 1.E-05;
  if (!tempAxis.IsEqual(ent->Axis().XYZ(),eps)) PR.AddWarning
    ("Axis poorly unitary, normalized");
}

void  IGESSolid_ToolCylinder::WriteOwnParams
  (const Handle(IGESSolid_Cylinder)& ent, IGESData_IGESWriter& IW) const
{
  IW.Send(ent->Height());
  IW.Send(ent->Radius());
  IW.Send(ent->FaceCenter().X());
  IW.Send(ent->FaceCenter().Y());
  IW.Send(ent->FaceCenter().Z());
  IW.Send(ent->Axis().X());
  IW.Send(ent->Axis().Y());
  IW.Send(ent->Axis().Z());
}

void  IGESSolid_ToolCylinder::OwnShared
  (const Handle(IGESSolid_Cylinder)& /* ent */, Interface_EntityIterator& /* iter */) const
{
}

void  IGESSolid_ToolCylinder::OwnCopy
  (const Handle(IGESSolid_Cylinder)& another,
   const Handle(IGESSolid_Cylinder)& ent, Interface_CopyTool& /* TC */) const
{
  ent->Init
    (another->Height(), another->Radius(), another->FaceCenter().XYZ(),
     another->Axis().XYZ());
}

IGESData_DirChecker  IGESSolid_ToolCylinder::DirChecker
  (const Handle(IGESSolid_Cylinder)& /* ent */ ) const
{
  IGESData_DirChecker DC(154, 0);

  DC.Structure  (IGESData_DefVoid);
  DC.LineFont   (IGESData_DefAny);
  DC.Color      (IGESData_DefAny);

  DC.UseFlagRequired (0);
  DC.HierarchyStatusIgnored ();
  return DC;
}

void  IGESSolid_ToolCylinder::OwnCheck
  (const Handle(IGESSolid_Cylinder)& ent,
   const Interface_ShareTool& , Handle(Interface_Check)& ach) const
{
  if (ent->Height() <= 0.0)
    ach->AddFail("Height : Value < 0");
  if (ent->Radius() <= 0.0)
    ach->AddFail("Radius : Value < 0");
}

void  IGESSolid_ToolCylinder::OwnDump
  (const Handle(IGESSolid_Cylinder)& ent, const IGESData_IGESDumper& /* dumper */,
   const Handle(Message_Messenger)& S, const Standard_Integer level) const
{

//  Standard_Boolean locprint = (ent->HasTransf() && level >=6);
//  gp_Pnt TCenter = ent->TransformedFaceCenter();
//  gp_Dir TAxis   = ent->TransformedAxis();

  S << "IGESSolid_Cylinder" << endl;

  S << "Height : " << ent->Height() << "  ";
  S << "Radius : " << ent->Radius() << endl;
  S << "Center : ";
  IGESData_DumpXYZL(S,level, ent->FaceCenter(), ent->Location());
  S << endl << "Axis : ";
  IGESData_DumpXYZL(S,level, ent->Axis(), ent->VectorLocation());
  S << endl;
}
