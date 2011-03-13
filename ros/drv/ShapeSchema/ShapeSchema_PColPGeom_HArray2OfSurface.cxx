#ifndef _ShapeSchema_PColPGeom_HArray2OfSurface_HeaderFile
#include <ShapeSchema_PColPGeom_HArray2OfSurface.hxx>
#endif
#ifndef _PColPGeom_HArray2OfSurface_HeaderFile
#include <PColPGeom_HArray2OfSurface.hxx>
#endif
#include <ShapeSchema_PColPGeom_HArray2OfSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColPGeom_HArray2OfSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColPGeom_HArray2OfSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColPGeom_HArray2OfSurface::New() const
{
  return new PColPGeom_HArray2OfSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PColPGeom_HArray2OfSurface::SAdd(const Handle(PColPGeom_HArray2OfSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColPGeom_HArray2OfSurface")) {
         ShapeSchema_PColPGeom_FieldOfHArray2OfSurface::SAdd(p->_CSFDB_GetPColPGeom_HArray2OfSurfaceData(),theSchema);

    }
  }
}

void ShapeSchema_PColPGeom_HArray2OfSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColPGeom_HArray2OfSurface::SAdd((Handle(PColPGeom_HArray2OfSurface)&)p,theSchema);
}

void ShapeSchema_PColPGeom_HArray2OfSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom_HArray2OfSurface) &pp = (Handle(PColPGeom_HArray2OfSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray2OfSurfacemyLowerRow());
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray2OfSurfacemyLowerCol());
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray2OfSurfacemyUpperRow());
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray2OfSurfacemyUpperCol());
    ShapeSchema_PColPGeom_FieldOfHArray2OfSurface::SWrite(pp->_CSFDB_GetPColPGeom_HArray2OfSurfaceData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColPGeom_HArray2OfSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColPGeom_HArray2OfSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PColPGeom_HArray2OfSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom_HArray2OfSurface) &pp = (Handle(PColPGeom_HArray2OfSurface)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColPGeom_HArray2OfSurfacemyLowerRow;
    f.GetInteger(PColPGeom_HArray2OfSurfacemyLowerRow);
    pp->_CSFDB_SetPColPGeom_HArray2OfSurfacemyLowerRow(PColPGeom_HArray2OfSurfacemyLowerRow);

    Standard_Integer PColPGeom_HArray2OfSurfacemyLowerCol;
    f.GetInteger(PColPGeom_HArray2OfSurfacemyLowerCol);
    pp->_CSFDB_SetPColPGeom_HArray2OfSurfacemyLowerCol(PColPGeom_HArray2OfSurfacemyLowerCol);

    Standard_Integer PColPGeom_HArray2OfSurfacemyUpperRow;
    f.GetInteger(PColPGeom_HArray2OfSurfacemyUpperRow);
    pp->_CSFDB_SetPColPGeom_HArray2OfSurfacemyUpperRow(PColPGeom_HArray2OfSurfacemyUpperRow);

    Standard_Integer PColPGeom_HArray2OfSurfacemyUpperCol;
    f.GetInteger(PColPGeom_HArray2OfSurfacemyUpperCol);
    pp->_CSFDB_SetPColPGeom_HArray2OfSurfacemyUpperCol(PColPGeom_HArray2OfSurfacemyUpperCol);

    ShapeSchema_PColPGeom_FieldOfHArray2OfSurface::SRead((PColPGeom_FieldOfHArray2OfSurface&)pp->_CSFDB_GetPColPGeom_HArray2OfSurfaceData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColPGeom_HArray2OfSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColPGeom_HArray2OfSurface::SRead(p,f,theSchema);
}
