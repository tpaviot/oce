#ifndef _ShapeSchema_gp_XYZ_HeaderFile
#include <ShapeSchema_gp_XYZ.hxx>
#endif
#ifndef _gp_XYZ_HeaderFile
#include <gp_XYZ.hxx>
#endif
#include <ShapeSchema_gp_XYZ.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void ShapeSchema_gp_XYZ::SWrite(const gp_XYZ& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)pp; (void)theSchema; // dummy to avoid compiler warning on unused arg
  f.BeginWriteObjectData();
  f.PutReal(pp._CSFDB_Getgp_XYZx());
  f.PutReal(pp._CSFDB_Getgp_XYZy());
  f.PutReal(pp._CSFDB_Getgp_XYZz());

  f.EndWriteObjectData();
}

void ShapeSchema_gp_XYZ::SRead(gp_XYZ& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)pp; (void)theSchema; // dummy to avoid compiler warning on unused arg
  f.BeginReadObjectData();

    Standard_Real gp_XYZx;
    f.GetReal(gp_XYZx);
    pp._CSFDB_Setgp_XYZx(gp_XYZx);

    Standard_Real gp_XYZy;
    f.GetReal(gp_XYZy);
    pp._CSFDB_Setgp_XYZy(gp_XYZy);

    Standard_Real gp_XYZz;
    f.GetReal(gp_XYZz);
    pp._CSFDB_Setgp_XYZz(gp_XYZz);

  f.EndReadObjectData();
}
