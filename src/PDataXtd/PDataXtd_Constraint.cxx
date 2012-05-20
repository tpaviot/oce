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

#include <PDataXtd_Constraint.ixx>



PDataXtd_Constraint::PDataXtd_Constraint () { }

PDataXtd_Constraint::PDataXtd_Constraint(const Standard_Integer Type,
					 const Handle(PDF_HAttributeArray1)& Geometries,
					 const Handle(PDataStd_Real)& Value,
					 const Handle(PNaming_NamedShape)& Plane)

: myType (Type), myGeometries (Geometries), myValue (Value), myIsReversed(Standard_False),
  myIsInverted(Standard_False),
  myIsVerified(Standard_True),
  myPlane(Plane)
  {}

Handle(PDataStd_Real) PDataXtd_Constraint::GetValue() const
{ return myValue; }

Standard_Integer PDataXtd_Constraint::GetType() const
{ return myType; }

Handle(PDF_HAttributeArray1) PDataXtd_Constraint::GetGeometries() const
{ return myGeometries; }

Handle(PNaming_NamedShape) PDataXtd_Constraint::GetPlane() const 
{ return myPlane;}

void PDataXtd_Constraint::SetPlane(const Handle(PNaming_NamedShape)& plane)
{ myPlane = plane;}

void PDataXtd_Constraint::Set(const Handle(PDataStd_Real)& V) 
{ myValue = V; }

void PDataXtd_Constraint::SetType(const Standard_Integer Type) 
{ myType = Type; }

void PDataXtd_Constraint::SetGeometries(const Handle(PDF_HAttributeArray1)& Geometries) 
{ myGeometries = Geometries; }

//=======================================================================
//function : Verified
//purpose  : 
//=======================================================================
void PDataXtd_Constraint::Verified(const Standard_Boolean status)
{
  myIsVerified = status;
}

//=======================================================================
//function : Verified
//purpose  : 
//=======================================================================
Standard_Boolean PDataXtd_Constraint::Verified() const 
{
  return myIsVerified;
}

//=======================================================================
//function : Reversed
//purpose  : 
//=======================================================================
void PDataXtd_Constraint::Reversed(const Standard_Boolean status)
{
  myIsReversed = status;
}

//=======================================================================
//function : Reversed
//purpose  : 
//=======================================================================
Standard_Boolean PDataXtd_Constraint::Reversed() const 
{
  return myIsReversed;
}

//=======================================================================
//function : Inverted
//purpose  : 
//=======================================================================
void PDataXtd_Constraint::Inverted(const Standard_Boolean status)
{
  myIsInverted = status;
}

//=======================================================================
//function : Inverted
//purpose  : 
//=======================================================================
Standard_Boolean PDataXtd_Constraint::Inverted() const 
{
  return myIsInverted;
}
