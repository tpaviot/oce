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

#include <IGESGeom_ToolFlash.ixx>
#include <IGESData_ParamCursor.hxx>
#include <gp_XY.hxx>
#include <gp_Pnt2d.hxx>
#include <IGESData_IGESEntity.hxx>
#include <IGESData_LineFontEntity.hxx>
#include <IGESData_Dump.hxx>
#include <Interface_Macros.hxx>


IGESGeom_ToolFlash::IGESGeom_ToolFlash ()    {  }


void IGESGeom_ToolFlash::ReadOwnParams
  (const Handle(IGESGeom_Flash)& ent,
   const Handle(IGESData_IGESReaderData)& IR, IGESData_ParamReader& PR) const
{
  gp_XY aPoint;
  Standard_Real aDim1, aDim2, aRotation;
  Handle(IGESData_IGESEntity) aReference;
  Standard_Integer fn = ent->FormNumber();    // for default cases

  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed
  aDim1 = aDim2 = aRotation = 0.;    // default values

  // Reading reference of flash
  PR.ReadXY(PR.CurrentList(1, 2), "Reference of Flash", aPoint); //szv#4:S4163:12Mar99 `st=` not needed

  // Reading first flash sizing parameter
  if (PR.DefinedElseSkip())
    PR.ReadReal(PR.Current(), "First Flash sizing parameter", aDim1); //szv#4:S4163:12Mar99 `st=` not needed
  else if (fn > 0) PR.AddFail("Fist Flash sizing parameter : undefined");

  // Reading second flash sizing parameter
  if (PR.DefinedElseSkip())
    PR.ReadReal(PR.Current(), "Second Flash sizing parameter", aDim2); //szv#4:S4163:12Mar99 `st=` not needed
  else {
    if (fn > 1) PR.AddFail("Second Flash sizing parameter : not defined");
  }

  // Reading rotation of flash about reference point
  if (PR.DefinedElseSkip())
    PR.ReadReal(PR.Current(), "Rotation about ref. point", aRotation); //szv#4:S4163:12Mar99 `st=` not needed
  else {
    if (fn == 2 || fn == 4) PR.AddFail("Rotation about ref. point : not defined");
  }

  if ( PR.IsParamEntity(PR.CurrentNumber()) )
    // Reading the referenced entity
    PR.ReadEntity(IR, PR.Current(), "Referenced entity", aReference); //szv#4:S4163:12Mar99 `st=` not needed
  // "else" not necessary as this is the last field

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init (aPoint, aDim1, aDim2, aRotation, aReference);
}

void IGESGeom_ToolFlash::WriteOwnParams
  (const Handle(IGESGeom_Flash)& ent, IGESData_IGESWriter& IW)  const
{
  IW.Send( ent->ReferencePoint().X() );
  IW.Send( ent->ReferencePoint().Y() );
  IW.Send( ent->Dimension1() );
  IW.Send( ent->Dimension2() );
  IW.Send( ent->Rotation() );
  IW.Send( ent->ReferenceEntity() );
}

void  IGESGeom_ToolFlash::OwnShared
  (const Handle(IGESGeom_Flash)& ent, Interface_EntityIterator& iter) const
{
  iter.GetOneItem( ent->ReferenceEntity() );
}

void IGESGeom_ToolFlash::OwnCopy
  (const Handle(IGESGeom_Flash)& another,
   const Handle(IGESGeom_Flash)& ent, Interface_CopyTool& TC) const
{
  gp_XY aPoint = (another->ReferencePoint()).XY();
  Standard_Real aDim1 = another->Dimension1();
  Standard_Real aDim2 = another->Dimension2();
  Standard_Real aRotation = another->Rotation();

  DeclareAndCast(IGESData_IGESEntity, aReference,
		 TC.Transferred(another->ReferenceEntity()));

  ent->Init(aPoint, aDim1, aDim2, aRotation, aReference);
}

Standard_Boolean  IGESGeom_ToolFlash::OwnCorrect
  (const Handle(IGESGeom_Flash)& ent) const
{
  Standard_Integer fn = ent->FormNumber();
  Standard_Boolean res0 = (ent->RankLineFont() != 1);
  if (res0) {
    Handle(IGESData_LineFontEntity) nulfont;
    ent->InitLineFont(nulfont,1);    // ranklinefont force a 1
  }
  Standard_Boolean res1 = Standard_False;
  Handle(IGESData_IGESEntity) ref = ent->ReferenceEntity();
  if (fn != 0 && !ref.IsNull()) {
    ref.Nullify();
    res1 = Standard_True;
  }
  Standard_Real d1 = ent->Dimension1();
  Standard_Real d2 = ent->Dimension2();
  Standard_Real rt = ent->Rotation();
  if (fn == 0 && d1 != 0.) {  d1 = 0.; res1 = Standard_True;  }
  if (fn <= 1 && d2 != 0.) {  d2 = 0.; res1 = Standard_True;  }
  if ((fn <= 1 || fn == 3) && rt != 0.) {  rt = 0.; res1 = Standard_True;  }
  if (res1) ent->Init (ent->ReferencePoint().XY(), d1, d2, rt, ref);
  return (res0 || res1);
}

IGESData_DirChecker IGESGeom_ToolFlash::DirChecker
  (const Handle(IGESGeom_Flash)& /* ent */ )  const
{
  IGESData_DirChecker DC(125, 0, 4);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefValue);
//  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);
  DC.HierarchyStatusRequired(0);
  return DC;
}

void IGESGeom_ToolFlash::OwnCheck
  (const Handle(IGESGeom_Flash)& ent,
   const Interface_ShareTool& , Handle(Interface_Check)& ach)  const
{
  Standard_Integer fn = ent->FormNumber();
  if (ent->RankLineFont() != 1)
    ach->AddFail("LineFontPattern : Value != 1");
  if (ent->ReferenceEntity().IsNull()) {
    if (fn == 0)
      ach->AddFail("Flash defined by a Reference Entity, which is absent");
  }
  else if (fn != 0) ach->AddWarning("Reference Entity present though useless");
  if (fn == 1 && ent->Dimension2() != 0.)
    ach->AddWarning("Dimension 2 present though useless");
  if ((fn == 1 || fn == 3) && ent->Rotation() != 0.)
    ach->AddWarning("Rotation present though useless");
}


void IGESGeom_ToolFlash::OwnDump
  (const Handle(IGESGeom_Flash)& ent, const IGESData_IGESDumper& dumper,
   const Handle(Message_Messenger)& S, const Standard_Integer level)  const
{
  Standard_Integer sublevel = (level <= 4) ? 0 : 1;
  Standard_Integer fn = ent->FormNumber();

  S << "IGESGeom_Flash" << endl;
  switch (fn) {
    case 0 : S << " --    Form defined by reference entity   --" << endl; break;
    case 1 : S << " --    Circular    --  ";  break;
    case 2 : S << " --    Rectangle   --  ";  break;
    case 3 : S << " --    Donut    --  ";  break;
    case 4 : S << " --    Canoe    --  ";  break;
    default : break;
  }

  S << "Flash reference point    : ";
  IGESData_DumpXYL(S,level, ent->ReferencePoint(), ent->Location());
  S << " First sizing parameter  : " << ent->Dimension1() << "  ";
  S << " Second sizing parameter : " << ent->Dimension2() << endl;
  S << " Rotation about reference entity : " << ent->Rotation() << endl;
  S << "Reference Entity         : ";
  dumper.Dump(ent->ReferenceEntity(),S, sublevel);
  S << endl;
}
