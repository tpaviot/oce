#ifndef _ShapeSchema_PColgp_HArray2OfCirc2d_HeaderFile
#include <ShapeSchema_PColgp_HArray2OfCirc2d.hxx>
#endif
#ifndef _PColgp_HArray2OfCirc2d_HeaderFile
#include <PColgp_HArray2OfCirc2d.hxx>
#endif
#include <ShapeSchema_PColgp_HArray2OfCirc2d.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_HArray2OfCirc2d,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_HArray2OfCirc2d,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_HArray2OfCirc2d::New() const
{
  return new PColgp_HArray2OfCirc2d(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_HArray2OfCirc2d::SAdd(const Handle(PColgp_HArray2OfCirc2d)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_HArray2OfCirc2d")) {
      
    }
  }
}

void ShapeSchema_PColgp_HArray2OfCirc2d::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_HArray2OfCirc2d::SAdd((Handle(PColgp_HArray2OfCirc2d)&)p,theSchema);
}

void ShapeSchema_PColgp_HArray2OfCirc2d::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray2OfCirc2d) &pp = (Handle(PColgp_HArray2OfCirc2d)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfCirc2dmyLowerRow());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfCirc2dmyLowerCol());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfCirc2dmyUpperRow());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfCirc2dmyUpperCol());
    ShapeSchema_PColgp_FieldOfHArray2OfCirc2d::SWrite(pp->_CSFDB_GetPColgp_HArray2OfCirc2dData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray2OfCirc2d::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_HArray2OfCirc2d::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_HArray2OfCirc2d::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray2OfCirc2d) &pp = (Handle(PColgp_HArray2OfCirc2d)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColgp_HArray2OfCirc2dmyLowerRow;
    f.GetInteger(PColgp_HArray2OfCirc2dmyLowerRow);
    pp->_CSFDB_SetPColgp_HArray2OfCirc2dmyLowerRow(PColgp_HArray2OfCirc2dmyLowerRow);

    Standard_Integer PColgp_HArray2OfCirc2dmyLowerCol;
    f.GetInteger(PColgp_HArray2OfCirc2dmyLowerCol);
    pp->_CSFDB_SetPColgp_HArray2OfCirc2dmyLowerCol(PColgp_HArray2OfCirc2dmyLowerCol);

    Standard_Integer PColgp_HArray2OfCirc2dmyUpperRow;
    f.GetInteger(PColgp_HArray2OfCirc2dmyUpperRow);
    pp->_CSFDB_SetPColgp_HArray2OfCirc2dmyUpperRow(PColgp_HArray2OfCirc2dmyUpperRow);

    Standard_Integer PColgp_HArray2OfCirc2dmyUpperCol;
    f.GetInteger(PColgp_HArray2OfCirc2dmyUpperCol);
    pp->_CSFDB_SetPColgp_HArray2OfCirc2dmyUpperCol(PColgp_HArray2OfCirc2dmyUpperCol);

    ShapeSchema_PColgp_FieldOfHArray2OfCirc2d::SRead((PColgp_FieldOfHArray2OfCirc2d&)pp->_CSFDB_GetPColgp_HArray2OfCirc2dData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray2OfCirc2d::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_HArray2OfCirc2d::SRead(p,f,theSchema);
}
