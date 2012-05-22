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

#include <IGESDraw_ToolCircArraySubfigure.ixx>
#include <IGESData_ParamCursor.hxx>
#include <gp_XYZ.hxx>
#include <IGESData_IGESEntity.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <IGESData_Dump.hxx>
#include <Interface_Macros.hxx>


IGESDraw_ToolCircArraySubfigure::IGESDraw_ToolCircArraySubfigure ()    {  }


void IGESDraw_ToolCircArraySubfigure::ReadOwnParams
  (const Handle(IGESDraw_CircArraySubfigure)& ent,
   const Handle(IGESData_IGESReaderData)& IR, IGESData_ParamReader& PR) const
{
  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed

  gp_XYZ tempCenter;
  Handle(IGESData_IGESEntity) tempBase;
  Standard_Real tempRadius, tempStAngle, tempDelAngle;
  Standard_Integer tempNumLocs, tempFlag, tempListCount;
  Handle(TColStd_HArray1OfInteger) tempNumPos;

  //szv#4:S4163:12Mar99 `st=` not needed
  PR.ReadEntity(IR, PR.Current(), "Base Entity", tempBase);
  PR.ReadInteger(PR.Current(), "Number Of Instance Locations", tempNumLocs);
  PR.ReadXYZ(PR.CurrentList(1, 3), "Imaginary Circle Center Coordinate", tempCenter);
  PR.ReadReal(PR.Current(), "Radius Of Imaginary Circle", tempRadius);
  PR.ReadReal(PR.Current(), "Start Angle in Radians", tempStAngle);
  PR.ReadReal(PR.Current(), "Delta Angle in Radians", tempDelAngle);

  //st = PR.ReadInteger(PR.Current(), "DO-DONT List Count", tempListCount); //szv#4:S4163:12Mar99 moved in if
  if (PR.ReadInteger(PR.Current(), "DO-DONT List Count", tempListCount)) {
    // Initialise HArray1 only if there is no error reading its Length
    if (tempListCount > 0)
      tempNumPos = new TColStd_HArray1OfInteger(1, tempListCount);
    else if (tempListCount < 0)
      PR.AddFail("DO-DONT List Count : Less than Zero");
  }

  PR.ReadInteger(PR.Current(), "DO-DONT Flag", tempFlag); //szv#4:S4163:12Mar99 `st=` not needed

  // Read the HArray1 only if its Length was read without any Error
  if (! tempNumPos.IsNull()) {
    Standard_Integer I;
    for (I = 1; I <= tempListCount; I++) {
      Standard_Integer tempPosition;
      //st = PR.ReadInteger(PR.Current(), "Number Of Position To Process",
			    //tempPosition); //szv#4:S4163:12Mar99 moved in if
      if (PR.ReadInteger(PR.Current(), "Number Of Position To Process", tempPosition))
	tempNumPos->SetValue(I, tempPosition);
    }
  }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init
    (tempBase, tempNumLocs, tempCenter, tempRadius,
     tempStAngle,tempDelAngle, tempFlag, tempNumPos);
}

void IGESDraw_ToolCircArraySubfigure::WriteOwnParams
  (const Handle(IGESDraw_CircArraySubfigure)& ent, IGESData_IGESWriter& IW)  const
{
  IW.Send(ent->BaseEntity());
  IW.Send(ent->NbLocations());
  IW.Send(ent->CenterPoint().X());
  IW.Send(ent->CenterPoint().Y());
  IW.Send(ent->CenterPoint().Z());
  IW.Send(ent->CircleRadius());
  IW.Send(ent->StartAngle());
  IW.Send(ent->DeltaAngle());
  IW.Send(ent->ListCount());
  IW.SendBoolean(ent->DoDontFlag());
  // Send the HArray1 only if it is not empty (i.e. Null)
  Standard_Integer I;
  Standard_Integer up  = ent->ListCount();
  for (I = 1; I <= up; I++)
    IW.Send(ent->ListPosition(I));
}

void  IGESDraw_ToolCircArraySubfigure::OwnShared
  (const Handle(IGESDraw_CircArraySubfigure)& /*ent*/, Interface_EntityIterator& /*iter*/) const
{
}

void IGESDraw_ToolCircArraySubfigure::OwnCopy
  (const Handle(IGESDraw_CircArraySubfigure)& another,
   const Handle(IGESDraw_CircArraySubfigure)& ent, Interface_CopyTool& TC) const
{
  DeclareAndCast(IGESData_IGESEntity, tempBase,
                 TC.Transferred(another->BaseEntity()));
  Standard_Integer tempNumLocs = another->NbLocations();
  gp_XYZ tempCenter = (another->CenterPoint()).XYZ();
  Standard_Real tempRadius = another->CircleRadius();
  Standard_Real tempStAngle = another->StartAngle();
  Standard_Real tempDelAngle = another->DeltaAngle();
  Standard_Integer tempListCount = another->ListCount();
  Standard_Integer tempFlag = another->DoDontFlag();
  Handle(TColStd_HArray1OfInteger) tempNumPos;
  if (! another->DisplayFlag()) {
    tempNumPos = new TColStd_HArray1OfInteger(1, tempListCount);
    Standard_Integer I;
    for (I = 1; I <= tempListCount; I++) {
      Standard_Integer tempPosition = another->ListPosition(I);
      tempNumPos->SetValue(I, tempPosition);
    }
  }

  ent->Init(tempBase, tempNumLocs, tempCenter, tempRadius,
	    tempStAngle, tempDelAngle, tempFlag, tempNumPos);
}

IGESData_DirChecker IGESDraw_ToolCircArraySubfigure::DirChecker
  (const Handle(IGESDraw_CircArraySubfigure)& /*ent*/)  const
{
  IGESData_DirChecker DC(414, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);
  DC.GraphicsIgnored(1);

  return DC;
}

void IGESDraw_ToolCircArraySubfigure::OwnCheck
  (const Handle(IGESDraw_CircArraySubfigure)& /*ent*/,
   const Interface_ShareTool& , Handle(Interface_Check)& /*ach*/)  const
{
}

void IGESDraw_ToolCircArraySubfigure::OwnDump
  (const Handle(IGESDraw_CircArraySubfigure)& ent, const IGESData_IGESDumper& dumper,
   const Handle(Message_Messenger)& S, const Standard_Integer level)  const
{
  Standard_Integer tempSubLevel = (level <= 4) ? 0 : 1;

  S << "IGESDraw_CircArraySubfigure" << endl;

  S << "Base Entity : ";
  dumper.Dump(ent->BaseEntity(),S, tempSubLevel);
  S << endl;
  S << "Total Number Of Possible Instance Locations : " << ent->NbLocations()
    << endl;
  S << "Imaginary Circle. Radius : " << ent->CircleRadius() << "  Center : ";
  IGESData_DumpXYZL(S, level, ent->CenterPoint(), ent->Location());  S << endl;
  S << "Start Angle (in radians) : " << ent->StartAngle() << "  ";
  S << "Delta Angle (in radians) : " << ent->DeltaAngle() << endl;
  S << "Do-Dont Flag : ";
  if (ent->DoDontFlag())     S << "Dont" << endl;
  else                       S << "Do" << endl;
  S << "The Do-Dont List : ";
  IGESData_DumpVals(S ,level,1, ent->ListCount(),ent->ListPosition);
  S << endl;
}
