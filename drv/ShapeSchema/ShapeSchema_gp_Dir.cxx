#ifndef _ShapeSchema_gp_Dir_HeaderFile
#include <ShapeSchema_gp_Dir.hxx>
#endif
#ifndef _gp_Dir_HeaderFile
#include <gp_Dir.hxx>
#endif
#include <ShapeSchema_gp_Dir.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void ShapeSchema_gp_Dir::SWrite(const gp_Dir& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)pp; (void)theSchema; // dummy to avoid compiler warning on unused arg
  f.BeginWriteObjectData();
    ShapeSchema_gp_XYZ::SWrite(pp._CSFDB_Getgp_Dircoord(),f,theSchema);

  f.EndWriteObjectData();
}

void ShapeSchema_gp_Dir::SRead(gp_Dir& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)pp; (void)theSchema; // dummy to avoid compiler warning on unused arg
  f.BeginReadObjectData();

    ShapeSchema_gp_XYZ::SRead((gp_XYZ&)pp._CSFDB_Getgp_Dircoord(),f,theSchema);

  f.EndReadObjectData();
}
