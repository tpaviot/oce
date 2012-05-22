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

#include <Transfer_Finder.ixx>
#include <Interface_IntVal.hxx>
#include <Geom2d_CartesianPoint.hxx>
#include <TCollection_HAsciiString.hxx>
#include <Dico_IteratorOfDictionaryOfTransient.hxx>


void  Transfer_Finder::SetHashCode (const Standard_Integer code)
      {  thecode = code;  }

    Standard_Integer  Transfer_Finder::GetHashCode () const
      {  return thecode;  }

    Handle(Standard_Type)  Transfer_Finder::ValueType () const
      {  return DynamicType();  }

    Standard_CString  Transfer_Finder::ValueTypeName () const
      {  return "(finder)";  }


//  ####    ATTRIBUTES    ####


// Integer -> IntVal, Real -> Geom2d_CartesianPoint, CString -> HAsciiString

    void  Transfer_Finder::SetAttribute
  (const Standard_CString name, const Handle(Standard_Transient)& val)
{
  if (theattrib.IsNull()) theattrib = new Dico_DictionaryOfTransient;
  theattrib->SetItem (name,val);
}

    Standard_Boolean  Transfer_Finder::RemoveAttribute
  (const Standard_CString name)
{
  if (theattrib.IsNull()) return Standard_False;
  return theattrib->RemoveItem (name);
}

    Standard_Boolean  Transfer_Finder::GetAttribute
  (const Standard_CString name, const Handle(Standard_Type)& type,
   Handle(Standard_Transient)& val) const
{
  if (theattrib.IsNull())  {  val.Nullify();  return Standard_False;  }
  if (!theattrib->GetItem (name,val))  {  val.Nullify();  return Standard_False;  }
  if (!val->IsKind(type))  {  val.Nullify();  return Standard_False;  }
  return Standard_True;
}

    Handle(Standard_Transient)  Transfer_Finder::Attribute
  (const Standard_CString name) const
{
  Handle(Standard_Transient) atr;
  if (theattrib.IsNull()) return atr;
  if (!theattrib->GetItem (name,atr)) atr.Nullify();
  return atr;
}

    Interface_ParamType  Transfer_Finder::AttributeType
  (const Standard_CString name) const
{
  Handle(Standard_Transient) atr = Attribute(name);
  if (atr.IsNull()) return Interface_ParamVoid;
  if (atr->DynamicType() == STANDARD_TYPE(Interface_IntVal))
    return Interface_ParamInteger;
  if (atr->DynamicType() == STANDARD_TYPE(Geom2d_CartesianPoint))
    return Interface_ParamReal;
  if (atr->DynamicType() == STANDARD_TYPE(TCollection_HAsciiString))
    return Interface_ParamText;
  return Interface_ParamIdent;
}


    void  Transfer_Finder::SetIntegerAttribute
  (const Standard_CString name, const Standard_Integer val)
{
  Handle(Interface_IntVal) ival = new Interface_IntVal;
  ival->CValue() = val;
  SetAttribute (name, ival);
}

    Standard_Boolean  Transfer_Finder::GetIntegerAttribute
  (const Standard_CString name, Standard_Integer& val) const
{
  Handle(Interface_IntVal) ival = Handle(Interface_IntVal)::DownCast
    (Attribute(name));
  if (ival.IsNull())  {  val = 0;  return Standard_False;  }
  val = ival->Value();
  return Standard_True;
}

    Standard_Integer  Transfer_Finder::IntegerAttribute
  (const Standard_CString name) const
{
  Handle(Interface_IntVal) ival = Handle(Interface_IntVal)::DownCast
    (Attribute(name));
  if (ival.IsNull()) return 0;
  return ival->Value();
}

    void  Transfer_Finder::SetRealAttribute
  (const Standard_CString name, const Standard_Real val)
{
  Handle(Geom2d_CartesianPoint) rval = new Geom2d_CartesianPoint (val,0);
  SetAttribute (name,rval);
}

    Standard_Boolean  Transfer_Finder::GetRealAttribute
  (const Standard_CString name, Standard_Real& val) const
{
  Handle(Geom2d_CartesianPoint) rval = Handle(Geom2d_CartesianPoint)::DownCast
    (Attribute(name));
  if (rval.IsNull())  {  val = 0.0;  return Standard_False;  }
  val = rval->X();
  return Standard_True;
}

    Standard_Real  Transfer_Finder::RealAttribute (const Standard_CString name) const
{
  Handle(Geom2d_CartesianPoint) rval = Handle(Geom2d_CartesianPoint)::DownCast
    (Attribute(name));
  if (rval.IsNull()) return 0;
  return rval->X();
}

    void  Transfer_Finder::SetStringAttribute
  (const Standard_CString name, const Standard_CString val)
{
  Handle(TCollection_HAsciiString) hval = new TCollection_HAsciiString (val);
  SetAttribute (name,hval);
}

    Standard_Boolean  Transfer_Finder::GetStringAttribute
  (const Standard_CString name, Standard_CString& val) const
{
  Handle(TCollection_HAsciiString) hval = Handle(TCollection_HAsciiString)::DownCast
    (Attribute(name));
  if (hval.IsNull())  {  val = "";  return Standard_False;  }
  val = hval->ToCString();
  return Standard_True;
}

    Standard_CString  Transfer_Finder::StringAttribute (const Standard_CString name) const
{
  Handle(TCollection_HAsciiString) hval = Handle(TCollection_HAsciiString)::DownCast
    (Attribute(name));
  if (hval.IsNull()) return "";
  return hval->ToCString();
}

    Handle(Dico_DictionaryOfTransient)  Transfer_Finder::AttrList () const
      {  return theattrib;  }

    void  Transfer_Finder::SameAttributes (const Handle(Transfer_Finder)& other)
      {  if (!other.IsNull()) theattrib = other->AttrList();  }

    void  Transfer_Finder::GetAttributes
  (const Handle(Transfer_Finder)& other,
   const Standard_CString fromname, const Standard_Boolean copied)
{
  if (other.IsNull()) return;
  Handle(Dico_DictionaryOfTransient) list = other->AttrList();
  if (list.IsNull()) return;
  if (theattrib.IsNull()) theattrib = new Dico_DictionaryOfTransient;

  for (Dico_IteratorOfDictionaryOfTransient iter (list,fromname);
       iter.More(); iter.Next()) {
    TCollection_AsciiString name = iter.Name();
    Handle(Standard_Transient) atr = iter.Value();
    Handle(Standard_Transient) newatr = atr;

//    Copy ? according type
    if (copied) {
      Handle(Interface_IntVal) ival = Handle(Interface_IntVal)::DownCast(atr);
      if (!ival.IsNull()) {
	Standard_Integer intval = ival->Value();
	ival = new Interface_IntVal;
	ival->CValue() = intval;
	newatr = ival; 
      }
      Handle(Geom2d_CartesianPoint) rval = Handle(Geom2d_CartesianPoint)::DownCast(atr);
      if (!rval.IsNull()) {
	Standard_Real realval = rval->X();
	rval = new Geom2d_CartesianPoint (realval,0);
	newatr = rval;
      }
      Handle(TCollection_HAsciiString) hval = Handle(TCollection_HAsciiString)::DownCast(atr);
      if (!hval.IsNull()) {
	Handle(TCollection_HAsciiString) strval = new TCollection_HAsciiString
	  (hval->ToCString());
	newatr = strval;
      }

    }

    theattrib->SetItem (name.ToCString(),newatr);

  }
}
