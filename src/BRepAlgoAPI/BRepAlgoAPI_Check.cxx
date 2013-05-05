// Created on: 2012-12-17
// Created by: Eugeny MALTCHIKOV
// Copyright (c) 2012-2012 OPEN CASCADE SAS
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

#include <BRepAlgoAPI_Check.ixx>
#include <BOPAlgo_ArgumentAnalyzer.hxx>
#include <BRepBuilderAPI_Copy.hxx>
#include <BRepCheck_Analyzer.hxx>

//=======================================================================
//function : BRepAlgoAPI_Check
//purpose  : 
//=======================================================================
  BRepAlgoAPI_Check::BRepAlgoAPI_Check()
: myAnalyzer(NULL)
{
}

//=======================================================================
//function : BRepAlgoAPI_Check
//purpose  : 
//=======================================================================
  BRepAlgoAPI_Check::BRepAlgoAPI_Check(const TopoDS_Shape& theS,
                                       const Standard_Boolean bTestSE,
                                       const Standard_Boolean bTestSI)
{
  Init(theS, TopoDS_Shape(), BOPAlgo_UNKNOWN, bTestSE, bTestSI);
  //
  Perform();
}

//=======================================================================
//function : BRepAlgoAPI_Check
//purpose  : 
//=======================================================================
  BRepAlgoAPI_Check::BRepAlgoAPI_Check(const TopoDS_Shape& theS1,
                                       const TopoDS_Shape& theS2,
                                       const BOPAlgo_Operation theOp,
                                       const Standard_Boolean bTestSE,
                                       const Standard_Boolean bTestSI)
{
  Init(theS1, theS2, theOp, bTestSE, bTestSI);
  //
  Perform();
}

//=======================================================================
//function : ~BRepAlgoAPI_Check
//purpose  : 
//=======================================================================
  BRepAlgoAPI_Check::~BRepAlgoAPI_Check()
{
  if(myAnalyzer){
    delete myAnalyzer;
    myAnalyzer=NULL;
  }
  myResult.Clear();
}

//=======================================================================
//function : SetData
//purpose  : 
//=======================================================================
  void BRepAlgoAPI_Check::SetData(const TopoDS_Shape& theS,
                                  const Standard_Boolean bTestSE,
                                  const Standard_Boolean bTestSI)
{
  Init(theS, TopoDS_Shape(), BOPAlgo_UNKNOWN, bTestSE, bTestSI);
}

//=======================================================================
//function : SetData
//purpose  : 
//=======================================================================
  void BRepAlgoAPI_Check::SetData(const TopoDS_Shape& theS1,
                                  const TopoDS_Shape& theS2,
                                  const BOPAlgo_Operation theOp,
                                  const Standard_Boolean bTestSE,
                                  const Standard_Boolean bTestSI)
{
  Init(theS1, theS2, theOp, bTestSE, bTestSI);
}


//=======================================================================
//function : Init
//purpose  : 
//=======================================================================
  void BRepAlgoAPI_Check::Init(const TopoDS_Shape& theS1,
                               const TopoDS_Shape& theS2,
                               const BOPAlgo_Operation theOp,
                               const Standard_Boolean bTestSE,
                               const Standard_Boolean bTestSI)
{
  myResult.Clear();
  myS1 = theS1.IsNull() ? theS1 : BRepBuilderAPI_Copy(theS1).Shape();
  myS2 = theS2.IsNull() ? theS2 : BRepBuilderAPI_Copy(theS2).Shape();
  //
  myAnalyzer = new BOPAlgo_ArgumentAnalyzer();
  //
  myAnalyzer->SetShape1(myS1);
  myAnalyzer->SetShape2(myS2);
  myAnalyzer->OperationType()=theOp;
  myAnalyzer->ArgumentTypeMode() = Standard_True;
  myAnalyzer->SmallEdgeMode() = bTestSE;
  myAnalyzer->SelfInterMode() = bTestSI;
}

//=======================================================================
//function : Result
//purpose  : 
//=======================================================================
  const BOPAlgo_ListOfCheckResult& BRepAlgoAPI_Check::Result()
{
  return myResult;
}

//=======================================================================
//function : IsValid
//purpose  : 
//=======================================================================
  Standard_Boolean BRepAlgoAPI_Check::IsValid()
{
  return myResult.IsEmpty();
}

//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================
  void BRepAlgoAPI_Check::Perform()
{
  Standard_Boolean isS1, isS2;
  //incompatibility of shape types, small edges and self-interference
  myAnalyzer->Perform();
  if (myAnalyzer->HasFaulty()) {
    myResult = myAnalyzer->GetCheckResult();
  }

  //topological validity
  isS1 = !myS1.IsNull();
  isS2 = !myS2.IsNull();
  if (isS1) {
    BRepCheck_Analyzer anS1(myS1);
    isS1 = anS1.IsValid();
  } else {
    isS1 = Standard_True;
  }
  //
  if (isS2) {
    BRepCheck_Analyzer anS2(myS2);
    isS2 = anS2.IsValid();
  } else {
    isS2 = Standard_True;
  }
  if (!isS1 || !isS2) {
    BOPAlgo_CheckResult aRes;
    aRes.SetCheckStatus(BOPAlgo_NotValid);
    if (!isS1) {
      aRes.SetShape1(myS1);
    }
    if (!isS1) {
      aRes.SetShape2(myS2);
    }
    myResult.Append(aRes);
  }
}


