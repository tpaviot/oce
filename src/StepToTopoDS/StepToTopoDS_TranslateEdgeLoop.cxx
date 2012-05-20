// Created on: 1995-03-29
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

// gka 21.08.98 PRO7656
// gka 15.12.98 UKI60591 #1274560
//pdn 18.12.98 to keep pcurves
//:o0 abv 16.02.99: POLYLINE allowed as 3d curve of edge
//:   abv 07.04.99: S4136: improve tolerance management and dealing with pcurves
//    rln 02.06.99 removing #include <StepToTopoDS_DegeneratedTool.hxx>
//    smh 31.01.01 BUC60810 : IsNull protection
#include <StepToTopoDS_TranslateEdgeLoop.ixx>

#include <StepToTopoDS.hxx>
#include <StepToTopoDS_TranslateVertex.hxx>
#include <StepToTopoDS_TranslateEdge.hxx>
#include <StepToTopoDS_GeometricTool.hxx>
#include <ShapeAnalysis_Curve.hxx>
#include <StepToGeom_MakeCurve2d.hxx>
#include <StepToGeom_MakeCurve.hxx>

#include <Geom_RectangularTrimmedSurface.hxx>

#include <StepShape_EdgeLoop.hxx>
#include <StepShape_Edge.hxx>
#include <StepShape_OrientedEdge.hxx>
#include <StepGeom_Curve.hxx>
#include <StepShape_EdgeCurve.hxx>
#include <StepGeom_Pcurve.hxx>
//#include <StepGeom_Polyline.hxx>
#include <StepGeom_SurfaceCurve.hxx>
#include <StepRepr_DefinitionalRepresentation.hxx>
#include <StepGeom_PcurveOrSurface.hxx>

#include <BRep_Builder.hxx>
#include <BRep_Tool.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Vertex.hxx>

#include <BRep_TEdge.hxx>
#include <BRep_CurveRepresentation.hxx>
#include <BRep_ListOfCurveRepresentation.hxx>
#include <BRep_ListIteratorOfListOfCurveRepresentation.hxx>

#include <TopExp_Explorer.hxx>
#include <TopExp.hxx>

#include <TopLoc_Location.hxx>
#include <TopAbs.hxx>

#include <Geom_Surface.hxx>
#include <Geom_Plane.hxx>
#include <Geom_Curve.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom2d_BoundedCurve.hxx>
#include <Geom2d_Line.hxx>

#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>

#include <Precision.hxx>
#include <Interface_Static.hxx>
#include <Transfer_TransientProcess.hxx>
#include <TopoDS_Iterator.hxx>
#include <ShapeFix_EdgeProjAux.hxx>
#include <ShapeAnalysis_Edge.hxx>
#include <ShapeExtend_WireData.hxx>
#include <ShapeBuild_Edge.hxx>

#include <ShapeAlgo.hxx>
#include <ShapeAlgo_AlgoContainer.hxx>
#include <ShapeAlgo_ToolContainer.hxx>
#include <XSAlgo.hxx>
#include <XSAlgo_AlgoContainer.hxx>

// ============================================================================
// Method  : RemoveSinglePCurve
// Purpose : 
// ============================================================================

static void RemoveSinglePCurve (const TopoDS_Edge& aEdge, const TopoDS_Face& aFace)
{
  ShapeBuild_Edge().RemovePCurve (aEdge, aFace);
}

// ============================================================================
// Method  : RemovePCurves
// Purpose : 
// ============================================================================

static void RemovePCurves(const TopoDS_Wire& aWire, const TopoDS_Face& aFace)
{
  TopExp_Explorer EdgeExp(aWire, TopAbs_EDGE);
  while (EdgeExp.More()) {
    const TopoDS_Edge& myEdge = TopoDS::Edge(EdgeExp.Current());
    RemoveSinglePCurve(myEdge,aFace);
    EdgeExp.Next();
  }
}

// ============================================================================
// Method  : CheckPCurves
// Purpose : Checks the pcurves topological trimming parameter consistency
//           and deviation between 2D ans 3D  
// ============================================================================

static void CheckPCurves (TopoDS_Wire& aWire, const TopoDS_Face& aFace,
			  const Standard_Boolean isPlane,const Standard_Real preci )
{
  if (isPlane) { RemovePCurves (aWire,aFace);return; }
  BRep_Builder B;
  Standard_Real w1, w2, cf, cl;
  Handle(Geom_Surface) mySurf = BRep_Tool::Surface(aFace);
  
  Handle(ShapeExtend_WireData) sbwd = new ShapeExtend_WireData ( aWire );
  for (Standard_Integer i = 1; i <= sbwd->NbEdges(); i++) {
    const TopoDS_Edge& myEdge = sbwd->Edge(i);
//    B.SameRange( myEdge, Standard_True );
//    B.SameParameter ( myEdge, Standard_True ); 
    
    // First Check : 2D Parameters on Edge :
    // Case 1 : w1 == w2 illegal => Drop the PCurve
    // Case 2 : on bounded curve w1 < FirstParameter => w1 = FirstParameter
    //                           w2 > LastParameter  => w2 = LastParameter

    Handle(Geom2d_Curve) thePC;
    ShapeAnalysis_Edge sae;
    if (!sae.PCurve (myEdge, aFace, thePC, w1, w2, Standard_False )) {
      continue;
    }
    cf = thePC->FirstParameter();
    cl = thePC->LastParameter();
    
    if (w1 == w2) {
      RemoveSinglePCurve(myEdge,aFace);
#ifdef DEBUG      
      cout<<"Removing pcuve w1=w2"<<endl;
#endif      
      continue;
    }

    if (w1 < cf) {
      B.Range(myEdge, aFace, cf, w2);
      w1 = cf;
    }
    if (w2 > cl) {
      B.Range(myEdge, aFace, w1, cl);      
      w2 = cf;
    }
    
    // advanced check
    XSAlgo::AlgoContainer()->CheckPCurve (myEdge, aFace, preci, sbwd->IsSeam(i) );
  }
}

// ============================================================================
// Method  : StepToTopoDS_TranslateEdgeLoop::StepToTopoDS_TranslateEdgeLoop
// Purpose : Empty Constructor
// ============================================================================

StepToTopoDS_TranslateEdgeLoop::StepToTopoDS_TranslateEdgeLoop()
{
  done = Standard_False;
}

// ============================================================================
// Method  : StepToTopoDS_TranslateEdgeLoop::StepToTopoDS_TranslateEdgeLoop
// Purpose : Constructor with a FaceSurface and a Tool
// ============================================================================

StepToTopoDS_TranslateEdgeLoop::StepToTopoDS_TranslateEdgeLoop(const Handle(StepShape_FaceBound)& FB, 
                                                               const TopoDS_Face& Face,
                                                               const Handle(Geom_Surface)& GeomSurf,
                                                               const Handle(StepGeom_Surface)& StepSurf,
                                                               const Standard_Boolean sameSense,
                                                               StepToTopoDS_Tool& T,
                                                               StepToTopoDS_NMTool& NMTool) {
  Init(FB, Face, GeomSurf, StepSurf, sameSense, T, NMTool);
}

// ============================================================================
// Method  : Init
// Purpose : Init with a EdgeLoop and a Tool
// ============================================================================

void StepToTopoDS_TranslateEdgeLoop::Init(const Handle(StepShape_FaceBound)& FaceBound, 
                                          const TopoDS_Face& Face,
                                          const Handle(Geom_Surface)& GeomSurf,
                                          const Handle(StepGeom_Surface)& StepSurf,
                                          const Standard_Boolean sameSense,
                                          StepToTopoDS_Tool& aTool,
                                          StepToTopoDS_NMTool& NMTool) {
  done = Standard_True;
  Handle(StepShape_EdgeLoop) EL = 
    Handle(StepShape_EdgeLoop)::DownCast(FaceBound->Bound());

  if (aTool.IsBound(EL)) {
    myResult = TopoDS::Wire(aTool.Find(EL));
    myError  = StepToTopoDS_TranslateEdgeLoopDone;
    done     = Standard_True;
    return;
  }
  Standard_Integer modepcurve = Interface_Static::IVal("read.surfacecurve.mode");
//  0,1 : suivre le code,  2 : ne prendre que pcurve,  3 : ne prendre que C3D

  BRep_Builder B;
  Handle(Transfer_TransientProcess) TP = aTool.TransientProcess();
  
  Standard_Real preci = Precision();
  TopoDS_Wire   W;
  TopoDS_Edge   E;
  TopoDS_Vertex V;

//  Standard_Real U1,U2, U1a, U1b, U2a, U2b;
  
  Standard_Boolean isSeam, isLikeSeam;
  
  Handle(StepShape_Edge)         StepEdge, StepEdge1;
  Handle(StepShape_OrientedEdge) OrEdge1, OrEdge2;
  Handle(StepGeom_Curve) StepCurve, StepCurve1, StepCurve2;
//  Handle(StepGeom_Pcurve) StepPCurve, StepPCurve1, StepPCurve2;
  Handle(StepRepr_DefinitionalRepresentation) DRI, Dri1, Dri2;
  
  Handle(Geom2d_Curve) C2d, C2d1, C2d2, WhichC2d1, WhichC2d2;
// unused  gp_Pnt Pdeb, Pmil, Pfin, pV1, pV2;
  
  TopoDS_Edge   suspectE; //:f1, degEdge; 
  
  Standard_Integer j, NbEdge = EL->NbEdgeList();
  if( NbEdge == 0) {
    TP->AddWarning(EL,"Wire not done. EdgeLoop does not contain edges.");
    done = Standard_False;
    return;
  }
// PTV 16.09.2000 
// default value set as Standard_True (if not correct see logic of algorithm).
  Standard_Boolean hasPcurve = Standard_True;
  Standard_Boolean isPlane = GeomSurf->IsKind(STANDARD_TYPE(Geom_Plane));
  Handle(Geom_Surface) ConvSurf = GeomSurf;
  if (GeomSurf->IsKind(STANDARD_TYPE(Geom_RectangularTrimmedSurface))) {
    Handle(Geom_RectangularTrimmedSurface) theRTS =
      Handle(Geom_RectangularTrimmedSurface)::DownCast(GeomSurf);
    ConvSurf = theRTS->BasisSurface();
  }

  aTool.ComputePCurve(Standard_False);
  
  // What is the Wire Orientation
  Standard_Boolean ForwardWire = FaceBound->Orientation();

  // --- Initialize target Wire ---

  B.MakeWire(W);

//  Standard_Integer lastpcurve = 0;

  // -----------------------------------------------
  // Preparation : Make Vertices + Curves3d
  //  Hence, a closed curve limited by distinct vertices
  //  will give a unique vertex (if same coords)
  //
  // In addition : detect shared PCurve (cf SYRKO)
  //  This case may not be processed, PCurves has to be recomputed from scratch
  // -----------------------------------------------
//  Standard_Integer theSame = 1; //gka 15.12.98
  
  for (j=1; j<=NbEdge; j++ ) {
    OrEdge1  = EL->EdgeListValue(j);
    StepEdge = OrEdge1->EdgeElement();
//    if(j>1 && StepEdge == StepEdge1) theSame++; //gka 15.12.98
    StepEdge1 = StepEdge;                         //
    Handle(StepShape_EdgeCurve) EC = Handle(StepShape_EdgeCurve)::DownCast(StepEdge);
    Handle(StepGeom_Curve) C = EC->EdgeGeometry();
    if (C->IsKind(STANDARD_TYPE(StepGeom_SurfaceCurve))) {
      Handle(StepGeom_SurfaceCurve) Sc = Handle(StepGeom_SurfaceCurve)::DownCast(C);
      C = Sc->Curve3d();
//      if (modepcurve != 3) {
//	lastpcurve = StepToTopoDS_GeometricTool::PCurve (Sc,StepSurf,StepPCurve1);
//	if (StepPCurve1 == StepPCurve) modepcurve = -1;
//	StepPCurve = StepPCurve1;
//      }
    }
////    else if (C->IsKind(STANDARD_TYPE(StepGeom_Polyline))) {  }
//    else if (C->IsKind(STANDARD_TYPE(StepGeom_Pcurve))) {
//      if (modepcurve != 3) {
//	if (C == StepPCurve) modepcurve = -1;
//	StepPCurve = Handle(StepGeom_Pcurve)::DownCast(C);
//      }
//    }
    Handle(Geom_Curve) C1;
    if (!C.IsNull()) {
      C1 = Handle(Geom_Curve)::DownCast (TP->FindTransient(C));
      if (C1.IsNull()) {
        if (StepToGeom_MakeCurve::Convert(C,C1))
          TP->BindTransient (C,C1);
      }
    }

    Handle(StepShape_Vertex) Vstart, Vend;
    if (EC->SameSense()) {
      Vstart = EC->EdgeStart();
      Vend   = EC->EdgeEnd();
    }
    else {
      Vend   = EC->EdgeStart();
      Vstart = EC->EdgeEnd();
    }

    Standard_Boolean istV = aTool.IsBound(Vstart);
    Standard_Boolean iseV = aTool.IsBound(Vend);
    TopoDS_Vertex V1, V2;
    StepToTopoDS_TranslateVertex myTranVertex1(Vstart, aTool, NMTool);
    StepToTopoDS_TranslateVertex myTranVertex2(Vend, aTool, NMTool);

    if (myTranVertex1.IsDone()) {
      V1 = TopoDS::Vertex(myTranVertex1.Value());
    }
//    if (Vend == Vstart) {  cas normal deja assure par aTool
//      aTool.Bind (Vend,V1);
//    }
//    else
    if (myTranVertex2.IsDone()) {
      V2 = TopoDS::Vertex(myTranVertex2.Value());
      gp_Pnt p1 = BRep_Tool::Pnt(V1);
      gp_Pnt p2 = BRep_Tool::Pnt(V2);
      if (p1.Distance(p2) <= Precision::Confusion() ) { //:S4136: preci) {
	Standard_Boolean Fixed = Standard_True;
	if(!iseV) aTool.Bind(Vend,V1); //gka 21.08.1998 bug PRO7656 
	else if(!istV)  aTool.Bind (Vstart,V2);
	else aTool.Bind (Vend,V1);
        //Fixed = Standard_False;
	//aTool.Bind (Vend,V1);
	if (!C1.IsNull() && !C1->IsClosed() && Fixed)
	  TP->AddWarning(EL->EdgeListValue(j),
			 "Vertex of same coordinates, set confused");
      }
    }
  }
//  if (NbEdge!=1 && theSame == NbEdge) {
//    TP->AddWarning(EL,"Wire was ignored. All edges are the same.");
//    done = Standard_False;
//    return;
//  }
//  Fixed=Standard_True;
//  if (modepcurve == -1) {
//    modepcurve = 3;
//    TP->AddWarning(EL,"Shared Pcurve not allowed, Pcurves are recomputed");
//  }

  //:f6 abv 29 Apr 98: BUC50070 #3815: make sure that each two edges are
  // connected by the same vertex; else check that vertices confuse
  // and make it be one vertex
  // NOTE: this is done only for the case if at least one of edges 
  // was not yet translated; else nothing will help
  for (j=1; j<=NbEdge; j++ ) {
    OrEdge1  = EL->EdgeListValue ( j );
    OrEdge2  = EL->EdgeListValue ( j < NbEdge ? j + 1 : 1 );
    Handle(StepShape_EdgeCurve) EC1 = 
      Handle(StepShape_EdgeCurve)::DownCast ( OrEdge1->EdgeElement() );
    Handle(StepShape_EdgeCurve) EC2 = 
      Handle(StepShape_EdgeCurve)::DownCast ( OrEdge2->EdgeElement() );

    Handle(StepShape_Vertex) Vs1, Vs2,Vs11,Vs22;
    Vs1 = ( OrEdge1->Orientation() ? EC1->EdgeEnd() : EC1->EdgeStart() );
    Vs2 = ( OrEdge2->Orientation() ? EC2->EdgeStart() : EC2->EdgeEnd() );

    Vs11 = ( OrEdge1->Orientation() ?  EC1->EdgeStart() : EC1->EdgeEnd());
    Vs22 = ( OrEdge2->Orientation() ?  EC2->EdgeEnd() : EC2->EdgeStart() );

    if((Vs1 == Vs2) || (Vs1 == Vs22) || (Vs2 == Vs11) || (Vs22 == Vs11)) continue;
    //??    if ( Vs1.IsSame(Vs2) ) continue; // OK

    StepToTopoDS_TranslateVertex myTranVertex1 (Vs1, aTool, NMTool);
    StepToTopoDS_TranslateVertex myTranVertex2 (Vs2, aTool, NMTool);

    TopoDS_Vertex V1, V2;
    if ( myTranVertex1.IsDone() ) 
      V1 = TopoDS::Vertex ( myTranVertex1.Value() );
    if ( myTranVertex2.IsDone() ) 
      V2 = TopoDS::Vertex ( myTranVertex2.Value() );
    if ( V1.IsNull() || V2.IsNull() ) continue; // not treated
    if ( V1.IsSame(V2) ) continue; // OK

    gp_Pnt p1 = BRep_Tool::Pnt(V1);
    gp_Pnt p2 = BRep_Tool::Pnt(V2);
    Standard_Boolean locFixed = Standard_True;
    if (p1.Distance(p2) <= preci) {
      if ( ! aTool.IsBound ( EC1 ) ) aTool.Bind ( Vs1, V2 );
      else if ( ! aTool.IsBound ( EC2 ) ) aTool.Bind ( Vs2, V1 );
      else locFixed = Standard_False;
    }
    else locFixed = Standard_False;
    if ( locFixed ) TP->AddWarning(EL,"Adjacent edges do not have common vertex; set confused");
    else TP->AddWarning(EL,"Adjacent edges are not connected");
  }

  // -----------------------------------------------
  // Iteration on each Oriented Edge of the EdgeLoop
  // -----------------------------------------------

  for (j=1; j<=NbEdge; j++ ) {

    Standard_Boolean ThereIsLikeSeam = Standard_False;
    
#ifdef DEBUG
    cout << "      Processing Edge :" << j << endl;
#endif

    OrEdge1  = EL->EdgeListValue(j);
    StepEdge = OrEdge1->EdgeElement();
    Handle(StepShape_EdgeCurve) EC = Handle(StepShape_EdgeCurve)::DownCast(StepEdge);
    
    // ----------------
    // Map the StepEdge
    // ----------------
    
    StepToTopoDS_TranslateEdge myTranEdge;
    
    myTranEdge.SetPrecision(preci);
    myTranEdge.SetMaxTol(MaxTol());
    myTranEdge.Init(OrEdge1, aTool, NMTool);

    if (myTranEdge.IsDone()) {
      
      E = TopoDS::Edge(myTranEdge.Value());
      if (E.IsNull()) continue;  // NULL, on saute

      Handle(StepGeom_Curve) C = EC->EdgeGeometry();

      if (OrEdge1->Orientation() && EC->SameSense()) 
	E.Orientation(TopAbs_FORWARD);
      else if (!OrEdge1->Orientation() && !EC->SameSense())
	E.Orientation(TopAbs_FORWARD);
      else E.Orientation(TopAbs_REVERSED);

      isSeam = isLikeSeam = Standard_False;
      
      // ------------------------------------------
      // Map the StepEdge parametric representation
      // ------------------------------------------

      // --------------------------------------------
      // CASE 1 : The Edge Geometry is of Pcurve Type
      // --------------------------------------------
      
      if (C->IsKind(STANDARD_TYPE(StepGeom_Pcurve))) {
	Handle(StepGeom_Pcurve) StepPCurve = Handle(StepGeom_Pcurve)::DownCast(C);
	C2d = myTranEdge.MakePCurve (StepPCurve,ConvSurf);
	// -- Statistics --
	aTool.AddContinuity (C2d);
      }

      // -----------------------------------------
      // CASE 2 : The curve is a SurfaceCurve i.e. 
      //           - a 3D Curve (mandatory)
      //           - 2 PCurveOrSurface
      //   If modepcurve = 3, PCurve are ignored here
      // -----------------------------------------

      else if (modepcurve == 3) {
	aTool.ComputePCurve(Standard_True);
	hasPcurve = Standard_False;
      }
      else if (C->IsKind(STANDARD_TYPE(StepGeom_SurfaceCurve)) ) {
	// recouvre les cas SeamCurve et IntersectionCurve
	
	Handle(StepGeom_SurfaceCurve) SurfCurve =
	  Handle(StepGeom_SurfaceCurve)::DownCast(C);

	Handle(StepGeom_Pcurve) StepPCurve, StepPCurve1, StepPCurve2;
	Standard_Integer lastpcurve = StepToTopoDS_GeometricTool::PCurve(SurfCurve,StepSurf,StepPCurve,0);
	hasPcurve = !StepPCurve.IsNull();

	// De toute facon, on recalcule

	if (isPlane) hasPcurve = Standard_False;

	// -------------------------------------------
	// ---        Special Mapping Cases :      ---
	// ---   the SurfaceCurve is a SeamCurve   ---
	// ---        or is like a seam curve      ---
	// ---         (see CATIA cylinder)        ---
	// -------------------------------------------
	isLikeSeam = StepToTopoDS_GeometricTool::IsLikeSeam(SurfCurve,StepSurf,StepEdge,EL);

	isSeam = StepToTopoDS_GeometricTool::IsSeamCurve(SurfCurve, StepSurf,StepEdge, EL);
	
	if (isSeam || isLikeSeam) {
	  // isLikeSeam = Two faces on the same Surface
	  StepPCurve1 = SurfCurve->AssociatedGeometryValue(1).Pcurve();
	  StepPCurve2 = SurfCurve->AssociatedGeometryValue(2).Pcurve();
	  if (StepPCurve1.IsNull() || StepPCurve2.IsNull()) hasPcurve = Standard_False; //smh : BUC60810
	  else {
	    C2d1 = myTranEdge.MakePCurve (StepPCurve1,ConvSurf);
	    C2d2 = myTranEdge.MakePCurve (StepPCurve2,ConvSurf);
	    hasPcurve = (!C2d1.IsNull() && !C2d2.IsNull());
	  }

	  if (isLikeSeam) {
	    suspectE = E;
	    ThereIsLikeSeam = Standard_True;
	    hasPcurve = Standard_True;
	  }
	}
	else if (hasPcurve) {
//  GeometricTool : Pcurve a retourne StepPCurve
	  while (lastpcurve > 0) {
	    C2d1 = myTranEdge.MakePCurve (StepPCurve,ConvSurf);
	    if (C2d1.IsNull()) {
	      hasPcurve = Standard_False;
	      break;
	    }
	    else C2d = C2d1;
	    lastpcurve = StepToTopoDS_GeometricTool::PCurve(SurfCurve,StepSurf,StepPCurve,lastpcurve);
	    // -- Statistics --
	    aTool.AddContinuity (C2d);
	  }
	}
	if (!hasPcurve) {
	  // The edge geometry has no 2D representation
	  aTool.ComputePCurve(Standard_True);
	}
      }
      
      // ----------------------------------------------------------
      // CASE 3 : The EdgeCurve Geometry is not a Pcurve 
      //          nor a SurfaceCurve (i.e. it is a single 3D curve)
      // ----------------------------------------------------------

      else {
	aTool.ComputePCurve(Standard_True);
	hasPcurve = Standard_False;
      }
      
      // ----------------------------------
      // update the edge with the pcurve(s)
      // ----------------------------------

      if (hasPcurve && (isSeam || ThereIsLikeSeam)) {

      // -----------------------------------------------------------
      // The Edge is a Seam Edge : The pcurve wich is FORWARD has to
      //                           be identified
      // -----------------------------------------------------------
      
	if ((!C2d1.IsNull()) && (!C2d2.IsNull())) {
	  TopAbs_Orientation CumulO, EdgeO, WireO, FaceO;
	  EdgeO = E.Orientation();
	  if (ForwardWire)  WireO = TopAbs_FORWARD;
	  else  	    WireO = TopAbs_REVERSED;
	  if (sameSense) FaceO = TopAbs_FORWARD;
	  else           FaceO = TopAbs_REVERSED;

	  CumulO = TopAbs::Compose(EdgeO, WireO);
	  CumulO = TopAbs::Compose(CumulO, FaceO);

	  Standard_Boolean ForwardEdge = (CumulO == TopAbs_FORWARD);

	  // if(!ThereIsLikeSeam) ForwardEdge = Standard_True;
	  Standard_Integer forwardPC =
	    ShapeAnalysis_Curve().SelectForwardSeam (C2d1,C2d2);
	  if (forwardPC == 0) {
	    TP->AddFail(StepEdge," Seam curve not mapped");
	    done = Standard_False;
	    myError = StepToTopoDS_TranslateEdgeLoopOther;
	    continue;
	  }
	  else if (!ForwardEdge) forwardPC = 3 - forwardPC;  // inverser 1-2

	  if (forwardPC == 1) {
	    if(isSeam) {
	      // When the edge is a Seam, it is better to find the topological
	      // trimming right now. 
	      // Remarque : pour bien faire, il faudrait, si necessaire, recalculer
	      //            les trois courbes de maniere a ce qu`elles soient
	      //            immediatement Same Range et Same Parameter.
	      B.UpdateEdge(E, C2d1, C2d2, Face, 0.);
//:S4136	      FindParameter(C2d1, C2d2, E, Face, preci);
	    }
	    else
	      B.UpdateEdge(E, C2d1, Face, 0.); //preci
	  }
	  else {
	    if(isSeam) {
	      // When the edge is a Seam, it is better to find the topological
	      // trimming right now. 
	      B.UpdateEdge(E, C2d2, C2d1, Face, 0.);
//:S4136	      FindParameter(C2d1, C2d2, E, Face, preci);
	    }
	    else
	      B.UpdateEdge(E, C2d2, Face, 0.);
	  }
	}
	else {
	  TP->AddFail(StepEdge," Seam curve not mapped");
	  done = Standard_False;
	  myError = StepToTopoDS_TranslateEdgeLoopOther;
	  continue;
	}
      }
      else {
	
	// ---------------------------
	// The Edge is a "normal" edge
	// ---------------------------
	
	if (hasPcurve) {
	  if ( !C2d.IsNull() && !isLikeSeam ) {
	    B.UpdateEdge(E, C2d, Face, 0.);
	  }
	  else {
	    TP->AddFail(StepEdge," Edge: Trimming of 2D curve failed");
	    //	  cout << "2D curve type : " << C2d->DynamicType() << endl;
	    done = Standard_False;
	    myError = StepToTopoDS_TranslateEdgeLoopOther;
	    continue;
	  }
	}
      }

      if (!E.IsNull()) {
//	B.Add(W,E);   -- DABORD regarder degeneree manquante !!!
      }
      else {
	TP->AddFail(StepEdge," an Edge not mapped");
	done = Standard_False;
	myError = StepToTopoDS_TranslateEdgeLoopOther;
//	continue;
      }
    }
    else { // The Edge is Not mapped => switch to next wire ?
      TP->AddFail(StepEdge," an Edge not mapped");
      done = Standard_False;
      myError = StepToTopoDS_TranslateEdgeLoopOther;
//      continue;
    }

    if (done) B.Add (W,E);  // on le fait ici. Sauf si erreur rencontree ... !
    else {
      Handle(StepShape_Vertex) Vs1, Vs2;
      Vs1 = StepEdge->EdgeStart();
      Vs2 = StepEdge->EdgeEnd();
      if(!Vs1.IsNull() && !Vs2.IsNull() && Vs1==Vs2) {
        done = Standard_True;
        TP->AddFail(EL," Edge with equal vertices failed, scipped");
      }
    }
  }

  // The EdgeLoop is binded in the Wire

  if (!done) {
    TP->AddFail(EL,"At least one edge failed : wire not done");
    return;
  }
  aTool.Bind(EL, W);
  
  // ----------------------------------------------
  // Computes the 2D parameter of Vertices on Edges
  // ----------------------------------------------
  //pdn compute parameter of Vertices using progecting
  if (!aTool.ComputePCurve()) 
    for (TopoDS_Iterator EdgeIt(W);EdgeIt.More();EdgeIt.Next()){
      TopoDS_Edge edge = TopoDS::Edge(EdgeIt.Value());
      Handle(ShapeFix_EdgeProjAux) myEdgePro = ShapeAlgo::AlgoContainer()->ToolContainer()->EdgeProjAux();
      myEdgePro->Init (Face, edge);
      myEdgePro->Compute(preci);
      if (myEdgePro->IsFirstDone() && myEdgePro->IsLastDone()) {
        if (Abs (myEdgePro->FirstParam() - myEdgePro->LastParam()) < Precision::PConfusion())
          continue;
        B.Range(edge, Face,myEdgePro->FirstParam(), myEdgePro->LastParam());
      }
      else {
        RemoveSinglePCurve(edge, Face);
#ifdef DEBUG
        cout <<"Removing after prj"<<endl;
#endif
      }
    }       
    
  myResult = W;
  myError  = StepToTopoDS_TranslateEdgeLoopDone;
  done     = Standard_True;
  //  Check des PCurves SYSTEMATIQUE, s il n y en a que quelques unes
//  if (isPlane) RemovePCurves (W, Face);
// else         CheckPCurves  (W, Face);
  CheckPCurves  (W, Face,isPlane,preci);

  // --------------------------------------------      
  // Control the UVLoop (Closed and Head To Tail)
  // --------------------------------------------
  
//  StepToTopoDS_GeometricToolError tError = 
//    StepToTopoDS_GeometricTool::CloseUV(W, Face, aTool);
//  if(tError != StepToTopoDS_GeometricToolDone) {
//    TP->AddWarning(StepEdge,StepToTopoDS::DecodeGeometricToolError(tError));
//  }
  return;
}


// ============================================================================
// Method  : Value 
// Purpose : Return the mapped Shape
// ============================================================================

const TopoDS_Shape& StepToTopoDS_TranslateEdgeLoop::Value() const 
{
  StdFail_NotDone_Raise_if(!done,"");
  return myResult;
}

// ============================================================================
// Method  : Error
// Purpose : Return the TranslateEdgeLoop error
// ============================================================================

StepToTopoDS_TranslateEdgeLoopError StepToTopoDS_TranslateEdgeLoop::Error() const
{
  return myError;
}

