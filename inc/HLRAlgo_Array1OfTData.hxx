// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _HLRAlgo_Array1OfTData_HeaderFile
#define _HLRAlgo_Array1OfTData_HeaderFile

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
class Standard_RangeError;
class Standard_DimensionMismatch;
class Standard_OutOfRange;
class Standard_OutOfMemory;
class HLRAlgo_TriangleData;



class HLRAlgo_Array1OfTData  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   HLRAlgo_Array1OfTData(const Standard_Integer Low,const Standard_Integer Up);
  
  Standard_EXPORT   HLRAlgo_Array1OfTData(const HLRAlgo_TriangleData& Item,const Standard_Integer Low,const Standard_Integer Up);
  
  Standard_EXPORT     void Init(const HLRAlgo_TriangleData& V) ;
  
  Standard_EXPORT     void Destroy() ;
~HLRAlgo_Array1OfTData()
{
  Destroy();
}
  
        Standard_Boolean IsAllocated() const;
  
  Standard_EXPORT    const HLRAlgo_Array1OfTData& Assign(const HLRAlgo_Array1OfTData& Other) ;
   const HLRAlgo_Array1OfTData& operator =(const HLRAlgo_Array1OfTData& Other) 
{
  return Assign(Other);
}
  
        Standard_Integer Length() const;
  
        Standard_Integer Lower() const;
  
        Standard_Integer Upper() const;
  
        void SetValue(const Standard_Integer Index,const HLRAlgo_TriangleData& Value) ;
  
       const HLRAlgo_TriangleData& Value(const Standard_Integer Index) const;
     const HLRAlgo_TriangleData& operator ()(const Standard_Integer Index) const
{
  return Value(Index);
}
  
        HLRAlgo_TriangleData& ChangeValue(const Standard_Integer Index) ;
      HLRAlgo_TriangleData& operator ()(const Standard_Integer Index) 
{
  return ChangeValue(Index);
}





protected:





private:

  
  Standard_EXPORT   HLRAlgo_Array1OfTData(const HLRAlgo_Array1OfTData& AnArray);


Standard_Integer myLowerBound;
Standard_Integer myUpperBound;
Standard_Address myStart;
Standard_Boolean isAllocated;


};

#define Array1Item HLRAlgo_TriangleData
#define Array1Item_hxx <HLRAlgo_TriangleData.hxx>
#define TCollection_Array1 HLRAlgo_Array1OfTData
#define TCollection_Array1_hxx <HLRAlgo_Array1OfTData.hxx>

#include <TCollection_Array1.lxx>

#undef Array1Item
#undef Array1Item_hxx
#undef TCollection_Array1
#undef TCollection_Array1_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif
