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

#include <DrawTrSurf_BSplineSurface.ixx>
#include <DrawTrSurf_BSplineCurve.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Draw_MarkerShape.hxx>
#include <GeomAdaptor_HSurface.hxx>
#include <GeomAdaptor_Surface.hxx>
#include <Adaptor3d_IsoCurve.hxx>
#include <gp_Pnt2d.hxx>

#include <TColgp_Array2OfPnt.hxx>
#include <TColStd_Array1OfReal.hxx>



DrawTrSurf_BSplineSurface::DrawTrSurf_BSplineSurface (
   const Handle(Geom_BSplineSurface)& S)
   : DrawTrSurf_Surface (S, S->NbUKnots()-2, S->NbVKnots()-2, 
                         Draw_jaune, Draw_bleu, 30, 0.05, 0){

     drawPoles = Standard_True;
     drawKnots = Standard_True;
     knotsIsos  = Standard_True;
     knotsForm = Draw_Losange;
     knotsLook = Draw_violet;
     knotsDim  = 5;
     polesLook = Draw_rouge;
   }




   DrawTrSurf_BSplineSurface::DrawTrSurf_BSplineSurface (
   const Handle(Geom_BSplineSurface)& S, const Draw_Color& BoundsColor,
   const Draw_Color& IsosColor, const Draw_Color& PolesColor,
   const Draw_Color& KnotsColor, const Draw_MarkerShape KnotsShape,
   const Standard_Integer KnotsSize, const Standard_Boolean ShowPoles, const Standard_Boolean ShowKnots,
   const Standard_Integer Discret, const Standard_Real Deflection, const Standard_Integer DrawMode) 
   : DrawTrSurf_Surface (S, S->NbUKnots()-2, S->NbVKnots()-2, BoundsColor,
                         IsosColor, Discret, Deflection, DrawMode){

     knotsIsos  = Standard_True;
     drawPoles = ShowPoles;
     drawKnots = ShowKnots;
     knotsForm = KnotsShape;
     knotsLook = KnotsColor;
     knotsDim  = KnotsSize;
     polesLook = PolesColor;
   }



   DrawTrSurf_BSplineSurface::DrawTrSurf_BSplineSurface (
   const Handle(Geom_BSplineSurface)& S, const Standard_Integer NbUIsos,
   const Standard_Integer NbVIsos, const Draw_Color& BoundsColor,
   const Draw_Color& IsosColor, const Draw_Color& PolesColor,
   const Draw_Color& KnotsColor, const Draw_MarkerShape KnotsShape,
   const Standard_Integer KnotsSize, const Standard_Boolean ShowPoles, const Standard_Boolean ShowKnots,
   const Standard_Integer Discret, const Standard_Real Deflection, const Standard_Integer DrawMode) 
   : DrawTrSurf_Surface (S, Abs(NbUIsos), Abs(NbVIsos), BoundsColor, 
                         IsosColor, Discret, Deflection, DrawMode){

     knotsIsos  = Standard_False;
     drawPoles  = ShowPoles;
     drawKnots  = ShowKnots;
     knotsForm  = KnotsShape;
     knotsLook  = KnotsColor;
     knotsDim   = KnotsSize;
     polesLook  = PolesColor;
   }




void DrawTrSurf_BSplineSurface::DrawOn (Draw_Display& dis) const {
    
  Handle(Geom_BSplineSurface) S = Handle(Geom_BSplineSurface)::DownCast(surf);
  Standard_Integer i, j;

  Standard_Real Ua,Ub,Va,Vb;
  S->Bounds(Ua,Ub,Va,Vb);

  if (drawPoles) {
    Standard_Integer NbUPoles = S->NbUPoles();
    Standard_Integer NbVPoles = S->NbVPoles();
    dis.SetColor(polesLook);
    TColgp_Array2OfPnt SPoles (1, NbUPoles, 1, NbVPoles);
    S->Poles (SPoles);
    for (j = 1; j <= NbVPoles; j++) {
      dis.MoveTo(SPoles(1, j));
      for (i = 2; i <= NbUPoles; i++) {
	dis.DrawTo(SPoles(i, j));
      }
      if (S->IsUPeriodic())
	dis.DrawTo(SPoles(1,j));
    }
    for (i = 1; i <= NbUPoles; i++) {
      dis.MoveTo(SPoles(i, 1));
      for (j = 2; j <= NbVPoles; j++) {
	dis.DrawTo(SPoles(i, j));
      }
      if (S->IsVPeriodic())
	dis.DrawTo(SPoles(i,1));
    }
  }


  if (knotsIsos) {
    Standard_Integer first, last;
    Handle(GeomAdaptor_HSurface) HS = new GeomAdaptor_HSurface();
    HS->ChangeSurface().Load(surf);
    
    Adaptor3d_IsoCurve C(HS);

    dis.SetColor(isosLook);
    first = S->FirstUKnotIndex() + 1;
    last  = S->LastUKnotIndex() - 1;
    for (i = first; i <= last; i++) {
      DrawIsoCurveOn(C,GeomAbs_IsoU,S->UKnot(i),Va,Vb,dis);
    }
    first = S->FirstVKnotIndex() + 1;
    last  = S->LastVKnotIndex() - 1;
    for (j = first; j <= last; j++) {
      DrawIsoCurveOn(C,GeomAbs_IsoV,S->VKnot(j),Ua,Ub,dis);
    }
  }

  DrawTrSurf_Surface::DrawOn(dis,!knotsIsos);

  if (drawKnots) {
    Standard_Integer first, last;
    Standard_Integer NbUKnots = S->NbUKnots();
    TColStd_Array1OfReal SUKnots (1, NbUKnots);
    S->UKnots (SUKnots); 
    dis.SetColor(knotsLook);
    first = S->FirstUKnotIndex();
    last  = S->LastUKnotIndex();
    for (i = first; i <= last; i++) {
      dis.DrawMarker (S->Value (SUKnots(i), Va), knotsForm, knotsDim);
    }
    Standard_Integer NbVKnots = S->NbVKnots();
    TColStd_Array1OfReal SVKnots (1, NbVKnots);
    S->VKnots (SVKnots); 
    dis.SetColor(knotsLook);
    first = S->FirstVKnotIndex();
    last  = S->LastVKnotIndex();
    for (j = first; j <= last; j++) {
      dis.DrawMarker (S->Value (Ua, SVKnots(j)), knotsForm, knotsDim);
    }
  }
}







  void DrawTrSurf_BSplineSurface::ShowPoles () { drawPoles = Standard_True; }


  void DrawTrSurf_BSplineSurface::ShowKnots () { drawKnots = Standard_True; }


  void DrawTrSurf_BSplineSurface::ClearPoles () { drawPoles = Standard_False; }


  void DrawTrSurf_BSplineSurface::ShowKnotsIsos () { 
     knotsIsos = Standard_True;
     Handle(Geom_BSplineSurface) S = Handle(Geom_BSplineSurface)::DownCast(surf);
     nbUIsos = S->NbUKnots()-2;
     nbVIsos = S->NbVKnots()-2;
  }



  void DrawTrSurf_BSplineSurface::ClearIsos () { 

     knotsIsos = Standard_False;
     nbUIsos = 0;
     nbVIsos = 0;
  }


  void DrawTrSurf_BSplineSurface::ShowIsos (
  const Standard_Integer Nu, const Standard_Integer Nv) { 

     knotsIsos = Standard_False;
     nbUIsos = Abs(Nu);
     nbVIsos = Abs(Nv);
  }


  void DrawTrSurf_BSplineSurface::ClearKnots () { drawKnots = Standard_False; }


   void DrawTrSurf_BSplineSurface::FindPole (
   const Standard_Real X, const Standard_Real Y, const Draw_Display& D, const Standard_Real XPrec,
   Standard_Integer& UIndex, Standard_Integer& VIndex) const {

     Handle(Geom_BSplineSurface) bs = Handle(Geom_BSplineSurface)::DownCast(surf);
     gp_Pnt2d p1(X/D.Zoom(),Y/D.Zoom());
     Standard_Real Prec = XPrec / D.Zoom();
     UIndex++;
     VIndex++;
     Standard_Integer NbUPoles = bs->NbUPoles();
     Standard_Integer NbVPoles = bs->NbVPoles();
     while (VIndex <= NbVPoles) {
       while (UIndex <= NbUPoles) {
         if (D.Project(bs->Pole(UIndex, VIndex)).Distance(p1) <= Prec)
	   return;
         UIndex++;
       }
       UIndex = 1;
       VIndex++;
     }
     UIndex = VIndex = 0;
   }
 


   void DrawTrSurf_BSplineSurface::FindUKnot (
   const Standard_Real X, const Standard_Real Y, const Draw_Display& D, const Standard_Real Prec,
   Standard_Integer& UIndex) const {

     Handle(Geom_BSplineSurface) bs = Handle(Geom_BSplineSurface)::DownCast(surf);
     gp_Pnt2d p1(X,Y);
     UIndex++;
     Standard_Integer NbUKnots = bs->NbUKnots();
     Standard_Real U1, U2, V1, V2;
     surf->Bounds (U1, U2, V1, V2);
     while (UIndex <= NbUKnots) {
       if (D.Project(bs->Value(bs->UKnot(UIndex), V1)).Distance(p1) <= Prec)
	 return;
       UIndex++;
     }
     UIndex = 0;
   }


   void DrawTrSurf_BSplineSurface::FindVKnot (
   const Standard_Real X, const Standard_Real Y, const Draw_Display& D, const Standard_Real Prec,
   Standard_Integer& VIndex) const {


     Handle(Geom_BSplineSurface) bs = Handle(Geom_BSplineSurface)::DownCast(surf);
     gp_Pnt2d p1(X,Y);
     VIndex++;
     Standard_Integer NbVKnots = bs->NbVKnots();
     Standard_Real U1, U2, V1, V2;
     surf->Bounds (U1, U2, V1, V2);
     while (VIndex <= NbVKnots) {
       if (D.Project(bs->Value(U1, bs->VKnot(VIndex))).Distance(p1) <= Prec)
	 return;
       VIndex++;
     }
     VIndex = 0;
  }



//=======================================================================
//function : Copy
//purpose  : 
//=======================================================================

Handle(Draw_Drawable3D)  DrawTrSurf_BSplineSurface::Copy()const 
{
  Handle(DrawTrSurf_BSplineSurface) DS;
  if (!knotsIsos)
    DS = new DrawTrSurf_BSplineSurface
      (Handle(Geom_BSplineSurface)::DownCast(surf->Copy()),
       nbUIsos,nbVIsos,
       boundsLook,isosLook,polesLook,knotsLook,
       knotsForm,knotsDim,drawPoles,drawKnots,
       GetDiscretisation(),GetDeflection(),GetDrawMode());
  else
    DS = new DrawTrSurf_BSplineSurface
      (Handle(Geom_BSplineSurface)::DownCast(surf->Copy()),
       boundsLook,isosLook,polesLook,knotsLook,
       knotsForm,knotsDim,drawPoles,drawKnots,
       GetDiscretisation(),GetDeflection(),GetDrawMode());

  return DS;

}


