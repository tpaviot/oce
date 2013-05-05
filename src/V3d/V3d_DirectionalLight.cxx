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
        Classe V3d_DirectionalLight :
 
     HISTORIQUE DES MODIFICATIONS   :
     --------------------------------
      00-09-92 : GG  ; Creation.
      18-06-96 : FMN ; Ajout MyGraphicStructure1 pour sauvegarder snopick
      24-12-97 : FMN ; Remplacement de math par MathGra
      31-12-97 : CAL ; Suppression de MathGra
      21-01-98 : CAL ; Window de Xw et WNT remplacee par Aspect_Window
      23-02-98 : FMN ; Remplacement PI par Standard_PI
      30-03-98 : ZOV ; PRO6774 (reconstruction of the class hierarchy and suppressing useless methods)

************************************************************************/

/*----------------------------------------------------------------------*/
/*
 * Includes
 */

#include <V3d.hxx>
#include <V3d_DirectionalLight.ixx>
#include <Graphic3d_Vector.hxx>
#include <Graphic3d_Vertex.hxx>
#include <Graphic3d_Structure.hxx>
#include <Graphic3d_Group.hxx>
#include <Graphic3d_ArrayOfSegments.hxx>
#include <Graphic3d_AspectMarker3d.hxx>
#include <Graphic3d_AspectLine3d.hxx>
#include <Graphic3d_AspectText3d.hxx>
#include <Visual3d_Light.hxx>
#include <Visual3d_ViewManager.hxx>
#include <Visual3d_ContextPick.hxx>
#include <Visual3d_PickDescriptor.hxx>
#include <Visual3d_HSequenceOfPickPath.hxx>
#include <Visual3d_PickPath.hxx>
#include <V3d_BadValue.hxx>
#include <gp_Dir.hxx>
#include <gp_Ax1.hxx>
#include <gp_Vec.hxx>
#include <gp_Pnt.hxx>
#include <gp_Trsf.hxx>
#include <TColStd_Array2OfReal.hxx>
#include <Aspect_Window.hxx>

//-Constructors

V3d_DirectionalLight::V3d_DirectionalLight(const Handle(V3d_Viewer)& VM, const
V3d_TypeOfOrientation Direction,const Quantity_NameOfColor Name,const Standard_Boolean Headlight):V3d_PositionLight(VM) { 
  Quantity_Color C(Name) ;
  Graphic3d_Vertex T(0.,0.,0.) ;
  Graphic3d_Vertex P ;
  Graphic3d_Vector V = V3d::GetProjAxis(Direction) ;
  
  MyType = V3d_DIRECTIONAL ;
  MyLight = new Visual3d_Light(C,V, Headlight) ;
  // The initial target is chosen at random
  MyTarget = T;
// Position is found
  P.SetCoord(-V.X(),-V.Y(),-V.Z());
  MyDisplayPosition = P; 

}

V3d_DirectionalLight::V3d_DirectionalLight(const Handle(V3d_Viewer)& VM,const Standard_Real Xt,const Standard_Real Yt,const Standard_Real Zt,const Standard_Real Xp,const Standard_Real Yp,const Standard_Real Zp,const Quantity_NameOfColor Name,const Standard_Boolean Headlight):V3d_PositionLight(VM) { 
  Quantity_Color C(Name) ;
  Graphic3d_Vertex T(Xt,Yt,Zt) ;
  Graphic3d_Vertex P(Xp,Yp,Zp) ;
  Graphic3d_Vector V(P,T);
  
  MyType = V3d_DIRECTIONAL ;
  V.Normalize();
  MyLight = new Visual3d_Light(C,V, Headlight) ;
  MyTarget = T;
  MyDisplayPosition = P;
}

//-Methods, in order

void V3d_DirectionalLight::SetDirection(const V3d_TypeOfOrientation Direction) {

  Graphic3d_Vector V = V3d::GetProjAxis(Direction) ;
  MyLight->SetDirection(V) ;
}

void V3d_DirectionalLight::SetDirection(const Standard_Real Vx, const Standard_Real Vy, const Standard_Real Vz) {

  V3d_BadValue_Raise_if( sqrt( Vx*Vx + Vy*Vy + Vz*Vz ) <= 0.,"V3d_DirectionalLight::SetDirection, null vector" );

  Graphic3d_Vector V(Vx,Vy,Vz) ;
  V.Normalize() ;
  MyLight->SetDirection(V) ;
}

void V3d_DirectionalLight::SetDisplayPosition(const Standard_Real X, const Standard_Real Y, const Standard_Real Z) {

  Standard_Real Xt,Yt,Zt;

  MyDisplayPosition.SetCoord(X,Y,Z) ;
  MyTarget.Coord(Xt,Yt,Zt);
  SetDirection(Xt-X,Yt-Y,Zt-Z);
}

void V3d_DirectionalLight::SetPosition(const Standard_Real Xp, const Standard_Real Yp, const Standard_Real Zp) {

  SetDisplayPosition (Xp,Yp,Zp);
}

void V3d_DirectionalLight::Position(Standard_Real& Xp, Standard_Real& Yp, Standard_Real& Zp)const  {

  DisplayPosition (Xp,Yp,Zp) ;
}

void V3d_DirectionalLight::DisplayPosition(Standard_Real& Xp, Standard_Real& Yp, Standard_Real& Zp)const  {

  MyDisplayPosition.Coord(Xp,Yp,Zp) ;
}

void V3d_DirectionalLight::Symbol (const Handle(Graphic3d_Group)& gsymbol, const Handle(V3d_View)& aView) const
{
  Standard_Real Xi,Yi,Zi,Xf,Yf,Zf,Rayon,PXT,PYT,X,Y,Z,XT,YT,ZT;
  Standard_Real A,B,C,Dist,Beta,CosBeta,SinBeta,Coef,X1,Y1,Z1;
  Standard_Real DX,DY,DZ,VX,VY,VZ;
  Standard_Integer IXP,IYP,j;
  TColStd_Array2OfReal MatRot(0,2,0,2);

  aView->Proj(VX,VY,VZ);
  this->DisplayPosition(Xi,Yi,Zi);
  Rayon = this->Radius();
  aView->Project(Xi,Yi,Zi,PXT,PYT); 
  aView->Convert(PXT,PYT,IXP,IYP);
//  Coordinated 3d in the plane of projection of the source.
  aView->Convert(IXP,IYP,XT,YT,ZT);
  aView->Convert(PXT,PYT+Rayon,IXP,IYP);
  aView->Convert(IXP,IYP,X,Y,Z);
  X = X+Xi-XT; Y = Y+Yi-YT; Z = Z+Zi-ZT;
  Dist = Sqrt( Square(X-Xi) + Square(Y-Yi) + Square(Z-Zi) );
//  Axis of rotation.
  A = (X-Xi)/Dist;
  B = (Y-Yi)/Dist;
  C = (Z-Zi)/Dist;

//  A sphere is drawn
  V3d::CircleInPlane(gsymbol,Xi,Yi,Zi,VX,VY,VZ,Rayon/40.);
  for( j=1 ; j<=3 ; j++ ) {
    Beta = j * M_PI / 4.;
    CosBeta = Cos(Beta);
    SinBeta = Sin(Beta);
    Coef = 1. - CosBeta;
    MatRot(0,0) =  A * A + (1. - A * A) * CosBeta;
    MatRot(0,1) = -C * SinBeta + Coef * A * B;
    MatRot(0,2) =  B * SinBeta + Coef * A * C;
    MatRot(1,0) =  C * SinBeta + Coef * A * B; 
    MatRot(1,1) =  B * B + (1. - B * B) * CosBeta;
    MatRot(1,2) = -A * SinBeta + Coef * B * C;
    MatRot(2,0) = -B * SinBeta + Coef * A * C;
    MatRot(2,1) =  A * SinBeta + Coef * B * C;
    MatRot(2,2) =  C * C + (1. - C * C) * CosBeta;
    Xf = Xi * MatRot(0,0) + Yi * MatRot(0,1) + Zi * MatRot(0,2);
    Yf = Xi * MatRot(1,0) + Yi * MatRot(1,1) + Zi * MatRot(1,2);
    Zf = Xi * MatRot(2,0) + Yi * MatRot(2,1) + Zi * MatRot(2,2);
//    Rotation of the normal
    X1 = VX * MatRot(0,0) + VY * MatRot(0,1) + VZ * MatRot(0,2);
    Y1 = VX * MatRot(1,0) + VY * MatRot(1,1) + VZ * MatRot(1,2);
    Z1 = VX * MatRot(2,0) + VY * MatRot(2,1) + VZ * MatRot(2,2);
    VX = X1 + Xi - Xf ; VY = Y1 + Yi - Yf ; VZ = Z1 + Zi - Zf;
    V3d::CircleInPlane(gsymbol,Xi,Yi,Zi,VX,VY,VZ,Rayon/40.);
  }

//  The arrow is drawn
  Rayon = this->Radius();
  this->Direction(DX,DY,DZ);
  X = Xi + DX*Rayon/10.; Y = Yi + DY*Rayon/10.; Z = Zi + DZ*Rayon/10.;

  Handle(Graphic3d_ArrayOfSegments) aPrims = new Graphic3d_ArrayOfSegments(2);
  aPrims->AddVertex(Standard_ShortReal(Xi),Standard_ShortReal(Yi),Standard_ShortReal(Zi));
  aPrims->AddVertex(Standard_ShortReal(X),Standard_ShortReal(Y),Standard_ShortReal(Z));
  gsymbol->AddPrimitiveArray(aPrims);

  V3d::ArrowOfRadius(gsymbol, X, Y, Z, DX, DY, DZ, M_PI / 15., Rayon / 20.);
}

void V3d_DirectionalLight::Display( const Handle(V3d_View)& aView,
                                    const V3d_TypeOfRepresentation TPres) {

  Standard_Real X,Y,Z,Rayon;
  Standard_Real X0,Y0,Z0,VX,VY,VZ;
  Standard_Real X1,Y1,Z1;
  Standard_Real DXRef,DYRef,DZRef,DXini,DYini,DZini;
  Standard_Real R1,G1,B1;
  V3d_TypeOfRepresentation Pres;
  V3d_TypeOfUpdate UpdSov;

//  Creation of a structure of markable elements (position of the
//  light, and the domain of lighting represented by a circle)
//  Creation of a structure of non-markable elements (target, meridian and 
//  parallel).

    Pres = TPres;
    Handle(V3d_Viewer) TheViewer = aView->Viewer();
    UpdSov = TheViewer->UpdateMode();
    TheViewer->SetUpdateMode(V3d_WAIT);
    if (!MyGraphicStructure.IsNull()) {
       MyGraphicStructure->Disconnect(MyGraphicStructure1);
       MyGraphicStructure->Clear();
       MyGraphicStructure1->Clear();
       if (Pres == V3d_SAMELAST) Pres = MyTypeOfRepresentation;
    }
    else {
      if (Pres == V3d_SAMELAST) Pres = V3d_SIMPLE;
      Handle(Graphic3d_Structure) slight = new Graphic3d_Structure(TheViewer->Viewer());
      MyGraphicStructure = slight;
      Handle(Graphic3d_Structure) snopick = new Graphic3d_Structure(TheViewer->Viewer()); 
      MyGraphicStructure1 = snopick;
    }
  
  Handle(Graphic3d_Group) glight  = new Graphic3d_Group(MyGraphicStructure);
  Handle(Graphic3d_Group) gsphere;
  if (Pres == V3d_COMPLETE || Pres == V3d_PARTIAL) gsphere = new Graphic3d_Group(MyGraphicStructure);
  
  Handle(Graphic3d_Group) gnopick = new Graphic3d_Group(MyGraphicStructure1);
  MyGraphicStructure1->SetPick(Standard_False);
  
  X0 = MyTarget.X();
  Y0 = MyTarget.Y();
  Z0 = MyTarget.Z();

//Display of the position of the light.

  this->Color(Quantity_TOC_RGB,R1,G1,B1);
  Quantity_Color Col1(R1,G1,B1,Quantity_TOC_RGB);
  Handle(Graphic3d_AspectLine3d) Asp1 = new Graphic3d_AspectLine3d();
  Asp1->SetColor(Col1);
  glight->SetPrimitivesAspect(Asp1);
  this->Symbol(glight,aView);
  
  // Display of the markable sphere (limit at the circle).

  if (Pres == V3d_COMPLETE || Pres == V3d_PARTIAL) {
    
    Rayon = this->Radius(); 
    aView->Proj(VX,VY,VZ);
    V3d::CircleInPlane(gsphere,X0,Y0,Z0,VX,VY,VZ,Rayon);
    
//Display of the meridian

    Quantity_Color Col2(Quantity_NOC_GREEN);
    Handle(Graphic3d_AspectLine3d) Asp2 = new Graphic3d_AspectLine3d
      (Col2,Aspect_TOL_SOLID,1.);
    gnopick->SetPrimitivesAspect(Asp2);
    
//    Definition of the axis of circle
    aView->Up(DXRef,DYRef,DZRef);
    this->DisplayPosition(X,Y,Z);
    DXini = X-X0; DYini = Y-Y0; DZini = Z-Z0;
    VX = DYRef*DZini - DZRef*DYini;
    VY = DZRef*DXini - DXRef*DZini;
    VZ = DXRef*DYini - DYRef*DXini;
    
    V3d::CircleInPlane(gnopick,X0,Y0,Z0,VX,VY,VZ,Rayon);
      
//  Display of the parallel

//    Definition of the axis of circle
    aView->Proj(VX,VY,VZ);
    aView->Up(X1,Y1,Z1);
    DXRef = VY * Z1 - VZ * Y1;
    DYRef = VZ * X1 - VX * Z1;
    DZRef = VX * Y1 - VY * X1;
    this->DisplayPosition(X,Y,Z);
    DXini = X-X0; DYini = Y-Y0; DZini = Z-Z0;
    VX = DYRef*DZini - DZRef*DYini;
    VY = DZRef*DXini - DXRef*DZini;
    VZ = DXRef*DYini - DYRef*DXini;
    
    V3d::CircleInPlane(gnopick,X0,Y0,Z0,VX,VY,VZ,Rayon);
    
  }
  
  MyGraphicStructure->Connect(MyGraphicStructure1,Graphic3d_TOC_DESCENDANT);
//    cout << "MyGraphicStructure exploration \n" << flush; MyGraphicStructure->Exploration();
  MyTypeOfRepresentation = Pres;
  MyGraphicStructure->Display();
  TheViewer->SetUpdateMode(UpdSov);
}

void V3d_DirectionalLight::Direction(Standard_Real& Vx, Standard_Real& Vy, Standard_Real& Vz)const  {
  
  Quantity_Color C ;
  Graphic3d_Vector V ;

  MyLight->Values(C,V) ;
  V.Coord(Vx,Vy,Vz) ;
}
