// Created by: DAUTRY Philippe
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

//      	------------------

// Version:	0.0
//Version	Date		Purpose
//		0.0	Feb  7 1997	Creation



#include <TDF_Attribute.ixx>

#include <TCollection_AsciiString.hxx>
#include <TDF_DefaultDeltaOnModification.hxx>
#include <TDF_DefaultDeltaOnRemoval.hxx>
#include <TDF_DeltaOnForget.hxx>
#include <TDF_DeltaOnResume.hxx>
#include <TDF_DataSet.hxx>
#include <TDF_Label.hxx>
#include <TDF_LabelNode.hxx>
#include <TDF_Tool.hxx>

#include <Standard_DomainError.hxx>
#include <Standard_ImmutableObject.hxx>

#undef TDF_DATA_COMMIT_OPTIMIZED

#define BUC60879

//=======================================================================
//function : TDF_Attribute
//purpose  : Initializes fields.
//=======================================================================

TDF_Attribute::TDF_Attribute() :
myLabelNode(NULL),
myTransaction(0),
mySavedTransaction(0),
myFlags(1)

{}


//=======================================================================
//function : Label
//purpose  : 
//=======================================================================

const TDF_Label TDF_Attribute::Label() const
{ return TDF_Label(myLabelNode); }


//=======================================================================
//function : Find
//purpose  : 
//=======================================================================

Standard_Boolean TDF_Attribute::FindAttribute (const Standard_GUID& anID,
					       Handle(TDF_Attribute)& anAttribute) const
{
  return Label().FindAttribute(anID,anAttribute);
}

//=======================================================================
//function : IsAttribute
//purpose  : 
//=======================================================================

Standard_Boolean TDF_Attribute::IsAttribute (const Standard_GUID& anID) const
{
  return Label().IsAttribute(anID);
}

//=======================================================================
//function : AddAttribute
//purpose  : 
//=======================================================================

void TDF_Attribute::AddAttribute (const Handle(TDF_Attribute)& otherAttribute)  const
{ Label().AddAttribute (otherAttribute); }



//=======================================================================
//function : ForgetAttribute
//purpose  : 
//=======================================================================

Standard_Boolean  TDF_Attribute::ForgetAttribute (const Standard_GUID& anID) const
{ return Label().ForgetAttribute (anID); }



//=======================================================================
//function : ForgetAllAttributes
//purpose  : 
//=======================================================================

void TDF_Attribute::ForgetAllAttributes (const Standard_Boolean clearChildren) const
{ Label().ForgetAllAttributes (clearChildren); }




//=======================================================================
//function : Forget
//purpose  : 
//=======================================================================

void TDF_Attribute::Forget (const Standard_Integer aTransaction)
{
  mySavedTransaction = myTransaction;
  myTransaction = aTransaction;
  myFlags = (myFlags | TDF_AttributeForgottenMsk);
  Validate(Standard_False);
}


//=======================================================================
//function : Resume
//purpose  : 
//=======================================================================

void TDF_Attribute::Resume()
{
  myTransaction = mySavedTransaction;
  mySavedTransaction = -1; // To say "just resumed"!
  myFlags = (myFlags & ~TDF_AttributeForgottenMsk);
  Validate(Standard_True);
}


//=======================================================================
//function : UntilTransaction
//purpose  : 
//=======================================================================

Standard_Integer TDF_Attribute::UntilTransaction() const
{
  if      (IsForgotten())   return myTransaction;
  else if (IsBackuped())  return myNext->myTransaction - 1;
  else if (IsValid())     return myLabelNode->Data()->Transaction();
  Standard_DomainError::Raise("The attribute structure is wrong.");
  return 0;
}


//=======================================================================
//function : AfterAddition
//purpose  : 
//=======================================================================

void TDF_Attribute::AfterAddition() 
{}


//=======================================================================
//function : BeforeRemoval
//purpose  : 
//=======================================================================

void TDF_Attribute::BeforeRemoval() 
{}

//=======================================================================
//function : BeforeForget
//purpose  : 
//=======================================================================

void TDF_Attribute::BeforeForget() 
{}


//=======================================================================
//function : AfterResume
//purpose  : 
//=======================================================================

void TDF_Attribute::AfterResume() 
{}


//=======================================================================
//function : BeforeUndo
//purpose  : Before application of a TDF_Delta.
//=======================================================================

Standard_Boolean TDF_Attribute::BeforeUndo
(const Handle(TDF_AttributeDelta)& anAttDelta,
 const Standard_Boolean forceIt)
{ return Standard_True; }


//=======================================================================
//function : AfterUndo
//purpose  : After application of a TDF_Delta.
//=======================================================================

Standard_Boolean TDF_Attribute::AfterUndo
(const Handle(TDF_AttributeDelta)& anAttDelta,
 const Standard_Boolean forceIt)
{ return Standard_True; }


//=======================================================================
//function : AfterRetrieval
//purpose  : 
//=======================================================================

Standard_Boolean TDF_Attribute::AfterRetrieval
(const Standard_Boolean forceIt)
{ return Standard_True; }

#ifdef BUC60879
//=======================================================================
//function : BeforeCommitTransaction
//purpose  : 
//=======================================================================

void TDF_Attribute::BeforeCommitTransaction() {}
#endif

//=======================================================================
//function : Backup
//purpose  : Backups the attribute.
//=======================================================================

void TDF_Attribute::Backup()
{
  // The attribute must be valid and attached to a label.
  if (IsValid() && (myLabelNode != NULL)) {
    Handle(TDF_Data) aData = myLabelNode->Data();

    // check that modification is allowed
    if ( !aData->IsModificationAllowed() ) {
      TCollection_AsciiString aMess;
      aMess = "Attribute \"";
      aMess += DynamicType()->Name();
      aMess += "\" is changed outside transaction";
      Standard_ImmutableObject::Raise(aMess.ToCString());
    }

    const Standard_Integer currentTransaction =
      aData->Transaction();
    if (myTransaction < currentTransaction) {//"!=" is less secure.
      Handle(TDF_Attribute) backup = BackupCopy();
#ifdef TDF_DATA_COMMIT_OPTIMIZED
      myLabelNode->AttributesModified(Standard_True);
#endif
      backup->myLabelNode          = myLabelNode;
      backup->myNext               = this; // Back reference;
      backup->myBackup             = myBackup;
      backup->myTransaction        = myTransaction;
      backup->Backup(Standard_True);

      myBackup        = backup;
      myTransaction   = currentTransaction;
    }
  }
}


//=======================================================================
//function : BackupCopy
//purpose  : Standard implementation of BackupCopy.
//=======================================================================

Handle(TDF_Attribute) TDF_Attribute::BackupCopy() const
{
  Handle(TDF_Attribute) copy = NewEmpty(); copy->Restore(this);
  return copy;
}


//=======================================================================
//function : RemoveBackup
//purpose  : 
//=======================================================================

void TDF_Attribute::RemoveBackup()
{
#ifdef DEB
  if (myBackup.IsNull())
    Standard_DomainError::Raise("Impossible to remove a nonexistent backup.");
#endif
  myBackup->BeforeRemoval();
  myBackup->myLabelNode = NULL; // Absolutly necessary!
  myBackup->myNext.Nullify();   // Absolutly necessary!
  myBackup = myBackup->myBackup;
  if (!myBackup.IsNull()) myBackup->myNext = this; // New back reference.
}

//=======================================================================
//function : References
//purpose  : Adds the referenced attributes or labels.
//=======================================================================

void TDF_Attribute::References(const Handle(TDF_DataSet)& aDataSet) const
{}


//=======================================================================
//function : DeltaOnAddition
//purpose  : Creates such a delta.
//=======================================================================

Handle(TDF_DeltaOnAddition) TDF_Attribute::DeltaOnAddition() const
{ return new TDF_DeltaOnAddition(this); }


//=======================================================================
//function : DeltaOnForget
//purpose  : Creates such a delta.
//=======================================================================

Handle(TDF_DeltaOnForget) TDF_Attribute::DeltaOnForget() const
{ return new TDF_DeltaOnForget(this); }


//=======================================================================
//function : DeltaOnResume
//purpose  : Creates such a delta.
//=======================================================================

Handle(TDF_DeltaOnResume) TDF_Attribute::DeltaOnResume() const
{ return new TDF_DeltaOnResume(this); }


//=======================================================================
//function : DeltaOnModification
//purpose  : Creates such a delta.
//=======================================================================

Handle(TDF_DeltaOnModification) TDF_Attribute::DeltaOnModification
(const Handle(TDF_Attribute)& anOldAttribute) const
{ return new TDF_DefaultDeltaOnModification(anOldAttribute); }


//=======================================================================
//function : DeltaOnModification
//purpose  : Applies such a delta.
//=======================================================================

void TDF_Attribute::DeltaOnModification
(const Handle(TDF_DeltaOnModification)& aDelta)
{
  Backup();
  Restore(aDelta->Attribute());
}


//=======================================================================
//function : DeltaOnRemoval
//purpose  : Creates such a delta.
//=======================================================================

Handle(TDF_DeltaOnRemoval) TDF_Attribute::DeltaOnRemoval() const
{ return new TDF_DefaultDeltaOnRemoval(this); } // myBackup


//=======================================================================
//function : Dump
//purpose  : This method is equivalent to operator <<
//=======================================================================

Standard_OStream& TDF_Attribute::Dump(Standard_OStream& anOS) const
{
  anOS<<"\t"<<DynamicType()->Name()<<"\tTrans. "<<myTransaction<<";";
  if (IsValid())     anOS<<" Valid";
  if (IsBackuped())  anOS<<" Backuped";
  if (IsForgotten()) anOS<<" Forgotten";
  char toto[45];
  Standard_PCharacter pStr;
  //
  pStr=toto;
  ID().ToCString(pStr); anOS<<";\tID = "<<toto<<endl;
  //ID().ShallowDump(anOS);anOS<<endl;
  return anOS;
}


//=======================================================================
//function :ExtendedDump
//purpose  : 
//=======================================================================

void TDF_Attribute::ExtendedDump
(Standard_OStream& anOS,
 const TDF_IDFilter& aFilter,
 TDF_AttributeIndexedMap& aMap) const
{ Dump(anOS); }

