#ifndef _ShapeSchema_PGeom2d_CartesianPoint_HeaderFile
#include <ShapeSchema_PGeom2d_CartesianPoint.hxx>
#endif
#ifndef _PGeom2d_CartesianPoint_HeaderFile
#include <PGeom2d_CartesianPoint.hxx>
#endif
#include <ShapeSchema_PGeom2d_CartesianPoint.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_CartesianPoint,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_CartesianPoint,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_CartesianPoint::New() const
{
  return new PGeom2d_CartesianPoint(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom2d_CartesianPoint::SAdd(const Handle(PGeom2d_CartesianPoint)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_CartesianPoint")) {
      
    }
  }
}

void ShapeSchema_PGeom2d_CartesianPoint::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_CartesianPoint::SAdd((Handle(PGeom2d_CartesianPoint)&)p,theSchema);
}

void ShapeSchema_PGeom2d_CartesianPoint::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_CartesianPoint) &pp = (Handle(PGeom2d_CartesianPoint)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Pnt2d::SWrite(pp->_CSFDB_GetPGeom2d_CartesianPointpnt(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_CartesianPoint::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_CartesianPoint::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_CartesianPoint::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_CartesianPoint) &pp = (Handle(PGeom2d_CartesianPoint)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Pnt2d::SRead((gp_Pnt2d&)pp->_CSFDB_GetPGeom2d_CartesianPointpnt(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_CartesianPoint::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_CartesianPoint::SRead(p,f,theSchema);
}
