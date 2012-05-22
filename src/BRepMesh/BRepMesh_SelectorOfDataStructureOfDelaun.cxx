// Created on: 1993-06-01
// Created by: Didier PIFFAULT
// Copyright (c) 1993-1999 Matra Datavision
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


#include <BRepMesh_SelectorOfDataStructureOfDelaun.ixx>
#include <BRepMesh_PairOfIndex.hxx>

//=======================================================================
//function : BRepMesh_SelectorOfDataStructureOfDelaun
//purpose  : 
//=======================================================================
BRepMesh_SelectorOfDataStructureOfDelaun::BRepMesh_SelectorOfDataStructureOfDelaun()
: myNodes(10, new NCollection_IncAllocator),
myLinks(10, new NCollection_IncAllocator),
myElements(10, new NCollection_IncAllocator),
myFrontier(10, new NCollection_IncAllocator)

{}

BRepMesh_SelectorOfDataStructureOfDelaun::BRepMesh_SelectorOfDataStructureOfDelaun(const Handle(BRepMesh_DataStructureOfDelaun)& theMesh)
: myMesh(theMesh),
myNodes(10, myMesh->Allocator()),
myLinks(10, myMesh->Allocator()),
myElements(10, myMesh->Allocator()),
myFrontier(10, myMesh->Allocator())
{}

void  BRepMesh_SelectorOfDataStructureOfDelaun::Initialize(const Handle(BRepMesh_DataStructureOfDelaun)& theMesh)
{
  myMesh=theMesh;
  myNodes.Clear();
  myLinks.Clear();
  myElements.Clear();
  myFrontier.Clear();
}

//=======================================================================
//function : NeighboursOfNode
//purpose  : 
//=======================================================================
void  BRepMesh_SelectorOfDataStructureOfDelaun::NeighboursOf(const BRepMesh_Vertex& theNode)
{
  NeighboursOfNode(myMesh->IndexOf(theNode));
}

void  BRepMesh_SelectorOfDataStructureOfDelaun::NeighboursOfNode(const Standard_Integer indexNode)
{
  BRepMesh_ListOfInteger::Iterator itL(myMesh->LinkNeighboursOf(indexNode));

  for (; itL.More(); itL.Next()) {
    const BRepMesh_PairOfIndex& aPair = myMesh->ElemConnectedTo(itL.Value());
    for(Standard_Integer j = 1, jn = aPair.Extent(); j <= jn; j++)
      myElements.Add(aPair.Index(j));
  }
}

//=======================================================================
//function : NeighboursOfLink
//purpose  : 
//=======================================================================
void  BRepMesh_SelectorOfDataStructureOfDelaun::NeighboursOf(const BRepMesh_Edge& theLink)
{
  NeighboursOfNode(theLink.FirstNode());
  NeighboursOfNode(theLink.LastNode());
}

void  BRepMesh_SelectorOfDataStructureOfDelaun::NeighboursOfLink(const Standard_Integer indexLink)
{
  NeighboursOf(myMesh->GetLink(indexLink));
}

//=======================================================================
//function : NeighboursOfElement
//purpose  : by edge and by vertices
//=======================================================================
void  BRepMesh_SelectorOfDataStructureOfDelaun::NeighboursOf(const BRepMesh_Triangle& theElem)
{
  Standard_Integer v1, v2, v3, ev;
  Standard_Boolean o1, o2, o3;
  theElem.Edges(v1, v3, ev, o1, o2, o3);
  v2=myMesh->GetLink(v1).LastNode();
  v1=myMesh->GetLink(v1).FirstNode();
  ev=myMesh->GetLink(v3).LastNode();
  if (v1!=ev && v2!=ev) v3=ev;
  else v3=myMesh->GetLink(v3).FirstNode();
  NeighboursOfNode(v1);
  NeighboursOfNode(v2);
  NeighboursOfNode(v3);
}

void  BRepMesh_SelectorOfDataStructureOfDelaun::NeighboursOfElement(const Standard_Integer indexElem)
{
  NeighboursOf(myMesh->GetElement(indexElem));
}

//=======================================================================
//function : NeighboursByEdgeOf
//purpose  : Neighbours Of an element only by edge
//=======================================================================
void  BRepMesh_SelectorOfDataStructureOfDelaun::NeighboursByEdgeOf(const BRepMesh_Triangle& theElem)
{
  Standard_Integer e[3], iEd;
  Standard_Boolean o1, o2, o3;
  theElem.Edges(e[0], e[1], e[2], o1, o2, o3);

  for (iEd=0; iEd<3; iEd++) {
    const BRepMesh_PairOfIndex& aPair = myMesh->ElemConnectedTo(e[iEd]);
    for(Standard_Integer j = 1, jn = aPair.Extent(); j <= jn; j++)
      myElements.Add(aPair.Index(j));
  }
}


//=======================================================================
//function : NeighboursOfSelector
//purpose  : 
//=======================================================================
void  BRepMesh_SelectorOfDataStructureOfDelaun::NeighboursOf(const BRepMesh_SelectorOfDataStructureOfDelaun& /*theSelector*/)
{}

//=======================================================================
//function : AddNeighbours
//purpose  : 
//=======================================================================
void  BRepMesh_SelectorOfDataStructureOfDelaun::AddNeighbours()
{}

//=======================================================================
//function : Nodes
//purpose  : 
//=======================================================================
const BRepMesh_MapOfInteger& BRepMesh_SelectorOfDataStructureOfDelaun::Nodes()const
{return myNodes;}

//=======================================================================
//function : Links
//purpose  : 
//=======================================================================
const BRepMesh_MapOfInteger& BRepMesh_SelectorOfDataStructureOfDelaun::Links()const
{return myLinks;}

//=======================================================================
//function : Elements
//purpose  : 
//=======================================================================
const BRepMesh_MapOfInteger& BRepMesh_SelectorOfDataStructureOfDelaun::Elements()const
{return myElements;}

//=======================================================================
//function : FrontierLinks
//purpose  : 
//=======================================================================
const BRepMesh_MapOfInteger& BRepMesh_SelectorOfDataStructureOfDelaun::FrontierLinks()const
{return myFrontier;}

