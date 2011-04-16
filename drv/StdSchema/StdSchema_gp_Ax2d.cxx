#ifndef _StdSchema_gp_Ax2d_HeaderFile
#include <StdSchema_gp_Ax2d.hxx>
#endif
#ifndef _gp_Ax2d_HeaderFile
#include <gp_Ax2d.hxx>
#endif
#include <StdSchema_gp_Ax2d.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void StdSchema_gp_Ax2d::SWrite(const gp_Ax2d& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  f.BeginWriteObjectData();
    StdSchema_gp_Pnt2d::SWrite(pp._CSFDB_Getgp_Ax2dloc(),f,theSchema);
    StdSchema_gp_Dir2d::SWrite(pp._CSFDB_Getgp_Ax2dvdir(),f,theSchema);

  f.EndWriteObjectData();
}

void StdSchema_gp_Ax2d::SRead(gp_Ax2d& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  f.BeginReadObjectData();

    StdSchema_gp_Pnt2d::SRead((gp_Pnt2d&)pp._CSFDB_Getgp_Ax2dloc(),f,theSchema);

    StdSchema_gp_Dir2d::SRead((gp_Dir2d&)pp._CSFDB_Getgp_Ax2dvdir(),f,theSchema);

  f.EndReadObjectData();
}
