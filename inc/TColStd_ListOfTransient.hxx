// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TColStd_ListOfTransient_HeaderFile
#define _TColStd_ListOfTransient_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Standard_Address_HeaderFile
#include <Standard_Address.hxx>
#endif
#ifndef _Handle_Standard_Transient_HeaderFile
#include <Handle_Standard_Transient.hxx>
#endif
#ifndef _Handle_TColStd_ListNodeOfListOfTransient_HeaderFile
#include <Handle_TColStd_ListNodeOfListOfTransient.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class Standard_NoSuchObject;
class TColStd_ListIteratorOfListOfTransient;
class Standard_Transient;
class TColStd_ListNodeOfListOfTransient;



class TColStd_ListOfTransient  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   TColStd_ListOfTransient();
  
  Standard_EXPORT     void Assign(const TColStd_ListOfTransient& Other) ;
    void operator=(const TColStd_ListOfTransient& Other) 
{
  Assign(Other);
}
  
  Standard_EXPORT     Standard_Integer Extent() const;
  
  Standard_EXPORT     void Clear() ;
~TColStd_ListOfTransient()
{
  Clear();
}
  
        Standard_Boolean IsEmpty() const;
  
  Standard_EXPORT     void Prepend(const Handle(Standard_Transient)& I) ;
  
  Standard_EXPORT     void Prepend(const Handle(Standard_Transient)& I,TColStd_ListIteratorOfListOfTransient& theIt) ;
  
  Standard_EXPORT     void Prepend(TColStd_ListOfTransient& Other) ;
  
  Standard_EXPORT     void Append(const Handle(Standard_Transient)& I) ;
  
  Standard_EXPORT     void Append(const Handle(Standard_Transient)& I,TColStd_ListIteratorOfListOfTransient& theIt) ;
  
  Standard_EXPORT     void Append(TColStd_ListOfTransient& Other) ;
  
  Standard_EXPORT     Handle_Standard_Transient& First() const;
  
  Standard_EXPORT     Handle_Standard_Transient& Last() const;
  
  Standard_EXPORT     void RemoveFirst() ;
  
  Standard_EXPORT     void Remove(TColStd_ListIteratorOfListOfTransient& It) ;
  
  Standard_EXPORT     void InsertBefore(const Handle(Standard_Transient)& I,TColStd_ListIteratorOfListOfTransient& It) ;
  
  Standard_EXPORT     void InsertBefore(TColStd_ListOfTransient& Other,TColStd_ListIteratorOfListOfTransient& It) ;
  
  Standard_EXPORT     void InsertAfter(const Handle(Standard_Transient)& I,TColStd_ListIteratorOfListOfTransient& It) ;
  
  Standard_EXPORT     void InsertAfter(TColStd_ListOfTransient& Other,TColStd_ListIteratorOfListOfTransient& It) ;


friend class TColStd_ListIteratorOfListOfTransient;



protected:





private:

  
  Standard_EXPORT   TColStd_ListOfTransient(const TColStd_ListOfTransient& Other);


Standard_Address myFirst;
Standard_Address myLast;


};

#define Item Handle_Standard_Transient
#define Item_hxx <Standard_Transient.hxx>
#define TCollection_ListNode TColStd_ListNodeOfListOfTransient
#define TCollection_ListNode_hxx <TColStd_ListNodeOfListOfTransient.hxx>
#define TCollection_ListIterator TColStd_ListIteratorOfListOfTransient
#define TCollection_ListIterator_hxx <TColStd_ListIteratorOfListOfTransient.hxx>
#define Handle_TCollection_ListNode Handle_TColStd_ListNodeOfListOfTransient
#define TCollection_ListNode_Type_() TColStd_ListNodeOfListOfTransient_Type_()
#define TCollection_List TColStd_ListOfTransient
#define TCollection_List_hxx <TColStd_ListOfTransient.hxx>

#include <TCollection_List.lxx>

#undef Item
#undef Item_hxx
#undef TCollection_ListNode
#undef TCollection_ListNode_hxx
#undef TCollection_ListIterator
#undef TCollection_ListIterator_hxx
#undef Handle_TCollection_ListNode
#undef TCollection_ListNode_Type_
#undef TCollection_List
#undef TCollection_List_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif
