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

#include <IGESSolid_ToolSolidOfLinearExtrusion.ixx>
#include <IGESData_ParamCursor.hxx>
#include <IGESData_IGESEntity.hxx>
#include <gp_XYZ.hxx>
#include <IGESData_Dump.hxx>
#include <Interface_Macros.hxx>


IGESSolid_ToolSolidOfLinearExtrusion::IGESSolid_ToolSolidOfLinearExtrusion ()
      {  }


void  IGESSolid_ToolSolidOfLinearExtrusion::ReadOwnParams
  (const Handle(IGESSolid_SolidOfLinearExtrusion)& ent,
   const Handle(IGESData_IGESReaderData)& IR, IGESData_ParamReader& PR) const
{
  Handle(IGESData_IGESEntity) tempEntity;
  gp_XYZ tempDirection;
  Standard_Real tempLength;
  Standard_Real tempreal;
  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed

  PR.ReadEntity(IR, PR.Current(), "Curve Entity", tempEntity); //szv#4:S4163:12Mar99 `st=` not needed

  PR.ReadReal(PR.Current(), "Length of extrusion", tempLength); //szv#4:S4163:12Mar99 `st=` not needed

  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(), "Extrusion direction (I)", tempreal); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadReal(PR.Current(), "Extrusion direction (I)", tempreal))
	tempDirection.SetX(tempreal);
    }
  else  tempDirection.SetX(0.0);

  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(), "Extrusion direction (J)", tempreal); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadReal(PR.Current(), "Extrusion direction (J)", tempreal))
	tempDirection.SetY(tempreal);
    }
  else  tempDirection.SetY(0.0);

  if (PR.DefinedElseSkip())
    {
      //st = PR.ReadReal(PR.Current(), "Extrusion direction (K)", tempreal); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadReal(PR.Current(), "Extrusion direction (K)", tempreal))
	tempDirection.SetZ(tempreal);
    }
  else  tempDirection.SetZ(1.0);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init(tempEntity, tempLength, tempDirection);
  Standard_Real eps = 1.E-05;
  if (!tempDirection.IsEqual(ent->ExtrusionDirection().XYZ(),eps))
    PR.AddWarning("Extrusion Direction poorly unitary, normalized");
}

void  IGESSolid_ToolSolidOfLinearExtrusion::WriteOwnParams
  (const Handle(IGESSolid_SolidOfLinearExtrusion)& ent, IGESData_IGESWriter& IW) const
{
  IW.Send(ent->Curve());
  IW.Send(ent->ExtrusionLength());
  IW.Send(ent->ExtrusionDirection().X());
  IW.Send(ent->ExtrusionDirection().Y());
  IW.Send(ent->ExtrusionDirection().Z());
}

void  IGESSolid_ToolSolidOfLinearExtrusion::OwnShared
  (const Handle(IGESSolid_SolidOfLinearExtrusion)& ent, Interface_EntityIterator& iter) const
{
  iter.GetOneItem(ent->Curve());
}

void  IGESSolid_ToolSolidOfLinearExtrusion::OwnCopy
  (const Handle(IGESSolid_SolidOfLinearExtrusion)& another,
   const Handle(IGESSolid_SolidOfLinearExtrusion)& ent, Interface_CopyTool& TC) const
{
  DeclareAndCast(IGESData_IGESEntity, tempEntity,
		 TC.Transferred(another->Curve()));
  Standard_Real tempLength = another->ExtrusionLength();
  gp_XYZ tempDirection = another->ExtrusionDirection().XYZ();
  ent->Init(tempEntity, tempLength, tempDirection);
}

IGESData_DirChecker  IGESSolid_ToolSolidOfLinearExtrusion::DirChecker
  (const Handle(IGESSolid_SolidOfLinearExtrusion)& /* ent */ ) const
{
  IGESData_DirChecker DC(164, 0);

  DC.Structure  (IGESData_DefVoid);
  DC.LineFont   (IGESData_DefAny);
  DC.Color      (IGESData_DefAny);

  DC.UseFlagRequired (0);
  DC.HierarchyStatusIgnored ();
  return DC;
}

void  IGESSolid_ToolSolidOfLinearExtrusion::OwnCheck
  (const Handle(IGESSolid_SolidOfLinearExtrusion)& ent,
   const Interface_ShareTool& , Handle(Interface_Check)& ach) const
{
  if (ent->ExtrusionLength() <= 0.0)
    ach->AddFail("Length of extrusion : Not Positive");
}

void  IGESSolid_ToolSolidOfLinearExtrusion::OwnDump
  (const Handle(IGESSolid_SolidOfLinearExtrusion)& ent, const IGESData_IGESDumper& dumper,
   const Handle(Message_Messenger)& S, const Standard_Integer level) const
{
  S << "IGESSolid_SolidOfLinearExtrusion" << endl;

  S << "Curve entity        : ";
  dumper.Dump(ent->Curve(),S, (level <= 4) ? 0 : 1);
  S << endl;
  S << "Extrusion length    : " << ent->ExtrusionLength() << endl;
  S << "Extrusion direction : ";
  IGESData_DumpXYZL(S,level, ent->ExtrusionDirection(), ent->VectorLocation());
  S << endl;
}
