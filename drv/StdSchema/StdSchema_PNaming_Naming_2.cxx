#ifndef _StdSchema_PNaming_Naming_2_HeaderFile
#include <StdSchema_PNaming_Naming_2.hxx>
#endif
#ifndef _PNaming_Naming_2_HeaderFile
#include <PNaming_Naming_2.hxx>
#endif
#include <StdSchema_PNaming_Naming_2.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PNaming_Naming_2,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PNaming_Naming_2,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PNaming_Naming_2::New() const
{
  return new PNaming_Naming_2(Storage_stCONSTclCOM());
}

void StdSchema_PNaming_Naming_2::SAdd(const Handle(PNaming_Naming_2)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PNaming_Naming_2")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPNaming_Naming_2myName());

    }
  }
}

void StdSchema_PNaming_Naming_2::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PNaming_Naming_2::SAdd((Handle(PNaming_Naming_2)&)p,theSchema);
}

void StdSchema_PNaming_Naming_2::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PNaming_Naming_2) &pp = (Handle(PNaming_Naming_2)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPNaming_Naming_2myName(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PNaming_Naming_2::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PNaming_Naming_2::SWrite(p,f,theSchema);
}


void StdSchema_PNaming_Naming_2::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PNaming_Naming_2) &pp = (Handle(PNaming_Naming_2)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PNaming_Name_2) PNaming_Naming_2myName;

    theSchema->ReadPersistentReference(PNaming_Naming_2myName,f);
    pp->_CSFDB_SetPNaming_Naming_2myName(PNaming_Naming_2myName);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PNaming_Naming_2::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PNaming_Naming_2::SRead(p,f,theSchema);
}
