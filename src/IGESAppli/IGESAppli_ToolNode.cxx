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

#include <IGESAppli_ToolNode.ixx>
#include <IGESData_ParamCursor.hxx>
#include <IGESGeom_TransformationMatrix.hxx>
#include <gp_XYZ.hxx>
#include <gp_Pnt.hxx>
#include <Interface_Macros.hxx>
#include <Message_Messenger.hxx>

IGESAppli_ToolNode::IGESAppli_ToolNode ()    {  }


void  IGESAppli_ToolNode::ReadOwnParams
  (const Handle(IGESAppli_Node)& ent,
   const Handle(IGESData_IGESReaderData)& IR, IGESData_ParamReader& PR) const
{
  gp_XYZ tempCoordinates;
  Handle(IGESGeom_TransformationMatrix) tempSystem;
  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed

  //szv#4:S4163:12Mar99 `st=` not needed
  PR.ReadXYZ(PR.CurrentList(1, 3),"Coordinates of Node (XYZ)",tempCoordinates);

  if (PR.DefinedElseSkip())
    PR.ReadEntity(IR,PR.Current(),"Transformation Matrix",
		  STANDARD_TYPE(IGESGeom_TransformationMatrix), tempSystem,Standard_True);

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init(tempCoordinates,tempSystem);
}

void  IGESAppli_ToolNode::WriteOwnParams
  (const Handle(IGESAppli_Node)& ent, IGESData_IGESWriter& IW) const
{
  IW.Send(ent->Coord().X());
  IW.Send(ent->Coord().Y());
  IW.Send(ent->Coord().Z());
  IW.Send(ent->System());
}

void  IGESAppli_ToolNode::OwnShared
  (const Handle(IGESAppli_Node)& ent, Interface_EntityIterator& iter) const
{
  iter.GetOneItem(ent->System());
}

void  IGESAppli_ToolNode::OwnCopy
  (const Handle(IGESAppli_Node)& another,
   const Handle(IGESAppli_Node)& ent, Interface_CopyTool& TC) const
{
  gp_XYZ aCoord = (another->Coord()).XYZ();
  DeclareAndCast(IGESGeom_TransformationMatrix,aSystem,
		 TC.Transferred(another->System()));

  ent->Init(aCoord,aSystem);
}

IGESData_DirChecker  IGESAppli_ToolNode::DirChecker
  (const Handle(IGESAppli_Node)& /*ent*/ ) const
{
  IGESData_DirChecker DC(134,0);  //Form no = 0 & Type = 134
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefAny);
  DC.UseFlagRequired(04);
  return DC;
}

void  IGESAppli_ToolNode::OwnCheck
  (const Handle(IGESAppli_Node)& ent,
   const Interface_ShareTool& , Handle(Interface_Check)& ach) const
{
  if (!ent->HasSubScriptNumber())
    ach->AddFail("SubScript Number expected (for Node Number) not present");
  if (!ent->HasTransf())
    ach->AddFail("Transformation Matrix expected, not present");
  if (!ent->System().IsNull())
    if (ent->System()->FormNumber() < 10)
      ach->AddFail("System : Incorrect FormNumber (not 10-11-12)");
}

void  IGESAppli_ToolNode::OwnDump
  (const Handle(IGESAppli_Node)& ent, const IGESData_IGESDumper& dumper,
   const Handle(Message_Messenger)& S, const Standard_Integer level) const
{
  S << "IGESAppli_Node" << endl;
  S << " Nodal Coords : 1st " << ent->Coord().X()
    << "  2nd : " << ent->Coord().Y() << "  3rd : " << ent->Coord().Z() <<endl;
  S << "Nodal Displacement Coordinate System : ";
  if (!ent->System().IsNull())
    dumper.Dump(ent->System(),S, level);
  else
    S << "Global Cartesian Coordinate System (default)";
  S << endl;
}
