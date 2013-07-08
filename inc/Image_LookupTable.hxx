// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Image_LookupTable_HeaderFile
#define _Image_LookupTable_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _TCollection_BasicMap_HeaderFile
#include <TCollection_BasicMap.hxx>
#endif
#ifndef _Handle_Image_DataMapNodeOfLookupTable_HeaderFile
#include <Handle_Image_DataMapNodeOfLookupTable.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Standard_Address_HeaderFile
#include <Standard_Address.hxx>
#endif
class Standard_DomainError;
class Standard_NoSuchObject;
class Aspect_IndexPixel;
class Image_IndexPixelMapHasher;
class Image_DataMapNodeOfLookupTable;
class Image_DataMapIteratorOfLookupTable;



class Image_LookupTable  : public TCollection_BasicMap {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   Image_LookupTable(const Standard_Integer NbBuckets = 1);
  
  Standard_EXPORT     Image_LookupTable& Assign(const Image_LookupTable& Other) ;
    Image_LookupTable& operator =(const Image_LookupTable& Other) 
{
  return Assign(Other);
}
  
  Standard_EXPORT     void ReSize(const Standard_Integer NbBuckets) ;
  
  Standard_EXPORT     void Clear() ;
~Image_LookupTable()
{
  Clear();
}
  
  Standard_EXPORT     Standard_Boolean Bind(const Aspect_IndexPixel& K,const Aspect_IndexPixel& I) ;
  
  Standard_EXPORT     Standard_Boolean IsBound(const Aspect_IndexPixel& K) const;
  
  Standard_EXPORT     Standard_Boolean UnBind(const Aspect_IndexPixel& K) ;
  
  Standard_EXPORT    const Aspect_IndexPixel& Find(const Aspect_IndexPixel& K) const;
   const Aspect_IndexPixel& operator()(const Aspect_IndexPixel& K) const
{
  return Find(K);
}
  
  Standard_EXPORT     Aspect_IndexPixel& ChangeFind(const Aspect_IndexPixel& K) ;
    Aspect_IndexPixel& operator()(const Aspect_IndexPixel& K) 
{
  return ChangeFind(K);
}
  
  Standard_EXPORT     Standard_Address Find1(const Aspect_IndexPixel& K) const;
  
  Standard_EXPORT     Standard_Address ChangeFind1(const Aspect_IndexPixel& K) ;





protected:





private:

  
  Standard_EXPORT   Image_LookupTable(const Image_LookupTable& Other);




};





// other Inline functions and methods (like "C++: function call" methods)


#endif
