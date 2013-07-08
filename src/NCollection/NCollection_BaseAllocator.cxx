// Created on: 2002-04-12
// Created by: Alexander KARTOMIN (akm)
// Copyright (c) 2002-2012 OPEN CASCADE SAS
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

// Purpose:     Implementation of the BaseAllocator class

#include <NCollection_BaseAllocator.hxx>
#include <NCollection_DataMap.hxx>
#include <NCollection_Map.hxx>
#include <NCollection_List.hxx>
#include <Standard_Mutex.hxx>

#include <stdio.h>

#if defined(_MSC_VER)
# define FMT_SZ_Q "I"
#elif defined(__GNUC__)
# define FMT_SZ_Q "z"
#elif defined(_OCC64)
# define FMT_SZ_Q "l"
#else
# define FMT_SZ_Q ""
#endif

IMPLEMENT_STANDARD_HANDLE(NCollection_BaseAllocator,MMgt_TShared)
IMPLEMENT_STANDARD_RTTIEXT(NCollection_BaseAllocator,MMgt_TShared)

//=======================================================================
//function : Allocate
//purpose  : Standard allocation
//=======================================================================

void* NCollection_BaseAllocator::Allocate(const size_t size)
{ 
  return Standard::Allocate(size);
}

//=======================================================================
//function : Free
//purpose  : Standard deallocation
//=======================================================================

void  NCollection_BaseAllocator::Free(void *anAddress)
{ 
  if (anAddress) Standard::Free((Standard_Address&)anAddress); 
}

//=======================================================================
//function : CommonBaseAllocator
//purpose  : Creates the only one BaseAllocator
//=======================================================================

const Handle(NCollection_BaseAllocator)& 
       NCollection_BaseAllocator::CommonBaseAllocator(void)
{ 
  static Handle(NCollection_BaseAllocator) pAllocator = 
    new NCollection_BaseAllocator;
  return pAllocator;
}

// global variable to ensure that allocator will be created during loading the library
static Handle(NCollection_BaseAllocator) theAllocInit = 
  NCollection_BaseAllocator::CommonBaseAllocator();

//=======================================================================
/**
 * Structure for collecting statistics about blocks of one size
 */
//=======================================================================
struct StorageInfo
{
  Standard_Size roundSize;
  int nbAlloc;
  int nbFree;
  StorageInfo()
    : roundSize(0), nbAlloc(0), nbFree(0) {}
  StorageInfo(Standard_Size theSize)
    : roundSize(theSize), nbAlloc(0), nbFree(0) {}
};

//=======================================================================
/**
 * Static data map (block_size -> StorageInfo)
 */
//=======================================================================
static NCollection_DataMap<Standard_Size, StorageInfo>& StorageMap()
{
  static NCollection_IncAllocator TheAlloc;
  static NCollection_DataMap<Standard_Size, StorageInfo>
    TheMap (1, & TheAlloc);
  return TheMap;
}

//=======================================================================
/**
 * Static data map (address -> AllocationID)
 */
//=======================================================================
static NCollection_DataMap<Standard_Address, Standard_Size>& StorageIDMap()
{
  static NCollection_IncAllocator TheAlloc;
  static NCollection_DataMap<Standard_Address, Standard_Size>
    TheMap (1, & TheAlloc);
  return TheMap;
}

//=======================================================================
/**
 * Static map (AllocationID)
 */
//=======================================================================
static NCollection_Map<Standard_Size>& StorageIDSet()
{
  static NCollection_IncAllocator TheAlloc;
  static NCollection_Map<Standard_Size> TheMap (1, & TheAlloc);
  return TheMap;
}

//=======================================================================
/**
 * Exported value to set the block size for which it is required 
 * collecting alive allocation IDs.
 * The method NCollection_BaseAllocator::PrintMemUsageStatistics
 * dumps all alive IDs into the file alive.d in the current directory.
 */
//=======================================================================
Standard_EXPORT Standard_Size& StandardCallBack_CatchSize()
{
  static Standard_Size Value = 0;
  return Value;
}

//=======================================================================
/**
 * Exported value to set the allocation ID for which it is required 
 * to set a breakpoint on the moment of allocation or freeing.
 * See the method NCollection_BaseAllocator::StandardCallBack
 * where the value StandardCallBack_CatchID() is compared to the current ID.
 * There you can place a break point at the stub assignment statement "a =".
 */
//=======================================================================
Standard_EXPORT Standard_Size& StandardCallBack_CatchID()
{
  static Standard_Size Value = 0;
  return Value;
}

//=======================================================================
/**
 * Static value of the current allocation ID. It provides unique
 * numbering of allocation events.
 */
//=======================================================================
static Standard_Size CurrentID = 0;

//=======================================================================
/**
 * Exported function to reset the callback system to the initial state
 */
//=======================================================================
Standard_EXPORT void StandardCallBack_Reset()
{
  StorageMap().Clear();
  StorageIDMap().Clear();
  StorageIDSet().Clear();
  CurrentID = 0;
  StandardCallBack_CatchSize() = 0;
  StandardCallBack_CatchID() = 0;
}

//=======================================================================
//function : StandardCallBack
//purpose  : Callback function to register alloc/free calls
//=======================================================================

void NCollection_BaseAllocator::StandardCallBack
                    (const Standard_Boolean theIsAlloc,
                     const Standard_Address theStorage,
                     const Standard_Size theRoundSize,
                     const Standard_Size /*theSize*/)
{
  static Standard_Mutex aMutex;
  Standard_Boolean isReentrant = Standard::IsReentrant();
  if (isReentrant)
    aMutex.Lock();
  // statistics by storage size
  NCollection_DataMap<Standard_Size, StorageInfo>& aStMap = StorageMap();
  if (!aStMap.IsBound(theRoundSize))
  {
    StorageInfo aEmpty(theRoundSize);
    aStMap.Bind(theRoundSize, aEmpty);
  }
  StorageInfo& aInfo = aStMap(theRoundSize);
  if (theIsAlloc)
    aInfo.nbAlloc++;
  else
    aInfo.nbFree++;

  if (theRoundSize == StandardCallBack_CatchSize())
  {
    // statistics by alive objects
    NCollection_DataMap<Standard_Address, Standard_Size>& aStIDMap = StorageIDMap();
    NCollection_Map<Standard_Size>& aStIDSet = StorageIDSet();
    if (theIsAlloc)
    {
      aStIDMap.Bind(theStorage, ++CurrentID);
      aStIDSet.Add(CurrentID);
      if (CurrentID == StandardCallBack_CatchID())
      {
        // Place for break point for allocation of investigated ID
      }
    }
    else
    {
      if (aStIDMap.IsBound(theStorage))
      {
        Standard_Size anID = aStIDMap(theStorage);
        aStIDSet.Remove(anID);
        if (anID == StandardCallBack_CatchID())
        {
          // Place for break point for freeing of investigated ID
        }
      }
    }
  }

  if (isReentrant)
    aMutex.Unlock();
}

//=======================================================================
//function : PrintMemUsageStatistics
//purpose  : Prints memory usage statistics cumulated by StandardCallBack
//=======================================================================

void NCollection_BaseAllocator::PrintMemUsageStatistics()
{
  // sort by roundsize
  NCollection_List<StorageInfo> aColl;
  NCollection_List<StorageInfo>::Iterator itLst;
  NCollection_DataMap<Standard_Size, StorageInfo>::Iterator itMap(StorageMap());
  for (; itMap.More(); itMap.Next())
  {
    for (itLst.Init(aColl); itLst.More(); itLst.Next())
      if (itMap.Value().roundSize < itLst.Value().roundSize)
        break;
    if (itLst.More())
      aColl.InsertBefore(itMap.Value(), itLst);
    else
      aColl.Append(itMap.Value());
  }
  Standard_Size aTotAlloc = 0;
  Standard_Size aTotLeft = 0;
  // print
  FILE * ff = fopen("memstat.d", "wt");
  if (ff == NULL)
  {
    cout << "failure writing file memstat.d" << endl;
    return;
  }
  fprintf(ff, "%12s %12s %12s %12s %12s\n",
          "BlockSize", "NbAllocated", "NbLeft", "Allocated", "Left");
  for (itLst.Init(aColl); itLst.More(); itLst.Next())
  {
    const StorageInfo& aInfo = itLst.Value();
    Standard_Integer nbLeft = aInfo.nbAlloc - aInfo.nbFree;
    Standard_Size aSizeAlloc = aInfo.nbAlloc * aInfo.roundSize;
    Standard_Size aSizeLeft = nbLeft * aInfo.roundSize;
    fprintf(ff, "%12" FMT_SZ_Q "u %12d %12d %12" FMT_SZ_Q "u %12" FMT_SZ_Q "u\n", aInfo.roundSize,
            aInfo.nbAlloc, nbLeft, aSizeAlloc, aSizeLeft);
    aTotAlloc += aSizeAlloc;
    aTotLeft += aSizeLeft;
  }
  fprintf(ff, "%12s %12s %12s %12" FMT_SZ_Q "u %12" FMT_SZ_Q "u\n", "Total:", "", "",
          aTotAlloc, aTotLeft);

  if (!StorageIDSet().IsEmpty())
  {
    fprintf(ff, "Alive allocation numbers of size=%" FMT_SZ_Q "u\n", StandardCallBack_CatchSize());
    NCollection_Map<Standard_Size>::Iterator itMap1(StorageIDSet());
    for (; itMap1.More(); itMap1.Next())
      fprintf(ff, "%" FMT_SZ_Q "u\n", itMap1.Key());
  }
  fclose(ff);
}
