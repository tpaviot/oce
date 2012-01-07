// Copyright:   Matra-Datavision 1995
// File:        SelectMgr_SelectableObject.cxx
// Created:     Mon Feb 20 17:40:49 1995
// Author:      Mister rmi
//              <rmi>



#include <Standard_NotImplemented.hxx>

#include <SelectMgr_SelectableObject.ixx>
#include <Standard_NoSuchObject.hxx>
#include <SelectMgr_Selection.hxx>
#include <Select3D_SensitiveEntity.hxx>
#include <SelectBasics_EntityOwner.hxx>
#include <SelectMgr_EntityOwner.hxx>
#include <PrsMgr_PresentationManager3d.hxx>

#include <gp_Pnt.hxx>

static Standard_Integer Search (const SelectMgr_SequenceOfSelection& seq,
                                const Handle (SelectMgr_Selection)& theSel)
{
  Standard_Integer ifound=0;
  for (Standard_Integer i=1;i<=seq.Length()&& ifound==0;i++)
    {if(theSel == seq.Value(i)) ifound=i;}
  return ifound;
} 



//==================================================
// Function: 
// Purpose :
//==================================================

SelectMgr_SelectableObject::SelectMgr_SelectableObject( const PrsMgr_TypeOfPresentation3d aTypeOfPresentation3d):PrsMgr_PresentableObject(aTypeOfPresentation3d)
{
  myAutoHilight = Standard_True;
}


//==================================================
// Function: 
// Purpose :
//==================================================

Standard_Boolean SelectMgr_SelectableObject
::HasSelection(const Standard_Integer aMode) const
{
  Standard_Boolean Found=Standard_False;
  for (Standard_Integer I=1;I<= myselections.Length() && !Found;I++)
    { if(((myselections.Value(I))->Mode())==aMode) 
        return Standard_True;
    }
  return Standard_False;
}

//==================================================
// Function: UpdateSelection
// Purpose :
//==================================================
void SelectMgr_SelectableObject::UpdateSelection()
{
  for (Standard_Integer I=1;I<=myselections.Length();I++)
    {
      UpdateSelection(myselections.ChangeValue(I)->Mode());
    }
}

Standard_Integer  SelectMgr_SelectableObject::NbPossibleSelection() const
{return 0;}

//==================================================
// Function: UpdateSelection
// Purpose :
//==================================================
void SelectMgr_SelectableObject::UpdateSelection(const Standard_Integer aMode)
{
  for (Standard_Integer i =1; i<= myselections.Length(); i++ ) {
    if (myselections.Value(i)->Mode() == aMode) {
      myselections(i)->Clear();
      ComputeSelection(myselections(i),aMode);
      myselections(i)->UpdateStatus(SelectMgr_TOU_Partial);
      return;
    }
  }
  Handle(SelectMgr_Selection) S = new SelectMgr_Selection(aMode);
  ComputeSelection(S,aMode);
  S->UpdateStatus(SelectMgr_TOU_Partial);
  
  myselections.Append(S);
  
}

//==================================================
// Function: ClearSelections
// Purpose :
//==================================================
void SelectMgr_SelectableObject::ClearSelections(const Standard_Boolean update)
{
  for (Standard_Integer i =1; i<= myselections.Length(); i++ ) {
    myselections.Value(i)->Clear();
    if(update)
      myselections.Value(i)->UpdateStatus(SelectMgr_TOU_Full);
  }
}


//==================================================
// Function: Selection
// Purpose :
//==================================================

const Handle(SelectMgr_Selection)& SelectMgr_SelectableObject
::Selection(const Standard_Integer aMode) const
{
  static Handle(SelectMgr_Selection) bidsel;
  Standard_Boolean Found = Standard_False;
  Standard_Integer Rank=0;
  for (Standard_Integer i=1;i<=myselections.Length() && !Found;i++)
    {
      if((myselections.Value(i))->Mode()==aMode){ Found = Standard_True;
                                                  Rank=i;}}
  return myselections.Value(Rank);
}


//==================================================
// Function: AddSelection
// Purpose :
//==================================================

void SelectMgr_SelectableObject
::AddSelection(const Handle(SelectMgr_Selection)& aSel,
               const Standard_Integer aMode)
{
  if(aSel->IsEmpty()){
    ComputeSelection(aSel,aMode);
    aSel->UpdateStatus(SelectMgr_TOU_Partial);
  }
  if(HasSelection(aMode))
    {
      const Handle(SelectMgr_Selection)& temp= Selection(aMode);
      Standard_Integer I = Search(myselections,temp);
      if(I!=0) myselections.Remove(I);
    }
  myselections.Append(aSel);
  
}



//=======================================================================
//function : ReSetLocation
//purpose  : 
//=======================================================================
void SelectMgr_SelectableObject::ResetLocation() 
{
  TopLoc_Location aLoc;


  // les selections
  Handle(Select3D_SensitiveEntity) SE;
  for(Init();More();Next()){
    const Handle(SelectMgr_Selection) & Sel =  CurrentSelection();
    for(Sel->Init();Sel->More();Sel->Next()){
      SE =  *((Handle(Select3D_SensitiveEntity)*) &(Sel->Sensitive()));
      if(!SE.IsNull()){
        if(SE->HasLocation()) {
          if( SE->Location()==myLocation){
            SE->ResetLocation();
            const Handle(SelectBasics_EntityOwner)& EO = SE->OwnerId();
            (*((Handle(SelectMgr_EntityOwner)*)&EO))->ResetLocation();}
          else{
            const TopLoc_Location& iniloc =SE->Location();
            SE->SetLocation(iniloc*myLocation.Inverted());
            const Handle(SelectBasics_EntityOwner)& EO = SE->OwnerId();
            (*((Handle(SelectMgr_EntityOwner)*)&EO))->SetLocation(SE->Location());}
        }
      }
    }
    Sel->UpdateStatus(SelectMgr_TOU_None);
  }

  PrsMgr_PresentableObject::ResetLocation();
}


//=======================================================================
//function : UpdateLocation
//purpose  : 
//=======================================================================
void SelectMgr_SelectableObject::UpdateLocation() 
{
  
  Handle(Select3D_SensitiveEntity) SE;
  for(Init();More();Next()){
    const Handle(SelectMgr_Selection) & Sel =  CurrentSelection();
    Sel->UpdateStatus(SelectMgr_TOU_Partial);
  }
  PrsMgr_PresentableObject::UpdateLocation();

}


//=======================================================================
//function : UpdateLocation
//purpose  : 
//=======================================================================
void SelectMgr_SelectableObject::UpdateLocation(const Handle(SelectMgr_Selection)& Sel)
{
  Handle(Select3D_SensitiveEntity) SE;
  if(myLocation.IsIdentity()) return;
  for(Sel->Init();Sel->More();Sel->Next()){
    SE =  *((Handle(Select3D_SensitiveEntity)*) &(Sel->Sensitive()));
    if(!SE.IsNull()){
      SE->UpdateLocation(myLocation);
    }
  }
}

//=======================================================================
//function : HilightSelected
//purpose  : 
//=======================================================================
void SelectMgr_SelectableObject::HilightSelected 
  ( const Handle(PrsMgr_PresentationManager3d)&,
    const SelectMgr_SequenceOfOwner&)
{
  Standard_NotImplemented::Raise ("SelectMgr_SelectableObject::HilightSelected");
}

//=======================================================================
//function : ClearSelected
//purpose  : 
//=======================================================================
void SelectMgr_SelectableObject::ClearSelected ()
{
  //Standard_NotImplemented::Raise ("SelectMgr_SelectableObject::HilightOwnerWithColor");
  if( !mySelectionPrs.IsNull() )
    mySelectionPrs->Clear();  
}

//=======================================================================
//function : HilightOwnerWithColor
//purpose  : 
//=======================================================================
void SelectMgr_SelectableObject::HilightOwnerWithColor 
  ( const Handle(PrsMgr_PresentationManager3d)&,
    const Quantity_NameOfColor,
    const Handle(SelectMgr_EntityOwner)&)
{
  Standard_NotImplemented::Raise ("SelectMgr_SelectableObject::HilightOwnerWithColor");
}

//=======================================================================
//function : MaxFaceNodes
//purpose  : 
//=======================================================================
Standard_Boolean SelectMgr_SelectableObject::IsAutoHilight () const
{
  return myAutoHilight;
}

//=======================================================================
//function : MaxFaceNodes
//purpose  : 
//=======================================================================
void SelectMgr_SelectableObject::SetAutoHilight ( const Standard_Boolean newAutoHilight )
{
  myAutoHilight = newAutoHilight;
}

//=======================================================================
//function : GetHilightPresentation
//purpose  : 
//=======================================================================
Handle(Prs3d_Presentation) SelectMgr_SelectableObject::GetHilightPresentation( const Handle(PrsMgr_PresentationManager3d)& TheMgr )
{
  if( myHilightPrs.IsNull() && !TheMgr.IsNull() )
    {
      myHilightPrs = new Prs3d_Presentation( TheMgr->StructureManager() );
      myHilightPrs->SetTransformPersistence( GetTransformPersistenceMode(), 
					 GetTransformPersistencePoint() );
    }

  return myHilightPrs;
}


//=======================================================================
//function : GetSelectPresentation
//purpose  : 
//=======================================================================
Handle(Prs3d_Presentation) SelectMgr_SelectableObject::GetSelectPresentation( const Handle(PrsMgr_PresentationManager3d)& TheMgr )
{
  if( mySelectionPrs.IsNull() && !TheMgr.IsNull() ) {
    mySelectionPrs = new Prs3d_Presentation( TheMgr->StructureManager() );
    mySelectionPrs->SetTransformPersistence( GetTransformPersistenceMode(), 
					     GetTransformPersistencePoint() );
  }
  return mySelectionPrs;
}

