// Created on: 1997-12-10
// Created by: Denis PASCAL
// Copyright (c) 1997-1999 Matra Datavision
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



#include <TDataStd_Relation.ixx>
#include <TCollection_AsciiString.hxx>
#include <TDataStd_Variable.hxx>
#include <TDF_ListIteratorOfAttributeList.hxx>

#define OCC387

//=======================================================================
//function : GetID
//purpose  : 
//=======================================================================

const Standard_GUID& TDataStd_Relation::GetID() 
{  
  static Standard_GUID TDataStd_RelationID("ce24146b-8e57-11d1-8953-080009dc4425");
  return TDataStd_RelationID;
}

//=======================================================================
//function : Set
//purpose  : 
//=======================================================================

Handle(TDataStd_Relation) TDataStd_Relation::Set(const TDF_Label& L) 
{  
  Handle(TDataStd_Relation) A;
  if (!L.FindAttribute (TDataStd_Relation::GetID(), A)) {
    A = new TDataStd_Relation ();
    L.AddAttribute(A);
  }
  return A;
}

//=======================================================================
//function : TDataStd_Relation
//purpose  : 
//=======================================================================

TDataStd_Relation::TDataStd_Relation()
{
}


//=======================================================================
//function : Name
//purpose  : 
//=======================================================================
TCollection_ExtendedString TDataStd_Relation::Name () const 
{  
  return myRelation;  // ->String();
}

//=======================================================================
//function : SetRelation
//purpose  : 
//=======================================================================

void TDataStd_Relation::SetRelation(const TCollection_ExtendedString& R)
{
  // OCC2932 correction
  if(myRelation == R) return;

#ifdef OCC387
  Backup();
#endif
  myRelation = R;
}

//=======================================================================
//function : GetRelation
//purpose  : 
//=======================================================================

const TCollection_ExtendedString& TDataStd_Relation::GetRelation() const
{
  return myRelation;
}

//=======================================================================
//function : GetVariables
//purpose  : 
//=======================================================================

TDF_AttributeList& TDataStd_Relation::GetVariables()
{
  return myVariables;
}

//=======================================================================
//function : ID
//purpose  : 
//=======================================================================

const Standard_GUID& TDataStd_Relation::ID() const
{
  return GetID();
}

//=======================================================================
//function : Restore
//purpose  : 
//=======================================================================

void TDataStd_Relation::Restore(const Handle(TDF_Attribute)& With) 
{  
  Handle(TDataStd_Relation) REL = Handle(TDataStd_Relation)::DownCast (With);
  myRelation = REL->GetRelation();
  Handle(TDataStd_Variable) V;
  myVariables.Clear();
  for (TDF_ListIteratorOfAttributeList it (REL->GetVariables()); it.More(); it.Next()) {
    V = Handle(TDataStd_Variable)::DownCast(it.Value());
    myVariables.Append(V);
  }
}

//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================

Handle(TDF_Attribute) TDataStd_Relation::NewEmpty() const
{
  return new TDataStd_Relation();
}

//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================

void TDataStd_Relation::Paste(const Handle(TDF_Attribute)& Into,
				     const Handle(TDF_RelocationTable)& RT) const
{  
  Handle(TDataStd_Relation) REL = Handle(TDataStd_Relation)::DownCast (Into); 
  REL->SetRelation(myRelation);  
  Handle(TDataStd_Variable) V1,V2;
  for (TDF_ListIteratorOfAttributeList it (myVariables); it.More(); it.Next()) {
    V1 = Handle(TDataStd_Variable)::DownCast(it.Value());
    RT->HasRelocation (V1,V2);
    REL->GetVariables().Append(V2);
  }
}

//=======================================================================
//function : Dump
//purpose  : 
//=======================================================================

Standard_OStream& TDataStd_Relation::Dump(Standard_OStream& anOS) const
{ 
  anOS << "Relation";
  return anOS;
}

