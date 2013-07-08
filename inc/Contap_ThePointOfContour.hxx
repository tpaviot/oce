// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Contap_ThePointOfContour_HeaderFile
#define _Contap_ThePointOfContour_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _gp_Pnt_HeaderFile
#include <gp_Pnt.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Handle_Adaptor2d_HCurve2d_HeaderFile
#include <Handle_Adaptor2d_HCurve2d.hxx>
#endif
#ifndef _IntSurf_Transition_HeaderFile
#include <IntSurf_Transition.hxx>
#endif
#ifndef _Handle_Adaptor3d_HVertex_HeaderFile
#include <Handle_Adaptor3d_HVertex.hxx>
#endif
class Adaptor2d_HCurve2d;
class Adaptor3d_HVertex;
class Standard_DomainError;
class gp_Pnt;
class IntSurf_Transition;



class Contap_ThePointOfContour  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   Contap_ThePointOfContour();
  
  Standard_EXPORT   Contap_ThePointOfContour(const gp_Pnt& Pt,const Standard_Real U,const Standard_Real V);
  
        void SetValue(const gp_Pnt& Pt,const Standard_Real U,const Standard_Real V) ;
  
        void SetParameter(const Standard_Real Para) ;
  
        void SetVertex(const Handle(Adaptor3d_HVertex)& V) ;
  
        void SetArc(const Handle(Adaptor2d_HCurve2d)& A,const Standard_Real Param,const IntSurf_Transition& TLine,const IntSurf_Transition& TArc) ;
  
        void SetMultiple() ;
  
        void SetInternal() ;
  
       const gp_Pnt& Value() const;
  
        Standard_Real ParameterOnLine() const;
  
        void Parameters(Standard_Real& U1,Standard_Real& V1) const;
  
        Standard_Boolean IsOnArc() const;
  
       const Handle_Adaptor2d_HCurve2d& Arc() const;
  
        Standard_Real ParameterOnArc() const;
  
       const IntSurf_Transition& TransitionOnLine() const;
  
       const IntSurf_Transition& TransitionOnArc() const;
  
        Standard_Boolean IsVertex() const;
  
       const Handle_Adaptor3d_HVertex& Vertex() const;
  
        Standard_Boolean IsMultiple() const;
  
        Standard_Boolean IsInternal() const;





protected:





private:



gp_Pnt pt;
Standard_Real uparam;
Standard_Real vparam;
Standard_Real paraline;
Standard_Boolean onarc;
Handle_Adaptor2d_HCurve2d arc;
IntSurf_Transition traline;
IntSurf_Transition traarc;
Standard_Real prmarc;
Standard_Boolean isvtx;
Handle_Adaptor3d_HVertex vtx;
Standard_Boolean ismult;
Standard_Boolean myInternal;


};

#define TheVertex Handle_Adaptor3d_HVertex
#define TheVertex_hxx <Adaptor3d_HVertex.hxx>
#define TheArc Handle_Adaptor2d_HCurve2d
#define TheArc_hxx <Adaptor2d_HCurve2d.hxx>
#define Contap_Point Contap_ThePointOfContour
#define Contap_Point_hxx <Contap_ThePointOfContour.hxx>

#include <Contap_Point.lxx>

#undef TheVertex
#undef TheVertex_hxx
#undef TheArc
#undef TheArc_hxx
#undef Contap_Point
#undef Contap_Point_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif
