// Copyright (c) 1998-1999 Matra Datavision
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


// Robert Boehne 30 May 2000 : Dec Osf

#include <TopOpeBRepDS_FIR.ixx>
#include <TopOpeBRepDS_define.hxx>
#include <TopOpeBRepTool_EXPORT.hxx>
#include <TopOpeBRepTool_SC.hxx>

#include <TopOpeBRepDS_ProcessInterferencesTool.hxx>
#include <TopoDS.hxx>
#include <TopExp_Explorer.hxx>
#include <TopOpeBRepDS_FaceInterferenceTool.hxx>
#include <TopOpeBRepDS_CurvePointInterference.hxx>
#include <TopOpeBRepDS_ShapeShapeInterference.hxx>
#include <TopOpeBRepDS_ShapeData.hxx>
#include <TopOpeBRepDS_MapOfShapeData.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRep_Builder.hxx>
#include <BRep_Tool.hxx>
#include <TopOpeBRepDS_ListOfShapeOn1State.hxx>
#include <TopOpeBRepDS_DataMapOfShapeListOfShapeOn1State.hxx>

#define MDSke TopOpeBRepDS_EDGE
#define MDSkf TopOpeBRepDS_FACE

#ifdef DEB
Standard_EXPORT void debrededg(const Standard_Integer I) {cout<<"+++ debrededg f"<<I<<endl;}
Standard_EXPORT void debredfac(const Standard_Integer I) {cout<<"+++ debredfac f"<<I<<endl;}
void FUN_dumploiS(const TopoDS_Shape& SG,const TopOpeBRepDS_ListOfInterference& loi,const TopOpeBRepDS_DataStructure& BDS,TCollection_AsciiString str) 
{
  cout<<str<<"   G : "<<BDS.Shape(SG)<<"   S : ";
  for(TopOpeBRepDS_ListIteratorOfListOfInterference it(loi);it.More();it.Next()) cout<<it.Value()->Support()<<" "; 
  cout<<endl;cout.flush();
}
void FUN_dumpmosd(TopOpeBRepDS_MapOfShapeData& mosd,const TopOpeBRepDS_DataStructure& BDS,const Standard_Integer F,TCollection_AsciiString str) 
{
  cout<<str<<"GmapS sur ";TopAbs::Print(BDS.Shape(F).ShapeType(),cout);
  cout<<" "<<F<<" : "<<mosd.Extent()<<" (GK EDGE)(SK FACE)"<<endl;
  for(Standard_Integer i=1,n=mosd.Extent();i<=n;i++) {
    FUN_dumploiS(mosd.FindKey(i),mosd.FindFromIndex(i).Interferences(),BDS,str);
  }
}
#endif

#ifdef DEB
Standard_EXPORT Standard_Boolean TopOpeBRepDS_GettraceSTRANGE();
Standard_EXPORT Standard_Boolean TopOpeBRepDS_GettracePEI();
Standard_EXPORT Standard_Boolean TopOpeBRepDS_GettracePFI();
Standard_EXPORT Standard_Boolean TopOpeBRepDS_GettracePI();
Standard_EXPORT Standard_Boolean TopOpeBRepDS_GettraceSPSX(const Standard_Integer);
static Standard_Boolean FTRCF(const Standard_Integer F) {
  Standard_Boolean b1 = TopOpeBRepDS_GettracePFI();
  Standard_Boolean b2 = TopOpeBRepDS_GettracePI();
  Standard_Boolean b3 = TopOpeBRepDS_GettraceSPSX(F);
  return (b1 || b2 || b3);
}
static Standard_Boolean FTRCE(const Standard_Integer E) {
  Standard_Boolean b1 = TopOpeBRepDS_GettracePEI();
  Standard_Boolean b2 = TopOpeBRepDS_GettracePI();
  Standard_Boolean b3 = TopOpeBRepDS_GettraceSPSX(E);
  return (b1 || b2 || b3);
}
#endif

Standard_EXPORT Standard_Boolean FUN_Parameters(const gp_Pnt& Pnt,const TopoDS_Shape& F,Standard_Real& u,Standard_Real& v);
Standard_EXPORT Standard_Boolean FUN_edgeofface(const TopoDS_Shape& E,const TopoDS_Shape& F);

//------------------------------------------------------
Standard_Boolean FUN_isPonF(const TopOpeBRepDS_ListOfInterference& LIF,const gp_Pnt& P,const TopOpeBRepDS_DataStructure& BDS,const TopoDS_Edge& E)
{
  Standard_Boolean Pok = Standard_True;
  TopOpeBRepDS_Kind GT1,ST1; Standard_Integer G1,S1;

  TopOpeBRepDS_ListIteratorOfListOfInterference itF(LIF);
  for (;itF.More();itF.Next()) {
    Handle(TopOpeBRepDS_Interference)& IF = itF.Value(); FDS_data(IF,GT1,G1,ST1,S1);
    const TopoDS_Face& F = TopoDS::Face(BDS.Shape(S1));
    TopAbs_Orientation oEinF; Standard_Boolean edonfa = FUN_tool_orientEinFFORWARD(E,F,oEinF );
    if ( edonfa ) Pok = Standard_True;
    else {
      // P est NOK pour une face de LIF : arret
      Standard_Real u,v; Pok = FUN_Parameters(P,F,u,v);
      if (!Pok) break;
    }
  }
  return Pok;
}

//------------------------------------------------------
Standard_Boolean FUN_findPonF(const TopoDS_Edge& E,const TopOpeBRepDS_DataStructure& BDS, const TopOpeBRepDS_ListOfInterference& LIF,gp_Pnt& P,Standard_Real& par)
{
  Standard_Boolean Pok = Standard_False;
  BRepAdaptor_Curve BAC(E);
  const TopOpeBRepDS_ListOfInterference& LIE = BDS.ShapeInterferences(E);
  TopOpeBRepDS_ListIteratorOfListOfInterference itI; itI.Initialize(LIE);

  if ( !itI.More() ) {
    Pok = FUN_tool_findPinBAC(BAC,P,par);
    Pok = FUN_isPonF(LIF,P,BDS,E);
    return Pok;
  }
  
  TopOpeBRepDS_Kind GT1,ST1;Standard_Integer G1,S1;
  for (;itI.More();itI.Next()) {
    Standard_Boolean pardef = Standard_False;
    
    Handle(TopOpeBRepDS_Interference)& I = itI.Value(); FDS_data(I,GT1,G1,ST1,S1);        
    const Handle(TopOpeBRepDS_CurvePointInterference)& CPI = Handle(TopOpeBRepDS_CurvePointInterference)::DownCast(I);
    const Handle(TopOpeBRepDS_ShapeShapeInterference)& SSI = Handle(TopOpeBRepDS_ShapeShapeInterference)::DownCast(I);
    if      (!CPI.IsNull()) {
      par = CPI->Parameter(); pardef = Standard_True;
    }
    else if (!SSI.IsNull()) {
      Standard_Boolean gb = SSI->GBound();
      if (gb) {
	const TopoDS_Vertex& V = TopoDS::Vertex(BDS.Shape(G1));
	P = BRep_Tool::Pnt(V); par = BRep_Tool::Parameter(V,E); pardef = Standard_True;
      }
      else {
	pardef = Standard_False;
	if      (GT1 == TopOpeBRepDS_POINT)  P = BDS.Point(G1).Point();
	else if (GT1 == TopOpeBRepDS_VERTEX) P = BRep_Tool::Pnt(TopoDS::Vertex(BDS.Shape(G1)));
	if (pardef) { 
	  Standard_Real dist; pardef = FUN_tool_projPonC(P,BAC,par,dist);
	}
      }
    }
    else {
      continue;
    }

    if (!pardef) {
      continue;
    }

    BAC.D0(par,P);
    Pok = FUN_isPonF(LIF,P,BDS,E);
    // P est OK pour toutes les faces de LIF : on arrete de chercher
    if (Pok) {
      break;
    }
  }
  return Pok;
}

// --------------------------------------------------------
static void FDS_DUMPTRANSITION(const Standard_Boolean
#ifdef DEB
                                                      TRCF
#endif 
                               ,const TCollection_AsciiString&
#ifdef DEB
                                                      str
#endif 
                               ,const Standard_Integer
#ifdef DEB
                                                      iFI
#endif 
                               ,TopOpeBRepDS_FaceInterferenceTool&
#ifdef DEB
                                                                   FITool
#endif 
                               )
{
#ifdef DEB
  if (TRCF) {
    cout<<str<<iFI<<endl;
    Handle(TopOpeBRepDS_Interference) IBID = new TopOpeBRepDS_Interference();
    FITool.Transition(IBID);
    IBID->Transition().Dump(cout);cout<<endl;
  }
#endif
}

// --------------------------------------------------------
static void FDS_ADDEDGE
(const Standard_Boolean
#ifdef DEB
                        TRCF
#endif 
 ,const TCollection_AsciiString&
#ifdef DEB
                                 str
#endif 
 ,const Standard_Integer
#ifdef DEB
                        iFI // DEB args
#endif 
 ,TopOpeBRepDS_FaceInterferenceTool& FITool
 ,const TopoDS_Shape& FI
 ,const TopoDS_Shape& F
 ,const TopoDS_Shape& Ecpx
 ,const Standard_Boolean isEGsp
 ,const Handle(TopOpeBRepDS_Interference)& I
)
{
#ifdef DEB
  if (TRCF) {TCollection_AsciiString cr("\n"),s=str+iFI+cr;I->Dump(cout,s,cr);}
#endif 
  FITool.Add(FI,F,Ecpx,isEGsp,I);
#ifdef DEB
  FDS_DUMPTRANSITION(TRCF,"--> resultat partiel sur face ",iFI,FITool);
#endif
}

//------------------------------------------------------
// EGsp = edge splittee de iEG ( Null si iEG n'est pas splittee)
void FUN_reduceEDGEgeometry1
(TopOpeBRepDS_ListOfInterference& LI,const TopOpeBRepDS_DataStructure& BDS,const Standard_Integer iFI,const Standard_Integer iEG,const TopoDS_Shape& EGsp,
// const TopOpeBRepDS_DataMapOfShapeListOfShapeOn1State& MEsp)
 const TopOpeBRepDS_DataMapOfShapeListOfShapeOn1State& )
{
  Standard_Boolean TRCF = Standard_False;
#ifdef DEB
  Standard_Boolean TRCE = Standard_False;
  TRCE = FTRCE(iEG);if (TRCE) debrededg(iEG);
  TRCF = FTRCF(iFI);if (TRCF) debredfac(iFI);
#endif

  TopOpeBRepDS_ListIteratorOfListOfInterference ili(LI); if (!ili.More()) return; 

  // choix de l'arete Ecpx, lieu de resolution de la transition complexe
  const TopoDS_Face& FI = TopoDS::Face(BDS.Shape(iFI));
  Standard_Boolean isEGsp = (! EGsp.IsNull());
  TopoDS_Edge Ecpx;
  if (isEGsp) Ecpx = TopoDS::Edge(EGsp);
  else        Ecpx = TopoDS::Edge(BDS.Shape(iEG));

  TopOpeBRepDS_PDataStructure pbds = (TopOpeBRepDS_PDataStructure)(void*)&BDS;
  TopOpeBRepDS_FaceInterferenceTool FITool(pbds);
  gp_Pnt Pok; Standard_Boolean isPok = Standard_False; Standard_Real parPok;
  if ( LI.Extent() >= 2) {
    if ( isEGsp ) isPok = FUN_tool_findPinE(Ecpx,Pok,parPok);
    else          isPok = FUN_findPonF(Ecpx,BDS,LI,Pok,parPok); // NYI pas necessaire
    if (!isPok) { LI.Clear(); return; }
    FITool.SetEdgePntPar(Pok,parPok);
  }

  // xpu :090498 : 
  //      CTS20205 : sp(e5) = sp(e4 of rank=1) and c3d(e5) c3d(e4) are diff oriented
  //            As transitions on face<iFI> are given relative to the geometry of e5,
  //            we have to complement them.
//  Standard_Boolean toreverse = Standard_False;
//  Standard_Boolean hsdm = !BDS.ShapeSameDomain(iEG).IsEmpty();
//  if (hsdm) {
//    Standard_Boolean sameoriented = Standard_False;
//    Standard_Boolean ok = FUN_tool_curvesSO(TopoDS::Edge(Ecpx),parPok,TopoDS::Edge(BDS.Shape(iEG)),
//			       sameoriented); 
//    if (ok) toreverse = !sameoriented;
//  }
  // xpu :090498

  // FI = face de reference (shape), iFI (indice)
  // E = arete geometrie d'interference (shape), iEG (indice)
  // LI = liste d'interf de geom iEG et dont les Support() sont a transitionner complexe

  Handle(TopOpeBRepDS_Interference) I1,I2; TopOpeBRepDS_Kind GT1,ST1,GT2,ST2; Standard_Integer G1,S1,G2,S2;
  TopOpeBRepDS_ListIteratorOfListOfInterference it1; it1.Initialize(LI);
  while (it1.More()) {
    Standard_Boolean u1 = FDS_data(it1,I1,GT1,G1,ST1,S1);if (u1) {it1.Next();continue;}
    Standard_Boolean ya1 = (GT1 == MDSke); if (!ya1) {it1.Next();continue;}
    
    Standard_Boolean isComplex = Standard_False; // True if at least two interfs on the same edge
    const TopoDS_Face& F1 = TopoDS::Face(BDS.Shape(S1));
    
    TopOpeBRepDS_ListIteratorOfListOfInterference it2(it1); it2.Next();
    while (it2.More()) {
      Standard_Boolean u2 = FDS_data(it2,I2,GT2,G2,ST2,S2);if (u2) {it2.Next();continue;}
      Standard_Boolean ya2 = (GT2==GT1 && G2==G1 && ST2==ST1); if (!ya2) {it2.Next();continue;}
      const TopoDS_Face& F2 = TopoDS::Face(BDS.Shape(S2));
      if (!isComplex) {
	isComplex = Standard_True;

	 
//	TopOpeBRepDS_Transition T1 = I1->Transition(); TopAbs_Orientation O1 = T1.Orientation(TopAbs_IN); // xpu :090498	
//	Standard_Boolean revT1 = toreverse && (M_FORWARD(O1) || M_REVERSED(O1));      // xpu :090498	
#ifdef DEB
//	if ((TRCE || TRCF) && revT1) cout<<"-> REVERSE T"<<endl;
#endif
//	if (revT1) I1->ChangeTransition() = T1.Complement();  //xpu :090498
	FITool.Init(FI,Ecpx,isEGsp,I1);
	FDS_ADDEDGE(TRCF,"\ninit transition complexe F",iFI,FITool,FI,F1,Ecpx,isEGsp,I1);
//	if (revT1) I1->ChangeTransition() = T1.Complement();  //xpu :090498
      }
    
//      TopOpeBRepDS_Transition T2 = I2->Transition(); TopAbs_Orientation O2 = T2.Orientation(TopAbs_IN);  // xpu :090498 
//      Standard_Boolean revT2 = toreverse && (M_FORWARD(O2) || M_REVERSED(O2));       // xpu :090498       
#ifdef DEB
//	if ((TRCE || TRCF) && revT2) cout<<"-> REVERSE T"<<endl;
#endif 
//      if (revT2) I2->ChangeTransition() = T2.Complement();  //xpu :090498
      FDS_ADDEDGE(TRCF,"add transition complexe F",iFI,FITool,FI,F2,Ecpx,isEGsp,I2);
//      if (revT2) I2->ChangeTransition() = T2.Complement();  //xpu :090498 

      LI.Remove(it2);
    }
    if (isComplex) {
      FITool.Transition(I1);
      FDS_DUMPTRANSITION(TRCF,"--> result transition on face ",iFI,FITool); // DEB
    }
    it1.Next();
  }  // it1.More()
} // FUN_reduceEDGEgeometry1

//------------------------------------------------------
void FUN_GmapS(TopOpeBRepDS_ListOfInterference& LI, const TopOpeBRepDS_DataStructure& BDS, TopOpeBRepDS_MapOfShapeData& mosd)
{
  mosd.Clear();
  TopOpeBRepDS_Kind GT1,ST1;Standard_Integer G1,S1;
  for (TopOpeBRepDS_ListIteratorOfListOfInterference it1(LI);it1.More();it1.Next()) {
    Handle(TopOpeBRepDS_Interference)& I1=it1.Value(); FDS_data(I1,GT1,G1,ST1,S1); 
    if ( GT1 != MDSke || ST1 != MDSkf ) continue;
    const TopoDS_Shape& SG1 = BDS.Shape(G1);
    TopOpeBRepDS_ShapeData thedata;
    if (!mosd.Contains(SG1)) mosd.Add(SG1, thedata);
    mosd.ChangeFromKey(SG1).ChangeInterferences().Append(I1);
  }
} 

//------------------------------------------------------
TopAbs_State FUN_stateedgeface(const TopoDS_Shape& E, const TopoDS_Shape& F, gp_Pnt& P)
{
  TopAbs_State state = TopAbs_UNKNOWN;
  Standard_Real par; FUN_tool_findPinE(E,P,par);
  Standard_Real u,v; Standard_Boolean Pok = FUN_Parameters(P,F,u,v);
  if (Pok) { // classifier u,v dans F
    TopOpeBRepTool_ShapeClassifier& PSC = FSC_GetPSC(F);
    gp_Pnt2d Puv(u,v);
    PSC.StateP2DReference(Puv);
    state = PSC.State();
  }
  return state;
}

#define  M_IN(ssstate) ((ssstate) == TopAbs_IN)
#define  M_ON(ssstate) ((ssstate) == TopAbs_ON)
#define M_OUT(ssstate) ((ssstate) == TopAbs_OUT)
#define M_UNK(ssstate) ((ssstate) == TopAbs_UNK)

//------------------------------------------------------
void FUN_reduceEDGEgeometry
(TopOpeBRepDS_ListOfInterference& LI,const TopOpeBRepDS_DataStructure& BDS,const Standard_Integer iFI,
const TopOpeBRepDS_DataMapOfShapeListOfShapeOn1State& MEsp)
{
  if (!LI.Extent()) return;
  
  TopOpeBRepDS_MapOfShapeData mosd; 
  FUN_GmapS(LI,BDS,mosd);

#ifdef DEB
  Standard_Boolean TRC = FTRCF(iFI); 
  if (TRC) FUN_dumpmosd(mosd,BDS,iFI,"");
  if (TRC) debredfac(iFI);
#endif
  
  TopOpeBRepDS_ListOfInterference LIout;
  //modified by NIZNHY-PKV Thu Mar 16 09:44:24 2000 f
  Standard_Integer i, aN;
  aN=mosd.Extent();
  //for(Standard_Integer i=1,n=mosd.Extent(); i<=n; i++) {
  //modified by NIZNHY-PKV Thu Mar 16 09:44:27 2000 t
  for(i=1 ; i<=aN; i++) {
    const TopoDS_Shape& EG = mosd.FindKey(i); 
    Standard_Integer iEG = BDS.Shape(EG);

    // donnees samedomain attachees a l'arete iEG
    const TopTools_ListOfShape& esdeg = BDS.ShapeSameDomain(iEG);
    Standard_Boolean egissect = BDS.IsSectionEdge(TopoDS::Edge(EG));
    Standard_Boolean eghasesd = (! esdeg.IsEmpty());

#ifdef DEB
//    Standard_Integer egiref = BDS.SameDomainRef(iEG);
//    Standard_Integer egisref = (iEG == egiref);
//    TopOpeBRepDS_Config egc = BDS.SameDomainOri(iEG);
#endif

    TopOpeBRepDS_ListOfInterference& LIEG = mosd.ChangeFromKey(EG).ChangeInterferences();
    Standard_Integer nExt = LIEG.Extent();
    // LIEG = toutes les interferences dont le Support() est une 
    // face possedant une interference dont la Geometry() est EG.
    
#ifdef DEB
    if (TRC) FUN_dumploiS(EG,LIEG,BDS,"   ");
#endif
    
    if      (nExt == 0) {
      continue;
    }
    if      (nExt == 1) {
      LIout.Append(LIEG);
    }
    
    else if (nExt >= 2) {
      Standard_Boolean isEGsp = MEsp.IsBound(EG);
      //modified by NIZNHY-PKV Thu Mar 16 11:03:44 2000 from
      //Standard_Integer nEGsp = 0;
      //modified by NIZNHY-PKV Thu Mar 16 11:03:49 2000 to
      if (isEGsp) {
	const TopOpeBRepDS_ListOfShapeOn1State& los1 = MEsp.Find(EG);
	isEGsp = los1.IsSplit();
	//modified by NIZNHY-PKV Thu Mar 16 11:02:40 2000 from
	//if ( isEGsp ) {
	//  const TopTools_ListOfShape& los = los1.ListOnState();
	//  nEGsp = los.Extent();
	//}
	//modified by NIZNHY-PKV Thu Mar 16 11:02:46 2000 to
      }
      
      if ( isEGsp ) {
	const TopTools_ListOfShape& los = MEsp.Find(EG).ListOnState();
	TopTools_ListIteratorOfListOfShape itlos(los);
	for(;itlos.More();itlos.Next()) {
	  // EGsp est une arete splitee de EG.
	  const TopoDS_Shape& EGsp = itlos.Value();
	  
	  // LISFIN = liste des interferences de LI dont le Support()
	  // est une face contenant geometriquement l'arete EGsp
	  TopOpeBRepDS_ListOfInterference LISFIN;
	  TopOpeBRepDS_ListIteratorOfListOfInterference itLIEG(LIEG);
	  for(; itLIEG.More(); itLIEG.Next()) {
	    const Handle(TopOpeBRepDS_Interference)& ILIEG = itLIEG.Value();
	    Standard_Integer  iS = ILIEG->Support();
	    TopOpeBRepDS_Kind kS = ILIEG->SupportType();
	    if ( kS == MDSkf ) {
	      const TopoDS_Shape& SFILIEG = BDS.Shape(iS);
	      gp_Pnt P; 
	      TopAbs_State staef = FUN_stateedgeface(EGsp,SFILIEG,P);
	      
	      Standard_Boolean Pok = M_IN(staef);
	      if ( eghasesd || egissect ) {
		Pok = Pok || M_ON(staef);
	      }

	      if (Pok) {
		LISFIN.Append(ILIEG);
	      }
	    }
	  } // itLIEG.More

	  Standard_Integer nLISFIN = LISFIN.Extent();
	  if (nLISFIN >= 2 ) {
	    Standard_Boolean gb;
	    gb = Handle(TopOpeBRepDS_ShapeShapeInterference)::DownCast(LISFIN.First())->GBound();
	    
	    if (gb) {
	      //modified by NIZNHY-PKV Thu Mar 16 10:40:57 2000 f
	      // we have to rest at least one  Interference on the face.
	      // To kill all of them is too bravely. 
	      Handle(TopOpeBRepDS_Interference) anInterference = LISFIN.First();
	      LISFIN.Clear();
	      LISFIN.Append(anInterference);
	      //modified by NIZNHY-PKV Thu Mar 16 10:41:01 2000 t
	    }
	    else    
	      FUN_reduceEDGEgeometry1(LISFIN,BDS,iFI,iEG,EGsp,MEsp);
	  }

	  nLISFIN = LISFIN.Extent();
	  if (nLISFIN) 
	    LIout.Append(LISFIN);
	}
      } // isEGsp
      else {
	// iFI = face de reference (indice)
	// E = arete geometrie d'interference (shape), iEG (indice)
	// LIEG = liste d'interferences de geometrie EG
	//        et dont les Support() sont a transitionner complexe
	TopoDS_Shape Enull;
	FUN_reduceEDGEgeometry1(LIEG,BDS,iFI,iEG,Enull,MEsp);
	LIout.Append(LIEG);
      }
    }
  }

  LI.Clear();
  LI.Append(LIout);
} // FUN_reduceEDGEgeometry

//=======================================================================
//function : TopOpeBRepDS_FIR
//purpose  : 
//=======================================================================
TopOpeBRepDS_FIR::TopOpeBRepDS_FIR
(const Handle(TopOpeBRepDS_HDataStructure)& HDS) : myHDS(HDS)
{}

//=======================================================================
//function : ProcessFaceInterferences
//purpose  : 
//=======================================================================
void TopOpeBRepDS_FIR::ProcessFaceInterferences(const TopOpeBRepDS_DataMapOfShapeListOfShapeOn1State& M)
{
  TopOpeBRepDS_DataStructure& BDS = myHDS->ChangeDS();
  Standard_Integer i,nshape = BDS.NbShapes();
  for (i = 1; i <= nshape; i++) {
    const TopoDS_Shape& S = BDS.Shape(i);
    if(S.IsNull()) continue;
    if ( S.ShapeType() == TopAbs_FACE ) {
      ProcessFaceInterferences(i,M);
    }
  }
}

//=======================================================================
//function : ProcessFaceInterferences
//purpose  : 
//=======================================================================
void TopOpeBRepDS_FIR::ProcessFaceInterferences
(const Standard_Integer SIX,const TopOpeBRepDS_DataMapOfShapeListOfShapeOn1State& MEsp)
{
  TopOpeBRepDS_DataStructure& BDS = myHDS->ChangeDS();

#ifdef DEB
  Standard_Boolean TRC = FTRCF(SIX);
  if (TRC) debredfac(SIX);
#endif
  // F is the Face, LI is list of interferences to compact
#ifdef DEB
//  const TopoDS_Shape& F = BDS.Shape(SIX);
#endif
  TopOpeBRepDS_ListOfInterference& LI = BDS.ChangeShapeInterferences(SIX);
  TopOpeBRepDS_ListOfInterference lw, lE, lFE, lFEF, lF; lw.Assign(LI);

  Standard_Integer nF = ::FUN_selectTRASHAinterference(lw,TopAbs_FACE,lF);
  Standard_Integer nFE = ::FUN_selectGKinterference(lF,MDSke,lFE);
  Standard_Integer nFEF = ::FUN_selectSKinterference(lFE,MDSkf,lFEF);
  Standard_Integer nE = ::FUN_selectTRASHAinterference(lw,TopAbs_EDGE,lE);

  nF = lF.Extent();
  nFE = lFE.Extent();
  nFEF = lFEF.Extent();
  nE = lE.Extent();
#ifdef DEB
  if(TRC){
    if(nF||nFE||nFEF||nE){cout<<endl;cout<<"-----------------------"<<endl;}
    if(nF) {cout<<"FACE "<<SIX<<" (FACE) : "<<nF<<endl;FDS_dumpLI(lF,"  ");}
    if(nFE){cout<<"FACE "<<SIX<<" (FACE)(GK EDGE) : "<<nFE<<endl;FDS_dumpLI(lFE,"  ");}
    if(nFEF){cout<<"FACE "<<SIX<<" (FACE)(GK EDGE)(SK FACE) : "<<nFEF<<endl;FDS_dumpLI(lFEF,"  ");}
    if(nE) {cout<<"FACE "<<SIX<<" (EDGE) : "<<nE<<endl;FDS_dumpLI(lE,"  ");}
  }
#endif

  FUN_reduceEDGEgeometry(lFEF,BDS,SIX,MEsp);

  nF = lF.Extent();
  nFE = lFE.Extent();
  nFEF = lFEF.Extent();
  nE = lE.Extent();
#ifdef DEB
  if(TRC){
    if(nF||nFE||nFEF||nE)cout<<endl;
    if(nF) {cout<<"FACE "<<SIX<<" (FACE) : "<<nF<<endl;FDS_dumpLI(lF,"  ");}
    if(nFE){cout<<"FACE "<<SIX<<" (FACE)(GK EDGE) : "<<nFE<<endl;FDS_dumpLI(lFE,"  ");}
    if(nFEF){cout<<"FACE "<<SIX<<" (FACE)(GK EDGE)(SK FACE) : "<<nFEF<<endl;FDS_dumpLI(lFEF,"  ");}
    if(nE) {cout<<"FACE "<<SIX<<" (EDGE) : "<<nE<<endl;FDS_dumpLI(lE,"  ");}
    cout<<"-----------------------"<<endl;
  }
#endif

  LI.Clear();
  LI.Append(lF);
  LI.Append(lFE);
  LI.Append(lFEF);
  LI.Append(lE);
  // MSV: filter duplicates
  ::FUN_reducedoublons(LI,BDS,SIX);
}
