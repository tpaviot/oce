// Created on: 1999-04-15
// Created by: Roman LYGIN
// Copyright (c) 1999-1999 Matra Datavision
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



#include <ShapeUpgrade_SplitCurve3dContinuity.ixx>
#include <Standard_ErrorHandler.hxx>
#include <Standard_Failure.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Precision.hxx>
#include <ShapeUpgrade.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_OffsetCurve.hxx>
#include <Geom_Curve.hxx>
#include <TColStd_HSequenceOfReal.hxx>
#include <TColGeom_HArray1OfCurve.hxx>
#include <ShapeExtend.hxx>

//=======================================================================
//function : ShapeUpgrade_SplitCurve3dContinuity
//purpose  : 
//=======================================================================

ShapeUpgrade_SplitCurve3dContinuity::ShapeUpgrade_SplitCurve3dContinuity()
{
  myCriterion = GeomAbs_C1;
  myTolerance = Precision::Confusion();
  myCont =1;
}

//=======================================================================
//function : SetCriterion
//purpose  : 
//=======================================================================

 void ShapeUpgrade_SplitCurve3dContinuity::SetCriterion(const GeomAbs_Shape Criterion) 
{
  myCriterion = Criterion;
  switch (myCriterion) {
    case GeomAbs_C0 : myCont = 0; break;
    case GeomAbs_C1 : myCont = 1; break;
    case GeomAbs_C2 : myCont = 2; break;
    case GeomAbs_C3 : myCont = 3; break;
    case GeomAbs_CN : myCont = 4; break;
    default         : myCont = 1;
  }
}

//=======================================================================
//function : SetTolerance
//purpose  : 
//=======================================================================

 void ShapeUpgrade_SplitCurve3dContinuity::SetTolerance(const Standard_Real Tol) 
{
  myTolerance = Tol;
}

//=======================================================================
//function : Compute
//purpose  : 
//===================================================================
void ShapeUpgrade_SplitCurve3dContinuity::Compute()  
{  
  Standard_Real First =  mySplitValues->Value(1);
  Standard_Real Last =  mySplitValues->Value(mySplitValues->Length());
  Standard_Real precision = Precision::PConfusion();
  if(myCurve->Continuity() < myCriterion) 
    myStatus = ShapeExtend::EncodeStatus (ShapeExtend_DONE2);
  if (mySplitValues->Length() > 2)
    myStatus = ShapeExtend::EncodeStatus (ShapeExtend_DONE1);
  if (myCurve->IsKind(STANDARD_TYPE(Geom_TrimmedCurve))) {
    Handle(Geom_TrimmedCurve) tmp = Handle(Geom_TrimmedCurve)::DownCast (myCurve);
    Handle(Geom_Curve) BasCurve = tmp->BasisCurve();
    ShapeUpgrade_SplitCurve3dContinuity spc;
//    spc.Init(BasCurve,Max(tmp->FirstParameter(),First),Min(tmp->LastParameter(),Last));
    spc.Init(BasCurve,First,Last);
    spc.SetSplitValues(mySplitValues);  
    spc.SetTolerance(myTolerance);
    spc.SetCriterion(myCriterion);
    spc.Compute();
    mySplitValues->Clear();
    mySplitValues->ChangeSequence() = spc.SplitValues()->Sequence();
    myStatus |= spc.myStatus;
    return;
  }
  else if (myCurve->IsKind(STANDARD_TYPE(Geom_OffsetCurve))) {
    GeomAbs_Shape BasCriterion;
    switch (myCriterion) {
      default         :
      case GeomAbs_C1 : BasCriterion = GeomAbs_C2; break;
      case GeomAbs_C2 : BasCriterion = GeomAbs_C3; break;
      case GeomAbs_C3 : // if (ShapeUpgrade::Debug()) cout<<". this criterion is not suitable for a Offset curve"<<endl; 
#ifdef DEB
			cout << "Warning: ShapeUpgrade_SplitCurve3dContinuity: criterion C3 for Offset curve" << endl; 
#endif
      case GeomAbs_CN : BasCriterion = GeomAbs_CN; break;
    }
    Handle(Geom_OffsetCurve) tmp = Handle(Geom_OffsetCurve)::DownCast (myCurve);
    Handle(Geom_Curve) BasCurve = tmp->BasisCurve();
    //Standard_Real Offset = tmp->Offset(); // Offset not used (skl)
    //gp_Dir Direct = tmp->Direction(); // Direct not used (skl)
    ShapeUpgrade_SplitCurve3dContinuity spc;
//    spc.Init(BasCurve,Max(tmp->FirstParameter(),First),Min(tmp->LastParameter(),Last));
    spc.Init(BasCurve,First,Last);
    spc.SetSplitValues(mySplitValues);
    spc.SetTolerance(myTolerance);
    spc.SetCriterion(BasCriterion);
    spc.Compute();
    mySplitValues->Clear();
    mySplitValues->ChangeSequence() = spc.SplitValues()->Sequence();
    myStatus |= spc.myStatus;
    return ;
  }
  
  Handle(Geom_BSplineCurve) MyBSpline = Handle(Geom_BSplineCurve)::DownCast (myCurve);
  if (MyBSpline.IsNull()) {
//    if (ShapeUpgrade::Debug()) cout<<". curve is not a Bspline"<<endl;
    return ;
  }
  // it is a BSplineCurve
//  if (ShapeUpgrade::Debug()) cout<<". curve is a Bspline"<<endl;

  myNbCurves=1;
  Standard_Integer Deg=MyBSpline->Degree();
  Standard_Integer NbKnots= MyBSpline->NbKnots(); 
//  if (ShapeUpgrade::Debug()) cout<<". NbKnots="<<NbKnots<<endl;
  if (NbKnots <= 2) {
    return;
  }
  // Only the internal knots are checked.
  Standard_Integer FirstInd =MyBSpline->FirstUKnotIndex()+1, 
  LastInd = MyBSpline->LastUKnotIndex()-1;
  for(Standard_Integer j =2; j <= mySplitValues->Length(); j++) {
    Last =  mySplitValues->Value(j);  
    for (Standard_Integer iknot = FirstInd; iknot <= LastInd; iknot++) {
      Standard_Real valknot = MyBSpline->Knot(iknot);
      if(valknot <= First + precision) continue;
      if(valknot > Last - precision) break;
      Standard_Integer Continuity=Deg-MyBSpline->Multiplicity(iknot);
      if (Continuity < myCont) { 
	// At this knot, the curve is C0; try to remove Knot.
	Standard_Boolean corrected = Standard_False;
	Standard_Integer newMultiplicity = Deg - myCont;
 	if (newMultiplicity < 0) newMultiplicity = 0;
	{
	  try {
	    OCC_CATCH_SIGNALS
	    corrected = MyBSpline->RemoveKnot(iknot, newMultiplicity, myTolerance);
	  }
	  catch (Standard_Failure) {
	    corrected = Standard_False;
	  }
	}
	
	
	if (corrected && newMultiplicity > 0) {
	 Continuity=Deg-MyBSpline->Multiplicity(iknot);
	 corrected = (Continuity >= myCont);
	}
	if (corrected) {
	  // at this knot, the continuity is now C1. Nothing else to do.
//	  if (ShapeUpgrade::Debug()) cout<<". Correction at Knot "<<iknot<<endl;
	  myStatus |= ShapeExtend::EncodeStatus ( ShapeExtend_DONE3 );
          if(newMultiplicity == 0) {
            //in case if knot is completelly removed
            //it is necessary to modify last idex and decrease current knot index
            LastInd = MyBSpline->LastUKnotIndex()-1;
            iknot--;
          }
	}
	else {
	  // impossible to force C1 within the tolerance: 
	  // this knot will be a splitting value.
	  mySplitValues->InsertBefore(j++,MyBSpline->Knot(iknot));
	  myNbCurves++;
//	  if (ShapeUpgrade::Debug()) cout<<". Splitting at Knot "<<iknot<<endl;
	}
      }
    }
    First = Last;
  }
  
  if (mySplitValues->Length() > 2)
    myStatus = ShapeExtend::EncodeStatus (ShapeExtend_DONE1);
}

//=======================================================================
//function : GetCurve
//purpose  : 
//=======================================================================

const Handle(Geom_Curve)& ShapeUpgrade_SplitCurve3dContinuity::GetCurve() const
{
  return myCurve;
}
