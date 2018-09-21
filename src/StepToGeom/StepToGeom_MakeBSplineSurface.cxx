// Created on: 1993-07-02
// Created by: Martine LANGLOIS
// Copyright (c) 1993-1999 Matra Datavision
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

#include <StepToGeom_MakeBSplineSurface.ixx>
#include <StepGeom_BSplineSurfaceWithKnots.hxx>
#include <StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColgp_Array2OfPnt.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <TColStd_HArray2OfReal.hxx>
#include <StepGeom_HArray2OfCartesianPoint.hxx>
#include <StepGeom_CartesianPoint.hxx>
#include <StepToGeom_MakeCartesianPoint.hxx>
#include <Geom_CartesianPoint.hxx>
#include <gp_Pnt.hxx>

//=============================================================================
// Creation d' une BSplineSurface de Geom a partir d' une
// BSplineSurface de Step
//=============================================================================


Standard_Boolean StepToGeom_MakeBSplineSurface::Convert
    (const Handle(StepGeom_BSplineSurface)& SS,
     Handle(Geom_BSplineSurface)& CS)
{
  Standard_Integer                    i, j;
  Handle(StepGeom_BSplineSurfaceWithKnots) BS;
  Handle(StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface) BSR;

  if (SS->IsKind(STANDARD_TYPE(StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface))) {
    BSR = Handle(StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface)::DownCast(SS);
    BS = BSR->BSplineSurfaceWithKnots();
  } else BS = Handle(StepGeom_BSplineSurfaceWithKnots)::DownCast(SS);

  if ( BS.IsNull() ) {
    cout << "StepToGeom_MakeBSplineSurface failed, cast failed! " << endl;
    return Standard_False;
  }

  const Standard_Integer UDeg = BS->UDegree();
  const Standard_Integer VDeg = BS->VDegree();
  const Standard_Integer NUPoles = BS->NbControlPointsListI();
  const Standard_Integer NVPoles = BS->NbControlPointsListJ();
  const Handle(StepGeom_HArray2OfCartesianPoint)& aControlPointsList = BS->ControlPointsList();
  Handle(Geom_CartesianPoint) P;
  TColgp_Array2OfPnt Poles(1,NUPoles,1,NVPoles);
  for (i=1; i<=NUPoles; i++) {
    for (j=1; j<=NVPoles; j++) {
      if (StepToGeom_MakeCartesianPoint::Convert(aControlPointsList->Value(i,j),P))
        Poles.SetValue(i,j,P->Pnt());
	  else
        return Standard_False;
    }
  }
  const Standard_Integer NUKnots = BS->NbUMultiplicities();
  const Handle(TColStd_HArray1OfInteger)& aUMultiplicities = BS->UMultiplicities();
  const Handle(TColStd_HArray1OfReal)& aUKnots = BS->UKnots();
  
  // count number of unique uknots
  Standard_Real lastKnot = RealFirst();
  Standard_Integer NUKnotsUnique = 0;
  for (i=1; i<=NUKnots; i++) {
    if (aUKnots->Value(i) - lastKnot > Epsilon (Abs(lastKnot))) {
      NUKnotsUnique++;
      lastKnot = aUKnots->Value(i);
    }
  }

  // set umultiplicities and uknots
  TColStd_Array1OfInteger UMult(1,NUKnotsUnique);
  TColStd_Array1OfReal KUn(1,NUKnotsUnique);
  Standard_Integer pos = 1;
  lastKnot = aUKnots->Value(1);
  KUn.SetValue(1, aUKnots->Value(1));
  UMult.SetValue(1, aUMultiplicities->Value(1));
  for (i=2; i<=NUKnots; i++) {
    if (aUKnots->Value(i) - lastKnot > Epsilon (Abs(lastKnot))) {
      pos++;
      KUn.SetValue(pos, aUKnots->Value(i));
      UMult.SetValue(pos, aUMultiplicities->Value(i));
      lastKnot = aUKnots->Value(i);
    }
    else {
      // Knot not unique, increase multiplicity
      Standard_Integer curMult = UMult.Value(pos);
      UMult.SetValue(pos, curMult + aUMultiplicities->Value(i));
    }
  }
  const Standard_Integer NVKnots = BS->NbVMultiplicities();
  const Handle(TColStd_HArray1OfInteger)& aVMultiplicities = BS->VMultiplicities();
  const Handle(TColStd_HArray1OfReal)& aVKnots = BS->VKnots();
  
  // count number of unique vknots
  lastKnot = RealFirst();
  Standard_Integer NVKnotsUnique = 0;
  for (i=1; i<=NVKnots; i++) {
    if (aVKnots->Value(i) - lastKnot > Epsilon (Abs(lastKnot))) {
      NVKnotsUnique++;
      lastKnot = aVKnots->Value(i);
    }
  }
  
  // set vmultiplicities and vknots
  TColStd_Array1OfInteger VMult(1,NVKnotsUnique);
  TColStd_Array1OfReal KVn(1,NVKnotsUnique);
  pos = 1;
  lastKnot = aVKnots->Value(1);
  KVn.SetValue(1, aVKnots->Value(1));
  VMult.SetValue(1, aVMultiplicities->Value(1));
  for (i=2; i<=NVKnots; i++) {
    if (aVKnots->Value(i) - lastKnot > Epsilon (Abs(lastKnot))) {
      pos++;
      KVn.SetValue(pos, aVKnots->Value(i));
      VMult.SetValue(pos, aVMultiplicities->Value(i));
      lastKnot = aVKnots->Value(i);
    }
    else {
      // Knot not unique, increase multiplicity
      Standard_Integer curMult = VMult.Value(pos);
      VMult.SetValue(pos, curMult + aVMultiplicities->Value(i));
    }
  }
  
  // --- Does the Surface Descriptor LOOKS like a U and/or V Periodic ---
  // --- Descriptor ? ---
  
  // --- U Periodic ? ---
  
  Standard_Integer SumMult = 0;
  for (i=1; i<=NUKnotsUnique; i++) {
    SumMult += UMult.Value(i);
  }
  
  Standard_Boolean shouldBeUPeriodic = Standard_False;
  if (SumMult == (NUPoles + UDeg + 1)) {
    //shouldBeUPeriodic = Standard_False;
  }
  else if ((UMult.Value(1) == 
	    UMult.Value(NUKnotsUnique)) &&
	   ((SumMult - UMult.Value(1))== NUPoles)) {
    shouldBeUPeriodic = Standard_True;
  }
  
  // --- V Periodic ? ---
  
  SumMult = 0;
  for (i=1; i<=NVKnotsUnique; i++) {
    SumMult += VMult.Value(i);
  }
  
  Standard_Boolean shouldBeVPeriodic = Standard_False;
  if (SumMult == (NVPoles + VDeg + 1)) {
    //shouldBeVPeriodic = Standard_False;
  }
  else if ((VMult.Value(1) == 
	    VMult.Value(NVKnotsUnique)) &&
	   ((SumMult - VMult.Value(1)) == NVPoles)) {
    shouldBeVPeriodic = Standard_True;
  }
  
  if (SS->IsKind(STANDARD_TYPE(StepGeom_BSplineSurfaceWithKnotsAndRationalBSplineSurface))) {
    const Handle(TColStd_HArray2OfReal)& aWeight = BSR->WeightsData();
    TColStd_Array2OfReal W(1,NUPoles,1,NVPoles);
    for (i=1; i<=NUPoles; i++) {
      for (j=1; j<=NVPoles; j++) {
        W.SetValue(i,j,aWeight->Value(i,j));
      }
    }
    CS = new Geom_BSplineSurface(Poles, W, KUn, KVn, UMult,
                                 VMult, UDeg, VDeg,
                                 shouldBeUPeriodic,
                                 shouldBeVPeriodic);
  }
  else
    CS = new Geom_BSplineSurface(Poles, KUn, KVn, UMult,
                                 VMult, UDeg, VDeg,
                                 shouldBeUPeriodic,
                                 shouldBeVPeriodic);
  return Standard_True;
}
