// Created on: 2000-12-25
// Created by: Igor FEOKTISTOV
// Copyright (c) 2000-2012 OPEN CASCADE SAS
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

#include <QANewModTopOpe_Intersection.ixx>
#include <TopoDS.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <BRep_Builder.hxx>
#include <BRep_Tool.hxx>
#include <TopExp_Explorer.hxx>
#include <BRepExtrema_SupportType.hxx>
#include <BRepExtrema_DistShapeShape.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <TopoDS_Vertex.hxx>
#include <gp_Pnt.hxx>
#include <BRepAlgo_EdgeConnector.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopoDS_Iterator.hxx>
#include <BRepTools.hxx>
#include <BOPTools_SSIntersectionAttribute.hxx>
#include <BOPTools_DSFiller.hxx>
#include <TopTools_MapOfShape.hxx>
#include <TopoDS_Edge.hxx>
#include <QANewModTopOpe_Tools.hxx>


static Standard_Boolean NoFaces(const TopoDS_Shape& S1, const TopoDS_Shape& S2)
{
  TopExp_Explorer Ex;
  Ex.Init(S1,TopAbs_FACE);
  Standard_Boolean f1 = Ex.More();
  Ex.Init(S2,TopAbs_FACE);
  Standard_Boolean f2 = Ex.More();

  return !f1&&!f2;
}

QANewModTopOpe_Intersection::QANewModTopOpe_Intersection( const TopoDS_Shape& theObject1, 
					        const TopoDS_Shape& theObject2 )
: BRepAlgoAPI_BooleanOperation( theObject1, theObject2, BOP_SECTION)
{
  myMapGener.Clear();

  if(NoFaces(myS1, myS2)) {

    BRep_Builder BB;
    BB.MakeCompound(TopoDS::Compound(myShape));

    BRepExtrema_DistShapeShape DSS(myS1, myS2); 


    if(DSS.IsDone() && DSS.NbSolution() > 0) {
      Standard_Integer nbs = DSS.NbSolution();
      Standard_Real mindist = DSS.Value();
      Standard_Real maxtol = 0., tol;
      TopExp_Explorer ExV;
      for(ExV.Init(myS1,TopAbs_VERTEX); ExV.More(); ExV.Next()) { 
	TopoDS_Vertex Vertex=TopoDS::Vertex(ExV.Current());
	tol=BRep_Tool::Tolerance(Vertex);
	if(tol > maxtol) maxtol = tol;
      }

      for(ExV.Init(myS2,TopAbs_VERTEX); ExV.More(); ExV.Next()) { 
	TopoDS_Vertex Vertex=TopoDS::Vertex(ExV.Current());
	tol=BRep_Tool::Tolerance(Vertex);
	if(tol > maxtol) maxtol = tol;
      }
	
      if(mindist <= maxtol) {
	tol = maxtol*maxtol;
	Standard_Integer i;
	  
	for(i = 1; i <= nbs; i++) {
	  gp_Pnt p1 = DSS.PointOnShape1(i);
	  gp_Pnt p2 = DSS.PointOnShape2(i);
	  if(p1.SquareDistance(p2) > tol) continue;
	  BRepExtrema_SupportType aSupTyp = DSS. SupportTypeShape1(i);
	  if(aSupTyp == BRepExtrema_IsVertex) {
	    BB.Add(myShape, DSS.SupportOnShape1(i));
	  }
	  else {
	    aSupTyp = DSS. SupportTypeShape2(i);
	    if(aSupTyp == BRepExtrema_IsVertex) {
	      BB.Add(myShape, DSS.SupportOnShape2(i));
	    }
	    else {
	      gp_Pnt p(.5*(p1.XYZ()+p2.XYZ()));
	      BRepBuilderAPI_MakeVertex mkV(p);
	      BB.Add(myShape, mkV.Vertex());

	      if (!myMapGener.IsBound(DSS. SupportOnShape1(i))) {
		// for Mandrake-10 - mkv,02.06.06 - myMapGener.Bind(DSS.SupportOnShape1(i), TopTools_ListOfShape());
                TopTools_ListOfShape aListOfShape1;
		myMapGener.Bind(DSS.SupportOnShape1(i), aListOfShape1);
              }
	      myMapGener(DSS.SupportOnShape1(i)).Append(mkV.Vertex());

	      if (!myMapGener.IsBound(DSS.SupportOnShape2(i))) {
		// for Mandrake-10 - mkv,02.06.06 - myMapGener.Bind(DSS.SupportOnShape2(i), TopTools_ListOfShape());
                TopTools_ListOfShape aListOfShape2;
		myMapGener.Bind(DSS.SupportOnShape2(i), aListOfShape2);
              }
	      myMapGener(DSS.SupportOnShape2(i)).Append(mkV.Vertex());

	    }

	  }
	}
      }
    }

    Done();
    return;
  }

  Standard_Boolean bIsNewFiller = PrepareFiller();
    //
  if (myErrorStatus!=1) {
    // there were errors during the preparation 
    return;
  }
  //
  if (bIsNewFiller) {
    //Prepare the DS
    BOPTools_SSIntersectionAttribute aSectionAttribute(Standard_True, 
						       Standard_False, Standard_False);
    myDSFiller->Perform(aSectionAttribute);
  }

  Build();

  Standard_Boolean bcw = BuilderCanWork();

  if ( ! bcw ) return;

  BRep_Builder BB;
  BB.MakeCompound(TopoDS::Compound(myShape));
  TopTools_ListIteratorOfListOfShape itloe(SectionEdges());

  if(itloe.More()) {

    for(; itloe.More(); itloe.Next()) BB.Add(myShape,itloe.Value());

    // try to make wire from set of edges
    TopTools_ListOfShape LOEdge;
    TopTools_ListOfShape LOSEdge;
    Standard_Integer nbe = 0;
    TopoDS_Shape aux;
    TopExp_Explorer Ex;
    BB.MakeCompound(TopoDS::Compound(aux));
    for(Ex.Init(myShape,TopAbs_EDGE); Ex.More(); Ex.Next()) {
      LOEdge.Append(Ex.Current()); 
      LOSEdge.Append(Ex.Current());
      nbe++;
    }
    BRepAlgo_EdgeConnector EC;
    TopoDS_Shape se = LOEdge.First();
    EC.Add(LOEdge);
    EC.AddStart(LOSEdge);
    const TopTools_ListOfShape& LOWire = EC.MakeBlock();
    TopTools_ListIteratorOfListOfShape its;
    for(its.Initialize(LOWire);its.More();its.Next()) {
      BB.Add(aux,its.Value());
    }
    for(Ex.Init(aux,TopAbs_EDGE); Ex.More(); Ex.Next()) {
      nbe--;
    }
    if(nbe == 0) myShape = aux;
    
  }
  else {
    // check if there are new vertices - IFV

    Standard_Integer nbp = QANewModTopOpe_Tools::NbPoints(myDSFiller);

    if(nbp > 0) {

      TopoDS_Shape aux1, aux2;
      BB.MakeCompound(TopoDS::Compound(aux1));
      BB.MakeCompound(TopoDS::Compound(aux2));

      BB.Add(aux1, myS1);
      BB.Add(aux1, myS2);

      Standard_Integer i;
      Standard_Real maxtol = 0., tol;

      for(i = 1; i <= nbp; i++)  {
	TopoDS_Vertex aVertex=
                      TopoDS::Vertex(QANewModTopOpe_Tools::NewVertex(myDSFiller, i));

	tol=BRep_Tool::Tolerance(aVertex);
	if(tol > maxtol) maxtol = tol;
	BB.Add(aux2, aVertex);
      }
	
      BRepExtrema_DistShapeShape DSS(aux1, aux2); 
      if(DSS.IsDone() && DSS.NbSolution() > 0) {
	Standard_Integer nbs = DSS.NbSolution();
	Standard_Real mindist = DSS.Value();
	if(mindist <= maxtol) {
	  tol = maxtol*maxtol;
	  
	  TopTools_MapOfShape aMap;
	  
	  for(i = 1; i <= nbs; i++) {
	    gp_Pnt p1 = DSS.PointOnShape1(i);
	    gp_Pnt p2 = DSS.PointOnShape2(i);
	    if(p1.SquareDistance(p2) > tol) continue;
	    BRepExtrema_SupportType aSupTyp = DSS.SupportTypeShape1(i);
	    TopoDS_Vertex aVertex;
	    if(aSupTyp == BRepExtrema_IsVertex) {
	      aVertex = TopoDS::Vertex(DSS.SupportOnShape1(i));
	      TopoDS_Iterator anIter(myShape);
	      Standard_Boolean anIsNew = Standard_True;
	      for(; anIter.More(); anIter.Next()) {
		if(BRepTools::Compare(aVertex, TopoDS::Vertex(anIter.Value()))) {
		  anIsNew = Standard_False;
		  break;
		}
	      }
	      if(anIsNew) {
		BB.Add(myShape, aVertex);
	      }
	    }
	    else {
	      aVertex = TopoDS::Vertex(DSS.SupportOnShape2(i));
	      if(aMap.Add(aVertex)) BB.Add(myShape, aVertex);
	      if (!myMapGener.IsBound(DSS.SupportOnShape1(i))) {
		// for Mandrake-10 - mkv,02.06.06 - myMapGener.Bind(DSS.SupportOnShape1(i), TopTools_ListOfShape());
                TopTools_ListOfShape aListOfShape3;
		myMapGener.Bind(DSS.SupportOnShape1(i), aListOfShape3);
              }
	      myMapGener(DSS.SupportOnShape1(i)).Append(aVertex);
	      
	    }
	  } // end for
	}
      }
    }
  }
  
  
  Done();
  
}

//=======================================================================
//function : Generated
//purpose  : gives list of shape generated from shape S
//=======================================================================
const TopTools_ListOfShape& QANewModTopOpe_Intersection::Generated(const TopoDS_Shape& theS) 
{
  myGenerated.Clear();

  if(theS.ShapeType() == TopAbs_FACE || theS.ShapeType() == TopAbs_EDGE) {
    if (BRepAlgoAPI_BooleanOperation::HasGenerated()) {
      const TopTools_ListOfShape         &aLOfShape = 
	                          BRepAlgoAPI_BooleanOperation::Generated(theS);
      TopTools_ListIteratorOfListOfShape  anIter(aLOfShape);

      for (; anIter.More(); anIter.Next()) {
	const TopoDS_Shape &aGenShape = anIter.Value();

	if (aGenShape.ShapeType() == TopAbs_VERTEX)
	  continue;

	myGenerated.Append(aGenShape);
      }
    }

    if(myMapGener.IsBound(theS)) {
      TopTools_ListIteratorOfListOfShape anIter(myMapGener(theS));

      for(; anIter.More(); anIter.Next())
	myGenerated.Append(anIter.Value());
    }
  }

  return myGenerated;

}

//=======================================================================
//function : HasGenerated
//purpose  : 
//=======================================================================
Standard_Boolean QANewModTopOpe_Intersection::HasGenerated() const
{
  Standard_Boolean aHasGenerated = Standard_False;

  if (BRepAlgoAPI_BooleanOperation::HasGenerated()) {
    aHasGenerated = Standard_True;
  }
  else {
    aHasGenerated = !myMapGener.IsEmpty();
  }
  return aHasGenerated;
}


//=======================================================================
//function : IsDeleted
//purpose  : 
//=======================================================================
Standard_Boolean QANewModTopOpe_Intersection::IsDeleted(const TopoDS_Shape& aS) 
{
  if(BRepAlgoAPI_BooleanOperation::IsDeleted(aS))
    return Standard_True;

  if(myMapGener.IsBound(aS))
    return Standard_False;
  return Standard_True;
}

//=======================================================================
//function : HasDeleted
//purpose  : 
//=======================================================================
Standard_Boolean QANewModTopOpe_Intersection::HasDeleted() const
{
  Standard_Real aresult = Standard_False;
  TopExp_Explorer anExp;

  for(Standard_Integer argit = 0; argit < 2; argit++) {
    Standard_Boolean bTillVertex = Standard_True;

    if(argit == 0)
      anExp.Init(myS1, TopAbs_FACE);
    else
      anExp.Init(myS2, TopAbs_FACE);

    if(anExp.More())
      bTillVertex = Standard_False;
    Standard_Integer nb = (bTillVertex) ? 3 : 2;

    for(Standard_Integer i = 0; i < nb; i++) {
      TopAbs_ShapeEnum aType = (i == 0) ? TopAbs_FACE : ((i == 1) ? TopAbs_EDGE : TopAbs_VERTEX);

      if(argit == 0)
	anExp.Init(myS1, aType);
      else
	anExp.Init(myS2, aType);

      for(; anExp.More(); anExp.Next()) {
	if(!myMapGener.IsBound(anExp.Current())) {
	  return Standard_True;
	}
      }
    }
  }
  return Standard_False;
}
