// Created on: 1993-03-04
// Created by: Jacques GOUSSARD
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


#include <Contap_ContAna.ixx>

#include <gp_XYZ.hxx>
#include <gp.hxx>

#define Tolpetit 1.e-8

Contap_ContAna::Contap_ContAna (): done(Standard_False) {}

void Contap_ContAna::Perform (const gp_Sphere& S,
                              const gp_Dir& D)
{
  done  = Standard_False;
  typL  = GeomAbs_Circle;
  pt1   = S.Location();
  dir1  = D;
  if (Abs(D.Dot(S.XAxis().Direction())) < 0.9999999999999) {
    dir2 = D.Crossed(S.XAxis().Direction());
  }
  else {
    dir2 = D.Crossed(S.YAxis().Direction());
  }
  prm   = S.Radius();
  nbSol = 1;
  done  = Standard_True;
}

void Contap_ContAna::Perform (const gp_Sphere& S,
                              const gp_Dir& D,
                              const Standard_Real Angle)
{
  done  = Standard_False;
  typL  = GeomAbs_Circle;

  dir1  = D;
  if (Abs(D.Dot(S.XAxis().Direction())) < 0.9999999999999) {
    dir2 = D.Crossed(S.XAxis().Direction());
  }
  else {
    dir2 = D.Crossed(S.YAxis().Direction());
  }
  Standard_Real alpha = (S.Direct() ? Angle : -Angle); 
  pt1.SetXYZ(S.Location().XYZ() - S.Radius()*sin(alpha)*D.XYZ()) ;
  prm   = S.Radius()*cos(alpha);
  nbSol = 1;
  done  = Standard_True;
}

void Contap_ContAna::Perform (const gp_Sphere& S,
                              const gp_Pnt& Eye)
{
  done = Standard_False;

  Standard_Real radius = S.Radius();
  Standard_Real dist = Eye.Distance(S.Location());
  if (dist <= radius) {
    nbSol = 0;
  }
  else {
    prm = radius*sqrt(1.-radius*radius/(dist*dist));
    if (prm < Tolpetit) {
      nbSol = 0;
    }
    else {
      gp_XYZ locxyz(S.Location().XYZ());
      dir1.SetXYZ(Eye.XYZ()-locxyz);
      pt1.SetXYZ(locxyz + (radius*radius/dist)*dir1.XYZ());
      if (Abs(dir1.Dot(S.XAxis().Direction())) < 0.9999999999999) {
	dir2 = dir1.Crossed(S.XAxis().Direction());
      }
      else {
	dir2 = dir1.Crossed(S.YAxis().Direction());
      }
      nbSol = 1;
      typL = GeomAbs_Circle;
    }
  }
  done = Standard_True;
}

void Contap_ContAna::Perform (const gp_Cylinder& C,
                              const gp_Dir& D)
{
  done = Standard_False;

  gp_XYZ normale(C.Position().Direction().XYZ());
  normale.Cross(D.XYZ());
  if (normale.Modulus() <= 1e-15) {
    nbSol = 0;
  }
  else {
    normale.Normalize();
    typL = GeomAbs_Line;
    dir1 = C.Position().Direction();
    dir2 = dir1;
    pt1.SetXYZ(C.Location().XYZ() + C.Radius()*normale);
    pt2.SetXYZ(C.Location().XYZ() - C.Radius()*normale);
    nbSol = 2;
  }

  done = Standard_True;
}

void Contap_ContAna::Perform (const gp_Cylinder& C,
                              const gp_Dir& D,
                              const Standard_Real Angle)
{
  done = Standard_False;

  Standard_Real Coefcos = D.Dot(C.Position().XDirection());
  Standard_Real Coefsin = D.Dot(C.Position().YDirection());
  Standard_Real Coefcst = cos(M_PI*0.5 + Angle);

  Standard_Real norm1 = Coefcos*Coefcos + Coefsin*Coefsin;
  Standard_Real norm2 = sqrt(norm1);

  if (Abs(Coefcst) < norm2) {
    typL = GeomAbs_Line;
    nbSol = 2;
    dir1 = dir2 = C.Position().Direction();

    if (!C.Direct()) { // The normal is inverted.
      Coefcos = -Coefcos;
      Coefsin = -Coefsin;
    }

    // Necessary to solve Coefcos*cos(t) + Coefsin*sin(t) = Coefcst
    // and the origins of solution are in the reference of the 
    // cylinder in (R*cost0, R*sint0,0) and (R*cost1,R*sint1,0)
    // By setting cos(phi) = Coefcos/Sqrt(Coefcos**2 + Coefsin**2) and
    //           sin(phi) = Coefsin/Sqrt(Coefcos**2 + Coefsin**2)
    // and by using trigonometric relations the values of cosinus 
    // and sinus to the solutions are obtained.

    prm = Sqrt(norm1 - Coefcst*Coefcst);
    Standard_Real cost0,sint0,cost1,sint1;

    cost0 = (Coefcos*Coefcst - Coefsin*prm)/norm1;
    cost1 = (Coefcos*Coefcst + Coefsin*prm)/norm1;

    sint0 = ( Coefcos*prm + Coefsin*Coefcst)/norm1;
    sint1 = (-Coefcos*prm + Coefsin*Coefcst)/norm1;

    gp_XYZ Xdir(C.Position().XDirection().XYZ());
    gp_XYZ Ydir(C.Position().YDirection().XYZ());
    gp_XYZ dirxyz;

    dirxyz.SetLinearForm(cost0,Xdir,sint0,Ydir);
    dirxyz.Multiply(C.Radius());
    pt1.SetXYZ(C.Location().XYZ().Added(dirxyz));

    dirxyz.SetLinearForm(cost1,Xdir,sint1,Ydir);
    dirxyz.Multiply(C.Radius());
    pt2.SetXYZ(C.Location().XYZ().Added(dirxyz));
  }
  else {
    nbSol = 0;
  }

  done = Standard_True;
}

void Contap_ContAna::Perform (const gp_Cylinder& C,
                              const gp_Pnt& Eye)
{
  done = Standard_False;

  Standard_Real radius = C.Radius();
  gp_Lin theaxis(C.Axis());
  Standard_Real dist = theaxis.Distance(Eye);
  if (dist <= radius) {
    nbSol = 0;
  }
  else {
    typL = GeomAbs_Line;
    prm = radius*sqrt(1.-radius*radius/(dist*dist));
    dir1 = C.Axis().Direction();
    dir2 = dir1;
    gp_XYZ axeye(theaxis.Normal(Eye).Direction().XYZ()); // orientate the axis to the outside
    gp_XYZ normale((theaxis.Direction().Crossed(axeye)).XYZ());
//      normale.Normalize();
    pt1.SetXYZ(C.Location().XYZ() + (radius*radius/dist)*axeye);
    pt2.SetXYZ(pt1.XYZ() - prm*normale);
    pt1.SetXYZ(pt1.XYZ() + prm*normale);
    nbSol = 2;
  }
  done = Standard_True;
}

void Contap_ContAna::Perform (const gp_Cone& C,
                              const gp_Dir& D)
{
  done = Standard_False;

  Standard_Real Tgtalpha = Tan(C.SemiAngle());

  Standard_Real Coefcos = D.Dot(C.Position().XDirection());
  Standard_Real Coefsin = D.Dot(C.Position().YDirection());
  Standard_Real Coefcst = D.Dot(C.Axis().Direction())*Tgtalpha;

  Standard_Real norm1 = Coefcos*Coefcos + Coefsin*Coefsin;
  Standard_Real norm2 = Sqrt(norm1);
//  if (Abs(Abs(Coefcst)-norm2) <= Tolpetit) { // tol angulaire 1.e-8
//    typL = GeomAbs_Line;
//    nbSol = 1;
//    pt1 = C.Apex();
//    dir1 = D;
//  }
//  else if (Abs(Coefcst) < norm2) {

  if (Abs(Coefcst) < norm2) {
    typL = GeomAbs_Line;
    nbSol = 2;
    pt1 = C.Apex();
    pt2 = pt1;
    // Necessary to solve Coefcos*cos(t) + Coefsin*sin(t) = Coefcst
    // and director vectors of solutions are
    // cos(t0) * XDirection + sin(t0) * YDirection + ZDirection/Tgtalpha
    // By setting cos(phi) = Coefcos/Sqrt(Coefcos**2 + Coefsin**2) and
    //           sin(phi) = Coefsin/Sqrt(Coefcos**2 + Coefsin**2)
    // and by using trigonometric relations the values of cosinus 
    // and sinus to the solutions are obtained.

    prm = Sqrt(norm1 - Coefcst*Coefcst);
    Standard_Real cost0,sint0,cost1,sint1;

    cost0 = (Coefcos*Coefcst - Coefsin*prm)/norm1;
    cost1 = (Coefcos*Coefcst + Coefsin*prm)/norm1;

    sint0 = ( Coefcos*prm + Coefsin*Coefcst)/norm1;
    sint1 = (-Coefcos*prm + Coefsin*Coefcst)/norm1;
    
    gp_XYZ Xdir(C.Position().XDirection().XYZ());
    gp_XYZ Ydir(C.Position().YDirection().XYZ());
    gp_XYZ Zdir(C.Axis().Direction().XYZ());
    gp_XYZ dirxyz;
    dirxyz.SetLinearForm(cost0,Xdir,sint0,Ydir,1./Tgtalpha,Zdir);
    dir1.SetXYZ(dirxyz);
    pt1.SetXYZ(pt1.XYZ()+dirxyz);
    dirxyz.SetLinearForm(cost1,Xdir,sint1,Ydir,1./Tgtalpha,Zdir);
    dir2.SetXYZ(dirxyz);
    pt2.SetXYZ(pt2.XYZ()+dirxyz);
  }
  else {
    nbSol = 0;
  }
  done = Standard_True;
}

void Contap_ContAna::Perform (const gp_Cone& C,
                              const gp_Dir& D,
                              const Standard_Real Angle)
{
  done = Standard_False;
  nbSol = 0;

  Standard_Real Ang = C.SemiAngle();
  Standard_Real Cosa = cos(Ang);
  Standard_Real Sina = sin(Ang);

  Standard_Real Coefcos = D.Dot(C.Position().XDirection());
  Standard_Real Coefsin = D.Dot(C.Position().YDirection());

  Standard_Real Coefcst1 = cos(M_PI*0.5 + Angle);

  Standard_Real norm1 = Coefcos*Coefcos + Coefsin*Coefsin;
  Standard_Real norm2 = Sqrt(norm1);

  Standard_Real Coefnz = D.Dot(C.Axis().Direction())*Sina;
  Standard_Real Coefcst = (Coefcst1 + Coefnz)/Cosa;

  if (Abs(Coefcst) < norm2) {
    typL = GeomAbs_Line;
    nbSol+= 2;
    pt1 = C.Apex();
    pt2 = pt1;

    // It is requiredto solve Coefcos*cos(t) + Coefsin*sin(t) = Coefcst
    // and the director vectors of solutions are
    // cos(t0) * XDirection + sin(t0) * YDirection + ZDirection/Tgtalpha
    // By setting cos(phi) = Coefcos/Sqrt(Coefcos**2 + Coefsin**2) and
    //           sin(phi) = Coefsin/Sqrt(Coefcos**2 + Coefsin**2)
    // and by using trigonometric relations the values of cosinus 
    // and sinus to the solutions are obtained.

    prm = Sqrt(norm1 - Coefcst*Coefcst);
    Standard_Real cost0,sint0,cost1,sint1;

    cost0 = (Coefcos*Coefcst - Coefsin*prm)/norm1;
    cost1 = (Coefcos*Coefcst + Coefsin*prm)/norm1;

    sint0 = ( Coefcos*prm + Coefsin*Coefcst)/norm1;
    sint1 = (-Coefcos*prm + Coefsin*Coefcst)/norm1;

    gp_XYZ Xdir(C.Position().XDirection().XYZ());
    gp_XYZ Ydir(C.Position().YDirection().XYZ());
    gp_XYZ Zdir(C.Axis().Direction().XYZ());
    if (!C.Direct()) {
      Zdir.Reverse();
    }
    gp_XYZ dirxyz;
    dirxyz.SetLinearForm(cost0,Xdir,sint0,Ydir,Cosa/Sina,Zdir);
    dir1.SetXYZ(dirxyz);
    pt1.SetXYZ(pt1.XYZ()+dirxyz);
    dirxyz.SetLinearForm(cost1,Xdir,sint1,Ydir,Cosa/Sina,Zdir);
    dir2.SetXYZ(dirxyz);
    pt2.SetXYZ(pt2.XYZ()+dirxyz);
  }

  Coefcst = (Coefcst1 - Coefnz)/Cosa;

  if (Abs(Coefcst) < norm2) {
    typL = GeomAbs_Line;
    nbSol+= 2;
    pt3 = C.Apex();
    pt4 = pt3;

    prm = Sqrt(norm1 - Coefcst*Coefcst);
    Standard_Real cost0,sint0,cost1,sint1;

    cost0 = (Coefcos*Coefcst - Coefsin*prm)/norm1;
    cost1 = (Coefcos*Coefcst + Coefsin*prm)/norm1;

    sint0 = ( Coefcos*prm + Coefsin*Coefcst)/norm1;
    sint1 = (-Coefcos*prm + Coefsin*Coefcst)/norm1;

    gp_XYZ Xdir(C.Position().XDirection().XYZ());
    gp_XYZ Ydir(C.Position().YDirection().XYZ());
    gp_XYZ Zdir(C.Axis().Direction().XYZ());
    if (!C.Direct()) {
      Zdir.Reverse();
    }
    gp_XYZ dirxyz;
    dirxyz.SetLinearForm(cost0,Xdir,sint0,Ydir,-Cosa/Sina,Zdir);
    dir3.SetXYZ(dirxyz);
    pt3.SetXYZ(pt3.XYZ()+dirxyz);
    dirxyz.SetLinearForm(cost1,Xdir,sint1,Ydir,-Cosa/Sina,Zdir);
    dir4.SetXYZ(dirxyz);
    pt4.SetXYZ(pt4.XYZ()+dirxyz);
    if (nbSol == 2) {
      pt1 = pt3;
      pt2 = pt4;
      dir1 = dir3;
      dir2 = dir4;
    }
  }

  done = Standard_True;
}

void Contap_ContAna::Perform (const gp_Cone& C,
                              const gp_Pnt& Eye)
{
  done = Standard_False;

  Standard_Real Tgtalpha = Tan(C.SemiAngle());

  gp_XYZ apexeye(Eye.XYZ());
  apexeye.Subtract(C.Apex().XYZ());

  Standard_Real Coefcos = apexeye.Dot(C.Position().XDirection().XYZ());
  Standard_Real Coefsin = apexeye.Dot(C.Position().YDirection().XYZ());
  Standard_Real Coefcst = apexeye.Dot(C.Axis().Direction().XYZ())*Tgtalpha;

  Standard_Real norm1 = Coefcos*Coefcos + Coefsin*Coefsin;
  Standard_Real norm2 = Sqrt(Coefcos*Coefcos + Coefsin*Coefsin);
//  if (Abs(Abs(Coefcst)-norm2) <= Tolpetit) { // tol angulaire 1.e-8
//    typL = GeomAbs_Line;
//    nbSol = 1;
//    pt1 = C.Apex();
//    dir1.SetXYZ(apexeye);
//  }
//  else if (Abs(Coefcst) < norm2) {

  if (Abs(Coefcst) < norm2) {
    typL = GeomAbs_Line;
    nbSol = 2;
    pt1 = C.Apex();
    pt2 = pt1;
    // It is required to solve Coefcos*cos(t) + Coefsin*sin(t) = Coefcst
    // and the director vectors of solutions are
    // cos(t0) * XDirection + sin(t0) * YDirection + ZDirection/Tgtalpha
    // By setting cos(phi) = Coefcos/Sqrt(Coefcos**2 + Coefsin**2) and
    //           sin(phi) = Coefsin/Sqrt(Coefcos**2 + Coefsin**2)
    // and by using trigonometric relations the values of cosinus 
    // and sinus to the solutions are obtained.

    prm = Sqrt(norm1 - Coefcst*Coefcst);
    Standard_Real cost0,sint0,cost1,sint1;

    cost0 = (Coefcos*Coefcst - Coefsin*prm)/norm1;
    cost1 = (Coefcos*Coefcst + Coefsin*prm)/norm1;

    sint0 = ( Coefcos*prm + Coefsin*Coefcst)/norm1;
    sint1 = (-Coefcos*prm + Coefsin*Coefcst)/norm1;

    gp_XYZ Xdir(C.Position().XDirection().XYZ());
    gp_XYZ Ydir(C.Position().YDirection().XYZ());
    gp_XYZ Zdir(C.Axis().Direction().XYZ());
    gp_XYZ dirxyz;
    dirxyz.SetLinearForm(cost0,Xdir,sint0,Ydir,1./Tgtalpha,Zdir);
    dir1.SetXYZ(dirxyz);
    pt1.SetXYZ(pt1.XYZ()+dirxyz);
    dirxyz.SetLinearForm(cost1,Xdir,sint1,Ydir,1./Tgtalpha,Zdir);
    dir2.SetXYZ(dirxyz);
    pt2.SetXYZ(pt2.XYZ()+dirxyz);
  }
  else {
    nbSol = 0;
  }
  done = Standard_True;
}

gp_Lin Contap_ContAna::Line (const Standard_Integer Index) const
{
  if (!done) {StdFail_NotDone::Raise();}
  if (typL != GeomAbs_Line || nbSol == 0) {Standard_DomainError::Raise();}
  if (Index <=0 || Index > nbSol) {Standard_OutOfRange::Raise();}
  switch (Index) {
  case 1:
    return gp_Lin(pt1,dir1);
  case 2:
    return gp_Lin(pt2,dir2);
  case 3:
    return gp_Lin(pt3,dir3);
  case 4:
    return gp_Lin(pt4,dir4);
  }
  Standard_OutOfRange::Raise("Program error in Contap_ContAna");
  return gp_Lin();
}
