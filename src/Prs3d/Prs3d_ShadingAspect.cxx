// Copyright (c) 1995-1999 Matra Datavision
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


#define BUC60488	//GG_23/09/99 Updates correctly the Material after
//			any change.

#define GER61351		//GG_171199     Enable to set an object RGB color
//						  instead a restricted object NameOfColor.
//				Enable to change separatly the front and back color.

#define OCC1174 //SAV_080103 Added back face interior color management

#include <Prs3d_ShadingAspect.ixx>

//=======================================================================
//function : Prs3d_ShadingAspect
//purpose  : 
//=======================================================================

Prs3d_ShadingAspect::Prs3d_ShadingAspect () {


  Graphic3d_MaterialAspect aMat (Graphic3d_NOM_BRASS);
  Quantity_Color Col;
  // Ceci permet de recuperer la couleur associee
  // au materiau defini par defaut.
//POP K4L
  Col = aMat.AmbientColor ();
//  Col = aMat.Color ();
  myAspect = new Graphic3d_AspectFillArea3d (Aspect_IS_SOLID,
					     Col,
					     Col,
					     Aspect_TOL_SOLID,
					     1.0,
					     aMat,
					     aMat);
}


//=======================================================================
//function : SetColor
//purpose  : 
//=======================================================================

#ifdef GER61351
void Prs3d_ShadingAspect::SetColor(const Quantity_NameOfColor aColor,
					     const Aspect_TypeOfFacingModel aModel) {

  SetColor(Quantity_Color(aColor),aModel);
}

void Prs3d_ShadingAspect::SetColor(const Quantity_Color &aColor,
					     const Aspect_TypeOfFacingModel aModel) {
#ifndef OCC1174  
  myAspect->SetInteriorColor(aColor);
#endif

  if( aModel != Aspect_TOFM_BOTH_SIDE ) {
    myAspect->SetDistinguishOn();
  }
  if( aModel == Aspect_TOFM_FRONT_SIDE || aModel == Aspect_TOFM_BOTH_SIDE ) {
    Graphic3d_MaterialAspect front = myAspect->FrontMaterial();
    front.SetColor(aColor);
    myAspect->SetFrontMaterial(front);
#ifdef OCC1174
    myAspect->SetInteriorColor( aColor );
#endif
  }

  if( aModel == Aspect_TOFM_BACK_SIDE || aModel == Aspect_TOFM_BOTH_SIDE ) {
    Graphic3d_MaterialAspect back = myAspect->BackMaterial();
    back.SetColor(aColor);
    myAspect->SetBackMaterial(back);
#ifdef OCC1174
    myAspect->SetBackInteriorColor( aColor );
#endif
  }
}

Quantity_Color Prs3d_ShadingAspect::Color( const Aspect_TypeOfFacingModel aModel ) const {
  Quantity_Color myReturn ;
  switch (aModel) {
    default:
    case Aspect_TOFM_BOTH_SIDE:
    case Aspect_TOFM_FRONT_SIDE:
	myReturn = myAspect->FrontMaterial().Color();
	break;
    case Aspect_TOFM_BACK_SIDE:
	myReturn = myAspect->BackMaterial().Color();
	break;
  }
  return myReturn ;
}
#else
void Prs3d_ShadingAspect::SetColor(const Quantity_NameOfColor aColor) {
  myAspect->SetInteriorColor(aColor);
#ifdef OCC1174
  myAspect->SetBackInteriorColor( aColor );
#endif
  myAspect->FrontMaterial().SetAmbientColor(Quantity_Color(aColor));
  myAspect->BackMaterial().SetAmbientColor(Quantity_Color(aColor));
//  myAspect->FrontMaterial().SetColor(Quantity_Color(aColor));
//  myAspect->BackMaterial().SetColor(Quantity_Color(aColor));
}
#endif	

//=======================================================================
//function : SetMaterial
//purpose  : 
//=======================================================================

#ifdef GER61351
void Prs3d_ShadingAspect::SetMaterial(
                   const Graphic3d_NameOfMaterial aMaterial,
			 const Aspect_TypeOfFacingModel aModel ) {

  SetMaterial(Graphic3d_MaterialAspect(aMaterial),aModel);
}
#else
void Prs3d_ShadingAspect::SetMaterial(
//                 const Graphic3d_NameOfPhysicalMaterial aMaterial) {
                 const Graphic3d_NameOfMaterial aMaterial) {

  Graphic3d_MaterialAspect TheMaterial(aMaterial);
  myAspect->SetFrontMaterial (TheMaterial);
  myAspect->SetBackMaterial (TheMaterial);
}
#endif

//=======================================================================
//function : SetMaterial
//purpose  : 
//=======================================================================

#ifdef GER61351
void Prs3d_ShadingAspect::SetMaterial(
                   const Graphic3d_MaterialAspect& aMaterial,
			 const Aspect_TypeOfFacingModel aModel ) {

  if( aModel != Aspect_TOFM_BOTH_SIDE ) {
    myAspect->SetDistinguishOn();
  }
  if( aModel == Aspect_TOFM_FRONT_SIDE || aModel == Aspect_TOFM_BOTH_SIDE ) {
    myAspect->SetFrontMaterial(aMaterial);
  }

  if( aModel == Aspect_TOFM_BACK_SIDE || aModel == Aspect_TOFM_BOTH_SIDE ) {
    myAspect->SetBackMaterial(aMaterial);
  }
}

Graphic3d_MaterialAspect  Prs3d_ShadingAspect::Material(
			 const Aspect_TypeOfFacingModel aModel ) const {
  Graphic3d_MaterialAspect myReturn ;		   
  switch (aModel) {
    default:
    case Aspect_TOFM_BOTH_SIDE:
    case Aspect_TOFM_FRONT_SIDE:
	myReturn = myAspect->FrontMaterial();
	break;
    case Aspect_TOFM_BACK_SIDE:
	myReturn = myAspect->BackMaterial();
	break;
  }
 return myReturn ;  
} 
#else
void Prs3d_ShadingAspect::SetMaterial(
                 const Graphic3d_MaterialAspect&  aMaterial) 
{
  myAspect->SetFrontMaterial (aMaterial);
  myAspect->SetBackMaterial (aMaterial);
}
#endif

//=======================================================================
//function : SetTransparency
//purpose  : 
//=======================================================================

#ifdef GER61351
void Prs3d_ShadingAspect::SetTransparency(const Standard_Real aValue,
						      const Aspect_TypeOfFacingModel aModel ) {

  if( aModel != Aspect_TOFM_BOTH_SIDE ) {
    myAspect->SetDistinguishOn();
  }
  if( aModel == Aspect_TOFM_FRONT_SIDE || aModel == Aspect_TOFM_BOTH_SIDE ) {
    Graphic3d_MaterialAspect front = myAspect->FrontMaterial();
    front.SetTransparency(aValue);
    myAspect->SetFrontMaterial(front);
  }

  if( aModel == Aspect_TOFM_BACK_SIDE || aModel == Aspect_TOFM_BOTH_SIDE ) {
    Graphic3d_MaterialAspect back = myAspect->BackMaterial();
    back.SetTransparency(aValue);
    myAspect->SetBackMaterial(back);
  }
}

Standard_Real Prs3d_ShadingAspect::Transparency(const Aspect_TypeOfFacingModel aModel ) const {
Standard_Real aValue(0.);
  switch (aModel) {
    case Aspect_TOFM_BOTH_SIDE:
    case Aspect_TOFM_FRONT_SIDE:
	aValue = myAspect->FrontMaterial().Transparency();
	break;
    case Aspect_TOFM_BACK_SIDE:
	aValue = myAspect->BackMaterial().Transparency();
	break;
  }
  return aValue;
}
#endif

//=======================================================================
//function : SetAspect
//purpose  : 
//=======================================================================

void Prs3d_ShadingAspect::SetAspect(const Handle(Graphic3d_AspectFillArea3d)& Asp)
{
  myAspect=Asp;
}

Handle (Graphic3d_AspectFillArea3d) Prs3d_ShadingAspect::Aspect () const {
  return myAspect;
}

