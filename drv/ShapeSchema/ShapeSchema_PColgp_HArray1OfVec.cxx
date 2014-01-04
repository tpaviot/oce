#ifndef _ShapeSchema_PColgp_HArray1OfVec_HeaderFile
#include <ShapeSchema_PColgp_HArray1OfVec.hxx>
#endif
#ifndef _PColgp_HArray1OfVec_HeaderFile
#include <PColgp_HArray1OfVec.hxx>
#endif
#include <ShapeSchema_PColgp_HArray1OfVec.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_HArray1OfVec,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_HArray1OfVec,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_HArray1OfVec::New() const
{
  return new PColgp_HArray1OfVec(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_HArray1OfVec::SAdd(const Handle(PColgp_HArray1OfVec)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_HArray1OfVec")) {
      
    }
  }
}

void ShapeSchema_PColgp_HArray1OfVec::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_HArray1OfVec::SAdd((Handle(PColgp_HArray1OfVec)&)p,theSchema);
}

void ShapeSchema_PColgp_HArray1OfVec::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray1OfVec) &pp = (Handle(PColgp_HArray1OfVec)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray1OfVecLowerBound());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray1OfVecUpperBound());
    ShapeSchema_PColgp_FieldOfHArray1OfVec::SWrite(pp->_CSFDB_GetPColgp_HArray1OfVecData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray1OfVec::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_HArray1OfVec::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_HArray1OfVec::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray1OfVec) &pp = (Handle(PColgp_HArray1OfVec)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColgp_HArray1OfVecLowerBound;
    f.GetInteger(PColgp_HArray1OfVecLowerBound);
    pp->_CSFDB_SetPColgp_HArray1OfVecLowerBound(PColgp_HArray1OfVecLowerBound);

    Standard_Integer PColgp_HArray1OfVecUpperBound;
    f.GetInteger(PColgp_HArray1OfVecUpperBound);
    pp->_CSFDB_SetPColgp_HArray1OfVecUpperBound(PColgp_HArray1OfVecUpperBound);

    ShapeSchema_PColgp_FieldOfHArray1OfVec::SRead((PColgp_FieldOfHArray1OfVec&)pp->_CSFDB_GetPColgp_HArray1OfVecData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray1OfVec::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_HArray1OfVec::SRead(p,f,theSchema);
}
