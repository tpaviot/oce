// Created on: 1999-06-16
// Created by: Sergey RUIN
// Copyright (c) 1999-1999 Matra Datavision
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



#include <TDataStd_IntegerArray.ixx>
#include <TDataStd_DeltaOnModificationOfIntArray.hxx>
#include <TDF_DefaultDeltaOnModification.hxx>
#define OCC925
#define OCC2932

//=======================================================================
//function : GetID
//purpose  : 
//=======================================================================

const Standard_GUID& TDataStd_IntegerArray::GetID() 
{ 
  static Standard_GUID TDataStd_IntegerArrayID ("2a96b61d-ec8b-11d0-bee7-080009dc3333");
  return TDataStd_IntegerArrayID; 
}


//=======================================================================
//function : TDataStd_IntegerArray
//purpose  : Empty Constructor
//=======================================================================

TDataStd_IntegerArray::TDataStd_IntegerArray()
     :myIsDelta(Standard_False) {}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void TDataStd_IntegerArray::Init(const Standard_Integer lower,
                                 const Standard_Integer upper)
{
#ifdef OCC925
  Backup();
#endif
  myValue = new TColStd_HArray1OfInteger(lower, upper, 0);
}

//=======================================================================
//function : Set
//purpose  : isDelta applicable only for new attributes
//=======================================================================

Handle(TDataStd_IntegerArray) TDataStd_IntegerArray::Set
                                                (const TDF_Label&       label,
                                                 const Standard_Integer lower,
                                                 const Standard_Integer upper,
						 const Standard_Boolean isDelta) 

{
  Handle(TDataStd_IntegerArray) A;
  if (!label.FindAttribute (TDataStd_IntegerArray::GetID(), A)) {
    A = new TDataStd_IntegerArray;
    A->Init (lower, upper);
    A->SetDelta(isDelta);
    label.AddAttribute(A);
  }
  else if (lower != A->Lower() || upper != A->Upper())
  {
    A->Init (lower, upper); 
  }
  return A;
}

//=======================================================================
//function : SetValue
//purpose  : 
//=======================================================================

void TDataStd_IntegerArray::SetValue(const Standard_Integer index, const Standard_Integer value) 
{
  if(myValue.IsNull()) return;
  if( myValue->Value(index) == value)
    return; 
  Backup();
  myValue->SetValue(index, value);
}


//=======================================================================
//function : GetValue
//purpose  : 
//=======================================================================

Standard_Integer TDataStd_IntegerArray::Value (const Standard_Integer index) const 
{
  if(myValue.IsNull()) return 0;
  return myValue->Value(index); 
}



//=======================================================================
//function : Lower
//purpose  : 
//=======================================================================
Standard_Integer TDataStd_IntegerArray::Lower (void) const 
{ 
  if(myValue.IsNull()) return 0;
  return myValue->Lower(); 
}


//=======================================================================
//function : Upper
//purpose  : 
//=======================================================================
Standard_Integer TDataStd_IntegerArray::Upper (void) const 
{ 
  if(myValue.IsNull()) return 0; 
  return myValue->Upper(); 
}


//=======================================================================
//function : Length
//purpose  : 
//=======================================================================
Standard_Integer TDataStd_IntegerArray::Length (void) const 
{
  if(myValue.IsNull()) return 0;
  return myValue->Length(); 
}


//=======================================================================
//function : ChangeArray
//purpose  : If value of <newArray> differs from <myValue>, Backup 
//         : performed and myValue refers to new instance of HArray1OfInteger 
//         : that holds <newArray>
//=======================================================================

void TDataStd_IntegerArray::ChangeArray(const Handle(TColStd_HArray1OfInteger)& newArray,
					const Standard_Boolean isCheckItems) 
{
  Standard_Integer aLower    = newArray->Lower();
  Standard_Integer anUpper   = newArray->Upper();
  Standard_Boolean aDimEqual = Standard_False;
  Standard_Integer i;
#ifdef OCC2932

  if(Lower() == aLower && Upper() == anUpper ) {
    aDimEqual = Standard_True;
    if(isCheckItems) {
      Standard_Boolean isEqual = Standard_True;
      for(i = aLower; i <= anUpper; i++) {
	if(myValue->Value(i) != newArray->Value(i)) {
	  isEqual = Standard_False;
	  break;
	}
      }
      if(isEqual)
	return;
    }
  }
#endif
  
  Backup();
// Handles of myValue of current and backuped attributes will be different!
  if(myValue.IsNull() || !aDimEqual) 
    myValue = new TColStd_HArray1OfInteger(aLower, anUpper);  

  for(i = aLower; i <= anUpper; i++) 
    myValue->SetValue(i, newArray->Value(i));
}


//=======================================================================
//function : ID
//purpose  : 
//=======================================================================

const Standard_GUID& TDataStd_IntegerArray::ID () const { return GetID(); }


//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================

Handle(TDF_Attribute) TDataStd_IntegerArray::NewEmpty () const
{  
  return new TDataStd_IntegerArray(); 
}

//=======================================================================
//function : Restore
//purpose  : 
//=======================================================================

void TDataStd_IntegerArray::Restore(const Handle(TDF_Attribute)& With) 
{
  Standard_Integer i, lower, upper;
  Handle(TDataStd_IntegerArray) anArray = Handle(TDataStd_IntegerArray)::DownCast(With);
  if(!anArray->myValue.IsNull()) {
    lower = anArray->Lower();
    upper = anArray->Upper(); 
    myValue = new TColStd_HArray1OfInteger(lower, upper); 
    for(i = lower; i<=upper; i++)
      myValue->SetValue(i, anArray->Value(i));
    myIsDelta = anArray->myIsDelta;
  }
  else
    myValue.Nullify();
}

//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================

void TDataStd_IntegerArray::Paste (const Handle(TDF_Attribute)& Into,
                                   const Handle(TDF_RelocationTable)& ) const
{

  if(!myValue.IsNull()) {
    Handle(TDataStd_IntegerArray) anAtt = Handle(TDataStd_IntegerArray)::DownCast(Into);
    if(!anAtt.IsNull()) {
      anAtt->ChangeArray( myValue, Standard_False );
      anAtt->SetDelta(myIsDelta);
    }
  }
}

//=======================================================================
//function : Dump
//purpose  : 
//=======================================================================

Standard_OStream& TDataStd_IntegerArray::Dump (Standard_OStream& anOS) const
{  
  anOS << "\nIntegerArray:: " << this <<" :";
  if(!myValue.IsNull()) {
    Standard_Integer i, lower, upper;
    lower = myValue->Lower();
    upper = myValue->Upper();
    for(i = lower; i<=upper; i++)
      anOS << " " <<myValue->Value(i);
  }
  anOS << " Delta is " << (myIsDelta ? "ON":"OFF");
  anOS << endl;

  // anOS <<"\nAttribute fields: ";
  //  anOS << TDF_Attribute::Dump(anOS);

  return anOS;
}

//=======================================================================
//function : DeltaOnModification
//purpose  : 
//=======================================================================

Handle(TDF_DeltaOnModification) TDataStd_IntegerArray::DeltaOnModification
(const Handle(TDF_Attribute)& OldAttribute) const
{
  if(myIsDelta)
    return new TDataStd_DeltaOnModificationOfIntArray(*((Handle(TDataStd_IntegerArray)*)&OldAttribute));
  else return new TDF_DefaultDeltaOnModification(OldAttribute);
}


