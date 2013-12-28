#ifndef _ShapeSchema_PGeom_Plane_HeaderFile
#include <ShapeSchema_PGeom_Plane.hxx>
#endif
#ifndef _PGeom_Plane_HeaderFile
#include <PGeom_Plane.hxx>
#endif
#include <ShapeSchema_PGeom_Plane.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_Plane,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_Plane,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_Plane::New() const
{
  return new PGeom_Plane(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_Plane::SAdd(const Handle(PGeom_Plane)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_Plane")) {
      
    }
  }
}

void ShapeSchema_PGeom_Plane::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_Plane::SAdd((Handle(PGeom_Plane)&)p,theSchema);
}

void ShapeSchema_PGeom_Plane::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Plane) &pp = (Handle(PGeom_Plane)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax3::SWrite(pp->_CSFDB_GetPGeom_ElementarySurfaceposition(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_Plane::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_Plane::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_Plane::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Plane) &pp = (Handle(PGeom_Plane)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax3::SRead((gp_Ax3&)pp->_CSFDB_GetPGeom_ElementarySurfaceposition(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_Plane::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_Plane::SRead(p,f,theSchema);
}
