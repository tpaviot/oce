#ifndef _ShapeSchema_PColgp_HArray2OfPnt_HeaderFile
#include <ShapeSchema_PColgp_HArray2OfPnt.hxx>
#endif
#ifndef _PColgp_HArray2OfPnt_HeaderFile
#include <PColgp_HArray2OfPnt.hxx>
#endif
#include <ShapeSchema_PColgp_HArray2OfPnt.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_HArray2OfPnt,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_HArray2OfPnt,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_HArray2OfPnt::New() const
{
  return new PColgp_HArray2OfPnt(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_HArray2OfPnt::SAdd(const Handle(PColgp_HArray2OfPnt)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_HArray2OfPnt")) {
      
    }
  }
}

void ShapeSchema_PColgp_HArray2OfPnt::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_HArray2OfPnt::SAdd((Handle(PColgp_HArray2OfPnt)&)p,theSchema);
}

void ShapeSchema_PColgp_HArray2OfPnt::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray2OfPnt) &pp = (Handle(PColgp_HArray2OfPnt)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfPntmyLowerRow());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfPntmyLowerCol());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfPntmyUpperRow());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfPntmyUpperCol());
    ShapeSchema_PColgp_FieldOfHArray2OfPnt::SWrite(pp->_CSFDB_GetPColgp_HArray2OfPntData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray2OfPnt::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_HArray2OfPnt::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_HArray2OfPnt::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray2OfPnt) &pp = (Handle(PColgp_HArray2OfPnt)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColgp_HArray2OfPntmyLowerRow;
    f.GetInteger(PColgp_HArray2OfPntmyLowerRow);
    pp->_CSFDB_SetPColgp_HArray2OfPntmyLowerRow(PColgp_HArray2OfPntmyLowerRow);

    Standard_Integer PColgp_HArray2OfPntmyLowerCol;
    f.GetInteger(PColgp_HArray2OfPntmyLowerCol);
    pp->_CSFDB_SetPColgp_HArray2OfPntmyLowerCol(PColgp_HArray2OfPntmyLowerCol);

    Standard_Integer PColgp_HArray2OfPntmyUpperRow;
    f.GetInteger(PColgp_HArray2OfPntmyUpperRow);
    pp->_CSFDB_SetPColgp_HArray2OfPntmyUpperRow(PColgp_HArray2OfPntmyUpperRow);

    Standard_Integer PColgp_HArray2OfPntmyUpperCol;
    f.GetInteger(PColgp_HArray2OfPntmyUpperCol);
    pp->_CSFDB_SetPColgp_HArray2OfPntmyUpperCol(PColgp_HArray2OfPntmyUpperCol);

    ShapeSchema_PColgp_FieldOfHArray2OfPnt::SRead((PColgp_FieldOfHArray2OfPnt&)pp->_CSFDB_GetPColgp_HArray2OfPntData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray2OfPnt::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_HArray2OfPnt::SRead(p,f,theSchema);
}
