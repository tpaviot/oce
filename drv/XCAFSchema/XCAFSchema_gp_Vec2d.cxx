#ifndef _XCAFSchema_gp_Vec2d_HeaderFile
#include <XCAFSchema_gp_Vec2d.hxx>
#endif
#ifndef _gp_Vec2d_HeaderFile
#include <gp_Vec2d.hxx>
#endif
#include <XCAFSchema_gp_Vec2d.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void XCAFSchema_gp_Vec2d::SWrite(const gp_Vec2d& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)pp; (void)theSchema; // dummy to avoid compiler warning on unused arg
  f.BeginWriteObjectData();
    XCAFSchema_gp_XY::SWrite(pp._CSFDB_Getgp_Vec2dcoord(),f,theSchema);

  f.EndWriteObjectData();
}

void XCAFSchema_gp_Vec2d::SRead(gp_Vec2d& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)pp; (void)theSchema; // dummy to avoid compiler warning on unused arg
  f.BeginReadObjectData();

    XCAFSchema_gp_XY::SRead((gp_XY&)pp._CSFDB_Getgp_Vec2dcoord(),f,theSchema);

  f.EndReadObjectData();
}
