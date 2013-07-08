// Created by: Peter KURNEV
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


#include <BOPDS_SubIterator.ixx>
//
#include <Bnd_Box.hxx>
//
#include <NCollection_BaseAllocator.hxx>
#include <NCollection_UBTreeFiller.hxx>
//
#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Shape.hxx>
//
#include <BOPCol_IndexedDataMapOfShapeBox.hxx>
#include <BOPCol_DataMapOfIntegerInteger.hxx>
#include <BOPCol_DataMapOfIntegerMapOfInteger.hxx>
#include <BOPCol_MapOfInteger.hxx>
//
#include <BOPDS_BoxBndTree.hxx>
#include <BOPDS_IndexRange.hxx>
#include <BOPDS_PassKeyBoolean.hxx>
#include <BOPDS_MapOfPassKeyBoolean.hxx>
#include <BOPDS_Tools.hxx>
#include <BOPDS_MapOfPassKeyBoolean.hxx>

//=======================================================================
//function : 
//purpose  : 
//=======================================================================
  BOPDS_SubIterator::BOPDS_SubIterator()
:
  myAllocator(NCollection_BaseAllocator::CommonBaseAllocator()),
  myList(myAllocator)
{
  myDS=NULL; 
}
//=======================================================================
//function : 
//purpose  : 
//=======================================================================
  BOPDS_SubIterator::BOPDS_SubIterator(const Handle(NCollection_BaseAllocator)& theAllocator)
:
  myAllocator(theAllocator),
  myList(myAllocator)
{
  myDS=NULL; 
}
//=======================================================================
//function : ~
//purpose  : 
//=======================================================================
  BOPDS_SubIterator::~BOPDS_SubIterator()
{
}
//=======================================================================
// function: SetDS
// purpose: 
//=======================================================================
  void BOPDS_SubIterator::SetDS(const BOPDS_PDS& aDS)
{
  myDS=aDS;
}
//=======================================================================
// function: DS
// purpose: 
//=======================================================================
  const BOPDS_DS&  BOPDS_SubIterator::DS()const
{
  return *myDS;
}
//=======================================================================
//function : SetSubSet1
//purpose  : 
//=======================================================================
  void BOPDS_SubIterator::SetSubSet1(const BOPCol_ListOfInteger& theLI)
{
  mySubSet1=(BOPCol_PListOfInteger)&theLI;
}
//=======================================================================
//function : SubSet1
//purpose  : 
//=======================================================================
  const BOPCol_ListOfInteger& BOPDS_SubIterator::SubSet1()const 
{
  return *mySubSet1;
}
//=======================================================================
//function : SetSubSet2
//purpose  : 
//=======================================================================
  void BOPDS_SubIterator::SetSubSet2(const BOPCol_ListOfInteger& theLI)
{
  mySubSet2=(BOPCol_PListOfInteger)&theLI;
}
//=======================================================================
//function : SubSet2
//purpose  : 
//=======================================================================
  const BOPCol_ListOfInteger& BOPDS_SubIterator::SubSet2()const 
{
  return *mySubSet2;
}
//=======================================================================
// function: Initialize
// purpose: 
//=======================================================================
  void BOPDS_SubIterator::Initialize()
{
  myIterator.Initialize(myList);
}
//=======================================================================
// function: More
// purpose: 
//=======================================================================
  Standard_Boolean BOPDS_SubIterator::More()const
{
  return myIterator.More();
}
//=======================================================================
// function: Next
// purpose: 
//=======================================================================
  void BOPDS_SubIterator::Next()
{
  myIterator.Next();
}
//=======================================================================
// function: Value
// purpose: 
//=======================================================================
  void BOPDS_SubIterator::Value(Standard_Integer& theI1,
				Standard_Integer& theI2) const
{
  Standard_Integer iT1, iT2, n1, n2;
  //
  const BOPDS_PassKeyBoolean& aPKB=myIterator.Value();
  aPKB.Ids(n1, n2);
  //
  iT1=(Standard_Integer)(myDS->ShapeInfo(n1).ShapeType());
  iT2=(Standard_Integer)(myDS->ShapeInfo(n2).ShapeType());
  //
  theI1=n1;
  theI2=n2;
  if (iT1<iT2) {
    theI1=n2;
    theI2=n1;
  }
}
//=======================================================================
// function: Prepare
// purpose: 
//=======================================================================
  void BOPDS_SubIterator::Prepare()
{
  myList.Clear();
  //
  if (!myDS){
    return;
  }
  if (!mySubSet1->Extent() || !mySubSet2->Extent()) {
    return;
  }
  Intersect();
}
//=======================================================================
// function: Intersect
// purpose: 
//=======================================================================
  void BOPDS_SubIterator::Intersect()
{
  Standard_Integer i, aNbB, aNbSD, j, iDS, jB;
  Handle(NCollection_IncAllocator) aAllocator;
  BOPCol_ListIteratorOfListOfInteger aIt, aIt1, aIt2;
  BOPDS_PassKeyBoolean aPKXB; 
  //
  //-----------------------------------------------------scope_1 f
  aAllocator=new NCollection_IncAllocator();
  //
  BOPCol_DataMapOfShapeInteger aMSI(100, aAllocator);
  BOPCol_DataMapOfIntegerInteger aMII(100, aAllocator);
  BOPDS_MapOfPassKeyBoolean aMPKXB(100, aAllocator);
  BOPCol_IndexedDataMapOfShapeBox aMSB(100, aAllocator);
  //
  BOPDS_BoxBndTreeSelector aSelector;
  BOPDS_BoxBndTree aBBTree;
  NCollection_UBTreeFiller <Standard_Integer, Bnd_Box> aTreeFiller(aBBTree);
  //
  aIt1.Initialize(*mySubSet1);
  for (; aIt1.More(); aIt1.Next()) {
    i=aIt1.Value();
    const BOPDS_ShapeInfo& aSI=myDS->ShapeInfo(i);
    const TopoDS_Shape& aS=aSI.Shape();
    const Bnd_Box& aBoxEx=aSI.Box();
    aMSI.Bind(aS, i);
    aMSB.Add(aS, aBoxEx);
  }
  //
  aNbB=aMSB.Extent();
  for (i=1; i<=aNbB; ++i) {
    const TopoDS_Shape& aS=aMSB.FindKey(i);
    const Bnd_Box& aBoxEx=aMSB(i);
    //
    aTreeFiller.Add(i, aBoxEx);
    //
    iDS=aMSI.Find(aS);
    aMII.Bind(i, iDS);
  }
  //
  aTreeFiller.Fill();
  //
  aIt2.Initialize(*mySubSet2);
  for (; aIt2.More(); aIt2.Next()) {
    i=aIt2.Value();
    //
    const BOPDS_ShapeInfo& aSI=myDS->ShapeInfo(i);
    const TopoDS_Shape& aSi=aSI.Shape();
    const Bnd_Box& aBoxEx=aSI.Box();
    //
    aSelector.Clear();
    aSelector.SetBox(aBoxEx);
    aNbSD=aBBTree.Select(aSelector);
    if (!aNbSD){
      continue;
    }
    //const Bnd_Box& aBoxi=myDS->ShapeInfo(i).Box();
    //
    const BOPCol_ListOfInteger& aLI=aSelector.Indices();
    aIt.Initialize(aLI);
    for (; aIt.More(); aIt.Next()) {
      jB=aIt.Value();  // box index in MII
      j=aMII.Find(jB); // DS index
      //
      aPKXB.SetIds(i, j);
      if (aMPKXB.Add(aPKXB)) {
	myList.Append(aPKXB);
      }// if (aMPKXB.Add(aPKXB)) {
    }// for (; aIt.More(); aIt.Next()) {
  }
  //
  aMSI.Clear();
  aMII.Clear();
  aMPKXB.Clear();
  aMSB.Clear();
  //
  aAllocator.Nullify();
  //-----------------------------------------------------scope_1 t
}
