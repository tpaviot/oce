// Created on: 1993-03-11
// Created by: Jean Yves LEBEY
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


#include <TopOpeBRepBuild_BlockBuilder.ixx>
#include <Standard_Failure.hxx>

//=======================================================================
//function : TopOpeBRepBuild_BlockBuilder
//purpose  : 
//=======================================================================

TopOpeBRepBuild_BlockBuilder::TopOpeBRepBuild_BlockBuilder()
:myIsDone(Standard_False)
{
}

//=======================================================================
//function : TopOpeBRepBuild_BlockBuilder
//purpose  : 
//=======================================================================

TopOpeBRepBuild_BlockBuilder::TopOpeBRepBuild_BlockBuilder 
(TopOpeBRepBuild_ShapeSet& SS)
:myIsDone(Standard_False)
{
  MakeBlock(SS);
}

//=======================================================================
//function : MakeBlock
//purpose  : 
//=======================================================================

void TopOpeBRepBuild_BlockBuilder::MakeBlock(TopOpeBRepBuild_ShapeSet& SS)
{
  // Compute the set of connexity blocks of elements of element set SS
  //
  // Logic : 
  // - A block is a set of connex elements of SS
  // - We assume that any element of SS appears in only 1 connexity block.
  //
  // Implementation :
  // - All the elements of all the blocks are stored in map myOrientedShapeMap(M).
  // - A connexity block is a segment [f,l] of element indices of M.
  // - myBlocks is a sequence of integer; each integer is the index of the 
  //   first element (in M) of a connexity block.
  // - Bounds [f,l] of a connexity block are : 
  //    f = myBlocks(i)
  //    l = myBlocks(i+1) - 1

  myOrientedShapeMap.Clear();
  myOrientedShapeMapIsValid.Clear();
  myBlocks.Clear();
  myBlocksIsRegular.Clear();
  
  Standard_Boolean IsRegular;
  Standard_Integer CurNei;
  Standard_Integer Mextent;
  Standard_Integer Eindex;

  for (SS.InitStartElements();SS.MoreStartElements();SS.NextStartElement()) {

    const TopoDS_Shape& E = SS.StartElement(); 
    Mextent = myOrientedShapeMap.Extent();
    Eindex = AddElement(E); 

    // E = current element of the element set SS
    // Mextent = index of last element stored in map M, before E is added. 
    // Eindex  = index of E added to M : Eindex > Mextent => E is new in M

    Standard_Boolean EnewinM = (Eindex > Mextent);
    if (EnewinM) {

      // make a new block starting at element Eindex
      myBlocks.Append(Eindex);
      IsRegular = Standard_True; CurNei = 0;
      // put in current block all the elements connex to E :
      // while an element E has been added to M
      //    - compute neighbours of E : N(E)
      //    - add each element N of N(E) to M

      Mextent = myOrientedShapeMap.Extent();
      Standard_Boolean searchneighbours = (Eindex <= Mextent);
      while (searchneighbours) {

	// E = element of M on which neighbours must be searched
	// first step : Eindex = index of starting element of SS
	// next steps : Eindex = index of neighbours of starting element of SS 
	const TopoDS_Shape& E1 = myOrientedShapeMap(Eindex);
	CurNei = SS.MaxNumberSubShape(E1);
	Standard_Boolean condregu = Standard_True;
	if (CurNei > 2) condregu = Standard_False;
	IsRegular = IsRegular && condregu;
	// compute neighbours of E : add them to M to increase M.Extent().
	SS.InitNeighbours(E1);

	for (; SS.MoreNeighbours(); SS.NextNeighbour()) {
	  const TopoDS_Shape& N = SS.Neighbour();
	  AddElement(N);
	}
	
	Eindex++;
	Mextent = myOrientedShapeMap.Extent();
	searchneighbours = (Eindex <= Mextent);
	
      } // while (searchneighbours)
      Standard_Integer iiregu = IsRegular ? 1 : 0;
      myBlocksIsRegular.Append(iiregu);      
    } // if (EnewinM)
  } // for ()
  
  // To value the l bound of the last connexity block created above,
  // we create an artificial block of value = myOrientedShapeMap.Extent() + 1
  // The real number of connexity blocks is myBlocks.Length() - 1
  Mextent = myOrientedShapeMap.Extent();
  myBlocks.Append(Mextent + 1);
  myIsDone = Standard_True;

#if 0
// version seche
  myOrientedShapeMap.Clear();
  myOrientedShapeMapIsValid.Clear();
  myBlocks.Clear();
  while (SS.MoreStartElements()) {
    Standard_Integer last = myOrientedShapeMap.Extent();
    Standard_Integer index =AddElement(SS.StartElement());
    if (index > last) {
      myBlocks.Append(index);
      while (index <= myOrientedShapeMap.Extent()) {
	for (SS.InitNeighbours(myOrientedShapeMap(index));
	     SS.MoreNeighbours();
	     SS.NextNeighbour()) {
	 AddElement(SS.Neighbour());
	}
	index++;
      }
    }
    SS.NextStartElement();
  }
  myBlocks.Append(myOrientedShapeMap.Extent()+1);
  myBlockIndex = 1;
#endif
}

//=======================================================================
//function : InitBlock
//purpose  : 
//=======================================================================

void TopOpeBRepBuild_BlockBuilder::InitBlock()
{
  myBlockIndex = 1;
}

//=======================================================================
//function : MoreBlock
//purpose  : 
//=======================================================================

Standard_Boolean TopOpeBRepBuild_BlockBuilder::MoreBlock() const
{
  // the length of myBlocks is 1 + number of connexity blocks
  Standard_Integer l =  myBlocks.Length();
  Standard_Boolean b = (myBlockIndex < l);
  return b;
}

//=======================================================================
//function : NextBlock
//purpose  : 
//=======================================================================

void TopOpeBRepBuild_BlockBuilder::NextBlock()
{
  myBlockIndex++;
}

//=======================================================================
//function : BlockIterator
//purpose  : 
//=======================================================================

TopOpeBRepBuild_BlockIterator TopOpeBRepBuild_BlockBuilder::BlockIterator() const
{
  Standard_Integer lower = myBlocks(myBlockIndex);
  Standard_Integer upper = myBlocks(myBlockIndex+1)-1;
  return TopOpeBRepBuild_BlockIterator(lower,upper);
}

//=======================================================================
//function : Element
//purpose  : 
//=======================================================================

const TopoDS_Shape& TopOpeBRepBuild_BlockBuilder::Element 
(const TopOpeBRepBuild_BlockIterator& BI) const
{
  Standard_Boolean isbound = BI.More();
  if (!isbound) Standard_Failure::Raise("OutOfRange");

  Standard_Integer index = BI.Value();
  const TopoDS_Shape& E = myOrientedShapeMap(index);
  return E;
} 

const TopoDS_Shape& TopOpeBRepBuild_BlockBuilder::Element 
(const Standard_Integer index) const
{
  Standard_Boolean isbound = myOrientedShapeMapIsValid.IsBound(index);
  if (!isbound) Standard_Failure::Raise("OutOfRange");

  const TopoDS_Shape& E = myOrientedShapeMap(index);
  return E;
} 

Standard_Integer TopOpeBRepBuild_BlockBuilder::Element 
(const TopoDS_Shape& E) const
{
  Standard_Boolean isbound = myOrientedShapeMap.Contains(E);
  if (!isbound) Standard_Failure::Raise("OutOfRange");

  Standard_Integer I = myOrientedShapeMap.FindIndex(E);
  return I;
}

//=======================================================================
//function : ElementIsValid
//purpose  : 
//=======================================================================

Standard_Boolean TopOpeBRepBuild_BlockBuilder::ElementIsValid
(const TopOpeBRepBuild_BlockIterator& BI) const 
{  
  Standard_Boolean isbound = BI.More();
  if (!isbound) return Standard_False;

  Standard_Integer Sindex = BI.Value();
  Standard_Integer isb = myOrientedShapeMapIsValid.Find(Sindex);
  Standard_Boolean isvalid = (isb == 1)? Standard_True: Standard_False;
  
  return isvalid;
}

Standard_Boolean TopOpeBRepBuild_BlockBuilder::ElementIsValid
(const Standard_Integer Sindex) const
{  
  Standard_Boolean isbound = myOrientedShapeMapIsValid.IsBound(Sindex);
  if (!isbound) return Standard_False;

  Standard_Integer isb = myOrientedShapeMapIsValid.Find(Sindex);
  Standard_Boolean isvalid = (isb == 1)? Standard_True: Standard_False;
  
  return isvalid;
}

//=======================================================================
//function : AddElement
//purpose  : 
//=======================================================================

Standard_Integer TopOpeBRepBuild_BlockBuilder::AddElement(const TopoDS_Shape& S) 
{
  Standard_Integer Sindex = myOrientedShapeMap.Add(S);
  myOrientedShapeMapIsValid.Bind(Sindex, 1);

  return Sindex;
}

//=======================================================================
//function : SetValid
//purpose  : 
//=======================================================================

void TopOpeBRepBuild_BlockBuilder::SetValid
(const TopOpeBRepBuild_BlockIterator& BI,
 const Standard_Boolean isvalid)
{
  Standard_Boolean isbound = BI.More();
  if (!isbound) return;

  Standard_Integer Sindex = BI.Value();
  Standard_Integer i = (isvalid) ? 1 : 0;
  myOrientedShapeMapIsValid.Bind(Sindex,i);
}

void TopOpeBRepBuild_BlockBuilder::SetValid
(const Standard_Integer Sindex,
 const Standard_Boolean isvalid)
{
  Standard_Boolean isbound = myOrientedShapeMapIsValid.IsBound(Sindex);
  if (!isbound) return;

  Standard_Integer i = (isvalid) ? 1 : 0;
  myOrientedShapeMapIsValid.Bind(Sindex,i);
}

//=======================================================================
//function : CurrentBlockIsRegular
//purpose  : 
//=======================================================================

Standard_Boolean TopOpeBRepBuild_BlockBuilder::CurrentBlockIsRegular()
{
  Standard_Boolean b = Standard_False;
  Standard_Integer i = myBlocksIsRegular.Value(myBlockIndex);
  if(i == 1)
    b = Standard_True;
  return b;
}
