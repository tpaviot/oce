#ifndef _StdLSchema_PDataStd_Variable_HeaderFile
#include <StdLSchema_PDataStd_Variable.hxx>
#endif
#ifndef _PDataStd_Variable_HeaderFile
#include <PDataStd_Variable.hxx>
#endif
#include <StdLSchema_PDataStd_Variable.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_Variable,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_Variable,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_Variable::New() const
{
  return new PDataStd_Variable(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_Variable::SAdd(const Handle(PDataStd_Variable)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_Variable")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_VariablemyUnit());

    }
  }
}

void StdLSchema_PDataStd_Variable::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_Variable::SAdd((Handle(PDataStd_Variable)&)p,theSchema);
}

void StdLSchema_PDataStd_Variable::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_Variable) &pp = (Handle(PDataStd_Variable)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutBoolean(pp->_CSFDB_GetPDataStd_VariableisConstant());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_VariablemyUnit(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_Variable::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_Variable::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_Variable::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_Variable) &pp = (Handle(PDataStd_Variable)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Boolean PDataStd_VariableisConstant;
    f.GetBoolean(PDataStd_VariableisConstant);
    pp->_CSFDB_SetPDataStd_VariableisConstant(PDataStd_VariableisConstant);

    Handle(PCollection_HAsciiString) PDataStd_VariablemyUnit;

    theSchema->ReadPersistentReference(PDataStd_VariablemyUnit,f);
    pp->_CSFDB_SetPDataStd_VariablemyUnit(PDataStd_VariablemyUnit);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_Variable::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_Variable::SRead(p,f,theSchema);
}
