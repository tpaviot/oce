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

//      	----------------

// Version:	0.0
//Version	Date		Purpose
//		0.0	Aug 22 1997	Creation

#include <Standard_Stream.hxx>

#include <DDF_IOStream.hxx>

// This file has been written using FSD_File.cxx as template.
// This is a specific adaptation for Draw use (save & restore commands).
// It is not sure at all this code is portable on any other plateform than
// SUN OS. Don't use it anywhere else.
// Thanks for comprehension. (22 august 97)


#include <Storage_StreamTypeMismatchError.hxx>
#include <Storage_StreamFormatError.hxx>
#include <Storage_StreamWriteError.hxx>
#include <Storage_StreamExtCharParityError.hxx>

#include <TCollection_AsciiString.hxx>
#include <TCollection_ExtendedString.hxx>

#include <TColStd_SequenceOfAsciiString.hxx>
#include <TColStd_SequenceOfExtendedString.hxx>

const Standard_CString MAGICNUMBER = "FSDFILE";


//=======================================================================
//function : DDF_IOStream
//purpose  : 
//=======================================================================

DDF_IOStream::DDF_IOStream()
{}

//=======================================================================
//function : Open
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::Open(const TCollection_AsciiString& aName,const Storage_OpenMode aMode)
{
  //myIStream = NULL;
  //myOStream = NULL;
  //return Storage_VSOk;

  Storage_Error result = Storage_VSOk;

  SetName(aName);

  if (OpenMode() == Storage_VSNone) {
    if (aMode == Storage_VSRead) {
      if (myIStream != NULL) delete myIStream;
      myIStream = new ifstream(aName.ToCString(),ios::in); // ios::nocreate is not portable
      if (myIStream->fail()) {
	result = Storage_VSOpenError;
      }
      else {
	myIStream->precision(17);
	SetOpenMode(aMode);
      }
    }
    else if (aMode == Storage_VSWrite) {
      if (myOStream != NULL) delete myOStream;
      myOStream = new ofstream(aName.ToCString(),ios::out);
      if (myOStream->fail()) {
	result = Storage_VSOpenError;
      }
      else {
	myOStream->precision(17);
	SetOpenMode(aMode);
      }
    }
  }
  else {
    result = Storage_VSAlreadyOpen;
  }

  return result;
}

//=======================================================================
//function : Open
//purpose  : "Opens" an istream.
//=======================================================================

Storage_Error DDF_IOStream::Open(istream* anIStream)
{
  myOStream = NULL;
  SetOpenMode(Storage_VSRead);
  myIStream = anIStream;
  myIStream->precision(17);
  SetName("DDF_IOStream");
  return Storage_VSOk; // ou Storage_VSAlreadyOpen ?
}

//=======================================================================
//function : Open
//purpose  : "Opens" an ostream.
//=======================================================================

Storage_Error DDF_IOStream::Open(ostream* anOStream)
{
  myIStream = NULL;
  SetOpenMode(Storage_VSWrite);
  myOStream = anOStream;
  myOStream->precision(17);
  SetName("DDF_IOStream");
  return Storage_VSOk; // ou Storage_VSAlreadyOpen ?
}

//=======================================================================
//function : IsEnd
//purpose  : 
//=======================================================================

Standard_Boolean DDF_IOStream::IsEnd()
{
  if (OpenMode() == Storage_VSRead) return myIStream->eof();
  else                              return myOStream->eof();
}

//=======================================================================
//function : Close
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::Close()
{ return Storage_VSOk; }


// ------------------ PROTECTED


//=======================================================================
//function : MagicNumber
//purpose  : 
//=======================================================================

const Standard_CString DDF_IOStream::MagicNumber()
{ return MAGICNUMBER; }

//=======================================================================
//function : FlushEndOfLine
//purpose  : 
//=======================================================================

void DDF_IOStream::FlushEndOfLine()
{
  static char Buffer[8192];
  char c;
  Standard_Boolean IsEnd = Standard_False;

  while (!IsEnd && !DDF_IOStream::IsEnd()) {
    Buffer[0] = '\0';
    myIStream->get(Buffer,8192,'\n');

    if (myIStream->get(c) && c != '\n') {
    }
    else {
      IsEnd = Standard_True;
    }
  }
}

//=======================================================================
//function : ReadLine
//purpose  : 
//=======================================================================

void DDF_IOStream::ReadLine(TCollection_AsciiString& buffer)
{
  static char Buffer[8193];
  char c;
  Standard_Boolean IsEnd = Standard_False;
  
  buffer.Clear();

  while (!IsEnd && !DDF_IOStream::IsEnd()) {
    Buffer[0] = '\0';
    myIStream->get(Buffer,8192,'\n');
    
    if (myIStream->get(c) && c != '\n') {
      buffer += Buffer;
      buffer += c;
    }
    else {
      buffer += Buffer;
      IsEnd = Standard_True;
    }
  }
}


//=======================================================================
//function : WriteExtendedLine
//purpose  : 
//=======================================================================

void DDF_IOStream::WriteExtendedLine(const TCollection_ExtendedString& buffer)
{
  Standard_ExtString extBuffer;
  Standard_Integer   i,c,d;

  extBuffer = buffer.ToExtString();

  for (i = 0; i < buffer.Length(); i++) {
    c = (extBuffer[i] & 0x0000FF00 ) >> 8 ;
    d = extBuffer[i] & 0x000000FF;

    *myOStream << (char)c << (char)d;
  }

  *myOStream << (char)0 << "\n";
}

//=======================================================================
//function : ReadExtendedLine
//purpose  : 
//=======================================================================

void DDF_IOStream::ReadExtendedLine(TCollection_ExtendedString& buffer)
{
  char c = '\0';
  Standard_ExtCharacter i = 0,j,check = 0;
  Standard_Boolean fin = Standard_False;

  buffer.Clear();

  while (!fin && !IsEnd()) {
    myIStream->get(c);
    check++; 
//    if (!(check % 2)) Storage_StreamExtCharParityError::Raise();
    i = 0; j = 0;
    i += (Standard_ExtCharacter)c;
    if (c == '\0') fin = Standard_True;
    i = (i << 8);

    myIStream->get(c);
    check++;
//    if ((check % 2) != 0) Storage_StreamExtCharParityError::Raise();
//    cout << check << endl;
    j += (Standard_ExtCharacter)c;
    if (c != '\n') fin = Standard_False;
    i |= (0x00FF & j);
    buffer += (Standard_ExtCharacter)i;
  }

//  if ((check % 2) != 0) Storage_StreamExtCharParityError::Raise();
//  cout << check << endl;
}

//=======================================================================
//function : ReadChar
//purpose  : 
//=======================================================================

void DDF_IOStream::ReadChar(TCollection_AsciiString& buffer, const Standard_Integer rsize)
{
  char             c;
  Standard_Integer ccount = 0;

  buffer.Clear();

  while (!IsEnd() && (ccount < rsize)) {
    myIStream->get(c);
    buffer += c;
    ccount++;
  }
}

//=======================================================================
//function : ReadString
//purpose  : 
//=======================================================================

void DDF_IOStream::ReadString(TCollection_AsciiString& buffer)
{
  char c = 0;
  Standard_Boolean IsEnd = Standard_False;

  buffer.Clear();

  while (!IsEnd && !DDF_IOStream::IsEnd()) {
    myIStream->get(c);
    if ((c != ' ') && (c != '\n')) IsEnd = Standard_True;
  }

  IsEnd = Standard_False;

  while (!IsEnd && !DDF_IOStream::IsEnd()) {
    buffer += c;
    myIStream->get(c);
    if (c == '\n') IsEnd = Standard_True;
  }
}

//=======================================================================
//function : ReadWord
//purpose  : 
//=======================================================================

void DDF_IOStream::ReadWord(TCollection_AsciiString& buffer)
{
  char c = 0;
  Standard_Boolean IsEnd = Standard_False;

  buffer.Clear();

  while (!IsEnd && !DDF_IOStream::IsEnd()) {
    myIStream->get(c);
    if ((c != ' ') && (c != '\n')) IsEnd = Standard_True;
  }

  IsEnd = Standard_False;

  while (!IsEnd && !DDF_IOStream::IsEnd()) {
    buffer += c;
    myIStream->get(c);
    if ((c == '\n') || (c == ' ')) IsEnd = Standard_True;
  }
}

//=======================================================================
//function : FindTag
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::FindTag(const Standard_CString aTag)
{
  TCollection_AsciiString l;
  
  ReadString(l);

  while ((strcmp(l.ToCString(),aTag) != 0) && !IsEnd()) {
    ReadString(l);
  }

  if (IsEnd()) {
    return Storage_VSSectionNotFound;
  }
  else {
    return Storage_VSOk;
  }
}

//=======================================================================
//function : SkipObject
//purpose  : 
//=======================================================================

void DDF_IOStream::SkipObject()
{
  FlushEndOfLine();
}


// ---------------------- PUBLIC : PUT


//=======================================================================
//function : PutReference
//purpose  : 
//=======================================================================

Storage_BaseDriver& DDF_IOStream::PutReference(const Standard_Integer aValue)
{
  *myOStream << aValue << " ";
  if (myOStream->bad()) Storage_StreamWriteError::Raise("PutReference");
  return *this;
}

//=======================================================================
//function : PutCharacter
//purpose  : 
//=======================================================================

Storage_BaseDriver& DDF_IOStream::PutCharacter(const Standard_Character aValue)
{
  *myOStream << aValue << " ";
  if (myOStream->bad()) Storage_StreamWriteError::Raise("PutCharacter");
  return *this;
}

//=======================================================================
//function : PutExtCharacter
//purpose  : 
//=======================================================================

Storage_BaseDriver& DDF_IOStream::PutExtCharacter(const Standard_ExtCharacter aValue)
{
  *myOStream << aValue << " ";
  if (myOStream->bad()) Storage_StreamWriteError::Raise("PutExtCharacter");
  return *this;
}

//=======================================================================
//function : PutInteger
//purpose  : 
//=======================================================================

Storage_BaseDriver& DDF_IOStream::PutInteger(const Standard_Integer aValue)
{
  *myOStream << aValue << " ";
  if (myOStream->bad()) Storage_StreamWriteError::Raise("PutInteger");
  return *this;
}

//=======================================================================
//function : PutBoolean
//purpose  : 
//=======================================================================

Storage_BaseDriver& DDF_IOStream::PutBoolean(const Standard_Boolean aValue)
{
  *myOStream << ((Standard_Integer)aValue) << " ";
  if (myOStream->bad()) Storage_StreamWriteError::Raise("PutBoolean");
  return *this;
}

//=======================================================================
//function : PutReal
//purpose  : 
//=======================================================================

Storage_BaseDriver& DDF_IOStream::PutReal(const Standard_Real aValue)
{
  *myOStream << ((Standard_Real)aValue) << " ";
  if (myOStream->bad()) Storage_StreamWriteError::Raise("PutReal");
  return *this;
}

//=======================================================================
//function : PutShortReal
//purpose  : 
//=======================================================================

Storage_BaseDriver& DDF_IOStream::PutShortReal(const Standard_ShortReal aValue)
{
  *myOStream << aValue << " ";
  if (myOStream->bad()) Storage_StreamWriteError::Raise("PutShortReal");
  return *this;
}


// ----------------- PUBLIC : GET


//=======================================================================
//function : GetReference
//purpose  : 
//=======================================================================

Storage_BaseDriver& DDF_IOStream::GetReference(Standard_Integer& aValue)
{
  if (!(*myIStream >> aValue)) Storage_StreamTypeMismatchError::Raise("GetReference");
  return *this;
}

//=======================================================================
//function : GetCharacter
//purpose  : 
//=======================================================================

Storage_BaseDriver& DDF_IOStream::GetCharacter(Standard_Character& aValue)
{
  if (!(*myIStream >> aValue)) Storage_StreamTypeMismatchError::Raise("GetCharacter");
  return *this;
}

//=======================================================================
//function : GetExtCharacter
//purpose  : 
//=======================================================================

Storage_BaseDriver& DDF_IOStream::GetExtCharacter(Standard_ExtCharacter& aValue)
{
  if (!(*myIStream >> aValue)) Storage_StreamTypeMismatchError::Raise("GetExtCharacter");
  return *this;
}

//=======================================================================
//function : GetInteger
//purpose  : 
//=======================================================================

Storage_BaseDriver& DDF_IOStream::GetInteger(Standard_Integer& aValue)
{
  if (!(*myIStream >> aValue)) Storage_StreamTypeMismatchError::Raise("GetInteger");
  return *this;
}

//=======================================================================
//function : GetBoolean
//purpose  : 
//=======================================================================

Storage_BaseDriver& DDF_IOStream::GetBoolean(Standard_Boolean& aValue)
{
  if (!(*myIStream >> aValue)) Storage_StreamTypeMismatchError::Raise("GetBoolean");
  return *this;
}

//=======================================================================
//function : GetReal
//purpose  : 
//=======================================================================

Storage_BaseDriver& DDF_IOStream::GetReal(Standard_Real& aValue)
{
  if (!(*myIStream >> aValue)) Storage_StreamTypeMismatchError::Raise("GetReal");
  return *this;
}

//=======================================================================
//function : GetShortReal
//purpose  : 
//=======================================================================

Storage_BaseDriver& DDF_IOStream::GetShortReal(Standard_ShortReal& aValue)
{
  if (!(*myIStream >> aValue)) Storage_StreamTypeMismatchError::Raise("GetShortReal");
  return *this;
}

// -------------------------- DESTROY

//=======================================================================
//function : Destroy
//purpose  : 
//=======================================================================

void DDF_IOStream::Destroy()
{
  if (OpenMode() != Storage_VSNone) Close();
}


// -------------------------- INFO : WRITE


//=======================================================================
//function : BeginWriteInfoSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::BeginWriteInfoSection() 
{
  *myOStream << DDF_IOStream::MagicNumber() << '\n';
  *myOStream << "BEGIN_INFO_SECTION\n";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();

  return Storage_VSOk;
}

//=======================================================================
//function : WriteInfo
//purpose  : 
//=======================================================================

void DDF_IOStream::WriteInfo(const Standard_Integer nbObj,
			 const TCollection_AsciiString& dbVersion,
			 const TCollection_AsciiString& date,
			 const TCollection_AsciiString& schemaName,
			 const TCollection_AsciiString& schemaVersion,
			 const TCollection_ExtendedString& appName,
			 const TCollection_AsciiString& appVersion,
			 const TCollection_ExtendedString& dataType,
			 const TColStd_SequenceOfAsciiString& userInfo) 
{
  Standard_Integer i;
//  char *extBuffer;

  *myOStream << nbObj;
  *myOStream << "\n";
  *myOStream << dbVersion.ToCString() << "\n";
  *myOStream << date.ToCString() << "\n";
  *myOStream << schemaName.ToCString() << "\n";
  *myOStream << schemaVersion.ToCString() << "\n";
  WriteExtendedLine(appName);
  *myOStream << appVersion.ToCString() << "\n";
  WriteExtendedLine(dataType);
  *myOStream << userInfo.Length() << "\n";

  if (myOStream->bad()) Storage_StreamWriteError::Raise();

  for (i = 1; i <= userInfo.Length(); i++) {
    *myOStream << userInfo.Value(i).ToCString() << "\n";
    if (myOStream->bad()) Storage_StreamWriteError::Raise();
  }
}


//=======================================================================
//function : EndWriteInfoSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::EndWriteInfoSection() 
{
  *myOStream << "END_INFO_SECTION\n";
  if (myOStream->bad())  Storage_StreamWriteError::Raise();
  return Storage_VSOk;
}

//=======================================================================
//function : BeginReadInfoSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::BeginReadInfoSection() 
{
  Storage_Error s;
  TCollection_AsciiString l;
  Standard_Integer        len = (Standard_Integer) strlen(DDF_IOStream::MagicNumber());

  // Added because of Draw:
  // It don't go to next line after reading its own header line information!
  FlushEndOfLine();
  ReadChar(l,len);
  
  if (strncmp(DDF_IOStream::MagicNumber(),l.ToCString(),len) != 0) {
#ifdef DEB
    cout<<"BeginReadInfoSection: format error"<<endl;
#endif
    s = Storage_VSFormatError;
  }
  else {
    s = FindTag("BEGIN_INFO_SECTION");
  }

  return s;
}


// ------------------- INFO : READ


//=======================================================================
//function : ReadInfo
//purpose  : 
//=======================================================================

void DDF_IOStream::ReadInfo(Standard_Integer& nbObj,
			TCollection_AsciiString& dbVersion,
			TCollection_AsciiString& date,
			TCollection_AsciiString& schemaName,
			TCollection_AsciiString& schemaVersion,
			TCollection_ExtendedString& appName,
			TCollection_AsciiString& appVersion,
			TCollection_ExtendedString& dataType,
			TColStd_SequenceOfAsciiString& userInfo) 
{
  if (!(*myIStream >> nbObj)) Storage_StreamTypeMismatchError::Raise("ReadInfo 1");

  FlushEndOfLine();

  ReadLine(dbVersion);
  ReadLine(date);
  ReadLine(schemaName);
  ReadLine(schemaVersion);
  ReadExtendedLine(appName);
  ReadLine(appVersion);
  ReadExtendedLine(dataType);

  Standard_Integer i,len = 0;

  if (!(*myIStream >> len)) Storage_StreamTypeMismatchError::Raise("ReadInfo 2");

  FlushEndOfLine();

  TCollection_AsciiString line;

  for (i = 1; i <= len && !IsEnd(); i++) {
    ReadLine(line);
    userInfo.Append(line);
    line.Clear();
  }
}

//=======================================================================
//function : EndReadInfoSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::EndReadInfoSection() 
{ return FindTag("END_INFO_SECTION"); }


// ---------------- COMMENTS : WRITE


//=======================================================================
//function : BeginWriteCommentSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::BeginWriteCommentSection() 
{
  *myOStream << "BEGIN_COMMENT_SECTION\n";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
  return Storage_VSOk;
}

//=======================================================================
//function : WriteComment
//purpose  : 
//=======================================================================

void DDF_IOStream::WriteComment(const TColStd_SequenceOfExtendedString& aCom)
{
 Standard_Integer i,aSize;

 aSize = aCom.Length();
 *myOStream << aSize << "\n";
 if (myOStream->bad()) Storage_StreamWriteError::Raise();

 for (i = 1; i <= aSize; i++) {
   WriteExtendedLine(aCom.Value(i));
   if (myOStream->bad()) Storage_StreamWriteError::Raise();
 }
}

//=======================================================================
//function : EndWriteCommentSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::EndWriteCommentSection() 
{
  *myOStream << "END_COMMENT_SECTION\n";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
  return Storage_VSOk;
}


// ---------------- COMMENTS : READ


//=======================================================================
//function : BeginReadCommentSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::BeginReadCommentSection() 
{
  return FindTag("BEGIN_COMMENT_SECTION");
}

//=======================================================================
//function : ReadComment
//purpose  : 
//=======================================================================

void DDF_IOStream::ReadComment(TColStd_SequenceOfExtendedString& aCom)
{
  TCollection_ExtendedString line;
  Standard_Integer           len,i;

  if (!(*myIStream >> len)) Storage_StreamTypeMismatchError::Raise("ReadComment");
  
  FlushEndOfLine();  

  for (i = 1; i <= len && !IsEnd(); i++) {
    ReadExtendedLine(line);
    aCom.Append(line);
    line.Clear();
  }
}

//=======================================================================
//function : EndReadCommentSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::EndReadCommentSection() 
{ return FindTag("END_COMMENT_SECTION"); }


// --------------- TYPE : WRITE


//=======================================================================
//function : BeginWriteTypeSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::BeginWriteTypeSection() 
{
  *myOStream << "BEGIN_TYPE_SECTION\n";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
  return Storage_VSOk;
}

//=======================================================================
//function : SetTypeSectionSize
//purpose  : 
//=======================================================================

void DDF_IOStream::SetTypeSectionSize(const Standard_Integer aSize) 
{
  *myOStream << aSize << "\n";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
}

//=======================================================================
//function : WriteTypeInformations
//purpose  : 
//=======================================================================

void DDF_IOStream::WriteTypeInformations(const Standard_Integer typeNum,
				      const TCollection_AsciiString& typeName) 
{
  *myOStream << typeNum << " " << typeName.ToCString() << "\n";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
}

//=======================================================================
//function : EndWriteTypeSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::EndWriteTypeSection() 
{
  *myOStream << "END_TYPE_SECTION\n";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
  return Storage_VSOk;
}


// ------------------- TYPE : READ


//=======================================================================
//function : BeginReadTypeSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::BeginReadTypeSection() 
{ return FindTag("BEGIN_TYPE_SECTION"); }

//=======================================================================
//function : TypeSectionSize
//purpose  : 
//=======================================================================

Standard_Integer DDF_IOStream::TypeSectionSize() 
{
  Standard_Integer i;

  if (!(*myIStream >> i)) Storage_StreamTypeMismatchError::Raise("TypeSectionSize");

  FlushEndOfLine();

  return i;
}

//=======================================================================
//function : ReadTypeInformations
//purpose  : 
//=======================================================================

void DDF_IOStream::ReadTypeInformations(Standard_Integer& typeNum,
				    TCollection_AsciiString& typeName) 
{
  if (!(*myIStream >> typeNum)) Storage_StreamTypeMismatchError::Raise("ReadTypeInformations 1");
  if (!(*myIStream >> typeName)) Storage_StreamTypeMismatchError::Raise("ReadTypeInformations 2");
  FlushEndOfLine();
}

//=======================================================================
//function : EndReadTypeSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::EndReadTypeSection() 
{
  return FindTag("END_TYPE_SECTION");
}


// -------------------- ROOT : WRITE


//=======================================================================
//function : BeginWriteRootSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::BeginWriteRootSection() 
{
  *myOStream << "BEGIN_ROOT_SECTION\n";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
  return Storage_VSOk;
}

//=======================================================================
//function : SetRootSectionSize
//purpose  : 
//=======================================================================

void DDF_IOStream::SetRootSectionSize(const Standard_Integer aSize) 
{
  *myOStream << aSize << "\n";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
}

//=======================================================================
//function : WriteRoot
//purpose  : 
//=======================================================================

void DDF_IOStream::WriteRoot(const TCollection_AsciiString& rootName, const Standard_Integer aRef, const TCollection_AsciiString& rootType) 
{
  *myOStream << aRef << " " << rootName.ToCString() << " " << rootType.ToCString() << "\n";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
}

//=======================================================================
//function : EndWriteRootSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::EndWriteRootSection() 
{
  *myOStream << "END_ROOT_SECTION\n";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
  return Storage_VSOk;
}


// ----------------------- ROOT : READ


//=======================================================================
//function : BeginReadRootSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::BeginReadRootSection() 
{ return FindTag("BEGIN_ROOT_SECTION"); }

//=======================================================================
//function : RootSectionSize
//purpose  : 
//=======================================================================

Standard_Integer DDF_IOStream::RootSectionSize() 
{
  Standard_Integer i;

  if (!(*myIStream >> i)) Storage_StreamTypeMismatchError::Raise("RootSectionSize");
  
  FlushEndOfLine();
  
  return i;
}

//=======================================================================
//function : ReadRoot
//purpose  : 
//=======================================================================

void DDF_IOStream::ReadRoot(TCollection_AsciiString& rootName, Standard_Integer& aRef,TCollection_AsciiString& rootType) 
{
  if (!(*myIStream >> aRef)) Storage_StreamTypeMismatchError::Raise("ReadRoot");
  ReadWord(rootName);
  ReadWord(rootType);
}

//=======================================================================
//function : EndReadRootSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::EndReadRootSection() 
{ return FindTag("END_ROOT_SECTION"); }


// -------------------------- REF : WRITE


//=======================================================================
//function : BeginWriteRefSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::BeginWriteRefSection() 
{
  *myOStream << "BEGIN_REF_SECTION\n";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
  return Storage_VSOk;
}

//=======================================================================
//function : SetRefSectionSize
//purpose  : 
//=======================================================================

void DDF_IOStream::SetRefSectionSize(const Standard_Integer aSize) 
{
  *myOStream << aSize << "\n";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
}

//=======================================================================
//function : WriteReferenceType
//purpose  : 
//=======================================================================

void DDF_IOStream::WriteReferenceType(const Standard_Integer reference,
				  const Standard_Integer typeNum) 
{
  *myOStream << reference << " " << typeNum << "\n";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
}

//=======================================================================
//function : EndWriteRefSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::EndWriteRefSection() 
{
  *myOStream << "END_REF_SECTION\n";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
  return Storage_VSOk;
}


// ----------------------- REF : READ


//=======================================================================
//function : BeginReadRefSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::BeginReadRefSection() 
{ return FindTag("BEGIN_REF_SECTION"); }

//=======================================================================
//function : RefSectionSize
//purpose  : 
//=======================================================================

Standard_Integer DDF_IOStream::RefSectionSize() 
{
  Standard_Integer i;

  if (!(*myIStream >> i)) Storage_StreamTypeMismatchError::Raise("RefSectionSize");
  FlushEndOfLine();

  return i;
}

//=======================================================================
//function : ReadReferenceType
//purpose  : 
//=======================================================================

void DDF_IOStream::ReadReferenceType(Standard_Integer& reference,
				 Standard_Integer& typeNum) 
{
  if (!(*myIStream >> reference)) Storage_StreamTypeMismatchError::Raise("ReadReferenceType 1");
  if (!(*myIStream >> typeNum)) Storage_StreamTypeMismatchError::Raise("ReadReferenceType 2");
  FlushEndOfLine();
}

//=======================================================================
//function : EndReadRefSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::EndReadRefSection() 
{
  return FindTag("END_REF_SECTION");
}


// -------------------- DATA : WRITE


//=======================================================================
//function : BeginWriteDataSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::BeginWriteDataSection() 
{
  *myOStream << "BEGIN_DATA_SECTION";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
  return Storage_VSOk;
}

//=======================================================================
//function : WritePersistentObjectHeader
//purpose  : 
//=======================================================================

void DDF_IOStream::WritePersistentObjectHeader(const Standard_Integer aRef,
					   const Standard_Integer aType) 
{
  *myOStream << "\n#" << aRef << "=%" << aType;
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
}

//=======================================================================
//function : BeginWritePersistentObjectData
//purpose  : 
//=======================================================================

void DDF_IOStream::BeginWritePersistentObjectData() 
{
  *myOStream << "( ";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
}

//=======================================================================
//function : BeginWriteObjectData
//purpose  : 
//=======================================================================

void DDF_IOStream::BeginWriteObjectData() 
{
  *myOStream << "( ";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
}

//=======================================================================
//function : EndWriteObjectData
//purpose  : 
//=======================================================================

void DDF_IOStream::EndWriteObjectData() 
{
  *myOStream << ") ";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
}

//=======================================================================
//function : EndWritePersistentObjectData
//purpose  : 
//=======================================================================

void DDF_IOStream::EndWritePersistentObjectData() 
{
  *myOStream << ")";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
}

//=======================================================================
//function : EndWriteDataSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::EndWriteDataSection() 
{
  *myOStream << "\nEND_DATA_SECTION\n";
  if (myOStream->bad()) Storage_StreamWriteError::Raise();
  return Storage_VSOk;
}


// ---------------------- DATA : READ


//=======================================================================
//function : BeginReadDataSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::BeginReadDataSection() 
{ return FindTag("BEGIN_DATA_SECTION"); }

//=======================================================================
//function : ReadPersistentObjectHeader
//purpose  : 
//=======================================================================

void DDF_IOStream::ReadPersistentObjectHeader(Standard_Integer& aRef,
					  Standard_Integer& aType) 
{
  char c;

  myIStream->get(c);

  while (c != '#') {
    if (IsEnd() || (c != ' ') || (c == '\n')) {
      Storage_StreamFormatError::Raise();
    }
    myIStream->get(c);
  }

  if (!(*myIStream >> aRef)) Storage_StreamTypeMismatchError::Raise("ReadPersistentObjectHeader 1");
  myIStream->get(c);

  while (c != '=') {
    if (IsEnd() || (c != ' ') || (c == '\n')) {
      Storage_StreamFormatError::Raise();
    }
    myIStream->get(c);
  }

  myIStream->get(c);

  while (c != '%') {
    if (IsEnd() || (c != ' ') || (c == '\n')) {
      Storage_StreamFormatError::Raise();
    }
    myIStream->get(c);
  }

  if (!(*myIStream >> aType)) Storage_StreamTypeMismatchError::Raise("ReadPersistentObjectHeader 2");
}

//=======================================================================
//function : BeginReadPersistentObjectData
//purpose  : 
//=======================================================================

void DDF_IOStream::BeginReadPersistentObjectData() 
{
  char c;
  myIStream->get(c);
  while (c != '(') {
    if (IsEnd() || (c != ' ') || (c == '\n')) {
      Storage_StreamFormatError::Raise();
    }
    myIStream->get(c);
  }
}

//=======================================================================
//function : BeginReadObjectData
//purpose  : 
//=======================================================================

void DDF_IOStream::BeginReadObjectData() 
{
  char c;
  myIStream->get(c);
  while (c != '(') {
    if (IsEnd() || (c != ' ') || (c == '\n')) {
      Storage_StreamFormatError::Raise("BeginReadObjectData");
    }
    myIStream->get(c);
  }
}

//=======================================================================
//function : EndReadObjectData
//purpose  : 
//=======================================================================

void DDF_IOStream::EndReadObjectData() 
{
  char c;
  myIStream->get(c);
  while (c != ')') {
    if (IsEnd() || (c != ' ') || (c == '\n')) {
      Storage_StreamFormatError::Raise("EndReadObjectData");
    }
    myIStream->get(c);
  }
}

//=======================================================================
//function : EndReadPersistentObjectData
//purpose  : 
//=======================================================================

void DDF_IOStream::EndReadPersistentObjectData() 
{
  char c;

  myIStream->get(c);
  while (c != ')') {
    if (IsEnd() || (c != ' ') || (c == '\n')) {
      Storage_StreamFormatError::Raise("EndReadPersistentObjectData");
    }
    myIStream->get(c);
  }

  myIStream->get(c);
  while (c != '\n') {
    if (IsEnd() || (c != ' ')) {
      Storage_StreamFormatError::Raise();
    }
    myIStream->get(c);
  }
}

//=======================================================================
//function : EndReadDataSection
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::EndReadDataSection() 
{ return FindTag("END_DATA_SECTION"); }

//=======================================================================
//function : IsGoodFileType
//purpose  : 
//=======================================================================

Storage_Error DDF_IOStream::IsGoodFileType(istream* anIStream)
{
  DDF_IOStream      f;
  Storage_Error s;

  s = f.Open(anIStream);

  if (s == Storage_VSOk) {
    TCollection_AsciiString l;
    Standard_Integer        len = (Standard_Integer) strlen(DDF_IOStream::MagicNumber());

    f.ReadChar(l,len);

    f.Close();

    if (strncmp(DDF_IOStream::MagicNumber(),l.ToCString(),len) != 0) {
#ifdef DEB
    cout<<"IsGoodFileType: format error"<<endl;
#endif
      s = Storage_VSFormatError;
    }
  }

  return s;
}

