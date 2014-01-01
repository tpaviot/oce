#ifndef _ShapeSchema_PGeom_Axis1Placement_HeaderFile
#include <ShapeSchema_PGeom_Axis1Placement.hxx>
#endif
#ifndef _PGeom_Axis1Placement_HeaderFile
#include <PGeom_Axis1Placement.hxx>
#endif
#include <ShapeSchema_PGeom_Axis1Placement.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_Axis1Placement,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_Axis1Placement,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_Axis1Placement::New() const
{
  return new PGeom_Axis1Placement(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_Axis1Placement::SAdd(const Handle(PGeom_Axis1Placement)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_Axis1Placement")) {
      
    }
  }
}

void ShapeSchema_PGeom_Axis1Placement::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_Axis1Placement::SAdd((Handle(PGeom_Axis1Placement)&)p,theSchema);
}

void ShapeSchema_PGeom_Axis1Placement::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Axis1Placement) &pp = (Handle(PGeom_Axis1Placement)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax1::SWrite(pp->_CSFDB_GetPGeom_AxisPlacementaxis(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_Axis1Placement::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_Axis1Placement::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_Axis1Placement::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Axis1Placement) &pp = (Handle(PGeom_Axis1Placement)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax1::SRead((gp_Ax1&)pp->_CSFDB_GetPGeom_AxisPlacementaxis(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_Axis1Placement::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_Axis1Placement::SRead(p,f,theSchema);
}
