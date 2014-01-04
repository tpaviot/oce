#ifndef _ShapeSchema_PGeom_Circle_HeaderFile
#include <ShapeSchema_PGeom_Circle.hxx>
#endif
#ifndef _PGeom_Circle_HeaderFile
#include <PGeom_Circle.hxx>
#endif
#include <ShapeSchema_PGeom_Circle.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_Circle,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_Circle,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_Circle::New() const
{
  return new PGeom_Circle(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_Circle::SAdd(const Handle(PGeom_Circle)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_Circle")) {
      
    }
  }
}

void ShapeSchema_PGeom_Circle::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_Circle::SAdd((Handle(PGeom_Circle)&)p,theSchema);
}

void ShapeSchema_PGeom_Circle::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Circle) &pp = (Handle(PGeom_Circle)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax2::SWrite(pp->_CSFDB_GetPGeom_Conicposition(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPGeom_Circleradius());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_Circle::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_Circle::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_Circle::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Circle) &pp = (Handle(PGeom_Circle)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax2::SRead((gp_Ax2&)pp->_CSFDB_GetPGeom_Conicposition(),f,theSchema);

    Standard_Real PGeom_Circleradius;
    f.GetReal(PGeom_Circleradius);
    pp->_CSFDB_SetPGeom_Circleradius(PGeom_Circleradius);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_Circle::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_Circle::SRead(p,f,theSchema);
}
