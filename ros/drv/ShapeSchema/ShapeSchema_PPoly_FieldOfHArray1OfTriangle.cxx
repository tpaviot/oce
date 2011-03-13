#ifndef _ShapeSchema_PPoly_FieldOfHArray1OfTriangle_HeaderFile
#include <ShapeSchema_PPoly_FieldOfHArray1OfTriangle.hxx>
#endif
#ifndef _PPoly_FieldOfHArray1OfTriangle_HeaderFile
#include <PPoly_FieldOfHArray1OfTriangle.hxx>
#endif
#include <ShapeSchema_PPoly_FieldOfHArray1OfTriangle.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void ShapeSchema_PPoly_FieldOfHArray1OfTriangle::SWrite(const PPoly_FieldOfHArray1OfTriangle& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  Standard_Integer i;

  f.BeginWriteObjectData();
  f.PutInteger(pp.Length());
  for (i = 0; i < pp.Length(); i++) {
    ShapeSchema_PPoly_Triangle::SWrite(pp.Value(i),f,theSchema);

  }
  f.EndWriteObjectData();
}

void ShapeSchema_PPoly_FieldOfHArray1OfTriangle::SRead(PPoly_FieldOfHArray1OfTriangle& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  Standard_Integer size = 0;

  f.BeginReadObjectData();
  f.GetInteger(size);
  pp.Resize(size);

  for (Standard_Integer j = 0; j < size; j++) {
    ShapeSchema_PPoly_Triangle::SRead((PPoly_Triangle&)pp.Value(j),f,theSchema);

  }
  f.EndReadObjectData();
}
