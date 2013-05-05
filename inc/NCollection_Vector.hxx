// Created on: 2002-04-23
// Created by: Alexander GRIGORIEV
// Copyright (c) 2002-2013 OPEN CASCADE SAS
//
// The content of this file is subject to the Open CASCADE Technology Public
// License Version 6.5 (the "License"). You may not use the content of this file
// except in compliance with the License. Please obtain a copy of the License
// at http://www.opencascade.org and read it completely before using this file.
//
// The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
// main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.
//
// The Original Code and all software distributed under the License is
// distributed on an "AS IS" basis, without warranty of any kind, and the
// Initial Developer hereby disclaims all such warranties, including without
// limitation, any warranties of merchantability, fitness for a particular
// purpose or non-infringement. Please see the License for the specific terms
// and conditions governing the rights and limitations under the License.

#ifndef NCollection_Vector_HeaderFile
#define NCollection_Vector_HeaderFile

#include <NCollection_BaseVector.hxx>
#include <NCollection_BaseCollection.hxx>

//! Class NCollection_Vector (dynamic array of objects)
//!
//! This class is similar to NCollection_Array1  though the indices always start
//! at 0 (in Array1 the first index must be specified)
//!
//! The Vector is always created with 0 length. It can be enlarged by two means:
//!  1. Calling the method Append (val) - then "val" is added to the end of the
//!     vector (the vector length is incremented)
//!  2. Calling the method SetValue (i, val)  - if "i" is greater than or equal
//!     to the current length of the vector,  the vector is enlarged to accomo-
//!     date this index
//!
//! The methods Append and SetValue return  a non-const reference  to the copied
//! object  inside  the vector.  This reference  is guaranteed to be valid until
//! the vector is destroyed. It can be used to access the vector member directly
//! or to pass its address to other data structures.
//!
//! The vector iterator remembers the length of the vector  at the moment of the
//! creation or initialisation of the iterator.   Therefore the iteration begins
//! at index 0  and stops at the index equal to (remembered_length-1).  It is OK
//! to enlarge the vector during the iteration.
template <class TheItemType> class NCollection_Vector
: public NCollection_BaseCollection<TheItemType>,
  public NCollection_BaseVector
{
public:

  typedef TheItemType TheItemTypeD;

  //! Nested class Iterator
  class Iterator : public NCollection_BaseCollection<TheItemType>::Iterator,
                   public NCollection_BaseVector::Iterator
  {
  public:

    //! Empty constructor - for later Init
    Iterator() {}

    //! Constructor with initialisation
    Iterator (const NCollection_Vector& theVector)
    : NCollection_BaseVector::Iterator (theVector) {}

    //! Copy constructor
    Iterator (const Iterator& theOther)
    : NCollection_BaseVector::Iterator (theOther) {}

    //! Initialisation
    void Init (const NCollection_Vector& theVector)
    {
      initV (theVector);
    }

    //! Assignment
    Iterator& operator= (const Iterator& theOther)
    {
      copyV (theOther);
      return *this;
    }

    //! Check end
    virtual Standard_Boolean More() const
    {
      return moreV();
    }

    //! Make step
    virtual void Next()
    {
      nextV();
    }

    //! Constant value access
    virtual const TheItemType& Value() const
    {
      return ((const TheItemType* )curBlockV()->DataPtr)[myCurIndex];
    }

    //! Variable value access
    virtual TheItemType& ChangeValue() const
    {
      return ((TheItemType* )curBlockV()->DataPtr)[myCurIndex];
    }

  };

public: //! @name public methods

  //! Constructor
  NCollection_Vector (const Standard_Integer theIncrement              = 256,
                      const Handle_NCollection_BaseAllocator& theAlloc = NULL)
  : NCollection_BaseCollection<TheItemType> (theAlloc),
    NCollection_BaseVector (NCollection_BaseCollection<TheItemType>::myAllocator, initMemBlocks, sizeof(TheItemType), theIncrement) {}

  //! Copy constructor
  NCollection_Vector (const NCollection_Vector& theOther)
  : NCollection_BaseCollection<TheItemType> (theOther.myAllocator),
    NCollection_BaseVector (NCollection_BaseCollection<TheItemType>::myAllocator, initMemBlocks, theOther)
  {
    copyData (theOther);
  }

  //! Destructor
  ~NCollection_Vector()
  {
    for (Standard_Integer anItemIter = 0; anItemIter < myCapacity; ++anItemIter)
    {
      initMemBlocks (*this, myData[anItemIter], 0, 0);
    }
    NCollection_BaseCollection<TheItemType>::myAllocator->Free (myData);
  }

  //! Operator=
  NCollection_Vector& operator= (const NCollection_Vector& theOther)
  {
    Assign (theOther, Standard_False);
    return *this;
  }

  //! Total number of items
  Standard_Integer Length() const
  {
    return myLength;
  }

  //! Total number of items in the vector
  virtual Standard_Integer Size() const
  {
    return myLength;
  }

  //! Method for consistency with other collections.
  //! @return Lower bound (inclusive) for iteration.
  Standard_Integer Lower() const
  {
    return 0;
  }

  //! Method for consistency with other collections.
  //! @return Upper bound (inclusive) for iteration.
  Standard_Integer Upper() const
  {
    return myLength - 1;
  }

  //! Empty query
  Standard_Boolean IsEmpty() const
  {
    return (myLength == 0);
  }

  //! Virtual assignment (any collection to this array)
  virtual void Assign (const NCollection_BaseCollection<TheItemType>& theOther)
  {
    if (this != &theOther)
    {
      TYPENAME NCollection_BaseCollection<TheItemType>::Iterator& anIter2 = theOther.CreateIterator();
      while (anIter2.More())
      {
        Append (anIter2.Value());
        anIter2.Next();
      }
    }
  }

  //! Assignment to the collection of the same type
  inline void Assign (const NCollection_Vector& theOther,
                      const Standard_Boolean    theOwnAllocator = Standard_True);

  //! Method to create iterators for base collections
  virtual TYPENAME NCollection_BaseCollection<TheItemType>::Iterator& CreateIterator() const
  {
    return *(new (this->IterAllocator()) Iterator(*this));
  }

  //! Append
  TheItemType& Append (const TheItemType& theValue)
  {
    TheItemType& anAppended = *(TheItemType* )expandV (NCollection_BaseCollection<TheItemType>::myAllocator, myLength);
    anAppended = theValue;
    return anAppended;
  }

  //! Operator() - query the const value
  const TheItemType& operator() (const Standard_Integer theIndex) const
  {
    return Value (theIndex);
  }

  const TheItemType& Value (const Standard_Integer theIndex) const
  {
    return *(const TheItemType* )findV (theIndex);
  }

  //! @return first element
  const TheItemType& First() const
  {
    return *(const TheItemType* )findV (Lower());
  }

  //! @return first element
  TheItemType& ChangeFirst()
  {
    return *(TheItemType* )findV (Lower());
  }

  //! @return last element
  const TheItemType& Last() const
  {
    return *(const TheItemType* )findV (Upper());
  }

  //! @return last element
  TheItemType& ChangeLast()
  {
    return *(TheItemType* )findV (Upper());
  }

  //! Operator() - query the value
  TheItemType& operator() (const Standard_Integer theIndex)
  {
    return ChangeValue (theIndex);
  }

  TheItemType& ChangeValue (const Standard_Integer theIndex)
  {
    return *(TheItemType* )findV (theIndex);
  }

  //! SetValue () - set or append a value
  TheItemType& SetValue (const Standard_Integer theIndex,
                         const TheItemType&     theValue)
  {
    Standard_OutOfRange_Raise_if (theIndex < 0, "NCollection_Vector::SetValue");
    TheItemType* const aVecValue = (TheItemType* )(theIndex < myLength ? findV (theIndex) : expandV (NCollection_BaseCollection<TheItemType>::myAllocator, theIndex));
    *aVecValue = theValue;
    return *aVecValue;
  }

private: //! @name private methods

  void copyData (const NCollection_Vector& theOther)
  {
    Standard_Integer iBlock = 0;
    /*NCollection_Vector::*/Iterator anIter (theOther);
    for (Standard_Integer aLength = 0; aLength < myLength; aLength += myIncrement)
    {
      MemBlock& aBlock = myData[iBlock];
      initMemBlocks (*this, aBlock, aLength, myIncrement);
      Standard_Integer anItemIter = 0;
      for (; anItemIter < myIncrement; ++anItemIter)
      {
        if (!anIter.More())
        {
          break;
        }

        ((TheItemType* )aBlock.DataPtr)[anItemIter] = anIter.Value();
        anIter.Next();
      }
      aBlock.Length = anItemIter;
      iBlock++;
    }
  }

  //! Method to initialize memory block content
  static void initMemBlocks (NCollection_BaseVector&           theVector,
                             NCollection_BaseVector::MemBlock& theBlock,
                             const Standard_Integer            theFirst,
                             const Standard_Integer            theSize)
  {
    NCollection_Vector& aSelf = static_cast<NCollection_Vector&> (theVector);
    Handle(NCollection_BaseAllocator)& anAllocator = aSelf.myAllocator;

    // release current content
    if (theBlock.DataPtr != NULL)
    {
      for (Standard_Integer anItemIter = 0; anItemIter < theBlock.Size; ++anItemIter)
      {
#ifdef __BORLANDC__
        ((TheItemType* )theBlock.DataPtr)[anItemIter].~TheItemType();
#else
        ((TheItemType* )theBlock.DataPtr)[anItemIter].~TheItemTypeD();
#endif
      }
      anAllocator->Free (theBlock.DataPtr);
      theBlock.DataPtr = NULL;
    }

    // allocate new content if requested
    if (theSize > 0)
    {
      theBlock.DataPtr = anAllocator->Allocate (theSize * sizeof(TheItemType));
      for (Standard_Integer anItemIter = 0; anItemIter < theSize; ++anItemIter)
      {
        new (&((TheItemType* )theBlock.DataPtr)[anItemIter]) TheItemType;
      }
    }
    theBlock.FirstIndex = theFirst;
    theBlock.Size       = theSize;
    theBlock.Length     = 0;
  }

  friend class Iterator;

};

//! Assignment to the collection of the same type
template <class TheItemType> inline
void NCollection_Vector<TheItemType>::Assign (const NCollection_Vector& theOther,
                                              const Standard_Boolean    theOwnAllocator)
{
  if (this == &theOther)
  {
    return;
  }

  // destroy current data using current allocator
  for (Standard_Integer anItemIter = 0; anItemIter < myCapacity; ++anItemIter)
  {
    initMemBlocks (*this, myData[anItemIter], 0, 0);
  }
  NCollection_BaseCollection<TheItemType>::myAllocator->Free (myData);

  // allocate memory blocks with new allocator
  if (!theOwnAllocator)
  {
    NCollection_BaseCollection<TheItemType>::myAllocator = theOther.myAllocator;
  }
  myIncrement = theOther.myIncrement;
  myLength    = theOther.myLength;
  myNBlocks   = (myLength == 0) ? 0 : (1 + (myLength - 1)/myIncrement);
  myCapacity  = GetCapacity (myIncrement) + myLength / myIncrement;
  myData      = allocMemBlocks (NCollection_BaseCollection<TheItemType>::myAllocator, myCapacity);

  // copy data
  copyData (theOther);
}

#endif // NCollection_Vector_HeaderFile
