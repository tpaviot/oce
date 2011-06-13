#ifndef _StdSchema_PDataXtd_Point_HeaderFile
#include <StdSchema_PDataXtd_Point.hxx>
#endif
#ifndef _PDataXtd_Point_HeaderFile
#include <PDataXtd_Point.hxx>
#endif
#include <StdSchema_PDataXtd_Point.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PDataXtd_Point,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PDataXtd_Point,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PDataXtd_Point::New() const
{
  return new PDataXtd_Point(Storage_stCONSTclCOM());
}

void StdSchema_PDataXtd_Point::SAdd(const Handle(PDataXtd_Point)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataXtd_Point")) {
      
    }
  }
}

void StdSchema_PDataXtd_Point::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PDataXtd_Point::SAdd((Handle(PDataXtd_Point)&)p,theSchema);
}

void StdSchema_PDataXtd_Point::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PDataXtd_Point::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PDataXtd_Point::SWrite(p,f,theSchema);
}


void StdSchema_PDataXtd_Point::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
 
    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PDataXtd_Point::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PDataXtd_Point::SRead(p,f,theSchema);
}
