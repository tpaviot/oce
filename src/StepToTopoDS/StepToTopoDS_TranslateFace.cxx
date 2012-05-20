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

// pdn 30.11.98: fixes improved
// pdn 20.12.98: to keep pcurves
// pdn 28.12.98: PRO10366 shifting pcurve between two singularities
//:p4 abv, pdn 23.02.99: PRO9234 #15720: call BRepTools::Update() for faces
//:q7 abv 23.03.99: bm4_al_eye.stp #53710: remove pseudo-seams
//    rln 31.03.99 S4135: prohibit fixing intersection of non-adjacent edges (temporarily)
//#4  szv          S4163: optimization
//%19 pdn 17.04.99 using ShapeFix_Wire::FixEdgeCurves instead of ShapeFix_PCurves
//    smh 31.01.01 Bad data in file : case of vertex loop on plane face
// sln 01.10.2001 BUC61003. StepToTopoDS_TranslateFace::Init function is corrected (verifying  Handle(...).IsNull() is added)
#include <StepToTopoDS_TranslateFace.ixx>

#include <StepToTopoDS.hxx>

#include <StepToGeom_MakeSurface.hxx>

#include <StepToTopoDS_TranslateVertexLoop.hxx>
#include <StepToTopoDS_TranslatePolyLoop.hxx>
#include <StepToTopoDS_TranslateEdgeLoop.hxx>

#include <StepShape_EdgeCurve.hxx>
#include <StepShape_VertexLoop.hxx>
#include <StepShape_EdgeLoop.hxx>
#include <StepShape_PolyLoop.hxx>
#include <StepGeom_Surface.hxx>
#include <StepShape_FaceBound.hxx>
#include <StepShape_FaceOuterBound.hxx>
#include <StepShape_OrientedEdge.hxx>
#include <StepShape_Edge.hxx>

//#3 rln 16/02/98
#include <BRep_TEdge.hxx>
#include <BRep_TVertex.hxx>

#include <Geom_BoundedSurface.hxx>
#include <Geom_Plane.hxx>
#include <Geom_Surface.hxx>
#include <GeomAbs_Shape.hxx>
#include <GeomAdaptor_Surface.hxx>
#include <GeomAdaptor_HSurface.hxx>
//#include <GeomAdaptor_Curve.hxx>
//#include <GeomAdaptor_CurveOnSurface.hxx>

#include <Geom2d_Curve.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>//#3 rln 16/02/98
#include <TopoDS_Face.hxx>
#include <TopoDS_Vertex.hxx>

#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>//rln 28/01/98

#include <TopoDS_Wire.hxx>
#include <BRepTools.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRep_Builder.hxx>//rln 28/01/98
#include <BRep_Tool.hxx>
#include <Transfer_TransientProcess.hxx>
#include <Precision.hxx>

//  Provisoire, pour VertexLoop
#include <Geom_SphericalSurface.hxx>
#include <Geom_ToroidalSurface.hxx>
#include <StepGeom_OffsetSurface.hxx> //:d4
#include <StepGeom_BSplineSurfaceForm.hxx>
#include <StepGeom_BSplineSurface.hxx>
#include <ShapeAlgo.hxx>
#include <ShapeAlgo_AlgoContainer.hxx>
#include <TopoDS_Iterator.hxx>

// To proceed with I-DEAS-like STP (ssv; 15.11.2010)
#include <TCollection_HAsciiString.hxx>

//#define DEBUG

// ============================================================================
// Method  : StepToTopoDS_TranslateFace::StepToTopoDS_TranslateFace
// Purpose : Empty Constructor
// ============================================================================

StepToTopoDS_TranslateFace::StepToTopoDS_TranslateFace()
{
  done = Standard_False;
}

// ============================================================================
// Method  : StepToTopoDS_TranslateFace::StepToTopoDS_TranslateFace
// Purpose : Constructor with a FaceSurface and a Tool
// ============================================================================

StepToTopoDS_TranslateFace::StepToTopoDS_TranslateFace
(const Handle(StepShape_FaceSurface)& FS, StepToTopoDS_Tool& T, StepToTopoDS_NMTool& NMTool)
{
  Init(FS, T, NMTool);
}

// ============================================================================
// Method  : Init
// Purpose : Init with a FaceSurface and a Tool
// ============================================================================

void StepToTopoDS_TranslateFace::Init
(const Handle(StepShape_FaceSurface)& FS, StepToTopoDS_Tool& aTool, StepToTopoDS_NMTool& NMTool)
{
  done = Standard_True;
  if (aTool.IsBound(FS)) {
    myResult = TopoDS::Face(aTool.Find(FS));
    myError  = StepToTopoDS_TranslateFaceDone;
    done     = Standard_True;
    return;
  }
  
  Handle(Transfer_TransientProcess) TP = aTool.TransientProcess();
  
  // ----------------------------------------------
  // Map the Face Geometry and create a TopoDS_Face
  // ----------------------------------------------
  
  Handle(StepGeom_Surface) StepSurf = FS->FaceGeometry();

   // sln 01.10.2001 BUC61003. If corresponding entity was read with error StepSurface may be NULL. In this case we exit from function
  if ( StepSurf.IsNull() ) {
    TP->AddFail(StepSurf," Surface has not been created");
    myError = StepToTopoDS_TranslateFaceOther;
    done = Standard_False;
    return;
  }

  // [BEGIN] Added to process non-manifold topology (ssv; 14.11.2010)
  if ( NMTool.IsActive() && NMTool.IsBound(StepSurf) ) {
    TopoDS_Shape existingShape = NMTool.Find(StepSurf);
    // Reverse shape's orientation for the next shell
    existingShape.Reverse();
    myResult = existingShape;
    myError  = StepToTopoDS_TranslateFaceDone;
    done = Standard_True;
    return;
  }
  // [END] Added to process non-manifold topology (ssv; 14.11.2010)

  if (StepSurf->IsKind(STANDARD_TYPE(StepGeom_OffsetSurface))) //:d4 abv 12 Mar 98
    TP->AddWarning(StepSurf," Type OffsetSurface is out of scope of AP 214");
  Handle(Geom_Surface) GeomSurf;
  if (!StepToGeom_MakeSurface::Convert(StepSurf,GeomSurf))
  {
    TP->AddFail(StepSurf," Surface has not been created");
    myError = StepToTopoDS_TranslateFaceOther;
    done = Standard_False;
    return;
  }
  // pdn to force bsplsurf to be periodic
  Handle(StepGeom_BSplineSurface) sgbss = Handle(StepGeom_BSplineSurface)::DownCast(StepSurf);
  if (!sgbss.IsNull()) {
/*
    StepGeom_BSplineSurfaceForm form = sgbss->SurfaceForm();
    if ((form == StepGeom_bssfCylindricalSurf)||
	(form == StepGeom_bssfConicalSurf)||
	(form == StepGeom_bssfSphericalSurf)||
	(form == StepGeom_bssfToroidalSurf)||
	(form == StepGeom_bssfSurfOfRevolution)||
	(form == StepGeom_bssfGeneralisedCone)||
        (form == StepGeom_bssfUnspecified))
*/
    {
      Handle(Geom_Surface) periodicSurf = ShapeAlgo::AlgoContainer()->ConvertToPeriodic (GeomSurf);
      if(!periodicSurf.IsNull()) {
	TP->AddWarning(StepSurf,"Surface forced to be periodic");
	GeomSurf = periodicSurf;
      }
    }
  }
    
  Standard_Boolean sameSense = FS->SameSense();

  // -- Statistics --
  aTool.AddContinuity (GeomSurf);
  
  TopoDS_Face   F;
  BRep_Builder B;
  B.MakeFace ( F, GeomSurf, Precision::Confusion() );
  
  // ----------------------------------
  // Iterate on each FaceBounds (Wires)
  // ----------------------------------
  
  Handle(StepShape_FaceBound) FaceBound;
  Handle(StepShape_Loop)      Loop;
  
  StepToTopoDS_TranslateVertexLoop myTranVL;
  StepToTopoDS_TranslatePolyLoop   myTranPL;
  StepToTopoDS_TranslateEdgeLoop   myTranEdgeLoop;
  
  Standard_Integer NbBnd = FS->NbBounds();

  // --  Critere de couture simple (CKY, JAN97)
  // surface periodique (typiquement un cylindre)
  // 2 face bounds, chacun avec un edge loop d une seule edge
  //  cette edge est fermee, c-a-d vtx-deb = vtx-fin (pour les deux edges)
  // est-ce suffisant (verifier que ce sont deux outer-bounds ... ?? comment ?)
  // Alors on peut dire : face a deux bords dont la couture manque
  // La couture est entre les deux vertex

//  TopoDS_Wire W1,W2;
//  Standard_Boolean fautcoudre =
//    ( (NbBnd == 2) && (GeomSurf->IsUClosed() || GeomSurf->IsVClosed()) );

  for (Standard_Integer i = 1; i <= NbBnd; i ++) {

#ifdef DEBUG
    cout << "    Processing Wire : " << i << endl;
#endif    
    FaceBound = FS->BoundsValue(i);
    Loop      = FaceBound->Bound();
    
    // ------------------------
    // The Loop is a VertexLoop
    // ------------------------
    
    if (Loop->IsKind(STANDARD_TYPE(StepShape_VertexLoop))) {
//:S4136      STF.Closed() = Standard_False;
//  PROBLEME si SPHERE ou TORE
//  Il faudra faire un wire complet, a condition que le point porte sur la face
//  En attendant, on ne fait rien
      Handle(StepShape_VertexLoop) VL = Handle(StepShape_VertexLoop)::DownCast(Loop);

      // abv 10.07.00 pr1sy.stp: vertex_loop can be wrong; so just make natural bounds
      if (GeomSurf->IsKind (STANDARD_TYPE(Geom_SphericalSurface)) ||
          GeomSurf->IsKind (STANDARD_TYPE(Geom_BSplineSurface)) )
      {
        BRepBuilderAPI_MakeFace mf (GeomSurf, Precision());
        for (TopoDS_Iterator it(mf); it.More(); it.Next()) 
          B.Add (F, it.Value());

        continue;
      }
      
      if (//GeomSurf->IsKind(STANDARD_TYPE(Geom_SphericalSurface)) ||
	  GeomSurf->IsKind(STANDARD_TYPE(Geom_ToroidalSurface)) ) {
//	TP->AddWarning(VL," VertexLoop on Cone or Torus NOT YET IMPLEMENTED");
	continue;
      }
      if (GeomSurf->IsKind(STANDARD_TYPE(Geom_Plane)) ) {
	TP->AddWarning(VL,"VertexLoop on plane is ignored");
	continue; //smh : BUC60809
      }
      myTranVL.SetPrecision(Precision());//gka
      myTranVL.SetMaxTol(MaxTol());
      myTranVL.Init(VL, aTool, NMTool);
      if (myTranVL.IsDone()) {
	B.Add ( F, myTranVL.Value() );
      }
      else {
	TP->AddWarning(VL," a VertexLoop not mapped to TopoDS");
      }
    }
    
    // ----------------------
    // The Loop is a PolyLoop
    // ----------------------
    
    else if (Loop->IsKind(STANDARD_TYPE(StepShape_PolyLoop))) {
//:S4136      STF.Closed() = Standard_False;
      Handle(StepShape_PolyLoop) PL = Handle(StepShape_PolyLoop)::DownCast(Loop);
      F.Orientation ( FS->SameSense() ? TopAbs_FORWARD : TopAbs_REVERSED);
      myTranPL.SetPrecision(Precision()); //gka
      myTranPL.SetMaxTol(MaxTol());
      myTranPL.Init(PL, aTool, GeomSurf, F);
      if (myTranPL.IsDone()) {
	TopoDS_Wire W = TopoDS::Wire(myTranPL.Value());
	W.Orientation ( FaceBound->Orientation()  ? TopAbs_FORWARD : TopAbs_REVERSED);
	B.Add ( F, W );
      }
      else { 
	TP->AddWarning(PL," a PolyLoop not mapped to TopoDS");
      }
    }
    
    // -----------------------
    // The Loop is an EdgeLoop
    // -----------------------
    
    else if (Loop->IsKind(STANDARD_TYPE(StepShape_EdgeLoop))) {
//:S4136      if (STF.Closed()) {
//:S4136	Handle(StepShape_EdgeLoop) EL = 
//:S4136	  Handle(StepShape_EdgeLoop)::DownCast(FaceBound->Bound());
//:S4136	if (EL->NbEdgeList() != 1) STF.Closed() = Standard_False;
//:S4136      }

      TopoDS_Wire   W;
      myTranEdgeLoop.SetPrecision(Precision());  //gka
      myTranEdgeLoop.SetMaxTol(MaxTol());
      myTranEdgeLoop.Init(FaceBound, F, GeomSurf, StepSurf, sameSense, aTool, NMTool);

      if (myTranEdgeLoop.IsDone()) {

	W = TopoDS::Wire(myTranEdgeLoop.Value());

 	// STEP Face_Surface orientation :
 	// if the topological orientation is opposite to the geometric
 	// orientation of the surface => the underlying topological 
 	// orientation are not implicitly reversed
 	// this is the case in CAS.CADE => If the face_surface is reversed,
 	// the wire orientation has to be explictly reversed
	if (FaceBound->Orientation()) {
// *DTH*	  if (sameSense || GeomSurf->IsKind(STANDARD_TYPE(Geom_Plane)))
	  W.Orientation (sameSense ? TopAbs_FORWARD : TopAbs_REVERSED);
	}
	else {
// *DTH*	  if (sameSense || GeomSurf->IsKind(STANDARD_TYPE(Geom_Plane)))
	  W.Orientation (sameSense ? TopAbs_REVERSED : TopAbs_FORWARD);
	}
	// -----------------------------
	// The Wire is added to the Face      
	// -----------------------------
	
	B.Add ( F, W );
      }
      else {
	// Il y a eu un probleme dans le mapping : On perd la Face
	// (facon de parler ...) Pas de moyen aujourd hui de recuperer
	// au moins toutes les geometries (Points, Courbes 3D, Surface)
	TP->AddFail(Loop," EdgeLoop not mapped to TopoDS");
	//if(GeomSurf->IsKind(STANDARD_TYPE(Geom_BoundedSurface))) {
	//Standard_Real su1, sv1, su2, sv2;
	//GeomSurf->Bounds(su1, su2, sv1, sv2);
	//if(sv1 == -Precision::Infinite()) sv1 = 0.;
	//if(sv2 ==  Precision::Infinite()) sv2 = 1.;
	//BRepBuilderAPI_MakeFace mkf(GeomSurf,su1,su2,sv1,sv2);
	//if (mkf.IsDone()) {
	// done shall be standard false but no recipient to
	// to store uncompletally mapped topology
	// see Improvment Resquest DPA/126/95
	//myResult = mkf.Face();
	//done = Standard_True;
	//}
	//}

	// CKY JAN-97 : un Wire manque, eh bien on continue quand meme !!
	//  sauf si OuterBound : la c est quand meme pas bien normal ...
	if (FaceBound->IsKind(STANDARD_TYPE(StepShape_FaceOuterBound))) {
	  TP->AddWarning(FS,"No Outer Bound : Face not done");
//	return;
	}
	continue;
//	myError = StepToTopoDS_TranslateFaceOther;
//	done = Standard_False;
//	return;
      }
    }
    
    else { 
      // Type not yet implemented or non sens
      TP->AddFail(Loop," Type of loop not yet implemented");
#ifdef DEBUG
      cout << Loop->DynamicType() << endl;
#endif
      continue;
//      done    = Standard_False;
//      myError = StepToTopoDS_TranslateFaceOther;
//      return;
    }
  }

  F.Orientation ( FS->SameSense() ? TopAbs_FORWARD : TopAbs_REVERSED);
  aTool.Bind(FS,F);

  // Register face in NM tool (ssv; 14.11.2010)
  if ( NMTool.IsActive() )
    NMTool.Bind(StepSurf, F);

  myResult = F;
  myError  = StepToTopoDS_TranslateFaceDone;
  done     = Standard_True;
}


// ============================================================================
// Method  : Value 
// Purpose : Return the mapped Shape
// ============================================================================

const TopoDS_Shape& StepToTopoDS_TranslateFace::Value() const 
{
  StdFail_NotDone_Raise_if(!done,"");
  return myResult;
}

// ============================================================================
// Method  : Error
// Purpose : Return the TranslateFace error
// ============================================================================

StepToTopoDS_TranslateFaceError StepToTopoDS_TranslateFace::Error() const
{
  return myError;
}
