#ifndef _ShapeSchema_PGeom2d_Parabola_HeaderFile
#include <ShapeSchema_PGeom2d_Parabola.hxx>
#endif
#ifndef _PGeom2d_Parabola_HeaderFile
#include <PGeom2d_Parabola.hxx>
#endif
#include <ShapeSchema_PGeom2d_Parabola.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_Parabola,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_Parabola,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_Parabola::New() const
{
  return new PGeom2d_Parabola(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom2d_Parabola::SAdd(const Handle(PGeom2d_Parabola)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_Parabola")) {
      
    }
  }
}

void ShapeSchema_PGeom2d_Parabola::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_Parabola::SAdd((Handle(PGeom2d_Parabola)&)p,theSchema);
}

void ShapeSchema_PGeom2d_Parabola::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Parabola) &pp = (Handle(PGeom2d_Parabola)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_gp_Ax22d::SWrite(pp->_CSFDB_GetPGeom2d_Conicposition(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPGeom2d_ParabolafocalLength());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Parabola::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_Parabola::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_Parabola::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_Parabola) &pp = (Handle(PGeom2d_Parabola)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_gp_Ax22d::SRead((gp_Ax22d&)pp->_CSFDB_GetPGeom2d_Conicposition(),f,theSchema);

    Standard_Real PGeom2d_ParabolafocalLength;
    f.GetReal(PGeom2d_ParabolafocalLength);
    pp->_CSFDB_SetPGeom2d_ParabolafocalLength(PGeom2d_ParabolafocalLength);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_Parabola::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_Parabola::SRead(p,f,theSchema);
}
