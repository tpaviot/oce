// File:	DDF_BrowserCommands.cxx
//      	-----------------------
// Author:	DAUTRY Philippe
//		<fid@fox.paris1.matra-dtv.fr>
// Copyright:	Matra Datavision 1997

// Version:	0.0
// History:	Version	Date		Purpose
//		0.0	Oct  3 1997	Creation

#include <stdio.h>

#include <DDF.hxx>
#include <DDF_Browser.hxx>
#include <DDF_Data.hxx>

#include <Draw.hxx>
#include <Draw_Appli.hxx>
#include <Draw_Drawable3D.hxx>
#include <Draw_Interpretor.hxx>

#include <TDF_Label.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_AttributeIterator.hxx>
#include <TDF_Tool.hxx>

#include <TCollection_AsciiString.hxx>
#include <TCollection_HAsciiString.hxx>
#ifdef WNT
#include <stdio.h>
#endif










// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




//=======================================================================
//function : BrowserCommands
//purpose  : 
//=======================================================================

void DDF::BrowserCommands (Draw_Interpretor& theCommands) 
{
/*
  static Standard_Boolean done = Standard_False;
  if (done) return;
  done = Standard_True;

  const char* g = "DF browser commands";

  theCommands.Add
    ("DFBrowse",
     "Creates a browser on a df: DFBrowse dfname [browsername]",
     __FILE__, DFBrowse, g);

  theCommands.Add
    ("DFOpenLabel",
     "DON'T USE THIS COMMAND RESERVED TO THE BROWSER!\nReturns the list of sub-label entries: DFOpenLabel browsername [label]",
     __FILE__, DFOpenLabel, g);

  theCommands.Add
    ("DFOpenAttributeList",
     "DON'T USE THIS COMMAND RESERVED TO THE BROWSER!\nReturns the attribute list of a label: DFOpenLabel browsername label",
     __FILE__, DFOpenAttributeList, g);

  theCommands.Add
    ("DFOpenAttribute",
     "DON'T USE THIS COMMAND RESERVED TO THE BROWSER!\nReturns the reference list of an attribute: DFOpenLabel browsername attributeindex",
     __FILE__, DFOpenAttribute, g);
#if 0
  theCommands.Add
    ("DFDisplayInfo",
     "DON'T USE THIS COMMAND RESERVED TO THE BROWSER!\nReturns information about an attribute, a df or a label: DFDisplayInfo {#} | {browsername [label]}",
     __FILE__, DFDisplayInfo, g);
#endif
*/
}
