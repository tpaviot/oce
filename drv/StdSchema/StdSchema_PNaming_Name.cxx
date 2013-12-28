#ifndef _StdSchema_PNaming_Name_HeaderFile
#include <StdSchema_PNaming_Name.hxx>
#endif
#ifndef _PNaming_Name_HeaderFile
#include <PNaming_Name.hxx>
#endif
#include <StdSchema_PNaming_Name.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PNaming_Name,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PNaming_Name,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PNaming_Name::New() const
{
  return new PNaming_Name(Storage_stCONSTclCOM());
}

void StdSchema_PNaming_Name::SAdd(const Handle(PNaming_Name)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PNaming_Name")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPNaming_NamemyArgs());
   theSchema->PersistentToAdd(p->_CSFDB_GetPNaming_NamemyStop());

    }
  }
}

void StdSchema_PNaming_Name::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PNaming_Name::SAdd((Handle(PNaming_Name)&)p,theSchema);
}

void StdSchema_PNaming_Name::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PNaming_Name) &pp = (Handle(PNaming_Name)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPNaming_NamemyType());
  f.PutInteger(pp->_CSFDB_GetPNaming_NamemyShapeType());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPNaming_NamemyArgs(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPNaming_NamemyStop(),f);
  f.PutInteger(pp->_CSFDB_GetPNaming_NamemyIndex());

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PNaming_Name::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PNaming_Name::SWrite(p,f,theSchema);
}


void StdSchema_PNaming_Name::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PNaming_Name) &pp = (Handle(PNaming_Name)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PNaming_NamemyType;
    f.GetInteger(PNaming_NamemyType);
    pp->_CSFDB_SetPNaming_NamemyType(PNaming_NamemyType);

    Standard_Integer PNaming_NamemyShapeType;
    f.GetInteger(PNaming_NamemyShapeType);
    pp->_CSFDB_SetPNaming_NamemyShapeType(PNaming_NamemyShapeType);

    Handle(PNaming_HArray1OfNamedShape) PNaming_NamemyArgs;

    theSchema->ReadPersistentReference(PNaming_NamemyArgs,f);
    pp->_CSFDB_SetPNaming_NamemyArgs(PNaming_NamemyArgs);

    Handle(PNaming_NamedShape) PNaming_NamemyStop;

    theSchema->ReadPersistentReference(PNaming_NamemyStop,f);
    pp->_CSFDB_SetPNaming_NamemyStop(PNaming_NamemyStop);

    Standard_Integer PNaming_NamemyIndex;
    f.GetInteger(PNaming_NamemyIndex);
    pp->_CSFDB_SetPNaming_NamemyIndex(PNaming_NamemyIndex);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PNaming_Name::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PNaming_Name::SRead(p,f,theSchema);
}
