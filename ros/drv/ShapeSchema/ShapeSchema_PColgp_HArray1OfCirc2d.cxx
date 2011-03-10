#ifndef _ShapeSchema_PColgp_HArray1OfCirc2d_HeaderFile
#include <ShapeSchema_PColgp_HArray1OfCirc2d.hxx>
#endif
#ifndef _PColgp_HArray1OfCirc2d_HeaderFile
#include <PColgp_HArray1OfCirc2d.hxx>
#endif
#include <ShapeSchema_PColgp_HArray1OfCirc2d.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_HArray1OfCirc2d,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_HArray1OfCirc2d,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_HArray1OfCirc2d::New() const
{
  return new PColgp_HArray1OfCirc2d(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_HArray1OfCirc2d::SAdd(const Handle(PColgp_HArray1OfCirc2d)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_HArray1OfCirc2d")) {
      
    }
  }
}

void ShapeSchema_PColgp_HArray1OfCirc2d::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_HArray1OfCirc2d::SAdd((Handle(PColgp_HArray1OfCirc2d)&)p,theSchema);
}

void ShapeSchema_PColgp_HArray1OfCirc2d::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray1OfCirc2d) &pp = (Handle(PColgp_HArray1OfCirc2d)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray1OfCirc2dLowerBound());
  f.PutInteger(pp->_CSFDB_GetPColgp_HArray1OfCirc2dUpperBound());
    ShapeSchema_PColgp_FieldOfHArray1OfCirc2d::SWrite(pp->_CSFDB_GetPColgp_HArray1OfCirc2dData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray1OfCirc2d::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_HArray1OfCirc2d::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_HArray1OfCirc2d::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HArray1OfCirc2d) &pp = (Handle(PColgp_HArray1OfCirc2d)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColgp_HArray1OfCirc2dLowerBound;
    f.GetInteger(PColgp_HArray1OfCirc2dLowerBound);
    pp->_CSFDB_SetPColgp_HArray1OfCirc2dLowerBound(PColgp_HArray1OfCirc2dLowerBound);

    Standard_Integer PColgp_HArray1OfCirc2dUpperBound;
    f.GetInteger(PColgp_HArray1OfCirc2dUpperBound);
    pp->_CSFDB_SetPColgp_HArray1OfCirc2dUpperBound(PColgp_HArray1OfCirc2dUpperBound);

    ShapeSchema_PColgp_FieldOfHArray1OfCirc2d::SRead((PColgp_FieldOfHArray1OfCirc2d&)pp->_CSFDB_GetPColgp_HArray1OfCirc2dData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_HArray1OfCirc2d::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_HArray1OfCirc2d::SRead(p,f,theSchema);
}
