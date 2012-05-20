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


#include <BinMDataStd_IntegerDriver.ixx>
#include <TDataStd_Integer.hxx>

//=======================================================================
//function : BinMDataStd_IntegerDriver
//purpose  : Constructor
//=======================================================================

BinMDataStd_IntegerDriver::BinMDataStd_IntegerDriver
                        (const Handle(CDM_MessageDriver)& theMsgDriver)
     : BinMDF_ADriver (theMsgDriver, STANDARD_TYPE(TDataStd_Integer)->Name())
{
}

//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================

Handle(TDF_Attribute) BinMDataStd_IntegerDriver::NewEmpty() const
{
  return new TDataStd_Integer();
}

//=======================================================================
//function : Paste
//purpose  : persistent -> transient (retrieve)
//=======================================================================

Standard_Boolean BinMDataStd_IntegerDriver::Paste
                                (const BinObjMgt_Persistent&  theSource,
                                 const Handle(TDF_Attribute)& theTarget,
                                 BinObjMgt_RRelocationTable&  ) const
{
  Handle(TDataStd_Integer) anAtt = Handle(TDataStd_Integer)::DownCast(theTarget);
  Standard_Integer aValue=0;
  Standard_Boolean ok = theSource >> aValue;
  if (ok)
    anAtt->Set(aValue);
  return ok;
}

//=======================================================================
//function : Paste
//purpose  : transient -> persistent (store)
//=======================================================================

void BinMDataStd_IntegerDriver::Paste (const Handle(TDF_Attribute)& theSource,
                                       BinObjMgt_Persistent&        theTarget,
                                       BinObjMgt_SRelocationTable&  ) const
{
  Handle(TDataStd_Integer) anAtt = Handle(TDataStd_Integer)::DownCast(theSource);
  theTarget << anAtt->Get();
}
