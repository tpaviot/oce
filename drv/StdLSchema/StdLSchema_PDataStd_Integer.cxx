#ifndef _StdLSchema_PDataStd_Integer_HeaderFile
#include <StdLSchema_PDataStd_Integer.hxx>
#endif
#ifndef _PDataStd_Integer_HeaderFile
#include <PDataStd_Integer.hxx>
#endif
#include <StdLSchema_PDataStd_Integer.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_Integer,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_Integer,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_Integer::New() const
{
  return new PDataStd_Integer(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_Integer::SAdd(const Handle(PDataStd_Integer)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_Integer")) {
      
    }
  }
}

void StdLSchema_PDataStd_Integer::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_Integer::SAdd((Handle(PDataStd_Integer)&)p,theSchema);
}

void StdLSchema_PDataStd_Integer::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_Integer) &pp = (Handle(PDataStd_Integer)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPDataStd_IntegermyValue());

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_Integer::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_Integer::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_Integer::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_Integer) &pp = (Handle(PDataStd_Integer)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PDataStd_IntegermyValue;
    f.GetInteger(PDataStd_IntegermyValue);
    pp->_CSFDB_SetPDataStd_IntegermyValue(PDataStd_IntegermyValue);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_Integer::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_Integer::SRead(p,f,theSchema);
}
