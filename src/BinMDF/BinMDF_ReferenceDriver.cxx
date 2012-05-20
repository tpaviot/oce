// Created on: 2002-10-30
// Created by: Michael SAZONOV
// Copyright (c) 2002-2012 OPEN CASCADE SAS
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


#include <BinMDF_ReferenceDriver.ixx>
#include <TDF_Reference.hxx>

//=======================================================================
//function : BinMDF_ReferenceDriver
//purpose  : Constructor
//=======================================================================

BinMDF_ReferenceDriver::BinMDF_ReferenceDriver
                        (const Handle(CDM_MessageDriver)& theMsgDriver)
     : BinMDF_ADriver (theMsgDriver, STANDARD_TYPE(TDF_Reference)->Name())
{
}

//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================

Handle(TDF_Attribute) BinMDF_ReferenceDriver::NewEmpty() const
{
  return new TDF_Reference();
}

//=======================================================================
//function : Paste
//purpose  : persistent -> transient (retrieve)
//=======================================================================

Standard_Boolean BinMDF_ReferenceDriver::Paste
                (const BinObjMgt_Persistent&   theSource,
                 const Handle(TDF_Attribute)&  theTarget,
                 BinObjMgt_RRelocationTable&   ) const
{
  Handle(TDF_Reference) aRef = Handle(TDF_Reference)::DownCast(theTarget);

  TDF_Label tLab; // Null label.
  if (!theSource.GetLabel(aRef->Label().Data(), tLab))
    return Standard_False;

  // set referenced label
  aRef->Set(tLab);
  return Standard_True;
}

//=======================================================================
//function : Paste
//purpose  : transient -> persistent (store)
//=======================================================================

void BinMDF_ReferenceDriver::Paste (const Handle(TDF_Attribute)&  theSource,
                                    BinObjMgt_Persistent&         theTarget,
                                    BinObjMgt_SRelocationTable&   ) const
{
  Handle(TDF_Reference) aRef = Handle(TDF_Reference)::DownCast(theSource);
  if (!aRef.IsNull()) {
    const TDF_Label& lab = aRef->Label();
    const TDF_Label& refLab = aRef->Get();
    if (!lab.IsNull() && !refLab.IsNull()) {
      if (lab.IsDescendant(refLab.Root())) {   // Internal reference
        theTarget << refLab;
      }
    }
  }
}
