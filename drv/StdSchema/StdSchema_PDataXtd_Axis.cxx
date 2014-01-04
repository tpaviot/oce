#ifndef _StdSchema_PDataXtd_Axis_HeaderFile
#include <StdSchema_PDataXtd_Axis.hxx>
#endif
#ifndef _PDataXtd_Axis_HeaderFile
#include <PDataXtd_Axis.hxx>
#endif
#include <StdSchema_PDataXtd_Axis.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PDataXtd_Axis,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PDataXtd_Axis,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PDataXtd_Axis::New() const
{
  return new PDataXtd_Axis(Storage_stCONSTclCOM());
}

void StdSchema_PDataXtd_Axis::SAdd(const Handle(PDataXtd_Axis)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataXtd_Axis")) {
      
    }
  }
}

void StdSchema_PDataXtd_Axis::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PDataXtd_Axis::SAdd((Handle(PDataXtd_Axis)&)p,theSchema);
}

void StdSchema_PDataXtd_Axis::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataXtd_Axis) &pp = (Handle(PDataXtd_Axis)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PDataXtd_Axis::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PDataXtd_Axis::SWrite(p,f,theSchema);
}


void StdSchema_PDataXtd_Axis::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataXtd_Axis) &pp = (Handle(PDataXtd_Axis)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PDataXtd_Axis::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PDataXtd_Axis::SRead(p,f,theSchema);
}
