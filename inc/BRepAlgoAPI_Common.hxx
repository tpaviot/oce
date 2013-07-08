// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _BRepAlgoAPI_Common_HeaderFile
#define _BRepAlgoAPI_Common_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _BRepAlgoAPI_BooleanOperation_HeaderFile
#include <BRepAlgoAPI_BooleanOperation.hxx>
#endif
class TopoDS_Shape;
class BOPAlgo_PaveFiller;


//! The class Common provides a <br>
//! Boolean common operation on a pair of arguments (Boolean Intersection). <br>
//!  The class Common provides a framework for: <br>
//! -           Defining the construction of a common shape; <br>
//! -           Implementing the   building algorithm <br>
//! -           Consulting the result. <br>
class BRepAlgoAPI_Common  : public BRepAlgoAPI_BooleanOperation {
public:

  DEFINE_STANDARD_ALLOC

  //! Constructs a common part for shapes aS1 and aS2 . <br>
  Standard_EXPORT   BRepAlgoAPI_Common(const TopoDS_Shape& S1,const TopoDS_Shape& S2);
  
  Standard_EXPORT   BRepAlgoAPI_Common(const TopoDS_Shape& S1,const TopoDS_Shape& S2,const BOPAlgo_PaveFiller& aDSF);





protected:





private:





};





// other Inline functions and methods (like "C++: function call" methods)


#endif
