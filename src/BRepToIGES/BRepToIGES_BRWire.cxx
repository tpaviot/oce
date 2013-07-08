// Created on: 1995-01-27
// Created by: Marie Jose MARTZ
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

//:q4 abv 16.03.99: PRO17828 face 555: transform pcurves on SurfaceOfRevolution
//szv#4 S4163
//S4181 pdn implementing of writing IGES elementary surfaces.

#include <BRepToIGES_BRWire.ixx>

#include <BRep_Tool.hxx>
#include <BRepTools.hxx>
#include <BRepTools_WireExplorer.hxx>

#include <gp.hxx>
#include <gp_Ax2d.hxx>
#include <gp_Dir2d.hxx>
#include <gp_Pln.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Trsf.hxx>
#include <gp_Trsf2d.hxx>

#include <Geom_CartesianPoint.hxx>
#include <Geom_ConicalSurface.hxx>
#include <Geom_Curve.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Geom_Plane.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom_SphericalSurface.hxx>
#include <Geom_Surface.hxx>
#include <Geom_SurfaceOfLinearExtrusion.hxx>
#include <Geom_SurfaceOfRevolution.hxx>
#include <Geom_ToroidalSurface.hxx>
#include <Geom_TrimmedCurve.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom2d_Line.hxx>

#include <GeomToIGES_GeomPoint.hxx>
#include <GeomToIGES_GeomCurve.hxx>

#include <Geom2dToIGES_Geom2dCurve.hxx>

#include <IGESData_HArray1OfIGESEntity.hxx>
#include <IGESData_IGESEntity.hxx>
#include <IGESData_IGESModel.hxx>

#include <IGESGeom_CompositeCurve.hxx>
#include <IGESGeom_Point.hxx>

#include <Interface_Macros.hxx>

#include <Precision.hxx>

#include <TColStd_HSequenceOfTransient.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Shape.hxx>

#include <TopAbs_ShapeEnum.hxx>
#include <TopAbs_Orientation.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <Interface_Static.hxx>
#include <ShapeBuild_Edge.hxx>
#include <Geom_OffsetSurface.hxx>
#include <ShapeExtend_WireData.hxx>
#include <ShapeFix_Wire.hxx>


//=============================================================================
// BRepToIGES_BRWire
//=============================================================================

BRepToIGES_BRWire::BRepToIGES_BRWire()
{
}


//=============================================================================
// BRepToIGES_BRWire
//=============================================================================

BRepToIGES_BRWire::BRepToIGES_BRWire
(const BRepToIGES_BREntity& BR)
: BRepToIGES_BREntity(BR)
{
}


//=============================================================================
// TransferWire
//=============================================================================

Handle(IGESData_IGESEntity) BRepToIGES_BRWire ::TransferWire
(const TopoDS_Shape& start)
{
  Handle(IGESData_IGESEntity) res;

  if (start.IsNull())  return  res;

  if (start.ShapeType() == TopAbs_VERTEX) {
    TopoDS_Vertex V =  TopoDS::Vertex(start);
    res = TransferVertex(V);
  }  
  else if (start.ShapeType() == TopAbs_EDGE) {
    TopoDS_Edge E =  TopoDS::Edge(start);
    res = TransferEdge(E, Standard_False);
  }  
  else if (start.ShapeType() == TopAbs_WIRE) {
    TopoDS_Wire W =  TopoDS::Wire(start);
    res = TransferWire(W);
  }  
  else {
    // error message
  }  
  return res;
}


//=============================================================================
// TransferVertex
// 
//=============================================================================

Handle(IGESData_IGESEntity) BRepToIGES_BRWire ::TransferVertex
(const TopoDS_Vertex& myvertex)
{
  Handle(IGESData_IGESEntity) res;
  if ( myvertex.IsNull()) return res;

  Handle(Geom_CartesianPoint) Point;
  Point = new Geom_CartesianPoint(BRep_Tool::Pnt(myvertex));
  Handle(IGESData_IGESEntity) IVertex;
  if (!Point.IsNull()) {
    GeomToIGES_GeomPoint GP;
    GP.SetModel(GetModel());
    IVertex = GP.TransferPoint(Point);
  }

  if (!IVertex.IsNull()) res = IVertex;
  return res;
}


//=============================================================================
// TransferVertex
// 
//=============================================================================

Handle(IGESData_IGESEntity) BRepToIGES_BRWire ::TransferVertex
(const TopoDS_Vertex& myvertex,
 const TopoDS_Edge&   myedge,
 Standard_Real&       parameter)
{
  Handle(IGESData_IGESEntity) res;
  if ( myvertex.IsNull()) return res;

  Handle(IGESData_IGESEntity) IVertex = TransferVertex(myvertex);

  // returns the parameter of myvertex on myedge
  parameter = BRep_Tool::Parameter(myvertex,myedge);

  if (!IVertex.IsNull()) res = IVertex;
  return res;
}


//=============================================================================
// TransferVertex
// 
//=============================================================================

Handle(IGESData_IGESEntity) BRepToIGES_BRWire ::TransferVertex
(const TopoDS_Vertex& myvertex,
 const TopoDS_Edge&   myedge,
 const TopoDS_Face&   myface,
 Standard_Real&       parameter)
{
  Handle(IGESData_IGESEntity) res;
  if ( myvertex.IsNull()) return res;

  Handle(IGESData_IGESEntity) IVertex = TransferVertex(myvertex);

  // returns the parameter of myvertex on the pcurve of myedge on myface
  parameter = BRep_Tool::Parameter(myvertex, myedge, myface);

  if (!IVertex.IsNull()) res = IVertex;
  return res;
}


//=============================================================================
// TransferVertex
// 
//=============================================================================

Handle(IGESData_IGESEntity) BRepToIGES_BRWire ::TransferVertex
(const TopoDS_Vertex&          myvertex,
 const TopoDS_Edge&            myedge,
 const Handle(Geom_Surface)&   mysurface,
 const TopLoc_Location&        myloc,
 Standard_Real&                parameter)
{
  Handle(IGESData_IGESEntity) res;
  if ( myvertex.IsNull()) return res;

  Handle(IGESData_IGESEntity) IVertex = TransferVertex(myvertex);

  // returns the parameter of myvertex on the pcurve of myedge on mysurface
  parameter = BRep_Tool::Parameter(myvertex, myedge, mysurface, myloc);

  if (!IVertex.IsNull()) res = IVertex;
  return res;
}


//=============================================================================
// TransferVertex
// 
//=============================================================================

Handle(IGESData_IGESEntity) BRepToIGES_BRWire ::TransferVertex
(const TopoDS_Vertex& myvertex,
 const TopoDS_Face&   myface,
       gp_Pnt2d&      mypoint)
{
  Handle(IGESData_IGESEntity) res;
  if ( myvertex.IsNull()) return res;

  Handle(IGESData_IGESEntity) IVertex = TransferVertex(myvertex);

  // returns the parameter of myvertex on myface
  mypoint = BRep_Tool::Parameters(myvertex, myface);

  if (!IVertex.IsNull()) res = IVertex;
  return res;
}


//=============================================================================
// TransferEdge
//=============================================================================

Handle(IGESData_IGESEntity) BRepToIGES_BRWire ::TransferEdge
(const TopoDS_Edge&     myedge,
 const Standard_Boolean isBRepMode)
{
  Handle(IGESData_IGESEntity) res;
  if ( myedge.IsNull()) return res;

  // returns the 3d curve of the edge and the parameter range
  TopLoc_Location L;
  Standard_Real First, Last, U1, U2;
  Handle(IGESData_IGESEntity) ICurve;
  Handle(Geom_Curve) Curve3d = BRep_Tool::Curve(myedge, L, First, Last);

  //#28 rln 19.10.98 UKI60155, etc.
  //Only Bezier will be converted into B-Spline, not Conic. This conertation
  //will be done only inside GeomToIGES package for simplifying the code.

  //#29 rln 19.10.98
  //Unnecessary duplication of curves is removed.

  if (!Curve3d.IsNull()) {
    gp_Trsf Tr = L.Transformation();
    if (Tr.Form() != gp_Identity)
      Curve3d = Handle(Geom_Curve)::DownCast(Curve3d->Transformed (Tr));
    else
      Curve3d = Handle(Geom_Curve)::DownCast(Curve3d->Copy()); 

    if (myedge.Orientation() == TopAbs_REVERSED && !isBRepMode) {
      U1 = Curve3d->ReversedParameter(Last);
      U2 = Curve3d->ReversedParameter(First);
      Curve3d->Reverse();
    }
    else {
      U1 = First;
      U2 = Last;
    }

    GeomToIGES_GeomCurve GC;
    GC.SetModel(GetModel());
    ICurve = GC.TransferCurve(Curve3d, U1, U2);
  }

  //#31 rln 19.10.98
  //Vertices are not translated into IGES anymore since they are not put into
  //the model

  if (!ICurve.IsNull()) res = ICurve;

  SetShapeResult ( myedge, res );

  return res;
}


//=============================================================================
// TransferEdge
//=============================================================================

Handle(IGESData_IGESEntity) BRepToIGES_BRWire ::TransferEdge (const TopoDS_Edge& myedge,
							      const TopoDS_Face& myface,
							      const Standard_Real length,
							      const Standard_Boolean isBRepMode)
{
  Handle(IGESData_IGESEntity) res;
  if ( myedge.IsNull() || GetPCurveMode() ==0 ||
       ( ! isBRepMode && BRep_Tool::Degenerated ( myedge ) ) ) return res;

  //S4181 pdn 23.04.99 adjusting length factor according to analytic mode.
  Standard_Real myLen = length;
  Standard_Boolean analyticMode = ( GetConvertSurfaceMode() ==0 && isBRepMode );
  
  // returns the 2d curve associated to myedge in the parametric space of myface
  Standard_Real First, Last;
  Handle(Geom2d_Curve) Curve2d = BRep_Tool::CurveOnSurface(myedge, myface, First, Last);
  Handle(IGESData_IGESEntity) ICurve2d;
  //#29 rln 19.10.98

  if (!Curve2d.IsNull()) {
    // For "revolution" and "LinearExtrusion" surfaces, it is necessary
    // to apply a translation of 2D curves to agree on the 
    // origin (U,V) between IGES and BRep (for Cylindrical,
    // Conical and SurfaceOfLinearExtrusion)
    // It is necessary to invert (u,v) surfaces of revolution.
    
    TopLoc_Location L;
    Handle(Geom_Surface) st = BRep_Tool::Surface(myface, L);
    if (st->IsKind(STANDARD_TYPE(Geom_Plane))){
      return res;
    }
    Standard_Real Ufirst, Ulast, Vfirst, Vlast;
    BRepTools::UVBounds(myface, Ufirst, Ulast, Vfirst, Vlast);
    Handle(Geom_Surface) Surf;

    if (st->IsKind(STANDARD_TYPE(Geom_RectangularTrimmedSurface))) { 
      DeclareAndCast(Geom_RectangularTrimmedSurface, rectang, st);
      Surf = rectang->BasisSurface();
    }
    else 
      Surf = st;

    //:abv 19.06.02: writing (loopback) on file offseted_sphere.rle in BRep mode
    if (st->IsKind(STANDARD_TYPE(Geom_OffsetSurface))) { 
      DeclareAndCast(Geom_OffsetSurface, offset, Surf);
      Surf = offset->BasisSurface();
    }

    //S4181 pdn 20.04.99 transformation of pcurves id defined by type of surface 
    // and analytic mode.
    // skl 18.07.2005 for OCC9490 : in following if() commented
    // condition for SurfaceOfLinearExtrusion
    Standard_Boolean needShift = (!analyticMode&&
                                  ((Surf->IsKind(STANDARD_TYPE(Geom_CylindricalSurface))) ||
                                   (Surf->IsKind(STANDARD_TYPE(Geom_ConicalSurface)))/* ||
                                   (Surf->IsKind(STANDARD_TYPE(Geom_SurfaceOfLinearExtrusion)))*/));
    //:q4 abv 16 Mar 99: PRO17828 face 555: shift pcurves on SurfaceOfRevolution
    if (Surf->IsKind(STANDARD_TYPE(Geom_SurfaceOfRevolution))) { 
      Handle(Geom_SurfaceOfRevolution) rev = 
	Handle(Geom_SurfaceOfRevolution)::DownCast ( Surf );
      Handle(Geom_Curve) curve = rev->BasisCurve();
      // skl 31.05.2004 for OCC6004
      if(curve->IsKind(STANDARD_TYPE(Geom_TrimmedCurve))) {
        Handle(Geom_TrimmedCurve) tc = Handle(Geom_TrimmedCurve)::DownCast(curve);
        curve = tc->BasisCurve();
      }
      if ( curve->IsKind(STANDARD_TYPE(Geom_Line)) ) needShift = Standard_True;
    }
    if ( needShift ) {
      gp_Trsf2d TR;
      TR.SetTranslation(gp_Pnt2d(0.,0.),gp_Pnt2d(0.,-Vfirst)); 
      Curve2d = Handle(Geom2d_Curve)::DownCast(Curve2d->Transformed(TR));
    }
    else Curve2d = Handle(Geom2d_Curve)::DownCast(Curve2d->Copy());

    if (!analyticMode&&((Surf->IsKind(STANDARD_TYPE(Geom_CylindricalSurface)))  ||
			(Surf->IsKind(STANDARD_TYPE(Geom_ConicalSurface)))      ||
			(Surf->IsKind(STANDARD_TYPE(Geom_SphericalSurface))))) {
      //#30 rln 19.10.98 transformation of pcurves for IGES Surface of Revolution
      Curve2d->Mirror (gp_Ax2d (gp::Origin2d(), gp_Dir2d (1.,1.)));
      Curve2d->Mirror (gp::OX2d());
      Curve2d->Translate (gp_Vec2d (0, 2 * M_PI));
    }
    
    if(Surf->IsKind(STANDARD_TYPE(Geom_SurfaceOfRevolution))||
       (Surf->IsKind(STANDARD_TYPE(Geom_ToroidalSurface)))){
      Curve2d->Mirror (gp_Ax2d (gp::Origin2d(), gp_Dir2d (1.,1.)));
      Curve2d->Mirror (gp::OX2d());
      Curve2d->Translate (gp_Vec2d (0, 2 * M_PI));
    }
    
    if (analyticMode&&(Surf->IsKind(STANDARD_TYPE(Geom_CylindricalSurface)) ||
		       Surf->IsKind(STANDARD_TYPE(Geom_ConicalSurface))))
      myLen = M_PI/180.;
    
    if (analyticMode&&(Surf->IsKind(STANDARD_TYPE(Geom_SphericalSurface)) ||
		       Surf->IsKind(STANDARD_TYPE(Geom_ToroidalSurface)))) {
      gp_Trsf2d trans;
      trans.SetScale(gp_Pnt2d(0,0),180./M_PI);
      Curve2d->Transform(trans);
      First = Curve2d->TransformedParameter(First,trans);
      Last  = Curve2d->TransformedParameter(Last, trans);
    }
    
    if (analyticMode&&(Surf->IsKind(STANDARD_TYPE(Geom_ConicalSurface)))) {
      Handle(Geom_ConicalSurface) con = Handle(Geom_ConicalSurface)::DownCast ( Surf );
      if(con->SemiAngle() < 0) {
	Standard_Real vApex = 2 * con->RefRadius() / Sin (con->SemiAngle());
	Curve2d->Translate (gp_Vec2d (0, vApex));
      }
    }
    //S4181 transfer functionality
    gp_Trsf2d trans;
    Standard_Real uFact = 1.;
    if(isBRepMode && Surf->IsKind(STANDARD_TYPE(Geom_Plane))) {
      trans.SetScale(gp_Pnt2d(0,0),1./GetUnit());
    }
    if(Surf->IsKind(STANDARD_TYPE(Geom_SurfaceOfLinearExtrusion))) {
      Standard_Real aDiv = myLen;
      if(aDiv < gp::Resolution())
        aDiv = 1.;
      //emv: changed for bug OCC22126 17.12.2010
      trans.SetScale(gp_Pnt2d(0,0), 1. / (Vlast - Vfirst));
      //uFact = myLen; 
      
      //added by skl 18.07.2005 for OCC9490
//      trans.SetScale(gp_Pnt2d(0,0),1./Vlast);

      Standard_Real du = 1.;
      Standard_Real us1,us2,vs1,vs2;
      //scaling parameterization to [0,1]
      Surf->Bounds(us1,us2,vs1,vs2);
      du = us2-us1;
      //emv: changed for bug OCC22126 17.12.2010
      uFact = (Vlast - Vfirst)/du;
      //uFact = aDiv/du;
    }
    if (Surf->IsKind(STANDARD_TYPE(Geom_CylindricalSurface)) ||
	Surf->IsKind(STANDARD_TYPE(Geom_ConicalSurface)) ||
	Surf->IsKind(STANDARD_TYPE(Geom_SurfaceOfRevolution))) { //:q4
      uFact = 1./myLen; 
    }
    
    ShapeBuild_Edge sbe;
    Curve2d = sbe.TransformPCurve(Curve2d,trans,uFact,First,Last);
//      (Curve2d, Surf, First, Last, myLen, isBRepMode);
    // if the edge is REVERSED, it is necessary to "REVERSE" the curve 2d.

    // added by skl 18.07.2005 for OCC9490
    if(Surf->IsKind(STANDARD_TYPE(Geom_SurfaceOfLinearExtrusion))) {
      //emv: changed for bug OCC22126 17.12.2010
      gp_Trsf2d trans1;
      Standard_Real us1,us2,vs1,vs2,du;
      //computing shift of pcurves
      Surf->Bounds(us1,us2,vs1,vs2);
      du = us2-us1;
      trans1.SetTranslation(gp_Vec2d(-us1/du,-Vfirst/(Vlast-Vfirst)));
      Curve2d = sbe.TransformPCurve(Curve2d,trans1,1.,First,Last);
    }

    if (myedge.Orientation() == TopAbs_REVERSED) {
      Standard_Real tmpFirst = Curve2d->ReversedParameter(Last),
                    tmpLast  = Curve2d->ReversedParameter(First);
      Curve2d->Reverse();
      First = tmpFirst;
      Last  = tmpLast;
    }
    Geom2dToIGES_Geom2dCurve GC;
    GC.SetModel(GetModel());
    ICurve2d = GC.Transfer2dCurve(Curve2d, First, Last);
  }

  //#31 rln 19.10.98
  //Vertices are not translated into IGES anymore since they are not put into
  //the model

  if (!ICurve2d.IsNull()) res = ICurve2d;

  SetShapeResult ( myedge, res );

  return res;
}


//=============================================================================
// TransferWire
//=============================================================================

Handle(IGESData_IGESEntity) BRepToIGES_BRWire ::TransferWire
(const TopoDS_Wire& mywire)
{
  Handle(IGESData_IGESEntity) res;
  if ( mywire.IsNull()) return res;

  //A composite curve is defined as an ordered list of entities
  //consisting of a point, connect point and parametrised curve
  //entities (excluding the CompositeCurve entity).

  Handle(IGESData_IGESEntity) ent ;
  Handle(TColStd_HSequenceOfTransient) Seq = new TColStd_HSequenceOfTransient();

  TopExp_Explorer TE(mywire, TopAbs_VERTEX);
  if ( TE.More()) {
    BRepTools_WireExplorer WE;
    for ( WE.Init(mywire); WE.More(); WE.Next()) {
      TopoDS_Edge E = WE.Current();
      if (E.IsNull()) {
	AddWarning(mywire, "an Edge is a null entity");
      }
      else {
	ent = TransferEdge(E, Standard_False);
	if (!ent.IsNull()) Seq->Append(ent);
      }
    }
  }
  else 
    AddWarning(mywire, " no Vertex associated to the Wire");
  

  Standard_Integer nbedges = Seq->Length();
  Handle(IGESData_HArray1OfIGESEntity) Tab;
  if ( nbedges == 1 ) {
    res = ent;
  }
  else if ( nbedges >= 2) {
    Tab =  new IGESData_HArray1OfIGESEntity(1,nbedges);
    for (Standard_Integer itab = 1; itab <= nbedges; itab++) {
      Handle(IGESData_IGESEntity) item = GetCasted(IGESData_IGESEntity, Seq->Value(itab));
      Tab->SetValue(itab,item);
    }
    Handle(IGESGeom_CompositeCurve) Comp = new IGESGeom_CompositeCurve;
    Comp->Init(Tab);
    res = Comp;
  }

  SetShapeResult ( mywire, res );

  return res;
}


//=============================================================================
// TransferWire
//=============================================================================

Handle(IGESData_IGESEntity) BRepToIGES_BRWire ::TransferWire
(const TopoDS_Wire &          mywire,
 const TopoDS_Face &          myface,
 Handle(IGESData_IGESEntity)& mycurve2d,
 const Standard_Real          length)
{
  Handle(IGESData_IGESEntity) res;
  if ( mywire.IsNull()) return res;

  Handle(IGESData_IGESEntity) ent3d ;
  Handle(IGESData_IGESEntity) ent2d ;
  Handle(TColStd_HSequenceOfTransient) Seq3d = new TColStd_HSequenceOfTransient();
  Handle(TColStd_HSequenceOfTransient) Seq2d = new TColStd_HSequenceOfTransient();


  // create a 3d CompositeCurve and a 2d CompositeCurve
  TopExp_Explorer TE(mywire, TopAbs_VERTEX);
  if ( TE.More()) {
    // PTV OCC908 workaround for KAS:dev version
    /*
    BRepTools_WireExplorer WE;
    for ( WE.Init(mywire,myface); WE.More(); WE.Next()) { 
      TopoDS_Edge E = WE.Current();
      if (E.IsNull()) {
	AddWarning(mywire, "an Edge is a null entity");
      }
      else {
	ent3d = TransferEdge(E, Standard_False);
	if (!ent3d.IsNull()) Seq3d->Append(ent3d);
	ent2d = TransferEdge(E, myface, length, Standard_False);
	if (!ent2d.IsNull()) Seq2d->Append(ent2d);
      }
    }
    */
    Handle(ShapeFix_Wire) aSFW = 
      new ShapeFix_Wire( mywire, myface, Precision::Confusion() );
    aSFW->FixReorder();
    Handle(ShapeExtend_WireData) aSEWD = aSFW->WireData();
    Standard_Integer nbE = aSEWD->NbEdges();
    for (Standard_Integer windex = 1; windex <= nbE; windex++) {
      TopoDS_Edge E = aSEWD->Edge( windex );
      if (E.IsNull()) {
	AddWarning(mywire, "an Edge is a null entity");
      }
      else {
        ent3d = TransferEdge(E, Standard_False);
        if (!ent3d.IsNull()) Seq3d->Append(ent3d);
        ent2d = TransferEdge(E, myface, length, Standard_False);
        if (!ent2d.IsNull()) Seq2d->Append(ent2d);
      }
    }
    // OCC908 end of workaround
  }
  else 
    AddWarning(mywire, " no Vertex associated to the Wire");
  
  // Composite Curve 3D
  Standard_Integer nb3d = Seq3d->Length();
  Handle(IGESData_HArray1OfIGESEntity) Tab3d;
  if ( nb3d == 1 ) {
    res = ent3d;
  }
  else if (nb3d >= 2) {
    Tab3d =  new IGESData_HArray1OfIGESEntity(1,nb3d);
    //Standard_Integer tabval = nb3d; //szv#4:S4163:12Mar99 unused
    for (Standard_Integer itab = 1; itab <= nb3d; itab++) {
      Handle(IGESData_IGESEntity) item = 
	GetCasted(IGESData_IGESEntity, Seq3d->Value(itab));
      Tab3d->SetValue(itab,item);
    }
    Handle(IGESGeom_CompositeCurve) Comp = new IGESGeom_CompositeCurve;
    Comp->Init(Tab3d);
    res = Comp;
  }

  // Composite Curve 2D
  Standard_Integer nb2d = Seq2d->Length();
  Handle(IGESData_HArray1OfIGESEntity) Tab2d;
  if ( nb2d == 1 ) {
    mycurve2d = ent2d;
  }
  else if (nb2d >= 2) {
    Tab2d =  new IGESData_HArray1OfIGESEntity(1,nb2d);
    //Standard_Integer tabval = nb2d; //szv#4:S4163:12Mar99 unused
    for ( Standard_Integer itab = 1; itab <= nb2d; itab++) {
      Handle(IGESData_IGESEntity) item = 
	GetCasted(IGESData_IGESEntity, Seq2d->Value(itab));
      Tab2d->SetValue(itab,item);
    }
    Handle(IGESGeom_CompositeCurve) Comp = new IGESGeom_CompositeCurve;
    Comp->Init(Tab2d);
    mycurve2d = Comp;
  }
  
  SetShapeResult ( mywire, res );

  return res;
}
