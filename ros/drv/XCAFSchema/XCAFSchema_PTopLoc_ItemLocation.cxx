#ifndef _XCAFSchema_PTopLoc_ItemLocation_HeaderFile
#include <XCAFSchema_PTopLoc_ItemLocation.hxx>
#endif
#ifndef _PTopLoc_ItemLocation_HeaderFile
#include <PTopLoc_ItemLocation.hxx>
#endif
#include <XCAFSchema_PTopLoc_ItemLocation.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PTopLoc_ItemLocation,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PTopLoc_ItemLocation,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PTopLoc_ItemLocation::New() const
{
  return new PTopLoc_ItemLocation(Storage_stCONSTclCOM());
}

void XCAFSchema_PTopLoc_ItemLocation::SAdd(const Handle(PTopLoc_ItemLocation)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PTopLoc_ItemLocation")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPTopLoc_ItemLocationmyDatum());
   XCAFSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPTopLoc_ItemLocationmyNext(),theSchema);

    }
  }
}

void XCAFSchema_PTopLoc_ItemLocation::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PTopLoc_ItemLocation::SAdd((Handle(PTopLoc_ItemLocation)&)p,theSchema);
}

void XCAFSchema_PTopLoc_ItemLocation::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopLoc_ItemLocation) &pp = (Handle(PTopLoc_ItemLocation)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPTopLoc_ItemLocationmyDatum(),f);
  f.PutInteger(pp->_CSFDB_GetPTopLoc_ItemLocationmyPower());
    XCAFSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPTopLoc_ItemLocationmyNext(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PTopLoc_ItemLocation::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PTopLoc_ItemLocation::SWrite(p,f,theSchema);
}


void XCAFSchema_PTopLoc_ItemLocation::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopLoc_ItemLocation) &pp = (Handle(PTopLoc_ItemLocation)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PTopLoc_Datum3D) PTopLoc_ItemLocationmyDatum;

    theSchema->ReadPersistentReference(PTopLoc_ItemLocationmyDatum,f);
    pp->_CSFDB_SetPTopLoc_ItemLocationmyDatum(PTopLoc_ItemLocationmyDatum);

    Standard_Integer PTopLoc_ItemLocationmyPower;
    f.GetInteger(PTopLoc_ItemLocationmyPower);
    pp->_CSFDB_SetPTopLoc_ItemLocationmyPower(PTopLoc_ItemLocationmyPower);

    XCAFSchema_PTopLoc_Location::SRead((PTopLoc_Location&)pp->_CSFDB_GetPTopLoc_ItemLocationmyNext(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PTopLoc_ItemLocation::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PTopLoc_ItemLocation::SRead(p,f,theSchema);
}
