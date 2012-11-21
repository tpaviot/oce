// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _StepToTopoDS_DataMapOfTRI_HeaderFile
#define _StepToTopoDS_DataMapOfTRI_HeaderFile

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
#ifndef _Handle_StepShape_TopologicalRepresentationItem_HeaderFile
#include <Handle_StepShape_TopologicalRepresentationItem.hxx>
#endif
#ifndef _Handle_StepToTopoDS_DataMapNodeOfDataMapOfTRI_HeaderFile
#include <Handle_StepToTopoDS_DataMapNodeOfDataMapOfTRI.hxx>
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
class StepShape_TopologicalRepresentationItem;
class TopoDS_Shape;
class TColStd_MapTransientHasher;
class StepToTopoDS_DataMapNodeOfDataMapOfTRI;
class StepToTopoDS_DataMapIteratorOfDataMapOfTRI;



class StepToTopoDS_DataMapOfTRI  : public TCollection_BasicMap {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   StepToTopoDS_DataMapOfTRI(const Standard_Integer NbBuckets = 1);
  
  Standard_EXPORT     StepToTopoDS_DataMapOfTRI& Assign(const StepToTopoDS_DataMapOfTRI& Other) ;
    StepToTopoDS_DataMapOfTRI& operator =(const StepToTopoDS_DataMapOfTRI& Other) 
{
  return Assign(Other);
}
  
  Standard_EXPORT     void ReSize(const Standard_Integer NbBuckets) ;
  
  Standard_EXPORT     void Clear() ;
~StepToTopoDS_DataMapOfTRI()
{
  Clear();
}
  
  Standard_EXPORT     Standard_Boolean Bind(const Handle(StepShape_TopologicalRepresentationItem)& K,const TopoDS_Shape& I) ;
  
  Standard_EXPORT     Standard_Boolean IsBound(const Handle(StepShape_TopologicalRepresentationItem)& K) const;
  
  Standard_EXPORT     Standard_Boolean UnBind(const Handle(StepShape_TopologicalRepresentationItem)& K) ;
  
  Standard_EXPORT    const TopoDS_Shape& Find(const Handle(StepShape_TopologicalRepresentationItem)& K) const;
   const TopoDS_Shape& operator()(const Handle(StepShape_TopologicalRepresentationItem)& K) const
{
  return Find(K);
}
  
  Standard_EXPORT     TopoDS_Shape& ChangeFind(const Handle(StepShape_TopologicalRepresentationItem)& K) ;
    TopoDS_Shape& operator()(const Handle(StepShape_TopologicalRepresentationItem)& K) 
{
  return ChangeFind(K);
}
  
  Standard_EXPORT     Standard_Address Find1(const Handle(StepShape_TopologicalRepresentationItem)& K) const;
  
  Standard_EXPORT     Standard_Address ChangeFind1(const Handle(StepShape_TopologicalRepresentationItem)& K) ;





protected:





private:

  
  Standard_EXPORT   StepToTopoDS_DataMapOfTRI(const StepToTopoDS_DataMapOfTRI& Other);




};





// other Inline functions and methods (like "C++: function call" methods)


#endif
