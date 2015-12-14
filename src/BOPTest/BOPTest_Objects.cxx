// Created by: Peter KURNEV
// Copyright (c) 1999-2014 OPEN CASCADE SAS
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

#include <BOPTest_Objects.ixx>

#include <NCollection_BaseAllocator.hxx>

static Handle(NCollection_BaseAllocator)& Allocator1();

//=======================================================================
//function : BOPTest_Session
//purpose  : 
//=======================================================================
class BOPTest_Session {
 public:
  //
  BOPTest_Session() {
    Init();
  };
  //
  ~BOPTest_Session(){
    Clear();
  };
  //
  // Init
  void Init() {
    Handle(NCollection_BaseAllocator) pA1, pA2;
    //
    pA1=NCollection_BaseAllocator::CommonBaseAllocator();
    pA2=NCollection_BaseAllocator::CommonBaseAllocator();
    //
    myPaveFiller=new BOPAlgo_PaveFiller(pA1);
    myBuilderDefault=new BOPAlgo_Builder(pA2);
    //
    myBuilder=myBuilderDefault;
    myRunParallel=Standard_False;
    myFuzzyValue=0.;
  };
  //
  // Clear
  void Clear() {
    if (myPaveFiller) {
      delete myPaveFiller;
      myPaveFiller=NULL;
    }
    //
    if (myBuilderDefault) {
      delete myBuilderDefault;
      myBuilderDefault=NULL;
    }
  };
  //
  // IsValid
  Standard_Boolean IsValid() const {
    return (myPaveFiller!=NULL);
  }
  // PaveFiller
  BOPAlgo_PaveFiller& PaveFiller() {
    return *myPaveFiller;
  };
  //
  // Builder
  BOPAlgo_Builder& Builder() {
    return *myBuilder;
  };
  // 
  // SetBuilder
  void SetBuilder(BOPAlgo_Builder* pBuilder) {
    myBuilder=pBuilder;
  };
  //
  // SetBuilderDef
  void SetBuilderDefault() {
    myBuilder=myBuilderDefault;
  };
  //
  BOPCol_ListOfShape& Shapes() {
    return myShapes;
  }
  //
  BOPCol_ListOfShape& Tools() {
    return myTools;
  }
  //
  void SetRunParallel(const Standard_Boolean bFlag) {
    myRunParallel=bFlag;
  };
  //
  Standard_Boolean RunParallel()const {
    return myRunParallel;
  };
  //
  void SetFuzzyValue(const Standard_Real aValue) {
    myFuzzyValue=aValue;
  };
  //
  Standard_Real FuzzyValue()const {
    return myFuzzyValue;
  };
  //
protected:
  //
  BOPTest_Session(const BOPTest_Session&);
  BOPTest_Session& operator=(const BOPTest_Session&);
  //
protected:
  //
  BOPAlgo_PaveFiller* myPaveFiller;
  BOPAlgo_Builder* myBuilder;
  BOPAlgo_Builder* myBuilderDefault;
  //
  BOPCol_ListOfShape myShapes;
  BOPCol_ListOfShape myTools;
  Standard_Boolean myRunParallel;
  Standard_Real myFuzzyValue;
};
//
//=======================================================================
//function : GetSession
//purpose  : 
//=======================================================================
static BOPTest_Session& GetSession()
{
  static BOPTest_Session* pSession=new BOPTest_Session;
  //
  if (!pSession->IsValid()) {
    pSession->Init();
  }
  return *pSession;
}
//
//=======================================================================
//function : Init
//purpose  : 
//=======================================================================
void BOPTest_Objects::Init() 
{
  GetSession().Init();
}
//=======================================================================
//function : Clear
//purpose  : 
//=======================================================================
void BOPTest_Objects::Clear() 
{
  GetSession().Clear();
  Shapes().Clear();
  Tools().Clear();
}
//=======================================================================
//function : PaveFiller
//purpose  : 
//=======================================================================
BOPAlgo_PaveFiller& BOPTest_Objects::PaveFiller() 
{
  return GetSession().PaveFiller();
}
//=======================================================================
//function : PDS
//purpose  : 
//=======================================================================
BOPDS_PDS BOPTest_Objects::PDS() 
{
  return BOPTest_Objects::PaveFiller().PDS();
}
//=======================================================================
//function : Builder
//purpose  : 
//=======================================================================
BOPAlgo_Builder& BOPTest_Objects::Builder()
{
  return GetSession().Builder();
}
//=======================================================================
//function : SetBuilder
//purpose  : 
//=======================================================================
void BOPTest_Objects::SetBuilder(const BOPAlgo_PBuilder& theBuilder)
{
  BOPAlgo_Builder* pB;
  //
  pB=(BOPAlgo_Builder*)theBuilder;
  GetSession().SetBuilder(pB);
}
//=======================================================================
//function : SetBuilderDefault
//purpose  : 
//=======================================================================
void BOPTest_Objects::SetBuilderDefault()
{
  GetSession().SetBuilderDefault();
}
//=======================================================================
//function : BOP
//purpose  : 
//=======================================================================
BOPAlgo_BOP& BOPTest_Objects::BOP()
{
  static BOPAlgo_BOP sBOP(Allocator1());
  return sBOP;
}
//=======================================================================
//function : Section
//purpose  : 
//=======================================================================
BOPAlgo_Section& BOPTest_Objects::Section()
{
  static BOPAlgo_Section sSection(Allocator1());
  return sSection;
}
//=======================================================================
//function : Shapes
//purpose  : 
//=======================================================================
BOPCol_ListOfShape& BOPTest_Objects::Shapes()
{
  return GetSession().Shapes();
}
//=======================================================================
//function : Tools
//purpose  : 
//=======================================================================
BOPCol_ListOfShape& BOPTest_Objects::Tools()
{
  return GetSession().Tools();
}
//=======================================================================
//function : SetRunParallel
//purpose  : 
//=======================================================================
void BOPTest_Objects::SetRunParallel(const Standard_Boolean bFlag)
{
  GetSession().SetRunParallel(bFlag);
}
//=======================================================================
//function : RunParallel
//purpose  : 
//=======================================================================
Standard_Boolean BOPTest_Objects::RunParallel()
{
  return GetSession().RunParallel();
}
//=======================================================================
//function : SetFuzzyValue
//purpose  : 
//=======================================================================
void BOPTest_Objects::SetFuzzyValue(const Standard_Real aValue)
{
  GetSession().SetFuzzyValue(aValue);
}
//=======================================================================
//function : FuzzyValue
//purpose  : 
//=======================================================================
Standard_Real BOPTest_Objects::FuzzyValue()
{
  return GetSession().FuzzyValue();
}
//=======================================================================
//function : Allocator1
//purpose  : 
//=======================================================================
Handle(NCollection_BaseAllocator)& Allocator1() 
{
  static Handle(NCollection_BaseAllocator) sAL1=
    NCollection_BaseAllocator::CommonBaseAllocator();
  return sAL1;
}
