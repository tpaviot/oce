// Created on: 1995-05-30
// Created by: Jacques GOUSSARD
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



#include <BRepFeat_MakeCylindricalHole.ixx>


#include <LocOpe_CurveShapeIntersector.hxx>
#include <LocOpe_PntFace.hxx>

#include <Bnd_Box.hxx>
#include <BRep_Builder.hxx>
#include <BRep_Tool.hxx>
#include <BRepPrim_Cylinder.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TopoDS_Solid.hxx>
#include <TopExp_Explorer.hxx>
#include <TopLoc_Location.hxx>

#include <Geom_Curve.hxx>

#include <ElCLib.hxx>
#include <BRepTools.hxx>
#include <TopoDS.hxx>
#include <Precision.hxx>
#include <BRepBndLib.hxx>



static void Baryc(const TopoDS_Shape&,
                  gp_Pnt&);

static void BoxParameters(const TopoDS_Shape&,
                          const gp_Ax1&,
                          Standard_Real&,
                          Standard_Real&);


//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================

void BRepFeat_MakeCylindricalHole::Perform(const Standard_Real Radius)
{
  if (Object().IsNull() || !myAxDef) {
    Standard_ConstructionError::Raise();
  }

  myIsBlind = Standard_False;
  myStatus = BRepFeat_NoError;

  LocOpe_CurveShapeIntersector theASI(myAxis,Object());
  if (!theASI.IsDone() || theASI.NbPoints() <= 0) {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }
  
  //TopTools_ListOfShape theList;
  //for (Standard_Integer i=1; i<= theASI.NbPoints(); i++) {
  //  theList.Append(theASI.Point(i).Face());
  //}

  // It is not possible to use infinite cylinder for topological operations.
  Standard_Real PMin,PMax;
  BoxParameters(Object(),myAxis,PMin,PMax);
  Standard_Real Heigth = 2.*(PMax-PMin);
  gp_XYZ theOrig = myAxis.Location().XYZ();
  theOrig += ((3.*PMin-PMax)/2.) * myAxis.Direction().XYZ();
  gp_Pnt p1_ao1(theOrig); gp_Ax2 a1_ao1(p1_ao1,myAxis.Direction());
  BRepPrim_Cylinder theCylinder(a1_ao1,
                                Radius,
                                Heigth);

  // Probably it is better to make cut directly

  BRep_Builder B;
  TopoDS_Solid theTool;
  B.MakeSolid(theTool);
  B.Add(theTool,theCylinder.Shell());
  theTool.Closed(Standard_True);

  myTopFace = theCylinder.TopFace();
  myBotFace = theCylinder.BottomFace();
  myValidate = Standard_False;

//  BRepTools::Dump(theTool,cout);
  Standard_Boolean Fuse = Standard_False;
  //
  AddTool(theTool);
  SetOperation(Fuse);
  BOPAlgo_Builder::Perform();
  //myBuilder.Perform(theTool,theList,Fuse);
//  myBuilder.PerformResult();
}


//=======================================================================
//function : PerformThruNext
//purpose  : 
//=======================================================================

void BRepFeat_MakeCylindricalHole::PerformThruNext(const Standard_Real Radius,
                                                   const Standard_Boolean Cont)
{

  if (Object().IsNull() || !myAxDef) {
    Standard_ConstructionError::Raise();
  }

  myIsBlind = Standard_False;
  myValidate = Cont;
  myStatus = BRepFeat_NoError;

  LocOpe_CurveShapeIntersector theASI(myAxis,Object());
  if (!theASI.IsDone()) {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }
  
  Standard_Real First=0.,Last=0.;
  Standard_Integer IndFrom,IndTo;
  TopAbs_Orientation theOr;
  Standard_Boolean ok = theASI.LocalizeAfter(0.,theOr,IndFrom,IndTo);
  if (ok) {
    if (theOr == TopAbs_FORWARD) {
      First = theASI.Point(IndFrom).Parameter();
      ok = theASI.LocalizeAfter(IndTo,theOr,IndFrom,IndTo);
      if (ok) {
        if (theOr != TopAbs_REVERSED) {
          ok = Standard_False;
        }
        else {
          Last = theASI.Point(IndTo).Parameter();
        }
      }
      
    }
    else { // TopAbs_REVERSED
      Last = theASI.Point(IndTo).Parameter();
      ok = theASI.LocalizeBefore(IndFrom,theOr,IndFrom,IndTo);
      if (ok) {
        if (theOr != TopAbs_FORWARD) {
          ok = Standard_False;
        }
        else {
          First = theASI.Point(IndFrom).Parameter();
        }
      }
    }
  }
  if (!ok) {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  /*TopTools_ListOfShape theList;
  for (Standard_Integer i=1; i<= theASI.NbPoints(); i++) {
    prm = theASI.Point(i).Parameter();
    if (prm >= First && prm <= Last) {
      theList.Append(theASI.Point(i).Face());
    }
    else if (prm > Last) {
      break;
    }
  }*/

  // It is not possible to use infinite cylinder for topological operations.
  Standard_Real PMin,PMax;
  BoxParameters(Object(),myAxis,PMin,PMax);
  Standard_Real Heigth = 2.*(PMax-PMin);
  gp_XYZ theOrig = myAxis.Location().XYZ();
  theOrig += ((3.*PMin-PMax)/2.) * myAxis.Direction().XYZ();
  gp_Pnt p2_ao1(theOrig); gp_Ax2 a2_ao1(p2_ao1,myAxis.Direction());
  BRepPrim_Cylinder theCylinder(a2_ao1,
                                Radius,
                                Heigth);

  BRep_Builder B;
  TopoDS_Solid theTool;
  B.MakeSolid(theTool);
  B.Add(theTool,theCylinder.Shell());
  theTool.Closed(Standard_True);

  myTopFace = theCylinder.TopFace();
  myBotFace = theCylinder.BottomFace();

  //  BRepTools::Dump(theTool,cout);
  Standard_Boolean Fuse = Standard_False;
  //myBuilder.Perform(theTool,theList,Fuse);
  //myBuilder.BuildPartsOfTool();
  AddTool(theTool);
  SetOperation(Fuse);
  BOPAlgo_Builder::Perform();
  TopTools_ListOfShape parts;
  PartsOfTool(parts);


  Standard_Integer nbparts = 0;
  TopTools_ListIteratorOfListOfShape its(parts);
  for (; its.More(); its.Next()) {
    nbparts ++;
  }
  if (nbparts == 0) {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  if (nbparts >= 2) { // preserve the smallest as parameter 
                      // along the axis
    TopoDS_Shape tokeep;
    Standard_Real parbar,parmin = Last;
    gp_Pnt Barycentre;
    for (its.Initialize(parts); its.More(); its.Next()) {
      Baryc(its.Value(),Barycentre);
      parbar = ElCLib::LineParameter(myAxis,Barycentre);
      if (parbar >= First && parbar <= Last && parbar <= parmin) {
        parmin = parbar;
        tokeep = its.Value();
      }
    }

    if (tokeep.IsNull()) { // preserve the closest interval

      Standard_Real dmin = RealLast();
      for (its.Initialize(parts); its.More(); its.Next()) {
        Baryc(its.Value(),Barycentre);
        parbar = ElCLib::LineParameter(myAxis,Barycentre);
        if (parbar < First) {
          if (First - parbar < dmin ) {
            dmin = First-parbar;
            tokeep = its.Value();
          }
          else { // parbar > Last
            if (parbar - Last < dmin) {
              dmin = parbar-Last;
              tokeep = its.Value();
            }
          }
        }
      }
    }
    for (its.Initialize(parts); its.More(); its.Next()) {
      //if (!tokeep.IsSame(its.Value())) {
      //  myBuilder.RemovePart(its.Value());
      //}
      if (tokeep.IsSame(its.Value())) {
        KeepPart(its.Value());
        break;
      }
    }
  }
//  myBuilder.PerformResult();
}

//=======================================================================
//function : PerformUntilEnd
//purpose  : 
//=======================================================================

void BRepFeat_MakeCylindricalHole::PerformUntilEnd(const Standard_Real Radius,
                                                   const Standard_Boolean Cont)
{

  if (Object().IsNull() || !myAxDef) {
    Standard_ConstructionError::Raise();
  }

  myIsBlind = Standard_False;
  myValidate = Cont;
  myStatus = BRepFeat_NoError;

  LocOpe_CurveShapeIntersector theASI(myAxis,Object());
  if (!theASI.IsDone()) {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }
  
  Standard_Real First=0,Last=0,prm;
  Standard_Integer IndFrom,IndTo;
  TopAbs_Orientation theOr;
  Standard_Boolean ok = theASI.LocalizeAfter(0.,theOr,IndFrom,IndTo);
  
  if (ok) {
    if (theOr == TopAbs_REVERSED) {
      ok = theASI.LocalizeBefore(IndFrom,theOr,IndFrom,IndTo); // on reset
      // It is possible to search for the next.
    }
    if ( ok && theOr == TopAbs_FORWARD) {
      First = theASI.Point(IndFrom).Parameter();
      ok = theASI.LocalizeBefore(theASI.NbPoints()+1,theOr,IndFrom,IndTo);
      if (ok) {
        if (theOr != TopAbs_REVERSED) {
          ok = Standard_False;
        }
        else {
          Last = theASI.Point(IndTo).Parameter();
        }
      }
    }
  }
  if (!ok) {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  TopTools_ListOfShape theList;
  for (Standard_Integer i=1; i<= theASI.NbPoints(); i++) {
    prm = theASI.Point(i).Parameter();
    if (prm >= First && prm <= Last) {
      theList.Append(theASI.Point(i).Face());
    }
    else if (prm > Last) {
      break;
    }
  }

  // It is not possible to use infinite cylinder for topological operations.
  Standard_Real PMin,PMax;
  BoxParameters(Object(),myAxis,PMin,PMax);
  Standard_Real Heigth = 2.*(PMax-PMin);
  gp_XYZ theOrig = myAxis.Location().XYZ();
  theOrig += ((3.*PMin-PMax)/2.) * myAxis.Direction().XYZ();
  gp_Pnt p3_ao1(theOrig); gp_Ax2 a3_ao1(p3_ao1,myAxis.Direction());
  BRepPrim_Cylinder theCylinder(a3_ao1,
                                Radius,
                                Heigth);

  BRep_Builder B;
  TopoDS_Solid theTool;
  B.MakeSolid(theTool);
  B.Add(theTool,theCylinder.Shell());
  theTool.Closed(Standard_True);

  myTopFace = theCylinder.TopFace();
  myBotFace = theCylinder.BottomFace();

  //  BRepTools::Dump(theTool,cout);
  Standard_Boolean Fuse = Standard_False;
  //myBuilder.Perform(theTool,theList,Fuse);
  //myBuilder.BuildPartsOfTool();
  AddTool(theTool);
  SetOperation(Fuse);
  BOPAlgo_Builder::Perform();
  TopTools_ListOfShape parts;
  PartsOfTool(parts);

  Standard_Integer nbparts = 0;
  TopTools_ListIteratorOfListOfShape its(parts);
  for (; its.More(); its.Next()) {
    nbparts ++;
  }
  if (nbparts == 0) {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  if (nbparts >= 2) { // preserve everything above the First 
    Standard_Real parbar;
    gp_Pnt Barycentre;
    for (its.Initialize(parts); its.More(); its.Next()) {
      Baryc(its.Value(),Barycentre);
      parbar = ElCLib::LineParameter(myAxis,Barycentre);
      if (parbar > First) {
        KeepPart(its.Value());
      }
    }
  }
}


//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================

void BRepFeat_MakeCylindricalHole::Perform(const Standard_Real Radius,
                                           const Standard_Real PFrom,
                                           const Standard_Real PTo,
                                           const Standard_Boolean Cont)
{

  if (Object().IsNull() || !myAxDef) {
    Standard_ConstructionError::Raise();
  }

  myIsBlind = Standard_False;
  myValidate = Cont;
  myStatus = BRepFeat_NoError;

  LocOpe_CurveShapeIntersector theASI(myAxis,Object());
  if (!theASI.IsDone()) {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  Standard_Real thePFrom,thePTo;
  if (PFrom < PTo) {
    thePFrom = PFrom;
    thePTo   = PTo;
  }
  else {
    thePFrom = PTo;
    thePTo   = PFrom;
  }

  Standard_Real First=0,Last=0,prm;
  Standard_Integer IndFrom,IndTo;
  TopAbs_Orientation theOr;
  Standard_Boolean ok = theASI.LocalizeAfter(thePFrom,theOr,IndFrom,IndTo);
  if (ok) {
    if (theOr == TopAbs_REVERSED) {
      ok = theASI.LocalizeBefore(IndFrom,theOr,IndFrom,IndTo); // reset
      // It is possible to find the next.
    }
    if ( ok && theOr == TopAbs_FORWARD) {
      First = theASI.Point(IndFrom).Parameter();
      ok = theASI.LocalizeBefore(thePTo,theOr,IndFrom,IndTo);
      if (ok) {
        if (theOr == TopAbs_FORWARD) {
          ok = theASI.LocalizeAfter(IndTo,theOr,IndFrom,IndTo);
        }
        if (ok && theOr == TopAbs_REVERSED) {
          Last = theASI.Point(IndTo).Parameter();
        }
      }
    }
  }

  if (!ok) {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  TopTools_ListOfShape theList;
  for (Standard_Integer i=1; i<= theASI.NbPoints(); i++) {
    prm = theASI.Point(i).Parameter();
    if (prm >= First && prm <= Last) {
      theList.Append(theASI.Point(i).Face());
    }
    else if (prm > Last) {
      break;
    }
  }

  // // It is not possible to use infinite cylinder for topological operations.
  Standard_Real PMin,PMax;
  BoxParameters(Object(),myAxis,PMin,PMax);
  Standard_Real Heigth = 2.*(PMax-PMin);
  gp_XYZ theOrig = myAxis.Location().XYZ();
  theOrig += ((3.*PMin-PMax)/2.) * myAxis.Direction().XYZ();

  gp_Pnt p4_ao1(theOrig); gp_Ax2 a4_ao1(p4_ao1,myAxis.Direction());
  BRepPrim_Cylinder theCylinder(a4_ao1,
                                Radius,
                                Heigth);

  BRep_Builder B;
  TopoDS_Solid theTool;
  B.MakeSolid(theTool);
  B.Add(theTool,theCylinder.Shell());
  theTool.Closed(Standard_True);

  myTopFace = theCylinder.TopFace();
  myBotFace = theCylinder.BottomFace();

  //  BRepTools::Dump(theTool,cout);
  Standard_Boolean Fuse = Standard_False;
  //myBuilder.Perform(theTool,theList,Fuse);
  //myBuilder.BuildPartsOfTool();
  AddTool(theTool);
  SetOperation(Fuse);
  BOPAlgo_Builder::Perform();
  TopTools_ListOfShape parts;
  PartsOfTool(parts);

  Standard_Integer nbparts = 0;
  TopTools_ListIteratorOfListOfShape its(parts);
  for (; its.More(); its.Next()) {
    nbparts ++;
  }
  if (nbparts == 0) {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  if (nbparts >= 2) { // preserve parts between First and Last

    TopoDS_Shape tokeep;
    Standard_Real parbar;
    gp_Pnt Barycentre;
    for (its.Initialize(parts); its.More(); its.Next()) {
      Baryc(its.Value(),Barycentre);
      parbar = ElCLib::LineParameter(myAxis,Barycentre);
      if (!(parbar < First || parbar > Last)) {
        KeepPart(its.Value());
      }
    }
  }
}


//=======================================================================
//function : PerformBlind
//purpose  : 
//=======================================================================

void BRepFeat_MakeCylindricalHole::PerformBlind(const Standard_Real Radius,
                                                const Standard_Real Length,
                                                const Standard_Boolean Cont)
{

  if (Object().IsNull() || !myAxDef || Length <= 0.) {
    Standard_ConstructionError::Raise();
  }

  myIsBlind = Standard_True;
  myValidate = Cont;
  myStatus = BRepFeat_NoError;

  LocOpe_CurveShapeIntersector theASI(myAxis,Object());
  if (!theASI.IsDone()) {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }
  
//  Standard_Real First,prm;
  Standard_Real First;
  Standard_Integer IndFrom,IndTo;
  TopAbs_Orientation theOr;
  Standard_Boolean ok = theASI.LocalizeAfter(0.,theOr,IndFrom,IndTo);
  
  if (ok) {
    if (theOr == TopAbs_REVERSED) {
      ok = theASI.LocalizeBefore(IndFrom,theOr,IndFrom,IndTo); // reset
      // it is possible to find the next
    }
    ok = ok && theOr == TopAbs_FORWARD;
  }
  if (!ok) {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  // check a priori the length of the hole
  Standard_Integer IFNext,ITNext;
  ok = theASI.LocalizeAfter(IndTo,theOr,IFNext,ITNext);
  if (!ok) {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }
  if (theASI.Point(IFNext).Parameter() <= Length) {
    myStatus = BRepFeat_HoleTooLong;
    return;
  }

  TopTools_ListOfShape theList;
/*
  for (Standard_Integer i=IndFrom; i<= IndTo; i++) {
    theList.Append(theASI.Point(i).Face());
  }
*/
  // version for advanced control
  for (Standard_Integer i=IndFrom; i<= ITNext; i++) {
    theList.Append(theASI.Point(i).Face());
  }

  First = theASI.Point(IndFrom).Parameter();

  //// It is not possible to use infinite cylinder for topological operations.
  Standard_Real PMin,PMax;
  BoxParameters(Object(),myAxis,PMin,PMax);
  if (PMin > Length) {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  Standard_Real Heigth = 3.*(Length-PMin)/2.;
  gp_XYZ theOrig = myAxis.Location().XYZ();
  theOrig += ((3.*PMin-Length)/2.) * myAxis.Direction().XYZ();
  gp_Pnt p5_ao1(theOrig); gp_Ax2 a5_ao1(p5_ao1,myAxis.Direction());
  BRepPrim_Cylinder theCylinder(a5_ao1,
                                Radius,
                                Heigth);

  BRep_Builder B;
  TopoDS_Solid theTool;
  B.MakeSolid(theTool);
  B.Add(theTool,theCylinder.Shell());
  theTool.Closed(Standard_True);

  myTopFace = theCylinder.TopFace();
  myBotFace.Nullify();

  //  BRepTools::Dump(theTool,cout);
  Standard_Boolean Fuse = Standard_False;
  //myBuilder.Perform(theTool,theList,Fuse);
  //myBuilder.BuildPartsOfTool();
  AddTool(theTool);
  SetOperation(Fuse);
  BOPAlgo_Builder::Perform();
  TopTools_ListOfShape parts;
  PartsOfTool(parts);

  Standard_Integer nbparts = 0;
  TopTools_ListIteratorOfListOfShape its(parts);
  for (; its.More(); its.Next()) {
    nbparts ++;
  }
  if (nbparts == 0) {
    myStatus = BRepFeat_InvalidPlacement;
    return;
  }

  if (nbparts >= 2) { // preserve the smallest as parameter along the axis
    TopoDS_Shape tokeep;
    Standard_Real parbar,parmin = RealLast();
    gp_Pnt Barycentre;
    for (its.Initialize(parts); its.More(); its.Next()) {
      Baryc(its.Value(),Barycentre);
      parbar = ElCLib::LineParameter(myAxis,Barycentre);
      if (parbar >= First && parbar <= parmin) {
        parmin = parbar;
        tokeep = its.Value();
      }
    }

    if (tokeep.IsNull()) { // preserve the closest interval

      Standard_Real dmin = RealLast();
      for (its.Initialize(parts); its.More(); its.Next()) {
        Baryc(its.Value(),Barycentre);
        parbar = ElCLib::LineParameter(myAxis,Barycentre);
        if (Abs(First - parbar) < dmin ) {
          dmin = Abs(First-parbar);
          tokeep = its.Value();
        }
      }
    }
    for (its.Initialize(parts); its.More(); its.Next()) {
      if (tokeep.IsSame(its.Value())) {
        KeepPart(its.Value());
        break;
      }
    }
  }
}

//=======================================================================
//function : Build
//purpose  : 
//=======================================================================

void BRepFeat_MakeCylindricalHole::Build ()
{
  if (myStatus == BRepFeat_NoError) {
    PerformResult();
    if (!ErrorStatus()) {
      myStatus = (myValidate) ? Validate() : BRepFeat_NoError;
      if (myStatus == BRepFeat_NoError) {
        myShape = Shape();
      }
    }
    else {
      myStatus = BRepFeat_InvalidPlacement; // why not
    }
  }
}


//=======================================================================
//function : Validate
//purpose  : 
//=======================================================================

BRepFeat_Status BRepFeat_MakeCylindricalHole::Validate ()
{
  BRepFeat_Status thestat = BRepFeat_NoError;
  TopExp_Explorer ex(Shape(),TopAbs_FACE);
  if (myIsBlind) { // limit of the hole
    for (; ex.More(); ex.Next()) {
      if (ex.Current().IsSame(myTopFace) ) {
        break;
      }
    }
    if (!ex.More()) {
      thestat = BRepFeat_HoleTooLong;
    }
  }
  else {
    for (; ex.More(); ex.Next()) {
      if (ex.Current().IsSame(myTopFace) ) {
        return BRepFeat_InvalidPlacement;
      }
    }
    for (ex.ReInit(); ex.More(); ex.Next()) {
      if (ex.Current().IsSame(myBotFace) ) {
        return BRepFeat_InvalidPlacement;
      }
    }
  }
  return thestat;
}



void Baryc(const TopoDS_Shape& S, gp_Pnt& B)
{
  TopExp_Explorer exp(S,TopAbs_EDGE);
  gp_XYZ Bar(0.,0.,0.);
  TopLoc_Location L;
  Handle(Geom_Curve) C;
  Standard_Real prm,First,Last;

  Standard_Integer i, nbp= 0;
  for (; exp.More(); exp.Next()) {
    // Calculate points by non-degenerated edges
    const TopoDS_Edge& E = TopoDS::Edge(exp.Current());
    if (!BRep_Tool::Degenerated(E)) {
      C = BRep_Tool::Curve(E,L,First,Last);
      C = Handle(Geom_Curve)::DownCast(C->Transformed(L.Transformation()));
      for (i=1;i<=11; i++) {
        prm = ((11-i)*First + (i-1)*Last)/10.;
        Bar += C->Value(prm).XYZ();
        nbp++;
      }
    }
  }
  Bar.Divide((Standard_Real)nbp);
  B.SetXYZ(Bar);
}


void BoxParameters(const TopoDS_Shape& S,
                   const gp_Ax1& Axis,
                   Standard_Real& parmin,
                   Standard_Real& parmax)
{

  // calculate the parameters of a bounding box in the direction of the axis of the hole
  Bnd_Box B;
  BRepBndLib::Add(S,B);
  Standard_Real c[6];
  B.Get(c[0],c[2],c[4],c[1],c[3],c[5]);
  gp_Pnt P;
  Standard_Integer i,j,k;
  parmin = RealLast();
  parmax = RealFirst();
  Standard_Real param;
  for (i=0; i<=1; i++) {
    P.SetX(c[i]);
    for (j=2; j<=3; j++) {
      P.SetY(c[j]);
      for (k=4; k<=5; k++) {
        P.SetZ(c[k]);
        param = ElCLib::LineParameter(Axis,P);
        parmin = Min(param,parmin);
        parmax = Max(param,parmax);
      }
    }
  }
}
