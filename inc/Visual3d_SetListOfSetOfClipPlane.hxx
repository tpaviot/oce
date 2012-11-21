// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Visual3d_SetListOfSetOfClipPlane_HeaderFile
#define _Visual3d_SetListOfSetOfClipPlane_HeaderFile

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
#ifndef _Handle_Visual3d_ClipPlane_HeaderFile
#include <Handle_Visual3d_ClipPlane.hxx>
#endif
#ifndef _Handle_Visual3d_ListNodeOfSetListOfSetOfClipPlane_HeaderFile
#include <Handle_Visual3d_ListNodeOfSetListOfSetOfClipPlane.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class Standard_NoSuchObject;
class Visual3d_ListIteratorOfSetListOfSetOfClipPlane;
class Visual3d_ClipPlane;
class Visual3d_ListNodeOfSetListOfSetOfClipPlane;



class Visual3d_SetListOfSetOfClipPlane  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   Visual3d_SetListOfSetOfClipPlane();
  
  Standard_EXPORT     void Assign(const Visual3d_SetListOfSetOfClipPlane& Other) ;
    void operator=(const Visual3d_SetListOfSetOfClipPlane& Other) 
{
  Assign(Other);
}
  
  Standard_EXPORT     Standard_Integer Extent() const;
  
  Standard_EXPORT     void Clear() ;
~Visual3d_SetListOfSetOfClipPlane()
{
  Clear();
}
  
        Standard_Boolean IsEmpty() const;
  
  Standard_EXPORT     void Prepend(const Handle(Visual3d_ClipPlane)& I) ;
  
  Standard_EXPORT     void Prepend(const Handle(Visual3d_ClipPlane)& I,Visual3d_ListIteratorOfSetListOfSetOfClipPlane& theIt) ;
  
  Standard_EXPORT     void Prepend(Visual3d_SetListOfSetOfClipPlane& Other) ;
  
  Standard_EXPORT     void Append(const Handle(Visual3d_ClipPlane)& I) ;
  
  Standard_EXPORT     void Append(const Handle(Visual3d_ClipPlane)& I,Visual3d_ListIteratorOfSetListOfSetOfClipPlane& theIt) ;
  
  Standard_EXPORT     void Append(Visual3d_SetListOfSetOfClipPlane& Other) ;
  
  Standard_EXPORT     Handle_Visual3d_ClipPlane& First() const;
  
  Standard_EXPORT     Handle_Visual3d_ClipPlane& Last() const;
  
  Standard_EXPORT     void RemoveFirst() ;
  
  Standard_EXPORT     void Remove(Visual3d_ListIteratorOfSetListOfSetOfClipPlane& It) ;
  
  Standard_EXPORT     void InsertBefore(const Handle(Visual3d_ClipPlane)& I,Visual3d_ListIteratorOfSetListOfSetOfClipPlane& It) ;
  
  Standard_EXPORT     void InsertBefore(Visual3d_SetListOfSetOfClipPlane& Other,Visual3d_ListIteratorOfSetListOfSetOfClipPlane& It) ;
  
  Standard_EXPORT     void InsertAfter(const Handle(Visual3d_ClipPlane)& I,Visual3d_ListIteratorOfSetListOfSetOfClipPlane& It) ;
  
  Standard_EXPORT     void InsertAfter(Visual3d_SetListOfSetOfClipPlane& Other,Visual3d_ListIteratorOfSetListOfSetOfClipPlane& It) ;


friend class Visual3d_ListIteratorOfSetListOfSetOfClipPlane;



protected:





private:

  
  Standard_EXPORT   Visual3d_SetListOfSetOfClipPlane(const Visual3d_SetListOfSetOfClipPlane& Other);


Standard_Address myFirst;
Standard_Address myLast;


};

#define Item Handle_Visual3d_ClipPlane
#define Item_hxx <Visual3d_ClipPlane.hxx>
#define TCollection_ListNode Visual3d_ListNodeOfSetListOfSetOfClipPlane
#define TCollection_ListNode_hxx <Visual3d_ListNodeOfSetListOfSetOfClipPlane.hxx>
#define TCollection_ListIterator Visual3d_ListIteratorOfSetListOfSetOfClipPlane
#define TCollection_ListIterator_hxx <Visual3d_ListIteratorOfSetListOfSetOfClipPlane.hxx>
#define Handle_TCollection_ListNode Handle_Visual3d_ListNodeOfSetListOfSetOfClipPlane
#define TCollection_ListNode_Type_() Visual3d_ListNodeOfSetListOfSetOfClipPlane_Type_()
#define TCollection_List Visual3d_SetListOfSetOfClipPlane
#define TCollection_List_hxx <Visual3d_SetListOfSetOfClipPlane.hxx>

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
