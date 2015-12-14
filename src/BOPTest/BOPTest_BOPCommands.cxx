// Created on: 2000-03-16
// Created by: Peter KURNEV
// Copyright (c) 2000-2014 OPEN CASCADE SAS
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

#include <TCollection_AsciiString.hxx>

#include <DBRep.hxx>
#include <DrawTrSurf.hxx>
#include <Draw_Color.hxx>
#include <Draw.hxx>

#include <NCollection_BaseAllocator.hxx>

#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Iterator.hxx>
//
#include <BRep_Builder.hxx>

#include <IntTools_FaceFace.hxx>
#include <IntTools_Curve.hxx>
#include <IntTools_PntOn2Faces.hxx>

#include <BOPCol_ListOfShape.hxx>

#include <BOPDS_DS.hxx>

#include <BOPAlgo_PaveFiller.hxx>
#include <BOPAlgo_Operation.hxx>
#include <BOPAlgo_BOP.hxx>
#include <BOPAlgo_MakerVolume.hxx>
#include <BOPAlgo_Section.hxx>

#include <BRepAlgoAPI_BooleanOperation.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Section.hxx>

#include <BOPTest_DrawableShape.hxx>
#include <BOPTest_Objects.hxx>

//
static BOPAlgo_PaveFiller* pPF=NULL;
//

static
  Standard_Integer bopsmt(Draw_Interpretor& di,
                          Standard_Integer n,
                          const char** a,
                          const BOPAlgo_Operation aOp);
//
static
  Standard_Integer bsmt (Draw_Interpretor& di, 
                       Standard_Integer n, 
                       const char** a,
                       const BOPAlgo_Operation aOp);
//
static Standard_Integer bop       (Draw_Interpretor&, Standard_Integer, const char**);
static Standard_Integer bopsection(Draw_Interpretor&, Standard_Integer, const char**);
static Standard_Integer boptuc    (Draw_Interpretor&, Standard_Integer, const char**);
static Standard_Integer bopcut    (Draw_Interpretor&, Standard_Integer, const char**);
static Standard_Integer bopfuse   (Draw_Interpretor&, Standard_Integer, const char**);
static Standard_Integer bopcommon (Draw_Interpretor&, Standard_Integer, const char**);
//
static Standard_Integer bsection  (Draw_Interpretor&, Standard_Integer, const char**);
static Standard_Integer btuc      (Draw_Interpretor&, Standard_Integer, const char**);
static Standard_Integer bcut      (Draw_Interpretor&, Standard_Integer, const char**);
static Standard_Integer bfuse     (Draw_Interpretor&, Standard_Integer, const char**);
static Standard_Integer bcommon   (Draw_Interpretor&, Standard_Integer, const char**);
//
static Standard_Integer bopcurves (Draw_Interpretor&, Standard_Integer, const char**);
static Standard_Integer bopnews   (Draw_Interpretor&, Standard_Integer, const char**);
static Standard_Integer mkvolume   (Draw_Interpretor&, Standard_Integer, const char**);

//=======================================================================
//function : BOPCommands
//purpose  : 
//=======================================================================
  void BOPTest::BOPCommands(Draw_Interpretor& theCommands)
{
  static Standard_Boolean done = Standard_False;
  if (done) return;
  done = Standard_True;
  // Chapter's name
  const char* g = "BOPTest commands";
  // Commands
  
  theCommands.Add("bop"       , "use bop s1 s2" , __FILE__, bop, g);
  theCommands.Add("bopcommon" , "use bopcommon r"     , __FILE__, bopcommon, g);
  theCommands.Add("bopfuse"   , "use bopfuse r"       , __FILE__,bopfuse, g);
  theCommands.Add("bopcut"    , "use bopcut r"        , __FILE__,bopcut, g);
  theCommands.Add("boptuc"    , "use boptuc r"        , __FILE__,boptuc, g);
  theCommands.Add("bopsection", "use bopsection r"    , __FILE__,bopsection, g);
  //
  theCommands.Add("bcommon" , "use bcommon r s1 s2" , __FILE__,bcommon, g);
  theCommands.Add("bfuse"   , "use bfuse r s1 s2"   , __FILE__,bfuse, g);
  theCommands.Add("bcut"    , "use bcut r s1 s2"    , __FILE__,bcut, g);
  theCommands.Add("btuc"    , "use btuc r s1 s2"    , __FILE__,btuc, g);
  theCommands.Add("bsection", "use bsection r s1 s2 [-n2d/-n2d1/-n2d2] [-na]", 
                                                      __FILE__, bsection, g);
  //
  theCommands.Add("bopcurves", "use bopcurves F1 F2 [-2d/-2d1/-2d2]",
                                                      __FILE__, bopcurves, g);
  theCommands.Add("bopnews"  , "use  bopnews -v[e,f]"      , __FILE__, bopnews, g);
  theCommands.Add("mkvolume", "make solids from set of shapes.\nmkvolume r b1 b2 ... [-c] [-ni]", 
                  __FILE__, mkvolume , g);
}

//=======================================================================
//function : bop
//purpose  : 
//=======================================================================
Standard_Integer bop(Draw_Interpretor& di, 
                     Standard_Integer n, 
                     const char** a)
{
  char buf[32];
  Standard_Boolean bRunParallel;
  Standard_Integer iErr;
  Standard_Real aTol;
  TopoDS_Shape aS1, aS2;
  BOPCol_ListOfShape aLC;
  //
  if (n != 3) {
    di << " use bop s1 s2 \n";
    return 0;
  }
  //
  aS1=DBRep::Get(a[1]);
  aS2=DBRep::Get(a[2]);
  //
  if (aS1.IsNull() || aS2.IsNull()) {
    di << " null shapes are not allowed \n";
    return 0;
  }
  //
  aTol=BOPTest_Objects::FuzzyValue();
  bRunParallel=BOPTest_Objects::RunParallel();
  //
  aLC.Append(aS1);
  aLC.Append(aS2);
  //
  if (pPF!=NULL) {
    delete pPF;
    pPF=NULL;
  }
  Handle(NCollection_BaseAllocator)aAL=
    NCollection_BaseAllocator::CommonBaseAllocator();
  pPF=new BOPAlgo_PaveFiller(aAL);
  //
  pPF->SetArguments(aLC);
  pPF->SetFuzzyValue(aTol);
  pPF->SetRunParallel(bRunParallel);
  //
  pPF->Perform();
  iErr=pPF->ErrorStatus();
  if (iErr) {
    Sprintf(buf, " ErrorStatus : %d\n",  iErr);
    di << buf;
    return 0;
  }
  //
  return 0;
}
//=======================================================================
//function : bopcommon
//purpose  : 
//=======================================================================
Standard_Integer bopcommon (Draw_Interpretor& di, 
                            Standard_Integer n, 
                            const char** a)
{
  return bopsmt(di, n, a, BOPAlgo_COMMON);
}
//=======================================================================
//function : bopfuse
//purpose  : 
//=======================================================================
Standard_Integer bopfuse(Draw_Interpretor& di, 
                         Standard_Integer n, 
                         const char** a)
{
  return bopsmt(di, n, a, BOPAlgo_FUSE);
}
//=======================================================================
//function : bopcut
//purpose  : 
//=======================================================================
Standard_Integer bopcut(Draw_Interpretor& di, 
                        Standard_Integer n, 
                        const char** a)
{
  return bopsmt(di, n, a, BOPAlgo_CUT);
}
//=======================================================================
//function : boptuc
//purpose  : 
//=======================================================================
Standard_Integer boptuc(Draw_Interpretor& di, 
                        Standard_Integer n, 
                        const char** a)
{
  return bopsmt(di, n, a, BOPAlgo_CUT21);
}
//=======================================================================
//function : bopsmt
//purpose  : 
//=======================================================================
Standard_Integer bopsmt(Draw_Interpretor& di,
                        Standard_Integer n,
                        const char** a,
                        const BOPAlgo_Operation aOp)
{
  if (n<2) {
    di << " use bopsmt r\n";
    return 0;
  }
  //
  if (!pPF) {
    di << " prepare PaveFiller first\n";
    return 0;
  }
  //
  if (pPF->ErrorStatus()) {
    di << " PaveFiller has not been done\n";
    return 0;
  }
  //
  char buf[64];
  Standard_Boolean bRunParallel;
  Standard_Integer aNb, iErr;
  BOPAlgo_BOP aBOP;
  //
  const BOPCol_ListOfShape& aLC=pPF->Arguments();
  aNb=aLC.Extent();
  if (aNb!=2) {
    Sprintf (buf, " wrong number of arguments %s\n", aNb);
    di << buf;
    return 0;
  }
  // 
  bRunParallel=BOPTest_Objects::RunParallel();
  //
  const TopoDS_Shape& aS1=aLC.First();
  const TopoDS_Shape& aS2=aLC.Last();
  //
  aBOP.AddArgument(aS1);
  aBOP.AddTool(aS2);
  aBOP.SetOperation(aOp);
  aBOP.SetRunParallel (bRunParallel);
  //
  aBOP.PerformWithFiller(*pPF);
  iErr=aBOP.ErrorStatus();
  if (iErr) {
    Sprintf(buf, " ErrorStatus : %d\n",  iErr);
    di << buf;
    return 0;
  }
  //
  const TopoDS_Shape& aR=aBOP.Shape();
  if (aR.IsNull()) {
    di << " null shape\n";
    return 0;
  }
  //
  DBRep::Set(a[1], aR);
  return 0;
}
//=======================================================================
//function : bopsection
//purpose  : 
//=======================================================================
Standard_Integer bopsection(Draw_Interpretor& di, 
                            Standard_Integer n, 
                            const char** a)
{
  if (n<2) {
    di << " use bopsection r\n";
    return 0;
  }
  //
  if (!pPF) {
    di << " prepare PaveFiller first\n";
    return 0;
  }
  //
  if (pPF->ErrorStatus()) {
    di << " PaveFiller has not been done\n";
    return 0;
  }
  //
  char buf[64];
  Standard_Boolean bRunParallel;
  Standard_Integer aNb, iErr;
  BOPAlgo_Section aBOP;
  //
  const BOPCol_ListOfShape& aLC=pPF->Arguments();
  aNb=aLC.Extent();
  if (aNb!=2) {
    Sprintf (buf, " wrong number of arguments %s\n", aNb);
    di << buf;
    return 0;
  }
  //
  bRunParallel=BOPTest_Objects::RunParallel();
  //
  const TopoDS_Shape& aS1=aLC.First();
  const TopoDS_Shape& aS2=aLC.Last();
  //
  aBOP.AddArgument(aS1);
  aBOP.AddArgument(aS2);
  aBOP.SetRunParallel (bRunParallel);
  //
  aBOP.PerformWithFiller(*pPF);
  iErr=aBOP.ErrorStatus();
  if (iErr) {
    Sprintf(buf, " ErrorStatus : %d\n",  iErr);
    di << buf;
    return 0;
  }
  //
  const TopoDS_Shape& aR=aBOP.Shape();
  if (aR.IsNull()) {
    di << " null shape\n";
    return 0;
  }
  //
  DBRep::Set(a[1], aR);
  return 0;
}
//=======================================================================
//function : bcommon
//purpose  : 
//=======================================================================
Standard_Integer bcommon (Draw_Interpretor& di, 
                          Standard_Integer n, 
                          const char** a)
{
  return bsmt(di, n, a, BOPAlgo_COMMON);
}
//=======================================================================
//function : bfuse
//purpose  : 
//=======================================================================
Standard_Integer bfuse (Draw_Interpretor& di, 
                        Standard_Integer n, 
                        const char** a)
{
  return bsmt(di, n, a, BOPAlgo_FUSE);
}
//=======================================================================
//function : bcut
//purpose  : 
//=======================================================================
Standard_Integer bcut (Draw_Interpretor& di, 
                       Standard_Integer n, 
                       const char** a)
{
  return bsmt(di, n, a, BOPAlgo_CUT);
}
//=======================================================================
//function : btuc
//purpose  : 
//=======================================================================
Standard_Integer btuc (Draw_Interpretor& di, 
                       Standard_Integer n, 
                       const char** a)
{
  return bsmt(di, n, a, BOPAlgo_CUT21);
}
//=======================================================================
//function : bsection
//purpose  : 
//=======================================================================
Standard_Integer  bsection(Draw_Interpretor& di, 
                           Standard_Integer n, 
                           const char** a)
{
  if (n < 4) {
    di << "use bsection r s1 s2 [-n2d/-n2d1/-n2d2] [-na] [tol]\n";
    return 0;
  }
  //
  TopoDS_Shape aS1, aS2;
  //
  aS1=DBRep::Get(a[2]);
  aS2=DBRep::Get(a[3]);
  if (aS1.IsNull() || aS2.IsNull()) {
    di << " Null shapes are not allowed \n";
    return 0;
  }
  // 
  char buf[80];
  Standard_Boolean bRunParallel, bApp, bPC1, bPC2;
  Standard_Integer i, iErr;
  Standard_Real aTol;
  //
  bApp = Standard_True;
  bPC1 = Standard_True;
  bPC2 = Standard_True;
  aTol = BOPTest_Objects::FuzzyValue(); 
  bRunParallel = BOPTest_Objects::RunParallel();
  //
  for (i = 4; i < n; ++i) {
    if (!strcmp(a[i], "-n2d")) {
      bPC1 = Standard_False;
      bPC2 = Standard_False;
    }
    else if (!strcmp(a[i], "-n2d1")) {
      bPC1 = Standard_False;
    }
    else if (!strcmp(a[i], "-n2d2")) {
      bPC2 = Standard_False;
    }
    else if (!strcmp(a[i], "-na")) {
      bApp = Standard_False;
    }
  }
  //
  BRepAlgoAPI_Section aSec(aS1, aS2, Standard_False);
  //
  aSec.Approximation(bApp);
  aSec.ComputePCurveOn1(bPC1);
  aSec.ComputePCurveOn2(bPC2);
  //
  aSec.SetFuzzyValue(aTol);
  aSec.SetRunParallel(bRunParallel);
  //
  aSec.Build();
  iErr=aSec.ErrorStatus();
  if (!aSec.IsDone()) {
    Sprintf(buf, " ErrorStatus : %d\n",  iErr);
    di << buf;
    return 0;
  }
  //
  const TopoDS_Shape& aR=aSec.Shape();
  if (aR.IsNull()) {
    di << " null shape\n";
    return 0;
  }
  DBRep::Set(a[1], aR);
  return 0;
}
//=======================================================================
//function : bsmt
//purpose  : 
//=======================================================================
Standard_Integer bsmt (Draw_Interpretor& di, 
                       Standard_Integer n, 
                       const char** a,
                       const BOPAlgo_Operation aOp)
{
  char buf[32];
  Standard_Boolean bRunParallel;
  Standard_Integer iErr;
  TopoDS_Shape aS1, aS2;
  BOPCol_ListOfShape aLC;
  Standard_Real aTol;
  //
  if (n != 4) {
    di << " use bx r s1 s2\n";
    return 0;
  }
  //
  aS1=DBRep::Get(a[2]);
  aS2=DBRep::Get(a[3]);
  //
  if (aS1.IsNull() || aS2.IsNull()) {
    di << " null shapes are not allowed \n";
    return 0;
  }
  aLC.Append(aS1);
  aLC.Append(aS2);
  // 
  aTol=BOPTest_Objects::FuzzyValue();
  bRunParallel = BOPTest_Objects::RunParallel();
  //
  Handle(NCollection_BaseAllocator)aAL=
    NCollection_BaseAllocator::CommonBaseAllocator();
  //
  //---------------------------------------------------------------
  BOPAlgo_PaveFiller aPF(aAL);
  //
  aPF.SetArguments(aLC);
  aPF.SetFuzzyValue(aTol); 
  aPF.SetRunParallel(bRunParallel);
  //
  aPF.Perform();
  iErr=aPF.ErrorStatus();
  if (iErr) {
    Sprintf(buf, " ErrorStatus : %d\n",  iErr);
    di << buf;
    return 0;
  }
  //
  //---------------------------------------------------------------
  BOPAlgo_BOP aBOP(aAL);
  //
  aBOP.AddArgument(aS1);
  aBOP.AddTool(aS2);
  aBOP.SetOperation(aOp);
  aBOP.SetRunParallel(bRunParallel);
  // 
  aBOP.PerformWithFiller(aPF);
  //
  iErr=aBOP.ErrorStatus();
  if (iErr) {
    Sprintf(buf, " ErrorStatus : %d\n",  iErr);
    di << buf;
    return 0;
  }
  const TopoDS_Shape& aR=aBOP.Shape();
  if (aR.IsNull()) {
    di << " null shape\n";
    return 0;
  }
  //
  DBRep::Set(a[1], aR);
  return 0;
}
//=======================================================================
//function : bopnews
//purpose  : 
//=======================================================================
Standard_Integer bopnews (Draw_Interpretor& di, 
                          Standard_Integer n, 
                          const char** a)
{
  if (n!=2) {
    di << " use bopnews -v[e,f]\n";
    return 0;
  }
  //
  if (pPF==NULL) {
    di << " Prepare BOPAlgo_PaveFiller first >bop S1 S2\n";
    return 0;
  }
  //
  char buf[32];
  Standard_CString aText;
  Standard_Integer i, i1, i2, iFound;
  Draw_Color aTextColor(Draw_cyan);
  TopAbs_ShapeEnum aT;
  Handle(BOPTest_DrawableShape) aDShape;
  //
  const BOPDS_PDS& pDS=pPF->PDS();
  //
  aT=TopAbs_SHAPE;
  if (!strcmp (a[1], "-f")) {
    aT=TopAbs_FACE;
  }
  else if (!strcmp (a[1], "-e")){
    aT=TopAbs_EDGE;
  }
  else if (!strcmp (a[1], "-v")){
    aT=TopAbs_VERTEX;
  }
  else {
    di << " use bopnews -v[e,f]\n";
    return 0;
  }
  //
  iFound=0;
  i1=pDS->NbSourceShapes();
  i2=pDS->NbShapes();
  for (i=i1; i<i2; ++i) {
    const BOPDS_ShapeInfo& aSI=pDS->ShapeInfo(i);
    if (aSI.ShapeType()==aT) {
      const TopoDS_Shape& aS=aSI.Shape();
      //
      Sprintf (buf, "z%d", i);
      aText=buf;
      aDShape=new BOPTest_DrawableShape (aS, aText, aTextColor);
      Draw::Set (aText, aDShape);
      //
      Sprintf (buf, " z%d", i);
      di << buf;
      //
      iFound=1;
    }
  }
  //
  if (iFound) {
    di << "\n";
  }
  else {
    di << " not found\n";
  }
  //
  return 0;
}
//=======================================================================
//function : bopcurves
//purpose  : 
//=======================================================================
Standard_Integer bopcurves (Draw_Interpretor& di, 
                            Standard_Integer n, 
                            const char** a)
{
  if (n<3) {
    di << " use bopcurves F1 F2 [-2d/-2d1/-2d2]\n";
    return 1;
  }
  //
  TopoDS_Shape S1 = DBRep::Get(a[1]);
  TopoDS_Shape S2 = DBRep::Get(a[2]);
  TopAbs_ShapeEnum aType;
  //
  if (S1.IsNull() || S2.IsNull()) {
    di << " Null shapes is not allowed \n";
    return 1;
  }
  //
  aType=S1.ShapeType();
  if (aType != TopAbs_FACE) {
    di << " Type mismatch F1\n";
    return 1;
  }
  aType=S2.ShapeType();
  if (aType != TopAbs_FACE) {
    di << " Type mismatch F2\n";
    return 1;
  }
  //
  const TopoDS_Face& aF1=*(TopoDS_Face*)(&S1);
  const TopoDS_Face& aF2=*(TopoDS_Face*)(&S2);
  //
  Standard_Boolean aToApproxC3d, aToApproxC2dOnS1, aToApproxC2dOnS2, anIsDone;
  Standard_Integer i, aNbCurves, aNbPoints;
  Standard_Real anAppTol, aTolR;
  TCollection_AsciiString aNm("c_"), aNp("p_");
  //
  anAppTol = 0.0000001;
  aToApproxC3d = Standard_True;
  aToApproxC2dOnS1 = Standard_False;
  aToApproxC2dOnS2 = Standard_False;
  //
  if (n > 3) {
    if (!strcasecmp(a[3],"-2d")) {
      aToApproxC2dOnS1 = Standard_True;
      aToApproxC2dOnS2 = Standard_True;
    } 
    else if (!strcasecmp(a[3],"-2d1")) {
      aToApproxC2dOnS1 = Standard_True;
    }
    else if (!strcasecmp(a[3],"-2d2")) {
      aToApproxC2dOnS2 = Standard_True;
    }
    else {
      di << "Wrong key. To build 2d curves use: bopcurves F1 F2 -2d/-2d1/-2d2 \n";
      return 1;
    }
  }
  //
  IntTools_FaceFace aFF;
  //
  aFF.SetParameters (aToApproxC3d,
                     aToApproxC2dOnS1,
                     aToApproxC2dOnS2,
                     anAppTol);
  //
  aFF.Perform (aF1, aF2);
  //
  anIsDone=aFF.IsDone();
  if (!anIsDone) {
    di << "Error: anIsDone=" << (Standard_Integer) anIsDone << "\n";
    return 0;
  }
  //
  aFF.PrepareLines3D(Standard_False);
  const IntTools_SequenceOfCurves& aSCs=aFF.Lines();
  const IntTools_SequenceOfPntOn2Faces& aSPs = aFF.Points();
  //
  aNbCurves = aSCs.Length();
  aNbPoints = aSPs.Length();
  if (!aNbCurves && !aNbPoints) {
    di << " has no 3d curves\n";
    di << " has no 3d points\n";
    return 0;
  }
  //
  aTolR=aFF.TolReached3d();
  di << "Tolerance Reached=" << aTolR << "\n";
  //
  // curves
  if (aNbCurves) {
    di << aNbCurves << " curve(s) found.\n";
    //
    for (i=1; i<=aNbCurves; i++) {
      const IntTools_Curve& anIC=aSCs(i);

      Handle (Geom_Curve)  aC3D = anIC.Curve();

      if (aC3D.IsNull()) {
        di << " has Null 3d curve# " << i << "\n";
        continue;
      }

      TCollection_AsciiString anIndx(i), aNmx;
      aNmx = aNm + anIndx;

      Standard_CString nameC = aNmx.ToCString();

      DrawTrSurf::Set(nameC, aC3D);
      di << nameC << " ";
      //
      Handle(Geom2d_Curve) aPC1 = anIC.FirstCurve2d();
      Handle(Geom2d_Curve) aPC2 = anIC.SecondCurve2d();
      //
      if (!aPC1.IsNull() || !aPC2.IsNull()) {
        di << "(";
        //
        if (!aPC1.IsNull()) {
          TCollection_AsciiString pc1N("c2d1_"), pc1Nx;
          pc1Nx = pc1N + anIndx;
          Standard_CString nameC2d1 = pc1Nx.ToCString();
          //
          DrawTrSurf::Set(nameC2d1, aPC1);
          di << nameC2d1;
        }
        //
        if (!aPC2.IsNull()) {
          TCollection_AsciiString pc2N("c2d2_"), pc2Nx;
          pc2Nx = pc2N + anIndx;
          Standard_CString nameC2d2 = pc2Nx.ToCString();
          //
          DrawTrSurf::Set(nameC2d2, aPC2);
          //
          if (!aPC1.IsNull()) {
            di << ", ";
          }
          di << nameC2d2;
        }
        di << ") ";
      }
    }
    di << "\n";
  }
  //
  // points
  if (aNbPoints) {
    di << aNbPoints << " point(s) found.\n";
    //
    for (i = 1; i <= aNbPoints; i++) {
      const IntTools_PntOn2Faces& aPi = aSPs(i);
      const gp_Pnt& aP = aPi.P1().Pnt();
      //
      TCollection_AsciiString anIndx(i), aNmx;
      aNmx = aNp + anIndx;
      Standard_CString nameP = aNmx.ToCString();
      //
      DrawTrSurf::Set(nameP, aP);
      di << nameP << " ";
    }
    di << "\n";
  }
  //
  return 0;
}
//=======================================================================
//function : mkvolume
//purpose  : 
//=======================================================================
Standard_Integer mkvolume(Draw_Interpretor& di, Standard_Integer n, const char** a) 
{
  if (n < 3) {
    di << "Usage: mkvolume r b1 b2 ... [-c] [-ni]\n";
    di << "Options:\n";
    di << " -c  - use this option if the arguments are compounds\n";
    di << "       containing shapes that should be interfered;\n";
    di << " -ni - use this option if the arguments should not be interfered;\n";
    return 1;
  }
  //
  const char* usage = "Type mkvolume without arguments for the usage of the command.\n";
  //
  Standard_Boolean bToIntersect, bRunParallel, bCompounds;
  Standard_Integer i;
  Standard_Real aTol;
  TopoDS_Shape aS;
  BOPCol_ListOfShape aLS;
  //
  aTol = BOPTest_Objects::FuzzyValue();
  bRunParallel = BOPTest_Objects::RunParallel();
  //
  bToIntersect = Standard_True;
  bCompounds = Standard_False;
  //
  for (i = 2; i < n; ++i) {
    aS = DBRep::Get(a[i]);
    if (!aS.IsNull()) {
      aLS.Append(aS);
    }
    else {
      if (!strcmp(a[i], "-c")) {
        bCompounds = Standard_True;
      }
      else if (!strcmp(a[i], "-ni")) {
        bToIntersect = Standard_False;
      }
    }
  }
  //
  if (aLS.IsEmpty()) {
    di << "No shapes to process.\n";
    di << usage;
    return 1;
  }
  //
  // treat list of arguments for the case of compounds
  if (bToIntersect && bCompounds) {
    BOPCol_ListOfShape aLSx;
    BOPCol_ListIteratorOfListOfShape aItLS;
    //
    aItLS.Initialize(aLS);
    for (; aItLS.More(); aItLS.Next()) {
      const TopoDS_Shape& aSx = aItLS.Value();
      TopoDS_Iterator aItS(aSx);
      for (; aItS.More(); aItS.Next()) {
        const TopoDS_Shape& aSxS = aItS.Value();
        aLSx.Append(aSxS);
      }
    }
    //
    aLS.Clear();
    aLS.Assign(aLSx);
  }
  //
  BOPAlgo_MakerVolume aMV;
  aMV.SetArguments(aLS);
  aMV.SetIntersect(bToIntersect);
  aMV.SetRunParallel(bRunParallel);
  aMV.SetFuzzyValue(aTol);
  //
  aMV.Perform();
  if (aMV.ErrorStatus()) {
    di << "Error status: " << aMV.ErrorStatus();
    return 1;
  }
  //
  const TopoDS_Shape& aR = aMV.Shape();
  //
  DBRep::Set(a[1], aR);
  //
  return 0;
}
