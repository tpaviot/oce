// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _ShapeAnalysis_Edge_HeaderFile
#define _ShapeAnalysis_Edge_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Handle_Geom_Curve_HeaderFile
#include <Handle_Geom_Curve.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Handle_Geom_Surface_HeaderFile
#include <Handle_Geom_Surface.hxx>
#endif
#ifndef _Handle_Geom2d_Curve_HeaderFile
#include <Handle_Geom2d_Curve.hxx>
#endif
#ifndef _ShapeExtend_Status_HeaderFile
#include <ShapeExtend_Status.hxx>
#endif
class TopoDS_Edge;
class Geom_Curve;
class TopoDS_Face;
class Geom_Surface;
class TopLoc_Location;
class Geom2d_Curve;
class gp_Pnt2d;
class TopoDS_Vertex;
class gp_Vec2d;
class gp_Pnt;


//! Tool for analyzing the edge. <br>
//!          Queries geometrical representations of the edge (3d curve, pcurve <br>
//!          on the given face or surface) and topological sub-shapes (bounding <br>
//!          vertices). <br>
//!          Provides methods for analyzing geometry and topology consistency <br>
//!          (3d and pcurve(s) consistency, their adjacency to the vertices). <br>
class ShapeAnalysis_Edge  {
public:

  DEFINE_STANDARD_ALLOC

  //! Empty constructor; initialises Status to OK <br>
  Standard_EXPORT   ShapeAnalysis_Edge();
  //! Tells if the edge has a 3d curve <br>
  Standard_EXPORT     Standard_Boolean HasCurve3d(const TopoDS_Edge& edge) const;
  //! Returns the 3d curve and bounding parameteres for the edge <br>
//!          Returns False if no 3d curve. <br>
//!          If <orient> is True (default), takes orientation into account: <br>
//!          if the edge is reversed, cf and cl are toggled <br>
  Standard_EXPORT     Standard_Boolean Curve3d(const TopoDS_Edge& edge,Handle(Geom_Curve)& C3d,Standard_Real& cf,Standard_Real& cl,const Standard_Boolean orient = Standard_True) const;
  //! Gives True if the edge has a 3d curve, this curve is closed, <br>
//!          and the edge has the same vertex at start and end <br>
  Standard_EXPORT     Standard_Boolean IsClosed3d(const TopoDS_Edge& edge) const;
  //! Tells if the Edge has a pcurve on the face. <br>
  Standard_EXPORT     Standard_Boolean HasPCurve(const TopoDS_Edge& edge,const TopoDS_Face& face) const;
  //! Tells if the edge has a pcurve on the surface (with location). <br>
  Standard_EXPORT     Standard_Boolean HasPCurve(const TopoDS_Edge& edge,const Handle(Geom_Surface)& surface,const TopLoc_Location& location) const;
  
  Standard_EXPORT     Standard_Boolean PCurve(const TopoDS_Edge& edge,const TopoDS_Face& face,Handle(Geom2d_Curve)& C2d,Standard_Real& cf,Standard_Real& cl,const Standard_Boolean orient = Standard_True) const;
  //! Returns the pcurve and bounding parameteres for the edge <br>
//!          lying on the surface. <br>
//!          Returns False if the edge has no pcurve on this surface. <br>
//!          If <orient> is True (default), takes orientation into account: <br>
//!          if the edge is reversed, cf and cl are toggled <br>
  Standard_EXPORT     Standard_Boolean PCurve(const TopoDS_Edge& edge,const Handle(Geom_Surface)& surface,const TopLoc_Location& location,Handle(Geom2d_Curve)& C2d,Standard_Real& cf,Standard_Real& cl,const Standard_Boolean orient = Standard_True) const;
  
  Standard_EXPORT     Standard_Boolean BoundUV(const TopoDS_Edge& edge,const TopoDS_Face& face,gp_Pnt2d& first,gp_Pnt2d& last) const;
  //! Returns the ends of pcurve <br>
//!          Calls method PCurve with <orient> equal to True <br>
  Standard_EXPORT     Standard_Boolean BoundUV(const TopoDS_Edge& edge,const Handle(Geom_Surface)& surface,const TopLoc_Location& location,gp_Pnt2d& first,gp_Pnt2d& last) const;
  
  Standard_EXPORT     Standard_Boolean IsSeam(const TopoDS_Edge& edge,const TopoDS_Face& face) const;
  //! Returns True if the edge has two pcurves on one surface <br>
  Standard_EXPORT     Standard_Boolean IsSeam(const TopoDS_Edge& edge,const Handle(Geom_Surface)& surface,const TopLoc_Location& location) const;
  //! Returns start vertex of the edge (taking edge orientation <br>
//!          into account). <br>
  Standard_EXPORT     TopoDS_Vertex FirstVertex(const TopoDS_Edge& edge) const;
  //! Returns end vertex of the edge (taking edge orientation <br>
//!          into account). <br>
  Standard_EXPORT     TopoDS_Vertex LastVertex(const TopoDS_Edge& edge) const;
  
  Standard_EXPORT     Standard_Boolean GetEndTangent2d(const TopoDS_Edge& edge,const TopoDS_Face& face,const Standard_Boolean atEnd,gp_Pnt2d& pos,gp_Vec2d& tang,const Standard_Real dparam = 0.0) const;
  //! Returns tangent of the edge pcurve at its start (if atEnd is <br>
//!          False) or end (if True), regarding the orientation of edge. <br>
//!          If edge is REVERSED, tangent is reversed before return. <br>
//!          Returns True if pcurve is available and tangent is computed <br>
//!          and is not null, else False. <br>
  Standard_EXPORT     Standard_Boolean GetEndTangent2d(const TopoDS_Edge& edge,const Handle(Geom_Surface)& surface,const TopLoc_Location& location,const Standard_Boolean atEnd,gp_Pnt2d& pos,gp_Vec2d& tang,const Standard_Real dparam = 0.0) const;
  //! Checks the start and/or end vertex of the edge for matching <br>
//!          with 3d curve with the given precision. <br>
//!          <vtx> = 1 : start vertex only <br>
//!          <vtx> = 2 : end vertex only <br>
//!          <vtx> = 0 : both (default) <br>
//!          If preci < 0 the vertices are considered with their own <br>
//!          tolerances, else with the given <preci>. <br>
  Standard_EXPORT     Standard_Boolean CheckVerticesWithCurve3d(const TopoDS_Edge& edge,const Standard_Real preci = -1,const Standard_Integer vtx = 0) ;
  
  Standard_EXPORT     Standard_Boolean CheckVerticesWithPCurve(const TopoDS_Edge& edge,const TopoDS_Face& face,const Standard_Real preci = -1,const Standard_Integer vtx = 0) ;
  //! Checks the start and/or end vertex of the edge for matching <br>
//!          with pcurve with the given precision. <br>
//!          <vtx> = 1 : start vertex <br>
//!          <vtx> = 2 : end vertex <br>
//!          <vtx> = 0 : both <br>
//!          If preci < 0 the vertices are considered with their own <br>
//!          tolerances, else with the given <preci>. <br>
  Standard_EXPORT     Standard_Boolean CheckVerticesWithPCurve(const TopoDS_Edge& edge,const Handle(Geom_Surface)& surface,const TopLoc_Location& location,const Standard_Real preci = -1,const Standard_Integer vtx = 0) ;
  
  Standard_EXPORT     Standard_Boolean CheckVertexTolerance(const TopoDS_Edge& edge,const TopoDS_Face& face,Standard_Real& toler1,Standard_Real& toler2) ;
  //! Checks if it is necessary to increase tolerances of the edge <br>
//!          vertices to comprise the ends of 3d curve and pcurve on <br>
//!          the given face (first method) or all pcurves stored in an edge <br>
//!          (second one) <br>
//!          toler1 returns necessary tolerance for first vertex, <br>
//!          toler2 returns necessary tolerance for last vertex. <br>
  Standard_EXPORT     Standard_Boolean CheckVertexTolerance(const TopoDS_Edge& edge,Standard_Real& toler1,Standard_Real& toler2) ;
  
  Standard_EXPORT     Standard_Boolean CheckCurve3dWithPCurve(const TopoDS_Edge& edge,const TopoDS_Face& face) ;
  //! Checks mutual orientation of 3d curve and pcurve on the <br>
//!          analysis of curves bounding points <br>
  Standard_EXPORT     Standard_Boolean CheckCurve3dWithPCurve(const TopoDS_Edge& edge,const Handle(Geom_Surface)& surface,const TopLoc_Location& location) ;
  //! Returns the status (in the form of True/False) of last Check <br>
  Standard_EXPORT     Standard_Boolean Status(const ShapeExtend_Status status) const;
  //! Checks the edge to be SameParameter. <br>
//!          Calculates the maximal deviation between 3d curve and each <br>
//!          pcurve of the edge on <NbControl> equidistant points (the same <br>
//!          algorithm as in BRepCheck; default value is 23 as in BRepCheck). <br>
//!          This deviation is returned in <maxdev> parameter. <br>
//!          If deviation is greater than tolerance of the edge (i.e. <br>
//!          incorrect flag) returns False, else returns True. <br>
  Standard_EXPORT     Standard_Boolean CheckSameParameter(const TopoDS_Edge& edge,Standard_Real& maxdev,const Standard_Integer NbControl = 23) ;
  //! Checks the first edge is overlapped with second edge. <br>
//!          If distance between two edges is less then theTolOverlap <br>
//!          edges is overlapped. <br>
//!          theDomainDis - length of part of edges on wich edges is overlapped. <br>
  Standard_EXPORT     Standard_Boolean CheckOverlapping(const TopoDS_Edge& theEdge1,const TopoDS_Edge& theEdge2,Standard_Real& theTolOverlap,const Standard_Real theDomainDist = 0.0) ;





protected:



Standard_Integer myStatus;


private:

  //! Check points by pairs (A and A, B and B) with precisions <br>
//!          (preci1 and preci2). <br>
//!          P1 are the points either from 3d curve or from vertices, <br>
//!          P2 are the points from pcurve <br>
  Standard_EXPORT     Standard_Boolean CheckPoints(const gp_Pnt& P1A,const gp_Pnt& P1B,const gp_Pnt& P2A,const gp_Pnt& P2B,const Standard_Real preci1,const Standard_Real preci2) ;




};





// other Inline functions and methods (like "C++: function call" methods)


#endif
