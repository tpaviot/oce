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


#include <XmlMDataXtd_PatternStdDriver.ixx>

#include <TDataStd_Real.hxx>
#include <TDataStd_Integer.hxx>
#include <TDataXtd_PatternStd.hxx>
#include <TNaming_NamedShape.hxx>

IMPLEMENT_DOMSTRING (SignatureString,           "signature")
IMPLEMENT_DOMSTRING (Axis1RevString,            "axis1reversed")
IMPLEMENT_DOMSTRING (Axis2RevString,            "axis2reversed")

IMPLEMENT_DOMSTRING (NbInstances1RefString,     "nbinstances1")
IMPLEMENT_DOMSTRING (Value1RefString,           "value1ref")
IMPLEMENT_DOMSTRING (Axis1RefString,            "axis1")

IMPLEMENT_DOMSTRING (NbInstances2RefString,     "nbinstances2")
IMPLEMENT_DOMSTRING (Value2RefString,           "value2ref")
IMPLEMENT_DOMSTRING (Axis2RefString,            "axis2")

IMPLEMENT_DOMSTRING (MirrorRefString,           "mirror")

IMPLEMENT_DOMSTRING (TrueString,                "true")

//=======================================================================
//function : XmlMDataXtd_PatternStdDriver
//purpose  : Constructor
//=======================================================================
XmlMDataXtd_PatternStdDriver::XmlMDataXtd_PatternStdDriver
                        (const Handle(CDM_MessageDriver)& theMsgDriver)
      : XmlMDF_ADriver (theMsgDriver, NULL)
{}

//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================
Handle(TDF_Attribute) XmlMDataXtd_PatternStdDriver::NewEmpty() const
{
  return (new TDataXtd_PatternStd());
}

//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================
Standard_Boolean XmlMDataXtd_PatternStdDriver::Paste
                        (const XmlObjMgt_Persistent&  theSource,
                         const Handle(TDF_Attribute)& theTarget,
                         XmlObjMgt_RRelocationTable&  theRelocTable) const
{
  Handle(TDataXtd_PatternStd) aP =
    Handle(TDataXtd_PatternStd)::DownCast(theTarget);
  const XmlObjMgt_Element& anElem = theSource;
  
  Standard_Integer aNb;
  TCollection_ExtendedString aMsgString;

  Standard_Integer signature;
  if (!anElem.getAttribute(::SignatureString()).GetInteger(signature))
  {
    aMsgString = TCollection_ExtendedString
      ("XmlMDataXtd_PatternStdDriver: Bad or undefined value for a \"")
        + ::SignatureString() + "\" attribute (must be integer)";
    WriteMessage (aMsgString);
    return Standard_False;
  }
  
  aP->Signature(signature);

  XmlObjMgt_DOMString aString = anElem.getAttribute(::Axis1RevString());
  aP->Axis1Reversed(aString != NULL);
  aString = anElem.getAttribute(::Axis2RevString());
  aP->Axis2Reversed(aString != NULL);
  
  Handle(TNaming_NamedShape) TNS;
  Handle(TDataStd_Real) TReal;
  Handle(TDataStd_Integer) TInt;
  
  if (signature < 5)
  {
    if (!anElem.getAttribute(::Axis1RefString()).GetInteger(aNb))
    {
      aMsgString = TCollection_ExtendedString
        ("XmlMDataXtd_PatternStdDriver: Bad or undefined value for a \"")
          + ::Axis1RefString() + "\" attribute (must be integer)";
      WriteMessage (aMsgString);
      return Standard_False;
    }
    if (theRelocTable.IsBound(aNb))
      TNS = Handle(TNaming_NamedShape)::DownCast(theRelocTable.Find(aNb));
    else
    {
      TNS = new TNaming_NamedShape;
      theRelocTable.Bind(aNb, TNS);
    }
    aP->Axis1(TNS);

    if (!anElem.getAttribute(::Value1RefString()).GetInteger(aNb))
    {
      aMsgString = TCollection_ExtendedString
        ("XmlMDataXtd_PatternStdDriver: Bad or undefined value for a \"")
          + ::Value1RefString() + "\" attribute (must be integer)";
      WriteMessage (aMsgString);
      return Standard_False;
    }
    if (theRelocTable.IsBound(aNb))
      TReal = Handle(TDataStd_Real)::DownCast(theRelocTable.Find(aNb));
    else
    {
      TReal = new TDataStd_Real;
      theRelocTable.Bind(aNb, TReal);
    }
    aP->Value1(TReal);

    if (!anElem.getAttribute(::NbInstances1RefString()).GetInteger(aNb))
    {
      aMsgString = TCollection_ExtendedString
        ("XmlMDataXtd_PatternStdDriver: Bad or undefined value for a \"")
          + ::NbInstances1RefString() + "\" attribute (must be integer)";
      WriteMessage (aMsgString);
      return Standard_False;
    }
    if (theRelocTable.IsBound(aNb))
      TInt = Handle(TDataStd_Integer)::DownCast(theRelocTable.Find(aNb));
    else
    {
      TInt = new TDataStd_Integer;
      theRelocTable.Bind(aNb, TInt);
    }
    aP->NbInstances1(TInt);
    
    if (signature > 2)
    {
      if (!anElem.getAttribute(::Axis2RefString()).GetInteger(aNb))
      {
        aMsgString = TCollection_ExtendedString
          ("XmlMDataXtd_PatternStdDriver: Bad or undefined value for a \"")
            + ::Axis2RefString() + "\" attribute (must be integer)";
        WriteMessage (aMsgString);
        return Standard_False;
      }
      if (theRelocTable.IsBound(aNb))
        TNS = Handle(TNaming_NamedShape)::DownCast(theRelocTable.Find(aNb));
      else
      {
        TNS = new TNaming_NamedShape;
        theRelocTable.Bind(aNb, TNS);
      }
      aP->Axis2(TNS);

      if (!anElem.getAttribute(::Value2RefString()).GetInteger(aNb))
      {
        aMsgString = TCollection_ExtendedString
          ("XmlMDataXtd_PatternStdDriver: Bad or undefined value for a \"")
            + ::Value2RefString() + "\" attribute (must be integer)";
        WriteMessage (aMsgString);
        return Standard_False;
      }
      if (theRelocTable.IsBound(aNb))
        TReal = Handle(TDataStd_Real)::DownCast(theRelocTable.Find(aNb));
      else
      {
        TReal = new TDataStd_Real;
        theRelocTable.Bind(aNb, TReal);
      }
      aP->Value2(TReal);

      if (!anElem.getAttribute(::NbInstances2RefString()).GetInteger(aNb))
      {
        aMsgString = TCollection_ExtendedString
          ("XmlMDataXtd_PatternStdDriver: Bad or undefined value for a \"")
            + ::NbInstances2RefString() + "\" attribute (must be integer)";
        WriteMessage (aMsgString);
        return Standard_False;
      }
      if (theRelocTable.IsBound(aNb))
        TInt = Handle(TDataStd_Integer)::DownCast(theRelocTable.Find(aNb));
      else
      {
        TInt = new TDataStd_Integer;
        theRelocTable.Bind(aNb, TInt);
      }
      aP->NbInstances2(TInt);
    }
  }
  else
  {
    if (!anElem.getAttribute(::MirrorRefString()).GetInteger(aNb))
    {
      aMsgString = TCollection_ExtendedString
        ("XmlMDataXtd_PatternStdDriver: Bad or undefined value for a \"")
          + ::MirrorRefString() + "\" attribute (must be integer)";
      WriteMessage (aMsgString);
      return Standard_False;
    }
    if (theRelocTable.IsBound(aNb))
      TNS = Handle(TNaming_NamedShape)::DownCast(theRelocTable.Find(aNb));
    else
    {
      TNS = new TNaming_NamedShape;
      theRelocTable.Bind(aNb, TNS);
    }
    aP->Mirror(TNS);
  }
  return Standard_True;
}

//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================
void XmlMDataXtd_PatternStdDriver::Paste
                        (const Handle(TDF_Attribute)& theSource,
                         XmlObjMgt_Persistent&        theTarget,
                         XmlObjMgt_SRelocationTable&  theRelocTable) const
{
  Handle(TDataXtd_PatternStd) aP =
    Handle(TDataXtd_PatternStd)::DownCast(theSource);
  XmlObjMgt_Element& anElem = theTarget;
  
  Standard_Integer signature = aP->Signature();
  anElem.setAttribute(::SignatureString(), signature);

  if (aP->Axis1Reversed())
    anElem.setAttribute(::Axis1RevString(), ::TrueString());
  if (aP->Axis2Reversed())
    anElem.setAttribute(::Axis2RevString(), ::TrueString());
  
  Handle(TNaming_NamedShape) TNS;
  Handle(TDataStd_Real) TReal;
  Handle(TDataStd_Integer) TInt;
  
  Standard_Integer aNb;

  if (signature < 5)
  {
    // axis 1
    TNS = aP->Axis1();
    aNb = theRelocTable.FindIndex(TNS);
    if (aNb == 0)
    {
      aNb = theRelocTable.Add(TNS);
    }
    anElem.setAttribute(::Axis1RefString(), aNb);

    // real value 1
    TReal = aP->Value1();
    aNb = theRelocTable.FindIndex(TReal);
    if (aNb == 0)
    {
      aNb = theRelocTable.Add(TReal);
    }
    anElem.setAttribute(::Value1RefString(), aNb);

    // number of instances 1
    TInt = aP->NbInstances1();
    aNb = theRelocTable.FindIndex(TInt);
    if (aNb == 0)
    {
      aNb = theRelocTable.Add(TInt);
    }
    anElem.setAttribute(::NbInstances1RefString(), aNb);
    
    if (signature > 2)
    {
      // axis 2
      TNS = aP->Axis2();
      aNb = theRelocTable.FindIndex(TNS);
      if (aNb == 0)
      {
        aNb = theRelocTable.Add(TNS);
      }
      anElem.setAttribute(::Axis2RefString(), aNb);

      // real value 2
      TReal = aP->Value2();
      aNb = theRelocTable.FindIndex(TReal);
      if (aNb == 0)
      {
        aNb = theRelocTable.Add(TReal);
      }
      anElem.setAttribute(::Value2RefString(), aNb);

      // number of instances 2
      TInt = aP->NbInstances2();
      aNb = theRelocTable.FindIndex(TInt);
      if (aNb == 0)
      {
        aNb = theRelocTable.Add(TInt);
      }
      anElem.setAttribute(::NbInstances2RefString(), aNb);
    }
  }
  else
  {
    TNS = aP->Mirror();
    aNb = theRelocTable.FindIndex(TNS);
    if (aNb == 0)
    {
      aNb = theRelocTable.Add(TNS);
    }
    anElem.setAttribute(::MirrorRefString(), aNb);
  }
}
