#ifndef _ShapeSchema_PTopoDS_HArray1OfHShape_HeaderFile
#include <ShapeSchema_PTopoDS_HArray1OfHShape.hxx>
#endif
#ifndef _PTopoDS_HArray1OfHShape_HeaderFile
#include <PTopoDS_HArray1OfHShape.hxx>
#endif
#include <ShapeSchema_PTopoDS_HArray1OfHShape.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PTopoDS_HArray1OfHShape,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PTopoDS_HArray1OfHShape,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PTopoDS_HArray1OfHShape::New() const
{
  return new PTopoDS_HArray1OfHShape(Storage_stCONSTclCOM());
}

void ShapeSchema_PTopoDS_HArray1OfHShape::SAdd(const Handle(PTopoDS_HArray1OfHShape)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PTopoDS_HArray1OfHShape")) {
         ShapeSchema_PTopoDS_FieldOfHArray1OfHShape::SAdd(p->_CSFDB_GetPTopoDS_HArray1OfHShapeData(),theSchema);

    }
  }
}

void ShapeSchema_PTopoDS_HArray1OfHShape::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PTopoDS_HArray1OfHShape::SAdd((Handle(PTopoDS_HArray1OfHShape)&)p,theSchema);
}

void ShapeSchema_PTopoDS_HArray1OfHShape::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopoDS_HArray1OfHShape) &pp = (Handle(PTopoDS_HArray1OfHShape)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPTopoDS_HArray1OfHShapeLowerBound());
  f.PutInteger(pp->_CSFDB_GetPTopoDS_HArray1OfHShapeUpperBound());
    ShapeSchema_PTopoDS_FieldOfHArray1OfHShape::SWrite(pp->_CSFDB_GetPTopoDS_HArray1OfHShapeData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PTopoDS_HArray1OfHShape::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PTopoDS_HArray1OfHShape::SWrite(p,f,theSchema);
}


void ShapeSchema_PTopoDS_HArray1OfHShape::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopoDS_HArray1OfHShape) &pp = (Handle(PTopoDS_HArray1OfHShape)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PTopoDS_HArray1OfHShapeLowerBound;
    f.GetInteger(PTopoDS_HArray1OfHShapeLowerBound);
    pp->_CSFDB_SetPTopoDS_HArray1OfHShapeLowerBound(PTopoDS_HArray1OfHShapeLowerBound);

    Standard_Integer PTopoDS_HArray1OfHShapeUpperBound;
    f.GetInteger(PTopoDS_HArray1OfHShapeUpperBound);
    pp->_CSFDB_SetPTopoDS_HArray1OfHShapeUpperBound(PTopoDS_HArray1OfHShapeUpperBound);

    ShapeSchema_PTopoDS_FieldOfHArray1OfHShape::SRead((PTopoDS_FieldOfHArray1OfHShape&)pp->_CSFDB_GetPTopoDS_HArray1OfHShapeData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PTopoDS_HArray1OfHShape::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PTopoDS_HArray1OfHShape::SRead(p,f,theSchema);
}
