#ifndef _StdSchema_Standard_Persistent_HeaderFile
#include <StdSchema_Standard_Persistent.hxx>
#endif
#ifndef _Standard_Persistent_HeaderFile
#include <Standard_Persistent.hxx>
#endif
#include <StdSchema_Standard_Persistent.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_Standard_Persistent,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_Standard_Persistent,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_Standard_Persistent::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void StdSchema_Standard_Persistent::SAdd(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"Standard_Persistent")) {
      
    }
  }
}

void StdSchema_Standard_Persistent::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_Standard_Persistent::SAdd((Handle(Standard_Persistent)&)p,theSchema);
}

void StdSchema_Standard_Persistent::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(Standard_Persistent) &pp = (Handle(Standard_Persistent)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_Standard_Persistent::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_Standard_Persistent::SWrite(p,f,theSchema);
}


void StdSchema_Standard_Persistent::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(Standard_Persistent) &pp = (Handle(Standard_Persistent)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_Standard_Persistent::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_Standard_Persistent::SRead(p,f,theSchema);
}
