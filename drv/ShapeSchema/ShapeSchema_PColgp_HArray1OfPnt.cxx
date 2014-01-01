#ifndef _ShapeSchema_PColgp_HArray1OfPnt_HeaderFile
#include <ShapeSchema_PColgp_HArray1OfPnt.hxx>
#endif
#ifndef _PColgp_HArray1OfPnt_HeaderFile
#include <PColgp_HArray1OfPnt.hxx>
#endif
#include <ShapeSchema_PColgp_HArray1OfPnt.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_HArray1OfPnt,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_HArray1OfPnt,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_HArray1OfPnt::New() const
{
  return new PColgp_HArray1OfPnt(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_HArray1OfPnt::SAdd(const Handle(PColgp_HArray1OfPnt)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_HArray1OfPnt")) {
      
    }
  }
}

void ShapeSchema_PColgp_HArray1OfPnt::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_HArray1OfPnt::SAdd((Handle(PColgp_HArray1OfPnt)&)p,theSchema);
}

void ShapeSchema_PColgp_HArray1OfPnt::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray1OfPnt) &pp = (Handle(PColgp_HArray1OfPnt)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray1OfPntLowerBound());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray1OfPntUpperBound());
    ShapeSchema_PColgp_FieldOfHArray1OfPnt::SWrite(pp->_CSFDB_GetPColgp_HArray1OfPntData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray1OfPnt::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_HArray1OfPnt::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_HArray1OfPnt::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray1OfPnt) &pp = (Handle(PColgp_HArray1OfPnt)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColgp_HArray1OfPntLowerBound;
    f.GetInteger(PColgp_HArray1OfPntLowerBound);
    pp->_CSFDB_SetPColgp_HArray1OfPntLowerBound(PColgp_HArray1OfPntLowerBound);

    Standard_Integer PColgp_HArray1OfPntUpperBound;
    f.GetInteger(PColgp_HArray1OfPntUpperBound);
    pp->_CSFDB_SetPColgp_HArray1OfPntUpperBound(PColgp_HArray1OfPntUpperBound);

    ShapeSchema_PColgp_FieldOfHArray1OfPnt::SRead((PColgp_FieldOfHArray1OfPnt&)pp->_CSFDB_GetPColgp_HArray1OfPntData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray1OfPnt::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_HArray1OfPnt::SRead(p,f,theSchema);
}
