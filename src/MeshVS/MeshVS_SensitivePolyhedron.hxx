// Created on: 2005-01-21
// Created by: Alexander SOLOVYOV
// Copyright (c) 2005-2014 OPEN CASCADE SAS
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

#ifndef _MeshVS_SensitivePolyhedron_HeaderFile
#define _MeshVS_SensitivePolyhedron_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>

#include <Handle_TColgp_HArray1OfPnt.hxx>
#include <Handle_TColgp_HArray1OfPnt2d.hxx>
#include <Handle_MeshVS_HArray1OfSequenceOfInteger.hxx>
#include <gp_XY.hxx>
#include <NCollection_List.hxx>
#include <Select3D_SensitiveEntity.hxx>
#include <Handle_SelectBasics_EntityOwner.hxx>
#include <Select3D_SensitiveEntity.hxx>
#include <Select3D_BndBox3d.hxx>

class TColgp_HArray1OfPnt;
class TColgp_HArray1OfPnt2d;
class MeshVS_HArray1OfSequenceOfInteger;
class SelectBasics_EntityOwner;
class TColgp_Array1OfPnt;
class Select3D_SensitiveEntity;
class TopLoc_Location;
class TColgp_Array1OfPnt2d;
class Bnd_Box2d;
class TColStd_SequenceOfInteger;
class gp_Lin;
class SelectBasics_ListOfBox2d;

typedef NCollection_List<Handle(TColgp_HArray1OfPnt)> MeshVS_PolyhedronVerts;
typedef NCollection_List<Handle(TColgp_HArray1OfPnt)>::Iterator MeshVS_PolyhedronVertsIter;

//! This class is used to detect selection of a polyhedron. The main
//! principle of detection algorithm is to search for overlap with
//! each polyhedron's face separately, treating them as planar convex
//! polygons.
class MeshVS_SensitivePolyhedron : public Select3D_SensitiveEntity
{
public:

  Standard_EXPORT MeshVS_SensitivePolyhedron (const Handle(SelectBasics_EntityOwner)& theOwner,
                                              const TColgp_Array1OfPnt& theNodes,
                                              const Handle(MeshVS_HArray1OfSequenceOfInteger)& theTopo);

  Standard_EXPORT virtual Handle_Select3D_SensitiveEntity GetConnected() Standard_OVERRIDE;

  Standard_EXPORT virtual Standard_Boolean Matches (SelectBasics_SelectingVolumeManager& theMgr,
                                                    SelectBasics_PickResult& thePickResult) Standard_OVERRIDE;

  //! Returns the amount of nodes of polyhedron
  Standard_EXPORT virtual Standard_Integer NbSubElements() Standard_OVERRIDE;

  Standard_EXPORT virtual Select3D_BndBox3d BoundingBox() Standard_OVERRIDE;

  Standard_EXPORT virtual gp_Pnt CenterOfGeometry() const Standard_OVERRIDE;

  DEFINE_STANDARD_RTTI(MeshVS_SensitivePolyhedron)

private:

  MeshVS_PolyhedronVerts myTopology;
  gp_XYZ myCenter;
  Select3D_BndBox3d myBndBox;
  Handle(TColgp_HArray1OfPnt) myNodes;
  Handle(MeshVS_HArray1OfSequenceOfInteger) myTopo;
};

DEFINE_STANDARD_HANDLE(MeshVS_SensitivePolyhedron, Select3D_SensitiveEntity)

#endif // _MeshVS_SensitivePolyhedron_HeaderFile
