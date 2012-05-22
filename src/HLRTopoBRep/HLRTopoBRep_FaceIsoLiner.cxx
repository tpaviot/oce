// Created on: 1995-01-05
// Created by: Christophe MARION
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



#include <HLRTopoBRep_FaceIsoLiner.ixx>
#include <TopAbs.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopTools_Array1OfShape.hxx>
#include <TColStd_Array1OfBoolean.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
//#include <BRepAdaptor_Curve2d.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <BRepTools.hxx>
#include <BRep_Tool.hxx>
#include <BRep_Builder.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2dHatch_Hatcher.hxx>
#include <Geom2dHatch_Intersector.hxx>
#include <HatchGen_ErrorStatus.hxx>
#include <HatchGen_Domain.hxx>
#include <HatchGen_PointOnHatching.hxx>
#include <HatchGen_PointOnElement.hxx>
#include <Precision.hxx>

const Standard_Real IntersectorConfusion = 1.e-10;
const Standard_Real IntersectorTangency  = 1.e-10;
const Standard_Real HatcherConfusion2d   = 1.e-8;
const Standard_Real HatcherConfusion3d   = 1.e-8;
const Standard_Real Infinite = 100.;

//=======================================================================
// Function : Perform
// Purpose  : Builds isoparametric curves with a hatcher.
//=======================================================================

void HLRTopoBRep_FaceIsoLiner::Perform (const Standard_Integer FI,
					const TopoDS_Face& F,
					HLRTopoBRep_Data& DS,
					const Standard_Integer nbIsos)
{
  Standard_Real UMin, UMax, VMin, VMax, U1, U2;
  Standard_Integer ne = 0;
  //BRep_Builder Builder;
  TopoDS_Edge Edge;
  TopExp_Explorer ExpEdges;
  TopoDS_Face TF = F;
  TF.Orientation (TopAbs_FORWARD);
  gp_Pnt2d P;
  gp_Pnt P1, P2;
  TopoDS_Vertex V1U, V2U, V1V, V2V;

  Geom2dHatch_Intersector Intersector
    (IntersectorConfusion,IntersectorTangency);
  Geom2dHatch_Hatcher Hatcher 
    (Intersector,HatcherConfusion2d,HatcherConfusion3d,Standard_True);

  BRepTools::UVBounds (TF, UMin, UMax, VMin, VMax);
  Standard_Boolean InfiniteUMin = Precision::IsNegativeInfinite (UMin);
  Standard_Boolean InfiniteUMax = Precision::IsPositiveInfinite (UMax);
  Standard_Boolean InfiniteVMin = Precision::IsNegativeInfinite (VMin);
  Standard_Boolean InfiniteVMax = Precision::IsPositiveInfinite (VMax);

  if (InfiniteUMin && InfiniteUMax) {
    UMin = - Infinite;
    UMax =   Infinite;
  }
  else if (InfiniteUMin)
    UMin = UMax - Infinite;
  else if (InfiniteUMax)
    UMax = UMin + Infinite;

  if (InfiniteVMin && InfiniteVMax) {
    VMin = - Infinite;
    VMax =   Infinite;
  }
  else if (InfiniteVMin)
    VMin = VMax - Infinite;
  else if (InfiniteVMax)
    VMax = VMin + Infinite;
  
  for (ExpEdges.Init (TF, TopAbs_EDGE); // Edges of the face TF
       ExpEdges.More();
       ExpEdges.Next()) ne++;

  if (DS.FaceHasIntL(TF)) {             // OutLines built on face TF.
    
    TopTools_ListIteratorOfListOfShape itE;
    for(itE.Initialize(DS.FaceIntL(TF));
	itE.More();
	itE.Next()) 
      ne++;
  }

  TopTools_Array1OfShape SH(1,ne);
  TColStd_Array1OfBoolean IL(1,ne); // internal OutLine

  for (ExpEdges.Init (TF, TopAbs_EDGE);
       ExpEdges.More();
       ExpEdges.Next()) {
    Standard_Integer IndE;
    const TopoDS_Edge& newE = TopoDS::Edge(ExpEdges.Current());
    const Handle(Geom2d_Curve) PC =
      BRep_Tool::CurveOnSurface (newE, TF, U1, U2);
    if(   Abs(PC->FirstParameter() - U1) <= Precision::PConfusion() 
       && Abs(PC->LastParameter()  - U2) <= Precision::PConfusion()) { 
      IndE = Hatcher.AddElement (PC,  newE.Orientation());      
    }
    else { 
      Handle (Geom2d_TrimmedCurve) TPC =
	new Geom2d_TrimmedCurve (PC, U1, U2);
      IndE = Hatcher.AddElement (TPC, newE.Orientation());
    }
    SH(IndE) = newE;
    if (DS.IsOutLFaceEdge(TF,newE)) IL(IndE) = Standard_True;
    else                            IL(IndE) = Standard_False;
  }
  
  if (DS.FaceHasIntL(TF)) { // get the internal OutLines built on face F.
    TopTools_ListIteratorOfListOfShape itE;
    for(itE.Initialize(DS.FaceIntL(TF));
	itE.More();
	itE.Next()) {
      Standard_Integer IndE;
      const TopoDS_Edge& newE = TopoDS::Edge(itE.Value());
      const Handle(Geom2d_Curve) PC =
	BRep_Tool::CurveOnSurface (newE, TF, U1, U2);
      if(   Abs(PC->FirstParameter() - U1) <= Precision::PConfusion() 
	 && Abs(PC->LastParameter()  - U2) <= Precision::PConfusion()) { 
	IndE = Hatcher.AddElement (PC,  TopAbs_INTERNAL);      
      }
      else { 
	Handle (Geom2d_TrimmedCurve) TPC =
	  new Geom2d_TrimmedCurve (PC, U1, U2);
	IndE = Hatcher.AddElement (TPC, TopAbs_INTERNAL);
      }
      SH(IndE) = newE;
      IL(IndE) = Standard_True;
    }
  }

  //-----------------------------------------------------------------------
  // Creation des hachures.
  //-----------------------------------------------------------------------
  
  BRepAdaptor_Surface Surface (TF);
  Standard_Real Tolerance = BRep_Tool::Tolerance (TF);
  
  Standard_Integer IIso;
  Standard_Real DeltaU = Abs (UMax - UMin);
  Standard_Real DeltaV = Abs (VMax - VMin);
  Standard_Real Confusion = Min (DeltaU, DeltaV) * HatcherConfusion3d;
  Hatcher.Confusion3d (Confusion);
  
  //-----------------------------------------------------------------------
  // Courbes Iso U.
  //-----------------------------------------------------------------------
  
  Standard_Real StepU = DeltaU / (Standard_Real) nbIsos;
  if (StepU > Confusion) {
    Standard_Real UPrm = UMin + StepU / 2.;
    gp_Dir2d Dir (0., 1.);

    for (IIso = 1; IIso <= nbIsos; IIso++) {
      gp_Pnt2d Ori (UPrm, 0.);
      Handle (Geom2d_Line) IsoLine = new Geom2d_Line (Ori, Dir);
      
      Standard_Integer IndH = Hatcher.AddHatching (IsoLine);
      Hatcher.Trim (IndH);
      if (Hatcher.TrimDone (IndH) && !Hatcher.TrimFailed (IndH))
	Hatcher.ComputeDomains (IndH);
      if (!Hatcher.IsDone (IndH)) {
	cout << "HLRTopoBRep::MakeIsoLines : Face " << FI << endl;
	cout << "U iso of parameter: " << UPrm;
	switch (Hatcher.Status (IndH)) {
	case HatchGen_NoProblem          :
	  cout << " No Problem"          << endl;
	  break;
	case HatchGen_TrimFailure        :
	  cout << " Trim Failure"        << endl;
	  break;
	case HatchGen_TransitionFailure  :
	  cout << " Transition Failure"  << endl;
	  break;
	case HatchGen_IncoherentParity   :
	  cout << " Incoherent Parity"   << endl;
	  break;
	case HatchGen_IncompatibleStates :
	  cout << " Incompatible States" << endl;
	  break;
	}
	Hatcher.RemHatching (IndH);
	continue;
      }
      
      Standard_Integer NbDom = Hatcher.NbDomains (IndH);
      if (NbDom > 0) {

	for (Standard_Integer IDom = 1; IDom <= NbDom; IDom++) {
	  const HatchGen_Domain& Dom = Hatcher.Domain (IndH, IDom);
	  Standard_Real U1 = Dom.HasFirstPoint()  ? 
	    Dom.FirstPoint().Parameter()  : VMin - Infinite;
	  Standard_Real U2 = Dom.HasSecondPoint() ? 
	    Dom.SecondPoint().Parameter() : VMax + Infinite;
	  IsoLine->D0 (U1, P);
	  Surface.D0 (P.X(), P.Y(), P1);
	  IsoLine->D0 (U2, P);
	  Surface.D0 (P.X(), P.Y(), P2);
	  if (Dom.HasFirstPoint()) { // Iso U - Premier point
	    const HatchGen_PointOnHatching& PntH = Dom.FirstPoint();

	    for (Standard_Integer IPntE = 1;
		 IPntE <= PntH.NbPoints();
		 IPntE++) {
	      const HatchGen_PointOnElement& PntE = PntH.Point(IPntE);
	      V1U = HLRTopoBRep_FaceIsoLiner::MakeVertex
		(TopoDS::Edge(SH(PntE.Index())),
		 P1,PntE.Parameter(),Tolerance,DS);
	      if (IL(PntE.Index())) DS.AddOutV(V1U);
	    }
	  }
	  if (Dom.HasSecondPoint()) { // Iso U - Deuxieme point
	    const HatchGen_PointOnHatching& PntH = Dom.SecondPoint();
	    
	    for (Standard_Integer IPntE = 1;
		 IPntE <= PntH.NbPoints();
		 IPntE++) {
	      const HatchGen_PointOnElement& PntE = PntH.Point(IPntE);
	      V2U = HLRTopoBRep_FaceIsoLiner::MakeVertex
		(TopoDS::Edge(SH(PntE.Index())),
		 P2,PntE.Parameter(),Tolerance,DS);
	      if (IL(PntE.Index())) DS.AddOutV(V2U);
	    }
	  }
	  if(!V1U.IsNull() && !V2U.IsNull())
	    HLRTopoBRep_FaceIsoLiner::MakeIsoLine
	      (F,IsoLine,V1U,V2U,U1,U2,Tolerance,DS);
	}
      }
      
      Hatcher.RemHatching (IndH);
      UPrm += StepU;
    }
  }
  
  //-----------------------------------------------------------------------
  // Courbes Iso V.
  //-----------------------------------------------------------------------
  
  Standard_Real StepV = DeltaV / (Standard_Real) nbIsos;
  if (StepV > Confusion) {
    Standard_Real VPrm = VMin + StepV / 2.;
    gp_Dir2d Dir (1., 0.);

    for (IIso = 1; IIso <= nbIsos; IIso++) {
      gp_Pnt2d Ori (0., VPrm);
      Handle (Geom2d_Line) IsoLine = new Geom2d_Line (Ori, Dir);
      
      Standard_Integer IndH = Hatcher.AddHatching (IsoLine);
      Hatcher.Trim (IndH);
      if (Hatcher.TrimDone (IndH) && !Hatcher.TrimFailed (IndH))
	Hatcher.ComputeDomains (IndH);
      if (!Hatcher.IsDone (IndH)) {
	cout << "HLRTopoBRep::MakeIsoLines : Face " << FI << endl;
	cout << "V iso of parameter: " << VPrm;
	switch (Hatcher.Status (IndH)) {
	case HatchGen_NoProblem          :
	  cout << " No Problem"          << endl;
	  break;
	case HatchGen_TrimFailure        :
	  cout << " Trim Failure"        << endl;
	  break;
	case HatchGen_TransitionFailure  :
	  cout << " Transition Failure"  << endl;
	  break;
	case HatchGen_IncoherentParity   :
	  cout << " Incoherent Parity"   << endl;
	  break;
	case HatchGen_IncompatibleStates :
	  cout << " Incompatible States" << endl;
	  break;
	}
	Hatcher.RemHatching (IndH);
	continue;
      }
      
      Standard_Integer NbDom = Hatcher.NbDomains (IndH);
      if (NbDom > 0) {

	for (Standard_Integer IDom = 1; IDom <= NbDom; IDom++) {
	  const HatchGen_Domain& Dom = Hatcher.Domain (IndH, IDom);
	  Standard_Real U1 = Dom.HasFirstPoint()  ? 
	    Dom.FirstPoint().Parameter()  : VMin - Infinite;
	  Standard_Real U2 = Dom.HasSecondPoint() ? 
	    Dom.SecondPoint().Parameter() : VMax + Infinite;
	  IsoLine->D0 (U1, P);
	  Surface.D0 (P.X(), P.Y(), P1);
	  IsoLine->D0 (U2, P);
	  Surface.D0 (P.X(), P.Y(), P2);
	  if (Dom.HasFirstPoint()) { // Iso V - Premier point
	    const HatchGen_PointOnHatching& PntH = Dom.FirstPoint();

	    for (Standard_Integer IPntE = 1; 
		 IPntE <= PntH.NbPoints();
		 IPntE++) {
	      const HatchGen_PointOnElement& PntE = PntH.Point(IPntE);
	      V1V = HLRTopoBRep_FaceIsoLiner::MakeVertex
		(TopoDS::Edge(SH(PntE.Index())),
		 P1,PntE.Parameter(),Tolerance,DS);
	 
     if (IL(PntE.Index())) DS.AddOutV(V1V);
	    }
	  }
	  if (Dom.HasSecondPoint()) { // Iso V - Deuxieme point
	    const HatchGen_PointOnHatching& PntH = Dom.SecondPoint();

	    for (Standard_Integer IPntE = 1;
		 IPntE <= PntH.NbPoints();
		 IPntE++) {
	      const HatchGen_PointOnElement& PntE = PntH.Point(IPntE);
	      V2V = HLRTopoBRep_FaceIsoLiner::MakeVertex
		(TopoDS::Edge(SH(PntE.Index())),
		 P2,PntE.Parameter(),Tolerance,DS);
	      if (IL(PntE.Index())) DS.AddOutV(V2V);
	    }
	  }
	  if(!V1V.IsNull() && !V2V.IsNull())
	    HLRTopoBRep_FaceIsoLiner::MakeIsoLine
	      (F,IsoLine,V1V,V2V,U1,U2,Tolerance,DS);
	}
      }
      
      Hatcher.RemHatching (IndH);
      VPrm += StepV;
    }
  }
}

//=======================================================================
//function : MakeVertex
//purpose  :
//=======================================================================

TopoDS_Vertex
HLRTopoBRep_FaceIsoLiner::MakeVertex (const TopoDS_Edge& E,
				      const gp_Pnt& P,
				      const Standard_Real Par,
				      const Standard_Real Tol,
				      HLRTopoBRep_Data& DS)
{
  TopoDS_Vertex V, VF, VL;
  BRep_Builder B;
  TopExp::Vertices (E, VF, VL);
  if (P.IsEqual(BRep_Tool::Pnt(VF),BRep_Tool::Tolerance(VF)))
    return VF;
  if (P.IsEqual(BRep_Tool::Pnt(VL),BRep_Tool::Tolerance(VL)))
    return VL;

  for (DS.InitVertex(E); DS.MoreVertex(); DS.NextVertex()) {
    TopoDS_Vertex curV = DS.Vertex();
    Standard_Real curP = DS.Parameter();
    if (P.IsEqual(BRep_Tool::Pnt(curV),BRep_Tool::Tolerance(curV))) {
      V = curV;
      break;
    }
    else if (Par < curP) { 
      B.MakeVertex(V,P,Tol);
      V.Orientation(TopAbs_INTERNAL);
      DS.InsertBefore(V,Par);
      break;
    }
  }
  
  if (!DS.MoreVertex()) {
    B.MakeVertex(V,P,Tol);
    V.Orientation(TopAbs_INTERNAL);
    DS.Append(V,Par);
  }
  
  return V;
}

//=======================================================================
//function : MakeIsoLine
//purpose  :
//=======================================================================

void HLRTopoBRep_FaceIsoLiner::MakeIsoLine (const TopoDS_Face& F,
					    const Handle(Geom2d_Line)& Iso,
					    TopoDS_Vertex& V1,
					    TopoDS_Vertex& V2,
					    const Standard_Real U1,
					    const Standard_Real U2,
					    const Standard_Real Tol,
					    HLRTopoBRep_Data& DS)
{
  BRep_Builder B;
  TopoDS_Edge E;
  E.Orientation (TopAbs_INTERNAL);
  V1.Orientation (TopAbs_FORWARD);
  V2.Orientation (TopAbs_REVERSED);
  B.MakeEdge (E);
  B.UpdateEdge (E, Iso, F, Tol);
  B.Add (E, V1);
  B.UpdateVertex (V1, U1, E, Tol);
  B.Add (E, V2);
  B.UpdateVertex (V2, U2, E, Tol);
  DS.AddIsoL(F).Append(E);
}

