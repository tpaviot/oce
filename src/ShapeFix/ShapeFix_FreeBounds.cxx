// Created on: 1998-09-16
// Created by: Roman LYGIN
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

// 25.12.98 pdn: renaming methods GetWires and GetEdges to GetClosedWires
//               and GetOpenWires respectively

#include <ShapeFix_FreeBounds.ixx>

#include <BRep_Builder.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_DataMapOfShapeShape.hxx>

#include <ShapeExtend_Explorer.hxx>
#include <ShapeAnalysis_FreeBounds.hxx>

//=======================================================================
//function : ShapeFix_FreeBounds
//purpose  : 
//=======================================================================

ShapeFix_FreeBounds::ShapeFix_FreeBounds() {}

//=======================================================================
//function : ShapeFix_FreeBounds
//purpose  : 
//=======================================================================

ShapeFix_FreeBounds::ShapeFix_FreeBounds(const TopoDS_Shape& shape,
					 const Standard_Real sewtoler,
					 const Standard_Real closetoler,
					 const Standard_Boolean splitclosed,
					 const Standard_Boolean splitopen) :
       myShared (Standard_False), mySewToler (sewtoler), myCloseToler (closetoler),
       mySplitClosed (splitclosed), mySplitOpen (splitopen)
{
  myShape = shape;
  Perform();
}

//=======================================================================
//function : ShapeFix_FreeBounds
//purpose  : 
//=======================================================================

ShapeFix_FreeBounds::ShapeFix_FreeBounds(const TopoDS_Shape& shape,
					 const Standard_Real closetoler,
					 const Standard_Boolean splitclosed,
					 const Standard_Boolean splitopen):
       myShared (Standard_True), mySewToler (0.), myCloseToler (closetoler),
       mySplitClosed (splitclosed), mySplitOpen (splitopen)
{
  myShape = shape;
  Perform();
}

//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================

Standard_Boolean ShapeFix_FreeBounds::Perform() 
{
  ShapeAnalysis_FreeBounds safb;
  if (myShared)
    safb = ShapeAnalysis_FreeBounds (myShape, mySplitClosed, mySplitOpen);
  else
    safb = ShapeAnalysis_FreeBounds (myShape, mySewToler, mySplitClosed, mySplitOpen);
  
  myWires = safb.GetClosedWires();
  myEdges = safb.GetOpenWires();
  
  if (myCloseToler > mySewToler) {
    ShapeExtend_Explorer see;
    Handle(TopTools_HSequenceOfShape) newwires,
                                      open = see.SeqFromCompound (myEdges,
								  Standard_False);
    TopTools_DataMapOfShapeShape vertices;
    ShapeAnalysis_FreeBounds::ConnectWiresToWires (open, myCloseToler, myShared,
						   newwires, vertices);
    myEdges.Nullify();
    ShapeAnalysis_FreeBounds::DispatchWires (newwires, myWires, myEdges);
    
    for( TopExp_Explorer exp (myShape, TopAbs_EDGE); exp.More(); exp.Next()) {
      TopoDS_Edge Edge = TopoDS::Edge(exp.Current());
      for( TopoDS_Iterator iter (Edge); iter.More(); iter.Next()) {
	TopoDS_Vertex V = TopoDS::Vertex (iter.Value());
	BRep_Builder B;
	TopoDS_Vertex newV;
	if( vertices.IsBound(V)) {
	  newV = TopoDS::Vertex (vertices.Find(V));
	  newV.Orientation(V.Orientation());
	  B.Remove(Edge, V);
	  B.Add(Edge, newV);
	}
      }
    }
  }
  return Standard_True;
}
