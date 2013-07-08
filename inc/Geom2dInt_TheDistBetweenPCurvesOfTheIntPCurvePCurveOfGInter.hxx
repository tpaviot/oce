// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter_HeaderFile
#define _Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Standard_Address_HeaderFile
#include <Standard_Address.hxx>
#endif
#ifndef _math_FunctionSetWithDerivatives_HeaderFile
#include <math_FunctionSetWithDerivatives.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class Adaptor2d_Curve2d;
class Geom2dInt_Geom2dCurveTool;
class math_Vector;
class math_Matrix;



class Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter  : public math_FunctionSetWithDerivatives {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter(const Adaptor2d_Curve2d& curve1,const Adaptor2d_Curve2d& curve2);
  
  Standard_EXPORT     Standard_Integer NbVariables() const;
  
  Standard_EXPORT     Standard_Integer NbEquations() const;
  
  Standard_EXPORT     Standard_Boolean Value(const math_Vector& X,math_Vector& F) ;
  
  Standard_EXPORT     Standard_Boolean Derivatives(const math_Vector& X,math_Matrix& D) ;
  
  Standard_EXPORT     Standard_Boolean Values(const math_Vector& X,math_Vector& F,math_Matrix& D) ;





protected:





private:



Standard_Address thecurve1;
Standard_Address thecurve2;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
