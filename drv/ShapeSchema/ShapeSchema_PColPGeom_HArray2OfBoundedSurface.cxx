#ifndef _ShapeSchema_PColPGeom_HArray2OfBoundedSurface_HeaderFile
#include <ShapeSchema_PColPGeom_HArray2OfBoundedSurface.hxx>
#endif
#ifndef _PColPGeom_HArray2OfBoundedSurface_HeaderFile
#include <PColPGeom_HArray2OfBoundedSurface.hxx>
#endif
#include <ShapeSchema_PColPGeom_HArray2OfBoundedSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColPGeom_HArray2OfBoundedSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColPGeom_HArray2OfBoundedSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColPGeom_HArray2OfBoundedSurface::New() const
{
  return new PColPGeom_HArray2OfBoundedSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PColPGeom_HArray2OfBoundedSurface::SAdd(const Handle(PColPGeom_HArray2OfBoundedSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColPGeom_HArray2OfBoundedSurface")) {
         ShapeSchema_PColPGeom_FieldOfHArray2OfBoundedSurface::SAdd(p->_CSFDB_GetPColPGeom_HArray2OfBoundedSurfaceData(),theSchema);

    }
  }
}

void ShapeSchema_PColPGeom_HArray2OfBoundedSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColPGeom_HArray2OfBoundedSurface::SAdd((Handle(PColPGeom_HArray2OfBoundedSurface)&)p,theSchema);
}

void ShapeSchema_PColPGeom_HArray2OfBoundedSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom_HArray2OfBoundedSurface) &pp = (Handle(PColPGeom_HArray2OfBoundedSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray2OfBoundedSurfacemyLowerRow());
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray2OfBoundedSurfacemyLowerCol());
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray2OfBoundedSurfacemyUpperRow());
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray2OfBoundedSurfacemyUpperCol());
    ShapeSchema_PColPGeom_FieldOfHArray2OfBoundedSurface::SWrite(pp->_CSFDB_GetPColPGeom_HArray2OfBoundedSurfaceData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColPGeom_HArray2OfBoundedSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColPGeom_HArray2OfBoundedSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PColPGeom_HArray2OfBoundedSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom_HArray2OfBoundedSurface) &pp = (Handle(PColPGeom_HArray2OfBoundedSurface)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColPGeom_HArray2OfBoundedSurfacemyLowerRow;
    f.GetInteger(PColPGeom_HArray2OfBoundedSurfacemyLowerRow);
    pp->_CSFDB_SetPColPGeom_HArray2OfBoundedSurfacemyLowerRow(PColPGeom_HArray2OfBoundedSurfacemyLowerRow);

    Standard_Integer PColPGeom_HArray2OfBoundedSurfacemyLowerCol;
    f.GetInteger(PColPGeom_HArray2OfBoundedSurfacemyLowerCol);
    pp->_CSFDB_SetPColPGeom_HArray2OfBoundedSurfacemyLowerCol(PColPGeom_HArray2OfBoundedSurfacemyLowerCol);

    Standard_Integer PColPGeom_HArray2OfBoundedSurfacemyUpperRow;
    f.GetInteger(PColPGeom_HArray2OfBoundedSurfacemyUpperRow);
    pp->_CSFDB_SetPColPGeom_HArray2OfBoundedSurfacemyUpperRow(PColPGeom_HArray2OfBoundedSurfacemyUpperRow);

    Standard_Integer PColPGeom_HArray2OfBoundedSurfacemyUpperCol;
    f.GetInteger(PColPGeom_HArray2OfBoundedSurfacemyUpperCol);
    pp->_CSFDB_SetPColPGeom_HArray2OfBoundedSurfacemyUpperCol(PColPGeom_HArray2OfBoundedSurfacemyUpperCol);

    ShapeSchema_PColPGeom_FieldOfHArray2OfBoundedSurface::SRead((PColPGeom_FieldOfHArray2OfBoundedSurface&)pp->_CSFDB_GetPColPGeom_HArray2OfBoundedSurfaceData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColPGeom_HArray2OfBoundedSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColPGeom_HArray2OfBoundedSurface::SRead(p,f,theSchema);
}
