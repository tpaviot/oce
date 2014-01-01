#ifndef _StdSchema_PTopLoc_Datum3D_HeaderFile
#include <StdSchema_PTopLoc_Datum3D.hxx>
#endif
#ifndef _PTopLoc_Datum3D_HeaderFile
#include <PTopLoc_Datum3D.hxx>
#endif
#include <StdSchema_PTopLoc_Datum3D.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PTopLoc_Datum3D,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PTopLoc_Datum3D,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PTopLoc_Datum3D::New() const
{
  return new PTopLoc_Datum3D(Storage_stCONSTclCOM());
}

void StdSchema_PTopLoc_Datum3D::SAdd(const Handle(PTopLoc_Datum3D)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PTopLoc_Datum3D")) {
      
    }
  }
}

void StdSchema_PTopLoc_Datum3D::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PTopLoc_Datum3D::SAdd((Handle(PTopLoc_Datum3D)&)p,theSchema);
}

void StdSchema_PTopLoc_Datum3D::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopLoc_Datum3D) &pp = (Handle(PTopLoc_Datum3D)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    StdSchema_gp_Trsf::SWrite(pp->_CSFDB_GetPTopLoc_Datum3DmyTrsf(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PTopLoc_Datum3D::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PTopLoc_Datum3D::SWrite(p,f,theSchema);
}


void StdSchema_PTopLoc_Datum3D::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopLoc_Datum3D) &pp = (Handle(PTopLoc_Datum3D)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    StdSchema_gp_Trsf::SRead((gp_Trsf&)pp->_CSFDB_GetPTopLoc_Datum3DmyTrsf(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PTopLoc_Datum3D::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PTopLoc_Datum3D::SRead(p,f,theSchema);
}
