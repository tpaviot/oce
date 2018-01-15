// Copyright (c) 2013 OPEN CASCADE SAS
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


#ifndef _BRepMesh_Vertex_HeaderFile
#define _BRepMesh_Vertex_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>
#include <gp_XY.hxx>
#include <BRepMesh_DegreeOfFreedom.hxx>

//! Light weighted structure representing vertex 
//! of the mesh in parametric space. Vertex could be 
//! associated with 3d point stored in external map.
class BRepMesh_Vertex
{
public:

  DEFINE_STANDARD_ALLOC
  
  //! Default constructor
  Standard_EXPORT BRepMesh_Vertex()
    : myLocation3d(0),
      myMovability(BRepMesh_Free)
  {
  }
  
  //! Creates vertex associated with point in 3d space.
  //! @param theUV position of vertex in parametric space.
  //! @param theLocation3d index of 3d point to be associated with vertex.
  //! @param theMovability movability of the vertex.
  Standard_EXPORT BRepMesh_Vertex(const gp_XY&                   theUV,
                                  const Standard_Integer         theLocation3d,
                                  const BRepMesh_DegreeOfFreedom theMovability)
  {
    Initialize(theUV, theLocation3d, theMovability);
  }
  
  //! Creates vertex without association with point in 3d space.
  //! @param theU U position of vertex in parametric space.
  //! @param theV V position of vertex in parametric space.
  //! @param theMovability movability of the vertex.
  Standard_EXPORT BRepMesh_Vertex(const Standard_Real            theU,
                                  const Standard_Real            theV,
                                  const BRepMesh_DegreeOfFreedom theMovability)
    : myUV(theU, theV),
      myLocation3d(0),
      myMovability(theMovability)
  {}

  //! Initializes vertex associated with point in 3d space.
  //! @param theUV position of vertex in parametric space.
  //! @param theLocation3d index of 3d point to be associated with vertex.
  //! @param theMovability movability of the vertex.
  inline void Initialize(const gp_XY&                   theUV,
                         const Standard_Integer         theLocation3d,
                         const BRepMesh_DegreeOfFreedom theMovability)
  {
    myUV         = theUV;
    myLocation3d = theLocation3d;
    myMovability = theMovability;
  }
  
  //! Returns position of the vertex in parametric space.
  inline const gp_XY& Coord() const
  {
    return myUV;
  }

  //! Returns position of the vertex in parametric space for modification.
  inline gp_XY& ChangeCoord()
  {
    return myUV;
  }
  
  //! Returns index of 3d point associated with the vertex.
  inline Standard_Integer Location3d() const
  {
    return myLocation3d;
  }
  
  //! Returns movability of the vertex.
  inline BRepMesh_DegreeOfFreedom Movability() const
  {
    return myMovability;
  }
  
  //! Sets movability of the vertex.
  inline void SetMovability(const BRepMesh_DegreeOfFreedom theMovability)
  {
    myMovability = theMovability;
  }
  
  //! Returns hash code for this vertex.
  //! @param theUpper upper index in the container.
  //! @return hash code.
  Standard_EXPORT Standard_Integer HashCode(const Standard_Integer Upper) const
  {
    return ::HashCode(Floor(1e5 * myUV.X()) * Floor(1e5 * myUV.Y()), Upper);
  }
  
  //! Checks for equality with another vertex.
  //! @param theOther vertex to be checked against this one.
  //! @return TRUE if equal, FALSE if not.
  Standard_EXPORT Standard_Boolean IsEqual(const BRepMesh_Vertex& theOther) const
  {
    if (myMovability          == BRepMesh_Deleted || 
        theOther.myMovability == BRepMesh_Deleted)
    {
      return Standard_False;
    }

    return (myUV.IsEqual(theOther.myUV, Precision::PConfusion()));
  }

  //! Alias for IsEqual.
  Standard_EXPORT Standard_Boolean operator ==(const BRepMesh_Vertex& Other) const
  {
    return IsEqual(Other);
  }

private:

  gp_XY                     myUV;
  Standard_Integer          myLocation3d;
  BRepMesh_DegreeOfFreedom  myMovability;
};

inline Standard_Integer HashCode(const BRepMesh_Vertex& me, const Standard_Integer Upper)
{
 return me.HashCode(Upper);
}

#endif
