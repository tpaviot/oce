// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _GeomInt_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfWLApprox_HeaderFile
#define _GeomInt_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfWLApprox_HeaderFile

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
#ifndef _gp_Pnt_HeaderFile
#include <gp_Pnt.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _gp_Vec_HeaderFile
#include <gp_Vec.hxx>
#endif
#ifndef _IntImp_ConstIsoparametric_HeaderFile
#include <IntImp_ConstIsoparametric.hxx>
#endif
#ifndef _math_FunctionSetWithDerivatives_HeaderFile
#include <math_FunctionSetWithDerivatives.hxx>
#endif
#ifndef _Handle_Adaptor3d_HSurface_HeaderFile
#include <Handle_Adaptor3d_HSurface.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _gp_Dir_HeaderFile
#include <gp_Dir.hxx>
#endif
#ifndef _gp_Dir2d_HeaderFile
#include <gp_Dir2d.hxx>
#endif
class StdFail_UndefinedDerivative;
class Standard_ConstructionError;
class Adaptor3d_HSurface;
class Adaptor3d_HSurfaceTool;
class math_Vector;
class math_Matrix;
class TColStd_Array1OfReal;



class GeomInt_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfWLApprox  : public math_FunctionSetWithDerivatives {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   GeomInt_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfWLApprox();
  
  Standard_EXPORT   GeomInt_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfWLApprox(const Handle(Adaptor3d_HSurface)& S1,const Handle(Adaptor3d_HSurface)& S2);
  
  Standard_EXPORT     Standard_Integer NbVariables() const;
  
  Standard_EXPORT     Standard_Integer NbEquations() const;
  
  Standard_EXPORT     Standard_Boolean Value(const math_Vector& X,math_Vector& F) ;
  
  Standard_EXPORT     Standard_Boolean Derivatives(const math_Vector& X,math_Matrix& D) ;
  
  Standard_EXPORT     Standard_Boolean Values(const math_Vector& X,math_Vector& F,math_Matrix& D) ;
  
  Standard_EXPORT     void ComputeParameters(const IntImp_ConstIsoparametric ChoixIso,const TColStd_Array1OfReal& Param,math_Vector& UVap,math_Vector& BornInf,math_Vector& BornSup,math_Vector& Tolerance) ;
  
        Standard_Real Root() const;
  
        gp_Pnt Point() const;
  
  Standard_EXPORT     Standard_Boolean IsTangent(const math_Vector& UVap,TColStd_Array1OfReal& Param,IntImp_ConstIsoparametric& BestChoix) ;
  
        gp_Dir Direction() const;
  
        gp_Dir2d DirectionOnS1() const;
  
        gp_Dir2d DirectionOnS2() const;
  
       const Handle_Adaptor3d_HSurface& AuxillarSurface1() const;
  
       const Handle_Adaptor3d_HSurface& AuxillarSurface2() const;





protected:





private:



Standard_Address surf1;
Standard_Address surf2;
gp_Pnt pntsol1;
gp_Pnt pntsol2;
Standard_Real f[3];
Standard_Boolean compute;
Standard_Boolean tangent;
Standard_Real tgduv[4];
gp_Vec dpuv[4];
IntImp_ConstIsoparametric chxIso;
Standard_Real paramConst;
Standard_Real ua0;
Standard_Real va0;
Standard_Real ua1;
Standard_Real va1;
Standard_Real ub0;
Standard_Real vb0;
Standard_Real ub1;
Standard_Real vb1;
Standard_Real ures1;
Standard_Real ures2;
Standard_Real vres1;
Standard_Real vres2;


};

#define ThePSurface Handle_Adaptor3d_HSurface
#define ThePSurface_hxx <Adaptor3d_HSurface.hxx>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hxx>
#define IntImp_ZerParFunc GeomInt_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfWLApprox
#define IntImp_ZerParFunc_hxx <GeomInt_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfWLApprox.hxx>

#include <IntImp_ZerParFunc.lxx>

#undef ThePSurface
#undef ThePSurface_hxx
#undef ThePSurfaceTool
#undef ThePSurfaceTool_hxx
#undef IntImp_ZerParFunc
#undef IntImp_ZerParFunc_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif
