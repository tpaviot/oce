// Created on: 1997-12-16
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



#include <TDataStd_Expression.ixx>
#include <TCollection_AsciiString.hxx>
#include <TDataStd_Variable.hxx>
#include <TDF_ListIteratorOfAttributeList.hxx>

//=======================================================================
//function : GetID
//purpose  : 
//=======================================================================

const Standard_GUID& TDataStd_Expression::GetID() 
{  
  static Standard_GUID TDataStd_ExpressionID("ce24146a-8e57-11d1-8953-080009dc4425");
  return TDataStd_ExpressionID;
}

//=======================================================================
//function : Set
//purpose  : 
//=======================================================================

Handle(TDataStd_Expression) TDataStd_Expression::Set(const TDF_Label& L) 
{  
  Handle(TDataStd_Expression) A;
  if (!L.FindAttribute (TDataStd_Expression::GetID(), A)) {
    A = new TDataStd_Expression (); 
    L.AddAttribute(A);
  }
  return A;
}

//=======================================================================
//function : TDataStd_Expression
//purpose  : 
//=======================================================================

TDataStd_Expression::TDataStd_Expression()
{
}


//=======================================================================
//function : Name
//purpose  : 
//=======================================================================
TCollection_ExtendedString TDataStd_Expression::Name () const 
{  
  return myExpression; // ->String();
}

//=======================================================================
//function : SetExpression
//purpose  : 
//=======================================================================

void TDataStd_Expression::SetExpression(const TCollection_ExtendedString& E)
{
  // OCC2932 correction
  if(myExpression == E) return;

  Backup();
  myExpression = E;
}

//=======================================================================
//function : GetExpression
//purpose  : 
//=======================================================================

const TCollection_ExtendedString& TDataStd_Expression::GetExpression () const
{
  return myExpression;
}

//=======================================================================
//function : GetVariables
//purpose  : 
//=======================================================================

TDF_AttributeList& TDataStd_Expression::GetVariables()
{
  return myVariables;
}

//=======================================================================
//function : ID
//purpose  : 
//=======================================================================

const Standard_GUID& TDataStd_Expression::ID() const
{
  return GetID();
}

//=======================================================================
//function : Restore
//purpose  : 
//=======================================================================

void TDataStd_Expression::Restore(const Handle(TDF_Attribute)& With) 
{  
  Handle(TDataStd_Expression) EXPR = Handle(TDataStd_Expression)::DownCast (With);
  myExpression = EXPR->GetExpression();

  Handle(TDataStd_Variable) V;
  for (TDF_ListIteratorOfAttributeList it (EXPR->GetVariables()); it.More(); it.Next()) {
    V = Handle(TDataStd_Variable)::DownCast(it.Value());
    myVariables.Append(V);
  }
}

//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================

Handle(TDF_Attribute) TDataStd_Expression::NewEmpty() const
{
  return new TDataStd_Expression();
}

//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================

void TDataStd_Expression::Paste(const Handle(TDF_Attribute)& Into,
				 const Handle(TDF_RelocationTable)& RT) const
{  
  Handle(TDataStd_Expression) EXPR = Handle(TDataStd_Expression)::DownCast (Into); 
  EXPR->SetExpression(myExpression);  
  Handle(TDataStd_Variable) V1,V2;
  for (TDF_ListIteratorOfAttributeList it (myVariables); it.More(); it.Next()) {
    V1 = Handle(TDataStd_Variable)::DownCast(it.Value());
    RT->HasRelocation (V1,V2);
    EXPR->GetVariables().Append(V2);
  }
}

//=======================================================================
//function : Dump
//purpose  : 
//=======================================================================

Standard_OStream& TDataStd_Expression::Dump(Standard_OStream& anOS) const
{ 
  anOS << "Expression";
  return anOS;
}

