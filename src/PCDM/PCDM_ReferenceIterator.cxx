// Created on: 1997-12-01
// Created by: Jean-Louis Frenkel
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

#include <PCDM_ReferenceIterator.ixx>
#include <Storage_Data.hxx>
#include <UTL.hxx>
#include <CDM_Document.hxx>
#include <CDM_Application.hxx>
#include <PCDM_RetrievalDriver.hxx>
#include <PCDM_Reference.hxx>
#include <OSD_Path.hxx>

#ifdef WNT
# include <tchar.h>
#endif  // WNT

//=======================================================================
//function : PCDM_ReferenceIterator
//purpose  : 
//=======================================================================

PCDM_ReferenceIterator::PCDM_ReferenceIterator (const Handle(CDM_MessageDriver)& theMsgDriver) {
  myMessageDriver = theMsgDriver;
}

//=======================================================================
//function : LoadReferences
//purpose  : 
//=======================================================================

void PCDM_ReferenceIterator::LoadReferences(const Handle(CDM_Document)& aDocument, 
					    const Handle(CDM_MetaData)& aMetaData, 
					    const Handle(CDM_Application)& anApplication, 
					    const Standard_Boolean UseStorageConfiguration) {
  for (Init(aMetaData);More();Next()) {
    aDocument->CreateReference(MetaData(UseStorageConfiguration),ReferenceIdentifier(),
			       anApplication,DocumentVersion(),UseStorageConfiguration);
  }
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void PCDM_ReferenceIterator::Init(const Handle(CDM_MetaData)& theMetaData) {

  myReferences.Clear();
  // mod. by szy
  PCDM_RetrievalDriver::References(theMetaData->FileName(), myReferences, 
    myMessageDriver);
  myIterator=1;  
}

//=======================================================================
//function : More
//purpose  : 
//=======================================================================

Standard_Boolean PCDM_ReferenceIterator::More() const {
  return myIterator <= myReferences.Length();
}

//=======================================================================
//function : Next
//purpose  : 
//=======================================================================

void PCDM_ReferenceIterator::Next() {
  myIterator++;
}

//=======================================================================
//function : MetaData
//purpose  : 
//=======================================================================

Handle(CDM_MetaData) PCDM_ReferenceIterator::MetaData(const Standard_Boolean ) const {
  
  TCollection_ExtendedString theFolder,theName;
  TCollection_ExtendedString theFile=myReferences(myIterator).FileName();
  TCollection_ExtendedString f(theFile);
#ifndef WNT
  
  Standard_Integer i= f.SearchFromEnd("/");
  TCollection_ExtendedString n = f.Split(i); 
  f.Trunc(f.Length()-1);
  theFolder = f;
  theName = n;
#else
  OSD_Path p = UTL::Path(f);
  Standard_ExtCharacter      chr;
  TCollection_ExtendedString dir, dirRet, name;
  
  dir = UTL::Disk(p);
  dir += UTL::Trek(p);
  
  for ( int i = 1; i <= dir.Length (); ++i ) {
    
    chr = dir.Value ( i );
    
    switch ( chr ) {
      
    case _TEXT( '|' ):
      dirRet += _TEXT( "/" );
      break;
      
    case _TEXT( '^' ):
      
      dirRet += _TEXT( ".." );
      break;
      
    default:
      dirRet += chr;
      
    }  
  }
  theFolder = dirRet;
  theName   = UTL::Name(p); theName+= UTL::Extension(p);
#endif  // WNT
  
  return CDM_MetaData::LookUp(theFolder,theName,theFile,theFile,UTL::IsReadOnly(theFile));
}
//=======================================================================
//function : ReferenceIdentifier
//purpose  : 
//=======================================================================

Standard_Integer PCDM_ReferenceIterator::ReferenceIdentifier() const {
  return myReferences(myIterator).ReferenceIdentifier();
}
//=======================================================================
//function : DocumentVersion
//purpose  : 
//=======================================================================

Standard_Integer PCDM_ReferenceIterator::DocumentVersion() const {
  return myReferences(myIterator).DocumentVersion();
}
