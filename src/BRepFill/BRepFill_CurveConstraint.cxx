// Created on: 1997-10-31
// Created by: Joelle CHAUVET
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



#include <BRepFill_CurveConstraint.ixx>
#include <GeomPlate_CurveConstraint.hxx>
#include <GCPnts_AbscissaPoint.hxx>
#include <Adaptor2d_HCurve2d.hxx>
#include <Adaptor3d_HSurface.hxx>
#include <ProjLib_ProjectOnPlane.hxx>
#include <GeomAdaptor.hxx>
#include <GeomAPI.hxx>
#include <Geom_Plane.hxx>
#include <Precision.hxx>
#include <GeomAdaptor_HSurface.hxx>
#include <BRepAdaptor_HSurface.hxx>
#include <BRep_Tool.hxx>

#include <Geom2dAdaptor_HCurve.hxx>
#include <Adaptor2d_HCurve2d.hxx>
#include <ProjLib_ProjectedCurve.hxx>
//---------------------------------------------------------
//         Constructeurs avec courbe sur surface
//---------------------------------------------------------
BRepFill_CurveConstraint :: BRepFill_CurveConstraint (const Handle(Adaptor3d_HCurveOnSurface)& Boundary,
						const Standard_Integer Tang,
						const Standard_Integer NPt,
						const Standard_Real TolDist,
						const Standard_Real TolAng,
						const Standard_Real TolCurv
)
{ 
  myFrontiere=Boundary;
  myTolDist=TolDist;
  myTolAng=TolAng;
  myTolCurv=TolCurv;
  GeomLProp_SLProps SLP(2,TolDist);
  myLProp=SLP;
  myOrder=Tang;
  if ((Tang<-1)||(Tang>2))
    Standard_Failure::Raise("BRepFill : The continuity is not G0 G1 or G2"); 
  myNbPoints=NPt;
myConstG0=Standard_True;
myConstG1=Standard_True;
myConstG2=Standard_True;
 if (myFrontiere.IsNull())
    Standard_Failure::Raise("BRepFill_CurveConstraint : Curve must be on a Surface"); 
  Handle(Geom_Surface) Surf;
  Handle(GeomAdaptor_HSurface) GS1;
  GS1 = Handle(GeomAdaptor_HSurface)::DownCast(myFrontiere->ChangeCurve().GetSurface());
  if (!GS1.IsNull()) {
    Surf=GS1->ChangeSurface().Surface();
  }
  else {
    Handle(BRepAdaptor_HSurface) BS1;
    BS1=Handle(BRepAdaptor_HSurface)::DownCast(myFrontiere->ChangeCurve().GetSurface());
    Surf = BRep_Tool::Surface(BS1->ChangeSurface().Face());
  }
  myLProp.SetSurface(Surf);
}

//---------------------------------------------------------
//    Constructeurs avec courbe 3d (pour continuite G0 G-1)
//---------------------------------------------------------
BRepFill_CurveConstraint :: BRepFill_CurveConstraint (const Handle(Adaptor3d_HCurve)& Boundary,
						const Standard_Integer Tang, 
						const Standard_Integer NPt,
						const Standard_Real TolDist) 
: GeomPlate_CurveConstraint(Boundary,Tang,NPt,TolDist)

{ 
}





