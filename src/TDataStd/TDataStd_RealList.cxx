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


#include <TDataStd_RealList.ixx>
#include <TColStd_ListIteratorOfListOfReal.hxx>

//=======================================================================
//function : GetID
//purpose  : 
//=======================================================================
const Standard_GUID& TDataStd_RealList::GetID() 
{ 
  static Standard_GUID TDataStd_RealListID ("349ACE18-7CD6-4525-9938-FBBF22AA54D3");
  return TDataStd_RealListID; 
}

//=======================================================================
//function : TDataStd_RealList
//purpose  : Empty Constructor
//=======================================================================
TDataStd_RealList::TDataStd_RealList() 
{

}

//=======================================================================
//function : Set
//purpose  : 
//=======================================================================
Handle(TDataStd_RealList) TDataStd_RealList::Set(const TDF_Label& label) 
{
  Handle(TDataStd_RealList) A;
  if (!label.FindAttribute (TDataStd_RealList::GetID(), A)) 
  {
    A = new TDataStd_RealList;
    label.AddAttribute(A);
  }
  return A;
}

//=======================================================================
//function : IsEmpty
//purpose  : 
//=======================================================================
Standard_Boolean TDataStd_RealList::IsEmpty() const
{
  return myList.IsEmpty();
}

//=======================================================================
//function : Extent
//purpose  : 
//=======================================================================
Standard_Integer TDataStd_RealList::Extent() const
{
  return myList.Extent();
}

//=======================================================================
//function : Prepend
//purpose  : 
//=======================================================================
void TDataStd_RealList::Prepend(const Standard_Real value)
{
  Backup();
  myList.Prepend(value);
}

//=======================================================================
//function : Append
//purpose  : 
//=======================================================================
void TDataStd_RealList::Append(const Standard_Real value)
{
  Backup();
  myList.Append(value);
}

//=======================================================================
//function : InsertBefore
//purpose  : 
//=======================================================================
Standard_Boolean TDataStd_RealList::InsertBefore(const Standard_Real value,
						 const Standard_Real before_value)
{
  TColStd_ListIteratorOfListOfReal itr(myList);
  for (; itr.More(); itr.Next())
  {
    if (itr.Value() == before_value)
    {
      Backup();
      myList.InsertBefore(value, itr);
      return Standard_True;
    }
  }
  return Standard_False;
}

//=======================================================================
//function : InsertAfter
//purpose  : 
//=======================================================================
Standard_Boolean TDataStd_RealList::InsertAfter(const Standard_Real value,
						const Standard_Real after_value)
{
  TColStd_ListIteratorOfListOfReal itr(myList);
  for (; itr.More(); itr.Next())
  {
    if (itr.Value() == after_value)
    {
      Backup();
      myList.InsertAfter(value, itr);
      return Standard_True;
    }
  }
  return Standard_False;
}

//=======================================================================
//function : Remove
//purpose  : 
//=======================================================================
Standard_Boolean TDataStd_RealList::Remove(const Standard_Real value)
{
  TColStd_ListIteratorOfListOfReal itr(myList);
  for (; itr.More(); itr.Next())
  {
    if (itr.Value() == value)
    {
      Backup();
      myList.Remove(itr);
      return Standard_True;
    }
  }
  return Standard_False;
}

//=======================================================================
//function : Clear
//purpose  : 
//=======================================================================
void TDataStd_RealList::Clear()
{
  Backup();
  myList.Clear();
}

//=======================================================================
//function : First
//purpose  : 
//=======================================================================
Standard_Real TDataStd_RealList::First() const
{
  return myList.First();
}

//=======================================================================
//function : Last
//purpose  : 
//=======================================================================
Standard_Real TDataStd_RealList::Last() const
{
  return myList.Last();
}

//=======================================================================
//function : List
//purpose  : 
//=======================================================================
const TColStd_ListOfReal& TDataStd_RealList::List() const
{
  return myList;
}

//=======================================================================
//function : ID
//purpose  : 
//=======================================================================
const Standard_GUID& TDataStd_RealList::ID () const 
{ 
  return GetID(); 
}

//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================
Handle(TDF_Attribute) TDataStd_RealList::NewEmpty () const
{  
  return new TDataStd_RealList(); 
}

//=======================================================================
//function : Restore
//purpose  : 
//=======================================================================
void TDataStd_RealList::Restore(const Handle(TDF_Attribute)& With) 
{
  myList.Clear();
  Handle(TDataStd_RealList) aList = Handle(TDataStd_RealList)::DownCast(With);
  TColStd_ListIteratorOfListOfReal itr(aList->List());
  for (; itr.More(); itr.Next())
  {
    myList.Append(itr.Value());
  }
}

//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================
void TDataStd_RealList::Paste (const Handle(TDF_Attribute)& Into,
				  const Handle(TDF_RelocationTable)& ) const
{
  Handle(TDataStd_RealList) aList = Handle(TDataStd_RealList)::DownCast(Into);
  aList->Clear();
  TColStd_ListIteratorOfListOfReal itr(myList);
  for (; itr.More(); itr.Next())
  {
    aList->Append(itr.Value());
  }
}

//=======================================================================
//function : Dump
//purpose  : 
//=======================================================================
Standard_OStream& TDataStd_RealList::Dump (Standard_OStream& anOS) const
{  
  anOS << "RealList";
  return anOS;
}
