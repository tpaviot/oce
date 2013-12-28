#ifndef _ShapeSchema_PGeom_Vector_HeaderFile
#include <ShapeSchema_PGeom_Vector.hxx>
#endif
#ifndef _PGeom_Vector_HeaderFile
#include <PGeom_Vector.hxx>
#endif
#include <ShapeSchema_PGeom_Vector.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_Vector,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_Vector,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_Vector::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PGeom_Vector::SAdd(const Handle(PGeom_Vector)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_Vector")) {
      
    }
  }
}

void ShapeSchema_PGeom_Vector::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_Vector::SAdd((Handle(PGeom_Vector)&)p,theSchema);
}

void ShapeSchema_PGeom_Vector::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Vector) &pp = (Handle(PGeom_Vector)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Vec::SWrite(pp->_CSFDB_GetPGeom_Vectorvec(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_Vector::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_Vector::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_Vector::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Vector) &pp = (Handle(PGeom_Vector)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Vec::SRead((gp_Vec&)pp->_CSFDB_GetPGeom_Vectorvec(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_Vector::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_Vector::SRead(p,f,theSchema);
}
