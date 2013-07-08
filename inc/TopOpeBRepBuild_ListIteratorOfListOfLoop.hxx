// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TopOpeBRepBuild_ListIteratorOfListOfLoop_HeaderFile
#define _TopOpeBRepBuild_ListIteratorOfListOfLoop_HeaderFile

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
#ifndef _Handle_TopOpeBRepBuild_Loop_HeaderFile
#include <Handle_TopOpeBRepBuild_Loop.hxx>
#endif
#ifndef _Handle_TopOpeBRepBuild_ListNodeOfListOfLoop_HeaderFile
#include <Handle_TopOpeBRepBuild_ListNodeOfListOfLoop.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class Standard_NoMoreObject;
class Standard_NoSuchObject;
class TopOpeBRepBuild_ListOfLoop;
class TopOpeBRepBuild_Loop;
class TopOpeBRepBuild_ListNodeOfListOfLoop;



class TopOpeBRepBuild_ListIteratorOfListOfLoop  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   TopOpeBRepBuild_ListIteratorOfListOfLoop();
  
  Standard_EXPORT   TopOpeBRepBuild_ListIteratorOfListOfLoop(const TopOpeBRepBuild_ListOfLoop& L);
  
  Standard_EXPORT     void Initialize(const TopOpeBRepBuild_ListOfLoop& L) ;
  
        Standard_Boolean More() const;
  
  Standard_EXPORT     void Next() ;
  
  Standard_EXPORT     Handle_TopOpeBRepBuild_Loop& Value() const;


friend class TopOpeBRepBuild_ListOfLoop;



protected:





private:



Standard_Address current;
Standard_Address previous;


};

#define Item Handle_TopOpeBRepBuild_Loop
#define Item_hxx <TopOpeBRepBuild_Loop.hxx>
#define TCollection_ListNode TopOpeBRepBuild_ListNodeOfListOfLoop
#define TCollection_ListNode_hxx <TopOpeBRepBuild_ListNodeOfListOfLoop.hxx>
#define TCollection_ListIterator TopOpeBRepBuild_ListIteratorOfListOfLoop
#define TCollection_ListIterator_hxx <TopOpeBRepBuild_ListIteratorOfListOfLoop.hxx>
#define Handle_TCollection_ListNode Handle_TopOpeBRepBuild_ListNodeOfListOfLoop
#define TCollection_ListNode_Type_() TopOpeBRepBuild_ListNodeOfListOfLoop_Type_()
#define TCollection_List TopOpeBRepBuild_ListOfLoop
#define TCollection_List_hxx <TopOpeBRepBuild_ListOfLoop.hxx>

#include <TCollection_ListIterator.lxx>

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
