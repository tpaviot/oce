// File       NCollection_QuickSort.hxx
// Created    27 January 2011
// Author     KGV
// Copyright  OpenCASCADE 2011

#ifndef _NCollection_QuickSort_HeaderFile
#define _NCollection_QuickSort_HeaderFile

#include <NCollection_Comparator.hxx>
#include <Standard_Integer.hxx>

/**
 * Perform sorting of enumerable collection with QuickSort algorithm.
 * Enumerable collection should provide the random access to its values
 * by index number with methods Value(theId) and ChangeValue(theId).
 * Currently it supposed to be used with NCollection_Sequence and NCollection_Vector.
 *
 * Usage sample:
 *   // input sequence
 *   NCollection_Sequence<Standard_Real> aSequence;
 *   // perform sorting for the whole sequence.
 *   NCollection_QuickSort<NCollection_Sequence<Standard_Real>, Standard_Real>
 *     ::Perform (aSequence, NCollection_Comparator<Standard_Real>(),
 *                1, aSequence.Size());
 */
template<class TheCollType, class TheItemType>
class NCollection_QuickSort
{
public:

  //! Main entry call to perform sorting
  static void Perform (TheCollType& theEnumColl,
                       const NCollection_Comparator<TheItemType>& theComparator,
                       const Standard_Integer theLower,
                       const Standard_Integer theUpper)
  {
    if (theLower < theUpper)
    {
      Standard_Integer aPivotPosition = Partition (theEnumColl, theComparator,
                                                   theLower, theUpper);
      if (theLower < aPivotPosition)
      {
        // recursive call
        Perform (theEnumColl, theComparator,
                 theLower, aPivotPosition - 1);
      }
      // recursive call
      Perform (theEnumColl, theComparator,
               aPivotPosition + 1, theUpper);
    }
  }

private:

  //! Auxiliary function
  static void SwapValues (TheItemType& x, TheItemType& y)
  {
    TheItemType aCopy = x;
    x = y;
    y = aCopy;
  }

  static Standard_Integer Partition (TheCollType& theEnumColl,
                                     const NCollection_Comparator<TheItemType>& theComparator,
                                     const Standard_Integer theLower,
                                     const Standard_Integer theUpper)
  {
    Standard_Integer anIdLeft (theLower), anIdRight (theUpper);
    const TheItemType aPivot = theEnumColl.Value (theLower);

    while (anIdLeft < anIdRight)
    {
      while (theComparator.IsGreater (theEnumColl.Value (anIdRight), aPivot))
      {
        --anIdRight;
      }
      while ((anIdLeft < anIdRight) &&
             theComparator.IsLowerEqual (theEnumColl.Value (anIdLeft), aPivot))
      {
        ++anIdLeft;
      }

      if (anIdLeft < anIdRight)
      {
        SwapValues (theEnumColl.ChangeValue (anIdLeft),
                    theEnumColl.ChangeValue (anIdRight));
      }
    }

    theEnumColl.ChangeValue (theLower) = theEnumColl.Value (anIdRight);
    theEnumColl.ChangeValue (anIdRight) = aPivot;
    return anIdRight;
  }

};

#endif /*_NCollection_QuickSort_HeaderFile*/
