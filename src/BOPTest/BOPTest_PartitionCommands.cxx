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

#include <BOPTest.ixx>

#include <stdio.h>
#include <string.h>
#include <DBRep.hxx>
#include <Draw.hxx>
#include <Draw_Color.hxx>
#include <DrawTrSurf.hxx>

#include <TopoDS_Shape.hxx>
//
#include <BOPAlgo_Builder.hxx>
#include <BOPAlgo_PaveFiller.hxx>
#include <BOPAlgo_Operation.hxx>
#include <BOPAlgo_BOP.hxx>
#include <BOPAlgo_Section.hxx>
//
#include <BOPTest_DrawableShape.hxx>
#include <BOPTest_Objects.hxx>

#include <OSD_Timer.hxx>

static Standard_Integer bfillds  (Draw_Interpretor&, Standard_Integer, const char**); 
static Standard_Integer bbuild   (Draw_Interpretor&, Standard_Integer, const char**);
static Standard_Integer bbop     (Draw_Interpretor&, Standard_Integer, const char**);

//=======================================================================
//function : PartitionCommands
//purpose  : 
//=======================================================================
void BOPTest::PartitionCommands(Draw_Interpretor& theCommands)
{
  static Standard_Boolean done = Standard_False;
  if (done) return;
  done = Standard_True;
  // Chapter's name
  const char* g = "BOPTest commands";
  // Commands  
  theCommands.Add("bfillds", "use bfillds [-t]"  , __FILE__, bfillds, g);
  theCommands.Add("bbuild" , "use bbuild r [-t]" , __FILE__, bbuild, g);
  theCommands.Add("bbop"   , "use bbop r op [-t]", __FILE__, bbop, g);
}
//=======================================================================
//function : bfillds
//purpose  : 
//=======================================================================
Standard_Integer bfillds(Draw_Interpretor& di, 
                         Standard_Integer n, 
                         const char** a) 
{ 
  if (n > 2) {
    di << " use bfillds [-t]\n";
    return 0;
  }
  //
  char buf[32];
  Standard_Boolean bRunParallel, bShowTime;
  Standard_Integer i, aNbS, iErr;
  Standard_Real aTol;
  BOPCol_ListIteratorOfListOfShape aIt;
  BOPCol_ListOfShape aLC;
  BOPCol_ListOfShape& aLS=BOPTest_Objects::Shapes();
  aNbS=aLS.Extent();
  if (!aNbS) {
    di << " no objects to process\n";
    return 0;
  }
  //
  bShowTime = Standard_False;
  //
  bRunParallel=BOPTest_Objects::RunParallel();
  aTol=BOPTest_Objects::FuzzyValue();
  //
  for (i=1; i<n; ++i) {
    if (!strcmp(a[i], "-t")) {
      bShowTime=Standard_True;
    }
    }
  //
  BOPCol_ListOfShape& aLT=BOPTest_Objects::Tools();
  //
  aIt.Initialize(aLS);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aS=aIt.Value();
    aLC.Append(aS);
  }
  //
  aIt.Initialize(aLT);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aS=aIt.Value();
     aLC.Append(aS);
  }
  //
  BOPAlgo_PaveFiller& aPF=BOPTest_Objects::PaveFiller();
  //
  aPF.SetArguments(aLC);
  aPF.SetRunParallel(bRunParallel);
  aPF.SetFuzzyValue(aTol);
  //
  OSD_Timer aTimer;
  aTimer.Start();
  //
  aPF.Perform();
  iErr=aPF.ErrorStatus();
  if (iErr) {
    Sprintf(buf, " error: %d\n",  iErr);
    di << buf;
    return 0;
  }
  //
  aTimer.Stop();
  //
  if (bShowTime)
  {
    Sprintf(buf, "  Tps: %7.2lf\n", aTimer.ElapsedTime());
    di << buf;
  }
  //
  return 0;
}
//=======================================================================
//function : bbuild
//purpose  : 
//=======================================================================
Standard_Integer bbuild(Draw_Interpretor& di,
                        Standard_Integer n, 
                        const char** a) 
{ 
  if (n<2) {
    di << " use bbuild r [-t]\n";
    return 0;
  }
  //
  BOPDS_PDS pDS=BOPTest_Objects::PDS();
  if (!pDS) {
    di << " prepare PaveFiller first\n";
    return 0;
  }
  //
  char buf[128];
  Standard_Boolean bRunParallel, bShowTime;
  Standard_Integer i, iErr;

  BOPCol_ListIteratorOfListOfShape aIt;
  //
  BOPAlgo_PaveFiller& aPF=BOPTest_Objects::PaveFiller();
  //
  BOPTest_Objects::SetBuilderDefault();
  BOPAlgo_Builder& aBuilder=BOPTest_Objects::Builder();
  aBuilder.Clear();
  //
  BOPCol_ListOfShape& aLSObj=BOPTest_Objects::Shapes();
  aIt.Initialize(aLSObj);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aS=aIt.Value();
    aBuilder.AddArgument(aS);
  }
  //
  BOPCol_ListOfShape& aLSTool=BOPTest_Objects::Tools();
  aIt.Initialize(aLSTool);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aS=aIt.Value();
    aBuilder.AddArgument(aS);
  }
  //
  bShowTime=Standard_False;
  bRunParallel=BOPTest_Objects::RunParallel();
  for (i=2; i<n; ++i) {
    if (!strcmp(a[i], "-t")) {
      bShowTime=Standard_True;
    }
  }
  aBuilder.SetRunParallel(bRunParallel);
  //
  //
  OSD_Timer aTimer;
  aTimer.Start();
  //
  aBuilder.PerformWithFiller(aPF); 
  iErr=aBuilder.ErrorStatus();
  if (iErr) {
    Sprintf(buf, " error: %d\n",  iErr);
    di << buf;
    return 0;
  }
  //
  aTimer.Stop();
  //
  if (bShowTime)
  {
    Sprintf(buf, "  Tps: %7.2lf\n", aTimer.ElapsedTime());
    di << buf;
  }
  //
  const TopoDS_Shape& aR=aBuilder.Shape();
  if (aR.IsNull()) {
    di << " null shape\n";
    return 0;
  }
  //
  DBRep::Set(a[1], aR);
  return 0;
}
//=======================================================================
//function : bbop
//purpose  : 
//=======================================================================
Standard_Integer bbop(Draw_Interpretor& di, 
                      Standard_Integer n, 
                      const char** a) 
{ 
  if (n<3) {
    di << " use bbop r op [-t]\n";
    return 0;
  }
  //
  BOPDS_PDS pDS=BOPTest_Objects::PDS();
  if (!pDS) {
    di << " prepare PaveFiller first\n";
    return 0;
  }
  //
  char buf[32];
  Standard_Boolean bRunParallel, bShowTime;
  Standard_Integer iErr, iOp, i;
  BOPAlgo_Operation aOp;
  BOPCol_ListIteratorOfListOfShape aIt; 
  //
  iOp=Draw::Atoi(a[2]);
  if (iOp<0 || iOp>4) {
    di << " invalid operation type\n";
    return 0;
  }
  aOp=(BOPAlgo_Operation)iOp;
  //
  bShowTime=Standard_False;
  bRunParallel=BOPTest_Objects::RunParallel();
  for (i=3; i<n; ++i) {
    if (!strcmp(a[i], "-t")) {
      bShowTime=Standard_True;
    }
  }
  //
  BOPAlgo_PaveFiller& aPF=BOPTest_Objects::PaveFiller();
  //
  BOPAlgo_Builder *pBuilder=NULL;
  
  if (aOp!=BOPAlgo_SECTION) { 
    pBuilder=&BOPTest_Objects::BOP();
  } 
  else {
    pBuilder=&BOPTest_Objects::Section();
  }
  //
  pBuilder->Clear();
  //
  BOPCol_ListOfShape& aLSObj=BOPTest_Objects::Shapes();
  aIt.Initialize(aLSObj);
  for (; aIt.More(); aIt.Next()) {
    const TopoDS_Shape& aS=aIt.Value();
    pBuilder->AddArgument(aS);
  }
  //
  if (aOp!=BOPAlgo_SECTION) {
    BOPAlgo_BOP *pBOP=(BOPAlgo_BOP *)pBuilder;
    //
    BOPCol_ListOfShape& aLSTools=BOPTest_Objects::Tools();
    aIt.Initialize(aLSTools);
    for (; aIt.More(); aIt.Next()) {
      const TopoDS_Shape& aS=aIt.Value();
      pBOP->AddTool(aS);
    }
    //
    pBOP->SetOperation(aOp);
  }
  else {
    BOPCol_ListOfShape& aLSTools=BOPTest_Objects::Tools();
    aIt.Initialize(aLSTools);
    for (; aIt.More(); aIt.Next()) {
      const TopoDS_Shape& aS=aIt.Value();
      pBuilder->AddArgument(aS);
    }
  }
  //
  pBuilder->SetRunParallel(bRunParallel);
  //
  OSD_Timer aTimer;
  aTimer.Start();
  //
  pBuilder->PerformWithFiller(aPF);
  iErr=pBuilder->ErrorStatus();
  if (iErr) {
    Sprintf(buf, " error: %d\n",  iErr);
    di << buf;
    return 0;
  }
  //
  aTimer.Stop();
  //
  if (bShowTime) {
    Sprintf(buf, "  Tps: %7.2lf\n", aTimer.ElapsedTime());
    di << buf;
  }
  //
  const TopoDS_Shape& aR=pBuilder->Shape();
  if (aR.IsNull()) {
    di << " null shape\n";
    return 0;
  }
  //
  BOPTest_Objects::SetBuilder(pBuilder);
  //
  DBRep::Set(a[1], aR);
  return 0;
}

