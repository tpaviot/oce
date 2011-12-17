// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _BRepMAT2d_DataMapOfBasicEltShape_HeaderFile
#define _BRepMAT2d_DataMapOfBasicEltShape_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _TCollection_BasicMap_HeaderFile
#include <TCollection_BasicMap.hxx>
#endif
#ifndef _Handle_MAT_BasicElt_HeaderFile
#include <Handle_MAT_BasicElt.hxx>
#endif
#ifndef _Handle_BRepMAT2d_DataMapNodeOfDataMapOfBasicEltShape_HeaderFile
#include <Handle_BRepMAT2d_DataMapNodeOfDataMapOfBasicEltShape.hxx>
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
class MAT_BasicElt;
class TopoDS_Shape;
class TColStd_MapTransientHasher;
class BRepMAT2d_DataMapNodeOfDataMapOfBasicEltShape;
class BRepMAT2d_DataMapIteratorOfDataMapOfBasicEltShape;



class BRepMAT2d_DataMapOfBasicEltShape  : public TCollection_BasicMap {
public:

  void* operator new(size_t,void* anAddress) 
  {
    return anAddress;
  }
  void* operator new(size_t size) 
  {
    return Standard::Allocate(size); 
  }
  void  operator delete(void *anAddress) 
  {
    if (anAddress) Standard::Free((Standard_Address&)anAddress); 
  }

  
  Standard_EXPORT   BRepMAT2d_DataMapOfBasicEltShape(const Standard_Integer NbBuckets = 1);
  
  Standard_EXPORT     BRepMAT2d_DataMapOfBasicEltShape& Assign(const BRepMAT2d_DataMapOfBasicEltShape& Other) ;
    BRepMAT2d_DataMapOfBasicEltShape& operator =(const BRepMAT2d_DataMapOfBasicEltShape& Other) 
{
  return Assign(Other);
}
  
  Standard_EXPORT     void ReSize(const Standard_Integer NbBuckets) ;
  
  Standard_EXPORT     void Clear() ;
~BRepMAT2d_DataMapOfBasicEltShape()
{
  Clear();
}
  
  Standard_EXPORT     Standard_Boolean Bind(const Handle(MAT_BasicElt)& K,const TopoDS_Shape& I) ;
  
  Standard_EXPORT     Standard_Boolean IsBound(const Handle(MAT_BasicElt)& K) const;
  
  Standard_EXPORT     Standard_Boolean UnBind(const Handle(MAT_BasicElt)& K) ;
  
  Standard_EXPORT    const TopoDS_Shape& Find(const Handle(MAT_BasicElt)& K) const;
   const TopoDS_Shape& operator()(const Handle(MAT_BasicElt)& K) const
{
  return Find(K);
}
  
  Standard_EXPORT     TopoDS_Shape& ChangeFind(const Handle(MAT_BasicElt)& K) ;
    TopoDS_Shape& operator()(const Handle(MAT_BasicElt)& K) 
{
  return ChangeFind(K);
}
  
  Standard_EXPORT     Standard_Address Find1(const Handle(MAT_BasicElt)& K) const;
  
  Standard_EXPORT     Standard_Address ChangeFind1(const Handle(MAT_BasicElt)& K) ;





protected:





private:

  
  Standard_EXPORT   BRepMAT2d_DataMapOfBasicEltShape(const BRepMAT2d_DataMapOfBasicEltShape& Other);




};





// other Inline functions and methods (like "C++: function call" methods)


#endif
