#ifndef _ShapeSchema_PGeom_VectorWithMagnitude_HeaderFile
#include <ShapeSchema_PGeom_VectorWithMagnitude.hxx>
#endif
#ifndef _PGeom_VectorWithMagnitude_HeaderFile
#include <PGeom_VectorWithMagnitude.hxx>
#endif
#include <ShapeSchema_PGeom_VectorWithMagnitude.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_VectorWithMagnitude,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_VectorWithMagnitude,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_VectorWithMagnitude::New() const
{
  return new PGeom_VectorWithMagnitude(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_VectorWithMagnitude::SAdd(const Handle(PGeom_VectorWithMagnitude)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_VectorWithMagnitude")) {
      
    }
  }
}

void ShapeSchema_PGeom_VectorWithMagnitude::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_VectorWithMagnitude::SAdd((Handle(PGeom_VectorWithMagnitude)&)p,theSchema);
}

void ShapeSchema_PGeom_VectorWithMagnitude::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_VectorWithMagnitude) &pp = (Handle(PGeom_VectorWithMagnitude)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Vec::SWrite(pp->_CSFDB_GetPGeom_Vectorvec(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_VectorWithMagnitude::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_VectorWithMagnitude::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_VectorWithMagnitude::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_VectorWithMagnitude) &pp = (Handle(PGeom_VectorWithMagnitude)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Vec::SRead((gp_Vec&)pp->_CSFDB_GetPGeom_Vectorvec(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_VectorWithMagnitude::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_VectorWithMagnitude::SRead(p,f,theSchema);
}
