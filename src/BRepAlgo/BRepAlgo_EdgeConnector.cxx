// Created on: 1997-08-22
// Created by: Prestataire Mary FABIEN
// Copyright (c) 1997-1999 Matra Datavision
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



#include <BRepAlgo_EdgeConnector.ixx>

#include <TopoDS_Shape.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TopoDS_Wire.hxx>
#include <BRep_Builder.hxx>
#include <TopOpeBRepBuild_ShapeSet.hxx>
#include <TopOpeBRepBuild_BlockIterator.hxx>
#include <TopOpeBRepBuild_BlockBuilder.hxx>
#include <BRepAlgo_DataMapOfShapeBoolean.hxx>

//=======================================================================
//function : Create
//purpose  : 
//=======================================================================

BRepAlgo_EdgeConnector::BRepAlgo_EdgeConnector()
:myIsDone(Standard_False)
{
  myListeOfEdge.Clear();
}

//=======================================================================
//function : Add
//purpose  : 
//=======================================================================

void BRepAlgo_EdgeConnector::Add(const TopoDS_Edge& e)
{
  if(e.IsNull()) return;
  myListeOfEdge.Append(e);
}

//=======================================================================
//function : Add
//purpose  : 
//=======================================================================

void BRepAlgo_EdgeConnector::Add(TopTools_ListOfShape& LOEdge)
{
  if(LOEdge.IsEmpty()) return;
  myListeOfEdge.Append(LOEdge);
}

//=======================================================================
//function : AddStart
//purpose  : 
//=======================================================================

void BRepAlgo_EdgeConnector::AddStart(const TopoDS_Shape& e)
{
  if(e.IsNull()) return;
  myListeOfStartEdge.Append(e);
}

//=======================================================================
//function : AddStart
//purpose  : 
//=======================================================================

void BRepAlgo_EdgeConnector::AddStart(TopTools_ListOfShape& LOEdge)
{
  if(LOEdge.IsEmpty()) return;
  myListeOfStartEdge.Append(LOEdge);
}

//=======================================================================
//function : ClearStartElement
//purpose  : 
//=======================================================================

void BRepAlgo_EdgeConnector::ClearStartElement()
{
  myListeOfStartEdge.Clear();
}

//=======================================================================
//function : MakeBlock
//purpose  : 
//=======================================================================

TopTools_ListOfShape& BRepAlgo_EdgeConnector::MakeBlock()
{
  Standard_Boolean b;
  if(myListeOfStartEdge.IsEmpty()) return myListeOfStartEdge;
  TopOpeBRepBuild_ShapeSet SS(TopAbs_VERTEX);
  myResultMap.Clear();
  myResultList.Clear();
  TopTools_ListIteratorOfListOfShape it(myListeOfEdge);
  for(;it.More();it.Next()) {
    const TopoDS_Shape& edge = it.Value();
    SS.AddElement(edge);
  }
  it.Initialize(myListeOfStartEdge);
  for(;it.More();it.Next()) {
    const TopoDS_Shape& edge = it.Value();
    SS.AddStartElement(edge);
  }
  myBlockB.MakeBlock(SS);
  BRep_Builder WireB;
  for(myBlockB.InitBlock();myBlockB.MoreBlock();myBlockB.NextBlock()) {
//#ifndef DEB
    TopOpeBRepBuild_BlockIterator BI = myBlockB.BlockIterator();
//#else
//    TopOpeBRepBuild_BlockIterator& BI = myBlockB.BlockIterator();
//#endif
    TopoDS_Wire W;
    WireB.MakeWire(W);
    for(BI.Initialize();BI.More();BI.Next()) {
      const TopoDS_Shape& CurrentE = myBlockB.Element(BI);
      WireB.Add(W, CurrentE);
    }
    b = myBlockB.CurrentBlockIsRegular();
    myResultMap.Bind(W, b);
    myResultList.Append(W);
  }
  Done();
  return myResultList;
}

//=======================================================================
//function : IsWire
//purpose  : 
//=======================================================================

Standard_Boolean BRepAlgo_EdgeConnector::IsWire(const TopoDS_Shape& S)
{
  if(!myResultMap.IsBound(S)) {
    return Standard_False;
  }
  Standard_Boolean b = Standard_False;
  myBlockB.InitBlock();
  TopTools_ListIteratorOfListOfShape LI(myResultList);
  for(;myBlockB.MoreBlock();myBlockB.NextBlock(),LI.Next()) {
    if(S == LI.Value()) {
      b = myBlockB.CurrentBlockIsRegular();
      break;
    }
  }
  return b;
}

//=======================================================================
//function : IsDone
//purpose  : 
//=======================================================================


Standard_Boolean BRepAlgo_EdgeConnector::IsDone() const
{
  return myIsDone;
}

//=======================================================================
//function : Done
//purpose  : 
//=======================================================================


void BRepAlgo_EdgeConnector::Done()
{
  myIsDone = Standard_True;
}

