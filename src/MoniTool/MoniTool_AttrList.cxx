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

#include <MoniTool_AttrList.ixx>
#include <MoniTool_IntVal.hxx>
#include <MoniTool_RealVal.hxx>
#include <TCollection_HAsciiString.hxx>
#include <Dico_IteratorOfDictionaryOfTransient.hxx>

MoniTool_AttrList::MoniTool_AttrList ()    {  }

    MoniTool_AttrList::MoniTool_AttrList (const MoniTool_AttrList& other)
    : theattrib (other.AttrList())    {  }

//  ####    ATTRIBUTES    ####


// Integer -> IntVal, Real -> RealVal, CString -> HAsciiString

    void  MoniTool_AttrList::SetAttribute
  (const Standard_CString name, const Handle(Standard_Transient)& val)
{
  if (theattrib.IsNull()) theattrib = new Dico_DictionaryOfTransient;
  theattrib->SetItem (name,val);
}

    Standard_Boolean  MoniTool_AttrList::RemoveAttribute
  (const Standard_CString name)
{
  if (theattrib.IsNull()) return Standard_False;
  return theattrib->RemoveItem (name);
}

    Standard_Boolean  MoniTool_AttrList::GetAttribute
  (const Standard_CString name, const Handle(Standard_Type)& type,
   Handle(Standard_Transient)& val) const
{
  if (theattrib.IsNull())  {  val.Nullify();  return Standard_False;  }
  if (!theattrib->GetItem (name,val))  {  val.Nullify();  return Standard_False;  }
  if (!val->IsKind(type))  {  val.Nullify();  return Standard_False;  }
  return Standard_True;
}

    Handle(Standard_Transient)  MoniTool_AttrList::Attribute
  (const Standard_CString name) const
{
  Handle(Standard_Transient) atr;
  if (theattrib.IsNull()) return atr;
  if (!theattrib->GetItem (name,atr)) atr.Nullify();
  return atr;
}

    MoniTool_ValueType  MoniTool_AttrList::AttributeType
  (const Standard_CString name) const
{
  Handle(Standard_Transient) atr = Attribute(name);
  if (atr.IsNull()) return MoniTool_ValueVoid;
  if (atr->DynamicType() == STANDARD_TYPE(MoniTool_IntVal))
    return MoniTool_ValueInteger;
  if (atr->DynamicType() == STANDARD_TYPE(MoniTool_RealVal))
    return MoniTool_ValueReal;
  if (atr->DynamicType() == STANDARD_TYPE(TCollection_HAsciiString))
    return MoniTool_ValueText;
  return MoniTool_ValueIdent;
}


    void  MoniTool_AttrList::SetIntegerAttribute
  (const Standard_CString name, const Standard_Integer val)
{
  Handle(MoniTool_IntVal) ival = new MoniTool_IntVal;
  ival->CValue() = val;
  SetAttribute (name, ival);
}

    Standard_Boolean  MoniTool_AttrList::GetIntegerAttribute
  (const Standard_CString name, Standard_Integer& val) const
{
  Handle(MoniTool_IntVal) ival = Handle(MoniTool_IntVal)::DownCast
    (Attribute(name));
  if (ival.IsNull())  {  val = 0;  return Standard_False;  }
  val = ival->Value();
  return Standard_True;
}

    Standard_Integer  MoniTool_AttrList::IntegerAttribute
  (const Standard_CString name) const
{
  Handle(MoniTool_IntVal) ival = Handle(MoniTool_IntVal)::DownCast
    (Attribute(name));
  if (ival.IsNull()) return 0;
  return ival->Value();
}

    void  MoniTool_AttrList::SetRealAttribute
  (const Standard_CString name, const Standard_Real val)
{
  Handle(MoniTool_RealVal) rval = new MoniTool_RealVal;
  rval->CValue() = val;
  SetAttribute (name,rval);
}

    Standard_Boolean  MoniTool_AttrList::GetRealAttribute
  (const Standard_CString name, Standard_Real& val) const
{
  Handle(MoniTool_RealVal) rval = Handle(MoniTool_RealVal)::DownCast
    (Attribute(name));
  if (rval.IsNull())  {  val = 0.0;  return Standard_False;  }
  val = rval->Value();
  return Standard_True;
}

    Standard_Real  MoniTool_AttrList::RealAttribute (const Standard_CString name) const
{
  Handle(MoniTool_RealVal) rval = Handle(MoniTool_RealVal)::DownCast
    (Attribute(name));
  if (rval.IsNull()) return 0;
  return rval->Value();
}

    void  MoniTool_AttrList::SetStringAttribute
  (const Standard_CString name, const Standard_CString val)
{
  Handle(TCollection_HAsciiString) hval = new TCollection_HAsciiString (val);
  SetAttribute (name,hval);
}

    Standard_Boolean  MoniTool_AttrList::GetStringAttribute
  (const Standard_CString name, Standard_CString& val) const
{
  Handle(TCollection_HAsciiString) hval = Handle(TCollection_HAsciiString)::DownCast
    (Attribute(name));
  if (hval.IsNull())  {  val = "";  return Standard_False;  }
  val = hval->ToCString();
  return Standard_True;
}

    Standard_CString  MoniTool_AttrList::StringAttribute (const Standard_CString name) const
{
  Handle(TCollection_HAsciiString) hval = Handle(TCollection_HAsciiString)::DownCast
    (Attribute(name));
  if (hval.IsNull()) return "";
  return hval->ToCString();
}

    Handle(Dico_DictionaryOfTransient)  MoniTool_AttrList::AttrList () const
      {  return theattrib;  }

    void  MoniTool_AttrList::SameAttributes (const MoniTool_AttrList& other)
      {  theattrib = other.AttrList();  }

    void  MoniTool_AttrList::GetAttributes
  (const MoniTool_AttrList& other,
   const Standard_CString fromname, const Standard_Boolean copied)
{
  Handle(Dico_DictionaryOfTransient) list = other.AttrList();
  if (list.IsNull()) return;
  if (theattrib.IsNull()) theattrib = new Dico_DictionaryOfTransient;

  for (Dico_IteratorOfDictionaryOfTransient iter (list,fromname);
       iter.More(); iter.Next()) {
    TCollection_AsciiString name = iter.Name();
    Handle(Standard_Transient) atr = iter.Value();
    Handle(Standard_Transient) newatr = atr;

//    Copy ? according type
    if (copied) {
      Handle(MoniTool_IntVal) ival = Handle(MoniTool_IntVal)::DownCast(atr);
      if (!ival.IsNull()) {
	Standard_Integer intval = ival->Value();
	ival = new MoniTool_IntVal;
	ival->CValue() = intval;
	newatr = ival; 
      }
      Handle(MoniTool_RealVal) rval = Handle(MoniTool_RealVal)::DownCast(atr);
      if (!rval.IsNull()) {
	Standard_Real realval = rval->Value();
	rval = new MoniTool_RealVal;
	rval->CValue() = realval;
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
