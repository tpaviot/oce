#ifndef _ShapeSchema_PColgp_HArray1OfVec2d_HeaderFile
#include <ShapeSchema_PColgp_HArray1OfVec2d.hxx>
#endif
#ifndef _PColgp_HArray1OfVec2d_HeaderFile
#include <PColgp_HArray1OfVec2d.hxx>
#endif
#include <ShapeSchema_PColgp_HArray1OfVec2d.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_HArray1OfVec2d,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_HArray1OfVec2d,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_HArray1OfVec2d::New() const
{
  return new PColgp_HArray1OfVec2d(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_HArray1OfVec2d::SAdd(const Handle(PColgp_HArray1OfVec2d)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_HArray1OfVec2d")) {
      
    }
  }
}

void ShapeSchema_PColgp_HArray1OfVec2d::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_HArray1OfVec2d::SAdd((Handle(PColgp_HArray1OfVec2d)&)p,theSchema);
}

void ShapeSchema_PColgp_HArray1OfVec2d::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray1OfVec2d) &pp = (Handle(PColgp_HArray1OfVec2d)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray1OfVec2dLowerBound());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray1OfVec2dUpperBound());
    ShapeSchema_PColgp_FieldOfHArray1OfVec2d::SWrite(pp->_CSFDB_GetPColgp_HArray1OfVec2dData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray1OfVec2d::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_HArray1OfVec2d::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_HArray1OfVec2d::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray1OfVec2d) &pp = (Handle(PColgp_HArray1OfVec2d)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColgp_HArray1OfVec2dLowerBound;
    f.GetInteger(PColgp_HArray1OfVec2dLowerBound);
    pp->_CSFDB_SetPColgp_HArray1OfVec2dLowerBound(PColgp_HArray1OfVec2dLowerBound);

    Standard_Integer PColgp_HArray1OfVec2dUpperBound;
    f.GetInteger(PColgp_HArray1OfVec2dUpperBound);
    pp->_CSFDB_SetPColgp_HArray1OfVec2dUpperBound(PColgp_HArray1OfVec2dUpperBound);

    ShapeSchema_PColgp_FieldOfHArray1OfVec2d::SRead((PColgp_FieldOfHArray1OfVec2d&)pp->_CSFDB_GetPColgp_HArray1OfVec2dData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray1OfVec2d::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_HArray1OfVec2d::SRead(p,f,theSchema);
}
