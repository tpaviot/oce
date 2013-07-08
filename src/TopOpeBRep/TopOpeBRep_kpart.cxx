// Created on: 1994-02-17
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
#include <Standard_DomainError.hxx>
#include <Geom_Curve.hxx>
#include <Geom2d_Curve.hxx>
#include <TopOpeBRep_FFTransitionTool.hxx>
#include <TopOpeBRep_PointGeomTool.hxx>
#include <TopOpeBRep.hxx>
#include <TopOpeBRepDS_InterferenceTool.hxx>
#include <TopOpeBRepDS_Config.hxx>
#include <TopOpeBRepDS_Curve.hxx>
#include <TopOpeBRepDS_PointIterator.hxx>
#include <TopOpeBRepTool_ShapeTool.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <Precision.hxx>
#include <TopoDS.hxx>

#include <TopOpeBRepDS_define.hxx>

#ifdef DEB
extern Standard_Boolean TopOpeBRepDS_GettraceDSF(); 
extern Standard_Boolean TopOpeBRep_GetcontextNEWKP();
#endif

// VP<STATIC_lastVPind> is the vp on which was computed the last CPI.
// if no CPI is computed yet, <STATIC_lastVPind> = 0.
static Standard_Integer STATIC_lastVPind;

#define M_FORWARD( st) (st == TopAbs_FORWARD)
#define M_REVERSED(st) (st == TopAbs_REVERSED)
#define M_INTERNAL(st) (st == TopAbs_INTERNAL)
#define M_EXTERNAL(st) (st == TopAbs_EXTERNAL)

//-----------------------------------------------------------------------
static void FUNBREP_Periodize
(const TopOpeBRep_LineInter& L,const Handle(TopOpeBRepDS_Interference)& Ifound,Standard_Real& PIfound,Standard_Real& parline)
//-----------------------------------------------------------------------
{
  const TopOpeBRepDS_Transition& TIfound = Ifound->Transition();
  TopAbs_Orientation OTIfound = TIfound.Orientation(TopAbs_IN);

  if (L.IsPeriodic()) {
    Standard_Real f,l; L.Bounds(f,l);
    Standard_Boolean onf = Abs(parline-f) < Precision::PConfusion();
    Standard_Boolean onl = Abs(parline-l) < Precision::PConfusion();
    Standard_Boolean onfl = onf || onl;
    if ( onfl ) {
      if      ( OTIfound == TopAbs_FORWARD ) {
	PIfound = f; 
	parline = l;
      }
      else if ( OTIfound == TopAbs_REVERSED ) {
	PIfound = l;
	parline = f;
      }
      else {
	Standard_ProgramError::Raise("FUNBREP_Periodize");
      }
    } // onfl
    else {
      parline = PIfound = Min(parline,PIfound);
    }
  } // IsPeriodic
  else {
    parline = PIfound = Min(parline,PIfound);
  }
}

//-----------------------------------------------------------------------
static Standard_Boolean FUNBREP_HasSameGPoint(const TopOpeBRepDS_Point& DSP,const Handle(TopOpeBRepDS_Interference)& I,
				 const TopOpeBRepDS_DataStructure& BDS) 
//-----------------------------------------------------------------------
{      
  // returns <true> if <DSP> shares same geometric point with 
  // <I> geometry.
  Standard_Integer G = I->Geometry();	
  Standard_Boolean samegp = Standard_False;
  if      ( I->GeometryType() == TopOpeBRepDS_POINT ) {
    const TopOpeBRepDS_Point& P = BDS.Point(G); 
    samegp = DSP.IsEqual(P);
  }
  else if ( I->GeometryType() == TopOpeBRepDS_VERTEX ) {
    TopOpeBRepDS_Point P(BDS.Shape(G));
    samegp = DSP.IsEqual(P);
  }
  return samegp;
}

//-----------------------------------------------------------------------
static Standard_Boolean FUNBREP_SameUV(const TopOpeBRep_VPointInter& VP1,
			  const TopOpeBRep_VPointInter& VP2,
			  const Standard_Integer sind,const Standard_Real toluv)
//-----------------------------------------------------------------------
{
  Standard_Real u1 = 0.0,v1 = 0.0,u2 = 0.0,v2 = 0.0;
  if (sind == 1) {
    VP1.ParametersOnS1(u1,v1); VP2.ParametersOnS1(u2,v2);
  }
  if (sind == 2) {
    VP1.ParametersOnS2(u1,v1); VP2.ParametersOnS2(u2,v2);
  }
  gp_Pnt2d p1(u1,v1), p2(u2,v2);
  Standard_Real dist = p1.Distance(p2);
  Standard_Boolean sameuv = (dist < toluv);
  return sameuv;
}

#ifdef DEB
//-------------------------------------------------------------------
void FUNBREP_topokpartDEB 
(const Handle(TopOpeBRepDS_Interference)& Ifound,const TopOpeBRepDS_ListOfInterference& DSCIL,const TopOpeBRep_LineInter& L,
 const TopOpeBRep_VPointInter& VP,const TopOpeBRepDS_Transition& lasttransLine,
 const TopOpeBRepDS_DataStructure& BDS,const TopoDS_Shape& E,const TopoDS_Shape& F,const Standard_Real toluv,
 const Standard_Boolean CPIfound,const Standard_Boolean samepar, const Standard_Boolean couture,
 const Standard_Real& parline,const TopOpeBRepDS_Transition& transLine)
//-------------------------------------------------------------------
{
  Standard_Integer iVP = VP.Index();
  Standard_Boolean fermee  = L.IsVClosed();
  Standard_Boolean onsort = (transLine.Orientation(TopAbs_OUT) == TopAbs_FORWARD);
  Standard_Boolean lastdefinie = ! lasttransLine.IsUnknown();
  Standard_Boolean lastonsort = Standard_False;
  if (lastdefinie) lastonsort = (lasttransLine.Orientation(TopAbs_OUT) == TopAbs_FORWARD);

  Standard_Boolean LITdefinie = Standard_False;
  Standard_Boolean LITonsort = Standard_False;
  TopOpeBRepDS_Transition LIT;
  Standard_Boolean nointerf = DSCIL.IsEmpty();

  if (nointerf) STATIC_lastVPind = 0;
  if (!nointerf) {
    const Handle(TopOpeBRepDS_Interference)& I = DSCIL.Last();
    LIT = I->Transition();
    LITdefinie = ! LIT.IsUnknown();
    if (LITdefinie) LITonsort = (LIT.Orientation(TopAbs_OUT) == TopAbs_FORWARD);
  }
  
  Standard_Boolean iswalki = (L.TypeLineCurve() == TopOpeBRep_WALKING);
  if   (iswalki) cout<<"kpwalk ";
  else           cout<<"kpglin ";

  cout<<"\tVP "<<iVP<<" : ";                     
  
  if      (CPIfound && samepar)  cout<<"trouve ("<<parline<<")";
  else if (CPIfound && !samepar) cout<<"trouve";
  else    	                 cout<<"non trouve";
  
  if (fermee) cout<<", fermee"; 
  else        cout<<", ouverte";
  
  if (couture) cout<<", couture";
  
  if (onsort) cout<<", sortant"; 
  else        cout<<", entrant";
  
  if      (lastdefinie &&  lastonsort) cout<<", prec = sortant";
  else if (lastdefinie && !lastonsort) cout<<", prec = entrant";
  else                                 cout<<", prec = ?";
  
  if      (LITdefinie &&  LITonsort) cout<<", Lprec = sortant";
  else if (LITdefinie && !LITonsort) cout<<", Lprec = entrant";
  else                               cout<<", Lprec = ?";
  cout<<endl;

  if (!iswalki) {
    cout<<"kpglin ";
    Standard_Boolean hasfp = L.HasFirstPoint();
    Standard_Boolean haslp = L.HasLastPoint();
    Standard_Real f,l; L.Bounds(f,l);
    if (hasfp) cout<<"\thas fp "<<f; 
    else       cout<<"\thas NO fp";
    if (haslp) cout<<", has lp "<<l;
    else       cout<<", has NO lp";
    cout<<endl;
  }  
}
#endif

//----------------------------------------------------------------------
Standard_Boolean FUNBREP_topowalki_new
(const Handle(TopOpeBRepDS_Interference)& Ifound,const TopOpeBRepDS_ListOfInterference& DSCIL,const TopOpeBRep_LineInter& L,
 const TopOpeBRep_VPointInter& VP,const TopoDS_Shape& E,const Standard_Boolean samepar,const Standard_Boolean couture,
 TopOpeBRepDS_Transition& transLine)
//----------------------------------------------------------------------
{
#ifdef DEB
  Standard_Boolean trc = TopOpeBRepDS_GettraceDSF();
#endif
  
  if (L.TypeLineCurve() != TopOpeBRep_WALKING) {
    Standard_ProgramError::Raise("FUNBREP_topowalki_new : line is not a walking");
    return Standard_False;
  }

  Standard_Boolean CPIfound = !Ifound.IsNull();
  Standard_Integer iVP = VP.Index();
  Standard_Integer iINON1,iINONn,nINON; L.VPBounds(iINON1,iINONn,nINON);
  Standard_Boolean onsort = (transLine.Orientation(TopAbs_OUT) == TopAbs_FORWARD);

  Standard_Boolean LITdefinie = DSCIL.IsEmpty()? Standard_False: !DSCIL.Last()->Transition().IsUnknown();

  // dealing with INTERNAL/EXTERNAL <E> :
  // ------------------------------------
  TopAbs_Orientation Eori = E.Orientation();
  Standard_Boolean EFR = M_FORWARD(Eori) || M_REVERSED(Eori);
  if (!EFR) { // E INTERNAL ou EXTERNAL    
    // we assume transition for first vp on non oriented edge to be FORWARD 
    //                          last vp on non oriented edge to be REVERSED
    if (iVP == iINON1) transLine = TopOpeBRepDS_Transition(TopAbs_OUT,TopAbs_IN);
    if (iVP == iINONn) transLine = TopOpeBRepDS_Transition(TopAbs_IN,TopAbs_OUT);      
  }  

  // no last defined transition :
  // ----------------------------
  if  (!LITdefinie) {
    if (onsort)        return Standard_False;
    if (iVP == iINONn) return Standard_False;
  }    

  // has last defined transition :
  // -----------------------------
  Standard_Boolean keep = Standard_True;
  if  (LITdefinie) {

    Handle(TopOpeBRepDS_Interference) I = DSCIL.Last();
    TopOpeBRepDS_Transition LIT = I->Transition();
    Standard_Boolean LITonsort = M_FORWARD( LIT.Orientation(TopAbs_OUT) );
    Standard_Boolean LprecIsEntrant = !LITonsort;
    Standard_Boolean entrantsortant = LprecIsEntrant && onsort;
    
    if(EFR && !entrantsortant) keep = Standard_False;

    if (couture) {    
    // vp describing the same geometric point on closing edge :
    // it is the same vp described on the FORWARD and REVERSED closing edge -> we keep it only once
    // INFO : on walking, vp line parameter is the vp index on the walking 
    // samepar => describes same CPI 
      Standard_Boolean samevponcouture = samepar && keep;    
      if (samevponcouture) {
	keep = Standard_False;      
#ifdef DEB
	if (trc) cout<<"is same vp on couture";
#endif
      }
    }

    { // kpart JYL 971204 for closing walking, first and current VP same parameter,
      //                  lastonentre && onsort, 
      //                  first VP is first walking point (PIfound == 1.0),
      //                  current VP is the second one on walking and not the last.
      const Handle(TopOpeBRepDS_Interference)& I = DSCIL.First();     
      const TopOpeBRepDS_Transition& lasttransLine = I->Transition();
      // xpu12-12-97 : line is built on only 2 vp,
      //  DSCIL->First() == DSCIL->Last()          
      //  lasttransLine = DSCIL's first transition
      Standard_Real PIfound = TopOpeBRepDS_InterferenceTool::Parameter(Ifound); 
      Standard_Boolean fermee  = L.IsVClosed();
      Standard_Boolean lastonsort = LITdefinie && M_FORWARD(lasttransLine.Orientation(TopAbs_OUT));

      Standard_Boolean kpartclosingwalki = (LITdefinie && !lastonsort);
      kpartclosingwalki = kpartclosingwalki && CPIfound && samepar;
      kpartclosingwalki = kpartclosingwalki && onsort;
      kpartclosingwalki = kpartclosingwalki && fermee;
      kpartclosingwalki = kpartclosingwalki && (PIfound == 1.0);
      kpartclosingwalki = kpartclosingwalki && (iVP == iINON1+1) && (iVP != iINONn);
      if (kpartclosingwalki) {
	keep = Standard_False;
      }
    }
  } // LITdefinie

  return keep;
} // FUNBREP_topowalki_new 

#ifdef DEB
extern Standard_Boolean GLOBAL_bvpr;
Standard_EXPORT void debvpr2(void) {}
#endif

//----------------------------------------------------------------------
Standard_Boolean FUNBREP_topowalki
(const Handle(TopOpeBRepDS_Interference)& Ifound,const TopOpeBRepDS_ListOfInterference& DSCIL,const TopOpeBRep_LineInter& L,
 const TopOpeBRep_VPointInter& VP,const TopOpeBRepDS_Transition& lasttransLine,
// const TopOpeBRepDS_DataStructure& BDS,
 const TopOpeBRepDS_DataStructure& ,
 const TopoDS_Shape& E,
// const TopoDS_Shape& F,
 const TopoDS_Shape& ,
// const Standard_Real toluv,
 const Standard_Real ,
 const Standard_Boolean CPIfound,const Standard_Boolean samepar, const Standard_Boolean couture,
// Standard_Real& parline,
 Standard_Real& ,
 TopOpeBRepDS_Transition& transLine)
//----------------------------------------------------------------------
{
#ifdef DEB
  Standard_Boolean trc = TopOpeBRepDS_GettraceDSF();
#endif
  
  if (L.TypeLineCurve() != TopOpeBRep_WALKING) {
    Standard_ProgramError::Raise("FUNBREP_topowalki : line is not a walking");
    return Standard_False;
  }

#ifdef DEB
  Standard_Boolean newkp = TopOpeBRep_GetcontextNEWKP();
  if (newkp) {
    Standard_Boolean keep = FUNBREP_topowalki_new(Ifound,DSCIL,L,VP,E,samepar,couture,transLine);
    return keep;
  }
#endif

  TopAbs_Orientation Eori = E.Orientation();
  Standard_Integer iVP = VP.Index();
  Standard_Integer iINON1,iINONn,nINON; L.VPBounds(iINON1,iINONn,nINON);
  Standard_Boolean fermee  = L.IsVClosed();
  Standard_Boolean onsort = (transLine.Orientation(TopAbs_OUT) == TopAbs_FORWARD);
  Standard_Boolean lastdefinie = ! lasttransLine.IsUnknown();
  Standard_Boolean lastonsort = Standard_False;
  Standard_Boolean lastinin = Standard_False;

  if (lastdefinie) {
    lastonsort = (lasttransLine.Orientation(TopAbs_OUT) == TopAbs_FORWARD);
    lastinin = (lasttransLine.Before() == TopAbs_IN);
    lastinin = lastinin && (lasttransLine.After() == TopAbs_IN);
  }
  
  Standard_Boolean LITdefinie = Standard_False;
  Standard_Boolean LITonsort = Standard_False;
  TopOpeBRepDS_Transition LIT;
  Handle(TopOpeBRepDS_Interference) I;
  Standard_Boolean nointerf = DSCIL.IsEmpty();
  if (!nointerf) {
    I = DSCIL.Last();
    LIT = I->Transition();
    LITdefinie = ! LIT.IsUnknown();
    if (LITdefinie) LITonsort = (LIT.Orientation(TopAbs_OUT) == TopAbs_FORWARD);
  }

  Standard_Boolean keep = Standard_True;
  Standard_Boolean EFR = (Eori == TopAbs_FORWARD || Eori == TopAbs_REVERSED);
  
  if  (!LITdefinie) {
    if (onsort) {
      Standard_Boolean condCTS19305 = Standard_False;
      // start debug 971216 : CTS19305
      condCTS19305 = (!CPIfound);
      condCTS19305 = condCTS19305 && (!fermee);
      condCTS19305 = condCTS19305 && (!lastdefinie);
      condCTS19305 = condCTS19305 && (iVP == 1) && (iVP == iINON1); 
      if ( condCTS19305 ) {
	keep = Standard_True;
	transLine = TopOpeBRepDS_Transition(TopAbs_OUT,TopAbs_IN);
      }
      // end debug 971216 : 
      else keep = Standard_False;
    }
    if (iVP == iINONn) keep = Standard_False;
    if (!EFR) { // E INTERNAL ou EXTERNAL
      if (iVP == iINON1) {
	transLine = TopOpeBRepDS_Transition(TopAbs_OUT,TopAbs_IN);
      }
    }
  }    

  if  (keep && LITdefinie) {
    Standard_Boolean LprecIsEntrant = (LITdefinie && !LITonsort);
    Standard_Boolean entrantsortant = LprecIsEntrant && onsort;
    if (!EFR) {
      if ( iVP == iINONn) {
	transLine = TopOpeBRepDS_Transition(TopAbs_IN,TopAbs_OUT);
      }
    }
    else {
      Standard_Boolean condCTS19305 = Standard_False;
      condCTS19305 = (!CPIfound);
      condCTS19305 = condCTS19305 && (!fermee);
      condCTS19305 = condCTS19305 && (lastdefinie && !lastonsort);
      condCTS19305 = condCTS19305 && (LITdefinie && !LITonsort);
      condCTS19305 = condCTS19305 && (iVP == iINONn);

      if      ( condCTS19305 ) {
	keep = Standard_True;
	transLine = TopOpeBRepDS_Transition(TopAbs_IN,TopAbs_OUT);
      }
      else {
	if ( !entrantsortant ) {
	  keep = Standard_False;
	}
      }
    }

    // vp describing the same geometric point on closing edge :
    // it is the same vp described on the FORWARD and REVERSED closing edge -> we keep it only once
    // INFO : on walking, vp line parameter is the vp index on the walking 
    // samepar => describes same CPI 
    
    Standard_Boolean samevponcouture = samepar && couture;    
    if (keep && samevponcouture) {
      keep = Standard_False;
  
#ifdef DEB
      if (trc) cout<<"is same vp on couture";
#endif
    }

    if (keep) {
#ifdef DEB
      if (GLOBAL_bvpr) debvpr2(); 
#endif

      if (CPIfound && samepar) {
	Standard_Real PIfound = TopOpeBRepDS_InterferenceTool::Parameter(Ifound);

	// 971204
	Standard_Boolean cond1 = Standard_True;
	cond1 = cond1 && (lastdefinie && !lastonsort);
	cond1 = cond1 && onsort;
	cond1 = cond1 && fermee;
	cond1 = cond1 && (CPIfound && samepar);
	cond1 = cond1 && (PIfound == 1.0);
	cond1 = cond1 && (iVP==iINON1+1) && (iVP != iINONn);
	if ( cond1 ) {
	  keep = Standard_False;
	  return keep;
	}

	// PRO12107
	Standard_Boolean cond2 = Standard_True;	
	cond2 = cond2 && (lastdefinie && !lastonsort);
	cond1 = cond1 && onsort;
	cond2 = cond2 && (!fermee);
	cond2 = cond2 && (CPIfound && samepar);
	cond2 = cond2 && (PIfound == 1.0);
	cond2 = cond2 && (iVP==iINON1+1) && (iVP != iINONn);
	if ( cond2 ) {
	  keep = Standard_False;
	  return keep;
	}	
      }
    } // keep
    
  } // keep && LITdefinie
 
  if (keep) STATIC_lastVPind = iVP;
  return keep;
} // FUNBREP_topowalki

//----------------------------------------------------------------------
Standard_Boolean FUNBREP_topogline_new
(const TopOpeBRepDS_ListOfInterference& DSCIL,const TopOpeBRep_LineInter& L, const TopOpeBRep_VPointInter& VP,
 const TopOpeBRepDS_DataStructure& BDS,const Standard_Real toluv,
 const Standard_Boolean samepar, const Standard_Boolean couture,
 Standard_Real& parline,TopOpeBRepDS_Transition& transLine)
//----------------------------------------------------------------------
{
  if (L.TypeLineCurve() == TopOpeBRep_WALKING) {
    Standard_ProgramError::Raise("FUNBREP_topogline_new : line is not a GLine");
    return Standard_False;
  }

  Standard_Integer iVP = VP.Index();
  Standard_Integer iINON1,iINONn,nINON; L.VPBounds(iINON1,iINONn,nINON);

  // if VP<iVP> is on 3 
  //            and VP on 1 has transition OUT/IN, 
  //                VP on 2 has transition IN/OUT,
  // same VP will be kept.

  // the line is described with (VPmin,VPmax) boundaries.
  // if VP == VPmax, as we are only regarding IN/OUT transitions->ok
  // if VP == VPmin :
  Standard_Boolean dscilempty = DSCIL.IsEmpty();
  Standard_Boolean notkept = !dscilempty && (iVP == 1);
  if (notkept) return Standard_False;

  // <transLine> : for unknown current transition
  // ------------
  // (see TopOpeBRep_FacesFiller::ProcessVPonR)
  // vpmin with transition UNKNOWN               => transLine-> OUT/IN
  // vpmin OUT/IN, vpmax with transition UNKNOWN => transLine-> IN/OUT 
  TopOpeBRepDS_Transition LIT;
  Handle(TopOpeBRepDS_Interference) I;
  Standard_Boolean LITdefinie,LITonsort; LITdefinie = LITonsort = Standard_False;
  if ( !dscilempty ) {
    I = DSCIL.Last();
    LIT = I->Transition();
    LITdefinie = ! LIT.IsUnknown();
    if (LITdefinie) LITonsort = M_FORWARD( LIT.Orientation(TopAbs_OUT) );
  }
  Standard_Boolean trliunk = transLine.IsUnknown();
  Standard_Boolean isfirstvp = (iVP == iINON1);
  Standard_Boolean islastvp = (iVP == iINONn);
  if (trliunk) {
    if (isfirstvp)                             transLine = TopOpeBRepDS_Transition(TopAbs_OUT,TopAbs_IN);
    if (islastvp && LITdefinie &&  !LITonsort) transLine = LIT.Complement();
  }

  
  Standard_Boolean onsort = M_FORWARD( transLine.Orientation(TopAbs_OUT) );
  Standard_Boolean hasfp = L.HasFirstPoint(), haslp = L.HasLastPoint();
  Standard_Boolean hasfol = hasfp || haslp;
  Standard_Boolean keep = Standard_True;
  
  // no last defined transition :
  // ----------------------------
  if  (!LITdefinie) {
    if (onsort) keep = Standard_False;
    if (iVP == iINONn) keep = Standard_False;
  }

  // has last defined transition :
  // -----------------------------
  if  (LITdefinie) {
    Standard_Boolean LprecIsEntrant = (LITdefinie && !LITonsort);
    Standard_Boolean entrantsortant = LprecIsEntrant && onsort;
    if(!entrantsortant) keep = Standard_False;
    
    Standard_Boolean sameparoncouture = samepar && couture;
    if (sameparoncouture && hasfol && keep) { 

      // INFO : on geometric line, vp parameter on line is the point on 
      //        curve's parameter.	  
      TopOpeBRepDS_Point pntVP = TopOpeBRep_PointGeomTool::MakePoint(VP); 
      Standard_Boolean samegp = FUNBREP_HasSameGPoint(pntVP,I,BDS);     
      
      // !fermee : same p3d && samepar        => same CPI
      // fermee  : (same p3d && samepar
      //           && sameUVon1 && sameUVon2) => same CPI      
      Standard_Boolean fermee  = L.IsVClosed(); 
      if (!fermee && samegp) keep = Standard_False;
      if (fermee  && samegp) {
	// 2 vp describing a closing line describe the same 3dpoint
	// have same parameter, but do not describe the same uv 
	// points on the closed surface (cobo121)
	const TopOpeBRep_VPointInter& lastVP = L.VPoint(STATIC_lastVPind);	
	Standard_Boolean sameUVon1 = FUNBREP_SameUV(VP,lastVP,1,toluv);
	Standard_Boolean sameUVon2 = FUNBREP_SameUV(VP,lastVP,2,toluv);
	keep = !(sameUVon1 && sameUVon2);
      }	 
    }
    if (sameparoncouture && !hasfol) {

      // we have to parametrize the found interference (parameter PIfound)
      // and next interference (parline)
      Handle(TopOpeBRepDS_Interference) Ifound = DSCIL.First();
      Standard_Real PIfound = TopOpeBRepDS_InterferenceTool::Parameter(Ifound);
      FUNBREP_Periodize(L,Ifound,PIfound,parline);
      TopOpeBRepDS_InterferenceTool::Parameter(Ifound,PIfound);      
      transLine = LIT.Complement();

    }
  } // LITdefinie
    
  if (keep) STATIC_lastVPind = iVP;  
  return keep;
  
} // FUNBREP_topogline_new

//----------------------------------------------------------------------
Standard_Boolean FUNBREP_topogline
(const Handle(TopOpeBRepDS_Interference)& Ifound,const TopOpeBRepDS_ListOfInterference& DSCIL,const TopOpeBRep_LineInter& L,
 const TopOpeBRep_VPointInter& VP,const TopOpeBRepDS_Transition& lasttransLine,
 const TopOpeBRepDS_DataStructure& BDS,const TopoDS_Shape& E,
// const TopoDS_Shape& F,
 const TopoDS_Shape& ,
 const Standard_Real toluv,
// const Standard_Boolean CPIfound,
 const Standard_Boolean ,
 const Standard_Boolean samepar,const Standard_Boolean couture,
 Standard_Real& parline,TopOpeBRepDS_Transition& transLine)
//----------------------------------------------------------------------
{
  if (L.TypeLineCurve() == TopOpeBRep_WALKING) {
    Standard_ProgramError::Raise("FUNBREP_topogline : line is not a GLine");
    return Standard_False;
  }
  
#ifdef DEB
  Standard_Boolean newkp = TopOpeBRep_GetcontextNEWKP();
  if (newkp) {
    Standard_Boolean keep = FUNBREP_topogline_new(DSCIL,L,VP,BDS,toluv,samepar,couture,parline,transLine);
    return keep;
  }
#endif

  TopAbs_Orientation Eori = E.Orientation();
  Standard_Boolean EFR = M_FORWARD(Eori) || M_REVERSED(Eori);
  Standard_Integer iVP = VP.Index();
  Standard_Integer iINON1,iINONn,nINON; L.VPBounds(iINON1,iINONn,nINON);
  Standard_Boolean fermee  = L.IsVClosed();

  if (!EFR) { // E INTERNAL ou EXTERNAL    
    if (iVP == iINON1) transLine = TopOpeBRepDS_Transition(TopAbs_OUT,TopAbs_IN);
    if (iVP == iINONn) transLine = TopOpeBRepDS_Transition(TopAbs_IN,TopAbs_OUT);    
  }
  Standard_Boolean onsort = (transLine.Orientation(TopAbs_OUT) == TopAbs_FORWARD);

  Standard_Boolean LITdefinie = Standard_False;
  Standard_Boolean LITonsort = Standard_False;
  TopOpeBRepDS_Transition LIT;
  Handle(TopOpeBRepDS_Interference) I;
  Standard_Boolean dscilempty = DSCIL.IsEmpty();

  // xpu : 28-05-97 : if VP<iVP> is on 3 and 
  // VP on 1 has transition OUT/IN, VP on 2 has transition IN/OUT,
  // same VP will be kept.
  // the line is described with (VPmin,VPmax) boundaries.
  // if VP is VPmax, as we are only regarding IN/OUT transitions->ok
  // if VP is VPmin :
  Standard_Boolean newvvv = Standard_True;// xpu : 28-05-97
  if (newvvv) {
    Standard_Boolean notkept = !dscilempty && (iVP == 1);
    if (notkept) return Standard_False;
  }// 28-05-97 : xpu

  if ( !dscilempty ) {
    I = DSCIL.Last();
    LIT = I->Transition();
    LITdefinie = ! LIT.IsUnknown();
    if (LITdefinie) LITonsort = (LIT.Orientation(TopAbs_OUT) == TopAbs_FORWARD);
  }

  // xpu : 21-05-97 (see TopOpeBRep_FacesFiller::ProcessVPonR)
  // vpmin with transition UNKNOWN =>transLine-> OUT/IN
  // vpmin OUT/IN, vpmax with transition UNKNOWN =>transLine-> IN/OUT
  Standard_Boolean trliunk = transLine.IsUnknown();
  Standard_Boolean newvv = Standard_True;// xpu : 21-05-97
  Standard_Boolean isfirstvp = (iVP == iINON1);
  Standard_Boolean islastvp = (iVP == iINONn);
  if (newvv && trliunk) {
    if (isfirstvp) {
      transLine = TopOpeBRepDS_Transition(TopAbs_OUT,TopAbs_IN);
      onsort = Standard_False;
    }
    if (islastvp)
      if (LITdefinie &&  !LITonsort) {
	transLine = LIT.Complement();
	onsort = Standard_True;
      }
  }//21-05-97 :xpu

  Standard_Boolean hasfp = L.HasFirstPoint();
  Standard_Boolean haslp = L.HasLastPoint();
  Standard_Boolean hasfol = hasfp || haslp;

  Standard_Boolean keep = Standard_True;

  if  (!LITdefinie) {
    if (onsort) keep = Standard_False;
    if (iVP == iINONn) keep = Standard_False;
  }
  if  (LITdefinie) {
    Standard_Boolean LprecIsEntrant = (LITdefinie && !LITonsort);
    Standard_Boolean entrantsortant = LprecIsEntrant && onsort;
    if(!entrantsortant) keep = Standard_False;
    
    Standard_Boolean sameparoncouture = samepar && couture;
    if (sameparoncouture && hasfol) { 
      if (keep) {	  
	// INFO : on geometric line, vp parameter on line is the point on 
	//        curve parameter.	  
	TopOpeBRepDS_Point pntVP = TopOpeBRep_PointGeomTool::MakePoint(VP); 
	Standard_Boolean samegp = FUNBREP_HasSameGPoint(pntVP,I,BDS);
	const TopOpeBRep_VPointInter& lastVP = L.VPoint(STATIC_lastVPind);
	// if the line is not closed, same p3d and samepar represent
	// same CPI.else :
	if (fermee) {
	  // 2 vp describing a closing line describe the same 3dpoint
	  // have same parameter, but do not describe the same uv 
	  // points on the closed surface (cobo121)
	  Standard_Boolean sameUVon1 = FUNBREP_SameUV(VP,lastVP,1,toluv);
	  Standard_Boolean sameUVon2 = FUNBREP_SameUV(VP,lastVP,2,toluv);
	  samegp = samegp && sameUVon1 && sameUVon2;
	}	  
	if (samegp) keep = Standard_False; 
      }
    }
    if (sameparoncouture && !hasfol) {
      // parametrize Ifound (parameter PIfound) and next interference (parline)
      Standard_Real PIfound = TopOpeBRepDS_InterferenceTool::Parameter(Ifound);
      FUNBREP_Periodize(L,Ifound,PIfound,parline);
      TopOpeBRepDS_InterferenceTool::Parameter(Ifound,PIfound);      
      if (LITdefinie) transLine = LIT.Complement();
    }
  }

  if (keep) STATIC_lastVPind = iVP;  
  return keep;
  
} // end of FUNBREP_topogline

//-----------------------------------------------------------------------
static Standard_Boolean TopoParameter(const TopOpeBRep_LineInter& L,const Handle(TopOpeBRepDS_Interference)& I,
			 const Standard_Real parline,const Standard_Boolean closingedge)
//-----------------------------------------------------------------------
{
  if ( I.IsNull() ) return Standard_False;
  Standard_Boolean samepar = Standard_False;
  Standard_Real pCPI = TopOpeBRepDS_InterferenceTool::Parameter(I);
  if (! closingedge ) 
    samepar = (Abs(parline-pCPI)<Precision::PConfusion());
  else {
    // trouve et couture et courbe periodique : 
    // on retourne vrai pour laisser a FUNBREP_topokpart
    // le soin de definir correctement les couples 
    // (parametre, transition) pour les points confondus sur couture.
    Standard_Boolean perio = L.IsPeriodic();
    if ( perio ) {
      samepar = Standard_True;
    }
    else {
      samepar = (Abs(parline-pCPI)<Precision::PConfusion());      
    }
  }  
  return samepar;
}

//----------------------------------------------------------------------
Standard_EXPORT Standard_Boolean FUNBREP_topokpart
(const Handle(TopOpeBRepDS_Interference)& Ifound,const TopOpeBRepDS_ListOfInterference& DSCIL,
 const TopOpeBRep_LineInter& L,const TopOpeBRep_VPointInter& VP,
 const TopOpeBRepDS_DataStructure& BDS,const TopoDS_Shape& E,const TopoDS_Shape& F,const Standard_Real toluv,
 Standard_Real& parline,TopOpeBRepDS_Transition& transLine)
//----------------------------------------------------------------------
{
  Standard_Boolean keep = Standard_True;

  Standard_Boolean CPIfound = !Ifound.IsNull();
  Standard_Boolean couture = TopOpeBRepTool_ShapeTool::Closed(TopoDS::Edge(E),TopoDS::Face(F));
  Standard_Boolean samepar = Standard_False; // = True if current VPoint falls on an existing geometry with an equal parameter.
  if (!CPIfound) samepar = Standard_False;
  else           samepar = CPIfound ? TopoParameter(L,Ifound,parline,couture) : Standard_False;

  TopOpeBRepDS_Transition lasttransLine; if (!DSCIL.IsEmpty()) lasttransLine = DSCIL.Last()->Transition(); // xpu12-12-97
#ifdef DEB
  if (TopOpeBRepDS_GettraceDSF()) {
    FUNBREP_topokpartDEB(Ifound,DSCIL,L,VP,lasttransLine,BDS,E,F,toluv,
			 CPIfound,samepar,couture,parline,transLine);
  }
#endif
  
  // A line is valid if at least it has VPi1 and VPi2 with i1 < i2 and :
  // transition on line for VPi1 : OUT/IN and for VPi2 : IN/OUT.
  // When <VPj> is on j=i1/i2, we keep it (returning true).
  // Rmq :VP internal to the face is given with transition on line
  // OUT/IN or IN/OUT if it is on the beginning or on the end 
  // of the line.
  
  if (L.TypeLineCurve() == TopOpeBRep_WALKING) {
    keep = FUNBREP_topowalki(Ifound,DSCIL,L,VP,lasttransLine,BDS,E,F,toluv,
			     CPIfound,samepar,couture,parline,transLine);
  }
  else {
    keep = FUNBREP_topogline(Ifound,DSCIL,L,VP,lasttransLine,BDS,E,F,toluv,
			     CPIfound,samepar,couture,parline,transLine);
  }
  return keep;  
} // end of FUNBREP_tpokpart

