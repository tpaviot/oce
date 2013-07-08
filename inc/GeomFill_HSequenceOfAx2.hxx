// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _GeomFill_HSequenceOfAx2_HeaderFile
#define _GeomFill_HSequenceOfAx2_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineHandle_HeaderFile
#include <Standard_DefineHandle.hxx>
#endif
#ifndef _Handle_GeomFill_HSequenceOfAx2_HeaderFile
#include <Handle_GeomFill_HSequenceOfAx2.hxx>
#endif

#ifndef _GeomFill_SequenceOfAx2_HeaderFile
#include <GeomFill_SequenceOfAx2.hxx>
#endif
#ifndef _MMgt_TShared_HeaderFile
#include <MMgt_TShared.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
class Standard_NoSuchObject;
class Standard_OutOfRange;
class gp_Ax2;
class GeomFill_SequenceOfAx2;



class GeomFill_HSequenceOfAx2 : public MMgt_TShared {

public:

  
      GeomFill_HSequenceOfAx2();
  
        Standard_Boolean IsEmpty() const;
  
        Standard_Integer Length() const;
  
  Standard_EXPORT     void Clear() ;
  
  Standard_EXPORT     void Append(const gp_Ax2& anItem) ;
  
  Standard_EXPORT     void Append(const Handle(GeomFill_HSequenceOfAx2)& aSequence) ;
  
  Standard_EXPORT     void Prepend(const gp_Ax2& anItem) ;
  
  Standard_EXPORT     void Prepend(const Handle(GeomFill_HSequenceOfAx2)& aSequence) ;
  
  Standard_EXPORT     void Reverse() ;
  
  Standard_EXPORT     void InsertBefore(const Standard_Integer anIndex,const gp_Ax2& anItem) ;
  
  Standard_EXPORT     void InsertBefore(const Standard_Integer anIndex,const Handle(GeomFill_HSequenceOfAx2)& aSequence) ;
  
  Standard_EXPORT     void InsertAfter(const Standard_Integer anIndex,const gp_Ax2& anItem) ;
  
  Standard_EXPORT     void InsertAfter(const Standard_Integer anIndex,const Handle(GeomFill_HSequenceOfAx2)& aSequence) ;
  
  Standard_EXPORT     void Exchange(const Standard_Integer anIndex,const Standard_Integer anOtherIndex) ;
  
  Standard_EXPORT     Handle_GeomFill_HSequenceOfAx2 Split(const Standard_Integer anIndex) ;
  
  Standard_EXPORT     void SetValue(const Standard_Integer anIndex,const gp_Ax2& anItem) ;
  
  Standard_EXPORT    const gp_Ax2& Value(const Standard_Integer anIndex) const;
  
  Standard_EXPORT     gp_Ax2& ChangeValue(const Standard_Integer anIndex) ;
  
  Standard_EXPORT     void Remove(const Standard_Integer anIndex) ;
  
  Standard_EXPORT     void Remove(const Standard_Integer fromIndex,const Standard_Integer toIndex) ;
  
       const GeomFill_SequenceOfAx2& Sequence() const;
  
        GeomFill_SequenceOfAx2& ChangeSequence() ;
  
  Standard_EXPORT     Handle_GeomFill_HSequenceOfAx2 ShallowCopy() const;




  DEFINE_STANDARD_RTTI(GeomFill_HSequenceOfAx2)

protected:




private: 


GeomFill_SequenceOfAx2 mySequence;


};

#define Item gp_Ax2
#define Item_hxx <gp_Ax2.hxx>
#define TheSequence GeomFill_SequenceOfAx2
#define TheSequence_hxx <GeomFill_SequenceOfAx2.hxx>
#define TCollection_HSequence GeomFill_HSequenceOfAx2
#define TCollection_HSequence_hxx <GeomFill_HSequenceOfAx2.hxx>
#define Handle_TCollection_HSequence Handle_GeomFill_HSequenceOfAx2
#define TCollection_HSequence_Type_() GeomFill_HSequenceOfAx2_Type_()

#include <TCollection_HSequence.lxx>

#undef Item
#undef Item_hxx
#undef TheSequence
#undef TheSequence_hxx
#undef TCollection_HSequence
#undef TCollection_HSequence_hxx
#undef Handle_TCollection_HSequence
#undef TCollection_HSequence_Type_


// other Inline functions and methods (like "C++: function call" methods)
inline Handle_GeomFill_HSequenceOfAx2 ShallowCopy(const Handle_GeomFill_HSequenceOfAx2& me) {
 return me->ShallowCopy();
}



#endif
