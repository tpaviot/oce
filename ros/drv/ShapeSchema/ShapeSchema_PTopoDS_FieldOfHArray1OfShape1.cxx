#ifndef _ShapeSchema_PTopoDS_FieldOfHArray1OfShape1_HeaderFile
#include <ShapeSchema_PTopoDS_FieldOfHArray1OfShape1.hxx>
#endif
#ifndef _PTopoDS_FieldOfHArray1OfShape1_HeaderFile
#include <PTopoDS_FieldOfHArray1OfShape1.hxx>
#endif
#include <ShapeSchema_PTopoDS_FieldOfHArray1OfShape1.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void ShapeSchema_PTopoDS_FieldOfHArray1OfShape1::SAdd(const PTopoDS_FieldOfHArray1OfShape1& p, const Handle(Storage_Schema)& theSchema)
{
    Standard_Integer i;
  for (i = 0; i < p.Length(); i++) {
    ShapeSchema_PTopoDS_Shape1::SAdd(p.Value(i),theSchema);    
  }

}

void ShapeSchema_PTopoDS_FieldOfHArray1OfShape1::SWrite(const PTopoDS_FieldOfHArray1OfShape1& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  Standard_Integer i;

  f.BeginWriteObjectData();
  f.PutInteger(pp.Length());
  for (i = 0; i < pp.Length(); i++) {
    ShapeSchema_PTopoDS_Shape1::SWrite(pp.Value(i),f,theSchema);

  }
  f.EndWriteObjectData();
}

void ShapeSchema_PTopoDS_FieldOfHArray1OfShape1::SRead(PTopoDS_FieldOfHArray1OfShape1& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  Standard_Integer size = 0;

  f.BeginReadObjectData();
  f.GetInteger(size);
  pp.Resize(size);

  for (Standard_Integer j = 0; j < size; j++) {
    ShapeSchema_PTopoDS_Shape1::SRead((PTopoDS_Shape1&)pp.Value(j),f,theSchema);

  }
  f.EndReadObjectData();
}
