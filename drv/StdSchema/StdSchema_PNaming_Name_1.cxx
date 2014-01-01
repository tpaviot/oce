#ifndef _StdSchema_PNaming_Name_1_HeaderFile
#include <StdSchema_PNaming_Name_1.hxx>
#endif
#ifndef _PNaming_Name_1_HeaderFile
#include <PNaming_Name_1.hxx>
#endif
#include <StdSchema_PNaming_Name_1.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PNaming_Name_1,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PNaming_Name_1,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PNaming_Name_1::New() const
{
  return new PNaming_Name_1(Storage_stCONSTclCOM());
}

void StdSchema_PNaming_Name_1::SAdd(const Handle(PNaming_Name_1)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PNaming_Name_1")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPNaming_Name_1myArgs());
   theSchema->PersistentToAdd(p->_CSFDB_GetPNaming_Name_1myStop());
   theSchema->PersistentToAdd(p->_CSFDB_GetPNaming_Name_1myContextLabel());

    }
  }
}

void StdSchema_PNaming_Name_1::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PNaming_Name_1::SAdd((Handle(PNaming_Name_1)&)p,theSchema);
}

void StdSchema_PNaming_Name_1::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PNaming_Name_1) &pp = (Handle(PNaming_Name_1)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPNaming_Name_1myType());
  f.PutInteger(pp->_CSFDB_GetPNaming_Name_1myShapeType());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPNaming_Name_1myArgs(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPNaming_Name_1myStop(),f);
  f.PutInteger(pp->_CSFDB_GetPNaming_Name_1myIndex());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPNaming_Name_1myContextLabel(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PNaming_Name_1::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PNaming_Name_1::SWrite(p,f,theSchema);
}


void StdSchema_PNaming_Name_1::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PNaming_Name_1) &pp = (Handle(PNaming_Name_1)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PNaming_Name_1myType;
    f.GetInteger(PNaming_Name_1myType);
    pp->_CSFDB_SetPNaming_Name_1myType(PNaming_Name_1myType);

    Standard_Integer PNaming_Name_1myShapeType;
    f.GetInteger(PNaming_Name_1myShapeType);
    pp->_CSFDB_SetPNaming_Name_1myShapeType(PNaming_Name_1myShapeType);

    Handle(PNaming_HArray1OfNamedShape) PNaming_Name_1myArgs;

    theSchema->ReadPersistentReference(PNaming_Name_1myArgs,f);
    pp->_CSFDB_SetPNaming_Name_1myArgs(PNaming_Name_1myArgs);

    Handle(PNaming_NamedShape) PNaming_Name_1myStop;

    theSchema->ReadPersistentReference(PNaming_Name_1myStop,f);
    pp->_CSFDB_SetPNaming_Name_1myStop(PNaming_Name_1myStop);

    Standard_Integer PNaming_Name_1myIndex;
    f.GetInteger(PNaming_Name_1myIndex);
    pp->_CSFDB_SetPNaming_Name_1myIndex(PNaming_Name_1myIndex);

    Handle(PCollection_HAsciiString) PNaming_Name_1myContextLabel;

    theSchema->ReadPersistentReference(PNaming_Name_1myContextLabel,f);
    pp->_CSFDB_SetPNaming_Name_1myContextLabel(PNaming_Name_1myContextLabel);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PNaming_Name_1::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PNaming_Name_1::SRead(p,f,theSchema);
}
