#ifndef _ShapeSchema_PColgp_HArray1OfXY_HeaderFile
#include <ShapeSchema_PColgp_HArray1OfXY.hxx>
#endif
#ifndef _PColgp_HArray1OfXY_HeaderFile
#include <PColgp_HArray1OfXY.hxx>
#endif
#include <ShapeSchema_PColgp_HArray1OfXY.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_HArray1OfXY,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_HArray1OfXY,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_HArray1OfXY::New() const
{
  return new PColgp_HArray1OfXY(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_HArray1OfXY::SAdd(const Handle(PColgp_HArray1OfXY)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_HArray1OfXY")) {
      
    }
  }
}

void ShapeSchema_PColgp_HArray1OfXY::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_HArray1OfXY::SAdd((Handle(PColgp_HArray1OfXY)&)p,theSchema);
}

void ShapeSchema_PColgp_HArray1OfXY::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray1OfXY) &pp = (Handle(PColgp_HArray1OfXY)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray1OfXYLowerBound());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray1OfXYUpperBound());
    ShapeSchema_PColgp_FieldOfHArray1OfXY::SWrite(pp->_CSFDB_GetPColgp_HArray1OfXYData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray1OfXY::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_HArray1OfXY::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_HArray1OfXY::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray1OfXY) &pp = (Handle(PColgp_HArray1OfXY)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColgp_HArray1OfXYLowerBound;
    f.GetInteger(PColgp_HArray1OfXYLowerBound);
    pp->_CSFDB_SetPColgp_HArray1OfXYLowerBound(PColgp_HArray1OfXYLowerBound);

    Standard_Integer PColgp_HArray1OfXYUpperBound;
    f.GetInteger(PColgp_HArray1OfXYUpperBound);
    pp->_CSFDB_SetPColgp_HArray1OfXYUpperBound(PColgp_HArray1OfXYUpperBound);

    ShapeSchema_PColgp_FieldOfHArray1OfXY::SRead((PColgp_FieldOfHArray1OfXY&)pp->_CSFDB_GetPColgp_HArray1OfXYData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray1OfXY::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_HArray1OfXY::SRead(p,f,theSchema);
}
