// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TColStd_StackIteratorOfStackOfReal_HeaderFile
#define _TColStd_StackIteratorOfStackOfReal_HeaderFile

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
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Handle_TColStd_StackNodeOfStackOfReal_HeaderFile
#include <Handle_TColStd_StackNodeOfStackOfReal.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class Standard_NoSuchObject;
class TColStd_StackOfReal;
class TColStd_StackNodeOfStackOfReal;



class TColStd_StackIteratorOfStackOfReal  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   TColStd_StackIteratorOfStackOfReal();
  
  Standard_EXPORT   TColStd_StackIteratorOfStackOfReal(const TColStd_StackOfReal& S);
  
  Standard_EXPORT     void Initialize(const TColStd_StackOfReal& S) ;
  
        Standard_Boolean More() const;
  
  Standard_EXPORT     void Next() ;
  
  Standard_EXPORT    const Standard_Real& Value() const;





protected:





private:



Standard_Address current;


};

#define Item Standard_Real
#define Item_hxx <Standard_Real.hxx>
#define TCollection_StackNode TColStd_StackNodeOfStackOfReal
#define TCollection_StackNode_hxx <TColStd_StackNodeOfStackOfReal.hxx>
#define TCollection_StackIterator TColStd_StackIteratorOfStackOfReal
#define TCollection_StackIterator_hxx <TColStd_StackIteratorOfStackOfReal.hxx>
#define Handle_TCollection_StackNode Handle_TColStd_StackNodeOfStackOfReal
#define TCollection_StackNode_Type_() TColStd_StackNodeOfStackOfReal_Type_()
#define TCollection_Stack TColStd_StackOfReal
#define TCollection_Stack_hxx <TColStd_StackOfReal.hxx>

#include <TCollection_StackIterator.lxx>

#undef Item
#undef Item_hxx
#undef TCollection_StackNode
#undef TCollection_StackNode_hxx
#undef TCollection_StackIterator
#undef TCollection_StackIterator_hxx
#undef Handle_TCollection_StackNode
#undef TCollection_StackNode_Type_
#undef TCollection_Stack
#undef TCollection_Stack_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif
