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

// Language:    C++
// Version:     Euclid Designer 2.0
// Purpose:     Update AIS object from a TDataXtd_Constraint.
// Modified     Mon 30 10:15:43 1998 by SZY


#include <TPrsStd_ConstraintTools.ixx>

#include <stdio.h>
#include <UnitsAPI.hxx>
#include <TCollection_ExtendedString.hxx>

#include <TNaming_Tool.hxx>
#include <TNaming_Iterator.hxx>
#include <TNaming_NamedShape.hxx>
#include <TDF_Label.hxx>
#include <TDataStd_Real.hxx>
#include <TDataStd_Name.hxx>
#include <TDataXtd_Geometry.hxx>
#include <TDF_Reference.hxx>


#include <AIS_OffsetDimension.hxx>
#include <AIS_LengthDimension.hxx>
#include <AIS_ParallelRelation.hxx>
#include <AIS_TangentRelation.hxx>
#include <AIS_IdenticRelation.hxx>
#include <AIS_AngleDimension.hxx>
#include <AIS_RadiusDimension.hxx>
#include <AIS_DiameterDimension.hxx>
#include <AIS_FixRelation.hxx>
#include <AIS_PerpendicularRelation.hxx>
#include <AIS_ConcentricRelation.hxx>
#include <AIS_SymmetricRelation.hxx>
#include <AIS_MidPointRelation.hxx>
#include <AIS_InteractiveContext.hxx>
#include <AIS_Drawer.hxx>
#include <AIS_EqualRadiusRelation.hxx>
#include <AIS_EqualDistanceRelation.hxx>
#include <AIS_MinRadiusDimension.hxx> 
#include <AIS_MaxRadiusDimension.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>

#include <BRep_Tool.hxx>
#include <BRep_Builder.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepAdaptor_Surface.hxx>

#include <GeomAbs_SurfaceType.hxx>
#include <Geom_Geometry.hxx>
#include <Geom_Line.hxx>
#include <Geom_Plane.hxx>
#include <Geom_CartesianPoint.hxx>
#include <Geom_Circle.hxx>
#include <gp_Pln.hxx>
#include <gp_Dir.hxx>
#include <gp_Ax1.hxx>
#include <gp_Lin.hxx>
#include <gp_Pnt.hxx>
#include <gp_Cylinder.hxx>
#include <gp_Cone.hxx>
#include <gp_Torus.hxx>
#include <GC_MakePlane.hxx> 

#include <Precision.hxx>
#include <IntAna_QuadQuadGeo.hxx>

#include <Standard_ProgramError.hxx>
#include <Standard_ErrorHandler.hxx>

#include <TopTools_IndexedMapOfShape.hxx>

#define BUC60846

static Standard_Boolean CheckShapesPair(const TopoDS_Shape& , const TopoDS_Shape& ); //ota

//=======================================================================
//function : static NullifyAIS
//purpose  : 
//=======================================================================
static void NullifyAIS ( Handle(AIS_InteractiveObject)& anais)
{
  if (anais.IsNull())  return;
  anais.Nullify();
}



//=======================================================================
//function : static FindExternalShape
//purpose  : 
//=======================================================================
static void FindExternalShape(const Handle(TDataXtd_Constraint)& aConst,
			      Standard_Integer& extShape)
{
  extShape = 0;
    const TDF_Label& L =  aConst->Label();
    if (!aConst->GetGeometry(1)->Label().IsDescendant(L)) extShape = 1;    
    else if (!aConst->GetGeometry(2)->Label().IsDescendant(L)) extShape = 2;
}

//=======================================================================
//function : static GetGoodShape for planar constraint
//purpose  : 
//=======================================================================
static void  GetGoodShape(TopoDS_Shape& shape)
{
  switch (shape.ShapeType()) {
  case TopAbs_EDGE:
  case TopAbs_VERTEX: { return; }
  default:
    {
      TopExp_Explorer EXP(shape,TopAbs_EDGE);
      if (EXP.More()) {
	shape = EXP.Current();
	return;
      }
      else {
	EXP.Init(shape,TopAbs_VERTEX);
	if (EXP.More()) shape = EXP.Current();
      }
    }
  }
}

// Pour le cas ou S est un compound
static Standard_Boolean IsFace (const TopoDS_Shape& S)
{
  Standard_Boolean  findface = Standard_False;
  TopExp_Explorer EXP (S,TopAbs_FACE);
  if (EXP.More()) findface = Standard_True;
  return  findface;
}

static TopoDS_Face  GetFace (const TopoDS_Shape& S)
{
  TopoDS_Face F;
  TopExp_Explorer EXP (S,TopAbs_FACE);
  if (EXP.More())  F = TopoDS::Face (EXP.Current());
  return  F;
}

static TopoDS_Edge  GetEdge (const TopoDS_Shape& S)
{
  TopoDS_Edge E;
  TopExp_Explorer EXP (S, TopAbs_EDGE);
  if (EXP.More()) E = TopoDS::Edge (EXP.Current());
  return  E;
}



//=======================================================================
//Function : ComputeAndTextValue
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputeTextAndValue(const Handle(TDataXtd_Constraint)& aConst,
						 Standard_Real&                val,
						 TCollection_ExtendedString&   txt,
						 const Standard_Boolean  anIsAngle  )
{
  Standard_Real outvalue;
  const Handle(TDataStd_Real)& VAL = aConst->GetValue();
  val      = VAL->Get();
  if(anIsAngle){
    outvalue = UnitsAPI::CurrentFromLS(Abs(val),"PLANE ANGLE");
  }
  else {
    outvalue = UnitsAPI::CurrentFromLS(val,"LENGTH");
  }
  char res[1000];
  sprintf(res,"%g",outvalue);
  txt = TCollection_ExtendedString(res);
  
  if (VAL->IsCaptured()) {
    Handle(TDF_Reference) ref;
    VAL->Label().FindAttribute(TDF_Reference::GetID(),ref);
    Handle(TDataStd_Name) name;
    const TDF_Label& L = ref->Get();
    if (ref->Get().FindAttribute(TDataStd_Name::GetID(),name)) {
      TCollection_ExtendedString fullname;
      Handle(TDataStd_Name) Fathername;
      if (L.Father().FindAttribute(TDataStd_Name::GetID(),Fathername)) {
	fullname = Fathername->Get() + TCollection_ExtendedString(".") + name->Get();
      }
      else fullname = name->Get();
      txt = fullname + TCollection_ExtendedString("=") + txt;
    }
  }
}


//=======================================================================
//function : UpdateOnlyValue
//purpose  : 
//=======================================================================

void TPrsStd_ConstraintTools::UpdateOnlyValue(const Handle(TDataXtd_Constraint)& aConst, 
				     const Handle(AIS_InteractiveObject)& anAIS)
{
  if (anAIS.IsNull()) return; 
  if (!aConst->IsDimension()) return; 
  Standard_Real val;
  TCollection_ExtendedString txt;
  TPrsStd_ConstraintTools:: ComputeTextAndValue(aConst,val,txt,aConst->GetType() == TDataXtd_ANGLE);
  Handle(AIS_Relation) rel = Handle(AIS_Relation)::DownCast(anAIS);
  if (!rel.IsNull()) rel->SetText(txt); 
}


//=======================================================================
//function : ComputeDistance
//purpose  : Build an AIS_LengtDimension.
//=======================================================================
void TPrsStd_ConstraintTools::ComputeDistance (const Handle(TDataXtd_Constraint)& aConst,
					      Handle(AIS_InteractiveObject)& anAIS) 
{
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom < 2) {
#ifdef DEB
    cout <<  "TPrsStd_ConstraintTools::ComputeDistance: at least 2 geometries are needed" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  TopoDS_Shape shape1,shape2,shape3 ;
  Handle(Geom_Geometry) ageom3;
  Standard_Boolean is_planar(aConst->IsPlanar()),is_directed(Standard_False);
  AIS_TypeOfDist typedist = AIS_TOD_Unknown;

  // Get shapes and geometry
  if (is_planar) {
    if (nbgeom == 2)
      GetShapesAndGeom (aConst,shape1,shape2,ageom3);
    else
      GetShapesAndGeom (aConst,shape1,shape2,shape3,ageom3);
  }
  else
    GetTwoShapes (aConst,shape1,shape2);    

  if (shape1.IsNull() || shape2.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeDistance : null shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }

  Handle(Geom_Plane) aplane;
  if (is_planar) {
    if (nbgeom != 2) {
      is_directed = !shape3.IsNull();
      if (!is_directed)  {
#ifdef DEB
	cout << "TPrsStd_ConstraintTools::ComputeDistance : null shape" << endl;
#endif
	NullifyAIS(anAIS);
	return;
      }
    }

    GetGoodShape (shape1);
    GetGoodShape (shape2);

    aplane = Handle(Geom_Plane)::DownCast(ageom3);
    if (aplane.IsNull()) {
#ifdef DEB
      cout << "TPrsStd_ConstraintTools::ComputeDistance : null plane" << endl;
#endif
      NullifyAIS(anAIS);
      return;
    }
    
    if (is_directed) {
      GetGoodShape(shape3);
      const TopoDS_Edge& E = TopoDS::Edge(shape3);
      BRepAdaptor_Curve CURVE(E);
      Handle_Geom_Geometry aGeomGeometry = CURVE.Curve().Curve()->Transformed(CURVE.Trsf()) ;
      gp_Dir Dir = ((Handle(Geom_Line)&) aGeomGeometry)->Lin().Direction();
      gp_Dir xdir(aplane->Pln().Position().XDirection());
      if (Dir.IsParallel(xdir,Precision::Confusion()))
	typedist = AIS_TOD_Horizontal;
      else
	typedist = AIS_TOD_Vertical;
    }
  }

  Standard_Real val1;
  TCollection_ExtendedString txt;
  ComputeTextAndValue(aConst,val1,txt,Standard_False);
  
  //  Arguments de l'AIS
  Standard_Boolean isface = IsFace(shape1) && IsFace(shape2);
  Standard_Boolean isedgeface = (shape1.ShapeType () == TopAbs_FACE && 
                                 shape2.ShapeType () == TopAbs_EDGE);
  Standard_Boolean is2vertices =(shape1.ShapeType () == TopAbs_VERTEX &&                 //addition 1
                                 shape2.ShapeType () == TopAbs_VERTEX);
  if (!isface && !is_planar && !is2vertices)  {
    // Recherche arguments pouvant convenir
    if (shape1.ShapeType() == shape2.ShapeType())  {
      TopoDS_Vertex  v1,v2,v3,v4;
      if (shape1.ShapeType() == TopAbs_EDGE)  {
	TopExp::Vertices (TopoDS::Edge(shape1),v1,v2);
	TopExp::Vertices (TopoDS::Edge(shape2),v3,v4);
      }
      else
      if (shape1.ShapeType() == TopAbs_WIRE)  {
	TopExp::Vertices (TopoDS::Wire(shape1),v1,v2);
	TopExp::Vertices (TopoDS::Wire(shape2),v3,v4);
      }
      shape1 = v1;
      gp_Pnt P1 = BRep_Tool::Pnt(v1);
      gp_Pnt P2 = BRep_Tool::Pnt(v3), P3 = BRep_Tool::Pnt(v4);
      if (P1.Distance(P2) < P1.Distance(P3))  {
	shape2 = v3;
	gp_Ax2 ax2 (P1, gp_Dir (P2.XYZ() - P1.XYZ()));
	aplane = new Geom_Plane (P1,ax2.XDirection());
      }
      else {
	shape2 = v4;
	gp_Ax2 ax2 (P1, gp_Dir (P3.XYZ() - P1.XYZ()));
	aplane = new Geom_Plane (P1,ax2.XDirection());
      }
    }
    else  {
      if (!isedgeface) {
	NullifyAIS(anAIS);
	return;
      }
    }
  }

  //  Update de l'AIS
  Handle(AIS_LengthDimension) ais;
  Standard_Boolean SaveDrw = Standard_False;
  Handle(AIS_Drawer) aDrawer;

  if (!anAIS.IsNull()) {
    ais = Handle(AIS_LengthDimension)::DownCast(anAIS);
  }

  if (ais.IsNull())  {
    if (is2vertices)  {                                        //addition 2
      gp_Pnt P1 = BRep_Tool::Pnt( TopoDS::Vertex(shape1) );
      gp_Pnt P2 = BRep_Tool::Pnt( TopoDS::Vertex(shape2) );
      gp_Pnt P3(P1.Y()-1., P2.X()+1., 0.); 
      GC_MakePlane mkPlane(P1, P2, P3); 
      ais = new AIS_LengthDimension (shape1, shape2, mkPlane.Value(), val1,txt);
    }
    else if (isface)  {
      ais = new AIS_LengthDimension (GetFace(shape1),GetFace(shape2),val1,txt);
    }
    else if (isedgeface) {
      ais = new AIS_LengthDimension (GetFace(shape1),GetEdge(shape2),val1,txt);
    }
    else  {
      ais = new AIS_LengthDimension (shape1,shape2,aplane,val1,txt);
    }
    if( SaveDrw ) ais->SetAttributes(aDrawer);   
  }
  else {
    if (isface)  {
      ais->SetFirstShape  (GetFace(shape1));
      ais->SetSecondShape (GetFace(shape2));
    }
    else  {
      ais->SetFirstShape  (shape1);
      ais->SetSecondShape (shape2);
    }
    if (is2vertices)  {                     //addition 3
      gp_Pnt P1 = BRep_Tool::Pnt( TopoDS::Vertex(shape1) );
      gp_Pnt P2 = BRep_Tool::Pnt( TopoDS::Vertex(shape2) );
      gp_Pnt P3(P1.Y()-1., P2.X()+1., 0.); 
      GC_MakePlane mkPlane(P1, P2, P3); 
      ais->SetPlane( mkPlane.Value() );
    }

    ais->SetValue       (val1);
    ais->SetText        (txt);
  }
  
  if (is_planar) {
    Standard_Integer extShape (0);
#ifndef BUC60846
    FindExternalShape (aConst,extShape);
#endif
    ais->SetPlane      (aplane);
    ais->SetTypeOfDist (typedist);
    ais->SetExtShape   (extShape);
  }
  anAIS = ais;
}

//=======================================================================
//function : ComputePerpendicular
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputePerpendicular(const Handle(TDataXtd_Constraint)& aConst,
						  Handle(AIS_InteractiveObject)& anAIS) 
{
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom < 2) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputePerpendicular: at leat two constraintes are needed" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  
  TopoDS_Shape shape1,shape2 ;
  Handle(Geom_Geometry) ageom3;
  Standard_Boolean is_planar(aConst->IsPlanar());
  
  if (is_planar) GetShapesAndGeom(aConst,shape1,shape2,ageom3);
  else GetTwoShapes(aConst,shape1,shape2); 
  if (shape1.IsNull() || shape2.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputePerpendicular : null shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  GetGoodShape(shape1);
  GetGoodShape(shape2);
  //  Update de l'AIS
  Handle(AIS_PerpendicularRelation) ais;
  if (anAIS.IsNull()) ais = new AIS_PerpendicularRelation(shape1,shape2);
  else {
    ais = Handle(AIS_PerpendicularRelation)::DownCast(anAIS);
    if (ais.IsNull()) {
      ais = new AIS_PerpendicularRelation(shape1,shape2);
    }
    else {
      ais->SetFirstShape(shape1);
      ais->SetSecondShape(shape2);
    }
  }
  
  if (is_planar) {
    Handle(Geom_Plane) aplane = Handle(Geom_Plane)::DownCast(ageom3);
    if (aplane.IsNull()) {
#ifdef DEB
      cout << "TPrsStd_ConstraintTools::ComputePerpendicular: nul plane" << endl;
#endif
      NullifyAIS(anAIS);
      return;
    }
    ais->SetPlane(aplane);
  }
  anAIS = ais;
}

//=======================================================================
//function : ComputeParallel
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputeParallel(const Handle(TDataXtd_Constraint)& aConst, 
					     Handle(AIS_InteractiveObject)& anAIS) 
{
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom < 2) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeParallel: at least 2 constraintes are needed" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  
  if (!aConst->IsPlanar()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeParallel: must be a planar constraint" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }

  TopoDS_Shape shape1,shape2 ;
  Handle(Geom_Geometry) ageom3;
  
  GetShapesAndGeom(aConst,shape1,shape2,ageom3);
  if (shape1.IsNull() || shape2.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeParallel : null shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  Handle(Geom_Plane) aplane = Handle(Geom_Plane)::DownCast(ageom3);
  if (aplane.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeParallel: nul plane" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  //  Update de l'AIS
  GetGoodShape(shape1);
  GetGoodShape(shape2);
  Handle(AIS_ParallelRelation) ais;
  if (anAIS.IsNull()) ais = new AIS_ParallelRelation(shape1,shape2,aplane);
  else { 
    ais = Handle(AIS_ParallelRelation)::DownCast(anAIS);
    if (ais.IsNull()) {
      ais = new AIS_ParallelRelation(shape1,shape2,aplane);
    }
    else {
      ais->SetFirstShape(shape1);
      ais->SetSecondShape(shape2);
      ais->SetPlane(aplane);
    }
  }
  anAIS = ais;
}
//=======================================================================
//function : ComputeSymmetry
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputeSymmetry(const Handle(TDataXtd_Constraint)& aConst,
					     Handle(AIS_InteractiveObject)& anAIS) 
{
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom < 3) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeSymmetry: at least 3 constraintes are needed" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }

  Standard_Boolean is_planar(aConst->IsPlanar());
  if (!is_planar) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeSymmetry: must be a planar constraint" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }

  TopoDS_Shape shape1,shape2,shape3 ;
  Handle(Geom_Geometry) ageom3;
  GetShapesAndGeom(aConst,shape1,shape2,shape3,ageom3);

  if (shape1.IsNull() || shape2.IsNull() || shape3.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeSymmetry : null shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  GetGoodShape(shape1);
  GetGoodShape(shape2);
  GetGoodShape(shape3);
  Handle(Geom_Plane) aplane = Handle(Geom_Plane)::DownCast(ageom3);
  if (aplane.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeSymmetry: null plane" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  //  Update de l'AIS
  Handle(AIS_SymmetricRelation) ais;
  if (anAIS.IsNull()) ais = new AIS_SymmetricRelation(shape3,shape1,shape2,aplane);
  else {
    ais = Handle(AIS_SymmetricRelation)::DownCast(anAIS);
    if (ais.IsNull()) {
      ais = new AIS_SymmetricRelation(shape3,shape1,shape2,aplane);
    }
    else {
      ais->SetFirstShape(shape1);
      ais->SetSecondShape(shape2);
      ais->SetPlane(aplane);
      ais->SetTool(shape3);
    }
  }
  anAIS = ais;
}

//=======================================================================
//function : ComputeMidPoint
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputeMidPoint(const Handle(TDataXtd_Constraint)& aConst,
					      Handle(AIS_InteractiveObject)& anAIS) 
{
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom < 3)
    {
#ifdef DEB
      cout << "TPrsStd_ConstraintTools::ComputeSymmetry: at least 3 constraints are needed" << endl;
#endif
      NullifyAIS(anAIS);
      return;
    }

  Standard_Boolean is_planar(aConst->IsPlanar());
  if ( !is_planar )
    {
#ifdef DEB
      cout << "TPrsStd_ConstraintTools::ComputeSymmetry: must be a planar constraint" << endl;
#endif
      NullifyAIS(anAIS);
      return;
    }

  TopoDS_Shape shape1,shape2,shape3;
  Handle(Geom_Geometry) ageom3;
  GetShapesAndGeom(aConst,shape1,shape2,shape3,ageom3);

  if (shape1.IsNull() || shape2.IsNull() || shape3.IsNull())
    {
#ifdef DEB
      cout << "TPrsStd_ConstraintTools::ComputeSymmetry : null shape" << endl;
#endif
      NullifyAIS(anAIS);
      return;
    }
  GetGoodShape(shape1);
  GetGoodShape(shape2);
  GetGoodShape(shape3);

  Handle(Geom_Plane) aplane = Handle(Geom_Plane)::DownCast(ageom3);
  if (aplane.IsNull())
    {
#ifdef DEB
      cout << "TPrsStd_ConstraintTools::ComputeSymmetry: null plane" << endl;
#endif
      NullifyAIS(anAIS);
      return;
    }

  //  Update de l'AIS
  Handle(AIS_MidPointRelation) ais;
  if ( anAIS.IsNull() ) ais = new AIS_MidPointRelation(shape3,shape1,shape2,aplane);
  else
    {
      ais = Handle(AIS_MidPointRelation)::DownCast(anAIS);
      if (ais.IsNull())
	{
	  ais = new AIS_MidPointRelation(shape3,shape1,shape2,aplane);
	}
      else
	{
	  ais->SetFirstShape(shape1);
	  ais->SetSecondShape(shape2);
	  ais->SetPlane(aplane);
	  ais->SetTool(shape3);
	}
    }
  anAIS = ais;
}

//=======================================================================
//function : ComputeTangent
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputeTangent (const Handle(TDataXtd_Constraint)& aConst, 
					     Handle(AIS_InteractiveObject)& anAIS) 
{
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom < 2) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeTangent: at leat two constraintes are needed" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  if (!aConst->IsPlanar()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeTangent: must be a planar constraint" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  TopoDS_Shape shape1,shape2 ;
  Handle(Geom_Geometry) ageom3;
  
  GetShapesAndGeom(aConst,shape1,shape2,ageom3);
  if (shape1.IsNull() || shape2.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeTangent : null shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  GetGoodShape(shape1);
  GetGoodShape(shape2);
  Handle(Geom_Plane) aplane = Handle(Geom_Plane)::DownCast(ageom3);
  if (aplane.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeTangent: nul plane" << endl;
#endif
    NullifyAIS(anAIS);
    return;    
  }
  //  Update de l'AIS
  Handle(AIS_TangentRelation) ais;
  if (anAIS.IsNull())
    {
      ais = new AIS_TangentRelation(shape1,shape2,aplane);
      ais->SetArrowSize(10000000); // jfa 9/10/2000
    }
  else
    {
      ais = Handle(AIS_TangentRelation)::DownCast(anAIS);
      if (ais.IsNull())
	{
	  ais = new AIS_TangentRelation(shape1,shape2,aplane);
	  ais->SetArrowSize(10000000); // jfa 9/10/2000
	}
      else
	{
	  ais->SetFirstShape(shape1);
	  ais->SetSecondShape(shape2);
	  ais->SetPlane(aplane);
	  ais->SetArrowSize(10000000); // jfa 9/10/2000
	}
    }
  anAIS = ais;
}

//=======================================================================
//function : ComputeAngleForOneFace
//purpose  : computes AngleDimension for one-conical-face case
//=======================================================================
void TPrsStd_ConstraintTools::ComputeAngleForOneFace (const Handle(TDataXtd_Constraint)& aConst,
					   Handle(AIS_InteractiveObject)& anAIS) 
{
 
  TopoDS_Shape shape;
  Handle(Geom_Geometry) ageom3;
  
  GetOneShape( aConst, shape ); 
  if (shape.IsNull() ) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeAngleForOneFace : null shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }

  Standard_Real val1;
  TCollection_ExtendedString txt;
  TPrsStd_ConstraintTools::ComputeTextAndValue (aConst,val1,txt,Standard_True);  
  
  Handle(AIS_AngleDimension) ais;
  TopoDS_Face face;
  if (!anAIS.IsNull()) {
    ais = Handle(AIS_AngleDimension)::DownCast(anAIS);
    if(ais.IsNull()) {
      face = TopoDS::Face( shape );
      ais =  new AIS_AngleDimension ( face, val1, txt);
    }
    else {
      ais->SetConeFace(TopoDS::Face( shape ));
      ais->SetValue(val1);
      ais->SetText(txt);
    }
  }
  else {
    face = TopoDS::Face( shape );
    ais =  new AIS_AngleDimension ( face, val1, txt);
  } 

  anAIS = ais;
}

//====================================================================
static Standard_Boolean CheckIsShapeCompound(TopoDS_Shape& shape, TopoDS_Face& aFace)
{
  if (shape.ShapeType() == TopAbs_COMPOUND) {
    TopTools_IndexedMapOfShape aFaceMap;
    TopExp::MapShapes(shape, TopAbs_FACE, aFaceMap);
    for(Standard_Integer i = 1;i <= aFaceMap.Extent();i++) 
      {
	aFace = TopoDS::Face(aFaceMap.FindKey(i));
	if(!aFace.IsNull()) {
	  shape = aFace;
	  return (Standard_True);
	}
      }
  }
#ifdef DEB
  cout << "TPrsStd::Compute angle : Shape is not Compound or is Null" <<endl;
#endif
  return (Standard_False);
}
//=======================================================================
//function : ComputeAngle
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputeAngle (const Handle(TDataXtd_Constraint)& aConst,
					   Handle(AIS_InteractiveObject)& anAIS) 
{
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom < 2) {
    if( nbgeom == 1 ) { ComputeAngleForOneFace( aConst, anAIS ); return; }
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeAngle: at least 2 constraints are needed" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  
  TopoDS_Shape shape1,shape2 ;
  Handle(Geom_Geometry) ageom3;
  
  GetShapesAndGeom (aConst,shape1,shape2,ageom3);
  if (shape1.IsNull() || shape2.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeAngle : null shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  
  Standard_Boolean isCurvilinear = Standard_False;
  if (ageom3.IsNull()) {
    // on essaie de le calculer
    
    TopoDS_Face  aFace;
    if (shape1.ShapeType() == TopAbs_WIRE)  {
      BRepBuilderAPI_MakeFace MkF (TopoDS::Wire(shape1),Standard_True);
      if (MkF.IsDone())  {
	aFace = MkF.Face();
	shape1 = aFace;
      }
    }
    else
      if (shape1.ShapeType() == TopAbs_FACE)
	aFace    = TopoDS::Face(shape1);
      else
	if(!CheckIsShapeCompound(shape1, aFace)) {
#ifdef DEB
	cout << "Compute angle : Geom type = " << shape1.ShapeType()
	  << " non traite"<<endl;
#endif
	NullifyAIS(anAIS);
	return;      
      }

    gp_Ax1 anax1aFace1;
    gp_Pln aPlnaFace1;

    BRepAdaptor_Surface   aSurfaFace (aFace);
    GeomAbs_SurfaceType aTypeaFace = aSurfaFace.GetType();
    if (aTypeaFace  == GeomAbs_Plane) {
      aPlnaFace1 = aSurfaFace.Plane();
      anax1aFace1 = aPlnaFace1.Axis(); // Normale au plan
    } else if (aTypeaFace  == GeomAbs_Cylinder) {
      gp_Cylinder aCylaFace = aSurfaFace.Cylinder();
      anax1aFace1 = aCylaFace.Axis();
    } else if (aTypeaFace  == GeomAbs_Cone) {
      gp_Cone aCone = aSurfaFace.Cone();
      anax1aFace1 = aCone.Axis();  
    } else if (aTypeaFace  == GeomAbs_Torus) {
      gp_Torus aTore = aSurfaFace.Torus();
      anax1aFace1 = aTore.Axis();  
    } else {
#ifdef DEB
      cout<<"Compute angle"<<aTypeaFace<<" non traite"<<endl;
#endif
      NullifyAIS(anAIS);
      return;      
    }

    gp_Ax1 anax1aFace2;
    gp_Pln aPlnaFace2;
    if (shape2.ShapeType() == TopAbs_WIRE)  {
      BRepBuilderAPI_MakeFace MkF (TopoDS::Wire(shape2),Standard_True);
      if (MkF.IsDone())  {
	aFace = MkF.Face();
	shape2 = aFace;
      }
    }
    else
      if (shape2.ShapeType() == TopAbs_FACE)
	aFace    = TopoDS::Face(shape2); 
    else  
      if(!CheckIsShapeCompound(shape2, aFace)) {
#ifdef DEB
	cout << "Compute angle : Geom type = " << shape2.ShapeType()
	  << " non traite"<<endl;
#endif
	NullifyAIS(anAIS);
	return;      
      }
    
    aSurfaFace.Initialize(aFace);
    aTypeaFace = aSurfaFace.GetType();
    if (aTypeaFace  == GeomAbs_Plane) {
      aPlnaFace2 = aSurfaFace.Plane();
      anax1aFace2 = aPlnaFace2.Axis(); // Normale au plan
    } else if (aTypeaFace  == GeomAbs_Cylinder) {
      gp_Cylinder aCylaFace = aSurfaFace.Cylinder();
      anax1aFace2 = aCylaFace.Axis();
    } else if (aTypeaFace  == GeomAbs_Cone) {
      gp_Cone aCone = aSurfaFace.Cone();
      anax1aFace2 = aCone.Axis();  
    } else if (aTypeaFace  == GeomAbs_Torus) {
      gp_Torus aTore = aSurfaFace.Torus();
      anax1aFace2 = aTore.Axis();  
    } else {
#ifdef DEB
      cout << "Compute angle " << aTypeaFace << " non traite"<<endl;
#endif
      NullifyAIS(anAIS);
      return;      
    }

    if (aTypeaFace==GeomAbs_Plane) {
      if (!anax1aFace1.IsParallel(anax1aFace2, Precision::Angular())) {
	
	IntAna_QuadQuadGeo IntersectPlane (aPlnaFace1, aPlnaFace2, Precision::Angular(), Precision::Angular());
	if (IntersectPlane.IsDone() &&
	    (IntersectPlane.TypeInter() != IntAna_Empty))  {
	  gp_Lin aLine = IntersectPlane.Line(1);
	  Handle(Geom_Line) computedgeom3 = new Geom_Line (aLine);
	  ageom3 = computedgeom3;
	} else {
#ifdef DEB
	  cout<<"Compute angle insertection of planes failed"<<endl;
#endif
	  NullifyAIS(anAIS);
	  return;            
	}
      } else {
	
#ifdef DEB
	cout<<"Compute angle faces are //"<<endl;
#endif
	NullifyAIS(anAIS);
	return;            
      }
    } else {
      // Curvilinear faces...
      isCurvilinear = Standard_True;
    }
  } // endif (ageom3.IsNull())


  Standard_Boolean isplan(Standard_False);

  if (!isCurvilinear) {
    if (ageom3->IsKind(STANDARD_TYPE(Geom_Plane))) isplan = Standard_True;
    else if (ageom3->IsKind(STANDARD_TYPE(Geom_Line))) isplan = Standard_False;
    else {
#ifdef DEB
      cout << "TPrsStd_ConstraintTools::ComputeAngle: unknown 3rd arg " << endl;
#endif
      NullifyAIS(anAIS);
      return;
    }
  }
  Standard_Real val1;
  TCollection_ExtendedString txt;
  ComputeTextAndValue (aConst,val1,txt,Standard_True);  
  
  Standard_Boolean toCreate (Standard_True);
  Standard_Boolean isface(shape1.ShapeType()==TopAbs_FACE);
  
  Handle(AIS_AngleDimension) ais;
  if (!anAIS.IsNull()) {
    ais = Handle(AIS_AngleDimension)::DownCast(anAIS);
    if( ais.IsNull() ) {
      toCreate = Standard_True;
    }
    else toCreate = Standard_False;
  }
  
  Standard_Integer ExtShape(0);
  if (toCreate)  {
    // Creation de l'AIS
    if (isplan) {
      if(!isface) {
	FindExternalShape(aConst,ExtShape);
	GetGoodShape(shape1);
	GetGoodShape(shape2);
	ais = new AIS_AngleDimension (TopoDS::Edge(shape1),
				      TopoDS::Edge(shape2),
				      (Handle(Geom_Plane)&) ageom3,val1,txt);
	ais->SetExtShape(ExtShape);
      }
    }
    else { 
      if (isCurvilinear) {
	ais = new AIS_AngleDimension (TopoDS::Face(shape1),
				      TopoDS::Face(shape2),val1,txt);
      }
      else if (isface) {
	ais =  new AIS_AngleDimension (TopoDS::Face(shape1),
				       TopoDS::Face(shape2),
				       ((Handle(Geom_Line)&) ageom3)->Position(),val1,txt);
      }
    }
  }
  else {
    // Update de l'AIS
    if (isplan) {
      GetGoodShape(shape1);
      GetGoodShape(shape2);
    }
    ais->SetFirstShape(shape1);
    ais->SetSecondShape(shape2);
    ais->SetValue(val1);
    ais->SetText(txt);
    if (isplan)
      ais->SetPlane ((Handle(Geom_Plane)&) ageom3);
    else if (!isCurvilinear)
      ais->SetAxis (((Handle(Geom_Line)&) ageom3)->Position());
  }
  anAIS = ais;
}


//=======================================================================
//function : ComputeConcentric
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputeConcentric(const Handle(TDataXtd_Constraint)& aConst,
					       Handle(AIS_InteractiveObject)& anAIS) 
{
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom < 2) {
    Standard_ProgramError::Raise ("TPrsStd_ConstraintTools::ComputeConcentric: at least 2 constraintes are needed");
  }
  if (!aConst->IsPlanar()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeConcentric: must be a planar constraint" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  TopoDS_Shape shape1,shape2 ;
  Handle(Geom_Geometry) ageom3;
  
  GetShapesAndGeom(aConst,shape1,shape2,ageom3);
  if (shape1.IsNull() || shape2.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeConcentric : null shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }

  GetGoodShape(shape1);
  GetGoodShape(shape2);

//ota : to allow concentric constraint display between vertex and edge
  if (shape1.ShapeType() != TopAbs_EDGE && shape2.ShapeType() != TopAbs_EDGE) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeConcentric: concentric between two vertexes : NOT DISPLAYED" << endl;;
#endif
    NullifyAIS(anAIS);
    return;
  }

  Handle(Geom_Plane) aplane = Handle(Geom_Plane)::DownCast(ageom3);
  if (aplane.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeConcentric: nul plane" << endl;;
#endif
    NullifyAIS(anAIS);
    return;
  }
  //  Update de l'AIS
  Handle(AIS_ConcentricRelation) ais;
  if (!anAIS.IsNull()) {
    ais = Handle(AIS_ConcentricRelation)::DownCast(anAIS);
    if (ais.IsNull()) {
      ais = new AIS_ConcentricRelation (shape1,shape2,aplane);
    } 
    else {
      ais->SetFirstShape(shape1);
      ais->SetSecondShape(shape2);
      ais->SetPlane(aplane);
    }
  }
  else {
    ais = new AIS_ConcentricRelation (shape1,shape2,aplane);
  }

  anAIS = ais;
}

//=======================================================================
//function : ComputeRadius
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputeRadius (const Handle(TDataXtd_Constraint)& aConst,
					    Handle(AIS_InteractiveObject)& anAIS) 
{
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom < 1) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeRadius: at least one constrainte is needed" << endl;    
#endif
    NullifyAIS(anAIS);
    return;
  }

  TopoDS_Shape shape1 ;
  GetOneShape (aConst,shape1);
  if (shape1.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeRadius: null shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }

  // POP on teste si ce n'est pas un compound
  if (shape1.ShapeType()==TopAbs_COMPOUND ||
      shape1.ShapeType()==TopAbs_COMPSOLID ||
      shape1.ShapeType()==TopAbs_SOLID ||
      shape1.ShapeType()==TopAbs_SHELL ) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeRadius: not good shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
      
  if (IsFace(shape1))
    shape1 = GetFace(shape1);

  Standard_Real val1;
  TCollection_ExtendedString txt;
  ComputeTextAndValue(aConst,val1,txt,Standard_False);

  //  Update de l'AIS
  Standard_Boolean isplanar(aConst->IsPlanar());
  if (isplanar) GetGoodShape(shape1);

  Handle(AIS_RadiusDimension) ais;
  if (!anAIS.IsNull()) {
    ais = Handle(AIS_RadiusDimension)::DownCast(anAIS);
    if (ais.IsNull()) {
      ais = new AIS_RadiusDimension (shape1,val1,txt);
    }
    else {
      ais->SetValue(val1);
      ais->SetFirstShape(shape1);
      ais->SetText(txt);    
    }
  }
  else ais = new AIS_RadiusDimension (shape1,val1,txt);

  if (isplanar) {
    Handle(Geom_Geometry) ageom2;
    GetGeom(aConst,ageom2);
    Handle(Geom_Plane) aplane = Handle(Geom_Plane)::DownCast(ageom2);
    if (aplane.IsNull()) {
#ifdef DEB
      cout << "TPrsStd_ConstraintTools::ComputeRadius: nul plane" << endl;
#endif
      NullifyAIS(anAIS);
      return;
    }
    ais->SetPlane(aplane);
    ais->SetDrawFromCenter(Standard_False);
  }
  anAIS = ais;
}
// ota -- begin --
//=======================================================================
//function : ComputeMinRadius
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputeMinRadius (const Handle(TDataXtd_Constraint)& aConst,
						Handle(AIS_InteractiveObject)& anAIS) 
{
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom < 1) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeMinRadius: at least one constrainte is needed" << endl;    
#endif
    NullifyAIS(anAIS);
    return;
  }

  TopoDS_Shape shape1 ;
  GetOneShape (aConst,shape1);
  if (shape1.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeMinradius: null shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }

  // POP on teste si ce n'est pas un compound
  if (shape1.ShapeType()==TopAbs_COMPOUND ||
      shape1.ShapeType()==TopAbs_COMPSOLID ||
      shape1.ShapeType()==TopAbs_SOLID ||
      shape1.ShapeType()==TopAbs_SHELL ) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeMinRadius: not good shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
      
  if (IsFace(shape1))
    shape1 = GetFace(shape1);

  Standard_Real val1;
  TCollection_ExtendedString txt;
  ComputeTextAndValue(aConst,val1,txt,Standard_False);

  //  Update de l'AIS
  Standard_Boolean isplanar(aConst->IsPlanar());
  if (isplanar) GetGoodShape(shape1);

  Handle(AIS_MinRadiusDimension) ais;
  if (!anAIS.IsNull()) {
    ais = Handle(AIS_MinRadiusDimension)::DownCast(anAIS);
    if (ais.IsNull()) {
      ais = new AIS_MinRadiusDimension (shape1,val1,txt);
    }
    else {
      ais->SetValue(val1);
      ais->SetFirstShape(shape1);
      ais->SetText(txt);    
    }
  }
  else ais = new AIS_MinRadiusDimension (shape1,val1,txt);

  if (isplanar) {
    Handle(Geom_Geometry) ageom2;
    GetGeom(aConst,ageom2);
    Handle(Geom_Plane) aplane = Handle(Geom_Plane)::DownCast(ageom2);
    if (aplane.IsNull()) {
#ifdef DEB
      cout << "TPrsStd_ConstraintTools::ComputeMinRadius: nul plane" << endl;
#endif
      NullifyAIS(anAIS);
      return;
    }
    ais->SetPlane(aplane);
  }
  anAIS = ais;
}

//=======================================================================
//function : ComputeMaxRadius
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputeMaxRadius (const Handle(TDataXtd_Constraint)& aConst,
						Handle(AIS_InteractiveObject)& anAIS) 
{
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom < 1) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeMaxRadius: at least one constrainte is needed" << endl;    
#endif
    NullifyAIS(anAIS);
    return;
  }

  TopoDS_Shape shape1 ;
  GetOneShape (aConst,shape1);
  if (shape1.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeMaxradius: null shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }

  // POP on teste si ce n'est pas un compound
  if (shape1.ShapeType()==TopAbs_COMPOUND ||
      shape1.ShapeType()==TopAbs_COMPSOLID ||
      shape1.ShapeType()==TopAbs_SOLID ||
      shape1.ShapeType()==TopAbs_SHELL ) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeMaxRadius: not good shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }

  if (IsFace(shape1))
    shape1 = GetFace(shape1);

  Standard_Real val1;
  TCollection_ExtendedString txt;
  ComputeTextAndValue(aConst,val1,txt,Standard_False);

  //  Update de l'AIS
  Standard_Boolean isplanar(aConst->IsPlanar());
  if (isplanar) GetGoodShape(shape1);

  Handle(AIS_MaxRadiusDimension) ais;
  if (!anAIS.IsNull()) {
    ais = Handle(AIS_MaxRadiusDimension)::DownCast(anAIS);
    if (ais.IsNull()) {
      ais = new AIS_MaxRadiusDimension (shape1,val1,txt);
    }
    else {
      ais->SetValue(val1);
      ais->SetFirstShape(shape1);
      ais->SetText(txt);    
    }
  }
  else ais = new AIS_MaxRadiusDimension (shape1,val1,txt);

  if (isplanar) {
    Handle(Geom_Geometry) ageom2;
    GetGeom(aConst,ageom2);
    Handle(Geom_Plane) aplane = Handle(Geom_Plane)::DownCast(ageom2);
    if (aplane.IsNull()) {
#ifdef DEB
      cout << "TPrsStd_ConstraintTools::ComputeMaxRadius: nul plane" << endl;
#endif
      NullifyAIS(anAIS);
      return;
    }
    ais->SetPlane(aplane);
  }
  anAIS = ais;
}

//=======================================================================
//function : ComputeEqualDistance
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputeEqualDistance(const Handle(TDataXtd_Constraint)& aConst,
						   Handle(AIS_InteractiveObject)& anAIS) 
{
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom < 4) {
      cout << "TPrsStd_ConstraintTools::ComputeEqual: at least four geometries are needed" << endl;;
      NullifyAIS(anAIS);
      return;
    }
  TopoDS_Shape aShape1, aShape2, aShape3, aShape4;
  Handle(Geom_Geometry) aGeom;
  GetShapesAndGeom(aConst, aShape1, aShape2, aShape3, aShape4, aGeom);
   if (aShape1.IsNull()||aShape2.IsNull()||
       aShape3.IsNull()||aShape4.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeEqualDistance : null shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }

  GetGoodShape(aShape1);
  GetGoodShape(aShape2);
  GetGoodShape(aShape3);
  GetGoodShape(aShape4);
  
  if (!CheckShapesPair(aShape1, aShape2) || 
      !CheckShapesPair(aShape3, aShape4)){
#ifdef DEB
	cout << "TPrsStd_ConstraintTools::ComputeEqualDistance : at least one pair of shapes is incorrect"<<endl;
#endif
	NullifyAIS(anAIS);
	return;
      }

  //Get the plane
  Standard_Boolean IsPlanar(aConst->IsPlanar());
  Handle(Geom_Plane) aPlane ;
  if(IsPlanar) aPlane = Handle(Geom_Plane)::DownCast(aGeom) ; 
 
  if (!IsPlanar || aPlane.IsNull()) {
    //create the plane
#ifdef DEB
    cout<< "The constraint plane is not assigned "<< endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  
  //Update AIS
  Handle(AIS_EqualDistanceRelation) ais; 
  if (!anAIS.IsNull()) {
    {
      ais = Handle(AIS_EqualDistanceRelation)::DownCast(anAIS);
    
      if (ais.IsNull()) 
	ais = new AIS_EqualDistanceRelation(aShape1, aShape2, aShape3, aShape4, aPlane);
      
      else {
	ais->SetFirstShape(aShape1);
	ais->SetSecondShape(aShape2);
	ais->SetShape3(aShape3);
	ais->SetShape4(aShape4);
	ais->SetPlane(aPlane);
      }
    }
  }
  else ais = new AIS_EqualDistanceRelation(aShape1, aShape2, aShape3, aShape4, aPlane);
  
  anAIS = ais;  

  return;
}

//======================================================================
// function : CheckShapesPair
// purpose  : checks the types of two shapes. 
//            If the types aShape1 and aShape2 are EDGE - EDGE,
//                                              or EDGE - VERTEX,
//                                              or VERTEX - VERTEX,
//                                              or CIRCLE - CIRCLE,
//                                              or CIRCLE - VERTEX,
//            then function returns TRUE, otherwise FALSE.
//======================================================================
static Standard_Boolean CheckShapesPair(const TopoDS_Shape& aShape1, 
				    const TopoDS_Shape& aShape2)
{
  //Check whether the shapes form a correct pair.
  if (aShape1.ShapeType() == TopAbs_EDGE && aShape2.ShapeType() == TopAbs_EDGE)
    {
      BRepAdaptor_Curve aCurve1(TopoDS::Edge(aShape1));
      BRepAdaptor_Curve aCurve2(TopoDS::Edge(aShape2));
      if (aCurve1.GetType() == GeomAbs_Line && aCurve2.GetType() == GeomAbs_Line)
	{ //Are lines parallel ?
	  gp_Dir aDir1 = aCurve1.Line().Direction();
	  gp_Dir aDir2 = aCurve2.Line().Direction();
	  if (!(aDir1.IsParallel(aDir2, Precision::Confusion()))) {
#ifdef DEB
	    cout << " Lines are not parallel"<<endl;
#endif
	    return Standard_False;
	  }
	}
      else if (aCurve1.GetType() == GeomAbs_Circle && aCurve2.GetType() == GeomAbs_Circle)
	{
	  gp_Pnt aCntr1 = aCurve1.Circle().Location(); //get the circle center
	  gp_Pnt aCntr2 = aCurve2.Circle().Location(); //get the circle center
	  if (!aCntr1.IsEqual(aCntr2,Precision::Confusion())){
#ifdef DEB
	    cout << " Circles are not concentric"<<endl;
#endif
	    return Standard_False;
	  }
	}
      else {
#ifdef DEB
	cout << "Incorrect pair of curves "<<endl;
#endif
	return Standard_False;
      }
    }
  else if ( aShape1.ShapeType() != TopAbs_VERTEX || aShape2.ShapeType() != TopAbs_VERTEX)
    {
      gp_Pnt aPnt;
      BRepAdaptor_Curve aCurve;
      if ( aShape1.ShapeType() == TopAbs_VERTEX) {
	aPnt = BRep_Tool::Pnt(TopoDS::Vertex(aShape1));
	aCurve.Initialize(TopoDS::Edge(aShape2));
      }
      else {
	aPnt = BRep_Tool::Pnt(TopoDS::Vertex(aShape2));
	aCurve.Initialize(TopoDS::Edge(aShape1));
      }
      if ( aCurve.GetType() == GeomAbs_Circle)
	{
	  gp_Pnt aCntr = aCurve.Circle().Location();
	  if (!aCntr.IsEqual(aPnt, Precision::Confusion())){
#ifdef DEB
	    cout << " The point doesn't coincide with the circle center"<<endl;
#endif
	    return Standard_False;
	  }
	}
    }
  return Standard_True;
}

//=======================================================================
//function : ComputeEqualRadius
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputeEqualRadius(const Handle(TDataXtd_Constraint)& aConst,
						 Handle(AIS_InteractiveObject)& anAIS) 
{
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom < 2) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeEqualRadius: at least two geometries are needed" << endl;;
#endif
    NullifyAIS(anAIS);
    return;
  }
  TopoDS_Shape shape1, shape2;
  Handle(Geom_Geometry) ageom3;
  
  GetShapesAndGeom(aConst, shape1, shape2, ageom3);
  if (shape1.IsNull()||shape2.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeEqualRadius : null shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  
  //  Update AIS
  Standard_Boolean IsPlanar(aConst->IsPlanar());
 
  GetGoodShape(shape1);
  GetGoodShape(shape2);
  const TopoDS_Edge edge1 = TopoDS::Edge(shape1);
  const TopoDS_Edge edge2 = TopoDS::Edge(shape2);
  Handle(Geom_Plane) aplane ;
  
  if (IsPlanar) aplane = Handle(Geom_Plane)::DownCast(ageom3) ;
  
  if (!IsPlanar || aplane.IsNull()) {
    // check are the planes of edge1 and edge2 coincident
    BRepAdaptor_Curve aCurve( edge1 );
    Handle( Geom_Curve ) aProjCurve = aCurve.Curve().Curve();
    gp_Circ aCircle = (Handle( Geom_Circle )::DownCast( aProjCurve ))->Circ();
    gp_Ax3 anAx31(aCircle.Position()); //get the circle axis
    // get the circle plane 
    Handle(Geom_Plane) aPlane1 = new Geom_Plane (anAx31);

    aCurve.Initialize(edge2);
    aProjCurve = aCurve.Curve().Curve();
    aCircle = (Handle( Geom_Circle )::DownCast( aProjCurve ))->Circ();
    gp_Ax3 anAx32(aCircle.Position()); //get the circle axis
    // get the circle plane 
    Handle(Geom_Plane) aPlane2 = new Geom_Plane (anAx32);

    Standard_Real A, B, C ,D1, D2;
    aPlane1->Coefficients(A, B, C, D1);//Get normalized coefficients
    aPlane2->Coefficients(A, B, C, D2);//Get normalized coefficients
    const gp_Dir& aDir1 = anAx31.Direction();
    const gp_Dir& aDir2 = anAx32.Direction();
    
    if(Abs(D1 - D2) < Precision::Confusion() &&
       aDir1.IsParallel(aDir2, Precision::Confusion()))
      aplane = aPlane2;
    else {
#ifdef DEB
      cout << "TPrsStd_ConstraintTools::ComputeRadiusRelation: nul plane" << endl;
#endif
      NullifyAIS(anAIS);
      return;
    }
  }   
  Handle(AIS_EqualRadiusRelation) ais;
  if (!anAIS.IsNull()) {
    ais = Handle(AIS_EqualRadiusRelation)::DownCast(anAIS);
    
    if (ais.IsNull()) {
      ais = new AIS_EqualRadiusRelation(edge1, edge2, aplane);
      }
    else {
      ais->SetFirstShape(shape1);
      ais->SetSecondShape(shape2);
      ais->SetPlane(aplane);
    }
  }
  else {
    ais = new AIS_EqualRadiusRelation(edge1, edge2, aplane);
  }
  
  anAIS = ais;
}
//ota -- end --

//=======================================================================
//function : ComputeDiameter
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputeDiameter(const Handle(TDataXtd_Constraint)& aConst,
					     Handle(AIS_InteractiveObject)& anAIS) 
{
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom < 1) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeDiameter: at least one constrainte is needed" << endl;;
#endif
    NullifyAIS(anAIS);
    return;
  }
  TopoDS_Shape shape1 ;
  
  GetOneShape(aConst,shape1);
  if (shape1.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeDiameter : null shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  Standard_Real val1;
  TCollection_ExtendedString txt;
  ComputeTextAndValue(aConst,val1,txt,Standard_False);

  //  Update de l'AIS
  Standard_Boolean IsPlanar(aConst->IsPlanar());
  if (IsPlanar) GetGoodShape(shape1);
  Handle(AIS_DiameterDimension) ais;
  if (!anAIS.IsNull()) {
    ais = Handle(AIS_DiameterDimension)::DownCast(anAIS);
    if (ais.IsNull()) {
      ais = new AIS_DiameterDimension (shape1,val1,txt);
    }
    else {
      ais->SetFirstShape(shape1);
      ais->SetValue(val1);
      ais->SetText(txt);
    }
  }
  else ais = new AIS_DiameterDimension (shape1,val1,txt);

  if (IsPlanar) {
    Handle(Geom_Geometry) ageom2;
    GetGeom(aConst,ageom2);
    Handle(Geom_Plane) aplane = Handle(Geom_Plane)::DownCast(ageom2);
    if (aplane.IsNull()) {
#ifdef DEB
      cout << "TPrsStd_ConstraintTools::ComputeDiameter: nul plane" << endl;
#endif
      NullifyAIS(anAIS);
      return;
    }
    ais->SetPlane(aplane);
  }
  anAIS = ais;
}


//=======================================================================
//function : ComputeFix
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputeFix(const Handle(TDataXtd_Constraint)& aConst,
					Handle(AIS_InteractiveObject)& anAIS) 
{
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom < 1) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeFix: at least one constrainte is needed" << endl;;
#endif
    NullifyAIS(anAIS);
    return;
  }
  if (!aConst->IsPlanar()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeFix: must be a planar constraint" << endl;;
#endif
    NullifyAIS(anAIS);
    return;
  }

  TopoDS_Shape shape1 ;
  Handle(Geom_Geometry) ageom2;
  
  GetOneShape(aConst,shape1);
  if (shape1.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeFix : null shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }  
  GetGoodShape(shape1);
  GetGeom(aConst,ageom2);
  Handle(Geom_Plane) aplane = Handle(Geom_Plane)::DownCast(ageom2);
  if (aplane.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeFix: nul plane" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  //  Update de l'AIS
  Handle(AIS_FixRelation) ais;
  if (!anAIS.IsNull()) {
    ais = Handle(AIS_FixRelation)::DownCast(anAIS);
    if (ais.IsNull()) {
      ais = new AIS_FixRelation (shape1,aplane);
    }
    else {
      ais->SetFirstShape(shape1);
      ais->SetPlane(aplane);
    }
  }
  else ais = new AIS_FixRelation (shape1,aplane);

  anAIS = ais;
}

//=======================================================================
//function : ComputeOffset
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputeOffset (const Handle(TDataXtd_Constraint)& aConst,
					    Handle(AIS_InteractiveObject)& anAIS) 
{
  // Get plane for planar constraint
  Standard_Boolean is_planar (aConst->IsPlanar());
  Handle(Geom_Plane) aplane;      
  if (is_planar) {
    GetGeom (aConst,aplane);
    if (aplane.IsNull()) {
#ifdef DEB
      cout << "TPrsStd_ConstraintTools::ComputeOffset: null plane" << endl;
#endif
      NullifyAIS(anAIS);
      return;
    }
  }

  // Get shapes
  TopoDS_Shape S1, S2;
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom == 1) {
    Handle(TNaming_NamedShape) ageom1 = aConst->GetGeometry(1);
    // c'est une shape qui contient les faces generees par les faces d'origines
    TNaming_Iterator It (ageom1);
    if (It.More()) {
      S1 = It.OldShape();
      S2 = It.NewShape();
    }
  }
  else
  if (nbgeom == 2)  {
    // Get geometry of the constraint
    GetTwoShapes (aConst,S1,S2);
  }

  if (S1.IsNull() || S2.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeOffset: null shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }


  Standard_Real val1;
  TCollection_ExtendedString txt;
  Handle(AIS_LengthDimension) ais;
  //Handle(AIS_Drawer) aDrawer;
  Standard_Boolean NotNull = Standard_False;

  if (nbgeom == 1) {
      
    ComputeTextAndValue (aConst,val1,txt,Standard_False);
  
    if (!anAIS.IsNull()) {
      ais = Handle(AIS_LengthDimension)::DownCast(anAIS);
      NotNull = Standard_True; 
    }
   
    if (S1.ShapeType() == TopAbs_FACE && S2.ShapeType() == TopAbs_FACE) {
      if (ais.IsNull()) {
	ais = new AIS_LengthDimension (TopoDS::Face(S1),TopoDS::Face(S2),
				       val1,txt);
      }
      else {
	ais->SetFirstShape(S1);
	ais->SetSecondShape(S2);
	ais->SetValue(val1);
	ais->SetText(txt);
      }

      if (is_planar) ais->SetPlane (aplane);
      anAIS = ais;
      return;
    }
    else
    if (S1.ShapeType() == TopAbs_EDGE && S2.ShapeType() == TopAbs_EDGE) {
      // Find a plane for the dimension
      TopoDS_Edge OE = TopoDS::Edge(S1);
      BRepAdaptor_Curve CURVE(OE);
      if (CURVE.GetType() == GeomAbs_Line)  {
	// Works only with line !!
//#ifndef DEB
        Handle_Geom_Geometry aGeomGeometry = CURVE.Curve().Curve()->Transformed(CURVE.Trsf()) ;
        gp_Lin OLin = ((Handle(Geom_Line)&) aGeomGeometry)->Lin();
//#else
//	gp_Lin OLin = ((Handle(Geom_Line)&) CURVE.Curve().Curve()->Transformed(CURVE.Trsf()))->Lin();
//#endif
	TopoDS_Edge NE = TopoDS::Edge(S2);
	CURVE.Initialize (NE);
//#ifndef DEB
        aGeomGeometry = CURVE.Curve().Curve()->Transformed(CURVE.Trsf()) ;
        gp_Lin NLin = ((Handle(Geom_Line)&)aGeomGeometry)->Lin();
//#else
//	gp_Lin NLin = ((Handle(Geom_Line)&) CURVE.Curve().Curve()->Transformed(CURVE.Trsf()))->Lin();
//#endif
	gp_Dir TDir (NLin.Location().XYZ() - OLin.Location().XYZ());
	aplane = new Geom_Plane (NLin.Location(),NLin.Direction()^TDir);

	if (ais.IsNull()) {
	  ais = new AIS_LengthDimension (S1,S2,aplane,val1,txt);
	}
	else {
	  ais->SetFirstShape(S1);
	  ais->SetSecondShape(S2);
	  ais->SetValue(val1);
	  ais->SetText(txt);
	  ais->SetPlane(aplane);
	}
	anAIS = ais;
	return;
      }
      else
      if (CURVE.GetType() == GeomAbs_Circle)  {
//#ifndef DEB
        Handle_Geom_Geometry aGeomGeometry = CURVE.Curve().Curve()->Transformed(CURVE.Trsf()) ;
        gp_Ax1 ax = ((Handle(Geom_Circle)&) aGeomGeometry)->Circ().Axis();
//#else
//	gp_Ax1 ax = ((Handle(Geom_Circle)&) CURVE.Curve().Curve()->Transformed(CURVE.Trsf()))->Circ().Axis();
//#endif
	aplane = new Geom_Plane (ax.Location(),ax.Direction());
	is_planar = Standard_True;
      }
    }
  }


  if (!is_planar)  {
    if (S1.ShapeType() == TopAbs_COMPOUND && 
	S2.ShapeType() == TopAbs_COMPOUND)  {
      // Resultat d'un offset - on reconstruit un wire pour determiner un plan
      TopoDS_Wire w1;
      BRep_Builder B;
      B.MakeWire (w1);
      TopExp_Explorer exp (S1,TopAbs_EDGE);
      for (;exp.More();exp.Next())
	B.Add (w1,exp.Current());

      BRepBuilderAPI_MakeFace MkF (w1,Standard_True);
      if (MkF.IsDone())  {
//#ifndef DEB
        Handle_Geom_Surface aGeomSurface = BRep_Tool::Surface(MkF.Face());
        aplane = (Handle(Geom_Plane)&) aGeomSurface ;
//#else
//	aplane = ((Handle(Geom_Plane)&) BRep_Tool::Surface(MkF.Face()));
//#endif
	is_planar = Standard_True;
      }
    }
  }

  if (is_planar) {
    ComputeTextAndValue (aConst,val1,txt,Standard_False);
    TopExp_Explorer EXP1 (S1,TopAbs_VERTEX);
    S1 = EXP1.Current();
    gp_Pnt P = BRep_Tool::Pnt(TopoDS::Vertex(S1));
      
    TopoDS_Vertex nearest;
    Standard_Real dist(RealLast());

    for (TopExp_Explorer EXP2(S2,TopAbs_VERTEX); EXP2.More(); EXP2.Next()) {
      const TopoDS_Vertex& current = TopoDS::Vertex(EXP2.Current());
      gp_Pnt curpnt = BRep_Tool::Pnt(current);
      Standard_Real curdist = P.SquareDistance(curpnt);
      if (curdist < dist) {
	nearest= current;
	dist = curdist;
      }
    }
    S2 = nearest;
    if( !anAIS.IsNull() ) NotNull = Standard_True; 
    ais = Handle(AIS_LengthDimension)::DownCast(anAIS);
    if (ais.IsNull()) {
      ais = new AIS_LengthDimension (S1,S2,aplane,val1,txt);
    }
    else {
      ais->SetFirstShape (S1);
      ais->SetSecondShape (S2);
      ais->SetValue(val1);
      ais->SetText(txt);
      ais->SetPlane(aplane);
    }
    anAIS = ais;
    return;
  }

#ifdef DEB
  cout << "TPrsStd_ConstraintTools::ComputeOffset: Case not implemented" << endl;
#endif
  NullifyAIS(anAIS);
}


//=======================================================================
//function : ComputePlacement
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputePlacement
(const Handle(TDataXtd_Constraint)& aConst,
 Handle(AIS_InteractiveObject)& anAIS) 
{
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom < 2) 
    Standard_ProgramError::Raise
      ("TPrsStd_ConstraintTools::ComputePlacement: at leat two constraints are needed");
  
  TopoDS_Shape shape1,shape2 ;
  GetTwoShapes(aConst,shape1,shape2);
  if (shape1.IsNull() || shape2.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputePlacement: nul shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  
  Standard_Real val1=0.0;
  TCollection_ExtendedString txt= " ";
  if (aConst->IsDimension()) {
    ComputeTextAndValue(aConst,val1,txt,Standard_False);
  }
  //  Update de l'AIS
  Handle(AIS_OffsetDimension) ais;
  if (anAIS.IsNull()) {
    ais = new AIS_OffsetDimension(GetFace(shape1),GetFace(shape2),val1,txt);
    ais->SetArrowSize(val1/20.);
  } else {
    ais = Handle(AIS_OffsetDimension)::DownCast(anAIS);
    if (ais.IsNull()) {
      ais = new AIS_OffsetDimension(GetFace(shape1),GetFace(shape2),val1,txt);
      ais->SetArrowSize(val1/20.);
    } else {
      ais->SetFirstShape(GetFace(shape1));
      ais->SetSecondShape(GetFace(shape2));
      ais->SetValue(val1);
      ais->SetText(txt);
      ais->SetArrowSize(val1/20.);
    }
  }
  if (GetFace(shape1).IsNull() || GetFace(shape2).IsNull()) ais.Nullify();
  anAIS = ais;
}

//=======================================================================
//function : ComputeOthers
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputeOthers
(const Handle(TDataXtd_Constraint)& aConst,
 Handle(AIS_InteractiveObject)& anAIS) 
{
}

//=======================================================================
//function : GetOneShape
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::GetOneShape
(const Handle(TDataXtd_Constraint)& aConst,
 TopoDS_Shape& aShape) 
{
  const Handle(TNaming_NamedShape)& ageom1 = aConst->GetGeometry(1);
  if (!ageom1.IsNull()) aShape =  TNaming_Tool::CurrentShape(ageom1);
}

//=======================================================================
//function : GetTwoShapes
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::GetTwoShapes
(const Handle(TDataXtd_Constraint)& aConst,
 TopoDS_Shape& aShape1,
 TopoDS_Shape& aShape2) 
{
  const Handle(TNaming_NamedShape)& ageom1 = aConst->GetGeometry(1);    
  if (!ageom1.IsNull()) aShape1 =  TNaming_Tool::CurrentShape(aConst->GetGeometry(1));
  const Handle(TNaming_NamedShape)& ageom2 = aConst->GetGeometry(2);    
  if (!ageom2.IsNull()) aShape2 =  TNaming_Tool::CurrentShape(aConst->GetGeometry(2));
}

//=======================================================================
//function : GetShapesAndGeom
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::GetShapesAndGeom
(const Handle(TDataXtd_Constraint)& aConst,
 TopoDS_Shape& aShape1,
 TopoDS_Shape& aShape2,
 Handle(Geom_Geometry)& aGeom) 
{
  GetTwoShapes(aConst,aShape1,aShape2);
  GetGeom(aConst,aGeom);
}

//=======================================================================
//function : GetShapesAndGeom
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::GetShapesAndGeom
(const Handle(TDataXtd_Constraint)& aConst,
 TopoDS_Shape& aShape1,
 TopoDS_Shape& aShape2,
 TopoDS_Shape& aShape3,
 Handle(Geom_Geometry)& aGeom) 
{
  GetTwoShapes(aConst,aShape1,aShape2);
  const Handle(TNaming_NamedShape)& ageom3 = aConst->GetGeometry(3);//ota: GetGeometry(2) was  
  if (!ageom3.IsNull()) aShape3 =  TNaming_Tool::CurrentShape(aConst->GetGeometry(3));
  GetGeom(aConst,aGeom);
}

//=======================================================================
//function : GetShapesAndGeom
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::GetShapesAndGeom
  (const Handle(TDataXtd_Constraint)& aConst,
   TopoDS_Shape& aShape1,
   TopoDS_Shape& aShape2,
   TopoDS_Shape& aShape3,
   TopoDS_Shape& aShape4,
   Handle(Geom_Geometry)& aGeom) 
{
  GetTwoShapes(aConst,aShape1, aShape2 );
  const Handle(TNaming_NamedShape)& ageom3 = aConst->GetGeometry(3);    
  if (!ageom3.IsNull()) aShape3 =  TNaming_Tool::CurrentShape(aConst->GetGeometry(3));
  const Handle(TNaming_NamedShape)& ageom4 = aConst->GetGeometry(4); 
  if (!ageom4.IsNull()) aShape4 =  TNaming_Tool::CurrentShape(aConst->GetGeometry(4));
  GetGeom(aConst,aGeom);
}

//=======================================================================
//function : ComputeCoincident
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputeCoincident(const Handle(TDataXtd_Constraint)& aConst,
					       Handle(AIS_InteractiveObject)& anAIS) 
{
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom < 2) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeCoincident: at leat two constraintes are needed" << endl;
#endif
    NullifyAIS(anAIS);
    return; 
  }
  
  if (!aConst->IsPlanar()) { 
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeCoincident: must be a planar constraint" << endl;
#endif
    anAIS.Nullify() ; 
    return;
  }
  
  TopoDS_Shape shape1,shape2 ;
  Handle(Geom_Plane) aplane;
  GetShapesAndGeom(aConst,shape1,shape2,aplane);
  if (shape1.IsNull() || shape2.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeCoincident: nul shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }

  GetGoodShape(shape1);
  GetGoodShape(shape2);
  if (aplane.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeCoincident: nul plane" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  
  //  Update de l'AIS
  Handle(AIS_IdenticRelation) ais;
  if (anAIS.IsNull()) ais = new AIS_IdenticRelation(shape1,shape2,aplane);
  else {
    ais = Handle(AIS_IdenticRelation)::DownCast(anAIS);
    if (ais.IsNull()) {
      ais = new AIS_IdenticRelation(shape1,shape2,aplane);
    }
    else {
      ais->SetFirstShape(shape1);
      ais->SetSecondShape(shape2);
      ais->SetPlane(aplane);
    }
  }
  anAIS = ais;
}

//=======================================================================
//function : ComputeRound
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::ComputeRound(const Handle(TDataXtd_Constraint)& aConst,
					       Handle(AIS_InteractiveObject)& anAIS) 
{
  Standard_Integer nbgeom = aConst->NbGeometries();
  if (nbgeom < 1) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputeRound: at leat one geometry is needed" << endl;
#endif
    NullifyAIS(anAIS);
    return; 
  }
  TopoDS_Shape shape1;
  GetOneShape (aConst,shape1);
  if (shape1.IsNull()) {
#ifdef DEB
    cout << "TPrsStd_ConstraintTools::ComputePlacement: nul shape" << endl;
#endif
    NullifyAIS(anAIS);
    return;
  }
  
  Standard_Real val1;
  TCollection_ExtendedString txt;
  ComputeTextAndValue(aConst,val1,txt,Standard_False);
  
  //  Update de l'AIS
  Handle(AIS_RadiusDimension) ais;

  {
   try {
     OCC_CATCH_SIGNALS
     if (anAIS.IsNull()) ais = 
       new AIS_RadiusDimension(shape1,val1,txt);
     else {
       ais = Handle(AIS_RadiusDimension)::DownCast(anAIS);
       if (ais.IsNull()) {
	 ais = new AIS_RadiusDimension(shape1,val1,txt);
       }
       else {
	 ais->SetValue(val1);
	 ais->SetText(txt);
	 ais->SetFirstShape(shape1);
       }
     }
   }
   catch(Standard_Failure) {
     ais.Nullify();
   }
 }
  anAIS = ais;
}

//=======================================================================
//function : GetGeom
//purpose  : 
//=======================================================================
void TPrsStd_ConstraintTools::GetGeom(const Handle(TDataXtd_Constraint)& aConst,
				     Handle(Geom_Geometry)& aGeom)
{  
  Handle(TNaming_NamedShape) atgeom = aConst->GetPlane();
  if (atgeom.IsNull()) {
#ifdef DEB    
    cout<<"TPrsStd_ConstraintTools::GetGeom : aConst->GetPlane().IsNull()"<<endl;
#endif
    return;
  }
  gp_Pln aplane;
  gp_Lin anaxis;
  gp_Pnt apoint;
  
  TDF_Label label = atgeom->Label();

  Handle(TNaming_NamedShape) NS;
  if(label.FindAttribute(TNaming_NamedShape::GetID(),NS)){
    TopoDS_Shape s = TNaming_Tool::GetShape(NS);
    if(s.IsNull()) return;
  }

  if (TDataXtd_Geometry::Plane(label,aplane)) aGeom =  new Geom_Plane(aplane);
  else if (TDataXtd_Geometry::Line(label,anaxis)) aGeom =  new Geom_Line(anaxis);
  else if (TDataXtd_Geometry::Point(label,apoint)) aGeom =  new Geom_CartesianPoint(apoint);
#ifdef DEB
  else {
    cout << "TPrsStd_ConstraintTools::GetGeom no geom on label " << endl;
  }
#endif  
}

