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

//    abv 28.04.99 S4137: ading method Apply for work on all types of shapes
//    sln 29.11.01 Bug24: correction iteration through map in method 'Status'
//    sln 29.11.01 Bug22: correction of methods Replace and Value for case when mode myConsiderLocation is on

#include <BRepTools_ReShape.ixx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopExp_Explorer.hxx>
#include <BRep_Builder.hxx>
//include <ShapeExtend.hxx>
//#include <BRepTools_Edge.hxx>
#include <TopoDS.hxx>
#include <BRep_ListIteratorOfListOfCurveRepresentation.hxx>
#include <BRep_TEdge.hxx>
#include <BRep_GCurve.hxx>
#include <Geom_Surface.hxx>
#include <TopLoc_Location.hxx>
#include <BRep_ListOfCurveRepresentation.hxx>
#include <BRep_GCurve.hxx>
#include <BRep_Tool.hxx>
#include <BRep_ListIteratorOfListOfCurveRepresentation.hxx>
#include <TopoDS_Edge.hxx>


static void CopyRanges (const TopoDS_Edge& toedge, 
				  const TopoDS_Edge& fromedge,
				  const Standard_Real alpha,
				  const Standard_Real beta) 
{
/*  BRep_Builder B;
    for (BRep_ListIteratorOfListOfCurveRepresentation itcr
    ((*((Handle(BRep_TEdge)*)&fromedge.TShape()))->ChangeCurves()); itcr.More(); itcr.Next()) {
    Handle(BRep_GCurve) GC = Handle(BRep_GCurve)::DownCast(itcr.Value());
    if ( GC.IsNull() ) continue;
    Standard_Real first, last;
    GC->Range ( first, last );
    if ( GC->IsCurve3D() ) 
      B.Range ( toedge, first, last );
    else if ( GC->IsCurveOnSurface() )
      B.Range ( toedge, GC->Surface(), fromedge.Location().Multiplied (GC->Location()), first, last);
  }
*/
  for (BRep_ListIteratorOfListOfCurveRepresentation fromitcr
       ((*((Handle(BRep_TEdge)*)&fromedge.TShape()))->ChangeCurves()); fromitcr.More(); fromitcr.Next()) {
    Handle(BRep_GCurve) fromGC = Handle(BRep_GCurve)::DownCast(fromitcr.Value());
    if ( fromGC.IsNull() ) continue;
    Standard_Boolean isC3d = fromGC->IsCurve3D();
    if(isC3d) {
      if(fromGC->Curve3D().IsNull()) continue; }
    else {
       if(fromGC->PCurve().IsNull()) continue; }
      
    if ( ! isC3d && ! fromGC->IsCurveOnSurface()) continue; // only 3d curves and pcurves are treated

    Handle(Geom_Surface) surface;
    TopLoc_Location L;
    if ( ! isC3d ) {
      surface = fromGC->Surface();
      L = fromGC->Location();
    } 

    BRep_ListOfCurveRepresentation& tolist = (*((Handle(BRep_TEdge)*)&toedge.TShape()))->ChangeCurves();
    Handle(BRep_GCurve) toGC;
    for (BRep_ListIteratorOfListOfCurveRepresentation toitcr (tolist); toitcr.More(); toitcr.Next()) {
      toGC = Handle(BRep_GCurve)::DownCast(toitcr.Value());
      if ( toGC.IsNull() ) continue;
      if ( isC3d ) {
	if ( ! toGC->IsCurve3D() ) continue;
      }
      else if ( ! toGC->IsCurveOnSurface() || 
	       surface != toGC->Surface() || L != toGC->Location() ) continue;
      Standard_Real first = fromGC->First();
      Standard_Real last = fromGC->Last();
      Standard_Real len = last - first;
      toGC->SetRange ( first+alpha*len, first+beta*len );
      break;
    }
  }
}


//=======================================================================
//function : BRepTools_ReShape
//purpose  : 
//=======================================================================

BRepTools_ReShape::BRepTools_ReShape()
{
  myConsiderLocation = Standard_False;
  myConsiderOrientation = Standard_False;
}


//=======================================================================
//function : Clear
//purpose  : 
//=======================================================================

void BRepTools_ReShape::Clear() 
{
  myNMap.Clear();
  myRMap.Clear();
}


//=======================================================================
//function : Remove
//purpose  : 
//=======================================================================

void BRepTools_ReShape::Remove (const TopoDS_Shape& shape,
                                const Standard_Boolean oriented) 
{
  TopoDS_Shape nulshape;
  Replace (shape,nulshape,oriented);
}

//=======================================================================
//function : Replace
//purpose  : 
//=======================================================================

void BRepTools_ReShape::Replace (const TopoDS_Shape& ashape,
                                 const TopoDS_Shape& anewshape,
                                 const Standard_Boolean oriented) 
{
  TopoDS_Shape shape = ashape;
  TopoDS_Shape newshape = anewshape;
  if ( shape.IsNull() || shape == newshape ) return;
  if (myConsiderLocation) {
    //sln 29.11.01 Bug22: Change location of 'newshape' in accordance with location of 'shape'
    newshape.Location(newshape.Location().Multiplied(shape.Location().Inverted()));
    TopLoc_Location nullLoc; 
    shape.Location ( nullLoc );
  }

#ifdef DEB
  if ( IsRecorded ( shape ) && ((myConsiderLocation && ! Value ( shape ).IsPartner ( newshape )) ||
                                 (!myConsiderLocation && ! Value ( shape ).IsSame ( newshape )))) 
    cout << "Warning: BRepTools_ReShape::Replace: shape already recorded" << endl;
#endif
  
  if (oriented) {
    if( shape.Orientation()==TopAbs_REVERSED ) {
      if( myConsiderOrientation )
        myRMap.Bind (shape,newshape);
      else {
        myNMap.Bind (shape.Reversed(),newshape.Reversed());
      }
    }
    else
      myNMap.Bind (shape,newshape);
  } 
  else {
    // protect against INTERNAL or EXTERNAL shape
    if ( shape.Orientation() == TopAbs_INTERNAL ||
	 shape.Orientation() == TopAbs_EXTERNAL ) {
      Replace ( shape.Oriented ( TopAbs_FORWARD ), 
	        newshape.Oriented ( newshape.Orientation() == shape.Orientation() ?
				    TopAbs_FORWARD : TopAbs_REVERSED ), oriented );
      return;
    }
  
    Replace (shape,newshape,Standard_True);
    if(myConsiderOrientation)
      Replace (shape.Reversed(),newshape.Reversed(),Standard_True);
  }
}


//=======================================================================
//function : IsRecorded
//purpose  : 
//=======================================================================

Standard_Boolean BRepTools_ReShape::IsRecorded (const TopoDS_Shape& ashape) const
{
  TopoDS_Shape shape = ashape;
  if (myConsiderLocation) {
    TopLoc_Location nullLoc;
    shape.Location ( nullLoc );
  }
  if (shape.IsNull()) return Standard_False;
  if ( myConsiderOrientation && shape.Orientation()==TopAbs_REVERSED )
    return myRMap.IsBound (shape);
  else
    return myNMap.IsBound (shape);
}


//=======================================================================
//function : Value
//purpose  : 
//=======================================================================

TopoDS_Shape BRepTools_ReShape::Value (const TopoDS_Shape& ashape) const
{
  TopoDS_Shape res;
  if (ashape.IsNull()) return res;
  TopoDS_Shape shape = ashape;
  if (myConsiderLocation) {
    TopLoc_Location nullLoc;
    shape.Location ( nullLoc );
  }
  
  Standard_Boolean fromMap = Standard_False;
  if ( shape.Orientation()==TopAbs_REVERSED ) {
    if( myConsiderOrientation ) {
      if (!myRMap.IsBound (shape)) res = shape;
      else { 
        res = myRMap.Find (shape);
        fromMap = Standard_True;
      }
    }
    else {
      if (!myNMap.IsBound (shape)) res = shape;
      else { 
        res = myNMap.Find (shape).Reversed();
        fromMap = Standard_True;
      }
    }
  }
  else {
    if (!myNMap.IsBound (shape)) res = shape;
    else {
      res = myNMap.Find (shape);
      fromMap = Standard_True;
    }
  }
  // for INTERNAL/EXTERNAL, since they are not fully supported, keep orientation
  if ( shape.Orientation() == TopAbs_INTERNAL ||
       shape.Orientation() == TopAbs_EXTERNAL ) 
    res.Orientation ( shape.Orientation() );

  if (myConsiderLocation) {
    //sln 29.11.01 Bug22: Recalculate location of resulting shape in accordance with
    //whether result is from map or not
    if(fromMap) res.Location(ashape.Location()*res.Location());
    else res.Location(ashape.Location());
  }

  return res;
}


//=======================================================================
//function : Status
//purpose  : 
//=======================================================================

Standard_Integer BRepTools_ReShape::Status(const TopoDS_Shape& ashape,
					    TopoDS_Shape& newsh,
					    const Standard_Boolean last) 
{
  Standard_Integer res = 0;
  if (ashape.IsNull())  {  newsh.Nullify();  return res;  }

  TopoDS_Shape shape = ashape;
  TopLoc_Location aLocSh = shape.Location();
  if (myConsiderLocation) {
    TopLoc_Location nullLoc;
    shape.Location ( nullLoc );
  }

  if ( myConsiderOrientation && shape.Orientation()==TopAbs_REVERSED ) {
    if (!myRMap.IsBound (shape))  {  newsh = shape;  res = 0; }
    else {  newsh = myRMap.Find (shape);  res = 1;  }
  } 
  else {
    if (!myNMap.IsBound (shape))  {  newsh = shape;  res = 0; }
    else {  newsh = myNMap.Find (shape);  res = 1;  }
  }
  if (res > 0) {
    if (newsh.IsNull()) res = -1;
    else if (newsh.IsEqual (shape)) res = 0;
    else if ( last && ((myConsiderLocation && ! newsh.IsPartner (shape)) ||
                       (!myConsiderLocation && ! newsh.IsSame (shape)))) {
      //TopoDS_Shape newnewsh;
      //Standard_Integer newres = Status (newsh, newnewsh, last);
      //newsh = newnewsh;
      //if (newres) res = newres;
      // sln 29.11.01 Bug24: Correction iteration through maps. Way of iteration used early does not
      // correspond to way of storing information in the maps.
      newsh = Apply(shape, TopAbs_SHAPE);
      if (newsh.IsNull()) res = -1; 
      if (newsh.IsEqual (shape)) res = 0;
    }
  }
  if(myConsiderLocation && !newsh.IsNull()) 
  {
    TopLoc_Location aResLoc = (res >0 && !newsh.Location().IsIdentity() ? 
      aLocSh * newsh.Location() : aLocSh);
    newsh.Location(aResLoc);
  }
  return res;
}


//=======================================================================
//function : Apply
//purpose  : 
//=======================================================================

TopoDS_Shape BRepTools_ReShape::Apply (const TopoDS_Shape& shape,
                                       const TopAbs_ShapeEnum until,
                                       const Standard_Integer buildmode) 
{
  if (shape.IsNull()) return shape;
  TopoDS_Shape newsh;
  if (Status (shape,newsh,Standard_False) != 0) return newsh;

  TopAbs_ShapeEnum st = shape.ShapeType();
  if (st == until) return newsh;    // critere d arret

  Standard_Integer modif = 0;
  if (st == TopAbs_COMPOUND || st == TopAbs_COMPSOLID) {
    BRep_Builder B;
    TopoDS_Compound C;
    B.MakeCompound (C);
    for (TopoDS_Iterator it (shape); it.More(); it.Next()) {
      TopoDS_Shape sh = it.Value();
      Standard_Integer stat = Status (sh,newsh,Standard_False);
      if (stat != 0) modif = 1;
      if (stat >= 0) B.Add (C,newsh);
    }
    if (modif == 0) return shape;
    return C;
  }

  if (st == TopAbs_SOLID) {
    BRep_Builder B;
    TopoDS_Compound C;
    B.MakeCompound (C);
    TopoDS_Solid S;
    B.MakeSolid (S);
    for (TopoDS_Iterator it (shape); it.More(); it.Next()) {
      TopoDS_Shape sh = it.Value();
      newsh = Apply (sh,until,buildmode);
      if (newsh.IsNull()) {
	modif = -1;
      } 
      else if (newsh.ShapeType() != TopAbs_SHELL) {
	Standard_Integer nbsub = 0;
	for (TopExp_Explorer exh(newsh,TopAbs_SHELL); exh.More(); exh.Next()) {
	  TopoDS_Shape onesh = exh.Current ();
	  B.Add (S,onesh);
	  nbsub ++;
	}
	if (nbsub == 0) modif = -1;
	B.Add (C,newsh);  // c est tout
      } 
      else {
	if (modif == 0 && !sh.IsEqual(newsh)) modif = 1;
	B.Add (C,newsh);
	B.Add (S,newsh);
      }
    }
    if ( (modif < 0 && buildmode < 2) || (modif == 0 && buildmode < 1) )
      return C;
    else return S;
  }

  if (st == TopAbs_SHELL) {
    BRep_Builder B;
    TopoDS_Compound C;
    B.MakeCompound (C);
    TopoDS_Shell S;
    B.MakeShell (S);
    for (TopoDS_Iterator it (shape); it.More(); it.Next()) {
      TopoDS_Shape sh = it.Value();
      newsh = Apply (sh,until,buildmode);
      if (newsh.IsNull()) {
	modif = -1;
      } 
      else if (newsh.ShapeType() != TopAbs_FACE) {
	Standard_Integer nbsub = 0;
	for (TopExp_Explorer exf(newsh,TopAbs_FACE); exf.More(); exf.Next()) {
	  TopoDS_Shape onesh = exf.Current ();
	  B.Add (S,onesh);
	  nbsub ++;
	}
	if (nbsub == 0) modif = -1;
	B.Add (C,newsh);  // c est tout
      } 
      else {
	if (modif == 0 && !sh.IsEqual(newsh)) modif = 1;
	B.Add (C,newsh);
	B.Add (S,newsh);
      }
    }
    if ( (modif < 0 && buildmode < 2) || (modif == 0 && buildmode < 1) )
      return C;
    else return S;
  }
  cout<<"BRepTools_ReShape::Apply NOT YET IMPLEMENTED"<<endl;
  return shape;
}


//=======================================================================
//function : EncodeStatus
//purpose  : static
//=======================================================================
static Standard_Integer EncodeStatus (const Standard_Integer status)
{
  switch ( status ) {
  case 0   : return 0x0000; //ShapeExtend_OK
  case 1: return 0x0001;    //ShapeExtend_DONE1
  case 2: return 0x0002;    //....
  case 3: return 0x0004;
  case 4: return 0x0008;
  case 5: return 0x0010;
  case 6: return 0x0020;
  case 7: return 0x0040;
  case 8: return 0x0080;    //....
  case 9 : return 0x00ff;   //ShapeExtend_DONE
  case 10: return 0x0100;   //ShapeExtend_FAIL1
  case 11: return 0x0200;   //...
  case 12: return 0x0400;
  case 13: return 0x0800;
  case 14: return 0x1000;
  case 15: return 0x2000;
  case 16: return 0x4000;
  case 17: return 0x8000;   //....
  case 18 : return 0xff00;  //ShapeExtend_FAIL
  }
  return 0;
}


//=======================================================================
//function : Apply
//purpose  : 
//=======================================================================

TopoDS_Shape BRepTools_ReShape::Apply (const TopoDS_Shape& shape,
                                       const TopAbs_ShapeEnum until) 
{
  myStatus = EncodeStatus(0); //ShapeExtend::EncodeStatus ( ShapeExtend_OK );
  if ( shape.IsNull() ) return shape;

  // apply direct replacement
  TopoDS_Shape newsh = Value ( shape );
  
  // if shape removed, return NULL
  if ( newsh.IsNull() ) {
    myStatus = EncodeStatus (2); //ShapeExtend_DONE2
    return newsh;
  }
  
  // if shape replaced, apply modifications to the result recursively 
  if ( (myConsiderLocation && ! newsh.IsPartner (shape)) || 
      (!myConsiderLocation &&! newsh.IsSame ( shape )) ) {
    TopoDS_Shape res = Apply ( newsh, until );
    myStatus |= EncodeStatus(1); //ShapeExtend::EncodeStatus ( ShapeExtend_DONE1 );
    return res;
  }

  TopAbs_ShapeEnum st = shape.ShapeType(); //, subt;
  if ( st >= until ) return newsh;    // critere d arret
  if(st == TopAbs_VERTEX || st == TopAbs_SHAPE)
    return shape;
  // define allowed types of components
  //fix for SAMTECH bug OCC322 about abcense internal vertices after sewing. 
  /*
  switch ( st ) {
  case TopAbs_COMPOUND:  subt = TopAbs_SHAPE;  break;
  case TopAbs_COMPSOLID: subt = TopAbs_SOLID;  break;
  case TopAbs_SOLID:     subt = TopAbs_SHELL;  break;
  case TopAbs_SHELL:     subt = TopAbs_FACE;   break;
  case TopAbs_FACE:      subt = TopAbs_WIRE;   break;
  case TopAbs_WIRE:      subt = TopAbs_EDGE;   break;
  case TopAbs_EDGE:      subt = TopAbs_VERTEX; break;
  case TopAbs_VERTEX:
  case TopAbs_SHAPE:
  default:               return shape;
  }
  */
  BRep_Builder B;
  
  TopoDS_Shape result = shape.EmptyCopied();
  TopAbs_Orientation orien = shape.Orientation();
  result.Orientation(TopAbs_FORWARD); // protect against INTERNAL or EXTERNAL shapes
  Standard_Boolean modif = Standard_False;
  Standard_Integer locStatus = myStatus;
  
  // apply recorded modifications to subshapes
  for ( TopoDS_Iterator it(shape,Standard_False); it.More(); it.Next() ) {
    TopoDS_Shape sh = it.Value();
    newsh = Apply ( sh, until );
    if ( newsh != sh ) {
      if ( myStatus & EncodeStatus(4)) //ShapeExtend::DecodeStatus ( myStatus, ShapeExtend_DONE4 ) )
	locStatus |= EncodeStatus(4); //|= ShapeExtend::EncodeStatus ( ShapeExtend_DONE4 );
      modif = 1;
    }
    if ( newsh.IsNull() ) {
      locStatus |= EncodeStatus(4); //ShapeExtend::EncodeStatus ( ShapeExtend_DONE4 );
      continue;
    }
    locStatus |= EncodeStatus(3);//ShapeExtend::EncodeStatus ( ShapeExtend_DONE3 );
    if ( st == TopAbs_COMPOUND || newsh.ShapeType() == sh.ShapeType()) { //fix for SAMTECH bug OCC322 about abcense internal vertices after sewing.
      B.Add ( result, newsh );
      continue;
    }
    Standard_Integer nitems = 0;
    for ( TopoDS_Iterator subit(newsh); subit.More(); subit.Next(), nitems++ ) {
      TopoDS_Shape subsh = subit.Value();
      if ( subsh.ShapeType() == sh.ShapeType() ) B.Add ( result, subsh );//fix for SAMTECH bug OCC322 about abcense internal vertices after sewing.
      else locStatus |= EncodeStatus(10);//ShapeExtend::EncodeStatus ( ShapeExtend_FAIL1 );
    }
    if ( ! nitems ) locStatus |= EncodeStatus(10);//ShapeExtend::EncodeStatus ( ShapeExtend_FAIL1 );
  }
  if ( ! modif ) return shape;

  // restore Range on edge broken by EmptyCopied()
  if ( st == TopAbs_EDGE ) {
    //BRepTools_Edge sbe;
    CopyRanges ( TopoDS::Edge ( result ), TopoDS::Edge ( shape ),0,1 );
  }

  if (st == TopAbs_FACE)  {
    TopoDS_Face face = TopoDS::Face ( shape );
    if( BRep_Tool::NaturalRestriction( face ) ) {
      BRep_Builder aB;
      aB.NaturalRestriction( TopoDS::Face (  result ), Standard_True );
    }
  }

  result.Orientation(orien);
  myStatus = locStatus;
  Replace ( shape, result );
  return result;
}


//=======================================================================
//function : Status
//purpose  : 
//=======================================================================

/*Standard_Boolean BRepTools_ReShape::Status (const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus ( myStatus, status );
}*/


//=======================================================================
//function : ModeConsiderLocation
//purpose  : 
//=======================================================================

Standard_Boolean& BRepTools_ReShape::ModeConsiderLocation() 
{
  return myConsiderLocation;
}


//=======================================================================
//function : ModeConsiderOrientation
//purpose  : 
//=======================================================================

Standard_Boolean& BRepTools_ReShape::ModeConsiderOrientation() 
{
  return myConsiderOrientation;
}
