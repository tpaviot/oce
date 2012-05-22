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

// Modified by rmi, Thu Dec  4 14:24:24 1997
#include <CDF_Store.ixx>
#include <CDF_Session.hxx>
#include <CDF_Application.hxx>
#include <PCDM_StoreStatus.hxx>
#include <CDF_StoreSetNameStatus.hxx>
#include <Standard_ProgramError.hxx>
#include <CDF_MetaDataDriver.hxx>
#include <PCDM_StorageDriver.hxx>
#include <PCDM.hxx>
#include <TCollection_ExtendedString.hxx>
#include <CDM_MetaData.hxx>

#define theMetaDataDriver CDF_Session::CurrentSession()->MetaDataDriver()


static TCollection_ExtendedString blank("");



CDF_Store::CDF_Store() {}
CDF_Store::CDF_Store(const Handle(CDM_Document)& aDocument):myHasSubComponents(Standard_False) {
  
  myMainDocument = aDocument;
  Init();
}

void CDF_Store::Init() {
  
  myCurrentDocument = myMainDocument;
  myList = new CDF_StoreList(myCurrentDocument);

  myIsMainDocument = Standard_True;
  FindDefault();

// getting the subcomponents.
  //
  myIsMainDocument = Standard_False;
  myList->Init();
  for ( myList->Init(); myList->More(); myList->Next()) {
    myCurrentDocument = myList->Value();
    if(myCurrentDocument != myMainDocument) {
      myHasSubComponents  = Standard_True;
      FindDefault();
      
    }
  }
  myIsMainDocument = Standard_True;
  myCurrentDocument = myMainDocument;
}

CDF_TryStoreStatus CDF_Store::Check() {
  if(!PCDM::FindStorageDriver(myMainDocument))  return CDF_TS_NoDriver;

  
  // Checking the subcomponent.
  Handle(CDM_Document) theCurrentDocument;
  myList->Init();
  for ( myList->Init(); myList->More(); myList->Next()) {
    theCurrentDocument = myList->Value();

    if(theCurrentDocument != myMainDocument) {
      if( theCurrentDocument->IsModified()) {
   
	myLastName = theCurrentDocument->Presentation();
	
	if(!PCDM::FindStorageDriver(theCurrentDocument))  return CDF_TS_NoDriver;
	
      }
    }
  }
  return CDF_TS_OK;
}


Standard_ExtString CDF_Store::LastName() const {
  return myLastName.ToExtString();
}

Standard_ExtString CDF_Store::Folder() const {
  static TCollection_ExtendedString retv;
  if(myCurrentDocument->HasRequestedFolder())
    retv =  myCurrentDocument->RequestedFolder();
  else
    retv= blank;
  return retv.ToExtString();
}

Standard_ExtString CDF_Store::Name() const {
  static TCollection_ExtendedString retv;
  retv = myCurrentDocument->RequestedName();
  return retv.ToExtString();
}


Standard_Boolean  CDF_Store::SetFolder(const Standard_ExtString aFolder) {
  TCollection_ExtendedString f(aFolder);
  return SetFolder(f);
}
Standard_Boolean  CDF_Store::SetFolder(const TCollection_ExtendedString& aFolder) {

  TCollection_ExtendedString theFolder(aFolder);
  Standard_Integer l = theFolder.Length();

  // if the last character is the folder separator (which is always the first character)
  // it is removed.
	// This is correct for Unix systems but not for Windows! VMS and MAC? Thomas Haller, 23.11.01
  if(l > 1) {
#ifndef WNT
    if(theFolder.Value(l) == theFolder.Value(1)) theFolder.Trunc(l-1);
#else
	if (theFolder.Value(l) == '/' || theFolder.Value(l) == '\\')
		theFolder.Trunc(l-1);
#endif
  }

  if(theMetaDataDriver->FindFolder(theFolder))  {
    myCurrentDocument->SetRequestedFolder(theFolder);
    return Standard_True;
  }
  return Standard_False;
}


CDF_StoreSetNameStatus CDF_Store::RecheckName () {
   return SetName(myCurrentDocument->RequestedName());
}

CDF_StoreSetNameStatus CDF_Store::SetName(const TCollection_ExtendedString&  aName)
{
  TCollection_ExtendedString theName=theMetaDataDriver->SetName(myCurrentDocument,aName);

  if(myCurrentDocument->IsStored ()) { 
    Handle(CDM_MetaData)  E = myCurrentDocument->MetaData();
    if(   E->Folder() == myCurrentDocument->RequestedFolder() 
       && E->Name()   == theName) return CDF_SSNS_OK;
  }
  
  if(myCurrentDocument->HasRequestedFolder()) {
    if (theMetaDataDriver->Find(myCurrentDocument->RequestedFolder(),theName)) {
      if(theMetaDataDriver->MetaData(myCurrentDocument->RequestedFolder(),theName)->IsRetrieved())
	return CDF_SSNS_OpenDocument;
      else {
	myCurrentDocument->SetRequestedName(theName);
	return CDF_SSNS_ReplacingAnExistentDocument;
      }
    }
  }
  myCurrentDocument->SetRequestedName(theName);
  return  CDF_SSNS_OK;
}
CDF_StoreSetNameStatus CDF_Store::SetName(const Standard_ExtString aName)
{
  TCollection_ExtendedString theName(aName);
  return SetName(theName);
}

void CDF_Store::Realize() {
  Standard_ProgramError_Raise_if(!myList->IsConsistent(),"information are missing");
  Handle(CDM_MetaData) m;
  myText = "";
  myStatus = myList->Store(m,myText);
  if(myStatus==PCDM_SS_OK) myPath = m->Path();
}
Standard_ExtString CDF_Store::Path() const {
  return myPath.ToExtString();
}
Standard_ExtString CDF_Store::MetaDataPath() const {
  static TCollection_ExtendedString retv;
  retv="";
  if(myCurrentDocument->IsStored()) retv=myCurrentDocument->MetaData()->Path();
  return retv.ToExtString();
}
Standard_ExtString CDF_Store::Description() const {
  static TCollection_ExtendedString retv;

  if(myMainDocument->FindDescription())
    retv = myMainDocument->Description();
  else
    retv= blank;

  return retv.ToExtString();
}

Standard_Boolean CDF_Store::IsStored() const {
  return myCurrentDocument->IsStored();
}
Standard_Boolean CDF_Store::IsModified() const {
  return myCurrentDocument->IsModified();
}
Standard_Boolean CDF_Store::CurrentIsConsistent() const {
  if(!myCurrentDocument->IsStored())
    return myCurrentDocument->HasRequestedFolder();
  return Standard_True;
}

Standard_Boolean CDF_Store::IsConsistent() const {
  return myList->IsConsistent();
}
Standard_Boolean CDF_Store::HasAPreviousVersion() const {
  return myCurrentDocument->HasRequestedPreviousVersion();
}

Standard_ExtString CDF_Store::PreviousVersion() const {
  static TCollection_ExtendedString retv;
  if(myCurrentDocument->HasRequestedPreviousVersion())
    retv= myCurrentDocument->RequestedPreviousVersion();
  else
    retv=blank;
  return retv.ToExtString();
}

Standard_Boolean CDF_Store::SetPreviousVersion (const Standard_ExtString aPreviousVersion) {
  if(theMetaDataDriver->HasVersionCapability()) {
    if(myCurrentDocument->HasRequestedFolder()) {
      if(theMetaDataDriver->Find(myCurrentDocument->RequestedFolder(),myCurrentDocument->RequestedName(),aPreviousVersion)){
	
	myCurrentDocument->SetRequestedPreviousVersion(aPreviousVersion);
	return Standard_True;
      }
      else
	return Standard_False;
    }
    else 
      return Standard_False;
  }
  return Standard_True;
}

void CDF_Store::InitComponent() {
   myList->Init();
}

Standard_Boolean CDF_Store::MoreComponent() const {
  return myList->More();
}

void CDF_Store::NextComponent()  {
  myList->Next();
}
void CDF_Store::SetCurrent() {
  myCurrentDocument = myList->Value();
  myIsMainDocument = myCurrentDocument == myMainDocument;


}

Standard_ExtString CDF_Store::Component() const {
  
  static TCollection_ExtendedString retv;
  retv=myList->Value()->Presentation();
  return retv.ToExtString();
}
Standard_Boolean CDF_Store::HasSubComponents () const {
   return myHasSubComponents;
}

void CDF_Store::SetCurrent(const Standard_ExtString aPresentation) {
  myCurrentDocument = CDM_Document::FindFromPresentation(aPresentation);
  myIsMainDocument = myCurrentDocument == myMainDocument;
}
void CDF_Store::SetMain() {
  myCurrentDocument = myMainDocument;
  myIsMainDocument = Standard_True;

}
Standard_Boolean CDF_Store::IsMainDocument() const {
  return myIsMainDocument;
}

CDF_SubComponentStatus CDF_Store::SubComponentStatus(const Standard_ExtString aPresentation) const {
   Handle(CDM_Document) d = CDM_Document::FindFromPresentation(aPresentation);

  if(!d->IsStored()) 
    return d->HasRequestedFolder()? CDF_SCS_Consistent : CDF_SCS_Unconsistent;

  if(d->IsModified()) return CDF_SCS_Modified;
  return CDF_SCS_Stored;
}



PCDM_StoreStatus CDF_Store::StoreStatus() const {
  return myStatus;
}
Standard_ExtString CDF_Store::AssociatedStatusText() const {
  return myText.ToExtString();
}


void CDF_Store::FindDefault() {
  if (!myCurrentDocument->IsStored ()) {
    myCurrentDocument->SetRequestedFolder(CDF_Session::CurrentSession()->CurrentApplication()->DefaultFolder());
//    myCurrentDocument->SetRequestedName(theMetaDataDriver->SetName(myCurrentDocument,myCurrentDocument->Presentation()));
    myCurrentDocument->SetRequestedName(theMetaDataDriver->SetName(myCurrentDocument,myCurrentDocument->RequestedName()));
  }
}
void CDF_Store::SetComment(const Standard_ExtString aComment) {
  myCurrentDocument->SetRequestedComment(aComment);
}

Standard_ExtString CDF_Store::Comment() const {
  static TCollection_ExtendedString retv;
  retv=myCurrentDocument->RequestedComment();
  return retv.ToExtString();
}
