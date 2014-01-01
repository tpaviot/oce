#ifndef _StdSchema_PDataXtd_PatternStd_HeaderFile
#include <StdSchema_PDataXtd_PatternStd.hxx>
#endif
#ifndef _PDataXtd_PatternStd_HeaderFile
#include <PDataXtd_PatternStd.hxx>
#endif
#include <StdSchema_PDataXtd_PatternStd.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PDataXtd_PatternStd,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PDataXtd_PatternStd,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PDataXtd_PatternStd::New() const
{
  return new PDataXtd_PatternStd(Storage_stCONSTclCOM());
}

void StdSchema_PDataXtd_PatternStd::SAdd(const Handle(PDataXtd_PatternStd)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataXtd_PatternStd")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataXtd_PatternStdmyAxis1());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataXtd_PatternStdmyAxis2());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataXtd_PatternStdmyValue1());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataXtd_PatternStdmyValue2());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataXtd_PatternStdmyNb1());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataXtd_PatternStdmyNb2());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataXtd_PatternStdmyMirror());

    }
  }
}

void StdSchema_PDataXtd_PatternStd::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PDataXtd_PatternStd::SAdd((Handle(PDataXtd_PatternStd)&)p,theSchema);
}

void StdSchema_PDataXtd_PatternStd::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataXtd_PatternStd) &pp = (Handle(PDataXtd_PatternStd)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPDataXtd_PatternStdmySignature());
  f.PutBoolean(pp->_CSFDB_GetPDataXtd_PatternStdmyAxis1Reversed());
  f.PutBoolean(pp->_CSFDB_GetPDataXtd_PatternStdmyAxis2Reversed());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataXtd_PatternStdmyAxis1(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataXtd_PatternStdmyAxis2(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataXtd_PatternStdmyValue1(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataXtd_PatternStdmyValue2(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataXtd_PatternStdmyNb1(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataXtd_PatternStdmyNb2(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataXtd_PatternStdmyMirror(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PDataXtd_PatternStd::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PDataXtd_PatternStd::SWrite(p,f,theSchema);
}


void StdSchema_PDataXtd_PatternStd::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataXtd_PatternStd) &pp = (Handle(PDataXtd_PatternStd)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PDataXtd_PatternStdmySignature;
    f.GetInteger(PDataXtd_PatternStdmySignature);
    pp->_CSFDB_SetPDataXtd_PatternStdmySignature(PDataXtd_PatternStdmySignature);

    Standard_Boolean PDataXtd_PatternStdmyAxis1Reversed;
    f.GetBoolean(PDataXtd_PatternStdmyAxis1Reversed);
    pp->_CSFDB_SetPDataXtd_PatternStdmyAxis1Reversed(PDataXtd_PatternStdmyAxis1Reversed);

    Standard_Boolean PDataXtd_PatternStdmyAxis2Reversed;
    f.GetBoolean(PDataXtd_PatternStdmyAxis2Reversed);
    pp->_CSFDB_SetPDataXtd_PatternStdmyAxis2Reversed(PDataXtd_PatternStdmyAxis2Reversed);

    Handle(PNaming_NamedShape) PDataXtd_PatternStdmyAxis1;

    theSchema->ReadPersistentReference(PDataXtd_PatternStdmyAxis1,f);
    pp->_CSFDB_SetPDataXtd_PatternStdmyAxis1(PDataXtd_PatternStdmyAxis1);

    Handle(PNaming_NamedShape) PDataXtd_PatternStdmyAxis2;

    theSchema->ReadPersistentReference(PDataXtd_PatternStdmyAxis2,f);
    pp->_CSFDB_SetPDataXtd_PatternStdmyAxis2(PDataXtd_PatternStdmyAxis2);

    Handle(PDataStd_Real) PDataXtd_PatternStdmyValue1;

    theSchema->ReadPersistentReference(PDataXtd_PatternStdmyValue1,f);
    pp->_CSFDB_SetPDataXtd_PatternStdmyValue1(PDataXtd_PatternStdmyValue1);

    Handle(PDataStd_Real) PDataXtd_PatternStdmyValue2;

    theSchema->ReadPersistentReference(PDataXtd_PatternStdmyValue2,f);
    pp->_CSFDB_SetPDataXtd_PatternStdmyValue2(PDataXtd_PatternStdmyValue2);

    Handle(PDataStd_Integer) PDataXtd_PatternStdmyNb1;

    theSchema->ReadPersistentReference(PDataXtd_PatternStdmyNb1,f);
    pp->_CSFDB_SetPDataXtd_PatternStdmyNb1(PDataXtd_PatternStdmyNb1);

    Handle(PDataStd_Integer) PDataXtd_PatternStdmyNb2;

    theSchema->ReadPersistentReference(PDataXtd_PatternStdmyNb2,f);
    pp->_CSFDB_SetPDataXtd_PatternStdmyNb2(PDataXtd_PatternStdmyNb2);

    Handle(PNaming_NamedShape) PDataXtd_PatternStdmyMirror;

    theSchema->ReadPersistentReference(PDataXtd_PatternStdmyMirror,f);
    pp->_CSFDB_SetPDataXtd_PatternStdmyMirror(PDataXtd_PatternStdmyMirror);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PDataXtd_PatternStd::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PDataXtd_PatternStd::SRead(p,f,theSchema);
}
