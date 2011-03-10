#ifndef _StdSchema_PDataXtd_Position_HeaderFile
#include <StdSchema_PDataXtd_Position.hxx>
#endif
#ifndef _PDataXtd_Position_HeaderFile
#include <PDataXtd_Position.hxx>
#endif
#include <StdSchema_PDataXtd_Position.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PDataXtd_Position,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PDataXtd_Position,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PDataXtd_Position::New() const
{
  return new PDataXtd_Position(Storage_stCONSTclCOM());
}

void StdSchema_PDataXtd_Position::SAdd(const Handle(PDataXtd_Position)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataXtd_Position")) {
      
    }
  }
}

void StdSchema_PDataXtd_Position::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PDataXtd_Position::SAdd((Handle(PDataXtd_Position)&)p,theSchema);
}

void StdSchema_PDataXtd_Position::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataXtd_Position) &pp = (Handle(PDataXtd_Position)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    StdSchema_gp_Pnt::SWrite(pp->_CSFDB_GetPDataXtd_PositionmyPosition(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PDataXtd_Position::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PDataXtd_Position::SWrite(p,f,theSchema);
}


void StdSchema_PDataXtd_Position::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataXtd_Position) &pp = (Handle(PDataXtd_Position)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    StdSchema_gp_Pnt::SRead((gp_Pnt&)pp->_CSFDB_GetPDataXtd_PositionmyPosition(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PDataXtd_Position::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PDataXtd_Position::SRead(p,f,theSchema);
}
