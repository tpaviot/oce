// Created on: 1995-03-28
// Created by: Yves FRICAUD
// Copyright (c) 1995-1999 Matra Datavision
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



#include <BRepTools_Substitution.ixx>
#include <TopoDS.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopTools_DataMapIteratorOfDataMapOfShapeListOfShape.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <BRep_Builder.hxx>
#include <Standard_ConstructionError.hxx>
#include <BRep_Tool.hxx>

//=======================================================================
//function : BRepTools_Substitution
//purpose  : 
//=======================================================================

BRepTools_Substitution::BRepTools_Substitution()
{}

//=======================================================================
//function : Clear
//purpose  : 
//=======================================================================

void BRepTools_Substitution::Clear()
{
  myMap.Clear();
}

//=======================================================================
//function : Substitute
//purpose  : 
//=======================================================================

void BRepTools_Substitution::Substitute(const TopoDS_Shape&         OS, 
					const TopTools_ListOfShape& NS)
{
  Standard_ConstructionError_Raise_if 
    (IsCopied(OS),"BRepTools_CutClue::Substitute");
  myMap.Bind(OS,NS);
}


//=======================================================================
//function : Build
//purpose  : 
//=======================================================================

void BRepTools_Substitution::Build(const TopoDS_Shape& S)
{
  if (IsCopied(S)) return;

  BRep_Builder     B;
  TopoDS_Iterator  iteS (S.Oriented(TopAbs_FORWARD));
  Standard_Boolean IsModified  = Standard_False;
  Standard_Boolean HasSubShape = Standard_False;

  //------------------------------------------
  // look S is modified and build subshapes.
  //------------------------------------------
  for (; iteS.More(); iteS.Next()) {
    const TopoDS_Shape& SS = iteS.Value();
    Build (SS);
    if (IsCopied(SS)) {
      IsModified = Standard_True;
    }
  }

  TopoDS_Shape NewS = S.Oriented(TopAbs_FORWARD);
  if (IsModified) {
    //----------------------------------------
    // Rebuild S.
    //------------------------------------------
    NewS.EmptyCopy();

    if (NewS.ShapeType() == TopAbs_EDGE) {
      Standard_Real f,l;
      BRep_Tool::Range(TopoDS::Edge(S),f,l);
      B.Range(TopoDS::Edge(NewS),f,l);
    }
    
    iteS.Initialize(S.Oriented(TopAbs_FORWARD));
    //------------------------------------------
    // Add the copy of subshapes of S to NewS.
    //------------------------------------------
    for ( ;iteS.More(); iteS.Next()) {
      TopAbs_Orientation          OS = iteS.Value().Orientation();
      TopTools_ListOfShape L;
      L  = myMap(iteS.Value());
      TopTools_ListIteratorOfListOfShape iteL(L);

      for ( ; iteL.More(); iteL.Next()){
	const TopoDS_Shape NSS = iteL.Value();
	//------------------------------------------
	// Rebuild NSS and add its copy to NewS.
	//------------------------------------------
	Build(NSS);      

	const TopTools_ListOfShape&  NL = myMap(NSS);
	TopAbs_Orientation NewOr = TopAbs::Compose(OS,NSS.Orientation());		
	TopTools_ListIteratorOfListOfShape iteNL(NL);

	for ( ; iteNL.More(); iteNL.Next()){
	  B.Add (NewS,iteNL.Value().Oriented(NewOr));
	  HasSubShape = Standard_True;
	}
      }
    }
    if (!HasSubShape) {
      if (NewS.ShapeType() == TopAbs_WIRE  || NewS.ShapeType() == TopAbs_SHELL ||
	  NewS.ShapeType() == TopAbs_SOLID || NewS.ShapeType() == TopAbs_COMPOUND)
	//----------------------------------------------------------------
	// Wire,Solid,Shell,Compound mut have subshape else they disapear
	//---------------------------------------------------------------	
	NewS.Nullify();
    }
  }
  TopTools_ListOfShape L;
  //-------------------------------------------------------
  // NewS has the same orientation than S in its ancestors
  // so NewS is bound with orientation FORWARD.
  //-------------------------------------------------------
  if (!NewS.IsNull()) L.Append(NewS.Oriented(TopAbs_FORWARD));
  Substitute(S, L);
}


//=======================================================================
//function : IsCopied
//purpose  : 
//=======================================================================

Standard_Boolean BRepTools_Substitution::IsCopied(const TopoDS_Shape& S) const 
{
  if (myMap.IsBound(S)) {
    if (myMap (S).IsEmpty()) return Standard_True;
    else
      return !S.IsSame(myMap(S).First());
  }
  else
    return Standard_False;
}


//=======================================================================
//function : Copy
//purpose  : 
//=======================================================================

const TopTools_ListOfShape& BRepTools_Substitution::Copy (const TopoDS_Shape& S) 
     const 
{
  Standard_NoSuchObject_Raise_if(!IsCopied(S),"BRepTools_Substitution::Copy");
  return myMap(S);
}

