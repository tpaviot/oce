#ifndef _ShapeSchema_PGeom_Hyperbola_HeaderFile
#include <ShapeSchema_PGeom_Hyperbola.hxx>
#endif
#ifndef _PGeom_Hyperbola_HeaderFile
#include <PGeom_Hyperbola.hxx>
#endif
#include <ShapeSchema_PGeom_Hyperbola.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_Hyperbola,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_Hyperbola,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_Hyperbola::New() const
{
  return new PGeom_Hyperbola(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_Hyperbola::SAdd(const Handle(PGeom_Hyperbola)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_Hyperbola")) {
      
    }
  }
}

void ShapeSchema_PGeom_Hyperbola::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_Hyperbola::SAdd((Handle(PGeom_Hyperbola)&)p,theSchema);
}

void ShapeSchema_PGeom_Hyperbola::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Hyperbola) &pp = (Handle(PGeom_Hyperbola)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax2::SWrite(pp->_CSFDB_GetPGeom_Conicposition(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPGeom_HyperbolamajorRadius());
  f.PutReal(pp->_CSFDB_GetPGeom_HyperbolaminorRadius());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_Hyperbola::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_Hyperbola::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_Hyperbola::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Hyperbola) &pp = (Handle(PGeom_Hyperbola)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax2::SRead((gp_Ax2&)pp->_CSFDB_GetPGeom_Conicposition(),f,theSchema);

    Standard_Real PGeom_HyperbolamajorRadius;
    f.GetReal(PGeom_HyperbolamajorRadius);
    pp->_CSFDB_SetPGeom_HyperbolamajorRadius(PGeom_HyperbolamajorRadius);

    Standard_Real PGeom_HyperbolaminorRadius;
    f.GetReal(PGeom_HyperbolaminorRadius);
    pp->_CSFDB_SetPGeom_HyperbolaminorRadius(PGeom_HyperbolaminorRadius);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_Hyperbola::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_Hyperbola::SRead(p,f,theSchema);
}
