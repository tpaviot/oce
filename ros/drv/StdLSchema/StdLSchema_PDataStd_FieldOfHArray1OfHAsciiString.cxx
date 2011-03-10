#ifndef _StdLSchema_PDataStd_FieldOfHArray1OfHAsciiString_HeaderFile
#include <StdLSchema_PDataStd_FieldOfHArray1OfHAsciiString.hxx>
#endif
#ifndef _PDataStd_FieldOfHArray1OfHAsciiString_HeaderFile
#include <PDataStd_FieldOfHArray1OfHAsciiString.hxx>
#endif
#include <StdLSchema_PDataStd_FieldOfHArray1OfHAsciiString.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void StdLSchema_PDataStd_FieldOfHArray1OfHAsciiString::SAdd(const PDataStd_FieldOfHArray1OfHAsciiString& p, const Handle(Storage_Schema)& theSchema)
{
    Standard_Integer i;
  for (i = 0; i < p.Length(); i++) {
    theSchema->PersistentToAdd(p.Value(i));    
  }

}

void StdLSchema_PDataStd_FieldOfHArray1OfHAsciiString::SWrite(const PDataStd_FieldOfHArray1OfHAsciiString& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  Standard_Integer i;

  f.BeginWriteObjectData();
  f.PutInteger(pp.Length());
  for (i = 0; i < pp.Length(); i++) {
    theSchema->WritePersistentReference(pp.Value(i),f);

  }
  f.EndWriteObjectData();
}

void StdLSchema_PDataStd_FieldOfHArray1OfHAsciiString::SRead(PDataStd_FieldOfHArray1OfHAsciiString& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  Standard_Integer size = 0;

  f.BeginReadObjectData();
  f.GetInteger(size);
  pp.Resize(size);

  for (Standard_Integer j = 0; j < size; j++) {
    Handle(PCollection_HAsciiString) par;

    theSchema->ReadPersistentReference(par,f);
    pp.SetValue(j,par);

  }
  f.EndReadObjectData();
}
