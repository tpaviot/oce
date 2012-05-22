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


#include <Extrema_ExtPElS.ixx>
#include <StdFail_NotDone.hxx>
#include <Standard_OutOfRange.hxx>
#include <Standard_NotImplemented.hxx>
#include <ElSLib.hxx>
//=============================================================================

Extrema_ExtPElS::Extrema_ExtPElS () { myDone = Standard_False; }
//=============================================================================

Extrema_ExtPElS::Extrema_ExtPElS (const gp_Pnt& P, 
				  const gp_Cylinder& S,
				  const Standard_Real Tol)
{

 Perform(P, S, Tol);
}
/*-----------------------------------------------------------------------------
Function:
Find 2 extreme distances between point P and cylinder S.

Method:
  Let Pp be the projection of P in plane XOY of the cylinder;
  2 cases are considered:
  1- distance(Pp,O) < Tol:
     There are infinite solutions; IsDone() = Standard_False.
  2- distance(Pp,O) > Tol:
     let V = OP.OZ,
          U1 = angle(OX,OPp) with 0 < U1 < 2.*M_PI
	  U2 = U1 + M_PI with 0 < U2 < 2.*M_PI;
     then (U1,V) corresponds to the min distance.
     and  (U2,V) corresponds to the max distance.
-----------------------------------------------------------------------------*/

void Extrema_ExtPElS::Perform(const gp_Pnt&       P, 
			      const gp_Cylinder&  S,
			      const Standard_Real Tol)
{
  myDone = Standard_False;
  myNbExt = 0;

// Projection of point P in plane XOY of the cylinder ...
  gp_Ax3 Pos = S.Position();
  gp_Pnt O = Pos.Location();
  gp_Vec OZ (Pos.Direction());
  Standard_Real V = gp_Vec(O,P).Dot(OZ);
  gp_Pnt Pp = P.Translated(OZ.Multiplied(-V));

// Calculation of extrema
  gp_Vec OPp (O,Pp);
  if (OPp.Magnitude() < Tol) { return; }
  gp_Vec myZ = Pos.XDirection()^Pos.YDirection();
  Standard_Real U1 = gp_Vec(Pos.XDirection()).AngleWithRef(OPp,myZ); //-M_PI<U1<M_PI
  Standard_Real U2 = U1 + M_PI;
  if (U1 < 0.) { U1 += 2. * M_PI; }

  gp_Pnt Ps;
  Ps = ElSLib::Value(U1,V,S);
  mySqDist[0] = Ps.SquareDistance(P);
  myPoint[0] = Extrema_POnSurf(U1,V,Ps);
  Ps = ElSLib::Value(U2,V,S);
  mySqDist[1] = Ps.SquareDistance(P);
  myPoint[1] = Extrema_POnSurf(U2,V,Ps);

  myNbExt = 2;
  myDone = Standard_True;
}
//=============================================================================

Extrema_ExtPElS::Extrema_ExtPElS (const gp_Pnt&       P, 
				  const gp_Cone&      S,
				  const Standard_Real Tol)
{
  Perform(P, S, Tol);
}
/*-----------------------------------------------------------------------------
Function:
   Find 2 extreme distances between point P and cone S.

Method:
  Let M the top of the cone.
  2 cases are considered:
  1- distance(P,M) < Tol:
     there is a minimum in M.
  2- distance(P,M) > Tol:
     Let Pp the projection of P in the plane XOY of the cone;
     2 cases are considered:
     1- distance(Pp,O) < Tol:
     There is an infinite number of solutions; IsDone() = Standard_False.
     2- distance(Pp,O) > Tol:
        There exist 2 extrema:
        Let Vm = value of v for point M,
             Vp = value of v for point P,
             U1 = angle(OX,OPp) if Vp > Vm )
	         -angle(OX,OPp) otherwise      ) with 0. < U1 < 2*M_PI,
             U2 = U1 + M_PI with 0. < U2 < 2*M_PI;
        We are in plane PpOZ.
       Let A the angle of the cone,
             B = angle(MP,MO) with 0. < B < M_PI,
	     L = longueur(MP),
	     V1 = (L * cos(B-A)) + Vm,
	     V2 = (L * cos(B+A)) + Vm;
       then (U1,V1) and (U2,V2) correspond to min distances.
-----------------------------------------------------------------------------*/

void Extrema_ExtPElS::Perform(const gp_Pnt&       P, 
			      const gp_Cone&      S,
			      const Standard_Real Tol)
{
  myDone = Standard_False;
  myNbExt = 0;

  gp_Pnt M = S.Apex();
  gp_Ax3 Pos = S.Position();
  gp_Pnt O = Pos.Location();
  Standard_Real A = S.SemiAngle();
  gp_Vec OZ (Pos.Direction());
  gp_Vec myZ = Pos.XDirection()^Pos.YDirection();
  gp_Vec MP (M,P);

  Standard_Real L2 = MP.SquareMagnitude();
  Standard_Real Vm = -(S.RefRadius() / Sin(A));

// Case when P is mixed with S ...
  if (L2 < Tol * Tol) {
    mySqDist[0] = L2;
    myPoint[0] = Extrema_POnSurf(0.,Vm,M);
    myNbExt = 1;
    myDone = Standard_True;
    return;
  }
    gp_Vec DirZ;
    if (M.SquareDistance(O)<Tol * Tol) 
    { DirZ=OZ;
     if( A<0) DirZ.Multiplied(-1.);
    }
    else 
     DirZ=gp_Vec(M,O); 
// Projection of P in the reference plane of the cone ...
  Standard_Real Zp = gp_Vec(O, P).Dot(OZ);

  gp_Pnt Pp = P.Translated(OZ.Multiplied(-Zp));
  gp_Vec OPp(O, Pp);
  if (OPp.SquareMagnitude() < Tol * Tol) return;
  Standard_Real B, U1, V1, U2, V2;
  Standard_Boolean Same = DirZ.Dot(MP) >= 0.0;
  U1 = gp_Vec(Pos.XDirection()).AngleWithRef(OPp,myZ); //-M_PI<U1<M_PI
  B = MP.Angle(DirZ);
  if (!Same) { U1 += M_PI; }
  U2 = U1 + M_PI;
  if (U1 < 0.) { U1 += 2. * M_PI; }
  if (U2 > 2.*M_PI) { U2 -= 2. * M_PI; }
  B = MP.Angle(DirZ);
  A = Abs(A);
  Standard_Real L = sqrt(L2);
  if (!Same) {
    B = M_PI-B;
    V1 = -L*cos(B-A);
    V2 = -L*cos(B+A);
  }
  else {
    V1 = L * cos(B-A);
    V2 = L * cos(B+A);
  }
  Standard_Real Sense = OZ.Dot(gp_Dir(DirZ));
  V1 *= Sense;   V2 *= Sense;
  V1 += Vm;   V2 += Vm;

  gp_Pnt Ps;
  Ps = ElSLib::Value(U1,V1,S);
  mySqDist[0] = Ps.SquareDistance(P);
  myPoint[0] = Extrema_POnSurf(U1,V1,Ps);
  Ps = ElSLib::Value(U2,V2,S);
  mySqDist[1] = Ps.SquareDistance(P);
  myPoint[1] = Extrema_POnSurf(U2,V2,Ps);

  myNbExt = 2;
  myDone = Standard_True;
}
//=============================================================================

Extrema_ExtPElS::Extrema_ExtPElS (const gp_Pnt&       P, 
				  const gp_Sphere&    S,
				  const Standard_Real Tol)
{
  Perform(P, S, Tol);
}
/*-----------------------------------------------------------------------------
Function:
  Find 2 extreme distances between point P and sphere S.

Method:
   Let O be the origin of the sphere.
  2 cases are considered:
  1- distance(P,O) < Tol:
     There is an infinite number of solutions; IsDone() = Standard_False
  2- distance(P,O) > Tol:
     Let Pp be the projection of point P in the plane XOY of the sphere;
     2 cases are considered:
     1- distance(Pp,O) < Tol:
        2 solutions are: (0,-M_PI/2.) and (0.,M_PI/2.)
     2- distance(Pp,O) > Tol:
        Let U1 = angle(OX,OPp) with 0. < U1 < 2.*M_PI,
	     U2 = U1 + M_PI avec 0. < U2 < 2*M_PI,
	     V1 = angle(OPp,OP) with -M_PI/2. < V1 < M_PI/2. ,
	then (U1, V1) corresponds to the min distance
	and  (U2,-V1) corresponds to the max distance.
-----------------------------------------------------------------------------*/

void Extrema_ExtPElS::Perform(const gp_Pnt&       P, 
			      const gp_Sphere&    S,
			      const Standard_Real Tol)
{
  myDone = Standard_False;
  myNbExt = 0;

  gp_Ax3 Pos = S.Position();
  gp_Vec OP (Pos.Location(),P);

// Case when P is mixed with O ...
  if (OP.SquareMagnitude() < Tol * Tol) { return; }

// Projection if P in plane XOY of the sphere ...
  gp_Pnt O = Pos.Location();
  gp_Vec OZ (Pos.Direction());
  Standard_Real Zp = OP.Dot(OZ);
  gp_Pnt Pp = P.Translated(OZ.Multiplied(-Zp));

// Calculation of extrema ...
  gp_Vec OPp (O,Pp);
  Standard_Real U1, U2, V;
  if (OPp.SquareMagnitude() < Tol * Tol) {
    U1 = 0.;
    U2 = 0.;
    if (Zp < 0.) { V = -M_PI / 2.; }
    else { V = M_PI / 2.; }
  }
  else {
    gp_Vec myZ = Pos.XDirection()^Pos.YDirection();
    U1 = gp_Vec(Pos.XDirection()).AngleWithRef(OPp,myZ);
    U2 = U1 + M_PI;
    if (U1 < 0.) { U1 += 2. * M_PI; }
    V = OP.Angle(OPp);
    if (Zp < 0.) { V = -V; }
  }

  gp_Pnt Ps;
  Ps = ElSLib::Value(U1,V,S);
  mySqDist[0] = Ps.SquareDistance(P);
  myPoint[0] = Extrema_POnSurf(U1,V,Ps);
  Ps = ElSLib::Value(U2,-V,S);
  mySqDist[1] = Ps.SquareDistance(P);
  myPoint[1] = Extrema_POnSurf(U2,-V,Ps);

  myNbExt = 2;
  myDone = Standard_True;
}
//=============================================================================

Extrema_ExtPElS::Extrema_ExtPElS (const gp_Pnt&       P, 
				  const gp_Torus&     S,
				  const Standard_Real Tol)
{
  Perform(P, S, Tol);
}
/*-----------------------------------------------------------------------------
Function:
  Find 2 extreme distances between point P and torus S.

  Method:
  Let Pp be the projection of point P in plane XOY of the torus;
  2 cases are consideres:
  1- distance(Pp,O) < Tol:
     There is an infinite number of solutions; IsDone() = Standard_False.
  2- distance(Pp,O) > Tol:
     One is located in plane PpOZ;
     Let V1 = angle(OX,OPp) with 0. < V1 < 2.*M_PI,
	 V2 = V1 + M_PI with 0. < V2 < 2.*M_PI,
	 O1 and O2 centers of circles (O1 on coord. posit.)
         U1 = angle(OPp,O1P),
	 U2 = angle(OPp,PO2);
     then (U1,V1) corresponds to the min distance
     and  (U2,V2) corresponds to the max distance.
-----------------------------------------------------------------------------*/
void Extrema_ExtPElS::Perform(const gp_Pnt&       P, 
			      const gp_Torus&     S,
			      const Standard_Real Tol)
{
  myDone = Standard_False;
  myNbExt = 0;

// Projection of P in plane XOY ...
  gp_Ax3 Pos = S.Position();
  gp_Pnt O = Pos.Location();
  gp_Vec OZ (Pos.Direction());
  gp_Pnt Pp = P.Translated(OZ.Multiplied(-(gp_Vec(O,P).Dot(Pos.Direction()))));
					 
// Calculation of extrema ...
  gp_Vec OPp (O,Pp);
  Standard_Real R2 = OPp.SquareMagnitude();
  if (R2 < Tol * Tol) { return; }
 
  gp_Vec myZ = Pos.XDirection()^Pos.YDirection();
  Standard_Real U1 = gp_Vec(Pos.XDirection()).AngleWithRef(OPp,myZ);
  Standard_Real U2 = U1 + M_PI;
  if (U1 < 0.) { U1 += 2. * M_PI; }
  Standard_Real R = sqrt(R2);
  gp_Vec OO1 = OPp.Divided(R).Multiplied(S.MajorRadius());
  gp_Vec OO2 = OO1.Multiplied(-1.);
  gp_Pnt O1 = O.Translated(OO1);
  gp_Pnt O2 = O.Translated(OO2);

  if(O1.SquareDistance(P) < Tol) { return; }
  if(O2.SquareDistance(P) < Tol) { return; }

  Standard_Real V1 = OO1.AngleWithRef(gp_Vec(O1,P),OO1.Crossed(OZ));
  Standard_Real V2 = OO2.AngleWithRef(gp_Vec(P,O2),OO2.Crossed(OZ));
  if (V1 < 0.) { V1 += 2. * M_PI; }
  if (V2 < 0.) { V2 += 2. * M_PI; }

  gp_Pnt Ps;
  Ps = ElSLib::Value(U1,V1,S);
  mySqDist[0] = Ps.SquareDistance(P);
  myPoint[0] = Extrema_POnSurf(U1,V1,Ps);

  Ps = ElSLib::Value(U1,V1+M_PI,S);
  mySqDist[1] = Ps.SquareDistance(P);
  myPoint[1] = Extrema_POnSurf(U1,V1+M_PI,Ps);

  Ps = ElSLib::Value(U2,V2,S);
  mySqDist[2] = Ps.SquareDistance(P);
  myPoint[2] = Extrema_POnSurf(U2,V2,Ps);

  Ps = ElSLib::Value(U2,V2+M_PI,S);
  mySqDist[3] = Ps.SquareDistance(P);
  myPoint[3] = Extrema_POnSurf(U2,V2+M_PI,Ps);

  myNbExt = 4;
  myDone = Standard_True;
}


Extrema_ExtPElS::Extrema_ExtPElS (const gp_Pnt&       P, 
				  const gp_Pln&       S,
				  const Standard_Real Tol)
{
  Perform(P, S, Tol);
}

void Extrema_ExtPElS::Perform (const gp_Pnt&       P, 
			       const gp_Pln&       S,
//			       const Standard_Real Tol)
			       const Standard_Real )
{
  myDone = Standard_False;
  myNbExt = 0;

// Projection of point P in plane XOY of the cylinder ...
  gp_Pnt O = S.Location();
  gp_Vec OZ (S.Axis().Direction());
  Standard_Real U, V = gp_Vec(O,P).Dot(OZ);
  gp_Pnt Pp = P.Translated(OZ.Multiplied(-V));

  ElSLib::Parameters(S, P, U, V);
  mySqDist[0] = Pp.SquareDistance(P);
  myPoint[0] = Extrema_POnSurf(U,V,Pp);
  myNbExt = 1;
  myDone = Standard_True;
}


//=============================================================================

Standard_Boolean Extrema_ExtPElS::IsDone () const { return myDone; }
//=============================================================================

Standard_Integer Extrema_ExtPElS::NbExt () const
{
  if (!IsDone()) { StdFail_NotDone::Raise(); }
  return myNbExt;
}
//=============================================================================

Standard_Real Extrema_ExtPElS::SquareDistance (const Standard_Integer N) const
{
  if (!IsDone()) { StdFail_NotDone::Raise(); }
  if ((N < 1) || (N > myNbExt)) { Standard_OutOfRange::Raise(); }
  return mySqDist[N-1];
}
//=============================================================================

Extrema_POnSurf Extrema_ExtPElS::Point (const Standard_Integer N) const
{
  if (!IsDone()) { StdFail_NotDone::Raise(); }
  if ((N < 1) || (N > myNbExt)) { Standard_OutOfRange::Raise(); }
  return myPoint[N-1];
}
//=============================================================================
