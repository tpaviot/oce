// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Units_QtsSequence_HeaderFile
#define _Units_QtsSequence_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _TCollection_BaseSequence_HeaderFile
#include <TCollection_BaseSequence.hxx>
#endif
#ifndef _Handle_Units_Quantity_HeaderFile
#include <Handle_Units_Quantity.hxx>
#endif
#ifndef _Handle_Units_SequenceNodeOfQtsSequence_HeaderFile
#include <Handle_Units_SequenceNodeOfQtsSequence.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
class Standard_NoSuchObject;
class Standard_OutOfRange;
class Units_Quantity;
class Units_SequenceNodeOfQtsSequence;



class Units_QtsSequence  : public TCollection_BaseSequence {
public:

  DEFINE_STANDARD_ALLOC

  
      Units_QtsSequence();
  
  Standard_EXPORT     void Clear() ;
~Units_QtsSequence()
{
  Clear();
}
  
  Standard_EXPORT    const Units_QtsSequence& Assign(const Units_QtsSequence& Other) ;
   const Units_QtsSequence& operator =(const Units_QtsSequence& Other) 
{
  return Assign(Other);
}
  
  Standard_EXPORT     void Append(const Handle(Units_Quantity)& T) ;
  
        void Append(Units_QtsSequence& S) ;
  
  Standard_EXPORT     void Prepend(const Handle(Units_Quantity)& T) ;
  
        void Prepend(Units_QtsSequence& S) ;
  
        void InsertBefore(const Standard_Integer Index,const Handle(Units_Quantity)& T) ;
  
        void InsertBefore(const Standard_Integer Index,Units_QtsSequence& S) ;
  
  Standard_EXPORT     void InsertAfter(const Standard_Integer Index,const Handle(Units_Quantity)& T) ;
  
        void InsertAfter(const Standard_Integer Index,Units_QtsSequence& S) ;
  
  Standard_EXPORT    const Handle_Units_Quantity& First() const;
  
  Standard_EXPORT    const Handle_Units_Quantity& Last() const;
  
        void Split(const Standard_Integer Index,Units_QtsSequence& Sub) ;
  
  Standard_EXPORT    const Handle_Units_Quantity& Value(const Standard_Integer Index) const;
   const Handle_Units_Quantity& operator()(const Standard_Integer Index) const
{
  return Value(Index);
}
  
  Standard_EXPORT     void SetValue(const Standard_Integer Index,const Handle(Units_Quantity)& I) ;
  
  Standard_EXPORT     Handle_Units_Quantity& ChangeValue(const Standard_Integer Index) ;
    Handle_Units_Quantity& operator()(const Standard_Integer Index) 
{
  return ChangeValue(Index);
}
  
  Standard_EXPORT     void Remove(const Standard_Integer Index) ;
  
  Standard_EXPORT     void Remove(const Standard_Integer FromIndex,const Standard_Integer ToIndex) ;





protected:





private:

  
  Standard_EXPORT   Units_QtsSequence(const Units_QtsSequence& Other);




};

#define SeqItem Handle_Units_Quantity
#define SeqItem_hxx <Units_Quantity.hxx>
#define TCollection_SequenceNode Units_SequenceNodeOfQtsSequence
#define TCollection_SequenceNode_hxx <Units_SequenceNodeOfQtsSequence.hxx>
#define Handle_TCollection_SequenceNode Handle_Units_SequenceNodeOfQtsSequence
#define TCollection_SequenceNode_Type_() Units_SequenceNodeOfQtsSequence_Type_()
#define TCollection_Sequence Units_QtsSequence
#define TCollection_Sequence_hxx <Units_QtsSequence.hxx>

#include <TCollection_Sequence.lxx>

#undef SeqItem
#undef SeqItem_hxx
#undef TCollection_SequenceNode
#undef TCollection_SequenceNode_hxx
#undef Handle_TCollection_SequenceNode
#undef TCollection_SequenceNode_Type_
#undef TCollection_Sequence
#undef TCollection_Sequence_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif
