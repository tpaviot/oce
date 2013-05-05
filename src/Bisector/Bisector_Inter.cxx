// Created on: 1994-06-24
// Created by: Yves FRICAUD
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


//  Modified by skv - Mon May  5 15:06:39 2003 OCC616

#include <Bisector_Inter.ixx>
#include <IntRes2d_Intersection.hxx>
#include <Bisector_Curve.hxx>
#include <Bisector_BisecAna.hxx>
#include <Bisector_BisecCC.hxx>
#include <Bisector_BisecPC.hxx>
#include <Bisector_FunctionInter.hxx>
#include <Geom2dInt_GInter.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2dAdaptor_Curve.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2d_Line.hxx>
#include <IntRes2d_Transition.hxx>
#include <IntRes2d_IntersectionPoint.hxx>
#include <Precision.hxx>
#include <math_BissecNewton.hxx>
#include <ElCLib.hxx>

#ifdef DRAW
#include <Draw_Appli.hxx>
#include <DrawTrSurf_Curve2d.hxx>
#include <Draw_Marker2D.hxx>

static Standard_Boolean Affich = Standard_False;
#endif

//===================================================================================
// function :
// putpose  :
//===================================================================================
Bisector_Inter::Bisector_Inter() 
{
}

//===================================================================================
// function :
// putpose  :
//===================================================================================
Bisector_Inter::Bisector_Inter(const Bisector_Bisec&  C1, 
			       const IntRes2d_Domain& D1, 
			       const Bisector_Bisec&  C2, 
			       const IntRes2d_Domain& D2, 
			       const Standard_Real    TolConf, 
			       const Standard_Real    Tol,
			       const Standard_Boolean ComunElement) 
{
  Perform (C1,D1,C2,D2,TolConf,Tol,ComunElement);
}

//===================================================================================
// function : ConstructSegment
// putpose  :
//===================================================================================
static Handle(Geom2d_Line) ConstructSegment(const gp_Pnt2d&     PMin,
					    const gp_Pnt2d&     PMax,
					    const Standard_Real UMin,
//					    const Standard_Real UMax)
					    const Standard_Real )
{
  gp_Dir2d Dir(PMax.X() - PMin.X(),PMax.Y() - PMin.Y());
  Handle(Geom2d_Line) L = new Geom2d_Line (gp_Pnt2d(PMin.X() - UMin*Dir.X(),
						    PMin.Y() - UMin*Dir.Y()),Dir);
  return L;
}

//===================================================================================
// function : Perform
// putpose  :
//===================================================================================
void Bisector_Inter::Perform(const Bisector_Bisec&  C1,
			     const IntRes2d_Domain& D1, 
			     const Bisector_Bisec&  C2,
			     const IntRes2d_Domain& D2,
			     const Standard_Real    TolConf,
			     const Standard_Real    Tol,
			     const Standard_Boolean ComunElement) 
{
  Handle(Bisector_Curve)    Bis1  = Handle(Bisector_Curve)::DownCast( C1.Value()->BasisCurve()); 
  Handle(Bisector_Curve)    Bis2  = Handle(Bisector_Curve)::DownCast( C2.Value()->BasisCurve());

  Handle(Geom2d_Curve)*  SBis1 = new Handle(Geom2d_Curve) [Bis1->NbIntervals()+1];
  Handle(Geom2d_Curve)*  SBis2 = new Handle(Geom2d_Curve) [Bis2->NbIntervals()+1];
  IntRes2d_Domain*       SD1   = new IntRes2d_Domain [Bis1->NbIntervals()+1];
  IntRes2d_Domain*       SD2   = new IntRes2d_Domain [Bis2->NbIntervals()+1];

  Standard_Integer NB1 = 0; Standard_Integer NB2 = 0;
  Standard_Real    MinDomain,MaxDomain;
  Standard_Real    UMin,UMax;
  gp_Pnt2d         PMin,PMax;

  //------------------------------------------------------
  // Return Min Max domain1.
  //------------------------------------------------------
  if (D1.HasFirstPoint()) {MinDomain = D1.FirstParameter();}
  else                    {MinDomain = RealFirst();        }

  if (D1.HasLastPoint())  {MaxDomain = D1.LastParameter();}
  else                    {MaxDomain = RealLast();        }

  //----------------------------------------------------------
  // Cutting the first curve by the intervals of
  // continuity taking account of D1
  //----------------------------------------------------------
//for (Standard_Integer IB1 = 1; IB1 <= Bis1->NbIntervals(); IB1++) {
  Standard_Integer IB1;
  for ( IB1 = 1; IB1 <= Bis1->NbIntervals(); IB1++) {
    UMin = Bis1->IntervalFirst(IB1);
    UMax = Bis1->IntervalLast (IB1);
    if (UMax > MinDomain && UMin < MaxDomain) {
      UMin = Max (UMin,MinDomain);
      UMax = Min (UMax,MaxDomain);
      PMin = Bis1->Value(UMin);
      PMax = Bis1->Value(UMax);
      SD1 [IB1].SetValues(PMin,UMin,D1.FirstTolerance(),
			  PMax,UMax,D1.LastTolerance());

      if ((IB1 == 1                   && Bis1->IsExtendAtStart()) || 
	  (IB1 == Bis1->NbIntervals() && Bis1->IsExtendAtEnd())    ){
	//--------------------------------------------------------
	// Part corresponding to an extension is a segment.	
	//--------------------------------------------------------
	SBis1 [IB1] = ConstructSegment (PMin,PMax,UMin,UMax);
      }
      else {
	SBis1 [IB1] = Bis1;
      }
      NB1++;
    }
  }

  //------------------------------------------------------
  // Return Min Max domain2.
  //------------------------------------------------------
  if (D2.HasFirstPoint()) {MinDomain = D2.FirstParameter();}
  else                    {MinDomain = RealFirst();        }

  if (D2.HasLastPoint())  {MaxDomain = D2.LastParameter();}
  else                    {MaxDomain = RealLast();        }

  //----------------------------------------------------------
  // Cut the second curve following the intervals of
  // continuity taking account of D2
  //----------------------------------------------------------
//for (Standard_Integer IB2 = 1; IB2 <= Bis2->NbIntervals(); IB2++) {
  Standard_Integer IB2;
  for ( IB2 = 1; IB2 <= Bis2->NbIntervals(); IB2++) {
    UMin = Bis2->IntervalFirst(IB2);
    UMax = Bis2->IntervalLast  (IB2);
    if (UMax > MinDomain && UMin < MaxDomain) {
      UMin = Max (UMin,MinDomain);
      UMax = Min (UMax,MaxDomain);
      PMin = Bis2->Value(UMin);
      PMax = Bis2->Value(UMax);
      SD2 [IB2].SetValues(PMin,UMin,D2.FirstTolerance(),
			  PMax,UMax,D2.LastTolerance());

      if ((IB2 == 1                   && Bis2->IsExtendAtStart()) || 
	  (IB2 == Bis1->NbIntervals() && Bis2->IsExtendAtEnd())    ){
	//--------------------------------------------------------
	// Part corresponding to an extension is a segment.	
	//--------------------------------------------------------
	SBis2 [IB2] = ConstructSegment (PMin,PMax,UMin,UMax);
      }
      else {
	SBis2 [IB2] = Bis2;
      }
      NB2++;
    }
  }

  //--------------------------------------------------------------
  // Loop on the intersections of parts of each curve.
  //--------------------------------------------------------------
  for ( IB1 = 1; IB1 <= NB1; IB1++) {
    for ( IB2 = 1; IB2 <= NB2; IB2++) {
      SinglePerform(SBis1[IB1],SD1[IB1],
		    SBis2[IB2],SD2[IB2],TolConf,Tol,ComunElement);
    }
  }
  delete [] SBis1;
  delete [] SBis2;
  delete [] SD1;
  delete [] SD2;
}

//===================================================================================
// function : SinglePerform
// putpose  :
//===================================================================================
void Bisector_Inter::SinglePerform(const Handle(Geom2d_Curve)&    CBis1,
				   const IntRes2d_Domain&         D1, 
				   const Handle(Geom2d_Curve)&    CBis2,
				   const IntRes2d_Domain&         D2,
				   const Standard_Real            TolConf,
				   const Standard_Real            Tol,
				   const Standard_Boolean         ComunElement) 
{
  Handle(Geom2d_Curve)   Bis1 = CBis1;
  Handle(Geom2d_Curve)   Bis2 = CBis2;

  Handle(Standard_Type)  Type1 = Bis1->DynamicType();
  Handle(Standard_Type)  Type2 = Bis2->DynamicType();

  if (Type1 == STANDARD_TYPE(Bisector_BisecAna) || Type2 ==  STANDARD_TYPE(Bisector_BisecAna)) {      
    Handle(Geom2d_Curve) C2Bis1,C2Bis2;
    if (Type1 == STANDARD_TYPE(Bisector_BisecAna)) {
      C2Bis1 = Handle(Bisector_BisecAna)::DownCast(Bis1)->Geom2dCurve();
    }
    else {
      C2Bis1 = Bis1;
    }
    if (Type2 == STANDARD_TYPE(Bisector_BisecAna)) {
      C2Bis2 = Handle(Bisector_BisecAna)::DownCast(Bis2)->Geom2dCurve();
    }   
    else {
      C2Bis2 = Bis2;
    }
    Type1 = C2Bis1->DynamicType();
    Type2 = C2Bis2->DynamicType();
    if (Type1 == STANDARD_TYPE(Geom2d_Line) && Type2 != STANDARD_TYPE(Geom2d_Line)) {
      TestBound(Handle(Geom2d_Line)::DownCast(C2Bis1),
		D1,C2Bis2,D2,TolConf,Standard_False);
    }
    else if (Type2 == STANDARD_TYPE(Geom2d_Line)&& Type1 != STANDARD_TYPE(Geom2d_Line)) {
      TestBound(Handle(Geom2d_Line)::DownCast(C2Bis2),
		D2,C2Bis1,D1,TolConf,Standard_True);
    }
    Geom2dInt_GInter Intersect;
    Geom2dAdaptor_Curve AC2Bis1(C2Bis1);
    Geom2dAdaptor_Curve AC2Bis2(C2Bis2);
    Intersect.Perform(AC2Bis1,D1,AC2Bis2,D2,TolConf,Tol);
    Append (Intersect,D1.FirstParameter(),D1.LastParameter(),
	              D2.FirstParameter(),D2.LastParameter());
  }
  else if (Type1 == STANDARD_TYPE(Bisector_BisecPC) || Type2 == STANDARD_TYPE(Bisector_BisecPC)) {
    Geom2dInt_GInter Intersect;
    Geom2dAdaptor_Curve ABis1(Bis1);
    Geom2dAdaptor_Curve ABis2(Bis2);
    Intersect.Perform(ABis1,D1,ABis2,D2,TolConf,Tol);
    Append (Intersect,D1.FirstParameter(),D1.LastParameter(),
	              D2.FirstParameter(),D2.LastParameter());
  }
  else if (ComunElement &&
	   Type1 == STANDARD_TYPE(Bisector_BisecCC) &&  Type2 == STANDARD_TYPE(Bisector_BisecCC)) {
    NeighbourPerform(Handle(Bisector_BisecCC)::DownCast(Bis1),D1,
		     Handle(Bisector_BisecCC)::DownCast(Bis2),D2,Tol);
  }
  else {
    // If we are here one of two bissectrices is a segment.
    // If one of bissectrices is not a segment, it is tested if 
    // its extremities are on the straight line.

    if (Type1 == STANDARD_TYPE(Geom2d_Line) && Type2 != STANDARD_TYPE(Geom2d_Line)) {
      TestBound(Handle(Geom2d_Line)::DownCast(Bis1),
		D1,Bis2,D2,TolConf,Standard_False);
    }
    else if (Type2 == STANDARD_TYPE(Geom2d_Line)&& Type1 != STANDARD_TYPE(Geom2d_Line)) {
      TestBound(Handle(Geom2d_Line)::DownCast(Bis2),
		D2,Bis1,D1,TolConf,Standard_True);
    }
    Geom2dInt_GInter Intersect;
    Geom2dAdaptor_Curve ABis1(Bis1);
    Geom2dAdaptor_Curve ABis2(Bis2);
    Intersect.Perform(ABis1,D1,ABis2,D2,TolConf,Tol);
    Append (Intersect,D1.FirstParameter(),D1.LastParameter(),
	              D2.FirstParameter(),D2.LastParameter());
  }

#ifdef DRAW
  if (Affich) {
    Handle(DrawTrSurf_Curve2d) dr;
    Draw_Color                 Couleur = Draw_bleu;
    
    dr = new DrawTrSurf_Curve2d(Bis1,Couleur,100);
    dout << dr;
    dr = new DrawTrSurf_Curve2d(Bis2,Couleur,100);
    dout << dr;
    if (IsDone() && !IsEmpty()) {
      for (Standard_Integer k = 1; k <= NbPoints(); k++) {
	gp_Pnt2d P =  Point(k).Value();
	Handle(Draw_Marker2D) drp  = new Draw_Marker2D(P,Draw_Plus,Draw_vert); 
	dout << drp;
      }
    }
    dout.Flush();
  }
#endif  
}

//===================================================================================
// function : NeighbourPerform
// putpose  : Find the intersection of 2 neighbor bissectrices curve/curve
//            (ie Bis1 separates A and B and Bis2 separates B and C).
//            Bis1 is parameterized by B and Bis2 by C.
//
//            Method : Bis2 is parameterized by B 
//            2 bissectrices are thus parameterized by the same curve.
//            Let D1(u) = d(Bis1(u),B(u)) and D2(U) = d(Bis2(u),B(U))
//            Parameter U0 for which D1(U0)-D2(U0) = 0 is found.
//===================================================================================
void Bisector_Inter::NeighbourPerform(const Handle(Bisector_BisecCC)&  Bis1,
				      const IntRes2d_Domain&           D1, 
				      const Handle(Bisector_BisecCC)&  Bis2,
				      const IntRes2d_Domain&           D2,
				      const Standard_Real              Tol)
{
  Standard_Real USol,U1,U2,Dist;
  Standard_Real UMin =0.,UMax =0.;  
  Standard_Real Eps = Precision::PConfusion();
  gp_Pnt2d PSol;
  
  Handle(Geom2d_Curve)     Guide;
  Handle(Bisector_BisecCC) BisTemp;

  // Change guiedline on Bis2.
  BisTemp      = Bis2->ChangeGuide();
  Guide        = Bis2->Curve(2);
#ifdef DEB
  gp_Pnt2d P2S = Bis2->ValueAndDist(D2.FirstParameter(),U1,UMax,Dist);
  gp_Pnt2d P2E = Bis2->ValueAndDist(D2.LastParameter() ,U1,UMin,Dist);
#else
  Bis2->ValueAndDist(D2.FirstParameter(),U1,UMax,Dist);
  Bis2->ValueAndDist(D2.LastParameter() ,U1,UMin,Dist);
#endif
  // Calculate the domain of intersection on the guideline.
  UMin = Max (D1.FirstParameter(),UMin);
  UMax = Min (D1.LastParameter() ,UMax);

  done = Standard_True;

  if (UMin - Eps > UMax + Eps) {return;}

  // Solution F = 0 to find the common point.
  Bisector_FunctionInter Fint (Guide,Bis1,BisTemp);
  math_BissecNewton      Sol (Fint,UMin,UMax,Tol,20);
  if (Sol.IsDone()) {
    USol   = Sol.Root();
  }
  else { return; }

  PSol    = BisTemp ->ValueAndDist(USol,U1,U2,Dist);
  
  IntRes2d_Transition        Trans1,Trans2;
  IntRes2d_IntersectionPoint PointInterSol(PSol,USol,U2,
					   Trans1,Trans2,Standard_False);
  Append (PointInterSol);
}



//=====================================================================================
// function : TestBound
// putpose  : Test if the extremities of Bis2 are on the segment cooresponding to Bis1.
//=====================================================================================
void Bisector_Inter::TestBound (const Handle(Geom2d_Line)&   Bis1,
				const IntRes2d_Domain&       D1,
				const Handle(Geom2d_Curve)&  Bis2,
				const IntRes2d_Domain&       D2,
				const Standard_Real          TolConf,
				const Standard_Boolean       Reverse)
{
  IntRes2d_Transition Trans1,Trans2;
  IntRes2d_IntersectionPoint PointInterSol;

  gp_Lin2d L1       = Bis1->Lin2d();
  gp_Pnt2d PF       = Bis2->Value(D2.FirstParameter());
  gp_Pnt2d PL       = Bis2->Value(D2.LastParameter());
//  Modified by skv - Mon May  5 14:43:28 2003 OCC616 Begin
//   Standard_Real Tol = Min(TolConf,Precision::Confusion());
//   Tol = 10*Tol;
  Standard_Real Tol = TolConf;
//  Modified by skv - Mon May  5 14:43:30 2003 OCC616 End

  Standard_Boolean BisecAlgo = Standard_False;
  if (Bis2->DynamicType() == STANDARD_TYPE(Bisector_BisecCC))
    {
      BisecAlgo = Standard_True;
//  Modified by skv - Mon May  5 14:43:45 2003 OCC616 Begin
//       Tol = 1.e-5;
//  Modified by skv - Mon May  5 14:43:46 2003 OCC616 End
    }

  if (L1.Distance(PF) < Tol) {
    Standard_Real U1 = ElCLib::Parameter(L1,PF);
//  Modified by skv - Mon May  5 14:48:12 2003 OCC616 Begin
//     if ( D1.FirstParameter() - Tol <= U1 &&
// 	 D1.LastParameter () + Tol >= U1   ) {
    if ( D1.FirstParameter() - D1.FirstTolerance() < U1 &&
	 D1.LastParameter () + D1.LastTolerance()  > U1   ) {
//  Modified by skv - Mon May  5 14:48:14 2003 OCC616 End
      // PF est sur L1
      if (BisecAlgo)
	PF = ElCLib::Value( U1 , L1 );
      PointInterSol.SetValues (PF, U1, D2.FirstParameter(), 
			       Trans1, Trans2, Reverse);
      Append (PointInterSol);
    }
  }  

  if (L1.Distance(PL) < Tol) {
    Standard_Real U1 = ElCLib::Parameter(L1,PL);
//  Modified by skv - Mon May  5 15:05:48 2003 OCC616 Begin
//     if ( D1.FirstParameter() - Tol <= U1 &&
// 	 D1.LastParameter () + Tol >= U1   ) {
    if ( D1.FirstParameter() - D1.FirstTolerance() < U1 &&
	 D1.LastParameter () + D1.LastTolerance()  > U1   ) {
//  Modified by skv - Mon May  5 15:05:49 2003 OCC616 End
      if (BisecAlgo)
	PL = ElCLib::Value( U1 , L1 );
      PointInterSol.SetValues (PL, U1, D2.LastParameter(), 
			       Trans1, Trans2, Reverse);
      Append (PointInterSol);
    }
  }	
}
