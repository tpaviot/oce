// Created on: 1994-10-10
// Created by: Jean Yves LEBEY
// Copyright (c) 1994-1999 Matra Datavision
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

#include <Standard_ProgramError.hxx>
//#include <BRepAdaptor_Curve2d.hxx>
#include <TopOpeBRep_FFTransitionTool.hxx>
#include <TopOpeBRep.hxx>
#include <Precision.hxx>
#include <TopoDS.hxx>
#include <BRep_Tool.hxx>
#include <Geom_Surface.hxx>
#include <GeomProjLib.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Line.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <TopOpeBRepTool_EXPORT.hxx>
#include <TopOpeBRepTool_2d.hxx>
#include <TopOpeBRep_define.hxx>
#include <TopOpeBRepTool_defineG.hxx>
#include <TopOpeBRepTool_SC.hxx>

Standard_EXPORT Standard_Boolean FUN_projPonL(const gp_Pnt& P,const TopOpeBRep_LineInter L,const TopOpeBRep_FacesFiller& FF,
				 Standard_Real& paramL)
{
  Standard_Boolean paramLdef = Standard_False;
  Standard_Integer Esi = (L.ArcIsEdge(1)) ? 1:2;
  const TopoDS_Edge& E = TopoDS::Edge(L.Arc());
  Standard_Boolean hasC3D = FC2D_HasC3D(E);
  Standard_Real dist;
  if (hasC3D) {
    BRepAdaptor_Curve BAC(E);
    paramLdef = FUN_tool_projPonC(P,BAC,paramL,dist);
  }
  else {
    BRepAdaptor_Curve2d BAC2D;
    if      (Esi == 1)  BAC2D.Initialize(E,FF.Face(1));
    else if (Esi == 2)  BAC2D.Initialize(E,FF.Face(2));
    paramLdef = FUN_tool_projPonC2D(P,BAC2D,paramL,dist);
  }
  return paramLdef;
}

#ifdef DEB
extern Standard_Boolean TopOpeBRepDS_GettraceDSF(); 
extern Standard_Boolean TopOpeBRepDS_GettraceDSFK(); 
extern Standard_Boolean TopOpeBRepDS_GettraceDSNC(); 
void debffsamdom(void){}
#endif

static void FUN_MakeERL(TopOpeBRep_FacesIntersector& FI,TopTools_ListOfShape& ERL)
{
  ERL.Clear();
  const TopTools_IndexedMapOfShape& mer = FI.Restrictions();
  for ( Standard_Integer ie = 1, ne = mer.Extent(); ie <= ne; ie++) {
    const TopoDS_Edge& E = TopoDS::Edge(mer.FindKey(ie));
    ERL.Append(E);
  }
}

//=======================================================================
//function : TopOpeBRep_FacesFiller
//purpose  : 
//=======================================================================
TopOpeBRep_FacesFiller::TopOpeBRep_FacesFiller() : myPShapeClassifier(NULL)
{ 
  myexF1 = myexF2 = 0;
#ifdef DEB
  myHFFD = new TopOpeBRep_FFDumper(this);
#endif
}

//=======================================================================
//function : PShapeClassifier
//purpose  : 
//=======================================================================
TopOpeBRepTool_PShapeClassifier TopOpeBRep_FacesFiller::PShapeClassifier() const
{
  return myPShapeClassifier;
}

//=======================================================================
//function : SetPShapeClassifier
//purpose  : 
//=======================================================================
void TopOpeBRep_FacesFiller::SetPShapeClassifier(const TopOpeBRepTool_PShapeClassifier& PSC) 
{
  myPShapeClassifier = PSC;
}

//=======================================================================
//function : Insert
//purpose  : 
//=======================================================================
void TopOpeBRep_FacesFiller::Insert(const TopoDS_Shape& S1,const TopoDS_Shape& S2,TopOpeBRep_FacesIntersector& FACINT,const Handle(TopOpeBRepDS_HDataStructure)& HDS)
{
  myF1 = TopoDS::Face(S1); myF1ori = S1.Orientation();
  myF2 = TopoDS::Face(S2); myF2ori = S2.Orientation(); 
  myFacesIntersector = &FACINT;
  myHDS = HDS;
  myDS = &(HDS->ChangeDS());
  if (myPShapeClassifier == NULL) myPShapeClassifier = new TopOpeBRepTool_ShapeClassifier();

#ifdef DEB
  Standard_Integer exF1,exF2; GetTraceIndex(exF1,exF2);
  myFacesIntersector->InitLine();
  for (; myFacesIntersector->MoreLine(); myFacesIntersector->NextLine()) myFacesIntersector->CurrentLine().SetTraceIndex(exF1,exF2);
  myHFFD->Init(this);
#endif
  
  Standard_Boolean samdom = myFacesIntersector->SameDomain();
  if ( samdom ) {
    myDS->FillShapesSameDomain(S1,S2);
    return;
  }
  
  myFacesIntersector->InitLine();
  for (; myFacesIntersector->MoreLine(); myFacesIntersector->NextLine()) {
    TopOpeBRep_LineInter& L = myFacesIntersector->CurrentLine();
    L.SetFaces(TopoDS::Face(S1),TopoDS::Face(S2));
  }
  
  VP_Position(FACINT);

  myFacesIntersector->InitLine();
  for (; myFacesIntersector->MoreLine(); myFacesIntersector->NextLine()) {
    TopOpeBRep_LineInter& L = myFacesIntersector->CurrentLine();
    L.SetHasVPonR();
    L.SetINL();
    L.SetIsVClosed();
  }

  ProcessSectionEdges();
  myFFfirstDSP = myDS->NbPoints() + 1;

  FUN_MakeERL((*myFacesIntersector), myERL); // BUG

  myFacesIntersector->InitLine();
  for (; myFacesIntersector->MoreLine(); myFacesIntersector->NextLine()) {
    TopOpeBRep_LineInter& L = myFacesIntersector->CurrentLine();
    LoadLine(L);
    ProcessLine();
  }
  
}

//=======================================================================
//function : ChangePointClassifier
//purpose  : 
//=======================================================================
TopOpeBRep_PointClassifier& TopOpeBRep_FacesFiller::ChangePointClassifier()
{  
  return myPointClassifier;
}


//=======================================================================
//function : LoadLine
//purpose  : 
//=======================================================================
void TopOpeBRep_FacesFiller::LoadLine(TopOpeBRep_LineInter& L)
{
  myLine = &L;
  Standard_Boolean bchk = CheckLine(L);
  Standard_Boolean binl = L.INL();
  myLineINL = binl;
  {
    TopOpeBRep_TypeLineCurve t = L.TypeLineCurve();
    if ( !bchk && binl && t == TopOpeBRep_LINE ) {
      bchk = Standard_True;
    }
  }
  L.SetOK(bchk);
  myLineOK = bchk;
  if (!myLineOK) return;
  
  L.ComputeFaceFaceTransition();
} // LoadLine

//=======================================================================
//function : CheckLine
//purpose  : private
//           returns False if L is WALKING line with a number of VPoints < 2
//           else returns True 
//=======================================================================
Standard_Boolean TopOpeBRep_FacesFiller::CheckLine(TopOpeBRep_LineInter& L) const
{
  Standard_Real tol1,tol2;
  myFacesIntersector->GetTolerances(tol1,tol2);
  
  Standard_Boolean check = Standard_True;
  TopOpeBRep_TypeLineCurve t = L.TypeLineCurve();
  Standard_Integer nbvp = L.NbVPoint();
  
#ifdef DEB
  Standard_Boolean TDSF = TopOpeBRepDS_GettraceDSF();
  if (TDSF) { cout<<"CheckLine ";TopOpeBRep::Print(t,cout);cout<<" "<<nbvp<<" points"<<endl; }
#endif
  
  if ( t == TopOpeBRep_WALKING ) {
    if ( nbvp < 2 ) {
#ifdef DEB
      cout<<"\n=== Nb de IntPatch_Point sur WL incorrect : "<<nbvp<<" ===\n";
#endif
      check = Standard_False;
    }
  }
  else if (t == TopOpeBRep_LINE) {
    Standard_Integer np = 0;
    TopOpeBRep_VPointInterIterator VPI;
    
    for ( VPI.Init(L); VPI.More(); VPI.Next()) {
      const TopOpeBRep_VPointInter& VP = VPI.CurrentVP();
      if ( VP.Keep() ) np++;
    }
    if ( np != 2 ) {
      return Standard_True;
    }
    
    TopOpeBRep_VPointInter A,B;
    np = 0;
    for ( VPI.Init(L); VPI.More(); VPI.Next()) {
      const TopOpeBRep_VPointInter& VP = VPI.CurrentVP();
      if ( !VP.Keep() ) continue;
      np++;
      if ( np == 1 ) A = VP;
      if ( np == 2 ) B = VP;
    }
    
    Standard_Boolean isAV1 = A.IsVertexOnS1();
    Standard_Boolean isAV2 = A.IsVertexOnS2();
    TopoDS_Shape V1;
    if (isAV1) V1 = A.VertexOnS1();
    if (isAV2) V1 = A.VertexOnS2();
    Standard_Boolean isBV1 = B.IsVertexOnS1();
    Standard_Boolean isBV2 = B.IsVertexOnS2();
    TopoDS_Shape V2;
    if (isBV1) V2 = B.VertexOnS1();
    if (isBV2) V2 = B.VertexOnS2();
    
#ifdef DEB
    if (TDSF) {
      cout<<"CheckLine : isAV1 isAV2 isBV1 isBV2 ";
      cout<<isAV1<<" "<<isAV2<<" "<<isBV1<<" "<<isBV2<<endl;
    }
#endif
    
    if ( !V1.IsNull() && ( V1.IsSame(V2) ) ) {
#ifdef DEB
      Standard_Real parA = A.ParameterOnLine();    
      Standard_Real parB = B.ParameterOnLine();    
      if (TDSF) {
	cout<<"kpart : parA parB delta "<<parA<<" "<<parB<<" "<<parA-parB<<endl;
	cout<<"kpart : rejet de ligne"<<endl;
      }
#endif
      return Standard_False;      
    }
  } // LINE
  else {
    Standard_Boolean notrnotw = (t != TopOpeBRep_RESTRICTION && t != TopOpeBRep_WALKING);
    if (notrnotw) {
      if (t == TopOpeBRep_CIRCLE) { 
	// cto 012 D2, faces 6 et 1, line 3 incorrecte.
	
	Standard_Integer iINON1,iINONn,nINON;
	myLine->VPBounds(iINON1,iINONn,nINON);
	if ( nINON >= 2) {
	  
	  const TopOpeBRep_VPointInter& A = myLine->VPoint(iINON1);
	  const TopOpeBRep_VPointInter& B = myLine->VPoint(iINONn);
	  Standard_Real parA = A.ParameterOnLine();    
	  Standard_Real parB = B.ParameterOnLine();    
	  Standard_Boolean conf = (fabs(parA-parB) < tol1);
	  if (conf) {
	    //modified by NIZHNY-MZV  Wed Dec  1 09:53:08 1999
	    check = Msf;
//modified by NIZHNY-MZV  Wed Dec  1 09:53:18 1999	    Standard_Boolean isp = L.IsPeriodic();
//modified by NIZHNY-MZV  Wed Dec  1 09:53:20 1999	    if (isp) {
//modified by NIZHNY-MZV  Wed Dec  1 09:53:21 1999	      Handle(Geom_Circle) C = Handle(Geom_Circle)::DownCast(L.Curve());
//modified by NIZHNY-MZV  Wed Dec  1 09:53:22 1999	      Standard_Real per = C->Period();
//modified by NIZHNY-MZV  Wed Dec  1 09:53:23 1999	      parB = parA + per;
//modified by NIZHNY-MZV  Wed Dec  1 09:53:25 1999	    }
	  }
	  
//modified by NIZHNY-MZV  Wed Dec  1 09:53:32 1999	  Standard_Real t = 0.2567899311;
//modified by NIZHNY-MZV  Wed Dec  1 09:53:33 1999	  Standard_Real p = (1-t)*parA + t*parB;
//modified by NIZHNY-MZV  Wed Dec  1 09:53:34 1999	  Handle(Geom_Curve) GC = myLine->Curve();
//modified by NIZHNY-MZV  Wed Dec  1 09:53:34 1999	  const TopoDS_Face& F1 = TopoDS::Face(myF1);
//modified by NIZHNY-MZV  Wed Dec  1 09:53:35 1999	  const TopoDS_Face& F2 = TopoDS::Face(myF2);
//modified by NIZHNY-MZV  Wed Dec  1 09:53:36 1999	  Handle(Geom_Surface) GS1 = BRep_Tool::Surface(F1);
//modified by NIZHNY-MZV  Wed Dec  1 09:53:36 1999	  Handle(Geom_Surface) GS2 = BRep_Tool::Surface(F2);
//modified by NIZHNY-MZV  Wed Dec  1 09:53:37 1999	  Handle(Geom2d_Curve) C1 = GeomProjLib::Curve2d(GC,parA,parB,GS1);
//modified by NIZHNY-MZV  Wed Dec  1 09:53:38 1999	  Handle(Geom2d_Curve) C2 = GeomProjLib::Curve2d(GC,parA,parB,GS2);	  
	  
//modified by NIZHNY-MZV  Wed Dec  1 09:53:39 1999	  gp_Pnt2d P1 = C1->Value(p);
//modified by NIZHNY-MZV  Wed Dec  1 09:53:44 1999	  gp_Pnt2d P2 = C2->Value(p);
//modified by NIZHNY-MZV  Wed Dec  1 09:53:45 1999	  TopOpeBRep_PointClassifier* pcl = (TopOpeBRep_PointClassifier*)((void*)&myPointClassifier);
//modified by NIZHNY-MZV  Wed Dec  1 09:53:46 1999	  TopAbs_State staP1 = pcl->Classify(F1,P1,tol1);
//modified by NIZHNY-MZV  Wed Dec  1 09:53:47 1999	  TopAbs_State staP2 = pcl->Classify(F2,P2,tol1);
//modified by NIZHNY-MZV  Wed Dec  1 09:53:48 1999Standard_Boolean ok1 = (staP1 == TopAbs_IN || staP1 == TopAbs_ON);
//modified by NIZHNY-MZV  Wed Dec  1 09:53:49 1999	  Standard_Boolean ok2 = (staP2 == TopAbs_IN || staP2 == TopAbs_ON);
//modified by NIZHNY-MZV  Wed Dec  1 09:53:50 1999	  check = (ok1 && ok2);
	  
	}
      } // CIRCLE
      else if (t == TopOpeBRep_HYPERBOLA) {
	Standard_Integer iINON1,iINONn,nINON;
	myLine->VPBounds(iINON1,iINONn,nINON);
	if ( nINON < 2 ) {
	  check = Standard_False;
	}
      }
      else if (t == TopOpeBRep_ELLIPSE) {
	Standard_Integer iINON1,iINONn,nINON;
	myLine->VPBounds(iINON1,iINONn,nINON);
	if ( nINON < 2 ) {
	  check = Standard_False;
	}
	else {
	  const TopOpeBRep_VPointInter& A = myLine->VPoint(iINON1);
	  const TopOpeBRep_VPointInter& B = myLine->VPoint(iINONn);
	  Standard_Real parA = A.ParameterOnLine();    
	  Standard_Real parB = B.ParameterOnLine();    
	  Standard_Boolean conf = (fabs(parA-parB) < tol1);
	  if (conf) {
	    check = Standard_False;
	  }
	}
      }
    }
  }
  
#ifdef DEB
  if (!check) { cout<<"# DEB CheckLine : rejet de ";TopOpeBRep::Print(t,cout);cout<<" a "<<nbvp<<" points"<<endl; }
#endif

  return check;
}

//=======================================================================
//function : VP_Position
//purpose  : 
//=======================================================================
//void TopOpeBRep_FacesFiller::VP_Position(TopOpeBRep_FacesIntersector& FACINT)
void TopOpeBRep_FacesFiller::VP_Position(TopOpeBRep_FacesIntersector& )
{
  for (myFacesIntersector->InitLine(); 
       myFacesIntersector->MoreLine();
       myFacesIntersector->NextLine()) {
    TopOpeBRep_LineInter& L = myFacesIntersector->CurrentLine();
    const TopOpeBRep_TypeLineCurve tl = L.TypeLineCurve();
    Standard_Boolean ok = (tl == TopOpeBRep_RESTRICTION) ;
    if ( ok ) VP_Position(L);
  }
  
  for (myFacesIntersector->InitLine(); 
       myFacesIntersector->MoreLine(); 
       myFacesIntersector->NextLine()) {
    TopOpeBRep_LineInter& L = myFacesIntersector->CurrentLine();
    const TopOpeBRep_TypeLineCurve tl = L.TypeLineCurve();
    Standard_Boolean ok = (tl != TopOpeBRep_RESTRICTION) ;
    if ( ok ) VP_Position(L);
  }
}

//=======================================================================
//function : VP_Position
//purpose  : 
//=======================================================================
void TopOpeBRep_FacesFiller::VP_Position(TopOpeBRep_LineInter& L)
{
  myLine = &L;
#ifdef DEB
  if (TopOpeBRepDS_GettraceDSFK()) {
    cout<<endl<<"VP_Position on line "<<L.Index()<<" ";L.DumpType();cout<<endl;
  }
#endif
  Standard_Boolean isrest = (L.TypeLineCurve() == TopOpeBRep_RESTRICTION) ;
  
  if (!isrest) VP_PositionOnL(L);
  else         VP_PositionOnR(L);
  
  L.SetVPBounds();
  
#ifdef DEB
  if (TopOpeBRepDS_GettraceDSFK()) {
    Standard_Integer VPF,VPL,VPN; L.VPBounds(VPF,VPL,VPN);
    cout<<"SetVPBounds : VPF,VPL,VPN = "<<VPF<<","<<VPL<<","<<VPN;
    if (VPN != 0) cout<<" : VP(s) kept"<<endl;
    else          cout<<" : NO VP kept"<<endl;
  }
#endif
}

//=======================================================================
//function : VP_PositionOnL
//purpose  : 
//=======================================================================
void TopOpeBRep_FacesFiller::VP_PositionOnL(TopOpeBRep_LineInter& L)
{
  TopOpeBRep_VPointInterIterator VPI(L);
  Standard_Integer Lindex = L.Index();
  TopOpeBRep_VPointInterClassifier VPC;
  
  for (; VPI.More(); VPI.Next()) {
    TopOpeBRep_VPointInter& VP = VPI.ChangeCurrentVP();
    Standard_Integer VPsi = VP.ShapeIndex();
    const gp_Pnt& P3D = VP.Value();
    
    Standard_Boolean VPequalVPONRESTRICTION = Standard_False;
    TopOpeBRep_FacesIntersector& FI = *((TopOpeBRep_FacesIntersector*)((void*)myFacesIntersector));
    Standard_Integer iOL = 1,n = FI.NbLines(); 
    for (iOL=1; iOL<=n; iOL++ ) { 
      if (iOL == Lindex ) continue; 
      TopOpeBRep_LineInter& OL = FI.ChangeLine(iOL);
      VPequalVPONRESTRICTION = PequalVPonR(P3D,VPsi,VP,OL);
      if ( VPequalVPONRESTRICTION ) break;
    }
    
    if ( !VPequalVPONRESTRICTION ) {
      VP_Position(VP,VPC);
    }    
  }
}

//=======================================================================
//function : VP_PositionOnR
//purpose  : 
//=======================================================================
void TopOpeBRep_FacesFiller::VP_PositionOnR(TopOpeBRep_LineInter& L)
{
  TopOpeBRep_VPointInterClassifier VPC;
  
  TopOpeBRep_VPointInterIterator VPI(L);
  Standard_Integer Esi   = (L.ArcIsEdge(1)) ? 1:2;
  Standard_Integer OOEsi = (L.ArcIsEdge(1)) ? 2:1;
  
  Standard_Boolean isline = Standard_False;
  const TopoDS_Edge& earc = TopoDS::Edge(L.Arc());
  Standard_Boolean hasc3d = FC2D_HasC3D(earc);
  if (hasc3d) isline = FUN_tool_line(earc);
  else {
    BRepAdaptor_Curve2d BAC2D;
    if      (Esi == 1)  BAC2D.Initialize(earc,myF1);
    else if (Esi == 2)  BAC2D.Initialize(earc,myF2);
    GeomAbs_CurveType t = BAC2D.GetType();
    isline = (t == GeomAbs_Line);
  }
  
  for (; VPI.More(); VPI.Next()) {
    TopOpeBRep_VPointInter& VP = VPI.ChangeCurrentVP();
    
    Standard_Boolean isvertex = VP.IsVertex(Esi);
    if ( isvertex ) {
      if (!isline) VP_Position(VP,VPC);
      continue;
    }
    Standard_Boolean OOisvertex = VP.IsVertex(OOEsi);
    if ( OOisvertex ) {
      if (!isline) VP_Position(VP,VPC);
      continue;
    }
    
    const gp_Pnt& P = VP.Value();
    Standard_Boolean arcisE = L.ArcIsEdge(Esi);
    Standard_Boolean arcisOOE = L.ArcIsEdge(OOEsi);
    
    if (arcisE) {
      Standard_Real paramC;Standard_Boolean paramCdef = FUN_projPonL(P,L,(*this),paramC);
      if ( paramCdef ) {
	const TopoDS_Edge& E = TopoDS::Edge(L.Arc());
	VP.State(TopAbs_ON,Esi);
	VP.EdgeON(E,paramC,Esi);
      }
      else {
//	Standard_ProgramError::Raise("VP_Position projection failed on E");
	VP.ChangeKeep(Standard_False); // xpu051198
      }
    }
    
    if (arcisOOE) {
      Standard_Real paramC;Standard_Boolean paramCdef = FUN_projPonL(P,L,(*this),paramC);
      if ( paramCdef ) {
	const TopoDS_Edge& OOE = TopoDS::Edge(L.Arc());
	VP.State(TopAbs_ON,OOEsi);
	VP.EdgeON(OOE,paramC,OOEsi);
      }
      else {
//	Standard_ProgramError::Raise("VP_Position projection failed on OOE");
	VP.ChangeKeep(Standard_False); // xpu051198
      }
    }
    
#ifdef DEB
    if (TopOpeBRepDS_GettraceDSFK()) {
      cout<<"VP "<<VP.Index()<<" on "<<Esi<<" : ";
      TopAbs::Print(VP.State(Esi),cout);
      cout<<"/"<<Esi<<" ";
      if (VP.Keep()) { cout<<"kept"<<endl; }
      else           { cout<<"NOT kept"<<endl; }
    }
#endif
  }
}

//=======================================================================
//function : VP_Position
//purpose  : 
//=======================================================================
void TopOpeBRep_FacesFiller::VP_Position(TopOpeBRep_VPointInter& VP,TopOpeBRep_VPointInterClassifier& VPC)
{
  Standard_Integer si = VP.ShapeIndex();
  Standard_Boolean c1=Standard_False,c2=Standard_False;

  if      (si == 0) { c1 = Standard_True; c2 = Standard_True; }
  else if (si == 1) { c1 = Standard_False; c2 = Standard_True; }
  else if (si == 2) { c1 = Standard_True; c2 = Standard_False; }
  else if (si == 3) { c1 = Standard_True; c2 = Standard_True; }
  
  Standard_Boolean AssumeINON = Standard_False;
  if (myLine) AssumeINON = (myLine->TypeLineCurve() != TopOpeBRep_RESTRICTION);

  // modified by NIZHNY-MKK  Fri Oct 27 14:50:28 2000.BEGIN
  //   Standard_Real tol = Precision::Confusion();
  Standard_Real tol1, tol2;
  tol1 = tol2 = Precision::Confusion();
  myFacesIntersector->GetTolerances(tol1, tol2);
  Standard_Real tol = (tol1 > tol2) ? tol1 : tol2;
  // modified by NIZHNY-MKK  Fri Oct 27 14:50:36 2000.END

  if (c1) VPC.VPointPosition(myF1,VP,1,myPointClassifier,AssumeINON,tol);
  if (c2) VPC.VPointPosition(myF2,VP,2,myPointClassifier,AssumeINON,tol);
  
#ifdef DEB
  if (TopOpeBRepDS_GettraceDSFK()) {
    cout<<"VP "<<VP.Index()<<" on "<<si<<" : ";
    if (c1) { TopAbs::Print(VP.State(1),cout);cout<<"/1 "; }
    if (c2) { TopAbs::Print(VP.State(2),cout);cout<<"/2 "; }
    if (VP.Keep()) { cout<<"kept"<<endl; }
    else           { cout<<"NOT kept"<<endl; }
  }
#endif
}

//=======================================================================
//function : PequalVPonR
//purpose  : 
//=======================================================================
Standard_Boolean TopOpeBRep_FacesFiller::PequalVPonR(const gp_Pnt& P3D,const Standard_Integer VPsi,TopOpeBRep_VPointInter& VP,TopOpeBRep_LineInter& Lrest) const 
{
  const TopOpeBRep_TypeLineCurve tOL = Lrest.TypeLineCurve();
  Standard_Boolean OLok = (tOL == TopOpeBRep_RESTRICTION) ;
  if ( !OLok ) return Standard_False;
  
  Standard_Boolean VPequalVPONRESTRICTION = Standard_False;
  const TopoDS_Edge& EOL = TopoDS::Edge(Lrest.Arc());
  Standard_Integer EOLsi = (Lrest.ArcIsEdge(1)) ? 1:2;
  
  TopOpeBRep_VPointInterIterator VPIOL(Lrest);
  for (; VPIOL.More(); VPIOL.Next()) {
    TopOpeBRep_VPointInter& VPOL = VPIOL.ChangeCurrentVP();
    Standard_Integer VPOLsi = VPOL.ShapeIndex();
    
    Standard_Boolean VPOLisvertex = Standard_False;
    VPOLisvertex = VPOL.IsVertex(1);
    if (VPOLisvertex) continue;
    
    Standard_Boolean diffsi = (VPOLsi != VPsi);
    if ( diffsi ) continue;
    
    TopAbs_State stateEsi = VPOL.State(EOLsi);
    if (stateEsi != TopAbs_ON) continue; 
    
    const gp_Pnt& P3DOL = VPOL.Value();
    Standard_Real tolE = BRep_Tool::Tolerance(EOL);
    VPequalVPONRESTRICTION = P3DOL.IsEqual(P3D,tolE);
    
    if ( VPequalVPONRESTRICTION ) {
      Standard_Real paramCOL = VPOL.EdgeONParameter(EOLsi);
      VP.State(TopAbs_ON,EOLsi);
      VP.EdgeON(EOL,paramCOL,EOLsi);
      break;
    }
  }
  return VPequalVPONRESTRICTION;
}

//=======================================================================
//function : FacesIntersector
//purpose  : 
//=======================================================================
TopOpeBRep_FacesIntersector& TopOpeBRep_FacesFiller::ChangeFacesIntersector()
{
  return (*myFacesIntersector);
}

//=======================================================================
//function : HDataStructure
//purpose  : 
//=======================================================================
Handle(TopOpeBRepDS_HDataStructure) TopOpeBRep_FacesFiller::HDataStructure()
{
  return myHDS;
}

//=======================================================================
//function : DataStructure
//purpose  : 
//=======================================================================
TopOpeBRepDS_DataStructure& TopOpeBRep_FacesFiller::ChangeDataStructure()
{
  return (*myDS);
}

//=======================================================================
//function : Face
//purpose  : 
//=======================================================================
const TopoDS_Face& TopOpeBRep_FacesFiller::Face(const Standard_Integer I) const
{
  if      (I == 1) return myF1;
  else if (I == 2) return myF2;
  Standard_ProgramError::Raise("FacesFiller::Face");
  return myF1;
}

//=======================================================================
//function : FaceFaceTransition
//purpose  : 
//=======================================================================
const TopOpeBRepDS_Transition& TopOpeBRep_FacesFiller::FaceFaceTransition(const TopOpeBRep_LineInter& L,const Standard_Integer I) const
{
  const TopOpeBRepDS_Transition& T = L.FaceFaceTransition(I);
  return T;
}

//=======================================================================
//function : FaceFaceTransition
//purpose  : 
//=======================================================================
const TopOpeBRepDS_Transition& TopOpeBRep_FacesFiller::FaceFaceTransition(const Standard_Integer I) const
{
  const TopOpeBRepDS_Transition& T = myLine->FaceFaceTransition(I);
  return T;
}

TopOpeBRep_PFacesIntersector TopOpeBRep_FacesFiller::PFacesIntersectorDummy() const 
{return myFacesIntersector;}
TopOpeBRepDS_PDataStructure TopOpeBRep_FacesFiller::PDataStructureDummy() const 
{return myDS;}
TopOpeBRep_PLineInter TopOpeBRep_FacesFiller::PLineInterDummy() const 
{return myLine;}

//=======================================================================
//function : SetTraceIndex
//purpose  : 
//=======================================================================
void TopOpeBRep_FacesFiller::SetTraceIndex(const Standard_Integer exF1,const Standard_Integer exF2)
{ 
  myexF1 = exF1;
  myexF2 = exF2;
}

//=======================================================================
//function : GetTraceIndex
//purpose  : 
//=======================================================================
void TopOpeBRep_FacesFiller::GetTraceIndex(Standard_Integer& exF1,Standard_Integer& exF2)const 
{ 
  exF1 = myexF1;
  exF2 = myexF2;
}
