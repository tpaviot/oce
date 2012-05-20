// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _ProjLib_CompProjectedCurve_HeaderFile
#define _ProjLib_CompProjectedCurve_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Handle_Adaptor3d_HSurface_HeaderFile
#include <Handle_Adaptor3d_HSurface.hxx>
#endif
#ifndef _Handle_Adaptor3d_HCurve_HeaderFile
#include <Handle_Adaptor3d_HCurve.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Handle_ProjLib_HSequenceOfHSequenceOfPnt_HeaderFile
#include <Handle_ProjLib_HSequenceOfHSequenceOfPnt.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Handle_TColStd_HArray1OfBoolean_HeaderFile
#include <Handle_TColStd_HArray1OfBoolean.hxx>
#endif
#ifndef _Handle_TColStd_HArray1OfReal_HeaderFile
#include <Handle_TColStd_HArray1OfReal.hxx>
#endif
#ifndef _Adaptor2d_Curve2d_HeaderFile
#include <Adaptor2d_Curve2d.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _GeomAbs_Shape_HeaderFile
#include <GeomAbs_Shape.hxx>
#endif
#ifndef _Handle_Adaptor2d_HCurve2d_HeaderFile
#include <Handle_Adaptor2d_HCurve2d.hxx>
#endif
#ifndef _GeomAbs_CurveType_HeaderFile
#include <GeomAbs_CurveType.hxx>
#endif
class Adaptor3d_HSurface;
class Adaptor3d_HCurve;
class ProjLib_HSequenceOfHSequenceOfPnt;
class TColStd_HArray1OfBoolean;
class TColStd_HArray1OfReal;
class Standard_OutOfRange;
class Standard_NoSuchObject;
class Standard_DomainError;
class Standard_NotImplemented;
class gp_Pnt2d;
class gp_Vec2d;
class Adaptor2d_HCurve2d;
class TColStd_Array1OfReal;



class ProjLib_CompProjectedCurve  : public Adaptor2d_Curve2d {
public:

  void* operator new(size_t,void* anAddress) 
  {
    return anAddress;
  }
  void* operator new(size_t size) 
  {
    return Standard::Allocate(size); 
  }
  void  operator delete(void *anAddress) 
  {
    if (anAddress) Standard::Free((Standard_Address&)anAddress); 
  }

  
  Standard_EXPORT   ProjLib_CompProjectedCurve();
  //! try to find all solutions <br>
  Standard_EXPORT   ProjLib_CompProjectedCurve(const Handle(Adaptor3d_HSurface)& S,const Handle(Adaptor3d_HCurve)& C,const Standard_Real TolU,const Standard_Real TolV);
  //! this constructor tries to optimize the search using the <br>
//! assamption that maximum distance between surface and curve less or <br>
//! equal then MaxDist. <br>
//! if MaxDist < 0 then algorithm works as above. <br>
  Standard_EXPORT   ProjLib_CompProjectedCurve(const Handle(Adaptor3d_HSurface)& S,const Handle(Adaptor3d_HCurve)& C,const Standard_Real TolU,const Standard_Real TolV,const Standard_Real MaxDist);
  //! computes a set of projected point and determine the <br>
//! continuous parts of the projected  curves. The  points <br>
//! corresponding to a projection on the bounds of the surface are <br>
//! included  in this set of points. <br>
  Standard_EXPORT     void Init() ;
  //! Changes the surface. <br>
  Standard_EXPORT     void Load(const Handle(Adaptor3d_HSurface)& S) ;
  //! Changes the  curve. <br>
  Standard_EXPORT     void Load(const Handle(Adaptor3d_HCurve)& C) ;
  
  Standard_EXPORT    const Handle_Adaptor3d_HSurface& GetSurface() const;
  
  Standard_EXPORT    const Handle_Adaptor3d_HCurve& GetCurve() const;
  
  Standard_EXPORT     void GetTolerance(Standard_Real& TolU,Standard_Real& TolV) const;
  //! returns the number of continuous part of the projected curve <br>
  Standard_EXPORT     Standard_Integer NbCurves() const;
  //! returns the bounds of the continuous part corresponding to Index <br>
  Standard_EXPORT     void Bounds(const Standard_Integer Index,Standard_Real& Udeb,Standard_Real& Ufin) const;
  //! returns  True  if  part  of  projection with  number  Index is  a  single  point  and  writes  its  coordinats in  P <br>
  Standard_EXPORT     Standard_Boolean IsSinglePnt(const Standard_Integer Index,gp_Pnt2d& P) const;
  //! returns  True  if  part  of  projection with  number  Index is  an  u-isoparametric curve  of  input  surface <br>
  Standard_EXPORT     Standard_Boolean IsUIso(const Standard_Integer Index,Standard_Real& U) const;
  //! returns  True  if  part  of  projection with  number  Index is  an  v-isoparametric curve  of  input  surface <br>
  Standard_EXPORT     Standard_Boolean IsVIso(const Standard_Integer Index,Standard_Real& V) const;
  //! Computes the point of parameter U on the curve. <br>
  Standard_EXPORT     gp_Pnt2d Value(const Standard_Real U) const;
  //! Computes the point of parameter U on the curve. <br>
  Standard_EXPORT     void D0(const Standard_Real U,gp_Pnt2d& P) const;
  //! Computes the point of parameter U on the curve with its <br>
//!  first derivative. <br>//! Raised if the continuity of the current interval <br>
//!  is not C1. <br>
  Standard_EXPORT     void D1(const Standard_Real U,gp_Pnt2d& P,gp_Vec2d& V) const;
  
//!  Returns the point P of parameter U, the first and second <br>
//!  derivatives V1 and V2. <br>//! Raised if the continuity of the current interval <br>
//!  is not C2. <br>
  Standard_EXPORT     void D2(const Standard_Real U,gp_Pnt2d& P,gp_Vec2d& V1,gp_Vec2d& V2) const;
  
//!  The returned vector gives the value of the derivative for the <br>
//!  order of derivation N. <br>//! Raised if N < 1. <br>//! Raised if N > 2. <br>
  Standard_EXPORT     gp_Vec2d DN(const Standard_Real U,const Standard_Integer N) const;
  //! Returns  the  first  parameter of  the  curve  C <br>
//!  which  has  a  projection  on  S. <br>
  Standard_EXPORT     Standard_Real FirstParameter() const;
  //! Returns  the  last  parameter of  the  curve  C <br>
//!  which  has  a  projection  on  S. <br>
  Standard_EXPORT     Standard_Real LastParameter() const;
  //! Returns  the number  of  intervals which  define <br>
//!  an  S  continuous  part  of  the  projected  curve <br>
  Standard_EXPORT     Standard_Integer NbIntervals(const GeomAbs_Shape S) const;
  //! Returns    a  curve equivalent   of  <me>  between <br>
//!          parameters <First>  and <Last>. <Tol>  is used  to <br>
//!          test for 2d points confusion. <br>//! If <First> >= <Last> <br>
  Standard_EXPORT     Handle_Adaptor2d_HCurve2d Trim(const Standard_Real FirstParam,const Standard_Real LastParam,const Standard_Real Tol) const;
  //! Returns  the  parameters  corresponding  to <br>
//!          S  discontinuities. <br>
//! <br>
//!          The array must provide  enough room to  accomodate <br>
//!          for the parameters. i.e. T.Length() > NbIntervals() <br>
  Standard_EXPORT     void Intervals(TColStd_Array1OfReal& T,const GeomAbs_Shape S) const;
  //!  returns  the  maximum  distance  between <br>
//!  curve  to  project  and  surface <br>
  Standard_EXPORT     Standard_Real MaxDistance(const Standard_Integer Index) const;
  
  Standard_EXPORT    const Handle_ProjLib_HSequenceOfHSequenceOfPnt& GetSequence() const;
  //! Returns  the  type of the   curve  in the  current <br>
//!          interval :   Line,   Circle,   Ellipse, Hyperbola, <br>
//!          Parabola, BezierCurve, BSplineCurve, OtherCurve. <br>
  Standard_EXPORT     GeomAbs_CurveType GetType() const;





protected:





private:

  
  Standard_EXPORT     void BuildIntervals(const GeomAbs_Shape S) const;


Handle_Adaptor3d_HSurface mySurface;
Handle_Adaptor3d_HCurve myCurve;
Standard_Integer myNbCurves;
Handle_ProjLib_HSequenceOfHSequenceOfPnt mySequence;
Standard_Real myTolU;
Standard_Real myTolV;
Standard_Real myMaxDist;
Handle_TColStd_HArray1OfBoolean myUIso;
Handle_TColStd_HArray1OfBoolean myVIso;
Handle_TColStd_HArray1OfBoolean mySnglPnts;
Handle_TColStd_HArray1OfReal myMaxDistance;
Handle_TColStd_HArray1OfReal myTabInt;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
