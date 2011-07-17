#ifndef _ShapeSchema_PGeom_Ellipse_HeaderFile
#include <ShapeSchema_PGeom_Ellipse.hxx>
#endif
#ifndef _PGeom_Ellipse_HeaderFile
#include <PGeom_Ellipse.hxx>
#endif
#include <ShapeSchema_PGeom_Ellipse.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_Ellipse,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_Ellipse,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_Ellipse::New() const
{
  return new PGeom_Ellipse(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_Ellipse::SAdd(const Handle(PGeom_Ellipse)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_Ellipse")) {
      
    }
  }
}

void ShapeSchema_PGeom_Ellipse::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_Ellipse::SAdd((Handle(PGeom_Ellipse)&)p,theSchema);
}

void ShapeSchema_PGeom_Ellipse::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Ellipse) &pp = (Handle(PGeom_Ellipse)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax2::SWrite(pp->_CSFDB_GetPGeom_Conicposition(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPGeom_EllipsemajorRadius());
  f.PutReal(pp->_CSFDB_GetPGeom_EllipseminorRadius());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_Ellipse::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_Ellipse::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_Ellipse::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Ellipse) &pp = (Handle(PGeom_Ellipse)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax2::SRead((gp_Ax2&)pp->_CSFDB_GetPGeom_Conicposition(),f,theSchema);

    Standard_Real PGeom_EllipsemajorRadius;
    f.GetReal(PGeom_EllipsemajorRadius);
    pp->_CSFDB_SetPGeom_EllipsemajorRadius(PGeom_EllipsemajorRadius);

    Standard_Real PGeom_EllipseminorRadius;
    f.GetReal(PGeom_EllipseminorRadius);
    pp->_CSFDB_SetPGeom_EllipseminorRadius(PGeom_EllipseminorRadius);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_Ellipse::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_Ellipse::SRead(p,f,theSchema);
}
