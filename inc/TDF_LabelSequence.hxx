// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TDF_LabelSequence_HeaderFile
#define _TDF_LabelSequence_HeaderFile

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
#ifndef _Handle_TDF_SequenceNodeOfLabelSequence_HeaderFile
#include <Handle_TDF_SequenceNodeOfLabelSequence.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
class Standard_NoSuchObject;
class Standard_OutOfRange;
class TDF_Label;
class TDF_SequenceNodeOfLabelSequence;



class TDF_LabelSequence  : public TCollection_BaseSequence {
public:

  DEFINE_STANDARD_ALLOC

  
      TDF_LabelSequence();
  
  Standard_EXPORT     void Clear() ;
~TDF_LabelSequence()
{
  Clear();
}
  
  Standard_EXPORT    const TDF_LabelSequence& Assign(const TDF_LabelSequence& Other) ;
   const TDF_LabelSequence& operator =(const TDF_LabelSequence& Other) 
{
  return Assign(Other);
}
  
  Standard_EXPORT     void Append(const TDF_Label& T) ;
  
        void Append(TDF_LabelSequence& S) ;
  
  Standard_EXPORT     void Prepend(const TDF_Label& T) ;
  
        void Prepend(TDF_LabelSequence& S) ;
  
        void InsertBefore(const Standard_Integer Index,const TDF_Label& T) ;
  
        void InsertBefore(const Standard_Integer Index,TDF_LabelSequence& S) ;
  
  Standard_EXPORT     void InsertAfter(const Standard_Integer Index,const TDF_Label& T) ;
  
        void InsertAfter(const Standard_Integer Index,TDF_LabelSequence& S) ;
  
  Standard_EXPORT    const TDF_Label& First() const;
  
  Standard_EXPORT    const TDF_Label& Last() const;
  
        void Split(const Standard_Integer Index,TDF_LabelSequence& Sub) ;
  
  Standard_EXPORT    const TDF_Label& Value(const Standard_Integer Index) const;
   const TDF_Label& operator()(const Standard_Integer Index) const
{
  return Value(Index);
}
  
  Standard_EXPORT     void SetValue(const Standard_Integer Index,const TDF_Label& I) ;
  
  Standard_EXPORT     TDF_Label& ChangeValue(const Standard_Integer Index) ;
    TDF_Label& operator()(const Standard_Integer Index) 
{
  return ChangeValue(Index);
}
  
  Standard_EXPORT     void Remove(const Standard_Integer Index) ;
  
  Standard_EXPORT     void Remove(const Standard_Integer FromIndex,const Standard_Integer ToIndex) ;





protected:





private:

  
  Standard_EXPORT   TDF_LabelSequence(const TDF_LabelSequence& Other);




};

#define SeqItem TDF_Label
#define SeqItem_hxx <TDF_Label.hxx>
#define TCollection_SequenceNode TDF_SequenceNodeOfLabelSequence
#define TCollection_SequenceNode_hxx <TDF_SequenceNodeOfLabelSequence.hxx>
#define Handle_TCollection_SequenceNode Handle_TDF_SequenceNodeOfLabelSequence
#define TCollection_SequenceNode_Type_() TDF_SequenceNodeOfLabelSequence_Type_()
#define TCollection_Sequence TDF_LabelSequence
#define TCollection_Sequence_hxx <TDF_LabelSequence.hxx>

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
