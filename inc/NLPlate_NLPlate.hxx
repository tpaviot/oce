// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _NLPlate_NLPlate_HeaderFile
#define _NLPlate_NLPlate_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Handle_Geom_Surface_HeaderFile
#include <Handle_Geom_Surface.hxx>
#endif
#ifndef _NLPlate_SequenceOfHGPPConstraint_HeaderFile
#include <NLPlate_SequenceOfHGPPConstraint.hxx>
#endif
#ifndef _NLPlate_StackOfPlate_HeaderFile
#include <NLPlate_StackOfPlate.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Handle_NLPlate_HGPPConstraint_HeaderFile
#include <Handle_NLPlate_HGPPConstraint.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
class Geom_Surface;
class NLPlate_HGPPConstraint;
class gp_XYZ;
class gp_XY;



//! <br>
//! <br>
class NLPlate_NLPlate  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   NLPlate_NLPlate(const Handle(Geom_Surface)& InitialSurface);
  
  Standard_EXPORT     void Load(const Handle(NLPlate_HGPPConstraint)& GConst) ;
  
  Standard_EXPORT     void Solve(const Standard_Integer ord = 2,const Standard_Integer InitialConsraintOrder = 1) ;
  
  Standard_EXPORT     void Solve2(const Standard_Integer ord = 2,const Standard_Integer InitialConsraintOrder = 1) ;
  
  Standard_EXPORT     void IncrementalSolve(const Standard_Integer ord = 2,const Standard_Integer InitialConsraintOrder = 1,const Standard_Integer NbIncrements = 4,const Standard_Boolean UVSliding = Standard_False) ;
  //! returns True if all has been correctly done. <br>
  Standard_EXPORT     Standard_Boolean IsDone() const;
  
  Standard_EXPORT     void destroy() ;
~NLPlate_NLPlate()
{
  destroy();
}
  //! reset the Plate in the initial state <br>
//!           ( same as after Create((Surface)) <br>
  Standard_EXPORT     void Init() ;
  
  Standard_EXPORT     gp_XYZ Evaluate(const gp_XY& point2d) const;
  
  Standard_EXPORT     gp_XYZ EvaluateDerivative(const gp_XY& point2d,const Standard_Integer iu,const Standard_Integer iv) const;
  
  Standard_EXPORT     Standard_Integer Continuity() const;
  
  Standard_EXPORT     void ConstraintsSliding(const Standard_Integer NbIterations = 3) ;
  
  Standard_EXPORT     Standard_Integer MaxActiveConstraintOrder() const;





protected:





private:

  
  Standard_EXPORT     Standard_Boolean Iterate(const Standard_Integer ConstraintOrder,const Standard_Integer ResolutionOrder,const Standard_Real IncrementalLoading = 1.0) ;


Handle_Geom_Surface myInitialSurface;
NLPlate_SequenceOfHGPPConstraint myHGPPConstraints;
NLPlate_StackOfPlate mySOP;
Standard_Boolean OK;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
