// Created on: 1992-03-13
// Created by: Christophe MARION
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


#include <HLRBRep_Surface.ixx>
#include <HLRBRep_BSurfaceTool.hxx>
#include <gp_Pln.hxx>
#include <GProp_PEquation.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <BRepClass_FaceClassifier.hxx>
#include <HLRAlgo_Projector.hxx>
#include <HLRBRep_Curve.hxx>
#include <TColStd_Array2OfReal.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_BezierSurface.hxx>

//=======================================================================
//function : HLRBRep_Surface
//purpose  : 
//=======================================================================

HLRBRep_Surface::HLRBRep_Surface ()
{
}

//=======================================================================
//function : Surface
//purpose  : 
//=======================================================================

void HLRBRep_Surface::Surface (const TopoDS_Face& F)
{
  mySurf.Initialize(F,Standard_False);
  GeomAbs_SurfaceType typ = HLRBRep_BSurfaceTool::GetType(mySurf);
  switch (typ) {

  case GeomAbs_Plane :
  case GeomAbs_Cylinder :
  case GeomAbs_Cone :
  case GeomAbs_Sphere :
  case GeomAbs_Torus :
    // unchanged type
    myType = typ;
    break;
    
  case GeomAbs_BezierSurface :
    if (HLRBRep_BSurfaceTool::UDegree(mySurf) == 1 &&
	HLRBRep_BSurfaceTool::VDegree(mySurf) == 1) {
      myType = GeomAbs_Plane;
    }
    else
      myType = typ;
    break;
    
    default :
    myType = GeomAbs_OtherSurface;
    break;
  }
}

//=======================================================================
//function : SideRowsOfPoles
//purpose  : 
//=======================================================================

Standard_Boolean 
HLRBRep_Surface::SideRowsOfPoles (const Standard_Real tol,
				  const Standard_Integer nbuPoles,
				  const Standard_Integer nbvPoles,
				  TColgp_Array2OfPnt& Pnt) const
{
  Standard_Integer iu,iv;
  Standard_Real x0,y0,x,y,z;
  Standard_Boolean result;
  Standard_Real tole = (Standard_Real)tol;
  const gp_Trsf& T = ((HLRAlgo_Projector*) myProj)->Transformation();

  for (iu = 1; iu <= nbuPoles; iu++) {
    
    for (iv = 1; iv <= nbvPoles; iv++)
      Pnt(iu,iv).Transform(T);
  }
  result = Standard_True;

  for (iu = 1; iu <= nbuPoles && result; iu++) {         // Side iso u ?
    Pnt(iu,1).Coord(x0,y0,z);
    
    for (iv = 2; iv <= nbvPoles && result; iv++) {
      Pnt(iu,iv).Coord(x,y,z);
      result = Abs(x-x0) < tole && Abs(y-y0) < tole;
    }
  }
  if (result) return result;
  result = Standard_True;
  
  for (iv = 1; iv <= nbvPoles && result; iv++) {         // Side iso v ?
    Pnt(1,iv).Coord(x0,y0,z);
    
    for (iu = 2; iu <= nbuPoles && result; iu++) {
      Pnt(iu,iv).Coord(x,y,z);
      result = Abs(x-x0) < tole && Abs(y-y0) < tole;
    }
  }
  if (result) return result;

  // Are the Poles in a Side Plane ?
  TColgp_Array1OfPnt p(1,nbuPoles*nbvPoles);
  Standard_Integer i = 0;

  for (iu = 1; iu <= nbuPoles; iu++) {
    
    for (iv = 1; iv <= nbvPoles; iv++) { 
      i++;
      p(i) = Pnt(iu,iv);
    }
  }

  GProp_PEquation Pl(p,(Standard_Real)tol);
  if (Pl.IsPlanar())
    result = Abs(Pl.Plane().Axis().Direction().Z()) < 0.0001;

  return result;
}

//=======================================================================
//function : IsSide
//purpose  : 
//=======================================================================

Standard_Boolean 
HLRBRep_Surface::IsSide (const Standard_Real tolF,
			 const Standard_Real toler) const
{
  gp_Pnt Pt;
  gp_Vec D;
  Standard_Real r;

  if (myType == GeomAbs_Plane) {
    gp_Pln Pl = Plane();
    gp_Ax1 A  = Pl.Axis();
    Pt = A.Location();
    D  = A.Direction();
    Pt.Transform(((HLRAlgo_Projector*) myProj)->Transformation());
    D .Transform(((HLRAlgo_Projector*) myProj)->Transformation());
    if (((HLRAlgo_Projector*) myProj)->Perspective()) {
      r = D.Z() * ((HLRAlgo_Projector*) myProj)->Focus() - 
	( D.X() * Pt.X() + D.Y() * Pt.Y() + D.Z() * Pt.Z() );
    }
    else r= D.Z();
    return Abs(r) < toler;
  }
  else if (myType == GeomAbs_Cylinder) {
    if (((HLRAlgo_Projector*) myProj)->Perspective()) return Standard_False;
    gp_Cylinder Cyl = HLRBRep_BSurfaceTool::Cylinder(mySurf);
    gp_Ax1 A = Cyl.Axis();
    D  = A.Direction();
    D .Transform(((HLRAlgo_Projector*) myProj)->Transformation());
    r = Sqrt(D.X() * D.X() + D.Y() * D.Y());
    return r < toler;
  }
  else if (myType == GeomAbs_Cone) {
    if (!((HLRAlgo_Projector*) myProj)->Perspective()) return Standard_False;
    gp_Cone Con = HLRBRep_BSurfaceTool::Cone(mySurf);
    Pt = Con.Apex();
    Pt.Transform(((HLRAlgo_Projector*) myProj)->Transformation());
    Standard_Real tol = 0.001;
    return Pt.IsEqual(gp_Pnt(0,0,((HLRAlgo_Projector*) myProj)->Focus()),tol);
  }
  else if (myType == GeomAbs_BezierSurface) {
    if (((HLRAlgo_Projector*) myProj)->Perspective()) return Standard_False;
    Standard_Integer nu = HLRBRep_BSurfaceTool::NbUPoles(mySurf);
    Standard_Integer nv = HLRBRep_BSurfaceTool::NbVPoles(mySurf);
    TColgp_Array2OfPnt Pnt(1,nu,1,nv);
    HLRBRep_BSurfaceTool::Bezier(mySurf)->Poles(Pnt);
    return SideRowsOfPoles (tolF,nu,nv,Pnt);
  }
  else if (myType == GeomAbs_BSplineSurface) {
    if (((HLRAlgo_Projector*) myProj)->Perspective()) return Standard_False;
    Standard_Integer nu = HLRBRep_BSurfaceTool::NbUPoles(mySurf);
    Standard_Integer nv = HLRBRep_BSurfaceTool::NbVPoles(mySurf);
    TColgp_Array2OfPnt Pnt(1,nu,1,nv);
    TColStd_Array2OfReal W(1,nu,1,nv);
    HLRBRep_BSurfaceTool::BSpline(mySurf)->Poles(Pnt);
    HLRBRep_BSurfaceTool::BSpline(mySurf)->Weights(W);
    return SideRowsOfPoles (tolF,nu,nv,Pnt);
  }
  else return Standard_False;
}

//=======================================================================
//function : IsAbove
//purpose  : 
//=======================================================================

Standard_Boolean  
HLRBRep_Surface::IsAbove (const Standard_Boolean back,
			  const Standard_Address A,
			  const Standard_Real tol) const
{ 
  Standard_Boolean planar = (myType == GeomAbs_Plane);
  if (planar) {
    gp_Pln Pl = Plane();
    Standard_Real a,b,c,d;
    Pl.Coefficients(a,b,c,d);
    Standard_Real u,u1,u2,dd,x,y,z;
    gp_Pnt P;
    u1 = ((HLRBRep_Curve*)A)->Parameter3d
      (((HLRBRep_Curve*)A)->FirstParameter());
    u2 = ((HLRBRep_Curve*)A)->Parameter3d
      (((HLRBRep_Curve*)A)->LastParameter());
    u=u1;
    ((HLRBRep_Curve*)A)->D0(u,P);
    P.Coord(x,y,z);
    dd = a*x + b*y + c*z + d;
    if (back) dd = -dd;
    if (dd < -tol) return Standard_False;
    if (((HLRBRep_Curve*)A)->GetType() != GeomAbs_Line) {
      Standard_Integer nbPnt = 30;
      Standard_Real step = (u2-u1)/(nbPnt+1);
      for (Standard_Integer i = 1; i <= nbPnt; i++) {
	u += step;
	((HLRBRep_Curve*)A)->D0(u,P);
	P.Coord(x,y,z);
	dd = a*x + b*y + c*z + d;
	if (back) dd = -dd;
	if (dd < -tol) return Standard_False;
      }
    }
    u = u2;
    ((HLRBRep_Curve*)A)->D0(u,P);
    P.Coord(x,y,z);
    dd = a*x + b*y + c*z + d;
    if (back) dd = -dd;
    if (dd < -tol) return Standard_False;
    return Standard_True;
  }
  else return Standard_False; 
}

//=======================================================================
//function : Value
//purpose  : 
//=======================================================================

gp_Pnt HLRBRep_Surface::Value (const Standard_Real U,
			       const Standard_Real V) const
{ 
  gp_Pnt P;
  D0(U,V,P);
  return P;
}

//=======================================================================
//function : Plane
//purpose  : 
//=======================================================================

gp_Pln  HLRBRep_Surface::Plane () const 
{
  GeomAbs_SurfaceType typ = HLRBRep_BSurfaceTool::GetType(mySurf);
  switch (typ) {
  case GeomAbs_BezierSurface :
    {
      gp_Pnt P;
      gp_Vec D1U;
      gp_Vec D1V;
      D1(0.5,0.5,P,D1U,D1V);
      return gp_Pln(P,gp_Dir(D1U.Crossed(D1V)));
    }
    
    default :
    return HLRBRep_BSurfaceTool::Plane(mySurf);
  }
}
