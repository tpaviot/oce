#ifndef _StdLSchema_PDataStd_Real_HeaderFile
#include <StdLSchema_PDataStd_Real.hxx>
#endif
#ifndef _PDataStd_Real_HeaderFile
#include <PDataStd_Real.hxx>
#endif
#include <StdLSchema_PDataStd_Real.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_Real,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_Real,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_Real::New() const
{
  return new PDataStd_Real(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_Real::SAdd(const Handle(PDataStd_Real)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_Real")) {
      
    }
  }
}

void StdLSchema_PDataStd_Real::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_Real::SAdd((Handle(PDataStd_Real)&)p,theSchema);
}

void StdLSchema_PDataStd_Real::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_Real) &pp = (Handle(PDataStd_Real)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutReal(pp->_CSFDB_GetPDataStd_RealmyValue());
  f.PutInteger(pp->_CSFDB_GetPDataStd_RealmyDimension());

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_Real::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_Real::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_Real::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_Real) &pp = (Handle(PDataStd_Real)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Real PDataStd_RealmyValue;
    f.GetReal(PDataStd_RealmyValue);
    pp->_CSFDB_SetPDataStd_RealmyValue(PDataStd_RealmyValue);

    Standard_Integer PDataStd_RealmyDimension;
    f.GetInteger(PDataStd_RealmyDimension);
    pp->_CSFDB_SetPDataStd_RealmyDimension(PDataStd_RealmyDimension);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_Real::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_Real::SRead(p,f,theSchema);
}
