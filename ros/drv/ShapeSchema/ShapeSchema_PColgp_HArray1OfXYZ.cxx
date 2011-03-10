#ifndef _ShapeSchema_PColgp_HArray1OfXYZ_HeaderFile
#include <ShapeSchema_PColgp_HArray1OfXYZ.hxx>
#endif
#ifndef _PColgp_HArray1OfXYZ_HeaderFile
#include <PColgp_HArray1OfXYZ.hxx>
#endif
#include <ShapeSchema_PColgp_HArray1OfXYZ.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_HArray1OfXYZ,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_HArray1OfXYZ,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_HArray1OfXYZ::New() const
{
  return new PColgp_HArray1OfXYZ(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_HArray1OfXYZ::SAdd(const Handle(PColgp_HArray1OfXYZ)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_HArray1OfXYZ")) {
      
    }
  }
}

void ShapeSchema_PColgp_HArray1OfXYZ::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_HArray1OfXYZ::SAdd((Handle(PColgp_HArray1OfXYZ)&)p,theSchema);
}

void ShapeSchema_PColgp_HArray1OfXYZ::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray1OfXYZ) &pp = (Handle(PColgp_HArray1OfXYZ)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray1OfXYZLowerBound());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray1OfXYZUpperBound());
    ShapeSchema_PColgp_FieldOfHArray1OfXYZ::SWrite(pp->_CSFDB_GetPColgp_HArray1OfXYZData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray1OfXYZ::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_HArray1OfXYZ::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_HArray1OfXYZ::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray1OfXYZ) &pp = (Handle(PColgp_HArray1OfXYZ)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColgp_HArray1OfXYZLowerBound;
    f.GetInteger(PColgp_HArray1OfXYZLowerBound);
    pp->_CSFDB_SetPColgp_HArray1OfXYZLowerBound(PColgp_HArray1OfXYZLowerBound);

    Standard_Integer PColgp_HArray1OfXYZUpperBound;
    f.GetInteger(PColgp_HArray1OfXYZUpperBound);
    pp->_CSFDB_SetPColgp_HArray1OfXYZUpperBound(PColgp_HArray1OfXYZUpperBound);

    ShapeSchema_PColgp_FieldOfHArray1OfXYZ::SRead((PColgp_FieldOfHArray1OfXYZ&)pp->_CSFDB_GetPColgp_HArray1OfXYZData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray1OfXYZ::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_HArray1OfXYZ::SRead(p,f,theSchema);
}
