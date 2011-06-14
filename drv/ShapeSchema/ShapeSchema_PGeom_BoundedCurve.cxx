#ifndef _ShapeSchema_PGeom_BoundedCurve_HeaderFile
#include <ShapeSchema_PGeom_BoundedCurve.hxx>
#endif
#ifndef _PGeom_BoundedCurve_HeaderFile
#include <PGeom_BoundedCurve.hxx>
#endif
#include <ShapeSchema_PGeom_BoundedCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_BoundedCurve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_BoundedCurve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_BoundedCurve::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PGeom_BoundedCurve::SAdd(const Handle(PGeom_BoundedCurve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_BoundedCurve")) {
      
    }
  }
}

void ShapeSchema_PGeom_BoundedCurve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_BoundedCurve::SAdd((Handle(PGeom_BoundedCurve)&)p,theSchema);
}

void ShapeSchema_PGeom_BoundedCurve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_BoundedCurve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_BoundedCurve::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_BoundedCurve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_BoundedCurve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_BoundedCurve::SRead(p,f,theSchema);
}
