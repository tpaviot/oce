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

#include <IGESAppli_SpecificModule.ixx>
#include <Interface_Macros.hxx>

#include <IGESAppli_DrilledHole.hxx>
#include <IGESAppli_ElementResults.hxx>
#include <IGESAppli_FiniteElement.hxx>
#include <IGESAppli_Flow.hxx>
#include <IGESAppli_FlowLineSpec.hxx>
#include <IGESAppli_LevelFunction.hxx>
#include <IGESAppli_LevelToPWBLayerMap.hxx>
#include <IGESAppli_LineWidening.hxx>
#include <IGESAppli_NodalConstraint.hxx>
#include <IGESAppli_NodalDisplAndRot.hxx>
#include <IGESAppli_NodalResults.hxx>
#include <IGESAppli_Node.hxx>
#include <IGESAppli_PWBArtworkStackup.hxx>
#include <IGESAppli_PWBDrilledHole.hxx>
#include <IGESAppli_PartNumber.hxx>
#include <IGESAppli_PinNumber.hxx>
#include <IGESAppli_PipingFlow.hxx>
#include <IGESAppli_ReferenceDesignator.hxx>
#include <IGESAppli_RegionRestriction.hxx>

#include <IGESAppli_ToolDrilledHole.hxx>
#include <IGESAppli_ToolElementResults.hxx>
#include <IGESAppli_ToolFiniteElement.hxx>
#include <IGESAppli_ToolFlow.hxx>
#include <IGESAppli_ToolFlowLineSpec.hxx>
#include <IGESAppli_ToolLevelFunction.hxx>
#include <IGESAppli_ToolLevelToPWBLayerMap.hxx>
#include <IGESAppli_ToolLineWidening.hxx>
#include <IGESAppli_ToolNodalConstraint.hxx>
#include <IGESAppli_ToolNodalDisplAndRot.hxx>
#include <IGESAppli_ToolNodalResults.hxx>
#include <IGESAppli_ToolNode.hxx>
#include <IGESAppli_ToolPWBArtworkStackup.hxx>
#include <IGESAppli_ToolPWBDrilledHole.hxx>
#include <IGESAppli_ToolPartNumber.hxx>
#include <IGESAppli_ToolPinNumber.hxx>
#include <IGESAppli_ToolPipingFlow.hxx>
#include <IGESAppli_ToolReferenceDesignator.hxx>
#include <IGESAppli_ToolRegionRestriction.hxx>



//  Each Module is attached to a Protocol : it must interprete Case Numbers
//  (arguments <CN> of various methods) in accordance to values returned by
//  the method TypeNumber from this Protocol


IGESAppli_SpecificModule::IGESAppli_SpecificModule()    {  }


    void  IGESAppli_SpecificModule::OwnDump
  (const Standard_Integer CN, const Handle(IGESData_IGESEntity)& ent,
   const IGESData_IGESDumper& dumper, const Handle(Message_Messenger)& S,
   const Standard_Integer own) const 
{
  switch (CN) {
    case  1 : {
      DeclareAndCast(IGESAppli_DrilledHole,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolDrilledHole tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  2 : {
      DeclareAndCast(IGESAppli_ElementResults,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolElementResults tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  3 : {
      DeclareAndCast(IGESAppli_FiniteElement,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolFiniteElement tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  4 : {
      DeclareAndCast(IGESAppli_Flow,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolFlow tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  5 : {
      DeclareAndCast(IGESAppli_FlowLineSpec,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolFlowLineSpec tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  6 : {
      DeclareAndCast(IGESAppli_LevelFunction,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolLevelFunction tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  7 : {
      DeclareAndCast(IGESAppli_LevelToPWBLayerMap,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolLevelToPWBLayerMap tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  8 : {
      DeclareAndCast(IGESAppli_LineWidening,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolLineWidening tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  9 : {
      DeclareAndCast(IGESAppli_NodalConstraint,anent,ent) ;
      if (anent.IsNull()) return;
      IGESAppli_ToolNodalConstraint tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 10 : {
      DeclareAndCast(IGESAppli_NodalDisplAndRot,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolNodalDisplAndRot tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 11 : {
      DeclareAndCast(IGESAppli_NodalResults,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolNodalResults tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 12 : {
      DeclareAndCast(IGESAppli_Node,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolNode tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 13 : {
      DeclareAndCast(IGESAppli_PWBArtworkStackup,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolPWBArtworkStackup tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 14 : {
      DeclareAndCast(IGESAppli_PWBDrilledHole,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolPWBDrilledHole tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 15 : {
      DeclareAndCast(IGESAppli_PartNumber,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolPartNumber tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 16 : {
      DeclareAndCast(IGESAppli_PinNumber,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolPinNumber tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 17 : {
      DeclareAndCast(IGESAppli_PipingFlow,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolPipingFlow tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 18 : {
      DeclareAndCast(IGESAppli_ReferenceDesignator,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolReferenceDesignator tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 19 : {
      DeclareAndCast(IGESAppli_RegionRestriction,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolRegionRestriction tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    default : break;
  }
}


    Standard_Boolean  IGESAppli_SpecificModule::OwnCorrect
  (const Standard_Integer CN, const Handle(IGESData_IGESEntity)& ent) const
{
//   Applies only on some types
  switch (CN) {
    case  1 : {
      DeclareAndCast(IGESAppli_DrilledHole,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolDrilledHole tool;
      return tool.OwnCorrect(anent);
    }
    case  4 : {
      DeclareAndCast(IGESAppli_Flow,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolFlow tool;
      return tool.OwnCorrect(anent);
    }
    case  6 : {
      DeclareAndCast(IGESAppli_LevelFunction,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolLevelFunction tool;
      return tool.OwnCorrect(anent);
    }
    case  8 : {
      DeclareAndCast(IGESAppli_LineWidening,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolLineWidening tool;
      return tool.OwnCorrect(anent);
    }
    case 14 : {
      DeclareAndCast(IGESAppli_PWBDrilledHole,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolPWBDrilledHole tool;
      return tool.OwnCorrect(anent);
    }
    case 15 : {
      DeclareAndCast(IGESAppli_PartNumber,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolPartNumber tool;
      return tool.OwnCorrect(anent);
    }
    case 16 : {
      DeclareAndCast(IGESAppli_PinNumber,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolPinNumber tool;
      return tool.OwnCorrect(anent);
    }
    case 17 : {
      DeclareAndCast(IGESAppli_PipingFlow,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolPipingFlow tool;
      return tool.OwnCorrect(anent);
    }
    case 18 : {
      DeclareAndCast(IGESAppli_ReferenceDesignator,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolReferenceDesignator tool;
      return tool.OwnCorrect(anent);
    }
    case 19 : {
      DeclareAndCast(IGESAppli_RegionRestriction,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolRegionRestriction tool;
      return tool.OwnCorrect(anent);
    }
    default : break;
  }
  return Standard_False;
}
