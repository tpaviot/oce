// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _BRepBlend_SequenceOfPointOnRst_HeaderFile
#define _BRepBlend_SequenceOfPointOnRst_HeaderFile

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
#ifndef _Handle_BRepBlend_SequenceNodeOfSequenceOfPointOnRst_HeaderFile
#include <Handle_BRepBlend_SequenceNodeOfSequenceOfPointOnRst.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
class Standard_NoSuchObject;
class Standard_OutOfRange;
class BRepBlend_PointOnRst;
class BRepBlend_SequenceNodeOfSequenceOfPointOnRst;



class BRepBlend_SequenceOfPointOnRst  : public TCollection_BaseSequence {
public:

  DEFINE_STANDARD_ALLOC

  
      BRepBlend_SequenceOfPointOnRst();
  
  Standard_EXPORT     void Clear() ;
~BRepBlend_SequenceOfPointOnRst()
{
  Clear();
}
  
  Standard_EXPORT    const BRepBlend_SequenceOfPointOnRst& Assign(const BRepBlend_SequenceOfPointOnRst& Other) ;
   const BRepBlend_SequenceOfPointOnRst& operator =(const BRepBlend_SequenceOfPointOnRst& Other) 
{
  return Assign(Other);
}
  
  Standard_EXPORT     void Append(const BRepBlend_PointOnRst& T) ;
  
        void Append(BRepBlend_SequenceOfPointOnRst& S) ;
  
  Standard_EXPORT     void Prepend(const BRepBlend_PointOnRst& T) ;
  
        void Prepend(BRepBlend_SequenceOfPointOnRst& S) ;
  
        void InsertBefore(const Standard_Integer Index,const BRepBlend_PointOnRst& T) ;
  
        void InsertBefore(const Standard_Integer Index,BRepBlend_SequenceOfPointOnRst& S) ;
  
  Standard_EXPORT     void InsertAfter(const Standard_Integer Index,const BRepBlend_PointOnRst& T) ;
  
        void InsertAfter(const Standard_Integer Index,BRepBlend_SequenceOfPointOnRst& S) ;
  
  Standard_EXPORT    const BRepBlend_PointOnRst& First() const;
  
  Standard_EXPORT    const BRepBlend_PointOnRst& Last() const;
  
        void Split(const Standard_Integer Index,BRepBlend_SequenceOfPointOnRst& Sub) ;
  
  Standard_EXPORT    const BRepBlend_PointOnRst& Value(const Standard_Integer Index) const;
   const BRepBlend_PointOnRst& operator()(const Standard_Integer Index) const
{
  return Value(Index);
}
  
  Standard_EXPORT     void SetValue(const Standard_Integer Index,const BRepBlend_PointOnRst& I) ;
  
  Standard_EXPORT     BRepBlend_PointOnRst& ChangeValue(const Standard_Integer Index) ;
    BRepBlend_PointOnRst& operator()(const Standard_Integer Index) 
{
  return ChangeValue(Index);
}
  
  Standard_EXPORT     void Remove(const Standard_Integer Index) ;
  
  Standard_EXPORT     void Remove(const Standard_Integer FromIndex,const Standard_Integer ToIndex) ;





protected:





private:

  
  Standard_EXPORT   BRepBlend_SequenceOfPointOnRst(const BRepBlend_SequenceOfPointOnRst& Other);




};

#define SeqItem BRepBlend_PointOnRst
#define SeqItem_hxx <BRepBlend_PointOnRst.hxx>
#define TCollection_SequenceNode BRepBlend_SequenceNodeOfSequenceOfPointOnRst
#define TCollection_SequenceNode_hxx <BRepBlend_SequenceNodeOfSequenceOfPointOnRst.hxx>
#define Handle_TCollection_SequenceNode Handle_BRepBlend_SequenceNodeOfSequenceOfPointOnRst
#define TCollection_SequenceNode_Type_() BRepBlend_SequenceNodeOfSequenceOfPointOnRst_Type_()
#define TCollection_Sequence BRepBlend_SequenceOfPointOnRst
#define TCollection_Sequence_hxx <BRepBlend_SequenceOfPointOnRst.hxx>

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
