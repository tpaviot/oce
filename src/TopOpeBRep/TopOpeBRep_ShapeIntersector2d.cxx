// Created on: 1993-05-07
// Created by: Jean Yves LEBEY
// Copyright (c) 1993-1999 Matra Datavision
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


#include <TopOpeBRep_ShapeIntersector2d.ixx>

#include <Standard_ProgramError.hxx>
#include <Standard_NotImplemented.hxx>
#include <TopAbs.hxx>
#include <Bnd_Box.hxx>
#include <TopOpeBRepTool_box.hxx>

#ifdef DEB
extern Standard_Boolean TopOpeBRep_GettraceSI(); 
extern Standard_Boolean TopOpeBRep_GetcontextFFOR();
#endif

//=======================================================================
//function : TopOpeBRep_ShapeIntersector2d
//purpose  : 
//=======================================================================

TopOpeBRep_ShapeIntersector2d::TopOpeBRep_ShapeIntersector2d()
{
  Reset();
  myHBoxTool = FBOX_GetHBoxTool();
  myFaceScanner.ChangeBoxSort().SetHBoxTool(myHBoxTool);
  myEdgeScanner.ChangeBoxSort().SetHBoxTool(myHBoxTool);
}

//=======================================================================
//function : Reset
//purpose  : 
//=======================================================================

void TopOpeBRep_ShapeIntersector2d::Reset()
{
  myIntersectionDone = Standard_False;
  
  myFFDone = Standard_False;
  myEEFFDone = Standard_False;
  
  myFFInit = Standard_False;
  myEEFFInit = Standard_False;
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void TopOpeBRep_ShapeIntersector2d::Init
(const TopoDS_Shape& S1, const TopoDS_Shape& S2)
{
  Reset();
  myShape1 = S1;
  myShape2 = S2;
  myHBoxTool->Clear();
}

//=======================================================================
//function : SetIntersectionDone
//purpose  : 
//=======================================================================

void TopOpeBRep_ShapeIntersector2d::SetIntersectionDone()
{
  myIntersectionDone = (myFFDone || 
			myEEFFDone);
}


//=======================================================================
//function : CurrentGeomShape
//purpose  : 
//=======================================================================

const TopoDS_Shape& TopOpeBRep_ShapeIntersector2d::CurrentGeomShape
(const Standard_Integer Index) const
{
  if ( myIntersectionDone ) {
    if      (myFFDone) {
      if      ( Index == 1 ) return myFaceScanner.Current();
      else if ( Index == 2 ) return myFaceExplorer.Current();
    }
    else if (myEEFFDone) {
      if      ( Index == 1 ) return myEdgeScanner.Current();
      else if ( Index == 2 ) return myEdgeExplorer.Current();
    }
  }
  
  Standard_ProgramError::Raise("CurrentGeomShape : no intersection 2d");
  TopoDS_Shape* bid = new TopoDS_Shape();
  return *bid;
}


//=======================================================================
//function : InitIntersection
//purpose  : 
//=======================================================================

void TopOpeBRep_ShapeIntersector2d::InitIntersection
(const TopoDS_Shape& S1, const TopoDS_Shape& S2)
{
  Init(S1,S2);
  InitFFIntersection();
}


//=======================================================================
//function : MoreIntersection
//purpose  : 
//=======================================================================

Standard_Boolean TopOpeBRep_ShapeIntersector2d::MoreIntersection() const
{
  Standard_Boolean res = myIntersectionDone;
  
#ifdef DEB
  if (TopOpeBRep_GettraceSI() && res) {
    if      ( myFFDone )   cout<<"FF : ";
    else if ( myEEFFDone ) cout<<"    EE : ";
    DumpCurrent(1);
    DumpCurrent(2);
  }    
#endif
  
  return res;
}


//=======================================================================
//function : DumpCurrent
//purpose  : 
//=======================================================================

void TopOpeBRep_ShapeIntersector2d::DumpCurrent(const Standard_Integer K) const
{
#ifdef DEB
  if      ( myFFDone ) {
    if      ( K == 1 ) myFaceScanner.DumpCurrent(cout);
    else if ( K == 2 ) myFaceExplorer.DumpCurrent(cout);
  }
  else if ( myEEFFDone ) {
    if      ( K == 1 ) myEdgeScanner.DumpCurrent(cout);
    else if ( K == 2 ) myEdgeExplorer.DumpCurrent(cout);
  }
#endif
}

//=======================================================================
//function : Index
//purpose  : 
//=======================================================================

Standard_Integer TopOpeBRep_ShapeIntersector2d::Index
(const Standard_Integer K)const
{
  Standard_Integer i = 0;
#ifdef DEB
  if      ( myFFDone ) {
    if      ( K == 1 ) i = myFaceScanner.Index();
    else if ( K == 2 ) i = myFaceExplorer.Index();
  }
  else if ( myEEFFDone ) {
    if      ( K == 1 ) i = myEdgeScanner.Index();
    else if ( K == 2 ) i = myEdgeExplorer.Index();
  }
#endif
  return i;
}


//=======================================================================
//function : NextIntersection
//purpose  : 
//=======================================================================

void TopOpeBRep_ShapeIntersector2d::NextIntersection()
{
  myIntersectionDone = Standard_False;
  
  if (myFFDone) {
    // precedant etat du More() : 2 faces
    myFFDone = Standard_False;
    InitEEFFIntersection();
    FindEEFFIntersection();
    if ( !myIntersectionDone ) {
      NextFFCouple();
      FindFFIntersection();
    }
  }
  else if ( myEEFFDone ) {
    NextEEFFCouple();
    FindEEFFIntersection();
    if ( !myIntersectionDone ) {
      NextFFCouple();
      FindFFIntersection();
    }
  }
  
  if ( !myIntersectionDone ) {
    InitFFIntersection();
  }
}


// ========
// FFFFFFFF
// ========


//=======================================================================
//function : InitFFIntersection
//purpose  : 
//=======================================================================

void TopOpeBRep_ShapeIntersector2d::InitFFIntersection()
{
  if ( !myFFInit) { 
    TopAbs_ShapeEnum tscann = TopAbs_FACE;
    TopAbs_ShapeEnum texplo = TopAbs_FACE;
    myFaceScanner.Clear();
    myFaceScanner.AddBoxesMakeCOB(myShape1,tscann);
    myFaceExplorer.Init(myShape2,texplo);
    myFaceScanner.Init(myFaceExplorer);
    FindFFIntersection();
  }
  myFFInit = Standard_True;
}


//=======================================================================
//function : FindFFIntersection
//purpose  : 
//=======================================================================

void TopOpeBRep_ShapeIntersector2d::FindFFIntersection()
{
  myFFDone = Standard_False;
//  myFFSameDomain = Standard_False;
  
  if ( MoreFFCouple() ) {
    
    // The two candidate intersecting GeomShapes GS1,GS2 and their types t1,t2
    const TopoDS_Shape& GS1 = myFaceScanner.Current();
    const TopoDS_Shape& GS2 = myFaceExplorer.Current();
    
#ifdef DEB
    if (TopOpeBRep_GettraceSI()) {
      cout<<"?? FF : ";
      myFaceScanner.DumpCurrent(cout); 
      myFaceExplorer.DumpCurrent(cout);
      cout<<endl;
    }    
#endif

    const TopOpeBRepTool_BoxSort& BS = myFaceScanner.BoxSort();
    BS.Box(GS1);
    BS.Box(GS2);
    myFFDone = Standard_True;
  }
  
  SetIntersectionDone();
}


//=======================================================================
//function : MoreFFCouple
//purpose  : 
//=======================================================================

Standard_Boolean TopOpeBRep_ShapeIntersector2d::MoreFFCouple() const
{
  Standard_Boolean more1 = myFaceScanner.More();
  Standard_Boolean more2 = myFaceExplorer.More();
  return (more1 && more2);
}


//=======================================================================
//function : NextFFCouple
//purpose  : 
//=======================================================================

void TopOpeBRep_ShapeIntersector2d::NextFFCouple()
{
  myFaceScanner.Next();
  Standard_Boolean b1,b2;
  
  b1 = (!myFaceScanner.More());
  b2 = (myFaceExplorer.More());
  while ( b1 && b2 ) {
    myFaceExplorer.Next();
    myFaceScanner.Init(myFaceExplorer);
    b1 = (!myFaceScanner.More());
    b2 = (myFaceExplorer.More());
  }

}


// ========
// EEFFEEFF
// ========


//=======================================================================
//function : InitEEFFIntersection
//purpose  : 
//=======================================================================

void TopOpeBRep_ShapeIntersector2d::InitEEFFIntersection()
{
  // prepare exploration of the edges of the two current SameDomain faces 
  TopoDS_Shape face1 = myFaceScanner.Current(); // -26-08-96
  TopoDS_Shape face2 = myFaceExplorer.Current(); // -26-08-96
  
#ifdef DEB
  if (TopOpeBRep_GetcontextFFOR()) {
    face1.Orientation(TopAbs_FORWARD); //-05/07
    face2.Orientation(TopAbs_FORWARD); //-05/07
    cout<<"ctx : InitEEFFIntersection : faces FORWARD"<<endl;
  }
#endif
  
  myEEIntersector.SetFaces(face1,face2);
  
  TopAbs_ShapeEnum tscann = TopAbs_EDGE;
  TopAbs_ShapeEnum texplo = TopAbs_EDGE;
  myEdgeScanner.Clear();
  myEdgeScanner.AddBoxesMakeCOB(face1,tscann);
  myEdgeExplorer.Init(face2,texplo);
  myEdgeScanner.Init(myEdgeExplorer);
  
  myEEFFInit = Standard_True;
}


//=======================================================================
//function : FindEEFFIntersection
//purpose  : 
//=======================================================================

void TopOpeBRep_ShapeIntersector2d::FindEEFFIntersection()
{
  myEEFFDone = Standard_False;
  while ( MoreEEFFCouple() ) {
    const TopoDS_Shape& GS1 = myEdgeScanner.Current();
    const TopoDS_Shape& GS2 = myEdgeExplorer.Current();
    myEEIntersector.Perform(GS1,GS2);
    
#ifdef DEB
    if (TopOpeBRep_GettraceSI() && myEEIntersector.IsEmpty()) {
      cout<<"    EE : ";
      myEdgeScanner.DumpCurrent(cout);
      myEdgeExplorer.DumpCurrent(cout);
      cout<<"(EE of FF SameDomain)";
      cout<<" : EMPTY INTERSECTION";
      cout<<endl;
    }    
#endif
    
    myEEFFDone = ! (myEEIntersector.IsEmpty());
    if (myEEFFDone) break;
    else NextEEFFCouple();
  }
  SetIntersectionDone();
}


//=======================================================================
//function : MoreEEFFCouple
//purpose  : 
//=======================================================================

Standard_Boolean TopOpeBRep_ShapeIntersector2d::MoreEEFFCouple() const
{
  Standard_Boolean more1 = myEdgeScanner.More();
  Standard_Boolean more2 = myEdgeExplorer.More();
  return (more1 && more2);
}


//=======================================================================
//function : NextEEFFCouple
//purpose  : 
//=======================================================================

void TopOpeBRep_ShapeIntersector2d::NextEEFFCouple()
{
  myEdgeScanner.Next();
  while ( ! myEdgeScanner.More() && myEdgeExplorer.More() ) {
    myEdgeExplorer.Next();
    myEdgeScanner.Init(myEdgeExplorer);
  }
}


//=======================================================================
//function : Shape
//purpose  : 
//=======================================================================

const TopoDS_Shape& TopOpeBRep_ShapeIntersector2d::Shape
( const Standard_Integer Index )const
{
  if      ( Index == 1 ) return myShape1;
  else if ( Index == 2 ) return myShape2;
  
  Standard_ProgramError::Raise("ShapeIntersector : no shape");
  TopoDS_Shape* bid = new TopoDS_Shape();
  return *bid;
}

//=======================================================================
//function : ChangeEdgesIntersector
//purpose  : 
//=======================================================================

TopOpeBRep_EdgesIntersector& 
TopOpeBRep_ShapeIntersector2d::ChangeEdgesIntersector()
{ return myEEIntersector; }

