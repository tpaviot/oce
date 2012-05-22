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


//  Modified by skv - Thu Jul  7 14:37:05 2005 OCC9134

#include <Extrema_ExtElCS.ixx>
#include <Extrema_ExtPElS.hxx>
#include <Extrema_ExtPElC.hxx>
#include <Extrema_ExtElC.hxx>
#include <Extrema_POnCurv.hxx>
#include <Standard_NotImplemented.hxx>
#include <StdFail_InfiniteSolutions.hxx>
#include <Precision.hxx>
#include <ElSLib.hxx>
#include <ElCLib.hxx>
#include <gp_Vec.hxx>
#include <IntAna_Quadric.hxx>
#include <IntAna_IntConicQuad.hxx>


Extrema_ExtElCS::Extrema_ExtElCS() 
{
  myDone = Standard_False;
  myIsPar = Standard_False;
}


Extrema_ExtElCS::Extrema_ExtElCS(const gp_Lin& C,
				 const gp_Pln& S)
{
  Perform(C, S);
}



void Extrema_ExtElCS::Perform(const gp_Lin& C,
			      const gp_Pln& S)
{
  myDone = Standard_True;
  myIsPar = Standard_False;

  if (C.Direction().IsNormal(S.Axis().Direction(), 
			     Precision::Angular())) {
    mySqDist = new TColStd_HArray1OfReal(1, 1);
    mySqDist->SetValue(1, S.SquareDistance(C));
    myIsPar = Standard_True;
  }
  else {
    myNbExt = 0;
  }
  
}


Extrema_ExtElCS::Extrema_ExtElCS(const gp_Lin& C,
				 const gp_Cylinder& S)
{
  Perform(C, S);
}



void Extrema_ExtElCS::Perform(const gp_Lin& C,
			      const gp_Cylinder& S)
{
  myDone = Standard_False;
  myNbExt = 0;
  myIsPar = Standard_False;

  gp_Ax3 Pos = S.Position();
  gp_Pnt Origin = Pos.Location();
  gp_Pnt LineOrig = C.Location();

  Standard_Real radius = S.Radius();
  Extrema_ExtElC Extrem(gp_Lin(Pos.Axis()), C, Precision::Angular());
  if (Extrem.IsParallel()) {
    mySqDist = new TColStd_HArray1OfReal(1, 1);
    myPoint1 = new Extrema_HArray1OfPOnCurv(1, 1);
    myPoint2 = new Extrema_HArray1OfPOnSurf(1, 1);
    Standard_Real aDist = sqrt(Extrem.SquareDistance(1)) - radius;
    mySqDist->SetValue(1, aDist * aDist);
    Standard_Real u, v, w;
    gp_Vec aVec(LineOrig, Origin);
    gp_Vec aDirVec(C.Direction());
    w = aVec*aDirVec;
    gp_Pnt LinPoint = LineOrig.Translated(w * aDirVec);
    Extrema_POnCurv PonC(w, LinPoint);
    myPoint1->SetValue(1, PonC);
    gp_Pnt CylPoint;
    gp_Vec OrigToLine(Origin, LinPoint);
    if (OrigToLine.Magnitude() <= gp::Resolution())
    {
      u = 0.;
      v = 0.;
      CylPoint = ElSLib::Value(u, v, S);
    }
    else
    {
      OrigToLine.Normalize();
      CylPoint = Origin.Translated(radius * OrigToLine);
      ElSLib::CylinderParameters(Pos, radius, CylPoint, u, v);
    }
    Extrema_POnSurf PonS(u, v, CylPoint);
    myPoint2->SetValue(1, PonS);
    myDone = Standard_True;
    myIsPar = Standard_True;
  }
  else {
    Standard_Integer i;
    
    Extrema_POnCurv myPOnC1, myPOnC2;
    Extrem.Points(1, myPOnC1, myPOnC2);
    gp_Pnt PonAxis = myPOnC1.Value();
    gp_Pnt PC = myPOnC2.Value();

    // line is tangent or outside of the cylunder -- single solution
    if (radius - PonAxis.Distance(PC) < Precision::PConfusion())
    {
      Extrema_ExtPElS ExPS(PC, S, Precision::Confusion());
      if (ExPS.IsDone()) {
        myNbExt = ExPS.NbExt();
        mySqDist = new TColStd_HArray1OfReal(1, myNbExt);
        myPoint1 = new Extrema_HArray1OfPOnCurv(1, myNbExt);
        myPoint2 = new Extrema_HArray1OfPOnSurf(1, myNbExt);
        for (i = 1; i <= myNbExt; i++) {
          myPoint1->SetValue(i, myPOnC2);
          myPoint2->SetValue(i, ExPS.Point(i));
          mySqDist->SetValue(i,(myPOnC2.Value()).SquareDistance(ExPS.Point(i).Value()));
        }
      }
    }
    // line intersects the cylinder
    else
    {
      IntAna_Quadric theQuadric(S);
      IntAna_IntConicQuad Inters(C, theQuadric);
      if (Inters.IsDone())
      {
        myNbExt = Inters.NbPoints();
        if (myNbExt > 0)
        {
          mySqDist = new TColStd_HArray1OfReal(1, myNbExt);
          myPoint1 = new Extrema_HArray1OfPOnCurv(1, myNbExt);
          myPoint2 = new Extrema_HArray1OfPOnSurf(1, myNbExt);
          Standard_Real u, v, w;
          for (i = 1; i <= myNbExt; i++)
          {
            mySqDist->SetValue(i, 0.);
            gp_Pnt P_int = Inters.Point(i);
            w = Inters.ParamOnConic(i);
            Extrema_POnCurv PonC(w, P_int);
            myPoint1->SetValue(i, PonC);
            ElSLib::CylinderParameters(Pos, radius, P_int, u, v);
            Extrema_POnSurf PonS(u, v, P_int);
            myPoint2->SetValue(i, PonS);
          }
        }
      }
    }
    myDone = Standard_True;
  }

}



Extrema_ExtElCS::Extrema_ExtElCS(const gp_Lin& C,
				 const gp_Cone& S)
{
  Perform(C, S);
}



//void Extrema_ExtElCS::Perform(const gp_Lin& C,
//			      const gp_Cone& S)
void Extrema_ExtElCS::Perform(const gp_Lin& ,
			      const gp_Cone& )
{
  Standard_NotImplemented::Raise();

}



Extrema_ExtElCS::Extrema_ExtElCS(const gp_Lin& C,
				 const gp_Sphere& S)
{
  Perform(C, S);
}



void Extrema_ExtElCS::Perform(const gp_Lin& C,
			      const gp_Sphere& S)
{
  myDone = Standard_False;
  myNbExt = 0;
  myIsPar = Standard_False;

  gp_Pnt O = S.Location();

  Extrema_ExtPElC Extrem(O, C, Precision::Angular(), RealFirst(), RealLast());

  Standard_Integer i;
  if (Extrem.IsDone()) {
    Extrema_POnCurv myPOnC1 =  Extrem.Point(1);
    Extrema_ExtPElS ExPS(myPOnC1.Value(), S, Precision::Confusion());
    if (ExPS.IsDone()) {
      myNbExt = ExPS.NbExt();
      mySqDist = new TColStd_HArray1OfReal(1, myNbExt);
      myPoint1 = new Extrema_HArray1OfPOnCurv(1, myNbExt);
      myPoint2 = new Extrema_HArray1OfPOnSurf(1, myNbExt);
      for (i = 1; i <= myNbExt; i++) {
	myPoint1->SetValue(i, myPOnC1);
	myPoint2->SetValue(i, ExPS.Point(i));
	mySqDist->SetValue(i,(myPOnC1.Value()).SquareDistance(ExPS.Point(i).Value()));
	myDone = Standard_True;
      }
    }
  }
}


Extrema_ExtElCS::Extrema_ExtElCS(const gp_Lin& C,
				 const gp_Torus& S)
{
  Perform(C, S);
}



//void Extrema_ExtElCS::Perform(const gp_Lin& C,
//			      const gp_Torus& S)
void Extrema_ExtElCS::Perform(const gp_Lin& ,
			      const gp_Torus& )
{
  Standard_NotImplemented::Raise();

}


//        Circle-?

Extrema_ExtElCS::Extrema_ExtElCS(const gp_Circ& C,
				 const gp_Pln& S)
{
  Perform(C, S);
}



//void Extrema_ExtElCS::Perform(const gp_Circ& C,
//			      const gp_Pln& S)
void Extrema_ExtElCS::Perform(const gp_Circ& ,
			      const gp_Pln& )
{
  Standard_NotImplemented::Raise();

}



Extrema_ExtElCS::Extrema_ExtElCS(const gp_Circ& C,
				 const gp_Cylinder& S)
{
  Perform(C, S);
}



//  Modified by skv - Thu Jul  7 14:37:05 2005 OCC9134 Begin
// Implementation of the method.
void Extrema_ExtElCS::Perform(const gp_Circ& C,
			      const gp_Cylinder& S)
{
  myDone  = Standard_False;
  myIsPar = Standard_False;
  myNbExt = 0;

  // Get an axis line of the cylinder.
  gp_Lin anAxis(S.Axis());

  // Compute extrema between the circle and the line.
  Extrema_ExtElC anExtC(anAxis, C, 0.);

  if (anExtC.IsDone()) {
    if (anExtC.IsParallel()) {
      myIsPar =     Standard_True;
      mySqDist = new TColStd_HArray1OfReal(1, 1);
      Standard_Real aDist = sqrt (anExtC.SquareDistance(1)) - S.Radius();
      mySqDist->SetValue(1, aDist * aDist);
    } else {
      Standard_Integer aNbExt   = anExtC.NbExt();
      gp_Pnt           aCenter  = C.Location();
      Standard_Integer i;
      Standard_Integer aCurI    = 1;
      Standard_Real    aTolConf = Precision::Confusion();
      Standard_Real    aCylRad  = S.Radius();

      // Compute the extremas.
      myNbExt  =     2*aNbExt;
      mySqDist  = new TColStd_HArray1OfReal(1, myNbExt);
      myPoint1 = new Extrema_HArray1OfPOnCurv(1, myNbExt);
      myPoint2 = new Extrema_HArray1OfPOnSurf(1, myNbExt);

      for (i = 1; i <= aNbExt; i++) {
	Extrema_POnCurv aPOnAxis;
	Extrema_POnCurv aPOnCirc;
	Standard_Real   aSqDist = anExtC.SquareDistance(i);
	Standard_Real   aDist = sqrt (aSqDist);

	anExtC.Points(i, aPOnAxis, aPOnCirc);

	if (aSqDist <= (aTolConf * aTolConf) || aCenter.IsEqual(aPOnAxis.Value(), aTolConf)) {
	  myNbExt -= 2;
	  continue;
	}

	gp_Dir           aDir(aPOnAxis.Value().XYZ().
			      Subtracted(aPOnCirc.Value().XYZ()));
	Standard_Real    aShift[2] = { aDist + aCylRad, aDist - aCylRad };
	Standard_Integer j;

	for (j = 0; j < 2; j++) {
	  gp_Vec aVec(aDir);
	  gp_Pnt aPntOnCyl;

	  aVec.Multiply(aShift[j]);
	  aPntOnCyl = aPOnCirc.Value().Translated(aVec);

	  Standard_Real aU;
	  Standard_Real aV;

	  ElSLib::Parameters(S, aPntOnCyl, aU, aV);

	  Extrema_POnSurf aPOnSurf(aU, aV, aPntOnCyl);

	  myPoint1->SetValue(aCurI, aPOnCirc);
	  myPoint2->SetValue(aCurI, aPOnSurf);
	  mySqDist->SetValue(aCurI++, aShift[j] * aShift[j]);
	}
      }
    }

    myDone = Standard_True;
  }
}
//  Modified by skv - Thu Jul  7 14:37:05 2005 OCC9134 End



Extrema_ExtElCS::Extrema_ExtElCS(const gp_Circ& C,
				 const gp_Cone& S)
{
  Perform(C, S);
}



//void Extrema_ExtElCS::Perform(const gp_Circ& C,
//			 const gp_Cone& S)
void Extrema_ExtElCS::Perform(const gp_Circ& ,
			 const gp_Cone& )
{
  Standard_NotImplemented::Raise();

}



Extrema_ExtElCS::Extrema_ExtElCS(const gp_Circ& C,
				 const gp_Sphere& S)
{
  Perform(C, S);
}



//void Extrema_ExtElCS::Perform(const gp_Circ& C,
//			      const gp_Sphere& S)
void Extrema_ExtElCS::Perform(const gp_Circ& ,
			      const gp_Sphere& )
{
  Standard_NotImplemented::Raise();

}

Extrema_ExtElCS::Extrema_ExtElCS(const gp_Circ& C,
				 const gp_Torus& S)
{
  Perform(C, S);
}



//void Extrema_ExtElCS::Perform(const gp_Circ& C,
//			      const gp_Torus& S)
void Extrema_ExtElCS::Perform(const gp_Circ& ,
			      const gp_Torus& )
{
  Standard_NotImplemented::Raise();

}

Extrema_ExtElCS::Extrema_ExtElCS(const gp_Hypr& C,
				 const gp_Pln& S)
{
  Perform(C, S);
}



void Extrema_ExtElCS::Perform(const gp_Hypr& C,
			      const gp_Pln& S)
{
  myDone = Standard_True;
  myIsPar = Standard_False;

  gp_Ax2 Pos = C.Position();
  gp_Dir NHypr = Pos.Direction();
  gp_Dir NPln = S.Axis().Direction();

  if (NHypr.IsParallel(NPln, Precision::Angular())) {

    mySqDist = new TColStd_HArray1OfReal(1, 1);
    mySqDist->SetValue(1, S.SquareDistance(C.Location()));
    myIsPar = Standard_True;

  }
  else {

    gp_Dir XDir = Pos.XDirection();
    gp_Dir YDir = Pos.YDirection();

    Standard_Real A = C.MinorRadius()*(NPln.Dot(YDir)); 
    Standard_Real B = C.MajorRadius()*(NPln.Dot(XDir)); 

    if(Abs(B) > Abs(A)) {
      Standard_Real T = -0.5 * Log((A+B)/(B-A));
      gp_Pnt Ph = ElCLib::HyperbolaValue(T, Pos, C.MajorRadius(), C.MinorRadius());
      Extrema_POnCurv PC(T, Ph);
      myPoint1 = new Extrema_HArray1OfPOnCurv(1,1);
      myPoint1->SetValue(1, PC);

      mySqDist = new TColStd_HArray1OfReal(1, 1);
      mySqDist->SetValue(1, S.SquareDistance(Ph));

      Standard_Real U, V;
      ElSLib::PlaneParameters(S.Position(), Ph, U, V);
      gp_Pnt Pp = ElSLib::PlaneValue(U, V, S.Position());
      Extrema_POnSurf PS(U, V, Pp);
      myPoint2 = new Extrema_HArray1OfPOnSurf(1,1);
      myPoint2->SetValue(1, PS);

      myNbExt = 1;
    }
    else {
      myNbExt = 0;
    }

  }
  
}


Standard_Boolean Extrema_ExtElCS::IsDone() const
{
  return myDone;
}


Standard_Integer Extrema_ExtElCS::NbExt() const
{
  if (myIsPar) StdFail_InfiniteSolutions::Raise();
  return myNbExt;
}

Standard_Real Extrema_ExtElCS::SquareDistance(const Standard_Integer N) const
{
  if (myIsPar && N != 1) StdFail_InfiniteSolutions::Raise();
  return mySqDist->Value(N);
}


void Extrema_ExtElCS::Points(const Standard_Integer N,
			     Extrema_POnCurv& P1,
			     Extrema_POnSurf& P2) const
{
  if (myIsPar) StdFail_InfiniteSolutions::Raise();
  P1 = myPoint1->Value(N);
  P2 = myPoint2->Value(N);
}


Standard_Boolean Extrema_ExtElCS::IsParallel() const
{
  return myIsPar;
}
