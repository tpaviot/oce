#ifndef _StdSchema_gp_Ax2_HeaderFile
#include <StdSchema_gp_Ax2.hxx>
#endif
#ifndef _gp_Ax2_HeaderFile
#include <gp_Ax2.hxx>
#endif
#include <StdSchema_gp_Ax2.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void StdSchema_gp_Ax2::SWrite(const gp_Ax2& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  f.BeginWriteObjectData();
    StdSchema_gp_Ax1::SWrite(pp._CSFDB_Getgp_Ax2axis(),f,theSchema);
    StdSchema_gp_Dir::SWrite(pp._CSFDB_Getgp_Ax2vydir(),f,theSchema);
    StdSchema_gp_Dir::SWrite(pp._CSFDB_Getgp_Ax2vxdir(),f,theSchema);

  f.EndWriteObjectData();
}

void StdSchema_gp_Ax2::SRead(gp_Ax2& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  f.BeginReadObjectData();

    StdSchema_gp_Ax1::SRead((gp_Ax1&)pp._CSFDB_Getgp_Ax2axis(),f,theSchema);

    StdSchema_gp_Dir::SRead((gp_Dir&)pp._CSFDB_Getgp_Ax2vydir(),f,theSchema);

    StdSchema_gp_Dir::SRead((gp_Dir&)pp._CSFDB_Getgp_Ax2vxdir(),f,theSchema);

  f.EndReadObjectData();
}
