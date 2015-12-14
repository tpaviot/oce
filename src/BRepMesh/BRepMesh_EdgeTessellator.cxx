// Created on: 2014-08-13
// Created by: Oleg AGASHIN
// Copyright (c) 2011-2014 OPEN CASCADE SAS
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

#include <BRepMesh_EdgeTessellator.hxx>
#include <Geom_Surface.hxx>
#include <Geom_Plane.hxx>
#include <Geom2d_Curve.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <BRepAdaptor_HSurface.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopLoc_Location.hxx>
#include <BRep_Tool.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TColStd_Array1OfReal.hxx>

IMPLEMENT_STANDARD_HANDLE (BRepMesh_EdgeTessellator, BRepMesh_IEdgeTool)
IMPLEMENT_STANDARD_RTTIEXT(BRepMesh_EdgeTessellator, BRepMesh_IEdgeTool)

//=======================================================================
//function : Constructor
//purpose  : 
//=======================================================================
BRepMesh_EdgeTessellator::BRepMesh_EdgeTessellator(
  const TopoDS_Edge&                               theEdge,
  const Handle(BRepMesh_FaceAttribute)&            theFaceAttribute,
  const TopTools_IndexedDataMapOfShapeListOfShape& theMapOfSharedFaces,
  const Standard_Real                              theLinDeflection,
  const Standard_Real                              theAngDeflection,
  const Standard_Real                              theMinSize)
  : mySurface(theFaceAttribute->Surface())
{
  Standard_Real aPreciseAngDef = 0.5 * theAngDeflection;
  Standard_Real aPreciseLinDef = 0.5 * theLinDeflection;
  if (theEdge.Orientation() == TopAbs_INTERNAL)
    aPreciseLinDef *= 0.5;

  mySquareEdgeDef = aPreciseLinDef * aPreciseLinDef;
  mySquareMinSize = Max(mySquareEdgeDef, theMinSize * theMinSize);

  Standard_Boolean isSameParam = BRep_Tool::SameParameter(theEdge);
  if (isSameParam)
    myCOnS.Initialize(theEdge);
  else
    myCOnS.Initialize(theEdge, theFaceAttribute->Face());

  TopLoc_Location aLoc;
  const GeomAbs_CurveType aCurveType = myCOnS.GetType();
  Standard_Integer aMinPntNb = (aCurveType == GeomAbs_Circle) ? 4 : 2; //OCC287

  // Get range on 2d curve
  Standard_Real aFirstParam, aLastParam;
  BRep_Tool::Range(theEdge, theFaceAttribute->Face(), aFirstParam, aLastParam);
  myTool = new BRepMesh_GeomTool(myCOnS, aFirstParam, aLastParam, 
    aPreciseLinDef, aPreciseAngDef, aMinPntNb, theMinSize);

  if (aCurveType == GeomAbs_BSplineCurve)
  {
    // bug24220
    const Standard_Integer aNbInt = myCOnS.NbIntervals(GeomAbs_C1);
    if ( aNbInt > 0 )
    {
      TColStd_Array1OfReal anIntervals( 1, aNbInt + 1 );
      myCOnS.Intervals(anIntervals, GeomAbs_C1);
      for (Standard_Integer aIntIt = 1; aIntIt <= aNbInt; ++aIntIt)
      {
        const Standard_Real& aStartInt = anIntervals.Value( aIntIt );
        const Standard_Real& anEndInt  = anIntervals.Value( aIntIt + 1 );

        BRepMesh_GeomTool aDetalizator(myCOnS, aStartInt, anEndInt,
          aPreciseLinDef, aPreciseAngDef, aMinPntNb, theMinSize);

        Standard_Integer aNbAddNodes = aDetalizator.NbPoints();
        for ( Standard_Integer aNodeIt = 1; aNodeIt <= aNbAddNodes; ++aNodeIt )
        {
          Standard_Real aParam;
          gp_Pnt        aPoint3d;
          gp_Pnt2d      aPoint2d;
          aDetalizator.Value( aNodeIt, mySurface, aParam, aPoint3d, aPoint2d );
          myTool->AddPoint( aPoint3d, aParam, Standard_False );
        }
      }
    }
  }

  // PTv, chl/922/G9, Take into account internal vertices
  // it is necessary for internal edges, which do not split other edges, by their vertex
  TopExp_Explorer aVertexIt(theEdge, TopAbs_VERTEX);
  for (; aVertexIt.More(); aVertexIt.Next())
  {
    const TopoDS_Vertex& aVertex = TopoDS::Vertex(aVertexIt.Current());
    if (aVertex.Orientation() != TopAbs_INTERNAL)
      continue;

    myTool->AddPoint(BRep_Tool::Pnt(aVertex), 
      BRep_Tool::Parameter(aVertex, theEdge), Standard_True);
  }

  Standard_Integer aNodesNb = myTool->NbPoints();
  //Check deflection in 2d space for improvement of edge tesselation.
  if( isSameParam && aNodesNb > 1)
  {
    const TopTools_ListOfShape& aSharedFaces = theMapOfSharedFaces.FindFromKey(theEdge);
    TopTools_ListIteratorOfListOfShape aFaceIt(aSharedFaces);
    for (; aFaceIt.More(); aFaceIt.Next())
    {
      TopLoc_Location aLoc;
      const TopoDS_Face&   aFace = TopoDS::Face(aFaceIt.Value());
      Handle(Geom_Surface) aSurf = BRep_Tool::Surface(aFace, aLoc);

      if (aSurf->IsInstance(STANDARD_TYPE(Geom_Plane)))
        continue;

      Standard_Real aF, aL;
      Handle(Geom2d_Curve) aCurve2d = BRep_Tool::CurveOnSurface(theEdge, aFace, aF, aL);
      if ( Abs(aF - aFirstParam) > Precision::PConfusion() ||
           Abs(aL - aLastParam ) > Precision::PConfusion() )
      {
        continue;
      }

      aNodesNb = myTool->NbPoints();
      TColStd_Array1OfReal aParamArray(1, aNodesNb);
      for (Standard_Integer i = 1; i <= aNodesNb; ++i)
      {
        gp_Pnt2d      aTmpUV;
        gp_Pnt        aTmpPnt;
        Standard_Real aParam;
        myTool->Value(i, mySurface, aParam, aTmpPnt, aTmpUV);
        aParamArray.SetValue(i, aParam);
      }

      for (Standard_Integer i = 1; i < aNodesNb; ++i)
        splitSegment(aSurf, aCurve2d, aParamArray(i), aParamArray(i + 1), 1);
    }
  }
}

//=======================================================================
//function : Value
//purpose  : 
//=======================================================================
void BRepMesh_EdgeTessellator::Value(const Standard_Integer theIndex,
                                     Standard_Real&         theParameter,
                                     gp_Pnt&                thePoint,
                                     gp_Pnt2d&              theUV)
{
  myTool->Value(theIndex, mySurface, theParameter, thePoint, theUV);
}

//=======================================================================
//function : splitSegment
//purpose  : 
//=======================================================================
void BRepMesh_EdgeTessellator::splitSegment(
  const Handle(Geom_Surface)& theSurf,
  const Handle(Geom2d_Curve)& theCurve2d,
  const Standard_Real         theFirst,
  const Standard_Real         theLast,
  const Standard_Integer      theNbIter)
{
  // limit iteration depth
  if(theNbIter > 10)
    return;

  gp_Pnt2d uvf, uvl, uvm;
  gp_Pnt   P3dF, P3dL, midP3d, midP3dFromSurf;
  Standard_Real midpar;
  
  if(Abs(theLast - theFirst) < 2 * Precision::PConfusion())
    return;

  theCurve2d->D0(theFirst, uvf);
  theCurve2d->D0(theLast,  uvl);

  P3dF = theSurf->Value(uvf.X(), uvf.Y());
  P3dL = theSurf->Value(uvl.X(), uvl.Y());
  
  if(P3dF.SquareDistance(P3dL) < mySquareMinSize)
    return;

  uvm = gp_Pnt2d((uvf.XY() + uvl.XY())*0.5);
  midP3dFromSurf = theSurf->Value(uvm.X(), uvm.Y());

  gp_XYZ Vec1 = midP3dFromSurf.XYZ() - P3dF.XYZ();
  if(Vec1.SquareModulus() < mySquareMinSize)
    return;

  gp_XYZ aVec = P3dL.XYZ() - P3dF.XYZ();
  aVec.Normalize();

  Standard_Real aModulus = Vec1.Dot(aVec);
  gp_XYZ aProj = aVec * aModulus;
  gp_XYZ aDist = Vec1 - aProj;

  if(aDist.SquareModulus() < mySquareEdgeDef)
    return;

  midpar = (theFirst + theLast) * 0.5;
  myCOnS.D0(midpar, midP3d);
  myTool->AddPoint(midP3d, midpar, Standard_False);

  splitSegment(theSurf, theCurve2d, theFirst, midpar, theNbIter + 1);
  splitSegment(theSurf, theCurve2d, midpar, theLast,  theNbIter + 1); 
}
