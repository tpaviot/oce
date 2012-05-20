// Created on: 1997-11-24
// Created by: Mister rmi
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



#include <UTL.ixx>
#include <OSD_Host.hxx>
#include <OSD_Path.hxx>
#include <TCollection_ExtendedString.hxx>
#include <TCollection_AsciiString.hxx>
#include <Resource_Unicode.hxx>
#include <OSD_Environment.hxx>
#include <OSD_FileIterator.hxx>
#include <OSD_File.hxx>
#include <OSD_Protection.hxx>
#include <OSD_SingleProtection.hxx>
#define MaxChar 10000


static Standard_Character longtc[MaxChar];
static Standard_PCharacter aLongCString = longtc;
static TCollection_ExtendedString outExtendedString;

static TCollection_AsciiString ASCII(const TCollection_ExtendedString& anXString) {
  Resource_Unicode::ConvertUnicodeToFormat(anXString,aLongCString,MaxChar);
  return TCollection_AsciiString(aLongCString);
}


static TCollection_ExtendedString UNICODE(const TCollection_AsciiString& aCString) {
  Resource_Unicode::ConvertFormatToUnicode(aCString.ToCString(),outExtendedString);
  return outExtendedString;
}

TCollection_ExtendedString UTL::xgetenv(const Standard_CString aCString) {
  TCollection_ExtendedString x;
  OSD_Environment theEnv(aCString);
  TCollection_AsciiString theValue=theEnv.Value();
  if( ! theValue.IsEmpty()) x=UNICODE(theValue);
  return x;
}
TCollection_ExtendedString UTL::Extension(const TCollection_ExtendedString& aFileName) {
  OSD_Path p = OSD_Path(ASCII(aFileName));

  TCollection_AsciiString theExtension=p.Extension();

  TCollection_AsciiString theGoodExtension=theExtension;;

  if(TCollection_AsciiString(theExtension.Value(1))==".") 
    theGoodExtension=theExtension.Split(1);

  return UNICODE(theGoodExtension);
}
Storage_Error UTL::OpenFile(Storage_BaseDriver& aDriver, const TCollection_ExtendedString& aFileName, const Storage_OpenMode aMode) {
  return aDriver.Open(ASCII(aFileName),aMode);
}

void UTL::AddToUserInfo(const Handle(Storage_Data)& aData, const TCollection_ExtendedString& anInfo) {
  aData->AddToUserInfo(ASCII(anInfo));
}
OSD_Path UTL::Path(const TCollection_ExtendedString& aFileName) {

//  cout << "Path : " << aFileName << endl;
//  TCollection_AsciiString theAciiString=ASCII(aFileName);
//  OSD_Path p = OSD_Path(theAciiString);
  OSD_Path p = OSD_Path(ASCII(aFileName));
  return p;
}
TCollection_ExtendedString UTL::Disk(const OSD_Path& aPath) {
  return UNICODE(aPath.Disk());
}
TCollection_ExtendedString UTL::Trek(const OSD_Path& aPath) {
  return UNICODE(aPath.Trek());
}
TCollection_ExtendedString UTL::Name(const OSD_Path& aPath) {
  return UNICODE(aPath.Name());
}
TCollection_ExtendedString UTL::Extension(const OSD_Path& aPath) {
  return UNICODE(aPath.Extension());
}
OSD_FileIterator UTL::FileIterator(const OSD_Path& aPath, const TCollection_ExtendedString& aMask) {
  OSD_FileIterator it = OSD_FileIterator(aPath,ASCII(aMask));
  return it;
}
TCollection_ExtendedString UTL::LocalHost() {
  OSD_Host h;
  return UNICODE(h.HostName());
}
TCollection_ExtendedString UTL::ExtendedString(const TCollection_AsciiString& anAsciiString) {
  return UNICODE(anAsciiString);
}
Standard_GUID UTL::GUID(const TCollection_ExtendedString& anXString) {
  return Standard_GUID(TCollection_AsciiString(anXString,'?').ToCString());
}
Standard_Boolean UTL::Find(const Handle(Resource_Manager)& aResourceManager, const TCollection_ExtendedString& aResourceName) {
  return aResourceManager->Find(ASCII(aResourceName).ToCString());
}  
TCollection_ExtendedString UTL::Value(const Handle(Resource_Manager)& aResourceManager, const TCollection_ExtendedString& aResourceName) {
  return UNICODE(aResourceManager->Value(ASCII(aResourceName).ToCString()));
}  

Standard_Integer UTL::IntegerValue(const TCollection_ExtendedString& anExtendedString) {
  TCollection_AsciiString a=ASCII(anExtendedString);
  return a.IntegerValue();
}
Standard_CString UTL::CString(const TCollection_ExtendedString& anExtendedString) {
  static TCollection_AsciiString theValue;
  theValue=ASCII(anExtendedString);
  return theValue.ToCString();
}
Standard_Boolean UTL::IsReadOnly(const TCollection_ExtendedString& aFileName) {

  switch (OSD_File(UTL::Path(aFileName)).Protection().User()) {
  case OSD_W:
  case OSD_RW:
  case OSD_WX:
  case OSD_RWX:
  case OSD_RWD:
  case OSD_WXD:
  case OSD_RWXD:
    return Standard_False;
  default:
    return Standard_True;
  }
}
