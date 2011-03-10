#ifndef _ShapeSchema_PGeom_OffsetSurface_HeaderFile
#include <ShapeSchema_PGeom_OffsetSurface.hxx>
#endif
#ifndef _PGeom_OffsetSurface_HeaderFile
#include <PGeom_OffsetSurface.hxx>
#endif
#include <ShapeSchema_PGeom_OffsetSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_OffsetSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_OffsetSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_OffsetSurface::New() const
{
  return new PGeom_OffsetSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_OffsetSurface::SAdd(const Handle(PGeom_OffsetSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_OffsetSurface")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_OffsetSurfacebasisSurface());

    }
  }
}

void ShapeSchema_PGeom_OffsetSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_OffsetSurface::SAdd((Handle(PGeom_OffsetSurface)&)p,theSchema);
}

void ShapeSchema_PGeom_OffsetSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_OffsetSurface) &pp = (Handle(PGeom_OffsetSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_OffsetSurfacebasisSurface(),f);
  f.PutReal(pp->_CSFDB_GetPGeom_OffsetSurfaceoffsetValue());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_OffsetSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_OffsetSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_OffsetSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_OffsetSurface) &pp = (Handle(PGeom_OffsetSurface)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PGeom_Surface) PGeom_OffsetSurfacebasisSurface;

    theSchema->ReadPersistentReference(PGeom_OffsetSurfacebasisSurface,f);
    pp->_CSFDB_SetPGeom_OffsetSurfacebasisSurface(PGeom_OffsetSurfacebasisSurface);

    Standard_Real PGeom_OffsetSurfaceoffsetValue;
    f.GetReal(PGeom_OffsetSurfaceoffsetValue);
    pp->_CSFDB_SetPGeom_OffsetSurfaceoffsetValue(PGeom_OffsetSurfaceoffsetValue);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_OffsetSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_OffsetSurface::SRead(p,f,theSchema);
}
