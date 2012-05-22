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

#include <IGESAppli_GeneralModule.ixx>
#include <Interface_Macros.hxx>
#include <Interface_Category.hxx>

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


IGESAppli_GeneralModule::IGESAppli_GeneralModule ()    {  }


    void  IGESAppli_GeneralModule::OwnSharedCase
  (const Standard_Integer CN, const Handle(IGESData_IGESEntity)& ent,
   Interface_EntityIterator& iter) const 
{
  switch (CN) {
    case  1 : {
      DeclareAndCast(IGESAppli_DrilledHole,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolDrilledHole tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case  2 : {
      DeclareAndCast(IGESAppli_ElementResults,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolElementResults tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case  3 : {
      DeclareAndCast(IGESAppli_FiniteElement,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolFiniteElement tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case  4 : {
      DeclareAndCast(IGESAppli_Flow,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolFlow tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case  5 : {
      DeclareAndCast(IGESAppli_FlowLineSpec,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolFlowLineSpec tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case  6 : {
      DeclareAndCast(IGESAppli_LevelFunction,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolLevelFunction tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case  7 : {
      DeclareAndCast(IGESAppli_LevelToPWBLayerMap,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolLevelToPWBLayerMap tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case  8 : {
      DeclareAndCast(IGESAppli_LineWidening,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolLineWidening tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case  9 : {
      DeclareAndCast(IGESAppli_NodalConstraint,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolNodalConstraint tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case 10 : {
      DeclareAndCast(IGESAppli_NodalDisplAndRot,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolNodalDisplAndRot tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case 11 : {
      DeclareAndCast(IGESAppli_NodalResults,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolNodalResults tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case 12 : {
      DeclareAndCast(IGESAppli_Node,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolNode tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case 13 : {
      DeclareAndCast(IGESAppli_PWBArtworkStackup,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolPWBArtworkStackup tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case 14 : {
      DeclareAndCast(IGESAppli_PWBDrilledHole,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolPWBDrilledHole tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case 15 : {
      DeclareAndCast(IGESAppli_PartNumber,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolPartNumber tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case 16 : {
      DeclareAndCast(IGESAppli_PinNumber,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolPinNumber tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case 17 : {
      DeclareAndCast(IGESAppli_PipingFlow,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolPipingFlow tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case 18 : {
      DeclareAndCast(IGESAppli_ReferenceDesignator,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolReferenceDesignator tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case 19 : {
      DeclareAndCast(IGESAppli_RegionRestriction,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolRegionRestriction tool;
      tool.OwnShared(anent,iter);
    }
      break;
    default : break;
  }
}


    IGESData_DirChecker  IGESAppli_GeneralModule::DirChecker
  (const Standard_Integer CN, const Handle(IGESData_IGESEntity)& ent) const 
{
  switch (CN) {
    case  1 : {
      DeclareAndCast(IGESAppli_DrilledHole,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolDrilledHole tool;
      return tool.DirChecker(anent);
    }
    case  2 : {
      DeclareAndCast(IGESAppli_ElementResults,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolElementResults tool;
      return tool.DirChecker(anent);
    }
    case  3 : {
      DeclareAndCast(IGESAppli_FiniteElement,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolFiniteElement tool;
      return tool.DirChecker(anent);
    }
    case  4 : {
      DeclareAndCast(IGESAppli_Flow,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolFlow tool;
      return tool.DirChecker(anent);
    }
    case  5 : {
      DeclareAndCast(IGESAppli_FlowLineSpec,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolFlowLineSpec tool;
      return tool.DirChecker(anent);
    }
    case  6 : {
      DeclareAndCast(IGESAppli_LevelFunction,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolLevelFunction tool;
      return tool.DirChecker(anent);
    }
    case  7 : {
      DeclareAndCast(IGESAppli_LevelToPWBLayerMap,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolLevelToPWBLayerMap tool;
      return tool.DirChecker(anent);
    }
    case  8 : {
      DeclareAndCast(IGESAppli_LineWidening,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolLineWidening tool;
      return tool.DirChecker(anent);
    }
    case  9 : {
      DeclareAndCast(IGESAppli_NodalConstraint,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolNodalConstraint tool;
      return tool.DirChecker(anent);
    }
    case 10 : {
      DeclareAndCast(IGESAppli_NodalDisplAndRot,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolNodalDisplAndRot tool;
      return tool.DirChecker(anent);
    }
    case 11 : {
      DeclareAndCast(IGESAppli_NodalResults,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolNodalResults tool;
      return tool.DirChecker(anent);
    }
    case 12 : {
      DeclareAndCast(IGESAppli_Node,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolNode tool;
      return tool.DirChecker(anent);
    }
    case 13 : {
      DeclareAndCast(IGESAppli_PWBArtworkStackup,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolPWBArtworkStackup tool;
      return tool.DirChecker(anent);
    }
    case 14 : {
      DeclareAndCast(IGESAppli_PWBDrilledHole,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolPWBDrilledHole tool;
      return tool.DirChecker(anent);
    }
    case 15 : {
      DeclareAndCast(IGESAppli_PartNumber,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolPartNumber tool;
      return tool.DirChecker(anent);
    }
    case 16 : {
      DeclareAndCast(IGESAppli_PinNumber,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolPinNumber tool;
      return tool.DirChecker(anent);
    }
    case 17 : {
      DeclareAndCast(IGESAppli_PipingFlow,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolPipingFlow tool;
      return tool.DirChecker(anent);
    }
    case 18 : {
      DeclareAndCast(IGESAppli_ReferenceDesignator,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolReferenceDesignator tool;
      return tool.DirChecker(anent);
    }
    case 19 : {
      DeclareAndCast(IGESAppli_RegionRestriction,anent,ent);
      if (anent.IsNull()) break;
      IGESAppli_ToolRegionRestriction tool;
      return tool.DirChecker(anent);
    }
    default : break;
  }
  return IGESData_DirChecker();    // by default, no specific criterium
}


    void  IGESAppli_GeneralModule::OwnCheckCase
  (const Standard_Integer CN, const Handle(IGESData_IGESEntity)& ent,
   const Interface_ShareTool& shares, Handle(Interface_Check)& ach) const 
{
  switch (CN) {
    case  1 : {
      DeclareAndCast(IGESAppli_DrilledHole,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolDrilledHole tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case  2 : {
      DeclareAndCast(IGESAppli_ElementResults,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolElementResults tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case  3 : {
      DeclareAndCast(IGESAppli_FiniteElement,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolFiniteElement tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case  4 : {
      DeclareAndCast(IGESAppli_Flow,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolFlow tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case  5 : {
      DeclareAndCast(IGESAppli_FlowLineSpec,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolFlowLineSpec tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case  6 : {
      DeclareAndCast(IGESAppli_LevelFunction,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolLevelFunction tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case  7 : {
      DeclareAndCast(IGESAppli_LevelToPWBLayerMap,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolLevelToPWBLayerMap tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case  8 : {
      DeclareAndCast(IGESAppli_LineWidening,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolLineWidening tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case  9 : {
      DeclareAndCast(IGESAppli_NodalConstraint,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolNodalConstraint tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case 10 : {
      DeclareAndCast(IGESAppli_NodalDisplAndRot,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolNodalDisplAndRot tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case 11 : {
      DeclareAndCast(IGESAppli_NodalResults,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolNodalResults tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case 12 : {
      DeclareAndCast(IGESAppli_Node,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolNode tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case 13 : {
      DeclareAndCast(IGESAppli_PWBArtworkStackup,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolPWBArtworkStackup tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case 14 : {
      DeclareAndCast(IGESAppli_PWBDrilledHole,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolPWBDrilledHole tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case 15 : {
      DeclareAndCast(IGESAppli_PartNumber,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolPartNumber tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case 16 : {
      DeclareAndCast(IGESAppli_PinNumber,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolPinNumber tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case 17 : {
      DeclareAndCast(IGESAppli_PipingFlow,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolPipingFlow tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case 18 : {
      DeclareAndCast(IGESAppli_ReferenceDesignator,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolReferenceDesignator tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case 19 : {
      DeclareAndCast(IGESAppli_RegionRestriction,anent,ent);
      if (anent.IsNull()) return;
      IGESAppli_ToolRegionRestriction tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    default : break;
  }
}

    Standard_Boolean  IGESAppli_GeneralModule::NewVoid
  (const Standard_Integer CN, Handle(Standard_Transient)& ent) const 
{
  switch (CN) {
    case  1 : ent = new IGESAppli_DrilledHole;	break;
    case  2 : ent = new IGESAppli_ElementResults;	break;
    case  3 : ent = new IGESAppli_FiniteElement;	break;
    case  4 : ent = new IGESAppli_Flow;	break;
    case  5 : ent = new IGESAppli_FlowLineSpec;	break;
    case  6 : ent = new IGESAppli_LevelFunction;	break;
    case  7 : ent = new IGESAppli_LevelToPWBLayerMap;	break;
    case  8 : ent = new IGESAppli_LineWidening;	break;
    case  9 : ent = new IGESAppli_NodalConstraint;	break;
    case 10 : ent = new IGESAppli_NodalDisplAndRot;	break;
    case 11 : ent = new IGESAppli_NodalResults;	break;
    case 12 : ent = new IGESAppli_Node;	break;
    case 13 : ent = new IGESAppli_PWBArtworkStackup;	break;
    case 14 : ent = new IGESAppli_PWBDrilledHole;	break;
    case 15 : ent = new IGESAppli_PartNumber;	break;
    case 16 : ent = new IGESAppli_PinNumber;	break;
    case 17 : ent = new IGESAppli_PipingFlow;	break;
    case 18 : ent = new IGESAppli_ReferenceDesignator;	break;
    case 19 : ent = new IGESAppli_RegionRestriction;	break;
    default : return Standard_False;    // by default, Failure on Recognize
  }
  return Standard_True;
}

    void  IGESAppli_GeneralModule::OwnCopyCase
  (const Standard_Integer CN,
   const Handle(IGESData_IGESEntity)& entfrom,
   const Handle(IGESData_IGESEntity)& entto,
   Interface_CopyTool& TC) const 
{
  switch (CN) {
    case  1 : {
      DeclareAndCast(IGESAppli_DrilledHole,enfr,entfrom);
      DeclareAndCast(IGESAppli_DrilledHole,ento,entto);
      IGESAppli_ToolDrilledHole tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case  2 : {
      DeclareAndCast(IGESAppli_ElementResults,enfr,entfrom);
      DeclareAndCast(IGESAppli_ElementResults,ento,entto);
      IGESAppli_ToolElementResults tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case  3 : {
      DeclareAndCast(IGESAppli_FiniteElement,enfr,entfrom);
      DeclareAndCast(IGESAppli_FiniteElement,ento,entto);
      IGESAppli_ToolFiniteElement tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case  4 : {
      DeclareAndCast(IGESAppli_Flow,enfr,entfrom);
      DeclareAndCast(IGESAppli_Flow,ento,entto);
      IGESAppli_ToolFlow tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case  5 : {
      DeclareAndCast(IGESAppli_FlowLineSpec,enfr,entfrom);
      DeclareAndCast(IGESAppli_FlowLineSpec,ento,entto);
      IGESAppli_ToolFlowLineSpec tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case  6 : {
      DeclareAndCast(IGESAppli_LevelFunction,enfr,entfrom);
      DeclareAndCast(IGESAppli_LevelFunction,ento,entto);
      IGESAppli_ToolLevelFunction tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case  7 : {
      DeclareAndCast(IGESAppli_LevelToPWBLayerMap,enfr,entfrom);
      DeclareAndCast(IGESAppli_LevelToPWBLayerMap,ento,entto);
      IGESAppli_ToolLevelToPWBLayerMap tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case  8 : {
      DeclareAndCast(IGESAppli_LineWidening,enfr,entfrom);
      DeclareAndCast(IGESAppli_LineWidening,ento,entto);
      IGESAppli_ToolLineWidening tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case  9 : {
      DeclareAndCast(IGESAppli_NodalConstraint,enfr,entfrom);
      DeclareAndCast(IGESAppli_NodalConstraint,ento,entto);
      IGESAppli_ToolNodalConstraint tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case 10 : {
      DeclareAndCast(IGESAppli_NodalDisplAndRot,enfr,entfrom);
      DeclareAndCast(IGESAppli_NodalDisplAndRot,ento,entto);
      IGESAppli_ToolNodalDisplAndRot tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case 11 : {
      DeclareAndCast(IGESAppli_NodalResults,enfr,entfrom);
      DeclareAndCast(IGESAppli_NodalResults,ento,entto);
      IGESAppli_ToolNodalResults tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case 12 : {
      DeclareAndCast(IGESAppli_Node,enfr,entfrom);
      DeclareAndCast(IGESAppli_Node,ento,entto);
      IGESAppli_ToolNode tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case 13 : {
      DeclareAndCast(IGESAppli_PWBArtworkStackup,enfr,entfrom);
      DeclareAndCast(IGESAppli_PWBArtworkStackup,ento,entto);
      IGESAppli_ToolPWBArtworkStackup tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case 14 : {
      DeclareAndCast(IGESAppli_PWBDrilledHole,enfr,entfrom);
      DeclareAndCast(IGESAppli_PWBDrilledHole,ento,entto);
      IGESAppli_ToolPWBDrilledHole tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case 15 : {
      DeclareAndCast(IGESAppli_PartNumber,enfr,entfrom);
      DeclareAndCast(IGESAppli_PartNumber,ento,entto);
      IGESAppli_ToolPartNumber tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case 16 : {
      DeclareAndCast(IGESAppli_PinNumber,enfr,entfrom);
      DeclareAndCast(IGESAppli_PinNumber,ento,entto);
      IGESAppli_ToolPinNumber tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case 17 : {
      DeclareAndCast(IGESAppli_PipingFlow,enfr,entfrom);
      DeclareAndCast(IGESAppli_PipingFlow,ento,entto);
      IGESAppli_ToolPipingFlow tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case 18 : {
      DeclareAndCast(IGESAppli_ReferenceDesignator,enfr,entfrom);
      DeclareAndCast(IGESAppli_ReferenceDesignator,ento,entto);
      IGESAppli_ToolReferenceDesignator tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case 19 : {
      DeclareAndCast(IGESAppli_RegionRestriction,enfr,entfrom);
      DeclareAndCast(IGESAppli_RegionRestriction,ento,entto);
      IGESAppli_ToolRegionRestriction tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    default : break;
  }
}


    Standard_Integer  IGESAppli_GeneralModule::CategoryNumber
  (const Standard_Integer CN, const Handle(Standard_Transient)& ent,
   const Interface_ShareTool& ) const
{
  if (CN == 4 || CN == 5 || CN == 17) return Interface_Category::Number("Piping");
  if (CN == 2 || CN == 3 || (CN >= 9 && CN <= 12)) return Interface_Category::Number("FEA");
  return Interface_Category::Number("Professional");
}
