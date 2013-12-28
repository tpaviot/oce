#ifndef _ShapeSchema_PGeom_Axis2Placement_HeaderFile
#include <ShapeSchema_PGeom_Axis2Placement.hxx>
#endif
#ifndef _PGeom_Axis2Placement_HeaderFile
#include <PGeom_Axis2Placement.hxx>
#endif
#include <ShapeSchema_PGeom_Axis2Placement.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_Axis2Placement,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_Axis2Placement,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_Axis2Placement::New() const
{
  return new PGeom_Axis2Placement(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_Axis2Placement::SAdd(const Handle(PGeom_Axis2Placement)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_Axis2Placement")) {
      
    }
  }
}

void ShapeSchema_PGeom_Axis2Placement::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_Axis2Placement::SAdd((Handle(PGeom_Axis2Placement)&)p,theSchema);
}

void ShapeSchema_PGeom_Axis2Placement::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Axis2Placement) &pp = (Handle(PGeom_Axis2Placement)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax1::SWrite(pp->_CSFDB_GetPGeom_AxisPlacementaxis(),f,theSchema);
    ShapeSchema_gp_Dir::SWrite(pp->_CSFDB_GetPGeom_Axis2PlacementxDirection(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_Axis2Placement::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_Axis2Placement::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_Axis2Placement::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Axis2Placement) &pp = (Handle(PGeom_Axis2Placement)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax1::SRead((gp_Ax1&)pp->_CSFDB_GetPGeom_AxisPlacementaxis(),f,theSchema);

    ShapeSchema_gp_Dir::SRead((gp_Dir&)pp->_CSFDB_GetPGeom_Axis2PlacementxDirection(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_Axis2Placement::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_Axis2Placement::SRead(p,f,theSchema);
}
