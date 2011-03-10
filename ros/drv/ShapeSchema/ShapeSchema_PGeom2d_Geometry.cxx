#ifndef _ShapeSchema_PGeom2d_Geometry_HeaderFile
#include <ShapeSchema_PGeom2d_Geometry.hxx>
#endif
#ifndef _PGeom2d_Geometry_HeaderFile
#include <PGeom2d_Geometry.hxx>
#endif
#include <ShapeSchema_PGeom2d_Geometry.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_Geometry,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_Geometry,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_Geometry::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PGeom2d_Geometry::SAdd(const Handle(PGeom2d_Geometry)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_Geometry")) {
      
    }
  }
}

void ShapeSchema_PGeom2d_Geometry::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_Geometry::SAdd((Handle(PGeom2d_Geometry)&)p,theSchema);
}

void ShapeSchema_PGeom2d_Geometry::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Geometry) &pp = (Handle(PGeom2d_Geometry)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Geometry::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_Geometry::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_Geometry::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Geometry) &pp = (Handle(PGeom2d_Geometry)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Geometry::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_Geometry::SRead(p,f,theSchema);
}
