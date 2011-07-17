#ifndef _StdSchema_PDataXtd_Placement_HeaderFile
#include <StdSchema_PDataXtd_Placement.hxx>
#endif
#ifndef _PDataXtd_Placement_HeaderFile
#include <PDataXtd_Placement.hxx>
#endif
#include <StdSchema_PDataXtd_Placement.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PDataXtd_Placement,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PDataXtd_Placement,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PDataXtd_Placement::New() const
{
  return new PDataXtd_Placement(Storage_stCONSTclCOM());
}

void StdSchema_PDataXtd_Placement::SAdd(const Handle(PDataXtd_Placement)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataXtd_Placement")) {
      
    }
  }
}

void StdSchema_PDataXtd_Placement::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PDataXtd_Placement::SAdd((Handle(PDataXtd_Placement)&)p,theSchema);
}

void StdSchema_PDataXtd_Placement::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataXtd_Placement) &pp = (Handle(PDataXtd_Placement)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PDataXtd_Placement::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PDataXtd_Placement::SWrite(p,f,theSchema);
}


void StdSchema_PDataXtd_Placement::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataXtd_Placement) &pp = (Handle(PDataXtd_Placement)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PDataXtd_Placement::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PDataXtd_Placement::SRead(p,f,theSchema);
}
