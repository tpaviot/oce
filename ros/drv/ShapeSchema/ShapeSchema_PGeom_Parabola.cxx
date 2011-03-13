#ifndef _ShapeSchema_PGeom_Parabola_HeaderFile
#include <ShapeSchema_PGeom_Parabola.hxx>
#endif
#ifndef _PGeom_Parabola_HeaderFile
#include <PGeom_Parabola.hxx>
#endif
#include <ShapeSchema_PGeom_Parabola.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_Parabola,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_Parabola,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_Parabola::New() const
{
  return new PGeom_Parabola(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_Parabola::SAdd(const Handle(PGeom_Parabola)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_Parabola")) {
      
    }
  }
}

void ShapeSchema_PGeom_Parabola::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_Parabola::SAdd((Handle(PGeom_Parabola)&)p,theSchema);
}

void ShapeSchema_PGeom_Parabola::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Parabola) &pp = (Handle(PGeom_Parabola)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax2::SWrite(pp->_CSFDB_GetPGeom_Conicposition(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPGeom_ParabolafocalLength());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_Parabola::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_Parabola::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_Parabola::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_Parabola) &pp = (Handle(PGeom_Parabola)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax2::SRead((gp_Ax2&)pp->_CSFDB_GetPGeom_Conicposition(),f,theSchema);

    Standard_Real PGeom_ParabolafocalLength;
    f.GetReal(PGeom_ParabolafocalLength);
    pp->_CSFDB_SetPGeom_ParabolafocalLength(PGeom_ParabolafocalLength);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_Parabola::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_Parabola::SRead(p,f,theSchema);
}
