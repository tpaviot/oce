// Created on: 1997-01-10
// Created by: Bruno DUMORTIER
// Copyright (c) 1997-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <BiTgte_CurveOnEdge.ixx>

#include <BiTgte_HCurveOnEdge.hxx>
#include <BRep_Tool.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <Standard_NotImplemented.hxx>
#include <Precision.hxx>


//=======================================================================
//function : BiTgte_CurveOnEdge
//purpose  : 
//======================================================================

BiTgte_CurveOnEdge::BiTgte_CurveOnEdge()
: myType(GeomAbs_OtherCurve)
{
}


//=======================================================================
//function : BiTgte_CurveOnEdge
//purpose  : 
//=======================================================================

BiTgte_CurveOnEdge::BiTgte_CurveOnEdge(const TopoDS_Edge& theEonF,
                                       const TopoDS_Edge& theEdge)
: myEdge(theEdge),
  myEonF(theEonF),
  myType(GeomAbs_OtherCurve)
{
  Init(theEonF, theEdge);
}


//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void BiTgte_CurveOnEdge::Init(const TopoDS_Edge& EonF,
                              const TopoDS_Edge& Edge)
{
  Standard_Real f,l;

  myEdge = Edge;
  myCurv = BRep_Tool::Curve(myEdge,f,l);
  myCurv = new Geom_TrimmedCurve(myCurv,f,l);

  myEonF = EonF;
  myConF = BRep_Tool::Curve(myEonF,f,l);
  myConF = new Geom_TrimmedCurve(myConF,f,l);

  // peut on generer un cercle de rayon nul
  GeomAdaptor_Curve Curv(myCurv);
  GeomAdaptor_Curve ConF(myConF);
  
  myType = GeomAbs_OtherCurve;
  if (Curv.GetType() == GeomAbs_Line && 
      ConF.GetType() == GeomAbs_Circle ) {
    gp_Ax1 a1 = Curv.Line().Position();
    gp_Ax1 a2 = ConF.Circle().Axis();
    if ( a1.IsCoaxial(a2,Precision::Angular(),Precision::Confusion())) {
      myType = GeomAbs_Circle;
      myCirc = gp_Circ(ConF.Circle().Position(),0.);
    }
  }
}


//=======================================================================
//function : FirstParameter
//purpose  : 
//=======================================================================

Standard_Real BiTgte_CurveOnEdge::FirstParameter() const
{
  return myConF->FirstParameter();
}


//=======================================================================
//function : LastParameter
//purpose  : 
//=======================================================================

Standard_Real BiTgte_CurveOnEdge::LastParameter() const
{
  return myConF->LastParameter();
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

GeomAbs_Shape BiTgte_CurveOnEdge::Continuity() const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
  return GeomAbs_C0;
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

Standard_Integer BiTgte_CurveOnEdge::NbIntervals(const GeomAbs_Shape) const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
  return 0;
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

void BiTgte_CurveOnEdge::Intervals(TColStd_Array1OfReal&,
                                   const GeomAbs_Shape) const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

Handle(Adaptor3d_HCurve) BiTgte_CurveOnEdge::Trim(const Standard_Real,
                                                  const Standard_Real,
                                                  const Standard_Real) const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
  Handle(BiTgte_HCurveOnEdge) HC;
  return HC;
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

Standard_Boolean BiTgte_CurveOnEdge::IsClosed() const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
  return Standard_False;
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

Standard_Boolean BiTgte_CurveOnEdge::IsPeriodic() const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
  return Standard_False;
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

Standard_Real BiTgte_CurveOnEdge::Period() const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
  return 0.;
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

gp_Pnt BiTgte_CurveOnEdge::Value(const Standard_Real U) const
{
  gp_Pnt P;
  D0(U,P);
  return P;
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

void BiTgte_CurveOnEdge::D0(const Standard_Real U,gp_Pnt& P) const
{
  GeomAPI_ProjectPointOnCurve Projector;
  P = myConF->Value(U);
  Projector.Init(P, myCurv);
  P = Projector.NearestPoint();
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

void BiTgte_CurveOnEdge::D1(const Standard_Real,gp_Pnt& ,gp_Vec& ) const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

void BiTgte_CurveOnEdge::D2(const Standard_Real ,gp_Pnt&,
                            gp_Vec& ,gp_Vec&) const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

void BiTgte_CurveOnEdge::D3(const Standard_Real ,gp_Pnt&,
                            gp_Vec& ,gp_Vec& ,gp_Vec& ) const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

gp_Vec BiTgte_CurveOnEdge::DN(const Standard_Real,
                              const Standard_Integer) const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
  return gp_Vec();
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

Standard_Real BiTgte_CurveOnEdge::Resolution(const Standard_Real) const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
  return 0.;
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

GeomAbs_CurveType BiTgte_CurveOnEdge::GetType() const
{
  return myType;
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

gp_Lin BiTgte_CurveOnEdge::Line() const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
  return gp_Lin();
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

gp_Circ BiTgte_CurveOnEdge::Circle() const
{
  if ( myType != GeomAbs_Circle) {
    Standard_NoSuchObject::Raise("BiTgte_CurveOnEdge::Circle");
    return gp_Circ();
  }

  return myCirc;
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

gp_Elips BiTgte_CurveOnEdge::Ellipse() const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
  return gp_Elips();
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

gp_Hypr BiTgte_CurveOnEdge::Hyperbola() const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
  return gp_Hypr();
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

gp_Parab BiTgte_CurveOnEdge::Parabola() const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
  return gp_Parab();
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

Standard_Integer BiTgte_CurveOnEdge::Degree() const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
  return 0;
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

Standard_Boolean BiTgte_CurveOnEdge::IsRational() const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
  return Standard_False;
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

Standard_Integer BiTgte_CurveOnEdge::NbPoles() const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
  return 0;
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

Standard_Integer BiTgte_CurveOnEdge::NbKnots() const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
  return 0;
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

Handle(Geom_BezierCurve) BiTgte_CurveOnEdge::Bezier() const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
  Handle(Geom_BezierCurve) B;
  return B;
}


//=======================================================================
//function : 
//purpose  : 
//=======================================================================

Handle(Geom_BSplineCurve) BiTgte_CurveOnEdge::BSpline() const
{
  Standard_NotImplemented::Raise("BiTgte_CurveOnEdge");
  Handle(Geom_BSplineCurve) B;
  return B;
}


