#ifndef _ShapeSchema_PColgp_HArray2OfVec_HeaderFile
#include <ShapeSchema_PColgp_HArray2OfVec.hxx>
#endif
#ifndef _PColgp_HArray2OfVec_HeaderFile
#include <PColgp_HArray2OfVec.hxx>
#endif
#include <ShapeSchema_PColgp_HArray2OfVec.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_HArray2OfVec,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_HArray2OfVec,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_HArray2OfVec::New() const
{
  return new PColgp_HArray2OfVec(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_HArray2OfVec::SAdd(const Handle(PColgp_HArray2OfVec)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_HArray2OfVec")) {
      
    }
  }
}

void ShapeSchema_PColgp_HArray2OfVec::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_HArray2OfVec::SAdd((Handle(PColgp_HArray2OfVec)&)p,theSchema);
}

void ShapeSchema_PColgp_HArray2OfVec::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray2OfVec) &pp = (Handle(PColgp_HArray2OfVec)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfVecmyLowerRow());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfVecmyLowerCol());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfVecmyUpperRow());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfVecmyUpperCol());
    ShapeSchema_PColgp_FieldOfHArray2OfVec::SWrite(pp->_CSFDB_GetPColgp_HArray2OfVecData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray2OfVec::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_HArray2OfVec::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_HArray2OfVec::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray2OfVec) &pp = (Handle(PColgp_HArray2OfVec)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColgp_HArray2OfVecmyLowerRow;
    f.GetInteger(PColgp_HArray2OfVecmyLowerRow);
    pp->_CSFDB_SetPColgp_HArray2OfVecmyLowerRow(PColgp_HArray2OfVecmyLowerRow);

    Standard_Integer PColgp_HArray2OfVecmyLowerCol;
    f.GetInteger(PColgp_HArray2OfVecmyLowerCol);
    pp->_CSFDB_SetPColgp_HArray2OfVecmyLowerCol(PColgp_HArray2OfVecmyLowerCol);

    Standard_Integer PColgp_HArray2OfVecmyUpperRow;
    f.GetInteger(PColgp_HArray2OfVecmyUpperRow);
    pp->_CSFDB_SetPColgp_HArray2OfVecmyUpperRow(PColgp_HArray2OfVecmyUpperRow);

    Standard_Integer PColgp_HArray2OfVecmyUpperCol;
    f.GetInteger(PColgp_HArray2OfVecmyUpperCol);
    pp->_CSFDB_SetPColgp_HArray2OfVecmyUpperCol(PColgp_HArray2OfVecmyUpperCol);

    ShapeSchema_PColgp_FieldOfHArray2OfVec::SRead((PColgp_FieldOfHArray2OfVec&)pp->_CSFDB_GetPColgp_HArray2OfVecData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray2OfVec::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_HArray2OfVec::SRead(p,f,theSchema);
}
