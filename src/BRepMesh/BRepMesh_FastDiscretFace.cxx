// Created by: Ekaterina SMIRNOVA
// Copyright (c) 2008-2014 OPEN CASCADE SAS
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

#include <BRepMesh_FastDiscretFace.hxx>

#include <BRepMesh_PairOfPolygon.hxx>
#include <BRepMesh_ShapeTool.hxx>
#include <Poly_PolygonOnTriangulation.hxx>
#include <Poly_Triangulation.hxx>

#include <BRepAdaptor_Surface.hxx>
#include <BRepAdaptor_HSurface.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <Adaptor3d_IsoCurve.hxx>

#include <BRep_ListIteratorOfListOfPointRepresentation.hxx>
#include <BRep_PointRepresentation.hxx>
#include <BRep_TVertex.hxx>
#include <BRep_Tool.hxx>

#include <GeomLib.hxx>
#include <Geom_Surface.hxx>
#include <Geom_BSplineSurface.hxx>
#include <GCPnts_TangentialDeflection.hxx>
#include <GCPnts_AbscissaPoint.hxx>

#include <Standard_ErrorHandler.hxx>
#include <Standard_Failure.hxx>
#include <SortTools_ShellSortOfReal.hxx>
#include <TCollection_CompareOfReal.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_ListOfInteger.hxx>
#include <TColStd_SequenceOfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TopTools_DataMapOfShapeReal.hxx>

#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopExp.hxx>

#include <NCollection_Map.hxx>
#include <Bnd_Box2d.hxx>

#include <algorithm>

IMPLEMENT_STANDARD_HANDLE (BRepMesh_FastDiscretFace, Standard_Transient)
IMPLEMENT_STANDARD_RTTIEXT(BRepMesh_FastDiscretFace, Standard_Transient)

static Standard_Real FUN_CalcAverageDUV(TColStd_Array1OfReal& P, const Standard_Integer PLen)
{
  Standard_Integer i, j, n = 0;
  Standard_Real p, result = 0.;

  for(i = 1; i <= PLen; i++)
  {
    // Sort
    for(j = i + 1; j <= PLen; j++)
    {
      if(P(i) > P(j))
      {
        p = P(i);
        P(i) = P(j);
        P(j) = p;
      }
    }
    // Accumulate
    if (i != 1)
    {
      p = Abs(P(i) - P(i-1));
      if(p > 1.e-7)
      {
        result += p;
        n++;
      }
    }
  }
  return (n? (result / (Standard_Real) n) : -1.);
}

namespace
{

  //! Auxiliary class used to extract geometrical parameters of fixed TopoDS_Vertex.
  class FixedVExplorer
  {
  public:

    DEFINE_STANDARD_ALLOC

    FixedVExplorer(const TopoDS_Vertex& theVertex)
      : myVertex(theVertex)
    {
    }

    const TopoDS_Vertex& Vertex() const
    {
      return myVertex;
    }

    Standard_Boolean IsSameUV() const
    {
      return Standard_False;
    }

    TopoDS_Vertex SameVertex() const
    {
      return TopoDS_Vertex();
    }

    gp_Pnt Point() const
    {
      return BRep_Tool::Pnt(myVertex);
    }

  private:

    void operator =(const FixedVExplorer& /*theOther*/)
    {
    }

  private:
    const TopoDS_Vertex& myVertex;
  };
}


//=======================================================================
//function : BRepMesh_FastDiscretFace
//purpose  :
//=======================================================================
BRepMesh_FastDiscretFace::BRepMesh_FastDiscretFace(
  const Standard_Real    theAngle,
  const Standard_Real    theMinSize,
  const Standard_Boolean isInternalVerticesMode,
  const Standard_Boolean isControlSurfaceDeflection)
: myAngle(theAngle),
  myInternalVerticesMode(isInternalVerticesMode),
  myMinSize(theMinSize),
  myIsControlSurfaceDeflection(isControlSurfaceDeflection)
{
}

//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscretFace::Perform(const Handle(BRepMesh_FaceAttribute)& theAttribute)
{
  add(theAttribute);
  commitSurfaceTriangulation();
}

//=======================================================================
//function : initDataStructure
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscretFace::initDataStructure()
{
  const Standard_Real aTolU = myAttribute->ToleranceU();
  const Standard_Real aTolV = myAttribute->ToleranceV();
  const Standard_Real uCellSize = 14.0 * aTolU;
  const Standard_Real vCellSize = 14.0 * aTolV;

  const Standard_Real deltaX = myAttribute->GetDeltaX();
  const Standard_Real deltaY = myAttribute->GetDeltaY();

  Handle(NCollection_IncAllocator) aAllocator = 
    new NCollection_IncAllocator(BRepMesh::MEMORY_BLOCK_SIZE_HUGE);
  myStructure = new BRepMesh_DataStructureOfDelaun(aAllocator);
  myStructure->Data()->SetCellSize ( uCellSize / deltaX, vCellSize / deltaY);
  myStructure->Data()->SetTolerance( aTolU     / deltaX, aTolV     / deltaY);

  myAttribute->ChangeStructure() = myStructure;
  myAttribute->ChangeSurfacePoints() = new BRepMesh::DMapOfIntegerPnt;
  myAttribute->ChangeSurfaceVertices()= new BRepMesh::DMapOfVertexInteger;

  // Check the necessity to fill the map of parameters
  const Handle(BRepAdaptor_HSurface)& gFace = myAttribute->Surface();
  GeomAbs_SurfaceType thetype = gFace->GetType();
  const Standard_Boolean isBSpline = (thetype == GeomAbs_BezierSurface ||
                                      thetype == GeomAbs_BSplineSurface);
  const Standard_Boolean useUVParam = (thetype == GeomAbs_Torus ||isBSpline);

  myUParam.Clear(); 
  myVParam.Clear();

  // essai de determination de la longueur vraie:
  // akm (bug OCC16) : We must calculate these measures in non-singular
  //     parts of face. Let`s try to compute average value of three
  //     (umin, (umin+umax)/2, umax), and respectively for v.
  //                 vvvvv
  //Standard_Real longu = 0.0, longv = 0.0; //, last , first;
  //gp_Pnt P11, P12, P21, P22, P31, P32;
  BRepMesh::HVectorOfVertex& aBoundaryNodes = myAttribute->ChangeMeshNodes();
  BRepMesh::VectorOfVertex::Iterator aNodesIt(*aBoundaryNodes);
  for (; aNodesIt.More(); aNodesIt.Next())
  {
    BRepMesh_Vertex& aNode = aNodesIt.ChangeValue();
    gp_XY aPnt2d = aNode.Coord();

    if (useUVParam)
    {
      myUParam.Add(aPnt2d.X());
      myVParam.Add(aPnt2d.Y());
    }

    aNode.ChangeCoord() = myAttribute->Scale(aPnt2d, Standard_True);
    myStructure->AddNode(aNode, Standard_True);
  }
  aBoundaryNodes.Nullify();

  if (isBSpline)
  {
    const Standard_Real aRange[2][2] = {
      {myAttribute->GetUMin(), myAttribute->GetUMax()},
      {myAttribute->GetVMin(), myAttribute->GetVMax()}
    };

    const GeomAbs_Shape aContinuity = GeomAbs_CN;
    for (Standard_Integer i = 0; i < 2; ++i)
    {
      const Standard_Boolean isU = (i == 0);
      const Standard_Integer aIntervalsNb = isU ?
        gFace->NbUIntervals(aContinuity) :
        gFace->NbVIntervals(aContinuity);

      BRepMesh::IMapOfReal& aParams = isU ? myUParam : myVParam;
      if (aIntervalsNb < aParams.Size())
        continue;

      TColStd_Array1OfReal aIntervals(1, aIntervalsNb + 1);
      if (isU)
        gFace->UIntervals(aIntervals, aContinuity);
      else
        gFace->VIntervals(aIntervals, aContinuity);

      for (Standard_Integer j = 1; j <= aIntervals.Upper(); ++j)
      {
        const Standard_Real aParam = aIntervals(j);
        if (aParam > aRange[i][0] && aParam < aRange[i][1])
          aParams.Add(aParam);
      }
    }
  }

  //////////////////////////////////////////////////////////// 
  //add internal vertices after self-intersection check
  if ( myInternalVerticesMode )
  {
    TopExp_Explorer anExplorer(myAttribute->Face(), TopAbs_VERTEX, TopAbs_EDGE);
    for ( ; anExplorer.More(); anExplorer.Next() )
      add(TopoDS::Vertex(anExplorer.Current()));
  }

  const BRepMesh::HDMapOfShapePairOfPolygon& aEdges = myAttribute->ChangeInternalEdges();
  TopExp_Explorer aWireIt(myAttribute->Face(), TopAbs_WIRE);
  for (; aWireIt.More(); aWireIt.Next())
  {
    TopExp_Explorer aEdgeIt(aWireIt.Current(), TopAbs_EDGE);
    for (; aEdgeIt.More(); aEdgeIt.Next())
    {
      const TopoDS_Edge& aEdge = TopoDS::Edge(aEdgeIt.Current());
      BRepMesh_PairOfPolygon aPair;
      if (!aEdges->Find(aEdge, aPair))
        continue;

      TopAbs_Orientation aOri = aEdge.Orientation();
      const Handle(Poly_PolygonOnTriangulation)& aPolygon = 
        aOri == TopAbs_REVERSED ? aPair.Last() : aPair.First();

      const TColStd_Array1OfInteger& aIndices = aPolygon->Nodes();
      const Standard_Integer aNodesNb = aPolygon->NbNodes();

      Standard_Integer aPrevId = aIndices(1);
      for (Standard_Integer i = 2; i <= aNodesNb; ++i)
      {
        const Standard_Integer aCurId = aIndices(i);
        addLinkToMesh(aPrevId, aCurId, aOri);
        aPrevId = aCurId;
      }
    }
  }
}

//=======================================================================
//function : addLinkToMesh
//purpose  :
//=======================================================================
void BRepMesh_FastDiscretFace::addLinkToMesh(
  const Standard_Integer   theFirstNodeId,
  const Standard_Integer   theLastNodeId,
  const TopAbs_Orientation theOrientation)
{
  if (theOrientation == TopAbs_FORWARD)
    myStructure->AddLink(BRepMesh_Edge(theFirstNodeId, theLastNodeId, BRepMesh_Frontier));
  else if (theOrientation == TopAbs_REVERSED)
    myStructure->AddLink(BRepMesh_Edge(theLastNodeId, theFirstNodeId, BRepMesh_Frontier));
  else if (theOrientation == TopAbs_INTERNAL)
    myStructure->AddLink(BRepMesh_Edge(theFirstNodeId, theLastNodeId, BRepMesh_Fixed));
}

//=======================================================================
//function : Add
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscretFace::add(const Handle(BRepMesh_FaceAttribute)& theAttribute)
{
  if (!theAttribute->IsValid() || theAttribute->ChangeMeshNodes()->IsEmpty())
    return;

  myAttribute = theAttribute;
  initDataStructure();

  BRepMesh::HIMapOfInteger& aVertexEdgeMap = myAttribute->ChangeVertexEdgeMap();
  Standard_Integer nbVertices = aVertexEdgeMap->Extent();
  BRepMesh::Array1OfInteger tabvert_corr(1, nbVertices);
  for ( Standard_Integer i = 1; i <= nbVertices; ++i )
    tabvert_corr(i) = i;

  BRepMesh_Delaun trigu(myStructure, tabvert_corr);

  //removed all free edges from triangulation
  const Standard_Integer nbLinks = myStructure->NbLinks();
  for( Standard_Integer i = 1; i <= nbLinks; i++ ) 
  {
    if( myStructure->ElementsConnectedTo(i).Extent() < 1 )
    {
      BRepMesh_Edge& anEdge = (BRepMesh_Edge&)trigu.GetEdge(i);
      if ( anEdge.Movability() == BRepMesh_Deleted )
        continue;

      anEdge.SetMovability(BRepMesh_Free);
      myStructure->RemoveLink(i);
    }
  }

  const Handle(BRepAdaptor_HSurface)& gFace = myAttribute->Surface();
  GeomAbs_SurfaceType thetype = gFace->GetType();

  Standard_Boolean rajout = 
    (thetype == GeomAbs_Sphere || thetype == GeomAbs_Torus);

  // Check the necessity to fill the map of parameters
  const Standard_Boolean useUVParam = (thetype == GeomAbs_Torus         ||
                                       thetype == GeomAbs_BezierSurface ||
                                       thetype == GeomAbs_BSplineSurface);

  const Standard_Real umax = myAttribute->GetUMax();
  const Standard_Real umin = myAttribute->GetUMin();
  const Standard_Real vmax = myAttribute->GetVMax();
  const Standard_Real vmin = myAttribute->GetVMin();

  Standard_Boolean isaline = 
    ((umax - umin) < Precision::PConfusion() || 
     (vmax - vmin) < Precision::PConfusion());

  Standard_Real aDef = -1;
  if ( !isaline && myStructure->ElementsOfDomain().Extent() > 0 )
  {
    BRepMesh::ListOfVertex aNewVertices;
    if (!rajout)
    {
      aDef = control(aNewVertices, trigu, Standard_True);
      rajout = (aDef > myAttribute->GetDefFace() || aDef < 0.);
    }

    if (!rajout && useUVParam)
    {
      rajout = (myVParam.Extent() > 2 && 
        (gFace->IsUClosed() || gFace->IsVClosed()));
    }

    if (rajout)
    {
      insertInternalVertices(aNewVertices, trigu);

      //control internal points
      if (myIsControlSurfaceDeflection)
        aDef = control(aNewVertices, trigu, Standard_False);
    }
  }

  //modify myStructure back
  BRepMesh::HVectorOfVertex& aMeshNodes = myStructure->Data()->ChangeVertices();
  for ( Standard_Integer i = 1; i <= myStructure->NbNodes(); ++i )
  {
    BRepMesh_Vertex& aNode = aMeshNodes->ChangeValue(i - 1);
    aNode.ChangeCoord() = myAttribute->Scale(aNode.Coord(), Standard_False);

    const BRepMesh::ListOfInteger& alist = myStructure->LinksConnectedTo(i);
    // Register internal nodes used in triangulation
    if (!alist.IsEmpty() && aVertexEdgeMap->FindIndex(i) == 0)
      aVertexEdgeMap->Add(i);
  }

  if (!(aDef < 0.))
    myAttribute->SetDefFace(aDef);
}

//=======================================================================
//function : addVerticesToMesh
//purpose  : 
//=======================================================================
Standard_Boolean BRepMesh_FastDiscretFace::addVerticesToMesh(
  const BRepMesh::ListOfVertex& theVertices,
  BRepMesh_Delaun&              theMeshBuilder)
{
  if (theVertices.IsEmpty())
    return Standard_False;

  BRepMesh::Array1OfVertexOfDelaun aArrayOfNewVertices(1, theVertices.Extent());
  BRepMesh::ListOfVertex::Iterator aVertexIt(theVertices);
  for (Standard_Integer aVertexId = 0; aVertexIt.More(); aVertexIt.Next())
    aArrayOfNewVertices(++aVertexId) = aVertexIt.Value();

  theMeshBuilder.AddVertices(aArrayOfNewVertices);
  return Standard_True;
}

//=======================================================================
//function : insertInternalVertices
//purpose  : 
//=======================================================================
static void filterParameters(const BRepMesh::IMapOfReal& theParams,
                             const Standard_Real         theMinDist,
                             const Standard_Real         theFilterDist,
                             BRepMesh::SequenceOfReal&   theResult)
{
  // Sort sequence of parameters
  BRepMesh::SequenceOfReal aParamTmp;
  Standard_Integer aParamLength = 1;
  const Standard_Integer anInitLen = theParams.Extent();
    
  TColStd_Array1OfReal aParamArray(1, anInitLen);
  Standard_Integer j;
  for (j = 1; j <= anInitLen; j++)
    aParamArray(j) = theParams(j);

  TCollection_CompareOfReal aCompare;
  SortTools_ShellSortOfReal::Sort(aParamArray, aCompare);

  // mandadory pre-filtering using the first (minimal) filter value
  Standard_Real aP1, aP2;
  aP1 = aParamArray(1);
  aParamTmp.Append(aP1);
  for (j = 2; j <= anInitLen; j++) 
  {
    aP2 = aParamArray(j);
    if ((aP2-aP1) > theMinDist)
    {
      aParamTmp.Append(aP2);
      aP1 = aP2;
      aParamLength++;
    }
  }

  //add last point if required
  if(aParamArray(anInitLen)-theParams(aParamLength) > theMinDist)
  {
    aParamTmp.Append(aParamArray(anInitLen));
    aParamLength++;
  }
  
  //perform filtering on series
  Standard_Real aLastAdded, aLastCandidate;
  Standard_Boolean isCandidateDefined = Standard_False;
  aLastAdded = aParamTmp.First();
  aLastCandidate = aLastAdded;
  theResult.Append(aParamTmp.First());
  
  for(j=2;j<aParamTmp.Length();j++) 
  {
    Standard_Real aVal = aParamTmp.Value(j);
    if(aVal-aLastAdded > theFilterDist) 
    {
      //adds the parameter
      if(isCandidateDefined) {
        aLastAdded = aLastCandidate;
        isCandidateDefined = Standard_False;
        j--;
      }
      else 
      {
        aLastAdded = aVal;
      }
      theResult.Append(aLastAdded);
      continue;
    }
    
    aLastCandidate = aVal;
    isCandidateDefined = Standard_True;
  }
  theResult.Append(aParamTmp.Last());
  
  if( theResult.Length() == 2 )
  {
    Standard_Real    dist  = theResult.Last() - theResult.First();
    Standard_Integer nbint = (Standard_Integer)((dist / theFilterDist) + 0.5);

    if( nbint > 1 )
    {
      //Five points more is maximum
      if( nbint > 5 )
      {
        nbint = 5;
      }

      Standard_Integer i;
      Standard_Real dU = dist / nbint;
      for( i = 1; i < nbint; i++ )
      {
        theResult.InsertAfter(i, theResult.First()+i*dU);
      }
    }
  }
}

void BRepMesh_FastDiscretFace::insertInternalVertices(
  BRepMesh::ListOfVertex&  theNewVertices,
  BRepMesh_Delaun&         theMeshBuilder)
{
  const Handle(BRepAdaptor_HSurface)& gFace = myAttribute->Surface();
  switch (gFace->GetType())
  {
  case GeomAbs_Sphere:
      insertInternalVerticesSphere(theNewVertices);
      break;

  case GeomAbs_Cylinder:
      insertInternalVerticesCylinder(theNewVertices);
      break;

  case GeomAbs_Cone:
    insertInternalVerticesCone(theNewVertices);
    break;

  case GeomAbs_Torus:
    insertInternalVerticesTorus(theNewVertices);
    break;

  case GeomAbs_BezierSurface:
  case GeomAbs_BSplineSurface:
    insertInternalVerticesBSpline(theNewVertices);
    break;

  default:
    insertInternalVerticesOther(theNewVertices);
    break;
  }
  
  addVerticesToMesh(theNewVertices, theMeshBuilder);
}

//=======================================================================
//function : insertInternalVerticesSphere
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscretFace::insertInternalVerticesSphere(
  BRepMesh::ListOfVertex& theNewVertices)
{
  Standard_Real aRange[] = {
    myAttribute->GetVMin(), myAttribute->GetVMax(),
    myAttribute->GetUMin(), myAttribute->GetUMax()
  };

  gp_Sphere aSphere = myAttribute->Surface()->Sphere();

  // Calculate parameters for iteration in V direction
  Standard_Real aStep = 0.7 * GCPnts_TangentialDeflection::ArcAngularStep(
    aSphere.Radius(), myAttribute->GetDefFace(), myAngle, myMinSize);

  Standard_Real aDd[2] = {aStep, aStep};
  Standard_Real aPasMax[2] = {0., 0.};
  for (Standard_Integer i = 0; i < 2; ++i)
  {
    const Standard_Real aMax = aRange[2 * i + 1];
    const Standard_Real aDiff = aMax - aRange[2 * i + 0];
    aDd[i] = aDiff / ((Standard_Integer)(aDiff / aDd[i]) + 1);
    aPasMax[i] = aMax - Precision::PConfusion();
  }

  const Standard_Real aHalfDu = aDd[1] * 0.5;
  Standard_Boolean Shift = Standard_False;
  Standard_Real aPasV = aRange[0] + aDd[0];
  for (; aPasV < aPasMax[0]; aPasV += aDd[0])
  {
    Shift = !Shift;
    const Standard_Real d = (Shift) ? aHalfDu : 0.;
    Standard_Real aPasU = aRange[2] + d;
    for (; aPasU < aPasMax[1]; aPasU += aDd[1])
    {
      tryToInsertAnalyticVertex(gp_Pnt2d(aPasU, aPasV), aSphere, theNewVertices);
    }
  }
}

//=======================================================================
//function : insertInternalVerticesCylinder
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscretFace::insertInternalVerticesCylinder(
  BRepMesh::ListOfVertex& theNewVertices)
{
  const Standard_Real umax = myAttribute->GetUMax();
  const Standard_Real umin = myAttribute->GetUMin();
  const Standard_Real vmax = myAttribute->GetVMax();
  const Standard_Real vmin = myAttribute->GetVMin();

  gp_Cylinder aCylinder = myAttribute->Surface()->Cylinder();
  const Standard_Real aRadius = aCylinder.Radius();

  // Calculate parameters for iteration in U direction
  Standard_Real Du = GCPnts_TangentialDeflection::ArcAngularStep(
    aRadius, myAttribute->GetDefFace(), myAngle, myMinSize);

  const Standard_Real su = umax - umin;
  const Standard_Integer nbU = (Standard_Integer)(su / Du);
  Du = su / (nbU + 1);

  // Calculate parameters for iteration in V direction
  const Standard_Real sv = vmax - vmin;
  Standard_Integer nbV = (Standard_Integer)(nbU*sv / (su*aRadius));
  nbV = Min(nbV, 100 * nbU);
  Standard_Real Dv = sv / (nbV + 1);

  Standard_Real pasu, pasv, pasvmax = vmax - Dv*0.5, pasumax = umax - Du*0.5;
  for (pasv = vmin + Dv; pasv < pasvmax; pasv += Dv)
  {
    for (pasu = umin + Du; pasu < pasumax; pasu += Du)
    {
      tryToInsertAnalyticVertex(gp_Pnt2d(pasu, pasv), aCylinder, theNewVertices);
    }
  }
}

//=======================================================================
//function : insertInternalVerticesCone
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscretFace::insertInternalVerticesCone(
  BRepMesh::ListOfVertex& theNewVertices)
{
  const Standard_Real umax = myAttribute->GetUMax();
  const Standard_Real umin = myAttribute->GetUMin();
  const Standard_Real vmax = myAttribute->GetVMax();
  const Standard_Real vmin = myAttribute->GetVMin();

  gp_Cone aCone = myAttribute->Surface()->Cone();
  Standard_Real RefR = aCone.RefRadius();
  Standard_Real SAng = aCone.SemiAngle();
  Standard_Real aRadius = Max(Abs(RefR + vmin*Sin(SAng)), Abs(RefR + vmax*Sin(SAng)));

  Standard_Real Du = GCPnts_TangentialDeflection::ArcAngularStep(
    aRadius, myAttribute->GetDefFace(), myAngle, myMinSize);

  Standard_Real Dv, pasu, pasv;
  Standard_Integer nbU = (Standard_Integer)((umax - umin) / Du);
  Standard_Integer nbV = (Standard_Integer)(nbU*(vmax - vmin) / ((umax - umin)*aRadius));
  Du = (umax - umin) / (nbU + 1);
  Dv = (vmax - vmin) / (nbV + 1);

  Standard_Real pasvmax = vmax - Dv*0.5, pasumax = umax - Du*0.5;
  for (pasv = vmin + Dv; pasv < pasvmax; pasv += Dv)
  {
    for (pasu = umin + Du; pasu < pasumax; pasu += Du)
    {
      tryToInsertAnalyticVertex(gp_Pnt2d(pasu, pasv), aCone, theNewVertices);
    }
  }
}

//=======================================================================
//function : insertInternalVerticesTorus
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscretFace::insertInternalVerticesTorus(
  BRepMesh::ListOfVertex& theNewVertices)
{
  const Standard_Real umax     = myAttribute->GetUMax();
  const Standard_Real umin     = myAttribute->GetUMin();
  const Standard_Real vmax     = myAttribute->GetVMax();
  const Standard_Real vmin     = myAttribute->GetVMin();
  const Standard_Real deltaX   = myAttribute->GetDeltaX();
  const Standard_Real deltaY   = myAttribute->GetDeltaY();
  const Standard_Real aDefFace = myAttribute->GetDefFace();

  gp_Torus T = myAttribute->Surface()->Torus();

  Standard_Boolean insert;
  Standard_Integer i, j, ParamULength, ParamVLength;
  Standard_Real pp, pasu, pasv;
  Standard_Real r = T.MinorRadius(), R = T.MajorRadius();

  BRepMesh::SequenceOfReal ParamU, ParamV;

  Standard_Real oldDv = GCPnts_TangentialDeflection::ArcAngularStep(
    r, aDefFace, myAngle, myMinSize);

  Standard_Real Dv = 0.9*oldDv; //TWOTHIRD * oldDv;
  Dv = oldDv;

  Standard_Real Du;
  Standard_Integer nbV = Max((Standard_Integer)((vmax - vmin) / Dv), 2);
  Dv = (vmax - vmin) / (nbV + 1);
  Standard_Real ru = R + r;
  if (ru > 1.e-16)
  {
    Du = GCPnts_TangentialDeflection::ArcAngularStep(
      ru, aDefFace, myAngle, myMinSize);

    Standard_Real aa = sqrt(Du*Du + oldDv*oldDv);
    if (aa < gp::Resolution())
      return;
    Du *= Min(oldDv, Du) / aa;
  }
  else Du = Dv;

  Standard_Integer nbU = Max((Standard_Integer)((umax - umin) / Du), 2);
  nbU = Max(nbU, (int)(nbV*(umax - umin)*R / ((vmax - vmin)*r) / 5.));
  Du = (umax - umin) / (nbU + 1);

  if (R < r)
  {
    // As the points of edges are returned.
    // in this case, the points are not representative.

    //-- Choose DeltaX and DeltaY so that to avoid skipping points on the grid
    for (i = 0; i <= nbU; i++) ParamU.Append(umin + i* Du);
  }//R<r
  else //U if R > r
  {
    //--ofv: U
    // Number of mapped U parameters
    const Standard_Integer LenU = myUParam.Extent();
    // Fill array of U parameters
    TColStd_Array1OfReal Up(1, LenU);
    for (j = 1; j <= LenU; j++) Up(j) = myUParam(j);

    // Calculate DU, leave array of parameters
    Standard_Real aDU = FUN_CalcAverageDUV(Up, LenU);
    aDU = Max(aDU, Abs(umax - umin) / (Standard_Real)nbU / 2.);
    Standard_Real dUstd = Abs(umax - umin) / (Standard_Real)LenU;
    if (aDU > dUstd) dUstd = aDU;
    // Add U parameters
    for (j = 1; j <= LenU; j++)
    {
      pp = Up(j);
      insert = Standard_True;
      ParamULength = ParamU.Length();
      for (i = 1; i <= ParamULength && insert; i++)
      {
        insert = (Abs(ParamU.Value(i) - pp) > (0.5*dUstd));
      }
      if (insert) ParamU.Append(pp);
    }
  }

  //--ofv: V
  // Number of mapped V parameters
  const Standard_Integer LenV = myVParam.Extent();
  // Fill array of V parameters
  TColStd_Array1OfReal Vp(1, LenV);
  for (j = 1; j <= LenV; j++) Vp(j) = myVParam(j);
  // Calculate DV, sort array of parameters
  Standard_Real aDV = FUN_CalcAverageDUV(Vp, LenV);
  aDV = Max(aDV, Abs(vmax - vmin) / (Standard_Real)nbV / 2.);

  Standard_Real dVstd = Abs(vmax - vmin) / (Standard_Real)LenV;
  if (aDV > dVstd) dVstd = aDV;
  // Add V parameters
  for (j = 1; j <= LenV; j++)
  {
    pp = Vp(j);

    insert = Standard_True;
    ParamVLength = ParamV.Length();
    for (i = 1; i <= ParamVLength && insert; i++)
    {
      insert = (Abs(ParamV.Value(i) - pp) > (dVstd*2. / 3.));
    }
    if (insert) ParamV.Append(pp);
  }

  Standard_Integer Lu = ParamU.Length(), Lv = ParamV.Length();
  Standard_Real uminnew = umin + deltaY*0.1;
  Standard_Real vminnew = vmin + deltaX*0.1;
  Standard_Real umaxnew = umax - deltaY*0.1;
  Standard_Real vmaxnew = vmax - deltaX*0.1;

  for (i = 1; i <= Lu; i++)
  {
    pasu = ParamU.Value(i);
    if (pasu >= uminnew && pasu < umaxnew)
    {
      for (j = 1; j <= Lv; j++)
      {
        pasv = ParamV.Value(j);
        if (pasv >= vminnew && pasv < vmaxnew)
        {
          tryToInsertAnalyticVertex(gp_Pnt2d(pasu, pasv), T, theNewVertices);
        }
      }
    }
  }
}

//=======================================================================
//function : insertInternalVerticesBSpline
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscretFace::insertInternalVerticesBSpline(
  BRepMesh::ListOfVertex& theNewVertices)
{
  const Standard_Real aRange[2][2] = {
      { myAttribute->GetUMax(), myAttribute->GetUMin() },
      { myAttribute->GetVMax(), myAttribute->GetVMin() }
  };

  const Standard_Real aDelta[2] = { 
    myAttribute->GetDeltaX(),
    myAttribute->GetDeltaY()
  };

  const Standard_Real                 aDefFace = myAttribute->GetDefFace();
  const Handle(BRepAdaptor_HSurface)& gFace    = myAttribute->Surface();

  BRepMesh::SequenceOfReal aParams[2];
  for (Standard_Integer i = 0; i < 2; ++i)
  {
    Standard_Boolean isU = (i == 0);
    Standard_Real aRes = isU ?
      gFace->UResolution(aDefFace) :
      gFace->VResolution(aDefFace);

    // Sort and filter sequence of parameters
    Standard_Real aMinDiff = Precision::PConfusion();
    if (aDelta[i] < 1.)
      aMinDiff /= aDelta[i];

    aMinDiff = Max(myMinSize, aMinDiff);

    Standard_Real aRangeDiff = aRange[i][0] - aRange[i][1];
    Standard_Real aDiffMaxLim = 0.1 * aRangeDiff;
    Standard_Real aDiffMinLim = Max(0.005 * aRangeDiff, 2. * aRes);
    Standard_Real aDiff = Max(myMinSize, Min(aDiffMaxLim, aDiffMinLim));
    filterParameters(isU ? myUParam : myVParam, aMinDiff, aDiff, aParams[i]);
  }

  // check intermediate isolines
  Handle(Geom_Surface) aBSpline;
  GeomAbs_SurfaceType  aSurfType = gFace->GetType();
  if (aSurfType == GeomAbs_BezierSurface)
    aBSpline = gFace->Bezier();
  else if (aSurfType == GeomAbs_BSplineSurface)
    aBSpline = gFace->BSpline();

  const BRepMesh::HClassifier& aClassifier = myAttribute->ChangeClassifier();

  // precision for compare square distances
  const Standard_Real aPrecision   = Precision::Confusion();
  const Standard_Real aSqPrecision = aPrecision * aPrecision;
  for (Standard_Integer k = 0; k < 2; ++k)
  {
    BRepMesh::SequenceOfReal& aParams1 = aParams[k];
    BRepMesh::SequenceOfReal& aParams2 = aParams[(k + 1) % 2];
    const Standard_Boolean isU = (k == 0);
    Standard_Integer aStartIndex, aEndIndex; 
    if (isU)
    {
      aStartIndex = 1;
      aEndIndex   = aParams1.Length();
    }
    else
    {
      aStartIndex = 2;
      aEndIndex   = aParams1.Length() - 1;
    }

    for (Standard_Integer i = aStartIndex; i <= aEndIndex; ++i)
    {
      const Standard_Real aParam1 = aParams1(i);
      GeomAdaptor_Curve aIso(isU ?
        aBSpline->UIso(aParam1) : aBSpline->VIso(aParam1));

      Standard_Real aPrevParam2 = aParams2(1);
      gp_Pnt aPrevPnt2 = aIso.Value(aPrevParam2);
      for (Standard_Integer j = 2; j <= aParams2.Length();)
      {
        Standard_Real aParam2 = aParams2(j);
        gp_Pnt aPnt2 = aIso.Value(aParam2);
        Standard_Real aMidParam = 0.5 * (aPrevParam2 + aParam2);
        gp_Pnt aMidPnt = aIso.Value(aMidParam);

        // 23.03.2010 skl for OCC21645 - change precision for comparison
        Standard_Real aDist;
        if (aPrevPnt2.SquareDistance(aPnt2) > aSqPrecision)
        {
          gp_Lin aLin(aPrevPnt2, gp_Dir(gp_Vec(aPrevPnt2, aPnt2)));
          aDist = aLin.Distance(aMidPnt);
        }
        else
          aDist = aPrevPnt2.Distance(aMidPnt);

        if (aDist > aDefFace && aDist > myMinSize)
        {
          // insertion 
          aParams2.InsertBefore(j, aMidParam);
        }
        else
        {
          //put regular grig for normals
          gp_Pnt2d aStPnt1, aStPnt2;
          if (isU)
          {
            aStPnt1 = gp_Pnt2d(aParam1, aPrevParam2);
            aStPnt2 = gp_Pnt2d(aParam1, aMidParam);
          }
          else
          {
            aStPnt1 = gp_Pnt2d(aPrevParam2, aParam1);
            aStPnt2 = gp_Pnt2d(aMidParam,   aParam1);
          }

          gp_Dir N1(0, 0, 1), N2(0, 0, 1);
          Standard_Integer aSt1 = GeomLib::NormEstim(aBSpline, aStPnt1, aPrecision, N1);
          Standard_Integer aSt2 = GeomLib::NormEstim(aBSpline, aStPnt2, aPrecision, N2);

          Standard_Real aAngle = N2.Angle(N1);
          if (aSt1 < 1 && aSt2 < 1 && aAngle > myAngle)
          {
            Standard_Real aLen = GCPnts_AbscissaPoint::Length(aIso,
              aPrevParam2, aMidParam, aDefFace);

            if (aLen > myMinSize)
            {
              // insertion 
              aParams2.InsertBefore(j, aMidParam);
              continue;
            }
          }

          aPrevParam2 = aParam2;
          aPrevPnt2   = aPnt2;

          ++j;
        }
      }
    }
  }

  // insert nodes of the regular grid
  for (Standard_Integer i = 1; i <= aParams[0].Length(); ++i)
  {
    const Standard_Real aParam1 = aParams[0].Value(i);
    for (Standard_Integer j = 1; j <= aParams[1].Length(); ++j)
    {
      gp_Pnt2d aPnt2d(aParam1, aParams[1].Value(j));

      // Classify intersection point
      if (aClassifier->Perform(aPnt2d) == TopAbs_IN)
      {
        gp_Pnt aPnt;
        gFace->D0(aPnt2d.X(), aPnt2d.Y(), aPnt);
        insertVertex(aPnt, aPnt2d.Coord(), theNewVertices);
      }
    }
  }
}

//=======================================================================
//function : insertInternalVerticesOther
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscretFace::insertInternalVerticesOther(
  BRepMesh::ListOfVertex& theNewVertices)
{
  const Standard_Real aAngle = myAngle;//0.35;
  const Standard_Real aRange[2][2] = {
      { myAttribute->GetUMax(), myAttribute->GetUMin() },
      { myAttribute->GetVMax(), myAttribute->GetVMin() }
  };

  const Standard_Real                 aDefFace = myAttribute->GetDefFace();
  const Handle(BRepAdaptor_HSurface)& gFace = myAttribute->Surface();

  BRepMesh::SequenceOfReal aParams[2];
  const Standard_Integer aIsoPointsNb = 11;
  for (Standard_Integer k = 0; k < 2; ++k)
  {
    const Standard_Boolean isU = (k == 0);
    const GeomAbs_IsoType  aIsoType = isU ? GeomAbs_IsoU : GeomAbs_IsoV;
    const Standard_Integer aOtherParamsIndex = (k + 1) % 2;
    const Standard_Real (&aRange1)[2] = aRange[k];
    const Standard_Real (&aRange2)[2] = aRange[aOtherParamsIndex];

    GCPnts_TangentialDeflection aDiscretIso[aIsoPointsNb];
    const Standard_Real aStepWidth = (aRange1[0] - aRange1[1]) / aIsoPointsNb;

    // Find the most curved Iso.
    Standard_Integer aMaxIndex = 1, aMaxPointsNb = 0;
    for (Standard_Integer aIsoIt = 0; aIsoIt < aIsoPointsNb; ++aIsoIt)
    {
      Standard_Real aParam = aRange1[1] + aIsoIt * aStepWidth;
      Adaptor3d_IsoCurve aIso(gFace, aIsoType, aParam);

      Standard_Real aFirstParam = Max(aRange2[1], aIso.FirstParameter());
      Standard_Real aLastParam  = Min(aRange2[0], aIso.LastParameter());

      aDiscretIso[aIsoIt].Initialize(aIso, aFirstParam, aLastParam, 
        aAngle, 0.7 * aDefFace, 2, Precision::PConfusion(), myMinSize);

      const Standard_Integer aPointsNb = aDiscretIso[aIsoIt].NbPoints();
      if (aPointsNb > aMaxPointsNb)
      {
        aMaxPointsNb = aPointsNb;
        aMaxIndex    = aIsoIt;
      }
    }

    BRepMesh::SequenceOfReal& aParams2 = aParams[aOtherParamsIndex];
    GCPnts_TangentialDeflection& aDIso = aDiscretIso[aMaxIndex];
    for (Standard_Integer i = 1; i <= aMaxPointsNb; ++i)
      aParams2.Append(aDIso.Parameter(i));

    if (aParams2.Length() == 2)
      aParams2.InsertAfter(1, 0.5 * (aRange2[1] + aRange2[0]));
  }

  Adaptor3d_IsoCurve aIsoV;
  aIsoV.Load(gFace);

  const BRepMesh::HClassifier& aClassifier = myAttribute->ChangeClassifier();
  const Standard_Integer aUPointsNb = aParams[0].Length();
  const Standard_Integer aVPointsNb = aParams[1].Length();
  for (Standard_Integer i = 2; i < aVPointsNb; ++i)
  {
    const Standard_Real aV = aParams[1].Value(i);
    aIsoV.Load(GeomAbs_IsoV, aV);

    for (Standard_Integer j = 2; j < aUPointsNb; ++j)
    {
      const Standard_Real aU = aParams[0].Value(j);

      const gp_Pnt2d aNewPoint(aU, aV);
      if (aClassifier->Perform(aNewPoint) == TopAbs_IN)
        insertVertex(aIsoV.Value(aU), aNewPoint.Coord(), theNewVertices);
    }
  }
}

//=======================================================================
//function : checkDeflectionAndInsert
//purpose  : 
//=======================================================================
Standard_Boolean BRepMesh_FastDiscretFace::checkDeflectionAndInsert(
  const gp_Pnt&              thePnt3d,
  const gp_XY&               theUV,
  const Standard_Boolean     isDeflectionCheckOnly,
  const Standard_Real        theTriangleDeflection,
  const Standard_Real        theFaceDeflection,
  const BRepMesh_CircleTool& theCircleTool,
  BRepMesh::ListOfVertex&    theVertices,
  Standard_Real&             theMaxTriangleDeflection)
{
  if (theTriangleDeflection > theMaxTriangleDeflection)
    theMaxTriangleDeflection = theTriangleDeflection;

  if (theTriangleDeflection < theFaceDeflection)
    return Standard_True;

  if (myMinSize > Precision::Confusion())
  {
    // Iterator in the list of indexes of circles containing the node
    BRepMesh::ListOfInteger& aCirclesList = 
      const_cast<BRepMesh_CircleTool&>(theCircleTool).Select(
      myAttribute->Scale(theUV, Standard_True));
    
    Handle(NCollection_IncAllocator) aAllocator =
      new NCollection_IncAllocator(BRepMesh::MEMORY_BLOCK_SIZE_HUGE);
    BRepMesh::MapOfInteger aUsedNodes(10, aAllocator);
    BRepMesh::ListOfInteger::Iterator aCircleIt(aCirclesList);
    for (; aCircleIt.More(); aCircleIt.Next())
    {
      const BRepMesh_Triangle& aTriangle = 
        myStructure->GetElement(aCircleIt.Value());

      Standard_Integer aNodes[3];
      myStructure->ElementNodes(aTriangle, aNodes);

      for (Standard_Integer i = 0; i < 3; ++i)
      {
        const Standard_Integer aNodeId = aNodes[i];
        if (aUsedNodes.Contains(aNodeId))
          continue;

        aUsedNodes.Add(aNodeId);
        const BRepMesh_Vertex& aNode = myStructure->GetNode(aNodeId);
        const gp_Pnt& aPoint = myAttribute->GetPoint(aNode);

        if (thePnt3d.SquareDistance(aPoint) < myMinSize * myMinSize)
          return Standard_True;
      }
    }
  }

  if (isDeflectionCheckOnly)
    return Standard_False;

  insertVertex(thePnt3d, theUV, theVertices);
  return Standard_True;
}

//=======================================================================
//function : control
//purpose  : 
//=======================================================================
Standard_Real BRepMesh_FastDiscretFace::control(
  BRepMesh::ListOfVertex&  theNewVertices,
  BRepMesh_Delaun&         theTrigu,
  const Standard_Boolean   theIsFirst)
{
  Standard_Integer aTrianglesNb = myStructure->ElementsOfDomain().Extent();
  if (aTrianglesNb < 1)
    return -1.0;

  //IMPORTANT: Constants used in calculations
  const Standard_Real MinimalArea2d     = 1.e-9;
  const Standard_Real MinimalSqLength3d = 1.e-12;
  const Standard_Real aSqDefFace = myAttribute->GetDefFace() * myAttribute->GetDefFace();

  const Handle(BRepAdaptor_HSurface)& gFace = myAttribute->Surface();

  Handle(Geom_Surface) aBSpline;
  GeomAbs_SurfaceType  aSurfType = gFace->GetType();
  if (aSurfType == GeomAbs_BezierSurface)
    aBSpline = gFace->Bezier();
  else if (aSurfType == GeomAbs_BSplineSurface)
    aBSpline = gFace->BSpline();

  NCollection_DataMap<Standard_Integer, gp_Dir> aNorMap;
  BRepMesh::MapOfIntegerInteger                 aStatMap;
  NCollection_Map<BRepMesh_OrientedEdge>        aCouples(3 * aTrianglesNb);
  const BRepMesh_CircleTool& aCircles = theTrigu.Circles();

  // Perform refinement passes
  // Define the number of iterations
  Standard_Integer       aIterationsNb = 11;
  const Standard_Integer aPassesNb = (theIsFirst ? 1 : aIterationsNb);
  // Initialize stop condition
  Standard_Real aMaxSqDef = -1.;
  Standard_Integer aPass = 1, aInsertedNb = 1;
  Standard_Boolean isAllDegenerated = Standard_False;
  for (; aPass <= aPassesNb && aInsertedNb && !isAllDegenerated; ++aPass)
  {
    theNewVertices.Clear();

    // Reset stop condition
    aInsertedNb      = 0;
    aMaxSqDef        = -1.;
    isAllDegenerated = Standard_True;

    aTrianglesNb = myStructure->ElementsOfDomain().Extent();
    if (aTrianglesNb < 1)
      break;

    // Iterate on current triangles
    const BRepMesh::MapOfInteger& aTriangles = myStructure->ElementsOfDomain();
    BRepMesh::MapOfInteger::Iterator aTriangleIt(aTriangles);
    for (; aTriangleIt.More(); aTriangleIt.Next())
    {
      const Standard_Integer aTriangleId = aTriangleIt.Key();
      const BRepMesh_Triangle& aCurrentTriangle = myStructure->GetElement(aTriangleId);

      if (aCurrentTriangle.Movability() == BRepMesh_Deleted)
        continue;

      Standard_Integer v[3];
      myStructure->ElementNodes(aCurrentTriangle, v);

      Standard_Integer e[3];
      Standard_Boolean o[3];
      aCurrentTriangle.Edges(e, o);

      gp_XY xy[3];
      gp_XYZ p[3];
      Standard_Boolean m[3];
      for (Standard_Integer i = 0; i < 3; ++i)
      {
        m[i] = (myStructure->GetLink(e[i]).Movability() == BRepMesh_Frontier);

        const BRepMesh_Vertex& aVertex = myStructure->GetNode(v[i]);
        xy[i] = myAttribute->Scale(aVertex.Coord(), Standard_False);
        p [i] = myAttribute->GetPoint(aVertex).Coord();
      }

      gp_XYZ aLinkVec[3];
      Standard_Boolean isDegeneratedTri = Standard_False;
      for (Standard_Integer i = 0; i < 3 && !isDegeneratedTri; ++i)
      {
        aLinkVec[i] = p[(i + 1) % 3] - p[i];
        isDegeneratedTri = (aLinkVec[i].SquareModulus() < MinimalSqLength3d);
      }

      if (isDegeneratedTri) 
        continue;

      isAllDegenerated = Standard_False;

      // Check triangle area in 2d
      if (Abs((xy[1]-xy[0])^(xy[2]-xy[1])) < MinimalArea2d)
        continue;

      // Check triangle normal
      gp_Pnt pDef;
      Standard_Real aSqDef = -1.;
      Standard_Boolean isSkipped = Standard_False;
      gp_XYZ normal(aLinkVec[0] ^ aLinkVec[1]);
      try
      {
        OCC_CATCH_SIGNALS

        normal.Normalize();

        // Check deflection on triangle
        gp_XY mi2d = (xy[0] + xy[1] + xy[2]) / 3.0;
        gFace->D0(mi2d.X(), mi2d.Y(), pDef);
        aSqDef = Abs(normal * (pDef.XYZ() - p[0]));
        aSqDef *= aSqDef;

        isSkipped = !checkDeflectionAndInsert(pDef, mi2d, theIsFirst, 
          aSqDef, aSqDefFace, aCircles, theNewVertices, aMaxSqDef);

        if (isSkipped)
          break;
      }
      catch (Standard_Failure)
      {
        continue;
      }

      for (Standard_Integer i = 0; i < 3 && !isSkipped; ++i)
      {
        if (m[i]) // is a boundary
          continue;

        Standard_Integer j = (i + 1) % 3;
        // Check if this link was already processed
        Standard_Integer aFirstVertex, aLastVertex;
        if (v[i] < v[j])
        { 
          aFirstVertex = v[i];
          aLastVertex = v[j];
        }
        else
        {
          aFirstVertex = v[j];
          aLastVertex = v[i];
        }

        if (aCouples.Add(BRepMesh_OrientedEdge(aFirstVertex, aLastVertex)))
        {
          // Check deflection on edge 1
          gp_XY mi2d = (xy[i] + xy[j]) * 0.5;
          gFace->D0(mi2d.X(), mi2d.Y(), pDef);
          gp_Lin aLin(p[i], gp_Vec(p[i], p[j]));
          aSqDef = aLin.SquareDistance(pDef);

          isSkipped = !checkDeflectionAndInsert(pDef, mi2d, theIsFirst, 
            aSqDef, aSqDefFace, aCircles, theNewVertices, aMaxSqDef);
        }
      }

      if (isSkipped)
        break;

      //check normal on bsplines
      if (theIsFirst && !aBSpline.IsNull())
      {
        gp_Dir N[3] = { gp::DZ(), gp::DZ(), gp::DZ() };
        Standard_Integer aSt[3];

        for (Standard_Integer i = 0; i < 3; ++i)
        {
          if (aNorMap.IsBound(v[i]))
          {
            aSt[i] = aStatMap.Find(v[i]);
            N[i] = aNorMap.Find(v[i]);
          }
          else
          {
            aSt[i] = GeomLib::NormEstim(aBSpline, gp_Pnt2d(xy[i]), Precision::Confusion(), N[i]);
            aStatMap.Bind(v[i], aSt[i]);
            aNorMap.Bind(v[i], N[i]);
          }
        }

        Standard_Real aAngle[3];
        for (Standard_Integer i = 0; i < 3; ++i)
          aAngle[i] = N[(i + 1) % 3].Angle(N[i]);

        if (aSt[0] < 1 && aSt[1] < 1 && aSt[2] < 1)
        {
          if (aAngle[0] > myAngle || aAngle[1] > myAngle || aAngle[2] > myAngle)
          {
            aMaxSqDef = -1.;
            break;
          }
        }
      }
    }

    if (theIsFirst)
      continue;

    if (addVerticesToMesh(theNewVertices, theTrigu))
      ++aInsertedNb;
  }

  return (aMaxSqDef < 0) ? aMaxSqDef : Sqrt(aMaxSqDef);
}

//=======================================================================
//function : add
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscretFace::add(const TopoDS_Vertex& theVertex)
{
  if (theVertex.Orientation() != TopAbs_INTERNAL)
    return;

  try
  {
    OCC_CATCH_SIGNALS

    gp_Pnt2d aPnt2d = BRep_Tool::Parameters(theVertex, myAttribute->Face());
    // check UV values for internal vertices
    if (myAttribute->ChangeClassifier()->Perform(aPnt2d) != TopAbs_IN)
      return;

    NCollection_Handle<FixedVExplorer> aFixedVExplorer = new FixedVExplorer(theVertex);
    Standard_Integer aIndex = myAttribute->GetVertexIndex(aFixedVExplorer);
    gp_XY anUV = BRepMesh_ShapeTool::FindUV(aIndex, aPnt2d,
      theVertex, BRep_Tool::Tolerance(theVertex), myAttribute);

    Standard_Integer aTmpId1, aTmpId2;
    anUV = myAttribute->Scale(anUV, Standard_True);
    myAttribute->AddNode(aIndex, anUV, BRepMesh_Fixed, aTmpId1, aTmpId2);
  }
  catch (Standard_Failure)
  {
  }
}

//=======================================================================
//function : insertVertex
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscretFace::insertVertex(
  const gp_Pnt&           thePnt3d,
  const gp_XY&            theUV,
  BRepMesh::ListOfVertex& theVertices)
{
  Standard_Integer aNbLocat = myAttribute->LastPointId();
  myAttribute->ChangeSurfacePoints()->Bind(++aNbLocat, thePnt3d);

  gp_XY aPnt2d  = myAttribute->Scale(theUV, Standard_True);
  BRepMesh_Vertex aVertex(aPnt2d, aNbLocat, BRepMesh_Free);
  theVertices.Append(aVertex);
}

//=======================================================================
//function : commitSurfaceTriangulation
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscretFace::commitSurfaceTriangulation()
{
  if (myAttribute.IsNull() || !myAttribute->IsValid())
    return;

  const TopoDS_Face& aFace = myAttribute->Face();
  BRepMesh_ShapeTool::NullifyFace(aFace);

  Handle(BRepMesh_DataStructureOfDelaun)& aStructure = myAttribute->ChangeStructure();
  const BRepMesh::MapOfInteger&           aTriangles = aStructure->ElementsOfDomain();

  if (aTriangles.IsEmpty())
  {
    myAttribute->SetStatus(BRepMesh_Failure);
    return;
  }

  BRepMesh::HIMapOfInteger& aVetrexEdgeMap = myAttribute->ChangeVertexEdgeMap();

  // Store triangles
  Standard_Integer aVerticesNb  = aVetrexEdgeMap->Extent();
  Standard_Integer aTrianglesNb = aTriangles.Extent();
  Handle(Poly_Triangulation) aNewTriangulation =
    new Poly_Triangulation(aVerticesNb, aTrianglesNb, Standard_True);

  Poly_Array1OfTriangle& aPolyTrianges = aNewTriangulation->ChangeTriangles();

  Standard_Integer aTriangeId = 1;
  BRepMesh::MapOfInteger::Iterator aTriIt(aTriangles);
  for (; aTriIt.More(); aTriIt.Next())
  {
    const BRepMesh_Triangle& aCurElem = aStructure->GetElement(aTriIt.Key());

    Standard_Integer aNode[3];
    aStructure->ElementNodes(aCurElem, aNode);

    Standard_Integer aNodeId[3];
    for (Standard_Integer i = 0; i < 3; ++i)
      aNodeId[i] = aVetrexEdgeMap->FindIndex(aNode[i]);

    aPolyTrianges(aTriangeId++).Set(aNodeId[0], aNodeId[1], aNodeId[2]);
  }

  // Store mesh nodes
  TColgp_Array1OfPnt&   aNodes   = aNewTriangulation->ChangeNodes();
  TColgp_Array1OfPnt2d& aNodes2d = aNewTriangulation->ChangeUVNodes();

  for (Standard_Integer i = 1; i <= aVerticesNb; ++i)
  {
    Standard_Integer       aVertexId = aVetrexEdgeMap->FindKey(i);
    const BRepMesh_Vertex& aVertex   = aStructure->GetNode(aVertexId);
    const gp_Pnt&          aPoint    = myAttribute->GetPoint(aVertex);

    aNodes(i)   = aPoint;
    aNodes2d(i) = aVertex.Coord();
  }

  aNewTriangulation->Deflection(myAttribute->GetDefFace());
  BRepMesh_ShapeTool::AddInFace(aFace, aNewTriangulation);

  // Delete unused data
  myAttribute->ChangeStructure().Nullify();
  myAttribute->ChangeSurfacePoints().Nullify();
  myAttribute->ChangeSurfaceVertices().Nullify();

  myAttribute->ChangeClassifier().Nullify();
  myAttribute->ChangeLocation2D().Nullify();
  myAttribute->ChangeVertexEdgeMap().Nullify();
}
