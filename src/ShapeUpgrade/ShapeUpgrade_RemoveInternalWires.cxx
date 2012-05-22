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

#include <ShapeUpgrade_RemoveInternalWires.ixx>
#include <TopExp_Explorer.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>  
#include <TopoDS_Iterator.hxx>
#include <TopoDS.hxx>
#include <ShapeAnalysis.hxx>
#include <ShapeExtend.hxx>
#include <TopTools_SequenceOfShape.hxx>
#include <ShapeExtend_WireData.hxx>
#include <ShapeBuild_ReShape.hxx>
#include <Precision.hxx>
#include <TopoDS_Edge.hxx>
#include <TopTools_IndexedMapOfShape.hxx>

//=======================================================================
//function : ShapeUpgrade_RemoveInternalWires
//purpose  : 
//=======================================================================

ShapeUpgrade_RemoveInternalWires::ShapeUpgrade_RemoveInternalWires()
{
  myMinArea =0.;
  myRemoveFacesMode = Standard_True;
  myStatus = ShapeExtend::EncodeStatus ( ShapeExtend_OK );
  Handle(ShapeBuild_ReShape) aContext = new ShapeBuild_ReShape;
  SetContext(aContext);
  
}

//=======================================================================
//function : ShapeUpgrade_RemoveInternalWires
//purpose  : 
//=======================================================================

ShapeUpgrade_RemoveInternalWires::ShapeUpgrade_RemoveInternalWires(const TopoDS_Shape& theShape)
{
  Handle(ShapeBuild_ReShape) aContext = new ShapeBuild_ReShape;
  SetContext(aContext);
  Init(theShape);
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

 void ShapeUpgrade_RemoveInternalWires::Init(const TopoDS_Shape& theShape) 
{
  myShape = theShape;
  Context()->Apply(theShape);
  TopExp::MapShapesAndAncestors(myShape,TopAbs_EDGE,TopAbs_FACE,myEdgeFaces);
  myStatus = ShapeExtend::EncodeStatus ( ShapeExtend_OK );
  myMinArea =0.;
  myRemoveFacesMode = Standard_True;
}

//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================

 Standard_Boolean ShapeUpgrade_RemoveInternalWires::Perform() 
{
  Clear();
  if(myShape.IsNull()) {
    myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_FAIL1);
    return Standard_False;
  }
  TopExp_Explorer aExpF(myShape,TopAbs_FACE);
  for( ; aExpF.More(); aExpF.Next()) {
    TopoDS_Face aF = TopoDS::Face(aExpF.Current());
    removeSmallWire(aF,TopoDS_Wire());
  }
  if(myRemoveFacesMode)
    removeSmallFaces();
  
  myResult = Context()->Apply(myShape);
  return Status( ShapeExtend_DONE );
}
 
//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================

 Standard_Boolean ShapeUpgrade_RemoveInternalWires::Perform(const TopTools_SequenceOfShape& theSeqShapes) 
{
  if(myShape.IsNull()) {
    myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_FAIL1);
    return Standard_False;
  }
  Clear();
  TopTools_IndexedDataMapOfShapeListOfShape aWireFaces;
  Standard_Integer i =1, nb = theSeqShapes.Length();
  for( ; i <= nb; i++) {
    TopoDS_Shape aS = theSeqShapes.Value(i);
    if(aS.ShapeType() == TopAbs_FACE)
      removeSmallWire(aS,TopoDS_Wire());
    else if(aS.ShapeType() == TopAbs_WIRE) {
      if(!aWireFaces.Extent())
        TopExp::MapShapesAndAncestors(myShape,TopAbs_WIRE,TopAbs_FACE,aWireFaces);
      if(aWireFaces.Contains(aS)) {
        const TopTools_ListOfShape& alfaces = aWireFaces.FindFromKey(aS);
        TopTools_ListIteratorOfListOfShape liter(alfaces);
        for( ; liter.More(); liter.Next())
          removeSmallWire(liter.Value(),aS);
      }
        
    }
    
  }
  if(myRemoveFacesMode)
      removeSmallFaces();
  myResult = Context()->Apply(myShape);
  return Status( ShapeExtend_DONE );
}

//=======================================================================
//function : removeSmallWire
//purpose  : 
//=======================================================================

void ShapeUpgrade_RemoveInternalWires::removeSmallWire (const TopoDS_Shape& theFace,
                                                        const TopoDS_Shape& theWire) 
{
  TopoDS_Face aF = TopoDS::Face(theFace);
  TopoDS_Wire anOutW = ShapeAnalysis::OuterWire(aF);
  TopoDS_Iterator aIt(aF);
  for( ; aIt.More(); aIt.Next()) {
    if(aIt.Value().ShapeType() != TopAbs_WIRE || aIt.Value().IsSame(anOutW))
      continue;
    //Handle(ShapeExtend_WireData) asewd = new  ShapeExtend_WireData();
    TopoDS_Wire aW = TopoDS::Wire(aIt.Value());
    if(!theWire.IsNull() && !theWire.IsSame(aW))
      continue;
    Standard_Real anArea = ShapeAnalysis::ContourArea(aW);
    if(anArea < myMinArea -Precision::Confusion()) {
      Context()->Remove(aW);
      myRemoveWires.Append(aW);
      myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE1);
      if(!myRemoveFacesMode )
        continue;
      
      TopoDS_Iterator aIte(aW,Standard_False);
      for( ; aIte.More(); aIte.Next()) {
        TopoDS_Shape aE = aIte.Value();
        if(myRemoveEdges.IsBound(aE))
          myRemoveEdges.ChangeFind(aE).Append(aF);
        else {
          TopTools_ListOfShape alfaces;
          alfaces.Append(aF);
          myRemoveEdges.Bind(aE,alfaces);
        }
      }
    }
    
  }
}

//=======================================================================
//function : removeSmallFaces
//purpose  : 
//=======================================================================

void ShapeUpgrade_RemoveInternalWires::removeSmallFaces ()
{
  
  Standard_Integer i =1;
  for( ; i <= myRemoveWires.Length() ; i++) {
    TopoDS_Shape aWire = myRemoveWires.Value(i);
    TopoDS_Iterator aIte(aWire,Standard_False);
    TopTools_IndexedMapOfShape aFaceCandidates;
    //collecting all faces containing edges from removed wire
    for( ; aIte.More(); aIte.Next()) {
      
      TopoDS_Shape aEdge =  aIte.Value();
      if(!myEdgeFaces.Contains(aEdge)) {
        myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_FAIL2);
        continue;
      }
      const TopTools_ListOfShape& aLface1 = myEdgeFaces.FindFromKey(aEdge);
      const TopTools_ListOfShape& aLface2 = myRemoveEdges.Find(aEdge);
      TopTools_ListIteratorOfListOfShape aliter(aLface1);
      TopTools_ListIteratorOfListOfShape aliter2(aLface2);
      for( ; aliter.More(); aliter.Next()) {
        TopoDS_Shape aF = Context()->Apply(aliter.Value());
        if(aF.IsNull())
          continue;
        Standard_Boolean isFind = Standard_False;
        for( ; aliter2.More() && !isFind; aliter2.Next()) {
          TopoDS_Shape aF2 = Context()->Apply(aliter2.Value());
          isFind = aF.IsSame(aF2);
        }
        
        if(!isFind) {
          TopoDS_Wire aWout = ShapeAnalysis::OuterWire(TopoDS::Face(aF));
          Standard_Boolean isOuter = Standard_False;
          TopoDS_Iterator aIter(aWout,Standard_False);
          for( ; aIter.More() && !isOuter; aIter.Next())
            isOuter = aEdge.IsSame(aIter.Value());
          if(isOuter)
            aFaceCandidates.Add(aF);
        }
      }
      
    }
    
    //remove faces which have outer wire consist of only
    //edges from removed wires and
    //seam edges for faces based on conic surface or 
    //in the case of a few faces based on the same conic surface
    //the edges belogining these faces.
    Standard_Integer k =1;
    for( ; k <= aFaceCandidates.Extent(); k++) {
      TopoDS_Shape aF = aFaceCandidates.FindKey(k);
      TopoDS_Wire anOutW = ShapeAnalysis::OuterWire(TopoDS::Face(aF));
      Handle(ShapeExtend_WireData) asewd = new ShapeExtend_WireData(anOutW);
      Standard_Integer n =1, nbE = asewd->NbEdges();
      Standard_Integer nbNotRemoved =0;
      for( ; n <= nbE; n++) {
        if(asewd->IsSeam(n))
          continue;
        TopoDS_Edge aE = asewd->Edge(n);
        if(!myRemoveEdges.IsBound(aE) ) {
          const TopTools_ListOfShape& aLface3 = myEdgeFaces.FindFromKey(aE);
          TopTools_ListIteratorOfListOfShape aliter3(aLface3);
          for( ; aliter3.More();aliter3.Next()) {
            TopoDS_Shape aF2 = Context()->Apply(aliter3.Value());
            if(aF2.IsNull())
              continue;
            if(!aF.IsSame(aF2) && !aFaceCandidates.Contains(aF2))
              nbNotRemoved++;
          }
        }
        
      }
    
      if(!nbNotRemoved) {
        Context()->Remove(aF);
        myRemovedFaces.Append(aF);
      }
    }
  }
  
  if(myRemovedFaces.Length())
    myStatus |= ShapeExtend::EncodeStatus(ShapeExtend_DONE2);
}

//=======================================================================
//function : Clear
//purpose  : 
//=======================================================================

void ShapeUpgrade_RemoveInternalWires::Clear()
{
  myRemoveEdges.Clear();
  myRemovedFaces.Clear();
  myRemoveWires.Clear();
  myStatus = ShapeExtend::EncodeStatus (ShapeExtend_OK);
}

