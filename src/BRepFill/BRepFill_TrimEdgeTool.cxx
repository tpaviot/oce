// Created on: 1995-04-24
// Created by: Bruno DUMORTIER
// Copyright (c) 1995-1999 Matra Datavision
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



#include <BRepFill_TrimEdgeTool.ixx>
#include <BRep_Tool.hxx>
#include <Bisector_BisecAna.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2d_CartesianPoint.hxx>
#include <Geom_Curve.hxx>
#include <GeomProjLib.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <Geom2dInt_GInter.hxx>
#include <gp_Pnt.hxx>
#include <TopLoc_Location.hxx>
#include <TopoDS.hxx>
#include <Precision.hxx>
#include <IntRes2d_IntersectionPoint.hxx>
#include <IntRes2d_IntersectionSegment.hxx>

#include <StdFail_NotDone.hxx>

#ifdef DRAW
#include <DrawTrSurf.hxx>
#include <DBRep.hxx>
static Standard_Boolean Affich       = Standard_False;
#endif


//=======================================================================
//function : SimpleExpression
//purpose  : 
//=======================================================================

static void SimpleExpression (const Bisector_Bisec&        B, 
			            Handle(Geom2d_Curve)&  Bis)
{
  Bis = B.Value();

  Handle(Standard_Type) BT = Bis->DynamicType();
  if (BT == STANDARD_TYPE(Geom2d_TrimmedCurve)) {
    Handle(Geom2d_TrimmedCurve) TrBis 
      = Handle(Geom2d_TrimmedCurve)::DownCast(Bis);
    Handle(Geom2d_Curve) BasBis = TrBis->BasisCurve();
    BT = BasBis->DynamicType();
    if (BT == STANDARD_TYPE(Bisector_BisecAna)) {
      Bis = Handle(Bisector_BisecAna)::DownCast(BasBis)->Geom2dCurve();
      Bis = new Geom2d_TrimmedCurve (Bis,
				     TrBis->FirstParameter(),
				     TrBis->LastParameter());
    }
  }
}


//=======================================================================
//function : BRepFill_TrimEdgeTool
//purpose  : 
//=======================================================================

BRepFill_TrimEdgeTool::BRepFill_TrimEdgeTool()
{
}


//=======================================================================
//function : BRepFill_TrimEdgeTool
//purpose  : 
//=======================================================================

BRepFill_TrimEdgeTool::BRepFill_TrimEdgeTool
(const Bisector_Bisec& Bisec,
 const Handle(Geom2d_Geometry)& S1,
 const Handle(Geom2d_Geometry)& S2,
 const Standard_Real   Offset) :
myOffset(Offset),
myBisec(Bisec)
{
  isPoint1 = (S1->DynamicType() == STANDARD_TYPE(Geom2d_CartesianPoint));
  isPoint2 = (S2->DynamicType() == STANDARD_TYPE(Geom2d_CartesianPoint));

// return geometries of shapes.
//  Standard_Real f,l;
  if (isPoint1) {
    myP1 = Handle(Geom2d_Point)::DownCast(S1)->Pnt2d();
  }
  else {
    myC1 = Handle(Geom2d_Curve)::DownCast(S1);
#ifdef DRAW
    if ( Affich) {
//POP pour NT
      char* myC1name = "myC1";
      DrawTrSurf::Set(myC1name,myC1);
//      DrawTrSurf::Set("myC1",myC1);
    }
#endif
  }
  if (isPoint2) {
    myP2 = Handle(Geom2d_Point)::DownCast(S2)->Pnt2d();
  }
  else {
    myC2 = Handle(Geom2d_Curve)::DownCast(S2);
#ifdef DRAW
    if ( Affich) {
      char* myC2name = "myC2";
      DrawTrSurf::Set(myC2name,myC2);
//      DrawTrSurf::Set("myC2",myC2);
    }
#endif
  }
  // return the simple expression of the bissectrice
  Handle(Geom2d_Curve) Bis;
  SimpleExpression(myBisec, Bis);
  myBis = Geom2dAdaptor_Curve(Bis);
#ifdef DRAW
  if ( Affich) {
      char* myBisname = "myBis";
      DrawTrSurf::Set(myBisname,Bis);
  }
#endif

}

//=======================================================================
//function : Bubble
//purpose  : Order the sequence of points by increasing x. 
//=======================================================================

static void Bubble(TColgp_SequenceOfPnt& Seq) 
{
  Standard_Boolean Invert = Standard_True;
  Standard_Integer NbPoints = Seq.Length();
  while (Invert) {
    Invert = Standard_False;
    for ( Standard_Integer i = 1; i < NbPoints; i++) {
      gp_Pnt P1 = Seq.Value(i);
      gp_Pnt P2 = Seq.Value(i+1);
      if (P2.X()<P1.X())  {
	Seq.Exchange(i,i+1);
	Invert = Standard_True;
      }
    }
  }
}


//=======================================================================
//function : EvalParameters  
//purpose  : 
//=======================================================================

static void EvalParameters(const Geom2dAdaptor_Curve& Bis,
			   const Geom2dAdaptor_Curve& AC,
			         TColgp_SequenceOfPnt& Params)
{
  Geom2dInt_GInter Intersector;
  Standard_Real Tol = Precision::Intersection();
//  Standard_Real TolC = 1.e-9;

  Geom2dAdaptor_Curve CBis(Bis);
  Geom2dAdaptor_Curve CAC (AC);

  if(AC.GetType() != GeomAbs_Circle || AC.GetType() != GeomAbs_Line) {
    Tol *= 100.;
  } 

  //Intersector = Geom2dInt_GInter(CBis, CAC, TolC, Tol);
  Intersector = Geom2dInt_GInter(CAC, CBis, Tol, Tol);

  Standard_Integer NbPoints, NbSegments;
  Standard_Real U1, U2;
  gp_Pnt P;

  if ( !Intersector.IsDone()) {
    StdFail_NotDone::Raise("BRepFill_TrimSurfaceTool::IntersectWith");
  }
  
  NbPoints = Intersector.NbPoints();
  
  if (NbPoints > 0) {
    for ( Standard_Integer i = 1; i <= NbPoints; i++) {
      U1 = Intersector.Point(i).ParamOnSecond();
      U2 = Intersector.Point(i).ParamOnFirst();
      P = gp_Pnt(U1,U2,0.);
      Params.Append(P);
    }
    
  }
  
  NbSegments = Intersector.NbSegments();
  
  if (NbSegments > 0) {
    IntRes2d_IntersectionSegment Seg;
    for ( Standard_Integer i = 1; i <= NbSegments; i++) {
      Seg = Intersector.Segment(i);
      U1  = Seg.FirstPoint().ParamOnSecond();
      Standard_Real Ulast = Seg.LastPoint().ParamOnSecond();
      if ( Abs(U1    - CBis.FirstParameter()) <= Tol &&
	   Abs(Ulast - CBis.LastParameter())  <= Tol    ) {
	P = gp_Pnt(U1,Seg.FirstPoint().ParamOnFirst(),0.);
	Params.Append(P);
	P = gp_Pnt(Ulast,Seg.LastPoint().ParamOnFirst(),0.);
	Params.Append(P);
      }
      else {
	U1 += Seg.LastPoint().ParamOnSecond();
	U1 /= 2.;
	U2  = Seg.FirstPoint().ParamOnFirst();
	U2 += Seg.LastPoint().ParamOnFirst();
	U2 /= 2.;
	P = gp_Pnt(U1,U2,0.);
	Params.Append(P);
      }
    }
  }

  // Order the sequence by growing parameter on the bissectrice.
  Bubble( Params);
}
			   
static void EvalParametersBis(const Geom2dAdaptor_Curve& Bis,
			      const Geom2dAdaptor_Curve& AC,
			      TColgp_SequenceOfPnt& Params,
			      const Standard_Real Tol)
{
  Geom2dInt_GInter Intersector;
  Standard_Real TolC = Tol;
  
  Geom2dAdaptor_Curve CBis(Bis);
  Geom2dAdaptor_Curve CAC (AC);

  Intersector = Geom2dInt_GInter(CAC, CBis, TolC, Tol);

  Standard_Integer NbPoints, NbSegments;
  Standard_Real U1, U2;
  gp_Pnt P;

  if ( !Intersector.IsDone()) {
    StdFail_NotDone::Raise("BRepFill_TrimSurfaceTool::IntersectWith");
  }
  
  NbPoints = Intersector.NbPoints();
  
  if (NbPoints > 0) {
    for ( Standard_Integer i = 1; i <= NbPoints; i++) {
      U1 = Intersector.Point(i).ParamOnSecond();
      U2 = Intersector.Point(i).ParamOnFirst();
      P = gp_Pnt(U1,U2,0.);
      Params.Append(P);
    }
    
  }
  
  NbSegments = Intersector.NbSegments();
  
  if (NbSegments > 0) {
    IntRes2d_IntersectionSegment Seg;
    for ( Standard_Integer i = 1; i <= NbSegments; i++) {
      Seg = Intersector.Segment(i);
      U1  = Seg.FirstPoint().ParamOnSecond();
      Standard_Real Ulast = Seg.LastPoint().ParamOnSecond();
      if ( Abs(U1    - CBis.FirstParameter()) <= Tol &&
	   Abs(Ulast - CBis.LastParameter())  <= Tol    ) {
	P = gp_Pnt(U1,Seg.FirstPoint().ParamOnFirst(),0.);
	Params.Append(P);
	P = gp_Pnt(Ulast,Seg.LastPoint().ParamOnFirst(),0.);
	Params.Append(P);
      }
      else {
	U1 += Seg.LastPoint().ParamOnSecond();
	U1 /= 2.;
	U2  = Seg.FirstPoint().ParamOnFirst();
	U2 += Seg.LastPoint().ParamOnFirst();
	U2 /= 2.;
	P = gp_Pnt(U1,U2,0.);
	Params.Append(P);
      }
    }
  }

  // Order the sequence by parameter growing on the bissectrice.
  Bubble( Params);
}


//=======================================================================
//function : IntersectWith
//purpose  : 
//=======================================================================

void BRepFill_TrimEdgeTool::IntersectWith(const TopoDS_Edge& Edge1,
					  const TopoDS_Edge& Edge2,
					        TColgp_SequenceOfPnt& Params)
{
  Params.Clear();

  // return curves associated to edges.
  TopLoc_Location L;
  Standard_Real   f,l;
  Handle(Geom_Surface) Surf;

  Handle(Geom2d_Curve) C1;
  BRep_Tool::CurveOnSurface(Edge1,C1,Surf,L,f,l);
  Geom2dAdaptor_Curve AC1(C1,f,l);

  Handle(Geom2d_Curve) C2;
  BRep_Tool::CurveOnSurface(Edge2,C2,Surf,L,f,l);
  Geom2dAdaptor_Curve AC2(C2,f,l);

#ifdef DRAW
  if ( Affich) {
    f = AC1.FirstParameter();
    l = AC1.LastParameter();
    char* CURVE1name = "CURVE1";
    DrawTrSurf::Set(CURVE1name, new Geom2d_TrimmedCurve(C1,f,l));
    f = AC2.FirstParameter();
    l = AC2.LastParameter();
    char* CURVE2name = "CURVE2";
    DrawTrSurf::Set(CURVE2name, new Geom2d_TrimmedCurve(C2,f,l));
    f = myBis.FirstParameter();
    l = myBis.LastParameter();
    char* bisname = "BIS";
    DrawTrSurf::Set(bisname, new Geom2d_TrimmedCurve(myBis.Curve(),f,l));
    char* Edge1name = "E1";
    DBRep::Set(Edge1name, Edge1);
    char* Edge2name = "E2";
    DBRep::Set(Edge2name, Edge2);

  }
#endif
  
  // Calculate intersection
  TColgp_SequenceOfPnt Points2;
  gp_Pnt PSeq;

  EvalParameters (myBis,AC1,Params);
  EvalParameters (myBis,AC2,Points2);


  Standard_Integer SeanceDeRattrapage=0;
  Standard_Real TolInit= 1.e-9;
  Standard_Integer nn = 7;

  if(AC1.GetType() != GeomAbs_Circle ||
     AC1.GetType() != GeomAbs_Line   ||
     AC2.GetType() != GeomAbs_Circle ||
     AC2.GetType() != GeomAbs_Line     ) {

    TolInit = 1.e-8;
    nn = 6;
  }
  
  while (     SeanceDeRattrapage < nn // TolInit <= 0.01
	 && ( Points2.Length() != Params.Length() || 
	     (Points2.Length() == 0 && Params.Length() == 0) ) ) {

#ifdef DEB
    cout << "BRepFill_TrimEdgeTool: incoherent intersection. Try with a greater tolerance" << endl;
#endif

    Params.Clear();
    Points2.Clear();
    
    TolInit*=10.0;
    
    EvalParametersBis(myBis,AC1,Params,TolInit);
    EvalParametersBis(myBis,AC2,Points2,TolInit); 
    SeanceDeRattrapage++;
  }

#ifdef DEB
  if(SeanceDeRattrapage != 0) cout << "SeanceDeRattrapage = " << SeanceDeRattrapage << endl;
  if(SeanceDeRattrapage == nn) { 
    cout << "BRepFill_TrimEdgeTool: incoherent intersection" << endl;
  }
#endif


  if(Params.Length() == 0 && Points2.Length() == 1) {

    //cout << "Params.Length() == 0 && Points2.Length() == 1" << endl;
    Standard_Real dmin;
    Standard_Real tBis = Points2(1).X();
    gp_Pnt2d PBis = myBis.Value(tBis);

    Standard_Real t = AC1.FirstParameter();
    gp_Pnt2d PC = AC1.Value(t);
    dmin = PC.SquareDistance(PBis);
    gp_Pnt P(tBis, t, 0.);
    Params.Append(P);

    t = AC1.LastParameter();
    PC = AC1.Value(t);
    if(dmin > PC.SquareDistance(PBis)) {
      P.SetY(t);
      Params.SetValue(1,P);
    }
  }
  else if(Params.Length() == 1 && Points2.Length() == 0) {

    //cout << "Params.Length() == 1 && Points2.Length() == 0" << endl;
    Standard_Real dmin;
    Standard_Real tBis = Params(1).X();
    gp_Pnt2d PBis = myBis.Value(tBis);

    Standard_Real t = AC2.FirstParameter();
    gp_Pnt2d PC = AC2.Value(t);
    dmin = PC.SquareDistance(PBis);
    gp_Pnt P(tBis, t, 0.);
    Points2.Append(P);

    t = AC2.LastParameter();
    PC = AC2.Value(t);
    if(dmin > PC.SquareDistance(PBis)) {
      P.SetY(t);
      Points2.SetValue(1,P);
    }
  }

  // small manipulation to remove incorrect intersections:
  // return only common intersections (same parameter
  // on the bissectrice.).
  // The tolerance can be eventually changed.

  gp_Pnt P1,P2;
  Standard_Real Tol = 4 * 100 * Precision::PConfusion();
  Standard_Integer i = 1;
  Standard_Integer NbPoints = Params.Length();

  if(NbPoints == 1 && Points2.Length() == 1) {
    //cout << "NbPoints == 1 && Points2.Length() == 1" << endl;
    for ( i = 1; i <= NbPoints; i++) {
      PSeq = Params(i);
      PSeq.SetZ((Points2.Value(i)).Y());
      Params.SetValue(i,PSeq);
    }
    return;
  }    

  i = 1;
  while ( i <= Min( Params.Length(), Points2.Length())) {
    P1 = Params(i);
    P2 = Points2(i);
    Standard_Real P1xP2x=Abs( P1.X() - P2.X());

    if ( P1xP2x > Tol ) {
#ifdef DEB
      cout << "BRepFill_TrimEdgeTool: no same parameter on the bissectrice" << endl;
#endif
      if(P1xP2x>TolInit) { 
#ifdef DEB
      cout << "BRepFill_TrimEdgeTool: Continue somehow" << endl;
#endif	
      i++;
      }
      else { 
	if ( P1.X() < P2.X()) Params.Remove(i);
	else                  Points2.Remove(i);
      }
    }
    else i++;
  }

  if ( Params.Length() > Points2.Length()) {
    Params.Remove(Points2.Length()+1, Params.Length());
  }
  else if ( Params.Length() < Points2.Length()) {
    Points2.Remove(Params.Length()+1, Points2.Length());
  }

  NbPoints = Params.Length();
  for ( i = 1; i <= NbPoints; i++) {
    PSeq = Params(i);
    PSeq.SetZ((Points2.Value(i)).Y());
    Params.SetValue(i,PSeq);
  }
}

//=======================================================================
//function : AddOrConfuse
//purpose  : the first or the last point of the bissectrice is on the 
//           parallel if it was not found in the intersections, 
//           it is projected on parallel lines and added in the parameters 
//=======================================================================

void BRepFill_TrimEdgeTool::AddOrConfuse(const Standard_Boolean  Start,
					 const TopoDS_Edge&      Edge1,
					 const TopoDS_Edge&      Edge2,
					 TColgp_SequenceOfPnt&   Params) 
const 
{
  Standard_Boolean  ToProj = Standard_True;
  gp_Pnt2d          PBis;
  Standard_Real     Tol = 10*Precision::Confusion(); 

  // return curves associated to edges.
  TopLoc_Location L;
  Standard_Real   f,l;
  Handle(Geom_Surface) Surf;

  Handle(Geom2d_Curve) C1;
  BRep_Tool::CurveOnSurface(Edge1,C1,Surf,L,f,l);
  Geom2dAdaptor_Curve AC1(C1,f,l);


  if (Start) PBis = myBis.Value(myBis.FirstParameter());
  else       PBis = myBis.Value(myBis.LastParameter ()); 

  // Test if the end of the bissectrice is in the set of intersection points.
  if (!Params.IsEmpty()) {
    gp_Pnt2d P;
    if (Start) P = AC1.Value(Params.First().Y());
    else       P = AC1.Value(Params.Last ().Y()); 
    ToProj     = !PBis.IsEqual(P,Tol);
  }
  
  if (ToProj) {
#ifdef DEB
    cout << " project extremity bissectrice on parallel."<<endl;
#endif

    // Project point on parallels and add in Params

    Standard_Real f2,l2;
    Handle(Geom2d_Curve) C2;
    BRep_Tool::CurveOnSurface(Edge2,C2,Surf,L,f2,l2);

    Geom2dAPI_ProjectPointOnCurve Projector1(PBis,C1,f,l);    
    Geom2dAPI_ProjectPointOnCurve Projector2(PBis,C2,f2,l2);

    if (Projector1.NbPoints() == 0) {
#ifdef DEB
      cout << "Failed projection in BRepFill_TrimEdgeTool::AddOrConfuse"<<endl;
#endif
      return;
    }
    if (!Projector1.NearestPoint().IsEqual(PBis,Tol)) {
#ifdef DEB
      cout <<"Incorrect solution in BRepFill_TrimEdgeTool::AddOrConfuse"<<endl;
#endif
      return;
    }
    if (Projector2.NbPoints() == 0) {
#ifdef DEB
      cout << "Failed projection in BRepFill_TrimEdgeTool::AddOrConfuse"<<endl;
#endif
      return;
    }
    if (!Projector2.NearestPoint().IsEqual(PBis,Tol)) {
#ifdef DEB
      cout <<" Mauvaisesolution dans BRepFill_TrimEdgeTool::AddOrConfuse"<<endl;
#endif
      return;
    }
    gp_Pnt PInt (0,
		 Projector1.LowerDistanceParameter(),
		 Projector2.LowerDistanceParameter());
    if (Start) {
      PInt.SetX (myBis.FirstParameter());
      Params.Prepend(PInt);
    }
    else {
      PInt.SetX (myBis.LastParameter());
      Params.Append(PInt);
    }
  }
}

//=======================================================================
//function : IsInside
//purpose  : 
//=======================================================================

Standard_Boolean BRepFill_TrimEdgeTool::IsInside(const gp_Pnt2d& P) const 
{
//  Modified by Sergey KHROMOV - Fri Sep 27 11:43:12 2002 Begin
//   Standard_Real Dist;
  Standard_Real Dist = RealLast();
//  Modified by Sergey KHROMOV - Fri Sep 27 11:43:12 2002 End
  if (isPoint1) 
    Dist = P.Distance(myP1);
  else if (isPoint2) 
    Dist = P.Distance(myP2);
  else {
    Geom2dAPI_ProjectPointOnCurve Projector(P,myC1);
    if (Projector.NbPoints() > 0) {
      Dist = Projector.LowerDistance();
    }
//  Modified by Sergey KHROMOV - Fri Sep 27 11:43:43 2002 Begin
//     else {
//       gp_Pnt2d PF = myC1->Value(myC1->FirstParameter());
//       gp_Pnt2d PL = myC1->Value(myC1->LastParameter());
//       Dist = Min (P.Distance(PF),P.Distance(PL));
//     }

// Check of distances between P and first and last point of the first curve
// should be performed in any case, despite of the results of projection.
    gp_Pnt2d      PF       = myC1->Value(myC1->FirstParameter());
    gp_Pnt2d      PL       = myC1->Value(myC1->LastParameter());
    Standard_Real aDistMin = Min (P.Distance(PF),P.Distance(PL));

    if (Dist > aDistMin)
      Dist = aDistMin;
//  Modified by Sergey KHROMOV - Fri Sep 27 11:43:44 2002 End
  }
  
//  return (Dist < Abs(myOffset);
// return (Dist < Abs(myOffset) + Precision::Confusion());
  return (Dist < Abs(myOffset) - Precision::Confusion());
}

