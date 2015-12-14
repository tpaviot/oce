// Created on: 1995-06-27
// Created by: Jacques GOUSSARD
// Copyright (c) 1995-1999 Matra Datavision
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

#include <LocOpe_SplitShape.ixx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TopTools_MapOfShape.hxx>
#include <TopTools_MapOfOrientedShape.hxx>
#include <TopTools_DataMapOfShapeListOfShape.hxx>
#include <TopTools_DataMapIteratorOfDataMapOfShapeListOfShape.hxx>
#include <TopTools_DataMapOfShapeInteger.hxx>
#include <TopTools_DataMapOfShapeShape.hxx>
#include <TopTools_DataMapIteratorOfDataMapOfShapeShape.hxx>
#include <TopTools_MapIteratorOfMapOfShape.hxx>
#include <TopTools_MapIteratorOfMapOfOrientedShape.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopExp_Explorer.hxx>
#include <BRep_Builder.hxx>
#include <TopoDS_Vertex.hxx>
#include <BRepLib_MakeFace.hxx>
#include <BRepLib_MakeWire.hxx>
#include <BRep_Tool.hxx>
#include <BRepTools.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <BRep_Builder.hxx>

#include <BRepClass_FaceExplorer.hxx>
#include <BRepTopAdaptor_FClass2d.hxx>
#include <BRepAdaptor_Surface.hxx>

#include <Geom2d_Curve.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Vec2d.hxx>
#include <gp_Dir2d.hxx>
#include <TopoDS.hxx>
#include <TopExp.hxx>
#include <Precision.hxx>
#include <BRepTools.hxx>
#include <LocOpe.hxx>
#include <Standard_ErrorHandler.hxx>

static Standard_Boolean IsInside(const TopoDS_Face&,
                                 const TopoDS_Wire&,
                                 const TopoDS_Wire&);

static Standard_Boolean IsInside(const TopoDS_Face&,
                                 const TopoDS_Wire&);

static void GetDirection(const TopoDS_Edge&,
                         const TopoDS_Face&,
                         Standard_Real&,
                         gp_Pnt2d&,
                         gp_Vec2d&);

static void ChoixUV(const TopoDS_Edge&,
                    const TopoDS_Face&,
                    const TopTools_IndexedMapOfShape&,
                    TopoDS_Edge&,
                    gp_Pnt2d&,
                    gp_Vec2d&,
                    const Standard_Real tol);

static TopoDS_Shape ChooseDirection(const TopoDS_Shape&,
                                    const TopoDS_Vertex&,
                                    const TopoDS_Face&,
                                    const TopTools_ListOfShape&);

inline Standard_Boolean SameUV(const gp_Pnt2d& P1, const gp_Pnt2d& P2, 
                               const BRepAdaptor_Surface& theBAS)//const Standard_Real tol)
{
  //  Standard_Real tol = Precision::Confusion();
  //  return P1.SquareDistance(P2) < 10*tol;
  //gka
  Standard_Boolean isSame = Standard_True;
  if(theBAS.IsUPeriodic())
    isSame = (fabs(P1.X() - P2.X()) < theBAS.UPeriod() *0.5);
  if(theBAS.IsVPeriodic())
    isSame = (isSame && (fabs(P1.Y() - P2.Y()) < theBAS.VPeriod() *0.5));
  return isSame;
  //return P1.SquareDistance(P2) < tol * tol; //IFV
}



//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void LocOpe_SplitShape::Init(const TopoDS_Shape& S)
{
  myDone = Standard_False;
  myShape = S;
  myDblE.Clear();
  myMap.Clear();
  Put(myShape);
}


//=======================================================================
//function : CanSplit
//purpose  : 
//=======================================================================

Standard_Boolean LocOpe_SplitShape::CanSplit(const TopoDS_Edge& E) const
{
  if (myDone) {
    return Standard_False;
  }
  if (myMap.IsEmpty()) {
    return Standard_False;
  }

  if (!myMap.IsBound(E)) {
    return Standard_False;
  }

  // On verifie que l`edge n`appartient pas a un wire deja reconstruit
  TopExp_Explorer exp;  
  TopTools_DataMapIteratorOfDataMapOfShapeListOfShape itm(myMap);
  for (; itm.More(); itm.Next()) {
    if (itm.Key().ShapeType() == TopAbs_WIRE && !itm.Value().IsEmpty()) {
      for (exp.Init(itm.Key(),TopAbs_EDGE); exp.More(); exp.Next()) {
        if (exp.Current().IsSame(E)) {
          return Standard_False;
        }
      }
    }
  }
  return Standard_True;
}


//=======================================================================
//function : Add
//purpose  : 
//=======================================================================

void LocOpe_SplitShape::Add(const TopoDS_Vertex& V,
                            const Standard_Real P,
                            const TopoDS_Edge& E)
{
  if (!CanSplit(E)) {
    Standard_ConstructionError::Raise();
  }

  BRep_Builder B;
  TopTools_ListOfShape& le = myMap(E);
  if (le.IsEmpty()) {
    le.Append(E);
  }
  TopTools_ListIteratorOfListOfShape itl(le);
  Standard_Real f,l;

  for (; itl.More(); itl.Next()) {
    const TopoDS_Edge& edg = TopoDS::Edge(itl.Value());
    BRep_Tool::Range(edg,f,l);
    if (P>f && P <l) {
      break;
    }
  }
  if (!itl.More()) {
    Standard_ConstructionError::Raise();
  }
  TopoDS_Edge edg = TopoDS::Edge(itl.Value());
  le.Remove(itl);
  if (V.Orientation() == TopAbs_FORWARD ||
    V.Orientation() == TopAbs_REVERSED) {

      TopoDS_Shape aLocalShape = edg.EmptyCopied();
      TopoDS_Edge E1 = TopoDS::Edge(aLocalShape);
      aLocalShape = edg.EmptyCopied();
      TopoDS_Edge E2 = TopoDS::Edge(aLocalShape);
      //    TopoDS_Edge E1 = TopoDS::Edge(edg.EmptyCopied());
      //    TopoDS_Edge E2 = TopoDS::Edge(edg.EmptyCopied());
      E1.Orientation(TopAbs_FORWARD);
      E2.Orientation(TopAbs_FORWARD);
      TopoDS_Vertex newVtx = V;
      newVtx.Orientation(TopAbs_REVERSED);
      B.Add(E1,newVtx);
      B.UpdateVertex(newVtx,P,E1,BRep_Tool::Tolerance(V));
      newVtx.Orientation(TopAbs_FORWARD);
      B.Add(E2,newVtx);
      B.UpdateVertex(newVtx,P,E2,BRep_Tool::Tolerance(V));
      edg.Orientation(TopAbs_FORWARD);
      TopExp_Explorer exp;
      for (exp.Init(edg,TopAbs_VERTEX); exp.More(); exp.Next()) {
        //    for (TopExp_Explorer exp(edg,TopAbs_VERTEX); exp.More(); exp.Next()) {
        const TopoDS_Vertex& vtx = TopoDS::Vertex(exp.Current());
        f = BRep_Tool::Parameter(vtx,edg);
        if (f < P) {
          B.Add(E1,vtx);
          B.UpdateVertex(vtx,f,E1,BRep_Tool::Tolerance(vtx));
        }
        else {
          B.Add(E2,vtx);
          B.UpdateVertex(vtx,f,E2,BRep_Tool::Tolerance(vtx));
        }
      }
      le.Append(E1);
      le.Append(E2);
  }
  else {
    TopoDS_Shape aLocalShape = edg.EmptyCopied();
    TopoDS_Edge E1 = TopoDS::Edge(aLocalShape);
    //    TopoDS_Edge E1 = TopoDS::Edge(edg.EmptyCopied());
    TopExp_Explorer exp;
    for (exp.Init(edg,TopAbs_VERTEX); exp.More(); exp.Next()) {
      //    for (TopExp_Explorer exp(edg,TopAbs_VERTEX); exp.More(); exp.Next()) {
      const TopoDS_Vertex& vtx = TopoDS::Vertex(exp.Current());
      f = BRep_Tool::Parameter(vtx,edg);
      B.Add(E1,vtx);
      B.UpdateVertex(vtx,f,E1,BRep_Tool::Tolerance(vtx));
    }
    B.Add(E1,V);
    B.UpdateVertex(V,P,E1,BRep_Tool::Tolerance(V));
    le.Append(E1);
  }
}

//=======================================================================
//function : Add
//purpose  : adds the list of wires on the face <F>
//=======================================================================

void LocOpe_SplitShape::Add(const TopTools_ListOfShape& Lwires,
                            const TopoDS_Face& F)
{

  if (myDone) {
    Standard_ConstructionError::Raise();
  }

  TopTools_ListOfShape& lf = myMap(F);
  if (lf.IsEmpty()) {
    Rebuild(F);
  }

  // On cherche la face descendante de F qui continent le wire
  lf = myMap(F);
  TopTools_ListIteratorOfListOfShape itl(lf);
  TopoDS_Vertex Vfirst,Vlast;

  BRepTools::Update(F);

  for (; itl.More(); itl.Next())
  {
    const TopoDS_Face& fac = TopoDS::Face(itl.Value());
    Standard_Boolean AllWiresInside = Standard_True;
    TopTools_ListIteratorOfListOfShape itwires(Lwires);
    for (; itwires.More(); itwires.Next())
    {
      const TopoDS_Wire& aWire = TopoDS::Wire(itwires.Value());
      if (!IsInside(fac, aWire))
      {
        AllWiresInside = Standard_False;
        break;
      }
    }
    if (AllWiresInside)
      break;
  }
  if (!itl.More()) {
    Standard_ConstructionError::Raise();
  }

  TopoDS_Face FaceRef = TopoDS::Face(itl.Value());
  FaceRef.Orientation(TopAbs_FORWARD);
  lf.Remove(itl);

  TopTools_ListOfShape NewWires;

  TopTools_DataMapOfShapeInteger SectionsTimes;
  for (itl.Initialize(Lwires); itl.More(); itl.Next())
    SectionsTimes.Bind(itl.Value(), 2);
  
  TopTools_ListOfShape BreakVertices;
  TopTools_ListOfShape BreakOnWires;

  TopTools_DataMapOfShapeShape VerWireMap;
  Standard_Integer i;
  TopExp_Explorer ExploF, ExploW;
  for (itl.Initialize(Lwires); itl.More(); itl.Next())
  {
    const TopoDS_Wire& aSection = TopoDS::Wire(itl.Value());
    TopoDS_Vertex Ver [2];
    TopExp::Vertices(aSection, Ver[0], Ver[1]);
    for (i = 0; i < 2; i++)
    {
      if (VerWireMap.IsBound(Ver[i]))
        continue;
      for (ExploF.Init(FaceRef, TopAbs_WIRE); ExploF.More(); ExploF.Next())
      {
        const TopoDS_Shape& aWire = ExploF.Current();
        TopoDS_Shape aVer;
        for (ExploW.Init(aWire, TopAbs_VERTEX); ExploW.More(); ExploW.Next())
        {
          aVer = ExploW.Current();
          if (aVer.IsSame(Ver[i]))
            break;
        }
        if (aVer.IsSame(Ver[i]))
        {
          VerWireMap.Bind(aVer, aWire);
          break;
        }
      }
    }
  }  
  
  TopTools_DataMapOfShapeListOfShape VerSecMap;
  for (itl.Initialize(Lwires); itl.More(); itl.Next())
  {
    const TopoDS_Wire& aWire = TopoDS::Wire(itl.Value());
    TopoDS_Vertex V1, V2;
    TopExp::Vertices(aWire, V1, V2);
    TopTools_ListOfShape LW1, LW2;
    if (!VerSecMap.IsBound(V1))
      VerSecMap.Bind(V1, LW1);
    VerSecMap(V1).Append(aWire);
    if (!VerSecMap.IsBound(V2))
      VerSecMap.Bind(V2, LW2);
    VerSecMap(V2).Append(aWire);
  }

  //TopTools_IndexedDataMapOfShapeShape InnerTouchingWiresOnVertex;
  
  TopoDS_Wire outerW = BRepTools::OuterWire(FaceRef);
  TopoDS_Wire CurWire = outerW;
  BRepLib_MakeWire *MW;
  MW = new BRepLib_MakeWire();
  BRepTools_WireExplorer wexp(CurWire, FaceRef);
  for (;;)
  {
    TopoDS_Vertex theStartVertex = wexp.CurrentVertex(), CurVertex;
    TopoDS_Edge CurEdge = wexp.Current();
    TopoDS_Edge LastEdge = CurEdge;
    MW->Add(CurEdge);
    TopoDS_Wire aSectionWire;
    TopoDS_Vertex aBreakVertex;
    wexp.Next();
    if (!wexp.More())
      wexp.Init(CurWire, FaceRef);
    for (;;)
    {
      if (MW->Wire().Closed())
        break;
      CurVertex = wexp.CurrentVertex();
      if (VerSecMap.IsBound(CurVertex))
      {
        TopoDS_Shape aLocalWire = ChooseDirection(LastEdge, CurVertex, FaceRef, VerSecMap(CurVertex));
        aSectionWire = TopoDS::Wire(aLocalWire);
        break;
      }
      CurEdge = wexp.Current();
      MW->Add(CurEdge);
      LastEdge = CurEdge;
      wexp.Next();
      if (!wexp.More())
        wexp.Init(CurWire, FaceRef);
    }
    if (MW->Wire().Closed())
    {
      NewWires.Append(MW->Wire());
      theStartVertex = TopoDS::Vertex(BreakVertices.First());
      BreakVertices.RemoveFirst();
      CurWire = TopoDS::Wire(BreakOnWires.First());
      BreakOnWires.RemoveFirst();
      wexp.Init(CurWire, FaceRef);
      while (!wexp.CurrentVertex().IsSame(theStartVertex))
        wexp.Next();
      MW = new BRepLib_MakeWire();
      continue;
    }
    aBreakVertex = CurVertex;
    BreakVertices.Append(aBreakVertex);
    BreakOnWires.Append(CurWire);
    for (;;)
    {
      MW->Add(aSectionWire);
      (SectionsTimes(aSectionWire))--;
      if (SectionsTimes(aSectionWire) == 0)
        SectionsTimes.UnBind(aSectionWire);
      if (MW->Wire().Closed())
      {
        NewWires.Append(MW->Wire());
        if (SectionsTimes.IsEmpty())
          break;
        theStartVertex = TopoDS::Vertex(BreakVertices.First());
        BreakVertices.RemoveFirst();
        CurWire = TopoDS::Wire(BreakOnWires.First());
        BreakOnWires.RemoveFirst();
        wexp.Init(CurWire, FaceRef);
        while (!wexp.CurrentVertex().IsSame(theStartVertex))
          wexp.Next();
        MW = new BRepLib_MakeWire();
        break;
      }
      else
      {
        TopoDS_Vertex V1, V2, aStartVertex;
        TopExp::Vertices(aSectionWire, V1, V2);
        aStartVertex = (V1.IsSame(aBreakVertex))? V2 : V1;
        CurWire = TopoDS::Wire(VerWireMap(aStartVertex));
        
        wexp.Init(CurWire, FaceRef);
        while (!wexp.CurrentVertex().IsSame(aStartVertex))
          wexp.Next();
            
        const TopTools_ListOfShape& Lsections = VerSecMap(aStartVertex);
        if (Lsections.Extent() == 1)
          break;
        
        //else: choose the way
        TopoDS_Wire NextSectionWire =
          TopoDS::Wire((aSectionWire.IsSame(Lsections.First()))? Lsections.Last() : Lsections.First());
        
        Standard_Integer Times = 0;
        TopTools_DataMapIteratorOfDataMapOfShapeShape itVW(VerWireMap);
        for (; itVW.More(); itVW.Next())
          if (itVW.Value().IsSame(CurWire))
            Times++;
        if (Times == 1) //it is inner touching wire
        {
          //InnerTouchingWiresOnVertex.Bind(aWire, aStartVertex);
        }
        else
          {
            //we have to choose the direction
            TopoDS_Edge aStartEdge = wexp.Current();
            TopTools_ListOfShape Ldirs;
            Ldirs.Append(aStartEdge);
            Ldirs.Append(NextSectionWire);
            TopoDS_Shape theDirection = ChooseDirection(aSectionWire, aStartVertex, FaceRef, Ldirs);
            if (theDirection.IsSame(aStartEdge))
              break;
          }
        aSectionWire = NextSectionWire;
        aBreakVertex = aStartVertex;
      } //end of else (MW is not closed)
    } //end of for (;;) (loop on section wires)
    if (SectionsTimes.IsEmpty())
      break;
  } //end of global for (;;)

  TopTools_ListOfShape NewFaces;
  BRep_Builder BB;
  for (itl.Initialize(NewWires); itl.More(); itl.Next())
  {
    TopoDS_Shape aLocalFace = FaceRef.EmptyCopied();
    TopoDS_Face aNewFace = TopoDS::Face(aLocalFace);
    aNewFace.Orientation(TopAbs_FORWARD);
    BB.Add(aNewFace, itl.Value());
    NewFaces.Append(aNewFace);
  }

  //Inserting holes
  TopTools_ListOfShape Holes;
  for (ExploF.Init(FaceRef, TopAbs_WIRE); ExploF.More(); ExploF.Next())
  {
    const TopoDS_Shape& aWire = ExploF.Current();
    ExploW.Init(aWire, TopAbs_EDGE);
    TopoDS_Shape anEdge = ExploW.Current();
    Standard_Boolean found = Standard_False;
    for (itl.Initialize(NewWires); itl.More(); itl.Next())
    {
      const TopoDS_Shape& aNewWire = itl.Value();
      for (ExploW.Init(aNewWire, TopAbs_EDGE); ExploW.More(); ExploW.Next())
      {
        if (anEdge.IsSame(ExploW.Current()))
        {
          found = Standard_True;
          break;
        }
      }
      if (found)
        break;
    }
    if (!found)
      Holes.Append(aWire);
  }
  TopTools_ListIteratorOfListOfShape itlNewF;
  for (itl.Initialize(Holes); itl.More(); itl.Next())
  {
    const TopoDS_Wire& aHole = TopoDS::Wire(itl.Value());
    for (itlNewF.Initialize(NewFaces); itlNewF.More(); itlNewF.Next())
    {
      TopoDS_Face& aNewFace = TopoDS::Face(itlNewF.Value());
      if (IsInside(aNewFace, aHole))
      {
        BB.Add(aNewFace, aHole);
        break;
      }
    }
  }

  //Update "myMap"
  lf.Append(NewFaces);

  //Update of descendants of wires
  for (ExploF.Init(F, TopAbs_WIRE); ExploF.More(); ExploF.Next())
  {
    TopTools_ListOfShape& ls = myMap(ExploF.Current());
    ls.Clear();
  }
  ///////////////////
  
  // JAG 10.11.95 Codage des regularites
  for (itl.Initialize(Lwires); itl.More(); itl.Next())
    for (ExploW.Init(itl.Value(), TopAbs_EDGE); ExploW.More(); ExploW.Next())
    {
      const TopoDS_Edge& edg = TopoDS::Edge(ExploW.Current());
      if (!BRep_Tool::HasContinuity(edg,F,F)) {
        BB.Continuity(edg,F,F,GeomAbs_CN);
      }
    }
}


//=======================================================================
//function : Add
//purpose  : 
//=======================================================================

void LocOpe_SplitShape::Add(const TopoDS_Wire& W,
                            const TopoDS_Face& F)
{

  if (myDone) {
    Standard_ConstructionError::Raise();
  }


  TopExp_Explorer exp;
  TopTools_ListOfShape& lf = myMap(F);
  if (lf.IsEmpty()) {
    Rebuild(F);
  }
  try {
    OCC_CATCH_SIGNALS
    if (!LocOpe::Closed(W,F)) {
      AddOpenWire(W,F);
    }
    else {
      AddClosedWire(W,F);
    }
  } catch (Standard_Failure ) {
#ifdef OCCT_DEBUG
    cout << "Warning: SpliShape internal problem detected, some faces may be lost. Check input edges/wires" <<endl;
#endif
    return;
  }
  // JAG 10.11.95 Codage des regularites
  BRep_Builder B;
  for (exp.Init(W,TopAbs_EDGE); exp.More(); exp.Next()) {
    const TopoDS_Edge& edg = TopoDS::Edge(exp.Current());
    if (!BRep_Tool::HasContinuity(edg,F,F)) {
      B.Continuity(edg,F,F,GeomAbs_CN);
    }
  }
}



//=======================================================================
//function : AddClosedWire
//purpose  : 
//=======================================================================

void LocOpe_SplitShape::AddClosedWire(const TopoDS_Wire& W,
                                      const TopoDS_Face& F)
{
  TopExp_Explorer exp;

  // On cherche la face descendante de F qui continent le wire
  TopTools_ListOfShape& lf = myMap(F);
  TopTools_ListIteratorOfListOfShape itl(lf);
  TopoDS_Wire outerW;
  for (; itl.More(); itl.Next()) {
    const TopoDS_Face& fac = TopoDS::Face(itl.Value());
    /*
    outerW = BRepTools::OuterWire(fac);
    if (IsInside(F,W,outerW)) {
    break;
    }
    */
    if (IsInside(fac,W)) {
      break;
    }

  }
  if (!itl.More()) {
    Standard_ConstructionError::Raise();
  }

  BRep_Builder B;

  TopAbs_Orientation orWire = W.Orientation();
  TopoDS_Shape aLocalFace = F.EmptyCopied();
  TopoDS_Face newFace = TopoDS::Face(aLocalFace);
  //  TopoDS_Face newFace = TopoDS::Face(F.EmptyCopied());
  newFace.Orientation(TopAbs_FORWARD);
  B.Add(newFace,W);
  //  GProp_GProps GP;
  //  BRepGProp::SurfaceProperties (newFace,GP);
  //  if (GP.Mass() < 0) {
  BRepTopAdaptor_FClass2d classif(newFace,Precision::PConfusion());
  if (classif.PerformInfinitePoint() == TopAbs_IN) {
    //le wire donne defini un trou
    aLocalFace = F.EmptyCopied();
    newFace = TopoDS::Face(aLocalFace);
    //    newFace = TopoDS::Face(F.EmptyCopied());
    newFace.Orientation(TopAbs_FORWARD);
    orWire = TopAbs::Reverse(orWire);
    B.Add(newFace,W.Oriented(orWire));
  }

  TopoDS_Face FaceRef = TopoDS::Face(itl.Value());
  FaceRef.Orientation(TopAbs_FORWARD);
  lf.Remove(itl);

  aLocalFace = FaceRef.EmptyCopied();
  TopoDS_Face newRef = TopoDS::Face(aLocalFace);
  //  TopoDS_Face newRef = TopoDS::Face(FaceRef.EmptyCopied());
  newRef.Orientation(TopAbs_FORWARD);

  // On suppose que les edges du wire ont des courbes 2d. 
  // Comme on ne change pas de surface de base, pas besoin d`UpdateEdge.

  for (exp.Init(FaceRef.Oriented(TopAbs_FORWARD),TopAbs_WIRE);
    exp.More(); exp.Next()) {
      const TopoDS_Wire& wir = TopoDS::Wire(exp.Current());
      if (IsInside(F,wir,W)) {
        B.Add(newFace,wir);
      }
      else {
        B.Add(newRef,wir);
      }
  }
  B.Add(newRef,W.Oriented(TopAbs::Reverse(orWire)));
  lf.Append(newRef);
  lf.Append(newFace);

}


//=======================================================================
//function : AddOpenWire
//purpose  : 
//=======================================================================

void LocOpe_SplitShape::AddOpenWire(const TopoDS_Wire& W,
                                    const TopoDS_Face& F)
{
  // On cherche la face descendante de F qui continent le wire
  TopTools_ListOfShape& lf = myMap(F);
  TopTools_ListIteratorOfListOfShape itl(lf);
  TopoDS_Vertex Vfirst,Vlast;

  BRepTools::Update(F);

  Standard_Real tolf, toll, tol1;

  TopoDS_Shape aLocalShape = W.Oriented(TopAbs_FORWARD);
  TopExp::Vertices(TopoDS::Wire(aLocalShape),Vfirst,Vlast);

  tolf = BRep_Tool::Tolerance(Vfirst);
  toll = BRep_Tool::Tolerance(Vlast);
  tol1 = Max(tolf, toll);


  TopExp_Explorer exp,exp2;  

  TopoDS_Wire wfirst,wlast;
  for (; itl.More(); itl.Next()) {
    TopoDS_Face fac = TopoDS::Face(itl.Value());
    if (!IsInside(fac,W)) {
      continue;
    }
    
    fac.Orientation(TopAbs_FORWARD);
    Standard_Boolean ffound = Standard_False;
    Standard_Boolean lfound = Standard_False;
    for (exp.Init(fac,TopAbs_WIRE); exp.More(); exp.Next()) {
      const TopoDS_Wire& wir = TopoDS::Wire(exp.Current());
      for (exp2.Init(wir,TopAbs_VERTEX); exp2.More(); exp2.Next()) {
        if (!ffound && exp2.Current().IsSame(Vfirst)) {
          ffound = Standard_True;
          wfirst = wir;
        }
        else if (!lfound && exp2.Current().IsSame(Vlast)) {
          lfound = Standard_True;
          wlast = wir;
        }
        if (ffound && lfound) {
          break;
        }
      }
      if (exp2.More()) {
        break;
      }
    }
    if (exp.More()) {
      break;
    }
  }
  if (!itl.More()) {
    Standard_ConstructionError::Raise();
  }

  TopoDS_Face FaceRef = TopoDS::Face(itl.Value());
  FaceRef.Orientation(TopAbs_FORWARD);
  lf.Remove(itl);
  BRep_Builder B;

  BRepAdaptor_Surface BAS(FaceRef, Standard_False);

  Standard_Boolean IsPeriodic = BAS.IsUPeriodic() || BAS.IsVPeriodic();

  tol1 = Max(BAS.UResolution(tol1), BAS.VResolution(tol1));

  if (wfirst.IsSame(wlast)) {
    // on cree 2 faces en remplacement de itl.Value()
    // Essai JAG
    TopTools_ListOfShape WiresFirst;
    for (exp.Init(wfirst,TopAbs_EDGE); exp.More(); exp.Next()) {
      if (BRep_Tool::IsClosed(TopoDS::Edge(exp.Current()),FaceRef)) {
        myDblE.Add(exp.Current());
      }
      WiresFirst.Append(exp.Current());      
    }

    TopAbs_Orientation orient;
    TopoDS_Wire newW1,newW2;
    B.MakeWire(newW1);
    newW1.Orientation(TopAbs_FORWARD);
    B.MakeWire(newW2);
    newW2.Orientation(TopAbs_FORWARD);

    Standard_Integer nbE = 0;    
    for (exp.Init(W.Oriented(TopAbs_FORWARD),TopAbs_EDGE);
         exp.More(); exp.Next()) {
      nbE++;
      const TopoDS_Edge& edg = TopoDS::Edge(exp.Current());
      orient = edg.Orientation();      
      WiresFirst.Append(edg);
      WiresFirst.Append(edg.Oriented(TopAbs::Reverse(orient)));
      myDblE.Add(edg);
    }    

    TopTools_IndexedMapOfShape PossE;
    TopTools_MapOfOrientedShape MapE;
    TopoDS_Vertex vdeb,vfin;
    Standard_Integer nbPoss;

    // On recherche l`edge contenant Vlast
    TopoDS_Edge LastEdge;
    gp_Pnt2d pfirst,plast;
    gp_Vec2d dlast;
    Handle(Geom2d_Curve) C2d;
    Standard_Real f,l;

    for (exp.Init(W.Oriented(TopAbs_FORWARD),TopAbs_EDGE); 
         exp.More(); exp.Next()) {
      const TopoDS_Edge& edg = TopoDS::Edge(exp.Current());
      for (exp2.Init(edg,TopAbs_VERTEX); exp2.More(); exp2.Next()) {
        if (exp2.Current().IsSame(Vfirst)) {
          break;
        }
      }
      if (exp2.More()) {
        LastEdge = edg;
        LastEdge.Orientation(edg.Orientation());
        break;
      }
    }

    TopoDS_Shape aLocalFace = FaceRef.Oriented(wfirst.Orientation());
    C2d = BRep_Tool::CurveOnSurface(LastEdge, TopoDS::Face(aLocalFace), f, l);

    if (LastEdge.Orientation() == TopAbs_FORWARD) {
      pfirst = C2d->Value(f);
    }
    else {
      pfirst = C2d->Value(l);
    }

    for (exp.Init(W.Oriented(TopAbs_FORWARD),TopAbs_EDGE); 
         exp.More(); exp.Next()) {
      const TopoDS_Edge& edg = TopoDS::Edge(exp.Current());
      if( nbE>1 && edg.IsSame(LastEdge) )
        continue;
      for (exp2.Init(edg,TopAbs_VERTEX); exp2.More(); exp2.Next()) {
        if (exp2.Current().IsSame(Vlast)) {
          break;
        }
      }
      if (exp2.More()) {
        LastEdge = edg;
        LastEdge.Orientation(edg.Orientation());
        break;
      }
    }
    aLocalFace  = FaceRef.Oriented(wfirst.Orientation());
    C2d = BRep_Tool::CurveOnSurface(LastEdge, TopoDS::Face(aLocalFace), f, l);
    Standard_Real dpar = (l - f)*0.01;
 
    if (LastEdge.Orientation() == TopAbs_FORWARD) {
      C2d->D1(l,plast,dlast);
      if (dlast.Magnitude() < gp::Resolution())
      {
        gp_Pnt2d PrevPnt = C2d->Value(l - dpar);
        dlast.SetXY(plast.XY() - PrevPnt.XY());
      }
    }
    else {
      C2d->D1(f,plast,dlast);
      if (dlast.Magnitude() < gp::Resolution())
      {
        gp_Pnt2d NextPnt = C2d->Value(f + dpar);
        dlast.SetXY(NextPnt.XY() - plast.XY());
      }
      dlast.Reverse();
    }

    Standard_Boolean cond;

    if(IsPeriodic) {

      cond = !(Vfirst.IsSame(Vlast) && SameUV(pfirst,plast,BAS));
    }
    else {
      cond = !(Vfirst.IsSame(Vlast));
    }
        
    while (cond) {      
      PossE.Clear();
      
      // On enchaine par la fin      
      TopTools_ListIteratorOfListOfShape lexp(WiresFirst);
      for (; lexp.More(); lexp.Next()) {
        const TopoDS_Edge& edg = TopoDS::Edge(lexp.Value());        

        orient = edg.Orientation();
        TopExp::Vertices(edg,vdeb,vfin);
        if (orient == TopAbs_FORWARD && Vlast.IsSame(vdeb)) {
          PossE.Add(edg.Oriented(orient));
        }
        else if (orient == TopAbs_REVERSED && Vlast.IsSame(vfin)) {
          PossE.Add(edg.Oriented(orient));
        }
      }
      nbPoss = PossE.Extent();
      if (nbPoss == 0)
      {
        break;
      }

      TopoDS_Edge aNextEdge;
      if (nbPoss == 1) {
        aNextEdge = TopoDS::Edge (PossE.FindKey (1));
        TopoDS_Shape aLocalFace  = FaceRef.Oriented(wfirst.Orientation());
        C2d = BRep_Tool::CurveOnSurface(aNextEdge,
                                        TopoDS::Face(aLocalFace), f, l);
        Standard_Real dpar = (l - f)*0.01;

        if (aNextEdge.Orientation() == TopAbs_FORWARD) {
          C2d->D1(l,plast,dlast);
          if (dlast.Magnitude() < gp::Resolution())
          {
            gp_Pnt2d PrevPnt = C2d->Value(l - dpar);
            dlast.SetXY(plast.XY() - PrevPnt.XY());
          }
        }
        else {
          C2d->D1(f,plast,dlast);
          if (dlast.Magnitude() < gp::Resolution())
          {
            gp_Pnt2d NextPnt = C2d->Value(f + dpar);
            dlast.SetXY(NextPnt.XY() - plast.XY());
          }
          dlast.Reverse();
        }
      }
      else if (nbPoss > 1) {
        // Faire choix en U,V...
        TopoDS_Shape aLocalFace  = FaceRef.Oriented(wfirst.Orientation());
        
        ChoixUV(LastEdge, TopoDS::Face(aLocalFace), PossE,
                aNextEdge, plast, dlast, toll);
      }

      if (nbPoss >= 1) {
        if (aNextEdge.IsNull())
        {
          // loop is not closed. Split is not possible
          Standard_ConstructionError::Raise("Split is not possible: split loop is not closed"); 
        }

        if (MapE.Contains(aNextEdge)) 
          break;
        B.Add(newW1, aNextEdge);
        MapE.Add(aNextEdge);        
        LastEdge = aNextEdge;
        
        if (LastEdge.Orientation() == TopAbs_FORWARD) {
          Vlast = TopExp::LastVertex(LastEdge);
        }
        else {
          Vlast = TopExp::FirstVertex(LastEdge);
        }
        
        toll = BRep_Tool::Tolerance(Vlast);
        tol1 = Max(tolf, toll);
        
      }
      //MODIFICATION PIERRE SMEYERS : si pas de possibilite, on sort avec erreur
      else{
        cout<<"erreur Spliter : pas de chainage du wire"<<endl;
        Standard_ConstructionError::Raise();        
      }
      //fin MODIF.
      
      tol1 = Max(BAS.UResolution(tol1), BAS.VResolution(tol1));
      
    }
    
    TopTools_ListIteratorOfListOfShape lexp(WiresFirst);
    for (; lexp.More(); lexp.Next()) {    
      const TopoDS_Edge& edg = TopoDS::Edge(lexp.Value());
      if (!MapE.Contains(edg)) {
        B.Add(newW2,edg);
        MapE.Add(edg);
      }
    }        
   
    TopoDS_Face newF1,newF2;
    aLocalFace = FaceRef.EmptyCopied();
    newF1 = TopoDS::Face(aLocalFace);
    newF1.Orientation(TopAbs_FORWARD);
    aLocalFace = FaceRef.EmptyCopied();
    newF2 = TopoDS::Face(aLocalFace);
    newF2.Orientation(TopAbs_FORWARD);
    
    // modifs JAG 97.05.28

    B.Add(newF1,newW1);
    //BRepTools::Write(newF1, "k:/queries/WrongBOP/NewF1.brep");
    B.Add(newF2,newW2);
    //BRepTools::Write(newF2, "k:/queries/WrongBOP/NewF2.brep");
    
    for (exp.Init(FaceRef.Oriented(TopAbs_FORWARD),TopAbs_WIRE); exp.More(); exp.Next()) {
      const TopoDS_Wire& wir = TopoDS::Wire(exp.Current());
      if (!wir.IsSame(wfirst)) {
        if (IsInside(newF1, wir)) {
          B.Add(newF1,wir);
        }
        else if (IsInside(newF2, wir)) {
          B.Add(newF2,wir);
        }
        else {
          // Ce wire est ni dans newF2 ni dans newF1
          // Peut etre faut il construire une troisieme face
          cout << "WARNING: LocOpe_SPlitShape : Ce wire est ni dans newF2 ni dans newF1" << endl;
        }
      }
    }
    lf.Append(newF1);
    lf.Append(newF2);
    
    // Mise a jour des descendants des wires
    for (exp.Init(F,TopAbs_WIRE); exp.More(); exp.Next()) {
      TopTools_ListOfShape& ls = myMap(exp.Current());
      itl.Initialize(ls);
      for (; itl.More(); itl.Next()) {
        if (itl.Value().IsSame(wfirst)) {
          break;
        }
      }
      if (itl.More()) { // on a trouve le wire
        ls.Remove(itl);
        ls.Append(newW1);
        ls.Append(newW2);
      }
    }
  }
  else {
    // on ne cree qu`une seule face
    TopoDS_Wire outerW = BRepTools::OuterWire(FaceRef);
    TopoDS_Wire newWire;
    TopoDS_Face newFace;
    B.MakeWire(newWire);
    newWire.Orientation(TopAbs_FORWARD);
    TopAbs_Orientation orient,orRelat;

    if (wfirst.Orientation() == wlast.Orientation()) {
      orRelat = TopAbs_FORWARD;
    }
    else {
      orRelat = TopAbs_REVERSED;
    }

    if (wlast.IsSame(outerW)) {
      wlast = wfirst;
      wfirst = outerW;
    }
    
    // Edges de wfirst
    for (exp.Init(wfirst.Oriented(TopAbs_FORWARD),TopAbs_EDGE);
         exp.More(); exp.Next()) {
      B.Add(newWire,TopoDS::Edge(exp.Current()));
    }

    // Edges de wlast
    for (exp.Init(wlast.Oriented(TopAbs_FORWARD),TopAbs_EDGE);
         exp.More(); exp.Next()) {
      const TopoDS_Edge& edg = TopoDS::Edge(exp.Current());
      orient = TopAbs::Compose(edg.Orientation(),orRelat);
      B.Add(newWire,edg.Oriented(orient));
    }
    

    // Edges du wire ajoute, et dans les 2 sens
    for (exp.Init(W.Oriented(TopAbs_FORWARD),TopAbs_EDGE);
         exp.More(); exp.Next()) {
      const TopoDS_Edge& edg = TopoDS::Edge(exp.Current());
      orient = edg.Orientation();
      B.Add(newWire,edg.Oriented(orient));
      B.Add(newWire,edg.Oriented(TopAbs::Reverse(orient)));
      myDblE.Add(edg.Oriented(orient));
    }
    
    // on refait une face

    TopoDS_Shape aLocalFace = FaceRef.EmptyCopied();
    newFace = TopoDS::Face(aLocalFace);
    //    newFace = TopoDS::Face(FaceRef.EmptyCopied());
    FaceRef.Orientation(TopAbs_FORWARD);
    for (exp.Init(FaceRef.Oriented(TopAbs_FORWARD),TopAbs_WIRE); 
         exp.More(); exp.Next()) {
      const TopoDS_Wire& wir = TopoDS::Wire(exp.Current());
      if (wir.IsSame(wfirst)) {
        B.Add(newFace,newWire.Oriented(wir.Orientation()));
      }
      else if (!wir.IsSame(wlast)) {
        B.Add(newFace,wir);
      }
    }
    lf.Append(newFace);
    
    // Mise a jour des descendants des wires
    for (exp.Init(F,TopAbs_WIRE); exp.More(); exp.Next()) {
      TopTools_ListOfShape& ls = myMap(exp.Current());
      itl.Initialize(ls);
      Standard_Boolean touch = Standard_False;
      while (itl.More()) {
        if (itl.Value().IsSame(wfirst) || itl.Value().IsSame(wlast)) {
          ls.Remove(itl);
          touch = Standard_True;
        }
        else {
          itl.Next();
        }
      }
      if (touch) {
        ls.Append(newWire);
      }
      
    }
  }
}


//=======================================================================
//function : LeftOf
//purpose  : 
//=======================================================================

const TopTools_ListOfShape& LocOpe_SplitShape::LeftOf(const TopoDS_Wire& W,
                                                      const TopoDS_Face& F)
{
  if (myShape.IsNull()) {
    Standard_NoSuchObject::Raise();
  }

  TopExp_Explorer exp,expw,expf;
  exp.Init(myShape,TopAbs_FACE);
  for (; exp.More(); exp.Next()) {
    if (exp.Current().IsSame(F)) {
      break;
    }
  }
  if (!exp.More()) {
    Standard_NoSuchObject::Raise();
  }
  myLeft.Clear();

  const TopoDS_Face& theFace = TopoDS::Face(exp.Current());
  TopAbs_Orientation orFace = theFace.Orientation();
  TopTools_ListIteratorOfListOfShape itl,itl2;

  for (expw.Init(W,TopAbs_EDGE); expw.More(); expw.Next()) {
    const TopoDS_Edge& edg = TopoDS::Edge(expw.Current());
    for (itl.Initialize(myMap(theFace)); itl.More(); itl.Next()) {
      TopoDS_Face fac = TopoDS::Face(itl.Value());
      fac.Orientation(orFace);
      for (expf.Init(fac,TopAbs_EDGE); expf.More(); expf.Next()) {
        const TopoDS_Edge& edgbis = TopoDS::Edge(expf.Current());
        if (edgbis.IsSame(edg) && 
          edgbis.Orientation() == edg.Orientation()) {
            for (itl2.Initialize(myLeft); itl2.More(); itl2.Next()) {
              if (itl2.Value().IsSame(fac)) {
                break;
              }
            }
            if (!itl2.More()) { // la face n`est pas deja presente
              myLeft.Append(fac);
            }
            break;
        }
      }
      if (expf.More()) { // face found
        break;
      }
    }
  }
  return myLeft;
}


//=======================================================================
//function : DescendantShapes
//purpose  : 
//=======================================================================

const TopTools_ListOfShape& LocOpe_SplitShape::DescendantShapes
(const TopoDS_Shape& S)
{
  if (!myDone) {
    Rebuild(myShape);
    myDone = Standard_True;
  }
#ifdef OCCT_DEBUG
  if (!myDblE.IsEmpty()) {
    cout << "Le shape comporte des faces invalides" << endl;
  }
#endif
  return myMap(S);
}



//=======================================================================
//function : Put
//purpose  : 
//=======================================================================

void LocOpe_SplitShape::Put(const TopoDS_Shape& S)
{
  if (!myMap.IsBound(S)) {
    TopTools_ListOfShape thelist;
    myMap.Bind(S, thelist);
    if (S.ShapeType() != TopAbs_VERTEX) {
      for(TopoDS_Iterator theIterator(S);theIterator.More();
        theIterator.Next()) {
          Put(theIterator.Value());
      }
    }
    else {
      myMap(S).Append(S);
    }
  }
}


//=======================================================================
//function : Rebuild
//purpose  : 
//=======================================================================

Standard_Boolean LocOpe_SplitShape::Rebuild(const TopoDS_Shape& S)

{

  TopTools_ListIteratorOfListOfShape itr(myMap(S));
  if (itr.More()) {
    if (itr.Value().IsSame(S)) {
      return Standard_False;
    }
    return Standard_True;
  }
  Standard_Boolean rebuild = Standard_False;
  TopoDS_Iterator it;
  for(it.Initialize(S); it.More(); it.Next()) {
    rebuild = Rebuild(it.Value()) || rebuild;
  }

  if (rebuild) {
    BRep_Builder B;
    TopoDS_Shape result = S.EmptyCopied();
    TopAbs_Orientation orient;
    for(it.Initialize(S); it.More(); it.Next()) {
      orient = it.Value().Orientation();
      for (itr.Initialize(myMap(it.Value())); itr.More(); itr.Next()) {
        B.Add(result,itr.Value().Oriented(orient));
      }
    }
    // Assign "Closed" flag for Wires and Shells only
    if (result.ShapeType() == TopAbs_WIRE || result.ShapeType() == TopAbs_SHELL)
      result.Closed (BRep_Tool::IsClosed(result));
    myMap(S).Append(result);
  }
  else {
    myMap(S).Append(S);
  }
  return rebuild;
}



//=======================================================================
//function : IsInside
//purpose  : 
//=======================================================================

static Standard_Boolean IsInside(const TopoDS_Face& F,
                                 const TopoDS_Wire& W1,
                                 const TopoDS_Wire& W2)
{
  // Attention, c`est tres boeuf !!!!
  BRep_Builder B;
  TopoDS_Shape aLocalShape = F.EmptyCopied();
  TopoDS_Face newFace = TopoDS::Face(aLocalShape);
  //  TopoDS_Face newFace = TopoDS::Face(F.EmptyCopied());

  //TopAbs_Orientation orWire = W2.Orientation();
    
  newFace.Orientation(TopAbs_FORWARD);
  B.Add(newFace,W2);
  //  GProp_GProps GP;
  //  BRepGProp::SurfaceProperties(newFace,GP);
  //  if (GP.Mass() < 0) {
  BRepTopAdaptor_FClass2d classif(newFace,Precision::PConfusion());
  Standard_Boolean Reversed = Standard_False;
  if (classif.PerformInfinitePoint() == TopAbs_IN) {
    //le wire donne defini un trou
    //    newFace = TopoDS::Face(F.EmptyCopied());
    //    newFace.Orientation(TopAbs_FORWARD);
    //    orWire = TopAbs::Reverse(orWire);
    //    B.Add(newFace,W2.Oriented(orWire));
    Reversed = Standard_True;
  }

  //  Standard_Real U,V;
  TopExp_Explorer exp(W1,TopAbs_EDGE);
  const TopoDS_Edge& edg = TopoDS::Edge(exp.Current());
  TopExp_Explorer exp2(edg,TopAbs_VERTEX);
  const TopoDS_Vertex& vtx = TopoDS::Vertex(exp2.Current());
  Standard_Real prm = BRep_Tool::Parameter(vtx,edg);
  Standard_Real f,l;
  Handle(Geom2d_Curve) C2d = BRep_Tool::CurveOnSurface(edg,F,f,l);
  if(C2d.IsNull()) {
#ifdef OCCT_DEBUG
	  cout << "Edge is not on surface" <<endl;
#endif
      return Standard_False;
  }
  gp_Pnt2d pt2d(C2d->Value(prm));
  //  BRepClass_FaceClassifier classif(newFace,pt2d,Precision::PConfusion());
  //  return (classif.State() == TopAbs_IN);
  if (!Reversed) {
    return (classif.Perform(pt2d) == TopAbs_IN);
  }
  else {
    return (classif.Perform(pt2d) == TopAbs_OUT);
  }
}


//=======================================================================
//function : IsInside
//purpose  : 
//=======================================================================

static Standard_Boolean IsInside(const TopoDS_Face& F,
                                 const TopoDS_Wire& W)
{
  // Attention, c`est tres boeuf !!!!
  TopExp_Explorer exp(W,TopAbs_EDGE);
  for( ; exp.More(); exp.Next()) {
    const TopoDS_Edge& edg = TopoDS::Edge(exp.Current());
    //  TopExp_Explorer exp2(edg,TopAbs_VERTEX);
    //  const TopoDS_Vertex& vtx = TopoDS::Vertex(exp2.Current());
    //  Standard_Real prm = BRep_Tool::Parameter(vtx,edg);
    Standard_Real f,l,prm;
    Handle(Geom2d_Curve) C2d = BRep_Tool::CurveOnSurface(edg,F,f,l);
    if (!Precision::IsNegativeInfinite(f) && 
      !Precision::IsPositiveInfinite(l)) {
        prm = (f+l)/2.;
    }
    else {
      if (Precision::IsNegativeInfinite(f) && 
        Precision::IsPositiveInfinite(l)){
          prm = 0.;
      }
      else if (Precision::IsNegativeInfinite(f)) {
        prm = l-1.;
      }
      else {
        prm = f+1.;
      }
    }

    gp_Pnt2d pt2d(C2d->Value(prm));
    //  BRepClass_FaceClassifier classif(F,pt2d,Precision::PConfusion());
    //  return (classif.State() != TopAbs_OUT);
    BRepTopAdaptor_FClass2d classif(F,Precision::PConfusion());
    TopAbs_State stat = classif.Perform(pt2d);
    //  return (classif.Perform(pt2d) != TopAbs_OUT);
    if(stat == TopAbs_OUT) return Standard_False;

    if(stat == TopAbs_ON) {
      Standard_Integer nbPnt =10;
      Standard_Integer nbOut =0,nbIn =0,nbOn=0;
      Standard_Integer j =1;
      for( ; j<= nbPnt ; j++)
      {
        //check neighbouring point
        //prm = .66 * prm + .34 * l;
        prm = f + (l-f)/nbPnt*(j-1);
        pt2d = C2d->Value(prm);
        stat = classif.Perform(pt2d);
        if(stat == TopAbs_OUT ) 
          nbOut++;
        else if(stat == TopAbs_IN)
          nbIn++;
        else
          nbOn++;
      }
      if(nbOut > nbIn + nbOn)
        return Standard_False;
    }
  }
  return Standard_True;
}

//=======================================================================
//function : GetDirection
//purpose  : 
//=======================================================================
static void GetDirection(const TopoDS_Edge& theEdge,
                         const TopoDS_Face& theFace,
                         Standard_Real& theTol,
                         gp_Pnt2d& thePnt,
                         gp_Vec2d& theDir)
{
  Standard_Real aFirst, aLast;
  Handle(Geom2d_Curve) aC2d = BRep_Tool::CurveOnSurface (theEdge, theFace, aFirst, aLast);

  TopAbs_Orientation anOr = theEdge.Orientation();
  TopoDS_Vertex aVtx;
  if (anOr == TopAbs_FORWARD)
  {
    aVtx = TopExp::FirstVertex (theEdge);
    aC2d->D0 (aFirst, thePnt);
  }
  else
  {
    aVtx = TopExp::LastVertex (theEdge);
    aC2d->D0 (aLast, thePnt);
  }

  BRepAdaptor_Surface aSurf (theFace, Standard_False);
  theTol = BRep_Tool::Tolerance (aVtx);
  Standard_Real aTol = Max (aSurf.UResolution (theTol), aSurf.VResolution (theTol));
  aTol = Min (aTol, (aLast - aFirst)*0.1);

  gp_Pnt2d aP2d;

  if (anOr == TopAbs_FORWARD)
  {
      aFirst += aTol;
      aC2d->D0 (aFirst, aP2d);
  }
  else
  {
      aLast -= aTol;
      aC2d->D0 (aLast, aP2d);
  }
  theDir = gp_Vec2d (thePnt, aP2d);
}

//=======================================================================
//function : ChoixUV
//purpose  : 
//=======================================================================

static void ChoixUV(const TopoDS_Edge& Last,
                    const TopoDS_Face& F,
                    const TopTools_IndexedMapOfShape& Poss,
                    TopoDS_Edge& theResEdge,
                    gp_Pnt2d& plst,
                    gp_Vec2d& dlst,
                    const Standard_Real toll)
{

  Standard_Real f,l;
  gp_Pnt2d p2d;
  gp_Vec2d v2d;
  gp_Pnt aPCur, aPlst;

  BRepAdaptor_Surface surf(F,Standard_False); // no restriction
  surf.D0 (plst.X(), plst.Y(), aPlst);

  Standard_Real tol;

  gp_Dir2d ref2d(dlst);

  Handle(Geom2d_Curve) C2d;
  Standard_Real dpar;

  Standard_Integer index = 0, imin=0;
  Standard_Real  angmax = -M_PI, dist, ang;


  for (index = 1; index <= Poss.Extent(); index++) {
    TopoDS_Edge anEdge = TopoDS::Edge (Poss.FindKey (index));
    GetDirection (anEdge, F, tol, p2d, v2d);

    surf.D0 (p2d.X(), p2d.Y(), aPCur);

    tol = Max(toll, tol); tol *= tol;

    dist = aPCur.SquareDistance(aPlst);

    if (!Last.IsSame(anEdge)) {
      ang = ref2d.Angle(gp_Dir2d(v2d));
    }
    else {
      ang = -M_PI;
    }

    if ((dist - tol < Epsilon(1.0))  && (ang > angmax)) {
      imin = index;
      angmax = ang;
    }
  }

  if (imin)
  {
    theResEdge = TopoDS::Edge (Poss.FindKey (imin));
    C2d = BRep_Tool::CurveOnSurface (theResEdge, F, f, l);
    dpar = (l - f)*0.01;
    if (theResEdge.Orientation() == TopAbs_FORWARD)
    {
      C2d->D1 (l, plst, dlst);
      if (dlst.Magnitude() < gp::Resolution())
      {
        gp_Pnt2d PrevPnt = C2d->Value(l - dpar);
        dlst.SetXY(plst.XY() - PrevPnt.XY());
      }
    }
    else
    {
      C2d->D1 (f, plst, dlst);
      if (dlst.Magnitude() < gp::Resolution())
      {
        gp_Pnt2d NextPnt = C2d->Value(f + dpar);
        dlst.SetXY(NextPnt.XY() - plst.XY());
      }
      dlst.Reverse();
    }
  }

}

//=======================================================================
//function : ChooseDirection
//purpose  : 
//=======================================================================

static TopoDS_Shape ChooseDirection(const TopoDS_Shape& RefDir,
                                    const TopoDS_Vertex& RefVertex,
                                    const TopoDS_Face& theFace,
                                    const TopTools_ListOfShape& Ldirs)
{
  TopExp_Explorer Explo(RefDir, TopAbs_EDGE);
  TopoDS_Edge RefEdge;
  TopoDS_Vertex V1, V2;
  TopAbs_Orientation anOr = TopAbs_FORWARD;
  for (; Explo.More(); Explo.Next())
  {
    RefEdge = TopoDS::Edge(Explo.Current());
    TopExp::Vertices(RefEdge, V1, V2);
    if (V1.IsSame(RefVertex))
    {
      anOr = TopAbs_REVERSED;
      break;
    }
    else if (V2.IsSame(RefVertex))
    {
      anOr = TopAbs_FORWARD;
      break;
    }
  }
  
  Standard_Real RefFirst, RefLast;
  Handle(Geom2d_Curve) RefCurve = BRep_Tool::CurveOnSurface(RefEdge, theFace, RefFirst, RefLast);
  gp_Pnt2d RefPnt;
  gp_Vec2d RefVec;

  //Standard_Real RefPar = (RefEdge.Orientation() == TopAbs_FORWARD)? RefLast : RefFirst;
  Standard_Real RefPar = (anOr == TopAbs_FORWARD)? RefLast : RefFirst;
  RefCurve->D1(RefPar, RefPnt, RefVec);
  if (anOr == TopAbs_FORWARD)
    RefVec.Reverse();

  Handle(Geom2d_Curve) aCurve;
  Standard_Real aFirst, aLast, aPar;
  gp_Vec2d aVec;
  Standard_Real MinAngle = RealLast(), anAngle;
  TopoDS_Shape TargetDir;
  TopTools_ListIteratorOfListOfShape itl(Ldirs);
  for (; itl.More(); itl.Next())
  {
    const TopoDS_Shape& aShape = itl.Value();
    TopoDS_Edge anEdge;
    for (Explo.Init(aShape, TopAbs_EDGE); Explo.More(); Explo.Next())
    {
      anEdge = TopoDS::Edge(Explo.Current());
      TopExp::Vertices(anEdge, V1, V2);
      if (V1.IsSame(RefVertex))
      {
        anOr = TopAbs_FORWARD;
        break;
      }
      else if (V2.IsSame(RefVertex))
      {
        anOr = TopAbs_REVERSED;
        break;
      }
    }
    aCurve = BRep_Tool::CurveOnSurface(anEdge, theFace, aFirst, aLast);
    aPar = (anOr == TopAbs_FORWARD)? aFirst : aLast;
    aCurve->D1(aPar, RefPnt, aVec);
    if (anOr == TopAbs_REVERSED)
      aVec.Reverse();
    anAngle = aVec.Angle(RefVec);
    if (anAngle < 0.)
      anAngle += 2.*M_PI;

    if (anAngle < MinAngle)
    {
      MinAngle = anAngle;
      TargetDir = aShape;
    }
  }

  return TargetDir;
}
