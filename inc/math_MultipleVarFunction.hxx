// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _math_MultipleVarFunction_HeaderFile
#define _math_MultipleVarFunction_HeaderFile

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
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
class math_Vector;



//! Describes the virtual functions associated with a multiple variable function. <br>
class math_MultipleVarFunction  {
public:

  DEFINE_STANDARD_ALLOC

  
//! Returns the number of variables of the function <br>
  Standard_EXPORT   virtual  Standard_Integer NbVariables() const = 0;
  //! Computes the values of the Functions <F> for the <br>
//!          variable <X>. <br>
//!          returns True if the computation was done successfully, <br>
//!      otherwise false. <br>
  Standard_EXPORT   virtual  Standard_Boolean Value(const math_Vector& X,Standard_Real& F)  = 0;
  //! return the state of the function corresponding to the latestt <br>
//!          call of any methods associated to the function. This <br>
//!          function is called by each of the algorithms described <br>
//!          later which define the function Integer <br>
//!          Algorithm::StateNumber(). The algorithm has the <br>
//!          responsibility to call this function when it has found <br>
//!          a solution (i.e. a root or a minimum) and has to maintain <br>
//!          the association between the solution found and this <br>
//!          StateNumber. <br>
//!          Byu default, this method returns 0 (which means for the <br>
//!          algorithm: no state has been saved). It is the <br>
//!          responsibility of the programmer to decide if he needs <br>
//!          to save the current state of the function and to return <br>
//!          an Integer that allows retrieval of the state. <br>
  Standard_EXPORT   virtual  Standard_Integer GetStateNumber() ;





protected:





private:





};





// other Inline functions and methods (like "C++: function call" methods)


#endif
