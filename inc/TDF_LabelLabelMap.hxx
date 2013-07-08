// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TDF_LabelLabelMap_HeaderFile
#define _TDF_LabelLabelMap_HeaderFile

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
#ifndef _Handle_TDF_DataMapNodeOfLabelLabelMap_HeaderFile
#include <Handle_TDF_DataMapNodeOfLabelLabelMap.hxx>
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
class TDF_Label;
class TDF_LabelMapHasher;
class TDF_DataMapNodeOfLabelLabelMap;
class TDF_DataMapIteratorOfLabelLabelMap;



class TDF_LabelLabelMap  : public TCollection_BasicMap {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   TDF_LabelLabelMap(const Standard_Integer NbBuckets = 1);
  
  Standard_EXPORT     TDF_LabelLabelMap& Assign(const TDF_LabelLabelMap& Other) ;
    TDF_LabelLabelMap& operator =(const TDF_LabelLabelMap& Other) 
{
  return Assign(Other);
}
  
  Standard_EXPORT     void ReSize(const Standard_Integer NbBuckets) ;
  
  Standard_EXPORT     void Clear() ;
~TDF_LabelLabelMap()
{
  Clear();
}
  
  Standard_EXPORT     Standard_Boolean Bind(const TDF_Label& K,const TDF_Label& I) ;
  
  Standard_EXPORT     Standard_Boolean IsBound(const TDF_Label& K) const;
  
  Standard_EXPORT     Standard_Boolean UnBind(const TDF_Label& K) ;
  
  Standard_EXPORT    const TDF_Label& Find(const TDF_Label& K) const;
   const TDF_Label& operator()(const TDF_Label& K) const
{
  return Find(K);
}
  
  Standard_EXPORT     TDF_Label& ChangeFind(const TDF_Label& K) ;
    TDF_Label& operator()(const TDF_Label& K) 
{
  return ChangeFind(K);
}
  
  Standard_EXPORT     Standard_Address Find1(const TDF_Label& K) const;
  
  Standard_EXPORT     Standard_Address ChangeFind1(const TDF_Label& K) ;





protected:





private:

  
  Standard_EXPORT   TDF_LabelLabelMap(const TDF_LabelLabelMap& Other);




};





// other Inline functions and methods (like "C++: function call" methods)


#endif
