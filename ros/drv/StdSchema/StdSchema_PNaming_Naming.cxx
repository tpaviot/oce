#ifndef _StdSchema_PNaming_Naming_HeaderFile
#include <StdSchema_PNaming_Naming.hxx>
#endif
#ifndef _PNaming_Naming_HeaderFile
#include <PNaming_Naming.hxx>
#endif
#include <StdSchema_PNaming_Naming.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PNaming_Naming,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PNaming_Naming,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PNaming_Naming::New() const
{
  return new PNaming_Naming(Storage_stCONSTclCOM());
}

void StdSchema_PNaming_Naming::SAdd(const Handle(PNaming_Naming)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PNaming_Naming")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPNaming_NamingmyName());

    }
  }
}

void StdSchema_PNaming_Naming::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PNaming_Naming::SAdd((Handle(PNaming_Naming)&)p,theSchema);
}

void StdSchema_PNaming_Naming::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PNaming_Naming) &pp = (Handle(PNaming_Naming)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPNaming_NamingmyName(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PNaming_Naming::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PNaming_Naming::SWrite(p,f,theSchema);
}


void StdSchema_PNaming_Naming::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PNaming_Naming) &pp = (Handle(PNaming_Naming)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PNaming_Name) PNaming_NamingmyName;

    theSchema->ReadPersistentReference(PNaming_NamingmyName,f);
    pp->_CSFDB_SetPNaming_NamingmyName(PNaming_NamingmyName);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PNaming_Naming::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PNaming_Naming::SRead(p,f,theSchema);
}
