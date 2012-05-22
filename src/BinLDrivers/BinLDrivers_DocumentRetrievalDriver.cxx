// Created on: 2002-10-31
// Created by: Michael SAZONOV
// Copyright (c) 2002-2012 OPEN CASCADE SAS
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


#include <BinLDrivers_DocumentRetrievalDriver.ixx>
#include <BinLDrivers.hxx>
#include <BinLDrivers_Marker.hxx>
#include <BinMDF_ADriver.hxx>
#include <BinMDataStd.hxx>
#include <BinObjMgt_Persistent.hxx>
#include <FSD_BinaryFile.hxx>
#include <FSD_FileHeader.hxx>
#include <Standard_ErrorHandler.hxx>
#include <Standard_Stream.hxx>
#include <Storage_Schema.hxx>
#include <TDF_Data.hxx>
#include <TDocStd_Document.hxx>
#include <TDocStd_Owner.hxx>

#define SHAPESECTION_POS "SHAPE_SECTION_POS:"
#define SIZEOFSHAPELABEL  18

#define DATATYPE_MIGRATION
//#define DATATYPE_MIGRATION_DEB
//=======================================================================
//function : BinLDrivers_DocumentRetrievalDriver
//purpose  : Constructor
//=======================================================================

BinLDrivers_DocumentRetrievalDriver::BinLDrivers_DocumentRetrievalDriver ()
{
  myReaderStatus = PCDM_RS_OK;
}

//=======================================================================
//function : CreateDocument
//purpose  : pure virtual method definition
//=======================================================================

Handle(CDM_Document) BinLDrivers_DocumentRetrievalDriver::CreateDocument()
{
  return new TDocStd_Document(PCDM_RetrievalDriver::GetFormat());
}

//=======================================================================
//function : SchemaName
//purpose  : pure virtual method definition
//=======================================================================

TCollection_ExtendedString BinLDrivers_DocumentRetrievalDriver::SchemaName() const
{
  TCollection_ExtendedString schemaname;
  return schemaname;
}

//=======================================================================
//function : Make
//purpose  : pure virtual method definition
//=======================================================================

void BinLDrivers_DocumentRetrievalDriver::Make (const Handle(PCDM_Document)&,
                                               const Handle(CDM_Document)&)
{
}

//=======================================================================
//function : Read
//purpose  :
//=======================================================================

#define START_TYPES "START_TYPES"
#define END_TYPES "END_TYPES"

void BinLDrivers_DocumentRetrievalDriver::Read
                         (const TCollection_ExtendedString& theFileName,
                          const Handle(CDM_Document)&       theNewDocument,
                          const Handle(CDM_Application)&    theApplication)
{
  myReaderStatus = PCDM_RS_DriverFailure;
  myMsgDriver = theApplication -> MessageDriver();

  const TCollection_ExtendedString aMethStr
    ("BinLDrivers_DocumentRetrievalDriver: ");

  Handle(TDocStd_Document) aDoc =
    Handle(TDocStd_Document)::DownCast(theNewDocument);
  if (aDoc.IsNull()) {
#ifdef DEB
    WriteMessage (aMethStr + "error: null document");
#endif
    myReaderStatus = PCDM_RS_NoDocument;
    return;
  }

  TCollection_AsciiString aFileName (theFileName,'?');

  // 1. Read the information section
  Handle(Storage_HeaderData) aHeaderData;
  Storage_Position anInfoSectionEnd = ReadInfoSection( aFileName, aHeaderData );
  if (!anInfoSectionEnd) {
    WriteMessage (aMethStr + "error: file has invalid header");
    myReaderStatus = PCDM_RS_UnrecognizedFileFormat;
    return;
  }

  // 1.a Version of writer
  if (!aHeaderData->StorageVersion().IsIntegerValue()) {
    // file has no format version
    WriteMessage (aMethStr + "error: file has no format version");
    myReaderStatus = PCDM_RS_FormatFailure;
    return;
  }
  Standard_Integer aFileVer = aHeaderData->StorageVersion().IntegerValue();
  Standard_Integer aCurrVer = BinLDrivers::StorageVersion().IntegerValue();
  // maintain one-way compatibility starting from version 2+
  if (aFileVer < 2 || aFileVer > aCurrVer) {
    // file was written with another version
    WriteMessage (aMethStr + "error: wrong file version: " +
		  aHeaderData->StorageVersion() + " while current is " +
		  BinLDrivers::StorageVersion());
    myReaderStatus = PCDM_RS_NoVersion;
    return;
  }

  // 1.b Retrieve the Types table
  TColStd_SequenceOfAsciiString aTypeNames; //Sequence of types in file
  const TColStd_SequenceOfAsciiString& aUserInfo = aHeaderData->UserInfo();
  Standard_Boolean begin = Standard_False;
  Standard_Integer i;
  for (i=1; i <= aUserInfo.Length(); i++) {
    //const TCollection_AsciiString& aStr = aUserInfo(i);
    TCollection_AsciiString aStr = aUserInfo(i);
    if (aStr == START_TYPES)
      begin = Standard_True;
    else if (aStr == END_TYPES)
      break;
    else if (begin) {
      if(aFileVer < 5) {
#ifdef DATATYPE_MIGRATION
	TCollection_AsciiString  newName;	
	if(Storage_Schema::CheckTypeMigration(aStr, newName)) {
#ifdef DATATYPE_MIGRATION_DEB
	  cout << "CheckTypeMigration:OldType = " <<aStr << " Len = "<<aStr.Length()<<endl;
	  cout << "CheckTypeMigration:NewType = " <<newName  << " Len = "<< newName.Length()<<endl;
#endif
	  aStr = newName;
	}
#endif  
      } 
      aTypeNames.Append (aStr);    
    }
  }
  if (myDrivers.IsNull())
    myDrivers = AttributeDrivers (myMsgDriver);
  myDrivers->AssignIds (aTypeNames); 

  // recognize types not supported by drivers
  myMapUnsupported.Clear();
  for (i=1; i <= aTypeNames.Length(); i++)
    if (myDrivers->GetDriver(i).IsNull()) 
      myMapUnsupported.Add(i);
  if (!myMapUnsupported.IsEmpty()) {
    WriteMessage (aMethStr + "warning: "
                  "the following attributes have no driver:");
    for (i=1; i <= aTypeNames.Length(); i++)
      if (myMapUnsupported.Contains(i))
	WriteMessage (aTypeNames(i));
  }

  // Open the file stream
#ifdef WNT
  ifstream anIS (aFileName.ToCString(), ios::in | ios::binary);
#else
  ifstream anIS (aFileName.ToCString());
#endif

  if (!anIS) {
    // Can not open file
    WriteMessage (aMethStr + "error: can't open file " + theFileName);
    myReaderStatus = PCDM_RS_OpenError;
    return;
  }

  // skip info section
  anIS.seekg( (streampos) anInfoSectionEnd );

  // propagate the opened document version to data drivers
  PropagateDocumentVersion(aFileVer);

  // 2. Read document contents

  // 2a. Retrieve data from the stream:
  myRelocTable.Clear();
  mySections.Clear();
  myPAtt.Init();
  Handle(TDF_Data) aData = new TDF_Data();
  std::streamoff aDocumentPos = -1;

  // 2b. Read the TOC of Sections
  if (aFileVer >= 3) {
    BinLDrivers_DocumentSection aSection;
    do {
      BinLDrivers_DocumentSection::ReadTOC (aSection, anIS);
      mySections.Append(aSection);
    } while
      (!aSection.Name().IsEqual((Standard_CString)SHAPESECTION_POS));
    aDocumentPos = anIS.tellg(); // position of root label

    BinLDrivers_VectorOfDocumentSection::Iterator anIterS (mySections);
    for (; anIterS.More(); anIterS.Next()) {
      BinLDrivers_DocumentSection& aCurSection = anIterS.ChangeValue();
      if (aCurSection.IsPostRead() == Standard_False) {
        anIS.seekg ((streampos) aCurSection.Offset());
        if (aCurSection.Name().IsEqual ((Standard_CString)SHAPESECTION_POS)) 
          ReadShapeSection (aCurSection, anIS);
        else
          ReadSection (aCurSection, theNewDocument, anIS); 
      }
    }
  } else { //aFileVer < 3
    aDocumentPos = anIS.tellg(); // position of root label

    // retrieve SHAPESECTION_POS string
    char aShapeSecLabel[SIZEOFSHAPELABEL + 1];
    aShapeSecLabel[SIZEOFSHAPELABEL] = 0x00;
    anIS.read ((char*)&aShapeSecLabel, SIZEOFSHAPELABEL);// SHAPESECTION_POS
    TCollection_AsciiString aShapeLabel(aShapeSecLabel);
    // detect if a file was written in old fashion (version 2 without shapes)
    // and if so then skip reading ShapeSection
    if (aShapeLabel.Length() > 0) {
      // version 2+(with shapes) and higher goes here
      if(aShapeLabel.Length() <= 0 || aShapeLabel != SHAPESECTION_POS) {
        WriteMessage (aMethStr + "error: Format failure");
        myReaderStatus = PCDM_RS_FormatFailure;
        return;
      }

      // retrieve ShapeSection Position
      Standard_Integer aShapeSectionPos; // go to ShapeSection
      anIS.read ((char*)&aShapeSectionPos, sizeof(Standard_Integer));

#if DO_INVERSE
      aShapeSectionPos = InverseInt (aShapeSectionPos);
#endif
#ifdef DATATYPE_MIGRATION_DEB      
      cout <<"aShapeSectionPos = " <<aShapeSectionPos <<endl;
#endif
      if(aShapeSectionPos) { 
	aDocumentPos = anIS.tellg();
	anIS.seekg((streampos) aShapeSectionPos);

	CheckShapeSection((streampos)aShapeSectionPos, anIS);
	// Read Shapes
	BinLDrivers_DocumentSection aCurSection;
	ReadShapeSection (aCurSection, anIS, Standard_False);
      }
    }
  } // end of reading Sections or shape section

  // Return to read of the Document structure
  anIS.seekg((streampos) aDocumentPos);

  // read the header (tag) of the root label
  Standard_Integer aTag;
  anIS.read ((char*)&aTag, sizeof(Standard_Integer));

  // read sub-tree of the root label
  Standard_Integer nbRead = ReadSubTree (anIS, aData->Root());
  myPAtt.Destroy();    // free buffer
  myRelocTable.Clear();
  myMapUnsupported.Clear();
    
  if (nbRead > 0) {
    // attach data to the document
    aDoc->SetData (aData);
    TDocStd_Owner::SetDocument (aData, aDoc);
    aDoc->SetComments(aHeaderData->Comments());
    myReaderStatus = PCDM_RS_OK;
  }

  // Read Sections (post-reading type)
  if (aFileVer >= 3) {
    BinLDrivers_VectorOfDocumentSection::Iterator anIterS (mySections);
    for (; anIterS.More(); anIterS.Next()) {
      BinLDrivers_DocumentSection& aCurSection = anIterS.ChangeValue();
      if (aCurSection.IsPostRead()) {
	anIS.seekg ((streampos) aCurSection.Offset());
	ReadSection (aCurSection, theNewDocument, anIS); 
      }
    }
  }
}

//=======================================================================
//function : ReadSubTree
//purpose  :
//=======================================================================

Standard_Integer BinLDrivers_DocumentRetrievalDriver::ReadSubTree
                         (Standard_IStream& theIS,
                          const TDF_Label&  theLabel)
{
  Standard_Integer nbRead = 0;
  static TCollection_ExtendedString aMethStr
    ("BinLDrivers_DocumentRetrievalDriver: ");

  // Read attributes:
  theIS >> myPAtt;
  while (theIS && myPAtt.TypeId() > 0 &&             // not an end marker ?
         myPAtt.Id() > 0) {                          // not a garbage ?
    // get a driver according to TypeId
    Handle(BinMDF_ADriver) aDriver = myDrivers->GetDriver (myPAtt.TypeId());
    if (!aDriver.IsNull()) {
      // create transient attribute
      nbRead++;
      Standard_Integer anID = myPAtt.Id();
      Handle(TDF_Attribute) tAtt;
      Standard_Boolean isBound = myRelocTable.IsBound(anID);
      if (isBound)
        tAtt = Handle(TDF_Attribute)::DownCast(myRelocTable.Find(anID));
      else
        tAtt = aDriver->NewEmpty();
      if (tAtt->Label().IsNull())
	theLabel.AddAttribute (tAtt);
      else
	WriteMessage (aMethStr +
		      "warning: attempt to attach attribute " +
		      aDriver->TypeName() + " to a second label");

      Standard_Boolean ok = aDriver->Paste (myPAtt, tAtt, myRelocTable);
      if (!ok) {
        // error converting persistent to transient
        WriteMessage (aMethStr + "warning: failure reading attribute " +
                      aDriver->TypeName());
      }
      else if (!isBound)
        myRelocTable.Bind (anID, tAtt);
    }
    else if (!myMapUnsupported.Contains(myPAtt.TypeId()))
      WriteMessage (aMethStr + "warning: type ID not registered in header: "
                    + myPAtt.TypeId());

    // read next attribute
    theIS >> myPAtt;
  }
  if (!theIS || myPAtt.TypeId() != BinLDrivers_ENDATTRLIST) {
    // unexpected EOF or garbage data
    WriteMessage (aMethStr + "error: unexpected EOF or garbage data");
    myReaderStatus = PCDM_RS_UnrecognizedFileFormat;
    return -1;
  }

  // Read children:
  // read the tag of a child label
  Standard_Integer aTag = BinLDrivers_ENDLABEL;
  theIS.read ((char*) &aTag, sizeof(Standard_Integer));
#if DO_INVERSE
  aTag = InverseInt (aTag);
#endif
  while (theIS && aTag >= 0) { // not an end marker ?
    // create sub-label
    TDF_Label aLab = theLabel.FindChild (aTag, Standard_True);

    // read sub-tree
    Standard_Integer nbSubRead = ReadSubTree(theIS, aLab);
    // check for error
    if (nbSubRead == -1)
      return -1;
    nbRead += nbSubRead;

    // read the tag of the next child
    theIS.read ((char*) &aTag, sizeof(Standard_Integer));
#if DO_INVERSE
    aTag = InverseInt (aTag);
#endif
  }
  if (aTag != BinLDrivers_ENDLABEL) {
    // invalid end label marker
    WriteMessage (aMethStr + "error: invalid end label marker");
    myReaderStatus = PCDM_RS_UnrecognizedFileFormat;
    return -1;
  }

  return nbRead;
}

//=======================================================================
//function : AttributeDrivers
//purpose  :
//=======================================================================

Handle(BinMDF_ADriverTable) BinLDrivers_DocumentRetrievalDriver::AttributeDrivers
       (const Handle(CDM_MessageDriver)& theMessageDriver)
{
  return BinLDrivers::AttributeDrivers (theMessageDriver);
}

//=======================================================================
//function : ReadInfoSection
//purpose  : Read the info  section  of  theFile, return a file
//           position corresponding to the info section end
//=======================================================================

Storage_Position BinLDrivers_DocumentRetrievalDriver::ReadInfoSection
                         (const TCollection_AsciiString& theFileName,
                          Handle(Storage_HeaderData)&    theData)
{
  TCollection_ExtendedString aMsg
    ( "BinLDrivers_DocumentRetrievalDriver: error: ");

  FSD_BinaryFile aFileDriver;
  Storage_Position aPos = 0;
  if (aFileDriver.Open( theFileName, Storage_VSRead ) == Storage_VSOk)
  {
    Storage_Schema aSchema;
    theData = aSchema.ReadHeaderSection( aFileDriver );

    if (theData->ErrorStatus() == Storage_VSOk)
      aPos = aFileDriver.Tell();
    else
      WriteMessage( aMsg + theData->ErrorStatusExtension() );
  }
  else
    WriteMessage( aMsg + "can not open file " + theFileName);

  aFileDriver.Close();

  return aPos;
}

//=======================================================================
//function : WriteMessage
//purpose  : write   theMessage   to   the   MessageDriver   of
//           theApplication
//=======================================================================

void BinLDrivers_DocumentRetrievalDriver::WriteMessage
                         (const TCollection_ExtendedString& theMsg)
{
  if (!myMsgDriver.IsNull())
    myMsgDriver->Write (theMsg.ToExtString());
}

//=======================================================================
//function : ReadSection
//purpose  : 
//=======================================================================

void BinLDrivers_DocumentRetrievalDriver::ReadSection
                                (BinLDrivers_DocumentSection& /*theSection*/,
                                 const Handle(CDM_Document)&  /*theDocument*/,
                                 Standard_IStream&            /*theIS*/)
{
  // empty; should be redefined in subclasses
}

//=======================================================================
//function : ReadShapeSection
//purpose  : 
//=======================================================================

void BinLDrivers_DocumentRetrievalDriver::ReadShapeSection
                              (BinLDrivers_DocumentSection& theSection,
                               Standard_IStream&            /*theIS*/,
			       const Standard_Boolean isMess)

{
  if(isMess && theSection.Length()) {
    const TCollection_ExtendedString aMethStr ("BinLDrivers_DocumentRetrievalDriver: ");
    WriteMessage (aMethStr + "warning: Geometry is not supported by Lite schema. ");
  }
}

//=======================================================================
//function : CheckShapeSection
//purpose  : 
//=======================================================================
void BinLDrivers_DocumentRetrievalDriver::CheckShapeSection(
				  const Storage_Position& ShapeSectionPos, 
						    Standard_IStream& IS)
{
  if(!IS.eof()) {
#if defined(WNT) || defined(OCE_HAVE_IOSTREAM)
    const Storage_Position endPos = IS.rdbuf()->pubseekoff(0L, std::ios_base::end, std::ios_base::in);
#else
    const Storage_Position endPos = IS.rdbuf()->seekoff(0L, unsafe_ios::end, unsafe_ios::in);
#endif
#ifdef DATATYPE_MIGRATION_DEB
    cout << "endPos = " << endPos <<endl;
#endif
    if(ShapeSectionPos != endPos) {
      const TCollection_ExtendedString aMethStr ("BinLDrivers_DocumentRetrievalDriver: ");
      WriteMessage (aMethStr + "warning: Geometry is not supported by Lite schema. ");
    }
  }
}

//=======================================================================
//function : PropagateDocumentVersion
//purpose  : 
//=======================================================================
void BinLDrivers_DocumentRetrievalDriver::PropagateDocumentVersion(const Standard_Integer theDocVersion )
{
  BinMDataStd::SetDocumentVersion(theDocVersion);
}
