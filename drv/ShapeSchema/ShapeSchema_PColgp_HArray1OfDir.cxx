#ifndef _ShapeSchema_PColgp_HArray1OfDir_HeaderFile
#include <ShapeSchema_PColgp_HArray1OfDir.hxx>
#endif
#ifndef _PColgp_HArray1OfDir_HeaderFile
#include <PColgp_HArray1OfDir.hxx>
#endif
#include <ShapeSchema_PColgp_HArray1OfDir.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_HArray1OfDir,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_HArray1OfDir,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_HArray1OfDir::New() const
{
  return new PColgp_HArray1OfDir(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_HArray1OfDir::SAdd(const Handle(PColgp_HArray1OfDir)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_HArray1OfDir")) {
      
    }
  }
}

void ShapeSchema_PColgp_HArray1OfDir::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_HArray1OfDir::SAdd((Handle(PColgp_HArray1OfDir)&)p,theSchema);
}

void ShapeSchema_PColgp_HArray1OfDir::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray1OfDir) &pp = (Handle(PColgp_HArray1OfDir)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray1OfDirLowerBound());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray1OfDirUpperBound());
    ShapeSchema_PColgp_FieldOfHArray1OfDir::SWrite(pp->_CSFDB_GetPColgp_HArray1OfDirData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray1OfDir::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_HArray1OfDir::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_HArray1OfDir::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray1OfDir) &pp = (Handle(PColgp_HArray1OfDir)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColgp_HArray1OfDirLowerBound;
    f.GetInteger(PColgp_HArray1OfDirLowerBound);
    pp->_CSFDB_SetPColgp_HArray1OfDirLowerBound(PColgp_HArray1OfDirLowerBound);

    Standard_Integer PColgp_HArray1OfDirUpperBound;
    f.GetInteger(PColgp_HArray1OfDirUpperBound);
    pp->_CSFDB_SetPColgp_HArray1OfDirUpperBound(PColgp_HArray1OfDirUpperBound);

    ShapeSchema_PColgp_FieldOfHArray1OfDir::SRead((PColgp_FieldOfHArray1OfDir&)pp->_CSFDB_GetPColgp_HArray1OfDirData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray1OfDir::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_HArray1OfDir::SRead(p,f,theSchema);
}
