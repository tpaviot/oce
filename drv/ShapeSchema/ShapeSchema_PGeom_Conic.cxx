#ifndef _ShapeSchema_PGeom_Conic_HeaderFile
#include <ShapeSchema_PGeom_Conic.hxx>
#endif
#ifndef _PGeom_Conic_HeaderFile
#include <PGeom_Conic.hxx>
#endif
#include <ShapeSchema_PGeom_Conic.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_Conic,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_Conic,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_Conic::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PGeom_Conic::SAdd(const Handle(PGeom_Conic)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_Conic")) {
      
    }
  }
}

void ShapeSchema_PGeom_Conic::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_Conic::SAdd((Handle(PGeom_Conic)&)p,theSchema);
}

void ShapeSchema_PGeom_Conic::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Conic) &pp = (Handle(PGeom_Conic)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax2::SWrite(pp->_CSFDB_GetPGeom_Conicposition(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_Conic::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_Conic::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_Conic::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Conic) &pp = (Handle(PGeom_Conic)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax2::SRead((gp_Ax2&)pp->_CSFDB_GetPGeom_Conicposition(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_Conic::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_Conic::SRead(p,f,theSchema);
}
