// Created on: 2001-08-24
// Created by: Alexnder GRIGORIEV
// Copyright (c) 2001-2012 OPEN CASCADE SAS
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


#include <XmlMDataStd_VariableDriver.ixx>
#include <TDataStd_Variable.hxx>

IMPLEMENT_DOMSTRING (IsConstString, "isconst")
IMPLEMENT_DOMSTRING (UnitString,    "unit")
IMPLEMENT_DOMSTRING (ConstString,   "true")

//=======================================================================
//function : XmlMDataStd_VariableDriver
//purpose  : Constructor
//=======================================================================
XmlMDataStd_VariableDriver::XmlMDataStd_VariableDriver
                        (const Handle(CDM_MessageDriver)& theMsgDriver)
      : XmlMDF_ADriver (theMsgDriver, NULL)
{}

//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================
Handle(TDF_Attribute) XmlMDataStd_VariableDriver::NewEmpty() const
{
  return (new TDataStd_Variable());
}

//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================
Standard_Boolean XmlMDataStd_VariableDriver::Paste
                                (const XmlObjMgt_Persistent&  theSource,
                                 const Handle(TDF_Attribute)& theTarget,
                                 XmlObjMgt_RRelocationTable&  ) const
{
  Handle(TDataStd_Variable) aV = Handle(TDataStd_Variable)::DownCast(theTarget);
  
  XmlObjMgt_DOMString aStr =
    theSource.Element().getAttribute(::IsConstString());
  aV->Constant (aStr != NULL);

  aStr = theSource.Element().getAttribute(::UnitString());
  aV->Unit(aStr);
  return Standard_True;
}

//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================
void XmlMDataStd_VariableDriver::Paste (const Handle(TDF_Attribute)& theSource,
                                        XmlObjMgt_Persistent&        theTarget,
                                        XmlObjMgt_SRelocationTable&  ) const
{
  Handle(TDataStd_Variable) aV = Handle(TDataStd_Variable)::DownCast(theSource);
  if (aV->IsConstant())
    theTarget.Element().setAttribute (::IsConstString(), ::ConstString());
  theTarget.Element().setAttribute(::UnitString(), aV->Unit().ToCString());
}
