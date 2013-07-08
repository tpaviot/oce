// Created on: 1998-07-22
// Created by: Philippe MANGIN
// Copyright (c) 1998-1999 Matra Datavision
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


#include <stdio.h>

#include <BRepFill_PipeShell.ixx>

#include <BRep_Builder.hxx>
#include <BRep_Tool.hxx>
#include <TopExp.hxx>
#include <TopTools_SequenceOfShape.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopLoc_Location.hxx>

#include <BRepLib_MakeEdge.hxx>
#include <BRepLib_MakeFace.hxx>
#include <BRepAdaptor_HCompCurve.hxx>
#include <BRepClass3d_SolidClassifier.hxx>

#include <BRepFill.hxx>
#include <BRepFill_Sweep.hxx>
#include <BRepFill_SectionPlacement.hxx>
#include <BRepFill_Edge3DLaw.hxx>
#include <BRepFill_ACRLaw.hxx>
#include <BRepFill_EdgeOnSurfLaw.hxx>
#include <BRepFill_ShapeLaw.hxx>
#include <BRepFill_CompatibleWires.hxx>
#include <BRepFill_NSections.hxx>
#include <TColStd_HArray1OfReal.hxx>

#include <GeomFill_TrihedronLaw.hxx>
#include <GeomFill_CorrectedFrenet.hxx>
#include <GeomFill_Frenet.hxx>
#include <GeomFill_DiscreteTrihedron.hxx>
#include <GeomFill_Fixed.hxx>
#include <GeomFill_ConstantBiNormal.hxx>
#include <GeomFill_SectionLaw.hxx>
#include <GeomFill_CurveAndTrihedron.hxx>
#include <GeomFill_GuideTrihedronAC.hxx>
#include <GeomFill_GuideTrihedronPlan.hxx>
#include <GeomFill_LocationGuide.hxx>

//Specification Guide
#include <GeomAdaptor_HCurve.hxx>

#include <gp_Trsf.hxx>
#include <gp_Dir.hxx>
#include <gp_Vec.hxx>
#include <Precision.hxx>

#include <Standard_NotImplemented.hxx>
#include <Standard_ConstructionError.hxx>
#include <StdFail_NotDone.hxx>

#include <BRepBuilderAPI_Copy.hxx>

#ifdef DRAW
#include <Draw.hxx>
#include <DrawTrSurf.hxx>
#include <DBRep.hxx>
static Standard_Boolean Affich = 0;
#endif

#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopoDS_Compound.hxx>

static Standard_Boolean UpdateMap(const TopoDS_Shape&                 theKey,
				  const TopoDS_Shape&                 theValue,
				  TopTools_DataMapOfShapeListOfShape& theMap);

static Standard_Boolean BuildBoundaries(const BRepFill_Sweep&               theSweep,
					const Handle(BRepFill_SectionLaw)&  theSection,
					TopoDS_Shape&                       theBottom,
					TopoDS_Shape&                       theTop);

//=======================================================================
//function :  ComputeSection
//purpose  : Construct an intermediary section
//=======================================================================

static Standard_Boolean ComputeSection(const TopoDS_Wire& W1,
                                       const TopoDS_Wire& W2,
                                       const Standard_Real p1,
                                       const Standard_Real p2,
                                       TopoDS_Wire& Wres)
{
  TColStd_SequenceOfReal SR;
  TopTools_SequenceOfShape SSh;
  SR.Clear();
  SR.Append(0.);
  SR.Append(1.);
  SSh.Clear();
  SSh.Append(W1);
  SSh.Append(W2);
  BRepFill_CompatibleWires CW(SSh);
  CW.SetPercent(0.1);
  CW.Perform();
  if (!CW.IsDone()) StdFail_NotDone::Raise("Uncompatible wires");
  GeomFill_SequenceOfTrsf EmptyTrsfs;
  Handle(BRepFill_NSections) SL = new (BRepFill_NSections) (CW.Shape(),EmptyTrsfs,SR,0.,1.);
  Standard_Real US = p1/(p1+p2);
  SL->D0(US, Wres);
  return Standard_True;
}

				      

//=======================================================================
//function : PerformTransition
//purpose  : Modify a law of location depending on Transition
//=======================================================================

static void PerformTransition(const BRepFill_TransitionStyle Mode,
			      Handle(BRepFill_LocationLaw)& Loc,
			      const Standard_Real angmin)
{
 if (!Loc.IsNull()) {
   Loc->DeleteTransform();
   if (Mode == BRepFill_Modified) Loc->TransformInG0Law();
   else  Loc->TransformInCompatibleLaw(angmin);
 } 
}
//=======================================================================
//function :  PerformPlan
//purpose  : Construct a plane of filling if exists
//=======================================================================

static Standard_Boolean PerformPlan(TopoDS_Shape& S)
{
  Standard_Boolean isDegen = Standard_True;
  TopExp_Explorer explo(S, TopAbs_EDGE);
  for (; explo.More(); explo.Next())
    {
      const TopoDS_Edge& anEdge = TopoDS::Edge(explo.Current());
      if (!BRep_Tool::Degenerated(anEdge))
	isDegen = Standard_False;
    }
  if (isDegen)
    {
      S.Nullify();
      return Standard_True;
    }

  TopoDS_Wire W = TopoDS::Wire(S);
  Standard_Boolean Ok = Standard_False;
  if (!W.IsNull()) {
    BRepLib_MakeFace mkplan(W, Standard_True);
    if (mkplan.IsDone()) {
      S = mkplan.Face();
      Ok = Standard_True;
    }
  }
 return Ok;
}

//=============================================================================
//function :  IsSameOriented
//purpose  : Checks whether aFace is oriented to the same side as aShell or not
//=============================================================================

static Standard_Boolean IsSameOriented(const TopoDS_Shape& aFace,
				       const TopoDS_Shape& aShell)
{
  TopExp_Explorer Explo(aFace, TopAbs_EDGE);
  TopoDS_Shape anEdge = Explo.Current();
  TopAbs_Orientation Or1 = anEdge.Orientation();

  TopTools_IndexedDataMapOfShapeListOfShape EFmap;
  TopExp::MapShapesAndAncestors( aShell, TopAbs_EDGE, TopAbs_FACE, EFmap );

  const TopoDS_Shape& AdjacentFace = EFmap.FindFromKey(anEdge).First();
  TopoDS_Shape theEdge;
  for (Explo.Init(AdjacentFace, TopAbs_EDGE); Explo.More(); Explo.Next())
    {
      theEdge = Explo.Current();
      if (theEdge.IsSame(anEdge))
	break;
    }

  TopAbs_Orientation Or2 = theEdge.Orientation();
  if (Or1 == Or2)
    return Standard_False;
  return Standard_True;
}
//=======================================================================
//function : BRepFill_PipeShell
//purpose  : 
//=======================================================================
BRepFill_PipeShell::BRepFill_PipeShell(const TopoDS_Wire& Spine)
                      :  mySpine(Spine), 
			 myTrihedron(GeomFill_IsCorrectedFrenet),
			 myTransition(BRepFill_Modified),
                         myForceApproxC1(Standard_False),
			 myStatus(GeomFill_PipeOk)
{
  myLocation.Nullify();
  mySection.Nullify();
  myLaw.Nullify();
  SetTolerance();

  // Attention to closed non-declared wire !
  if (!mySpine.Closed()) {
    TopoDS_Vertex Vf, Vl;
    TopExp::Vertices(mySpine, Vf, Vl);
    if (Vf.IsSame(Vl)) mySpine.Closed(Standard_True);
  }  
}

//=======================================================================
//function : Set
//purpose  : Define a law of Frenet (Correct)
//=======================================================================
 void BRepFill_PipeShell::Set(const Standard_Boolean IsFrenet) 
{
  Handle(GeomFill_TrihedronLaw) TLaw;
  if (IsFrenet) {
    myTrihedron = GeomFill_IsFrenet;
    TLaw = new (GeomFill_Frenet) ();
  }
  else {
    myTrihedron = GeomFill_IsFrenet;
    TLaw = new (GeomFill_CorrectedFrenet) ();
  }
  Handle(GeomFill_CurveAndTrihedron) Loc = 
    new (GeomFill_CurveAndTrihedron) (TLaw);
  myLocation = new (BRepFill_Edge3DLaw) (mySpine, Loc);
  mySection.Nullify(); //It is required to relocalize sections.
}

//=======================================================================
//function : SetDiscrete
//purpose  : Define a law of Discrete Trihedron
//=======================================================================
 void BRepFill_PipeShell::SetDiscrete() 
{
  Handle(GeomFill_TrihedronLaw) TLaw;

  myTrihedron = GeomFill_IsDiscreteTrihedron;
  TLaw = new (GeomFill_DiscreteTrihedron) ();

  Handle(GeomFill_CurveAndTrihedron) Loc = 
    new (GeomFill_CurveAndTrihedron) (TLaw);
  myLocation = new (BRepFill_Edge3DLaw) (mySpine, Loc);
  mySection.Nullify(); //It is required to relocalize sections.
}

//=======================================================================
//function : Set
//purpose  : Define a law Constant
//=======================================================================
 void BRepFill_PipeShell::Set(const gp_Ax2& Axe) 
{
  myTrihedron = GeomFill_IsFixed;
  gp_Vec V1, V2;
  V1.SetXYZ(Axe.Direction().XYZ());
  V2.SetXYZ(Axe.XDirection().XYZ());
  Handle(GeomFill_Fixed) TLaw = new (GeomFill_Fixed) (V1, V2);
  Handle(GeomFill_CurveAndTrihedron) Loc = 
    new (GeomFill_CurveAndTrihedron) (TLaw);
  myLocation = new (BRepFill_Edge3DLaw) (mySpine, Loc); 
  mySection.Nullify(); //It is required to relocalize sections.
}

//=======================================================================
//function : Set
//purpose  : Construct a law of location of binormal fixed type
//=======================================================================
 void BRepFill_PipeShell::Set(const gp_Dir& BiNormal) 
{
  myTrihedron = GeomFill_IsConstantNormal;

  Handle(GeomFill_ConstantBiNormal) TLaw = 
    new (GeomFill_ConstantBiNormal) (BiNormal);
  Handle(GeomFill_CurveAndTrihedron) Loc = 
    new (GeomFill_CurveAndTrihedron) (TLaw);
  myLocation = new (BRepFill_Edge3DLaw) (mySpine, Loc); 
  mySection.Nullify(); //Il faut relocaliser les sections.
}

//=======================================================================
//function : Set
//purpose  : Construct a law of location of Darboux type
//=======================================================================
 Standard_Boolean BRepFill_PipeShell::Set(const TopoDS_Shape& SpineSupport) 
{
 Standard_Boolean B;

  // A special law of location is required
 Handle(BRepFill_EdgeOnSurfLaw) loc = 
   new (BRepFill_EdgeOnSurfLaw) (mySpine, SpineSupport);
 B = loc->HasResult();
 if (B) {
   myLocation = loc; 
   myTrihedron = GeomFill_IsDarboux;
   mySection.Nullify(); //It is required to relocalize the sections.
 }
 return B;
}

//=======================================================================
//function : Set
//purpose  : Defines a lawv with help of a guided contour
//=======================================================================
 void BRepFill_PipeShell::Set(const TopoDS_Wire& AuxiliarySpine,
			      const Standard_Boolean CurvilinearEquivalence,
			      const Standard_Boolean KeepContact) 
{  
  // Reorganization of the guide (pb of orientation and origin)
  TopoDS_Wire TheGuide;
  TheGuide =  AuxiliarySpine;
  Standard_Boolean SpClose = mySpine.Closed(), 
                   GuideClose = AuxiliarySpine.Closed();

  if (!SpClose && !GuideClose) {
    // Case open reorientation of the guide
    TopoDS_Wire sp = mySpine;
    TopTools_SequenceOfShape Seq;
    Seq.Append(sp);
    Seq.Append(TheGuide);
    BRepFill_CompatibleWires CW(Seq);
    CW.SetPercent(0.1);
    CW.Perform();
    if (!CW.IsDone()) StdFail_NotDone::Raise("Uncompatible wires");
    TheGuide = TopoDS::Wire(CW.Shape().Value(2));
  }
  else if (GuideClose) {
    // Case guide closed : Determination of the origin 
    // & reorientation of the guide
    gp_Vec Dir;
    gp_Pnt SpOr;
    if (!SpClose) {
      TopoDS_Vertex Vf, Vl;
      gp_Pnt P;
      TopExp::Vertices(mySpine, Vf, Vl);
      SpOr = BRep_Tool::Pnt(Vf);
      P = BRep_Tool::Pnt(Vl);
      gp_Vec V(P, SpOr);
      SpOr.BaryCenter(0.5, P, 0.5);
      Dir = V;
    }
    else {
      BRepAdaptor_CompCurve BC(mySpine);
      BC.D1(0,SpOr,Dir); 
    } 
    BRepFill::SearchOrigin(TheGuide, SpOr, Dir, 100*myTol3d);
  }

#ifdef DRAW
  if (Affich)
    DBRep::Set("theguide", TheGuide);
#endif
  // transform the guide in a single curve (periodic if posssible)
  Handle(BRepAdaptor_HCompCurve) Guide  = 
    new (BRepAdaptor_HCompCurve) (TheGuide);
  Guide->ChangeCurve().SetPeriodic(Standard_True);

  if (CurvilinearEquivalence) { // trihedron by curvilinear reduced abscissa
    if (KeepContact) 
      myTrihedron = GeomFill_IsGuideACWithContact; // with rotation 
    else
      myTrihedron = GeomFill_IsGuideAC; // without rotation 
      
    Handle(GeomFill_GuideTrihedronAC) TLaw
      = new (GeomFill_GuideTrihedronAC) (Guide);
    Handle(GeomFill_LocationGuide) Loc = 
      new (GeomFill_LocationGuide) (TLaw);      
    myLocation = new (BRepFill_ACRLaw) (mySpine, Loc); 	
  }
  else {// trihedron by plane
    if (KeepContact) 
      myTrihedron = GeomFill_IsGuidePlanWithContact; // with rotation 
    else 
      myTrihedron = GeomFill_IsGuidePlan; // without rotation

    Handle(GeomFill_GuideTrihedronPlan) TLaw = 
      new (GeomFill_GuideTrihedronPlan) (Guide);    
    Handle(GeomFill_LocationGuide) Loc = 
      new (GeomFill_LocationGuide) (TLaw);
    myLocation = new (BRepFill_Edge3DLaw) (mySpine, Loc);  
  }    
  mySection.Nullify(); //It is required to relocalize the sections.
}

//=======================================================================
//function : SetForceApproxC1
//purpose  : Set the flag that indicates attempt to approximate
//           a C1-continuous surface if a swept surface proved
//           to be C0.
//=======================================================================
void BRepFill_PipeShell::SetForceApproxC1(const Standard_Boolean ForceApproxC1)
{
  myForceApproxC1 = ForceApproxC1;
}

//=======================================================================
//function : Add
//purpose  : Add a Section
//=======================================================================
 void BRepFill_PipeShell::Add(const TopoDS_Shape& Profile,
			      const Standard_Boolean WithContact,
			      const Standard_Boolean WithCorrection) 
{ 
  TopoDS_Vertex V;
  V.Nullify();
  Add(Profile, V, WithContact, WithCorrection);
  ResetLoc();
}

//=======================================================================
//function : Add
//purpose  : Add a Section
//=======================================================================
 void BRepFill_PipeShell::Add(const TopoDS_Shape& Profile,
			      const TopoDS_Vertex& Location,
			      const Standard_Boolean WithContact,
			      const Standard_Boolean WithCorrection) 
{
 Delete(Profile); // No duplication
 BRepFill_Section S (Profile, Location, WithContact, WithCorrection);
 mySeq.Append(S);
 mySection.Nullify();
 ResetLoc();
}

//=======================================================================
//function : SetLaw
//purpose  : Section + law of homothety
//=======================================================================
 void BRepFill_PipeShell::SetLaw(const TopoDS_Shape& Profile,
				 const Handle(Law_Function)& L,
				 const Standard_Boolean WithContact,
				 const Standard_Boolean WithCorrection) 
{
 TopoDS_Vertex V;
 V.Nullify();
 SetLaw( Profile, L, V, WithContact, WithCorrection);
 ResetLoc();
}

//=======================================================================
//function : SetLaw
//purpose  :  Section + Law of homothety
//=======================================================================
 void BRepFill_PipeShell::SetLaw(const TopoDS_Shape& Profile,
				 const Handle(Law_Function)& L,
				 const TopoDS_Vertex& Location,
				 const Standard_Boolean WithContact,
				 const Standard_Boolean WithCorrection) 
{
  mySeq.Clear();
  BRepFill_Section S (Profile, Location, WithContact, WithCorrection);
  S.Set(Standard_True);
  mySeq.Append(S);
  myLaw = L;
  mySection.Nullify();
  ResetLoc();
}

//=======================================================================
//function : Delete
//purpose  : Delete a section
//=======================================================================
 void BRepFill_PipeShell::Delete(const TopoDS_Shape&  Profile)
{
  Standard_Boolean isVertex = (Profile.ShapeType() == TopAbs_VERTEX);

  Standard_Boolean Trouve=Standard_False;
  Standard_Integer ii;
  for (ii=1; ii<=mySeq.Length() && !Trouve; ii++) {
    Standard_Boolean found = Standard_False;
    const TopoDS_Wire& aWire = mySeq.Value(ii).Wire();
    if (isVertex)
      {
	TopExp_Explorer Explo(aWire, TopAbs_VERTEX);
	for (; Explo.More(); Explo.Next())
	  if (Profile.IsSame(Explo.Current()))
	    found = Standard_True;
      }
    else if (Profile.IsSame(aWire))
      found = Standard_True;
    
    if (found)
      {
	Trouve = Standard_True;
	mySeq.Remove(ii);
      }
  }

  if (Trouve) mySection.Nullify();
  ResetLoc();
}


//=======================================================================
//function : IsReady
//purpose  : 
//=======================================================================
 Standard_Boolean BRepFill_PipeShell::IsReady() const
{
 return (mySeq.Length() != 0);
}
//=======================================================================
//function : GetStatus
//purpose  : 
//=======================================================================
 GeomFill_PipeError BRepFill_PipeShell::GetStatus() const
{
 return myStatus;
}


//=======================================================================
//function : SetTolerance
//purpose  :
//=======================================================================
 void BRepFill_PipeShell::SetTolerance(const Standard_Real Tol3d  ,
				       const Standard_Real BoundTol, 
				       const Standard_Real TolAngular)
{
 myTol3d = Tol3d;
 myBoundTol =  BoundTol;
 myTolAngular = TolAngular;
}

//=======================================================================
//function : SetTransition
//purpose  : Defines the mode of processing of corners
//=======================================================================
 void BRepFill_PipeShell::SetTransition(const BRepFill_TransitionStyle Mode,
					const Standard_Real Angmin,
					const Standard_Real Angmax)
{
 if (myTransition != Mode) 
   mySection.Nullify(); //It is required to relocalize the sections.
 myTransition = Mode;
 angmin =  Angmin;
 angmax = Angmax;
}  

//=======================================================================
//function : Simulate
//purpose  : Calculate N Sections
//=======================================================================
 void BRepFill_PipeShell::Simulate(const Standard_Integer N, 
				   TopTools_ListOfShape& List)
{
  // Preparation
  Prepare();
  List.Clear();

  Standard_Real First, Last, Length, Delta, U, 
                US, DeltaS,FirstS;
  Standard_Integer ii, NbL = myLocation->NbLaw();
  Standard_Boolean Finis=Standard_False;
  TopoDS_Shape W;
  
  // Calculate the parameters of digitalization
  mySection->Law(1)->GetDomain(FirstS, Last);
  DeltaS = Last - FirstS; 
  myLocation->CurvilinearBounds(NbL,First, Length);
  Delta = Length;
  if (N>1) Delta /= (N-1);

  myLocation->CurvilinearBounds(1,First, Last); // Initiation of Last
  for (U=0.0, ii=1; !Finis ; U+=Delta) {
    if (U >= Length) {
      U = Length;
      Finis = Standard_True;
    }
    else {
      if (ii <  NbL) myLocation->CurvilinearBounds(NbL,First, Last);
      if (U > Last) U = (Last+First)/2; // The edge is not skipped
      if (U> First) ii++;
    }
    US = FirstS + (U/Length)*DeltaS;
    // Calcul d'une section
    mySection->D0(US, W);
    myLocation->D0(U, W);
    List.Append(W);
  } 
}

//=======================================================================
//function : Build
//purpose  : Construct the Shell and the history
//=======================================================================
 Standard_Boolean BRepFill_PipeShell::Build() 
{
  Standard_Boolean Ok;
  Standard_Real FirstS, LastS;
  // 1) Preparation
  Prepare();

  if (myStatus != GeomFill_PipeOk) {
    BRep_Builder B;
    TopoDS_Shell Sh;
    B.MakeShell(Sh); 
    myShape = Sh; // Nullify
    return Standard_False; 
  }

  // 2) Calculate myFirst and myLast
  mySection->Law(1)->GetDomain(FirstS, LastS);
  mySection->D0(FirstS, myFirst);
  myLocation->D0(0, myFirst);
  if (mySection->IsVClosed() && myLocation->IsClosed()) {
      if (myLocation->IsG1(0)>=0) 
	myLast = myFirst;
      else {
	myFirst.Nullify();
	myLast.Nullify();
      }
  }
  else {
    Standard_Real Length;
    myLocation->CurvilinearBounds(myLocation->NbLaw(), 
				  FirstS, Length);
    mySection->D0(LastS,   myLast);
    myLocation->D0(Length, myLast);
    // eap 5 Jun 2002 occ332, myLast and myFirst must not share one TShape,
    // tolerances of shapes built on them may be quite different
    if (myFirst.IsPartner( myLast )) {
      BRepBuilderAPI_Copy copy(myLast);
      if (copy.IsDone()) 
        myLast = copy.Shape();
    }
    // eap 5 Jun 2002 occ332, end modif
  }
#if DRAW
  if (Affich) {
    DBRep::Set("PipeFirst", myFirst);
    DBRep::Set("PipeLast",  myLast);
  }
#endif

  // 3) Construction
  BRepFill_Sweep MkSw(mySection, myLocation, Standard_True);
  MkSw.SetTolerance(myTol3d, myBoundTol, 1.e-5, myTolAngular);
  MkSw.SetAngularControl(angmin, angmax);
  MkSw.SetForceApproxC1(myForceApproxC1);
  MkSw.SetBounds(TopoDS::Wire(myFirst), 
		 TopoDS::Wire(myLast));
  GeomAbs_Shape theContinuity = GeomAbs_C2;
  if (myTrihedron == GeomFill_IsDiscreteTrihedron)
    theContinuity = GeomAbs_C0;
  MkSw.Build(myTransition, theContinuity);

  myStatus = myLocation->GetStatus();
  Ok =  (MkSw.IsDone() && (myStatus == GeomFill_PipeOk));

  if (Ok) {
    myShape = MkSw.Shape();

    TopoDS_Shape aBottomWire = myFirst;
    TopoDS_Shape aTopWire    = myLast;

    if(BuildBoundaries(MkSw, mySection, aBottomWire, aTopWire)) {
      myFirst = aBottomWire;
      myLast = aTopWire;
    }
    
    if (mySection->IsUClosed())
      {
	TopExp_Explorer explo;
	Standard_Boolean DegenFirst = Standard_True, DegenLast = Standard_True;

	for (explo.Init(myFirst, TopAbs_EDGE); explo.More(); explo.Next())
	  {
	    const TopoDS_Edge& anEdge = TopoDS::Edge(explo.Current());
	    DegenFirst = DegenFirst && BRep_Tool::Degenerated(anEdge);
	  }

	for (explo.Init(myLast, TopAbs_EDGE); explo.More(); explo.Next())
	  {
	    const TopoDS_Edge& anEdge = TopoDS::Edge(explo.Current());
	    DegenLast = DegenLast && BRep_Tool::Degenerated(anEdge);
	  }

	if (DegenFirst && DegenLast)
	  myShape.Closed(Standard_True);
      }

    BuildHistory(MkSw);
  }
  else {
    BRep_Builder B;
    TopoDS_Shell Sh;
    B.MakeShell(Sh); 
    myShape = Sh; // Nullify
    if (myStatus == GeomFill_PipeOk) myStatus = GeomFill_PipeNotOk;
  }
  return Ok;
}

//=======================================================================
//function : MakeSolid
//purpose  : 
//=======================================================================
 Standard_Boolean BRepFill_PipeShell::MakeSolid() 
{ 
  if (myShape.IsNull()) 
    StdFail_NotDone::Raise("PipeShell is not built");
  Standard_Boolean B = myShape.Closed();
  BRep_Builder BS;

  if (!B)
    {
      if(!myFirst.IsNull() && !myLast.IsNull()) {
	B = (myFirst.Closed() && myLast.Closed());
      }
      if (B) {
	// It is necessary to block the extremities 
	B =  PerformPlan(myFirst);
	if (B) {
	  B =  PerformPlan(myLast);
	  if (B) {
	    if (!myFirst.IsNull() && !IsSameOriented( myFirst, myShape ))
	      myFirst.Reverse();
	    if (!myLast.IsNull() && !IsSameOriented( myLast, myShape ))
	      myLast.Reverse();

	    if (!myFirst.IsNull())
	      BS.Add(myShape, TopoDS::Face(myFirst));
	    if (!myLast.IsNull())
	      BS.Add(myShape, TopoDS::Face(myLast));

	    myShape.Closed(Standard_True);
	  }
	}
      }
    }

  if (B) {
   TopoDS_Solid solid;
   BS.MakeSolid(solid);
   BS.Add(solid,TopoDS::Shell(myShape));
   BRepClass3d_SolidClassifier SC(solid);
   SC.PerformInfinitePoint(Precision::Confusion());
   if ( SC.State() == TopAbs_IN) {
     BS.MakeSolid(solid);
     myShape.Reverse();
     BS.Add(solid,TopoDS::Shell(myShape));
   }
   myShape = solid;   
   myShape.Closed(Standard_True);
 }
  return B;
}

//=======================================================================
//function : Shape
//purpose  : Return the result
//=======================================================================
const TopoDS_Shape& BRepFill_PipeShell::Shape() const
{
  return myShape;
}

//=======================================================================
//function : FirstShape
//purpose  : Return the start section 
//=======================================================================
const TopoDS_Shape& BRepFill_PipeShell::FirstShape() const
{
  return myFirst;
}

//=======================================================================
//function : LastShape
//purpose  : Return the end section 
//=======================================================================
const TopoDS_Shape& BRepFill_PipeShell::LastShape() const
{
 return myLast;
}

//=======================================================================
//function : Generated
//purpose  : 
//=======================================================================
//  void BRepFill_PipeShell::Generated(const TopoDS_Shape& ,
// 				    TopTools_ListOfShape& ) 
void BRepFill_PipeShell::Generated(const TopoDS_Shape&   theShape,
				   TopTools_ListOfShape& theList) 
{
  //   Standard_NotImplemented::Raise("Generated:Pas Fait"); 
  theList.Clear();

  if(myGenMap.IsBound(theShape)) {
    theList = myGenMap.Find(theShape);
  } 
}

//=======================================================================
//function : Prepare
//purpose  : - Check that everything is ready
//           - Construct the law of section
//           - Construct the law of location if required
//           - Calculate First & Last
//=======================================================================
 void BRepFill_PipeShell::Prepare() 
{
  TopoDS_Wire theSect;
  if (!IsReady()) StdFail_NotDone::Raise("PipeShell");
  if (!myLocation.IsNull() && !mySection.IsNull()) return; // It is ready
 
  //Check set of section for right configuration of punctual sections
  Standard_Integer i;
  TopoDS_Iterator iter;;
  for (i = 2; i <= mySeq.Length()-1; i++)
    {
      Standard_Boolean wdeg = Standard_True;
      for (iter.Initialize(mySeq(i).Wire()); iter.More(); iter.Next())
	{
	  const TopoDS_Edge& anEdge = TopoDS::Edge(iter.Value());
	  wdeg = wdeg && (BRep_Tool::Degenerated(anEdge));
	}
      if (wdeg)
	Standard_Failure::Raise("Wrong usage of punctual sections");
    }
  if (mySeq.Length() <= 2)
    {
      Standard_Boolean wdeg = Standard_True;
      for (i = 1; i <= mySeq.Length(); i++)
	for (iter.Initialize(mySeq(i).Wire()); iter.More(); iter.Next())
	  {
	    const TopoDS_Edge& anEdge = TopoDS::Edge(iter.Value());
	    wdeg = wdeg && (BRep_Tool::Degenerated(anEdge));
	  }
      if (wdeg)
	Standard_Failure::Raise("Wrong usage of punctual sections");
    }

  // Construction of the law of location  
  if(myLocation.IsNull()) 
    {
      switch(myTrihedron)
	{
	case GeomFill_IsCorrectedFrenet :
	  {
	    Handle(GeomFill_TrihedronLaw) TLaw = 
	      new (GeomFill_CorrectedFrenet) ();
	    Handle(GeomFill_CurveAndTrihedron) Loc = 
	      new (GeomFill_CurveAndTrihedron) (TLaw);
	    myLocation = new (BRepFill_Edge3DLaw) (mySpine, Loc);
	    break;
	  } 
	  default :
	    { // Not planned!
	      Standard_ConstructionError::Raise("PipeShell");
	    }
	}
    }  
  
  //Transformation of the law (Transition Management)
  PerformTransition(myTransition, myLocation, angmin);

  
 // Construction of the section law
  if (mySeq.Length() == 1) {
    Standard_Real p1;
    gp_Trsf aTrsf;
    Place(mySeq(1), theSect, aTrsf, p1);
    TopoDS_Wire aLocalShape = theSect;
    if (mySeq(1).IsLaw())
      mySection = new BRepFill_ShapeLaw(aLocalShape, myLaw);
//      mySection = new (BRepFill_ShapeLaw) (TopoDS_Wire(theSect), myLaw);
    else 
      mySection = new BRepFill_ShapeLaw(aLocalShape);
// mySection = new (BRepFill_ShapeLaw) (TopoDS::Wire(theSect));
    }   
  else 
    {
      TColStd_SequenceOfReal Param;
      TopTools_SequenceOfShape WSeq;
      GeomFill_SequenceOfTrsf Transformations;
      //WSeq.Clear();
      //Param.Clear();
      Standard_Integer NbL = myLocation->NbLaw();
      gp_Trsf aTrsf;
      Standard_Real V1, V2, param;
      myLocation->CurvilinearBounds(NbL, V1, V2);
      V1 = 0.;
      Standard_Integer ideb = 0, ifin = 0;
//      for (Standard_Integer iseq=1;iseq<=mySeq.Length();iseq++) {
      Standard_Integer iseq;
      for (iseq=1;iseq<=mySeq.Length();iseq++) {
	Place(mySeq(iseq), theSect, aTrsf, param);
	Param.Append(param);
	WSeq.Append(theSect);
//	WSeq.Append(TopoDS::Wire(theSect));
        Transformations.Append(aTrsf);
        if (param==V1) ideb = iseq;
        if (param==V2) ifin = iseq;
      }
      

      // looping sections ?
      if (myLocation->IsClosed()) {
        if (ideb>0) {
          // place the initial section at the final position 
          Param.Append(V2);
          WSeq.Append(WSeq(ideb));
        }
        else if (ifin>0) {
          // place the final section at the initial position
          Param.Append(V1);
          WSeq.Append(WSeq(ifin));
        }
        else {
          // it is necessary to find a medium section to impose by V1 and by V2
          Standard_Real pmin = Param.Value(1), pmax = Param.Value(1);
          TopoDS_Wire Wmin = TopoDS::Wire(WSeq.Value(1)), Wmax;
          for (iseq=2;iseq<=WSeq.Length();iseq++) {
            if (Param.Value(iseq)<pmin) {
              pmin = Param.Value(iseq);
              Wmin = TopoDS::Wire(WSeq.Value(iseq));
            }
            if (Param.Value(iseq)>pmax) {
              pmax = Param.Value(iseq);
              Wmax = TopoDS::Wire(WSeq.Value(iseq));
            }
          }
          // medium section between Wmin and Wmax
          TopoDS_Wire Wres;
          Standard_Real dmin = Abs(pmin-V1);
          Standard_Real dmax = Abs(pmax-V2);
          if (ComputeSection(Wmin,Wmax,dmin,dmax,Wres)) {
            // impose section Wres at the beginning and the end
            Param.Append(V1);
            WSeq.Append(Wres);
            Param.Append(V2);
            WSeq.Append(Wres);
            
          }
          
        }
      }

      // parse sections by increasing parameter
      Standard_Boolean play_again = Standard_True;
      while (play_again) {
	play_again = Standard_False;
	for (iseq=1;iseq<=WSeq.Length();iseq++) {
	  for (Standard_Integer jseq=iseq+1;jseq<=WSeq.Length();jseq++) {
	    if (Param.Value(iseq)>Param.Value(jseq)) {
	      Param.Exchange(iseq,jseq);
	      WSeq.Exchange(iseq,jseq);
	      play_again = Standard_True;
	    }
	  }
	}
      }

#ifdef DRAW
  if ( Affich) {
    char*  name = new char[100];
    Standard_Integer NBSECT = 0;
    for (Standard_Integer i=1;i<=WSeq.Length();i++) {
      NBSECT++;
      sprintf(name,"WSeq_%d",NBSECT);
      DBRep::Set(name,TopoDS::Wire(WSeq.Value(i)));
    }
  }
#endif
      
      

      //  Calculate work sections 
      TopTools_SequenceOfShape WorkingSections;
      WorkingSections.Clear();
      TopTools_DataMapOfShapeListOfShape WorkingMap;
      WorkingMap.Clear();
      BRepFill_CompatibleWires Georges(WSeq);
      Georges.SetPercent(0.1);
      Georges.Perform(Standard_False);
      if (Georges.IsDone()) {
	WorkingSections = Georges.Shape();
	WorkingMap = Georges.Generated();
      }
      else {
	Standard_ConstructionError::Raise("PipeShell : uncompatible wires");
      }
      mySection = new (BRepFill_NSections) (WorkingSections,Transformations,Param,V1,V2);
      
    }// else

  //  modify the law of location if contact
  if ( (myTrihedron == GeomFill_IsGuidePlanWithContact)
      || (myTrihedron == GeomFill_IsGuideACWithContact) )  {
    Standard_Real fs, f, l, Delta, Length;
    Handle(GeomFill_LocationGuide) Loc;
    Handle(GeomFill_SectionLaw) Sec = mySection->ConcatenedLaw();
    myLocation->CurvilinearBounds(myLocation->NbLaw(), f, Length);
    Sec->GetDomain(fs,l);
    Delta = (l-fs)/Length;

    Standard_Real angle, old_angle = 0;
    for (Standard_Integer ipath=1; ipath<=myLocation->NbLaw(); ipath++) {
      myLocation->CurvilinearBounds(ipath, f, l);
      Loc = Handle(GeomFill_LocationGuide)::DownCast(myLocation->Law(ipath));
      Loc->Set(Sec, Standard_True, fs + f*Delta, fs + l*Delta,
	       old_angle, angle); // force the rotation	
      old_angle = angle;
    }      
  }

  myStatus = myLocation->GetStatus();
}

//=======================================================================
//function : Place
//purpose  : Implement a Section in the local refernce frame
//           and return its parameter on the trajectory
//=======================================================================
void BRepFill_PipeShell::Place(const BRepFill_Section& Sec,
			       TopoDS_Wire& W,
                               gp_Trsf& aTrsf,
			       Standard_Real& param)
{
  BRepFill_SectionPlacement Place(myLocation, 
				  Sec.Wire(),
				  Sec.Vertex(),
				  Sec.WithContact(),
				  Sec.WithCorrection());
  W =  Sec.Wire();
  aTrsf = Place.Transformation();
  TopLoc_Location Loc2(Place.Transformation()), Loc1;
  Loc1 = W.Location();
  W.Location(Loc2.Multiplied(Loc1));
  param = Place.AbscissaOnPath();
}


//=======================================================================
//function : ResetLoc
//purpose  : Remove references to the sections in the laws of location
//=======================================================================
 void BRepFill_PipeShell::ResetLoc() 
{
  if ( (myTrihedron == GeomFill_IsGuidePlanWithContact)
      || (myTrihedron == GeomFill_IsGuideACWithContact) ) {
    Handle(GeomFill_LocationGuide) Loc;
    for (Standard_Integer isec=1; isec<=myLocation->NbLaw(); isec++) { 
      Loc = Handle(GeomFill_LocationGuide)::DownCast(myLocation->Law(isec));
      Loc->EraseRotation();// remove the rotation	
    }    
  }
}

//=======================================================================
//function : BuildHistory
//purpose  : Builds history for edges of spine, 
//           for built bottom shape of sweep,
//           for boundary vertices of bottom shape of sweep,
//           for boundary profiles
//=======================================================================
void BRepFill_PipeShell::BuildHistory(const BRepFill_Sweep& theSweep) 
{
  Handle(TopTools_HArray2OfShape) aFaces = theSweep.SubShape();
  Handle(TopTools_HArray2OfShape) aVEdges = theSweep.Sections();
  Handle(TopTools_HArray2OfShape) aUEdges = theSweep.InterFaces();
  Standard_Integer i = 0, j = 0;
  Standard_Boolean bPrevModified = Standard_False;

  for(i = 1; i <= mySection->NbLaw(); i++) {
    if((!aVEdges->Value(i, 1).IsNull()) && (aVEdges->Value(i, 1).ShapeType() == TopAbs_FACE)) {
      bPrevModified = Standard_True;
      break;
    }
  }

  for(j = myLocation->NbLaw(); j >= 1; j--) {
    TopTools_ListOfShape aListOfFace;

    if(bPrevModified) {
      for(i = 1; i <= mySection->NbLaw(); i++) {
	Standard_Integer lessindex = j + 1;
	lessindex = (lessindex > myLocation->NbLaw()) ? 1 : lessindex;

	if((!aVEdges->Value(i, lessindex).IsNull()) && (aVEdges->Value(i, lessindex).ShapeType() == TopAbs_FACE)) {
	  aListOfFace.Append(aVEdges->Value(i, lessindex));
	  const TopoDS_Shape& aBottomEdge = aVEdges->Value(i, 1);

	  if((!aBottomEdge.IsNull()) && (aBottomEdge.ShapeType() == TopAbs_EDGE)) {
	    UpdateMap(aBottomEdge, aVEdges->Value(i, lessindex), myGenMap);
	  }
	}
      }
    }
    bPrevModified = Standard_False;

    for(i = 1; i <= mySection->NbLaw(); i++) {
      if((!aVEdges->Value(i, j).IsNull()) && (aVEdges->Value(i, j).ShapeType() == TopAbs_FACE)) {
	aListOfFace.Append(aVEdges->Value(i, j));
	bPrevModified = Standard_True;

	const TopoDS_Shape& aBottomEdge = aVEdges->Value(i, 1);

	if((!aBottomEdge.IsNull()) && (aBottomEdge.ShapeType() == TopAbs_EDGE)) {
	  UpdateMap(aBottomEdge, aVEdges->Value(i, j), myGenMap);
	}
      }

      if(aFaces->Value(i, j).ShapeType() == TopAbs_FACE) {
	aListOfFace.Append(aFaces->Value(i, j));
	const TopoDS_Shape& aBottomEdge = aVEdges->Value(i, 1);

	if((!aBottomEdge.IsNull()) && (aBottomEdge.ShapeType() == TopAbs_EDGE)) {
	  UpdateMap(aBottomEdge, aFaces->Value(i, j), myGenMap);
	}
      }
    }

    if(!myGenMap.IsBound(myLocation->Edge(j)))
      myGenMap.Bind(myLocation->Edge(j), aListOfFace);
    else
      myGenMap.ChangeFind(myLocation->Edge(j)).Append(aListOfFace);

    // build history for free booundaries.begin
    if(!mySection->IsUClosed()) {
      TopoDS_Compound aFaceComp;
      BRep_Builder aB;
      aB.MakeCompound(aFaceComp);
      TopTools_ListIteratorOfListOfShape anIt(aListOfFace);

      for(; anIt.More(); anIt.Next()) {
	aB.Add(aFaceComp, anIt.Value());
      }
      TopTools_IndexedDataMapOfShapeListOfShape aMapEF;
      TopExp::MapShapesAndAncestors(aFaceComp, TopAbs_EDGE, TopAbs_FACE, aMapEF);
      Standard_Integer eit = 0;

      for(eit = aUEdges->LowerRow(); eit <= aUEdges->UpperRow(); eit++) {
	const TopoDS_Shape& aShape = aUEdges->Value(eit, j);

	if(aMapEF.Contains(aShape)) {
	  const TopTools_ListOfShape& aList = aMapEF.FindFromKey(aShape);

	  if(aList.Extent() < 2) {
	    UpdateMap(myLocation->Edge(j), aShape, myGenMap);

	    TopoDS_Shape aGenVertex;
	    TopTools_IndexedDataMapOfShapeListOfShape aMapVE;
	    
	    for(i = 1; i <= mySection->NbLaw(); i++) {
	      const TopoDS_Shape& aBottomEdge = aVEdges->Value(i, aVEdges->LowerCol());

	      if((!aBottomEdge.IsNull()) && (aBottomEdge.ShapeType() == TopAbs_EDGE)) {
		TopExp::MapShapesAndAncestors(aBottomEdge, TopAbs_VERTEX, TopAbs_EDGE, aMapVE);
	      }
	    }
	    const TopoDS_Shape& aFreeEdge = aUEdges->Value(eit, aUEdges->LowerCol());
	    TopExp::MapShapesAndAncestors(aFreeEdge, TopAbs_VERTEX, TopAbs_EDGE, aMapVE);
	    TopExp_Explorer anExpV(aFreeEdge, TopAbs_VERTEX);

	    for(; anExpV.More(); anExpV.Next()) {
	      if(aMapVE.Contains(anExpV.Current())) {
		const TopTools_ListOfShape& aListOfV = aMapVE.FindFromKey(anExpV.Current());

		if(aListOfV.Extent() >= 2) {
		  aGenVertex = anExpV.Current();
		}
	      }
	    }

	    if(!aGenVertex.IsNull()) {
	      UpdateMap(aGenVertex, aShape, myGenMap);
	    }
	  }
	}
      }
      // end for(eit = aUEdges->LowerRow...
    }
    // build history for free booundaries.end
  }

  // build history for boundary section wires. begin

  if(!mySeq.IsEmpty()) {
    Standard_Integer iseq;
    TopoDS_Wire aSect;
    gp_Trsf aTrsf;
    Standard_Real param = 0., aparmin = RealLast(), aparmax = -RealLast();
    Standard_Integer ideb = 1, ifin = mySeq.Length();

    for (iseq = 1;iseq <= mySeq.Length(); iseq++) {
      Place(mySeq(iseq), aSect, aTrsf, param);

      if(param < aparmin) {
	ideb = iseq;
	aparmin = param;
      }

      if(param > aparmax) {
	ifin = iseq;
	aparmax = param;
      }
    }
    
    UpdateMap(mySeq(ideb).Wire(), myFirst, myGenMap);
    UpdateMap(mySeq(ifin).Wire(), myLast, myGenMap);
  }
  // build history for boundary section wires. end
}

// ---------------------------------------------------------------------------------
// static function: UpdateMap
// purpose:
// ---------------------------------------------------------------------------------
Standard_Boolean UpdateMap(const TopoDS_Shape&                 theKey,
			   const TopoDS_Shape&                 theValue,
			   TopTools_DataMapOfShapeListOfShape& theMap) {

  if(!theMap.IsBound(theKey)) {
    TopTools_ListOfShape thelist;
    theMap.Bind(theKey, thelist);
  }
  TopTools_ListOfShape& aList = theMap.ChangeFind(theKey);
  TopTools_ListIteratorOfListOfShape anIt(aList);
  Standard_Boolean found = Standard_False;

  for(; anIt.More(); anIt.Next()) {
    if(theValue.IsSame(anIt.Value())) {
      found = Standard_True;
      break;
    }
  }

  if(!found)
    aList.Append(theValue);
  return !found;
}

// ---------------------------------------------------------------------------------
// static function: BuildBoundaries
// purpose:
// ---------------------------------------------------------------------------------
Standard_Boolean BuildBoundaries(const BRepFill_Sweep&               theSweep,
				 const Handle(BRepFill_SectionLaw)&  theSection,
				 TopoDS_Shape&                       theBottom,
				 TopoDS_Shape&                       theTop) {
  
  TopoDS_Wire aBottomWire;
  TopoDS_Wire aTopWire;
  BRep_Builder aB;
  aB.MakeWire(aBottomWire);
  aB.MakeWire(aTopWire);
  Standard_Boolean bfoundbottom = Standard_False;
  Standard_Boolean bfoundtop = Standard_False;
  Handle(TopTools_HArray2OfShape) aVEdges = theSweep.Sections();
  Standard_Integer i = 0;
  Standard_Boolean bAllSame = Standard_True;

  for(i = 1; i <= theSection->NbLaw(); i++) {
    const TopoDS_Shape& aBottomEdge = aVEdges->Value(i, aVEdges->LowerCol());

    if(!aBottomEdge.IsNull() && (aBottomEdge.ShapeType() == TopAbs_EDGE)) {
      aB.Add(aBottomWire, aBottomEdge);
      bfoundbottom = Standard_True;
    }
    const TopoDS_Shape& aTopEdge = aVEdges->Value(i, aVEdges->UpperCol());

    if(!aTopEdge.IsNull() && (aTopEdge.ShapeType() == TopAbs_EDGE)) {
      aB.Add(aTopWire, aTopEdge);
      bfoundtop = Standard_True;
    }

    if(!aBottomEdge.IsNull() && !aTopEdge.IsNull() && !aBottomEdge.IsSame(aTopEdge))
      bAllSame = Standard_False;
  }

  if(theSection->IsUClosed()) {
    aBottomWire.Closed(Standard_True);
    aTopWire.Closed(Standard_True);
  }

  if(bfoundbottom) {
    theBottom = aBottomWire;
  }

  if(bfoundtop) {
    theTop  = aTopWire;
  }

  if(bAllSame && bfoundbottom && bfoundtop)
    theTop = theBottom;

  return bfoundbottom || bfoundtop;
}
