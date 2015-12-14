// Created on: 2014-05-22
// Created by: Varvara POSKONINA
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

#include <SelectMgr_BaseFrustum.hxx>

//=======================================================================
// function : SelectMgr_SelectingVolume
// purpose  : Creates new selecting volume with pixel toletance set to 2,
//            orthographic camera and empty frustum builder
//=======================================================================
SelectMgr_BaseFrustum::SelectMgr_BaseFrustum()
: myPixelTolerance (2),
  myIsOrthographic (Standard_True)
{
  myBuilder = new SelectMgr_FrustumBuilder();
}

//=======================================================================
// function : SetCamera
// purpose  : Passes camera projection and orientation matrices to builder
//=======================================================================
void SelectMgr_BaseFrustum::SetCamera (const Handle(Graphic3d_Camera)& theCamera)
{
  myBuilder->SetOrientation (theCamera->OrientationMatrix());
  myBuilder->SetProjection (theCamera->ProjectionMatrix());
  myIsOrthographic = theCamera->IsOrthographic();
  myBuilder->InvalidateViewport();
}

//=======================================================================
// function : SetCamera
// purpose  : Passes camera projection and orientation matrices to builder
//=======================================================================
void SelectMgr_BaseFrustum::SetCamera (const Graphic3d_Mat4d& theProjection,
                                       const Graphic3d_Mat4d& theOrientation,
                                       const Standard_Integer theIsOrthographic)
{
  myBuilder->SetOrientation (theOrientation);
  myBuilder->SetProjection (theProjection);
  myIsOrthographic = theIsOrthographic;
}

//=======================================================================
// function : SetViewport
// purpose  : Passes viewport parameters to builder
//=======================================================================
void SelectMgr_BaseFrustum::SetViewport (const Standard_Real theX,
                                         const Standard_Real theY,
                                         const Standard_Real theWidth,
                                         const Standard_Real theHeight)
{
  myBuilder->SetViewport (theX, theY, theWidth, theHeight);
}

//=======================================================================
// function : SetPixelTolerance
// purpose  :
//=======================================================================
void SelectMgr_BaseFrustum::SetPixelTolerance (const Standard_Integer theTol)
{
  myPixelTolerance = theTol;
}

//=======================================================================
// function : SetWindowSize
// purpose  :
//=======================================================================
void SelectMgr_BaseFrustum::SetWindowSize (const Standard_Integer theWidth, const Standard_Integer theHeight)
{
  myBuilder->SetWindowSize (theWidth, theHeight);
}

//=======================================================================
// function : SetBuilder
// purpose  :
//=======================================================================
void SelectMgr_BaseFrustum::SetBuilder (const Handle(SelectMgr_FrustumBuilder)& theBuilder)
{
  myBuilder.Nullify();
  myBuilder = theBuilder;
}

//=======================================================================
// function : Overlaps
// purpose  : SAT intersection test between defined volume and
//            given axis-aligned box
//=======================================================================
Standard_Boolean SelectMgr_BaseFrustum::Overlaps (const SelectMgr_Vec3& /*theBoxMin*/,
                                                  const SelectMgr_Vec3& /*theBoxMax*/,
                                                  Standard_Real& /*theDepth*/)
{
  return Standard_False;
}

//=======================================================================
// function : Overlaps
// purpose  : Intersection test between defined volume and given point
//=======================================================================
Standard_Boolean SelectMgr_BaseFrustum::Overlaps (const SelectMgr_Vec3& /*theBoxMin*/,
                                                  const SelectMgr_Vec3& /*theBoxMax*/,
                                                  Standard_Boolean*     /*theInside*/)
{
  return Standard_False;
}

//=======================================================================
// function : Overlaps
// purpose  : Intersection test between defined volume and given point
//=======================================================================
Standard_Boolean SelectMgr_BaseFrustum::Overlaps (const gp_Pnt& /*thePnt*/,
                                                  Standard_Real& /*theDepth*/)
{
  return Standard_False;
}

//=======================================================================
// function : Overlaps
// purpose  : Intersection test between defined volume and given point
//=======================================================================
Standard_Boolean SelectMgr_BaseFrustum::Overlaps (const gp_Pnt& /*thePnt*/)
{
  return Standard_False;
}

//=======================================================================
// function : Overlaps
// purpose  : SAT intersection test between defined volume and given
//            ordered set of points, representing line segments. The test
//            may be considered of interior part or boundary line defined
//            by segments depending on given sensitivity type
//=======================================================================
Standard_Boolean SelectMgr_BaseFrustum::Overlaps (const Handle(TColgp_HArray1OfPnt)& /*theArrayOfPnts*/,
                                                  Select3D_TypeOfSensitivity /*theSensType*/,
                                                  Standard_Real& /*theDepth*/)
{
  return Standard_False;
}

//=======================================================================
// function : Overlaps
// purpose  : SAT intersection test between defined volume and given
//            triangle. The test may be considered of interior part or
//            boundary line defined by triangle vertices depending on
//            given sensitivity type
//=======================================================================
Standard_Boolean SelectMgr_BaseFrustum::Overlaps (const gp_Pnt& /*thePt1*/,
                                                  const gp_Pnt& /*thePt2*/,
                                                  const gp_Pnt& /*thePt3*/,
                                                  Select3D_TypeOfSensitivity /*theSensType*/,
                                                  Standard_Real& /*theDepth*/)
{
  return Standard_False;
}

//=======================================================================
// function : Overlaps
// purpose  : Checks if line segment overlaps selecting volume
//=======================================================================
Standard_Boolean SelectMgr_BaseFrustum::Overlaps (const gp_Pnt& /*thePnt1*/,
                                                  const gp_Pnt& /*thePnt2*/,
                                                  Standard_Real& /*theDepth*/)
{
  return Standard_False;
}

//=======================================================================
// function : DistToGeometryCenter
// purpose  : Measures distance between 3d projection of user-picked
//            screen point and given point theCOG
//=======================================================================
Standard_Real SelectMgr_BaseFrustum::DistToGeometryCenter (const gp_Pnt& /*theCOG*/)
{
  return DBL_MAX;
}

gp_Pnt SelectMgr_BaseFrustum::DetectedPoint (const Standard_Real /*theDepth*/) const
{
  return gp_Pnt (RealLast(), RealLast(), RealLast());
}

//=======================================================================
// function : IsClipped
// purpose  : Checks if the point of sensitive in which selection was
//            detected belongs to the region defined by clipping planes
//=======================================================================
Standard_Boolean SelectMgr_BaseFrustum::IsClipped (const Graphic3d_SequenceOfHClipPlane& /*thePlanes*/,
                                                   const Standard_Real /*theDepth*/)
{
  return Standard_True;
}
