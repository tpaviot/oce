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

//:o0 abv 16.02.99: POLYLINE allowed as 3d curve of edge
//gka,abv 05.04.99: S4136: improving tolerance management, eliminate BRepAPI::Precision()

#include <StepToTopoDS_TranslateEdge.ixx>

#include <StepToTopoDS.hxx>
#include <StepToTopoDS_TranslateVertex.hxx>
#include <StepToTopoDS_GeometricTool.hxx>
#include <StepToGeom_MakeCurve.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <BRep_Builder.hxx>
#include <BRep_Tool.hxx>
#include <BRepLib.hxx>
#include <BRepLib_MakeEdge.hxx>
#include <Geom_Curve.hxx>
#include <GeomAbs_Shape.hxx>

#include <Geom_Line.hxx>
#include <gp_Vec.hxx>
#include <gp_Dir.hxx>
#include <gp_Lin.hxx>

#include <ShapeAnalysis_Curve.hxx>
#include <ShapeConstruct_Curve.hxx>

#include <StepShape_EdgeCurve.hxx>
#include <StepShape_OrientedEdge.hxx>
#include <StepGeom_Curve.hxx>
//#include <StepGeom_Polyline.hxx>
#include <StepGeom_Pcurve.hxx>
#include <StepGeom_SurfaceCurve.hxx>
#include <Transfer_TransientProcess.hxx>
//#include <TransferBRep.hxx>

#include <GeomAdaptor_Curve.hxx>
#include <GCPnts_AbscissaPoint.hxx>
#include <Precision.hxx>

#include <StepToGeom_MakeCurve2d.hxx>
#include <StepRepr_DefinitionalRepresentation.hxx>
#include <UnitsMethods.hxx>

//:d8
#include <StepShape_VertexPoint.hxx>
#include <StepGeom_CartesianPoint.hxx>
#include <StepToGeom_MakeCartesianPoint.hxx>
#include <Geom_CartesianPoint.hxx>

// Used in I-DEAS-like STP processing (ssv; 15.11.2010)
#include <TCollection_HAsciiString.hxx>

//#define DEBUG


// ============================================================================
// Method  : DecodeMakeEdgeError
// Purpose : 
// ============================================================================

static void DecodeMakeEdgeError(const BRepLib_MakeEdge&   ME,
				const Handle(Standard_Transient)& orig,
				const Handle(Geom_Curve)& myCurve,
				const TopoDS_Vertex&      V1,
				const TopoDS_Vertex&      V2,
				const Standard_Real&    /*U1*/,
				const Standard_Real&    /*U2*/,
				StepToTopoDS_Tool&   aTool,
				const Handle(StepShape_TopologicalRepresentationItem)& /*tobind*/)
{
  Handle(Transfer_TransientProcess) TP = aTool.TransientProcess();
//  if (!myCurve.IsNull() && !tobind.IsNull()) {
//    TransferBRep::SetShapeResult
//      (TP,tobind, MakeEdge(myCurve,V1,V2,U1,U2,BRepAPI::Precision()) );
//    aTool.Bind (tobind,E);  SURTOUT PAS : noter pour debug/erreur
//  }
#ifdef DEBUG
  cout << "------------------------------------" << endl;
  cout << "MakeEdge Error  : " << ME.Error()<<" - ";
#endif
  switch(ME.Error())
    {
    case (BRepLib_EdgeDone): return;
    case (BRepLib_PointProjectionFailed):
      TP->AddFail(orig," Point Projection failed");
      break;
    case (BRepLib_ParameterOutOfRange):
      TP->AddFail(orig," Parameter Out Of Range");
      break;
    case (BRepLib_DifferentPointsOnClosedCurve):
      TP->AddFail(orig," Different Points on Closed Curve");
      break;
    case (BRepLib_PointWithInfiniteParameter):
      TP->AddFail(orig," Point with infinite Parameter");
      break;
    case (BRepLib_DifferentsPointAndParameter):
      if (!ShapeConstruct_Curve().AdjustCurve
	  (myCurve,BRep_Tool::Pnt(V1),BRep_Tool::Pnt(V2),Standard_True,Standard_True))
	TP->AddFail(orig," Different Points and Parameters");
       else TP->AddWarning(orig,"Different Points and Parameters, adjusted");
      break;
    case (BRepLib_LineThroughIdenticPoints):
      TP->AddFail(orig," Line through identic Points");
      break;
    }
#ifdef DEBUG
  cout << "Original Type   : " << orig->DynamicType() << endl;
  cout << "3D Curve Type   : " << myCurve->DynamicType() << endl;
  cout << "First Parameter : " << U1 << endl;
  gp_Pnt p1 = BRep_Tool::Pnt(V1);
//  cout << "First Point     : ";
  cout << "First Vertex    : "<<p1.X()<<"  "<<p1.Y()<<"  "<<p1.Z()<<"  ";
  cout << "Distance Point - Vertex : ";
  Standard_Real d1 = p1.Distance(myCurve->Value(U1)); 
  cout << d1 << endl;
  cout << "Last  Parameter : " << U2 << endl;
  gp_Pnt p2 = BRep_Tool::Pnt(V2);
//  cout << "Last  Point     : ";
  cout << "Last  Vertex    : "<<p2.X()<<"  "<<p2.Y()<<"  "<<p2.Z()<<"  ";
  cout << "Distance Point - Vertex : ";
  Standard_Real d2 = BRep_Tool::Pnt(V2).Distance(myCurve->Value(U2)); 
  cout << d2 << endl;
#endif
}

// ============================================================================
// Method  : StepToTopoDS_TranslateEdge::StepToTopoDS_TranslateEdge
// Purpose : Empty Constructor
// ============================================================================

static Handle(Geom_Curve) MakeCurve
  (const Handle(StepGeom_Curve)& C1, const Handle(Transfer_TransientProcess) TP)
{
  Handle(Geom_Curve) C2 = Handle(Geom_Curve)::DownCast (TP->FindTransient(C1));
  if (!C2.IsNull()) return C2;
  if (StepToGeom_MakeCurve::Convert(C1,C2))
    TP->BindTransient (C1,C2);
  return C2;
}

static TopoDS_Edge  MakeEdge
  (const Handle(Geom_Curve)& C3D,
   const TopoDS_Vertex& V1, const TopoDS_Vertex& V2,
   const Standard_Real U1, const Standard_Real U2) //, const Standard_Real preci)
{
//  fait son edge quoi qu il arrive
  BRep_Builder B;
  TopoDS_Edge E;
  B.MakeEdge (E,C3D,Precision::Confusion());//preci);
  B.Add (E,V1);  B.Add (E,V2);
  B.UpdateVertex(V1, U1, E, 0.);//preci);
  B.UpdateVertex(V2, U2, E, 0.);//preci);
  return E;
}

StepToTopoDS_TranslateEdge::StepToTopoDS_TranslateEdge()
{
  done = Standard_False;
}

// ============================================================================
// Method  : StepToTopoDS_TranslateEdge::StepToTopoDS_TranslateEdge()
// Purpose : Constructor with an Edge and a Tool
// ============================================================================

StepToTopoDS_TranslateEdge::StepToTopoDS_TranslateEdge(const Handle(StepShape_Edge)& E, 
                                                       StepToTopoDS_Tool& T, 
                                                       StepToTopoDS_NMTool& NMTool)
{
  Init(E, T, NMTool);
}

// ============================================================================
// Method  : Init
// Purpose : Init with an Edge and a Tool.
//           This method builds an Edge With 2 Vertices and 2 Parameters.
//           The Edge is always build like FORWARD (BRepLib_MakeEdge)
// ============================================================================

void StepToTopoDS_TranslateEdge::Init(const Handle(StepShape_Edge)& aEdge, 
                                      StepToTopoDS_Tool& aTool,
                                      StepToTopoDS_NMTool& NMTool)
{
  Handle(Transfer_TransientProcess) TP = aTool.TransientProcess();

  Handle(StepShape_OrientedEdge) OE = 
    Handle(StepShape_OrientedEdge)::DownCast(aEdge);
  Handle(StepShape_Edge) wEdge = aEdge;
  if ( ! OE.IsNull() ) wEdge = OE->EdgeElement();
  Handle(StepShape_EdgeCurve) EC = Handle(StepShape_EdgeCurve)::DownCast(wEdge);
  
  if (aTool.IsBound(EC)) {
    myResult = aTool.Find(EC);
    if (BRep_Tool::Degenerated(TopoDS::Edge(myResult))) {
      TP->AddWarning(EC,"Degenerated Edge in several faces : transferred for each face");
    }
    else {
      myError  = StepToTopoDS_TranslateEdgeDone;
      done     = Standard_True;
//      BRep_Builder B;
//:S4136      B.SameRange(TopoDS::Edge(myResult), Standard_False);    //:a5 abv 11 Feb 98
//:S4136      B.SameParameter(TopoDS::Edge(myResult), Standard_False);//:a5
      return;
    }
  }

  // [BEGIN] Proceed with non-manifold cases (ssv; 12.11.2010)
  if ( NMTool.IsActive() && NMTool.IsBound(EC) ) {
    TopoDS_Shape existingShape = NMTool.Find(EC);
    // Reverse shape's orientation if needed
    if ( !OE->Orientation() )
      existingShape.Reverse();
    myResult = existingShape;
    myError = StepToTopoDS_TranslateEdgeDone;
    done = Standard_True;
    return;
  }
  // [END] Proceed with non-manifold cases (ssv; 12.11.2010)

  // [BEGIN] Proceed with I-DEAS-like STP (ssv; 15.11.2010)
  const Handle(TCollection_HAsciiString) anECName = EC->Name();
  if ( NMTool.IsIDEASCase() && !anECName.IsNull() && !anECName->IsEmpty() &&
       NMTool.IsBound(anECName->String()) ) {
    TopoDS_Shape existingShape = NMTool.Find(anECName->String());
    // Reverse shape's orientation if needed
    if ( !OE->Orientation() )
      existingShape.Reverse();
    // Register Edge for final processing (I-DEAS case)
    NMTool.RegisterNMEdge(existingShape);
    myResult = existingShape;
    myError = StepToTopoDS_TranslateEdgeDone;
    done = Standard_True;
    return;
  }
  // [END] Proceed with I-DEAS-like STP (ssv; 15.11.2010)

  BRep_Builder B;

//  Standard_Real preci = BRepAPI::Precision();

//  Standard_Real precision = BRepAPI::Precision();

  Handle(StepGeom_Curve) C = EC->EdgeGeometry();
  TopoDS_Edge E;
  Handle(StepShape_Vertex) Vstart, Vend;

  // -----------------------------------------------------------
  // Extract the start and end Vertices corresponding to FORWARD
  // (following the geometrical sense)
  // -----------------------------------------------------------

//  Standard_Boolean OrientedEdgeOrientation = OE->Orientation();
  Standard_Boolean EdgeCurveSameSense      = EC->SameSense();
  
  if (EdgeCurveSameSense) {
    Vstart = EC->EdgeStart();
    Vend   = EC->EdgeEnd();
  }
  else {
    Vend   = EC->EdgeStart();
    Vstart = EC->EdgeEnd();
  }

  TopoDS_Vertex V1, V2;

  StepToTopoDS_TranslateVertex myTranVertex1(Vstart, aTool, NMTool);
  StepToTopoDS_TranslateVertex myTranVertex2(Vend, aTool, NMTool);

  if (myTranVertex1.IsDone()) {
    V1 = TopoDS::Vertex(myTranVertex1.Value());
    V1.Orientation(TopAbs_FORWARD);
  }
  if (Vend == Vstart) {
    V2 = V1;
    V2.Orientation(TopAbs_REVERSED);
  }
  else if (myTranVertex2.IsDone()) {
    V2 = TopoDS::Vertex(myTranVertex2.Value());
    V2.Orientation(TopAbs_REVERSED);
  }
  done = Standard_True;
  
  // ----------------------------------------------------------
  // --- The EdgeCurve Geometry is of StepGeom_Curve Type
  // --- It can be : * a Pcurve : no 3D curve is constructed
  // ---             * a Surface Curve, Intersection Curve
  // ---               or a Seam Curve
  // ---             * a 3D Curve
  // ----------------------------------------------------------
  
  if ( C->IsKind(STANDARD_TYPE(StepGeom_Pcurve))) {
    B.MakeEdge(E);
//:S4136    B.UpdateEdge (E,preci);
    B.Add(E, V1);    // ?? en fin de TranslateEdgeLoop
    B.Add(E, V2);
  }
  else if (C->IsKind(STANDARD_TYPE(StepGeom_SurfaceCurve)) ) {
    // qui reprend les types SeamCurve et IntersectionCurve
    // --- The Edge Geometry is a Surface Curve ---
    // ---     (3d + 2 Pcurve Or Surface)       ---
    Handle(StepGeom_SurfaceCurve) Sc =
      Handle(StepGeom_SurfaceCurve)::DownCast(C);
    Handle(StepGeom_Curve) C1 = Sc->Curve3d();
//    if (C1->IsKind(STANDARD_TYPE(StepGeom_Polyline))) {
//    B.MakeEdge(E);
//      B.UpdateEdge (E,preci);
//      B.Add(E, V1);    // ?? en fin de TranslateEdgeLoop
//      B.Add(E, V2);
//    }
//    else {
      MakeFromCurve3D (C1,EC,Vend,Precision(), E,V1,V2 , aTool);
//    }
  }
//  else if (C->IsKind(STANDARD_TYPE(StepGeom_Polyline))) {
//    B.MakeEdge(E);
//    B.UpdateEdge (E,preci);
//    B.Add(E, V1);    // ?? en fin de TranslateEdgeLoop
//    B.Add(E, V2);
//  }
  else {
    // --- The Edge Geometry is a Single 3d Curve ---
    MakeFromCurve3D (C,EC,Vend,Precision(), E,V1,V2 , aTool);
  }
  // On force les flags SameRange et SameParameter a Standard_False
  if (done) {
//:S4136    B.SameRange(E, Standard_False);
//:S4136    B.SameParameter(E, Standard_False);
    aTool.Bind(EC,E);

    // Bind Edge in NM tool (ssv; 15.11.2010)
    if ( NMTool.IsActive() ) {
      NMTool.Bind(EC, E);
      if ( NMTool.IsIDEASCase() && !anECName.IsNull() && !anECName->IsEmpty() )
        NMTool.Bind(anECName->String(), E);
    }

    myResult = E;
    myError = StepToTopoDS_TranslateEdgeDone;
  }
}


// ============================================================================
// Method  : MakeFromCurve3D
// Purpose : case of a Curve 3D (alone or in SurfaceCurve)
// ============================================================================

// auxiliary function
//:e6 abv 16 Apr 98: ProSTEP TR8, r0601_sy.stp, #14907
static void GetCartesianPoints ( const Handle(StepShape_EdgeCurve)& EC, 
				 gp_Pnt &P1, gp_Pnt &P2)
{
  for ( Standard_Integer i=1; i<=2; i++ ) {
    const Handle(StepShape_Vertex) V = ( (Standard_Boolean)(i==1) == EC->SameSense() ? EC->EdgeStart() : EC->EdgeEnd() );
    const Handle(StepShape_VertexPoint) VP = Handle(StepShape_VertexPoint)::DownCast(V);
    if ( VP.IsNull() ) continue;
    const Handle(StepGeom_CartesianPoint) P = Handle(StepGeom_CartesianPoint)::DownCast(VP->VertexGeometry());
    Handle(Geom_CartesianPoint) CP;
    StepToGeom_MakeCartesianPoint::Convert(P,CP);
	( i==1 ? P1 : P2 ) = CP->Pnt();
  }
}

void  StepToTopoDS_TranslateEdge::MakeFromCurve3D
  (const Handle(StepGeom_Curve)& C3D, const Handle(StepShape_EdgeCurve)& EC,
   const Handle(StepShape_Vertex)&  Vend,
   const Standard_Real preci, TopoDS_Edge& E,
   TopoDS_Vertex& V1, TopoDS_Vertex& V2,
   StepToTopoDS_Tool&   aTool)
{
  Handle(Transfer_TransientProcess) TP = aTool.TransientProcess();
  Handle(Geom_Curve) C1 = MakeCurve(C3D,TP);
  if (C1.IsNull()) {
    TP->AddFail(C3D," Make Geom_Curve (3D) failed");
    myError = StepToTopoDS_TranslateEdgeOther;
    done = Standard_False;
    return;
  }
    // -- Statistics -- -> No Warning message
  aTool.AddContinuity (C1);
  BRep_Builder B;
  Standard_Real temp1,temp2, U1,U2;
  gp_Pnt pproj;
  gp_Pnt pv1 = BRep_Tool::Pnt(V1);
  gp_Pnt pv2 = BRep_Tool::Pnt(V2);

  //:e6 abv
  gp_Pnt pnt1 = pv1, pnt2 = pv2;
  if ( V1.IsSame ( V2 ) ) GetCartesianPoints ( EC, pnt1, pnt2 );
  ShapeAnalysis_Curve sac;
  temp1 = sac.Project (C1,pnt1,preci,pproj,U1,Standard_False);
  temp2 = sac.Project (C1,pnt2,preci,pproj,U2,Standard_False);

  if (!StepToTopoDS_GeometricTool::UpdateParam3d(C1, U1, U2, preci))
    TP->AddWarning(C3D,"Update of 3D-Parameters has failed");

  //:d5: instead of AdjustCurve above which is incorrect if U1 and U2 are not ends
  gp_Pnt pU1 = C1->Value ( U1 ), pU2 = C1->Value ( U2 );
  temp1 = pU1.Distance ( pv1 );
  temp2 = pU2.Distance ( pv2 );
  if ( temp1 > preci || temp2 > preci ) {
    TP->AddWarning (C3D,"Poor result from projection vertex / curve 3d");
  }
  B.UpdateVertex ( V1, 1.000001*temp1 ); //:h6 abv 14 Jul 98: PRO8845 #2746: *=1.0001
  B.UpdateVertex ( V2, 1.000001*temp2 ); //:h6
  
  BRepLib_MakeEdge ME(C1, V1, V2, U1, U2);
  if (ME.IsDone()) {
    E = ME.Edge();
    B.Range ( E, U1, U2 ); // abv 14 Mar 00: trj3_pm1-ug.stp #91739, edge 2
  }
  else {
    if (ME.Error() == BRepLib_DifferentPointsOnClosedCurve) {
      // The Edge could be closed and trimmed by 2 Differents
      // Vertices
      if (C1->IsClosed()) {
	// Attention : il faudra mettre a jour la topologie des
	// vertex pour avoir des edges cul a cul ...... Good Luck!
	aTool.Bind (Vend,V1);
	TopoDS_Shape aLocalShape = V1.Reversed();
	V2 = TopoDS::Vertex(aLocalShape);
	ME.Init(C1, V1, V2, U1, U2);
	if (ME.IsDone()) {
	  TP->AddWarning(EC, "Wrong topology corrected : Closed Edge with TWO different Vertices");
	  E = ME.Edge();
	}
	else {
	  DecodeMakeEdgeError(ME, C3D, C1, V1, V2, U1, U2, aTool, EC);
	  E = MakeEdge (C1,V1,V2,U1,U2);//preci
	  myError = StepToTopoDS_TranslateEdgeDone; // ????
	  done = Standard_True;
	  //		return;	  	      
        }
      }
      else {
	// Then, this is should be coded as degenerated
	// To be performed later !!!
//	   DecodeMakeEdgeError(ME, C3D, C1, V1, V2, U1, U2, aTool, EC);
	myError = StepToTopoDS_TranslateEdgeDone; // ????
	//  Bon, on la fait cette petite edge, mais faudra repasser
	//  pour l enlever ET FUSIONNER LES VERTEX, pour tout le shell !
	//  courbe trop petite pour etre mise -> fait planter
	done = Standard_True;
	if (!V1.IsSame(V2)) {
	  TP->AddFail(EC, "This edge has null arc length");
	  gp_Pnt P1 = BRep_Tool::Pnt(V1);
	  gp_Pnt P2 = BRep_Tool::Pnt(V2);
	  gp_Vec avec (P1,P2);  gp_Dir adir (avec);  gp_Lin alin (P1,adir);
	  C1 = new Geom_Line (alin);
	  U1 = 0.;  U2 = P1.Distance(P2);
	  E = MakeEdge (C1,V1,V2,U1,U2);//,preci
	} 
	else {
	  TP->AddFail(EC,"NULL EDGE, SKIPPED");
	  myResult.Nullify();
	  return;	  
	}
      }
    }
    else {
      DecodeMakeEdgeError(ME, C3D, C1, V1, V2, U1, U2, aTool, EC);
      E = MakeEdge (C1,V1,V2,U1,U2);//,preci
      myError = StepToTopoDS_TranslateEdgeDone; // ????
      done = Standard_True;
    }
  }
}


// ============================================================================
// Method  : MakePCurve
// Purpose : Computes an individual pcurve (i.e. curve 2d)
// ============================================================================
Handle(Geom2d_Curve)  StepToTopoDS_TranslateEdge::MakePCurve
  (const Handle(StepGeom_Pcurve)& PCU, const Handle(Geom_Surface)& ConvSurf) const
{
  Handle(Geom2d_Curve) C2d;
  const Handle(StepRepr_DefinitionalRepresentation) DRI = PCU->ReferenceToCurve();
  if( DRI.IsNull()) return C2d;
  const Handle(StepGeom_Curve) StepCurve = Handle(StepGeom_Curve)::DownCast(DRI->ItemsValue(1));
  if (StepToGeom_MakeCurve2d::Convert(StepCurve,C2d)) {
    // -- if the surface is a RectangularTrimmedSurface, 
    // -- send the BasisSurface.
    C2d = UnitsMethods::DegreeToRadian(C2d, ConvSurf);
  }
  return C2d;
}


// ============================================================================
// Method  : Value
// Purpose : Returns the mapped edge
// ============================================================================

const TopoDS_Shape& StepToTopoDS_TranslateEdge::Value() const 
{
  StdFail_NotDone_Raise_if(!done,"");
  return myResult;
}

// ============================================================================
// Method  : Error
// Purpose : Returns the error code
// ============================================================================

StepToTopoDS_TranslateEdgeError StepToTopoDS_TranslateEdge::Error() const
{
  return myError;
}
