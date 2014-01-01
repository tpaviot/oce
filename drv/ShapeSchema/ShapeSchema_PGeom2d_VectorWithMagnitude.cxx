#ifndef _ShapeSchema_PGeom2d_VectorWithMagnitude_HeaderFile
#include <ShapeSchema_PGeom2d_VectorWithMagnitude.hxx>
#endif
#ifndef _PGeom2d_VectorWithMagnitude_HeaderFile
#include <PGeom2d_VectorWithMagnitude.hxx>
#endif
#include <ShapeSchema_PGeom2d_VectorWithMagnitude.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_VectorWithMagnitude,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_VectorWithMagnitude,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_VectorWithMagnitude::New() const
{
  return new PGeom2d_VectorWithMagnitude(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom2d_VectorWithMagnitude::SAdd(const Handle(PGeom2d_VectorWithMagnitude)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_VectorWithMagnitude")) {
      
    }
  }
}

void ShapeSchema_PGeom2d_VectorWithMagnitude::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_VectorWithMagnitude::SAdd((Handle(PGeom2d_VectorWithMagnitude)&)p,theSchema);
}

void ShapeSchema_PGeom2d_VectorWithMagnitude::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_VectorWithMagnitude) &pp = (Handle(PGeom2d_VectorWithMagnitude)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Vec2d::SWrite(pp->_CSFDB_GetPGeom2d_Vectorvec(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_VectorWithMagnitude::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_VectorWithMagnitude::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_VectorWithMagnitude::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_VectorWithMagnitude) &pp = (Handle(PGeom2d_VectorWithMagnitude)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Vec2d::SRead((gp_Vec2d&)pp->_CSFDB_GetPGeom2d_Vectorvec(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_VectorWithMagnitude::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_VectorWithMagnitude::SRead(p,f,theSchema);
}
