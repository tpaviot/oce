#ifndef _ShapeSchema_gp_Trsf_HeaderFile
#include <ShapeSchema_gp_Trsf.hxx>
#endif
#ifndef _gp_Trsf_HeaderFile
#include <gp_Trsf.hxx>
#endif
#include <ShapeSchema_gp_Trsf.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void ShapeSchema_gp_Trsf::SWrite(const gp_Trsf& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)pp; (void)theSchema; // dummy to avoid compiler warning on unused arg
  f.BeginWriteObjectData();
  f.PutReal(pp._CSFDB_Getgp_Trsfscale());
  f.PutInteger(pp._CSFDB_Getgp_Trsfshape());
    ShapeSchema_gp_Mat::SWrite(pp._CSFDB_Getgp_Trsfmatrix(),f,theSchema);
    ShapeSchema_gp_XYZ::SWrite(pp._CSFDB_Getgp_Trsfloc(),f,theSchema);

  f.EndWriteObjectData();
}

void ShapeSchema_gp_Trsf::SRead(gp_Trsf& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)pp; (void)theSchema; // dummy to avoid compiler warning on unused arg
  f.BeginReadObjectData();

    Standard_Real gp_Trsfscale;
    f.GetReal(gp_Trsfscale);
    pp._CSFDB_Setgp_Trsfscale(gp_Trsfscale);

    gp_TrsfForm gp_Trsfshape;
    Standard_Integer i_CSFDB_gp_Trsfshape;
    f.GetInteger(i_CSFDB_gp_Trsfshape);
    gp_Trsfshape = (gp_TrsfForm)i_CSFDB_gp_Trsfshape;
    pp._CSFDB_Setgp_Trsfshape(gp_Trsfshape);

    ShapeSchema_gp_Mat::SRead((gp_Mat&)pp._CSFDB_Getgp_Trsfmatrix(),f,theSchema);

    ShapeSchema_gp_XYZ::SRead((gp_XYZ&)pp._CSFDB_Getgp_Trsfloc(),f,theSchema);

  f.EndReadObjectData();
}
