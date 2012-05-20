// Created on: 1993-05-04
// Created by: Yves FRICAUD
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



#include <MAT_Arc.ixx>
#include <Standard_DomainError.hxx>

//========================================================================
// function:
// purpose :
//========================================================================
MAT_Arc::MAT_Arc (const Standard_Integer      ArcIndex, 
		  const Standard_Integer      GeomIndex, 
		  const Handle(MAT_BasicElt)& FirstElement, 
		  const Handle(MAT_BasicElt)& SecondElement)
 : arcIndex(ArcIndex),
   geomIndex(GeomIndex),
   firstArcLeft  (0),
   firstArcRight (0),
   secondArcRight (0),
   secondArcLeft (0)   
{
  firstElement  = FirstElement;
  secondElement = SecondElement;
}

//========================================================================
// function: Index
// purpose :
//========================================================================
Standard_Integer  MAT_Arc::Index() const
{
  return arcIndex;
}

//========================================================================
// function: GeomIndex
// purpose :
//========================================================================
Standard_Integer  MAT_Arc::GeomIndex() const
{
  return geomIndex;
}

//========================================================================
// function: FirstElement
// purpose :
//========================================================================
Handle(MAT_BasicElt)  MAT_Arc::FirstElement() const
{
  return firstElement;
}

//========================================================================
// function: SecondElement
// purpose :
//========================================================================
Handle(MAT_BasicElt)  MAT_Arc::SecondElement() const
{
  return secondElement;
}

//========================================================================
// function: FirstNode
// purpose :
//========================================================================
Handle(MAT_Node)  MAT_Arc::FirstNode() const
{
  return firstNode; 
}

//========================================================================
// function: SecondNode
// purpose :
//========================================================================
Handle(MAT_Node)  MAT_Arc::SecondNode() const
{
  return secondNode;
}

//========================================================================
// function: TheOtherNode
// purpose :
//========================================================================
Handle(MAT_Node) MAT_Arc::TheOtherNode(const Handle(MAT_Node)& aNode)const 
{
  if (FirstNode() == aNode)
    return SecondNode();
  else if (SecondNode() == aNode)
    return FirstNode();
  else {
    Standard_DomainError::Raise("MAT_Arc::TheOtherNode");
    return aNode;
  }
}

//========================================================================
// function: HasNeighbour
// purpose :
//========================================================================
Standard_Boolean MAT_Arc::HasNeighbour(const Handle(MAT_Node)& aNode,
				       const MAT_Side          aSide ) const
{
  if (aSide == MAT_Left) {
//    if (aNode == FirstNode())  return (!firstArcLeft  == NULL);
    if (aNode == FirstNode())  return (!firstArcLeft  == 0);
//    if (aNode == SecondNode()) return (!secondArcLeft == NULL);
    if (aNode == SecondNode()) return (!secondArcLeft == 0);
  }
  else {
//    if (aNode == FirstNode())  return (!firstArcRight  == NULL);
    if (aNode == FirstNode())  return (!firstArcRight  == 0);
//    if (aNode == SecondNode()) return (!secondArcRight == NULL);
    if (aNode == SecondNode()) return (!secondArcRight == 0);
  }
  Standard_DomainError::Raise("MAT_Arc::HasNeighbour");
  return Standard_False;
}

//========================================================================
// function: Neighbour
// purpose :
//========================================================================
Handle(MAT_Arc)  MAT_Arc::Neighbour(const Handle(MAT_Node)& aNode,
				    const MAT_Side          aSide ) 
const

{
  if (aSide == MAT_Left) {
    if (aNode == FirstNode())  return (MAT_Arc*)firstArcLeft;
    if (aNode == SecondNode()) return (MAT_Arc*)secondArcLeft;
  }
  else {
    if (aNode == FirstNode())  return (MAT_Arc*)firstArcRight;
    if (aNode == SecondNode()) return (MAT_Arc*)secondArcRight;
  }
  Standard_DomainError::Raise("MAT_Arc::Neighbour");
  return (MAT_Arc*)firstArcLeft;
}

//========================================================================
// function: SetIndex
// purpose :
//========================================================================
void  MAT_Arc::SetIndex(const Standard_Integer anInteger)
{
  arcIndex = anInteger;
}

//========================================================================
// function: SetGeomIndex
// purpose :
//========================================================================
void  MAT_Arc::SetGeomIndex(const Standard_Integer anInteger)
{
  geomIndex = anInteger;
}

//========================================================================
// function: SetFirstElement
// purpose :
//========================================================================
void  MAT_Arc::SetFirstElement(const Handle(MAT_BasicElt)& aBasicElt)
{
  firstElement = aBasicElt;
}

//========================================================================
// function: SetSecondElement
// purpose :
//========================================================================
void  MAT_Arc::SetSecondElement(const Handle(MAT_BasicElt)& aBasicElt)
{
  secondElement = aBasicElt;
}

//========================================================================
// function: SetFirstNode
// purpose :
//========================================================================
void  MAT_Arc::SetFirstNode(const Handle(MAT_Node)& aNode)
{
  firstNode = aNode;
}

//========================================================================
// function: SetSecondNode
// purpose :
//========================================================================
void  MAT_Arc::SetSecondNode(const Handle_MAT_Node& aNode)
{
  secondNode = aNode;
}

//========================================================================
// function: SetFirstArc
// purpose :
//========================================================================
void  MAT_Arc::SetFirstArc(const MAT_Side aSide ,
			   const Handle(MAT_Arc)& anArc)
{
  if (aSide == MAT_Left) 
    firstArcLeft  = anArc.operator->();
  else
    firstArcRight = anArc.operator->();
}

//========================================================================
// function: SetSecondArc
// purpose :
//========================================================================
void  MAT_Arc::SetSecondArc(const MAT_Side aSide ,
			    const Handle(MAT_Arc)& anArc)
{ 
  if (aSide == MAT_Left) 
    secondArcLeft = anArc.operator->();
  else
    secondArcRight = anArc.operator->();
}

//========================================================================
// function: SetNeighbour
// purpose :
//========================================================================
void  MAT_Arc::SetNeighbour(const MAT_Side aSide, 
			    const Handle(MAT_Node)& aNode, 
			    const Handle(MAT_Arc)& anArc)
{
  if (aSide == MAT_Left) {
    if (aNode == FirstNode())  
      firstArcLeft  = anArc.operator->();
    else if (aNode == SecondNode())
      secondArcLeft = anArc.operator->();
    else
     Standard_DomainError::Raise("MAT_Arc::SetNeighbour"); 
  }
  else {
    if (aNode == FirstNode())  
      firstArcRight  = anArc.operator->();
    else if (aNode == SecondNode())
      secondArcRight = anArc.operator->();
    else
      Standard_DomainError::Raise("MAT_Arc::SetNeighbour");
  }
}











