#ifndef _ShapeSchema_PGeom_ElementarySurface_HeaderFile
#include <ShapeSchema_PGeom_ElementarySurface.hxx>
#endif
#ifndef _PGeom_ElementarySurface_HeaderFile
#include <PGeom_ElementarySurface.hxx>
#endif
#include <ShapeSchema_PGeom_ElementarySurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_ElementarySurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_ElementarySurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_ElementarySurface::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PGeom_ElementarySurface::SAdd(const Handle(PGeom_ElementarySurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_ElementarySurface")) {
      
    }
  }
}

void ShapeSchema_PGeom_ElementarySurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_ElementarySurface::SAdd((Handle(PGeom_ElementarySurface)&)p,theSchema);
}

void ShapeSchema_PGeom_ElementarySurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_ElementarySurface) &pp = (Handle(PGeom_ElementarySurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax3::SWrite(pp->_CSFDB_GetPGeom_ElementarySurfaceposition(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_ElementarySurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_ElementarySurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_ElementarySurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_ElementarySurface) &pp = (Handle(PGeom_ElementarySurface)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax3::SRead((gp_Ax3&)pp->_CSFDB_GetPGeom_ElementarySurfaceposition(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_ElementarySurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_ElementarySurface::SRead(p,f,theSchema);
}
