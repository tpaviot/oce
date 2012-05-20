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

#include <IGESDefs_SpecificModule.ixx>
#include <Interface_Macros.hxx>

#include <IGESDefs_AssociativityDef.hxx>
#include <IGESDefs_AttributeDef.hxx>
#include <IGESDefs_AttributeTable.hxx>
#include <IGESDefs_GenericData.hxx>
#include <IGESDefs_MacroDef.hxx>
#include <IGESDefs_TabularData.hxx>
#include <IGESDefs_UnitsData.hxx>

#include <IGESDefs_ToolAssociativityDef.hxx>
#include <IGESDefs_ToolAttributeDef.hxx>
#include <IGESDefs_ToolAttributeTable.hxx>
#include <IGESDefs_ToolGenericData.hxx>
#include <IGESDefs_ToolMacroDef.hxx>
#include <IGESDefs_ToolTabularData.hxx>
#include <IGESDefs_ToolUnitsData.hxx>



//  Each Module is attached to a Protocol : it must interprete Case Numbers
//  (arguments <CN> of various methods) in accordance to values returned by
//  the method TypeNumber from this Protocol


IGESDefs_SpecificModule::IGESDefs_SpecificModule()    {  }


    void  IGESDefs_SpecificModule::OwnDump
  (const Standard_Integer CN, const Handle(IGESData_IGESEntity)& ent,
   const IGESData_IGESDumper& dumper, const Handle(Message_Messenger)& S,
   const Standard_Integer own) const 
{
  switch (CN) {
    case  1 : {
      DeclareAndCast(IGESDefs_AssociativityDef,anent,ent);
      if (anent.IsNull()) return;
      IGESDefs_ToolAssociativityDef tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  2 : {
      DeclareAndCast(IGESDefs_AttributeDef,anent,ent);
      if (anent.IsNull()) return;
      IGESDefs_ToolAttributeDef tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  3 : {
      DeclareAndCast(IGESDefs_AttributeTable,anent,ent);
      if (anent.IsNull()) return;
      IGESDefs_ToolAttributeTable tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  4 : {
      DeclareAndCast(IGESDefs_GenericData,anent,ent);
      if (anent.IsNull()) return;
      IGESDefs_ToolGenericData tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  5 : {
      DeclareAndCast(IGESDefs_MacroDef,anent,ent);
      if (anent.IsNull()) return;
      IGESDefs_ToolMacroDef tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  6 : {
      DeclareAndCast(IGESDefs_TabularData,anent,ent);
      if (anent.IsNull()) return;
      IGESDefs_ToolTabularData tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  7 : {
      DeclareAndCast(IGESDefs_UnitsData,anent,ent);
      if (anent.IsNull()) return;
      IGESDefs_ToolUnitsData tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    default : break;
  }
}
