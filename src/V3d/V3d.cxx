// Created by: GG
// Copyright (c) 1991-1999 Matra Datavision
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

// Modified     23/02/98 : FMN ; Remplacement PI par Standard_PI
//              02.15.100 : JR : Clutter


//-Version

//-Design       

//-Warning     

//-References

//-Language     C++ 2.1

//-Declarations

// for the class
#include <V3d.ixx>
#include <V3d_View.hxx>

#include <Quantity_NameOfColor.hxx>
#include <Aspect_Grid.hxx>
#include <Aspect_Window.hxx>
#include <Graphic3d_ArrayOfPolylines.hxx>
#include <Graphic3d_Group.hxx>
#include <Graphic3d_Structure.hxx>
#include <Graphic3d_AspectLine3d.hxx>
#include <Graphic3d_AspectText3d.hxx>
#include <Visual3d_HSetOfView.hxx>
#include <Visual3d_SetIteratorOfSetOfView.hxx>
#include <Visual3d_View.hxx>
#include <Visual3d_ViewManager.hxx>

Graphic3d_Vector V3d::GetProjAxis(const V3d_TypeOfOrientation Orientation) {
Standard_Real Xpn=0,Ypn=0,Zpn=0 ;
Graphic3d_Vector Vec ;

        switch (Orientation) {
            case V3d_Xpos :
                Xpn = 1. ; Ypn = 0. ; Zpn = 0. ;
                break ;
            case V3d_Ypos :
                Xpn = 0. ; Ypn = 1. ; Zpn = 0. ;
                break ;
            case V3d_Zpos :
                Xpn = 0. ; Ypn = 0. ; Zpn = 1. ;
                break ;
            case V3d_Xneg :
                Xpn = -1. ; Ypn = 0. ; Zpn = 0. ;
                break ;
            case V3d_Yneg :
                Xpn = 0. ; Ypn = -1. ; Zpn = 0. ;
                break ;
            case V3d_Zneg :
                Xpn = 0. ; Ypn = 0. ; Zpn = -1. ;
                break ;
            case V3d_XposYposZpos :
                Xpn = 1. ; Ypn = 1. ; Zpn = 1. ;
                break ;
            case V3d_XposYposZneg :
                Xpn = 1. ; Ypn = 1. ; Zpn = -1. ;
                break ;
            case V3d_XposYnegZpos :
                Xpn = 1. ; Ypn = -1. ; Zpn = 1. ;
                break ;
            case V3d_XposYnegZneg :
                Xpn = 1. ; Ypn = -1. ; Zpn = -1. ;
                break ;
            case V3d_XnegYposZpos :
                Xpn = -1. ; Ypn = 1. ; Zpn = 1. ;
                break ;
            case V3d_XnegYposZneg :
                Xpn = -1. ; Ypn = 1. ; Zpn = -1. ;
                break ;
            case V3d_XnegYnegZpos :
                Xpn = -1. ; Ypn = -1. ; Zpn = 1. ;
                break ;
            case V3d_XnegYnegZneg :
                Xpn = -1. ; Ypn = -1. ; Zpn = -1. ;
                break ;
            case V3d_XposYpos :
                Xpn = 1. ; Ypn = 1. ; Zpn = 0. ;
                break ;
            case V3d_XposYneg :
                Xpn = 1. ; Ypn = -1. ; Zpn = 0. ;
                break ;
            case V3d_XnegYpos :
                Xpn = -1. ; Ypn = 1. ; Zpn = 0. ;
                break ;
            case V3d_XnegYneg :
                Xpn = -1. ; Ypn = -1. ; Zpn = 0. ;
                break ;
            case V3d_XposZpos :
                Xpn = 1. ; Ypn = 0. ; Zpn = 1. ;
                break ;
            case V3d_XposZneg :
                Xpn = 1. ; Ypn = 0. ; Zpn = -1. ;
                break ;
            case V3d_XnegZpos :
                Xpn = -1. ; Ypn = 0. ; Zpn = 1. ;
                break ;
            case V3d_XnegZneg :
                Xpn = -1. ; Ypn = 0. ; Zpn = -1. ;
                break ;
            case V3d_YposZpos :
                Xpn = 0. ; Ypn = 1. ; Zpn = 1. ;
                break ;
            case V3d_YposZneg :
                Xpn = 0. ; Ypn = 1. ; Zpn = -1. ;
                break ;
            case V3d_YnegZpos :
                Xpn = 0. ; Ypn = -1. ; Zpn = 1. ;
                break ;
            case V3d_YnegZneg :
                Xpn = 0. ; Ypn = -1. ; Zpn = -1. ;
                break ;
        }
        Vec.SetCoord(Xpn,Ypn,Zpn) ; Vec.Normalize() ;
        return Vec ;
}

void V3d::ArrowOfRadius(const Handle(Graphic3d_Group)& garrow,const Standard_Real X0,const Standard_Real Y0,const Standard_Real Z0,const Standard_Real Dx,const Standard_Real Dy,const Standard_Real Dz,const Standard_Real Alpha,const Standard_Real Lng)
{
  Standard_Real Xc,Yc,Zc,Xi,Yi,Zi,Xj,Yj,Zj;
  Standard_Real Xn,Yn,Zn,X,Y,Z,X1,Y1,Z1,Norme;
  const Standard_Integer NbPoints = 10;

//      Centre du cercle base de la fleche :
  Xc = X0 - Dx * Lng;
  Yc = Y0 - Dy * Lng;
  Zc = Z0 - Dz * Lng;

//      Construction d'un repere i,j pour le cercle:
  Xn=0., Yn=0., Zn=0.;

  if ( Abs(Dx) <= Abs(Dy) && Abs(Dx) <= Abs(Dz)) Xn=1.;
  else if ( Abs(Dy) <= Abs(Dz) && Abs(Dy) <= Abs(Dx)) Yn=1.;
  else Zn=1.;
  Xi = Dy * Zn - Dz * Yn;
  Yi = Dz * Xn - Dx * Zn;
  Zi = Dx * Yn - Dy * Xn;

  Norme = Sqrt ( Xi*Xi + Yi*Yi + Zi*Zi );
  Xi= Xi / Norme; Yi = Yi / Norme; Zi = Zi/Norme;

  Xj = Dy * Zi - Dz * Yi;
  Yj = Dz * Xi - Dx * Zi;
  Zj = Dx * Yi - Dy * Xi;

  Handle(Graphic3d_ArrayOfPolylines) aPrims = new Graphic3d_ArrayOfPolylines(3*NbPoints,NbPoints);

  Standard_Integer i;
  const Standard_Real Tg = Tan(Alpha);
  for (i = 1; i <= NbPoints; i++)
  {
    const Standard_Real cosinus = Cos ( 2. * M_PI / NbPoints * (i-1) );
    const Standard_Real sinus = Sin ( 2. * M_PI / NbPoints * (i-1) );

    X = Xc + (cosinus * Xi + sinus * Xj) * Lng * Tg;
    Y = Yc + (cosinus * Yi + sinus * Yj) * Lng * Tg;
    Z = Zc + (cosinus * Zi + sinus * Zj) * Lng * Tg;

    if(i==1) { X1=X, Y1=Y, Z1=Z; }
    else aPrims->AddVertex(X,Y,Z);
    aPrims->AddBound(3);
    aPrims->AddVertex(X0,Y0,Z0);
    aPrims->AddVertex(X,Y,Z);
  }
  aPrims->AddVertex(X1,Y1,Z1);

  garrow->AddPrimitiveArray(aPrims);
}


void V3d::CircleInPlane(const Handle(Graphic3d_Group)& gcircle,const Standard_Real X0,const Standard_Real Y0,const Standard_Real Z0,const Standard_Real DX,const Standard_Real DY,const Standard_Real DZ,const Standard_Real Rayon)
{
  Standard_Real Norme = Sqrt ( DX*DX + DY*DY + DZ*DZ );
  if ( Norme >= 0.0001 )
  {
    Standard_Real VX,VY,VZ,X,Y,Z,Xn,Yn,Zn,Xi,Yi,Zi,Xj,Yj,Zj;

    VX= DX/Norme; VY = DY/Norme; VZ = DZ/Norme;

//Construction of marker i,j for the circle:
    Xn=0., Yn=0., Zn=0.;   
    if ( Abs(VX) <= Abs(VY) && Abs(VX) <= Abs(VZ)) Xn=1.;
    else if ( Abs(VY) <= Abs(VZ) && Abs(VY) <= Abs(VX)) Yn=1.;
    else Zn=1.;
    Xi = VY * Zn - VZ * Yn;
    Yi = VZ * Xn - VX * Zn;
    Zi = VX * Yn - VY * Xn;

    Norme = Sqrt ( Xi*Xi + Yi*Yi + Zi*Zi );
    Xi= Xi / Norme; Yi = Yi / Norme; Zi = Zi/Norme;

    Xj = VY * Zi - VZ * Yi;
    Yj = VZ * Xi - VX * Zi;
    Zj = VX * Yi - VY * Xi;      

    const Standard_Integer NFACES = 30;
    Handle(Graphic3d_ArrayOfPolylines) aPrims = new Graphic3d_ArrayOfPolylines(NFACES+1);

    Standard_Integer i = 0;
    Standard_Real Alpha = 0.;
    const Standard_Real Dalpha = 2. * M_PI / NFACES;
    for (; i <= NFACES; i++, Alpha += Dalpha)
    {
      const Standard_Real cosinus = Cos(Alpha);
      const Standard_Real sinus = Sin(Alpha);

      X = X0 + (cosinus * Xi + sinus * Xj) * Rayon;
      Y = Y0 + (cosinus * Yi + sinus * Yj) * Rayon;
      Z = Z0 + (cosinus * Zi + sinus * Zj) * Rayon;

      aPrims->AddVertex(X,Y,Z);
    }
    gcircle->AddPrimitiveArray(aPrims);
  }
}


void V3d::SwitchViewsinWindow(const Handle(V3d_View)& aPreviousView,
                              const Handle(V3d_View)& aNextView) {
  aPreviousView->Viewer()->SetViewOff(aPreviousView);
  if(!aNextView->IfWindow())
    aNextView->SetWindow(aPreviousView->Window());
  aNextView->Viewer()->SetViewOn(aNextView);
    
}
void V3d::DrawSphere(const Handle(V3d_Viewer)& aViewer,const Quantity_Length ray)
{
  const Standard_Boolean inf = ray < 0;
  const Standard_Real aRadius = Standard_ShortReal(Abs(ray));
  Handle(Graphic3d_Structure) Struct = new Graphic3d_Structure(aViewer->Viewer()) ;
  Handle(Graphic3d_Group) Group = new Graphic3d_Group(Struct) ;

  Handle(Graphic3d_AspectLine3d) LineAttrib = new Graphic3d_AspectLine3d() ;
  LineAttrib->SetColor(Quantity_Color(Quantity_NOC_YELLOW));
  Struct->SetPrimitivesAspect(LineAttrib) ;

  const Standard_Integer NFACES = 30;
  Handle(Graphic3d_ArrayOfPolylines) aPrims = new Graphic3d_ArrayOfPolylines(NFACES*(NFACES+1),NFACES);

  const Standard_Real Dbeta = 2. * M_PI / NFACES;
  const Standard_Real Dalpha = 2. * M_PI / NFACES;
  Standard_ShortReal X,Y,Z,X0,Y0,Z0;
  Standard_Real R, Alpha, Beta = 0.;
  Standard_Integer i,j ;
  for( j=0; j<NFACES/2 ; j++, Beta += Dbeta ) {
    aPrims->AddBound(NFACES+1);
    R = aRadius*sin(Beta);
    Z = Standard_ShortReal(aRadius*cos(Beta));
    for( i=0, Alpha = 0.; i<NFACES; i++, Alpha += Dalpha ) {
      X = Standard_ShortReal(R*cos(Alpha));
      Y = Standard_ShortReal(R*sin(Alpha));
      aPrims->AddVertex(X,Y,Z);
      if (i==0) { X0=X, Y0=Y, Z0=Z; }
    }
    aPrims->AddVertex(X0,Y0,Z0);
  }
  for( j=0; j<NFACES/2 ; j++, Beta += Dbeta ) {
    aPrims->AddBound(NFACES+1);
    R = aRadius*sin(Beta);
    Y = Standard_ShortReal(aRadius*cos(Beta));
    Beta += Dbeta ;
    for( i=0, Alpha = 0.; i<NFACES; i++, Alpha += Dalpha ) {
      X = Standard_ShortReal(R*cos(Alpha));
      Z = Standard_ShortReal(R*sin(Alpha));
      aPrims->AddVertex(X,Y,Z);
      if (i==0) { X0=X, Y0=Y, Z0=Z; }
    }
    aPrims->AddVertex(X0,Y0,Z0);
  }
  Group->AddPrimitiveArray(aPrims);
  if(inf) Struct->SetInfiniteState(Standard_True);
  Struct->Display();
  aViewer->Update();
}

void V3d::SetPlane(const Handle(V3d_Viewer)& aViewer, 
                   const Standard_Real x1,
                   const Standard_Real y1,
                   const Standard_Real z1,
                   const Standard_Real x2,
                   const Standard_Real y2,
                   const Standard_Real z2) {

  gp_Ax3 a(gp_Pnt(0.,0.,0),gp_Dir(x1,y1,z1),gp_Dir(x2,y2,z2));
  aViewer->SetPrivilegedPlane(a);

}
void V3d::PickGrid(const Handle(V3d_Viewer)& aViewer,
//                                const Quantity_Length ray) {
                                const Quantity_Length ) {
Standard_Real x1, y1, z1;
Standard_Real x2, y2, z2;
        cout << "Direction ? " << flush;
        cin >> x1; cin >> y1; cin >> z1;
        cout << "XDirection ? " << flush;
        cin >> x2; cin >> y2; cin >> z2;
Standard_Integer u, v;
        cout << "u, v ? " << flush;
        cin >> u; cin >> v;
        V3d::SetPlane (aViewer, x1, y1, z1, x2, y2, z2);

        // To restart the calculation on the new plane
        if (aViewer->Grid ()->IsActive ()) {
                Standard_Real xo, yo;
                Quantity_PlaneAngle angle;
                switch (aViewer->GridType ()) {
                        case Aspect_GT_Rectangular :
                                Standard_Real xstep, ystep;
                                aViewer->RectangularGridValues
                                        (xo, yo, xstep, ystep, angle);
                                aViewer->SetRectangularGridValues
                                        (xo, yo, xstep, ystep, angle);
                        break;
                        case Aspect_GT_Circular :
                                Standard_Real radiusstep;
                                Standard_Integer division;
                                aViewer->CircularGridValues
                                        (xo, yo, radiusstep, division, angle);
                                aViewer->SetCircularGridValues
                                        (xo, yo, radiusstep, division, angle);
                        break;
                }
        }

        for (aViewer->InitActiveViews ();
                aViewer->MoreActiveViews ();
                   aViewer->NextActiveViews()) {
Standard_Real X, Y, Z;
                aViewer->ActiveView ()->Convert (u, v, X, Y, Z);
        }
}
