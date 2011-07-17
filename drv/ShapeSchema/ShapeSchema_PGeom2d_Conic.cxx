#ifndef _ShapeSchema_PGeom2d_Conic_HeaderFile
#include <ShapeSchema_PGeom2d_Conic.hxx>
#endif
#ifndef _PGeom2d_Conic_HeaderFile
#include <PGeom2d_Conic.hxx>
#endif
#include <ShapeSchema_PGeom2d_Conic.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_Conic,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_Conic,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_Conic::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PGeom2d_Conic::SAdd(const Handle(PGeom2d_Conic)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_Conic")) {
      
    }
  }
}

void ShapeSchema_PGeom2d_Conic::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_Conic::SAdd((Handle(PGeom2d_Conic)&)p,theSchema);
}

void ShapeSchema_PGeom2d_Conic::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Conic) &pp = (Handle(PGeom2d_Conic)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax22d::SWrite(pp->_CSFDB_GetPGeom2d_Conicposition(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Conic::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_Conic::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_Conic::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Conic) &pp = (Handle(PGeom2d_Conic)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax22d::SRead((gp_Ax22d&)pp->_CSFDB_GetPGeom2d_Conicposition(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Conic::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_Conic::SRead(p,f,theSchema);
}
