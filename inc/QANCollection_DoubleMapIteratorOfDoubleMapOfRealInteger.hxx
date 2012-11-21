// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _QANCollection_DoubleMapIteratorOfDoubleMapOfRealInteger_HeaderFile
#define _QANCollection_DoubleMapIteratorOfDoubleMapOfRealInteger_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _TCollection_BasicMapIterator_HeaderFile
#include <TCollection_BasicMapIterator.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Handle_QANCollection_DoubleMapNodeOfDoubleMapOfRealInteger_HeaderFile
#include <Handle_QANCollection_DoubleMapNodeOfDoubleMapOfRealInteger.hxx>
#endif
class Standard_NoSuchObject;
class TColStd_MapRealHasher;
class TColStd_MapIntegerHasher;
class QANCollection_DoubleMapOfRealInteger;
class QANCollection_DoubleMapNodeOfDoubleMapOfRealInteger;



class QANCollection_DoubleMapIteratorOfDoubleMapOfRealInteger  : public TCollection_BasicMapIterator {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   QANCollection_DoubleMapIteratorOfDoubleMapOfRealInteger();
  
  Standard_EXPORT   QANCollection_DoubleMapIteratorOfDoubleMapOfRealInteger(const QANCollection_DoubleMapOfRealInteger& aMap);
  
  Standard_EXPORT     void Initialize(const QANCollection_DoubleMapOfRealInteger& aMap) ;
  
  Standard_EXPORT    const Standard_Real& Key1() const;
  
  Standard_EXPORT    const Standard_Integer& Key2() const;





protected:





private:





};





// other Inline functions and methods (like "C++: function call" methods)


#endif
