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

//      	-----------------------

// Version:	0.0
//Version	Date		Purpose
//		0.0	Mar  7 1997	Creation



#include <TDF_RelocationTable.ixx>

#include <TDF_DataMapIteratorOfAttributeDataMap.hxx>
#include <TDF_DataMapIteratorOfLabelDataMap.hxx>


//=======================================================================
//function : TDF_RelocationTable
//purpose  : 
//=======================================================================

TDF_RelocationTable::TDF_RelocationTable(const Standard_Boolean selfRelocate)
: mySelfRelocate(selfRelocate),myAfterRelocate(Standard_False)
{}


//=======================================================================
//function : SelfRelocate
//purpose  : 
//=======================================================================

void TDF_RelocationTable::SelfRelocate(const Standard_Boolean selfRelocate)
{ mySelfRelocate = selfRelocate; }


//=======================================================================
//function : SelfRelocate
//purpose  : 
//=======================================================================

Standard_Boolean TDF_RelocationTable::SelfRelocate() const
{ return mySelfRelocate; }

//=======================================================================
//function : SelfRelocate
//purpose  : 
//=======================================================================

void TDF_RelocationTable::AfterRelocate(const Standard_Boolean afterRelocate)
{ myAfterRelocate = afterRelocate; }


//=======================================================================
//function : SelfRelocate
//purpose  : 
//=======================================================================

Standard_Boolean TDF_RelocationTable::AfterRelocate() const
{ return myAfterRelocate; }


//=======================================================================
//function : SetRelocation
//purpose  : Sets the relocation value of <aSourceLabel>
//           to <aTargetLabel>.
//=======================================================================

void TDF_RelocationTable::SetRelocation
(const TDF_Label& aSourceLabel,
 const TDF_Label& aTargetLabel) 
{
  if (!myLabelTable.IsBound(aSourceLabel))
    myLabelTable.Bind(aSourceLabel,aTargetLabel);
}


//=======================================================================
//function : HasRelocation
//purpose  : Finds the relocation value of <aSourceLabel>
//           and returns it into <aTargetLabel>.
//=======================================================================

Standard_Boolean TDF_RelocationTable::HasRelocation
(const TDF_Label& aSourceLabel,
 TDF_Label& aTargetLabel) const
{
  aTargetLabel.Nullify();
  if (myLabelTable.IsBound(aSourceLabel)) {
    aTargetLabel = myLabelTable.Find(aSourceLabel);
    return Standard_True;
  }
  if (mySelfRelocate) {
    aTargetLabel = aSourceLabel;
    return !myAfterRelocate;
  }
  return Standard_False;
}


//=======================================================================
//function : SetRelocation
//purpose  : Sets the relocation value of <aSourceAttribute>
//           to <aTargetAttribute>.
//=======================================================================

void TDF_RelocationTable::SetRelocation
(const Handle(TDF_Attribute)& aSourceAttribute,
 const Handle(TDF_Attribute)& aTargetAttribute) 
{
  if (!myAttributeTable.IsBound(aSourceAttribute))
    myAttributeTable.Bind(aSourceAttribute,aTargetAttribute);
}


//=======================================================================
//function : HasRelocation
//purpose  : Finds the relocation value of <aSourceAttribute>
//           and returns it into <aTargetAttribute>.
//=======================================================================

Standard_Boolean TDF_RelocationTable::HasRelocation
(const Handle(TDF_Attribute)& aSourceAttribute,
 Handle(TDF_Attribute)& aTargetAttribute) const
{
  aTargetAttribute.Nullify();
  if (myAttributeTable.IsBound(aSourceAttribute)) {
    aTargetAttribute = myAttributeTable.Find(aSourceAttribute);
    return Standard_True;
  }
  if (mySelfRelocate) {
    aTargetAttribute = aSourceAttribute;
    return !myAfterRelocate;
  }
  return Standard_False;
}


//=======================================================================
//function : SetTransientRelocation
//purpose  : Sets the relocation value of <aSourceTransient>
//           to <aTargetTransient>.
//=======================================================================

void TDF_RelocationTable::SetTransientRelocation
(const Handle(Standard_Transient)& aSourceTransient,
 const Handle(Standard_Transient)& aTargetTransient) 
{
  if (!myTransientTable.Contains(aSourceTransient))
    myTransientTable.Add(aSourceTransient,aTargetTransient);
}


//=======================================================================
//function : HasTransientRelocation
//purpose  : Finds the relocation value of <aSourceTransient>
//           and returns it into <aTargetTransient>.
//=======================================================================

Standard_Boolean TDF_RelocationTable::HasTransientRelocation
(const Handle(Standard_Transient)& aSourceTransient,
 Handle(Standard_Transient)& aTargetTransient) const
{
  aTargetTransient.Nullify();
  if (myTransientTable.Contains(aSourceTransient)) {
    aTargetTransient = myTransientTable.FindFromKey(aSourceTransient);
    return Standard_True;
  }
  if (mySelfRelocate) {
    aTargetTransient = aSourceTransient;
    return !myAfterRelocate;
  }
  return Standard_False;
}


//=======================================================================
//function : Clear
//purpose  : Clears the relocation dictonnary.
//=======================================================================

void TDF_RelocationTable::Clear()
{
  myLabelTable.Clear();
  myAttributeTable.Clear();
  myTransientTable.Clear();
}


//=======================================================================
//function : TargetLabelMap
//purpose  : 
//=======================================================================

void TDF_RelocationTable::TargetLabelMap(TDF_LabelMap& aLabelMap) const
{
  for (TDF_DataMapIteratorOfLabelDataMap itr(myLabelTable);
       itr.More(); itr.Next())
    aLabelMap.Add(itr.Value());
}


//=======================================================================
//function : TargetAttributeMap
//purpose  : 
//=======================================================================

void TDF_RelocationTable::TargetAttributeMap(TDF_AttributeMap& anAttributeMap) const
{
  for (TDF_DataMapIteratorOfAttributeDataMap itr(myAttributeTable);
       itr.More(); itr.Next())
    anAttributeMap.Add(itr.Value());
}


//=======================================================================
//function : LabelTable
//purpose  : 
//=======================================================================

TDF_LabelDataMap& TDF_RelocationTable::LabelTable()
{ return myLabelTable; }


//=======================================================================
//function : AttributeTable
//purpose  : 
//=======================================================================

TDF_AttributeDataMap& TDF_RelocationTable::AttributeTable()
{ return myAttributeTable; }


//=======================================================================
//function : TransientTable
//purpose  : 
//=======================================================================

TColStd_IndexedDataMapOfTransientTransient& TDF_RelocationTable::TransientTable()
{ return myTransientTable; }


//=======================================================================
//function : Dump
//purpose  : 
//=======================================================================

Standard_OStream& TDF_RelocationTable::Dump
(const Standard_Boolean dumpLabels,
 const Standard_Boolean dumpAttributes,
 const Standard_Boolean dumpTransients,
 Standard_OStream& anOS) const
{
  anOS<<"Relocation Table  ";
  if (mySelfRelocate) anOS<<"IS"; else anOS<<"NOT";
  anOS<<" self relocate ";
  if (myAfterRelocate) anOS<<"WITH"; else anOS<<"WITHOUT";
  anOS<<" after relocate"<<endl;
  anOS<<"Nb labels="<<myLabelTable.Extent();
  anOS<<"  Nb attributes="<<myAttributeTable.Extent();
  anOS<<"  Nb transients="<<myTransientTable.Extent()<<endl;

  Standard_Integer nb = 0;
  if (dumpLabels) {
    anOS<<"Label Table:"<<endl;
    for (TDF_DataMapIteratorOfLabelDataMap itr(myLabelTable);
	 itr.More(); itr.Next()) {
      ++nb;
      anOS<<nb<<" ";
      itr.Key().EntryDump(anOS);
      anOS<<"<=>";
      itr.Value().EntryDump(anOS);
      anOS<<"| ";
    }
    cout<<endl;
  }

  nb = 0;
  if (dumpAttributes) {
    anOS<<"Attribute Table:"<<endl;
    for (TDF_DataMapIteratorOfAttributeDataMap itr(myAttributeTable);
	 itr.More(); itr.Next()) {
      ++nb;
      anOS<<nb<<" ";
      itr.Key()->Dump(anOS);
      anOS<<"<=>";
      itr.Value()->Dump(anOS);
      anOS<<"| ";
      anOS<<endl;
    }
  }
  
  if (dumpTransients) {
    anOS<<"Transient Table:"<<myTransientTable.Extent()<<" transient(s) in table."<<endl;
  }

  return anOS;
}
