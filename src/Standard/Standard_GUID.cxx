// Copyright (c) 1998-1999 Matra Datavision
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

#include <Standard_GUID.ixx>
#include <Standard_RangeError.hxx>
#include <Standard_IStream.hxx>
#include <stdio.h>

#define Standard_GUID_SIZE 36
#define Standard_GUID_SIZE_ALLOC Standard_GUID_SIZE+1

//Fixes incorrect treatment of GUID given as a string with invalid format
#define OCC669 

//=======================================================================
//function : Standard_GUID_MatchChar
//purpose  : 
//=======================================================================
Standard_Integer Standard_GUID_MatchChar(const Standard_CString buffer, 
					 const Standard_Character aChar)
{
  Standard_CString tmpbuffer = buffer;
  Standard_Integer result    = -1;

  while(*tmpbuffer != '\0' && *tmpbuffer != aChar) {tmpbuffer++; result++;}

#ifdef OCC669
  if(*tmpbuffer == '\0') return -1; //The searched symbol wasn't found
#endif 

  if (result >= 0) result++;

  return result;
}
//=======================================================================
//function : Standard_GUID_GetValue32
//purpose  : 
//=======================================================================
Standard_PCharacter Standard_GUID_GetValue32(Standard_PCharacter tmpBuffer, 
					     Standard_Integer& my32b) 
{
  Standard_Character strtmp[Standard_GUID_SIZE_ALLOC];
  Standard_Integer   pos = 0;

  pos = Standard_GUID_MatchChar(tmpBuffer,'-');
  if (pos >= 0) {
    strncpy(strtmp,tmpBuffer,pos);
    strtmp[pos] = '\0';
    my32b = (Standard_Integer) strtoul(strtmp, (char **)NULL, 16);
  }
#ifdef OCC669
  else return NULL;
#endif 
  return &tmpBuffer[pos+1];
}
//=======================================================================
//function : Standard_GUID_GetValue16
//purpose  : 
//=======================================================================
Standard_PCharacter Standard_GUID_GetValue16(Standard_PCharacter tmpBuffer, 
					     Standard_ExtCharacter& my32b) 
{
  Standard_Character strtmp[Standard_GUID_SIZE_ALLOC];
  Standard_Integer   pos = 0;

  pos = Standard_GUID_MatchChar(tmpBuffer,'-');
  if (pos >= 0) {
    strncpy(strtmp,tmpBuffer,pos);
    strtmp[pos] = '\0';
    my32b = (Standard_ExtCharacter) strtoul(strtmp, (char **)NULL, 16);
  }
#ifdef OCC669
  else return NULL;
#endif 
//  cout << "V16 :" << hex(my32b) << endl;
  return &tmpBuffer[pos+1];
}
//=======================================================================
//function : Standard_GUID_GetValue8
//purpose  : 
//=======================================================================
Standard_PCharacter Standard_GUID_GetValue8(Standard_PCharacter tmpBuffer, 
					    Standard_Byte& my32b) 
{
  Standard_Character strtmp[Standard_GUID_SIZE_ALLOC];

  strncpy(strtmp,tmpBuffer,2);
  strtmp[2] = '\0';
  my32b = (Standard_Byte) strtoul(strtmp, (char **)NULL, 16);
//  cout << "V8 :" << hex(my32b) << endl;
  return &tmpBuffer[2];
}
//=======================================================================
//function : CheckGUIDFormat
//purpose  : 
//=======================================================================
Standard_Boolean Standard_GUID::CheckGUIDFormat(const Standard_CString aGuid)
{
  Standard_Boolean result = Standard_True;

  if (aGuid == NULL) return Standard_False;

  if (strlen(aGuid) == Standard_GUID_SIZE) {
    Standard_Integer i;

    for (i = 0; i < 8 && result; i++) {
      if (!IsXDigit(aGuid[i])) {
	return Standard_False;
      }
    }

    if (aGuid[8] != '-') return Standard_False;

    for (i = 9; i < 13 && result; i++) {
      if (!IsXDigit(aGuid[i])) {
	return Standard_False;
      }
    }

    if (aGuid[13] != '-') return Standard_False;
    
    for (i = 14; i < 18 && result; i++) {
      if (!IsXDigit(aGuid[i])) {
	return Standard_False;
      }
    }

    if (aGuid[18] != '-') return Standard_False;

    for (i = 19; i < 23; i++) {
      if (!IsXDigit(aGuid[i])) {
	return Standard_False;
      }
    }

    if (aGuid[23] != '-') return Standard_False;

    for (i = 24; i < 36; i++) {
      if (!IsXDigit(aGuid[i])) {
	return Standard_False;
      }
    }
  }
  else result = Standard_False;

  return result;
}

Standard_GUID::Standard_GUID() 
: my32b ( 0),
  my16b1 ( 0),
  my16b2 ( 0),
  my16b3 ( 0),
  my8b1 ( 0),
  my8b2 ( 0),
  my8b3 ( 0),
  my8b4 ( 0),
  my8b5 ( 0),
  my8b6 ( 0)
{
}

Standard_GUID::Standard_GUID(const Standard_CString aGuid) 
: my32b ( 0),
  my16b1 ( 0),
  my16b2 ( 0),
  my16b3 ( 0),
  my8b1 ( 0),
  my8b2 ( 0),
  my8b3 ( 0),
  my8b4 ( 0),
  my8b5 ( 0),
  my8b6 ( 0)
{
  char* tmpBuffer =(char*) aGuid;

#ifdef OCC669 
  if(!CheckGUIDFormat(tmpBuffer)) Standard_RangeError::Raise("Invalid format of GUID");
#endif 

#ifdef  OCC669
  if((tmpBuffer = Standard_GUID_GetValue32(tmpBuffer,my32b)) == NULL) 
    Standard_RangeError::Raise("Invalid format of GUID");
  if((tmpBuffer = Standard_GUID_GetValue16(tmpBuffer,my16b1)) == NULL) 
    Standard_RangeError::Raise("Invalid format of GUID");
  if((tmpBuffer = Standard_GUID_GetValue16(tmpBuffer,my16b2)) == NULL) 
    Standard_RangeError::Raise("Invalid format of GUID");
  if((tmpBuffer = Standard_GUID_GetValue16(tmpBuffer,my16b3)) == NULL) 
    Standard_RangeError::Raise("Invalid format of GUID");
#else
  tmpBuffer = Standard_GUID_GetValue32(tmpBuffer,my32b);
  tmpBuffer = Standard_GUID_GetValue16(tmpBuffer,my16b1);
  tmpBuffer = Standard_GUID_GetValue16(tmpBuffer,my16b2);
  tmpBuffer = Standard_GUID_GetValue16(tmpBuffer,my16b3);
#endif 
  tmpBuffer = Standard_GUID_GetValue8(tmpBuffer,my8b1);
  tmpBuffer = Standard_GUID_GetValue8(tmpBuffer,my8b2);
  tmpBuffer = Standard_GUID_GetValue8(tmpBuffer,my8b3);
  tmpBuffer = Standard_GUID_GetValue8(tmpBuffer,my8b4);
  tmpBuffer = Standard_GUID_GetValue8(tmpBuffer,my8b5);
  tmpBuffer = Standard_GUID_GetValue8(tmpBuffer,my8b6);
}

Standard_GUID::Standard_GUID(const Standard_ExtString aGuid) 
: my32b ( 0),
  my16b1 ( 0),
  my16b2 ( 0),
  my16b3 ( 0),
  my8b1 ( 0),
  my8b2 ( 0),
  my8b3 ( 0),
  my8b4 ( 0),
  my8b5 ( 0),
  my8b6 ( 0)
{ 
  char tpb[Standard_GUID_SIZE_ALLOC];
  char *tmpBuffer = tpb;
  Standard_Integer   i = 0;
  while(i < Standard_GUID_SIZE) {
    tmpBuffer[i] = (char ) aGuid[i];
    i++;
  }

  tmpBuffer[i] = '\0';

#ifdef OCC669
  if(!CheckGUIDFormat(tmpBuffer)) Standard_RangeError::Raise("Invalid format of GUID");
#endif 

#ifdef  OCC669
  if((tmpBuffer = Standard_GUID_GetValue32(tmpBuffer,my32b)) == NULL) 
    Standard_RangeError::Raise("Invalid format of GUID");
  if((tmpBuffer = Standard_GUID_GetValue16(tmpBuffer,my16b1)) == NULL) 
    Standard_RangeError::Raise("Invalid format of GUID");
  if((tmpBuffer = Standard_GUID_GetValue16(tmpBuffer,my16b2)) == NULL) 
    Standard_RangeError::Raise("Invalid format of GUID");
  if((tmpBuffer = Standard_GUID_GetValue16(tmpBuffer,my16b3)) == NULL) 
    Standard_RangeError::Raise("Invalid format of GUID");
#else
  tmpBuffer = Standard_GUID_GetValue32(tmpBuffer,my32b);
  tmpBuffer = Standard_GUID_GetValue16(tmpBuffer,my16b1);
  tmpBuffer = Standard_GUID_GetValue16(tmpBuffer,my16b2);
  tmpBuffer = Standard_GUID_GetValue16(tmpBuffer,my16b3);
#endif 
  tmpBuffer = Standard_GUID_GetValue8(tmpBuffer,my8b1);
  tmpBuffer = Standard_GUID_GetValue8(tmpBuffer,my8b2);
  tmpBuffer = Standard_GUID_GetValue8(tmpBuffer,my8b3);
  tmpBuffer = Standard_GUID_GetValue8(tmpBuffer,my8b4);
  tmpBuffer = Standard_GUID_GetValue8(tmpBuffer,my8b5);
  tmpBuffer = Standard_GUID_GetValue8(tmpBuffer,my8b6);
}

Standard_GUID::Standard_GUID(const Standard_Integer a32b,
	const Standard_ExtCharacter a16b1,
	const Standard_ExtCharacter a16b2,
	const Standard_ExtCharacter a16b3,
	const Standard_Byte a8b1,
	const Standard_Byte a8b2,
	const Standard_Byte a8b3,
	const Standard_Byte a8b4,
	const Standard_Byte a8b5,
	const Standard_Byte a8b6)
{
	my32b = a32b;
	my16b1 = a16b1;
	 my16b2 = a16b2;
	 my16b3 = a16b3;
	 my8b1 = a8b1;
	 my8b2 = a8b2;
	 my8b3 = a8b3;
	 my8b4 = a8b4;
	 my8b5 = a8b5;
	 my8b6 = a8b6;
}

Standard_GUID::Standard_GUID(const Standard_GUID& aGuid)
{
	 my32b  = aGuid.my32b;
	 my16b1 = aGuid.my16b1;
	 my16b2 = aGuid.my16b2;
	 my16b3 = aGuid.my16b3;
	 my8b1  = aGuid.my8b1;
	 my8b2  = aGuid.my8b2;
	 my8b3  = aGuid.my8b3;
	 my8b4  = aGuid.my8b4;
	 my8b5  = aGuid.my8b5;
	 my8b6  = aGuid.my8b6;
}
Standard_GUID::Standard_GUID(const Standard_UUID& aWntGuid)
{
	 my32b  = aWntGuid.Data1;
	 my16b1 = aWntGuid.Data2;
	 my16b2 = aWntGuid.Data3;
	 my16b3 = (aWntGuid.Data4[0] << 8) | (aWntGuid.Data4[1]) ;
	 my8b1  = aWntGuid.Data4[2] ;
	 my8b2  = aWntGuid.Data4[3] ;
	 my8b3  = aWntGuid.Data4[4] ;
	 my8b4  = aWntGuid.Data4[5] ;
	 my8b5  = aWntGuid.Data4[6] ;
	 my8b6  = aWntGuid.Data4[7] ;
}

//=======================================================================
//function : ToCString
//purpose  : 
//=======================================================================
void Standard_GUID::ToCString(const Standard_PCharacter aStrGuid) const
{
  sprintf(aStrGuid,"%.8x-%.4x-%.4x-%.4x-%.2x%.2x%.2x%.2x%.2x%.2x",
	  my32b,
	  (unsigned short) my16b1,
	  (unsigned short) my16b2,
	  (unsigned short) my16b3,
	  (unsigned char)my8b1,
	  (unsigned char)my8b2,
	  (unsigned char)my8b3,
	  (unsigned char)my8b4,
	  (unsigned char)my8b5,
	  (unsigned char)my8b6);
}

//=======================================================================
//function : ToExtString
//purpose  : 
//=======================================================================
void Standard_GUID::ToExtString(const Standard_PExtCharacter aStrGuid) const
{
  Standard_Character sguid[Standard_GUID_SIZE_ALLOC];
  ToCString(sguid);

  for(Standard_Integer i = 0; i < Standard_GUID_SIZE; i++) {
    aStrGuid[i] = (Standard_ExtCharacter)sguid[i];
  }

  aStrGuid[Standard_GUID_SIZE] = (Standard_ExtCharacter)0;
}

Standard_UUID Standard_GUID::ToUUID() const
{
  Standard_UUID result ;

  result.Data1 = my32b ;
  result.Data2 = my16b1 ;
  result.Data3 = my16b2 ;
  result.Data4[0] = my16b3 >> 8 ;
  result.Data4[1] = (char ) my16b3 ;
  result.Data4[2] = my8b1 ;
  result.Data4[3] = my8b2 ;
  result.Data4[4] = my8b3 ;
  result.Data4[5] = my8b4 ;
  result.Data4[6] = my8b5 ;
  result.Data4[7] = my8b6 ;
  return result ;
}       

Standard_Boolean Standard_GUID::IsSame(const Standard_GUID& uid) const
{
  Standard_Boolean result = Standard_True;

  if (my32b  != uid.my32b) result = Standard_False;
  else if (my16b1 != uid.my16b1) result = Standard_False;
  else if (my16b2 != uid.my16b2) result = Standard_False;
  else if (my16b3 != uid.my16b3) result = Standard_False;
  else if (my8b1  != uid.my8b1) result = Standard_False;
  else if (my8b2  != uid.my8b2) result = Standard_False;
  else if (my8b3  != uid.my8b3) result = Standard_False;
  else if (my8b4  != uid.my8b4) result = Standard_False;
  else if (my8b5  != uid.my8b5) result = Standard_False;
  else if (my8b6  != uid.my8b6) result = Standard_False;

  return result;
}

Standard_Boolean Standard_GUID::IsNotSame(const Standard_GUID& uid) const
{
  return !IsSame(uid);
}

void Standard_GUID::Assign(const Standard_GUID& uid) 
{
  my32b  = uid.my32b;
  my16b1 = uid.my16b1;
  my16b2 = uid.my16b2;
  my16b3 = uid.my16b3;
  my8b1  = uid.my8b1;
  my8b2  = uid.my8b2;
  my8b3  = uid.my8b3;
  my8b4  = uid.my8b4;
  my8b5  = uid.my8b5;
  my8b6  = uid.my8b6;
}

void Standard_GUID::ShallowDump(Standard_OStream& aStream) const
{
  Standard_Character sguid[Standard_GUID_SIZE_ALLOC];
  ToCString(sguid);
  aStream << sguid;
}

Standard_Integer Standard_GUID::HashCode(const Standard_GUID& aGuid,const Standard_Integer Upper)
{
  return aGuid.Hash(Upper);
}

Standard_Integer Standard_GUID::Hash(const Standard_Integer Upper) const
{
  if (Upper < 1){
    Standard_RangeError::
      Raise("Standard_GUID::Hash: Try to apply HashCode method with negative or null argument.");
  }

  char sguid[Standard_GUID_SIZE_ALLOC];
  ToCString(sguid);

  return ::HashCode(sguid,Upper);
}

Standard_Boolean Standard_GUID::IsEqual(const Standard_GUID& aGuid1,const Standard_GUID& aGuid2)
{
  return (aGuid1 == aGuid2);
}

