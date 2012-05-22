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

/***********************************************************************
 
     FONCTION :
     ----------
        Classe V3d_SpotLight :
 
     HISTORIQUE DES MODIFICATIONS   :
     --------------------------------
      00-09-92 : GG  ; Creation.
      30-03-98 : ZOV ; PRO6774 (reconstruction of the class hierarchy and suppressing useless methods)
      IMP230300: GG Add SetColor() and Color() methods
      IMP231100: GG Add IsDisplayed() method

************************************************************************/

/*----------------------------------------------------------------------*/
/*
 * Includes
 */

#include <V3d.hxx>
#include <V3d_Light.ixx>

//-Declarations


//-Aliases

//-Global data definitions

//-Local data definitions

//-Constructors

V3d_Light::V3d_Light(const Handle(V3d_Viewer)& VM) {

	MyType = V3d_AMBIENT ;
	VM->AddLight(this) ;
}

//-Methods, in order

Handle(Visual3d_Light) V3d_Light::Light() const {

	return MyLight ;
}

void V3d_Light::SetColor(const Quantity_TypeOfColor Type, const Standard_Real v1, const Standard_Real v2, const Standard_Real v3) {
  Standard_Real V1 = v1 ;
  Standard_Real V2 = v2 ;
  Standard_Real V3 = v3 ;

  if( V1 < 0. ) V1 = 0. ; else if( V1 > 1. ) V1 = 1. ;
  if( V2 < 0. ) V2 = 0. ; else if( V2 > 1. ) V2 = 1. ;
  if( V3 < 0. ) V3 = 0. ; else if( V3 > 1. ) V3 = 1. ;


  Quantity_Color C(V1,V2,V3,Type) ;
  MyLight->SetColor(C) ;
}

void V3d_Light::SetColor(const Quantity_NameOfColor Name) {
  Quantity_Color C(Name) ;
  MyLight->SetColor(C) ;
}

void V3d_Light::SetColor(const Quantity_Color& aColor) {
  MyLight->SetColor(aColor) ;
}

void V3d_Light::Color(const Quantity_TypeOfColor Type, Standard_Real& V1, Standard_Real& V2, Standard_Real& V3) const {

  Quantity_Color C ;
  C = MyLight->Color() ;
  C.Values(V1,V2,V3,Type) ;
}

void V3d_Light::Color(Quantity_NameOfColor& Name) const{

  Quantity_Color C ;
  C = MyLight->Color() ;
  Name = C.Name();
}

Quantity_Color V3d_Light::Color() const{

  return MyLight->Color();
}

V3d_TypeOfLight V3d_Light::Type() const {

  return MyType;
}


Standard_Boolean V3d_Light::Headlight() const {
  return MyLight->Headlight();
}

void V3d_Light::SymetricPointOnSphere (const Handle(V3d_View)& aView, const Graphic3d_Vertex &Center, const Graphic3d_Vertex &aPoint, const Standard_Real Rayon, Standard_Real& X, Standard_Real& Y, Standard_Real& Z, Standard_Real& VX, Standard_Real& VY, Standard_Real& VZ ) {

  Standard_Real X0,Y0,Z0,XP,YP,ZP;
  Standard_Real PXP,PYP,DeltaX,DeltaY,DeltaZ;
  Standard_Real A,B,C,Delta,Lambda;
  Standard_Integer IPX,IPY;

  Center.Coord(X0,Y0,Z0);
  aPoint.Coord(XP,YP,ZP);
  aView->Project(XP,YP,ZP,PXP,PYP);
  aView->Convert(PXP,PYP,IPX,IPY);
  aView->ProjReferenceAxe(IPX,IPY,X,Y,Z,VX,VY,VZ);
  DeltaX = X0 - XP;
  DeltaY = Y0 - YP;
  DeltaZ = Z0 - ZP;

//      The point of intersection of straight lines defined by :
//      - Straight line passing by the point of projection and the eye
//        if this is a perspective, parralel to the normal of the view 
//        if this is an axonometric view.
//        position in the view is parallel to the normal of the view
//      - The distance position of the target camera is equal to the radius.

  A = VX*VX + VY*VY + VZ*VZ ;
  B = -2. * (VX*DeltaX + VY*DeltaY + VZ*DeltaZ);
  C = DeltaX*DeltaX + DeltaY*DeltaY + DeltaZ*DeltaZ 
    - Rayon*Rayon ;
  Delta = B*B - 4.*A*C;
  if ( Delta >= 0 ) {
    Lambda = (-B + Sqrt(Delta))/(2.*A);
    if ( Lambda >= -0.0001 && Lambda <= 0.0001 ) 
      Lambda = (-B - Sqrt(Delta))/(2.*A);
    X = XP + Lambda*VX;
    Y = YP + Lambda*VY;
    Z = ZP + Lambda*VZ;
  }
  else {
    X = XP; Y = YP; Z = ZP;
  }
}

Standard_Boolean V3d_Light::IsDisplayed() const {
  if( MyGraphicStructure.IsNull() ) return Standard_False;
  return MyGraphicStructure->IsDisplayed();
}
