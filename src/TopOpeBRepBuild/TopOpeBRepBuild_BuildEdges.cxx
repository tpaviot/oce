// Created on: 1993-06-14
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


#include <TopOpeBRepBuild_Builder.jxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <TopOpeBRepDS_CurveExplorer.hxx>
#include <TopOpeBRepDS_Curve.hxx>
#include <TopoDS.hxx>
#include <TopOpeBRepBuild_define.hxx>

#ifdef DEB
extern Standard_Boolean TopOpeBRepBuild_GettraceCU();
#endif

//=======================================================================
//function : BuildEdges
//purpose  : 
//=======================================================================
void TopOpeBRepBuild_Builder::BuildEdges(const Standard_Integer iC,const Handle(TopOpeBRepDS_HDataStructure)& HDS)
{
#ifdef DEB
  if (TopOpeBRepBuild_GettraceCU()) cout<<"\nBuildEdges on C "<<iC<<endl;
#endif
  const TopOpeBRepDS_Curve& C = HDS->Curve(iC);
  const Handle(Geom_Curve)& C3D = C.Curve(); 
  const Handle(TopOpeBRepDS_Interference)& I1 = C.GetSCI1();
  const Handle(TopOpeBRepDS_Interference)& I2 = C.GetSCI2();
  Standard_Boolean nnn = C3D.IsNull() && I1.IsNull() && I2.IsNull();
  if (nnn) {
    return;
  }
  
  TopoDS_Shape anEdge;
  const TopOpeBRepDS_Curve& curC = HDS->Curve(iC);
  myBuildTool.MakeEdge(anEdge,curC,HDS->DS());
  TopOpeBRepBuild_PaveSet PVS(anEdge);
  TopOpeBRepDS_PointIterator CPIT(HDS->CurvePoints(iC));
  FillVertexSet(CPIT,TopAbs_IN,PVS);
  TopOpeBRepBuild_PaveClassifier VCL(anEdge);
  Standard_Boolean equalpar = PVS.HasEqualParameters();
  if (equalpar) VCL.SetFirstParameter(PVS.EqualParameters());
  Standard_Boolean closvert = PVS.ClosedVertices();
  VCL.ClosedVertices(closvert);  
  PVS.InitLoop();
  if ( !PVS.MoreLoop() ) {
    return;
  }
  TopOpeBRepBuild_EdgeBuilder EDBU(PVS,VCL);
  TopTools_ListOfShape& EL = ChangeNewEdges(iC);
  MakeEdges(anEdge,EDBU,EL);
  TopTools_ListIteratorOfListOfShape It(EL);
  Standard_Integer inewC = -1;
  for (; It.More(); It.Next()) {
    TopoDS_Edge& newEdge = TopoDS::Edge(It.Value());
    myBuildTool.RecomputeCurves(curC,TopoDS::Edge(anEdge),newEdge,inewC,HDS);
    if (inewC != -1) ChangeNewEdges(inewC).Append(newEdge);
  }
  if (inewC != -1) {
    HDS->RemoveCurve(iC);
  }
  else {
    for (It.Initialize(EL);It.More();It.Next()) {
      TopoDS_Edge& newEdge = TopoDS::Edge(It.Value());
      myBuildTool.UpdateEdge(anEdge,newEdge);
    }
  }
}

//=======================================================================
//function : BuildEdges
//purpose  : 
//=======================================================================
void TopOpeBRepBuild_Builder::BuildEdges(const Handle(TopOpeBRepDS_HDataStructure)& HDS)
{
  TopOpeBRepDS_DataStructure& BDS = HDS->ChangeDS();

  myNewEdges.Clear();
  TopOpeBRepDS_CurveExplorer cex;

  Standard_Integer ick = 0;
  for (cex.Init(BDS,Standard_False); cex.More(); cex.Next()) {
    Standard_Integer ic = cex.Index();
    Standard_Boolean ck = cex.IsCurveKeep(ic);
    Standard_Integer im = cex.Curve(ic).Mother();
    if (ck == 1 && im != 0 && ick == 0) { ick = ic; break; }
  }
  if (ick) {
    for (cex.Init(BDS,Standard_True); cex.More(); cex.Next()) {
      Standard_Integer ic = cex.Index();
      BDS.RemoveCurve(ic);
    }
    BDS.ChangeNbCurves(ick-1);
  }

  for (cex.Init(BDS,Standard_False); cex.More(); cex.Next()) {
    Standard_Integer ic = cex.Index();
    Standard_Integer im = cex.Curve(ic).Mother();
    if (im != 0 ) continue;
    BuildEdges(ic,HDS);
  }

  Standard_Integer ip, np = HDS->NbPoints();
  TColStd_HArray1OfInteger tp(0,np,0);
  for (cex.Init(BDS); cex.More(); cex.Next()) {
#ifdef DEB
//    const TopOpeBRepDS_Curve& C = cex.Curve();
#endif
    Standard_Integer ic = cex.Index();
    TopOpeBRepDS_ListIteratorOfListOfInterference it(BDS.CurveInterferences(ic));
    for(;it.More();it.Next()) {
      const Handle(TopOpeBRepDS_Interference)& I = it.Value();
      {
        Standard_Integer ig = I->Geometry();
        TopOpeBRepDS_Kind kg = I->GeometryType();
        if (kg == TopOpeBRepDS_POINT && ig <= np) tp.ChangeValue(ig) = tp.Value(ig) + 1;
      }
      {
        Standard_Integer is = I->Support();
        TopOpeBRepDS_Kind ks = I->SupportType();
        if (ks == TopOpeBRepDS_POINT) tp.ChangeValue(is) = tp.Value(is) + 1;
      }
    }
  }
  Standard_Integer is, ns = BDS.NbShapes();
  for (is = 1; is <= ns; is++ ) {
    const TopoDS_Shape& S = BDS.Shape(is);
    if(S.IsNull()) continue;
    Standard_Boolean test = (S.ShapeType() == TopAbs_EDGE); 
    if ( !test ) continue;
    TopOpeBRepDS_ListIteratorOfListOfInterference it(BDS.ShapeInterferences(is));
    for(;it.More();it.Next()) {
      const Handle(TopOpeBRepDS_Interference)& I = it.Value(); 
      {
        Standard_Integer ig = I->Geometry();
        TopOpeBRepDS_Kind kg = I->GeometryType();
        if (kg == TopOpeBRepDS_POINT) tp.ChangeValue(ig) = tp.Value(ig) + 1;
      }
      {
        Standard_Integer is1 = I->Support();
        TopOpeBRepDS_Kind ks = I->SupportType();
       if (ks == TopOpeBRepDS_POINT) tp.ChangeValue(is1) = tp.Value(is1) + 1;
      }
    }
  }
  for (ip = 1; ip <= np; ip++) if (tp.Value(ip) == 0) BDS.RemovePoint(ip);
}
