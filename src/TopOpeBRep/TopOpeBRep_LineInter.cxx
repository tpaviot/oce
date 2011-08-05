// File:      TopOpeBRep_LineInter.cxx
// Created:   Wed Nov 10 18:31:43 1993
// Author:    Jean Yves LEBEY
// Copyright: OPEN CASCADE 1993

#include <TopOpeBRep_LineInter.ixx>

#include <TopOpeBRep.hxx>
#include <TopOpeBRep_VPointInter.hxx>
#include <TopOpeBRep_VPointInterIterator.hxx>
#include <TopOpeBRep_FFTransitionTool.hxx>

#include <IntPatch_IType.hxx>
#include <Geom_Line.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Ellipse.hxx>
#include <Geom_Parabola.hxx>
#include <Geom_Hyperbola.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <IntPatch_ALineToWLine.hxx>
#include <IntSurf_Quadric.hxx>
#include <GeomAbs_SurfaceType.hxx> 
#include <gp_Pnt.hxx>

#include <Adaptor2d_HCurve2d.hxx>
#include <BRepAdaptor_Curve2d.hxx>
#include <TopAbs.hxx>

#include <Standard_ProgramError.hxx>
#include <Standard_NotImplemented.hxx>

#ifdef DEB
Standard_IMPORT Standard_Boolean TopOpeBRep_GetcontextALWLNBP(Standard_Integer&);
Standard_IMPORT Standard_Boolean TopOpeBRep_GettraceCONIC();
Standard_IMPORT Standard_Boolean TopOpeBRepDS_GettraceDSF();
Standard_IMPORT Standard_Boolean TopOpeBRepDS_GettraceDSNC();
#endif

//-----------------------------------------------------------------------
static Handle(IntPatch_WLine) FUN_ALINETOWLINE
(const Handle(IntPatch_ALine)& AL,
 const BRepAdaptor_Surface surf1,const BRepAdaptor_Surface surf2)
//-----------------------------------------------------------------------
{
  IntSurf_Quadric Quad1,Quad2;

  switch(surf1.GetType())
  {
    case GeomAbs_Plane:    Quad1.SetValue(surf1.Plane()); break;
    case GeomAbs_Cylinder: Quad1.SetValue(surf1.Cylinder()); break;
    case GeomAbs_Sphere:   Quad1.SetValue(surf1.Sphere()); break;
    case GeomAbs_Cone:     Quad1.SetValue(surf1.Cone()); break;
    default : Standard_ProgramError::Raise
      ("TopOpeBRep_LineInter::FUN_ALINETOWLINE"); break;
  }
  
  switch(surf2.GetType())
  {
    case GeomAbs_Plane:    Quad2.SetValue(surf2.Plane()); break;
    case GeomAbs_Cylinder: Quad2.SetValue(surf2.Cylinder()); break;
    case GeomAbs_Sphere:   Quad2.SetValue(surf2.Sphere()); break;
    case GeomAbs_Cone:     Quad2.SetValue(surf2.Cone()); break;
    default : Standard_ProgramError::Raise
      ("TopOpeBRep_LineInter::FUN_ALINETOWLINE"); break;
  }

  const Standard_Real deflectionmax = 0.01;
  const Standard_Real pasUVmax = 0.05;
  Standard_Integer nbpointsmax = 200;
#ifdef DEB
  Standard_Integer newnbp;
  if (TopOpeBRep_GetcontextALWLNBP(newnbp)) nbpointsmax = newnbp;
#endif
  IntPatch_ALineToWLine 
    AToL(Quad1,Quad2,deflectionmax,pasUVmax,nbpointsmax);
  return AToL.MakeWLine(AL);
}

//=======================================================================
//function : SetLine
//purpose  : 
//=======================================================================

void TopOpeBRep_LineInter::SetLine(const Handle(IntPatch_Line)& L,
                                   const BRepAdaptor_Surface& S1,
                                   const BRepAdaptor_Surface& S2)
{
  // load line according to its type
  myIL = L;
  IntPatch_IType type = L->ArcType();
  switch (type) {
  case IntPatch_Analytic :    myTypeLineCurve = TopOpeBRep_ANALYTIC; break;
  case IntPatch_Restriction : myTypeLineCurve = TopOpeBRep_RESTRICTION; break;
  case IntPatch_Walking :     myTypeLineCurve = TopOpeBRep_WALKING; break;
  case IntPatch_Lin :         myTypeLineCurve = TopOpeBRep_LINE; break;
  case IntPatch_Circle :      myTypeLineCurve = TopOpeBRep_CIRCLE; break;
  case IntPatch_Ellipse :     myTypeLineCurve = TopOpeBRep_ELLIPSE; break;
  case IntPatch_Parabola :    myTypeLineCurve = TopOpeBRep_PARABOLA; break;
  case IntPatch_Hyperbola :   myTypeLineCurve = TopOpeBRep_HYPERBOLA; break;
  default : 
    myTypeLineCurve = TopOpeBRep_OTHERTYPE; 
    SetOK(Standard_False);
    break;
  }

  switch (type) {
  case IntPatch_Analytic :
    myILA = *((Handle(IntPatch_ALine)*)&L); break;
  case IntPatch_Restriction :
    myILR = *((Handle(IntPatch_RLine)*)&L); break;
  case IntPatch_Walking : 
    myILW = *((Handle(IntPatch_WLine)*)&L); break;
  default :  //"geometric" line
    myILG = *((Handle(IntPatch_GLine)*)&L); break;
  }

  // transform an analytic line to a walking line
  if (myTypeLineCurve == TopOpeBRep_ANALYTIC) {
    myILW = ::FUN_ALINETOWLINE(myILA,S1,S2);
    myTypeLineCurve = TopOpeBRep_WALKING;
  }

  // number of points found on restriction(s)
  Standard_Integer n = 0;
  switch (myTypeLineCurve) { 
  case TopOpeBRep_ANALYTIC :    n = myILA->NbVertex(); break;
  case TopOpeBRep_RESTRICTION : n = myILR->NbVertex(); break;
  case TopOpeBRep_WALKING :     n = myILW->NbVertex(); break;
  case TopOpeBRep_LINE :        n = myILG->NbVertex(); break;
  case TopOpeBRep_CIRCLE :      n = myILG->NbVertex(); break;
  case TopOpeBRep_ELLIPSE :     n = myILG->NbVertex(); break;
  case TopOpeBRep_PARABOLA :    n = myILG->NbVertex(); break; 
  case TopOpeBRep_HYPERBOLA :   n = myILG->NbVertex(); break;
  default : 
    SetOK(Standard_False);
    break;
  }
  myNbVPoint = n;

  // prepare VPoints from intersection points
  myHAVP = new TopOpeBRep_HArray1OfVPointInter(0,n);
  for (Standard_Integer i=1;i<=n;i++) {
    TopOpeBRep_VPointInter& VP = myHAVP->ChangeValue(i);
    switch (myTypeLineCurve) {
    case TopOpeBRep_ANALYTIC :    VP.SetPoint(myILA->Vertex(i)); break;
    case TopOpeBRep_RESTRICTION : VP.SetPoint(myILR->Vertex(i)); break;
    case TopOpeBRep_WALKING :     VP.SetPoint(myILW->Vertex(i)); break;
    default :                     VP.SetPoint(myILG->Vertex(i)); break;
    }
    VP.Index(i);
  }
}

//=======================================================================
//function : VPoint
//purpose  : 
//=======================================================================

const TopOpeBRep_VPointInter& TopOpeBRep_LineInter::VPoint(const Standard_Integer I) const
{
  return myHAVP->Value(I);
}
  
//=======================================================================
//function : ChangeVPoint
//purpose  : 
//=======================================================================

TopOpeBRep_VPointInter& TopOpeBRep_LineInter::ChangeVPoint(const Standard_Integer I)
{
  return myHAVP->ChangeValue(I);
}
  
//=======================================================================
//function : SetINL
//purpose  : 
//=======================================================================

void TopOpeBRep_LineInter::SetINL()
{
  TopOpeBRep_VPointInterIterator VPI(*this);
  if (!VPI.More()) {
    myINL = Standard_False;
    return;
  }
  const Standard_Real p0 = VPI.CurrentVP().ParameterOnLine();
  VPI.Next();
  if (!VPI.More()) { 
    myINL = Standard_True;
    return;
  }
  for (; VPI.More(); VPI.Next() ) {
    const Standard_Real p = VPI.CurrentVP().ParameterOnLine();
    if ( p != p0 ) {
      myINL = Standard_False;
      return;
    }
  }
  myINL = Standard_True;
}

//=======================================================================
//function : SetIsVClosed
//purpose  : 
//=======================================================================

void TopOpeBRep_LineInter::SetIsVClosed()
{
  if (myINL) {
    myIsVClosed = Standard_False;
    return;    
  }

  /*Standard_Boolean newV = Standard_True;
  if (!newV) {
    if (myTypeLineCurve != TopOpeBRep_WALKING) {
      myIsVClosed = Standard_False;
      return;
    }
  }*/
  
  TopOpeBRep_VPointInterIterator VPI(*this);
  Standard_Integer nV = myNbVPoint;
  Standard_Real    pmin = RealLast(),pmax = RealFirst();
  Standard_Integer imin=0, imax = 0; // index of IsOnArc VPoints
  if (nV >= 2) {
    for (; VPI.More(); VPI.Next() ) {
      const TopOpeBRep_VPointInter& P = VPI.CurrentVP();
      if ( ! P.IsInternal() ) {
	const Standard_Integer i = VPI.CurrentVPIndex();
	const Standard_Real p = P.ParameterOnLine();
	if ( p < pmin ) { imin = i; pmin = p; }
	if ( p > pmax ) { imax = i; pmax = p; }
      }
    }
    if ( imax == 0 ) {       // no VPoint on restriction found
      myIsVClosed = Standard_True;
      return;
    }

    const TopOpeBRep_VPointInter& P1 = VPoint(imin);
    const TopOpeBRep_VPointInter& P2 = VPoint(imax);

    const gp_Pnt& pp1 = P1.Value();
    const gp_Pnt& pp2 = P2.Value();

    const Standard_Real tol1 = P1.Tolerance();
    const Standard_Real tol2 = P2.Tolerance();
    const Standard_Real tol = Max(tol1,tol2);

    myIsVClosed = pp1.IsEqual(pp2,tol);
  }
  else {
    SetOK(Standard_False);
    myIsVClosed = Standard_False;
  }
}

//=======================================================================
//function : SetHasVPonR
//purpose  : 
//=======================================================================

void TopOpeBRep_LineInter::SetHasVPonR()
{
  myHasVPonR = Standard_False;
  TopOpeBRep_VPointInterIterator VPI(*this);
  for (; VPI.More(); VPI.Next()) {
    const TopOpeBRep_VPointInter& P = VPI.CurrentVP();
    if (P.IsOnDomS1() || P.IsOnDomS2()) {
      myHasVPonR = Standard_True;
      break;
    }
  }
}

//=======================================================================
//function : SetVPBounds
//purpose  : 
//=======================================================================

void TopOpeBRep_LineInter::SetVPBounds()
{
  myVPF = myVPL = myVPN = 0;
  myVPBDefined = Standard_True;

  TopOpeBRep_VPointInterIterator VPI(*this);
  Standard_Integer f = myNbVPoint + 1, l = 0, n = 0;
  
  for (; VPI.More(); VPI.Next()) {
    if (VPI.CurrentVP().Keep()) {
      n++;
      const Standard_Integer i = VPI.CurrentVPIndex();
      if ( i < f ) f = i;
      if ( i > l ) l = i;
    }
  }    
  
  myVPF = f; myVPL = l; myVPN = n;  
}

//=======================================================================
//function : VPBounds
//purpose  : 
//=======================================================================

void TopOpeBRep_LineInter::VPBounds
(Standard_Integer& f, Standard_Integer& l, Standard_Integer& n) const
{
  if ( !myVPBDefined ) {
    TopOpeBRep_LineInter* p = (TopOpeBRep_LineInter*)this; // NYI deconst
    p->SetOK(Standard_False);
    f = l = n = 0;
    return;
  }
  f = myVPF;
  l = myVPL;
  n = myVPN;
}

//=======================================================================
//function : IsPeriodic
//purpose  : 
//=======================================================================

Standard_Boolean TopOpeBRep_LineInter::IsPeriodic() const
{
  switch (myTypeLineCurve)
  {
    case TopOpeBRep_CIRCLE  :
    case TopOpeBRep_ELLIPSE : return Standard_True;
    default: /* Do nothing */ break;
  }
  return Standard_False;
}

//=======================================================================
//function : Period
//purpose  : 
//=======================================================================

Standard_Real TopOpeBRep_LineInter::Period() const
{
  Standard_Real f,l;
  Bounds(f,l);
  return (l - f);
}

//=======================================================================
//function : Bounds
//purpose  : 
//=======================================================================

void TopOpeBRep_LineInter::Bounds(Standard_Real& First,Standard_Real& Last) const
{
  if ( myILG.IsNull() )  {
    TopOpeBRep_LineInter* p = (TopOpeBRep_LineInter*)this; // NYI deconst
    p->SetOK(Standard_False);
    return;
  }
  
  First = 0.; Last = 0.;
  if ( IsPeriodic() )
    Last = Curve()->Period();
  
  if ( myILG->HasFirstPoint() )
    First = myILG->FirstPoint().ParameterOnLine();

  if ( myILG->HasLastPoint() )
    Last = myILG->LastPoint().ParameterOnLine();
}

//=======================================================================
//function : HasVInternal
//purpose  : 
//=======================================================================

Standard_Boolean TopOpeBRep_LineInter::HasVInternal()
{
  TopOpeBRep_VPointInterIterator VPI(*this);
  for (; VPI.More(); VPI.Next()) {
    if (VPI.CurrentVP().IsInternal()) return Standard_True;
  }
  return Standard_False;
}


//=======================================================================
//function : NbWPoint
//purpose  : 
//=======================================================================

Standard_Integer TopOpeBRep_LineInter::NbWPoint() const
{
  switch (myTypeLineCurve)
  {
    case TopOpeBRep_WALKING : return myILW->NbPnts();
    default: /* Do nothing */ break;
  }
  return 0;
}


//=======================================================================
//function : WPoint
//purpose  : 
//=======================================================================

const TopOpeBRep_WPointInter& TopOpeBRep_LineInter::WPoint(const Standard_Integer IW)
{
  switch (myTypeLineCurve)
  {
    case TopOpeBRep_RESTRICTION : myCurrentWP.Set(myILR->Point(IW)); break;
    case TopOpeBRep_WALKING :     myCurrentWP.Set(myILW->Point(IW)); break;
    default : break;
  }
  return myCurrentWP;
}

//=======================================================================
//function : Curve
//purpose  : 
//=======================================================================

Handle(Geom_Curve) TopOpeBRep_LineInter::Curve() const 
{
  // Build the 3d curve
  Handle(Geom_Curve) C3D;
  switch (myTypeLineCurve) {
  case TopOpeBRep_LINE : 
    C3D = new Geom_Line(myILG->Line()); break;
  case TopOpeBRep_CIRCLE :    
    C3D = new Geom_Circle(myILG->Circle()); break;
  case TopOpeBRep_ELLIPSE :   
    C3D = new Geom_Ellipse(myILG->Ellipse()); break;
  case TopOpeBRep_PARABOLA :  
    C3D = new Geom_Parabola(myILG->Parabola()); break;
  case TopOpeBRep_HYPERBOLA : 
    C3D = new Geom_Hyperbola(myILG->Hyperbola()); break;
  default : 
    TopOpeBRep_LineInter* p = (TopOpeBRep_LineInter*)this; // NYI deconst
    p->SetOK(Standard_False);
    break;
  }
  return C3D;
}

//=======================================================================
//function : Curve
//purpose  : 
//=======================================================================

Handle(Geom_Curve) TopOpeBRep_LineInter::Curve
(const Standard_Real parmin, const Standard_Real parmax) const 
{
  // Build the trimmed 3d curve
  Handle(Geom_Curve) C3D = Curve();
  Handle(Geom_TrimmedCurve) TC3D = new Geom_TrimmedCurve(C3D,parmin,parmax);
#ifdef DEB
  if ( TopOpeBRep_GettraceCONIC() ) {
    cout<<"TopOpeBRep_LineInter::Curve on a ";
    TopOpeBRep::Print(myTypeLineCurve,cout);cout<<endl;
    cout<<"  ... Trimmed from "<<parmin<<" to "<<parmax<<endl;
  }
#endif
  return TC3D;
}

//=======================================================================
//function : Arc
//purpose  : 
//=======================================================================

const TopoDS_Shape& TopOpeBRep_LineInter::Arc() const
{
  if (myTypeLineCurve == TopOpeBRep_RESTRICTION) {
    if(myILR->IsArcOnS1()) { 
      const Handle(Adaptor2d_HCurve2d)& AHC2D = myILR->ArcOnS1();
      const BRepAdaptor_Curve2d& BC2DP = *((BRepAdaptor_Curve2d*)&(AHC2D->Curve2d()));
      const TopoDS_Shape& S = BC2DP.Edge();
      return S;
    }
    else { 
      const Handle(Adaptor2d_HCurve2d)& AHC2D = myILR->ArcOnS2();
      const BRepAdaptor_Curve2d& BC2DP = *((BRepAdaptor_Curve2d*)&(AHC2D->Curve2d()));
      const TopoDS_Shape& S = BC2DP.Edge();
      return S;
    }
  }
  else
    return myNullShape;
}

//=======================================================================
//function : ArcIsEdge
//purpose  : 
//=======================================================================

Standard_Boolean TopOpeBRep_LineInter::ArcIsEdge(const Standard_Integer Index) const
{
  if (myTypeLineCurve == TopOpeBRep_RESTRICTION) {
    const Standard_Boolean r = myILR->IsArcOnS1();
    return ( Index == 2 ? !r : r );
  }
  return Standard_False;
}

//=======================================================================
//function : HasFirstPoint
//purpose  : 
//=======================================================================

Standard_Boolean TopOpeBRep_LineInter::HasFirstPoint() const
{
  if (myILG.IsNull())
    Standard_ProgramError::Raise("TopOpeBRep_LineInter::HasFirstPoint sur line != GLine");
  return myILG->HasFirstPoint();
}

//=======================================================================
//function : HasLastPoint
//purpose  : 
//=======================================================================

Standard_Boolean TopOpeBRep_LineInter::HasLastPoint() const
{
  if (myILG.IsNull())
    Standard_ProgramError::Raise("TopOpeBRep_LineInter::HasLastPoint sur line != GLine");
  return myILG->HasLastPoint();
}

//=======================================================================
//function : ComputeFaceFaceTransition
//purpose  : 
//=======================================================================

void TopOpeBRep_LineInter::ComputeFaceFaceTransition()
{
  TopAbs_Orientation F1ori = myF1.Orientation();
  TopAbs_Orientation F2ori = myF2.Orientation();
  myLineTonF1=TopOpeBRep_FFTransitionTool::ProcessFaceTransition(*this,1,F2ori);
  myLineTonF2=TopOpeBRep_FFTransitionTool::ProcessFaceTransition(*this,2,F1ori);
}

//=======================================================================
//function : FaceFaceTransition
//purpose  : 
//=======================================================================
const TopOpeBRepDS_Transition& TopOpeBRep_LineInter::FaceFaceTransition
(const Standard_Integer I) const
{
  if (I == 1) return myLineTonF1;
  if (I == 2) return myLineTonF2;
  Standard_ProgramError::Raise("TopOpeBRep_LineInter::FaceFaceTransition");
  return myLineTonF1;
}

//=======================================================================
//function : DumpType
//purpose  : 
//=======================================================================

void TopOpeBRep_LineInter::DumpType()const
{
#ifdef DEB
  TopOpeBRep::Print(myTypeLineCurve,cout);
#endif
}

//=======================================================================
//function : DumpVPoint
//purpose  : 
//=======================================================================

void TopOpeBRep_LineInter::DumpVPoint
#ifndef DEB
(const Standard_Integer ,
 const TCollection_AsciiString& ,
 const TCollection_AsciiString& ) const
{
#else
(const Standard_Integer I,
 const TCollection_AsciiString& s1,
 const TCollection_AsciiString& s2) const
{
  const TopOpeBRep_VPointInter& VP = VPoint(I);
  const gp_Pnt& P = VP.Value();
  cout<<s1;
  cout<<"L"<<Index()<<"P"<<VP.Index();
  if (VP.Keep()) cout<<"K";
  cout<<" "<<P.X()<<" "<<P.Y()<<" "<<P.Z();
  cout<<s2;
#endif
}

//=======================================================================
//function : DumpBipoint
//purpose  : 
//=======================================================================

void TopOpeBRep_LineInter::DumpBipoint
#ifndef DEB
(const TopOpeBRep_Bipoint& ,
 const TCollection_AsciiString& ,
 const TCollection_AsciiString& ) const
{
#else
(const TopOpeBRep_Bipoint& bip,
 const TCollection_AsciiString& s1,
 const TCollection_AsciiString& s2) const
{
  Standard_Integer i1 = bip.I1();
  Standard_Integer i2 = bip.I2();
  cout<<s1;
  cout<<"("<<i1<<","<<i2<<")";
  cout<<s2;
#endif
}

//=======================================================================
//function : SetOK
//purpose  : 
//=======================================================================

void TopOpeBRep_LineInter::SetOK(const Standard_Boolean B)
{
#ifdef DEB
  if (TopOpeBRepDS_GettraceDSF() || TopOpeBRepDS_GettraceDSNC()) {
    if (myOK != B) {
      cout<<"line "<<myIndex<<" (";
      TopOpeBRep::Print(myTypeLineCurve,cout);cout<<") ";
      if (!B) cout<<"OK->NOK"; else cout<<"NOK->OK";
      cout<<endl;
    }
  }
#endif
  myOK = B;
}

//=======================================================================
//function : SetTraceIndex
//purpose  : 
//=======================================================================

void TopOpeBRep_LineInter::SetTraceIndex(const Standard_Integer exF1,
					 const Standard_Integer exF2)
{ 
  myexF1 = exF1;
  myexF2 = exF2;
}

//=======================================================================
//function : GetTraceIndex
//purpose  : 
//=======================================================================

void TopOpeBRep_LineInter::GetTraceIndex(Standard_Integer& exF1,
					 Standard_Integer& exF2)const 
{ 
  exF1 = myexF1;
  exF2 = myexF2;
}

//=======================================================================
//function : DumpLineTransitions
//purpose  : 
//=======================================================================
Standard_OStream& TopOpeBRep_LineInter::DumpLineTransitions(Standard_OStream& OS) const
{
#ifdef DEB
  OS<<"transition from f1 / f2 "; TopAbs::Print(myF2.Orientation(),OS);
  OS<<" : "; myLineTonF1.Dump(OS); OS<<endl;
  OS<<"transition from f2 / f1 "; TopAbs::Print(myF1.Orientation(),OS);
  OS<<" : "; myLineTonF2.Dump(OS); OS<<endl;
#endif
  return OS;
}
