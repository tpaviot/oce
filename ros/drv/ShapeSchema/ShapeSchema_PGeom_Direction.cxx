#ifndef _ShapeSchema_PGeom_Direction_HeaderFile
#include <ShapeSchema_PGeom_Direction.hxx>
#endif
#ifndef _PGeom_Direction_HeaderFile
#include <PGeom_Direction.hxx>
#endif
#include <ShapeSchema_PGeom_Direction.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_Direction,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_Direction,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_Direction::New() const
{
  return new PGeom_Direction(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_Direction::SAdd(const Handle(PGeom_Direction)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_Direction")) {
      
    }
  }
}

void ShapeSchema_PGeom_Direction::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_Direction::SAdd((Handle(PGeom_Direction)&)p,theSchema);
}

void ShapeSchema_PGeom_Direction::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Direction) &pp = (Handle(PGeom_Direction)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Vec::SWrite(pp->_CSFDB_GetPGeom_Vectorvec(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_Direction::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_Direction::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_Direction::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Direction) &pp = (Handle(PGeom_Direction)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Vec::SRead((gp_Vec&)pp->_CSFDB_GetPGeom_Vectorvec(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_Direction::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_Direction::SRead(p,f,theSchema);
}
