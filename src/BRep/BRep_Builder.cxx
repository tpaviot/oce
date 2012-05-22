// Created on: 1991-07-02
// Created by: Remi LEQUETTE
// Copyright (c) 1991-1999 Matra Datavision
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


#include <BRep_Builder.ixx>

#include <BRep_TEdge.hxx>
#include <BRep_Curve3D.hxx>
#include <BRep_GCurve.hxx>
#include <BRep_CurveOnClosedSurface.hxx>
#include <BRep_CurveOn2Surfaces.hxx>
#include <BRep_ListIteratorOfListOfCurveRepresentation.hxx>

#include <BRep_PointOnCurve.hxx>
#include <BRep_PointOnCurveOnSurface.hxx>
#include <BRep_PointOnSurface.hxx>
#include <BRep_ListIteratorOfListOfPointRepresentation.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Iterator.hxx>

#include <Precision.hxx>

#include <BRep_Polygon3D.hxx>
#include <BRep_PolygonOnSurface.hxx>
#include <BRep_PolygonOnClosedSurface.hxx>
#include <BRep_PolygonOnTriangulation.hxx>
#include <BRep_PolygonOnClosedTriangulation.hxx>

#include <Standard_NullObject.hxx>

//=======================================================================
//function : Auxiliary methods
//purpose  : 
//=======================================================================

//=======================================================================
//function : UpdateCurves
//purpose  : Insert a 3d curve <C> with location <L> 
//           in a list of curve representations <lcr>
//=======================================================================

static void UpdateCurves(BRep_ListOfCurveRepresentation& lcr,
                         const Handle(Geom_Curve)&       C,
                         const TopLoc_Location&          L)
{
  BRep_ListIteratorOfListOfCurveRepresentation itcr(lcr);
  Handle(BRep_GCurve) GC;
  Standard_Real f = 0,l = 0;

  while (itcr.More()) {
    GC = Handle(BRep_GCurve)::DownCast(itcr.Value());
    if (!GC.IsNull()) {
      GC->Range(f, l);
      if (GC->IsCurve3D()) break;

    }
    itcr.Next();
  }

  if (itcr.More()) {
    itcr.Value()->Curve3D(C);
    itcr.Value()->Location(L);
  }
  else {
    Handle(BRep_Curve3D) C3d = new BRep_Curve3D(C,L);
    // test if there is already a range
    if (!GC.IsNull()) {
      C3d->SetRange(f,l);
    }
    lcr.Append(C3d);
  }
  
}

//=======================================================================
//function : UpdateCurves
//purpose  : Insert a pcurve <C> on surface <S> with location <L> 
//           in a list of curve representations <lcr>
//           Remove the pcurve on <S> from <lcr> if <C> is null
//=======================================================================

static void UpdateCurves(BRep_ListOfCurveRepresentation& lcr,
                         const Handle(Geom2d_Curve)& C,
                         const Handle(Geom_Surface)& S,
                         const TopLoc_Location& L)
{
  BRep_ListIteratorOfListOfCurveRepresentation itcr(lcr);
  Handle(BRep_CurveRepresentation) cr;
  Handle(BRep_GCurve) GC;
  Standard_Real f = 0,l = 0;
  Standard_Boolean rangeFound = Standard_False;

  // search the range of the 3d curve
  // and remove any existing representation

  while (itcr.More()) {
    GC = Handle(BRep_GCurve)::DownCast(itcr.Value());
    if (!GC.IsNull()) {
      if (GC->IsCurve3D()) {
        // xpu151298 : parameters can be setted for null curves
        //             see lbo & flo, to determine whether range is defined
        //             compare first and last parameters with default values.
        GC->Range(f, l);
        //lvt 15/6/99: On enleve la comparaison de reels infinis.
        Standard_Boolean undefined = (Precision::IsPositiveInfinite(l) ||
                                      Precision::IsNegativeInfinite(f));
        
        if (!undefined) {
          rangeFound = Standard_True;
        }
      }
      if (GC->IsCurveOnSurface(S,L)) {
        // remove existing curve on surface
        // cr is used to keep a reference on the curve representation
        // this avoid deleting it as its content may be referenced by C or S
        cr = itcr.Value();
        lcr.Remove(itcr);
      }
      else {
        itcr.Next();
      }
    }
    else {
      itcr.Next();
    }
  }

  if (! C.IsNull()) {
    Handle(BRep_CurveOnSurface) COS = new BRep_CurveOnSurface(C,S,L);
    // test if there is already a range
    if (rangeFound) {
      COS->SetRange(f,l);
    }
    lcr.Append(COS);
  }
}

//=======================================================================
//function : UpdateCurves
//purpose  : Insert a pcurve <C> on surface <S> with location <L> 
//           in a list of curve representations <lcr>
//           Remove the pcurve on <S> from <lcr> if <C> is null
//=======================================================================
static void UpdateCurves(BRep_ListOfCurveRepresentation& lcr,
                         const Handle(Geom2d_Curve)& C,
                         const Handle(Geom_Surface)& S,
                         const TopLoc_Location& L,
                         const gp_Pnt2d& Pf,
                         const gp_Pnt2d& Pl)
{
  BRep_ListIteratorOfListOfCurveRepresentation itcr(lcr);
  Handle(BRep_CurveRepresentation) cr;
  Handle(BRep_GCurve) GC;
  Standard_Real f = 0,l = 0;
  Standard_Boolean rangeFound = Standard_False;

  // search the range of the 3d curve
  // and remove any existing representation

  while (itcr.More()) {
    GC = Handle(BRep_GCurve)::DownCast(itcr.Value());
    if (!GC.IsNull()) {
      if (GC->IsCurve3D()) {
        // xpu151298 : parameters can be setted for null curves
        //             see lbo & flo, to determine whether range is defined
        //             compare first and last parameters with default values.
        GC->Range(f, l);
        //lvt 15/6/99: On enleve la comparaison de reels infinis.
        Standard_Boolean undefined = (Precision::IsPositiveInfinite(l) ||
                                      Precision::IsNegativeInfinite(f));
        
        if (!undefined) {
          rangeFound = Standard_True;
        }
      }
      if (GC->IsCurveOnSurface(S,L)) {
        // remove existing curve on surface
        // cr is used to keep a reference on the curve representation
        // this avoid deleting it as its content may be referenced by C or S
        cr = itcr.Value();
        lcr.Remove(itcr);
      }
      else {
        itcr.Next();
      }
    }
    else {
      itcr.Next();
    }
  }

  if (! C.IsNull()) {
    Handle(BRep_CurveOnSurface) COS = new BRep_CurveOnSurface(C,S,L);
    // test if there is already a range
    if (rangeFound) {
      COS->SetRange(f,l);
    }
    COS->SetUVPoints(Pf,Pl);
    lcr.Append(COS);
  }
}

//=======================================================================
//function : UpdateCurves
//purpose  : Insert two pcurves <C1,C2> on surface <S> with location <L> 
//           in a list of curve representations <lcr>
//           Remove the pcurves on <S> from <lcr> if <C1> or <C2> is null
//=======================================================================

static void UpdateCurves(BRep_ListOfCurveRepresentation& lcr,
                         const Handle(Geom2d_Curve)& C1,
                         const Handle(Geom2d_Curve)& C2,
                         const Handle(Geom_Surface)& S,
                         const TopLoc_Location& L)
{
  BRep_ListIteratorOfListOfCurveRepresentation itcr(lcr);
  Handle(BRep_CurveRepresentation) cr;
  Handle(BRep_GCurve) GC;
  Standard_Real f = 0,l = 0;

  while (itcr.More()) {
    GC = Handle(BRep_GCurve)::DownCast(itcr.Value());
    if ( !GC.IsNull() ) {
      GC->Range(f,l);
      Standard_Boolean iscos = GC->IsCurveOnSurface(S,L);
      if (iscos) break;
    }
    itcr.Next();
  }

  if (itcr.More())  {
    // cr is used to keep a reference on the curve representation
    // this avoid deleting it as its content may be referenced by C or S
    cr = itcr.Value();
    lcr.Remove(itcr);
  }

  if ( !C1.IsNull() && !C2.IsNull() ) {
    Handle(BRep_CurveOnClosedSurface) COS =
      new BRep_CurveOnClosedSurface(C1,C2,S,L,GeomAbs_C0);
    // test if there is already a range
    if (!GC.IsNull()) {
      COS->SetRange(f,l);
    }
    lcr.Append(COS);
  }
}

//=======================================================================
//function : UpdateCurves
//purpose  : Insert two pcurves <C1,C2> on surface <S> with location <L> 
//           in a list of curve representations <lcr>
//           Remove the pcurves on <S> from <lcr> if <C1> or <C2> is null
//=======================================================================
static void UpdateCurves(BRep_ListOfCurveRepresentation& lcr,
                         const Handle(Geom2d_Curve)& C1,
                         const Handle(Geom2d_Curve)& C2,
                         const Handle(Geom_Surface)& S,
                         const TopLoc_Location& L,
                         const gp_Pnt2d& Pf,
                         const gp_Pnt2d& Pl)
{
  BRep_ListIteratorOfListOfCurveRepresentation itcr(lcr);
  Handle(BRep_CurveRepresentation) cr;
  Handle(BRep_GCurve) GC;
  Standard_Real f = 0,l = 0;

  while (itcr.More()) {
    GC = Handle(BRep_GCurve)::DownCast(itcr.Value());
    if ( !GC.IsNull() ) {
      GC->Range(f,l);
      Standard_Boolean iscos = GC->IsCurveOnSurface(S,L);
      if (iscos) break;
    }
    itcr.Next();
  }

  if (itcr.More())  {
    // cr is used to keep a reference on the curve representation
    // this avoid deleting it as its content may be referenced by C or S
    cr = itcr.Value();
    lcr.Remove(itcr);
  }

  if ( !C1.IsNull() && !C2.IsNull() ) {
    Handle(BRep_CurveOnClosedSurface) COS =
      new BRep_CurveOnClosedSurface(C1,C2,S,L,GeomAbs_C0);
    // test if there is already a range
    if (!GC.IsNull()) {
      COS->SetRange(f,l);
    }
    COS->SetUVPoints2(Pf,Pl);
    lcr.Append(COS);
  }
}


static void UpdateCurves(BRep_ListOfCurveRepresentation& lcr,
                         const Handle(Geom_Surface)& S1,
                         const Handle(Geom_Surface)& S2,
                         const TopLoc_Location& L1,
                         const TopLoc_Location& L2,
                         const GeomAbs_Shape C)
{
  BRep_ListIteratorOfListOfCurveRepresentation itcr(lcr);
  while (itcr.More()) {
    const Handle(BRep_CurveRepresentation)& cr = itcr.Value();
    Standard_Boolean isregu = cr->IsRegularity(S1,S2,L1,L2);
    if (isregu) break;
    itcr.Next();
  }
  
  if (itcr.More()) {
    Handle(BRep_CurveRepresentation)& cr = itcr.Value();
    cr->Continuity(C);
  }
  else {
    Handle(BRep_CurveOn2Surfaces) COS = new BRep_CurveOn2Surfaces
      (S1,S2,L1,L2,C);
    lcr.Append(COS);
  }
}

static void UpdatePoints(BRep_ListOfPointRepresentation& lpr,
                         Standard_Real p,
                         const Handle(Geom_Curve)& C,
                         const TopLoc_Location& L)
{
  BRep_ListIteratorOfListOfPointRepresentation itpr(lpr);
  while (itpr.More()) {
    const Handle(BRep_PointRepresentation)& pr = itpr.Value();
    Standard_Boolean isponc = pr->IsPointOnCurve(C,L);
    if (isponc) break;
    itpr.Next();
  }

  if (itpr.More()) {
    Handle(BRep_PointRepresentation)& pr = itpr.Value();
    pr->Parameter(p);
  }
  else {
    Handle(BRep_PointOnCurve) POC = new BRep_PointOnCurve(p,C,L);
    lpr.Append(POC);
  }
}

static void UpdatePoints(BRep_ListOfPointRepresentation& lpr,
                         Standard_Real p,
                         const Handle(Geom2d_Curve)& PC,
                         const Handle(Geom_Surface)& S,
                         const TopLoc_Location& L)
{
  BRep_ListIteratorOfListOfPointRepresentation itpr(lpr);
  while (itpr.More()) {
    const Handle(BRep_PointRepresentation)& pr = itpr.Value();
    Standard_Boolean isponcons = pr->IsPointOnCurveOnSurface(PC,S,L);
    if (isponcons) break;
    itpr.Next();
  }

  if (itpr.More()) {
    Handle(BRep_PointRepresentation)& pr = itpr.Value();
    pr->Parameter(p);
  }
  else {
    Handle(BRep_PointOnCurveOnSurface) POCS = 
      new BRep_PointOnCurveOnSurface(p,PC,S,L);
    lpr.Append(POCS);
  }
}


static void UpdatePoints(BRep_ListOfPointRepresentation& lpr,
                         Standard_Real p1,
                         Standard_Real p2,
                         const Handle(Geom_Surface)& S,
                         const TopLoc_Location& L)
{
  BRep_ListIteratorOfListOfPointRepresentation itpr(lpr);
  while (itpr.More()) {
    const Handle(BRep_PointRepresentation)& pr = itpr.Value();
    Standard_Boolean ispons = pr->IsPointOnSurface(S,L);
    if (ispons) break;
    itpr.Next();
  }

  if (itpr.More()) {
    Handle(BRep_PointRepresentation)& pr = itpr.Value();
    pr->Parameter(p1);
//    pr->Parameter(p2); // skv
    pr->Parameter2(p2); // skv
  }
  else {
    Handle(BRep_PointOnSurface) POS = new BRep_PointOnSurface(p1,p2,S,L);
    lpr.Append(POS);
  }
}


//=======================================================================
//function : MakeFace
//purpose  : 
//=======================================================================

void  BRep_Builder::MakeFace(TopoDS_Face& F,
                             const Handle(Geom_Surface)& S,
                             const Standard_Real Tol) const 
{
  Handle(BRep_TFace) TF = new BRep_TFace();
  TF->Surface(S);
  TF->Tolerance(Tol);
  MakeShape(F,TF);
}


//=======================================================================
//function : MakeFace
//purpose  : 
//=======================================================================

void  BRep_Builder::MakeFace(TopoDS_Face&                      F,
                             const Handle(Poly_Triangulation)& T) const
{
  Handle(BRep_TFace) TF = new BRep_TFace();
  TF->Triangulation(T);
  MakeShape(F, TF);
}


//=======================================================================
//function : MakeFace
//purpose  : 
//=======================================================================

void  BRep_Builder::MakeFace(TopoDS_Face& F,
                             const Handle(Geom_Surface)& S,
                             const TopLoc_Location& L,
                             const Standard_Real Tol) const 
{
  Handle(BRep_TFace) TF = new BRep_TFace();
  TF->Surface(S);
  TF->Tolerance(Tol);
  TF->Location(L);
  MakeShape(F,TF);
}


//=======================================================================
//function : UpdateFace
//purpose  : 
//=======================================================================

void  BRep_Builder::UpdateFace(const TopoDS_Face& F,
                               const Handle(Geom_Surface)& S,
                               const TopLoc_Location& L,
                               const Standard_Real Tol) const
{
  const Handle(BRep_TFace)& TF = *((Handle(BRep_TFace)*) &F.TShape());
  TF->Surface(S);
  TF->Tolerance(Tol);
  TF->Location(L.Predivided(F.Location()));
  F.TShape()->Modified(Standard_True);
}


//=======================================================================
//function : UpdateFace
//purpose  : 
//=======================================================================

void  BRep_Builder::UpdateFace(const TopoDS_Face& F,
                               const Handle(Poly_Triangulation)& T) const
{
  (*((Handle(BRep_TFace)*) &F.TShape()))->Triangulation(T);
  F.TShape()->Modified(Standard_True);
}


//=======================================================================
//function : UpdateFace
//purpose  : 
//=======================================================================

void  BRep_Builder::UpdateFace(const TopoDS_Face& F,
                               const Standard_Real Tol) const 
{
  (*((Handle(BRep_TFace)*) &F.TShape()))->Tolerance(Tol);
  F.TShape()->Modified(Standard_True);
}


//=======================================================================
//function : NaturalRestriction
//purpose  : 
//=======================================================================

void  BRep_Builder::NaturalRestriction(const TopoDS_Face& F,
                                       const Standard_Boolean N) const 
{
  (*((Handle(BRep_TFace)*) &F.TShape()))->NaturalRestriction(N);
  F.TShape()->Modified(Standard_True);
}


//=======================================================================
//function : MakeEdge
//purpose  : make undefined edge
//=======================================================================

void  BRep_Builder::MakeEdge(TopoDS_Edge& E) const
{
  Handle(BRep_TEdge) TE = new BRep_TEdge();
  TE->Closed(Standard_False);
  MakeShape(E,TE);
}


//=======================================================================
//function : UpdateEdge
//purpose  : 
//=======================================================================

void  BRep_Builder::UpdateEdge(const TopoDS_Edge& E, 
                               const Handle(Geom_Curve)& C, 
                               const TopLoc_Location& L,
                               const Standard_Real Tol) const
{
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());
  const TopLoc_Location l = L.Predivided(E.Location());

  UpdateCurves(TE->ChangeCurves(),C,l);
  if (!C.IsNull()) TE->Closed(C->IsClosed());

  TE->UpdateTolerance(Tol);
  TE->Modified(Standard_True);
}


//=======================================================================
//function : UpdateEdge
//purpose  : 
//=======================================================================

void  BRep_Builder::UpdateEdge(const TopoDS_Edge& E, 
                               const Handle(Geom2d_Curve)& C, 
                               const Handle(Geom_Surface)& S, 
                               const TopLoc_Location& L,
                               const Standard_Real Tol) const
{
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());
  const TopLoc_Location l = L.Predivided(E.Location());

  UpdateCurves(TE->ChangeCurves(),C,S,l);
  
  TE->UpdateTolerance(Tol);
  TE->Modified(Standard_True);
}


//=======================================================================
//function : UpdateEdge
//purpose  : for the second format (for XML Persistence)
//=======================================================================

void  BRep_Builder::UpdateEdge(const TopoDS_Edge& E, 
                               const Handle(Geom2d_Curve)& C, 
                               const Handle(Geom_Surface)& S, 
                               const TopLoc_Location& L,
                               const Standard_Real Tol,
                               const gp_Pnt2d& Pf,
                               const gp_Pnt2d& Pl) const
{
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());
  const TopLoc_Location l = L.Predivided(E.Location());

  UpdateCurves(TE->ChangeCurves(),C,S,l,Pf,Pl);
  
  TE->UpdateTolerance(Tol);
  TE->Modified(Standard_True);
}


//=======================================================================
//function : UpdateEdge
//purpose  : 
//=======================================================================

void  BRep_Builder::UpdateEdge(const TopoDS_Edge& E, 
                               const Handle(Geom2d_Curve)& C1, 
                               const Handle(Geom2d_Curve)& C2, 
                               const Handle(Geom_Surface)& S, 
                               const TopLoc_Location& L, 
                               const Standard_Real Tol) const
{
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());
  const TopLoc_Location l = L.Predivided(E.Location());

  UpdateCurves(TE->ChangeCurves(),C1,C2,S,l);
  if (!C1.IsNull() && !C2.IsNull()) 
    TE->Closed(C1->IsClosed() && C2->IsClosed());

  TE->UpdateTolerance(Tol);
  TE->Modified(Standard_True);
}


//=======================================================================
//function : UpdateEdge
//purpose  : for the second format (for XML Persistence)
//=======================================================================

void  BRep_Builder::UpdateEdge(const TopoDS_Edge& E, 
                               const Handle(Geom2d_Curve)& C1, 
                               const Handle(Geom2d_Curve)& C2, 
                               const Handle(Geom_Surface)& S, 
                               const TopLoc_Location& L, 
                               const Standard_Real Tol,
                               const gp_Pnt2d& Pf,
                               const gp_Pnt2d& Pl) const
{
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());
  const TopLoc_Location l = L.Predivided(E.Location());

  UpdateCurves(TE->ChangeCurves(),C1,C2,S,l,Pf,Pl);
  if (!C1.IsNull() && !C2.IsNull()) 
    TE->Closed(C1->IsClosed() && C2->IsClosed());
  
  TE->UpdateTolerance(Tol);
  TE->Modified(Standard_True);
}


//=======================================================================
//function : UpdateEdge
//purpose  : 
//=======================================================================

void  BRep_Builder::UpdateEdge(const TopoDS_Edge& E,
                               const Handle(Poly_Polygon3D)& P,
                               const TopLoc_Location& L) const
{
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());

  BRep_ListOfCurveRepresentation& lcr = TE->ChangeCurves();
  BRep_ListIteratorOfListOfCurveRepresentation itcr(lcr);

  while (itcr.More())
  {
    if (itcr.Value()->IsPolygon3D())
    {
      if (P.IsNull())
        lcr.Remove(itcr);
      else
        itcr.Value()->Polygon3D(P);
      TE->Modified(Standard_True);
      return;
    }
    itcr.Next();
  }

  const TopLoc_Location l = L.Predivided(E.Location());
  Handle(BRep_Polygon3D) P3d = new BRep_Polygon3D(P,l);
  lcr.Append(P3d);

  TE->Modified(Standard_True);
}


//=======================================================================
//function : UpdateEdge
//purpose  : 
//=======================================================================

void  BRep_Builder::UpdateEdge(const TopoDS_Edge& E,
                               const Handle(Poly_PolygonOnTriangulation)& P,
                               const Handle(Poly_Triangulation)& T,
                               const TopLoc_Location& L) const
{
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());
  const TopLoc_Location l = L.Predivided(E.Location());

  Standard_Boolean isModified = Standard_False;

  BRep_ListOfCurveRepresentation& lcr = TE->ChangeCurves();
  BRep_ListIteratorOfListOfCurveRepresentation itcr(lcr);
  Handle(BRep_CurveRepresentation) cr;

  while (itcr.More())
  {
    if (itcr.Value()->IsPolygonOnTriangulation(T,l))
	{
      // cr is used to keep a reference on the curve representation
      // this avoid deleting it as its content may be referenced by T
      cr = itcr.Value();
      lcr.Remove(itcr);
      isModified = Standard_True;
      break;
	}
    itcr.Next();
  }

  if (!P.IsNull())
  {
    Handle(BRep_PolygonOnTriangulation) PT =
      new BRep_PolygonOnTriangulation(P,T,l);
    lcr.Append(PT);
    isModified = Standard_True;
  }
  
  if (isModified)
    TE->Modified(Standard_True);
}


//=======================================================================
//function : UpdateEdge
//purpose  : 
//=======================================================================

void  BRep_Builder::UpdateEdge(const TopoDS_Edge& E,
                               const Handle(Poly_PolygonOnTriangulation)& P1,
                               const Handle(Poly_PolygonOnTriangulation)& P2,
                               const Handle(Poly_Triangulation)& T,
                               const TopLoc_Location& L) const
{
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());
  const TopLoc_Location l = L.Predivided(E.Location());

  Standard_Boolean isModified = Standard_False;

  BRep_ListOfCurveRepresentation& lcr = TE->ChangeCurves();
  BRep_ListIteratorOfListOfCurveRepresentation itcr(lcr);
  Handle(BRep_CurveRepresentation) cr;

  while (itcr.More())
  {
    if (itcr.Value()->IsPolygonOnTriangulation(T,l)) //szv:was L
    {
      // cr is used to keep a reference on the curve representation
      // this avoid deleting it as its content may be referenced by T
      cr = itcr.Value();
      lcr.Remove(itcr);
      isModified = Standard_True;
      break;
    }
    itcr.Next();
  }

  if (!P1.IsNull() && !P2.IsNull())
  {
    Handle(BRep_PolygonOnClosedTriangulation) PT =
      new BRep_PolygonOnClosedTriangulation(P1,P2,T,l);
    lcr.Append(PT);
    isModified = Standard_True;
  }

  if (isModified)
    TE->Modified(Standard_True);
}

//=======================================================================
//function : UpdateEdge
//purpose  : 
//=======================================================================

void  BRep_Builder::UpdateEdge(const TopoDS_Edge&            E,
                               const Handle(Poly_Polygon2D)& P,
                               const TopoDS_Face&            F) const
{
  TopLoc_Location l;
  const Handle(Geom_Surface)& S = BRep_Tool::Surface(F,l);
  UpdateEdge(E, P, S, l);
}

//=======================================================================
//function : UpdateEdge
//purpose  : 
//=======================================================================

void  BRep_Builder::UpdateEdge(const TopoDS_Edge&            E,
                               const Handle(Poly_Polygon2D)& P,
                               const Handle(Geom_Surface)&   S,
                               const TopLoc_Location&        L) const
{
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());
  TopLoc_Location l = L.Predivided(E.Location());

  BRep_ListOfCurveRepresentation& lcr = TE->ChangeCurves();
  Handle(BRep_CurveRepresentation) cr;

  BRep_ListIteratorOfListOfCurveRepresentation itcr(lcr);
  while (itcr.More()) {
    if (itcr.Value()->IsPolygonOnSurface(S, l)) break;
    itcr.Next();
  }

  if (itcr.More()) {
    // cr is used to keep a reference on the curve representation
    // this avoid deleting it as its content may be referenced by T
    cr = itcr.Value();
    lcr.Remove(itcr);
  }

  if (!P.IsNull()) {
    Handle(BRep_PolygonOnSurface) PS =
      new BRep_PolygonOnSurface(P, S, l);
    lcr.Append(PS);
  }

  TE->Modified(Standard_True);
}

//=======================================================================
//function : UpdateEdge
//purpose  : 
//=======================================================================

void  BRep_Builder::UpdateEdge(const TopoDS_Edge&            E,
                               const Handle(Poly_Polygon2D)& P1,
                               const Handle(Poly_Polygon2D)& P2,
                               const TopoDS_Face&            F) const
{
  TopLoc_Location l;
  const Handle(Geom_Surface)& S = BRep_Tool::Surface(F,l);
  UpdateEdge(E, P1, P2, S, l);
}

//=======================================================================
//function : UpdateEdge
//purpose  : 
//=======================================================================

void  BRep_Builder::UpdateEdge(const TopoDS_Edge&            E,
                               const Handle(Poly_Polygon2D)& P1,
                               const Handle(Poly_Polygon2D)& P2,
                               const Handle(Geom_Surface)&   S,
                               const TopLoc_Location&        L) const
{
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());
  TopLoc_Location l = L.Predivided(E.Location());
  
  BRep_ListOfCurveRepresentation& lcr = TE->ChangeCurves();
  Handle(BRep_CurveRepresentation) cr;

  BRep_ListIteratorOfListOfCurveRepresentation itcr(lcr);
  while (itcr.More()) {
    if (itcr.Value()->IsPolygonOnSurface(S, l)) break;
    itcr.Next();
  }

  if (itcr.More()) {
    // cr is used to keep a reference on the curve representation
    // this avoid deleting it as its content may be referenced by T
    cr = itcr.Value();
    lcr.Remove(itcr);
  }

  if (!P1.IsNull() && !P2.IsNull()) {
    Handle(BRep_PolygonOnClosedSurface) PS =
      new BRep_PolygonOnClosedSurface(P1, P2, S, TopLoc_Location());
    lcr.Append(PS);
  }
  
  TE->Modified(Standard_True);
}

//=======================================================================
//function : UpdateEdge
//purpose  : 
//=======================================================================

void  BRep_Builder::UpdateEdge(const TopoDS_Edge& E, 
                               const Standard_Real Tol) const
{
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());
  TE->UpdateTolerance(Tol);
  TE->Modified(Standard_True);
}


//=======================================================================
//function : Continuity
//purpose  : 
//=======================================================================

void  BRep_Builder::Continuity(const TopoDS_Edge& E, 
                               const TopoDS_Face& F1, 
                               const TopoDS_Face& F2, 
                               const GeomAbs_Shape C) const 
{
  TopLoc_Location l1,l2;
  const Handle(Geom_Surface)& S1 = BRep_Tool::Surface(F1,l1);
  const Handle(Geom_Surface)& S2 = BRep_Tool::Surface(F2,l2);
  Continuity(E,S1,S2,l1,l2,C);
}

//=======================================================================
//function : Continuity
//purpose  : 
//=======================================================================

void  BRep_Builder::Continuity(const TopoDS_Edge& E, 
                               const Handle(Geom_Surface)& S1,
                               const Handle(Geom_Surface)& S2, 
                               const TopLoc_Location& L1,
                               const TopLoc_Location& L2, 
                               const GeomAbs_Shape C)const 
{
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());

  const TopLoc_Location l1 = L1.Predivided(E.Location());
  const TopLoc_Location l2 = L2.Predivided(E.Location());

  UpdateCurves(TE->ChangeCurves(),S1,S2,l1,l2,C);
  
  TE->Modified(Standard_True);
}

//=======================================================================
//function : SameParameter
//purpose  : 
//=======================================================================

void  BRep_Builder::SameParameter(const TopoDS_Edge& E, 
                                  const Standard_Boolean S) const 
{
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());
  TE->SameParameter(S);
  TE->Modified(Standard_True);
}

//=======================================================================
//function : SameRange
//purpose  : 
//=======================================================================

void  BRep_Builder::SameRange(const TopoDS_Edge& E, 
                              const Standard_Boolean S) const 
{
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());
  TE->SameRange(S);
  TE->Modified(Standard_True);
}

//=======================================================================
//function : Degenerated
//purpose  : 
//=======================================================================

void  BRep_Builder::Degenerated(const TopoDS_Edge& E, 
                                const Standard_Boolean D) const 
{
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());
  TE->Degenerated(D);
  if (D) {
    // set a null 3d curve
    UpdateCurves(TE->ChangeCurves(),Handle(Geom_Curve)(),E.Location());
  }
  TE->Modified(Standard_True);
}


//=======================================================================
//function : Range
//purpose  : 
//=======================================================================

void  BRep_Builder::Range(const TopoDS_Edge&  E, 
                          const Standard_Real First, 
                          const Standard_Real Last,
                          const Standard_Boolean Only3d) const
{
  //  set the range to all the representations if Only3d=FALSE
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());
  
  BRep_ListOfCurveRepresentation& lcr = TE->ChangeCurves();
  BRep_ListIteratorOfListOfCurveRepresentation itcr(lcr);
  Handle(BRep_GCurve) GC;
  
  while (itcr.More()) {
    GC = Handle(BRep_GCurve)::DownCast(itcr.Value());
    if (!GC.IsNull()) {
      if (!Only3d || GC->IsCurve3D())
	GC->SetRange(First,Last);
      if (GC->IsCurve3D()) {
        // Set the closedness flag to the correct value.
        Handle(Geom_Curve) C = GC->Curve3D();
        
        //fixing a bug PRO18577 to avoid infinite values of First and Last 
        if ( !C.IsNull() && 
            !Precision::IsNegativeInfinite(First) && 
            !Precision::IsPositiveInfinite(Last) )   {
          Standard_Boolean closed = 
            C->Value(First).IsEqual(C->Value(Last),BRep_Tool::Tolerance(E));
          TE->Closed(closed);
        }
      }
    }
    itcr.Next();
  }
  
  TE->Modified(Standard_True);
}


//=======================================================================
//function : Range
//purpose  : 
//=======================================================================

void  BRep_Builder::Range(const TopoDS_Edge& E, 
                          const Handle(Geom_Surface)& S,
                          const TopLoc_Location& L,
                          const Standard_Real First, 
                          const Standard_Real Last) const
{
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());
  const TopLoc_Location l = L.Predivided(E.Location());

  BRep_ListOfCurveRepresentation& lcr = TE->ChangeCurves();
  BRep_ListIteratorOfListOfCurveRepresentation itcr(lcr);
  Handle(BRep_GCurve) GC;

  while (itcr.More()) {
    GC = Handle(BRep_GCurve)::DownCast(itcr.Value());
    if (!GC.IsNull()) {
      if (GC->IsCurveOnSurface(S,l)) {
        GC->SetRange(First,Last);

        // Set the closedness flag to the correct value.
        Handle(Geom2d_Curve) PC = GC->PCurve();
        gp_Pnt2d P1 = PC->Value(First);
        gp_Pnt2d P2 = PC->Value(Last);
        gp_Pnt   PP1 = S->Value(P1.X(),P1.Y());
        gp_Pnt   PP2 = S->Value(P2.X(),P2.Y());
        Standard_Boolean closed = PP1.IsEqual(PP2,BRep_Tool::Tolerance(E));
        TE->Closed(closed);
        break;
      }
    }
    itcr.Next();
  }
  
  if (!itcr.More())
    Standard_DomainError::Raise("BRep_Builder::Range, no pcurve");
  
  TE->Modified(Standard_True);
}


//=======================================================================
//function : Transfert
//purpose  : 
//=======================================================================

void  BRep_Builder::Transfert(const TopoDS_Edge& Ein, 
                              const TopoDS_Edge& Eout) const
{
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &Ein.TShape());

  const Standard_Real tol = TE->Tolerance();
  
  BRep_ListOfCurveRepresentation& lcr = TE->ChangeCurves();
  BRep_ListIteratorOfListOfCurveRepresentation itcr(lcr);
  
  while (itcr.More()) {
    
    const Handle(BRep_CurveRepresentation)& CR = itcr.Value();
    
    if (CR->IsCurveOnSurface()) {
      UpdateEdge(Eout,
                 CR->PCurve(),
                 CR->Surface(),
                 Ein.Location() * CR->Location(),tol);
    }

    else if (CR->IsCurveOnClosedSurface()) {
      UpdateEdge(Eout,
                 CR->PCurve(),
                 CR->PCurve2(),
                 CR->Surface(),
                 Ein.Location() * CR->Location(),tol);
    }
    
    if (CR->IsRegularity()) {
      Continuity(Eout,
                 CR->Surface(),
                 CR->Surface2(),
                 Ein.Location() * CR->Location(),
                 Ein.Location() * CR->Location2(),
                 CR->Continuity());
    }
    
    itcr.Next();
  }
}


//=======================================================================
//function : UpdateVertex
//purpose  : update vertex with 3d point
//=======================================================================

void  BRep_Builder::UpdateVertex(const TopoDS_Vertex& V, 
                                 const gp_Pnt& P, 
                                 const Standard_Real Tol) const 
{
  const Handle(BRep_TVertex)& TV = *((Handle(BRep_TVertex)*) &V.TShape());

  TV->Pnt(P.Transformed(V.Location().Inverted().Transformation()));
  TV->UpdateTolerance(Tol);
  TV->Modified(Standard_True);
}


//=======================================================================
//function : UpdateVertex
//purpose  : update vertex with parameter on edge
//=======================================================================

void  BRep_Builder::UpdateVertex(const TopoDS_Vertex& V, 
                                 const Standard_Real Par, 
                                 const TopoDS_Edge& E,
                                 const Standard_Real Tol) const
{
  if (Precision::IsPositiveInfinite(Par) ||
      Precision::IsNegativeInfinite(Par))
    Standard_DomainError::Raise("BRep_Builder::Infinite parameter");
  
  const Handle(BRep_TVertex)& TV = *((Handle(BRep_TVertex)*) &V.TShape());
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());

  TopLoc_Location L = E.Location().Predivided(V.Location());

  // Search the vertex in the edge
  TopAbs_Orientation ori = TopAbs_INTERNAL;

  TopoDS_Iterator itv(E.Oriented(TopAbs_FORWARD));

  // if the edge has no vertices
  // and is degenerated use the vertex orientation
  // RLE, june 94

  if (!itv.More() && TE->Degenerated())
    ori = V.Orientation();

  while (itv.More()) {
    const TopoDS_Shape& Vcur = itv.Value();
    if (V.IsSame(Vcur)) {
      ori = Vcur.Orientation();
      if (ori == V.Orientation()) break;
    }
    itv.Next();
  }

  BRep_ListOfCurveRepresentation& lcr = TE->ChangeCurves();
  BRep_ListIteratorOfListOfCurveRepresentation itcr(lcr);
  Handle(BRep_GCurve) GC;

  while (itcr.More()) {
    GC = Handle(BRep_GCurve)::DownCast(itcr.Value());
    if (!GC.IsNull()) {
      if (ori == TopAbs_FORWARD) 
        GC->First(Par);
      else if (ori == TopAbs_REVERSED)
        GC->Last(Par);
      else {
        BRep_ListOfPointRepresentation& lpr = TV->ChangePoints();
        const TopLoc_Location& GCloc = GC->Location();
        TopLoc_Location LGCloc = L*GCloc; 
        if (GC->IsCurve3D()) {
          const Handle(Geom_Curve)& GC3d = GC->Curve3D();
          UpdatePoints(lpr,Par,GC3d,LGCloc);
        }
        else if (GC->IsCurveOnSurface()) {
          const Handle(Geom2d_Curve)& GCpc = GC->PCurve();
          const Handle(Geom_Surface)& GCsu = GC->Surface();
          UpdatePoints(lpr,Par,GCpc,GCsu,LGCloc);
        }
      }
    }
    itcr.Next();
  }

  if ((ori != TopAbs_FORWARD) && (ori != TopAbs_REVERSED))
    TV->Modified(Standard_True);
  TV->UpdateTolerance(Tol);
  TE->Modified(Standard_True);
}


//=======================================================================
//function : UpdateVertex
//purpose  : update vertex with parameter on edge on face
//=======================================================================

void  BRep_Builder::UpdateVertex(const TopoDS_Vertex& V,
                                 const Standard_Real  Par,
                                 const TopoDS_Edge&   E,
                                 const Handle(Geom_Surface)& S,
                                 const TopLoc_Location& L,
                                 const Standard_Real  Tol) const
{
  if (Precision::IsPositiveInfinite(Par) ||
      Precision::IsNegativeInfinite(Par))
    Standard_DomainError::Raise("BRep_Builder::Infinite parameter");
  
  // Find the curve representation
  TopLoc_Location l = L.Predivided(V.Location());
  
  const Handle(BRep_TVertex)& TV = *((Handle(BRep_TVertex)*) &V.TShape());
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());
  
  
  // Search the vertex in the edge
  TopAbs_Orientation ori = TopAbs_INTERNAL;
  
  TopoDS_Iterator itv(E.Oriented(TopAbs_FORWARD));

  // if the edge has no vertices
  // and is degenerated use the vertex orientation
  // RLE, june 94

  if (!itv.More() && TE->Degenerated())
    ori = V.Orientation();

  while (itv.More()) {
    const TopoDS_Shape& Vcur = itv.Value();
    if (V.IsSame(Vcur)) {
      ori = Vcur.Orientation();
      if (ori == V.Orientation()) break;
    }
    itv.Next();
  }

  BRep_ListOfCurveRepresentation& lcr = TE->ChangeCurves();
  BRep_ListIteratorOfListOfCurveRepresentation itcr(lcr);
  Handle(BRep_GCurve) GC;

  while (itcr.More()) {
    GC = Handle(BRep_GCurve)::DownCast(itcr.Value());
    if (!GC.IsNull()) {
//      if (GC->IsCurveOnSurface(S,l)) {
      if (GC->IsCurveOnSurface(S,L)) { //xpu020198 : BUC60407
        if (ori == TopAbs_FORWARD) 
          GC->First(Par);
        else if (ori == TopAbs_REVERSED)
          GC->Last(Par);
        else {
          BRep_ListOfPointRepresentation& lpr = TV->ChangePoints();
          const Handle(Geom2d_Curve)& GCpc = GC->PCurve();
          UpdatePoints(lpr,Par,GCpc,S,l);
          TV->Modified(Standard_True);
        }
        break;
      }
    }
    itcr.Next();
  }
  
  if (!itcr.More())
    Standard_DomainError::Raise("BRep_Builder:: no pcurve");
  
  TV->UpdateTolerance(Tol);
  TE->Modified(Standard_True);
}

//=======================================================================
//function : UpdateVertex
//purpose  : update vertex with parameters on face
//=======================================================================

void  BRep_Builder::UpdateVertex(const TopoDS_Vertex& Ve, 
                                 const Standard_Real U, 
                                 const Standard_Real V,
                                 const TopoDS_Face& F, 
                                 const Standard_Real Tol) const
{
  const Handle(BRep_TVertex)& TV = *((Handle(BRep_TVertex)*) &Ve.TShape());
  
  TopLoc_Location L;
  const Handle(Geom_Surface)& S = BRep_Tool::Surface(F,L);
  L = L.Predivided(Ve.Location());
  BRep_ListOfPointRepresentation& lpr = TV->ChangePoints(); 
  UpdatePoints(lpr,U,V,S,L);
  
  TV->UpdateTolerance(Tol);
  TV->Modified(Standard_True);
}

//=======================================================================
//function : UpdateVertex
//purpose  : update vertex with 3d point
//=======================================================================

void  BRep_Builder::UpdateVertex(const TopoDS_Vertex& V, 
                                 const Standard_Real Tol) const
{
  const Handle(BRep_TVertex)& TV = *((Handle(BRep_TVertex)*) &V.TShape());
  TV->UpdateTolerance(Tol);
  TV->Modified(Standard_True);
}


//=======================================================================
//function : Transfert
//purpose  : 
//=======================================================================

void  BRep_Builder::Transfert(const TopoDS_Edge& Ein,
                              const TopoDS_Edge& Eout,
                              const TopoDS_Vertex& Vin,
                              const TopoDS_Vertex& Vout) const
{
  const Standard_Real tol = BRep_Tool::Tolerance(Vin);
  const Standard_Real parin = BRep_Tool::Parameter(Vin,Ein);
  UpdateVertex(Vout,parin,Eout,tol);
}
