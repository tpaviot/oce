#ifndef _ShapeSchema_PColgp_FieldOfHArray2OfCirc2d_HeaderFile
#include <ShapeSchema_PColgp_FieldOfHArray2OfCirc2d.hxx>
#endif
#ifndef _PColgp_FieldOfHArray2OfCirc2d_HeaderFile
#include <PColgp_FieldOfHArray2OfCirc2d.hxx>
#endif
#include <ShapeSchema_PColgp_FieldOfHArray2OfCirc2d.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void ShapeSchema_PColgp_FieldOfHArray2OfCirc2d::SWrite(const PColgp_FieldOfHArray2OfCirc2d& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)theSchema; // dummy to avoid compiler warning on unused arg

  f.BeginWriteObjectData();
  f.PutInteger(pp.Length());
  for (Standard_Integer i = 0; i < pp.Length(); i++) {
    ShapeSchema_gp_Circ2d::SWrite(pp.Value(i),f,theSchema);

  }
  f.EndWriteObjectData();
}

void ShapeSchema_PColgp_FieldOfHArray2OfCirc2d::SRead(PColgp_FieldOfHArray2OfCirc2d& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)theSchema; // dummy to avoid compiler warning on unused arg
  Standard_Integer size = 0;

  f.BeginReadObjectData();
  f.GetInteger(size);
  pp.Resize(size);

  for (Standard_Integer j = 0; j < size; j++) {
    ShapeSchema_gp_Circ2d::SRead((gp_Circ2d&)pp.Value(j),f,theSchema);

  }
  f.EndReadObjectData();
}
