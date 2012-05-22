// Created on: 1996-09-20
// Created by: Jean Yves LEBEY
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


#ifdef HAVE_CONFIG_H
# include <oce-config.h>
#endif
#include <TestTopOpeDraw_TTOT.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <GeomAdaptor_Surface.hxx>
#include <BRep_Tool.hxx>
#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif

//=======================================================================
//function : ShapeEnumToString
//purpose  : 
//=======================================================================
void TestTopOpeDraw_TTOT::ShapeEnumToString
(const TopAbs_ShapeEnum T, TCollection_AsciiString& N)
{
  if      (T == TopAbs_SHAPE)  N = "s"; 
  else if (T == TopAbs_COMPOUND)  N = "co";
  else if (T == TopAbs_COMPSOLID)  N = "cs";
  else if (T == TopAbs_SOLID)  N = "so";
  else if (T == TopAbs_SHELL)  N = "sh";  
  else if (T == TopAbs_FACE)   N = "f"; 
  else if (T == TopAbs_WIRE)   N = "w"; 
  else if (T == TopAbs_EDGE)   N = "e"; 
  else if (T == TopAbs_VERTEX) N = "v"; 
}

//=======================================================================
//function : OrientationToString
//purpose  : 
//=======================================================================

void TestTopOpeDraw_TTOT::OrientationToString
(const TopAbs_Orientation o, TCollection_AsciiString& N)
{
  switch (o) {
  case TopAbs_FORWARD  : N = "FORWARD" ; break;
  case TopAbs_REVERSED : N = "REVERSED"; break;
  case TopAbs_INTERNAL : N = "INTERNAL"; break;
  case TopAbs_EXTERNAL : N = "EXTERNAL"; break;
  }
}

//=======================================================================
//function : StringToKind
//purpose  : 
//=======================================================================

Standard_Boolean TestTopOpeDraw_TTOT::StringToKind
(const TCollection_AsciiString& N, TopOpeBRepDS_Kind& T)
{ 
  char *s = (char*)N.ToCString();
  Standard_Integer ok = 0;
  if      (!strcasecmp(s,"su")) { T = TopOpeBRepDS_SURFACE; ok = 1; }
  else if (!strcasecmp(s,"c"))  { T = TopOpeBRepDS_CURVE; ok = 1; }
  else if (!strcasecmp(s,"p"))  { T = TopOpeBRepDS_POINT; ok = 1; }
  if      (!strcasecmp(s,"co")) { T = TopOpeBRepDS_COMPOUND; ok = 1; }
  if      (!strcasecmp(s,"cs")) { T = TopOpeBRepDS_COMPSOLID; ok = 1; }
  else if (!strcasecmp(s,"so")) { T = TopOpeBRepDS_SOLID; ok = 1; }
  else if (!strcasecmp(s,"sh")) { T = TopOpeBRepDS_SHELL; ok = 1; }
  else if (!strcasecmp(s,"f"))  { T = TopOpeBRepDS_FACE; ok = 1; }
  else if (!strcasecmp(s,"w"))  { T = TopOpeBRepDS_WIRE; ok = 1; }
  else if (!strcasecmp(s,"e"))  { T = TopOpeBRepDS_EDGE; ok = 1; }
  else if (!strcasecmp(s,"v"))  { T = TopOpeBRepDS_VERTEX; ok = 1; }
  return ok != 0;
}

//=======================================================================
//function : KindToString
//purpose  : 
//=======================================================================

void TestTopOpeDraw_TTOT::KindToString
(const TopOpeBRepDS_Kind T, TCollection_AsciiString& N)
{
  if      (T == TopOpeBRepDS_SURFACE) N = "su"; 
  else if (T == TopOpeBRepDS_CURVE)   N = "c";
  else if (T == TopOpeBRepDS_POINT)   N = "p";  
  else if (T == TopOpeBRepDS_COMPOUND)   N = "co";
  else if (T == TopOpeBRepDS_COMPSOLID)   N = "cs";
  else if (T == TopOpeBRepDS_SOLID)   N = "so";
  else if (T == TopOpeBRepDS_SHELL)   N = "sh";  
  else if (T == TopOpeBRepDS_FACE)    N = "f"; 
  else if (T == TopOpeBRepDS_WIRE)    N = "w"; 
  else if (T == TopOpeBRepDS_EDGE)    N = "e"; 
  else if (T == TopOpeBRepDS_VERTEX)  N = "v"; 
}


//=======================================================================
//function : StringToShapeEnum
//purpose  : 
//=======================================================================

Standard_Boolean TestTopOpeDraw_TTOT::StringToShapeEnum
(const TCollection_AsciiString& N, TopAbs_ShapeEnum& T)
{ 
  char *s = (char*)N.ToCString();
  Standard_Integer ok = 0;
  if      (!strcasecmp(s,"s"))   { T = TopAbs_SHAPE; ok = 1; }
  else if (!strcasecmp(s,"co"))  { T = TopAbs_COMPOUND; ok = 1; }
  else if (!strcasecmp(s,"cs"))  { T = TopAbs_COMPSOLID; ok = 1; }
  else if (!strcasecmp(s,"so"))  { T = TopAbs_SOLID; ok = 1; }
  else if (!strcasecmp(s,"sh"))  { T = TopAbs_SHELL; ok = 1; }
  else if (!strcasecmp(s,"f"))   { T = TopAbs_FACE; ok = 1; }
  else if (!strcasecmp(s,"w"))   { T = TopAbs_WIRE; ok = 1; }
  else if (!strcasecmp(s,"e"))   { T = TopAbs_EDGE; ok = 1; }
  else if (!strcasecmp(s,"v"))   { T = TopAbs_VERTEX; ok = 1; }
  return ok != 0;
}


//=======================================================================
//function : ShapeColor
//purpose  : 
//=======================================================================

Draw_ColorKind TestTopOpeDraw_TTOT::ShapeColor
(const TopoDS_Shape& S)
{
  Draw_ColorKind col = Draw_orange;
  switch ( S.ShapeType() ) {
  case TopAbs_COMPOUND : col = Draw_saumon; break;
  case TopAbs_COMPSOLID : col = Draw_blanc; break;
  case TopAbs_SOLID  : col = Draw_violet; break;
  case TopAbs_SHELL  : col = Draw_corail; break;
  case TopAbs_FACE   : col = Draw_vert; break; // col = Draw_jaune; break;
  case TopAbs_WIRE   : col = Draw_cyan; break;
  case TopAbs_EDGE   : col = Draw_magenta; break;
  case TopAbs_VERTEX : col = Draw_orange; break;
  default            : col = Draw_marron;
  }
  return col;
}

Draw_ColorKind TestTopOpeDraw_TTOT::KindColor
(const TopOpeBRepDS_Kind K)
{
  Draw_ColorKind col = Draw_orange;
  if      (K == TopOpeBRepDS_SURFACE) col = Draw_jaune;
  else if (K == TopOpeBRepDS_CURVE)   col = Draw_vert;
  else if (K == TopOpeBRepDS_POINT)   col = Draw_blanc;
  else if (K == TopOpeBRepDS_FACE)    col = Draw_cyan;
  return col;
}

//=======================================================================
//function : GeometryColor
//purpose  : 
//=======================================================================

Draw_ColorKind TestTopOpeDraw_TTOT::GeometryColor
(const TopOpeBRepDS_Kind K)
{
  Draw_ColorKind col = Draw_orange;
  col = KindColor(K);
  return col;
}

//=======================================================================
//function : CurveToString
//purpose  : 
//=======================================================================

void TestTopOpeDraw_TTOT::CurveToString
(const GeomAbs_CurveType t, TCollection_AsciiString& N)
{
  switch(t) {
  case GeomAbs_Line                : N = "LINE";              break;
  case GeomAbs_Circle              : N = "CIRCLE";            break;
  case GeomAbs_Ellipse             : N = "ELLIPSE";           break;
  case GeomAbs_Hyperbola           : N = "HYPERBOLA";         break;
  case GeomAbs_Parabola            : N = "PARABOLA";          break;
  case GeomAbs_BezierCurve         : N = "BEZIER";       break;
  case GeomAbs_BSplineCurve        : N = "BSPLINE";      break;
  case GeomAbs_OtherCurve          : N = "OTHER";        break;
  default                          : N = "UNKNOWN";           break;  
  }
}

//=======================================================================
//function : SurfaceToString
//purpose  : 
//=======================================================================

void TestTopOpeDraw_TTOT::SurfaceToString
(const GeomAbs_SurfaceType t, TCollection_AsciiString& N)
{
  switch(t) {
  case GeomAbs_Plane               : N = "PLANE";              break;
  case GeomAbs_Cylinder            : N = "CYLINDER";            break;
  case GeomAbs_Cone                : N = "CONE";           break;
  case GeomAbs_Sphere              : N = "SPHERE";         break;
  case GeomAbs_Torus               : N = "TORUS";          break;
  case GeomAbs_BezierSurface       : N = "BEZIER";       break;
  case GeomAbs_BSplineSurface      : N = "BSPLINE";      break;
  case GeomAbs_SurfaceOfRevolution : N = "REVOLUTION";        break;
  case GeomAbs_SurfaceOfExtrusion  : N = "EXTRUSION";        break;
  case GeomAbs_OffsetSurface       : N = "OFFSET";        break;
  case GeomAbs_OtherSurface        : N = "OTHER";        break;
  default                          : N = "UNKNOWN";           break;  
  }
}

//=======================================================================
//function : GeometryName
//purpose  : 
//=======================================================================

void TestTopOpeDraw_TTOT::GeometryName
(const Standard_Integer  I, const TopOpeBRepDS_Kind K, TCollection_AsciiString& N)
{ 
  TCollection_AsciiString name; KindToString(K,name); 
  name = name + "_" + TCollection_AsciiString(I);
  N = name;
}

//=======================================================================
//function : CatCurveName
//purpose  : 
//=======================================================================

void TestTopOpeDraw_TTOT::CatCurveName
(const Standard_Integer I, TCollection_AsciiString& N)
{ 
  TCollection_AsciiString n; GeometryName(I,TopOpeBRepDS_CURVE,n); 
  N = N + n;
}

//=======================================================================
//function : CatOrientation
//purpose  : 
//=======================================================================

void TestTopOpeDraw_TTOT::CatOrientation
(const TopAbs_Orientation o,TCollection_AsciiString& N)
{ 
  TCollection_AsciiString s; OrientationToString(o,s);
  s.Trunc(1);
  N = N + "["; N = N + s; N = N + "]";
}

//=======================================================================
//function : CatOrientation
//purpose  : 
//=======================================================================

void TestTopOpeDraw_TTOT::CatOrientation
(const TopoDS_Shape& S,TCollection_AsciiString& N)
{ 
  CatOrientation(S.Orientation(),N);
}

//=======================================================================
//function : CatCurve
//purpose  : 
//=======================================================================

void TestTopOpeDraw_TTOT::CatCurve
(const Handle(Geom_Curve) GC, TCollection_AsciiString& N)
{
  if ( GC.IsNull() ) return;
  GeomAdaptor_Curve GAC(GC); GeomAbs_CurveType t = GAC.GetType();
  TCollection_AsciiString s; CurveToString(t,s); 
  s.Trunc(2);
  N = N + "("; N = N + s; N = N + ")";
}

//=======================================================================
//function : CatSurface
//purpose  : 
//=======================================================================

void TestTopOpeDraw_TTOT::CatSurface
(const Handle(Geom_Surface) GS, TCollection_AsciiString& N)
{
  if ( GS.IsNull() ) return;
  GeomAdaptor_Surface GAS(GS); GeomAbs_SurfaceType t = GAS.GetType();
  TCollection_AsciiString s; SurfaceToString(t,s);
  s.Trunc(2);
  N = N + "("; N = N + s; N = N + ")";
}

//=======================================================================
//function : CatGeometry
//purpose  : 
//=======================================================================

void TestTopOpeDraw_TTOT::CatGeometry
(const TopoDS_Shape& S, TCollection_AsciiString& N)
{
  if ( S.IsNull() ) return;
  const TopAbs_ShapeEnum t = S.ShapeType();
  if      (t == TopAbs_FACE) {
    const TopoDS_Face& F = TopoDS::Face(S);
    TopLoc_Location loc; 
    Handle(Geom_Surface) GS = BRep_Tool::Surface(F,loc);
    CatSurface(GS,N);
  }
  else if (t == TopAbs_EDGE) {
    const TopoDS_Edge& E = TopoDS::Edge(S);
    TopLoc_Location loc; Standard_Real f,l;
    Handle(Geom_Curve) GC = BRep_Tool::Curve(E,loc,f,l);
    CatCurve(GC,N);
  }
}

//=======================================================================
//function : CatCurveDisplayName
//purpose  : 
//=======================================================================

void TestTopOpeDraw_TTOT::CatCurveDisplayName
(const Standard_Integer I, const Handle(Geom_Curve) GC, TCollection_AsciiString& N)
{
  if ( GC.IsNull() ) return;
  CatCurveName(I,N);
  CatCurve(GC,N);
}

//=======================================================================
//function : CurveDisplayName
//purpose  : 
//=======================================================================

void TestTopOpeDraw_TTOT::CurveDisplayName
(const Standard_Integer   I, const Handle(Geom_Curve) GC, TCollection_AsciiString& N)
{
  N = " "; 
  CatCurveDisplayName(I,GC,N);
}

//=======================================================================
//function : ShapeKind
//purpose  : 
//=======================================================================

Standard_Boolean TestTopOpeDraw_TTOT::ShapeKind(const TopoDS_Shape& S,const TopAbs_ShapeEnum TS)
{
  if ( TS == TopAbs_SHAPE ) return Standard_True;
  else return ( S.ShapeType() == TS );
}
