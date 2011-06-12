#ifndef _ShapeSchema_PGeom_BoundedSurface_HeaderFile
#include <ShapeSchema_PGeom_BoundedSurface.hxx>
#endif
#ifndef _PGeom_BoundedSurface_HeaderFile
#include <PGeom_BoundedSurface.hxx>
#endif
#include <ShapeSchema_PGeom_BoundedSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_BoundedSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_BoundedSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_BoundedSurface::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PGeom_BoundedSurface::SAdd(const Handle(PGeom_BoundedSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_BoundedSurface")) {
      
    }
  }
}

void ShapeSchema_PGeom_BoundedSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_BoundedSurface::SAdd((Handle(PGeom_BoundedSurface)&)p,theSchema);
}

void ShapeSchema_PGeom_BoundedSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_BoundedSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_BoundedSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_BoundedSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
  
    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_BoundedSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_BoundedSurface::SRead(p,f,theSchema);
}
