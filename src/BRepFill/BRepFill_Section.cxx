// Created on: 1998-07-22
// Created by: Philippe MANGIN
// Copyright (c) 1998-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <BRepFill_Section.ixx>

#include <TopoDS.hxx>
#include <BRep_Builder.hxx>
#include <TopoDS_Edge.hxx>


BRepFill_Section::BRepFill_Section() :islaw(0), contact(0), correction(0)
{
}


BRepFill_Section::BRepFill_Section(const TopoDS_Shape& Profile,
				   const TopoDS_Vertex& V,
				   const Standard_Boolean WithContact,
				   const Standard_Boolean WithCorrection) 
                                  : vertex(V),
				    islaw(0),contact(WithContact),
				    correction(WithCorrection)
{
  if (Profile.ShapeType() == TopAbs_WIRE)
    wire = TopoDS::Wire(Profile);
  else if (Profile.ShapeType() == TopAbs_VERTEX)
    {
      TopoDS_Vertex aVertex = TopoDS::Vertex(Profile);
      BRep_Builder BB;
      
      TopoDS_Edge DegEdge;
      BB.MakeEdge( DegEdge );
      BB.Add( DegEdge, aVertex.Oriented(TopAbs_FORWARD) );
      BB.Add( DegEdge, aVertex.Oriented(TopAbs_REVERSED) );
      BB.Degenerated( DegEdge, Standard_True );
      
      BB.MakeWire( wire );
      BB.Add( wire, DegEdge );
      wire.Closed( Standard_True );
    }
  else
    Standard_Failure::Raise("BRepFill_Section: bad shape type of section");
}

void BRepFill_Section::Set(const Standard_Boolean IsLaw)
{
  islaw = IsLaw;
}
