#ifndef _StdSchema_PDataXtd_Plane_HeaderFile
#include <StdSchema_PDataXtd_Plane.hxx>
#endif
#ifndef _PDataXtd_Plane_HeaderFile
#include <PDataXtd_Plane.hxx>
#endif
#include <StdSchema_PDataXtd_Plane.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PDataXtd_Plane,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PDataXtd_Plane,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PDataXtd_Plane::New() const
{
  return new PDataXtd_Plane(Storage_stCONSTclCOM());
}

void StdSchema_PDataXtd_Plane::SAdd(const Handle(PDataXtd_Plane)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataXtd_Plane")) {
      
    }
  }
}

void StdSchema_PDataXtd_Plane::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PDataXtd_Plane::SAdd((Handle(PDataXtd_Plane)&)p,theSchema);
}

void StdSchema_PDataXtd_Plane::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataXtd_Plane) &pp = (Handle(PDataXtd_Plane)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PDataXtd_Plane::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PDataXtd_Plane::SWrite(p,f,theSchema);
}


void StdSchema_PDataXtd_Plane::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataXtd_Plane) &pp = (Handle(PDataXtd_Plane)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PDataXtd_Plane::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PDataXtd_Plane::SRead(p,f,theSchema);
}
