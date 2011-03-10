#ifndef _ShapeSchema_PColStd_HArray2OfReal_HeaderFile
#include <ShapeSchema_PColStd_HArray2OfReal.hxx>
#endif
#ifndef _PColStd_HArray2OfReal_HeaderFile
#include <PColStd_HArray2OfReal.hxx>
#endif
#include <ShapeSchema_PColStd_HArray2OfReal.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColStd_HArray2OfReal,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColStd_HArray2OfReal,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColStd_HArray2OfReal::New() const
{
  return new PColStd_HArray2OfReal(Storage_stCONSTclCOM());
}

void ShapeSchema_PColStd_HArray2OfReal::SAdd(const Handle(PColStd_HArray2OfReal)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColStd_HArray2OfReal")) {
      
    }
  }
}

void ShapeSchema_PColStd_HArray2OfReal::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColStd_HArray2OfReal::SAdd((Handle(PColStd_HArray2OfReal)&)p,theSchema);
}

void ShapeSchema_PColStd_HArray2OfReal::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColStd_HArray2OfReal) &pp = (Handle(PColStd_HArray2OfReal)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColStd_HArray2OfRealmyLowerRow());
  f.PutInteger(pp->_CSFDB_GetPColStd_HArray2OfRealmyLowerCol());
  f.PutInteger(pp->_CSFDB_GetPColStd_HArray2OfRealmyUpperRow());
  f.PutInteger(pp->_CSFDB_GetPColStd_HArray2OfRealmyUpperCol());
    ShapeSchema_PColStd_FieldOfHArray2OfReal::SWrite(pp->_CSFDB_GetPColStd_HArray2OfRealData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColStd_HArray2OfReal::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColStd_HArray2OfReal::SWrite(p,f,theSchema);
}


void ShapeSchema_PColStd_HArray2OfReal::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColStd_HArray2OfReal) &pp = (Handle(PColStd_HArray2OfReal)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColStd_HArray2OfRealmyLowerRow;
    f.GetInteger(PColStd_HArray2OfRealmyLowerRow);
    pp->_CSFDB_SetPColStd_HArray2OfRealmyLowerRow(PColStd_HArray2OfRealmyLowerRow);

    Standard_Integer PColStd_HArray2OfRealmyLowerCol;
    f.GetInteger(PColStd_HArray2OfRealmyLowerCol);
    pp->_CSFDB_SetPColStd_HArray2OfRealmyLowerCol(PColStd_HArray2OfRealmyLowerCol);

    Standard_Integer PColStd_HArray2OfRealmyUpperRow;
    f.GetInteger(PColStd_HArray2OfRealmyUpperRow);
    pp->_CSFDB_SetPColStd_HArray2OfRealmyUpperRow(PColStd_HArray2OfRealmyUpperRow);

    Standard_Integer PColStd_HArray2OfRealmyUpperCol;
    f.GetInteger(PColStd_HArray2OfRealmyUpperCol);
    pp->_CSFDB_SetPColStd_HArray2OfRealmyUpperCol(PColStd_HArray2OfRealmyUpperCol);

    ShapeSchema_PColStd_FieldOfHArray2OfReal::SRead((PColStd_FieldOfHArray2OfReal&)pp->_CSFDB_GetPColStd_HArray2OfRealData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColStd_HArray2OfReal::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColStd_HArray2OfReal::SRead(p,f,theSchema);
}
