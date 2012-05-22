// Created on: 1998-05-07
// Created by: Andre LIEUTIER
// Copyright (c) 1998-1999 Matra Datavision
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



#include <Plate_PlaneConstraint.ixx>
#include <Plate_PinpointConstraint.hxx>


Plate_PlaneConstraint::Plate_PlaneConstraint(const gp_XY& point2d,
					     const gp_Pln& pln,
					     const Standard_Integer iu,
					     const Standard_Integer iv)
:myLSC(1,1)
{
  gp_XYZ point = pln.Location().XYZ();
  myLSC.SetPPC(1,Plate_PinpointConstraint(point2d,point,iu,iv));
  gp_XYZ dir = pln.Axis().Direction().XYZ();
  dir.Normalize();
  myLSC.SetCoeff(1,1,dir);
}
