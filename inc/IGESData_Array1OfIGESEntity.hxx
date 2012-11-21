// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _IGESData_Array1OfIGESEntity_HeaderFile
#define _IGESData_Array1OfIGESEntity_HeaderFile

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
#ifndef _Standard_Address_HeaderFile
#include <Standard_Address.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Handle_IGESData_IGESEntity_HeaderFile
#include <Handle_IGESData_IGESEntity.hxx>
#endif
class Standard_RangeError;
class Standard_DimensionMismatch;
class Standard_OutOfRange;
class Standard_OutOfMemory;
class IGESData_IGESEntity;



class IGESData_Array1OfIGESEntity  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   IGESData_Array1OfIGESEntity(const Standard_Integer Low,const Standard_Integer Up);
  
  Standard_EXPORT   IGESData_Array1OfIGESEntity(const Handle(IGESData_IGESEntity)& Item,const Standard_Integer Low,const Standard_Integer Up);
  
  Standard_EXPORT     void Init(const Handle(IGESData_IGESEntity)& V) ;
  
  Standard_EXPORT     void Destroy() ;
~IGESData_Array1OfIGESEntity()
{
  Destroy();
}
  
        Standard_Boolean IsAllocated() const;
  
  Standard_EXPORT    const IGESData_Array1OfIGESEntity& Assign(const IGESData_Array1OfIGESEntity& Other) ;
   const IGESData_Array1OfIGESEntity& operator =(const IGESData_Array1OfIGESEntity& Other) 
{
  return Assign(Other);
}
  
        Standard_Integer Length() const;
  
        Standard_Integer Lower() const;
  
        Standard_Integer Upper() const;
  
        void SetValue(const Standard_Integer Index,const Handle(IGESData_IGESEntity)& Value) ;
  
       const Handle_IGESData_IGESEntity& Value(const Standard_Integer Index) const;
     const Handle_IGESData_IGESEntity& operator ()(const Standard_Integer Index) const
{
  return Value(Index);
}
  
        Handle_IGESData_IGESEntity& ChangeValue(const Standard_Integer Index) ;
      Handle_IGESData_IGESEntity& operator ()(const Standard_Integer Index) 
{
  return ChangeValue(Index);
}





protected:





private:

  
  Standard_EXPORT   IGESData_Array1OfIGESEntity(const IGESData_Array1OfIGESEntity& AnArray);


Standard_Integer myLowerBound;
Standard_Integer myUpperBound;
Standard_Address myStart;
Standard_Boolean isAllocated;


};

#define Array1Item Handle_IGESData_IGESEntity
#define Array1Item_hxx <IGESData_IGESEntity.hxx>
#define TCollection_Array1 IGESData_Array1OfIGESEntity
#define TCollection_Array1_hxx <IGESData_Array1OfIGESEntity.hxx>

#include <TCollection_Array1.lxx>

#undef Array1Item
#undef Array1Item_hxx
#undef TCollection_Array1
#undef TCollection_Array1_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif
