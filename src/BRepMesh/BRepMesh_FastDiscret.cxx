// Created on: 1996-02-27
// Created by: Ekaterina SMIRNOVA
// Copyright (c) 1996-1999 Matra Datavision
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

#include <BRepMesh_FastDiscret.hxx>

#include <BRepMesh_WireChecker.hxx>
#include <BRepMesh_FastDiscretFace.hxx>
#include <BRepMesh_FaceAttribute.hxx>
#include <BRepMesh_DataStructureOfDelaun.hxx>
#include <BRepMesh_GeomTool.hxx>
#include <BRepMesh_PairOfPolygon.hxx>
#include <BRepMesh_Classifier.hxx>
#include <BRepMesh_EdgeParameterProvider.hxx>
#include <BRepMesh_IEdgeTool.hxx>
#include <BRepMesh_EdgeTessellator.hxx>
#include <BRepMesh_EdgeTessellationExtractor.hxx>

#include <BRepAdaptor_Curve.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <BRepAdaptor_HSurface.hxx>

#include <Bnd_Box.hxx>
#include <BRepTools.hxx>
#include <BRepBndLib.hxx>
#include <BndLib_Add3dCurve.hxx>
#include <Poly_Triangulation.hxx>
#include <Poly_PolygonOnTriangulation.hxx>

#include <Precision.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom_Surface.hxx>
#include <Geom_Plane.hxx>
#include <GeomAbs_SurfaceType.hxx>
#include <Extrema_LocateExtPC.hxx>

#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TColGeom2d_SequenceOfCurve.hxx>
#include <SortTools_ShellSortOfReal.hxx>
#include <TCollection_CompareOfReal.hxx>

#include <TopTools_SequenceOfShape.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>

#include <TopAbs.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>

#include <OSD_Parallel.hxx>

#include <Standard_ErrorHandler.hxx>
#include <Standard_Failure.hxx>
#include <NCollection_IncAllocator.hxx>

#include <BRep_ListIteratorOfListOfPointRepresentation.hxx>
#include <BRep_PointRepresentation.hxx>

#include <vector>

#define UVDEFLECTION 1.e-05

IMPLEMENT_STANDARD_HANDLE (BRepMesh_FastDiscret, Standard_Transient)
IMPLEMENT_STANDARD_RTTIEXT(BRepMesh_FastDiscret, Standard_Transient)

//=======================================================================
//function : BRepMesh_FastDiscret
//purpose  : 
//=======================================================================
BRepMesh_FastDiscret::BRepMesh_FastDiscret(
  const Standard_Real    theDefle,
  const Standard_Real    theAngl,
  const Bnd_Box&         theBox,
  const Standard_Boolean theWithShare,
  const Standard_Boolean theInshape,
  const Standard_Boolean theRelative,
  const Standard_Boolean theShapetrigu,
  const Standard_Boolean isInParallel,
  const Standard_Real    theMinSize,
  const Standard_Boolean isInternalVerticesMode,
  const Standard_Boolean isControlSurfaceDeflection)
: myAngle (theAngl),
  myDeflection (theDefle),
  myWithShare (theWithShare),
  myInParallel (isInParallel),
  myRelative (theRelative),
  myShapetrigu (theShapetrigu), 
  myInshape (theInshape),
  myBoundaryVertices(new BRepMesh::DMapOfVertexInteger),
  myBoundaryPoints(new BRepMesh::DMapOfIntegerPnt),
  myMinSize(theMinSize),
  myInternalVerticesMode(isInternalVerticesMode),
  myIsControlSurfaceDeflection(isControlSurfaceDeflection)
{
  if ( myRelative )
    BRepMesh_ShapeTool::BoxMaxDimension(theBox, myDtotale);
}

//=======================================================================
//function : BRepMesh_FastDiscret
//purpose  : 
//=======================================================================
BRepMesh_FastDiscret::BRepMesh_FastDiscret(
  const TopoDS_Shape&    theShape,
  const Standard_Real    theDefle,
  const Standard_Real    theAngl,
  const Bnd_Box&         theBox,
  const Standard_Boolean theWithShare,
  const Standard_Boolean theInshape,
  const Standard_Boolean theRelative,
  const Standard_Boolean theShapetrigu,
  const Standard_Boolean isInParallel,
  const Standard_Real    theMinSize,
  const Standard_Boolean isInternalVerticesMode,
  const Standard_Boolean isControlSurfaceDeflection)
: myAngle (theAngl),
  myDeflection (theDefle),
  myWithShare (theWithShare),
  myInParallel (isInParallel),
  myRelative (theRelative),
  myShapetrigu (theShapetrigu),
  myInshape (theInshape),
  myBoundaryVertices(new BRepMesh::DMapOfVertexInteger),
  myBoundaryPoints(new BRepMesh::DMapOfIntegerPnt),
  myMinSize(theMinSize),
  myInternalVerticesMode(isInternalVerticesMode),
  myIsControlSurfaceDeflection(isControlSurfaceDeflection)
{
  if ( myRelative )
    BRepMesh_ShapeTool::BoxMaxDimension(theBox, myDtotale);

  Perform(theShape);
}

//=======================================================================
//function : InitSharedFaces
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscret::InitSharedFaces(const TopoDS_Shape& theShape)
{
  TopExp::MapShapesAndAncestors(theShape, TopAbs_EDGE, TopAbs_FACE, mySharedFaces);
}

//=======================================================================
//function : Perform(shape)
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscret::Perform(const TopoDS_Shape& theShape)
{
  InitSharedFaces(theShape);

  std::vector<TopoDS_Face> aFaces;
  TopExp_Explorer anExplorer(theShape, TopAbs_FACE);
  for (; anExplorer.More(); anExplorer.Next())
  {
    const TopoDS_Face& aFace = TopoDS::Face(anExplorer.Current());
    Add(aFace);
    aFaces.push_back(aFace);
  }
  
#if defined(_OPENMP)
  if (myInParallel)
  {
    int i, n = aFaces.size();
#pragma omp parallel for private(i)
    for (i = 0; i < n; ++i)
      Process(aFaces[i]);
  }
  else
    OSD_Parallel::ForEach(aFaces.begin(), aFaces.end(), *this, !myInParallel);
#else
  OSD_Parallel::ForEach(aFaces.begin(), aFaces.end(), *this, !myInParallel);
#endif
}


//=======================================================================
//function : Process
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscret::Process(const TopoDS_Face& theFace) const
{
  Handle(BRepMesh_FaceAttribute) anAttribute;
  if (GetFaceAttribute(theFace, anAttribute))
  {
    try
    {
      OCC_CATCH_SIGNALS

      BRepMesh_FastDiscretFace aTool(GetAngle(), myMinSize, 
        myInternalVerticesMode, myIsControlSurfaceDeflection);
      aTool.Perform(anAttribute);
    }
    catch (Standard_Failure)
    {
      anAttribute->SetStatus(BRepMesh_Failure);
    }
  }
}

//=======================================================================
//function : resetDataStructure
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscret::resetDataStructure()
{
  Handle(NCollection_IncAllocator) aAllocator;
  if (myAttribute->ChangeStructure().IsNull())
    aAllocator = new NCollection_IncAllocator(BRepMesh::MEMORY_BLOCK_SIZE_HUGE);
  else
    aAllocator = myAttribute->ChangeStructure()->Allocator();

  myAttribute->Clear();
  aAllocator->Reset(Standard_False);
  Handle(BRepMesh_DataStructureOfDelaun) aStructure = 
    new BRepMesh_DataStructureOfDelaun(aAllocator);

  const Standard_Real aTolU = myAttribute->ToleranceU();
  const Standard_Real aTolV = myAttribute->ToleranceV();
  const Standard_Real uCellSize = 14.0 * aTolU;
  const Standard_Real vCellSize = 14.0 * aTolV;

  aStructure->Data()->SetCellSize ( uCellSize, vCellSize);
  aStructure->Data()->SetTolerance( aTolU    , aTolV    );

  myAttribute->ChangeStructure() = aStructure;
}

//=======================================================================
//function : Add(face)
//purpose  : 
//=======================================================================
Standard_Integer BRepMesh_FastDiscret::Add(const TopoDS_Face& theFace)
{
  try
  {
    OCC_CATCH_SIGNALS

    // Initialize face attributes
    myAttribute.Nullify();
    GetFaceAttribute(theFace, myAttribute);
    if (myAttribute.IsNull())
    {
      myAttribute = new BRepMesh_FaceAttribute(theFace,
        myBoundaryVertices, myBoundaryPoints);

      myAttributes.Bind(theFace, myAttribute);
    }

    BRepMesh::HIMapOfInteger&            aVertexEdgeMap = myAttribute->ChangeVertexEdgeMap();
    BRepMesh::HDMapOfShapePairOfPolygon& aInternalEdges = myAttribute->ChangeInternalEdges();

    resetDataStructure();

    if (!myWithShare)
    {
      myEdges.Clear();
      myBoundaryVertices->Clear();
      myBoundaryPoints->Clear();
    }

    Standard_Real defedge;
    Standard_Integer nbEdge = 0;
    Standard_Real savangle = myAngle;
    Standard_Real cdef;
    Standard_Real maxdef = 2.* BRepMesh_ShapeTool::MaxFaceTolerance(theFace);

    Standard_Real defface = 0.;
    if (!myRelative)
      defface = Max(myDeflection, maxdef);

    NCollection_Sequence<EdgePCurve>  aPCurves;
    NCollection_Sequence<TopoDS_Edge> aFaceEdges;

    const TopoDS_Face&                  aFace = myAttribute->Face();
    const Handle(BRepAdaptor_HSurface)& gFace = myAttribute->Surface();
    TopExp_Explorer aWireIt(aFace, TopAbs_WIRE);
    for (; aWireIt.More(); aWireIt.Next())
    {
      TopExp_Explorer aEdgeIt(aWireIt.Current(), TopAbs_EDGE);
      for (; aEdgeIt.More(); aEdgeIt.Next(), ++nbEdge)
      {
        const TopoDS_Edge& aEdge = TopoDS::Edge(aEdgeIt.Current());
        if (!myMapdefle.IsBound(aEdge))
        {
          if (myRelative)
          {
            if (myEdges.IsBound(aEdge))
            {
              const BRepMesh_PairOfPolygon& aPair = myEdges.Find(aEdge);
              const Handle(Poly_PolygonOnTriangulation)& aPolygon = aPair.First();
              defedge = aPolygon->Deflection();
            }
            else
            {
              defedge = BRepMesh_ShapeTool::RelativeEdgeDeflection(
                aEdge, myDeflection, myDtotale, cdef);

              myAngle = savangle * cdef;
            }

            defface += defedge;
            defface = Max(maxdef, defface);
          }
          else
          {
            defedge = myDeflection;
          }

          defedge = Max(maxdef, defedge);
          defedge = Max(UVDEFLECTION, defedge);
          myMapdefle.Bind(aEdge, defedge);
        }
        else
        {
          defedge = myMapdefle(aEdge);
          if ( myRelative )
          {
            defface += defedge;
            defface = Max(maxdef, defface);
          }
        }

        Standard_Real aFirstParam, aLastParam;
        Handle(Geom2d_Curve) aCurve2d = 
          BRep_Tool::CurveOnSurface(aEdge, aFace, aFirstParam, aLastParam);

        if (aCurve2d.IsNull())
          continue;

        EdgePCurve aPCurve = { aCurve2d, aFirstParam, aLastParam };
        aPCurves.Append(aPCurve);
        aFaceEdges.Append(aEdge);

        add(aEdge, aPCurve, defedge);
        myAngle = savangle;
      }
    }

    if ( nbEdge == 0 || aVertexEdgeMap->Extent() < 3 )
    {
      myAttribute->ChangeStructure().Nullify();
      myAttribute->SetStatus(BRepMesh_Failure);
      return myAttribute->GetStatus();
    }

    if ( myRelative )
    {
      defface = defface / nbEdge;
    }
    else
    {
      defface = myDeflection;
    }

    if ( myWithShare )
      defface = Max(maxdef, defface);

    TopLoc_Location aLoc;
    Handle(Poly_Triangulation) aTriangulation = BRep_Tool::Triangulation(aFace, aLoc);

    if (!myShapetrigu || aTriangulation.IsNull())
    {
      Standard_Real xCur, yCur;
      Standard_Real maxX, minX, maxY, minY;

      minX = minY = 1.e100;
      maxX = maxY =-1.e100;

      Standard_Integer ipn = 0;
      Standard_Integer i1 = 1;
      for ( i1 = 1; i1 <= aVertexEdgeMap->Extent(); ++i1 )
      {
        const BRepMesh_Vertex& aVertex = 
          myAttribute->ChangeStructure()->GetNode(aVertexEdgeMap->FindKey(i1));

        ++ipn;

        xCur = aVertex.Coord().X();
        yCur = aVertex.Coord().Y();

        minX = Min(xCur, minX);
        maxX = Max(xCur, maxX);
        minY = Min(yCur, minY);
        maxY = Max(yCur, maxY);
      }

      Standard_Real myumin = minX;
      Standard_Real myumax = maxX;
      Standard_Real myvmin = minY;
      Standard_Real myvmax = maxY;

      const Standard_Real umin = gFace->FirstUParameter();
      const Standard_Real umax = gFace->LastUParameter();
      const Standard_Real vmin = gFace->FirstVParameter();
      const Standard_Real vmax = gFace->LastVParameter();

      if (myumin < umin || myumax > umax)
      {
        if (gFace->IsUPeriodic())
        {
          if ((myumax - myumin) > (umax - umin))
            myumax = myumin + (umax - umin);
        }
        else
        {
          if (umin > myumin)
            myumin = umin;

          if (umax < myumax)
            myumax = umax;
        }
      }

      if (myvmin < vmin || myvmax > vmax)
      {
        if (gFace->IsVPeriodic())
        {
          if ((myvmax - myvmin) > (vmax - vmin))
            myvmax = myvmin + (vmax - vmin);
        }
        else
        {
          if ( vmin > myvmin )
            myvmin = vmin;

          if (vmax < myvmax)
            myvmax = vmax;
        }
      }

      GeomAbs_SurfaceType aSurfType = gFace->GetType();
      // Fast verification of the validity of calculated limits.
      // If wrong, sure a problem of pcurve.
      if (aSurfType == GeomAbs_BezierSurface &&
         (myumin < -0.5 || myumax > 1.5 || myvmin < -0.5 || myvmax > 1.5) )
      {
        myAttribute->ChangeStructure().Nullify();
        myAttribute->SetStatus(BRepMesh_Failure);
        return myAttribute->GetStatus();
      }

      //define parameters for correct parametrics
      Standard_Real deltaX = 1.0;
      Standard_Real deltaY = 1.0;

      {
        BRepMesh::HClassifier& aClassifier = myAttribute->ChangeClassifier();
        BRepMesh_WireChecker aDFaceChecker(aFace, Precision::PConfusion(),
          aInternalEdges, aVertexEdgeMap, myAttribute->ChangeStructure(),
          myumin, myumax, myvmin, myvmax, myInParallel );

        aDFaceChecker.ReCompute(aClassifier);
        BRepMesh_Status aCheckStatus = aDFaceChecker.Status();

        if (aCheckStatus == BRepMesh_SelfIntersectingWire)
        {
          Standard_Integer nbmaill = 0;
          Standard_Real eps = Precision::Confusion();
          while (nbmaill < 5 && aCheckStatus != BRepMesh_ReMesh)
          {
            ++nbmaill;

            resetDataStructure();
            for (Standard_Integer j = 1; j <= aFaceEdges.Length(); ++j)
            {
              const TopoDS_Edge& anEdge = aFaceEdges(j);
              if (myEdges.IsBound(anEdge))
                myEdges.UnBind(anEdge);

              defedge = Max(myMapdefle(anEdge) / 3.0, eps);
              myMapdefle.Bind(anEdge, defedge);

              add(anEdge, aPCurves(j), defedge);
            }

            aDFaceChecker.ReCompute(aClassifier);
            if (aDFaceChecker.Status() == BRepMesh_NoError)
              aCheckStatus = BRepMesh_ReMesh;
          }
        }

        myAttribute->SetStatus(aCheckStatus);
        if (!myAttribute->IsValid())
        {
          myAttribute->ChangeStructure().Nullify();
          return myAttribute->GetStatus();
        }
      }

      // try to find the real length:
      // akm (bug OCC16) : We must calculate these measures in non-singular
      //     parts of face. Let's try to compute average value of three
      //     (umin, (umin+umax)/2, umax), and respectively for v.
      //                 vvvvv
      Standard_Real longu = 0.0, longv = 0.0; //, last , first;
      gp_Pnt P11, P12, P21, P22, P31, P32;

      Standard_Real du = 0.05 * ( myumax - myumin );
      Standard_Real dv = 0.05 * ( myvmax - myvmin );
      Standard_Real dfuave = 0.5 * ( myumin + myumax );
      Standard_Real dfvave = 0.5 * ( myvmin + myvmax );
      Standard_Real dfucur, dfvcur;

      // U loop
      gFace->D0(myumin, myvmin, P11);
      gFace->D0(myumin, dfvave, P21);
      gFace->D0(myumin, myvmax, P31);
      for (i1=1, dfucur=myumin+du; i1 <= 20; i1++, dfucur+=du)
      {
        gFace->D0(dfucur, myvmin, P12);
        gFace->D0(dfucur, dfvave, P22);
        gFace->D0(dfucur, myvmax, P32);
        longu += ( P11.Distance(P12) + P21.Distance(P22) + P31.Distance(P32) );
        P11 = P12;
        P21 = P22;
        P31 = P32;
      }

      // V loop
      gFace->D0(myumin, myvmin, P11);
      gFace->D0(dfuave, myvmin, P21);
      gFace->D0(myumax, myvmin, P31);
      for (i1=1, dfvcur=myvmin+dv; i1 <= 20; i1++, dfvcur+=dv)
      {
        gFace->D0(myumin, dfvcur, P12);
        gFace->D0(dfuave, dfvcur, P22);
        gFace->D0(myumax, dfvcur, P32);
        longv += ( P11.Distance(P12) + P21.Distance(P22) + P31.Distance(P32) );
        P11 = P12;
        P21 = P22;
        P31 = P32;
      }

      longu /= 3.;
      longv /= 3.;
      // akm (bug OCC16) ^^^^^

      if (longu <= 1.e-16 || longv <= 1.e-16)
      {
        //yes, it is seen!!
        myAttribute->ChangeStructure().Nullify();
        myAttribute->SetStatus(BRepMesh_Failure);
        return myAttribute->GetStatus();
      }


      if (aSurfType == GeomAbs_Torus)
      {
        gp_Torus Tor = gFace->Torus();
        Standard_Real r = Tor.MinorRadius(), R = Tor.MajorRadius();
        Standard_Real Du, Dv;//, pasu, pasv;

        Dv = Max(1.0e0 - (defface/r),0.0e0) ;
        Standard_Real oldDv = 2.0 * ACos (Dv);
        oldDv = Min(oldDv, myAngle);
        Dv  =  0.9*oldDv; //TWOTHIRD * oldDv;
        Dv = oldDv;

        Standard_Integer nbV = Max((Standard_Integer)((myvmax-myvmin)/Dv), 2);
        Dv = (myvmax-myvmin)/(nbV+1);

        Standard_Real ru = R + r;
        if ( ru > 1.e-16 )
        {
          Du = Max(1.0e0 - (defface/ru),0.0e0);
          Du  = (2.0 * ACos (Du));
          Du = Min(Du, myAngle);
          Standard_Real aa = sqrt(Du*Du + oldDv*oldDv);

          if (aa < gp::Resolution())
          {
            myAttribute->ChangeStructure().Nullify();
            return myAttribute->GetStatus();
          }

          Du = Du * Min(oldDv, Du) / aa;
        }
        else
        {
          Du = Dv;
        }

        Standard_Integer nbU = Max((Standard_Integer)((myumax-myumin)/Du), 2);
        nbU = Max(nbU, (Standard_Integer)(nbV*(myumax-myumin)*R/((myvmax-myvmin)*r)/5.));
      
        Du = (myumax-myumin)/(nbU+1);
        //-- DeltaX and DeltaY are chosen so that to avoid "jumping" 
        //-- of points on the grid
        deltaX = Du;
        deltaY = Dv;
      }
      else if (aSurfType == GeomAbs_Cylinder)
      {
        gp_Cylinder Cyl = gFace->Cylinder();
        Standard_Real R = Cyl.Radius();

        // Calculate parameters for iteration in U direction
        Standard_Real Du = 1.0 - (defface/R);
        if (Du < 0.0)
          Du = 0.0;

        Du = 2.0 * ACos (Du);
        if (Du > GetAngle())
          Du = GetAngle();

        deltaX = Du / longv;
        deltaY = 1.;
      }
      else
      {
        deltaX = (myumax-myumin)/longu;
        deltaY = (myvmax-myvmin)/longv;
      }

      // Restore face attribute
      myAttribute->SetDefFace(defface);
      myAttribute->SetUMax(myumax);
      myAttribute->SetVMax(myvmax);
      myAttribute->SetUMin(myumin);
      myAttribute->SetVMin(myvmin);
      myAttribute->SetDeltaX(deltaX);
      myAttribute->SetDeltaY(deltaY);
    }
  }
  catch(Standard_Failure)
  {
    myAttribute->SetStatus(BRepMesh_Failure);
  }

  myAttribute->ChangeMeshNodes() = 
    myAttribute->ChangeStructure()->Data()->Vertices();

  myAttribute->ChangeStructure().Nullify();
  return myAttribute->GetStatus();
}

//=======================================================================
//function : getEdgeAttributes
//purpose  :
//=======================================================================
Standard_Boolean BRepMesh_FastDiscret::getEdgeAttributes(
  const TopoDS_Edge&                      theEdge,
  const BRepMesh_FastDiscret::EdgePCurve& thePCurve,
  const Standard_Real                     theDefEdge,
  BRepMesh_FastDiscret::EdgeAttributes&   theAttributes) const
{
  EdgeAttributes& aEAttr = theAttributes;

  // Get vertices
  TopExp::Vertices(theEdge, aEAttr.FirstVertex, aEAttr.LastVertex);
  if (aEAttr.FirstVertex.IsNull() || aEAttr.LastVertex.IsNull())
    return Standard_False;

  // Get range on 2d curve
  const TopoDS_Face& aFace = myAttribute->Face();
  BRep_Tool::Range(theEdge, aFace, aEAttr.FirstParam, aEAttr.LastParam);

  // Get end points on 2d curve
  BRep_Tool::UVPoints(theEdge, aFace, aEAttr.FirstUV, aEAttr.LastUV);

  aEAttr.IsSameUV =
    aEAttr.FirstUV.IsEqual(aEAttr.LastUV, Precision::PConfusion());

  //Control tolerance of vertices
  const Handle(BRepAdaptor_HSurface)& gFace = myAttribute->Surface();
  gp_Pnt pFirst = gFace->Value(aEAttr.FirstUV.X(), aEAttr.FirstUV.Y());
  gp_Pnt pLast  = gFace->Value(aEAttr.LastUV.X(),  aEAttr.LastUV.Y());

  aEAttr.MinDist = 10. * Max(pFirst.Distance(BRep_Tool::Pnt(aEAttr.FirstVertex)),
                             pLast .Distance(BRep_Tool::Pnt(aEAttr.LastVertex)));

  if (aEAttr.MinDist < BRep_Tool::Tolerance(aEAttr.FirstVertex) ||
      aEAttr.MinDist < BRep_Tool::Tolerance(aEAttr.LastVertex))
  {
    aEAttr.MinDist = theDefEdge;
  }

  if (aEAttr.IsSameUV)
  {
    // 1. is it really sameUV without being degenerated
    gp_Pnt2d uvF, uvL;
    thePCurve.Curve2d->D0(thePCurve.FirstParam, uvF);
    thePCurve.Curve2d->D0(thePCurve.LastParam,  uvL);

    if (!aEAttr.FirstUV.IsEqual(uvF, Precision::PConfusion()))
      aEAttr.FirstUV = uvF;

    if (!aEAttr.LastUV.IsEqual(uvL, Precision::PConfusion()))
      aEAttr.LastUV = uvL;
  }

  return Standard_True;
}

//=======================================================================
//function : registerEdgeVertices
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscret::registerEdgeVertices(
  BRepMesh_FastDiscret::EdgeAttributes& theAttributes,
  Standard_Integer&                     ipf,
  Standard_Integer&                     ivf,
  Standard_Integer&                     isvf,
  Standard_Integer&                     ipl,
  Standard_Integer&                     ivl,
  Standard_Integer&                     isvl)
{
  EdgeAttributes& aEAttr = theAttributes;
  if (aEAttr.FirstVExtractor.IsNull())
  {
    // Use edge geometry to produce tesselation.
    aEAttr.FirstVExtractor = 
      new TopoDSVExplorer(aEAttr.FirstVertex, aEAttr.IsSameUV, aEAttr.LastVertex);
  }

  if (aEAttr.LastVExtractor.IsNull())
  {
    // Use edge geometry to produce tesselation.
    aEAttr.LastVExtractor = 
      new TopoDSVExplorer(aEAttr.LastVertex, aEAttr.IsSameUV, aEAttr.FirstVertex);
  }

  gp_XY aTmpUV;
  // Process first vertex
  ipf = myAttribute->GetVertexIndex(aEAttr.FirstVExtractor, Standard_True);
  aTmpUV = BRepMesh_ShapeTool::FindUV(ipf, aEAttr.FirstUV, aEAttr.FirstVertex, 
    aEAttr.MinDist, myAttribute);

  myAttribute->AddNode(ipf, aTmpUV, BRepMesh_Frontier, ivf, isvf);

  // Process last vertex
  ipl = aEAttr.LastVertex.IsSame(aEAttr.FirstVertex) ? ipf :
    myAttribute->GetVertexIndex(aEAttr.LastVExtractor, Standard_True);
  aTmpUV = BRepMesh_ShapeTool::FindUV(ipl, aEAttr.LastUV, aEAttr.LastVertex, 
    aEAttr.MinDist, myAttribute);

  myAttribute->AddNode(ipl, aTmpUV, BRepMesh_Frontier, ivl, isvl);
}

//=======================================================================
//function : add
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscret::add(
  const TopoDS_Edge&                      theEdge,
  const BRepMesh_FastDiscret::EdgePCurve& thePCurve,
  const Standard_Real                     theDefEdge)
{
  const TopAbs_Orientation orEdge = theEdge.Orientation();
  if (orEdge == TopAbs_EXTERNAL)
    return;

  EdgeAttributes aEAttr;
  if (!getEdgeAttributes(theEdge, thePCurve, theDefEdge, aEAttr))
    return;

  if (!myEdges.IsBound(theEdge))
  {
    update(theEdge, thePCurve.Curve2d, theDefEdge, aEAttr);
    return;
  }

  Standard_Integer ipf, ivf, isvf, ipl, ivl, isvl;
  registerEdgeVertices(aEAttr, ipf, ivf, isvf, ipl, ivl, isvl);

  // If this Edge has been already checked and it is not degenerated, 
  // the points of the polygon calculated at the first check are retrieved :

  // retrieve the polygone:
  const BRepMesh_PairOfPolygon&              aPair    = myEdges.Find(theEdge);
  const Handle(Poly_PolygonOnTriangulation)& aPolygon = aPair.First();
  const TColStd_Array1OfInteger&             aNodes   = aPolygon->Nodes();
  Handle(TColStd_HArray1OfReal)              aParams  = aPolygon->Parameters();

  // creation anew:
  const Standard_Integer  aNodesNb = aNodes.Length();
  TColStd_Array1OfInteger aNewNodes (1, aNodesNb);
  TColStd_Array1OfReal    aNewParams(1, aNodesNb);

  aNewNodes (1) = isvf;
  aNewParams(1) = aEAttr.FirstParam;

  aNewNodes (aNodesNb) = isvl;
  aNewParams(aNodesNb) = aEAttr.LastParam;

  const TopoDS_Face& aFace = myAttribute->Face();
  if (!BRepMesh_ShapeTool::IsDegenerated(theEdge, aFace))
  {
    BRepMesh_EdgeParameterProvider aProvider(theEdge, aFace, aParams);
    for (Standard_Integer i = 2; i < aNodesNb; ++i)
    {
      const Standard_Integer aPointId = aNodes(i);
      const gp_Pnt& aPnt = myBoundaryPoints->Find(aPointId);

      const Standard_Real aParam = aProvider.Parameter(i, aPnt);
      gp_Pnt2d aUV = thePCurve.Curve2d->Value(aParam);

      Standard_Integer iv2, isv;
      myAttribute->AddNode(aPointId, aUV.Coord(), BRepMesh_OnCurve, iv2, isv);

      aNewNodes (i) = isv;
      aNewParams(i) = aParam;
    }
  }

  Handle(Poly_PolygonOnTriangulation) P1 = 
    new Poly_PolygonOnTriangulation(aNewNodes, aNewParams);

  storePolygon(theEdge, P1, theDefEdge);
}

//=======================================================================
//function : update(edge)
//purpose  :
//=======================================================================
void BRepMesh_FastDiscret::update(
  const TopoDS_Edge&                                theEdge,
  const Handle(Geom2d_Curve)&                       theC2d,
  const Standard_Real                               theDefEdge,
  BRepMesh_FastDiscret::EdgeAttributes&             theAttributes)
{
  EdgeAttributes& aEAttr = theAttributes;

  const TopoDS_Face& aFace = myAttribute->Face();
  Handle(BRepMesh_IEdgeTool) aEdgeTool;
  // Try to find existing tessellation.
  for (Standard_Integer i = 1; aEdgeTool.IsNull(); ++i)
  {
    TopLoc_Location aLoc;
    Handle(Poly_Triangulation) aTriangulation;
    Handle(Poly_PolygonOnTriangulation) aPolygon;
    BRep_Tool::PolygonOnTriangulation(theEdge, aPolygon, aTriangulation, aLoc, i);

    if (aPolygon.IsNull())
      break;

    if (aTriangulation.IsNull() || !aPolygon->HasParameters())
      continue;

    if (aPolygon->Deflection() > 1.1 * theDefEdge)
      continue;

    const TColgp_Array1OfPnt&      aNodes   = aTriangulation->Nodes();
    const TColStd_Array1OfInteger& aIndices = aPolygon->Nodes();
    Handle(TColStd_HArray1OfReal)  aParams  = aPolygon->Parameters();

    aEAttr.FirstVExtractor = new PolyVExplorer(aEAttr.FirstVertex, 
      aEAttr.IsSameUV, aEAttr.LastVertex, aIndices(1), aNodes, aLoc);

    aEAttr.LastVExtractor = new PolyVExplorer(aEAttr.LastVertex, 
      aEAttr.IsSameUV, aEAttr.FirstVertex, aIndices(aIndices.Length()), aNodes, aLoc);

    aEdgeTool = new BRepMesh_EdgeTessellationExtractor(theEdge, theC2d, 
      aFace, aTriangulation, aPolygon, aLoc);
  }

  if (aEdgeTool.IsNull())
  {
    aEdgeTool = new BRepMesh_EdgeTessellator(theEdge, myAttribute, 
      mySharedFaces, theDefEdge, myAngle, myMinSize);
  }

  Standard_Integer ipf, ivf, isvf, ipl, ivl, isvl;
  registerEdgeVertices(aEAttr, ipf, ivf, isvf, ipl, ivl, isvl);

  Handle(Poly_PolygonOnTriangulation) P1, P2;
  if (BRepMesh_ShapeTool::IsDegenerated(theEdge, aFace))
  {
    const Standard_Integer  aNodesNb = 2;
    TColStd_Array1OfInteger aNewNodes      (1, aNodesNb);
    TColStd_Array1OfInteger aNewNodInStruct(1, aNodesNb);
    TColStd_Array1OfReal    aNewParams     (1, aNodesNb);

    aNewNodInStruct(1) = ipf;
    aNewNodes      (1) = isvf;
    aNewParams     (1) = aEAttr.FirstParam;

    aNewNodInStruct(aNodesNb) = ipl;
    aNewNodes      (aNodesNb) = isvl;
    aNewParams     (aNodesNb) = aEAttr.LastParam;

    P1 = new Poly_PolygonOnTriangulation(aNewNodes,       aNewParams);
    P2 = new Poly_PolygonOnTriangulation(aNewNodInStruct, aNewParams);
  }
  else
  {
    const Standard_Integer  aNodesNb = aEdgeTool->NbPoints();
    TColStd_Array1OfInteger aNewNodes      (1, aNodesNb);
    TColStd_Array1OfInteger aNewNodInStruct(1, aNodesNb);
    TColStd_Array1OfReal    aNewParams     (1, aNodesNb);

    aNewNodInStruct(1) = ipf;
    aNewNodes      (1) = isvf;
    aNewParams     (1) = aEAttr.FirstParam;

    aNewNodInStruct(aNodesNb) = ipl;
    aNewNodes      (aNodesNb) = isvl;
    aNewParams     (aNodesNb) = aEAttr.LastParam;

    Standard_Integer aLastPointId = myAttribute->LastPointId();
    for (Standard_Integer i = 2; i < aNodesNb; ++i)
    {
      gp_Pnt        aPnt;
      gp_Pnt2d      aUV;
      Standard_Real aParam;
      aEdgeTool->Value(i, aParam, aPnt, aUV);
      myBoundaryPoints->Bind(++aLastPointId, aPnt);

      Standard_Integer iv2, isv;
      myAttribute->AddNode(aLastPointId, aUV.Coord(), BRepMesh_Frontier, iv2, isv);

      aNewNodInStruct(i) = aLastPointId;
      aNewNodes      (i) = isv;
      aNewParams     (i) = aParam;
    }

    P1 = new Poly_PolygonOnTriangulation(aNewNodes,       aNewParams);
    P2 = new Poly_PolygonOnTriangulation(aNewNodInStruct, aNewParams);
  }

  storePolygon(theEdge, P1, theDefEdge);
  storePolygonSharedData(theEdge, P2, theDefEdge);
}

//=======================================================================
//function : storeInternalPolygon
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscret::storePolygon(
  const TopoDS_Edge&                         theEdge,
  Handle(Poly_PolygonOnTriangulation)&       thePolygon,
  const Standard_Real                        theDeflection)
{
  thePolygon->Deflection(theDeflection);
  BRepMesh::HDMapOfShapePairOfPolygon& aInternalEdges = myAttribute->ChangeInternalEdges();
  if (aInternalEdges->IsBound(theEdge))
  {
    BRepMesh_PairOfPolygon& aPair = aInternalEdges->ChangeFind(theEdge);
    if (theEdge.Orientation() == TopAbs_REVERSED)
      aPair.Append(thePolygon);
    else
      aPair.Prepend(thePolygon);

    return;
  }

  BRepMesh_PairOfPolygon aPair;
  aPair.Append(thePolygon);
  aInternalEdges->Bind(theEdge, aPair);
}

//=======================================================================
//function : storePolygonSharedData
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscret::storePolygonSharedData(
  const TopoDS_Edge&                         theEdge,
  Handle(Poly_PolygonOnTriangulation)&       thePolygon,
  const Standard_Real                        theDeflection)
{
  thePolygon->Deflection(theDeflection);
  BRepMesh_PairOfPolygon aPair;
  aPair.Append(thePolygon);
  myEdges.Bind(theEdge, aPair);
}

//=======================================================================
//function : GetFaceAttribute
//purpose  : 
//=======================================================================
Standard_Boolean BRepMesh_FastDiscret::GetFaceAttribute(
  const TopoDS_Face&              theFace,
  Handle(BRepMesh_FaceAttribute)& theAttribute ) const
{
  if (myAttributes.IsBound(theFace))
  {
    theAttribute = myAttributes(theFace);
    return Standard_True;
  }

  return Standard_False;
}

//=======================================================================
//function : RemoveFaceAttribute
//purpose  : 
//=======================================================================
void BRepMesh_FastDiscret::RemoveFaceAttribute(const TopoDS_Face& theFace)
{
  if (myAttributes.IsBound(theFace))
    myAttributes.UnBind(theFace);
}
