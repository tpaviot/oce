#ifndef _StdSchema_DBC_VArrayOfCharacter_HeaderFile
#include <StdSchema_DBC_VArrayOfCharacter.hxx>
#endif
#ifndef _DBC_VArrayOfCharacter_HeaderFile
#include <DBC_VArrayOfCharacter.hxx>
#endif
#include <StdSchema_DBC_VArrayOfCharacter.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void StdSchema_DBC_VArrayOfCharacter::SWrite(const DBC_VArrayOfCharacter& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  Standard_Integer i;

  f.BeginWriteObjectData();
  f.PutInteger(pp.Length());
  for (i = 0; i < pp.Length(); i++) {
    f.PutCharacter(pp.Value(i));

  }
  f.EndWriteObjectData();
}

void StdSchema_DBC_VArrayOfCharacter::SRead(DBC_VArrayOfCharacter& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
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
