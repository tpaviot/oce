#ifndef _ShapeSchema_PGeom_Transformation_HeaderFile
#include <ShapeSchema_PGeom_Transformation.hxx>
#endif
#ifndef _PGeom_Transformation_HeaderFile
#include <PGeom_Transformation.hxx>
#endif
#include <ShapeSchema_PGeom_Transformation.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_Transformation,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_Transformation,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_Transformation::New() const
{
  return new PGeom_Transformation(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_Transformation::SAdd(const Handle(PGeom_Transformation)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_Transformation")) {
      
    }
  }
}

void ShapeSchema_PGeom_Transformation::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_Transformation::SAdd((Handle(PGeom_Transformation)&)p,theSchema);
}

void ShapeSchema_PGeom_Transformation::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Transformation) &pp = (Handle(PGeom_Transformation)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Trsf::SWrite(pp->_CSFDB_GetPGeom_Transformationtrsf(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_Transformation::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_Transformation::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_Transformation::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Transformation) &pp = (Handle(PGeom_Transformation)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Trsf::SRead((gp_Trsf&)pp->_CSFDB_GetPGeom_Transformationtrsf(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_Transformation::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_Transformation::SRead(p,f,theSchema);
}
