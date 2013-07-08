// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TDF_DoubleMapIteratorOfGUIDProgIDMap_HeaderFile
#define _TDF_DoubleMapIteratorOfGUIDProgIDMap_HeaderFile

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
#ifndef _Handle_TDF_DoubleMapNodeOfGUIDProgIDMap_HeaderFile
#include <Handle_TDF_DoubleMapNodeOfGUIDProgIDMap.hxx>
#endif
class Standard_NoSuchObject;
class Standard_GUID;
class TCollection_ExtendedString;
class TDF_GUIDProgIDMap;
class TDF_DoubleMapNodeOfGUIDProgIDMap;



class TDF_DoubleMapIteratorOfGUIDProgIDMap  : public TCollection_BasicMapIterator {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   TDF_DoubleMapIteratorOfGUIDProgIDMap();
  
  Standard_EXPORT   TDF_DoubleMapIteratorOfGUIDProgIDMap(const TDF_GUIDProgIDMap& aMap);
  
  Standard_EXPORT     void Initialize(const TDF_GUIDProgIDMap& aMap) ;
  
  Standard_EXPORT    const Standard_GUID& Key1() const;
  
  Standard_EXPORT    const TCollection_ExtendedString& Key2() const;





protected:





private:





};





// other Inline functions and methods (like "C++: function call" methods)


#endif
