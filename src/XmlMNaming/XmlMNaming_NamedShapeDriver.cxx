// Created on: 2001-07-11
// Created by: Julia DOROVSKIKH
// Copyright (c) 2001-2012 OPEN CASCADE SAS
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

//AGV 150202: Changed prototype LDOM_Node::getOwnerDocument()

#include <XmlMNaming_NamedShapeDriver.ixx>

#include <XmlObjMgt.hxx>
#include <XmlMNaming_Array1OfShape1.hxx>
#include <XmlMNaming_Shape1.hxx>

#include <TDF_Label.hxx>
#include <TNaming_Builder.hxx>
#include <TNaming_NamedShape.hxx>
#include <TNaming_Iterator.hxx>

#include <TopoDS_Shape.hxx>
#include <BRepTools.hxx>
#include <LDOM_Text.hxx>
#include <LDOM_OSStream.hxx>

#include <Standard_SStream.hxx>

static TNaming_Evolution          EvolutionEnum   (const XmlObjMgt_DOMString&);
static const XmlObjMgt_DOMString& EvolutionString (const TNaming_Evolution);
static void                       doTranslate     (const TopoDS_Shape&,
                                                   XmlMNaming_Shape1&,
                                                   BRepTools_ShapeSet&);
static int                        doTranslate     (const XmlMNaming_Shape1&,
                                                   TopoDS_Shape&,
                                                   BRepTools_ShapeSet&);

IMPLEMENT_DOMSTRING (OldsString,    "olds")
IMPLEMENT_DOMSTRING (NewsString,    "news")
IMPLEMENT_DOMSTRING (StatusString,  "evolution")
IMPLEMENT_DOMSTRING (VersionString, "version")
IMPLEMENT_DOMSTRING (ShapesString,  "shapes")

IMPLEMENT_DOMSTRING (EvolPrimitiveString, "primitive")
IMPLEMENT_DOMSTRING (EvolGeneratedString, "generated")
IMPLEMENT_DOMSTRING (EvolModifyString,    "modify")
IMPLEMENT_DOMSTRING (EvolDeleteString,    "delete")
IMPLEMENT_DOMSTRING (EvolSelectedString,  "selected")
IMPLEMENT_DOMSTRING (EvolReplaceString,   "replace")

//=======================================================================
//function : XmlMNaming_NamedShapeDriver
//purpose  : Constructor
//=======================================================================

XmlMNaming_NamedShapeDriver::XmlMNaming_NamedShapeDriver
                        (const Handle(CDM_MessageDriver&) theMessageDriver)
     : XmlMDF_ADriver (theMessageDriver, NULL),
  myShapeSet (Standard_False) // triangles mode
{}

//=======================================================================
//function : NewEmpty()
//purpose  : 
//=======================================================================
Handle(TDF_Attribute) XmlMNaming_NamedShapeDriver::NewEmpty () const
{
  return (new TNaming_NamedShape());
}

//=======================================================================
//function : Paste()
//purpose  : retrieval of TNaming_NamedShape
//=======================================================================

Standard_Boolean XmlMNaming_NamedShapeDriver::Paste
                                       (const XmlObjMgt_Persistent&  theSource,
                                        const Handle(TDF_Attribute)& theTarget,
                                        XmlObjMgt_RRelocationTable&) const
{
  Handle(TNaming_NamedShape) aTarget =
    Handle(TNaming_NamedShape)::DownCast(theTarget);
  TDF_Label Label = aTarget -> Label();
  TNaming_Builder aBld (Label);

  //    Get Version
  Standard_Integer    aVersion = 0;
  const XmlObjMgt_Element& anElement = theSource;
  XmlObjMgt_DOMString aVerString = anElement.getAttribute (::VersionString());
  if (aVerString != NULL)
    aVerString.GetInteger (aVersion);

  //    Get Evolution status
  XmlObjMgt_DOMString aStatus = anElement.getAttribute (::StatusString());
  TNaming_Evolution evol = EvolutionEnum (aStatus);
  // apres creation Builder qui a mis la version a 1 :
  aTarget -> SetVersion (aVersion);

  const XmlMNaming_Array1OfShape1 OldPShapes (anElement, ::OldsString());
  const XmlMNaming_Array1OfShape1 NewPShapes (anElement, ::NewsString());
  if (NewPShapes.Length() == 0 && OldPShapes.Length() == 0)
    return Standard_True;

  TopoDS_Shape anOldShape;
  TopoDS_Shape aNewShape;
  BRepTools_ShapeSet& aShapeSet = (BRepTools_ShapeSet&) myShapeSet;

  Standard_Integer lower = NewPShapes.Lower();
  if (OldPShapes.Lower() < lower) lower = OldPShapes.Lower();

  Standard_Integer upper = NewPShapes.Upper();
  if (OldPShapes.Upper() > upper) upper = OldPShapes.Upper();

  for (Standard_Integer i = lower; i <= upper; i++)
  {
    const XmlMNaming_Shape1 aNewPShape  = NewPShapes.Value(i);
    const XmlMNaming_Shape1 anOldPShape = OldPShapes.Value(i);

    if ( evol != TNaming_PRIMITIVE && anOldPShape.Element() != NULL )
    {
      if (::doTranslate (anOldPShape, anOldShape, aShapeSet)) {
        WriteMessage ("NamedShapeDriver: Error reading a shape from array");
        return Standard_False;
      }
    }

    if (evol != TNaming_DELETE && aNewPShape.Element() != NULL )
    {
      if (::doTranslate (aNewPShape, aNewShape, aShapeSet)) {
        WriteMessage ("NamedShapeDriver: Error reading a shape from array");
        return Standard_False;
      }
    }

    switch (evol)
    {
    case TNaming_PRIMITIVE:
      aBld.Generated(aNewShape);
      break;
    case TNaming_GENERATED:
      aBld.Generated(anOldShape,aNewShape);
      break;
    case TNaming_MODIFY:
      aBld.Modify(anOldShape,aNewShape);
      break;
    case TNaming_DELETE:
      aBld.Delete(anOldShape);
      break;
    case TNaming_SELECTED:
      aBld.Select(aNewShape, anOldShape);
      break;
      //    case TNaming_REPLACE:
      //      aBld.Replace(anOldShape,aNewShape);
      //      break;
    default:
      Standard_DomainError::Raise("TNaming_Evolution; enum term unknown");
    }
    anOldShape.Nullify();
    aNewShape.Nullify();
  }
  return Standard_True;
}

//=======================================================================
//function : Paste()
//purpose  : storage of TNaming_NamedShape
//=======================================================================

void XmlMNaming_NamedShapeDriver::Paste (const Handle(TDF_Attribute)& theSource,
                                         XmlObjMgt_Persistent&        theTarget,
                                         XmlObjMgt_SRelocationTable&) const
{
//AGV  XmlObjMgt_Document& aDoc =
//AGV    (XmlObjMgt_Document&) theTarget.Element().getOwnerDocument();
  XmlObjMgt_Document aDoc =
    XmlObjMgt_Document (theTarget.Element().getOwnerDocument());

  Handle(TNaming_NamedShape) aNamedShape =
    Handle(TNaming_NamedShape)::DownCast(theSource);
  TNaming_Evolution evol = aNamedShape->Evolution();

  //    Create arrays
  Standard_Integer NbShapes = 0;
  TNaming_Iterator SItr (aNamedShape);
  while (SItr.More()) {
    NbShapes++;
    SItr.Next ();
  }

  BRepTools_ShapeSet& aShapeSet = (BRepTools_ShapeSet&) myShapeSet;
  XmlMNaming_Array1OfShape1 OldPShapes (1,NbShapes), NewPShapes (1,NbShapes);

  OldPShapes.CreateArrayElement (theTarget, ::OldsString());
  NewPShapes.CreateArrayElement (theTarget, ::NewsString());

  //    Fill arrays
  Standard_Integer i = 1;
  TNaming_Iterator SIterator(aNamedShape);
  while (SIterator.More())
  {
    const TopoDS_Shape& OldShape = SIterator.OldShape();
    const TopoDS_Shape& NewShape = SIterator.NewShape();

    if ( evol != TNaming_PRIMITIVE )
    {
      XmlMNaming_Shape1 anOldPShape (aDoc);
      ::doTranslate (OldShape, anOldPShape, aShapeSet);
      OldPShapes.SetValue (i, anOldPShape.Element());
    }

    if (evol != TNaming_DELETE)
    {
      XmlMNaming_Shape1 aNewPShape (aDoc);
      ::doTranslate (NewShape, aNewPShape, aShapeSet);
      NewPShapes.SetValue (i, aNewPShape.Element());
    }
    i++;
    SIterator.Next();
  }

  theTarget.Element().setAttribute (::StatusString(), EvolutionString(evol));
  Standard_Integer aVersion = aNamedShape -> Version();
  if (aVersion != 0)
    theTarget.Element().setAttribute (::VersionString(), aVersion);
}

//=======================================================================
//function : EvolutionEnum
//purpose  : static
//=======================================================================

static const XmlObjMgt_DOMString& EvolutionString(const TNaming_Evolution i)
{
  switch(i) {
    case TNaming_PRIMITIVE    : return ::EvolPrimitiveString();
    case TNaming_GENERATED    : return ::EvolGeneratedString();
    case TNaming_MODIFY       : return ::EvolModifyString();
    case TNaming_DELETE       : return ::EvolDeleteString();
    case TNaming_SELECTED     : return ::EvolSelectedString();
      //    case TNaming_REPLACE      : return ::EvolReplaceString();
  default:
    Standard_DomainError::Raise("TNaming_Evolution; enum term unknown");
  }
  static XmlObjMgt_DOMString aNullString;
  return aNullString; // To avoid compilation error message.
}

//=======================================================================
//function : EvolutionEnum
//purpose  : static
//=======================================================================

static TNaming_Evolution EvolutionEnum (const XmlObjMgt_DOMString& theString)
{
  TNaming_Evolution aResult = TNaming_PRIMITIVE;
  if (theString.equals (::EvolPrimitiveString()) == Standard_False) {
    if (theString.equals (::EvolGeneratedString()))
      aResult = TNaming_GENERATED;
    else if (theString.equals (::EvolModifyString()))
      aResult = TNaming_MODIFY;
    else if (theString.equals (::EvolDeleteString()))
      aResult = TNaming_DELETE;
    else if (theString.equals (::EvolSelectedString()))
      aResult = TNaming_SELECTED;
    else if (theString.equals (::EvolReplaceString()))
      aResult = TNaming_MODIFY; // for compatibility //TNaming_REPLACE;
    else
      Standard_DomainError::Raise
        ("TNaming_Evolution; string value without enum term equivalence");
  }
  return aResult;
}

//=======================================================================
//function : doTranslate
//purpose  : shape storage to XML
//=======================================================================

static void doTranslate (const TopoDS_Shape&            theShape,
                         XmlMNaming_Shape1&             theResult,
                         BRepTools_ShapeSet&            theShapeSet)
{
  // Check for empty shape
  if (theShape.IsNull()) return;

  // Add to shape set both TShape and Location contained in theShape
  const Standard_Integer aTShapeId = theShapeSet.Add (theShape);
  const Standard_Integer aLocId =
    theShapeSet.Locations().Index (theShape.Location());

  // Fill theResult with shape parameters: TShape ID, Location, Orientation
  theResult.SetShape (aTShapeId, aLocId, theShape.Orientation());

  if (theShape.ShapeType() == TopAbs_VERTEX)
  {
    theResult.SetVertex(theShape);
  }
}

//=======================================================================
//function : doTranslate
//purpose  : shape retrieval from XML
//=======================================================================

static int doTranslate  (const XmlMNaming_Shape1&       thePShape,
                         TopoDS_Shape&                  theResult,
                         BRepTools_ShapeSet&            theShapeSet)
{
  const Standard_Integer aShapeId = thePShape.TShapeId();

  // Read TShape and Orientation
  if (aShapeId <= 0 || aShapeId > theShapeSet.NbShapes())
    return 1;
  theResult.TShape      (theShapeSet.Shape(aShapeId).TShape());
  theResult.Orientation (thePShape.Orientation());
  theResult.Location    (theShapeSet.Locations().Location (thePShape.LocId()));

  return 0;
}

//=======================================================================
//function : ReadShapeSection
//purpose  : 
//=======================================================================

void XmlMNaming_NamedShapeDriver::ReadShapeSection
                                        (const XmlObjMgt_Element& theElement)
{
  XmlObjMgt_Element anElement =
    XmlObjMgt::FindChildByName (theElement, ::ShapesString());
  if (anElement != NULL) {
    for (LDOM_Node aNode = anElement.getFirstChild();
         aNode != NULL;
         aNode = anElement.getNextSibling())
    {
      if (aNode.getNodeType() == LDOM_Node::TEXT_NODE) {
        LDOM_Text aText = (LDOM_Text&) aNode;
        LDOMString aData = aText.getData();
	#ifdef USE_STL_STREAM
        std::stringstream aStream (std::string(aData.GetString()));
	#else
        istrstream aStream (Standard_CString(aData.GetString()));
	#endif
        myShapeSet.Clear();
        myShapeSet.Read (aStream);
        break;
      }
    }
  }
}

//=======================================================================
//function : WriteShapeSection
//purpose  : 
//=======================================================================

void XmlMNaming_NamedShapeDriver::WriteShapeSection
                                        (XmlObjMgt_Element& theElement)
{
  //  Create "shapes" element and append it as child
  XmlObjMgt_Document aDoc     = theElement.getOwnerDocument();
  XmlObjMgt_Element anElement = aDoc.createElement (::ShapesString());
  theElement.appendChild (anElement);

  //  Add text to the "shapes" element
  if (myShapeSet.NbShapes() > 0) {
    myShapeSet.SetFormatNb(2);
    LDOM_OSStream aStream (1024);
//    ostrstream aStream;
//    aStream.rdbuf() -> setbuf (0, 16380);
    myShapeSet.Write (aStream);
    aStream << ends;
    char * aStr = (char *)aStream.str();
    LDOM_Text aText = aDoc.createTextNode (aStr);
    delete [] aStr;
    aText.SetValueClear();      // There are no characters '<' and '&' and like
//    aStream.rdbuf() -> freeze(0);                     // release the buffer
    anElement.appendChild (aText);
  // Clear the shape set to avoid appending to it on the next write
    BRepTools_ShapeSet& aShapeSet = (BRepTools_ShapeSet&) myShapeSet;
    aShapeSet.Clear();
  }
}

//=======================================================================
//function : Clear
//purpose  : 
//=======================================================================

void XmlMNaming_NamedShapeDriver::Clear()
{
  myShapeSet.Clear();
}
