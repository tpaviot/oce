// Created on: 1998-09-30
// Created by: Sergey RUIN
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




// Lastly modified by :
// +---------------------------------------------------------------------------+
// !      ivan ! SetMode                                 ! 5-04-2001! 3.0-00-1!
// +---------------------------------------------------------------------------+
#include <TPrsStd_AISPresentation.ixx>

#include <TDF_DefaultDeltaOnRemoval.hxx>
#include <TDF_DefaultDeltaOnModification.hxx>
#include <TDF_DeltaOnAddition.hxx>
#include <TDF_Tool.hxx>
#include <TCollection_ExtendedString.hxx>
#include <TPrsStd_AISViewer.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>
#include <TPrsStd_Driver.hxx>
#include <TPrsStd_DriverTable.hxx>


#define BUC60917
#define BUC61050

#define OCC1029
#define OCC1030
#define OCC1031
#define OCC1032
#define OCC1033
#define OCC1034

//=======================================================================
//function : Set
//purpose  : 
//=======================================================================
Handle(TPrsStd_AISPresentation) TPrsStd_AISPresentation::Set(const TDF_Label& L,const Standard_GUID& driver) 
{   

  Handle(TPrsStd_AISPresentation) P; 

  if (!L.FindAttribute(TPrsStd_AISPresentation::GetID(),P)) { 
    P = new TPrsStd_AISPresentation ();  
    L.AddAttribute(P);
  }
  P->SetDriverGUID(driver);   
  return P;
}


//=======================================================================
//function : Unset
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::Unset (const TDF_Label& L)
{   
  Handle(TPrsStd_AISPresentation) P;  

  if (L.FindAttribute(TPrsStd_AISPresentation::GetID(),P)) { 
    L.ForgetAttribute(P);
  }
}


//=======================================================================
//function : Set
//purpose  : 
//=======================================================================
Handle(TPrsStd_AISPresentation) TPrsStd_AISPresentation::Set (const Handle(TDF_Attribute)& master) 
{  
  Handle(TPrsStd_AISPresentation) P;  

  if (!master->Label().FindAttribute(TPrsStd_AISPresentation::GetID(),P)) { 
    P = new TPrsStd_AISPresentation ();  
    master->Label().AddAttribute(P);
  }   

  P->SetDriverGUID( master->ID() );

  return P;
}




//=======================================================================
//function : GetID
//purpose  : 
//=======================================================================
const Standard_GUID& TPrsStd_AISPresentation::GetID() 
{
  static Standard_GUID TPrsStd_AISPresentationID("04fb4d00-5690-11d1-8940-080009dc3333");
  return TPrsStd_AISPresentationID;
}


//=======================================================================
//function : TPrsStd_AISPresentation
//purpose  : 
//=======================================================================
TPrsStd_AISPresentation::TPrsStd_AISPresentation () : 
myDriverGUID("00000000-0000-0000-0000-000000000000"),
myTransparency(0.),
myColor(Quantity_NOC_WHITE),
myMaterial(Graphic3d_NOM_BRASS),
myWidth(0.),
#ifdef BUC61050
myMode(0),
mySelectionMode(0),
#endif
isDisplayed(Standard_False),
hasOwnColor(Standard_False),
hasOwnMaterial(Standard_False),
hasOwnTransparency(Standard_False),
hasOwnWidth(Standard_False)
#ifdef BUC61050
,hasOwnMode(Standard_False),
hasOwnSelectionMode(Standard_False)
#endif
{}


//=======================================================================
//function : Display
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::Display (const Standard_Boolean update)
{
   
  if( update || myAIS.IsNull() ) {
    AISUpdate();
  }
  AISDisplay();     
}


//=======================================================================
//function : Erase
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::Erase (const Standard_Boolean remove)
{  
  if( isDisplayed ) AISErase(remove);   
}

//=======================================================================
//function : Update
//purpose  : 
//=======================================================================
void  TPrsStd_AISPresentation::Update ()
{  
  AISUpdate();
}


//=======================================================================
//function : IsDisplayed
//purpose  : 
//=======================================================================
Standard_Boolean TPrsStd_AISPresentation::IsDisplayed () const
{
  return isDisplayed;
}


//=======================================================================
//function :SetDriverGUID
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::SetDriverGUID(const Standard_GUID& guid) 
{
  // OCC2932 correction
  if(myDriverGUID == guid) return;

  Backup(); 
  myDriverGUID = guid;
}


//=======================================================================
//function :GetDriverGUID
//purpose  : 
//=======================================================================
Standard_GUID TPrsStd_AISPresentation::GetDriverGUID() const
{
  return myDriverGUID;
}


//=======================================================================
//function :Material
//purpose  : 
//=======================================================================
Graphic3d_NameOfMaterial TPrsStd_AISPresentation::Material() const
{
  return myMaterial; 
}

//=======================================================================
//function :HasMaterial
//purpose  : 
//=======================================================================
Standard_Boolean TPrsStd_AISPresentation::HasOwnMaterial() const
{
  return hasOwnMaterial;
}

//=======================================================================
//function :UnsetMaterial
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::UnsetMaterial()
{
  // OCC2932 correction
  if(hasOwnMaterial == Standard_False && !myAIS.IsNull()) {
      if(!myAIS->HasMaterial())
	return;
  }
    
  Backup();
  hasOwnMaterial = Standard_False;
  if( myAIS.IsNull() ) AISUpdate();
  if( !myAIS.IsNull() &&  myAIS->HasMaterial() ) {
    Handle(AIS_InteractiveContext) ctx;
    Handle(TPrsStd_AISViewer) viewer;
    if( TPrsStd_AISViewer::Find(Label(), viewer) ) ctx = viewer->GetInteractiveContext(); 
    if( !ctx.IsNull() )   
      ctx->UnsetMaterial(myAIS, Standard_False);
    else  
      myAIS->UnsetMaterial();
  }
}

//=======================================================================
//function :SetMaterial
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::SetMaterial(const Graphic3d_NameOfMaterial aName) 
{
  // OCC2932 correction
  if(myMaterial == aName && hasOwnMaterial == Standard_True && !myAIS.IsNull()) {
      if(myAIS->HasMaterial() && myAIS->Material() == aName)
	return;
  }

  Backup();
  myMaterial = aName;
  hasOwnMaterial = Standard_True;
  if( myAIS.IsNull() ) AISUpdate();
  if( !myAIS.IsNull() ) { 
    if( myAIS->HasMaterial() && myAIS->Material() == aName ) return;   // AIS has already had that material     
    Handle(AIS_InteractiveContext) ctx;
    Handle(TPrsStd_AISViewer) viewer;
    if( TPrsStd_AISViewer::Find(Label(), viewer) ) ctx = viewer->GetInteractiveContext(); 
    if( !ctx.IsNull() )   
      ctx->SetMaterial(myAIS, aName,  Standard_False);
    else  
      myAIS->SetMaterial(aName);
  }
}


//=======================================================================
//function :SetTransparency
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::SetTransparency(const Standard_Real aValue) 
{
  // OCC2932 correction
  if(hasOwnTransparency == Standard_True && myTransparency == aValue && !myAIS.IsNull())
      if(myAIS->Transparency() == aValue)
	return;

  Backup();
  myTransparency = aValue;
  hasOwnTransparency = Standard_True;
  if( myAIS.IsNull() ) AISUpdate(); 
  if( !myAIS.IsNull() ) { 
    if( myAIS->Transparency() == aValue ) return;   // AIS has already had that transparency 
    Handle(AIS_InteractiveContext) ctx;
    Handle(TPrsStd_AISViewer) viewer;
    if( TPrsStd_AISViewer::Find(Label(), viewer) ) ctx = viewer->GetInteractiveContext();
    if( !ctx.IsNull() )  
      ctx->SetTransparency(myAIS, aValue, Standard_False);
    else 
      myAIS->SetTransparency(aValue);
  }
}


//=======================================================================
//function :Transparency
//purpose  : 
//=======================================================================
Standard_Real TPrsStd_AISPresentation::Transparency() const
{
  return myTransparency;
}

//=======================================================================
//function :UnsetTransparency
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::UnsetTransparency()
{
  // OCC2932 correction
  if(!hasOwnTransparency)
    return;

  Backup(); 
  hasOwnTransparency = Standard_False;
  if( myAIS.IsNull() ) AISUpdate();
  if( !myAIS.IsNull() ) {
    Handle(AIS_InteractiveContext) ctx;
    Handle(TPrsStd_AISViewer) viewer;
    if( TPrsStd_AISViewer::Find(Label(), viewer) ) ctx = viewer->GetInteractiveContext(); 
    if( !ctx.IsNull() )   
      ctx->UnsetTransparency(myAIS, Standard_False);
    else  
      myAIS->UnsetTransparency();
  }
}

//=======================================================================
//function :HasTransparency
//purpose  : 
//=======================================================================
Standard_Boolean TPrsStd_AISPresentation::HasOwnTransparency() const
{
  return hasOwnTransparency;
}

//=======================================================================
//function :Color
//purpose  : 
//=======================================================================
Quantity_NameOfColor TPrsStd_AISPresentation::Color() const
{
  return myColor;
}

//=======================================================================
//function :HasColor
//purpose  : 
//=======================================================================
Standard_Boolean TPrsStd_AISPresentation::HasOwnColor() const
{
  return hasOwnColor;
}

//=======================================================================
//function :UnsetColor
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::UnsetColor()
{
  // OCC2932 correction
  if(!hasOwnColor && !myAIS.IsNull()) 
      if(!myAIS->HasColor())
	return;
  
  Backup();
  hasOwnColor = Standard_False;
  if( myAIS.IsNull() ) AISUpdate();
  if( !myAIS.IsNull() &&  myAIS->HasColor() ) {
    Handle(AIS_InteractiveContext) ctx;
    Handle(TPrsStd_AISViewer) viewer;
    if( TPrsStd_AISViewer::Find(Label(), viewer) ) ctx = viewer->GetInteractiveContext(); 
    if( !ctx.IsNull() )   
      ctx->UnsetColor(myAIS, Standard_False);
    else  
      myAIS->UnsetColor();
  }
}

//=======================================================================
//function :SetColor
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::SetColor(const Quantity_NameOfColor aColor) 
{
  // OCC2932 correction
  if(hasOwnColor && myColor == aColor && ! myAIS.IsNull()) 
    if(myAIS->HasColor() && myAIS->Color() == aColor ) 
      return;
  
  Backup();
  myColor = aColor;
  hasOwnColor = Standard_True;
  if( myAIS.IsNull() ) AISUpdate();
  if( !myAIS.IsNull() ) {
    if( myAIS->HasColor() && myAIS->Color() == aColor ) return;   // AIS has already had that color     
    Handle(AIS_InteractiveContext) ctx;
    Handle(TPrsStd_AISViewer) viewer;
    if( TPrsStd_AISViewer::Find(Label(), viewer) ) ctx = viewer->GetInteractiveContext();
    if( !ctx.IsNull() )  
      ctx->SetColor(myAIS, aColor, Standard_False);
    else 
      myAIS->SetColor(aColor);
  }
}


//=======================================================================
//function :Width
//purpose  : 
//=======================================================================
Standard_Real TPrsStd_AISPresentation::Width() const
{
   return myWidth;
}

//=======================================================================
//function :HasWidth
//purpose  : 
//=======================================================================
Standard_Boolean TPrsStd_AISPresentation::HasOwnWidth() const
{
  return hasOwnWidth;
}

//=======================================================================
//function :SetWidth
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::SetWidth(const Standard_Real aWidth) 
{
  // OCC2932 correction
  if(hasOwnWidth && myWidth == aWidth && myAIS.IsNull()) 
    if(myAIS->HasWidth() && myAIS->Width() == aWidth ) 
      return;

  Backup();
  myWidth = aWidth;
  hasOwnWidth = Standard_True;
  if( myAIS.IsNull() ) AISUpdate();
  if( !myAIS.IsNull() ) {
    if( myAIS->HasWidth() && myAIS->Width() == aWidth ) return;   // AIS has already had that width     
    Handle(AIS_InteractiveContext) ctx;
    Handle(TPrsStd_AISViewer) viewer;
    if( TPrsStd_AISViewer::Find(Label(), viewer) ) ctx = viewer->GetInteractiveContext();
    if( !ctx.IsNull() )  
      ctx->SetWidth(myAIS, aWidth, Standard_False);
    else 
      myAIS->SetWidth(aWidth);
  }
}

//=======================================================================
//function :UnsetWidth
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::UnsetWidth()
{
  // OCC2932 correction
  if(!hasOwnWidth && !myAIS.IsNull())
    if(!myAIS->HasWidth())
      return;

  Backup();
  hasOwnWidth = Standard_False;
  if( myAIS.IsNull() ) AISUpdate();
  if( !myAIS.IsNull() &&  myAIS->HasWidth() ) {
    Handle(AIS_InteractiveContext) ctx;
    Handle(TPrsStd_AISViewer) viewer;
    if( TPrsStd_AISViewer::Find(Label(), viewer) ) ctx = viewer->GetInteractiveContext(); 
    if( !ctx.IsNull() )   
      ctx->UnsetWidth(myAIS, Standard_False);
    else  
      myAIS->UnsetWidth();
  }
}



//=======================================================================
//function : Mode
//purpose  : 
//=======================================================================

Standard_Integer TPrsStd_AISPresentation::Mode() const
{
   return myMode;
}

//=======================================================================
//function :HasOwnMode
//purpose  : 
//=======================================================================
Standard_Boolean TPrsStd_AISPresentation::HasOwnMode() const
{
  return hasOwnMode;
}

//=======================================================================
//function :SetMode
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::SetMode(const Standard_Integer theMode) 
{
  // OCC2932 correction
  if(hasOwnMode && myMode == theMode && !myAIS.IsNull()) 
    if(myAIS->DisplayMode() == theMode ) 
      return;

  Backup();
  myMode = theMode;
  hasOwnMode = Standard_True;
  if( myAIS.IsNull() ) AISUpdate();
  if( !myAIS.IsNull() ) {
    if(  myAIS->DisplayMode() == theMode ) return;   // AIS has already had that mode    
    Handle(AIS_InteractiveContext) ctx;
    Handle(TPrsStd_AISViewer) viewer;
    if( TPrsStd_AISViewer::Find(Label(), viewer) )
      ctx = viewer->GetInteractiveContext();
    if( !ctx.IsNull() )  
      ctx->SetDisplayMode(myAIS, theMode, Standard_False);
    else 
      myAIS->SetDisplayMode(theMode);
  }
}

//=======================================================================
//function :UnsetMode
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::UnsetMode()
{
  // OCC2932 correction
  if(HasOwnMode() == Standard_False && myAIS.IsNull() == Standard_False)
    if(!myAIS->HasDisplayMode())
      return;

  Backup();
  hasOwnMode = Standard_False;
  if( myAIS.IsNull() ) AISUpdate();
  if( !myAIS.IsNull() &&  myAIS->HasDisplayMode() ) {
  	Handle(AIS_InteractiveContext) ctx;
   	Handle(TPrsStd_AISViewer) viewer;
   	if( TPrsStd_AISViewer::Find(Label(), viewer) )
    	ctx = viewer->GetInteractiveContext(); 
   	if( !ctx.IsNull() )
        ctx->UnsetDisplayMode(myAIS, Standard_False);
    else  
       	myAIS->UnsetDisplayMode();
  }
}

#ifdef BUC61050
//=======================================================================
//function : SelectionMode
//purpose  : 
//=======================================================================

Standard_Integer TPrsStd_AISPresentation::SelectionMode() const
{
   return mySelectionMode;
}

//=======================================================================
//function :HasOwnSelectionMode
//purpose  : 
//=======================================================================
Standard_Boolean TPrsStd_AISPresentation::HasOwnSelectionMode() const
{
  return hasOwnSelectionMode;
}

//=======================================================================
//function :SetSelectionMode
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::SetSelectionMode(const Standard_Integer theSelectionMode) 
{
  // OCC2932 correction
  if(hasOwnSelectionMode && mySelectionMode == theSelectionMode && !myAIS.IsNull())
    if(myAIS->SelectionMode() == theSelectionMode )
      return;

  Backup();
  mySelectionMode = theSelectionMode;
  hasOwnSelectionMode = Standard_True;
  if( myAIS.IsNull() ) AISUpdate();
  if( !myAIS.IsNull() ) {
    if(  myAIS->SelectionMode() == theSelectionMode ) return;
    myAIS->SetSelectionMode(theSelectionMode);
  }
}

//=======================================================================
//function :UnsetSelectionMode
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::UnsetSelectionMode()
{
  if(!hasOwnSelectionMode && !myAIS.IsNull())
    if(!myAIS->HasSelectionMode())
      return;

  Backup();
  hasOwnSelectionMode = Standard_False;
  if( myAIS.IsNull() ) AISUpdate();
  if( !myAIS.IsNull() &&  myAIS->HasSelectionMode() ) {
    myAIS->UnsetSelectionMode();
  }
}
#endif


//=======================================================================
//function : ID
//purpose  : 
//=======================================================================
const Standard_GUID& TPrsStd_AISPresentation::ID() const { return GetID(); }


//=======================================================================
//function : BackupCopy
//purpose  : 
//=======================================================================
Handle(TDF_Attribute) TPrsStd_AISPresentation::BackupCopy() const 
{
  Handle(TPrsStd_AISPresentation) copy = new TPrsStd_AISPresentation;
  copy->myTransparency = myTransparency;
  copy->myColor = myColor;
  copy->myMode= myMode;
#ifdef BUC60917
  copy->myWidth= myWidth;
#endif
  copy->myMaterial = myMaterial;
  copy->hasOwnColor = hasOwnColor;
  copy->hasOwnMaterial = hasOwnMaterial;
  copy->hasOwnWidth = hasOwnWidth;
  copy->hasOwnMode=hasOwnMode;
  copy->hasOwnTransparency = hasOwnTransparency;
  copy->myAIS.Nullify();
  copy->isDisplayed = isDisplayed;
  copy->myDriverGUID = myDriverGUID;
#ifdef BUC61050
  copy->mySelectionMode= mySelectionMode;
  copy->hasOwnSelectionMode = hasOwnSelectionMode;
#endif
  return copy; 
}


//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================
Handle(TDF_Attribute) TPrsStd_AISPresentation::NewEmpty() const
{   
  return new TPrsStd_AISPresentation ();
}

//=======================================================================
//function : Restore
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::Restore (const Handle(TDF_Attribute)& With) 
{ 
  Handle(TPrsStd_AISPresentation) with = Handle(TPrsStd_AISPresentation)::DownCast(With);

  myAIS.Nullify();

  if(!with->HasOwnMaterial()) hasOwnMaterial = Standard_False;
  else { 
#ifndef OCC1031
    myMaterial = with->Material();
#endif
    hasOwnMaterial = Standard_True;
  }
#ifdef OCC1031
  myMaterial = with->Material();
#endif

  if(!with->HasOwnColor()) hasOwnColor = Standard_False;
  else { 
#ifndef OCC1030
    myColor = with->Color(); 
#endif
    hasOwnColor = Standard_True;
  }
#ifdef OCC1030
  myColor = with->Color(); 
#endif

  if(!with->HasOwnWidth()) hasOwnWidth = Standard_False;
  else { 
#ifndef OCC1032
    myWidth = with->Width();
#endif
    hasOwnWidth = Standard_True;
  }
#ifdef OCC1032
  myWidth = with->Width();
#endif

 if(!with->HasOwnMode()) hasOwnMode = Standard_False;
  else { 
#ifndef OCC1033
    myMode = with->Mode();
#endif
    hasOwnMode = Standard_True;
  }
#ifdef OCC1033
  myMode = with->Mode();
#endif
  
#ifdef BUC61050
  if(!with->HasOwnSelectionMode()) hasOwnSelectionMode = Standard_False;
  else { 
#ifndef OCC1034
    mySelectionMode = with->SelectionMode();
#endif
    hasOwnSelectionMode = Standard_True;
  }
#ifdef OCC1034
  mySelectionMode = with->SelectionMode();
#endif
#endif

  if(!with->HasOwnTransparency()) hasOwnTransparency = Standard_False;
  else { 
#ifndef OCC1029
    myTransparency = with->Transparency();
#endif
    hasOwnTransparency = Standard_True;
  }
#ifdef OCC1029
  myTransparency = with->Transparency();
#endif

  isDisplayed = with->IsDisplayed();
  myDriverGUID  = with->GetDriverGUID();
}

//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::Paste (const Handle(TDF_Attribute)& Into,
				     const Handle(TDF_RelocationTable)& ) const
{  
  Handle(TPrsStd_AISPresentation) into = Handle(TPrsStd_AISPresentation)::DownCast(Into);
  
  into->Backup();

  if(!hasOwnMaterial) into->hasOwnMaterial = Standard_False;
  else {
    into->myMaterial = myMaterial;
    into->hasOwnMaterial = Standard_True;
  }

  if(!hasOwnColor) into->hasOwnColor = Standard_False;
  else {
    into->myColor = myColor; 
    into->hasOwnColor = Standard_True;
  }

  if(!hasOwnWidth) into->hasOwnWidth = Standard_False;
  else {
    into->myWidth = myWidth;
    into->hasOwnWidth = Standard_True;
  }
 if(!hasOwnMode) into->hasOwnMode = Standard_False;
  else {
    into->myMode = myMode;
    into->hasOwnMode = Standard_True;
  }

#ifdef BUC61050
 if(!hasOwnSelectionMode) into->hasOwnSelectionMode = Standard_False;
  else {
    into->mySelectionMode = mySelectionMode;
    into->hasOwnSelectionMode = Standard_True;
  }
#endif

  if(!hasOwnTransparency) into->hasOwnTransparency = Standard_False;
  else {
    into->myTransparency = myTransparency;
    into->hasOwnTransparency = Standard_True;
  }

  if (into->isDisplayed)
    into->AISErase(Standard_True);

  into->isDisplayed = isDisplayed;   
  into->myDriverGUID = myDriverGUID;

  into->myAIS.Nullify();
}

//=======================================================================
//function : AfterAddition
//purpose  : erase if displayed
//=======================================================================
void TPrsStd_AISPresentation::AfterAddition() 
{ 
  AfterResume();
}

//=======================================================================
//function : BeforeRemoval
//purpose  : erase if displayed
//=======================================================================
void TPrsStd_AISPresentation::BeforeRemoval() 
{ 
   BeforeForget();
}

//=======================================================================
//function : BeforeForget
//purpose  : erase if displayed
//=======================================================================
void TPrsStd_AISPresentation::BeforeForget() 
{ 
  if( !myAIS.IsNull() ) {
    AISErase(Standard_True);   //Remove AISObject from context
    myAIS.Nullify();
  }
}


//=======================================================================
//function : AfterResume
//purpose  : display if displayed
//=======================================================================
void TPrsStd_AISPresentation::AfterResume() 
{
  AISUpdate();
  if( IsDisplayed() ) AISDisplay();
  else AISErase();
}

//=======================================================================
//function : BeforeUndo
//purpose  : le NamedShape associe doit etre present
//=======================================================================

Standard_Boolean TPrsStd_AISPresentation::BeforeUndo (const Handle(TDF_AttributeDelta)& AD,
						      const Standard_Boolean ) 
{
  Handle(TPrsStd_AISPresentation) P;
  AD->Label().FindAttribute(TPrsStd_AISPresentation::GetID(), P); 

  if (AD->IsKind(STANDARD_TYPE(TDF_DeltaOnAddition))) {    
    if( !P.IsNull() ) P->BeforeForget();
  }
  else if (AD->IsKind(STANDARD_TYPE(TDF_DefaultDeltaOnRemoval))) {
  }  
  else if (AD->IsKind(STANDARD_TYPE(TDF_DefaultDeltaOnModification))) {
    if( !P.IsNull() ) P->BeforeForget();
  } 

  return Standard_True;
}


//=======================================================================
//function : AfterUndo
//purpose  : le NamedShape associe doit etre present
//=======================================================================

Standard_Boolean TPrsStd_AISPresentation::AfterUndo (const Handle(TDF_AttributeDelta)& AD,
						     const Standard_Boolean ) 
{ 
  Handle(TPrsStd_AISPresentation) P;
  AD->Label().FindAttribute(TPrsStd_AISPresentation::GetID(), P);

  if (AD->IsKind(STANDARD_TYPE(TDF_DeltaOnAddition))) {
  }
  else if (AD->IsKind(STANDARD_TYPE(TDF_DefaultDeltaOnRemoval))) {  
    if( !P.IsNull() ) P->AfterAddition();
  }  
  else if (AD->IsKind(STANDARD_TYPE(TDF_DefaultDeltaOnModification))) {
    if( !P.IsNull() ) P->AfterResume();
  }

  return Standard_True;
}



//=======================================================================
//function : AISUpdate
//purpose  : 
//=======================================================================

void TPrsStd_AISPresentation::AISUpdate ()
{ 
  Backup();

  Handle(AIS_InteractiveContext) ctx;
  if(!Label().IsNull()) {  
    Handle(TPrsStd_AISViewer) viewer;
    if( TPrsStd_AISViewer::Find(Label(), viewer) ) ctx = viewer->GetInteractiveContext();

    Handle(TPrsStd_Driver) driver;
    if (TPrsStd_DriverTable::Get()->FindDriver(GetDriverGUID(), driver)) {
      if (myAIS.IsNull()) {              // build a new  AIS
	Handle(AIS_InteractiveObject) newais;
	if (driver->Update (Label(), newais))  {
	  myAIS = newais;
	  newais->SetOwner(this);
	}
      }
      else {
	Handle(AIS_InteractiveObject) theais = myAIS;
	if (driver->Update (Label(), theais)) {
	  if (! (theais ==  myAIS)) {    
	    if(!ctx.IsNull()) ctx->Remove(myAIS);
	    myAIS = theais;               //Driver has built new AIS
	    theais->SetOwner(this);
	  }
	}
      }
    }
  }
  else return;

//Apply the visualization settings
  if( !myAIS.IsNull() ) {

    if( hasOwnColor ) { 
      if( !(myAIS->HasColor()) || (myAIS->HasColor() && myAIS->Color() != myColor) ) {
	if(!ctx.IsNull()) ctx->SetColor(myAIS, myColor, Standard_False);
	else myAIS->SetColor(myColor);  
      }
    } 

    if( hasOwnMaterial ) { 
      if( !(myAIS->HasMaterial()) || (myAIS->HasMaterial() && myAIS->Material() != myMaterial) ) {
	if(!ctx.IsNull()) ctx->SetMaterial(myAIS, myMaterial, Standard_False );
	else myAIS->SetMaterial(myMaterial);  
      }
    } 
    
    if( hasOwnTransparency ) {
      if(  myAIS->Transparency() != myTransparency )  {
	if(!ctx.IsNull()) ctx->SetTransparency(myAIS, myTransparency, Standard_False);
	else myAIS->SetTransparency(myTransparency);  
      }
    }

    if( hasOwnWidth ) { 
      if( !(myAIS->HasWidth()) || (myAIS->HasWidth() && myAIS->Width() != myWidth) ) {
	if(!ctx.IsNull()) ctx->SetWidth(myAIS, myWidth, Standard_False);
	else myAIS->SetWidth(myWidth); 
      }
    }

    if( hasOwnMode) { 
      if(  myAIS->DisplayMode() != myMode ) {
	  myAIS->SetDisplayMode(myMode); 
      } 
     
           
    }

#ifdef BUC61050
    if (hasOwnSelectionMode) { 
      if (myAIS->SelectionMode() != mySelectionMode ) {
	myAIS->SetSelectionMode(mySelectionMode); 
      } 
    }
#endif

  }
  
  if( isDisplayed && !ctx.IsNull() ) ctx->Redisplay(myAIS, Standard_False);
 
  return;
}

//=======================================================================
//function : AISDisplay
//purpose  : 
//=======================================================================

void TPrsStd_AISPresentation::AISDisplay ()
{   
  
  if (!Label().IsNull()) {  
    Handle(TPrsStd_AISViewer) viewer;
    if( !TPrsStd_AISViewer::Find(Label(), viewer) ) return;   
    Handle(AIS_InteractiveContext) ctx = viewer->GetInteractiveContext();
    if( ctx.IsNull() ) return;

    if (!myAIS.IsNull()) { 

      if( !(myAIS->GetContext()).IsNull() && (myAIS->GetContext()) != ctx ) myAIS->GetContext()->Remove(myAIS);
      
      if( isDisplayed && ctx->IsDisplayed(myAIS) ) return;

      ctx->Display(myAIS, Standard_False);
      
      if( ctx->IsDisplayed(myAIS) ) SetDisplayed(Standard_True); 
    }
  }
}


//=======================================================================
//function : AISErase
//purpose  : 
//=======================================================================

void TPrsStd_AISPresentation::AISErase (const Standard_Boolean remove)
{   
  SetDisplayed(Standard_False);  
  Handle(AIS_InteractiveContext) ctx, ownctx;

  if ( !myAIS.IsNull() ) {   
    ownctx = myAIS->GetContext();
    if ( !Label().IsNull()) {  
      Handle(TPrsStd_AISViewer) viewer;
      if( !TPrsStd_AISViewer::Find(Label(), viewer) ) return;   
      ctx = viewer->GetInteractiveContext();
      if( remove ) {
	if( !ctx.IsNull() ) ctx->Remove (myAIS,Standard_False); 
	if( !ownctx.IsNull() && ownctx != ctx ) ownctx->Remove (myAIS,Standard_False);
        myAIS->SetToUpdate();
      }
      else {
	if( !ctx.IsNull() ) ctx->Erase (myAIS,Standard_False); 
	if( !ownctx.IsNull() && ownctx != ctx ) ownctx->Erase (myAIS,Standard_False);
      }
    }
    else {
     if( remove ) {
      if( !ownctx.IsNull() ) {
	ownctx->Remove (myAIS,Standard_False);
	myAIS->SetToUpdate();
      }
     } else
      if( !ownctx.IsNull() ) ownctx->Erase (myAIS,Standard_False); 
    }
  }
}


//=======================================================================
//function :GetAIS
//purpose  : 
//=======================================================================
Handle(AIS_InteractiveObject) TPrsStd_AISPresentation::GetAIS() const
{
  return myAIS;
}


//=======================================================================
//function :SetDisplayed
//purpose  : 
//=======================================================================
void TPrsStd_AISPresentation::SetDisplayed(const Standard_Boolean B) 
{
  Backup();
  isDisplayed = B;
}

