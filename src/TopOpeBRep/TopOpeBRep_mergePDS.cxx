// Created on: 1993-06-24
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


#include <TopoDS.hxx>
#include <TopExp_Explorer.hxx>
#include <TopOpeBRepDS_CurveExplorer.hxx>
#include <TopOpeBRepDS_IndexedDataMapOfVertexPoint.hxx>
#include <TopOpeBRepDS_CurveExplorer.hxx>
#include <TopOpeBRepDS_Curve.hxx>
#include <TopOpeBRepDS_Point.hxx>
#include <TopOpeBRepDS.hxx>

#include <TopOpeBRep_define.hxx>


Standard_Integer BREP_findPDSamongIDMOVP(const TopOpeBRepDS_Point& PDS,const TopOpeBRepDS_IndexedDataMapOfVertexPoint& IDMOVP)
{
  Standard_Integer iIDMOVP = 0;
  Standard_Integer i = 1, n = IDMOVP.Extent();
  for(; i <= n; i++) {
    const TopOpeBRepDS_Point& PM = IDMOVP.FindFromIndex(i);
    if (PDS.IsEqual(PM)) { iIDMOVP = i; break; }
  }
  return iIDMOVP;
}

void BREP_makeIDMOVP(const TopoDS_Shape& S,TopOpeBRepDS_IndexedDataMapOfVertexPoint& IDMOVP)
{
  TopExp_Explorer Ex;
  for (Ex.Init(S,TopAbs_VERTEX);Ex.More();Ex.Next()) {
    const TopoDS_Vertex& v = TopoDS::Vertex(Ex.Current()); 
    TopOpeBRepDS_Point PDS(v); IDMOVP.Add(v,PDS);
  }
}

Standard_EXPORT void BREP_mergePDS(const Handle(TopOpeBRepDS_HDataStructure)& HDS)
{
  TopOpeBRepDS_DataStructure& BDS = HDS->ChangeDS();
  TopOpeBRepDS_CurveExplorer cex(BDS);if (!cex.More()) return;
  
  TopOpeBRepDS_IndexedDataMapOfVertexPoint Mvp1;
  TopOpeBRepDS_IndexedDataMapOfVertexPoint Mvp2;
  
  for (;cex.More();cex.Next()) {
    
    const TopOpeBRepDS_Curve& c = cex.Curve(); const Standard_Integer ic = cex.Index();
    TopOpeBRepDS_ListIteratorOfListOfInterference itI;itI.Initialize(BDS.ChangeCurveInterferences(ic));if (!itI.More()) continue;
    
    const TopoDS_Face& f1 = TopoDS::Face(c.Shape1());
#ifdef DEB
    Standard_Integer if1 =
#endif
              BDS.Shape(f1);
    const TopoDS_Face& f2 = TopoDS::Face(c.Shape2());
#ifdef DEB
    Standard_Integer if2 =
#endif
              BDS.Shape(f2);
    
    Mvp1.Clear();BREP_makeIDMOVP(f1,Mvp1);
    Mvp2.Clear();BREP_makeIDMOVP(f2,Mvp2);
    
    for (; itI.More(); itI.Next()) {
      Handle(TopOpeBRepDS_Interference) ITF = itI.Value();
      Handle(TopOpeBRepDS_CurvePointInterference) CPI = Handle(TopOpeBRepDS_CurvePointInterference)::DownCast(ITF); if (CPI.IsNull()) continue;
      TopOpeBRepDS_Kind GK = CPI->GeometryType(); if (GK != TopOpeBRepDS_POINT) continue;
      Standard_Integer GI = CPI->Geometry();
      //**!
      if(GI > BDS.NbPoints()) continue;
      //**!
      const TopOpeBRepDS_Point& PDS = BDS.Point(GI);

      Standard_Integer ivp1; TopoDS_Shape v1; TopOpeBRepDS_Kind k1=TopOpeBRepDS_UNKNOWN; Standard_Integer iv1 = 0;
#ifdef DEB
      Standard_Boolean newv1 = Standard_False;
#endif

      ivp1 = BREP_findPDSamongIDMOVP(PDS,Mvp1);
      if (ivp1) {
	v1 = Mvp1.FindKey(ivp1);
#ifdef DEB
	newv1 = !BDS.HasShape(v1);
#endif
	iv1 = BDS.AddShape(v1);
	k1 = TopOpeBRepDS_VERTEX;
      }
      
      Standard_Integer ivp2; TopoDS_Shape v2; TopOpeBRepDS_Kind k2=TopOpeBRepDS_UNKNOWN; Standard_Integer iv2 = 0;
#ifdef DEB
      Standard_Boolean newv2 = Standard_False;
#endif

      ivp2 = BREP_findPDSamongIDMOVP(PDS,Mvp2);
      if (ivp2) {
	v2 = Mvp2.FindKey(ivp2);
#ifdef DEB
	newv2 = !BDS.HasShape(v2);
#endif
	iv2 = BDS.AddShape(v2);
	k2 = TopOpeBRepDS_VERTEX;
      }
      
      if (ivp1 && ivp2) BDS.FillShapesSameDomain(v1,v2);

      Standard_Boolean editITF = (ivp1 || ivp2);
      if (editITF) {		
	if      (ivp1) { CPI->GeometryType(k1); CPI->Geometry(iv1); }
	else if (ivp2) { CPI->GeometryType(k2); CPI->Geometry(iv2); }
      }
            
#ifdef DEB
      if (editITF) {
	if (ivp1 != 0) {
	  cout<<TopOpeBRepDS::SPrint(TopOpeBRepDS_CURVE,ic,"# BREP_mergePDS "," : ");
	  cout<<TopOpeBRepDS::SPrint(GK,GI,""," = ");
	  TCollection_AsciiString str; if (newv1) str = "new "; else str = "old ";
	  cout<<TopOpeBRepDS::SPrint(k1,iv1,str);
	  cout<<TopOpeBRepDS::SPrint(TopOpeBRepDS::ShapeToKind(f1.ShapeType()),if1," de ")<<endl;
	}
	if (ivp2 != 0) {
	  cout<<TopOpeBRepDS::SPrint(TopOpeBRepDS_CURVE,ic,"# BREP_mergePDS "," : ");
	  cout<<TopOpeBRepDS::SPrint(GK,GI,""," = ");
	  TCollection_AsciiString str; if (newv2) str = "new "; else str = "old ";
	  cout<<TopOpeBRepDS::SPrint(k2,iv2,str);
	  cout<<TopOpeBRepDS::SPrint(TopOpeBRepDS::ShapeToKind(f2.ShapeType()),if2," de ")<<endl;
	}
	ITF->Dump(cout,"# BREP_mergePDS resu ","\n");
      }
#endif
      
    } // itI.More()
  }
} // BREP_mergePDS
