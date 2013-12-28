#ifndef _ShapeSchema_PPoly_Polygon2D_HeaderFile
#include <ShapeSchema_PPoly_Polygon2D.hxx>
#endif
#ifndef _PPoly_Polygon2D_HeaderFile
#include <PPoly_Polygon2D.hxx>
#endif
#include <ShapeSchema_PPoly_Polygon2D.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PPoly_Polygon2D,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PPoly_Polygon2D,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PPoly_Polygon2D::New() const
{
  return new PPoly_Polygon2D(Storage_stCONSTclCOM());
}

void ShapeSchema_PPoly_Polygon2D::SAdd(const Handle(PPoly_Polygon2D)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PPoly_Polygon2D")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPPoly_Polygon2DmyNodes());

    }
  }
}

void ShapeSchema_PPoly_Polygon2D::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PPoly_Polygon2D::SAdd((Handle(PPoly_Polygon2D)&)p,theSchema);
}

void ShapeSchema_PPoly_Polygon2D::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PPoly_Polygon2D) &pp = (Handle(PPoly_Polygon2D)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutReal(pp->_CSFDB_GetPPoly_Polygon2DmyDeflection());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPPoly_Polygon2DmyNodes(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PPoly_Polygon2D::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PPoly_Polygon2D::SWrite(p,f,theSchema);
}


void ShapeSchema_PPoly_Polygon2D::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PPoly_Polygon2D) &pp = (Handle(PPoly_Polygon2D)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Real PPoly_Polygon2DmyDeflection;
    f.GetReal(PPoly_Polygon2DmyDeflection);
    pp->_CSFDB_SetPPoly_Polygon2DmyDeflection(PPoly_Polygon2DmyDeflection);

    Handle(PColgp_HArray1OfPnt2d) PPoly_Polygon2DmyNodes;

    theSchema->ReadPersistentReference(PPoly_Polygon2DmyNodes,f);
    pp->_CSFDB_SetPPoly_Polygon2DmyNodes(PPoly_Polygon2DmyNodes);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PPoly_Polygon2D::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PPoly_Polygon2D::SRead(p,f,theSchema);
}
