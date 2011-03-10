#ifndef _StdLSchema_PColStd_FieldOfHArray1OfExtendedString_HeaderFile
#include <StdLSchema_PColStd_FieldOfHArray1OfExtendedString.hxx>
#endif
#ifndef _PColStd_FieldOfHArray1OfExtendedString_HeaderFile
#include <PColStd_FieldOfHArray1OfExtendedString.hxx>
#endif
#include <StdLSchema_PColStd_FieldOfHArray1OfExtendedString.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void StdLSchema_PColStd_FieldOfHArray1OfExtendedString::SAdd(const PColStd_FieldOfHArray1OfExtendedString& p, const Handle(Storage_Schema)& theSchema)
{
    Standard_Integer i;
  for (i = 0; i < p.Length(); i++) {
    theSchema->PersistentToAdd(p.Value(i));    
  }

}

void StdLSchema_PColStd_FieldOfHArray1OfExtendedString::SWrite(const PColStd_FieldOfHArray1OfExtendedString& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  Standard_Integer i;

  f.BeginWriteObjectData();
  f.PutInteger(pp.Length());
  for (i = 0; i < pp.Length(); i++) {
    theSchema->WritePersistentReference(pp.Value(i),f);

  }
  f.EndWriteObjectData();
}

void StdLSchema_PColStd_FieldOfHArray1OfExtendedString::SRead(PColStd_FieldOfHArray1OfExtendedString& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  Standard_Integer size = 0;

  f.BeginReadObjectData();
  f.GetInteger(size);
  pp.Resize(size);

  for (Standard_Integer j = 0; j < size; j++) {
    Handle(PCollection_HExtendedString) par;

    theSchema->ReadPersistentReference(par,f);
    pp.SetValue(j,par);

  }
  f.EndReadObjectData();
}
