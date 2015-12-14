// Created by: Peter KURNEV
// Copyright (c) 2010-2014 OPEN CASCADE SAS
// Copyright (c) 2007-2010 CEA/DEN, EDF R&D, OPEN CASCADE
// Copyright (c) 2003-2007 OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN, CEDRAT,
//                         EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <BOPAlgo_Builder.ixx>
//
#include <TopoDS_Shape.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Compound.hxx>
//
#include <BRep_Tool.hxx>
#include <BRep_Builder.hxx>
//
#include <TopExp_Explorer.hxx>
//
#include <BOPCol_ListOfShape.hxx>
#include <BOPCol_ListOfInteger.hxx>
#include <BOPCol_MapOfInteger.hxx>
#include <BOPCol_DataMapOfIntegerListOfShape.hxx>
#include <BOPCol_DataMapOfShapeShape.hxx>
#include <BOPCol_NCVector.hxx>
#include <BOPCol_Parallel.hxx>
//
#include <IntTools_Context.hxx>
//
#include <BOPDS_PaveBlock.hxx>
#include <BOPDS_ShapeInfo.hxx>
#include <BOPDS_DS.hxx>
#include <BOPDS_FaceInfo.hxx>
#include <BOPDS_MapOfPaveBlock.hxx>
#include <BOPDS_VectorOfInterfFF.hxx>
#include <BOPDS_Interf.hxx>
#include <BOPDS_VectorOfCurve.hxx>
#include <BOPDS_VectorOfPoint.hxx>
//
#include <BOPTools.hxx>
#include <BOPTools_AlgoTools.hxx>
#include <BOPTools_AlgoTools2D.hxx>
#include <BOPTools_AlgoTools3D.hxx>
#include <BOPAlgo_BuilderFace.hxx>
#include <BOPTools_CoupleOfShape.hxx>
#include <BOPTools_ListOfCoupleOfShape.hxx>
#include <BOPTools_MapOfSet.hxx>
#include <BOPTools_DataMapOfShapeSet.hxx>


static
  Standard_Boolean HasPaveBlocksOnIn(const BOPDS_FaceInfo& aFI1,
                                     const BOPDS_FaceInfo& aFI2);
static
  void FillMap(const TopoDS_Shape& aS1,
               const TopoDS_Shape& aS2,
               BOPCol_IndexedDataMapOfShapeListOfShape& aDMSLS,
               Handle(NCollection_BaseAllocator)& aAllocator);
static
  void MakeBlocksCnx(const BOPCol_IndexedDataMapOfShapeListOfShape& aMILI,
                     BOPCol_DataMapOfIntegerListOfShape& aMBlocks,
                     Handle(NCollection_BaseAllocator)& aAllocator);
//
typedef BOPCol_NCVector<TopoDS_Shape> BOPAlgo_VectorOfShape;
//
typedef BOPCol_NCVector<BOPAlgo_VectorOfShape> \
  BOPAlgo_VectorOfVectorOfShape;
//
typedef NCollection_IndexedDataMap\
  <BOPTools_Set, Standard_Integer, BOPTools_SetMapHasher> \
    BOPAlgo_IndexedDataMapOfSetInteger;
//
//=======================================================================
//class    : BOPAlgo_PairOfShapeBoolean
//purpose  : 
//=======================================================================
class BOPAlgo_PairOfShapeBoolean : public BOPAlgo_Algo {

 public:
  DEFINE_STANDARD_ALLOC

  BOPAlgo_PairOfShapeBoolean() : 
    BOPAlgo_Algo(),
    myFlag(Standard_False) {
  }
  //
  virtual ~BOPAlgo_PairOfShapeBoolean() {
  }
  //
  TopoDS_Shape& Shape1() {
    return myShape1;
  }
  //
  TopoDS_Shape& Shape2() {
    return myShape2;
  }
  //
  Standard_Boolean& Flag() {
    return myFlag;
  }
  //
  void SetContext(const Handle(IntTools_Context)& aContext) {
    myContext=aContext;
  }
  //
  const Handle(IntTools_Context)& Context()const {
    return myContext;
  }
  //
  virtual void Perform() {
    BOPAlgo_Algo::UserBreak();
    //  
    const TopoDS_Face& aFj=*((TopoDS_Face*)&myShape1);
    const TopoDS_Face& aFk=*((TopoDS_Face*)&myShape2);
    myFlag=BOPTools_AlgoTools::AreFacesSameDomain(aFj, aFk, myContext);
  }
  //
 protected: 
  Standard_Boolean myFlag;
  TopoDS_Shape myShape1;
  TopoDS_Shape myShape2;
  Handle(IntTools_Context) myContext;
};
//
typedef BOPCol_NCVector<BOPAlgo_PairOfShapeBoolean> \
  BOPAlgo_VectorOfPairOfShapeBoolean;
//
typedef BOPCol_ContextFunctor 
  <BOPAlgo_PairOfShapeBoolean,
  BOPAlgo_VectorOfPairOfShapeBoolean,
  Handle(IntTools_Context), 
  IntTools_Context> BOPCol_BuilderSDFaceFunctor;
//
typedef BOPCol_ContextCnt 
  <BOPCol_BuilderSDFaceFunctor,
  BOPAlgo_VectorOfPairOfShapeBoolean,
  Handle(IntTools_Context)> BOPAlgo_BuilderSDFaceCnt;
//
//=======================================================================
// BuilderFace
//
typedef BOPCol_NCVector<BOPAlgo_BuilderFace> BOPAlgo_VectorOfBuilderFace;
//
typedef BOPCol_Functor 
  <BOPAlgo_BuilderFace,
  BOPAlgo_VectorOfBuilderFace> BOPAlgo_BuilderFaceFunctor;
//
typedef BOPCol_Cnt 
  <BOPAlgo_BuilderFaceFunctor,
  BOPAlgo_VectorOfBuilderFace> BOPAlgo_BuilderFaceCnt;
//
//=======================================================================
//class    : BOPAlgo_VFI
//purpose  : 
//=======================================================================
class BOPAlgo_VFI : public BOPAlgo_Algo {

 public:
  DEFINE_STANDARD_ALLOC
  
  BOPAlgo_VFI() :
    BOPAlgo_Algo(),
    myFlag(-1) {
  }
  //
  virtual ~BOPAlgo_VFI(){
  }
  //
  void SetVertex(const TopoDS_Vertex& aV) {
    myV=aV;
  }
  //
  TopoDS_Vertex& Vertex() {
    return myV;
  }
  //
  void SetFace(const TopoDS_Face& aF) {
    myF=aF;
  }
  //
  TopoDS_Face& Face() {
    return myF;
  }
  //
  Standard_Integer Flag()const {
    return myFlag;
  }
  //
  void SetContext(const Handle(IntTools_Context)& aContext) {
    myContext=aContext;
  }
  //
  const Handle(IntTools_Context)& Context()const {
    return myContext;
  }
  //
  virtual void Perform() {
    Standard_Real aT1, aT2;
    //
    BOPAlgo_Algo::UserBreak();
    myFlag=myContext->ComputeVF(myV, myF, aT1, aT2);
  }
  //
 protected:
  Standard_Integer myFlag;
  TopoDS_Vertex myV;
  TopoDS_Face myF;
  Handle(IntTools_Context) myContext;
};
//
typedef BOPCol_NCVector<BOPAlgo_VFI> BOPAlgo_VectorOfVFI; 
//
typedef BOPCol_ContextFunctor 
  <BOPAlgo_VFI,
  BOPAlgo_VectorOfVFI,
  Handle(IntTools_Context), 
  IntTools_Context> BOPAlgo_VFIFunctor;
//
typedef BOPCol_ContextCnt 
  <BOPAlgo_VFIFunctor,
  BOPAlgo_VectorOfVFI,
  Handle(IntTools_Context)> BOPAlgo_VFICnt;
//
//=======================================================================
//function : FillImagesFaces
//purpose  : 
//=======================================================================
void BOPAlgo_Builder::FillImagesFaces()
{
  myErrorStatus=0;
  //
  BuildSplitFaces();
  FillSameDomainFaces();
  FillImagesFaces1();
}
//=======================================================================
//function : BuildSplitFaces
//purpose  : 
//=======================================================================
void BOPAlgo_Builder::BuildSplitFaces()
{
  Standard_Boolean bHasFaceInfo, bIsClosed, bIsDegenerated, bToReverse;
  Standard_Integer i, j, k, aNbS, aNbPBIn, aNbPBOn, aNbPBSc, aNbAV, nSp;
  Standard_Size aNbBF;
  TopoDS_Face aFF, aFSD;
  TopoDS_Edge aSp, aEE;
  TopAbs_Orientation anOriF, anOriE;
  TopExp_Explorer aExp;
  BOPCol_ListIteratorOfListOfShape aIt;
  BOPCol_ListOfInteger aLIAV;
  BOPCol_MapOfShape aMFence;
  Handle(NCollection_BaseAllocator) aAllocator;
  BOPCol_ListOfShape aLFIm(myAllocator);
  BOPAlgo_VectorOfBuilderFace aVBF;
  //
  myErrorStatus=0;
  //
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~scope f
  aAllocator=
    NCollection_BaseAllocator::CommonBaseAllocator();
  //
  BOPCol_ListOfShape aLE(aAllocator);
  BOPCol_MapOfShape aMDE(100, aAllocator);
  //
  aNbS=myDS->NbSourceShapes();
  //
  for (i=0; i<aNbS; ++i) {
    const BOPDS_ShapeInfo& aSI=myDS->ShapeInfo(i);
    if (aSI.ShapeType()!=TopAbs_FACE) {
      continue;
    }
    //
    const TopoDS_Face& aF=(*(TopoDS_Face*)(&aSI.Shape()));
    //
    bHasFaceInfo=myDS->HasFaceInfo(i);
    if(!bHasFaceInfo) {
      continue;
    }
    //
    const BOPDS_FaceInfo& aFI=myDS->FaceInfo(i);
    //
    const BOPDS_IndexedMapOfPaveBlock& aMPBIn=aFI.PaveBlocksIn();
    const BOPDS_IndexedMapOfPaveBlock& aMPBOn=aFI.PaveBlocksOn();
    const BOPDS_IndexedMapOfPaveBlock& aMPBSc=aFI.PaveBlocksSc();
    aLIAV.Clear();
    myDS->AloneVertices(i, aLIAV);
    
    aNbPBIn=aMPBIn.Extent();
    aNbPBOn=aMPBOn.Extent();
    aNbPBSc=aMPBSc.Extent();
    aNbAV=aLIAV.Extent();
    if (!aNbPBIn && !aNbPBOn && !aNbPBSc && !aNbAV) { // not compete
      continue;
    }
    //
    aMFence.Clear();
    //
    anOriF=aF.Orientation();
    aFF=aF;
    aFF.Orientation(TopAbs_FORWARD);
    //
    // 1. Fill the egdes set for the face aFF -> LE
    aLE.Clear();
    //
    //
    // 1.1 Bounding edges
    aExp.Init(aFF, TopAbs_EDGE);
    for (; aExp.More(); aExp.Next()) {
      const TopoDS_Edge& aE=(*(TopoDS_Edge*)(&aExp.Current()));
      anOriE=aE.Orientation();
      bIsDegenerated=BRep_Tool::Degenerated(aE);
      bIsClosed=BRep_Tool::IsClosed(aE, aF);
      //
      if (!myImages.IsBound(aE)) {
        if (anOriE==TopAbs_INTERNAL) {
          aEE=aE;
          aEE.Orientation(TopAbs_FORWARD);
          aLE.Append(aEE);
          aEE.Orientation(TopAbs_REVERSED);
          aLE.Append(aEE);
        }
        else {
          aLE.Append(aE);
        }
      }
      else {//else 1
        const BOPCol_ListOfShape& aLIE=myImages.Find(aE);
        aIt.Initialize(aLIE);
        for (; aIt.More(); aIt.Next()) {
          aSp=(*(TopoDS_Edge*)(&aIt.Value()));
          if (bIsDegenerated) {
            aSp.Orientation(anOriE);
            aLE.Append(aSp);
            continue;
          }
          //
          if (anOriE==TopAbs_INTERNAL) {
            aSp.Orientation(TopAbs_FORWARD);
            aLE.Append(aSp);
            aSp.Orientation(TopAbs_REVERSED);
            aLE.Append(aSp);
            continue;
          }
          //
          if (bIsClosed) {
            if (aMFence.Add(aSp)) {
              if (!BRep_Tool::IsClosed(aSp, aF)){
                BOPTools_AlgoTools3D::DoSplitSEAMOnFace(aSp, aF);
                }
              //
              aSp.Orientation(TopAbs_FORWARD);
              aLE.Append(aSp);
              aSp.Orientation(TopAbs_REVERSED);
              aLE.Append(aSp);
            }// if (aMFence.Add(aSp))
            continue;
          }// if (bIsClosed){
          //
          aSp.Orientation(anOriE);
          bToReverse=BOPTools_AlgoTools::IsSplitToReverse(aSp, aE, myContext);
          if (bToReverse) {
            aSp.Reverse();
          }
          aLE.Append(aSp);
        }// for (; aIt.More(); aIt.Next()) {
      }// else 1
    }// for (; aExp.More(); aExp.Next()) {
    // 
    //
    // 1.2 In edges
    for (j=1; j<=aNbPBIn; ++j) {
      const Handle(BOPDS_PaveBlock)& aPB=aMPBIn(j);
      nSp=aPB->Edge();
      aSp=(*(TopoDS_Edge*)(&myDS->Shape(nSp)));
      //
      aSp.Orientation(TopAbs_FORWARD);
      aLE.Append(aSp);
      aSp.Orientation(TopAbs_REVERSED);
      aLE.Append(aSp);
    }
    //
    //
    // 1.3 Section edges
    for (j=1; j<=aNbPBSc; ++j) {
      const Handle(BOPDS_PaveBlock)& aPB=aMPBSc(j);
      nSp=aPB->Edge();
      aSp=(*(TopoDS_Edge*)(&myDS->Shape(nSp)));
      //
      aSp.Orientation(TopAbs_FORWARD);
      aLE.Append(aSp);
      aSp.Orientation(TopAbs_REVERSED);
      aLE.Append(aSp);
    }
    //
    BOPTools_AlgoTools2D::BuildPCurveForEdgesOnPlane (aLE, aFF);
    //
    // 3 Build split faces
    BOPAlgo_BuilderFace& aBF=aVBF.Append1();
    aBF.SetFace(aF);
    aBF.SetShapes(aLE);
    aBF.SetRunParallel(myRunParallel);
    aBF.SetProgressIndicator(myProgressIndicator);
    //
  }// for (i=0; i<aNbS; ++i) {
  //
  aNbBF=aVBF.Extent();
  //
  //===================================================
  BOPAlgo_BuilderFaceCnt::Perform(myRunParallel, aVBF);
  //===================================================
  //
  for (k=0; k<(Standard_Integer)aNbBF; ++k) {
    aLFIm.Clear();
    //
    BOPAlgo_BuilderFace& aBF=aVBF(k);
    TopoDS_Face aF=aBF.Face();
    anOriF=aBF.Orientation();
    aF.Orientation(anOriF);
    //
    const BOPCol_ListOfShape& aLFR=aBF.Areas();
    aIt.Initialize(aLFR);
    for (; aIt.More(); aIt.Next()) {
      TopoDS_Shape& aFR=aIt.ChangeValue();
      if (anOriF==TopAbs_REVERSED) {
        aFR.Orientation(TopAbs_REVERSED);
      }
      //aFR.Orientation(anOriF);
      aLFIm.Append(aFR);
    }
    //
    mySplits.Bind(aF, aLFIm); 
  }// for (k=0; k<aNbBF; ++k) {
  //
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~scope t
}
//=======================================================================
//function : FillSameDomainFaces
//purpose  : 
//=======================================================================
void BOPAlgo_Builder::FillSameDomainFaces()
{
  Standard_Boolean bFlag;
  Standard_Integer i, j, k, aNbFFs, aNbCurves, aNbPoints, nF1, nF2, aNbS;
  Handle(NCollection_BaseAllocator) aAllocator;
  BOPCol_ListIteratorOfListOfShape aItF;
  BOPCol_MapOfShape aMFence;
  BOPAlgo_IndexedDataMapOfSetInteger aIDMSS;
  BOPAlgo_VectorOfVectorOfShape aVVS;
  //
  myErrorStatus=0;
  //
  const BOPDS_VectorOfInterfFF& aFFs=myDS->InterfFF();
  //
  aNbFFs=aFFs.Extent();
  if (!aNbFFs) {
    return;
  }
  //
  for (i=0; i<aNbFFs; ++i) {
    const BOPDS_InterfFF& aFF=aFFs(i);
    aFF.Indices(nF1, nF2);
    //
    const BOPDS_VectorOfCurve& aCurves=aFF.Curves();
    aNbCurves=aCurves.Extent();
    if (aNbCurves) {
      //
      bFlag=Standard_False;
      for (j=0; j<aNbCurves; ++j) {
        const BOPDS_Curve& aNC=aCurves.Value(j);
        bFlag=aNC.HasEdge();
        if (bFlag) {
          break;
        }
      }
      if (bFlag) {
        continue;
      }
      //continue;
    }
    //
    const BOPDS_VectorOfPoint& aPoints=aFF.Points();
    aNbPoints=aPoints.Extent();
    if (aNbPoints) {
      continue;
    }
    //
    if (!myDS->HasFaceInfo(nF1) || !myDS->HasFaceInfo(nF2) ) {
      continue;
    }
    //
    const BOPDS_FaceInfo& aFI1=myDS->FaceInfo(nF1);
    const BOPDS_FaceInfo& aFI2=myDS->FaceInfo(nF2);
    //
    const TopoDS_Shape& aF1=myDS->Shape(nF1);
    const TopoDS_Shape& aF2=myDS->Shape(nF2);
    //
    bFlag=HasPaveBlocksOnIn(aFI1, aFI2);
    bFlag=bFlag && (mySplits.IsBound(aF1) && mySplits.IsBound(aF2));
    //
    if (bFlag) {
      for (k=0; k<2; ++k) {
        const TopoDS_Shape& aF=(!k) ? aF1 : aF2;
        const BOPCol_ListOfShape& aLF=mySplits.Find(aF);
        //
        aItF.Initialize(aLF);
        for (; aItF.More(); aItF.Next()) {
          const TopoDS_Shape& aFx=aItF.Value();
          //
          if (aMFence.Add(aFx)) {
            BOPTools_Set aSTx;
            //
            aSTx.Add(aFx, TopAbs_EDGE);
            //
            if (!aIDMSS.Contains(aSTx)) {
              BOPAlgo_VectorOfShape& aVS=aVVS.Append1(); 
              aVS.Append(aFx);
              //
              j=aVVS.Extent()-1;
              aIDMSS.Add (aSTx, j);
            }
            else {
              j=aIDMSS.ChangeFromKey(aSTx);
              BOPAlgo_VectorOfShape& aVS=aVVS(j);
              aVS.Append(aFx);
            }
          }
        }
      }
    }// if (bFlag) {
    else {// if (!bFlag) 
      BOPTools_Set aST1, aST2;
      //
      aST1.Add(aF1, TopAbs_EDGE);
      aST2.Add(aF2, TopAbs_EDGE);
      //
      if (aST1.IsEqual(aST2)) {
        if (!aIDMSS.Contains(aST1)) {
          BOPAlgo_VectorOfShape& aVS=aVVS.Append1(); 
          if (aMFence.Add(aF1)) {
            aVS.Append(aF1);
          }
          if (aMFence.Add(aF2)) {
            aVS.Append(aF2);
          }
          //
          k=aVVS.Extent()-1;
          aIDMSS.Add (aST1, k);
        }
        else {
          k=aIDMSS.ChangeFromKey(aST1);
          BOPAlgo_VectorOfShape& aVS=aVVS(k);
          if (aMFence.Add(aF1)) {
            aVS.Append(aF1);
          }
          if (aMFence.Add(aF2)) {
            aVS.Append(aF2);
          }
        }
      }//if (aST1.IsEqual(aST2)) {
    }// else {// if (!bFlag) 
    //
  }// for (i=0; i<aNbFFs; ++i) {
  //
  aIDMSS.Clear();
  //
  Standard_Boolean bFlagSD;
  Standard_Integer aNbVPSB, aNbVVS, aNbF, aNbF1;
  BOPAlgo_VectorOfPairOfShapeBoolean aVPSB;
  //
  aNbVVS=aVVS.Extent();
  for (i=0; i<aNbVVS; ++i) {
    const BOPAlgo_VectorOfShape& aVS=aVVS(i);
    aNbF=aVS.Extent();
    if (aNbF<2) {
      continue;
    }
    //
    aNbF1=aNbF-1;
    for (j=0; j<aNbF1; ++j) {
      const TopoDS_Shape& aFj=aVS(j);
      for (k=j+1; k<aNbF; ++k) {
        const TopoDS_Shape& aFk=aVS(k);
        BOPAlgo_PairOfShapeBoolean& aPSB=aVPSB.Append1();
        aPSB.Shape1()=aFj;
        aPSB.Shape2()=aFk;
        aPSB.SetProgressIndicator(myProgressIndicator);
      }
    }
  }
  //================================================================
  BOPAlgo_BuilderSDFaceCnt::Perform(myRunParallel, aVPSB, myContext);
  //================================================================
  aAllocator=
    NCollection_BaseAllocator::CommonBaseAllocator();
  BOPCol_IndexedDataMapOfShapeListOfShape aDMSLS(100, aAllocator);
  BOPCol_DataMapOfIntegerListOfShape aMBlocks(100, aAllocator);
  //
  aNbVPSB=aVPSB.Extent();
  for (i=0; i<aNbVPSB; ++i) {
    BOPAlgo_PairOfShapeBoolean& aPSB=aVPSB(i);
    bFlagSD=aPSB.Flag();
    if (bFlagSD) {
      const TopoDS_Shape& aFj=aPSB.Shape1();
      const TopoDS_Shape& aFk=aPSB.Shape2();
      FillMap(aFj, aFk, aDMSLS, aAllocator);
    }
  }
  aVPSB.Clear();
  //
  // 2. Make blocks
  MakeBlocksCnx(aDMSLS, aMBlocks, aAllocator);
  //
  // 3. Fill same domain faces map -> aMSDF
  aNbS = aMBlocks.Extent();
  for (i=0; i<aNbS; ++i) {
    const BOPCol_ListOfShape& aLSD=aMBlocks.Find(i);
    if (aLSD.IsEmpty()) {
      continue;
    }
    //
    const TopoDS_Shape& aFSD1=aLSD.First();
    aItF.Initialize(aLSD);
    for (; aItF.More(); aItF.Next()) {
      const TopoDS_Shape& aFSD=aItF.Value();
      myShapesSD.Bind(aFSD, aFSD1);
      //
      // If the face has no splits but are SD face,
      // it is considered as splitted face
      if (!mySplits.IsBound(aFSD)) {
        BOPCol_ListOfShape aLS;
        aLS.Append(aFSD);
        mySplits.Bind(aFSD, aLS);
      }
    }
  }
  aMBlocks.Clear();
  aDMSLS.Clear();
}
//=======================================================================
// function: FillImagesFaces1
// purpose: 
//=======================================================================
void BOPAlgo_Builder::FillImagesFaces1()
{
  Standard_Integer i, aNbS, iSense, nVx, aNbVFI, iFlag;
  TopoDS_Face aFSD;
  TopoDS_Vertex aVx;
  BRep_Builder aBB;
  BOPCol_ListOfInteger aLIAV;
  BOPCol_ListOfShape aLFIm;
  BOPCol_ListIteratorOfListOfInteger aItV;
  BOPCol_ListIteratorOfListOfShape aItLS, aItF;
  BOPAlgo_VectorOfVFI aVVFI;
  //
  aNbS=myDS->NbSourceShapes();
  for (i=0; i<aNbS; ++i) {
    const BOPDS_ShapeInfo& aSI=myDS->ShapeInfo(i);
    if (aSI.ShapeType()!=TopAbs_FACE) {
      continue;
    }
    //
    const TopoDS_Face& aF=(*(TopoDS_Face*)(&aSI.Shape()));
    //
    if (!mySplits.IsBound(aF)) {
      continue;
    }
    // 
    // 1.
    aLIAV.Clear();
    myDS->AloneVertices(i, aLIAV);
    aLFIm.Clear();
    //
    const BOPCol_ListOfShape& aLSp=mySplits.Find(aF);
    aItLS.Initialize(aLSp);
    for (; aItLS.More(); aItLS.Next()) {
      const TopoDS_Face& aFSp=(*(TopoDS_Face*)(&aItLS.Value()));
      if (!myShapesSD.IsBound(aFSp)) {
        aLFIm.Append(aFSp);
      }
      else {
        aFSD=(*(TopoDS_Face*)(&myShapesSD.Find(aFSp)));
        iSense=BOPTools_AlgoTools::Sense(aFSp, aFSD);
        if (iSense<0) {
          aFSD.Reverse();
        }
        aLFIm.Append(aFSD);
      }
    }
    //
    //FillInternalVertices(aLFIm, aLIAV);
    //
    myImages.Bind(aF, aLFIm); 
    //
    // 2. fill myOrigins
    aItLS.Initialize(aLFIm);
    for (; aItLS.More(); aItLS.Next()) {
      const TopoDS_Face& aFSp=(*(TopoDS_Face*)(&aItLS.Value()));
      myOrigins.Bind(aFSp, aF);
    }
    //
    // 3.
    aItV.Initialize(aLIAV);
    for (; aItV.More(); aItV.Next()) {
      nVx=aItV.Value();
      aVx=(*(TopoDS_Vertex*)(&myDS->Shape(nVx)));
      aVx.Orientation(TopAbs_INTERNAL);
      //
      aItF.Initialize(aLFIm);
      for (; aItF.More(); aItF.Next()) {
        TopoDS_Face& aFy=(*(TopoDS_Face*)(&aItF.Value()));
        //
        BOPAlgo_VFI& aVFI=aVVFI.Append1();
        aVFI.SetVertex(aVx);
        aVFI.SetFace(aFy);
        aVFI.SetProgressIndicator(myProgressIndicator);
      }
    }
  }// for (i=0; i<aNbS; ++i) {
  //
  // 4. 
  aNbVFI=aVVFI.Extent();
  //================================================================
  BOPAlgo_VFICnt::Perform(myRunParallel, aVVFI, myContext);
  //================================================================
  //
  for (i=0; i < aNbVFI; ++i) {
    BOPAlgo_VFI& aVFI=aVVFI(i);
    //
    iFlag=aVFI.Flag();
    if (!iFlag) {
      TopoDS_Vertex& aVx=aVFI.Vertex();
      TopoDS_Face& aFy=aVFI.Face(); 
      aBB.Add(aFy, aVx);
    }
  }
}
//=======================================================================
//function : MakeBlocksCnx
//purpose  : 
//=======================================================================
void MakeBlocksCnx(const BOPCol_IndexedDataMapOfShapeListOfShape& aMILI,
                   BOPCol_DataMapOfIntegerListOfShape& aMBlocks,
                   Handle(NCollection_BaseAllocator)& aAllocator)
{
  Standard_Integer aNbV, aNbVS, aNbVP, aNbEC, k, i, j;
  BOPCol_ListIteratorOfListOfShape aItLI;
  //
  BOPCol_MapOfShape aMVS(100, aAllocator);
  BOPCol_IndexedMapOfShape aMEC(100, aAllocator);
  BOPCol_IndexedMapOfShape aMVP(100, aAllocator);
  BOPCol_IndexedMapOfShape aMVAdd(100, aAllocator);
  //
  aNbV=aMILI.Extent();
  //
  for (k=0,i=1; i<=aNbV; ++i) {
    aNbVS=aMVS.Extent();
    if (aNbVS==aNbV) {
      break;
    }
    //
    const TopoDS_Shape& nV=aMILI.FindKey(i);
    if (aMVS.Contains(nV)){
      continue;
    }
    aMVS.Add(nV);
    //
    aMEC.Clear();
    aMVP.Clear();
    aMVAdd.Clear();
    //
    aMVP.Add(nV);
    for(;;) {
      aNbVP=aMVP.Extent();
      for (j=1; j<=aNbVP; ++j) {
        const TopoDS_Shape& nVP=aMVP(j);
        const BOPCol_ListOfShape& aLV=aMILI.FindFromKey(nVP);
        aItLI.Initialize(aLV);
        for (; aItLI.More(); aItLI.Next()) {
          const TopoDS_Shape& nVx=aItLI.Value();
          if (aMEC.Contains(nVx)) {
            continue;
          }
          //
          aMVS.Add(nVx);
          aMEC.Add(nVx);
          aMVAdd.Add(nVx);
        }
      }
      //
      aNbVP=aMVAdd.Extent();
      if (!aNbVP) {
        break; // from while(1)
      }
      //
      aMVP.Clear();
      for (j=1; j<=aNbVP; ++j) {
        aMVP.Add(aMVAdd(j));
      }
      aMVAdd.Clear();
    }//while(1) {
    //
    BOPCol_ListOfShape aLIx(aAllocator);
    //
    aNbEC = aMEC.Extent();
    for (j=1; j<=aNbEC; ++j) {
      const TopoDS_Shape& nVx=aMEC(j);
      aLIx.Append(nVx);
    }
    //
    aMBlocks.Bind(k, aLIx);
    ++k;
  }//for (k=0,i=1; i<=aNbV; ++i)
  aMVAdd.Clear();
  aMVP.Clear();
  aMEC.Clear();
  aMVS.Clear();
}
//=======================================================================
//function : FillMap
//purpose  : 
//=======================================================================
void FillMap(const TopoDS_Shape& aS1,
             const TopoDS_Shape& aS2,
             BOPCol_IndexedDataMapOfShapeListOfShape& aDMSLS,
             Handle(NCollection_BaseAllocator)& aAllocator)
{
  if (aDMSLS.Contains(aS1)) {
    BOPCol_ListOfShape& aLS=aDMSLS.ChangeFromKey(aS1);
    aLS.Append(aS2);
  }
  else {
    BOPCol_ListOfShape aLS(aAllocator);
    aLS.Append(aS2);
    aDMSLS.Add(aS1, aLS);
  }
  //
  if (aDMSLS.Contains(aS2)) {
    BOPCol_ListOfShape& aLS=aDMSLS.ChangeFromKey(aS2);
    aLS.Append(aS1);
  }
  else {
    BOPCol_ListOfShape aLS(aAllocator);
    aLS.Append(aS1);
    aDMSLS.Add(aS2, aLS);
  }
}
//=======================================================================
//function :HasPaveBlocksOnIn
//purpose  : 
//=======================================================================
Standard_Boolean HasPaveBlocksOnIn(const BOPDS_FaceInfo& aFI1,
                                   const BOPDS_FaceInfo& aFI2)
{
  Standard_Boolean bRet;
  Standard_Integer i, aNbPB;
  //
  bRet=Standard_False;
  const BOPDS_IndexedMapOfPaveBlock& aMPBOn1 = aFI1.PaveBlocksOn();
  const BOPDS_IndexedMapOfPaveBlock& aMPBIn1 = aFI1.PaveBlocksIn();
  //
  const BOPDS_IndexedMapOfPaveBlock& aMPBOn2 = aFI2.PaveBlocksOn();
  aNbPB = aMPBOn2.Extent();
  for (i = 1; i <= aNbPB; ++i) {
    const Handle(BOPDS_PaveBlock)& aPB = aMPBOn2(i);
    bRet = aMPBOn1.Contains(aPB) || aMPBIn1.Contains(aPB);
    if (bRet) {
      return bRet;
    }
  }
  //
  const BOPDS_IndexedMapOfPaveBlock& aMPBIn2 = aFI2.PaveBlocksIn();
  aNbPB = aMPBIn2.Extent();
  for (i = 1; i <= aNbPB; ++i) {
    const Handle(BOPDS_PaveBlock)& aPB = aMPBIn2(i);
    bRet = aMPBOn1.Contains(aPB) || aMPBIn1.Contains(aPB);
    if (bRet) {
      return bRet;
    }
  }
  return bRet;
}

/*
//DEBf
    {
      TopoDS_Compound aCx;
      BRep_Builder aBBx;
      BOPCol_ListIteratorOfListOfShape aItx;
      //
      aBBx.MakeCompound(aCx);
      aBBx.Add(aCx, aFF);
      aItx.Initialize(aLE);
      for (; aItx.More(); aItx.Next()) {
      const TopoDS_Shape& aEx=aItx.Value();
      aBBx.Add(aCx, aEx);
      }
      int a=0;
    }
    //DEBt
*/
