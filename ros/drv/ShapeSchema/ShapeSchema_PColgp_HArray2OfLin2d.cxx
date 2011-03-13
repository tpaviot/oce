#ifndef _ShapeSchema_PColgp_HArray2OfLin2d_HeaderFile
#include <ShapeSchema_PColgp_HArray2OfLin2d.hxx>
#endif
#ifndef _PColgp_HArray2OfLin2d_HeaderFile
#include <PColgp_HArray2OfLin2d.hxx>
#endif
#include <ShapeSchema_PColgp_HArray2OfLin2d.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_HArray2OfLin2d,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_HArray2OfLin2d,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_HArray2OfLin2d::New() const
{
  return new PColgp_HArray2OfLin2d(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_HArray2OfLin2d::SAdd(const Handle(PColgp_HArray2OfLin2d)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_HArray2OfLin2d")) {
      
    }
  }
}

void ShapeSchema_PColgp_HArray2OfLin2d::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_HArray2OfLin2d::SAdd((Handle(PColgp_HArray2OfLin2d)&)p,theSchema);
}

void ShapeSchema_PColgp_HArray2OfLin2d::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray2OfLin2d) &pp = (Handle(PColgp_HArray2OfLin2d)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfLin2dmyLowerRow());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfLin2dmyLowerCol());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfLin2dmyUpperRow());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfLin2dmyUpperCol());
    ShapeSchema_PColgp_FieldOfHArray2OfLin2d::SWrite(pp->_CSFDB_GetPColgp_HArray2OfLin2dData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray2OfLin2d::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_HArray2OfLin2d::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_HArray2OfLin2d::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray2OfLin2d) &pp = (Handle(PColgp_HArray2OfLin2d)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColgp_HArray2OfLin2dmyLowerRow;
    f.GetInteger(PColgp_HArray2OfLin2dmyLowerRow);
    pp->_CSFDB_SetPColgp_HArray2OfLin2dmyLowerRow(PColgp_HArray2OfLin2dmyLowerRow);

    Standard_Integer PColgp_HArray2OfLin2dmyLowerCol;
    f.GetInteger(PColgp_HArray2OfLin2dmyLowerCol);
    pp->_CSFDB_SetPColgp_HArray2OfLin2dmyLowerCol(PColgp_HArray2OfLin2dmyLowerCol);

    Standard_Integer PColgp_HArray2OfLin2dmyUpperRow;
    f.GetInteger(PColgp_HArray2OfLin2dmyUpperRow);
    pp->_CSFDB_SetPColgp_HArray2OfLin2dmyUpperRow(PColgp_HArray2OfLin2dmyUpperRow);

    Standard_Integer PColgp_HArray2OfLin2dmyUpperCol;
    f.GetInteger(PColgp_HArray2OfLin2dmyUpperCol);
    pp->_CSFDB_SetPColgp_HArray2OfLin2dmyUpperCol(PColgp_HArray2OfLin2dmyUpperCol);

    ShapeSchema_PColgp_FieldOfHArray2OfLin2d::SRead((PColgp_FieldOfHArray2OfLin2d&)pp->_CSFDB_GetPColgp_HArray2OfLin2dData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray2OfLin2d::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_HArray2OfLin2d::SRead(p,f,theSchema);
}
