// Created on: 2009-05-05
// Created by: Sergey ZARITCHNY
// Copyright (c) 2009-2012 OPEN CASCADE SAS
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



#include <DNaming_BooleanOperationDriver.ixx>
#include <TFunction_Function.hxx>
#include <TDataStd_Real.hxx>
#include <TDataStd_Integer.hxx>
#include <TFunction_Logbook.hxx>
#include <TNaming.hxx>
#include <TNaming_NamedShape.hxx>
#include <BRepCheck_Analyzer.hxx>
#include <TopLoc_Location.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Vertex.hxx>
#include <Standard_GUID.hxx>
#include <Standard_Real.hxx>
#include <TDF_Label.hxx>
#include <ModelDefinitions.hxx>

#include <DNaming.hxx>
#include <TNaming_Builder.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopTools_MapOfShape.hxx>
#include <TopExp_Explorer.hxx>
#include <TopExp.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <BRepLib.hxx>
#include <Precision.hxx>
#include <BRepCheck_ListIteratorOfListOfStatus.hxx>
#include <BRepCheck_Result.hxx>
#include <BRepCheck_ListOfStatus.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <Adaptor3d_HCurve.hxx>
#include <GeomAbs_SurfaceType.hxx>

static Standard_Boolean FixSameParameter(const TopoDS_Shape&    theShape,
					     BRepCheck_Analyzer&    theAnalyzer,
					     const Standard_Boolean bIgnoreNotSPErrors = Standard_False );
static void FindSPErrorEdges(const TopoDS_Shape&         theShape,
			     const BRepCheck_Analyzer&   theAnalyzer,
			     TopTools_IndexedMapOfShape& theMap);

static Standard_Boolean FindOtherErrors(const TopoDS_Shape&               theShape,
					const BRepCheck_Analyzer&         theAnalyzer,
					const TopTools_IndexedMapOfShape& theMap);

//=======================================================================
//function : DNaming_BooleanOperationDriver
//purpose  : Constructor
//=======================================================================
DNaming_BooleanOperationDriver::DNaming_BooleanOperationDriver()
{}

//=======================================================================
//function : Validate
//purpose  : Validates labels of a function in <log>.
//=======================================================================
void DNaming_BooleanOperationDriver::Validate(TFunction_Logbook& theLog) const
{}

//=======================================================================
//function : MustExecute
//purpose  : Analyse in <log> if the loaded function must be executed
//=======================================================================
Standard_Boolean DNaming_BooleanOperationDriver::MustExecute(const TFunction_Logbook& theLog) const
{
  return Standard_True;
}

//=======================================================================
//function : Execute
//purpose  : Execute the function and push in <log> the impacted labels
//=======================================================================
Standard_Integer DNaming_BooleanOperationDriver::Execute(TFunction_Logbook& theLog) const
{
  Handle(TFunction_Function) aFunction;
  Label().FindAttribute(TFunction_Function::GetID(),aFunction);
  if(aFunction.IsNull()) return -1;

//  Handle(TDataStd_UAttribute) anObject = DNaming::GetObjectFromFunction(aFunction);
//  if(anObject.IsNull()) return -1;
//  Handle(TNaming_NamedShape) anObjectNS = DNaming::GetObjectValue(anObject);
  Handle(TFunction_Function) aPrevFun = DNaming::GetPrevFunction(aFunction);
  if(aPrevFun.IsNull()) return -1;
  const TDF_Label& aLab = RESPOSITION(aPrevFun);
  Handle(TNaming_NamedShape) anObjectNS;
  aLab.FindAttribute(TNaming_NamedShape::GetID(), anObjectNS);
  if (anObjectNS.IsNull() || anObjectNS->IsEmpty()) {
#ifdef DEB
    cout<<"BooleanOperationDriver:: Object is empty"<<endl;
#endif
    aFunction->SetFailure(WRONG_ARGUMENT);
    return -1;
  }

  Handle(TDataStd_UAttribute) aToolObj = DNaming::GetObjectArg(aFunction,BOOL_TOOL);
  Handle(TNaming_NamedShape) aToolNS = DNaming::GetObjectValue(aToolObj);

  if (aToolNS.IsNull() || aToolNS->IsEmpty()) {
#ifdef DEB
    cout<<"BooleanOperationDriver:: Tool is empty"<<endl;
#endif
    aFunction->SetFailure(WRONG_ARGUMENT);
    return -1;
  }

  TopoDS_Shape aTOOL = aToolNS->Get();
  TopoDS_Shape anOBJECT = anObjectNS->Get();
  if (aTOOL.IsNull() || anOBJECT.IsNull()) {
#ifdef DEB
    cout<<"BooleanOperationDriver:: Tool is null"<<endl;
#endif
    aFunction->SetFailure(WRONG_ARGUMENT);
    return -1;
  }

  Standard_Boolean anIsDone = Standard_False;

  //case FUSE 
  if(aFunction->GetDriverGUID() == FUSE_GUID){
    BRepAlgoAPI_Fuse aMkFuse (anOBJECT, aTOOL);
    anIsDone = CheckAndLoad(aMkFuse, aFunction);
  }
  //case CUT
  else if(aFunction->GetDriverGUID() == CUT_GUID){
    BRepAlgoAPI_Cut aMkCut (anOBJECT, aTOOL);    
    anIsDone = CheckAndLoad(aMkCut, aFunction);
  } 
  // case COMMON
  else if(aFunction->GetDriverGUID() == COMMON_GUID){
    BRepAlgoAPI_Common aMkCom (anOBJECT, aTOOL);    
    anIsDone = CheckAndLoad(aMkCom, aFunction);
  }
  else {
    aFunction->SetFailure(UNSUPPORTED_FUNCTION);
    return -1;
  }
  if(!anIsDone) return -1;
  else {
    theLog.SetValid(RESPOSITION(aFunction),Standard_True);  
    aFunction->SetFailure(DONE);
    return 0;
  }

}
//===================================================================
//=======================================================================
//function : ShapeType
//purpose  :
//=======================================================================

static TopAbs_ShapeEnum ShapeType(const TopoDS_Shape& theShape) {
  TopAbs_ShapeEnum TypeSh = theShape.ShapeType();
  if (TypeSh == TopAbs_COMPOUND || TypeSh == TopAbs_COMPSOLID) {
    TopoDS_Iterator itr(theShape);
    if (!itr.More()) return TypeSh;
    TypeSh = ShapeType(itr.Value());
    if(TypeSh == TopAbs_COMPOUND) return TypeSh;
    itr.Next();
    for(; itr.More(); itr.Next())
      if(ShapeType(itr.Value()) != TypeSh) return TopAbs_COMPOUND;
  }
  return TypeSh;
}
//=====================================================================
static Standard_Boolean IsValidSurfType(const TopoDS_Face& theFace) {
  BRepAdaptor_Surface anAdapt(theFace);
  Handle( Adaptor3d_HCurve ) aBasisCurve;
  const GeomAbs_SurfaceType& aType = anAdapt.GetType();
  if(aType == GeomAbs_Sphere)
    return Standard_True;
/*  if(aType == GeomAbs_Cylinder || aType == GeomAbs_Cone || Type == GeomAbs_Sphere)
    return Standard_True;
  else if(aType == GeomAbs_SurfaceOfRevolution){
    aBasisCurve = anAdapt.BasisCurve();
    if (aBasisCurve->GetType() == GeomAbs_Line)
      return Standard_True;
  }
  else if(aType == GeomAbs_SurfaceOfExtrusion) {
    aBasisCurve = anAdapt.BasisCurve();
    if (aBasisCurve->GetType() == GeomAbs_Circle || aBasisCurve->GetType() == GeomAbs_Ellipse)
      return Standard_True;
  }
*/
#ifdef DEB
  //ModDbgTools_Write(theFace, "Surf");
#endif
  return Standard_False;
}
//=======================================================================
//function : IsWRCase
//purpose  :
//=======================================================================

static Standard_Boolean IsWRCase(const BRepAlgoAPI_BooleanOperation& MS) {

  const TopoDS_Shape& ObjSh = MS.Shape1();
  const TopoDS_Shape& ToolSh = MS.Shape2();
  const TopAbs_ShapeEnum& Type1 = ShapeType(ObjSh);
  if(Type1  == TopAbs_COMPOUND || Type1 > TopAbs_FACE) return Standard_False;
  const TopAbs_ShapeEnum& Type2 = ShapeType(ToolSh);
  if(Type2  == TopAbs_COMPOUND || Type2 > TopAbs_FACE) return Standard_False;
  TopTools_ListOfShape aList;

  if(Type1 != TopAbs_FACE) {
    TopExp_Explorer anExp(ObjSh, TopAbs_FACE);
    for(;anExp.More();anExp.Next()) {
      if(IsValidSurfType(TopoDS::Face(anExp.Current())))
        aList.Append(anExp.Current());
    }
  } else
       if(IsValidSurfType(TopoDS::Face(ObjSh)))
        aList.Append(ObjSh);

  if(aList.Extent() == 0) {
    if(Type2 != TopAbs_FACE) {
      TopExp_Explorer anExp(ToolSh, TopAbs_FACE);
      for(;anExp.More();anExp.Next()) {
        if(IsValidSurfType(TopoDS::Face(anExp.Current())))
          aList.Append(anExp.Current());
      }
    } else
      if(IsValidSurfType(TopoDS::Face(ToolSh)))
        aList.Append(ToolSh);
  }
  if(aList.Extent() > 0) return Standard_True;
  return Standard_False;
}

//=======================================================================
//function : LoadNamingDS
//purpose  : 
//=======================================================================
void DNaming_BooleanOperationDriver::LoadNamingDS (const TDF_Label& theResultLabel, 
					   BRepAlgoAPI_BooleanOperation& MS) const
{

  const TopoDS_Shape& ResSh = MS.Shape();
  const TopoDS_Shape& ObjSh = MS.Shape1();
  const TopoDS_Shape& ToolSh = MS.Shape2();
 if (ResSh.IsNull()) {
#ifdef DEB
   cout<<"LoadFuseNamingDS: The result of the boolean operation is null"<<endl;
#endif
    return;
  }

  // LoadResult
  DNaming::LoadResult(theResultLabel, MS);

  TopTools_DataMapOfShapeShape SubShapes;
  TopExp_Explorer Exp(ResSh, TopAbs_FACE);
  for (; Exp.More(); Exp.Next()) {
    SubShapes.Bind(Exp.Current(),Exp.Current());
  }

 // Naming of modified faces: 
  TNaming_Builder modFB (theResultLabel.NewChild()); //FindChild(1,Standard_True)); 
  DNaming::LoadAndOrientModifiedShapes (MS, ObjSh,  TopAbs_FACE, modFB,SubShapes);  
  DNaming::LoadAndOrientModifiedShapes (MS, ToolSh, TopAbs_FACE, modFB, SubShapes);

  // Naming of deleted faces:
  if(MS.HasDeleted()){
    TNaming_Builder delB (theResultLabel.NewChild());  // FindChild(2,Standard_True)); 
    DNaming::LoadDeletedShapes  (MS, ObjSh,  TopAbs_FACE, delB);
    DNaming::LoadDeletedShapes  (MS, ToolSh, TopAbs_FACE, delB);
  }

  if(IsWRCase(MS)) {
  // Edges 
    Exp.Init(ResSh, TopAbs_EDGE);
    for (; Exp.More(); Exp.Next()) {
      SubShapes.Bind(Exp.Current(),Exp.Current());
    }
  
    const TopTools_ListOfShape& aList = MS.SectionEdges();
    Standard_Boolean theCase(Standard_False);
    TopTools_MapOfShape aView;
    if(aList.Extent() > 0 && aList.Extent() < 3) 
      theCase = Standard_True;
    
    TopTools_ListIteratorOfListOfShape it(aList);
    for(;it.More();it.Next()) {
      TopoDS_Shape newShape = it.Value();
      if (SubShapes.IsBound(newShape)) 
	newShape.Orientation((SubShapes(newShape)).Orientation());
      TNaming_Builder secED (theResultLabel.NewChild());
      secED.Generated(newShape);
      if(theCase) {
	TopoDS_Vertex Vfirst, Vlast;
	TopExp::Vertices(TopoDS::Edge(newShape), Vfirst, Vlast, Standard_True);
	if(aView.Add(Vfirst)) {
	  TNaming_Builder secV (theResultLabel.NewChild());
	  secV.Generated(Vfirst);
	}
	if(aView.Add(Vlast)) {
	  TNaming_Builder secV (theResultLabel.NewChild());
	  secV.Generated(Vlast);
	}
      }
    }
  }
}

//=======================================================================
//function : CheckAndLoad
//purpose  : checks result of operation and performs Topological Naming
//=======================================================================
Standard_Boolean DNaming_BooleanOperationDriver::CheckAndLoad
  (BRepAlgoAPI_BooleanOperation& theMkOpe, 
   const Handle(TFunction_Function)& theFunction) const
{

  if (theMkOpe.IsDone() && !theMkOpe.Shape().IsNull()) {
#ifdef MDTV_DEB   
    Standard_CString aFileName = "BoolOp.brep";
    Write(theMkOpe.Shape(), aFileName);
#endif
    if (theMkOpe.Shape().ShapeType() == TopAbs_COMPOUND) {
      TopoDS_Iterator anItr(theMkOpe.Shape());
      if(!anItr.More()) {
	theFunction->SetFailure(NULL_RESULT);
	return Standard_False;
      }      
    }
    BRepCheck_Analyzer aCheck (theMkOpe.Shape());
    Standard_Boolean aResIsValid = Standard_True;
    if(!aCheck.IsValid(theMkOpe.Shape())) 
      aResIsValid = FixSameParameter(theMkOpe.Shape(), aCheck);
    if (aResIsValid) {
      if(theFunction->GetDriverGUID() == FUSE_GUID) {
	LoadNamingDS(RESPOSITION(theFunction), theMkOpe);
      }
      else if(theFunction->GetDriverGUID() == CUT_GUID) {
	LoadNamingDS(RESPOSITION(theFunction), theMkOpe); // the same naming only for case of solids
      } else if(theFunction->GetDriverGUID() == COMMON_GUID) {
	LoadNamingDS(RESPOSITION(theFunction), theMkOpe); 
      }
      
      theFunction->SetFailure(DONE);
      return Standard_True;
    } else {
      theFunction->SetFailure(RESULT_NOT_VALID);
      return Standard_False;
    }
  }
  theFunction->SetFailure(ALGO_FAILED);
  return Standard_False;
}

// ------------------------------------------------------------------------
// static function: FixSameParameter
// purpose:
// ------------------------------------------------------------------------
Standard_Boolean FixSameParameter(const TopoDS_Shape&    theShape,
				      BRepCheck_Analyzer&    theAnalyzer,
				      const Standard_Boolean bIgnoreNotSPErrors) {

  Standard_Integer bDoFix = Standard_True;
  TopTools_IndexedMapOfShape aMapE;

  FindSPErrorEdges(theShape, theAnalyzer, aMapE);

  if(!bIgnoreNotSPErrors) {
    if(FindOtherErrors(theShape, theAnalyzer, aMapE)) {
      bDoFix = Standard_False;
    }
  }

  if(bDoFix) {
    Standard_Integer i = 0;

    for(i = 1; i <= aMapE.Extent(); i++) {
      const TopoDS_Shape& aE = aMapE(i);
      BRepLib::SameParameter(aE, Precision::Confusion(), Standard_True);
    }

    if(!aMapE.IsEmpty()) {
      theAnalyzer.Init(theShape);
      return theAnalyzer.IsValid();
    }
  }
  return Standard_False;
}

// ------------------------------------------------------------------------
// static function: FindSPErrorEdges
// purpose:
// ------------------------------------------------------------------------
void FindSPErrorEdges(const TopoDS_Shape&         theShape,
		      const BRepCheck_Analyzer&   theAnalyzer,
		      TopTools_IndexedMapOfShape& theMap) {
  BRepCheck_ListIteratorOfListOfStatus itl;

  TopoDS_Iterator anIt(theShape);

  for (; anIt.More(); anIt.Next()) {
    FindSPErrorEdges(anIt.Value(), theAnalyzer, theMap);
  }

  if(theShape.ShapeType() == TopAbs_FACE) {
    TopExp_Explorer anExpE(theShape, TopAbs_EDGE);
    
    for(; anExpE.More(); anExpE.Next()) {
      Handle(BRepCheck_Result) aResult = theAnalyzer.Result(anExpE.Current());

      if(aResult.IsNull() || theMap.Contains(anExpE.Current()))
	continue;

      for (aResult->InitContextIterator();
	   aResult->MoreShapeInContext(); 
	   aResult->NextShapeInContext()) {
	if (aResult->ContextualShape().IsSame(theShape)) {
	  itl.Initialize(aResult->StatusOnShape());

	  for(; itl.More(); itl.Next()) {
	    if((itl.Value() == BRepCheck_InvalidSameParameterFlag) ||
	       (itl.Value() == BRepCheck_InvalidCurveOnSurface)) {
	      theMap.Add(anExpE.Current());
	      break;
	    }
	  }
	}
      }
    }
  }
  else if(theShape.ShapeType() == TopAbs_EDGE) {
    Handle(BRepCheck_Result) aResult = theAnalyzer.Result(theShape);
    itl.Initialize(aResult->Status());
    
    for(; itl.More(); itl.Next()) {
      if((itl.Value() == BRepCheck_InvalidSameParameterFlag) ||
	 (itl.Value() == BRepCheck_InvalidCurveOnSurface)) {
	theMap.Add(theShape);
	break;
      }
    }
  }
}

// ------------------------------------------------------------------------
// static function: FindOtherErrors
// purpose:
// ------------------------------------------------------------------------
Standard_Boolean FindOtherErrors(const TopoDS_Shape&               theShape,
				 const BRepCheck_Analyzer&         theAnalyzer,
				 const TopTools_IndexedMapOfShape& theMap) {

  Standard_Boolean bOtherFound = Standard_False;
  BRepCheck_ListIteratorOfListOfStatus itl;
  TopoDS_Iterator anIt(theShape);
  
  for (; anIt.More(); anIt.Next()) {
    if(FindOtherErrors(anIt.Value(), theAnalyzer, theMap))
      return Standard_True;
  }
  Handle(BRepCheck_Result) aResult = theAnalyzer.Result(theShape);
  
  if (!aResult.IsNull()) {

    if(!theMap.Contains(theShape) && !aResult->Status().IsEmpty()) {
      if(aResult->Status().First() != BRepCheck_NoError) {
	bOtherFound = Standard_True;

	//
	TopExp_Explorer anExpF(theShape, TopAbs_FACE);

	for(; anExpF.More(); anExpF.Next()) {
	  TopExp_Explorer anExpE(anExpF.Current(), TopAbs_EDGE);

	  for(; anExpE.More(); anExpE.Next()) {
	    Handle(BRepCheck_Result) aResultE = theAnalyzer.Result(anExpE.Current());

	    if(aResultE.IsNull())
	      continue;
	    bOtherFound = Standard_False;

	    for (aResultE->InitContextIterator();
		 aResultE->MoreShapeInContext(); 
		 aResultE->NextShapeInContext()) {

	      if (aResultE->ContextualShape().IsSame(anExpF.Current()) ||
		  aResultE->ContextualShape().IsSame(theShape)) {
		itl.Initialize(aResultE->StatusOnShape());

		if(!itl.More())
		  continue;

		if(itl.Value() != BRepCheck_NoError) {
		  if(theMap.Contains(anExpE.Current())) {
		    for(; itl.More(); itl.Next()) {

		      if((itl.Value() != BRepCheck_InvalidSameParameterFlag) &&
			 (itl.Value() != BRepCheck_InvalidCurveOnSurface) &&
			 (itl.Value() != BRepCheck_NoError)) {
			return Standard_True;
		      }
		    }
		  }
		  else {
		    return Standard_True;
		  }
		}
	      }
	    }
	  }
	}
	// 

	if(!bOtherFound) {
	  for (aResult->InitContextIterator(); 
	       !bOtherFound && aResult->MoreShapeInContext(); 
	       aResult->NextShapeInContext()) {
	    if(!aResult->StatusOnShape().IsEmpty()) {
	      bOtherFound = (aResult->StatusOnShape().First() != BRepCheck_NoError);
	    }
	  }
	}
      }
      else {
	TopAbs_ShapeEnum aType = theShape.ShapeType();

	if((aType == TopAbs_VERTEX) ||
	   (aType == TopAbs_EDGE) ||
	   (aType == TopAbs_WIRE) ||
	   (aType == TopAbs_FACE) ||
	   (aType == TopAbs_SHELL)) {
	  for (aResult->InitContextIterator();
	       aResult->MoreShapeInContext(); 
	       aResult->NextShapeInContext()) {
	    if(!aResult->StatusOnShape().IsEmpty()) {
	      if(aResult->StatusOnShape().First() != BRepCheck_NoError) {
		return Standard_True;
	      }
	    }
	  }
	}
      }
    }
    else {
      itl.Initialize(aResult->Status());
      
      for(; itl.More(); itl.Next()) {
	if((itl.Value() != BRepCheck_InvalidSameParameterFlag) &&
	   (itl.Value() != BRepCheck_InvalidCurveOnSurface) &&
	   (itl.Value() != BRepCheck_NoError)) {
	  return Standard_True;
	}
      }
    }
  }
  
  return bOtherFound;
}
