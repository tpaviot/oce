// Created on: 1997-06-12
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


#include <TopOpeBRep_FacesFiller.ixx>

#include <TopOpeBRepTool_TOOL.hxx>
#include <TopOpeBRepTool_ShapeTool.hxx>
#include <TopoDS.hxx>
#include <TopExp.hxx>
#include <TColStd_ListOfInteger.hxx>
#include <TColStd_ListIteratorOfListOfInteger.hxx>
#include <BRep_Tool.hxx>
#include <gp_Pnt.hxx>
#include <TopOpeBRep_define.hxx>
#include <TopOpeBRepTool_EXPORT.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <TopOpeBRep_define.hxx>
#include <TopTools_MapOfShape.hxx>

#ifdef DEB
extern Standard_Boolean TopOpeBRepDS_GettraceDSF();
extern Standard_Boolean TopOpeBRepDS_GettraceDSFK();
extern Standard_Boolean TopOpeBRepDS_GettraceDSNC();
#endif

Standard_EXPORT Standard_Boolean FUN_EqualponR(const TopOpeBRep_LineInter& Lrest,
				  const TopOpeBRep_VPointInter& VP1,
				  const TopOpeBRep_VPointInter& VP2);
Standard_EXPORT Standard_Boolean FUN_EqualPonR(const TopOpeBRep_LineInter& Lrest,
				  const TopOpeBRep_VPointInter& VP1,
				  const TopOpeBRep_VPointInter& VP2);

//=======================================================================
//function : GetESL
//purpose  : Get list <LES> of restriction edges from the current faces 
//           intersector having part IN one of the 2 faces.
//=======================================================================
void TopOpeBRep_FacesFiller::GetESL(TopTools_ListOfShape& LES)
{

#ifdef DEB
  Standard_Boolean b22 = TopOpeBRepDS_GettraceDSNC();
  Standard_Boolean trRL=Standard_False;
#endif

  TopTools_MapOfShape mapES;

  // !! : do NOT use  myFacesIntersector->Restrictions()
  // the same map is filled for all couple of faces.
  
  myFacesIntersector->InitLine();
  for (; myFacesIntersector->MoreLine(); myFacesIntersector->NextLine()) {
    const TopOpeBRep_LineInter& L = myFacesIntersector->CurrentLine();
    TopOpeBRep_TypeLineCurve t = L.TypeLineCurve();
    Standard_Boolean isrest = (t == TopOpeBRep_RESTRICTION);
    
    if (isrest) {
      const TopoDS_Edge& E = TopoDS::Edge(L.Arc());
      
#ifdef DEB
      if (trRL) {
	TopOpeBRep_VPointInterIterator VPI;VPI.Init(L);
	cout<<endl<<"------------ Dump Rline  --------------------"<<endl;
	for (; VPI.More(); VPI.Next()) myHFFD->DumpVP(VPI.CurrentVP());
      }
#endif
      
      Standard_Boolean add = !mapES.Contains(E);
      if (add) {
	Standard_Boolean checkkeep = Standard_False;
	add = KeepRLine(L,checkkeep);
      }
      if (add) {
        mapES.Add(E);
        LES.Append(E);
      }

#ifdef DEB
      if (b22) {
	if (add) cout<<" : add restriction edge of line ";
	else cout<<" rejection of restriction edge of line ";
	cout<<L.Index()<<endl;
      }
#endif
    }

  } // loop on lines
}

//=======================================================================
//function : KeepRLine
//purpose  :
//=======================================================================
Standard_Boolean TopOpeBRep_FacesFiller::KeepRLine
(const TopOpeBRep_LineInter& L,const Standard_Boolean checkkeep) const
{ 
#ifdef DEB
  //Standard_Boolean trc = (TopOpeBRepDS_GettraceDSF() || TopOpeBRepDS_GettraceDSNC());
#endif

  TopOpeBRep_TypeLineCurve t = L.TypeLineCurve();
  Standard_Boolean isrest = (t == TopOpeBRep_RESTRICTION);
  if (!isrest) return Standard_False;
  const TopoDS_Edge& EL = TopoDS::Edge(L.Arc());
  Standard_Boolean isdg = BRep_Tool::Degenerated(EL);
  if (isdg) return Standard_False;

  // look for a vpoint with transition IN/OUT or OUT/IN
  TopOpeBRep_VPointInterIterator VPI; VPI.Init(L,checkkeep);
  
  // With LineContructor, each RLine restricted by its vpbounds
  // has its restrictions IN or ON the two faces
  Standard_Boolean keeprline;
  Standard_Boolean isedge1 = L.ArcIsEdge(1);
  if (!VPI.More()) return Standard_False;
  
  Standard_Boolean samevp = Standard_True;
  const TopOpeBRep_VPointInter& vpf = VPI.CurrentVP();
  
  TopOpeBRep_VPointInter vpl;
  VPI.Init(L,checkkeep);
  if (VPI.More()) VPI.Next();

  Standard_Boolean middle = Standard_False; // xpu011098 : cto012U1
  TopoDS_Vertex vv; Standard_Boolean closedE = TopOpeBRepTool_TOOL::ClosedE(EL,vv);
  if (closedE) {
    Standard_Real parf,parl; FUN_tool_bounds(EL,parf,parl);
    for (; VPI.More(); VPI.Next()) {
      vpl = VPI.CurrentVP();
      Standard_Real pf = VPParamOnER(vpl,L);
      Standard_Boolean middlept = (parf<pf) && (pf<parl);
      if (middlept) {middle = Standard_True; samevp=Standard_False; break;}
    }
    if (middle) {
      VPI.Init(L,checkkeep);
      for (; VPI.More(); VPI.Next()) {
	vpl = VPI.CurrentVP();	
	Standard_Boolean samept = FUN_EqualPonR(L,vpf,vpl);
	if (samept) continue;
	else break;
      }
    }
  }  
  if (!middle) {
    VPI.Init(L,checkkeep);
    if (VPI.More()) VPI.Next();
    for (; VPI.More(); VPI.Next()) {
      vpl = VPI.CurrentVP();
      samevp = FUN_EqualponR(L,vpf,vpl);
      if (!samevp) break;
    }
  }

  if (!samevp) {
    // xpu151098 : cto 904 C8 : modif done tol2d > 0 => found restriction shared 
    //   by circle/line
    Standard_Boolean samept = FUN_EqualPonR(L,vpf,vpl);
    if (samept) {
      TopoDS_Vertex vclo; Standard_Boolean closedEL = TopOpeBRepTool_TOOL::ClosedE(EL,vclo);
      if (closedEL) {
	Standard_Real tolvclo = BRep_Tool::Tolerance(vclo);
//	Standard_Real tolvclo = BRep_Tool::Tolerance(TopoDS::Vertex(vclo));
	gp_Pnt ptclo = BRep_Tool::Pnt(vclo);
//	gp_Pnt ptclo = BRep_Tool::Pnt(TopoDS::Vertex(vclo));
	Standard_Real tolf = vpf.Tolerance(); gp_Pnt ptf = vpf.Value();
	Standard_Real d = ptf.Distance(ptclo);
	Standard_Boolean sameclo = (d < Max(tolvclo,tolf));
	if (!sameclo) return Standard_False;
      }
      else return Standard_False;
    }
  }


  Standard_Boolean out = Standard_False;
  if (samevp) {
    Standard_Boolean isper = TopOpeBRepTool_ShapeTool::BASISCURVE(EL)->IsPeriodic();

    Standard_Integer f,l,n; L.VPBounds(f,l,n);
    if (isper && n == 2) {
      const TopOpeBRep_VPointInter& vpf1 = L.VPoint(f);
      const TopOpeBRep_VPointInter& vpl1 = L.VPoint(l);
      Standard_Integer ioo = (isedge1) ? 2 : 1;
      TopAbs_State sf = vpf1.State(ioo), sl = vpl1.State(ioo);
      Standard_Boolean bfl = Standard_True;
      // xpu120898 : when projection fails we get unknown status
      //             recall VP are same. (CTS21182,restriction edge 6)
      Standard_Boolean bf = (sf == TopAbs_IN || sf == TopAbs_ON);
      Standard_Boolean bl = (sl == TopAbs_IN || sl == TopAbs_ON);
//      bfl = bf && bl;
      if((sf == TopAbs_UNKNOWN)||(sl == TopAbs_UNKNOWN)) bfl = bf || bl;
      else    bfl = bf && bl;

      if ( bfl ) {
	out = Standard_False;
      } 
      else {
	out = Standard_True;
      }
    }
    else {
      out = Standard_True;
    }
  }
  if (out) {
    return Standard_False;
  }
  
  TopAbs_State stVPbip = StBipVPonF(vpf,vpl,L,isedge1);
  keeprline = (stVPbip == TopAbs_IN);
  keeprline = keeprline||(stVPbip==TopAbs_ON); // REST1
#ifdef DEB
//  if (trc) {
//    cout<<" bip("<<vpf.Index()<<","<<vpl.Index()<<") of line restriction ";
//    cout<<L.Index()<<" is ";TopAbs::Print(stVPbip,cout);
//    if (keeprline) cout<<" : edge restriction kept"<<endl;
//    else cout<<" : edge restriction kept not kept"<<endl; 
//  }
#endif	
    
  return keeprline;
}

Standard_EXPORT Standard_Boolean FUN_brep_sdmRE(const TopoDS_Edge& E1, const TopoDS_Edge& E2) 
{ // prequesitory : E1, E2 are restriction edges of opposite rank
  //                found in the same FacesFiller
  Standard_Boolean ok = Standard_False;
  BRepAdaptor_Curve BAC;
  TopoDS_Vertex v1,v2;TopExp::Vertices(E1,v1,v2);
  TopoDS_Vertex v3,v4;TopExp::Vertices(E2,v3,v4);
  if (!ok) {
    BAC.Initialize(E1);
    Standard_Real tol1 = BRep_Tool::Tolerance(E1);
    Standard_Real tol2 = BRep_Tool::Tolerance(v3);
    Standard_Real tol3 = BRep_Tool::Tolerance(v4);
    Standard_Real tol4 = Max(tol1,Max(tol2,tol3));
    if (!ok) {
      const gp_Pnt& P3 = BRep_Tool::Pnt(v3);
      ok = FUN_tool_PinC(P3,BAC,tol4);
    }
    if (!ok) {
      const gp_Pnt& P4 = BRep_Tool::Pnt(v4);
      ok = FUN_tool_PinC(P4,BAC,tol4);
    }
  }
  if (!ok) {
    BAC.Initialize(E2);
    Standard_Real tol1 = BRep_Tool::Tolerance(E2);
    Standard_Real tol2 = BRep_Tool::Tolerance(v1);
    Standard_Real tol3 = BRep_Tool::Tolerance(v2);
    Standard_Real tol4 = Max(tol1,Max(tol2,tol3));
    if (!ok) {
      const gp_Pnt& P1 = BRep_Tool::Pnt(v1);
      ok = FUN_tool_PinC(P1,BAC,tol4);
    }
    if (!ok) {
      const gp_Pnt& P2 = BRep_Tool::Pnt(v2);
      ok = FUN_tool_PinC(P2,BAC,tol4);
    }
  }
  return ok;
}

//=======================================================================
//function : ProcessSectionEdges
//purpose  : 
//=======================================================================
void TopOpeBRep_FacesFiller::ProcessSectionEdges()
{
#ifdef DEB   
  Standard_Boolean DSNC = TopOpeBRepDS_GettraceDSNC();
  if (DSNC) cout<<endl<<"--- Section Edges Processing : ---"<<endl;
#endif
  
  // recuperation des aretes d'intersection mapES
  // MSV: replace map with list to achieve predictable order of edges
  TopTools_ListOfShape LES;
  GetESL(LES);

  // add LES edges as section edges in the DS.
  TopTools_ListIteratorOfListOfShape itLES;
  for (itLES.Initialize(LES); itLES.More(); itLES.Next()) {
    const TopoDS_Edge& E = TopoDS::Edge(itLES.Value());

    Standard_Boolean isdg = BRep_Tool::Degenerated(E); //xpu290698
    if (isdg) continue;                   //xpu290698

#ifdef DEB
    Standard_Integer iSE =
#endif
              myDS->AddSectionEdge(E);
#ifdef DEB
    Standard_Integer iE =
#endif
              myDS->Shape(E);
#ifdef DEB
    Standard_Integer rE =
#endif
              myDS->AncestorRank(E);
#ifdef DEB
    if (DSNC) cout<<"add section edge "<<iSE<<" : "<<iE<<"("<<rE<<")"<<endl;
#endif
  }

  TColStd_ListOfInteger LOI; TColStd_ListIteratorOfListOfInteger itLOI;

  // LOI = liste des rank (1 ou 2 ) des aretes de section (liste LES)
  for( itLES.Initialize(LES); itLES.More(); itLES.Next()) {
    const TopoDS_Edge& ELES = TopoDS::Edge(itLES.Value());
    Standard_Boolean is1 = Standard_False;
    Standard_Boolean is2 = Standard_False;
    myFacesIntersector->InitLine();
    TopoDS_Edge ELI;
    for(;myFacesIntersector->MoreLine();myFacesIntersector->NextLine()){
      TopOpeBRep_LineInter& L = myFacesIntersector->CurrentLine();
      if (L.TypeLineCurve() != TopOpeBRep_RESTRICTION) continue;
      ELI = TopoDS::Edge(L.Arc());
      if ( ELI.IsEqual(ELES) ) {
	is1 = L.ArcIsEdge(1);
	is2 = L.ArcIsEdge(2);
	break;
      }
    }
    Standard_Real toappend = Standard_True;
    if (toappend) {
      if      (is1) LOI.Append(1);
      else if (is2) LOI.Append(2);
    }
  }
  
  // ajout des aretes de section dans la DS de shape,connaissant leur rank
  for (itLES.Initialize(LES),itLOI.Initialize(LOI);
       itLES.More(),itLOI.More();
       itLES.Next(),itLOI.Next()) {
    const TopoDS_Shape& E1 = itLES.Value();
    Standard_Integer rE1 = itLOI.Value();
    myDS->AddShape(E1,rE1);
  }
  
  // determination des aretes SameDomain en 3d pur
  // mapELE(arete(1)) -> {arete(2)}
  // mapELE(arete(2)) -> {arete(1)}
  TopTools_DataMapOfShapeListOfShape mapELE;
  for( itLES.Initialize(LES); itLES.More(); itLES.Next()) {
    const TopoDS_Edge& E1 = TopoDS::Edge(itLES.Value());
    Standard_Integer iE1 = myDS->Shape(E1);
    Standard_Integer rE1 = myDS->AncestorRank(iE1);
    if (rE1 != 1) continue;
    TopTools_ListOfShape thelist;
    mapELE.Bind(E1, thelist);

    TopTools_ListIteratorOfListOfShape itLES2;
    for (itLES2.Initialize(LES); itLES2.More(); itLES2.Next()) {
      const TopoDS_Edge& E2 = TopoDS::Edge(itLES2.Value());
      Standard_Integer iE2 = myDS->Shape(E2);
      Standard_Integer rE2 = myDS->AncestorRank(iE2);
      if ( rE2 == 0 || iE1 == iE2 || rE2 == rE1 ) continue;

      Standard_Boolean toappend = FUN_brep_sdmRE(E1,E2);
      if (toappend) { 
	mapELE.ChangeFind(E1).Append(E2);
      }
    }
  }

  TopTools_DataMapIteratorOfDataMapOfShapeListOfShape itmapELE;

#ifdef DEB
  if (DSNC) {
    for (itmapELE.Initialize(mapELE); itmapELE.More(); itmapELE.Next()) {
      const TopoDS_Edge& E1 = TopoDS::Edge(itmapELE.Key());
      Standard_Integer iE1 = myDS->Shape(E1);
      Standard_Integer rE1 = myDS->AncestorRank(iE1);
      cout<<"sd3d edge "<<iE1<<"("<<rE1<<") : ";
      TopTools_ListIteratorOfListOfShape itL(itmapELE.Value());
      for (; itL.More(); itL.Next()) {
	const TopoDS_Edge& E2 = TopoDS::Edge(itL.Value());
	Standard_Integer iE2 = myDS->Shape(E2);
	Standard_Integer rE2 = myDS->AncestorRank(iE2);
	cout<<iE2<<"("<<rE2<<") ";
      }
      cout<<endl;
    }
  }
#endif

  for (itmapELE.Initialize(mapELE); itmapELE.More(); itmapELE.Next()) {
    const TopoDS_Edge& E1 = TopoDS::Edge(itmapELE.Key());
    Standard_Integer iE1 = myDS->Shape(E1);
    Standard_Integer rE1 = myDS->AncestorRank(iE1);
    const TopoDS_Face& aFace1 = TopoDS::Face(myFacesIntersector->Face(rE1));
    Standard_Boolean isClosing1 = BRep_Tool::IsClosed(E1,aFace1);
    TopTools_ListIteratorOfListOfShape itL(itmapELE.Value());
    for (; itL.More(); itL.Next()) {
      const TopoDS_Edge& E2 = TopoDS::Edge(itL.Value());
      Standard_Integer iE2 = myDS->Shape(E2);
      Standard_Integer rE2 = myDS->AncestorRank(iE2);
      const TopoDS_Face& aFace2 = TopoDS::Face(myFacesIntersector->Face(rE2));
      Standard_Boolean isClosing2 = BRep_Tool::IsClosed(E2,aFace2);
      Standard_Boolean refFirst = isClosing1 || !isClosing2;
      myDS->FillShapesSameDomain(E1,E2,TopOpeBRepDS_UNSHGEOMETRY,
                                 TopOpeBRepDS_UNSHGEOMETRY, refFirst);
    }
  }
}
