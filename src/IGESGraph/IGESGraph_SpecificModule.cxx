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

#include <IGESGraph_SpecificModule.ixx>
#include <Interface_Macros.hxx>

#include <IGESGraph_Color.hxx>
#include <IGESGraph_DefinitionLevel.hxx>
#include <IGESGraph_DrawingSize.hxx>
#include <IGESGraph_DrawingUnits.hxx>
#include <IGESGraph_HighLight.hxx>
#include <IGESGraph_IntercharacterSpacing.hxx>
#include <IGESGraph_LineFontDefPattern.hxx>
#include <IGESGraph_LineFontPredefined.hxx>
#include <IGESGraph_LineFontDefTemplate.hxx>
#include <IGESGraph_NominalSize.hxx>
#include <IGESGraph_Pick.hxx>
#include <IGESGraph_TextDisplayTemplate.hxx>
#include <IGESGraph_TextFontDef.hxx>
#include <IGESGraph_UniformRectGrid.hxx>

#include <IGESGraph_ToolColor.hxx>
#include <IGESGraph_ToolDefinitionLevel.hxx>
#include <IGESGraph_ToolDrawingSize.hxx>
#include <IGESGraph_ToolDrawingUnits.hxx>
#include <IGESGraph_ToolHighLight.hxx>
#include <IGESGraph_ToolIntercharacterSpacing.hxx>
#include <IGESGraph_ToolLineFontDefPattern.hxx>
#include <IGESGraph_ToolLineFontPredefined.hxx>
#include <IGESGraph_ToolLineFontDefTemplate.hxx>
#include <IGESGraph_ToolNominalSize.hxx>
#include <IGESGraph_ToolPick.hxx>
#include <IGESGraph_ToolTextDisplayTemplate.hxx>
#include <IGESGraph_ToolTextFontDef.hxx>
#include <IGESGraph_ToolUniformRectGrid.hxx>



//  Each Module is attached to a Protocol : it must interprete Case Numbers
//  (arguments <CN> of various methods) in accordance to values returned by
//  the method TypeNumber from this Protocol


IGESGraph_SpecificModule::IGESGraph_SpecificModule()    {  }


    void  IGESGraph_SpecificModule::OwnDump
  (const Standard_Integer CN, const Handle(IGESData_IGESEntity)& ent,
   const IGESData_IGESDumper& dumper, const Handle(Message_Messenger)& S,
   const Standard_Integer own) const 
{
  switch (CN) {
    case  1 : {
      DeclareAndCast(IGESGraph_Color,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolColor tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  2 : {
      DeclareAndCast(IGESGraph_DefinitionLevel,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolDefinitionLevel tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  3 : {
      DeclareAndCast(IGESGraph_DrawingSize,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolDrawingSize tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  4 : {
      DeclareAndCast(IGESGraph_DrawingUnits,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolDrawingUnits tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  5 : {
      DeclareAndCast(IGESGraph_HighLight,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolHighLight tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  6 : {
      DeclareAndCast(IGESGraph_IntercharacterSpacing,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolIntercharacterSpacing tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  7 : {
      DeclareAndCast(IGESGraph_LineFontDefPattern,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolLineFontDefPattern tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  8 : {
      DeclareAndCast(IGESGraph_LineFontPredefined,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolLineFontPredefined tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case  9 : {
      DeclareAndCast(IGESGraph_LineFontDefTemplate,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolLineFontDefTemplate tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 10 : {
      DeclareAndCast(IGESGraph_NominalSize,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolNominalSize tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 11 : {
      DeclareAndCast(IGESGraph_Pick,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolPick tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 12 : {
      DeclareAndCast(IGESGraph_TextDisplayTemplate,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolTextDisplayTemplate tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 13 : {
      DeclareAndCast(IGESGraph_TextFontDef,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolTextFontDef tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    case 14 : {
      DeclareAndCast(IGESGraph_UniformRectGrid,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolUniformRectGrid tool;
      tool.OwnDump(anent,dumper,S,own);
    }
      break;
    default : break;
  }
}


    Standard_Boolean  IGESGraph_SpecificModule::OwnCorrect
  (const Standard_Integer CN, const Handle(IGESData_IGESEntity)& ent) const
{
//   Applies only on some types
  switch (CN) {
    case  3 : {
      DeclareAndCast(IGESGraph_DrawingSize,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolDrawingSize tool;
      return tool.OwnCorrect(anent);
    }
    case  4 : {
      DeclareAndCast(IGESGraph_DrawingUnits,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolDrawingUnits tool;
      return tool.OwnCorrect(anent);
    }
    case  5 : {
      DeclareAndCast(IGESGraph_HighLight,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolHighLight tool;
      return tool.OwnCorrect(anent);
    }
    case  6 : {
      DeclareAndCast(IGESGraph_IntercharacterSpacing,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolIntercharacterSpacing tool;
      return tool.OwnCorrect(anent);
    }
    case  8 : {
      DeclareAndCast(IGESGraph_LineFontPredefined,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolLineFontPredefined tool;
      return tool.OwnCorrect(anent);
    }
    case 10 : {
      DeclareAndCast(IGESGraph_NominalSize,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolNominalSize tool;
      return tool.OwnCorrect(anent);
    }
    case 11 : {
      DeclareAndCast(IGESGraph_Pick,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolPick tool;
      return tool.OwnCorrect(anent);
    }
    case 14 : {
      DeclareAndCast(IGESGraph_UniformRectGrid,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolUniformRectGrid tool;
      return tool.OwnCorrect(anent);
    }
    default : break;
  }
  return Standard_False;
}
