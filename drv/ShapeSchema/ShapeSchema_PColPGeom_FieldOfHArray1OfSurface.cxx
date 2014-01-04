#ifndef _ShapeSchema_PColPGeom_FieldOfHArray1OfSurface_HeaderFile
#include <ShapeSchema_PColPGeom_FieldOfHArray1OfSurface.hxx>
#endif
#ifndef _PColPGeom_FieldOfHArray1OfSurface_HeaderFile
#include <PColPGeom_FieldOfHArray1OfSurface.hxx>
#endif
#include <ShapeSchema_PColPGeom_FieldOfHArray1OfSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void ShapeSchema_PColPGeom_FieldOfHArray1OfSurface::SAdd(const PColPGeom_FieldOfHArray1OfSurface& p, const Handle(Storage_Schema)& theSchema)
{
    Standard_Integer i;
  for (i = 0; i < p.Length(); i++) {
    theSchema->PersistentToAdd(p.Value(i));    
  }

}

void ShapeSchema_PColPGeom_FieldOfHArray1OfSurface::SWrite(const PColPGeom_FieldOfHArray1OfSurface& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)theSchema; // dummy to avoid compiler warning on unused arg

  f.BeginWriteObjectData();
  f.PutInteger(pp.Length());
  for (Standard_Integer i = 0; i < pp.Length(); i++) {
    theSchema->WritePersistentReference(pp.Value(i),f);

  }
  f.EndWriteObjectData();
}

void ShapeSchema_PColPGeom_FieldOfHArray1OfSurface::SRead(PColPGeom_FieldOfHArray1OfSurface& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)theSchema; // dummy to avoid compiler warning on unused arg
  Standard_Integer size = 0;

  f.BeginReadObjectData();
  f.GetInteger(size);
  pp.Resize(size);

  for (Standard_Integer j = 0; j < size; j++) {
    Handle(PGeom_Surface) par;

    theSchema->ReadPersistentReference(par,f);
    pp.SetValue(j,par);

  }
  f.EndReadObjectData();
}
