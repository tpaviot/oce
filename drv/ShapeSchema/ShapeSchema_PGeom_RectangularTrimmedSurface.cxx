#ifndef _ShapeSchema_PGeom_RectangularTrimmedSurface_HeaderFile
#include <ShapeSchema_PGeom_RectangularTrimmedSurface.hxx>
#endif
#ifndef _PGeom_RectangularTrimmedSurface_HeaderFile
#include <PGeom_RectangularTrimmedSurface.hxx>
#endif
#include <ShapeSchema_PGeom_RectangularTrimmedSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_RectangularTrimmedSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_RectangularTrimmedSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_RectangularTrimmedSurface::New() const
{
  return new PGeom_RectangularTrimmedSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_RectangularTrimmedSurface::SAdd(const Handle(PGeom_RectangularTrimmedSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_RectangularTrimmedSurface")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_RectangularTrimmedSurfacebasisSurface());

    }
  }
}

void ShapeSchema_PGeom_RectangularTrimmedSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_RectangularTrimmedSurface::SAdd((Handle(PGeom_RectangularTrimmedSurface)&)p,theSchema);
}

void ShapeSchema_PGeom_RectangularTrimmedSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_RectangularTrimmedSurface) &pp = (Handle(PGeom_RectangularTrimmedSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_RectangularTrimmedSurfacebasisSurface(),f);
  f.PutReal(pp->_CSFDB_GetPGeom_RectangularTrimmedSurfacefirstU());
  f.PutReal(pp->_CSFDB_GetPGeom_RectangularTrimmedSurfacelastU());
  f.PutReal(pp->_CSFDB_GetPGeom_RectangularTrimmedSurfacefirstV());
  f.PutReal(pp->_CSFDB_GetPGeom_RectangularTrimmedSurfacelastV());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_RectangularTrimmedSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_RectangularTrimmedSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_RectangularTrimmedSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_RectangularTrimmedSurface) &pp = (Handle(PGeom_RectangularTrimmedSurface)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PGeom_Surface) PGeom_RectangularTrimmedSurfacebasisSurface;

    theSchema->ReadPersistentReference(PGeom_RectangularTrimmedSurfacebasisSurface,f);
    pp->_CSFDB_SetPGeom_RectangularTrimmedSurfacebasisSurface(PGeom_RectangularTrimmedSurfacebasisSurface);

    Standard_Real PGeom_RectangularTrimmedSurfacefirstU;
    f.GetReal(PGeom_RectangularTrimmedSurfacefirstU);
    pp->_CSFDB_SetPGeom_RectangularTrimmedSurfacefirstU(PGeom_RectangularTrimmedSurfacefirstU);

    Standard_Real PGeom_RectangularTrimmedSurfacelastU;
    f.GetReal(PGeom_RectangularTrimmedSurfacelastU);
    pp->_CSFDB_SetPGeom_RectangularTrimmedSurfacelastU(PGeom_RectangularTrimmedSurfacelastU);

    Standard_Real PGeom_RectangularTrimmedSurfacefirstV;
    f.GetReal(PGeom_RectangularTrimmedSurfacefirstV);
    pp->_CSFDB_SetPGeom_RectangularTrimmedSurfacefirstV(PGeom_RectangularTrimmedSurfacefirstV);

    Standard_Real PGeom_RectangularTrimmedSurfacelastV;
    f.GetReal(PGeom_RectangularTrimmedSurfacelastV);
    pp->_CSFDB_SetPGeom_RectangularTrimmedSurfacelastV(PGeom_RectangularTrimmedSurfacelastV);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_RectangularTrimmedSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_RectangularTrimmedSurface::SRead(p,f,theSchema);
}
