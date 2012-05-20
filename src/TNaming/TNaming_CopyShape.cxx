// Created on: 2000-02-14
// Created by: Denis PASCAL
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



#include <TNaming_CopyShape.ixx>
#include <TopAbs.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopLoc_Datum3D.hxx>

//=======================================================================
//function : CopyTool
//purpose  : Tool to copy a set of shape(s), using the aMap
//=======================================================================

void TNaming_CopyShape::CopyTool( const TopoDS_Shape& aShape,
				 TColStd_IndexedDataMapOfTransientTransient&  aMap,
				 TopoDS_Shape&       aResult)
{

  Handle(TNaming_TranslateTool) TrTool = new TNaming_TranslateTool();
  TNaming_CopyShape::Translate (aShape, aMap, aResult, TrTool) ;
}

//=======================================================================
//function : Translate
//purpose  : TNaming
//=======================================================================

void TNaming_CopyShape::Translate( const TopoDS_Shape& aShape,		         
				  TColStd_IndexedDataMapOfTransientTransient&  aMap,
				  TopoDS_Shape& aResult,
				  const Handle(TNaming_TranslateTool)& TrTool)
{

  if (aShape.IsNull()) return;

  if (aMap.Contains(aShape.TShape())) {
    // get the translated TShape
    Handle(TopoDS_TShape) TS =
       *((Handle(TopoDS_TShape)*) &aMap.FindFromKey(aShape.TShape()));
    aResult.TShape(TS);
  }
  else {

    // create if not translated and update
    
    switch (aShape.ShapeType()) {
      
    case TopAbs_VERTEX :
      TrTool->MakeVertex(aResult);
      TrTool->UpdateVertex(aShape,aResult,aMap);
      break;
      
    case TopAbs_EDGE :
      TrTool->MakeEdge(aResult);
      TrTool->UpdateEdge(aShape,aResult,aMap);
      break;
      
    case TopAbs_WIRE :
      TrTool->MakeWire(aResult);
      TrTool->UpdateShape(aShape,aResult);
      break;
      
    case TopAbs_FACE :
      TrTool->MakeFace(aResult);
      TrTool->UpdateFace(aShape,aResult,aMap);
      break;
    
    case TopAbs_SHELL :
      TrTool->MakeShell(aResult);
      TrTool->UpdateShape(aShape,aResult);
      break;
    
    case TopAbs_SOLID :
      TrTool->MakeSolid(aResult);
      TrTool->UpdateShape(aShape,aResult);
      break;
      
    case TopAbs_COMPSOLID :
      TrTool->MakeCompSolid(aResult);
      TrTool->UpdateShape(aShape,aResult);
      break;
      
  case TopAbs_COMPOUND :
      TrTool->MakeCompound(aResult);
      TrTool->UpdateShape(aShape,aResult);
      break;

    default:
      break;
    }
  
    // bind and copy the sub-elements
    aMap.Add(aShape.TShape(),aResult.TShape()); //TShapes
    TopoDS_Shape S = aShape;
    S.Orientation(TopAbs_FORWARD);
    S.Location(TopLoc_Location()); //Identity
    // copy current Shape
    TopoDS_Iterator itr(S, Standard_False);
    Standard_Boolean wasFree = aResult.Free();
    aResult.Free(Standard_True);
    // translate <sub-shapes>
    for (;itr.More();itr.Next()) {
      TopoDS_Shape subShape;
      TNaming_CopyShape::Translate(itr.Value(), aMap, subShape, TrTool);
      TrTool->Add(aResult, subShape);// add subshapes
    }

    aResult.Free(wasFree);
  }
  
  aResult.Orientation(aShape.Orientation());
  aResult.Location(TNaming_CopyShape::Translate(aShape.Location(), aMap));
  TrTool->UpdateShape(aShape,aResult);
// #ifdef DEB
//     if(fShar) {
//       cout << "=== Shareable shape ===" << endl;
//       cout << "aShape Type = " <<(aShape.TShape())->DynamicType() << endl;
//       if(aShape.Orientation() == aResult.Orientation())
// 	cout<<"\tSource and result shapes have the same Orientation"<< endl;
//       if((aShape.Location().IsEqual(aResult.Location())))
// 	cout <<"\tSource and result shapes have the same Locations" << endl;
//       if((aShape.IsSame(aResult)))
// 	 cout <<"\tShapes arew the same (i.e. the same TShape and the same Locations)" << endl;
//     }	    
// #endif
}

//=======================================================================
// static TranslateDatum3D
//=======================================================================
static Handle(TopLoc_Datum3D) TranslateDatum3D(const Handle(TopLoc_Datum3D)& D,
					       TColStd_IndexedDataMapOfTransientTransient&  aMap)
{
  Handle(TopLoc_Datum3D) TD;
  if(aMap.Contains(D))
       TD = Handle(TopLoc_Datum3D)::DownCast(aMap.FindFromKey(D));
  else {
    TD = new TopLoc_Datum3D(D->Transformation());
    aMap.Add(D, TD);
  }
  return TD;
}
//=======================================================================
//function : Translates
//purpose  : Topological Location
//=======================================================================

TopLoc_Location TNaming_CopyShape::Translate(const TopLoc_Location& L,
					     TColStd_IndexedDataMapOfTransientTransient&  aMap)
{
  TopLoc_Location result;

 if (!L.IsIdentity()) {
   result = Translate(L.NextLocation(),aMap) * 
     TopLoc_Location(TranslateDatum3D(L.FirstDatum(),aMap)).Powered(L.FirstPower());

 }
  return result;
}


