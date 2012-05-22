// Created on: 1994-12-09
// Created by: Jacques GOUSSARD
// Copyright (c) 1994-1999 Matra Datavision
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



#include <BRepBuilderAPI_NurbsConvert.ixx>
#include <BRepLib.hxx>
#include <TopAbs.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopTools_MapOfShape.hxx>
#include <TopExp_Explorer.hxx>
#include <BRep_Builder.hxx>
#include <BRepTools_NurbsConvertModification.hxx>
//#include <gp.hxx>


//=======================================================================
//function : BRepBuilderAPI_NurbsConvert
//purpose  : 
//=======================================================================

BRepBuilderAPI_NurbsConvert::BRepBuilderAPI_NurbsConvert () 
     
{
  myModification = new BRepTools_NurbsConvertModification();
}

//=======================================================================
//function : BRepBuilderAPI_NurbsConvert
//purpose  : 
//=======================================================================

BRepBuilderAPI_NurbsConvert::BRepBuilderAPI_NurbsConvert (const TopoDS_Shape& S,
					    const Standard_Boolean Copy) 
     
{
  myModification = new BRepTools_NurbsConvertModification();
  Perform(S,Copy);
}

//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================

void BRepBuilderAPI_NurbsConvert::Perform(const TopoDS_Shape& S,
				   const Standard_Boolean Copy)
{
  Handle(BRepTools_NurbsConvertModification) theModif = 
    Handle(BRepTools_NurbsConvertModification)::DownCast(myModification);
  DoModif(S,myModification);
}



