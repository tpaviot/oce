#ifndef _ShapeSchema_PGeom2d_Hyperbola_HeaderFile
#include <ShapeSchema_PGeom2d_Hyperbola.hxx>
#endif
#ifndef _PGeom2d_Hyperbola_HeaderFile
#include <PGeom2d_Hyperbola.hxx>
#endif
#include <ShapeSchema_PGeom2d_Hyperbola.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_Hyperbola,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_Hyperbola,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_Hyperbola::New() const
{
  return new PGeom2d_Hyperbola(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom2d_Hyperbola::SAdd(const Handle(PGeom2d_Hyperbola)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_Hyperbola")) {
      
    }
  }
}

void ShapeSchema_PGeom2d_Hyperbola::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_Hyperbola::SAdd((Handle(PGeom2d_Hyperbola)&)p,theSchema);
}

void ShapeSchema_PGeom2d_Hyperbola::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Hyperbola) &pp = (Handle(PGeom2d_Hyperbola)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax22d::SWrite(pp->_CSFDB_GetPGeom2d_Conicposition(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPGeom2d_HyperbolamajorRadius());
  f.PutReal(pp->_CSFDB_GetPGeom2d_HyperbolaminorRadius());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Hyperbola::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_Hyperbola::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_Hyperbola::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Hyperbola) &pp = (Handle(PGeom2d_Hyperbola)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax22d::SRead((gp_Ax22d&)pp->_CSFDB_GetPGeom2d_Conicposition(),f,theSchema);

    Standard_Real PGeom2d_HyperbolamajorRadius;
    f.GetReal(PGeom2d_HyperbolamajorRadius);
    pp->_CSFDB_SetPGeom2d_HyperbolamajorRadius(PGeom2d_HyperbolamajorRadius);

    Standard_Real PGeom2d_HyperbolaminorRadius;
    f.GetReal(PGeom2d_HyperbolaminorRadius);
    pp->_CSFDB_SetPGeom2d_HyperbolaminorRadius(PGeom2d_HyperbolaminorRadius);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Hyperbola::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_Hyperbola::SRead(p,f,theSchema);
}
