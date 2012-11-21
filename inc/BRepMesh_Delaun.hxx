// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _BRepMesh_Delaun_HeaderFile
#define _BRepMesh_Delaun_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Handle_BRepMesh_DataStructureOfDelaun_HeaderFile
#include <Handle_BRepMesh_DataStructureOfDelaun.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _BRepMesh_CircleTool_HeaderFile
#include <BRepMesh_CircleTool.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _BRepMesh_Triangle_HeaderFile
#include <BRepMesh_Triangle.hxx>
#endif
#ifndef _BRepMesh_MapOfInteger_HeaderFile
#include <BRepMesh_MapOfInteger.hxx>
#endif
#ifndef _BRepMesh_MapOfIntegerInteger_HeaderFile
#include <BRepMesh_MapOfIntegerInteger.hxx>
#endif
class BRepMesh_DataStructureOfDelaun;
class BRepMesh_Array1OfVertexOfDelaun;
class TColStd_Array1OfInteger;
class BRepMesh_Vertex;
class BRepMesh_Edge;
class BRepMesh_Triangle;
class Bnd_Box2d;
class TColStd_SequenceOfInteger;
class TColStd_MapOfInteger;


//! Compute the  Delaunay's triangulation    with  the <br>
//!          algorithm of Watson. <br>
class BRepMesh_Delaun  {
public:

  DEFINE_STANDARD_ALLOC

  //! Creates the  triangulation with an  empty Mesh <br>
//!          data structure. <br>
  Standard_EXPORT   BRepMesh_Delaun(BRepMesh_Array1OfVertexOfDelaun& Vertices,const Standard_Boolean ZPositive = Standard_True);
  //! Creates  the triangulation with   and existant <br>
//!          Mesh data structure. <br>
  Standard_EXPORT   BRepMesh_Delaun(const Handle(BRepMesh_DataStructureOfDelaun)& OldMesh,BRepMesh_Array1OfVertexOfDelaun& Vertices,const Standard_Boolean ZPositive = Standard_True);
  //! Creates  the triangulation with   and existant <br>
//!          Mesh data structure. <br>
  Standard_EXPORT   BRepMesh_Delaun(const Handle(BRepMesh_DataStructureOfDelaun)& OldMesh,TColStd_Array1OfInteger& VertexIndices,const Standard_Boolean ZPositive = Standard_True);
  //! Removes a vertex in the triangulation. <br>
  Standard_EXPORT     void RemoveVertex(const BRepMesh_Vertex& theVertex) ;
  //! Adds some vertices in the triangulation. <br>
  Standard_EXPORT     void AddVertices(BRepMesh_Array1OfVertexOfDelaun& Vertices) ;
  //! Modify mesh to use the edge. Return True if done. <br>
  Standard_EXPORT     Standard_Boolean UseEdge(const Standard_Integer theEdge) ;
  //! Gives the Mesh data structure. <br>
  Standard_EXPORT    const Handle_BRepMesh_DataStructureOfDelaun& Result() const;
  //! Gives the list of frontier edges <br>
  Standard_EXPORT    const BRepMesh_MapOfInteger& Frontier() ;
  //! Gives the list of internal edges <br>
  Standard_EXPORT    const BRepMesh_MapOfInteger& InternalEdges() ;
  //! Gives the list of free edges used only one time <br>
  Standard_EXPORT    const BRepMesh_MapOfInteger& FreeEdges() ;
  
       const BRepMesh_Vertex& GetVertex(const Standard_Integer vIndex) const;
  
       const BRepMesh_Edge& GetEdge(const Standard_Integer eIndex) const;
  
       const BRepMesh_Triangle& GetTriangle(const Standard_Integer tIndex) const;
  //! Initializes the triangulation with an Array of <br>
//!          Vertex. <br>
  Standard_EXPORT     void Init(BRepMesh_Array1OfVertexOfDelaun& Vertices) ;
  //! Computes the triangulation and add the vertices <br>
//!          edges and triangles to the Mesh data structure. <br>
  Standard_EXPORT     void Compute(TColStd_Array1OfInteger& VertexIndices) ;
  //! Build the super mesh . <br>
  Standard_EXPORT     void SuperMesh(const Bnd_Box2d& theBox) ;
  //! Test  if   triangle   of  index   <TrianIndex> <br>
//!          contains geometricaly <theVertex>. If <EdgeOn> <br>
//!          is != 0  then theVertex is  on Edge  of  index <br>
//!          <edgeOn>. <br>
  Standard_EXPORT     Standard_Boolean Contains(const Standard_Integer TrianIndex,const BRepMesh_Vertex& theVertex,Standard_Integer& edgeOn) const;





protected:





private:

  //! Adjust the mesh on the frontier. <br>
  Standard_EXPORT     void FrontierAdjust() ;
  //! Find left polygon of the edge and call MeshPolygon. <br>
  Standard_EXPORT     void MeshLeftPolygonOf(const Standard_Integer EdgeIndex,const Standard_Boolean EdgeSens) ;
  //! Mesh closed polygon. <br>
  Standard_EXPORT     void MeshPolygon(TColStd_SequenceOfInteger& Polygon) ;
  //! Creates the triangles beetween the node <br>
//!          <Vertex> and the polyline <freeEdges>. <br>
  Standard_EXPORT     void CreateTriangles(const Standard_Integer vertexIndex,BRepMesh_MapOfIntegerInteger& freeEdges) ;
  //! Deletes the triangle of index <TrianIndex> and <br>
//!          add the free edges to the map. <br>
//!          When an edge is suppressed more than one time <br>
//!          it is destroyed. <br>
  Standard_EXPORT     void DeleteTriangle(const Standard_Integer TrianIndex,BRepMesh_MapOfIntegerInteger& freeEdges) ;
  
  Standard_EXPORT     void Perform(Bnd_Box2d& theBndBox,TColStd_Array1OfInteger& theVertexIndices) ;
  //! Creates the triangles on new nodes <br>
  Standard_EXPORT     void CreateTrianglesOnNewVertices(TColStd_Array1OfInteger& theVertexIndices) ;
  //! Check intersection between the two segments. <br>
  Standard_EXPORT     Standard_Boolean IntSegSeg(const BRepMesh_Edge& theEdge1,const BRepMesh_Edge& theEdge2) ;
  //! Removes triangles within polygon <br>
  Standard_EXPORT     void KillInternalTriangles(const Standard_Integer theEdgeId,const TColStd_MapOfInteger& theIgnoredEdges,BRepMesh_MapOfIntegerInteger& theLoopEdges) ;
  //! Cleanup mesh from the free triangles <br>
  Standard_EXPORT     void CleanupMesh() ;
  //! Removes triangles around the given pivot node <br>
  Standard_EXPORT     void RemovePivotTriangles(const Standard_Integer theEdgeInfo,const Standard_Integer thePivotNode,TColStd_MapOfInteger& theInfectedEdges,BRepMesh_MapOfIntegerInteger& theLoopEdges,const Standard_Boolean isFirstPass) ;
  //! Remove internal triangles from the given polygon <br>
  Standard_EXPORT     void CleanupPolygon(const TColStd_SequenceOfInteger& thePolygon,TColStd_MapOfInteger& theInfectedEdges,BRepMesh_MapOfIntegerInteger& theLoopEdges) ;


Handle_BRepMesh_DataStructureOfDelaun myMeshData;
Standard_Boolean myPositiveOrientation;
BRepMesh_CircleTool myCircles;
Standard_Integer mySupVert1;
Standard_Integer mySupVert2;
Standard_Integer mySupVert3;
BRepMesh_Triangle mySupTrian;
BRepMesh_MapOfInteger myMapEdges;


};


#include <BRepMesh_Delaun.lxx>



// other Inline functions and methods (like "C++: function call" methods)


#endif
