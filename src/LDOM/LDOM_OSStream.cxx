// Created on: 2001-10-01
// Created by: Julia DOROVSKIKH
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


#include <LDOM_OSStream.hxx>
#include <string.h>
#include <Standard_Integer.hxx>

// One element of sequence
class LDOM_StringElem
{
  char* buf;             // pointer on data string
  int len;               // quantity of really written data
  LDOM_StringElem* next; // pointer on the next element of a sequence

  LDOM_StringElem (int aLen)
  {
    buf = new char[aLen];
    len = 0;
    next = 0;
  }

  ~LDOM_StringElem ()
  {
    delete [] buf;
    if (next) delete next;
  }
friend class LDOM_SBuffer;
};

//=======================================================================
//function : LDOM_SBuffer()
//purpose  : 
//=======================================================================
LDOM_SBuffer::LDOM_SBuffer (const Standard_Integer theMaxBuf)
     : myMaxBuf (theMaxBuf), myLength(0)
{
  myFirstString = new LDOM_StringElem (theMaxBuf);
  myCurString = myFirstString;
}

//=======================================================================
//function : ~LDOM_SBuffer()
//purpose  : 
//=======================================================================
LDOM_SBuffer::~LDOM_SBuffer ()
{
  if (myFirstString) delete myFirstString;
}

//=======================================================================
//function : Clear()
//purpose  : 
//=======================================================================
void LDOM_SBuffer::Clear ()
{
  if (myFirstString->next) delete myFirstString->next;
  myFirstString->next = 0;
  myFirstString->len = 0;
  myLength = 0;
  myCurString = myFirstString;
}

//=======================================================================
//function : str()
//purpose  : 
//=======================================================================
Standard_CString LDOM_SBuffer::str () const
{
  char* aRetStr = new char [myLength + 1];

  LDOM_StringElem* aCurElem = myFirstString;
  int aCurLen = 0;
  while (aCurElem)
  {
    strncpy(aRetStr + aCurLen, aCurElem->buf, aCurElem->len);
    aCurLen += aCurElem->len;
    aCurElem = aCurElem->next;
  }
  *(aRetStr + myLength) = '\0';

  return aRetStr;
}

//=======================================================================
//function : overflow()
//purpose  : redefined virtual
//=======================================================================
int LDOM_SBuffer::overflow(signed char c)
{
  char cc = (char)c;
  return (int)xsputn(&cc,1);
}

//=======================================================================
//function : underflow
//purpose  : redefined virtual
//=======================================================================

int LDOM_SBuffer::underflow()
{
  return EOF;
}

//int LDOM_SBuffer::uflow()
//{ return EOF; }

//=======================================================================
//function : xsputn()
//purpose  : redefined virtual
//=======================================================================
std::streamsize LDOM_SBuffer::xsputn(const char* aStr, std::streamsize n)
{
  int aLen = (int)(n) + 1;
  int freeLen = myMaxBuf - myCurString->len - 1;
  if (freeLen >= n)
  {
    strncpy(myCurString->buf + myCurString->len, aStr, aLen);
  }
  else if (freeLen <= 0)
  {
    LDOM_StringElem* aNextElem = new LDOM_StringElem(Max(aLen, myMaxBuf));
    myCurString->next = aNextElem;
    myCurString = aNextElem;
    strncpy(myCurString->buf + myCurString->len, aStr, aLen);
  }
  else // 0 < freeLen < n
  {
    // copy string by parts
    strncpy(myCurString->buf + myCurString->len, aStr, freeLen);
    myCurString->len += freeLen;
    *(myCurString->buf + myCurString->len) = '\0';
    aLen -= freeLen;
    LDOM_StringElem* aNextElem = new LDOM_StringElem(Max(aLen, myMaxBuf));
    myCurString->next = aNextElem;
    myCurString = aNextElem;
    strncpy(myCurString->buf + myCurString->len, aStr + freeLen, aLen);
  }
  myCurString->len += aLen - 1;
  *(myCurString->buf + myCurString->len) = '\0';

  myLength += (int)n;
  return n;
}

//streamsize LDOM_SBuffer::xsgetn(char* s, streamsize n)
//{ return _IO_default_xsgetn(this, s, n); }

//=======================================================================
//function : LDOM_OSStream()
//purpose  : Constructor
//=======================================================================
LDOM_OSStream::LDOM_OSStream (const Standard_Integer theMaxBuf)
     : Standard_OStream (&myBuffer), myBuffer (theMaxBuf)
{
  init(&myBuffer);
}
