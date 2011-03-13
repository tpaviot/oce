#ifndef _ShapeSchema_PColgp_FieldOfHArray2OfDir_HeaderFile
#include <ShapeSchema_PColgp_FieldOfHArray2OfDir.hxx>
#endif
#ifndef _PColgp_FieldOfHArray2OfDir_HeaderFile
#include <PColgp_FieldOfHArray2OfDir.hxx>
#endif
#include <ShapeSchema_PColgp_FieldOfHArray2OfDir.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void ShapeSchema_PColgp_FieldOfHArray2OfDir::SWrite(const PColgp_FieldOfHArray2OfDir& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  Standard_Integer i;

  f.BeginWriteObjectData();
  f.PutInteger(pp.Length());
  for (i = 0; i < pp.Length(); i++) {
    ShapeSchema_gp_Dir::SWrite(pp.Value(i),f,theSchema);

  }
  f.EndWriteObjectData();
}

void ShapeSchema_PColgp_FieldOfHArray2OfDir::SRead(PColgp_FieldOfHArray2OfDir& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  Standard_Integer size = 0;

  f.BeginReadObjectData();
  f.GetInteger(size);
  pp.Resize(size);

  for (Standard_Integer j = 0; j < size; j++) {
    ShapeSchema_gp_Dir::SRead((gp_Dir&)pp.Value(j),f,theSchema);

  }
  f.EndReadObjectData();
}
