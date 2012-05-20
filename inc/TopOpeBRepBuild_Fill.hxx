// Created on: 1993-06-14
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


#ifndef _TopOpeBRepBuild_Fill_HeaderFile
#define _TopOpeBRepBuild_Fill_HeaderFile

//=======================================================================
//function : FillShape
//purpose  : 
//=======================================================================
void TopOpeBRepBuild_Builder::FillShape(const TopoDS_Shape& S1,
					const TopAbs_State ToBuild1,
					const TopTools_ListOfShape& LS2,
					const TopAbs_State ToBuild2,
					TopOpeBRepBuild_ShapeSet& aSet,
					const Standard_Boolean In_RevOri)
{
  Standard_Boolean RevOri = In_RevOri;

  TopAbs_ShapeEnum t = S1.ShapeType();
#ifdef DEB
  TopAbs_ShapeEnum t1,t11;
#else
  TopAbs_ShapeEnum t1=TopAbs_COMPOUND,t11=TopAbs_COMPOUND;
#endif
  if      (t == TopAbs_FACE )  { 
    t1 = TopAbs_WIRE;
    t11 = TopAbs_EDGE;
  }
  else if (t == TopAbs_SOLID || t == TopAbs_SHELL) {
    t1 = TopAbs_SHELL; 
    t11 = TopAbs_FACE; 
  }

  // if the shape S1 is a SameDomain one, get its orientation compared
  // with the shape taken as reference for all of the SameDomain shape of S1.
  Standard_Boolean hsd = myDataStructure->HasSameDomain(S1);
  if (hsd) {
    TopOpeBRepDS_Config ssc = myDataStructure->SameDomainOrientation(S1);
    if ( ssc == TopOpeBRepDS_DIFFORIENTED ) {
      RevOri = ! RevOri;
#ifdef DEB
//      Standard_Integer iFace = myDataStructure->Shape(S1);
//      cout<<endl<<"********** ";
//      cout<<"retournement d'orientation de ";TopAbs::Print(t,cout);
//      cout<<" "<<iFace<<endl;
#endif
    }
  }

  // work on a FORWARD shape <aShape>
  TopoDS_Shape aShape = S1; 
  myBuildTool.Orientation(aShape,TopAbs_FORWARD);

  TopoDS_Shape aSubShape;
  TopAbs_Orientation newori;

  // Explore the SubShapes of type <t1>
  for (TopOpeBRepTool_ShapeExplorer ex1(aShape,t1); ex1.More(); ex1.Next()) {
    aSubShape = ex1.Current();

    if ( ! myDataStructure->HasShape(aSubShape) ) {
      // SubShape is not in DS : classify it with shapes of LS2
      Standard_Boolean keep = KeepShape(aSubShape,LS2,ToBuild1);
      if (keep) {
	newori = Orient(myBuildTool.Orientation(aSubShape),RevOri);
	myBuildTool.Orientation(aSubShape,newori);
	aSet.AddShape(aSubShape);
      }
    }
    else {
      // SubShape has geometry : split the <t11> SubShapes of the SubShape
      TopOpeBRepTool_ShapeExplorer ex11(aSubShape,t11);
      SplitShapes(ex11,ToBuild1,ToBuild2,aSet,RevOri);
    } 
  } // exploration ot SubShapes of type <t1> of shape <S1>

} // FillShape


//=======================================================================
//function : FillFace
//purpose  : 
//=======================================================================
void TopOpeBRepBuild_Builder::FillFace(const TopoDS_Shape& F1, 
				       const TopAbs_State ToBuild1,
				       const TopTools_ListOfShape& LF2,
				       const TopAbs_State ToBuild2,
				       TopOpeBRepBuild_WireEdgeSet& WES,
				       const Standard_Boolean RevOri)
{
#ifdef DEB
  Standard_Boolean tSPF = TopOpeBRepBuild_GettraceSPF();
//  Standard_Integer iFace = myDataStructure->Shape(F1);
  if(tSPF){cout<<endl;}
  if(tSPF){GdumpSHASTA(F1,ToBuild1,"=-= FillFace ");}
#endif
  myListOfFace = LF2;
  FillShape(F1,ToBuild1,LF2,ToBuild2,WES,RevOri);
  myListOfFace.Clear();
} // FillFace


//=======================================================================
//function : FillSolid
//purpose  : load shells and faces from the solid in the ShellFaceSet <aSet>
//=======================================================================
void TopOpeBRepBuild_Builder::FillSolid(const TopoDS_Shape& S1, 
					const TopAbs_State ToBuild1, 
					const TopTools_ListOfShape& LS2,
					const TopAbs_State ToBuild2, 
					TopOpeBRepBuild_ShapeSet& aSet,
					const Standard_Boolean RevOri)
{
  FillShape(S1,ToBuild1,LS2,ToBuild2,aSet,RevOri);
} // FillSolid


//=======================================================================
//function : FillVertexSet
//purpose  : private
//=======================================================================
void TopOpeBRepBuild_Builder::FillVertexSet(TopOpeBRepDS_PointIterator& IT,
					    const TopAbs_State ToBuild,
					    TopOpeBRepBuild_PaveSet& PVS) const
{
  for (; IT.More(); IT.Next()) {
    FillVertexSetOnValue(IT,ToBuild,PVS);
  }
}


//=======================================================================
//function : FillVertexSetOnValue
//purpose  : private
//=======================================================================
void TopOpeBRepBuild_Builder::FillVertexSetOnValue
(const TopOpeBRepDS_PointIterator& IT,
 const TopAbs_State ToBuild,
 TopOpeBRepBuild_PaveSet& PVS) const
{
  TopoDS_Shape V;
  
  // ind = index of new point or existing vertex
  Standard_Integer ind = IT.Current();
  Standard_Boolean ispoint  = IT.IsPoint();
  //**!
  //if (ispoint) V = NewVertex(ind);
  if (ispoint && ind <= myDataStructure->NbPoints()) V = NewVertex(ind);
  //**!
  else         V = myDataStructure->Shape(ind);
  Standard_Real      par = IT.Parameter();
  TopAbs_Orientation ori = IT.Orientation(ToBuild);
  
  Standard_Boolean keep = Standard_True;
  //    if (ori==TopAbs_EXTERNAL || ori==TopAbs_INTERNAL) keep = Standard_False;
  
  if ( keep ) {
    myBuildTool.Orientation(V,ori);
    Handle(TopOpeBRepBuild_Pave) PV = new TopOpeBRepBuild_Pave(V,par,Standard_False);
    PVS.Append(PV);
  }
  
#ifdef DEB
  const TopoDS_Edge& EDEB = PVS.Edge();
  Standard_Integer iE; Standard_Boolean tSPS = GtraceSPS(EDEB,iE);
  if (tSPS) {
    if (keep) cout<<"+"; else cout<<"-";
    if (ispoint) cout<<" PDS "; else cout<<" VDS ";
    cout<<ind<<" : "; GdumpORIPARPNT(ori,par,BRep_Tool::Pnt(TopoDS::Vertex(V)));
    cout<<endl;
  }
#endif
}

//#ifndef _TopOpeBRepBuild_Fill_HeaderFile
#endif
