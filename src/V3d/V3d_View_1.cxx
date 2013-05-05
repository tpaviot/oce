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
        File V3d_View_1.cxx :

************************************************************************/
/*----------------------------------------------------------------------*/
/*
 * Includes
 */ 

#include <V3d_View.jxx>

/*----------------------------------------------------------------------*/

void V3d_View::SetAntialiasingOn() {
  MyViewContext.SetAliasingOn() ;
  MyView->SetContext(MyViewContext) ;
}

void V3d_View::SetAntialiasingOff() {
  MyViewContext.SetAliasingOff() ;
  MyView->SetContext(MyViewContext) ;
}

/*----------------------------------------------------------------------*/

void V3d_View::SetZClippingDepth(const Standard_Real Depth) {
  Standard_Real Front,Back,Width ;

  Front = MyViewContext.ZClippingFrontPlane() ;
  Back = MyViewContext.ZClippingBackPlane() ;
  Width = Front - Back ;
  Front = Depth + Width/2. ;
  Back = Depth - Width/2. ;
  MyViewContext.SetZClippingBackPlane(Back) ;
  MyViewContext.SetZClippingFrontPlane(Front) ;
  MyView->SetContext(MyViewContext) ;
}

/*----------------------------------------------------------------------*/

void V3d_View::SetZClippingWidth(const Standard_Real Width) {
  Standard_Real Front,Back,Depth ;
  V3d_BadValue_Raise_if( Width <= 0.,"V3d_View::SetZClippingWidth, bad width");

  Front = MyViewContext.ZClippingFrontPlane() ;
  Back = MyViewContext.ZClippingBackPlane() ;
  Depth = (Front + Back)/2. ;
  Front = Depth + Width/2. ;
  Back = Depth - Width/2. ;
  MyViewContext.SetZClippingBackPlane(Back) ;
  MyViewContext.SetZClippingFrontPlane(Front) ;
  MyView->SetContext(MyViewContext) ;
}

/*----------------------------------------------------------------------*/

void V3d_View::SetZClippingType(const V3d_TypeOfZclipping Type) {

  switch (Type) {
  case V3d_OFF :
    MyViewContext.SetZClippingOff() ;
    break ;
  case V3d_BACK :
    MyViewContext.SetBackZClippingOn() ;
    MyViewContext.SetFrontZClippingOff() ;
    break ;
  case V3d_FRONT :
    MyViewContext.SetFrontZClippingOn() ;
    MyViewContext.SetBackZClippingOff() ;
    break ;
  case V3d_SLICE :
    MyViewContext.SetZClippingOn() ;
    break ;
  }
  MyView->SetContext(MyViewContext) ;
}

/*----------------------------------------------------------------------*/

V3d_TypeOfZclipping V3d_View::ZClipping(Standard_Real& Depth, Standard_Real& Width) const {
  V3d_TypeOfZclipping T = V3d_OFF ;
  Standard_Real Front,Back ;
  Standard_Boolean Aback,Afront ;

  Back = MyViewContext.ZClippingBackPlane() ;
  Front = MyViewContext.ZClippingFrontPlane() ;
  Aback = MyViewContext.BackZClippingIsOn() ;
  Afront = MyViewContext.FrontZClippingIsOn() ;
  Width = Front - Back ;
  Depth = (Front + Back)/2. ;
  if( Aback ) {
    if( Afront ) T = V3d_SLICE ;
    else	 T = V3d_BACK ;
  } else if( Afront ) T = V3d_FRONT ;

  return T ;
}


/*----------------------------------------------------------------------*/

void V3d_View::SetZCueingDepth(const Standard_Real Depth) {
  Standard_Real Front,Back,Width ;

  Front = MyViewContext.DepthCueingFrontPlane() ;
  Back = MyViewContext.DepthCueingBackPlane() ;
  Width = Front - Back ;
  Front = Depth + Width/2. ;
  Back = Depth - Width/2. ;
  MyViewContext.SetDepthCueingBackPlane(Back) ;
  MyViewContext.SetDepthCueingFrontPlane(Front) ;
  MyView->SetContext(MyViewContext) ;
}

/*----------------------------------------------------------------------*/

void V3d_View::SetZCueingWidth(const Standard_Real Width) {
  Standard_Real Front,Back,Depth ;
  V3d_BadValue_Raise_if( Width <= 0.,"V3d_View::SetZCueingWidth, bad width");

  Front = MyViewContext.DepthCueingFrontPlane() ;
  Back = MyViewContext.DepthCueingBackPlane() ;
  Depth = (Front + Back)/2. ;
  Front = Depth + Width/2. ;
  Back = Depth - Width/2. ;
  MyViewContext.SetDepthCueingBackPlane(Back) ;
  MyViewContext.SetDepthCueingFrontPlane(Front) ;
  MyView->SetContext(MyViewContext) ;
}

/*----------------------------------------------------------------------*/

void V3d_View::SetZCueingOn() {

  MyViewContext.SetDepthCueingOn() ;
  MyView->SetContext(MyViewContext) ;
}

/*----------------------------------------------------------------------*/

void V3d_View::SetZCueingOff() {

  MyViewContext.SetDepthCueingOff() ;
  MyView->SetContext(MyViewContext) ;
}

/*----------------------------------------------------------------------*/

Standard_Boolean V3d_View::ZCueing(Standard_Real& Depth, Standard_Real& Width)const  {
  Standard_Boolean Z = MyViewContext.DepthCueingIsOn() ;
  Standard_Real Front,Back ;

Back = MyViewContext.DepthCueingBackPlane() ;
  Front = MyViewContext.DepthCueingFrontPlane() ;
  Width = Front - Back ;
  Depth = (Front + Back)/2. ;

  return Z ;
}

/*----------------------------------------------------------------------*/
