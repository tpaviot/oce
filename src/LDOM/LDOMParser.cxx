// File:      LDOMParser.cxx
// Created:   20.07.01 14:58:24
// Author:    Alexander GRIGORIEV
// Copyright: OpenCascade 2001
// History:   AGV 060302: Input from istream
//            AGV 130302: Return error if there are data after the root element

//#define LDOM_PARSER_TRACE

#include <LDOMParser.hxx>
#include <LDOM_MemManager.hxx>
#include <LDOM_XmlReader.hxx>
#include <LDOM_BasicText.hxx>
#include <LDOM_CharReference.hxx>

#include <fcntl.h>
#ifdef WNT
#include <io.h>
#else
#include <unistd.h>
#endif

//=======================================================================
//function : ~LDOMParser
//purpose  : 
//=======================================================================

LDOMParser::~LDOMParser()
{
  if (myReader) delete myReader;
}

//=======================================================================
//function : ReadRecord
//purpose  : Take the next lexical element from XML stream
//=======================================================================

#ifdef LDOM_PARSER_TRACE
static
#else
inline
#endif
        LDOM_XmlReader::RecordType ReadRecord (LDOM_XmlReader&  aReader,
                                               LDOM_OSStream&   aData)
{
#ifdef LDOM_PARSER_TRACE
  static aCounter = 0;
  ++ aCounter;
#endif
  const LDOM_XmlReader::RecordType aType = aReader.ReadRecord (aData);
#ifdef LDOM_PARSER_TRACE
  static FILE * ff = NULL;
  TCollection_AsciiString aTraceFileName;
#ifdef WNT
  aTraceFileName = TCollection_AsciiString (getenv("TEMP")) + "\\ldom.trace";
#else
  aTraceFileName = "/tmp/ldom.trace";
#endif
  ff = fopen (aTraceFileName.ToCString(),ff ? "at": "wt");
  const char * aDataType;
  switch (aType) {
  case LDOM_XmlReader::XML_UNKNOWN:       aDataType= "XML_UNKNOWN      "; break;
  case LDOM_XmlReader::XML_HEADER:        aDataType= "XML_HEADER       "; break;
  case LDOM_XmlReader::XML_DOCTYPE:       aDataType= "XML_DOCTYPE      "; break;
  case LDOM_XmlReader::XML_COMMENT:       aDataType= "XML_COMMENT      "; break;
  case LDOM_XmlReader::XML_START_ELEMENT: aDataType= "XML_START_ELEMENT"; break;
  case LDOM_XmlReader::XML_END_ELEMENT:   aDataType= "XML_END_ELEMENT  "; break;
  case LDOM_XmlReader::XML_FULL_ELEMENT:  aDataType= "XML_FULL_ELEMENT "; break;
  case LDOM_XmlReader::XML_TEXT:          aDataType= "XML_TEXT         "; break;
  case LDOM_XmlReader::XML_CDATA:         aDataType= "XML_CDATA        "; break;
  case LDOM_XmlReader::XML_EOF:           aDataType= "XML_EOF          ";
  }
  char * aStr = aData.str();
  fprintf (ff, "%5d %s: %s\n", aCounter, aDataType, aStr);
  delete [] aStr;
  fclose (ff);
#endif
  return aType;
}

//=======================================================================
//function : GetError
//purpose  : Return text describing a parsing error
//=======================================================================

const TCollection_AsciiString& LDOMParser::GetError
                                (TCollection_AsciiString& aData) const
{
  char * aStr =(char *)myCurrentData.str();
  aData = aStr;
  delete [] aStr;
  return myError;
}

//=======================================================================
//function : parse
//purpose  :
//=======================================================================

Standard_Boolean LDOMParser::parse (istream& anInput)
{
  // Open the DOM Document
  myDocument = new LDOM_MemManager (20000);
  myError.Clear();

  // Create the Reader instance
  if (myReader) delete myReader;
  myReader = new LDOM_XmlReader (anInput, myDocument, myError);

  // Parse
  return ParseDocument();
}

//=======================================================================
//function : parse
//purpose  :
//=======================================================================

Standard_Boolean LDOMParser::parse (const char * const aFileName)
{
  // Open the DOM Document
  myDocument = new LDOM_MemManager (20000);
  myError.Clear ();

  // Open the file
  int aFile = open (aFileName, O_RDONLY);
  if (aFile < 0) {
    myError = "Fatal XML error: Cannot open XML file";
    return Standard_True;
  }

  // Create the Reader instance
  if (myReader) delete myReader;
  myReader = new LDOM_XmlReader (aFile, myDocument, myError);

  // Parse
  Standard_Boolean isError = ParseDocument();
  close (aFile);
  return isError;
}

//=======================================================================
//function : ParseDocument
//purpose  : parse the whole document (abstracted from the XML source)
//=======================================================================

Standard_Boolean LDOMParser::ParseDocument ()
{
  Standard_Boolean      isError   = Standard_False;
  Standard_Boolean      isElement = Standard_False;
  Standard_Boolean      isDoctype = Standard_False;

  while (1) {
    LDOM_XmlReader::RecordType aType = ReadRecord (*myReader, myCurrentData);
    switch (aType) {
    case LDOM_XmlReader::XML_HEADER:
      if (isDoctype || isElement) {
        myError = "Unexpected XML declaration";
        isError = Standard_True;
        break;
      }
      continue;
    case LDOM_XmlReader::XML_DOCTYPE:
      if (isElement) {
        myError = "Unexpected DOCTYPE declaration";
        isError = Standard_True;
        break;
      }
      isDoctype = Standard_True;
    case LDOM_XmlReader::XML_COMMENT:
      continue;
    case LDOM_XmlReader::XML_FULL_ELEMENT:
      if (isElement == Standard_False) {
        isElement = Standard_True;
        myDocument -> myRootElement = &myReader -> GetElement ();
        if (startElement()) {
          isError = Standard_True;
          myError = "User abort at startElement()";
          break;
        }
        if (endElement()) {
          isError = Standard_True;
          myError = "User abort at endElement()";
          break;
        }
        continue;
      }
    case LDOM_XmlReader::XML_START_ELEMENT:
      if (isElement == Standard_False) {
        isElement = Standard_True;
        myDocument -> myRootElement = &myReader -> GetElement ();
        if (startElement()) {
          isError = Standard_True;
          myError = "User abort at startElement()";
          break;
        }
        isError = ParseElement ();
        if (isError) break;
        continue;
      }
      isError = Standard_True;
      myError = "Expected comment or end-of-file";
    case LDOM_XmlReader::XML_END_ELEMENT:
      if (endElement()) {
        isError = Standard_True;
        myError = "User abort at endElement()";
      }
    case LDOM_XmlReader::XML_EOF:
      break;
    case LDOM_XmlReader::XML_UNKNOWN:
      if (isElement) {
    default:
        myError = "Unexpected data beyond the Document Element";
      }
      isError = Standard_True;
    }
    break;
  }
  return isError;
}

//=======================================================================
//function : ParseElement
//purpose  : parse one element, given the type of its XML presentation
//=======================================================================

Standard_Boolean LDOMParser::ParseElement ()
{
  Standard_Boolean  isError = Standard_False;
  const LDOM_BasicElement * aParent = &myReader->GetElement();
  const LDOM_BasicNode    * aLastChild = NULL;
  while (1) {
    LDOM_Node::NodeType aLocType;
    LDOMBasicString     aTextValue;
    char *aTextStr;
    LDOM_XmlReader::RecordType aType = ReadRecord (* myReader, myCurrentData);
    switch (aType) {
    case LDOM_XmlReader::XML_UNKNOWN:
      isError = Standard_True;
      break;
    case LDOM_XmlReader::XML_FULL_ELEMENT:
      aParent -> AppendChild (&myReader -> GetElement(), aLastChild);
      if (startElement()) {
        isError = Standard_True;
        myError = "User abort at startElement()";
        break;
      }
      if (endElement()) {
        isError = Standard_True;
        myError = "User abort at endElement()";
        break;
      }
      break;
    case LDOM_XmlReader::XML_START_ELEMENT:
      aParent -> AppendChild (&myReader -> GetElement(), aLastChild);
      if (startElement()) {
        isError = Standard_True;
        myError = "User abort at startElement()";
        break;
      }
      isError = ParseElement ();
      break;
    case LDOM_XmlReader::XML_END_ELEMENT:
      {
        Standard_CString aParentName = Standard_CString(aParent->GetTagName());
        aTextStr = (char *)myCurrentData.str();
        if (strcmp(aTextStr, aParentName) != 0) {
          myError = "Expected end tag \'";
          myError += aParentName;
          myError += "\'";
          isError = Standard_True;
        }
        else if (endElement()) {
          isError = Standard_True;
          myError = "User abort at endElement()";
        }
        delete [] aTextStr;
      }
      return isError;
    case LDOM_XmlReader::XML_TEXT:
      aLocType = LDOM_Node::TEXT_NODE;
      {
        Standard_Integer aTextLen;
        aTextStr = LDOM_CharReference::Decode ((char *)myCurrentData.str(), aTextLen);
        // try to convert to integer
        if (IsDigit(aTextStr[0])) {
          if (LDOM_XmlReader::getInteger (aTextValue, aTextStr,
                                          aTextStr + aTextLen))
            aTextValue = LDOMBasicString (aTextStr, aTextLen, myDocument);
        } else
          aTextValue = LDOMBasicString (aTextStr, aTextLen, myDocument);
      }
      goto create_text_node;
    case LDOM_XmlReader::XML_COMMENT:
      aLocType = LDOM_Node::COMMENT_NODE;
      {
        Standard_Integer aTextLen;
        aTextStr = LDOM_CharReference::Decode ((char *)myCurrentData.str(), aTextLen);
        aTextValue = LDOMBasicString (aTextStr, aTextLen, myDocument);
      }
      goto create_text_node;
    case LDOM_XmlReader::XML_CDATA:
      aLocType = LDOM_Node::CDATA_SECTION_NODE;
      aTextStr = (char *)myCurrentData.str();
      aTextValue = LDOMBasicString(aTextStr,myCurrentData.Length(),myDocument);
    create_text_node:
      {
        LDOM_BasicNode& aTextNode =
          LDOM_BasicText::Create (aLocType, aTextValue, myDocument);
        aParent -> AppendChild (&aTextNode, aLastChild);
      }
      delete [] aTextStr;
      break;
    case LDOM_XmlReader::XML_EOF:
      myError = "Inexpected end of file";
      isError = Standard_True;
      break;
    default: ;
    }
    if (isError) break;
  }
  return isError;
}

//=======================================================================
//function : startElement
//purpose  : virtual hook on 'StartElement' event for descendant classes
//=======================================================================

Standard_Boolean LDOMParser::startElement ()
{
  return Standard_False;
}

//=======================================================================
//function : endElement
//purpose  : virtual hook on 'EndElement' event for descendant classes
//=======================================================================

Standard_Boolean LDOMParser::endElement ()
{
  return Standard_False;
}

//=======================================================================
//function : getCurrentElement
//purpose  : 
//=======================================================================

LDOM_Element LDOMParser::getCurrentElement () const
{
  return LDOM_Element (myReader -> GetElement(), myDocument);
}

//=======================================================================
//function : getDocument
//purpose  : 
//=======================================================================

LDOM_Document LDOMParser::getDocument ()
{
  return myDocument -> Self();
}

