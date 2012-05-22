// Created on: 2000-08-15
// Created by: Andrey BETENEV
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


#include <XCAFPrs.ixx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <TDF_LabelSequence.hxx>
#include <TopoDS_Iterator.hxx>
#include <BRep_Builder.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Compound.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <TColStd_HSequenceOfExtendedString.hxx>
#include <XCAFDoc_LayerTool.hxx>
#include <TopTools_SequenceOfShape.hxx>
#include <TopLoc_IndexedMapOfLocation.hxx>
#include <TDF_AttributeSequence.hxx>
#include <XCAFDoc_GraphNode.hxx>

static Standard_Boolean viewnameMode = Standard_False;

static Standard_Boolean getShapesOfSHUO (TopLoc_IndexedMapOfLocation& theaPrevLocMap,
                                         const Handle(XCAFDoc_ShapeTool)& theSTool,
                                         const TDF_Label& theSHUOlab,
                                         TopTools_SequenceOfShape& theSHUOShapeSeq)
{
  Handle(XCAFDoc_GraphNode) SHUO;
  TDF_LabelSequence aLabSeq;
  theSTool->GetSHUONextUsage( theSHUOlab, aLabSeq );
  if (aLabSeq.Length() >= 1)
    for (Standard_Integer i = 1; i <= aLabSeq.Length(); i++) {
      TDF_Label aSubCompL = aLabSeq.Value( i );
      TopLoc_Location compLoc = XCAFDoc_ShapeTool::GetLocation ( aSubCompL.Father() );
      // create new map of laocation (to not merge locations from different shapes)
      TopLoc_IndexedMapOfLocation aNewPrevLocMap;
      for (Standard_Integer m = 1; m <= theaPrevLocMap.Extent(); m++)
        aNewPrevLocMap.Add( theaPrevLocMap.FindKey( m ) );
      aNewPrevLocMap.Add( compLoc );
      // got for the new sublocations and corresponding shape
      getShapesOfSHUO( aNewPrevLocMap, theSTool, aSubCompL, theSHUOShapeSeq );
    }
  else {
    TopoDS_Shape aSHUO_NUSh = theSTool->GetShape ( theSHUOlab.Father() );
    if ( aSHUO_NUSh.IsNull() ) return Standard_False;
    // cause got shape with location already.
    TopLoc_Location nullLoc;
    aSHUO_NUSh.Location ( nullLoc );
    // multiply the locations
    Standard_Integer intMapLenght = theaPrevLocMap.Extent();
    if ( intMapLenght < 1 )
      return Standard_False; // should not be, but to avoid exception...?
    TopLoc_Location SupcompLoc;
    SupcompLoc = theaPrevLocMap.FindKey( intMapLenght );
    if (intMapLenght > 1) {
      Standard_Integer l = intMapLenght - 1;
      while (l >= 1) {
        SupcompLoc = theaPrevLocMap.FindKey( l ).Multiplied( SupcompLoc );
        l--;
      }
    }
    aSHUO_NUSh.Location( SupcompLoc );
    theSHUOShapeSeq.Append( aSHUO_NUSh );
  }
  return (theSHUOShapeSeq.Length() > 0);
}

//=======================================================================
//function : CollectStyleSettings
//purpose  : 
//=======================================================================

void XCAFPrs::CollectStyleSettings (const TDF_Label &L, 
				    const TopLoc_Location &loc, 
				    XCAFPrs_DataMapOfShapeStyle &settings)
{
  Handle(XCAFDoc_ColorTool) CTool = XCAFDoc_DocumentTool::ColorTool( L );

  // for references, first collect colors of referred shape
  TDF_Label Lref;
  if ( XCAFDoc_ShapeTool::GetReferredShape ( L, Lref ) ) {
    TopLoc_Location locSub = loc.Multiplied ( XCAFDoc_ShapeTool::GetLocation ( L ) );
    CollectStyleSettings ( Lref, locSub, settings );
  }
  
  // for assemblies, first collect colors defined in components
  TDF_LabelSequence seq;
  if ( XCAFDoc_ShapeTool::GetComponents ( L, seq ) && seq.Length() >0 ) {
    for ( Standard_Integer i = 1; i <= seq.Length(); i++ ) {
      CollectStyleSettings ( seq.Value(i), loc, settings );
    }
  }

  // collect settings on subshapes and the shape itself
  seq.Clear();
  XCAFDoc_ShapeTool::GetSubShapes ( L, seq );
  seq.Append ( L );
  for ( Standard_Integer i = 1; i <= seq.Length(); i++ ) {
    TDF_Label lab = seq.Value(i);
    XCAFPrs_Style style;
    Handle(XCAFDoc_LayerTool) LTool = XCAFDoc_DocumentTool::LayerTool( lab );
    Handle(TColStd_HSequenceOfExtendedString) LayNames = new TColStd_HSequenceOfExtendedString;

    LTool->GetLayers(lab, LayNames);
    Standard_Integer InVisCount = 0;
    for ( Standard_Integer iL = 1; iL <= LayNames->Length(); iL++) {
      if ( !LTool->IsVisible( LTool->FindLayer(LayNames->Value(iL)) ) ) InVisCount++;
    }
    if ( (InVisCount >0 && InVisCount == LayNames->Length() ) ||
         !CTool->IsVisible(lab) ) {
      style.SetVisibility(Standard_False);
    }
    else {
      Quantity_Color C;
      if ( CTool->GetColor ( lab, XCAFDoc_ColorGen, C ) ) {
	style.SetColorCurv ( C );
	style.SetColorSurf ( C );
      }
      if ( CTool->GetColor ( lab, XCAFDoc_ColorSurf, C ) )
	style.SetColorSurf ( C );
      if ( CTool->GetColor ( lab, XCAFDoc_ColorCurv, C ) )
	style.SetColorCurv ( C );
    }
    // PTV try to set color from SHUO structure
    Handle(XCAFDoc_ShapeTool) STool = CTool->ShapeTool();
    Handle(XCAFDoc_GraphNode) SHUO;
    TDF_AttributeSequence theSHUOAttrs;
    if (STool->IsComponent( lab ) ) {
      STool->GetAllComponentSHUO( lab, theSHUOAttrs );
      for (Standard_Integer shuoIndx = 1; shuoIndx <= theSHUOAttrs.Length(); shuoIndx++) {
        SHUO = Handle(XCAFDoc_GraphNode)::DownCast(theSHUOAttrs.Value(shuoIndx));
        if ( SHUO.IsNull() )
          continue;
        TDF_Label aSHUOlab = SHUO->Label();

        TDF_LabelSequence aLabSeq;
        STool->GetSHUONextUsage( aSHUOlab, aLabSeq );
        if (aLabSeq.Length() < 1 )
          continue;
      
        Quantity_Color C;
        XCAFPrs_Style SHUOstyle;
        if (!CTool->IsVisible( aSHUOlab ) )
          SHUOstyle.SetVisibility(Standard_False);
        else {
          if ( CTool->GetColor ( aSHUOlab, XCAFDoc_ColorGen, C ) ) {
            SHUOstyle.SetColorCurv ( C );
            SHUOstyle.SetColorSurf ( C );
          }
          if ( CTool->GetColor ( aSHUOlab, XCAFDoc_ColorSurf, C ) )
            SHUOstyle.SetColorSurf ( C );
          if ( CTool->GetColor ( aSHUOlab, XCAFDoc_ColorCurv, C ) )
            SHUOstyle.SetColorCurv ( C );
        }
        if ( !SHUOstyle.IsSetColorCurv() && 
            !SHUOstyle.IsSetColorSurf() &&
            SHUOstyle.IsVisible() )
          continue;
      
      // set style for all component from Next Usage Occurrence.
#ifdef DEB
        cout << "Set the style for SHUO next_usage-occurrance" << endl;
#endif
        /* 
        // may be work, but static it returns excess shapes. It is more faster to use OLD version.
        // PTV 14.02.2003 NEW version using API of ShapeTool
        TopTools_SequenceOfShape aSHUOShapeSeq;
        STool->GetAllStyledComponents( SHUO, aSHUOShapeSeq );
        for (Standard_Integer si= 1; si <= aSHUOShapeSeq.Length(); si++) {
          TopoDS_Shape aSHUOSh = aSHUOShapeSeq.Value(si);
          if (!aSHUOSh.IsNull())
            settings.Bind ( aSHUOSh, SHUOstyle );
        }
        */
        // OLD version that was written before ShapeTool API, and ti FASTER for presentation
        // get TOP location of SHUO component
        TopLoc_Location compLoc = XCAFDoc_ShapeTool::GetLocation ( lab );
        TopLoc_IndexedMapOfLocation aPrevLocMap;
        // get previous setted location 
        if ( !loc.IsIdentity() )
          aPrevLocMap.Add( loc );
      
        aPrevLocMap.Add( compLoc );
        TopTools_SequenceOfShape aSHUOShapeSeq;
        // get shapes of SHUO Next_Usage components
        getShapesOfSHUO( aPrevLocMap, STool, aSHUOlab, aSHUOShapeSeq );
        for (Standard_Integer n = 1; n <= aSHUOShapeSeq.Length(); n++ ) {
          TopoDS_Shape aSHUOSh = aSHUOShapeSeq.Value( n );
          settings.Bind ( aSHUOSh, SHUOstyle );
        }
        continue;
      }
    }
    if ( !style.IsSetColorCurv() && 
         !style.IsSetColorSurf() &&
          style.IsVisible() )
      continue;
    TopoDS_Shape sub = XCAFDoc_ShapeTool::GetShape ( lab );
    sub.Move ( loc );
    settings.Bind ( sub, style );
  }
}

//=======================================================================
//function : DispatchStyles
//purpose  : fill items map (style - shape)
//=======================================================================

// merge style with father (to reflect inheritance)
static Standard_Boolean MergeStyles (XCAFPrs_Style &style, const XCAFPrs_Style &father)
{
  if ( ! style.IsSetColorCurv() && father.IsSetColorCurv() ) 
    style.SetColorCurv ( father.GetColorCurv() );
  if ( ! style.IsSetColorSurf() && father.IsSetColorSurf() ) 
    style.SetColorSurf ( father.GetColorSurf() );
  return style == father;
}

Standard_Boolean XCAFPrs::DispatchStyles (const TopoDS_Shape &shape, 
					  const XCAFPrs_DataMapOfShapeStyle &settings, 
					  XCAFPrs_DataMapOfStyleShape &items, 
					  const XCAFPrs_Style &DefStyle,
					  const Standard_Boolean force,
					  const TopAbs_ShapeEnum context)
{
  const XCAFPrs_Style *style = &DefStyle;
  XCAFPrs_Style ownstyle;

  // check own setting of current shape
  Standard_Boolean overriden = Standard_False;
  if ( settings.IsBound ( shape ) ) {
    ownstyle = settings.Find ( shape );
    if ( ! MergeStyles ( ownstyle, DefStyle ) ) {
      overriden = Standard_True;
      style = &ownstyle;
    }
  }

  // iterate on subshapes
  BRep_Builder B;
  TopoDS_Shape copy = shape.EmptyCopied();
  Standard_Boolean suboverride = Standard_False;
  Standard_Integer nbDef = 0;
  for ( TopoDS_Iterator it(shape); it.More(); it.Next() ) {
    if ( DispatchStyles ( it.Value(), settings, items, *style, Standard_False, shape.ShapeType() ) ) {
      suboverride = Standard_True;
    }
    else {
      B.Add ( copy, it.Value() );
      nbDef++;
    }
  }
  if ( shape.ShapeType() == TopAbs_FACE || ! suboverride ) 
    copy = shape;
  else if ( ! nbDef ) return overriden || suboverride; // avoid empty compounds

  // if any of styles is overriden regarding to default one, add rest to map
  if ( overriden || force || 
       ( suboverride && context != TopAbs_FACE ) ) { // avoid drawing edges of the same color as face
    TopoDS_Compound C;
    if ( items.IsBound ( *style ) ) 
      C = TopoDS::Compound ( items.Find ( *style ) );
    else {
      B.MakeCompound ( C );
      items.Bind ( *style, C );
    }
    B.Add ( C, copy );
  }
  return overriden || suboverride;
}

//=======================================================================
//function : SetViewNameMode
//purpose  : 
//=======================================================================

void XCAFPrs::SetViewNameMode(const Standard_Boolean aNameMode )
{
  viewnameMode = aNameMode;
}

//=======================================================================
//function : GetViewNameMode
//purpose  : 
//=======================================================================

Standard_Boolean XCAFPrs::GetViewNameMode()
{
  return viewnameMode;
}
