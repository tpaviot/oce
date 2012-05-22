// Created on: 1998-10-29
// Created by: Jean Yves LEBEY
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


#include <TopOpeBRep_Hctxff2d.ixx>
#include <TopOpeBRep_define.hxx>
#include <TopOpeBRepTool_ShapeTool.hxx>
#include <TopAbs.hxx>
#include <TopoDS.hxx>

//=======================================================================
//function : TopOpeBRep_Hctxff2d
//purpose  : 
//=======================================================================
TopOpeBRep_Hctxff2d::TopOpeBRep_Hctxff2d() 
{
  myf1surf1F_sameoriented = Standard_True;
  myf2surf1F_sameoriented = Standard_True;
  mySurfacesSameOriented = Standard_False;
  myFacesSameOriented = Standard_False;
  myTol1 = 0.;
  myTol2 = 0.;
}

//=======================================================================
//function : SetFaces
//purpose  : 
//=======================================================================
void TopOpeBRep_Hctxff2d::SetFaces(const TopoDS_Face& F1,const TopoDS_Face& F2)
{
  Standard_Boolean newf1 = !F1.IsEqual(myFace1);
  Standard_Boolean newf2 = !F2.IsEqual(myFace2);
  Standard_Boolean yaduneuf = (newf1 || newf2); if (!yaduneuf) return;

  Standard_Boolean computerestriction = Standard_False;
  if (newf1) {
    if (mySurface1.IsNull()) mySurface1 = new BRepAdaptor_HSurface();
    mySurface1->ChangeSurface().Initialize(F1,computerestriction);
  }
  if (newf2) {
    if (mySurface2.IsNull()) mySurface2 = new BRepAdaptor_HSurface();
    mySurface2->ChangeSurface().Initialize(F2,computerestriction);
  }
  SetHSurfacesPrivate();
} // SetFaces


//=======================================================================
//function : SetHSurfaces
//purpose  : 
//=======================================================================
void TopOpeBRep_Hctxff2d::SetHSurfaces(const Handle(BRepAdaptor_HSurface)& HS1,
				       const Handle(BRepAdaptor_HSurface)& HS2)
{
  Standard_Boolean newf1 = Standard_False; Standard_Boolean newf2 = Standard_False;
  if (!HS1.IsNull()) newf1 = !HS1->ChangeSurface().Face().IsEqual(myFace1);
  if (!HS2.IsNull()) newf2 = !HS2->ChangeSurface().Face().IsEqual(myFace2);
  Standard_Boolean yaduneuf = (newf1 || newf2); if (!yaduneuf) return;
  
  mySurface1 = HS1;
  mySurface2 = HS2;
  SetHSurfacesPrivate();
} // SetHSurfaces

//=======================================================================
//function : SetHSurfacesPrivate
//purpose  : 
//=======================================================================
void TopOpeBRep_Hctxff2d::SetHSurfacesPrivate()
{
  BRepAdaptor_Surface& S1 = mySurface1->ChangeSurface();
  myFace1 = S1.Face();
  mySurfaceType1 = S1.GetType();

  BRepAdaptor_Surface& S2 = mySurface2->ChangeSurface(); 
  myFace2 = S2.Face(); 
  mySurfaceType2 = S2.GetType();
  
  mySurfacesSameOriented = Standard_True;
  myFacesSameOriented = Standard_True;  
  Standard_Boolean so11 = Standard_True; myf1surf1F_sameoriented = so11;
  Standard_Boolean so21 = Standard_True; myf2surf1F_sameoriented = so21;
  
  TopoDS_Face face1forward = myFace1; face1forward.Orientation(TopAbs_FORWARD);
  so11 = TopOpeBRepTool_ShapeTool::FacesSameOriented(face1forward,myFace1);
  myf1surf1F_sameoriented = so11; 
  so21 = TopOpeBRepTool_ShapeTool::FacesSameOriented(face1forward,myFace2);
  myf2surf1F_sameoriented = so21;
  
  mySurfacesSameOriented = TopOpeBRepTool_ShapeTool::SurfacesSameOriented(S1,S2);
  myFacesSameOriented = TopOpeBRepTool_ShapeTool::FacesSameOriented(myFace1,myFace2);
  
#ifdef DEB
  Standard_Integer DEBi = 0;
  if ( DEBi ) {
    cout<<"TopOpeBRep_Hctxff2d::SetSurfacesPrivate : ";
    cout<<"f1 "; TopAbs::Print(myFace1.Orientation(),cout);
    cout<< " / f1F : ";
    if (so11) cout<<"sameoriented"; else cout<<"difforiented"; cout<<endl;
    cout <<"  ";
    cout<<"f2 "; TopAbs::Print(myFace2.Orientation(),cout);
    cout<< " / f1F : ";
    if (so21) cout<<"sameoriented"; else cout<<"difforiented"; cout<<endl;
  }
#endif
} // SetHSurfacesPrivate

//=======================================================================
//function : SetTolerances
//purpose  : 
//=======================================================================

void TopOpeBRep_Hctxff2d::SetTolerances(const Standard_Real Tol1,const Standard_Real Tol2)
{
  myTol1 = Tol1;
  myTol2 = Tol2;
}

//=======================================================================
//function : GetTolerances
//purpose  : 
//=======================================================================

void TopOpeBRep_Hctxff2d::GetTolerances(Standard_Real& Tol1,Standard_Real& Tol2) const
{
  Tol1 = myTol1;
  Tol2 = myTol2;
}

//=======================================================================
//function : GetMaxTolerance
//purpose  : 
//=======================================================================
Standard_Real TopOpeBRep_Hctxff2d::GetMaxTolerance() const 
{
  Standard_Real tol = Max(myTol1,myTol2);
  return tol;
}

//=======================================================================
//function : Face
//purpose  : 
//=======================================================================
const TopoDS_Face& TopOpeBRep_Hctxff2d::Face(const Standard_Integer Index) const 
{
  if      ( Index == 1 ) return myFace1;
  else if ( Index == 2 ) return myFace2;
  else Standard_Failure::Raise("TopOpeBRep_Hctxff2d::Face");
  
  return myFace1;
}

//=======================================================================
//function : Surface
//purpose  : 
//=======================================================================
Handle(BRepAdaptor_HSurface) TopOpeBRep_Hctxff2d::HSurface(const Standard_Integer Index) const 
{
  if      ( Index == 1 ) return mySurface1;
  else if ( Index == 2 ) return mySurface2;
  else Standard_Failure::Raise("TopOpeBRep_Hctxff2d::HSurface");
  
  return mySurface1;
}

//=======================================================================
//function : SurfacesSameOriented
//purpose  : 
//=======================================================================
Standard_Boolean TopOpeBRep_Hctxff2d::SurfacesSameOriented () const
{
  return mySurfacesSameOriented;
}

//=======================================================================
//function : FacesSameOriented
//purpose  : 
//=======================================================================
Standard_Boolean TopOpeBRep_Hctxff2d::FacesSameOriented () const
{
  return myFacesSameOriented;
}

//=======================================================================
//function : FaceSameOrientedwithNatural1
//purpose  : 
//=======================================================================
Standard_Boolean TopOpeBRep_Hctxff2d::FaceSameOrientedWithRef (const Standard_Integer Index) const
{
  if      ( Index == 1 ) return myf1surf1F_sameoriented;
  else if ( Index == 2 ) return myf2surf1F_sameoriented;
  else Standard_Failure::Raise("TopOpeBRep_Hctxff2d::FSO");

  return Standard_True;
}
