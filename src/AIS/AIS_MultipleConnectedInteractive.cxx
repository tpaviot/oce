// Created on: 1997-04-22
// Created by: Guest Design
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

//		<g_design>


#include <Standard_NotImplemented.hxx>

#include <AIS_MultipleConnectedInteractive.ixx>

#include <PrsMgr_ModedPresentation.hxx>
#include <PrsMgr_Presentation3d.hxx>

static Standard_Boolean IsInSeq (const AIS_SequenceOfInteractive&      theSeq,
				 const Handle(AIS_InteractiveObject)&  theItem) 
{
  Standard_Integer I = theSeq.Length();
  while ( I>0 && theSeq.Value(I) != theItem) {    
    I--;
  }
  return (I>0);
}

static Standard_Integer RangeInSeq (const AIS_SequenceOfInteractive& theSeq ,
				    const Handle(AIS_InteractiveObject)&     theItem) 
{
  Standard_Integer I = theSeq.Length();
  while ( I>0 && theSeq.Value(I) != theItem) {    
    I--;
  }
  return I;
}


//=======================================================================
//function : AIS_MultipleConnectedInteractive
//purpose  : 
//=======================================================================

AIS_MultipleConnectedInteractive::AIS_MultipleConnectedInteractive
(const PrsMgr_TypeOfPresentation3d aTypeOfPresentation3d):
AIS_InteractiveObject(aTypeOfPresentation3d)
{    
  SetHilightMode(0);
}

//=======================================================================
//function : Type
//purpose  : 
//=======================================================================
AIS_KindOfInteractive AIS_MultipleConnectedInteractive::Type() const
{return AIS_KOI_Object;}

//=======================================================================
//function : Signature
//purpose  : 
//=======================================================================
Standard_Integer AIS_MultipleConnectedInteractive::Signature() const
{return 1;}

//=======================================================================
//function : Connect
//purpose  : 
//=======================================================================
void AIS_MultipleConnectedInteractive::Connect(const Handle(AIS_InteractiveObject)& anotherIObj)
{

  if (!IsInSeq (myReferences, anotherIObj)) {
    myReferences.Append(anotherIObj);
  }
}

//=======================================================================
//function : HasConnection
//purpose  : 
//=======================================================================
Standard_Boolean AIS_MultipleConnectedInteractive::HasConnection() const 
{
  return (!myReferences.Length()==0);
}

//=======================================================================
//function : Disconnect
//purpose  : 
//=======================================================================

void AIS_MultipleConnectedInteractive::Disconnect(const Handle(AIS_InteractiveObject)& anotherIObj)
{
  Standard_Integer I = RangeInSeq (myReferences, anotherIObj);
  if (I != 0) {
    myReferences.Remove(I);
    
  }
}

//=======================================================================
//function : DisconnectAll
//purpose  : 
//=======================================================================

void AIS_MultipleConnectedInteractive::DisconnectAll ()
{
/*  for(Standard_Integer i =1;i<=myPresentations.Length();i++)
    {
      Handle(PrsMgr_Presentation3d) P = Handle(PrsMgr_Presentation3d)::DownCast(myPresentations(i).Presentation());
      if(!P.IsNull()) {
	P->Presentation()->DisconnectAll(Graphic3d_TOC_DESCENDANT);
      }
    }*/
  myPreviousReferences = myReferences; // pour garder les poignees au chaud!!!!
  myReferences.Clear();
}

//=======================================================================
//function : Compute
//purpose  : 
//=======================================================================

void AIS_MultipleConnectedInteractive::Compute
(const Handle(PrsMgr_PresentationManager3d)& aPresentationManager, 
 const Handle(Prs3d_Presentation)& aPresentation, 
 const Standard_Integer aMode)

{
  //cout<<"AIS_MultipleConnectedInteractive::Compute"<<endl;

  aPresentation->Clear(Standard_False);
  aPresentation->RemoveAll();
  if(HasConnection()) {
    for (Standard_Integer I=1 ; I<= myReferences.Length(); I++) {
      const Handle (AIS_InteractiveObject)& aReference = myReferences.Value (I);
      aPresentationManager->Connect( this, aReference, aMode, aMode);
      if(aPresentationManager->Presentation(aReference,aMode)->MustBeUpdated())
	aPresentationManager->Update(aReference,aMode);
    }
  }

  aPresentation->ReCompute();

}
   
//=======================================================================
//function : Compute
//purpose  : 
//=======================================================================

void AIS_MultipleConnectedInteractive::Compute(const Handle_Prs3d_Projector& aProjector,
                                               const Handle_Prs3d_Presentation& aPresentation)
{
// Standard_NotImplemented::Raise("AIS_MultipleConnectedInteractive::Compute(const Handle_Prs3d_Projector&, const Handle_Prs3d_Presentation&)");
 PrsMgr_PresentableObject::Compute( aProjector , aPresentation ) ;
}

//=======================================================================
//function : Compute
//purpose  : 
//=======================================================================

void AIS_MultipleConnectedInteractive::Compute(const Handle_PrsMgr_PresentationManager2d& aPresentationManager2d,
                                               const Handle_Graphic2d_GraphicObject& aGraphicObject,
                                               const int anInteger)
{
// Standard_NotImplemented::Raise("AIS_MultipleConnectedInteractive::Compute(const Handle_PrsMgr_PresentationManager2d&, const Handle_Graphic2d_GraphicObject&, const int)");
 PrsMgr_PresentableObject::Compute( aPresentationManager2d ,aGraphicObject,anInteger) ;
}

//=======================================================================
//function : Compute
//purpose  : 
//=======================================================================

void AIS_MultipleConnectedInteractive::Compute(const Handle_Prs3d_Projector& aProjector,
                                               const Handle_Geom_Transformation& aTransformation,
                                               const Handle_Prs3d_Presentation& aPresentation)
{
// Standard_NotImplemented::Raise("AIS_MultipleConnectedInteractive::Compute(const Handle_Prs3d_Projector&, const Handle_Geom_Transformation&, const Handle_Prs3d_Presentation&)");
 PrsMgr_PresentableObject::Compute( aProjector , aTransformation , aPresentation ) ;
}

//=======================================================================
//function : ComputeSelection
//purpose  : 
//=======================================================================
void AIS_MultipleConnectedInteractive::ComputeSelection(const Handle(SelectMgr_Selection)& /*aSel*/,
                                                        const Standard_Integer /*aMode*/)
{
}
