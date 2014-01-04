#ifndef _StdLSchema_PDataStd_HArray1OfHArray1OfReal_HeaderFile
#include <StdLSchema_PDataStd_HArray1OfHArray1OfReal.hxx>
#endif
#ifndef _PDataStd_HArray1OfHArray1OfReal_HeaderFile
#include <PDataStd_HArray1OfHArray1OfReal.hxx>
#endif
#include <StdLSchema_PDataStd_HArray1OfHArray1OfReal.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_HArray1OfHArray1OfReal,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_HArray1OfHArray1OfReal,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_HArray1OfHArray1OfReal::New() const
{
  return new PDataStd_HArray1OfHArray1OfReal(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_HArray1OfHArray1OfReal::SAdd(const Handle(PDataStd_HArray1OfHArray1OfReal)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_HArray1OfHArray1OfReal")) {
         StdLSchema_PDataStd_FieldOfHArray1OfHArray1OfReal::SAdd(p->_CSFDB_GetPDataStd_HArray1OfHArray1OfRealData(),theSchema);

    }
  }
}

void StdLSchema_PDataStd_HArray1OfHArray1OfReal::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_HArray1OfHArray1OfReal::SAdd((Handle(PDataStd_HArray1OfHArray1OfReal)&)p,theSchema);
}

void StdLSchema_PDataStd_HArray1OfHArray1OfReal::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_HArray1OfHArray1OfReal) &pp = (Handle(PDataStd_HArray1OfHArray1OfReal)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPDataStd_HArray1OfHArray1OfRealLowerBound());
  f.PutInteger(pp->_CSFDB_GetPDataStd_HArray1OfHArray1OfRealUpperBound());
    StdLSchema_PDataStd_FieldOfHArray1OfHArray1OfReal::SWrite(pp->_CSFDB_GetPDataStd_HArray1OfHArray1OfRealData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_HArray1OfHArray1OfReal::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_HArray1OfHArray1OfReal::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_HArray1OfHArray1OfReal::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_HArray1OfHArray1OfReal) &pp = (Handle(PDataStd_HArray1OfHArray1OfReal)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PDataStd_HArray1OfHArray1OfRealLowerBound;
    f.GetInteger(PDataStd_HArray1OfHArray1OfRealLowerBound);
    pp->_CSFDB_SetPDataStd_HArray1OfHArray1OfRealLowerBound(PDataStd_HArray1OfHArray1OfRealLowerBound);

    Standard_Integer PDataStd_HArray1OfHArray1OfRealUpperBound;
    f.GetInteger(PDataStd_HArray1OfHArray1OfRealUpperBound);
    pp->_CSFDB_SetPDataStd_HArray1OfHArray1OfRealUpperBound(PDataStd_HArray1OfHArray1OfRealUpperBound);

    StdLSchema_PDataStd_FieldOfHArray1OfHArray1OfReal::SRead((PDataStd_FieldOfHArray1OfHArray1OfReal&)pp->_CSFDB_GetPDataStd_HArray1OfHArray1OfRealData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_HArray1OfHArray1OfReal::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_HArray1OfHArray1OfReal::SRead(p,f,theSchema);
}
