// Created on: 2002-04-24
// Created by: Alexander KARTOMIN (akm)
// Copyright (c) 2002-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef NCollection_DataMap_HeaderFile
#define NCollection_DataMap_HeaderFile

#include <NCollection_BaseMap.hxx>
#include <NCollection_TListNode.hxx>
#include <NCollection_StlIterator.hxx>
#include <NCollection_DefaultHasher.hxx>

#include <Standard_TypeMismatch.hxx>
#include <Standard_NoSuchObject.hxx>

/**
* Purpose:     The DataMap is a Map to store keys with associated
*              Items. See Map  from NCollection for  a discussion
*              about the number of buckets.
*
*              The DataMap can be seen as an extended array where
*              the Keys  are the   indices.  For this reason  the
*              operator () is defined on DataMap to fetch an Item
*              from a Key. So the following syntax can be used :
*
*              anItem = aMap(aKey);
*              aMap(aKey) = anItem;
*
*              This analogy has its  limit.   aMap(aKey) = anItem
*              can  be done only  if aKey was previously bound to
*              an item in the map.
*/              

template < class TheKeyType, 
           class TheItemType, 
           class Hasher = NCollection_DefaultHasher<TheKeyType> >
class NCollection_DataMap : public NCollection_BaseMap
{
  // **************** Adaptation of the TListNode to the DATAmap
 public:
  class DataMapNode : public NCollection_TListNode<TheItemType>
  {
  public:
    //! Constructor with 'Next'
    DataMapNode (const TheKeyType&     theKey, 
                 const TheItemType&    theItem, 
                 NCollection_ListNode* theNext) :
      NCollection_TListNode<TheItemType> (theItem, theNext),
      myKey(theKey)
    {}

    //! Key
    const TheKeyType& Key (void) const
    { return myKey; }
    
    //! Static deleter to be passed to BaseMap
    static void delNode (NCollection_ListNode * theNode, 
                         Handle(NCollection_BaseAllocator)& theAl)
    {
      ((DataMapNode *) theNode)->~DataMapNode();
      theAl->Free(theNode);
    }

  private:
    TheKeyType    myKey;
  };

 public:
  // **************** Implementation of the Iterator interface.
  class Iterator : public NCollection_BaseMap::Iterator
  {
  public:
    //! Empty constructor
    Iterator (void) :
      NCollection_BaseMap::Iterator() {}
    //! Constructor
    Iterator (const NCollection_DataMap& theMap) :
      NCollection_BaseMap::Iterator(theMap) {}
    //! Query if the end of collection is reached by iterator
    Standard_Boolean More(void) const
    { return PMore(); }
    //! Make a step along the collection
    void Next(void)
    { PNext(); }
    //! Value inquiry
    const TheItemType& Value(void) const
    {  
      Standard_NoSuchObject_Raise_if(!More(), "NCollection_DataMap::Iterator::Value");  
      return ((DataMapNode *) myNode)->Value();
    }
    //! Value change access
    TheItemType& ChangeValue(void) const
    {  
      Standard_NoSuchObject_Raise_if(!More(), "NCollection_DataMap::Iterator::ChangeValue");  
      return ((DataMapNode *) myNode)->ChangeValue();
    }
    //! Key
    const TheKeyType& Key (void) const
    { 
      Standard_NoSuchObject_Raise_if(!More(), "NCollection_DataMap::Iterator::Key");  
      return ((DataMapNode *) myNode)->Key();
    }
  };
  
  //! Shorthand for a regular iterator type.
  typedef NCollection_StlIterator<std::forward_iterator_tag, Iterator, TheItemType, false> iterator;

  //! Shorthand for a constant iterator type.
  typedef NCollection_StlIterator<std::forward_iterator_tag, Iterator, TheItemType, true> const_iterator;

  //! Returns an iterator pointing to the first element in the map.
  iterator begin() const { return Iterator (*this); }

  //! Returns an iterator referring to the past-the-end element in the map.
  iterator end() const { return Iterator(); }

  //! Returns a const iterator pointing to the first element in the map.
  const_iterator cbegin() const { return Iterator (*this); }

  //! Returns a const iterator referring to the past-the-end element in the map.
  const_iterator cend() const { return Iterator(); }

 public:
  // ---------- PUBLIC METHODS ------------

  //! Constructor
  NCollection_DataMap (const Standard_Integer NbBuckets=1,
                     const Handle(NCollection_BaseAllocator)& theAllocator = 0L)
    : NCollection_BaseMap (NbBuckets, Standard_True, theAllocator) {}

  //! Copy constructor
  NCollection_DataMap (const NCollection_DataMap& theOther)
    : NCollection_BaseMap (theOther.NbBuckets(), Standard_True, theOther.myAllocator) 
  { *this = theOther; }

  //! Exchange the content of two maps without re-allocations.
  //! Notice that allocators will be swapped as well!
  void Exchange (NCollection_DataMap& theOther)
  {
    this->exchangeMapsData (theOther);
  }

  //! Assignment.
  //! This method does not change the internal allocator.
  NCollection_DataMap& Assign (const NCollection_DataMap& theOther)
  { 
    if (this == &theOther)
      return *this;

    Clear();
    ReSize (theOther.Extent()-1);
    Iterator anIter(theOther);
    for (; anIter.More(); anIter.Next())
      Bind (anIter.Key(), anIter.Value());
    return *this;
  }

  //! Assignment operator
  NCollection_DataMap& operator= (const NCollection_DataMap& theOther)
  { 
    return Assign (theOther);
  }

  //! ReSize
  void ReSize (const Standard_Integer N)
  {
    NCollection_ListNode** newdata = NULL;
    NCollection_ListNode** dummy   = NULL;
    Standard_Integer newBuck;
    if (BeginResize (N, newBuck, newdata, dummy))
    {
      if (myData1) 
      {
        DataMapNode** olddata = (DataMapNode**) myData1;
        DataMapNode *p, *q;
        Standard_Integer i,k;
        for (i = 0; i <= NbBuckets(); i++) 
        {
          if (olddata[i]) 
          {
            p = olddata[i];
            while (p) 
            {
              k = Hasher::HashCode(p->Key(),newBuck);
              q = (DataMapNode*) p->Next();
              p->Next() = newdata[k];
              newdata[k] = p;
              p = q;
            }
          }
        }
      }
      EndResize (N, newBuck, newdata, dummy);
    }
  }

  //! Bind binds Item to Key in map. Returns Standard_True if Key was not
  //! exist in the map. If the Key was already bound, the Item will be rebinded
  //! and Standard_False will be returned.
  Standard_Boolean Bind (const TheKeyType& theKey, const TheItemType& theItem)
  {
    if (Resizable()) 
      ReSize(Extent());
    DataMapNode** data = (DataMapNode**)myData1;
    Standard_Integer k = Hasher::HashCode (theKey, NbBuckets());
    DataMapNode* p = data[k];
    while (p) 
    {
      if (Hasher::IsEqual(p->Key(), theKey))
      {
        p->ChangeValue() = theItem;
        return Standard_False;
      }
      p = (DataMapNode *) p->Next();
    }
    data[k] = new (this->myAllocator) DataMapNode (theKey, theItem, data[k]);
    Increment();
    return Standard_True;
  }

  //! Bound binds Item to Key in map. Returns modifiable Item 
  TheItemType* Bound (const TheKeyType& theKey, const TheItemType& theItem)
  {
    if (Resizable()) 
      ReSize(Extent());
    DataMapNode** data = (DataMapNode**)myData1;
    Standard_Integer k = Hasher::HashCode (theKey, NbBuckets());
    DataMapNode* p = data[k];
    while (p)
    {
      if (Hasher::IsEqual(p->Key(), theKey))
      {
        p->ChangeValue() = theItem;
        return &p->ChangeValue();
      }
      p = (DataMapNode*)p->Next();
    }
    data[k] = new (this->myAllocator) DataMapNode (theKey, theItem, data[k]);
    Increment();
    return &data[k]->ChangeValue();
  }

  //! IsBound
  Standard_Boolean IsBound(const TheKeyType& K) const
  {
    DataMapNode* p;
    return lookup(K, p);
  }

  //! UnBind removes Item Key pair from map
  Standard_Boolean UnBind(const TheKeyType& K)
  {
    if (IsEmpty()) 
      return Standard_False;
    DataMapNode** data = (DataMapNode**) myData1;
    Standard_Integer k = Hasher::HashCode(K,NbBuckets());
    DataMapNode* p = data[k];
    DataMapNode* q = NULL;
    while (p) 
    {
      if (Hasher::IsEqual(p->Key(),K)) 
      {
        Decrement();
        if (q) 
          q->Next() = p->Next();
        else
          data[k] = (DataMapNode*) p->Next();
        p->~DataMapNode();
        this->myAllocator->Free(p);
        return Standard_True;
      }
      q = p;
      p = (DataMapNode*) p->Next();
    }
    return Standard_False;
  }

  //! Seek returns pointer to Item by Key. Returns
  //! NULL is Key was not bound.
  const TheItemType* Seek(const TheKeyType& theKey) const
  {
    DataMapNode* p = 0;
    if (!lookup(theKey, p))
      return 0L;
    return &p->Value();
  }

  //! Find returns the Item for Key. Raises if Key was not bound
  const TheItemType& Find(const TheKeyType& theKey) const
  {
    DataMapNode* p = 0;
    if (!lookup(theKey, p))
      Standard_NoSuchObject::Raise("NCollection_DataMap::Find");
    return p->Value();
  }

  //! Find Item for key with copying.
  //! @return true if key was found
  Standard_Boolean Find (const TheKeyType& theKey,
                         TheItemType&      theValue) const
  {
    DataMapNode* p = 0;
    if (!lookup(theKey, p))
      return Standard_False;

    theValue = p->Value();
    return Standard_True;
  }

  //! operator ()
  const TheItemType& operator() (const TheKeyType& theKey) const
  { return Find(theKey); }

  //! ChangeSeek returns modifiable pointer to Item by Key. Returns
  //! NULL is Key was not bound.
  TheItemType* ChangeSeek(const TheKeyType& theKey)
  {
    DataMapNode* p = 0;
    if (!lookup(theKey, p))
      return 0L;
    return &p->ChangeValue();
  }

  //! ChangeFind returns mofifiable Item by Key. Raises if Key was not bound
  TheItemType& ChangeFind (const TheKeyType& theKey)
  {
    DataMapNode* p = 0;
    if (!lookup(theKey, p))
      Standard_NoSuchObject::Raise("NCollection_DataMap::Find");
    return p->ChangeValue();
  }

  //! operator ()
  TheItemType& operator() (const TheKeyType& theKey)
  { return ChangeFind(theKey); }

  //! Clear data. If doReleaseMemory is false then the table of
  //! buckets is not released and will be reused.
  void Clear(const Standard_Boolean doReleaseMemory = Standard_True)
  { Destroy (DataMapNode::delNode, doReleaseMemory); }

  //! Clear data and reset allocator
  void Clear (const Handle(NCollection_BaseAllocator)& theAllocator)
  { 
    Clear();
    this->myAllocator = ( ! theAllocator.IsNull() ? theAllocator :
                    NCollection_BaseAllocator::CommonBaseAllocator() );
  }

  //! Destructor
  ~NCollection_DataMap (void)
  { Clear(); }

  //! Size
  Standard_Integer Size(void) const
  { return Extent(); }

  
 protected:
  // ---------- PROTECTED METHODS ----------
  //! Lookup for particular key in map. Returns true if key is found and
  //! thepNode points to binded node. Returns false if key is not found,
  //! thehNode value is this case is not usable.
  Standard_Boolean lookup(const TheKeyType& theKey,DataMapNode*& thepNode) const
  {
    if (IsEmpty())
      return Standard_False; // Not found
    for (thepNode = (DataMapNode*)myData1[Hasher::HashCode(theKey, NbBuckets())];
         thepNode; thepNode = (DataMapNode*)thepNode->Next())
    {
      if (Hasher::IsEqual(thepNode->Key(), theKey)) 
        return Standard_True;
    }
    return Standard_False; // Not found
  }

};

#endif

