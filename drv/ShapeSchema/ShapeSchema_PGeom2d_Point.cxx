#ifndef _ShapeSchema_PGeom2d_Point_HeaderFile
#include <ShapeSchema_PGeom2d_Point.hxx>
#endif
#ifndef _PGeom2d_Point_HeaderFile
#include <PGeom2d_Point.hxx>
#endif
#include <ShapeSchema_PGeom2d_Point.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_Point,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_Point,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_Point::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PGeom2d_Point::SAdd(const Handle(PGeom2d_Point)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_Point")) {
      
    }
  }
}

void ShapeSchema_PGeom2d_Point::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_Point::SAdd((Handle(PGeom2d_Point)&)p,theSchema);
}

void ShapeSchema_PGeom2d_Point::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Point) &pp = (Handle(PGeom2d_Point)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Point::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_Point::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_Point::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Point) &pp = (Handle(PGeom2d_Point)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Point::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_Point::SRead(p,f,theSchema);
}
