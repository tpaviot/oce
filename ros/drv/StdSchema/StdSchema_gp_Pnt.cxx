#ifndef _StdSchema_gp_Pnt_HeaderFile
#include <StdSchema_gp_Pnt.hxx>
#endif
#ifndef _gp_Pnt_HeaderFile
#include <gp_Pnt.hxx>
#endif
#include <StdSchema_gp_Pnt.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void StdSchema_gp_Pnt::SWrite(const gp_Pnt& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  f.BeginWriteObjectData();
    StdSchema_gp_XYZ::SWrite(pp._CSFDB_Getgp_Pntcoord(),f,theSchema);

  f.EndWriteObjectData();
}

void StdSchema_gp_Pnt::SRead(gp_Pnt& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  f.BeginReadObjectData();

    StdSchema_gp_XYZ::SRead((gp_XYZ&)pp._CSFDB_Getgp_Pntcoord(),f,theSchema);

  f.EndReadObjectData();
}
