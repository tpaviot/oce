#ifndef _StdSchema_gp_Mat2d_HeaderFile
#include <StdSchema_gp_Mat2d.hxx>
#endif
#ifndef _gp_Mat2d_HeaderFile
#include <gp_Mat2d.hxx>
#endif
#include <StdSchema_gp_Mat2d.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void StdSchema_gp_Mat2d::SWrite(const gp_Mat2d& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)pp; (void)theSchema; // dummy to avoid compiler warning on unused arg
  f.BeginWriteObjectData();
  Standard_Integer gp_Mat2dmatrix1 = 0,gp_Mat2dmatrix2 = 0;

    for (gp_Mat2dmatrix1 = 0; gp_Mat2dmatrix1 < 2; gp_Mat2dmatrix1++)
    for (gp_Mat2dmatrix2 = 0; gp_Mat2dmatrix2 < 2; gp_Mat2dmatrix2++)
 {
    f.PutReal(((gp_Mat2d&)pp)._CSFDB_Getgp_Mat2dmatrix(gp_Mat2dmatrix1,gp_Mat2dmatrix2));

  }

  f.EndWriteObjectData();
}

void StdSchema_gp_Mat2d::SRead(gp_Mat2d& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)pp; (void)theSchema; // dummy to avoid compiler warning on unused arg
  f.BeginReadObjectData();
  Standard_Integer gp_Mat2dmatrix1 = 0,gp_Mat2dmatrix2 = 0;
   
    for (gp_Mat2dmatrix1 = 0; gp_Mat2dmatrix1 < 2; gp_Mat2dmatrix1++)
    for (gp_Mat2dmatrix2 = 0; gp_Mat2dmatrix2 < 2; gp_Mat2dmatrix2++)
 {
  Standard_Real gp_Mat2dmatrix;

  f.GetReal(gp_Mat2dmatrix);
  pp._CSFDB_Getgp_Mat2dmatrix(gp_Mat2dmatrix1,gp_Mat2dmatrix2) = gp_Mat2dmatrix;

}

  f.EndReadObjectData();
}
