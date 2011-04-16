#ifndef _ShapeSchema_PGeom_CylindricalSurface_HeaderFile
#include <ShapeSchema_PGeom_CylindricalSurface.hxx>
#endif
#ifndef _PGeom_CylindricalSurface_HeaderFile
#include <PGeom_CylindricalSurface.hxx>
#endif
#include <ShapeSchema_PGeom_CylindricalSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_CylindricalSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_CylindricalSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_CylindricalSurface::New() const
{
  return new PGeom_CylindricalSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_CylindricalSurface::SAdd(const Handle(PGeom_CylindricalSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_CylindricalSurface")) {
      
    }
  }
}

void ShapeSchema_PGeom_CylindricalSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_CylindricalSurface::SAdd((Handle(PGeom_CylindricalSurface)&)p,theSchema);
}

void ShapeSchema_PGeom_CylindricalSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_CylindricalSurface) &pp = (Handle(PGeom_CylindricalSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax3::SWrite(pp->_CSFDB_GetPGeom_ElementarySurfaceposition(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPGeom_CylindricalSurfaceradius());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_CylindricalSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_CylindricalSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_CylindricalSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_CylindricalSurface) &pp = (Handle(PGeom_CylindricalSurface)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax3::SRead((gp_Ax3&)pp->_CSFDB_GetPGeom_ElementarySurfaceposition(),f,theSchema);

    Standard_Real PGeom_CylindricalSurfaceradius;
    f.GetReal(PGeom_CylindricalSurfaceradius);
    pp->_CSFDB_SetPGeom_CylindricalSurfaceradius(PGeom_CylindricalSurfaceradius);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_CylindricalSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_CylindricalSurface::SRead(p,f,theSchema);
}
