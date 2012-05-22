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

// 25.12.98 pdn: adding empty constructor

#include <ShapeFix_ShapeTolerance.ixx>

#include <BRep_Tool.hxx>
#include <BRep_TVertex.hxx>
#include <BRep_TEdge.hxx>
#include <BRep_TFace.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>

#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>

//=======================================================================
//function : Constructor
//purpose  : 
//=======================================================================

ShapeFix_ShapeTolerance::ShapeFix_ShapeTolerance()
{
}  

//=======================================================================
//function : LimitTolerance
//purpose  : 
//=======================================================================

Standard_Boolean ShapeFix_ShapeTolerance::LimitTolerance(const TopoDS_Shape& shape,
                                                         const Standard_Real tmin,
                                                         const Standard_Real tmax,
                                                         const TopAbs_ShapeEnum styp) const
{
  if (shape.IsNull() || tmin < 0) return Standard_False;
  Standard_Boolean iamax = (tmax >= tmin);
  Standard_Real prec;
  Standard_Boolean fait = Standard_False;
  if (styp == TopAbs_VERTEX || styp == TopAbs_EDGE || styp == TopAbs_FACE) {
    for (TopExp_Explorer ex(shape,styp); ex.More(); ex.Next()) {
      TopoDS_Shape sh = ex.Current();
      int newtol = 0;
      if        (styp == TopAbs_VERTEX) {
	TopoDS_Vertex V = TopoDS::Vertex (sh);
	prec = BRep_Tool::Tolerance (V);
	if (iamax && prec > tmax) newtol = 1;
	else if     (prec < tmin) newtol = -1;
	if (newtol) {
	  const Handle(BRep_TVertex)& TV = *((Handle(BRep_TVertex)*)&V.TShape());
	  TV->Tolerance( (newtol > 0 ? tmax : tmin) );
	  fait = Standard_True;
	}
     } else if (styp == TopAbs_EDGE) {
	TopoDS_Edge   E = TopoDS::Edge   (sh);
	prec = BRep_Tool::Tolerance (E);
	if (iamax && prec > tmax) newtol = 1;
	else if     (prec < tmin) newtol = -1;
	if (newtol) {
	  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*)&E.TShape());
	  TE->Tolerance( (newtol > 0 ? tmax : tmin) );
	  fait = Standard_True;
	}
      } else if (styp == TopAbs_FACE) {
	TopoDS_Face   F = TopoDS::Face   (sh);
	prec = BRep_Tool::Tolerance (F);
	if (iamax && prec > tmax) newtol = 1;
	else if     (prec < tmin) newtol = -1;
	if (newtol) {
	  const Handle(BRep_TFace)& TF = *((Handle(BRep_TFace)*)&F.TShape());
	  TF->Tolerance( (newtol > 0 ? tmax : tmin) );
	  fait = Standard_True;
	}
      }
    }
  } else if (styp == TopAbs_WIRE) {
    for (TopExp_Explorer ex(shape,TopAbs_EDGE); ex.More(); ex.Next()) {
      TopoDS_Shape sh = ex.Current();
      TopoDS_Edge   E = TopoDS::Edge   (sh);
      LimitTolerance (E,tmin,tmax,TopAbs_EDGE);
      TopoDS_Vertex V1,V2;
      TopExp::Vertices (E,V1,V2);
      if (!V1.IsNull()) fait |= LimitTolerance (V1,tmin,tmax,TopAbs_VERTEX);
      if (!V2.IsNull()) fait |= LimitTolerance (V2,tmin,tmax,TopAbs_VERTEX);
    }
  } else {
    fait |= LimitTolerance (shape,tmin,tmax,TopAbs_VERTEX);
    fait |= LimitTolerance (shape,tmin,tmax,TopAbs_EDGE);
    fait |= LimitTolerance (shape,tmin,tmax,TopAbs_FACE);
  }
  return fait;
}

//=======================================================================
//function : SetTolerance
//purpose  : 
//=======================================================================

void ShapeFix_ShapeTolerance::SetTolerance(const TopoDS_Shape& shape,
                                           const Standard_Real preci,
                                           const TopAbs_ShapeEnum styp) const
{
//   VERTEX ou EDGE ou FACE : ces types seulement
//   WIRE : EDGE + VERTEX
//   Autres : TOUT (donc == WIRE + FACE)
  if (shape.IsNull() || preci <= 0) return;
  if (styp == TopAbs_VERTEX || styp == TopAbs_EDGE || styp == TopAbs_FACE) {
    for (TopExp_Explorer ex(shape,styp); ex.More(); ex.Next()) {
      TopoDS_Shape sh = ex.Current();
      if        (styp == TopAbs_VERTEX) {
	TopoDS_Vertex V = TopoDS::Vertex (sh);
//	B.UpdateVertex (V,preci);
	const Handle(BRep_TVertex)& TV = *((Handle(BRep_TVertex)*)&V.TShape());
	TV->Tolerance(preci);
      } else if (styp == TopAbs_EDGE) {
	TopoDS_Edge   E = TopoDS::Edge   (sh);
//	B.UpdateEdge   (E,preci);
	const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*)&E.TShape());
	TE->Tolerance(preci);
      } else if (styp == TopAbs_FACE) {
	TopoDS_Face   F = TopoDS::Face   (sh);
//	B.UpdateFace   (F,preci);
	const Handle(BRep_TFace)& TF = *((Handle(BRep_TFace)*)&F.TShape());
	TF->Tolerance(preci);
      }
    }
  }
  else if (styp == TopAbs_WIRE) {
    for (TopExp_Explorer ex(shape,TopAbs_EDGE); ex.More(); ex.Next()) {
      TopoDS_Shape sh = ex.Current();
      TopoDS_Edge   E = TopoDS::Edge   (sh);
//      B.UpdateEdge   (E,preci);
      const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*)&E.TShape());
      TE->Tolerance(preci);
      TopoDS_Vertex V1,V2;
      TopExp::Vertices (E,V1,V2);
      if (!V1.IsNull()) {
//	B.UpdateVertex (V1,preci);
	const Handle(BRep_TVertex)& TV= *((Handle(BRep_TVertex)*)&V1.TShape());
	TV->Tolerance(preci);
      }
      if (!V2.IsNull()) {
//	B.UpdateVertex (V2,preci);
	const Handle(BRep_TVertex)& TV= *((Handle(BRep_TVertex)*)&V2.TShape());
	TV->Tolerance(preci);
      }
    }
  }
  else {
    SetTolerance (shape,preci,TopAbs_VERTEX);
    SetTolerance (shape,preci,TopAbs_EDGE);
    SetTolerance (shape,preci,TopAbs_FACE);
  }
}
