#ifndef _StdSchema_gp_XY_HeaderFile
#include <StdSchema_gp_XY.hxx>
#endif
#ifndef _gp_XY_HeaderFile
#include <gp_XY.hxx>
#endif
#include <StdSchema_gp_XY.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void StdSchema_gp_XY::SWrite(const gp_XY& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  f.BeginWriteObjectData();
  f.PutReal(pp._CSFDB_Getgp_XYx());
  f.PutReal(pp._CSFDB_Getgp_XYy());

  f.EndWriteObjectData();
}

void StdSchema_gp_XY::SRead(gp_XY& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  f.BeginReadObjectData();

    Standard_Real gp_XYx;
    f.GetReal(gp_XYx);
    pp._CSFDB_Setgp_XYx(gp_XYx);

    Standard_Real gp_XYy;
    f.GetReal(gp_XYy);
    pp._CSFDB_Setgp_XYy(gp_XYy);

  f.EndReadObjectData();
}
