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



#include <ProjLib_Plane.ixx>

#include <gp_Vec.hxx>

//=======================================================================
//function : ProjLib_Plane
//purpose  : 
//=======================================================================

ProjLib_Plane::ProjLib_Plane()
{
}


//=======================================================================
//function : ProjLib_Plane
//purpose  : 
//=======================================================================

ProjLib_Plane::ProjLib_Plane(const gp_Pln& Pl)
{
  Init(Pl);
}


//=======================================================================
//function : ProjLib_Plane
//purpose  : 
//=======================================================================

ProjLib_Plane::ProjLib_Plane(const gp_Pln& Pl, const gp_Lin& L)
{
  Init(Pl);
  Project(L);
}


//=======================================================================
//function : ProjLib_Plane
//purpose  : 
//=======================================================================

ProjLib_Plane::ProjLib_Plane(const gp_Pln& Pl, const gp_Circ& C)
{
  Init(Pl);
  Project(C);
}


//=======================================================================
//function : ProjLib_Plane
//purpose  : 
//=======================================================================

ProjLib_Plane::ProjLib_Plane(const gp_Pln& Pl, const gp_Elips& E)
{
  Init(Pl);
  Project(E);
}


//=======================================================================
//function : ProjLib_Plane
//purpose  : 
//=======================================================================

ProjLib_Plane::ProjLib_Plane(const gp_Pln& Pl, const gp_Parab& P)
{
  Init(Pl);
  Project(P);
}


//=======================================================================
//function : ProjLib_Plane
//purpose  : 
//=======================================================================

ProjLib_Plane::ProjLib_Plane(const gp_Pln& Pl, const gp_Hypr& H)
{
  Init(Pl);
  Project(H);
}


//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void  ProjLib_Plane::Init(const gp_Pln& Pl)
{
  myType  = GeomAbs_OtherCurve;
  isDone  = Standard_False;
  myIsPeriodic = Standard_False;
  myPlane = Pl;
}

//=======================================================================
//function : EvalPnt2d / EvalDir2d
//purpose  : returns the Projected Pnt / Dir in the parametrization range
//           of myPlane.
//=======================================================================

static gp_Pnt2d EvalPnt2d( const gp_Pnt P, const gp_Pln& Pl)
{
  gp_Vec OP( Pl.Location(),P);
  return gp_Pnt2d( OP.Dot(gp_Vec(Pl.Position().XDirection())),
	           OP.Dot(gp_Vec(Pl.Position().YDirection())));
}

static gp_Dir2d EvalDir2d( const gp_Dir& D, const gp_Pln& Pl)
{
  return gp_Dir2d( D.Dot(Pl.Position().XDirection()),
	           D.Dot(Pl.Position().YDirection()));
}


//=======================================================================
//function : Project
//purpose  : 
//=======================================================================

void  ProjLib_Plane::Project(const gp_Lin& L)
{
  myType = GeomAbs_Line;
  myLin  = gp_Lin2d(EvalPnt2d(L.Location() ,myPlane),
		    EvalDir2d(L.Direction(),myPlane) );
  isDone = Standard_True;
}


//=======================================================================
//function : Project
//purpose  : 
//=======================================================================

void  ProjLib_Plane::Project(const gp_Circ& C)
{

  myType = GeomAbs_Circle;

  gp_Pnt2d P2d = EvalPnt2d(C.Location(),myPlane);
  gp_Dir2d X2d = EvalDir2d(C.Position().XDirection(),myPlane);
  gp_Dir2d Y2d = EvalDir2d(C.Position().YDirection(),myPlane);
  gp_Ax22d Ax(P2d,X2d,Y2d);

  myCirc = gp_Circ2d(Ax, C.Radius());
  myIsPeriodic = Standard_True;
  isDone = Standard_True;
}


//=======================================================================
//function : Project
//purpose  : 
//=======================================================================

void  ProjLib_Plane::Project(const gp_Elips& E)
{
  myType = GeomAbs_Ellipse;

  gp_Pnt2d P2d = EvalPnt2d(E.Location(),myPlane);
  gp_Dir2d X2d = EvalDir2d(E.Position().XDirection(),myPlane);
  gp_Dir2d Y2d = EvalDir2d(E.Position().YDirection(),myPlane);
  gp_Ax22d Ax(P2d,X2d,Y2d);

  myElips = gp_Elips2d(Ax,E.MajorRadius(),E.MinorRadius());
  myIsPeriodic = Standard_True;
  isDone = Standard_True;
}


//=======================================================================
//function : Project
//purpose  : 
//=======================================================================

void  ProjLib_Plane::Project(const gp_Parab& P)
{
  myType = GeomAbs_Parabola;

  gp_Pnt2d P2d = EvalPnt2d(P.Location(),myPlane);
  gp_Dir2d X2d = EvalDir2d(P.Position().XDirection(),myPlane);
  gp_Dir2d Y2d = EvalDir2d(P.Position().YDirection(),myPlane);
  gp_Ax22d Ax(P2d,X2d,Y2d);

  myParab = gp_Parab2d(Ax,P.Focal());
  isDone = Standard_True;
}


//=======================================================================
//function : Project
//purpose  : 
//=======================================================================

void  ProjLib_Plane::Project(const gp_Hypr& H)
{
  myType = GeomAbs_Hyperbola;

  gp_Pnt2d P2d = EvalPnt2d(H.Location(),myPlane);
  gp_Dir2d X2d = EvalDir2d(H.Position().XDirection(),myPlane);
  gp_Dir2d Y2d = EvalDir2d(H.Position().YDirection(),myPlane);
  gp_Ax22d Ax(P2d,X2d,Y2d);

  myHypr = gp_Hypr2d(Ax,H.MajorRadius(),H.MinorRadius());
  isDone = Standard_True;
}
