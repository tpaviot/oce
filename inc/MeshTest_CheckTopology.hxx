// File:      MeshTest_CheckTopology.hxx
// Created:   5.10.2004
// Author:    Michael SAZONOV
// Copyright: Open CASCADE 2004

#ifndef MeshTest_CheckTopology_HeaderFile
#define MeshTest_CheckTopology_HeaderFile

#include <TopoDS_Shape.hxx>
#include <NCollection_IndexedDataMap.hxx>
#include <TColStd_SequenceOfInteger.hxx>
#include <TColStd_SequenceOfReal.hxx>

//! This class checks topology of the mesh presented by
//! triangulations of faces.
//!
//! The following error are reported:
//! - free links. A link is considered free if it has only one
//!   neighboring triangle and at least one of its nodes belongs to
//!   interior of the face rather than to its boundary.
//! - cross face errors. It is a situation when a point on a common
//!   boundary between two faces has different 3d coordinates on each
//!   triangulation. The error is reported if the distance is greater
//!   than a deflection written in triangulations.
//! - asynchronous edges. It is an edge having polygons on two neighboring
//!   triangulations with different number of points in the polygons.
//! - free nodes -- nodes not shared by any triangle.

class MeshTest_CheckTopology
{
public:
  //! constructor
  MeshTest_CheckTopology(const TopoDS_Shape& theShape)
    : myShape(theShape) {}

  //! performs checking
  Standard_EXPORT void Perform();

  //! returns the number of faces with free links
  Standard_Integer NbFacesWithFL() const
  { return myMapFaceLinks.Extent(); }

  //! returns the number (in the shape) of a face with free links
  //! with the given index
  Standard_Integer GetFaceNumWithFL(const Standard_Integer theIndex) const
  { return myMapFaceLinks.FindKey(theIndex); }

  //! returns the number free links on a face with the given index
  Standard_Integer NbFreeLinks(const Standard_Integer theIndex) const
  { return myMapFaceLinks(theIndex).Length() / 2; }

  //! gets the numbers of nodes of a free link with the given index
  //! in the face with the given index
  Standard_EXPORT void GetFreeLink(const Standard_Integer theFaceIndex,
				   const Standard_Integer theLinkIndex,
				   Standard_Integer& theNode1,
				   Standard_Integer& theNode2) const;

  //! returns the number of cross face errors
  Standard_Integer NbCrossFaceErrors() const
  { return myErrorsVal.Length(); }

  //! gets the attributes of a cross face error with the given index
  Standard_EXPORT void GetCrossFaceError(const Standard_Integer theIndex,
					 Standard_Integer& theFace1,
					 Standard_Integer& theNode1,
					 Standard_Integer& theFace2,
					 Standard_Integer& theNode2,
					 Standard_Real&    theValue) const;

  //! returns the number of async edges
  Standard_Integer NbAsyncEdges() const
  { return myAsyncEdges.Length(); }

  //! returns the number (in the shape) of an async edge with the given index
  Standard_Integer GetAsyncEdgeNum(const Standard_Integer theIndex) const
  { return myAsyncEdges(theIndex); }

  //! returns the number of free nodes
  Standard_Integer NbFreeNodes() const
  { return myFreeNodeFaces.Length(); }

  //! returns the number of face containing the Index-th detected free node,
  //! and number of this node in the triangulation of that face
  void GetFreeNodeNum (const Standard_Integer theIndex, 
                       Standard_Integer& theFaceNum, 
		       Standard_Integer& theNodeNum) const
  { 
    theFaceNum = myFreeNodeFaces(theIndex);
    theNodeNum = myFreeNodeNums(theIndex);
  }

private:
  TopoDS_Shape myShape;
  NCollection_IndexedDataMap<Standard_Integer,TColStd_SequenceOfInteger>
               myMapFaceLinks;

  TColStd_SequenceOfInteger myErrors;
  TColStd_SequenceOfReal    myErrorsVal;

  TColStd_SequenceOfInteger myAsyncEdges;
  TColStd_SequenceOfInteger myFreeNodeFaces;
  TColStd_SequenceOfInteger myFreeNodeNums;
};

#endif
