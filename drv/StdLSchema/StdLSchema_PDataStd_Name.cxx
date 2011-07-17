#ifndef _StdLSchema_PDataStd_Name_HeaderFile
#include <StdLSchema_PDataStd_Name.hxx>
#endif
#ifndef _PDataStd_Name_HeaderFile
#include <PDataStd_Name.hxx>
#endif
#include <StdLSchema_PDataStd_Name.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_Name,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_Name,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_Name::New() const
{
  return new PDataStd_Name(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_Name::SAdd(const Handle(PDataStd_Name)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_Name")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_NamemyValue());

    }
  }
}

void StdLSchema_PDataStd_Name::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_Name::SAdd((Handle(PDataStd_Name)&)p,theSchema);
}

void StdLSchema_PDataStd_Name::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_Name) &pp = (Handle(PDataStd_Name)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_NamemyValue(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_Name::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_Name::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_Name::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_Name) &pp = (Handle(PDataStd_Name)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PCollection_HExtendedString) PDataStd_NamemyValue;

    theSchema->ReadPersistentReference(PDataStd_NamemyValue,f);
    pp->_CSFDB_SetPDataStd_NamemyValue(PDataStd_NamemyValue);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_Name::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_Name::SRead(p,f,theSchema);
}
