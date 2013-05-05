// Created by: Peter KURNEV
// Copyright (c) 2010-2012 OPEN CASCADE SAS
// Copyright (c) 2007-2010 CEA/DEN, EDF R&D, OPEN CASCADE
// Copyright (c) 2003-2007 OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN, CEDRAT,
//                         EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS
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


#include <BOPAlgo_Builder.ixx>

#include <TopAbs_ShapeEnum.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Iterator.hxx>
#include <BRep_Builder.hxx>


#include <BOPCol_DataMapOfIntegerInteger.hxx>
#include <BOPCol_ListOfShape.hxx>
#include <BOPCol_MapOfShape.hxx>

#include <BOPDS_DS.hxx>
#include <BOPDS_VectorOfListOfPaveBlock.hxx>
#include <BOPDS_PaveBlock.hxx>
#include <BOPDS_ListOfPaveBlock.hxx>
#include <BOPDS_ShapeInfo.hxx>

#include <BOPTools_AlgoTools.hxx>

//=======================================================================
//function : FillImagesVertices
//purpose  : 
//=======================================================================
  void BOPAlgo_Builder::FillImagesVertices()
{
  myErrorStatus=0;
  //
  Standard_Integer nV, nVSD;
  BOPCol_DataMapIteratorOfDataMapOfIntegerInteger aIt;
  //
  const BOPCol_DataMapOfIntegerInteger& aMSDV=myDS->ShapesSD();
  aIt.Initialize(aMSDV);
  for (; aIt.More(); aIt.Next()) {
    nV=aIt.Key();
    nVSD=aIt.Value();
    const TopoDS_Shape& aV=myDS->Shape(nV);
    const TopoDS_Shape& aVSD=myDS->Shape(nVSD);
    //
    BOPCol_ListOfShape aLVSD(myAllocator);
    //
    aLVSD.Append(aVSD);
    myImages.Bind(aV, aLVSD);
    //
    myShapesSD.Bind(aV, aVSD);
  }
}
//=======================================================================
//function : FillImagesEdges
//purpose  : 
//=======================================================================
  void BOPAlgo_Builder::FillImagesEdges()
{
  myErrorStatus=0;
  //
  Standard_Integer i, aNbPBP, nE, nSp, nSpR;
  BOPDS_ListIteratorOfListOfPaveBlock aItPB;
  //
  const BOPDS_VectorOfListOfPaveBlock& aPBP=myDS->PaveBlocksPool();
  aNbPBP=aPBP.Extent();
  for (i=0; i<aNbPBP; ++i) {
    const BOPDS_ListOfPaveBlock& aLPB=aPBP(i);
    if (aLPB.Extent()) {
      BOPCol_ListOfShape aLS(myAllocator);
      //
      const Handle(BOPDS_PaveBlock)& aPB1=aLPB.First();
      nE=aPB1->OriginalEdge();
      const TopoDS_Shape& aE=myDS->Shape(nE);
      //
      aItPB.Initialize(aLPB);
      for (; aItPB.More(); aItPB.Next()) {
        const Handle(BOPDS_PaveBlock)& aPB=aItPB.Value();
        const Handle(BOPDS_PaveBlock)& aPBR=aPB->RealPaveBlock();
        //
        nSpR=aPBR->Edge();
        const TopoDS_Shape& aSpR=myDS->Shape(nSpR);
        aLS.Append(aSpR);
        myOrigins.Bind(aSpR, aE);
        //
        if (aPB->IsCommonBlockOnEdge()) {
          nSp=aPB->Edge();
          const TopoDS_Shape& aSp=myDS->Shape(nSp);
          myShapesSD.Bind(aSp, aSpR);
        }
      }
      myImages.Bind(aE, aLS);
    }
  }
}
//=======================================================================
// function: IsInterferred
// purpose: 
//=======================================================================
  Standard_Boolean BOPAlgo_Builder::IsInterferred(const TopoDS_Shape& theS)const
{
  Standard_Boolean bInterferred;
  TopoDS_Iterator aIt;
  //
  bInterferred=Standard_False;
  aIt.Initialize(theS);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aSx=aIt.Value();
    if (myImages.IsBound(aSx)) {
      bInterferred=!bInterferred;
      break;
    }
  }
  return bInterferred;
}
//=======================================================================
//function : BuildResult
//purpose  : 
//=======================================================================
  void BOPAlgo_Builder::BuildResult(const TopAbs_ShapeEnum theType)
{
  myErrorStatus=0;
  //
  TopAbs_ShapeEnum aType;
  BRep_Builder aBB;
  BOPCol_MapOfShape aM;
  BOPCol_ListIteratorOfListOfShape aIt, aItIm;
  //
  aIt.Initialize(myArguments);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aS=aIt.Value();
    aType=aS.ShapeType();
    if (aType==theType) {
      if (myImages.IsBound(aS)){
	const BOPCol_ListOfShape& aLSIm=myImages.Find(aS);
	aItIm.Initialize(aLSIm);
	for (; aItIm.More(); aItIm.Next()) {
	  const TopoDS_Shape& aSIm=aItIm.Value();
	  if (aM.Add(aSIm)) {
	    aBB.Add(myShape, aSIm);
	  }
	}
      }
      else {
	if (aM.Add(aS)) {
	  aBB.Add(myShape, aS);
	}
      }
    }
  }
}
//=======================================================================
// function: FillImagesContainers
// purpose: 
//=======================================================================
  void BOPAlgo_Builder::FillImagesContainers(const TopAbs_ShapeEnum theType)
{
  myErrorStatus=0;
  //
  Standard_Integer i, aNbS;
  BOPCol_MapOfShape aMFP(100, myAllocator);
  //
  aNbS=myDS->NbSourceShapes();
  for (i=0; i<aNbS; ++i) {
    const BOPDS_ShapeInfo& aSI=myDS->ShapeInfo(i);
    if (aSI.ShapeType()==theType) {
      const TopoDS_Shape& aC=aSI.Shape();
      FillImagesContainer(aC, theType);
    }   
  }// for (; aItS.More(); aItS.Next()) {
}
//=======================================================================
// function: FillImagesCompounds
// purpose: 
//=======================================================================
  void BOPAlgo_Builder::FillImagesCompounds()
{
  myErrorStatus=0;
  //
  Standard_Integer i, aNbS;
  BOPCol_MapOfShape aMFP(100, myAllocator);
  //
  aNbS=myDS->NbSourceShapes();
  for (i=0; i<aNbS; ++i) {
    const BOPDS_ShapeInfo& aSI=myDS->ShapeInfo(i);
    if (aSI.ShapeType()==TopAbs_COMPOUND) {
      const TopoDS_Shape& aC=aSI.Shape();
      FillImagesCompound(aC, aMFP);
    }
  }// for (; aItS.More(); aItS.Next()) {
}
//=======================================================================
//function : FillImagesContainer
//purpose  : 
//=======================================================================
  void BOPAlgo_Builder::FillImagesContainer(const TopoDS_Shape& theS,
                                            const TopAbs_ShapeEnum theType)
{
  Standard_Boolean bInterferred, bToReverse;
  TopoDS_Iterator aIt;
  BRep_Builder aBB;
  BOPCol_ListIteratorOfListOfShape aItIm; 
  //
  bInterferred=IsInterferred(theS);
  if (!bInterferred){
    return;
  }
  //
  TopoDS_Shape aCIm;
  BOPTools_AlgoTools::MakeContainer(theType, aCIm);
  //
  aIt.Initialize(theS);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aSx=aIt.Value();
    if (myImages.IsBound(aSx)) {
      const BOPCol_ListOfShape& aLFIm=myImages.Find(aSx);
      aItIm.Initialize(aLFIm);
      for (; aItIm.More(); aItIm.Next()) {
        TopoDS_Shape aSxIm=aItIm.Value();
        //
        bToReverse=BOPTools_AlgoTools::IsSplitToReverse(aSxIm, aSx, myContext);
        if (bToReverse) {
          aSxIm.Reverse();
        }
        aBB.Add(aCIm, aSxIm);
      }
    }
    else {
      aBB.Add(aCIm, aSx);
    }
  }
  //
  BOPCol_ListOfShape aLSIm(myAllocator);
  aLSIm.Append(aCIm);
  myImages.Bind(theS, aLSIm); 
}
//=======================================================================
//function : FillImagesCompound
//purpose  : 
//=======================================================================
  void BOPAlgo_Builder::FillImagesCompound(const TopoDS_Shape& theS,
                                           BOPCol_MapOfShape& theMFP)
{ 
  Standard_Boolean bInterferred;
  TopAbs_Orientation aOrX;
  TopoDS_Iterator aIt;
  BRep_Builder aBB;
  BOPCol_ListIteratorOfListOfShape aItIm; 
  //
  if (!theMFP.Add(theS)) {
    return;
  }
  //
  bInterferred=Standard_False;
  aIt.Initialize(theS);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aSx=aIt.Value();
    if (aSx.ShapeType()==TopAbs_COMPOUND) {
      FillImagesCompound(aSx, theMFP);
    }
    if (myImages.IsBound(aSx)) {
      bInterferred=Standard_True;
    }
  }
  if (!bInterferred){
    return;
  }
  //
  TopoDS_Shape aCIm;
  BOPTools_AlgoTools::MakeContainer(TopAbs_COMPOUND, aCIm);
  //
  aIt.Initialize(theS);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aSX=aIt.Value();
    aOrX=aSX.Orientation();
    if (myImages.IsBound(aSX)) {
      const BOPCol_ListOfShape& aLFIm=myImages.Find(aSX);
      aItIm.Initialize(aLFIm);
      for (; aItIm.More(); aItIm.Next()) {
	TopoDS_Shape aSXIm=aItIm.Value();
	aSXIm.Orientation(aOrX);
	aBB.Add(aCIm, aSXIm);
      }
    }
    else {
      aBB.Add(aCIm, aSX);
    }
  }
  //
  BOPCol_ListOfShape aLSIm(myAllocator);
  aLSIm.Append(aCIm);
  myImages.Bind(theS, aLSIm); 
}
