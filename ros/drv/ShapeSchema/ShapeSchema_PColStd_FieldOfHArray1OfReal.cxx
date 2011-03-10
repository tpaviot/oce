#ifndef _ShapeSchema_PColStd_FieldOfHArray1OfReal_HeaderFile
#include <ShapeSchema_PColStd_FieldOfHArray1OfReal.hxx>
#endif
#ifndef _PColStd_FieldOfHArray1OfReal_HeaderFile
#include <PColStd_FieldOfHArray1OfReal.hxx>
#endif
#include <ShapeSchema_PColStd_FieldOfHArray1OfReal.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void ShapeSchema_PColStd_FieldOfHArray1OfReal::SWrite(const PColStd_FieldOfHArray1OfReal& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  Standard_Integer i;

  f.BeginWriteObjectData();
  f.PutInteger(pp.Length());
  for (i = 0; i < pp.Length(); i++) {
    f.PutReal(pp.Value(i));

  }
  f.EndWriteObjectData();
}

void ShapeSchema_PColStd_FieldOfHArray1OfReal::SRead(PColStd_FieldOfHArray1OfReal& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  Standard_Integer size = 0;

  f.BeginReadObjectData();
  f.GetInteger(size);
  pp.Resize(size);

  for (Standard_Integer j = 0; j < size; j++) {
    Standard_Real par;

    f.GetReal(par);
    pp.SetValue(j,par);

  }
  f.EndReadObjectData();
}
