#ifndef _ShapeSchema_gp_Vec_HeaderFile
#include <ShapeSchema_gp_Vec.hxx>
#endif
#ifndef _gp_Vec_HeaderFile
#include <gp_Vec.hxx>
#endif
#include <ShapeSchema_gp_Vec.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void ShapeSchema_gp_Vec::SWrite(const gp_Vec& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  f.BeginWriteObjectData();
    ShapeSchema_gp_XYZ::SWrite(pp._CSFDB_Getgp_Veccoord(),f,theSchema);

  f.EndWriteObjectData();
}

void ShapeSchema_gp_Vec::SRead(gp_Vec& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  f.BeginReadObjectData();

    ShapeSchema_gp_XYZ::SRead((gp_XYZ&)pp._CSFDB_Getgp_Veccoord(),f,theSchema);

  f.EndReadObjectData();
}
