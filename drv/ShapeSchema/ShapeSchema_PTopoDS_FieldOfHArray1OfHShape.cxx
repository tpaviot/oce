#ifndef _ShapeSchema_PTopoDS_FieldOfHArray1OfHShape_HeaderFile
#include <ShapeSchema_PTopoDS_FieldOfHArray1OfHShape.hxx>
#endif
#ifndef _PTopoDS_FieldOfHArray1OfHShape_HeaderFile
#include <PTopoDS_FieldOfHArray1OfHShape.hxx>
#endif
#include <ShapeSchema_PTopoDS_FieldOfHArray1OfHShape.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

void ShapeSchema_PTopoDS_FieldOfHArray1OfHShape::SAdd(const PTopoDS_FieldOfHArray1OfHShape& p, const Handle(Storage_Schema)& theSchema)
{
    Standard_Integer i;
  for (i = 0; i < p.Length(); i++) {
    theSchema->PersistentToAdd(p.Value(i));    
  }

}

void ShapeSchema_PTopoDS_FieldOfHArray1OfHShape::SWrite(const PTopoDS_FieldOfHArray1OfHShape& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)theSchema; // dummy to avoid compiler warning on unused arg

  f.BeginWriteObjectData();
  f.PutInteger(pp.Length());
  for (Standard_Integer i = 0; i < pp.Length(); i++) {
    theSchema->WritePersistentReference(pp.Value(i),f);

  }
  f.EndWriteObjectData();
}

void ShapeSchema_PTopoDS_FieldOfHArray1OfHShape::SRead(PTopoDS_FieldOfHArray1OfHShape& pp, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{
  (void)theSchema; // dummy to avoid compiler warning on unused arg
  Standard_Integer size = 0;

  f.BeginReadObjectData();
  f.GetInteger(size);
  pp.Resize(size);

  for (Standard_Integer j = 0; j < size; j++) {
    Handle(PTopoDS_HShape) par;

    theSchema->ReadPersistentReference(par,f);
    pp.SetValue(j,par);

  }
  f.EndReadObjectData();
}
