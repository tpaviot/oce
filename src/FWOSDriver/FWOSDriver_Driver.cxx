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

#include <FWOSDriver_Driver.ixx>
#include <TCollection_ExtendedString.hxx>
#include <OSD_Path.hxx>
#include <OSD_Directory.hxx>
#include <OSD_Protection.hxx>
#include <OSD_SingleProtection.hxx>
#include <OSD_File.hxx>
#include <OSD_FileNode.hxx>
#include <UTL.hxx>
#include <TCollection_ExtendedString.hxx>
#ifdef WNT
#include <tchar.h>
#endif  // WNT


//==============================================================================
//function : PutSlash
//purpose  :
//==============================================================================
static void PutSlash (TCollection_ExtendedString& anXSTRING) {
#ifdef WNT
  anXSTRING+="\\";
#else
  anXSTRING+="/";
#endif  // WNT
}

//==============================================================================
//function : FWOSDriver_Driver
//purpose  :
//==============================================================================
FWOSDriver_Driver::FWOSDriver_Driver() {}

//==============================================================================
//function : Find
//purpose  :
//==============================================================================
Standard_Boolean FWOSDriver_Driver::Find(const TCollection_ExtendedString& aFolder,
                                         const TCollection_ExtendedString& aName,
                                         const TCollection_ExtendedString& aVersion)
{

  OSD_Path thePath=UTL::Path(aFolder);
  OSD_Directory theDirectory(thePath);
  if(theDirectory.Exists()) {
    TCollection_ExtendedString f(aFolder);
    PutSlash(f);
    f+=aName;
    OSD_Path p2 = UTL::Path(f);
    OSD_File theFile(p2);
    return theFile.Exists();
  }
  return Standard_False;
}

//==============================================================================
//function : HasReadPermission
//purpose  :
//==============================================================================
Standard_Boolean FWOSDriver_Driver::HasReadPermission(const TCollection_ExtendedString& aFolder,
                                                      const TCollection_ExtendedString& aName,
                                                      const TCollection_ExtendedString& aVersion)
{
  OSD_SingleProtection theProtection=OSD_File(UTL::Path(Concatenate(aFolder,aName))).Protection().User();
  switch (theProtection) {
    case OSD_None:
    case OSD_R:
    case OSD_RW:
    case OSD_RX:
    case OSD_WX:
    case OSD_RWX:
    case OSD_RD:
    case OSD_RWD:
    case OSD_RXD:
    case OSD_RWXD:
      return Standard_True;
    default:
      break;
    }
  return Standard_False;
}

//==============================================================================
//function : MetaData
//purpose  :
//==============================================================================
Handle(CDM_MetaData) FWOSDriver_Driver::MetaData(const TCollection_ExtendedString& aFolder,
                                                 const TCollection_ExtendedString& aName,
                                                 const TCollection_ExtendedString& aVersion)
{
  TCollection_ExtendedString p = Concatenate(aFolder,aName);
  return CDM_MetaData::LookUp(aFolder,aName,p,p,UTL::IsReadOnly(p));
}

//==============================================================================
//function : CreateMetaData
//purpose  :
//==============================================================================
Handle(CDM_MetaData) FWOSDriver_Driver::CreateMetaData(const Handle(CDM_Document)& aDocument,
                                                       const TCollection_ExtendedString& aFileName)
{
  return CDM_MetaData::LookUp(aDocument->RequestedFolder(),aDocument->RequestedName(),
                              Concatenate(aDocument->RequestedFolder(),aDocument->RequestedName()),
                              aFileName,UTL::IsReadOnly(aFileName));
}

//==============================================================================
//function : BuildFileName
//purpose  :
//==============================================================================
TCollection_ExtendedString FWOSDriver_Driver::BuildFileName(const Handle(CDM_Document)& aDocument)
{

  TCollection_ExtendedString retstr = TCollection_ExtendedString(aDocument->RequestedFolder());
  PutSlash(retstr);
  retstr += aDocument->RequestedName();
  return retstr;
}

//==============================================================================
//function : FindFolder
//purpose  :
//==============================================================================
Standard_Boolean FWOSDriver_Driver::FindFolder(const TCollection_ExtendedString& aFolder)
{
  
  OSD_Path thePath=UTL::Path(aFolder);
  OSD_Directory theDirectory(thePath);
  return theDirectory.Exists();
}

//==============================================================================
//function : Concatenate
//purpose  :
//==============================================================================
TCollection_ExtendedString FWOSDriver_Driver::Concatenate(const TCollection_ExtendedString& aFolder,
                                                          const TCollection_ExtendedString& aName)
{
  TCollection_ExtendedString ff(aFolder);
  ff = "";
  ff += aFolder;
  PutSlash(ff);
  ff+=aName;
  return ff;
}

//==============================================================================
//function : DefaultFolder
//purpose  :
//==============================================================================
TCollection_ExtendedString FWOSDriver_Driver::DefaultFolder()
{
  TCollection_ExtendedString theDefaultFolder;
  if (theDefaultFolder.Length() == 0) {
    
#ifdef WNT
    TCollection_ExtendedString hd=UTL::xgetenv("HOMEDRIVE");
    if(hd.Length() != NULL) {
      theDefaultFolder=hd;
      theDefaultFolder+=UTL::xgetenv("HOMEPATH");
    }
    else {
      theDefaultFolder=UTL::xgetenv("TEMP");
      if(theDefaultFolder.Length()==0)
        Standard_Failure::Raise("cannot determine default folder; HOMEDRIVE and TEMP are undefined");
    }
#else
    TCollection_ExtendedString home=UTL::xgetenv("HOME");
    if(home.Length() !=0)
      theDefaultFolder =  home;
    else
      theDefaultFolder= TCollection_ExtendedString("/tmp");
#endif
  }
  return theDefaultFolder;
}

//==============================================================================
//function : BuildMetaData
//purpose  :
//==============================================================================
Handle(CDM_MetaData) FWOSDriver_Driver::BuildMetaData(const TCollection_ExtendedString& aFileName)
{

  OSD_Path p = UTL::Path(aFileName);
  
  TCollection_ExtendedString f = UTL::Trek(p);
  TCollection_ExtendedString n = UTL::Name(p);
  n +=".";
  n += UTL::Extension(p);

  return CDM_MetaData::LookUp(f,n,aFileName,aFileName,UTL::IsReadOnly(aFileName));
}

//==============================================================================
//function : SetName
//purpose  :
//==============================================================================
TCollection_ExtendedString FWOSDriver_Driver::SetName(const Handle(CDM_Document)& aDocument,
                                                      const TCollection_ExtendedString& aName)
{
  
  TCollection_ExtendedString xn(aName), n(aName);

#ifdef WNT
  //windows is not case sensitive
  Standard_ExtCharacter   echar;
  //make the extension lower case
  for(int i = 1; i <= xn.Length(); i++)
  {
	echar = xn.Value(i);
	echar = towlower(echar);
	xn.SetValue(i, echar);
  }
#endif
  
  TCollection_ExtendedString e (aDocument->FileExtension());
  TCollection_ExtendedString xe(e);
  if (e.Length() > 0) {
#ifdef WNT
    //windows is not case sensitive
    Standard_ExtCharacter   echar;
    //make the extension lower case
    for(int i = 1; i <= xe.Length(); i++)
    {
	  echar = xe.Value(i);
	  echar = towlower(echar);
	  xe.SetValue(i, echar);
    }
#endif
    xe.Insert(1, '.');
    e.Insert(1, '.');
    Standard_Integer ln = xn.Length();
    Standard_Integer le = xe.Length();
    Standard_Boolean ExtensionIsAlreadyThere = Standard_False;
    if(ln>=le) {
      Standard_Integer ind=xn.SearchFromEnd(xe);
      ExtensionIsAlreadyThere = ind+le-1==ln;
    }
    if(!ExtensionIsAlreadyThere) n+=e;
  }
  return n;
}
