#ifndef _ShapeSchema_PGeom2d_BoundedCurve_HeaderFile
#include <ShapeSchema_PGeom2d_BoundedCurve.hxx>
#endif
#ifndef _PGeom2d_BoundedCurve_HeaderFile
#include <PGeom2d_BoundedCurve.hxx>
#endif
#include <ShapeSchema_PGeom2d_BoundedCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_BoundedCurve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_BoundedCurve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_BoundedCurve::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PGeom2d_BoundedCurve::SAdd(const Handle(PGeom2d_BoundedCurve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_BoundedCurve")) {
      
    }
  }
}

void ShapeSchema_PGeom2d_BoundedCurve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_BoundedCurve::SAdd((Handle(PGeom2d_BoundedCurve)&)p,theSchema);
}

void ShapeSchema_PGeom2d_BoundedCurve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_BoundedCurve) &pp = (Handle(PGeom2d_BoundedCurve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_BoundedCurve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_BoundedCurve::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_BoundedCurve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_BoundedCurve) &pp = (Handle(PGeom2d_BoundedCurve)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_BoundedCurve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_BoundedCurve::SRead(p,f,theSchema);
}
