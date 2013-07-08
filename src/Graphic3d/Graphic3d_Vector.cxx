// Created by: NW,JPB,CAL
// Copyright (c) 1991-1999 Matra Datavision
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


// Modified	27/12/98 : FMN ; PERF: OPTIMISATION LOADER (LOPTIM)


//-Version	

//-Design	Declaration des variables specifiques aux vecteurs

//-Warning	Un vecteur est defini par ses composantes ou par
//		deux points
//		Il peut etre normalise

//-References	

//-Language	C++ 2.0

//-Declarations

// for the class
#include <Graphic3d_Vector.ixx>

#include <Standard_Boolean.hxx>

//-Aliases

//-Global data definitions

#define Graphic3d_Vector_MyEpsilon 0.000001

//	-- les coordonnees du vecteur
//	MyX		:	Standard_ShortReal;
//	MyY		:	Standard_ShortReal;
//	MyZ		:	Standard_ShortReal;

//	-- la norme du vecteur
//	MyNorme		:	Standard_ShortReal;

//-Constructors

Graphic3d_Vector::Graphic3d_Vector ():
MyX (Standard_ShortReal (1.0)),
MyY (Standard_ShortReal (1.0)),
MyZ (Standard_ShortReal (1.0)),
MyNorme (Standard_ShortReal (1.0)) {
}

Graphic3d_Vector::Graphic3d_Vector (const Standard_Real AX, const Standard_Real AY, const Standard_Real AZ):
MyX (Standard_ShortReal (AX)),
MyY (Standard_ShortReal (AY)),
MyZ (Standard_ShortReal (AZ)),
MyNorme (Standard_ShortReal (Graphic3d_Vector::NormeOf (AX, AY, AZ))) {
}

Graphic3d_Vector::Graphic3d_Vector (const Graphic3d_Vertex& APoint1, const Graphic3d_Vertex& APoint2) {

	MyX	= APoint2.X() - APoint1.X();
	MyY	= APoint2.Y() - APoint1.Y();
	MyZ	= APoint2.Z() - APoint1.Z();

	MyNorme	= Standard_ShortReal (Graphic3d_Vector::NormeOf (MyX, MyY, MyZ));

}

//-Destructors

//-Methods, in order

void Graphic3d_Vector::Coord (Standard_Real& AX, Standard_Real& AY, Standard_Real& AZ) const {

	AX	= Standard_Real (MyX);
	AY	= Standard_Real (MyY);
	AZ	= Standard_Real (MyZ);

}

Standard_Real Graphic3d_Vector::X () const {

	return Standard_Real (MyX);

}

Standard_Real Graphic3d_Vector::Y () const {

	return Standard_Real (MyY);

}

Standard_Real Graphic3d_Vector::Z () const {

	return Standard_Real (MyZ);

}

void Graphic3d_Vector::Normalize () {

	if (Abs (MyNorme) <= RealEpsilon ())
		Graphic3d_VectorError::Raise ("The norm is null");

	if (!IsNormalized()) // CQO CTS40181
	    {	
	       MyX	= MyX / MyNorme;
	       MyY	= MyY / MyNorme;
	       MyZ	= MyZ / MyNorme;
	    }

	MyNorme	= Standard_ShortReal (1.0);

}

void Graphic3d_Vector::SetCoord (const Standard_Real Xnew, const Standard_Real Ynew, const Standard_Real Znew) {

	MyX	= Standard_ShortReal (Xnew);
	MyY	= Standard_ShortReal (Ynew);
	MyZ	= Standard_ShortReal (Znew);

	MyNorme	= Standard_ShortReal (Graphic3d_Vector::NormeOf (Standard_Real (MyX), Standard_Real (MyY), Standard_Real (MyZ)));

}

void Graphic3d_Vector::SetXCoord (const Standard_Real Xnew) {

	MyX	= Standard_ShortReal (Xnew);

	MyNorme	= Standard_ShortReal (Graphic3d_Vector::NormeOf (Standard_Real (MyX), Standard_Real (MyY), Standard_Real (MyZ)));

}

void Graphic3d_Vector::SetYCoord (const Standard_Real Ynew) {

	MyY	= Standard_ShortReal (Ynew);

	MyNorme	= Standard_ShortReal (Graphic3d_Vector::NormeOf (Standard_Real (MyX), Standard_Real (MyY), Standard_Real (MyZ)));

}

void Graphic3d_Vector::SetZCoord (const Standard_Real Znew) {

	MyZ	= Standard_ShortReal (Znew);

	MyNorme	= Standard_ShortReal (Graphic3d_Vector::NormeOf (Standard_Real (MyX), Standard_Real (MyY), Standard_Real (MyZ)));

}

Standard_Boolean Graphic3d_Vector::LengthZero () const {

	return (Abs (Standard_Real (MyNorme)) <= RealEpsilon ());

}

Standard_Boolean Graphic3d_Vector::IsNormalized () const {

	return (Abs (Standard_Real (MyNorme) - 1.0) <=
				Graphic3d_Vector_MyEpsilon);

}

Standard_Boolean Graphic3d_Vector::IsParallel (const Graphic3d_Vector& AV1, const Graphic3d_Vector& AV2) {

  Standard_Real aDif1 = 0, aDif2 = 0, aDif3 = 0;

  aDif1 = AV1.X () * AV2.Y () - AV1.Y () * AV2.X ();
  aDif2 = AV1.X () * AV2.Z () - AV1.Z () * AV2.X ();
  aDif3 = AV1.Y () * AV2.Z () - AV1.Z () * AV2.Y ();

  return (  (Abs (aDif1) <= Graphic3d_Vector_MyEpsilon) &&
            (Abs (aDif2) <= Graphic3d_Vector_MyEpsilon) &&
            (Abs (aDif3) <= Graphic3d_Vector_MyEpsilon)  );
}

Standard_Real Graphic3d_Vector::NormeOf (const Standard_Real AX, const Standard_Real AY, const Standard_Real AZ) {

	return (Sqrt (AX*AX+AY*AY+AZ*AZ));

}

Standard_Real Graphic3d_Vector::NormeOf (const Graphic3d_Vector& AVector) {

Standard_Real X, Y, Z;

	AVector.Coord(X, Y, Z);
	return (Graphic3d_Vector::NormeOf (X, Y, Z));

}
