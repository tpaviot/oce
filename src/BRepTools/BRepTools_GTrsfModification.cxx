// Created on: 1996-12-30
// Created by: Stagiaire Mary FABIEN
// Copyright (c) 1996-1999 Matra Datavision
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



#include <BRepTools_GTrsfModification.ixx>

#include <Geom_Plane.hxx>
#include <Geom_Line.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_BezierSurface.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_BezierCurve.hxx>
#include <Standard_Type.hxx>
#include <BRep_Tool.hxx>
#include <gp_GTrsf2d.hxx>
#include <gp_XYZ.hxx>
#include <gp_TrsfForm.hxx>
#include <Standard_NoSuchObject.hxx>

#include <gp.hxx>
#include <GeomLib.hxx>
#include <TopAbs.hxx>

//=======================================================================
//function : BRepTools_GTrsfModification
//purpose  : 
//=======================================================================

BRepTools_GTrsfModification::BRepTools_GTrsfModification(const gp_GTrsf& T) :
myGTrsf(T)
{
  // on prend comme dilatation maximale pour la tolerance la norme sup
  Standard_Real loc1, loc2, loc3, loc4;

  loc1 = Max(Abs(T.Value(1,1)), Abs(T.Value(1,2)));
  loc2 = Max(Abs(T.Value(2,1)), Abs(T.Value(2,2)));
  loc3 = Max(Abs(T.Value(3,1)), Abs(T.Value(3,2)));
  loc4 = Max(Abs(T.Value(1,3)), Abs(T.Value(2,3)));

  loc1 = Max(loc1, loc2);
  loc2 = Max(loc3, loc4);

  loc1 = Max(loc1, loc2);

  myGScale = Max(loc1, Abs(T.Value(3,3)));
}


//=======================================================================
//function : GTrsf
//purpose  : 
//=======================================================================

gp_GTrsf& BRepTools_GTrsfModification::GTrsf ()
{
  return myGTrsf;
}

//=======================================================================
//function : NewSurface
//purpose  : 
//=======================================================================

Standard_Boolean BRepTools_GTrsfModification::NewSurface
      (const TopoDS_Face& F,
       Handle(Geom_Surface)& S,
       TopLoc_Location& L,
       Standard_Real& Tol,
       Standard_Boolean& RevWires,
       Standard_Boolean& RevFace)
{
  gp_GTrsf gtrsf;
  gtrsf.SetVectorialPart(myGTrsf.VectorialPart());
  gtrsf.SetTranslationPart(myGTrsf.TranslationPart());
  S = Handle(Geom_Surface)::DownCast(BRep_Tool::Surface(F,L)->Copy());

  Tol = BRep_Tool::Tolerance(F);
  Tol *= myGScale;
  RevWires = Standard_False;
  RevFace = myGTrsf.IsNegative();
  S = Handle(Geom_Surface)::DownCast(S->Transformed(L.Transformation()));
  
  Handle(Standard_Type) TheTypeS = S->DynamicType();
  if (TheTypeS == STANDARD_TYPE(Geom_BSplineSurface)) {
    Handle(Geom_BSplineSurface) S2 = Handle(Geom_BSplineSurface)::DownCast(S);
    for(Standard_Integer i = 1; i <= S2->NbUPoles(); i++) 
      for(Standard_Integer j = 1; j <= S2->NbVPoles(); j++) {
	gp_XYZ coor(S2->Pole(i, j).Coord());
	gtrsf.Transforms(coor);
	gp_Pnt P(coor);
	S2->SetPole(i, j, P);
      }
  }
  else
    if (TheTypeS == STANDARD_TYPE(Geom_BezierSurface)) {
      Handle(Geom_BezierSurface) S2 = Handle(Geom_BezierSurface)::DownCast(S);
      for(Standard_Integer i = 1; i <= S2->NbUPoles(); i++) 
	for(Standard_Integer j = 1; j <= S2->NbVPoles(); j++) {
	  gp_XYZ coor(S2->Pole(i, j).Coord());
	  gtrsf.Transforms(coor);
	  gp_Pnt P(coor);
	  S2->SetPole(i, j, P);
	}
    }
    else
      Standard_NoSuchObject_Raise_if(1,"BRepTools_GTrsfModification : Pb no BSpline/Bezier Type Surface");

  L.Identity();
  return Standard_True;
}


//=======================================================================
//function : NewCurve
//purpose  : 
//=======================================================================

Standard_Boolean BRepTools_GTrsfModification::NewCurve
(const TopoDS_Edge& E, 
 Handle(Geom_Curve)& C,
 TopLoc_Location& L, 
 Standard_Real& Tol)
{
  Standard_Real f,l;
  gp_GTrsf gtrsf;
  gtrsf.SetVectorialPart(myGTrsf.VectorialPart());
  gtrsf.SetTranslationPart(myGTrsf.TranslationPart());
  Tol = BRep_Tool::Tolerance(E)*myGScale;
  C = BRep_Tool::Curve(E, L, f, l);
  
  if (!C.IsNull()) {
    C = Handle(Geom_Curve)::DownCast(C->Copy()->Transformed(L.Transformation()));
    Handle(Standard_Type) TheTypeC = C->DynamicType();
    if (TheTypeC == STANDARD_TYPE(Geom_BSplineCurve)) {
      Handle(Geom_BSplineCurve) C2 = Handle(Geom_BSplineCurve)::DownCast(C);
      for(Standard_Integer i = 1; i <= C2->NbPoles(); i++) {
	gp_XYZ coor(C2->Pole(i).Coord());
	gtrsf.Transforms(coor);
	gp_Pnt P(coor);
	C2->SetPole(i, P);
      }
    }
    else
      if(TheTypeC == STANDARD_TYPE(Geom_BezierCurve)) {
	Handle(Geom_BezierCurve) C2 = Handle(Geom_BezierCurve)::DownCast(C);
	for(Standard_Integer i = 1; i <= C2->NbPoles(); i++) {
	  gp_XYZ coor(C2->Pole(i).Coord());
	  gtrsf.Transforms(coor);
	  gp_Pnt P(coor);
	  C2->SetPole(i, P);
	}
      }
      else
      Standard_NoSuchObject_Raise_if(1,"BRepTools_GTrsfModification : Pb no BSpline/Bezier Type Curve");
    C = new Geom_TrimmedCurve(C, f, l);
  }
  L.Identity() ;  
  return Standard_True;
}

//=======================================================================
//function : NewPoint
//purpose  : 
//=======================================================================

Standard_Boolean BRepTools_GTrsfModification::NewPoint
(const TopoDS_Vertex& V, 
 gp_Pnt& P, 
 Standard_Real& Tol)
{
  gp_Pnt Pnt = BRep_Tool::Pnt(V);
  Tol = BRep_Tool::Tolerance(V);
  Tol *= myGScale;
  gp_XYZ coor(Pnt.Coord());
  myGTrsf.Transforms(coor);
  P.SetXYZ(coor);

  return Standard_True;
}

//=======================================================================
//function : NewCurve2d
//purpose  : 
//=======================================================================

Standard_Boolean BRepTools_GTrsfModification::NewCurve2d
    (const TopoDS_Edge& E, 
     const TopoDS_Face& F, 
     const TopoDS_Edge&, 
     const TopoDS_Face&, 
     Handle(Geom2d_Curve)& C,
     Standard_Real& Tol)
{
  TopLoc_Location loc;
  Tol = BRep_Tool::Tolerance(E);
  Tol *= myGScale;
  Standard_Real f,l;
  C = BRep_Tool::CurveOnSurface(E,F,f,l);
  C = new Geom2d_TrimmedCurve(C, f, l);
  return Standard_True;
}

//=======================================================================
//function : NewParameter
//purpose  : 
//=======================================================================

Standard_Boolean BRepTools_GTrsfModification::NewParameter
   (const TopoDS_Vertex& V, 
    const TopoDS_Edge& E, 
    Standard_Real& P, 
    Standard_Real& Tol)
{
  Tol = BRep_Tool::Tolerance(V);
  Tol *= myGScale;
  P = BRep_Tool::Parameter(V,E);
  return Standard_True;
}

//=======================================================================
//function : Continuity
//purpose  : 
//=======================================================================

GeomAbs_Shape BRepTools_GTrsfModification::Continuity
  (const TopoDS_Edge& E,
   const TopoDS_Face& F1,
   const TopoDS_Face& F2,
   const TopoDS_Edge&,
   const TopoDS_Face&,
   const TopoDS_Face&)
{
  return BRep_Tool::Continuity(E,F1,F2);
}


