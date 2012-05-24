// Created on: 1996-10-23
// Created by: Jean Yves LEBEY
// Copyright (c) 1996-1999 Matra Datavision
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


#include <TopOpeBRep_FFDumper.ixx>
#include <TopExp_Explorer.hxx>
#include <TopAbs.hxx>
#include <TopOpeBRep_FacesIntersector.hxx>
#include <TopOpeBRep_VPointInterIterator.hxx>
#include <TopOpeBRep_VPointInter.hxx>
#include <TopOpeBRep.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <TopOpeBRepTool_ShapeTool.hxx>
#include <BRep_Tool.hxx>
#include <TopOpeBRep_FFTransitionTool.hxx>
#include <gp_Dir.hxx>
#include <gp_Pnt.hxx>
#include <TopOpeBRep_FacesFiller.hxx>
#include <TopOpeBRep_define.hxx>
#include <IntPatch_GLine.hxx>

#ifdef DEB
Standard_IMPORT Standard_Boolean TopOpeBRepDS_GettraceDSNC(); 
Standard_IMPORT Standard_Boolean TopOpeBRepDS_GettraceDSF(); 
Standard_IMPORT Standard_Boolean TopOpeBRepDS_GettraceDSFK(); 
static TCollection_AsciiString PRODINP("dinp ");
#endif

//=======================================================================
//function : TopOpeBRep_FFDumper
//purpose  : 
//=======================================================================
#ifndef DEB
TopOpeBRep_FFDumper::TopOpeBRep_FFDumper(const TopOpeBRep_PFacesFiller& )
{
#else
TopOpeBRep_FFDumper::TopOpeBRep_FFDumper(const TopOpeBRep_PFacesFiller& PFF)
{
  Init(PFF);
#endif
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================
#ifndef DEB
void TopOpeBRep_FFDumper::Init(const TopOpeBRep_PFacesFiller& )
{
#else
void TopOpeBRep_FFDumper::Init(const TopOpeBRep_PFacesFiller& PFF)
{
  myPFF = PFF;
  const TopoDS_Face& fpff1 = myPFF->Face(1);
  const TopoDS_Face& fpff2 = myPFF->Face(2);
  Standard_Boolean f1diff = (!myF1.IsEqual(fpff1));
  Standard_Boolean f2diff = (!myF2.IsEqual(fpff2));
  Standard_Boolean init = f1diff || f2diff;
  if (init) {
    myF1 = myPFF->Face(1);
    myF2 = myPFF->Face(2);
    myEM1.Clear(); myEn1 = 0;
    myEM2.Clear(); myEn2 = 0;
    TopExp_Explorer x;
    for (x.Init(myF1,TopAbs_EDGE);x.More();x.Next()) myEM1.Bind(x.Current(),++myEn1);
    for (x.Init(myF2,TopAbs_EDGE);x.More();x.Next()) myEM2.Bind(x.Current(),++myEn2);
    myLineIndex = 0;
  }
#endif
}

//=======================================================================
//function : DumpLine
//purpose  : 
//=======================================================================
#ifndef DEB
void TopOpeBRep_FFDumper::DumpLine(const Standard_Integer )
{
#else
void TopOpeBRep_FFDumper::DumpLine(const Standard_Integer I)
{
  const TopOpeBRep_LineInter& L = myPFF->ChangeFacesIntersector().ChangeLine(I);
  DumpLine(L);
#endif
}

//=======================================================================
//function : DumpLine
//purpose  : 
//=======================================================================
#ifndef DEB
void TopOpeBRep_FFDumper::DumpLine(const TopOpeBRep_LineInter& )
{
#else
void TopOpeBRep_FFDumper::DumpLine(const TopOpeBRep_LineInter& LI)
{
  Standard_Integer il = LI.Index();
  myLineIndex = il;
  Standard_Integer nl = myPFF->ChangeFacesIntersector().NbLines();
  Standard_Boolean HasVPonR = LI.HasVPonR();
  Standard_Boolean IsVClosed  = LI.IsVClosed();
  Standard_Boolean IsPeriodic = LI.IsPeriodic();
  Standard_Boolean isrest = (LI.TypeLineCurve() == TopOpeBRep_RESTRICTION);
  
  cout<<endl<<"--------------------------------------------------"<<endl;
  cout<<"line "<<il<<"/"<<nl<<" is a "; LI.DumpType(); 
  if ( isrest) { 
    Standard_Boolean isedge1 = LI.ArcIsEdge(1);
    Standard_Boolean isedge2 = LI.ArcIsEdge(2);
    if      ( isedge1 ) cout<<" of 1";
    else if ( isedge2 ) cout<<" of 2";
    else cout<<"of 0(BUG)";
  }
  cout<<endl;
  if ( isrest) { 
    const TopoDS_Shape& Erest = LI.Arc();
    Standard_Boolean FIisrest = myPFF->ChangeFacesIntersector().IsRestriction(Erest);
    cout<<"++++ line restriction"; 
    if (FIisrest) {
      cout<<" edge restriction";
      Standard_Integer iErest = 0; 
      if (myPFF->ChangeDataStructure().HasShape(Erest)) 
	iErest = myPFF->ChangeDataStructure().Shape(Erest);
      cout<<" "<<iErest;
    }
    cout<<endl;
  }
  if (HasVPonR) cout<<"has vertex on restriction"<<endl;
  else         cout<<"has no vertex on restriction"<<endl;
  if (IsVClosed)  cout<<"is closed by vertices"<<endl;
  else         cout<<"is not closed by vertices"<<endl;
  if (IsPeriodic) cout<<"is periodic"<<endl;
  else         cout<<"is not periodic"<<endl;
  
  TopOpeBRep_VPointInterIterator VPI;
  
  VPI.Init(LI); if (VPI.More()) cout<<endl;
  for (;VPI.More();VPI.Next()) {
    TCollection_AsciiString stol("; #draw ");
    stol = stol + VPI.CurrentVP().Tolerance() + "\n";
    LI.DumpVPoint(VPI.CurrentVPIndex(),PRODINP,stol);
  }
  
  VPI.Init(LI);
  if (VPI.More()) cout<<endl;
  for (;VPI.More();VPI.Next()) {
    const TopOpeBRep_VPointInter& VP = VPI.CurrentVP();
    Standard_Boolean dump = VP.Keep() || TopOpeBRepDS_GettraceDSFK();
    if (dump) { DumpVP(VP); cout<<endl; }
  }
  
  if (LI.TypeLineCurve() == TopOpeBRep_LINE) {
    gp_Dir D = LI.LineG()->Line().Direction();
    TopOpeBRep::Print(LI.TypeLineCurve(),cout); Standard_Real x,y,z; D.Coord(x,y,z);
    cout<<" dir : "<<x<<" "<<y<<" "<<z<<endl;
  }
  
  LI.DumpLineTransitions(cout);
  
  cout<<endl<<"--------------------------------------------------"<<endl;
#endif
}

//=======================================================================
//function : DumpVP
//purpose  : 
//=======================================================================
#ifndef DEB
void TopOpeBRep_FFDumper::DumpVP(const TopOpeBRep_VPointInter& )
{
#else
void TopOpeBRep_FFDumper::DumpVP(const TopOpeBRep_VPointInter& VP)
{
  Standard_Integer il = myLineIndex;
  cout<<"VP "<<VP.Index()<<" on "<<VP.ShapeIndex()<<" :";
  Standard_Real Cpar = VP.ParameterOnLine(); cout<<" on curve : "<<Cpar; 
  if (!VP.Keep()) cout<<" NOT kept";
  cout<<endl;
  Standard_Boolean k = VP.Keep();
  const gp_Pnt& P = VP.Value();
  cout<<PRODINP<<"L"<<il<<"P"<<VP.Index();if (k) cout<<"K";cout<<" "<<P.X()<<" "<<P.Y()<<" "<<P.Z();
  cout<<"; #draw"<<endl;
  
  if (TopOpeBRepDS_GettraceDSFK()) { 
    Standard_Real u,v;
    VP.ParametersOnS1(u,v); cout<<"u1,v1 : "<<u<<" "<<v; cout<<"   ";
    VP.ParametersOnS2(u,v); cout<<"u2,v2 : "<<u<<" "<<v; cout<<endl;
  }
  
  if      (VP.ShapeIndex() == 1) 
    DumpVP(VP,1);
  else if (VP.ShapeIndex() == 2)
    DumpVP(VP,2);
  else if (VP.ShapeIndex() == 3) {
    DumpVP(VP,1);
    DumpVP(VP,2);
  }
#endif
}

//=======================================================================
//function : DumpVP
//purpose  : 
//=======================================================================
#ifndef DEB
void TopOpeBRep_FFDumper::DumpVP(const TopOpeBRep_VPointInter& ,const Standard_Integer )
{
#else
void TopOpeBRep_FFDumper::DumpVP(const TopOpeBRep_VPointInter& VP,const Standard_Integer ISI)
{
  const Handle(TopOpeBRepDS_HDataStructure)& HDS = myPFF->HDataStructure();
  const TopoDS_Edge& E = TopoDS::Edge(VP.Edge(ISI)); 
  Standard_Real Epar = VP.EdgeParameter(ISI);
  TopAbs_Orientation O = E.Orientation(); 
  TopOpeBRepDS_Transition T = TopOpeBRep_FFTransitionTool::ProcessLineTransition(VP,ISI,O);
  const TopoDS_Face F = myPFF->Face(ISI);
  Standard_Boolean Closed = TopOpeBRepTool_ShapeTool::Closed(E,F);
  Standard_Boolean Degen = BRep_Tool::Degenerated(E);
  Standard_Integer exi = ExploreIndex(E,ISI);
  Standard_Integer dsi = (HDS->HasShape(E)) ? HDS->Shape(E) : 0;
  Standard_Boolean isv = VP.IsVertex(ISI);
  if (isv) cout<<"is vertex of "<<ISI<<endl;
  if (Closed) cout<<"on closing edge "; else cout<<"on edge "; 
  if (Degen) cout<<" on degenerated edge ";
  TopAbs::Print(O,cout); cout<<" (ds"<<dsi<<") (ex"<<exi<<") of face of "<<ISI;
  cout<<" : par : "<<Epar<<endl;  
  if (Closed) cout<<"on closing edge "; else cout<<"on edge "; 
  if (Degen) cout<<" on degenerated edge ";
  TopAbs::Print(O,cout); cout<<" (ds"<<dsi<<") (ex"<<exi<<") of face of "<<ISI;
  cout<<" : line transition : ";T.Dump(cout);cout<<endl;
#endif
}

//=======================================================================
//function : ExploreIndex
//purpose  : 
//=======================================================================
#ifndef DEB
Standard_Integer TopOpeBRep_FFDumper::ExploreIndex(const TopoDS_Shape& , const Standard_Integer ) const
{
	return 0;
}
#else
Standard_Integer TopOpeBRep_FFDumper::ExploreIndex(const TopoDS_Shape& S, const Standard_Integer ISI) const
{
  Standard_Integer r = 0;
  if (ISI == 1) r = myEM1.Find(S);
  if (ISI == 2) r = myEM2.Find(S);
  return r;
}
#endif

//=======================================================================
//function : DumpDSP
//purpose  : 
//=======================================================================
#ifndef DEB
void TopOpeBRep_FFDumper::DumpDSP(const TopOpeBRep_VPointInter& ,const TopOpeBRepDS_Kind ,const Standard_Integer ,
				  const Standard_Boolean ) const
{
#else
void TopOpeBRep_FFDumper::DumpDSP(const TopOpeBRep_VPointInter& VP,const TopOpeBRepDS_Kind GK,const Standard_Integer G,
				  const Standard_Boolean newinDS) const
{
  cout<<"VP "<<VP.Index()<<" on "<<VP.ShapeIndex();
  if (newinDS) {
    if      (GK == TopOpeBRepDS_VERTEX) cout<<" gives new DSV";
    else if (GK == TopOpeBRepDS_POINT)  cout<<" gives new DSP";
    else                                cout<<" gives new DS???";
  }
  else {
    if      (GK == TopOpeBRepDS_VERTEX) cout<<" equals new DSV";
    else if (GK == TopOpeBRepDS_POINT)  cout<<" equals new DSP";
    else                                cout<<" equals new DS???";
  }
  cout<<" "<<G;
  
  const Handle(TopOpeBRepDS_HDataStructure)& HDS = myPFF->HDataStructure();
  Standard_Real tol = -1.0;
  if      (GK == TopOpeBRepDS_VERTEX) tol = BRep_Tool::Tolerance(TopoDS::Vertex(HDS->Shape(G)));
  else if (GK == TopOpeBRepDS_POINT)  tol = HDS->Point(G).Tolerance();
  cout<<" tol = "<<tol;
  cout<<endl;
#endif
}

TopOpeBRep_PFacesFiller TopOpeBRep_FFDumper::PFacesFillerDummy() const {return myPFF;}
