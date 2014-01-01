#ifndef _ShapeSchema_PGeom2d_Vector_HeaderFile
#include <ShapeSchema_PGeom2d_Vector.hxx>
#endif
#ifndef _PGeom2d_Vector_HeaderFile
#include <PGeom2d_Vector.hxx>
#endif
#include <ShapeSchema_PGeom2d_Vector.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_Vector,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_Vector,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_Vector::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PGeom2d_Vector::SAdd(const Handle(PGeom2d_Vector)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_Vector")) {
      
    }
  }
}

void ShapeSchema_PGeom2d_Vector::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_Vector::SAdd((Handle(PGeom2d_Vector)&)p,theSchema);
}

void ShapeSchema_PGeom2d_Vector::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Vector) &pp = (Handle(PGeom2d_Vector)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Vec2d::SWrite(pp->_CSFDB_GetPGeom2d_Vectorvec(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Vector::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_Vector::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_Vector::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Vector) &pp = (Handle(PGeom2d_Vector)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Vec2d::SRead((gp_Vec2d&)pp->_CSFDB_GetPGeom2d_Vectorvec(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Vector::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_Vector::SRead(p,f,theSchema);
}
