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

#include <IGESSolid_SpecificModule.ixx>
#include <Interface_Macros.hxx>

#include <IGESSolid_Block.hxx>
#include <IGESSolid_BooleanTree.hxx>
#include <IGESSolid_ConeFrustum.hxx>
#include <IGESSolid_ConicalSurface.hxx>
#include <IGESSolid_Cylinder.hxx>
#include <IGESSolid_CylindricalSurface.hxx>
#include <IGESSolid_EdgeList.hxx>
#include <IGESSolid_Ellipsoid.hxx>
#include <IGESSolid_Face.hxx>
#include <IGESSolid_Loop.hxx>
#include <IGESSolid_ManifoldSolid.hxx>
#include <IGESSolid_PlaneSurface.hxx>
#include <IGESSolid_RightAngularWedge.hxx>
#include <IGESSolid_SelectedComponent.hxx>
#include <IGESSolid_Shell.hxx>
#include <IGESSolid_SolidAssembly.hxx>
#include <IGESSolid_SolidInstance.hxx>
#include <IGESSolid_SolidOfLinearExtrusion.hxx>
#include <IGESSolid_SolidOfRevolution.hxx>
#include <IGESSolid_Sphere.hxx>
#include <IGESSolid_SphericalSurface.hxx>
#include <IGESSolid_ToroidalSurface.hxx>
#include <IGESSolid_Torus.hxx>
#include <IGESSolid_VertexList.hxx>

#include <IGESSolid_ToolBlock.hxx>
#include <IGESSolid_ToolBooleanTree.hxx>
#include <IGESSolid_ToolConeFrustum.hxx>
#include <IGESSolid_ToolConicalSurface.hxx>
#include <IGESSolid_ToolCylinder.hxx>
#include <IGESSolid_ToolCylindricalSurface.hxx>
#include <IGESSolid_ToolEdgeList.hxx>
#include <IGESSolid_ToolEllipsoid.hxx>
#include <IGESSolid_ToolFace.hxx>
#include <IGESSolid_ToolLoop.hxx>
#include <IGESSolid_ToolManifoldSolid.hxx>
#include <IGESSolid_ToolPlaneSurface.hxx>
#include <IGESSolid_ToolRightAngularWedge.hxx>
#include <IGESSolid_ToolSelectedComponent.hxx>
#include <IGESSolid_ToolShell.hxx>
#include <IGESSolid_ToolSolidAssembly.hxx>
#include <IGESSolid_ToolSolidInstance.hxx>
#include <IGESSolid_ToolSolidOfLinearExtrusion.hxx>
#include <IGESSolid_ToolSolidOfRevolution.hxx>
#include <IGESSolid_ToolSphere.hxx>
#include <IGESSolid_ToolSphericalSurface.hxx>
#include <IGESSolid_ToolToroidalSurface.hxx>
#include <IGESSolid_ToolTorus.hxx>
#include <IGESSolid_ToolVertexList.hxx>



//  Each Module is attached to a Protocol : it must interprete Case Numbers
//  (arguments <CN> of various methods) in accordance to values returned by
//  the method TypeNumber from this Protocol


IGESSolid_SpecificModule::IGESSolid_SpecificModule()    {  }


    void  IGESSolid_SpecificModule::OwnDump
  (const Standard_Integer CN, const Handle(IGESData_IGESEntity)& ent,
   const IGESData_IGESDumper& dumper, const Handle(Message_Messenger)& S,
   const Standard_Integer own) const 
{
  switch (CN) {
    case  1 : {
      DeclareAndCast(IGESSolid_Block,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolBlock tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  2 : {
      DeclareAndCast(IGESSolid_BooleanTree,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolBooleanTree tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  3 : {
      DeclareAndCast(IGESSolid_ConeFrustum,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolConeFrustum tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  4 : {
      DeclareAndCast(IGESSolid_ConicalSurface,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolConicalSurface tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  5 : {
      DeclareAndCast(IGESSolid_Cylinder,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolCylinder tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  6 : {
      DeclareAndCast(IGESSolid_CylindricalSurface,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolCylindricalSurface tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  7 : {
      DeclareAndCast(IGESSolid_EdgeList,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolEdgeList tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  8 : {
      DeclareAndCast(IGESSolid_Ellipsoid,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolEllipsoid tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  9 : {
      DeclareAndCast(IGESSolid_Face,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolFace tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 10 : {
      DeclareAndCast(IGESSolid_Loop,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolLoop tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 11 : {
      DeclareAndCast(IGESSolid_ManifoldSolid,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolManifoldSolid tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 12 : {
      DeclareAndCast(IGESSolid_PlaneSurface,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolPlaneSurface tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 13 : {
      DeclareAndCast(IGESSolid_RightAngularWedge,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolRightAngularWedge tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 14 : {
      DeclareAndCast(IGESSolid_SelectedComponent,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolSelectedComponent tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 15 : {
      DeclareAndCast(IGESSolid_Shell,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolShell tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 16 : {
      DeclareAndCast(IGESSolid_SolidAssembly,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolSolidAssembly tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 17 : {
      DeclareAndCast(IGESSolid_SolidInstance,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolSolidInstance tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 18 : {
      DeclareAndCast(IGESSolid_SolidOfLinearExtrusion,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolSolidOfLinearExtrusion tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 19 : {
      DeclareAndCast(IGESSolid_SolidOfRevolution,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolSolidOfRevolution tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 20 : {
      DeclareAndCast(IGESSolid_Sphere,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolSphere tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 21 : {
      DeclareAndCast(IGESSolid_SphericalSurface,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolSphericalSurface tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 22 : {
      DeclareAndCast(IGESSolid_ToroidalSurface,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolToroidalSurface tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 23 : {
      DeclareAndCast(IGESSolid_Torus,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolTorus tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 24 : {
      DeclareAndCast(IGESSolid_VertexList,anent,ent);
      if (anent.IsNull()) return;
      IGESSolid_ToolVertexList tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    default : break;
  }
}
