#ifndef _StdLSchema_PDataStd_FieldOfHArray1OfByte_HeaderFile
#include <StdLSchema_PDataStd_FieldOfHArray1OfByte.hxx>
#endif
#ifndef _PDataStd_FieldOfHArray1OfByte_HeaderFile
#include <PDataStd_FieldOfHArray1OfByte.hxx>
#endif
#include <StdLSchema_PDataStd_FieldOfHArray1OfByte.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void StdLSchema_PDataStd_FieldOfHArray1OfByte::SWrite(const PDataStd_FieldOfHArray1OfByte& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)theSchema; // dummy to avoid compiler warning on unused arg

  f.BeginWriteObjectData();
  f.PutInteger(pp.Length());
  for (Standard_Integer i = 0; i < pp.Length(); i++) {
    f.PutCharacter(pp.Value(i));

  }
  f.EndWriteObjectData();
}

void StdLSchema_PDataStd_FieldOfHArray1OfByte::SRead(PDataStd_FieldOfHArray1OfByte& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)theSchema; // dummy to avoid compiler warning on unused arg
  Standard_Integer size = 0;

  f.BeginReadObjectData();
  f.GetInteger(size);
  pp.Resize(size);

  for (Standard_Integer j = 0; j < size; j++) {
    Standard_Character par;

    f.GetCharacter(par);
    pp.SetValue(j,par);

  }
  f.EndReadObjectData();
}
