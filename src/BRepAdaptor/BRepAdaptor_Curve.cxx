// Created on: 1993-02-19
// Created by: Remi LEQUETTE
// Copyright (c) 1993-1999 Matra Datavision
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



#include <BRepAdaptor_Curve.ixx>

#include <BRepAdaptor_HCurve.hxx>
#include <BRep_Tool.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom_Surface.hxx>
#include <Geom2dAdaptor_HCurve.hxx>
#include <GeomAdaptor_HSurface.hxx>

//=======================================================================
//function : BRepAdaptor_Curve
//purpose  : 
//=======================================================================

BRepAdaptor_Curve::BRepAdaptor_Curve()
{}

//=======================================================================
//function : BRepAdaptor_Curve
//purpose  : 
//=======================================================================

BRepAdaptor_Curve::BRepAdaptor_Curve(const TopoDS_Edge& E)
{
  Initialize(E);
}

//=======================================================================
//function : BRepAdaptor_Curve
//purpose  : 
//=======================================================================

BRepAdaptor_Curve::BRepAdaptor_Curve(const TopoDS_Edge& E,
				     const TopoDS_Face& F)
{
  Initialize(E,F);
}

//=======================================================================
//function : Initialize
//purpose  : 
//=======================================================================

void BRepAdaptor_Curve::Initialize(const TopoDS_Edge& E)
{
  myConSurf.Nullify();
  myEdge = E;
  Standard_Real pf,pl;

  TopLoc_Location L;
  Handle(Geom_Curve) C = BRep_Tool::Curve(E,L,pf,pl);

  if (!C.IsNull()) {
    myCurve.Load(C,pf,pl);
  }
  else {
    Handle(Geom2d_Curve) PC;
    Handle(Geom_Surface) S;
    BRep_Tool::CurveOnSurface(E,PC,S,L,pf,pl);
    if (!PC.IsNull()) {
      Handle(GeomAdaptor_HSurface) HS = new GeomAdaptor_HSurface();
      HS->ChangeSurface().Load(S);
      Handle(Geom2dAdaptor_HCurve) HC = new Geom2dAdaptor_HCurve();
      HC->ChangeCurve2d().Load(PC,pf,pl);
      myConSurf = new Adaptor3d_HCurveOnSurface();
      myConSurf->ChangeCurve().Load(HC);
      myConSurf->ChangeCurve().Load(HS);
    }
    else {
      Standard_NullObject::Raise("BRepAdaptor_Curve::No geometry");
    }
  }
  myTrsf = L.Transformation();
}

//=======================================================================
//function : Initialize
//purpose  : 
//=======================================================================

void BRepAdaptor_Curve::Initialize(const TopoDS_Edge& E,
				   const TopoDS_Face& F)
{
  myConSurf.Nullify();

  myEdge = E;
  TopLoc_Location L;
  Standard_Real pf,pl;
  Handle(Geom_Surface) S = BRep_Tool::Surface(F,L);
  Handle(Geom2d_Curve) PC = BRep_Tool::CurveOnSurface(E,F,pf,pl); 

  Handle(GeomAdaptor_HSurface) HS = new GeomAdaptor_HSurface();
  HS->ChangeSurface().Load(S);
  Handle(Geom2dAdaptor_HCurve) HC = new Geom2dAdaptor_HCurve();
  HC->ChangeCurve2d().Load(PC,pf,pl);
  myConSurf = new Adaptor3d_HCurveOnSurface();
  myConSurf->ChangeCurve().Load(HC);
  myConSurf->ChangeCurve().Load(HS);
  
  myTrsf = L.Transformation();
}

//=======================================================================
//function : Trsf
//purpose  : 
//=======================================================================

const gp_Trsf& BRepAdaptor_Curve::Trsf() const
{
  return myTrsf;
}

//=======================================================================
//function : Is3DCurve
//purpose  : 
//=======================================================================

Standard_Boolean BRepAdaptor_Curve::Is3DCurve() const
{
  return myConSurf.IsNull();
}

//=======================================================================
//function : IsCurveOnSurface
//purpose  : 
//=======================================================================

Standard_Boolean BRepAdaptor_Curve::IsCurveOnSurface() const
{
  return !myConSurf.IsNull();
}

//=======================================================================
//function : Curve
//purpose  : 
//=======================================================================

const GeomAdaptor_Curve& BRepAdaptor_Curve::Curve() const
{
  return myCurve;
}

//=======================================================================
//function : CurveOnSurface
//purpose  : 
//=======================================================================

const Adaptor3d_CurveOnSurface& BRepAdaptor_Curve::CurveOnSurface() const
{
  return *((Adaptor3d_CurveOnSurface*)&(myConSurf->Curve()));
}

//=======================================================================
//function : Edge
//purpose  : 
//=======================================================================

const TopoDS_Edge& BRepAdaptor_Curve::Edge() const
{
  return myEdge;
}

//=======================================================================
//function : Tolerance
//purpose  : 
//=======================================================================

Standard_Real BRepAdaptor_Curve::Tolerance() const
{
  return BRep_Tool::Tolerance(myEdge);
}

//=======================================================================
//function : FirstParameter
//purpose  : 
//=======================================================================

Standard_Real BRepAdaptor_Curve::FirstParameter() const 
{
  if (myConSurf.IsNull()) {
    return myCurve.FirstParameter();
  }
  else {
    return myConSurf->FirstParameter();
  }
}

//=======================================================================
//function : LastParameter
//purpose  : 
//=======================================================================

Standard_Real BRepAdaptor_Curve::LastParameter() const 
{
  if (myConSurf.IsNull()) {
    return myCurve.LastParameter();
  }
  else {
    return myConSurf->LastParameter();
  }
}

//=======================================================================
//function : Continuity
//purpose  : 
//=======================================================================

GeomAbs_Shape BRepAdaptor_Curve::Continuity() const 
{
  if (myConSurf.IsNull()) {
    return myCurve.Continuity();
  }
  else {
    return myConSurf->Continuity();
  }
}

//=======================================================================
//function : NbIntervals
//purpose  : 
//=======================================================================

Standard_Integer BRepAdaptor_Curve::NbIntervals(const GeomAbs_Shape S) 
{
  if (myConSurf.IsNull()) {
    return myCurve.NbIntervals(S);
  }
  else {
    return myConSurf->NbIntervals(S);
  }
}

//=======================================================================
//function : Intervals
//purpose  : 
//=======================================================================

void BRepAdaptor_Curve::Intervals(TColStd_Array1OfReal& T, 
				  const GeomAbs_Shape S)  
{
  if (myConSurf.IsNull()) {
    myCurve.Intervals(T, S);
  }
  else {
    myConSurf->Intervals(T, S);
  }
}


//=======================================================================
//function : Trim
//purpose  : 
//=======================================================================

Handle(Adaptor3d_HCurve) BRepAdaptor_Curve::Trim(const Standard_Real First, 
					       const Standard_Real Last, 
					       const Standard_Real Tol) const 
{
  // On fait une copie de this pour garder la trsf.
  Handle(BRepAdaptor_HCurve) res = new BRepAdaptor_HCurve();
  if (myConSurf.IsNull()){
    Standard_Real pf = FirstParameter(), pl = LastParameter();
    Handle(Geom_Curve) C = myCurve.Curve();
    ((GeomAdaptor_Curve*) (void*) &myCurve)->Load(C,First,Last);
    res->ChangeCurve() = *this;
    ((GeomAdaptor_Curve*) (void*) &myCurve)->Load(C,pf,pl);
  }
  else {
    Handle(Adaptor3d_HCurveOnSurface) sav = myConSurf;
    *((Handle_Adaptor3d_HCurveOnSurface*) (void*) &myConSurf) = 
      Handle(Adaptor3d_HCurveOnSurface)::DownCast(myConSurf->Trim(First,Last,Tol));
    res->ChangeCurve() = *this;
    *((Handle_Adaptor3d_HCurveOnSurface*) (void*) &myConSurf) = sav;
  }
  return res;
}


//=======================================================================
//function : IsClosed
//purpose  : 
//=======================================================================

Standard_Boolean BRepAdaptor_Curve::IsClosed() const 
{
  if (myConSurf.IsNull()) {
    return myCurve.IsClosed();
  }
  else {
    return myConSurf->IsClosed();
  }
}

//=======================================================================
//function : IsPeriodic
//purpose  : 
//=======================================================================

Standard_Boolean BRepAdaptor_Curve::IsPeriodic() const 
{
  if (myConSurf.IsNull()) {
    return myCurve.IsPeriodic();
  }
  else {
    return myConSurf->IsPeriodic();
  }
}

//=======================================================================
//function : Period
//purpose  : 
//=======================================================================

Standard_Real BRepAdaptor_Curve::Period() const 
{
  if (myConSurf.IsNull()) {
    return myCurve.Period();
  }
  else {
    return myConSurf->Period();
  }
}

//=======================================================================
//function : Value
//purpose  : 
//=======================================================================

gp_Pnt BRepAdaptor_Curve::Value(const Standard_Real U) const
{
  gp_Pnt P;
  if (myConSurf.IsNull())
    P = myCurve.Value(U);
  else
    P = myConSurf->Value(U);
  P.Transform(myTrsf);
  return P;
}

//=======================================================================
//function : D0
//purpose  : 
//=======================================================================

void BRepAdaptor_Curve::D0(const Standard_Real U, gp_Pnt& P) const
{
  if (myConSurf.IsNull())
    myCurve.D0(U,P);
  else
    myConSurf->D0(U,P);
  P.Transform(myTrsf);
}

//=======================================================================
//function : D1
//purpose  : 
//=======================================================================

void BRepAdaptor_Curve::D1(const Standard_Real U,
			   gp_Pnt& P, gp_Vec& V) const
{
  if (myConSurf.IsNull())
    myCurve.D1(U,P,V);
  else
    myConSurf->D1(U,P,V);
  P.Transform(myTrsf);
  V.Transform(myTrsf);
}

//=======================================================================
//function : D2
//purpose  : 
//=======================================================================

void BRepAdaptor_Curve::D2(const Standard_Real U,
			   gp_Pnt& P, gp_Vec& V1, gp_Vec& V2) const
{
  if (myConSurf.IsNull())
    myCurve.D2(U,P,V1,V2);
  else
    myConSurf->D2(U,P,V1,V2);
  P.Transform(myTrsf);
  V1.Transform(myTrsf);
  V2.Transform(myTrsf);
}

//=======================================================================
//function : D3
//purpose  : 
//=======================================================================

void BRepAdaptor_Curve::D3(const Standard_Real U,
			   gp_Pnt& P, 
			   gp_Vec& V1, gp_Vec& V2, gp_Vec& V3) const
{
  if (myConSurf.IsNull())
    myCurve.D3(U,P,V1,V2,V3);
  else
    myConSurf->D3(U,P,V1,V2,V3);
  P.Transform(myTrsf);
  V1.Transform(myTrsf);
  V2.Transform(myTrsf);
  V3.Transform(myTrsf);
}

//=======================================================================
//function : DN
//purpose  : 
//=======================================================================

gp_Vec BRepAdaptor_Curve::DN(const Standard_Real U,
			     const Standard_Integer N) const
{
  gp_Vec V;
  if (myConSurf.IsNull())
    V = myCurve.DN(U,N);
  else
    V = myConSurf->DN(U,N);
  V.Transform(myTrsf);
  return V;
}

//=======================================================================
//function : Resolution
//purpose  : 
//=======================================================================

Standard_Real BRepAdaptor_Curve::Resolution(const Standard_Real R) const 
{
  if (myConSurf.IsNull()) {
    return myCurve.Resolution(R);
  }
  else {
    return myConSurf->Resolution(R);
  }
}

//=======================================================================
//function : GetTYpe
//purpose  : 
//=======================================================================

GeomAbs_CurveType BRepAdaptor_Curve::GetType() const 
{
  if (myConSurf.IsNull()) {
    return myCurve.GetType();
  }
  else {
    return myConSurf->GetType();
  }
}

//=======================================================================
//function : Line
//purpose  : 
//=======================================================================

gp_Lin BRepAdaptor_Curve::Line() const
{
  gp_Lin L;
  if (myConSurf.IsNull())
    L = myCurve.Line();
  else
    L = myConSurf->Line();
  L.Transform(myTrsf);
  return L;
}

//=======================================================================
//function : Circle
//purpose  : 
//=======================================================================

gp_Circ BRepAdaptor_Curve::Circle() const
{
  gp_Circ C;
  if (myConSurf.IsNull())
    C = myCurve.Circle();
  else
    C = myConSurf->Circle();
  C.Transform(myTrsf);
  return C;
}

//=======================================================================
//function : Ellipse
//purpose  : 
//=======================================================================

gp_Elips BRepAdaptor_Curve::Ellipse() const
{
  gp_Elips E;
  if (myConSurf.IsNull())
    E = myCurve.Ellipse();
  else
    E = myConSurf->Ellipse();
  E.Transform(myTrsf);
  return E;
}

//=======================================================================
//function : Hyperbola
//purpose  : 
//=======================================================================

gp_Hypr BRepAdaptor_Curve::Hyperbola() const
{
  gp_Hypr H;
  if (myConSurf.IsNull())
    H = myCurve.Hyperbola();
  else
    H = myConSurf->Hyperbola();
  H.Transform(myTrsf);
  return H;
}

//=======================================================================
//function : Parabola
//purpose  : 
//=======================================================================

gp_Parab BRepAdaptor_Curve::Parabola() const
{
  gp_Parab P;
  if (myConSurf.IsNull())
    P = myCurve.Parabola();
  else
    P = myConSurf->Parabola();
  P.Transform(myTrsf);
  return P;
}

//=======================================================================
//function : Degree
//purpose  : 
//=======================================================================

Standard_Integer BRepAdaptor_Curve::Degree() const
{
  if (myConSurf.IsNull())
    return myCurve.Degree();
  else
    return myConSurf->Degree();
}

//=======================================================================
//function : IsRational
//purpose  : 
//=======================================================================

Standard_Boolean BRepAdaptor_Curve::IsRational() const
{
  if (myConSurf.IsNull())
    return myCurve.IsRational();
  else
    return myConSurf->IsRational();
}
//=======================================================================
//function : NbPoles
//purpose  : 
//=======================================================================

Standard_Integer BRepAdaptor_Curve::NbPoles() const
{
  if (myConSurf.IsNull()) 
    return myCurve.NbPoles();
  else
    return myConSurf->NbPoles();
}
//=======================================================================
//function : NbKnots
//purpose  : 
//=======================================================================

Standard_Integer BRepAdaptor_Curve::NbKnots() const
{
  if (myConSurf.IsNull()) 
    return myCurve.NbKnots();
  else
    return myConSurf->NbKnots();
}

//=======================================================================
//function : Bezier
//purpose  : 
//=======================================================================

Handle(Geom_BezierCurve) BRepAdaptor_Curve::Bezier() const 
{
  Handle(Geom_BezierCurve) BC;
  if (myConSurf.IsNull()) {
    BC = myCurve.Bezier();
  }
  else {
    BC = myConSurf->Bezier();
  }
  return Handle(Geom_BezierCurve)::DownCast(BC->Transformed(myTrsf));
}


//=======================================================================
//function : BSpline
//purpose  : 
//=======================================================================

Handle(Geom_BSplineCurve) BRepAdaptor_Curve::BSpline() const 
{
  Handle(Geom_BSplineCurve) BS;
  if (myConSurf.IsNull()) {
    BS = myCurve.BSpline();
  }
  else {
    BS = myConSurf->BSpline();
  }
  return Handle(Geom_BSplineCurve)::DownCast(BS->Transformed(myTrsf));
}
