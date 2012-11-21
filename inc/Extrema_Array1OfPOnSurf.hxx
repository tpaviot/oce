// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Extrema_Array1OfPOnSurf_HeaderFile
#define _Extrema_Array1OfPOnSurf_HeaderFile

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
class Extrema_POnSurf;



class Extrema_Array1OfPOnSurf  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   Extrema_Array1OfPOnSurf(const Standard_Integer Low,const Standard_Integer Up);
  
  Standard_EXPORT   Extrema_Array1OfPOnSurf(const Extrema_POnSurf& Item,const Standard_Integer Low,const Standard_Integer Up);
  
  Standard_EXPORT     void Init(const Extrema_POnSurf& V) ;
  
  Standard_EXPORT     void Destroy() ;
~Extrema_Array1OfPOnSurf()
{
  Destroy();
}
  
        Standard_Boolean IsAllocated() const;
  
  Standard_EXPORT    const Extrema_Array1OfPOnSurf& Assign(const Extrema_Array1OfPOnSurf& Other) ;
   const Extrema_Array1OfPOnSurf& operator =(const Extrema_Array1OfPOnSurf& Other) 
{
  return Assign(Other);
}
  
        Standard_Integer Length() const;
  
        Standard_Integer Lower() const;
  
        Standard_Integer Upper() const;
  
        void SetValue(const Standard_Integer Index,const Extrema_POnSurf& Value) ;
  
       const Extrema_POnSurf& Value(const Standard_Integer Index) const;
     const Extrema_POnSurf& operator ()(const Standard_Integer Index) const
{
  return Value(Index);
}
  
        Extrema_POnSurf& ChangeValue(const Standard_Integer Index) ;
      Extrema_POnSurf& operator ()(const Standard_Integer Index) 
{
  return ChangeValue(Index);
}





protected:





private:

  
  Standard_EXPORT   Extrema_Array1OfPOnSurf(const Extrema_Array1OfPOnSurf& AnArray);


Standard_Integer myLowerBound;
Standard_Integer myUpperBound;
Standard_Address myStart;
Standard_Boolean isAllocated;


};

#define Array1Item Extrema_POnSurf
#define Array1Item_hxx <Extrema_POnSurf.hxx>
#define TCollection_Array1 Extrema_Array1OfPOnSurf
#define TCollection_Array1_hxx <Extrema_Array1OfPOnSurf.hxx>

#include <TCollection_Array1.lxx>

#undef Array1Item
#undef Array1Item_hxx
#undef TCollection_Array1
#undef TCollection_Array1_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif
