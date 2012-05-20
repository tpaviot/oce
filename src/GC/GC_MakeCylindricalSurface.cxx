// Created on: 1992-10-02
// Created by: Remi GILET
// Copyright (c) 1992-1999 Matra Datavision
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


#include <GC_MakeCylindricalSurface.ixx>
#include <gce_MakeCylinder.hxx>
#include <gp_Lin.hxx>
#include <StdFail_NotDone.hxx>

GC_MakeCylindricalSurface::GC_MakeCylindricalSurface(const gp_Cylinder& C)
{
  TheError = gce_Done;
  TheCylinder = new Geom_CylindricalSurface(C);
}

GC_MakeCylindricalSurface::GC_MakeCylindricalSurface(const gp_Ax2& A2    ,
						const Standard_Real  Radius)
{
  if (Radius < 0.0) { TheError = gce_NegativeRadius; }
  else {
    TheError = gce_Done;
    TheCylinder = new Geom_CylindricalSurface(A2,Radius);
  }
}

//=========================================================================
//   Construction of a cylinder by axis <A1> et radius <Radius>.           +
//=========================================================================

GC_MakeCylindricalSurface::GC_MakeCylindricalSurface(const gp_Ax1& A1     ,
						 const Standard_Real Radius ) 
{
  gce_MakeCylinder Cyl = gce_MakeCylinder(A1,Radius);
  TheError = Cyl.Status();
  if (TheError == gce_Done) {
    TheCylinder=new Geom_CylindricalSurface(Cyl.Value());
  }
}

//=========================================================================
//   Construction of a cylinder by a circle <Cir>.                      +
//=========================================================================

GC_MakeCylindricalSurface::GC_MakeCylindricalSurface(const gp_Circ& Circ ) {
  gp_Cylinder Cyl = gce_MakeCylinder(Circ);
  TheCylinder=new Geom_CylindricalSurface(Cyl);
  TheError = gce_Done;
}

//=========================================================================
//   Construction of a cylinder by tree points <P1>, <P2>, <P3>.         +
//   Two first points define the axis.                                   +
//   The third gives the radius.                                         +
//=========================================================================

GC_MakeCylindricalSurface::GC_MakeCylindricalSurface(const gp_Pnt& P1 ,
						       const gp_Pnt& P2 ,
						       const gp_Pnt& P3 ) {
  gce_MakeCylinder Cyl = gce_MakeCylinder(P1,P2,P3);
  TheError = Cyl.Status();
  if (TheError == gce_Done) {
    TheCylinder=new Geom_CylindricalSurface(Cyl.Value());
  }
}

GC_MakeCylindricalSurface::GC_MakeCylindricalSurface(const gp_Cylinder& Cyl ,
						     const Standard_Real  Dist)
{
  TheError = gce_Done;
  Standard_Real R = Abs(Cyl.Radius()-Dist);
  TheCylinder = new Geom_CylindricalSurface(Cyl);
  TheCylinder->SetRadius(R);
}

GC_MakeCylindricalSurface::GC_MakeCylindricalSurface(const gp_Cylinder& Cyl ,
						       const gp_Pnt&     Point)
{
  TheError = gce_Done;
  gp_Cylinder C(Cyl);
  gp_Lin L(C.Axis());
  Standard_Real R = L.Distance(Point);
  C.SetRadius(R);
  TheCylinder = new Geom_CylindricalSurface(C);
}

const Handle(Geom_CylindricalSurface)& 
       GC_MakeCylindricalSurface::Value() const
{ 
  StdFail_NotDone_Raise_if(!TheError == gce_Done,"");
  return TheCylinder;
}

const Handle(Geom_CylindricalSurface)& GC_MakeCylindricalSurface::Operator() const 
{
  return Value();
}

GC_MakeCylindricalSurface::operator Handle(Geom_CylindricalSurface) () const
{
  return Value();
}
