#ifndef _StdSchema_PDataXtd_Shape_HeaderFile
#include <StdSchema_PDataXtd_Shape.hxx>
#endif
#ifndef _PDataXtd_Shape_HeaderFile
#include <PDataXtd_Shape.hxx>
#endif
#include <StdSchema_PDataXtd_Shape.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PDataXtd_Shape,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PDataXtd_Shape,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PDataXtd_Shape::New() const
{
  return new PDataXtd_Shape(Storage_stCONSTclCOM());
}

void StdSchema_PDataXtd_Shape::SAdd(const Handle(PDataXtd_Shape)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataXtd_Shape")) {
      
    }
  }
}

void StdSchema_PDataXtd_Shape::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PDataXtd_Shape::SAdd((Handle(PDataXtd_Shape)&)p,theSchema);
}

void StdSchema_PDataXtd_Shape::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PDataXtd_Shape::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PDataXtd_Shape::SWrite(p,f,theSchema);
}


void StdSchema_PDataXtd_Shape::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
 
    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PDataXtd_Shape::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PDataXtd_Shape::SRead(p,f,theSchema);
}
