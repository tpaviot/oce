// Created on: 1997-09-17
// Created by: Jean Yves LEBEY
// Copyright (c) 1997-1999 Matra Datavision
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


#include <TopOpeBRepDS_TKI.ixx>
#include <TopOpeBRepDS_define.hxx>
#include <TopOpeBRepDS_EXPORT.hxx>
#include <TopOpeBRepDS.hxx>
#include <Standard_ProgramError.hxx>

// extras define
#include <TopOpeBRepDS_DataMapOfIntegerListOfInterference.hxx>
#include <TopOpeBRepDS_DataMapIteratorOfDataMapOfIntegerListOfInterference.hxx>
#define MDSdmoiloi TopOpeBRepDS_DataMapOfIntegerListOfInterference
#define MDSdmiodmoiloi TopOpeBRepDS_DataMapIteratorOfDataMapOfIntegerListOfInterference
#define MDShaodmoiloi TopOpeBRepDS_HArray1OfDataMapOfIntegerListOfInterference

//=======================================================================
//function : TopOpeBRepDS_TKI
//purpose  : 
//=======================================================================
TopOpeBRepDS_TKI::TopOpeBRepDS_TKI()
{
  Reset();
}

//=======================================================================
//function : Reset
//purpose  : private
//=======================================================================
void TopOpeBRepDS_TKI::Reset()
{
  Standard_Integer ip = (Standard_Integer)TopOpeBRepDS_POINT;
  Standard_Integer is = (Standard_Integer)TopOpeBRepDS_SOLID;
  if (ip > is ) {
    Standard_ProgramError::Raise("TopOpeBRepDS_TKI : enumeration badly ordered");
    return;
  }
  Standard_Integer f = 1;           // first index of table
  Standard_Integer l = f + (is-ip); // last index of table
  mydelta = f - ip;
  // k + mydelta = i in [f,l]; TopOpeBRepDS_POINT,SOLID + mydelta = f,l
  if (myT.IsNull()) myT = new MDShaodmoiloi(f,l);
  Clear();
  myK = TopOpeBRepDS_UNKNOWN;
  myG = 0;
}

//=======================================================================
//function : Clear
//purpose  : 
//=======================================================================
void TopOpeBRepDS_TKI::Clear()
{
  Standard_Integer i=myT->Lower(), n=myT->Upper();
  for (; i<=n; i++) myT->ChangeValue(i).Clear();
}

//=======================================================================
//function : FillOnGeometry
//purpose  : 
//=======================================================================
void TopOpeBRepDS_TKI::FillOnGeometry(const TopOpeBRepDS_ListOfInterference& L)
{
  for(TopOpeBRepDS_ListIteratorOfListOfInterference it(L);it.More();it.Next()) {
    const Handle(TopOpeBRepDS_Interference)& I = it.Value();
    TopOpeBRepDS_Kind GT,ST; Standard_Integer G,S;
    FDS_data(I,GT,G,ST,S);
    Add(GT,G,I);
  }
}

//=======================================================================
//function : FillOnSupport
//purpose  : 
//=======================================================================
void TopOpeBRepDS_TKI::FillOnSupport(const TopOpeBRepDS_ListOfInterference& L)
{
  for(TopOpeBRepDS_ListIteratorOfListOfInterference it(L);it.More();it.Next()) {
    const Handle(TopOpeBRepDS_Interference)& I = it.Value();
    TopOpeBRepDS_Kind GT,ST; Standard_Integer G,S;
    FDS_data(I,GT,G,ST,S);
    Add(ST,S,I);
  }
}

//=======================================================================
//function : IsBound
//purpose  : 
//=======================================================================
Standard_Boolean TopOpeBRepDS_TKI::IsBound(const TopOpeBRepDS_Kind K,const Standard_Integer G) const
{
  if (!IsValidKG(K,G)) return Standard_False;
  Standard_Integer TI = KindToTableIndex(K);
  Standard_Boolean in = myT->Value(TI).IsBound(G);
  return in;
}

//=======================================================================
//function : Interferences
//purpose  : 
//=======================================================================
const TopOpeBRepDS_ListOfInterference& TopOpeBRepDS_TKI::Interferences
(const TopOpeBRepDS_Kind K,const Standard_Integer G) const
{
  Standard_Boolean in = IsBound(K,G);
  Standard_Integer TI = KindToTableIndex(K);
  if ( in ) return myT->Value(TI).Find(G);
  return myEmptyLOI;
}

//=======================================================================
//function : ChangeInterferences
//purpose  : 
//=======================================================================
TopOpeBRepDS_ListOfInterference& TopOpeBRepDS_TKI::ChangeInterferences(const TopOpeBRepDS_Kind K,const Standard_Integer G)
{
  Standard_Boolean in = IsBound(K,G);
  Standard_Integer TI = KindToTableIndex(K);
  if ( in ) return myT->ChangeValue(TI).ChangeFind(G);
  return myEmptyLOI;
}

//=======================================================================
//function : HasInterferences
//purpose  : 
//=======================================================================
Standard_Boolean TopOpeBRepDS_TKI::HasInterferences(const TopOpeBRepDS_Kind K,const Standard_Integer G) const
{
  Standard_Boolean has = IsBound(K,G);
  if ( has ) {
    const TopOpeBRepDS_ListOfInterference& loi = Interferences(K,G);
    Standard_Integer l = loi.Extent();
    has = (l != 0 ) ;
  }
  return has;
}

//=======================================================================
//function : Add
//purpose  : 
//=======================================================================
void TopOpeBRepDS_TKI::Add(const TopOpeBRepDS_Kind K,const Standard_Integer G)
{
  Standard_Boolean ok = IsValidKG(K,G);
  if (!ok) {
    Standard_ProgramError::Raise("TopOpeBRepDS_TKI : Add K G");
    return;
  }

  Standard_Boolean in = IsBound(K,G);
  Standard_Integer TI = KindToTableIndex(K);
  TopOpeBRepDS_ListOfInterference thelist;
  if ( !in ) 
    myT->ChangeValue(TI).Bind(G, thelist);
}

//=======================================================================
//function : Add
//purpose  : 
//=======================================================================
void TopOpeBRepDS_TKI::Add(const TopOpeBRepDS_Kind K,const Standard_Integer G,const Handle(TopOpeBRepDS_Interference)& HI)
{
  Standard_Boolean ok = IsValidKG(K,G);
  if (!ok) Standard_ProgramError::Raise("TopOpeBRepDS_TKI : Add K G HI");

  Add(K,G);
  ChangeInterferences(K,G).Append(HI);
}

//=======================================================================
//function : DumpTKI
//purpose  : 
//=======================================================================
void TopOpeBRepDS_TKI::DumpTKI
(const TCollection_AsciiString& s1,const TCollection_AsciiString& s2) const
{
  if (myT.IsNull()) return;
  cout<<s1;
  for (Standard_Integer i=myT->Lower();i<=myT->Upper();i++) {
    TopOpeBRepDS_Kind k = TableIndexToKind(i);
    DumpTKI(k);
  }
  cout<<s2;
  cout.flush();
}

//=======================================================================
//function : DumpTKI
//purpose  : 
//=======================================================================
void TopOpeBRepDS_TKI::DumpTKI
(const TopOpeBRepDS_Kind K,const TCollection_AsciiString&,const TCollection_AsciiString&) const
{
  if (myT.IsNull()) return;
  Standard_Integer TI = KindToTableIndex(K);
  const MDSdmoiloi& M = myT->Value(TI);
  for (MDSdmiodmoiloi it(M);it.More();it.Next()) {
    Standard_Integer G = it.Key();
    DumpTKI(K,G,"","\n");
  }
}

//=======================================================================
//function : DumpTKI
//purpose  : 
//=======================================================================
void TopOpeBRepDS_TKI::DumpTKI
(const TopOpeBRepDS_Kind K,const Standard_Integer G,const TCollection_AsciiString& s1,const TCollection_AsciiString& s2) const
{
  if (!HasInterferences(K,G)) return;
  const TopOpeBRepDS_ListOfInterference& loi = Interferences(K,G);
  DumpTKI(K,G,loi,s1,s2);
}

//=======================================================================
//function : DumpTKI
//purpose  : 
//=======================================================================
void TopOpeBRepDS_TKI::DumpTKI
(const TopOpeBRepDS_Kind K,const Standard_Integer G,const TopOpeBRepDS_ListOfInterference& L,const TCollection_AsciiString& s1,const TCollection_AsciiString& s2) const
{
  if (!HasInterferences(K,G)) return;
  TCollection_AsciiString s; 
  if (s1.Length()) s = s1;
  else s = TopOpeBRepDS::SPrint(K,G,"at "," : ");
  TCollection_AsciiString sb(s.Length(),' ');
  Standard_Integer i=0;
  for (TopOpeBRepDS_ListIteratorOfListOfInterference it(L);it.More();it.Next(),i++) {
    if (i) it.Value()->Dump(cout,sb,s2);
    else   it.Value()->Dump(cout,s,s2);
  }
}

//=======================================================================
//function : DumpTKIIterator
//purpose  : 
//=======================================================================
void TopOpeBRepDS_TKI::DumpTKIIterator(const TCollection_AsciiString& s1,const TCollection_AsciiString& s2)
{
  cout<<s1;
  Init();
  while (More()) {
    TopOpeBRepDS_Kind K;Standard_Integer G; const TopOpeBRepDS_ListOfInterference& L = Value(K,G);
    DumpTKI(K,G,L,"","\n");
    Next();
  }
  cout<<s2;
  cout.flush();
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================
void TopOpeBRepDS_TKI::Init()
{
  myK = TopOpeBRepDS_UNKNOWN;
  myG = 0;
  if (myT.IsNull()) return;
  myTI = myT->Lower(); myK = TableIndexToKind(myTI);
  myITM.Initialize(myT->Value(myTI));
  Find();
}

//=======================================================================
//function : More
//purpose  : 
//=======================================================================
Standard_Boolean TopOpeBRepDS_TKI::More() const 
{
  Standard_Boolean b = IsValidKG(myK,myG);
  return b;
}

//=======================================================================
//function : Next
//purpose  : 
//=======================================================================
void TopOpeBRepDS_TKI::Next()
{
  if ( MoreITM() ) {
    NextITM();
    Find();
  }
  else if ( MoreTI() ) {
    NextTI();
    if (MoreTI()) {
      myITM.Initialize(myT->Value(myTI));
    }
    Find();
  }
}

//=======================================================================
//function : Value
//purpose  : 
//=======================================================================
const TopOpeBRepDS_ListOfInterference& TopOpeBRepDS_TKI::Value(TopOpeBRepDS_Kind& K,Standard_Integer& G) const
{
  if ( !More() ) return myEmptyLOI;
  K = myK; G = myG;
  return Interferences(K,G);
}

//=======================================================================
//function : ChangeValue
//purpose  : 
//=======================================================================
TopOpeBRepDS_ListOfInterference& TopOpeBRepDS_TKI::ChangeValue(TopOpeBRepDS_Kind& K,Standard_Integer& G)
{
  if ( !More() ) return myEmptyLOI;
  K = myK; G = myG;
  return ChangeInterferences(K,G);
}

//=======================================================================
//function : MoreTI
//purpose  : 
//=======================================================================
Standard_Boolean TopOpeBRepDS_TKI::MoreTI() const 
{
  Standard_Boolean b = IsValidTI(myTI);
  return b;
}

//=======================================================================
//function : NextTI
//purpose  : 
//=======================================================================
void TopOpeBRepDS_TKI::NextTI()
{
  myTI = myTI + 1; myK = TableIndexToKind(myTI);
}

//=======================================================================
//function : MoreITM
//purpose  : 
//=======================================================================
Standard_Boolean TopOpeBRepDS_TKI::MoreITM() const 
{
  Standard_Boolean b = myITM.More();
  return b;
}

//=======================================================================
//function : FindITM
//purpose  : 
//=======================================================================
void TopOpeBRepDS_TKI::FindITM()
{
  Standard_Boolean f = Standard_False;
  while (MoreITM()) {
    myG = myITM.Key();
    f = HasInterferences(myK,myG);
    if (f) break;
    else myITM.Next();
  }
}

//=======================================================================
//function : NextITM
//purpose  : 
//=======================================================================
void TopOpeBRepDS_TKI::NextITM()
{
  if ( !MoreITM() ) return;
  myITM.Next();
  FindITM();
}

//=======================================================================
//function : Find
//purpose  : 
//=======================================================================
void TopOpeBRepDS_TKI::Find()
{
  Standard_Boolean f = Standard_False;
  while (MoreTI()) {
    while (MoreITM()) {
      FindITM();
      f = HasInterferences(myK,myG);
      if (f) break;
    }
    if (f) break;
    else {
      NextTI();
      if (MoreTI()) {
	myITM.Initialize(myT->Value(myTI));
      }
    }
  }
}

//=======================================================================
//function : KindToTableIndex
//purpose  : private
//=======================================================================
Standard_Integer TopOpeBRepDS_TKI::KindToTableIndex(const TopOpeBRepDS_Kind K) const
{
  // K(Kind) + mydelta = TI(integer) = index in myT
  Standard_Integer TI = (Standard_Integer)K + mydelta;
  return TI;
}

//=======================================================================
//function : TableIndexToKind
//purpose  : private
//=======================================================================
TopOpeBRepDS_Kind TopOpeBRepDS_TKI::TableIndexToKind(const Standard_Integer TI) const
{
  // K(Kind) + mydelta = TI(integer) = index in myT
  TopOpeBRepDS_Kind K = (TopOpeBRepDS_Kind)(TI - mydelta);
  return K;
}

//=======================================================================
//function : IsValidTI
//purpose  : private
//=======================================================================
Standard_Boolean TopOpeBRepDS_TKI::IsValidTI(const Standard_Integer TI) const
{
  if ( myT.IsNull() ) return Standard_False;
  Standard_Boolean nok = ( TI < myT->Lower() || TI > myT->Upper() );
  return !nok;
}

//=======================================================================
//function : IsValidK
//purpose  : private
//=======================================================================
Standard_Boolean TopOpeBRepDS_TKI::IsValidK(const TopOpeBRepDS_Kind K) const
{
  Standard_Boolean nok = ( K < TopOpeBRepDS_POINT || K > TopOpeBRepDS_SOLID );
  return !nok;
}

//=======================================================================
//function : IsValidG
//purpose  : private
//=======================================================================
Standard_Boolean TopOpeBRepDS_TKI::IsValidG(const Standard_Integer G) const
{
  Standard_Boolean nok = (G <= 0);
  return !nok;
}

//=======================================================================
//function : IsValidKG
//purpose  : private
//=======================================================================
Standard_Boolean TopOpeBRepDS_TKI::IsValidKG(const TopOpeBRepDS_Kind K,const Standard_Integer G) const
{
  Standard_Boolean nok = (!IsValidK(K) || !IsValidG(G));
  return !nok;
}
