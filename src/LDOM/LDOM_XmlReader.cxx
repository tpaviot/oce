// Created on: 2001-07-20
// Created by: Alexander GRIGORIEV
// Copyright (c) 2001-2012 OPEN CASCADE SAS
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

//AGV 060302: Input from istream
//            AGV 130302: bug corr: was error if strlen(root_elem_name) < 7

#include <LDOM_XmlReader.hxx>
#include <Standard_Stream.hxx>
#include <LDOM_MemManager.hxx>
#include <LDOM_BasicAttribute.hxx>
#include <LDOM_CharReference.hxx>
#include <LDOM_OSStream.hxx>

#include <string.h>
#include <errno.h>
#ifdef WNT
#include <io.h>
#else
#include <unistd.h>
#endif

//#include <ctype.h>

const int XML_MIN_BUFFER = 10;
const int MAX_ATTRIBUTES = 512;
const int FILE_NONVALUE  = -1;

typedef enum {
  STATE_WAITING = 0,
  STATE_HEADER,
  STATE_DOCTYPE,
  STATE_DOCTYPE_MARKUP,
  STATE_ELEMENT,
  STATE_ELEMENT_END,
  STATE_ATTRIBUTE_NAME,
  STATE_ATTRIBUTE_EQUAL,
  STATE_ATTRIBUTE_VALUE,
  STATE_COMMENT,
  STATE_CDATA,
  STATE_TEXT
} ParserState;

#define TEXT_COMPARE(aPtr,aPattern) \
  (memcmp ((aPtr), (aPattern), sizeof(aPattern) - 1) == 0)

static Standard_Boolean isName          (const char             * aString,
                                         const char             * aStringEnd,
                                         const char             *& aNameEnd);

//=======================================================================
//function : LDOM_XmlReader()
//purpose  : Constructor (file descriptor)
//=======================================================================

LDOM_XmlReader::LDOM_XmlReader (const int                       aFileDes,
                                const Handle(LDOM_MemManager)&  aDocument,
                                TCollection_AsciiString&        anErrorString)
     : myEOF            (Standard_False),
       myFileDes        (aFileDes),
#ifdef WNT
       myIStream        (cin),  // one quirk of MSVC6.0: can't initialise by 0
#else
       myIStream        (* (istream *) UndefinedHandleAddress),
#endif
       myError          (anErrorString),
       myDocument       (aDocument),
       myPtr            (&myBuffer[0]),
       myEndPtr         (&myBuffer[0])
{}

//=======================================================================
//function : LDOM_XmlReader()
//purpose  : Constructor (istream)
//=======================================================================

LDOM_XmlReader::LDOM_XmlReader (istream&                        anInput,
                                const Handle(LDOM_MemManager)&  aDocument,
                                TCollection_AsciiString&        anErrorString)
     : myEOF            (Standard_False),
       myFileDes        (FILE_NONVALUE),
       myIStream        (anInput),
       myError          (anErrorString),
       myDocument       (aDocument),
       myPtr            (&myBuffer[0]),
       myEndPtr         (&myBuffer[0])
{}

//=======================================================================
//function : ReadRecord
//purpose  : Read a record from XML file
//=======================================================================

LDOM_XmlReader::RecordType LDOM_XmlReader::ReadRecord
                                        (LDOM_OSStream& theData)
{
  theData.Clear();
  myError.Clear();
  ParserState aState = STATE_WAITING;
  const char * aStartData = NULL, * aNameEnd = NULL, * aPtr;
  LDOMBasicString anAttrName, anAttrValue;
  char anAttDelimiter = '\0';

  while (1) {
    //  Check if the current file buffer is exhausted
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //  There should always be some bytes available in the buffer for analysis
    Standard_Integer aBytesRest = myEndPtr - myPtr;
    if (aBytesRest < XML_MIN_BUFFER) {
      if (myEOF == Standard_True) {
        if (aBytesRest <= 0)
          break;                        // END of processing
      } else {
      // If we are reading some data, save the beginning and preserve the state
        if (aStartData /* && aState != STATE_WAITING */) {
          if (myPtr > aStartData)
            theData.rdbuf()->sputn(aStartData, myPtr - aStartData);
          aStartData = &myBuffer[0];
        }
      // Copy the rest of file data to the beginning of buffer
        if (aBytesRest > 0)
          memcpy (&myBuffer[0], myPtr, aBytesRest);

      // Read the full buffer and reset start and end buffer pointers
        myPtr    = &myBuffer[0];
        std::streamsize aNBytes;
        if (myFileDes != FILE_NONVALUE)
          aNBytes = read (myFileDes, &myBuffer[aBytesRest],
                          XML_BUFFER_SIZE - aBytesRest);
        else {
          myIStream.read (&myBuffer[aBytesRest],
                          XML_BUFFER_SIZE - aBytesRest);
          aNBytes = myIStream.gcount();
        }
        if (aNBytes == 0)
          myEOF = Standard_True;                  // END-OF-FILE
        myEndPtr = &myBuffer[aBytesRest + aNBytes];
        myBuffer[aBytesRest + aNBytes] = '\0';
      }
    }

    //  Check the character data
    switch (aState) {

      // Checking the characters in STATE_WAITING (blank, TEXT or markup)
      // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case STATE_WAITING:
      switch (myPtr[0]) {
      case ' ':
      case '\t':
      case '\n':
      case '\r':
        ++ myPtr;
        continue;
      case '<':
        // XML markup found, then make detect the record type
        switch (myPtr[1]) {
        case '?':
          aState = STATE_HEADER;
          myPtr += 2;
          aStartData = myPtr;
          continue;
        case '/':
          aState = STATE_ELEMENT_END;
          myPtr += 2;
          aStartData = myPtr;
          continue;
        case '!':
          if (myPtr[2] == '-' && myPtr[3] == '-') {
            aState = STATE_COMMENT;
            myPtr += 4;
          } else if (TEXT_COMPARE (&myPtr[2], "DOCTYPE")) {
            char ch = myPtr[9];
            if (ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r')
              break;
            aState = STATE_DOCTYPE;
            myPtr += 10;
          } else if (TEXT_COMPARE (&myPtr[2], "[CDATA[")) {
            aState = STATE_CDATA;
            myPtr += 9;
          } else break;                   // ERROR
          aStartData = myPtr;
          continue;
        default:
          if (::isName (&myPtr[1], myEndPtr, aNameEnd)) {
            aStartData = myPtr + 1;
            myPtr = aNameEnd;
            if (myPtr < myEndPtr) {
              myElement = & LDOM_BasicElement::Create (aStartData,
                                                       myPtr - aStartData,
                                                       myDocument);
              myLastChild = NULL;
              aState = STATE_ATTRIBUTE_NAME;
              aStartData = NULL;
            }else
              aState = STATE_ELEMENT;
            continue;
          }       // otherwise ERROR
        }     // end of switch
        myError = "Unknown XML object: ";
        myError += TCollection_AsciiString ((const Standard_CString)myPtr,
                                            XML_MIN_BUFFER);
        return XML_UNKNOWN;
      case '\0':
        if (myEOF == Standard_True) continue;
      default:
        //      Limitation: we do not treat '&' as special character
        aPtr = (const char *) memchr (myPtr, '<', myEndPtr - myPtr);
        if (aPtr) {
          // The end of text field reached
          theData.rdbuf()->sputn(myPtr, aPtr - myPtr);
          myPtr = aPtr;
          return XML_TEXT;
        }
        aState = STATE_TEXT;
        aStartData = myPtr;
        myPtr = myEndPtr;
      }   // end of checking in STATE_WAITING
      continue;

      // Checking the characters in STATE_HEADER, seek for "?>" sequence
      // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case STATE_HEADER:
      aPtr = (const char *) memchr (aStartData, '?', (myEndPtr-1) - aStartData);
      if (aPtr) {
        // The end of XML declaration found
        if (aPtr[1] != '>') {           // ERROR
          myError = "Character \'>\' is expected in the end of XML declaration";
          return XML_UNKNOWN;
        }
        // The XML declaration is retrieved
        theData.rdbuf()->sputn(aStartData, aPtr - aStartData);
        myPtr = aPtr + 2;
        return XML_HEADER;
      }
      myPtr = myEndPtr - 1;
      continue;

      // Checking the characters in STATE_DOCTYPE, seek for "]>" sequence
      // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case STATE_DOCTYPE:
      for (aPtr = aStartData; aPtr < myEndPtr-1; aPtr++) {
        const int aChar = aPtr[0];
        if (aChar == '[') {
          aState = STATE_DOCTYPE_MARKUP;
          aStartData = &aPtr[1];
          goto state_doctype_markup;
        }
        if (aChar == '>') {
          // The DOCTYPE declaration is retrieved
          theData.rdbuf()->sputn(aStartData, aPtr - aStartData - 1);
          myPtr = aPtr + 1;
          return XML_DOCTYPE;
        }
      }
      myPtr = myEndPtr - 1;
      continue;

    state_doctype_markup:
    case STATE_DOCTYPE_MARKUP:
      aPtr = (const char *) memchr (aStartData, ']', (myEndPtr-1) - aStartData);
      if (aPtr) {
        // The end of DOCTYPE declaration found
        if (aPtr[1] != '>') {           // ERROR
          myError =
            "Character \'>\' is expected in the end of DOCTYPE declaration";
          return XML_UNKNOWN;
        }
        // The DOCTYPE declaration is retrieved
        theData.rdbuf()->sputn(aStartData, aPtr - aStartData);
        myPtr = aPtr + 2;
        return XML_DOCTYPE;
      }
      myPtr = myEndPtr - 1;
      continue;

        // Checking the characters in STATE_COMMENT, seek for "-->" sequence
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case STATE_COMMENT:
      aPtr = aStartData;
      while (1) {
        aPtr = (const char *) memchr (aPtr, '-', (myEndPtr - 2) - aPtr);
        if (aPtr == NULL) break;
        if (aPtr[1] != '-') ++ aPtr;
        else {
          if (aPtr[2] != '>') {       // ERROR
            myError = "Character \'>\' is expected in the end of comment";
            return XML_UNKNOWN;
          }
          theData.rdbuf()->sputn(aStartData, aPtr - aStartData);
          myPtr = aPtr + 3;
          return XML_COMMENT;
        }
      }
      myPtr = myEndPtr - 2;
      continue;

        // Checking the characters in STATE_TEXT, seek for "<"
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case STATE_TEXT:
      aPtr = (const char *) memchr (aStartData, '<', myEndPtr - aStartData);
      if (aPtr) {
        // The end of text field reached
        theData.rdbuf()->sputn(aStartData, aPtr - aStartData);
        myPtr = aPtr;
        return XML_TEXT;
      }
      myPtr = myEndPtr;
      continue;

        // Checking the characters in STATE_CDATA, seek for "]]"
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case STATE_CDATA:
      aPtr = aStartData;
      while (1) {
        aPtr = (const char *) memchr (aPtr, ']', (myEndPtr - 1) - aStartData);
        if (aPtr == NULL) break;
        if (aPtr[1] != ']') {           // ERROR
          myError = "Characters \']]\' are expected in the end of CDATA";
          return XML_UNKNOWN;
        }
        theData.rdbuf()->sputn(aStartData, aPtr - aStartData);
        myPtr = aPtr + 2;
        return XML_CDATA;
      }
      myPtr = myEndPtr - 1;
      continue;

        // Checking the characters in STATE_ELEMENT, seek the end of TagName
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case STATE_ELEMENT:
      if (::isName (myPtr, myEndPtr, aNameEnd) == Standard_False)
        if (theData.Length() == 0 || aNameEnd != myPtr) {
          myError = "Invalid tag name";
          return XML_UNKNOWN;
        }
      {
        theData.rdbuf()->sputn(aStartData, aNameEnd - aStartData);
        char* aDataString = (char *)theData.str();
        myElement = & LDOM_BasicElement::Create (aDataString, theData.Length(),
                                                 myDocument);
        theData.Clear();
        myLastChild = NULL;
        delete [] aDataString;
        aState = STATE_ATTRIBUTE_NAME;
        aStartData = NULL;
        myPtr = aNameEnd;
        continue;
      }
        // Parsing a single attribute (STATE_ATTRIBUTE)
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case STATE_ATTRIBUTE_NAME:          // attribute name
      switch (myPtr[0]) {
      case ' ' :
      case '\t':
      case '\n':
      case '\r':
        if (aStartData) goto attr_name;
        ++ myPtr;
        continue;
      case '/' :
        if (aStartData)
          myError = "Inexpected end of attribute";
        else if (myPtr[1] != '>')
          myError = "Improper element tag termination";
        else {
          myPtr += 2;
#ifdef DEB
          theData.Clear();
          theData << myElement->GetTagName();
#endif
          return XML_FULL_ELEMENT;
        }
        return XML_UNKNOWN;
      case '>' :
        if (aStartData) {
          myError = "Inexpected end of attribute";
          return XML_UNKNOWN;
        }
        ++ myPtr;
#ifdef DEB
        theData.Clear();
        theData << myElement->GetTagName();
#endif
        return XML_START_ELEMENT;
      default  :
        if (::isName (myPtr, myEndPtr, aNameEnd) == Standard_False)
          if (theData.Length() == 0 || aNameEnd != myPtr) {
            myError = "Invalid attribute name";
            return XML_UNKNOWN;
          }
        if (aNameEnd >= myEndPtr)
          aStartData = myPtr;
        else {
          if (theData.Length() == 0)
            anAttrName = LDOMBasicString(myPtr, aNameEnd - myPtr, myDocument);
          else {
            theData.rdbuf()->sputn(myPtr, aNameEnd - myPtr);
attr_name:
            char* aDataString = (char *)theData.str();
            theData.Clear();
            anAttrName = LDOMBasicString (aDataString, myDocument);
            delete [] aDataString;
          }
          aStartData = NULL;
          aState = STATE_ATTRIBUTE_EQUAL;
        }
        myPtr = aNameEnd;
        continue;
      }
    case STATE_ATTRIBUTE_EQUAL:          // attribute 'equal' sign
      switch (myPtr[0]) {
      case '=' :
        aState = STATE_ATTRIBUTE_VALUE;
      case ' ' :
      case '\t':
      case '\n':
      case '\r':
        ++ myPtr;
        continue;
      default:
        myError = "Equal sign expected in attribute definition";
        return XML_UNKNOWN;
      }

    case STATE_ATTRIBUTE_VALUE:          // attribute value
      switch (myPtr[0]) {
      case ' ' :
      case '\t':
      case '\n':
      case '\r':
        if (aStartData == NULL) {
          ++ myPtr;
          continue;
      default:
          if (anAttDelimiter == '\0') {
            myError = "Expected an attribute value";
            return XML_UNKNOWN;
      case '\"':
      case '\'':
            if (aStartData == NULL) {
              aStartData     = &myPtr[1];
              anAttDelimiter = myPtr[0];
            }
          }
        }
        //      Limitation: we do not take into account that '<' and '&'
        //      are not allowed in attribute values
        aPtr = (const char *) memchr (aStartData, anAttDelimiter,
                                      myEndPtr - aStartData);
        if (aPtr) {
          (char&) aPtr[0] = '\0';
          anAttDelimiter  = '\0';
          char          * aDataString   = (char *) aStartData;
          const char    * ePtr          = aPtr;

          //    Append the end of the string to previously taken data
          if (theData.Length() > 0) {
            theData.rdbuf()->sputn(aStartData, aPtr-aStartData);
            aDataString = (char *)theData.str();
            ePtr = strchr (aDataString, '\0');
          }

          Standard_Integer aDataLen;
          aDataString = LDOM_CharReference::Decode (aDataString, aDataLen);
          if (IsDigit(aDataString[0])) {
            if (getInteger (anAttrValue, aDataString, ePtr))
              anAttrValue = LDOMBasicString (aDataString,aDataLen,myDocument);
          } else
            anAttrValue = LDOMBasicString (aDataString, aDataLen, myDocument);

          if (theData.Length() > 0) {
            theData.Clear();
            delete [] aDataString;
          }
          //    Create an attribute
          myLastChild = myElement -> AddAttribute (anAttrName, anAttrValue,
                                                   myDocument, myLastChild);
          myPtr = aPtr + 1;
          aStartData = NULL;
          aState = STATE_ATTRIBUTE_NAME;
        } else
          myPtr = myEndPtr;
        continue;
      }
        // Checking the characters in STATE_ELEMENT_END, seek for ">"
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    case STATE_ELEMENT_END:
      aPtr = (const char *) memchr (aStartData, '>', myEndPtr - aStartData);
      if (aPtr) {
        // The end of the end-element markup
        theData.rdbuf()->sputn(aStartData, aPtr - aStartData);
        myPtr = aPtr + 1;
        return XML_END_ELEMENT;
      }
      myPtr = myEndPtr;
      continue;
    }
  }
  if (aState != STATE_WAITING) {
    myError = "Unexpected end of file";
    return XML_UNKNOWN;
  }
  return XML_EOF;
}

//=======================================================================
//function : isName
//type     : static
//purpose  : Check if aString is a valid XML Name
//=======================================================================

static Standard_Boolean isName (const char  * aString,
                                const char  * aStringEnd,
                                const char  *& aNameEnd)
{
  Standard_Boolean aResult;
  Standard_Character aCh = aString[0];
  if (IsAlphabetic(aCh) || aCh == '_' || aCh == ':') {
    const char * aPtr = &aString[1];
    while (aPtr < aStringEnd) {
      aCh = * aPtr;
      switch (aCh) {
      case ' ' :
      case '\n':
      case '\r':
      case '\t':
      case '=' :
      case '\0':
      case '/' :
      case '>' :
        aNameEnd = aPtr;
        return Standard_True;
      default:
        if (IsAlphanumeric(aCh) == 0) {
          aNameEnd = aPtr;
          return Standard_False;
        }
      case '.' :
      case '-' :
      case '_' :
      case ':' :
        ++ aPtr;
      }
    }
    aNameEnd = aPtr;
    aResult = Standard_True;
  } else {
    aNameEnd = aString;
    aResult = Standard_False;
  }
  return aResult;
}

//=======================================================================
//function : getInteger
//purpose  : Try to initialize theValue as Integer; return False on success
//=======================================================================

Standard_Boolean LDOM_XmlReader::getInteger (LDOMBasicString&    theValue,
                                             const char          * theStart,
                                             const char          * theEnd)
{
  char * ptr;
  errno = 0;
  if (theEnd - theStart == 1 || theStart[0] != '0')
  {
      long aResult = strtol (theStart, &ptr, 10);
      if (ptr == theEnd && errno == 0) 
      {
        theValue = Standard_Integer(aResult);
        return Standard_False;
      }
  }
  return Standard_True;
}
