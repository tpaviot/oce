#ifndef _ShapeSchema_PColStd_HArray1OfReal_HeaderFile
#include <ShapeSchema_PColStd_HArray1OfReal.hxx>
#endif
#ifndef _PColStd_HArray1OfReal_HeaderFile
#include <PColStd_HArray1OfReal.hxx>
#endif
#include <ShapeSchema_PColStd_HArray1OfReal.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColStd_HArray1OfReal,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColStd_HArray1OfReal,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColStd_HArray1OfReal::New() const
{
  return new PColStd_HArray1OfReal(Storage_stCONSTclCOM());
}

void ShapeSchema_PColStd_HArray1OfReal::SAdd(const Handle(PColStd_HArray1OfReal)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColStd_HArray1OfReal")) {
      
    }
  }
}

void ShapeSchema_PColStd_HArray1OfReal::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColStd_HArray1OfReal::SAdd((Handle(PColStd_HArray1OfReal)&)p,theSchema);
}

void ShapeSchema_PColStd_HArray1OfReal::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColStd_HArray1OfReal) &pp = (Handle(PColStd_HArray1OfReal)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColStd_HArray1OfRealLowerBound());
  f.PutInteger(pp->_CSFDB_GetPColStd_HArray1OfRealUpperBound());
    ShapeSchema_PColStd_FieldOfHArray1OfReal::SWrite(pp->_CSFDB_GetPColStd_HArray1OfRealData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColStd_HArray1OfReal::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColStd_HArray1OfReal::SWrite(p,f,theSchema);
}


void ShapeSchema_PColStd_HArray1OfReal::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColStd_HArray1OfReal) &pp = (Handle(PColStd_HArray1OfReal)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColStd_HArray1OfRealLowerBound;
    f.GetInteger(PColStd_HArray1OfRealLowerBound);
    pp->_CSFDB_SetPColStd_HArray1OfRealLowerBound(PColStd_HArray1OfRealLowerBound);

    Standard_Integer PColStd_HArray1OfRealUpperBound;
    f.GetInteger(PColStd_HArray1OfRealUpperBound);
    pp->_CSFDB_SetPColStd_HArray1OfRealUpperBound(PColStd_HArray1OfRealUpperBound);

    ShapeSchema_PColStd_FieldOfHArray1OfReal::SRead((PColStd_FieldOfHArray1OfReal&)pp->_CSFDB_GetPColStd_HArray1OfRealData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColStd_HArray1OfReal::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColStd_HArray1OfReal::SRead(p,f,theSchema);
}
