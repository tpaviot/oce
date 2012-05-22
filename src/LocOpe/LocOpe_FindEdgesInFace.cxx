// Created on: 1996-02-15
// Created by: Jacques GOUSSARD
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



#include <LocOpe_FindEdgesInFace.ixx>

#include <BRep_Tool.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_MapOfShape.hxx>
#include <BRepTopAdaptor_TopolTool.hxx>
#include <BRepAdaptor_HSurface.hxx>
#include <BRepAdaptor_Surface.hxx>

#include <Geom_Curve.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_Line.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Surface.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom_Plane.hxx>
#include <Geom_CylindricalSurface.hxx>

#include <ElCLib.hxx>
#include <ElSLib.hxx>
#include <Precision.hxx>



//=======================================================================
//function : Set
//purpose  : 
//=======================================================================

void LocOpe_FindEdgesInFace::Set(const TopoDS_Shape& Sh,
				 const TopoDS_Face& F)
{
  myShape = Sh;
  myFace = F;
  myList.Clear();

  TopTools_MapOfShape M;
  TopExp_Explorer exp,expf;
  Handle(Geom_Curve) C;
  Handle(Geom_Surface) S;
  TopLoc_Location Loc;
  Standard_Real f,l;
  Handle(Standard_Type) Tc,Ts;
  Standard_Boolean ToAdd;
  gp_Pln pl;
  gp_Cylinder cy;


  Standard_Real Tol = Precision::Confusion();
  Standard_Real TolAng = Precision::Angular();

  S = BRep_Tool::Surface(F);
  Ts = S->DynamicType();
  if (Ts == STANDARD_TYPE(Geom_RectangularTrimmedSurface)) {
    S = Handle(Geom_RectangularTrimmedSurface)::DownCast(S)->BasisSurface();
    Ts = S->DynamicType();
  }

  if (Ts != STANDARD_TYPE(Geom_Plane) && Ts != STANDARD_TYPE(Geom_CylindricalSurface)) {
    return; // pour le moment
  }

  Handle(BRepAdaptor_HSurface) HS = new BRepAdaptor_HSurface(myFace);
  BRepTopAdaptor_TopolTool TPT(HS);

  for (exp.Init(myShape,TopAbs_EDGE); exp.More(); exp.Next()) {
    ToAdd = Standard_False;
    const TopoDS_Edge& edg = TopoDS::Edge(exp.Current());
    if (M.Contains(edg)) {
      continue;
    }

    for (expf.Init(myFace,TopAbs_EDGE); expf.More();expf.Next()) {
      if (expf.Current().IsSame(edg)) {
	break;
      }
    }
    if (expf.More()) { // partage d`edge
      M.Add(edg);
      myList.Append(edg);
      continue;
    }

    C = BRep_Tool::Curve(edg,Loc,f,l);
    C = Handle(Geom_Curve)::DownCast(C->Transformed(Loc.Transformation()));
    Tc = C->DynamicType();
    if (Tc == STANDARD_TYPE(Geom_TrimmedCurve)) {
      C = Handle(Geom_TrimmedCurve)::DownCast(C)->BasisCurve();
      Tc = C->DynamicType();
    }
    if (Tc != STANDARD_TYPE(Geom_Line) && Tc != STANDARD_TYPE(Geom_Circle)) {
      continue; // pour le moment
    }
    if (Ts == STANDARD_TYPE(Geom_Plane)) {
      pl = Handle(Geom_Plane)::DownCast(S)->Pln();
    }
    else {
      cy = Handle(Geom_CylindricalSurface)::DownCast(S)->Cylinder();
    }

    if (Tc == STANDARD_TYPE(Geom_Line)) {
      gp_Lin li = Handle(Geom_Line)::DownCast(C)->Lin();
      if (Ts == STANDARD_TYPE(Geom_Plane)) {
	if (pl.Contains(li,Tol,TolAng)) {
	  ToAdd = Standard_True;
	}
      }
      else { //Ts == STANDARD_TYPE(Geom_CylindricalSurface)
	if (cy.Axis().IsParallel(li.Position(),TolAng) &&
	    Abs(li.Distance(cy.Location())-cy.Radius()) < Tol) {
	  ToAdd = Standard_True;
	}
      }
    }
    else { // Tt == STANDARD_TYPE(Geom_Circle)
      gp_Circ ci = Handle(Geom_Circle)::DownCast(C)->Circ();
      if (Ts == STANDARD_TYPE(Geom_Plane)) {
	if (pl.Position().IsCoplanar(ci.Position(),Tol,TolAng)) {
	  ToAdd = Standard_True;
	}
      }
      else {
	if (Abs(cy.Radius()-ci.Radius()) < Tol &&
	    cy.Axis().IsCoaxial(ci.Axis(),TolAng,Tol)) {
	  ToAdd = Standard_True;
	}
      }
    }

    if (ToAdd) {
      // On classifie 3 points.
      gp_Pnt p[3];
      Standard_Real U,V;
      p[0] = C->Value(f);
      p[1] = C->Value(l);
      p[2] = C->Value((f+l)/2.);
//      for (Standard_Integer i=0; i<3; i++) {
      Standard_Integer i;
      for ( i=0; i<3; i++) {
	if (Ts == STANDARD_TYPE(Geom_Plane)) {
	  ElSLib::Parameters(pl,p[i],U,V);
	}
	else {
	  ElSLib::Parameters(cy,p[i],U,V);
	}
	if (TPT.Classify(gp_Pnt2d(U,V),Precision::Confusion())== TopAbs_OUT) {
	  break;
	}
      }
      if (i >= 3) { 
	M.Add(edg);
	myList.Append(edg);
      }
    }
  }
}
