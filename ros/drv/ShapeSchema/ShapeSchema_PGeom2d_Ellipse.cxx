#ifndef _ShapeSchema_PGeom2d_Ellipse_HeaderFile
#include <ShapeSchema_PGeom2d_Ellipse.hxx>
#endif
#ifndef _PGeom2d_Ellipse_HeaderFile
#include <PGeom2d_Ellipse.hxx>
#endif
#include <ShapeSchema_PGeom2d_Ellipse.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_Ellipse,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_Ellipse,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_Ellipse::New() const
{
  return new PGeom2d_Ellipse(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom2d_Ellipse::SAdd(const Handle(PGeom2d_Ellipse)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_Ellipse")) {
      
    }
  }
}

void ShapeSchema_PGeom2d_Ellipse::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_Ellipse::SAdd((Handle(PGeom2d_Ellipse)&)p,theSchema);
}

void ShapeSchema_PGeom2d_Ellipse::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Ellipse) &pp = (Handle(PGeom2d_Ellipse)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax22d::SWrite(pp->_CSFDB_GetPGeom2d_Conicposition(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPGeom2d_EllipsemajorRadius());
  f.PutReal(pp->_CSFDB_GetPGeom2d_EllipseminorRadius());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Ellipse::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_Ellipse::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_Ellipse::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Ellipse) &pp = (Handle(PGeom2d_Ellipse)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax22d::SRead((gp_Ax22d&)pp->_CSFDB_GetPGeom2d_Conicposition(),f,theSchema);

    Standard_Real PGeom2d_EllipsemajorRadius;
    f.GetReal(PGeom2d_EllipsemajorRadius);
    pp->_CSFDB_SetPGeom2d_EllipsemajorRadius(PGeom2d_EllipsemajorRadius);

    Standard_Real PGeom2d_EllipseminorRadius;
    f.GetReal(PGeom2d_EllipseminorRadius);
    pp->_CSFDB_SetPGeom2d_EllipseminorRadius(PGeom2d_EllipseminorRadius);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Ellipse::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_Ellipse::SRead(p,f,theSchema);
}
