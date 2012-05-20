// Created on: 1998-03-12
// Created by: Pierre BARRAS
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


#include <ShapeUpgrade_SplitCurve2d.ixx>
#include <ShapeUpgrade.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <TColStd_ListIteratorOfListOfReal.hxx>
#include <TColStd_HSequenceOfReal.hxx>
#include <TColGeom2d_HArray1OfCurve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2d_OffsetCurve.hxx>
#include <Standard_ErrorHandler.hxx>
#include <Standard_Failure.hxx>
#include <ShapeExtend.hxx>
#include <Precision.hxx>
#include <Geom2d_BezierCurve.hxx>
#include <ShapeAnalysis_Curve.hxx>

//=======================================================================
//function : ShapeUpgrade_SplitCurve2d
//purpose  : 
//=======================================================================

ShapeUpgrade_SplitCurve2d::ShapeUpgrade_SplitCurve2d()
{
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

 void ShapeUpgrade_SplitCurve2d::Init(const Handle(Geom2d_Curve)& C) 
{
  Init (C, C->FirstParameter(), C->LastParameter());
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

 void ShapeUpgrade_SplitCurve2d::Init(const Handle(Geom2d_Curve)& C,
				      const Standard_Real First,
				      const Standard_Real Last) 
{
//  if (ShapeUpgrade::Debug()) cout << "SplitCurve2d::Init"<<endl;
  Handle(Geom2d_Curve) CopyOfC = Handle(Geom2d_Curve)::DownCast(C->Copy());
  myCurve = CopyOfC;
  
  Standard_Real precision = Precision::PConfusion();
  Standard_Real firstPar = First;
  Standard_Real lastPar = Last;
  Handle (Geom2d_Curve) aCurve = myCurve;
  if(aCurve->IsKind(STANDARD_TYPE(Geom2d_TrimmedCurve))) 
    aCurve=Handle(Geom2d_TrimmedCurve)::DownCast(aCurve)->BasisCurve();
  // 15.11.2002 PTV OCC966
  if(!ShapeAnalysis_Curve::IsPeriodic(C)) {
    Standard_Real fP = aCurve->FirstParameter();
    Standard_Real lP  = aCurve->LastParameter();
    if(Abs(firstPar-fP) < precision)
       firstPar = fP;
    if(Abs(lastPar-lP) < precision)
      lastPar = lP;
    if(firstPar < fP){
#ifdef DEB
      cout <<"Warning: The range of the edge exceeds the curve domain" <<endl;
#endif
      firstPar = fP;
    }
    if(lastPar > lP){
#ifdef DEB
      cout <<"Warning: The range of the edge exceeds the curve domain" <<endl;
#endif
      lastPar = lP;
    }
    if( (lastPar-firstPar) < precision)
      lastPar=firstPar+2*precision;
  }
  
  ShapeUpgrade_SplitCurve::Init (firstPar, lastPar);

  // first, we make a copy of C to prevent modification:
//  if (ShapeUpgrade::Debug()) cout << ". copy of the curve"<<endl;
  
  myNbCurves = 1;
}

//=======================================================================
//function : Build
//purpose  : 
//=======================================================================

 void ShapeUpgrade_SplitCurve2d::Build(const Standard_Boolean Segment) 
{
//  if (ShapeUpgrade::Debug()) cout<<"ShapeUpgrade_SplitCurve2d::Build"<<endl;
  Standard_Real First =  mySplitValues->Value(1);
  Standard_Real Last = mySplitValues->Value(mySplitValues->Length());
  //PrepareKnots();
  if (mySplitValues->Length() > 2)
    myStatus = ShapeExtend::EncodeStatus (ShapeExtend_DONE1);
  if (myCurve->IsKind(STANDARD_TYPE(Geom2d_TrimmedCurve))) {
    Handle(Geom2d_TrimmedCurve) tmp = Handle(Geom2d_TrimmedCurve)::DownCast (myCurve);
    Handle(Geom2d_Curve) BasCurve = tmp->BasisCurve();
    ShapeUpgrade_SplitCurve2d spc;
    spc.Init(BasCurve,First,Last); 
    spc.SetSplitValues(mySplitValues);
    spc.Build(Segment);
    myNbCurves = spc.GetCurves()->Length();
    
    myResultingCurves=new TColGeom2d_HArray1OfCurve (1,myNbCurves);
    if (myNbCurves == 1) {
      Handle(Geom2d_TrimmedCurve) NewTrimCurve = 
	new Geom2d_TrimmedCurve(spc.GetCurves()->Value(1),First,Last);
      myResultingCurves->SetValue(1,NewTrimCurve);
    }
    else 
      myResultingCurves = spc.GetCurves();
    myStatus |= spc.myStatus;
    return;
  }
  else if (myCurve->IsKind(STANDARD_TYPE(Geom2d_OffsetCurve))) {
    Handle(Geom2d_OffsetCurve) tmp = Handle(Geom2d_OffsetCurve)::DownCast (myCurve);
    Handle(Geom2d_Curve) BasCurve = tmp->BasisCurve();
    Standard_Real Offset = tmp->Offset();
    ShapeUpgrade_SplitCurve2d spc;
    spc.Init(BasCurve,First,Last);
    spc.SetSplitValues(mySplitValues);
    spc.Build(Segment);
    myNbCurves = spc.GetCurves()->Length();
    myResultingCurves = new TColGeom2d_HArray1OfCurve (1,myNbCurves);
    for(Standard_Integer i = 1; i <= myNbCurves; i++) {
      Handle(Geom2d_OffsetCurve) NewOffsetCurve = new Geom2d_OffsetCurve(spc.GetCurves()->Value(i),Offset);
      myResultingCurves->SetValue(i,NewOffsetCurve);
    }
    myStatus |= spc.myStatus;
    return;
  }

  myNbCurves = mySplitValues->Length() -1;
  myResultingCurves=new TColGeom2d_HArray1OfCurve (1,myNbCurves);
  if(myNbCurves ==1) {
    Standard_Boolean filled = Standard_True;
    if ( Abs ( myCurve->FirstParameter() - First ) < Precision::PConfusion() && 
	 Abs ( myCurve->LastParameter()  - Last  ) < Precision::PConfusion() )
      myResultingCurves->SetValue(1,myCurve);
    
    else if ( ! Segment || (!myCurve->IsKind (STANDARD_TYPE (Geom2d_BSplineCurve)) &&
	     !myCurve->IsKind (STANDARD_TYPE (Geom2d_BezierCurve))) || ! Status ( ShapeExtend_DONE2 ) ) {
      if(myCurve->IsKind (STANDARD_TYPE (Geom2d_BSplineCurve)) ||
	     myCurve->IsKind (STANDARD_TYPE (Geom2d_BezierCurve) )) {
	Handle(Geom2d_Curve) theNewCurve = Handle(Geom2d_Curve)::DownCast(myCurve->Copy());
	try {
	  OCC_CATCH_SIGNALS
	  if (myCurve->IsKind (STANDARD_TYPE (Geom2d_BSplineCurve)))
	    Handle(Geom2d_BSplineCurve)::DownCast(theNewCurve)->Segment (First, Last);
	  else if (myCurve->IsKind (STANDARD_TYPE (Geom2d_BezierCurve)))
	    Handle(Geom2d_BezierCurve)::DownCast(theNewCurve)->Segment (First, Last);
	}
	catch (Standard_Failure) {
#ifdef DEB 
	  cout << "Warning: ShapeUpgrade_Split2dCurve::Build(): Exception in Segment      :";
	  Standard_Failure::Caught()->Print(cout); cout << endl;
#endif
	  theNewCurve = new Geom2d_TrimmedCurve(Handle(Geom2d_Curve)::DownCast(myCurve->Copy()),First,Last);
	}
	myResultingCurves->SetValue (1, theNewCurve);
      
      }
      else {
	Handle(Geom2d_TrimmedCurve) theNewCurve = new Geom2d_TrimmedCurve(Handle(Geom2d_Curve)::DownCast(myCurve->Copy()),First,Last);
	myResultingCurves->SetValue (1, theNewCurve);
      }
    }
    else filled = Standard_False;
    if ( filled ) return;
  }
  
  
  if (myCurve->IsKind (STANDARD_TYPE (Geom2d_BSplineCurve))) {
    Handle(Geom2d_BSplineCurve) BsCurve = Handle(Geom2d_BSplineCurve)::DownCast(myCurve->Copy());
    Standard_Integer FirstInd =BsCurve->FirstUKnotIndex(), 
    LastInd = BsCurve->LastUKnotIndex();
    Standard_Integer j =  FirstInd;
    for(Standard_Integer ii =1 ; ii <= mySplitValues->Length(); ii++) {
      Standard_Real spval = mySplitValues->Value(ii);
      for(; j <=LastInd;j++) {
	if( spval > BsCurve->Knot(j) + Precision::PConfusion()) continue;
	if( spval < BsCurve->Knot(j) - Precision::PConfusion()) break;
	mySplitValues->SetValue(ii,BsCurve->Knot(j));
      }
      if(j == LastInd) break;
    }
    
  }
  for (Standard_Integer i = 1; i <= myNbCurves; i++) {
    // skl : in the next block I change "First","Last" to "Firstt","Lastt"
    Standard_Real Firstt = mySplitValues->Value(i), Lastt = mySplitValues->Value(i+1);
    Handle(Geom2d_Curve) theNewCurve;
    if(Segment) {
      // creates a copy of myCurve before to segment:
      if (myCurve->IsKind (STANDARD_TYPE (Geom2d_BSplineCurve)) ||
	  myCurve->IsKind (STANDARD_TYPE (Geom2d_BezierCurve))) {
	theNewCurve = Handle(Geom2d_Curve)::DownCast(myCurve->Copy());
	try {
	  OCC_CATCH_SIGNALS
	  if (myCurve->IsKind (STANDARD_TYPE (Geom2d_BSplineCurve)))
	    Handle(Geom2d_BSplineCurve)::DownCast(theNewCurve)->Segment (Firstt, Lastt);
	  else if (myCurve->IsKind (STANDARD_TYPE (Geom2d_BezierCurve)))
	    Handle(Geom2d_BezierCurve)::DownCast(theNewCurve)->Segment (Firstt, Lastt);
	  myStatus |= ShapeExtend::EncodeStatus ( ShapeExtend_DONE3 );
	}
	catch (Standard_Failure) {
#ifdef DEB 
	  cout << "Warning: ShapeUpgrade_Split2dCurve::Build(): Exception in Segment      :";
	  Standard_Failure::Caught()->Print(cout); cout << endl;
#endif
	  theNewCurve = new Geom2d_TrimmedCurve(Handle(Geom2d_Curve)::DownCast(myCurve->Copy()),Firstt,Lastt);
	}
      }
      else 
	theNewCurve = new Geom2d_TrimmedCurve(Handle(Geom2d_Curve)::DownCast(myCurve->Copy()),Firstt,Lastt);
    }
    myResultingCurves->SetValue (i, theNewCurve);
  }
}

//=======================================================================
//function : GetCurves
//purpose  : 
//=======================================================================

const Handle(TColGeom2d_HArray1OfCurve)& ShapeUpgrade_SplitCurve2d::GetCurves() const
{
  return myResultingCurves;
}
