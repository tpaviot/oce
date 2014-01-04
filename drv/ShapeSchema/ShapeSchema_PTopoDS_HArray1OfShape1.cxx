#ifndef _ShapeSchema_PTopoDS_HArray1OfShape1_HeaderFile
#include <ShapeSchema_PTopoDS_HArray1OfShape1.hxx>
#endif
#ifndef _PTopoDS_HArray1OfShape1_HeaderFile
#include <PTopoDS_HArray1OfShape1.hxx>
#endif
#include <ShapeSchema_PTopoDS_HArray1OfShape1.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PTopoDS_HArray1OfShape1,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PTopoDS_HArray1OfShape1,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PTopoDS_HArray1OfShape1::New() const
{
  return new PTopoDS_HArray1OfShape1(Storage_stCONSTclCOM());
}

void ShapeSchema_PTopoDS_HArray1OfShape1::SAdd(const Handle(PTopoDS_HArray1OfShape1)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PTopoDS_HArray1OfShape1")) {
         ShapeSchema_PTopoDS_FieldOfHArray1OfShape1::SAdd(p->_CSFDB_GetPTopoDS_HArray1OfShape1Data(),theSchema);

    }
  }
}

void ShapeSchema_PTopoDS_HArray1OfShape1::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PTopoDS_HArray1OfShape1::SAdd((Handle(PTopoDS_HArray1OfShape1)&)p,theSchema);
}

void ShapeSchema_PTopoDS_HArray1OfShape1::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopoDS_HArray1OfShape1) &pp = (Handle(PTopoDS_HArray1OfShape1)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPTopoDS_HArray1OfShape1LowerBound());
  f.PutInteger(pp->_CSFDB_GetPTopoDS_HArray1OfShape1UpperBound());
    ShapeSchema_PTopoDS_FieldOfHArray1OfShape1::SWrite(pp->_CSFDB_GetPTopoDS_HArray1OfShape1Data(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PTopoDS_HArray1OfShape1::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PTopoDS_HArray1OfShape1::SWrite(p,f,theSchema);
}


void ShapeSchema_PTopoDS_HArray1OfShape1::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopoDS_HArray1OfShape1) &pp = (Handle(PTopoDS_HArray1OfShape1)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PTopoDS_HArray1OfShape1LowerBound;
    f.GetInteger(PTopoDS_HArray1OfShape1LowerBound);
    pp->_CSFDB_SetPTopoDS_HArray1OfShape1LowerBound(PTopoDS_HArray1OfShape1LowerBound);

    Standard_Integer PTopoDS_HArray1OfShape1UpperBound;
    f.GetInteger(PTopoDS_HArray1OfShape1UpperBound);
    pp->_CSFDB_SetPTopoDS_HArray1OfShape1UpperBound(PTopoDS_HArray1OfShape1UpperBound);

    ShapeSchema_PTopoDS_FieldOfHArray1OfShape1::SRead((PTopoDS_FieldOfHArray1OfShape1&)pp->_CSFDB_GetPTopoDS_HArray1OfShape1Data(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PTopoDS_HArray1OfShape1::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PTopoDS_HArray1OfShape1::SRead(p,f,theSchema);
}
