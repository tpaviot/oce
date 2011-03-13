#ifndef _ShapeSchema_PGeom_ToroidalSurface_HeaderFile
#include <ShapeSchema_PGeom_ToroidalSurface.hxx>
#endif
#ifndef _PGeom_ToroidalSurface_HeaderFile
#include <PGeom_ToroidalSurface.hxx>
#endif
#include <ShapeSchema_PGeom_ToroidalSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_ToroidalSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_ToroidalSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_ToroidalSurface::New() const
{
  return new PGeom_ToroidalSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_ToroidalSurface::SAdd(const Handle(PGeom_ToroidalSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_ToroidalSurface")) {
      
    }
  }
}

void ShapeSchema_PGeom_ToroidalSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_ToroidalSurface::SAdd((Handle(PGeom_ToroidalSurface)&)p,theSchema);
}

void ShapeSchema_PGeom_ToroidalSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_ToroidalSurface) &pp = (Handle(PGeom_ToroidalSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax3::SWrite(pp->_CSFDB_GetPGeom_ElementarySurfaceposition(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPGeom_ToroidalSurfacemajorRadius());
  f.PutReal(pp->_CSFDB_GetPGeom_ToroidalSurfaceminorRadius());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_ToroidalSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_ToroidalSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_ToroidalSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_ToroidalSurface) &pp = (Handle(PGeom_ToroidalSurface)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax3::SRead((gp_Ax3&)pp->_CSFDB_GetPGeom_ElementarySurfaceposition(),f,theSchema);

    Standard_Real PGeom_ToroidalSurfacemajorRadius;
    f.GetReal(PGeom_ToroidalSurfacemajorRadius);
    pp->_CSFDB_SetPGeom_ToroidalSurfacemajorRadius(PGeom_ToroidalSurfacemajorRadius);

    Standard_Real PGeom_ToroidalSurfaceminorRadius;
    f.GetReal(PGeom_ToroidalSurfaceminorRadius);
    pp->_CSFDB_SetPGeom_ToroidalSurfaceminorRadius(PGeom_ToroidalSurfaceminorRadius);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_ToroidalSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_ToroidalSurface::SRead(p,f,theSchema);
}
