// Created on: 1998-09-23
// Created by: Denis PASCAL
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



#include <DDataStd_DrawPresentation.ixx>
#include <Draw_Drawable3D.hxx>
#include <Draw.hxx>
#include <Draw_Viewer.hxx>
#include <TDF_DefaultDeltaOnModification.hxx>
#include <TDF_DefaultDeltaOnRemoval.hxx>
#include <TDF_DeltaOnAddition.hxx>
#include <TDF_Tool.hxx>
#include <DDataStd_DrawDriver.hxx>

#ifndef WNT
extern Draw_Viewer dout;
#else
Standard_IMPORT Draw_Viewer dout;
#endif
//=======================================================================
//function : IsDisplayed
//purpose  : 
//=======================================================================

Standard_Boolean DDataStd_DrawPresentation::IsDisplayed (const TDF_Label& L)
{  
  Handle(DDataStd_DrawPresentation) P; 
  if (L.FindAttribute(DDataStd_DrawPresentation::GetID(),P)) {
    return P->IsDisplayed();
  }
  return Standard_False;
}


//=======================================================================
//function : HasPresentation
//purpose  : 
//=======================================================================

Standard_Boolean DDataStd_DrawPresentation::HasPresentation (const TDF_Label& L)
{
  return (L.IsAttribute(DDataStd_DrawPresentation::GetID()));
}

//=======================================================================
//function : Display
//purpose  : 
//=======================================================================

void DDataStd_DrawPresentation::Display (const TDF_Label& L)
{  
  Handle(DDataStd_DrawPresentation) P;
  // set
  if (!L.FindAttribute(DDataStd_DrawPresentation::GetID(),P)) {
    P = new DDataStd_DrawPresentation ();  
    L.AddAttribute(P);
  } 
  // display
  if (P->IsDisplayed()) return;
  if (P->GetDrawable().IsNull()) P->DrawBuild();  
  DrawDisplay (P->Label(),P);
  P->SetDisplayed(Standard_True);
}

//=======================================================================
//function : Erase
//purpose  : 
//=======================================================================

void DDataStd_DrawPresentation::Erase(const TDF_Label& L)
{  
  Handle(DDataStd_DrawPresentation) P;
  if (L.FindAttribute(DDataStd_DrawPresentation::GetID(),P)) {
    if (P->IsDisplayed()) {
      DrawErase (P->Label(),P);
      P->SetDisplayed(Standard_False);
    }  
  }
}

//=======================================================================
//function : Update
//purpose  : 
//=======================================================================

void  DDataStd_DrawPresentation::Update (const TDF_Label& L)
{
  Handle(DDataStd_DrawPresentation) P;
  if (L.FindAttribute(DDataStd_DrawPresentation::GetID(),P)) {   
    DrawErase(P->Label(),P);
    P->Backup();
    P->DrawBuild(); 
    DrawDisplay (P->Label(),P);
    P->SetDisplayed(Standard_True);
  }
}

//=======================================================================
//function : GetID
//purpose  : idem GUID DDataStd Display
//=======================================================================

const Standard_GUID& DDataStd_DrawPresentation::GetID() 
{
  static Standard_GUID DDataStd_DrawPresentationID("1c0296d4-6dbc-22d4-b9c8-0070b0ee301b");
  return DDataStd_DrawPresentationID;
}


//=======================================================================
//function : DDataStd_DrawPresentation
//purpose  : 
//=======================================================================

DDataStd_DrawPresentation::DDataStd_DrawPresentation () : isDisplayed(Standard_False) {}


//=======================================================================
//function : SetDisplayed
//purpose  : 
//=======================================================================

void DDataStd_DrawPresentation::SetDisplayed (const Standard_Boolean status)
{ 
  isDisplayed = status;
}

//=======================================================================
//function : IsDisplayed
//purpose  : 
//=======================================================================

Standard_Boolean DDataStd_DrawPresentation::IsDisplayed () const
{ 
  return isDisplayed;
}

//=======================================================================
//function : SetDrawable
//purpose  : 
//=======================================================================

void DDataStd_DrawPresentation::SetDrawable (const Handle(Draw_Drawable3D)& D)
{ 
  myDrawable = D;
}

//=======================================================================
//function : GetDrawable
//purpose  : 
//=======================================================================

Handle(Draw_Drawable3D) DDataStd_DrawPresentation::GetDrawable () const
{ 
  return myDrawable;
}

//=======================================================================
//function : ID
//purpose  : 
//=======================================================================

const Standard_GUID& DDataStd_DrawPresentation::ID() const { return GetID(); }


//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================

Handle(TDF_Attribute) DDataStd_DrawPresentation::NewEmpty() const
{ 
  return new DDataStd_DrawPresentation ();
}

//=======================================================================
//function : Restore
//purpose  : 
//=======================================================================

void DDataStd_DrawPresentation::Restore (const Handle(TDF_Attribute)& With) 
{  
  //cout<< "DDataStd_DrawPresentation::Restore" << endl; 
  isDisplayed = Handle(DDataStd_DrawPresentation)::DownCast (With)->IsDisplayed();
  myDrawable  = Handle(DDataStd_DrawPresentation)::DownCast (With)->GetDrawable();
}

//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================

void DDataStd_DrawPresentation::Paste (const Handle(TDF_Attribute)& Into,
				       const Handle(TDF_RelocationTable)& RT) const
{   
  //cout<< "DDataStd_DrawPresentation::Paste" << endl;  
  Handle(DDataStd_DrawPresentation)::DownCast(Into)->SetDisplayed(isDisplayed);  
  Handle(DDataStd_DrawPresentation)::DownCast(Into)->SetDrawable(myDrawable);
}

//=======================================================================
//function : AfterAddition
//purpose  : erase if displayed
//=======================================================================

void DDataStd_DrawPresentation::AfterAddition() 
{ 
  //cout<< "DDataStd_DrawPresentation::AfterAddition" << endl; 
  //if (isDisplayed)  DrawDisplay ();
}

//=======================================================================
//function : BeforeRemoval
//purpose  : erase if displayed
//=======================================================================

void DDataStd_DrawPresentation::BeforeRemoval() 
{ 
  //cout<< "DDataStd_DrawPresentation::BeforeRemoval" << endl; 
  //if (isDisplayed)  DrawErase ();
}

//=======================================================================
//function : BeforeForget
//purpose  : erase if displayed
//=======================================================================

void DDataStd_DrawPresentation::BeforeForget() 
{ 
  //cout<< "DDataStd_DrawPresentation::BeforeForget" << endl; 
  if (isDisplayed)  DrawErase (Label(),this);
}


//=======================================================================
//function : AfterResume
//purpose  : display if displayed
//=======================================================================

void DDataStd_DrawPresentation::AfterResume() 
{
  //cout<< "DDataStd_DrawPresentation::AfterResume"<< endl;
  if (isDisplayed) DrawDisplay (Label(),this);
}

//=======================================================================
//function : BeforeUndo
//purpose  : the associated NamedShape should be present
//=======================================================================

Standard_Boolean DDataStd_DrawPresentation::BeforeUndo (const Handle(TDF_AttributeDelta)& AD,
 							const Standard_Boolean forceIt) 
{
  Handle(DDataStd_DrawPresentation) Pme = this;
  Handle(DDataStd_DrawPresentation) Pdt = Handle(DDataStd_DrawPresentation)::DownCast(AD->Attribute());   
  Handle(DDataStd_DrawPresentation) Pfw;
  if (AD->Label().FindAttribute(GetID(),Pfw)) {  
    //cout<< "DDataStd_DrawPresentation::BeforeUndo : attribute in framework" << endl;
  }
  else  {
    //cout<< "DDataStd_DrawPresentation::BeforeUndo : attribute not in framework" << endl;
  }
  //
  if (AD->IsKind(STANDARD_TYPE(TDF_DeltaOnAddition))) {    
    //cout<< "DDataStd_DrawPresentation::BeforeUndo : delta on addition" << endl;
    if (Pfw->IsDisplayed())  DrawErase(AD->Label(),Pfw);
    //TDF appelle BeforeRemoval effacer
  }
  else if (AD->IsKind(STANDARD_TYPE(TDF_DefaultDeltaOnRemoval))) { 
    //cout<< "DDataStd_DrawPresentation::BeforeUndo : delta on removal" << endl; 
  }  
  else if (AD->IsKind(STANDARD_TYPE(TDF_DefaultDeltaOnModification))) {     
    //cout<< "DDataStd_DrawPresentation::BeforeUndo : delta on modification" << endl; 
    if (Pfw->IsDisplayed()) DrawErase(AD->Label(),Pfw);
  } 
  else {  
    //cout<< "DDataStd_DrawPresentation::BeforeUndo : unknown delta" << endl;
  }  
  //if (Label().IsNull()) cout<< "DDataStd_DrawPresentation::BeforeUndo : null label" << endl;      
  return Standard_True;
}


//=======================================================================
//function : AfterUndo
//purpose  : associated NamedShape should be present
//=======================================================================

Standard_Boolean DDataStd_DrawPresentation::AfterUndo (const Handle(TDF_AttributeDelta)& AD,
						       const Standard_Boolean forceIt) 
{   
  Handle(DDataStd_DrawPresentation) Pme = this;
  Handle(DDataStd_DrawPresentation) Pdt = Handle(DDataStd_DrawPresentation)::DownCast(AD->Attribute());   
  Handle(DDataStd_DrawPresentation) Pfw;
  if (AD->Label().FindAttribute(GetID(),Pfw)) {  
    //cout<< "DDataStd_DrawPresentation::AfterUndo : attribute in framework" << endl;
  }
  else  {
    //cout<< "DDataStd_DrawPresentation::AfterUndo : attribute not in framework" << endl;
  }
  
  //
  if (AD->IsKind(STANDARD_TYPE(TDF_DeltaOnAddition))) {
    //cout<< "DDataStd_DrawPresentation::AfterUndo : delta on addition" << endl;
  }
  else if (AD->IsKind(STANDARD_TYPE(TDF_DefaultDeltaOnRemoval))) {  
    //cout<< "DDataStd_DrawPresentation::AfterUndo : delta on removal" << endl;  
    if (Pdt->IsDisplayed()) DrawDisplay(AD->Label(),Pdt); 
  }  
  else if (AD->IsKind(STANDARD_TYPE(TDF_DefaultDeltaOnModification))) {     
    //cout<< "DDataStd_DrawPresentation::AfterUndo : delta on modification" << endl;
    if (Pdt->IsDisplayed()) DrawDisplay(AD->Label(),Pdt);
  }
  else {
    //cout<< "DDataStd_DrawPresentation::AfterUndo : unknown delta" << endl;  
  }  
  //if (Label().IsNull()) cout<< "DDataStd_DrawPresentation::AfterUndo : null label" << endl;   
  return Standard_True;
}



//=======================================================================
//function : DrawBuild
//purpose  : 
//=======================================================================

void DDataStd_DrawPresentation::DrawBuild ()
{   
  //cout<< "DDataStd_DrawPresentation::DrawBuild" << endl;     
  Handle(DDataStd_DrawDriver) DD = DDataStd_DrawDriver::Get();
  if (DD.IsNull()) {
    DD = new DDataStd_DrawDriver ();
    DDataStd_DrawDriver::Set(DD);
  }
  Handle(Draw_Drawable3D) D3D = DD->Drawable(Label()); 
  if (D3D.IsNull()) cout<< "DDataStd_DrawPresentation::DrawBuild : null drawable" << endl;
  myDrawable = D3D;
}



//=======================================================================
//function : DrawDisplay
//purpose  : 
//=======================================================================

void DDataStd_DrawPresentation::DrawDisplay (const TDF_Label& L,
					     const Handle(DDataStd_DrawPresentation)& P)
{     
  if (!L.IsNull()) {     
    if (!P->GetDrawable().IsNull()) {
      TCollection_AsciiString S;
      TDF_Tool::Entry(L,S);
      Standard_CString name = S.ToCString();
      Draw::Set(name,P->GetDrawable());
      return;
    }
    else {    
      //cout<< "DDataStd_DrawPresentation::DrawDisplay : null Drawable" << endl;
      return;
    }
  }
  cout<< "DDataStd_DrawPresentation::DrawDisplay : null Label" << endl;
}

//=======================================================================
//function : DrawErase
//purpose  : 
//=======================================================================

void DDataStd_DrawPresentation::DrawErase (const TDF_Label& L,
					   const Handle(DDataStd_DrawPresentation)& P)
{    
  if (!L.IsNull()) {   
    if (!P->GetDrawable().IsNull()) {
      dout.RemoveDrawable(P->GetDrawable());
      return;
    }    
    else {
      //cout<< "DDataStd_DrawPresentation::DrawErase : null Drawable" << endl;
      return;
    }
  }
  cout<< "DDataStd_DrawPresentation::DrawErase : null Label" << endl;
}




