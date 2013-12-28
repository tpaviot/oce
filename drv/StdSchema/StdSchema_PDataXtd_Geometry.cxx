#ifndef _StdSchema_PDataXtd_Geometry_HeaderFile
#include <StdSchema_PDataXtd_Geometry.hxx>
#endif
#ifndef _PDataXtd_Geometry_HeaderFile
#include <PDataXtd_Geometry.hxx>
#endif
#include <StdSchema_PDataXtd_Geometry.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PDataXtd_Geometry,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PDataXtd_Geometry,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PDataXtd_Geometry::New() const
{
  return new PDataXtd_Geometry(Storage_stCONSTclCOM());
}

void StdSchema_PDataXtd_Geometry::SAdd(const Handle(PDataXtd_Geometry)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataXtd_Geometry")) {
      
    }
  }
}

void StdSchema_PDataXtd_Geometry::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PDataXtd_Geometry::SAdd((Handle(PDataXtd_Geometry)&)p,theSchema);
}

void StdSchema_PDataXtd_Geometry::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataXtd_Geometry) &pp = (Handle(PDataXtd_Geometry)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPDataXtd_GeometrymyType());

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PDataXtd_Geometry::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PDataXtd_Geometry::SWrite(p,f,theSchema);
}


void StdSchema_PDataXtd_Geometry::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataXtd_Geometry) &pp = (Handle(PDataXtd_Geometry)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PDataXtd_GeometrymyType;
    f.GetInteger(PDataXtd_GeometrymyType);
    pp->_CSFDB_SetPDataXtd_GeometrymyType(PDataXtd_GeometrymyType);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PDataXtd_Geometry::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PDataXtd_Geometry::SRead(p,f,theSchema);
}
