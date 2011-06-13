#ifndef _StdLSchema_PDataStd_Directory_HeaderFile
#include <StdLSchema_PDataStd_Directory.hxx>
#endif
#ifndef _PDataStd_Directory_HeaderFile
#include <PDataStd_Directory.hxx>
#endif
#include <StdLSchema_PDataStd_Directory.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_Directory,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_Directory,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_Directory::New() const
{
  return new PDataStd_Directory(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_Directory::SAdd(const Handle(PDataStd_Directory)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_Directory")) {
      
    }
  }
}

void StdLSchema_PDataStd_Directory::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_Directory::SAdd((Handle(PDataStd_Directory)&)p,theSchema);
}

void StdLSchema_PDataStd_Directory::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_Directory::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_Directory::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_Directory::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
 
    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_Directory::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_Directory::SRead(p,f,theSchema);
}
