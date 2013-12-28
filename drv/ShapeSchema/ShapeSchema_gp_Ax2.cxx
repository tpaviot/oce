#ifndef _ShapeSchema_gp_Ax2_HeaderFile
#include <ShapeSchema_gp_Ax2.hxx>
#endif
#ifndef _gp_Ax2_HeaderFile
#include <gp_Ax2.hxx>
#endif
#include <ShapeSchema_gp_Ax2.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void ShapeSchema_gp_Ax2::SWrite(const gp_Ax2& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)pp; (void)theSchema; // dummy to avoid compiler warning on unused arg
  f.BeginWriteObjectData();
    ShapeSchema_gp_Ax1::SWrite(pp._CSFDB_Getgp_Ax2axis(),f,theSchema);
    ShapeSchema_gp_Dir::SWrite(pp._CSFDB_Getgp_Ax2vydir(),f,theSchema);
    ShapeSchema_gp_Dir::SWrite(pp._CSFDB_Getgp_Ax2vxdir(),f,theSchema);

  f.EndWriteObjectData();
}

void ShapeSchema_gp_Ax2::SRead(gp_Ax2& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)pp; (void)theSchema; // dummy to avoid compiler warning on unused arg
  f.BeginReadObjectData();

    ShapeSchema_gp_Ax1::SRead((gp_Ax1&)pp._CSFDB_Getgp_Ax2axis(),f,theSchema);

    ShapeSchema_gp_Dir::SRead((gp_Dir&)pp._CSFDB_Getgp_Ax2vydir(),f,theSchema);

    ShapeSchema_gp_Dir::SRead((gp_Dir&)pp._CSFDB_Getgp_Ax2vxdir(),f,theSchema);

  f.EndReadObjectData();
}
