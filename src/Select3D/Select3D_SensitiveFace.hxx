// Created on: 1995-03-27
// Created by: Robert COUBLANC
// Copyright (c) 1995-1999 Matra Datavision
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

//Modif on jun-24-97 : introduction de CSLib_Class2d de LBR
//                     pour teste si on est dedans ou dehors...
//Modif on jul-21-97 : changement en harray1 pour eventuelles connexions ...

#ifndef _Select3D_SensitiveFace_HeaderFile
#define _Select3D_SensitiveFace_HeaderFile

#include <Standard_DefineHandle.hxx>

#include <Select3D_TypeOfSensitivity.hxx>
#include <Select3D_SensitiveSet.hxx>
#include <Handle_SelectBasics_EntityOwner.hxx>
#include <Handle_TColgp_HArray1OfPnt.hxx>
#include <Standard_Boolean.hxx>
#include <SelectBasics_SelectingVolumeManager.hxx>
#include <Standard_Real.hxx>
#include <Standard_OStream.hxx>

class Standard_ConstructionError;
class Standard_OutOfRange;
class SelectBasics_EntityOwner;
class TColgp_Array1OfPnt;
class TColgp_HArray1OfPnt;
class TopLoc_Location;


//! Sensitive Entity to make a face selectable.
//! In some cases this class can raise Standard_ConstructionError and
//! Standard_OutOfRange exceptions. For more details see Select3D_SensitivePoly.
class Select3D_SensitiveFace : public Select3D_SensitiveEntity
{
public:

  //! Constructs a sensitive face object defined by the
  //! owner theOwnerId, the array of points thePoints, and
  //! the sensitivity type theType.
  //! The array of points is the outer polygon of the geometric face.
  Standard_EXPORT Select3D_SensitiveFace (const Handle(SelectBasics_EntityOwner)& theOwnerId,
                                          const TColgp_Array1OfPnt& thePoints,
                                          const Select3D_TypeOfSensitivity theType);

  //! Constructs a sensitive face object defined by the
  //! owner theOwnerId, the array of points thePoints, and
  //! the sensitivity type theType.
  //! The array of points is the outer polygon of the geometric face.
  Standard_EXPORT Select3D_SensitiveFace (const Handle(SelectBasics_EntityOwner)& theOwnerId,
                                          const Handle(TColgp_HArray1OfPnt)& thePoints,
                                          const Select3D_TypeOfSensitivity theType);

  //! Initializes the given array theHArrayOfPnt by 3d
  //! coordinates of vertices of the face
  Standard_EXPORT void GetPoints (Handle(TColgp_HArray1OfPnt)& theHArrayOfPnt);

  //! Checks whether the face overlaps current selecting volume
  Standard_EXPORT virtual Standard_Boolean Matches (SelectBasics_SelectingVolumeManager& theMgr,
                                                    SelectBasics_PickResult& thePickResult) Standard_OVERRIDE;

  Standard_EXPORT virtual Handle(Select3D_SensitiveEntity) GetConnected() Standard_OVERRIDE;

  //! Returns bounding box of the face. If location transformation
  //! is set, it will be applied
  Standard_EXPORT virtual Select3D_BndBox3d BoundingBox() Standard_OVERRIDE;

  //! Returns center of the face. If location transformation
  //! is set, it will be applied
  Standard_EXPORT virtual gp_Pnt CenterOfGeometry() const Standard_OVERRIDE;

  //! Builds BVH tree for the face
  Standard_EXPORT virtual void BVH() Standard_OVERRIDE;

  //! Returns the amount of sub-entities (points or planar convex polygons)
  Standard_EXPORT virtual Standard_Integer NbSubElements() Standard_OVERRIDE;

  DEFINE_STANDARD_RTTI(Select3D_SensitiveFace)

private:

  Select3D_TypeOfSensitivity    mySensType;       //!< Type of sensitivity: interior or boundary
  Handle(Select3D_SensitiveSet) myFacePoints;     //!< Wrapper for overlap detection created depending on sensitivity type
};

DEFINE_STANDARD_HANDLE(Select3D_SensitiveFace, Select3D_SensitiveEntity)

#endif // _Select3D_SensitiveFace_HeaderFile
