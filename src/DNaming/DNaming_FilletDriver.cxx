// Created on: 2009-05-06
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


#include <DNaming_FilletDriver.ixx>
#include <Precision.hxx>
#include <Standard_GUID.hxx>
#include <Standard_Real.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_MapOfShape.hxx>
#include <TopTools_ListOfShape.hxx>
#include <BRepAlgo.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Edge.hxx>
#include <TDF_Label.hxx>
#include <TDataStd_Real.hxx>
#include <TDataStd_Integer.hxx>
#include <TNaming.hxx>
#include <TNaming_Iterator.hxx>
#include <TNaming_Builder.hxx>
#include <TNaming_NamedShape.hxx>
#include <TFunction_Logbook.hxx>
#include <TFunction_Function.hxx>
#include <DNaming.hxx>
#include <TopTools_DataMapOfShapeShape.hxx>
#include <ModelDefinitions.hxx>


//=======================================================================
//function : FilletDriver
//purpose  : Constructor
//=======================================================================
DNaming_FilletDriver::DNaming_FilletDriver()
{}

//=======================================================================
//function : Validate
//purpose  : Validates labels of a function in <log>.
//=======================================================================
void DNaming_FilletDriver::Validate(TFunction_Logbook& theLog) const
{}

//=======================================================================
//function : MustExecute
//purpose  : Analyse in <log> if the loaded function must be executed
//=======================================================================
Standard_Boolean DNaming_FilletDriver::MustExecute(const TFunction_Logbook& theLog) const
{
  return Standard_True;
}

//=======================================================================
//function : Execute
//purpose  : Execute the function and push in <log> the impacted labels
//=======================================================================
Standard_Integer DNaming_FilletDriver::Execute(TFunction_Logbook& theLog) const
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
    cout<<"FilletDriver:: Context is empty"<<endl;
#endif
    aFunction->SetFailure(WRONG_ARGUMENT);
    return -1;
  }
  
  const Standard_Real aRadius = DNaming::GetReal(aFunction,FILLET_RADIUS)->Get();  
  const ChFi3d_FilletShape aSurfaceType = 
    (ChFi3d_FilletShape) DNaming::GetInteger(aFunction,FILLET_SURFTYPE)->Get();

  if(aRadius < Precision::Confusion()) {
    aFunction->SetFailure(WRONG_ARGUMENT);
#ifdef DEB
    cout << "FilletDriver:: Radius < Precision::Confusion" << endl;
#endif
    return -1;
  }


  Handle(TDataStd_UAttribute) aPathObj = DNaming::GetObjectArg(aFunction,FILLET_PATH);
  Handle(TNaming_NamedShape) aPathNS = DNaming::GetObjectValue(aPathObj);
  if (aPathNS.IsNull() || aPathNS->IsEmpty()) {
#ifdef DEB
    cout<<"FilletDriver:: Path is empty"<<endl;
#endif
    aFunction->SetFailure(WRONG_ARGUMENT);
    return -1;
  }
  
  TopoDS_Shape aPATH = aPathNS->Get();
  TopoDS_Shape aCONTEXT = aContextNS->Get();
  if (aPATH.IsNull() || aCONTEXT.IsNull()) {
#ifdef DEB
    cout<<"FilletDriver:: Path or Context is null"<<endl;
#endif
    aFunction->SetFailure(WRONG_ARGUMENT);
    return -1;
  }

  TopExp_Explorer expl;
  TopTools_MapOfShape View;
  
  BRepFilletAPI_MakeFillet aMkFillet(aCONTEXT, aSurfaceType);

  if(aPATH.ShapeType() != TopAbs_EDGE && aPATH.ShapeType() != TopAbs_FACE) {
    aFunction->SetFailure(WRONG_ARGUMENT);
    return -1;
  }
    
  if(aPATH.ShapeType() == TopAbs_FACE) {
    for (expl.Init(aPATH, TopAbs_EDGE); expl.More(); expl.Next()){ 
      const TopoDS_Edge& anEdge = TopoDS::Edge(expl.Current());
      if (!View.Add(anEdge)) continue;
      else 
	aMkFillet.Add(aRadius, anEdge); //Edge
    }
  }
  else {
    const TopoDS_Edge& anEdge = TopoDS::Edge(aPATH);
    aMkFillet.Add(aRadius, anEdge); //Edge
  }

  
  aMkFillet.Build();

  if (!aMkFillet.IsDone()) {
    aFunction->SetFailure(ALGO_FAILED);
    return -1;
  }
  TopTools_ListOfShape aLarg;
  aLarg.Append(aCONTEXT);
  if (!BRepAlgo::IsValid(aLarg, aMkFillet.Shape(),Standard_False,Standard_False)) {
    aFunction->SetFailure(RESULT_NOT_VALID);
    return -1;
  }

// Naming
  LoadNamingDS(RESPOSITION(aFunction), aMkFillet, aCONTEXT);

  theLog.SetValid(RESPOSITION(aFunction),Standard_True);  
  aFunction->SetFailure(DONE);
  return 0;
}

//=======================================================================
//function : LoadAndName
//purpose  : 
//=======================================================================
void DNaming_FilletDriver::LoadNamingDS (const TDF_Label& theResultLabel, 
					 BRepFilletAPI_MakeFillet& theMkFillet,
					 const TopoDS_Shape& theContext) const 
{
  TNaming_Builder aBuilder (theResultLabel);
  TopoDS_Shape aResult = theMkFillet.Shape();

  if (aResult.ShapeType() == TopAbs_COMPOUND) {
    Standard_Integer nbSubResults = 0;
    TopoDS_Iterator itr(aResult);
    for (; itr.More(); itr.Next()) nbSubResults++;
    if (nbSubResults == 1) {
      itr.Initialize(aResult);
      if (itr.More()) aResult = itr.Value();
    }
  }
  if (aResult.IsNull()) aBuilder.Generated(aResult);
  else 
    aBuilder.Modify(theContext, aResult);

  TopTools_DataMapOfShapeShape SubShapes;
  for (TopExp_Explorer Exp(aResult, TopAbs_FACE); Exp.More(); Exp.Next()) {
    SubShapes.Bind(Exp.Current(),Exp.Current());
  }

  //New faces generated from edges
  TNaming_Builder anEdgeBuilder(theResultLabel.FindChild(1,Standard_True));
  DNaming::LoadAndOrientGeneratedShapes(theMkFillet, theContext, TopAbs_EDGE, anEdgeBuilder, SubShapes);

  //Faces of the initial shape modified by theMkFillet
  TNaming_Builder aFacesBuilder(theResultLabel.FindChild(2,Standard_True));
  DNaming::LoadAndOrientModifiedShapes(theMkFillet, theContext, TopAbs_FACE, aFacesBuilder, SubShapes);


  //New faces generated from vertices (if exist)
  TNaming_Builder aVFacesBuilder(theResultLabel.FindChild(3,Standard_True));
  DNaming::LoadAndOrientGeneratedShapes(theMkFillet, theContext, TopAbs_VERTEX, aVFacesBuilder, SubShapes);  

  //Deleted faces of the initial shape
  TNaming_Builder aDelBuilder(theResultLabel.FindChild(4,Standard_True));
  DNaming::LoadDeletedShapes(theMkFillet, theContext, TopAbs_FACE, aDelBuilder);

}
