#ifndef _ShapeSchema_PGeom_Curve_HeaderFile
#include <ShapeSchema_PGeom_Curve.hxx>
#endif
#ifndef _PGeom_Curve_HeaderFile
#include <PGeom_Curve.hxx>
#endif
#include <ShapeSchema_PGeom_Curve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_Curve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_Curve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_Curve::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PGeom_Curve::SAdd(const Handle(PGeom_Curve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_Curve")) {
      
    }
  }
}

void ShapeSchema_PGeom_Curve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_Curve::SAdd((Handle(PGeom_Curve)&)p,theSchema);
}

void ShapeSchema_PGeom_Curve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Curve) &pp = (Handle(PGeom_Curve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_Curve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_Curve::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_Curve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Curve) &pp = (Handle(PGeom_Curve)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_Curve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_Curve::SRead(p,f,theSchema);
}
