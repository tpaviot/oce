// Copyright (c) 1998-1999 Matra Datavision
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

#include <PrsMgr_PresentationManager.ixx>
#include <PrsMgr_PresentableObject.hxx>
#include <PrsMgr_Presentation.hxx>
#include <PrsMgr_Presentations.hxx>
#include <PrsMgr_ModedPresentation.hxx>
#include <TColStd_ListIteratorOfListOfTransient.hxx>


PrsMgr_PresentationManager::PrsMgr_PresentationManager ():
myImmediateMode(Standard_False){}


void PrsMgr_PresentationManager::Display(
    const Handle(PrsMgr_PresentableObject)& aPresentableObject,
    const Standard_Integer aMode) 
{
  if (!HasPresentation(aPresentableObject,aMode)){
    AddPresentation(aPresentableObject,aMode);
  }
  else if(Presentation(aPresentableObject,aMode)->MustBeUpdated()){
    Update(aPresentableObject,aMode);
  }
  
  if(myImmediateMode)
    Add(aPresentableObject,aMode);
  else
    Presentation(aPresentableObject,aMode)->Display();
}

void PrsMgr_PresentationManager::Erase(
    const Handle(PrsMgr_PresentableObject)& aPresentableObject,
    const Standard_Integer aMode) 
{
  if (HasPresentation(aPresentableObject,aMode)){
    if(myImmediateMode)
      Remove(aPresentableObject,aMode);
    else
     Presentation(aPresentableObject,aMode)->Erase();}
}

void PrsMgr_PresentationManager::Clear(const Handle(PrsMgr_PresentableObject)& aPresentableObject,
				       const Standard_Integer aMode) 
{
  if (HasPresentation(aPresentableObject,aMode)){
    if(myImmediateMode)
      Remove(aPresentableObject,aMode);
    else
      Presentation(aPresentableObject,aMode)->Clear();}
}


void PrsMgr_PresentationManager::Highlight(
    const Handle(PrsMgr_PresentableObject)& aPresentableObject,
    const Standard_Integer aMode)
{
  if (!HasPresentation(aPresentableObject,aMode)){
    AddPresentation(aPresentableObject,aMode);
  }
  else if(Presentation(aPresentableObject,aMode)->MustBeUpdated()){
    Update(aPresentableObject,aMode);
  }
  Presentation(aPresentableObject,aMode)->Highlight();

  if(myImmediateMode)
    Add(aPresentableObject,aMode);
}

void PrsMgr_PresentationManager::Unhighlight(
    const Handle(PrsMgr_PresentableObject)& aPresentableObject,
    const Standard_Integer aMode) 
{
  if (HasPresentation(aPresentableObject,aMode)){
    Presentation(aPresentableObject,aMode)->Unhighlight();
    if(myImmediateMode)
      Remove(aPresentableObject,aMode);
  }
}


void PrsMgr_PresentationManager::
SetDisplayPriority(const Handle(PrsMgr_PresentableObject)& aPresentableObject,
		   const Standard_Integer aMode,
		   const Standard_Integer theNewPrior) const 
{
  if (HasPresentation(aPresentableObject,aMode))
    Presentation(aPresentableObject,aMode)->SetDisplayPriority(theNewPrior);
}

Standard_Integer PrsMgr_PresentationManager::
DisplayPriority(const Handle(PrsMgr_PresentableObject)& aPresentableObject,
		const Standard_Integer aMode) const 
{
  if (HasPresentation(aPresentableObject,aMode))
    return Presentation(aPresentableObject,aMode)->DisplayPriority();
  
  return 0;
}


Standard_Boolean PrsMgr_PresentationManager::IsDisplayed (    
    const Handle(PrsMgr_PresentableObject)& aPresentableObject,
    const Standard_Integer aMode) const {
     if (HasPresentation(aPresentableObject,aMode))
       return Presentation(aPresentableObject,aMode)->IsDisplayed();
     return Standard_False;
    }

Standard_Boolean PrsMgr_PresentationManager::IsHighlighted (    
    const Handle(PrsMgr_PresentableObject)& aPresentableObject,
    const Standard_Integer aMode) const {
          if (HasPresentation(aPresentableObject,aMode))
       return Presentation(aPresentableObject,aMode)->IsHighlighted();
     return Standard_False;
    }

void PrsMgr_PresentationManager::Update (const Handle(PrsMgr_PresentableObject)& aPresentableObject,const Standard_Integer aMode ) const {
  if(HasPresentation(aPresentableObject,aMode)) {
    Handle(PrsMgr_Presentation) P = Presentation(aPresentableObject,aMode);
    if (!P.IsNull()) {
      P->Clear();
      aPresentableObject->Fill(this,P,aMode);
      P->SetUpdateStatus(Standard_False);
    }
  }
}
void PrsMgr_PresentationManager::BeginDraw() {
  myImmediateMode = Standard_True;
  myImmediateList.Clear();
}


void PrsMgr_PresentationManager::Add(const Handle(PrsMgr_PresentableObject)& aPresentableObject,
				     const Standard_Integer aMode) {
  if (myImmediateMode ) {
    Handle(PrsMgr_Presentation) P = Presentation(aPresentableObject,aMode);
    for (TColStd_ListIteratorOfListOfTransient it(myImmediateList);it.More();it.Next()){
      if(it.Value()==P) return;
    }
    myImmediateList.Append(P);
  }
}
void PrsMgr_PresentationManager::Remove(const Handle(PrsMgr_PresentableObject)& aPresentableObject,
				     const Standard_Integer aMode) {
  if (myImmediateMode ) {
    Handle(PrsMgr_Presentation) P = Presentation(aPresentableObject,aMode);
    for (TColStd_ListIteratorOfListOfTransient it(myImmediateList);it.More();it.Next()){
      if(it.Value()==P) {
	myImmediateList.Remove(it);
	return;
      }
    }
  }
}




Standard_Boolean PrsMgr_PresentationManager::HasPresentation
    (const Handle(PrsMgr_PresentableObject)& aPresentableObject,
     const Standard_Integer aMode) const {

       const PrsMgr_Presentations& S = aPresentableObject->Presentations();
       Standard_Boolean found = Standard_False;
       Standard_Integer i=1; Standard_Integer l= S.Length();
       while (i<= l && !found) {
// modif WOK++ : operator == is ambiguous 
//	 found =  aMode == S(i).Mode()
//	          && this == S(i).Presentation()->PresentationManager();
	 const Handle (PrsMgr_Presentation)& popPrs = S(i).Presentation();
	 const Handle (PrsMgr_PresentationManager)& popPrsMgr = popPrs->PresentationManager();
	 if ( aMode == S(i).Mode() && this == popPrsMgr ) 
	   found = Standard_True;
	 i++;
       }
       return found;
     }

Handle (PrsMgr_Presentation) 
     PrsMgr_PresentationManager::Presentation(const Handle(PrsMgr_PresentableObject)& aPresentableObject,
					      const Standard_Integer aMode) const 
{
  Handle(PrsMgr_Presentation) P;
  const PrsMgr_Presentations& S  = aPresentableObject->Presentations();
  Standard_Boolean found = Standard_False;
  Standard_Integer i=1; Standard_Integer l= S.Length();
  while (i<= l && !found) {
    P =  S(i).Presentation();
    const Handle (PrsMgr_PresentationManager)& popPrsMgr = P->PresentationManager();
    if (aMode == S(i).Mode() && this ==  popPrsMgr) {
      found = Standard_True;


    }
    i++;
  }

  return P;
}

void PrsMgr_PresentationManager::AddPresentation
           (const Handle(PrsMgr_PresentableObject)& aPresentableObject,
	    const Standard_Integer aMode) {

    Handle(PrsMgr_Presentation) P = newPresentation(aPresentableObject);
    aPresentableObject->Presentations().Append(PrsMgr_ModedPresentation(P,aMode));
    aPresentableObject->Fill(this,P,aMode);

    // set layer index accordingly to object's presentations
    Standard_Integer aZLayerId = GetZLayer (aPresentableObject);
    if (aZLayerId >= 0)
      P->SetZLayer (aZLayerId);

    P->SetUpdateStatus(Standard_False);
}

void PrsMgr_PresentationManager::RemovePresentation(const Handle(PrsMgr_PresentableObject)& aPresentableObject,
                                                    const Standard_Integer aMode)
{
  PrsMgr_Presentations& S = aPresentableObject->Presentations();
  Standard_Integer i = 1; 
  Standard_Integer n = S.Length();
  while (i<= n) {
    if (aMode == S(i).Mode()) {
      S.Remove(i);
      break;
    }
    i++;
  }
}

//=======================================================================
//function : SetZLayer
//purpose  :
//=======================================================================

void PrsMgr_PresentationManager::SetZLayer 
  (const Handle(PrsMgr_PresentableObject)& thePresentableObject,
   const Standard_Integer theLayerId)
{
  PrsMgr_Presentations& aPresentations = thePresentableObject->Presentations();
  for (Standard_Integer aIdx = 1; aIdx <= aPresentations.Length (); aIdx++)
  {
    Handle(PrsMgr_Presentation) aPrs = aPresentations (aIdx).Presentation ();
    if (aPrs->PresentationManager () == this)
      aPrs->SetZLayer (theLayerId);
  }
}

//=======================================================================
//function : GetZLayer
//purpose  :
//=======================================================================

Standard_Integer PrsMgr_PresentationManager::GetZLayer 
  (const Handle(PrsMgr_PresentableObject)& thePresentableObject) const
{
  PrsMgr_Presentations& aPresentations = thePresentableObject->Presentations();
  for (Standard_Integer aIdx = 1; aIdx <= aPresentations.Length (); aIdx++)
  {
    Handle(PrsMgr_Presentation) aPrs = aPresentations (aIdx).Presentation ();
    if (aPrs->PresentationManager () == this)
      return aPrs->GetZLayer ();
  }
  
  return -1;
}
