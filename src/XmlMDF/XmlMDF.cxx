// Created on: 2001-07-09
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


#include <XmlMDF.ixx>
#include <XmlMDF_ADriver.hxx>
#include <XmlMDF_TagSourceDriver.hxx>
#include <XmlMDF_ReferenceDriver.hxx>
#include <XmlMDF_DataMapIteratorOfTypeADriverMap.hxx>

#include <XmlObjMgt_Persistent.hxx>
#include <XmlObjMgt_DOMString.hxx>
#include <XmlObjMgt_Document.hxx>

#include <TDF_TagSource.hxx>
#include <TDF_Label.hxx>
#include <TDF_Tool.hxx>
#include <TDF_AttributeIterator.hxx>
#include <TDF_ChildIterator.hxx>
#include <TColStd_MapOfTransient.hxx>
#include <Storage_Schema.hxx>

IMPLEMENT_DOMSTRING (TagString,         "tag")
IMPLEMENT_DOMSTRING (LabelString,       "label")
#define DATATYPE_MIGRATION
//#define DATATYPE_MIGRATION_DEB
//=======================================================================
//function : UnsuppTypesMap
//purpose  : 
//=======================================================================

static TColStd_MapOfTransient& UnsuppTypesMap ()
{
  static TColStd_MapOfTransient anUnsuppTypes;
  return anUnsuppTypes;
}

//=======================================================================
//function : FromTo
//purpose  : Paste transient data into DOM_Element
//=======================================================================
void XmlMDF::FromTo (const Handle(TDF_Data)&             theData,
                     XmlObjMgt_Element&                  theElement,
                     XmlObjMgt_SRelocationTable&         theRelocTable,
                     const Handle(XmlMDF_ADriverTable)&  theDrivers)
{
  UnsuppTypesMap().Clear();
//  Standard_Integer count =
  WriteSubTree(theData->Root(), theElement, theRelocTable, theDrivers);
  UnsuppTypesMap().Clear();
}

//=======================================================================
//function : WriteSubTree
//purpose  : 
//=======================================================================
Standard_Integer XmlMDF::WriteSubTree
                      (const TDF_Label&                    theLabel,
                       XmlObjMgt_Element&                  theElement,
                       XmlObjMgt_SRelocationTable&         theRelocTable,
                       const Handle(XmlMDF_ADriverTable)&  theDrivers)
{
  XmlObjMgt_Document aDoc = theElement.getOwnerDocument();

  // create element "label"
  XmlObjMgt_Element aLabElem = aDoc.createElement (::LabelString());

  // Extraction of the driver subset.
  const XmlMDF_TypeADriverMap& aDriverMap = theDrivers->GetDrivers();

  // write attributes
  Standard_Integer count = 0;
  TDF_AttributeIterator itr1 (theLabel);
  for ( ; itr1.More(); itr1.Next())
  {
    const Handle(TDF_Attribute)& tAtt = itr1.Value();
    const Handle(Standard_Type)& aType = tAtt->DynamicType();
    if (aDriverMap.IsBound (aType))
    {
      const Handle(XmlMDF_ADriver)& aDriver = aDriverMap.Find (aType);
      count++;

      //    Add source to relocation table
      Standard_Integer anId      = theRelocTable.Add (tAtt);

      //    Create DOM data item
      XmlObjMgt_Persistent pAtt;
      pAtt.CreateElement (aLabElem, aDriver->TypeName().ToCString(), anId);

      //    Paste
      aDriver -> Paste (tAtt, pAtt, theRelocTable);
    }
#ifdef DEB
    else if (!UnsuppTypesMap().Contains (aType))
    {
      cout << "attribute driver for type "<< aType -> Name()<< " not found"<< endl;
      UnsuppTypesMap().Add (aType);
    }
#endif
  }

  // write sub-labels
  TDF_ChildIterator itr2 (theLabel);
  for ( ; itr2.More(); itr2.Next())
  {
    const TDF_Label& aChildLab = itr2.Value();
    count += WriteSubTree(aChildLab, aLabElem, theRelocTable, theDrivers);
  }

  if (count > 0)
  {
    theElement.appendChild(aLabElem);

    // set attribute "tag"
    aLabElem.setAttribute (::TagString(), theLabel.Tag());
  }

  return count;
}

//=======================================================================
//function : FromTo
//purpose  : Paste data from DOM_Element into transient document
//=======================================================================
Standard_Boolean XmlMDF::FromTo (const XmlObjMgt_Element&         theElement,
                                 Handle(TDF_Data)&                theData,
                                 XmlObjMgt_RRelocationTable&      theRelocTable,
                                 const Handle(XmlMDF_ADriverTable)& theDrivers)
{
  TDF_Label aRootLab = theData->Root();
  XmlMDF_MapOfDriver aDriverMap;
  CreateDrvMap (theDrivers, aDriverMap);

  Standard_Integer count = 0;

  LDOM_Node theNode = theElement.getFirstChild();
  XmlObjMgt_Element anElem = (const XmlObjMgt_Element&)theNode;
  while ( !anElem.isNull() )
  {
    if ( anElem.getNodeName().equals (::LabelString()) )
    {
      Standard_Integer subcount =
        ReadSubTree(anElem, aRootLab, theRelocTable, aDriverMap);
      // check for error
      if (subcount < 0)
        return Standard_False;
      count += subcount;
    }
    //anElem = (const XmlObjMgt_Element &) anElem.getNextSibling();
    LDOM_Node theNode1 = anElem.getNextSibling();
    anElem = (const XmlObjMgt_Element &) theNode1;
  }

  return Standard_True;
}

//=======================================================================
//function : ReadSubTree
//purpose  : 
//=======================================================================
Standard_Integer XmlMDF::ReadSubTree (const XmlObjMgt_Element&    theElement,
                                      const TDF_Label&            theLabel,
                                      XmlObjMgt_RRelocationTable& theRelocTable,
                                      const XmlMDF_MapOfDriver&   theDriverMap)
{
  // Extraction of the driver subset.
  Standard_Integer count = 0;

  //XmlObjMgt_Element anElem = (const XmlObjMgt_Element &) theElement.getFirstChild();
  LDOM_Node theNode = theElement.getFirstChild();
  XmlObjMgt_Element anElem = (const XmlObjMgt_Element &) theNode;
  while ( !anElem.isNull() )
  {
    if ( anElem.getNodeType() == LDOM_Node::ELEMENT_NODE )
    {
      if ( anElem.getNodeName().equals (::LabelString()) )
      {
        // read tag
        Standard_Integer tag;
        XmlObjMgt_DOMString aTag (anElem.getAttribute(::TagString()));
        if ( !aTag.GetInteger (tag) ) {
          TCollection_ExtendedString anErrorMessage =
            TCollection_ExtendedString ("Wrong Tag value for OCAF Label: ")
              + aTag;
          theDriverMap.Find("TDF_TagSource") -> WriteMessage (anErrorMessage);
          return -1;
        }
        // create label
        TDF_Label aLab = theLabel.FindChild(tag, Standard_True);

        // read sub-tree
        Standard_Integer subcount =
          ReadSubTree(anElem, aLab, theRelocTable, theDriverMap);
        // check for error
        if (subcount == -1)
          return -1;
        count += subcount;
      }
      else
      {
        // read attribute
        XmlObjMgt_DOMString aName = anElem.getNodeName();

#ifdef DATATYPE_MIGRATION
	TCollection_AsciiString  newName;	
	if(Storage_Schema::CheckTypeMigration(aName, newName)) {
#ifdef DATATYPE_MIGRATION_DEB
	  cout << "CheckTypeMigration:OldType = " <<aName.GetString() << " Len = "<<strlen(aName.GetString())<<endl;
	  cout << "CheckTypeMigration:NewType = " <<newName  << " Len = "<< newName.Length()<<endl;
#endif
	  aName = newName.ToCString();
	}
#endif  
       
        if (theDriverMap.IsBound (aName))
        {
          count++;
          const Handle(XmlMDF_ADriver)& driver = theDriverMap.Find(aName);
          XmlObjMgt_Persistent pAtt (anElem);
          Standard_Integer anID = pAtt.Id ();
          if (anID <= 0) {      // check for ID validity
            TCollection_ExtendedString anErrorMessage =
             TCollection_ExtendedString("Wrong ID of OCAF attribute with type ")
               + aName;
            driver -> WriteMessage (anErrorMessage);
            return -1;
          }
          Handle(TDF_Attribute) tAtt;
          Standard_Boolean isBound = theRelocTable.IsBound(anID);
          if (isBound)
            tAtt = Handle(TDF_Attribute)::DownCast(theRelocTable.Find(anID));
          else
            tAtt = driver -> NewEmpty();
	  if (tAtt->Label().IsNull())
	    theLabel.AddAttribute (tAtt);
	  else
	    driver->WriteMessage
	      (TCollection_ExtendedString("XmlDriver warning: ") +
	       "attempt to attach attribute " +
	       aName + " to a second label");

          if (! driver -> Paste (pAtt, tAtt, theRelocTable))
          {
            // error converting persistent to transient
            driver->WriteMessage
              (TCollection_ExtendedString("XmlDriver warning: ") +
               "failure reading attribute " + aName);
          }
          else if (isBound == Standard_False)
            theRelocTable.Bind (anID, tAtt);
        }
#ifdef DEB
        else
        {
          const TCollection_AsciiString anAsciiName = aName;
          cerr << "XmlDriver warning: "
               << "label contains object of unknown type "<< anAsciiName<< endl;
        }
#endif
      }
    }
    //anElem = (const XmlObjMgt_Element &) anElem.getNextSibling();
    LDOM_Node theNode1 = anElem.getNextSibling();
    anElem = (const XmlObjMgt_Element &) theNode1;
  }

  // AfterRetrieval
  if (count > 0)
  {
  }

  return count;
}

//=======================================================================
//function : AddDrivers
//purpose  : 
//=======================================================================
void XmlMDF::AddDrivers (const Handle(XmlMDF_ADriverTable)& aDriverTable,
                         const Handle(CDM_MessageDriver)&   aMessageDriver)
{
  aDriverTable->AddDriver (new XmlMDF_TagSourceDriver(aMessageDriver)); 
  aDriverTable->AddDriver (new XmlMDF_ReferenceDriver(aMessageDriver));
}

//=======================================================================
//function : CreateDrvMap
//purpose  : 
//=======================================================================

void XmlMDF::CreateDrvMap (const Handle(XmlMDF_ADriverTable)& theDrivers,
                           XmlMDF_MapOfDriver&                theAsciiDriverMap)
{
  const XmlMDF_TypeADriverMap& aDriverMap = theDrivers->GetDrivers();
  XmlMDF_DataMapIteratorOfTypeADriverMap anIter (aDriverMap);
  while (anIter.More()) {
    const Handle(XmlMDF_ADriver)& aDriver = anIter.Value();
    const TCollection_AsciiString aTypeName = aDriver -> TypeName();
    if (theAsciiDriverMap.IsBound (aTypeName) == Standard_False)
      theAsciiDriverMap.Bind (aTypeName, aDriver);
    else
      aDriver -> WriteMessage
        (TCollection_ExtendedString ("Warning: skipped driver name: \"")
         + aTypeName + '\"');
    anIter.Next();
  }
}
