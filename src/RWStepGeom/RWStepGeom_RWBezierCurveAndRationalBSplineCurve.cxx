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


#include <RWStepGeom_RWBezierCurveAndRationalBSplineCurve.ixx>
#include <StepGeom_BezierCurve.hxx>
#include <StepGeom_RationalBSplineCurve.hxx>
#include <StepGeom_HArray1OfCartesianPoint.hxx>
#include <StepGeom_CartesianPoint.hxx>
#include <StepGeom_BSplineCurveForm.hxx>
#include <StepData_Logical.hxx>
#include <TColStd_HArray1OfReal.hxx>


#include <Interface_EntityIterator.hxx>


#include <StepGeom_BezierCurveAndRationalBSplineCurve.hxx>



// --- Enum : BSplineCurveForm ---
static TCollection_AsciiString bscfEllipticArc(".ELLIPTIC_ARC.");
static TCollection_AsciiString bscfPolylineForm(".POLYLINE_FORM.");
static TCollection_AsciiString bscfParabolicArc(".PARABOLIC_ARC.");
static TCollection_AsciiString bscfCircularArc(".CIRCULAR_ARC.");
static TCollection_AsciiString bscfUnspecified(".UNSPECIFIED.");
static TCollection_AsciiString bscfHyperbolicArc(".HYPERBOLIC_ARC.");

RWStepGeom_RWBezierCurveAndRationalBSplineCurve::RWStepGeom_RWBezierCurveAndRationalBSplineCurve () {}

void RWStepGeom_RWBezierCurveAndRationalBSplineCurve::ReadStep
	(const Handle(StepData_StepReaderData)& data,
	 const Standard_Integer num0,
	 Handle(Interface_Check)& ach,
	 const Handle(StepGeom_BezierCurveAndRationalBSplineCurve)& ent) const
{

	Standard_Integer num = num0;


	// --- Instance of plex componant BezierCurve ---

	if (!data->CheckNbParams(num,0,ach,"bezier_curve")) return;

	num = data->NextForComplex(num);

	// --- Instance of plex componant BoundedCurve ---

	if (!data->CheckNbParams(num,0,ach,"bounded_curve")) return;

	num = data->NextForComplex(num);

	// --- Instance of common supertype BSplineCurve ---

	if (!data->CheckNbParams(num,5,ach,"b_spline_curve")) return;
	// --- field : degree ---


	Standard_Integer aDegree;
	//szv#4:S4163:12Mar99 `Standard_Boolean stat1 =` not needed
	data->ReadInteger (num,1,"degree",ach,aDegree);
	// --- field : controlPointsList ---


	Handle(StepGeom_HArray1OfCartesianPoint) aControlPointsList;
	Handle(StepGeom_CartesianPoint) anent2;
	Standard_Integer nsub2;
	if (data->ReadSubList (num,2,"control_points_list",ach,nsub2)) {
	  Standard_Integer nb2 = data->NbParams(nsub2);
	  aControlPointsList = new StepGeom_HArray1OfCartesianPoint (1, nb2);
	  for (Standard_Integer i2 = 1; i2 <= nb2; i2 ++) {
	    //szv#4:S4163:12Mar99 `Standard_Boolean stat2 =` not needed
	    if (data->ReadEntity (nsub2, i2,"cartesian_point", ach,
				  STANDARD_TYPE(StepGeom_CartesianPoint), anent2))
	      aControlPointsList->SetValue(i2, anent2);
	  }
	}

	// --- field : curveForm ---


	StepGeom_BSplineCurveForm aCurveForm = StepGeom_bscfPolylineForm;
	if (data->ParamType(num,3) == Interface_ParamEnum) {
	  Standard_CString text = data->ParamCValue(num,3);
	  if      (bscfEllipticArc.IsEqual(text)) aCurveForm = StepGeom_bscfEllipticArc;
	  else if (bscfPolylineForm.IsEqual(text)) aCurveForm = StepGeom_bscfPolylineForm;
	  else if (bscfParabolicArc.IsEqual(text)) aCurveForm = StepGeom_bscfParabolicArc;
	  else if (bscfCircularArc.IsEqual(text)) aCurveForm = StepGeom_bscfCircularArc;
	  else if (bscfUnspecified.IsEqual(text)) aCurveForm = StepGeom_bscfUnspecified;
	  else if (bscfHyperbolicArc.IsEqual(text)) aCurveForm = StepGeom_bscfHyperbolicArc;
	  else ach->AddFail("Enumeration b_spline_curve_form has not an allowed value");
	}
	else ach->AddFail("Parameter #3 (curve_form) is not an enumeration");
	// --- field : closedCurve ---


	StepData_Logical aClosedCurve;
	//szv#4:S4163:12Mar99 `Standard_Boolean stat4 =` not needed
	data->ReadLogical (num,4,"closed_curve",ach,aClosedCurve);
	// --- field : selfIntersect ---


	StepData_Logical aSelfIntersect;
	//szv#4:S4163:12Mar99 `Standard_Boolean stat5 =` not needed
	data->ReadLogical (num,5,"self_intersect",ach,aSelfIntersect);

	num = data->NextForComplex(num);

	// --- Instance of plex componant Curve ---

	if (!data->CheckNbParams(num,0,ach,"curve")) return;

	num = data->NextForComplex(num);

	// --- Instance of plex componant GeometricRepresentationItem ---

	if (!data->CheckNbParams(num,0,ach,"geometric_representation_item")) return;

	num = data->NextForComplex(num);

	// --- Instance of plex componant RationalBSplineCurve ---

	if (!data->CheckNbParams(num,1,ach,"rational_b_spline_curve")) return;

	// --- field : weightsData ---

	Handle(TColStd_HArray1OfReal) aWeightsData;
	Standard_Real aWeightsDataItem;
	Standard_Integer nsub6;
	if (data->ReadSubList (num,1,"weights_data",ach,nsub6)) {
	  Standard_Integer nb6 = data->NbParams(nsub6);
	  aWeightsData = new TColStd_HArray1OfReal (1, nb6);
	  for (Standard_Integer i6 = 1; i6 <= nb6; i6 ++) {
	    //szv#4:S4163:12Mar99 `Standard_Boolean stat6 =` not needed
	    if (data->ReadReal (nsub6,i6,"weights_data",ach,aWeightsDataItem))
	      aWeightsData->SetValue(i6,aWeightsDataItem);
	  }
	}

	num = data->NextForComplex(num);

	// --- Instance of plex componant RepresentationItem ---

	if (!data->CheckNbParams(num,1,ach,"representation_item")) return;

	// --- field : name ---

	Handle(TCollection_HAsciiString) aName;
	//szv#4:S4163:12Mar99 `Standard_Boolean stat7 =` not needed
	data->ReadString (num,1,"name",ach,aName);

	//--- Initialisation of the red entity ---

	ent->Init(aName,aDegree,aControlPointsList,aCurveForm,aClosedCurve,aSelfIntersect,aWeightsData);
}


void RWStepGeom_RWBezierCurveAndRationalBSplineCurve::WriteStep
	(StepData_StepWriter& SW,
	 const Handle(StepGeom_BezierCurveAndRationalBSplineCurve)& ent) const
{

	// --- Instance of plex componant BezierCurve ---

	SW.StartEntity("BEZIER_CURVE");

	// --- Instance of plex componant BoundedCurve ---

	SW.StartEntity("BOUNDED_CURVE");

	// --- Instance of common supertype BSplineCurve ---

	SW.StartEntity("B_SPLINE_CURVE");
	// --- field : degree ---

	SW.Send(ent->Degree());
	// --- field : controlPointsList ---

	SW.OpenSub();
	for (Standard_Integer i2 = 1;  i2 <= ent->NbControlPointsList();  i2 ++) {
	  SW.Send(ent->ControlPointsListValue(i2));
	}
	SW.CloseSub();
	// --- field : curveForm ---

	switch(ent->CurveForm()) {
	  case StepGeom_bscfEllipticArc : SW.SendEnum (bscfEllipticArc); break;
	  case StepGeom_bscfPolylineForm : SW.SendEnum (bscfPolylineForm); break;
	  case StepGeom_bscfParabolicArc : SW.SendEnum (bscfParabolicArc); break;
	  case StepGeom_bscfCircularArc : SW.SendEnum (bscfCircularArc); break;
	  case StepGeom_bscfUnspecified : SW.SendEnum (bscfUnspecified); break;
	  case StepGeom_bscfHyperbolicArc : SW.SendEnum (bscfHyperbolicArc); break;
	}
	// --- field : closedCurve ---

	SW.SendLogical(ent->ClosedCurve());
	// --- field : selfIntersect ---

	SW.SendLogical(ent->SelfIntersect());

	// --- Instance of plex componant Curve ---

	SW.StartEntity("CURVE");

	// --- Instance of plex componant GeometricRepresentationItem ---

	SW.StartEntity("GEOMETRIC_REPRESENTATION_ITEM");

	// --- Instance of plex componant RationalBSplineCurve ---

	SW.StartEntity("RATIONAL_B_SPLINE_CURVE");
	// --- field : weightsData ---

	SW.OpenSub();
	for (Standard_Integer i6 = 1;  i6 <= ent->NbWeightsData();  i6 ++) {
	  SW.Send(ent->WeightsDataValue(i6));
	}
	SW.CloseSub();

	// --- Instance of plex componant RepresentationItem ---

	SW.StartEntity("REPRESENTATION_ITEM");
	// --- field : name ---

	SW.Send(ent->Name());
}


void RWStepGeom_RWBezierCurveAndRationalBSplineCurve::Share(const Handle(StepGeom_BezierCurveAndRationalBSplineCurve)& ent, Interface_EntityIterator& iter) const
{

	Standard_Integer nbElem1 = ent->NbControlPointsList();
	for (Standard_Integer is1=1; is1<=nbElem1; is1 ++) {
	  iter.GetOneItem(ent->ControlPointsListValue(is1));
	}

}

