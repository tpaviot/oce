#ifndef _StdSchema_gp_Pnt2d_HeaderFile
#include <StdSchema_gp_Pnt2d.hxx>
#endif
#ifndef _gp_Pnt2d_HeaderFile
#include <gp_Pnt2d.hxx>
#endif
#include <StdSchema_gp_Pnt2d.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void StdSchema_gp_Pnt2d::SWrite(const gp_Pnt2d& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  f.BeginWriteObjectData();
    StdSchema_gp_XY::SWrite(pp._CSFDB_Getgp_Pnt2dcoord(),f,theSchema);

  f.EndWriteObjectData();
}

void StdSchema_gp_Pnt2d::SRead(gp_Pnt2d& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  f.BeginReadObjectData();

    StdSchema_gp_XY::SRead((gp_XY&)pp._CSFDB_Getgp_Pnt2dcoord(),f,theSchema);

  f.EndReadObjectData();
}
