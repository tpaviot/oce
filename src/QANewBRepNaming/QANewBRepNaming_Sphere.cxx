// Created on: 1999-11-05
// Created by: Vladislav ROMASHKO
// Copyright (c) 1999-1999 Matra Datavision
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


#include <QANewBRepNaming_Sphere.ixx>
#include <QANewBRepNaming_Loader.hxx>
#include <TNaming_Builder.hxx>
#include <TDF_Label.hxx>
#include <TDF_TagSource.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Edge.hxx>
#include <Standard_NullObject.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopExp.hxx>
#include <TColStd_ListOfInteger.hxx>
#include <BRep_Tool.hxx>
#include <TNaming_NamedShape.hxx>

#ifdef MDTV_DEB
#include <TDataStd_Name.hxx>
#endif


//=======================================================================
//function : QANewBRepNaming_Sphere
//purpose  : 
//=======================================================================

QANewBRepNaming_Sphere::QANewBRepNaming_Sphere() {}

//=======================================================================
//function : QANewBRepNaming_Sphere
//purpose  : 
//=======================================================================

QANewBRepNaming_Sphere::QANewBRepNaming_Sphere(const TDF_Label& ResultLabel):QANewBRepNaming_TopNaming(ResultLabel) {}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void QANewBRepNaming_Sphere::Init(const TDF_Label& ResultLabel) {
  if(ResultLabel.IsNull())
    Standard_NullObject::Raise("QANewBRepNaming_Sphere::Init The Result label is Null ..."); 
  myResultLabel = ResultLabel;
}   

//=======================================================================
//function : Bottom
//purpose  : 
//=======================================================================

TDF_Label QANewBRepNaming_Sphere::Bottom() const {
  const TDF_Label& BottomL = ResultLabel().NewChild();
#ifdef MDTV_DEB
  TDataStd_Name::Set(BottomL, "Bottom");
#endif
  return BottomL;
}

//=======================================================================
//function : Top
//purpose  : 
//=======================================================================

TDF_Label QANewBRepNaming_Sphere::Top() const {
  const TDF_Label& TopL = ResultLabel().NewChild();
#ifdef MDTV_DEB
  TDataStd_Name::Set(TopL, "Top");
#endif
  return TopL;
}

//=======================================================================
//function : Lateral
//purpose  : 
//=======================================================================

TDF_Label QANewBRepNaming_Sphere::Lateral() const {
  const TDF_Label& LateralL = ResultLabel().NewChild();
#ifdef MDTV_DEB
  TDataStd_Name::Set(LateralL, "Lateral");
#endif
  return LateralL;
}

//=======================================================================
//function : StartSide
//purpose  : 
//=======================================================================

TDF_Label QANewBRepNaming_Sphere::StartSide() const {
  const TDF_Label& StartSideL = ResultLabel().NewChild();
#ifdef MDTV_DEB
  TDataStd_Name::Set(StartSideL, "StartSide");
#endif
  return StartSideL;
}

//=======================================================================
//function : EndSide
//purpose  : 
//=======================================================================

TDF_Label QANewBRepNaming_Sphere::EndSide() const {
  const TDF_Label& EndSideL = ResultLabel().NewChild();
#ifdef MDTV_DEB
  TDataStd_Name::Set(EndSideL, "EndSide");
#endif
  return EndSideL;
}

//=======================================================================
//function : Meridian
//purpose  : 
//=======================================================================

TDF_Label QANewBRepNaming_Sphere::Meridian() const {
  const TDF_Label& MeridianL = ResultLabel().NewChild();
#ifdef MDTV_DEB
  TDataStd_Name::Set(MeridianL, "Meridian");
#endif
  return MeridianL;
}

//=======================================================================
//function : Degenerated
//purpose  : 
//=======================================================================

TDF_Label QANewBRepNaming_Sphere::Degenerated() const {
  const TDF_Label& DegeneratedL = ResultLabel().NewChild();
#ifdef MDTV_DEB
  TDataStd_Name::Set(DegeneratedL, "Degenerated");
#endif
  return DegeneratedL;
}

//=======================================================================
//function : Load (Sphere)
//purpose  : 
//=======================================================================

void QANewBRepNaming_Sphere::Load (BRepPrimAPI_MakeSphere& mkSphere, 
			      const QANewBRepNaming_TypeOfPrimitive3D Type) const
{
  BRepPrim_Sphere& S = mkSphere.Sphere();

  Handle(TDF_TagSource) Tagger = TDF_TagSource::Set(ResultLabel());
  if (Tagger.IsNull()) return;
  Tagger->Set(0);

  TNaming_Builder Builder (ResultLabel());
  if (Type == QANewBRepNaming_SOLID) Builder.Generated (mkSphere.Solid());
  else if (Type == QANewBRepNaming_SHELL) Builder.Generated (mkSphere.Shell());
  else {
#ifdef MDTV_DEB
    cout<<"QANewBRepNaming_Sphere::Load(): Unexpected type of result"<<endl;
    Builder.Generated (mkSphere.Shape());
#endif
  }

  if (S.HasBottom()) {
    TopoDS_Face BottomFace = S.BottomFace();
    TNaming_Builder BottomFaceIns(Bottom()); 
    BottomFaceIns.Generated(BottomFace); 
  }

  if (S.HasTop()) {
    TopoDS_Face TopFace = S.TopFace();
    TNaming_Builder TopFaceIns(Top()); 
    TopFaceIns.Generated (TopFace); 
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

  TopTools_IndexedMapOfShape LateralEdges;
  TopExp::MapShapes(LateralFace, TopAbs_EDGE, LateralEdges);
  Standard_Integer i = 1;
  TColStd_ListOfInteger goodEdges;
  for (; i <= LateralEdges.Extent(); i++) {
    if (!BRep_Tool::Degenerated(TopoDS::Edge(LateralEdges.FindKey(i)))) goodEdges.Append(i);
    else {
      TNaming_Builder DegeneratedBuilder(Degenerated()); 
      DegeneratedBuilder.Generated(LateralEdges.FindKey(i));
    }      
  }
  if (goodEdges.Extent() == 1) {
    const TopoDS_Edge& aLateralEdge = TopoDS::Edge(LateralEdges.FindKey(goodEdges.First()));
    TNaming_Builder MeridianBuilder(Meridian());
    MeridianBuilder.Generated(LateralFace, aLateralEdge);
  }

}

