// Created on: 1995-07-17
// Created by: Modelistation
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


#include <HLRBRep_CurveTool.ixx>
#include <HLRBRep_Curve.hxx>
#include <GeomAbs_CurveType.hxx>
#include <GeomAbs_Shape.hxx>
#include <Handle_Geom2d_BezierCurve.hxx>
#include <Handle_Geom2d_BSplineCurve.hxx>
#include <TColStd_Array1OfReal.hxx>

//=======================================================================
//function : NbSamples
//purpose  : 
//=======================================================================

Standard_Integer
HLRBRep_CurveTool::NbSamples (const Standard_Address C)
{ 
  GeomAbs_CurveType typC = ((HLRBRep_Curve *)C)->GetType();
  static Standard_Real nbsOther = 10.0;
  Standard_Real nbs = nbsOther;
  
  if(typC == GeomAbs_Line) 
    nbs = 2;
  else if(typC == GeomAbs_BezierCurve) 
    nbs = 3 + ((HLRBRep_Curve *)C)->NbPoles();
  else if(typC == GeomAbs_BSplineCurve) { 
    nbs = ((HLRBRep_Curve *)C)->NbKnots();
    nbs*= ((HLRBRep_Curve *)C)->Degree();
    if(nbs < 2.0) nbs=2;
  }
  if(nbs>50)
    nbs = 50;
  return((Standard_Integer)nbs);
}

//=======================================================================
//function : NbSamples
//purpose  : 
//=======================================================================

Standard_Integer
HLRBRep_CurveTool::NbSamples (const Standard_Address C,
			      const Standard_Real u1,
			      const Standard_Real u2) 
{ 
  GeomAbs_CurveType typC = ((HLRBRep_Curve *)C)->GetType();
  static Standard_Real nbsOther = 10.0;
  Standard_Real nbs = nbsOther;
  
  if(typC == GeomAbs_Line) 
    nbs = 2;
  else if(typC == GeomAbs_BezierCurve) 
    nbs = 3 + ((HLRBRep_Curve *)C)->NbPoles();
  else if(typC == GeomAbs_BSplineCurve) { 
    nbs = ((HLRBRep_Curve *)C)->NbKnots();
    nbs*= ((HLRBRep_Curve *)C)->Degree();
    if(nbs < 2.0) nbs=2;
  }
  if(nbs>50)
    nbs = 50;
  return((Standard_Integer)nbs);
}
