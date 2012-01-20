// File:	BinMDataStd_IntPackedMapDriver.cxx
// Created:	Wed Aug  1 14:30:43 2007
// Author:	Sergey ZARITCHNY
//		<sergey.zaritchny@opencascade.com>
// Copyright:   Open CASCADE SA 2007


#include <BinMDataStd_IntPackedMapDriver.ixx>
#include <CDM_MessageDriver.hxx>
#include <TColStd_PackedMapOfInteger.hxx>
#include <TColStd_HPackedMapOfInteger.hxx>
#include <TColStd_MapIteratorOfPackedMapOfInteger.hxx>
#include <BinMDF_ADriver.hxx>
#include <TDataStd_IntPackedMap.hxx>
#include <TDF_Attribute.hxx>
#include <BinObjMgt_Persistent.hxx>
#include <BinObjMgt_RRelocationTable.hxx>
#include <BinObjMgt_SRelocationTable.hxx>
#include <TCollection_ExtendedString.hxx>
#include <BinMDataStd.hxx>
//=======================================================================
//function : BinMDataStd_IntPackedMapDriver
//purpose  :
//=======================================================================

BinMDataStd_IntPackedMapDriver::BinMDataStd_IntPackedMapDriver
                         (const Handle(CDM_MessageDriver)& theMessageDriver)
     : BinMDF_ADriver (theMessageDriver, STANDARD_TYPE(TDataStd_IntPackedMap)->Name())
{
}

//=======================================================================
//function : NewEmpty
//purpose  :
//=======================================================================

Handle(TDF_Attribute) BinMDataStd_IntPackedMapDriver::NewEmpty() const
{
  return new TDataStd_IntPackedMap;
}

//=======================================================================
//function : Paste
//purpose  : persistent -> transient (retrieve)
//=======================================================================

Standard_Boolean BinMDataStd_IntPackedMapDriver::Paste
                         (const BinObjMgt_Persistent&  Source,
                          const Handle(TDF_Attribute)& Target,
                          BinObjMgt_RRelocationTable&  /*RelocTable*/) const
{
  Handle(TDataStd_IntPackedMap) aTagAtt = Handle(TDataStd_IntPackedMap)::DownCast(Target);
  if(aTagAtt.IsNull()) {
    WriteMessage (TCollection_ExtendedString("IntPackedMapDriver:: The target attribute is Null."));
    return Standard_False;
  }

  Standard_Integer aSize = 0;
  if (! (Source >> aSize)) {
    WriteMessage (TCollection_ExtendedString("Cannot retrieve size for IntPackedMap attribute."));
    return Standard_False;
  }
  if(aSize) {
    Handle(TColStd_HPackedMapOfInteger) aHMap = new TColStd_HPackedMapOfInteger ();
    Standard_Integer aKey=0;
    for(Standard_Integer i = 0; i< aSize; i++) {
      Standard_Boolean ok = Source >> aKey;
      if (!ok) {
	WriteMessage ("Cannot retrieve integer member for IntPackedMap attribute.");
	return Standard_False;
      }
      if(!aHMap->ChangeMap().Add( aKey )) return Standard_False;
    }
    aTagAtt->ChangeMap(aHMap);
  }
#ifdef DEB
  //cout << "CurDocVersion = " << BinMDataStd::DocumentVersion() <<endl;
#endif  
  Standard_Boolean aDelta(Standard_False);
  if(BinMDataStd::DocumentVersion() > 2) {
    Standard_Byte aDeltaValue;
    if (! (Source >> aDeltaValue))
      return Standard_False;
    else
      aDelta = (Standard_Boolean)aDeltaValue;
  }
  aTagAtt->SetDelta(aDelta);
  return Standard_True;
}

//=======================================================================
//function : Paste
//purpose  : transient -> persistent (store)
//=======================================================================

void BinMDataStd_IntPackedMapDriver::Paste
                         (const Handle(TDF_Attribute)& Source,
                          BinObjMgt_Persistent&        Target,
                          BinObjMgt_SRelocationTable&  /*RelocTable*/) const
{
  Handle(TDataStd_IntPackedMap) anAtt = Handle(TDataStd_IntPackedMap)::DownCast(Source);
  if (anAtt.IsNull()) {
    WriteMessage ("IntPackedMapDriver:: The source attribute is Null.");
    return;
  }
  Standard_Integer aSize = (anAtt->IsEmpty()) ? 0 : anAtt->Extent();
  Target << aSize;
  if(aSize) {
    TColStd_MapIteratorOfPackedMapOfInteger anIt(anAtt->GetMap());
    for(;anIt.More();anIt.Next())
      Target << anIt.Key();
  }
  Target << (Standard_Byte)anAtt->GetDelta(); 
}
