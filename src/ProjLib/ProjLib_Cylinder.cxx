// Created on: 1993-08-24
// Created by: Bruno DUMORTIER
// Copyright (c) 1993-1999 Matra Datavision
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


#include <Standard_NotImplemented.hxx>

#include <ProjLib_Cylinder.ixx>

#include <Precision.hxx>
#include <gp_Pln.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>
#include <gp_Ax3.hxx>
#include <gp_Vec2d.hxx>

//=======================================================================
//function : ProjLib_Cylinder
//purpose  : 
//=======================================================================

ProjLib_Cylinder::ProjLib_Cylinder()
{
}


//=======================================================================
//function : ProjLib_Cylinder
//purpose  : 
//=======================================================================

ProjLib_Cylinder::ProjLib_Cylinder(const gp_Cylinder& Cyl)
{
  Init(Cyl);
}


//=======================================================================
//function : ProjLib_Cylinder
//purpose  : 
//=======================================================================

ProjLib_Cylinder::ProjLib_Cylinder(const gp_Cylinder& Cyl, const gp_Lin& L)
{
  Init(Cyl);
  Project(L);
}


//=======================================================================
//function : ProjLib_Cylinder
//purpose  : 
//=======================================================================

ProjLib_Cylinder::ProjLib_Cylinder(const gp_Cylinder& Cyl, const gp_Circ& C)
{
  Init(Cyl);
  Project(C);
}


//=======================================================================
//function : ProjLib_Cylinder
//purpose  : 
//=======================================================================

ProjLib_Cylinder::ProjLib_Cylinder(const gp_Cylinder& Cyl, const gp_Elips& E)
{
  Init(Cyl);
  Project(E);
}


//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void  ProjLib_Cylinder::Init(const gp_Cylinder& Cyl)
{
  myType = GeomAbs_OtherCurve;
  myCylinder = Cyl;
  myIsPeriodic = Standard_False;
  isDone = Standard_False;
}


//=======================================================================
//function : EvalPnt2d / EvalDir2d
//purpose  : returns the Projected Pnt / Dir in the parametrization range
//           of myPlane.
//=======================================================================

static gp_Pnt2d EvalPnt2d( const gp_Pnt& P, const gp_Cylinder& Cy )
{
  gp_Vec OP( Cy.Location(),P);
  Standard_Real X = OP.Dot(gp_Vec(Cy.Position().XDirection()));
  Standard_Real Y = OP.Dot(gp_Vec(Cy.Position().YDirection()));
  Standard_Real Z = OP.Dot(gp_Vec(Cy.Position().Direction()));
  Standard_Real U ;

  if ( Abs(X) > Precision::PConfusion() ||
       Abs(Y) > Precision::PConfusion() ) {
    U = ATan2(Y,X);
  }
  else {
    U = 0.;
  }
  return gp_Pnt2d( U, Z);
}



//=======================================================================
//function : Project
//purpose  : 
//=======================================================================

void  ProjLib_Cylinder::Project(const gp_Lin& L)
{
  myType = GeomAbs_Line;

  gp_Pnt2d P2d = EvalPnt2d(L.Location(),myCylinder);
  if ( P2d.X() < 0.) {
    P2d.SetX(P2d.X()+2*M_PI);
  }
  Standard_Real Signe 
    = L.Direction().Dot(myCylinder.Position().Direction());
  Signe = (Signe > 0.) ? 1. : -1.;
  gp_Dir2d D2d(0., Signe);
  
  myLin = gp_Lin2d( P2d, D2d);
  isDone = Standard_True;
}


//=======================================================================
//function : Project
//purpose  : 
//=======================================================================

void  ProjLib_Cylinder::Project(const gp_Circ& C)
{
  myType = GeomAbs_Line;

  gp_Dir ZCyl = myCylinder.Position().XDirection().Crossed
    (myCylinder.Position().YDirection());
  gp_Dir ZCir = C.Position().XDirection().Crossed
    (C.Position().YDirection());

  Standard_Real U = myCylinder.Position().XDirection()
    .AngleWithRef(C.Position().XDirection(), ZCyl);

  gp_Vec OP( myCylinder.Location(),C.Location());
  Standard_Real V = OP.Dot(gp_Vec(myCylinder.Position().Direction()));


  gp_Pnt2d P2d1 (U, V);
  gp_Dir2d D2d;
  if ( ZCyl.Dot(ZCir) > 0.) 
    D2d.SetCoord(1., 0.);
  else
    D2d.SetCoord(-1., 0.);

  myLin = gp_Lin2d(P2d1, D2d);
  isDone = Standard_True;
}


//=======================================================================
//function : Project
//purpose  : 
//=======================================================================

//void  ProjLib_Cylinder::Project(const gp_Elips& E)
void  ProjLib_Cylinder::Project(const gp_Elips& )
{
  // Pour de vastes raisons de periodicite mal gerees,
  // la projection d`une ellipse sur un cylindre sera passee aux approx.
  
  
}

void  ProjLib_Cylinder::Project(const gp_Parab& P)
{
 ProjLib_Projector::Project(P);
}

void  ProjLib_Cylinder::Project(const gp_Hypr& H)
{
 ProjLib_Projector::Project(H);
}

