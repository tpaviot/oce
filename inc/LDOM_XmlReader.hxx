// Created on: 2001-07-20
// Created by: Alexander GRIGORIEV
// Copyright (c) 2001-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

//AGV 060302: Input from istream
//            AGV 130302: bug corr: was error if strlen(root_elem_name) < 7

#ifndef LDOM_XmlReader_HeaderFile
#define LDOM_XmlReader_HeaderFile

//#define XML_BUFFER_SIZE 1000
#define XML_BUFFER_SIZE 20480

#include <LDOM_BasicElement.hxx>

class TCollection_AsciiString;
class LDOM_OSStream;

//  Class LDOM_XmlReader
//

class LDOM_XmlReader 
{
 public:
  enum RecordType {
    XML_UNKNOWN,
    XML_HEADER,
    XML_DOCTYPE,
    XML_COMMENT,
    XML_START_ELEMENT,
    XML_END_ELEMENT,
    XML_FULL_ELEMENT,
    XML_TEXT,
    XML_CDATA,
    XML_EOF
  };

  // ---------- PUBLIC METHODS ----------
  LDOM_XmlReader (const int aFileDes, const Handle(LDOM_MemManager)& aDocument,
                  TCollection_AsciiString& anErrorString);
  // Constructor - takes a file descriptor for input

  LDOM_XmlReader (istream& anInput, const Handle(LDOM_MemManager)& aDocument,
                  TCollection_AsciiString& anErrorString);
  // Constructor - takes an istream for input

  RecordType            ReadRecord      (LDOM_OSStream& theData);
  // reading a markup or other element of XML format

  LDOM_BasicElement&    GetElement      () const        { return * myElement; }
  // get the last element retrieved from the stream

  static Standard_Boolean getInteger    (LDOMBasicString&       theValue,
                                         const char             * theStart,
                                         const char             * theEnd);
  // try convert string theStart to LDOM_AsciiInteger, return False on success

 private:
  // ---------- PRIVATE (PROHIBITED) METHODS ----------
  LDOM_XmlReader (const LDOM_XmlReader& theOther);
  // Copy constructor

  LDOM_XmlReader& operator = (const LDOM_XmlReader& theOther);
  // Assignment

 private:
  // ---------- PRIVATE FIELDS ----------

  Standard_Boolean              myEOF;
  int                           myFileDes; // alternative 1: file descriptor
  istream&                      myIStream; // alternative 2: istream
  TCollection_AsciiString       & myError;
  Handle(LDOM_MemManager)       myDocument;
  LDOM_BasicElement             * myElement;
  const LDOM_BasicNode          * myLastChild;  // optim. reading attributes
  const char                    * myPtr;
  const char                    * myEndPtr;
  char                          myBuffer [XML_BUFFER_SIZE+4];
};

#endif
