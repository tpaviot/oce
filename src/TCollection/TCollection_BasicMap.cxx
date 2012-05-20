// Created on: 1993-02-26
// Created by: Remi LEQUETTE
// Copyright (c) 1993-1999 Matra Datavision
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



#ifdef HAVE_CONFIG_H
# include <oce-config.h>
#endif
#include <TCollection_BasicMap.ixx>
#include <TCollection.hxx>
#include <TCollection_BasicMapIterator.hxx>
#include <TCollection_MapNode.hxx>
#include <Standard_Stream.hxx>

//=======================================================================
//function : TCollection_BasicMap
//purpose  : 
//=======================================================================

TCollection_BasicMap::TCollection_BasicMap(const Standard_Integer NbBuckets, 
					   const Standard_Boolean single) :
       myData1(NULL),
       myData2(NULL),
       isDouble(!single),
       mySaturated(Standard_False),
       myNbBuckets(NbBuckets),
       mySize(0)
{
}


//=======================================================================
//function : BeginResize
//purpose  : 
//=======================================================================

Standard_Boolean  TCollection_BasicMap::BeginResize
  (const Standard_Integer NbBuckets,
   Standard_Integer& N,
   Standard_Address& data1,
   Standard_Address& data2) const 
{
  if (mySaturated) return Standard_False;
  N = TCollection::NextPrimeForMap(NbBuckets);
  if (N <= myNbBuckets) {
    if (IsEmpty())
      N = myNbBuckets;
    else
      return Standard_False;
  }
  data1 = Standard::Allocate((N+1)*sizeof(TCollection_MapNodePtr));
  memset(data1, 0, (N+1)*sizeof(TCollection_MapNodePtr));
  if (isDouble) {
    data2 = Standard::Allocate((N+1)*sizeof(TCollection_MapNodePtr));
    memset(data2, 0, (N+1)*sizeof(TCollection_MapNodePtr));
  }
  else
    data2 = NULL;
  return Standard_True;
}


//=======================================================================
//function : EndResize
//purpose  : 
//=======================================================================

void  TCollection_BasicMap::EndResize(const Standard_Integer NbBuckets,
				      const Standard_Integer N,
				      const Standard_Address data1,
				      const Standard_Address data2)
{
  Standard::Free(myData1);
  Standard::Free(myData2);
  myNbBuckets = N;
  mySaturated = myNbBuckets <= NbBuckets;
  myData1 = data1;
  myData2 = data2;
}


//=======================================================================
//function : Destroy
//purpose  : 
//=======================================================================

void  TCollection_BasicMap::Destroy()
{
  mySize = 0;
  mySaturated = Standard_False;
  Standard::Free(myData1);
  Standard::Free(myData2);
  myData1 = myData2 = NULL;
}


//=======================================================================
//function : Statistics
//purpose  : 
//=======================================================================

void TCollection_BasicMap::Statistics(Standard_OStream& S) const
{
  S <<"\nMap Statistics\n---------------\n\n";
  S <<"This Map has "<<myNbBuckets<<" Buckets and "<<mySize<<" Keys\n\n";
  if (mySaturated) S<<"The maximum number of Buckets is reached\n";
  
  if (mySize == 0) return;

  // compute statistics on 1
  Standard_Integer * sizes = new Standard_Integer [mySize+1];
  Standard_Integer i,l,nb;
  TCollection_MapNode* p;
  TCollection_MapNode** data;
  
  S << "\nStatistics for the first Key\n";
  for (i = 0; i <= mySize; i++) sizes[i] = 0;
  data = (TCollection_MapNode**) myData1;
  nb = 0;
  for (i = 0; i <= myNbBuckets; i++) {
    l = 0;
    p = data[i];
    if (p) nb++;
    while (p) {
      l++;
      p = p->Next();
    }
    sizes[l]++;
  }

  // display results
  l = 0;
  for (i = 0; i<= mySize; i++) {
    if (sizes[i] > 0) {
      l += sizes[i] * i;
      S << setw(5) << sizes[i] <<" buckets of size "<<i<<"\n";
    }
  }

  Standard_Real mean = ((Standard_Real) l) / ((Standard_Real) nb);
  S<<"\n\nMean of length : "<<mean<<"\n";

  delete [] sizes;
}
