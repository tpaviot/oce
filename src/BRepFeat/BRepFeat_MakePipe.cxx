// File:	BRepFeat_MakePipe.cxx
// Created:	Tue Sep  3 11:18:26 1996
// Author:	Jacques GOUSSARD
//		<jag@mobilox.lyon.matra-dtv.fr>


#include <BRepFeat_MakePipe.ixx>

#include <BRepFeat.hxx>
#include <LocOpe.hxx>

//modified by NIZNHY-PKV Thu Mar 21 17:54:27 2002 f
//#include <BRepAlgo_Fuse.hxx>
//#include <BRepAlgo_Cut.hxx> 
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Cut.hxx> 
//modified by NIZNHY-PKV Thu Mar 21 17:54:30 2002 t

#include <gp_Vec.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <TColgp_SequenceOfPnt.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Line.hxx>

#include <LocOpe_Pipe.hxx>

#include <BRep_Tool.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_MapOfShape.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TopTools_MapIteratorOfMapOfShape.hxx>
#include <TopTools_DataMapIteratorOfDataMapOfShapeListOfShape.hxx>

#include <Bnd_Box.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS.hxx>

#include <Standard_ConstructionError.hxx>

#include <TopExp.hxx>
#include <BRepBndLib.hxx>

#ifdef DEB
Standard_IMPORT Standard_Boolean BRepFeat_GettraceFEAT();
#endif

static void MajMap(const TopoDS_Shape&, // base
		   LocOpe_Pipe&,
		   TopTools_DataMapOfShapeListOfShape&, // myMap
		   TopoDS_Shape&,  // myFShape
		   TopoDS_Shape&); // myLShape




//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void BRepFeat_MakePipe::Init(const TopoDS_Shape& Sbase,
			     const TopoDS_Shape& Pbase,
			     const TopoDS_Face& Skface,
			     const TopoDS_Wire& Spine,
			     const Standard_Integer Mode,
			     const Standard_Boolean Modify)
{
#ifdef DEB
  Standard_Boolean trc = BRepFeat_GettraceFEAT();
  if (trc) cout << "BRepFeat_MakePipe::Init" << endl;
#endif
  mySbase  = Sbase;
  BasisShapeValid();
  mySkface = Skface;
  SketchFaceValid();
  myPbase  = Pbase;
  mySlface.Clear();
  mySpine   = Spine;
  if(Mode == 0) {
    myFuse   = Standard_False;
    myJustFeat = Standard_False;
  }
  else if(Mode == 1) {
    myFuse   = Standard_True;
    myJustFeat = Standard_False;
  }
  else if(Mode == 2) {
    myFuse   = Standard_True;
    myJustFeat = Standard_True;
  }
  else {    
  }
  myModify = Modify;
  myJustGluer = Standard_False;


  //-------------- ifv
  //mySkface.Nullify();
  //-------------- ifv

  myShape.Nullify();
  myMap.Clear();
  myFShape.Nullify();
  myLShape.Nullify();
  TopExp_Explorer exp;
  for (exp.Init(mySbase,TopAbs_FACE);exp.More();exp.Next()) {
    TopTools_ListOfShape thelist;
    myMap.Bind(exp.Current(), thelist);
    myMap(exp.Current()).Append(exp.Current());
  }
#ifdef DEB
  if (trc) {
    if (myJustFeat)  cout << " Just Feature" << endl;
    if (myFuse)  cout << " Fuse" << endl;
    if (!myFuse)  cout << " Cut" << endl;
    if (!myModify) cout << " Modify = 0" << endl;
  }
#endif 
}


//=======================================================================
//function : Add
//purpose  : add faces de collage
//=======================================================================

void BRepFeat_MakePipe::Add(const TopoDS_Edge& E,
			     const TopoDS_Face& F)
{
#ifdef DEB
  Standard_Boolean trc = BRepFeat_GettraceFEAT();
  if (trc) cout << "BRepFeat_MakePipe::Add(Edge,face)" << endl;
#endif
  TopExp_Explorer exp;
  for (exp.Init(mySbase,TopAbs_FACE);exp.More();exp.Next()) {
    if (exp.Current().IsSame(F)) {
      break;
    }
  }
  if (!exp.More()) {
    Standard_ConstructionError::Raise();
  }

  for (exp.Init(myPbase,TopAbs_EDGE);exp.More();exp.Next()) {
    if (exp.Current().IsSame(E)) {
      break;
    }
  }
  if (!exp.More()) {
    Standard_ConstructionError::Raise();
  }

  if (!mySlface.IsBound(F)) {
    TopTools_ListOfShape thelist1;
    mySlface.Bind(F,thelist1);
  }
  TopTools_ListIteratorOfListOfShape itl(mySlface(F));
  for (; itl.More();itl.Next()) {
    if (itl.Value().IsSame(E)) {
      break;
    }
  }
  if (!itl.More()) {
    mySlface(F).Append(E);
  }
}


//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================

void BRepFeat_MakePipe::Perform()
{
#ifdef DEB
  Standard_Boolean trc = BRepFeat_GettraceFEAT();
  if (trc) cout << "BRepFeat_MakePipe::Perform()" << endl;
#endif
  mySFrom.Nullify();
  ShapeFromValid();
  mySUntil.Nullify();
  ShapeUntilValid();
  myGluedF.Clear();
  myPerfSelection = BRepFeat_NoSelection;
  PerfSelectionValid();
  TopoDS_Shape theBase = myPbase;
  LocOpe_Pipe thePipe(mySpine,theBase);
  TopoDS_Shape VraiPipe = thePipe.Shape();
  MajMap(myPbase,thePipe,myMap,myFShape,myLShape);
  myGShape = VraiPipe;
  GeneratedShapeValid();

  //SetGluedFaces(mySkface, mySbase, myPbase, mySlface, thePipe, myGluedF);
  GluedFacesValid();

  if(myGluedF.IsEmpty()) {
    if(myFuse == 1) {
      //modified by NIZNHY-PKV Thu Mar 21 17:53:05 2002 f
      //BRepAlgo_Fuse f(mySbase, myGShape);
      //myShape = f.Shape();
      //UpdateDescendants(f.Builder(), myShape, Standard_False);
      BRepAlgoAPI_Fuse f(mySbase, myGShape);
      myShape = f.Shape();
      UpdateDescendants(f, myShape, Standard_False);
      //modified by NIZNHY-PKV Thu Mar 21 17:53:10 2002 t
      Done();
    }
    else if(myFuse == 0) {
      //modified by NIZNHY-PKV Thu Mar 21 17:53:37 2002 f
      //BRepAlgo_Cut c(mySbase, myGShape);
      //myShape = c.Shape();
      //UpdateDescendants(c.Builder(), myShape, Standard_False);
      BRepAlgoAPI_Cut c(mySbase, myGShape);
      myShape = c.Shape();
      UpdateDescendants(c, myShape, Standard_False);
      //modified by NIZNHY-PKV Thu Mar 21 17:53:50 2002 t
      Done();
    }
    else {
      myShape = myGShape;
      Done();
    }
  }
  else {
    myFShape = thePipe.FirstShape();
    TColgp_SequenceOfPnt spt;
    LocOpe::SampleEdges(myFShape,spt); 
    myCurves = thePipe.Curves(spt);
    myBCurve = thePipe.BarycCurve();
    GlobalPerform();
  }
}


//=======================================================================
//function : Perform
//purpose  : jusqu'au shape Until
//=======================================================================

void BRepFeat_MakePipe::Perform(const TopoDS_Shape& Until)
{
#ifdef DEB
  Standard_Boolean trc = BRepFeat_GettraceFEAT();
  if (trc) cout << "BRepFeat_MakePipe::Perform(Until)" << endl;
#endif
  if (Until.IsNull()) {
    Standard_ConstructionError::Raise();
  }
  TopExp_Explorer exp(Until, TopAbs_FACE);
  if (!exp.More()) {
    Standard_ConstructionError::Raise();
  }
  myGluedF.Clear();
  myPerfSelection = BRepFeat_SelectionU;
  PerfSelectionValid();
  mySFrom.Nullify();
  ShapeFromValid();
  mySUntil = Until;
  TransformShapeFU(1);
  ShapeUntilValid();
  LocOpe_Pipe thePipe(mySpine,myPbase);
  TopoDS_Shape VraiTuyau = thePipe.Shape();
  MajMap(myPbase,thePipe,myMap,myFShape,myLShape);
  myGShape = VraiTuyau;
  GeneratedShapeValid();

  //SetGluedFaces(mySkface, mySbase, myPbase, mySlface, thePipe, myGluedF);
  GluedFacesValid();

  myFShape = thePipe.FirstShape();
  TColgp_SequenceOfPnt spt;
  LocOpe::SampleEdges(myFShape,spt); 
  myCurves = thePipe.Curves(spt);
  myBCurve = thePipe.BarycCurve();
  GlobalPerform();
}


//=======================================================================
//function : Perform
//purpose  : entre From et Until
//=======================================================================

void BRepFeat_MakePipe::Perform(const TopoDS_Shape& From,
				const TopoDS_Shape& Until)
{
#ifdef DEB
  Standard_Boolean trc = BRepFeat_GettraceFEAT();
  if (trc) cout << "BRepFeat_MakePipe::Perform(From,Until)" << endl;
#endif
  if (From.IsNull() || Until.IsNull()) {
    Standard_ConstructionError::Raise();
  }
  if (!mySkface.IsNull()) {
    if (From.IsSame(mySkface)) {
      Perform(Until);
      return;
    }
    else if (Until.IsSame(mySkface)) {
      Perform(From);
      return;
    }
  }
  myGluedF.Clear();
  myPerfSelection = BRepFeat_SelectionFU;
  PerfSelectionValid();
  TopExp_Explorer exp(From, TopAbs_FACE);
  if (!exp.More()) {
    Standard_ConstructionError::Raise();
  }
  exp.Init(Until, TopAbs_FACE);
  if (!exp.More()) {
    Standard_ConstructionError::Raise();
  }
  mySFrom = From;
  TransformShapeFU(0);
  ShapeFromValid();
  mySUntil = Until;
  TransformShapeFU(1);
  ShapeUntilValid();  
  LocOpe_Pipe thePipe(mySpine,myPbase);
  TopoDS_Shape VraiTuyau = thePipe.Shape();
  MajMap(myPbase,thePipe,myMap,myFShape,myLShape);
  myGShape = VraiTuyau;
  GeneratedShapeValid();

  //SetGluedFaces(TopoDS_Face(), // on ne veut pas binder mySkface
	//	mySbase, myPbase, mySlface, thePipe, myGluedF);
  GluedFacesValid();

  myFShape = thePipe.FirstShape();
  TColgp_SequenceOfPnt spt;
  LocOpe::SampleEdges(myFShape,spt); 
  myCurves = thePipe.Curves(spt);
  myBCurve = thePipe.BarycCurve();
  GlobalPerform();
}


//=======================================================================
//function : Curves
//purpose  : courbes paralleles au wire-generarice du pipe
//=======================================================================

void BRepFeat_MakePipe::Curves(TColGeom_SequenceOfCurve& scur)
{
  scur = myCurves;
}

//=======================================================================
//function : BarycCurve
//purpose  : passe par le centre des masses
//=======================================================================

Handle(Geom_Curve) BRepFeat_MakePipe::BarycCurve()
{
  return myBCurve;
}




//=======================================================================
//function : MajMap
//purpose  : gestion de descendants
//=======================================================================

static void MajMap(const TopoDS_Shape& theB,
		   LocOpe_Pipe& theP,
		   TopTools_DataMapOfShapeListOfShape& theMap, // myMap
		   TopoDS_Shape& theFShape,  // myFShape
		   TopoDS_Shape& theLShape) // myLShape
{
  TopExp_Explorer exp(theP.FirstShape(),TopAbs_WIRE);
  if (exp.More()) {
    theFShape = exp.Current();
    TopTools_ListOfShape thelist2;
    theMap.Bind(theFShape, thelist2);
    for (exp.Init(theP.FirstShape(),TopAbs_FACE);exp.More();exp.Next()) {
      theMap(theFShape).Append(exp.Current());
    }
  }
  
  exp.Init(theP.LastShape(),TopAbs_WIRE);
  if (exp.More()) {
    theLShape = exp.Current();
    TopTools_ListOfShape thelist3;
    theMap.Bind(theLShape, thelist3);
    for (exp.Init(theP.LastShape(),TopAbs_FACE);exp.More();exp.Next()) {
      theMap(theLShape).Append(exp.Current());
    }
  }

  for (exp.Init(theB,TopAbs_EDGE); exp.More(); exp.Next()) {
    if (!theMap.IsBound(exp.Current())) {
      TopTools_ListOfShape thelist4;
      theMap.Bind(exp.Current(), thelist4);
      theMap(exp.Current()) = theP.Shapes(exp.Current());
    }
  }
}














