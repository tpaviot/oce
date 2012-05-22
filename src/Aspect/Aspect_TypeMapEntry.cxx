// Created on: 1993-09-14
// Created by: GG
// Copyright (c) 1993-1999 Matra Datavision
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



//-Version

//-Design       Declaration des variables specifiques aux Entries de 
//		Types de trait

//-Warning      Une entry est definie par un index associee a un Line style

//-References

//-Language     C++ 2.0

//-Declarations

// for the class
#include <Aspect_TypeMapEntry.ixx>
#include <TColQuantity_Array1OfLength.hxx>
//-Aliases

//-Global data definitions

//      MyType      		: LineStyle from Aspect
//      MyIndex   		: Integer from Standard
//      MyTypeIsDef		: Boolean from Standard
//      MyIndexIsDef		: Boolean from Standard

//-Constructors

//-Destructors

//-Methods, in order

Aspect_TypeMapEntry::Aspect_TypeMapEntry() {

	MyTypeIsDef	= Standard_True;
	MyIndexIsDef	= Standard_True;
	MyIndex		= 0;
	MyType.SetValues (Aspect_TOL_SOLID);

}

Aspect_TypeMapEntry::Aspect_TypeMapEntry (const Standard_Integer index, const Aspect_LineStyle &style) {

	MyTypeIsDef	= Standard_True;
	MyIndexIsDef	= Standard_True;
	MyIndex		= index;
	MyType		= style;

}

Aspect_TypeMapEntry::Aspect_TypeMapEntry (const Aspect_TypeMapEntry& entry) {

	if ( !entry.MyTypeIsDef || !entry.MyIndexIsDef ) {
		Aspect_BadAccess::Raise("Unallocated TypeMapEntry") ;
	}
	else {
		MyTypeIsDef	= Standard_True;
		MyIndexIsDef	= Standard_True;
		MyIndex		= entry.MyIndex;
		MyType		= entry.MyType;
	}
}

void Aspect_TypeMapEntry::SetValue (const Standard_Integer index, const Aspect_LineStyle &style) {

	MyTypeIsDef	= Standard_True;
	MyIndexIsDef	= Standard_True;
	MyIndex		= index;
	MyType		= style;

}

void Aspect_TypeMapEntry::SetValue (const Aspect_TypeMapEntry& entry) {

	if ( !entry.MyTypeIsDef || !entry.MyIndexIsDef ) {
		Aspect_BadAccess::Raise("Unallocated TypeMapEntry") ;
	}
	else {
		MyTypeIsDef	= Standard_True;
		MyIndexIsDef	= Standard_True;
		MyIndex		= entry.MyIndex;
		MyType		= entry.MyType;
	}

}

void Aspect_TypeMapEntry::SetType (const Aspect_LineStyle &style) {

	MyTypeIsDef	= Standard_True;
	MyType		= style;

}

const Aspect_LineStyle& Aspect_TypeMapEntry::Type () const {

	if ( !MyTypeIsDef || !MyIndexIsDef ) 
		Aspect_BadAccess::Raise("Unallocated TypeMapEntry") ;

	return MyType;

}

void Aspect_TypeMapEntry::SetIndex (const Standard_Integer index) {

	MyTypeIsDef	= Standard_True;
	MyIndex		= index;

}

Standard_Integer Aspect_TypeMapEntry::Index () const {

	if ( !MyTypeIsDef || !MyIndexIsDef ) 
		Aspect_BadAccess::Raise("Unallocated TypeMapEntry");

	return MyIndex;

}

Standard_Boolean Aspect_TypeMapEntry::IsAllocated () const {

	return ( MyTypeIsDef && MyIndexIsDef ) ; 

}

void Aspect_TypeMapEntry::Free () {

	MyTypeIsDef	= Standard_False;
	MyIndexIsDef	= Standard_False;

}

void Aspect_TypeMapEntry::Dump () const {

  Aspect_TypeOfLine style = MyType.Style() ;
  Standard_Integer i,length = MyType.Length() ;

  cout << " Aspect_TypeMapEntry::Dump ()\n";
  cout << "      MyTypeIsDef : " << (MyTypeIsDef ? "True\n" : "False\n");
  cout << "      MyIndexIsDef : " << (MyIndexIsDef ? "True\n" : "False\n");
  cout << "      LineStyle : " << (Standard_Integer) style << " Length : " << length << "\n";//WNT
  if( length ) {
    for( i=(MyType.Values()).Lower() ; i<=(MyType.Values()).Upper() ; i++ ) 
	cout << "\t\tvalue(" << i << ") : " << MyType.Values().Value(i) << "\n";
  }
  cout << flush;
}
