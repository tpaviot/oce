#ifndef _StdLSchema_PFunction_Function_HeaderFile
#include <StdLSchema_PFunction_Function.hxx>
#endif
#ifndef _PFunction_Function_HeaderFile
#include <PFunction_Function.hxx>
#endif
#include <StdLSchema_PFunction_Function.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PFunction_Function,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PFunction_Function,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PFunction_Function::New() const
{
  return new PFunction_Function(Storage_stCONSTclCOM());
}

void StdLSchema_PFunction_Function::SAdd(const Handle(PFunction_Function)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PFunction_Function")) {
      
    }
  }
}

void StdLSchema_PFunction_Function::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PFunction_Function::SAdd((Handle(PFunction_Function)&)p,theSchema);
}

void StdLSchema_PFunction_Function::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PFunction_Function) &pp = (Handle(PFunction_Function)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    StdLSchema_Standard_GUID::SWrite(pp->_CSFDB_GetPFunction_FunctionmyDriverGUID(),f,theSchema);
  f.PutInteger(pp->_CSFDB_GetPFunction_FunctionmyFailure());

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PFunction_Function::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PFunction_Function::SWrite(p,f,theSchema);
}


void StdLSchema_PFunction_Function::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PFunction_Function) &pp = (Handle(PFunction_Function)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    StdLSchema_Standard_GUID::SRead((Standard_GUID&)pp->_CSFDB_GetPFunction_FunctionmyDriverGUID(),f,theSchema);

    Standard_Integer PFunction_FunctionmyFailure;
    f.GetInteger(PFunction_FunctionmyFailure);
    pp->_CSFDB_SetPFunction_FunctionmyFailure(PFunction_FunctionmyFailure);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PFunction_Function::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PFunction_Function::SRead(p,f,theSchema);
}
