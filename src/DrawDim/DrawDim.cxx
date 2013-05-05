// Created on: 1996-01-10
// Created by: Denis PASCAL
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



#include <DrawDim.ixx>

#include <Draw_Text3D.hxx>
#include <gp_Pnt.hxx>  
#include <TCollection_AsciiString.hxx>
#include <Geom_Curve.hxx>
#include <BRep_Tool.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopExp_Explorer.hxx> 
#include <TopoDS.hxx>
#include <TopAbs.hxx>
#include <Geom_Line.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Plane.hxx>
#include <ElCLib.hxx>
#include <Draw.hxx>
#include <Draw_Appli.hxx>
#include <TopoDS_Vertex.hxx>
#ifdef WNT
Standard_IMPORT Draw_Viewer dout;
#endif

//=======================================================================
//function : AllCommands
//purpose  : 
//=======================================================================

void DrawDim::AllCommands (Draw_Interpretor& theCommands)
{ 
  PlanarDimensionCommands (theCommands);
}


//=======================================================================
//function : DrawShapeName
//purpose  : 
//=======================================================================

void DrawDim::DrawShapeName (const TopoDS_Shape& ashape, 
			     const Standard_CString aname) 
{    
  gp_Pnt position;
  TCollection_AsciiString t (" ");
  switch (ashape.ShapeType()) {
  case TopAbs_EDGE :
    {
      Standard_Real f,l,parameter;
      Handle(Geom_Curve) curve = BRep_Tool::Curve(TopoDS::Edge(ashape),f,l);
      if (curve->IsKind(STANDARD_TYPE(Geom_Line))) {    
	parameter  = (f+l)/2.;  
	position = ElCLib::Value(parameter,Handle(Geom_Line)::DownCast(curve)->Lin());
      }
      else if (curve->IsKind(STANDARD_TYPE(Geom_Circle))) {
	parameter  = (f+l)/2.;
	if (f > l) parameter = parameter + M_PI;  
	position = ElCLib::Value(parameter,Handle(Geom_Circle)::DownCast(curve)->Circ());
      }
    }
    break;
  case TopAbs_VERTEX :
    {
      position = BRep_Tool::Pnt(TopoDS::Vertex(ashape));
    }
    break;
  default:
    break;
  }
  t+=aname; //Name();
  Handle(Draw_Text3D) text = new Draw_Text3D (position,t.ToCString(),Draw_blanc);
  dout << text;
}


//=======================================================================
//function : Pln
//purpose  : 
//=======================================================================

Standard_Boolean DrawDim::Pln (const TopoDS_Face& f, gp_Pln& p)
{
  Handle(Geom_Plane) P = Handle(Geom_Plane)::DownCast(BRep_Tool::Surface(f));
  if (!P.IsNull()) {
    p = P->Pln();
    return Standard_True;
  }
  return Standard_False;
}



//=======================================================================
//function : Lin
//purpose  : 
//=======================================================================

Standard_Boolean DrawDim::Lin (const TopoDS_Edge& e,
			       gp_Lin& l, 
			       Standard_Boolean& infinite,
			       Standard_Real& first,
			       Standard_Real& last)
{  
  Standard_Real f1,l1;
  Handle(Geom_Line) L = Handle(Geom_Line)::DownCast(BRep_Tool::Curve(e,f1,l1));
  if (!L.IsNull()) {  
    TopoDS_Vertex vf, vl;   
    TopExp::Vertices(TopoDS::Edge(e),vf,vl); 
    if (vf.IsNull() && vl.IsNull()) {
      infinite = Standard_True;
      l = L->Lin();
      return Standard_True;
    }
    else if (vf.IsNull() || vl.IsNull()) {
      Standard_DomainError::Raise("DrawDim::Lin : semi infinite edge");
    }
    else {    
      l = L->Lin();   
      infinite = Standard_True;
      first = f1;
      last  = l1; 
      return Standard_True;
    }
  }
  return Standard_False;
}


//=======================================================================
//function : Lin
//purpose  : 
//=======================================================================

Standard_Boolean DrawDim::Circ (const TopoDS_Edge& e,
				gp_Circ& c, 
				Standard_Real& first,
				Standard_Real& last)
{
  Standard_Real f1,l1;
  Handle(Geom_Circle) C = Handle(Geom_Circle)::DownCast(BRep_Tool::Curve(e,f1,l1));
  if (!C.IsNull()) {  
    c = C->Circ();   
    first = f1;
    last  = l1; 
    return Standard_True;
  }
  return Standard_False;
}




//=======================================================================
//function : Nearest
//purpose  : 
//=======================================================================

gp_Pnt DrawDim::Nearest(const TopoDS_Shape& ashape, const gp_Pnt& apoint)
{
  Standard_Real dist = RealLast();
  Standard_Real curdist;
  gp_Pnt result;
  gp_Pnt curpnt;
  TopExp_Explorer explo(ashape,TopAbs_VERTEX);
  while (explo.More()) {
    curpnt = BRep_Tool::Pnt(TopoDS::Vertex(explo.Current()));
    curdist = apoint.Distance(curpnt);
    if (curdist < dist) {
      result = curpnt;
      dist = curdist;
    }
    explo.Next();
  }
  return result;
}
