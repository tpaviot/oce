// Copyright (c) 1999-2012 OPEN CASCADE SAS
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

#include <IntTools_MarkedRangeSet.ixx>

IntTools_MarkedRangeSet::IntTools_MarkedRangeSet() :
myRangeNumber(0)
{
}

IntTools_MarkedRangeSet::IntTools_MarkedRangeSet(const Standard_Real    theFirstBoundary,
						 const Standard_Real    theLastBoundary,
						 const Standard_Integer theInitFlag) 
{
  SetBoundaries(theFirstBoundary, theLastBoundary, theInitFlag);
}

IntTools_MarkedRangeSet::IntTools_MarkedRangeSet(const IntTools_CArray1OfReal& theSortedArray,
						 const Standard_Integer        theInitFlag)

{
  SetRanges(theSortedArray, theInitFlag);
}

void IntTools_MarkedRangeSet::SetBoundaries(const Standard_Real    theFirstBoundary,
					    const Standard_Real    theLastBoundary,
					    const Standard_Integer theInitFlag) 
{
  myRangeSetStorer.Clear();
  myRangeSetStorer.Append(theFirstBoundary);
  myRangeSetStorer.Append(theLastBoundary);
  myRangeNumber = 1;
  myFlags.Clear();
  myFlags.Append(theInitFlag);
}

void IntTools_MarkedRangeSet::SetRanges(const IntTools_CArray1OfReal& theSortedArray,
					const Standard_Integer        theInitFlag) 
{
  myRangeSetStorer.Clear();
  myFlags.Clear();
  Standard_Integer i = 0;

  for(i = 0; i < theSortedArray.Length(); i++) {
    myRangeSetStorer.Append(theSortedArray(i));    
  }
  myRangeNumber = myRangeSetStorer.Length() - 1;

  for(i = 1; i <= myRangeNumber; i++) {
    myFlags.Append(theInitFlag);
  }
}

Standard_Boolean IntTools_MarkedRangeSet::InsertRange(const Standard_Real    theFirstBoundary,
						      const Standard_Real    theLastBoundary,
						      const Standard_Integer theFlag) 
{
  Standard_Integer anIndex1 = GetIndex(theFirstBoundary, Standard_True);

  if(!anIndex1)
    return Standard_False;
  Standard_Integer anIndex2 = GetIndex(theLastBoundary, Standard_False);

  if(!anIndex2)
    return Standard_False;

  if(anIndex2 < anIndex1) { // it can be if theLastBoundary==theFirstBoundary==boundary_of_a_range or theFirstBoundary > theLastBoundary
    Standard_Integer atmpindex = anIndex1;
    anIndex1 = anIndex2;
    anIndex2 = atmpindex;

    if(theLastBoundary < theFirstBoundary)
      return Standard_False;
  }

  Standard_Boolean areEqualIndices = (anIndex1 == anIndex2);
  Standard_Integer aPrevFlag = myFlags(anIndex1);

  myRangeSetStorer.InsertAfter(anIndex1, theFirstBoundary);
  anIndex2++;
  myFlags.InsertAfter(anIndex1, theFlag);
  myRangeNumber = myRangeSetStorer.Length() - 1;

  myRangeSetStorer.InsertAfter(anIndex2, theLastBoundary);

  if(areEqualIndices) {
    myFlags.InsertAfter(anIndex2, aPrevFlag);
  }
  else {
    myFlags.InsertBefore(anIndex2, theFlag);
  }

  if(!areEqualIndices) {
    anIndex1++;
    anIndex2++;

    for(Standard_Integer i = anIndex1; i < anIndex2; i++) {
      myFlags.SetValue(i, theFlag);
    }
  }

  myRangeNumber = myRangeSetStorer.Length() - 1;

  return Standard_True;
}

Standard_Boolean IntTools_MarkedRangeSet::InsertRange(const IntTools_Range&  theRange,
						      const Standard_Integer theFlag) 
{
  return InsertRange(theRange.First(), theRange.Last(), theFlag);
}

Standard_Boolean IntTools_MarkedRangeSet::InsertRange(const Standard_Real    theFirstBoundary,
						      const Standard_Real    theLastBoundary,
						      const Standard_Integer theFlag,
						      const Standard_Integer theIndex) 
{
  Standard_Real aTolerance = 1.e-15;
  Standard_Integer anIndex = theIndex;

  if((theIndex <= 0) || (theIndex > myRangeNumber))
    return Standard_False;

  if((theFirstBoundary < myRangeSetStorer(theIndex)) ||
     (theLastBoundary > myRangeSetStorer(theIndex+1)) ||
     (Abs(theFirstBoundary - theLastBoundary) < aTolerance)) {
    return InsertRange(theFirstBoundary, theLastBoundary, theFlag);
  }
  else {
    Standard_Integer aPrevFlag = myFlags(anIndex);

    if((Abs(theFirstBoundary - myRangeSetStorer(anIndex)) > aTolerance) &&
       (Abs(theFirstBoundary - myRangeSetStorer(anIndex+1)) > aTolerance)) {
      myRangeSetStorer.InsertAfter(anIndex, theFirstBoundary);
      myFlags.InsertAfter(anIndex, theFlag);
      anIndex++;
      myRangeNumber = myRangeSetStorer.Length() - 1;
    }
    else {
      myFlags.SetValue(anIndex, theFlag);
    }

    if((Abs(theLastBoundary - myRangeSetStorer(anIndex)) > aTolerance) &&
       (Abs(theLastBoundary - myRangeSetStorer(anIndex+1)) > aTolerance)) {
      myRangeSetStorer.InsertAfter(anIndex, theLastBoundary);
      myRangeNumber = myRangeSetStorer.Length() - 1;
      myFlags.InsertAfter(anIndex, aPrevFlag);
    }
  }
  
  return Standard_True;
}

Standard_Boolean IntTools_MarkedRangeSet::InsertRange(const IntTools_Range&  theRange,
						      const Standard_Integer theFlag,
						      const Standard_Integer theIndex) 
{
  return InsertRange(theRange.First(), theRange.Last(), theFlag, theIndex);
}

void IntTools_MarkedRangeSet::SetFlag(const Standard_Integer theIndex,
				      const Standard_Integer theFlag) 
{
  myFlags.SetValue(theIndex, theFlag);
}

Standard_Integer IntTools_MarkedRangeSet::Flag(const Standard_Integer theIndex) const
{
  return myFlags(theIndex);
}

const TColStd_SequenceOfInteger& IntTools_MarkedRangeSet::GetIndices(const Standard_Real theValue)
{
  myFoundIndices.Clear();

  if(theValue < myRangeSetStorer(1))
    return myFoundIndices;
  else {
    Standard_Boolean found = Standard_False;

    for(Standard_Integer i = 2; i <= myRangeSetStorer.Length(); i++) {
      if(found) {
	if(theValue >= myRangeSetStorer(i-1)) {
	  myFoundIndices.Append(i-1);
	}
	else {
	  break;
	}
      }
      else {
	if(theValue <= myRangeSetStorer(i)) {
	  myFoundIndices.Append(i-1);
	  found = Standard_True;
	}
	else {
	  if(found) {
	    break;
	}
	}
      }
    }
  }
  return myFoundIndices;
}


Standard_Integer IntTools_MarkedRangeSet::GetIndex(const Standard_Real theValue) const
{
  Standard_Integer anIndex = 0;

  if(theValue < myRangeSetStorer(1))
    anIndex = 0;
  else {
    for(Standard_Integer i = 2; i <= myRangeSetStorer.Length(); i++) {
      if(theValue <= myRangeSetStorer(i)) {
	anIndex = i-1;
	break;
      }
    }
  }

  return anIndex;
}

Standard_Integer IntTools_MarkedRangeSet::GetIndex(const Standard_Real theValue,
						   const Standard_Boolean UseLower) const
{
  Standard_Integer anIndex = 0;

  if((UseLower && theValue < myRangeSetStorer(1)) ||
     (!UseLower && theValue <= myRangeSetStorer(1)))
    anIndex = 0;
  else {
    for(Standard_Integer i = 2; i <= myRangeSetStorer.Length(); i++) {
      if((UseLower && theValue < myRangeSetStorer(i)) ||
	 (!UseLower && theValue <= myRangeSetStorer(i))) {
	anIndex = i-1;
	break;
      }
    }
  }
  return anIndex;
}

IntTools_Range IntTools_MarkedRangeSet::Range(const Standard_Integer theIndex) const
{
  IntTools_Range aRange(myRangeSetStorer(theIndex), myRangeSetStorer(theIndex+1));
  return aRange;
}
