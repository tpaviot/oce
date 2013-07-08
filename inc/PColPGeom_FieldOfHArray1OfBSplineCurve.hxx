// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _PColPGeom_FieldOfHArray1OfBSplineCurve_HeaderFile
#define _PColPGeom_FieldOfHArray1OfBSplineCurve_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _DBC_BaseArray_HeaderFile
#include <DBC_BaseArray.hxx>
#endif
#ifndef _Handle_PGeom_BSplineCurve_HeaderFile
#include <Handle_PGeom_BSplineCurve.hxx>
#endif
#ifndef _Handle_PColPGeom_VArrayNodeOfFieldOfHArray1OfBSplineCurve_HeaderFile
#include <Handle_PColPGeom_VArrayNodeOfFieldOfHArray1OfBSplineCurve.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_PrimitiveTypes_HeaderFile
#include <Standard_PrimitiveTypes.hxx>
#endif
class Standard_NegativeValue;
class Standard_OutOfRange;
class Standard_DimensionMismatch;
class Standard_NullObject;
class PGeom_BSplineCurve;
class PColPGeom_VArrayNodeOfFieldOfHArray1OfBSplineCurve;
class PColPGeom_VArrayTNodeOfFieldOfHArray1OfBSplineCurve;



Standard_EXPORT const Handle(Standard_Type)& STANDARD_TYPE(PColPGeom_FieldOfHArray1OfBSplineCurve);


class PColPGeom_FieldOfHArray1OfBSplineCurve  : public DBC_BaseArray {

public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   PColPGeom_FieldOfHArray1OfBSplineCurve();
  
  Standard_EXPORT   PColPGeom_FieldOfHArray1OfBSplineCurve(const Standard_Integer Size);
  
  Standard_EXPORT   PColPGeom_FieldOfHArray1OfBSplineCurve(const PColPGeom_FieldOfHArray1OfBSplineCurve& Varray);
  
  Standard_EXPORT     void Resize(const Standard_Integer Size) ;
  
  Standard_EXPORT     void Assign(const PColPGeom_FieldOfHArray1OfBSplineCurve& Other) ;
    void operator =(const PColPGeom_FieldOfHArray1OfBSplineCurve& Other) 
{
  Assign(Other);
}
  
  Standard_EXPORT     void SetValue(const Standard_Integer Index,const Handle(PGeom_BSplineCurve)& Value) ;
  
  Standard_EXPORT     Handle_PGeom_BSplineCurve& Value(const Standard_Integer Index) const;
    Handle_PGeom_BSplineCurve& operator ()(const Standard_Integer Index) const
{
  return Value(Index);
}
  
  Standard_EXPORT     void Destroy() ;
~PColPGeom_FieldOfHArray1OfBSplineCurve()
{
  Destroy();
}



protected:




private: 

#ifdef CSFDB
// DBC_VArray : field
//
#endif



};





// other Inline functions and methods (like "C++: function call" methods)


#endif
