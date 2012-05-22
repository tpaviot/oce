// Created on: 1997-07-08
// Created by: Sergey RUIN
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



#include <MPrsStd_AISPresentationStorageDriver.ixx>

#include <PPrsStd_AISPresentation.hxx>
#include <PPrsStd_AISPresentation_1.hxx>
#include <TPrsStd_AISPresentation.hxx>
#include <AIS_InteractiveObject.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_Drawer.hxx>
#include <V3d_Viewer.hxx>
#include <TCollection_ExtendedString.hxx>
#include <PCollection_HExtendedString.hxx>
#include <CDM_MessageDriver.hxx>

//=======================================================================
//function : MPrsStd_AISPresentationStorageDriver
//purpose  : 
//=======================================================================

MPrsStd_AISPresentationStorageDriver::MPrsStd_AISPresentationStorageDriver(const Handle(CDM_MessageDriver)& theMsgDriver):MDF_ASDriver(theMsgDriver)
{
}

Standard_Integer MPrsStd_AISPresentationStorageDriver::VersionNumber() const
{ return 0; }

Handle(Standard_Type) MPrsStd_AISPresentationStorageDriver::SourceType() const
{ return STANDARD_TYPE(TPrsStd_AISPresentation); }

Handle(PDF_Attribute) MPrsStd_AISPresentationStorageDriver::NewEmpty() const
{
// return new PPrsStd_AISPresentation; 
  return new PPrsStd_AISPresentation_1;
}

void MPrsStd_AISPresentationStorageDriver::Paste(const Handle(TDF_Attribute)& Source,
						 const Handle(PDF_Attribute)& Target,
						 const Handle(MDF_SRelocationTable)& RelocTable) const
{
  Handle(TPrsStd_AISPresentation) S = Handle(TPrsStd_AISPresentation)::DownCast (Source);

  // Handle(PPrsStd_AISPresentation) T = Handle(PPrsStd_AISPresentation)::DownCast (Target);
  Handle(PPrsStd_AISPresentation_1) T = Handle(PPrsStd_AISPresentation_1)::DownCast (Target);

  T->SetDisplayed( S->IsDisplayed() );  

  TCollection_ExtendedString  extstr("00000000-0000-0000-0000-000000000000");  //covert GUID into ExtendedString
  Standard_PExtCharacter pStr;
  //
  pStr=(Standard_PExtCharacter)extstr.ToExtString();
  S->GetDriverGUID().ToExtString(pStr); 

  Handle(PCollection_HExtendedString) guid = new PCollection_HExtendedString ( extstr ); 
  T->SetDriverGUID ( guid );    

  if( S->HasOwnColor() ) T->SetColor( (Standard_Integer)(S->Color())  );
  else T->SetColor(-1);

  if( S->HasOwnMaterial() ) T->SetMaterial( (Standard_Integer)(S->Material())  );
  else T->SetMaterial(-1);

  if( S->HasOwnTransparency() ) T->SetTransparency( S->Transparency() );
  else T->SetTransparency(-1.);

  if( S->HasOwnWidth() ) T->SetWidth( S->Width() );
  else T->SetWidth(-1.);  

   T->SetMode(S->Mode());

#ifdef DEB
  cout << "AISPresentationStorageDriver "  << "storaged DriverGUID ==> "   << guid->Convert() << endl;
#endif
}



