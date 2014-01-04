#ifndef _ShapeSchema_PGeom_ConicalSurface_HeaderFile
#include <ShapeSchema_PGeom_ConicalSurface.hxx>
#endif
#ifndef _PGeom_ConicalSurface_HeaderFile
#include <PGeom_ConicalSurface.hxx>
#endif
#include <ShapeSchema_PGeom_ConicalSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_ConicalSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_ConicalSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_ConicalSurface::New() const
{
  return new PGeom_ConicalSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_ConicalSurface::SAdd(const Handle(PGeom_ConicalSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_ConicalSurface")) {
      
    }
  }
}

void ShapeSchema_PGeom_ConicalSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_ConicalSurface::SAdd((Handle(PGeom_ConicalSurface)&)p,theSchema);
}

void ShapeSchema_PGeom_ConicalSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_ConicalSurface) &pp = (Handle(PGeom_ConicalSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax3::SWrite(pp->_CSFDB_GetPGeom_ElementarySurfaceposition(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPGeom_ConicalSurfaceradius());
  f.PutReal(pp->_CSFDB_GetPGeom_ConicalSurfacesemiAngle());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_ConicalSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_ConicalSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_ConicalSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_ConicalSurface) &pp = (Handle(PGeom_ConicalSurface)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax3::SRead((gp_Ax3&)pp->_CSFDB_GetPGeom_ElementarySurfaceposition(),f,theSchema);

    Standard_Real PGeom_ConicalSurfaceradius;
    f.GetReal(PGeom_ConicalSurfaceradius);
    pp->_CSFDB_SetPGeom_ConicalSurfaceradius(PGeom_ConicalSurfaceradius);

    Standard_Real PGeom_ConicalSurfacesemiAngle;
    f.GetReal(PGeom_ConicalSurfacesemiAngle);
    pp->_CSFDB_SetPGeom_ConicalSurfacesemiAngle(PGeom_ConicalSurfacesemiAngle);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_ConicalSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_ConicalSurface::SRead(p,f,theSchema);
}
