// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _StepToTopoDS_PointVertexMap_HeaderFile
#define _StepToTopoDS_PointVertexMap_HeaderFile

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
#ifndef _Handle_StepGeom_CartesianPoint_HeaderFile
#include <Handle_StepGeom_CartesianPoint.hxx>
#endif
#ifndef _Handle_StepToTopoDS_DataMapNodeOfPointVertexMap_HeaderFile
#include <Handle_StepToTopoDS_DataMapNodeOfPointVertexMap.hxx>
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
class StepGeom_CartesianPoint;
class TopoDS_Vertex;
class StepToTopoDS_CartesianPointHasher;
class StepToTopoDS_DataMapNodeOfPointVertexMap;
class StepToTopoDS_DataMapIteratorOfPointVertexMap;



class StepToTopoDS_PointVertexMap  : public TCollection_BasicMap {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   StepToTopoDS_PointVertexMap(const Standard_Integer NbBuckets = 1);
  
  Standard_EXPORT     StepToTopoDS_PointVertexMap& Assign(const StepToTopoDS_PointVertexMap& Other) ;
    StepToTopoDS_PointVertexMap& operator =(const StepToTopoDS_PointVertexMap& Other) 
{
  return Assign(Other);
}
  
  Standard_EXPORT     void ReSize(const Standard_Integer NbBuckets) ;
  
  Standard_EXPORT     void Clear() ;
~StepToTopoDS_PointVertexMap()
{
  Clear();
}
  
  Standard_EXPORT     Standard_Boolean Bind(const Handle(StepGeom_CartesianPoint)& K,const TopoDS_Vertex& I) ;
  
  Standard_EXPORT     Standard_Boolean IsBound(const Handle(StepGeom_CartesianPoint)& K) const;
  
  Standard_EXPORT     Standard_Boolean UnBind(const Handle(StepGeom_CartesianPoint)& K) ;
  
  Standard_EXPORT    const TopoDS_Vertex& Find(const Handle(StepGeom_CartesianPoint)& K) const;
   const TopoDS_Vertex& operator()(const Handle(StepGeom_CartesianPoint)& K) const
{
  return Find(K);
}
  
  Standard_EXPORT     TopoDS_Vertex& ChangeFind(const Handle(StepGeom_CartesianPoint)& K) ;
    TopoDS_Vertex& operator()(const Handle(StepGeom_CartesianPoint)& K) 
{
  return ChangeFind(K);
}
  
  Standard_EXPORT     Standard_Address Find1(const Handle(StepGeom_CartesianPoint)& K) const;
  
  Standard_EXPORT     Standard_Address ChangeFind1(const Handle(StepGeom_CartesianPoint)& K) ;





protected:





private:

  
  Standard_EXPORT   StepToTopoDS_PointVertexMap(const StepToTopoDS_PointVertexMap& Other);




};





// other Inline functions and methods (like "C++: function call" methods)


#endif
