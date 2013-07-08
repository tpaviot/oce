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

#include <Prs3d_Arrow.ixx>
#include <Graphic3d_Group.hxx>
#include <Graphic3d_ArrayOfSegments.hxx>
#include <Graphic3d_ArrayOfPolylines.hxx>

//=======================================================================
//function : Draw
//purpose  : 
//=======================================================================

void Prs3d_Arrow::Draw(const Handle(Prs3d_Presentation)& aPresentation,
                       const gp_Pnt& aLocation,
                       const gp_Dir& aDirection,
                       const Quantity_PlaneAngle anAngle,
                       const Quantity_Length aLength)
{
  Quantity_Length dx,dy,dz;  aDirection.Coord(dx,dy,dz);
//
// Point of the arrow:
  Quantity_Length xo,yo,zo;  aLocation.Coord(xo,yo,zo);

// Center of the base circle of the arrow:
  Quantity_Length xc = xo - dx * aLength;
  Quantity_Length yc = yo - dy * aLength;
  Quantity_Length zc = zo - dz * aLength;

// Construction of i,j mark for the circle:
  Quantity_Length xn=0., yn=0., zn=0.;

  if ( Abs(dx) <= Abs(dy) && Abs(dx) <= Abs(dz)) xn=1.;
  else if ( Abs(dy) <= Abs(dz) && Abs(dy) <= Abs(dx)) yn=1.;
  else zn=1.;
  Quantity_Length xi = dy * zn - dz * yn;
  Quantity_Length yi = dz * xn - dx * zn;
  Quantity_Length zi = dx * yn - dy * xn;

  Quantity_Length Norme = sqrt ( xi*xi + yi*yi + zi*zi );
  xi = xi / Norme; yi = yi / Norme; zi = zi/Norme;

  const Quantity_Length  xj = dy * zi - dz * yi;
  const Quantity_Length  yj = dz * xi - dx * zi;
  const Quantity_Length  zj = dx * yi - dy * xi;

  const Standard_Integer NbPoints = 15;

  Handle(Graphic3d_ArrayOfSegments) aPrims1 = new Graphic3d_ArrayOfSegments(2*NbPoints);
  Handle(Graphic3d_ArrayOfPolylines) aPrims2 = new Graphic3d_ArrayOfPolylines(NbPoints+1);

  gp_Pnt p1;
  const Standard_Real Tg=tan(anAngle);

  for (Standard_Integer i = 1; i <= NbPoints ; i++)
  {
    const Standard_Real cosinus = cos ( 2 * M_PI / NbPoints * (i-1) );   
    const Standard_Real sinus   = sin ( 2 * M_PI / NbPoints * (i-1) );

    const gp_Pnt pp(xc + (cosinus * xi + sinus * xj) * aLength * Tg,
                    yc + (cosinus * yi + sinus * yj) * aLength * Tg,
                    zc + (cosinus * zi + sinus * zj) * aLength * Tg);

    aPrims1->AddVertex(aLocation);
    aPrims1->AddVertex(pp);
    if(i==1) p1 = pp;
    aPrims2->AddVertex(pp);
  }
  aPrims2->AddVertex(p1);

  Prs3d_Root::CurrentGroup(aPresentation)->AddPrimitiveArray(aPrims1);
  Prs3d_Root::CurrentGroup(aPresentation)->AddPrimitiveArray(aPrims2);
}

//=======================================================================
//function : Fill
//purpose  : 
//=======================================================================

void Prs3d_Arrow::Fill(const Handle(Prs3d_Presentation)& /*aPresentation*/,
                       const gp_Pnt& /*aLocation*/,
                       const gp_Dir& /*aDirection*/,
                       const Quantity_PlaneAngle /*anAngle*/,
                       const Quantity_Length /*aLength*/)
{
}
