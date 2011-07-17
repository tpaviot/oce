#ifndef _ShapeSchema_PColgp_HArray2OfXY_HeaderFile
#include <ShapeSchema_PColgp_HArray2OfXY.hxx>
#endif
#ifndef _PColgp_HArray2OfXY_HeaderFile
#include <PColgp_HArray2OfXY.hxx>
#endif
#include <ShapeSchema_PColgp_HArray2OfXY.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_HArray2OfXY,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_HArray2OfXY,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_HArray2OfXY::New() const
{
  return new PColgp_HArray2OfXY(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_HArray2OfXY::SAdd(const Handle(PColgp_HArray2OfXY)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_HArray2OfXY")) {
      
    }
  }
}

void ShapeSchema_PColgp_HArray2OfXY::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_HArray2OfXY::SAdd((Handle(PColgp_HArray2OfXY)&)p,theSchema);
}

void ShapeSchema_PColgp_HArray2OfXY::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray2OfXY) &pp = (Handle(PColgp_HArray2OfXY)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfXYmyLowerRow());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfXYmyLowerCol());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfXYmyUpperRow());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfXYmyUpperCol());
    ShapeSchema_PColgp_FieldOfHArray2OfXY::SWrite(pp->_CSFDB_GetPColgp_HArray2OfXYData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray2OfXY::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_HArray2OfXY::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_HArray2OfXY::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray2OfXY) &pp = (Handle(PColgp_HArray2OfXY)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColgp_HArray2OfXYmyLowerRow;
    f.GetInteger(PColgp_HArray2OfXYmyLowerRow);
    pp->_CSFDB_SetPColgp_HArray2OfXYmyLowerRow(PColgp_HArray2OfXYmyLowerRow);

    Standard_Integer PColgp_HArray2OfXYmyLowerCol;
    f.GetInteger(PColgp_HArray2OfXYmyLowerCol);
    pp->_CSFDB_SetPColgp_HArray2OfXYmyLowerCol(PColgp_HArray2OfXYmyLowerCol);

    Standard_Integer PColgp_HArray2OfXYmyUpperRow;
    f.GetInteger(PColgp_HArray2OfXYmyUpperRow);
    pp->_CSFDB_SetPColgp_HArray2OfXYmyUpperRow(PColgp_HArray2OfXYmyUpperRow);

    Standard_Integer PColgp_HArray2OfXYmyUpperCol;
    f.GetInteger(PColgp_HArray2OfXYmyUpperCol);
    pp->_CSFDB_SetPColgp_HArray2OfXYmyUpperCol(PColgp_HArray2OfXYmyUpperCol);

    ShapeSchema_PColgp_FieldOfHArray2OfXY::SRead((PColgp_FieldOfHArray2OfXY&)pp->_CSFDB_GetPColgp_HArray2OfXYData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray2OfXY::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_HArray2OfXY::SRead(p,f,theSchema);
}
