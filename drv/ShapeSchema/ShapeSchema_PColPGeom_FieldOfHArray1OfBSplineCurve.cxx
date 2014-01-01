#ifndef _ShapeSchema_PColPGeom_FieldOfHArray1OfBSplineCurve_HeaderFile
#include <ShapeSchema_PColPGeom_FieldOfHArray1OfBSplineCurve.hxx>
#endif
#ifndef _PColPGeom_FieldOfHArray1OfBSplineCurve_HeaderFile
#include <PColPGeom_FieldOfHArray1OfBSplineCurve.hxx>
#endif
#include <ShapeSchema_PColPGeom_FieldOfHArray1OfBSplineCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void ShapeSchema_PColPGeom_FieldOfHArray1OfBSplineCurve::SAdd(const PColPGeom_FieldOfHArray1OfBSplineCurve& p, const Handle(Storage_Schema)& theSchema)
{
    Standard_Integer i;
  for (i = 0; i < p.Length(); i++) {
    theSchema->PersistentToAdd(p.Value(i));    
  }

}

void ShapeSchema_PColPGeom_FieldOfHArray1OfBSplineCurve::SWrite(const PColPGeom_FieldOfHArray1OfBSplineCurve& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)theSchema; // dummy to avoid compiler warning on unused arg

  f.BeginWriteObjectData();
  f.PutInteger(pp.Length());
  for (Standard_Integer i = 0; i < pp.Length(); i++) {
    theSchema->WritePersistentReference(pp.Value(i),f);

  }
  f.EndWriteObjectData();
}

void ShapeSchema_PColPGeom_FieldOfHArray1OfBSplineCurve::SRead(PColPGeom_FieldOfHArray1OfBSplineCurve& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)theSchema; // dummy to avoid compiler warning on unused arg
  Standard_Integer size = 0;

  f.BeginReadObjectData();
  f.GetInteger(size);
  pp.Resize(size);

  for (Standard_Integer j = 0; j < size; j++) {
    Handle(PGeom_BSplineCurve) par;

    theSchema->ReadPersistentReference(par,f);
    pp.SetValue(j,par);

  }
  f.EndReadObjectData();
}
