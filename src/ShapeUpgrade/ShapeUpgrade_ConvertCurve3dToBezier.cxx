// Created on: 1999-05-13
// Created by: data exchange team
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



#include <ShapeUpgrade_ConvertCurve3dToBezier.ixx>
#include <Precision.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_BezierCurve.hxx>
#include <ShapeExtend.hxx>
#include <Geom_Line.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_Conic.hxx>
#include <GeomConvert_ApproxCurve.hxx>
#include <GeomConvert.hxx>
#include <GeomConvert_BSplineCurveToBezierCurve.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColGeom_HArray1OfCurve.hxx>
#include <Geom_Circle.hxx>

ShapeUpgrade_ConvertCurve3dToBezier::ShapeUpgrade_ConvertCurve3dToBezier()
{
  mySegments = new TColGeom_HSequenceOfCurve;
  mySplitParams = new TColStd_HSequenceOfReal;
  myLineMode = Standard_True;
  myCircleMode = Standard_True;
  myConicMode = Standard_True;
}

//=======================================================================
//function : Compute
//purpose  : 
//=======================================================================

void ShapeUpgrade_ConvertCurve3dToBezier::Compute()
{
  mySegments->Clear();
  mySplitParams->Clear();
  Standard_Real precision = Precision::PConfusion();
  Standard_Real First =  mySplitValues->Value(1);
  Standard_Real Last = mySplitValues->Value(mySplitValues->Length());
  if(myCurve->IsKind(STANDARD_TYPE(Geom_TrimmedCurve))) {
    Handle(Geom_TrimmedCurve) tmp = Handle(Geom_TrimmedCurve)::DownCast (myCurve);
    Handle(Geom_Curve) BasCurve = tmp->BasisCurve();
    ShapeUpgrade_ConvertCurve3dToBezier converter;
    converter.Init(BasCurve,First,Last);
    converter.SetSplitValues(mySplitValues);
    converter.Compute();
    mySplitValues->ChangeSequence() = converter.SplitValues()->Sequence();
    myNbCurves = mySplitValues->Length()-1;
    myStatus |= converter.myStatus;
    mySegments->ChangeSequence() = converter.Segments()->Sequence();
    mySplitParams->ChangeSequence() = converter.SplitParams()->Sequence();
    return;
  }
  else if(myCurve->IsKind(STANDARD_TYPE(Geom_BezierCurve))) {
    Handle(Geom_BezierCurve) bezier = Handle(Geom_BezierCurve)::DownCast (myCurve);
    myNbCurves = mySplitValues->Length()-1;
    mySplitParams->Append(First);
    mySplitParams->Append(Last);
    if(First < precision && Last > 1 - precision) {
      mySegments->Append(bezier);
      myStatus = ShapeExtend::EncodeStatus (ShapeExtend_OK);
    } else {
      Handle(Geom_BezierCurve) besNew = Handle(Geom_BezierCurve)::DownCast(bezier->Copy());
      besNew->Segment(First,Last);
      mySegments->Append(besNew);
      myStatus = ShapeExtend::EncodeStatus (ShapeExtend_DONE2);
    }
    return;
  }
  else if(myCurve->IsKind(STANDARD_TYPE(Geom_Line))) {
    Handle(Geom_Line) aLine = Handle(Geom_Line)::DownCast(myCurve);
    myNbCurves = mySplitValues->Length()-1;
    mySplitParams->Append(First);
    mySplitParams->Append(Last);
    if(!myLineMode) {
      mySegments->Append(aLine);
      myStatus = ShapeExtend::EncodeStatus (ShapeExtend_OK);
      return;
    }
    TColgp_Array1OfPnt poles(1,2);
    poles(1) = aLine->Value(First);
    poles(2) = aLine->Value(Last);
    Handle(Geom_BezierCurve) bezier = new Geom_BezierCurve(poles);
    mySegments->Append(bezier);
    myStatus = ShapeExtend::EncodeStatus (ShapeExtend_DONE1);
    return;
  }
  else if((myCurve->IsKind(STANDARD_TYPE(Geom_Conic))&&!myConicMode)||
	  (myCurve->IsKind(STANDARD_TYPE(Geom_Circle))&&!myCircleMode)) {
    myNbCurves = mySplitValues->Length()-1;
    mySplitParams->Append(First);
    mySplitParams->Append(Last);
    mySegments->Append(myCurve);
    myStatus = ShapeExtend::EncodeStatus (ShapeExtend_OK);
    return;
  }
  else {
    Handle(Geom_BSplineCurve) aBSpline;
    Standard_Real Shift = 0.;
    if(myCurve->IsKind(STANDARD_TYPE(Geom_Conic))) {
      Handle(Geom_TrimmedCurve) tcurve = new Geom_TrimmedCurve(myCurve,First,Last); //protection agains parabols ets
      GeomConvert_ApproxCurve approx (tcurve, Precision::Approximation(), 
				      GeomAbs_C1, 100, 6 );
      if ( approx.HasResult() )
	aBSpline = Handle(Geom_BSplineCurve)::DownCast(approx.Curve());
      else {
	Handle(Geom_TrimmedCurve) t3d = new Geom_TrimmedCurve(myCurve,First,Last);
	aBSpline = GeomConvert::CurveToBSplineCurve(t3d,Convert_QuasiAngular);
      }
      Shift = First - aBSpline->FirstParameter();
      First = aBSpline->FirstParameter();
      Last = aBSpline->LastParameter();
    }
    else if(!myCurve->IsKind(STANDARD_TYPE(Geom_BSplineCurve))) {
      aBSpline = GeomConvert::CurveToBSplineCurve(myCurve,Convert_QuasiAngular);
    }
    else
      aBSpline = Handle(Geom_BSplineCurve)::DownCast(myCurve);
    
    Standard_Real bf = aBSpline->FirstParameter();
    Standard_Real bl = aBSpline->LastParameter();
    if(Abs(First-bf) < precision)
      First = bf;
    if(Abs(Last-bl) < precision)
      Last = bl;
    if(First < bf){
#ifdef DEB
      cout <<"Warning: The range of the edge exceeds the curve domain" <<endl;
#endif
      First = bf;
      mySplitValues->SetValue(1,First);
    }
    if(Last > bl){
#ifdef DEB
      cout <<"Warning: The range of the edge exceeds the curve domain" <<endl;
#endif
      Last = bl;
      mySplitValues->SetValue(mySplitValues->Length(),Last);
    }
    
    GeomConvert_BSplineCurveToBezierCurve tool(aBSpline,First,Last,precision);
    Standard_Integer nbArcs = tool.NbArcs();
    TColStd_Array1OfReal knots(1,nbArcs+1);
    tool.Knots(knots);
    mySplitParams->Append(First+Shift);
    Standard_Integer j; // svv Jan 10 2000 : porting on DEC
    for(j = 1; j <=nbArcs; j++) {
      Standard_Real nextKnot = knots(j+1)+Shift;
      if(nextKnot - mySplitParams->Value(mySplitParams->Length()) > precision) {
	mySegments->Append(tool.Arc(j));
	mySplitParams->Append(knots(j+1)+Shift);
      }
    }
    
    First = mySplitValues->Value(1);
    for(j = 2; j <= mySplitValues->Length(); j++) {
      Last =  mySplitValues->Value(j);
      for(Standard_Integer i = 2; i <= nbArcs+1; i++) {
	Standard_Real valknot = knots(i)+Shift;
	if(valknot <= First + precision) continue;
	if(valknot >= Last - precision) break;
	mySplitValues->InsertBefore(j++,valknot);
      }
      First = Last;
    }
    myNbCurves = mySplitValues->Length()-1;
  }
  myStatus = ShapeExtend::EncodeStatus (ShapeExtend_DONE1);
}

//=======================================================================
//function : Build
//purpose  : 
//=======================================================================

void ShapeUpgrade_ConvertCurve3dToBezier::Build(const Standard_Boolean /*Segment*/)
{
  Standard_Real prec = Precision::PConfusion();
  Standard_Integer nb = mySplitValues->Length();
  myResultingCurves =  new TColGeom_HArray1OfCurve (1,nb-1);
  Standard_Real prevPar = 0.;
  Standard_Integer j=2;
  for(Standard_Integer i = 2; i <= nb; i++) {
    Standard_Real par = mySplitValues->Value(i);
    for(; j<= mySplitParams->Length(); j++) 
      if(mySplitParams->Value(j)+prec > par) 
	break;
      else
	prevPar = 0.;
	
    Handle(Geom_Curve) crv = Handle(Geom_Curve)::DownCast(mySegments->Value(j-1)->Copy());
    if(crv->IsKind(STANDARD_TYPE(Geom_BezierCurve))) {
      Handle(Geom_BezierCurve) bes = Handle(Geom_BezierCurve)::DownCast(crv);
      Standard_Real uFact = mySplitParams->Value(j) - mySplitParams->Value(j-1);
      Standard_Real pp = mySplitValues->Value(i-1);
      Standard_Real length = (par - pp)/uFact;
      bes->Segment(prevPar, prevPar+length);
      prevPar += length;
      myResultingCurves->SetValue(i-1,bes);
    }
    else 
     myResultingCurves->SetValue(i-1,crv); 
  }
}

//=======================================================================
//function : Segments
//purpose  : 
//=======================================================================

Handle(TColGeom_HSequenceOfCurve) ShapeUpgrade_ConvertCurve3dToBezier::Segments() const
{
  return mySegments;
}

//=======================================================================
//function : SplitParams
//purpose  : 
//=======================================================================

Handle(TColStd_HSequenceOfReal) ShapeUpgrade_ConvertCurve3dToBezier::SplitParams() const
{
  return mySplitParams;
}
