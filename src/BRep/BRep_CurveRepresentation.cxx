// Created on: 1993-07-06
// Created by: Remi LEQUETTE
// Copyright (c) 1993-1999 Matra Datavision
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

#include <BRep_CurveRepresentation.ixx>
#include <TColStd_HArray1OfInteger.hxx>


//=======================================================================
//function : BRep_CurveRepresentation
//purpose  : 
//=======================================================================

BRep_CurveRepresentation::BRep_CurveRepresentation(const TopLoc_Location& L):
       myLocation(L)
{
}


//=======================================================================
//function : IsCurve3D
//purpose  : 
//=======================================================================

Standard_Boolean  BRep_CurveRepresentation::IsCurve3D()const 
{
  return Standard_False;
}


//=======================================================================
//function : IsCurveOnSurface
//purpose  : 
//=======================================================================

Standard_Boolean  BRep_CurveRepresentation::IsCurveOnSurface()const 
{
  return Standard_False;
}


//=======================================================================
//function : IsCurveOnClosedSurface
//purpose  : 
//=======================================================================

Standard_Boolean  BRep_CurveRepresentation::IsCurveOnClosedSurface()const 
{
  return Standard_False;
}


//=======================================================================
//function : IsRegularity
//purpose  : 
//=======================================================================

Standard_Boolean  BRep_CurveRepresentation::IsRegularity()const 
{
  return Standard_False;
}

//=======================================================================
//function : IsCurveOnSurface
//purpose  : 
//=======================================================================

Standard_Boolean  BRep_CurveRepresentation::IsCurveOnSurface
  (const Handle(Geom_Surface)& , const TopLoc_Location& )const 
{
  return Standard_False;
}


//=======================================================================
//function : IsRegularity
//purpose  : 
//=======================================================================

Standard_Boolean  BRep_CurveRepresentation::IsRegularity
  (const Handle(Geom_Surface)& ,
   const Handle(Geom_Surface)& ,
   const TopLoc_Location& , 
   const TopLoc_Location& )const 
{
  return Standard_False;
}

//=======================================================================
//function : IsPolygon3D
//purpose  : 
//=======================================================================

Standard_Boolean  BRep_CurveRepresentation::IsPolygon3D() const
{
  return Standard_False;
}

//=======================================================================
//function : IsPolygonOnTriangulation
//purpose  : 
//=======================================================================

Standard_Boolean  BRep_CurveRepresentation::IsPolygonOnTriangulation() const
{
  return Standard_False;
}


//=======================================================================
//function : IsPolygonOnTriangulation
//purpose  : 
//=======================================================================

Standard_Boolean  BRep_CurveRepresentation::IsPolygonOnTriangulation
  (const Handle(Poly_Triangulation)&, const TopLoc_Location&) const
{
  return Standard_False;
}


//=======================================================================
//function : IsPolygonOnClosedTriangulation
//purpose  : 
//=======================================================================

Standard_Boolean  BRep_CurveRepresentation::IsPolygonOnClosedTriangulation() const
{
  return Standard_False;
}


//=======================================================================
//function : IsPolygonOnClosedSurface
//purpose  : 
//=======================================================================

Standard_Boolean  BRep_CurveRepresentation::IsPolygonOnClosedSurface() const
{
  return Standard_False;
}

//=======================================================================
//function : IsPolygonOnSurface
//purpose  : 
//=======================================================================

Standard_Boolean  BRep_CurveRepresentation::IsPolygonOnSurface() const
{
  return Standard_False;
}

//=======================================================================
//function : IsPolygonOnSurface
//purpose  : 
//=======================================================================

Standard_Boolean  BRep_CurveRepresentation::IsPolygonOnSurface
  (const Handle(Geom_Surface)&, 
   const TopLoc_Location&) const
{
  return Standard_False;
}


//=======================================================================
//function : Curve3D
//purpose  : 
//=======================================================================

const Handle(Geom_Curve)&  BRep_CurveRepresentation::Curve3D()const 
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
  Standard_UNREACHABLE;
    return *((Handle(Geom_Curve)*) NULL);
}

//=======================================================================
//function : Curve3D
//purpose  : 
//=======================================================================

void BRep_CurveRepresentation::Curve3D(const Handle(Geom_Curve)&)
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
}





//=======================================================================
//function : Surface
//purpose  : 
//=======================================================================

const Handle(Geom_Surface)&  BRep_CurveRepresentation::Surface()const 
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
  Standard_UNREACHABLE;
    return *((Handle(Geom_Surface)*) NULL);
}


//=======================================================================
//function : PCurve
//purpose  : 
//=======================================================================

const Handle(Geom2d_Curve)&  BRep_CurveRepresentation::PCurve()const 
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
  Standard_UNREACHABLE;
    return *((Handle(Geom2d_Curve)*) NULL);
}

//=======================================================================
//function : PCurve2
//purpose  : 
//=======================================================================

const Handle(Geom2d_Curve)&  BRep_CurveRepresentation::PCurve2()const 
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
  Standard_UNREACHABLE;
    return *((Handle(Geom2d_Curve)*) NULL);
}

//=======================================================================
//function : PCurve
//purpose  : 
//=======================================================================

void  BRep_CurveRepresentation::PCurve(const Handle(Geom2d_Curve)&)
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
}

//=======================================================================
//function : PCurve2
//purpose  : 
//=======================================================================

void  BRep_CurveRepresentation::PCurve2(const Handle(Geom2d_Curve)&)
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
}


//=======================================================================
//function : Continuity
//purpose  : 
//=======================================================================

const GeomAbs_Shape&  BRep_CurveRepresentation::Continuity()const 
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
  Standard_UNREACHABLE;
    return *((GeomAbs_Shape*) NULL);
}

//=======================================================================
//function : Continuity
//purpose  : 
//=======================================================================

void BRep_CurveRepresentation::Continuity(const GeomAbs_Shape )
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
}


//=======================================================================
//function : Surface2
//purpose  : 
//=======================================================================

const Handle(Geom_Surface)&  BRep_CurveRepresentation::Surface2()const 
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
  Standard_UNREACHABLE;
    return *((Handle(Geom_Surface)*) NULL);
}


//=======================================================================
//function : Location2
//purpose  : 
//=======================================================================

const TopLoc_Location&  BRep_CurveRepresentation::Location2()const 
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
  Standard_UNREACHABLE;
    return *((TopLoc_Location*) NULL);
}



//=======================================================================
//function : Polygon3D
//purpose  : 
//=======================================================================

const Handle(Poly_Polygon3D)&  BRep_CurveRepresentation::Polygon3D()const 
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
  Standard_UNREACHABLE;
    return *((Handle(Poly_Polygon3D)*) NULL);
}

//=======================================================================
//function : Polygon3D
//purpose  : 
//=======================================================================

void BRep_CurveRepresentation::Polygon3D(const Handle(Poly_Polygon3D)&)
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
}


//=======================================================================
//function : Polygon
//purpose  : 
//=======================================================================

const Handle(Poly_Polygon2D)&  BRep_CurveRepresentation::Polygon()const 
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
  Standard_UNREACHABLE;
  return *((Handle(Poly_Polygon2D)*) NULL);
}


//=======================================================================
//function : Polygon
//purpose  : 
//=======================================================================

void BRep_CurveRepresentation::Polygon(const Handle(Poly_Polygon2D)&)
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
}

//=======================================================================
//function : PolygonOnTriangulation2
//purpose  : 
//=======================================================================

const Handle(Poly_PolygonOnTriangulation)& BRep_CurveRepresentation::PolygonOnTriangulation2() const
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
  Standard_UNREACHABLE;
  return *((Handle(Poly_PolygonOnTriangulation)*) NULL);
}

//=======================================================================
//function : PolygonOnTriangulation2
//purpose  : 
//=======================================================================

void BRep_CurveRepresentation::PolygonOnTriangulation2
  (const Handle(Poly_PolygonOnTriangulation)&) 
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
}


//=======================================================================
//function : PolygonOnTriangulation
//purpose  : 
//=======================================================================

void BRep_CurveRepresentation::PolygonOnTriangulation
  (const Handle(Poly_PolygonOnTriangulation)&)
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
}


//=======================================================================
//function : PolygonOnTriangulation
//purpose  : 
//=======================================================================

const Handle(Poly_PolygonOnTriangulation)& BRep_CurveRepresentation::PolygonOnTriangulation()
const
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
  Standard_UNREACHABLE;
  return *(Handle(Poly_PolygonOnTriangulation)*)NULL;
}
//=======================================================================
//function : Triangulation
//purpose  : 
//=======================================================================

const Handle(Poly_Triangulation)& BRep_CurveRepresentation::Triangulation()
const
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
  Standard_UNREACHABLE;
  return *(Handle(Poly_Triangulation)*)NULL;
}



//=======================================================================
//function : Polygon2
//purpose  : 
//=======================================================================

const Handle(Poly_Polygon2D)&  BRep_CurveRepresentation::Polygon2()const 
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
  Standard_UNREACHABLE;
  return *((Handle(Poly_Polygon2D)*) NULL);
}


//=======================================================================
//function : Polygon2
//purpose  : 
//=======================================================================

void BRep_CurveRepresentation::Polygon2(const Handle(Poly_Polygon2D)&)
{
  Standard_DomainError::Raise("BRep_CurveRepresentation");
}

