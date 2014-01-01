#ifndef _StdLSchema_PDataStd_IntPackedMap_HeaderFile
#include <StdLSchema_PDataStd_IntPackedMap.hxx>
#endif
#ifndef _PDataStd_IntPackedMap_HeaderFile
#include <PDataStd_IntPackedMap.hxx>
#endif
#include <StdLSchema_PDataStd_IntPackedMap.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_IntPackedMap,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_IntPackedMap,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_IntPackedMap::New() const
{
  return new PDataStd_IntPackedMap(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_IntPackedMap::SAdd(const Handle(PDataStd_IntPackedMap)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_IntPackedMap")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_IntPackedMapmyIntValues());

    }
  }
}

void StdLSchema_PDataStd_IntPackedMap::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_IntPackedMap::SAdd((Handle(PDataStd_IntPackedMap)&)p,theSchema);
}

void StdLSchema_PDataStd_IntPackedMap::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_IntPackedMap) &pp = (Handle(PDataStd_IntPackedMap)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_IntPackedMapmyIntValues(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_IntPackedMap::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_IntPackedMap::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_IntPackedMap::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_IntPackedMap) &pp = (Handle(PDataStd_IntPackedMap)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColStd_HArray1OfInteger) PDataStd_IntPackedMapmyIntValues;

    theSchema->ReadPersistentReference(PDataStd_IntPackedMapmyIntValues,f);
    pp->_CSFDB_SetPDataStd_IntPackedMapmyIntValues(PDataStd_IntPackedMapmyIntValues);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_IntPackedMap::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_IntPackedMap::SRead(p,f,theSchema);
}
