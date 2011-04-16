#ifndef _StdSchema_PNaming_Naming_1_HeaderFile
#include <StdSchema_PNaming_Naming_1.hxx>
#endif
#ifndef _PNaming_Naming_1_HeaderFile
#include <PNaming_Naming_1.hxx>
#endif
#include <StdSchema_PNaming_Naming_1.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PNaming_Naming_1,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PNaming_Naming_1,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PNaming_Naming_1::New() const
{
  return new PNaming_Naming_1(Storage_stCONSTclCOM());
}

void StdSchema_PNaming_Naming_1::SAdd(const Handle(PNaming_Naming_1)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PNaming_Naming_1")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPNaming_Naming_1myName());

    }
  }
}

void StdSchema_PNaming_Naming_1::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PNaming_Naming_1::SAdd((Handle(PNaming_Naming_1)&)p,theSchema);
}

void StdSchema_PNaming_Naming_1::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PNaming_Naming_1) &pp = (Handle(PNaming_Naming_1)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPNaming_Naming_1myName(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PNaming_Naming_1::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PNaming_Naming_1::SWrite(p,f,theSchema);
}


void StdSchema_PNaming_Naming_1::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PNaming_Naming_1) &pp = (Handle(PNaming_Naming_1)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PNaming_Name_1) PNaming_Naming_1myName;

    theSchema->ReadPersistentReference(PNaming_Naming_1myName,f);
    pp->_CSFDB_SetPNaming_Naming_1myName(PNaming_Naming_1myName);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PNaming_Naming_1::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PNaming_Naming_1::SRead(p,f,theSchema);
}
