// Created on: 1997-11-25
// Created by: Jean Yves LEBEY
// Copyright (c) 1997-1999 Matra Datavision
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


#include <TopOpeBRepDS_connex.hxx>

#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>

static TopTools_DataMapOfShapeListOfShape *GLOBAL_elf1 = NULL; // NYI to CDLize as a tool of DS
static TopTools_DataMapOfShapeListOfShape *GLOBAL_elf2 = NULL; // NYI to CDLize as a tool of DS
static TopTools_DataMapOfShapeListOfShape *GLOBAL_fle = NULL;  // NYI to CDLize as a tool of DS
static TopTools_ListOfShape *GLOBAL_los = NULL;  // NYI to CDLize as a tool of DS
static Standard_Boolean GLOBAL_FDSCNX_prepared = Standard_False;

//modified by NIZNHY-PKV Sun Dec 15 17:41:43 2002 f
//=======================================================================
//function : FDSCNX_Close
//purpose  : 
//=======================================================================
void FDSCNX_Close()
{
  if (GLOBAL_elf1) {
    delete GLOBAL_elf1;
    GLOBAL_elf1=NULL;
  }
  //
  if (GLOBAL_elf2) {
    delete GLOBAL_elf2;
    GLOBAL_elf2=NULL;
  }
  //
  if (GLOBAL_fle) {
    delete GLOBAL_fle;
    GLOBAL_fle=NULL;
  }
  //
  if (GLOBAL_los) {
    delete GLOBAL_los;
    GLOBAL_los=NULL;
  }
  //
  GLOBAL_FDSCNX_prepared = Standard_False;
}
//modified by NIZNHY-PKV Sun Dec 15 17:41:40 2002 t

Standard_EXPORT const TopTools_ListOfShape& FDSCNX_EdgeConnexityShapeIndex(const TopoDS_Shape& E,const Handle(TopOpeBRepDS_HDataStructure)& HDS,const Standard_Integer SI) 
{
  if (HDS.IsNull()) return *GLOBAL_los;
  if (!GLOBAL_FDSCNX_prepared) return *GLOBAL_los;
  if (SI != 1 && SI != 2) return *GLOBAL_los;
  const TopOpeBRepDS_DataStructure& BDS = HDS->DS();
  TopAbs_ShapeEnum t = E.ShapeType(); if (t != TopAbs_EDGE) return *GLOBAL_los;
  Standard_Boolean has = FDSCNX_HasConnexFace(E,HDS); if (!has) return *GLOBAL_los;
  Standard_Integer re = BDS.AncestorRank(E); if (re == 0) return *GLOBAL_los;
  TopTools_DataMapOfShapeListOfShape* pelf = (SI == 1) ? GLOBAL_elf1 : GLOBAL_elf2;
  TopTools_DataMapOfShapeListOfShape& elf = *pelf;
  return elf.Find(E);
}

// S = edge --> liste de faces connexes par S
// S = face --> liste d'edges E de S qui ont au moins une autre face connexe
Standard_EXPORT const TopTools_ListOfShape& FDSCNX_EdgeConnexitySameShape(const TopoDS_Shape& S,const Handle(TopOpeBRepDS_HDataStructure)& HDS) 
{
  TopAbs_ShapeEnum t = S.ShapeType();
  if      (t == TopAbs_EDGE) {
    Standard_Integer si = HDS->DS().AncestorRank(S);
    const TopTools_ListOfShape& lf = FDSCNX_EdgeConnexityShapeIndex(S,HDS,si);
    return lf;
  }
  else if (t == TopAbs_FACE) {
    TopTools_DataMapOfShapeListOfShape& fle = *GLOBAL_fle;
    if (fle.IsBound(S)) {
      return fle.Find(S);
    }
  }
  return *GLOBAL_los;
}

Standard_EXPORT void FDSCNX_Prepare(const TopoDS_Shape& /*S1*/,
                                    const TopoDS_Shape& /*S2*/,
                                    const Handle(TopOpeBRepDS_HDataStructure)& HDS)
{
  if (HDS.IsNull()) {
    GLOBAL_FDSCNX_prepared = Standard_False;
    return;
  }
  const TopOpeBRepDS_DataStructure& BDS = HDS->DS();
  if (GLOBAL_elf1 == NULL) GLOBAL_elf1 = (TopTools_DataMapOfShapeListOfShape*) new TopTools_DataMapOfShapeListOfShape();
  if (GLOBAL_elf2 == NULL) GLOBAL_elf2 = (TopTools_DataMapOfShapeListOfShape*) new TopTools_DataMapOfShapeListOfShape();
  if (GLOBAL_fle == NULL) GLOBAL_fle = (TopTools_DataMapOfShapeListOfShape*) new TopTools_DataMapOfShapeListOfShape();
  if (GLOBAL_los == NULL) GLOBAL_los = (TopTools_ListOfShape*) new TopTools_ListOfShape();
  GLOBAL_elf1->Clear();
  GLOBAL_elf2->Clear();
  GLOBAL_fle->Clear();
  GLOBAL_los->Clear();

  Standard_Integer i=0,n=BDS.NbShapes();
  for (i=1;i<=n;i++) {
    const TopoDS_Shape& f = BDS.Shape(i); if (f.ShapeType() != TopAbs_FACE) continue;
    Standard_Integer rf = BDS.AncestorRank(f); if (rf == 0) continue;
//    BDS.Shape(f);
    TopTools_DataMapOfShapeListOfShape& fle = *GLOBAL_fle;
    TopTools_DataMapOfShapeListOfShape& elf = (rf == 1) ? *GLOBAL_elf1 : *GLOBAL_elf2; 
    TopExp_Explorer exe;
    for (exe.Init(f,TopAbs_EDGE);exe.More();exe.Next()) {
//    for (TopExp_Explorer exe(f,TopAbs_EDGE);exe.More();exe.Next()) {
      const TopoDS_Shape& e = exe.Current();
//               BDS.Shape(e);
//      Standard_Boolean se = BDS.IsSectionEdge(TopoDS::Edge(e)); if (!se) continue;
      Standard_Boolean hs = BDS.HasShape(TopoDS::Edge(e)); if (!hs) continue;
      TopTools_ListOfShape thelist, thelist1;
      if (!fle.IsBound(f)) fle.Bind(f, thelist); fle.ChangeFind(f).Append(e);
      if (!elf.IsBound(e)) elf.Bind(e, thelist1); elf.ChangeFind(e).Append(f);
    }
  }
  GLOBAL_FDSCNX_prepared = Standard_True;
}

Standard_EXPORT Standard_Boolean FDSCNX_HasConnexFace(const TopoDS_Shape& S,const Handle(TopOpeBRepDS_HDataStructure)& HDS) 
{
  if (HDS.IsNull()) return Standard_False; const TopOpeBRepDS_DataStructure& BDS = HDS->DS();
  const TopAbs_ShapeEnum t = S.ShapeType(); if (t != TopAbs_FACE && t != TopAbs_EDGE) return Standard_False;
  const Standard_Integer rs = BDS.AncestorRank(S); if (rs == 0) return Standard_False;
  TopTools_DataMapOfShapeListOfShape* pelf = (rs == 1) ? GLOBAL_elf1 : GLOBAL_elf2; if (pelf == NULL) return Standard_False;
  TopTools_DataMapOfShapeListOfShape& fle = *GLOBAL_fle; 
  TopTools_DataMapOfShapeListOfShape& elf = *pelf;
  Standard_Boolean has = Standard_False;
  if      (t == TopAbs_EDGE) has = elf.IsBound(S);
  else if (t == TopAbs_FACE) has = fle.IsBound(S);
  return has;
}

Standard_EXPORT void FDSCNX_FaceEdgeConnexFaces(const TopoDS_Shape& F,const TopoDS_Shape& E,const Handle(TopOpeBRepDS_HDataStructure)& HDS,TopTools_ListOfShape& LF) 
{
  LF.Clear();
#ifdef DEB
//  Standard_Integer Fi =
#endif
//           HDS->Shape(F);
#ifdef DEB
//  Standard_Integer Ei =
#endif
//           HDS->Shape(E);

  // verifier que E est une arete de connexite de F
  Standard_Boolean EofF = Standard_False;
  const TopTools_ListOfShape& loe = FDSCNX_EdgeConnexitySameShape(F,HDS); if (loe.IsEmpty()) return;
  for (TopTools_ListIteratorOfListOfShape i(loe);i.More();i.Next()) {
    const TopoDS_Shape& e = i.Value();
//             HDS->Shape(e);
    Standard_Boolean b = e.IsSame(E);
    if (b) {
      EofF=Standard_True;
      break;
    }
  }
  if (!EofF) return;
  
  const TopTools_ListOfShape& lof = FDSCNX_EdgeConnexitySameShape(E,HDS); if (lof.IsEmpty()) return;
  for (TopTools_ListIteratorOfListOfShape it(lof);it.More();it.Next()) {
    const TopoDS_Shape& f = it.Value();
#ifdef DEB
//    Standard_Integer fi =
#endif
//             HDS->Shape(f);
    Standard_Boolean b = f.IsSame(F);
    if (!b) {
      LF.Append(f);
    }
  }
}

Standard_EXPORT void FDSCNX_DumpIndex(const Handle(TopOpeBRepDS_HDataStructure)& HDS,const Standard_Integer I)
{
  if (HDS.IsNull()) return; const TopOpeBRepDS_DataStructure& BDS = HDS->DS();
  Standard_Integer ns=BDS.NbShapes();
  if (I<1 || I>ns) return;
  Standard_Integer i=I;
  const TopoDS_Shape& s=BDS.Shape(i);
#ifdef DEB
//  Standard_Integer is=
#endif
//         BDS.Shape(s);
  TopAbs_ShapeEnum ts=s.ShapeType();
  const TopTools_ListOfShape& ls=FDSCNX_EdgeConnexitySameShape(s,HDS);
  if      (ts == TopAbs_EDGE) {
    TopTools_ListIteratorOfListOfShape ils(ls);if(!ils.More())return;
    for(;ils.More();ils.Next())cout<<BDS.Shape(ils.Value())<<" ";
  }
  else if (ts == TopAbs_FACE) {
    TopTools_ListIteratorOfListOfShape ils(ls);if(!ils.More())return;
    for(;ils.More();ils.Next()) {
      const TopoDS_Shape& e=ils.Value();
#ifdef DEB
//      Standard_Integer ie=BDS.Shape(e);
//      TopAbs_ShapeEnum te=e.ShapeType();
#endif
      TopTools_ListOfShape lf;FDSCNX_FaceEdgeConnexFaces(s,e,HDS,lf);
      TopTools_ListIteratorOfListOfShape ilf(lf);if(!ilf.More())continue;
      for(;ilf.More();ilf.Next())cout<<BDS.Shape(ilf.Value())<<" ";
    }
  }
}

Standard_EXPORT void FDSCNX_Dump(const Handle(TopOpeBRepDS_HDataStructure)& HDS,const Standard_Integer I)
{
  if (HDS.IsNull()) return; const TopOpeBRepDS_DataStructure& BDS = HDS->DS();
  Standard_Integer ns=BDS.NbShapes();
  if (I<1 || I>ns) return;
  Standard_Integer i=I;
  const TopoDS_Shape& s=BDS.Shape(i);Standard_Integer is=BDS.Shape(s);TopAbs_ShapeEnum ts=s.ShapeType();
  const TopTools_ListOfShape& ls=FDSCNX_EdgeConnexitySameShape(s,HDS);
  if      (ts == TopAbs_EDGE) {
    TopTools_ListIteratorOfListOfShape ils(ls);if(!ils.More())return;
    cout<<"clear;";
    for(;ils.More();ils.Next())cout<<"tsee f "<<BDS.Shape(ils.Value())<<";";
    cout<<"tsee e "<<is<<";### edge "<<is<<" connexity"<<endl;
  }
  else if (ts == TopAbs_FACE) {
    TopTools_ListIteratorOfListOfShape ils(ls);if(!ils.More())return;
    for(;ils.More();ils.Next()) {
      const TopoDS_Shape& e=ils.Value();Standard_Integer ie=BDS.Shape(e);
#ifdef DEB
//      TopAbs_ShapeEnum te=e.ShapeType();
#endif
      TopTools_ListOfShape lf;FDSCNX_FaceEdgeConnexFaces(s,e,HDS,lf);
      TopTools_ListIteratorOfListOfShape ilf(lf);if(!ilf.More())continue;
      cout<<"clear;";cout<<"tsee f "<<is<<";";
      for(;ilf.More();ilf.Next())cout<<"tsee f "<<BDS.Shape(ilf.Value())<<";";
      cout<<"tsee e "<<ie<<";### face "<<is<<" connexity"<<endl;
    }
  }
}

Standard_EXPORT void FDSCNX_Dump(const Handle(TopOpeBRepDS_HDataStructure)& HDS)
{
  if (HDS.IsNull()) return; const TopOpeBRepDS_DataStructure& BDS = HDS->DS();
  Standard_Integer i=1,ns=BDS.NbShapes();
  for (i=1;i<=ns;i++) FDSCNX_Dump(HDS,i);
}
