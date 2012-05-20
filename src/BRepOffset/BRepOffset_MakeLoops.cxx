// Created on: 1996-09-05
// Created by: Yves FRICAUD
// Copyright (c) 1996-1999 Matra Datavision
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


#include <stdio.h>

#include <BRepOffset_MakeLoops.ixx>
#include <BRepAlgo_Loop.hxx>


#include <BRep_Builder.hxx>
#include <BRep_Tool.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopTools_MapOfShape.hxx>
#include <TopoDS_Iterator.hxx>
#include <BRep_TVertex.hxx>

#ifdef DRAW
#include <DBRep.hxx>
#endif
#ifdef DRAW
Standard_Integer NbF = 1;
static Standard_Boolean Affich = Standard_False;
//POP pour NT
//char name[100];
#endif


BRepOffset_MakeLoops::BRepOffset_MakeLoops()
{
}

//=======================================================================
//function : Build
//purpose  : 
//=======================================================================

void BRepOffset_MakeLoops::Build(const TopTools_ListOfShape&   LF, 
				 const Handle(BRepAlgo_AsDes)& AsDes, 
				 BRepAlgo_Image&               Image)
{
  TopTools_ListIteratorOfListOfShape    it(LF);
  TopTools_ListIteratorOfListOfShape    itl,itLCE;
  BRepAlgo_Loop                       Loops;
  Loops.VerticesForSubstitute( myVerVerMap );

  for (; it.More(); it.Next()) {
    const TopoDS_Face& F = TopoDS::Face(it.Value());
    //---------------------------
    // Initialization of Loops.
    //---------------------------
    Loops.Init(F);
    //-----------------------------
    // return edges of F.
    //-----------------------------
    const TopTools_ListOfShape& LE = AsDes->Descendant(F);
    TopTools_ListOfShape        AddedEdges;

    for (itl.Initialize(LE); itl.More(); itl.Next()) {
      TopoDS_Edge E = TopoDS::Edge(itl.Value());
      if (Image.HasImage(E)) {
	//-------------------------------------------
	// E was already cut in another face.
	// Return the cut edges reorientate them as E.
	// See pb for the edges that have disappeared?
	//-------------------------------------------
	const TopTools_ListOfShape& LCE = Image.Image(E);
	for (itLCE.Initialize(LCE); itLCE.More(); itLCE.Next()) {
	  TopoDS_Shape CE = itLCE.Value().Oriented(E.Orientation()); 
	  Loops.AddConstEdge(TopoDS::Edge(CE));
	}
      }
      else {
	Loops     .AddEdge(E, AsDes->Descendant(E));
	AddedEdges.Append (E);
      }
    }
    //------------------------
    // Unwind.
    //------------------------
    Loops.Perform();
    Loops.WiresToFaces();      
    //------------------------
    // MAJ SD.
    //------------------------
    const TopTools_ListOfShape&  NF = Loops.NewFaces();
    //-----------------------
    // F => New faces;
    //-----------------------
    Image.Bind(F,NF);

    TopTools_ListIteratorOfListOfShape itAdded;
    for (itAdded.Initialize(AddedEdges); itAdded.More(); itAdded.Next()) {
      const TopoDS_Edge& E = TopoDS::Edge(itAdded.Value());
      //-----------------------
      //  E => New edges;
      //-----------------------
      const TopTools_ListOfShape& LoopNE = Loops.NewEdges(E);
      if (Image.HasImage(E)) {
	Image.Add(E,LoopNE);
      }
      else {
	Image.Bind(E,LoopNE);
      }
    }
  }
  Loops.GetVerticesForSubstitute( myVerVerMap );
  if (myVerVerMap.IsEmpty())
    return;
  BRep_Builder BB;
  for (it.Initialize( LF ); it.More(); it.Next())
    {
      TopoDS_Shape F = it.Value();
      TopTools_ListOfShape LIF;
      Image.LastImage( F, LIF );
      for (itl.Initialize(LIF); itl.More(); itl.Next())
	{
	  const TopoDS_Shape& IF = itl.Value();
	  TopExp_Explorer EdExp( IF, TopAbs_EDGE );
	  for (; EdExp.More(); EdExp.Next())
	    {
	      TopoDS_Shape E = EdExp.Current();
	      TopTools_ListOfShape VList;
	      TopoDS_Iterator VerExp( E );
	      for (; VerExp.More(); VerExp.Next())
		VList.Append( VerExp.Value() );
	      TopTools_ListIteratorOfListOfShape itlv( VList );
	      for (; itlv.More(); itlv.Next())
		{
		  const TopoDS_Shape& V = itlv.Value();
		  if (myVerVerMap.IsBound( V ))
		    {
		      TopoDS_Shape NewV = myVerVerMap( V );
		      E.Free( Standard_True );
		      NewV.Orientation( V.Orientation() );
		      Handle(BRep_TVertex)& TV = *((Handle(BRep_TVertex)*) &V.TShape());
		      Handle(BRep_TVertex)& NewTV = *((Handle(BRep_TVertex)*) &NewV.TShape());
		      if (TV->Tolerance() > NewTV->Tolerance())
			NewTV->Tolerance( TV->Tolerance() );
		      NewTV->ChangePoints().Append( TV->ChangePoints() );
		      AsDes->Replace( V, NewV );
		      BB.Remove( E, V );
		      BB.Add( E, NewV );
		    }
		}
	    }
	}
    }
}

//=======================================================================
//function : IsBetweenCorks
//purpose  : 
//=======================================================================

static Standard_Boolean IsBetweenCorks(const TopoDS_Shape& E,
				       const Handle(BRepAlgo_AsDes)& AsDes,
				       const TopTools_ListOfShape&   LContext) 
{
  if (!AsDes->HasAscendant(E)) return 1;
  const TopTools_ListOfShape& LF = AsDes->Ascendant(E);
  TopTools_ListIteratorOfListOfShape it;
  for (it.Initialize(LF); it.More(); it.Next()) {
    const TopoDS_Shape& S = it.Value();
    Standard_Boolean found = 0;
    TopTools_ListIteratorOfListOfShape it2;
    for (it2.Initialize(LContext); it2.More(); it2.Next()) {
      if(S.IsSame(it2.Value())) {
	found = 1;
	break;
      }
    }
    if (!found) return 0;
  }
  return 1;
}
//=======================================================================
//function : BuildOnContext
//purpose  : 
//=======================================================================

void BRepOffset_MakeLoops::BuildOnContext(const TopTools_ListOfShape&   LContext,  
					  const BRepOffset_Analyse&     Analyse, 
					  const Handle(BRepAlgo_AsDes)& AsDes, 
					  BRepAlgo_Image&               Image,
					  const Standard_Boolean        InSide)
{
  //-----------------------------------------
  // unwinding of caps.
  //-----------------------------------------
  TopTools_ListIteratorOfListOfShape  it(LContext);
  TopTools_ListIteratorOfListOfShape  itl,itLCE;
  BRepAlgo_Loop                     Loops;
  Loops.VerticesForSubstitute( myVerVerMap );
  TopExp_Explorer                     exp; 
  TopTools_MapOfShape                 MapExtent;

  for (; it.More(); it.Next()) {
    const TopoDS_Face& F = TopoDS::Face(it.Value());
    TopTools_MapOfShape                 MBound;
    //-----------------------------------------------
    // Initialisation of Loops.
    // F is reversed it will be added in myOffC.
    // and myOffC will be reversed in the final result.
    //-----------------------------------------------
    TopoDS_Shape aLocalShape = F.Reversed();
    if (InSide) Loops.Init(TopoDS::Face(aLocalShape));
//    if (InSide) Loops.Init(TopoDS::Face(F.Reversed()));
    else        Loops.Init(F);
    //--------------------------------------------------------
    // return edges of F not modified by definition.
    //--------------------------------------------------------
    for (exp.Init(F.Oriented(TopAbs_FORWARD),TopAbs_EDGE);
	 exp.More();
	 exp.Next()) {
      TopoDS_Edge CE = TopoDS::Edge(exp.Current());
      MBound.Add(CE);   
      if (Analyse.HasAncestor(CE)) {
	// the stop of cups except for the connectivity stops between caps.
	//      if (!AsDes->HasAscendant(CE)) {
	aLocalShape = CE.Reversed();
	if (InSide) Loops.AddConstEdge(CE);
	else        Loops.AddConstEdge(TopoDS::Edge(aLocalShape));
//	else        Loops.AddConstEdge(TopoDS::Edge(CE.Reversed()));
      }
    }
    //------------------------------------------------------
    // Trace of offsets + connectivity edge between caps.
    //------------------------------------------------------    
    const TopTools_ListOfShape& LE = AsDes->Descendant(F);
    TopTools_ListOfShape        AddedEdges;
    
    for (itl.Initialize(LE); itl.More(); itl.Next()) {
      TopoDS_Edge E = TopoDS::Edge(itl.Value());
      if (Image.HasImage(E)) {
	//-------------------------------------------
	// E was already cut in another face.
	// Return cut edges and orientate them as E.
	// See pb for the edges that have disappeared?
	//-------------------------------------------
	const TopTools_ListOfShape& LCE = Image.Image(E);
	for (itLCE.Initialize(LCE); itLCE.More(); itLCE.Next()) {
	  TopoDS_Shape CE = itLCE.Value().Oriented(E.Orientation()); 	  
	  if (MapExtent.Contains(E)) {
	    Loops.AddConstEdge(TopoDS::Edge(CE));
	    continue;
	  }
	  if (!MBound.Contains(E)) CE.Reverse();
	  if (InSide) Loops.AddConstEdge(TopoDS::Edge(CE));
	  else
	    {
	      TopoDS_Shape aLocalShape = CE.Reversed();
	      Loops.AddConstEdge(TopoDS::Edge(aLocalShape));
	    }
//	  else        Loops.AddConstEdge(TopoDS::Edge(CE.Reversed()));
	}
      }
      else {
	if (IsBetweenCorks(E,AsDes,LContext) && AsDes->HasDescendant(E)) {
	  //connection between 2 caps
	  MapExtent.Add(E);
	  TopTools_ListOfShape LV;
	  if (InSide) {
	    for (itLCE.Initialize(AsDes->Descendant(E)); itLCE.More(); itLCE.Next()) {
	      LV.Append(itLCE.Value().Reversed());
	    }
	    Loops.AddEdge(E,LV);
	  }
	  else {
	    Loops.AddEdge(E,AsDes->Descendant(E));
	  }
	  AddedEdges.Append (E);
	}
	else if (IsBetweenCorks(E,AsDes,LContext)) {
	TopoDS_Shape aLocalShape = E.Reversed();
	  if (InSide) Loops.AddConstEdge(E);
	  else        Loops.AddConstEdge(TopoDS::Edge(aLocalShape));
//	  if (InSide) Loops.AddConstEdge(TopoDS::Edge(E));
//	  else        Loops.AddConstEdge(TopoDS::Edge(E.Reversed()));
	}
	else { 
	  TopoDS_Shape aLocalShape = E.Reversed();
	  if (InSide) Loops.AddConstEdge(TopoDS::Edge(aLocalShape));
	  else        Loops.AddConstEdge(E);
//	  if (InSide) Loops.AddConstEdge(TopoDS::Edge(E.Reversed()));
//	  else        Loops.AddConstEdge(TopoDS::Edge(E));
	}
      }
    }
    //------------------------
    // Unwind.
    //------------------------
    Loops.Perform();
    Loops.WiresToFaces();      
    //------------------------
    // MAJ SD.
    //------------------------
    const TopTools_ListOfShape&  NF = Loops.NewFaces();
    //-----------------------
    // F => New faces;
    //-----------------------
    Image.Bind(F,NF);   

    TopTools_ListIteratorOfListOfShape itAdded;
    for (itAdded.Initialize(AddedEdges); itAdded.More(); itAdded.Next()) {
      const TopoDS_Edge& E = TopoDS::Edge(itAdded.Value());
      //-----------------------
      //  E => New edges;
      //-----------------------
      if (Image.HasImage(E)) {
	Image.Add(E,Loops.NewEdges(E));
      }
      else {
	Image.Bind(E,Loops.NewEdges(E));
      }
    }
  }
  Loops.GetVerticesForSubstitute( myVerVerMap );
  if (myVerVerMap.IsEmpty())
    return;
  BRep_Builder BB;
  for (it.Initialize( LContext ); it.More(); it.Next())
    {
      TopoDS_Shape F = it.Value();
      TopTools_ListOfShape LIF;
      Image.LastImage( F, LIF );
      for (itl.Initialize(LIF); itl.More(); itl.Next())
	{
	  const TopoDS_Shape& IF = itl.Value();
	  TopExp_Explorer EdExp( IF, TopAbs_EDGE );
	  for (; EdExp.More(); EdExp.Next())
	    {
	      TopoDS_Shape E = EdExp.Current();
	      TopTools_ListOfShape VList;
	      TopoDS_Iterator VerExp( E );
	      for (; VerExp.More(); VerExp.Next())
		VList.Append( VerExp.Value() );
	      TopTools_ListIteratorOfListOfShape itlv( VList );
	      for (; itlv.More(); itlv.Next())
		{
		  const TopoDS_Shape& V = itlv.Value();
		  if (myVerVerMap.IsBound( V ))
		    {
		      TopoDS_Shape NewV = myVerVerMap( V );
		      E.Free( Standard_True );
		      NewV.Orientation( V.Orientation() );
		      Handle(BRep_TVertex)& TV = *((Handle(BRep_TVertex)*) &V.TShape());
		      Handle(BRep_TVertex)& NewTV = *((Handle(BRep_TVertex)*) &NewV.TShape());
		      if (TV->Tolerance() > NewTV->Tolerance())
			NewTV->Tolerance( TV->Tolerance() );
		      NewTV->ChangePoints().Append( TV->ChangePoints() );
		      AsDes->Replace( V, NewV );
		      BB.Remove( E, V );
		      BB.Add( E, NewV );
		    }
		}
	    }
	}
    }
}


//=======================================================================
//function : BuildFaces
//purpose  : 
//=======================================================================
  
void BRepOffset_MakeLoops::BuildFaces(const TopTools_ListOfShape&   LF, 
				      const Handle(BRepAlgo_AsDes)& AsDes, 
				      BRepAlgo_Image&               Image)
{
  TopTools_ListIteratorOfListOfShape itr,itl,itLCE;
  Standard_Boolean                   ToRebuild;
  BRepAlgo_Loop                    Loops;
  Loops.VerticesForSubstitute( myVerVerMap );
  BRep_Builder                       B;

  //----------------------------------
  // Loop on all faces //.
  //----------------------------------
  for (itr.Initialize(LF); itr.More(); itr.Next()) {
    TopoDS_Face F = TopoDS::Face(itr.Value());
    Loops.Init(F);
    ToRebuild = Standard_False;
    TopTools_ListOfShape        AddedEdges;
    
    if (!Image.HasImage(F)) {
      //----------------------------------
      // Face F not yet reconstructed.
      //----------------------------------
      const TopTools_ListOfShape& LE = AsDes->Descendant(F);
      //----------------------------------------------------------------
      // first loop to find if the edges of the face were reconstructed.
      // - maj on map MONV. Some vertices on reconstructed edges
      // coincide geometrically with old but are not IsSame.
      //----------------------------------------------------------------
      TopTools_DataMapOfShapeShape MONV;
      TopoDS_Vertex OV1,OV2,NV1,NV2;
      
      for (itl.Initialize(LE); itl.More(); itl.Next()) {
	TopoDS_Edge E = TopoDS::Edge(itl.Value());
	if (Image.HasImage(E)) {
	  const TopTools_ListOfShape& LCE = Image.Image(E);
	  if (LCE.Extent() == 1 && LCE.First().IsSame(E)) {
	    TopoDS_Shape aLocalShape = LCE.First().Oriented(E.Orientation());
	    TopoDS_Edge CE = TopoDS::Edge(aLocalShape);
//	    TopoDS_Edge CE = TopoDS::Edge(LCE.First().Oriented(E.Orientation()));
	    Loops.AddConstEdge(CE);
	    continue;
	  }
	  //----------------------------------
	  // F should be reconstructed.
	  //----------------------------------
	  ToRebuild = Standard_True;
	  for (itLCE.Initialize(LCE); itLCE.More(); itLCE.Next()) {
	    TopoDS_Shape aLocalShape = itLCE.Value().Oriented(E.Orientation());
	    TopoDS_Edge CE = TopoDS::Edge(aLocalShape); 
//	    TopoDS_Edge CE = TopoDS::Edge(itLCE.Value().Oriented(E.Orientation())); 
	    TopExp::Vertices (E ,OV1,OV2);
	    TopExp::Vertices (CE,NV1,NV2);
	    if (!OV1.IsSame(NV1)) MONV.Bind(OV1,NV1);
	    if (!OV2.IsSame(NV2)) MONV.Bind(OV2,NV2);
	    Loops.AddConstEdge(CE);
	  }
	}
      }
      if (ToRebuild) {
#ifdef DRAW
//POP for NT
	if ( Affich) {
	  char* name = new char[100];
	  sprintf(name,"CF_%d",NbF++);
	  DBRep::Set(name,F);
	}
#endif

	//-----------------------------------------------------------
	// Non-reconstructed edges on other faces are added.  
	// If their vertices were reconstructed they are reconstructed.
	//-----------------------------------------------------------
	for (itl.Initialize(LE); itl.More(); itl.Next()) {
	  Standard_Real f,l;
	  TopoDS_Edge E = TopoDS::Edge(itl.Value());
	  BRep_Tool::Range(E,f,l);
	  if (!Image.HasImage(E)) {
	    TopExp::Vertices (E,OV1,OV2);
	    TopTools_ListOfShape LV;
	    if (MONV.IsBound(OV1)) {
	      TopoDS_Vertex VV = TopoDS::Vertex(MONV(OV1));
	      VV.Orientation(TopAbs_FORWARD);
	      LV.Append(VV);
	      TopoDS_Shape aLocalShape = VV.Oriented(TopAbs_INTERNAL);
	      B.UpdateVertex(TopoDS::Vertex(aLocalShape),
			     f,E,BRep_Tool::Tolerance(VV));
	    }
	    if (MONV.IsBound(OV2)) {
	      TopoDS_Vertex VV = TopoDS::Vertex(MONV(OV2));
	      VV.Orientation(TopAbs_REVERSED);
	      LV.Append(VV);
	      TopoDS_Shape aLocalShape = VV.Oriented(TopAbs_INTERNAL);
	      B.UpdateVertex(TopoDS::Vertex(aLocalShape),
			     l,E,BRep_Tool::Tolerance(VV));
//	      B.UpdateVertex(TopoDS::Vertex(VV.Oriented(TopAbs_INTERNAL)),
//			     l,E,BRep_Tool::Tolerance(VV));
	    }
	    if (LV.IsEmpty()) Loops.AddConstEdge(E);
	    else  {
	      Loops.AddEdge    (E,LV);
	      AddedEdges.Append(E);
	    }
	  }
	}
      }  
    }
    if (ToRebuild) {
      //------------------------
      // Reconstruction.
      //------------------------
      Loops.Perform();
      Loops.WiresToFaces();
      //------------------------
      // MAJ SD.
      //------------------------
      const TopTools_ListOfShape&  NF = Loops.NewFaces();
      //-----------------------
      // F => New faces;
      //-----------------------
      Image.Bind(F,NF); 

      TopTools_ListIteratorOfListOfShape itAdded;
      for (itAdded.Initialize(AddedEdges); itAdded.More(); itAdded.Next()) {
	const TopoDS_Edge& E = TopoDS::Edge(itAdded.Value());
	//-----------------------
	//  E => New edges;
	//-----------------------
	if (Image.HasImage(E)) {
	  Image.Add(E,Loops.NewEdges(E));
	}
	else {
	  Image.Bind(E,Loops.NewEdges(E));
	}
      }
    }
  }
  Loops.GetVerticesForSubstitute( myVerVerMap );
  if (myVerVerMap.IsEmpty())
    return;
  BRep_Builder BB;
  for (itr.Initialize( LF ); itr.More(); itr.Next())
    {
      TopoDS_Shape F = itr.Value();
      TopTools_ListOfShape LIF;
      Image.LastImage( F, LIF );
      for (itl.Initialize(LIF); itl.More(); itl.Next())
	{
	  const TopoDS_Shape& IF = itl.Value();
	  TopExp_Explorer EdExp( IF, TopAbs_EDGE );
	  for (; EdExp.More(); EdExp.Next())
	    {
	      TopoDS_Shape E = EdExp.Current();
	      TopTools_ListOfShape VList;
	      TopoDS_Iterator VerExp( E );
	      for (; VerExp.More(); VerExp.Next())
		VList.Append( VerExp.Value() );
	      TopTools_ListIteratorOfListOfShape itlv( VList );
	      for (; itlv.More(); itlv.Next())
		{
		  const TopoDS_Shape& V = itlv.Value();
		  if (myVerVerMap.IsBound( V ))
		    {
		      TopoDS_Shape NewV = myVerVerMap( V );
		      E.Free( Standard_True );
		      NewV.Orientation( V.Orientation() );
		      Handle(BRep_TVertex)& TV = *((Handle(BRep_TVertex)*) &V.TShape());
		      Handle(BRep_TVertex)& NewTV = *((Handle(BRep_TVertex)*) &NewV.TShape());
		      if (TV->Tolerance() > NewTV->Tolerance())
			NewTV->Tolerance( TV->Tolerance() );
		      NewTV->ChangePoints().Append( TV->ChangePoints() );
		      AsDes->Replace( V, NewV );
		      BB.Remove( E, V );
		      BB.Add( E, NewV );
		    }
		}
	    }
	}
    }
}
