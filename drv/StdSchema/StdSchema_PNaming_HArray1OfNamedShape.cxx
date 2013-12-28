#ifndef _StdSchema_PNaming_HArray1OfNamedShape_HeaderFile
#include <StdSchema_PNaming_HArray1OfNamedShape.hxx>
#endif
#ifndef _PNaming_HArray1OfNamedShape_HeaderFile
#include <PNaming_HArray1OfNamedShape.hxx>
#endif
#include <StdSchema_PNaming_HArray1OfNamedShape.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PNaming_HArray1OfNamedShape,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PNaming_HArray1OfNamedShape,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PNaming_HArray1OfNamedShape::New() const
{
  return new PNaming_HArray1OfNamedShape(Storage_stCONSTclCOM());
}

void StdSchema_PNaming_HArray1OfNamedShape::SAdd(const Handle(PNaming_HArray1OfNamedShape)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PNaming_HArray1OfNamedShape")) {
         StdSchema_PNaming_FieldOfHArray1OfNamedShape::SAdd(p->_CSFDB_GetPNaming_HArray1OfNamedShapeData(),theSchema);

    }
  }
}

void StdSchema_PNaming_HArray1OfNamedShape::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PNaming_HArray1OfNamedShape::SAdd((Handle(PNaming_HArray1OfNamedShape)&)p,theSchema);
}

void StdSchema_PNaming_HArray1OfNamedShape::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PNaming_HArray1OfNamedShape) &pp = (Handle(PNaming_HArray1OfNamedShape)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPNaming_HArray1OfNamedShapeLowerBound());
  f.PutInteger(pp->_CSFDB_GetPNaming_HArray1OfNamedShapeUpperBound());
    StdSchema_PNaming_FieldOfHArray1OfNamedShape::SWrite(pp->_CSFDB_GetPNaming_HArray1OfNamedShapeData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PNaming_HArray1OfNamedShape::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PNaming_HArray1OfNamedShape::SWrite(p,f,theSchema);
}


void StdSchema_PNaming_HArray1OfNamedShape::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PNaming_HArray1OfNamedShape) &pp = (Handle(PNaming_HArray1OfNamedShape)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PNaming_HArray1OfNamedShapeLowerBound;
    f.GetInteger(PNaming_HArray1OfNamedShapeLowerBound);
    pp->_CSFDB_SetPNaming_HArray1OfNamedShapeLowerBound(PNaming_HArray1OfNamedShapeLowerBound);

    Standard_Integer PNaming_HArray1OfNamedShapeUpperBound;
    f.GetInteger(PNaming_HArray1OfNamedShapeUpperBound);
    pp->_CSFDB_SetPNaming_HArray1OfNamedShapeUpperBound(PNaming_HArray1OfNamedShapeUpperBound);

    StdSchema_PNaming_FieldOfHArray1OfNamedShape::SRead((PNaming_FieldOfHArray1OfNamedShape&)pp->_CSFDB_GetPNaming_HArray1OfNamedShapeData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PNaming_HArray1OfNamedShape::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PNaming_HArray1OfNamedShape::SRead(p,f,theSchema);
}
