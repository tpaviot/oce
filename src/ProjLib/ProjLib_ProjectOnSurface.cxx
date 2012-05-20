// Created on: 1994-09-15
// Created by: Bruno DUMORTIER
// Copyright (c) 1994-1999 Matra Datavision
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


#include <ProjLib_ProjectOnSurface.ixx>

#include <AppCont_Function.hxx>
#include <Approx_FitAndDivide.hxx>
#include <AppParCurves_MultiCurve.hxx>
#include <Standard_NoSuchObject.hxx>
#include <Extrema_POnSurf.hxx>
#include <Precision.hxx>
#include <BSplCLib.hxx>
#include <PLib.hxx>
#include <Adaptor3d_HCurve.hxx>
#include <Handle_Adaptor3d_HCurve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Handle_Geom_BSplineCurve.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <Extrema_ExtPS.hxx>


//=======================================================================
//function : OnSurface_Value
//purpose  : Evaluate current point of the projected curve
//=======================================================================

static gp_Pnt OnSurface_Value(const Standard_Real U,
			      const Handle(Adaptor3d_HCurve)& myCurve,
			      Extrema_ExtPS * myExtPS)
{
  // on essaie de rendre le point solution le plus proche.
  myExtPS->Perform(myCurve->Value(U));
  
  Standard_Real Dist2Min = RealLast();
  Standard_Integer Index = 0;
  
  for ( Standard_Integer i = 1; i <= myExtPS->NbExt(); i++) {
    if ( myExtPS->SquareDistance(i) < Dist2Min) {
      Index = i;
      Dist2Min = myExtPS->SquareDistance(Index);
    }
  }
  if ( Index == 0 ) {
    cout << " Extrema non trouve pour U = " << U << endl;
    return gp_Pnt(0.,0.,0.);
  }
  else {
    return (myExtPS->Point(Index)).Value();
  }
}

//=======================================================================
//function : OnSurface_D1
//purpose  : 
//=======================================================================

static Standard_Boolean OnSurface_D1(const Standard_Real , // U,
				     gp_Pnt& ,       // P,
				     gp_Vec&       , // V,
				     const  Handle(Adaptor3d_HCurve)& , //  myCurve,
				     Extrema_ExtPS *) // myExtPS)
{
  return Standard_False;
}


//=======================================================================
//  class  : ProjLib_OnSurface
//purpose  : Use to approximate the projection on a plane
//=======================================================================

class ProjLib_OnSurface : public AppCont_Function

{
  Handle(Adaptor3d_HCurve)       myCurve;
  Extrema_ExtPS *myExtPS;

  public :

  ProjLib_OnSurface(const Handle(Adaptor3d_HCurve)   & C, 
		    const Handle(Adaptor3d_HSurface) & S)
    : myCurve(C)
      {Standard_Real U = myCurve->FirstParameter();
       gp_Pnt P = myCurve->Value(U);
       Standard_Real Tol = Precision::PConfusion();
       myExtPS = new Extrema_ExtPS(P,S->Surface(),Tol,Tol);}

  ~ProjLib_OnSurface() { delete myExtPS; }

  Standard_Real FirstParameter() const
    {return myCurve->FirstParameter();}
  
  Standard_Real LastParameter() const
    {return myCurve->LastParameter();}

  gp_Pnt Value( const Standard_Real t) const
    {return OnSurface_Value(t,myCurve,myExtPS);}

  Standard_Boolean D1(const Standard_Real t, gp_Pnt& P, gp_Vec& V) const
    {return OnSurface_D1(t,P,V,myCurve,myExtPS);}
};
  



//=====================================================================//
//                                                                     //
//  D E S C R I P T I O N   O F   T H E   C L A S S  :                 // 
//                                                                     //
//         P r o j L i b _ A p p r o x P r o j e c t O n P l a n e     //
//                                                                     //
//=====================================================================//


//=======================================================================
//function : ProjLib_ProjectOnSurface
//purpose  : 
//=======================================================================

ProjLib_ProjectOnSurface::ProjLib_ProjectOnSurface() :
myIsDone(Standard_False) 
{
}

//=======================================================================
//function : ProjLib_ProjectOnSurface
//purpose  : 
//=======================================================================

ProjLib_ProjectOnSurface::ProjLib_ProjectOnSurface
(const Handle(Adaptor3d_HSurface)& S ) :
myIsDone(Standard_False) 
{
  mySurface = S;
}

void ProjLib_ProjectOnSurface::Load(const Handle(Adaptor3d_HCurve)& C,
				    const Standard_Real  Tolerance) 
{
  myTolerance = Tolerance ;
  myCurve = C;
  myIsDone = Standard_False ; 
  if (!mySurface.IsNull()) { 
      
    ProjLib_OnSurface F(myCurve, mySurface);

    Standard_Integer Deg1, Deg2;
    Deg1 = 8; Deg2 = 8;
    
    Approx_FitAndDivide Fit(F,Deg1,Deg2,Precision::Approximation(),
			    Precision::PApproximation(),Standard_True);
    Standard_Integer i;
    Standard_Integer NbCurves = Fit.NbMultiCurves();
    Standard_Integer MaxDeg = 0;
    
    // Pour transformer la MultiCurve en BSpline, il faut que toutes 
    // les Bezier la constituant aient le meme degre -> Calcul de MaxDeg
    Standard_Integer NbPoles  = 1;
    for (i = 1; i <= NbCurves; i++) {
      Standard_Integer Deg = Fit.Value(i).Degree();
      MaxDeg = Max ( MaxDeg, Deg);
    }
    NbPoles = MaxDeg * NbCurves + 1;               //Poles sur la BSpline
    TColgp_Array1OfPnt  Poles( 1, NbPoles);
    
    TColgp_Array1OfPnt TempPoles( 1, MaxDeg + 1);  //pour augmentation du degre
    
    TColStd_Array1OfReal Knots( 1, NbCurves + 1);  //Noeuds de la BSpline
    
    Standard_Integer Compt = 1;
    for (i = 1; i <= Fit.NbMultiCurves(); i++) {
      Fit.Parameters(i, Knots(i), Knots(i+1)); 
      
      AppParCurves_MultiCurve MC = Fit.Value( i);   //Charge la Ieme Curve
      TColgp_Array1OfPnt LocalPoles( 1, MC.Degree() + 1);//Recupere les poles
      MC.Curve(1, Poles);
      
      //Augmentation eventuelle du degre
      Standard_Integer Inc = MaxDeg - MC.Degree();
      if ( Inc > 0) {
	BSplCLib::IncreaseDegree( Inc, LocalPoles, PLib::NoWeights(),
				 TempPoles, PLib::NoWeights());
	  //mise a jour des poles de la PCurve
	  for (Standard_Integer j = 1 ; j <= MaxDeg + 1; j++) {
	    Poles.SetValue( Compt, TempPoles( j));
	    Compt++;
	  }
	}
      else {
	//mise a jour des poles de la PCurve
	for (Standard_Integer j = 1 ; j <= MaxDeg + 1; j++) {
	  Poles.SetValue( Compt, LocalPoles( j));
	  Compt++;
	}
      } 
      
      Compt--;
    }
    
    //mise a jour des fields de ProjLib_Approx
    
    Standard_Integer NbKnots = NbCurves + 1;
    
    TColStd_Array1OfInteger  Mults( 1, NbKnots);
    Mults.SetValue( 1, MaxDeg + 1);
    for ( i = 2; i <= NbCurves; i++) {
      Mults.SetValue( i, MaxDeg);
    }
    Mults.SetValue(NbKnots, MaxDeg + 1);
    myResult = 
      new Geom_BSplineCurve(Poles,
			    Knots,
			    Mults,
			    MaxDeg,
			    Standard_False) ;
    myIsDone = Standard_True ;
  }
}

void ProjLib_ProjectOnSurface::Delete()
{}

//=======================================================================
//function : BSpline
//purpose  : 
//=======================================================================

Handle(Geom_BSplineCurve) ProjLib_ProjectOnSurface::BSpline() const 
{
  Standard_NoSuchObject_Raise_if
    (!myIsDone,
     "ProjLib_ProjectOnSurface:BSpline");
  return myResult ;
}

//=======================================================================
//function : IsDone
//purpose  : 
//=======================================================================

Standard_Boolean ProjLib_ProjectOnSurface::IsDone() const 
{
  return myIsDone;
}
