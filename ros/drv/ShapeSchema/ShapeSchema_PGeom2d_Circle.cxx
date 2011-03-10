#ifndef _ShapeSchema_PGeom2d_Circle_HeaderFile
#include <ShapeSchema_PGeom2d_Circle.hxx>
#endif
#ifndef _PGeom2d_Circle_HeaderFile
#include <PGeom2d_Circle.hxx>
#endif
#include <ShapeSchema_PGeom2d_Circle.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_Circle,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_Circle,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_Circle::New() const
{
  return new PGeom2d_Circle(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom2d_Circle::SAdd(const Handle(PGeom2d_Circle)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_Circle")) {
      
    }
  }
}

void ShapeSchema_PGeom2d_Circle::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_Circle::SAdd((Handle(PGeom2d_Circle)&)p,theSchema);
}

void ShapeSchema_PGeom2d_Circle::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Circle) &pp = (Handle(PGeom2d_Circle)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax22d::SWrite(pp->_CSFDB_GetPGeom2d_Conicposition(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPGeom2d_Circleradius());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Circle::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_Circle::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_Circle::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Circle) &pp = (Handle(PGeom2d_Circle)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax22d::SRead((gp_Ax22d&)pp->_CSFDB_GetPGeom2d_Conicposition(),f,theSchema);

    Standard_Real PGeom2d_Circleradius;
    f.GetReal(PGeom2d_Circleradius);
    pp->_CSFDB_SetPGeom2d_Circleradius(PGeom2d_Circleradius);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Circle::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_Circle::SRead(p,f,theSchema);
}
