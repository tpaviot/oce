#ifndef _ShapeSchema_PPoly_Polygon3D_HeaderFile
#include <ShapeSchema_PPoly_Polygon3D.hxx>
#endif
#ifndef _PPoly_Polygon3D_HeaderFile
#include <PPoly_Polygon3D.hxx>
#endif
#include <ShapeSchema_PPoly_Polygon3D.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PPoly_Polygon3D,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PPoly_Polygon3D,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PPoly_Polygon3D::New() const
{
  return new PPoly_Polygon3D(Storage_stCONSTclCOM());
}

void ShapeSchema_PPoly_Polygon3D::SAdd(const Handle(PPoly_Polygon3D)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PPoly_Polygon3D")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPPoly_Polygon3DmyNodes());
   theSchema->PersistentToAdd(p->_CSFDB_GetPPoly_Polygon3DmyParameters());

    }
  }
}

void ShapeSchema_PPoly_Polygon3D::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PPoly_Polygon3D::SAdd((Handle(PPoly_Polygon3D)&)p,theSchema);
}

void ShapeSchema_PPoly_Polygon3D::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PPoly_Polygon3D) &pp = (Handle(PPoly_Polygon3D)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutReal(pp->_CSFDB_GetPPoly_Polygon3DmyDeflection());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPPoly_Polygon3DmyNodes(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPPoly_Polygon3DmyParameters(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PPoly_Polygon3D::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PPoly_Polygon3D::SWrite(p,f,theSchema);
}


void ShapeSchema_PPoly_Polygon3D::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PPoly_Polygon3D) &pp = (Handle(PPoly_Polygon3D)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Real PPoly_Polygon3DmyDeflection;
    f.GetReal(PPoly_Polygon3DmyDeflection);
    pp->_CSFDB_SetPPoly_Polygon3DmyDeflection(PPoly_Polygon3DmyDeflection);

    Handle(PColgp_HArray1OfPnt) PPoly_Polygon3DmyNodes;

    theSchema->ReadPersistentReference(PPoly_Polygon3DmyNodes,f);
    pp->_CSFDB_SetPPoly_Polygon3DmyNodes(PPoly_Polygon3DmyNodes);

    Handle(PColStd_HArray1OfReal) PPoly_Polygon3DmyParameters;

    theSchema->ReadPersistentReference(PPoly_Polygon3DmyParameters,f);
    pp->_CSFDB_SetPPoly_Polygon3DmyParameters(PPoly_Polygon3DmyParameters);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PPoly_Polygon3D::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PPoly_Polygon3D::SRead(p,f,theSchema);
}
