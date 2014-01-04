#ifndef _ShapeSchema_PPoly_HArray1OfTriangle_HeaderFile
#include <ShapeSchema_PPoly_HArray1OfTriangle.hxx>
#endif
#ifndef _PPoly_HArray1OfTriangle_HeaderFile
#include <PPoly_HArray1OfTriangle.hxx>
#endif
#include <ShapeSchema_PPoly_HArray1OfTriangle.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PPoly_HArray1OfTriangle,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PPoly_HArray1OfTriangle,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PPoly_HArray1OfTriangle::New() const
{
  return new PPoly_HArray1OfTriangle(Storage_stCONSTclCOM());
}

void ShapeSchema_PPoly_HArray1OfTriangle::SAdd(const Handle(PPoly_HArray1OfTriangle)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PPoly_HArray1OfTriangle")) {
      
    }
  }
}

void ShapeSchema_PPoly_HArray1OfTriangle::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PPoly_HArray1OfTriangle::SAdd((Handle(PPoly_HArray1OfTriangle)&)p,theSchema);
}

void ShapeSchema_PPoly_HArray1OfTriangle::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PPoly_HArray1OfTriangle) &pp = (Handle(PPoly_HArray1OfTriangle)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPPoly_HArray1OfTriangleLowerBound());
  f.PutInteger(pp->_CSFDB_GetPPoly_HArray1OfTriangleUpperBound());
    ShapeSchema_PPoly_FieldOfHArray1OfTriangle::SWrite(pp->_CSFDB_GetPPoly_HArray1OfTriangleData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PPoly_HArray1OfTriangle::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PPoly_HArray1OfTriangle::SWrite(p,f,theSchema);
}


void ShapeSchema_PPoly_HArray1OfTriangle::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PPoly_HArray1OfTriangle) &pp = (Handle(PPoly_HArray1OfTriangle)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PPoly_HArray1OfTriangleLowerBound;
    f.GetInteger(PPoly_HArray1OfTriangleLowerBound);
    pp->_CSFDB_SetPPoly_HArray1OfTriangleLowerBound(PPoly_HArray1OfTriangleLowerBound);

    Standard_Integer PPoly_HArray1OfTriangleUpperBound;
    f.GetInteger(PPoly_HArray1OfTriangleUpperBound);
    pp->_CSFDB_SetPPoly_HArray1OfTriangleUpperBound(PPoly_HArray1OfTriangleUpperBound);

    ShapeSchema_PPoly_FieldOfHArray1OfTriangle::SRead((PPoly_FieldOfHArray1OfTriangle&)pp->_CSFDB_GetPPoly_HArray1OfTriangleData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PPoly_HArray1OfTriangle::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PPoly_HArray1OfTriangle::SRead(p,f,theSchema);
}
