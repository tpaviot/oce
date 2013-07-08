// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Geom2dLProp_CLProps2d_HeaderFile
#define _Geom2dLProp_CLProps2d_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Handle_Geom2d_Curve_HeaderFile
#include <Handle_Geom2d_Curve.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _gp_Pnt2d_HeaderFile
#include <gp_Pnt2d.hxx>
#endif
#ifndef _gp_Vec2d_HeaderFile
#include <gp_Vec2d.hxx>
#endif
#ifndef _gp_Dir2d_HeaderFile
#include <gp_Dir2d.hxx>
#endif
#ifndef _LProp_Status_HeaderFile
#include <LProp_Status.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class Geom2d_Curve;
class LProp_BadContinuity;
class Standard_DomainError;
class Standard_OutOfRange;
class LProp_NotDefined;
class gp_Vec2d;
class gp_Pnt2d;
class gp_Dir2d;
class Geom2dLProp_Curve2dTool;



class Geom2dLProp_CLProps2d  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   Geom2dLProp_CLProps2d(const Handle(Geom2d_Curve)& C,const Standard_Integer N,const Standard_Real Resolution);
  
  Standard_EXPORT   Geom2dLProp_CLProps2d(const Handle(Geom2d_Curve)& C,const Standard_Real U,const Standard_Integer N,const Standard_Real Resolution);
  
  Standard_EXPORT   Geom2dLProp_CLProps2d(const Standard_Integer N,const Standard_Real Resolution);
  
  Standard_EXPORT     void SetParameter(const Standard_Real U) ;
  
  Standard_EXPORT     void SetCurve(const Handle(Geom2d_Curve)& C) ;
  
  Standard_EXPORT    const gp_Pnt2d& Value() const;
  
  Standard_EXPORT    const gp_Vec2d& D1() ;
  
  Standard_EXPORT    const gp_Vec2d& D2() ;
  
  Standard_EXPORT    const gp_Vec2d& D3() ;
  
  Standard_EXPORT     Standard_Boolean IsTangentDefined() ;
  
  Standard_EXPORT     void Tangent(gp_Dir2d& D) ;
  
  Standard_EXPORT     Standard_Real Curvature() ;
  
  Standard_EXPORT     void Normal(gp_Dir2d& N) ;
  
  Standard_EXPORT     void CentreOfCurvature(gp_Pnt2d& P) ;





protected:





private:



Handle_Geom2d_Curve myCurve;
Standard_Real u;
Standard_Integer level;
Standard_Real cn;
Standard_Real linTol;
gp_Pnt2d pnt;
gp_Vec2d d[3];
gp_Dir2d tangent;
Standard_Real curvature;
LProp_Status tangentStatus;
Standard_Integer significantFirstDerivativeOrder;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
