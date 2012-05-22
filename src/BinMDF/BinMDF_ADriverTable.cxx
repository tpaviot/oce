// Created on: 2002-10-29
// Created by: Michael SAZONOV
// Copyright (c) 2002-2012 OPEN CASCADE SAS
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


#include <BinMDF_ADriverTable.ixx>
#include <Standard_NoSuchObject.hxx>
#include <BinMDF_StringIdMap.hxx>
#include <TCollection_HAsciiString.hxx>
#include <BinMDF_DataMapIteratorOfTypeADriverMap.hxx>

//=======================================================================
//function : BinMDF_ADriverTable
//purpose  : Constructor
//=======================================================================

BinMDF_ADriverTable::BinMDF_ADriverTable ()
{
}

//=======================================================================
//function : AddDriver
//purpose  : Adds a translation driver <theDriver>.
//=======================================================================

void BinMDF_ADriverTable::AddDriver
                (const Handle(BinMDF_ADriver)& theDriver)
{
  const Handle(Standard_Type)& aType = theDriver->SourceType();
  myMap.Bind (aType, theDriver);
}

//=======================================================================
//function : AssignIds
//purpose  : Assigns the IDs to the drivers of the given Types.
//           It uses indices in the map as IDs.
//           Useful in storage procedure.
//=======================================================================

void BinMDF_ADriverTable::AssignIds
                (const TColStd_IndexedMapOfTransient& theTypes)
{
  myMapId.Clear();
  Standard_Integer i;
  for (i=1; i <= theTypes.Extent(); i++) {
    const Handle(Standard_Type)& aType =
      Handle(Standard_Type)::DownCast (theTypes(i));
    if (myMap.IsBound (aType)) {
      myMapId.Bind (aType, i);
    }
    else {
      Standard_NoSuchObject::Raise
        ((TCollection_AsciiString("BinMDF_ADriverTable::AssignIds : ") +
          "the type " + aType->Name() + " has not been registered").ToCString());
    }
  }
}

//=======================================================================
//function : AssignIds
//purpose  : Assigns the IDs to the drivers of the given Type Names;
//           It uses indices in the sequence as IDs.
//           Useful in retrieval procedure.
//=======================================================================

void BinMDF_ADriverTable::AssignIds
                (const TColStd_SequenceOfAsciiString& theTypeNames)
{
  myMapId.Clear();
  // first prepare the data map (TypeName => TypeID) for input types
  BinMDF_StringIdMap aStringIdMap;
  Standard_Integer i;
  for (i=1; i <= theTypeNames.Length(); i++) {
    const TCollection_AsciiString& aTypeName = theTypeNames(i);
    aStringIdMap.Bind (aTypeName, i);
  }
  // and now associate the names with the registered types
  BinMDF_DataMapIteratorOfTypeADriverMap it (myMap);
  for (; it.More(); it.Next()) {
    const Handle(Standard_Type)& aType = it.Key();
    const Handle(BinMDF_ADriver)& aDriver = it.Value();
    const TCollection_AsciiString& aTypeName = aDriver->TypeName();
    if (aStringIdMap.IsBound(aTypeName)) {
      i = aStringIdMap(aTypeName);
      myMapId.Bind (aType, i);
    }
  }
}
