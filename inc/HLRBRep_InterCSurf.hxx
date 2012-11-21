// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _HLRBRep_InterCSurf_HeaderFile
#define _HLRBRep_InterCSurf_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _IntCurveSurface_Intersection_HeaderFile
#include <IntCurveSurface_Intersection.hxx>
#endif
#ifndef _Standard_Address_HeaderFile
#include <Standard_Address.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
class gp_Lin;
class HLRBRep_LineTool;
class HLRBRep_SurfaceTool;
class HLRBRep_ThePolygonOfInterCSurf;
class HLRBRep_ThePolygonToolOfInterCSurf;
class HLRBRep_ThePolyhedronOfInterCSurf;
class HLRBRep_ThePolyhedronToolOfInterCSurf;
class HLRBRep_TheInterferenceOfInterCSurf;
class HLRBRep_TheCSFunctionOfInterCSurf;
class HLRBRep_TheExactInterCSurf;
class HLRBRep_TheQuadCurvExactInterCSurf;
class HLRBRep_TheQuadCurvFuncOfTheQuadCurvExactInterCSurf;
class Bnd_BoundSortBox;
class gp_Circ;
class gp_Elips;
class gp_Parab;
class gp_Hypr;
class IntAna_IntConicQuad;
class TColgp_Array2OfPnt;
class Bnd_Box;
class TColStd_Array1OfReal;



class HLRBRep_InterCSurf  : public IntCurveSurface_Intersection {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   HLRBRep_InterCSurf();
  
  Standard_EXPORT     void Perform(const gp_Lin& Curve,const Standard_Address& Surface) ;
  
  Standard_EXPORT     void Perform(const gp_Lin& Curve,const HLRBRep_ThePolygonOfInterCSurf& Polygon,const Standard_Address& Surface) ;
  
  Standard_EXPORT     void Perform(const gp_Lin& Curve,const HLRBRep_ThePolygonOfInterCSurf& ThePolygon,const Standard_Address& Surface,const HLRBRep_ThePolyhedronOfInterCSurf& Polyhedron) ;
  
  Standard_EXPORT     void Perform(const gp_Lin& Curve,const HLRBRep_ThePolygonOfInterCSurf& ThePolygon,const Standard_Address& Surface,const HLRBRep_ThePolyhedronOfInterCSurf& Polyhedron,Bnd_BoundSortBox& BndBSB) ;
  
  Standard_EXPORT     void Perform(const gp_Lin& Curve,const Standard_Address& Surface,const HLRBRep_ThePolyhedronOfInterCSurf& Polyhedron) ;





protected:

  
  Standard_EXPORT     void Perform(const gp_Lin& Curve,const Standard_Address& Surface,const Standard_Real U0,const Standard_Real V0,const Standard_Real U1,const Standard_Real V1) ;
  
  Standard_EXPORT     void InternalPerformCurveQuadric(const gp_Lin& Curve,const Standard_Address& Surface) ;
  
  Standard_EXPORT     void InternalPerform(const gp_Lin& Curve,const HLRBRep_ThePolygonOfInterCSurf& Polygon,const Standard_Address& Surface,const HLRBRep_ThePolyhedronOfInterCSurf& Polyhedron,const Standard_Real U1,const Standard_Real V1,const Standard_Real U2,const Standard_Real V2) ;
  
  Standard_EXPORT     void InternalPerform(const gp_Lin& Curve,const HLRBRep_ThePolygonOfInterCSurf& Polygon,const Standard_Address& Surface,const HLRBRep_ThePolyhedronOfInterCSurf& Polyhedron,const Standard_Real U1,const Standard_Real V1,const Standard_Real U2,const Standard_Real V2,Bnd_BoundSortBox& BSB) ;
  
  Standard_EXPORT     void InternalPerform(const gp_Lin& Curve,const HLRBRep_ThePolygonOfInterCSurf& Polygon,const Standard_Address& Surface,const Standard_Real U1,const Standard_Real V1,const Standard_Real U2,const Standard_Real V2) ;
  
  Standard_EXPORT     void PerformConicSurf(const gp_Lin& Line,const gp_Lin& Curve,const Standard_Address& Surface,const Standard_Real U1,const Standard_Real V1,const Standard_Real U2,const Standard_Real V2) ;
  
  Standard_EXPORT     void PerformConicSurf(const gp_Circ& Circle,const gp_Lin& Curve,const Standard_Address& Surface,const Standard_Real U1,const Standard_Real V1,const Standard_Real U2,const Standard_Real V2) ;
  
  Standard_EXPORT     void PerformConicSurf(const gp_Elips& Ellipse,const gp_Lin& Curve,const Standard_Address& Surface,const Standard_Real U1,const Standard_Real V1,const Standard_Real U2,const Standard_Real V2) ;
  
  Standard_EXPORT     void PerformConicSurf(const gp_Parab& Parab,const gp_Lin& Curve,const Standard_Address& Surface,const Standard_Real U1,const Standard_Real V1,const Standard_Real U2,const Standard_Real V2) ;
  
  Standard_EXPORT     void PerformConicSurf(const gp_Hypr& Hyper,const gp_Lin& Curve,const Standard_Address& Surface,const Standard_Real U1,const Standard_Real V1,const Standard_Real U2,const Standard_Real V2) ;
  
  Standard_EXPORT     void AppendIntAna(const gp_Lin& Curve,const Standard_Address& Surface,const IntAna_IntConicQuad& InterAna) ;
  
  Standard_EXPORT     void AppendPoint(const gp_Lin& Curve,const Standard_Real w,const Standard_Address& Surface,const Standard_Real u,const Standard_Real v) ;
  
  Standard_EXPORT     void AppendSegment(const gp_Lin& Curve,const Standard_Real u0,const Standard_Real u1,const Standard_Address& Surface) ;




private:

  
  Standard_EXPORT     void DoSurface(const Standard_Address& surface,const Standard_Real u0,const Standard_Real u1,const Standard_Real v0,const Standard_Real v1,TColgp_Array2OfPnt& pntsOnSurface,Bnd_Box& boxSurface,Standard_Real& gap) ;
  
  Standard_EXPORT     void DoNewBounds(const Standard_Address& surface,const Standard_Real u0,const Standard_Real u1,const Standard_Real v0,const Standard_Real v1,const TColgp_Array2OfPnt& pntsOnSurface,const TColStd_Array1OfReal& X,const TColStd_Array1OfReal& Y,const TColStd_Array1OfReal& Z,TColStd_Array1OfReal& Bounds) ;




};





// other Inline functions and methods (like "C++: function call" methods)


#endif
