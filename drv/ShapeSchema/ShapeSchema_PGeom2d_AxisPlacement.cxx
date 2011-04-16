#ifndef _ShapeSchema_PGeom2d_AxisPlacement_HeaderFile
#include <ShapeSchema_PGeom2d_AxisPlacement.hxx>
#endif
#ifndef _PGeom2d_AxisPlacement_HeaderFile
#include <PGeom2d_AxisPlacement.hxx>
#endif
#include <ShapeSchema_PGeom2d_AxisPlacement.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_AxisPlacement,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_AxisPlacement,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_AxisPlacement::New() const
{
  return new PGeom2d_AxisPlacement(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom2d_AxisPlacement::SAdd(const Handle(PGeom2d_AxisPlacement)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_AxisPlacement")) {
      
    }
  }
}

void ShapeSchema_PGeom2d_AxisPlacement::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_AxisPlacement::SAdd((Handle(PGeom2d_AxisPlacement)&)p,theSchema);
}

void ShapeSchema_PGeom2d_AxisPlacement::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_AxisPlacement) &pp = (Handle(PGeom2d_AxisPlacement)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax2d::SWrite(pp->_CSFDB_GetPGeom2d_AxisPlacementaxis(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_AxisPlacement::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_AxisPlacement::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_AxisPlacement::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_AxisPlacement) &pp = (Handle(PGeom2d_AxisPlacement)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax2d::SRead((gp_Ax2d&)pp->_CSFDB_GetPGeom2d_AxisPlacementaxis(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_AxisPlacement::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_AxisPlacement::SRead(p,f,theSchema);
}
