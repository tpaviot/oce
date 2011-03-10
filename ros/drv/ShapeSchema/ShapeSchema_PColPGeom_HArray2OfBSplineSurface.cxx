#ifndef _ShapeSchema_PColPGeom_HArray2OfBSplineSurface_HeaderFile
#include <ShapeSchema_PColPGeom_HArray2OfBSplineSurface.hxx>
#endif
#ifndef _PColPGeom_HArray2OfBSplineSurface_HeaderFile
#include <PColPGeom_HArray2OfBSplineSurface.hxx>
#endif
#include <ShapeSchema_PColPGeom_HArray2OfBSplineSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColPGeom_HArray2OfBSplineSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColPGeom_HArray2OfBSplineSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColPGeom_HArray2OfBSplineSurface::New() const
{
  return new PColPGeom_HArray2OfBSplineSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PColPGeom_HArray2OfBSplineSurface::SAdd(const Handle(PColPGeom_HArray2OfBSplineSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColPGeom_HArray2OfBSplineSurface")) {
         ShapeSchema_PColPGeom_FieldOfHArray2OfBSplineSurface::SAdd(p->_CSFDB_GetPColPGeom_HArray2OfBSplineSurfaceData(),theSchema);

    }
  }
}

void ShapeSchema_PColPGeom_HArray2OfBSplineSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColPGeom_HArray2OfBSplineSurface::SAdd((Handle(PColPGeom_HArray2OfBSplineSurface)&)p,theSchema);
}

void ShapeSchema_PColPGeom_HArray2OfBSplineSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom_HArray2OfBSplineSurface) &pp = (Handle(PColPGeom_HArray2OfBSplineSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray2OfBSplineSurfacemyLowerRow());
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray2OfBSplineSurfacemyLowerCol());
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray2OfBSplineSurfacemyUpperRow());
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray2OfBSplineSurfacemyUpperCol());
    ShapeSchema_PColPGeom_FieldOfHArray2OfBSplineSurface::SWrite(pp->_CSFDB_GetPColPGeom_HArray2OfBSplineSurfaceData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColPGeom_HArray2OfBSplineSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColPGeom_HArray2OfBSplineSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PColPGeom_HArray2OfBSplineSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom_HArray2OfBSplineSurface) &pp = (Handle(PColPGeom_HArray2OfBSplineSurface)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColPGeom_HArray2OfBSplineSurfacemyLowerRow;
    f.GetInteger(PColPGeom_HArray2OfBSplineSurfacemyLowerRow);
    pp->_CSFDB_SetPColPGeom_HArray2OfBSplineSurfacemyLowerRow(PColPGeom_HArray2OfBSplineSurfacemyLowerRow);

    Standard_Integer PColPGeom_HArray2OfBSplineSurfacemyLowerCol;
    f.GetInteger(PColPGeom_HArray2OfBSplineSurfacemyLowerCol);
    pp->_CSFDB_SetPColPGeom_HArray2OfBSplineSurfacemyLowerCol(PColPGeom_HArray2OfBSplineSurfacemyLowerCol);

    Standard_Integer PColPGeom_HArray2OfBSplineSurfacemyUpperRow;
    f.GetInteger(PColPGeom_HArray2OfBSplineSurfacemyUpperRow);
    pp->_CSFDB_SetPColPGeom_HArray2OfBSplineSurfacemyUpperRow(PColPGeom_HArray2OfBSplineSurfacemyUpperRow);

    Standard_Integer PColPGeom_HArray2OfBSplineSurfacemyUpperCol;
    f.GetInteger(PColPGeom_HArray2OfBSplineSurfacemyUpperCol);
    pp->_CSFDB_SetPColPGeom_HArray2OfBSplineSurfacemyUpperCol(PColPGeom_HArray2OfBSplineSurfacemyUpperCol);

    ShapeSchema_PColPGeom_FieldOfHArray2OfBSplineSurface::SRead((PColPGeom_FieldOfHArray2OfBSplineSurface&)pp->_CSFDB_GetPColPGeom_HArray2OfBSplineSurfaceData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColPGeom_HArray2OfBSplineSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColPGeom_HArray2OfBSplineSurface::SRead(p,f,theSchema);
}
