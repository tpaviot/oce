#ifndef _ShapeSchema_PPoly_Triangle_HeaderFile
#include <ShapeSchema_PPoly_Triangle.hxx>
#endif
#ifndef _PPoly_Triangle_HeaderFile
#include <PPoly_Triangle.hxx>
#endif
#include <ShapeSchema_PPoly_Triangle.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void ShapeSchema_PPoly_Triangle::SWrite(const PPoly_Triangle& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)pp; (void)theSchema; // dummy to avoid compiler warning on unused arg
  f.BeginWriteObjectData();
  Standard_Integer PPoly_TrianglemyNodes1 = 0;

    for (PPoly_TrianglemyNodes1 = 0; PPoly_TrianglemyNodes1 < 3; PPoly_TrianglemyNodes1++)
 {
    f.PutInteger(((PPoly_Triangle&)pp)._CSFDB_GetPPoly_TrianglemyNodes(PPoly_TrianglemyNodes1));

  }

  f.EndWriteObjectData();
}

void ShapeSchema_PPoly_Triangle::SRead(PPoly_Triangle& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)pp; (void)theSchema; // dummy to avoid compiler warning on unused arg
  f.BeginReadObjectData();
  Standard_Integer PPoly_TrianglemyNodes1 = 0;
   
    for (PPoly_TrianglemyNodes1 = 0; PPoly_TrianglemyNodes1 < 3; PPoly_TrianglemyNodes1++)
 {
  Standard_Integer PPoly_TrianglemyNodes;

  f.GetInteger(PPoly_TrianglemyNodes);
  pp._CSFDB_GetPPoly_TrianglemyNodes(PPoly_TrianglemyNodes1) = PPoly_TrianglemyNodes;

}

  f.EndReadObjectData();
}
