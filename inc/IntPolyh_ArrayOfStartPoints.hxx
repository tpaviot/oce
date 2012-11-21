// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _IntPolyh_ArrayOfStartPoints_HeaderFile
#define _IntPolyh_ArrayOfStartPoints_HeaderFile

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
class IntPolyh_StartPoint;



class IntPolyh_ArrayOfStartPoints  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   IntPolyh_ArrayOfStartPoints();
  
  Standard_EXPORT   IntPolyh_ArrayOfStartPoints(const Standard_Integer nn);
  
  Standard_EXPORT     void Init(const Standard_Integer nn) ;
  
  Standard_EXPORT    const IntPolyh_StartPoint& Value(const Standard_Integer nn) const;
   const IntPolyh_StartPoint& operator [](const Standard_Integer nn) const
{
  return Value(nn);
}
  
  Standard_EXPORT     IntPolyh_StartPoint& ChangeValue(const Standard_Integer nn) ;
    IntPolyh_StartPoint& operator [](const Standard_Integer nn) 
{
  return ChangeValue(nn);
}
  
  Standard_EXPORT     IntPolyh_ArrayOfStartPoints& Copy(const IntPolyh_ArrayOfStartPoints& Other) ;
    IntPolyh_ArrayOfStartPoints& operator =(const IntPolyh_ArrayOfStartPoints& Other) 
{
  return Copy(Other);
}
  
  Standard_EXPORT     Standard_Integer NbPoints() const;
  
  Standard_EXPORT     void Destroy() ;
~IntPolyh_ArrayOfStartPoints()
{
  Destroy();
}
  
  Standard_EXPORT     void Dump() const;





protected:





private:



Standard_Integer n;
Standard_Address ptr;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
