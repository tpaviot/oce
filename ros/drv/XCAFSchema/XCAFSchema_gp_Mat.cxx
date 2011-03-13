#ifndef _XCAFSchema_gp_Mat_HeaderFile
#include <XCAFSchema_gp_Mat.hxx>
#endif
#ifndef _gp_Mat_HeaderFile
#include <gp_Mat.hxx>
#endif
#include <XCAFSchema_gp_Mat.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void XCAFSchema_gp_Mat::SWrite(const gp_Mat& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  f.BeginWriteObjectData();
  Standard_Integer gp_Matmatrix1 = 0,gp_Matmatrix2 = 0;

    for (gp_Matmatrix1 = 0; gp_Matmatrix1 < 3; gp_Matmatrix1++)
    for (gp_Matmatrix2 = 0; gp_Matmatrix2 < 3; gp_Matmatrix2++)
 {
    f.PutReal(((gp_Mat&)pp)._CSFDB_Getgp_Matmatrix(gp_Matmatrix1,gp_Matmatrix2));

  }

  f.EndWriteObjectData();
}

void XCAFSchema_gp_Mat::SRead(gp_Mat& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  f.BeginReadObjectData();
  Standard_Integer gp_Matmatrix1 = 0,gp_Matmatrix2 = 0;
   
    for (gp_Matmatrix1 = 0; gp_Matmatrix1 < 3; gp_Matmatrix1++)
    for (gp_Matmatrix2 = 0; gp_Matmatrix2 < 3; gp_Matmatrix2++)
 {
  Standard_Real gp_Matmatrix;

  f.GetReal(gp_Matmatrix);
  pp._CSFDB_Getgp_Matmatrix(gp_Matmatrix1,gp_Matmatrix2) = gp_Matmatrix;

}

  f.EndReadObjectData();
}
