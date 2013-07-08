// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Extrema_Array2OfPOnCurv2d_HeaderFile
#define _Extrema_Array2OfPOnCurv2d_HeaderFile

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
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Standard_Address_HeaderFile
#include <Standard_Address.hxx>
#endif
class Standard_RangeError;
class Standard_OutOfRange;
class Standard_OutOfMemory;
class Standard_DimensionMismatch;
class Extrema_POnCurv2d;



class Extrema_Array2OfPOnCurv2d  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   Extrema_Array2OfPOnCurv2d(const Standard_Integer R1,const Standard_Integer R2,const Standard_Integer C1,const Standard_Integer C2);
  
  Standard_EXPORT   Extrema_Array2OfPOnCurv2d(const Extrema_POnCurv2d& Item,const Standard_Integer R1,const Standard_Integer R2,const Standard_Integer C1,const Standard_Integer C2);
  
  Standard_EXPORT     void Init(const Extrema_POnCurv2d& V) ;
  
  Standard_EXPORT     void Destroy() ;
~Extrema_Array2OfPOnCurv2d()
{
  Destroy();
}
  
  Standard_EXPORT    const Extrema_Array2OfPOnCurv2d& Assign(const Extrema_Array2OfPOnCurv2d& Other) ;
   const Extrema_Array2OfPOnCurv2d& operator =(const Extrema_Array2OfPOnCurv2d& Other) 
{
  return Assign(Other);
}
  
        Standard_Integer ColLength() const;
  
        Standard_Integer RowLength() const;
  
        Standard_Integer LowerCol() const;
  
        Standard_Integer LowerRow() const;
  
        Standard_Integer UpperCol() const;
  
        Standard_Integer UpperRow() const;
  
        void SetValue(const Standard_Integer Row,const Standard_Integer Col,const Extrema_POnCurv2d& Value) ;
  
       const Extrema_POnCurv2d& Value(const Standard_Integer Row,const Standard_Integer Col) const;
     const Extrema_POnCurv2d& operator()(const Standard_Integer Row,const Standard_Integer Col) const
{
  return Value(Row,Col);
}
  
        Extrema_POnCurv2d& ChangeValue(const Standard_Integer Row,const Standard_Integer Col) ;
      Extrema_POnCurv2d& operator()(const Standard_Integer Row,const Standard_Integer Col) 
{
  return ChangeValue(Row,Col);
}





protected:





private:

  
  Standard_EXPORT   Extrema_Array2OfPOnCurv2d(const Extrema_Array2OfPOnCurv2d& AnArray);
  
  Standard_EXPORT     void Allocate() ;


Standard_Integer myLowerRow;
Standard_Integer myLowerColumn;
Standard_Integer myUpperRow;
Standard_Integer myUpperColumn;
Standard_Boolean myDeletable;
Standard_Address myData;


};

#define Array2Item Extrema_POnCurv2d
#define Array2Item_hxx <Extrema_POnCurv2d.hxx>
#define TCollection_Array2 Extrema_Array2OfPOnCurv2d
#define TCollection_Array2_hxx <Extrema_Array2OfPOnCurv2d.hxx>

#include <TCollection_Array2.lxx>

#undef Array2Item
#undef Array2Item_hxx
#undef TCollection_Array2
#undef TCollection_Array2_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif
