#ifndef _ShapeSchema_PGeom_AxisPlacement_HeaderFile
#include <ShapeSchema_PGeom_AxisPlacement.hxx>
#endif
#ifndef _PGeom_AxisPlacement_HeaderFile
#include <PGeom_AxisPlacement.hxx>
#endif
#include <ShapeSchema_PGeom_AxisPlacement.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_AxisPlacement,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_AxisPlacement,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_AxisPlacement::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PGeom_AxisPlacement::SAdd(const Handle(PGeom_AxisPlacement)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_AxisPlacement")) {
      
    }
  }
}

void ShapeSchema_PGeom_AxisPlacement::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_AxisPlacement::SAdd((Handle(PGeom_AxisPlacement)&)p,theSchema);
}

void ShapeSchema_PGeom_AxisPlacement::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_AxisPlacement) &pp = (Handle(PGeom_AxisPlacement)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax1::SWrite(pp->_CSFDB_GetPGeom_AxisPlacementaxis(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_AxisPlacement::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_AxisPlacement::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_AxisPlacement::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_AxisPlacement) &pp = (Handle(PGeom_AxisPlacement)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax1::SRead((gp_Ax1&)pp->_CSFDB_GetPGeom_AxisPlacementaxis(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_AxisPlacement::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_AxisPlacement::SRead(p,f,theSchema);
}
