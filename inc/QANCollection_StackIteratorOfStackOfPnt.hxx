// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _QANCollection_StackIteratorOfStackOfPnt_HeaderFile
#define _QANCollection_StackIteratorOfStackOfPnt_HeaderFile

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
#ifndef _Handle_QANCollection_StackNodeOfStackOfPnt_HeaderFile
#include <Handle_QANCollection_StackNodeOfStackOfPnt.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class Standard_NoSuchObject;
class gp_Pnt;
class QANCollection_StackOfPnt;
class QANCollection_StackNodeOfStackOfPnt;



class QANCollection_StackIteratorOfStackOfPnt  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   QANCollection_StackIteratorOfStackOfPnt();
  
  Standard_EXPORT   QANCollection_StackIteratorOfStackOfPnt(const QANCollection_StackOfPnt& S);
  
  Standard_EXPORT     void Initialize(const QANCollection_StackOfPnt& S) ;
  
        Standard_Boolean More() const;
  
  Standard_EXPORT     void Next() ;
  
  Standard_EXPORT    const gp_Pnt& Value() const;





protected:





private:



Standard_Address current;


};

#define Item gp_Pnt
#define Item_hxx <gp_Pnt.hxx>
#define TCollection_StackNode QANCollection_StackNodeOfStackOfPnt
#define TCollection_StackNode_hxx <QANCollection_StackNodeOfStackOfPnt.hxx>
#define TCollection_StackIterator QANCollection_StackIteratorOfStackOfPnt
#define TCollection_StackIterator_hxx <QANCollection_StackIteratorOfStackOfPnt.hxx>
#define Handle_TCollection_StackNode Handle_QANCollection_StackNodeOfStackOfPnt
#define TCollection_StackNode_Type_() QANCollection_StackNodeOfStackOfPnt_Type_()
#define TCollection_Stack QANCollection_StackOfPnt
#define TCollection_Stack_hxx <QANCollection_StackOfPnt.hxx>

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
