// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _HLRBRep_LineTool_HeaderFile
#define _HLRBRep_LineTool_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _GeomAbs_Shape_HeaderFile
#include <GeomAbs_Shape.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _gp_Pnt_HeaderFile
#include <gp_Pnt.hxx>
#endif
#ifndef _gp_Vec_HeaderFile
#include <gp_Vec.hxx>
#endif
#ifndef _GeomAbs_CurveType_HeaderFile
#include <GeomAbs_CurveType.hxx>
#endif
#ifndef _gp_Lin_HeaderFile
#include <gp_Lin.hxx>
#endif
#ifndef _gp_Circ_HeaderFile
#include <gp_Circ.hxx>
#endif
#ifndef _gp_Elips_HeaderFile
#include <gp_Elips.hxx>
#endif
#ifndef _gp_Hypr_HeaderFile
#include <gp_Hypr.hxx>
#endif
#ifndef _gp_Parab_HeaderFile
#include <gp_Parab.hxx>
#endif
#ifndef _Handle_Geom_BezierCurve_HeaderFile
#include <Handle_Geom_BezierCurve.hxx>
#endif
#ifndef _Handle_Geom_BSplineCurve_HeaderFile
#include <Handle_Geom_BSplineCurve.hxx>
#endif
#ifndef _Handle_TColStd_HArray1OfReal_HeaderFile
#include <Handle_TColStd_HArray1OfReal.hxx>
#endif
class Standard_OutOfRange;
class Standard_NoSuchObject;
class Standard_DomainError;
class gp_Lin;
class TColStd_Array1OfReal;
class gp_Pnt;
class gp_Vec;
class Geom_BezierCurve;
class Geom_BSplineCurve;
class TColgp_Array1OfPnt;
class TColStd_Array1OfInteger;
class TColStd_HArray1OfReal;


//! The  LineTool  class  provides  class  methods to <br>
//!          access the methodes of the Line. <br>
class HLRBRep_LineTool  {
public:

  DEFINE_STANDARD_ALLOC

  
      static  Standard_Real FirstParameter(const gp_Lin& C) ;
  
      static  Standard_Real LastParameter(const gp_Lin& C) ;
  
      static  GeomAbs_Shape Continuity(const gp_Lin& C) ;
  //! If necessary,   breaks the line  in  intervals of <br>
//!          continuity <S>.     And   returns  the  number  of <br>
//!          intervals. <br>
      static  Standard_Integer NbIntervals(const gp_Lin& C,const GeomAbs_Shape S) ;
  //! Sets the current working interval. <br>
      static  void Intervals(const gp_Lin& C,TColStd_Array1OfReal& T,const GeomAbs_Shape Sh) ;
  //! Returns  the  first  parameter    of  the  current <br>
//!          interval. <br>
      static  Standard_Real IntervalFirst(const gp_Lin& C) ;
  //! Returns  the  last  parameter    of  the  current <br>
//!          interval. <br>
      static  Standard_Real IntervalLast(const gp_Lin& C) ;
  
      static  GeomAbs_Shape IntervalContinuity(const gp_Lin& C) ;
  
      static  Standard_Boolean IsClosed(const gp_Lin& C) ;
  
      static  Standard_Boolean IsPeriodic(const gp_Lin& C) ;
  
      static  Standard_Real Period(const gp_Lin& C) ;
  //! Computes the point of parameter U on the line. <br>
      static  gp_Pnt Value(const gp_Lin& C,const Standard_Real U) ;
  //! Computes the point of parameter U on the line. <br>
      static  void D0(const gp_Lin& C,const Standard_Real U,gp_Pnt& P) ;
  //! Computes the point of parameter U on the line with its <br>
//!  first derivative. <br>//! Raised if the continuity of the current interval <br>
//!  is not C1. <br>
      static  void D1(const gp_Lin& C,const Standard_Real U,gp_Pnt& P,gp_Vec& V) ;
  
//!  Returns the point P of parameter U, the first and second <br>
//!  derivatives V1 and V2. <br>//! Raised if the continuity of the current interval <br>
//!  is not C2. <br>
      static  void D2(const gp_Lin& C,const Standard_Real U,gp_Pnt& P,gp_Vec& V1,gp_Vec& V2) ;
  
//!  Returns the point P of parameter U, the first, the second <br>
//!  and the third derivative. <br>//! Raised if the continuity of the current interval <br>
//!  is not C3. <br>
      static  void D3(const gp_Lin& C,const Standard_Real U,gp_Pnt& P,gp_Vec& V1,gp_Vec& V2,gp_Vec& V3) ;
  
//!  The returned vector gives the value of the derivative for the <br>
//!  order of derivation N. <br>//! Raised if the continuity of the current interval <br>
//!  is not CN. <br>//! Raised if N < 1. <br>
      static  gp_Vec DN(const gp_Lin& C,const Standard_Real U,const Standard_Integer N) ;
  //!  Returns the parametric  resolution corresponding <br>
//!         to the real space resolution <R3d>. <br>
      static  Standard_Real Resolution(const gp_Lin& C,const Standard_Real R3d) ;
  //! Returns  the  type of the   line  in the  current <br>
//!          interval :   Line,   Circle,   Ellipse, Hyperbola, <br>
//!          Parabola, BezierCurve, BSplineCurve, OtherCurve. <br>
      static  GeomAbs_CurveType GetType(const gp_Lin& C) ;
  
      static  gp_Lin Line(const gp_Lin& C) ;
  
      static  gp_Circ Circle(const gp_Lin& C) ;
  
      static  gp_Elips Ellipse(const gp_Lin& C) ;
  
      static  gp_Hypr Hyperbola(const gp_Lin& C) ;
  
      static  gp_Parab Parabola(const gp_Lin& C) ;
  
      static  Handle_Geom_BezierCurve Bezier(const gp_Lin& C) ;
  
      static  Handle_Geom_BSplineCurve BSpline(const gp_Lin& C) ;
  
      static  Standard_Integer Degree(const gp_Lin& C) ;
  
      static  Standard_Integer NbPoles(const gp_Lin& C) ;
  
      static  void Poles(const gp_Lin& C,TColgp_Array1OfPnt& TP) ;
  
      static  Standard_Boolean IsRational(const gp_Lin& C) ;
  
      static  void PolesAndWeights(const gp_Lin& C,TColgp_Array1OfPnt& TP,TColStd_Array1OfReal& TW) ;
  
      static  Standard_Integer NbKnots(const gp_Lin& C) ;
  
      static  void KnotsAndMultiplicities(const gp_Lin& C,TColStd_Array1OfReal& TK,TColStd_Array1OfInteger& TM) ;
  
      static  Standard_Integer NbSamples(const gp_Lin& C,const Standard_Real U0,const Standard_Real U1) ;
  
  Standard_EXPORT   static  void SamplePars(const gp_Lin& C,const Standard_Real U0,const Standard_Real U1,const Standard_Real Defl,const Standard_Integer NbMin,Handle(TColStd_HArray1OfReal)& Pars) ;





protected:





private:





};


#include <HLRBRep_LineTool.lxx>



// other Inline functions and methods (like "C++: function call" methods)


#endif
