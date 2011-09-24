// File:      XmlLDrivers_DocumentStorageDriver.cxx
// Created:   Mon Jul  9 12:29:49 MSK DST 2001
// Author:    Julia DOROVSKIKH
// Copyright: Open Cascade 2001

#include <XmlLDrivers_DocumentStorageDriver.ixx>

#include <XmlLDrivers.hxx>
#include <XmlLDrivers_NamespaceDef.hxx>
#include <XmlMDF.hxx>
#include <XmlMDF_ADriverTable.hxx>

#include <XmlObjMgt.hxx>
#include <XmlObjMgt_SRelocationTable.hxx>

#include <LDOM_XmlWriter.hxx>
#include <LDOM_LDOMImplementation.hxx>
#include <LDOM_DocumentType.hxx>
#include <XmlObjMgt_Document.hxx>

#include <Storage_Data.hxx>
#include <PCDM.hxx>
#include <PCDM_ReadWriter.hxx>
#include <CDM_NullMessageDriver.hxx>
#include <CDM_Document.hxx>
#include <CDM_Application.hxx>
#include <TDocStd_Document.hxx>
#include <TColStd_SequenceOfAsciiString.hxx>

#include <locale.h>
#include <Standard_Failure.hxx>
#include <Standard_ErrorHandler.hxx>

#include <OSD_File.hxx>
#include <OSD_Environment.hxx>

#define STORAGE_VERSION      "STORAGE_VERSION: "
#define REFERENCE_COUNTER    "REFERENCE_COUNTER: "
#define MODIFICATION_COUNTER "MODIFICATION_COUNTER: "
#define START_REF            "START_REF"
#define END_REF              "END_REF"

#define FAILSTR "Failed to write xsi:schemaLocation : "

//#define TAKE_TIMES
static void take_time (const Standard_Integer, const char *,
                       const Handle(CDM_MessageDriver)&)
#ifdef TAKE_TIMES
;
#else
{}
#endif

//=======================================================================
//function : XmlLDrivers_DocumentStorageDriver
//purpose  : Constructor
//=======================================================================
XmlLDrivers_DocumentStorageDriver::XmlLDrivers_DocumentStorageDriver
                                (const TCollection_ExtendedString& theCopyright)
     : myCopyright (theCopyright)
{ 
}

//=======================================================================
//function : SchemaName
//purpose  : 
//=======================================================================
TCollection_ExtendedString XmlLDrivers_DocumentStorageDriver::SchemaName() const
{
  TCollection_ExtendedString schemaname;
  return schemaname; 
}

//=======================================================================
//function : AddNamespace
//purpose  : 
//=======================================================================

void XmlLDrivers_DocumentStorageDriver::AddNamespace
                                (const TCollection_AsciiString& thePrefix,
                                 const TCollection_AsciiString& theURI)
{
  for (Standard_Integer i = 1; i <= mySeqOfNS.Length(); i++)
    if (thePrefix == mySeqOfNS(i).Prefix()) return;
  mySeqOfNS.Append (XmlLDrivers_NamespaceDef(thePrefix, theURI));
}

//=======================================================================
//function : Write
//purpose  : 
//=======================================================================
void XmlLDrivers_DocumentStorageDriver::Write
                          (const Handle(CDM_Document)&       theDocument,
                           const TCollection_ExtendedString& theFileName)
{
  const TCollection_AsciiString anOldNumLocale =
    (Standard_CString) setlocale (LC_NUMERIC, NULL);
  setlocale(LC_NUMERIC, "C");

  Handle(CDM_MessageDriver) aMessageDriver =
    theDocument -> Application() -> MessageDriver();
  ::take_time (~0, " +++++ Start STORAGE procedures ++++++", aMessageDriver);

  // Create new DOM_Document
  XmlObjMgt_Document aDOMDoc = XmlObjMgt_Document::createDocument ("document");

  // Fill the document with data
  XmlObjMgt_Element anElement = aDOMDoc.getDocumentElement();

  if (WriteToDomDocument (theDocument, anElement, theFileName) == Standard_False) {
    // Write DOM_Document into XML file,
    TCollection_AsciiString aFileName (theFileName, '?');
    FILE * aFile = fopen(aFileName.ToCString(), "wt");

    if (aFile) {
      LDOM_XmlWriter aWriter (aFile);
      aWriter.SetIndentation(1);
      aWriter << aDOMDoc;
      fclose(aFile);
      ::take_time (0, " +++++ Fin formatting to XML : ", aMessageDriver);

    }else{
      myIsError = Standard_True;
      TCollection_ExtendedString aMsg =
        TCollection_ExtendedString("Error: the file ") + aFileName +
          " cannot be opened for writing";
      aMessageDriver -> Write (aMsg.ToExtString());
        Standard_Failure::Raise("File cannot be opened for writing");
    }
  }
  setlocale(LC_NUMERIC, (char *) anOldNumLocale.ToCString()) ;
}

//=======================================================================
//function : WriteToDomDocument
//purpose  : management of the macro-structure of XML document data
//remark   : If the application needs to use myRelocTable to store additional
//           data to XML, this method should be reimplemented avoiding step 3
//=======================================================================

Standard_Boolean XmlLDrivers_DocumentStorageDriver::WriteToDomDocument
                                  (const Handle(CDM_Document)&  theDocument,
                                   XmlObjMgt_Element&           theElement,
				   const TCollection_ExtendedString& theFileName)
{
  myIsError = Standard_False;
  Handle(CDM_MessageDriver) aMessageDriver =
    theDocument -> Application() -> MessageDriver();
  // 1. Write header information
  Standard_Integer i;
  XmlObjMgt_Document aDOMDoc = theElement.getOwnerDocument();

  // 1.a File Format
  TCollection_AsciiString aStorageFormat (theDocument->StorageFormat(), '?');
  theElement.setAttribute ("format", aStorageFormat.ToCString());
//  theElement.setAttribute ("schema", "XSD");

  theElement.setAttribute ("xmlns" , "http://www.opencascade.org/OCAF/XML");
  for (i = 1; i <= mySeqOfNS.Length(); i++) {
    TCollection_AsciiString aPrefix =
      TCollection_AsciiString("xmlns:") + mySeqOfNS(i).Prefix().ToCString();
    theElement.setAttribute (aPrefix.ToCString(),
                             mySeqOfNS(i).URI().ToCString());
  }
  theElement.setAttribute ("xmlns:xsi",
                           "http://www.w3.org/2001/XMLSchema-instance");
  //mkv 15.09.05 OCC10001
  //theElement.setAttribute ("xsi:schemaLocation",
  //                         "http://www.opencascade.org/OCAF/XML"
  //                         " http://www.nnov.matra-dtv.fr/~agv/XmlOcaf.xsd");
  //
  // the order of search : by CSF_XmlOcafResource and then by CASROOT
  TCollection_AsciiString anHTTP = "http://www.opencascade.org/OCAF/XML";
  Standard_Boolean aToSetCSFVariable = Standard_False;
  const char * aCSFVariable [2] = {
    "CSF_XmlOcafResource",
    "CASROOT"
  };
  TCollection_AsciiString aResourceDir = "";
  aResourceDir = getenv (aCSFVariable[0]);
  if (aResourceDir.IsEmpty()) {
    // now try by CASROOT
    aResourceDir = getenv (aCSFVariable[1]);
#ifdef OCE_CASROOT_FALLBACK_DIR
    if (aResourceDir.IsEmpty()) {
      aResourceDir = OCE_CASROOT_FALLBACK_DIR;
    }
#endif
    if ( !aResourceDir.IsEmpty() ) {
      aResourceDir += "/src/XmlOcafResource" ;
      aToSetCSFVariable = Standard_True; //CSF variable to be set later
    }
#ifdef DEB
    else {
      TCollection_ExtendedString aWarn = FAILSTR "Neither ";
      aWarn = (aWarn + aCSFVariable[0] + ", nor " + aCSFVariable[1]
               + " variables have been set");
      aMessageDriver->Write (aWarn.ToExtString());
    }
#endif
  }
  if (!aResourceDir.IsEmpty()) {
    TCollection_AsciiString aResourceFileName =  aResourceDir + "/XmlOcaf.xsd";
    // search directory name that has been constructed, now check whether
    // it and the file exist
    OSD_File aResourceFile ( aResourceFileName );
    if ( aResourceFile.Exists() ) {
      if (aToSetCSFVariable) {
        OSD_Environment aCSFVarEnv ( aCSFVariable[0], aResourceDir );
        aCSFVarEnv.Build();
#ifdef DEB
        TCollection_ExtendedString aWarn1 = "Variable ";
        aWarn1 = (aWarn1 + aCSFVariable[0]
                  + " has not been explicitly defined. Set to " + aResourceDir);
        aMessageDriver->Write (aWarn1.ToExtString());
#endif
        if ( aCSFVarEnv.Failed() ) {
          TCollection_ExtendedString aWarn = FAILSTR "Failed to initialize ";
          aWarn = aWarn + aCSFVariable[0] + " with " + aResourceDir;
          aMessageDriver->Write (aWarn.ToExtString());
        }
      }
    }
#ifdef DEB
    else {
      TCollection_ExtendedString aWarn = FAILSTR "Schema definition file ";
      aWarn += (aResourceFileName + " was not found");
      aMessageDriver->Write (aWarn.ToExtString());
    }
#endif
    anHTTP = anHTTP + ' ' + aResourceFileName;
  }
  theElement.setAttribute ("xsi:schemaLocation", anHTTP.ToCString() );

  // 1.b Info section
  XmlObjMgt_Element anInfoElem = aDOMDoc.createElement("info");
  theElement.appendChild(anInfoElem);

  TCollection_AsciiString aCreationDate = XmlLDrivers::CreationDate();

//  anInfoElem.setAttribute("dbv", 0);
  anInfoElem.setAttribute("date", aCreationDate.ToCString());
  anInfoElem.setAttribute("schemav", 0);
//  anInfoElem.setAttribute("appv", anAppVersion.ToCString());

  // Document version
  anInfoElem.setAttribute("DocVersion", XmlLDrivers::StorageVersion().ToCString());
 
  // User info with Copyright
  TColStd_SequenceOfAsciiString aUserInfo;
  if (myCopyright.Length() > 0)
    aUserInfo.Append (TCollection_AsciiString(myCopyright,'?'));

  Handle(Storage_Data) theData = new Storage_Data;
  //PCDM_ReadWriter::WriteFileFormat( theData, theDocument );
  PCDM_ReadWriter::Writer()->WriteReferenceCounter(theData,theDocument);
  PCDM_ReadWriter::Writer()->WriteReferences(theData,theDocument,theFileName);
  PCDM_ReadWriter::Writer()->WriteExtensions(theData,theDocument);
  PCDM_ReadWriter::Writer()->WriteVersion(theData,theDocument);

  const TColStd_SequenceOfAsciiString& aRefs = theData->UserInfo();
  for(i = 1; i <= aRefs.Length(); i++)
    aUserInfo.Append(aRefs.Value(i));

  for (i = 1; i <= aUserInfo.Length(); i++)
  {
    XmlObjMgt_Element aUIItem = aDOMDoc.createElement ("iitem");
    anInfoElem.appendChild (aUIItem);
    LDOM_Text aUIText = aDOMDoc.createTextNode (aUserInfo(i).ToCString());
    aUIItem.appendChild (aUIText);
  }

  // 1.c Comments section
  TColStd_SequenceOfExtendedString aComments;
  theDocument->Comments(aComments);

  XmlObjMgt_Element aCommentsElem = aDOMDoc.createElement ("comments");
  theElement.appendChild (aCommentsElem);

  for (i = 1; i <= aComments.Length(); i++)
  {
    XmlObjMgt_Element aCItem = aDOMDoc.createElement ("citem");
    aCommentsElem.appendChild (aCItem);
    XmlObjMgt::SetExtendedString (aCItem, aComments(i));
  }

  // 2a. Write document contents
  Standard_Integer anObjNb = 0;
  {
    try
    {
      OCC_CATCH_SIGNALS
      anObjNb = MakeDocument(theDocument, theElement);
    }
    catch (Standard_Failure)
    {
      myIsError = Standard_True;
      TCollection_ExtendedString anErrorString (Standard_Failure::Caught()->GetMessageString());
      aMessageDriver -> Write (anErrorString.ToExtString());
    }
  }
  if (anObjNb <= 0 && myIsError == Standard_False) {
    myIsError = Standard_True;
    TCollection_ExtendedString anErrorString ("error occurred");
    aMessageDriver -> Write (anErrorString.ToExtString());
  }
  // 2b. Write number of objects into the info section
  anInfoElem.setAttribute("objnb", anObjNb);
  ::take_time (0, " +++++ Fin DOM data for OCAF : ", aMessageDriver);

  // 3. Clear relocation table
  //    If the application needs to use myRelocTable to store additional
  //    data to XML, this method should be reimplemented avoiding this step
  myRelocTable.Clear();

  // 4. Write Shapes section
  if(WriteShapeSection(theElement))
    ::take_time (0, " +++ Fin DOM data for Shapes : ", aMessageDriver);
  return myIsError;
}

//=======================================================================
//function : MakeDocument
//purpose  : 
//=======================================================================
Standard_Integer XmlLDrivers_DocumentStorageDriver::MakeDocument
                                    (const Handle(CDM_Document)& theTDoc,
                                     XmlObjMgt_Element&          theElement) 
{  
  TCollection_ExtendedString aMessage;
  Handle(TDocStd_Document) TDOC = Handle(TDocStd_Document)::DownCast(theTDoc);  
  myRelocTable.Clear();
  if (!TDOC.IsNull()) 
  {
//    myRelocTable.SetDocument (theElement.getOwnerDocument());
    Handle(TDF_Data) aTDF = TDOC->GetData();

//      Find MessageDriver and pass it to AttributeDrivers()
    Handle(CDM_Application) anApplication= theTDoc -> Application();
    Handle(CDM_MessageDriver) aMessageDriver;
    if (anApplication.IsNull())
      aMessageDriver = new CDM_NullMessageDriver;
    else
      aMessageDriver = anApplication -> MessageDriver();
    if (myDrivers.IsNull()) myDrivers = AttributeDrivers (aMessageDriver);

//      Retrieve from DOM_Document
    XmlMDF::FromTo (aTDF, theElement, myRelocTable, myDrivers); 
#if defined(DEB) && !defined(TAKE_TIMES)
    aMessage = "First step successfull";
    aMessageDriver -> Write (aMessage.ToExtString());
#endif
    return myRelocTable.Extent();
  }
#ifdef DEB
  cout << "First step failed" << endl;  // No MessageDriver available
#endif
  return -1; // error
}

//=======================================================================
//function : IsError
//purpose  : 
//=======================================================================

Standard_Boolean XmlLDrivers_DocumentStorageDriver::IsError () const
{
  return myIsError;
}

//=======================================================================
//function : AttributeDrivers
//purpose  : 
//=======================================================================
Handle(XmlMDF_ADriverTable) XmlLDrivers_DocumentStorageDriver::AttributeDrivers
       (const Handle(CDM_MessageDriver)& theMessageDriver) 
{
  return XmlLDrivers::AttributeDrivers (theMessageDriver);
}

//=======================================================================
//function : take_time
//class    : static
//purpose  : output astronomical time elapsed
//=======================================================================
#ifdef TAKE_TIMES
#include <time.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <stdio.h>
#ifndef WNT
extern "C" int ftime (struct timeb *tp);
#endif
struct timeb  tmbuf0;

static void take_time (const Standard_Integer isReset, const char * aHeader,
                       const Handle(CDM_MessageDriver)& aMessageDriver)
{
  struct timeb  tmbuf;
  ftime (&tmbuf);
  TCollection_ExtendedString aMessage ((Standard_CString)aHeader);
  if (isReset) tmbuf0 = tmbuf;
  else {
    char take_tm_buf [64];
    sprintf (take_tm_buf, "%9.2f s ++++",
             double(tmbuf.time - tmbuf0.time) +
             double(tmbuf.millitm - tmbuf0.millitm)/1000.);
    aMessage += take_tm_buf;
  }
  aMessageDriver -> Write (aMessage.ToExtString());
}
#endif

//=======================================================================
//function : WriteShapeSection
//purpose  : defines WriteShapeSection
//=======================================================================
Standard_Boolean XmlLDrivers_DocumentStorageDriver::WriteShapeSection
                                (XmlObjMgt_Element&  /*theElement*/)
{
  // empty; should be redefined in subclasses
  return Standard_False;
}

