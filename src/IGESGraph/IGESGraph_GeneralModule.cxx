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

#include <IGESGraph_GeneralModule.ixx>
#include <Interface_Macros.hxx>
#include <Interface_Category.hxx>

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


IGESGraph_GeneralModule::IGESGraph_GeneralModule ()    {  }


    void  IGESGraph_GeneralModule::OwnSharedCase
  (const Standard_Integer CN, const Handle(IGESData_IGESEntity)& ent,
   Interface_EntityIterator& iter) const 
{
  switch (CN) {
    case  1 : {
      DeclareAndCast(IGESGraph_Color,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolColor tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case  2 : {
      DeclareAndCast(IGESGraph_DefinitionLevel,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolDefinitionLevel tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case  3 : {
      DeclareAndCast(IGESGraph_DrawingSize,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolDrawingSize tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case  4 : {
      DeclareAndCast(IGESGraph_DrawingUnits,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolDrawingUnits tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case  5 : {
      DeclareAndCast(IGESGraph_HighLight,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolHighLight tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case  6 : {
      DeclareAndCast(IGESGraph_IntercharacterSpacing,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolIntercharacterSpacing tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case  7 : {
      DeclareAndCast(IGESGraph_LineFontDefPattern,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolLineFontDefPattern tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case  8 : {
      DeclareAndCast(IGESGraph_LineFontPredefined,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolLineFontPredefined tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case  9 : {
      DeclareAndCast(IGESGraph_LineFontDefTemplate,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolLineFontDefTemplate tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case 10 : {
      DeclareAndCast(IGESGraph_NominalSize,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolNominalSize tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case 11 : {
      DeclareAndCast(IGESGraph_Pick,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolPick tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case 12 : {
      DeclareAndCast(IGESGraph_TextDisplayTemplate,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolTextDisplayTemplate tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case 13 : {
      DeclareAndCast(IGESGraph_TextFontDef,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolTextFontDef tool;
      tool.OwnShared(anent,iter);
    }
      break;
    case 14 : {
      DeclareAndCast(IGESGraph_UniformRectGrid,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolUniformRectGrid tool;
      tool.OwnShared(anent,iter);
    }
      break;
    default : break;
  }
}


    IGESData_DirChecker  IGESGraph_GeneralModule::DirChecker
  (const Standard_Integer CN, const Handle(IGESData_IGESEntity)& ent) const 
{
  switch (CN) {
    case  1 : {
      DeclareAndCast(IGESGraph_Color,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolColor tool;
      return tool.DirChecker(anent);
    }
    case  2 : {
      DeclareAndCast(IGESGraph_DefinitionLevel,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolDefinitionLevel tool;
      return tool.DirChecker(anent);
    }
    case  3 : {
      DeclareAndCast(IGESGraph_DrawingSize,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolDrawingSize tool;
      return tool.DirChecker(anent);
    }
    case  4 : {
      DeclareAndCast(IGESGraph_DrawingUnits,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolDrawingUnits tool;
      return tool.DirChecker(anent);
    }
    case  5 : {
      DeclareAndCast(IGESGraph_HighLight,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolHighLight tool;
      return tool.DirChecker(anent);
    }
    case  6 : {
      DeclareAndCast(IGESGraph_IntercharacterSpacing,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolIntercharacterSpacing tool;
      return tool.DirChecker(anent);
    }
    case  7 : {
      DeclareAndCast(IGESGraph_LineFontDefPattern,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolLineFontDefPattern tool;
      return tool.DirChecker(anent);
    }
    case  8 : {
      DeclareAndCast(IGESGraph_LineFontPredefined,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolLineFontPredefined tool;
      return tool.DirChecker(anent);
    }
    case  9 : {
      DeclareAndCast(IGESGraph_LineFontDefTemplate,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolLineFontDefTemplate tool;
      return tool.DirChecker(anent);
    }
    case 10 : {
      DeclareAndCast(IGESGraph_NominalSize,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolNominalSize tool;
      return tool.DirChecker(anent);
    }
    case 11 : {
      DeclareAndCast(IGESGraph_Pick,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolPick tool;
      return tool.DirChecker(anent);
    }
    case 12 : {
      DeclareAndCast(IGESGraph_TextDisplayTemplate,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolTextDisplayTemplate tool;
      return tool.DirChecker(anent);
    }
    case 13 : {
      DeclareAndCast(IGESGraph_TextFontDef,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolTextFontDef tool;
      return tool.DirChecker(anent);
    }
    case 14 : {
      DeclareAndCast(IGESGraph_UniformRectGrid,anent,ent);
      if (anent.IsNull()) break;
      IGESGraph_ToolUniformRectGrid tool;
      return tool.DirChecker(anent);
    }
    default : break;
  }
  return IGESData_DirChecker();    // by default, no specific criterium
}


    void  IGESGraph_GeneralModule::OwnCheckCase
  (const Standard_Integer CN, const Handle(IGESData_IGESEntity)& ent,
   const Interface_ShareTool& shares, Handle(Interface_Check)& ach) const 
{
  switch (CN) {
    case  1 : {
      DeclareAndCast(IGESGraph_Color,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolColor tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case  2 : {
      DeclareAndCast(IGESGraph_DefinitionLevel,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolDefinitionLevel tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case  3 : {
      DeclareAndCast(IGESGraph_DrawingSize,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolDrawingSize tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case  4 : {
      DeclareAndCast(IGESGraph_DrawingUnits,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolDrawingUnits tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case  5 : {
      DeclareAndCast(IGESGraph_HighLight,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolHighLight tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case  6 : {
      DeclareAndCast(IGESGraph_IntercharacterSpacing,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolIntercharacterSpacing tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case  7 : {
      DeclareAndCast(IGESGraph_LineFontDefPattern,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolLineFontDefPattern tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case  8 : {
      DeclareAndCast(IGESGraph_LineFontPredefined,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolLineFontPredefined tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case  9 : {
      DeclareAndCast(IGESGraph_LineFontDefTemplate,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolLineFontDefTemplate tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case 10 : {
      DeclareAndCast(IGESGraph_NominalSize,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolNominalSize tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case 11 : {
      DeclareAndCast(IGESGraph_Pick,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolPick tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case 12 : {
      DeclareAndCast(IGESGraph_TextDisplayTemplate,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolTextDisplayTemplate tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case 13 : {
      DeclareAndCast(IGESGraph_TextFontDef,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolTextFontDef tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    case 14 : {
      DeclareAndCast(IGESGraph_UniformRectGrid,anent,ent);
      if (anent.IsNull()) return;
      IGESGraph_ToolUniformRectGrid tool;
      tool.OwnCheck(anent,shares,ach);
    }
      break;
    default : break;
  }
}


    Standard_Boolean  IGESGraph_GeneralModule::NewVoid
  (const Standard_Integer CN, Handle(Standard_Transient)& ent) const 
{
  switch (CN) {
    case  1 : ent = new IGESGraph_Color;		break;
    case  2 : ent = new IGESGraph_DefinitionLevel;	break;
    case  3 : ent = new IGESGraph_DrawingSize;		break;
    case  4 : ent = new IGESGraph_DrawingUnits;		break;
    case  5 : ent = new IGESGraph_HighLight;		break;
    case  6 : ent = new IGESGraph_IntercharacterSpacing;	break;
    case  7 : ent = new IGESGraph_LineFontDefPattern;	break;
    case  8 : ent = new IGESGraph_LineFontPredefined;	break;
    case  9 : ent = new IGESGraph_LineFontDefTemplate;	break;
    case 10 : ent = new IGESGraph_NominalSize;		break;
    case 11 : ent = new IGESGraph_Pick; 		break;
    case 12 : ent = new IGESGraph_TextDisplayTemplate;	break;
    case 13 : ent = new IGESGraph_TextFontDef;		break;
    case 14 : ent = new IGESGraph_UniformRectGrid;	break;
    default : return Standard_False;    // by default, Failure on Recognize
  }
  return Standard_True;
}


    void  IGESGraph_GeneralModule::OwnCopyCase
  (const Standard_Integer CN,
   const Handle(IGESData_IGESEntity)& entfrom,
   const Handle(IGESData_IGESEntity)& entto,
   Interface_CopyTool& TC) const 
{
  switch (CN) {
    case  1 : {
      DeclareAndCast(IGESGraph_Color,enfr,entfrom);
      DeclareAndCast(IGESGraph_Color,ento,entto);
      IGESGraph_ToolColor tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case  2 : {
      DeclareAndCast(IGESGraph_DefinitionLevel,enfr,entfrom);
      DeclareAndCast(IGESGraph_DefinitionLevel,ento,entto);
      IGESGraph_ToolDefinitionLevel tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case  3 : {
      DeclareAndCast(IGESGraph_DrawingSize,enfr,entfrom);
      DeclareAndCast(IGESGraph_DrawingSize,ento,entto);
      IGESGraph_ToolDrawingSize tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case  4 : {
      DeclareAndCast(IGESGraph_DrawingUnits,enfr,entfrom);
      DeclareAndCast(IGESGraph_DrawingUnits,ento,entto);
      IGESGraph_ToolDrawingUnits tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case  5 : {
      DeclareAndCast(IGESGraph_HighLight,enfr,entfrom);
      DeclareAndCast(IGESGraph_HighLight,ento,entto);
      IGESGraph_ToolHighLight tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case  6 : {
      DeclareAndCast(IGESGraph_IntercharacterSpacing,enfr,entfrom);
      DeclareAndCast(IGESGraph_IntercharacterSpacing,ento,entto);
      IGESGraph_ToolIntercharacterSpacing tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case  7 : {
      DeclareAndCast(IGESGraph_LineFontDefPattern,enfr,entfrom);
      DeclareAndCast(IGESGraph_LineFontDefPattern,ento,entto);
      IGESGraph_ToolLineFontDefPattern tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case  8 : {
      DeclareAndCast(IGESGraph_LineFontPredefined,enfr,entfrom);
      DeclareAndCast(IGESGraph_LineFontPredefined,ento,entto);
      IGESGraph_ToolLineFontPredefined tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case  9 : {
      DeclareAndCast(IGESGraph_LineFontDefTemplate,enfr,entfrom);
      DeclareAndCast(IGESGraph_LineFontDefTemplate,ento,entto);
      IGESGraph_ToolLineFontDefTemplate tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case 10 : {
      DeclareAndCast(IGESGraph_NominalSize,enfr,entfrom);
      DeclareAndCast(IGESGraph_NominalSize,ento,entto);
      IGESGraph_ToolNominalSize tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case 11 : {
      DeclareAndCast(IGESGraph_Pick,enfr,entfrom);
      DeclareAndCast(IGESGraph_Pick,ento,entto);
      IGESGraph_ToolPick tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case 12 : {
      DeclareAndCast(IGESGraph_TextDisplayTemplate,enfr,entfrom);
      DeclareAndCast(IGESGraph_TextDisplayTemplate,ento,entto);
      IGESGraph_ToolTextDisplayTemplate tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case 13 : {
      DeclareAndCast(IGESGraph_TextFontDef,enfr,entfrom);
      DeclareAndCast(IGESGraph_TextFontDef,ento,entto);
      IGESGraph_ToolTextFontDef tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    case 14 : {
      DeclareAndCast(IGESGraph_UniformRectGrid,enfr,entfrom);
      DeclareAndCast(IGESGraph_UniformRectGrid,ento,entto);
      IGESGraph_ToolUniformRectGrid tool;
      tool.OwnCopy(enfr,ento,TC);
    }
      break;
    default : break;
  }
}


    Standard_Integer  IGESGraph_GeneralModule::CategoryNumber
  (const Standard_Integer CN, const Handle(Standard_Transient)& ,
   const Interface_ShareTool& ) const
{
  return Interface_Category::Number("Drawing");
}
