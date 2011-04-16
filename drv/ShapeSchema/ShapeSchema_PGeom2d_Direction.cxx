#ifndef _ShapeSchema_PGeom2d_Direction_HeaderFile
#include <ShapeSchema_PGeom2d_Direction.hxx>
#endif
#ifndef _PGeom2d_Direction_HeaderFile
#include <PGeom2d_Direction.hxx>
#endif
#include <ShapeSchema_PGeom2d_Direction.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_Direction,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_Direction,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_Direction::New() const
{
  return new PGeom2d_Direction(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom2d_Direction::SAdd(const Handle(PGeom2d_Direction)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_Direction")) {
      
    }
  }
}

void ShapeSchema_PGeom2d_Direction::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_Direction::SAdd((Handle(PGeom2d_Direction)&)p,theSchema);
}

void ShapeSchema_PGeom2d_Direction::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Direction) &pp = (Handle(PGeom2d_Direction)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Vec2d::SWrite(pp->_CSFDB_GetPGeom2d_Vectorvec(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Direction::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_Direction::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_Direction::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Direction) &pp = (Handle(PGeom2d_Direction)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Vec2d::SRead((gp_Vec2d&)pp->_CSFDB_GetPGeom2d_Vectorvec(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Direction::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_Direction::SRead(p,f,theSchema);
}
