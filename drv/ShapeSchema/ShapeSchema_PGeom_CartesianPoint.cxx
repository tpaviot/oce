#ifndef _ShapeSchema_PGeom_CartesianPoint_HeaderFile
#include <ShapeSchema_PGeom_CartesianPoint.hxx>
#endif
#ifndef _PGeom_CartesianPoint_HeaderFile
#include <PGeom_CartesianPoint.hxx>
#endif
#include <ShapeSchema_PGeom_CartesianPoint.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_CartesianPoint,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_CartesianPoint,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_CartesianPoint::New() const
{
  return new PGeom_CartesianPoint(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_CartesianPoint::SAdd(const Handle(PGeom_CartesianPoint)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_CartesianPoint")) {
      
    }
  }
}

void ShapeSchema_PGeom_CartesianPoint::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_CartesianPoint::SAdd((Handle(PGeom_CartesianPoint)&)p,theSchema);
}

void ShapeSchema_PGeom_CartesianPoint::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_CartesianPoint) &pp = (Handle(PGeom_CartesianPoint)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Pnt::SWrite(pp->_CSFDB_GetPGeom_CartesianPointpnt(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_CartesianPoint::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_CartesianPoint::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_CartesianPoint::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_CartesianPoint) &pp = (Handle(PGeom_CartesianPoint)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Pnt::SRead((gp_Pnt&)pp->_CSFDB_GetPGeom_CartesianPointpnt(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_CartesianPoint::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_CartesianPoint::SRead(p,f,theSchema);
}
