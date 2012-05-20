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

#include <MDF_ReferenceRetrievalDriver.ixx>
#include <PCollection_HAsciiString.hxx>
#include <PDF_Reference.hxx>
#include <Standard_NoSuchObject.hxx>
#include <TCollection_AsciiString.hxx>
#include <TDF_Label.hxx>
#include <TDF_Tool.hxx>
#include <TDF_Reference.hxx>
#include <CDM_MessageDriver.hxx>

#define DeclareAndSpeedCast(V,T,Vdown) Handle(T) Vdown = *((Handle(T)*)& V)
#define DeclareConstAndSpeedCast(V,T,Vdown) const Handle(T)& Vdown = (Handle(T)&) V
#define SpeedCast(V,T,Vdown) Vdown = *((Handle(T)*)& V)

MDF_ReferenceRetrievalDriver::MDF_ReferenceRetrievalDriver(const Handle(CDM_MessageDriver)& theMsgDriver):MDF_ARDriver(theMsgDriver)
{
}

Standard_Integer MDF_ReferenceRetrievalDriver::VersionNumber() const
{ return 0; }

Handle(Standard_Type) MDF_ReferenceRetrievalDriver::SourceType() const
{ return STANDARD_TYPE (PDF_Reference); }

Handle(TDF_Attribute) MDF_ReferenceRetrievalDriver::NewEmpty() const
{ return new TDF_Reference; }

void MDF_ReferenceRetrievalDriver::Paste (
  const Handle(PDF_Attribute)&        Source,
  const Handle(TDF_Attribute)&        Target,
//  const Handle(MDF_RRelocationTable)& RelocTable) const
  const Handle(MDF_RRelocationTable)& ) const

{
  DeclareAndSpeedCast(Source,PDF_Reference,S);
  DeclareAndSpeedCast(Target,TDF_Reference,T);
  TDF_Label tLab; // Null label.
  Handle(PCollection_HAsciiString) pEntry = S->ReferencedLabel();
  if (!pEntry.IsNull()) {
    TCollection_AsciiString entry = pEntry->Convert();
    TDF_Tool::Label(T->Label().Data(),entry,tLab,Standard_True);
  }
  T->Set(tLab);
}

