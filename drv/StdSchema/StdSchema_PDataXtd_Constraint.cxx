#ifndef _StdSchema_PDataXtd_Constraint_HeaderFile
#include <StdSchema_PDataXtd_Constraint.hxx>
#endif
#ifndef _PDataXtd_Constraint_HeaderFile
#include <PDataXtd_Constraint.hxx>
#endif
#include <StdSchema_PDataXtd_Constraint.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PDataXtd_Constraint,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PDataXtd_Constraint,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PDataXtd_Constraint::New() const
{
  return new PDataXtd_Constraint(Storage_stCONSTclCOM());
}

void StdSchema_PDataXtd_Constraint::SAdd(const Handle(PDataXtd_Constraint)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataXtd_Constraint")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataXtd_ConstraintmyGeometries());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataXtd_ConstraintmyValue());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataXtd_ConstraintmyPlane());

    }
  }
}

void StdSchema_PDataXtd_Constraint::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PDataXtd_Constraint::SAdd((Handle(PDataXtd_Constraint)&)p,theSchema);
}

void StdSchema_PDataXtd_Constraint::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataXtd_Constraint) &pp = (Handle(PDataXtd_Constraint)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPDataXtd_ConstraintmyType());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataXtd_ConstraintmyGeometries(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataXtd_ConstraintmyValue(),f);
  f.PutBoolean(pp->_CSFDB_GetPDataXtd_ConstraintmyIsReversed());
  f.PutBoolean(pp->_CSFDB_GetPDataXtd_ConstraintmyIsInverted());
  f.PutBoolean(pp->_CSFDB_GetPDataXtd_ConstraintmyIsVerified());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataXtd_ConstraintmyPlane(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PDataXtd_Constraint::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PDataXtd_Constraint::SWrite(p,f,theSchema);
}


void StdSchema_PDataXtd_Constraint::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataXtd_Constraint) &pp = (Handle(PDataXtd_Constraint)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PDataXtd_ConstraintmyType;
    f.GetInteger(PDataXtd_ConstraintmyType);
    pp->_CSFDB_SetPDataXtd_ConstraintmyType(PDataXtd_ConstraintmyType);

    Handle(PDF_HAttributeArray1) PDataXtd_ConstraintmyGeometries;

    theSchema->ReadPersistentReference(PDataXtd_ConstraintmyGeometries,f);
    pp->_CSFDB_SetPDataXtd_ConstraintmyGeometries(PDataXtd_ConstraintmyGeometries);

    Handle(PDataStd_Real) PDataXtd_ConstraintmyValue;

    theSchema->ReadPersistentReference(PDataXtd_ConstraintmyValue,f);
    pp->_CSFDB_SetPDataXtd_ConstraintmyValue(PDataXtd_ConstraintmyValue);

    Standard_Boolean PDataXtd_ConstraintmyIsReversed;
    f.GetBoolean(PDataXtd_ConstraintmyIsReversed);
    pp->_CSFDB_SetPDataXtd_ConstraintmyIsReversed(PDataXtd_ConstraintmyIsReversed);

    Standard_Boolean PDataXtd_ConstraintmyIsInverted;
    f.GetBoolean(PDataXtd_ConstraintmyIsInverted);
    pp->_CSFDB_SetPDataXtd_ConstraintmyIsInverted(PDataXtd_ConstraintmyIsInverted);

    Standard_Boolean PDataXtd_ConstraintmyIsVerified;
    f.GetBoolean(PDataXtd_ConstraintmyIsVerified);
    pp->_CSFDB_SetPDataXtd_ConstraintmyIsVerified(PDataXtd_ConstraintmyIsVerified);

    Handle(PNaming_NamedShape) PDataXtd_ConstraintmyPlane;

    theSchema->ReadPersistentReference(PDataXtd_ConstraintmyPlane,f);
    pp->_CSFDB_SetPDataXtd_ConstraintmyPlane(PDataXtd_ConstraintmyPlane);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PDataXtd_Constraint::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PDataXtd_Constraint::SRead(p,f,theSchema);
}
