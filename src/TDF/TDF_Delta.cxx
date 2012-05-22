// Created by: DAUTRY Philippe
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

//      	-------------

// Version:	0.0
//Version	Date		Purpose
//		0.0	Sep  8 1997	Creation



#include <TDF_Delta.ixx>

#include <TDF_LabelMap.hxx>
#include <TDF_ListIteratorOfAttributeDeltaList.hxx>
#include <TDF_ListIteratorOfLabelList.hxx>
#include <TDF_MapIteratorOfLabelMap.hxx>

#ifdef DEB
#include <Standard_ConstructionError.hxx>
#endif

#undef DEB_DELTA

//=======================================================================
//function : TDF_Delta
//purpose  : 
//=======================================================================

TDF_Delta::TDF_Delta() 
: myBeginTime(0),
  myEndTime(0)
{}


//=======================================================================
//function : Validity
//purpose  : 
//=======================================================================

void TDF_Delta::Validity
(const Standard_Integer aBeginTime,
 const Standard_Integer anEndTime)
{
  myBeginTime   = aBeginTime;
  myEndTime     = anEndTime;
}


//=======================================================================
//function : AddAttributeDelta
//purpose  : 
//=======================================================================

void TDF_Delta::AddAttributeDelta
(const Handle(TDF_AttributeDelta)& anAttributeDelta)
{ if (!anAttributeDelta.IsNull()) myAttDeltaList.Append(anAttributeDelta); }


//=======================================================================
//function : BeforeOrAfterApply
//purpose  : 
//=======================================================================

void TDF_Delta::BeforeOrAfterApply(const Standard_Boolean before) const
{
  TDF_AttributeDeltaList ADlist;
//  for (TDF_ListIteratorOfAttributeDeltaList itr(myAttDeltaList);
  TDF_ListIteratorOfAttributeDeltaList itr(myAttDeltaList) ;
  for ( ; itr.More(); itr.Next()) ADlist.Append(itr.Value());

  Handle(TDF_AttributeDelta) attDelta;
  Handle(TDF_Attribute) att;

  Standard_Boolean noDeadLock = Standard_True;
  Standard_Integer nbAD = ADlist.Extent();
  Standard_Boolean next;
  while (noDeadLock && (nbAD != 0)) {
    itr.Initialize(ADlist);
    while (itr.More()) {
      next = Standard_True;
      attDelta = itr.Value();
      att = attDelta->Attribute();
      if (before)
	next = !att->BeforeUndo(attDelta);
      else
	next = !att->AfterUndo(attDelta);

      if (next)
	itr.Next();
      else
	ADlist.Remove(itr);
    }
    noDeadLock = (nbAD > ADlist.Extent());
    nbAD = ADlist.Extent();
  }

  if (!noDeadLock) {
#ifdef DEB
    if (before) cout<<"Before"; else cout<<"After";
    cout<<"Undo(): dead lock between these attributes:"<<endl;
    for (itr.Initialize(ADlist); itr.More(); itr.Next()) {
      cout<<"AttributeDelta type = "<<itr.Value()->DynamicType()->Name();
      cout<<"  Attribute type = "<<itr.Value()->Attribute()->DynamicType()->Name()<<endl;;
    if (before)
      Standard_ConstructionError::Raise("BeforeUndo(): dead lock.");
    else
      Standard_ConstructionError::Raise("AfterUndo(): dead lock.");
    }
#endif
    for (itr.Initialize(ADlist); itr.More(); itr.Next()) {
      attDelta = itr.Value();
      att = attDelta->Attribute();
      if (before)
	att->BeforeUndo(attDelta,Standard_True);
      else
	att->AfterUndo(attDelta,Standard_True);
    }
  }
}


//=======================================================================
//function : Apply
//purpose  : 
//=======================================================================

void TDF_Delta::Apply()
{
  TDF_ListIteratorOfAttributeDeltaList itr;
  for (itr.Initialize(myAttDeltaList); itr.More(); itr.Next()) {
    const Handle(TDF_AttributeDelta)& attDelta = itr.Value();
    attDelta->Apply();
  }
}


//=======================================================================
//function : Labels
//purpose  : 
//=======================================================================

void TDF_Delta::Labels(TDF_LabelList& aLabelList) const
{
  TDF_LabelMap labMap;
  // If <aLabelList> is not empty...
#ifdef DEB_DELTA
  Standard_Boolean inList;
  if (aLabelList.Extent() > 0) cout<<"Previously added as modified label(s) ";
#endif
  for (TDF_ListIteratorOfLabelList it1(aLabelList);
       it1.More(); it1.Next()) {
#ifdef DEB_DELTA
    const TDF_Label& lab1 = it1.Value();
    inList = labMap.Add(lab1);
    if (!inList) {
      lab1.EntryDump(cout);cout<<" | ";
    }
#endif
  }
#ifdef DEB_DELTA
  cout<<endl;
#endif

  // New labels to add.
#ifdef DEB_DELTA
  if (myAttDeltaList.Extent() > 0) cout<<"New added as modified label(s) ";
#endif
  for (TDF_ListIteratorOfAttributeDeltaList it2(myAttDeltaList);
       it2.More();
       it2.Next()) {
#ifdef DEB_DELTA
    const TDF_Label& lab1 = it2.Value()->Label();
    inList = labMap.Add(lab1);
    if (!inList) {
      lab1.EntryDump(cout);cout<<" | ";
    }
#endif
  }
#ifdef DEB_DELTA
  cout<<endl;
#endif

  // Now put labels into <aLabelList>.
  aLabelList.Clear();
  for (TDF_MapIteratorOfLabelMap it3(labMap);
       it3.More(); it3.Next()) {
    aLabelList.Append(it3.Key());
  }
}

//=======================================================================
//function : Dump
//purpose  : 
//=======================================================================

void TDF_Delta::Dump(Standard_OStream& OS) const
{
  OS<<"DELTA available from time \t#"<<myBeginTime<<" to time \t#"<<myEndTime<<endl;
  Standard_Integer n = 0;
//  for (TDF_ListIteratorOfAttributeDeltaList itr(myAttDeltaList);
  TDF_ListIteratorOfAttributeDeltaList itr(myAttDeltaList) ;
  for ( ; itr.More(); itr.Next()) ++n;
  OS<<"Nb Attribute Delta(s): "<<n<<endl;
  for (itr.Initialize(myAttDeltaList); itr.More(); itr.Next()) {
    const Handle(TDF_AttributeDelta)& attDelta = itr.Value();
    OS<<"| "; attDelta->Dump(OS); OS<<endl;
  }
}
