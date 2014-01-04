#ifndef _ShapeSchema_PColPGeom_HArray2OfBezierSurface_HeaderFile
#include <ShapeSchema_PColPGeom_HArray2OfBezierSurface.hxx>
#endif
#ifndef _PColPGeom_HArray2OfBezierSurface_HeaderFile
#include <PColPGeom_HArray2OfBezierSurface.hxx>
#endif
#include <ShapeSchema_PColPGeom_HArray2OfBezierSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColPGeom_HArray2OfBezierSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColPGeom_HArray2OfBezierSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColPGeom_HArray2OfBezierSurface::New() const
{
  return new PColPGeom_HArray2OfBezierSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PColPGeom_HArray2OfBezierSurface::SAdd(const Handle(PColPGeom_HArray2OfBezierSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColPGeom_HArray2OfBezierSurface")) {
         ShapeSchema_PColPGeom_FieldOfHArray2OfBezierSurface::SAdd(p->_CSFDB_GetPColPGeom_HArray2OfBezierSurfaceData(),theSchema);

    }
  }
}

void ShapeSchema_PColPGeom_HArray2OfBezierSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColPGeom_HArray2OfBezierSurface::SAdd((Handle(PColPGeom_HArray2OfBezierSurface)&)p,theSchema);
}

void ShapeSchema_PColPGeom_HArray2OfBezierSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom_HArray2OfBezierSurface) &pp = (Handle(PColPGeom_HArray2OfBezierSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray2OfBezierSurfacemyLowerRow());
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray2OfBezierSurfacemyLowerCol());
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray2OfBezierSurfacemyUpperRow());
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray2OfBezierSurfacemyUpperCol());
    ShapeSchema_PColPGeom_FieldOfHArray2OfBezierSurface::SWrite(pp->_CSFDB_GetPColPGeom_HArray2OfBezierSurfaceData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColPGeom_HArray2OfBezierSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColPGeom_HArray2OfBezierSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PColPGeom_HArray2OfBezierSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom_HArray2OfBezierSurface) &pp = (Handle(PColPGeom_HArray2OfBezierSurface)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColPGeom_HArray2OfBezierSurfacemyLowerRow;
    f.GetInteger(PColPGeom_HArray2OfBezierSurfacemyLowerRow);
    pp->_CSFDB_SetPColPGeom_HArray2OfBezierSurfacemyLowerRow(PColPGeom_HArray2OfBezierSurfacemyLowerRow);

    Standard_Integer PColPGeom_HArray2OfBezierSurfacemyLowerCol;
    f.GetInteger(PColPGeom_HArray2OfBezierSurfacemyLowerCol);
    pp->_CSFDB_SetPColPGeom_HArray2OfBezierSurfacemyLowerCol(PColPGeom_HArray2OfBezierSurfacemyLowerCol);

    Standard_Integer PColPGeom_HArray2OfBezierSurfacemyUpperRow;
    f.GetInteger(PColPGeom_HArray2OfBezierSurfacemyUpperRow);
    pp->_CSFDB_SetPColPGeom_HArray2OfBezierSurfacemyUpperRow(PColPGeom_HArray2OfBezierSurfacemyUpperRow);

    Standard_Integer PColPGeom_HArray2OfBezierSurfacemyUpperCol;
    f.GetInteger(PColPGeom_HArray2OfBezierSurfacemyUpperCol);
    pp->_CSFDB_SetPColPGeom_HArray2OfBezierSurfacemyUpperCol(PColPGeom_HArray2OfBezierSurfacemyUpperCol);

    ShapeSchema_PColPGeom_FieldOfHArray2OfBezierSurface::SRead((PColPGeom_FieldOfHArray2OfBezierSurface&)pp->_CSFDB_GetPColPGeom_HArray2OfBezierSurfaceData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColPGeom_HArray2OfBezierSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColPGeom_HArray2OfBezierSurface::SRead(p,f,theSchema);
}
