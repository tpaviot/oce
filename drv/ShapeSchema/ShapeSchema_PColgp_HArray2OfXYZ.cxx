#ifndef _ShapeSchema_PColgp_HArray2OfXYZ_HeaderFile
#include <ShapeSchema_PColgp_HArray2OfXYZ.hxx>
#endif
#ifndef _PColgp_HArray2OfXYZ_HeaderFile
#include <PColgp_HArray2OfXYZ.hxx>
#endif
#include <ShapeSchema_PColgp_HArray2OfXYZ.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_HArray2OfXYZ,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_HArray2OfXYZ,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_HArray2OfXYZ::New() const
{
  return new PColgp_HArray2OfXYZ(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_HArray2OfXYZ::SAdd(const Handle(PColgp_HArray2OfXYZ)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_HArray2OfXYZ")) {
      
    }
  }
}

void ShapeSchema_PColgp_HArray2OfXYZ::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_HArray2OfXYZ::SAdd((Handle(PColgp_HArray2OfXYZ)&)p,theSchema);
}

void ShapeSchema_PColgp_HArray2OfXYZ::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray2OfXYZ) &pp = (Handle(PColgp_HArray2OfXYZ)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfXYZmyLowerRow());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfXYZmyLowerCol());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfXYZmyUpperRow());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray2OfXYZmyUpperCol());
    ShapeSchema_PColgp_FieldOfHArray2OfXYZ::SWrite(pp->_CSFDB_GetPColgp_HArray2OfXYZData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray2OfXYZ::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_HArray2OfXYZ::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_HArray2OfXYZ::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray2OfXYZ) &pp = (Handle(PColgp_HArray2OfXYZ)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColgp_HArray2OfXYZmyLowerRow;
    f.GetInteger(PColgp_HArray2OfXYZmyLowerRow);
    pp->_CSFDB_SetPColgp_HArray2OfXYZmyLowerRow(PColgp_HArray2OfXYZmyLowerRow);

    Standard_Integer PColgp_HArray2OfXYZmyLowerCol;
    f.GetInteger(PColgp_HArray2OfXYZmyLowerCol);
    pp->_CSFDB_SetPColgp_HArray2OfXYZmyLowerCol(PColgp_HArray2OfXYZmyLowerCol);

    Standard_Integer PColgp_HArray2OfXYZmyUpperRow;
    f.GetInteger(PColgp_HArray2OfXYZmyUpperRow);
    pp->_CSFDB_SetPColgp_HArray2OfXYZmyUpperRow(PColgp_HArray2OfXYZmyUpperRow);

    Standard_Integer PColgp_HArray2OfXYZmyUpperCol;
    f.GetInteger(PColgp_HArray2OfXYZmyUpperCol);
    pp->_CSFDB_SetPColgp_HArray2OfXYZmyUpperCol(PColgp_HArray2OfXYZmyUpperCol);

    ShapeSchema_PColgp_FieldOfHArray2OfXYZ::SRead((PColgp_FieldOfHArray2OfXYZ&)pp->_CSFDB_GetPColgp_HArray2OfXYZData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray2OfXYZ::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_HArray2OfXYZ::SRead(p,f,theSchema);
}
