// Created on: 2001-09-04
// Created by: Julia DOROVSKIKH
// Copyright (c) 2001-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <XmlMPrsStd_AISPresentationDriver.ixx>

#include <XmlObjMgt.hxx>

#include <TPrsStd_AISPresentation.hxx>

IMPLEMENT_DOMSTRING (GuidString,        "guid")
IMPLEMENT_DOMSTRING (IsDisplayedString, "isdisplayed")
IMPLEMENT_DOMSTRING (ColorString,       "color")
IMPLEMENT_DOMSTRING (MaterialString,    "material")
IMPLEMENT_DOMSTRING (TransparencyString,"transparency")
IMPLEMENT_DOMSTRING (WidthString,       "width")
IMPLEMENT_DOMSTRING (ModeString,        "mode")

IMPLEMENT_DOMSTRING (DisplayedString,   "true")

//=======================================================================
//function : XmlMPrsStd_AISPresentationDriver
//purpose  : Constructor
//=======================================================================
XmlMPrsStd_AISPresentationDriver::XmlMPrsStd_AISPresentationDriver
                        (const Handle(CDM_MessageDriver)& theMsgDriver)
      : XmlMDF_ADriver (theMsgDriver, NULL)
{}

//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================
Handle(TDF_Attribute) XmlMPrsStd_AISPresentationDriver::NewEmpty() const
{
  return (new TPrsStd_AISPresentation());
}

//=======================================================================
//function : Paste
//purpose  : persistent -> transient (retrieve)
//=======================================================================
Standard_Boolean XmlMPrsStd_AISPresentationDriver::Paste
                                (const XmlObjMgt_Persistent&  theSource,
                                 const Handle(TDF_Attribute)& theTarget,
                                 XmlObjMgt_RRelocationTable&  ) const
{
  TCollection_ExtendedString aMessageString;
  XmlObjMgt_DOMString aDOMStr;

  Handle(TPrsStd_AISPresentation) aTPrs =
    Handle(TPrsStd_AISPresentation)::DownCast(theTarget);
  const XmlObjMgt_Element& anElem = theSource;

  //convert attribute value into GUID
  aDOMStr = anElem.getAttribute(::GuidString());
  if (aDOMStr == NULL)
  {
    WriteMessage("Cannot retrieve guid string from attribute");
    return Standard_False;
  }
  Standard_CString aGuidStr = (Standard_CString) aDOMStr.GetString();
  aTPrs->SetDriverGUID(aGuidStr);

  // is displayed
  aDOMStr = anElem.getAttribute(::IsDisplayedString());
  aTPrs->SetDisplayed(aDOMStr != NULL);

  Standard_Integer anIValue;

  // color
  aDOMStr = anElem.getAttribute(::ColorString());
  if (aDOMStr != NULL)
  {
    if (!aDOMStr.GetInteger(anIValue))
    {
      aMessageString = TCollection_ExtendedString
        ("Cannot retrieve Integer value from \"") + aDOMStr + "\"";
      WriteMessage (aMessageString);
      return Standard_False;
    }
    aTPrs->SetColor((Quantity_NameOfColor)anIValue);
  }
  else
  {
    aTPrs->UnsetColor();
  }

  // material
  aDOMStr = anElem.getAttribute(::MaterialString());
  if (aDOMStr != NULL)
  {
    if (!aDOMStr.GetInteger(anIValue))
    {
      aMessageString = TCollection_ExtendedString
        ("Cannot retrieve Integer value from \"") + aDOMStr + "\"";
      WriteMessage (aMessageString);
      return Standard_False;
    }
    aTPrs->SetMaterial((Graphic3d_NameOfMaterial)anIValue);
  }
  else
  {
    aTPrs->UnsetMaterial();
  }

  Standard_Real aValue;

  // transparency
  aDOMStr = anElem.getAttribute(::TransparencyString());
  if (aDOMStr != NULL)
  {
    if (!XmlObjMgt::GetReal(aDOMStr, aValue))
    {
      aMessageString = TCollection_ExtendedString
        ("Cannot retrieve Real value from \"") + aDOMStr + "\"";
      WriteMessage (aMessageString);
      return Standard_False;
    }
    aTPrs->SetTransparency(aValue);
  }
  else
  {
    aTPrs->UnsetTransparency();
  }

  // width
  aDOMStr = anElem.getAttribute(::WidthString());
  if (aDOMStr != NULL)
  {
    if (!XmlObjMgt::GetReal(aDOMStr, aValue))
    {
      aMessageString = TCollection_ExtendedString
        ("Cannot retrieve Real value from \"") + aDOMStr + "\"";
      WriteMessage (aMessageString);
      return Standard_False;
    }
    aTPrs->SetWidth(aValue);
  }
  else
  {
    aTPrs->UnsetWidth();
  }

  // mode
  aDOMStr = anElem.getAttribute(::ModeString());
  if (aDOMStr != NULL)
  {
    if (!aDOMStr.GetInteger(anIValue))
    {
      aMessageString = TCollection_ExtendedString
        ("Cannot retrieve Integer value from \"") + aDOMStr + "\"";
      WriteMessage (aMessageString);
      return Standard_False;
    }
    aTPrs->SetMode(anIValue);
  }
  else
  {
    aTPrs->UnsetMode();
  }

  return Standard_True;
}

//=======================================================================
//function : Paste
//purpose  : transient -> persistent (store)
//=======================================================================
void XmlMPrsStd_AISPresentationDriver::Paste
                                        (const Handle(TDF_Attribute)& theSource,
                                         XmlObjMgt_Persistent&        theTarget,
                                         XmlObjMgt_SRelocationTable&  ) const
{
  Handle(TPrsStd_AISPresentation) aTPrs =
    Handle(TPrsStd_AISPresentation)::DownCast(theSource);
  if (aTPrs.IsNull()) return;

  //convert GUID into attribute value
  Standard_Character aGuidStr [40];
  Standard_PCharacter pGuidStr;
  pGuidStr=aGuidStr;
  aTPrs->GetDriverGUID().ToCString (pGuidStr);
  theTarget.Element().setAttribute(::GuidString(), aGuidStr);

  // is displayed
  if (aTPrs->IsDisplayed())
    theTarget.Element().setAttribute(::IsDisplayedString(), ::DisplayedString());

  Standard_Integer aNb;

  // color
  if (aTPrs->HasOwnColor())
  {
    aNb = (Standard_Integer)(aTPrs->Color());
    theTarget.Element().setAttribute(::ColorString(), aNb);
  }

  // material
  if (aTPrs->HasOwnMaterial())
  {
    aNb = (Standard_Integer)(aTPrs->Material());
    theTarget.Element().setAttribute(::MaterialString(), aNb);
  }

  // transparency
  if (aTPrs->HasOwnTransparency())
  {
    TCollection_AsciiString aRNbStr (aTPrs->Transparency());
    theTarget.Element().setAttribute(::TransparencyString(), aRNbStr.ToCString());
  }

  // width
  if (aTPrs->HasOwnWidth())
  {
    TCollection_AsciiString aRNbStr (aTPrs->Width());
    theTarget.Element().setAttribute(::WidthString(), aRNbStr.ToCString());
  }

#ifdef OCC6010
  // mode
  if (aTPrs->HasOwnMode())
  {
    aNb = aTPrs->Mode();
    theTarget.Element().setAttribute(::ModeString(), aNb);
  }
#endif
}
