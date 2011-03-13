#ifndef _ShapeSchema_PGeom2d_Transformation_HeaderFile
#include <ShapeSchema_PGeom2d_Transformation.hxx>
#endif
#ifndef _PGeom2d_Transformation_HeaderFile
#include <PGeom2d_Transformation.hxx>
#endif
#include <ShapeSchema_PGeom2d_Transformation.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_Transformation,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_Transformation,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_Transformation::New() const
{
  return new PGeom2d_Transformation(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom2d_Transformation::SAdd(const Handle(PGeom2d_Transformation)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_Transformation")) {
      
    }
  }
}

void ShapeSchema_PGeom2d_Transformation::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_Transformation::SAdd((Handle(PGeom2d_Transformation)&)p,theSchema);
}

void ShapeSchema_PGeom2d_Transformation::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Transformation) &pp = (Handle(PGeom2d_Transformation)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Trsf2d::SWrite(pp->_CSFDB_GetPGeom2d_Transformationtrsf(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Transformation::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_Transformation::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_Transformation::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Transformation) &pp = (Handle(PGeom2d_Transformation)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Trsf2d::SRead((gp_Trsf2d&)pp->_CSFDB_GetPGeom2d_Transformationtrsf(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Transformation::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_Transformation::SRead(p,f,theSchema);
}
