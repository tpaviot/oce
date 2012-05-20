// Created on: 2009-05-07
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


#include <DNaming_TransformationDriver.ixx>
#include <Standard_NullObject.hxx>
#include <TopAbs.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <BRep_Builder.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRep_Tool.hxx>
#include <BRepBuilderAPI_MakeShape.hxx>
#include <TopTools_MapOfShape.hxx>
#include <TopTools_DataMapOfShapeShape.hxx>
#include <TopTools_MapIteratorOfMapOfShape.hxx>
#include <TopTools_DataMapIteratorOfDataMapOfShapeShape.hxx>
#include <TopTools_DataMapOfShapeInteger.hxx>
#include <TopTools_DataMapIteratorOfDataMapOfShapeInteger.hxx>
#include <TNaming_Builder.hxx>
#include <TNaming_NamedShape.hxx>
#include <TNaming_Tool.hxx>
#include <TFunction_Function.hxx>
#include <TFunction_Logbook.hxx>
#include <DNaming.hxx>
#include <TDataStd_Real.hxx>
#include <gp_Vec.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <gp_Pln.hxx>
#include <GeomLib_IsPlanarSurface.hxx>


#include <ModelDefinitions.hxx>

#ifdef WNT
#define EXCEPTION ...
#else
#define EXCEPTION Standard_Failure
#endif 

#define FACES_TAG  1
#define EDGES_TAG  2
#define VERTEX_TAG 3

//#define MDTV_DEB_TRSF
#ifdef  MDTV_DEB_TRSF
#include <TCollection_AsciiString.hxx>
#include <BRepTools.hxx>
#include <TDF_Tool.hxx>
void PrintE(const TDF_Label&       label)
{
  TCollection_AsciiString entry;
  TDF_Tool::Entry(label, entry);
  cout << "LabelEntry = "<< entry << endl;
}
#endif
//=======================================================================
//function : TransformationDriver
//purpose  : Constructor
//=======================================================================
DNaming_TransformationDriver::DNaming_TransformationDriver()
{}

//=======================================================================
//function : Validate
//purpose  : Validates labels of a function in <log>.
//=======================================================================
void DNaming_TransformationDriver::Validate(TFunction_Logbook& theLog) const
{}

//=======================================================================
//function : MustExecute
//purpose  : Analyse in <log> if the loaded function must be executed
//=======================================================================
Standard_Boolean DNaming_TransformationDriver::MustExecute(const TFunction_Logbook& theLog) const
{
  return Standard_True;
}


//=======================================================================
//function : Execute
//purpose  : Execute the function and push in <log> the impacted labels
//=======================================================================
Standard_Integer DNaming_TransformationDriver::Execute(TFunction_Logbook& theLog) const
{
  Handle(TFunction_Function) aFunction;
  Label().FindAttribute(TFunction_Function::GetID(),aFunction);
  if(aFunction.IsNull()) return -1;

  Handle(TFunction_Function) aPrevFun = DNaming::GetPrevFunction(aFunction);
  if(aPrevFun.IsNull()) return -1;
  const TDF_Label& aLab = RESPOSITION(aPrevFun);
  Handle(TNaming_NamedShape) aContextNS;
  aLab.FindAttribute(TNaming_NamedShape::GetID(), aContextNS);
  if (aContextNS.IsNull() || aContextNS->IsEmpty()) {
#ifdef DEB
    cout<<"TransformationDriver:: Context is empty"<<endl;
#endif
    aFunction->SetFailure(WRONG_CONTEXT);
    return -1;
  }
//
  gp_Trsf aTransformation;
  const Standard_GUID& aGUID = aFunction->GetDriverGUID();
  
  try {
    if(aGUID == PTXYZ_GUID) {
      Standard_Real aDX = DNaming::GetReal(aFunction,PTRANSF_DX)->Get();
      Standard_Real aDY = DNaming::GetReal(aFunction,PTRANSF_DY)->Get();
      Standard_Real aDZ = DNaming::GetReal(aFunction,PTRANSF_DZ)->Get();  
      gp_Vec aVector(aDX, aDY, aDZ);
      aTransformation.SetTranslation(aVector);      
    }  
    else if(aGUID == PTALINE_GUID) {
      Handle(TDataStd_UAttribute) aLineObj  = DNaming::GetObjectArg(aFunction, PTRANSF_LINE);
      Handle(TNaming_NamedShape) aLineNS = DNaming::GetObjectValue(aLineObj);
      gp_Ax1 anAxis;
      if(!DNaming::ComputeAxis(aLineNS, anAxis)) Standard_Failure::Raise();
      gp_Vec aVector(anAxis.Direction());
      aVector.Normalize();
      Standard_Real anOffset = DNaming::GetReal(aFunction,PTRANSF_OFF)->Get();
      aVector *= anOffset;
      aTransformation.SetTranslation(aVector);   

    }  else if(aGUID == PRRLINE_GUID) {
      Handle(TDataStd_UAttribute) aLineObj  = DNaming::GetObjectArg(aFunction, PTRANSF_LINE);
      Handle(TNaming_NamedShape) aLineNS = DNaming::GetObjectValue(aLineObj);
      gp_Ax1 anAxis;
      if(!DNaming::ComputeAxis(aLineNS, anAxis)) Standard_Failure::Raise();

      Standard_Real anAngle = DNaming::GetReal(aFunction,PTRANSF_ANG)->Get();
      aTransformation.SetRotation(anAxis, anAngle);
    }  else if(aGUID == PMIRR_GUID) {
      Handle(TDataStd_UAttribute) aPlaneObj  = DNaming::GetObjectArg(aFunction, PTRANSF_PLANE);
      Handle(TNaming_NamedShape) aNS = DNaming::GetObjectValue(aPlaneObj);
      
      if(aNS.IsNull() ||  aNS->IsEmpty() || aNS->Get().IsNull() || 
	 aNS->Get().ShapeType() != TopAbs_FACE) Standard_Failure::Raise();
      TopoDS_Face aFace = TopoDS::Face(aNS->Get());
      Handle(Geom_Surface) aSurf = BRep_Tool::Surface(aFace);
      GeomLib_IsPlanarSurface isPlanarSurface (aSurf);
      if(!isPlanarSurface.IsPlanar()) Standard_Failure::Raise();
      gp_Pln aPlane = isPlanarSurface.Plan();
      gp_Ax2 aMirrorAx2 = aPlane.Position().Ax2();
      aTransformation.SetMirror(aMirrorAx2);
    } else {
      aFunction->SetFailure(UNSUPPORTED_FUNCTION);
      return -1;
    }
  } catch (EXCEPTION) {
    aFunction->SetFailure(WRONG_ARGUMENT);
    return -1;
  }
//

// Naming
  LoadNamingDS(RESPOSITION(aFunction), aContextNS, aTransformation);

  theLog.SetValid(RESPOSITION(aFunction),Standard_True);  
  aFunction->SetFailure(DONE);
  return 0;
}
//=================================================================================
static void BuildMap(const TopTools_MapOfShape& SMap,
 		     BRepBuilderAPI_Transform& Transformer,
 		     TopTools_DataMapOfShapeShape& M)
{
  TopTools_MapIteratorOfMapOfShape anIt(SMap);
  for(;anIt.More();anIt.Next()) {
    if(!anIt.Key().IsNull()) {
      const TopoDS_Shape& aS = anIt.Key(); 
      M.Bind(aS,Transformer.ModifiedShape(aS));
    }
  } 
}
//=================================================================================
static void CollectShapes(const TopoDS_Shape& SSh, TopoDS_Compound& C, 
			  TopTools_MapOfShape& SMap, const TDF_Label& theLab,
			  TopTools_DataMapOfShapeInteger& TagMap, const Standard_Boolean isPrimitive)
{
  const TopAbs_ShapeEnum aType = SSh.ShapeType();
  BRep_Builder aB;
  switch(aType) {
  case TopAbs_COMPOUND:
    {
      TopoDS_Iterator it(SSh);
      for(;it.More();it.Next()) 
	CollectShapes(it.Value(), C, SMap, theLab, TagMap,isPrimitive);
    }
    break;
  case TopAbs_COMPSOLID:
  case TopAbs_SOLID:
  case TopAbs_SHELL:
    {
      TopExp_Explorer anEx(SSh, TopAbs_FACE);
      for(;anEx.More();anEx.Next()) {
	const Handle(TNaming_NamedShape) aNS =  TNaming_Tool::NamedShape(anEx.Current(), theLab);
	if(aNS.IsNull()) continue;
	if(SMap.Add(anEx.Current())) {
	  aB.Add(C,anEx.Current());
	  if(isPrimitive)
	    TagMap.Bind(anEx.Current(), aNS->Label().Tag());
	}
      }
      anEx.Init(SSh, TopAbs_EDGE); 
      for(;anEx.More();anEx.Next()) {
	const Handle(TNaming_NamedShape) aNS =  TNaming_Tool::NamedShape(anEx.Current(), theLab);
	if(aNS.IsNull()) continue;
	if(SMap.Add(anEx.Current())) {
	  aB.Add(C,anEx.Current());
	  if(isPrimitive)
	    TagMap.Bind(anEx.Current(), aNS->Label().Tag());
	}
      }
      anEx.Init(SSh, TopAbs_VERTEX); 
      for(;anEx.More();anEx.Next()) {
	const Handle(TNaming_NamedShape) aNS =  TNaming_Tool::NamedShape(anEx.Current(), theLab);
	if(aNS.IsNull()) continue;
	if(SMap.Add(anEx.Current())) {
	  aB.Add(C,anEx.Current());
	  if(isPrimitive)
	    TagMap.Bind(anEx.Current(), aNS->Label().Tag());
	}
      }
    }    
    break;
  case  TopAbs_FACE:
    {
      const Handle(TNaming_NamedShape) aNamedShape =  TNaming_Tool::NamedShape(SSh, theLab);
      if(!aNamedShape.IsNull())
	if(SMap.Add(SSh)) 
	  aB.Add(C,SSh); 
      TopExp_Explorer anEx(SSh, TopAbs_EDGE);
      for(;anEx.More();anEx.Next()) {
	const Handle(TNaming_NamedShape) aNS =  TNaming_Tool::NamedShape(anEx.Current(), theLab);
	if(aNS.IsNull()) continue;
	if(SMap.Add(anEx.Current())) {
	  aB.Add(C,anEx.Current());
	  if(isPrimitive)
	    TagMap.Bind(anEx.Current(), aNS->Label().Tag());
	}
      }
      anEx.Init(SSh, TopAbs_VERTEX); 
      for(;anEx.More();anEx.Next()) {
	const Handle(TNaming_NamedShape) aNS =  TNaming_Tool::NamedShape(anEx.Current(), theLab);
	if(aNS.IsNull()) continue;
	if(SMap.Add(anEx.Current())) {
	  aB.Add(C,anEx.Current());
	  if(isPrimitive)
	    TagMap.Bind(anEx.Current(), aNS->Label().Tag());
	}
      }
    }
    break;
  case TopAbs_WIRE:
    {      
      TopExp_Explorer anEx(SSh, TopAbs_EDGE);
      for(;anEx.More();anEx.Next()) {
	const Handle(TNaming_NamedShape) aNS =  TNaming_Tool::NamedShape(anEx.Current(), theLab);
	if(aNS.IsNull()) continue;
	if(SMap.Add(anEx.Current())) {
	  aB.Add(C,anEx.Current());
	  if(isPrimitive)
	    TagMap.Bind(anEx.Current(), aNS->Label().Tag());
	}
      }  
      anEx.Init(SSh, TopAbs_VERTEX); 
      for(;anEx.More();anEx.Next()) {
	const Handle(TNaming_NamedShape) aNS =  TNaming_Tool::NamedShape(anEx.Current(), theLab);
	if(aNS.IsNull()) continue;
	if(SMap.Add(anEx.Current())) {
	  aB.Add(C,anEx.Current()); 
	  if(isPrimitive)
	    TagMap.Bind(anEx.Current(), aNS->Label().Tag());
	}
      }     
    }
    break;
    
  case TopAbs_EDGE:
    {
      const Handle(TNaming_NamedShape) aNamedShape =  TNaming_Tool::NamedShape(SSh, theLab);
      if(!aNamedShape.IsNull())
	if(SMap.Add(SSh))
	  aB.Add(C,SSh); 
      TopExp_Explorer anEx(SSh, TopAbs_VERTEX);      
      anEx.Init(SSh, TopAbs_VERTEX); 
      for(;anEx.More();anEx.Next()) {
	const Handle(TNaming_NamedShape) aNS =  TNaming_Tool::NamedShape(anEx.Current(), theLab);
	if(aNS.IsNull()) continue;
	if(SMap.Add(anEx.Current())) {
	  aB.Add(C,anEx.Current()); 
	  if(isPrimitive)
	    TagMap.Bind(anEx.Current(), aNS->Label().Tag());
	}
      }   
    }
    break;
  case TopAbs_VERTEX:
  {
    const Handle(TNaming_NamedShape) aNS =  TNaming_Tool::NamedShape(SSh, theLab);
    if(!aNS.IsNull())
      if(SMap.Add(SSh)) {
	aB.Add(C,SSh); 
//	if(isPrimitive)
//	  TagMap.Bind(SSh, aNS->Label().Tag());
      }
  }
    break;
  default: /* Do nothing */ break;
  }   
}

//=======================================================================
//function : LoadAndName
//purpose  : 
//=======================================================================
void DNaming_TransformationDriver::LoadNamingDS (const TDF_Label& theResultLabel, 
						 const Handle(TNaming_NamedShape)& theSourceNS,
						 const gp_Trsf& theTrsf) const 
{
  TNaming_Builder aBuilder (theResultLabel);
  if(theSourceNS.IsNull() || theSourceNS->IsEmpty())
    return;
  const TopoDS_Shape& aSrcShape  = theSourceNS->Get();
  if (aSrcShape.IsNull()) {
#ifdef DEB
    cout<<"DNaming_TransformationDriver::LoadNamingDS: The result of the Transform operation is null"<<endl;
#endif
    return;
  }
  Standard_Boolean isPrimitive(Standard_False);
  if(theSourceNS->Evolution() == TNaming_PRIMITIVE) isPrimitive = Standard_True;
  const TDF_Label& aSrcLabel     = theSourceNS->Label();
#ifdef MDTV_DEB_TRSF
  cout <<"TransformationDriver: ";
  PrintE(aSrcLabel);
#endif

  TopoDS_Compound aCompShape;
  BRep_Builder    aB;
  aB.MakeCompound(aCompShape);
  TopTools_MapOfShape aSMap;
  TopTools_DataMapOfShapeInteger aTagMap;
  //Collect  shapes
  if(aSMap.Add(aSrcShape))
    aB.Add(aCompShape, aSrcShape); 
  CollectShapes(aSrcShape,aCompShape,aSMap, aSrcLabel, aTagMap, isPrimitive);

  //Transform
  BRepBuilderAPI_Transform aTransformer(aCompShape, theTrsf, Standard_False);
  TopTools_DataMapOfShapeShape aTMap;
  BuildMap (aSMap, aTransformer,aTMap);

//Load
  TopoDS_Shape aNewSh;
  if (aTMap.IsBound(aSrcShape)) aNewSh  = aTMap(aSrcShape);
  if(!aNewSh.IsNull()) {
    aBuilder.Modify(aSrcShape, aNewSh);
    aTMap.UnBind(aSrcShape);
  }

  TopTools_DataMapOfShapeShape SubShapes;
  TopExp_Explorer Exp(aNewSh, TopAbs_FACE);
  for (; Exp.More(); Exp.Next()) {
    SubShapes.Bind(Exp.Current(),Exp.Current());
  }
  for (Exp.Init(aNewSh, TopAbs_EDGE); Exp.More(); Exp.Next()) {
    SubShapes.Bind(Exp.Current(),Exp.Current());
  }
  for (Exp.Init(aNewSh, TopAbs_VERTEX); Exp.More(); Exp.Next()) {
    SubShapes.Bind(Exp.Current(),Exp.Current());
  }

  Standard_Integer aNextTag(0);
  TopTools_DataMapIteratorOfDataMapOfShapeInteger it(aTagMap);
  for(;it.More();it.Next()) {
    if(it.Value() > aNextTag)
      aNextTag = it.Value();
  }
  TopTools_DataMapIteratorOfDataMapOfShapeShape anIt(aTMap);
  Standard_Boolean aF, anE, aV;
  aF = anE = aV = Standard_True;
  TNaming_Builder* pB1 = NULL;
  TNaming_Builder* pB2 = NULL;
  TNaming_Builder* pB3 = NULL; 
  for(;anIt.More();anIt.Next()) {
    const TopoDS_Shape& aKey = anIt.Key();
    TopoDS_Shape newShape = anIt.Value();
    if(isPrimitive) {
      if (SubShapes.IsBound(newShape)) {
	newShape.Orientation((SubShapes(newShape)).Orientation());
      }
      if(aTagMap.IsBound(aKey)) {
	const TDF_Label& aLabel = theResultLabel.FindChild(aTagMap.Find(aKey),  Standard_True);
	TNaming_Builder aBuilder(aLabel);
	aBuilder.Modify(aKey, newShape);
      } else {
	aNextTag++;
	const TDF_Label& aLabel = theResultLabel.FindChild(aNextTag,  Standard_True);
	TNaming_Builder aBuilder(aLabel);
	aBuilder.Modify(aKey, newShape);
      }
    } else {
    if(aKey.ShapeType() == TopAbs_FACE) {
      if(aF) {
	const TDF_Label& aFLabel = theResultLabel.FindChild(FACES_TAG,  Standard_True);
	TNaming_Builder aFBuilder(aFLabel);
	pB1 = &aFBuilder;
	aF = Standard_False; 
      }
      if (SubShapes.IsBound(newShape)) {
	newShape.Orientation((SubShapes(newShape)).Orientation());
      }
      pB1->Modify(anIt.Key(), newShape);
    }
    else if(aKey.ShapeType() == TopAbs_EDGE) {
      if(anE) {
	const TDF_Label& aELabel = theResultLabel.FindChild(EDGES_TAG,  Standard_True);
	TNaming_Builder anEBuilder(aELabel);
	pB2 = &anEBuilder;
	anE = Standard_False; 
      }
      if (SubShapes.IsBound(newShape)) {
	newShape.Orientation((SubShapes(newShape)).Orientation());
      }
      pB2->Modify(anIt.Key(), newShape);
    }
    else if(aKey.ShapeType() == TopAbs_VERTEX) {
      if(aV) {
	const TDF_Label& aVLabel = theResultLabel.FindChild(VERTEX_TAG,  Standard_True);
	TNaming_Builder aVBuilder(aVLabel);
	pB3 = &aVBuilder;
	aV = Standard_False; 
      }
      if (SubShapes.IsBound(newShape)) {
	newShape.Orientation((SubShapes(newShape)).Orientation());
      }
      pB3->Modify(anIt.Key(), newShape);
    }
  }
  }
}
