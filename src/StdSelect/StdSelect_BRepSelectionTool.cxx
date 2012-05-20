// Created on: 1995-03-14
// Created by: Robert COUBLANC
// Copyright (c) 1995-1999 Matra Datavision
// Copyright (c) 1999-2012 OPEN CASCADE SAS
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


#include <StdSelect_BRepSelectionTool.ixx>
#include <GeomAdaptor_Curve.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <Select3D_SensitivePoint.hxx>
#include <StdSelect_BRepOwner.hxx>
#include <TopoDS.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <GeomAbs_SurfaceType.hxx>
#include <BRepBndLib.hxx>
#include <Bnd_Box.hxx>
#include <BRep_Tool.hxx>
#include <Geom_Circle.hxx>
#include <Select3D_SensitiveCircle.hxx>
#include <Select3D_SensitiveCurve.hxx>
#include <Select3D_SensitiveSegment.hxx>
#include <Select3D_SensitiveWire.hxx>
#include <Select3D_SensitiveFace.hxx>
#include <Select3D_SensitiveBox.hxx>
#include <Select3D_SensitiveTriangulation.hxx>
#include <Select3D_SensitiveTriangle.hxx>
#include <Select3D_SensitiveGroup.hxx>

#include <Select3D_ListIteratorOfListOfSensitive.hxx>
#include <Select3D_ListOfSensitiveTriangle.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <TColgp_SequenceOfPnt.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <BRep_Tool.hxx>
#include <BRepTools.hxx>
#include <Select3D_TypeOfSensitivity.hxx>
#include <Precision.hxx>
#include <gp_Circ.hxx>
#include <GCPnts_TangentialDeflection.hxx>
#include <TopoDS_Wire.hxx>
#include <Poly_Array1OfTriangle.hxx>
#include <Poly_Polygon3D.hxx>
#include <Poly_PolygonOnTriangulation.hxx>
#include <Poly_Triangulation.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <Standard_NullObject.hxx>
#include <Standard_ErrorHandler.hxx>

//==================================================
// Function: Load
// Purpose :
//==================================================
void StdSelect_BRepSelectionTool
::Load (const Handle(SelectMgr_Selection)& theSelection,
        const TopoDS_Shape& theShape,
        const TopAbs_ShapeEnum theType,
        const Standard_Real theDeflection,
        const Standard_Real theDeviationAngle,
        const Standard_Boolean isAutoTriangulation,
        const Standard_Integer thePriority,
        const Standard_Integer theNbPOnEdge,
        const Standard_Real theMaxParam)
{
  Standard_Integer aPriority = (thePriority == -1) ? GetStandardPriority (theShape, theType) : thePriority;

  if( isAutoTriangulation && !BRepTools::Triangulation (theShape, Precision::Infinite()) )
  {
    BRepMesh_IncrementalMesh(theShape, theDeflection, Standard_False, theDeviationAngle);
  }

  Handle(StdSelect_BRepOwner) aBrepOwner;
  switch (theType)
  {
    case TopAbs_VERTEX:
    case TopAbs_EDGE:
    case TopAbs_WIRE:
    case TopAbs_FACE:
    case TopAbs_SHELL:
    case TopAbs_SOLID:
    case TopAbs_COMPSOLID:
    {
      TopTools_IndexedMapOfShape aSubShapes;
      TopExp::MapShapes (theShape, theType, aSubShapes);

      Standard_Boolean isComesFromDecomposition = !((aSubShapes.Extent() == 1) && (theShape == aSubShapes (1)));
      for (Standard_Integer aShIndex = 1; aShIndex <= aSubShapes.Extent(); ++aShIndex)
      {
        const TopoDS_Shape& aSubShape = aSubShapes (aShIndex);
        aBrepOwner = new StdSelect_BRepOwner (aSubShape, aPriority, isComesFromDecomposition);
        ComputeSensitive (aSubShape, aBrepOwner,
                          theSelection,
                          theDeflection,
                          theDeviationAngle,
                          theNbPOnEdge,
                          theMaxParam,
                          isAutoTriangulation);
      }
      break;
    }
    default:
    {
      aBrepOwner = new StdSelect_BRepOwner (theShape, aPriority);
      ComputeSensitive (theShape, aBrepOwner,
                        theSelection,
                        theDeflection,
                        theDeviationAngle,
                        theNbPOnEdge,
                        theMaxParam,
                        isAutoTriangulation);
    }
  }
}

//==================================================
// Function: Load
// Purpose :
//==================================================
void StdSelect_BRepSelectionTool
::Load (const Handle(SelectMgr_Selection)& theSelection,
        const Handle(SelectMgr_SelectableObject)& theSelectableObj,
        const TopoDS_Shape& theShape,
        const TopAbs_ShapeEnum theType,
        const Standard_Real theDeflection,
        const Standard_Real theDeviationAngle,
        const Standard_Boolean isAutoTriangulation,
        const Standard_Integer thePriority,
        const Standard_Integer theNbPOnEdge,
        const Standard_Real theMaxParam)
{
  Load (theSelection,
        theShape,
        theType,
        theDeflection,
        theDeviationAngle,
        isAutoTriangulation,
        thePriority,
        theNbPOnEdge,
        theMaxParam);

  // loading of selectables...
  for (theSelection->Init(); theSelection->More(); theSelection->Next())
  {
    Handle(SelectMgr_EntityOwner) anOwner
      = Handle(SelectMgr_EntityOwner)::DownCast (theSelection->Sensitive()->OwnerId());
    anOwner->Set (theSelectableObj);
  }
}

//==================================================
// Function: ComputeSensitive
// Purpose :
//==================================================
void StdSelect_BRepSelectionTool
::ComputeSensitive (const TopoDS_Shape& theShape,
                    const Handle(StdSelect_BRepOwner)& theOwner,
                    const Handle(SelectMgr_Selection)& theSelection,
                    const Standard_Real theDeflection,
                    const Standard_Real theDeviationAngle,
                    const Standard_Integer theNbPOnEdge,
                    const Standard_Real theMaxParam,
                    const Standard_Boolean isAutoTriangulation)
{
  switch (theShape.ShapeType())
  {
    case TopAbs_VERTEX:
    {
      theSelection->Add (new Select3D_SensitivePoint
                         (theOwner, BRep_Tool::Pnt (TopoDS::Vertex (theShape))));
      break;
    }
    case TopAbs_EDGE:
    {
      Handle(Select3D_SensitiveEntity) aSensitive;
      GetEdgeSensitive (theShape, theOwner, theSelection,
                        theDeflection, theDeviationAngle, theNbPOnEdge, theMaxParam,
                        aSensitive);
      if (!aSensitive.IsNull())
      {
        theSelection->Add (aSensitive);
      }
      break;
    }
    case TopAbs_WIRE:
    {
      BRepTools_WireExplorer aWireExp (TopoDS::Wire (theShape));
      Handle (Select3D_SensitiveEntity) aSensitive;
      Handle (Select3D_SensitiveWire) aWireSensitive = new Select3D_SensitiveWire (theOwner);
      theSelection->Add (aWireSensitive);
      while (aWireExp.More())
      {
        GetEdgeSensitive (aWireExp.Current(), theOwner, theSelection,
                          theDeflection, theDeviationAngle, theNbPOnEdge, theMaxParam,
                          aSensitive);
        if (!aSensitive.IsNull())
        {
          aWireSensitive->Add (aSensitive);
        }
        aWireExp.Next();
      }
      break;
    }
    case TopAbs_FACE:
    {
      const TopoDS_Face& aFace = TopoDS::Face (theShape);
      Select3D_ListOfSensitive aSensitiveList;
      GetSensitiveForFace (aFace, theOwner,
                           aSensitiveList,
                           isAutoTriangulation, theNbPOnEdge, theMaxParam);
      for (Select3D_ListIteratorOfListOfSensitive aSensIter (aSensitiveList);
           aSensIter.More(); aSensIter.Next())
      {
        theSelection->Add (aSensIter.Value());
      }
      break;
    }
    case TopAbs_SHELL:
    case TopAbs_SOLID:
    case TopAbs_COMPSOLID:
    {
      TopTools_IndexedMapOfShape aSubfacesMap;
      TopExp::MapShapes (theShape, TopAbs_FACE, aSubfacesMap);
      for (Standard_Integer aShIndex = 1; aShIndex <= aSubfacesMap.Extent(); ++aShIndex)
      {
        ComputeSensitive (aSubfacesMap (aShIndex), theOwner,
                          theSelection,
                          theDeflection, theDeviationAngle, theNbPOnEdge, theMaxParam, isAutoTriangulation);
      }
      break;
    }
    case TopAbs_COMPOUND:
    default:
    {
      TopExp_Explorer anExp;
      // sub-vertices
      for (anExp.Init (theShape, TopAbs_VERTEX, TopAbs_EDGE); anExp.More(); anExp.Next())
      {
        ComputeSensitive (anExp.Current(), theOwner,
                          theSelection,
                          theDeflection, theDeviationAngle, theNbPOnEdge, theMaxParam, isAutoTriangulation);
      }
      // sub-edges
      for (anExp.Init (theShape, TopAbs_EDGE, TopAbs_FACE); anExp.More(); anExp.Next())
      {
        ComputeSensitive (anExp.Current(), theOwner,
                          theSelection,
                          theDeflection, theDeviationAngle, theNbPOnEdge, theMaxParam, isAutoTriangulation);
      }
      // sub-wires
      for (anExp.Init (theShape, TopAbs_WIRE, TopAbs_FACE); anExp.More(); anExp.Next())
      {
        ComputeSensitive (anExp.Current(), theOwner,
                          theSelection,
                          theDeflection, theDeviationAngle, theNbPOnEdge, theMaxParam, isAutoTriangulation);
      }

      // sub-faces
      TopTools_IndexedMapOfShape aSubfacesMap;
      TopExp::MapShapes (theShape, TopAbs_FACE, aSubfacesMap);
      for (Standard_Integer aShIndex = 1; aShIndex <= aSubfacesMap.Extent(); ++aShIndex)
      {
        ComputeSensitive (aSubfacesMap (aShIndex), theOwner,
                          theSelection,
                          theDeflection, theDeviationAngle, theNbPOnEdge, theMaxParam, isAutoTriangulation);
      }
    }
  }
}

//==================================================
// Function: GetPointsFromPolygon
// Purpose :
//==================================================
static Handle(TColgp_HArray1OfPnt) GetPointsFromPolygon (const TopoDS_Edge& theEdge,
                                                         const Standard_Real theDeflection)
{
  Handle(TColgp_HArray1OfPnt) aResultPoints;

  Standard_Real fi, la;
  Handle(Geom_Curve) CC3d = BRep_Tool::Curve (theEdge, fi, la);

  TopLoc_Location aLocation;
  Handle(Poly_Polygon3D) aPolygon = BRep_Tool::Polygon3D (theEdge, aLocation);
  if (!aPolygon.IsNull())
  {
    Standard_Boolean isOK = aPolygon->Deflection() <= theDeflection;
    isOK = isOK || (CC3d.IsNull());
    if (isOK)
    {
      const TColgp_Array1OfPnt& aNodes = aPolygon->Nodes();
      aResultPoints = new TColgp_HArray1OfPnt (1, aNodes.Length());
      if (aLocation.IsIdentity())
      {
        for (Standard_Integer aNodeId (aNodes.Lower()), aPntId (1); aNodeId <= aNodes.Upper(); ++aNodeId, ++aPntId)
        {
          aResultPoints->SetValue (aPntId, aNodes.Value (aNodeId));
        }
      }
      else
      {
        for (Standard_Integer aNodeId (aNodes.Lower()), aPntId (1); aNodeId <= aNodes.Upper(); ++aNodeId, ++aPntId)
        {
          aResultPoints->SetValue (aPntId, aNodes.Value (aNodeId).Transformed (aLocation));
        }
      }
      return aResultPoints;
    }
  }

  Handle(Poly_Triangulation) aTriangulation;
  Handle(Poly_PolygonOnTriangulation) anHIndices;
  BRep_Tool::PolygonOnTriangulation (theEdge, anHIndices, aTriangulation, aLocation);
  if (!anHIndices.IsNull())
  {
    Standard_Boolean isOK = anHIndices->Deflection() <= theDeflection;
    isOK = isOK || (CC3d.IsNull());
    if (isOK)
    {
      const TColStd_Array1OfInteger& anIndices = anHIndices->Nodes();
      const TColgp_Array1OfPnt& aNodes = aTriangulation->Nodes();

      aResultPoints = new TColgp_HArray1OfPnt (1, anIndices.Length());

      if (aLocation.IsIdentity())
      {
        for (Standard_Integer anIndex (anIndices.Lower()), aPntId (1); anIndex <= anIndices.Upper(); ++anIndex, ++aPntId)
        {
          aResultPoints->SetValue (aPntId, aNodes (anIndices (anIndex)));
        }
      }
      else
      {
        for (Standard_Integer anIndex (anIndices.Lower()), aPntId (1); anIndex <= anIndices.Upper(); ++anIndex, ++aPntId)
        {
          aResultPoints->SetValue (aPntId, aNodes (anIndices (anIndex)).Transformed (aLocation));
        }
      }
      return aResultPoints;
    }
  }
  return aResultPoints;
}

//==================================================
// Function: FindLimits
// Purpose :
//==================================================
static Standard_Boolean FindLimits (const Adaptor3d_Curve& theCurve,
                                    const Standard_Real    theLimit,
                                          Standard_Real&   theFirst,
                                          Standard_Real&   theLast)
{
  theFirst = theCurve.FirstParameter();
  theLast  = theCurve.LastParameter();
  Standard_Boolean isFirstInf = Precision::IsNegativeInfinite (theFirst);
  Standard_Boolean isLastInf  = Precision::IsPositiveInfinite (theLast);
  if (isFirstInf || isLastInf)
  {
    gp_Pnt aPnt1, aPnt2;
    Standard_Real aDelta = 1.0;
    Standard_Integer anIterCount = 0;
    if (isFirstInf && isLastInf)
    {
      do {
        if (anIterCount++ >= 100000) return Standard_False;
        aDelta *= 2.0;
        theFirst = - aDelta;
        theLast  =   aDelta;
        theCurve.D0 (theFirst, aPnt1);
        theCurve.D0 (theLast,  aPnt2);
      } while (aPnt1.Distance (aPnt2) < theLimit);
    }
    else if (isFirstInf)
    {
      theCurve.D0 (theLast, aPnt2);
      do {
        if (anIterCount++ >= 100000) return Standard_False;
        aDelta *= 2.0;
        theFirst = theLast - aDelta;
        theCurve.D0 (theFirst, aPnt1);
      } while (aPnt1.Distance (aPnt2) < theLimit);
    }
    else if (isLastInf)
    {
      theCurve.D0 (theFirst, aPnt1);
      do {
        if (anIterCount++ >= 100000) return Standard_False;
        aDelta *= 2.0;
        theLast = theFirst + aDelta;
        theCurve.D0 (theLast, aPnt2);
      } while (aPnt1.Distance (aPnt2) < theLimit);
    }
  }
  return Standard_True;
}

//=====================================================
// Function : GetEdgeSensitive
// Purpose  : create a sensitive edge to add it
//            in computeselection to "aselection" (case of selection of an edge)
//            or to "aSensitiveWire" (case of selection of a wire; in this case,
//            the sensitive wire is added to "aselection" )
//            odl - for selection by rectangle -
//=====================================================
void StdSelect_BRepSelectionTool
::GetEdgeSensitive (const TopoDS_Shape& theShape,
                    const Handle(StdSelect_BRepOwner)& theOwner,
                    const Handle(SelectMgr_Selection)& theSelection,
                    const Standard_Real theDeflection,
                    const Standard_Real theDeviationAngle,
                    const Standard_Integer theNbPOnEdge,
                    const Standard_Real theMaxParam,
                    Handle(Select3D_SensitiveEntity)& theSensitive)
{
  const TopoDS_Edge& anEdge = TopoDS::Edge (theShape);
  BRepAdaptor_Curve cu3d;
  try {
    OCC_CATCH_SIGNALS
    cu3d.Initialize (anEdge);
  } catch (Standard_NullObject) {
    return;
  }

  // try to get points from existing polygons
  Handle(TColgp_HArray1OfPnt) aPoints = GetPointsFromPolygon (anEdge, theDeflection);
  if (!aPoints.IsNull() && aPoints->Length() > 0)
  {
    theSensitive = new Select3D_SensitiveCurve (theOwner, aPoints);
    return;
  }

  Standard_Real aParamFirst = cu3d.FirstParameter();
  Standard_Real aParamLast  = cu3d.LastParameter();
  switch (cu3d.GetType())
  {
    case GeomAbs_Line:
    {
      BRep_Tool::Range (anEdge, aParamFirst, aParamLast);
      theSensitive = new Select3D_SensitiveSegment (theOwner,
                                                    cu3d.Value (aParamFirst),
                                                    cu3d.Value (aParamLast));
      break;
    }
    case GeomAbs_Circle:
    {
      Handle (Geom_Circle) aCircle = new Geom_Circle (cu3d.Circle());
      if (aCircle->Radius() <= Precision::Confusion())
      {
        theSelection->Add (new Select3D_SensitivePoint (theOwner, aCircle->Location()));
      }
      else
      {
        theSensitive = new Select3D_SensitiveCircle (theOwner, aCircle,
                                                     aParamFirst, aParamLast, Standard_False, 16);
      }
      break;
    }
    default:
    {
      // reproduce drawing behaviour
      // TODO: remove copy-paste from StdPrs_Curve and some others...
      if (FindLimits (cu3d, theMaxParam, aParamFirst, aParamLast))
      {
        Standard_Integer aNbIntervals = cu3d.NbIntervals (GeomAbs_C1);
        TColStd_Array1OfReal anIntervals (1, aNbIntervals + 1);
        cu3d.Intervals (anIntervals, GeomAbs_C1);
        Standard_Real aV1, aV2;
        Standard_Integer aNumberOfPoints;
        TColgp_SequenceOfPnt aPointsSeq;
        for (Standard_Integer anIntervalId = 1; anIntervalId <= aNbIntervals; ++anIntervalId)
        {
          aV1 = anIntervals (anIntervalId);
          aV2 = anIntervals (anIntervalId + 1);
          if (aV2 > aParamFirst && aV1 < aParamLast)
          {
            aV1 = Max (aV1, aParamFirst);
            aV2 = Min (aV2, aParamLast);

            GCPnts_TangentialDeflection anAlgo (cu3d, aV1, aV2, theDeviationAngle, theDeflection);
            aNumberOfPoints = anAlgo.NbPoints();

            for (Standard_Integer aPntId = 1; aPntId < aNumberOfPoints; ++aPntId)
            {
              aPointsSeq.Append (anAlgo.Value (aPntId));
            }
            if (aNumberOfPoints > 0 && anIntervalId == aNbIntervals)
            {
              aPointsSeq.Append (anAlgo.Value (aNumberOfPoints));
            }
          }
        }

        aPoints = new TColgp_HArray1OfPnt (1, aPointsSeq.Length());
        for (Standard_Integer aPntId = 1; aPntId <= aPointsSeq.Length(); ++aPntId)
        {
          aPoints->SetValue (aPntId, aPointsSeq.Value (aPntId));
        }
        theSensitive = new Select3D_SensitiveCurve (theOwner, aPoints);
        break;
      }

      // simple subdivisions
      Standard_Integer nbintervals = 1;
      if (cu3d.GetType() == GeomAbs_BSplineCurve)
      {
        nbintervals = cu3d.NbKnots() - 1;
        nbintervals = Max (1, nbintervals / 3);
      }

      Standard_Real aParam;
      Standard_Integer aPntNb = Max (2, theNbPOnEdge * nbintervals);
      Standard_Real aParamDelta = (aParamLast - aParamFirst) / (aPntNb - 1);
      Handle(TColgp_HArray1OfPnt) aPointArray = new TColgp_HArray1OfPnt (1, aPntNb);
      for (Standard_Integer aPntId = 1; aPntId <= aPntNb; ++aPntId)
      {
        aParam = aParamFirst + aParamDelta * (aPntId - 1);
        aPointArray->SetValue (aPntId, cu3d.Value (aParam));
      }
      theSensitive = new Select3D_SensitiveCurve (theOwner, aPointArray);
    }
    break;
  }
}

//=====================================================
// Function : GetStandardPriority
// Purpose  :
//=====================================================
Standard_Integer StdSelect_BRepSelectionTool::GetStandardPriority (const TopoDS_Shape& theShape,
                                                                   const TopAbs_ShapeEnum theType)
{
  switch (theType)
  {
    case TopAbs_VERTEX: return 8;
    case TopAbs_EDGE:   return 7;
    case TopAbs_WIRE:   return 6;
    case TopAbs_FACE:   return 5;
    case TopAbs_SHAPE:
    default:
      switch (theShape.ShapeType())
      {
        case TopAbs_VERTEX:    return 9;
        case TopAbs_EDGE:      return 8;
        case TopAbs_WIRE:      return 7;
        case TopAbs_FACE:      return 6;
        case TopAbs_SHELL:     return 5;
        case TopAbs_COMPOUND:
        case TopAbs_COMPSOLID:
        case TopAbs_SOLID:
        case TopAbs_SHAPE:
        default:
          return 4;
      }
  }
}

//=======================================================================
//function : GetSensitiveEntityForFace
//purpose  :
//=======================================================================
Standard_Boolean StdSelect_BRepSelectionTool
::GetSensitiveForFace (const TopoDS_Face& theFace,
                       const Handle(StdSelect_BRepOwner)& theOwner,
                       Select3D_ListOfSensitive& theSensitiveList,
                       const Standard_Boolean theAutoTriangulation,
                       const Standard_Integer NbPOnEdge,
                       const Standard_Real    theMaxParam,
                       const Standard_Boolean theInteriorFlag)
{
  // check if there is triangulation of the face...
  TopLoc_Location aLoc;
  Handle(Poly_Triangulation) aTriangulation = BRep_Tool::Triangulation (theFace, aLoc);

  if (!aTriangulation.IsNull())
  {
    Handle(Select3D_SensitiveTriangulation) STG = new Select3D_SensitiveTriangulation (theOwner, aTriangulation, aLoc, theInteriorFlag);
    theSensitiveList.Append (STG);
    return Standard_True;
  }

  // for faces with triangulation bugs or without autotriangulation ....
  // very ugly and should not even exist ...
  BRepAdaptor_Surface BS;
  BS.Initialize (theFace);

  Standard_Real FirstU = BS.FirstUParameter() <= -Precision::Infinite() ? -theMaxParam : BS.FirstUParameter();
  Standard_Real LastU  = BS.LastUParameter()  >=  Precision::Infinite() ?  theMaxParam : BS.LastUParameter();
  Standard_Real FirstV = BS.FirstVParameter() <= -Precision::Infinite() ? -theMaxParam : BS.FirstVParameter();
  Standard_Real LastV  = BS.LastVParameter()  >=  Precision::Infinite() ?  theMaxParam : BS.LastVParameter();

  if (BS.GetType() == GeomAbs_Plane)
  {
    gp_Pnt pcur;
    Handle(TColgp_HArray1OfPnt) P = new TColgp_HArray1OfPnt (1, 5);
    BS.D0 (FirstU, FirstV, pcur);
    P->SetValue (1, pcur);
    BS.D0 (LastU, FirstV, pcur);
    P->SetValue (2, pcur);
    BS.D0 (LastU, LastV, pcur);
    P->SetValue (3, pcur);
    BS.D0 (FirstU, LastV, pcur);
    P->SetValue (4, pcur);
    P->SetValue (5, P->Value (1));
    // if the plane is "infinite", it is sensitive only on the border limited by MaxParam
    if (FirstU == -theMaxParam && LastU == theMaxParam && FirstV == -theMaxParam && LastV == theMaxParam)
    {
      theSensitiveList.Append (new Select3D_SensitiveFace (theOwner, P, Select3D_TOS_BOUNDARY));
    }
    else
    {
      Select3D_TypeOfSensitivity TS = theInteriorFlag ? Select3D_TOS_INTERIOR : Select3D_TOS_BOUNDARY;
      theSensitiveList.Append (new Select3D_SensitiveFace (theOwner, P, TS));
    }
    return Standard_True;
  }

  // This is construction of a sevsitive polygon from the exterior contour of the face...
  // It is not good at all, but...
  TopoDS_Wire aWire;
  TopExp_Explorer anExpWiresInFace (theFace, TopAbs_WIRE);
  if (anExpWiresInFace.More())
  {
    // believing that this is the first... to be seen
    aWire = TopoDS::Wire (anExpWiresInFace.Current());
  }
  if (aWire.IsNull())
  {
    return Standard_False;
  }

  TColgp_SequenceOfPnt WirePoints;
  Standard_Boolean FirstExp = Standard_True;
  Standard_Real wf, wl;
  BRepAdaptor_Curve cu3d;
  for (BRepTools_WireExplorer aWireExplorer (aWire);
       aWireExplorer.More(); aWireExplorer.Next())
  {
    cu3d.Initialize (aWireExplorer.Current());
    BRep_Tool::Range (aWireExplorer.Current(), wf, wl);
    if (Abs (wf - wl) <= Precision::Confusion())
    {
    #ifdef DEB
      cout<<" StdSelect_BRepSelectionTool : Curve where ufirst = ulast ...."<<endl;
    #endif
    }
    else
    {
      if (FirstExp)
      {
        if (aWireExplorer.Orientation() == TopAbs_FORWARD)
        {
          WirePoints.Append (cu3d.Value (wf));
        }
        else
        {
          WirePoints.Append (cu3d.Value (wl));
        }
        FirstExp = Standard_False;
      }

      switch (cu3d.GetType())
      {
        case GeomAbs_Line:
        {
          WirePoints.Append (cu3d.Value ((aWireExplorer.Orientation() == TopAbs_FORWARD) ? wl : wf));
          break;
        }
        case GeomAbs_Circle:
        {
          if (2 * M_PI - Abs (wl - wf) <= Precision::Confusion())
          {
            if (BS.GetType() == GeomAbs_Cylinder ||
                BS.GetType() == GeomAbs_Torus ||
                BS.GetType() == GeomAbs_Cone  ||
                BS.GetType() == GeomAbs_BSplineSurface) // beuurkk pour l'instant...
            {
              Standard_Real ff = wf ,ll = wl;
              Standard_Real dw =(Max (wf, wl) - Min (wf, wl)) / (Standard_Real )Max (2, NbPOnEdge - 1);
              if (aWireExplorer.Orientation() == TopAbs_FORWARD)
              {
                for (Standard_Real wc = wf + dw; wc <= wl; wc += dw)
                {
                  WirePoints.Append (cu3d.Value (wc));
                }
              }
              else if (aWireExplorer.Orientation() == TopAbs_REVERSED)
              {
                for (Standard_Real wc = ll - dw; wc >= ff; wc -= dw)
                {
                  WirePoints.Append (cu3d.Value (wc));
                }
              }
            }
            else
            {
              if (cu3d.Circle().Radius() <= Precision::Confusion())
              {
                theSensitiveList.Append (new Select3D_SensitivePoint (theOwner, cu3d.Circle().Location()));
              }
              else
              {
                theSensitiveList.Append (new Select3D_SensitiveCircle (theOwner, new Geom_Circle (cu3d.Circle()), theInteriorFlag, 16));
              }
            }
          }
          else
          {
            Standard_Real ff = wf, ll = wl;
            Standard_Real dw = (Max (wf, wl) - Min (wf, wl)) / (Standard_Real )Max (2, NbPOnEdge - 1);
            if (aWireExplorer.Orientation() == TopAbs_FORWARD)
            {
              for (Standard_Real wc = wf + dw; wc <= wl; wc += dw)
              {
                WirePoints.Append (cu3d.Value (wc));
              }
            }
            else if (aWireExplorer.Orientation() == TopAbs_REVERSED)
            {
              for (Standard_Real wc = ll - dw; wc >= ff; wc -= dw)
              {
                WirePoints.Append (cu3d.Value (wc));
              }
            }
          }
          break;
        }
        default:
        {
          Standard_Real ff = wf, ll = wl;
          Standard_Real dw = (Max (wf, wl) - Min (wf, wl)) / (Standard_Real )Max (2, NbPOnEdge - 1);
          if (aWireExplorer.Orientation()==TopAbs_FORWARD)
          {
            for (Standard_Real wc = wf + dw; wc <= wl; wc += dw)
            {
              WirePoints.Append (cu3d.Value (wc));
            }
          }
          else if (aWireExplorer.Orientation() == TopAbs_REVERSED)
          {
            for (Standard_Real wc = ll - dw; wc >= ff; wc -= dw)
            {
              WirePoints.Append (cu3d.Value (wc));
            }
          }
        }
      }
    }
  }
  Standard_Integer ArrayPosition = WirePoints.Length();

  Handle(TColgp_HArray1OfPnt) facepoints = new TColgp_HArray1OfPnt (1, ArrayPosition);
  for (Standard_Integer I = 1; I <= ArrayPosition; ++I)
  {
    facepoints->SetValue (I, WirePoints.Value(I));
  }

  if ((facepoints->Array1()).Length() > 1)
  { //1 if only one circular edge
    Select3D_TypeOfSensitivity TS = theInteriorFlag ? Select3D_TOS_INTERIOR : Select3D_TOS_BOUNDARY;
    theSensitiveList.Append (new Select3D_SensitiveFace (theOwner, facepoints, TS));
  }
  return Standard_True;
}
