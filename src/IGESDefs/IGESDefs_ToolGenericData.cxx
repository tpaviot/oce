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

#include <IGESDefs_ToolGenericData.ixx>
#include <IGESData_ParamCursor.hxx>
#include <IGESData_IGESEntity.hxx>
#include <TColStd_HArray1OfTransient.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <TCollection_HAsciiString.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <IGESData_HArray1OfIGESEntity.hxx>
#include <Interface_HArray1OfHAsciiString.hxx>
#include <Interface_Macros.hxx>
#include <IGESData_Dump.hxx>


IGESDefs_ToolGenericData::IGESDefs_ToolGenericData ()    {  }


void  IGESDefs_ToolGenericData::ReadOwnParams
  (const Handle(IGESDefs_GenericData)& ent,
   const Handle(IGESData_IGESReaderData)& IR, IGESData_ParamReader& PR) const
{
  //Standard_Boolean st; //szv#4:S4163:12Mar99 moved down
  Standard_Integer i, num;
  Standard_Integer tempNbPropVal;
  Handle(TCollection_HAsciiString) tempName;
  Handle(TColStd_HArray1OfInteger) tempTypes;
  Handle(TColStd_HArray1OfTransient) tempValues;

  PR.ReadInteger(PR.Current(), "Number of property values", tempNbPropVal); //szv#4:S4163:12Mar99 `st=` not needed

  PR.ReadText(PR.Current(), "Property Name", tempName); //szv#4:S4163:12Mar99 `st=` not needed

  Standard_Boolean st = PR.ReadInteger(PR.Current(), "Number of TYPE/VALUEs", num);
  if (st && num > 0)
    {
      tempTypes = new TColStd_HArray1OfInteger(1, num);
      tempValues = new TColStd_HArray1OfTransient(1, num);
    }
  else  PR.AddFail("Number of TYPE/VALUEs: Not Positive");

  if (!tempTypes.IsNull() && !tempValues.IsNull())
    for ( i = 1; i <= num; i++ )
      {
	Standard_Integer tempTyp;
	PR.ReadInteger(PR.Current(), "Type code", tempTyp); //szv#4:S4163:12Mar99 `st=` not needed
	tempTypes->SetValue(i, tempTyp);
	switch (tempTyp)
          {
	  case 0: // No value
	    PR.SetCurrentNumber(PR.CurrentNumber()+1);
	    break;
	  case 1: // Integer
	    {
	      Handle(TColStd_HArray1OfInteger) tempObj;
	      //st = PR.ReadInts(PR.CurrentList(1), "Integer value", tempObj); //szv#4:S4163:12Mar99 moved in if
	      if (PR.ReadInts(PR.CurrentList(1), "Integer value", tempObj))
		tempValues->SetValue(i, tempObj);
	    }
	    break;
	  case 2: // Real
	    {
	      Handle(TColStd_HArray1OfReal) tempObj;
	      //st = PR.ReadReals(PR.CurrentList(1), "Real value", tempObj); //szv#4:S4163:12Mar99 moved in if
	      if (PR.ReadReals(PR.CurrentList(1), "Real value", tempObj))
		tempValues->SetValue(i, tempObj);
	    }
	    break;
	  case 3: // Character string
	    {
	      Handle(TCollection_HAsciiString) tempObj;
	      //st = PR.ReadText(PR.Current(), "String value", tempObj); //szv#4:S4163:12Mar99 moved in if
	      if (PR.ReadText(PR.Current(), "String value", tempObj))
		tempValues->SetValue(i, tempObj);
	    }
	    break;
	  case 4: // Pointer
	    {
	      Handle(IGESData_IGESEntity) tempEntity;
	      //st = PR.ReadEntity(IR, PR.Current(), "Entity value", tempEntity); //szv#4:S4163:12Mar99 moved in if
	      if (PR.ReadEntity(IR, PR.Current(), "Entity value", tempEntity))
		tempValues->SetValue(i, tempEntity);
	    }
	    break;
	  case 5: // Not used
	    PR.SetCurrentNumber(PR.CurrentNumber()+1);
	    break;
	  case 6: // Logical
	    {
	      Handle(TColStd_HArray1OfInteger) tempObj = new TColStd_HArray1OfInteger(1, 1);
	      Standard_Boolean tempBool;
	      //st = PR.ReadBoolean(PR.Current(), "Boolean value", tempBool); //szv#4:S4163:12Mar99 moved in if
	      if (PR.ReadBoolean(PR.Current(), "Boolean value", tempBool)) {
		tempObj->SetValue(1, (tempBool ? 1 : 0));
		tempValues->SetValue(i, tempObj);
	      }
	    }
	    break;
          }
      }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init (tempNbPropVal, tempName, tempTypes, tempValues);
}

void  IGESDefs_ToolGenericData::WriteOwnParams
  (const Handle(IGESDefs_GenericData)& ent, IGESData_IGESWriter& IW) const
{
  Standard_Integer i, num;
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->Name());
  IW.Send(ent->NbTypeValuePairs());
  for ( num = ent->NbTypeValuePairs(), i = 1; i <= num; i++ )
    {
      IW.Send(ent->Type(i));
      switch (ent->Type(i))
	{
	case 0 : IW.SendVoid();	  break;
	case 1 : IW.Send(ent->ValueAsInteger(i));  break;
	case 2 : IW.Send(ent->ValueAsReal(i));     break;
	case 3 : IW.Send(ent->ValueAsString(i));   break;
	case 4 : IW.Send(ent->ValueAsEntity(i));   break;
	case 5 : IW.SendVoid();   break;
	case 6 : IW.SendBoolean(ent->ValueAsLogical(i));  break;
        default : break;
	}
    }
}

void  IGESDefs_ToolGenericData::OwnShared
  (const Handle(IGESDefs_GenericData)& ent, Interface_EntityIterator& iter) const
{
  Standard_Integer i, num;
  for ( num = ent->NbTypeValuePairs(), i = 1; i <= num; i++ )
    {
      if (ent->Type(i) == 4)
	iter.GetOneItem(ent->ValueAsEntity(i));
    }
}

void  IGESDefs_ToolGenericData::OwnCopy
  (const Handle(IGESDefs_GenericData)& another,
   const Handle(IGESDefs_GenericData)& ent, Interface_CopyTool& TC) const
{
  Standard_Integer num = another->NbTypeValuePairs();
  Standard_Integer tempNbPropVal = another->NbPropertyValues();
  Handle(TCollection_HAsciiString) tempName =
    new TCollection_HAsciiString(another->Name());
  Handle(TColStd_HArray1OfInteger) tempTypes =
    new TColStd_HArray1OfInteger(1, num);
  Handle(TColStd_HArray1OfTransient) tempValues =
    new TColStd_HArray1OfTransient(1, num);

  for (Standard_Integer i = 1; i <= num; i++)
    {
      tempTypes->SetValue(i, another->Type(i));
      switch (another->Type(i))
	{
	case 0: // No value
          break;
	case 1: // Integer
          {
	    Handle(TColStd_HArray1OfInteger) tempObj =
	      new TColStd_HArray1OfInteger(1,1);
	    tempObj->SetValue(1,another->ValueAsInteger(i));
	    tempValues->SetValue(i, tempObj);
          }
          break;
	case 2: // Real
          {
	    Handle(TColStd_HArray1OfReal) tempObj =
	      new TColStd_HArray1OfReal(1,1);
	    tempObj->SetValue(1,another->ValueAsReal(i));
	    tempValues->SetValue(i, tempObj);
          }
          break;
	case 3: // Character string
          {
	    tempValues->SetValue
	      (i, new TCollection_HAsciiString(another->ValueAsString(i)));
          }
          break;
	case 4: // Pointer
          {
	    DeclareAndCast(IGESData_IGESEntity, tempObj,
			   TC.Transferred(another->ValueAsEntity(i)));
	    tempValues->SetValue(i, tempObj);
          }
          break;
	case 5: // Not used
	  break;
	case 6: // Logical
          {
	    Handle(TColStd_HArray1OfInteger) tempObj =
	      new TColStd_HArray1OfInteger(1,1);
	    tempObj->SetValue(1, (another->ValueAsLogical(i) ? 1 : 0) );
	    tempValues->SetValue(i, tempObj);
          }
          break;
	}
    }
  ent->Init (tempNbPropVal, tempName, tempTypes, tempValues);
}

IGESData_DirChecker  IGESDefs_ToolGenericData::DirChecker
  (const Handle(IGESDefs_GenericData)& /* ent */ ) const
{
  IGESData_DirChecker DC(406, 27);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.SubordinateStatusRequired(1);
  DC.UseFlagRequired(2);
  DC.HierarchyStatusIgnored();
  return DC;
}

void  IGESDefs_ToolGenericData::OwnCheck
  (const Handle(IGESDefs_GenericData)& ent,
   const Interface_ShareTool& , Handle(Interface_Check)& ach) const
{
  if (ent->NbPropertyValues() != ent->NbTypeValuePairs()*2 + 2)
    ach->AddFail("Nb. of Property Values not consistent with Nb. of Type/value Pairs");
}

void  IGESDefs_ToolGenericData::OwnDump
  (const Handle(IGESDefs_GenericData)& ent, const IGESData_IGESDumper& dumper,
   const Handle(Message_Messenger)& S, const Standard_Integer level) const
{
  S << "IGESDefs_GenericData" << endl;
  S << "Number of property values : " << ent->NbPropertyValues() << endl;
  S << "Property Name : ";
  IGESData_DumpString(S,ent->Name());
  S << endl;
  switch (level)
    {
    case 4:
      S << "Types  : " << endl;
      S << "Values : " << "Count = " << ent->NbTypeValuePairs() << endl;
      S << "      [ as level > 4 for content ]" << endl;
      break;
    case 5:
    case 6:
      {
	Standard_Integer i, num;
	S << "Types & Values : " << endl;
	for ( num = ent->NbTypeValuePairs(), i = 1; i <= num; i++ )
          {
	    S << "[" << i << "]: ";
	    S << "Type : " << ent->Type(i);
	    switch (ent->Type(i)) {
	      case 0 : S << "  (Void)";   break;
	      case 1 : S << "  Integer, Value : " << ent->ValueAsInteger(i);
		break;
	      case 2 : S << "  Real   , Value : " << ent->ValueAsReal(i);
		break;
	      case 3 : S << "  String , Value : ";
		IGESData_DumpString(S,ent->ValueAsString(i));    break;
	      case 4 : S << "  Entity , Value : ";
		dumper.Dump(ent->ValueAsEntity(i),S,level-1);    break;
	      case 5 : S << " (Not used)";  break;
	      case 6 : S << "  Logical, Value : "
		<< (ent->ValueAsLogical(i) ? "True" : "False");  break;
	      default : break;
	      }
	    S << endl;
          }
      }
    }
  S << endl;
}
