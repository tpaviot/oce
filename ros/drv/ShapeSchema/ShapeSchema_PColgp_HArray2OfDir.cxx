#ifndef _ShapeSchema_PColgp_HArray2OfDir_HeaderFile
#include <ShapeSchema_PColgp_HArray2OfDir.hxx>
#endif
#ifndef _PColgp_HArray2OfDir_HeaderFile
#include <PColgp_HArray2OfDir.hxx>
#endif
#include <ShapeSchema_PColgp_HArray2OfDir.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_HArray2OfDir,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_HArray2OfDir,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_HArray2OfDir::New() const
{
  return new PColgp_HArray2OfDir(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_HArray2OfDir::SAdd(const Handle(PColgp_HArray2OfDir)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_HArray2OfDir")) {
      
    }
  }
}

void ShapeSchema_PColgp_HArray2OfDir::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_HArray2OfDir::SAdd((Handle(PColgp_HArray2OfDir)&)p,theSchema);
}

void ShapeSchema_PColgp_HArray2OfDir::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray2OfDir) &pp = (Handle(PColgp_HArray2OfDir)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfDirmyLowerRow());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfDirmyLowerCol());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfDirmyUpperRow());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfDirmyUpperCol());
    ShapeSchema_PColgp_FieldOfHArray2OfDir::SWrite(pp->_CSFDB_GetPColgp_HArray2OfDirData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray2OfDir::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_HArray2OfDir::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_HArray2OfDir::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray2OfDir) &pp = (Handle(PColgp_HArray2OfDir)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColgp_HArray2OfDirmyLowerRow;
    f.GetInteger(PColgp_HArray2OfDirmyLowerRow);
    pp->_CSFDB_SetPColgp_HArray2OfDirmyLowerRow(PColgp_HArray2OfDirmyLowerRow);

    Standard_Integer PColgp_HArray2OfDirmyLowerCol;
    f.GetInteger(PColgp_HArray2OfDirmyLowerCol);
    pp->_CSFDB_SetPColgp_HArray2OfDirmyLowerCol(PColgp_HArray2OfDirmyLowerCol);

    Standard_Integer PColgp_HArray2OfDirmyUpperRow;
    f.GetInteger(PColgp_HArray2OfDirmyUpperRow);
    pp->_CSFDB_SetPColgp_HArray2OfDirmyUpperRow(PColgp_HArray2OfDirmyUpperRow);

    Standard_Integer PColgp_HArray2OfDirmyUpperCol;
    f.GetInteger(PColgp_HArray2OfDirmyUpperCol);
    pp->_CSFDB_SetPColgp_HArray2OfDirmyUpperCol(PColgp_HArray2OfDirmyUpperCol);

    ShapeSchema_PColgp_FieldOfHArray2OfDir::SRead((PColgp_FieldOfHArray2OfDir&)pp->_CSFDB_GetPColgp_HArray2OfDirData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray2OfDir::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_HArray2OfDir::SRead(p,f,theSchema);
}
