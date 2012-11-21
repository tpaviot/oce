// Created on: 2002-01-28
// Created by: Igor FEOKTISTOV
// Copyright (c) 2002-2012 OPEN CASCADE SAS
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

#include <QANewModTopOpe.ixx>
#include <TopAbs.hxx>
#include <TopoDS_Iterator.hxx>
#include <BRepCheck_Analyzer.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopExp.hxx>
#include <TopTools_DataMapOfShapeInteger.hxx>
#include <math_Matrix.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <BRepTools_Substitution.hxx>
#include <BRepCheck_ListIteratorOfListOfStatus.hxx>
#include <BRepCheck_Result.hxx>
#include <BRepCheck.hxx>
#include <BRepCheck_Shell.hxx>
#include <BRepCheck_Wire.hxx>
#include <TopTools_MapIteratorOfMapOfShape.hxx>
#include <TopTools_MapOfShape.hxx>

static Standard_Boolean NoInternalVertices(const TopoDS_Shape& TheS);
static Standard_Boolean CorrectOrientation(const TopoDS_Shell& TheS);

static TopoDS_Shape RemoveIntExtEdges(const TopoDS_Shape& TheS) 
{

  TopoDS_Shape aCopy = TheS;
  BRepTools_Substitution aSubst;
  TopTools_ListOfShape anEmptyList;
  TopAbs_Orientation anOr;

  TopExp_Explorer anExp(aCopy, TopAbs_EDGE);
  for(; anExp.More(); anExp.Next()) {
    anOr = anExp.Current().Orientation();
    if(anOr == TopAbs_INTERNAL || anOr == TopAbs_EXTERNAL) {
      if(!aSubst.IsCopied(anExp.Current())) {
	aSubst.Substitute(anExp.Current(), anEmptyList);
      }
    }
  }

  aSubst.Build(aCopy);

  if(aSubst.IsCopied(aCopy)) {
    aCopy = aSubst.Copy(aCopy).First();
  }

  return aCopy;
}

Standard_Boolean QANewModTopOpe::IsValid(const TopoDS_Shape& TheS, const Standard_Boolean GeomControls)
{

  TopExp_Explorer anExp, anExp1;  
  TopoDS_Shape aCopy;

  anExp.Init(TheS, TopAbs_SOLID);
  for(; anExp.More(); anExp.Next()) {

    aCopy = RemoveIntExtEdges(anExp.Current());

    BRepCheck_Analyzer anAnlz(aCopy, GeomControls);

    if(anAnlz.IsValid()) continue;
    else return Standard_False;

  }

  anExp.Init(TheS, TopAbs_SHELL, TopAbs_SOLID);
  for(; anExp.More(); anExp.Next()) {

    aCopy = RemoveIntExtEdges(anExp.Current());

    Handle(BRepCheck_Shell) aChkSh = new BRepCheck_Shell(TopoDS::Shell(aCopy));
    aChkSh->Minimum();
    aChkSh->Closed(Standard_True);
    aChkSh->Orientation(Standard_True);
    BRepCheck_ListIteratorOfListOfStatus anItl(aChkSh->Status());
    for (;anItl.More(); anItl.Next()) {
      if((anItl.Value() == BRepCheck_NoError) ||
	 (anItl.Value() == BRepCheck_InvalidMultiConnexity) ||
	 (anItl.Value() == BRepCheck_NotClosed) ||
	 (anItl.Value() == BRepCheck_BadOrientationOfSubshape)) continue;
      return Standard_False;
    }

    anExp1.Init(anExp.Current(), TopAbs_FACE);
    for(; anExp1.More(); anExp1.Next()) {
      if(IsValid(anExp1.Current())) continue;
      else return Standard_False;
    }
  }

  anExp.Init(TheS, TopAbs_FACE, TopAbs_SHELL);
  for(; anExp.More(); anExp.Next()) {

    aCopy = RemoveIntExtEdges(anExp.Current());

    BRepCheck_Analyzer anAnlz(aCopy, GeomControls);

    if(anAnlz.IsValid()) continue;
    else return Standard_False;

  }

  anExp.Init(TheS, TopAbs_WIRE, TopAbs_FACE);
  for(; anExp.More(); anExp.Next()) {

    BRepCheck_Analyzer anAnlz(anExp.Current(), GeomControls);

    Handle(BRepCheck_Result) aChkWr = anAnlz.Result(anExp.Current());
    BRepCheck_ListIteratorOfListOfStatus anItl(aChkWr->Status());
    for (;anItl.More(); anItl.Next()) {

      if(anItl.Value() == BRepCheck_NoError || 
	 anItl.Value() == BRepCheck_BadOrientationOfSubshape) continue;

      return Standard_False;

    }

  }

  anExp.Init(TheS, TopAbs_EDGE, TopAbs_WIRE);
  for(; anExp.More(); anExp.Next()) {

    BRepCheck_Analyzer anAnlz(anExp.Current(), GeomControls);

    if(anAnlz.IsValid()) continue;
    else return Standard_False;

  }

  return Standard_True;
}

Standard_Boolean QANewModTopOpe::IsManifold(const TopoDS_Shape& TheS)
{

  Standard_Boolean aRes = Standard_False;

  if(TheS.IsNull()) return aRes;

  TopAbs_ShapeEnum aType = TheS.ShapeType();
  
  switch (aType) {

  case TopAbs_COMPOUND :
    {
      TopoDS_Iterator anIter(TheS);
      if(!anIter.More()) return aRes;
      const TopoDS_Shape& aS = anIter.Value();
      anIter.Next();
      if(anIter.More()) aRes = IsCompoundManifold(TopoDS::Compound(TheS));
      else aRes = IsManifold(aS);
    }
    break;
  case TopAbs_COMPSOLID :
    aRes = Standard_False;
    break;
  case TopAbs_SOLID :
    {
      aRes = NoInternalVertices(TheS);
    }
    break;
  case TopAbs_SHELL :
    {
      aRes = NoInternalVertices(TheS);
      if(aRes) aRes = CorrectOrientation(TopoDS::Shell(TheS));
    }
    break;
  case TopAbs_FACE :
    {
      aRes = NoInternalVertices(TheS);
    }
    break;
  case TopAbs_WIRE :
    {
      aRes = NoInternalVertices(TheS);
    }
    break;
  case TopAbs_EDGE :
    aRes = NoInternalVertices(TheS);
    break;
  case TopAbs_VERTEX :
    aRes = Standard_True;
    break;
  case TopAbs_SHAPE :
  default :
    ;
  }
      

  return aRes;

}

static Standard_Boolean NoInternalVertices(const TopoDS_Shape& TheS)
{

  TopAbs_Orientation anOrnt;
  TopExp_Explorer anExp(TheS, TopAbs_VERTEX);
  for(; anExp.More(); anExp.Next()) {

    anOrnt = anExp.Current().Orientation();

    if(anOrnt == TopAbs_FORWARD) continue; 
    if(anOrnt == TopAbs_REVERSED) continue;

    return Standard_False;

  }
    
  return Standard_True;

}

static Standard_Boolean CorrectOrientation(const TopoDS_Shell& TheS)
{

  TopoDS_Iterator anIter(TheS);

  if(!anIter.More()) return Standard_False; //Empty shell;
  anIter.Next();
  if(!anIter.More()) return Standard_True; // only one face


  TopTools_IndexedDataMapOfShapeListOfShape aMapEdgeFace;
  TopExp::MapShapesAndAncestors(TheS, TopAbs_EDGE, TopAbs_FACE, aMapEdgeFace);

  Standard_Integer i, nbEdgs = aMapEdgeFace.Extent();
  TopExp_Explorer anExp;
  TopAbs_Orientation anOrnt;

  for(i = 1; i <= nbEdgs; i++) {

    const TopTools_ListOfShape& aL = aMapEdgeFace(i);

    if(aL.Extent() > 2) return Standard_False;
    if(aL.Extent() == 1) continue;

    const TopoDS_Shape& anE = aMapEdgeFace.FindKey(i);
    
    anExp.Init(aL.First(), TopAbs_EDGE);
    for(; anExp.More(); anExp.Next()) {
      if(anE.IsSame(anExp.Current())) {
	anOrnt = anExp.Current().Orientation();
	break;
      }
    }

    anExp.Init(aL.Last(), TopAbs_EDGE);
    for(; anExp.More(); anExp.Next()) {
      if(anE.IsSame(anExp.Current())) {
	if(anOrnt == anExp.Current().Orientation()) return Standard_False;
	break;
      }
    }

  }
    
  return Standard_True;

}

Standard_Boolean QANewModTopOpe::IsCompoundManifold(const TopoDS_Compound& TheS)
{
  Standard_Boolean aRes = Standard_True;

  TopExp_Explorer anExp;

  anExp.Init(TheS, TopAbs_COMPSOLID);
  if(anExp.More()) {

    aRes = Standard_False;
    return aRes;

  }

  TopTools_ListOfShape aList;
  TopExp_Explorer anExp1;
  TopTools_DataMapOfShapeInteger aMap;
  Standard_Integer n = 0, connect;

  anExp.Init(TheS, TopAbs_SOLID);
  for(; anExp.More(); anExp.Next()) {
    aRes = IsManifold(anExp.Current());
    if(!aRes) return aRes;
    ++n;
    anExp1.Init(anExp.Current(), TopAbs_FACE);
    for(; anExp1.More(); anExp1.Next()) {
      if(aMap.IsBound(anExp1.Current())) {
	connect = aMap(anExp1.Current());
	if(n != connect) {
	  aRes = Standard_False;
	  return aRes;
	}
      }
      else {
	aMap.Bind(anExp1.Current(), n);
      }
    }

    anExp1.Init(anExp.Current(), TopAbs_EDGE);
    for(; anExp1.More(); anExp1.Next()) {
      if(aMap.IsBound(anExp1.Current())) {
	connect = aMap(anExp1.Current());
	if(n != connect) {
	  aRes = Standard_False;
	  return aRes;
	}
      }
      else {
	aMap.Bind(anExp1.Current(), n);
      }
    }

    anExp1.Init(anExp.Current(), TopAbs_VERTEX);
    for(; anExp1.More(); anExp1.Next()) {
      if(aMap.IsBound(anExp1.Current())) {
	connect = aMap(anExp1.Current());
	if(n != connect) {
	  aRes = Standard_False;
	  return aRes;
	}
      }
      else {
	aMap.Bind(anExp1.Current(), n);
      }
    }
  }

  anExp.Init(TheS, TopAbs_SHELL, TopAbs_SOLID);
  for(; anExp.More(); anExp.Next()) {
    aRes = IsManifold(anExp.Current());
    if(!aRes) return aRes;
    ++n;
    anExp1.Init(anExp.Current(), TopAbs_FACE);
    for(; anExp1.More(); anExp1.Next()) {
      if(aMap.IsBound(anExp1.Current())) {
	connect = aMap(anExp1.Current());
	if(n != connect) {
	  aRes = Standard_False;
	  return aRes;
	}
      }
      else {
	aMap.Bind(anExp1.Current(), n);
      }
    }

    anExp1.Init(anExp.Current(), TopAbs_EDGE);
    for(; anExp1.More(); anExp1.Next()) {
      if(aMap.IsBound(anExp1.Current())) {
	connect = aMap(anExp1.Current());
	if(n != connect) {
	  aRes = Standard_False;
	  return aRes;
	}
      }
      else {
	aMap.Bind(anExp1.Current(), n);
      }
    }

    anExp1.Init(anExp.Current(), TopAbs_VERTEX);
    for(; anExp1.More(); anExp1.Next()) {
      if(aMap.IsBound(anExp1.Current())) {
	connect = aMap(anExp1.Current());
	if(n != connect) {
	  aRes = Standard_False;
	  return aRes;
	}
      }
      else {
	aMap.Bind(anExp1.Current(), n);
      }
    }
  }

  anExp.Init(TheS, TopAbs_FACE, TopAbs_SHELL);
  for(; anExp.More(); anExp.Next()) {
    aRes = IsManifold(anExp.Current());
    if(!aRes) return aRes;
    ++n;

    anExp1.Init(anExp.Current(), TopAbs_EDGE);
    for(; anExp1.More(); anExp1.Next()) {
      if(aMap.IsBound(anExp1.Current())) {
	connect = aMap(anExp1.Current());
	if(n != connect) {
	  aRes = Standard_False;
	  return aRes;
	}
      }
      else {
	aMap.Bind(anExp1.Current(), n);
      }
    }

    anExp1.Init(anExp.Current(), TopAbs_VERTEX);
    for(; anExp1.More(); anExp1.Next()) {
      if(aMap.IsBound(anExp1.Current())) {
	connect = aMap(anExp1.Current());
	if(n != connect) {
	  aRes = Standard_False;
	  return aRes;
	}
      }
      else {
	aMap.Bind(anExp1.Current(), n);
      }
    }
  }

  anExp.Init(TheS, TopAbs_WIRE, TopAbs_FACE);
  for(; anExp.More(); anExp.Next()) {
    aRes = IsManifold(anExp.Current());
    if(!aRes) return aRes;
    ++n;

    anExp1.Init(anExp.Current(), TopAbs_EDGE);
    for(; anExp1.More(); anExp1.Next()) {
      if(aMap.IsBound(anExp1.Current())) {
	connect = aMap(anExp1.Current());
	if(n != connect) {
	  aRes = Standard_False;
	  return aRes;
	}
      }
      else {
	aMap.Bind(anExp1.Current(), n);
      }
    }

    anExp1.Init(anExp.Current(), TopAbs_VERTEX);
    for(; anExp1.More(); anExp1.Next()) {
      if(aMap.IsBound(anExp1.Current())) {
	connect = aMap(anExp1.Current());
	if(n != connect) {
	  aRes = Standard_False;
	  return aRes;
	}
      }
      else {
	aMap.Bind(anExp1.Current(), n);
      }
    }
  }

  anExp.Init(TheS, TopAbs_EDGE, TopAbs_WIRE);
  for(; anExp.More(); anExp.Next()) {
    aRes = IsManifold(anExp.Current());
    if(!aRes) return aRes;
    ++n;

    anExp1.Init(anExp.Current(), TopAbs_VERTEX);
    for(; anExp1.More(); anExp1.Next()) {
      if(aMap.IsBound(anExp1.Current())) {
	connect = aMap(anExp1.Current());
	if(n != connect) {
	  aRes = Standard_False;
	  return aRes;
	}
      }
      else {
	aMap.Bind(anExp1.Current(), n);
      }
    }
  }

  anExp.Init(TheS, TopAbs_VERTEX, TopAbs_EDGE);
  for(; anExp.More(); anExp.Next()) {
    ++n;

    if(aMap.IsBound(anExp.Current())) {
      connect = aMap(anExp.Current());
      if(n != connect) {
	aRes = Standard_False;
	return aRes;
      }
    }
    else {
      aMap.Bind(anExp.Current(), n);
    }
  }

  return aRes;
}


TopAbs_ShapeEnum  QANewModTopOpe::TypeOfShape(const TopoDS_Shape& TheS)
{
  if(TheS.ShapeType() != TopAbs_COMPOUND) return TheS.ShapeType();

  TopAbs_ShapeEnum aType = TopAbs_COMPOUND;

  TopoDS_Iterator anIter(TheS);

  if(!anIter.More()) return aType;

  aType = TypeOfShape(anIter.Value());

  if(aType == TopAbs_COMPOUND) return aType;

  anIter.Next();

  for(; anIter.More(); anIter.Next()) {

    if(TypeOfShape(anIter.Value()) != aType) return TopAbs_COMPOUND;

  }

  return aType;
  
}


Standard_Boolean QANewModTopOpe::IsConnected(const TopoDS_Shape& TheS)
{
  cout << "QANewModTopOpe::IsConnected BEGIN" << endl;
  Standard_Boolean aRes = Standard_True;

  if(TheS.IsNull()) return aRes;

  TopAbs_ShapeEnum aType = TheS.ShapeType();

  if(aType != TopAbs_COMPOUND) return aRes;
      
  TopTools_ListOfShape aCompList;
  TopTools_DataMapOfShapeInteger aMap;
  TopTools_MapOfShape aSMap;
  TopoDS_Iterator anTDIter;
  TopExp_Explorer anExp;

  anTDIter.Initialize(TheS);
  for(; anTDIter.More(); anTDIter.Next()) {
    if(anTDIter.Value().ShapeType() == TopAbs_COMPOUND) aCompList.Append(anTDIter.Value());
    else aSMap.Add(anTDIter.Value());
  }

  TopTools_ListIteratorOfListOfShape anIter(aCompList);
  for(;anIter.More(); anIter.Next()) {
    anTDIter.Initialize(anIter.Value());
    for(; anTDIter.More(); anTDIter.Next()) {
      if(anTDIter.Value().ShapeType() == TopAbs_COMPOUND) aCompList.Append(anTDIter.Value());
      else aSMap.Add(anTDIter.Value());
    }
  }
  //cout << "QANewModTopOpe::IsConnected(2)" << endl;
   

  Standard_Integer nbs = aSMap.Extent();
  if(nbs <= 1) return aRes;

  math_Matrix aMat(1, nbs, 1, nbs, 0);
  Standard_Integer aMax=nbs*nbs;

  TopTools_MapIteratorOfMapOfShape anMIter(aSMap);
  Standard_Integer n = 1;
  Standard_Integer connect;
  const TopoDS_Shape& aFirstShape = anMIter.Key();

  aMat(n,n) = 1;

  anExp.Init(aFirstShape, TopAbs_VERTEX);
  for(; anExp.More(); anExp.Next()) {
    aMap.Bind(anExp.Current(), n);
  }

  anMIter.Next();

  for(; anMIter.More(); anMIter.Next()) {
    ++n;
    aMat(n,n) = 1;

    const TopoDS_Shape& aShape = anMIter.Key();

    anExp.Init(aShape, TopAbs_VERTEX);
    for(; anExp.More(); anExp.Next()) {
      if(aMap.IsBound(anExp.Current()))
      {
        connect = aMap(anExp.Current());
        aMat(n, connect) = 1;
        aMat(connect, n) = 1;
      }
      else
      {
        aMap.Bind(anExp.Current(), n);
      }
    }
  }
  //cout << "QANewModTopOpe::IsConnected(3)Lnbs=" <<nbs<< endl;

  Standard_Integer k,i,ncount=0;
  Standard_Real p; 
  Standard_Boolean aNotChanged;

  for (k = 1; k <= nbs; k++)
  {
    aRes = Standard_True;
    aNotChanged = Standard_True;
    for (n = 1; n <= nbs; n++)
    {
      if (aMat(1, n) == 0)
      {
        p = 0;
        for (i = 1; i <= nbs; i++)
        {
          if (aMat(1, i) == 1 && aMat(i, n) == 1)
          {
            p = 1;
            break;
          }
        }
        if (p > 0)
        {
          aMat(1, n) = 1;
          aMat(n, 1) = 1;
          aNotChanged = Standard_False;
        }
        aRes = Standard_False;
      }
    }
    if(aNotChanged) break;
    if(aRes) break;
  }

  cout << "QANewModTopOpe::IsConnected END: aRes="<<aRes <<endl;
  return aRes;

}
