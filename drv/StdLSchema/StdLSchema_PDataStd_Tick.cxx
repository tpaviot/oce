#ifndef _StdLSchema_PDataStd_Tick_HeaderFile
#include <StdLSchema_PDataStd_Tick.hxx>
#endif
#ifndef _PDataStd_Tick_HeaderFile
#include <PDataStd_Tick.hxx>
#endif
#include <StdLSchema_PDataStd_Tick.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_Tick,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_Tick,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_Tick::New() const
{
  return new PDataStd_Tick(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_Tick::SAdd(const Handle(PDataStd_Tick)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_Tick")) {
      
    }
  }
}

void StdLSchema_PDataStd_Tick::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_Tick::SAdd((Handle(PDataStd_Tick)&)p,theSchema);
}

void StdLSchema_PDataStd_Tick::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_Tick::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_Tick::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_Tick::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
 
    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_Tick::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_Tick::SRead(p,f,theSchema);
}
