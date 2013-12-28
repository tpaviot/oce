#ifndef _ShapeSchema_PGeom2d_Curve_HeaderFile
#include <ShapeSchema_PGeom2d_Curve.hxx>
#endif
#ifndef _PGeom2d_Curve_HeaderFile
#include <PGeom2d_Curve.hxx>
#endif
#include <ShapeSchema_PGeom2d_Curve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_Curve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_Curve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_Curve::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PGeom2d_Curve::SAdd(const Handle(PGeom2d_Curve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_Curve")) {
      
    }
  }
}

void ShapeSchema_PGeom2d_Curve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_Curve::SAdd((Handle(PGeom2d_Curve)&)p,theSchema);
}

void ShapeSchema_PGeom2d_Curve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Curve) &pp = (Handle(PGeom2d_Curve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Curve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_Curve::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_Curve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Curve) &pp = (Handle(PGeom2d_Curve)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Curve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_Curve::SRead(p,f,theSchema);
}
