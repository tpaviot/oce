#ifndef _ShapeSchema_PColPGeom_HArray1OfSurface_HeaderFile
#include <ShapeSchema_PColPGeom_HArray1OfSurface.hxx>
#endif
#ifndef _PColPGeom_HArray1OfSurface_HeaderFile
#include <PColPGeom_HArray1OfSurface.hxx>
#endif
#include <ShapeSchema_PColPGeom_HArray1OfSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColPGeom_HArray1OfSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColPGeom_HArray1OfSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColPGeom_HArray1OfSurface::New() const
{
  return new PColPGeom_HArray1OfSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PColPGeom_HArray1OfSurface::SAdd(const Handle(PColPGeom_HArray1OfSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColPGeom_HArray1OfSurface")) {
         ShapeSchema_PColPGeom_FieldOfHArray1OfSurface::SAdd(p->_CSFDB_GetPColPGeom_HArray1OfSurfaceData(),theSchema);

    }
  }
}

void ShapeSchema_PColPGeom_HArray1OfSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColPGeom_HArray1OfSurface::SAdd((Handle(PColPGeom_HArray1OfSurface)&)p,theSchema);
}

void ShapeSchema_PColPGeom_HArray1OfSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom_HArray1OfSurface) &pp = (Handle(PColPGeom_HArray1OfSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray1OfSurfaceLowerBound());
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray1OfSurfaceUpperBound());
    ShapeSchema_PColPGeom_FieldOfHArray1OfSurface::SWrite(pp->_CSFDB_GetPColPGeom_HArray1OfSurfaceData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColPGeom_HArray1OfSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColPGeom_HArray1OfSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PColPGeom_HArray1OfSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom_HArray1OfSurface) &pp = (Handle(PColPGeom_HArray1OfSurface)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColPGeom_HArray1OfSurfaceLowerBound;
    f.GetInteger(PColPGeom_HArray1OfSurfaceLowerBound);
    pp->_CSFDB_SetPColPGeom_HArray1OfSurfaceLowerBound(PColPGeom_HArray1OfSurfaceLowerBound);

    Standard_Integer PColPGeom_HArray1OfSurfaceUpperBound;
    f.GetInteger(PColPGeom_HArray1OfSurfaceUpperBound);
    pp->_CSFDB_SetPColPGeom_HArray1OfSurfaceUpperBound(PColPGeom_HArray1OfSurfaceUpperBound);

    ShapeSchema_PColPGeom_FieldOfHArray1OfSurface::SRead((PColPGeom_FieldOfHArray1OfSurface&)pp->_CSFDB_GetPColPGeom_HArray1OfSurfaceData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColPGeom_HArray1OfSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColPGeom_HArray1OfSurface::SRead(p,f,theSchema);
}
