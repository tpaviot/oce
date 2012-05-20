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

#include <IGESDefs_ToolUnitsData.ixx>
#include <IGESData_ParamCursor.hxx>
#include <TCollection_HAsciiString.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <Interface_HArray1OfHAsciiString.hxx>
#include <IGESData_Dump.hxx>
#include <Interface_Macros.hxx>


IGESDefs_ToolUnitsData::IGESDefs_ToolUnitsData ()    {  }


void  IGESDefs_ToolUnitsData::ReadOwnParams
  (const Handle(IGESDefs_UnitsData)& ent,
   const Handle(IGESData_IGESReaderData)& /* IR */, IGESData_ParamReader& PR) const
{ 
  //Standard_Boolean st; //szv#4:S4163:12Mar99 moved down

  Standard_Integer nbval;
  Handle(Interface_HArray1OfHAsciiString) unitTypes;
  Handle(Interface_HArray1OfHAsciiString) unitValues;
  Handle(TColStd_HArray1OfReal) unitScales;

  Standard_Boolean st = PR.ReadInteger(PR.Current(), "Number of Units", nbval);
  if (st && nbval > 0)
    {
      unitTypes = new Interface_HArray1OfHAsciiString(1, nbval); 
      unitValues = new Interface_HArray1OfHAsciiString(1, nbval); 
      unitScales = new TColStd_HArray1OfReal(1, nbval); 
    }
  else  PR.AddFail("Number of Units: Less than or Equal or zero");

  if (! unitTypes.IsNull())
    for (Standard_Integer i = 1; i <= nbval; i++)
      {
	Handle(TCollection_HAsciiString) unitType;
	Handle(TCollection_HAsciiString) unitValue;
	Standard_Real unitScale;

	//st = PR.ReadText(PR.Current(), "Type of Unit", unitType); //szv#4:S4163:12Mar99 moved in if
	if (PR.ReadText(PR.Current(), "Type of Unit", unitType))
	  unitTypes->SetValue(i, unitType);

	//st = PR.ReadText(PR.Current(), "Value of Unit", unitValue); //szv#4:S4163:12Mar99 moved in if
	if (PR.ReadText(PR.Current(), "Value of Unit", unitValue))
	  unitValues->SetValue(i, unitValue);

	//st = PR.ReadReal(PR.Current(), "Scale of Unit", unitScale); //szv#4:S4163:12Mar99 moved in if
	if (PR.ReadReal(PR.Current(), "Scale of Unit", unitScale))
	  unitScales->SetValue(i, unitScale);
      }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init(unitTypes, unitValues, unitScales);
}

void  IGESDefs_ToolUnitsData::WriteOwnParams
  (const Handle(IGESDefs_UnitsData)& ent, IGESData_IGESWriter& IW) const 
{ 
  Standard_Integer upper = ent->NbUnits();
  IW.Send(upper);

  for (Standard_Integer i = 1; i <= upper; i++)
    {
      IW.Send(ent->UnitType(i));
      IW.Send(ent->UnitValue(i));
      IW.Send(ent->ScaleFactor(i));
    }
}

void  IGESDefs_ToolUnitsData::OwnShared
  (const Handle(IGESDefs_UnitsData)& /* ent */, Interface_EntityIterator& /* iter */) const
{
}

void  IGESDefs_ToolUnitsData::OwnCopy
  (const Handle(IGESDefs_UnitsData)& another,
   const Handle(IGESDefs_UnitsData)& ent, Interface_CopyTool& /* TC */) const
{
  Handle(Interface_HArray1OfHAsciiString) unitTypes;
  Handle(Interface_HArray1OfHAsciiString) unitValues;
  Handle(TColStd_HArray1OfReal) unitScales;

  Standard_Integer nbval = another->NbUnits();

  unitTypes  = new Interface_HArray1OfHAsciiString(1, nbval); 
  unitValues = new Interface_HArray1OfHAsciiString(1, nbval); 
  unitScales = new TColStd_HArray1OfReal(1, nbval); 

  for (Standard_Integer i = 1; i <= nbval; i++)
    {
      Handle(TCollection_HAsciiString) unitType =
	new TCollection_HAsciiString(another->UnitType(i));
      unitTypes->SetValue(i, unitType);
      Handle(TCollection_HAsciiString) unitValue =
	new TCollection_HAsciiString(another->UnitValue(i));
      unitValues->SetValue(i, unitValue);
      Standard_Real unitScale = another->ScaleFactor(i);
      unitScales->SetValue(i, unitScale);
    }
  ent->Init(unitTypes, unitValues, unitScales);
}

IGESData_DirChecker  IGESDefs_ToolUnitsData::DirChecker
  (const Handle(IGESDefs_UnitsData)& /* ent */ ) const 
{ 
  IGESData_DirChecker DC (316, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.SubordinateStatusRequired(0);
  DC.UseFlagRequired(2);
  DC.HierarchyStatusIgnored();
  return DC;
}

void  IGESDefs_ToolUnitsData::OwnCheck
  (const Handle(IGESDefs_UnitsData)& /* ent */,
   const Interface_ShareTool& , Handle(Interface_Check)& /* ach */) const 
{
}

void  IGESDefs_ToolUnitsData::OwnDump
  (const Handle(IGESDefs_UnitsData)& ent, const IGESData_IGESDumper& /* dumper */,
   const Handle(Message_Messenger)& S, const Standard_Integer level) const 
{ 
  S << "IGESDefs_UnitsData" << endl;
  S << "Number of Units : " << ent->NbUnits() << endl;
  S << "Type of Unit : " << endl;
  S << "Value of Unit : " << endl;
  S << "Scale Factor : " << endl;
  IGESData_DumpStrings(S,-level,1, ent->NbUnits(),ent->UnitType);
  S << endl;
  if (level > 4)
    {
      S << "Details of the Units" << endl;
      Standard_Integer upper = ent->NbUnits();
      for (Standard_Integer i = 1; i <= upper; i++)
	{
          S << "[" << i << "] Type  : ";
          IGESData_DumpString(S,ent->UnitType(i));
          S << endl;
          S << "     Value : ";
          IGESData_DumpString(S,ent->UnitValue(i));
          S << endl;
          S << "     ScaleFactor: " << ent->ScaleFactor(i) << endl;
	}
    }
  S << endl;
}
