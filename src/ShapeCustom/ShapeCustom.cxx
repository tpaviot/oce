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

//#71 rln 09.03.99: S4135: new class _TrsfModification and method ::ScaleShape
//    abv 08.05.99: S4190: new class and method ConvertToRevolution
//    gka 01.08.99 S4188 : new class and method LimitDegreeShape
//    abv 16.06.99 general function ApplyModifier() implemented
//    gka 21.06.99 general LimitDegreeShape renamed to BSplineRestriction
//    szv 03.01.01 PositiveCones merged with DirectFaces
#include <ShapeCustom.hxx>
#include <ShapeCustom_DirectModification.hxx>
#include <ShapeCustom_TrsfModification.hxx>
#include <ShapeCustom_ConvertToRevolution.hxx>
#include <ShapeCustom_BSplineRestriction.hxx>
#include <ShapeCustom_ConvertToBSpline.hxx>
#include <ShapeCustom_SweptToElementary.hxx>

#include <gp_Trsf.hxx>
#include <GeomAbs_Shape.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Iterator.hxx>
#include <BRep_Builder.hxx>
#include <BRepTools_Modifier.hxx>


//=======================================================================
//function : ApplyModifier
//purpose  : static
//=======================================================================

TopoDS_Shape ShapeCustom::ApplyModifier (const TopoDS_Shape &S, 
                                         const Handle(BRepTools_Modification) &M,
                                         TopTools_DataMapOfShapeShape &context,
                                         BRepTools_Modifier& MD )
{
  // protect against INTERNAL/EXTERNAL shapes
  TopoDS_Shape SF = S.Oriented(TopAbs_FORWARD);
  
  // Process COMPOUNDs separately in order to handle sharing in assemblies
  if ( SF.ShapeType() == TopAbs_COMPOUND ) {
    Standard_Boolean locModified = Standard_False;
    TopoDS_Compound C;
    BRep_Builder B;
    B.MakeCompound ( C );
    for ( TopoDS_Iterator it(SF); it.More(); it.Next() ) {
      TopoDS_Shape shape = it.Value();
      TopLoc_Location L = shape.Location(), nullLoc;
      shape.Location ( nullLoc );
      TopoDS_Shape res;
      if ( context.IsBound ( shape ) )
	   res = context.Find ( shape ).Oriented ( shape.Orientation() );
      else res = ApplyModifier ( shape, M, context ,MD);
      if ( ! res.IsSame ( shape ) ) {
        context.Bind ( shape, res );
        locModified = Standard_True;
      }
      res.Location ( L );
      B.Add ( C, res );
    }
    if ( ! locModified ) return S;
    context.Bind ( SF, C );
    return C.Oriented ( S.Orientation() );
  }

  // Modify the shape
  //BRepTools_Modifier Op(SF,M);
  MD.Init(SF);
  MD.Perform(M);
    
  if ( ! MD.IsDone() ) return S;
  return MD.ModifiedShape(SF).Oriented(S.Orientation());
}
  

//=======================================================================
//function : DirectFaces
//purpose  : 
//=======================================================================

TopoDS_Shape ShapeCustom::DirectFaces (const TopoDS_Shape& S)
{
  // Create a modification description
  Handle(ShapeCustom_DirectModification) DM = 
    new ShapeCustom_DirectModification();
  TopTools_DataMapOfShapeShape context;
  BRepTools_Modifier MD;
  return ApplyModifier ( S, DM, context, MD );
}


//=======================================================================
//function : ScaleShape
//purpose  : 
//=======================================================================

TopoDS_Shape ShapeCustom::ScaleShape (const TopoDS_Shape& S, const Standard_Real scale) 
{
  // Create a modification description
  gp_Trsf T;
  T.SetScale (gp_Pnt (0, 0, 0), scale);
  Handle(ShapeCustom_TrsfModification) TM = new ShapeCustom_TrsfModification(T);
  TopTools_DataMapOfShapeShape context;
  BRepTools_Modifier MD;
  return ShapeCustom::ApplyModifier ( S, TM, context,MD );
}


//=======================================================================
//function : BSplineRestriction
//purpose  : 
//=======================================================================

TopoDS_Shape ShapeCustom::BSplineRestriction (const TopoDS_Shape& S, const Standard_Real Tol3d,
					      const Standard_Real Tol2d, const Standard_Integer MaxDegree,
					      const Standard_Integer MaxNbSegment,
					      const GeomAbs_Shape Continuity3d,
					      const GeomAbs_Shape Continuity2d,
					      const Standard_Boolean Degree,
					      const Standard_Boolean Rational,
					      const Handle(ShapeCustom_RestrictionParameters)& aParameters)
{
  // Create a modification description

  Handle(ShapeCustom_BSplineRestriction) BSR = new ShapeCustom_BSplineRestriction();
  BSR->SetTol3d(Tol3d);
  BSR->SetTol2d(Tol2d);
  BSR->SetMaxDegree(MaxDegree);
  BSR->SetMaxNbSegments(MaxNbSegment);
  BSR->SetContinuity3d(Continuity3d);
  BSR->SetContinuity2d(Continuity2d);
  BSR->SetPriority(Degree);
  BSR->SetConvRational(Rational);
  BSR->SetRestrictionParameters(aParameters);
  // Modify the shape
  TopTools_DataMapOfShapeShape context;
  BRepTools_Modifier MD;
  return ShapeCustom::ApplyModifier ( S, BSR, context ,MD);
}


//=======================================================================
//function : ConvertToRevolution
//purpose  : 
//=======================================================================

TopoDS_Shape ShapeCustom::ConvertToRevolution (const TopoDS_Shape& S) 
{
  // Create a modification description
  Handle(ShapeCustom_ConvertToRevolution) CRev = 
    new ShapeCustom_ConvertToRevolution();
  TopTools_DataMapOfShapeShape context;
  BRepTools_Modifier MD;
  return ShapeCustom::ApplyModifier ( S, CRev, context,MD );
}


//=======================================================================
//function : SweptToElementary
//purpose  : 
//=======================================================================

TopoDS_Shape ShapeCustom::SweptToElementary (const TopoDS_Shape& S) 
{
  // Create a modification description
  Handle(ShapeCustom_SweptToElementary) SE = 
    new ShapeCustom_SweptToElementary();
  TopTools_DataMapOfShapeShape context;
  BRepTools_Modifier MD;
  return ShapeCustom::ApplyModifier(S,SE,context,MD);
}


//=======================================================================
//function : ConvertToBSpline
//purpose  : 
//=======================================================================

TopoDS_Shape ShapeCustom::ConvertToBSpline (const TopoDS_Shape& S,
					    const Standard_Boolean extrMode,
					    const Standard_Boolean revolMode,
					    const Standard_Boolean offsetMode,
					    const Standard_Boolean planeMode) 
{
  // Create a modification description
  Handle(ShapeCustom_ConvertToBSpline) BSRev = new ShapeCustom_ConvertToBSpline();
  BSRev->SetExtrusionMode(extrMode);
  BSRev->SetRevolutionMode(revolMode);
  BSRev->SetOffsetMode(offsetMode);
  BSRev->SetPlaneMode(planeMode);
  TopTools_DataMapOfShapeShape context;
  BRepTools_Modifier MD;
  return ShapeCustom::ApplyModifier ( S, BSRev, context, MD);
}
