// Created on: 2007-06-27
// Created by: Sergey ZARITCHNY
// Copyright (c) 2007-2012 OPEN CASCADE SAS
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


#include <MDataStd_NamedDataRetrievalDriver.ixx>
#include <PDataStd_NamedData.hxx>
#include <TDataStd_NamedData.hxx>
#include <MDataStd.hxx>
#include <CDM_MessageDriver.hxx>
#include <PCollection_HExtendedString.hxx>
#include <TColStd_DataMapOfStringInteger.hxx>
#include <TDataStd_DataMapOfStringReal.hxx>
#include <TDataStd_DataMapOfStringByte.hxx>
#include <TDataStd_DataMapOfStringString.hxx>
#include <TDataStd_DataMapOfStringHArray1OfInteger.hxx>
#include <TDataStd_DataMapOfStringHArray1OfReal.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <PColStd_HArray1OfInteger.hxx>
#include <PColStd_HArray1OfReal.hxx>

//=======================================================================
//function : MDataStd_NamedDataRetrievalDriver
//purpose  : 
//=======================================================================
MDataStd_NamedDataRetrievalDriver::MDataStd_NamedDataRetrievalDriver(const Handle(CDM_MessageDriver)& theMsgDriver):MDF_ARDriver(theMsgDriver)
{

}

//=======================================================================
//function : VersionNumber
//purpose  : 
//=======================================================================
Standard_Integer MDataStd_NamedDataRetrievalDriver::VersionNumber() const
{ 
  return 0; 
}

//=======================================================================
//function : SourceType
//purpose  : 
//=======================================================================
Handle(Standard_Type) MDataStd_NamedDataRetrievalDriver::SourceType() const
{
  static Handle(Standard_Type) sourceType = STANDARD_TYPE(PDataStd_NamedData);
  return sourceType;
}

//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================
Handle(TDF_Attribute) MDataStd_NamedDataRetrievalDriver::NewEmpty () const 
{
  return new TDataStd_NamedData();
}

//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================
void MDataStd_NamedDataRetrievalDriver::Paste(const Handle(PDF_Attribute)& Source,
						   const Handle(TDF_Attribute)& Target,
						   const Handle(MDF_RRelocationTable)& ) const
{
  Handle(PDataStd_NamedData) S = Handle(PDataStd_NamedData)::DownCast (Source);
  Handle(TDataStd_NamedData) T = Handle(TDataStd_NamedData)::DownCast (Target);
  if(S.IsNull() || T.IsNull()) return;
  Standard_Integer i;
#ifdef MDTV_DEB
  cout << "Start: " <<S->LowerI() << " " <<S->UpperI()<<"\t"<<S->LowerR() << " " <<S->UpperR();
  cout << "\t"<<S->LowerS() << " " <<S->UpperS()<< "\t"<<S->LowerB() << " " <<S->UpperB();
  cout << "\t"<<S->LowerAI() << " " <<S->UpperAI()<<"\t"<<S->LowerAR() << " " <<S->UpperAR()<<endl;
#endif
  if(S->HasIntegers()) {
    TColStd_DataMapOfStringInteger aMap;
    for(i=S->LowerI();i<=S->UpperI();i++) {
      Handle(PCollection_HExtendedString) aPKey;
      Standard_Integer aValue = S->IntDataItemValue(i, aPKey);
      const TCollection_ExtendedString& aKey = aPKey->Convert();
      aMap.Bind(aKey, aValue);
    }
    T->ChangeIntegers(aMap);
    }

  if(S->HasReals()) {
    TDataStd_DataMapOfStringReal aMap;
    for(i=S->LowerR();i<=S->UpperR();i++) {
      Handle(PCollection_HExtendedString) aPKey;
      Standard_Real aValue = S->RealDataItemValue(i, aPKey);
      const TCollection_ExtendedString& aKey = aPKey->Convert();
      aMap.Bind(aKey, aValue);
    }
    T->ChangeReals(aMap);
  }
  if(S->HasStrings()) {
    TDataStd_DataMapOfStringString aMap;
    for(i=S->LowerS();i<=S->UpperS();i++) {
      Handle(PCollection_HExtendedString) aPKey;
      const Handle(PCollection_HExtendedString)& aPValue = S->StrDataItemValue(i, aPKey);
      const TCollection_ExtendedString& aKey = aPKey->Convert();
      const TCollection_ExtendedString& aValue = aPValue->Convert();
      aMap.Bind(aKey, aValue);
    }
    T->ChangeStrings(aMap);
  }
  if(S->HasBytes()) {
    TDataStd_DataMapOfStringByte aMap;
    for(i=S->LowerB();i<=S->UpperB();i++) {
      Handle(PCollection_HExtendedString) aPKey;
      Standard_Byte aValue = S->ByteDataItemValue(i, aPKey);
      const TCollection_ExtendedString& aKey = aPKey->Convert();
      aMap.Bind(aKey, aValue);
    }
    T->ChangeBytes(aMap);
  }
  if(S->HasArraysOfIntegers()) {
    TDataStd_DataMapOfStringHArray1OfInteger aMap;
    for(i=S->LowerAI();i<=S->UpperAI();i++) {
      Handle(PCollection_HExtendedString) aPKey;
      Handle(PColStd_HArray1OfInteger) aPValue = S->ArrIntDataItemValue(i, aPKey);
      const TCollection_ExtendedString& aKey = aPKey->Convert();
      Handle(TColStd_HArray1OfInteger) anAr;
      if (aPValue.IsNull()) continue;
      Standard_Integer lower = aPValue->Lower(), upper = aPValue->Upper();
      anAr = new TColStd_HArray1OfInteger(lower, upper);
      for (Standard_Integer j = lower; j <= upper; j++)
	anAr->SetValue(j, aPValue->Value(j));
      aMap.Bind(aKey, anAr);
    }
    T->ChangeArraysOfIntegers(aMap);
  }
  if(S->HasArraysOfReals()) {
    TDataStd_DataMapOfStringHArray1OfReal aMap;
    for(i=S->LowerAR();i<=S->UpperAR();i++) {
      Handle(PCollection_HExtendedString) aPKey;
      Handle(PColStd_HArray1OfReal) aPValue = S->ArrRealDataItemValue(i, aPKey);
      const TCollection_ExtendedString& aKey = aPKey->Convert();
      Handle(TColStd_HArray1OfReal) anAr;
      if (aPValue.IsNull()) continue;
      Standard_Integer lower = aPValue->Lower(), upper = aPValue->Upper();
      anAr = new TColStd_HArray1OfReal(lower, upper);
      for (Standard_Integer j = lower; j <= upper; j++)
	anAr->SetValue(j, aPValue->Value(j));
      aMap.Bind(aKey, anAr);
    }
    T->ChangeArraysOfReals(aMap);
  }
}
