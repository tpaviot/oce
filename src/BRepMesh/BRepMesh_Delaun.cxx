// File:        BRepMesh_Delaun.cxx
// Created:     Wed May 12 08:58:20 1993
// Author:      Didier PIFFAULT
//              <dpf@zerox>

#include <BRepMesh_Delaun.ixx>
#include <gp_XY.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Vec2d.hxx>
#include <TColStd_ListIteratorOfListOfInteger.hxx>
#include <TColStd_ListOfInteger.hxx>
#include <Precision.hxx>
#include <Bnd_Box2d.hxx>
#include <gp.hxx>
#include <TColStd_MapOfInteger.hxx>
#include <BRepMesh_MapOfIntegerInteger.hxx>
#include <BRepMesh_HeapSortIndexedVertexOfDelaun.hxx>
#include <BRepMesh_ComparatorOfIndexedVertexOfDelaun.hxx>
#include <BRepMesh_HeapSortIndexedVertexOfDelaun.hxx>
#include <BRepMesh_SelectorOfDataStructureOfDelaun.hxx>
#include <BRepMesh_HeapSortVertexOfDelaun.hxx>
#include <BRepMesh_ComparatorOfVertexOfDelaun.hxx>

typedef TColStd_ListIteratorOfListOfInteger  IteratorOnListOfInteger;
typedef TColStd_ListOfInteger                ListOfInteger;

#define EPSEPS Precision::PConfusion()*Precision::PConfusion()

const gp_XY SortingDirection(M_SQRT1_2, M_SQRT1_2);

//#define TRIANGULATION_MESURE

#ifdef TRIANGULATION_MESURE
#include <OSD_Chronometer.hxx>
#include <NCollection_IncAllocator.hxx>
static OSD_Chronometer ChroTrigu;
static OSD_Chronometer ChroSearch;
static OSD_Chronometer ChroDelete;
static OSD_Chronometer ChroDelTri;
static OSD_Chronometer ChroDelCir;
static OSD_Chronometer ChroCreate;
static OSD_Chronometer ChroFront;
Standard_EXPORT Standard_Boolean Triangulation_Chrono;
#endif

//#define TRIANGULATION_DEBUG

#ifdef TRIANGULATION_DEBUG
Standard_IMPORT Standard_Integer Triangulation_Trace;
#endif


//=======================================================================
//function : BRepMesh_Delaun
//purpose  : 
//=======================================================================
BRepMesh_Delaun::BRepMesh_Delaun
(BRepMesh_Array1OfVertexOfDelaun& Vertices, const Standard_Boolean ZPositive)
:  PositiveOrientation(ZPositive), tCircles(Vertices.Length(),new NCollection_IncAllocator())
{
  if (Vertices.Length()>2) {
    MeshData=new BRepMesh_DataStructureOfDelaun(new NCollection_IncAllocator(),Vertices.Length());
    Init(Vertices);
  }
}

//=======================================================================
//function : BRepMesh_Delaun
//purpose  : 
//=======================================================================
BRepMesh_Delaun::BRepMesh_Delaun 
(const Handle(BRepMesh_DataStructureOfDelaun)& OldMesh, 
 BRepMesh_Array1OfVertexOfDelaun& Vertices,
 const Standard_Boolean ZPositive)
 :  PositiveOrientation(ZPositive), tCircles(Vertices.Length(),OldMesh->Allocator())
{
  MeshData=OldMesh;
  if (Vertices.Length()>2)
    Init(Vertices);
}


//=======================================================================
//function : Init
//purpose  : 
//=======================================================================
void BRepMesh_Delaun::Init(BRepMesh_Array1OfVertexOfDelaun& Vertices)
{
  Bnd_Box2d theBox;
  TColStd_Array1OfInteger vertexIndices(Vertices.Lower(), Vertices.Upper());
  Standard_Integer niver;

  for (niver=Vertices.Lower(); niver<=Vertices.Upper(); niver++) {
    theBox.Add(gp_Pnt2d(Vertices(niver).Coord()));
    vertexIndices(niver)=MeshData->AddNode(Vertices(niver));
  }

  theBox.Enlarge(Precision::PConfusion());
  SuperMesh(theBox);

  BRepMesh_HeapSortIndexedVertexOfDelaun::Sort
    (vertexIndices, 
    BRepMesh_ComparatorOfIndexedVertexOfDelaun(SortingDirection,
    Precision::PConfusion(),
    MeshData));

  Compute(vertexIndices);
}


//=======================================================================
//function : BRepMesh_Delaun
//purpose  : 
//=======================================================================
BRepMesh_Delaun::BRepMesh_Delaun 
(const Handle(BRepMesh_DataStructureOfDelaun)& OldMesh, 
 TColStd_Array1OfInteger& VertexIndices,
 const Standard_Boolean ZPositive)
 :  PositiveOrientation(ZPositive), tCircles(VertexIndices.Length(),OldMesh->Allocator())
{
  MeshData=OldMesh;
  if (VertexIndices.Length()>2) {
    Bnd_Box2d theBox;
    Standard_Integer niver;
    for (niver=VertexIndices.Lower(); niver<=VertexIndices.Upper(); niver++) {
      theBox.Add(gp_Pnt2d(GetVertex(VertexIndices(niver)).Coord()));
    }

    theBox.Enlarge(Precision::PConfusion());
    SuperMesh(theBox);

    BRepMesh_HeapSortIndexedVertexOfDelaun::Sort
      (VertexIndices, 
      BRepMesh_ComparatorOfIndexedVertexOfDelaun(SortingDirection,
      Precision::PConfusion(),
      MeshData));

    Compute(VertexIndices);
  }
}

//=======================================================================
//function : Compute
//purpose  : 
//=======================================================================
void BRepMesh_Delaun::Compute (TColStd_Array1OfInteger& VertexIndices)
{
  // Insertion of edges of super triangles in the list of free edges: 
  BRepMesh_MapOfIntegerInteger loopEdges(10,MeshData->Allocator());
  Standard_Integer e1, e2, e3;
  Standard_Boolean o1, o2, o3;
  supTrian.Edges(e1, e2, e3, o1, o2, o3);
  loopEdges.Bind(e1, Standard_True);
  loopEdges.Bind(e2, Standard_True);
  loopEdges.Bind(e3, Standard_True);

  if (VertexIndices.Length()>0) {

    // Creation of 3 trianglers with the node and the edges of the super triangle:
    Standard_Integer iVert=VertexIndices.Lower();
    CreateTriangles(VertexIndices(iVert), loopEdges);

    // Insertion of nodes :
    Standard_Boolean modif=Standard_True;
    Standard_Integer edgeOn, triPerce;

    Standard_Integer aVertIdx;
    for (iVert++; iVert<=VertexIndices.Upper(); iVert++) {
      aVertIdx = VertexIndices(iVert);
      const BRepMesh_Vertex& refToVert=GetVertex(aVertIdx);
      loopEdges.Clear();

      // List of indices of circles containing the node :
      BRepMesh_ListOfInteger& cirL=tCircles.Select(refToVert.Coord());
      BRepMesh_ListOfInteger::Iterator itT(cirL);

      edgeOn=0;
      triPerce=0;

      for (; itT.More(); itT.Next()) {

        // To add a node in the mesh it is necessary to check to conditions
        // - the node should be located on the border of the mesh and in an existing triangle
        // - all adjacent triangles should belong to a component connected with this triangle 
        if (Contains(itT.Value(), refToVert, edgeOn)) {
          triPerce=itT.Value();
          cirL.Remove(itT);
          break;
        }
      }

      if (triPerce>0) {
        DeleteTriangle(triPerce, loopEdges);

        modif=Standard_True;
        while (modif && !cirL.IsEmpty()) {
          modif=Standard_False;
          BRepMesh_ListOfInteger::Iterator itT1(cirL);
          for (; itT1.More(); itT1.Next()) {
            GetTriangle(itT1.Value()).Edges(e1,e2,e3,o1,o2,o3);
            if (loopEdges.IsBound(e1) || 
              loopEdges.IsBound(e2) || 
              loopEdges.IsBound(e3)) {
                modif=Standard_True;
                DeleteTriangle(itT1.Value(), loopEdges);
                cirL.Remove(itT1);
                break;
            }
          }
        }

#ifdef TRIANGULATION_DEBUG
        if (Triangulation_Trace>0) {
          cout << " creation triangle avec le vertex: ";
          cout << refToVert.Coord().X() << "  " << refToVert.Coord().Y() << endl;
        }
#endif
        // Creation of triangles with the current node 
        // and free edges and removal of these edges from the list of free edges 
        CreateTriangles(aVertIdx, loopEdges);

      }
    }

    // check that internal edges are not crossed by triangles
    BRepMesh_MapOfInteger::Iterator itFr(InternalEdges());

    // destruction of triancles intersecting internal edges 
    // and their replacement by makeshift triangles
    Standard_Integer nbc;

    itFr.Reset();
    for (; itFr.More(); itFr.Next()) {
      nbc = MeshData->ElemConnectedTo(itFr.Key()).Extent();
      if (nbc == 0) {
        MeshLeftPolygonOf(itFr.Key(), Standard_True); 
        MeshLeftPolygonOf(itFr.Key(), Standard_False); 
      }
    }

    // adjustment of meshes to boundary edges
    FrontierAdjust();

  }

  // destruction of triangles containing a top of the super triangle
  BRepMesh_SelectorOfDataStructureOfDelaun select(MeshData);
  select.NeighboursOfNode(supVert1);
  select.NeighboursOfNode(supVert2);
  select.NeighboursOfNode(supVert3);
  BRepMesh_MapOfInteger::Iterator trs(select.Elements());
  loopEdges.Clear();
  for (;trs.More(); trs.Next()) {
    DeleteTriangle(trs.Key(), loopEdges);
  }

  // all edges that remain free are removed from loopEdges;
  // only the boundary edges of the triangulation remain in loopEdges
  BRepMesh_MapOfIntegerInteger::Iterator itLEd(loopEdges);
  for (; itLEd.More(); itLEd.Next()) {
    if (MeshData->ElemConnectedTo(itLEd.Key()).IsEmpty())
      MeshData->RemoveLink(itLEd.Key());
  }

  //the tops of the super triangle are destroyed
  MeshData->RemoveNode(supVert1);
  MeshData->RemoveNode(supVert2);
  MeshData->RemoveNode(supVert3);

}

//=======================================================================
//function : ReCompute
//purpose  : 
//=======================================================================
void BRepMesh_Delaun::ReCompute (TColStd_Array1OfInteger& VertexIndices)
{
  MeshData->ClearDomain();

  // Initialisation du CircleTool :
  tCircles.Initialize(VertexIndices.Length());

  if (VertexIndices.Length()>2)
    Compute(VertexIndices);
}


//=======================================================================
//function : FrontierAdjust
//purpose  : 
//=======================================================================
void BRepMesh_Delaun::FrontierAdjust()
{
  Standard_Integer e1, e2, e3;
  Standard_Boolean o1, o2, o3;
  BRepMesh_MapOfIntegerInteger loopEdges(10,MeshData->Allocator());
  BRepMesh_ListOfInteger::Iterator itconx;
  ListOfInteger tril;

  // find external triangles on boundary edges
  BRepMesh_MapOfInteger::Iterator itFr(Frontier());
  for (; itFr.More(); itFr.Next()) {
    const BRepMesh_PairOfIndex& aPair = MeshData->ElemConnectedTo(itFr.Key());
    for(Standard_Integer j = 1, jn = aPair.Extent(); j <= jn; j++) {
      const BRepMesh_Triangle& trc=GetTriangle(aPair.Index(j));
      trc.Edges(e1,e2,e3,o1,o2,o3);
      if      ((itFr.Key()==e1 && !o1) || 
        (itFr.Key()==e2 && !o2) ||
        (itFr.Key()==e3 && !o3))   {
#ifdef TRIANGULATION_DEBUG
          if (Triangulation_Trace>0) {
            cout << "---> destruction du triangle " << aPair.Index(j) << endl;
          }
#endif
          tril.Append(aPair.Index(j));
      }
    }
  }

  // destruction  of external triangles on boundary edges
  for (; !tril.IsEmpty(); tril.RemoveFirst()) {
    DeleteTriangle(tril.First(), loopEdges);
  }

  // destrucrion of remaining hanging edges :
  BRepMesh_MapOfIntegerInteger::Iterator itFE(loopEdges);

  for (; itFE.More(); itFE.Next()) {
    if (MeshData->ElemConnectedTo(itFE.Key()).IsEmpty())
      MeshData->RemoveLink(itFE.Key());
  }

  // destruction of triangles crossing the boundary edges and 
  // their replacement by makeshift triangles
  itFr.Reset();
  for (; itFr.More(); itFr.Next()) {
    if (MeshData->ElemConnectedTo(itFr.Key()).IsEmpty()) { 
      MeshLeftPolygonOf(itFr.Key(), Standard_True); 
    }
  } 

  // After this processing there sometimes remain triangles outside boundaries.
  // Destruction of these triangles : 
  Standard_Integer nbFront;

  // For each edge with only one connection
  // If one of its tops already passes two boundary edges, 
  // the connected triangle is outside of the contour 
  Standard_Boolean again = Standard_True;

  while (again) {
    tril.Clear();
    loopEdges.Clear();

    for (itFr.Initialize(FreeEdges()); itFr.More(); itFr.Next()) {
      const BRepMesh_Edge& edg=GetEdge(itFr.Key());
      if (edg.Movability()!=BRepMesh_Frontier) {
        nbFront=0;
        if (MeshData->ElemConnectedTo(itFr.Key()).IsEmpty()) 
          loopEdges.Bind(itFr.Key(), Standard_True);
        else {
          for (itconx.Init(MeshData->LinkNeighboursOf(edg.FirstNode()));
            itconx.More(); itconx.Next()) {
              if (GetEdge(itconx.Value()).Movability()==BRepMesh_Frontier) {
                nbFront++;
                if (nbFront>1) break;
              }
          }
          if (nbFront==2) {
            const BRepMesh_PairOfIndex& aPair = MeshData->ElemConnectedTo(itFr.Key());
            for(Standard_Integer j = 1, jn = aPair.Extent(); j <= jn; j++) {
              const Standard_Integer elemId = aPair.Index(j);
              GetTriangle(elemId).Edges(e1, e2, e3, o1, o2, o3);
              if (GetEdge(e1).Movability()==BRepMesh_Free &&
                GetEdge(e2).Movability()==BRepMesh_Free &&
                GetEdge(e3).Movability()==BRepMesh_Free) {
#ifdef TRIANGULATION_DEBUG
                  if (Triangulation_Trace>0) {
                    cout << " ----> destruction du triangle" << elemId <<endl;
                  }
#endif
                  tril.Append(elemId);
              }
            }
          }
        }
      }
    }

    // Destruction des triangles :
    Standard_Integer kk = 0;
    for (; !tril.IsEmpty(); tril.RemoveFirst()) {
      DeleteTriangle(tril.First(), loopEdges);
      kk++;
    }

    // destruction of remaining hanging edges
    for (itFE.Initialize(loopEdges); itFE.More(); itFE.Next()) {
      if (MeshData->ElemConnectedTo(itFE.Key()).IsEmpty())
        MeshData->RemoveLink(itFE.Key());
    }

    if (kk == 0) break;
  }

  // find external triangles on boundary edges
  // because in comlex curved boundaries external triangles can appear
  // after "mesh left polygon"
  for (itFr.Initialize(Frontier()); itFr.More(); itFr.Next()) {
    const BRepMesh_PairOfIndex& aPair = MeshData->ElemConnectedTo(itFr.Key());
    for(Standard_Integer j = 1, jn = aPair.Extent(); j <= jn; j++) {
      const BRepMesh_Triangle& trc=GetTriangle(aPair.Index(j));
      trc.Edges(e1,e2,e3,o1,o2,o3);
      if      ((itFr.Key()==e1 && !o1) || 
        (itFr.Key()==e2 && !o2) ||
        (itFr.Key()==e3 && !o3))   {
#ifdef TRIANGULATION_DEBUG
          if (Triangulation_Trace>0) {
            cout << "---> destruction du triangle " << aPair.Index(j) << endl;
          }
#endif
          tril.Append(aPair.Index(j));
      }
    }
  }

  // destruction  of external triangles on boundary edges
  for (; !tril.IsEmpty(); tril.RemoveFirst()) {
    DeleteTriangle(tril.First(), loopEdges);
  }

  for (itFE.Initialize(loopEdges); itFE.More(); itFE.Next()) {
    if (MeshData->ElemConnectedTo(itFE.Key()).IsEmpty())
      MeshData->RemoveLink(itFE.Key());
  }


  // in some cases there remain unused boundaries check
  for (itFr.Initialize(Frontier()); itFr.More(); itFr.Next()) {
    if (MeshData->ElemConnectedTo(itFr.Key()).IsEmpty()) { 
      MeshLeftPolygonOf(itFr.Key(), Standard_True); 
    }
  }
}


//=======================================================================
//function : MeshLeftPolygonOf
//purpose  : Triangulation of the polygon to the left of <indexEdg>.(material side)
//=======================================================================
void BRepMesh_Delaun::MeshLeftPolygonOf(const Standard_Integer indexEdg,
                                        const Standard_Boolean forwdEdg)
{
  const BRepMesh_Edge& edg=GetEdge(indexEdg);
  TColStd_SequenceOfInteger polyg;
  BRepMesh_MapOfIntegerInteger loopEdges(10,MeshData->Allocator());
  TColStd_MapOfInteger usedEdges;

  // Find the polygon
  usedEdges.Add(indexEdg);
  Standard_Integer debut, prem, pivo;
#ifndef DEB
  Standard_Integer ders =0, oth =0;
#else
  Standard_Integer ders, oth;
#endif
  if (forwdEdg) {
    polyg.Append(indexEdg);
    prem=edg.FirstNode();
    pivo=edg.LastNode();
  }
  else {
    polyg.Append(-indexEdg);
    prem=edg.LastNode();
    pivo=edg.FirstNode();
  }
  debut=prem;
  const BRepMesh_Vertex& debEd=GetVertex(debut);
  const BRepMesh_Vertex& finEd=GetVertex(pivo);

  // Check the presence of the previous edge <indexEdg> :
  BRepMesh_ListOfInteger::Iterator itLiVer(MeshData->LinkNeighboursOf(prem));
  for (; itLiVer.More(); itLiVer.Next()) {
    oth=0;
    if (itLiVer.Value()!=indexEdg) {
      const BRepMesh_Edge& nedg=GetEdge(itLiVer.Value());
      oth=nedg.LastNode();
      if (oth==prem) oth=nedg.FirstNode();
      break;
    }
  }
  if (oth==0) {
#ifdef TRIANGULATION_DEBUG
    if (Triangulation_Trace>0)
      cout << " MeshLeftPolygonOf : Aucun chemin Edge pr�c�dente !" << endl; 
#endif
    return;
  }


  gp_XY vedge(finEd.Coord());
  vedge.Subtract(debEd.Coord());
  gp_XY ved1(vedge);
  gp_XY ved2;
  Standard_Integer curEdg=indexEdg, e1, e2, e3;
  Standard_Boolean o1, o2, o3;

  // Find the nearest to <indexEdg> closed polygon :
  Standard_Boolean InMesh, notInters;
  Standard_Integer nextedge;
  Standard_Real ang, angref;
  gp_XY vpivo, vedcur, voth;

  while (pivo!=debut) {
    nextedge=0;
    if (PositiveOrientation) angref=RealFirst();
    else                     angref=RealLast();
    const BRepMesh_Vertex& vertPivo=GetVertex(pivo);
    vpivo=vertPivo.Coord();
    vpivo.Subtract(debEd.Coord());

    itLiVer.Init(MeshData->LinkNeighboursOf(pivo));

    // Find the next edge with the greatest angle with <indexEdg>
    // and non intersecting <indexEdg> :

    for (; itLiVer.More(); itLiVer.Next()) {
      if (itLiVer.Value()!=curEdg) {
        notInters=Standard_True;
        const BRepMesh_Edge& nedg=GetEdge(itLiVer.Value());

        InMesh=Standard_True;
        if (nedg.Movability()==BRepMesh_Free) {
          if (MeshData->ElemConnectedTo(itLiVer.Value()).IsEmpty()) 
            InMesh=Standard_False;
        }

        if (InMesh) {
          oth=nedg.FirstNode();
          if (oth==pivo) oth=nedg.LastNode();

          vedcur=GetVertex(oth).Coord();
          vedcur.Subtract(vertPivo.Coord());
          if (vedcur.Modulus() >= gp::Resolution() &&
            ved1.Modulus() >= gp::Resolution()) {
              if (prem!=debut && oth!=debut) {
                voth=GetVertex(oth).Coord();
                voth.Subtract(debEd.Coord());
                if ((vedge^vpivo)*(vedge^voth)<0.) {
                  voth=vertPivo.Coord();
                  voth.Subtract(finEd.Coord());
                  if ((vedcur^vpivo)*(vedcur^voth)<0.) 
                    notInters=Standard_False;
                }
              }

              if (notInters) {
                ang=gp_Vec2d(ved1).Angle(gp_Vec2d(vedcur));

                if ((PositiveOrientation && ang>angref) ||
                  (!PositiveOrientation && ang<angref)) {
                    angref=ang;
                    ved2=vedcur;
                    if (nedg.FirstNode()==pivo) nextedge=itLiVer.Value();
                    else                        nextedge=-itLiVer.Value();
                    ders=oth;

                    //epa: Find correct closing not direct to
                    // link but with maximal angle
                    // otherwise, polygon greater that expected is found
                    //if (ders==debut) break;
                }
              }
          }
        }
      }
    }

    if (nextedge!=0) {
      if (Abs(nextedge)!=indexEdg && Abs(nextedge)!=curEdg) {
        curEdg=Abs(nextedge);

        if (!usedEdges.Add(curEdg)) {

          //if this edge has already been added to the polygon, 
          //there is a risk of looping (attention to open contours)
#ifdef TRIANGULATION_DEBUG
          if (Triangulation_Trace>0)
            cout << " MeshLeftPolygonOf : pas de fermeture du polygone !" 
            << endl; 
#endif

          // all edges of the boundary contour are removed from the polygon
          curEdg=Abs(polyg(polyg.Length()));
          while (GetEdge(curEdg).Movability()==BRepMesh_Frontier){
            polyg.Remove(polyg.Length());
            if (polyg.Length()<=0) break;
            curEdg=Abs(polyg(polyg.Length()));
          }
          return;
        }

        polyg.Append(nextedge);

        Standard_Boolean forw=nextedge>0;
        const BRepMesh_PairOfIndex& aPair = MeshData->ElemConnectedTo(curEdg);
        for(Standard_Integer j = 1, jn = aPair.Extent(); j <= jn; j++) {
          const Standard_Integer elemId = aPair.Index(j);
          GetTriangle(elemId).Edges(e1,e2,e3,o1,o2,o3);
          if ((e1==curEdg && o1==forw) || 
            (e2==curEdg && o2==forw) ||
            (e3==curEdg && o3==forw)) {
              DeleteTriangle(elemId, loopEdges);
              break;
          }
        }
      }
    }
    else {
#ifdef TRIANGULATION_DEBUG
      if (Triangulation_Trace>0)
        cout << " MeshLeftPolygonOf : Pas de suivante !" << endl; 
#endif
      return;
    }
    prem=pivo;
    pivo=ders;
    ved1=ved2;
  }


  // Destruction of unused free edges :
  BRepMesh_MapOfIntegerInteger::Iterator itFE(loopEdges);

  for (; itFE.More(); itFE.Next()) {
    if (MeshData->ElemConnectedTo(itFE.Key()).IsEmpty())
      MeshData->RemoveLink(itFE.Key());
  }

  MeshPolygon(polyg);
}


//=======================================================================
//function : MeshPolygon
//purpose  : Triangulatiion of a closed polygon described by the list of indexes of
//           its edges in the structure. (negative index == reversed)
//=======================================================================
void BRepMesh_Delaun::MeshPolygon  (TColStd_SequenceOfInteger& poly)
{
  Standard_Integer vert, vert1, vert2, vert3 =0, tri;

  if (poly.Length()==3) {
    tri=MeshData->AddElement(BRepMesh_Triangle(Abs(poly(1)),Abs(poly(2)),Abs(poly(3)), 
      poly(1)>0,   poly(2)>0,   poly(3)>0,
      BRepMesh_Free));
    tCircles.MocAdd(tri);
    const BRepMesh_Edge& edg1=GetEdge(Abs(poly(1)));
    const BRepMesh_Edge& edg2=GetEdge(Abs(poly(2)));
    if (poly(1)>0) {
      vert1=edg1.FirstNode();
      vert2=edg1.LastNode();
    }
    else {
      vert1=edg1.LastNode();
      vert2=edg1.FirstNode();
    }
    if (poly(2)>0) 
      vert3=edg2.LastNode();
    else
      vert3=edg2.FirstNode();

    if (!tCircles.Add(GetVertex(vert1).Coord(), 
      GetVertex(vert2).Coord(), 
      GetVertex(vert3).Coord(),
      tri)) {
        MeshData->RemoveElement(tri);
    }
  }

  else if (poly.Length()>3) {
    const BRepMesh_Edge& edg=GetEdge(Abs(poly(1)));
    Standard_Real distmin=RealLast();
    Standard_Integer ip, used =0;

    if (poly(1)>0) {
      vert1=edg.FirstNode();
      vert2=edg.LastNode();
    }
    else {
      vert1=edg.LastNode();
      vert2=edg.FirstNode();
    }
    gp_XY vedg(GetVertex(vert2).Coord()-
      GetVertex(vert1).Coord());
    Standard_Real modul=vedg.Modulus();
    if (modul>0.) {
      vedg.SetCoord(vedg.X()/modul, vedg.Y()/modul);

      for (ip=3; ip<=poly.Length(); ip++) {
        const BRepMesh_Edge& nedg=GetEdge(Abs(poly(ip)));
        if (poly(ip)>0) vert=nedg.FirstNode();
        else            vert=nedg.LastNode();
        gp_XY vep(GetVertex(vert).Coord()-GetVertex(vert2).Coord());

        Standard_Real dist=vedg^vep;
        if (Abs(dist)>Precision::PConfusion()) {
          if ((dist>0. && PositiveOrientation) || 
            (dist<0. && !PositiveOrientation)) { 
              if (Abs(dist)<distmin) {
                distmin=dist;
                vert3=vert;
                used=ip;
              }
          }
        }
      }
    }

    Standard_Integer ne2, ne3;
    if (distmin<RealLast()) {
      ne2=MeshData->AddLink(BRepMesh_Edge(vert2, vert3, BRepMesh_Free));
      ne3=MeshData->AddLink(BRepMesh_Edge(vert3, vert1, BRepMesh_Free));
      tri=MeshData->AddElement(BRepMesh_Triangle(Abs(poly(1)), Abs(ne2), Abs(ne3), 
        (poly(1)>0),  (ne2>0),  (ne3>0),
        BRepMesh_Free));

      if (!tCircles.Add(GetVertex(vert1).Coord(), 
        GetVertex(vert2).Coord(), 
        GetVertex(vert3).Coord(),
        tri)) {
          MeshData->RemoveElement(tri);
      }

      if (used<poly.Length()) {
        TColStd_SequenceOfInteger suitePoly;
        poly.Split(used, suitePoly);
        suitePoly.Prepend(-ne3);
        MeshPolygon(suitePoly);
      }
      else 
        poly.Remove(poly.Length());

      if (used>3) {
        poly.SetValue(1, -ne2);
        MeshPolygon(poly);
      }
    }
    else {
#ifdef TRIANGULATION_DEBUG
      if (Triangulation_Trace>0) {
        cout << " MeshPolygon : aucune possibilit� !" << endl;
        if (Triangulation_Trace==5) {
          cout << " MeshPolygon : ";
          for (vert=1; vert<=poly.Length(); vert++) 
            cout << poly(vert) << " ";
          cout<<endl;
        }
      }
#endif
    }
  }
}

//=======================================================================
//function : SuperMesh
//purpose  : 
//=======================================================================
void BRepMesh_Delaun::SuperMesh  (const Bnd_Box2d& theBox)
{
  Standard_Real xMin, yMin, xMax, yMax;
  theBox.Get(xMin, yMin, xMax, yMax);
  Standard_Real deltax=xMax-xMin;
  Standard_Real deltay=yMax-yMin;

  Standard_Real deltaMin=Min(deltax, deltay);
  Standard_Real deltaMax=Max(deltax, deltay);
  Standard_Real delta=deltax+deltay;
  tCircles.SetMinMaxSize(gp_XY(xMin, yMin), gp_XY(xMax, yMax));

  Standard_Integer koeff = 2;
  if(MeshData->NbNodes()>100)
    koeff = 5;
  else if(MeshData->NbNodes()>1000)
    koeff = 7;

  tCircles.SetCellSize(deltax/koeff, deltay/koeff);

  supVert1=MeshData->AddNode(BRepMesh_Vertex((xMin+xMax)/2, yMax+deltaMax, BRepMesh_Free));
  supVert2=MeshData->AddNode(BRepMesh_Vertex(xMin-delta, yMin-deltaMin, BRepMesh_Free));
  supVert3=MeshData->AddNode(BRepMesh_Vertex(xMax+delta, yMin-deltaMin, BRepMesh_Free));

  Standard_Integer niver;
  if (!PositiveOrientation) {
    niver=supVert2;
    supVert2=supVert3;
    supVert3=niver;
  }

  Standard_Integer 
    ed1=MeshData->AddLink(BRepMesh_Edge(supVert1,supVert2,BRepMesh_Free));
  Standard_Integer 
    ed2=MeshData->AddLink(BRepMesh_Edge(supVert2,supVert3,BRepMesh_Free));
  Standard_Integer 
    ed3=MeshData->AddLink(BRepMesh_Edge(supVert3,supVert1,BRepMesh_Free));
  supTrian=BRepMesh_Triangle(Abs(ed1), Abs(ed2), Abs(ed3), 
    (ed1>0), (ed2>0), (ed3>0), BRepMesh_Free);
}


//=======================================================================
//function : CreateTriangles
//purpose  : Creation of triangles from the current node and free edges
//           and deletion of these edges in the list :
//=======================================================================
void BRepMesh_Delaun::CreateTriangles (const Standard_Integer theVertexIndex,  
                                       BRepMesh_MapOfIntegerInteger& theEdges)
{
  BRepMesh_MapOfIntegerInteger::Iterator itFE(theEdges);
  Standard_Real z12, z23, modul;
  Standard_Integer ne1, ne3, nt;
  gp_XY vl1, vl2, vl3;
  ListOfInteger EdgLoop, EdgOK, EdgExter;

  const gp_XY& VertexCoord = MeshData->GetNode(theVertexIndex).Coord();
  for (; itFE.More(); itFE.Next()) {
    const BRepMesh_Edge& edg=GetEdge(itFE.Key());
    Standard_Integer deb=edg.FirstNode();
    Standard_Integer fin=edg.LastNode();
    Standard_Boolean sens=(Standard_Boolean)theEdges(itFE.Key());
    if (!sens) {
      nt=deb;
      deb=fin;
      fin=nt;
    }

    const BRepMesh_Vertex& debVert=GetVertex(deb);
    const BRepMesh_Vertex& finVert=GetVertex(fin);

    vl1=debVert.Coord();
    vl1.Subtract(VertexCoord);
    vl2=finVert.Coord();
    vl2.Subtract(debVert.Coord());
    //    vl3=theVertex.Coord();
    vl3=VertexCoord;
    vl3.Subtract(finVert.Coord());

    z12=z23=0.;
    modul=vl2.Modulus();
    if (modul>Precision::PConfusion()) {
      vl2.SetCoord(vl2.X()/modul, vl2.Y()/modul);
      z12=vl1^vl2;
      z23=vl2^vl3;
    }

    if (Abs(z12)>=Precision::PConfusion() && 
      Abs(z23)>=Precision::PConfusion()) {
        Standard_Boolean sensOK;
        if (PositiveOrientation) sensOK=(z12>0. && z23>0.);
        else                     sensOK=(z12<0. && z23<0.);
        if (sensOK) {
          ne1=MeshData->AddLink(BRepMesh_Edge(theVertexIndex, deb, BRepMesh_Free));
          ne3=MeshData->AddLink(BRepMesh_Edge(fin, theVertexIndex, BRepMesh_Free));
          nt=MeshData->AddElement(BRepMesh_Triangle(Abs(ne1), itFE.Key(), Abs(ne3), 
            (ne1>0), sens, (ne3>0),
            BRepMesh_Free));

          if (!tCircles.Add(VertexCoord, 
            debVert.Coord(), 
            finVert.Coord(), nt))
            MeshData->RemoveElement(nt);
        }
        else {

          if (sens) EdgLoop.Append(itFE.Key());
          else      EdgLoop.Append(-itFE.Key());
          if (vl1.SquareModulus()>vl3.SquareModulus()) {
            ne1=MeshData->AddLink(BRepMesh_Edge(theVertexIndex, deb, BRepMesh_Free));
            EdgExter.Append(Abs(ne1));
          }
          else{
            ne3=MeshData->AddLink(BRepMesh_Edge(fin, theVertexIndex, BRepMesh_Free));
            EdgExter.Append(Abs(ne3));
          }
        }
    }
#ifdef TRIANGULATION_DEBUG
    else {
      if (Triangulation_Trace>0)
        cout << " CreateTriangles : produit vectoriel trop petit !" << endl;
    }
#endif
  }
  theEdges.Clear();
  while (!EdgExter.IsEmpty()) {
    const BRepMesh_PairOfIndex& conx = MeshData->ElemConnectedTo(Abs(EdgExter.First()));
    if (!conx.IsEmpty())
      DeleteTriangle(conx.FirstIndex(), theEdges);
    EdgExter.RemoveFirst();
  }

  for (itFE.Initialize(theEdges); itFE.More(); itFE.Next()) {
    if (MeshData->ElemConnectedTo(itFE.Key()).IsEmpty())
      MeshData->RemoveLink(itFE.Key());
  }

  while (!EdgLoop.IsEmpty()) {
    if (GetEdge(Abs(EdgLoop.First())).Movability()!=BRepMesh_Deleted) {
      MeshLeftPolygonOf(Abs(EdgLoop.First()), (EdgLoop.First()>0));
    }
    EdgLoop.RemoveFirst();
  }
}

//=======================================================================
//function : DeleteTriangle
//purpose : The concerned triangles are deleted and the freed edges are added in 
//           <loopEdges>.  If an edge is added twice, it does not exist and
//          it is necessary to destroy it.  This corresponds to the destruction of two
//          connected triangles.
//=======================================================================

void  BRepMesh_Delaun::DeleteTriangle (const Standard_Integer tIndex, 
                                       BRepMesh_MapOfIntegerInteger& fEdges)
{
  tCircles.Delete(tIndex);

  Standard_Integer fe1, fe2, fe3;
  Standard_Boolean or1, or2, or3;
  GetTriangle(tIndex).Edges(fe1, fe2, fe3, or1, or2, or3);
  MeshData->RemoveElement(tIndex);

  if (!fEdges.Bind(fe1, or1)) {
    fEdges.UnBind(fe1);
    MeshData->RemoveLink(fe1);
  }
  if (!fEdges.Bind(fe2, or2))  {
    fEdges.UnBind(fe2);
    MeshData->RemoveLink(fe2);
  }
  if (!fEdges.Bind(fe3, or3))  {
    fEdges.UnBind(fe3);
    MeshData->RemoveLink(fe3);
  }

}


//=======================================================================
//function : AddVertex
//purpose  : 
//=======================================================================
void  BRepMesh_Delaun::AddVertex(const BRepMesh_Vertex& theVert)
{
  Standard_Integer nv = MeshData->AddNode(theVert);

  // Iterator in the list of indexes of circles containing the node :
  BRepMesh_ListOfInteger& cirL=tCircles.Select(theVert.Coord());

  Standard_Integer edgon=0;
  Standard_Integer triPer=0;
  Standard_Integer e1, e2, e3;
  Standard_Boolean o1, o2, o3;

  BRepMesh_ListOfInteger::Iterator itT(cirL);
  for (; itT.More(); itT.Next()) {

    // To add a node in the mesh it is necessary to check conditions: 
    // - the node should be within the boundaries of the mesh and so in an existing triangle
    // - all adjacent triangles should belong to a component connected with this triangle
    if (Contains(itT.Value(), theVert, edgon)) {
      if (edgon==0) {
        triPer=itT.Value();
        cirL.Remove(itT);
        break;
      }
      else if (GetEdge(edgon).Movability()==BRepMesh_Free) {
        triPer=itT.Value();
        cirL.Remove(itT);
        break;
      }
    }
  }

  if (triPer>0) {

    BRepMesh_MapOfIntegerInteger loopEdges(10,MeshData->Allocator());
    DeleteTriangle(triPer, loopEdges);

    Standard_Boolean modif=Standard_True;
    while (modif && !cirL.IsEmpty()) {
      modif=Standard_False;
      BRepMesh_ListOfInteger::Iterator itT1(cirL);
      for (; itT1.More(); itT1.Next()) {
        GetTriangle(itT.Value()).Edges(e1,e2,e3,o1,o2,o3);
        if (loopEdges.IsBound(e1) || 
          loopEdges.IsBound(e2) || 
          loopEdges.IsBound(e3)) {
            modif=Standard_True;
            DeleteTriangle(itT1.Value(), loopEdges);
            cirL.Remove(itT1);
            break;
        }
      }
    }

    // Creation of triangles with the current node and free edges
    // and removal of these edges from the list of free edges
    CreateTriangles(nv, loopEdges);

    // Check that internal edges are not crossed by the triangles
    BRepMesh_MapOfInteger::Iterator itFr(InternalEdges());

    // Destruction of triangles crossing internal edges and 
    // their replacement by makeshift triangles
    Standard_Integer nbc;
    itFr.Reset();
    for (; itFr.More(); itFr.Next()) {
      nbc = MeshData->ElemConnectedTo(itFr.Key()).Extent();
      if (nbc == 0) {
        MeshLeftPolygonOf(itFr.Key(), Standard_True); 
        MeshLeftPolygonOf(itFr.Key(), Standard_False); 
      }
    }

    FrontierAdjust();

  }

}

//=======================================================================
//function : RemoveVertex
//purpose  : 
//=======================================================================
void  BRepMesh_Delaun::RemoveVertex(const BRepMesh_Vertex& theVert)
{
  BRepMesh_SelectorOfDataStructureOfDelaun select(MeshData);
  select.NeighboursOf(theVert);

  BRepMesh_MapOfIntegerInteger loopEdges(10,MeshData->Allocator());

  // Loop on triangles to be destroyed :
  BRepMesh_MapOfInteger::Iterator trs(select.Elements());
  for (;trs.More(); trs.Next()) {
    DeleteTriangle(trs.Key(), loopEdges);
  }

  TColStd_SequenceOfInteger polyg;
  Standard_Integer iv;
  Standard_Integer nbLi=loopEdges.Extent();
  BRepMesh_MapOfIntegerInteger::Iterator itFE(loopEdges);

  if (itFE.More()) {
    const BRepMesh_Edge& edg=GetEdge(itFE.Key());
    Standard_Integer deb=edg.FirstNode();
    Standard_Integer fin;
    Standard_Integer pivo=edg.LastNode();
    Standard_Integer iseg=itFE.Key();
    Standard_Boolean sens=(Standard_Boolean)loopEdges(iseg);
    if (!sens) {
      iv=deb;
      deb=pivo;
      pivo=iv;
      polyg.Append(-iseg);
    }
    else {
      polyg.Append(iseg);
    }
    loopEdges.UnBind(iseg);
    fin=deb;
    BRepMesh_ListOfInteger::Iterator itLiV;
    Standard_Integer vcur;
    while (pivo!=fin) {
      itLiV.Init(MeshData->LinkNeighboursOf(pivo));
      for (; itLiV.More(); itLiV.Next()) {
        if (itLiV.Value()!=iseg && loopEdges.IsBound(itLiV.Value())) {
          iseg=itLiV.Value();
          const BRepMesh_Edge& edg1=GetEdge(iseg);
          vcur=edg1.LastNode();
          if (vcur!=pivo) {
            vcur=edg1.FirstNode();
            polyg.Append(-iseg);
          }
          else
            polyg.Append(iseg);
          pivo=vcur;
          loopEdges.UnBind(iseg);
          break;
        }
      }
      if (nbLi<=0) break;
      nbLi--;
    }
    MeshPolygon(polyg);
  }
}


//=======================================================================
//function : AddVertices
//purpose  : 
//=======================================================================
void  BRepMesh_Delaun::AddVertices(BRepMesh_Array1OfVertexOfDelaun& vertices)
{
  BRepMesh_HeapSortVertexOfDelaun::Sort
    (vertices, 
    BRepMesh_ComparatorOfVertexOfDelaun(SortingDirection, Precision::PConfusion()));

  BRepMesh_MapOfIntegerInteger loopEdges(10,MeshData->Allocator());
  Standard_Boolean modif=Standard_True;
  Standard_Integer edgon, triPer;
  Standard_Integer e1, e2, e3;
  Standard_Boolean o1, o2, o3;

  Standard_Integer niver;
  Standard_Integer aIdxVert;
  for (niver=vertices.Lower(); niver<=vertices.Upper(); niver++) {
    aIdxVert = MeshData->AddNode(vertices(niver));

    // Iterator in the list of indexes of circles containing the node
    BRepMesh_ListOfInteger& cirL=tCircles.Select(vertices(niver).Coord());

    edgon=0;
    triPer=0;

    BRepMesh_ListOfInteger::Iterator itT(cirL);
    for (; itT.More(); itT.Next()) {

      // To add a node in the mesh it is necessary to check conditions: 
      // - the node should be within the boundaries of the mesh and so in an existing triangle
      // - all adjacent triangles should belong to a component connected with this triangle
      if (Contains(itT.Value(), vertices(niver), edgon)) {
        if (edgon==0) {
          triPer=itT.Value();
          cirL.Remove(itT);
          break;
        }
        else if (GetEdge(edgon).Movability()==BRepMesh_Free) {
          triPer=itT.Value();
          cirL.Remove(itT);
          break;
        }
      }
    }

    if (triPer>0) {
      DeleteTriangle(triPer, loopEdges);

      modif=Standard_True;
      while (modif && !cirL.IsEmpty()) {
        modif=Standard_False;
        BRepMesh_ListOfInteger::Iterator itT1(cirL);
        for (; itT1.More(); itT1.Next()) {
          GetTriangle(itT1.Value()).Edges(e1,e2,e3,o1,o2,o3);
          if (loopEdges.IsBound(e1) || 
            loopEdges.IsBound(e2) || 
            loopEdges.IsBound(e3)) {
              modif=Standard_True;
              DeleteTriangle(itT1.Value(), loopEdges);
              cirL.Remove(itT1);
              break;
          }
        }
      }

      // Creation of triangles with the current node and free edges
      // and removal of these edges from the list of free edges
      CreateTriangles(aIdxVert, loopEdges);
    }
  }

  // Check that internal edges are not crossed by triangles
  BRepMesh_MapOfInteger::Iterator itFr(InternalEdges());

  // Destruction of triangles crossing internal edges 
  //and their replacement by makeshift triangles
  Standard_Integer nbc;
  itFr.Reset();
  for (; itFr.More(); itFr.Next()) {
    nbc = MeshData->ElemConnectedTo(itFr.Key()).Extent();
    if (nbc == 0) {
      MeshLeftPolygonOf(itFr.Key(), Standard_True); 
      MeshLeftPolygonOf(itFr.Key(), Standard_False); 
    }
  }

  // Adjustment of meshes to boundary edges
  FrontierAdjust();
}


//=======================================================================
//function : RevertDiagonal
//purpose  : 
//=======================================================================
Standard_Boolean BRepMesh_Delaun::RevertDiagonal(const Standard_Integer ind)
{
  const BRepMesh_PairOfIndex& elConx = MeshData->ElemConnectedTo(ind);
  const BRepMesh_Edge& lEdge = GetEdge(ind);
  if (elConx.Extent()==2 && lEdge.Movability()==BRepMesh_Free) {
    Standard_Integer t1(elConx.FirstIndex());
    Standard_Integer t2(elConx.LastIndex());

    Standard_Integer e1t1, e2t1, e3t1, e1t2, e2t2, e3t2 ;
    Standard_Boolean o1t1, o2t1, o3t1, o1t2, o2t2, o3t2;
#ifndef DEB
    Standard_Integer ed13=0, ed23=0, ed14=0, ed24=0, v1, v2, v3=0, v4=0, vc1;
    Standard_Boolean oindt1=Standard_False, or13=Standard_False, 
      or23=Standard_False, or14=Standard_False, or24=Standard_False, orien;
#else
    Standard_Integer ed13, ed23, ed14, ed24, v1, v2, v3, v4, vc1;
    Standard_Boolean oindt1, or13, or23, or14, or24, orien;
#endif
    GetTriangle(t1).Edges(e1t1, e2t1, e3t1, o1t1, o2t1, o3t1);
    GetTriangle(t2).Edges(e1t2, e2t2, e3t2, o1t2, o2t2, o3t2);

    v1=lEdge.FirstNode(); v2=lEdge.LastNode();
    if      (e1t1==ind) {
      if (o2t1) v3 =GetEdge(e2t1).LastNode();
      else      v3 =GetEdge(e2t1).FirstNode();
      ed13=e3t1; ed23=e2t1;
      or13=o3t1; or23=o2t1;
      oindt1=o1t1;
    }
    else if (e2t1==ind) {
      if (o3t1) v3 =GetEdge(e3t1).LastNode();
      else      v3 =GetEdge(e3t1).FirstNode();
      ed13=e1t1; ed23=e3t1;
      or13=o1t1; or23=o3t1;
      oindt1=o2t1;
    }
    else if (e3t1==ind) {
      if (o1t1) v3 =GetEdge(e1t1).LastNode();
      else      v3 =GetEdge(e1t1).FirstNode();
      ed13=e2t1; ed23=e1t1;
      or13=o2t1; or23=o1t1;
      oindt1=o3t1;
    }
    if      (e1t2==ind) {
      if (o2t2) v4 =GetEdge(e2t2).LastNode();
      else      v4 =GetEdge(e2t2).FirstNode();
      ed14=e2t2; ed24=e3t2;
      or14=o2t2; or24=o3t2;
    }
    else if (e2t2==ind) {
      if (o3t2) v4 =GetEdge(e3t2).LastNode();
      else      v4 =GetEdge(e3t2).FirstNode();
      ed14=e3t2; ed24=e1t2;
      or14=o3t2; or24=o1t2;
    }
    else if (e3t2==ind) {
      if (o1t2) v4 =GetEdge(e1t2).LastNode();
      else      v4 =GetEdge(e1t2).FirstNode();
      ed14=e1t2; ed24=e2t2;
      or14=o1t2; or24=o2t2;
    }
    if (!oindt1) {
      vc1=v3; v3=v4; v4=vc1;
      vc1=ed13; ed13=ed24; ed24=vc1;
      orien =or13; or13=or24; or24=orien ;
      vc1=ed14; ed14=ed23; ed23=vc1;
      orien =or14; or14=or23; or23=orien ;
    }
    const BRepMesh_Vertex& vert1 = GetVertex(v1);
    const BRepMesh_Vertex& vert2 = GetVertex(v2);
    const BRepMesh_Vertex& vert3 = GetVertex(v3);
    const BRepMesh_Vertex& vert4 = GetVertex(v4);

    gp_XY ved13(vert1.Coord()); ved13.Subtract(vert3.Coord());
    gp_XY ved14(vert4.Coord()); ved14.Subtract(vert1.Coord());
    gp_XY ved23(vert3.Coord()); ved23.Subtract(vert2.Coord());
    gp_XY ved24(vert2.Coord()); ved24.Subtract(vert4.Coord());

    Standard_Real z13, z24, modul;
    z13=z24=0.;
    modul=ved13.Modulus();
    if (modul>Precision::PConfusion()) {
      ved13.SetCoord(ved13.X()/modul, ved13.Y()/modul);
      z13=ved13^ved14;
    }
    modul=ved24.Modulus();
    if (modul>Precision::PConfusion()) {
      ved24.SetCoord(ved24.X()/modul, ved24.Y()/modul);
      z24=ved24^ved23;
    }

    if (Abs(z13)>=Precision::PConfusion()&&Abs(z24)>=Precision::PConfusion()) {
      if ((z13>0. && z24>0.) || (z13<0. && z24<0.)) {
        tCircles.Delete(t1);
        tCircles.Delete(t2);
        if (!tCircles.Add(vert4.Coord(), vert2.Coord(), vert3.Coord(), t1) &&
          !tCircles.Add(vert3.Coord(), vert1.Coord(), vert4.Coord(), t2)) {
            Standard_Integer newd=ind;
            BRepMesh_Edge newEdg=BRepMesh_Edge(v3, v4, BRepMesh_Free);
            if (!MeshData->SubstituteLink(newd, newEdg)) {
              newd=MeshData->IndexOf(newEdg);
              MeshData->RemoveLink(ind);
            }
            MeshData->SubstituteElement(t1, BRepMesh_Triangle(ed24, ed23, newd,
              or24, or23, Standard_True,
              BRepMesh_Free));
            MeshData->SubstituteElement(t2, BRepMesh_Triangle(ed13, ed14, newd,
              or13, or14, Standard_False,
              BRepMesh_Free));
            return Standard_True;
        }
        else {
          if (oindt1) {
            tCircles.Add(vert1.Coord(), vert2.Coord(), vert3.Coord(), t1);
            tCircles.Add(vert2.Coord(), vert1.Coord(), vert4.Coord(), t2);
          }
          else {
            tCircles.Add(vert1.Coord(), vert2.Coord(), vert3.Coord(), t2);
            tCircles.Add(vert2.Coord(), vert1.Coord(), vert4.Coord(), t1);
          }
        }
      }
    }
  }
  return Standard_False;
}

//=======================================================================
//function : UseEdge
//purpose  : 
//=======================================================================
Standard_Boolean BRepMesh_Delaun::UseEdge(const Standard_Integer ind)
{
  const BRepMesh_PairOfIndex& elConx=MeshData->ElemConnectedTo(ind);
  if (elConx.Extent()==0) {
    const BRepMesh_Edge& lEdge = GetEdge(ind);
    Standard_Integer vdeb, pivo, othV, leftEdge, rightEdge;
    vdeb=lEdge.FirstNode();
    pivo=lEdge.LastNode();
    const BRepMesh_ListOfInteger& neigVDeb = MeshData->LinkNeighboursOf(vdeb);
    const BRepMesh_ListOfInteger& neigPivo = MeshData->LinkNeighboursOf(pivo);
    if (neigVDeb.Extent()>0 && neigPivo.Extent()>0) {
      const BRepMesh_Vertex& vertDeb=GetVertex(vdeb);
      const BRepMesh_Vertex& vertPivo=GetVertex(pivo);

      gp_XY vedcur;
      gp_XY vedge(vertPivo.Coord());
      vedge.Subtract(vertDeb.Coord());

      BRepMesh_ListOfInteger::Iterator itNeig(neigPivo);
#ifndef DEB
      Standard_Real ang =0.;
#else
      Standard_Real ang;
#endif
      Standard_Real angMin=RealLast();
      Standard_Real angMax=RealFirst();
      Standard_Boolean InMesh;
      leftEdge=rightEdge=0;

      for (; itNeig.More(); itNeig.Next()) {
        if (itNeig.Value()!=ind) {
          const BRepMesh_Edge& nedg=GetEdge(itNeig.Value());

          InMesh=Standard_True;
          if (nedg.Movability()==BRepMesh_Free) {
            if (MeshData->ElemConnectedTo(itNeig.Value()).IsEmpty()) 
              InMesh=Standard_False;
          }

          if (InMesh) {
            othV=nedg.FirstNode();
            if (othV==pivo) othV=nedg.LastNode();

            vedcur=GetVertex(othV).Coord();
            vedcur.Subtract(vertPivo.Coord());

            ang=gp_Vec2d(vedge).Angle(gp_Vec2d(vedcur));
          }
          if (ang>angMax) {
            angMax=ang;
            leftEdge=itNeig.Value();
          }
          if (ang<angMin) {
            angMin=ang;
            rightEdge=itNeig.Value();
          }
        }
      }
      if (leftEdge>0) {
        if (leftEdge==rightEdge) {
        }
        else {
        }
      }
    }
  }
  return Standard_False;
}

//=======================================================================
//function : SmoothMesh
//purpose  : 
//=======================================================================
void BRepMesh_Delaun::SmoothMesh(const Standard_Real Epsilon)
{
  Standard_Integer baryVert, polyVert, nbPolyVert;
  Standard_Real uSom, vSom, newU, newV;
  Standard_Integer nbVert=MeshData->NbNodes();
  BRepMesh_ListOfInteger::Iterator itNeig;

  uSom=vSom=0;
  for (baryVert=1; baryVert<=nbVert; baryVert++) {
    const BRepMesh_Vertex& curVert=GetVertex(baryVert);
    if (curVert.Movability()==BRepMesh_Free) {
      const BRepMesh_ListOfInteger& neighEdg=MeshData->LinkNeighboursOf(baryVert);
      if (neighEdg.Extent()>2) {
        nbPolyVert=0;
        for (itNeig.Init(neighEdg); itNeig.More(); itNeig.Next()) {
          const BRepMesh_Edge& nedg=GetEdge(itNeig.Value());
          polyVert=nedg.FirstNode();
          if (polyVert==baryVert) polyVert=nedg.LastNode();
          nbPolyVert++;
          const gp_XY& pVal = GetVertex(polyVert).Coord();
          uSom+=pVal.X();
          vSom+=pVal.Y();
        }
        if (nbPolyVert>2) {
          newU=uSom/(Standard_Real)nbPolyVert;
          newV=vSom/(Standard_Real)nbPolyVert;
          if (!curVert.Coord().IsEqual(gp_XY(newU, newV), Epsilon)) {
            BRepMesh_Vertex newVert(newU, newV, curVert.Movability());
            MeshData->MoveNode(baryVert, newVert);
          }
        }
      }
    }
  }
}

//=======================================================================
//function : Result
//purpose  : 
//=======================================================================
const Handle(BRepMesh_DataStructureOfDelaun)& BRepMesh_Delaun::Result()const
{
  return MeshData;
}

//=======================================================================
//function : Frontier
//purpose  : 
//=======================================================================
const BRepMesh_MapOfInteger& BRepMesh_Delaun::Frontier ()
{
  BRepMesh_MapOfInteger::Iterator triDom(MeshData->LinkOfDomain());

  mapEdges.Clear();
  for (; triDom.More(); triDom.Next()) {
    if (GetEdge(triDom.Key()).Movability()==BRepMesh_Frontier) {
      mapEdges.Add(triDom.Key());
    }
  }
  return mapEdges;
}

//=======================================================================
//function : InternalEdges
//purpose  : 
//=======================================================================
const BRepMesh_MapOfInteger& BRepMesh_Delaun::InternalEdges ()
{
  BRepMesh_MapOfInteger::Iterator triDom(MeshData->LinkOfDomain());

  mapEdges.Clear();
  for (; triDom.More(); triDom.Next()) {
    if (GetEdge(triDom.Key()).Movability()==BRepMesh_Fixed) {
      mapEdges.Add(triDom.Key());
    }
  }
  return mapEdges;
}

//=======================================================================
//function : FreeEdges
//purpose  : 
//=======================================================================
const BRepMesh_MapOfInteger& BRepMesh_Delaun::FreeEdges ()
{
  BRepMesh_MapOfInteger::Iterator triDom(MeshData->LinkOfDomain());

  mapEdges.Clear();
  for (; triDom.More(); triDom.Next()) {
    if (MeshData->ElemConnectedTo(triDom.Key()).Extent()<=1) {
      mapEdges.Add(triDom.Key());
    }
  }
  return mapEdges;
}


//=======================================================================
//function : Contains
//purpose  : 
//=======================================================================
Standard_Boolean BRepMesh_Delaun::Contains(const Standard_Integer tri,
                                           const BRepMesh_Vertex& vert,
                                           Standard_Integer& edgOn)const
{
  edgOn=0;
  Standard_Integer e1, e2, e3, p1, p2, p3;
  Standard_Boolean o1, o2, o3;
  GetTriangle(tri).Edges(e1, e2, e3, o1, o2, o3);
  const BRepMesh_Edge& edg1=GetEdge(e1);
  const BRepMesh_Edge& edg2=GetEdge(e2);
  const BRepMesh_Edge& edg3=GetEdge(e3);
  if (o1) {
    p1=edg1.FirstNode();
    p2=edg1.LastNode();
  }
  else {
    p2=edg1.FirstNode();
    p1=edg1.LastNode();
  }
  if (o3) p3=edg3.FirstNode();
  else    p3=edg3.LastNode();

  const gp_XY& P1=GetVertex(p1).Coord();
  const gp_XY& P2=GetVertex(p2).Coord();
  const gp_XY& P3=GetVertex(p3).Coord();
  gp_XY E1(P2); E1.Subtract(P1);
  gp_XY E2(P3); E2.Subtract(P2);
  gp_XY E3(P1); E3.Subtract(P3);

  Standard_Real mode1=E1.SquareModulus();
  //Standard_Real dist=Sqrt(mode1);
  if (mode1<=EPSEPS) return Standard_False;
  Standard_Real v1=E1^(vert.Coord()-P1);
  Standard_Real distMin=(v1*v1)/mode1;
  edgOn=e1;

  Standard_Real mode2=E2.SquareModulus();
  Standard_Real dist;
  //dist=Sqrt(mode2);
  if (mode2<=EPSEPS) return Standard_False;
  Standard_Real v2=E2^(vert.Coord()-P2);
  dist=(v2*v2)/mode2;
  if (dist<distMin) {
    edgOn=e2;
    distMin=dist;
  }

  Standard_Real mode3=E3.SquareModulus();
  //dist=Sqrt(mode3);
  if (mode3<=EPSEPS) return Standard_False;
  Standard_Real v3=E3^(vert.Coord()-P3);
  dist=(v3*v3)/mode3;
  if (dist<distMin) {
    edgOn=e3;
    distMin=dist;
  }

  if (distMin>EPSEPS) {
    Standard_Integer edf=edgOn;
    edgOn=0;
    if      (edf==e1 && edg1.Movability()!=BRepMesh_Free) {
      if (v1<(mode1/5.)) edgOn=e1;
    }
    else if (edf==e2 && edg2.Movability()!=BRepMesh_Free) {
      if (v2<(mode2/5.)) edgOn=e2;
    }
    else if (edf==e3 && edg3.Movability()!=BRepMesh_Free) {
      if (v3<(mode3/5.)) edgOn=e3;
    }
  }

  return (v1+v2+v3!=0. &&((v1>=0. && v2>=0. && v3>=0.) ||
    (v1<=0. && v2<=0. && v3<=0.)));
}

//=======================================================================
//function : TriangleContaining
//purpose  : 
//=======================================================================
Standard_Integer BRepMesh_Delaun::TriangleContaining(const BRepMesh_Vertex& vert)
{
  const BRepMesh_ListOfInteger& cirL=tCircles.Select(vert.Coord());

  BRepMesh_ListOfInteger::Iterator itT(cirL);
  Standard_Integer triPer=0;
  Standard_Integer edgon=0;
  for (; itT.More(); itT.Next()) {
    if (Contains(itT.Value(), vert, edgon)) {
      if (edgon==0) {
        triPer=itT.Value();
        break;
      }
      else if (GetEdge(edgon).Movability()==BRepMesh_Free) {
        triPer=itT.Value();
        break;
      }
    }
  }
  return triPer;
}
