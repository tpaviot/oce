#ifndef _StdSchema_PNaming_Name_2_HeaderFile
#include <StdSchema_PNaming_Name_2.hxx>
#endif
#ifndef _PNaming_Name_2_HeaderFile
#include <PNaming_Name_2.hxx>
#endif
#include <StdSchema_PNaming_Name_2.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PNaming_Name_2,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PNaming_Name_2,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PNaming_Name_2::New() const
{
  return new PNaming_Name_2(Storage_stCONSTclCOM());
}

void StdSchema_PNaming_Name_2::SAdd(const Handle(PNaming_Name_2)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PNaming_Name_2")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPNaming_Name_2myArgs());
   theSchema->PersistentToAdd(p->_CSFDB_GetPNaming_Name_2myStop());
   theSchema->PersistentToAdd(p->_CSFDB_GetPNaming_Name_2myContextLabel());

    }
  }
}

void StdSchema_PNaming_Name_2::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PNaming_Name_2::SAdd((Handle(PNaming_Name_2)&)p,theSchema);
}

void StdSchema_PNaming_Name_2::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PNaming_Name_2) &pp = (Handle(PNaming_Name_2)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPNaming_Name_2myType());
  f.PutInteger(pp->_CSFDB_GetPNaming_Name_2myShapeType());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPNaming_Name_2myArgs(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPNaming_Name_2myStop(),f);
  f.PutInteger(pp->_CSFDB_GetPNaming_Name_2myIndex());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPNaming_Name_2myContextLabel(),f);
  f.PutInteger(pp->_CSFDB_GetPNaming_Name_2myOrientation());

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PNaming_Name_2::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PNaming_Name_2::SWrite(p,f,theSchema);
}


void StdSchema_PNaming_Name_2::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PNaming_Name_2) &pp = (Handle(PNaming_Name_2)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PNaming_Name_2myType;
    f.GetInteger(PNaming_Name_2myType);
    pp->_CSFDB_SetPNaming_Name_2myType(PNaming_Name_2myType);

    Standard_Integer PNaming_Name_2myShapeType;
    f.GetInteger(PNaming_Name_2myShapeType);
    pp->_CSFDB_SetPNaming_Name_2myShapeType(PNaming_Name_2myShapeType);

    Handle(PNaming_HArray1OfNamedShape) PNaming_Name_2myArgs;

    theSchema->ReadPersistentReference(PNaming_Name_2myArgs,f);
    pp->_CSFDB_SetPNaming_Name_2myArgs(PNaming_Name_2myArgs);

    Handle(PNaming_NamedShape) PNaming_Name_2myStop;

    theSchema->ReadPersistentReference(PNaming_Name_2myStop,f);
    pp->_CSFDB_SetPNaming_Name_2myStop(PNaming_Name_2myStop);

    Standard_Integer PNaming_Name_2myIndex;
    f.GetInteger(PNaming_Name_2myIndex);
    pp->_CSFDB_SetPNaming_Name_2myIndex(PNaming_Name_2myIndex);

    Handle(PCollection_HAsciiString) PNaming_Name_2myContextLabel;

    theSchema->ReadPersistentReference(PNaming_Name_2myContextLabel,f);
    pp->_CSFDB_SetPNaming_Name_2myContextLabel(PNaming_Name_2myContextLabel);

    Standard_Integer PNaming_Name_2myOrientation;
    f.GetInteger(PNaming_Name_2myOrientation);
    pp->_CSFDB_SetPNaming_Name_2myOrientation(PNaming_Name_2myOrientation);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PNaming_Name_2::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PNaming_Name_2::SRead(p,f,theSchema);
}
