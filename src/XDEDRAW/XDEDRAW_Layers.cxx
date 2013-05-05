// Created on: 2000-08-04
// Created by: Pavel TELKOV
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


#include <XDEDRAW_Layers.ixx>

#include <Draw.hxx>
#include <DBRep.hxx>
#include <DDocStd.hxx>

#include <TCollection_AsciiString.hxx>
#include <TColStd_HSequenceOfExtendedString.hxx>
#include <TopoDS_Shape.hxx>

#include <TDF_Tool.hxx>
#include <TDF_Label.hxx>
#include <TDF_LabelSequence.hxx>
#include <TDocStd_Document.hxx>

#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_LayerTool.hxx>

//=======================================================================
// Section: Work with layers
//=======================================================================

static Standard_Integer addLayer (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc!=3) {
    di<<"Use: "<<argv[0]<<" DocName StringLayer "<<"\n";
    return 1;
  }
  Handle(TDocStd_Document) Doc;
  DDocStd::GetDocument(argv[1], Doc);
  if ( Doc.IsNull() ) { di << argv[1] << " is not a document" << "\n"; return 1; }
  Handle(XCAFDoc_LayerTool) localLayerTool = XCAFDoc_DocumentTool::LayerTool(Doc->Main());
  
  TCollection_ExtendedString aLayer = argv[2];
  TDF_Label aLabel = localLayerTool->AddLayer(aLayer);
  TCollection_AsciiString Entry;
  TDF_Tool::Entry(aLabel, Entry);
  di << Entry.ToCString();
  return 0;
}

static Standard_Integer findLayer (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc!=3) {
    di<<"Use: "<<argv[0]<<" DocName StringLayer "<<"\n";
    return 1;
  }
  Handle(TDocStd_Document) Doc;
  DDocStd::GetDocument(argv[1], Doc);
  if ( Doc.IsNull() ) { di << argv[1] << " is not a document" << "\n"; return 1; }
  Handle(XCAFDoc_LayerTool) localLayerTool = XCAFDoc_DocumentTool::LayerTool(Doc->Main());
  
  TCollection_ExtendedString aLayer = argv[2];
  TDF_Label aLabel = localLayerTool->FindLayer(aLayer);
  TCollection_AsciiString Entry;
  TDF_Tool::Entry(aLabel, Entry);
  di << Entry.ToCString();
  return 0;
}

static Standard_Integer removeLayer (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc!=3) {
    di<<"Use: "<<argv[0]<<" DocName {Label|string}"<<"\n";
    return 1;
  }
  Handle(TDocStd_Document) Doc;
  DDocStd::GetDocument(argv[1], Doc);
  if ( Doc.IsNull() ) { di << argv[1] << " is not a document" << "\n"; return 1; }
  Handle(XCAFDoc_LayerTool) localLayerTool = XCAFDoc_DocumentTool::LayerTool(Doc->Main());

  TDF_Label aLabel;
  TDF_Tool::Label(Doc->GetData(), argv[2], aLabel);
  if ( aLabel.IsNull() ) {
    TCollection_ExtendedString aLayer = argv[2];
    aLabel = localLayerTool->FindLayer(aLayer);
  }
  if ( aLabel.IsNull() ) return 1;
  localLayerTool->RemoveLayer( aLabel);
  return 0;
}


static Standard_Integer setLayer (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc<4) {
    di<<"Use: "<<argv[0]<<" DocName {Shape|Label} StringLayer [shapeInOneLayer(0/1)]"<<"\n";
    return 1;
  }
  Standard_Boolean shapeInOneLayer = Standard_False;
  if ( (argc==5) && (Draw::Atoi(argv[4])==1) ) shapeInOneLayer = Standard_True;
  Handle(TDocStd_Document) Doc;
  DDocStd::GetDocument(argv[1], Doc);
  if ( Doc.IsNull() ) { di << argv[1] << " is not a document" << "\n"; return 1; }
  Handle(XCAFDoc_LayerTool) localLayerTool = XCAFDoc_DocumentTool::LayerTool(Doc->Main());
  TDF_Label aLabel;
  TCollection_ExtendedString aLayer = argv[3];

  TDF_Tool::Label(Doc->GetData(), argv[2], aLabel);
  if ( !aLabel.IsNull() ) {
    localLayerTool->SetLayer(aLabel, aLayer, shapeInOneLayer);
  }
  else {
    TopoDS_Shape aShape= DBRep::Get(argv[2]);
    if ( !aShape.IsNull() ) {
      localLayerTool->SetLayer(aShape, aLayer, shapeInOneLayer);
    }
  }
  return 0;
}


static Standard_Integer getLayers (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc!=3) {
    di<<"Use: "<<argv[0]<<" DocName {Shape|Label} "<<"\n";
    return 1;
  }
  //
  Handle(TDocStd_Document) Doc;
  DDocStd::GetDocument(argv[1], Doc);
  if ( Doc.IsNull() ) { di << argv[1] << " is not a document" << "\n"; return 1; }
  Handle(XCAFDoc_LayerTool) localLayerTool = XCAFDoc_DocumentTool::LayerTool(Doc->Main());
  TDF_Label aLabel;
  Handle(TColStd_HSequenceOfExtendedString) aLayerS;
  TDF_Tool::Label(Doc->GetData(), argv[2], aLabel);
  if ( !aLabel.IsNull() ) {
    localLayerTool->GetLayers(aLabel, aLayerS);
  }
  else {
    TopoDS_Shape aShape= DBRep::Get(argv[2]);
    if ( !aShape.IsNull() ) {
      localLayerTool->GetLayers(aShape, aLayerS);
    }
  }
  Standard_Integer i = 1;
  if (!aLayerS.IsNull() && aLayerS->Length()!=0)
    for (; i <= aLayerS->Length(); i++) {
      TCollection_AsciiString Entry(aLayerS->Value(i),'?');
      di << "\"" << Entry.ToCString() << "\"" << " ";
    }
  return 0;
}


static Standard_Integer getLayerLabels (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc!=2) {
    di<<"Use: "<<argv[0]<<" DocName"<<"\n";
    return 1;
  }
  Handle(TDocStd_Document) Doc;
  DDocStd::GetDocument(argv[1], Doc);
  if ( Doc.IsNull() ) { di << argv[1] << " is not a document" << "\n"; return 1; }
  Handle(XCAFDoc_LayerTool) localLayerTool = XCAFDoc_DocumentTool::LayerTool(Doc->Main());
  TDF_LabelSequence aLabs;
  localLayerTool->GetLayerLabels(aLabs);
  if (aLabs.Length() ==0 ) {
    return 0;
  }
  Standard_Integer i = 1;
  for (; i <= aLabs.Length(); i++) {
    TDF_Label L = aLabs.Value(i);
    if ( !L.IsNull() ) {
      TCollection_AsciiString Entry;
      TDF_Tool::Entry(L, Entry);
      di << Entry.ToCString() << " ";
    }
  }
  return 0;
}


static Standard_Integer getOneLayer (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc!=3) {
    di<<"Use: "<<argv[0]<<" DocName LayerLabel"<<"\n";
    return 1;
  }
  Handle(TDocStd_Document) Doc;
  DDocStd::GetDocument(argv[1], Doc);
  if ( Doc.IsNull() ) { di << argv[1] << " is not a document" << "\n"; return 1; }
  Handle(XCAFDoc_LayerTool) localLayerTool = XCAFDoc_DocumentTool::LayerTool(Doc->Main());
  TDF_Label aLabel;
  TDF_Tool::Label(Doc->GetData(), argv[2], aLabel);
  if ( !aLabel.IsNull() ) {
    TCollection_ExtendedString layerName;
    localLayerTool->GetLayer(aLabel, layerName);
    TCollection_AsciiString Entry(layerName,'?');
    di << "\"" << Entry.ToCString() <<"\"";
  }
  return 0;
}


static Standard_Integer setLinkLayer (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc<4) {
    di<<"Use: "<<argv[0]<<" DocName {Shape|Label} LayerL [shapeInOneLayer(0/1)]"<<"\n";
    return 1;
  }
  Standard_Boolean shapeInOneLayer = Standard_False;
  if ( (argc==5) && (Draw::Atoi(argv[4])==1) ) shapeInOneLayer = Standard_True;
  Handle(TDocStd_Document) Doc;
  DDocStd::GetDocument(argv[1], Doc);
  if ( Doc.IsNull() ) { di << argv[1] << " is not a document" << "\n"; return 1; }
  Handle(XCAFDoc_LayerTool) localLayerTool = XCAFDoc_DocumentTool::LayerTool(Doc->Main());
  TDF_Label aLabel, layerLabel;
  TDF_Tool::Label(Doc->GetData(), argv[3], layerLabel);

  TDF_Tool::Label(Doc->GetData(), argv[2], aLabel);
  if ( !layerLabel.IsNull() ) {
    if ( !aLabel.IsNull() ) {
      localLayerTool->SetLayer(aLabel, layerLabel, shapeInOneLayer);
    }
    else {
      TopoDS_Shape aShape= DBRep::Get(argv[2]);
      if ( !aShape.IsNull() ) {
	localLayerTool->SetLayer(aShape, layerLabel, shapeInOneLayer);
      }
    }
  }
  return 0;
}


static Standard_Integer getAllLayers (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc!=2) {
    di<<"Use: "<<argv[0]<<" DocName"<<"\n";
    return 1;
  }
  Handle(TDocStd_Document) Doc;
  DDocStd::GetDocument(argv[1], Doc);
  if ( Doc.IsNull() ) { di << argv[1] << " is not a document" << "\n"; return 1; }
  Handle(XCAFDoc_LayerTool) localLayerTool = XCAFDoc_DocumentTool::LayerTool(Doc->Main());
  TDF_LabelSequence aLabs;
  localLayerTool->GetLayerLabels(aLabs);
  if (aLabs.Length() ==0 ) {
    return 0;
  }
  Standard_Integer i = 1;
  TCollection_ExtendedString layerName;
  
  for (; i <= aLabs.Length(); i++) {
    TDF_Label L = aLabs.Value(i);
    if ( !L.IsNull() ) {
      localLayerTool->GetLayer(L, layerName);
      TCollection_AsciiString Entry(layerName,'?');
      di << "\"" << Entry.ToCString() <<"\"";
      di << " ";
    }
  }
  return 0;
}


static Standard_Integer unSetLayer (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc!=4) {
    di<<"Use: "<<argv[0]<<" DocName {Shape|Label} stringL"<<"\n";
    return 1;
  }
  Handle(TDocStd_Document) Doc;
  DDocStd::GetDocument(argv[1], Doc);
  if ( Doc.IsNull() ) { di << argv[1] << " is not a document" << "\n"; return 1; }
  Handle(XCAFDoc_LayerTool) localLayerTool = XCAFDoc_DocumentTool::LayerTool(Doc->Main());
  TDF_Label aLabel;
  TCollection_ExtendedString aLayer = argv[3];

  TDF_Tool::Label(Doc->GetData(), argv[2], aLabel);
  if ( !aLabel.IsNull() ) {
    localLayerTool->UnSetOneLayer(aLabel, aLayer);
  }
  else {
    TopoDS_Shape aShape= DBRep::Get(argv[2]);
    if ( !aShape.IsNull() ) {
      localLayerTool->UnSetOneLayer(aShape, aLayer);
    }
  }
  return 0;
}


static Standard_Integer unSetAllLayers (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc!=3) {
    di<<"Use: "<<argv[0]<<" DocName {Shape|Label}"<<"\n";
    return 1;
  }
  Handle(TDocStd_Document) Doc;
  DDocStd::GetDocument(argv[1], Doc);
  if ( Doc.IsNull() ) { di << argv[1] << " is not a document" << "\n"; return 1; }
  Handle(XCAFDoc_LayerTool) localLayerTool = XCAFDoc_DocumentTool::LayerTool(Doc->Main());
  TDF_Label aLabel;

  TDF_Tool::Label(Doc->GetData(), argv[2], aLabel);
  if ( !aLabel.IsNull() ) {
    localLayerTool->UnSetLayers(aLabel);
  }
  else {
    TopoDS_Shape aShape= DBRep::Get(argv[2]);
    if ( !aShape.IsNull() ) {
      localLayerTool->UnSetLayers(aShape);
    }
  }
  return 0;
}


static Standard_Integer removeAllLayers (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc!=2) {
    di<<"Use: "<<argv[0]<<" DocName"<<"\n";
    return 1;
  }
  Handle(TDocStd_Document) Doc;
  DDocStd::GetDocument(argv[1], Doc);
  if ( Doc.IsNull() ) { di << argv[1] << " is not a document" << "\n"; return 1; }
  Handle(XCAFDoc_LayerTool) localLayerTool = XCAFDoc_DocumentTool::LayerTool(Doc->Main());
  
  TDF_LabelSequence aLabs;
  localLayerTool->GetLayerLabels(aLabs);
  if (aLabs.Length() ==0 ) {
    return 0;
  }
  Standard_Integer i = 1;
  for (; i <= aLabs.Length(); i++) {
    TDF_Label L = aLabs.Value(i);
    if ( !L.IsNull() ) {
      localLayerTool->RemoveLayer(L);
    }
  }
  return 0;
}

static Standard_Integer setVisibility (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc<3) {
    di<<"Use: "<<argv[0]<<"DocName {layerLable|StringLayer} [isvisible(1/0)]"<<"\n";
    return 1;
  }
  Handle(TDocStd_Document) Doc;
  DDocStd::GetDocument(argv[1], Doc);
  if ( Doc.IsNull() ) { di << argv[1] << " is not a document" << "\n"; return 1; }
  Handle(XCAFDoc_LayerTool) localLayerTool = XCAFDoc_DocumentTool::LayerTool(Doc->Main());
  Standard_Boolean isvisible = Standard_False;
  if ( (argc==4) && (Draw::Atoi(argv[3])==1) ) isvisible = Standard_True;
  
  TDF_Label aLabel;
  TDF_Tool::Label(Doc->GetData(), argv[2], aLabel);
  if ( aLabel.IsNull() ) {
    TCollection_ExtendedString aLayer = argv[2];
    aLabel = localLayerTool->FindLayer(aLayer);
  }
  if ( aLabel.IsNull() ) return 1;
  localLayerTool->SetVisibility(aLabel, isvisible);
  return 0;
}


static Standard_Integer isVisible (Draw_Interpretor& di, Standard_Integer argc, const char** argv)
{
  if (argc!=3) {
    di<<"Use: "<<argv[0]<<" DocName {layerLable|StringLayer}"<<"\n";
    return 1;
  }
  Handle(TDocStd_Document) Doc;
  DDocStd::GetDocument(argv[1], Doc);
  if ( Doc.IsNull() ) { di << argv[1] << " is not a document" << "\n"; return 1; }
  Handle(XCAFDoc_LayerTool) localLayerTool = XCAFDoc_DocumentTool::LayerTool(Doc->Main());

  TDF_Label aLabel;
  TDF_Tool::Label(Doc->GetData(), argv[2], aLabel);
  if ( aLabel.IsNull() ) {
    TCollection_ExtendedString aLayer = argv[2];
    aLabel = localLayerTool->FindLayer(aLayer);
  }
  if ( aLabel.IsNull() ) return 1;
  if (localLayerTool->IsVisible( aLabel) ) di << 1;
  else di << 0;
  return 0;
}

//=======================================================================
//function : InitCommands
//purpose  : 
//=======================================================================

void XDEDRAW_Layers::InitCommands(Draw_Interpretor& di) 
{

  static Standard_Boolean initactor = Standard_False;
  if (initactor) return;  initactor = Standard_True;

  //=====================================
  // Work with layers
  //=====================================  
  
  Standard_CString g = "XDE layer's commands";
  
  di.Add ("XSetLayer","DocName {Shape|Label} StringLayer [shapeInOneLayer(0/1)] \t: Set reference between Shape and Layer (add layer if nesessary). shapeInOneLayer 0 is default",
		   __FILE__, setLayer, g);

  di.Add ("XGetLayers","DocName {Shape|Label} \t: Get layers of indicated shape",
		   __FILE__, getLayers, g);

  di.Add ("XGetOneLayer","DocName LayerLabel \t: Print name of layer.",
		   __FILE__, getOneLayer, g);

  di.Add ("XAddLayer","DocName StringLayer \t: Adding layer in XCAFDocument.",
		   __FILE__, addLayer, g);

  di.Add ("XSetLinkLayer","DocName {Shape|Label} LayerL [shapeInOneLayer(0/1)] \t: Set reference between shape and existing layer. shapeInOneLayer 0 is default",
		   __FILE__, setLinkLayer, g);

  di.Add ("XGetAllLayers","DocName \t: Get all layers in XCAFDocument.",
		   __FILE__, getAllLayers, g);

  di.Add ("XUnSetLayer","DocName {Shape|Label} stringL \t: unset shape from indicated layer.",
		   __FILE__, unSetLayer, g);

  di.Add ("XUnSetAllLayers","DocName {Shape|Label} \t: unset shape from all layers.",
		   __FILE__, unSetAllLayers, g);

  di.Add ("XRemoveLayer","DocName {Label|string} \t:remove layer from XCAFDocument.",
		   __FILE__, removeLayer, g);

  di.Add ("XRemoveAllLayers","DocName \t: remove all layers from XCAFDocument.",
		   __FILE__, removeAllLayers, g);

  di.Add ("XFindLayer","DocName string \t: Print label where are layer is situated.",
		   __FILE__, findLayer, g);

  di.Add ("XGetLayerLabels","DocName \t: Print labels from layertable.",
		   __FILE__, getLayerLabels, g);

  di.Add ("XSetVisibility","DocName {layerLable|StringLayer} [isvisible(1/0)] \t: Set visibility of layer",
		   __FILE__, setVisibility, g);

  di.Add ("XIsVisible","DocName {layerLable|StringLayer} \t: Return 1 if layer is visible, 0 if not",
		   __FILE__, isVisible, g);
}
