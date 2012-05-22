// Created on: 2007-05-29
// Created by: Vlad Romashko
// Copyright (c) 2007-2012 OPEN CASCADE SAS
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


#include <TDataStd_BooleanList.ixx>
#include <TDataStd_ListIteratorOfListOfByte.hxx>

//=======================================================================
//function : GetID
//purpose  : 
//=======================================================================
const Standard_GUID& TDataStd_BooleanList::GetID() 
{ 
  static Standard_GUID TDataStd_BooleanListID ("23A9D60E-A033-44d8-96EE-015587A41BBC");
  return TDataStd_BooleanListID; 
}

//=======================================================================
//function : TDataStd_BooleanList
//purpose  : Empty Constructor
//=======================================================================
TDataStd_BooleanList::TDataStd_BooleanList() 
{

}

//=======================================================================
//function : Set
//purpose  : 
//=======================================================================
Handle(TDataStd_BooleanList) TDataStd_BooleanList::Set(const TDF_Label& label) 
{
  Handle(TDataStd_BooleanList) A;
  if (!label.FindAttribute (TDataStd_BooleanList::GetID(), A)) 
  {
    A = new TDataStd_BooleanList;
    label.AddAttribute(A);
  }
  return A;
}

//=======================================================================
//function : IsEmpty
//purpose  : 
//=======================================================================
Standard_Boolean TDataStd_BooleanList::IsEmpty() const
{
  return myList.IsEmpty();
}

//=======================================================================
//function : Extent
//purpose  : 
//=======================================================================
Standard_Integer TDataStd_BooleanList::Extent() const
{
  return myList.Extent();
}

//=======================================================================
//function : Prepend
//purpose  : 
//=======================================================================
void TDataStd_BooleanList::Prepend(const Standard_Boolean value)
{
  Backup();
  myList.Prepend( value ? 1 : 0 );
}

//=======================================================================
//function : Append
//purpose  : 
//=======================================================================
void TDataStd_BooleanList::Append(const Standard_Boolean value)
{
  Backup();
  myList.Append( value ? 1 : 0 );
}

//=======================================================================
//function : Clear
//purpose  : 
//=======================================================================
void TDataStd_BooleanList::Clear()
{
  Backup();
  myList.Clear();
}

//=======================================================================
//function : First
//purpose  : 
//=======================================================================
Standard_Boolean TDataStd_BooleanList::First() const
{
  return myList.First() == 1;
}

//=======================================================================
//function : Last
//purpose  : 
//=======================================================================
Standard_Boolean TDataStd_BooleanList::Last() const
{
  return myList.Last() == 1;
}

//=======================================================================
//function : List
//purpose  : 
//=======================================================================
const TDataStd_ListOfByte& TDataStd_BooleanList::List() const
{
  return myList;
}

//=======================================================================
//function : ID
//purpose  : 
//=======================================================================
const Standard_GUID& TDataStd_BooleanList::ID () const 
{ 
  return GetID(); 
}

//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================
Handle(TDF_Attribute) TDataStd_BooleanList::NewEmpty () const
{  
  return new TDataStd_BooleanList(); 
}

//=======================================================================
//function : Restore
//purpose  : 
//=======================================================================
void TDataStd_BooleanList::Restore(const Handle(TDF_Attribute)& With) 
{
  myList.Clear();
  Handle(TDataStd_BooleanList) aList = Handle(TDataStd_BooleanList)::DownCast(With);
  TDataStd_ListIteratorOfListOfByte itr(aList->List());
  for (; itr.More(); itr.Next())
  {
    myList.Append(itr.Value());
  }
}

//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================
void TDataStd_BooleanList::Paste (const Handle(TDF_Attribute)& Into,
				  const Handle(TDF_RelocationTable)& ) const
{
  Handle(TDataStd_BooleanList) aList = Handle(TDataStd_BooleanList)::DownCast(Into);
  aList->Clear();
  TDataStd_ListIteratorOfListOfByte itr(myList);
  for (; itr.More(); itr.Next())
  {
    aList->Append(itr.Value());
  }
}

//=======================================================================
//function : Dump
//purpose  : 
//=======================================================================
Standard_OStream& TDataStd_BooleanList::Dump (Standard_OStream& anOS) const
{  
  anOS << "BooleanList";
  return anOS;
}
