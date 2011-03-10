#ifndef _ShapeSchema_PTopLoc_ItemLocation_HeaderFile
#include <ShapeSchema_PTopLoc_ItemLocation.hxx>
#endif
#ifndef _PTopLoc_ItemLocation_HeaderFile
#include <PTopLoc_ItemLocation.hxx>
#endif
#include <ShapeSchema_PTopLoc_ItemLocation.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PTopLoc_ItemLocation,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PTopLoc_ItemLocation,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PTopLoc_ItemLocation::New() const
{
  return new PTopLoc_ItemLocation(Storage_stCONSTclCOM());
}

void ShapeSchema_PTopLoc_ItemLocation::SAdd(const Handle(PTopLoc_ItemLocation)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PTopLoc_ItemLocation")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPTopLoc_ItemLocationmyDatum());
   ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPTopLoc_ItemLocationmyNext(),theSchema);

    }
  }
}

void ShapeSchema_PTopLoc_ItemLocation::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PTopLoc_ItemLocation::SAdd((Handle(PTopLoc_ItemLocation)&)p,theSchema);
}

void ShapeSchema_PTopLoc_ItemLocation::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopLoc_ItemLocation) &pp = (Handle(PTopLoc_ItemLocation)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPTopLoc_ItemLocationmyDatum(),f);
  f.PutInteger(pp->_CSFDB_GetPTopLoc_ItemLocationmyPower());
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPTopLoc_ItemLocationmyNext(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PTopLoc_ItemLocation::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PTopLoc_ItemLocation::SWrite(p,f,theSchema);
}


void ShapeSchema_PTopLoc_ItemLocation::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
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

    ShapeSchema_PTopLoc_Location::SRead((PTopLoc_Location&)pp->_CSFDB_GetPTopLoc_ItemLocationmyNext(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PTopLoc_ItemLocation::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PTopLoc_ItemLocation::SRead(p,f,theSchema);
}
