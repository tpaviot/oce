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

#ifndef _BRepMesh_DiscretRoot_HeaderFile
#define _BRepMesh_DiscretRoot_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <TopoDS_Shape.hxx>
#include <Standard_Transient.hxx>

//! This is a common interface for meshing algorithms 
//! instantiated by Mesh Factory and implemented by plugins.
class BRepMesh_DiscretRoot : public Standard_Transient
{
public:
  
  //! Destructor
  Standard_EXPORT virtual ~BRepMesh_DiscretRoot();

  //! Setup linear deflection.
  inline void SetDeflection(const Standard_Real theDeflection)
  {
    myDeflection = theDeflection;
  }
  
  //! Returns linear deflection.
  inline Standard_Real Deflection() const
  {
    return myDeflection;
  }
  
  //! Setup angular deflection.
  inline void SetAngle(const Standard_Real theAngle)
  {
    myAngle = theAngle;
  }
  
  //! Returns angular deflection.
  inline Standard_Real Angle() const
  {
    return myAngle;
  }
  
  //! Set the shape to triangulate.
  inline void SetShape(const TopoDS_Shape& theShape)
  {
    myShape = theShape;
  }
  
  inline const TopoDS_Shape& Shape() const
  {
    return myShape;
  }
  
  //! Returns true if triangualtion was performed and has success.
  inline Standard_Boolean IsDone() const
  {
    return myIsDone;
  }

  //! Compute triangulation for set shape.
  Standard_EXPORT virtual void Perform() = 0;


  DEFINE_STANDARD_RTTI(BRepMesh_DiscretRoot)

protected:
  
  //! Constructor
  Standard_EXPORT BRepMesh_DiscretRoot();
  
  //! Sets IsDone flag.
  inline void setDone()
  {
    myIsDone = Standard_True;
  }
  
  //! Clears IsDone flag.
  inline void setNotDone()
  {
    myIsDone = Standard_False;
  }
  
  Standard_EXPORT virtual void init();

  Standard_Real     myDeflection;
  Standard_Real     myAngle;
  TopoDS_Shape      myShape;
  Standard_Boolean  myIsDone;
};

DEFINE_STANDARD_HANDLE(BRepMesh_DiscretRoot, Standard_Transient)

#endif
