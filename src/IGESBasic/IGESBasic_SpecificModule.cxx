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

#include <IGESBasic_SpecificModule.ixx>
#include <Interface_Macros.hxx>

#include <IGESBasic_AssocGroupType.hxx>
#include <IGESBasic_ExternalRefFile.hxx>
#include <IGESBasic_ExternalRefFileIndex.hxx>
#include <IGESBasic_ExternalRefFileName.hxx>
#include <IGESBasic_ExternalRefLibName.hxx>
#include <IGESBasic_ExternalRefName.hxx>
#include <IGESBasic_ExternalReferenceFile.hxx>
#include <IGESBasic_Group.hxx>
#include <IGESBasic_GroupWithoutBackP.hxx>
#include <IGESBasic_Hierarchy.hxx>
#include <IGESBasic_Name.hxx>
#include <IGESBasic_OrderedGroup.hxx>
#include <IGESBasic_OrderedGroupWithoutBackP.hxx>
#include <IGESBasic_SingleParent.hxx>
#include <IGESBasic_SingularSubfigure.hxx>
#include <IGESBasic_SubfigureDef.hxx>

#include <IGESBasic_ToolAssocGroupType.hxx>
#include <IGESBasic_ToolExternalRefFile.hxx>
#include <IGESBasic_ToolExternalRefFileIndex.hxx>
#include <IGESBasic_ToolExternalRefFileName.hxx>
#include <IGESBasic_ToolExternalRefLibName.hxx>
#include <IGESBasic_ToolExternalRefName.hxx>
#include <IGESBasic_ToolExternalReferenceFile.hxx>
#include <IGESBasic_ToolGroup.hxx>
#include <IGESBasic_ToolGroupWithoutBackP.hxx>
#include <IGESBasic_ToolHierarchy.hxx>
#include <IGESBasic_ToolName.hxx>
#include <IGESBasic_ToolOrderedGroup.hxx>
#include <IGESBasic_ToolOrderedGroupWithoutBackP.hxx>
#include <IGESBasic_ToolSingleParent.hxx>
#include <IGESBasic_ToolSingularSubfigure.hxx>
#include <IGESBasic_ToolSubfigureDef.hxx>

#include <Message_Messenger.hxx>

//  Each Module is attached to a Protocol : it must interprete Case Numbers
//  (arguments <CN> of various methods) in accordance to values returned by
//  the method TypeNumber from this Protocol


IGESBasic_SpecificModule::IGESBasic_SpecificModule()    {  }


    void  IGESBasic_SpecificModule::OwnDump
  (const Standard_Integer CN, const Handle(IGESData_IGESEntity)& ent,
   const IGESData_IGESDumper& dumper, const Handle(Message_Messenger)& S,
   const Standard_Integer own) const 
{
  switch (CN) {
    case  1 : {
      DeclareAndCast(IGESBasic_AssocGroupType,anent,ent);
      if (anent.IsNull()) return;
      IGESBasic_ToolAssocGroupType tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  2 : {
      DeclareAndCast(IGESBasic_ExternalRefFile,anent,ent);
      if (anent.IsNull()) return;
      IGESBasic_ToolExternalRefFile tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  3 : {
      DeclareAndCast(IGESBasic_ExternalRefFileIndex,anent,ent);
      if (anent.IsNull()) return;
      IGESBasic_ToolExternalRefFileIndex tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  4 : {
      DeclareAndCast(IGESBasic_ExternalRefFileName,anent,ent);
      if (anent.IsNull()) return;
      IGESBasic_ToolExternalRefFileName tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  5 : {
      DeclareAndCast(IGESBasic_ExternalRefLibName,anent,ent);
      if (anent.IsNull()) return;
      IGESBasic_ToolExternalRefLibName tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  6 : {
      DeclareAndCast(IGESBasic_ExternalRefName,anent,ent);
      if (anent.IsNull()) return;
      IGESBasic_ToolExternalRefName tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  7 : {
      DeclareAndCast(IGESBasic_ExternalReferenceFile,anent,ent);
      if (anent.IsNull()) return;
      IGESBasic_ToolExternalReferenceFile tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  8 : {
      DeclareAndCast(IGESBasic_Group,anent,ent);
      if (anent.IsNull()) return;
      IGESBasic_ToolGroup tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  9 : {
      DeclareAndCast(IGESBasic_GroupWithoutBackP,anent,ent);
      if (anent.IsNull()) return;
      IGESBasic_ToolGroupWithoutBackP tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 10 : {
      DeclareAndCast(IGESBasic_Hierarchy,anent,ent);
      if (anent.IsNull()) return;
      IGESBasic_ToolHierarchy tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 11 : {
      DeclareAndCast(IGESBasic_Name,anent,ent);
      if (anent.IsNull()) return;
      IGESBasic_ToolName tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 12 : {
      DeclareAndCast(IGESBasic_OrderedGroup,anent,ent);
      if (anent.IsNull()) return;
      IGESBasic_ToolOrderedGroup tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 13 : {
      DeclareAndCast(IGESBasic_OrderedGroupWithoutBackP,anent,ent);
      if (anent.IsNull()) return;
      IGESBasic_ToolOrderedGroupWithoutBackP tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 14 : {
      DeclareAndCast(IGESBasic_SingleParent,anent,ent);
      if (anent.IsNull()) return;
      IGESBasic_ToolSingleParent tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 15 : {
      DeclareAndCast(IGESBasic_SingularSubfigure,anent,ent);
      if (anent.IsNull()) return;
      IGESBasic_ToolSingularSubfigure tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 16 : {
      DeclareAndCast(IGESBasic_SubfigureDef,anent,ent);
      if (anent.IsNull()) return;
      IGESBasic_ToolSubfigureDef tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    default : break;
  }
}


    Standard_Boolean  IGESBasic_SpecificModule::OwnCorrect
  (const Standard_Integer CN, const Handle(IGESData_IGESEntity)& ent) const
{
//   Applies only on some types
  switch (CN) {
    case  1 : {
      DeclareAndCast(IGESBasic_AssocGroupType,anent,ent);
      if (anent.IsNull()) break;
      IGESBasic_ToolAssocGroupType tool;
      return tool.OwnCorrect(anent);
    }
    case  8 : {
      DeclareAndCast(IGESBasic_Group,anent,ent);
      if (anent.IsNull()) break;
      IGESBasic_ToolGroup tool;
      return tool.OwnCorrect(anent);
    }
    case  9 : {
      DeclareAndCast(IGESBasic_GroupWithoutBackP,anent,ent);
      if (anent.IsNull()) break;
      IGESBasic_ToolGroupWithoutBackP tool;
      return tool.OwnCorrect(anent);
    }
    case 10 : {
      DeclareAndCast(IGESBasic_Hierarchy,anent,ent);
      if (anent.IsNull()) break;
      IGESBasic_ToolHierarchy tool;
      return tool.OwnCorrect(anent);
    }
    case 11 : {
      DeclareAndCast(IGESBasic_Name,anent,ent);
      if (anent.IsNull()) break;
      IGESBasic_ToolName tool;
      return tool.OwnCorrect(anent);
    }
    case 12 : {
      DeclareAndCast(IGESBasic_OrderedGroup,anent,ent);
      if (anent.IsNull()) break;
      IGESBasic_ToolOrderedGroup tool;
      return tool.OwnCorrect(anent);
    }
    case 13 : {
      DeclareAndCast(IGESBasic_OrderedGroupWithoutBackP,anent,ent);
      if (anent.IsNull()) break;
      IGESBasic_ToolOrderedGroupWithoutBackP tool;
      return tool.OwnCorrect(anent);
    }
    case 14 : {
      DeclareAndCast(IGESBasic_SingleParent,anent,ent);
      if (anent.IsNull()) break;
      IGESBasic_ToolSingleParent tool;
      return tool.OwnCorrect(anent);
    }
    default : break;
  }
  return Standard_False;
}
