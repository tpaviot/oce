// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _WNT_FontTable_HeaderFile
#define _WNT_FontTable_HeaderFile

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
#ifndef _Handle_WNT_FontMapEntry_HeaderFile
#include <Handle_WNT_FontMapEntry.hxx>
#endif
class Standard_RangeError;
class Standard_DimensionMismatch;
class Standard_OutOfRange;
class Standard_OutOfMemory;
class WNT_FontMapEntry;



class WNT_FontTable  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   WNT_FontTable(const Standard_Integer Low,const Standard_Integer Up);
  
  Standard_EXPORT   WNT_FontTable(const Handle(WNT_FontMapEntry)& Item,const Standard_Integer Low,const Standard_Integer Up);
  
  Standard_EXPORT     void Init(const Handle(WNT_FontMapEntry)& V) ;
  
  Standard_EXPORT     void Destroy() ;
~WNT_FontTable()
{
  Destroy();
}
  
        Standard_Boolean IsAllocated() const;
  
  Standard_EXPORT    const WNT_FontTable& Assign(const WNT_FontTable& Other) ;
   const WNT_FontTable& operator =(const WNT_FontTable& Other) 
{
  return Assign(Other);
}
  
        Standard_Integer Length() const;
  
        Standard_Integer Lower() const;
  
        Standard_Integer Upper() const;
  
        void SetValue(const Standard_Integer Index,const Handle(WNT_FontMapEntry)& Value) ;
  
       const Handle_WNT_FontMapEntry& Value(const Standard_Integer Index) const;
     const Handle_WNT_FontMapEntry& operator ()(const Standard_Integer Index) const
{
  return Value(Index);
}
  
        Handle_WNT_FontMapEntry& ChangeValue(const Standard_Integer Index) ;
      Handle_WNT_FontMapEntry& operator ()(const Standard_Integer Index) 
{
  return ChangeValue(Index);
}





protected:





private:

  
  Standard_EXPORT   WNT_FontTable(const WNT_FontTable& AnArray);


Standard_Integer myLowerBound;
Standard_Integer myUpperBound;
Standard_Address myStart;
Standard_Boolean isAllocated;


};

#define Array1Item Handle_WNT_FontMapEntry
#define Array1Item_hxx <WNT_FontMapEntry.hxx>
#define TCollection_Array1 WNT_FontTable
#define TCollection_Array1_hxx <WNT_FontTable.hxx>

#include <TCollection_Array1.lxx>

#undef Array1Item
#undef Array1Item_hxx
#undef TCollection_Array1
#undef TCollection_Array1_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif
