// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _BOP_WireShape_HeaderFile
#define _BOP_WireShape_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _TopTools_ListOfShape_HeaderFile
#include <TopTools_ListOfShape.hxx>
#endif
#ifndef _BOP_Builder_HeaderFile
#include <BOP_Builder.hxx>
#endif



//!  The Root class to perform a Boolean Operations (BO) <br>
//!  Common,Cut,Fuse  between arguments when one of them is <br>
//!  a wire <br>
class BOP_WireShape  : public BOP_Builder {
public:

  DEFINE_STANDARD_ALLOC

  
//! Empty constructor; <br>
  Standard_EXPORT   BOP_WireShape();
  
  Standard_EXPORT     void AddSplitPartsINOUT() ;
  
  Standard_EXPORT     void AddSplitPartsON() ;
  
//! Constructs the result of the BO <br>
  Standard_EXPORT     void MakeResult() ;





protected:



TopTools_ListOfShape myLS;


private:





};





// other Inline functions and methods (like "C++: function call" methods)


#endif
