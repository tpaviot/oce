// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _IntCurve_PConicTool_HeaderFile
#define _IntCurve_PConicTool_HeaderFile

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
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
class IntCurve_PConic;
class gp_Pnt2d;
class gp_Vec2d;


//! Implementation of the ParTool from IntImpParGen <br>
//!          for conics of gp, using the class PConic from IntCurve. <br>
class IntCurve_PConicTool  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   static  Standard_Real EpsX(const IntCurve_PConic& C) ;
  
  Standard_EXPORT   static  Standard_Integer NbSamples(const IntCurve_PConic& C) ;
  
  Standard_EXPORT   static  Standard_Integer NbSamples(const IntCurve_PConic& C,const Standard_Real U0,const Standard_Real U1) ;
  
  Standard_EXPORT   static  gp_Pnt2d Value(const IntCurve_PConic& C,const Standard_Real X) ;
  
  Standard_EXPORT   static  void D1(const IntCurve_PConic& C,const Standard_Real U,gp_Pnt2d& P,gp_Vec2d& T) ;
  
  Standard_EXPORT   static  void D2(const IntCurve_PConic& C,const Standard_Real U,gp_Pnt2d& P,gp_Vec2d& T,gp_Vec2d& N) ;





protected:





private:





};





// other Inline functions and methods (like "C++: function call" methods)


#endif
