#ifndef _StdLSchema_Standard_GUID_HeaderFile
#include <StdLSchema_Standard_GUID.hxx>
#endif
#ifndef _Standard_GUID_HeaderFile
#include <Standard_GUID.hxx>
#endif
#include <StdLSchema_Standard_GUID.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void StdLSchema_Standard_GUID::SWrite(const Standard_GUID& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  f.BeginWriteObjectData();
  f.PutInteger(pp._CSFDB_GetStandard_GUIDmy32b());
  f.PutExtCharacter(pp._CSFDB_GetStandard_GUIDmy16b1());
  f.PutExtCharacter(pp._CSFDB_GetStandard_GUIDmy16b2());
  f.PutExtCharacter(pp._CSFDB_GetStandard_GUIDmy16b3());
  f.PutCharacter(pp._CSFDB_GetStandard_GUIDmy8b1());
  f.PutCharacter(pp._CSFDB_GetStandard_GUIDmy8b2());
  f.PutCharacter(pp._CSFDB_GetStandard_GUIDmy8b3());
  f.PutCharacter(pp._CSFDB_GetStandard_GUIDmy8b4());
  f.PutCharacter(pp._CSFDB_GetStandard_GUIDmy8b5());
  f.PutCharacter(pp._CSFDB_GetStandard_GUIDmy8b6());

  f.EndWriteObjectData();
}

void StdLSchema_Standard_GUID::SRead(Standard_GUID& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  f.BeginReadObjectData();

    Standard_Integer Standard_GUIDmy32b;
    f.GetInteger(Standard_GUIDmy32b);
    pp._CSFDB_SetStandard_GUIDmy32b(Standard_GUIDmy32b);

    Standard_ExtCharacter Standard_GUIDmy16b1;
    f.GetExtCharacter(Standard_GUIDmy16b1);
    pp._CSFDB_SetStandard_GUIDmy16b1(Standard_GUIDmy16b1);

    Standard_ExtCharacter Standard_GUIDmy16b2;
    f.GetExtCharacter(Standard_GUIDmy16b2);
    pp._CSFDB_SetStandard_GUIDmy16b2(Standard_GUIDmy16b2);

    Standard_ExtCharacter Standard_GUIDmy16b3;
    f.GetExtCharacter(Standard_GUIDmy16b3);
    pp._CSFDB_SetStandard_GUIDmy16b3(Standard_GUIDmy16b3);

    Standard_Character Standard_GUIDmy8b1;
    f.GetCharacter(Standard_GUIDmy8b1);
    pp._CSFDB_SetStandard_GUIDmy8b1(Standard_GUIDmy8b1);

    Standard_Character Standard_GUIDmy8b2;
    f.GetCharacter(Standard_GUIDmy8b2);
    pp._CSFDB_SetStandard_GUIDmy8b2(Standard_GUIDmy8b2);

    Standard_Character Standard_GUIDmy8b3;
    f.GetCharacter(Standard_GUIDmy8b3);
    pp._CSFDB_SetStandard_GUIDmy8b3(Standard_GUIDmy8b3);

    Standard_Character Standard_GUIDmy8b4;
    f.GetCharacter(Standard_GUIDmy8b4);
    pp._CSFDB_SetStandard_GUIDmy8b4(Standard_GUIDmy8b4);

    Standard_Character Standard_GUIDmy8b5;
    f.GetCharacter(Standard_GUIDmy8b5);
    pp._CSFDB_SetStandard_GUIDmy8b5(Standard_GUIDmy8b5);

    Standard_Character Standard_GUIDmy8b6;
    f.GetCharacter(Standard_GUIDmy8b6);
    pp._CSFDB_SetStandard_GUIDmy8b6(Standard_GUIDmy8b6);

  f.EndReadObjectData();
}
