// Created on: 2011-11-24
// Created by: ANNA MASALSKAYA
// Copyright (c) 2011-2012 OPEN CASCADE SAS
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


#ifndef _BRepBuilderAPI_CellFilter_HeaderFile
#define _BRepBuilderAPI_CellFilter_HeaderFile

#ifndef _gp_XYZ_HeaderFile
#include <gp_XYZ.hxx>
#endif
#ifndef _gp_XY_HeaderFile
#include <gp_XY.hxx>
#endif
#ifndef NCollection_CellFilter_HeaderFile
#include <NCollection_CellFilter.hxx>
#endif
#ifndef _BRepBuilderAPI_VertexInspector_HeaderFile
#include <BRepBuilderAPI_VertexInspector.hxx>
#endif

typedef NCollection_CellFilter<BRepBuilderAPI_VertexInspector> BRepBuilderAPI_CellFilter;

#ifdef __BORLANDC__
  // definition of global functions is needed for map
  Standard_Integer HashCode (const NCollection_CellFilter<BRepBuilderAPI_VertexInspector>::Cell &aCell, const Standard_Integer theUpper)
  { return aCell.HashCode(theUpper); }
  Standard_Boolean IsEqual (const NCollection_CellFilter<BRepBuilderAPI_VertexInspector>::Cell &aCell1, const NCollection_CellFilter<BRepBuilderAPI_VertexInspector>::Cell &aCell2)
  { return aCell1.IsEqual(aCell2); }
#endif

#endif
