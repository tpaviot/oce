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

//JCV 16/10/91


#include <Convert_CylinderToBSplineSurface.ixx>

#include <gp.hxx>
#include <gp_Trsf.hxx>

static const Standard_Integer TheUDegree  = 2;
static const Standard_Integer TheVDegree  = 1;
static const Standard_Integer TheNbUKnots = 5;
static const Standard_Integer TheNbVKnots = 2;
static const Standard_Integer TheNbUPoles = 9;
static const Standard_Integer TheNbVPoles = 2;


static void ComputePoles( const Standard_Real R,
			  const Standard_Real U1,
			  const Standard_Real U2,
			  const Standard_Real V1,
			  const Standard_Real V2,
			        TColgp_Array2OfPnt& Poles)
{
  Standard_Real deltaU = U2 - U1;
  
  Standard_Integer i;

  // Number of spans : maximum opening = 150 degrees ( = PI / 1.2 rds)
  Standard_Integer 
    nbUSpans = (Standard_Integer)IntegerPart( 1.2 * deltaU / M_PI) + 1;
  Standard_Real AlfaU = deltaU / ( nbUSpans * 2);

  Standard_Real UStart = U1;
  Poles(1,1) = gp_Pnt(R*Cos(UStart),R*Sin(UStart),V1);
  Poles(1,2) = gp_Pnt(R*Cos(UStart),R*Sin(UStart),V2);
  
  for ( i = 1; i <= nbUSpans; i++) {
    Poles( 2*i, 1) = gp_Pnt( R * Cos(UStart+AlfaU) / Cos(AlfaU),
			     R * Sin(UStart+AlfaU) / Cos(AlfaU),
			     V1 );
    Poles( 2*i, 2) = gp_Pnt( R * Cos(UStart+AlfaU) / Cos(AlfaU),
			     R * Sin(UStart+AlfaU) / Cos(AlfaU),
			     V2 );
    Poles(2*i+1,1) = gp_Pnt( R * Cos(UStart+2*AlfaU),
			     R * Sin(UStart+2*AlfaU),
			     V1 );
    Poles(2*i+1,2) = gp_Pnt( R * Cos(UStart+2*AlfaU),
			     R * Sin(UStart+2*AlfaU),
			     V2 );
    UStart += 2*AlfaU;
  }
}


//=======================================================================
//function : Convert_CylinderToBSplineSurface
//purpose  : 
//=======================================================================

Convert_CylinderToBSplineSurface::Convert_CylinderToBSplineSurface 
  (const gp_Cylinder&  Cyl, 
   const Standard_Real U1 ,
   const Standard_Real U2 , 
   const Standard_Real V1 ,
   const Standard_Real V2  ) 
: Convert_ElementarySurfaceToBSplineSurface (TheNbUPoles, TheNbVPoles, 
					     TheNbUKnots, TheNbVKnots,
					     TheUDegree , TheVDegree  ) 
{
  Standard_Real deltaU = U2 - U1;
  Standard_DomainError_Raise_if( (Abs(V2-V1) <= Abs(Epsilon(V1))) ||
				 (deltaU  >  2*M_PI)                || 
				 (deltaU  <  0.  ),
				 "Convert_CylinderToBSplineSurface");

  isuperiodic = Standard_False;
  isvperiodic = Standard_False;

  Standard_Integer i,j;
  // construction of the cylinder in the reference mark xOy.

  // Number of spans : maximum opening = 150 degrees ( = PI / 1.2 rds)
  Standard_Integer 
    nbUSpans = (Standard_Integer)IntegerPart( 1.2 * deltaU / M_PI) + 1;
  Standard_Real AlfaU = deltaU / ( nbUSpans * 2);

  nbUPoles = 2 * nbUSpans + 1;
  nbUKnots = nbUSpans + 1;

  nbVPoles = 2;
  nbVKnots = 2;

  Standard_Real R = Cyl.Radius();
  
  ComputePoles( R, U1, U2, V1, V2, poles);

  for ( i = 1; i<= nbUKnots; i++) {
    uknots(i) = U1 + (i-1) * 2 * AlfaU;
    umults(i) = 2;
  }
  umults(1)++; umults(nbUKnots)++;
  vknots(1) = V1; vmults(1) = 2;
  vknots(2) = V2; vmults(2) = 2;

  // Replace bspline in the mark of the sphere.
  // and calculate the weight of the bspline.
  Standard_Real W1;
  gp_Trsf Trsf;
  Trsf.SetTransformation( Cyl.Position(), gp::XOY());

  for ( i = 1; i <= nbUPoles; i++) {
    if ( i % 2 == 0)  W1 = Cos(AlfaU);
    else              W1 = 1.;

    for ( j = 1; j <= nbVPoles; j++) {
      weights( i, j) = W1;
      poles( i, j).Transform( Trsf);
    }
  }
}


//=======================================================================
//function : Convert_CylinderToBSplineSurface
//purpose  : 
//=======================================================================

Convert_CylinderToBSplineSurface::Convert_CylinderToBSplineSurface 
  (const gp_Cylinder&  Cyl, 
   const Standard_Real V1 , 
   const Standard_Real V2  )
: Convert_ElementarySurfaceToBSplineSurface (TheNbUPoles, TheNbVPoles,
					     TheNbUKnots, TheNbVKnots,
					     TheUDegree , TheVDegree)
{
  Standard_DomainError_Raise_if( Abs(V2-V1) <= Abs(Epsilon(V1)),
				 "Convert_CylinderToBSplineSurface");

  Standard_Integer i,j;

  isuperiodic = Standard_True;
  isvperiodic = Standard_False;

  // construction of the cylinder in the reference mark xOy.

  Standard_Real R = Cyl.Radius();
  
  ComputePoles( R, 0., 2.*M_PI, V1, V2, poles); 

  nbUPoles = 6;
  nbUKnots = 4;
  nbVPoles = 2;
  nbVKnots = 2;
  
  for ( i = 1; i <= nbUKnots; i++) {
    uknots(i) = ( i-1) * 2. * M_PI /3.;
    umults(i) = 2;
  }
  vknots(1) = V1;  vmults(1) = 2;
  vknots(2) = V2;  vmults(2) = 2;

  // Replace the bspline inn the mark of the cone.
  // and calculate the weight of the bspline.
  Standard_Real W;
  gp_Trsf Trsf;
  Trsf.SetTransformation( Cyl.Position(), gp::XOY());

  for ( i = 1; i <= nbUPoles; i++) {
    if ( i % 2 == 0)  W = 0.5;    // = Cos(pi /3)
    else              W = 1.;

    for ( j = 1; j <= nbVPoles; j++) {
      weights( i, j) = W;
      poles( i, j).Transform( Trsf);
    }
  }
}

