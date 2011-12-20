// File:        BRepMesh_CellFilter.hxx
// Created:     May 26 16:40:53 2008
// Author:      Ekaterina SMIRNOVA
// Copyright:   Open CASCADE SAS 2008


#include <gp_XYZ.hxx>
#include <gp_XY.hxx>
#include <NCollection_CellFilter.hxx>
#include <BRepMesh_CircleInspector.hxx>

typedef NCollection_CellFilter<BRepMesh_CircleInspector> BRepMesh_CellFilter;

#ifdef __BORLANDC__
  // definition of global functions is needed for map
  Standard_Integer HashCode (const NCollection_CellFilter<BRepMesh_CircleInspector>::Cell &aCell, const Standard_Integer theUpper)
  { return aCell.HashCode(theUpper); }
  Standard_Boolean IsEqual (const NCollection_CellFilter<BRepMesh_CircleInspector>::Cell &aCell1, const NCollection_CellFilter<BRepMesh_CircleInspector>::Cell &aCell2)
  { return aCell1.IsEqual(aCell2); }
#endif