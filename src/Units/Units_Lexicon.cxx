// Created on: 1992-06-24
// Created by: Gilles DEBARBOUILLE
// Copyright (c) 1992-1999 Matra Datavision
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



#include <Units_Lexicon.ixx>
#include <Units_Token.hxx>
#include <TCollection_HAsciiString.hxx>
#include <TCollection_AsciiString.hxx>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef WNT
# include <stdio.h>
#else
#include <Standard_Stream.hxx>
#endif  // WNT

//=======================================================================
//function : Units_Lexicon
//purpose  : 
//=======================================================================

Units_Lexicon::Units_Lexicon()
{
}


//=======================================================================
//function : Creates
//purpose  : 
//=======================================================================

void Units_Lexicon::Creates(const Standard_CString afilename)
{
  char chain[256],line[256];
  char oper[11],coeff[31];
#if 0
  char *Chain = chain ;
  char *Line = line ;
  char *Oper = oper ;
  char *Coeff = coeff ;
#endif
  Standard_Integer fr;
  int i;  // Warning : don't use unsigned type here (or Standard_Size or size_t), else the while's below will cause an unsigned 0-wrap!
  Standard_Real value;
  Handle(Units_Token) token;
  struct stat buf;

#if 0
  chain[255] = '\0' ;
  oper[10] = '\0' ;
  coeff[30] = '\0' ;
#endif

  //for(i=0; i<=255; i++)chain[i]=0;
  ifstream file(afilename, ios::in);
  if(!file) {
    cout<<"unable to open "<<afilename<<" for input"<<endl;
    return;
  }

  thefilename = new TCollection_HAsciiString(afilename);
  thesequenceoftokens = new Units_TokensSequence();

  if(!stat(afilename,&buf)) thetime = buf.st_ctime;

  //for(i=0; i<=255; i++)line[i]=0;

  while(file.getline(line,255)) {
    int len = (int) strlen( line ) ;
    if(len == 1) continue; //skl - ???
    for ( i = 0 ; i < 30 ; i++ ) {
      if ( i < len )
        sscanf(&line[i],"%c",&chain[i]);
      else
        chain[i] = 0 ;
    }
    for ( i = 0 ; i < 10 ; i++ ) {
      if ( 30+i < len )
        sscanf(&line[30+i],"%c",&oper[i]);
      else
        oper[i] = 0 ;
    }
    for ( i = 0 ; i < 30 ; i++ ) {
      if ( 40+i < len )
        sscanf(&line[40+i],"%c",&coeff[i]);
      else
        coeff[i] = 0 ;
    }
#if 0
    cout << "Lexiconsscanf(%c          )" << endl << "Chain" << Chain << endl
         << "Oper" << Oper << endl
         << "Coeff" << Coeff << endl ;
#endif
    i=29;
    while( i>=0 && ( chain[i] == ' ' || !chain[i] ))
      chain[i--]=0;
    if(i<0) continue;
    i=9;
    while( i>=0 && ( oper [i] == ' ' || !oper [i] ))
      oper[i--]=0;
    i=29;
    while( i>=0 && ( coeff[i] == ' ' || !coeff[i] ))
      coeff[i--]=0;

    if(coeff[0])
      value = atof(coeff);
    else
      value = 0.;

    if(thesequenceoftokens->IsEmpty()) {
      token = new Units_Token(chain,oper,value);
      thesequenceoftokens->Prepend(token);
    }
    else {
      AddToken(chain,oper,value);
    }

    for(i=0; i<255; i++)
      line[i]=0;
  }
  file.close();
}


//=======================================================================
//function : UpToDate
//purpose  : 
//=======================================================================

Standard_Boolean Units_Lexicon::UpToDate() const
{
  struct stat buf;
  TCollection_AsciiString string = FileName();

  if(!stat(string.ToCString(),&buf)) {
    if(thetime >= buf.st_ctime)
      return Standard_True;
  }

  return Standard_False;
}


//=======================================================================
//function : FileName
//purpose  : 
//=======================================================================

TCollection_AsciiString Units_Lexicon::FileName() const
{
  return thefilename->String();
}


//=======================================================================
//function : AddToken
//purpose  : 
//=======================================================================

void Units_Lexicon::AddToken(const Standard_CString aword,
			     const Standard_CString amean,
			     const Standard_Real avalue)
{
  Handle(Units_Token) token;
  Handle(Units_Token) referencetoken;
  Standard_Boolean found = Standard_False;
  Standard_Integer index;

  for(index=1;index<=thesequenceoftokens->Length();index++) {
    referencetoken = thesequenceoftokens->Value(index);
    if( referencetoken->Word() == aword ) {
      referencetoken->Update(amean);
      found = Standard_True;
      break;
    }
    else if( !( referencetoken->Word()>aword ) ) {
      token = new Units_Token(aword,amean,avalue);
      thesequenceoftokens->InsertBefore(index,token);
      found = Standard_True;
      break;
    }
  }
  if(!found) {
    token = new Units_Token(aword,amean,avalue);
    thesequenceoftokens->Append(token);
  }
}
