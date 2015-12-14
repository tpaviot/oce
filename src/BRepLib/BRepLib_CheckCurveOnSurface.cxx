// Created by: Eugeny MALTCHIKOV
// Copyright (c) 2014 OPEN CASCADE SAS
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

#include <BRepLib_CheckCurveOnSurface.ixx>

#include <Adaptor2d_HCurve2d.hxx>
#include <Adaptor3d_CurveOnSurface.hxx>
#include <Adaptor3d_HSurface.hxx>

#include <BRep_Tool.hxx>

#include <Geom2dAdaptor.hxx>
#include <Geom2dAdaptor_GHCurve.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <GeomAdaptor_HCurve.hxx>
#include <GeomAdaptor_HSurface.hxx>

#include <GeomProjLib.hxx>

#include <Geom_BSplineCurve.hxx>

#include <Geom_Plane.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom_TrimmedCurve.hxx>

#include <NCollection_Array1.hxx>

#include <OSD_Parallel.hxx>

#include <ProjLib_ProjectedCurve.hxx>

#include <Standard_ErrorHandler.hxx>

#include <TColStd_Array1OfReal.hxx>
#include <TopoDS.hxx>

#include <math_Matrix.hxx>
#include <math_MultipleVarFunctionWithHessian.hxx>
#include <math_NewtonMinimum.hxx>
#include <math_PSO.hxx>
#include <math_PSOParticlesPool.hxx>

class BRepLib_CheckCurveOnSurface_TargetFunc;

static 
Standard_Boolean MinComputing(
                BRepLib_CheckCurveOnSurface_TargetFunc& theFunction,
                const Standard_Real theEpsilon, //1.0e-3
                const Standard_Integer theNbParticles,
                Standard_Real& theBestValue,
                Standard_Real& theBestParameter);

static Standard_Integer FillSubIntervals( const Handle(Geom_Curve)& theCurve3d,
                                          const Handle(Geom2d_Curve)& theCurve2d,
                                          const Standard_Real theFirst,
                                          const Standard_Real theLast,
                                          Standard_Integer &theNbParticles,
                                          TColStd_Array1OfReal* const theSubIntervals = 0);

//=======================================================================
//class   : BRepLib_CheckCurveOnSurface_TargetFunc
//purpose : Target function (to be minimized)
//=======================================================================
class BRepLib_CheckCurveOnSurface_TargetFunc :
  public math_MultipleVarFunctionWithHessian
{
 public:
  BRepLib_CheckCurveOnSurface_TargetFunc( const Adaptor3d_Curve& theC3D,
                                          const Adaptor3d_Curve& theAdCS,
                                          const Standard_Real theFirst,
                                          const Standard_Real theLast):
  myCurve1(theC3D),
  myCurve2(theAdCS),
  myFirst(theFirst),
  myLast(theLast)
  {
  }
  
  //returns the number of parameters of the function
  //(the function is one-dimension).
  virtual Standard_Integer NbVariables() const {
    return 1;
  }
  
  //returns value of the function when parameters are equal to theX
  virtual Standard_Boolean Value(const math_Vector& theX,
                                 Standard_Real& theFVal)
  {
    return Value(theX(1), theFVal);
  }

  //returns value of the one-dimension-function when parameter
  //is equal to theX
  Standard_Boolean Value( const  Standard_Real theX,
                          Standard_Real& theFVal) const
  {
    try
    {
      OCC_CATCH_SIGNALS
      if (!CheckParameter(theX))
        return Standard_False;

      const gp_Pnt  aP1(myCurve1.Value(theX)),
                    aP2(myCurve2.Value(theX));
      
      theFVal = -1.0*aP1.SquareDistance(aP2);
    }
    catch(Standard_Failure) {
      return Standard_False;
    }
    //
    return Standard_True;
  }

  //see analogical method for abstract owner class math_MultipleVarFunction
  virtual Standard_Integer GetStateNumber()
  {
    return 0;
  }
  
  //returns the gradient of the function when parameters are
  //equal to theX
  virtual Standard_Boolean Gradient(const math_Vector& theX,
                                    math_Vector& theGrad)
  {
    return Derive(theX(1), theGrad(1));
  }

  //returns 1st derivative of the the one-dimension-function when
  //parameter is equal to theX
  Standard_Boolean Derive(const Standard_Real theX, Standard_Real& theDeriv) const
  {
    try
    {
      OCC_CATCH_SIGNALS
      if (!CheckParameter(theX))
      {
        return Standard_False;
      }
      //
      gp_Pnt aP1, aP2;
      gp_Vec aDC1, aDC2;
      //
      myCurve1.D1(theX, aP1, aDC1);
      myCurve2.D1(theX, aP2, aDC2);

      const gp_Vec aVec1(aP1, aP2), aVec2(aDC2-aDC1);
      //
      theDeriv = -2.0*aVec1.Dot(aVec2);
    }
    catch(Standard_Failure)
    {
      return Standard_False;
    }

    return Standard_True;
  }
  
  //returns value and gradient   
  virtual Standard_Boolean Values(const math_Vector& theX,
                                  Standard_Real& theVal,
                                  math_Vector& theGrad) 
  {
    if (!Value(theX, theVal))
    {
      return Standard_False;
    }
    //
    if (!Gradient(theX, theGrad)) {
      return Standard_False;
    }
    //
    return Standard_True;
  }

  //returns value, gradient and hessian
  virtual Standard_Boolean Values(const math_Vector& theX,
                                  Standard_Real& theVal,
                                  math_Vector& theGrad,
                                  math_Matrix& theHessian)
  {
    if (!Value(theX, theVal))
    {
      return Standard_False;
    }
    //
    if (!Gradient(theX, theGrad))
    {
      return Standard_False;
    }
    //
    theHessian(1,1) = theGrad(1);
    //
    return Standard_True;
  }
  //
  Standard_Real FirstParameter() const
  {
    return myFirst;
  }

  //
  Standard_Real LastParameter() const
  {
    return myLast;
  }
  
 private:
  BRepLib_CheckCurveOnSurface_TargetFunc operator=(BRepLib_CheckCurveOnSurface_TargetFunc&);

  //checks if the function can be computed when its parameter is
  //equal to theParam
   Standard_Boolean CheckParameter(const Standard_Real theParam) const
   {
     return ((myFirst <= theParam) && (theParam <= myLast));
   }

   const Adaptor3d_Curve& myCurve1;
   const Adaptor3d_Curve& myCurve2;
   const Standard_Real myFirst;
   const Standard_Real myLast;
};

//=======================================================================
//class   : BRepLib_CheckCurveOnSurface_Local
//purpose : Created for parallelization possibility only
//=======================================================================
class BRepLib_CheckCurveOnSurface_Local
{
public:
  BRepLib_CheckCurveOnSurface_Local(
              const Handle(Geom_Curve)& theCurve3D,
              const Handle(Geom2d_Curve)& theCurve2D,
              const Handle(Geom_Surface)& theSurface,
              const TColStd_Array1OfReal& theIntervalsArr,
              const Standard_Real theEpsilonRange,
              const Standard_Integer theNbParticles):
  myCurve3D(theCurve3D),
  myCurve2D(theCurve2D),
  mySurface(theSurface),
  mySubIntervals(theIntervalsArr),
  myEpsilonRange(theEpsilonRange),
  myNbParticles(theNbParticles),
  myArrOfDist(theIntervalsArr.Lower(), theIntervalsArr.Upper()-1),
  myArrOfParam(theIntervalsArr.Lower(), theIntervalsArr.Upper()-1)
  {
  }
  
  void operator()(const Standard_Integer& theIndex) const
  {
    //For every sub-interval (which is set by mySubIntervals array) this method
    //computes optimal value of BRepLib_CheckCurveOnSurface_TargetFunc function.
    //This optimal value will be put in corresponding (depending on theIndex - the
    //identificator of the current interval in mySubIntervals array) cell of 
    //myArrOfDist and myArrOfParam arrays.
    const GeomAdaptor_Curve anAC(myCurve3D);
    const Handle(Adaptor2d_HCurve2d) anAd2dC = new Geom2dAdaptor_GHCurve(myCurve2D);
    const Handle(Adaptor3d_HSurface) anAdS = new GeomAdaptor_HSurface(mySurface);

    const Adaptor3d_CurveOnSurface anACS(anAd2dC, anAdS);

    BRepLib_CheckCurveOnSurface_TargetFunc aFunc( anAC, anACS,
                                                  mySubIntervals.Value(theIndex),
                                                  mySubIntervals.Value(theIndex+1));

    Standard_Real aMinDist = RealLast(), aPar = 0.0;
    if(!MinComputing(aFunc, myEpsilonRange, myNbParticles, aMinDist, aPar))
    {
      myArrOfDist(theIndex) = RealLast();
      myArrOfParam(theIndex) = aFunc.FirstParameter();
      return;
    }

    myArrOfDist(theIndex) = aMinDist;
    myArrOfParam(theIndex) = aPar;
  }

  //Returns optimal value (inverse of square of maximal distance)
  void OptimalValues(Standard_Real& theMinimalValue, Standard_Real& theParameter) const
  {
    //This method looks for the minimal value of myArrOfDist.

    const Standard_Integer aStartInd = myArrOfDist.Lower();
    theMinimalValue = myArrOfDist(aStartInd);
    theParameter = myArrOfParam(aStartInd);
    for(Standard_Integer i = aStartInd + 1; i <= myArrOfDist.Upper(); i++)
    {
      if(myArrOfDist(i) < theMinimalValue)
      {
        theMinimalValue = myArrOfDist(i);
        theParameter = myArrOfParam(i);
      }
    }
  }

private:
  BRepLib_CheckCurveOnSurface_Local operator=(BRepLib_CheckCurveOnSurface_Local&);
  const Handle(Geom_Curve)& myCurve3D;
  const Handle(Geom2d_Curve)& myCurve2D;
  const Handle(Geom_Surface)& mySurface;

  const TColStd_Array1OfReal& mySubIntervals;
  const Standard_Real myEpsilonRange;
  const Standard_Integer myNbParticles;
  mutable NCollection_Array1<Standard_Real> myArrOfDist;
  mutable NCollection_Array1<Standard_Real> myArrOfParam;
};

//=======================================================================
//function : BRepLib_CheckCurveOnSurface
//purpose  : 
//=======================================================================
BRepLib_CheckCurveOnSurface::BRepLib_CheckCurveOnSurface()
:
  myFirst(0.),
  myLast(0.),
  myErrorStatus(0),
  myMaxDistance(RealLast()),
  myMaxParameter(0.)
{
}

//=======================================================================
//function : BRepLib_CheckCurveOnSurface
//purpose  : 
//=======================================================================
BRepLib_CheckCurveOnSurface::BRepLib_CheckCurveOnSurface
  (const TopoDS_Edge& theEdge,
   const TopoDS_Face& theFace)
:
  myErrorStatus(0),
  myMaxDistance(RealLast()),
  myMaxParameter(0.)
{
  Init(theEdge, theFace);
}

//=======================================================================
//function : BRepLib_CheckCurveOnSurface
//purpose  : 
//=======================================================================
BRepLib_CheckCurveOnSurface::BRepLib_CheckCurveOnSurface
  (const Handle(Geom_Curve)& the3DCurve,
   const Handle(Geom2d_Curve)& the2DCurve,
   const Handle(Geom_Surface)& theSurface,
   const Standard_Real theFirst,
   const Standard_Real theLast)
:
  myErrorStatus(0),
  myMaxDistance(RealLast()),
  myMaxParameter(0.)
{
  Init(the3DCurve, the2DCurve, theSurface, theFirst, theLast);
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================
void BRepLib_CheckCurveOnSurface::Init
  (const TopoDS_Edge& theEdge,
   const TopoDS_Face& theFace)
{
  myCurve.Nullify();
  myPCurve.Nullify();
  myPCurve2.Nullify();
  mySurface.Nullify();
  myErrorStatus = 0;
  myMaxDistance = RealLast();
  myMaxParameter = 0.0;
  myFirst = 0.0;
  myLast = 0.0;

  if (theEdge.IsNull() || theFace.IsNull()) {
    return;
  }
  //
  if (BRep_Tool::Degenerated(theEdge) ||
      !BRep_Tool::IsGeometric(theEdge)) {
    return;
  }
  //
  TopLoc_Location aLocE, aLocF, aLocC2D;
  //
  // 3D curve initialization
  const Handle(Geom_Curve)& aC = BRep_Tool::Curve(theEdge, aLocE, myFirst, myLast);
  myCurve = Handle(Geom_Curve)::DownCast(aC->Transformed(aLocE.Transformation()));

  // Surface initialization
  const Handle(Geom_Surface)& aS = BRep_Tool::Surface(theFace, aLocF);
  mySurface = Handle(Geom_Surface)::DownCast(aS->Transformed(aLocF.Transformation()));
  //
  // 2D curves initialization 
  myPCurve = BRep_Tool::CurveOnSurface(theEdge, theFace, myFirst, myLast);

  if(BRep_Tool::IsClosed(theEdge, theFace))
    myPCurve2 = BRep_Tool::CurveOnSurface(TopoDS::Edge(theEdge.Reversed()),
                                          theFace, myFirst, myLast);
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================
void BRepLib_CheckCurveOnSurface::Init
  (const Handle(Geom_Curve)& the3DCurve,
   const Handle(Geom2d_Curve)& the2DCurve,
   const Handle(Geom_Surface)& theSurface,
   const Standard_Real theFirst,
   const Standard_Real theLast)
{
  myCurve = the3DCurve;
  myPCurve = the2DCurve;
  myPCurve2.Nullify();
  mySurface = theSurface;
  myFirst = theFirst;
  myLast  = theLast;
  myErrorStatus = 0;
  myMaxDistance = RealLast();
  myMaxParameter = 0.0;
}

//=======================================================================
//function : Perform
//purpose  : if isTheMTDisabled == TRUE parallelization is not used
//=======================================================================
#ifndef HAVE_TBB
//After fixing bug # 26365, this fragment should be deleted
//(together the text "#ifdef HAVE_TBB")

void BRepLib_CheckCurveOnSurface::Perform(const Standard_Boolean)
{
  const Standard_Boolean isTheMTDisabled = Standard_True;
#else
void BRepLib_CheckCurveOnSurface::Perform(const Standard_Boolean isTheMTDisabled)
{
#endif
  try {
    OCC_CATCH_SIGNALS
    //
    // 1. Check data
    CheckData();
    if (myErrorStatus) {
      return;
    }

    // 2. Compute the max distance
    Compute(myPCurve, isTheMTDisabled);
    //
    if (!myPCurve2.IsNull()) {
      // compute max distance for myPCurve2
      // (for the second curve on closed surface)
      Compute(myPCurve2, isTheMTDisabled);
    }
  }
  catch (Standard_Failure) {
    myErrorStatus = 3;
  }
}

//=======================================================================
//function : Compute
//purpose  : if isTheMTDisabled == TRUE parallelization is not used
//=======================================================================
void BRepLib_CheckCurveOnSurface::Compute(const Handle(Geom2d_Curve)& thePCurve,
                                          const Standard_Boolean isTheMTDisabled)
{
  const Standard_Real anEpsilonRange = 1.e-3;

  Standard_Integer aNbParticles = 3;

  //Polynomial function with degree n has not more than n-1 maxima and
  //minima (degree of 1st derivative is equal to n-1 => 1st derivative has
  //no greater than n-1 roots). Consequently, this function has
  //maximum n monotonicity intervals. That is a good idea to try to put
  //at least one particle in every monotonicity interval. Therefore,
  //number of particles should be equal to n. 

  const Standard_Integer aNbSubIntervals = 
                              FillSubIntervals( myCurve, thePCurve,
                                                myFirst, myLast, aNbParticles);

  if(!aNbSubIntervals)
  {
    myErrorStatus = 3;
    return;
  }

  TColStd_Array1OfReal anIntervals(1, aNbSubIntervals+1);
  FillSubIntervals(myCurve, thePCurve, myFirst, myLast, aNbParticles, &anIntervals);

  BRepLib_CheckCurveOnSurface_Local aComp(myCurve, thePCurve,
                                mySurface, anIntervals, anEpsilonRange, aNbParticles);

  OSD_Parallel::For(anIntervals.Lower(), anIntervals.Upper(), aComp, isTheMTDisabled);

  aComp.OptimalValues(myMaxDistance, myMaxParameter);

  myMaxDistance = sqrt(Abs(myMaxDistance));
}

//=======================================================================
// Function : FillSubIntervals
// purpose : Divides [theFirst, theLast] interval on parts
//            in order to make searching-algorithm more precisely
//            (fills theSubIntervals array).
//            Returns number of subintervals.
//=======================================================================
Standard_Integer FillSubIntervals(const Handle(Geom_Curve)& theCurve3d,
                                  const Handle(Geom2d_Curve)& theCurve2d,
                                  const Standard_Real theFirst,
                                  const Standard_Real theLast,
                                  Standard_Integer &theNbParticles,
                                  TColStd_Array1OfReal* const theSubIntervals)
{
  const Standard_Real anArrTempC[2] = {theFirst, theLast};
  const TColStd_Array1OfReal anArrTemp(anArrTempC[0], 1, 2);

  theNbParticles = 3;
  Handle(Geom2d_BSplineCurve) aBS2DCurv;
  Handle(Geom_BSplineCurve) aBS3DCurv;

  //
  if (theCurve3d->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
  {
    aBS3DCurv = Handle(Geom_BSplineCurve)::
                      DownCast(Handle(Geom_TrimmedCurve)::
                      DownCast(theCurve3d)->BasisCurve());
  }
  else
  {
    aBS3DCurv = Handle(Geom_BSplineCurve)::DownCast(theCurve3d);
  }


  if (theCurve2d->IsKind(STANDARD_TYPE(Geom2d_TrimmedCurve)))
  {
    aBS2DCurv = Handle(Geom2d_BSplineCurve)::
                      DownCast(Handle(Geom2d_TrimmedCurve)::
                      DownCast(theCurve2d)->BasisCurve());
  }
  else
  {
    aBS2DCurv = Handle(Geom2d_BSplineCurve)::DownCast(theCurve2d);
  }

  const TColStd_Array1OfReal &anArrKnots3D = !aBS3DCurv.IsNull() ? 
                                              aBS3DCurv->Knots() :
                                              anArrTemp;
  const TColStd_Array1OfReal &anArrKnots2D = !aBS2DCurv.IsNull() ?
                                              aBS2DCurv->Knots() :
                                              anArrTemp;

  Standard_Integer aNbSubIntervals = 1;

  try
  {
    OCC_CATCH_SIGNALS
    const Standard_Integer  anIndMax3D = anArrKnots3D.Upper(),
                            anIndMax2D = anArrKnots2D.Upper();

    Standard_Integer  anIndex3D = anArrKnots3D.Lower(),
                      anIndex2D = anArrKnots2D.Lower();

    if(theSubIntervals)
      theSubIntervals->ChangeValue(aNbSubIntervals) = theFirst;

    while((anIndex3D <= anIndMax3D) && (anIndex2D <= anIndMax2D))
    {
      const Standard_Real aVal3D = anArrKnots3D.Value(anIndex3D),
                          aVal2D = anArrKnots2D.Value(anIndex2D);
      const Standard_Real aDelta = aVal3D - aVal2D;

      if(aDelta < Precision::PConfusion())
      {//aVal3D <= aVal2D
        if((aVal3D > theFirst) && (aVal3D < theLast))
        {
          aNbSubIntervals++;
        
          if(theSubIntervals)
            theSubIntervals->ChangeValue(aNbSubIntervals) = aVal3D;
        }

        anIndex3D++;

        if(-aDelta < Precision::PConfusion())
        {//aVal3D == aVal2D
          anIndex2D++;
        }
      }
      else
      {//aVal2D < aVal3D
        if((aVal2D > theFirst) && (aVal2D < theLast))
        {
          aNbSubIntervals++;
          
          if(theSubIntervals)
            theSubIntervals->ChangeValue(aNbSubIntervals) = aVal2D;
        }

        anIndex2D++;
      }
    }

    if(theSubIntervals)
      theSubIntervals->ChangeValue(aNbSubIntervals+1) = theLast;

    if(!aBS3DCurv.IsNull())
    {
      theNbParticles = Max(theNbParticles, aBS3DCurv->Degree());
    }

    if(!aBS2DCurv.IsNull())
    {
      theNbParticles = Max(theNbParticles, aBS2DCurv->Degree());
    }
  }
  catch(Standard_Failure)
  {
#ifdef OCCT_DEBUG
    cout << "ERROR! BRepLib_CheckCurveOnSurface.cxx, "
            "FillSubIntervals(): Incorrect filling!" << endl;
#endif

    aNbSubIntervals = 0;
  }

  return aNbSubIntervals;
}

//=======================================================================
//class   : MinComputing
//purpose : Performs computing minimal value
//=======================================================================
Standard_Boolean MinComputing (
                BRepLib_CheckCurveOnSurface_TargetFunc& theFunction,
                const Standard_Real theEpsilon, //1.0e-3
                const Standard_Integer theNbParticles,
                Standard_Real& theBestValue,
                Standard_Real& theBestParameter)
{
  try
  {
    OCC_CATCH_SIGNALS

    //They are used for finding a position of theNbParticles worst places
    const Standard_Integer aNbControlPoints = 3*theNbParticles;
    //
    math_Vector aParInf(1, 1), aParSup(1, 1), anOutputParam(1, 1), aStepPar(1,1);
    aParInf(1) = theFunction.FirstParameter();
    aParSup(1) = theFunction.LastParameter();
    theBestParameter = aParInf(1);
    theBestValue = RealLast();

    const Standard_Real aDeltaParam = aParSup(1) - aParInf(1);
    if(aDeltaParam < Precision::PConfusion())
        return Standard_False;

    aStepPar(1) = theEpsilon*aDeltaParam;

    math_PSOParticlesPool aParticles(theNbParticles, 1);

    const Standard_Real aStep = aDeltaParam/(aNbControlPoints-1);
    Standard_Integer aCount = 1;
    for(Standard_Real aPrm = aParInf(1); aCount <= aNbControlPoints; aCount++,
                      aPrm = (aCount == aNbControlPoints)? aParSup(1) : aPrm+aStep)
    {
      Standard_Real aVal = RealLast();
      theFunction.Value(aPrm, aVal);

      PSO_Particle* aParticle = aParticles.GetWorstParticle();

      if(aVal > aParticle->BestDistance)
        continue;

      aParticle->Position[0] = aPrm;
      aParticle->BestPosition[0] = aPrm;
      aParticle->Distance     = aVal;
      aParticle->BestDistance = aVal;
    }

    math_PSO aPSO(&theFunction, aParInf, aParSup, aStepPar);
    aPSO.Perform(aParticles, theNbParticles, theBestValue, anOutputParam);

    //Here, anOutputParam contains parameter, which is near to optimal.
    //It needs to be more precise. Precision is made by math_NewtonMinimum.
    math_NewtonMinimum anA(theFunction);
    anA.Perform(theFunction, anOutputParam);

    if(!anA.IsDone())
    {
#ifdef OCCT_DEBUG
      cout << "BRepLib_CheckCurveOnSurface::Compute(): No solution found!" << endl;
#endif
      return Standard_False;
    }

    anA.Location(anOutputParam);
    theBestParameter =  anOutputParam(1);
    theBestValue = anA.Minimum();
  }
  catch(Standard_Failure)
  {
#ifdef OCCT_DEBUG
    cout << "BRepLib_CheckCurveOnSurface.cxx: Exception in MinComputing()!" << endl;
#endif
    return Standard_False;
  }

  return Standard_True;
}
