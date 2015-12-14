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

#include <BOPAlgo_PaveFiller.ixx>
//
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Face.hxx>
#include <BRep_Tool.hxx>
#include <BRep_Builder.hxx>
#include <BRepBndLib.hxx>
//
#include <BOPCol_MapOfInteger.hxx>
#include <BOPCol_NCVector.hxx>
#include <BOPCol_Parallel.hxx>
//
#include <IntTools_Context.hxx>
//
#include <BOPDS_Iterator.hxx>
#include <BOPDS_VectorOfInterfVF.hxx>
#include <BOPDS_Interf.hxx>
#include <BOPDS_SubIterator.hxx>
#include <BOPDS_MapOfPaveBlock.hxx>
#include <BOPDS_FaceInfo.hxx>

//=======================================================================
//class    : BOPAlgo_VertexFace
//purpose  : 
//=======================================================================
class BOPAlgo_VertexFace : public BOPAlgo_Algo {
 public:
  DEFINE_STANDARD_ALLOC

  BOPAlgo_VertexFace() : 
    BOPAlgo_Algo(),
    myIV(-1), myIF(-1), myIVx(-1), 
    myFlag(-1), myT1(-1.),  myT2(-1.) {
  }
  //
  virtual ~BOPAlgo_VertexFace(){
  }
  //
  void SetIndices(const Standard_Integer nV,
                  const Standard_Integer nF,
                  const Standard_Integer nVx) {
    myIV=nV;
    myIF=nF;
    myIVx=nVx;
  }
  //
  void Indices(Standard_Integer& nV,
               Standard_Integer& nF,
               Standard_Integer& nVx) const {
    nV=myIV;
    nF=myIF;
    nVx=myIVx;
  }
  //
  void SetVertex(const TopoDS_Vertex& aV) {
    myV=aV;
  }
  //
  const TopoDS_Vertex& Vertex()const {
    return myV;
  }
  //
  void SetFace(const TopoDS_Face& aF) {
    myF=aF;
  }
  //
  const TopoDS_Face& Face()const {
    return myF;
  }
  //
  Standard_Integer Flag()const {
    return myFlag;
  }
  //
  void Parameters(Standard_Real& aT1,
                  Standard_Real& aT2)const {
    aT1=myT1;
    aT2=myT2;
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
    myFlag=myContext->ComputeVF(myV, myF, myT1, myT2);
  }
  //
 protected:
  Standard_Integer myIV;
  Standard_Integer myIF;
  Standard_Integer myIVx;
  Standard_Integer myFlag;
  Standard_Real myT1;
  Standard_Real myT2;
  TopoDS_Vertex myV;
  TopoDS_Face myF;
  Handle(IntTools_Context) myContext;
};
//=======================================================================
typedef BOPCol_NCVector<BOPAlgo_VertexFace>
  BOPAlgo_VectorOfVertexFace; 
//
typedef BOPCol_ContextFunctor 
  <BOPAlgo_VertexFace,
  BOPAlgo_VectorOfVertexFace,
  Handle(IntTools_Context), 
  IntTools_Context> BOPAlgo_VertexFaceFunctor;
//
typedef BOPCol_ContextCnt 
  <BOPAlgo_VertexFaceFunctor,
  BOPAlgo_VectorOfVertexFace,
  Handle(IntTools_Context)> BOPAlgo_VertexFaceCnt;
//
//=======================================================================
// function: PerformVF
// purpose: 
//=======================================================================
void BOPAlgo_PaveFiller::PerformVF()
{
  Standard_Boolean bJustAdd;
  Standard_Integer iSize, nV, nF, nVSD, iFlag, nVx, aNbVF, k;
  Standard_Real aT1, aT2, aTolF, aTolV;
  BRep_Builder aBB;
  BOPAlgo_VectorOfVertexFace aVVF; 
  //
  myErrorStatus=0;
  //
  myIterator->Initialize(TopAbs_VERTEX, TopAbs_FACE);
  iSize=myIterator->ExpectedLength();
  if (iSize) {
    //
    BOPDS_VectorOfInterfVF& aVFs=myDS->InterfVF();
    aVFs.SetIncrement(iSize);
    //
    for (; myIterator->More(); myIterator->Next()) {
      myIterator->Value(nV, nF, bJustAdd);
      if(bJustAdd) {
        continue;
      }
      //
      if (myDS->IsSubShape(nV, nF)) {
        continue;
      }
      //
      if (myDS->HasInterfShapeSubShapes(nV, nF)) {
        myDS->ChangeFaceInfo(nF);
        continue;
      }
      //
      nVx=nV;
      if (myDS->HasShapeSD(nV, nVSD)) {
        nVx=nVSD;
      }
      //
      if (myDS->HasInterf(nVx, nF)) {
        continue;
      }
      //
      myDS->ChangeFaceInfo(nF);// !
      //
      const TopoDS_Vertex& aV=(*(TopoDS_Vertex *)(&myDS->Shape(nVx))); 
      const TopoDS_Face& aF=(*(TopoDS_Face *)(&myDS->Shape(nF))); 
      //
      BOPAlgo_VertexFace& aVertexFace=aVVF.Append1();
      //
      aVertexFace.SetIndices(nV, nF, nVx);
      aVertexFace.SetVertex(aV);
      aVertexFace.SetFace(aF);
      aVertexFace.SetProgressIndicator(myProgressIndicator);
    }//for (; myIterator->More(); myIterator->Next()) {
    //
    aNbVF=aVVF.Extent();
    //================================================================
    BOPAlgo_VertexFaceCnt::Perform(myRunParallel, aVVF, myContext);
    //================================================================
    //
    for (k=0; k < aNbVF; ++k) {
      const BOPAlgo_VertexFace& aVertexFace=aVVF(k);
      // 
      iFlag=aVertexFace.Flag();
      if (iFlag) {
        continue;
      }
      //
      aVertexFace.Indices(nV, nF, nVx);
      aVertexFace.Parameters(aT1, aT2);
      const TopoDS_Vertex& aV=aVertexFace.Vertex();
      const TopoDS_Face& aF=aVertexFace.Face();
      // 1
      BOPDS_InterfVF& aVF=aVFs.Append1();
      aVF.SetIndices(nVx, nF);
      aVF.SetUV(aT1, aT2);
      // 2
      myDS->AddInterf(nVx, nF);
      // 3
      BOPDS_FaceInfo& aFI=myDS->ChangeFaceInfo(nF);
      BOPCol_MapOfInteger& aMVIn=aFI.ChangeVerticesIn();
      aMVIn.Add(nVx);
      // 4
      aTolV = BRep_Tool::Tolerance(aV);
      aTolF = BRep_Tool::Tolerance(aF);
      if (aTolV < aTolF) {
        aBB.UpdateVertex(aV, aTolF);
        BOPDS_ShapeInfo& aSIV = myDS->ChangeShapeInfo(nVx);
        Bnd_Box& aBoxV = aSIV.ChangeBox();
        BRepBndLib::Add(aV, aBoxV);
      }
    }//for (k=0; k < aNbVF; ++k) {
  }// if (iSize) {
  else {
    iSize=10;
    BOPDS_VectorOfInterfVF& aVFs=myDS->InterfVF();
    aVFs.SetIncrement(iSize);
  }
  //
  TreatVerticesEE();
}
//=======================================================================
//function : TreatVerticesEE
//purpose  : 
//=======================================================================
void BOPAlgo_PaveFiller::TreatVerticesEE()
{
  Standard_Integer i, aNbS,aNbEEs, nF, nV, iFlag;
  Standard_Real aT1, aT2;
  BOPCol_ListIteratorOfListOfInteger aItLI;
  Handle(NCollection_BaseAllocator) aAllocator;
  //
  aAllocator=
    NCollection_BaseAllocator::CommonBaseAllocator();
  BOPCol_ListOfInteger aLIV(aAllocator), aLIF(aAllocator);
  BOPCol_MapOfInteger aMI(100, aAllocator);
  BOPDS_MapOfPaveBlock aMPBF(100, aAllocator);
  //
  myErrorStatus=0;
  //
  
  aNbS=myDS->NbSourceShapes();
  //
  BOPDS_VectorOfInterfEE& aEEs=myDS->InterfEE();
  aNbEEs=aEEs.Extent();
  for (i=0; i<aNbEEs; ++i) {
    BOPDS_InterfEE& aEE=aEEs(i);
    if (aEE.HasIndexNew()) {
      nV=aEE.IndexNew();
      if (aMI.Add(nV)) {
        aLIV.Append(nV);
      }   
    }   
  }
  if (!aLIV.Extent()) {
    aAllocator.Nullify();
    return;
  }
  //
  aNbS=myDS->NbSourceShapes();
  for (nF=0; nF<aNbS; ++nF) {
    const BOPDS_ShapeInfo& aSI=myDS->ShapeInfo(nF);
    if (aSI.ShapeType()==TopAbs_FACE) {
      aLIF.Append(nF);
    }
  }
  if (!aLIF.Extent()) {
    aAllocator.Nullify();
    return;
  }
  //-------------------------------------------------------------
  BOPDS_VectorOfInterfVF& aVFs=myDS->InterfVF();
  //
  BOPDS_SubIterator aIt(aAllocator);
  //
  aIt.SetDS(myDS);
  aIt.SetSubSet1(aLIF);
  aIt.SetSubSet2(aLIV);
  aIt.Prepare();
  aIt.Initialize();
  for (; aIt.More(); aIt.Next()) {
    aIt.Value(nV, nF);
    //
    BOPDS_FaceInfo& aFI=myDS->ChangeFaceInfo(nF);
    const BOPCol_MapOfInteger& aMVOn=aFI.VerticesOn();
    //
    if (!aMVOn.Contains(nV)) {
      const TopoDS_Vertex& aV=(*(TopoDS_Vertex *)(&myDS->Shape(nV))); 
      const TopoDS_Face& aF=(*(TopoDS_Face *)(&myDS->Shape(nF))); 
      iFlag=myContext->ComputeVF(aV, aF, aT1, aT2);
      if (!iFlag) {
        // 1
        BOPDS_InterfVF& aVF=aVFs.Append1();
        i=aVFs.Extent()-1;
        aVF.SetIndices(nV, nF);
        aVF.SetUV(aT1, aT2);
        // 2
        myDS->AddInterf(nV, nF);
        //
        BOPCol_MapOfInteger& aMVIn=aFI.ChangeVerticesIn();
        aMVIn.Add(nV);
      }
    }
  }
}
