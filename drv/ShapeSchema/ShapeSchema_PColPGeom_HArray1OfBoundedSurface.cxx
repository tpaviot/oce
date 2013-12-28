#ifndef _ShapeSchema_PColPGeom_HArray1OfBoundedSurface_HeaderFile
#include <ShapeSchema_PColPGeom_HArray1OfBoundedSurface.hxx>
#endif
#ifndef _PColPGeom_HArray1OfBoundedSurface_HeaderFile
#include <PColPGeom_HArray1OfBoundedSurface.hxx>
#endif
#include <ShapeSchema_PColPGeom_HArray1OfBoundedSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColPGeom_HArray1OfBoundedSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColPGeom_HArray1OfBoundedSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColPGeom_HArray1OfBoundedSurface::New() const
{
  return new PColPGeom_HArray1OfBoundedSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PColPGeom_HArray1OfBoundedSurface::SAdd(const Handle(PColPGeom_HArray1OfBoundedSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColPGeom_HArray1OfBoundedSurface")) {
         ShapeSchema_PColPGeom_FieldOfHArray1OfBoundedSurface::SAdd(p->_CSFDB_GetPColPGeom_HArray1OfBoundedSurfaceData(),theSchema);

    }
  }
}

void ShapeSchema_PColPGeom_HArray1OfBoundedSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColPGeom_HArray1OfBoundedSurface::SAdd((Handle(PColPGeom_HArray1OfBoundedSurface)&)p,theSchema);
}

void ShapeSchema_PColPGeom_HArray1OfBoundedSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom_HArray1OfBoundedSurface) &pp = (Handle(PColPGeom_HArray1OfBoundedSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray1OfBoundedSurfaceLowerBound());
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray1OfBoundedSurfaceUpperBound());
    ShapeSchema_PColPGeom_FieldOfHArray1OfBoundedSurface::SWrite(pp->_CSFDB_GetPColPGeom_HArray1OfBoundedSurfaceData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColPGeom_HArray1OfBoundedSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColPGeom_HArray1OfBoundedSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PColPGeom_HArray1OfBoundedSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom_HArray1OfBoundedSurface) &pp = (Handle(PColPGeom_HArray1OfBoundedSurface)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColPGeom_HArray1OfBoundedSurfaceLowerBound;
    f.GetInteger(PColPGeom_HArray1OfBoundedSurfaceLowerBound);
    pp->_CSFDB_SetPColPGeom_HArray1OfBoundedSurfaceLowerBound(PColPGeom_HArray1OfBoundedSurfaceLowerBound);

    Standard_Integer PColPGeom_HArray1OfBoundedSurfaceUpperBound;
    f.GetInteger(PColPGeom_HArray1OfBoundedSurfaceUpperBound);
    pp->_CSFDB_SetPColPGeom_HArray1OfBoundedSurfaceUpperBound(PColPGeom_HArray1OfBoundedSurfaceUpperBound);

    ShapeSchema_PColPGeom_FieldOfHArray1OfBoundedSurface::SRead((PColPGeom_FieldOfHArray1OfBoundedSurface&)pp->_CSFDB_GetPColPGeom_HArray1OfBoundedSurfaceData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColPGeom_HArray1OfBoundedSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColPGeom_HArray1OfBoundedSurface::SRead(p,f,theSchema);
}
