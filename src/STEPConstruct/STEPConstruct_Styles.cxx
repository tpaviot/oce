// Created on: 1999-09-10
// Created by: Andrey BETENEV
// Copyright (c) 1999-1999 Matra Datavision
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


#include <STEPConstruct_Styles.ixx>
#include <STEPConstruct.hxx>

#include <TCollection_HAsciiString.hxx>
#include <TopoDS_Iterator.hxx>

#include <XSControl_TransferReader.hxx>
#include <XSControl_TransferWriter.hxx>
#include <Interface_Graph.hxx>
#include <Interface_Static.hxx>
#include <Interface_InterfaceModel.hxx>
#include <Interface_EntityIterator.hxx>
#include <TransferBRep_ShapeMapper.hxx>
#include <TransferBRep.hxx>
#include <Transfer_Binder.hxx>

#include <APIHeaderSection_MakeHeader.hxx>
#include <StepRepr_RepresentationItem.hxx>
#include <StepRepr_RepresentationContext.hxx>
#include <StepRepr_HArray1OfRepresentationItem.hxx>
#include <StepGeom_GeometricRepresentationItem.hxx>
#include <StepShape_ShapeRepresentation.hxx>
#include <StepVisual_ColourRgb.hxx>
#include <StepVisual_FillAreaStyleColour.hxx>
#include <StepVisual_FillStyleSelect.hxx>
#include <StepVisual_HArray1OfFillStyleSelect.hxx>
#include <StepVisual_FillAreaStyle.hxx>
#include <StepVisual_SurfaceStyleFillArea.hxx>
#include <StepVisual_SurfaceStyleElementSelect.hxx>
#include <StepVisual_HArray1OfSurfaceStyleElementSelect.hxx>
#include <StepVisual_SurfaceSideStyle.hxx>
#include <StepVisual_SurfaceStyleUsage.hxx>
#include <StepVisual_PresentationStyleSelect.hxx>
#include <StepVisual_HArray1OfPresentationStyleSelect.hxx>
#include <StepVisual_PresentationStyleAssignment.hxx>
#include <StepVisual_HArray1OfPresentationStyleAssignment.hxx>
#include <StepVisual_OverRidingStyledItem.hxx>
#include <StepVisual_StyledItem.hxx>
#include <StepVisual_MechanicalDesignGeometricPresentationRepresentation.hxx>
#include <StepVisual_PreDefinedColour.hxx>
#include <StepVisual_PreDefinedItem.hxx>
#include <StepVisual_CurveStyle.hxx>
#include <StepVisual_DraughtingPreDefinedCurveFont.hxx>
#include <StepVisual_SurfaceStyleBoundary.hxx>
#include <StepVisual_DraughtingPreDefinedColour.hxx>
#include <StepBasic_MeasureValueMember.hxx>
#include <StepVisual_DraughtingModel.hxx>
#include <StepVisual_PresentationStyleByContext.hxx>
#include <StepRepr_ProductDefinitionShape.hxx>
#include <StepShape_ShapeDefinitionRepresentation.hxx>
#include <StepRepr_ShapeRepresentationRelationship.hxx>
#include <StepRepr_RepresentationRelationshipWithTransformation.hxx>
#include <StepRepr_Transformation.hxx>
#include <StepRepr_ItemDefinedTransformation.hxx>
#include <StepVisual_Invisibility.hxx>
#include <TColStd_HSequenceOfTransient.hxx>
#include <StepVisual_InvisibleItem.hxx>
#include <gp_Pnt.hxx>


//=======================================================================
//function : STEPConstruct_Styles
//purpose  : 
//=======================================================================

STEPConstruct_Styles::STEPConstruct_Styles () 
{
}
     

//=======================================================================
//function : STEPConstruct_Styles
//purpose  : 
//=======================================================================

STEPConstruct_Styles::STEPConstruct_Styles (const Handle(XSControl_WorkSession) &WS)
     : STEPConstruct_Tool ( WS )
{
}


//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

Standard_Boolean STEPConstruct_Styles::Init (const Handle(XSControl_WorkSession) &WS)
{
  myMapOfStyles.Clear();
  myStyles.Clear();
  myPSA.Clear();
  return SetWS ( WS );
}


//=======================================================================
//function : NbStyles
//purpose  : 
//=======================================================================

Standard_Integer STEPConstruct_Styles::NbStyles () const
{
  return myStyles.Length();
}


//=======================================================================
//function : Style
//purpose  : 
//=======================================================================

Handle(StepVisual_StyledItem) STEPConstruct_Styles::Style (const Standard_Integer i) const
{
  return Handle(StepVisual_StyledItem)::DownCast ( myStyles.Value(i) );
}


//=======================================================================
//function : ClearStyles
//purpose  : 
//=======================================================================

void STEPConstruct_Styles::ClearStyles () 
{
  myStyles.Clear();
  myPSA.Clear();
}


//=======================================================================
//function : AddStyle
//purpose  : 
//=======================================================================

void STEPConstruct_Styles::AddStyle (const Handle(StepVisual_StyledItem) &style)
{
  myStyles.Append ( style );
}

  
//=======================================================================
//function : AddStyle
//purpose  : 
//=======================================================================

Handle(StepVisual_StyledItem) STEPConstruct_Styles::AddStyle (const Handle(StepRepr_RepresentationItem) &item,
							      const Handle(StepVisual_PresentationStyleAssignment) &PSA,
							      const Handle(StepVisual_StyledItem) &Override)
{
  Handle(StepVisual_StyledItem) Style;
  
  Handle(StepVisual_HArray1OfPresentationStyleAssignment) Styles = 
    new StepVisual_HArray1OfPresentationStyleAssignment ( 1, 1 );
  Styles->SetValue ( 1, PSA );
  
  if ( Override.IsNull() ) {
    Handle(TCollection_HAsciiString) StyName = new TCollection_HAsciiString ( "color" );
    Style = new StepVisual_StyledItem;
    Style->Init ( StyName, Styles, item );
  }
  else {
    Handle(TCollection_HAsciiString) StyName = new TCollection_HAsciiString ( "overriding color" );
    Handle(StepVisual_OverRidingStyledItem) OStyle = new StepVisual_OverRidingStyledItem;
    OStyle->Init ( StyName, Styles, item, Override );
    Style = OStyle;
  }
  
  myStyles.Append ( Style );
  // for future using
  myPSA.Append( PSA );
  
  return Style;
}


//=======================================================================
//function : AddStyle
//purpose  : 
//=======================================================================

Handle(StepVisual_StyledItem) STEPConstruct_Styles::AddStyle (const TopoDS_Shape &Shape,
							      const Handle(StepVisual_PresentationStyleAssignment) &PSA,
							      const Handle(StepVisual_StyledItem) &Override)
{
  Handle(StepRepr_RepresentationItem) item = STEPConstruct::FindEntity ( FinderProcess(), Shape );
  Handle(StepVisual_StyledItem) Style;
  if ( ! item.IsNull() ) Style = AddStyle ( item, PSA, Override );
  return Style;
}


//=======================================================================
//function : CreateMDGPR
//purpose  : 
//=======================================================================

Standard_Boolean STEPConstruct_Styles::CreateMDGPR (const Handle(StepRepr_RepresentationContext) &Context,
                                                    Handle(StepVisual_MechanicalDesignGeometricPresentationRepresentation)& Repr)
{
  if ( myStyles.Length() <1 ) return Standard_False;
  
  // create MECHANICAL_DESIGN_GEOMETRIC_PRESENTATION_REPRESENTATION
  Handle(StepRepr_HArray1OfRepresentationItem) elems = 
    new StepRepr_HArray1OfRepresentationItem ( 1, myStyles.Length() );
  for ( Standard_Integer i=1; i <= myStyles.Length(); i++ ) 
    elems->SetValue ( i, Handle(StepRepr_RepresentationItem)::DownCast ( myStyles.Value(i) ) );
  // create new MDGPR
  Repr = new StepVisual_MechanicalDesignGeometricPresentationRepresentation;
  Handle(TCollection_HAsciiString) ReprName = new TCollection_HAsciiString ( "" );
  Repr->Init ( ReprName, elems, Context );

  // record Repr in order to have it written to the file
//   Model()->AddWithRefs ( Repr ); add into the model upper

  // for AP203, add subschema name
  if ( Interface_Static::IVal("write.step.schema") ==3 ) {
    APIHeaderSection_MakeHeader mkHdr ( Handle(StepData_StepModel)::DownCast ( Model() ) );
    Handle(TCollection_HAsciiString) subSchema = 
      new TCollection_HAsciiString ( "SHAPE_APPEARANCE_LAYER_MIM" );
    mkHdr.AddSchemaIdentifier ( subSchema );
  }
  
  return Standard_True;
}


//=======================================================================
//function : CreateNAUOSRD
//purpose  : 
//=======================================================================

Standard_Boolean STEPConstruct_Styles::CreateNAUOSRD (const Handle(StepRepr_RepresentationContext) &Context,
                                                      const Handle(StepShape_ContextDependentShapeRepresentation)& CDSR,
                                                      const Handle(StepRepr_ProductDefinitionShape)& initPDS)
{
  Handle(StepShape_ShapeDefinitionRepresentation) aSDR =
    new StepShape_ShapeDefinitionRepresentation;
  Handle(StepShape_ShapeRepresentation) aSR =
    new StepShape_ShapeRepresentation;
  Handle(TCollection_HAsciiString) ReprName = new TCollection_HAsciiString ( "" );
  // element for axis 2 placement
  Handle(StepRepr_HArray1OfRepresentationItem) elems = 
    new StepRepr_HArray1OfRepresentationItem ( 1, 1 );
  // get PDS
  Handle(StepRepr_ProductDefinitionShape) aPDS;
  if ( initPDS.IsNull() )
    aPDS = CDSR->RepresentedProductRelation();
  else
    aPDS = initPDS; // for SHUO
  Handle(StepRepr_ShapeRepresentationRelationship) aRepRelationShip = CDSR->RepresentationRelation();
  Handle(StepRepr_RepresentationRelationshipWithTransformation) aRRwTRSF =
    Handle(StepRepr_RepresentationRelationshipWithTransformation)::DownCast(aRepRelationShip);
  StepRepr_Transformation SetReprTRSF;
  if (!aRRwTRSF.IsNull())
    SetReprTRSF = aRRwTRSF->TransformationOperator();
  else
    return Standard_False;
  // take Item defined transformation
  Handle(StepRepr_ItemDefinedTransformation) anItDT = SetReprTRSF.ItemDefinedTransformation();
  elems->SetValue( 1, anItDT->TransformItem2() );
  // init Shape representation.
  aSR->Init ( ReprName, elems, Context );
  // register reference between PresentationStyleByContext and ShapeRepresentation
  for (Standard_Integer psbci = 1; psbci <= myPSA.Length(); psbci++) {
    Handle(StepVisual_PresentationStyleByContext) PSA =
      Handle(StepVisual_PresentationStyleByContext)::DownCast(myPSA.Value(psbci));
    if (PSA.IsNull())
      continue;
    // register the reference
    StepVisual_StyleContextSelect aStyleCntxSlct;
    aStyleCntxSlct.SetValue( aSR );
    PSA->SetStyleContext( aStyleCntxSlct );
  }
  
  StepRepr_RepresentedDefinition aPDSselect;
  aPDSselect.SetValue(aPDS);
  aSDR->Init( aPDSselect, aSR );
  Model()->AddWithRefs ( aSDR );
  
  return Standard_True;
}


//=======================================================================
//function : FindContext
//purpose  : 
//=======================================================================

Handle(StepRepr_RepresentationContext) STEPConstruct_Styles::FindContext (const TopoDS_Shape &Shape) const
{
  // find context of items
  Handle(StepRepr_RepresentationContext) Context;
  Handle(TransferBRep_ShapeMapper) mapper = TransferBRep::ShapeMapper ( FinderProcess(), Shape );
  Handle(StepShape_ShapeRepresentation) sr;
  if ( FinderProcess()->FindTypedTransient (mapper,STANDARD_TYPE(StepShape_ShapeRepresentation), sr) ) {
#ifdef DEB
//    cout << "Context of " << Shape.TShape()->DynamicType()->Name() << ": SR found: " << sr->DynamicType()->Name() << endl;
#endif
    Context = sr->ContextOfItems();
  }
  else {
    Handle(StepGeom_GeometricRepresentationItem) item;
    if ( FinderProcess()->FindTypedTransient (mapper,STANDARD_TYPE(StepGeom_GeometricRepresentationItem), item) ) {
#ifdef DEB
//      cout << "Context of " << Shape.TShape()->DynamicType()->Name() << ": GeomRepItem found: " << item->DynamicType()->Name() << endl;
#endif
      Interface_EntityIterator subs = Graph().Sharings(item);
      for (subs.Start(); Context.IsNull() && subs.More(); subs.Next()) {
#ifdef DEB
//	cout << "Parsing back refs: found " << subs.Value()->DynamicType()->Name() << endl;
#endif
	if ( ! subs.Value()->IsKind(STANDARD_TYPE(StepShape_ShapeRepresentation)) ) continue;
	sr = Handle(StepShape_ShapeRepresentation)::DownCast ( subs.Value() );
	Context = sr->ContextOfItems();
      }
    }
  }
#ifdef DEB
  if ( Context.IsNull() ) {
    cout << Shape.TShape()->DynamicType()->Name() << ": Cannot find context" << endl;
  }
#endif

  return Context;
}


//=======================================================================
//function : LoadStyles
//purpose  : 
//=======================================================================

Standard_Boolean STEPConstruct_Styles::LoadStyles ()
{
  myStyles.Clear();
  myPSA.Clear();
  
  // find all MDGPRs and DMs and collect all defined styles in myStyles
  Handle(Interface_InterfaceModel) model = Model();
  Standard_Integer nb = model->NbEntities();
  Handle(Standard_Type) tMDGPR = STANDARD_TYPE(StepVisual_MechanicalDesignGeometricPresentationRepresentation);
  Handle(Standard_Type) tDM = STANDARD_TYPE(StepVisual_DraughtingModel);
  for (Standard_Integer i = 1; i <= nb; i ++) {
    Handle(Standard_Transient) enti = model->Value(i);
    if ( enti->DynamicType() != tMDGPR && enti->DynamicType() != tDM ) continue;

    Handle(StepRepr_Representation) container = Handle(StepRepr_Representation)::DownCast ( enti );

    Standard_Integer nbi = container->NbItems();
    for ( Standard_Integer j=1; j <= nbi; j++ ) {
      Handle(StepVisual_StyledItem) style = 
	Handle(StepVisual_StyledItem)::DownCast ( container->ItemsValue(j) );
      if ( style.IsNull() ) continue;
      myStyles.Append ( style );
    }
  }
  return myStyles.Length() >0;
}


//=======================================================================
//function : LoadInvisStyles
//purpose  : 
//=======================================================================

Standard_Boolean STEPConstruct_Styles::LoadInvisStyles (Handle(TColStd_HSequenceOfTransient)& theInvStyles) const
{
  Handle(Interface_InterfaceModel) model = Model();
  Standard_Integer nb = model->NbEntities();
  Handle(Standard_Type) tInvisibility = STANDARD_TYPE(StepVisual_Invisibility);
  // serach for invisibility
  for (Standard_Integer i = 1; i <= nb; i ++) {
    Handle(Standard_Transient) enti = model->Value(i);
    if ( enti->DynamicType() != tInvisibility )
      continue;
    // search for styled items
    Handle(StepVisual_Invisibility) container = Handle(StepVisual_Invisibility)::DownCast ( enti );
    Standard_Integer nbi = container->NbInvisibleItems();
    for ( Standard_Integer j=1; j <= nbi; j++ ) {
      StepVisual_InvisibleItem anInvItem = container->InvisibleItemsValue(j);
      Handle(StepVisual_StyledItem) style = anInvItem.StyledItem();
      if ( style.IsNull() ) 
        continue;
      // collect the invisible styled items
      if ( theInvStyles.IsNull() )
        theInvStyles = new TColStd_HSequenceOfTransient;
      theInvStyles->Append( style );
    }
  }
  return ( !theInvStyles.IsNull() && (theInvStyles->Length() > 0) );
}


//=======================================================================
//function : MakeColorPSA
//purpose  : 
//=======================================================================

Handle(StepVisual_PresentationStyleAssignment) STEPConstruct_Styles::MakeColorPSA (const Handle(StepRepr_RepresentationItem) &/*item*/,
										   const Handle(StepVisual_Colour) &SurfCol, 
										   const Handle(StepVisual_Colour) &CurveCol,
                                                                                   const Standard_Boolean isForNAUO) const
{  
  Handle(StepVisual_PresentationStyleAssignment) PSA;
  TColStd_SequenceOfTransient items;
  
  // surface color
  if ( ! SurfCol.IsNull() ) {
    Handle(TCollection_HAsciiString) FASCName = new TCollection_HAsciiString ( "" );
    Handle(StepVisual_FillAreaStyleColour) FASC = new StepVisual_FillAreaStyleColour;
    FASC->Init ( FASCName, SurfCol );
  
    StepVisual_FillStyleSelect FSS;
    FSS.SetValue ( FASC );
  
    Handle(StepVisual_HArray1OfFillStyleSelect) FASSs = new StepVisual_HArray1OfFillStyleSelect ( 1, 1 );
    FASSs->SetValue ( 1, FSS );
  
    Handle(TCollection_HAsciiString) FASName = new TCollection_HAsciiString ( "" );
    Handle(StepVisual_FillAreaStyle) FAS = new StepVisual_FillAreaStyle;
    FAS->Init ( FASName, FASSs );

    Handle(StepVisual_SurfaceStyleFillArea) SSFA = new StepVisual_SurfaceStyleFillArea;
    SSFA->Init ( FAS );
    
    StepVisual_SurfaceStyleElementSelect SES;
    SES.SetValue ( SSFA );
  
    Handle(StepVisual_HArray1OfSurfaceStyleElementSelect) SSESs = 
      new StepVisual_HArray1OfSurfaceStyleElementSelect ( 1, 1 );
    SSESs->SetValue ( 1, SES );
  
    Handle(TCollection_HAsciiString) SSSName = new TCollection_HAsciiString ( "" );
    Handle(StepVisual_SurfaceSideStyle) SSS = new StepVisual_SurfaceSideStyle;
    SSS->Init ( SSSName, SSESs );
  
    Handle(StepVisual_SurfaceStyleUsage) SSU = new StepVisual_SurfaceStyleUsage;
    SSU->Init ( StepVisual_ssBoth, SSS );
    
    items.Append ( SSU );
  }
  
  // curve color
  if ( ! CurveCol.IsNull() ) {
    Handle(TCollection_HAsciiString) fontName = new TCollection_HAsciiString("continuous");
    Handle(StepVisual_DraughtingPreDefinedCurveFont) SDPDCF = new StepVisual_DraughtingPreDefinedCurveFont;
    SDPDCF->Init(fontName);
  
    Handle(StepBasic_MeasureValueMember) Val = new StepBasic_MeasureValueMember;
    Val->SetReal ( 0.1 );
    Val->SetName ( "POSITIVE_LENGTH_MEASURE");
    
    StepVisual_CurveStyleFontSelect SCSFS;
    SCSFS.SetValue(SDPDCF);
    
    StepBasic_SizeSelect SSSelect;
    SSSelect.SetValue(Val);
  
    Handle(TCollection_HAsciiString) SCSName = new TCollection_HAsciiString ( "" );
    Handle(StepVisual_CurveStyle) SCS = new StepVisual_CurveStyle;
    SCS->Init(SCSName,SCSFS,SSSelect,CurveCol);

    items.Append ( SCS );
  }
  
  if ( items.Length() <1 ) {
#ifdef DEB
    cout << "Error: no color is supplied" << endl;
#endif
    return PSA;
  }
  
  // general part
  Handle(StepVisual_HArray1OfPresentationStyleSelect) PSSs = 
    new StepVisual_HArray1OfPresentationStyleSelect ( 1, items.Length() );
  for ( Standard_Integer i=1; i <= items.Length(); i++ ) {
    StepVisual_PresentationStyleSelect PSS;
    PSS.SetValue ( items.Value(i) );
    PSSs->SetValue ( i, PSS );
  }
  if (!isForNAUO)
    PSA = new StepVisual_PresentationStyleAssignment;
  else 
    PSA = new StepVisual_PresentationStyleByContext;
  PSA->Init ( PSSs );
  
  return PSA;
}


//=======================================================================
//function : GetColorPSA
//purpose  : 
//=======================================================================

Handle(StepVisual_PresentationStyleAssignment) STEPConstruct_Styles::GetColorPSA (const Handle(StepRepr_RepresentationItem) &item,
										  const Handle(StepVisual_Colour) &Col) 
{
  // if this color already was processed, just use the same PSA, else create new and add it to map
  Handle(StepVisual_PresentationStyleAssignment) PSA;
  if ( myMapOfStyles.Contains(Col) ) {
    PSA = Handle(StepVisual_PresentationStyleAssignment)::
      DownCast(myMapOfStyles.FindFromKey(Col));
  }
  else {
    PSA = MakeColorPSA ( item, Col, Col );
    myMapOfStyles.Add(Col,PSA);
  }
  return PSA;
}
  

//=======================================================================
//function : GetColors
//purpose  : 
//=======================================================================

Standard_Boolean STEPConstruct_Styles::GetColors (const Handle(StepVisual_StyledItem) &style,
						  Handle(StepVisual_Colour) &SurfCol,
						  Handle(StepVisual_Colour) &BoundCol,
						  Handle(StepVisual_Colour) &CurveCol,
                                                  Standard_Boolean& IsComponent) const
{
  SurfCol.Nullify();
  BoundCol.Nullify();
  CurveCol.Nullify();
    
  // parse on styles
  for(Standard_Integer j=1; j<=style->NbStyles(); j++ ) {
    Handle(StepVisual_PresentationStyleAssignment) PSA = style->StylesValue ( j );
    if(PSA.IsNull()) continue;
    IsComponent = Standard_True;
    
    for(Standard_Integer k=1; k<=PSA->NbStyles(); k++ ) {
      StepVisual_PresentationStyleSelect PSS = PSA->StylesValue(k);

      // try surface_style_usage
      Handle(StepVisual_SurfaceStyleUsage) SSU = PSS.SurfaceStyleUsage();
      if( !SSU.IsNull() ) {
	Handle(StepVisual_SurfaceSideStyle) SSS = SSU->Style();
	for(Standard_Integer l=1; l<=SSS->NbStyles(); l++ ) {
	  StepVisual_SurfaceStyleElementSelect SSES = SSS->StylesValue(l);
	  // try fill color
	  Handle(StepVisual_SurfaceStyleFillArea) SSFA = SSES.SurfaceStyleFillArea();
	  if ( !SSFA.IsNull() ) {
	    Handle(StepVisual_FillAreaStyle) FAS = SSFA->FillArea();
	    for ( Standard_Integer m=1; m <= FAS->NbFillStyles(); m++ ) {
	      StepVisual_FillStyleSelect FSS = FAS->FillStylesValue ( m );
	      Handle(StepVisual_FillAreaStyleColour) FASC = FSS.FillAreaStyleColour();
	      if ( SurfCol.IsNull() || SSU->Side() != StepVisual_ssNegative ) //abv 30 Mar 00: trj3_s1-pe.stp
		SurfCol = FASC->FillColour();
	    }
	    continue;
	  }
	  // try boundary color
	  Handle(StepVisual_SurfaceStyleBoundary) SSB = SSES.SurfaceStyleBoundary();
	  if(!SSB.IsNull()) {
	    Handle(StepVisual_CurveStyle) CS = SSB->StyleOfBoundary();
	    if ( ! CS.IsNull() ) BoundCol = CS->CurveColour();
	    continue;
	  }
	}
	continue;
      }
      
      // try curve_style
      Handle(StepVisual_CurveStyle) CS = PSS.CurveStyle();
      if ( ! CS.IsNull() ) CurveCol = CS->CurveColour();
    }
  }
  return ! SurfCol.IsNull() || ! BoundCol.IsNull() || ! CurveCol.IsNull();
}


//=======================================================================
//function : EncodeColor
//purpose  : 
//=======================================================================

Handle(StepVisual_Colour) STEPConstruct_Styles::EncodeColor(const Quantity_Color &C)
{
  // detect if color corresponds to one of pre-defined colors
  Standard_CString cName = 0;
  if      ( C == Quantity_Color(Quantity_NOC_GREEN) )    cName = "green";
  else if ( C == Quantity_Color(Quantity_NOC_RED) )      cName = "red";
  else if ( C == Quantity_Color(Quantity_NOC_BLUE1) )    cName = "blue";
  else if ( C == Quantity_Color(Quantity_NOC_YELLOW) )   cName = "yellow";
  else if ( C == Quantity_Color(Quantity_NOC_MAGENTA1) ) cName = "magenta";
  else if ( C == Quantity_Color(Quantity_NOC_CYAN1) )    cName = "cyan";
  else if ( C == Quantity_Color(Quantity_NOC_BLACK) )    cName = "black";
  else if ( C == Quantity_Color(Quantity_NOC_WHITE) )    cName = "white";
  
  if ( cName ) {
    Handle(StepVisual_DraughtingPreDefinedColour) ColPr = new StepVisual_DraughtingPreDefinedColour;
    Handle(StepVisual_PreDefinedItem) preDef = new StepVisual_PreDefinedItem;
    preDef->Init(new TCollection_HAsciiString(cName));
    ColPr->SetPreDefinedItem(preDef);
    return ColPr;
  }
  else {
    Handle(TCollection_HAsciiString) ColName = new TCollection_HAsciiString ( "" );
    Handle(StepVisual_ColourRgb) ColRGB = new StepVisual_ColourRgb;
    ColRGB->Init ( ColName, C.Red(), C.Green(), C.Blue() );
    return ColRGB;
  }
}


//=======================================================================
//function : EncodeColor
//purpose  : 
//=======================================================================

Handle(StepVisual_Colour) STEPConstruct_Styles::EncodeColor
       (const Quantity_Color &C,
        STEPConstruct_DataMapOfAsciiStringTransient &DPDCs,
        STEPConstruct_DataMapOfPointTransient &ColRGBs)
{
  // detect if color corresponds to one of pre-defined colors
  Standard_CString cName = 0;
  if      ( C == Quantity_Color(Quantity_NOC_GREEN) )    cName = "green";
  else if ( C == Quantity_Color(Quantity_NOC_RED) )      cName = "red";
  else if ( C == Quantity_Color(Quantity_NOC_BLUE1) )    cName = "blue";
  else if ( C == Quantity_Color(Quantity_NOC_YELLOW) )   cName = "yellow";
  else if ( C == Quantity_Color(Quantity_NOC_MAGENTA1) ) cName = "magenta";
  else if ( C == Quantity_Color(Quantity_NOC_CYAN1) )    cName = "cyan";
  else if ( C == Quantity_Color(Quantity_NOC_BLACK) )    cName = "black";
  else if ( C == Quantity_Color(Quantity_NOC_WHITE) )    cName = "white";
  
  if ( cName ) {
    Handle(StepVisual_DraughtingPreDefinedColour) ColPr;
    TCollection_AsciiString aName(cName);
    if(DPDCs.IsBound(aName)) {
      ColPr = Handle(StepVisual_DraughtingPreDefinedColour)::DownCast(DPDCs.Find(aName));
      if(!ColPr.IsNull()) return ColPr;
    }
    ColPr = new StepVisual_DraughtingPreDefinedColour;
    Handle(StepVisual_PreDefinedItem) preDef = new StepVisual_PreDefinedItem;
    preDef->Init(new TCollection_HAsciiString(cName));
    ColPr->SetPreDefinedItem(preDef);
    DPDCs.Bind(aName,ColPr);
    return ColPr;
  }
  else {
    Handle(StepVisual_ColourRgb) ColRGB;
    gp_Pnt P(C.Red(),C.Green(),C.Blue());
    if(ColRGBs.IsBound(P)) {
      ColRGB = Handle(StepVisual_ColourRgb)::DownCast(ColRGBs.Find(P));
      if(!ColRGB.IsNull()) return ColRGB;
    }
    Handle(TCollection_HAsciiString) ColName = new TCollection_HAsciiString ( "" );
    ColRGB = new StepVisual_ColourRgb;
    ColRGB->Init ( ColName, C.Red(), C.Green(), C.Blue() );
    ColRGBs.Bind(P,ColRGB);
    return ColRGB;
  }
}


//=======================================================================
//function : DecodeColor
//purpose  : 
//=======================================================================

Standard_Boolean STEPConstruct_Styles::DecodeColor (const Handle(StepVisual_Colour) &Colour, Quantity_Color &Col) 
{
  if ( Colour->IsKind (STANDARD_TYPE(StepVisual_ColourRgb)) ) {
    Handle(StepVisual_ColourRgb) rgb = Handle(StepVisual_ColourRgb)::DownCast ( Colour );
    if( rgb->Red()>1. || rgb->Green()>1. || rgb->Blue()>1. ) {
      Standard_Real norm = rgb->Red();
      if(norm<rgb->Green()) norm = rgb->Green();
      if(norm<rgb->Blue()) norm = rgb->Blue();
      Col.SetValues(rgb->Red()/norm, rgb->Green()/norm,
                    rgb->Blue()/norm, Quantity_TOC_RGB);
    }
    else
      Col.SetValues(rgb->Red(), rgb->Green(), rgb->Blue(), Quantity_TOC_RGB);
    return Standard_True;
  }
  else if ( Colour->IsKind (STANDARD_TYPE(StepVisual_PreDefinedColour)) ) {
    Handle(StepVisual_PreDefinedColour) pdc = 
      Handle(StepVisual_PreDefinedColour)::DownCast ( Colour );
    Handle(StepVisual_PreDefinedItem) pdi = pdc->GetPreDefinedItem();
    const TCollection_AsciiString name = pdi->Name()->String();
    if      ( name.IsEqual ( "red"     ) ) Col.SetValues ( Quantity_NOC_RED );
    else if ( name.IsEqual ( "green"   ) ) Col.SetValues ( Quantity_NOC_GREEN );
    else if ( name.IsEqual ( "blue"    ) ) Col.SetValues ( Quantity_NOC_BLUE1 );
    else if ( name.IsEqual ( "yellow"  ) ) Col.SetValues ( Quantity_NOC_YELLOW );
    else if ( name.IsEqual ( "magenta" ) ) Col.SetValues ( Quantity_NOC_MAGENTA1 );
    else if ( name.IsEqual ( "cyan"    ) ) Col.SetValues ( Quantity_NOC_CYAN1 );
    else if ( name.IsEqual ( "black"   ) ) Col.SetValues ( Quantity_NOC_BLACK );
    else if ( name.IsEqual ( "white"   ) ) Col.SetValues ( Quantity_NOC_WHITE );
    else {
#ifdef DEB
      cout << "Error: color name \"" << name << "\" is not recognized" << endl;
#endif
      return Standard_False;
    }
    return Standard_True;
  }
  return Standard_False;
}

