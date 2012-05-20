// Created on: 1995-01-06
// Created by: Frederic MAUPAS
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

//pdn 11.01.99 #144 bm1_pe_t4 protection of exceptions in draw
//    abv 13.04.99 S4136: eliminate BRepAPI::Precision()

#include <StepToTopoDS_GeometricTool.ixx>
#include <Standard_ErrorHandler.hxx>
#include <Standard_Failure.hxx>

#include <StepToTopoDS.hxx>
//#include <StepToTopoDS_ExtPCOnS.hxx>
#include <BRepTools_WireExplorer.hxx>

#include <StepGeom_PcurveOrSurface.hxx>
#include <StepGeom_Pcurve.hxx>
#include <StepGeom_Line.hxx>
#include <StepGeom_CartesianPoint.hxx>
#include <StepGeom_Vector.hxx>
#include <StepGeom_Direction.hxx>
#include <StepGeom_SeamCurve.hxx>
#include <StepRepr_DefinitionalRepresentation.hxx>
#include <StepShape_OrientedEdge.hxx>
//#include <BRepAPI.hxx>
#include <BRep_Tool.hxx>
#include <BRepTools.hxx>
#include <BRep_Builder.hxx>
#include <ElCLib.hxx>
#include <ElSLib.hxx>
#include <gp_Vec2d.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <GeomAbs_Shape.hxx>
#include <GeomAbs_CurveType.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom_BoundedCurve.hxx>
#include <Geom_Line.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Geom_ConicalSurface.hxx>
#include <Geom_SphericalSurface.hxx>
#include <Geom_ToroidalSurface.hxx>
#include <Geom_Plane.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_BSplineCurve.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopExp.hxx>
#include <Precision.hxx>
#include <Transfer_TransientProcess.hxx>


// ----------------------------------------------------------------------------
// Method  : HasPCurve
// Purpose : returns true if the surface curve has at least one pcurve lying
//on the surface
// ----------------------------------------------------------------------------

Standard_Integer StepToTopoDS_GeometricTool::PCurve
  (const Handle(StepGeom_SurfaceCurve)& SurfCurve,
   const Handle(StepGeom_Surface)&      BasisSurf,
   Handle(StepGeom_Pcurve)& thePCurve,  const Standard_Integer last)
{
  Standard_Integer NbAssGeom = SurfCurve->NbAssociatedGeometry();
  thePCurve.Nullify();
  for (Standard_Integer i= last+1; i<=NbAssGeom; i++) {
    thePCurve = SurfCurve->AssociatedGeometryValue(i).Pcurve();
    if (!thePCurve.IsNull()) {
      if (thePCurve->BasisSurface() == BasisSurf) return i;
    }
  }
  thePCurve.Nullify();
  return 0;
}

// ----------------------------------------------------------------------------
// Method  : IsSeamCurve
// Purpose : Two edges of the same wire references the same oriented edge
//           Then the surface_curve is a seam curve
// ----------------------------------------------------------------------------

Standard_Boolean  StepToTopoDS_GeometricTool::IsSeamCurve
(const Handle(StepGeom_SurfaceCurve)& SurfCurve,
 const Handle(StepGeom_Surface)&      Surf,
 const Handle(StepShape_Edge)&         StepEdge,
 const Handle(StepShape_EdgeLoop)&     EdgeLoop)
{
  if (!Handle(StepGeom_SeamCurve)::DownCast(SurfCurve).IsNull())
    return Standard_True;
  
  if (SurfCurve->NbAssociatedGeometry() != 2) return Standard_False;

  Handle(StepGeom_Pcurve) StepPCurve1 =
    SurfCurve->AssociatedGeometryValue(1).Pcurve();
  Handle(StepGeom_Pcurve) StepPCurve2 = 
    SurfCurve->AssociatedGeometryValue(2).Pcurve();

  // Do the two pcurves lye on the same surface ?

  if ((!StepPCurve1.IsNull() && !StepPCurve2.IsNull()) && 
      (StepPCurve1->BasisSurface() == Surf) &&
      (StepPCurve2->BasisSurface()== Surf)) {

    Standard_Integer NbEdge = EdgeLoop->NbEdgeList();
    Standard_Integer nbOE = 0;

    Handle(StepShape_OrientedEdge) OrEdge;

    for (Standard_Integer i = 1; i <= NbEdge; i ++ ) {
      OrEdge = EdgeLoop->EdgeListValue(i);
      if (StepEdge == OrEdge->EdgeElement()) nbOE ++;
    }
    // two oriented edges of the same wire share the same edge
    if (nbOE == 2) return Standard_True;
  }
  return Standard_False;
}

// ----------------------------------------------------------------------------
// Method  : IsLikeSeam
// Purpose : The two pcurves lies on the same surface but on different wires.
//           This is typical situation in CATIA BRep : a cylinder is coded
//           with two faces on the same 'Closed' BSplineSurf, which in the
//           range of gp_Resolution is not identified as closed
// ----------------------------------------------------------------------------

Standard_Boolean  StepToTopoDS_GeometricTool::IsLikeSeam
(const Handle(StepGeom_SurfaceCurve)& SurfCurve,
 const Handle(StepGeom_Surface)&      Surf,
 const Handle(StepShape_Edge)&         StepEdge,
 const Handle(StepShape_EdgeLoop)&     EdgeLoop)
{
  if (SurfCurve->NbAssociatedGeometry() != 2) return Standard_False;

  Handle(StepGeom_Pcurve) StepPCurve1 = 
    SurfCurve->AssociatedGeometryValue(1).Pcurve();
  Handle(StepGeom_Pcurve) StepPCurve2 = 
    SurfCurve->AssociatedGeometryValue(2).Pcurve();
  
  // Do the two pcurves lye on the same surface ?
  
  if ((!StepPCurve1.IsNull() && !StepPCurve2.IsNull()) && 
      (StepPCurve1->BasisSurface() == Surf) &&
      (StepPCurve2->BasisSurface() == Surf)) {
    
    Standard_Integer NbEdge = EdgeLoop->NbEdgeList();
    Standard_Integer nbOE = 0;

    Handle(StepShape_OrientedEdge) OrEdge;

    for (Standard_Integer i = 1; i <= NbEdge; i ++ ) {
      OrEdge = EdgeLoop->EdgeListValue(i);
      if (StepEdge == OrEdge->EdgeElement()) nbOE ++;
    }
    // the two oriented edges are not in the same wire
    if (nbOE == 1) { 
      // check is the two pcurve are not indentical ?
      Handle(StepGeom_Line) line1 = Handle(StepGeom_Line)::DownCast
	(StepPCurve1->ReferenceToCurve()->ItemsValue(1));
      Handle(StepGeom_Line) line2 = Handle(StepGeom_Line)::DownCast
	(StepPCurve2->ReferenceToCurve()->ItemsValue(1));
      if (!line1.IsNull() && !line2.IsNull()) {
	// Same Origin in X OR Y && Same Vector ??
	// WITHIN A given tolerance !!!
	Standard_Real DeltaX = Abs(line1->Pnt()->CoordinatesValue(1) -
				   line2->Pnt()->CoordinatesValue(1));
	Standard_Real DeltaY = Abs(line1->Pnt()->CoordinatesValue(2) -
				   line2->Pnt()->CoordinatesValue(2));

	Standard_Real DeltaDirX = 
	  Abs(line1->Dir()->Orientation()->DirectionRatiosValue(1) -
	      line2->Dir()->Orientation()->DirectionRatiosValue(1));
	Standard_Real DeltaDirY = 
	  Abs(line1->Dir()->Orientation()->DirectionRatiosValue(2) -
	      line2->Dir()->Orientation()->DirectionRatiosValue(2));

	Standard_Real preci2d = Precision::PConfusion(); //:S4136: Parametric(BRepAPI::Precision(),10);
	
	if ((DeltaX < preci2d) || (DeltaY < preci2d))
	  return ((DeltaDirX < preci2d) && (DeltaDirY < preci2d));
	else return Standard_False;

	// Warning : la manipulation de tolerances dans ce contexte est un
	//           peu trop dangeureux.
	//           il serait preferable de plus de ne pas restreindre au
	//           cas de deux lignes.
	//           un mode plus convenable de detection serait de se servir
	//           des isos (ou bords naturels) de la surface de base
	//           et de detecter que les deux courbes se trouvent sur le
	//           bord de fermeture.
	//           il faut toutefois prevoir le cas ou les deux courbes
	//           sont confondues (ex : CATIA, "couture" de separation
	//           en deux faces d un support periodique.
	//  Ce travail reste evidement A FAIRE !!! ...
      }
      else return Standard_False;
    }
    return Standard_False;
  }
  return Standard_False;
}

// ----------------------------------------------------------------------------
// Method  : UpdateParam3d
// Purpose : According to the type of curve update parameter (w1>w2)
//           This situation occurs when an edge crosses the parametric origin.
// ----------------------------------------------------------------------------

Standard_Boolean  StepToTopoDS_GeometricTool::UpdateParam3d
(const Handle(Geom_Curve)& theCurve, Standard_Real& w1, Standard_Real& w2,
 const Standard_Real preci)
{
  // w1 et/ou w2 peuvent etre en dehors des bornes naturelles de la courbe.
  // On donnera alors la valeur en bout a w1 et/ou w2
  
  Standard_Real cf = theCurve->FirstParameter();
  Standard_Real cl = theCurve->LastParameter();
//  Standard_Real preci = BRepAPI::Precision();

  if (theCurve->IsKind(STANDARD_TYPE(Geom_BoundedCurve)) && !theCurve->IsClosed()) {
    if (w1 < cf) {
#ifdef DEBUG
      cout << "Update Edge First Parameter to Curve First Parameter" << endl;
#endif
      w1 = cf;
    }
    else if (w1 > cl) {
#ifdef DEBUG
      cout << "Update Edge First Parameter to Curve Last Parameter" << endl;
#endif
      w1 = cl;
    }
    if (w2 < cf) {
#ifdef DEBUG
      cout << "Update Edge Last Parameter to Curve First Parameter" << endl;
#endif
      w2 = cf;
    }
    else if (w2 > cl) {
#ifdef DEBUG
      cout << "Update Edge Last Parameter to Curve Last Parameter" << endl;
#endif
      w2 = cl;
    }
  }

  if (w1 < w2) return Standard_True;

  if (theCurve->IsPeriodic()) 
    ElCLib::AdjustPeriodic(cf,cl,Precision::PConfusion(),w1,w2); //:a7 abv 11 Feb 98: preci -> PConfusion()
  else if (theCurve->IsClosed()) {
    // l'un des points projecte se trouve sur l'origine du parametrage
    // de la courbe 3D. L algo a donne cl +- preci au lieu de cf ou vice-versa
    // DANGER precision 3d applique a une espace 1d
    
    // w2 = cf au lieu de w2 = cl
    if      (Abs(w2 - cf) < Precision::PConfusion() /*preci*/)  w2 = cl ;
    // w1 = cl au lieu de w1 = cf
    else if (Abs(w1 - cl) < Precision::PConfusion() /*preci*/)  w1 = cf;

    // on se trouve dans un cas ou l origine est traversee
    // illegal sur une courbe fermee non periodique
    // on inverse quand meme les parametres !!!!!!
    else {
      //:S4136 abv 20 Apr 99: r0701_ug.stp #6230: add check in 3d
      if ( theCurve->Value(w1).Distance(theCurve->Value(cf)) < preci ) w1 = cf;
      if ( theCurve->Value(w2).Distance(theCurve->Value(cl)) < preci ) w2 = cl;
      if ( w1 > w2 ) {
#ifdef DEBUG
	cout << "Warning : parameter range of edge crossing non periodic curve origin" << endl;
#endif
	Standard_Real tmp = w1;
	w1 = w2;
	w2 = tmp;
      }
    }
  }
  // The curve is closed within the 3D tolerance
  else if (theCurve->IsKind(STANDARD_TYPE(Geom_BSplineCurve))) {
    Handle(Geom_BSplineCurve) aBSpline = 
      Handle(Geom_BSplineCurve)::DownCast(theCurve);
    if (aBSpline->StartPoint().Distance(aBSpline->EndPoint()) <= preci ) {
//:S4136	<= BRepAPI::Precision()) {
      // l'un des points projecte se trouve sur l'origine du parametrage
      // de la courbe 3D. L algo a donne cl +- preci au lieu de cf ou vice-versa
      // DANGER precision 3d applique a une espace 1d
      
      // w2 = cf au lieu de w2 = cl
      if      (Abs(w2 - cf) < Precision::PConfusion() /*preci*/) w2 = cl ;
      // w1 = cl au lieu de w1 = cf
      else if (Abs(w1 - cl) < Precision::PConfusion() /*preci*/) w1 =  cf;

      // on se trouve dans un cas ou l origine est traversee
      // illegal sur une courbe fermee non periodique
      // on inverse quand meme les parametres !!!!!!
      else {
#ifdef DEBUG
	cout << "Warning : parameter range of edge crossing non periodic curve origin" << endl;
#endif
	Standard_Real tmp = w1;
	w1 = w2;
	w2 = tmp;
      }
    }
    //abv 15.03.00 #72 bm1_pe_t4 protection of exceptions in draw
    else if ( w1 > w2 ) {
#ifdef DEBUG
      cout << "Warning: parameter range is bad; curve reversed" << endl;
#endif
      w1 = theCurve->ReversedParameter ( w1 );
      w2 = theCurve->ReversedParameter ( w2 );
      theCurve->Reverse();
    }
//:j9 abv 11 Dec 98: PRO7747 #4875, after :j8:    else 
    if (w1 == w2) {  //gka 10.07.1998 file PRO7656 entity 33334
      w1 = cf; w2 = cl;
      return Standard_False;
    }
  }
  else {
#ifdef DEBUG
    cout << "UpdateParam3d Failed" << endl;
    cout << "  - Curve Type : " << theCurve->DynamicType() << endl;
    cout << "  - Param 1    : " << w1 << endl;
    cout << "  - Param 2    : " << w2 << endl;
#endif
    //abv 15.03.00 #72 bm1_pe_t4 protection of exceptions in draw
    if ( w1 > w2 ) {
#ifdef DEBUG
      cout << "Warning: parameter range is bad; curve reversed" << endl;
#endif
      w1 = theCurve->ReversedParameter ( w1 );
      w2 = theCurve->ReversedParameter ( w2 );
      theCurve->Reverse();
    }
    //pdn 11.01.99 #144 bm1_pe_t4 protection of exceptions in draw
    if (w1 == w2) {
      w1 -= Precision::PConfusion();
      w2 += Precision::PConfusion();
    }
    return Standard_False;
  }
  return Standard_True;
}
