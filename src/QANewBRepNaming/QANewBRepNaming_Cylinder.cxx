// Created on: 2000-10-31
// Created by: Vladislav ROMASHKO
// Copyright (c) 2000-2012 OPEN CASCADE SAS
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


#include <QANewBRepNaming_Cylinder.ixx>
#include <TNaming_Builder.hxx>
#include <Standard_NullObject.hxx>
#include <TopoDS_Solid.hxx>
#ifdef MDTV_DEB
#include <TDataStd_Name.hxx>
#endif

//=======================================================================
//function : QANewBRepNaming_Cylinder
//purpose  : 
//=======================================================================

QANewBRepNaming_Cylinder::QANewBRepNaming_Cylinder() {}

//=======================================================================
//function : QANewBRepNaming_Cylinder
//purpose  : 
//=======================================================================

QANewBRepNaming_Cylinder::QANewBRepNaming_Cylinder(const TDF_Label& ResultLabel):
       QANewBRepNaming_TopNaming(ResultLabel) {}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void QANewBRepNaming_Cylinder::Init(const TDF_Label& ResultLabel) {
  if(ResultLabel.IsNull())
    Standard_NullObject::Raise("QANewBRepNaming_Cylinder::Init The Result label is Null ..."); 
  myResultLabel = ResultLabel;
}    

//=======================================================================
//function : Bottom
//purpose  : 
//=======================================================================

TDF_Label QANewBRepNaming_Cylinder::Bottom() const {
#ifdef MDTV_DEB
  TDataStd_Name::Set(ResultLabel().FindChild(1, Standard_True), "Bottom");
#endif
  return ResultLabel().FindChild(1, Standard_True);
}

//=======================================================================
//function : Top
//purpose  : 
//=======================================================================

TDF_Label QANewBRepNaming_Cylinder::Top() const {
#ifdef MDTV_DEB
  TDataStd_Name::Set(ResultLabel().FindChild(2, Standard_True), "Top");
#endif
  return ResultLabel().FindChild(2, Standard_True);
}

//=======================================================================
//function : Lateral
//purpose  : 
//=======================================================================

TDF_Label QANewBRepNaming_Cylinder::Lateral() const {
#ifdef MDTV_DEB
  TDataStd_Name::Set(ResultLabel().FindChild(3, Standard_True), "Lateral");
#endif
  return ResultLabel().FindChild(3, Standard_True);
}

//=======================================================================
//function : StartSide
//purpose  : 
//=======================================================================

TDF_Label QANewBRepNaming_Cylinder::StartSide() const {
#ifdef MDTV_DEB
  TDataStd_Name::Set(ResultLabel().FindChild(4, Standard_True), "StartSide");
#endif
  return ResultLabel().FindChild(4, Standard_True);
}

//=======================================================================
//function : EndSide
//purpose  : 
//=======================================================================

TDF_Label QANewBRepNaming_Cylinder::EndSide() const {
#ifdef MDTV_DEB
  TDataStd_Name::Set(ResultLabel().FindChild(5, Standard_True), "EndSide");
#endif
  return ResultLabel().FindChild(5, Standard_True);
}

//=======================================================================
//function : Load (Cylinder)
//purpose  : 
//=======================================================================

void QANewBRepNaming_Cylinder::Load (BRepPrimAPI_MakeCylinder& mkCylinder,
				const QANewBRepNaming_TypeOfPrimitive3D Type) const
{
  BRepPrim_Cylinder& S = mkCylinder.Cylinder();

  if (S.HasBottom()) {
    TopoDS_Face BottomFace = S.BottomFace();
    TNaming_Builder BottomFaceIns(Bottom()); 
    BottomFaceIns.Generated(BottomFace); 
  }

  if (S.HasTop()) {
    TopoDS_Face TopFace = S.TopFace();
    TNaming_Builder TopFaceIns(Top()); 
    TopFaceIns.Generated(TopFace); 
  }

  TopoDS_Face LateralFace = S.LateralFace();
  TNaming_Builder LateralFaceIns(Lateral()); 
  LateralFaceIns.Generated(LateralFace); 

  if (S.HasSides()) {
    TopoDS_Face StartFace = S.StartFace();
    TNaming_Builder StartFaceIns(StartSide()); 
    StartFaceIns.Generated(StartFace); 
    TopoDS_Face EndFace = S.EndFace();
    TNaming_Builder EndFaceIns(EndSide()); 
    EndFaceIns.Generated(EndFace); 
  }

  TNaming_Builder Builder (ResultLabel());
  if (Type == QANewBRepNaming_SOLID) Builder.Generated (mkCylinder.Solid());
  else if (Type == QANewBRepNaming_SHELL) Builder.Generated (mkCylinder.Shell());
  else {
#ifdef DEB
    cout<<"QANewBRepNaming_Cylinder::Load(): Unexpected type of result"<<endl;
    Builder.Generated (mkCylinder.Shape());
#endif
  }
}

