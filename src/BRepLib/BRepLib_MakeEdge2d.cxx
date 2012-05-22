// Created on: 1995-01-04
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



#include <BRepLib_MakeEdge2d.ixx>

#include <BRepLib.hxx>
#include <BRep_Tool.hxx>
#include <BRep_Builder.hxx>
#include <TopoDS.hxx>
#include <Geom_Plane.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2d_Parabola.hxx>
#include <Geom2d_Hyperbola.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2dAdaptor_Curve.hxx>
#include <Extrema_ExtPC2d.hxx>
#include <gp.hxx>
#include <ElCLib.hxx>
#include <ElSLib.hxx>
#include <Precision.hxx>


//=======================================================================
//function : Point
//purpose  : make a 3d point on the current plane
//=======================================================================

static gp_Pnt Point(const gp_Pnt2d& P)
{
  return BRepLib::Plane()->Value(P.X(),P.Y());
}

//=======================================================================
//function : Project
//purpose  : project a vertex on the current plane
//=======================================================================

static gp_Pnt2d Project(const TopoDS_Vertex& Ve)
{
  gp_Pnt P = BRep_Tool::Pnt(Ve); 
  Standard_Real U,V;
  ElSLib::Parameters(BRepLib::Plane()->Pln(),P,U,V);
  return gp_Pnt2d(U,V);
}

//=======================================================================
//function : Project
//purpose  : project a vertex on a curve
//=======================================================================

static Standard_Boolean Project(const Handle(Geom2d_Curve)& C,
				const TopoDS_Vertex& V,
				Standard_Real& p)
{
  gp_Pnt2d P = Project(V);
  Geom2dAdaptor_Curve AC(C);
  if (AC.GetType() == GeomAbs_Line) {
    p = ElCLib::LineParameter(AC.Line().Position(),P);
  }
  else if (AC.GetType() == GeomAbs_Circle) {
    p = ElCLib::CircleParameter(AC.Circle().Position(),P);
  }
  else {
    Extrema_ExtPC2d extrema(P,AC);
    if (extrema.IsDone()) {
      Standard_Integer i,n = extrema.NbExt();
      
      Standard_Real d2 = RealLast();
      for (i = 1; i <= n; i++) {
	//OCC16852:if (extrema.IsMin(i)) {
	  const Standard_Real dd2 = extrema.SquareDistance(i);
	  if (dd2 < d2) {
	    d2 = dd2;
	    p = extrema.Point(i).Parameter();
	  }
	//OCC16852:}
      }
    }
    else
      return Standard_False;
  }
  return Standard_True;
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const TopoDS_Vertex& V1, 
				       const TopoDS_Vertex& V2)
{
  gp_Pnt2d P1 = Project(V1);
  gp_Pnt2d P2 = Project(V2);
  Standard_Real l = P1.Distance(P2);
  if (l <= gp::Resolution()) {
    myError = BRepLib_LineThroughIdenticPoints;
    return;
  }
  gp_Lin2d L(P1,gp_Vec2d(P1,P2));
  Handle(Geom2d_Line) GL = new Geom2d_Line(L);
  Init(GL,V1,V2,0,l);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Pnt2d& P1, 
				       const gp_Pnt2d& P2)
{
  Standard_Real l = P1.Distance(P2);
  if (l <= gp::Resolution()) {
    myError = BRepLib_LineThroughIdenticPoints;
    return;
  }
  gp_Lin2d L(P1,gp_Vec2d(P1,P2));
  Handle(Geom2d_Line) GL = new Geom2d_Line(L);
  Init(GL,P1,P2,0,l);
}


//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Lin2d& L)
{
  Handle(Geom2d_Line) GL = new Geom2d_Line(L);
  Init(GL);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Lin2d& L, 
				       const Standard_Real p1, 
				       const Standard_Real p2)
{
  Handle(Geom2d_Line) GL = new Geom2d_Line(L);
  Init(GL,p1,p2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Lin2d& L, 
				       const gp_Pnt2d& P1, 
				       const gp_Pnt2d& P2)
{
  Handle(Geom2d_Line) GL = new Geom2d_Line(L);
  Init(GL,P1,P2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Lin2d& L, 
				       const TopoDS_Vertex& V1, 
				       const TopoDS_Vertex& V2)
{
  Handle(Geom2d_Line) GL = new Geom2d_Line(L);
  Init(GL,V1,V2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Circ2d& C) 
{
  Handle(Geom2d_Circle) GC = new Geom2d_Circle(C);
  Init(GC);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Circ2d& C,
				       const Standard_Real p1,
				       const Standard_Real p2)
{
  Handle(Geom2d_Circle) GC = new Geom2d_Circle(C);
  Init(GC,p1,p2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Circ2d& C,
				       const gp_Pnt2d& P1,
				       const gp_Pnt2d& P2)
{
  Handle(Geom2d_Circle) GC = new Geom2d_Circle(C);
  Init(GC,P1,P2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Circ2d& C,
				       const TopoDS_Vertex& V1,
				       const TopoDS_Vertex& V2)
{
  Handle(Geom2d_Circle) GC = new Geom2d_Circle(C);
  Init(GC,V1,V2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Elips2d& E) 
{
  Handle(Geom2d_Ellipse) GE = new Geom2d_Ellipse(E);
  Init(GE);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Elips2d& E,
				       const Standard_Real p1,
				       const Standard_Real p2)
{
  Handle(Geom2d_Ellipse) GE = new Geom2d_Ellipse(E);
  Init(GE,p1,p2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Elips2d& E,
				       const gp_Pnt2d& P1,
				       const gp_Pnt2d& P2)
{
  Handle(Geom2d_Ellipse) GE = new Geom2d_Ellipse(E);
  Init(GE,P1,P2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Elips2d& E,
				       const TopoDS_Vertex& V1,
				       const TopoDS_Vertex& V2)
{
  Handle(Geom2d_Ellipse) GE = new Geom2d_Ellipse(E);
  Init(GE,V1,V2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Hypr2d& H)
{
  Handle(Geom2d_Hyperbola) GH = new Geom2d_Hyperbola(H);
  Init(GH);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Hypr2d& H,
				       const Standard_Real p1,
				       const Standard_Real p2)
{
  Handle(Geom2d_Hyperbola) GH = new Geom2d_Hyperbola(H);
  Init(GH,p1,p2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Hypr2d& H,
				       const gp_Pnt2d& P1,
				       const gp_Pnt2d& P2)
{
  Handle(Geom2d_Hyperbola) GH = new Geom2d_Hyperbola(H);
  Init(GH,P1,P2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Hypr2d& H,
				       const TopoDS_Vertex& V1,
				       const TopoDS_Vertex& V2)
{
  Handle(Geom2d_Hyperbola) GH = new Geom2d_Hyperbola(H);
  Init(GH,V1,V2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Parab2d& P)
{
  Handle(Geom2d_Parabola) GP = new Geom2d_Parabola(P);
  Init(GP);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Parab2d& P,
				       const Standard_Real p1,
				       const Standard_Real p2)
{
  Handle(Geom2d_Parabola) GP = new Geom2d_Parabola(P);
  Init(GP,p1,p2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Parab2d& P,
				       const gp_Pnt2d& P1,
				       const gp_Pnt2d& P2)
{
  Handle(Geom2d_Parabola) GP = new Geom2d_Parabola(P);
  Init(GP,P1,P2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const gp_Parab2d& P,
				       const TopoDS_Vertex& V1,
				       const TopoDS_Vertex& V2)
{
  Handle(Geom2d_Parabola) GP = new Geom2d_Parabola(P);
  Init(GP,V1,V2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const Handle(Geom2d_Curve)& L)
{
  Init(L);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const Handle(Geom2d_Curve)& L,
				       const Standard_Real p1,
				       const Standard_Real p2)
{
  Init(L,p1,p2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const Handle(Geom2d_Curve)& L,
				       const gp_Pnt2d& P1,
				       const gp_Pnt2d& P2)
{
  Init(L,P1,P2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const Handle(Geom2d_Curve)& L,
				       const TopoDS_Vertex& V1,
				       const TopoDS_Vertex& V2)
{
  Init(L,V1,V2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const Handle(Geom2d_Curve)& L,
				       const gp_Pnt2d& P1,
				       const gp_Pnt2d& P2,
				       const Standard_Real p1,
				       const Standard_Real p2)
{
  Init(L,P1,P2,p1,p2);
}

//=======================================================================
//function : BRepLib_MakeEdge2d
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::BRepLib_MakeEdge2d(const Handle(Geom2d_Curve)& L,
				       const TopoDS_Vertex& V1,
				       const TopoDS_Vertex& V2,
				       const Standard_Real p1,
				       const Standard_Real p2)
{
  Init(L,V1,V2,p1,p2);
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void  BRepLib_MakeEdge2d::Init(const Handle(Geom2d_Curve)& C)
{
  Init(C,C->FirstParameter(),C->LastParameter());
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void  BRepLib_MakeEdge2d::Init(const Handle(Geom2d_Curve)& C,
			       const Standard_Real p1,
			       const Standard_Real p2)
{
//  BRep_Builder B;

  TopoDS_Vertex V1,V2;
  Init(C,V1,V2,p1,p2);
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void  BRepLib_MakeEdge2d::Init(const Handle(Geom2d_Curve)& C,
			       const gp_Pnt2d& P1,
			       const gp_Pnt2d& P2)
{
  BRep_Builder B;
  TopoDS_Vertex V1,V2;
  B.MakeVertex(V1,Point(P1),Precision::Confusion());
  if (P1.Distance(P2) < Precision::Confusion())
    V2 = V1;
  else
    B.MakeVertex(V2,Point(P2),Precision::Confusion());
  Init(C,V1,V2);
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void  BRepLib_MakeEdge2d::Init(const Handle(Geom2d_Curve)& C,
			       const TopoDS_Vertex& V1,
			       const TopoDS_Vertex& V2)
{
  // try projecting the vertices on the curve

  Standard_Real p1,p2;
  
  if (V1.IsNull())
    p1 = C->FirstParameter();
  else
    if (!Project(C,V1,p1)) {
      myError = BRepLib_PointProjectionFailed;
      return;
    }
  if (V2.IsNull())
    p2 = C->LastParameter();
  else
    if (!Project(C,V2,p2))  {
      myError = BRepLib_PointProjectionFailed;
      return;
    }
  
  Init(C,V1,V2,p1,p2);
}


//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void  BRepLib_MakeEdge2d::Init(const Handle(Geom2d_Curve)& C,
			       const gp_Pnt2d& P1,
			       const gp_Pnt2d& P2,
			       const Standard_Real p1,
			       const Standard_Real p2)
{
  BRep_Builder B;

  TopoDS_Vertex V1,V2;
  B.MakeVertex(V1,Point(P1),Precision::Confusion());
  if (P1.Distance(P2) < Precision::Confusion())
    V2 = V1;
  else
    B.MakeVertex(V2,Point(P2),Precision::Confusion());
  
  
  Init(C,V1,V2,p1,p2);
}


//=======================================================================
//function : Init
//purpose  : this one really makes the job ...
//=======================================================================

void  BRepLib_MakeEdge2d::Init(const Handle(Geom2d_Curve)& CC,
			       const TopoDS_Vertex& VV1,
			       const TopoDS_Vertex& VV2,
			       const Standard_Real pp1,
			       const Standard_Real pp2)
{
  // kill trimmed curves
  Handle(Geom2d_Curve) C = CC;
  Handle(Geom2d_TrimmedCurve) CT = Handle(Geom2d_TrimmedCurve)::DownCast(C);
  while (!CT.IsNull()) {
    C = CT->BasisCurve();
    CT = Handle(Geom2d_TrimmedCurve)::DownCast(C);
  }

  // check parameters
  Standard_Real p1 = pp1;
  Standard_Real p2 = pp2;
  Standard_Real cf = C->FirstParameter();
  Standard_Real cl = C->LastParameter();
  Standard_Real epsilon = Precision::Confusion();
  Standard_Boolean periodic = C->IsPeriodic();


  TopoDS_Vertex V1,V2;
  if (periodic) {
    // adjust in period
    ElCLib::AdjustPeriodic(cf,cl,epsilon,p1,p2);
    V1 = VV1;
    V2 = VV2;
  }
  else {
    // reordonate
    if (p1 < p2) {
      V1 = VV1;
      V2 = VV2;
    }
    else {
      V2 = VV1;
      V1 = VV2;
      Standard_Real x = p1;
      p1 = p2;
      p2 = x;
    }

    // check range
    if ((cf - p1 > epsilon) || (p2 - cl > epsilon)) {
      myError = BRepLib_ParameterOutOfRange;
      return;
    }
  }
  
  // compute points on the curve
  Standard_Boolean p1inf = Precision::IsNegativeInfinite(p1);
  Standard_Boolean p2inf = Precision::IsPositiveInfinite(p2);
  gp_Pnt2d P1,P2;
  if (!p1inf) P1 = C->Value(p1);
  if (!p2inf) P2 = C->Value(p2);

  Standard_Real preci = Precision::Confusion();
  BRep_Builder B;

  // check for closed curve
  Standard_Boolean closed = Standard_False;
  if (!p1inf && !p2inf)
    closed = (P1.Distance(P2) <= preci);

  // check if the vertices are on the curve
  if (closed) {
    if (V1.IsNull() && V2.IsNull()) {
      B.MakeVertex(V1,Point(P1),preci);
      V2 = V1;
    }
    else if (V1.IsNull())
      V1 = V2;
    else if (V2.IsNull())
      V2 = V1;
    else {
      if (!V1.IsSame(V2)) {
	myError = BRepLib_DifferentPointsOnClosedCurve;
	return;
      }
      else if (Point(P1).Distance(BRep_Tool::Pnt(V1)) > preci) {
	myError = BRepLib_DifferentPointsOnClosedCurve;
	return;
      }
    }
  }

  else {    // not closed

    if (p1inf) {
      if (!V1.IsNull()) {
	myError = BRepLib_PointWithInfiniteParameter;
	return;
      }
    }
    else {
      gp_Pnt P = Point(P1);
      if (V1.IsNull()) {
	B.MakeVertex(V1,P,preci);
      }
#if 0
      // desctivate control (RLE) for speed in sketcher
        else if (P.Distance(BRep_Tool::Pnt(V1)) > preci) {
	myError = BRepLib_DifferentsPointAndParameter;
	return;
      }
#endif
    }
    
    if (p2inf) {
      if (!V2.IsNull()) {
	myError = BRepLib_PointWithInfiniteParameter;
	return;
      }
    }
    else {
      gp_Pnt P = Point(P2);
      if (V2.IsNull()) {
	B.MakeVertex(V2,P,preci);
      }
#if 0
      // desctivate control (RLE) for speed in sketcher
        else if (P.Distance(BRep_Tool::Pnt(V2)) > preci){
	myError = BRepLib_DifferentsPointAndParameter;
	return;
      }
#endif
    }
  }

  V1.Orientation(TopAbs_FORWARD);
  V2.Orientation(TopAbs_REVERSED);
  myVertex1 = V1;
  myVertex2 = V2;

  TopoDS_Edge& E = TopoDS::Edge(myShape);
  B.MakeEdge(E);
  B.UpdateEdge(E,C,BRepLib::Plane(),TopLoc_Location(),preci);
  if (!V1.IsNull()) {
    B.Add(E,V1);
  }
  if (!V2.IsNull()) {
    B.Add(E,V2);
  }
  B.Range(E,p1,p2);
  Done();
}

//=======================================================================
//function : Error
//purpose  : 
//=======================================================================

BRepLib_EdgeError BRepLib_MakeEdge2d::Error() const
{
  return myError;
}

//=======================================================================
//function : Edge
//purpose  : 
//=======================================================================

const TopoDS_Edge&  BRepLib_MakeEdge2d::Edge()const 
{
  return TopoDS::Edge(Shape());
}


//=======================================================================
//function : Vertex1
//purpose  : 
//=======================================================================

const TopoDS_Vertex&  BRepLib_MakeEdge2d::Vertex1()const 
{
  Check();
  return myVertex1;
}


//=======================================================================
//function : Vertex2
//purpose  : 
//=======================================================================

const TopoDS_Vertex&  BRepLib_MakeEdge2d::Vertex2()const 
{
  Check();
  return myVertex2;
}



//=======================================================================
//function : operator
//purpose  : 
//=======================================================================

BRepLib_MakeEdge2d::operator TopoDS_Edge() const
{
  return Edge();
}
