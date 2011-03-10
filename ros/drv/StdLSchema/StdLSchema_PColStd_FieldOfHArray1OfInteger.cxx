#ifndef _StdLSchema_PColStd_FieldOfHArray1OfInteger_HeaderFile
#include <StdLSchema_PColStd_FieldOfHArray1OfInteger.hxx>
#endif
#ifndef _PColStd_FieldOfHArray1OfInteger_HeaderFile
#include <PColStd_FieldOfHArray1OfInteger.hxx>
#endif
#include <StdLSchema_PColStd_FieldOfHArray1OfInteger.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void StdLSchema_PColStd_FieldOfHArray1OfInteger::SWrite(const PColStd_FieldOfHArray1OfInteger& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  Standard_Integer i;

  f.BeginWriteObjectData();
  f.PutInteger(pp.Length());
  for (i = 0; i < pp.Length(); i++) {
    f.PutInteger(pp.Value(i));

  }
  f.EndWriteObjectData();
}

void StdLSchema_PColStd_FieldOfHArray1OfInteger::SRead(PColStd_FieldOfHArray1OfInteger& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  Standard_Integer size = 0;

  f.BeginReadObjectData();
  f.GetInteger(size);
  pp.Resize(size);

  for (Standard_Integer j = 0; j < size; j++) {
    Standard_Integer par;

    f.GetInteger(par);
    pp.SetValue(j,par);

  }
  f.EndReadObjectData();
}
