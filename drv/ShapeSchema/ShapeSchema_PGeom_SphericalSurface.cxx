#ifndef _ShapeSchema_PGeom_SphericalSurface_HeaderFile
#include <ShapeSchema_PGeom_SphericalSurface.hxx>
#endif
#ifndef _PGeom_SphericalSurface_HeaderFile
#include <PGeom_SphericalSurface.hxx>
#endif
#include <ShapeSchema_PGeom_SphericalSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_SphericalSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_SphericalSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_SphericalSurface::New() const
{
  return new PGeom_SphericalSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_SphericalSurface::SAdd(const Handle(PGeom_SphericalSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_SphericalSurface")) {
      
    }
  }
}

void ShapeSchema_PGeom_SphericalSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_SphericalSurface::SAdd((Handle(PGeom_SphericalSurface)&)p,theSchema);
}

void ShapeSchema_PGeom_SphericalSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_SphericalSurface) &pp = (Handle(PGeom_SphericalSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax3::SWrite(pp->_CSFDB_GetPGeom_ElementarySurfaceposition(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPGeom_SphericalSurfaceradius());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_SphericalSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_SphericalSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_SphericalSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_SphericalSurface) &pp = (Handle(PGeom_SphericalSurface)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax3::SRead((gp_Ax3&)pp->_CSFDB_GetPGeom_ElementarySurfaceposition(),f,theSchema);

    Standard_Real PGeom_SphericalSurfaceradius;
    f.GetReal(PGeom_SphericalSurfaceradius);
    pp->_CSFDB_SetPGeom_SphericalSurfaceradius(PGeom_SphericalSurfaceradius);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_SphericalSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_SphericalSurface::SRead(p,f,theSchema);
}
