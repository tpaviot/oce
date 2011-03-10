#ifndef _StdLSchema_PDataStd_Expression_HeaderFile
#include <StdLSchema_PDataStd_Expression.hxx>
#endif
#ifndef _PDataStd_Expression_HeaderFile
#include <PDataStd_Expression.hxx>
#endif
#include <StdLSchema_PDataStd_Expression.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_Expression,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_Expression,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_Expression::New() const
{
  return new PDataStd_Expression(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_Expression::SAdd(const Handle(PDataStd_Expression)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_Expression")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_ExpressionmyName());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_ExpressionmyVariables());

    }
  }
}

void StdLSchema_PDataStd_Expression::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_Expression::SAdd((Handle(PDataStd_Expression)&)p,theSchema);
}

void StdLSchema_PDataStd_Expression::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_Expression) &pp = (Handle(PDataStd_Expression)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_ExpressionmyName(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_ExpressionmyVariables(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_Expression::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_Expression::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_Expression::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_Expression) &pp = (Handle(PDataStd_Expression)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PCollection_HExtendedString) PDataStd_ExpressionmyName;

    theSchema->ReadPersistentReference(PDataStd_ExpressionmyName,f);
    pp->_CSFDB_SetPDataStd_ExpressionmyName(PDataStd_ExpressionmyName);

    Handle(PDF_HAttributeArray1) PDataStd_ExpressionmyVariables;

    theSchema->ReadPersistentReference(PDataStd_ExpressionmyVariables,f);
    pp->_CSFDB_SetPDataStd_ExpressionmyVariables(PDataStd_ExpressionmyVariables);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_Expression::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_Expression::SRead(p,f,theSchema);
}
