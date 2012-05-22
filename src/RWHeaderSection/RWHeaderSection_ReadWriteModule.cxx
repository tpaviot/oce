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

#include <RWHeaderSection_ReadWriteModule.ixx>
#include <Interface_ReaderLib.hxx>
#include <StepData_WriterLib.hxx>
#include <HeaderSection_Protocol.hxx>
#include <Interface_Macros.hxx>
#include <Interface_ParamType.hxx>


#include <HeaderSection_FileName.hxx>
#include <HeaderSection_FileDescription.hxx>
#include <HeaderSection_FileSchema.hxx>

#include <StepData_UndefinedEntity.hxx>


#include <RWHeaderSection_RWFileName.hxx>
#include <RWHeaderSection_RWFileDescription.hxx>
#include <RWHeaderSection_RWFileSchema.hxx>

// -- General Declarations (Recognize, StepType) ---

static TCollection_AsciiString PasReco("");    // neutralise StartEntity de SW
static TCollection_AsciiString Reco_FileName ("FILE_NAME");
static TCollection_AsciiString Reco_FileDescription ("FILE_DESCRIPTION");
static TCollection_AsciiString Reco_FileSchema ("FILE_SCHEMA");

	// -- Definition of the libraries --

RWHeaderSection_ReadWriteModule::RWHeaderSection_ReadWriteModule ()
{
	Handle(HeaderSection_Protocol) protocol = new HeaderSection_Protocol;
	StepData_WriterLib::SetGlobal(this,protocol);
	Interface_ReaderLib::SetGlobal(this,protocol);
}

	// --- Case Recognition ---

Standard_Integer RWHeaderSection_ReadWriteModule::CaseStep
	(const TCollection_AsciiString& key) const
{
	if (key.IsEqual(Reco_FileName)) return 1;
	if (key.IsEqual(Reco_FileDescription)) return 2;
	if (key.IsEqual(Reco_FileSchema)) return 3;
return 0;
}

	// --- External Mapping Case Recognition ---

Standard_Integer RWHeaderSection_ReadWriteModule::CaseStep
	(const TColStd_SequenceOfAsciiString& types) const
{

#ifdef DEB
  Standard_Integer NbComp = types.Length();
  if (NbComp < 2) {
    cout << "Plex Instance illegal " << endl;
  }
#endif
  return 0;
}


	// --- External Mapping Recognition ---

Standard_Boolean RWHeaderSection_ReadWriteModule::IsComplex
	(const Standard_Integer CN) const
{
	return Standard_False;
}



const TCollection_AsciiString& RWHeaderSection_ReadWriteModule::StepType
	(const Standard_Integer CN) const
{
	switch (CN) {
	  case 1 : return Reco_FileName;
	  case 2 : return Reco_FileDescription;
	  case 3 : return Reco_FileSchema;
	  default : return PasReco;
	}
}

	// -- Reading of a file --

void RWHeaderSection_ReadWriteModule::ReadStep
	(const Standard_Integer CN,
	 const Handle(StepData_StepReaderData)& data,
	 const Standard_Integer num,
	 Handle(Interface_Check)& ach,
	 const Handle(Standard_Transient)&ent) const
{
	if (CN == 0) return;
	switch (CN) {
	  case 1 : 
	    {
	      DeclareAndCast(HeaderSection_FileName, anent, ent);
	      RWHeaderSection_RWFileName tool;
	      if (anent.IsNull()) ach->AddFail("Type Mismatch on FileName");
	      else tool.ReadStep (data,num,ach,anent);
	    }

	    break;
	  case 2 : 
	    {
	      DeclareAndCast(HeaderSection_FileDescription, anent, ent);
	      RWHeaderSection_RWFileDescription tool;
	      if (anent.IsNull()) ach->AddFail("Type Mismatch on FileDescription");
	      else tool.ReadStep (data,num,ach,anent);
	    }

	    break;
	  case 3 : 
	    {
	      DeclareAndCast(HeaderSection_FileSchema, anent, ent);
	      RWHeaderSection_RWFileSchema tool;
	      if (anent.IsNull()) ach->AddFail("Type Mismatch on FileSchema");
	      else tool.ReadStep (data,num,ach,anent);
	    }

	    break;
	  case 4 : 
	    {
	      DeclareAndCast(StepData_UndefinedEntity,und,ent);
	      if (und.IsNull()) ach->AddFail
		("# Entity neither Recognized nor set as UndefinedEntity from StepData #");
	      else und->ReadRecord(data,num,ach);
	    }

	    break;
	  default : ach->AddFail("Type Mismatch when reading - Entity");
	}

return;}

	// -- Writing of a file --

void RWHeaderSection_ReadWriteModule::WriteStep
	(const Standard_Integer CN,
	 StepData_StepWriter& SW,
	 const Handle(Standard_Transient)&ent) const
{
	if (CN == 0) return;
	switch (CN) {
	  case 1 : 
	    {
	      DeclareAndCast(HeaderSection_FileName, anent, ent);
	      RWHeaderSection_RWFileName tool;
	      if (anent.IsNull()) return; 
	      else tool.WriteStep (SW,anent);
	    }

	    break;
	  case 2 : 
	    {
	      DeclareAndCast(HeaderSection_FileDescription, anent, ent);
	      RWHeaderSection_RWFileDescription tool;
	      if (anent.IsNull()) return; 
	      else tool.WriteStep (SW,anent);
	    }

	    break;
	  case 3 : 
	    {
	      DeclareAndCast(HeaderSection_FileSchema, anent, ent);
	      RWHeaderSection_RWFileSchema tool;
	      if (anent.IsNull()) return; 
	      else tool.WriteStep (SW,anent);
	    }

	    break;
	  case 4 : 
	    {
	      DeclareAndCast(StepData_UndefinedEntity,und,ent);
	      if (und.IsNull()) break;
//  Parentheses gerees par StepWriter lui-meme
//   car en recevant le type PasReco, StepWriter ne l'affiche pas,
//   mais il gere les parentheses comme si de rien n etait
	      if (und->IsComplex())   SW.StartComplex();
	      und->WriteParams(SW);
	      if (und->IsComplex())   SW.EndComplex();
	    }

	    break;
	  default : return;
	}
}

