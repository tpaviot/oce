// Created on: 1995-01-03
// Created by: Frederic MAUPAS
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

//gka,abv 14.09.99: S4136: eliminate BRepAPI::Precision()

#include <StepToTopoDS_TranslatePolyLoop.ixx>

#include <StepToTopoDS_PointPair.hxx>

#include <StepToGeom_MakeCartesianPoint.hxx>

#include <BRep_Builder.hxx>
//#include <BRepAPI.hxx>

#include <ElSLib.hxx>
#include <ShapeAnalysis_Surface.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Edge.hxx>

#include <Geom2d_Line.hxx>
#include <Geom_Line.hxx>
#include <Geom_Plane.hxx>
#include <Geom_CartesianPoint.hxx>

#include <gp_Vec2d.hxx>

#include <StepGeom_HArray1OfCartesianPoint.hxx>
#include <Transfer_TransientProcess.hxx>
#include <Precision.hxx>

// ============================================================================
// Method  :
// Purpose :
// ============================================================================

StepToTopoDS_TranslatePolyLoop::StepToTopoDS_TranslatePolyLoop()
{
  done = Standard_False;
}

// ============================================================================
// Method  :
// Purpose :
// ============================================================================

StepToTopoDS_TranslatePolyLoop::StepToTopoDS_TranslatePolyLoop(const Handle(StepShape_PolyLoop)& PL, StepToTopoDS_Tool& T, const Handle(Geom_Surface)& S, const TopoDS_Face& F)
{
  Init (PL, T, S, F);
}

// ============================================================================
// Method  :
// Purpose :
// ============================================================================

void StepToTopoDS_TranslatePolyLoop::Init(const Handle(StepShape_PolyLoop)& PL, StepToTopoDS_Tool& aTool, const Handle(Geom_Surface)& GeomSurf, const TopoDS_Face& TopoFace)
{
  if (!aTool.IsBound(PL)) {
    BRep_Builder B;
    Handle(Transfer_TransientProcess) TP = aTool.TransientProcess();

//:S4136    Standard_Real preci = BRepAPI::Precision();
    Standard_Integer i;
    Handle(StepGeom_CartesianPoint) P1,P2;
    Handle(Geom_CartesianPoint) GP1, GP2;
    TopoDS_Vertex V1, V2;
    TopoDS_Edge E;
    TopoDS_Wire W;
    Handle(Geom_Line) L;
    Handle(Geom2d_Line) L2d;
    gp_Vec V;
    gp_Vec2d V2d;
    Standard_Real Magn;
    Handle(Geom_Plane) SP = Handle(Geom_Plane)::DownCast(GeomSurf);
    if (SP.IsNull()) TP->AddFail(PL,"Surface not planar in a FacetedBRep !");
    Handle(ShapeAnalysis_Surface) STSU = new ShapeAnalysis_Surface ( GeomSurf );
    Standard_Integer Nb = PL->NbPolygon();
    Handle(StepGeom_HArray1OfCartesianPoint) Poly = 
      new StepGeom_HArray1OfCartesianPoint(1, Nb+1);

    for ( i=1; i<=Nb; i++ )
      Poly->SetValue(i, PL->PolygonValue(i));

    Nb++;
    Poly->SetValue(Nb, PL->PolygonValue(1));
    P1 = Poly->Value(1);
	StepToGeom_MakeCartesianPoint::Convert(P1,GP1);
    if (aTool.IsVertexBound(P1)) {
      V1 = aTool.FindVertex(P1);
    }
    else {
      B.MakeVertex(V1, GP1->Pnt(), Precision::Confusion()); //:S4136: preci
      aTool.BindVertex(P1,V1);
    }
    B.MakeWire(W);
    for ( i=2; i<=Nb; i++){
      P2 = Poly->Value(i);
      if (P1 == P2) continue;  // peut arriver (KK)  CKY 9-DEC-1997
      StepToTopoDS_PointPair PP(P1, P2); 
      StepToGeom_MakeCartesianPoint::Convert(P2,GP2);
      TopoDS_Shape aBoundEdge;
      Standard_Boolean isbound = aTool.IsEdgeBound(PP);
      if ( !isbound) {
	if (aTool.IsVertexBound(P2)) {
	  V2 = aTool.FindVertex(P2);
	}
	else {
	  B.MakeVertex(V2, GP2->Pnt(), Precision::Confusion()); //:S4136: preci
	  aTool.BindVertex(P2,V2);
	}
	V = gp_Vec( GP1->Pnt(), GP2->Pnt());
	L = new Geom_Line( GP1->Pnt() , gp_Dir(V) );
	B.MakeEdge(E, L, Precision::Confusion()); //:S4136: preci
	V1.Orientation(TopAbs_FORWARD);
	V2.Orientation(TopAbs_REVERSED);
	B.Add(E, V1);
	B.Add(E, V2);
	Magn = V.Magnitude();
	B.UpdateVertex(V1, 0., E, 0. ); //:S4136: preci
	B.UpdateVertex(V2, Magn, E, 0. ); //:S4136: preci
      } 
      else {
	aBoundEdge = aTool.FindEdge(PP);
	E = TopoDS::Edge(aBoundEdge);
//  Il faut qu en finale l edge soit vue
//  - via sa premiere face, orientation combinee = celle de cette premiere face
//  - via sa deuxieme face, orientation combinee INVERSE de la precedente
	if (TopoFace.Orientation() == TopAbs_FORWARD) E.Reverse();
	V2 = aTool.FindVertex(P2); 
//	Standard_Real u1,v1,u2,v2;
//	ElSLib::Parameters(SP->Pln(), GP1->Pnt(), u1, v1);
//	ElSLib::Parameters(SP->Pln(), GP2->Pnt(), u2, v2);
//	V2d = gp_Vec2d( gp_Pnt2d(u1,v1), gp_Pnt2d(u2,v2) );
//	L2d = new Geom2d_Line( gp_Pnt2d(u1,v1), gp_Dir2d(V2d) );
      }
      gp_Pnt2d V2p1 = STSU->ValueOfUV (GP1->Pnt(), Precision());
      gp_Pnt2d V2p2 = STSU->ValueOfUV (GP2->Pnt(), Precision());
      if (E.Orientation() == TopAbs_FORWARD) {
	V2d = gp_Vec2d( V2p1, V2p2 );
	L2d = new Geom2d_Line( V2p1, gp_Dir2d(V2d) );
      } else {
	V2d = gp_Vec2d( V2p2, V2p1 );
	L2d = new Geom2d_Line( V2p2, gp_Dir2d(V2d) );
      }
      B.UpdateEdge(E, L2d, TopoFace, 0.);
//      E.Orientation(TopAbs_FORWARD);
      TopoDS_Edge EB = E;  // pour le binding : cumul des orientations !
      EB.Orientation (TopoFace.Orientation());
      if (!isbound) aTool.BindEdge(PP, EB);
      if (!E.IsNull()) { 
	B.Add(W,E);
      }
      P1  = P2;
      GP1 = GP2;
      V1  = V2;
    }
    aTool.Bind(PL, W);
    myResult = W;
    myError  = StepToTopoDS_TranslatePolyLoopDone;
    done     = Standard_True;
  }
  else {
    myResult = TopoDS::Wire(aTool.Find(PL));
    myError  = StepToTopoDS_TranslatePolyLoopDone;
    done     = Standard_True;    
  }
}

// ============================================================================
// Method  :
// Purpose :
// ============================================================================

const TopoDS_Shape& StepToTopoDS_TranslatePolyLoop::Value() const 
{
  StdFail_NotDone_Raise_if(!done,"");
  return myResult;
}

// ============================================================================
// Method  :
// Purpose :
// ============================================================================

StepToTopoDS_TranslatePolyLoopError StepToTopoDS_TranslatePolyLoop::Error() const
{
  return myError;
}
