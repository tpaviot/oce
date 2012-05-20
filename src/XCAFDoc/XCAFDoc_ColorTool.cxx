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

#include <XCAFDoc_ColorTool.ixx>
#include <XCAFDoc.hxx>
#include <XCAFDoc_Color.hxx>

#include <TDF_ChildIDIterator.hxx>
#include <TDataStd_TreeNode.hxx>
#include <TDataStd_Name.hxx>
#include <TNaming_NamedShape.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_Color.hxx>
#include <TDataStd_UAttribute.hxx>
#include <XCAFDoc_GraphNode.hxx>

#define AUTONAMING // automatically set names for labels

//=======================================================================
//function : BaseLabel
//purpose  : 
//=======================================================================

TDF_Label XCAFDoc_ColorTool::BaseLabel() const
{
  return Label();
}
//=======================================================================
//function : ShapeTool
//purpose  : 
//=======================================================================

const Handle(XCAFDoc_ShapeTool)& XCAFDoc_ColorTool::ShapeTool() 
{
  if (myShapeTool.IsNull())
    myShapeTool = XCAFDoc_DocumentTool::ShapeTool(Label());
  return myShapeTool;
}


//=======================================================================
//function : IsColor
//purpose  : 
//=======================================================================

Standard_Boolean XCAFDoc_ColorTool::IsColor (const TDF_Label& lab) const
{
  Quantity_Color C;
  return GetColor ( lab, C );
}

//=======================================================================
//function : GetColor
//purpose  : 
//=======================================================================

Standard_Boolean XCAFDoc_ColorTool::GetColor (const TDF_Label& lab,
					       Quantity_Color& col) const
{
  if ( lab.Father() != Label() ) return Standard_False;
  
  Handle(XCAFDoc_Color) ColorAttribute;
  if ( ! lab.FindAttribute ( XCAFDoc_Color::GetID(), ColorAttribute ))
    return Standard_False;
  
  col = ColorAttribute->GetColor();
  
  return Standard_True;
}

//=======================================================================
//function : FindColor
//purpose  : 
//=======================================================================

Standard_Boolean XCAFDoc_ColorTool::FindColor (const Quantity_Color& col, TDF_Label& lab) const
{
  TDF_ChildIDIterator it(Label(),XCAFDoc_Color::GetID());
  for (; it.More(); it.Next()) {
    TDF_Label aLabel = it.Value()->Label();
    Quantity_Color C;
    if ( ! GetColor ( aLabel, C ) ) continue;
    if ( C.IsEqual ( col ) ) {
      lab = aLabel;
      return Standard_True;
    }
  }
  return Standard_False;
}

//=======================================================================
//function : FindColor
//purpose  : 
//=======================================================================

TDF_Label XCAFDoc_ColorTool::FindColor (const Quantity_Color& col) const
{
  TDF_Label L;
  FindColor ( col, L );
  return L;
}

//=======================================================================
//function : AddColor
//purpose  : 
//=======================================================================

TDF_Label XCAFDoc_ColorTool::AddColor (const Quantity_Color& col) const
{
  TDF_Label L;
  if ( FindColor ( col, L ) ) return L;

  // create a new color entry
  
  TDF_TagSource aTag;
  L = aTag.NewChild ( Label() );

  XCAFDoc_Color::Set(L, col);
  
#ifdef AUTONAMING
  // set name according to color value
  TCollection_AsciiString str;
  str += col.StringName ( col.Name() );
  str += " (";
  str += TCollection_AsciiString ( col.Red() );
  str += ",";
  str += TCollection_AsciiString ( col.Green() );
  str += ",";
  str += TCollection_AsciiString ( col.Blue() );
  str += ")";
  TDataStd_Name::Set ( L, str );
#endif
  
  return L;
}

//=======================================================================
//function : RemoveColor
//purpose  : 
//=======================================================================

void XCAFDoc_ColorTool::RemoveColor (const TDF_Label& lab) const
{
  lab.ForgetAllAttributes (Standard_True);
}

//=======================================================================
//function : GetColors
//purpose  : 
//=======================================================================

void XCAFDoc_ColorTool::GetColors (TDF_LabelSequence& Labels) const
{
  Labels.Clear();

  TDF_ChildIDIterator ChildIDIterator(Label(),XCAFDoc_Color::GetID()); 
  for (; ChildIDIterator.More(); ChildIDIterator.Next()) {
    TDF_Label L = ChildIDIterator.Value()->Label();
    if ( IsColor ( L ) ) Labels.Append ( L );
  }
}

//=======================================================================
//function : SetColor
//purpose  : 
//=======================================================================

void XCAFDoc_ColorTool::SetColor (const TDF_Label& L,
			       const TDF_Label& colorL,
			       const XCAFDoc_ColorType type) const
{
  // set reference
  Handle(TDataStd_TreeNode) refNode, mainNode;
  mainNode = TDataStd_TreeNode::Set ( colorL, XCAFDoc::ColorRefGUID(type) );
  refNode  = TDataStd_TreeNode::Set ( L,      XCAFDoc::ColorRefGUID(type) );
  refNode->Remove(); // abv: fix against bug in TreeNode::Append()
  mainNode->Prepend(refNode);
}

//=======================================================================
//function : SetColor
//purpose  : 
//=======================================================================

void XCAFDoc_ColorTool::SetColor (const TDF_Label& L,
			       const Quantity_Color& Color,
			       const XCAFDoc_ColorType type) const
{
  TDF_Label colorL = AddColor ( Color );
  SetColor ( L, colorL, type );
}

//=======================================================================
//function : UnSetColor
//purpose  : 
//=======================================================================

void XCAFDoc_ColorTool::UnSetColor (const TDF_Label& L, const XCAFDoc_ColorType type) const
{
  L.ForgetAttribute ( XCAFDoc::ColorRefGUID(type) );
}

//=======================================================================
//function : IsSet
//purpose  : 
//=======================================================================

Standard_Boolean XCAFDoc_ColorTool::IsSet (const TDF_Label& L, const XCAFDoc_ColorType type) const
{
  Handle(TDataStd_TreeNode) Node;
  return L.FindAttribute ( XCAFDoc::ColorRefGUID(type), Node) && Node->HasFather();
}

//=======================================================================
//function : GetColor
//purpose  : 
//=======================================================================

Standard_Boolean XCAFDoc_ColorTool::GetColor (const TDF_Label& L,
					   const XCAFDoc_ColorType type,
					   TDF_Label& colorL) 
{
  Handle(TDataStd_TreeNode) Node;
  if ( ! L.FindAttribute ( XCAFDoc::ColorRefGUID(type), Node) ||
       ! Node->HasFather() ) return Standard_False;
  colorL = Node->Father()->Label();
  return Standard_True;
}

//=======================================================================
//function : GetColor
//purpose  : 
//=======================================================================

Standard_Boolean XCAFDoc_ColorTool::GetColor (const TDF_Label& L,
					   const XCAFDoc_ColorType type,
					   Quantity_Color& color) 
{
  TDF_Label colorL;
  if ( ! GetColor ( L, type, colorL ) ) return Standard_False;
  return GetColor ( colorL, color );
}

//=======================================================================
//function : SetColor
//purpose  : 
//=======================================================================

Standard_Boolean XCAFDoc_ColorTool::SetColor (const TopoDS_Shape& S,
					   const TDF_Label& colorL,
					   const XCAFDoc_ColorType type) 
{
  TDF_Label L;
  if ( ! ShapeTool()->Search ( S, L ) ) return Standard_False;
  SetColor ( L, colorL, type );
  return Standard_True;
}

//=======================================================================
//function : SetColor
//purpose  : 
//=======================================================================

Standard_Boolean XCAFDoc_ColorTool::SetColor (const TopoDS_Shape& S,
					   const Quantity_Color& Color,
					   const XCAFDoc_ColorType type) 
{
  TDF_Label colorL = AddColor ( Color );
  return SetColor ( S, colorL, type );
}

//=======================================================================
//function : UnSetColor
//purpose  : 
//=======================================================================

Standard_Boolean XCAFDoc_ColorTool::UnSetColor (const TopoDS_Shape& S,
					     const XCAFDoc_ColorType type) 
{
  TDF_Label L;
  if ( ! ShapeTool()->Search ( S, L ) ) return Standard_False;
  UnSetColor ( L, type );
  return Standard_True;
}

//=======================================================================
//function : IsSet
//purpose  : 
//=======================================================================

Standard_Boolean XCAFDoc_ColorTool::IsSet (const TopoDS_Shape& S,
					const XCAFDoc_ColorType type) 
{
  TDF_Label L;
  if ( ! ShapeTool()->Search ( S, L ) ) return Standard_False;
  return IsSet ( L, type );
}

//=======================================================================
//function : GetColor
//purpose  : 
//=======================================================================

Standard_Boolean XCAFDoc_ColorTool::GetColor (const TopoDS_Shape& S, 
					   const XCAFDoc_ColorType type,
					   TDF_Label& colorL) 
{
  TDF_Label L;
  if ( ! ShapeTool()->Search ( S, L ) ) return Standard_False;
  return GetColor ( L, type, colorL );
}

//=======================================================================
//function : GetColor
//purpose  : 
//=======================================================================

Standard_Boolean XCAFDoc_ColorTool::GetColor (const TopoDS_Shape& S,
					   const XCAFDoc_ColorType type,
					   Quantity_Color& color) 
{
  TDF_Label colorL;
  if ( ! GetColor ( S, type, colorL ) ) return Standard_False;
  return GetColor ( colorL, color );
}

//=======================================================================
//function : GetID
//purpose  : 
//=======================================================================

const Standard_GUID& XCAFDoc_ColorTool::GetID() 
{
  static Standard_GUID ColorTblID ("efd212ed-6dfd-11d4-b9c8-0060b0ee281b");
  return ColorTblID; 
}

//=======================================================================
//function : Set
//purpose  : 
//=======================================================================

Handle(XCAFDoc_ColorTool) XCAFDoc_ColorTool::Set(const TDF_Label& L) 
{
  Handle(XCAFDoc_ColorTool) A;
  if (!L.FindAttribute (XCAFDoc_ColorTool::GetID(), A)) {
    A = new XCAFDoc_ColorTool ();
    L.AddAttribute(A);
    A->myShapeTool = XCAFDoc_DocumentTool::ShapeTool(L);
  }
  return A;
}

//=======================================================================
//function : ID
//purpose  : 
//=======================================================================

const Standard_GUID& XCAFDoc_ColorTool::ID() const
{
  return GetID();
}

//=======================================================================
//function : Restore
//purpose  : 
//=======================================================================

void XCAFDoc_ColorTool::Restore(const Handle(TDF_Attribute)& /*with*/) 
{
}

//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================

Handle(TDF_Attribute) XCAFDoc_ColorTool::NewEmpty() const
{
  return new XCAFDoc_ColorTool;
}

//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================

void XCAFDoc_ColorTool::Paste (const Handle(TDF_Attribute)& /*into*/,
			       const Handle(TDF_RelocationTable)& /*RT*/) const
{
}

/**/

//=======================================================================
//function : XCAFDoc_ColorTool
//purpose  : 
//=======================================================================

XCAFDoc_ColorTool::XCAFDoc_ColorTool()
{
}

// PTV 23.01.2003 add visibility flag for objects (CAX-IF TRJ11)
//=======================================================================
//function : IsVisible
//purpose  : 
//=======================================================================

Standard_Boolean XCAFDoc_ColorTool::IsVisible (const TDF_Label& L) const
{
  Handle(TDataStd_UAttribute) aUAttr;
  return (!L.FindAttribute(XCAFDoc::InvisibleGUID(), aUAttr));
}

//=======================================================================
//function : SetVisibility
//purpose  : 
//=======================================================================

void XCAFDoc_ColorTool::SetVisibility (const TDF_Label& L,
				       const Standard_Boolean isvisible)
{
  Handle(TDataStd_UAttribute) aUAttr;
  if (! isvisible ) {
    Handle(XCAFDoc_GraphNode) aSHUO;
    if (ShapeTool()->IsShape(L) || ShapeTool()->GetSHUO( L, aSHUO ) )
      if (!L.FindAttribute(XCAFDoc::InvisibleGUID(), aUAttr))
        aUAttr->Set( L, XCAFDoc::InvisibleGUID() );
  }
  else L.ForgetAttribute( XCAFDoc::InvisibleGUID() );
}

//=======================================================================
//function : SetInstanceColor
//purpose  : 
//=======================================================================

Standard_Boolean XCAFDoc_ColorTool::SetInstanceColor (const TopoDS_Shape& theShape,
                                                      const XCAFDoc_ColorType type,
                                                      const Quantity_Color& color,
                                                      const Standard_Boolean IsCreateSHUO)
{
  // find shuo label structure 
  TDF_LabelSequence aLabels;
  if ( !ShapeTool()->FindComponent( theShape, aLabels ) )
    return Standard_False;
  Handle(XCAFDoc_GraphNode) aSHUO;
  // set the SHUO structure for this component if it is not exist
  if ( !ShapeTool()->FindSHUO( aLabels, aSHUO ) ) {
    if (aLabels.Length() == 1) {
      // set color directly for component as NAUO
      SetColor(aLabels.Value(1), color, type);
      return Standard_True;
    }
    else if ( !IsCreateSHUO ||  !ShapeTool()->SetSHUO( aLabels, aSHUO ) )
      return Standard_False;
  }
  TDF_Label aSHUOLabel = aSHUO->Label();
  SetColor( aSHUOLabel, color, type );
  return Standard_True;
}

//=======================================================================
//function : GetInstanceColor
//purpose  : 
//=======================================================================

Standard_Boolean XCAFDoc_ColorTool::GetInstanceColor (const TopoDS_Shape& theShape,
                                                      const XCAFDoc_ColorType type,
                                                      Quantity_Color& color)
{
  // find shuo label structure 
  TDF_LabelSequence aLabels;
  if ( !ShapeTool()->FindComponent( theShape, aLabels ) )
    return Standard_False;
  Handle(XCAFDoc_GraphNode) aSHUO;
  // get shuo from document by label structure
  TDF_Label aCompLab = aLabels.Value(aLabels.Length());
  while (aLabels.Length() > 1) {
    if ( !ShapeTool()->FindSHUO( aLabels, aSHUO ) ) {
      // try to find other shuo 
      aLabels.Remove(aLabels.Length());
      continue;
    } else {
      TDF_Label aSHUOLabel = aSHUO->Label();
      if (GetColor ( aSHUOLabel, type, color ) )
        return Standard_True;
      else 
        // try to find other shuo 
        aLabels.Remove(aLabels.Length());
    }
  }
  // attempt to get color exactly of component
  if (GetColor( aCompLab, type, color ))
    return Standard_True;
  
  // attempt to get color of solid
  TopLoc_Location aLoc;
  TopoDS_Shape S0 = theShape;
  S0.Location( aLoc );
  TDF_Label aRefLab = ShapeTool()->FindShape( S0 );
  if (!aRefLab.IsNull())
    return GetColor( aRefLab, type, color );
  // no color assigned
  return Standard_False;
}

//=======================================================================
//function : IsInstanceVisible
//purpose  : 
//=======================================================================

Standard_Boolean XCAFDoc_ColorTool::IsInstanceVisible (const TopoDS_Shape& theShape)
{
  // check visibility status of top-level solid, cause it is have highest priority
  TopLoc_Location NullLoc;
  TopoDS_Shape S0 = theShape;
  S0.Location( NullLoc );
  TDF_Label aRefL = ShapeTool()->FindShape( S0 );
  if (!aRefL.IsNull() && !IsVisible(aRefL))
    return Standard_False;
  // find shuo label structure 
  TDF_LabelSequence aLabels;
  if ( !ShapeTool()->FindComponent( theShape, aLabels ) )
    return Standard_True;
  TDF_Label aCompLab = aLabels.Value(aLabels.Length());
  // visibility status of component withouts SHUO.
  if (!IsVisible( aCompLab ))
    return Standard_False;
  // check by SHUO structure
  TDF_LabelSequence aCurLabels;
  aCurLabels.Append(aCompLab);
  Standard_Integer i = aLabels.Length() - 1;
  //   while (aCurLabels.Length() < aLabels.Length()) {
  while (i >= 1) {
    aCurLabels.Prepend( aLabels.Value(i--) );
    // get shuo from document by label structure
    Handle(XCAFDoc_GraphNode) aSHUO;
    if ( !ShapeTool()->FindSHUO( aCurLabels, aSHUO ) )
      continue;
    if ( !IsVisible(aSHUO->Label()) )
      return Standard_False;
  }
  return Standard_True; //visible, cause cannot find invisibility status
}


//=======================================================================
//function : ReverseTreeNodes
//purpose  : auxilary
//=======================================================================
static void ReverseTreeNodes(Handle(TDataStd_TreeNode)& mainNode)
{
  if(mainNode->HasFirst()) {
    Handle(TDataStd_TreeNode) tmpNode;
    Handle(TDataStd_TreeNode) pNode = mainNode->First();
    Handle(TDataStd_TreeNode) nNode = pNode->Next();
    while(!nNode.IsNull()) {
      tmpNode = pNode->Previous();
      pNode->SetPrevious(nNode);
      pNode->SetNext(tmpNode);
      pNode = nNode;
      nNode = pNode->Next();
    }
    tmpNode = pNode->Previous();
    pNode->SetPrevious(nNode);
    pNode->SetNext(tmpNode);
    mainNode->SetFirst(pNode);
  }
}


//=======================================================================
//function : ReverseChainsOfTreeNodes
//purpose  : 
//=======================================================================

Standard_Boolean XCAFDoc_ColorTool::ReverseChainsOfTreeNodes()
{
  TDF_ChildIDIterator it(Label(),XCAFDoc_Color::GetID());
  for (; it.More(); it.Next()) {
    TDF_Label aLabel = it.Value()->Label();
    Handle(TDataStd_TreeNode) mainNode;
    if(aLabel.FindAttribute(XCAFDoc::ColorRefGUID(XCAFDoc_ColorSurf),mainNode)) {
      ReverseTreeNodes(mainNode);
    }
    if(aLabel.FindAttribute(XCAFDoc::ColorRefGUID(XCAFDoc_ColorCurv),mainNode)) {
      ReverseTreeNodes(mainNode);
    }
    if(aLabel.FindAttribute(XCAFDoc::ColorRefGUID(XCAFDoc_ColorGen),mainNode)) {
      ReverseTreeNodes(mainNode);
    }
  }
  return Standard_True;
}
