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


#include <TopOpeBRepBuild_Builder.jxx>
#include <TopOpeBRepDS_DataMapIteratorOfDataMapOfShapeListOfShapeOn1State.hxx>
#include <TopTools_DataMapIteratorOfDataMapOfIntegerListOfShape.hxx>
#include <TopOpeBRepDS_ListOfShapeOn1State.hxx>
#include <Geom_Curve.hxx>
#include <Geom2d_Curve.hxx>
#include <TopOpeBRepTool_2d.hxx>
#include <BRep_Tool.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS.hxx>
#include <BRep_Builder.hxx>
#include <TopExp.hxx>
#include <BRepAdaptor_Curve.hxx>
//#include <BRepAdaptor_Curve2d.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <BRep_Tool.hxx>
#include <gp_Pnt.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TopOpeBRepBuild_define.hxx>
#include <Bnd_Box.hxx>
#include <TopOpeBRepTool_FuseEdges.hxx>
#include <Standard_ProgramError.hxx>
#ifdef DEB
extern Standard_Boolean TopOpeBRepBuild_GetcontextNOFE();
#endif

//=======================================================================
//function : End
//purpose  : 
//=======================================================================
void TopOpeBRepBuild_Builder::End()
{
  const TopOpeBRepDS_DataStructure& BDS = myDataStructure->DS();
  {
    // recodage de la continuite (edge,(f1,f2)) != C0 perdue lors
    // du changement de surface-support d'une arete non decoupee
    // d'une face tangente.  
    for (Standard_Integer i=1;i<=2;i++) {   
      TopoDS_Shape S; TopAbs_State sta=TopAbs_UNKNOWN;
      if      ( i==1 ) { S = myShape1; sta = myState1; }
      else if ( i==2 ) { S = myShape2; sta = myState2; }
      
      TopExp_Explorer exs;
      for (exs.Init(S,TopAbs_SHELL);exs.More();exs.Next()) {
//      for (TopExp_Explorer exs(S,TopAbs_SHELL);exs.More();exs.Next()) {
	const TopoDS_Shape& SH = exs.Current();
	Standard_Boolean SHhassha = BDS.HasShape(SH);
	if ( !SHhassha ) continue;
	
	Standard_Boolean Fhassam = Standard_False;
	TopExp_Explorer exf;
	for (exf.Init(SH,TopAbs_FACE);exf.More(); exf.Next()) {
//	for (TopExp_Explorer exf(SH,TopAbs_FACE);exf.More(); exf.Next()) {
	  Fhassam = myDataStructure->HasSameDomain(exf.Current());
	  if ( Fhassam ) break;
	}
	if ( !Fhassam ) continue;
	
	TopTools_IndexedDataMapOfShapeListOfShape M;
	TopExp::MapShapesAndAncestors(S,TopAbs_EDGE,TopAbs_FACE,M);
	Standard_Integer nE = M.Extent();
	for (Standard_Integer iE = 1; iE <= nE; iE++) {
	  const TopoDS_Edge& E = TopoDS::Edge(M.FindKey(iE));
	  if ( IsSplit(E,sta) ) continue;
	  const TopTools_ListOfShape& LF = M.FindFromIndex(iE);
	  if ( LF.Extent() < 2 ) continue;
	  
	  // NYI : > 2 faces connexes par E : iterer sur tous les couples
	  TopTools_ListIteratorOfListOfShape itLF(LF);
	  const TopoDS_Face& F1 = TopoDS::Face(itLF.Value()); itLF.Next();
	  const TopoDS_Face& F2 = TopoDS::Face(itLF.Value());
	  GeomAbs_Shape C = BRep_Tool::Continuity(E,F1,F2);
	  if ( C == GeomAbs_C0 ) continue;
	  
	  Standard_Boolean F1hassam = myDataStructure->HasSameDomain(F1);
	  Standard_Boolean F2hassam = myDataStructure->HasSameDomain(F2);
	  if ( !F1hassam  && !F2hassam ) continue;
	  
	  Standard_Boolean F1issplit = IsSplit(F1,sta);
	  Standard_Boolean F2issplit = IsSplit(F2,sta);
	  F1issplit &= (Splits(F1,sta).Extent() != 0);
	  F2issplit &= (Splits(F2,sta).Extent() != 0);
	  if ( !F1issplit && !F2issplit ) continue;
	  
	  TopoDS_Face FF1=F1,FF2=F2;
	  for (Standard_Integer ii=1; ii<=2; ii++) {
	    if ((ii==1 && !F1issplit) || (ii==2 && !F2issplit)) continue;
	    TopoDS_Face F;
	    if (ii==1) F = F1;
	    else       F = F2;
	    Standard_Boolean f = Standard_False;
	    TopTools_ListIteratorOfListOfShape it;
	    for (it.Initialize(Splits(F,sta));it.More();it.Next()) {
	      const TopoDS_Shape& SF = it.Value();
	      if (SF.ShapeType() != TopAbs_FACE) continue;
	      TopExp_Explorer ex;
	      for (ex.Init(SF,TopAbs_EDGE);ex.More();ex.Next()) {
		if (ex.Current().IsSame(E)) {
		  if (ii==1) FF1 = TopoDS::Face(it.Value());
		  else       FF2 = TopoDS::Face(it.Value());
		  f = Standard_True; break;
		}
	      }
	      if (f) break;
	    }
	  }
	  BRep_Builder B;
	  B.Continuity(E,FF1,FF2,C);
	}
      }
    }
  }
  
  // M.A.J de la tolerance des vertex
  {
// modified by NIZHNY-MKK  Fri Oct  6 16:13:33 2000.BEGIN
    TopTools_MapOfShape aMapOfNewEdges, aMapOfNewVertices;
    TopTools_ListIteratorOfListOfShape anIt;
    Standard_Integer iteratorofnewshape=0;
    for(iteratorofnewshape=1; iteratorofnewshape <= myDataStructure->NbCurves(); iteratorofnewshape++) {
      for(anIt.Initialize(NewEdges(iteratorofnewshape)); anIt.More(); anIt.Next()) {
	aMapOfNewEdges.Add(anIt.Value());
      }
    }
    for(iteratorofnewshape=1; iteratorofnewshape <= myDataStructure->NbPoints(); iteratorofnewshape++) {      
      aMapOfNewVertices.Add(NewVertex(iteratorofnewshape));
    }
// modified by NIZHNY-MKK  Fri Oct  6 16:13:36 2000.END

    TopoDS_Compound R;BRep_Builder B;B.MakeCompound(R);
    const TopTools_ListOfShape& lmergesha1 = Merged(myShape1,myState1);
    TopTools_ListIteratorOfListOfShape it(lmergesha1); for(;it.More();it.Next()) B.Add(R,it.Value());
    const TopTools_ListOfShape& LOES = Section();
#ifdef DEB
//    Standard_Integer nLOES = LOES.Extent();
#endif
        
    TopTools_IndexedDataMapOfShapeListOfShape idmoelof; TopExp::MapShapesAndAncestors(R,TopAbs_EDGE,TopAbs_FACE,idmoelof);
    TopTools_IndexedDataMapOfShapeListOfShape idmovloe; TopExp::MapShapesAndAncestors(R,TopAbs_VERTEX,TopAbs_EDGE,idmovloe);
    TopTools_IndexedDataMapOfShapeListOfShape idmovloes; for (TopTools_ListIteratorOfListOfShape I(LOES);I.More();I.Next())
      TopExp::MapShapesAndAncestors(I.Value(),TopAbs_VERTEX,TopAbs_EDGE,idmovloes);
    Standard_Integer iv,nv = idmovloe.Extent();
    for (iv=1;iv<=nv;iv++) {
      Standard_Integer nP1 = 0;
      const TopoDS_Vertex& V = TopoDS::Vertex(idmovloe.FindKey(iv));
      Standard_Boolean isbe = idmovloes.Contains(V);
      if ( !isbe ) continue;

      const TopTools_ListOfShape& loe1 = idmovloe.FindFromIndex(iv); 
#ifdef DEB
//      Standard_Integer nloe1 = loe1.Extent();
#endif
      TopTools_MapOfShape mose; //une seule fois chaque arete
      TopTools_ListOfShape loe; 
      TopTools_ListIteratorOfListOfShape iloe;
      for (iloe.Initialize(loe1);iloe.More();iloe.Next()) {
	const TopoDS_Edge& E = TopoDS::Edge(iloe.Value());
	Standard_Boolean isb = mose.Contains(E); if (isb) continue;
	mose.Add(E);loe.Append(E);
      }
#ifdef DEB
//      Standard_Integer nloe = loe.Extent();
#endif
      
      for (iloe.Initialize(loe);iloe.More();iloe.Next()) {
	const TopoDS_Edge& E = TopoDS::Edge(iloe.Value());
	const TopTools_ListOfShape& lof = idmoelof.FindFromKey(E);
	Standard_Integer nlof = lof.Extent();
	nP1 += nlof+1;
      }

      TColgp_Array1OfPnt TP(1,nP1);
      Standard_Integer nP2 = 0;
      for (iloe.Initialize(loe);iloe.More();iloe.Next()) {
	const TopoDS_Edge& E = TopoDS::Edge(iloe.Value());
        Standard_Real pv = BRep_Tool::Parameter(V,E);
        gp_Pnt Pv;
        Standard_Real f,l;Handle(Geom_Curve) C3D = BRep_Tool::Curve(E,f,l);
        if (!C3D.IsNull()) {
          Pv = C3D->Value(pv);
          TP(++nP2) = Pv;
        }
	const TopTools_ListOfShape& lof = idmoelof.FindFromKey(E);
#ifdef DEB
//	Standard_Integer nlof = lof.Extent();
#endif
	for (TopTools_ListIteratorOfListOfShape ilof(lof);ilof.More();ilof.Next()) {
	  const TopoDS_Face& F = TopoDS::Face(ilof.Value());
          Standard_Real tolpc;
          Standard_Boolean pcf = FC2D_HasCurveOnSurface(E,F);
          Handle(Geom2d_Curve) C2D;
          if (!pcf) {
            C2D = FC2D_CurveOnSurface(E,F,f,l,tolpc);
            if (C2D.IsNull()) Standard_ProgramError::Raise("TopOpeBRepBuild_Builder::End 1");
            Standard_Real tolE = BRep_Tool::Tolerance(E);
            Standard_Real tol = Max(tolE,tolpc);
            B.UpdateEdge(E,C2D,F,tol);
          }
          C2D = FC2D_CurveOnSurface(E,F,f,l,tolpc);
          gp_Pnt2d P2 = C2D->Value(pv);
          BRepAdaptor_Surface BAS(F,Standard_False);
          Pv = BAS.Value(P2.X(),P2.Y());
          TP(++nP2) = Pv;
// modified by NIZHNY-MKK  Fri Sep 29 16:08:28 2000.BEGIN
	  if(aMapOfNewEdges.Contains(E)) {
	    Standard_Real anEdgeTol = BRep_Tool::Tolerance(E);
	    Standard_Real aFaceTol = BRep_Tool::Tolerance(F);
	    if(anEdgeTol < aFaceTol)
	      B.UpdateEdge(E, aFaceTol);
	  }
// modified by NIZHNY-MKK  Fri Sep 29 16:08:32 2000.END
	}
// modified by NIZHNY-MKK  Fri Sep 29 16:54:08 2000.BEGIN
	if(aMapOfNewVertices.Contains(V)) {
	  Standard_Real aVertexTol = BRep_Tool::Tolerance(V);
	  Standard_Real anEdgeTol = BRep_Tool::Tolerance(E);
	  if (aVertexTol < anEdgeTol)
	    B.UpdateVertex(V, anEdgeTol);
	}
// modified by NIZHNY-MKK  Fri Sep 29 16:54:12 2000.END
      }
      
      Standard_Real newtol = BRep_Tool::Tolerance(V);
      Bnd_Box BOX;
      gp_Pnt Pv = BRep_Tool::Pnt(V);
      BOX.Set(Pv);
      for (Standard_Integer i=1;i<=nP2;i++) {
	const gp_Pnt& Pi = TP(i);
	BOX.Update(Pi.X(),Pi.Y(),Pi.Z());
      }
      Standard_Real aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;	
      BOX.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);
      gp_Pnt P1(aXmin, aYmin, aZmin);
      gp_Pnt P2(aXmax, aYmax, aZmax);
      Standard_Real d = P1.Distance(P2);
      if (d > newtol) {
#ifdef DEB
        cout<<"\npoint P"<<iv<<" "<<Pv.X()<<" "<<Pv.Y()<<" "<<Pv.Z()<<endl;
        cout<<"TopOpeBRepBuild_Builder::End BOX newtol "<<newtol<<" -> "<<d<<endl;
#endif
        newtol = d;
        B.UpdateVertex(V,newtol);
      }
    }
  }

  Standard_Boolean makeFE = Standard_True;
#ifdef DEB
  makeFE = !TopOpeBRepBuild_GetcontextNOFE();
#endif

  if (makeFE) {
//    TopAbs_State state = myState1;
    TopTools_ListOfShape& ls = ChangeMerged(myShape1,myState1);
    for (TopTools_ListIteratorOfListOfShape itls(ls);itls.More();itls.Next()) {
      TopoDS_Shape& SFE = itls.Value();
      TopOpeBRepTool_FuseEdges FE(SFE);

      // avoid fusing old edges
      TopTools_IndexedMapOfShape mapOldEdges;
      TopExp::MapShapes (myShape1, TopAbs_EDGE, mapOldEdges);
      TopExp::MapShapes (myShape2, TopAbs_EDGE, mapOldEdges);
      FE.AvoidEdges (mapOldEdges);

      // Get List of edges that have been fused
      TopTools_DataMapOfIntegerListOfShape mle;
      FE.Edges(mle);

      Standard_Integer nle = mle.Extent();
      if ( nle != 0 ) {
	FE.Perform();
	SFE = FE.Shape();

	TopTools_DataMapOfIntegerShape mre;
	TopTools_DataMapOfShapeShape mlf;
	FE.ResultEdges(mre);
	FE.Faces(mlf);

	// edit the split to remove to edges to be fused and put them into the Merged
	//

	UpdateSplitAndMerged(mle, mre, mlf, TopAbs_IN);
	UpdateSplitAndMerged(mle, mre, mlf, TopAbs_OUT);
	UpdateSplitAndMerged(mle, mre, mlf, TopAbs_ON);

      }


    } // makeFE
  }
}

//=======================================================================
//function : UpdateSplitAndMerged
//purpose  :  edit the split to remove to edges to be fused and put them into the Merged
//=======================================================================

void TopOpeBRepBuild_Builder::UpdateSplitAndMerged(const  TopTools_DataMapOfIntegerListOfShape& mle,
				const  TopTools_DataMapOfIntegerShape& mre,
				const  TopTools_DataMapOfShapeShape& mlf,
				const  TopAbs_State state)
{
  const  TopOpeBRepDS_DataMapOfShapeListOfShapeOn1State& MapSplit = MSplit(state);
  TopOpeBRepDS_DataMapIteratorOfDataMapOfShapeListOfShapeOn1State it;
  for (it.Initialize(MapSplit); it.More(); it.Next()) {
    const TopoDS_Shape& e = it.Key();
 
    // For each edge of the MapSplit
    if ( e.ShapeType() == TopAbs_EDGE ) {
   
      // get the list of splitted edges.
      TopTools_ListOfShape& LstSplit = ChangeSplit(e,state);
   
      // for each edge of the list of splitted edges
      TopTools_ListIteratorOfListOfShape itSplitEdg;
      itSplitEdg.Initialize(LstSplit);
      while ( itSplitEdg.More()) {
	const TopoDS_Shape& edgecur = itSplitEdg.Value();
	
	// for each "packet" of edges to be fused
	TopTools_DataMapIteratorOfDataMapOfIntegerListOfShape itLstEdg;
	itLstEdg.Initialize(mle);
	Standard_Boolean Found = Standard_False;
	while ( itLstEdg.More() && !Found) {
	  const Standard_Integer& iLst = itLstEdg.Key();
	  const TopTools_ListOfShape& LmapEdg = mle.Find(iLst);
	  
	  // look for each edge of the list if it is in the map Split
	  TopTools_ListIteratorOfListOfShape itEdg; 
	  itEdg.Initialize(LmapEdg);
	  while ( itEdg.More() && !Found ) {
	    const TopoDS_Shape& edgefuse = itEdg.Value();
	    if (edgecur.IsSame(edgefuse)) {
	      Found = Standard_True;


	      LstSplit.Remove(itSplitEdg);

	      // edit the list of merged
	      TopAbs_State stateMerged;
	      if (ShapeRank(e) == 1)
		stateMerged = myState1;
	      else
		stateMerged = myState2;
	      
	      TopTools_ListOfShape LstMerged;
	      LstMerged.Append(mre(iLst));
	      ChangeMerged(e,stateMerged) = LstMerged;
	      
	    }
	    itEdg.Next();
	  }
	  
	  itLstEdg.Next();
	}
	
	if (!Found) {
	  itSplitEdg.Next();
	}

      }
   
    }
    // For each face of the MapSplit
    else if ( e.ShapeType() == TopAbs_FACE ) {
      // get the list of splitted faces.
      TopTools_ListOfShape& LstSplit = ChangeSplit(e,state);
   
      // for each face of the list of splitted faces
      TopTools_ListIteratorOfListOfShape itSplitFac;
      itSplitFac.Initialize(LstSplit);
      while ( itSplitFac.More()) {
	const TopoDS_Shape& facecur = itSplitFac.Value();

	if (mlf.IsBound(facecur)) {
	  LstSplit.InsertBefore(mlf(facecur),itSplitFac);
	  LstSplit.Remove(itSplitFac);

	}
	else {
	  itSplitFac.Next();
	}
      }      
    }
  }
}


  
