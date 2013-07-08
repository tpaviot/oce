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

#include <UnitsMethods.ixx>

#include <Geom_Plane.hxx>
#include <Geom_Surface.hxx>
#include <Geom_ConicalSurface.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Geom_SphericalSurface.hxx>
#include <Geom_ToroidalSurface.hxx>
#include <Geom_SurfaceOfRevolution.hxx>
#include <Geom2dConvert.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2d_Hyperbola.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_Parabola.hxx>
#include <gp.hxx>
#include <gp_GTrsf2d.hxx>
#include <gp_Trsf2d.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Dir2d.hxx>

static Standard_Real theLengthFactor     = 1.;
static Standard_Real thePlaneAngleFactor = 1.;
static Standard_Real theSolidAngleFactor = 1.;
static Standard_Boolean set3d            = Standard_True;

static Standard_Real FactRD = 1.;
static Standard_Real FactDR = 1.;

static Standard_Real theCasCadeLengthUnit = 1.; // abv 28 Feb 00

// ============================================================================
// Method :
// Purpose:
// ============================================================================

void UnitsMethods::InitializeFactors(const Standard_Real LengthFactor, const Standard_Real PlaneAngleFactor, const Standard_Real SolidAngleFactor)
{
  theLengthFactor     = LengthFactor;
  thePlaneAngleFactor = PlaneAngleFactor;
  theSolidAngleFactor = SolidAngleFactor;
  FactRD = 1./PlaneAngleFactor; 
  FactDR = PlaneAngleFactor;
}

// ============================================================================
// Method :
// Purpose:
// ============================================================================

Standard_Real UnitsMethods ::LengthFactor()
{
  return theLengthFactor;
}

// ============================================================================
// Method :
// Purpose:
// ============================================================================

Standard_Real UnitsMethods::PlaneAngleFactor()
{
  return thePlaneAngleFactor;
}

// ============================================================================
// Method :
// Purpose:
// ============================================================================

Standard_Real UnitsMethods::SolidAngleFactor()
{
  return theSolidAngleFactor;
}

// ============================================================================
// Method :
// Purpose:
// ============================================================================

void UnitsMethods::Set3dConversion(const Standard_Boolean B)
{
  set3d = B;
}

// ============================================================================
// Method :
// Purpose:
// ============================================================================

Standard_Boolean UnitsMethods::Convert3d()
{
  return set3d;
}


// ============================================================================
// Method :
// Purpose:
// ============================================================================

Handle(Geom2d_Curve) UnitsMethods::RadianToDegree
                                   (const Handle(Geom2d_Curve)  & theCurve2d,
				    const Handle(Geom_Surface)  & theSurf)
{
  Handle(Geom2d_Curve) aCurve2d = Handle(Geom2d_Curve)::DownCast(theCurve2d->Copy());
  Standard_Real uFact = 1.;
  Standard_Real vFact = 1.; 
  Standard_Real LengthFact  = 1. / UnitsMethods::LengthFactor();
  Standard_Real AngleFact  = FactRD;    // 180./PI;  pilotable
  
  gp_Pnt2d    Pt1;
  gp_XY       pXY;
  gp_GTrsf2d  tMatu , tMatv;
  
  //  theSurf is a CylindricalSurface or a ConicalSurface or
  //             a ToroidalSurface or a SphericalSurface or
  //             a SurfaceOfRevolution
  if (theSurf->IsKind(STANDARD_TYPE(Geom_SphericalSurface)) ||
      theSurf->IsKind(STANDARD_TYPE(Geom_ToroidalSurface))) {
    uFact = vFact = AngleFact;
  }
  else if (theSurf->IsKind(STANDARD_TYPE(Geom_CylindricalSurface))) {
    uFact = AngleFact;
    vFact = LengthFact;
  }
  else if ( theSurf->IsKind(STANDARD_TYPE(Geom_SurfaceOfRevolution))) {
    uFact = AngleFact;
  }
  else if (theSurf->IsKind(STANDARD_TYPE(Geom_ConicalSurface))) {
    Handle(Geom_ConicalSurface) conicS = 
      Handle(Geom_ConicalSurface)::DownCast(theSurf);
    Standard_Real semAng = conicS->SemiAngle();
    uFact = AngleFact;
    vFact = LengthFact * Cos(semAng);
  }
  else if (theSurf->IsKind(STANDARD_TYPE(Geom_Plane))) {
    uFact = vFact = LengthFact;
    if (aCurve2d->IsKind(STANDARD_TYPE(Geom2d_Circle)) ||
        aCurve2d->IsKind(STANDARD_TYPE(Geom2d_Ellipse))) {
      gp_Trsf2d aT;
      aT.SetScale (gp::Origin2d(), LengthFact);
      aCurve2d->Transform (aT);
      return aCurve2d;
    }
  }
  else {
//  debug
//    cout <<"UnitsMethods: SurfType = "<< aSurface->DynamicType();
    return aCurve2d;
  }

  if (aCurve2d->IsKind(STANDARD_TYPE(Geom2d_Line))) {
    Handle(Geom2d_Line) aLine2d = Handle(Geom2d_Line)::DownCast(aCurve2d);

    gp_Pnt2d myLoc = aLine2d->Location();
    gp_Dir2d myDir = aLine2d->Direction();

    gp_Pnt2d myNewLoc;
    myNewLoc.SetCoord(myLoc.X()*uFact, myLoc.Y()*vFact);

    gp_Dir2d myNewDir;
    myNewDir.SetCoord(myDir.X()*uFact, myDir.Y()*vFact);

    Handle(Geom2d_Line) myNewLine2d = Handle(Geom2d_Line)::DownCast(aLine2d->Copy());
    myNewLine2d->SetLocation(myNewLoc);
    myNewLine2d->SetDirection(myNewDir);

    return myNewLine2d;
  }
  else if (aCurve2d->IsKind(STANDARD_TYPE(Geom2d_Conic))) {
    if (aCurve2d->IsKind(STANDARD_TYPE(Geom2d_Circle)) ||
        aCurve2d->IsKind(STANDARD_TYPE(Geom2d_Ellipse))) {
      Handle(Geom2d_BSplineCurve) aBSpline2d = 
	Geom2dConvert::CurveToBSplineCurve(aCurve2d);
      aCurve2d = aBSpline2d;
    } 
    else if (aCurve2d->IsKind(STANDARD_TYPE(Geom2d_Parabola))) {
#ifdef DEBUG
      cout << "PCURVE of Parabola type in U or V Periodic Surface" << endl;
      cout << "Parameters Not transformed to Degree" << endl;
#endif
    }
    else if (aCurve2d->IsKind(STANDARD_TYPE(Geom2d_Hyperbola))) {
#ifdef DEBUG
      cout << "PCURVE of Hyperbola type in U or V Periodic Surface" << endl;
      cout << "Parameters Not transformed to Degree" << endl;
#endif
    }
    
  }
  
  // Compute affinity
  tMatu.SetAffinity(gp::OY2d(), uFact);
  tMatv.SetAffinity(gp::OX2d(), vFact);
  
  if (aCurve2d->IsKind(STANDARD_TYPE(Geom2d_BoundedCurve))) {
    if (aCurve2d->IsKind(STANDARD_TYPE(Geom2d_BSplineCurve))) {
      Handle(Geom2d_BSplineCurve) aBSpline2d = 
	Handle(Geom2d_BSplineCurve)::DownCast(aCurve2d);
      Handle(Geom2d_BSplineCurve) myNewBSpline2d = 
	Handle(Geom2d_BSplineCurve)::DownCast(aBSpline2d->Copy());
      Standard_Integer nbPol = aBSpline2d->NbPoles();
      for (Standard_Integer i = 1; i<=nbPol ; i++) {
	pXY = aBSpline2d->Pole(i).XY();
	tMatu.Transforms(pXY);
	tMatv.Transforms(pXY);
	Pt1.SetXY(pXY);
	myNewBSpline2d->SetPole(i, Pt1);
      }
      return myNewBSpline2d;
    }
    else {
#ifdef DEBUG
      cout << "PCURVE of Other Types of Bounded Curve in U or V Periodic Surface" << endl;
      cout << "Parameters Not transformed to Degree" << endl;
#endif
    }
  }
  return aCurve2d;
}

//=============================================================================
// DegreeToRadian: 1. Change definition of the pcurves according to Length
//                     Factor                  
//                  2. STEP cylinder, torus, cone and sphere are parametrized
//                     from 0 to 360 degree
//                     Then pcurves parameter have to be transformed 
//                     from DEGREE to RADIAN
//=============================================================================

Handle(Geom2d_Curve) UnitsMethods::DegreeToRadian
                             (const Handle(Geom2d_Curve) & thePcurve,
			      const Handle(Geom_Surface) & aSurface)
{
  Handle(Geom2d_Curve)  aPcurve = Handle(Geom2d_Curve)::DownCast(thePcurve->Copy());
  Standard_Real uFact       = 1.;
  Standard_Real vFact       = 1.; 
  Standard_Real LengthFact  = UnitsMethods::LengthFactor();
  Standard_Real AngleFact   = FactDR;  // PI/180.;  pilotable

  gp_Pnt2d    Pt1;
  gp_XY       pXY;
  gp_GTrsf2d  tMatu , tMatv;

  // What to change ??

  if (aSurface->IsKind(STANDARD_TYPE(Geom_SphericalSurface)) ||
      aSurface->IsKind(STANDARD_TYPE(Geom_ToroidalSurface))) {
    uFact = vFact = AngleFact;
  }
  else if (aSurface->IsKind(STANDARD_TYPE(Geom_CylindricalSurface))) {
    uFact = AngleFact;
    vFact = LengthFact;
  }
  else if ( aSurface->IsKind(STANDARD_TYPE(Geom_SurfaceOfRevolution))) {
    uFact = AngleFact;
  }
  else if (aSurface->IsKind(STANDARD_TYPE(Geom_ConicalSurface))) {
    Handle(Geom_ConicalSurface) conicS = 
      Handle(Geom_ConicalSurface)::DownCast(aSurface);
    Standard_Real semAng = conicS->SemiAngle();
    uFact = AngleFact;
    vFact = LengthFact / Cos(semAng);
  }
  else if (aSurface->IsKind(STANDARD_TYPE(Geom_Plane))) {
    uFact = vFact = LengthFact;
    if (aPcurve->IsKind(STANDARD_TYPE(Geom2d_Circle)) ||
        aPcurve->IsKind(STANDARD_TYPE(Geom2d_Ellipse))) {
      gp_Trsf2d aT;
      aT.SetScale (gp::Origin2d(), LengthFact);
      aPcurve->Transform (aT);
      return aPcurve;
    }
  }
  else {
//  debug
//    cout <<"UnitsMethods: SurfType = "<< aSurface->DynamicType();
    return aPcurve;
  }

  if (aPcurve->IsKind(STANDARD_TYPE(Geom2d_Conic))) {
    if (aPcurve->IsKind(STANDARD_TYPE(Geom2d_Circle)) || 
	aPcurve->IsKind(STANDARD_TYPE(Geom2d_Ellipse))) {
      Handle(Geom2d_BSplineCurve) aBSpline2d = 
	Geom2dConvert::CurveToBSplineCurve(aPcurve);
      aPcurve = aBSpline2d;
    }
    else if (aPcurve->IsKind(STANDARD_TYPE(Geom2d_Parabola))) {
#ifdef DEBUG
      cout << "PCURVE of Parabola type" << endl;
      cout << "Parameters Not Yet transformed according to LenghtUnit" << endl;
#endif
      return aPcurve;
    }
    else if (aPcurve->IsKind(STANDARD_TYPE(Geom2d_Hyperbola))) {
#ifdef DEBUG
      cout << "PCURVE of Hyperbola type" << endl;
      cout << "Parameters Not Yet transformed according to LenghtUnit" << endl;
#endif
      return aPcurve;
    }
  }

  // Compute affinity

  tMatu.SetAffinity(gp::OY2d(), uFact);
  tMatv.SetAffinity(gp::OX2d(), vFact);

  if (aPcurve->IsKind(STANDARD_TYPE(Geom2d_Line))) {
    Handle(Geom2d_Line) aLine2d = Handle(Geom2d_Line)::DownCast(aPcurve);

    gp_Pnt2d myLoc = aLine2d->Location();
    gp_Dir2d myDir = aLine2d->Direction();

    gp_Pnt2d myNewLoc;
    myNewLoc.SetCoord(myLoc.X()*uFact, myLoc.Y()*vFact);

    gp_Dir2d myNewDir;
    myNewDir.SetCoord(myDir.X()*uFact, myDir.Y()*vFact);

    aLine2d->SetLocation(myNewLoc);
    aLine2d->SetDirection(myNewDir);

    aPcurve = aLine2d;
  }
  else if (aPcurve->IsKind(STANDARD_TYPE(Geom2d_BSplineCurve))) {
    Handle(Geom2d_BSplineCurve) aBSpline2d = 
      Handle(Geom2d_BSplineCurve)::DownCast(aPcurve);

// transform the Poles of the BSplineCurve according to AngleFact and LengthFact

    Standard_Integer nbPol = aBSpline2d->NbPoles();
    for (Standard_Integer i = 1; i<=nbPol ; i++) {
      pXY = aBSpline2d->Pole(i).XY();
      tMatu.Transforms(pXY);
      tMatv.Transforms(pXY);
      Pt1.SetXY(pXY);
      aBSpline2d->SetPole(i, Pt1);
    }
    aPcurve = aBSpline2d;
  }
  else {
#ifdef DEBUG
    cout << "DegreeToRadian : Type " << aPcurve->DynamicType();
    cout << " not yet implemented" << endl;
#endif
  }
  return aPcurve;
}

// ============================================================================
// Method :
// Purpose:
// ============================================================================

Handle(Geom2d_Curve) UnitsMethods::MirrorPCurve
(const Handle(Geom2d_Curve) & C2d) 
{
  Handle(Geom2d_Curve) theMirrored = 
    Handle(Geom2d_Curve)::DownCast(C2d->Copy());
  
  gp_Trsf2d T;
  gp_Pnt2d  Loc(0.,0.);
  gp_Dir2d  Dir(1.,0.);
  gp_Ax2d   ax2(Loc, Dir);
  T.SetMirror(ax2);
  theMirrored->Transform(T);
  return theMirrored;
}

//=======================================================================
//function : GetCasCadeLengthUnit
//purpose  : 
//=======================================================================

Standard_Real UnitsMethods::GetCasCadeLengthUnit () 
{
  return theCasCadeLengthUnit;
}

//=======================================================================
//function : SetCasCadeLengthUnit
//purpose  : 
//=======================================================================

void UnitsMethods::SetCasCadeLengthUnit (const Standard_Integer unit) 
{
  theCasCadeLengthUnit = UnitsMethods::GetLengthFactorValue ( unit );
}

//=======================================================================
//function : GetLengthFactorValue
//purpose  : 
//=======================================================================

Standard_Real UnitsMethods::GetLengthFactorValue (const Standard_Integer par) 
{
  switch ( par ) {
  case  1 : return 25.4;
  case  2 : return 1.;
  
  case  4 : return 304.8;
  case  5 : return 1609270.;
  case  6 : return 1000.;
  case  7 : return 1000000.;
  case  8 : return 0.0254;
  case  9 : return 0.001;
  case 10 : return 10.;
  case 11 : return 0.0000254;
  default : return 1.;
  }
}

