// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _MAT2d_DataMapIteratorOfDataMapOfIntegerVec2d_HeaderFile
#define _MAT2d_DataMapIteratorOfDataMapOfIntegerVec2d_HeaderFile

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
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Handle_MAT2d_DataMapNodeOfDataMapOfIntegerVec2d_HeaderFile
#include <Handle_MAT2d_DataMapNodeOfDataMapOfIntegerVec2d.hxx>
#endif
class Standard_NoSuchObject;
class gp_Vec2d;
class TColStd_MapIntegerHasher;
class MAT2d_DataMapOfIntegerVec2d;
class MAT2d_DataMapNodeOfDataMapOfIntegerVec2d;



class MAT2d_DataMapIteratorOfDataMapOfIntegerVec2d  : public TCollection_BasicMapIterator {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   MAT2d_DataMapIteratorOfDataMapOfIntegerVec2d();
  
  Standard_EXPORT   MAT2d_DataMapIteratorOfDataMapOfIntegerVec2d(const MAT2d_DataMapOfIntegerVec2d& aMap);
  
  Standard_EXPORT     void Initialize(const MAT2d_DataMapOfIntegerVec2d& aMap) ;
  
  Standard_EXPORT    const Standard_Integer& Key() const;
  
  Standard_EXPORT    const gp_Vec2d& Value() const;





protected:





private:





};





// other Inline functions and methods (like "C++: function call" methods)


#endif
